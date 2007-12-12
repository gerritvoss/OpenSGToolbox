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

#include "OSGComboBox.h"
#include "OSGMutableComboBoxModel.h"
#include "Component/Menu/OSGPopupMenu.h"
#include "Component/Container/OSGFrame.h"
#include "Component/Button/OSGToggleButton.h"
#include "Component/ComboBox/Editors/OSGComboBoxEditor.h"
#include "Component/Menu/OSGLabelMenuItem.h"
#include "Util/OSGUIDrawUtils.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ComboBox
A UI ComboBox 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ComboBox::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ComboBox::updateLayout(void)
{
	Pnt2s BorderTopLeft, BorderBottomRight;
	getInsideInsetsBounds(BorderTopLeft, BorderBottomRight);

	//Place the Expand button on the Left
	beginEditCP(getExpandButton(), PositionFieldMask | SizeFieldMask);
		getExpandButton()->setSize(getExpandButton()->getPreferredSize());
		
        getExpandButton()->setPosition(calculateAlignment(BorderTopLeft, (BorderBottomRight-BorderTopLeft), getExpandButton()->getSize(),0.5, 1.0));
	endEditCP(getExpandButton(), PositionFieldMask | SizeFieldMask);

	//Editor
	if(getEditable() && getEditor() != NullFC && getEditor()->getEditorComponent() != NullFC)
	{
		beginEditCP(getEditor()->getEditorComponent(), PositionFieldMask | SizeFieldMask);
			getEditor()->getEditorComponent()->setSize(Vec2s(BorderBottomRight.x() - BorderTopLeft.x() - getExpandButton()->getSize().x(), getExpandButton()->getSize().y()));
			getEditor()->getEditorComponent()->setPosition(Pnt2s(BorderTopLeft.x(), getExpandButton()->getPosition().y()));
		endEditCP(getEditor()->getEditorComponent(), PositionFieldMask | SizeFieldMask);
	}

	//Selected Item Component
	if(!getEditable() && getRendererSelcetedItem() != NullFC)
	{
		beginEditCP(getRendererSelcetedItem(), PositionFieldMask | SizeFieldMask);
			getRendererSelcetedItem()->setSize(Vec2s(BorderBottomRight.x() - BorderTopLeft.x() - getExpandButton()->getSize().x(), getExpandButton()->getSize().y()));
			getRendererSelcetedItem()->setPosition(Pnt2s(BorderTopLeft.x(), getExpandButton()->getPosition().y()));
		endEditCP(getRendererSelcetedItem(), PositionFieldMask | SizeFieldMask);
	}
}

void ComboBox::actionPerformed(const ActionEvent& e)
{
	//Called by the MenuItems in my popupMenu

	//Need to determine the index of this MenuItem
	UInt32 i(0);
	while(i<getComboListPopupMenu()->getNumItems() && 
		getComboListPopupMenu()->getItem(i) != MenuItem::Ptr::dcast(e.getSource()))
	{
		++i;
	}

	if(i < getComboListPopupMenu()->getNumItems())
	{
		_Model->setSelectedItem(i);
		if(getEditable() && getEditor() != NullFC && getEditor()->getEditorComponent() != NullFC)
		{
			getEditor()->selectAll();
			getEditor()->getEditorComponent()->takeFocus();
		}
	}
}

void ComboBox::contentsChanged(ListDataEvent e)
{
	//TODO:Implement
	updateListFromModel();
}

void ComboBox::intervalAdded(ListDataEvent e)
{
	//TODO:Implement
}

void ComboBox::intervalRemoved(ListDataEvent e)
{
	//TODO:Implement
}

void ComboBox::selectionChanged(const ComboBoxSelectionEvent& e)
{
	//Update the Selected Item Component
	updateSelectedItemComponent();
}

void ComboBox::removeActionListener(ActionListenerPtr Listener)
{
   ActionListenerSetItor EraseIter(_ActionListeners.find(Listener));
   if(EraseIter != _ActionListeners.end())
   {
      _ActionListeners.erase(EraseIter);
   }
}


void ComboBox::addItem(SharedFieldPtr anObject)
{
	if(_Model != NULL && dynamic_cast<MutableComboBoxModelPtr>(_Model))
	{
		dynamic_cast<MutableComboBoxModelPtr>(_Model)->addElement(anObject);
	}
}

void ComboBox::configureEditor(ComboBoxEditorPtr anEditor, SharedFieldPtr anItem)
{
	//TODO:Implement
}

std::string ComboBox::getActionCommand(void) const
{
	//TODO:Implement
	return std::string("");
}

void ComboBox::insertItemAt(SharedFieldPtr anObject, const UInt32& index)
{
	if(_Model != NULL && dynamic_cast<MutableComboBoxModelPtr>(_Model))
	{
		dynamic_cast<MutableComboBoxModelPtr>(_Model)->insertElementAt(anObject, index);
	}
}

void ComboBox::processKeyEvent(KeyEvent e)
{
	//TODO:Implement
}

void ComboBox::removeAllItems(void)
{
	if(_Model != NULL && dynamic_cast<MutableComboBoxModelPtr>(_Model))
	{
		dynamic_cast<MutableComboBoxModelPtr>(_Model)->removeAllElements();
	}
}

void ComboBox::removeItem(SharedFieldPtr anObject)
{
	if(_Model != NULL && dynamic_cast<MutableComboBoxModelPtr>(_Model))
	{
		dynamic_cast<MutableComboBoxModelPtr>(_Model)->removeElement(anObject);
	}
}

void ComboBox::removeItemAt(const UInt32& anIndex)
{
	if(_Model != NULL && dynamic_cast<MutableComboBoxModelPtr>(_Model))
	{
		dynamic_cast<MutableComboBoxModelPtr>(_Model)->removeElementAt(anIndex);
	}
}

bool ComboBox::selectWithKey(KeyEvent::Key TheKey)
{
	//TODO:Implement
	return false;
}

void ComboBox::setActionCommand(std::string aCommand)
{
	//TODO:Implement
}


void ComboBox::setModel(ComboBoxModelPtr aModel)
{
	if(_Model != NULL)
	{
		_Model->removeListDataListener(this);
		_Model->removeSelectionListener(this);
	}

	_Model = aModel;

	if(_Model != NULL)
	{
		_Model->addListDataListener(this);
		_Model->addSelectionListener(this);
		updateListFromModel();
	}
}

void ComboBox::setPopupVisible(bool v)
{
	if(v)
	{
		showPopup();
	}
	else
	{
		hidePopup();
	}
}

void ComboBox::showPopup(void)
{
	Pnt2s BorderTopLeft, BorderBottomRight;
	getInsideInsetsBounds(BorderTopLeft, BorderBottomRight);

    beginEditCP(getComboListPopupMenu(), PopupMenu::InvokerFieldMask | PopupMenu::VisibleFieldMask | Component::PositionFieldMask);
       getComboListPopupMenu()->setInvoker(ComponentPtr(this));
       getComboListPopupMenu()->setVisible(true);
       getComboListPopupMenu()->setPosition(ComponentToFrame(BorderTopLeft + Vec2s(0,BorderBottomRight.y()), ComponentPtr(this)));
	   getComboListPopupMenu()->setSelection(_Model->getSelectedItemIndex());
    endEditCP(getComboListPopupMenu(), PopupMenu::InvokerFieldMask | PopupMenu::VisibleFieldMask | Component::PositionFieldMask);
    
    beginEditCP(getParentFrame(), Frame::ActivePopupMenusFieldMask);
        getParentFrame()->getActivePopupMenus().addValue(getComboListPopupMenu());
    endEditCP(getParentFrame(), Frame::ActivePopupMenusFieldMask);
}

void ComboBox::updateListFromModel(void)
{
	//Update the PopupMenu
	for(UInt32 i(0) ; i<getComboListPopupMenu()->getNumItems() ; ++i)
	{
		LabelMenuItem::Ptr::dcast(getComboListPopupMenu()->getItem(i))->removeActionListener(this);
	}
	getComboListPopupMenu()->removeAllItems();

	
    LabelMenuItemPtr Item;
	std::string TheText;
	for(UInt32 i(0) ; i<_Model->getSize() ; ++i)
	{
		Item = LabelMenuItem::create();
		if(_Model->getElementAt(i)->getType() == SFString::getClassType())
		{
            TheText = dynamic_cast<SFString*>(_Model->getElementAt(i).get())->getValue();
		}
		else
		{
			_Model->getElementAt(i)->getValueByStr(TheText);
		}
		beginEditCP(Item, LabelMenuItem::TextFieldMask);
			Item->setText(TheText);
		endEditCP(Item, LabelMenuItem::TextFieldMask);
		Item->addActionListener(this);

		getComboListPopupMenu()->addItem(Item);
	}

	//Update the Selected Item Component
	updateSelectedItemComponent();
}

void ComboBox::updateSelectedItemComponent(void)
{
	//Update the Editor
	if(getEditable() && getEditor() != NullFC && _Model->getSelectedItemIndex() >=0 )
	{
		getEditor()->setItem(_Model->getElementAt(_Model->getSelectedItemIndex()));
	}

	//Update the Selected Item Component
}

void ComboBox::configurePropertiesFromAction(Action a)
{
	//TODO:Implement
}

void ComboBox::produceActionPerformed(const ActionEvent& e)
{
	ActionListenerSet Liseners(_ActionListeners);
    for(ActionListenerSetConstItor SetItor(Liseners.begin()) ; SetItor != Liseners.end() ; ++SetItor)
    {
	    (*SetItor)->actionPerformed(e);
    }
}

void ComboBox::keyTyped(const KeyEvent& e)
{
	if(e.getKey() == KeyEvent::KEY_UP)
	{
		if(_Model->getSelectedItemIndex() > 0)
		{
			_Model->setSelectedItem(_Model->getSelectedItemIndex() - 1);
		}
	}
	else if(e.getKey() == KeyEvent::KEY_DOWN)
	{
		if(_Model->getSelectedItemIndex() < _Model->getSize()-1)
		{
			_Model->setSelectedItem(_Model->getSelectedItemIndex() + 1);
		}
	}
	else
	{
		Inherited::keyTyped(e);
	}
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ComboBox::ComboBox(void) :
    Inherited(),
		_Model(NULL),
		_CellRenderer(NULL),
		_ExpandButtonSelectedListener(ComboBoxPtr(this))
{
	beginEditCP(ComboBoxPtr(this), ComboListPopupMenuFieldMask);
		setComboListPopupMenu(PopupMenu::create());
	endEditCP(ComboBoxPtr(this), ComboListPopupMenuFieldMask);
}

ComboBox::ComboBox(const ComboBox &source) :
    Inherited(source),
		_Model(source._Model),
		_CellRenderer(source._CellRenderer),
		_ExpandButtonSelectedListener(ComboBoxPtr(this))
{
	beginEditCP(ComboBoxPtr(this), ComboListPopupMenuFieldMask);
		setComboListPopupMenu(PopupMenu::create());
	endEditCP(ComboBoxPtr(this), ComboListPopupMenuFieldMask);
	
    if(getExpandButton() != NullFC)
    {
        beginEditCP(ComboBoxPtr(this), ExpandButtonFieldMask);
			setExpandButton(ToggleButton::Ptr::dcast(getExpandButton()->shallowCopy()));
        endEditCP(ComboBoxPtr(this), ExpandButtonFieldMask);
    }
}

ComboBox::~ComboBox(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ComboBox::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

	if((whichField & ExpandButtonFieldMask) &&
		getExpandButton() != NullFC)
	{
		getExpandButton()->addButtonSelectedListener(&_ExpandButtonSelectedListener);
		getComboListPopupMenu()->addPopupMenuListener(&_ExpandButtonSelectedListener);
	}
	
    if( (whichField & ExpandButtonFieldMask) ||
        (whichField & EditorFieldMask) ||
        (whichField & EditableFieldMask) ||
        (whichField & RendererSelcetedItemFieldMask))
    {
        beginEditCP(ComboBoxPtr(this), ChildrenFieldMask);
            getChildren().clear();
			if(getExpandButton() != NullFC)
			{
				getChildren().addValue(getExpandButton());
			}
			if(getEditable() && getEditor() != NullFC && getEditor()->getEditorComponent() != NullFC)
			{
				getChildren().addValue(getEditor()->getEditorComponent());
			}
			if(!getEditable() && getRendererSelcetedItem() != NullFC)
			{
				getChildren().addValue(getRendererSelcetedItem());
			}
        endEditCP(ComboBoxPtr(this), ChildrenFieldMask);
    }
}

void ComboBox::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ComboBox NI" << std::endl;
}

void ComboBox::ExpandButtonSelectedListener::buttonSelected(const ButtonSelectedEvent& e)
{
	_ComboBox->setPopupVisible(true);
}

void ComboBox::ExpandButtonSelectedListener::buttonDeselected(const ButtonSelectedEvent& e)
{
	_ComboBox->setPopupVisible(false);
}

void ComboBox::ExpandButtonSelectedListener::popupMenuCanceled(const PopupMenuEvent& e)
{
	if(_ComboBox->getExpandButton()->getSelected())
	{
		beginEditCP(_ComboBox->getExpandButton(), ToggleButton::SelectedFieldMask);
			_ComboBox->getExpandButton()->setSelected(false);
		endEditCP(_ComboBox->getExpandButton(), ToggleButton::SelectedFieldMask);
	}
}

void ComboBox::ExpandButtonSelectedListener::popupMenuWillBecomeInvisible(const PopupMenuEvent& e)
{
	if(_ComboBox->getExpandButton()->getSelected())
	{
		beginEditCP(_ComboBox->getExpandButton(), ToggleButton::SelectedFieldMask);
			_ComboBox->getExpandButton()->setSelected(false);
		endEditCP(_ComboBox->getExpandButton(), ToggleButton::SelectedFieldMask);
	}
}
void ComboBox::ExpandButtonSelectedListener::popupMenuWillBecomeVisible(const PopupMenuEvent& e)
{
	if(!_ComboBox->getExpandButton()->getSelected())
	{
		beginEditCP(_ComboBox->getExpandButton(), ToggleButton::SelectedFieldMask);
			_ComboBox->getExpandButton()->setSelected(true);
		endEditCP(_ComboBox->getExpandButton(), ToggleButton::SelectedFieldMask);
	}
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
    static Char8 cvsid_hpp       [] = OSGCOMBOBOXBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCOMBOBOXBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCOMBOBOXFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

