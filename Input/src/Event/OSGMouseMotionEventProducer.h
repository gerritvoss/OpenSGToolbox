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

#ifndef _OSGMOUSEMOTIONEVENTPRODUCER_H_
#define _OSGMOUSEMOTIONEVENTPRODUCER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGInputDef.h"
#include "OSGEventProducer.h"

#include "OSGMouseMotionListener.h"
#include <set>

OSG_BEGIN_NAMESPACE

class OSG_INPUTLIB_DLLMAPPING MouseMotionEventProducer : public EventProducer
{
public:
    void addMouseMotionListener(MouseMotionListenerPtr Listener);
    void removeMouseMotionListener(MouseMotionListenerPtr Listener);

  protected:
	typedef std::set<MouseMotionListenerPtr> MouseMotionListenerSet;
    typedef MouseMotionListenerSet::iterator MouseMotionListenerSetItor;
    typedef MouseMotionListenerSet::const_iterator MouseMotionListenerSetConstItor;
	
    MouseMotionListenerSet       _MouseMotionListeners;
	
    virtual void produceMouseMoved(const MouseEvent& e);
    virtual void produceMouseDragged(const MouseEvent& e);

    MouseMotionEventProducer(void);
};

OSG_END_NAMESPACE

#include "OSGMouseMotionEventProducer.inl"

#endif /* _OSGMOUSEMOTIONEVENTPRODUCER_H_ */
