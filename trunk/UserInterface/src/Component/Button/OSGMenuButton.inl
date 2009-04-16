/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
bool MenuButton::isMenuActionListenerAttached(ActionListenerPtr Listener) const
{
    return _MenuActionListeners.find(Listener) != _MenuActionListeners.end();
}

inline
bool MenuButton::isPopupMenuListenerAttached(PopupMenuListenerPtr Listener) const
{
    return getMenuButtonPopupMenu()->isPopupMenuListenerAttached(Listener);
}

inline
EventConnection MenuButton::addPopupMenuListener(PopupMenuListenerPtr Listener)
{
	return getMenuButtonPopupMenu()->addPopupMenuListener(Listener);
}

inline
void MenuButton::removePopupMenuListener(PopupMenuListenerPtr Listener)
{
	getMenuButtonPopupMenu()->removePopupMenuListener(Listener);
}
inline 
bool MenuButton::isPopupVisible(void) const
{
    return getMenuButtonPopupMenu()->getVisible();
}

inline
MenuButton::MenuButtonEventsListener::MenuButtonEventsListener(MenuButtonPtr TheMenuButton) : _MenuButton(TheMenuButton)
{
}

OSG_END_NAMESPACE

#define OSGMENUBUTTON_INLINE_CVSID "@(#)$Id: FCTemplate_inl.h,v 1.8 2002/12/04 14:22:22 dirk Exp $"

