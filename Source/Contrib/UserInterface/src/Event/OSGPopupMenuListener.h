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

#ifndef _OSGPOPUPMENULISTENER_H_
#define _OSGPOPUPMENULISTENER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"

#include "OSGEventListener.h"
#include "OSGPopupMenuEvent.h"

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING PopupMenuListener : public EventListener
{
   /*=========================  PUBLIC  ===============================*/
public:
	//This method is called when the popup menu is canceled
	virtual void 	popupMenuCanceled(const PopupMenuEventUnrecPtr e) = 0;
	//This method is called before the popup menu becomes invisible Note that a JPopupMenu can become invisible any time
	virtual void 	popupMenuWillBecomeInvisible(const PopupMenuEventUnrecPtr e) = 0;
	//This method is called before the popup menu becomes visible
	virtual void 	popupMenuWillBecomeVisible(const PopupMenuEventUnrecPtr e) = 0;
	//This method is called before the items of the popup menu change
	virtual void 	popupMenuContentsChanged(const PopupMenuEventUnrecPtr e) = 0;
};

typedef PopupMenuListener* PopupMenuListenerPtr;

OSG_END_NAMESPACE

#endif /* _OSGPOPUPMENULISTENER_H_ */
