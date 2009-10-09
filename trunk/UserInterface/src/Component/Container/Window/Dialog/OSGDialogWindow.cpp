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
#include <vector>

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "Component/Container/OSGContainer.h"
#include "Component/Button/OSGButton.h"
#include "Component/ComboBox/OSGComboBox.h"
#include "Component/ComboBox/Models/OSGDefaultMutableComboBoxModel.h"
#include "Component/Container/OSGPanel.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include "Layout/OSGFlowLayout.h"
#include "Layout/Spring/OSGLayoutSpring.h"
#include "Layout/OSGSpringLayout.h"
#include "Layout/OSGSpringLayoutConstraints.h"
#include "Component/Misc/OSGImageComponent.h"
#include "Component/Text/OSGTextArea.h"
#include "Component/Text/OSGTextField.h"
#include "Border/OSGEmptyBorder.h"
#include "Border/OSGLineBorder.h"
#include "Layer/OSGEmptyLayer.h"
#include "OSGDialogWindow.h"
#include "Event/OSGActionListener.h"

#include "Component/Spinner/OSGSpinner.h"

#include "Layout/OSGBorderLayout.h"
#include "Layout/OSGBorderLayoutConstraints.h"

#include "Component/Container/ColorChooser/OSGColorChooser.h"
#include "Layout/OSGBorderLayout.h"
#include "Layout/OSGBorderLayoutConstraints.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DialogWindow
A UI Dialog Window. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

ComboBoxPtr InputComboBox;
TextFieldPtr InputTextField;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DialogWindow::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void DialogWindow::close(UInt32 intOption, std::string strInput)
{
	_VetoWindowClose = false;

	produceDialogWindowClosing(intOption,strInput);
	produceWindowClosing();
	
	if(!_VetoWindowClose && getDrawingSurface() != NullFC)
	{
		getDrawingSurface()->closeWindow(DialogWindowPtr(this));
		produceDialogWindowClosed(intOption,strInput);
		produceWindowClosed();
	}
}

void DialogWindow::produceDialogWindowClosing(UInt32 intOption, std::string strInput)
{
   const DialogWindowEventPtr TheEvent = DialogWindowEvent::create( DialogWindowPtr(this),getSystemTime(),intOption,strInput);
   for(DialogWindowListenerSetConstItor SetItor(_DialogWindowListeners.begin()) ; SetItor != _DialogWindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->dialogClosing(TheEvent);
   }
}

void DialogWindow::produceDialogWindowClosed(UInt32 intOption, std::string strInput)
{
   const DialogWindowEventPtr TheEvent = DialogWindowEvent::create( DialogWindowPtr(this),getSystemTime(),intOption,strInput);
   for(DialogWindowListenerSetConstItor SetItor(_DialogWindowListeners.begin()) ; SetItor != _DialogWindowListeners.end() ; ++SetItor)
   {
	   (*SetItor)->dialogClosed(TheEvent);
   }
}

EventConnection DialogWindow::addDialogWindowListener(DialogWindowListenerPtr Listener)
{
   _DialogWindowListeners.insert(Listener);
   return EventConnection(
       boost::bind(&DialogWindow::isDialogWindowListenerAttached, this, Listener),
       boost::bind(&DialogWindow::removeDialogWindowListener, this, Listener));
}

EventConnection DialogWindow::addEventListener(EventListenerPtr Listener)
{
    _EventListeners.insert(Listener);
   return EventConnection(
       boost::bind(&DialogWindow::isEventListenerAttached, this, Listener),
       boost::bind(&DialogWindow::removeEventListener, this, Listener));
}

void DialogWindow::removeEventListener(EventListenerPtr Listener)
{
   EventListenerSetItor EraseIter(_EventListeners.find(Listener));
   if(EraseIter != _EventListeners.end())
   {
      _EventListeners.erase(EraseIter);
   }
}

void DialogWindow::removeDialogWindowListener(DialogWindowListenerPtr Listener)
{
   DialogWindowListenerSetItor EraseIter(_DialogWindowListeners.find(Listener));
   if(EraseIter != _DialogWindowListeners.end())
   {
      _DialogWindowListeners.erase(EraseIter);
   }
}

DialogWindowPtr DialogWindow::createInputDialog(const std::string& Title, const std::string& Message, const int& Type, const bool& showCancel, const std::vector<std::string>& InputValues, const std::string& ConfirmBtnText, const std::string& CancelBtnText)
{
    int DialogHeight = 175;
	DialogWindowPtr TheDialog = DialogWindow::create();

	ImageComponentPtr TheIcon = ImageComponent::create();
	LineBorderPtr TempIconBorder = osg::LineBorder::create();
	beginEditCP(TheIcon, ImageComponent::PreferredSizeFieldMask | ImageComponent::BordersFieldMask);
		TheIcon->setPreferredSize(Vec2f(45,45));
		TheIcon->setBorders(TempIconBorder);
	endEditCP(TheIcon, ImageComponent::PreferredSizeFieldMask | ImageComponent::BordersFieldMask);
	
	// Create Panel for input
	PanelPtr InputPanel = osg::Panel::createEmpty();
	FlowLayoutPtr InputPanelLayout = osg::FlowLayout::create();
	beginEditCP(InputPanel, Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);
		InputPanel->setLayout(InputPanelLayout);
		InputPanel->setPreferredSize(Vec2f(450,75));
	endEditCP(InputPanel, Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);
	
	ButtonPtr InputButton;
	switch (Type) {
		case INPUT_TEXT:
			InputTextField = osg::TextField::create();
			beginEditCP(InputTextField, TextField::TextFieldMask | TextField::PreferredSizeFieldMask);
				InputTextField->setText(InputValues[0]);
				InputTextField->setPreferredSize(Vec2f(200,25));
			endEditCP(InputTextField, TextField::TextFieldMask | TextField::PreferredSizeFieldMask);
			beginEditCP(InputPanel, Panel::ChildrenFieldMask);
				InputPanel->getChildren().push_back(InputTextField);
			endEditCP(InputPanel, Panel::ChildrenFieldMask);
		break;
		case INPUT_BTNS:	
			DialogHeight = 150;
			beginEditCP(InputPanel, Panel::ChildrenFieldMask);	
				for (std::vector<std::string>::const_iterator it = InputValues.begin(); it!=InputValues.end(); ++it)
				{
					InputButton = osg::Button::create();
					beginEditCP(InputButton, Button::TextFieldMask | Button::PreferredSizeFieldMask | Button::MinSizeFieldMask);
						InputButton->setText(*it);
						InputButton->setMinSize(InputButton->getPreferredSize());
						InputButton->setPreferredSize(InputButton->getRequestedSize());
					endEditCP(InputButton, Button::TextFieldMask | Button::PreferredSizeFieldMask | Button::MinSizeFieldMask);
					InputButtonListener* InputListener = new InputButtonListener(TheDialog);
					InputButton->addActionListener(InputListener);
					InputPanel->getChildren().push_back(InputButton);
				}				
			endEditCP(InputPanel, Panel::ChildrenFieldMask);		
		break;
		case INPUT_COMBO:
		default:
			InputComboBox = osg::ComboBox::create();
			DefaultMutableComboBoxModelPtr InputComboBoxModel;
			InputComboBoxModel = DefaultMutableComboBoxModel::create();
			
			for (std::vector<std::string>::const_iterator it = InputValues.begin(); it!=InputValues.end(); ++it)
			{
				InputComboBoxModel->addElement(boost::any(std::string(*it)));
			}

			beginEditCP(InputComboBox, ComboBox::PreferredSizeFieldMask | ComboBox::ModelFieldMask);
				InputComboBox->setPreferredSize(Vec2f(150, 23));
				InputComboBox->setModel(InputComboBoxModel);
			endEditCP(InputComboBox, ComboBox::PreferredSizeFieldMask | ComboBox::ModelFieldMask);
			InputComboBox->setSelectedIndex(0);

			beginEditCP(InputPanel, Panel::ChildrenFieldMask);
				InputPanel->getChildren().push_back(InputComboBox);
			endEditCP(InputPanel, Panel::ChildrenFieldMask);
		break;
	}

	FlowLayoutPtr MessagePanelBottomLayout;
	PanelPtr MessageButtonPanel;
	ButtonPtr ConfirmationButton;
	ButtonPtr CancelButton;
	

	if(Type != INPUT_BTNS)
	{
		ConfirmationButton = osg::Button::create();
		//Confirm Button
		beginEditCP(ConfirmationButton, Button::TextFieldMask | Button::PreferredSizeFieldMask | Button::MinSizeFieldMask);
			ConfirmationButton->setText(ConfirmBtnText);
			ConfirmationButton->setMinSize(ConfirmationButton->getPreferredSize());
			ConfirmationButton->setPreferredSize(ConfirmationButton->getRequestedSize());
		endEditCP(ConfirmationButton, Button::TextFieldMask | Button::PreferredSizeFieldMask | Button::MinSizeFieldMask);

		ActionListener* ConfirmListener;

		if(Type == INPUT_TEXT)
			ConfirmListener = new TextButtonListener(TheDialog);
		else
			ConfirmListener = new ComboButtonListener(TheDialog);

		ConfirmationButton->addActionListener(ConfirmListener);
	}

	if(showCancel)
	{
		CancelButton = osg::Button::create();
		//Cancel Button
		beginEditCP(CancelButton, Button::TextFieldMask | Button::PreferredSizeFieldMask | Button::MinSizeFieldMask);
			CancelButton->setText(CancelBtnText);
			CancelButton->setMinSize(CancelButton->getPreferredSize());
			CancelButton->setPreferredSize(CancelButton->getRequestedSize());
		endEditCP(CancelButton, Button::TextFieldMask | Button::PreferredSizeFieldMask | Button::MinSizeFieldMask);

		//Attach listener to the Cancel button
		CancelButtonListener* CancelListener = new CancelButtonListener(TheDialog);
		CancelButton->addActionListener(CancelListener);
	}

	// Create Panel for top half of SplitPanel
	TextAreaPtr MessagePanelText = createTransparentTextArea(Message);

	//If the type of input is buttons and showCancel is true, just push the cancel button onto the input panel
	if(Type == INPUT_BTNS && showCancel)
	{
		beginEditCP(InputPanel, Panel::ChildrenFieldMask);
			InputPanel->getChildren().push_back(CancelButton);
		endEditCP(InputPanel, Panel::ChildrenFieldMask);
	}
	else if(Type != INPUT_BTNS)
	{
		// Create Panel for bottom half of SplitPanel
		MessageButtonPanel = osg::Panel::createEmpty();
		MessagePanelBottomLayout = osg::FlowLayout::create();
		beginEditCP(MessageButtonPanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);
			MessageButtonPanel->getChildren().push_back(ConfirmationButton);
			if(showCancel) 
				MessageButtonPanel->getChildren().push_back(CancelButton);
			MessageButtonPanel->setLayout(MessagePanelBottomLayout);
			MessageButtonPanel->setPreferredSize(Vec2f(450,75));
		endEditCP(MessageButtonPanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);
	} 

	// Create SplitPanel itself
    PanelPtr MessagePanel = osg::Panel::createEmpty();
    SpringLayoutPtr MessagePanelLayout = SpringLayout::create();
    beginEditCP(MessagePanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
		MessagePanel->getChildren().push_back(MessagePanelText);
		MessagePanel->getChildren().push_back(TheIcon);
		MessagePanel->getChildren().push_back(InputPanel);
		if(Type != INPUT_BTNS)
			MessagePanel->getChildren().push_back(MessageButtonPanel);
        MessagePanel->setLayout(MessagePanelLayout);
	endEditCP(MessagePanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);


    //MessagePanelLayout
    //Icon
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, TheIcon, 10, SpringLayoutConstraints::NORTH_EDGE, MessagePanel);
	MessagePanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, TheIcon, LayoutSpring::width(TheIcon));
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TheIcon, 10, SpringLayoutConstraints::WEST_EDGE, MessagePanel);
	MessagePanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, TheIcon, LayoutSpring::height(TheIcon));

    //Message
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, MessagePanelText, 5, SpringLayoutConstraints::NORTH_EDGE, MessagePanel);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MessagePanelText, -5, SpringLayoutConstraints::EAST_EDGE, MessagePanel);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MessagePanelText, 10, SpringLayoutConstraints::EAST_EDGE, TheIcon);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, MessagePanelText, 20, SpringLayoutConstraints::NORTH_EDGE, InputPanel);

    //Input Panel
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, InputPanel, 0, SpringLayoutConstraints::WEST_EDGE, MessagePanel);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, InputPanel, 0, SpringLayoutConstraints::EAST_EDGE, MessagePanel);
    
	if(Type != INPUT_BTNS)
	{
		MessagePanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, InputPanel, 40, SpringLayoutConstraints::NORTH_EDGE, MessageButtonPanel);
		//Button Panel
		MessagePanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, MessageButtonPanel, LayoutSpring::height(MessageButtonPanel));
		MessagePanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MessageButtonPanel, 0, SpringLayoutConstraints::WEST_EDGE, MessagePanel);
		MessagePanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MessageButtonPanel, 0, SpringLayoutConstraints::EAST_EDGE, MessagePanel);
		MessagePanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, MessageButtonPanel, 20, SpringLayoutConstraints::SOUTH_EDGE, MessagePanel);
	}
	else
	{
		MessagePanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, InputPanel, 20, SpringLayoutConstraints::SOUTH_EDGE, MessagePanel);
	}

	//Internals Layout and constraints
	BorderLayoutConstraintsPtr MessagePanelConstraints = BorderLayoutConstraints::create();
	beginEditCP(MessagePanelConstraints, BorderLayoutConstraints::RegionFieldMask);
		MessagePanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
	endEditCP(MessagePanelConstraints, BorderLayoutConstraints::RegionFieldMask);

	beginEditCP(MessagePanel, Container::ConstraintsFieldMask);
		MessagePanel->setConstraints(MessagePanelConstraints);
	endEditCP(MessagePanel, Container::ConstraintsFieldMask);

	BorderLayoutPtr DialogLayout = BorderLayout::create();

	//Create the Dialog box
	beginEditCP(TheDialog, DialogWindow::LayoutFieldMask | DialogWindow::PreferredSizeFieldMask | DialogWindow::ChildrenFieldMask | DialogWindow::TitleFieldMask);
		TheDialog->setLayout(DialogLayout);
        TheDialog->setPreferredSize(Vec2f(350,DialogHeight));
		TheDialog->getChildren().push_back(MessagePanel);
		TheDialog->setTitle(Title);
	endEditCP(TheDialog, DialogWindow::LayoutFieldMask | DialogWindow::PreferredSizeFieldMask | DialogWindow::ChildrenFieldMask | DialogWindow::TitleFieldMask);

	return TheDialog;
}

DialogWindowPtr DialogWindow::createMessageDialog(const std::string& Title, const std::string& Message, const int& Type, const bool& showCancel, const std::string& ConfirmBtnText, const std::string& CancelBtnText)
{
    ImageComponentPtr TheIcon = ImageComponent::create();
	LineBorderPtr TempIconBorder = osg::LineBorder::create();
	beginEditCP(TheIcon, ImageComponent::PreferredSizeFieldMask | ImageComponent::BordersFieldMask);
		TheIcon->setPreferredSize(Vec2f(45,45));
		TheIcon->setBorders(TempIconBorder);
	endEditCP(TheIcon, ImageComponent::PreferredSizeFieldMask | ImageComponent::BordersFieldMask);
     
	ButtonPtr ConfirmationButton = osg::Button::create();
	ButtonPtr CancelButton;
	
	//Confirm Button
    beginEditCP(ConfirmationButton, Button::TextFieldMask | Button::PreferredSizeFieldMask | Button::MinSizeFieldMask);
		ConfirmationButton->setText(ConfirmBtnText);
        ConfirmationButton->setMinSize(ConfirmationButton->getPreferredSize());
        ConfirmationButton->setPreferredSize(ConfirmationButton->getRequestedSize());
	endEditCP(ConfirmationButton, Button::TextFieldMask | Button::PreferredSizeFieldMask | Button::MinSizeFieldMask);

	if(showCancel)
	{
		//Cancel Button
		CancelButton = osg::Button::create();
		beginEditCP(CancelButton, Button::TextFieldMask | Button::PreferredSizeFieldMask | Button::MinSizeFieldMask);
			CancelButton->setText(CancelBtnText);
			CancelButton->setMinSize(CancelButton->getPreferredSize());
			CancelButton->setPreferredSize(CancelButton->getRequestedSize());
		endEditCP(CancelButton, Button::TextFieldMask | Button::PreferredSizeFieldMask | Button::MinSizeFieldMask);
	}

	// Create Panel for top half of SplitPanel
	TextAreaPtr MessagePanelText = createTransparentTextArea(Message);
	
	// Create Panel for bottom half of SplitPanel
	PanelPtr MessageButtonPanel = osg::Panel::createEmpty();
	FlowLayoutPtr MessagePanelBottomLayout = osg::FlowLayout::create();
	beginEditCP(MessageButtonPanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);
		MessageButtonPanel->getChildren().push_back(ConfirmationButton);
		if(showCancel) 
			MessageButtonPanel->getChildren().push_back(CancelButton);
		MessageButtonPanel->setLayout(MessagePanelBottomLayout);
		MessageButtonPanel->setPreferredSize(Vec2f(450,75));
	endEditCP(MessageButtonPanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
	 
	// Create SplitPanel itself
    PanelPtr MessagePanel = osg::Panel::createEmpty();
    SpringLayoutPtr MessagePanelLayout = SpringLayout::create();
    beginEditCP(MessagePanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
		MessagePanel->getChildren().push_back(MessagePanelText);
		MessagePanel->getChildren().push_back(TheIcon);
		MessagePanel->getChildren().push_back(MessageButtonPanel);
        MessagePanel->setLayout(MessagePanelLayout);
	endEditCP(MessagePanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);


    //MessagePanelLayout
    //Icon
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, TheIcon, 10, SpringLayoutConstraints::NORTH_EDGE, MessagePanel);
	MessagePanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, TheIcon, LayoutSpring::width(TheIcon));
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TheIcon, 10, SpringLayoutConstraints::WEST_EDGE, MessagePanel);
	MessagePanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, TheIcon, LayoutSpring::height(TheIcon));

    //Message
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, MessagePanelText, 5, SpringLayoutConstraints::NORTH_EDGE, MessagePanel);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MessagePanelText, -5, SpringLayoutConstraints::EAST_EDGE, MessagePanel);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MessagePanelText, 10, SpringLayoutConstraints::EAST_EDGE, TheIcon);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, MessagePanelText, -30, SpringLayoutConstraints::SOUTH_EDGE, MessagePanel);

    //Button Panel
	MessagePanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MessageButtonPanel, 0, SpringLayoutConstraints::WEST_EDGE, MessagePanel);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MessageButtonPanel, 0, SpringLayoutConstraints::EAST_EDGE, MessagePanel);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, MessageButtonPanel, 20, SpringLayoutConstraints::SOUTH_EDGE, MessagePanel);
    
	//Internals Layout and constraints
	BorderLayoutConstraintsPtr MessagePanelConstraints = BorderLayoutConstraints::create();
	beginEditCP(MessagePanelConstraints, BorderLayoutConstraints::RegionFieldMask);
		MessagePanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
	endEditCP(MessagePanelConstraints, BorderLayoutConstraints::RegionFieldMask);

	beginEditCP(MessagePanel, Container::ConstraintsFieldMask);
		MessagePanel->setConstraints(MessagePanelConstraints);
	endEditCP(MessagePanel, Container::ConstraintsFieldMask);

	BorderLayoutPtr DialogLayout = BorderLayout::create();

	//Create the Dialog box
	DialogWindowPtr TheDialog = DialogWindow::create();
	beginEditCP(TheDialog, DialogWindow::LayoutFieldMask | DialogWindow::PreferredSizeFieldMask | DialogWindow::ChildrenFieldMask | DialogWindow::TitleFieldMask);
		TheDialog->setLayout(DialogLayout);
        TheDialog->setPreferredSize(Vec2f(350,150));
		TheDialog->getChildren().push_back(MessagePanel);
		TheDialog->setTitle(Title);
	endEditCP(TheDialog, DialogWindow::LayoutFieldMask | DialogWindow::PreferredSizeFieldMask | DialogWindow::ChildrenFieldMask | DialogWindow::TitleFieldMask);

    //Attach listener to the Confirm button
    ConfirmButtonListener* ConfirmListener = new ConfirmButtonListener(TheDialog);
    ConfirmationButton->addActionListener(ConfirmListener);

	if(showCancel)
	{
		//Attach listener to the Cancel button
		CancelButtonListener* CancelListener = new CancelButtonListener(TheDialog);
		CancelButton->addActionListener(CancelListener);
	}

	return TheDialog;
}

DialogWindow::ConfirmButtonListener::ConfirmButtonListener(DialogWindowPtr TheDialogWindow) : _DialogWindow(TheDialogWindow)
{
    _DialogWindow->addEventListener(this);
}

void DialogWindow::ConfirmButtonListener::actionPerformed(const ActionEventPtr e)
{
	_DialogWindow->close(DialogWindowEvent::DIALOG_OPTION_OK,"");
}

DialogWindow::CancelButtonListener::CancelButtonListener(DialogWindowPtr TheDialogWindow) : _DialogWindow(TheDialogWindow)
{
    _DialogWindow->addEventListener(this);
}

void DialogWindow::CancelButtonListener::actionPerformed(const ActionEventPtr e)
{
	_DialogWindow->close(DialogWindowEvent::DIALOG_OPTION_CANCEL,"");
}

DialogWindow::InputButtonListener::InputButtonListener(DialogWindowPtr TheDialogWindow) : _DialogWindow(TheDialogWindow)
{
    _DialogWindow->addEventListener(this);
}

void DialogWindow::InputButtonListener::actionPerformed(const ActionEventPtr e)
{
	_DialogWindow->close(DialogWindowEvent::DIALOG_OPTION_OK,Button::Ptr::dcast(e->getSource())->getText());
}


DialogWindow::ComboButtonListener::ComboButtonListener(DialogWindowPtr TheDialogWindow) : _DialogWindow(TheDialogWindow)
{
    _DialogWindow->addEventListener(this);
}

void DialogWindow::ComboButtonListener::actionPerformed(const ActionEventPtr e)
{
	_DialogWindow->close(DialogWindowEvent::DIALOG_OPTION_OK,boost::any_cast<std::string> (InputComboBox->getSelectedItem()));
}

DialogWindow::TextButtonListener::TextButtonListener(DialogWindowPtr TheDialogWindow) : _DialogWindow(TheDialogWindow)
{
    _DialogWindow->addEventListener(this);
}

void DialogWindow::TextButtonListener::actionPerformed(const ActionEventPtr e)
{
	_DialogWindow->close(DialogWindowEvent::DIALOG_OPTION_OK,InputTextField->getText());
}

TextAreaPtr DialogWindow::createTransparentTextArea(const std::string& Message)
{
	TextAreaPtr TransparentTextArea = osg::TextArea::create();
	EmptyLayerPtr TransparentTextAreaBackground = osg::EmptyLayer::create();
	EmptyBorderPtr TransparentTextAreaBorder = osg::EmptyBorder::create();

    beginEditCP(TransparentTextArea, TextArea::BordersFieldMask | TextArea::BackgroundsFieldMask | TextArea::TextFieldMask | TextArea::EditableFieldMask);
		TransparentTextArea->setBorders(TransparentTextAreaBorder);
		TransparentTextArea->setBackgrounds(TransparentTextAreaBackground);
		TransparentTextArea->setWrapStyleWord(true);
		TransparentTextArea->setText(Message);
        TransparentTextArea->setEditable(false);
	endEditCP(TransparentTextArea, TextArea::BordersFieldMask | TextArea::BackgroundsFieldMask | TextArea::TextFieldMask | TextArea::EditableFieldMask);

	return TransparentTextArea;
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DialogWindow::DialogWindow(void) :
    Inherited()
{
}

DialogWindow::DialogWindow(const DialogWindow &source) :
    Inherited(source)
{
}

DialogWindow::~DialogWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DialogWindow::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DialogWindow::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DialogWindow NI" << std::endl;
}

OSG_END_NAMESPACE

