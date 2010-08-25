/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGListGeneratedPopupMenu.h"
#include "OSGMenuItem.h"
#include "OSGComponentMenuItem.h"
#include "OSGListModel.h" // Model type
#include "OSGComponentGenerator.h" // CellGenerator type
#include "OSGStringUtils.h" // CellGenerator type

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGListGeneratedPopupMenuBase.cpp file.
// To modify it, please change the .fcd file (OSGListGeneratedPopupMenu.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ListGeneratedPopupMenu::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ListGeneratedPopupMenu::addItem(MenuItem* const Item)
{
	//Do Nothing
    SWARNING << "Cannot add item to ListGeneratedPopupMenu" << std::endl;
}

void ListGeneratedPopupMenu::addItem(MenuItem* const Item, const UInt32& Index)
{
	//Do Nothing
    SWARNING << "Cannot add item to ListGeneratedPopupMenu" << std::endl;
}

void ListGeneratedPopupMenu::removeItem(MenuItem* const Item)
{
	//Do Nothing
    SWARNING << "Cannot remove Item from ListGeneratedPopupMenu" << std::endl;
}

void ListGeneratedPopupMenu::removeItem(const UInt32& Index)
{
	//Do Nothing
    SWARNING << "Cannot remove Item from ListGeneratedPopupMenu" << std::endl;
}

void ListGeneratedPopupMenu::removeAllItems(void)
{
	//Do Nothing
    SWARNING << "Cannot remove All Items from ListGeneratedPopupMenu" << std::endl;
}

MenuItem* ListGeneratedPopupMenu::getItem(const UInt32& Index)
{
	if(getModel() != NULL && Index < getMFChildren()->size())
	{
		return dynamic_cast<MenuItem*>(getChildren(Index));
	}
	else
	{
		return NULL;
	}
}

UInt32 ListGeneratedPopupMenu::getNumItems(void) const
{
	if(getModel() != NULL)
	{
		return getModel()->getSize();
	}
	else
	{
		return 0;
	}
}

void ListGeneratedPopupMenu::updateMenuItems(void)
{
    bool changed(false);

    if(getMFChildren()->size() > 0)
    {
        changed = true;
        clearChildren();
    }

    if(getModel() != NULL)
    {
        changed = true;
        MenuItemRefPtr Item;
        for(Int32 i(0) ; i<getModel()->getSize() ; ++i)
        {
            if(getCellGenerator() != NULL)
            {
                Item = ComponentMenuItem::create();
                ComponentRefPtr TheComponent = getCellGenerator()->getComponent(this, getModel()->getElementAt(i), i, 0, false, false);

                TheComponent->setBackgrounds(NULL);


                dynamic_pointer_cast<ComponentMenuItem>(Item)->setComponent(TheComponent);
            }
            else
            {
                //Generate the Menu Item
                Item = MenuItem::create();
                std::string TheText;
                try
                {
                    TheText = lexical_cast(getModel()->getElementAt(i));
                }
                catch (boost::bad_lexical_cast &)
                {
                    //Could not convert to a string
                }
                dynamic_pointer_cast<MenuItem>(Item)->setText(TheText);
            }
            pushToChildren(Item);
        }
    }

    if(changed)
    {
        producePopupMenuContentsChanged();
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ListGeneratedPopupMenu::ListGeneratedPopupMenu(void) :
    Inherited()
{
}

ListGeneratedPopupMenu::ListGeneratedPopupMenu(const ListGeneratedPopupMenu &source) :
    Inherited(source)
{
}

ListGeneratedPopupMenu::~ListGeneratedPopupMenu(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ListGeneratedPopupMenu::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
	
	if(whichField & ModelFieldMask)
	{
        _ListContentsChangedConnection.disconnect();
        _ListIntervalAddedConnection.disconnect();
        _ListIntervalRemovedConnection.disconnect();
		if(getModel() != NULL)
		{
            _ListContentsChangedConnection = getModel()->connectListDataContentsChanged(boost::bind(&ListGeneratedPopupMenu::handleListContentsChanged, this, _1));
            _ListIntervalAddedConnection = getModel()->connectListDataIntervalAdded(boost::bind(&ListGeneratedPopupMenu::handleListIntervalAdded, this, _1));
            _ListIntervalRemovedConnection = getModel()->connectListDataIntervalRemoved(boost::bind(&ListGeneratedPopupMenu::handleListIntervalRemoved, this, _1));
		}
	}

	if((whichField & ModelFieldMask) ||
	   (whichField & CellGeneratorFieldMask))
	{
		updateMenuItems();
	}
}

void ListGeneratedPopupMenu::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ListGeneratedPopupMenu NI" << std::endl;
}

void ListGeneratedPopupMenu::handleListContentsChanged(ListDataEventDetails* const e)
{
	updateMenuItems();
}

void ListGeneratedPopupMenu::handleListIntervalAdded(ListDataEventDetails* const e)
{
	updateMenuItems();
}

void ListGeneratedPopupMenu::handleListIntervalRemoved(ListDataEventDetails* const e)
{
	updateMenuItems();
}

OSG_END_NAMESPACE
