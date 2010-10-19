/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)*
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

#include "OSGSearchWindow.h"

#include "OSGPanel.h"
#include "OSGFlowLayout.h"
#include "OSGSpringLayout.h"
#include "OSGSpringLayoutConstraints.h"
#include "OSGComboBox.h"
#include "OSGDefaultMutableComboBoxModel.h"


OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSearchWindowBase.cpp file.
// To modify it, please change the .fcd file (OSGSearchWindow.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SearchWindow::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

void SearchWindow::close(/*UInt32 intOption,
                         std::string searchText,
						 std::string replaceText*/)
{
    _VetoWindowClose = false;

    produceSearchWindowClosing();
    produceWindowClosing();

    if(!_VetoWindowClose && getDrawingSurface() != NULL)
    {
        getDrawingSurface()->closeWindow(SearchWindowRefPtr(this));
        produceSearchWindowClosed();
        produceWindowClosed();
    }
}

void SearchWindow::produceSearchWindowClosing(void)
{
    const SearchWindowEventUnrecPtr TheEvent = SearchWindowEvent::create(this,getSystemTime());
    for(SearchWindowListenerSetConstItor SetItor(_SearchWindowListeners.begin()) ; SetItor != _SearchWindowListeners.end() ; ++SetItor)
    {
        (*SetItor)->dialogClosing(TheEvent);
    }
    _Producer.produceEvent(SearchWindowClosingMethodId,TheEvent);
}

void SearchWindow::produceSearchWindowClosed(void)
{
    const SearchWindowEventUnrecPtr TheEvent = SearchWindowEvent::create(this,getSystemTime());
    for(SearchWindowListenerSetConstItor SetItor(_SearchWindowListeners.begin()) ; SetItor != _SearchWindowListeners.end() ; ++SetItor)
    {
        (*SetItor)->dialogClosed(TheEvent);
    }
    _Producer.produceEvent(SearchWindowClosedMethodId,TheEvent);
}


void SearchWindow::produceSearchButtonClicked(void)
{
    const SearchWindowEventUnrecPtr TheEvent = SearchWindowEvent::create(this,getSystemTime());
    for(SearchWindowListenerSetConstItor SetItor(_SearchWindowListeners.begin()) ; SetItor != _SearchWindowListeners.end() ; ++SetItor)
    {
        (*SetItor)->searchButtonClicked(TheEvent);
    }
    _Producer.produceEvent(SearchButtonClickedMethodId,TheEvent);
}

void SearchWindow::produceReplaceButtonClicked(void)
{
    const SearchWindowEventUnrecPtr TheEvent = SearchWindowEvent::create(this,getSystemTime());
    for(SearchWindowListenerSetConstItor SetItor(_SearchWindowListeners.begin()) ; SetItor != _SearchWindowListeners.end() ; ++SetItor)
    {
        (*SetItor)->replaceButtonClicked(TheEvent);
    }
    _Producer.produceEvent(ReplaceButtonClickedMethodId,TheEvent);
}

void SearchWindow::produceReplaceAllButtonClicked(void)
{
    const SearchWindowEventUnrecPtr TheEvent = SearchWindowEvent::create(this,getSystemTime());
    for(SearchWindowListenerSetConstItor SetItor(_SearchWindowListeners.begin()) ; SetItor != _SearchWindowListeners.end() ; ++SetItor)
    {
        (*SetItor)->replaceAllButtonClicked(TheEvent);
    }
    _Producer.produceEvent(ReplaceAllButtonClickedMethodId,TheEvent);
}
void SearchWindow::produceBookmarkAllButtonClicked(void)
{
    const SearchWindowEventUnrecPtr TheEvent = SearchWindowEvent::create(this,getSystemTime());
    for(SearchWindowListenerSetConstItor SetItor(_SearchWindowListeners.begin()) ; SetItor != _SearchWindowListeners.end() ; ++SetItor)
    {
        (*SetItor)->bookmarkAllButtonClicked(TheEvent);
    }
    _Producer.produceEvent(BookmarkAllButtonClickedMethodId,TheEvent);
}

EventConnection SearchWindow::addSearchWindowListener(SearchWindowListenerPtr Listener)
{
    _SearchWindowListeners.insert(Listener);
    return EventConnection(
                           boost::bind(&SearchWindow::isSearchWindowListenerAttached, this, Listener),
                           boost::bind(&SearchWindow::removeSearchWindowListener, this, Listener));
}

EventConnection SearchWindow::addEventListener(EventListenerPtr Listener)
{
    _EventListeners.insert(Listener);
    return EventConnection(
                           boost::bind(&SearchWindow::isEventListenerAttached, this, Listener),
                           boost::bind(&SearchWindow::removeEventListener, this, Listener));
}

void SearchWindow::removeEventListener(EventListenerPtr Listener)
{
    EventListenerSetItor EraseIter(_EventListeners.find(Listener));
    if(EraseIter != _EventListeners.end())
    {
        _EventListeners.erase(EraseIter);
    }
}

void SearchWindow::removeSearchWindowListener(SearchWindowListenerPtr Listener)
{
    SearchWindowListenerSetItor EraseIter(_SearchWindowListeners.find(Listener));
    if(EraseIter != _SearchWindowListeners.end())
    {
        _SearchWindowListeners.erase(EraseIter);
    }
}


SearchWindowUnrecPtr SearchWindow::createDialog(const std::string& Title,
                                                  const std::vector<std::string>& InputValues)
{
    SearchWindowRefPtr TheDialog = SearchWindow::create();
    //TheDialog->_InputType = INPUT_TEXT;

    //Icon
    /*ImageComponentRefPtr TheIcon = ImageComponent::create();
    LineBorderRefPtr TempIconBorder = LineBorder::create();
    TheIcon->setPreferredSize(Vec2f(45,45));
    TheIcon->setBorders(TempIconBorder);*/

    //Search Button
    ButtonRefPtr SearchButton = Button::create();
    SearchButton->setText("Find Next");
    SearchButton->setMinSize(SearchButton->getPreferredSize());
    SearchButton->setPreferredSize(SearchButton->getRequestedSize());
    SearchButton->addActionListener(&TheDialog->_SearchButtonListener);

	//Replace Button
    ButtonRefPtr ReplaceButton = Button::create();
    ReplaceButton->setText("Replace");
    ReplaceButton->setMinSize(ReplaceButton->getPreferredSize());
    ReplaceButton->setPreferredSize(ReplaceButton->getRequestedSize());
    ReplaceButton->addActionListener(&TheDialog->_ReplaceButtonListener);
    
	ButtonRefPtr ReplaceAllButton = Button::create();
    ReplaceAllButton->setText("Replace All");
    ReplaceAllButton->setMinSize(ReplaceAllButton->getPreferredSize());
    ReplaceAllButton->setPreferredSize(ReplaceAllButton->getRequestedSize());
    ReplaceAllButton->addActionListener(&TheDialog->_ReplaceAllButtonListener);
    
	ButtonRefPtr BookmarkAllButton = Button::create();
    BookmarkAllButton->setText("Bookmark All");
    BookmarkAllButton->setMinSize(BookmarkAllButton->getPreferredSize());
    BookmarkAllButton->setPreferredSize(BookmarkAllButton->getRequestedSize());
    BookmarkAllButton->addActionListener(&TheDialog->_BookmarkAllButtonListener);

    //Message Panel
    /*TextAreaRefPtr MessagePanelText = createTransparentTextArea(Message);*/

    // Create Panel for bottom half of SplitPanel
    PanelRefPtr MessageButtonPanel;
    MessageButtonPanel = Panel::createEmpty();
    LayoutRefPtr MessagePanelBottomLayout = FlowLayout::create();
    MessageButtonPanel->pushToChildren(SearchButton);
	MessageButtonPanel->pushToChildren(ReplaceButton);
	MessageButtonPanel->pushToChildren(ReplaceAllButton);
	MessageButtonPanel->pushToChildren(BookmarkAllButton);
    MessageButtonPanel->setLayout(MessagePanelBottomLayout);
    MessageButtonPanel->setPreferredSize(Vec2f(450,75));

	

	LabelRefPtr SearchLabel = Label::create();
    SearchLabel->setText("Search Text");
    SearchLabel->setTextColor(Color4f(0.3, 0.3, 0.3, 1.0));
    SearchLabel->setAlignment(Vec2f(0.5,0.5));
    SearchLabel->setPreferredSize(Vec2f(200, 20));
    SearchLabel->setTextSelectable(false);

	LabelRefPtr ReplaceLabel = Label::create();
    ReplaceLabel->setText("Replace Text");
    ReplaceLabel->setTextColor(Color4f(0.3, 0.3, 0.3, 1.0));
    ReplaceLabel->setAlignment(Vec2f(0.5,0.5));
    ReplaceLabel->setPreferredSize(Vec2f(200,20));
    ReplaceLabel->setTextSelectable(false);

	TheDialog->_SearchComboBoxModel = DefaultMutableComboBoxModel::create();
    TheDialog->_SearchComboBoxModel->addElement(boost::any(std::string(InputValues[0])));
    TheDialog->_SearchComboBox = ComboBox::create();
    TheDialog->_SearchComboBox->setModel(TheDialog->_SearchComboBoxModel);
    TheDialog->_SearchComboBox->setSelectedIndex(0);
	

	TheDialog->_ReplaceComboBoxModel = DefaultMutableComboBoxModel::create();
    TheDialog->_ReplaceComboBoxModel->addElement(boost::any(std::string(InputValues[1])));
    TheDialog->_ReplaceComboBox = ComboBox::create();
    TheDialog->_ReplaceComboBox->setModel(TheDialog->_ReplaceComboBoxModel);
    TheDialog->_ReplaceComboBox->setSelectedIndex(0);

	
	GridBagLayoutRefPtr CheckBoxLayout = OSG::GridBagLayout::create();
    CheckBoxLayout->setColumns(1);
    CheckBoxLayout->setRows(3);
	GridBagLayoutConstraintsRefPtr CheckBox1Constraints = OSG::GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRefPtr CheckBox2Constraints = OSG::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsRefPtr CheckBox3Constraints = OSG::GridBagLayoutConstraints::create();
    CheckBox1Constraints->setGridX(0);
    CheckBox1Constraints->setGridY(0);
	CheckBox2Constraints->setGridX(0);
    CheckBox2Constraints->setGridY(1);
	CheckBox3Constraints->setGridX(0);
    CheckBox3Constraints->setGridY(2);

	TheDialog->_MatchCaseCheckboxButton = OSG::CheckboxButton::create();
    TheDialog->_MatchCaseCheckboxButton->setMinSize(Vec2f(50, 20));
    //TheDialog->_MatchCaseCheckboxButton->setMaxSize(Vec2f(300, 100));
    TheDialog->_MatchCaseCheckboxButton->setPreferredSize(Vec2f(100, 20));
    TheDialog->_MatchCaseCheckboxButton->setEnabled(true);
    TheDialog->_MatchCaseCheckboxButton->setText("Match Case");
    TheDialog->_MatchCaseCheckboxButton->setAlignment(Vec2f(0.0,0.5));
    TheDialog->_MatchCaseCheckboxButton->setSelected(false);
	TheDialog->_MatchCaseCheckboxButton->setConstraints(CheckBox1Constraints);

	TheDialog->_MatchWholeWordCheckboxButton = OSG::CheckboxButton::create();
    TheDialog->_MatchWholeWordCheckboxButton->setMinSize(Vec2f(50, 20));
    //TheDialog->_MatchWholeWordCheckboxButton->setMaxSize(Vec2f(300, 100));
    TheDialog->_MatchWholeWordCheckboxButton->setPreferredSize(Vec2f(100, 20));
    TheDialog->_MatchWholeWordCheckboxButton->setEnabled(true);
    TheDialog->_MatchWholeWordCheckboxButton->setText("Match Whole Word");
    TheDialog->_MatchWholeWordCheckboxButton->setAlignment(Vec2f(0.0,0.5));
    TheDialog->_MatchWholeWordCheckboxButton->setSelected(false);
	TheDialog->_MatchWholeWordCheckboxButton->setConstraints(CheckBox2Constraints);

	TheDialog->_MatchUseRegExCheckboxButton = OSG::CheckboxButton::create();
    TheDialog->_MatchUseRegExCheckboxButton->setMinSize(Vec2f(50, 20));
    //TheDialog->_MatchUseRegExCheckboxButton->setMaxSize(Vec2f(300, 100));
    TheDialog->_MatchUseRegExCheckboxButton->setPreferredSize(Vec2f(100, 20));
    TheDialog->_MatchUseRegExCheckboxButton->setEnabled(true);
    TheDialog->_MatchUseRegExCheckboxButton->setText("Use Regular Expression");
    TheDialog->_MatchUseRegExCheckboxButton->setAlignment(Vec2f(0.0,0.5));
    TheDialog->_MatchUseRegExCheckboxButton->setSelected(false);
	TheDialog->_MatchUseRegExCheckboxButton->setConstraints(CheckBox3Constraints);

	PanelRefPtr CheckBoxPanel;
	CheckBoxPanel = Panel::create();
	CheckBoxPanel->pushToChildren(TheDialog->_MatchCaseCheckboxButton);
	CheckBoxPanel->pushToChildren(TheDialog->_MatchWholeWordCheckboxButton);
	CheckBoxPanel->pushToChildren(TheDialog->_MatchUseRegExCheckboxButton);
    CheckBoxPanel->setLayout(CheckBoxLayout);
    CheckBoxPanel->setPreferredSize(Vec2f(150,60));


    //Dialog Window
    SpringLayoutRefPtr DialogLayout = SpringLayout::create();
    //TheDialog->pushToChildren(MessagePanelText);
    //TheDialog->pushToChildren(TheIcon);
    TheDialog->pushToChildren(MessageButtonPanel);
	TheDialog->pushToChildren(CheckBoxPanel);
	TheDialog->pushToChildren(SearchLabel);
	TheDialog->pushToChildren(ReplaceLabel);
    TheDialog->pushToChildren(TheDialog->_SearchComboBox);
	TheDialog->pushToChildren(TheDialog->_ReplaceComboBox);
    TheDialog->setPreferredSize(Vec2f(350.0f,300.0f));
    TheDialog->setTitle(Title);
    TheDialog->setLayout(DialogLayout);


    

    //Combobox
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, TheDialog->_SearchComboBox, 10, SpringLayoutConstraints::NORTH_EDGE, TheDialog);
	DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, TheDialog->_SearchComboBox, -5, SpringLayoutConstraints::EAST_EDGE, TheDialog);
	DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TheDialog->_SearchComboBox, 5, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, TheDialog);
	DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, TheDialog->_SearchComboBox, 30, SpringLayoutConstraints::NORTH_EDGE, TheDialog);

	//Combobox
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, TheDialog->_ReplaceComboBox, 50, SpringLayoutConstraints::NORTH_EDGE, TheDialog);
	DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, TheDialog->_ReplaceComboBox, -5, SpringLayoutConstraints::EAST_EDGE, TheDialog);
	DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TheDialog->_ReplaceComboBox, 5, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, TheDialog);
	DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, TheDialog->_ReplaceComboBox, 70, SpringLayoutConstraints::NORTH_EDGE, TheDialog);

	//Label
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, SearchLabel, 10, SpringLayoutConstraints::NORTH_EDGE, TheDialog);
	DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, SearchLabel, -5, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, TheDialog);
	DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, SearchLabel, 5, SpringLayoutConstraints::WEST_EDGE, TheDialog);
	DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, SearchLabel, 30, SpringLayoutConstraints::NORTH_EDGE, TheDialog);

	//Label
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, ReplaceLabel, 50, SpringLayoutConstraints::NORTH_EDGE, TheDialog);
	DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, ReplaceLabel, -5, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, TheDialog);
	DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, ReplaceLabel, 5, SpringLayoutConstraints::WEST_EDGE, TheDialog);
	DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, ReplaceLabel, 70, SpringLayoutConstraints::NORTH_EDGE, TheDialog);

	DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, CheckBoxPanel, 90, SpringLayoutConstraints::NORTH_EDGE, TheDialog);
	DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, CheckBoxPanel, 0, SpringLayoutConstraints::EAST_EDGE, TheDialog);
	DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, CheckBoxPanel, 0, SpringLayoutConstraints::WEST_EDGE, TheDialog);
	DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, CheckBoxPanel, 170, SpringLayoutConstraints::NORTH_EDGE, TheDialog);

    //Button Panel
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, MessageButtonPanel, 190, SpringLayoutConstraints::NORTH_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MessageButtonPanel, 0, SpringLayoutConstraints::WEST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MessageButtonPanel, 0, SpringLayoutConstraints::EAST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, MessageButtonPanel, -20, SpringLayoutConstraints::SOUTH_EDGE, TheDialog);

    return TheDialog;
}



SearchWindow::SearchButtonListener::SearchButtonListener(SearchWindowRefPtr TheDialogWindow) : _DialogWindow(TheDialogWindow)
{
}

void SearchWindow::SearchButtonListener::actionPerformed(const ActionEventUnrecPtr e)
{
    //_DialogWindow->close(SearchWindowEvent::DIALOG_OPTION_SEARCH,"",0);
	_DialogWindow->searchActionPerformed(e);
}


SearchWindow::ReplaceAllButtonListener::ReplaceAllButtonListener(SearchWindowRefPtr TheDialogWindow) : _DialogWindow(TheDialogWindow)
{
}

void SearchWindow::ReplaceAllButtonListener::actionPerformed(const ActionEventUnrecPtr e)
{
    //_DialogWindow->close(SearchWindowEvent::DIALOG_OPTION_REPLACE,"",0);
	_DialogWindow->replaceAllActionPerformed(e);	
}


SearchWindow::BookmarkAllButtonListener::BookmarkAllButtonListener(SearchWindowRefPtr TheDialogWindow) : _DialogWindow(TheDialogWindow)
{
}

void SearchWindow::BookmarkAllButtonListener::actionPerformed(const ActionEventUnrecPtr e)
{
    //_DialogWindow->close(SearchWindowEvent::DIALOG_OPTION_REPLACE,"",0);
	_DialogWindow->bookmarkAllActionPerformed(e);	
}


SearchWindow::ReplaceButtonListener::ReplaceButtonListener(SearchWindowRefPtr TheDialogWindow) : _DialogWindow(TheDialogWindow)
{
}

void SearchWindow::ReplaceButtonListener::actionPerformed(const ActionEventUnrecPtr e)
{
    //_DialogWindow->close(SearchWindowEvent::DIALOG_OPTION_REPLACE,"",0);
	_DialogWindow->replaceActionPerformed(e);	
}

void SearchWindow::searchActionPerformed(const ActionEventUnrecPtr e)
{
	_SearchComboBoxModel->insertElementAt(dynamic_pointer_cast<TextField>(this->_SearchComboBox->getEditor()->getEditorComponent())->getDrawnText(),0);
	produceSearchButtonClicked();
}
void SearchWindow::replaceActionPerformed(const ActionEventUnrecPtr e)
{
	_ReplaceComboBoxModel->insertElementAt(dynamic_pointer_cast<TextField>(this->_ReplaceComboBox->getEditor()->getEditorComponent())->getDrawnText(),0);
	produceReplaceButtonClicked();
}
void SearchWindow::replaceAllActionPerformed(const ActionEventUnrecPtr e)
{
	_ReplaceComboBoxModel->insertElementAt(dynamic_pointer_cast<TextField>(this->_ReplaceComboBox->getEditor()->getEditorComponent())->getDrawnText(),0);
	produceReplaceAllButtonClicked();
}
void SearchWindow::bookmarkAllActionPerformed(const ActionEventUnrecPtr e)
{
	produceBookmarkAllButtonClicked();
	//this->_ReplaceComboBoxModel->insertElementAt(dynamic_pointer_cast<TextField>(this->_ReplaceComboBox->getEditor()->getEditorComponent())->getDrawnText(),0);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SearchWindow::SearchWindow(void) :
	_SearchButtonListener(this),
	_ReplaceButtonListener(this),
	_ReplaceAllButtonListener(this),
	_BookmarkAllButtonListener(this),
    Inherited()
{
}

SearchWindow::SearchWindow(const SearchWindow &source) :
	_SearchButtonListener(this),
	_ReplaceButtonListener(this),
	_ReplaceAllButtonListener(this),
	_BookmarkAllButtonListener(this),
    Inherited(source)
{
}

SearchWindow::~SearchWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SearchWindow::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void SearchWindow::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SearchWindow NI" << std::endl;
}

OSG_END_NAMESPACE
