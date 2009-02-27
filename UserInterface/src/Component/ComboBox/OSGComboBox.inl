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
#include "OSGUserInterfaceDef.h"

#include "Component/Menu/OSGListGeneratedPopupMenu.h"
#include "Models/OSGComboBoxModel.h"
OSG_BEGIN_NAMESPACE

inline
UInt32 ComboBox::getSelectedIndex(void) const
{
	return getModel()->getSelectedItemIndex();
}

inline
boost::any ComboBox::getSelectedItem(void) const
{
	return getModel()->getSelectedItem();
}

inline
boost::any ComboBox::getItemAt(const UInt32& index) const
{
	return getModel()->getElementAt(index);
}

inline
UInt32 ComboBox::getItemCount(void) const
{
	return getModel()->getSize();
}

inline
void ComboBox::addActionListener(ActionListenerPtr Listener)
{
   _ActionListeners.insert(Listener);
}

inline
void ComboBox::setSelectedIndex(const UInt32& anIndex)
{
	getModel()->setSelectedItem(anIndex);
}

inline
void ComboBox::setSelectedItem(const boost::any& anObject)
{
	getModel()->setSelectedItem(anObject);
}

inline
void ComboBox::addPopupMenuListener(PopupMenuListenerPtr Listener)
{
	getComboListPopupMenu()->addPopupMenuListener(Listener);
}

inline
void ComboBox::removePopupMenuListener(PopupMenuListenerPtr Listener)
{
	getComboListPopupMenu()->removePopupMenuListener(Listener);
}

inline
bool ComboBox::isPopupVisible(void) const
{
	return getComboListPopupMenu()->getVisible();
}

inline
void ComboBox::hidePopup(void)
{
	getComboListPopupMenu()->clearSelection();
}

inline
ComboBox::ExpandButtonSelectedListener::ExpandButtonSelectedListener(ComboBoxPtr TheComboBox) :
   _ComboBox(TheComboBox)
{
}

inline
ComboBox::EditorListener::EditorListener(ComboBoxPtr TheComboBox) :
   _ComboBox(TheComboBox)
{
}

OSG_END_NAMESPACE

#define OSGCOMBOBOX_INLINE_CVSID "@(#)$Id: FCTemplate_inl.h,v 1.8 2002/12/04 14:22:22 dirk Exp $"

