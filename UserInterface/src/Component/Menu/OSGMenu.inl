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

#include <OpenSG/OSGConfig.h>
#include "OSGPopupMenu.h"

OSG_BEGIN_NAMESPACE

inline
void Menu::addItem(MenuItemPtr Item)
{
    getInternalPopupMenu()->addItem(Item);
}

inline
void Menu::addItem(MenuItemPtr Item, const UInt32& Index)
{
    getInternalPopupMenu()->addItem(Item, Index);
}

inline
void Menu::removeItem(MenuItemPtr Item)
{
    getInternalPopupMenu()->removeItem(Item);
}

inline
void Menu::removeItem(const UInt32& Index)
{
    getInternalPopupMenu()->removeItem(Index);
}

inline
MenuItemPtr Menu::getItem(const UInt32& Index)
{
    return getInternalPopupMenu()->getItem(Index);
}

inline
UInt32 Menu::getNumItems(void) const
{
    return getInternalPopupMenu()->getNumItems();
}

inline
bool Menu::getPopupVisible(void) const
{
    return getInternalPopupMenu()->getVisible();
}

inline
Menu::PopupUpdateListener::PopupUpdateListener(MenuPtr TheMenu) :
									_Menu(TheMenu),
									_PopupElps(0.0)
{
}

inline
void Menu::PopupUpdateListener::reset(void)
{
    _PopupElps = 0.0;
}

OSG_END_NAMESPACE

#define OSGMENU_INLINE_CVSID "@(#)$Id: FCTemplate_inl.h,v 1.8 2002/12/04 14:22:22 dirk Exp $"

