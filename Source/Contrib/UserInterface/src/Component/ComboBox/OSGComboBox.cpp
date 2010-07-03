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

#include "OSGComboBox.h"
#include "OSGMutableComboBoxModel.h"
#include "OSGListGeneratedPopupMenu.h"
#include "OSGInternalWindow.h"
#include "OSGToggleButton.h"
#include "OSGComboBoxEditor.h"
#include "OSGMenuItem.h"
#include "OSGTextField.h"
#include "OSGComboBoxComponentGenerator.h"
#include "OSGUIDrawUtils.h"
#include "OSGStringUtils.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGComboBoxBase.cpp file.
// To modify it, please change the .fcd file (OSGComboBox.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ComboBox::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

EventConnection ComboBox::addPopupMenuListener(PopupMenuListenerPtr Listener)
{
    return getComboListPopupMenu()->addPopupMenuListener(Listener);
}

EventConnection ComboBox::addActionListener(ActionListenerPtr Listener)
{
    _ActionListeners.insert(Listener);
    return EventConnection(
                           boost::bind(&ComboBox::isActionListenerAttached, this, Listener),
                           boost::bind(&ComboBox::removeActionListener, this, Listener));
}

void ComboBox::setEmptyDescText(const std::string& text)
{
    if(getEditor() != NULL &&
       getEditor()->getEditorComponent() != NULL &&
       getEditor()->getEditorComponent()->getType().isDerivedFrom(TextField::getClassType()))
    {
        dynamic_cast<TextField*>(getEditor()->getEditorComponent())->setEmptyDescText(text);
    }
}

void ComboBox::updateLayout(void)
{
    Pnt2f BorderTopLeft, BorderBottomRight;
    getInsideInsetsBounds(BorderTopLeft, BorderBottomRight);

    if(getExpandButton() != NULL)
    {
        //Place the Expand button on the Left
        getExpandButton()->setSize(getExpandButton()->getPreferredSize());

        getExpandButton()->setPosition(calculateAlignment(BorderTopLeft, (BorderBottomRight-BorderTopLeft), getExpandButton()->getSize(),0.5, 1.0));
    }

    //Editor
    if(getEditable() && getEditor() != NULL && getEditor()->getEditorComponent() != NULL)
    {
        getEditor()->getEditorComponent()->setSize(Vec2f(BorderBottomRight.x() - BorderTopLeft.x() - getExpandButton()->getSize().x(), getExpandButton()->getSize().y()));
        getEditor()->getEditorComponent()->setPosition(Pnt2f(BorderTopLeft.x(), getExpandButton()->getPosition().y()));
    }

    //Selected Item Component
    if(!getEditable() && getComponentGeneratorSelectedItem() != NULL)
    {
        getComponentGeneratorSelectedItem()->setSize(Vec2f(BorderBottomRight.x() - BorderTopLeft.x() - getExpandButton()->getSize().x(), getExpandButton()->getSize().y()));
        getComponentGeneratorSelectedItem()->setPosition(Pnt2f(BorderTopLeft.x(), getExpandButton()->getPosition().y()));
    }
}

void ComboBox::actionPerformed(const ActionEventUnrecPtr e)
{
    //Called by the MenuItems in my popupMenu

    //Need to determine the index of this MenuItem
    UInt32 i(0);
    while(i<getComboListPopupMenu()->getNumItems() && 
          getComboListPopupMenu()->getItem(i) != dynamic_cast<MenuItem*>(e->getSource()))
    {
        ++i;
    }

    if(i < getComboListPopupMenu()->getNumItems())
    {
        getModel()->setSelectedItem(i);
        if(getEditable() && getEditor() != NULL && getEditor()->getEditorComponent() != NULL)
        {
            getEditor()->selectAll();
            getEditor()->getEditorComponent()->takeFocus();
        }
        if(!getEditable() && getComponentGeneratorSelectedItem() != NULL)
        {
            getComponentGeneratorSelectedItem()->takeFocus();
        }
    }
}

void ComboBox::contentsChanged(const ListDataEventUnrecPtr e)
{
    updateListFromModel();
}

void ComboBox::intervalAdded(const ListDataEventUnrecPtr e)
{
    //TODO:Implement
    updateListFromModel();
}

void ComboBox::intervalRemoved(const ListDataEventUnrecPtr e)
{
    //TODO:Implement
    updateListFromModel();
}

void ComboBox::selectionChanged(const ComboBoxSelectionEventUnrecPtr e)
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


void ComboBox::addItem(const boost::any& anObject)
{
    if(getModel() != NULL && getModel()->getType().isDerivedFrom(MutableComboBoxModel::getClassType()))
    {
        dynamic_cast<MutableComboBoxModel*>(getModel())->addElement(anObject);
    }
}

void ComboBox::configureEditor(ComboBoxEditor* const anEditor, const boost::any& anItem)
{
    //TODO:Implement
}

std::string ComboBox::getActionCommand(void) const
{
    //TODO:Implement
    return std::string("");
}

void ComboBox::insertItemAt(const boost::any& anObject, const UInt32& index)
{
    if(getModel() != NULL && getModel()->getType().isDerivedFrom(MutableComboBoxModel::getClassType()))
    {
        dynamic_cast<MutableComboBoxModel*>(getModel())->insertElementAt(anObject, index);
    }
}

void ComboBox::removeAllItems(void)
{
    if(getModel() != NULL && getModel()->getType().isDerivedFrom(MutableComboBoxModel::getClassType()))
    {
        dynamic_cast<MutableComboBoxModel*>(getModel())->removeAllElements();
    }
}

void ComboBox::removeItem(const boost::any& anObject)
{
    if(getModel() != NULL && getModel()->getType().isDerivedFrom(MutableComboBoxModel::getClassType()))
    {
        dynamic_cast<MutableComboBoxModel*>(getModel())->removeElement(anObject);
    }
}

void ComboBox::removeItemAt(const UInt32& anIndex)
{
    if(getModel() != NULL && getModel()->getType().isDerivedFrom(MutableComboBoxModel::getClassType()))
    {
        dynamic_cast<MutableComboBoxModel*>(getModel())->removeElementAt(anIndex);
    }
}

bool ComboBox::selectWithKey(KeyEvent::Key TheKey)
{
    UInt32 i(1);
    boost::any ModelElement;
    std::string TheText;

    bool ExitLoop(false);
    while(i<getModel()->getSize()  && !ExitLoop)
    {
        //Get The first character of this item
        ModelElement = getModel()->getElementAt((getModel()->getSelectedItemIndex() + i) % getModel()->getSize());

        try
        {
            TheText = lexical_cast(ModelElement);
        }
        catch (boost::bad_lexical_cast &)
        {
            //Could not convert to string
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

    getComboListPopupMenu()->setInvoker(this);
    getComboListPopupMenu()->setVisible(true);
    getComboListPopupMenu()->setPosition(ComponentToFrame(BorderTopLeft + Vec2f(0,BorderBottomRight.y()), this));
    getComboListPopupMenu()->setSelection(getModel()->getSelectedItemIndex());

    getParentWindow()->pushToActivePopupMenus(getComboListPopupMenu());
}

void ComboBox::updateListFromModel(void)
{
    //Update the PopupMenu
    //for(UInt32 i(0) ; i<getComboListPopupMenu()->getNumItems() ; ++i)
    //{
    //	dynamic_pointer_cast<MenuItem>(getComboListPopupMenu()->getItem(i))->removeActionListener(this);
    //}

    //Update the Selected Item Component
    updateSelectedItemComponent();
}

void ComboBox::updateSelectedItemComponent(void)
{
    //Update the Editor
    if(getEditable() && getEditor() != NULL && getModel()->getSelectedItemIndex() >=0 )
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

void ComboBox::produceActionPerformed(const ActionEventUnrecPtr e)
{
    ActionListenerSet Liseners(_ActionListeners);
    for(ActionListenerSetConstItor SetItor(Liseners.begin()) ; SetItor != Liseners.end() ; ++SetItor)
    {
        (*SetItor)->actionPerformed(e);
    }
    _Producer.produceEvent(ActionPerformedMethodId,e);
}

void ComboBox::keyTyped(const KeyEventUnrecPtr e)
{
    if(e->getKey() == KeyEvent::KEY_UP)
    {
        if(getModel()->getSelectedItemIndex() > 0)
        {
            getModel()->setSelectedItem(getModel()->getSelectedItemIndex() - 1);
        }
    }
    else if(e->getKey() == KeyEvent::KEY_DOWN)
    {
        if(getModel()->getSelectedItemIndex() < getModel()->getSize()-1)
        {
            getModel()->setSelectedItem(getModel()->getSelectedItemIndex() + 1);
        }
    }
    else if(!getEditable() && e->getKeyChar() != 0)
    {
        selectWithKey(static_cast<KeyEvent::Key>(e->getKey()));
    }
    else
    {
        Inherited::keyTyped(e);
    }
}

void ComboBox::mouseClicked(const MouseEventUnrecPtr e)
{
    if(getEnabled() && !getEditable() && !getExpandButton()->isContained(e->getLocation(), true))
    {
        getExpandButton()->setSelected(true);
    }
    else
    {
        Inherited::mouseClicked(e);
    }
}

void ComboBox::updateComponentGeneratorSelectedItem(void)
{
    if(!getEditable() && getCellGenerator() != NULL && getModel() != NULL)
    {
        if(getCellGenerator()->getType().isDerivedFrom(ComboBoxComponentGenerator::getClassType()))
        {
            ComponentUnrecPtr GeneratedComp(dynamic_cast<ComboBoxComponentGenerator*>(getCellGenerator())->getComboBoxComponent(this, getModel()->getSelectedItem(), getModel()->getSelectedItemIndex(), false, false));
            setComponentGeneratorSelectedItem(GeneratedComp);
        }
        else
        {
            ComponentUnrecPtr GeneratedComp(getCellGenerator()->getComponent(this, getModel()->getSelectedItem(), getModel()->getSelectedItemIndex(), 0, false, false));
            setComponentGeneratorSelectedItem(GeneratedComp);
        }
    }
}

void ComboBox::updateSelectionFromEditor(void)
{
    if(getEditable() && getEditor() != NULL)
    {
        const boost::any& EditorItem = getEditor()->getItem();

        std::string EditorString;
        std::string ModelItemString;
        bool ExitLoop(false);
        for(UInt32 i(0) ; i<getModel()->getSize() && !ExitLoop ; ++i)
        {
            try
            {
                EditorString = lexical_cast(EditorItem);
                ModelItemString = lexical_cast(getModel()->getElementAt(i));
            }
            catch (boost::bad_lexical_cast &)
            {
                //Could not convert to string
            }
            if(EditorString.compare(ModelItemString) == 0)
            {
                ExitLoop = true;

                getModel()->setSelectedItem(i);
            }
        }
    }
}

void ComboBox::attachMenuItems(void)
{
    for(UInt32 i(0) ; i<getComboListPopupMenu()->getNumItems() ; ++i)
    {
        getComboListPopupMenu()->getItem(i)->addActionListener(this);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void ComboBox::onCreate(const ComboBox * Id)
{
	Inherited::onCreate(Id);
    
    ListGeneratedPopupMenuUnrecPtr TheMenu(ListGeneratedPopupMenu::create());
    setComboListPopupMenu(TheMenu);
	
    if(Id != NULL)
    {
        if(Id->getExpandButton() != NULL)
        {
            FieldContainerUnrecPtr FCCopy(Id->getExpandButton()->shallowCopy());
            setExpandButton(dynamic_pointer_cast<ToggleButton>(FCCopy));
        }
        if(Id->getEditor() != NULL)
        {
            FieldContainerUnrecPtr FCCopy(Id->getEditor()->shallowCopy());
            setEditor(dynamic_pointer_cast<ComboBoxEditor>(FCCopy));
        }
    }
}

void ComboBox::onDestroy()
{
}

/*----------------------- constructors & destructors ----------------------*/

ComboBox::ComboBox(void) :
    Inherited(),
		_ExpandButtonSelectedListener(this),
		_EditorListener(this)
{
}

ComboBox::ComboBox(const ComboBox &source) :
    Inherited(source),
		_ExpandButtonSelectedListener(this),
		_EditorListener(this)
{
}

ComboBox::~ComboBox(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ComboBox::changed(ConstFieldMaskArg whichField, 
                       UInt32            origin,
                       BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if( (whichField & EditableFieldMask))
    {
        updateComponentGeneratorSelectedItem();
    }

    if((whichField & ExpandButtonFieldMask) &&
       getExpandButton() != NULL)
    {
        getExpandButton()->addButtonSelectedListener(&_ExpandButtonSelectedListener);
        getComboListPopupMenu()->addPopupMenuListener(&_ExpandButtonSelectedListener);
    }

    if( (whichField & ExpandButtonFieldMask) ||
        (whichField & EditorFieldMask) ||
        (whichField & EditableFieldMask) ||
        (whichField & ComponentGeneratorSelectedItemFieldMask))
    {
        clearChildren();
        if(getExpandButton() != NULL)
        {
            getExpandButton()->setEnabled(getEnabled());
            pushToChildren(getExpandButton());
        }
        if(getEditable() && getEditor() != NULL && getEditor()->getEditorComponent() != NULL)
        {
            getEditor()->getEditorComponent()->setEnabled(getEnabled());
            pushToChildren(getEditor()->getEditorComponent());
        }
        if(!getEditable() && getComponentGeneratorSelectedItem() != NULL)
        {
            getComponentGeneratorSelectedItem()->setEnabled(getEnabled());
            pushToChildren(getComponentGeneratorSelectedItem());
        }
    }

    if( (whichField & EditorFieldMask) && getEditor() != NULL)
    {
        getEditor()->addActionListener(&_EditorListener);
    }

    if(whichField & ModelFieldMask)
    {
        if(getModel() != NULL)
        {
            getComboListPopupMenu()->setModel(getModel());

            getModel()->addListDataListener(this);
            getModel()->addSelectionListener(this);
            updateListFromModel();
        }
    }

    if(((whichField & CellGeneratorFieldMask) ||
        (whichField & ComboListPopupMenuFieldMask)) &&
       getCellGenerator() != NULL)
    {
        getComboListPopupMenu()->setCellGenerator(getCellGenerator());
    }
}

void ComboBox::dump(      UInt32    ,
                          const BitVector ) const
{
    SLOG << "Dump ComboBox NI" << std::endl;
}

void ComboBox::ExpandButtonSelectedListener::buttonSelected(const ButtonSelectedEventUnrecPtr e)
{
    _ComboBox->setPopupVisible(true);
}

void ComboBox::ExpandButtonSelectedListener::buttonDeselected(const ButtonSelectedEventUnrecPtr e)
{
    _ComboBox->setPopupVisible(false);
}

void ComboBox::ExpandButtonSelectedListener::popupMenuCanceled(const PopupMenuEventUnrecPtr e)
{
    if(_ComboBox->getExpandButton()->getSelected())
    {
        _ComboBox->getExpandButton()->setSelected(false);
    }
}

void ComboBox::ExpandButtonSelectedListener::popupMenuWillBecomeInvisible(const PopupMenuEventUnrecPtr e)
{
    if(_ComboBox->getExpandButton()->getSelected())
    {
        _ComboBox->getExpandButton()->setSelected(false);
    }
}
void ComboBox::ExpandButtonSelectedListener::popupMenuWillBecomeVisible(const PopupMenuEventUnrecPtr e)
{
    if(!_ComboBox->getExpandButton()->getSelected())
    {
        _ComboBox->getExpandButton()->setSelected(true);
    }
}

void ComboBox::ExpandButtonSelectedListener::popupMenuContentsChanged(const PopupMenuEventUnrecPtr e)
{
    _ComboBox->attachMenuItems();
}

void ComboBox::EditorListener::actionPerformed(const ActionEventUnrecPtr e)
{
    _ComboBox->updateSelectionFromEditor();
}

OSG_END_NAMESPACE
