/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#ifndef _OSGMOUSEEVENT_H_
#define _OSGMOUSEEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGInputConfig.h"

#include "Event/OSGEvent.h"

#include <OpenSG/OSGVector.h>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBaseTypeSystem
 */

class OSG_INPUT_CLASS_API MouseEvent : public Event
{
    /*=========================  PUBLIC  ===============================*/
  public:
    enum MouseButton {BUTTON1 = 1, BUTTON2, BUTTON3, BUTTON4, BUTTON5, BUTTON6, BUTTON7, BUTTON8, BUTTON9, BUTTON10};
  
    MouseButton getButton(void) const;
    UInt16 getClickCount(void) const;
    
    Pnt2us getLocationOnScreen(void) const;
    Pnt2us getLocation(void) const;
    
    UInt16 getX(void) const;
    UInt16 getXOnScreen(void) const;
    UInt16 getY(void) const;
    UInt16 getYOnScreen(void) const;
    
    MouseEvent(FieldContainerPtr Source, Time TimeStamp, MouseButton Button, UInt16 ClickCount, Pnt2s Location);
  private:
    MouseButton _Button;
    UInt16      _ClickCount;
    Pnt2s       _Location;
    
};

OSG_END_NAMESPACE

#include "OSGMouseEvent.inl"
      
#define _OSGMOUSEEVENT_H_ "@(#)$Id: $"

#endif /* _OSGEVENT_H_ */
