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

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGAdjustmentEvent.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AdjustmentEvent

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AdjustmentEvent::initMethod (void)
{
}

AdjustmentEventPtr AdjustmentEvent::create(  FieldContainerPtr Source,
                                     Time TimeStamp,
                                     UInt32 Value,
                                     bool ValueIsAdjusting) 
{
    AdjustmentEventPtr TheEvent = AdjustmentEvent::createEmpty();

    TheEvent->setSource(Source);
    TheEvent->setTimeStamp(TimeStamp);
    TheEvent->setValue(Value);
    TheEvent->setValueIsAdjusting(ValueIsAdjusting);

    return TheEvent;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AdjustmentEvent::AdjustmentEvent(void) :
    Inherited()
{
}

AdjustmentEvent::AdjustmentEvent(const AdjustmentEvent &source) :
    Inherited(source)
{
}

AdjustmentEvent::~AdjustmentEvent(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AdjustmentEvent::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void AdjustmentEvent::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump AdjustmentEvent NI" << std::endl;
}


OSG_END_NAMESPACE

