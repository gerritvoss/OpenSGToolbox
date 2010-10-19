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

void SearchWindow::close(UInt32 intOption,
                         std::string searchText,
						 std::string replaceText)
{
    _VetoWindowClose = false;

    produceSearchWindowClosing(intOption,searchText,replaceText);
    produceWindowClosing();

    if(!_VetoWindowClose && getDrawingSurface() != NULL)
    {
        getDrawingSurface()->closeWindow(SearchWindowRefPtr(this));
        produceSearchWindowClosed(intOption,searchText,replaceText);
        produceWindowClosed();
    }
}

void SearchWindow::produceSearchWindowClosing(UInt32 intOption,
                                              std::string searchText,
											  std::string replaceText)
{
    const SearchWindowEventUnrecPtr TheEvent = SearchWindowEvent::create(this,getSystemTime(),intOption,searchText,replaceText);
    for(SearchWindowListenerSetConstItor SetItor(_SearchWindowListeners.begin()) ; SetItor != _SearchWindowListeners.end() ; ++SetItor)
    {
        (*SetItor)->dialogClosing(TheEvent);
    }
    _Producer.produceEvent(SearchWindowClosingMethodId,TheEvent);
}

void SearchWindow::produceSearchWindowClosed(UInt32 intOption,
                                             std::string searchText,
											  std::string replaceText)
{
    const SearchWindowEventUnrecPtr TheEvent = SearchWindowEvent::create(this,getSystemTime(),intOption,searchText,replaceText);
    for(SearchWindowListenerSetConstItor SetItor(_SearchWindowListeners.begin()) ; SetItor != _SearchWindowListeners.end() ; ++SetItor)
    {
        (*SetItor)->dialogClosed(TheEvent);
    }
    _Producer.produceEvent(SearchWindowClosedMethodId,TheEvent);
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
                                                  const std::vector<std::string>& InputValues,
                                                  const std::string& SearchBtnText,
                                                  const std::string& ReplaceBtnText)
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
    SearchButton->setText(SearchBtnText);
    SearchButton->setMinSize(SearchButton->getPreferredSize());
    SearchButton->setPreferredSize(SearchButton->getRequestedSize());
    SearchButton->addActionListener(&TheDialog->_SearchButtonListener);

	//Replace Button
    ButtonRefPtr ReplaceButton = Button::create();
    ReplaceButton->setText(ReplaceBtnText);
    ReplaceButton->setMinSize(ReplaceButton->getPreferredSize());
    ReplaceButton->setPreferredSize(ReplaceButton->getRequestedSize());
    ReplaceButton->addActionListener(&TheDialog->_ReplaceButtonListener);
    

    //Message Panel
    /*TextAreaRefPtr MessagePanelText = createTransparentTextArea(Message);*/

    // Create Panel for bottom half of SplitPanel
    PanelRefPtr MessageButtonPanel;
    MessageButtonPanel = Panel::createEmpty();
    LayoutRefPtr MessagePanelBottomLayout = FlowLayout::create();
    MessageButtonPanel->pushToChildren(SearchButton);
	MessageButtonPanel->pushToChildren(ReplaceButton);
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

    //Create the TextField
    TheDialog->_SearchTextField = TextField::create();
    TheDialog->_SearchTextField->setText(InputValues[0]);
    TheDialog->_SearchTextField->setPreferredSize(Vec2f(200,20));

	//Create the TextField
    TheDialog->_ReplaceTextField = TextField::create();
    TheDialog->_ReplaceTextField->setText(InputValues[1]);
    TheDialog->_ReplaceTextField->setPreferredSize(Vec2f(200,20));


    //Dialog Window
    SpringLayoutRefPtr DialogLayout = SpringLayout::create();
    //TheDialog->pushToChildren(MessagePanelText);
    //TheDialog->pushToChildren(TheIcon);
    TheDialog->pushToChildren(MessageButtonPanel);
	TheDialog->pushToChildren(SearchLabel);
	TheDialog->pushToChildren(ReplaceLabel);
    TheDialog->pushToChildren(TheDialog->_SearchTextField);
	TheDialog->pushToChildren(TheDialog->_ReplaceTextField);
    TheDialog->setPreferredSize(Vec2f(350.0f,175.0f));
    TheDialog->setTitle(Title);
    TheDialog->setLayout(DialogLayout);

    //DialogLayout
    //Icon
    //DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, TheIcon, 10, SpringLayoutConstraints::NORTH_EDGE, TheDialog);
    //DialogLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, TheIcon, LayoutSpring::width(TheIcon));
    //DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TheIcon, 10, SpringLayoutConstraints::WEST_EDGE, TheDialog);
    //DialogLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, TheIcon, LayoutSpring::height(TheIcon));

    //Message
    /*DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, MessagePanelText, 5, SpringLayoutConstraints::NORTH_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, MessagePanelText, -5, SpringLayoutConstraints::EAST_EDGE, TheDialog);
    DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, MessagePanelText, 10, SpringLayoutConstraints::EAST_EDGE, TheIcon);
    DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, MessagePanelText, 20, SpringLayoutConstraints::NORTH_EDGE, TheDialog->_InputTextField);*/

    //TextField
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, TheDialog->_SearchTextField, 10, SpringLayoutConstraints::NORTH_EDGE, TheDialog);
	DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, TheDialog->_SearchTextField, -5, SpringLayoutConstraints::EAST_EDGE, TheDialog);
	DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TheDialog->_SearchTextField, 5, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, TheDialog);
	DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, TheDialog->_SearchTextField, 30, SpringLayoutConstraints::NORTH_EDGE, TheDialog);

	//TextField
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, TheDialog->_ReplaceTextField, 50, SpringLayoutConstraints::NORTH_EDGE, TheDialog);
	DialogLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, TheDialog->_ReplaceTextField, -5, SpringLayoutConstraints::EAST_EDGE, TheDialog);
	DialogLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, TheDialog->_ReplaceTextField, 5, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, TheDialog);
	DialogLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, TheDialog->_ReplaceTextField, 70, SpringLayoutConstraints::NORTH_EDGE, TheDialog);

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


    //Button Panel
    DialogLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, MessageButtonPanel, 90, SpringLayoutConstraints::NORTH_EDGE, TheDialog);
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
	std::cout<<"Searching... "<<std::endl;
}

SearchWindow::ReplaceButtonListener::ReplaceButtonListener(SearchWindowRefPtr TheDialogWindow) : _DialogWindow(TheDialogWindow)
{
}

void SearchWindow::ReplaceButtonListener::actionPerformed(const ActionEventUnrecPtr e)
{
    //_DialogWindow->close(SearchWindowEvent::DIALOG_OPTION_REPLACE,"",0);
	std::cout<<"Replacing ... "<<std::endl;
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
    Inherited()
{
}

SearchWindow::SearchWindow(const SearchWindow &source) :
	_SearchButtonListener(this),
	_ReplaceButtonListener(this),
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
