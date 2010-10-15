/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGLuaActivity.h"
#include "OSGLuaManager.h"
#include "OSG_wrap.h"
#include "OSGFilePathAttachment.h"
#include "OSGContainerUtils.h"
#include <fstream>
#include <sstream>
#include <boost/algorithm/string.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGLuaActivityBase.cpp file.
// To modify it, please change the .fcd file (OSGLuaActivity.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

LuaActivity::FuncMap  LuaActivity::_GlobalLuaActivities = LuaActivity::FuncMap();

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LuaActivity::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::Static)
    {
        FilePathAttachment::registerHandler(LuaActivity::getClassType(),LuaActivity::createLuaActivity);
    }
}

FieldContainerTransitPtr LuaActivity::createLuaActivity( const BoostPath& FilePath )
{
    LuaActivity* Result = LuaActivity::createEmpty();
    FilePathAttachment::setFilePath(Result, FilePath);

    std::ifstream TheFile;
    TheFile.exceptions(std::fstream::failbit | std::fstream::badbit);

    try
    {
        TheFile.open(FilePath.string().c_str());
        if(TheFile)
        {
            std::ostringstream Code;
            Code << TheFile.rdbuf();
            TheFile.close();

                Result->setCode(Code.str());
        }
        return FieldContainerTransitPtr(Result);
    }
    catch(std::fstream::failure &f)
    {
        SWARNING << "LuaActivity::createLuaActivity(): Error reading file" << FilePath.string() << ": " << f.what() << std::endl;
        return FieldContainerTransitPtr(NULL);
    }

}

boost::signals2::connection LuaActivity::addLuaCallback(FieldContainerRefPtr producerObject, std::string funcName, UInt32 producedEventId)
{
    if(producerObject->isEventProducer())
    {
        if(funcName.empty())
        {
            SWARNING << "LuaActivity::addLuaCallback(): Attempt to attach an empty function name." << std::endl;
            return boost::signals2::connection();
        }

        //Find an attached LuaActivity with the same
        //       ProducerObject
        //       Function
        //       ProducedMethodID
        LuaFuncGroup TheFuncGroup(producerObject, funcName, producedEventId);
        FuncMap::iterator SearchItor(_GlobalLuaActivities.find(TheFuncGroup));
        if(SearchItor != _GlobalLuaActivities.end() &&
           (*SearchItor).second.second.connected())
        {
            SWARNING << "Lua function: " << funcName << " is already attached to this produced method." << std::endl;
            return (*SearchItor).second.second;
        }

        LuaActivityUnrecPtr TheLuaActivity = LuaActivity::create();
        TheLuaActivity->setEntryFunction(funcName);
        commitChanges();

        boost::signals2::connection TheConnection(producerObject->attachActivity(producedEventId, TheLuaActivity));
        //BUG: Need to add ref count to keep it from being deleted,
        //but who has responsibility for deleting it?
        _GlobalLuaActivities[TheFuncGroup] = ActivityConnectionPair(TheLuaActivity, TheConnection);
        return TheConnection;
    }
    else
    {
        SWARNING << "LuaActivity::addLuaCallback(): Producer object is not an event producer." << std::endl;
        return boost::signals2::connection();
    }
}
    
boost::signals2::connection LuaActivity::addLuaCallback(FieldContainerRefPtr producerObject,
                                        std::string funcName,
                                        const std::string& producedEventName)
{
    const EventDescription* Desc(producerObject->getEventDescription(producedEventName.c_str()));
    if(Desc == NULL)
    {
        SWARNING << "No producedEvent named: " << producedEventName << " defined on containers of type: " << producerObject->getType().getName() << "." << std::endl;
        return boost::signals2::connection();
    }
    return addLuaCallback(producerObject, funcName, Desc->getEventId());
}

void LuaActivity::removeLuaCallback(FieldContainerRefPtr producerObject,
                       std::string funcName,
                       UInt32 producedEventId)
{
    LuaFuncGroup TheFuncGroup(producerObject, funcName, producedEventId);
    FuncMap::iterator SearchItor(_GlobalLuaActivities.find(TheFuncGroup));
    if(SearchItor != _GlobalLuaActivities.end())
    {
        (*SearchItor).second.second.disconnect();
        _GlobalLuaActivities.erase(SearchItor);
    }
}

void LuaActivity::removeLuaCallback(FieldContainerRefPtr producerObject,
                                    std::string funcName,
                                    const std::string& producedEventName)
{
    const EventDescription* Desc(producerObject->getEventDescription(producedEventName.c_str()));
    if(Desc == NULL)
    {
        SWARNING << "No producedEvent named: " << producedEventName << " defined on containers of type: " << producerObject->getType().getName() << "." << std::endl;
    }
    else
    {
        removeLuaCallback(producerObject, funcName, Desc->getEventId());
    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void LuaActivity::eventProduced(EventDetails* const details, UInt32 producedEventId)
{
    if(!getCode().empty())
    {
        //Run my Code
        if(LuaManager::the()->runScript(getCode()) != 0)
        {
            //Failed to run the script
            return;
        }
    }

    //If there is an entry function then call it
    if(!getEntryFunction().empty())
    {
        //Get the Lua state
        lua_State *LuaState(LuaManager::the()->getLuaState());

        //Get the Lua function to be called
        for(UInt32 i(0) ; i<_EntryFunctionPath.size() ; ++i)
        {
            if(i == 0)
            {
                lua_pushstring(LuaState,_EntryFunctionPath[i].c_str());             //push the name of the table on the stack
                lua_gettable(LuaState, LUA_GLOBALSINDEX);  //Push The table onto the stack
            }
            else
            {
                //Check if the the value given is a table
                if(!lua_istable(LuaState, -1))
                {
                    lua_pop(LuaState, 1); //Pop the value off the stack
                    std::string TablePath("");
                    for(UInt32 j(0) ; j<i ; ++j)
                    {
                        if(j!=0) TablePath += ".";
                        TablePath += _EntryFunctionPath[j];
                    }
                    SWARNING << TablePath << " cannot be referenced in lua because it is not a table" << std::endl;
                    return;
                }
            
                lua_pushstring(LuaState,_EntryFunctionPath[i].c_str());             //push the name of the table on the stack
                lua_gettable(LuaState, -2);  //Push The table onto the stack

                //Remove the original table from the stack
                lua_remove(LuaState, -2);
            }
        }

        //Check if the the value given is a function
        if(!lua_isfunction(LuaState, -1))
        {
            lua_pop(LuaState, 1); //Pop the value off the stack

            SWARNING << getEntryFunction() << " cannot be referenced in lua because it is not a function" << std::endl;
            return;
        }

        //Push on the arguments
        push_FieldContainer_on_lua(LuaState, details);   //Argument 1: the EventUnrecPtr

        lua_pushnumber(LuaState,producedEventId);             //Argument 2: the ProducedEvent ID

        //Execute the Function
        //                                   |------2 arguments to function
        //                                   |
        //                                   |  |---0 arguments returned
        //                                   |  |
        //                                   V  V
        LuaManager::the()->runPushedFunction(2, 0);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

LuaActivity::LuaActivity(void) :
    Inherited()
{
}

LuaActivity::LuaActivity(const LuaActivity &source) :
    Inherited(source)
{
}

LuaActivity::~LuaActivity(void)
{
}

/*----------------------------- class specific ----------------------------*/

void LuaActivity::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);


    if(whichField & EntryFunctionFieldMask)
    {
        //Split the Entry function up by nested tables
        boost::algorithm::split( _EntryFunctionPath, getEntryFunction(), boost::algorithm::is_any_of(std::string(".")) );
    }
}

void LuaActivity::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump LuaActivity NI" << std::endl;
}


LuaActivity::LuaFuncGroup::LuaFuncGroup(FieldContainer* EventProducer, std::string Function, UInt32 ProducedEventID) :
_EventProducer(EventProducer),
_Function(Function),
_ProducedEventID(ProducedEventID)
{
}

bool LuaActivity::LuaFuncComp::operator()(const LuaFuncGroup& Left, const LuaFuncGroup& Right) const
{
    int StrComp(Left._Function.compare(Right._Function));
    if(StrComp == 0)
    {
        if(Left._ProducedEventID == Right._ProducedEventID)
        {
            return Left._EventProducer < Right._EventProducer;
        }
        else
        {
            return Left._ProducedEventID < Right._ProducedEventID;
        }
    }
    else
    {
        return StrComp < 0;
    }
}

OSG_END_NAMESPACE
