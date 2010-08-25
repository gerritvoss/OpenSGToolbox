/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com), Mark Stenerson             *
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

#include "OSGDialogWindow.h"
#include "OSGComponentContainer.h"
#include "OSGDefaultMutableComboBoxModel.h"
#include "OSGPanel.h"
#include "OSGUIDrawingSurface.h"
#include "OSGFlowLayout.h"
#include "OSGLayoutSpring.h"
#include "OSGSpringLayout.h"
#include "OSGSpringLayoutConstraints.h"
#include "OSGImageComponent.h"
#include "OSGEmptyBorder.h"
#include "OSGLineBorder.h"
#include "OSGEmptyLayer.h"
#include "OSGDialogWindow.h"

#include "OSGSpinner.h"

#include "OSGBorderLayout.h"
#include "OSGBorderLayoutConstraints.h"

#include "OSGBorderLayout.h"
#include "OSGBorderLayoutConstraints.h"
#include "OSGScrollPanel.h"

#include "OSGTextArea.h"
#include "OSGButton.h"

#include "OSGComboBox.h"
#include "OSGTextField.h"
#include "OSGList.h"
#include "OSGColorChooser.h"


OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDialogWindowBase.cpp file.
// To modify it, please change the .fcd file (OSGDialogWindow.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DialogWindow::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void DialogWindow::close(UInt32 intOption,
                         std::string strInput,
                         UInt32 intInputIndex)
{
    _VetoWindowClose = false;

    produceDialogWindowClosing(intOption,strInput,intInputIndex);
    produceWindowClosing();

    if(!_VetoWindowClose && getParentDrawingSurface() != NULL)
    {
        getParentDrawingSurface()->closeWindow(this);
        produceDialogWindowClosed(intOption,strInput,intInputIndex);
        produceWindowClosed();
    }
}

void DialogWindow::produceDialogWindowClosing(UInt32 intOption,
                                              std::string strInput,
                                              UInt32 intInputIndex)
{
    DialogWindowEventDetailsUnrecPtr Details = DialogWindowEventDetails::create(this,getSystemTime(),intOption,strInput,intInputIndex);

    Inherited::produceDialogWindowClosing(Details);
}

void DialogWindow::produceDialogWindowClosed(UInt32 intOption,
                                             std::string strInput,
                                             UInt32 intInputIndex)
{
    DialogWindowEventDetailsUnrecPtr Details = DialogWindowEventDetails::create(this,getSystemTime(),intOption,strInput,intInputIndex);

    Inherited::produceDialogWindowClosed(Details);
}

DialogWindowUnrecPtr DialogWindow::createButtonsInputDialog(const std::string& Title,
                                              const std::string& Message,
                                              bool showCancel,
                                              const std::vector<std::string>& InputValues,
                                              const std::string& ConfirmBtnText,
                                              const std::string& CancelBtnText)
{
    DialogWindowRefPtr TheDialog = DialogWindow::create();
    TheDialog->_InputType = INPUT_BTNS;

    //Icon
    ImageComponentRefPtr TheIcon = ImageComponent::create();
    LineBorderRefPtr TempIconBorder = LineBorder::create();
    TheIcon->setPreferredSize(Vec2f(45,45));
    TheIcon->setBorders(TempIconBorder);

    //Message Panel
    TextAreaRefPtr MessagePanelText = createTransparentTextArea(Message);

    //Button Panel
    PanelRefPtr ButtonInputPanel = Panel::createEmpty();
    FlowLayoutRefPtr ButtonInputPanelLayout = FlowLayout::create();
    ButtonInputPanel->setLayout(ButtonInputPanelLayout);
    ButtonInputPanel->setPreferredSize(Vec2f(450,75));

    if(showCancel)
    {
        ButtonRefPtr CancelButton = Button::create();
        //Cancel Button
        CancelButton->setText(CancelBtnText);
        CancelButton->setMinSize(CancelButton->getPreferredSize());
        CancelButton->setPreferredSize(CancelButton->getRequestedSize());

        //Attach listener to the Cancel button
        TheDialog->_CancelButtonActionConnection = CancelButton->connectActionPerformed(boost::bind(&DialogWindow::handleCancelButtonAction, TheDialog.get(), _1));

        ButtonInputPanel->pushToChildren(CancelButton);
    }

    SpringLayoutRefPtr DialogLayout = SpringLayout::create();
    TheDialog->pushToChildren(MessagePanelText);
    TheDialog->pushToChildren(TheIcon);
    TheDialog->pushToChildren(ButtonInputPanel);
    TheDialog->setPreferredSize(Vec2f(350.0f,150.0f));
    TheDialog->setTitle(Title);
    TheDialog->setLayout(DialogLayout);

    //Create the input buttons
    ButtonRefPtr InputButton;
    for (std::vector<std::string>::const_iterator it = InputValues.begin(); it!=InputValues.end(); ++it)
    {
        InputButton = Button::create();
        InputButton->setText(*it);
        InputButton->setMinSize(InputButton->getPreferredSize());
        InputButton->setPreferredSize(InputButton->getRequestedSize());
        TheDialog->_InputButtonActionConnection = InputButton->connectActionPerformed(boost::bind(&DialogWindow::handleInputButtonAction, TheDialog.get(), _1));
        ButtonInputPanel->pushToChildren(InputButton);
    }				

    //MessagePanelLayout
    //Icon
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, TheIcon, 10, SpringLayoutConstraints::NORTH_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, TheIcon, LayoutSpring::width(TheIcon));
    DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TheIcon, 10, SpringLayoutConstraints::WEST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, TheIcon, LayoutSpring::height(TheIcon));

    //Message
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, MessagePanelText, 5, SpringLayoutConstraints::NORTH_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MessagePanelText, -5, SpringLayoutConstraints::EAST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MessagePanelText, 10, SpringLayoutConstraints::EAST_EDGE, TheIcon);
    DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, MessagePanelText, 20, SpringLayoutConstraints::NORTH_EDGE, ButtonInputPanel);

    //Input Panel
    DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, ButtonInputPanel, 0, SpringLayoutConstraints::WEST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, ButtonInputPanel, 0, SpringLayoutConstraints::EAST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, ButtonInputPanel, 20, SpringLayoutConstraints::SOUTH_EDGE, TheDialog);

    return TheDialog;
}

DialogWindowUnrecPtr DialogWindow::createComboInputDialog(const std::string& Title,
                                              const std::string& Message,
                                              bool showCancel,
                                              const std::vector<std::string>& InputValues,
                                              const std::string& ConfirmBtnText,
                                              const std::string& CancelBtnText)
{
    DialogWindowRefPtr TheDialog = DialogWindow::create();
    TheDialog->_InputType = INPUT_COMBO;

    //Icon
    ImageComponentRefPtr TheIcon = ImageComponent::create();
    LineBorderRefPtr TempIconBorder = LineBorder::create();
    TheIcon->setPreferredSize(Vec2f(45,45));
    TheIcon->setBorders(TempIconBorder);

    //Confirm Button
    ButtonRefPtr ConfirmationButton = Button::create();
    ConfirmationButton->setText(ConfirmBtnText);
    ConfirmationButton->setMinSize(ConfirmationButton->getPreferredSize());
    ConfirmationButton->setPreferredSize(ConfirmationButton->getRequestedSize());
    TheDialog->_ComboButtonActionConnection = ConfirmationButton->connectActionPerformed(boost::bind(&DialogWindow::handleComboButtonAction, TheDialog.get(), _1));

    //Message Panel
    TextAreaRefPtr MessagePanelText = createTransparentTextArea(Message);

    // Create Panel for bottom half of SplitPanel
    PanelRefPtr MessageButtonPanel;
    MessageButtonPanel = Panel::createEmpty();
    LayoutRefPtr MessagePanelBottomLayout = FlowLayout::create();
    MessageButtonPanel->pushToChildren(ConfirmationButton);
    MessageButtonPanel->setLayout(MessagePanelBottomLayout);
    MessageButtonPanel->setPreferredSize(Vec2f(450,75));

    //Cancel Button
    if(showCancel) 
    {
        ButtonRefPtr CancelButton = Button::create();
        //Cancel Button
        CancelButton->setText(CancelBtnText);
        CancelButton->setMinSize(CancelButton->getPreferredSize());
        CancelButton->setPreferredSize(CancelButton->getRequestedSize());

        //Attach listener to the Cancel button
        TheDialog->_CancelButtonActionConnection = CancelButton->connectActionPerformed(boost::bind(&DialogWindow::handleCancelButtonAction, TheDialog.get(), _1));
        MessageButtonPanel->pushToChildren(CancelButton);
    }

    //Create the ComboBox
    TheDialog->_InputComboBox = ComboBox::create();
    DefaultMutableComboBoxModelRefPtr InputComboBoxModel;
    InputComboBoxModel = DefaultMutableComboBoxModel::create();

    for (std::vector<std::string>::const_iterator it = InputValues.begin(); it!=InputValues.end(); ++it)
    {
        InputComboBoxModel->addElement(boost::any(std::string(*it)));
    }

    TheDialog->_InputComboBox->setPreferredSize(Vec2f(150, 23));
    TheDialog->_InputComboBox->setModel(InputComboBoxModel);
    TheDialog->_InputComboBox->setSelectedIndex(0);

    //Dialog Window
    SpringLayoutRefPtr DialogLayout = SpringLayout::create();
    TheDialog->pushToChildren(MessagePanelText);
    TheDialog->pushToChildren(TheIcon);
    TheDialog->pushToChildren(MessageButtonPanel);
    TheDialog->pushToChildren(TheDialog->_InputComboBox);
    TheDialog->setPreferredSize(Vec2f(350.0f,175.0f));
    TheDialog->setTitle(Title);
    TheDialog->setLayout(DialogLayout);

    //DialogLayout
    //Icon
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, TheIcon, 10, SpringLayoutConstraints::NORTH_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, TheIcon, LayoutSpring::width(TheIcon));
    DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TheIcon, 10, SpringLayoutConstraints::WEST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, TheIcon, LayoutSpring::height(TheIcon));

    //Message
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, MessagePanelText, 5, SpringLayoutConstraints::NORTH_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MessagePanelText, -5, SpringLayoutConstraints::EAST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MessagePanelText, 10, SpringLayoutConstraints::EAST_EDGE, TheIcon);
    DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, MessagePanelText, 20, SpringLayoutConstraints::NORTH_EDGE, TheDialog->_InputComboBox);

    //ComboBox
    DialogLayout->putConstraint(SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, TheDialog->_InputComboBox, 0, SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, TheDialog->_InputComboBox, -20, SpringLayoutConstraints::NORTH_EDGE, MessageButtonPanel);

    //Button Panel
    DialogLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, MessageButtonPanel, LayoutSpring::height(MessageButtonPanel));
    DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MessageButtonPanel, 0, SpringLayoutConstraints::WEST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MessageButtonPanel, 0, SpringLayoutConstraints::EAST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, MessageButtonPanel, 20, SpringLayoutConstraints::SOUTH_EDGE, TheDialog);

    return TheDialog;
}

DialogWindowUnrecPtr DialogWindow::createTextInputDialog(const std::string& Title,
                                              const std::string& Message,
                                              bool showCancel,
                                              const std::vector<std::string>& InputValues,
                                              const std::string& ConfirmBtnText,
                                              const std::string& CancelBtnText)
{
    DialogWindowRefPtr TheDialog = DialogWindow::create();
    TheDialog->_InputType = INPUT_TEXT;

    //Icon
    ImageComponentRefPtr TheIcon = ImageComponent::create();
    LineBorderRefPtr TempIconBorder = LineBorder::create();
    TheIcon->setPreferredSize(Vec2f(45,45));
    TheIcon->setBorders(TempIconBorder);

    //Confirm Button
    ButtonRefPtr ConfirmationButton = Button::create();
    ConfirmationButton->setText(ConfirmBtnText);
    ConfirmationButton->setMinSize(ConfirmationButton->getPreferredSize());
    ConfirmationButton->setPreferredSize(ConfirmationButton->getRequestedSize());
    TheDialog->_TextButtonActionConnection = ConfirmationButton->connectActionPerformed(boost::bind(&DialogWindow::handleTextButtonAction, TheDialog.get(), _1));

    //Message Panel
    TextAreaRefPtr MessagePanelText = createTransparentTextArea(Message);

    // Create Panel for bottom half of SplitPanel
    PanelRefPtr MessageButtonPanel;
    MessageButtonPanel = Panel::createEmpty();
    LayoutRefPtr MessagePanelBottomLayout = FlowLayout::create();
    MessageButtonPanel->pushToChildren(ConfirmationButton);
    MessageButtonPanel->setLayout(MessagePanelBottomLayout);
    MessageButtonPanel->setPreferredSize(Vec2f(450,75));

    //Cancel Button
    if(showCancel) 
    {
        ButtonRefPtr CancelButton = Button::create();
        //Cancel Button
        CancelButton->setText(CancelBtnText);
        CancelButton->setMinSize(CancelButton->getPreferredSize());
        CancelButton->setPreferredSize(CancelButton->getRequestedSize());

        //Attach listener to the Cancel button
        TheDialog->_CancelButtonActionConnection = CancelButton->connectActionPerformed(boost::bind(&DialogWindow::handleCancelButtonAction, TheDialog.get(), _1));
        MessageButtonPanel->pushToChildren(CancelButton);
    }

    //Create the TextField
    TheDialog->_InputTextField = TextField::create();
    TheDialog->_InputTextField->setText(InputValues[0]);
    TheDialog->_InputTextField->setPreferredSize(Vec2f(200,25));

    //Dialog Window
    SpringLayoutRefPtr DialogLayout = SpringLayout::create();
    TheDialog->pushToChildren(MessagePanelText);
    TheDialog->pushToChildren(TheIcon);
    TheDialog->pushToChildren(MessageButtonPanel);
    TheDialog->pushToChildren(TheDialog->_InputTextField);
    TheDialog->setPreferredSize(Vec2f(350.0f,175.0f));
    TheDialog->setTitle(Title);
    TheDialog->setLayout(DialogLayout);

    //DialogLayout
    //Icon
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, TheIcon, 10, SpringLayoutConstraints::NORTH_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, TheIcon, LayoutSpring::width(TheIcon));
    DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TheIcon, 10, SpringLayoutConstraints::WEST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, TheIcon, LayoutSpring::height(TheIcon));

    //Message
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, MessagePanelText, 5, SpringLayoutConstraints::NORTH_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MessagePanelText, -5, SpringLayoutConstraints::EAST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MessagePanelText, 10, SpringLayoutConstraints::EAST_EDGE, TheIcon);
    DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, MessagePanelText, 20, SpringLayoutConstraints::NORTH_EDGE, TheDialog->_InputTextField);

    //TextField
    DialogLayout->putConstraint(SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, TheDialog->_InputTextField, 0, SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, TheDialog->_InputTextField, -20, SpringLayoutConstraints::NORTH_EDGE, MessageButtonPanel);

    //Button Panel
    DialogLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, MessageButtonPanel, LayoutSpring::height(MessageButtonPanel));
    DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MessageButtonPanel, 0, SpringLayoutConstraints::WEST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MessageButtonPanel, 0, SpringLayoutConstraints::EAST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, MessageButtonPanel, 20, SpringLayoutConstraints::SOUTH_EDGE, TheDialog);

    return TheDialog;
}

DialogWindowUnrecPtr DialogWindow::createListInputDialog(const std::string& Title,
                                              const std::string& Message,
                                              bool showCancel,
                                              const std::vector<std::string>& InputValues,
                                              const std::string& ConfirmBtnText,
                                              const std::string& CancelBtnText)
{
    DialogWindowRefPtr TheDialog = DialogWindow::create();
    TheDialog->_InputType = INPUT_TEXT;

    //Icon
    ImageComponentRefPtr TheIcon = ImageComponent::create();
    LineBorderRefPtr TempIconBorder = LineBorder::create();
    TheIcon->setPreferredSize(Vec2f(45,45));
    TheIcon->setBorders(TempIconBorder);

    //Confirm Button
    ButtonRefPtr ConfirmationButton = Button::create();
    ConfirmationButton->setText(ConfirmBtnText);
    ConfirmationButton->setMinSize(ConfirmationButton->getPreferredSize());
    ConfirmationButton->setPreferredSize(ConfirmationButton->getRequestedSize());
    TheDialog->_ListButtonActionConnection = ConfirmationButton->connectActionPerformed(boost::bind(&DialogWindow::handleListButtonAction, TheDialog.get(), _1));

    //Message Panel
    TextAreaRefPtr MessagePanelText = createTransparentTextArea(Message);

    // Create Panel for bottom half of SplitPanel
    PanelRefPtr MessageButtonPanel;
    MessageButtonPanel = Panel::createEmpty();
    LayoutRefPtr MessagePanelBottomLayout = FlowLayout::create();
    MessageButtonPanel->pushToChildren(ConfirmationButton);
    MessageButtonPanel->setLayout(MessagePanelBottomLayout);
    MessageButtonPanel->setPreferredSize(Vec2f(450,75));

    //Cancel Button
    if(showCancel) 
    {
        ButtonRefPtr CancelButton = Button::create();
        //Cancel Button
        CancelButton->setText(CancelBtnText);
        CancelButton->setMinSize(CancelButton->getPreferredSize());
        CancelButton->setPreferredSize(CancelButton->getRequestedSize());

        //Attach listener to the Cancel button
        TheDialog->_CancelButtonActionConnection = CancelButton->connectActionPerformed(boost::bind(&DialogWindow::handleCancelButtonAction, TheDialog.get(), _1));
        MessageButtonPanel->pushToChildren(CancelButton);
    }

    TheDialog->_InputList = List::create();
    DefaultMutableComboBoxModelRefPtr _InputComboBoxModel;
    _InputComboBoxModel = DefaultMutableComboBoxModel::create();

    for (std::vector<std::string>::const_iterator it = InputValues.begin(); it!=InputValues.end(); ++it)
    {
        _InputComboBoxModel->addElement(boost::any(std::string(*it)));
    }

    TheDialog->_InputList->setPreferredSize(Vec2f(200.0f, 23.0f));
    TheDialog->_InputList->setModel(_InputComboBoxModel);
    TheDialog->_InputList->setSelectedIndex(0);

    // Create a ScrollPanel for easier viewing of the List (see 27ScrollPanel)
    ScrollPanelRefPtr ListScrollPanel = ScrollPanel::create();
    ListScrollPanel->setPreferredSize(Vec2f(170.0f,200.0f));
    ListScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    ListScrollPanel->setViewComponent(TheDialog->_InputList);

    //Dialog Window
    SpringLayoutRefPtr DialogLayout = SpringLayout::create();
    TheDialog->pushToChildren(MessagePanelText);
    TheDialog->pushToChildren(TheIcon);
    TheDialog->pushToChildren(MessageButtonPanel);
    TheDialog->pushToChildren(ListScrollPanel);
    TheDialog->setPreferredSize(Vec2f(350.0f,280.0f));
    TheDialog->setTitle(Title);
    TheDialog->setLayout(DialogLayout);

    //DialogLayout
    //Icon
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, TheIcon, 10, SpringLayoutConstraints::NORTH_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, TheIcon, LayoutSpring::width(TheIcon));
    DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TheIcon, 10, SpringLayoutConstraints::WEST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, TheIcon, LayoutSpring::height(TheIcon));

    //Message
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, MessagePanelText, 5, SpringLayoutConstraints::NORTH_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MessagePanelText, -5, SpringLayoutConstraints::EAST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MessagePanelText, 10, SpringLayoutConstraints::EAST_EDGE, TheIcon);
    DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, MessagePanelText, 0, SpringLayoutConstraints::SOUTH_EDGE, TheIcon);

    //List
    DialogLayout->putConstraint(SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, ListScrollPanel, 0, SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, ListScrollPanel, 20, SpringLayoutConstraints::SOUTH_EDGE, MessagePanelText);
    DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, ListScrollPanel, -20, SpringLayoutConstraints::NORTH_EDGE, MessageButtonPanel);

    //Button Panel
    DialogLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, MessageButtonPanel, LayoutSpring::height(MessageButtonPanel));
    DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MessageButtonPanel, 0, SpringLayoutConstraints::WEST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MessageButtonPanel, 0, SpringLayoutConstraints::EAST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, MessageButtonPanel, 20, SpringLayoutConstraints::SOUTH_EDGE, TheDialog);

    return TheDialog;
}

DialogWindowUnrecPtr DialogWindow::createInputDialog(const std::string& Title,
                                                     const std::string& Message,
                                                     UInt32 Type,
                                                     bool showCancel,
                                                     const std::vector<std::string>& InputValues,
                                                     const std::string& ConfirmBtnText,
                                                     const std::string& CancelBtnText)
{
    switch(Type)
    {
        case INPUT_COMBO:
            return createComboInputDialog(Title,
                                          Message,
                                          showCancel,
                                          InputValues,
                                          ConfirmBtnText,
                                          CancelBtnText);
            break;
        case INPUT_TEXT:
            return createTextInputDialog(Title,
                                         Message,
                                         showCancel,
                                         InputValues,
                                         ConfirmBtnText,
                                         CancelBtnText);
            break;
        case INPUT_LIST:
            return createListInputDialog(Title,
                                         Message,
                                         showCancel,
                                         InputValues,
                                         ConfirmBtnText,
                                         CancelBtnText);
            break;
        case INPUT_BTNS:
        default:
            return createButtonsInputDialog(Title,
                                            Message,
                                            showCancel,
                                            InputValues,
                                            ConfirmBtnText,
                                            CancelBtnText);
        break;
    }
}

DialogWindowUnrecPtr DialogWindow::createMessageDialog(const std::string& Title, const std::string& Message, bool showCancel, const std::string& ConfirmBtnText, const std::string& CancelBtnText)
{

    ImageComponentRefPtr TheIcon = ImageComponent::create();
    LineBorderRefPtr TempIconBorder = LineBorder::create();
    TheIcon->setPreferredSize(Vec2f(45,45));
    TheIcon->setBorders(TempIconBorder);

    ButtonRefPtr ConfirmationButton = Button::create();
    ButtonRefPtr CancelButton;

    //Confirm Button
    ConfirmationButton->setText(ConfirmBtnText);
    ConfirmationButton->setMinSize(ConfirmationButton->getPreferredSize());
    ConfirmationButton->setPreferredSize(ConfirmationButton->getRequestedSize());

    if(showCancel)
    {
        //Cancel Button
        CancelButton = Button::create();
        CancelButton->setText(CancelBtnText);
        CancelButton->setMinSize(CancelButton->getPreferredSize());
        CancelButton->setPreferredSize(CancelButton->getRequestedSize());
    }

    // Create Panel for top half of SplitPanel
    TextAreaRefPtr MessagePanelText = createTransparentTextArea(Message);

    // Create Panel for bottom half of SplitPanel
    PanelRefPtr MessageButtonPanel = Panel::createEmpty();
    FlowLayoutRefPtr MessagePanelBottomLayout = FlowLayout::create();
    MessageButtonPanel->pushToChildren(ConfirmationButton);
    if(showCancel) 
    {
        MessageButtonPanel->pushToChildren(CancelButton);
    }
    MessageButtonPanel->setLayout(MessagePanelBottomLayout);
    MessageButtonPanel->setPreferredSize(Vec2f(450,75));

    // Create SplitPanel itself
    PanelRefPtr MessagePanel = Panel::createEmpty();
    SpringLayoutRefPtr MessagePanelLayout = SpringLayout::create();
    MessagePanel->pushToChildren(MessagePanelText);
    MessagePanel->pushToChildren(TheIcon);
    MessagePanel->pushToChildren(MessageButtonPanel);
    MessagePanel->setLayout(MessagePanelLayout);


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
    BorderLayoutConstraintsRefPtr MessagePanelConstraints = BorderLayoutConstraints::create();
    MessagePanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);

    MessagePanel->setConstraints(MessagePanelConstraints);

    BorderLayoutRefPtr DialogLayout = BorderLayout::create();

    //Create the Dialog box
    DialogWindowRefPtr TheDialog = DialogWindow::create();
    TheDialog->_InputType = INPUT_MESSAGE;
    TheDialog->setLayout(DialogLayout);
    TheDialog->setPreferredSize(Vec2f(350,150));
    TheDialog->pushToChildren(MessagePanel);
    TheDialog->setTitle(Title);

    //Attach listener to the Confirm button
    TheDialog->_ConfirmButtonActionConnection = ConfirmationButton->connectActionPerformed(boost::bind(&DialogWindow::handleConfirmButtonAction, TheDialog.get(), _1));

    if(showCancel)
    {
        //Attach listener to the Cancel button
        TheDialog->_CancelButtonActionConnection = CancelButton->connectActionPerformed(boost::bind(&DialogWindow::handleCancelButtonAction, TheDialog.get(), _1));
    }

    return TheDialog;
}

void DialogWindow::handleConfirmButtonAction(ActionEventDetails* const e)
{
    close(DialogWindowEventDetails::DIALOG_OPTION_OK,"",0);
}

void DialogWindow::handleCancelButtonAction(ActionEventDetails* const e)
{
    close(DialogWindowEventDetails::DIALOG_OPTION_CANCEL,"",0);
}

void DialogWindow::handleInputButtonAction(ActionEventDetails* const e)
{
    close(DialogWindowEventDetails::DIALOG_OPTION_OK,dynamic_cast<Button*>(e->getSource())->getText(),0);
}

void DialogWindow::handleListButtonAction(ActionEventDetails* const e)
{
    close(DialogWindowEventDetails::DIALOG_OPTION_OK,
                         boost::any_cast<std::string>(_InputList->getSelectedItem()),
                         _InputList->getSelectedIndex());
}

void DialogWindow::handleComboButtonAction(ActionEventDetails* const e)
{
    close(DialogWindowEventDetails::DIALOG_OPTION_OK,
                         boost::any_cast<std::string>(_InputComboBox->getSelectedItem()),
                         _InputComboBox->getSelectedIndex());
}

void DialogWindow::handleTextButtonAction(ActionEventDetails* const e)
{
    close(DialogWindowEventDetails::DIALOG_OPTION_OK,_InputTextField->getText(),0);
}

TextAreaTransitPtr DialogWindow::createTransparentTextArea(const std::string& Message)
{
    TextAreaRefPtr TransparentTextArea = TextArea::create();
    EmptyLayerRefPtr TransparentTextAreaBackground = EmptyLayer::create();
    EmptyBorderRefPtr TransparentTextAreaBorder = EmptyBorder::create();

    TransparentTextArea->setBorders(TransparentTextAreaBorder);
    TransparentTextArea->setBackgrounds(TransparentTextAreaBackground);
    TransparentTextArea->setWrapStyleWord(true);
    TransparentTextArea->setText(Message);
    TransparentTextArea->setEditable(false);

    return TextAreaTransitPtr(TransparentTextArea);
}

DialogWindowUnrecPtr DialogWindow::createColorChooserDialog(const std::string& Title, 
                                                           const std::string& Message, 
                                                           bool showAlpha,
                                                           ColorSelectionModel* const colorModel,
                                                           bool showCancel, 
                                                           const std::string& ConfirmBtnText, 
                                                           const std::string& CancelBtnText)
{
    ButtonRefPtr ConfirmationButton = Button::create();
    ButtonRefPtr CancelButton;

    //Confirm Button
    ConfirmationButton->setText(ConfirmBtnText);
    ConfirmationButton->setMinSize(ConfirmationButton->getPreferredSize());
    ConfirmationButton->setPreferredSize(ConfirmationButton->getRequestedSize());

    if(showCancel)
    {
        //Cancel Button
        CancelButton = Button::create();
        CancelButton->setText(CancelBtnText);
        CancelButton->setMinSize(CancelButton->getPreferredSize());
        CancelButton->setPreferredSize(CancelButton->getRequestedSize());
    }

    // Create Panel for top half of SplitPanel
    TextAreaRefPtr MessagePanelText = TextArea::create();

    MessagePanelText->setBorders(NULL);
    MessagePanelText->setPreferredSize(Vec2f(100.0f, 100.0f));
    MessagePanelText->setBackgrounds(NULL);
    MessagePanelText->setWrapStyleWord(true);
    MessagePanelText->setText(Message);
    MessagePanelText->setEditable(false);

    // Create Panel for bottom half of SplitPanel
    PanelRefPtr MessageButtonPanel = Panel::createEmpty();
    FlowLayoutRefPtr MessagePanelBottomLayout = FlowLayout::create();
    MessageButtonPanel->pushToChildren(ConfirmationButton);
    if(showCancel) 
        MessageButtonPanel->pushToChildren(CancelButton);
    MessageButtonPanel->setLayout(MessagePanelBottomLayout);
    MessageButtonPanel->setPreferredSize(Vec2f(450,75));

    PanelRefPtr MessagePanel = Panel::createEmpty();
    SpringLayoutRefPtr MessagePanelLayout = SpringLayout::create();
    MessagePanel->pushToChildren(MessagePanelText);
    MessagePanel->pushToChildren(MessageButtonPanel);
    MessagePanel->setLayout(MessagePanelLayout);


    ColorChooserRefPtr TheColorChooser = ColorChooser::create();
    TheColorChooser->setSelectionModel(colorModel);

    //Internals Layout and constraints

    DialogWindowUnrecPtr TheDialog = DialogWindow::create();
    SpringLayoutRefPtr DialogLayout = SpringLayout::create();

    //Message Text
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, MessagePanelText, 5, SpringLayoutConstraints::NORTH_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MessagePanelText, -5, SpringLayoutConstraints::EAST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MessagePanelText, 5, SpringLayoutConstraints::WEST_EDGE, TheDialog);

    //Color Chooser
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, TheColorChooser, 5, SpringLayoutConstraints::SOUTH_EDGE, MessagePanelText);
    DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, TheColorChooser, -5, SpringLayoutConstraints::EAST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TheColorChooser, 5, SpringLayoutConstraints::WEST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, TheColorChooser, -5, SpringLayoutConstraints::NORTH_EDGE, MessageButtonPanel);

    //Button Panel
    DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MessageButtonPanel, 0, SpringLayoutConstraints::WEST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MessageButtonPanel, 0, SpringLayoutConstraints::EAST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, MessageButtonPanel, 20, SpringLayoutConstraints::SOUTH_EDGE, TheDialog);

    //Create the Dialog box
    TheDialog->setLayout(DialogLayout);
    TheDialog->setPreferredSize(Vec2f(350,400));
    TheDialog->pushToChildren(MessagePanelText);
    TheDialog->pushToChildren(TheColorChooser);
    TheDialog->pushToChildren(MessageButtonPanel);
    TheDialog->setTitle(Title);

    //Attach listener to the Confirm button
    TheDialog->_ConfirmButtonActionConnection = ConfirmationButton->connectActionPerformed(boost::bind(&DialogWindow::handleConfirmButtonAction, TheDialog.get(), _1));

    if(showCancel)
    {
        //Attach listener to the Cancel button
        TheDialog->_CancelButtonActionConnection = CancelButton->connectActionPerformed(boost::bind(&DialogWindow::handleCancelButtonAction, TheDialog.get(), _1));
    }

    return DialogWindowTransitPtr(TheDialog);
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

void DialogWindow::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DialogWindow::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DialogWindow NI" << std::endl;
}

OSG_END_NAMESPACE
