/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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
#include "OSGDragGestureRecognizer.h"
#include "OSGDragGestureEvent.h"
#include "OSGComponent.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

EventConnection DragGestureRecognizer::addDragGestureListener(DragGestureListenerPtr Listener)
{
    _DragGestureListeners.insert(Listener);
   return EventConnection(
       boost::bind(&DragGestureRecognizer::isDragGestureListenerAttached, this, Listener),
       boost::bind(&DragGestureRecognizer::removeDragGestureListener, this, Listener));
}

void DragGestureRecognizer::removeDragGestureListener(DragGestureListenerPtr Listener)
{
   DragGestureListenerSetItor EraseIter(_DragGestureListeners.find(Listener));
   if(EraseIter != _DragGestureListeners.end())
   {
      _DragGestureListeners.erase(EraseIter);
   }
}

void DragGestureRecognizer::produceDragGestureRecognized(ComponentRefPtr TheComponent, const Pnt2f &DragLocation) const
{
    const DragGestureEventUnrecPtr e = DragGestureEvent::create(TheComponent, getSystemTime(), DragLocation);
	DragGestureListenerSet Listeners(_DragGestureListeners);
    for(DragGestureListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->draqGestureRecognized(e);
    }
}

OSG_END_NAMESPACE
