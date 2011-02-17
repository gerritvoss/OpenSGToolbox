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

#include "OSGDocument.h"
//#include "OSGSearchWindowListener.h"
#include "OSGTextArea.h"
#include "OSGButton.h"
#include "OSGTextField.h"
#include "OSGGridBagLayout.h"
#include "OSGGridBagLayoutConstraints.h"
#include "OSGPanel.h"
#include "OSGFlowLayout.h"
#include "OSGSpringLayout.h"
#include "OSGSpringLayoutConstraints.h"

#include "OSGDefaultMutableComboBoxModel.h"
#include "OSGComboBox.h"
#include "OSGCheckboxButton.h"

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

SearchWindowTransitPtr SearchWindow::create(const std::string& WindowTitle)
{
    SearchWindowRefPtr CreatedWindow = SearchWindowBase::create();
	
    //Search Button
    ButtonRefPtr SearchButton = Button::create();
    SearchButton->setText("Find Next");
    SearchButton->setMinSize(SearchButton->getPreferredSize());
    SearchButton->setPreferredSize(SearchButton->getRequestedSize());
	CreatedWindow->_SearchButtonActionConnection = SearchButton->connectActionPerformed(boost::bind(&SearchWindow::handleSearchButtonAction, CreatedWindow, _1));
    //SearchButton->addActionListener(&CreatedWindow->_SearchButtonListener);

	//Replace Button
    ButtonRefPtr ReplaceButton = Button::create();
    ReplaceButton->setText("Replace");
    ReplaceButton->setMinSize(ReplaceButton->getPreferredSize());
    ReplaceButton->setPreferredSize(ReplaceButton->getRequestedSize());
	CreatedWindow->_ReplaceButtonActionConnection = ReplaceButton->connectActionPerformed(boost::bind(&SearchWindow::handleReplaceButtonAction, CreatedWindow, _1));
    //ReplaceButton->addActionListener(&CreatedWindow->_ReplaceButtonListener);
    
	ButtonRefPtr ReplaceAllButton = Button::create();
    ReplaceAllButton->setText("Replace All");
    ReplaceAllButton->setMinSize(ReplaceAllButton->getPreferredSize());
    ReplaceAllButton->setPreferredSize(ReplaceAllButton->getRequestedSize());
	CreatedWindow->_ReplaceAllButtonActionConnection = ReplaceAllButton->connectActionPerformed(boost::bind(&SearchWindow::handleReplaceAllButtonAction, CreatedWindow, _1));
    //ReplaceAllButton->addActionListener(&CreatedWindow->_ReplaceAllButtonListener);
    
	ButtonRefPtr BookmarkAllButton = Button::create();
    BookmarkAllButton->setText("Bookmark All");
    BookmarkAllButton->setMinSize(BookmarkAllButton->getPreferredSize());
    BookmarkAllButton->setPreferredSize(BookmarkAllButton->getRequestedSize());
	CreatedWindow->_BookmarkAllButtonActionConnection = BookmarkAllButton->connectActionPerformed(boost::bind(&SearchWindow::handleBookmarkAllButtonAction, CreatedWindow, _1));
    //BookmarkAllButton->addActionListener(&CreatedWindow->_BookmarkAllButtonListener);

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

	CreatedWindow->_SearchComboBoxModel = DefaultMutableComboBoxModel::create();
//    CreatedWindow->_SearchComboBoxModel->addElement(boost::any(std::string(InputValues[0])));
    CreatedWindow->_SearchComboBox = ComboBox::create();
    CreatedWindow->_SearchComboBox->setModel(CreatedWindow->_SearchComboBoxModel);
    CreatedWindow->_SearchComboBox->setSelectedIndex(0);
	

	CreatedWindow->_ReplaceComboBoxModel = DefaultMutableComboBoxModel::create();
    //CreatedWindow->_ReplaceComboBoxModel->addElement(boost::any(std::string(InputValues[1])));
    CreatedWindow->_ReplaceComboBox = ComboBox::create();
    CreatedWindow->_ReplaceComboBox->setModel(CreatedWindow->_ReplaceComboBoxModel);
    CreatedWindow->_ReplaceComboBox->setSelectedIndex(0);

	
	GridBagLayoutRefPtr CheckBoxLayout = OSG::GridBagLayout::create();
    CheckBoxLayout->setColumns(1);
    CheckBoxLayout->setRows(5);
	GridBagLayoutConstraintsRefPtr CheckBox1Constraints = OSG::GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRefPtr CheckBox2Constraints = OSG::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsRefPtr CheckBox3Constraints = OSG::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsRefPtr CheckBox4Constraints = OSG::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsRefPtr CheckBox5Constraints = OSG::GridBagLayoutConstraints::create();
    CheckBox1Constraints->setGridX(0);
    CheckBox1Constraints->setGridY(0);
	CheckBox2Constraints->setGridX(0);
    CheckBox2Constraints->setGridY(1);
	CheckBox3Constraints->setGridX(0);
    CheckBox3Constraints->setGridY(2);
	CheckBox4Constraints->setGridX(0);
    CheckBox4Constraints->setGridY(3);
	CheckBox5Constraints->setGridX(0);
    CheckBox5Constraints->setGridY(4);

	CreatedWindow->_MatchCaseCheckboxButton = OSG::CheckboxButton::create();
    CreatedWindow->_MatchCaseCheckboxButton->setMinSize(Vec2f(50, 20));
    CreatedWindow->_MatchCaseCheckboxButton->setPreferredSize(Vec2f(100, 20));
    CreatedWindow->_MatchCaseCheckboxButton->setEnabled(true);
    CreatedWindow->_MatchCaseCheckboxButton->setText("Match Case");
    CreatedWindow->_MatchCaseCheckboxButton->setAlignment(Vec2f(0.0,0.5));
    CreatedWindow->_MatchCaseCheckboxButton->setSelected(false);
	CreatedWindow->_MatchCaseCheckboxButton->setConstraints(CheckBox1Constraints);

	CreatedWindow->_MatchWholeWordCheckboxButton = OSG::CheckboxButton::create();
    CreatedWindow->_MatchWholeWordCheckboxButton->setMinSize(Vec2f(50, 20));
    CreatedWindow->_MatchWholeWordCheckboxButton->setPreferredSize(Vec2f(100, 20));
    CreatedWindow->_MatchWholeWordCheckboxButton->setEnabled(true);
    CreatedWindow->_MatchWholeWordCheckboxButton->setText("Match Whole Word");
    CreatedWindow->_MatchWholeWordCheckboxButton->setAlignment(Vec2f(0.0,0.5));
    CreatedWindow->_MatchWholeWordCheckboxButton->setSelected(false);
	CreatedWindow->_MatchWholeWordCheckboxButton->setConstraints(CheckBox2Constraints);

	CreatedWindow->_MatchUseRegExCheckboxButton = OSG::CheckboxButton::create();
    CreatedWindow->_MatchUseRegExCheckboxButton->setMinSize(Vec2f(50, 20));
    CreatedWindow->_MatchUseRegExCheckboxButton->setPreferredSize(Vec2f(100, 20));
    CreatedWindow->_MatchUseRegExCheckboxButton->setEnabled(true);
    CreatedWindow->_MatchUseRegExCheckboxButton->setText("Use Regular Expression");
    CreatedWindow->_MatchUseRegExCheckboxButton->setAlignment(Vec2f(0.0,0.5));
    CreatedWindow->_MatchUseRegExCheckboxButton->setSelected(false);
	CreatedWindow->_MatchUseRegExCheckboxButton->setConstraints(CheckBox3Constraints);

	CreatedWindow->_SearchUpCheckboxButton = OSG::CheckboxButton::create();
    CreatedWindow->_SearchUpCheckboxButton->setMinSize(Vec2f(50, 20));
    CreatedWindow->_SearchUpCheckboxButton->setPreferredSize(Vec2f(100, 20));
    CreatedWindow->_SearchUpCheckboxButton->setEnabled(true);
    CreatedWindow->_SearchUpCheckboxButton->setText("Search Up");
    CreatedWindow->_SearchUpCheckboxButton->setAlignment(Vec2f(0.0,0.5));
    CreatedWindow->_SearchUpCheckboxButton->setSelected(false);
	CreatedWindow->_SearchUpCheckboxButton->setConstraints(CheckBox4Constraints);

	CreatedWindow->_WrapAroundCheckboxButton = OSG::CheckboxButton::create();
    CreatedWindow->_WrapAroundCheckboxButton->setMinSize(Vec2f(50, 20));
    CreatedWindow->_WrapAroundCheckboxButton->setPreferredSize(Vec2f(100, 20));
    CreatedWindow->_WrapAroundCheckboxButton->setEnabled(true);
    CreatedWindow->_WrapAroundCheckboxButton->setText("Wrap Around");
    CreatedWindow->_WrapAroundCheckboxButton->setAlignment(Vec2f(0.0,0.5));
    CreatedWindow->_WrapAroundCheckboxButton->setSelected(false);
	CreatedWindow->_WrapAroundCheckboxButton->setConstraints(CheckBox5Constraints);

	PanelRefPtr CheckBoxPanel;
	CheckBoxPanel = Panel::create();
	CheckBoxPanel->pushToChildren(CreatedWindow->_MatchCaseCheckboxButton);
	CheckBoxPanel->pushToChildren(CreatedWindow->_MatchWholeWordCheckboxButton);
	CheckBoxPanel->pushToChildren(CreatedWindow->_MatchUseRegExCheckboxButton);
	CheckBoxPanel->pushToChildren(CreatedWindow->_SearchUpCheckboxButton);
	CheckBoxPanel->pushToChildren(CreatedWindow->_WrapAroundCheckboxButton);
    CheckBoxPanel->setLayout(CheckBoxLayout);
    CheckBoxPanel->setPreferredSize(Vec2f(150,100));


    //Dialog Window
    SpringLayoutRefPtr DialogLayout = SpringLayout::create();
    CreatedWindow->pushToChildren(MessageButtonPanel);
	CreatedWindow->pushToChildren(CheckBoxPanel);
	CreatedWindow->pushToChildren(SearchLabel);
	CreatedWindow->pushToChildren(ReplaceLabel);
    CreatedWindow->pushToChildren(CreatedWindow->_SearchComboBox);
	CreatedWindow->pushToChildren(CreatedWindow->_ReplaceComboBox);
    CreatedWindow->setPreferredSize(Vec2f(350.0f,340.0f));
    CreatedWindow->setTitle(WindowTitle);
    CreatedWindow->setLayout(DialogLayout);


    

    //Combobox
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, CreatedWindow->_SearchComboBox, 10, SpringLayoutConstraints::NORTH_EDGE, CreatedWindow);
	DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, CreatedWindow->_SearchComboBox, -5, SpringLayoutConstraints::EAST_EDGE, CreatedWindow);
	DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, CreatedWindow->_SearchComboBox, 5, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, CreatedWindow);
	DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, CreatedWindow->_SearchComboBox, 30, SpringLayoutConstraints::NORTH_EDGE, CreatedWindow);

	//Combobox
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, CreatedWindow->_ReplaceComboBox, 50, SpringLayoutConstraints::NORTH_EDGE, CreatedWindow);
	DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, CreatedWindow->_ReplaceComboBox, -5, SpringLayoutConstraints::EAST_EDGE, CreatedWindow);
	DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, CreatedWindow->_ReplaceComboBox, 5, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, CreatedWindow);
	DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, CreatedWindow->_ReplaceComboBox, 70, SpringLayoutConstraints::NORTH_EDGE, CreatedWindow);

	//Label
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, SearchLabel, 10, SpringLayoutConstraints::NORTH_EDGE, CreatedWindow);
	DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, SearchLabel, -5, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, CreatedWindow);
	DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, SearchLabel, 5, SpringLayoutConstraints::WEST_EDGE, CreatedWindow);
	DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, SearchLabel, 30, SpringLayoutConstraints::NORTH_EDGE, CreatedWindow);

	//Label
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, ReplaceLabel, 50, SpringLayoutConstraints::NORTH_EDGE, CreatedWindow);
	DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, ReplaceLabel, -5, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, CreatedWindow);
	DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, ReplaceLabel, 5, SpringLayoutConstraints::WEST_EDGE, CreatedWindow);
	DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, ReplaceLabel, 70, SpringLayoutConstraints::NORTH_EDGE, CreatedWindow);

	DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, CheckBoxPanel, 90, SpringLayoutConstraints::NORTH_EDGE, CreatedWindow);
	DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, CheckBoxPanel, 0, SpringLayoutConstraints::EAST_EDGE, CreatedWindow);
	DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, CheckBoxPanel, 0, SpringLayoutConstraints::WEST_EDGE, CreatedWindow);
	DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, CheckBoxPanel, 210, SpringLayoutConstraints::NORTH_EDGE, CreatedWindow);

    //Button Panel
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, MessageButtonPanel, 230, SpringLayoutConstraints::NORTH_EDGE, CreatedWindow);
    DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MessageButtonPanel, 0, SpringLayoutConstraints::WEST_EDGE, CreatedWindow);
    DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MessageButtonPanel, 0, SpringLayoutConstraints::EAST_EDGE, CreatedWindow);
    DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, MessageButtonPanel, -20, SpringLayoutConstraints::SOUTH_EDGE, CreatedWindow);


    return SearchWindowTransitPtr(CreatedWindow);
}

void SearchWindow::handleSearchButtonAction(ActionEventDetails* const details)
{
	std::cout<<"search";
	SearchWindowEventDetailsUnrecPtr SearchEventDetails(SearchWindowEventDetails::create(this, getTimeStamp()));
	produceSearchButtonClicked(SearchEventDetails);
}

void SearchWindow::handleReplaceButtonAction(ActionEventDetails* const details)
{
	std::cout<<"replace";
	SearchWindowEventDetailsUnrecPtr ReplaceEventDetails(SearchWindowEventDetails::create(this, getTimeStamp()));
	produceReplaceButtonClicked(ReplaceEventDetails);
}

void SearchWindow::handleReplaceAllButtonAction(ActionEventDetails* const details)
{
	std::cout<<"replaceall";
	SearchWindowEventDetailsUnrecPtr ReplaceAllEventDetails(SearchWindowEventDetails::create(this, getTimeStamp()));
	produceReplaceAllButtonClicked(ReplaceAllEventDetails);
}

void SearchWindow::handleBookmarkAllButtonAction(ActionEventDetails* const details)
{
	std::cout<<"bookmarkall";
	SearchWindowEventDetailsUnrecPtr BookmarkAllEventDetails(SearchWindowEventDetails::create(this, getTimeStamp()));
	produceBookmarkAllButtonClicked(BookmarkAllEventDetails);
}
	
/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SearchWindow::SearchWindow(void) :
    Inherited()
{
}

SearchWindow::SearchWindow(const SearchWindow &source) :
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
