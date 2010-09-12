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

    Vec2f Size;
    Pnt2f Pos;
    if(getExpandButton() != NULL)
    {
        //Place the Expand button on the Left
        Size = getExpandButton()->getPreferredSize();
        if(getExpandButton()->getSize() != Size)
        {
            getExpandButton()->setSize(Size);
        }

        Pos = calculateAlignment(BorderTopLeft, (BorderBottomRight-BorderTopLeft), getExpandButton()->getSize(),0.5, 1.0);
        if(getExpandButton()->getPosition() != Pos)
        {
            getExpandButton()->setPosition(Pos);
        }
    }

    //Editor
    if(getEditable() && getEditor() != NULL && getEditor()->getEditorComponent() != NULL)
    {
        Size = Vec2f(BorderBottomRight.x() - BorderTopLeft.x() - getExpandButton()->getSize().x(), getExpandButton()->getSize().y());
        if(getEditor()->getEditorComponent()->getSize() != Size)
        {
            getEditor()->getEditorComponent()->setSize(Size);
        }
        Pos = Pnt2f(BorderTopLeft.x(), getExpandButton()->getPosition().y());
        if(getEditor()->getEditorComponent()->getPosition() != Pos)
        {
            getEditor()->getEditorComponent()->setPosition(Pos);
        }
    }

    //Selected Item Component
    if(!getEditable() && getComponentGeneratorSelectedItem() != NULL)
    {
        Size = Vec2f(BorderBottomRight.x() - BorderTopLeft.x() - getExpandButton()->getSize().x(), getExpandButton()->getSize().y());
        if(getComponentGeneratorSelectedItem()->getSize() != Size)
        {
            getComponentGeneratorSelectedItem()->setSize(Size);
        }
        Pos = Pnt2f(BorderTopLeft.x(), getExpandButton()->getPosition().y());
        if(getComponentGeneratorSelectedItem()->getPosition() != Pos)
        {
            getComponentGeneratorSelectedItem()->setPosition(Pos);
        }
    }
}

void ComboBox::handleMenuItemActionPerformed(ActionEventDetails* const e)
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

void ComboBox::handleContentsChanged(ListDataEventDetails* const e)
{
    updateListFromModel();
}

void ComboBox::handleContentsIntervalAdded(ListDataEventDetails* const e)
{
    //TODO:Implement
    updateListFromModel();
}

void ComboBox::handleContentsIntervalRemoved(ListDataEventDetails* const e)
{
    //TODO:Implement
    updateListFromModel();
}

void ComboBox::handleSelectionChanged(ComboBoxSelectionEventDetails* const e)
{
    //Update the Selected Item Component
    updateSelectedItemComponent();
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

bool ComboBox::selectWithKey(KeyEventDetails::Key TheKey)
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
           (TheText[0] == KeyEventDetails::getCharFromKey(TheKey, 0) ||
            TheText[0] == KeyEventDetails::getCharFromKey(TheKey, KeyEventDetails::KEY_MODIFIER_CAPS_LOCK)))
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

void ComboBox::produceActionPerformed(void)
{
    ActionEventDetailsUnrecPtr Details = ActionEventDetails::create(this, getTimeStamp());

    Inherited::produceActionPerformed(Details);
}

void ComboBox::keyTyped(KeyEventDetails* const e)
{
    if(e->getKey() == KeyEventDetails::KEY_UP)
    {
        if(getModel()->getSelectedItemIndex() > 0)
        {
            getModel()->setSelectedItem(getModel()->getSelectedItemIndex() - 1);
        }
    }
    else if(e->getKey() == KeyEventDetails::KEY_DOWN)
    {
        if(getModel()->getSelectedItemIndex() < getModel()->getSize()-1)
        {
            getModel()->setSelectedItem(getModel()->getSelectedItemIndex() + 1);
        }
    }
    else if(!getEditable() && e->getKeyChar() != 0)
    {
        selectWithKey(static_cast<KeyEventDetails::Key>(e->getKey()));
    }
    else
    {
        Inherited::keyTyped(e);
    }
}

void ComboBox::mouseClicked(MouseEventDetails* const e)
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
    for(UInt32 i(0) ; i<_MenuItemActionConnections.size() ; ++i)
    {
        _MenuItemActionConnections[i].disconnect();
    }
    _MenuItemActionConnections.clear();

    for(UInt32 i(0) ; i<getComboListPopupMenu()->getNumItems() ; ++i)
    {
        _MenuItemActionConnections.push_back(getComboListPopupMenu()->getItem(i)->connectActionPerformed(boost::bind(&ComboBox::handleMenuItemActionPerformed, this, _1)));
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
    Inherited()
{
}

ComboBox::ComboBox(const ComboBox &source) :
    Inherited(source)
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
        _ExpandButtonSelectedConnection = getExpandButton()->connectButtonSelected(boost::bind(&ComboBox::handleExpandButtonSelected, this, _1));
        _ExpandButtonDeselectedConnection = getExpandButton()->connectButtonDeselected(boost::bind(&ComboBox::handleExpandButtonDeselected, this, _1));
        
        _ExpandPopupMenuCanceledConnection = getComboListPopupMenu()->connectPopupMenuCanceled(boost::bind(&ComboBox::handleExpandPopupMenuCanceled, this, _1));
        _ExpandPopupMenuWillBecomeInvisibleConnection = getComboListPopupMenu()->connectPopupMenuWillBecomeInvisible(boost::bind(&ComboBox::handleExpandPopupMenuWillBecomeInvisible, this, _1));
        _ExpandPopupMenuWillBecomeVisibleConnection = getComboListPopupMenu()->connectPopupMenuWillBecomeVisible(boost::bind(&ComboBox::handleExpandPopupMenuWillBecomeVisible, this, _1));
        _ExpandPopupMenuContentsChangedConnection = getComboListPopupMenu()->connectPopupMenuContentsChanged(boost::bind(&ComboBox::handleExpandPopupMenuContentsChanged, this, _1));
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
        _EditorActionConnection = getEditor()->connectActionPerformed(boost::bind(&ComboBox::handleEditorAction, this, _1));
    }

    if(whichField & ModelFieldMask)
    {
        if(getModel() != NULL)
        {
            getComboListPopupMenu()->setModel(getModel());

            _ContentsChangedConnection = getModel()->connectListDataContentsChanged(boost::bind(&ComboBox::handleContentsChanged, this, _1));
            _ContentsIntervalAddedConnection = getModel()->connectListDataIntervalAdded(boost::bind(&ComboBox::handleContentsIntervalAdded, this, _1));
            _ContentsIntervalRemovedConnection = getModel()->connectListDataIntervalRemoved(boost::bind(&ComboBox::handleContentsIntervalRemoved, this, _1));
            _SelectionChangedConnection = getModel()->connectSelectionChanged(boost::bind(&ComboBox::handleSelectionChanged, this, _1));
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

void ComboBox::handleExpandButtonSelected(ButtonSelectedEventDetails* const e)
{
    setPopupVisible(true);
}

void ComboBox::handleExpandButtonDeselected(ButtonSelectedEventDetails* const e)
{
    setPopupVisible(false);
}

void ComboBox::handleExpandPopupMenuCanceled(PopupMenuEventDetails* const e)
{
    if(getExpandButton()->getSelected())
    {
        getExpandButton()->setSelected(false);
    }
}

void ComboBox::handleExpandPopupMenuWillBecomeInvisible(PopupMenuEventDetails* const e)
{
    if(getExpandButton()->getSelected())
    {
        getExpandButton()->setSelected(false);
    }
}
void ComboBox::handleExpandPopupMenuWillBecomeVisible(PopupMenuEventDetails* const e)
{
    if(!getExpandButton()->getSelected())
    {
        getExpandButton()->setSelected(true);
    }
}

void ComboBox::handleExpandPopupMenuContentsChanged(PopupMenuEventDetails* const e)
{
    attachMenuItems();
}

void ComboBox::handleEditorAction(ActionEventDetails* const e)
{
    updateSelectionFromEditor();
}

OSG_END_NAMESPACE
