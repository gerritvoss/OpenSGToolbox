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

#include "OSGMouseWheelEvent.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMouseWheelEventBase.cpp file.
// To modify it, please change the .fcd file (OSGMouseWheelEvent.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MouseWheelEvent::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

MouseWheelEventTransitPtr MouseWheelEvent::create(  FieldContainerUnrecPtr Source,
                                    Time TimeStamp,
                                    Int32 WheelRotation,
                                    UInt8 TheScrollType,
                                    UInt8 ScrollOrientation,
                                    Pnt2f Location,
                                    ViewportUnrecPtr TheViewport)
{
    MouseWheelEvent* TheEvent = MouseWheelEvent::createEmpty();

    TheEvent->setSource(Source);
    TheEvent->setTimeStamp(TimeStamp);
    TheEvent->setWheelRotation(WheelRotation);
    TheEvent->setScrollType(TheScrollType);
    TheEvent->setScrollOrientation(ScrollOrientation);
    TheEvent->setLocation(Location);
    TheEvent->setViewport(TheViewport);

    return MouseWheelEventTransitPtr(TheEvent);
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MouseWheelEvent::MouseWheelEvent(void) :
    Inherited()
{
}

MouseWheelEvent::MouseWheelEvent(const MouseWheelEvent &source) :
    Inherited(source)
{
}

MouseWheelEvent::~MouseWheelEvent(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MouseWheelEvent::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void MouseWheelEvent::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump MouseWheelEvent NI" << std::endl;
}

OSG_END_NAMESPACE
