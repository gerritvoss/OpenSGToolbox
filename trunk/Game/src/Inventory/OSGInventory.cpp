/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Game                                *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                  Authors: David Kabala, Eric Langkamp                     *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEGAMELIB

#include <OpenSG/OSGConfig.h>

#include "OSGInventory.h"
#include "OSGInventoryItem.h"
#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Inventory
A Inventory. 	 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Inventory::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Inventory::addItem(InventoryItemPtr Item)
{
	getInventoryItems().push_back(Item);
}

std::vector<InventoryItemPtr> Inventory::getItemsOfClass(std::string className)
{
	std::vector<InventoryItemPtr> items;

	for(UInt32 i = 0; i < getInventoryItems().getSize(); ++i)
	{
		if(!getInventoryItems(i)->getClasses().isEmpty())
		{
			for(UInt32 c = 0; c < getInventoryItems(i)->getClasses().getSize(); ++i)
			{
				if(getInventoryItems(i)->getClasses(c) == className)
				{
					items.push_back(getInventoryItems(i));
				}
			}
		}
	}
	return items;
}

EventConnection Inventory::addInventoryListener(InventoryListenerPtr Listener)
{
   _InventoryListeners.insert(Listener);
   return EventConnection(
       boost::bind(&Inventory::isInventoryListenerAttached, this, Listener),
       boost::bind(&Inventory::removeInventoryListener, this, Listener));
}

void Inventory::removeInventoryListener(InventoryListenerPtr Listener)
{
   InventoryListenerSetItor EraseIter(_InventoryListeners.find(Listener));
   if(EraseIter != _InventoryListeners.end())
   {
      _InventoryListeners.erase(EraseIter);
   }
}

void Inventory::produceItemAdded(const InventoryEventPtr e)
{
	InventoryListenerSet Listeners(_InventoryListeners);
    for(InventoryListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->itemAdded(e);
    }
    produceEvent(ItemAddedMethodId,e);
}
void Inventory::produceInventorySorted(const InventoryEventPtr e)
{
	InventoryListenerSet Listeners(_InventoryListeners);
    for(InventoryListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->inventorySorted(e);
    }
    produceEvent(InventorySortedMethodId,e);
}
void Inventory::produceItemRemoved(const InventoryEventPtr e)
{
	InventoryListenerSet Listeners(_InventoryListeners);
    for(InventoryListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->itemRemoved(e);
    }
    produceEvent(ItemRemovedMethodId,e);
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

void Inventory::setupAsRoot()
{
	beginEditCP(InventoryPtr(this), Inventory::RootInventoryFieldMask | Inventory::InventoryClassNameFieldMask);
		setInventoryClassName("Root");
		setRootInventory(true);
	endEditCP(InventoryPtr(this), Inventory::RootInventoryFieldMask | Inventory::InventoryClassNameFieldMask);
}

Inventory::Inventory(void) :
    Inherited()
{
	setupAsRoot();
}

Inventory::Inventory(const Inventory &source) :
    Inherited(source)
{
	setupAsRoot();
}

Inventory::~Inventory(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Inventory::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

	if(whichField & InventoryClassNameFieldMask)
    {
	beginEditCP(InventoryPtr(this), Inventory::RootInventoryFieldMask);
		setRootInventory(false);
	endEditCP(InventoryPtr(this), Inventory::RootInventoryFieldMask);
    }
}

void Inventory::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Inventory NI" << std::endl;
}

OSG_END_NAMESPACE

