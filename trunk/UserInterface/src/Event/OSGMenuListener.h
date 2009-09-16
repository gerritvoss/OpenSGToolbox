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

#ifndef _OSGMENULISTENER_H_
#define _OSGMENULISTENER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/Toolbox/OSGEventListener.h>
#include "OSGMenuEvent.h"

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING MenuListener : public EventListener
{
   /*=========================  PUBLIC  ===============================*/
public:
	//Invoked when the menu is canceled.
	virtual void menuCanceled(const MenuEvent& e) = 0;
	//Invoked when the menu is deselected.
	virtual void menuDeselected(const MenuEvent& e) = 0;
	//Invoked when a menu is selected.
	virtual void menuSelected(const MenuEvent& e) = 0;
};

typedef MenuListener* MenuListenerPtr;

OSG_END_NAMESPACE

#endif /* _OSGMENULISTENER_H_ */
