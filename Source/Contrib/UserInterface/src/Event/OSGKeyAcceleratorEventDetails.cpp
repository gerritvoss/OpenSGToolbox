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

#include "OSGKeyAcceleratorEventDetails.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGKeyAcceleratorEventDetailsBase.cpp file.
// To modify it, please change the .fcd file (OSGKeyAcceleratorEventDetails.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void KeyAcceleratorEventDetails::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

KeyAcceleratorEventDetailsTransitPtr KeyAcceleratorEventDetails::create(  FieldContainer* const Source,
                                                            Time TimeStamp,
                                                            UInt32 TheKey,
                                                            UInt32 Modifiers)
{
    KeyAcceleratorEventDetails* TheEventDetails = KeyAcceleratorEventDetails::createUnregistered();

    TheEventDetails->setSource(Source);
    TheEventDetails->setTimeStamp(TimeStamp);
    TheEventDetails->setKey(TheKey);
    TheEventDetails->setModifiers(Modifiers);

    return KeyAcceleratorEventDetailsTransitPtr(TheEventDetails);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

KeyAcceleratorEventDetails::KeyAcceleratorEventDetails(void) :
    Inherited()
{
}

KeyAcceleratorEventDetails::KeyAcceleratorEventDetails(const KeyAcceleratorEventDetails &source) :
    Inherited(source)
{
}

KeyAcceleratorEventDetails::~KeyAcceleratorEventDetails(void)
{
}

/*----------------------------- class specific ----------------------------*/

void KeyAcceleratorEventDetails::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void KeyAcceleratorEventDetails::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump KeyAcceleratorEventDetails NI" << std::endl;
}

OSG_END_NAMESPACE
