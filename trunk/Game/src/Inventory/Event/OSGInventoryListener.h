/*---------------------------------------------------------------------------*\
 *                          OpenSG Toolbox Game                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Eric Langkamp                                    *
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

#ifndef _OSGINVENTORYLISTENER_H_
#define _OSGINVENTORYLISTENER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGGameDef.h"

#include <OpenSG/Input/OSGEventListener.h>
#include "OSGInventoryEvent.h"

OSG_BEGIN_NAMESPACE

class OSG_GAMELIB_DLLMAPPING InventoryListener : public EventListener
{
    /*=========================  PUBLIC  ===============================*/
  public:
  
    virtual void itemAdded(const InventoryEvent& e) = 0;
    virtual void inventorySorted(const InventoryEvent& e) = 0;
    virtual void itemRemoved(const InventoryEvent& e) = 0;
    
};

typedef InventoryListener* InventoryListenerPtr;

OSG_END_NAMESPACE

#endif /* _OSGINVENTORYLISTENER_H_ */
