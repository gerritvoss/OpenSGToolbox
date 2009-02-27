/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
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

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGListGeneratedPopupMenu.h"
#include "OSGMenuItem.h"
#include "OSGComponentMenuItem.h"
#include "Component/List/Models/OSGListModel.h" // Model type
#include "ComponentGenerators/OSGComponentGenerator.h" // CellGenerator type
#include <OpenSG/Toolbox/OSGStringUtils.h> // CellGenerator type

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ListGeneratedPopupMenu
A UI List Generated PopupMenu. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ListGeneratedPopupMenu::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


void ListGeneratedPopupMenu::addItem(MenuItemPtr Item)
{
	//Do Nothing
}

void ListGeneratedPopupMenu::addItem(MenuItemPtr Item, const UInt32& Index)
{
	//Do Nothing
}

void ListGeneratedPopupMenu::removeItem(MenuItemPtr Item)
{
	//Do Nothing
}

void ListGeneratedPopupMenu::removeItem(const UInt32& Index)
{
	//Do Nothing
}

void ListGeneratedPopupMenu::removeAllItems(void)
{
	//Do Nothing
}

MenuItemPtr ListGeneratedPopupMenu::getItem(const UInt32& Index)
{
	if(getModel() != NullFC && Index < getChildren().size())
	{
		return MenuItem::Ptr::dcast(getChildren()[Index]);
	}
	else
	{
		return NullFC;
	}
}

UInt32 ListGeneratedPopupMenu::getNumItems(void) const
{
	if(getModel() != NullFC)
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
    beginEditCP(ListGeneratedPopupMenuPtr(this), ChildrenFieldMask);
        getChildren().clear();

		if(getModel() != NullFC)// && )
		{
			MenuItemPtr Item;
			for(Int32 i(0) ; i<getModel()->getSize() ; ++i)
			{
				if(getCellGenerator() != NullFC)
				{
					Item = ComponentMenuItem::create();
					ComponentPtr TheComponent = getCellGenerator()->getComponent(ListGeneratedPopupMenuPtr(this), getModel()->getElementAt(i), i, 0, false, false);

					beginEditCP(TheComponent, Component::BackgroundsFieldMask);
						TheComponent->setBackgrounds(NullFC);
					endEditCP(TheComponent, Component::BackgroundsFieldMask);

					
					beginEditCP(Item, ComponentMenuItem::ComponentFieldMask);
						ComponentMenuItem::Ptr::dcast(Item)->setComponent(TheComponent);
					endEditCP(Item, ComponentMenuItem::ComponentFieldMask);
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
					beginEditCP(Item, MenuItem::TextFieldMask);
						MenuItem::Ptr::dcast(Item)->setText(TheText);
					endEditCP(Item, MenuItem::TextFieldMask);
				}
				getChildren().push_back(Item);
			}
		}
    endEditCP(ListGeneratedPopupMenuPtr(this), ChildrenFieldMask);
	producePopupMenuContentsChanged(PopupMenuEvent(PopupMenuPtr(this), getSystemTime()));
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ListGeneratedPopupMenu::ListGeneratedPopupMenu(void) :
    Inherited(),
		_ModelListener(ListGeneratedPopupMenuPtr(this))
{
}

ListGeneratedPopupMenu::ListGeneratedPopupMenu(const ListGeneratedPopupMenu &source) :
    Inherited(source),
		_ModelListener(ListGeneratedPopupMenuPtr(this))
{
}

ListGeneratedPopupMenu::~ListGeneratedPopupMenu(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ListGeneratedPopupMenu::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
	
	if(whichField & ModelFieldMask)
	{
		if(getModel() != NullFC)
		{
			getModel()->addListDataListener(&_ModelListener);
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


void ListGeneratedPopupMenu::ModelListener::contentsChanged(ListDataEvent e)
{
	_ListGeneratedPopupMenu->updateMenuItems();
}

void ListGeneratedPopupMenu::ModelListener::intervalAdded(ListDataEvent e)
{
	_ListGeneratedPopupMenu->updateMenuItems();
}

void ListGeneratedPopupMenu::ModelListener::intervalRemoved(ListDataEvent e)
{
	_ListGeneratedPopupMenu->updateMenuItems();
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
    static Char8 cvsid_hpp       [] = OSGLISTGENERATEDPOPUPMENUBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGLISTGENERATEDPOPUPMENUBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGLISTGENERATEDPOPUPMENUFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

