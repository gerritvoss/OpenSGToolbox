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

#include "OSGInventory.h"
#include "OSGInventoryItem.h"

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
	sortInventory();
	if(getRootInventory() && !Item->getClasses().isEmpty())
	{
		for(UInt32 i = 0; i < Item->getClasses().getSize(); i++)
		{
			bool classExists = false;
			for(UInt32 c = 0; c < getInventoryClasses().getSize(); c++)
			{
				if(Item->getClasses(i) == getInventoryClasses(c)->getInventoryClassName())
				{
					classExists = true;
					getInventoryClasses(c)->addItem(Item);
				}
			}
			if(!classExists)
			{
				InventoryPtr CInventory = osg::Inventory::create();
				beginEditCP(CInventory, Inventory::RootInventoryFieldMask | Inventory::InventoryClassNameFieldMask);
					setInventoryClassName(Item->getClasses(i));
					setRootInventory(false);
				endEditCP(CInventory, Inventory::RootInventoryFieldMask | Inventory::InventoryClassNameFieldMask);
				getInventoryClasses().push_back(CInventory);
				CInventory->addItem(Item);
			}
		}
	}
}
void Inventory::sortInventory()
{

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
    static Char8 cvsid_hpp       [] = OSGINVENTORYBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGINVENTORYBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGINVENTORYFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

