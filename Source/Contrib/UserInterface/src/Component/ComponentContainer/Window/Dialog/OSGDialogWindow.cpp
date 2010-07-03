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
#include "OSGActionListener.h"

#include "OSGSpinner.h"

#include "OSGBorderLayout.h"
#include "OSGBorderLayoutConstraints.h"

#include "OSGBorderLayout.h"
#include "OSGBorderLayoutConstraints.h"

#include <boost/bind.hpp>

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

void DialogWindow::close(UInt32 intOption, std::string strInput)
{
    _VetoWindowClose = false;

    produceDialogWindowClosing(intOption,strInput);
    produceWindowClosing();

    if(!_VetoWindowClose && getParentDrawingSurface() != NULL)
    {
        DialogWindowWeakPtr temp(this);

        getParentDrawingSurface()->closeWindow(this);
        produceDialogWindowClosed(intOption,strInput);
        produceWindowClosed();
    }
}

void DialogWindow::produceDialogWindowClosing(UInt32 intOption, std::string strInput)
{
    const DialogWindowEventUnrecPtr TheEvent = DialogWindowEvent::create( this,getSystemTime(),intOption,strInput);
    for(DialogWindowListenerSetConstItor SetItor(_DialogWindowListeners.begin()) ; SetItor != _DialogWindowListeners.end() ; ++SetItor)
    {
        (*SetItor)->dialogClosing(TheEvent);
    }
    _Producer.produceEvent(DialogWindowClosingMethodId,TheEvent);
}

void DialogWindow::produceDialogWindowClosed(UInt32 intOption, std::string strInput)
{
    const DialogWindowEventUnrecPtr TheEvent = DialogWindowEvent::create( NULL,getSystemTime(),intOption,strInput);
    for(DialogWindowListenerSetConstItor SetItor(_DialogWindowListeners.begin()) ; SetItor != _DialogWindowListeners.end() ; ++SetItor)
    {
        (*SetItor)->dialogClosed(TheEvent);
    }
    _Producer.produceEvent(DialogWindowClosedMethodId,TheEvent);
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

DialogWindowUnrecPtr DialogWindow::createInputDialog(const std::string& Title, const std::string& Message, const int& Type, const bool& showCancel, const std::vector<std::string>& InputValues, const std::string& ConfirmBtnText, const std::string& CancelBtnText)
{
    int DialogHeight = 175;
    DialogWindowRefPtr TheDialog = DialogWindow::create();

    ImageComponentRefPtr TheIcon = ImageComponent::create();
    LineBorderRefPtr TempIconBorder = OSG::LineBorder::create();
    TheIcon->setPreferredSize(Vec2f(45,45));
    TheIcon->setBorders(TempIconBorder);

    // Create Panel for input
    PanelRefPtr InputPanel = OSG::Panel::createEmpty();
    FlowLayoutRefPtr InputPanelLayout = OSG::FlowLayout::create();
    InputPanel->setLayout(InputPanelLayout);
    InputPanel->setPreferredSize(Vec2f(450,75));

    ButtonRefPtr InputButton;
    switch (Type) {
        case INPUT_TEXT:
            TheDialog->_InputTextField = OSG::TextField::create();
            TheDialog->_InputTextField->setText(InputValues[0]);
            TheDialog->_InputTextField->setPreferredSize(Vec2f(200,25));
            InputPanel->pushToChildren(TheDialog->_InputTextField);
            break;
        case INPUT_BTNS:	
            DialogHeight = 150;
            for (std::vector<std::string>::const_iterator it = InputValues.begin(); it!=InputValues.end(); ++it)
            {
                InputButton = OSG::Button::create();
                InputButton->setText(*it);
                InputButton->setMinSize(InputButton->getPreferredSize());
                InputButton->setPreferredSize(InputButton->getRequestedSize());
                InputButton->addActionListener(&TheDialog->_InputButtonListener);
                InputPanel->pushToChildren(InputButton);
            }				
            break;
        case INPUT_COMBO:
        default:
            TheDialog->_InputComboBox = OSG::ComboBox::create();
            DefaultMutableComboBoxModelRefPtr InputComboBoxModel;
            InputComboBoxModel = DefaultMutableComboBoxModel::create();

            for (std::vector<std::string>::const_iterator it = InputValues.begin(); it!=InputValues.end(); ++it)
            {
                InputComboBoxModel->addElement(boost::any(std::string(*it)));
            }

            TheDialog->_InputComboBox->setPreferredSize(Vec2f(150, 23));
            TheDialog->_InputComboBox->setModel(InputComboBoxModel);
            TheDialog->_InputComboBox->setSelectedIndex(0);

            InputPanel->pushToChildren(TheDialog->_InputComboBox);
            break;
    }

    FlowLayoutRefPtr MessagePanelBottomLayout;
    PanelRefPtr MessageButtonPanel;
    ButtonRefPtr ConfirmationButton;
    ButtonRefPtr CancelButton;


    if(Type != INPUT_BTNS)
    {
        ConfirmationButton = OSG::Button::create();
        //Confirm Button
        ConfirmationButton->setText(ConfirmBtnText);
        ConfirmationButton->setMinSize(ConfirmationButton->getPreferredSize());
        ConfirmationButton->setPreferredSize(ConfirmationButton->getRequestedSize());

        if(Type == INPUT_TEXT)
        {
            ConfirmationButton->addActionListener(&TheDialog->_TextButtonListener);
        }
        else
        {
            ConfirmationButton->addActionListener(&TheDialog->_ComboButtonListener);
        }
    }

    if(showCancel)
    {
        CancelButton = OSG::Button::create();
        //Cancel Button
        CancelButton->setText(CancelBtnText);
        CancelButton->setMinSize(CancelButton->getPreferredSize());
        CancelButton->setPreferredSize(CancelButton->getRequestedSize());

        //Attach listener to the Cancel button
        CancelButton->addActionListener(&TheDialog->_CancelButtonListener);
    }

    // Create Panel for top half of SplitPanel
    TextAreaRefPtr MessagePanelText = createTransparentTextArea(Message);

    //If the type of input is buttons and showCancel is true, just push the cancel button onto the input panel
    if(Type == INPUT_BTNS && showCancel)
    {
        InputPanel->pushToChildren(CancelButton);
    }
    else if(Type != INPUT_BTNS)
    {
        // Create Panel for bottom half of SplitPanel
        MessageButtonPanel = OSG::Panel::createEmpty();
        MessagePanelBottomLayout = OSG::FlowLayout::create();
        MessageButtonPanel->pushToChildren(ConfirmationButton);
        if(showCancel) 
            MessageButtonPanel->pushToChildren(CancelButton);
        MessageButtonPanel->setLayout(MessagePanelBottomLayout);
        MessageButtonPanel->setPreferredSize(Vec2f(450,75));
    } 

    // Create SplitPanel itself
    PanelRefPtr MessagePanel = OSG::Panel::createEmpty();
    SpringLayoutRefPtr MessagePanelLayout = SpringLayout::create();
    MessagePanel->pushToChildren(MessagePanelText);
    MessagePanel->pushToChildren(TheIcon);
    MessagePanel->pushToChildren(InputPanel);
    if(Type != INPUT_BTNS)
        MessagePanel->pushToChildren(MessageButtonPanel);
    MessagePanel->setLayout(MessagePanelLayout);


    //MessagePanelLayout
    //Icon
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, TheIcon, 10.0f, SpringLayoutConstraints::NORTH_EDGE, MessagePanel);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, TheIcon, LayoutSpringUnrecPtr(LayoutSpring::width(TheIcon)));
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TheIcon, 10.0f, SpringLayoutConstraints::WEST_EDGE, MessagePanel);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, TheIcon, LayoutSpringUnrecPtr(LayoutSpring::height(TheIcon)));

    //Message
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, MessagePanelText, 5.0f, SpringLayoutConstraints::NORTH_EDGE, MessagePanel);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MessagePanelText, -5.0f, SpringLayoutConstraints::EAST_EDGE, MessagePanel);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MessagePanelText, 10.0f, SpringLayoutConstraints::EAST_EDGE, TheIcon);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, MessagePanelText, 20.0f, SpringLayoutConstraints::NORTH_EDGE, InputPanel);

    //Input Panel
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, InputPanel, 0.0f, SpringLayoutConstraints::WEST_EDGE, MessagePanel);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, InputPanel, 0.0f, SpringLayoutConstraints::EAST_EDGE, MessagePanel);

    if(Type != INPUT_BTNS)
    {
        MessagePanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, InputPanel, 40, SpringLayoutConstraints::NORTH_EDGE, MessageButtonPanel);
        //Button Panel
        MessagePanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, MessageButtonPanel, LayoutSpringUnrecPtr(LayoutSpring::height(MessageButtonPanel)));
        MessagePanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MessageButtonPanel, 0.0f, SpringLayoutConstraints::WEST_EDGE, MessagePanel);
        MessagePanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MessageButtonPanel, 0.0f, SpringLayoutConstraints::EAST_EDGE, MessagePanel);
        MessagePanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, MessageButtonPanel, 20.0f, SpringLayoutConstraints::SOUTH_EDGE, MessagePanel);
    }
    else
    {
        MessagePanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, InputPanel, 20, SpringLayoutConstraints::SOUTH_EDGE, MessagePanel);
    }

    //Internals Layout and constraints
    BorderLayoutConstraintsRefPtr MessagePanelConstraints = BorderLayoutConstraints::create();
    MessagePanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);

    MessagePanel->setConstraints(MessagePanelConstraints);

    BorderLayoutRefPtr DialogLayout = BorderLayout::create();

    //Create the Dialog box
    TheDialog->setLayout(DialogLayout);
    TheDialog->setPreferredSize(Vec2f(350,DialogHeight));
    TheDialog->pushToChildren(MessagePanel);
    TheDialog->setTitle(Title);

    return TheDialog;
}

DialogWindowUnrecPtr DialogWindow::createMessageDialog(const std::string& Title, const std::string& Message, const int& Type, const bool& showCancel, const std::string& ConfirmBtnText, const std::string& CancelBtnText)
{
    ImageComponentRefPtr TheIcon = ImageComponent::create();
    LineBorderRefPtr TempIconBorder = OSG::LineBorder::create();
    TheIcon->setPreferredSize(Vec2f(45,45));
    TheIcon->setBorders(TempIconBorder);

    ButtonRefPtr ConfirmationButton = OSG::Button::create();
    ButtonRefPtr CancelButton;

    //Confirm Button
    ConfirmationButton->setText(ConfirmBtnText);
    ConfirmationButton->setMinSize(ConfirmationButton->getPreferredSize());
    ConfirmationButton->setPreferredSize(ConfirmationButton->getRequestedSize());

    if(showCancel)
    {
        //Cancel Button
        CancelButton = OSG::Button::create();
        CancelButton->setText(CancelBtnText);
        CancelButton->setMinSize(CancelButton->getPreferredSize());
        CancelButton->setPreferredSize(CancelButton->getRequestedSize());
    }

    // Create Panel for top half of SplitPanel
    TextAreaRefPtr MessagePanelText = createTransparentTextArea(Message);

    // Create Panel for bottom half of SplitPanel
    PanelRefPtr MessageButtonPanel = OSG::Panel::createEmpty();
    FlowLayoutRefPtr MessagePanelBottomLayout = OSG::FlowLayout::create();
    MessageButtonPanel->pushToChildren(ConfirmationButton);
    if(showCancel) 
        MessageButtonPanel->pushToChildren(CancelButton);
    MessageButtonPanel->setLayout(MessagePanelBottomLayout);
    MessageButtonPanel->setPreferredSize(Vec2f(450,75));

    // Create SplitPanel itself
    PanelRefPtr MessagePanel = OSG::Panel::createEmpty();
    SpringLayoutRefPtr MessagePanelLayout = SpringLayout::create();
    MessagePanel->pushToChildren(MessagePanelText);
    MessagePanel->pushToChildren(TheIcon);
    MessagePanel->pushToChildren(MessageButtonPanel);
    MessagePanel->setLayout(MessagePanelLayout);


    //MessagePanelLayout
    //Icon
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, TheIcon, 10.0f, SpringLayoutConstraints::NORTH_EDGE, MessagePanel);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, TheIcon, LayoutSpringUnrecPtr(LayoutSpring::width(TheIcon)));
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TheIcon, 10.0f, SpringLayoutConstraints::WEST_EDGE, MessagePanel);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, TheIcon, LayoutSpringUnrecPtr(LayoutSpring::height(TheIcon)));

    //Message
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, MessagePanelText, 5.0f, SpringLayoutConstraints::NORTH_EDGE, MessagePanel);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MessagePanelText, -5.0f, SpringLayoutConstraints::EAST_EDGE, MessagePanel);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MessagePanelText, 10.0f, SpringLayoutConstraints::EAST_EDGE, TheIcon);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, MessagePanelText, -30.0f, SpringLayoutConstraints::SOUTH_EDGE, MessagePanel);

    //Button Panel
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MessageButtonPanel, 0.0f, SpringLayoutConstraints::WEST_EDGE, MessagePanel);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MessageButtonPanel, 0.0f, SpringLayoutConstraints::EAST_EDGE, MessagePanel);
    MessagePanelLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, MessageButtonPanel, 20.0f, SpringLayoutConstraints::SOUTH_EDGE, MessagePanel);

    //Internals Layout and constraints
    BorderLayoutConstraintsRefPtr MessagePanelConstraints = BorderLayoutConstraints::create();
    MessagePanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);

    MessagePanel->setConstraints(MessagePanelConstraints);

    BorderLayoutRefPtr DialogLayout = BorderLayout::create();

    //Create the Dialog box
    DialogWindowRefPtr TheDialog = DialogWindow::create();
    TheDialog->setLayout(DialogLayout);
    TheDialog->setPreferredSize(Vec2f(350,150));
    TheDialog->pushToChildren(MessagePanel);
    TheDialog->setTitle(Title);

    //Attach listener to the Confirm button
    ConfirmationButton->addActionListener(&TheDialog->_ConfirmButtonListener);

    if(showCancel)
    {
        //Attach listener to the Cancel button
        CancelButton->addActionListener(&TheDialog->_CancelButtonListener);
    }

    return TheDialog;
}

DialogWindow::ConfirmButtonListener::ConfirmButtonListener(DialogWindow* const TheDialogWindow) : _DialogWindow(TheDialogWindow)
{
}

void DialogWindow::ConfirmButtonListener::actionPerformed(const ActionEventUnrecPtr e)
{
    _DialogWindow->close(DialogWindowEvent::DIALOG_OPTION_OK,"");
}

DialogWindow::CancelButtonListener::CancelButtonListener(DialogWindow* const TheDialogWindow) : _DialogWindow(TheDialogWindow)
{
}

void DialogWindow::CancelButtonListener::actionPerformed(const ActionEventUnrecPtr e)
{
    _DialogWindow->close(DialogWindowEvent::DIALOG_OPTION_CANCEL,"");
}

DialogWindow::InputButtonListener::InputButtonListener(DialogWindow* const TheDialogWindow) : _DialogWindow(TheDialogWindow)
{
}

void DialogWindow::InputButtonListener::actionPerformed(const ActionEventUnrecPtr e)
{
    _DialogWindow->close(DialogWindowEvent::DIALOG_OPTION_OK,dynamic_cast<Button*>(e->getSource())->getText());
}


DialogWindow::ComboButtonListener::ComboButtonListener(DialogWindow* const TheDialogWindow) : _DialogWindow(TheDialogWindow)
{
}

void DialogWindow::ComboButtonListener::actionPerformed(const ActionEventUnrecPtr e)
{
    _DialogWindow->close(DialogWindowEvent::DIALOG_OPTION_OK,boost::any_cast<std::string> (_DialogWindow->_InputComboBox->getSelectedItem()));
}

DialogWindow::TextButtonListener::TextButtonListener(DialogWindow* const TheDialogWindow) : _DialogWindow(TheDialogWindow)
{
}

void DialogWindow::TextButtonListener::actionPerformed(const ActionEventUnrecPtr e)
{
    _DialogWindow->close(DialogWindowEvent::DIALOG_OPTION_OK,_DialogWindow->_InputTextField->getText());
}

TextAreaTransitPtr DialogWindow::createTransparentTextArea(const std::string& Message)
{
    TextAreaRefPtr TransparentTextArea = OSG::TextArea::create();
    EmptyLayerRefPtr TransparentTextAreaBackground = OSG::EmptyLayer::create();
    EmptyBorderRefPtr TransparentTextAreaBorder = OSG::EmptyBorder::create();

    TransparentTextArea->setBorders(TransparentTextAreaBorder);
    TransparentTextArea->setBackgrounds(TransparentTextAreaBackground);
    TransparentTextArea->setWrapStyleWord(true);
    TransparentTextArea->setText(Message);
    TransparentTextArea->setEditable(false);

    return TextAreaTransitPtr(TransparentTextArea.get());
}

DialogWindowUnrecPtr DialogWindow::createColorChooserDialog(const std::string& Title, 
                                                           const std::string& Message, 
                                                           bool showAlpha,
                                                           ColorSelectionModelPtr colorModel,
                                                           bool showCancel, 
                                                           const std::string& ConfirmBtnText, 
                                                           const std::string& CancelBtnText)
{
    ButtonRefPtr ConfirmationButton = OSG::Button::create();
    ButtonRefPtr CancelButton;

    //Confirm Button
    ConfirmationButton->setText(ConfirmBtnText);
    ConfirmationButton->setMinSize(ConfirmationButton->getPreferredSize());
    ConfirmationButton->setPreferredSize(ConfirmationButton->getRequestedSize());

    if(showCancel)
    {
        //Cancel Button
        CancelButton = OSG::Button::create();
        CancelButton->setText(CancelBtnText);
        CancelButton->setMinSize(CancelButton->getPreferredSize());
        CancelButton->setPreferredSize(CancelButton->getRequestedSize());
    }

    // Create Panel for top half of SplitPanel
    TextAreaRefPtr MessagePanelText = OSG::TextArea::create();

    MessagePanelText->setBorders(NULL);
    MessagePanelText->setPreferredSize(Vec2f(100.0f, 100.0f));
    MessagePanelText->setBackgrounds(NULL);
    MessagePanelText->setWrapStyleWord(true);
    MessagePanelText->setText(Message);
    MessagePanelText->setEditable(false);

    // Create Panel for bottom half of SplitPanel
    PanelRefPtr MessageButtonPanel = OSG::Panel::createEmpty();
    FlowLayoutRefPtr MessagePanelBottomLayout = OSG::FlowLayout::create();
    MessageButtonPanel->pushToChildren(ConfirmationButton);
    if(showCancel) 
        MessageButtonPanel->pushToChildren(CancelButton);
    MessageButtonPanel->setLayout(MessagePanelBottomLayout);
    MessageButtonPanel->setPreferredSize(Vec2f(450,75));

    PanelRefPtr MessagePanel = OSG::Panel::createEmpty();
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
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, MessagePanelText, 5.0f, SpringLayoutConstraints::NORTH_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MessagePanelText, -5.0f, SpringLayoutConstraints::EAST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MessagePanelText, 5.0f, SpringLayoutConstraints::WEST_EDGE, TheDialog);

    //Color Chooser
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, TheColorChooser, 5.0f, SpringLayoutConstraints::SOUTH_EDGE, MessagePanelText);
    DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, TheColorChooser, -5.0f, SpringLayoutConstraints::EAST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TheColorChooser, 5.0f, SpringLayoutConstraints::WEST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, TheColorChooser, -5.0f, SpringLayoutConstraints::NORTH_EDGE, MessageButtonPanel);

    //Button Panel
    DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MessageButtonPanel, 0.0f, SpringLayoutConstraints::WEST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MessageButtonPanel, 0.0f, SpringLayoutConstraints::EAST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, MessageButtonPanel, 20.0f, SpringLayoutConstraints::SOUTH_EDGE, TheDialog);

    //Create the Dialog box
    TheDialog->setLayout(DialogLayout);
    TheDialog->setPreferredSize(Vec2f(350,400));
    TheDialog->pushToChildren(MessagePanelText);
    TheDialog->pushToChildren(TheColorChooser);
    TheDialog->pushToChildren(MessageButtonPanel);
    TheDialog->setTitle(Title);

    //Attach listener to the Confirm button
    ConfirmationButton->addActionListener(&TheDialog->_ConfirmButtonListener);

    if(showCancel)
    {
        //Attach listener to the Cancel button
        CancelButton->addActionListener(&TheDialog->_CancelButtonListener);
    }

    return DialogWindowTransitPtr(TheDialog);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DialogWindow::DialogWindow(void) :
    Inherited(),
    _ConfirmButtonListener(this),
    _CancelButtonListener(this),
    _InputButtonListener(this),
    _ComboButtonListener(this),
    _TextButtonListener(this)
{
}

DialogWindow::DialogWindow(const DialogWindow &source) :
    Inherited(source),
    _ConfirmButtonListener(this),
    _CancelButtonListener(this),
    _InputButtonListener(this),
    _ComboButtonListener(this),
    _TextButtonListener(this)
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
