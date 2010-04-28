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

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGLuaActivityBase.cpp file.
// To modify it, please change the .fcd file (OSGLuaActivity.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

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

LuaActivityRefPtr LuaActivity::addLuaCallback(FieldContainerRefPtr producerObject, std::string funcName, UInt32 producedMethodId)
{
    if(isEventProducer(producerObject))
    {
        if(funcName.empty())
        {
            SWARNING << "LuaActivity::addLuaCallback(): Attempt to attach an empty function name." << std::endl;
            return NULL;
        }

        //Check if a LuaActivity with this funcName is already attached
        ActivityUnrecPtr CheckActiviy;
        for(UInt32 i(0) ; i<getEventProducer(producerObject)->getNumAttachedActivities() ; ++i)
        {
            CheckActiviy = getEventProducer(producerObject)->getAttachedActivity(producedMethodId, i);

            if(CheckActiviy->getType() == LuaActivity::getClassType() &&
                dynamic_pointer_cast<LuaActivity>(CheckActiviy)->getEntryFunction().compare(funcName) == 0)
            {
                SWARNING << "Lua function: " << funcName << " is already attached to this produced method." << std::endl;
                return dynamic_pointer_cast<LuaActivity>(CheckActiviy);
            }
        }

        LuaActivityUnrecPtr TheLuaActivity = LuaActivity::create();
        TheLuaActivity->setEntryFunction(funcName);
        getEventProducer(producerObject)->attachActivity(TheLuaActivity,producedMethodId);
        return TheLuaActivity;
    }
    else
    {
        SWARNING << "LuaActivity::addLuaCallback(): Producer object is not an event producer." << std::endl;
        return NULL;
    }
}

void LuaActivity::removeLuaCallback(FieldContainerRefPtr producerObject,LuaActivityRefPtr toRemove, UInt32 producedMethodId)
{
    if(isEventProducer(producerObject))
    {
        getEventProducer(producerObject)->detachActivity(toRemove,producedMethodId);
    }
    else
    {
        SWARNING << "LuaActivity::removeLuaCallback(): Producer object is not an envent producer." << std::endl;
    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void LuaActivity::eventProduced(const EventUnrecPtr EventDetails, UInt32 ProducedEventId)
{
    if(!getCode().empty())
    {
        //Run my Code
        LuaManager::the()->runScript(getCode());
    }

    //If there is an entry function then call it
    if(!getEntryFunction().empty())
    {
        //Get the Lua state
        lua_State *LuaState(LuaManager::the()->getLuaState());

        //Get the Lua function to be called
        lua_getglobal(LuaState, getEntryFunction().c_str());

        //Push on the arguments
        push_FieldContainer_on_lua(LuaState, EventDetails);   //Argument 1: the EventUnrecPtr

        lua_pushnumber(LuaState,ProducedEventId);             //Argument 2: the ProducedEvent ID

        //Execute the Function
        //                                                 |------2 arguments to function
        //                                                 |
        //                                                 |  |---0 arguments returned
        //                                                 |  |
        //                                                 V  V
        LuaManager::the()->checkError( lua_pcall(LuaState, 2, 0, 0) );
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
}

void LuaActivity::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump LuaActivity NI" << std::endl;
}

OSG_END_NAMESPACE
