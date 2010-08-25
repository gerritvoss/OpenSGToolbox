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

#include "OSGLuaErrorEventDetails.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGLuaErrorEventDetailsBase.cpp file.
// To modify it, please change the .fcd file (OSGLuaErrorEventDetails.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LuaErrorEventDetails::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

LuaErrorEventDetailsTransitPtr LuaErrorEventDetails::create(FieldContainer* const Source,
                                              Time TimeStamp,
                                              lua_State* State,
                                              int LuaStatus,
                                              const std::list<std::string>& StackTrace,
                                              bool EnableStackTrace)
{
    LuaErrorEventDetails* TheEventDetails = LuaErrorEventDetails::createUnregistered();

    TheEventDetails->setSource(Source);
    TheEventDetails->setTimeStamp(TimeStamp);
    TheEventDetails->setLuaStateVoidP(static_cast<void*>(State));
    TheEventDetails->setStatus(LuaStatus);
    for(std::list<std::string>::const_iterator Itor(StackTrace.begin())
            ; Itor != StackTrace.end()
            ; ++Itor)
    {
        TheEventDetails->editMFStackTrace()->push_back(*Itor);
    }
    TheEventDetails->setStackTraceEnabled(EnableStackTrace);

    return LuaErrorEventDetailsTransitPtr(TheEventDetails);
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

LuaErrorEventDetails::LuaErrorEventDetails(void) :
    Inherited()
{
}

LuaErrorEventDetails::LuaErrorEventDetails(const LuaErrorEventDetails &source) :
    Inherited(source)
{
}

LuaErrorEventDetails::~LuaErrorEventDetails(void)
{
}

/*----------------------------- class specific ----------------------------*/

void LuaErrorEventDetails::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void LuaErrorEventDetails::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump LuaErrorEventDetails NI" << std::endl;
}

OSG_END_NAMESPACE
