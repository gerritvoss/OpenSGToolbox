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

#define OSG_COMPILEINPUTLIB

#include <OpenSG/OSGConfig.h>

#include "OSGMouseWheelEvent.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::MouseWheelEvent

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MouseWheelEvent::initMethod (void)
{
}

MouseWheelEventPtr MouseWheelEvent::create(  FieldContainerPtr Source,
                                    Time TimeStamp,
                                    Int32 WheelRotation,
                                    UInt8 TheScrollType,
                                    UInt8 ScrollOrientation,
                                    Pnt2f Location,
                                    ViewportPtr TheViewport)
{
    MouseWheelEventPtr TheEvent = MouseWheelEvent::createEmpty();

    TheEvent->setSource(Source);
    TheEvent->setTimeStamp(TimeStamp);
    TheEvent->setWheelRotation(WheelRotation);
    TheEvent->setScrollType(TheScrollType);
    TheEvent->setScrollOrientation(ScrollOrientation);
    TheEvent->setLocation(Location);
    TheEvent->setViewport(TheViewport);

    return TheEvent;
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

void MouseWheelEvent::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void MouseWheelEvent::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump MouseWheelEvent NI" << std::endl;
}


OSG_END_NAMESPACE

