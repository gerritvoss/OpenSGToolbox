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

#include "OSGSoundEvent.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSoundEventBase.cpp file.
// To modify it, please change the .fcd file (OSGSoundEvent.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SoundEvent::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

SoundEventTransitPtr SoundEvent::create(  FieldContainerUnrecPtr Source,
                                    Time TimeStamp,
                                    UInt32 Channel)
{
    SoundEvent* TheEvent = SoundEvent::createEmpty();

    TheEvent->setSource(Source);
    TheEvent->setTimeStamp(TimeStamp);
    TheEvent->setChannel(Channel);

    return SoundEventTransitPtr(TheEvent);
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SoundEvent::SoundEvent(void) :
    Inherited()
{
}

SoundEvent::SoundEvent(const SoundEvent &source) :
    Inherited(source)
{
}

SoundEvent::~SoundEvent(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SoundEvent::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void SoundEvent::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SoundEvent NI" << std::endl;
}

OSG_END_NAMESPACE
