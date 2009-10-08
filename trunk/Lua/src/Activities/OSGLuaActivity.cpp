/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILELUALIB

#include <OpenSG/OSGConfig.h>

#include "OSGLuaActivity.h"
#include "Manager/OSGLuaManager.h"
#include "Bindings/OSG_wrap.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::LuaActivity

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LuaActivity::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void LuaActivity::eventProduced(const EventPtr EventDetails, UInt32 ProducedEventId)
{
    //Run my Code
    LuaManager::the()->runScript(getCode());

    //If there is an entry function then call it
    if(!getEntryFunction().empty())
    {
        //Get the Lua state
        lua_State *LuaState(LuaManager::the()->getLuaState());

        //Get the Lua function to be called
        lua_getglobal(LuaState, getEntryFunction().c_str());

        //Push on the arguments
        push_FieldContainer_on_lua(LuaState, EventDetails);   //Argument 1: the EventPtr

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

void LuaActivity::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void LuaActivity::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump LuaActivity NI" << std::endl;
}


OSG_END_NAMESPACE

