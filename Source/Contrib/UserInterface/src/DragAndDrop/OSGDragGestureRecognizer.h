/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

#ifndef _OSGDRAGGESTURERECOGNIZER_H_
#define _OSGDRAGGESTURERECOGNIZER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"

#include "OSGComponentFields.h"
#include "OSGEventConnection.h"
#include "OSGDragGestureListener.h"
#include <set>

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING DragGestureRecognizer
{
   /*=========================  PUBLIC  ===============================*/
public:

    //Register a new DragGestureListener.
    EventConnection addDragGestureListener(DragGestureListenerPtr Listener);
	bool isDragGestureListenerAttached(DragGestureListenerPtr Listener) const;

    //Reset the Recognizer, if its currently recognizing a gesture, ignore it.
    virtual void resetRecognizer(void) = 0;

    //unregister the current DragGestureListener
    void removeDragGestureListener(DragGestureListenerPtr Listener); 

protected:
	typedef std::set<DragGestureListenerPtr> DragGestureListenerSet;
    typedef DragGestureListenerSet::iterator DragGestureListenerSetItor;
    typedef DragGestureListenerSet::const_iterator DragGestureListenerSetConstItor;
	
    DragGestureListenerSet       _DragGestureListeners;

    void produceDragGestureRecognized(ComponentRefPtr TheComponent, const Pnt2f &DragLocation) const;

};

typedef DragGestureRecognizer* DragGestureRecognizerRefPtr;

OSG_END_NAMESPACE

#include "OSGDragGestureRecognizer.inl"

#endif /* _OSGDRAGGESTURERECOGNIZER_H_ */
