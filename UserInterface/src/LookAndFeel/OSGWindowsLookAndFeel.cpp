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

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGWindowsLookAndFeel.h"
#include "Text/OSGUIFont.h"
#include "Border/OSGBorders.h"
#include "Background/OSGUIBackgrounds.h"
#include "Component/Button/OSGButton.h"
#include "Component/Button/OSGCheckboxButton.h"
#include "Component/Button/OSGRadioButton.h"
#include "Component/Button/OSGToggleButton.h"
#include "Component/Text/OSGLabel.h"
#include "Component/Container/Window/OSGInternalWindow.h"
#include "Component/Container/Window/Dialog/OSGDialogWindow.h"
#include "Component/Container/Window/OSGTitlebar.h"
#include "Component/Container/OSGPanel.h"
#include "Component/Container/OSGSplitPanel.h"
#include "Component/Container/OSGTabPanel.h"
#include "Component/Misc/OSGImageComponent.h"
#include "Graphics/UIDrawObjects/OSGRectUIDrawObject.h"
#include "Graphics/UIDrawObjects/OSGMultiColoredQuadUIDrawObject.h"
#include "Graphics/UIDrawObjects/OSGArcUIDrawObject.h"
#include "Graphics/UIDrawObjects/OSGDiscUIDrawObject.h"
#include "Graphics/UIDrawObjects/OSGLineUIDrawObject.h"
#include "Graphics/UIDrawObjects/OSGPolygonUIDrawObject.h"
#include "Component/Misc/OSGUIDrawObjectCanvas.h"
#include "Component/Text/OSGTextField.h"
#include "Component/Text/OSGPasswordField.h"
#include "Component/Text/OSGTextArea.h"
#include "Component/Misc/OSGToolTip.h"
#include "Component/Misc/OSGSeparator.h"

#include "Component/Menu/OSGMenuItem.h"
#include "Component/Menu/OSGComponentMenuItem.h"
#include "Component/Menu/OSGMenu.h"
#include "Component/Menu/OSGPopupMenu.h"
#include "Component/Menu/OSGListGeneratedPopupMenu.h"
#include "Component/Menu/OSGMenuBar.h"
#include "Models/SelectionModels/OSGDefaultSingleSelectionModel.h"

#include "Component/Misc/OSGRotatedComponent.h"

#include "Component/Scroll/OSGScrollBar.h"
#include "Component/Scroll/OSGScrollPanel.h"
#include "Component/Container/OSGUIViewport.h"

#include "Component/Table/OSGTableHeader.h"
#include "Component/Table/OSGTable.h"
#include "Component/Table/DefaultRenderers/OSGDefaultTableCellRenderers.h"

#include "Component/List/OSGList.h"
#include "Component/List/OSGDefaultListSelectionModel.h"
#include "Component/List/ComponentGenerators/OSGDefaultListComponentGenerator.h"

#include "Component/Spinner/OSGSpinner.h"
#include "Component/Spinner/Editors/OSGSpinnerDefaultEditor.h"
#include "Component/Spinner/Editors/OSGSpinnerNumberEditor.h"

#include "Component/ProgressBar/OSGProgressBar.h"

#include "Component/Slider/OSGSlider.h"

#include "Component/ComboBox/OSGComboBox.h"
#include "Component/ComboBox/Editors/OSGDefaultComboBoxEditor.h"
#include "Component/ComboBox/ComponentGenerators/OSGDefaultComboBoxComponentGenerator.h"

#include "Component/Tree/ModelLayout/OSGFixedHeightTreeModelLayout.h"
#include "Component/Tree/Editors/OSGDefaultTreeCellEditor.h"
#include "Component/Tree/ComponentGenerators/OSGDefaultTreeComponentGenerator.h"
#include "Component/Tree/OSGTree.h"

#include "Component/Container/ColorChooser/OSGColorChooser.h"
#include "Component/Container/ColorChooser/OSGRGBColorChooserPanel.h"
#include "Component/Container/ColorChooser/OSGHSVColorChooserPanel.h"

#include "Component/Container/Toolbar/OSGToolbar.h"
OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::WindowsLookAndFeel
UI Windows LookAndFeel. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void WindowsLookAndFeel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
void WindowsLookAndFeel::init(void)
{

	ButtonPtr WindowsButton = Button::create();
	LabelPtr WindowsLabel = Label::create();
	InternalWindowPtr WindowsInternalWindow = InternalWindow::create();
	DialogWindowPtr WindowsDialogWindow = DialogWindow::create();
	PanelPtr WindowsPanel = Panel::create();
	ToolbarPtr WindowsToolbar = Toolbar::create();
	SplitPanelPtr WindowsSplitPanel = SplitPanel::create();
	TabPanelPtr WindowsTabPanel = TabPanel::create();
	ImageComponentPtr WindowsImageComponent = ImageComponent::create();
	CheckboxButtonPtr WindowsCheckboxButton = CheckboxButton::create();
	RadioButtonPtr WindowsRadioButton = RadioButton::create();
	ToggleButtonPtr WindowsToggleButton = ToggleButton::create();
	TextFieldPtr WindowsTextField = TextField::create();
	PasswordFieldPtr WindowsPasswordField = PasswordField::create();
	TextAreaPtr WindowsTextArea = TextArea::create();
	ToolTipPtr WindowsToolTip = ToolTip::create();
	MenuItemPtr WindowsMenuItem = MenuItem::create();
	ComponentMenuItemPtr WindowsComponentMenuItem = ComponentMenuItem::create();
	MenuPtr WindowsMenu = Menu::create();
	PopupMenuPtr WindowsPopupMenu = PopupMenu::create();
	ListGeneratedPopupMenuPtr WindowsListGeneratedPopupMenu = ListGeneratedPopupMenu::create();
	MenuBarPtr WindowsMenuBar = MenuBar::create();
	ScrollBarPtr WindowsScrollBar = ScrollBar::create();
	ScrollPanelPtr WindowsScrollPanel = ScrollPanel::create();
	UIViewportPtr WindowsUIViewport = UIViewport::create();
	RotatedComponentPtr WindowsRotatedComponent = RotatedComponent::create();
    DefaultListComponentGeneratorPtr WindowsDefaultListComponentGenerator = DefaultListComponentGenerator::create();
	ListPtr WindowsList = List::create();
    SpinnerPtr WindowsSpinner = Spinner::create();
    SpinnerDefaultEditorPtr WindowsSpinnerDefaultEditor = SpinnerDefaultEditor::create();
    SpinnerNumberEditorPtr WindowsSpinnerNumberEditor = SpinnerNumberEditor::create();
    SeparatorPtr WindowsSeparator = Separator::create();
    ProgressBarPtr WindowsProgressBar = ProgressBar::create();
    SliderPtr WindowsSlider = Slider::create();
    DefaultComboBoxComponentGeneratorPtr WindowsDefaultComboBoxComponentGenerator = DefaultComboBoxComponentGenerator::create();
    ComboBoxPtr WindowsComboBox = ComboBox::create();
	TableHeaderPtr WindowsTableHeader = TableHeader::create();
	TablePtr WindowsTable = Table::create();
    DefaultTreeCellEditorPtr WindowsDefaultTreeCellEditor = DefaultTreeCellEditor::create();
    DefaultTreeComponentGeneratorPtr WindowsDefaultTreeComponentGenerator = DefaultTreeComponentGenerator::create();
	TreePtr WindowsTree = Tree::create();
	ColorChooserPtr WindowsColorChooser = ColorChooser::create();

	beginEditCP(WindowsLookAndFeelPtr(this), WindowsLookAndFeel::PrototypesFieldMask);
		getPrototypes().push_back(WindowsButton);
		getPrototypes().push_back(WindowsLabel);
		getPrototypes().push_back(WindowsInternalWindow);
		getPrototypes().push_back(WindowsDialogWindow);
		getPrototypes().push_back(WindowsPanel);
		getPrototypes().push_back(WindowsToolbar);
		getPrototypes().push_back(WindowsSplitPanel);
		getPrototypes().push_back(WindowsTabPanel);
		getPrototypes().push_back(WindowsImageComponent);
		getPrototypes().push_back(WindowsCheckboxButton);
		getPrototypes().push_back(WindowsRadioButton);
		getPrototypes().push_back(WindowsToggleButton);
		getPrototypes().push_back(WindowsTextField);
		getPrototypes().push_back(WindowsPasswordField);
		getPrototypes().push_back(WindowsTextArea);
		getPrototypes().push_back(WindowsToolTip);
		getPrototypes().push_back(WindowsMenuItem);
		getPrototypes().push_back(WindowsComponentMenuItem);
		getPrototypes().push_back(WindowsMenu);
		getPrototypes().push_back(WindowsPopupMenu);
		getPrototypes().push_back(WindowsListGeneratedPopupMenu);
		getPrototypes().push_back(WindowsMenuBar);
		getPrototypes().push_back(WindowsScrollBar);
		getPrototypes().push_back(WindowsScrollPanel);
		getPrototypes().push_back(WindowsUIViewport);
		getPrototypes().push_back(WindowsRotatedComponent);
		getPrototypes().push_back(WindowsDefaultListComponentGenerator);
		getPrototypes().push_back(WindowsList);
		getPrototypes().push_back(WindowsSpinner);
		getPrototypes().push_back(WindowsSpinnerDefaultEditor);
		getPrototypes().push_back(WindowsSpinnerNumberEditor);
		getPrototypes().push_back(WindowsSeparator);
		getPrototypes().push_back(WindowsProgressBar);
		getPrototypes().push_back(WindowsSlider);
		getPrototypes().push_back(WindowsDefaultComboBoxComponentGenerator);
		getPrototypes().push_back(WindowsComboBox);
		getPrototypes().push_back(WindowsTableHeader);
		getPrototypes().push_back(WindowsTable);
		getPrototypes().push_back(WindowsDefaultTreeCellEditor);
		getPrototypes().push_back(WindowsDefaultTreeComponentGenerator);
		getPrototypes().push_back(WindowsTree);
		getPrototypes().push_back(WindowsColorChooser);
	endEditCP(WindowsLookAndFeelPtr(this), WindowsLookAndFeel::PrototypesFieldMask);

    initPrototypes();

	setTextCaretRate(1.0);
	setToolTipPopupTime(1.5);
	setToolTipPopupTime(0.25);
	setKeyAcceleratorMenuFlashTime(0.15);

	Color4f WindowsXPMainColor(1.0,1.0,1.0,1.0);

	/********Empty Border*********/
	EmptyBorderPtr WindowsEmptyBorder = EmptyBorder::create();
	beginEditCP(WindowsEmptyBorder);
		WindowsEmptyBorder->setTopWidth(0);
		WindowsEmptyBorder->setBottomWidth(0);
		WindowsEmptyBorder->setRightWidth(0);
		WindowsEmptyBorder->setLeftWidth(0);
	endEditCP(WindowsEmptyBorder);

	/*********Empty Background**********/
	EmptyUIBackgroundPtr WindowsEmptyBackground = EmptyUIBackground::create();

	//Windows Font
	UIFontPtr WindowsFont = UIFont::create();
	beginEditCP(WindowsFont);
		WindowsFont->setFamily("Tahoma");
		WindowsFont->setGap(3);
		WindowsFont->setGlyphPixelSize(46);
		WindowsFont->setSize(14);
		WindowsFont->setTextureWidth(0);
		WindowsFont->setStyle(TextFace::STYLE_PLAIN);
	endEditCP(WindowsFont);

    Color4f WindowsDisabledTextColor(0.63,0.63,0.57,1.0);

	//Windows ButtonBorder
	RoundedCornerLineBorderPtr WindowsButtonBorder = RoundedCornerLineBorder::create();
	beginEditCP(WindowsButtonBorder);
		WindowsButtonBorder->setColor( Color4f(0.0, 0.235, 0.455 ,1.0) );
		WindowsButtonBorder->setWidth(1);
        WindowsButtonBorder->setCornerRadius(3);
	endEditCP(WindowsButtonBorder);

	//Windows Active button border
    RoundedCornerLineBorderPtr WindowsActiveButtonBorder = RoundedCornerLineBorder::create();
	beginEditCP(WindowsActiveButtonBorder);
		WindowsActiveButtonBorder->setColor( Color4f(0.0, 0.235, 0.455 ,1.0) );
		WindowsActiveButtonBorder->setWidth(1);
        WindowsActiveButtonBorder->setCornerRadius(3);
	endEditCP(WindowsActiveButtonBorder);
    

	//Windows Rollover button border
    RoundedCornerLineBorderPtr WindowsRolloverInsideButtonBorder = RoundedCornerLineBorder::create();
	beginEditCP(WindowsRolloverInsideButtonBorder);
		WindowsRolloverInsideButtonBorder->setColor( Color4f(0.98, 0.79, 0.42 ,1.0) );
		WindowsRolloverInsideButtonBorder->setWidth(2);
        WindowsRolloverInsideButtonBorder->setCornerRadius(1);
	endEditCP(WindowsRolloverInsideButtonBorder);

	CompoundBorderPtr WindowsRolloverButtonBorder = CompoundBorder::create();
	beginEditCP(WindowsRolloverButtonBorder);
        WindowsRolloverButtonBorder->setInnerBorder(WindowsRolloverInsideButtonBorder);
        WindowsRolloverButtonBorder->setOuterBorder(WindowsButtonBorder);
	endEditCP(WindowsRolloverButtonBorder);
    
	//Windows Disabled button border
    RoundedCornerLineBorderPtr WindowsDisabledInsideButtonBorder = RoundedCornerLineBorder::create();
	beginEditCP(WindowsDisabledInsideButtonBorder);
		WindowsDisabledInsideButtonBorder->setColor( Color4f(0.79, 0.78, 0.73 ,1.0) );
		WindowsDisabledInsideButtonBorder->setWidth(1);
        WindowsDisabledInsideButtonBorder->setCornerRadius(3);
	endEditCP(WindowsDisabledInsideButtonBorder);
    RoundedCornerLineBorderPtr WindowsDisabledOutsideButtonBorder = RoundedCornerLineBorder::create();
	beginEditCP(WindowsDisabledOutsideButtonBorder);
		WindowsDisabledOutsideButtonBorder->setColor( Color4f(0.93, 0.91, 0.85 ,1.0) );
		WindowsDisabledOutsideButtonBorder->setWidth(1);
        WindowsDisabledOutsideButtonBorder->setCornerRadius(1);
	endEditCP(WindowsDisabledOutsideButtonBorder);

	CompoundBorderPtr WindowsDisabledButtonBorder = CompoundBorder::create();
	beginEditCP(WindowsDisabledButtonBorder);
        WindowsDisabledButtonBorder->setInnerBorder(WindowsDisabledInsideButtonBorder);
        WindowsDisabledButtonBorder->setOuterBorder(WindowsDisabledOutsideButtonBorder);
	endEditCP(WindowsDisabledButtonBorder);

	//Windows ButtonBackground
	GradientUIBackgroundPtr WindowsButtonBackground = GradientUIBackground::create();
	beginEditCP(WindowsButtonBackground);
		WindowsButtonBackground->setColorStart(Color4f(.988, .988, .984, 1.0));
		WindowsButtonBackground->setColorEnd(Color4f(.941, .941, .918, 1.0));
		WindowsButtonBackground->setOrientation(GradientUIBackground::VERTICAL_ORIENTATION);
	endEditCP(WindowsButtonBackground);
	
	//Windows Disabled ButtonBackground
	ColorUIBackgroundPtr WindowsDisabledButtonBackground = ColorUIBackground::create();
	beginEditCP(WindowsDisabledButtonBackground);
		WindowsDisabledButtonBackground->setColor(Color4f(0.93,0.93,0.93,1.0));
	endEditCP(WindowsDisabledButtonBackground);
    
	//Windows Active ButtonBackground
	GradientUIBackgroundPtr WindowsActiveButtonBackground = GradientUIBackground::create();
	beginEditCP(WindowsActiveButtonBackground);
		WindowsActiveButtonBackground->setColorStart(Color4f(.90, .89, .87, 1.0));
		WindowsActiveButtonBackground->setColorEnd(Color4f(.89, .89, .85, 1.0));
		WindowsActiveButtonBackground->setOrientation(GradientUIBackground::VERTICAL_ORIENTATION);
	endEditCP(WindowsActiveButtonBackground);
    
	//Windows Rollover ButtonBackground
	GradientUIBackgroundPtr WindowsRolloverButtonBackground = GradientUIBackground::create();
	beginEditCP(WindowsRolloverButtonBackground);
		WindowsRolloverButtonBackground->setColorStart(Color4f(.99, .99, .98, 1.0));
		WindowsRolloverButtonBackground->setColorEnd(Color4f(.93, .92, .90, 1.0));
		WindowsRolloverButtonBackground->setOrientation(GradientUIBackground::VERTICAL_ORIENTATION);
	endEditCP(WindowsRolloverButtonBackground);

	//Windows Button
	beginEditCP(WindowsButton);
		WindowsButton->setEnabled(true);
		WindowsButton->setVisible(true);
		
		WindowsButton->setConstraints(NullFC);
		//Sizes
		WindowsButton->setMinSize(Vec2f(0,0));
		WindowsButton->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsButton->setPreferredSize(Vec2f(75,23));

		//Border
		WindowsButton->setBorder(WindowsButtonBorder);
		WindowsButton->setRolloverBorder(WindowsRolloverButtonBorder);
		WindowsButton->setFocusedBorder(WindowsButtonBorder);
		WindowsButton->setDisabledBorder(WindowsDisabledButtonBorder);
		WindowsButton->setActiveBorder(WindowsActiveButtonBorder);
		
		//Background
		WindowsButton->setBackground(WindowsButtonBackground);
		WindowsButton->setRolloverBackground(WindowsRolloverButtonBackground);
		WindowsButton->setFocusedBackground(WindowsButtonBackground);
		WindowsButton->setDisabledBackground(WindowsDisabledButtonBackground);
		WindowsButton->setActiveBackground(WindowsActiveButtonBackground);
		
		//Opacity
		WindowsButton->setOpacity(1.0);

		//Text
		WindowsButton->setText("");
		WindowsButton->setFont(WindowsFont);
		WindowsButton->setVerticalAlignment(0.5);
		WindowsButton->setHorizontalAlignment(0.5);
		WindowsButton->setTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsButton->setActiveTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsButton->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsButton->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsButton->setDisabledTextColor(WindowsDisabledTextColor);
        
        WindowsButton->setActiveOffset(Vec2f(2,2));
	endEditCP(WindowsButton);

	//************************** Label*****************************
	//Windows LabelBackground
	ColorUIBackgroundPtr WindowsLabelBackground = ColorUIBackground::create();
	beginEditCP(WindowsLabelBackground);
		WindowsLabelBackground->setColor(Color4f(0.9569,0.9529,0.9373,1.0));
	endEditCP(WindowsLabelBackground);

	//Windows Label
	beginEditCP(WindowsLabel);
		WindowsLabel->setEnabled(true);
		WindowsLabel->setVisible(true);
		
		WindowsLabel->setConstraints(NullFC);
		//Sizes
		WindowsLabel->setMinSize(Vec2f(0,0));
		WindowsLabel->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsLabel->setPreferredSize(Vec2f(75,23));

		//Border
		WindowsLabel->setBorders(WindowsEmptyBorder);
		
		//Background
		WindowsLabel->setBackgrounds(WindowsLabelBackground);
		
		//Opacity
		WindowsLabel->setOpacity(1.0);

		//Text
		WindowsLabel->setText("");
		WindowsLabel->setFont(WindowsFont);
		WindowsLabel->setTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsLabel->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsLabel->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsLabel->setDisabledTextColor(WindowsDisabledTextColor);
		
		WindowsLabel->setVerticalAlignment(0.5);
		WindowsLabel->setHorizontalAlignment(0.0);
		WindowsLabel->setTextSelectable(false);
	endEditCP(WindowsLabel);
	
	//************************** InternalWindow *****************************
	//Windows InternalWindow 
	//Inside FocusedBorder
	BevelBorderPtr WindowsInsideInternalWindowFocusedBorder = BevelBorder::create();
	beginEditCP(WindowsInsideInternalWindowFocusedBorder);
		WindowsInsideInternalWindowFocusedBorder->setRaised(true);
		WindowsInsideInternalWindowFocusedBorder->setWidth(2);
		WindowsInsideInternalWindowFocusedBorder->setHighlightInner(Color4f(0.4, 0.4, 0.49, 1.0));
		WindowsInsideInternalWindowFocusedBorder->setHighlightOuter(Color4f(0.89, 0.89, 0.89, 1.0));
		WindowsInsideInternalWindowFocusedBorder->setShadowInner(Color4f(0.4, 0.4, 0.49, 1.0));
		WindowsInsideInternalWindowFocusedBorder->setShadowOuter(Color4f(0.89, 0.89, 0.89, 1.0));
	endEditCP(WindowsInsideInternalWindowFocusedBorder);
    
	//Outside FocusedBorder
	BevelBorderPtr WindowsOutsideInternalWindowFocusedBorder = BevelBorder::create();
	beginEditCP(WindowsOutsideInternalWindowFocusedBorder);
		WindowsOutsideInternalWindowFocusedBorder->setRaised(true);
		WindowsOutsideInternalWindowFocusedBorder->setWidth(2);
		WindowsOutsideInternalWindowFocusedBorder->setHighlightOuter(Color4f(0.4, 0.4, 0.49, 1.0));
		WindowsOutsideInternalWindowFocusedBorder->setHighlightInner(Color4f(0.89, 0.89, 0.89, 1.0));
		WindowsOutsideInternalWindowFocusedBorder->setShadowOuter(Color4f(0.4, 0.4, 0.49, 1.0));
		WindowsOutsideInternalWindowFocusedBorder->setShadowInner(Color4f(0.89, 0.89, 0.89, 1.0));
	endEditCP(WindowsOutsideInternalWindowFocusedBorder);

	//FocusedBorder
	WindowBorderPtr WindowsInternalWindowFocusedBorder = WindowBorder::create();
	beginEditCP(WindowsInternalWindowFocusedBorder);
		WindowsInternalWindowFocusedBorder->setInnerBorder(WindowsInsideInternalWindowFocusedBorder);
		WindowsInternalWindowFocusedBorder->setOuterBorder(WindowsOutsideInternalWindowFocusedBorder);
	endEditCP(WindowsInternalWindowFocusedBorder);

	//Inside UnfocusedBorder
	BevelBorderPtr WindowsInsideInternalWindowUnfocusedBorder = BevelBorder::create();
	beginEditCP(WindowsInsideInternalWindowUnfocusedBorder);
		WindowsInsideInternalWindowUnfocusedBorder->setRaised(true);
		WindowsInsideInternalWindowUnfocusedBorder->setWidth(2);
		WindowsInsideInternalWindowUnfocusedBorder->setHighlightInner(Color4f(0.80, 0.80, 0.85, 1.0));
		WindowsInsideInternalWindowUnfocusedBorder->setHighlightOuter(Color4f(0.99, 1.0, 0.99, 1.0));
		WindowsInsideInternalWindowUnfocusedBorder->setShadowInner(Color4f(0.80, 0.80, 0.85, 1.0));
		WindowsInsideInternalWindowUnfocusedBorder->setShadowOuter(Color4f(0.99, 1.0, 0.99, 1.0));
	endEditCP(WindowsInsideInternalWindowUnfocusedBorder);
    
	//Outside UnfocusedBorder
	BevelBorderPtr WindowsOutsideInternalWindowUnfocusedBorder = BevelBorder::create();
	beginEditCP(WindowsOutsideInternalWindowUnfocusedBorder);
		WindowsOutsideInternalWindowUnfocusedBorder->setRaised(true);
		WindowsOutsideInternalWindowUnfocusedBorder->setWidth(2);
		WindowsOutsideInternalWindowUnfocusedBorder->setHighlightOuter(Color4f(0.80, 0.80, 0.85, 1.0));
		WindowsOutsideInternalWindowUnfocusedBorder->setHighlightInner(Color4f(0.99, 1.0, 0.99, 1.0));
		WindowsOutsideInternalWindowUnfocusedBorder->setShadowOuter(Color4f(0.80, 0.80, 0.85, 1.0));
		WindowsOutsideInternalWindowUnfocusedBorder->setShadowInner(Color4f(0.99, 1.0, 0.99, 1.0));
	endEditCP(WindowsOutsideInternalWindowUnfocusedBorder);

	//UnfocusedBorder
	WindowBorderPtr WindowsInternalWindowUnfocusedBorder = WindowBorder::create();
	beginEditCP(WindowsInternalWindowUnfocusedBorder);
		WindowsInternalWindowUnfocusedBorder->setInnerBorder(WindowsInsideInternalWindowUnfocusedBorder);
		WindowsInternalWindowUnfocusedBorder->setOuterBorder(WindowsOutsideInternalWindowUnfocusedBorder);
	endEditCP(WindowsInternalWindowUnfocusedBorder);	

	//InternalWindow Background
	ColorUIBackgroundPtr WindowsInternalWindowBackground = ColorUIBackground::create();
	beginEditCP(WindowsInternalWindowBackground);
		WindowsInternalWindowBackground->setColor( Color4f(0.9569,0.9529,0.9373,1.0) );
	endEditCP(WindowsInternalWindowBackground);
	
	//Decoration Buttons
	//Windows IconifyMaximizeButtonBorder
	RoundedCornerLineBorderPtr WindowsIconifyMaximizeButtonBorder = RoundedCornerLineBorder::create();
	beginEditCP(WindowsIconifyMaximizeButtonBorder);
		WindowsIconifyMaximizeButtonBorder->setColor( Color4f(0.42, 0.46, 0.56 ,1.0) );
		WindowsIconifyMaximizeButtonBorder->setWidth(1);
        WindowsIconifyMaximizeButtonBorder->setCornerRadius(3);
	endEditCP(WindowsIconifyMaximizeButtonBorder);

	//Windows ActiveIconifyMaximizeButtonBorder
	RoundedCornerLineBorderPtr ActiveWindowsIconifyMaximizeButtonBorder = RoundedCornerLineBorder::create();
	beginEditCP(ActiveWindowsIconifyMaximizeButtonBorder);
		ActiveWindowsIconifyMaximizeButtonBorder->setColor( Color4f(0.31, 0.35, 0.44 ,1.0) );
		ActiveWindowsIconifyMaximizeButtonBorder->setWidth(1);
        ActiveWindowsIconifyMaximizeButtonBorder->setCornerRadius(3);
	endEditCP(ActiveWindowsIconifyMaximizeButtonBorder);

	//Windows DisabledIconifyMaximizeButtonBorder
	RoundedCornerLineBorderPtr DisabledWindowsIconifyMaximizeButtonBorder = RoundedCornerLineBorder::create();
	beginEditCP(DisabledWindowsIconifyMaximizeButtonBorder);
		DisabledWindowsIconifyMaximizeButtonBorder->setColor( Color4f(0.66, 0.68, 0.73 ,1.0) );
		DisabledWindowsIconifyMaximizeButtonBorder->setWidth(1);
        DisabledWindowsIconifyMaximizeButtonBorder->setCornerRadius(3);
	endEditCP(DisabledWindowsIconifyMaximizeButtonBorder);

	//Windows  IconifyMaximizeButtonBackground
	GradientUIBackgroundPtr WindowsIconifyMaximizeButtonBackground = GradientUIBackground::create();
	beginEditCP(WindowsIconifyMaximizeButtonBackground);
		WindowsIconifyMaximizeButtonBackground->setColorStart(Color4f(1.0, 1.0, 1.0, 1.0));
		WindowsIconifyMaximizeButtonBackground->setColorEnd(Color4f(0.52, 0.54, 0.69, 1.0));
		WindowsIconifyMaximizeButtonBackground->setOrientation(GradientUIBackground::VERTICAL_ORIENTATION);
	endEditCP(WindowsIconifyMaximizeButtonBackground);

	//Windows  ActiveIconifyMaximizeButtonBackground
	GradientUIBackgroundPtr ActiveWindowsIconifyMaximizeButtonBackground = GradientUIBackground::create();
	beginEditCP(ActiveWindowsIconifyMaximizeButtonBackground);
		ActiveWindowsIconifyMaximizeButtonBackground->setColorStart(Color4f(0.55, 0.56, 0.68, 1.0));
		ActiveWindowsIconifyMaximizeButtonBackground->setColorEnd(Color4f(1.0, 0.98, 1.0, 1.0));
		ActiveWindowsIconifyMaximizeButtonBackground->setOrientation(GradientUIBackground::VERTICAL_ORIENTATION);
	endEditCP(ActiveWindowsIconifyMaximizeButtonBackground);
	
	//Windows  DisabledIconifyMaximizeButtonBackground
	GradientUIBackgroundPtr WindowsDisabledIconifyMaximizeButtonBackground = GradientUIBackground::create();
	beginEditCP(WindowsDisabledIconifyMaximizeButtonBackground);
		WindowsDisabledIconifyMaximizeButtonBackground->setColorStart(Color4f(1.0, 1.0, 1.0, 1.0));
		WindowsDisabledIconifyMaximizeButtonBackground->setColorEnd(Color4f(0.74, 0.75, 0.82, 1.0));
		WindowsDisabledIconifyMaximizeButtonBackground->setOrientation(GradientUIBackground::VERTICAL_ORIENTATION);
	endEditCP(WindowsDisabledIconifyMaximizeButtonBackground);

	//IconifyButton DrawObject
	PolygonUIDrawObjectPtr WindowsIconifyButtonDrawObject1 = PolygonUIDrawObject::create();
	beginEditCP(WindowsIconifyButtonDrawObject1);
		WindowsIconifyButtonDrawObject1->setColor(Color4f(1.0,1.0,1.0,1.0));
		WindowsIconifyButtonDrawObject1->setOpacity(1.0);
        WindowsIconifyButtonDrawObject1->getVerticies().push_back(Pnt2f(0,0));
        WindowsIconifyButtonDrawObject1->getVerticies().push_back(Pnt2f(0,4));
        WindowsIconifyButtonDrawObject1->getVerticies().push_back(Pnt2f(8,4));
        WindowsIconifyButtonDrawObject1->getVerticies().push_back(Pnt2f(8,0));
	endEditCP(WindowsIconifyButtonDrawObject1);
	
	PolygonUIDrawObjectPtr WindowsIconifyButtonDrawObject2 = PolygonUIDrawObject::create();
	beginEditCP(WindowsIconifyButtonDrawObject2);
		WindowsIconifyButtonDrawObject2->setColor(Color4f(0.15,0.15,0.21,1.0));
		WindowsIconifyButtonDrawObject2->setOpacity(1.0);
        WindowsIconifyButtonDrawObject2->getVerticies().push_back(Pnt2f(1,0));
        WindowsIconifyButtonDrawObject2->getVerticies().push_back(Pnt2f(1,1));
        WindowsIconifyButtonDrawObject2->getVerticies().push_back(Pnt2f(8,1));
        WindowsIconifyButtonDrawObject2->getVerticies().push_back(Pnt2f(8,0));
	endEditCP(WindowsIconifyButtonDrawObject2);
	
	PolygonUIDrawObjectPtr WindowsIconifyButtonDrawObject3 = PolygonUIDrawObject::create();
	beginEditCP(WindowsIconifyButtonDrawObject3);
		WindowsIconifyButtonDrawObject3->setColor(Color4f(0.15,0.15,0.21,1.0));
		WindowsIconifyButtonDrawObject3->setOpacity(1.0);
        WindowsIconifyButtonDrawObject3->getVerticies().push_back(Pnt2f(7,1));
        WindowsIconifyButtonDrawObject3->getVerticies().push_back(Pnt2f(7,3));
        WindowsIconifyButtonDrawObject3->getVerticies().push_back(Pnt2f(8,3));
        WindowsIconifyButtonDrawObject3->getVerticies().push_back(Pnt2f(8,1));
	endEditCP(WindowsIconifyButtonDrawObject3);
	
	PolygonUIDrawObjectPtr WindowsIconifyButtonDrawObject4 = PolygonUIDrawObject::create();
	beginEditCP(WindowsIconifyButtonDrawObject4);
		WindowsIconifyButtonDrawObject4->setColor(Color4f(0.43,0.43,0.56,1.0));
		WindowsIconifyButtonDrawObject4->setOpacity(1.0);
        WindowsIconifyButtonDrawObject4->getVerticies().push_back(Pnt2f(1,1));
        WindowsIconifyButtonDrawObject4->getVerticies().push_back(Pnt2f(1,3));
        WindowsIconifyButtonDrawObject4->getVerticies().push_back(Pnt2f(7,3));
        WindowsIconifyButtonDrawObject4->getVerticies().push_back(Pnt2f(7,1));
	endEditCP(WindowsIconifyButtonDrawObject4);

	UIDrawObjectCanvasPtr WindowsIconifyButtonCanvas = UIDrawObjectCanvas::create();
	beginEditCP(WindowsIconifyButtonCanvas);
	   WindowsIconifyButtonCanvas->getDrawObjects().push_back(WindowsIconifyButtonDrawObject1);
	   WindowsIconifyButtonCanvas->getDrawObjects().push_back(WindowsIconifyButtonDrawObject2);
	   WindowsIconifyButtonCanvas->getDrawObjects().push_back(WindowsIconifyButtonDrawObject3);
	   WindowsIconifyButtonCanvas->getDrawObjects().push_back(WindowsIconifyButtonDrawObject4);
	endEditCP(WindowsIconifyButtonCanvas);

	//Iconify Button
	ButtonPtr WindowsInternalWindowTitlebarIconifyButton = Button::create();
	beginEditCP(WindowsInternalWindowTitlebarIconifyButton);
		WindowsInternalWindowTitlebarIconifyButton->setPreferredSize(Vec2f(21, 21));
		
		//Border
		WindowsInternalWindowTitlebarIconifyButton->setBorder(WindowsIconifyMaximizeButtonBorder);
		WindowsInternalWindowTitlebarIconifyButton->setRolloverBorder(WindowsIconifyMaximizeButtonBorder);
		WindowsInternalWindowTitlebarIconifyButton->setFocusedBorder(WindowsIconifyMaximizeButtonBorder);
		WindowsInternalWindowTitlebarIconifyButton->setDisabledBorder(DisabledWindowsIconifyMaximizeButtonBorder);
		WindowsInternalWindowTitlebarIconifyButton->setActiveBorder(ActiveWindowsIconifyMaximizeButtonBorder);
		
		//Background
		WindowsInternalWindowTitlebarIconifyButton->setBackground(WindowsIconifyMaximizeButtonBackground);
		WindowsInternalWindowTitlebarIconifyButton->setRolloverBackground(WindowsIconifyMaximizeButtonBackground);
		WindowsInternalWindowTitlebarIconifyButton->setFocusedBackground(WindowsIconifyMaximizeButtonBackground);
		WindowsInternalWindowTitlebarIconifyButton->setDisabledBackground(WindowsDisabledIconifyMaximizeButtonBackground);
		WindowsInternalWindowTitlebarIconifyButton->setActiveBackground(ActiveWindowsIconifyMaximizeButtonBackground);

		//DrawObjects
        WindowsInternalWindowTitlebarIconifyButton->setDrawObject(WindowsIconifyButtonCanvas);
        WindowsInternalWindowTitlebarIconifyButton->setActiveDrawObject(WindowsIconifyButtonCanvas);
        WindowsInternalWindowTitlebarIconifyButton->setFocusedDrawObject(WindowsIconifyButtonCanvas);
        WindowsInternalWindowTitlebarIconifyButton->setRolloverDrawObject(WindowsIconifyButtonCanvas);
        WindowsInternalWindowTitlebarIconifyButton->setDisabledDrawObject(WindowsIconifyButtonCanvas);

        WindowsInternalWindowTitlebarIconifyButton->setActiveOffset(Vec2f(0,0));
		WindowsInternalWindowTitlebarIconifyButton->setVerticalAlignment(0.85f);
		WindowsInternalWindowTitlebarIconifyButton->setHorizontalAlignment(0.25f);
	endEditCP(WindowsInternalWindowTitlebarIconifyButton);

	//MaximizeButton
	ButtonPtr WindowsInternalWindowTitlebarMaximizeButton = Button::create();
	beginEditCP(WindowsInternalWindowTitlebarMaximizeButton);
		WindowsInternalWindowTitlebarMaximizeButton->setPreferredSize(Vec2f(21, 21));
		
		//Border
		WindowsInternalWindowTitlebarMaximizeButton->setBorder(WindowsIconifyMaximizeButtonBorder);
		WindowsInternalWindowTitlebarMaximizeButton->setRolloverBorder(WindowsIconifyMaximizeButtonBorder);
		WindowsInternalWindowTitlebarMaximizeButton->setFocusedBorder(WindowsIconifyMaximizeButtonBorder);
		WindowsInternalWindowTitlebarMaximizeButton->setDisabledBorder(DisabledWindowsIconifyMaximizeButtonBorder);
		WindowsInternalWindowTitlebarMaximizeButton->setActiveBorder(ActiveWindowsIconifyMaximizeButtonBorder);
		
		//Background
		WindowsInternalWindowTitlebarMaximizeButton->setBackground(WindowsIconifyMaximizeButtonBackground);
		WindowsInternalWindowTitlebarMaximizeButton->setRolloverBackground(WindowsIconifyMaximizeButtonBackground);
		WindowsInternalWindowTitlebarMaximizeButton->setFocusedBackground(WindowsIconifyMaximizeButtonBackground);
		WindowsInternalWindowTitlebarMaximizeButton->setDisabledBackground(WindowsDisabledIconifyMaximizeButtonBackground);
		WindowsInternalWindowTitlebarMaximizeButton->setActiveBackground(ActiveWindowsIconifyMaximizeButtonBackground);
		
        WindowsInternalWindowTitlebarMaximizeButton->setActiveOffset(Vec2f(0,0));
	endEditCP(WindowsInternalWindowTitlebarMaximizeButton);

	//Windows CloseButtonBorder
	RoundedCornerLineBorderPtr WindowsCloseButtonBorder = RoundedCornerLineBorder::create();
	beginEditCP(WindowsCloseButtonBorder);
		WindowsCloseButtonBorder->setColor( Color4f(0.65, 0.22, 0.27 ,1.0) );
		WindowsCloseButtonBorder->setWidth(1);
        WindowsCloseButtonBorder->setCornerRadius(3);
	endEditCP(WindowsCloseButtonBorder);
	
	//Windows ActiveCloseButtonBorder
	RoundedCornerLineBorderPtr ActiveWindowsCloseButtonBorder = RoundedCornerLineBorder::create();
	beginEditCP(ActiveWindowsCloseButtonBorder);
		ActiveWindowsCloseButtonBorder->setColor( Color4f(0.75, 0.22, 0.27 ,1.0) );
		ActiveWindowsCloseButtonBorder->setWidth(1);
        ActiveWindowsCloseButtonBorder->setCornerRadius(3);
	endEditCP(ActiveWindowsCloseButtonBorder);

	//Windows DisabledCloseButtonBorder
	RoundedCornerLineBorderPtr DisabledWindowsCloseButtonBorder = RoundedCornerLineBorder::create();
	beginEditCP(DisabledWindowsCloseButtonBorder);
		DisabledWindowsCloseButtonBorder->setColor( Color4f(0.76, 0.56, 0.58 ,1.0) );
		DisabledWindowsCloseButtonBorder->setWidth(1);
        DisabledWindowsCloseButtonBorder->setCornerRadius(3);
	endEditCP(DisabledWindowsCloseButtonBorder);

	//Windows  CloseButtonBackground
	GradientUIBackgroundPtr WindowsCloseButtonBackground = GradientUIBackground::create();
	beginEditCP(WindowsCloseButtonBackground);
		WindowsCloseButtonBackground->setColorStart(Color4f(0.96, 0.56, 0.52, 1.0));
		WindowsCloseButtonBackground->setColorEnd(Color4f(0.78, 0.33, 0.36, 1.0));
		WindowsCloseButtonBackground->setOrientation(GradientUIBackground::VERTICAL_ORIENTATION);
	endEditCP(WindowsCloseButtonBackground);

	//Windows  ActiveCloseButtonBackground
	GradientUIBackgroundPtr ActiveWindowsCloseButtonBackground = GradientUIBackground::create();
	beginEditCP(ActiveWindowsCloseButtonBackground);
		ActiveWindowsCloseButtonBackground->setColorStart(Color4f(0.92, 0.41, 0.36, 1.0));
		ActiveWindowsCloseButtonBackground->setColorEnd(Color4f(1.0, 0.64, 0.54, 1.0));
		ActiveWindowsCloseButtonBackground->setOrientation(GradientUIBackground::VERTICAL_ORIENTATION);
	endEditCP(ActiveWindowsCloseButtonBackground);
	
	//Windows  DisabledCloseButtonBackground
	GradientUIBackgroundPtr WindowsDisabledCloseButtonBackground = GradientUIBackground::create();
	beginEditCP(WindowsDisabledCloseButtonBackground);
		WindowsDisabledCloseButtonBackground->setColorStart(Color4f(0.94, 0.76, 0.75, 1.0));
		WindowsDisabledCloseButtonBackground->setColorEnd(Color4f(0.83, 0.63, 0.64, 1.0));
		WindowsDisabledCloseButtonBackground->setOrientation(GradientUIBackground::VERTICAL_ORIENTATION);
	endEditCP(WindowsDisabledCloseButtonBackground);

	
	PolygonUIDrawObjectPtr WindowsCloseButtonDrawObject1 = PolygonUIDrawObject::create();
	beginEditCP(WindowsCloseButtonDrawObject1);
		WindowsCloseButtonDrawObject1->setColor(Color4f(0.35,0.11,0.19,1.0));
		WindowsCloseButtonDrawObject1->setOpacity(1.0);
        WindowsCloseButtonDrawObject1->getVerticies().push_back(Pnt2f(1,0));
        WindowsCloseButtonDrawObject1->getVerticies().push_back(Pnt2f(11,11));
        WindowsCloseButtonDrawObject1->getVerticies().push_back(Pnt2f(13,11));
        WindowsCloseButtonDrawObject1->getVerticies().push_back(Pnt2f(3,0));
	endEditCP(WindowsCloseButtonDrawObject1);
	
	PolygonUIDrawObjectPtr WindowsCloseButtonDrawObject2 = PolygonUIDrawObject::create();
	beginEditCP(WindowsCloseButtonDrawObject2);
		WindowsCloseButtonDrawObject2->setColor(Color4f(0.35,0.11,0.19,1.0));
		WindowsCloseButtonDrawObject2->setOpacity(1.0);
        WindowsCloseButtonDrawObject2->getVerticies().push_back(Pnt2f(0,10));
        WindowsCloseButtonDrawObject2->getVerticies().push_back(Pnt2f(2,10));
        WindowsCloseButtonDrawObject2->getVerticies().push_back(Pnt2f(12,0));
        WindowsCloseButtonDrawObject2->getVerticies().push_back(Pnt2f(10,0));
	endEditCP(WindowsCloseButtonDrawObject2);

	PolygonUIDrawObjectPtr WindowsCloseButtonDrawObject3 = PolygonUIDrawObject::create();
	beginEditCP(WindowsCloseButtonDrawObject3);
		WindowsCloseButtonDrawObject3->setColor(Color4f(1.0,1.0,1.0,1.0));
		WindowsCloseButtonDrawObject3->setOpacity(1.0);
        WindowsCloseButtonDrawObject3->getVerticies().push_back(Pnt2f(1,1));
        WindowsCloseButtonDrawObject3->getVerticies().push_back(Pnt2f(1,3));
        WindowsCloseButtonDrawObject3->getVerticies().push_back(Pnt2f(10,12));
        WindowsCloseButtonDrawObject3->getVerticies().push_back(Pnt2f(12,12));
        WindowsCloseButtonDrawObject3->getVerticies().push_back(Pnt2f(12,10));
        WindowsCloseButtonDrawObject3->getVerticies().push_back(Pnt2f(3,1));
	endEditCP(WindowsCloseButtonDrawObject3);
	
	PolygonUIDrawObjectPtr WindowsCloseButtonDrawObject4 = PolygonUIDrawObject::create();
	beginEditCP(WindowsCloseButtonDrawObject4);
		WindowsCloseButtonDrawObject4->setColor(Color4f(1.0,1.0,1.0,1.0));
		WindowsCloseButtonDrawObject4->setOpacity(1.0);
        WindowsCloseButtonDrawObject4->getVerticies().push_back(Pnt2f(1,12));
        WindowsCloseButtonDrawObject4->getVerticies().push_back(Pnt2f(3,12));
        WindowsCloseButtonDrawObject4->getVerticies().push_back(Pnt2f(12,3));
        WindowsCloseButtonDrawObject4->getVerticies().push_back(Pnt2f(12,1));
        WindowsCloseButtonDrawObject4->getVerticies().push_back(Pnt2f(10,1));
        WindowsCloseButtonDrawObject4->getVerticies().push_back(Pnt2f(1,10));
	endEditCP(WindowsCloseButtonDrawObject4);

	UIDrawObjectCanvasPtr WindowsCloseButtonCanvas = UIDrawObjectCanvas::create();
	beginEditCP(WindowsCloseButtonCanvas);
	   WindowsCloseButtonCanvas->getDrawObjects().push_back(WindowsCloseButtonDrawObject1);
	   WindowsCloseButtonCanvas->getDrawObjects().push_back(WindowsCloseButtonDrawObject2);
	   WindowsCloseButtonCanvas->getDrawObjects().push_back(WindowsCloseButtonDrawObject3);
	   WindowsCloseButtonCanvas->getDrawObjects().push_back(WindowsCloseButtonDrawObject4);
	endEditCP(WindowsCloseButtonCanvas);

	//Windows CloseButton
	ButtonPtr WindowsInternalWindowTitlebarCloseButton = Button::create();
	beginEditCP(WindowsInternalWindowTitlebarCloseButton);
		WindowsInternalWindowTitlebarCloseButton->setPreferredSize(Vec2f(21, 21));

		//Border
		WindowsInternalWindowTitlebarCloseButton->setBorder(WindowsCloseButtonBorder);
		WindowsInternalWindowTitlebarCloseButton->setRolloverBorder(WindowsCloseButtonBorder);
		WindowsInternalWindowTitlebarCloseButton->setFocusedBorder(WindowsCloseButtonBorder);
		WindowsInternalWindowTitlebarCloseButton->setDisabledBorder(DisabledWindowsCloseButtonBorder);
		WindowsInternalWindowTitlebarCloseButton->setActiveBorder(ActiveWindowsCloseButtonBorder);
		
		//Background
		WindowsInternalWindowTitlebarCloseButton->setBackground(WindowsCloseButtonBackground);
		WindowsInternalWindowTitlebarCloseButton->setRolloverBackground(WindowsCloseButtonBackground);
		WindowsInternalWindowTitlebarCloseButton->setFocusedBackground(WindowsCloseButtonBackground);
		WindowsInternalWindowTitlebarCloseButton->setDisabledBackground(WindowsDisabledCloseButtonBackground);
		WindowsInternalWindowTitlebarCloseButton->setActiveBackground(ActiveWindowsCloseButtonBackground);
		
		//DrawObjects
        WindowsInternalWindowTitlebarCloseButton->setDrawObject(WindowsCloseButtonCanvas);
        WindowsInternalWindowTitlebarCloseButton->setActiveDrawObject(WindowsCloseButtonCanvas);
        WindowsInternalWindowTitlebarCloseButton->setFocusedDrawObject(WindowsCloseButtonCanvas);
        WindowsInternalWindowTitlebarCloseButton->setRolloverDrawObject(WindowsCloseButtonCanvas);
        WindowsInternalWindowTitlebarCloseButton->setDisabledDrawObject(WindowsCloseButtonCanvas);

        WindowsInternalWindowTitlebarCloseButton->setActiveOffset(Vec2f(0,0));
		WindowsInternalWindowTitlebarCloseButton->setVerticalAlignment(0.5f);
		WindowsInternalWindowTitlebarCloseButton->setHorizontalAlignment(0.5f);
	endEditCP(WindowsInternalWindowTitlebarCloseButton);

	LabelPtr WindowsInternalWindowTitlebarTitleLabel = Label::create();
	beginEditCP(WindowsInternalWindowTitlebarTitleLabel);
		WindowsInternalWindowTitlebarTitleLabel->setPreferredSize(Vec2f(23, 23));

		//Border
		WindowsInternalWindowTitlebarTitleLabel->setBorder(WindowsEmptyBorder);
		WindowsInternalWindowTitlebarTitleLabel->setRolloverBorder(WindowsEmptyBorder);
		WindowsInternalWindowTitlebarTitleLabel->setFocusedBorder(WindowsEmptyBorder);
		WindowsInternalWindowTitlebarTitleLabel->setDisabledBorder(WindowsEmptyBorder);
		
		//Background
		WindowsInternalWindowTitlebarTitleLabel->setBackground(WindowsEmptyBackground);
		WindowsInternalWindowTitlebarTitleLabel->setRolloverBackground(WindowsEmptyBackground);
		WindowsInternalWindowTitlebarTitleLabel->setFocusedBackground(WindowsEmptyBackground);
		WindowsInternalWindowTitlebarTitleLabel->setDisabledBackground(WindowsEmptyBackground);
	endEditCP(WindowsInternalWindowTitlebarTitleLabel);

	//Titlebar background
	GradientUIBackgroundPtr WIndowsInternalWindowTitlebarBackground = GradientUIBackground::create();
	beginEditCP(WIndowsInternalWindowTitlebarBackground);
		WIndowsInternalWindowTitlebarBackground->setColorStart(Color4f(0.64, 0.64, 0.75, 1.0));
		WIndowsInternalWindowTitlebarBackground->setColorEnd(Color4f(0.89, 0.89, 0.89, 1.0));
		WIndowsInternalWindowTitlebarBackground->setOrientation(GradientUIBackground::VERTICAL_ORIENTATION);
	endEditCP(WIndowsInternalWindowTitlebarBackground);
	//Titlebar DisabledBackground
	GradientUIBackgroundPtr WindowsInternalWindowTitlebarDisabledBackground = GradientUIBackground::create();
	beginEditCP(WindowsInternalWindowTitlebarDisabledBackground);
		WindowsInternalWindowTitlebarDisabledBackground->setColorStart(Color4f(0.84, 0.84, 0.89, 1.0));
		WindowsInternalWindowTitlebarDisabledBackground->setColorEnd(Color4f(0.99, 1.0, 0.99, 1.0));
		WindowsInternalWindowTitlebarDisabledBackground->setOrientation(GradientUIBackground::VERTICAL_ORIENTATION);
	endEditCP(WindowsInternalWindowTitlebarDisabledBackground);


	//Titlebar
	TitlebarPtr WindowsInternalWindowTitlebar = Titlebar::create();
	beginEditCP(WindowsInternalWindowTitlebar);
		WindowsInternalWindowTitlebar->setEnabled(true);
		WindowsInternalWindowTitlebar->setVisible(true);
		
		WindowsInternalWindowTitlebar->setConstraints(NullFC);
		//Sizes
		WindowsInternalWindowTitlebar->setMinSize(Vec2f(0,0));
		WindowsInternalWindowTitlebar->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsInternalWindowTitlebar->setPreferredSize(Vec2f(1, 23));

		//Border
		WindowsInternalWindowTitlebar->setBorder(WindowsEmptyBorder);
		WindowsInternalWindowTitlebar->setRolloverBorder(WindowsEmptyBorder);
		WindowsInternalWindowTitlebar->setFocusedBorder(WindowsEmptyBorder);
		WindowsInternalWindowTitlebar->setDisabledBorder(WindowsEmptyBorder);
		
		//Background
		WindowsInternalWindowTitlebar->setBackground(WIndowsInternalWindowTitlebarBackground);
		WindowsInternalWindowTitlebar->setRolloverBackground(WIndowsInternalWindowTitlebarBackground);
		WindowsInternalWindowTitlebar->setFocusedBackground(WIndowsInternalWindowTitlebarBackground);
		WindowsInternalWindowTitlebar->setDisabledBackground(WindowsInternalWindowTitlebarDisabledBackground);
		
		//Opacity
		WindowsInternalWindowTitlebar->setOpacity(1.0);

		//InternalWindow
		WindowsInternalWindowTitlebar->setIconifyButton(WindowsInternalWindowTitlebarIconifyButton);
		WindowsInternalWindowTitlebar->setMaximizeButton(WindowsInternalWindowTitlebarMaximizeButton);
		WindowsInternalWindowTitlebar->setCloseButton(WindowsInternalWindowTitlebarCloseButton);
		WindowsInternalWindowTitlebar->setTitleLabel(WindowsInternalWindowTitlebarTitleLabel);
		WindowsInternalWindowTitlebar->setFrameIcon(NullFC);
		WindowsInternalWindowTitlebar->setDrawClose(true);
		WindowsInternalWindowTitlebar->setDrawMaximize(true);
		WindowsInternalWindowTitlebar->setDrawIconify(true);

	endEditCP(WindowsInternalWindowTitlebar);

	//Windows InternalWindow
	beginEditCP(WindowsInternalWindow);
		WindowsInternalWindow->setEnabled(true);
		WindowsInternalWindow->setVisible(true);
		
		WindowsInternalWindow->setConstraints(NullFC);
		//Sizes
		WindowsInternalWindow->setMinSize(Vec2f(50,50));
		WindowsInternalWindow->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsInternalWindow->setPreferredSize(Vec2f(100,100));

		//Border
		WindowsInternalWindow->setBorder(WindowsInternalWindowUnfocusedBorder);
		WindowsInternalWindow->setRolloverBorder(WindowsInternalWindowUnfocusedBorder);
		WindowsInternalWindow->setFocusedBorder(WindowsInternalWindowFocusedBorder);
		WindowsInternalWindow->setDisabledBorder(WindowsInternalWindowUnfocusedBorder);
		
		//Background
		WindowsInternalWindow->setBackground(WindowsInternalWindowBackground);
		WindowsInternalWindow->setRolloverBackground(WindowsInternalWindowBackground);
		WindowsInternalWindow->setFocusedBackground(WindowsInternalWindowBackground);
		WindowsInternalWindow->setDisabledBackground(WindowsInternalWindowBackground);
		
		//Opacity
		WindowsInternalWindow->setOpacity(1.0);

		//AbstractWindow
		WindowsInternalWindow->setDrawingSurface(NullFC);
		WindowsInternalWindow->setClosable(true);
		WindowsInternalWindow->setIconable(true);
		WindowsInternalWindow->setMaximizable(true);
		WindowsInternalWindow->setResizable(true);
		WindowsInternalWindow->setTitle(std::string(""));
		WindowsInternalWindow->setDesktopIcon(NullFC);
		WindowsInternalWindow->setAllwaysOnTop(false);
		WindowsInternalWindow->setDrawTitlebar(true);
		WindowsInternalWindow->setDrawDecorations(true);
		WindowsInternalWindow->setAlignmentInDrawingSurface(Vec2f(-1.0f,-1.0f));
		WindowsInternalWindow->setScalingInDrawingSurface(Vec2f(-1.0f,-1.0f));
		WindowsInternalWindow->setResizeModifyCursorWidth(4);

		//InternalWindow
		WindowsInternalWindow->setTitlebar(WindowsInternalWindowTitlebar);

	endEditCP(WindowsInternalWindow);
	
	//************************** DialogWindow *****************************
	//Titlebar
	TitlebarPtr WindowsDialogWindowTitlebar = Titlebar::create();
	beginEditCP(WindowsDialogWindowTitlebar);
		WindowsDialogWindowTitlebar->setEnabled(true);
		WindowsDialogWindowTitlebar->setVisible(true);
		
		WindowsDialogWindowTitlebar->setConstraints(NullFC);
		//Sizes
		WindowsDialogWindowTitlebar->setMinSize(Vec2f(0,0));
		WindowsDialogWindowTitlebar->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsDialogWindowTitlebar->setPreferredSize(Vec2f(1, 23));

		//Border
		WindowsDialogWindowTitlebar->setBorder(WindowsEmptyBorder);
		WindowsDialogWindowTitlebar->setRolloverBorder(WindowsEmptyBorder);
		WindowsDialogWindowTitlebar->setFocusedBorder(WindowsEmptyBorder);
		WindowsDialogWindowTitlebar->setDisabledBorder(WindowsEmptyBorder);
		
		//Background
		WindowsDialogWindowTitlebar->setBackground(WIndowsInternalWindowTitlebarBackground);
		WindowsDialogWindowTitlebar->setRolloverBackground(WIndowsInternalWindowTitlebarBackground);
		WindowsDialogWindowTitlebar->setFocusedBackground(WIndowsInternalWindowTitlebarBackground);
		WindowsDialogWindowTitlebar->setDisabledBackground(WindowsInternalWindowTitlebarDisabledBackground);
		
		//Opacity
		WindowsDialogWindowTitlebar->setOpacity(1.0);

		//InternalWindow
		WindowsDialogWindowTitlebar->setIconifyButton(WindowsInternalWindowTitlebarIconifyButton);
		WindowsDialogWindowTitlebar->setMaximizeButton(WindowsInternalWindowTitlebarMaximizeButton);
		WindowsDialogWindowTitlebar->setCloseButton(WindowsInternalWindowTitlebarCloseButton);
		WindowsDialogWindowTitlebar->setTitleLabel(WindowsInternalWindowTitlebarTitleLabel);
		WindowsDialogWindowTitlebar->setFrameIcon(NullFC);
		WindowsDialogWindowTitlebar->setDrawClose(true);
		WindowsDialogWindowTitlebar->setDrawMaximize(false);
		WindowsDialogWindowTitlebar->setDrawIconify(false);

	endEditCP(WindowsDialogWindowTitlebar);

	//Windows DialogWindow
	beginEditCP(WindowsDialogWindow);
		WindowsDialogWindow->setEnabled(true);
		WindowsDialogWindow->setVisible(true);
		
		WindowsDialogWindow->setConstraints(NullFC);
		//Sizes
		WindowsDialogWindow->setMinSize(Vec2f(50,50));
		WindowsDialogWindow->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsDialogWindow->setPreferredSize(Vec2f(280,140));

		//Border
		WindowsDialogWindow->setBorder(WindowsInternalWindowUnfocusedBorder);
		WindowsDialogWindow->setRolloverBorder(WindowsInternalWindowUnfocusedBorder);
		WindowsDialogWindow->setFocusedBorder(WindowsInternalWindowFocusedBorder);
		WindowsDialogWindow->setDisabledBorder(WindowsInternalWindowUnfocusedBorder);
		
		//Background
		WindowsDialogWindow->setBackground(WindowsInternalWindowBackground);
		WindowsDialogWindow->setRolloverBackground(WindowsInternalWindowBackground);
		WindowsDialogWindow->setFocusedBackground(WindowsInternalWindowBackground);
		WindowsDialogWindow->setDisabledBackground(WindowsInternalWindowBackground);
		
		//Opacity
		WindowsDialogWindow->setOpacity(1.0);

		//AbstractWindow
		WindowsDialogWindow->setDrawingSurface(NullFC);
		WindowsDialogWindow->setClosable(true);
		WindowsDialogWindow->setIconable(false);
		WindowsDialogWindow->setMaximizable(false);
		WindowsDialogWindow->setResizable(false);
		WindowsDialogWindow->setTitle(std::string(""));
		WindowsDialogWindow->setDesktopIcon(NullFC);
		WindowsDialogWindow->setAllwaysOnTop(false);
		WindowsDialogWindow->setDrawTitlebar(true);
		WindowsDialogWindow->setDrawDecorations(true);
		WindowsDialogWindow->setAlignmentInDrawingSurface(Vec2f(-1.0f,-1.0f));
		WindowsDialogWindow->setScalingInDrawingSurface(Vec2f(-1.0f,-1.0f));
		WindowsDialogWindow->setResizeModifyCursorWidth(4);

		//DialogWindow
		WindowsDialogWindow->setTitlebar(WindowsDialogWindowTitlebar);

	endEditCP(WindowsDialogWindow);

	//************************** Panel *****************************
	//Windows PanelBorder
	/*LineBorderPtr WindowsPanelBorder = LineBorder::create();
	beginEditCP(WindowsPanelBorder);
		WindowsPanelBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsPanelBorder->setWidth(1);
	endEditCP(WindowsPanelBorder);*/

	EtchedBorderPtr WindowsPanelBorder = EtchedBorder::create();
	beginEditCP(WindowsPanelBorder);
		WindowsPanelBorder->setWidth(2);
		WindowsPanelBorder->setHighlight(Color4f(1.0, 1.0, 1.0, 1.0));
		WindowsPanelBorder->setShadow(Color4f(0.65, 0.65, 0.65, 1.0));
		WindowsPanelBorder->setRaised(true);
	endEditCP(WindowsPanelBorder);

	//Windows PanelBackground
	ColorUIBackgroundPtr WindowsPanelBackground = ColorUIBackground::create();
	beginEditCP(WindowsPanelBackground);
		WindowsPanelBackground->setColor(Color4f(0.9569,0.9529,0.9373,1.0));
	endEditCP(WindowsPanelBackground);


	//Windows Panel
	beginEditCP(WindowsPanel);
		WindowsPanel->setEnabled(true);
		WindowsPanel->setVisible(true);
		
		WindowsPanel->setConstraints(NullFC);
		//Sizes
		WindowsPanel->setMinSize(Vec2f(0,0));
		WindowsPanel->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsPanel->setPreferredSize(Vec2f(100,100));

		//Border
		WindowsPanel->setBorders(WindowsPanelBorder);
		
		//Background
		WindowsPanel->setBackgrounds(WindowsPanelBackground);
		
		//Opacity
		WindowsPanel->setOpacity(1.0);
	endEditCP(WindowsPanel);
	
	//************************** Toolbar *****************************
	//Windows Toolbar
	beginEditCP(WindowsToolbar);
		WindowsToolbar->setEnabled(true);
		WindowsToolbar->setVisible(true);
		
		WindowsToolbar->setConstraints(NullFC);
		//Sizes
		WindowsToolbar->setMinSize(Vec2f(0,0));
		WindowsToolbar->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsToolbar->setPreferredSize(Vec2f(100,100));

		//Border
		WindowsToolbar->setBorders(WindowsEmptyBorder);
		
		//Background
		WindowsToolbar->setBackgrounds(WindowsPanelBackground);
		
		//Opacity
		WindowsToolbar->setOpacity(1.0);
	endEditCP(WindowsToolbar);
	//************************** SplitPanel *****************************
	//The only default value set will be the divider

	//Windows Divider Background and Border
	ColorUIBackgroundPtr WindowsDividerBackground = ColorUIBackground::create();
	beginEditCP(WindowsDividerBackground);
		WindowsDividerBackground->setColor(Color4f(0.93,0.93,0.93,1.0));
	endEditCP(WindowsDividerBackground);

	//Windows Divider
	UIDrawObjectCanvasPtr WindowsDividerDrawObject = UIDrawObjectCanvas::create();
	beginEditCP(WindowsDividerDrawObject);
		WindowsDividerDrawObject->setBackground(WindowsDividerBackground);
	endEditCP(WindowsDividerDrawObject);

	//Windows SplitPanel
	beginEditCP(WindowsSplitPanel);
		WindowsSplitPanel->setEnabled(true);
		WindowsSplitPanel->setVisible(true);
		
		WindowsSplitPanel->setConstraints(NullFC);
		//Sizes
		WindowsSplitPanel->setMinSize(Vec2f(0,0));
		WindowsSplitPanel->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsSplitPanel->setPreferredSize(Vec2f(100,100));

		//Border
		WindowsSplitPanel->setBorders(WindowsEmptyBorder);
		
		//Background
		WindowsSplitPanel->setBackgrounds(WindowsEmptyBackground);
		
		//Opacity
		WindowsSplitPanel->setOpacity(1.0);

		WindowsSplitPanel->setDividerDrawObject(WindowsDividerDrawObject);
		WindowsSplitPanel->setDividerSize(5);
		WindowsSplitPanel->setDividerPosition(100);
		WindowsSplitPanel->setExpandable(true);
		WindowsSplitPanel->setOrientation(SplitPanel::HORIZONTAL_ORIENTATION);
	endEditCP(WindowsSplitPanel);
	
	//************************** TabPanel *****************************
	RoundedCornerLineBorderPtr WindowsTabPanelTabBorder = RoundedCornerLineBorder::create();
	beginEditCP(WindowsTabPanelTabBorder);
		WindowsTabPanelTabBorder->setColor( Color4f(0.57, 0.61, 0.61 ,1.0) );
		WindowsTabPanelTabBorder->setWidth(1);
        WindowsTabPanelTabBorder->setCornerRadius(3);
	endEditCP(WindowsTabPanelTabBorder);
	
	MatteBorderPtr WindowsTabPanelInsideActiveTabBorder = MatteBorder::create();
	beginEditCP(WindowsTabPanelInsideActiveTabBorder);
		WindowsTabPanelInsideActiveTabBorder->setLeftWidth(0);
		WindowsTabPanelInsideActiveTabBorder->setRightWidth(0);
		WindowsTabPanelInsideActiveTabBorder->setTopWidth(3);
		WindowsTabPanelInsideActiveTabBorder->setBottomWidth(0);
		WindowsTabPanelInsideActiveTabBorder->setColor(Color4f(1.0, 0.78, 0.24, 1.0));
	endEditCP(WindowsTabPanelInsideActiveTabBorder);

	CompoundBorderPtr WindowsTabPanelActiveTabBorder = CompoundBorder::create();
	beginEditCP(WindowsTabPanelActiveTabBorder);
        WindowsTabPanelActiveTabBorder->setInnerBorder(WindowsTabPanelInsideActiveTabBorder);
        WindowsTabPanelActiveTabBorder->setOuterBorder(WindowsTabPanelTabBorder);
	endEditCP(WindowsTabPanelActiveTabBorder);

	GradientUIBackgroundPtr WindowsTabPanelTabBackground = GradientUIBackground::create();
	beginEditCP(WindowsTabPanelTabBackground);
		WindowsTabPanelTabBackground->setColorStart(Color4f(1.0,1.0,1.0,1.0));
		WindowsTabPanelTabBackground->setColorEnd(Color4f(0.75,0.75,0.85,1.0));
		WindowsTabPanelTabBackground->setOrientation(GradientUIBackground::VERTICAL_ORIENTATION);
	endEditCP(WindowsTabPanelTabBackground);
	
	ColorUIBackgroundPtr WindowsTabPanelTabActiveBackground = ColorUIBackground::create();
	beginEditCP(WindowsTabPanelTabActiveBackground);
		WindowsTabPanelTabActiveBackground->setColor(Color4f(0.9569,0.9529,0.9373,1.0));
	endEditCP(WindowsTabPanelTabActiveBackground);

	LineBorderPtr WindowsTabPanelContentBorder = LineBorder::create();
	beginEditCP(WindowsTabPanelContentBorder);
		WindowsTabPanelContentBorder->setWidth(1);
		WindowsTabPanelContentBorder->setColor(Color4f(0.57, 0.61, 0.61 ,1.0));
	endEditCP(WindowsTabPanelContentBorder);
	//Windows TabPanel
	beginEditCP(WindowsTabPanel);
		WindowsTabPanel->setEnabled(true);
		WindowsTabPanel->setVisible(true);
		
		WindowsTabPanel->setConstraints(NullFC);
		//Sizes
		WindowsTabPanel->setMinSize(Vec2f(0,0));
		WindowsTabPanel->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsTabPanel->setPreferredSize(Vec2f(100,100));

		//Border
		WindowsTabPanel->setBorders(WindowsEmptyBorder);
		
		//Background
		WindowsTabPanel->setBackgrounds(WindowsEmptyBackground);
		
		//Opacity
		WindowsTabPanel->setOpacity(1.0);

		//TabPanel
		WindowsTabPanel->setTabPlacement(TabPanel::PLACEMENT_NORTH);
		WindowsTabPanel->setTabAlignment(0.0f);
		WindowsTabPanel->setTabRotation(TabPanel::CLOCKWISE_0);
		WindowsTabPanel->setTabBorderInsets(Vec2f(0.0f,0.0f));
		
		WindowsTabPanel->setTabBorder(WindowsTabPanelTabBorder);
		WindowsTabPanel->setTabActiveBorder(WindowsTabPanelActiveTabBorder);
		WindowsTabPanel->setTabDisabledBorder(WindowsTabPanelTabBorder);
		WindowsTabPanel->setTabRolloverBorder(WindowsTabPanelActiveTabBorder);
		WindowsTabPanel->setTabFocusedBorder(WindowsTabPanelTabBorder);
		
		WindowsTabPanel->setTabBackground(WindowsTabPanelTabBackground);
		WindowsTabPanel->setTabActiveBackground(WindowsTabPanelTabActiveBackground);
		WindowsTabPanel->setTabDisabledBackground(WindowsTabPanelTabBackground);
		WindowsTabPanel->setTabRolloverBackground(WindowsTabPanelTabBackground);
		WindowsTabPanel->setTabFocusedBackground(WindowsTabPanelTabBackground);
		
		WindowsTabPanel->setContentBorder(WindowsTabPanelContentBorder);
		WindowsTabPanel->setContentDisabledBorder(WindowsTabPanelContentBorder);
		WindowsTabPanel->setContentRolloverBorder(WindowsTabPanelContentBorder);
		
		WindowsTabPanel->setContentBackground(WindowsTabPanelTabActiveBackground);
		WindowsTabPanel->setContentDisabledBackground(WindowsTabPanelTabActiveBackground);
		WindowsTabPanel->setContentRolloverBackground(WindowsTabPanelTabActiveBackground);
        WindowsTabPanel->setSelectionModel(DefaultSingleSelectionModel::create());
	endEditCP(WindowsTabPanel);

	//************************** ImageComponent *****************************
	//Windows ImageComponentBorder
	EmptyBorderPtr WindowsImageComponentBorder = EmptyBorder::create();

	//Windows ImageComponentBackground
	EmptyUIBackgroundPtr WindowsImageComponentBackground = EmptyUIBackground::create();

	//Windows ImageComponent
	beginEditCP(WindowsImageComponent);
		WindowsImageComponent->setEnabled(true);
		WindowsImageComponent->setVisible(true);
		
		WindowsImageComponent->setConstraints(NullFC);
		//Sizes
		WindowsImageComponent->setMinSize(Vec2f(0,0));
		WindowsImageComponent->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsImageComponent->setPreferredSize(Vec2f(100,100));
		WindowsImageComponent->setSize(Vec2f(0,0));

		//Border
		WindowsImageComponent->setBorders(WindowsImageComponentBorder);
		
		//Background
		WindowsImageComponent->setBackgrounds(WindowsImageComponentBackground);
		
		//Opacity
		WindowsImageComponent->setOpacity(1.0);

		//Image Alignment
		WindowsImageComponent->setScale(ImageComponent::SCALE_NONE);
		WindowsImageComponent->setVerticalAlignment(0.5);
		WindowsImageComponent->setHorizontalAlignment(0.5);
	endEditCP(WindowsImageComponent);

	
	//************************** Checkbox Button Component *****************************
	UIDrawObjectCanvasPtr WindowsCheckboxDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsSelectedCheckboxDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsActiveCheckboxDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsActiveSelectedCheckboxDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsRolloverCheckboxDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsRolloverSelectedCheckboxDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsDisabledCheckboxDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsDisabledSelectedCheckboxDrawObject = UIDrawObjectCanvas::create();

    //Normal Background
	MultiColoredQuadUIDrawObjectPtr CheckboxBackground = MultiColoredQuadUIDrawObject::create();
	beginEditCP(CheckboxBackground);
        CheckboxBackground->setPoint1(Pnt2f(1,1));
        CheckboxBackground->setPoint2(Pnt2f(12,1));
        CheckboxBackground->setPoint3(Pnt2f(12,12));
        CheckboxBackground->setPoint4(Pnt2f(1,12));
		CheckboxBackground->setColor1(Color4f(.86,.86,.84,1.0));
		CheckboxBackground->setColor2(Color4f(.95,.95,.94,1.0));
		CheckboxBackground->setColor3(Color4f(1.0,1.0,1.0,1.0));
		CheckboxBackground->setColor4(Color4f(.95,.95,.94,1.0));
		CheckboxBackground->setOpacity(1.0);
	endEditCP(CheckboxBackground);

    //Normal Border
	RectUIDrawObjectPtr CheckboxBackgroundBorder = RectUIDrawObject::create();
	beginEditCP(CheckboxBackgroundBorder);
		CheckboxBackgroundBorder->setTopLeft(Pnt2f(0,0));
		CheckboxBackgroundBorder->setBottomRight(Pnt2f(13,13));
		CheckboxBackgroundBorder->setColor(Color4f(.110,.318,.502,1.0));
		CheckboxBackgroundBorder->setOpacity(1.0);
	endEditCP(CheckboxBackgroundBorder);

    //Active Background
	MultiColoredQuadUIDrawObjectPtr CheckboxActiveBackground = MultiColoredQuadUIDrawObject::create();
	beginEditCP(CheckboxActiveBackground);
        CheckboxActiveBackground->setPoint1(Pnt2f(1,1));
        CheckboxActiveBackground->setPoint2(Pnt2f(12,1));
        CheckboxActiveBackground->setPoint3(Pnt2f(12,12));
        CheckboxActiveBackground->setPoint4(Pnt2f(1,12));
		CheckboxActiveBackground->setColor1(Color4f(.69,.69,.65,1.0));
		CheckboxActiveBackground->setColor2(Color4f(.95,.94,.87,1.0));
		CheckboxActiveBackground->setColor3(Color4f(1.0,1.0,1.0,1.0));
		CheckboxActiveBackground->setColor4(Color4f(.84,.84,.78,1.0));
		CheckboxActiveBackground->setOpacity(1.0);
	endEditCP(CheckboxActiveBackground);
    
    //Disabled Background
	RectUIDrawObjectPtr CheckboxDisabledBackground = RectUIDrawObject::create();
	beginEditCP(CheckboxDisabledBackground);
		CheckboxDisabledBackground->setTopLeft(Pnt2f(1,1));
		CheckboxDisabledBackground->setBottomRight(Pnt2f(12,12));
		CheckboxDisabledBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
		CheckboxDisabledBackground->setOpacity(1.0);
	endEditCP(CheckboxDisabledBackground);

    //Disabled Border
	RectUIDrawObjectPtr CheckboxDisabledBackgroundBorder = RectUIDrawObject::create();
	beginEditCP(CheckboxDisabledBackgroundBorder);
		CheckboxDisabledBackgroundBorder->setTopLeft(Pnt2f(0,0));
		CheckboxDisabledBackgroundBorder->setBottomRight(Pnt2f(13,13));
		CheckboxDisabledBackgroundBorder->setColor(Color4f(.79,.78,.73,1.0));
		CheckboxDisabledBackgroundBorder->setOpacity(1.0);
	endEditCP(CheckboxDisabledBackgroundBorder);

    //The Checkmark
    Color4f CheckmarkColor(0.13,0.63,0.13,1.0);
	MultiColoredQuadUIDrawObjectPtr CheckboxCheckQuad1 = MultiColoredQuadUIDrawObject::create();
	beginEditCP(CheckboxCheckQuad1);
        CheckboxCheckQuad1->setPoint1(Pnt2f(3,4));
        CheckboxCheckQuad1->setPoint2(Pnt2f(6,7));
        CheckboxCheckQuad1->setPoint3(Pnt2f(6,10));
        CheckboxCheckQuad1->setPoint4(Pnt2f(3,7));
		CheckboxCheckQuad1->setColor1(CheckmarkColor);
		CheckboxCheckQuad1->setColor2(CheckmarkColor);
		CheckboxCheckQuad1->setColor3(CheckmarkColor);
		CheckboxCheckQuad1->setColor4(CheckmarkColor);
		CheckboxCheckQuad1->setOpacity(1.0);
	endEditCP(CheckboxCheckQuad1);

	MultiColoredQuadUIDrawObjectPtr CheckboxCheckQuad2 = MultiColoredQuadUIDrawObject::create();
	beginEditCP(CheckboxCheckQuad2);
        CheckboxCheckQuad2->setPoint1(Pnt2f(6,7));
        CheckboxCheckQuad2->setPoint2(Pnt2f(10,3));
        CheckboxCheckQuad2->setPoint3(Pnt2f(10,6));
        CheckboxCheckQuad2->setPoint4(Pnt2f(6,10));
		CheckboxCheckQuad2->setColor1(CheckmarkColor);
		CheckboxCheckQuad2->setColor2(CheckmarkColor);
		CheckboxCheckQuad2->setColor3(CheckmarkColor);
		CheckboxCheckQuad2->setColor4(CheckmarkColor);
		CheckboxCheckQuad2->setOpacity(1.0);
	endEditCP(CheckboxCheckQuad2);
    
    //The Disabled Checkmark
    Color4f CheckmarkDisabledColor(0.79,0.78,0.73,1.0);
	MultiColoredQuadUIDrawObjectPtr CheckboxDisabledCheckQuad1 = MultiColoredQuadUIDrawObject::create();
	beginEditCP(CheckboxDisabledCheckQuad1);
        CheckboxDisabledCheckQuad1->setPoint1(Pnt2f(3,4));
        CheckboxDisabledCheckQuad1->setPoint2(Pnt2f(6,7));
        CheckboxDisabledCheckQuad1->setPoint3(Pnt2f(6,10));
        CheckboxDisabledCheckQuad1->setPoint4(Pnt2f(3,7));
		CheckboxDisabledCheckQuad1->setColor1(CheckmarkDisabledColor);
		CheckboxDisabledCheckQuad1->setColor2(CheckmarkDisabledColor);
		CheckboxDisabledCheckQuad1->setColor3(CheckmarkDisabledColor);
		CheckboxDisabledCheckQuad1->setColor4(CheckmarkDisabledColor);
		CheckboxDisabledCheckQuad1->setOpacity(1.0);
	endEditCP(CheckboxDisabledCheckQuad1);

	MultiColoredQuadUIDrawObjectPtr CheckboxDisabledCheckQuad2 = MultiColoredQuadUIDrawObject::create();
	beginEditCP(CheckboxDisabledCheckQuad2);
        CheckboxDisabledCheckQuad2->setPoint1(Pnt2f(6,7));
        CheckboxDisabledCheckQuad2->setPoint2(Pnt2f(10,3));
        CheckboxDisabledCheckQuad2->setPoint3(Pnt2f(10,6));
        CheckboxDisabledCheckQuad2->setPoint4(Pnt2f(6,10));
		CheckboxDisabledCheckQuad2->setColor1(CheckmarkDisabledColor);
		CheckboxDisabledCheckQuad2->setColor2(CheckmarkDisabledColor);
		CheckboxDisabledCheckQuad2->setColor3(CheckmarkDisabledColor);
		CheckboxDisabledCheckQuad2->setColor4(CheckmarkDisabledColor);
		CheckboxDisabledCheckQuad2->setOpacity(1.0);
	endEditCP(CheckboxDisabledCheckQuad2);

    //Normal
	beginEditCP(WindowsCheckboxDrawObject);
	   WindowsCheckboxDrawObject->getDrawObjects().push_back(CheckboxBackgroundBorder);
	   WindowsCheckboxDrawObject->getDrawObjects().push_back(CheckboxBackground);
	endEditCP(WindowsCheckboxDrawObject);

    //Normal Selected
	beginEditCP(WindowsSelectedCheckboxDrawObject);
		WindowsSelectedCheckboxDrawObject->getDrawObjects().push_back(CheckboxBackgroundBorder);
		WindowsSelectedCheckboxDrawObject->getDrawObjects().push_back(CheckboxBackground);
		WindowsSelectedCheckboxDrawObject->getDrawObjects().push_back(CheckboxCheckQuad1);
		WindowsSelectedCheckboxDrawObject->getDrawObjects().push_back(CheckboxCheckQuad2);
	endEditCP(WindowsSelectedCheckboxDrawObject);

    //Active Selected
	beginEditCP(WindowsActiveSelectedCheckboxDrawObject);
	 	WindowsActiveSelectedCheckboxDrawObject->getDrawObjects().push_back(CheckboxBackgroundBorder);
		WindowsActiveSelectedCheckboxDrawObject->getDrawObjects().push_back(CheckboxBackground);
		WindowsActiveSelectedCheckboxDrawObject->getDrawObjects().push_back(CheckboxActiveBackground);
	endEditCP(WindowsActiveSelectedCheckboxDrawObject);

    //Active Non-selected
	beginEditCP(WindowsActiveCheckboxDrawObject);
		WindowsActiveCheckboxDrawObject->getDrawObjects().push_back(CheckboxBackgroundBorder);
		WindowsActiveCheckboxDrawObject->getDrawObjects().push_back(CheckboxBackground);
		WindowsActiveCheckboxDrawObject->getDrawObjects().push_back(CheckboxActiveBackground);
		WindowsActiveCheckboxDrawObject->getDrawObjects().push_back(CheckboxCheckQuad1);
		WindowsActiveCheckboxDrawObject->getDrawObjects().push_back(CheckboxCheckQuad2);
	endEditCP(WindowsActiveCheckboxDrawObject);


    //Rollover Border
	MultiColoredQuadUIDrawObjectPtr RolloverCheckboxBorder = MultiColoredQuadUIDrawObject::create();
	beginEditCP(RolloverCheckboxBorder);
        RolloverCheckboxBorder->setPoint1(Pnt2f(1,1));
        RolloverCheckboxBorder->setPoint2(Pnt2f(12,1));
        RolloverCheckboxBorder->setPoint3(Pnt2f(12,12));
        RolloverCheckboxBorder->setPoint4(Pnt2f(1,12));
		RolloverCheckboxBorder->setColor1(Color4f(1.0,.94,.81,1.0));
		RolloverCheckboxBorder->setColor2(Color4f(.98,.78,.39,1.0));
		RolloverCheckboxBorder->setColor3(Color4f(0.97,0.70,0.19,1.0));
		RolloverCheckboxBorder->setColor4(Color4f(.98,.78,.39,1.0));
		RolloverCheckboxBorder->setOpacity(1.0);
	endEditCP(RolloverCheckboxBorder);

	RectUIDrawObjectPtr RolloverCheckboxBackground = RectUIDrawObject::create();
	beginEditCP(RolloverCheckboxBackground);
		RolloverCheckboxBackground->setTopLeft(Pnt2f(3,3));
		RolloverCheckboxBackground->setBottomRight(Pnt2f(10,10));
		RolloverCheckboxBackground->setColor(Color4f(0.91,.91,.89,1.0));
		RolloverCheckboxBackground->setOpacity(1.0);
	endEditCP(RolloverCheckboxBackground);

    //Rollover Selected
	beginEditCP(WindowsRolloverSelectedCheckboxDrawObject);
		WindowsRolloverSelectedCheckboxDrawObject->getDrawObjects().push_back(CheckboxBackgroundBorder);
		WindowsRolloverSelectedCheckboxDrawObject->getDrawObjects().push_back(RolloverCheckboxBorder);
		WindowsRolloverSelectedCheckboxDrawObject->getDrawObjects().push_back(RolloverCheckboxBackground);
		WindowsRolloverSelectedCheckboxDrawObject->getDrawObjects().push_back(CheckboxCheckQuad1);
		WindowsRolloverSelectedCheckboxDrawObject->getDrawObjects().push_back(CheckboxCheckQuad2);
	endEditCP(WindowsRolloverSelectedCheckboxDrawObject);

    //Rollover Non-selected
	beginEditCP(WindowsRolloverCheckboxDrawObject);
		WindowsRolloverCheckboxDrawObject->getDrawObjects().push_back(CheckboxBackgroundBorder);
		WindowsRolloverCheckboxDrawObject->getDrawObjects().push_back(RolloverCheckboxBorder);
		WindowsRolloverCheckboxDrawObject->getDrawObjects().push_back(RolloverCheckboxBackground);
	endEditCP(WindowsRolloverCheckboxDrawObject);

    //Disabled Selected
	beginEditCP(WindowsDisabledSelectedCheckboxDrawObject);
		WindowsDisabledSelectedCheckboxDrawObject->getDrawObjects().push_back(CheckboxDisabledBackgroundBorder);
		WindowsDisabledSelectedCheckboxDrawObject->getDrawObjects().push_back(CheckboxDisabledBackground);
		WindowsDisabledSelectedCheckboxDrawObject->getDrawObjects().push_back(RolloverCheckboxBackground);
		WindowsDisabledSelectedCheckboxDrawObject->getDrawObjects().push_back(CheckboxDisabledCheckQuad1);
		WindowsDisabledSelectedCheckboxDrawObject->getDrawObjects().push_back(CheckboxDisabledCheckQuad2);
	endEditCP(WindowsDisabledSelectedCheckboxDrawObject);

    //Disabled Non-selected
	beginEditCP(WindowsDisabledCheckboxDrawObject);
		WindowsDisabledCheckboxDrawObject->getDrawObjects().push_back(CheckboxDisabledBackgroundBorder);
		WindowsDisabledCheckboxDrawObject->getDrawObjects().push_back(CheckboxDisabledBackground);
	endEditCP(WindowsDisabledCheckboxDrawObject);

    //Border
	EmptyBorderPtr WindowsCheckboxButtonBorder = EmptyBorder::create();

    //Background
	EmptyUIBackgroundPtr WindowsCheckboxButtonBackground = EmptyUIBackground::create();

	beginEditCP(WindowsCheckboxButton);
		WindowsCheckboxButton->setEnabled(true);
		WindowsCheckboxButton->setVisible(true);
		
		WindowsCheckboxButton->setConstraints(NullFC);
		//Sizes
		WindowsCheckboxButton->setMinSize(Vec2f(0,0));
		WindowsCheckboxButton->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsCheckboxButton->setPreferredSize(Vec2f(75,23));
		WindowsCheckboxButton->setSize(Vec2f(0,0));

        //Draw Objects
		WindowsCheckboxButton->setCheckboxDrawObject(WindowsCheckboxDrawObject);
		WindowsCheckboxButton->setSelectedCheckboxDrawObject(WindowsSelectedCheckboxDrawObject);
		WindowsCheckboxButton->setActiveCheckboxDrawObject(WindowsActiveCheckboxDrawObject);
		WindowsCheckboxButton->setActiveSelectedCheckboxDrawObject(WindowsActiveSelectedCheckboxDrawObject);
		WindowsCheckboxButton->setRolloverCheckboxDrawObject(WindowsRolloverCheckboxDrawObject);
		WindowsCheckboxButton->setRolloverSelectedCheckboxDrawObject(WindowsRolloverSelectedCheckboxDrawObject);
		WindowsCheckboxButton->setDisabledCheckboxDrawObject(WindowsDisabledCheckboxDrawObject);
		WindowsCheckboxButton->setDisabledSelectedCheckboxDrawObject(WindowsDisabledSelectedCheckboxDrawObject);

		//Border
		WindowsCheckboxButton->setBorder(WindowsCheckboxButtonBorder);
		WindowsCheckboxButton->setRolloverBorder(WindowsCheckboxButtonBorder);
		WindowsCheckboxButton->setFocusedBorder(WindowsCheckboxButtonBorder);
		WindowsCheckboxButton->setDisabledBorder(WindowsCheckboxButtonBorder);
		WindowsCheckboxButton->setActiveBorder(WindowsCheckboxButtonBorder);
		
		//Background
		WindowsCheckboxButton->setBackground(WindowsCheckboxButtonBackground);
		WindowsCheckboxButton->setRolloverBackground(WindowsCheckboxButtonBackground);
		WindowsCheckboxButton->setFocusedBackground(WindowsCheckboxButtonBackground);
		WindowsCheckboxButton->setDisabledBackground(WindowsCheckboxButtonBackground);
		WindowsCheckboxButton->setActiveBackground(WindowsCheckboxButtonBackground);
		
		//Opacity
		WindowsCheckboxButton->setOpacity(1.0);

		//Text
		WindowsCheckboxButton->setText("");
		WindowsCheckboxButton->setFont(WindowsFont);
		WindowsCheckboxButton->setVerticalAlignment(0.5);
		WindowsCheckboxButton->setHorizontalAlignment(0.5);
		WindowsCheckboxButton->setTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsCheckboxButton->setActiveTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsCheckboxButton->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsCheckboxButton->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsCheckboxButton->setDisabledTextColor(WindowsDisabledTextColor);
        
        WindowsCheckboxButton->setActiveOffset(Vec2f(0,0));
	endEditCP(WindowsCheckboxButton);

	//************************** Radio Button Component *****************************
	UIDrawObjectCanvasPtr WindowsRadioDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsSelectedRadioDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsActiveRadioDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsActiveSelectedRadioDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsRolloverRadioDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsRolloverSelectedRadioDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsDisabledRadioDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsDisabledSelectedRadioDrawObject = UIDrawObjectCanvas::create();

    Pnt2f RadioUIDrawObjectsCenter(6,6);
	DiscUIDrawObjectPtr RadioBackground = DiscUIDrawObject::create();
	beginEditCP(RadioBackground);
		RadioBackground->setWidth(6);
		RadioBackground->setHeight(6);
		RadioBackground->setSubDivisions(30);
		RadioBackground->setStartAngleRad(0);
		RadioBackground->setEndAngleRad(6.28318531);
		RadioBackground->setCenterColor(Color4f(.945,.945,.937,1.0));
		RadioBackground->setOuterColor(Color4f(.945,.945,.937,1.0));
		RadioBackground->setOpacity(1.0);
		RadioBackground->setCenter(RadioUIDrawObjectsCenter);
	endEditCP(RadioBackground);

	ArcUIDrawObjectPtr RadioBackgroundBorder = ArcUIDrawObject::create();
	beginEditCP(RadioBackgroundBorder);
		RadioBackgroundBorder->setWidth(6);
		RadioBackgroundBorder->setHeight(6);
		RadioBackgroundBorder->setSubDivisions(25);
		RadioBackgroundBorder->setStartAngleRad(0);
		RadioBackgroundBorder->setEndAngleRad(6.28318531);
		RadioBackgroundBorder->setColor(Color4f(0.137,0.337,0.510,1.0));
		RadioBackgroundBorder->setOpacity(0.90);
		RadioBackgroundBorder->setLineWidth(1);
		RadioBackgroundBorder->setCenter(RadioUIDrawObjectsCenter);
	endEditCP(RadioBackgroundBorder);

	DiscUIDrawObjectPtr RadioSelected = DiscUIDrawObject::create();
	beginEditCP(RadioSelected);
		RadioSelected->setWidth(3);
		RadioSelected->setHeight(3);
		RadioSelected->setSubDivisions(15);
		RadioSelected->setStartAngleRad(0);
		RadioSelected->setEndAngleRad(6.28318531);
		RadioSelected->setCenterColor(Color4f(0.220,0.725,0.208,1.0));
		RadioSelected->setOuterColor(Color4f(0.220,0.725,0.208,0.6));
		RadioSelected->setOpacity(1.0);
		RadioSelected->setCenter(RadioUIDrawObjectsCenter);
	endEditCP(RadioSelected);

	DiscUIDrawObjectPtr RadioActiveBackground = DiscUIDrawObject::create();
	beginEditCP(RadioActiveBackground);
		RadioActiveBackground->setWidth(6);
		RadioActiveBackground->setHeight(6);
		RadioActiveBackground->setSubDivisions(30);
		RadioActiveBackground->setStartAngleRad(0);
		RadioActiveBackground->setEndAngleRad(6.28318531);
		RadioActiveBackground->setCenterColor(Color4f(.804,.800,.753,1.0));
		RadioActiveBackground->setOuterColor(Color4f(.804,.800,.753,1.0));
		RadioActiveBackground->setOpacity(1.0);
		RadioActiveBackground->setCenter(RadioUIDrawObjectsCenter);
	endEditCP(RadioActiveBackground);
    
    //Disabled Draw Objects
	DiscUIDrawObjectPtr RadioDisabledBackground = DiscUIDrawObject::create();
	beginEditCP(RadioDisabledBackground);
		RadioDisabledBackground->setWidth(6);
		RadioDisabledBackground->setHeight(6);
		RadioDisabledBackground->setSubDivisions(30);
		RadioDisabledBackground->setStartAngleRad(0);
		RadioDisabledBackground->setEndAngleRad(6.28318531);
		RadioDisabledBackground->setCenterColor(Color4f(.98,.97,.97,1.0));
		RadioDisabledBackground->setOuterColor(Color4f(.98,.97,.97,1.0));
		RadioDisabledBackground->setOpacity(1.0);
		RadioDisabledBackground->setCenter(RadioUIDrawObjectsCenter);
	endEditCP(RadioDisabledBackground);

	ArcUIDrawObjectPtr RadioDisabledBackgroundBorder = ArcUIDrawObject::create();
	beginEditCP(RadioDisabledBackgroundBorder);
		RadioDisabledBackgroundBorder->setWidth(6);
		RadioDisabledBackgroundBorder->setHeight(6);
		RadioDisabledBackgroundBorder->setSubDivisions(25);
		RadioDisabledBackgroundBorder->setStartAngleRad(0);
		RadioDisabledBackgroundBorder->setEndAngleRad(6.28318531);
		RadioDisabledBackgroundBorder->setColor(Color4f(0.75,0.75,0.71,1.0));
		RadioDisabledBackgroundBorder->setOpacity(0.90);
		RadioDisabledBackgroundBorder->setLineWidth(1);
		RadioDisabledBackgroundBorder->setCenter(RadioUIDrawObjectsCenter);
	endEditCP(RadioDisabledBackgroundBorder);
    
	DiscUIDrawObjectPtr RadioDisabledSelected = DiscUIDrawObject::create();
	beginEditCP(RadioDisabledSelected);
		RadioDisabledSelected->setWidth(3);
		RadioDisabledSelected->setHeight(3);
		RadioDisabledSelected->setSubDivisions(15);
		RadioDisabledSelected->setStartAngleRad(0);
		RadioDisabledSelected->setEndAngleRad(6.28318531);
		RadioDisabledSelected->setCenterColor(Color4f(0.75,0.75,0.71,1.0));
		RadioDisabledSelected->setOuterColor(Color4f(0.75,0.75,0.71,0.6));
		RadioDisabledSelected->setOpacity(1.0);
		RadioDisabledSelected->setCenter(RadioUIDrawObjectsCenter);
	endEditCP(RadioSelected);

	// Yellow highlight border for whenever there is a hover listener
	ArcUIDrawObjectPtr RadioRolloverBorder = ArcUIDrawObject::create();
	beginEditCP(RadioRolloverBorder);
		RadioRolloverBorder->setWidth(5);
		RadioRolloverBorder->setHeight(5);
		RadioRolloverBorder->setSubDivisions(25);
		RadioRolloverBorder->setStartAngleRad(0);
		RadioRolloverBorder->setEndAngleRad(6.28318531);
		RadioRolloverBorder->setColor(Color4f(.980,.753,.306,1.0));
		RadioRolloverBorder->setOpacity(.85);
		RadioRolloverBorder->setCenter(RadioUIDrawObjectsCenter);
		RadioRolloverBorder->setLineWidth(2);
	endEditCP(RadioRolloverBorder);

	beginEditCP(WindowsRadioDrawObject);
		WindowsRadioDrawObject->getDrawObjects().push_back(RadioBackground);
		WindowsRadioDrawObject->getDrawObjects().push_back(RadioBackgroundBorder);
	endEditCP(WindowsRadioDrawObject);

	beginEditCP(WindowsSelectedRadioDrawObject);
		WindowsSelectedRadioDrawObject->getDrawObjects().push_back(RadioBackground);
		WindowsSelectedRadioDrawObject->getDrawObjects().push_back(RadioBackgroundBorder);
		WindowsSelectedRadioDrawObject->getDrawObjects().push_back(RadioSelected);
	endEditCP(WindowsSelectedRadioDrawObject);

	beginEditCP(WindowsActiveRadioDrawObject);
		WindowsActiveRadioDrawObject->getDrawObjects().push_back(RadioActiveBackground);
		WindowsActiveRadioDrawObject->getDrawObjects().push_back(RadioBackgroundBorder);
		WindowsActiveRadioDrawObject->getDrawObjects().push_back(RadioSelected);
	endEditCP(WindowsActiveRadioDrawObject);

	beginEditCP(WindowsActiveSelectedRadioDrawObject);
		WindowsActiveSelectedRadioDrawObject->getDrawObjects().push_back(RadioActiveBackground);
		WindowsActiveSelectedRadioDrawObject->getDrawObjects().push_back(RadioBackgroundBorder);
	endEditCP(WindowsActiveSelectedRadioDrawObject);
    
    //Rollover Not Selected
	beginEditCP(WindowsRolloverRadioDrawObject);
		WindowsRolloverRadioDrawObject->getDrawObjects().push_back(RadioBackground);
		WindowsRolloverRadioDrawObject->getDrawObjects().push_back(RadioBackgroundBorder);
		WindowsRolloverRadioDrawObject->getDrawObjects().push_back(RadioRolloverBorder);
	endEditCP(WindowsRolloverRadioDrawObject);

    //Rollover Selected
	beginEditCP(WindowsRolloverSelectedRadioDrawObject);
		WindowsRolloverSelectedRadioDrawObject->getDrawObjects().push_back(RadioBackground);
		WindowsRolloverSelectedRadioDrawObject->getDrawObjects().push_back(RadioBackgroundBorder);
		WindowsRolloverSelectedRadioDrawObject->getDrawObjects().push_back(RadioRolloverBorder);
		WindowsRolloverSelectedRadioDrawObject->getDrawObjects().push_back(RadioSelected);
	endEditCP(WindowsRolloverSelectedRadioDrawObject);
    
    //Disabled Not Selected
	beginEditCP(WindowsDisabledRadioDrawObject);
		WindowsDisabledRadioDrawObject->getDrawObjects().push_back(RadioDisabledBackground);
		WindowsDisabledRadioDrawObject->getDrawObjects().push_back(RadioDisabledBackgroundBorder);
	endEditCP(WindowsDisabledRadioDrawObject);

    //Disabled Selected
	beginEditCP(WindowsDisabledSelectedRadioDrawObject);
		WindowsDisabledSelectedRadioDrawObject->getDrawObjects().push_back(RadioDisabledBackground);
		WindowsDisabledSelectedRadioDrawObject->getDrawObjects().push_back(RadioDisabledBackgroundBorder);
		WindowsDisabledSelectedRadioDrawObject->getDrawObjects().push_back(RadioDisabledSelected);
	endEditCP(WindowsDisabledSelectedRadioDrawObject);
		
	EmptyBorderPtr WindowsRadioButtonBorder = EmptyBorder::create();
	EmptyUIBackgroundPtr WindowsRadioButtonBackground = EmptyUIBackground::create();
	

	beginEditCP(WindowsRadioButton);
		WindowsRadioButton->setEnabled(true);
		WindowsRadioButton->setVisible(true);
		WindowsRadioButton->setConstraints(NullFC);

		//sizes
		WindowsRadioButton->setMinSize(Vec2f(0, 0));
		WindowsRadioButton->setMaxSize(Vec2f(32767,32767));
		WindowsRadioButton->setPreferredSize(Vec2f(75,23));

		//draw objects
		WindowsRadioButton->setRadioDrawObject(WindowsRadioDrawObject);
		WindowsRadioButton->setSelectedRadioDrawObject(WindowsSelectedRadioDrawObject);
		WindowsRadioButton->setActiveRadioDrawObject(WindowsActiveRadioDrawObject);
		WindowsRadioButton->setActiveSelectedRadioDrawObject(WindowsActiveSelectedRadioDrawObject);
		WindowsRadioButton->setRolloverRadioDrawObject(WindowsRolloverRadioDrawObject);
		WindowsRadioButton->setRolloverSelectedRadioDrawObject(WindowsRolloverSelectedRadioDrawObject);
		WindowsRadioButton->setDisabledRadioDrawObject(WindowsDisabledRadioDrawObject);
		WindowsRadioButton->setDisabledSelectedRadioDrawObject(WindowsDisabledSelectedRadioDrawObject);

		//Border
		WindowsRadioButton->setBorder(WindowsRadioButtonBorder);
		WindowsRadioButton->setRolloverBorder(WindowsRadioButtonBorder);
		WindowsRadioButton->setFocusedBorder(WindowsRadioButtonBorder);
		WindowsRadioButton->setDisabledBorder(WindowsRadioButtonBorder);
		WindowsRadioButton->setActiveBorder(WindowsRadioButtonBorder);
		
		//Background
		WindowsRadioButton->setBackground(WindowsRadioButtonBackground);
		WindowsRadioButton->setRolloverBackground(WindowsRadioButtonBackground);
		WindowsRadioButton->setFocusedBackground(WindowsRadioButtonBackground);
		WindowsRadioButton->setDisabledBackground(WindowsRadioButtonBackground);
		WindowsRadioButton->setActiveBackground(WindowsRadioButtonBackground);

        //Opacity
		WindowsRadioButton->setOpacity(1.0);

		//text
		WindowsRadioButton->setText("");
		WindowsRadioButton->setFont(WindowsFont);

		//alignment
		WindowsRadioButton->setVerticalAlignment(0.5);
		WindowsRadioButton->setHorizontalAlignment(0.5);
		WindowsRadioButton->setTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsRadioButton->setActiveTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsRadioButton->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsRadioButton->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsRadioButton->setDisabledTextColor(WindowsDisabledTextColor);

        WindowsRadioButton->setActiveOffset(Vec2f(0,0));
	endEditCP(WindowsRadioButton);

	/********Toggle Button********/

	beginEditCP(WindowsToggleButton);
		WindowsToggleButton->setEnabled(true);
		WindowsToggleButton->setVisible(true);
		
		WindowsToggleButton->setConstraints(NullFC);
		//Sizes
		WindowsToggleButton->setMinSize(Vec2f(0,0));
		WindowsToggleButton->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsToggleButton->setPreferredSize(Vec2f(75,23));

		//Border
		WindowsToggleButton->setBorder(WindowsButtonBorder);
		WindowsToggleButton->setRolloverBorder(WindowsRolloverButtonBorder);
		WindowsToggleButton->setFocusedBorder(WindowsButtonBorder);
		WindowsToggleButton->setDisabledBorder(WindowsDisabledButtonBorder);
		WindowsToggleButton->setActiveBorder(WindowsActiveButtonBorder);
		
		//Background
		WindowsToggleButton->setBackground(WindowsButtonBackground);
		WindowsToggleButton->setRolloverBackground(WindowsRolloverButtonBackground);
		WindowsToggleButton->setFocusedBackground(WindowsButtonBackground);
		WindowsToggleButton->setDisabledBackground(WindowsDisabledButtonBackground);
		WindowsToggleButton->setActiveBackground(WindowsActiveButtonBackground);
		
		//Opacity
		WindowsToggleButton->setOpacity(1.0);

		//Text
		WindowsToggleButton->setText("");
		WindowsToggleButton->setFont(WindowsFont);
		WindowsToggleButton->setVerticalAlignment(0.5);
		WindowsToggleButton->setHorizontalAlignment(0.5);
		WindowsToggleButton->setTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsToggleButton->setActiveTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsToggleButton->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsToggleButton->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsToggleButton->setDisabledTextColor(WindowsDisabledTextColor);
        
        WindowsToggleButton->setActiveOffset(Vec2f(2,2));
	endEditCP(WindowsToggleButton);

	/********Text Field********/
	ColorUIBackgroundPtr WindowsTextFieldBackground = ColorUIBackground::create();
	beginEditCP(WindowsTextFieldBackground);
		WindowsTextFieldBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
	endEditCP(WindowsTextFieldBackground);

	ColorUIBackgroundPtr WindowsDisabledTextFieldBackground = ColorUIBackground::create();
	beginEditCP(WindowsDisabledTextFieldBackground);
		WindowsDisabledTextFieldBackground->setColor(Color4f(.8, .8, .8, 1.0));
	endEditCP(WindowsDisabledTextFieldBackground);

	LineBorderPtr WindowsTextFieldBorder = LineBorder::create();
	beginEditCP(WindowsTextFieldBorder);
		WindowsTextFieldBorder->setWidth(1);
		WindowsTextFieldBorder->setColor( Color4f(.498,.616,.725,1.0) );
	endEditCP(WindowsTextFieldBorder);


	beginEditCP(WindowsTextField);
		//size
		WindowsTextField->setMinSize(Vec2f(0, 0));
		WindowsTextField->setMaxSize(Vec2f(32767,32767));
		WindowsTextField->setPreferredSize(Vec2f(75,23));

		//font
		WindowsTextField->setFont(WindowsFont);
		
		WindowsTextField->setSelectionBoxColor(Color4f(.682, .769, .910, 1.0));
		WindowsTextField->setSelectionTextColor(Color4f(0.0, 0.0, 0.0, 1.0));
		WindowsTextField->setTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsTextField->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsTextField->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsTextField->setDisabledTextColor(WindowsDisabledTextColor);
        WindowsTextField->setVerticalAlignment(0.5);

		//background
		WindowsTextField->setBackground(WindowsTextFieldBackground);
		WindowsTextField->setRolloverBackground(WindowsTextFieldBackground);
		WindowsTextField->setFocusedBackground(WindowsTextFieldBackground);
		WindowsTextField->setDisabledBackground(WindowsDisabledTextFieldBackground);

		//Border
		WindowsTextField->setBorder(WindowsTextFieldBorder);
		WindowsTextField->setRolloverBorder(WindowsTextFieldBorder);
		WindowsTextField->setFocusedBorder(WindowsTextFieldBorder);
		WindowsTextField->setDisabledBorder(WindowsTextFieldBorder);

		WindowsTextField->setHorizontalAlignment(0.0);
		WindowsTextField->setVerticalAlignment(0.5);
	endEditCP(WindowsTextField);
    
    
	/********Password Field********/
	ColorUIBackgroundPtr WindowsPasswordFieldBackground = ColorUIBackground::create();
	beginEditCP(WindowsPasswordFieldBackground);
		WindowsPasswordFieldBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
	endEditCP(WindowsPasswordFieldBackground);

	ColorUIBackgroundPtr WindowsDisabledPasswordFieldBackground = ColorUIBackground::create();
	beginEditCP(WindowsDisabledPasswordFieldBackground);
		WindowsDisabledPasswordFieldBackground->setColor(Color4f(.8, .8, .8, 1.0));
	endEditCP(WindowsDisabledPasswordFieldBackground);

	LineBorderPtr WindowsPasswordFieldBorder = LineBorder::create();
	beginEditCP(WindowsPasswordFieldBorder);
		WindowsPasswordFieldBorder->setWidth(1);
		WindowsPasswordFieldBorder->setColor( Color4f(.498,.616,.725,1.0) );
	endEditCP(WindowsPasswordFieldBorder);


	beginEditCP(WindowsPasswordField);
		//size
		WindowsPasswordField->setMinSize(Vec2f(0, 0));
		WindowsPasswordField->setMaxSize(Vec2f(32767,32767));
		WindowsPasswordField->setPreferredSize(Vec2f(75,23));

		//font
		WindowsPasswordField->setFont(WindowsFont);
		
		WindowsPasswordField->setSelectionBoxColor(Color4f(.682, .769, .910, 1.0));
		WindowsPasswordField->setSelectionTextColor(Color4f(0.0, 0.0, 0.0, 1.0));
		WindowsPasswordField->setTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsPasswordField->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsPasswordField->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsPasswordField->setDisabledTextColor(WindowsDisabledTextColor);
        WindowsPasswordField->setVerticalAlignment(0.5);

		//background
		WindowsPasswordField->setBackground(WindowsPasswordFieldBackground);
		WindowsPasswordField->setRolloverBackground(WindowsPasswordFieldBackground);
		WindowsPasswordField->setFocusedBackground(WindowsPasswordFieldBackground);
		WindowsPasswordField->setDisabledBackground(WindowsDisabledPasswordFieldBackground);

		//Border
		WindowsPasswordField->setBorder(WindowsPasswordFieldBorder);
		WindowsPasswordField->setRolloverBorder(WindowsPasswordFieldBorder);
		WindowsPasswordField->setFocusedBorder(WindowsPasswordFieldBorder);
		WindowsPasswordField->setDisabledBorder(WindowsPasswordFieldBorder);

	endEditCP(WindowsPasswordField);

	/********Text Area********/
	ColorUIBackgroundPtr WindowsTextAreaBackground = ColorUIBackground::create();
	beginEditCP(WindowsTextAreaBackground);
		WindowsTextAreaBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
	endEditCP(WindowsTextAreaBackground);

	ColorUIBackgroundPtr WindowsDisabledTextAreaBackground = ColorUIBackground::create();
	beginEditCP(WindowsDisabledTextAreaBackground);
		WindowsDisabledTextAreaBackground->setColor(Color4f(.8, .8, .8, 1.0));
	endEditCP(WindowsDisabledTextAreaBackground);

	LineBorderPtr WindowsTextAreaBorder = LineBorder::create();
	beginEditCP(WindowsTextAreaBorder);
		WindowsTextAreaBorder->setWidth(1);
		WindowsTextAreaBorder->setColor( Color4f(.498,.616,.725,1.0) );
	endEditCP(WindowsTextAreaBorder);

	beginEditCP(WindowsTextArea);
		//size
		WindowsTextArea->setMinSize(Vec2f(0, 0));
		WindowsTextArea->setMaxSize(Vec2f(32767,32767));
		WindowsTextArea->setPreferredSize(Vec2f(100, 25));

		//font
		WindowsTextArea->setFont(WindowsFont);
		WindowsTextArea->setSelectionBoxColor(Color4f(.682, .769, .910, 1.0));
		WindowsTextArea->setSelectionTextColor(Color4f(0.0, 0.0, 0.0, 1.0));
		WindowsTextArea->setTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsTextArea->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsTextArea->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsTextArea->setDisabledTextColor(WindowsDisabledTextColor);
		

		//background
		WindowsTextArea->setBackground(WindowsTextAreaBackground);
		WindowsTextArea->setRolloverBackground(WindowsTextAreaBackground);
		WindowsTextArea->setFocusedBackground(WindowsTextAreaBackground);
		WindowsTextArea->setDisabledBackground(WindowsDisabledTextAreaBackground);

		//Border
		WindowsTextArea->setBorder(WindowsTextAreaBorder);
		WindowsTextArea->setRolloverBorder(WindowsTextAreaBorder);
		WindowsTextArea->setFocusedBorder(WindowsTextAreaBorder);
		WindowsTextArea->setDisabledBorder(WindowsTextAreaBorder);

	endEditCP(WindowsTextArea);

	//************************** ToolTip*****************************
	//Default ToolTipBorder
	LineBorderPtr WindowsToolTipLineBorder = LineBorder::create();
	beginEditCP(WindowsToolTipLineBorder);
		WindowsToolTipLineBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsToolTipLineBorder->setWidth(1);
	endEditCP(WindowsToolTipLineBorder);
    
    
	ShadowBorderPtr WindowsToolTipBorder = osg::ShadowBorder::create();
    beginEditCP(WindowsToolTipBorder, ShadowBorder::TopOffsetFieldMask | ShadowBorder::BottomOffsetFieldMask | ShadowBorder::LeftOffsetFieldMask | ShadowBorder::RightOffsetFieldMask | ShadowBorder::InternalColorFieldMask| ShadowBorder::EdgeColorFieldMask | ShadowBorder::InsideBorderFieldMask | ShadowBorder::CornerRadiusFieldMask | ShadowBorder::InternalToEdgeColorLengthFieldMask );
		WindowsToolTipBorder->setTopOffset(0);
		WindowsToolTipBorder->setBottomOffset(2);
		WindowsToolTipBorder->setLeftOffset(0);
		WindowsToolTipBorder->setRightOffset(2);
		WindowsToolTipBorder->setInsideBorder(WindowsToolTipLineBorder);
		WindowsToolTipBorder->setCornerRadius(3);
		WindowsToolTipBorder->setInternalColor(Color4f(0.0, 0.0, 0.0, 0.5));
		WindowsToolTipBorder->setEdgeColor(Color4f(0.0, 0.0, 0.0, 0.0));
		WindowsToolTipBorder->setInternalToEdgeColorLength(2);
	endEditCP(WindowsToolTipBorder, ShadowBorder::TopOffsetFieldMask | ShadowBorder::BottomOffsetFieldMask | ShadowBorder::LeftOffsetFieldMask | ShadowBorder::RightOffsetFieldMask | ShadowBorder::InternalColorFieldMask| ShadowBorder::EdgeColorFieldMask | ShadowBorder::InsideBorderFieldMask | ShadowBorder::CornerRadiusFieldMask | ShadowBorder::InternalToEdgeColorLengthFieldMask );

    
	//Default ToolTipBackground
	ColorUIBackgroundPtr WindowsToolTipBackground = ColorUIBackground::create();
	beginEditCP(WindowsToolTipBackground);
		WindowsToolTipBackground->setColor(Color4f(1.0,1.0,0.88,1.0));
	endEditCP(WindowsToolTipBackground);

	//Default ToolTip
	beginEditCP(WindowsToolTip);
		WindowsToolTip->setEnabled(true);
		WindowsToolTip->setVisible(true);
		
		WindowsToolTip->setConstraints(NullFC);
		//Sizes
		WindowsToolTip->setMinSize(Vec2f(0,0));
		WindowsToolTip->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsToolTip->setPreferredSize(Vec2f(75,23));

		//Border
		WindowsToolTip->setBorder(WindowsToolTipBorder);
		
		//Background
		WindowsToolTip->setBackground(WindowsToolTipBackground);
		
		//Opacity
		WindowsToolTip->setOpacity(1.0);

		//Text
		WindowsToolTip->setText("");
		WindowsToolTip->setFont(WindowsFont);
        WindowsToolTip->setVerticalAlignment(0.5);
        WindowsToolTip->setHorizontalAlignment(0.5);
		WindowsToolTip->setTextColor(Color4f(0.0,0.0,0.0,1.0));
	endEditCP(WindowsToolTip);

	//************************** MenuItem*****************************
	//Windows MenuItemBorder
	EmptyBorderPtr WindowsMenuItemBorder = EmptyBorder::create();

	//Windows MenuItemBackground
	ColorUIBackgroundPtr WindowsMenuItemBackground = ColorUIBackground::create();
	beginEditCP(WindowsMenuItemBackground);
		WindowsMenuItemBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
	endEditCP(WindowsMenuItemBackground);
	
	//Windows MenuItemBorder
	EmptyBorderPtr WindowsMenuItemSelectedBorder = EmptyBorder::create();

	//Windows MenuItemBackground
	ColorUIBackgroundPtr WindowsMenuItemSelectedBackground = ColorUIBackground::create();
	beginEditCP(WindowsMenuItemSelectedBackground);
		WindowsMenuItemSelectedBackground->setColor(Color4f(0.19,0.42,0.77,1.0));
	endEditCP(WindowsMenuItemSelectedBackground);

	//Windows MenuItem
	beginEditCP(WindowsMenuItem);
		WindowsMenuItem->setEnabled(true);
		WindowsMenuItem->setVisible(true);
		
		WindowsMenuItem->setConstraints(NullFC);
		//Sizes
		WindowsMenuItem->setMinSize(Vec2f(0,0));
		WindowsMenuItem->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsMenuItem->setPreferredSize(Vec2f(100,17));

		//Border
		WindowsMenuItem->setBorder(WindowsMenuItemBorder);
		
		//Background
		WindowsMenuItem->setBackground(WindowsMenuItemBackground);
		
		//Opacity
		WindowsMenuItem->setOpacity(1.0);

        //Accelerators
        WindowsMenuItem->setAcceleratorModifiers(0);
        WindowsMenuItem->setAcceleratorKey(KeyEvent::KEY_NONE);

        //Selected
        WindowsMenuItem->setSelected(false);
        WindowsMenuItem->setSelectedBorder(WindowsMenuItemSelectedBorder);
        WindowsMenuItem->setSelectedBackground(WindowsMenuItemSelectedBackground);
        
		//Text
		WindowsMenuItem->setText("");
		WindowsMenuItem->setFont(WindowsFont);
		WindowsMenuItem->setTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsMenuItem->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsMenuItem->setSelectedTextColor(Color4f(1.0,1.0,1.0,1.0));
		WindowsMenuItem->setRolloverTextColor(Color4f(1.0,1.0,1.0,1.0));
		WindowsMenuItem->setDisabledTextColor(Color4f(0.4,0.4,0.4,1.0));
		WindowsMenuItem->setVerticalAlignment(0.5);
		WindowsMenuItem->setHorizontalAlignment(0.0);
		WindowsMenuItem->setActiveOffset(Vec2f(0.0f,0.0f));
	endEditCP(WindowsMenuItem);
    
	//************************** ComponentMenuItem*****************************
	//Windows ComponentMenuItemBorder
	EmptyBorderPtr WindowsComponentMenuItemBorder = EmptyBorder::create();

	//Windows ComponentMenuItemBackground
	ColorUIBackgroundPtr WindowsComponentMenuItemBackground = ColorUIBackground::create();
	beginEditCP(WindowsComponentMenuItemBackground);
		WindowsComponentMenuItemBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
	endEditCP(WindowsComponentMenuItemBackground);
	
	//Windows ComponentMenuItemBorder
	EmptyBorderPtr WindowsComponentMenuItemSelectedBorder = EmptyBorder::create();

	//Windows ComponentMenuItemBackground
	ColorUIBackgroundPtr WindowsComponentMenuItemSelectedBackground = ColorUIBackground::create();
	beginEditCP(WindowsComponentMenuItemSelectedBackground);
		WindowsComponentMenuItemSelectedBackground->setColor(Color4f(0.19,0.42,0.77,1.0));
	endEditCP(WindowsComponentMenuItemSelectedBackground);

	//Windows ComponentMenuItem
	beginEditCP(WindowsComponentMenuItem);
		WindowsComponentMenuItem->setEnabled(true);
		WindowsComponentMenuItem->setVisible(true);
		
		WindowsComponentMenuItem->setConstraints(NullFC);
		//Sizes
		WindowsComponentMenuItem->setMinSize(Vec2f(0,0));
		WindowsComponentMenuItem->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsComponentMenuItem->setPreferredSize(Vec2f(100,17));

		//Border
		WindowsComponentMenuItem->setBorder(WindowsComponentMenuItemBorder);
		
		//Background
		WindowsComponentMenuItem->setBackground(WindowsComponentMenuItemBackground);
		
		//Opacity
		WindowsComponentMenuItem->setOpacity(1.0);

        //Accelerators
        WindowsComponentMenuItem->setAcceleratorModifiers(0);
        WindowsComponentMenuItem->setAcceleratorKey(KeyEvent::KEY_NONE);
        
        //Selected
        WindowsComponentMenuItem->setSelected(false);
        WindowsComponentMenuItem->setSelectedBorder(WindowsComponentMenuItemSelectedBorder);
        WindowsComponentMenuItem->setSelectedBackground(WindowsComponentMenuItemSelectedBackground);
        
		//Text
		WindowsComponentMenuItem->setText("");
		WindowsComponentMenuItem->setFont(WindowsFont);
		WindowsComponentMenuItem->setTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsComponentMenuItem->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsComponentMenuItem->setSelectedTextColor(Color4f(1.0,1.0,1.0,1.0));
		WindowsComponentMenuItem->setRolloverTextColor(Color4f(1.0,1.0,1.0,1.0));
		WindowsComponentMenuItem->setDisabledTextColor(Color4f(0.4,0.4,0.4,1.0));
		WindowsComponentMenuItem->setVerticalAlignment(0.5);
		WindowsComponentMenuItem->setHorizontalAlignment(0.0);
		WindowsComponentMenuItem->setActiveOffset(Vec2f(0.0f,0.0f));
	endEditCP(WindowsComponentMenuItem);
    
	//************************** Menu*****************************
	//Windows MenuBorder
	EmptyBorderPtr WindowsMenuBorder = EmptyBorder::create();

	//Windows MenuBackground
	ColorUIBackgroundPtr WindowsMenuBackground = ColorUIBackground::create();
	beginEditCP(WindowsMenuBackground);
		WindowsMenuBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
	endEditCP(WindowsMenuBackground);
	
	//Windows MenuBorder
	EmptyBorderPtr WindowsMenuSelectedBorder = EmptyBorder::create();

	//Windows MenuBackground
	ColorUIBackgroundPtr WindowsMenuSelectedBackground = ColorUIBackground::create();
	beginEditCP(WindowsMenuSelectedBackground);
		WindowsMenuSelectedBackground->setColor(Color4f(0.19,0.42,0.77,1.0));
	endEditCP(WindowsMenuSelectedBackground);

    
    //Expanding Draw Object
	PolygonUIDrawObjectPtr MenuExpandablePolygon = PolygonUIDrawObject::create();
	beginEditCP(MenuExpandablePolygon);
		MenuExpandablePolygon->setColor(Color4f(0.0,0.0,0.0,1.0));
		MenuExpandablePolygon->setOpacity(1.0);
        MenuExpandablePolygon->getVerticies().push_back(Pnt2f(0,0));
        MenuExpandablePolygon->getVerticies().push_back(Pnt2f(0,7));
        MenuExpandablePolygon->getVerticies().push_back(Pnt2f(4,4));
	endEditCP(MenuExpandablePolygon);

	UIDrawObjectCanvasPtr defaultMenuDrawObject = UIDrawObjectCanvas::create();
	beginEditCP(defaultMenuDrawObject);
	   defaultMenuDrawObject->getDrawObjects().push_back(MenuExpandablePolygon);
	endEditCP(defaultMenuDrawObject);

	//Windows Menu
	beginEditCP(WindowsMenu);
		WindowsMenu->setEnabled(true);
		WindowsMenu->setVisible(true);
		
		WindowsMenu->setConstraints(NullFC);
		//Sizes
		WindowsMenu->setMinSize(Vec2f(0,0));
		WindowsMenu->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsMenu->setPreferredSize(Vec2f(100,17));

		//Border
		WindowsMenu->setBorder(WindowsMenuBorder);
		
		//Background
		WindowsMenu->setBackground(WindowsMenuBackground);
		
		//Opacity
		WindowsMenu->setOpacity(1.0);

        //Accelerators
        WindowsMenu->setAcceleratorModifiers(0);
        WindowsMenu->setAcceleratorKey(KeyEvent::KEY_NONE);

        //Selected
        WindowsMenu->setSelected(false);
        WindowsMenu->setSelectedBorder(WindowsMenuSelectedBorder);
        WindowsMenu->setRolloverBorder(WindowsMenuSelectedBorder);
        WindowsMenu->setSelectedBackground(WindowsMenuSelectedBackground);
        WindowsMenu->setRolloverBackground(WindowsMenuSelectedBackground);
        
		//Text
		WindowsMenu->setText("");
		WindowsMenu->setFont(WindowsFont);
		WindowsMenu->setTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsMenu->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsMenu->setSelectedTextColor(Color4f(1.0,1.0,1.0,1.0));
		WindowsMenu->setRolloverTextColor(Color4f(1.0,1.0,1.0,1.0));
		WindowsMenu->setDisabledTextColor(Color4f(0.4,0.4,0.4,1.0));
		WindowsMenu->setActiveOffset(Vec2f(0.0f,0.0f));
		WindowsMenu->setVerticalAlignment(0.5);
		WindowsMenu->setHorizontalAlignment(0.0);

        //Expanding Draw Object
        WindowsMenu->setExpandDrawObject(defaultMenuDrawObject);
	endEditCP(WindowsMenu);
    
	//************************** PopupMenu*****************************
	//Windows PopupMenuBorder
	LineBorderPtr WindowsPopupMenuLineBorder = LineBorder::create();
	beginEditCP(WindowsPopupMenuLineBorder);
		WindowsPopupMenuLineBorder->setColor(Color4f(0.67,0.66,0.60,1.0));
		WindowsPopupMenuLineBorder->setWidth(1);
	endEditCP(WindowsPopupMenuLineBorder);

	ShadowBorderPtr WindowsPopupMenuBorder = osg::ShadowBorder::create();
    beginEditCP(WindowsPopupMenuBorder, ShadowBorder::TopOffsetFieldMask | ShadowBorder::BottomOffsetFieldMask | ShadowBorder::LeftOffsetFieldMask | ShadowBorder::RightOffsetFieldMask | ShadowBorder::InternalColorFieldMask| ShadowBorder::EdgeColorFieldMask | ShadowBorder::InsideBorderFieldMask | ShadowBorder::CornerRadiusFieldMask | ShadowBorder::InternalToEdgeColorLengthFieldMask );
		WindowsPopupMenuBorder->setTopOffset(0);
		WindowsPopupMenuBorder->setBottomOffset(4);
		WindowsPopupMenuBorder->setLeftOffset(0);
		WindowsPopupMenuBorder->setRightOffset(4);
		WindowsPopupMenuBorder->setInsideBorder(WindowsPopupMenuLineBorder);
		WindowsPopupMenuBorder->setCornerRadius(3);
		WindowsPopupMenuBorder->setInternalColor(Color4f(0.36, 0.36, 0.36, 0.5));
		WindowsPopupMenuBorder->setEdgeColor(Color4f(0.36, 0.36, 0.36, 0.0));
		WindowsPopupMenuBorder->setInternalToEdgeColorLength(3);
	endEditCP(WindowsPopupMenuBorder, ShadowBorder::TopOffsetFieldMask | ShadowBorder::BottomOffsetFieldMask | ShadowBorder::LeftOffsetFieldMask | ShadowBorder::RightOffsetFieldMask | ShadowBorder::InternalColorFieldMask| ShadowBorder::EdgeColorFieldMask | ShadowBorder::InsideBorderFieldMask | ShadowBorder::CornerRadiusFieldMask | ShadowBorder::InternalToEdgeColorLengthFieldMask );

	//Windows PopupMenuBackground
	ColorUIBackgroundPtr WindowsPopupMenuBackground = ColorUIBackground::create();
	beginEditCP(WindowsPopupMenuBackground);
		WindowsPopupMenuBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
	endEditCP(WindowsPopupMenuBackground);


    //Windows PopupMenu Default Separator
    SeparatorPtr WindowsPopupMenuDefaultSeparator = Separator::create();
    beginEditCP(WindowsPopupMenuDefaultSeparator, Separator::SeparatorSizeFieldMask | Separator::ColorFieldMask);
    WindowsPopupMenuDefaultSeparator->setSeparatorSize(1.0f);
    WindowsPopupMenuDefaultSeparator->setColor(Color4f(0.67,0.66,0.6,1.0));
    endEditCP(WindowsPopupMenuDefaultSeparator, Separator::SeparatorSizeFieldMask | Separator::ColorFieldMask);

	//Windows PopupMenu
	beginEditCP(WindowsPopupMenu);
		WindowsPopupMenu->setEnabled(true);
		WindowsPopupMenu->setVisible(false);
		
		WindowsPopupMenu->setConstraints(NullFC);
		//Sizes
		WindowsPopupMenu->setMinSize(Vec2f(0,0));
		WindowsPopupMenu->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsPopupMenu->setPreferredSize(Vec2f(100,50));

		//Border
		WindowsPopupMenu->setBorder(WindowsPopupMenuBorder);
        WindowsPopupMenu->setDisabledBorder(WindowsPopupMenuBorder);
        WindowsPopupMenu->setFocusedBorder(WindowsPopupMenuBorder);
        WindowsPopupMenu->setRolloverBorder(WindowsPopupMenuBorder);
        
		
		//Background
        WindowsPopupMenu->setBackground(WindowsPopupMenuBackground);
        WindowsPopupMenu->setDisabledBackground(WindowsPopupMenuBackground);
        WindowsPopupMenu->setFocusedBackground(WindowsPopupMenuBackground);
        WindowsPopupMenu->setRolloverBackground(WindowsPopupMenuBackground);
		
		//Opacity
		WindowsPopupMenu->setOpacity(1.0);

        //SubMenu delay in seconds
        WindowsPopupMenu->setSubMenuDelay(getSubMenuPopupTime());

        //Insets
        WindowsPopupMenu->setAllInsets(2);
        
        WindowsPopupMenu->setDefaultSeparator(WindowsPopupMenuDefaultSeparator);
        WindowsPopupMenu->setSelectionModel(DefaultSingleSelectionModel::create());
	endEditCP(WindowsPopupMenu);
    
	//************************** ListGeneratedPopupMenu*****************************
	//Windows ListGeneratedPopupMenuBorder
	LineBorderPtr WindowsListGeneratedPopupMenuLineBorder = LineBorder::create();
	beginEditCP(WindowsListGeneratedPopupMenuLineBorder);
		WindowsListGeneratedPopupMenuLineBorder->setColor(Color4f(0.67,0.66,0.60,1.0));
		WindowsListGeneratedPopupMenuLineBorder->setWidth(1);
	endEditCP(WindowsListGeneratedPopupMenuLineBorder);

	ShadowBorderPtr WindowsListGeneratedPopupMenuBorder = osg::ShadowBorder::create();
    beginEditCP(WindowsListGeneratedPopupMenuBorder, ShadowBorder::TopOffsetFieldMask | ShadowBorder::BottomOffsetFieldMask | ShadowBorder::LeftOffsetFieldMask | ShadowBorder::RightOffsetFieldMask | ShadowBorder::InternalColorFieldMask| ShadowBorder::EdgeColorFieldMask | ShadowBorder::InsideBorderFieldMask | ShadowBorder::CornerRadiusFieldMask | ShadowBorder::InternalToEdgeColorLengthFieldMask );
		WindowsListGeneratedPopupMenuBorder->setTopOffset(0);
		WindowsListGeneratedPopupMenuBorder->setBottomOffset(4);
		WindowsListGeneratedPopupMenuBorder->setLeftOffset(0);
		WindowsListGeneratedPopupMenuBorder->setRightOffset(4);
		WindowsListGeneratedPopupMenuBorder->setInsideBorder(WindowsListGeneratedPopupMenuLineBorder);
		WindowsListGeneratedPopupMenuBorder->setCornerRadius(3);
		WindowsListGeneratedPopupMenuBorder->setInternalColor(Color4f(0.36, 0.36, 0.36, 0.5));
		WindowsListGeneratedPopupMenuBorder->setEdgeColor(Color4f(0.36, 0.36, 0.36, 0.0));
		WindowsListGeneratedPopupMenuBorder->setInternalToEdgeColorLength(3);
	endEditCP(WindowsListGeneratedPopupMenuBorder, ShadowBorder::TopOffsetFieldMask | ShadowBorder::BottomOffsetFieldMask | ShadowBorder::LeftOffsetFieldMask | ShadowBorder::RightOffsetFieldMask | ShadowBorder::InternalColorFieldMask| ShadowBorder::EdgeColorFieldMask | ShadowBorder::InsideBorderFieldMask | ShadowBorder::CornerRadiusFieldMask | ShadowBorder::InternalToEdgeColorLengthFieldMask );

	//Windows ListGeneratedPopupMenuBackground
	ColorUIBackgroundPtr WindowsListGeneratedPopupMenuBackground = ColorUIBackground::create();
	beginEditCP(WindowsListGeneratedPopupMenuBackground);
		WindowsListGeneratedPopupMenuBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
	endEditCP(WindowsListGeneratedPopupMenuBackground);

	//Windows ListGeneratedPopupMenu
	beginEditCP(WindowsListGeneratedPopupMenu);
		WindowsListGeneratedPopupMenu->setEnabled(true);
		WindowsListGeneratedPopupMenu->setVisible(false);
		
		WindowsListGeneratedPopupMenu->setConstraints(NullFC);
		//Sizes
		WindowsListGeneratedPopupMenu->setMinSize(Vec2f(0,0));
		WindowsListGeneratedPopupMenu->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsListGeneratedPopupMenu->setPreferredSize(Vec2f(100,50));

		//Border
		WindowsListGeneratedPopupMenu->setBorder(WindowsListGeneratedPopupMenuBorder);
        WindowsListGeneratedPopupMenu->setDisabledBorder(WindowsListGeneratedPopupMenuBorder);
        WindowsListGeneratedPopupMenu->setFocusedBorder(WindowsListGeneratedPopupMenuBorder);
        WindowsListGeneratedPopupMenu->setRolloverBorder(WindowsListGeneratedPopupMenuBorder);
        
		
		//Background
        WindowsListGeneratedPopupMenu->setBackground(WindowsListGeneratedPopupMenuBackground);
        WindowsListGeneratedPopupMenu->setDisabledBackground(WindowsListGeneratedPopupMenuBackground);
        WindowsListGeneratedPopupMenu->setFocusedBackground(WindowsListGeneratedPopupMenuBackground);
        WindowsListGeneratedPopupMenu->setRolloverBackground(WindowsListGeneratedPopupMenuBackground);
		
		//Opacity
		WindowsListGeneratedPopupMenu->setOpacity(1.0);

        //SubMenu delay in seconds
        WindowsListGeneratedPopupMenu->setSubMenuDelay(getSubMenuPopupTime());

        //Insets
        WindowsListGeneratedPopupMenu->setAllInsets(2);
        WindowsListGeneratedPopupMenu->setSelectionModel(DefaultSingleSelectionModel::create());
	endEditCP(WindowsListGeneratedPopupMenu);
	//************************** MenuBar*****************************
	//Windows MenuBarBorder
	EmptyBorderPtr WindowsMenuBarBorder = EmptyBorder::create();

	//Windows MenuBarBackground
	ColorUIBackgroundPtr WindowsMenuBarBackground = ColorUIBackground::create();
	beginEditCP(WindowsMenuBarBackground);
		WindowsMenuBarBackground->setColor(Color4f(0.93,0.93,0.93,1.0));
	endEditCP(WindowsMenuBarBackground);

	//Windows MenuBar
	beginEditCP(WindowsMenuBar);
		WindowsMenuBar->setEnabled(true);
		WindowsMenuBar->setVisible(true);
		
		WindowsMenuBar->setConstraints(NullFC);
		//Sizes
		WindowsMenuBar->setMinSize(Vec2f(0,0));
		WindowsMenuBar->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsMenuBar->setPreferredSize(Vec2f(100,50));

		//Border
		WindowsMenuBar->setBorder(WindowsMenuBarBorder);
        WindowsMenuBar->setDisabledBorder(WindowsMenuBarBorder);
        WindowsMenuBar->setFocusedBorder(WindowsMenuBarBorder);
        WindowsMenuBar->setRolloverBorder(WindowsMenuBarBorder);
        
		
		//Background
        WindowsMenuBar->setBackground(WindowsMenuBarBackground);
        WindowsMenuBar->setDisabledBackground(WindowsMenuBarBackground);
        WindowsMenuBar->setFocusedBackground(WindowsMenuBarBackground);
        WindowsMenuBar->setRolloverBackground(WindowsMenuBarBackground);
		
		//Opacity
		WindowsMenuBar->setOpacity(1.0);

        //SubMenu delay in seconds
        WindowsMenuBar->setMenuDelay(getSubMenuPopupTime());
        WindowsMenuBar->setSelectionModel(DefaultSingleSelectionModel::create());
	endEditCP(WindowsMenuBar);
    
	//************************** ScrollBar*****************************
	//Windows ScrollBarBorder
	EmptyBorderPtr WindowsScrollBarBorder = EmptyBorder::create();

	//Windows ScrollBarBackground
	EmptyUIBackgroundPtr WindowsScrollBarBackground = EmptyUIBackground::create();

	RoundedCornerLineBorderPtr WindowsWhiteCorneredBorder = RoundedCornerLineBorder::create();
	beginEditCP(WindowsWhiteCorneredBorder);
		WindowsWhiteCorneredBorder->setWidth(1);
		WindowsWhiteCorneredBorder->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
		WindowsWhiteCorneredBorder->setCornerRadius(2);
	endEditCP(WindowsWhiteCorneredBorder);

	RoundedCornerLineBorderPtr WindowsBlueCorneredBorder = RoundedCornerLineBorder::create();
	beginEditCP(WindowsBlueCorneredBorder);
		WindowsBlueCorneredBorder->setWidth(1);
		WindowsBlueCorneredBorder->setColor(Color4f(0.49, 0.62, 0.83, 1.0));
		WindowsBlueCorneredBorder->setCornerRadius(2);
	endEditCP(WindowsBlueCorneredBorder);

	RoundedCornerLineBorderPtr WindowsLightBlueCorneredBorder = RoundedCornerLineBorder::create();
	beginEditCP(WindowsLightBlueCorneredBorder);
		WindowsLightBlueCorneredBorder->setWidth(1);
		WindowsLightBlueCorneredBorder->setColor(Color4f(0.73, 0.80, 0.96, 1.0));
		WindowsLightBlueCorneredBorder->setCornerRadius(2);
	endEditCP(WindowsLightBlueCorneredBorder);

	RoundedCornerLineBorderPtr WindowsDisabledCorneredBorder = RoundedCornerLineBorder::create();
	beginEditCP(WindowsDisabledCorneredBorder);
		WindowsDisabledCorneredBorder->setWidth(1);
		WindowsDisabledCorneredBorder->setColor(Color4f(0.93,0.93,0.90,1.0));
		WindowsDisabledCorneredBorder->setCornerRadius(2);
	endEditCP(WindowsDisabledCorneredBorder);

    //Vertical Min Draw Object
	PolygonUIDrawObjectPtr WindowsScrollBarVerticalMinButtonDrawObject1 = PolygonUIDrawObject::create();
	beginEditCP(WindowsScrollBarVerticalMinButtonDrawObject1);
		WindowsScrollBarVerticalMinButtonDrawObject1->setColor(Color4f(0.3,0.38,0.52,1.0));
		WindowsScrollBarVerticalMinButtonDrawObject1->setOpacity(1.0);
        WindowsScrollBarVerticalMinButtonDrawObject1->getVerticies().push_back(Pnt2f(0,4));
        WindowsScrollBarVerticalMinButtonDrawObject1->getVerticies().push_back(Pnt2f(4,0));
        WindowsScrollBarVerticalMinButtonDrawObject1->getVerticies().push_back(Pnt2f(4,2));
        WindowsScrollBarVerticalMinButtonDrawObject1->getVerticies().push_back(Pnt2f(1,5));
	endEditCP(WindowsScrollBarVerticalMinButtonDrawObject1);
	PolygonUIDrawObjectPtr WindowsScrollBarVerticalMinButtonDrawObject2 = PolygonUIDrawObject::create();
	beginEditCP(WindowsScrollBarVerticalMinButtonDrawObject2);
		WindowsScrollBarVerticalMinButtonDrawObject2->setColor(Color4f(0.3,0.38,0.52,1.0));
		WindowsScrollBarVerticalMinButtonDrawObject2->setOpacity(1.0);
        WindowsScrollBarVerticalMinButtonDrawObject2->getVerticies().push_back(Pnt2f(4,0));
        WindowsScrollBarVerticalMinButtonDrawObject2->getVerticies().push_back(Pnt2f(8,4));
        WindowsScrollBarVerticalMinButtonDrawObject2->getVerticies().push_back(Pnt2f(7,5));
        WindowsScrollBarVerticalMinButtonDrawObject2->getVerticies().push_back(Pnt2f(4,2));
	endEditCP(WindowsScrollBarVerticalMinButtonDrawObject2);

	UIDrawObjectCanvasPtr WindowsScrollBarVerticalMinButtonCanvas = UIDrawObjectCanvas::create();
	beginEditCP(WindowsScrollBarVerticalMinButtonCanvas);
	   WindowsScrollBarVerticalMinButtonCanvas->getDrawObjects().push_back(WindowsScrollBarVerticalMinButtonDrawObject1);
	   WindowsScrollBarVerticalMinButtonCanvas->getDrawObjects().push_back(WindowsScrollBarVerticalMinButtonDrawObject2);
	endEditCP(WindowsScrollBarVerticalMinButtonCanvas);

    //Vertical Min Button
	CompoundBorderPtr WindowsScrollBarButtonOuterBorder = CompoundBorder::create();
	beginEditCP(WindowsScrollBarButtonOuterBorder);
		WindowsScrollBarButtonOuterBorder->setInnerBorder(WindowsWhiteCorneredBorder);
		WindowsScrollBarButtonOuterBorder->setOuterBorder(WindowsBlueCorneredBorder);
	endEditCP(WindowsScrollBarButtonOuterBorder);
    
	CompoundBorderPtr WindowsScrollBarButtonBorder = CompoundBorder::create();
	beginEditCP(WindowsScrollBarButtonBorder);
		WindowsScrollBarButtonBorder->setInnerBorder(WindowsLightBlueCorneredBorder);
		WindowsScrollBarButtonBorder->setOuterBorder(WindowsScrollBarButtonOuterBorder);
	endEditCP(WindowsScrollBarButtonBorder);

	CompoundBorderPtr WindowsScrollBarButtonDisabledOuterBorder = CompoundBorder::create();
	beginEditCP(WindowsScrollBarButtonDisabledOuterBorder);
		WindowsScrollBarButtonDisabledOuterBorder->setInnerBorder(WindowsWhiteCorneredBorder);
		WindowsScrollBarButtonDisabledOuterBorder->setOuterBorder(WindowsDisabledCorneredBorder);
	endEditCP(WindowsScrollBarButtonDisabledOuterBorder);
    
	CompoundBorderPtr WindowsScrollBarDisabledButtonBorder = CompoundBorder::create();
	beginEditCP(WindowsScrollBarDisabledButtonBorder);
		WindowsScrollBarDisabledButtonBorder->setInnerBorder(WindowsDisabledCorneredBorder);
		WindowsScrollBarDisabledButtonBorder->setOuterBorder(WindowsScrollBarButtonDisabledOuterBorder);
	endEditCP(WindowsScrollBarDisabledButtonBorder);

    ColorUIBackgroundPtr WindowsScrollBarButtonBackground = ColorUIBackground::create();
	beginEditCP(WindowsScrollBarButtonBackground);
		WindowsScrollBarButtonBackground->setColor(Color4f(0.76,0.84,0.99,1.0));
	endEditCP(WindowsScrollBarButtonBackground);

    ColorUIBackgroundPtr WindowsScrollBarRolloverButtonBackground = ColorUIBackground::create();
	beginEditCP(WindowsScrollBarRolloverButtonBackground);
		WindowsScrollBarRolloverButtonBackground->setColor(Color4f(0.82,0.92,1.0,1.0));
	endEditCP(WindowsScrollBarRolloverButtonBackground);
    
    ColorUIBackgroundPtr WindowsScrollBarDisabledButtonBackground = ColorUIBackground::create();
	beginEditCP(WindowsScrollBarDisabledButtonBackground);
		WindowsScrollBarDisabledButtonBackground->setColor(Color4f(0.93,0.93,0.90,1.0));
	endEditCP(WindowsScrollBarDisabledButtonBackground);
    
    ColorUIBackgroundPtr WindowsScrollBarActiveButtonBackground = ColorUIBackground::create();
	beginEditCP(WindowsScrollBarActiveButtonBackground);
		WindowsScrollBarActiveButtonBackground->setColor(Color4f(0.55,0.63,0.94,1.0));
	endEditCP(WindowsScrollBarActiveButtonBackground);

	ButtonPtr WindowsScrollBarVerticalMinButton = Button::create();
    beginEditCP(WindowsScrollBarVerticalMinButton);
        WindowsScrollBarVerticalMinButton->setPreferredSize(Vec2f(17,17));
        WindowsScrollBarVerticalMinButton->setEnableActionOnMouseDownTime(true);
        WindowsScrollBarVerticalMinButton->setActionOnMouseDownRate(0.1);

        WindowsScrollBarVerticalMinButton->setDrawObject(WindowsScrollBarVerticalMinButtonCanvas);
        WindowsScrollBarVerticalMinButton->setActiveDrawObject(WindowsScrollBarVerticalMinButtonCanvas);
        WindowsScrollBarVerticalMinButton->setFocusedDrawObject(WindowsScrollBarVerticalMinButtonCanvas);
        WindowsScrollBarVerticalMinButton->setRolloverDrawObject(WindowsScrollBarVerticalMinButtonCanvas);
        WindowsScrollBarVerticalMinButton->setDisabledDrawObject(WindowsScrollBarVerticalMinButtonCanvas);

        WindowsScrollBarVerticalMinButton->setBorder(WindowsScrollBarButtonBorder);
        WindowsScrollBarVerticalMinButton->setActiveBorder(WindowsScrollBarButtonBorder);
        WindowsScrollBarVerticalMinButton->setDisabledBorder(WindowsScrollBarDisabledButtonBorder);
        WindowsScrollBarVerticalMinButton->setFocusedBorder(WindowsScrollBarButtonBorder);
        WindowsScrollBarVerticalMinButton->setRolloverBorder(WindowsScrollBarButtonBorder);
        
        WindowsScrollBarVerticalMinButton->setBackground(WindowsScrollBarButtonBackground);
        WindowsScrollBarVerticalMinButton->setActiveBackground(WindowsScrollBarActiveButtonBackground);
        WindowsScrollBarVerticalMinButton->setDisabledBackground(WindowsScrollBarDisabledButtonBackground);
        WindowsScrollBarVerticalMinButton->setFocusedBackground(WindowsScrollBarButtonBackground);
        WindowsScrollBarVerticalMinButton->setRolloverBackground(WindowsScrollBarRolloverButtonBackground);

        WindowsScrollBarVerticalMinButton->setActiveOffset(Vec2f(0,0));
    endEditCP(WindowsScrollBarVerticalMinButton);

    //Vertical Max Draw Object
	PolygonUIDrawObjectPtr WindowsScrollBarVerticalMaxButtonDrawObject1 = PolygonUIDrawObject::create();
	beginEditCP(WindowsScrollBarVerticalMaxButtonDrawObject1);
		WindowsScrollBarVerticalMaxButtonDrawObject1->setColor(Color4f(0.3,0.38,0.52,1.0));
		WindowsScrollBarVerticalMaxButtonDrawObject1->setOpacity(1.0);
        WindowsScrollBarVerticalMaxButtonDrawObject1->getVerticies().push_back(Pnt2f(1,0));
        WindowsScrollBarVerticalMaxButtonDrawObject1->getVerticies().push_back(Pnt2f(4,3));
        WindowsScrollBarVerticalMaxButtonDrawObject1->getVerticies().push_back(Pnt2f(4,5));
        WindowsScrollBarVerticalMaxButtonDrawObject1->getVerticies().push_back(Pnt2f(0,1));
	endEditCP(WindowsScrollBarVerticalMaxButtonDrawObject1);
	PolygonUIDrawObjectPtr WindowsScrollBarVerticalMaxButtonDrawObject2 = PolygonUIDrawObject::create();
	beginEditCP(WindowsScrollBarVerticalMaxButtonDrawObject2);
		WindowsScrollBarVerticalMaxButtonDrawObject2->setColor(Color4f(0.3,0.38,0.52,1.0));
		WindowsScrollBarVerticalMaxButtonDrawObject2->setOpacity(1.0);
        WindowsScrollBarVerticalMaxButtonDrawObject2->getVerticies().push_back(Pnt2f(4,3));
        WindowsScrollBarVerticalMaxButtonDrawObject2->getVerticies().push_back(Pnt2f(7,0));
        WindowsScrollBarVerticalMaxButtonDrawObject2->getVerticies().push_back(Pnt2f(8,1));
        WindowsScrollBarVerticalMaxButtonDrawObject2->getVerticies().push_back(Pnt2f(4,5));
	endEditCP(WindowsScrollBarVerticalMaxButtonDrawObject2);

	UIDrawObjectCanvasPtr WindowsScrollBarVerticalMaxButtonCanvas = UIDrawObjectCanvas::create();
	beginEditCP(WindowsScrollBarVerticalMaxButtonCanvas);
	   WindowsScrollBarVerticalMaxButtonCanvas->getDrawObjects().push_back(WindowsScrollBarVerticalMaxButtonDrawObject1);
	   WindowsScrollBarVerticalMaxButtonCanvas->getDrawObjects().push_back(WindowsScrollBarVerticalMaxButtonDrawObject2);
	endEditCP(WindowsScrollBarVerticalMaxButtonCanvas);
    //Vertical Max Button
	ButtonPtr WindowsScrollBarVerticalMaxButton = Button::create();
    beginEditCP(WindowsScrollBarVerticalMaxButton);
        WindowsScrollBarVerticalMaxButton->setPreferredSize(Vec2f(17,17));
        WindowsScrollBarVerticalMaxButton->setEnableActionOnMouseDownTime(true);
        WindowsScrollBarVerticalMaxButton->setActionOnMouseDownRate(0.1);
        
        WindowsScrollBarVerticalMaxButton->setDrawObject(WindowsScrollBarVerticalMaxButtonCanvas);
        WindowsScrollBarVerticalMaxButton->setActiveDrawObject(WindowsScrollBarVerticalMaxButtonCanvas);
        WindowsScrollBarVerticalMaxButton->setFocusedDrawObject(WindowsScrollBarVerticalMaxButtonCanvas);
        WindowsScrollBarVerticalMaxButton->setRolloverDrawObject(WindowsScrollBarVerticalMaxButtonCanvas);
        WindowsScrollBarVerticalMaxButton->setDisabledDrawObject(WindowsScrollBarVerticalMaxButtonCanvas);
        
        WindowsScrollBarVerticalMaxButton->setBorder(WindowsScrollBarButtonBorder);
        WindowsScrollBarVerticalMaxButton->setActiveBorder(WindowsScrollBarButtonBorder);
        WindowsScrollBarVerticalMaxButton->setDisabledBorder(WindowsScrollBarDisabledButtonBorder);
        WindowsScrollBarVerticalMaxButton->setFocusedBorder(WindowsScrollBarButtonBorder);
        WindowsScrollBarVerticalMaxButton->setRolloverBorder(WindowsScrollBarButtonBorder);
        
        WindowsScrollBarVerticalMaxButton->setBackground(WindowsScrollBarButtonBackground);
        WindowsScrollBarVerticalMaxButton->setActiveBackground(WindowsScrollBarActiveButtonBackground);
        WindowsScrollBarVerticalMaxButton->setDisabledBackground(WindowsScrollBarDisabledButtonBackground);
        WindowsScrollBarVerticalMaxButton->setFocusedBackground(WindowsScrollBarButtonBackground);
        WindowsScrollBarVerticalMaxButton->setRolloverBackground(WindowsScrollBarRolloverButtonBackground);

        WindowsScrollBarVerticalMaxButton->setActiveOffset(Vec2f(0,0));
    endEditCP(WindowsScrollBarVerticalMaxButton);

    //Horizontal Min Draw Object
	PolygonUIDrawObjectPtr WindowsScrollBarHorizontalMinButtonDrawObject1 = PolygonUIDrawObject::create();
	beginEditCP(WindowsScrollBarHorizontalMinButtonDrawObject1);
		WindowsScrollBarHorizontalMinButtonDrawObject1->setColor(Color4f(0.3,0.38,0.52,1.0));
		WindowsScrollBarHorizontalMinButtonDrawObject1->setOpacity(1.0);
        WindowsScrollBarHorizontalMinButtonDrawObject1->getVerticies().push_back(Pnt2f(0,4));
        WindowsScrollBarHorizontalMinButtonDrawObject1->getVerticies().push_back(Pnt2f(4,0));
        WindowsScrollBarHorizontalMinButtonDrawObject1->getVerticies().push_back(Pnt2f(5,1));
        WindowsScrollBarHorizontalMinButtonDrawObject1->getVerticies().push_back(Pnt2f(2,4));
	endEditCP(WindowsScrollBarHorizontalMinButtonDrawObject1);
	PolygonUIDrawObjectPtr WindowsScrollBarHorizontalMinButtonDrawObject2 = PolygonUIDrawObject::create();
	beginEditCP(WindowsScrollBarHorizontalMinButtonDrawObject2);
		WindowsScrollBarHorizontalMinButtonDrawObject2->setColor(Color4f(0.3,0.38,0.52,1.0));
		WindowsScrollBarHorizontalMinButtonDrawObject2->setOpacity(1.0);
        WindowsScrollBarHorizontalMinButtonDrawObject2->getVerticies().push_back(Pnt2f(0,4));
        WindowsScrollBarHorizontalMinButtonDrawObject2->getVerticies().push_back(Pnt2f(2,4));
        WindowsScrollBarHorizontalMinButtonDrawObject2->getVerticies().push_back(Pnt2f(5,7));
        WindowsScrollBarHorizontalMinButtonDrawObject2->getVerticies().push_back(Pnt2f(4,8));
	endEditCP(WindowsScrollBarHorizontalMinButtonDrawObject2);
    
	UIDrawObjectCanvasPtr WindowsScrollBarHorizontalMinButtonCanvas = UIDrawObjectCanvas::create();
	beginEditCP(WindowsScrollBarHorizontalMinButtonCanvas);
	   WindowsScrollBarHorizontalMinButtonCanvas->getDrawObjects().push_back(WindowsScrollBarHorizontalMinButtonDrawObject1);
	   WindowsScrollBarHorizontalMinButtonCanvas->getDrawObjects().push_back(WindowsScrollBarHorizontalMinButtonDrawObject2);
	endEditCP(WindowsScrollBarHorizontalMinButtonCanvas);

    //Horizontal Min Button
	ButtonPtr WindowsScrollBarHorizontalMinButton = Button::create();
    beginEditCP(WindowsScrollBarHorizontalMinButton);
        WindowsScrollBarHorizontalMinButton->setPreferredSize(Vec2f(17,17));
        WindowsScrollBarHorizontalMinButton->setEnableActionOnMouseDownTime(true);
        WindowsScrollBarHorizontalMinButton->setActionOnMouseDownRate(0.1);

        WindowsScrollBarHorizontalMinButton->setDrawObject(WindowsScrollBarHorizontalMinButtonCanvas);
        WindowsScrollBarHorizontalMinButton->setActiveDrawObject(WindowsScrollBarHorizontalMinButtonCanvas);
        WindowsScrollBarHorizontalMinButton->setFocusedDrawObject(WindowsScrollBarHorizontalMinButtonCanvas);
        WindowsScrollBarHorizontalMinButton->setRolloverDrawObject(WindowsScrollBarHorizontalMinButtonCanvas);
        WindowsScrollBarHorizontalMinButton->setDisabledDrawObject(WindowsScrollBarHorizontalMinButtonCanvas);
        
        WindowsScrollBarHorizontalMinButton->setBorder(WindowsScrollBarButtonBorder);
        WindowsScrollBarHorizontalMinButton->setActiveBorder(WindowsScrollBarButtonBorder);
        WindowsScrollBarHorizontalMinButton->setDisabledBorder(WindowsScrollBarButtonBorder);
        WindowsScrollBarHorizontalMinButton->setFocusedBorder(WindowsScrollBarButtonBorder);
        WindowsScrollBarHorizontalMinButton->setRolloverBorder(WindowsScrollBarButtonBorder);
        
        WindowsScrollBarHorizontalMinButton->setBackground(WindowsScrollBarButtonBackground);
        WindowsScrollBarHorizontalMinButton->setActiveBackground(WindowsScrollBarActiveButtonBackground);
        WindowsScrollBarHorizontalMinButton->setDisabledBackground(WindowsScrollBarDisabledButtonBackground);
        WindowsScrollBarHorizontalMinButton->setFocusedBackground(WindowsScrollBarButtonBackground);
        WindowsScrollBarHorizontalMinButton->setRolloverBackground(WindowsScrollBarRolloverButtonBackground);

        WindowsScrollBarHorizontalMinButton->setActiveOffset(Vec2f(0,0));
    endEditCP(WindowsScrollBarHorizontalMinButton);

    //Horizontal Max Draw Object
	PolygonUIDrawObjectPtr WindowsScrollBarHorizontalMaxButtonDrawObject1 = PolygonUIDrawObject::create();
	beginEditCP(WindowsScrollBarHorizontalMaxButtonDrawObject1);
		WindowsScrollBarHorizontalMaxButtonDrawObject1->setColor(Color4f(0.3,0.38,0.52,1.0));
		WindowsScrollBarHorizontalMaxButtonDrawObject1->setOpacity(1.0);
        WindowsScrollBarHorizontalMaxButtonDrawObject1->getVerticies().push_back(Pnt2f(0,1));
        WindowsScrollBarHorizontalMaxButtonDrawObject1->getVerticies().push_back(Pnt2f(1,0));
        WindowsScrollBarHorizontalMaxButtonDrawObject1->getVerticies().push_back(Pnt2f(5,4));
        WindowsScrollBarHorizontalMaxButtonDrawObject1->getVerticies().push_back(Pnt2f(3,4));
	endEditCP(WindowsScrollBarHorizontalMaxButtonDrawObject1);
	PolygonUIDrawObjectPtr WindowsScrollBarHorizontalMaxButtonDrawObject2 = PolygonUIDrawObject::create();
	beginEditCP(WindowsScrollBarHorizontalMaxButtonDrawObject2);
		WindowsScrollBarHorizontalMaxButtonDrawObject2->setColor(Color4f(0.3,0.38,0.52,1.0));
		WindowsScrollBarHorizontalMaxButtonDrawObject2->setOpacity(1.0);
        WindowsScrollBarHorizontalMaxButtonDrawObject2->getVerticies().push_back(Pnt2f(3,4));
        WindowsScrollBarHorizontalMaxButtonDrawObject2->getVerticies().push_back(Pnt2f(5,4));
        WindowsScrollBarHorizontalMaxButtonDrawObject2->getVerticies().push_back(Pnt2f(1,8));
        WindowsScrollBarHorizontalMaxButtonDrawObject2->getVerticies().push_back(Pnt2f(0,7));
	endEditCP(WindowsScrollBarHorizontalMaxButtonDrawObject2);
    
	UIDrawObjectCanvasPtr WindowsScrollBarHorizontalMaxButtonCanvas = UIDrawObjectCanvas::create();
	beginEditCP(WindowsScrollBarHorizontalMaxButtonCanvas);
	   WindowsScrollBarHorizontalMaxButtonCanvas->getDrawObjects().push_back(WindowsScrollBarHorizontalMaxButtonDrawObject1);
	   WindowsScrollBarHorizontalMaxButtonCanvas->getDrawObjects().push_back(WindowsScrollBarHorizontalMaxButtonDrawObject2);
	endEditCP(WindowsScrollBarHorizontalMaxButtonCanvas);
    //Horizontal Max Button
	ButtonPtr WindowsScrollBarHorizontalMaxButton = Button::create();
    beginEditCP(WindowsScrollBarHorizontalMaxButton);
        WindowsScrollBarHorizontalMaxButton->setPreferredSize(Vec2f(17,17));
        WindowsScrollBarHorizontalMaxButton->setEnableActionOnMouseDownTime(true);
        WindowsScrollBarHorizontalMaxButton->setActionOnMouseDownRate(0.1);
        
        WindowsScrollBarHorizontalMaxButton->setDrawObject(WindowsScrollBarHorizontalMaxButtonCanvas);
        WindowsScrollBarHorizontalMaxButton->setActiveDrawObject(WindowsScrollBarHorizontalMaxButtonCanvas);
        WindowsScrollBarHorizontalMaxButton->setFocusedDrawObject(WindowsScrollBarHorizontalMaxButtonCanvas);
        WindowsScrollBarHorizontalMaxButton->setRolloverDrawObject(WindowsScrollBarHorizontalMaxButtonCanvas);
        WindowsScrollBarHorizontalMaxButton->setDisabledDrawObject(WindowsScrollBarHorizontalMaxButtonCanvas);

        WindowsScrollBarHorizontalMaxButton->setBorder(WindowsScrollBarButtonBorder);
        WindowsScrollBarHorizontalMaxButton->setActiveBorder(WindowsScrollBarButtonBorder);
        WindowsScrollBarHorizontalMaxButton->setDisabledBorder(WindowsScrollBarButtonBorder);
        WindowsScrollBarHorizontalMaxButton->setFocusedBorder(WindowsScrollBarButtonBorder);
        WindowsScrollBarHorizontalMaxButton->setRolloverBorder(WindowsScrollBarButtonBorder);
        
        WindowsScrollBarHorizontalMaxButton->setBackground(WindowsScrollBarButtonBackground);
        WindowsScrollBarHorizontalMaxButton->setActiveBackground(WindowsScrollBarActiveButtonBackground);
        WindowsScrollBarHorizontalMaxButton->setDisabledBackground(WindowsScrollBarDisabledButtonBackground);
        WindowsScrollBarHorizontalMaxButton->setFocusedBackground(WindowsScrollBarButtonBackground);
        WindowsScrollBarHorizontalMaxButton->setRolloverBackground(WindowsScrollBarRolloverButtonBackground);

        WindowsScrollBarHorizontalMaxButton->setActiveOffset(Vec2f(0,0));
    endEditCP(WindowsScrollBarHorizontalMaxButton);

    //Vertical Scroll Field
	//Vertical Scroll Field Border
	MatteBorderPtr WindowsVerticalScrollFieldBorder = MatteBorder::create();
	beginEditCP(WindowsVerticalScrollFieldBorder);
		WindowsVerticalScrollFieldBorder->setLeftWidth(1);
		WindowsVerticalScrollFieldBorder->setRightWidth(1);
		WindowsVerticalScrollFieldBorder->setTopWidth(0);
		WindowsVerticalScrollFieldBorder->setBottomWidth(0);
		WindowsVerticalScrollFieldBorder->setColor(Color4f(0.93, 0.93, 0.9, 1.0));
	endEditCP(WindowsVerticalScrollFieldBorder);

	//Vertical Scroll Field Disabled Border
	BevelBorderPtr WindowsVerticalDisabledScrollFieldBorder = BevelBorder::create();
	beginEditCP(WindowsVerticalDisabledScrollFieldBorder);
		WindowsVerticalDisabledScrollFieldBorder->setRaised(true);
		WindowsVerticalDisabledScrollFieldBorder->setWidth(1);
		WindowsVerticalDisabledScrollFieldBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
		WindowsVerticalDisabledScrollFieldBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
		WindowsVerticalDisabledScrollFieldBorder->setShadowInner(Color4f(0.85, 0.85, 0.85, 1.0));
		WindowsVerticalDisabledScrollFieldBorder->setShadowOuter(Color4f(0.65, 0.65, 0.65, 1.0));
	endEditCP(WindowsVerticalDisabledScrollFieldBorder);

	//Vertical Scroll Field Background
	GradientUIBackgroundPtr WindowsVerticalScrollFieldBackground = GradientUIBackground::create();
	beginEditCP(WindowsVerticalScrollFieldBackground);
		WindowsVerticalScrollFieldBackground->setColorStart(Color4f(0.95,0.95,0.93,1.0));
		WindowsVerticalScrollFieldBackground->setColorEnd(Color4f(1.0,1.0,0.98,1.0));
		WindowsVerticalScrollFieldBackground->setOrientation(GradientUIBackground::HORIZONTAL_ORIENTATION);
	endEditCP(WindowsVerticalScrollFieldBackground);
	
	//Vertical Scroll Field Disabled Background
	ColorUIBackgroundPtr WindowsVerticalDisabledScrollFieldBackground = ColorUIBackground::create();
	beginEditCP(WindowsVerticalDisabledScrollFieldBackground);
		WindowsVerticalDisabledScrollFieldBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
	endEditCP(WindowsVerticalDisabledScrollFieldBackground);

	ButtonPtr WindowsVerticalScrollFieldButton = Button::create();
    beginEditCP(WindowsVerticalScrollFieldButton, Button::PreferredSizeFieldMask | Button::EnableActionOnMouseDownTimeFieldMask | Button::ActionOnMouseDownRateFieldMask);
        WindowsVerticalScrollFieldButton->setPreferredSize(Vec2f(17,17));
        WindowsVerticalScrollFieldButton->setEnableActionOnMouseDownTime(true);
        WindowsVerticalScrollFieldButton->setActionOnMouseDownRate(0.2);
        
		WindowsVerticalScrollFieldButton->setBorder(WindowsVerticalScrollFieldBorder);
		WindowsVerticalScrollFieldButton->setActiveBorder(WindowsVerticalScrollFieldBorder);
		WindowsVerticalScrollFieldButton->setRolloverBorder(WindowsVerticalScrollFieldBorder);
		WindowsVerticalScrollFieldButton->setFocusedBorder(WindowsVerticalScrollFieldBorder);
		WindowsVerticalScrollFieldButton->setDisabledBorder(WindowsVerticalDisabledScrollFieldBorder);
        
		WindowsVerticalScrollFieldButton->setBackground(WindowsVerticalScrollFieldBackground);
		WindowsVerticalScrollFieldButton->setActiveBackground(WindowsVerticalScrollFieldBackground);
		WindowsVerticalScrollFieldButton->setRolloverBackground(WindowsVerticalScrollFieldBackground);
		WindowsVerticalScrollFieldButton->setFocusedBackground(WindowsVerticalScrollFieldBackground);
		WindowsVerticalScrollFieldButton->setDisabledBackground(WindowsVerticalDisabledScrollFieldBackground);
    endEditCP(WindowsVerticalScrollFieldButton, Button::PreferredSizeFieldMask | Button::EnableActionOnMouseDownTimeFieldMask | Button::ActionOnMouseDownRateFieldMask);

    //Vertical Scroll Bar
	//Vertical Scroll Bar Border

	CompoundBorderPtr WindowsVerticalScrollBarDrawObjectOuterBorder = CompoundBorder::create();
	beginEditCP(WindowsVerticalScrollBarDrawObjectOuterBorder);
		WindowsVerticalScrollBarDrawObjectOuterBorder->setInnerBorder(WindowsWhiteCorneredBorder);
		WindowsVerticalScrollBarDrawObjectOuterBorder->setOuterBorder(WindowsBlueCorneredBorder);
	endEditCP(WindowsVerticalScrollBarDrawObjectOuterBorder);
    
	CompoundBorderPtr WindowsVerticalScrollBarDrawObjectBorder = CompoundBorder::create();
	beginEditCP(WindowsVerticalScrollBarDrawObjectBorder);
		WindowsVerticalScrollBarDrawObjectBorder->setInnerBorder(WindowsLightBlueCorneredBorder);
		WindowsVerticalScrollBarDrawObjectBorder->setOuterBorder(WindowsVerticalScrollBarDrawObjectOuterBorder);
	endEditCP(WindowsVerticalScrollBarDrawObjectBorder);

	//Vertical Scroll Bar Disabled Border
	BevelBorderPtr WindowsDisabledVerticalScrollBarDrawObjectBorder = BevelBorder::create();
	beginEditCP(WindowsDisabledVerticalScrollBarDrawObjectBorder);
		WindowsDisabledVerticalScrollBarDrawObjectBorder->setRaised(true);
		WindowsDisabledVerticalScrollBarDrawObjectBorder->setWidth(2);
		WindowsDisabledVerticalScrollBarDrawObjectBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
		WindowsDisabledVerticalScrollBarDrawObjectBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
		WindowsDisabledVerticalScrollBarDrawObjectBorder->setShadowInner(Color4f(0.85, 0.85, 0.85, 1.0));
		WindowsDisabledVerticalScrollBarDrawObjectBorder->setShadowOuter(Color4f(0.65, 0.65, 0.65, 1.0));
	endEditCP(WindowsDisabledVerticalScrollBarDrawObjectBorder);

	//Vertical Scroll Bar Background
	GradientUIBackgroundPtr WindowsVerticalScrollBarDrawObjectBackground = GradientUIBackground::create();
	beginEditCP(WindowsVerticalScrollBarDrawObjectBackground);
		WindowsVerticalScrollBarDrawObjectBackground->setColorStart(Color4f(0.79,0.85,0.99,1.0));
		WindowsVerticalScrollBarDrawObjectBackground->setColorEnd(Color4f(0.73,0.8,0.98,1.0));
		WindowsVerticalScrollBarDrawObjectBackground->setOrientation(GradientUIBackground::HORIZONTAL_ORIENTATION);
	endEditCP(WindowsVerticalScrollBarDrawObjectBackground);
	
	//Vertical Scroll Bar Disabled Background
	ColorUIBackgroundPtr WindowsDisabledVerticalScrollBarDrawObjectBackground = ColorUIBackground::create();
	beginEditCP(WindowsDisabledVerticalScrollBarDrawObjectBackground);
		WindowsDisabledVerticalScrollBarDrawObjectBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
	endEditCP(WindowsDisabledVerticalScrollBarDrawObjectBackground);

	//Vertical Scroll Bar Rollover Background
	GradientUIBackgroundPtr WindowsRolloverVerticalScrollBarDrawObjectBackground = GradientUIBackground::create();
	beginEditCP(WindowsRolloverVerticalScrollBarDrawObjectBackground);
		WindowsRolloverVerticalScrollBarDrawObjectBackground->setColorStart(Color4f(0.84,0.91,1.0,1.0));
		WindowsRolloverVerticalScrollBarDrawObjectBackground->setColorEnd(Color4f(0.80,0.88,1.0,1.0));
		WindowsRolloverVerticalScrollBarDrawObjectBackground->setOrientation(GradientUIBackground::HORIZONTAL_ORIENTATION);
	endEditCP(WindowsRolloverVerticalScrollBarDrawObjectBackground);

	//Vertical Scroll Bar Active Background
	GradientUIBackgroundPtr WindowsActiveVerticalScrollBarDrawObjectBackground = GradientUIBackground::create();
	beginEditCP(WindowsActiveVerticalScrollBarDrawObjectBackground);
		WindowsActiveVerticalScrollBarDrawObjectBackground->setColorStart(Color4f(0.84,0.91,1.0,1.0));
		WindowsActiveVerticalScrollBarDrawObjectBackground->setColorEnd(Color4f(0.80,0.88,1.0,1.0));
		WindowsActiveVerticalScrollBarDrawObjectBackground->setOrientation(GradientUIBackground::VERTICAL_ORIENTATION);
	endEditCP(WindowsActiveVerticalScrollBarDrawObjectBackground);

    //Vertical Scroll Bar Center Ridges
    RectUIDrawObjectPtr VerticalWhiteRidge1 = RectUIDrawObject::create();
	beginEditCP(VerticalWhiteRidge1);
       VerticalWhiteRidge1->setTopLeft(Pnt2f(0,0));
       VerticalWhiteRidge1->setBottomRight(Pnt2f(6,1));
       VerticalWhiteRidge1->setColor(Color4f(0.93,0.96,1.0,1.0));
	endEditCP(VerticalWhiteRidge1);

    RectUIDrawObjectPtr VerticalWhiteRidge2 = RectUIDrawObject::create();
	beginEditCP(VerticalWhiteRidge2);
       VerticalWhiteRidge2->setTopLeft(Pnt2f(0,2));
       VerticalWhiteRidge2->setBottomRight(Pnt2f(6,3));
       VerticalWhiteRidge2->setColor(Color4f(0.93,0.96,1.0,1.0));
	endEditCP(VerticalWhiteRidge2);
    
    RectUIDrawObjectPtr VerticalWhiteRidge3 = RectUIDrawObject::create();
	beginEditCP(VerticalWhiteRidge3);
       VerticalWhiteRidge3->setTopLeft(Pnt2f(0,4));
       VerticalWhiteRidge3->setBottomRight(Pnt2f(6,5));
       VerticalWhiteRidge3->setColor(Color4f(0.93,0.96,1.0,1.0));
	endEditCP(VerticalWhiteRidge3);

    RectUIDrawObjectPtr VerticalWhiteRidge4 = RectUIDrawObject::create();
	beginEditCP(VerticalWhiteRidge4);
       VerticalWhiteRidge4->setTopLeft(Pnt2f(0,6));
       VerticalWhiteRidge4->setBottomRight(Pnt2f(6,7));
       VerticalWhiteRidge4->setColor(Color4f(0.93,0.96,1.0,1.0));
	endEditCP(VerticalWhiteRidge4);
    
    RectUIDrawObjectPtr VerticalBlueRidge1 = RectUIDrawObject::create();
	beginEditCP(VerticalBlueRidge1);
       VerticalBlueRidge1->setTopLeft(Pnt2f(1,1));
       VerticalBlueRidge1->setBottomRight(Pnt2f(7,2));
       VerticalBlueRidge1->setColor(Color4f(0.55,0.69,0.97,1.0));
	endEditCP(VerticalBlueRidge1);

    RectUIDrawObjectPtr VerticalBlueRidge2 = RectUIDrawObject::create();
	beginEditCP(VerticalBlueRidge2);
       VerticalBlueRidge2->setTopLeft(Pnt2f(1,3));
       VerticalBlueRidge2->setBottomRight(Pnt2f(7,4));
       VerticalBlueRidge2->setColor(Color4f(0.55,0.69,0.97,1.0));
	endEditCP(VerticalBlueRidge2);
    
    RectUIDrawObjectPtr VerticalBlueRidge3 = RectUIDrawObject::create();
	beginEditCP(VerticalBlueRidge3);
       VerticalBlueRidge3->setTopLeft(Pnt2f(1,5));
       VerticalBlueRidge3->setBottomRight(Pnt2f(7,6));
       VerticalBlueRidge3->setColor(Color4f(0.55,0.69,0.97,1.0));
	endEditCP(VerticalBlueRidge3);

    RectUIDrawObjectPtr VerticalBlueRidge4 = RectUIDrawObject::create();
	beginEditCP(VerticalBlueRidge4);
       VerticalBlueRidge4->setTopLeft(Pnt2f(1,7));
       VerticalBlueRidge4->setBottomRight(Pnt2f(7,8));
       VerticalBlueRidge4->setColor(Color4f(0.55,0.69,0.97,1.0));
	endEditCP(VerticalBlueRidge4);

    UIDrawObjectCanvasPtr WindowsVerticalScrollBarRidges = UIDrawObjectCanvas::create();
	beginEditCP(WindowsVerticalScrollBarRidges);
        WindowsVerticalScrollBarRidges->getDrawObjects().push_back(VerticalWhiteRidge1);
        WindowsVerticalScrollBarRidges->getDrawObjects().push_back(VerticalBlueRidge1);
        WindowsVerticalScrollBarRidges->getDrawObjects().push_back(VerticalWhiteRidge2);
        WindowsVerticalScrollBarRidges->getDrawObjects().push_back(VerticalBlueRidge2);
        WindowsVerticalScrollBarRidges->getDrawObjects().push_back(VerticalWhiteRidge3);
        WindowsVerticalScrollBarRidges->getDrawObjects().push_back(VerticalBlueRidge3);
        WindowsVerticalScrollBarRidges->getDrawObjects().push_back(VerticalWhiteRidge4);
        WindowsVerticalScrollBarRidges->getDrawObjects().push_back(VerticalBlueRidge4);
	endEditCP(WindowsVerticalScrollBarRidges);
    
    //Vertical Active Scroll Bar Center Ridges
    RectUIDrawObjectPtr VerticalActiveWhiteRidge1 = RectUIDrawObject::create();
	beginEditCP(VerticalActiveWhiteRidge1);
       VerticalActiveWhiteRidge1->setTopLeft(Pnt2f(0,0));
       VerticalActiveWhiteRidge1->setBottomRight(Pnt2f(6,1));
       VerticalActiveWhiteRidge1->setColor(Color4f(0.81,0.87,0.99,1.0));
	endEditCP(VerticalActiveWhiteRidge1);

    RectUIDrawObjectPtr VerticalActiveWhiteRidge2 = RectUIDrawObject::create();
	beginEditCP(VerticalActiveWhiteRidge2);
       VerticalActiveWhiteRidge2->setTopLeft(Pnt2f(0,2));
       VerticalActiveWhiteRidge2->setBottomRight(Pnt2f(6,3));
       VerticalActiveWhiteRidge2->setColor(Color4f(0.81,0.87,0.99,1.0));
	endEditCP(VerticalActiveWhiteRidge2);
    
    RectUIDrawObjectPtr VerticalActiveWhiteRidge3 = RectUIDrawObject::create();
	beginEditCP(VerticalActiveWhiteRidge3);
       VerticalActiveWhiteRidge3->setTopLeft(Pnt2f(0,4));
       VerticalActiveWhiteRidge3->setBottomRight(Pnt2f(6,5));
       VerticalActiveWhiteRidge3->setColor(Color4f(0.81,0.87,0.99,1.0));
	endEditCP(VerticalActiveWhiteRidge3);

    RectUIDrawObjectPtr VerticalActiveWhiteRidge4 = RectUIDrawObject::create();
	beginEditCP(VerticalActiveWhiteRidge4);
       VerticalActiveWhiteRidge4->setTopLeft(Pnt2f(0,6));
       VerticalActiveWhiteRidge4->setBottomRight(Pnt2f(6,7));
       VerticalActiveWhiteRidge4->setColor(Color4f(0.81,0.87,0.99,1.0));
	endEditCP(VerticalActiveWhiteRidge4);
    
    RectUIDrawObjectPtr VerticalActiveBlueRidge1 = RectUIDrawObject::create();
	beginEditCP(VerticalActiveBlueRidge1);
       VerticalActiveBlueRidge1->setTopLeft(Pnt2f(1,1));
       VerticalActiveBlueRidge1->setBottomRight(Pnt2f(7,2));
       VerticalActiveBlueRidge1->setColor(Color4f(0.51,0.62,0.85,1.0));
	endEditCP(VerticalActiveBlueRidge1);

    RectUIDrawObjectPtr VerticalActiveBlueRidge2 = RectUIDrawObject::create();
	beginEditCP(VerticalActiveBlueRidge2);
       VerticalActiveBlueRidge2->setTopLeft(Pnt2f(1,3));
       VerticalActiveBlueRidge2->setBottomRight(Pnt2f(7,4));
       VerticalActiveBlueRidge2->setColor(Color4f(0.51,0.62,0.85,1.0));
	endEditCP(VerticalActiveBlueRidge2);
    
    RectUIDrawObjectPtr VerticalActiveBlueRidge3 = RectUIDrawObject::create();
	beginEditCP(VerticalActiveBlueRidge3);
       VerticalActiveBlueRidge3->setTopLeft(Pnt2f(1,5));
       VerticalActiveBlueRidge3->setBottomRight(Pnt2f(7,6));
       VerticalActiveBlueRidge3->setColor(Color4f(0.51,0.62,0.85,1.0));
	endEditCP(VerticalActiveBlueRidge3);

    RectUIDrawObjectPtr VerticalActiveBlueRidge4 = RectUIDrawObject::create();
	beginEditCP(VerticalActiveBlueRidge4);
       VerticalActiveBlueRidge4->setTopLeft(Pnt2f(1,7));
       VerticalActiveBlueRidge4->setBottomRight(Pnt2f(7,8));
       VerticalActiveBlueRidge4->setColor(Color4f(0.51,0.62,0.85,1.0));
	endEditCP(VerticalActiveBlueRidge4);

    UIDrawObjectCanvasPtr WindowsVerticalActiveScrollBarRidges = UIDrawObjectCanvas::create();
	beginEditCP(WindowsVerticalActiveScrollBarRidges);
        WindowsVerticalActiveScrollBarRidges->getDrawObjects().push_back(VerticalActiveWhiteRidge1);
        WindowsVerticalActiveScrollBarRidges->getDrawObjects().push_back(VerticalActiveBlueRidge1);
        WindowsVerticalActiveScrollBarRidges->getDrawObjects().push_back(VerticalActiveWhiteRidge2);
        WindowsVerticalActiveScrollBarRidges->getDrawObjects().push_back(VerticalActiveBlueRidge2);
        WindowsVerticalActiveScrollBarRidges->getDrawObjects().push_back(VerticalActiveWhiteRidge3);
        WindowsVerticalActiveScrollBarRidges->getDrawObjects().push_back(VerticalActiveBlueRidge3);
        WindowsVerticalActiveScrollBarRidges->getDrawObjects().push_back(VerticalActiveWhiteRidge4);
        WindowsVerticalActiveScrollBarRidges->getDrawObjects().push_back(VerticalActiveBlueRidge4);
	endEditCP(WindowsVerticalActiveScrollBarRidges);
    
    //Vertical Rollover Scroll Bar Center Ridges
    RectUIDrawObjectPtr VerticalRolloverWhiteRidge1 = RectUIDrawObject::create();
	beginEditCP(VerticalRolloverWhiteRidge1);
       VerticalRolloverWhiteRidge1->setTopLeft(Pnt2f(0,0));
       VerticalRolloverWhiteRidge1->setBottomRight(Pnt2f(6,1));
       VerticalRolloverWhiteRidge1->setColor(Color4f(0.99,0.99,1.0,1.0));
	endEditCP(VerticalRolloverWhiteRidge1);

    RectUIDrawObjectPtr VerticalRolloverWhiteRidge2 = RectUIDrawObject::create();
	beginEditCP(VerticalRolloverWhiteRidge2);
       VerticalRolloverWhiteRidge2->setTopLeft(Pnt2f(0,2));
       VerticalRolloverWhiteRidge2->setBottomRight(Pnt2f(6,3));
       VerticalRolloverWhiteRidge2->setColor(Color4f(0.99,0.99,1.0,1.0));
	endEditCP(VerticalRolloverWhiteRidge2);
    
    RectUIDrawObjectPtr VerticalRolloverWhiteRidge3 = RectUIDrawObject::create();
	beginEditCP(VerticalRolloverWhiteRidge3);
       VerticalRolloverWhiteRidge3->setTopLeft(Pnt2f(0,4));
       VerticalRolloverWhiteRidge3->setBottomRight(Pnt2f(6,5));
       VerticalRolloverWhiteRidge3->setColor(Color4f(0.99,0.99,1.0,1.0));
	endEditCP(VerticalRolloverWhiteRidge3);

    RectUIDrawObjectPtr VerticalRolloverWhiteRidge4 = RectUIDrawObject::create();
	beginEditCP(VerticalRolloverWhiteRidge4);
       VerticalRolloverWhiteRidge4->setTopLeft(Pnt2f(0,6));
       VerticalRolloverWhiteRidge4->setBottomRight(Pnt2f(6,7));
       VerticalRolloverWhiteRidge4->setColor(Color4f(0.99,0.99,1.0,1.0));
	endEditCP(VerticalRolloverWhiteRidge4);
    
    RectUIDrawObjectPtr VerticalRolloverBlueRidge1 = RectUIDrawObject::create();
	beginEditCP(VerticalRolloverBlueRidge1);
       VerticalRolloverBlueRidge1->setTopLeft(Pnt2f(1,1));
       VerticalRolloverBlueRidge1->setBottomRight(Pnt2f(7,2));
       VerticalRolloverBlueRidge1->setColor(Color4f(0.61,0.77,1.0,1.0));
	endEditCP(VerticalRolloverBlueRidge1);

    RectUIDrawObjectPtr VerticalRolloverBlueRidge2 = RectUIDrawObject::create();
	beginEditCP(VerticalRolloverBlueRidge2);
       VerticalRolloverBlueRidge2->setTopLeft(Pnt2f(1,3));
       VerticalRolloverBlueRidge2->setBottomRight(Pnt2f(7,4));
       VerticalRolloverBlueRidge2->setColor(Color4f(0.61,0.77,1.0,1.0));
	endEditCP(VerticalRolloverBlueRidge2);
    
    RectUIDrawObjectPtr VerticalRolloverBlueRidge3 = RectUIDrawObject::create();
	beginEditCP(VerticalRolloverBlueRidge3);
       VerticalRolloverBlueRidge3->setTopLeft(Pnt2f(1,5));
       VerticalRolloverBlueRidge3->setBottomRight(Pnt2f(7,6));
       VerticalRolloverBlueRidge3->setColor(Color4f(0.61,0.77,1.0,1.0));
	endEditCP(VerticalRolloverBlueRidge3);

    RectUIDrawObjectPtr VerticalRolloverBlueRidge4 = RectUIDrawObject::create();
	beginEditCP(VerticalRolloverBlueRidge4);
       VerticalRolloverBlueRidge4->setTopLeft(Pnt2f(1,7));
       VerticalRolloverBlueRidge4->setBottomRight(Pnt2f(7,8));
       VerticalRolloverBlueRidge4->setColor(Color4f(0.61,0.77,1.0,1.0));
	endEditCP(VerticalRolloverBlueRidge4);

    UIDrawObjectCanvasPtr WindowsVerticalRolloverScrollBarRidges = UIDrawObjectCanvas::create();
	beginEditCP(WindowsVerticalRolloverScrollBarRidges);
        WindowsVerticalRolloverScrollBarRidges->getDrawObjects().push_back(VerticalRolloverWhiteRidge1);
        WindowsVerticalRolloverScrollBarRidges->getDrawObjects().push_back(VerticalRolloverBlueRidge1);
        WindowsVerticalRolloverScrollBarRidges->getDrawObjects().push_back(VerticalRolloverWhiteRidge2);
        WindowsVerticalRolloverScrollBarRidges->getDrawObjects().push_back(VerticalRolloverBlueRidge2);
        WindowsVerticalRolloverScrollBarRidges->getDrawObjects().push_back(VerticalRolloverWhiteRidge3);
        WindowsVerticalRolloverScrollBarRidges->getDrawObjects().push_back(VerticalRolloverBlueRidge3);
        WindowsVerticalRolloverScrollBarRidges->getDrawObjects().push_back(VerticalRolloverWhiteRidge4);
        WindowsVerticalRolloverScrollBarRidges->getDrawObjects().push_back(VerticalRolloverBlueRidge4);
	endEditCP(WindowsVerticalRolloverScrollBarRidges);

	ButtonPtr WindowsVerticalScrollBarDrawObject = Button::create();
	beginEditCP(WindowsVerticalScrollBarDrawObject);
		WindowsVerticalScrollBarDrawObject->setBorder(WindowsVerticalScrollBarDrawObjectBorder);
		WindowsVerticalScrollBarDrawObject->setRolloverBorder(WindowsVerticalScrollBarDrawObjectBorder);
		WindowsVerticalScrollBarDrawObject->setFocusedBorder(WindowsVerticalScrollBarDrawObjectBorder);
		WindowsVerticalScrollBarDrawObject->setDisabledBorder(WindowsDisabledVerticalScrollBarDrawObjectBorder);
		WindowsVerticalScrollBarDrawObject->setActiveBorder(WindowsVerticalScrollBarDrawObjectBorder);
        
		WindowsVerticalScrollBarDrawObject->setBackground(WindowsVerticalScrollBarDrawObjectBackground);
		WindowsVerticalScrollBarDrawObject->setRolloverBackground(WindowsRolloverVerticalScrollBarDrawObjectBackground);
		WindowsVerticalScrollBarDrawObject->setFocusedBackground(WindowsVerticalScrollBarDrawObjectBackground);
		WindowsVerticalScrollBarDrawObject->setDisabledBackground(WindowsDisabledVerticalScrollBarDrawObjectBackground);
		WindowsVerticalScrollBarDrawObject->setActiveBackground(WindowsActiveVerticalScrollBarDrawObjectBackground);

        WindowsVerticalScrollBarDrawObject->setVerticalAlignment(0.5);
        WindowsVerticalScrollBarDrawObject->setHorizontalAlignment(0.5);
        WindowsVerticalScrollBarDrawObject->setActiveOffset(Vec2f(0,0));

        WindowsVerticalScrollBarDrawObject->setDrawObject(WindowsVerticalScrollBarRidges);
        WindowsVerticalScrollBarDrawObject->setActiveDrawObject(WindowsVerticalActiveScrollBarRidges);
        WindowsVerticalScrollBarDrawObject->setFocusedDrawObject(WindowsVerticalScrollBarRidges);
        WindowsVerticalScrollBarDrawObject->setRolloverDrawObject(WindowsVerticalRolloverScrollBarRidges);
        WindowsVerticalScrollBarDrawObject->setDisabledDrawObject(WindowsVerticalScrollBarRidges);
	endEditCP(WindowsVerticalScrollBarDrawObject);

    //Horizontal Scroll Field
	//Horizontal Scroll Field Border
	MatteBorderPtr WindowsHorizontalScrollFieldBorder = MatteBorder::create();
	beginEditCP(WindowsHorizontalScrollFieldBorder);
		WindowsHorizontalScrollFieldBorder->setLeftWidth(0);
		WindowsHorizontalScrollFieldBorder->setRightWidth(0);
		WindowsHorizontalScrollFieldBorder->setTopWidth(1);
		WindowsHorizontalScrollFieldBorder->setBottomWidth(1);
		WindowsHorizontalScrollFieldBorder->setColor(Color4f(0.93, 0.93, 0.9, 1.0));
	endEditCP(WindowsHorizontalScrollFieldBorder);

	//Horizontal Scroll Field Disabled Border
	BevelBorderPtr WindowsHorizontalDisabledScrollFieldBorder = BevelBorder::create();
	beginEditCP(WindowsHorizontalDisabledScrollFieldBorder);
		WindowsHorizontalDisabledScrollFieldBorder->setRaised(true);
		WindowsHorizontalDisabledScrollFieldBorder->setWidth(1);
		WindowsHorizontalDisabledScrollFieldBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
		WindowsHorizontalDisabledScrollFieldBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
		WindowsHorizontalDisabledScrollFieldBorder->setShadowInner(Color4f(0.85, 0.85, 0.85, 1.0));
		WindowsHorizontalDisabledScrollFieldBorder->setShadowOuter(Color4f(0.65, 0.65, 0.65, 1.0));
	endEditCP(WindowsHorizontalDisabledScrollFieldBorder);

	//Horizontal Scroll Field Background
	GradientUIBackgroundPtr WindowsHorizontalScrollFieldBackground = GradientUIBackground::create();
	beginEditCP(WindowsHorizontalScrollFieldBackground);
		WindowsHorizontalScrollFieldBackground->setColorStart(Color4f(0.95,0.95,0.93,1.0));
		WindowsHorizontalScrollFieldBackground->setColorEnd(Color4f(1.0,1.0,0.98,1.0));
		WindowsHorizontalScrollFieldBackground->setOrientation(GradientUIBackground::VERTICAL_ORIENTATION);
	endEditCP(WindowsHorizontalScrollFieldBackground);
	
	//Horizontal Scroll Field Disabled Background
	ColorUIBackgroundPtr WindowsHorizontalDisabledScrollFieldBackground = ColorUIBackground::create();
	beginEditCP(WindowsHorizontalDisabledScrollFieldBackground);
		WindowsHorizontalDisabledScrollFieldBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
	endEditCP(WindowsHorizontalDisabledScrollFieldBackground);

	ButtonPtr WindowsHorizontalScrollFieldButton = Button::create();
    beginEditCP(WindowsHorizontalScrollFieldButton, Button::PreferredSizeFieldMask | Button::EnableActionOnMouseDownTimeFieldMask | Button::ActionOnMouseDownRateFieldMask);
        WindowsHorizontalScrollFieldButton->setPreferredSize(Vec2f(17,17));
        WindowsHorizontalScrollFieldButton->setEnableActionOnMouseDownTime(true);
        WindowsHorizontalScrollFieldButton->setActionOnMouseDownRate(0.2);
        
		WindowsHorizontalScrollFieldButton->setBorder(WindowsHorizontalScrollFieldBorder);
		WindowsHorizontalScrollFieldButton->setActiveBorder(WindowsHorizontalScrollFieldBorder);
		WindowsHorizontalScrollFieldButton->setRolloverBorder(WindowsHorizontalScrollFieldBorder);
		WindowsHorizontalScrollFieldButton->setFocusedBorder(WindowsHorizontalScrollFieldBorder);
		WindowsHorizontalScrollFieldButton->setDisabledBorder(WindowsHorizontalDisabledScrollFieldBorder);
        
		WindowsHorizontalScrollFieldButton->setBackground(WindowsHorizontalScrollFieldBackground);
		WindowsHorizontalScrollFieldButton->setActiveBackground(WindowsHorizontalScrollFieldBackground);
		WindowsHorizontalScrollFieldButton->setRolloverBackground(WindowsHorizontalScrollFieldBackground);
		WindowsHorizontalScrollFieldButton->setFocusedBackground(WindowsHorizontalScrollFieldBackground);
		WindowsHorizontalScrollFieldButton->setDisabledBackground(WindowsHorizontalDisabledScrollFieldBackground);
    endEditCP(WindowsHorizontalScrollFieldButton, Button::PreferredSizeFieldMask | Button::EnableActionOnMouseDownTimeFieldMask | Button::ActionOnMouseDownRateFieldMask);

    //Horizontal Scroll Bar
	//Horizontal Scroll Bar Border
	CompoundBorderPtr WindowsHorizontalScrollBarDrawObjectBorder = CompoundBorder::create();
	beginEditCP(WindowsHorizontalScrollBarDrawObjectBorder);
		WindowsHorizontalScrollBarDrawObjectBorder->setInnerBorder(WindowsWhiteCorneredBorder);
		WindowsHorizontalScrollBarDrawObjectBorder->setOuterBorder(WindowsBlueCorneredBorder);
	endEditCP(WindowsHorizontalScrollBarDrawObjectBorder);

	//Horizontal Scroll Bar Disabled Border
	BevelBorderPtr WindowsDisabledHorizontalScrollBarDrawObjectBorder = BevelBorder::create();
	beginEditCP(WindowsDisabledHorizontalScrollBarDrawObjectBorder);
		WindowsDisabledHorizontalScrollBarDrawObjectBorder->setRaised(true);
		WindowsDisabledHorizontalScrollBarDrawObjectBorder->setWidth(2);
		WindowsDisabledHorizontalScrollBarDrawObjectBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
		WindowsDisabledHorizontalScrollBarDrawObjectBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
		WindowsDisabledHorizontalScrollBarDrawObjectBorder->setShadowInner(Color4f(0.85, 0.85, 0.85, 1.0));
		WindowsDisabledHorizontalScrollBarDrawObjectBorder->setShadowOuter(Color4f(0.65, 0.65, 0.65, 1.0));
	endEditCP(WindowsDisabledHorizontalScrollBarDrawObjectBorder);

	//Horizontal Scroll Bar Background
	GradientUIBackgroundPtr WindowsHorizontalScrollBarDrawObjectBackground = GradientUIBackground::create();
	beginEditCP(WindowsHorizontalScrollBarDrawObjectBackground);
		WindowsHorizontalScrollBarDrawObjectBackground->setColorStart(Color4f(0.79,0.85,0.99,1.0));
		WindowsHorizontalScrollBarDrawObjectBackground->setColorEnd(Color4f(0.73,0.8,0.98,1.0));
		WindowsHorizontalScrollBarDrawObjectBackground->setOrientation(GradientUIBackground::VERTICAL_ORIENTATION);
	endEditCP(WindowsHorizontalScrollBarDrawObjectBackground);
	
	//Horizontal Scroll Bar Disabled Background
	ColorUIBackgroundPtr WindowsDisabledHorizontalScrollBarDrawObjectBackground = ColorUIBackground::create();
	beginEditCP(WindowsDisabledHorizontalScrollBarDrawObjectBackground);
		WindowsDisabledHorizontalScrollBarDrawObjectBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
	endEditCP(WindowsDisabledHorizontalScrollBarDrawObjectBackground);

	//Horizontal Scroll Bar Rollover Background
	GradientUIBackgroundPtr WindowsRolloverHorizontalScrollBarDrawObjectBackground = GradientUIBackground::create();
	beginEditCP(WindowsRolloverHorizontalScrollBarDrawObjectBackground);
		WindowsRolloverHorizontalScrollBarDrawObjectBackground->setColorStart(Color4f(0.84,0.91,1.0,1.0));
		WindowsRolloverHorizontalScrollBarDrawObjectBackground->setColorEnd(Color4f(0.80,0.88,1.0,1.0));
		WindowsRolloverHorizontalScrollBarDrawObjectBackground->setOrientation(GradientUIBackground::VERTICAL_ORIENTATION);
	endEditCP(WindowsRolloverHorizontalScrollBarDrawObjectBackground);

	//Horizontal Scroll Bar Active Background
	GradientUIBackgroundPtr WindowsActiveHorizontalScrollBarDrawObjectBackground = GradientUIBackground::create();
	beginEditCP(WindowsActiveHorizontalScrollBarDrawObjectBackground);
		WindowsActiveHorizontalScrollBarDrawObjectBackground->setColorStart(Color4f(0.84,0.91,1.0,1.0));
		WindowsActiveHorizontalScrollBarDrawObjectBackground->setColorEnd(Color4f(0.80,0.88,1.0,1.0));
		WindowsActiveHorizontalScrollBarDrawObjectBackground->setOrientation(GradientUIBackground::VERTICAL_ORIENTATION);
	endEditCP(WindowsActiveHorizontalScrollBarDrawObjectBackground);

    //Horizontal Scroll Bar Center Ridges
    RectUIDrawObjectPtr HorizontalWhiteRidge1 = RectUIDrawObject::create();
	beginEditCP(HorizontalWhiteRidge1);
       HorizontalWhiteRidge1->setTopLeft(Pnt2f(0,0));
       HorizontalWhiteRidge1->setBottomRight(Pnt2f(1,6));
       HorizontalWhiteRidge1->setColor(Color4f(0.93,0.96,1.0,1.0));
	endEditCP(HorizontalWhiteRidge1);

    RectUIDrawObjectPtr HorizontalWhiteRidge2 = RectUIDrawObject::create();
	beginEditCP(HorizontalWhiteRidge2);
       HorizontalWhiteRidge2->setTopLeft(Pnt2f(2,0));
       HorizontalWhiteRidge2->setBottomRight(Pnt2f(3,6));
       HorizontalWhiteRidge2->setColor(Color4f(0.93,0.96,1.0,1.0));
	endEditCP(HorizontalWhiteRidge2);
    
    RectUIDrawObjectPtr HorizontalWhiteRidge3 = RectUIDrawObject::create();
	beginEditCP(HorizontalWhiteRidge3);
       HorizontalWhiteRidge3->setTopLeft(Pnt2f(4,0));
       HorizontalWhiteRidge3->setBottomRight(Pnt2f(5,6));
       HorizontalWhiteRidge3->setColor(Color4f(0.93,0.96,1.0,1.0));
	endEditCP(HorizontalWhiteRidge3);

    RectUIDrawObjectPtr HorizontalWhiteRidge4 = RectUIDrawObject::create();
	beginEditCP(HorizontalWhiteRidge4);
       HorizontalWhiteRidge4->setTopLeft(Pnt2f(6,0));
       HorizontalWhiteRidge4->setBottomRight(Pnt2f(7,6));
       HorizontalWhiteRidge4->setColor(Color4f(0.93,0.96,1.0,1.0));
	endEditCP(HorizontalWhiteRidge4);
    
    RectUIDrawObjectPtr HorizontalBlueRidge1 = RectUIDrawObject::create();
	beginEditCP(HorizontalBlueRidge1);
       HorizontalBlueRidge1->setTopLeft(Pnt2f(1,1));
       HorizontalBlueRidge1->setBottomRight(Pnt2f(2,7));
       HorizontalBlueRidge1->setColor(Color4f(0.55,0.69,0.97,1.0));
	endEditCP(HorizontalBlueRidge1);

    RectUIDrawObjectPtr HorizontalBlueRidge2 = RectUIDrawObject::create();
	beginEditCP(HorizontalBlueRidge2);
       HorizontalBlueRidge2->setTopLeft(Pnt2f(3,1));
       HorizontalBlueRidge2->setBottomRight(Pnt2f(4,7));
       HorizontalBlueRidge2->setColor(Color4f(0.55,0.69,0.97,1.0));
	endEditCP(HorizontalBlueRidge2);
    
    RectUIDrawObjectPtr HorizontalBlueRidge3 = RectUIDrawObject::create();
	beginEditCP(HorizontalBlueRidge3);
       HorizontalBlueRidge3->setTopLeft(Pnt2f(5,1));
       HorizontalBlueRidge3->setBottomRight(Pnt2f(6,7));
       HorizontalBlueRidge3->setColor(Color4f(0.55,0.69,0.97,1.0));
	endEditCP(HorizontalBlueRidge3);

    RectUIDrawObjectPtr HorizontalBlueRidge4 = RectUIDrawObject::create();
	beginEditCP(HorizontalBlueRidge4);
       HorizontalBlueRidge4->setTopLeft(Pnt2f(7,1));
       HorizontalBlueRidge4->setBottomRight(Pnt2f(8,7));
       HorizontalBlueRidge4->setColor(Color4f(0.55,0.69,0.97,1.0));
	endEditCP(HorizontalBlueRidge4);

    UIDrawObjectCanvasPtr WindowsHorizontalScrollBarRidges = UIDrawObjectCanvas::create();
	beginEditCP(WindowsHorizontalScrollBarRidges);
        WindowsHorizontalScrollBarRidges->getDrawObjects().push_back(HorizontalWhiteRidge1);
        WindowsHorizontalScrollBarRidges->getDrawObjects().push_back(HorizontalBlueRidge1);
        WindowsHorizontalScrollBarRidges->getDrawObjects().push_back(HorizontalWhiteRidge2);
        WindowsHorizontalScrollBarRidges->getDrawObjects().push_back(HorizontalBlueRidge2);
        WindowsHorizontalScrollBarRidges->getDrawObjects().push_back(HorizontalWhiteRidge3);
        WindowsHorizontalScrollBarRidges->getDrawObjects().push_back(HorizontalBlueRidge3);
        WindowsHorizontalScrollBarRidges->getDrawObjects().push_back(HorizontalWhiteRidge4);
        WindowsHorizontalScrollBarRidges->getDrawObjects().push_back(HorizontalBlueRidge4);
	endEditCP(WindowsHorizontalScrollBarRidges);
    
    //Horizontal Active Scroll Bar Center Ridges
    RectUIDrawObjectPtr HorizontalActiveWhiteRidge1 = RectUIDrawObject::create();
	beginEditCP(HorizontalActiveWhiteRidge1);
       HorizontalActiveWhiteRidge1->setTopLeft(Pnt2f(0,0));
       HorizontalActiveWhiteRidge1->setBottomRight(Pnt2f(1,6));
       HorizontalActiveWhiteRidge1->setColor(Color4f(0.81,0.87,0.99,1.0));
	endEditCP(HorizontalActiveWhiteRidge1);

    RectUIDrawObjectPtr HorizontalActiveWhiteRidge2 = RectUIDrawObject::create();
	beginEditCP(HorizontalActiveWhiteRidge2);
       HorizontalActiveWhiteRidge2->setTopLeft(Pnt2f(2,0));
       HorizontalActiveWhiteRidge2->setBottomRight(Pnt2f(3,6));
       HorizontalActiveWhiteRidge2->setColor(Color4f(0.81,0.87,0.99,1.0));
	endEditCP(HorizontalActiveWhiteRidge2);
    
    RectUIDrawObjectPtr HorizontalActiveWhiteRidge3 = RectUIDrawObject::create();
	beginEditCP(HorizontalActiveWhiteRidge3);
       HorizontalActiveWhiteRidge3->setTopLeft(Pnt2f(4,0));
       HorizontalActiveWhiteRidge3->setBottomRight(Pnt2f(5,6));
       HorizontalActiveWhiteRidge3->setColor(Color4f(0.81,0.87,0.99,1.0));
	endEditCP(HorizontalActiveWhiteRidge3);

    RectUIDrawObjectPtr HorizontalActiveWhiteRidge4 = RectUIDrawObject::create();
	beginEditCP(HorizontalActiveWhiteRidge4);
       HorizontalActiveWhiteRidge4->setTopLeft(Pnt2f(6,0));
       HorizontalActiveWhiteRidge4->setBottomRight(Pnt2f(7,6));
       HorizontalActiveWhiteRidge4->setColor(Color4f(0.81,0.87,0.99,1.0));
	endEditCP(HorizontalActiveWhiteRidge4);
    
    RectUIDrawObjectPtr HorizontalActiveBlueRidge1 = RectUIDrawObject::create();
	beginEditCP(HorizontalActiveBlueRidge1);
       HorizontalActiveBlueRidge1->setTopLeft(Pnt2f(1,1));
       HorizontalActiveBlueRidge1->setBottomRight(Pnt2f(2,7));
       HorizontalActiveBlueRidge1->setColor(Color4f(0.51,0.62,0.85,1.0));
	endEditCP(HorizontalActiveBlueRidge1);

    RectUIDrawObjectPtr HorizontalActiveBlueRidge2 = RectUIDrawObject::create();
	beginEditCP(HorizontalActiveBlueRidge2);
       HorizontalActiveBlueRidge2->setTopLeft(Pnt2f(3,1));
       HorizontalActiveBlueRidge2->setBottomRight(Pnt2f(4,7));
       HorizontalActiveBlueRidge2->setColor(Color4f(0.51,0.62,0.85,1.0));
	endEditCP(HorizontalActiveBlueRidge2);
    
    RectUIDrawObjectPtr HorizontalActiveBlueRidge3 = RectUIDrawObject::create();
	beginEditCP(HorizontalActiveBlueRidge3);
       HorizontalActiveBlueRidge3->setTopLeft(Pnt2f(5,1));
       HorizontalActiveBlueRidge3->setBottomRight(Pnt2f(6,7));
       HorizontalActiveBlueRidge3->setColor(Color4f(0.51,0.62,0.85,1.0));
	endEditCP(HorizontalActiveBlueRidge3);

    RectUIDrawObjectPtr HorizontalActiveBlueRidge4 = RectUIDrawObject::create();
	beginEditCP(HorizontalActiveBlueRidge4);
       HorizontalActiveBlueRidge4->setTopLeft(Pnt2f(7,1));
       HorizontalActiveBlueRidge4->setBottomRight(Pnt2f(8,7));
       HorizontalActiveBlueRidge4->setColor(Color4f(0.51,0.62,0.85,1.0));
	endEditCP(HorizontalActiveBlueRidge4);

    UIDrawObjectCanvasPtr WindowsHorizontalActiveScrollBarRidges = UIDrawObjectCanvas::create();
	beginEditCP(WindowsHorizontalActiveScrollBarRidges);
        WindowsHorizontalActiveScrollBarRidges->getDrawObjects().push_back(HorizontalActiveWhiteRidge1);
        WindowsHorizontalActiveScrollBarRidges->getDrawObjects().push_back(HorizontalActiveBlueRidge1);
        WindowsHorizontalActiveScrollBarRidges->getDrawObjects().push_back(HorizontalActiveWhiteRidge2);
        WindowsHorizontalActiveScrollBarRidges->getDrawObjects().push_back(HorizontalActiveBlueRidge2);
        WindowsHorizontalActiveScrollBarRidges->getDrawObjects().push_back(HorizontalActiveWhiteRidge3);
        WindowsHorizontalActiveScrollBarRidges->getDrawObjects().push_back(HorizontalActiveBlueRidge3);
        WindowsHorizontalActiveScrollBarRidges->getDrawObjects().push_back(HorizontalActiveWhiteRidge4);
        WindowsHorizontalActiveScrollBarRidges->getDrawObjects().push_back(HorizontalActiveBlueRidge4);
	endEditCP(WindowsHorizontalActiveScrollBarRidges);
    
    //Horizontal Rollover Scroll Bar Center Ridges
    RectUIDrawObjectPtr HorizontalRolloverWhiteRidge1 = RectUIDrawObject::create();
	beginEditCP(HorizontalRolloverWhiteRidge1);
       HorizontalRolloverWhiteRidge1->setTopLeft(Pnt2f(0,0));
       HorizontalRolloverWhiteRidge1->setBottomRight(Pnt2f(1,6));
       HorizontalRolloverWhiteRidge1->setColor(Color4f(0.99,0.99,1.0,1.0));
	endEditCP(HorizontalRolloverWhiteRidge1);

    RectUIDrawObjectPtr HorizontalRolloverWhiteRidge2 = RectUIDrawObject::create();
	beginEditCP(HorizontalRolloverWhiteRidge2);
       HorizontalRolloverWhiteRidge2->setTopLeft(Pnt2f(2,0));
       HorizontalRolloverWhiteRidge2->setBottomRight(Pnt2f(3,6));
       HorizontalRolloverWhiteRidge2->setColor(Color4f(0.99,0.99,1.0,1.0));
	endEditCP(HorizontalRolloverWhiteRidge2);
    
    RectUIDrawObjectPtr HorizontalRolloverWhiteRidge3 = RectUIDrawObject::create();
	beginEditCP(HorizontalRolloverWhiteRidge3);
       HorizontalRolloverWhiteRidge3->setTopLeft(Pnt2f(4,0));
       HorizontalRolloverWhiteRidge3->setBottomRight(Pnt2f(5,6));
       HorizontalRolloverWhiteRidge3->setColor(Color4f(0.99,0.99,1.0,1.0));
	endEditCP(HorizontalRolloverWhiteRidge3);

    RectUIDrawObjectPtr HorizontalRolloverWhiteRidge4 = RectUIDrawObject::create();
	beginEditCP(HorizontalRolloverWhiteRidge4);
       HorizontalRolloverWhiteRidge4->setTopLeft(Pnt2f(6,0));
       HorizontalRolloverWhiteRidge4->setBottomRight(Pnt2f(7,6));
       HorizontalRolloverWhiteRidge4->setColor(Color4f(0.99,0.99,1.0,1.0));
	endEditCP(HorizontalRolloverWhiteRidge4);
    
    RectUIDrawObjectPtr HorizontalRolloverBlueRidge1 = RectUIDrawObject::create();
	beginEditCP(HorizontalRolloverBlueRidge1);
       HorizontalRolloverBlueRidge1->setTopLeft(Pnt2f(1,1));
       HorizontalRolloverBlueRidge1->setBottomRight(Pnt2f(2,7));
       HorizontalRolloverBlueRidge1->setColor(Color4f(0.61,0.77,1.0,1.0));
	endEditCP(HorizontalRolloverBlueRidge1);

    RectUIDrawObjectPtr HorizontalRolloverBlueRidge2 = RectUIDrawObject::create();
	beginEditCP(HorizontalRolloverBlueRidge2);
       HorizontalRolloverBlueRidge2->setTopLeft(Pnt2f(3,1));
       HorizontalRolloverBlueRidge2->setBottomRight(Pnt2f(4,7));
       HorizontalRolloverBlueRidge2->setColor(Color4f(0.61,0.77,1.0,1.0));
	endEditCP(HorizontalRolloverBlueRidge2);
    
    RectUIDrawObjectPtr HorizontalRolloverBlueRidge3 = RectUIDrawObject::create();
	beginEditCP(HorizontalRolloverBlueRidge3);
       HorizontalRolloverBlueRidge3->setTopLeft(Pnt2f(5,1));
       HorizontalRolloverBlueRidge3->setBottomRight(Pnt2f(6,7));
       HorizontalRolloverBlueRidge3->setColor(Color4f(0.61,0.77,1.0,1.0));
	endEditCP(HorizontalRolloverBlueRidge3);

    RectUIDrawObjectPtr HorizontalRolloverBlueRidge4 = RectUIDrawObject::create();
	beginEditCP(HorizontalRolloverBlueRidge4);
       HorizontalRolloverBlueRidge4->setTopLeft(Pnt2f(7,1));
       HorizontalRolloverBlueRidge4->setBottomRight(Pnt2f(8,7));
       HorizontalRolloverBlueRidge4->setColor(Color4f(0.61,0.77,1.0,1.0));
	endEditCP(HorizontalRolloverBlueRidge4);

    UIDrawObjectCanvasPtr WindowsHorizontalRolloverScrollBarRidges = UIDrawObjectCanvas::create();
	beginEditCP(WindowsHorizontalRolloverScrollBarRidges);
        WindowsHorizontalRolloverScrollBarRidges->getDrawObjects().push_back(HorizontalRolloverWhiteRidge1);
        WindowsHorizontalRolloverScrollBarRidges->getDrawObjects().push_back(HorizontalRolloverBlueRidge1);
        WindowsHorizontalRolloverScrollBarRidges->getDrawObjects().push_back(HorizontalRolloverWhiteRidge2);
        WindowsHorizontalRolloverScrollBarRidges->getDrawObjects().push_back(HorizontalRolloverBlueRidge2);
        WindowsHorizontalRolloverScrollBarRidges->getDrawObjects().push_back(HorizontalRolloverWhiteRidge3);
        WindowsHorizontalRolloverScrollBarRidges->getDrawObjects().push_back(HorizontalRolloverBlueRidge3);
        WindowsHorizontalRolloverScrollBarRidges->getDrawObjects().push_back(HorizontalRolloverWhiteRidge4);
        WindowsHorizontalRolloverScrollBarRidges->getDrawObjects().push_back(HorizontalRolloverBlueRidge4);
	endEditCP(WindowsHorizontalRolloverScrollBarRidges);

	ButtonPtr WindowsHorizontalScrollBarDrawObject = Button::create();
	beginEditCP(WindowsHorizontalScrollBarDrawObject);
		WindowsHorizontalScrollBarDrawObject->setBorder(WindowsHorizontalScrollBarDrawObjectBorder);
		WindowsHorizontalScrollBarDrawObject->setRolloverBorder(WindowsHorizontalScrollBarDrawObjectBorder);
		WindowsHorizontalScrollBarDrawObject->setFocusedBorder(WindowsHorizontalScrollBarDrawObjectBorder);
		WindowsHorizontalScrollBarDrawObject->setDisabledBorder(WindowsDisabledHorizontalScrollBarDrawObjectBorder);
		WindowsHorizontalScrollBarDrawObject->setActiveBorder(WindowsHorizontalScrollBarDrawObjectBorder);
        
		WindowsHorizontalScrollBarDrawObject->setBackground(WindowsHorizontalScrollBarDrawObjectBackground);
		WindowsHorizontalScrollBarDrawObject->setRolloverBackground(WindowsRolloverHorizontalScrollBarDrawObjectBackground);
		WindowsHorizontalScrollBarDrawObject->setFocusedBackground(WindowsHorizontalScrollBarDrawObjectBackground);
		WindowsHorizontalScrollBarDrawObject->setDisabledBackground(WindowsDisabledHorizontalScrollBarDrawObjectBackground);
		WindowsHorizontalScrollBarDrawObject->setActiveBackground(WindowsActiveHorizontalScrollBarDrawObjectBackground);
        
        WindowsHorizontalScrollBarDrawObject->setVerticalAlignment(0.5);
        WindowsHorizontalScrollBarDrawObject->setHorizontalAlignment(0.5);
        WindowsHorizontalScrollBarDrawObject->setActiveOffset(Vec2f(0,0));

        WindowsHorizontalScrollBarDrawObject->setDrawObject(WindowsHorizontalScrollBarRidges);
        WindowsHorizontalScrollBarDrawObject->setActiveDrawObject(WindowsHorizontalActiveScrollBarRidges);
        WindowsHorizontalScrollBarDrawObject->setFocusedDrawObject(WindowsHorizontalScrollBarRidges);
        WindowsHorizontalScrollBarDrawObject->setRolloverDrawObject(WindowsHorizontalRolloverScrollBarRidges);
        WindowsHorizontalScrollBarDrawObject->setDisabledDrawObject(WindowsHorizontalScrollBarRidges);
	endEditCP(WindowsHorizontalScrollBarDrawObject);

	//Windows ScrollBar
	beginEditCP(WindowsScrollBar);
		WindowsScrollBar->setEnabled(true);
		WindowsScrollBar->setVisible(true);
		
		WindowsScrollBar->setConstraints(NullFC);
		//Sizes
		WindowsScrollBar->setMinSize(Vec2f(0,0));
		WindowsScrollBar->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsScrollBar->setPreferredSize(Vec2f(17,100));

		//Border
		WindowsScrollBar->setBorder(WindowsScrollBarBorder);
		WindowsScrollBar->setRolloverBorder(WindowsScrollBarBorder);
		WindowsScrollBar->setFocusedBorder(WindowsScrollBarBorder);
		WindowsScrollBar->setDisabledBorder(WindowsScrollBarBorder);
		
		//Background
		WindowsScrollBar->setBackground(WindowsScrollBarBackground);
		WindowsScrollBar->setRolloverBackground(WindowsScrollBarBackground);
		WindowsScrollBar->setFocusedBackground(WindowsScrollBarBackground);
		WindowsScrollBar->setDisabledBackground(WindowsScrollBarBackground);
		
		//Opacity
		WindowsScrollBar->setOpacity(1.0);

        //Min Button
        WindowsScrollBar->setVerticalMinButton(WindowsScrollBarVerticalMinButton);
        WindowsScrollBar->setHorizontalMinButton(WindowsScrollBarHorizontalMinButton);

        //Max Button
        WindowsScrollBar->setVerticalMaxButton(WindowsScrollBarVerticalMaxButton);
        WindowsScrollBar->setHorizontalMaxButton(WindowsScrollBarHorizontalMaxButton);

        //Scroll Field
        WindowsScrollBar->setVerticalScrollField(WindowsVerticalScrollFieldButton);
        WindowsScrollBar->setHorizontalScrollField(WindowsHorizontalScrollFieldButton);

        //Scroll Bar
        WindowsScrollBar->setVerticalScrollBar(WindowsVerticalScrollBarDrawObject);
        WindowsScrollBar->setHorizontalScrollBar(WindowsHorizontalScrollBarDrawObject);
        WindowsScrollBar->setScrollBarMinLength(20);
	endEditCP(WindowsScrollBar);

	//************************** ScrollPanel*****************************
	//Windows ScrollPanelBorder
	EmptyBorderPtr WindowsScrollPanelBorder = EmptyBorder::create();

	//Windows ScrollPanelBackground
	EmptyUIBackgroundPtr WindowsScrollPanelBackground = EmptyUIBackground::create();
    
	//Vertical ScrollBar
	ScrollBarPtr WindowsScrollPanelVerticalScrollBar = ScrollBar::create();
    beginEditCP(WindowsScrollPanelVerticalScrollBar, ScrollBar::PreferredSizeFieldMask | ScrollBar::OrientationFieldMask);
		WindowsScrollPanelVerticalScrollBar->setPreferredSize(Vec2f(17,100));
        WindowsScrollPanelVerticalScrollBar->setOrientation(ScrollBar::VERTICAL_ORIENTATION);
    beginEditCP(WindowsScrollPanelVerticalScrollBar, ScrollBar::PreferredSizeFieldMask | ScrollBar::OrientationFieldMask);

	//Horizontal ScrollBar
	ScrollBarPtr WindowsScrollPanelHorizontalScrollBar = ScrollBar::create();
    beginEditCP(WindowsScrollPanelHorizontalScrollBar, ScrollBar::PreferredSizeFieldMask | ScrollBar::OrientationFieldMask);
		WindowsScrollPanelHorizontalScrollBar->setPreferredSize(Vec2f(100,17));
        WindowsScrollPanelHorizontalScrollBar->setOrientation(ScrollBar::HORIZONTAL_ORIENTATION);
    beginEditCP(WindowsScrollPanelHorizontalScrollBar, ScrollBar::PreferredSizeFieldMask | ScrollBar::OrientationFieldMask);


	//Windows ScrollPanel
	beginEditCP(WindowsScrollPanel);
		WindowsScrollPanel->setEnabled(true);
		WindowsScrollPanel->setVisible(true);
		
		WindowsScrollPanel->setConstraints(NullFC);
		//Sizes
		WindowsScrollPanel->setMinSize(Vec2f(0,0));
		WindowsScrollPanel->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsScrollPanel->setPreferredSize(Vec2f(100,100));

		//Border
		WindowsScrollPanel->setBorder(WindowsScrollPanelBorder);
		WindowsScrollPanel->setRolloverBorder(WindowsScrollPanelBorder);
		WindowsScrollPanel->setFocusedBorder(WindowsScrollPanelBorder);
		WindowsScrollPanel->setDisabledBorder(WindowsScrollPanelBorder);
		
		//Background
		WindowsScrollPanel->setBackground(WindowsScrollPanelBackground);
		WindowsScrollPanel->setRolloverBackground(WindowsScrollPanelBackground);
		WindowsScrollPanel->setFocusedBackground(WindowsScrollPanelBackground);
		WindowsScrollPanel->setDisabledBackground(WindowsScrollPanelBackground);
		
		//Opacity
		WindowsScrollPanel->setOpacity(1.0);

        //Vertical Scroll Bar
        WindowsScrollPanel->setVerticalScrollBarDisplayPolicy(ScrollPanel::SCROLLBAR_AS_NEEDED);
        WindowsScrollPanel->setVerticalScrollBar(WindowsScrollPanelVerticalScrollBar);

        //Horizontal Scroll Bar
        WindowsScrollPanel->setHorizontalScrollBarDisplayPolicy(ScrollPanel::SCROLLBAR_AS_NEEDED);
        WindowsScrollPanel->setHorizontalScrollBar(WindowsScrollPanelHorizontalScrollBar);
	endEditCP(WindowsScrollPanel);

	//************************** UIViewport *****************************
	//Windows UIViewportBorder
	EmptyBorderPtr WindowsUIViewportBorder = EmptyBorder::create();
	beginEditCP(WindowsUIViewportBorder);
		WindowsUIViewportBorder->setLeftWidth(0);
		WindowsUIViewportBorder->setRightWidth(0);
		WindowsUIViewportBorder->setTopWidth(0);
		WindowsUIViewportBorder->setBottomWidth(0);
	endEditCP(WindowsUIViewportBorder);

	//Windows UIViewportBackground
	EmptyUIBackgroundPtr WindowsUIViewportBackground = EmptyUIBackground::create();

	//Windows UIViewport
	beginEditCP(WindowsUIViewport);
		WindowsUIViewport->setEnabled(true);
		WindowsUIViewport->setVisible(true);
		
		WindowsUIViewport->setConstraints(NullFC);
		//Sizes
		WindowsUIViewport->setMinSize(Vec2f(0,0));
		WindowsUIViewport->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsUIViewport->setPreferredSize(Vec2f(100,100));

		//Border
		WindowsUIViewport->setBorder(WindowsUIViewportBorder);
		
		//Background
		WindowsUIViewport->setBackground(WindowsUIViewportBackground);
		
		//Opacity
		WindowsUIViewport->setOpacity(1.0);
	endEditCP(WindowsUIViewport);
	
	//************************** RotatedComponent*****************************
	//Windows RotatedComponentBorder
	EmptyBorderPtr WindowsRotatedComponentBorder = EmptyBorder::create();

	//Windows RotatedComponentBackground
	EmptyUIBackgroundPtr WindowsRotatedComponentBackground = EmptyUIBackground::create();

	//Windows RotatedComponent
	beginEditCP(WindowsRotatedComponent);
		WindowsRotatedComponent->setEnabled(true);
		WindowsRotatedComponent->setVisible(true);
		
		WindowsRotatedComponent->setConstraints(NullFC);
		//Sizes
		WindowsRotatedComponent->setMinSize(Vec2f(0,0));
		WindowsRotatedComponent->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsRotatedComponent->setPreferredSize(Vec2f(100,100));

		//Border
		WindowsRotatedComponent->setBorder(WindowsRotatedComponentBorder);
		
		//Background
		WindowsRotatedComponent->setBackground(WindowsRotatedComponentBackground);
		
		//Opacity
		WindowsRotatedComponent->setOpacity(1.0);

		WindowsRotatedComponent->setInternalComponent(NullFC);

        WindowsRotatedComponent->setResizePolicy(RotatedComponent::RESIZE_TO_MIN);
	endEditCP(WindowsRotatedComponent);

    
	//************************** List *****************************
	//Windows RotatedComponentBorder
	EmptyBorderPtr WindowsListBorder = EmptyBorder::create();

	//Windows RotatedComponentBackground
	EmptyUIBackgroundPtr WindowsListBackground = EmptyUIBackground::create();

	//************************** DefaultListComponentGenerator *****************************
	LabelPtr WindowsDefaultListComponentGeneratorComponentPrototype = Label::create();
	beginEditCP(WindowsDefaultListComponentGeneratorComponentPrototype, Label::BordersFieldMask);
		WindowsDefaultListComponentGeneratorComponentPrototype->setBorders(WindowsEmptyBorder);
	endEditCP(WindowsDefaultListComponentGeneratorComponentPrototype, Label::BordersFieldMask);

    ColorUIBackgroundPtr WindowsDefaultListComponentGeneratorSelectedBackground = ColorUIBackground::create();
	beginEditCP(WindowsDefaultListComponentGeneratorSelectedBackground, ColorUIBackground::ColorFieldMask);
		WindowsDefaultListComponentGeneratorSelectedBackground->setColor(Color4f(0.4f,0.4f,1.0f,1.0f));
	endEditCP(WindowsDefaultListComponentGeneratorSelectedBackground, ColorUIBackground::ColorFieldMask);

    UIBackgroundPtr WindowsDefaultListComponentGeneratorFocusedBackground = WindowsDefaultListComponentGeneratorComponentPrototype->getBackground();

    BorderPtr WindowsDefaultListComponentGeneratorSelectedBorder = WindowsDefaultListComponentGeneratorComponentPrototype->getBorder();

    LineBorderPtr WindowsDefaultListComponentGeneratorFocusedBorder = LineBorder::create();
	beginEditCP(WindowsDefaultListComponentGeneratorFocusedBorder, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);
		WindowsDefaultListComponentGeneratorFocusedBorder->setWidth(1);
		WindowsDefaultListComponentGeneratorFocusedBorder->setColor(Color4f(0.0f,0.0f,1.0f,1.0f));
	endEditCP(WindowsDefaultListComponentGeneratorFocusedBorder, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);
    
	//DefaultListComponentGenerator
    beginEditCP(WindowsDefaultListComponentGenerator);
		WindowsDefaultListComponentGenerator->setDrawObjectPrototype(WindowsDefaultListComponentGeneratorComponentPrototype);
		WindowsDefaultListComponentGenerator->setSelectedBackground(WindowsDefaultListComponentGeneratorSelectedBackground);
		WindowsDefaultListComponentGenerator->setFocusedBackground(WindowsDefaultListComponentGeneratorFocusedBackground);
		WindowsDefaultListComponentGenerator->setSelectedBorder(WindowsDefaultListComponentGeneratorSelectedBorder);
		WindowsDefaultListComponentGenerator->setFocusedBorder(WindowsDefaultListComponentGeneratorFocusedBorder);
		WindowsDefaultListComponentGenerator->setSelectedTextColor(Color4f(1.0f,1.0f,1.0f,1.0f));
		WindowsDefaultListComponentGenerator->setFocusedTextColor(Color4f(0.0f,0.0f,0.0f,1.0f));
		WindowsDefaultListComponentGenerator->setFocusedBackgroundHasPriority(false);
		WindowsDefaultListComponentGenerator->setFocusedBorderHasPriority(true);
		WindowsDefaultListComponentGenerator->setFocusedTextColorHasPriority(false);
    endEditCP(WindowsDefaultListComponentGenerator);

	//Windows List
	beginEditCP(WindowsList);
		WindowsList->setEnabled(true);
		WindowsList->setVisible(true);
		
		WindowsList->setConstraints(NullFC);
		//Sizes
		WindowsList->setMinSize(Vec2f(0,0));
		WindowsList->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsList->setPreferredSize(Vec2f(100,100));

		//Border
		WindowsList->setBorder(WindowsListBorder);
		WindowsList->setRolloverBorder(WindowsListBorder);
		WindowsList->setFocusedBorder(WindowsListBorder);
		WindowsList->setDisabledBorder(WindowsListBorder);
		
		//Background
		WindowsList->setBackground(WindowsListBackground);
		WindowsList->setRolloverBackground(WindowsListBackground);
		WindowsList->setFocusedBackground(WindowsListBackground);
		WindowsList->setDisabledBackground(WindowsListBackground);
		
		//Opacity
		WindowsList->setOpacity(1.0);
        
        WindowsList->setCellMajorAxisLength(25);
		WindowsList->setCellGenerator(WindowsDefaultListComponentGenerator);
		WindowsList->setAutoScrollToFocused(true);
		
	endEditCP(WindowsList);
    
	//************************** Spinner *****************************

    //Spinner Next Draw Object
	PolygonUIDrawObjectPtr WindowsSpinnerNextButtonDrawObject1 = PolygonUIDrawObject::create();
	beginEditCP(WindowsSpinnerNextButtonDrawObject1);
		WindowsSpinnerNextButtonDrawObject1->setColor(Color4f(0.3,0.38,0.52,1.0));
		WindowsSpinnerNextButtonDrawObject1->setOpacity(1.0);
        WindowsSpinnerNextButtonDrawObject1->getVerticies().push_back(Pnt2f(0,4));
        WindowsSpinnerNextButtonDrawObject1->getVerticies().push_back(Pnt2f(4,0));
        WindowsSpinnerNextButtonDrawObject1->getVerticies().push_back(Pnt2f(4,2));
        WindowsSpinnerNextButtonDrawObject1->getVerticies().push_back(Pnt2f(1,5));
	endEditCP(WindowsSpinnerNextButtonDrawObject1);
	PolygonUIDrawObjectPtr WindowsSpinnerNextButtonDrawObject2 = PolygonUIDrawObject::create();
	beginEditCP(WindowsSpinnerNextButtonDrawObject2);
		WindowsSpinnerNextButtonDrawObject2->setColor(Color4f(0.3,0.38,0.52,1.0));
		WindowsSpinnerNextButtonDrawObject2->setOpacity(1.0);
        WindowsSpinnerNextButtonDrawObject2->getVerticies().push_back(Pnt2f(4,0));
        WindowsSpinnerNextButtonDrawObject2->getVerticies().push_back(Pnt2f(8,4));
        WindowsSpinnerNextButtonDrawObject2->getVerticies().push_back(Pnt2f(7,5));
        WindowsSpinnerNextButtonDrawObject2->getVerticies().push_back(Pnt2f(4,2));
	endEditCP(WindowsSpinnerNextButtonDrawObject2);
    
	UIDrawObjectCanvasPtr WindowsSpinnerNextButtonCanvas = UIDrawObjectCanvas::create();
	beginEditCP(WindowsSpinnerNextButtonCanvas);
	   WindowsSpinnerNextButtonCanvas->getDrawObjects().push_back(WindowsSpinnerNextButtonDrawObject1);
	   WindowsSpinnerNextButtonCanvas->getDrawObjects().push_back(WindowsSpinnerNextButtonDrawObject2);
	endEditCP(WindowsSpinnerNextButtonCanvas);

    ButtonPtr WindowsSpinnerNextButton = Button::create();
    beginEditCP(WindowsSpinnerNextButton);
        WindowsSpinnerNextButton->setPreferredSize(Vec2f(17,17));
        WindowsSpinnerNextButton->setEnableActionOnMouseDownTime(true);
        WindowsSpinnerNextButton->setActionOnMouseDownRate(0.2);
        
		//Border
		WindowsSpinnerNextButton->setBorder(WindowsScrollBarButtonBorder);
		WindowsSpinnerNextButton->setRolloverBorder(WindowsScrollBarButtonBorder);
		WindowsSpinnerNextButton->setFocusedBorder(WindowsScrollBarButtonBorder);
		WindowsSpinnerNextButton->setDisabledBorder(WindowsScrollBarDisabledButtonBorder);

		//Background
        WindowsSpinnerNextButton->setBackground(WindowsScrollBarButtonBackground);
        WindowsSpinnerNextButton->setActiveBackground(WindowsScrollBarActiveButtonBackground);
        WindowsSpinnerNextButton->setDisabledBackground(WindowsScrollBarDisabledButtonBackground);
        WindowsSpinnerNextButton->setFocusedBackground(WindowsScrollBarButtonBackground);
        WindowsSpinnerNextButton->setRolloverBackground(WindowsScrollBarRolloverButtonBackground);

        WindowsSpinnerNextButton->setActiveOffset(Vec2f(0,0));
        WindowsSpinnerNextButton->setDrawObject(WindowsSpinnerNextButtonCanvas);
        WindowsSpinnerNextButton->setActiveDrawObject(WindowsSpinnerNextButtonCanvas);
        WindowsSpinnerNextButton->setFocusedDrawObject(WindowsSpinnerNextButtonCanvas);
        WindowsSpinnerNextButton->setRolloverDrawObject(WindowsSpinnerNextButtonCanvas);
        WindowsSpinnerNextButton->setDisabledDrawObject(WindowsSpinnerNextButtonCanvas);

		WindowsSpinnerNextButton->setVerticalAlignment(0.5f);
		WindowsSpinnerNextButton->setHorizontalAlignment(0.5f);
    endEditCP(WindowsSpinnerNextButton);

    //Spinner Previous Draw Object
	PolygonUIDrawObjectPtr WindowsSpinnerPreviousButtonDrawObject1 = PolygonUIDrawObject::create();
	beginEditCP(WindowsSpinnerPreviousButtonDrawObject1);
		WindowsSpinnerPreviousButtonDrawObject1->setColor(Color4f(0.3,0.38,0.52,1.0));
		WindowsSpinnerPreviousButtonDrawObject1->setOpacity(1.0);
        WindowsSpinnerPreviousButtonDrawObject1->getVerticies().push_back(Pnt2f(1,0));
        WindowsSpinnerPreviousButtonDrawObject1->getVerticies().push_back(Pnt2f(4,3));
        WindowsSpinnerPreviousButtonDrawObject1->getVerticies().push_back(Pnt2f(4,5));
        WindowsSpinnerPreviousButtonDrawObject1->getVerticies().push_back(Pnt2f(0,1));
	endEditCP(WindowsSpinnerPreviousButtonDrawObject1);
	PolygonUIDrawObjectPtr WindowsSpinnerPreviousButtonDrawObject2 = PolygonUIDrawObject::create();
	beginEditCP(WindowsSpinnerPreviousButtonDrawObject2);
		WindowsSpinnerPreviousButtonDrawObject2->setColor(Color4f(0.3,0.38,0.52,1.0));
		WindowsSpinnerPreviousButtonDrawObject2->setOpacity(1.0);
        WindowsSpinnerPreviousButtonDrawObject2->getVerticies().push_back(Pnt2f(4,3));
        WindowsSpinnerPreviousButtonDrawObject2->getVerticies().push_back(Pnt2f(7,0));
        WindowsSpinnerPreviousButtonDrawObject2->getVerticies().push_back(Pnt2f(8,1));
        WindowsSpinnerPreviousButtonDrawObject2->getVerticies().push_back(Pnt2f(4,5));
	endEditCP(WindowsSpinnerPreviousButtonDrawObject2);
    
	UIDrawObjectCanvasPtr WindowsSpinnerPreviousButtonCanvas = UIDrawObjectCanvas::create();
	beginEditCP(WindowsSpinnerPreviousButtonCanvas);
	   WindowsSpinnerPreviousButtonCanvas->getDrawObjects().push_back(WindowsSpinnerPreviousButtonDrawObject1);
	   WindowsSpinnerPreviousButtonCanvas->getDrawObjects().push_back(WindowsSpinnerPreviousButtonDrawObject2);
	endEditCP(WindowsSpinnerPreviousButtonCanvas);
    ButtonPtr WindowsSpinnerPreviousButton = Button::create();
    beginEditCP(WindowsSpinnerPreviousButton);
        WindowsSpinnerPreviousButton->setPreferredSize(Vec2f(17,17));
        WindowsSpinnerPreviousButton->setEnableActionOnMouseDownTime(true);
        WindowsSpinnerPreviousButton->setActionOnMouseDownRate(0.2);
		//Border
		WindowsSpinnerPreviousButton->setBorder(WindowsScrollBarButtonBorder);
		WindowsSpinnerPreviousButton->setRolloverBorder(WindowsScrollBarButtonBorder);
		WindowsSpinnerPreviousButton->setFocusedBorder(WindowsScrollBarButtonBorder);
		WindowsSpinnerPreviousButton->setDisabledBorder(WindowsScrollBarDisabledButtonBorder);

		//Background
        WindowsSpinnerPreviousButton->setBackground(WindowsScrollBarButtonBackground);
        WindowsSpinnerPreviousButton->setActiveBackground(WindowsScrollBarActiveButtonBackground);
        WindowsSpinnerPreviousButton->setDisabledBackground(WindowsScrollBarDisabledButtonBackground);
        WindowsSpinnerPreviousButton->setFocusedBackground(WindowsScrollBarButtonBackground);
        WindowsSpinnerPreviousButton->setRolloverBackground(WindowsScrollBarRolloverButtonBackground);

        WindowsSpinnerPreviousButton->setActiveOffset(Vec2f(0,0));

        WindowsSpinnerPreviousButton->setDrawObject(WindowsSpinnerPreviousButtonCanvas);
        WindowsSpinnerPreviousButton->setActiveDrawObject(WindowsSpinnerPreviousButtonCanvas);
        WindowsSpinnerPreviousButton->setFocusedDrawObject(WindowsSpinnerPreviousButtonCanvas);
        WindowsSpinnerPreviousButton->setRolloverDrawObject(WindowsSpinnerPreviousButtonCanvas);
        WindowsSpinnerPreviousButton->setDisabledDrawObject(WindowsSpinnerPreviousButtonCanvas);

		WindowsSpinnerPreviousButton->setVerticalAlignment(0.5f);
		WindowsSpinnerPreviousButton->setHorizontalAlignment(0.5f);
    endEditCP(WindowsSpinnerPreviousButton);

	//Windows SpinnerBorder
	EmptyBorderPtr WindowsSpinnerBorder = EmptyBorder::create();

	//Windows SpinnerBackground
	EmptyUIBackgroundPtr WindowsSpinnerBackground = EmptyUIBackground::create();

    beginEditCP(WindowsSpinner);
		WindowsSpinner->setConstraints(NullFC);
		//Sizes
		WindowsSpinner->setMinSize(Vec2f(0,0));
		WindowsSpinner->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsSpinner->setPreferredSize(Vec2f(50,23));

		//Border
		WindowsSpinner->setBorder(WindowsTextFieldBorder);
		WindowsSpinner->setRolloverBorder(WindowsTextFieldBorder);
		WindowsSpinner->setFocusedBorder(WindowsTextFieldBorder);
		WindowsSpinner->setDisabledBorder(WindowsTextFieldBorder);
		
		//Background
		WindowsSpinner->setBackground(WindowsTextFieldBackground);
		WindowsSpinner->setRolloverBackground(WindowsTextFieldBackground);
		WindowsSpinner->setFocusedBackground(WindowsTextFieldBackground);
		WindowsSpinner->setDisabledBackground(WindowsDisabledTextFieldBackground);
		
		//Opacity
		WindowsSpinner->setOpacity(1.0);

        //Spinner
        WindowsSpinner->setNextButton(WindowsSpinnerNextButton);
        WindowsSpinner->setPreviousButton(WindowsSpinnerPreviousButton);
		WindowsSpinner->setEditorToButtonOffset(2);
    endEditCP(WindowsSpinner);
	
	//************************** SpinnerDefaultEditor *****************************
	//Windows SpinnerDefaultEditor TextField
	TextFieldPtr WindowsSpinnerDefaultEditorTextField = TextField::create();
    beginEditCP(WindowsSpinnerDefaultEditorTextField, TextField::HorizontalAlignmentFieldMask);
        WindowsSpinnerDefaultEditorTextField->setHorizontalAlignment(1.0);
        
		//Border
		WindowsSpinnerDefaultEditorTextField->setBorder(WindowsEmptyBorder);
		WindowsSpinnerDefaultEditorTextField->setRolloverBorder(WindowsEmptyBorder);
		WindowsSpinnerDefaultEditorTextField->setFocusedBorder(WindowsEmptyBorder);
		WindowsSpinnerDefaultEditorTextField->setDisabledBorder(WindowsEmptyBorder);
		
		//Background
		WindowsSpinnerDefaultEditorTextField->setBackground(WindowsEmptyBackground);
		WindowsSpinnerDefaultEditorTextField->setRolloverBackground(WindowsEmptyBackground);
		WindowsSpinnerDefaultEditorTextField->setFocusedBackground(WindowsEmptyBackground);
		WindowsSpinnerDefaultEditorTextField->setDisabledBackground(WindowsEmptyBackground);
    endEditCP(WindowsSpinnerDefaultEditorTextField, TextField::HorizontalAlignmentFieldMask);

    beginEditCP(WindowsSpinnerDefaultEditor);
		WindowsSpinnerDefaultEditor->setConstraints(NullFC);
		//Sizes
		WindowsSpinnerDefaultEditor->setMinSize(Vec2f(0,0));
		WindowsSpinnerDefaultEditor->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsSpinnerDefaultEditor->setPreferredSize(Vec2f(200,100));

		//Border
		WindowsSpinnerDefaultEditor->setBorder(WindowsEmptyBorder);
		WindowsSpinnerDefaultEditor->setRolloverBorder(WindowsEmptyBorder);
		WindowsSpinnerDefaultEditor->setFocusedBorder(WindowsEmptyBorder);
		WindowsSpinnerDefaultEditor->setDisabledBorder(WindowsEmptyBorder);
		
		//Background
		WindowsSpinnerDefaultEditor->setBackground(WindowsEmptyBackground);
		WindowsSpinnerDefaultEditor->setRolloverBackground(WindowsEmptyBackground);
		WindowsSpinnerDefaultEditor->setFocusedBackground(WindowsEmptyBackground);
		WindowsSpinnerDefaultEditor->setDisabledBackground(WindowsEmptyBackground);
		
		//Opacity
		WindowsSpinnerDefaultEditor->setOpacity(1.0);

        //WindowsSpinnerDefaultEditor
        WindowsSpinnerDefaultEditor->setTextField(WindowsSpinnerDefaultEditorTextField);
    endEditCP(WindowsSpinnerDefaultEditor);
	
	//************************** SpinnerNumberEditor *****************************
	//Windows SpinnerNumberEditor TextField
	TextFieldPtr WindowsSpinnerNumberEditorTextField = TextField::create();
    beginEditCP(WindowsSpinnerNumberEditorTextField, TextField::HorizontalAlignmentFieldMask);
        WindowsSpinnerNumberEditorTextField->setHorizontalAlignment(1.0);
        
		//Border
		WindowsSpinnerNumberEditorTextField->setBorder(WindowsEmptyBorder);
		WindowsSpinnerNumberEditorTextField->setRolloverBorder(WindowsEmptyBorder);
		WindowsSpinnerNumberEditorTextField->setFocusedBorder(WindowsEmptyBorder);
		WindowsSpinnerNumberEditorTextField->setDisabledBorder(WindowsEmptyBorder);
		
		//Background
		WindowsSpinnerNumberEditorTextField->setBackground(WindowsEmptyBackground);
		WindowsSpinnerNumberEditorTextField->setRolloverBackground(WindowsEmptyBackground);
		WindowsSpinnerNumberEditorTextField->setFocusedBackground(WindowsEmptyBackground);
		WindowsSpinnerNumberEditorTextField->setDisabledBackground(WindowsEmptyBackground);
    endEditCP(WindowsSpinnerNumberEditorTextField, TextField::HorizontalAlignmentFieldMask);

    beginEditCP(WindowsSpinnerNumberEditor);
		WindowsSpinnerNumberEditor->setConstraints(NullFC);
		//Sizes
		WindowsSpinnerNumberEditor->setMinSize(Vec2f(0,0));
		WindowsSpinnerNumberEditor->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsSpinnerNumberEditor->setPreferredSize(Vec2f(200,100));

		//Border
		WindowsSpinnerNumberEditor->setBorder(WindowsEmptyBorder);
		WindowsSpinnerNumberEditor->setRolloverBorder(WindowsEmptyBorder);
		WindowsSpinnerNumberEditor->setFocusedBorder(WindowsEmptyBorder);
		WindowsSpinnerNumberEditor->setDisabledBorder(WindowsEmptyBorder);
		
		//Background
		WindowsSpinnerNumberEditor->setBackground(WindowsEmptyBackground);
		WindowsSpinnerNumberEditor->setRolloverBackground(WindowsEmptyBackground);
		WindowsSpinnerNumberEditor->setFocusedBackground(WindowsEmptyBackground);
		WindowsSpinnerNumberEditor->setDisabledBackground(WindowsEmptyBackground);
		
		//Opacity
		WindowsSpinnerNumberEditor->setOpacity(1.0);

        //WindowsSpinnerNumberEditor
        WindowsSpinnerNumberEditor->setTextField(WindowsSpinnerNumberEditorTextField);
    endEditCP(WindowsSpinnerNumberEditor);
	
	//************************** Separator *****************************
	//Windows SeparatorBorder

	//Windows SeparatorBackground
	EmptyBorderPtr WindowsSeparatorBorder = EmptyBorder::create();
	EmptyUIBackgroundPtr WindowsSeparatorBackground = EmptyUIBackground::create();

    beginEditCP(WindowsSeparator);
		WindowsSeparator->setConstraints(NullFC);
		//Sizes
		WindowsSeparator->setMinSize(Vec2f(0,0));
		WindowsSeparator->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsSeparator->setPreferredSize(Vec2f(25,25));

		//Border
		WindowsSeparator->setBorders(WindowsSeparatorBorder);
		
		//Background
		WindowsSeparator->setBackgrounds(WindowsSeparatorBackground);
		
		//Opacity
		WindowsSeparator->setOpacity(1.0);

        //Separator
        WindowsSeparator->setOrientation(Separator::VERTICAL_ORIENTATION);
        WindowsSeparator->setSeparatorSize(2.0f);
        WindowsSeparator->setColor(Color4f(0.3,0.38,0.52,1.0));
    endEditCP(WindowsSeparator);

	//************************** ProgressBar *****************************
	//Windows ProgressBarBorder
	RoundedCornerLineBorderPtr WindowsProgressBarBorder = RoundedCornerLineBorder::create();
	beginEditCP(WindowsProgressBarBorder);
		WindowsProgressBarBorder->setColor( Color4f(0.0, 0.0, 0.0 ,1.0) );
		WindowsProgressBarBorder->setWidth(1);
        WindowsProgressBarBorder->setCornerRadius(5);
	endEditCP(WindowsProgressBarBorder);
	
	//Windows ProgressBarBackground
	ColorUIBackgroundPtr ProgressBarBackground = ColorUIBackground::create();
	beginEditCP(ProgressBarBackground);
		ProgressBarBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
	endEditCP(ProgressBarBackground);
	
	//Windows ProgressBarDrawObjectBackground
	ColorUIBackgroundPtr ProgressBarDrawObjectBackground = ColorUIBackground::create();
	beginEditCP(ProgressBarDrawObjectBackground);
		ProgressBarDrawObjectBackground->setColor(Color4f(0.0, 1.0, 0.0, 1.0));
	endEditCP(ProgressBarDrawObjectBackground);

	//ProgressBar DrawObjectCanvas
	UIDrawObjectCanvasPtr WindowsProgressBarCanvas = UIDrawObjectCanvas::create();
	beginEditCP(WindowsProgressBarCanvas);
		//Border
		WindowsProgressBarCanvas->setBorder(WindowsEmptyBorder);
		WindowsProgressBarCanvas->setRolloverBorder(WindowsEmptyBorder);
		WindowsProgressBarCanvas->setFocusedBorder(WindowsEmptyBorder);
		WindowsProgressBarCanvas->setDisabledBorder(WindowsEmptyBorder);
		
		//Background
		WindowsProgressBarCanvas->setBackground(ProgressBarDrawObjectBackground);
		WindowsProgressBarCanvas->setRolloverBackground(ProgressBarDrawObjectBackground);
		WindowsProgressBarCanvas->setFocusedBackground(ProgressBarDrawObjectBackground);
		WindowsProgressBarCanvas->setDisabledBackground(ProgressBarDrawObjectBackground);
	endEditCP(WindowsProgressBarCanvas);

	//ProgressBar
    beginEditCP(WindowsProgressBar);
		WindowsProgressBar->setConstraints(NullFC);
		//Sizes
		WindowsProgressBar->setMinSize(Vec2f(0,0));
		WindowsProgressBar->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsProgressBar->setPreferredSize(Vec2f(200,27));

		//Border
		WindowsProgressBar->setBorder(WindowsProgressBarBorder);
		WindowsProgressBar->setRolloverBorder(WindowsProgressBarBorder);
		WindowsProgressBar->setFocusedBorder(WindowsProgressBarBorder);
		WindowsProgressBar->setDisabledBorder(WindowsProgressBarBorder);
		
		//Background
		WindowsProgressBar->setBackground(ProgressBarBackground);
		WindowsProgressBar->setRolloverBackground(ProgressBarBackground);
		WindowsProgressBar->setFocusedBackground(ProgressBarBackground);
		WindowsProgressBar->setDisabledBackground(ProgressBarBackground);
		
		//Opacity
		WindowsProgressBar->setOpacity(1.0);

        //ProgressBar
        WindowsProgressBar->setOrientation(ProgressBar::HORIZONTAL_ORIENTATION);
        WindowsProgressBar->setIndeterminate(false);
        WindowsProgressBar->setIndeterminateBarMoveRate(0.5);
        WindowsProgressBar->setIndeterminateBarSize(0.25);
        WindowsProgressBar->setEnableProgressString(false);
		WindowsProgressBar->setProgressString(std::string(""));
        WindowsProgressBar->setVerticalAlignment(0.5);
        WindowsProgressBar->setHorizontalAlignment(0.5);
        WindowsProgressBar->setFont(WindowsFont);
        WindowsProgressBar->setTextColor(Color4f(0.0,0.0,0.0,1.0));
        WindowsProgressBar->setProgressBarDrawObject(WindowsProgressBarCanvas);
    endEditCP(WindowsProgressBar);
    
	//************************** Slider *****************************
	RoundedCornerLineBorderPtr WindowsSliderKnobButtonRoundedCornerBorder = RoundedCornerLineBorder::create();
	beginEditCP(WindowsSliderKnobButtonRoundedCornerBorder);
		WindowsSliderKnobButtonRoundedCornerBorder->setColor( Color4f(0.71, 0.77, 0.80 ,1.0) );
		WindowsSliderKnobButtonRoundedCornerBorder->setWidth(1);
        WindowsSliderKnobButtonRoundedCornerBorder->setCornerRadius(3);
	endEditCP(WindowsSliderKnobButtonRoundedCornerBorder);
	
	MatteBorderPtr WindowsSliderKnobButtonMatteBorder = MatteBorder::create();
	beginEditCP(WindowsSliderKnobButtonMatteBorder);
		WindowsSliderKnobButtonMatteBorder->setRightWidth(3);
		WindowsSliderKnobButtonMatteBorder->setLeftWidth(3);
		WindowsSliderKnobButtonMatteBorder->setTopWidth(0);
		WindowsSliderKnobButtonMatteBorder->setBottomWidth(0);
		WindowsSliderKnobButtonMatteBorder->setColor(Color4f(0.28, 0.8, 0.27, 1.0));
	endEditCP(WindowsSliderKnobButtonMatteBorder);
	
	CompoundBorderPtr WindowsSliderKnobButtonBorder = CompoundBorder::create();
	beginEditCP(WindowsSliderKnobButtonBorder);
		WindowsSliderKnobButtonBorder->setInnerBorder(WindowsSliderKnobButtonMatteBorder);
		WindowsSliderKnobButtonBorder->setOuterBorder(WindowsSliderKnobButtonRoundedCornerBorder);
	endEditCP(WindowsSliderKnobButtonBorder);
	
	ColorUIBackgroundPtr WindowsSliderBackground = ColorUIBackground::create();
	beginEditCP(WindowsSliderBackground);
		WindowsSliderBackground->setColor(Color4f(0.95, 0.95, 0.94, 1.0));
	endEditCP(WindowsSliderBackground);

    ButtonPtr WindowsSliderKnobButton = Button::create();
    beginEditCP(WindowsSliderKnobButton);
        WindowsSliderKnobButton->setPreferredSize(Vec2f(21,11));
        
		//Border
		WindowsSliderKnobButton->setBorder(WindowsSliderKnobButtonBorder);
        WindowsSliderKnobButton->setActiveBorder(WindowsSliderKnobButtonBorder);
		WindowsSliderKnobButton->setRolloverBorder(WindowsSliderKnobButtonBorder);
		WindowsSliderKnobButton->setFocusedBorder(WindowsSliderKnobButtonBorder);
		WindowsSliderKnobButton->setDisabledBorder(WindowsSliderKnobButtonBorder);

		//Background
        WindowsSliderKnobButton->setBackground(WindowsSliderBackground);
        WindowsSliderKnobButton->setActiveBackground(WindowsSliderBackground);
        WindowsSliderKnobButton->setDisabledBackground(WindowsSliderBackground);
        WindowsSliderKnobButton->setFocusedBackground(WindowsSliderBackground);
        WindowsSliderKnobButton->setRolloverBackground(WindowsSliderBackground);

        WindowsSliderKnobButton->setActiveOffset(Vec2f(0,0));
    beginEditCP(WindowsSliderKnobButton);
    
    LabelPtr WindowsSliderPrototypeLabel = Label::create();
	beginEditCP(WindowsSliderPrototypeLabel);
		//Border
		WindowsSliderPrototypeLabel->setBorder(WindowsEmptyBorder);
		WindowsSliderPrototypeLabel->setRolloverBorder(WindowsEmptyBorder);
		WindowsSliderPrototypeLabel->setFocusedBorder(WindowsEmptyBorder);
		WindowsSliderPrototypeLabel->setDisabledBorder(WindowsEmptyBorder);
		
		//Background
		WindowsSliderPrototypeLabel->setBackground(WindowsEmptyBackground);
		WindowsSliderPrototypeLabel->setRolloverBackground(WindowsEmptyBackground);
		WindowsSliderPrototypeLabel->setFocusedBackground(WindowsEmptyBackground);
		WindowsSliderPrototypeLabel->setDisabledBackground(WindowsEmptyBackground);

		WindowsSliderPrototypeLabel->setVerticalAlignment(0.5);
		WindowsSliderPrototypeLabel->setHorizontalAlignment(0.0);
	endEditCP(WindowsSliderPrototypeLabel);

	//Windows SliderBorder
	EtchedBorderPtr WindowsSliderBorder = EtchedBorder::create();
	beginEditCP(WindowsSliderBorder);
		WindowsSliderBorder->setWidth(2);
		WindowsSliderBorder->setRaised(true);
		WindowsSliderBorder->setHighlight(Color4f(1.0, 1.0, 1.0, 1.0));
		WindowsSliderBorder->setShadow(Color4f(0.65, 0.65, 0.65, 1.0));
	endEditCP(WindowsSliderBorder);
	
	//Windows SliderBackground
	ColorUIBackgroundPtr SliderBackground = ColorUIBackground::create();
	beginEditCP(SliderBackground);
		SliderBackground->setColor(Color4f(0.93, 0.91, 0.85, 1.0));
	endEditCP(SliderBackground);
	
	//Windows SliderDrawObjectBackground
	ColorUIBackgroundPtr SliderTrackDrawObjectBackground = ColorUIBackground::create();
	beginEditCP(SliderTrackDrawObjectBackground);
		SliderTrackDrawObjectBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
	endEditCP(SliderTrackDrawObjectBackground);
	
	BevelBorderPtr SliderTrackDrawObjectBorder = BevelBorder::create();
	beginEditCP(SliderTrackDrawObjectBorder);
		SliderTrackDrawObjectBorder->setRaised(true);
		SliderTrackDrawObjectBorder->setWidth(1);
		SliderTrackDrawObjectBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
		SliderTrackDrawObjectBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
		SliderTrackDrawObjectBorder->setShadowInner(Color4f(0.85, 0.85, 0.85, 1.0));
		SliderTrackDrawObjectBorder->setShadowOuter(Color4f(0.65, 0.65, 0.65, 1.0));
	endEditCP(SliderTrackDrawObjectBorder);

	//Slider DrawObjectCanvas
	UIDrawObjectCanvasPtr WindowsSliderTrackCanvas = UIDrawObjectCanvas::create();
	beginEditCP(WindowsSliderTrackCanvas);
		WindowsSliderTrackCanvas->setPreferredSize(Vec2f(5,5));
		//Border
		WindowsSliderTrackCanvas->setBorder(SliderTrackDrawObjectBorder);
		WindowsSliderTrackCanvas->setRolloverBorder(SliderTrackDrawObjectBorder);
		WindowsSliderTrackCanvas->setFocusedBorder(SliderTrackDrawObjectBorder);
		WindowsSliderTrackCanvas->setDisabledBorder(SliderTrackDrawObjectBorder);
		
		//Background
		WindowsSliderTrackCanvas->setBackground(SliderTrackDrawObjectBackground);
		WindowsSliderTrackCanvas->setRolloverBackground(SliderTrackDrawObjectBackground);
		WindowsSliderTrackCanvas->setFocusedBackground(SliderTrackDrawObjectBackground);
		WindowsSliderTrackCanvas->setDisabledBackground(SliderTrackDrawObjectBackground);
	endEditCP(WindowsSliderTrackCanvas);

	//Slider Major Tick Marks
    RectUIDrawObjectPtr WindowsSliderMajorTickMarks = RectUIDrawObject::create();
	beginEditCP(WindowsSliderMajorTickMarks);
       WindowsSliderMajorTickMarks->setTopLeft(Pnt2f(0,0));
       WindowsSliderMajorTickMarks->setBottomRight(Pnt2f(7,1));
       WindowsSliderMajorTickMarks->setColor(Color4f(0.63,0.63,0.57,1.0));
	endEditCP(WindowsSliderMajorTickMarks);
	
	//Slider Minor Tick Marks
    RectUIDrawObjectPtr WindowsSliderMinorTickMarks = RectUIDrawObject::create();
	beginEditCP(WindowsSliderMinorTickMarks);
       WindowsSliderMinorTickMarks->setTopLeft(Pnt2f(0,0));
       WindowsSliderMinorTickMarks->setBottomRight(Pnt2f(4,1));
       WindowsSliderMinorTickMarks->setColor(Color4f(0.63,0.63,0.57,1.0));
	endEditCP(WindowsSliderMinorTickMarks);


	//Slider
    beginEditCP(WindowsSlider);
		WindowsSlider->setConstraints(NullFC);
		//Sizes
		WindowsSlider->setMinSize(Vec2f(0,0));
		WindowsSlider->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsSlider->setPreferredSize(Vec2f(200,27));

		//Border
		WindowsSlider->setBorder(WindowsSliderBorder);
		WindowsSlider->setRolloverBorder(WindowsSliderBorder);
		WindowsSlider->setFocusedBorder(WindowsSliderBorder);
		WindowsSlider->setDisabledBorder(WindowsSliderBorder);
		
		//Background
		WindowsSlider->setBackground(SliderBackground);
		WindowsSlider->setRolloverBackground(SliderBackground);
		WindowsSlider->setFocusedBackground(SliderBackground);
		WindowsSlider->setDisabledBackground(SliderBackground);
		
		//Opacity
		WindowsSlider->setOpacity(1.0);

        //Slider
        WindowsSlider->setOrientation(Slider::VERTICAL_ORIENTATION);
        WindowsSlider->setKnobButton(WindowsSliderKnobButton);
        WindowsSlider->setMajorTickSpacing(25);
        WindowsSlider->setMinorTickSpacing(5);
        WindowsSlider->setSnapToTicks(false);
        WindowsSlider->setDrawMajorTicks(true);
        WindowsSlider->setDrawMinorTicks(true);
        WindowsSlider->setDrawTrack(true);
        WindowsSlider->setDrawLabels(true);
        WindowsSlider->setInverted(false);
        WindowsSlider->setLabelPrototype(WindowsSliderPrototypeLabel);
        WindowsSlider->setTrackDrawObject(WindowsSliderTrackCanvas);
        WindowsSlider->setMinTrackDrawObject(NullFC);
        WindowsSlider->setMaxTrackDrawObject(NullFC);
        WindowsSlider->setTrackInset(8);
        WindowsSlider->setTrackToTickOffset(8);
        WindowsSlider->setTrackToLabelOffset(18);

        WindowsSlider->getMajorTickDrawObjects().clear();
        WindowsSlider->getMajorTickDrawObjects().push_back(WindowsSliderMajorTickMarks);
        WindowsSlider->getMinorTickDrawObjects().clear();
        WindowsSlider->getMinorTickDrawObjects().push_back(WindowsSliderMinorTickMarks);
    endEditCP(WindowsSlider);
	
	//************************** ComboBox *****************************

    //Expand Button
	ToggleButtonPtr WindowsComboBoxExpandButton = ToggleButton::create();
    beginEditCP(WindowsComboBoxExpandButton);
        WindowsComboBoxExpandButton->setPreferredSize(Vec2f(17,17));
        
        WindowsComboBoxExpandButton->setDrawObject(WindowsScrollBarVerticalMaxButtonCanvas);
        WindowsComboBoxExpandButton->setActiveDrawObject(WindowsScrollBarVerticalMaxButtonCanvas);
        WindowsComboBoxExpandButton->setFocusedDrawObject(WindowsScrollBarVerticalMaxButtonCanvas);
        WindowsComboBoxExpandButton->setRolloverDrawObject(WindowsScrollBarVerticalMaxButtonCanvas);
        WindowsComboBoxExpandButton->setDisabledDrawObject(WindowsScrollBarVerticalMaxButtonCanvas);
        
        WindowsComboBoxExpandButton->setBorder(WindowsScrollBarButtonBorder);
        WindowsComboBoxExpandButton->setActiveBorder(WindowsScrollBarButtonBorder);
        WindowsComboBoxExpandButton->setDisabledBorder(WindowsScrollBarDisabledButtonBorder);
        WindowsComboBoxExpandButton->setFocusedBorder(WindowsScrollBarButtonBorder);
        WindowsComboBoxExpandButton->setRolloverBorder(WindowsScrollBarButtonBorder);
        
        WindowsComboBoxExpandButton->setBackground(WindowsScrollBarButtonBackground);
        WindowsComboBoxExpandButton->setActiveBackground(WindowsScrollBarActiveButtonBackground);
        WindowsComboBoxExpandButton->setDisabledBackground(WindowsScrollBarDisabledButtonBackground);
        WindowsComboBoxExpandButton->setFocusedBackground(WindowsScrollBarButtonBackground);
        WindowsComboBoxExpandButton->setRolloverBackground(WindowsScrollBarRolloverButtonBackground);

        WindowsComboBoxExpandButton->setActiveOffset(Vec2f(0,0));
    endEditCP(WindowsComboBoxExpandButton);

	//Windows ComboBoxBorder
	EtchedBorderPtr WindowsComboBoxBorder = EtchedBorder::create();
	beginEditCP(WindowsComboBoxBorder);
		WindowsComboBoxBorder->setWidth(2);
		WindowsComboBoxBorder->setRaised(true);
		WindowsComboBoxBorder->setHighlight(Color4f(1.0, 1.0, 1.0, 1.0));
		WindowsComboBoxBorder->setShadow(Color4f(0.65, 0.65, 0.65, 1.0));
	endEditCP(WindowsComboBoxBorder);
	
	//Windows ComboBoxBackground
	ColorUIBackgroundPtr WindowsComboBoxBackground = ColorUIBackground::create();
	beginEditCP(WindowsComboBoxBackground);
		WindowsComboBoxBackground->setColor(Color4f(0.93, 0.91, 0.85, 1.0));
	endEditCP(WindowsComboBoxBackground);

	//Default ComboBoxEditor
	//Windows Default ComboBoxEditor TextField
	TextFieldPtr WindowsDefaultComboBoxTextField = TextField::create();
    beginEditCP(WindowsDefaultComboBoxTextField);
        WindowsDefaultComboBoxTextField->setHorizontalAlignment(0.0);
        
		//Border
		WindowsDefaultComboBoxTextField->setBorder(WindowsEmptyBorder);
		WindowsDefaultComboBoxTextField->setRolloverBorder(WindowsEmptyBorder);
		WindowsDefaultComboBoxTextField->setFocusedBorder(WindowsEmptyBorder);
		WindowsDefaultComboBoxTextField->setDisabledBorder(WindowsEmptyBorder);
		
		//Background
		WindowsDefaultComboBoxTextField->setBackground(WindowsEmptyBackground);
		WindowsDefaultComboBoxTextField->setRolloverBackground(WindowsEmptyBackground);
		WindowsDefaultComboBoxTextField->setFocusedBackground(WindowsEmptyBackground);
		WindowsDefaultComboBoxTextField->setDisabledBackground(WindowsEmptyBackground);
    endEditCP(WindowsDefaultComboBoxTextField);

    DefaultComboBoxEditorPtr WindowsDefaultComboBoxEditor = DefaultComboBoxEditor::create();
    beginEditCP(WindowsDefaultComboBoxEditor);
		WindowsDefaultComboBoxEditor->setEditor(WindowsDefaultComboBoxTextField);
    endEditCP(WindowsDefaultComboBoxEditor);
	
	//************************** DefaultComboBoxComponentGenerator *****************************
	LabelPtr WindowsDefaultComboBoxComponentGeneratorComponentPrototype = Label::create();
	beginEditCP(WindowsDefaultComboBoxComponentGeneratorComponentPrototype, Label::BordersFieldMask | Label::BackgroundsFieldMask);
		WindowsDefaultComboBoxComponentGeneratorComponentPrototype->setBorders(WindowsEmptyBorder);
		WindowsDefaultComboBoxComponentGeneratorComponentPrototype->setBackgrounds(WindowsEmptyBackground);
	endEditCP(WindowsDefaultComboBoxComponentGeneratorComponentPrototype, Label::BordersFieldMask | Label::BackgroundsFieldMask);

    ColorUIBackgroundPtr WindowsDefaultComboBoxComponentGeneratorSelectedBackground = ColorUIBackground::create();
	beginEditCP(WindowsDefaultComboBoxComponentGeneratorSelectedBackground, ColorUIBackground::ColorFieldMask);
		WindowsDefaultComboBoxComponentGeneratorSelectedBackground->setColor(Color4f(0.4f,0.4f,1.0f,1.0f));
	endEditCP(WindowsDefaultComboBoxComponentGeneratorSelectedBackground, ColorUIBackground::ColorFieldMask);

    UIBackgroundPtr WindowsDefaultComboBoxComponentGeneratorFocusedBackground = WindowsDefaultComboBoxComponentGeneratorComponentPrototype->getBackground();

    BorderPtr WindowsDefaultComboBoxComponentGeneratorSelectedBorder = WindowsDefaultComboBoxComponentGeneratorComponentPrototype->getBorder();

    BorderPtr WindowsDefaultComboBoxComponentGeneratorFocusedBorder = WindowsDefaultComboBoxComponentGeneratorComponentPrototype->getBorder();
    
	//DefaultComboBoxComponentGenerator
    beginEditCP(WindowsDefaultComboBoxComponentGenerator);
		WindowsDefaultComboBoxComponentGenerator->setDrawObjectPrototype(WindowsDefaultComboBoxComponentGeneratorComponentPrototype);
		WindowsDefaultComboBoxComponentGenerator->setSelectedBackground(WindowsDefaultComboBoxComponentGeneratorSelectedBackground);
		WindowsDefaultComboBoxComponentGenerator->setFocusedBackground(WindowsDefaultComboBoxComponentGeneratorFocusedBackground);
		WindowsDefaultComboBoxComponentGenerator->setSelectedBorder(WindowsDefaultComboBoxComponentGeneratorSelectedBorder);
		WindowsDefaultComboBoxComponentGenerator->setFocusedBorder(WindowsDefaultComboBoxComponentGeneratorFocusedBorder);
		WindowsDefaultComboBoxComponentGenerator->setSelectedTextColor(Color4f(1.0f,1.0f,1.0f,1.0f));
		WindowsDefaultComboBoxComponentGenerator->setFocusedTextColor(Color4f(0.0f,0.0f,0.0f,1.0f));
		WindowsDefaultComboBoxComponentGenerator->setFocusedBackgroundHasPriority(false);
		WindowsDefaultComboBoxComponentGenerator->setFocusedBorderHasPriority(true);
		WindowsDefaultComboBoxComponentGenerator->setFocusedTextColorHasPriority(false);
    endEditCP(WindowsDefaultComboBoxComponentGenerator);

	//ComboBox
    beginEditCP(WindowsComboBox);
		WindowsComboBox->setConstraints(NullFC);
		//Sizes
		WindowsComboBox->setMinSize(Vec2f(0,0));
		WindowsComboBox->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsComboBox->setPreferredSize(Vec2f(75,23));

		//Border
		WindowsComboBox->setBorder(WindowsTextFieldBorder);
		WindowsComboBox->setRolloverBorder(WindowsTextFieldBorder);
		WindowsComboBox->setFocusedBorder(WindowsTextFieldBorder);
		WindowsComboBox->setDisabledBorder(WindowsTextFieldBorder);
		
		//Background
		WindowsComboBox->setBackground(WindowsTextFieldBackground);
		WindowsComboBox->setRolloverBackground(WindowsTextFieldBackground);
		WindowsComboBox->setFocusedBackground(WindowsTextFieldBackground);
		WindowsComboBox->setDisabledBackground(WindowsDisabledTextFieldBackground);
		
		//Opacity
		WindowsComboBox->setOpacity(1.0);

        //ComboBox
        WindowsComboBox->setExpandButton(WindowsComboBoxExpandButton);
        WindowsComboBox->setEditor(WindowsDefaultComboBoxEditor);
        WindowsComboBox->setEditable(true);
        WindowsComboBox->setMaxRowCount(5);
		WindowsComboBox->setCellGenerator(WindowsDefaultComboBoxComponentGenerator);
    endEditCP(WindowsComboBox);

	//************************** TableHeader *****************************
	//Windows RotatedComponentBorder
	EmptyBorderPtr WindowsTableHeaderBorder = EmptyBorder::create();

	//Windows RotatedComponentBackground
	EmptyUIBackgroundPtr WindowsTableHeaderBackground = EmptyUIBackground::create();
    
	//Windows RotatedComponent
	beginEditCP(WindowsTableHeader);
		WindowsTableHeader->setEnabled(true);
		WindowsTableHeader->setVisible(true);
		
		WindowsTableHeader->setConstraints(NullFC);
		//Sizes
		WindowsTableHeader->setMinSize(Vec2f(0,0));
		WindowsTableHeader->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsTableHeader->setPreferredSize(Vec2f(100,100));

		//Border
		WindowsTableHeader->setBorder(WindowsTableHeaderBorder);
		WindowsTableHeader->setRolloverBorder(WindowsTableHeaderBorder);
		WindowsTableHeader->setFocusedBorder(WindowsTableHeaderBorder);
		WindowsTableHeader->setDisabledBorder(WindowsTableHeaderBorder);
		
		//Background
		WindowsTableHeader->setBackground(WindowsTableHeaderBackground);
		WindowsTableHeader->setRolloverBackground(WindowsTableHeaderBackground);
		WindowsTableHeader->setFocusedBackground(WindowsTableHeaderBackground);
		WindowsTableHeader->setDisabledBackground(WindowsTableHeaderBackground);
		
		//Opacity
		WindowsTableHeader->setOpacity(1.0);

        //Table Values
		WindowsTableHeader->setTable(NullFC);
		WindowsTableHeader->setReorderingAllowed(true);
		WindowsTableHeader->setResizingAllowed(true);
		WindowsTableHeader->setDefaultMarginDrawObject(NullFC);
        WindowsTableHeader->setDefaultRenderer(TableCellRendererPtr(new DefaultTableHeaderCellRenderer()));
        WindowsTableHeader->setResizingCursorDriftAllowance(1);
		
	endEditCP(WindowsTableHeader);
    
	
	//************************** Table *****************************
	//Windows RotatedComponentBorder
	EmptyBorderPtr WindowsTableBorder = EmptyBorder::create();

	//Windows RotatedComponentBackground
	EmptyUIBackgroundPtr WindowsTableBackground = EmptyUIBackground::create();

	//Windows RotatedComponent
	beginEditCP(WindowsTable);
		WindowsTable->setEnabled(true);
		WindowsTable->setVisible(true);
		
		WindowsTable->setConstraints(NullFC);
		//Sizes
		WindowsTable->setMinSize(Vec2f(0,0));
		WindowsTable->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsTable->setPreferredSize(Vec2f(100,100));

		//Border
		WindowsTable->setBorder(WindowsTableBorder);
		WindowsTable->setRolloverBorder(WindowsTableBorder);
		WindowsTable->setFocusedBorder(WindowsTableBorder);
		WindowsTable->setDisabledBorder(WindowsTableBorder);
		
		//Background
		WindowsTable->setBackground(WindowsTableBackground);
		WindowsTable->setRolloverBackground(WindowsTableBackground);
		WindowsTable->setFocusedBackground(WindowsTableBackground);
		WindowsTable->setDisabledBackground(WindowsTableBackground);
		
		//Opacity
		WindowsTable->setOpacity(1.0);

        //Table Properties
        WindowsTable->setHeader(WindowsTableHeader);
        WindowsTable->setAutoCreateColumnsFromModel(true);
        WindowsTable->setAutoResizeMode(Table::AUTO_RESIZE_SUBSEQUENT_COLUMNS);
        WindowsTable->setRowHeight(50);
        WindowsTable->setRowMargin(1);
        WindowsTable->setRowSelectionAllowed(true);
        WindowsTable->setShowHorizontalLines(true);
        WindowsTable->setShowVerticalLines(true);
        WindowsTable->setGridColor(Color4f(0.0,0.0,0.0,1.0));

        WindowsTable->setDefaultRenderer(&SFGLenum::getClassType(), TableCellRendererPtr(new DefaultGLenumTableCellRenderer()));
        WindowsTable->setDefaultRenderer(&SFString::getClassType(), TableCellRendererPtr(new DefaultStringTableCellRenderer()));
        WindowsTable->setDefaultRenderer(&SFBool::getClassType(), TableCellRendererPtr(new DefaultBoolTableCellRenderer()));
        WindowsTable->setDefaultRenderer(&SFInt32::getClassType(), TableCellRendererPtr(new DefaultInt32TableCellRenderer()));
        WindowsTable->setDefaultRenderer(&SFUInt32::getClassType(), TableCellRendererPtr(new DefaultUInt32TableCellRenderer()));
        WindowsTable->setDefaultRenderer(&SFReal32::getClassType(), TableCellRendererPtr(new DefaultReal32TableCellRenderer()));
		
	endEditCP(WindowsTable);
    
	//************************** DefaultTreeEditor *****************************

	//DefaultTreeCellEditor
    beginEditCP(WindowsDefaultTreeCellEditor);
		WindowsDefaultTreeCellEditor->setClickCountToStart(3);
		WindowsDefaultTreeCellEditor->setDefaultEditor(WindowsTextField);
		WindowsDefaultTreeCellEditor->setDefaultStringEditor(WindowsTextField);
    endEditCP(WindowsDefaultTreeCellEditor);
    
	//************************** DefaultTreeComponentGenerator *****************************

    UIDrawObjectCanvasPtr WindowsExpandedDrawObject = UIDrawObjectCanvas::create();
    
    UIDrawObjectCanvasPtr WindowsNotExpandedDrawObjectPrototype = UIDrawObjectCanvas::create();
    
    UIDrawObjectCanvasPtr WindowsLeafDrawObjectPrototype = UIDrawObjectCanvas::create();
    
    UIDrawObjectCanvasPtr WindowsNonLeafDrawObjectPrototype = UIDrawObjectCanvas::create();
    
    UIDrawObjectCanvasPtr WindowsExpandedNonLeafDrawObjectPrototype = UIDrawObjectCanvas::create();

    LabelPtr WindowsDefaultTreeComponentGeneratorNodeLabelPrototype = Label::create();

    ColorUIBackgroundPtr WindowsDefaultTreeComponentGeneratorSelectedBackground = ColorUIBackground::create();

    ColorUIBackgroundPtr WindowsDefaultTreeComponentGeneratorNonSelectedBackground = ColorUIBackground::create();

    LineBorderPtr WindowsDefaultTreeComponentGeneratorSelectedBorder = LineBorder::create();

    PanelPtr WindowsDefaultTreeComponentGeneratorPanelPrototype = Panel::create();
    beginEditCP(WindowsDefaultTreeComponentGeneratorPanelPrototype);
		//Border
		WindowsDefaultTreeComponentGeneratorPanelPrototype->setBorder(WindowsEmptyBorder);
		WindowsDefaultTreeComponentGeneratorPanelPrototype->setRolloverBorder(WindowsEmptyBorder);
		WindowsDefaultTreeComponentGeneratorPanelPrototype->setFocusedBorder(WindowsEmptyBorder);
		WindowsDefaultTreeComponentGeneratorPanelPrototype->setDisabledBorder(WindowsEmptyBorder);
		
		//Background
		WindowsDefaultTreeComponentGeneratorPanelPrototype->setBackground(WindowsEmptyBackground);
		WindowsDefaultTreeComponentGeneratorPanelPrototype->setRolloverBackground(WindowsEmptyBackground);
		WindowsDefaultTreeComponentGeneratorPanelPrototype->setFocusedBackground(WindowsEmptyBackground);
		WindowsDefaultTreeComponentGeneratorPanelPrototype->setDisabledBackground(WindowsEmptyBackground);
    endEditCP(WindowsDefaultTreeComponentGeneratorPanelPrototype);
    


	//DefaultTreeComponentGenerator
    beginEditCP(WindowsDefaultTreeComponentGenerator);
		WindowsDefaultTreeComponentGenerator->setExpandedDrawObjectPrototype(WindowsExpandedDrawObject);
		WindowsDefaultTreeComponentGenerator->setNotExpandedDrawObjectPrototype(WindowsNotExpandedDrawObjectPrototype);
		WindowsDefaultTreeComponentGenerator->setLeafDrawObjectPrototype(WindowsLeafDrawObjectPrototype);
		WindowsDefaultTreeComponentGenerator->setNonLeafDrawObjectPrototype(WindowsNonLeafDrawObjectPrototype);
		WindowsDefaultTreeComponentGenerator->setExpandedNonLeafDrawObjectPrototype(WindowsExpandedNonLeafDrawObjectPrototype);
		WindowsDefaultTreeComponentGenerator->setNodeLabelPrototype(WindowsDefaultTreeComponentGeneratorNodeLabelPrototype);
		WindowsDefaultTreeComponentGenerator->setSelectedBackground(WindowsDefaultTreeComponentGeneratorSelectedBackground);
		WindowsDefaultTreeComponentGenerator->setNonSelectedBackground(WindowsDefaultTreeComponentGeneratorNonSelectedBackground);
		WindowsDefaultTreeComponentGenerator->setSelectedBorder(WindowsDefaultTreeComponentGeneratorSelectedBorder);
		WindowsDefaultTreeComponentGenerator->setSelectedTextColor(Color4f(1.0f,1.0f,1.0f,1.0f));
		WindowsDefaultTreeComponentGenerator->setNonSelectedTextColor(Color4f(0.0f,0.0f,0.0f,1.0f));
		WindowsDefaultTreeComponentGenerator->setNodePanelPrototype(WindowsDefaultTreeComponentGeneratorPanelPrototype);
    endEditCP(WindowsDefaultTreeComponentGenerator);

    //DefaultTreeLayout
    TreeModelLayoutPtr WindowsDefaultTreeModelLayout = FixedHeightTreeModelLayout::create();
    beginEditCP(WindowsDefaultTreeModelLayout);
		WindowsDefaultTreeModelLayout->setRootVisible(false);
        WindowsDefaultTreeModelLayout->setRowHeight(20);
    beginEditCP(WindowsDefaultTreeModelLayout);

	//************************** Tree *****************************
	//Windows RotatedComponentBorder
	LineBorderPtr WindowsTreeBorder = LineBorder::create();
	beginEditCP(WindowsTreeBorder);
		WindowsTreeBorder->setWidth(1);
		WindowsTreeBorder->setColor(Color4f(0.0, 0.0, 0.0, 1.0));
	endEditCP(WindowsTreeBorder);

	//Windows RotatedComponentBackground
	ColorUIBackgroundPtr WindowsTreeBackground = ColorUIBackground::create();
	beginEditCP(WindowsTreeBackground);
		WindowsTreeBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
	endEditCP(WindowsTreeBackground);

	//Windows WindowsTree
	beginEditCP(WindowsTree);
		WindowsTree->setEnabled(true);
		WindowsTree->setVisible(true);
		
		WindowsTree->setConstraints(NullFC);
		//Sizes
		WindowsTree->setMinSize(Vec2f(0,0));
		WindowsTree->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsTree->setPreferredSize(Vec2f(100,100));

		//Border
		WindowsTree->setBorder(WindowsTreeBorder);
		WindowsTree->setRolloverBorder(WindowsTreeBorder);
		WindowsTree->setFocusedBorder(WindowsTreeBorder);
		WindowsTree->setDisabledBorder(WindowsTreeBorder);
		
		//Background
		WindowsTree->setBackground(WindowsTreeBackground);
		WindowsTree->setRolloverBackground(WindowsTreeBackground);
		WindowsTree->setFocusedBackground(WindowsTreeBackground);
		WindowsTree->setDisabledBackground(WindowsTreeBackground);
		
		//Opacity
		WindowsTree->setOpacity(1.0);

        //Tree Values
		WindowsTree->setEditable(false);
		WindowsTree->setExpandsSelectedPaths(true);
		WindowsTree->setInvokesStopCellEditing(true);
		WindowsTree->setRowHeight(13);
		WindowsTree->setScrollsOnExpand(false);
		WindowsTree->setShowsRootHandles(true);
		WindowsTree->setToggleClickCount(2);
		WindowsTree->setVisibleRowCount(10);
		WindowsTree->setCellEditor(WindowsDefaultTreeCellEditor);
		WindowsTree->setCellGenerator(WindowsDefaultTreeComponentGenerator);
        WindowsTree->setModelLayout(WindowsDefaultTreeModelLayout);
		
	endEditCP(WindowsTree);
	
	
	//************************** RGBColorChooserPanel *****************************
	RGBColorChooserPanelPtr WindowsRGBColorChooserPanel = RGBColorChooserPanel::create();
	beginEditCP(WindowsRGBColorChooserPanel);
		WindowsRGBColorChooserPanel->setEnabled(true);
		WindowsRGBColorChooserPanel->setVisible(true);
		
		WindowsRGBColorChooserPanel->setConstraints(NullFC);

		//Sizes
		WindowsRGBColorChooserPanel->setMinSize(Vec2f(0,0));
		WindowsRGBColorChooserPanel->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsRGBColorChooserPanel->setPreferredSize(Vec2f(100,100));
		
		//Border
		WindowsRGBColorChooserPanel->setBorder(WindowsEmptyBorder);
		WindowsRGBColorChooserPanel->setRolloverBorder(WindowsEmptyBorder);
		WindowsRGBColorChooserPanel->setFocusedBorder(WindowsEmptyBorder);
		WindowsRGBColorChooserPanel->setDisabledBorder(WindowsEmptyBorder);
		
		//Background
		WindowsRGBColorChooserPanel->setBackground(WindowsEmptyBackground);
		WindowsRGBColorChooserPanel->setRolloverBackground(WindowsEmptyBackground);
		WindowsRGBColorChooserPanel->setFocusedBackground(WindowsEmptyBackground);
		WindowsRGBColorChooserPanel->setDisabledBackground(WindowsEmptyBackground);
		
		//Opacity
		WindowsRGBColorChooserPanel->setOpacity(1.0);

		WindowsRGBColorChooserPanel->setIncludeAlpha(true);
	endEditCP(WindowsRGBColorChooserPanel);

	//************************** HSVColorChooserPanel *****************************
	HSVColorChooserPanelPtr WindowsHSVColorChooserPanel = HSVColorChooserPanel::create();
	beginEditCP(WindowsHSVColorChooserPanel);
		WindowsHSVColorChooserPanel->setEnabled(true);
		WindowsHSVColorChooserPanel->setVisible(true);
		
		WindowsHSVColorChooserPanel->setConstraints(NullFC);

		//Sizes
		WindowsHSVColorChooserPanel->setMinSize(Vec2f(0,0));
		WindowsHSVColorChooserPanel->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsHSVColorChooserPanel->setPreferredSize(Vec2f(100,100));
		
		//Border
		WindowsHSVColorChooserPanel->setBorder(WindowsEmptyBorder);
		WindowsHSVColorChooserPanel->setRolloverBorder(WindowsEmptyBorder);
		WindowsHSVColorChooserPanel->setFocusedBorder(WindowsEmptyBorder);
		WindowsHSVColorChooserPanel->setDisabledBorder(WindowsEmptyBorder);
		
		//Background
		WindowsHSVColorChooserPanel->setBackground(WindowsEmptyBackground);
		WindowsHSVColorChooserPanel->setRolloverBackground(WindowsEmptyBackground);
		WindowsHSVColorChooserPanel->setFocusedBackground(WindowsEmptyBackground);
		WindowsHSVColorChooserPanel->setDisabledBackground(WindowsEmptyBackground);
		
		//Opacity
		WindowsHSVColorChooserPanel->setOpacity(1.0);

		WindowsHSVColorChooserPanel->setIncludeAlpha(true);
	endEditCP(WindowsHSVColorChooserPanel);

	//************************** ColorChooser *****************************

	//Windows WindowsColorChooser
	beginEditCP(WindowsColorChooser);
		WindowsColorChooser->setEnabled(true);
		WindowsColorChooser->setVisible(true);
		
		WindowsColorChooser->setConstraints(NullFC);
		//Sizes
		WindowsColorChooser->setMinSize(Vec2f(0,0));
		WindowsColorChooser->setMaxSize(Vec2f(32767,32767)); //2^15
		WindowsColorChooser->setPreferredSize(Vec2f(300,300));

		//Border
		WindowsColorChooser->setBorder(WindowsEmptyBorder);
		WindowsColorChooser->setRolloverBorder(WindowsEmptyBorder);
		WindowsColorChooser->setFocusedBorder(WindowsEmptyBorder);
		WindowsColorChooser->setDisabledBorder(WindowsEmptyBorder);
		
		//Background
		WindowsColorChooser->setBackground(WindowsEmptyBackground);
		WindowsColorChooser->setRolloverBackground(WindowsEmptyBackground);
		WindowsColorChooser->setFocusedBackground(WindowsEmptyBackground);
		WindowsColorChooser->setDisabledBackground(WindowsEmptyBackground);
		
		//Opacity
		WindowsColorChooser->setOpacity(1.0);

        //ColorChooser Values
		WindowsColorChooser->addChooserPanel(WindowsRGBColorChooserPanel);
		WindowsColorChooser->addChooserPanel(WindowsHSVColorChooserPanel);
		WindowsColorChooser->setPreviewPanel(NullFC);
	endEditCP(WindowsColorChooser);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

WindowsLookAndFeel::WindowsLookAndFeel(void) :
    Inherited()
{
}

WindowsLookAndFeel::WindowsLookAndFeel(const WindowsLookAndFeel &source) :
    Inherited(source)
{
}

WindowsLookAndFeel::~WindowsLookAndFeel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void WindowsLookAndFeel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void WindowsLookAndFeel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump WindowsLookAndFeel NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGWINDOWSLOOKANDFEELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGWINDOWSLOOKANDFEELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGWINDOWSLOOKANDFEELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

