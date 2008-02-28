#include "OSGDialogFactory.h"

//#include "Component/Container/Window/OSGInternalWindow.h"
#include "Component/Container/OSGContainer.h"
#include "Component/Button/OSGButton.h"
#include "Component/Container/OSGSplitPanel.h"
#include "Component/Container/OSGPanel.h"
#include "Layout/OSGFlowLayout.h"
#include "Component/Text/OSGLabel.h"
#include "Border/OSGEmptyBorder.h"
#include "Background/OSGEmptyUIBackground.h"
#include "OSGDialogWindow.h"
#include "Event/OSGActionListener.h"

#include "Component/Spinner/OSGSpinner.h"

#include "Layout/OSGBorderLayout.h"
#include "Layout/OSGBorderLayoutConstraints.h"

#include "Component/Container/ColorChooser/OSGColorChooser.h"
#include "Layout/OSGBorderLayout.h"
#include "Layout/OSGBorderLayoutConstraints.h"

OSG_BEGIN_NAMESPACE


DialogFactory *DialogFactory::_the = NULL;

DialogFactory* DialogFactory::the(void)
{
   if(_the == NULL)
   {
      _the = new DialogFactory();
   }
 
   return _the;
}

DialogWindowPtr DialogFactory::createMessageDialog(const std::string& Title, const std::string& Message, const std::string& ConfirmButtonText)
{
	//Internals Container
	ContainerPtr InternalsContainer(createMessagePanel(Message, ConfirmButtonText));

	//Internals Layout and constriants
	BorderLayoutConstraintsPtr InternalsContainerConstraints = BorderLayoutConstraints::create();
	beginEditCP(InternalsContainerConstraints, BorderLayoutConstraints::RegionFieldMask);
		InternalsContainerConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
	endEditCP(InternalsContainerConstraints, BorderLayoutConstraints::RegionFieldMask);

	beginEditCP(InternalsContainer, Container::ConstraintsFieldMask);
		InternalsContainer->setConstraints(InternalsContainerConstraints);
	endEditCP(InternalsContainer, Container::ConstraintsFieldMask);

	BorderLayoutPtr DialogLayout = BorderLayout::create();

	//Create the Dialog box
	DialogWindowPtr TheDialog = DialogWindow::create();
	beginEditCP(TheDialog, DialogWindow::LayoutFieldMask | DialogWindow::ChildrenFieldMask | DialogWindow::TitleFieldMask);
		TheDialog->setLayout(DialogLayout);
		TheDialog->getChildren().addValue(InternalsContainer);
		TheDialog->setTitle(Title);
	endEditCP(TheDialog, DialogWindow::LayoutFieldMask | DialogWindow::ChildrenFieldMask | DialogWindow::TitleFieldMask);

	return TheDialog;
}

LabelPtr DialogFactory::createTransparentLabel(const std::string& Message)
{
	LabelPtr TransparentLabel = osg::Label::create();
	EmptyUIBackgroundPtr TransparentLabelBackground = osg::EmptyUIBackground::create();
	EmptyBorderPtr TransparentLabelBorder = osg::EmptyBorder::create();

	beginEditCP(TransparentLabel, Label::BorderFieldMask | Label::BackgroundFieldMask | Label::TextFieldMask);
		TransparentLabel->setBorder(TransparentLabelBorder);
		TransparentLabel->setBackground(TransparentLabelBackground);
		TransparentLabel->setText(Message);
	endEditCP(TransparentLabel, Label::BorderFieldMask | Label::BackgroundFieldMask | Label::TextFieldMask);

	return TransparentLabel;
}

void DialogFactory::addButtonActionListener(const ActionListener& Listener, const int index)
{
    //TODO: Implement function to allow user to add actionlisteners 
	//to the buttons in an option panel

}
//InternalWindowPtr DialogFactory::createMessageDialog(const std::string& Title, const std::string& Message, const std::string& ConfirmButtonText)
//{
//    //TODO: Implement
//    return NullFC;
//}

ContainerPtr DialogFactory::createMessagePanel(const std::string& Message, const std::string& ConfirmButtonText)
{

	ButtonPtr ConfirmationButton = osg::Button::create();

    beginEditCP(ConfirmationButton, Button::TextFieldMask | Button::PreferredSizeFieldMask);
		ConfirmationButton->setText(ConfirmButtonText);
		ConfirmationButton->setPreferredSizeByContents(0);
	endEditCP(ConfirmationButton, Button::TextFieldMask | Button::PreferredSizeFieldMask);

	// Create Panel for top half of SplitPanel
	PanelPtr MessagePanelTop = osg::Panel::create();
	FlowLayoutPtr MessagePanelTopLayout = osg::FlowLayout::create();
	LabelPtr MessagePanelText = osg::DialogFactory::createTransparentLabel(Message);

	beginEditCP(MessagePanelTop, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
		MessagePanelTop->getChildren().addValue(MessagePanelText);
		MessagePanelTop->setLayout(MessagePanelTopLayout);
	endEditCP(MessagePanelTop, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
	
	// Create Panel for bottom half of SplitPanel
	PanelPtr MessagePanelBottom = osg::Panel::create();
	FlowLayoutPtr MessagePanelBottomLayout = osg::FlowLayout::create();
	beginEditCP(MessagePanelBottom, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
		MessagePanelBottom->getChildren().addValue(ConfirmationButton);
		MessagePanelBottom->setLayout(MessagePanelBottomLayout);
	endEditCP(MessagePanelBottom, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
	 
	// Create SplitPanel itself
    SplitPanelPtr MessageSplitPanel = osg::SplitPanel::create();
	beginEditCP(MessageSplitPanel, SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::DividerPositionFieldMask | SplitPanel::AlignmentFieldMask |
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask);
        MessageSplitPanel->setMinComponent(MessagePanelTop);
        MessageSplitPanel->setMaxComponent(MessagePanelBottom);
		MessageSplitPanel->setAlignment(VERTICAL_ALIGNMENT);
        MessageSplitPanel->setDividerPosition(.5); 
        MessageSplitPanel->setDividerSize(0);
        MessageSplitPanel->setExpandable(false);
		endEditCP(MessageSplitPanel, SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::DividerPositionFieldMask | SplitPanel::AlignmentFieldMask |
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask);

	return MessageSplitPanel;
}

//InternalWindowPtr DialogFactory::createOptionDialog(const std::string& Title, const std::string& Message, const std::vector<std::string>& ConfirmButtonsText)
//{
//    //TODO: Implement
//    return NullFC;
//}
    
ContainerPtr DialogFactory::createOptionPanel(const std::string& Message, const std::vector<std::string>& OptionButtonsText)
{


	// Create Panel for top half of SplitPanel
	PanelPtr MessagePanelTop = osg::Panel::create();
	FlowLayoutPtr MessagePanelTopLayout = osg::FlowLayout::create();
//	LabelPtr MessagePanelText = osg::DialogFactory::createTransparentLabel(Message);

	beginEditCP(MessagePanelTop, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
		MessagePanelTop->setLayout(MessagePanelTopLayout);
//		MessagePanelTop->getChildren().addValue(MessagePanelText);
	endEditCP(MessagePanelTop, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
	


    // Determine number of Buttons needed
	int NumberOfButtons = OptionButtonsText.size();
	// Create and add that many Buttons, in order, to the Panel
	std::vector<osg::ButtonPtr> OptionButtons;
	for(int i=0; i<NumberOfButtons;i++)
		{

			ButtonPtr OptionButton = osg::Button::create();
			beginEditCP(OptionButton, Button::TextFieldMask | Button::PreferredSizeFieldMask);
				OptionButton->setText(OptionButtonsText[i]);
				OptionButton->setPreferredSizeByContents(0);
			endEditCP(OptionButton, Button::TextFieldMask | Button::PreferredSizeFieldMask);

			OptionButtons.push_back(OptionButton);
		}
	 
	// Create Panel for bottom half of SplitPanel
	PanelPtr MessagePanelBottom = osg::Panel::create();
	FlowLayoutPtr MessagePanelBottomLayout = osg::FlowLayout::create();
	beginEditCP(MessagePanelBottom, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
		MessagePanelBottom->setLayout(MessagePanelBottomLayout);
		for (int i=0; i<NumberOfButtons; i++)
		{	
			MessagePanelBottom->getChildren().addValue(OptionButtons[i]);
		}
	endEditCP(MessagePanelBottom, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);

	// Create SplitPanel itself
    SplitPanelPtr MessageSplitPanel = osg::SplitPanel::create();
	beginEditCP(MessageSplitPanel, SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::DividerPositionFieldMask |
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask);
        MessageSplitPanel->setMinComponent(MessagePanelBottom);
        MessageSplitPanel->setMaxComponent(MessagePanelTop);
        MessageSplitPanel->setDividerPosition(.5); 
        MessageSplitPanel->setDividerSize(0);
        MessageSplitPanel->setExpandable(false);
    endEditCP(MessageSplitPanel, SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::DividerPositionFieldMask |
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask);

	return MessageSplitPanel;
}


void DialogFactory::createColorHistory(const std::string& HistoryName)
{
	ColorHistoryMapItor FindItor(_ColorHistory.find(HistoryName));
	if(FindItor == _ColorHistory.end())
	{
		_ColorHistory[HistoryName] = ColorHistoryMap::mapped_type();
	}
}

void DialogFactory::removeColorHistory(const std::string& HistoryName)
{
	ColorHistoryMapItor FindItor(_ColorHistory.find(HistoryName));
	if(FindItor != _ColorHistory.end())
	{
		_ColorHistory.erase(FindItor);
	}
}

void DialogFactory::pushToColorHistory(const std::string& HistoryName, const Color4f& TheColor)
{
	ColorHistoryMapItor FindItor(_ColorHistory.find(HistoryName));
	if(FindItor != _ColorHistory.end())
	{
		(*FindItor).second.push_back(TheColor);
	}
}

void DialogFactory::popFromColorHistory(const std::string& HistoryName)
{
	ColorHistoryMapItor FindItor(_ColorHistory.find(HistoryName));
	if(FindItor != _ColorHistory.end())
	{
		(*FindItor).second.pop_front();
	}
}

void DialogFactory::clearColorHistory(const std::string& HistoryName)
{
	ColorHistoryMapItor FindItor(_ColorHistory.find(HistoryName));
	if(FindItor != _ColorHistory.end())
	{
		(*FindItor).second.clear();
	}
}

DialogFactory::ColorDeque DialogFactory::getColorHistory(const std::string& HistoryName) const
{
	ColorHistoryMapConstItor FindItor(_ColorHistory.find(HistoryName));
	if(FindItor != _ColorHistory.end())
	{
		return FindItor->second;
	}
	else
	{
		return ColorHistoryMap::mapped_type();
	}
}

DialogFactory::StringVector DialogFactory::getColorHistories(void) const
{
	StringVector Histories;

	for(ColorHistoryMapConstItor Itor(_ColorHistory.begin()) ; Itor != _ColorHistory.end() ; ++Itor)
	{
		Histories.push_back(Itor->first);
	}

	return Histories;
}

DialogWindowPtr DialogFactory::createColorDialog(const std::string& Title, const Color4f& TheColor, const std::string& HistoryName)
{
	//Internals Container
	ContainerPtr InternalsContainer(createColorPanel(TheColor, HistoryName));

	//Internals Layout and constriants
	BorderLayoutConstraintsPtr InternalsContainerConstraints = BorderLayoutConstraints::create();
	beginEditCP(InternalsContainerConstraints, BorderLayoutConstraints::RegionFieldMask);
		InternalsContainerConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
	endEditCP(InternalsContainerConstraints, BorderLayoutConstraints::RegionFieldMask);

	beginEditCP(InternalsContainer, Container::ConstraintsFieldMask);
		InternalsContainer->setConstraints(InternalsContainerConstraints);
	endEditCP(InternalsContainer, Container::ConstraintsFieldMask);

	BorderLayoutPtr DialogLayout = BorderLayout::create();

	//Create the Dialog box
	DialogWindowPtr TheDialog = DialogWindow::create();
	beginEditCP(TheDialog, DialogWindow::LayoutFieldMask | DialogWindow::ChildrenFieldMask | DialogWindow::TitleFieldMask  | DialogWindow::PreferredSizeFieldMask  | DialogWindow::ResizableFieldMask);
		TheDialog->setLayout(DialogLayout);
		TheDialog->getChildren().addValue(InternalsContainer);
		TheDialog->setTitle(Title);
		TheDialog->setPreferredSize(Vec2s(300.0f,300.0f));
		TheDialog->setResizable(true);
	endEditCP(TheDialog, DialogWindow::LayoutFieldMask | DialogWindow::ChildrenFieldMask | DialogWindow::TitleFieldMask | DialogWindow::PreferredSizeFieldMask | DialogWindow::ResizableFieldMask);

	return TheDialog;
}

ContainerPtr DialogFactory::createColorPanel(const Color4f& TheColor, const std::string& HistoryName)
{

	ButtonPtr ConfirmButton = osg::Button::create();
	beginEditCP(ConfirmButton, Button::TextFieldMask);
		ConfirmButton->setText("Ok");
	endEditCP(ConfirmButton, Button::TextFieldMask);
	
	ButtonPtr CancelButton = osg::Button::create();
	beginEditCP(CancelButton, Button::TextFieldMask);
		CancelButton->setText("Cancel");
	endEditCP(CancelButton, Button::TextFieldMask);

	//Layout Constraints
    BorderLayoutConstraintsPtr ButtonPanelConstraints = osg::BorderLayoutConstraints::create();
    beginEditCP(ButtonPanelConstraints, BorderLayoutConstraints::RegionFieldMask);
        ButtonPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_SOUTH);
    endEditCP(ButtonPanelConstraints, BorderLayoutConstraints::RegionFieldMask);

    BorderLayoutConstraintsPtr TheColorChooserPanelConstraints = osg::BorderLayoutConstraints::create();
    beginEditCP(TheColorChooserPanelConstraints, BorderLayoutConstraints::RegionFieldMask);
        TheColorChooserPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
    endEditCP(TheColorChooserPanelConstraints, BorderLayoutConstraints::RegionFieldMask);

	//ButtonPanel
	PanelPtr ButtonPanel = osg::Panel::createEmpty();
	LayoutPtr ButtonPanelLayout = FlowLayout::create();
	beginEditCP(ButtonPanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::ConstraintsFieldMask | Panel::PreferredSizeFieldMask);
		ButtonPanel->setLayout(ButtonPanelLayout);
		ButtonPanel->getChildren().addValue(ConfirmButton);
		ButtonPanel->getChildren().addValue(CancelButton);
        ButtonPanel->setConstraints(ButtonPanelConstraints);
        ButtonPanel->setPreferredSize(Vec2f(200, 50));
	endEditCP(ButtonPanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::ConstraintsFieldMask | Panel::PreferredSizeFieldMask);

	//ColorPanel
	ColorChooserPtr TheColorChooserPanel = ColorChooser::create();
	beginEditCP(TheColorChooserPanel, ColorChooser::ConstraintsFieldMask);
        TheColorChooserPanel->setConstraints(TheColorChooserPanelConstraints);
	endEditCP(TheColorChooserPanel, ColorChooser::ConstraintsFieldMask);

	//Main Panel
	PanelPtr MainColorPanel = osg::Panel::create();
    BorderLayoutPtr MainColorPanelLayout = osg::BorderLayout::create();
	beginEditCP(MainColorPanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BordersFieldMask);
		MainColorPanel->setLayout(MainColorPanelLayout);
		MainColorPanel->getChildren().addValue(TheColorChooserPanel);
		MainColorPanel->getChildren().addValue(ButtonPanel);
		MainColorPanel->setBorders(NullFC);
	endEditCP(MainColorPanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BordersFieldMask);

	return MainColorPanel;
}

OSG_END_NAMESPACE