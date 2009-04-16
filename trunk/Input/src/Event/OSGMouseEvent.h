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

#include <OpenSG/OSGConfig.h>
#include "OSGInputDef.h"

#include "Event/OSGInputEvent.h"

#include <OpenSG/OSGVector.h>
#include <OpenSG/OSGViewport.h>

OSG_BEGIN_NAMESPACE

class OSG_INPUTLIB_DLLMAPPING MouseEvent : public InputEvent
{
    /*=========================  PUBLIC  ===============================*/
  public:
    enum MouseButton {BUTTON1 = 0, BUTTON2, BUTTON3, BUTTON4, BUTTON5, BUTTON6, BUTTON7, BUTTON8, BUTTON9, BUTTON10, NO_BUTTON};
  
    MouseButton getButton(void) const;
    UInt16 getClickCount(void) const;
    
    Pnt2f getLocationOnScreen(void) const;
    Pnt2f getLocation(void) const;
    
    Real32 getX(void) const;
    Real32 getXOnScreen(void) const;
    Real32 getY(void) const;
    Real32 getYOnScreen(void) const;
    ViewportPtr getViewport(void) const;
    
    MouseEvent(FieldContainerPtr Source, Time TimeStamp, WindowEventProducerPtr Producer, MouseButton Button, UInt16 ClickCount, Pnt2f Location, ViewportPtr TheViewport);
    
    virtual const EventType &getType(void) const;
    
    static const EventType &getClassType(void);
    
  protected:
    MouseButton _Button;
    UInt16      _ClickCount;
    Pnt2f       _Location;
    ViewportPtr _Viewport;
    
  private:
     static EventType _Type;
    
};

OSG_END_NAMESPACE

#include "OSGMouseEvent.inl"

#endif /* _OSGEVENT_H_ */
