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

#include "OSGKeyAcceleratorEvent.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGKeyAcceleratorEventBase.cpp file.
// To modify it, please change the .fcd file (OSGKeyAcceleratorEvent.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void KeyAcceleratorEvent::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

KeyAcceleratorEventTransitPtr KeyAcceleratorEvent::create(  FieldContainerRefPtr Source,
                                                            Time TimeStamp,
                                                            UInt32 TheKey,
                                                            UInt32 Modifiers)
{
    KeyAcceleratorEvent* TheEvent = KeyAcceleratorEvent::createEmpty();

    TheEvent->setSource(Source);
    TheEvent->setTimeStamp(TimeStamp);
    TheEvent->setKey(TheKey);
    TheEvent->setModifiers(Modifiers);

    return KeyAcceleratorEventTransitPtr(TheEvent);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

KeyAcceleratorEvent::KeyAcceleratorEvent(void) :
    Inherited()
{
}

KeyAcceleratorEvent::KeyAcceleratorEvent(const KeyAcceleratorEvent &source) :
    Inherited(source)
{
}

KeyAcceleratorEvent::~KeyAcceleratorEvent(void)
{
}

/*----------------------------- class specific ----------------------------*/

void KeyAcceleratorEvent::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void KeyAcceleratorEvent::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump KeyAcceleratorEvent NI" << std::endl;
}

OSG_END_NAMESPACE
