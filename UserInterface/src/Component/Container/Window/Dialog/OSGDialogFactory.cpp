#include "OSGDialogFactory.h"

//#include "Component/Container/Window/OSGInternalWindow.h"
#include "Component/Container/OSGContainer.h"
#include "Component/Button/OSGButton.h"
#include "Component/Container/OSGSplitPanel.h"
#include "Component/Container/OSGPanel.h"
#include "Layout/OSGFlowLayout.h"
#include "Component/Text/OSGLabel.h"
#include "Component/Text/OSGLabel.h"
#include "Border/OSGEmptyBorder.h"
#include "Background/OSGEmptyUIBackground.h"
#include "Event/OSGActionListener.h"

OSG_BEGIN_NAMESPACE

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
//	LabelPtr MessagePanelText = osg::DialogFactory::createTransparentLabel(Message);

	beginEditCP(MessagePanelTop, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
//		MessagePanelTop->getChildren().addValue(MessagePanelText);
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



OSG_END_NAMESPACE
