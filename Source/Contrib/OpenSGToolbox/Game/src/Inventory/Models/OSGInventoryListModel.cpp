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

#include "OSGInventoryListModel.h"
#include "Inventory/OSGInventoryItem.h"
#include "Inventory/Models/Comparitors/OSGInventoryListComparitor.h"
#include "Inventory/Models/Comparitors/OSGDefaultInventoryListComparitor.h"
#include "Inventory/Models/InventorySubsets/OSGInventorySubset.h"

#include <algorithm>


OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::InventoryListModel
A InventoryListModel. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void InventoryListModel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
UInt32 InventoryListModel::getSize(void) const
{
	return _InventoryItems.size();
}

boost::any InventoryListModel::getElementAt(UInt32 index) const
{
	if(index < getSize())
	{
		return getCurrentInventory()->getInventoryItems(_InventoryItems.at(index));
	}
	else
	{
        return boost::any();
	}
}

void InventoryListModel::setupInventoryItems()
{
	for(UInt32 i = 0; getCurrentInventory()->getInventoryItems().getSize() > i; ++i)
	{
		_InventoryItems.push_back(i);
	}
	if(getCurrentInventory() != NullFC && getComparitor() != NullFC)
	{
		std::sort(_InventoryItems.begin(),_InventoryItems.end(),getComparitor()->getComparitorFunc());
	}
}

void InventoryListModel::setupComparitor()
{
	DefaultInventoryListComparitorPtr DefaultComparitor = DefaultInventoryListComparitor::create();
	beginEditCP(getComparitor() , DefaultInventoryListComparitor::ModelFieldMask);
		getComparitor()->setModel(InventoryListModelPtr(this));
	endEditCP(getComparitor() , DefaultInventoryListComparitor::ModelFieldMask);
}

void InventoryListModel::setupSubset()
{
	if(getCurrentInventory()->getInventoryItems().getSize() != _InventoryItems.size())
	{
		setupInventoryItems();
	}
	getCurrentSubset()->setModel(InventoryListModelPtr(this));
	std::vector<UInt32> subset = getCurrentSubset()->GetSubset();
	_InventoryItems.assign(subset.begin(),subset.end());
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

InventoryListModel::InventoryListModel(void) :
    Inherited(),
		Ascending(false)
{
}

InventoryListModel::InventoryListModel(const InventoryListModel &source) :
    Inherited(source),
		Ascending(false)
{
}

InventoryListModel::~InventoryListModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void InventoryListModel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

	if(whichField & ComparitorFieldMask)
	{
		setupComparitor();
		std::sort(_InventoryItems.begin(),_InventoryItems.end(),getComparitor()->getComparitorFunc());
	}
    if(whichField & CurrentSubsetFieldMask || whichField & CurrentInventoryFieldMask)
	{
		_InventoryItems.clear();

		if(getCurrentInventory() == NullFC)
		{
			setupInventoryItems();
		}
		if(getCurrentSubset() != NullFC)
		{
			setupSubset();
		}
		else
		{
			setupInventoryItems();
		}
		produceListDataContentsChanged(InventoryListModelPtr(this), 0, _InventoryItems.size());
	}
}

void InventoryListModel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump InventoryListModel NI" << std::endl;
}

OSG_END_NAMESPACE

