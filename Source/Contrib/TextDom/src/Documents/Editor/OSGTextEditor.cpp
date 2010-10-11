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

//#define OSG_COMPILECONTRIBTEXTDOMLIB

#include <OSGConfig.h>

#include "OSGTextEditor.h"

#include "OSGDocument.h"
#include "OSGAdvancedTextDomArea.h"
#include "OSGUIDrawingSurface.h"
#include "OSGSearchWindow.h"
#include "OSGList.h"
#include "OSGDefaultListModel.h"
#include "OSGScrollPanel.h"
#include "OSGSplitPanel.h"
#include "OSGTabPanel.h"
#include "OSGTextArea.h"
#include "OSGTextDomArea.h"
#include "OSGSpringLayout.h"
#include "OSGSpringLayoutConstraints.h"
#include "OSGBorderLayout.h"
#include "OSGBorderLayoutConstraints.h"
#include "OSGDefaultListSelectionModel.h"
#include "OSGTextDomLayoutManager.h"
#include "OSGTextDomArea.h"
#include "OSGGlyphView.h"

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/algorithm/string.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTextEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGTextEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TextEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/



void TextEditor::keyTyped(KeyEventDetails* const details)
{
	if(details->getModifiers() & KeyEventDetails::KEY_MODIFIER_CONTROL)
	{
		switch(details->getKey())
        {
        case KeyEventDetails::KEY_F:
			if(_SearchDialog == NULL)
			{
				_SearchDialog = SearchWindow::create("Search Window");
				_SearchDialog->setIconable(false);
				_SearchDialog->setAllwaysOnTop(true);
                _SearchButtonClickedConnection = _SearchDialog->connectSearchButtonClicked(boost::bind(&TextEditor::handleSearchButtonClicked, this, _1));
                _ReplaceButtonClickedConnection = _SearchDialog->connectReplaceButtonClicked(boost::bind(&TextEditor::handleReplaceButtonClicked, this, _1));
                _ReplaceAllButtonClickedConnection = _SearchDialog->connectReplaceAllButtonClicked(boost::bind(&TextEditor::handleReplaceAllButtonClicked, this, _1));
                _BookmarkAllButtonClickedConnection = _SearchDialog->connectBookmarkAllButtonClicked(boost::bind(&TextEditor::handleBookmarkAllButtonClicked, this, _1));

				_SearchDialog->setPosition(getParentWindow()->getPosition());
				getParentWindow()->getParentDrawingSurface()->openWindow(_SearchDialog);
			}

			if(!_SearchDialog->isOpen())
			{
				getParentWindow()->getParentDrawingSurface()->openWindow(_SearchDialog);
			}
			else
			{
				//getParentWindow()->setFocused(false);
				//_SearchDialog->setFocused(true);
				//_SearchDialog->takeFocus();
				//getParentWindow()->giveFocus(_SearchDialog);
			}
            break;
        case KeyEventDetails::KEY_C:
			std::string theClipboard = getParentWindow()->getParentDrawingSurface()->getEventProducer()->getClipboard();
			_TheClipboardListModel->pushBack(boost::any(theClipboard));
            break;
		}
	}
}

void TextEditor::mouseClicked(MouseEventDetails* const details)
{

	if(getParentWindow()->getFocusedComponent()->getType().isDerivedFrom(TextDomArea::getClassType()))
	{
		setFocusedDomArea(dynamic_cast<TextDomArea*>(this->getParentWindow()->getFocusedComponent()));
	}

    //TODO: Move this into the a mouseClicked handler connected directly to the list
    if(details->getButton() == MouseEventDetails::BUTTON1)
	{
		if(details->getClickCount() >= 2)
		{
			if(_TheClipboardList->isContained(details->getLocation(), true))
			{
				std::string stringToBeInserted = boost::any_cast<std::string>(_TheClipboardList->getSelectedItem());
			}
		}
		if(_TheClipboardList->isContained(details->getLocation(), true))
		{
		}
	}
	Inherited::mouseClicked(details);
}

void TextEditor::handleSearchButtonClicked(SearchWindowEventDetails* const details)
{
	SearchWindowRefPtr theSearchWindow = dynamic_cast<SearchWindow*>(details->getSource());
}

void TextEditor::handleReplaceButtonClicked(SearchWindowEventDetails* const details)
{
}

void TextEditor::handleReplaceAllButtonClicked(SearchWindowEventDetails* const details)
{
}

void TextEditor::handleBookmarkAllButtonClicked(SearchWindowEventDetails* const details)
{
}

void TextEditor::saveFile(const BoostPath& file)
{
}

void TextEditor::handleCloseButtonAction(ActionEventDetails* const details)
{
	ButtonRefPtr _TempCloseButton = dynamic_cast<Button*>(details->getSource());
	PanelRefPtr _TempPanel = dynamic_cast<Panel*>(_TempCloseButton->getParentContainer());
	TabPanelRefPtr _TempTabPanel = dynamic_cast<TabPanel*>(_TempPanel->getParentContainer());
	UInt32 _ChildIndex = (_TempTabPanel->getChildIndex(_TempPanel))/2;

	_LeftTabPanel->removeTab(_ChildIndex);

	_RightTabPanel->removeTab(_ChildIndex);
}

void TextEditor::handleClipboardButtonAction(ActionEventDetails* const details)
{
	TextDomAreaRefPtr tempDomArea = getFocusedDomArea();
	if(tempDomArea == NULL) return;
	std::string stringToBeInserted = boost::any_cast<std::string>(_TheClipboardList->getSelectedItem());
	tempDomArea->handlePastingAString(stringToBeInserted);
}

void TextEditor::createRightTabPanel(void)
{
    _RightTabPanel= TabPanel::create();
    _RightTabPanel->setPreferredSize(Vec2f(600,400));
    _RightTabPanel->addTab(_RightTabPanelLabel, _RightTabPanelContent);
    _RightTabPanel->setTabAlignment(0.5f);
    _RightTabPanel->setTabPlacement(TabPanel::PLACEMENT_NORTH);
    _RightTabPanel->setSelectedIndex(0);
}

void TextEditor::createLeftTabPanel(void)
{
    _LeftTabPanel= TabPanel::create();
    _LeftTabPanel->setPreferredSize(Vec2f(600,400));
    _LeftTabPanel->addTab(_LeftTabPanelLabel, _LeftTabPanelContent);
    _LeftTabPanel->setTabAlignment(0.5f);
    _LeftTabPanel->setTabPlacement(TabPanel::PLACEMENT_NORTH);
    _LeftTabPanel->setSelectedIndex(0);
}

void TextEditor::createDefaultTabs()
{
    _LeftTabPanelLabel = Label::create();

    // set the fields of the labels
    _LeftTabPanelLabel->setPreferredSize(Vec2f(120,20));
    _LeftTabPanelLabel->setText("Welcome!");
    _LeftTabPanelLabel->setBorders(NULL);
    _LeftTabPanelLabel->setBackgrounds(NULL);

    // Create a _StackTraceTextArea
    _LeftTabPanelTextArea = TextArea::create();
    _LeftTabPanelTextArea->setEditable(false);

    _LeftTabPanelContent = ScrollPanel::create();
    _LeftTabPanelContent->setPreferredSize(Vec2f(200,1200));
    _LeftTabPanelContent->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    // Add the _LeftTabPanelTextArea to the ScrollPanel so it is displayed
    _LeftTabPanelContent->setViewComponent(_LeftTabPanelTextArea);


    _RightTabPanelLabel = Label::create();

    // set the fields of the labels
    _RightTabPanelLabel->setText("Screen2");
    _RightTabPanelLabel->setBorders(NULL);
    _RightTabPanelLabel->setBackgrounds(NULL);

    // Create a _StackTraceTextArea
    _RightTabPanelTextArea = TextArea::create();
    _RightTabPanelTextArea->setEditable(false);

    _RightTabPanelContent = ScrollPanel::create();
    _RightTabPanelContent->setPreferredSize(Vec2f(200,400));
    _RightTabPanelContent->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    // Add the _RightTabPanelTextArea to the ScrollPanel so it is displayed
    _RightTabPanelContent->setViewComponent(_RightTabPanelTextArea);

}

void TextEditor::updateDomLayout(bool isSplit)
{
    if(isSplit)
    {
        _InsideDomArea->setDividerPosition(.50); 
        _InsideDomArea->setMaxDividerPosition(.75);
        _InsideDomArea->setMinDividerPosition(.25);
    }
    else
    {
        _InsideDomArea->setDividerPosition(1); 
        _InsideDomArea->setMaxDividerPosition(1);
        _InsideDomArea->setMinDividerPosition(1);
    }
}

void TextEditor::updateLayout(bool isClipboardVisible)
{
	if(isClipboardVisible)
	{
		_DomAreaAndClipboard->setDividerSize(5);
		_DomAreaAndClipboard->setDividerPosition(0.75);
		_DomAreaAndClipboard->setMaxDividerPosition(.9);
		_DomAreaAndClipboard->setMinDividerPosition(0.5);
	}
	else
	{
		_DomAreaAndClipboard->setDividerSize(0);
		_DomAreaAndClipboard->setDividerPosition(1); 
        _DomAreaAndClipboard->setMaxDividerPosition(1);
        _DomAreaAndClipboard->setMinDividerPosition(1);
	}
}

AdvancedTextDomAreaTransitPtr TextEditor::createDuplicate(AdvancedTextDomArea* const TheAdvancedTextDomArea)
{
	return AdvancedTextDomAreaTransitPtr(TheAdvancedTextDomArea->createDuplicate());
}

void TextEditor::loadFile(const BoostPath& file)
{
	if(boost::filesystem::exists(file))
	{
		PanelRefPtr _NewLeftTabLabelPanel = Panel::createEmpty();

		ButtonRefPtr _NewLeftTabLabelCloseButtonRefPtr =
			dynamic_pointer_cast<Button>(dynamic_cast<InternalWindow*>(InternalWindow::getClassType().getPrototype())->getTitlebar()->getCloseButton()->shallowCopy());

		//ButtonRefPtr _NewLeftTabLabelCloseButtonRefPtr = Button::create();

		/*_NewLeftTabLabelCloseButtonRefPtr->setPreferredSize(Vec2f(100,20));
		_NewLeftTabLabelCloseButtonRefPtr->setText("X");*/

        _NewLeftTabLabelCloseButtonRefPtr->connectActionPerformed(boost::bind(&TextEditor::handleCloseButtonAction, this, _1));

		LabelRefPtr _NewLeftTabLabelLabel=Label::create();
		_NewLeftTabLabelLabel->setText(file.leaf());
		_NewLeftTabLabelLabel->setBorders(NULL);
		_NewLeftTabLabelLabel->setBackgrounds(NULL);

		SpringLayoutRefPtr _NewLeftTabLabelPanelSpringLayout = SpringLayout::create();

		_NewLeftTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _NewLeftTabLabelCloseButtonRefPtr, 2, SpringLayoutConstraints::NORTH_EDGE, _NewLeftTabLabelPanel);  
		_NewLeftTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _NewLeftTabLabelCloseButtonRefPtr, -2, SpringLayoutConstraints::EAST_EDGE, _NewLeftTabLabelPanel);
		_NewLeftTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _NewLeftTabLabelCloseButtonRefPtr, -20, SpringLayoutConstraints::EAST_EDGE, _NewLeftTabLabelPanel);
		_NewLeftTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _NewLeftTabLabelCloseButtonRefPtr, -2, SpringLayoutConstraints::SOUTH_EDGE, _NewLeftTabLabelPanel);

		_NewLeftTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _NewLeftTabLabelLabel, 2, SpringLayoutConstraints::NORTH_EDGE, _NewLeftTabLabelPanel);  
		_NewLeftTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _NewLeftTabLabelLabel, -5, SpringLayoutConstraints::WEST_EDGE, _NewLeftTabLabelCloseButtonRefPtr);
		_NewLeftTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _NewLeftTabLabelLabel, 2, SpringLayoutConstraints::WEST_EDGE, _NewLeftTabLabelPanel);
		_NewLeftTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _NewLeftTabLabelLabel, -2, SpringLayoutConstraints::SOUTH_EDGE, _NewLeftTabLabelPanel);


		_NewLeftTabLabelPanel->setPreferredSize(Vec2f(120,20));
		_NewLeftTabLabelPanel->pushToChildren(_NewLeftTabLabelLabel);
		_NewLeftTabLabelPanel->pushToChildren(_NewLeftTabLabelCloseButtonRefPtr);
		_NewLeftTabLabelPanel->setLayout(/*LayoutRefPtr(FlowLayout::create())*/_NewLeftTabLabelPanelSpringLayout);


			// Create a TextDomArea component
		UIFontRefPtr _Font = UIFont::create();
		_Font->setFamily("SANS");
		_Font->setGap(3);
		_Font->setGlyphPixelSize(46);
		_Font->setSize(15);
		_Font->setTextureWidth(0);
		_Font->setStyle(TextFace::STYLE_PLAIN);

		AdvancedTextDomAreaRefPtr ExampleTextDomArea = AdvancedTextDomArea::create();
		ExampleTextDomArea->setPreferredSize(Vec2f(400,400));
		ExampleTextDomArea->loadFile(file);
		
		/*ExampleTextDomArea->setWrapStyleWord(false);
		ExampleTextDomArea->setFont(_Font);*/

		ScrollPanelRefPtr _NewLeftTabContent = ScrollPanel::create();
		_NewLeftTabContent->setPreferredSize(Vec2f(200,400));
		_NewLeftTabContent->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
		_NewLeftTabContent->setViewComponent(ExampleTextDomArea); 

		PanelRefPtr _NewRightTabLabelPanel = Panel::createEmpty();

		ButtonRefPtr _RightTabLabelCloseButtonRefPtr = dynamic_pointer_cast<Button>(dynamic_cast<InternalWindow*>(InternalWindow::getClassType().getPrototype())->getTitlebar()->getCloseButton()->shallowCopy());

		//_RightTabLabelCloseButtonRefPtr->setPreferredSize(Vec2f(20,10));
		// _RightTabLabelCloseButtonRefPtr->setText("X");

        _RightTabLabelCloseButtonRefPtr->connectActionPerformed(boost::bind(&TextEditor::handleCloseButtonAction, this, _1));


		LabelRefPtr _NewRightTabLabel=Label::create();
		_NewRightTabLabel->setText(file.leaf());
		_NewRightTabLabel->setBorders(NULL);
		_NewRightTabLabel->setBackgrounds(NULL);

		SpringLayoutRefPtr _NewRightTabLabelPanelSpringLayout = SpringLayout::create();

		_NewRightTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _RightTabLabelCloseButtonRefPtr, 2, SpringLayoutConstraints::NORTH_EDGE, _NewRightTabLabelPanel);  
		_NewRightTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _RightTabLabelCloseButtonRefPtr, -2, SpringLayoutConstraints::EAST_EDGE, _NewRightTabLabelPanel);
		_NewRightTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _RightTabLabelCloseButtonRefPtr, -20, SpringLayoutConstraints::EAST_EDGE, _NewRightTabLabelPanel);
		_NewRightTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _RightTabLabelCloseButtonRefPtr, -2, SpringLayoutConstraints::SOUTH_EDGE, _NewRightTabLabelPanel);

		_NewRightTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _NewRightTabLabel, 2, SpringLayoutConstraints::NORTH_EDGE, _NewRightTabLabelPanel);  
		_NewRightTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _NewRightTabLabel, -5, SpringLayoutConstraints::WEST_EDGE, _RightTabLabelCloseButtonRefPtr);
		_NewRightTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _NewRightTabLabel, 2, SpringLayoutConstraints::WEST_EDGE, _NewRightTabLabelPanel);
		_NewRightTabLabelPanelSpringLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _NewRightTabLabel, -2, SpringLayoutConstraints::SOUTH_EDGE, _NewRightTabLabelPanel);


		_NewRightTabLabelPanel->setPreferredSize(Vec2f(120,20));
		_NewRightTabLabelPanel->pushToChildren(_RightTabLabelCloseButtonRefPtr);
		_NewRightTabLabelPanel->pushToChildren(_NewRightTabLabel);
		_NewRightTabLabelPanel->setLayout(/*LayoutRefPtr(FlowLayout::create())*/_NewRightTabLabelPanelSpringLayout);


		AdvancedTextDomAreaRefPtr ExampleTextDomArea2 =  createDuplicate(ExampleTextDomArea);///*dynamic_pointer_cast<AdvancedTextDomArea>(deepClone(ExampleTextDomArea));*/AdvancedTextDomArea::create();
		//ExampleTextDomArea2->setPreferredSize(Vec2f(400, 400));
		//ExampleTextDomArea2->loadFile(file);
		

		ScrollPanelRefPtr _NewRightTabContent = ScrollPanel::create();
		_NewRightTabContent->setPreferredSize(Vec2f(200,400));
		_NewRightTabContent->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
		_NewRightTabContent->setViewComponent(ExampleTextDomArea2);


		_LeftTabPanel->addTab(_NewLeftTabLabelPanel, _NewLeftTabContent);
		_LeftTabPanel->setSelectedIndex((_LeftTabPanel->getMFTabs()->size())-1);
		_RightTabPanel->addTab(_NewRightTabLabelPanel, _NewRightTabContent);
		_RightTabPanel->setSelectedIndex((_RightTabPanel->getMFTabs()->size())-1);
	
	}
}

void TextEditor::createDomArea(void)
{

	createDefaultTabs();
	createRightTabPanel();
	createLeftTabPanel();

	BorderLayoutConstraintsRefPtr ExampleSplitPanelConstraints2 = BorderLayoutConstraints::create();
    ExampleSplitPanelConstraints2->setRegion(BorderLayoutConstraints::BORDER_CENTER);
	
	_InsideDomArea = SplitPanel::create();

	_InsideDomArea->setConstraints(ExampleSplitPanelConstraints2);
	_InsideDomArea->setExpandable(true);
	_InsideDomArea->setDividerSize(2);
	_InsideDomArea->setOrientation(SplitPanel::HORIZONTAL_ORIENTATION);
	_InsideDomArea->setMinComponent(_LeftTabPanel);
	_InsideDomArea->setMaxComponent(_RightTabPanel);
	
	updateDomLayout(getIsSplit());

}

void TextEditor::clipboardInitialization()
{
	BorderLayoutRefPtr MainInternalWindowLayout = BorderLayout::create();

	BorderLayoutConstraintsRefPtr ClipboardLabelConstraints = BorderLayoutConstraints::create();
    BorderLayoutConstraintsRefPtr ClipboardPanelConstraints = BorderLayoutConstraints::create();
	BorderLayoutConstraintsRefPtr ClipboardButtonConstraints = BorderLayoutConstraints::create();

	ClipboardLabelConstraints->setRegion(BorderLayoutConstraints::BORDER_NORTH);
    ClipboardPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
	ClipboardButtonConstraints->setRegion(BorderLayoutConstraints::BORDER_SOUTH);

	_TheClipboardPanel = Panel::create();
	
	// the Clipboard label
	_TheClipboardLabel = Label::create();
    _TheClipboardLabel->setText("Copy Clipboard");
    _TheClipboardLabel->setTextColor(Color4f(0.3, 0.3, 0.3, 1.0));
    _TheClipboardLabel->setAlignment(Vec2f(0.5,0.5));
    _TheClipboardLabel->setPreferredSize(Vec2f(200, 20));
    _TheClipboardLabel->setTextSelectable(false);
	_TheClipboardLabel->setConstraints(ClipboardLabelConstraints);

	_TheClipboardButton = Button::create();
	_TheClipboardButton->setText("Insert Into Document");
	_TheClipboardButton->setMinSize(_TheClipboardButton->getPreferredSize());
    _TheClipboardButton->setPreferredSize(_TheClipboardButton->getRequestedSize());
    _ClipboardButtonActionConnection.disconnect();
    _ClipboardButtonActionConnection = _TheClipboardButton->connectActionPerformed(boost::bind(&TextEditor::handleClipboardButtonAction, this, _1));
	_TheClipboardButton->setConstraints(ClipboardButtonConstraints);

	// the Clipboard list
    _TheClipboardListSelectionModel=DefaultListSelectionModel::create();
	_TheClipboardListSelectionModel->setSelectionMode(DefaultListSelectionModel::SINGLE_SELECTION);

	_TheClipboardListModel = DefaultListModel::create();
	//_TheClipboardListModel->pushBack(boost::any(std::string("Red")));

	_TheClipboardList = List::create();
	_TheClipboardList->setPreferredSize(Vec2f(200, 400));
	_TheClipboardList->setOrientation(List::VERTICAL_ORIENTATION);
	_TheClipboardList->setModel(_TheClipboardListModel);

	_TheClipboardList->setSelectionModel(_TheClipboardListSelectionModel);

	_TheClipboardScrollPanel = ScrollPanel::create();
	_TheClipboardScrollPanel->setPreferredSize(Vec2f(200,400));
	_TheClipboardScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
	_TheClipboardScrollPanel->setViewComponent(_TheClipboardList);
	_TheClipboardScrollPanel->setConstraints(ClipboardPanelConstraints);

    _TheClipboardPanel->pushToChildren(_TheClipboardLabel);
	_TheClipboardPanel->pushToChildren(_TheClipboardScrollPanel);
	_TheClipboardPanel->pushToChildren(_TheClipboardButton);
	_TheClipboardPanel->setLayout(/*LayoutRefPtr(FlowLayout::create())*/MainInternalWindowLayout/*_TheClipboardPanelLayout*/);
	_TheClipboardPanel->setPreferredSize(Vec2f(200, 400));
}

void TextEditor::onCreate(const TextEditor *source)
{

	if(source == NULL)
	{
		return;
	}

	createDomArea();
	clipboardInitialization();

	_DomAreaAndClipboard = SplitPanel::create();

	BorderLayoutRefPtr MainInternalWindowLayout = BorderLayout::create();

    BorderLayoutConstraintsRefPtr ExampleSplitPanelConstraints = BorderLayoutConstraints::create();
    ExampleSplitPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
	
	_DomAreaAndClipboard->setConstraints(ExampleSplitPanelConstraints);
	_DomAreaAndClipboard->setExpandable(true);
	_DomAreaAndClipboard->setOrientation(SplitPanel::HORIZONTAL_ORIENTATION);
	_DomAreaAndClipboard->setMaxComponent(_TheClipboardPanel);
	_DomAreaAndClipboard->setMinComponent(_InsideDomArea);


	updateLayout(getClipboardVisible());

	pushToChildren(_DomAreaAndClipboard);
	setLayout(MainInternalWindowLayout);

}

void TextEditor::resolveLinks(void)
{
    Inherited::resolveLinks();

    _DomAreaAndClipboard = NULL;
    _InsideDomArea = NULL;
    _TheClipboardList = NULL;
    _TheClipboardListModel = NULL;
    _TheClipboardListSelectionModel = NULL;
    _TheClipboardScrollPanel = NULL;
    _TheClipboardLabel = NULL;
    _TheClipboardPanel = NULL;
    _TheClipboardPanelLayout = NULL;
    _TheClipboardButton = NULL;
    _LeftTabPanel = NULL;
    _LeftTabPanelLabel = NULL;
    _LeftTabPanelContent = NULL;
    _LeftTabPanelTextArea = NULL;
    _RightTabPanel = NULL;
    _RightTabPanelLabel = NULL;
    _RightTabPanelContent = NULL;
    _RightTabPanelTextArea = NULL;
    _SearchDialog = NULL;

    _SearchButtonClickedConnection.disconnect();
    _ReplaceButtonClickedConnection.disconnect();
    _ReplaceAllButtonClickedConnection.disconnect();
    _BookmarkAllButtonClickedConnection.disconnect();
    _ClipboardButtonActionConnection.disconnect();
    _CloseButtonActionConnection.disconnect();
}

TextEditor::TextEditor(void) :
    Inherited()
{
}

TextEditor::TextEditor(const TextEditor &source) :
    Inherited(source)
{
}

TextEditor::~TextEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TextEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
	if(whichField & TextEditor::ClipboardVisibleFieldMask)
	{
		updateLayout(getClipboardVisible());
	}
	else if(whichField & TextEditor::IsSplitFieldMask)
	{
		updateDomLayout(getIsSplit());
	}

    Inherited::changed(whichField, origin, details);
}

void TextEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TextEditor NI" << std::endl;
}

OSG_END_NAMESPACE
