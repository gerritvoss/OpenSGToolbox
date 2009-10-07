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

#include "OSGLuaErrorEvent.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::LuaErrorEvent

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LuaErrorEvent::initMethod (void)
{
}

LuaErrorEventPtr LuaErrorEvent::create(  FieldContainerPtr Source,
                                    Time TimeStamp,
                                    lua_State* State,
                                    int LuaStatus,
                                    const std::list<std::string>& StackTrace,
                                    bool EnableStackTrace)
{
    LuaErrorEventPtr TheEvent = LuaErrorEvent::createEmpty();

    TheEvent->setSource(Source);
    TheEvent->setTimeStamp(TimeStamp);
    TheEvent->setLuaStateVoidP(static_cast<void*>(State));
    TheEvent->setStatus(LuaStatus);
    for(std::list<std::string>::const_iterator Itor(StackTrace.begin())
            ; Itor != StackTrace.end()
            ; ++Itor)
    {
        TheEvent->editMFStackTrace()->push_back(*Itor);
    }
    TheEvent->setStackTraceEnabled(EnableStackTrace);

    return TheEvent;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

LuaErrorEvent::LuaErrorEvent(void) :
    Inherited()
{
}

LuaErrorEvent::LuaErrorEvent(const LuaErrorEvent &source) :
    Inherited(source)
{
}

LuaErrorEvent::~LuaErrorEvent(void)
{
}

/*----------------------------- class specific ----------------------------*/

void LuaErrorEvent::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void LuaErrorEvent::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump LuaErrorEvent NI" << std::endl;
}


OSG_END_NAMESPACE

