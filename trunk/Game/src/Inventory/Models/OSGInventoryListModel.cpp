/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Game                                *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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
		return getCurrentInventory()->getInventoryItems(_InventoryItems.at(index))->getName();
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
	if(getCurrentInventory() != NullFC)
	{
		std::sort(_InventoryItems.begin(),_InventoryItems.end(),getComparitor()->getComparitorFunc());
	}
}

void InventoryListModel::setupComparitor()
{
	DefaultInventoryListComparitorPtr DefaultComparitor = DefaultInventoryListComparitor::create();
	beginEditCP(getComparitor() , DefaultInventoryListComparitor::ModelFieldMask);
		DefaultComparitor->setModel(InventoryListModelPtr(this));
	endEditCP(getComparitor() , DefaultInventoryListComparitor::ModelFieldMask);

	beginEditCP(InventoryListModelPtr(this), InventoryListModel::ComparitorFieldMask);
		setComparitor(DefaultComparitor);
	endEditCP(InventoryListModelPtr(this), InventoryListModel::ComparitorFieldMask);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

InventoryListModel::InventoryListModel(void) :
    Inherited()
{
}

InventoryListModel::InventoryListModel(const InventoryListModel &source) :
    Inherited(source)
{
}

InventoryListModel::~InventoryListModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void InventoryListModel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
	
    if(whichField & CurrentInventoryFieldMask)
	{
		setupInventoryItems();
	}

}

void InventoryListModel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump InventoryListModel NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGINVENTORYLISTMODELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGINVENTORYLISTMODELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGINVENTORYLISTMODELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

