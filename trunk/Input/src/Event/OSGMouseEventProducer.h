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

#ifndef _OSGMOUSEVENTPRODUCER_H_
#define _OSGMOUSEVENTPRODUCER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGInputDef.h"
#include <OpenSG/Toolbox/OSGEventProducer.h>

#include "OSGMouseListener.h"
#include <set>

OSG_BEGIN_NAMESPACE

class OSG_INPUTLIB_DLLMAPPING MouseEventProducer : public EventProducer
{
public:
    void addMouseListener(MouseListenerPtr Listener);
    void removeMouseListener(MouseListenerPtr Listener);

  protected:
	typedef std::set<MouseListenerPtr> MouseListenerSet;
    typedef MouseListenerSet::iterator MouseListenerSetItor;
    typedef MouseListenerSet::const_iterator MouseListenerSetConstItor;
	
    MouseListenerSet       _MouseListeners;
	
    void produceMouseClicked(const MouseEvent& e);
    void produceMouseEntered(const MouseEvent& e);
    void produceMouseExited(const MouseEvent& e);
    void produceMousePressed(const MouseEvent& e);
    void produceMouseReleased(const MouseEvent& e);

    MouseEventProducer(void);
};

OSG_END_NAMESPACE

#include "OSGMouseEventProducer.inl"

#endif /* _OSGMOUSEVENTPRODUCER_H_ */


