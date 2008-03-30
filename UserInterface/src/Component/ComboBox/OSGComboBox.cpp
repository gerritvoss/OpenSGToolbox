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
#include "Models/OSGMutableComboBoxModel.h"
#include "Component/Menu/OSGPopupMenu.h"
#include "Component/Container/Window/OSGInternalWindow.h"
#include "Component/Button/OSGToggleButton.h"
#include "Component/ComboBox/Editors/OSGComboBoxEditor.h"
#include "Component/Menu/OSGLabelMenuItem.h"
#include "Component/ComboBox/ComponentGenerators/OSGComboBoxComponentGenerator.h"
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
	Pnt2f BorderTopLeft, BorderBottomRight;
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
			getEditor()->getEditorComponent()->setSize(Vec2f(BorderBottomRight.x() - BorderTopLeft.x() - getExpandButton()->getSize().x(), getExpandButton()->getSize().y()));
			getEditor()->getEditorComponent()->setPosition(Pnt2f(BorderTopLeft.x(), getExpandButton()->getPosition().y()));
		endEditCP(getEditor()->getEditorComponent(), PositionFieldMask | SizeFieldMask);
	}

	//Selected Item Component
	if(!getEditable() && getComponentGeneratorSelectedItem() != NullFC)
	{
		beginEditCP(getComponentGeneratorSelectedItem(), PositionFieldMask | SizeFieldMask);
			getComponentGeneratorSelectedItem()->setSize(Vec2f(BorderBottomRight.x() - BorderTopLeft.x() - getExpandButton()->getSize().x(), getExpandButton()->getSize().y()));
			getComponentGeneratorSelectedItem()->setPosition(Pnt2f(BorderTopLeft.x(), getExpandButton()->getPosition().y()));
		endEditCP(getComponentGeneratorSelectedItem(), PositionFieldMask | SizeFieldMask);
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
		getModel()->setSelectedItem(i);
		if(getEditable() && getEditor() != NullFC && getEditor()->getEditorComponent() != NullFC)
		{
			getEditor()->selectAll();
			getEditor()->getEditorComponent()->takeFocus();
		}
		if(!getEditable() && getComponentGeneratorSelectedItem() != NullFC)
		{
			getComponentGeneratorSelectedItem()->takeFocus();
		}
	}
}

void ComboBox::contentsChanged(ListDataEvent e)
{
	updateListFromModel();
}

void ComboBox::intervalAdded(ListDataEvent e)
{
	//TODO:Implement
	updateListFromModel();
}

void ComboBox::intervalRemoved(ListDataEvent e)
{
	//TODO:Implement
	updateListFromModel();
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
	if(getModel() != NullFC && getModel()->getType().isDerivedFrom(MutableComboBoxModel::getClassType()))
	{
		MutableComboBoxModel::Ptr::dcast(getModel())->addElement(anObject);
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
	if(getModel() != NullFC && getModel()->getType().isDerivedFrom(MutableComboBoxModel::getClassType()))
	{
		MutableComboBoxModel::Ptr::dcast(getModel())->insertElementAt(anObject, index);
	}
}

void ComboBox::removeAllItems(void)
{
	if(getModel() != NullFC && getModel()->getType().isDerivedFrom(MutableComboBoxModel::getClassType()))
	{
		MutableComboBoxModel::Ptr::dcast(getModel())->removeAllElements();
	}
}

void ComboBox::removeItem(SharedFieldPtr anObject)
{
	if(getModel() != NullFC && getModel()->getType().isDerivedFrom(MutableComboBoxModel::getClassType()))
	{
		MutableComboBoxModel::Ptr::dcast(getModel())->removeElement(anObject);
	}
}

void ComboBox::removeItemAt(const UInt32& anIndex)
{
	if(getModel() != NullFC && getModel()->getType().isDerivedFrom(MutableComboBoxModel::getClassType()))
	{
		MutableComboBoxModel::Ptr::dcast(getModel())->removeElementAt(anIndex);
	}
}

bool ComboBox::selectWithKey(KeyEvent::Key TheKey)
{
	UInt32 i(1);
	SharedFieldPtr ModelElement;
    std::string TheText;

    bool ExitLoop(false);
	while(i<getModel()->getSize()  && !ExitLoop)
	{
		//Get The first character of this item
		ModelElement = getModel()->getElementAt((getModel()->getSelectedItemIndex() + i) % getModel()->getSize());

        if(ModelElement->getType() == SFString::getClassType())
        {
            TheText = dynamic_cast<SFString*>(ModelElement.get())->getValue();
        }
        else
        {
            ModelElement->getValueByStr(TheText);
        }

        
		if(TheText.size() > 0 &&
		   (TheText[0] == KeyEvent::getCharFromKey(TheKey, 0) ||
		   TheText[0] == KeyEvent::getCharFromKey(TheKey, KeyEvent::KEY_MODIFIER_CAPS_LOCK)))
		{
		    ExitLoop = true;
		}
		else
		{
		    ++i;
		}
	}

	if(ExitLoop)
	{
	    getModel()->setSelectedItem((getModel()->getSelectedItemIndex() + i) % getModel()->getSize());
	}

	return false;
}

void ComboBox::setActionCommand(std::string aCommand)
{
	//TODO:Implement
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
	Pnt2f BorderTopLeft, BorderBottomRight;
	getInsideInsetsBounds(BorderTopLeft, BorderBottomRight);

    beginEditCP(getComboListPopupMenu(), PopupMenu::InvokerFieldMask | PopupMenu::VisibleFieldMask | Component::PositionFieldMask);
       getComboListPopupMenu()->setInvoker(ComponentPtr(this));
       getComboListPopupMenu()->setVisible(true);
       getComboListPopupMenu()->setPosition(ComponentToFrame(BorderTopLeft + Vec2f(0,BorderBottomRight.y()), ComponentPtr(this)));
	   getComboListPopupMenu()->setSelection(getModel()->getSelectedItemIndex());
    endEditCP(getComboListPopupMenu(), PopupMenu::InvokerFieldMask | PopupMenu::VisibleFieldMask | Component::PositionFieldMask);
    
    beginEditCP(getParentWindow(), InternalWindow::ActivePopupMenusFieldMask);
        getParentWindow()->getActivePopupMenus().push_back(getComboListPopupMenu());
    endEditCP(getParentWindow(), InternalWindow::ActivePopupMenusFieldMask);
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
	for(UInt32 i(0) ; i<getModel()->getSize() ; ++i)
	{
		Item = LabelMenuItem::create();
		if(getModel()->getElementAt(i)->getType() == SFString::getClassType())
		{
            TheText = dynamic_cast<SFString*>(getModel()->getElementAt(i).get())->getValue();
		}
		else
		{
			getModel()->getElementAt(i)->getValueByStr(TheText);
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
	if(getEditable() && getEditor() != NullFC && getModel()->getSelectedItemIndex() >=0 )
	{
		getEditor()->setItem(getModel()->getElementAt(getModel()->getSelectedItemIndex()));
	}

	//Update the Selected Item Component
	if( !getEditable() )
	{
		updateComponentGeneratorSelectedItem();
	}
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
		if(getModel()->getSelectedItemIndex() > 0)
		{
			getModel()->setSelectedItem(getModel()->getSelectedItemIndex() - 1);
		}
	}
	else if(e.getKey() == KeyEvent::KEY_DOWN)
	{
		if(getModel()->getSelectedItemIndex() < getModel()->getSize()-1)
		{
			getModel()->setSelectedItem(getModel()->getSelectedItemIndex() + 1);
		}
	}
	else if(!getEditable() && e.getKeyChar() != 0)
	{
		selectWithKey(e.getKey());
	}
	else
	{
		Inherited::keyTyped(e);
	}
}

void ComboBox::mouseClicked(const MouseEvent& e)
{
	if(getEnabled() && !getEditable() && !getExpandButton()->isContained(e.getLocation(), true))
	{
		beginEditCP(getExpandButton(), ToggleButton::SelectedFieldMask);
			getExpandButton()->setSelected(true);
		endEditCP(getExpandButton(), ToggleButton::SelectedFieldMask);
	}
	else
	{
		Inherited::mouseClicked(e);
	}
}

void ComboBox::updateComponentGeneratorSelectedItem(void)
{
	if(!getEditable() && getCellGenerator() != NullFC && getModel() != NullFC)
	{
		beginEditCP(ComboBoxPtr(this), ComponentGeneratorSelectedItemFieldMask);
			if(getCellGenerator()->getType().isDerivedFrom(ComboBoxComponentGenerator::getClassType()))
			{
				setComponentGeneratorSelectedItem(ComboBoxComponentGenerator::Ptr::dcast(getCellGenerator())->getComboBoxComponent(ComboBoxPtr(this), getModel()->getSelectedItem(), getModel()->getSelectedItemIndex(), false, false));
			}
			else
			{
				setComponentGeneratorSelectedItem(getCellGenerator()->getComponent(ComboBoxPtr(this), getModel()->getSelectedItem(), getModel()->getSelectedItemIndex(), 0, false, false));
			}
		endEditCP(ComboBoxPtr(this), ComponentGeneratorSelectedItemFieldMask);
	}
}

void ComboBox::updateSelectionFromEditor(void)
{
    if(getEditable() && getEditor() != NullFC)
    {
        SharedFieldPtr EditorItem = getEditor()->getItem();

	    std::string EditorString;
	    std::string ModelItemString;
	    bool ExitLoop(false);
        for(UInt32 i(0) ; i<getModel()->getSize() && !ExitLoop ; ++i)
        {
            EditorItem->getValueByStr(EditorString);
            getModel()->getElementAt(i)->getValueByStr(ModelItemString);
            if(EditorString.compare(ModelItemString) == 0)
            {
                ExitLoop = true;

                getModel()->setSelectedItem(i);
            }
        }
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ComboBox::ComboBox(void) :
    Inherited(),
		_ExpandButtonSelectedListener(ComboBoxPtr(this)),
		_EditorListener(ComboBoxPtr(this))
{
	beginEditCP(ComboBoxPtr(this), ComboListPopupMenuFieldMask);
		setComboListPopupMenu(PopupMenu::create());
	endEditCP(ComboBoxPtr(this), ComboListPopupMenuFieldMask);
}

ComboBox::ComboBox(const ComboBox &source) :
    Inherited(source),
		_ExpandButtonSelectedListener(ComboBoxPtr(this)),
		_EditorListener(ComboBoxPtr(this))
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
    if(getEditor() != NullFC)
    {
        beginEditCP(ComboBoxPtr(this), EditorFieldMask);
			setEditor(ComboBoxEditor::Ptr::dcast(getEditor()->shallowCopy()));
        endEditCP(ComboBoxPtr(this), EditorFieldMask);
    }
}

ComboBox::~ComboBox(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ComboBox::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

	if( (whichField & EditableFieldMask))
	{
		updateComponentGeneratorSelectedItem();
	}

	if((whichField & ExpandButtonFieldMask) &&
		getExpandButton() != NullFC)
	{
		getExpandButton()->addButtonSelectedListener(&_ExpandButtonSelectedListener);
		getComboListPopupMenu()->addPopupMenuListener(&_ExpandButtonSelectedListener);
	}
	
    if( (whichField & ExpandButtonFieldMask) ||
        (whichField & EditorFieldMask) ||
        (whichField & EditableFieldMask) ||
        (whichField & ComponentGeneratorSelectedItemFieldMask))
    {
        beginEditCP(ComboBoxPtr(this), ChildrenFieldMask);
            getChildren().clear();
			if(getExpandButton() != NullFC)
			{
				getChildren().push_back(getExpandButton());
			}
			if(getEditable() && getEditor() != NullFC && getEditor()->getEditorComponent() != NullFC)
			{
				getChildren().push_back(getEditor()->getEditorComponent());
			}
			if(!getEditable() && getComponentGeneratorSelectedItem() != NullFC)
			{
				getChildren().push_back(getComponentGeneratorSelectedItem());
			}
        endEditCP(ComboBoxPtr(this), ChildrenFieldMask);
    }
    
    if( (whichField & EditorFieldMask) && getEditor() != NullFC)
    {
        getEditor()->addActionListener(&_EditorListener);
    }

	if(whichField & ModelFieldMask)
	{
		if(getModel() != NullFC)
		{
			getModel()->addListDataListener(this);
			getModel()->addSelectionListener(this);
			updateListFromModel();
		}
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

void ComboBox::EditorListener::actionPerformed(const ActionEvent& e)
{
    _ComboBox->updateSelectionFromEditor();
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

