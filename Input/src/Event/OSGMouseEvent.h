/*---------------------------------------------------------------------------*\
 *                            OpenSGToolbox                                  *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *   contact: dkabala@vrac.iastate.edu                                       *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 3.                               *
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
#ifndef _OSGMOUSEEVENT_H_
#define _OSGMOUSEEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGInputConfig.h"

#include "Event/OSGEvent.h"

#include <OpenSG/OSGVector.h>

OSG_BEGIN_NAMESPACE

class OSG_INPUT_CLASS_API MouseEvent : public Event
{
    /*=========================  PUBLIC  ===============================*/
  public:
    enum MouseButton {NO_BUTTON = 0, BUTTON1 = 1, BUTTON2, BUTTON3, BUTTON4, BUTTON5, BUTTON6, BUTTON7, BUTTON8, BUTTON9, BUTTON10};
  
    MouseButton getButton(void) const;
    UInt16 getClickCount(void) const;
    
    Pnt2s getLocationOnScreen(void) const;
    Pnt2s getLocation(void) const;
    
    Int16 getX(void) const;
    Int16 getXOnScreen(void) const;
    Int16 getY(void) const;
    Int16 getYOnScreen(void) const;
    
    MouseEvent(FieldContainerPtr Source, Time TimeStamp, MouseButton Button, UInt16 ClickCount, Pnt2s Location);
  private:
    MouseButton _Button;
    UInt16      _ClickCount;
    Pnt2s       _Location;
    
};

OSG_END_NAMESPACE

#include "OSGMouseEvent.inl"

#endif /* _OSGEVENT_H_ */
