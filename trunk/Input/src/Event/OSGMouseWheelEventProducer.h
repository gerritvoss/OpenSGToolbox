/*---------------------------------------------------------------------------*\
 *                          OpenSG Toolbox Input                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala                                                   *
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

#ifndef _OSGMOUSEWHEELEVENTPRODUCER_H_
#define _OSGMOUSEWHEELEVENTPRODUCER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGInputDef.h"
#include <OpenSG/Toolbox/OSGEventProducer.h>

#include "OSGMouseWheelListener.h"
#include <set>

OSG_BEGIN_NAMESPACE

class OSG_INPUTLIB_DLLMAPPING MouseWheelEventProducer : public EventProducer
{
public:
    void addMouseWheelListener(MouseWheelListenerPtr Listener);
    void removeMouseWheelListener(MouseWheelListenerPtr Listener);

  protected:
	typedef std::set<MouseWheelListenerPtr> MouseWheelListenerSet;
    typedef MouseWheelListenerSet::iterator MouseWheelListenerSetItor;
    typedef MouseWheelListenerSet::const_iterator MouseWheelListenerSetConstItor;
	
    MouseWheelListenerSet       _MouseWheelListeners;
	
    void produceMouseWheelMoved(const MouseWheelEvent& e);

    MouseWheelEventProducer(void);
};

OSG_END_NAMESPACE

#include "OSGMouseWheelEventProducer.inl"

#endif /* _OSGMOUSEWHEELEVENTPRODUCER_H_ */


