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

#include "OSGLuaErrorEvent.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGLuaErrorEventBase.cpp file.
// To modify it, please change the .fcd file (OSGLuaErrorEvent.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LuaErrorEvent::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

LuaErrorEventTransitPtr LuaErrorEvent::create(FieldContainerRefPtr Source,
                                              Time TimeStamp,
                                              lua_State* State,
                                              int LuaStatus,
                                              const std::list<std::string>& StackTrace,
                                              bool EnableStackTrace)
{
    LuaErrorEvent* TheEvent = LuaErrorEvent::createEmpty();

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

    return LuaErrorEventTransitPtr(TheEvent);
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

void LuaErrorEvent::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void LuaErrorEvent::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump LuaErrorEvent NI" << std::endl;
}

OSG_END_NAMESPACE
