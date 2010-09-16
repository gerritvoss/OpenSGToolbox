/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#include "OSGWindowsLookAndFeel.h"
#include "OSGUIFont.h"
#include "OSGBorders.h"
#include "OSGLayers.h"
#include "OSGButton.h"
#include "OSGCheckboxButton.h"
#include "OSGRadioButton.h"
#include "OSGToggleButton.h"
#include "OSGMenuButton.h"
#include "OSGLabel.h"
#include "OSGInternalWindow.h"
#include "OSGDialogWindow.h"
#include "OSGTitlebar.h"
#include "OSGPanel.h"
#include "OSGSplitPanel.h"
#include "OSGTabPanel.h"
#include "OSGImageComponent.h"
#include "OSGRectUIDrawObject.h"
#include "OSGMultiColoredQuadUIDrawObject.h"
#include "OSGArcUIDrawObject.h"
#include "OSGDiscUIDrawObject.h"
#include "OSGLineUIDrawObject.h"
#include "OSGPolygonUIDrawObject.h"
#include "OSGUIDrawObjectCanvas.h"
#include "OSGTextField.h"
#include "OSGPasswordField.h"
#include "OSGTextArea.h"
#include "OSGToolTip.h"
#include "OSGSeparator.h"

#include "OSGMenuItem.h"
#include "OSGComponentMenuItem.h"
#include "OSGMenu.h"
#include "OSGPopupMenu.h"
#include "OSGListGeneratedPopupMenu.h"
#include "OSGMenuBar.h"
#include "OSGDefaultSingleSelectionModel.h"

#include "OSGRotatedComponent.h"

#include "OSGScrollBar.h"
#include "OSGScrollPanel.h"
#include "OSGUIViewport.h"

#include "OSGTableHeader.h"
#include "OSGTable.h"
#include "OSGDefaultTableCellRenderers.h"
#include "OSGDefaultTableColumnModel.h"

#include "OSGList.h"
#include "OSGDefaultListSelectionModel.h"
#include "OSGDefaultListComponentGenerator.h"

#include "OSGSpinner.h"
#include "OSGSpinnerDefaultEditor.h"
#include "OSGSpinnerNumberEditor.h"

#include "OSGProgressBar.h"

#include "OSGSlider.h"

#include "OSGComboBox.h"
#include "OSGDefaultComboBoxEditor.h"
#include "OSGDefaultComboBoxComponentGenerator.h"

#include "OSGFixedHeightTreeModelLayout.h"
#include "OSGDefaultTreeCellEditor.h"
#include "OSGDefaultTreeComponentGenerator.h"
#include "OSGTree.h"

#include "OSGColorChooser.h"
#include "OSGRGBColorChooserPanel.h"
#include "OSGHSVColorChooserPanel.h"

//#include "OSGToolbar.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGWindowsLookAndFeelBase.cpp file.
// To modify it, please change the .fcd file (OSGWindowsLookAndFeel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void WindowsLookAndFeel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void WindowsLookAndFeel::init(void)
{
    ButtonRefPtr WindowsButton = Button::createEmpty();
    LabelRefPtr WindowsLabel = Label::createEmpty();
    InternalWindowRefPtr WindowsInternalWindow = InternalWindow::createEmpty();
    DialogWindowRefPtr WindowsDialogWindow = DialogWindow::createEmpty();
    PanelRefPtr WindowsPanel = Panel::createEmpty();
    //ToolbarRefPtr WindowsToolbar = Toolbar::createEmpty();
    SplitPanelRefPtr WindowsSplitPanel = SplitPanel::createEmpty();
    TabPanelRefPtr WindowsTabPanel = TabPanel::createEmpty();
    ImageComponentRefPtr WindowsImageComponent = ImageComponent::createEmpty();
    CheckboxButtonRefPtr WindowsCheckboxButton = CheckboxButton::createEmpty();
    RadioButtonRefPtr WindowsRadioButton = RadioButton::createEmpty();
    ToggleButtonRefPtr WindowsToggleButton = ToggleButton::createEmpty();
    TextFieldRefPtr WindowsTextField = TextField::createEmpty();
    PasswordFieldRefPtr WindowsPasswordField = PasswordField::createEmpty();
    TextAreaRefPtr WindowsTextArea = TextArea::createEmpty();
    ToolTipRefPtr WindowsToolTip = ToolTip::createEmpty();
    ScrollBarRefPtr WindowsScrollBar = ScrollBar::createEmpty();
    ScrollPanelRefPtr WindowsScrollPanel = ScrollPanel::createEmpty();
    UIViewportRefPtr WindowsUIViewport = UIViewport::createEmpty();
    RotatedComponentRefPtr WindowsRotatedComponent = RotatedComponent::createEmpty();
    DefaultListComponentGeneratorRefPtr WindowsDefaultListComponentGenerator = DefaultListComponentGenerator::createEmpty();
    ListRefPtr WindowsList = List::createEmpty();
    SpinnerRefPtr WindowsSpinner = Spinner::createEmpty();
    SpinnerDefaultEditorRefPtr WindowsSpinnerDefaultEditor = SpinnerDefaultEditor::createEmpty();
    SpinnerNumberEditorRefPtr WindowsSpinnerNumberEditor = SpinnerNumberEditor::createEmpty();
    SeparatorRefPtr WindowsSeparator = Separator::createEmpty();
    ProgressBarRefPtr WindowsProgressBar = ProgressBar::createEmpty();
    SliderRefPtr WindowsSlider = Slider::createEmpty();
    DefaultComboBoxComponentGeneratorRefPtr WindowsDefaultComboBoxComponentGenerator = DefaultComboBoxComponentGenerator::createEmpty();
    ComboBoxRefPtr WindowsComboBox = ComboBox::createEmpty();
    TableHeaderRefPtr WindowsTableHeader = TableHeader::createEmpty();
    TableRefPtr WindowsTable = Table::createEmpty();
    DefaultTreeCellEditorRefPtr WindowsDefaultTreeCellEditor = DefaultTreeCellEditor::createEmpty();
    DefaultTreeComponentGeneratorRefPtr WindowsDefaultTreeComponentGenerator = DefaultTreeComponentGenerator::createEmpty();
    TreeRefPtr WindowsTree = Tree::createEmpty();
    ColorChooserRefPtr WindowsColorChooser = ColorChooser::createEmpty();
    MenuItemRefPtr WindowsMenuItem = MenuItem::createEmpty();
    ComponentMenuItemRefPtr WindowsComponentMenuItem = ComponentMenuItem::createEmpty();
    PopupMenuRefPtr WindowsPopupMenu = PopupMenu::createEmpty();
    MenuRefPtr WindowsMenu = Menu::createEmpty();
    MenuBarRefPtr WindowsMenuBar = MenuBar::createEmpty();
    MenuButtonRefPtr WindowsMenuButton = MenuButton::createEmpty();
    ListGeneratedPopupMenuRefPtr WindowsListGeneratedPopupMenu = ListGeneratedPopupMenu::createEmpty();

    pushToPrototypes(WindowsButton);
    pushToPrototypes(WindowsMenuButton);
    pushToPrototypes(WindowsLabel);
    pushToPrototypes(WindowsInternalWindow);
    pushToPrototypes(WindowsDialogWindow);
    pushToPrototypes(WindowsPanel);
    //pushToPrototypes(WindowsToolbar);
    pushToPrototypes(WindowsSplitPanel);
    pushToPrototypes(WindowsTabPanel);
    pushToPrototypes(WindowsImageComponent);
    pushToPrototypes(WindowsCheckboxButton);
    pushToPrototypes(WindowsRadioButton);
    pushToPrototypes(WindowsToggleButton);
    pushToPrototypes(WindowsTextField);
    pushToPrototypes(WindowsPasswordField);
    pushToPrototypes(WindowsTextArea);
    pushToPrototypes(WindowsToolTip);
    pushToPrototypes(WindowsMenuItem);
    pushToPrototypes(WindowsComponentMenuItem);
    pushToPrototypes(WindowsMenu);
    pushToPrototypes(WindowsPopupMenu);
    pushToPrototypes(WindowsListGeneratedPopupMenu);
    pushToPrototypes(WindowsMenuBar);
    pushToPrototypes(WindowsScrollBar);
    pushToPrototypes(WindowsScrollPanel);
    pushToPrototypes(WindowsUIViewport);
    pushToPrototypes(WindowsRotatedComponent);
    pushToPrototypes(WindowsDefaultListComponentGenerator);
    pushToPrototypes(WindowsList);
    pushToPrototypes(WindowsSpinner);
    pushToPrototypes(WindowsSpinnerDefaultEditor);
    pushToPrototypes(WindowsSpinnerNumberEditor);
    pushToPrototypes(WindowsSeparator);
    pushToPrototypes(WindowsProgressBar);
    pushToPrototypes(WindowsSlider);
    pushToPrototypes(WindowsDefaultComboBoxComponentGenerator);
    pushToPrototypes(WindowsComboBox);
    pushToPrototypes(WindowsTableHeader);
    pushToPrototypes(WindowsTable);
    pushToPrototypes(WindowsDefaultTreeCellEditor);
    pushToPrototypes(WindowsDefaultTreeComponentGenerator);
    pushToPrototypes(WindowsTree);
    pushToPrototypes(WindowsColorChooser);

    initPrototypes();
    
    commitChanges();

    setTextCaretRate(1.0);
    setToolTipPopupTime(1.5);
    setToolTipPopupTime(0.25);
    setKeyAcceleratorMenuFlashTime(0.15);

    Color4f WindowsXPMainColor(1.0,1.0,1.0,1.0);

    /********Empty Border*********/
    EmptyBorderRefPtr WindowsEmptyBorder = EmptyBorder::create();
    WindowsEmptyBorder->setTopWidth(0);
    WindowsEmptyBorder->setBottomWidth(0);
    WindowsEmptyBorder->setRightWidth(0);
    WindowsEmptyBorder->setLeftWidth(0);

    /*********Empty Background**********/
    EmptyLayerRefPtr WindowsEmptyBackground = EmptyLayer::create();

    //Windows Font
    UIFontRefPtr WindowsFont = UIFont::create();
    WindowsFont->setFamily("Tahoma");
    WindowsFont->setGap(3);
    WindowsFont->setGlyphPixelSize(46);
    WindowsFont->setSize(14);
    WindowsFont->setTextureWidth(0);
    WindowsFont->setStyle(TextFace::STYLE_PLAIN);

    Color4f WindowsDisabledTextColor(0.63,0.63,0.57,1.0);

    //Windows ButtonBorder
    RoundedCornerLineBorderRefPtr WindowsButtonBorder = RoundedCornerLineBorder::create();
    WindowsButtonBorder->setColor( Color4f(0.0, 0.235, 0.455 ,1.0) );
    WindowsButtonBorder->setWidth(1);
    WindowsButtonBorder->setCornerRadius(3);

    //Windows Active button border
    RoundedCornerLineBorderRefPtr WindowsActiveButtonBorder = RoundedCornerLineBorder::create();
    WindowsActiveButtonBorder->setColor( Color4f(0.0, 0.235, 0.455 ,1.0) );
    WindowsActiveButtonBorder->setWidth(1);
    WindowsActiveButtonBorder->setCornerRadius(3);


    //Windows Rollover button border
    RoundedCornerLineBorderRefPtr WindowsRolloverInsideButtonBorder = RoundedCornerLineBorder::create();
    WindowsRolloverInsideButtonBorder->setColor( Color4f(0.98, 0.79, 0.42 ,1.0) );
    WindowsRolloverInsideButtonBorder->setWidth(2);
    WindowsRolloverInsideButtonBorder->setCornerRadius(1);

    CompoundBorderRefPtr WindowsRolloverButtonBorder = CompoundBorder::create();
    WindowsRolloverButtonBorder->setInnerBorder(WindowsRolloverInsideButtonBorder);
    WindowsRolloverButtonBorder->setOuterBorder(WindowsButtonBorder);

    //Windows Disabled button border
    RoundedCornerLineBorderRefPtr WindowsDisabledInsideButtonBorder = RoundedCornerLineBorder::create();
    WindowsDisabledInsideButtonBorder->setColor( Color4f(0.79, 0.78, 0.73 ,1.0) );
    WindowsDisabledInsideButtonBorder->setWidth(1);
    WindowsDisabledInsideButtonBorder->setCornerRadius(3);
    RoundedCornerLineBorderRefPtr WindowsDisabledOutsideButtonBorder = RoundedCornerLineBorder::create();
    WindowsDisabledOutsideButtonBorder->setColor( Color4f(0.93, 0.91, 0.85 ,1.0) );
    WindowsDisabledOutsideButtonBorder->setWidth(1);
    WindowsDisabledOutsideButtonBorder->setCornerRadius(1);

    CompoundBorderRefPtr WindowsDisabledButtonBorder = CompoundBorder::create();
    WindowsDisabledButtonBorder->setInnerBorder(WindowsDisabledInsideButtonBorder);
    WindowsDisabledButtonBorder->setOuterBorder(WindowsDisabledOutsideButtonBorder);

    //Windows ButtonBackground
    GradientLayerRefPtr WindowsButtonBackground = GradientLayer::create();
    WindowsButtonBackground->editMFColors()->push_back(Color4f(.988, .988, .984, 1.0));
    WindowsButtonBackground->editMFStops()->push_back(0.0);
    WindowsButtonBackground->editMFColors()->push_back(Color4f(.941, .941, .918, 1.0));
    WindowsButtonBackground->editMFStops()->push_back(1.0);
    WindowsButtonBackground->setStartPosition(Vec2f(0.0f,0.0f));
    WindowsButtonBackground->setEndPosition(Vec2f(0.0f,1.0f));

    //Windows Disabled ButtonBackground
    ColorLayerRefPtr WindowsDisabledButtonBackground = ColorLayer::create();
    WindowsDisabledButtonBackground->setColor(Color4f(0.93,0.93,0.93,1.0));

    //Windows Active ButtonBackground
    GradientLayerRefPtr WindowsActiveButtonBackground = GradientLayer::create();
    WindowsActiveButtonBackground->editMFColors()->push_back(Color4f(.90, .89, .87, 1.0));
    WindowsActiveButtonBackground->editMFStops()->push_back(0.0);
    WindowsActiveButtonBackground->editMFColors()->push_back(Color4f(.89, .89, .85, 1.0));
    WindowsActiveButtonBackground->editMFStops()->push_back(1.0);
    WindowsActiveButtonBackground->setStartPosition(Vec2f(0.0f,0.0f));
    WindowsActiveButtonBackground->setEndPosition(Vec2f(0.0f,1.0f));

    //Windows Rollover ButtonBackground
    GradientLayerRefPtr WindowsRolloverButtonBackground = GradientLayer::create();
    WindowsRolloverButtonBackground->editMFColors()->push_back(Color4f(.99, .99, .98, 1.0));
    WindowsRolloverButtonBackground->editMFStops()->push_back(0.0);
    WindowsRolloverButtonBackground->editMFColors()->push_back(Color4f(.93, .92, .90, 1.0));
    WindowsRolloverButtonBackground->editMFStops()->push_back(1.0);
    WindowsRolloverButtonBackground->setStartPosition(Vec2f(0.0f,0.0f));
    WindowsRolloverButtonBackground->setEndPosition(Vec2f(0.0f,1.0f));

    //Windows Button
    WindowsButton->setEnabled(true);
    WindowsButton->setVisible(true);

    WindowsButton->setConstraints(NULL);
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
    WindowsButton->setAlignment(Vec2f(0.5f,0.5f));
    WindowsButton->setTextColor(Color4f(0.0,0.0,0.0,1.0));
    WindowsButton->setActiveTextColor(Color4f(0.0,0.0,0.0,1.0));
    WindowsButton->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
    WindowsButton->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
    WindowsButton->setDisabledTextColor(WindowsDisabledTextColor);

    WindowsButton->setActiveOffset(Vec2f(2,2));
    WindowsButton->setDrawObjectToTextAlignment(Button::ALIGN_DRAW_OBJECT_LEFT_OF_TEXT);
    WindowsButton->setDrawObjectToTextPadding(4.0f);

    //************************** Label*****************************
    //Windows LabelBackground
    ColorLayerRefPtr WindowsLabelBackground = ColorLayer::create();
    WindowsLabelBackground->setColor(Color4f(0.9569,0.9529,0.9373,1.0));

    //Windows Label
    WindowsLabel->setEnabled(true);
    WindowsLabel->setVisible(true);

    WindowsLabel->setConstraints(NULL);
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

    WindowsLabel->setAlignment(Vec2f(0.0f,0.5f));
    WindowsLabel->setTextSelectable(false);

    //************************** InternalWindow *****************************
    //Windows InternalWindow 
    //Inside FocusedBorder
    BevelBorderRefPtr WindowsInsideInternalWindowFocusedBorder = BevelBorder::create();
    WindowsInsideInternalWindowFocusedBorder->setRaised(true);
    WindowsInsideInternalWindowFocusedBorder->setWidth(2);
    WindowsInsideInternalWindowFocusedBorder->setHighlightInner(Color4f(0.4, 0.4, 0.49, 1.0));
    WindowsInsideInternalWindowFocusedBorder->setHighlightOuter(Color4f(0.89, 0.89, 0.89, 1.0));
    WindowsInsideInternalWindowFocusedBorder->setShadowInner(Color4f(0.4, 0.4, 0.49, 1.0));
    WindowsInsideInternalWindowFocusedBorder->setShadowOuter(Color4f(0.89, 0.89, 0.89, 1.0));

    //Outside FocusedBorder
    BevelBorderRefPtr WindowsOutsideInternalWindowFocusedBorder = BevelBorder::create();
    WindowsOutsideInternalWindowFocusedBorder->setRaised(true);
    WindowsOutsideInternalWindowFocusedBorder->setWidth(2);
    WindowsOutsideInternalWindowFocusedBorder->setHighlightOuter(Color4f(0.4, 0.4, 0.49, 1.0));
    WindowsOutsideInternalWindowFocusedBorder->setHighlightInner(Color4f(0.89, 0.89, 0.89, 1.0));
    WindowsOutsideInternalWindowFocusedBorder->setShadowOuter(Color4f(0.4, 0.4, 0.49, 1.0));
    WindowsOutsideInternalWindowFocusedBorder->setShadowInner(Color4f(0.89, 0.89, 0.89, 1.0));

    //FocusedBorder
    WindowBorderRefPtr WindowsInternalWindowFocusedBorder = WindowBorder::create();
    WindowsInternalWindowFocusedBorder->setInnerBorder(WindowsInsideInternalWindowFocusedBorder);
    WindowsInternalWindowFocusedBorder->setOuterBorder(WindowsOutsideInternalWindowFocusedBorder);

    //Inside UnfocusedBorder
    BevelBorderRefPtr WindowsInsideInternalWindowUnfocusedBorder = BevelBorder::create();
    WindowsInsideInternalWindowUnfocusedBorder->setRaised(true);
    WindowsInsideInternalWindowUnfocusedBorder->setWidth(2);
    WindowsInsideInternalWindowUnfocusedBorder->setHighlightInner(Color4f(0.80, 0.80, 0.85, 1.0));
    WindowsInsideInternalWindowUnfocusedBorder->setHighlightOuter(Color4f(0.99, 1.0, 0.99, 1.0));
    WindowsInsideInternalWindowUnfocusedBorder->setShadowInner(Color4f(0.80, 0.80, 0.85, 1.0));
    WindowsInsideInternalWindowUnfocusedBorder->setShadowOuter(Color4f(0.99, 1.0, 0.99, 1.0));

    //Outside UnfocusedBorder
    BevelBorderRefPtr WindowsOutsideInternalWindowUnfocusedBorder = BevelBorder::create();
    WindowsOutsideInternalWindowUnfocusedBorder->setRaised(true);
    WindowsOutsideInternalWindowUnfocusedBorder->setWidth(2);
    WindowsOutsideInternalWindowUnfocusedBorder->setHighlightOuter(Color4f(0.80, 0.80, 0.85, 1.0));
    WindowsOutsideInternalWindowUnfocusedBorder->setHighlightInner(Color4f(0.99, 1.0, 0.99, 1.0));
    WindowsOutsideInternalWindowUnfocusedBorder->setShadowOuter(Color4f(0.80, 0.80, 0.85, 1.0));
    WindowsOutsideInternalWindowUnfocusedBorder->setShadowInner(Color4f(0.99, 1.0, 0.99, 1.0));

    //UnfocusedBorder
    WindowBorderRefPtr WindowsInternalWindowUnfocusedBorder = WindowBorder::create();
    WindowsInternalWindowUnfocusedBorder->setInnerBorder(WindowsInsideInternalWindowUnfocusedBorder);
    WindowsInternalWindowUnfocusedBorder->setOuterBorder(WindowsOutsideInternalWindowUnfocusedBorder);

    //InternalWindow Background
    ColorLayerRefPtr WindowsInternalWindowBackground = ColorLayer::create();
    WindowsInternalWindowBackground->setColor( Color4f(0.9569,0.9529,0.9373,1.0) );

    //Decoration Buttons
    //Windows IconifyMaximizeButtonBorder
    RoundedCornerLineBorderRefPtr WindowsIconifyMaximizeButtonBorder = RoundedCornerLineBorder::create();
    WindowsIconifyMaximizeButtonBorder->setColor( Color4f(0.42, 0.46, 0.56 ,1.0) );
    WindowsIconifyMaximizeButtonBorder->setWidth(1);
    WindowsIconifyMaximizeButtonBorder->setCornerRadius(3);

    //Windows ActiveIconifyMaximizeButtonBorder
    RoundedCornerLineBorderRefPtr ActiveWindowsIconifyMaximizeButtonBorder = RoundedCornerLineBorder::create();
    ActiveWindowsIconifyMaximizeButtonBorder->setColor( Color4f(0.31, 0.35, 0.44 ,1.0) );
    ActiveWindowsIconifyMaximizeButtonBorder->setWidth(1);
    ActiveWindowsIconifyMaximizeButtonBorder->setCornerRadius(3);

    //Windows DisabledIconifyMaximizeButtonBorder
    RoundedCornerLineBorderRefPtr DisabledWindowsIconifyMaximizeButtonBorder = RoundedCornerLineBorder::create();
    DisabledWindowsIconifyMaximizeButtonBorder->setColor( Color4f(0.66, 0.68, 0.73 ,1.0) );
    DisabledWindowsIconifyMaximizeButtonBorder->setWidth(1);
    DisabledWindowsIconifyMaximizeButtonBorder->setCornerRadius(3);

    //Windows  IconifyMaximizeButtonBackground
    GradientLayerRefPtr WindowsIconifyMaximizeButtonBackground = GradientLayer::create();
    WindowsIconifyMaximizeButtonBackground->editMFColors()->push_back(Color4f(1.0, 1.0, 1.0, 1.0));
    WindowsIconifyMaximizeButtonBackground->editMFStops()->push_back(0.0);
    WindowsIconifyMaximizeButtonBackground->editMFColors()->push_back(Color4f(0.52, 0.54, 0.69, 1.0));
    WindowsIconifyMaximizeButtonBackground->editMFStops()->push_back(0.0);
    WindowsIconifyMaximizeButtonBackground->setStartPosition(Vec2f(0.0f,0.0f));
    WindowsIconifyMaximizeButtonBackground->setEndPosition(Vec2f(0.0f,1.0f));

    //Windows  ActiveIconifyMaximizeButtonBackground
    GradientLayerRefPtr ActiveWindowsIconifyMaximizeButtonBackground = GradientLayer::create();
    ActiveWindowsIconifyMaximizeButtonBackground->editMFColors()->push_back(Color4f(0.55, 0.56, 0.68, 1.0));
    ActiveWindowsIconifyMaximizeButtonBackground->editMFStops()->push_back(0.0);
    ActiveWindowsIconifyMaximizeButtonBackground->editMFColors()->push_back(Color4f(1.0, 0.98, 1.0, 1.0));
    ActiveWindowsIconifyMaximizeButtonBackground->editMFStops()->push_back(1.0);
    ActiveWindowsIconifyMaximizeButtonBackground->setStartPosition(Vec2f(0.0f,0.0f));
    ActiveWindowsIconifyMaximizeButtonBackground->setEndPosition(Vec2f(0.0f,1.0f));

    //Windows  DisabledIconifyMaximizeButtonBackground
    GradientLayerRefPtr WindowsDisabledIconifyMaximizeButtonBackground = GradientLayer::create();
    WindowsDisabledIconifyMaximizeButtonBackground->editMFStops()->push_back(0.0);
    WindowsDisabledIconifyMaximizeButtonBackground->editMFColors()->push_back(Color4f(1.0, 1.0, 1.0, 1.0));
    WindowsDisabledIconifyMaximizeButtonBackground->editMFStops()->push_back(1.0);
    WindowsDisabledIconifyMaximizeButtonBackground->editMFColors()->push_back(Color4f(0.74, 0.75, 0.82, 1.0));
    WindowsDisabledIconifyMaximizeButtonBackground->setStartPosition(Vec2f(0.0f,0.0f));
    WindowsDisabledIconifyMaximizeButtonBackground->setEndPosition(Vec2f(0.0f,1.0f));

    //IconifyButton DrawObject
    PolygonUIDrawObjectRefPtr WindowsIconifyButtonDrawObject1 = PolygonUIDrawObject::create();
    WindowsIconifyButtonDrawObject1->setColor(Color4f(1.0,1.0,1.0,1.0));
    WindowsIconifyButtonDrawObject1->setOpacity(1.0);
    WindowsIconifyButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(0,0));
    WindowsIconifyButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(0,4));
    WindowsIconifyButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(8,4));
    WindowsIconifyButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(8,0));

    PolygonUIDrawObjectRefPtr WindowsIconifyButtonDrawObject2 = PolygonUIDrawObject::create();
    WindowsIconifyButtonDrawObject2->setColor(Color4f(0.15,0.15,0.21,1.0));
    WindowsIconifyButtonDrawObject2->setOpacity(1.0);
    WindowsIconifyButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(1,0));
    WindowsIconifyButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(1,1));
    WindowsIconifyButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(8,1));
    WindowsIconifyButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(8,0));

    PolygonUIDrawObjectRefPtr WindowsIconifyButtonDrawObject3 = PolygonUIDrawObject::create();
    WindowsIconifyButtonDrawObject3->setColor(Color4f(0.15,0.15,0.21,1.0));
    WindowsIconifyButtonDrawObject3->setOpacity(1.0);
    WindowsIconifyButtonDrawObject3->editMFVerticies()->push_back(Pnt2f(7,1));
    WindowsIconifyButtonDrawObject3->editMFVerticies()->push_back(Pnt2f(7,3));
    WindowsIconifyButtonDrawObject3->editMFVerticies()->push_back(Pnt2f(8,3));
    WindowsIconifyButtonDrawObject3->editMFVerticies()->push_back(Pnt2f(8,1));

    PolygonUIDrawObjectRefPtr WindowsIconifyButtonDrawObject4 = PolygonUIDrawObject::create();
    WindowsIconifyButtonDrawObject4->setColor(Color4f(0.43,0.43,0.56,1.0));
    WindowsIconifyButtonDrawObject4->setOpacity(1.0);
    WindowsIconifyButtonDrawObject4->editMFVerticies()->push_back(Pnt2f(1,1));
    WindowsIconifyButtonDrawObject4->editMFVerticies()->push_back(Pnt2f(1,3));
    WindowsIconifyButtonDrawObject4->editMFVerticies()->push_back(Pnt2f(7,3));
    WindowsIconifyButtonDrawObject4->editMFVerticies()->push_back(Pnt2f(7,1));

    UIDrawObjectCanvasRefPtr WindowsIconifyButtonCanvas = UIDrawObjectCanvas::create();
    WindowsIconifyButtonCanvas->pushToDrawObjects(WindowsIconifyButtonDrawObject1);
    WindowsIconifyButtonCanvas->pushToDrawObjects(WindowsIconifyButtonDrawObject2);
    WindowsIconifyButtonCanvas->pushToDrawObjects(WindowsIconifyButtonDrawObject3);
    WindowsIconifyButtonCanvas->pushToDrawObjects(WindowsIconifyButtonDrawObject4);

    //Iconify Button
    ButtonRefPtr WindowsInternalWindowTitlebarIconifyButton = Button::create();
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
    WindowsInternalWindowTitlebarIconifyButton->setAlignment(Vec2f(0.25f,0.85f));

    //MaximizeButton
    ButtonRefPtr WindowsInternalWindowTitlebarMaximizeButton = Button::create();
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

    //Windows CloseButtonBorder
    RoundedCornerLineBorderRefPtr WindowsCloseButtonBorder = RoundedCornerLineBorder::create();
    WindowsCloseButtonBorder->setColor( Color4f(0.65, 0.22, 0.27 ,1.0) );
    WindowsCloseButtonBorder->setWidth(1);
    WindowsCloseButtonBorder->setCornerRadius(3);

    //Windows ActiveCloseButtonBorder
    RoundedCornerLineBorderRefPtr ActiveWindowsCloseButtonBorder = RoundedCornerLineBorder::create();
    ActiveWindowsCloseButtonBorder->setColor( Color4f(0.75, 0.22, 0.27 ,1.0) );
    ActiveWindowsCloseButtonBorder->setWidth(1);
    ActiveWindowsCloseButtonBorder->setCornerRadius(3);

    //Windows DisabledCloseButtonBorder
    RoundedCornerLineBorderRefPtr DisabledWindowsCloseButtonBorder = RoundedCornerLineBorder::create();
    DisabledWindowsCloseButtonBorder->setColor( Color4f(0.76, 0.56, 0.58 ,1.0) );
    DisabledWindowsCloseButtonBorder->setWidth(1);
    DisabledWindowsCloseButtonBorder->setCornerRadius(3);

    //Windows  CloseButtonBackground
    GradientLayerRefPtr WindowsCloseButtonBackground = GradientLayer::create();
    WindowsCloseButtonBackground->editMFColors()->push_back(Color4f(0.96, 0.56, 0.52, 1.0));
    WindowsCloseButtonBackground->editMFStops()->push_back(0.0);
    WindowsCloseButtonBackground->editMFColors()->push_back(Color4f(0.78, 0.33, 0.36, 1.0));
    WindowsCloseButtonBackground->editMFStops()->push_back(1.0);
    WindowsCloseButtonBackground->setStartPosition(Vec2f(0.0f,0.0f));
    WindowsCloseButtonBackground->setEndPosition(Vec2f(0.0f,1.0f));

    //Windows  ActiveCloseButtonBackground
    GradientLayerRefPtr ActiveWindowsCloseButtonBackground = GradientLayer::create();
    ActiveWindowsCloseButtonBackground->editMFColors()->push_back(Color4f(0.92, 0.41, 0.36, 1.0));
    ActiveWindowsCloseButtonBackground->editMFStops()->push_back(0.0);
    ActiveWindowsCloseButtonBackground->editMFColors()->push_back(Color4f(1.0, 0.64, 0.54, 1.0));
    ActiveWindowsCloseButtonBackground->editMFStops()->push_back(1.0);
    ActiveWindowsCloseButtonBackground->setStartPosition(Vec2f(0.0f,0.0f));
    ActiveWindowsCloseButtonBackground->setEndPosition(Vec2f(0.0f,1.0f));

    //Windows  DisabledCloseButtonBackground
    GradientLayerRefPtr WindowsDisabledCloseButtonBackground = GradientLayer::create();
    WindowsDisabledCloseButtonBackground->editMFColors()->push_back(Color4f(0.94, 0.76, 0.75, 1.0));
    WindowsDisabledCloseButtonBackground->editMFStops()->push_back(0.0);
    WindowsDisabledCloseButtonBackground->editMFColors()->push_back(Color4f(0.83, 0.63, 0.64, 1.0));
    WindowsDisabledCloseButtonBackground->editMFStops()->push_back(1.0);
    WindowsDisabledCloseButtonBackground->setStartPosition(Vec2f(0.0f,0.0f));
    WindowsDisabledCloseButtonBackground->setEndPosition(Vec2f(0.0f,1.0f));


    PolygonUIDrawObjectRefPtr WindowsCloseButtonDrawObject1 = PolygonUIDrawObject::create();
    WindowsCloseButtonDrawObject1->setColor(Color4f(0.35,0.11,0.19,1.0));
    WindowsCloseButtonDrawObject1->setOpacity(1.0);
    WindowsCloseButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(1,0));
    WindowsCloseButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(11,11));
    WindowsCloseButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(13,11));
    WindowsCloseButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(3,0));

    PolygonUIDrawObjectRefPtr WindowsCloseButtonDrawObject2 = PolygonUIDrawObject::create();
    WindowsCloseButtonDrawObject2->setColor(Color4f(0.35,0.11,0.19,1.0));
    WindowsCloseButtonDrawObject2->setOpacity(1.0);
    WindowsCloseButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(0,10));
    WindowsCloseButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(2,10));
    WindowsCloseButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(12,0));
    WindowsCloseButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(10,0));

    PolygonUIDrawObjectRefPtr WindowsCloseButtonDrawObject3 = PolygonUIDrawObject::create();
    WindowsCloseButtonDrawObject3->setColor(Color4f(1.0,1.0,1.0,1.0));
    WindowsCloseButtonDrawObject3->setOpacity(1.0);
    WindowsCloseButtonDrawObject3->editMFVerticies()->push_back(Pnt2f(1,1));
    WindowsCloseButtonDrawObject3->editMFVerticies()->push_back(Pnt2f(1,3));
    WindowsCloseButtonDrawObject3->editMFVerticies()->push_back(Pnt2f(10,12));
    WindowsCloseButtonDrawObject3->editMFVerticies()->push_back(Pnt2f(12,12));
    WindowsCloseButtonDrawObject3->editMFVerticies()->push_back(Pnt2f(12,10));
    WindowsCloseButtonDrawObject3->editMFVerticies()->push_back(Pnt2f(3,1));

    PolygonUIDrawObjectRefPtr WindowsCloseButtonDrawObject4 = PolygonUIDrawObject::create();
    WindowsCloseButtonDrawObject4->setColor(Color4f(1.0,1.0,1.0,1.0));
    WindowsCloseButtonDrawObject4->setOpacity(1.0);
    WindowsCloseButtonDrawObject4->editMFVerticies()->push_back(Pnt2f(1,12));
    WindowsCloseButtonDrawObject4->editMFVerticies()->push_back(Pnt2f(3,12));
    WindowsCloseButtonDrawObject4->editMFVerticies()->push_back(Pnt2f(12,3));
    WindowsCloseButtonDrawObject4->editMFVerticies()->push_back(Pnt2f(12,1));
    WindowsCloseButtonDrawObject4->editMFVerticies()->push_back(Pnt2f(10,1));
    WindowsCloseButtonDrawObject4->editMFVerticies()->push_back(Pnt2f(1,10));

    UIDrawObjectCanvasRefPtr WindowsCloseButtonCanvas = UIDrawObjectCanvas::create();
    WindowsCloseButtonCanvas->pushToDrawObjects(WindowsCloseButtonDrawObject1);
    WindowsCloseButtonCanvas->pushToDrawObjects(WindowsCloseButtonDrawObject2);
    WindowsCloseButtonCanvas->pushToDrawObjects(WindowsCloseButtonDrawObject3);
    WindowsCloseButtonCanvas->pushToDrawObjects(WindowsCloseButtonDrawObject4);

    //Windows CloseButton
    ButtonRefPtr WindowsInternalWindowTitlebarCloseButton = Button::create();
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
    WindowsInternalWindowTitlebarCloseButton->setAlignment(Vec2f(0.5f,0.5f));

    LabelRefPtr WindowsInternalWindowTitlebarTitleLabel = Label::create();
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

    //Titlebar background
    GradientLayerRefPtr WIndowsInternalWindowTitlebarBackground = GradientLayer::create();
    WIndowsInternalWindowTitlebarBackground->editMFColors()->push_back(Color4f(0.64, 0.64, 0.75, 1.0));
    WIndowsInternalWindowTitlebarBackground->editMFStops()->push_back(0.0);
    WIndowsInternalWindowTitlebarBackground->editMFColors()->push_back(Color4f(0.89, 0.89, 0.89, 1.0));
    WIndowsInternalWindowTitlebarBackground->editMFStops()->push_back(1.0);
    WIndowsInternalWindowTitlebarBackground->setStartPosition(Vec2f(0.0f,0.0f));
    WIndowsInternalWindowTitlebarBackground->setEndPosition(Vec2f(0.0f,1.0f));
    //Titlebar DisabledBackground
    GradientLayerRefPtr WindowsInternalWindowTitlebarDisabledBackground = GradientLayer::create();
    WindowsInternalWindowTitlebarDisabledBackground->editMFColors()->push_back(Color4f(0.84, 0.84, 0.89, 1.0));
    WindowsInternalWindowTitlebarDisabledBackground->editMFStops()->push_back(0.0);
    WindowsInternalWindowTitlebarDisabledBackground->editMFColors()->push_back(Color4f(0.99, 1.0, 0.99, 1.0));
    WindowsInternalWindowTitlebarDisabledBackground->editMFStops()->push_back(1.0);
    WindowsInternalWindowTitlebarDisabledBackground->setStartPosition(Vec2f(0.0f,0.0f));
    WindowsInternalWindowTitlebarDisabledBackground->setEndPosition(Vec2f(0.0f,1.0f));


    //Titlebar
    TitlebarRefPtr WindowsInternalWindowTitlebar = Titlebar::create();
    WindowsInternalWindowTitlebar->setEnabled(true);
    WindowsInternalWindowTitlebar->setVisible(true);

    WindowsInternalWindowTitlebar->setConstraints(NULL);
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
    WindowsInternalWindowTitlebar->setFrameIcon(NULL);
    WindowsInternalWindowTitlebar->setDrawClose(true);
    WindowsInternalWindowTitlebar->setDrawMaximize(true);
    WindowsInternalWindowTitlebar->setDrawIconify(true);


    //Windows InternalWindow
    WindowsInternalWindow->setEnabled(true);
    WindowsInternalWindow->setVisible(true);

    WindowsInternalWindow->setConstraints(NULL);
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
    WindowsInternalWindow->setClosable(true);
    WindowsInternalWindow->setIconable(true);
    WindowsInternalWindow->setMaximizable(true);
    WindowsInternalWindow->setResizable(true);
    WindowsInternalWindow->setTitle(std::string(""));
    WindowsInternalWindow->setDesktopIcon(NULL);
    WindowsInternalWindow->setAllwaysOnTop(false);
    WindowsInternalWindow->setDrawTitlebar(true);
    WindowsInternalWindow->setDrawDecorations(true);
    WindowsInternalWindow->setAlignmentInDrawingSurface(Vec2f(-1.0f,-1.0f));
    WindowsInternalWindow->setScalingInDrawingSurface(Vec2f(-1.0f,-1.0f));
    WindowsInternalWindow->setResizeModifyCursorWidth(4);

    //InternalWindow
    WindowsInternalWindow->setTitlebar(WindowsInternalWindowTitlebar);
    


    //************************** DialogWindow *****************************
    //Titlebar
    TitlebarRefPtr WindowsDialogWindowTitlebar = Titlebar::create();
    WindowsDialogWindowTitlebar->setEnabled(true);
    WindowsDialogWindowTitlebar->setVisible(true);

    WindowsDialogWindowTitlebar->setConstraints(NULL);
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
    WindowsDialogWindowTitlebar->setFrameIcon(NULL);
    WindowsDialogWindowTitlebar->setDrawClose(true);
    WindowsDialogWindowTitlebar->setDrawMaximize(false);
    WindowsDialogWindowTitlebar->setDrawIconify(false);


    //Windows DialogWindow
    WindowsDialogWindow->setEnabled(true);
    WindowsDialogWindow->setVisible(true);

    WindowsDialogWindow->setConstraints(NULL);
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
    WindowsDialogWindow->setClosable(true);
    WindowsDialogWindow->setIconable(false);
    WindowsDialogWindow->setMaximizable(false);
    WindowsDialogWindow->setResizable(false);
    WindowsDialogWindow->setTitle(std::string(""));
    WindowsDialogWindow->setDesktopIcon(NULL);
    WindowsDialogWindow->setAllwaysOnTop(true);
    WindowsDialogWindow->setDrawTitlebar(true);
    WindowsDialogWindow->setDrawDecorations(true);
    WindowsDialogWindow->setAlignmentInDrawingSurface(Vec2f(-1.0f,-1.0f));
    WindowsDialogWindow->setScalingInDrawingSurface(Vec2f(-1.0f,-1.0f));
    WindowsDialogWindow->setResizeModifyCursorWidth(4);

    //DialogWindow
    WindowsDialogWindow->setTitlebar(WindowsDialogWindowTitlebar);


    //************************** Panel *****************************
    //Windows PanelBorder
    //LineBorderRefPtr WindowsPanelBorder = LineBorder::create();
    //WindowsPanelBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
    //WindowsPanelBorder->setWidth(1);

    EtchedBorderRefPtr WindowsPanelBorder = EtchedBorder::create();
    WindowsPanelBorder->setWidth(2);
    WindowsPanelBorder->setHighlight(Color4f(1.0, 1.0, 1.0, 1.0));
    WindowsPanelBorder->setShadow(Color4f(0.65, 0.65, 0.65, 1.0));
    WindowsPanelBorder->setRaised(true);

    //Windows PanelBackground
    ColorLayerRefPtr WindowsPanelBackground = ColorLayer::create();
    WindowsPanelBackground->setColor(Color4f(0.9569,0.9529,0.9373,1.0));


    //Windows Panel
    WindowsPanel->setEnabled(true);
    WindowsPanel->setVisible(true);

    WindowsPanel->setConstraints(NULL);
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
    

    ///[>************************* Toolbar *****************************
    ////Windows Toolbar
    //WindowsToolbar->setEnabled(true);
    //WindowsToolbar->setVisible(true);

    //WindowsToolbar->setConstraints(NULL);
    ////Sizes
    //WindowsToolbar->setMinSize(Vec2f(0,0));
    //WindowsToolbar->setMaxSize(Vec2f(32767,32767)); //2^15
    //WindowsToolbar->setPreferredSize(Vec2f(100,100));

    ////Border
    //WindowsToolbar->setBorders(WindowsEmptyBorder);

    ////Background
    //WindowsToolbar->setBackgrounds(WindowsPanelBackground);

    ////Opacity
    //WindowsToolbar->setOpacity(1.0);
    //************************** SplitPanel *****************************
    //The only default value set will be the divider

    //Windows Divider Background and Border
    ColorLayerRefPtr WindowsDividerBackground = ColorLayer::create();
    WindowsDividerBackground->setColor(Color4f(0.93,0.93,0.93,1.0));

    //Windows Divider
    UIDrawObjectCanvasRefPtr WindowsDividerDrawObject = UIDrawObjectCanvas::create();
    WindowsDividerDrawObject->setBackground(WindowsDividerBackground);

    //Windows SplitPanel
    WindowsSplitPanel->setEnabled(true);
    WindowsSplitPanel->setVisible(true);

    WindowsSplitPanel->setConstraints(NULL);
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

    //************************** TabPanel *****************************
    RoundedCornerLineBorderRefPtr WindowsTabPanelTabBorder = RoundedCornerLineBorder::create();
    WindowsTabPanelTabBorder->setColor( Color4f(0.57, 0.61, 0.61 ,1.0) );
    WindowsTabPanelTabBorder->setWidth(1);
    WindowsTabPanelTabBorder->setCornerRadius(3);

    MatteBorderRefPtr WindowsTabPanelInsideActiveTabBorder = MatteBorder::create();
    WindowsTabPanelInsideActiveTabBorder->setLeftWidth(0);
    WindowsTabPanelInsideActiveTabBorder->setRightWidth(0);
    WindowsTabPanelInsideActiveTabBorder->setTopWidth(3);
    WindowsTabPanelInsideActiveTabBorder->setBottomWidth(0);
    WindowsTabPanelInsideActiveTabBorder->setColor(Color4f(1.0, 0.78, 0.24, 1.0));

    CompoundBorderRefPtr WindowsTabPanelActiveTabBorder = CompoundBorder::create();
    WindowsTabPanelActiveTabBorder->setInnerBorder(WindowsTabPanelInsideActiveTabBorder);
    WindowsTabPanelActiveTabBorder->setOuterBorder(WindowsTabPanelTabBorder);

    GradientLayerRefPtr WindowsTabPanelTabBackground = GradientLayer::create();
    WindowsTabPanelTabBackground->editMFColors()->push_back(Color4f(1.0,1.0,1.0,1.0));
    WindowsTabPanelTabBackground->editMFStops()->push_back(0.0);
    WindowsTabPanelTabBackground->editMFColors()->push_back(Color4f(0.75,0.75,0.85,1.0));
    WindowsTabPanelTabBackground->editMFStops()->push_back(1.0);
    WindowsTabPanelTabBackground->setStartPosition(Vec2f(0.0f,0.0f));
    WindowsTabPanelTabBackground->setEndPosition(Vec2f(0.0f,1.0f));

    ColorLayerRefPtr WindowsTabPanelTabActiveBackground = ColorLayer::create();
    WindowsTabPanelTabActiveBackground->setColor(Color4f(0.9569,0.9529,0.9373,1.0));

    LineBorderRefPtr WindowsTabPanelContentBorder = LineBorder::create();
    WindowsTabPanelContentBorder->setWidth(1);
    WindowsTabPanelContentBorder->setColor(Color4f(0.57, 0.61, 0.61 ,1.0));
    //Windows TabPanel
    WindowsTabPanel->setEnabled(true);
    WindowsTabPanel->setVisible(true);

    WindowsTabPanel->setConstraints(NULL);
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

    //************************** ImageComponent *****************************
    //Windows ImageComponentBorder
    EmptyBorderRefPtr WindowsImageComponentBorder = EmptyBorder::create();

    //Windows ImageComponentBackground
    EmptyLayerRefPtr WindowsImageComponentBackground = EmptyLayer::create();

    //Windows ImageComponent
    WindowsImageComponent->setEnabled(true);
    WindowsImageComponent->setVisible(true);

    WindowsImageComponent->setConstraints(NULL);
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
    WindowsImageComponent->setAlignment(Vec2f(0.5f,0.5f));
    


    //************************** Checkbox Button Component *****************************
    UIDrawObjectCanvasRefPtr WindowsCheckboxDrawObject = UIDrawObjectCanvas::create();
    UIDrawObjectCanvasRefPtr WindowsSelectedCheckboxDrawObject = UIDrawObjectCanvas::create();
    UIDrawObjectCanvasRefPtr WindowsActiveCheckboxDrawObject = UIDrawObjectCanvas::create();
    UIDrawObjectCanvasRefPtr WindowsActiveSelectedCheckboxDrawObject = UIDrawObjectCanvas::create();
    UIDrawObjectCanvasRefPtr WindowsRolloverCheckboxDrawObject = UIDrawObjectCanvas::create();
    UIDrawObjectCanvasRefPtr WindowsRolloverSelectedCheckboxDrawObject = UIDrawObjectCanvas::create();
    UIDrawObjectCanvasRefPtr WindowsDisabledCheckboxDrawObject = UIDrawObjectCanvas::create();
    UIDrawObjectCanvasRefPtr WindowsDisabledSelectedCheckboxDrawObject = UIDrawObjectCanvas::create();

    //Normal Background
    MultiColoredQuadUIDrawObjectRefPtr CheckboxBackground = MultiColoredQuadUIDrawObject::create();
    CheckboxBackground->setPoint1(Pnt2f(1,1));
    CheckboxBackground->setPoint2(Pnt2f(12,1));
    CheckboxBackground->setPoint3(Pnt2f(12,12));
    CheckboxBackground->setPoint4(Pnt2f(1,12));
    CheckboxBackground->setColor1(Color4f(.86,.86,.84,1.0));
    CheckboxBackground->setColor2(Color4f(.95,.95,.94,1.0));
    CheckboxBackground->setColor3(Color4f(1.0,1.0,1.0,1.0));
    CheckboxBackground->setColor4(Color4f(.95,.95,.94,1.0));
    CheckboxBackground->setOpacity(1.0);

    //Normal Border
    RectUIDrawObjectRefPtr CheckboxBackgroundBorder = RectUIDrawObject::create();
    CheckboxBackgroundBorder->setTopLeft(Pnt2f(0,0));
    CheckboxBackgroundBorder->setBottomRight(Pnt2f(13,13));
    CheckboxBackgroundBorder->setColor(Color4f(.110,.318,.502,1.0));
    CheckboxBackgroundBorder->setOpacity(1.0);

    //Active Background
    MultiColoredQuadUIDrawObjectRefPtr CheckboxActiveBackground = MultiColoredQuadUIDrawObject::create();
    CheckboxActiveBackground->setPoint1(Pnt2f(1,1));
    CheckboxActiveBackground->setPoint2(Pnt2f(12,1));
    CheckboxActiveBackground->setPoint3(Pnt2f(12,12));
    CheckboxActiveBackground->setPoint4(Pnt2f(1,12));
    CheckboxActiveBackground->setColor1(Color4f(.69,.69,.65,1.0));
    CheckboxActiveBackground->setColor2(Color4f(.95,.94,.87,1.0));
    CheckboxActiveBackground->setColor3(Color4f(1.0,1.0,1.0,1.0));
    CheckboxActiveBackground->setColor4(Color4f(.84,.84,.78,1.0));
    CheckboxActiveBackground->setOpacity(1.0);

    //Disabled Background
    RectUIDrawObjectRefPtr CheckboxDisabledBackground = RectUIDrawObject::create();
    CheckboxDisabledBackground->setTopLeft(Pnt2f(1,1));
    CheckboxDisabledBackground->setBottomRight(Pnt2f(12,12));
    CheckboxDisabledBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
    CheckboxDisabledBackground->setOpacity(1.0);

    //Disabled Border
    RectUIDrawObjectRefPtr CheckboxDisabledBackgroundBorder = RectUIDrawObject::create();
    CheckboxDisabledBackgroundBorder->setTopLeft(Pnt2f(0,0));
    CheckboxDisabledBackgroundBorder->setBottomRight(Pnt2f(13,13));
    CheckboxDisabledBackgroundBorder->setColor(Color4f(.79,.78,.73,1.0));
    CheckboxDisabledBackgroundBorder->setOpacity(1.0);

    //The Checkmark
    Color4f CheckmarkColor(0.13,0.63,0.13,1.0);
    MultiColoredQuadUIDrawObjectRefPtr CheckboxCheckQuad1 = MultiColoredQuadUIDrawObject::create();
    CheckboxCheckQuad1->setPoint1(Pnt2f(3,4));
    CheckboxCheckQuad1->setPoint2(Pnt2f(6,7));
    CheckboxCheckQuad1->setPoint3(Pnt2f(6,10));
    CheckboxCheckQuad1->setPoint4(Pnt2f(3,7));
    CheckboxCheckQuad1->setColor1(CheckmarkColor);
    CheckboxCheckQuad1->setColor2(CheckmarkColor);
    CheckboxCheckQuad1->setColor3(CheckmarkColor);
    CheckboxCheckQuad1->setColor4(CheckmarkColor);
    CheckboxCheckQuad1->setOpacity(1.0);

    MultiColoredQuadUIDrawObjectRefPtr CheckboxCheckQuad2 = MultiColoredQuadUIDrawObject::create();
    CheckboxCheckQuad2->setPoint1(Pnt2f(6,7));
    CheckboxCheckQuad2->setPoint2(Pnt2f(10,3));
    CheckboxCheckQuad2->setPoint3(Pnt2f(10,6));
    CheckboxCheckQuad2->setPoint4(Pnt2f(6,10));
    CheckboxCheckQuad2->setColor1(CheckmarkColor);
    CheckboxCheckQuad2->setColor2(CheckmarkColor);
    CheckboxCheckQuad2->setColor3(CheckmarkColor);
    CheckboxCheckQuad2->setColor4(CheckmarkColor);
    CheckboxCheckQuad2->setOpacity(1.0);

    //The Disabled Checkmark
    Color4f CheckmarkDisabledColor(0.79,0.78,0.73,1.0);
    MultiColoredQuadUIDrawObjectRefPtr CheckboxDisabledCheckQuad1 = MultiColoredQuadUIDrawObject::create();
    CheckboxDisabledCheckQuad1->setPoint1(Pnt2f(3,4));
    CheckboxDisabledCheckQuad1->setPoint2(Pnt2f(6,7));
    CheckboxDisabledCheckQuad1->setPoint3(Pnt2f(6,10));
    CheckboxDisabledCheckQuad1->setPoint4(Pnt2f(3,7));
    CheckboxDisabledCheckQuad1->setColor1(CheckmarkDisabledColor);
    CheckboxDisabledCheckQuad1->setColor2(CheckmarkDisabledColor);
    CheckboxDisabledCheckQuad1->setColor3(CheckmarkDisabledColor);
    CheckboxDisabledCheckQuad1->setColor4(CheckmarkDisabledColor);
    CheckboxDisabledCheckQuad1->setOpacity(1.0);

    MultiColoredQuadUIDrawObjectRefPtr CheckboxDisabledCheckQuad2 = MultiColoredQuadUIDrawObject::create();
    CheckboxDisabledCheckQuad2->setPoint1(Pnt2f(6,7));
    CheckboxDisabledCheckQuad2->setPoint2(Pnt2f(10,3));
    CheckboxDisabledCheckQuad2->setPoint3(Pnt2f(10,6));
    CheckboxDisabledCheckQuad2->setPoint4(Pnt2f(6,10));
    CheckboxDisabledCheckQuad2->setColor1(CheckmarkDisabledColor);
    CheckboxDisabledCheckQuad2->setColor2(CheckmarkDisabledColor);
    CheckboxDisabledCheckQuad2->setColor3(CheckmarkDisabledColor);
    CheckboxDisabledCheckQuad2->setColor4(CheckmarkDisabledColor);
    CheckboxDisabledCheckQuad2->setOpacity(1.0);

    //Normal
    WindowsCheckboxDrawObject->pushToDrawObjects(CheckboxBackgroundBorder);
    WindowsCheckboxDrawObject->pushToDrawObjects(CheckboxBackground);
    WindowsCheckboxDrawObject->setClipping(false);

    //Normal Selected
    WindowsSelectedCheckboxDrawObject->pushToDrawObjects(CheckboxBackgroundBorder);
    WindowsSelectedCheckboxDrawObject->pushToDrawObjects(CheckboxBackground);
    WindowsSelectedCheckboxDrawObject->pushToDrawObjects(CheckboxCheckQuad1);
    WindowsSelectedCheckboxDrawObject->pushToDrawObjects(CheckboxCheckQuad2);
    WindowsSelectedCheckboxDrawObject->setClipping(false);

    //Active Selected
    WindowsActiveSelectedCheckboxDrawObject->pushToDrawObjects(CheckboxBackgroundBorder);
    WindowsActiveSelectedCheckboxDrawObject->pushToDrawObjects(CheckboxBackground);
    WindowsActiveSelectedCheckboxDrawObject->pushToDrawObjects(CheckboxActiveBackground);
    WindowsActiveSelectedCheckboxDrawObject->setClipping(false);

    //Active Non-selected
    WindowsActiveCheckboxDrawObject->pushToDrawObjects(CheckboxBackgroundBorder);
    WindowsActiveCheckboxDrawObject->pushToDrawObjects(CheckboxBackground);
    WindowsActiveCheckboxDrawObject->pushToDrawObjects(CheckboxActiveBackground);
    WindowsActiveCheckboxDrawObject->pushToDrawObjects(CheckboxCheckQuad1);
    WindowsActiveCheckboxDrawObject->pushToDrawObjects(CheckboxCheckQuad2);
    WindowsActiveCheckboxDrawObject->setClipping(false);


    //Rollover Border
    MultiColoredQuadUIDrawObjectRefPtr RolloverCheckboxBorder = MultiColoredQuadUIDrawObject::create();
    RolloverCheckboxBorder->setPoint1(Pnt2f(1,1));
    RolloverCheckboxBorder->setPoint2(Pnt2f(12,1));
    RolloverCheckboxBorder->setPoint3(Pnt2f(12,12));
    RolloverCheckboxBorder->setPoint4(Pnt2f(1,12));
    RolloverCheckboxBorder->setColor1(Color4f(1.0,.94,.81,1.0));
    RolloverCheckboxBorder->setColor2(Color4f(.98,.78,.39,1.0));
    RolloverCheckboxBorder->setColor3(Color4f(0.97,0.70,0.19,1.0));
    RolloverCheckboxBorder->setColor4(Color4f(.98,.78,.39,1.0));
    RolloverCheckboxBorder->setOpacity(1.0);

    RectUIDrawObjectRefPtr RolloverCheckboxBackground = RectUIDrawObject::create();
    RolloverCheckboxBackground->setTopLeft(Pnt2f(3,3));
    RolloverCheckboxBackground->setBottomRight(Pnt2f(10,10));
    RolloverCheckboxBackground->setColor(Color4f(0.91,.91,.89,1.0));
    RolloverCheckboxBackground->setOpacity(1.0);

    //Rollover Selected
    WindowsRolloverSelectedCheckboxDrawObject->pushToDrawObjects(CheckboxBackgroundBorder);
    WindowsRolloverSelectedCheckboxDrawObject->pushToDrawObjects(RolloverCheckboxBorder);
    WindowsRolloverSelectedCheckboxDrawObject->pushToDrawObjects(RolloverCheckboxBackground);
    WindowsRolloverSelectedCheckboxDrawObject->pushToDrawObjects(CheckboxCheckQuad1);
    WindowsRolloverSelectedCheckboxDrawObject->pushToDrawObjects(CheckboxCheckQuad2);
    WindowsRolloverSelectedCheckboxDrawObject->setClipping(false);

    //Rollover Non-selected
    WindowsRolloverCheckboxDrawObject->pushToDrawObjects(CheckboxBackgroundBorder);
    WindowsRolloverCheckboxDrawObject->pushToDrawObjects(RolloverCheckboxBorder);
    WindowsRolloverCheckboxDrawObject->pushToDrawObjects(RolloverCheckboxBackground);
    WindowsRolloverCheckboxDrawObject->setClipping(false);

    //Disabled Selected
    WindowsDisabledSelectedCheckboxDrawObject->pushToDrawObjects(CheckboxDisabledBackgroundBorder);
    WindowsDisabledSelectedCheckboxDrawObject->pushToDrawObjects(CheckboxDisabledBackground);
    WindowsDisabledSelectedCheckboxDrawObject->pushToDrawObjects(RolloverCheckboxBackground);
    WindowsDisabledSelectedCheckboxDrawObject->pushToDrawObjects(CheckboxDisabledCheckQuad1);
    WindowsDisabledSelectedCheckboxDrawObject->pushToDrawObjects(CheckboxDisabledCheckQuad2);
    WindowsDisabledSelectedCheckboxDrawObject->setClipping(false);

    //Disabled Non-selected
    WindowsDisabledCheckboxDrawObject->pushToDrawObjects(CheckboxDisabledBackgroundBorder);
    WindowsDisabledCheckboxDrawObject->pushToDrawObjects(CheckboxDisabledBackground);
    WindowsDisabledCheckboxDrawObject->setClipping(false);

    //Border
    EmptyBorderRefPtr WindowsCheckboxButtonBorder = EmptyBorder::create();

    //Background
    EmptyLayerRefPtr WindowsCheckboxButtonBackground = EmptyLayer::create();

    WindowsCheckboxButton->setEnabled(true);
    WindowsCheckboxButton->setVisible(true);

    WindowsCheckboxButton->setConstraints(NULL);
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
    WindowsCheckboxButton->setAlignment(Vec2f(0.5f,0.5f));
    WindowsCheckboxButton->setTextColor(Color4f(0.0,0.0,0.0,1.0));
    WindowsCheckboxButton->setActiveTextColor(Color4f(0.0,0.0,0.0,1.0));
    WindowsCheckboxButton->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
    WindowsCheckboxButton->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
    WindowsCheckboxButton->setDisabledTextColor(WindowsDisabledTextColor);

    WindowsCheckboxButton->setActiveOffset(Vec2f(0,0));
    WindowsCheckboxButton->setDrawObjectToTextAlignment(Button::ALIGN_DRAW_OBJECT_LEFT_OF_TEXT);
    WindowsCheckboxButton->setDrawObjectToTextPadding(3.0f);
    

    //************************** Radio Button Component *****************************
    UIDrawObjectCanvasRefPtr WindowsRadioDrawObject = UIDrawObjectCanvas::create();
    UIDrawObjectCanvasRefPtr WindowsSelectedRadioDrawObject = UIDrawObjectCanvas::create();
    UIDrawObjectCanvasRefPtr WindowsActiveRadioDrawObject = UIDrawObjectCanvas::create();
    UIDrawObjectCanvasRefPtr WindowsActiveSelectedRadioDrawObject = UIDrawObjectCanvas::create();
    UIDrawObjectCanvasRefPtr WindowsRolloverRadioDrawObject = UIDrawObjectCanvas::create();
    UIDrawObjectCanvasRefPtr WindowsRolloverSelectedRadioDrawObject = UIDrawObjectCanvas::create();
    UIDrawObjectCanvasRefPtr WindowsDisabledRadioDrawObject = UIDrawObjectCanvas::create();
    UIDrawObjectCanvasRefPtr WindowsDisabledSelectedRadioDrawObject = UIDrawObjectCanvas::create();

    Pnt2f RadioUIDrawObjectsCenter(6,6);
    DiscUIDrawObjectRefPtr RadioBackground = DiscUIDrawObject::create();
    RadioBackground->setWidth(6);
    RadioBackground->setHeight(6);
    RadioBackground->setSubDivisions(30);
    RadioBackground->setStartAngleRad(0);
    RadioBackground->setEndAngleRad(6.28318531);
    RadioBackground->setCenterColor(Color4f(.945,.945,.937,1.0));
    RadioBackground->setOuterColor(Color4f(.945,.945,.937,1.0));
    RadioBackground->setOpacity(1.0);
    RadioBackground->setCenter(RadioUIDrawObjectsCenter);

    ArcUIDrawObjectRefPtr RadioBackgroundBorder = ArcUIDrawObject::create();
    RadioBackgroundBorder->setWidth(6);
    RadioBackgroundBorder->setHeight(6);
    RadioBackgroundBorder->setSubDivisions(25);
    RadioBackgroundBorder->setStartAngleRad(0);
    RadioBackgroundBorder->setEndAngleRad(6.28318531);
    RadioBackgroundBorder->setColor(Color4f(0.137,0.337,0.510,1.0));
    RadioBackgroundBorder->setOpacity(0.90);
    RadioBackgroundBorder->setLineWidth(1);
    RadioBackgroundBorder->setCenter(RadioUIDrawObjectsCenter);

    DiscUIDrawObjectRefPtr RadioSelected = DiscUIDrawObject::create();
    RadioSelected->setWidth(3);
    RadioSelected->setHeight(3);
    RadioSelected->setSubDivisions(15);
    RadioSelected->setStartAngleRad(0);
    RadioSelected->setEndAngleRad(6.28318531);
    RadioSelected->setCenterColor(Color4f(0.220,0.725,0.208,1.0));
    RadioSelected->setOuterColor(Color4f(0.220,0.725,0.208,0.6));
    RadioSelected->setOpacity(1.0);
    RadioSelected->setCenter(RadioUIDrawObjectsCenter);

    DiscUIDrawObjectRefPtr RadioActiveBackground = DiscUIDrawObject::create();
    RadioActiveBackground->setWidth(6);
    RadioActiveBackground->setHeight(6);
    RadioActiveBackground->setSubDivisions(30);
    RadioActiveBackground->setStartAngleRad(0);
    RadioActiveBackground->setEndAngleRad(6.28318531);
    RadioActiveBackground->setCenterColor(Color4f(.804,.800,.753,1.0));
    RadioActiveBackground->setOuterColor(Color4f(.804,.800,.753,1.0));
    RadioActiveBackground->setOpacity(1.0);
    RadioActiveBackground->setCenter(RadioUIDrawObjectsCenter);

    //Disabled Draw Objects
    DiscUIDrawObjectRefPtr RadioDisabledBackground = DiscUIDrawObject::create();
    RadioDisabledBackground->setWidth(6);
    RadioDisabledBackground->setHeight(6);
    RadioDisabledBackground->setSubDivisions(30);
    RadioDisabledBackground->setStartAngleRad(0);
    RadioDisabledBackground->setEndAngleRad(6.28318531);
    RadioDisabledBackground->setCenterColor(Color4f(.98,.97,.97,1.0));
    RadioDisabledBackground->setOuterColor(Color4f(.98,.97,.97,1.0));
    RadioDisabledBackground->setOpacity(1.0);
    RadioDisabledBackground->setCenter(RadioUIDrawObjectsCenter);

    ArcUIDrawObjectRefPtr RadioDisabledBackgroundBorder = ArcUIDrawObject::create();
    RadioDisabledBackgroundBorder->setWidth(6);
    RadioDisabledBackgroundBorder->setHeight(6);
    RadioDisabledBackgroundBorder->setSubDivisions(25);
    RadioDisabledBackgroundBorder->setStartAngleRad(0);
    RadioDisabledBackgroundBorder->setEndAngleRad(6.28318531);
    RadioDisabledBackgroundBorder->setColor(Color4f(0.75,0.75,0.71,1.0));
    RadioDisabledBackgroundBorder->setOpacity(0.90);
    RadioDisabledBackgroundBorder->setLineWidth(1);
    RadioDisabledBackgroundBorder->setCenter(RadioUIDrawObjectsCenter);

    DiscUIDrawObjectRefPtr RadioDisabledSelected = DiscUIDrawObject::create();
    RadioDisabledSelected->setWidth(3);
    RadioDisabledSelected->setHeight(3);
    RadioDisabledSelected->setSubDivisions(15);
    RadioDisabledSelected->setStartAngleRad(0);
    RadioDisabledSelected->setEndAngleRad(6.28318531);
    RadioDisabledSelected->setCenterColor(Color4f(0.75,0.75,0.71,1.0));
    RadioDisabledSelected->setOuterColor(Color4f(0.75,0.75,0.71,0.6));
    RadioDisabledSelected->setOpacity(1.0);
    RadioDisabledSelected->setCenter(RadioUIDrawObjectsCenter);

    // Yellow highlight border for whenever there is a hover listener
    ArcUIDrawObjectRefPtr RadioRolloverBorder = ArcUIDrawObject::create();
    RadioRolloverBorder->setWidth(5);
    RadioRolloverBorder->setHeight(5);
    RadioRolloverBorder->setSubDivisions(25);
    RadioRolloverBorder->setStartAngleRad(0);
    RadioRolloverBorder->setEndAngleRad(6.28318531);
    RadioRolloverBorder->setColor(Color4f(.980,.753,.306,1.0));
    RadioRolloverBorder->setOpacity(.85);
    RadioRolloverBorder->setCenter(RadioUIDrawObjectsCenter);
    RadioRolloverBorder->setLineWidth(2);

    WindowsRadioDrawObject->pushToDrawObjects(RadioBackground);
    WindowsRadioDrawObject->pushToDrawObjects(RadioBackgroundBorder);
    WindowsRadioDrawObject->setClipping(false);

    WindowsSelectedRadioDrawObject->pushToDrawObjects(RadioBackground);
    WindowsSelectedRadioDrawObject->pushToDrawObjects(RadioBackgroundBorder);
    WindowsSelectedRadioDrawObject->pushToDrawObjects(RadioSelected);
    WindowsSelectedRadioDrawObject->setClipping(false);

    WindowsActiveRadioDrawObject->pushToDrawObjects(RadioActiveBackground);
    WindowsActiveRadioDrawObject->pushToDrawObjects(RadioBackgroundBorder);
    WindowsActiveRadioDrawObject->pushToDrawObjects(RadioSelected);
    WindowsActiveRadioDrawObject->setClipping(false);

    WindowsActiveSelectedRadioDrawObject->pushToDrawObjects(RadioActiveBackground);
    WindowsActiveSelectedRadioDrawObject->pushToDrawObjects(RadioBackgroundBorder);
    WindowsActiveSelectedRadioDrawObject->setClipping(false);

    //Rollover Not Selected
    WindowsRolloverRadioDrawObject->pushToDrawObjects(RadioBackground);
    WindowsRolloverRadioDrawObject->pushToDrawObjects(RadioBackgroundBorder);
    WindowsRolloverRadioDrawObject->pushToDrawObjects(RadioRolloverBorder);
    WindowsRolloverRadioDrawObject->setClipping(false);

    //Rollover Selected
    WindowsRolloverSelectedRadioDrawObject->pushToDrawObjects(RadioBackground);
    WindowsRolloverSelectedRadioDrawObject->pushToDrawObjects(RadioBackgroundBorder);
    WindowsRolloverSelectedRadioDrawObject->pushToDrawObjects(RadioRolloverBorder);
    WindowsRolloverSelectedRadioDrawObject->pushToDrawObjects(RadioSelected);
    WindowsRolloverSelectedRadioDrawObject->setClipping(false);

    //Disabled Not Selected
    WindowsDisabledRadioDrawObject->pushToDrawObjects(RadioDisabledBackground);
    WindowsDisabledRadioDrawObject->pushToDrawObjects(RadioDisabledBackgroundBorder);
    WindowsDisabledRadioDrawObject->setClipping(false);

    //Disabled Selected
    WindowsDisabledSelectedRadioDrawObject->pushToDrawObjects(RadioDisabledBackground);
    WindowsDisabledSelectedRadioDrawObject->pushToDrawObjects(RadioDisabledBackgroundBorder);
    WindowsDisabledSelectedRadioDrawObject->pushToDrawObjects(RadioDisabledSelected);
    WindowsDisabledSelectedRadioDrawObject->setClipping(false);

    EmptyBorderRefPtr WindowsRadioButtonBorder = EmptyBorder::create();
    EmptyLayerRefPtr WindowsRadioButtonBackground = EmptyLayer::create();


    WindowsRadioButton->setEnabled(true);
    WindowsRadioButton->setVisible(true);
    WindowsRadioButton->setConstraints(NULL);

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
    WindowsRadioButton->setAlignment(Vec2f(0.5f,0.5f));
    WindowsRadioButton->setTextColor(Color4f(0.0,0.0,0.0,1.0));
    WindowsRadioButton->setActiveTextColor(Color4f(0.0,0.0,0.0,1.0));
    WindowsRadioButton->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
    WindowsRadioButton->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
    WindowsRadioButton->setDisabledTextColor(WindowsDisabledTextColor);

    WindowsRadioButton->setActiveOffset(Vec2f(0,0));
    WindowsRadioButton->setDrawObjectToTextAlignment(Button::ALIGN_DRAW_OBJECT_LEFT_OF_TEXT);
    WindowsRadioButton->setDrawObjectToTextPadding(3.0f);


    /********Toggle Button********/

    WindowsToggleButton->setEnabled(true);
    WindowsToggleButton->setVisible(true);

    WindowsToggleButton->setConstraints(NULL);
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
    WindowsToggleButton->setAlignment(Vec2f(0.5f,0.5f));
    WindowsToggleButton->setTextColor(Color4f(0.0,0.0,0.0,1.0));
    WindowsToggleButton->setActiveTextColor(Color4f(0.0,0.0,0.0,1.0));
    WindowsToggleButton->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
    WindowsToggleButton->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
    WindowsToggleButton->setDisabledTextColor(WindowsDisabledTextColor);

    WindowsToggleButton->setActiveOffset(Vec2f(2,2));
    WindowsToggleButton->setDrawObjectToTextAlignment(Button::ALIGN_DRAW_OBJECT_LEFT_OF_TEXT);
    WindowsToggleButton->setDrawObjectToTextPadding(4.0f);
    


    //************************** Menu Button *****************************

    WindowsMenuButton->setEnabled(true);
    WindowsMenuButton->setVisible(true);

    WindowsMenuButton->setConstraints(NULL);
    //Sizes
    WindowsMenuButton->setMinSize(Vec2f(0,0));
    WindowsMenuButton->setMaxSize(Vec2f(32767,32767)); //2^15
    WindowsMenuButton->setPreferredSize(Vec2f(75,23));

    //Border
    WindowsMenuButton->setBorder(WindowsButtonBorder);
    WindowsMenuButton->setRolloverBorder(WindowsRolloverButtonBorder);
    WindowsMenuButton->setFocusedBorder(WindowsButtonBorder);
    WindowsMenuButton->setDisabledBorder(WindowsDisabledButtonBorder);
    WindowsMenuButton->setActiveBorder(WindowsActiveButtonBorder);

    //Background
    WindowsMenuButton->setBackground(WindowsButtonBackground);
    WindowsMenuButton->setRolloverBackground(WindowsRolloverButtonBackground);
    WindowsMenuButton->setFocusedBackground(WindowsButtonBackground);
    WindowsMenuButton->setDisabledBackground(WindowsDisabledButtonBackground);
    WindowsMenuButton->setActiveBackground(WindowsActiveButtonBackground);

    //Opacity
    WindowsMenuButton->setOpacity(1.0);

    //Text
    WindowsMenuButton->setText("");
    WindowsMenuButton->setFont(WindowsFont);
    WindowsMenuButton->setAlignment(Vec2f(0.5f,0.5f));
    WindowsMenuButton->setTextColor(Color4f(0.0,0.0,0.0,1.0));
    WindowsMenuButton->setActiveTextColor(Color4f(0.0,0.0,0.0,1.0));
    WindowsMenuButton->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
    WindowsMenuButton->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
    WindowsMenuButton->setDisabledTextColor(WindowsDisabledTextColor);

    WindowsMenuButton->setActiveOffset(Vec2f(2,2));
    WindowsMenuButton->setDrawObjectToTextAlignment(Button::ALIGN_DRAW_OBJECT_LEFT_OF_TEXT);
    WindowsMenuButton->setDrawObjectToTextPadding(4.0f);


    /********Text Field********/
    ColorLayerRefPtr WindowsTextFieldBackground = ColorLayer::create();
    WindowsTextFieldBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));

    ColorLayerRefPtr WindowsDisabledTextFieldBackground = ColorLayer::create();
    WindowsDisabledTextFieldBackground->setColor(Color4f(.8, .8, .8, 1.0));

    LineBorderRefPtr WindowsTextFieldBorder = LineBorder::create();
    WindowsTextFieldBorder->setWidth(1);
    WindowsTextFieldBorder->setColor( Color4f(.498,.616,.725,1.0) );


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
    WindowsTextField->setAlignment(Vec2f(0.0f,0.5f));

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

    //Empty Description Text
    WindowsTextField->setEmptyDescTextColor(Color4f(0.5,0.5,0.5,1.0));
    WindowsTextField->setEmptyDescTextFont(WindowsFont);
    WindowsTextField->setEmptyDescText("");



    /********Password Field********/
    ColorLayerRefPtr WindowsPasswordFieldBackground = ColorLayer::create();
    WindowsPasswordFieldBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));

    ColorLayerRefPtr WindowsDisabledPasswordFieldBackground = ColorLayer::create();
    WindowsDisabledPasswordFieldBackground->setColor(Color4f(.8, .8, .8, 1.0));

    LineBorderRefPtr WindowsPasswordFieldBorder = LineBorder::create();
    WindowsPasswordFieldBorder->setWidth(1);
    WindowsPasswordFieldBorder->setColor( Color4f(.498,.616,.725,1.0) );


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
    WindowsPasswordField->setAlignment(Vec2f(0.0f,0.5f));

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

    //Empty Description Text
    WindowsPasswordField->setEmptyDescTextColor(Color4f(0.5,0.5,0.5,1.0));
    WindowsPasswordField->setEmptyDescTextFont(WindowsFont);
    WindowsPasswordField->setEmptyDescText("");


    /********Text Area********/
    ColorLayerRefPtr WindowsTextAreaBackground = ColorLayer::create();
    WindowsTextAreaBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));

    ColorLayerRefPtr WindowsDisabledTextAreaBackground = ColorLayer::create();
    WindowsDisabledTextAreaBackground->setColor(Color4f(.8, .8, .8, 1.0));

    LineBorderRefPtr WindowsTextAreaBorder = LineBorder::create();
    WindowsTextAreaBorder->setWidth(1);
    WindowsTextAreaBorder->setColor( Color4f(.498,.616,.725,1.0) );

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
    


    //************************** ToolTip*****************************
    //Default ToolTipBorder
    LineBorderRefPtr WindowsToolTipLineBorder = LineBorder::create();
    WindowsToolTipLineBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
    WindowsToolTipLineBorder->setWidth(1);


    ShadowBorderRefPtr WindowsToolTipBorder = OSG::ShadowBorder::create();
    WindowsToolTipBorder->setTopOffset(0);
    WindowsToolTipBorder->setBottomOffset(2);
    WindowsToolTipBorder->setLeftOffset(0);
    WindowsToolTipBorder->setRightOffset(2);
    WindowsToolTipBorder->setInsideBorder(WindowsToolTipLineBorder);
    WindowsToolTipBorder->setCornerRadius(3);
    WindowsToolTipBorder->setInternalColor(Color4f(0.0, 0.0, 0.0, 0.5));
    WindowsToolTipBorder->setEdgeColor(Color4f(0.0, 0.0, 0.0, 0.0));
    WindowsToolTipBorder->setInternalToEdgeColorLength(2);


    //Default ToolTipBackground
    ColorLayerRefPtr WindowsToolTipBackground = ColorLayer::create();
    WindowsToolTipBackground->setColor(Color4f(1.0,1.0,0.88,1.0));

    //Default ToolTip
    WindowsToolTip->setEnabled(true);
    WindowsToolTip->setVisible(true);

    WindowsToolTip->setConstraints(NULL);
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
    WindowsToolTip->setAlignment(Vec2f(0.5f,0.5f));
    WindowsToolTip->setTextColor(Color4f(0.0,0.0,0.0,1.0));
    

    //************************** MenuItem*****************************
    //Windows MenuItemBorder
    EmptyBorderRefPtr WindowsMenuItemBorder = EmptyBorder::create();

    //Windows MenuItemBackground
    ColorLayerRefPtr WindowsMenuItemBackground = ColorLayer::create();
    WindowsMenuItemBackground->setColor(Color4f(1.0,1.0,1.0,1.0));

    //Windows MenuItemBorder
    EmptyBorderRefPtr WindowsMenuItemSelectedBorder = EmptyBorder::create();

    //Windows MenuItemBackground
    ColorLayerRefPtr WindowsMenuItemSelectedBackground = ColorLayer::create();
    WindowsMenuItemSelectedBackground->setColor(Color4f(0.19,0.42,0.77,1.0));

    //Windows MenuItem
    WindowsMenuItem->setEnabled(true);
    WindowsMenuItem->setVisible(true);

    WindowsMenuItem->setConstraints(NULL);
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
    WindowsMenuItem->setAcceleratorKey(KeyEventDetails::KEY_NONE);

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
    WindowsMenuItem->setAlignment(Vec2f(0.0f,0.5f));
    WindowsMenuItem->setActiveOffset(Vec2f(0.0f,0.0f));
    

    //************************** ComponentMenuItem*****************************
    //Windows ComponentMenuItemBorder
    EmptyBorderRefPtr WindowsComponentMenuItemBorder = EmptyBorder::create();

    //Windows ComponentMenuItemBackground
    ColorLayerRefPtr WindowsComponentMenuItemBackground = ColorLayer::create();
    WindowsComponentMenuItemBackground->setColor(Color4f(1.0,1.0,1.0,1.0));

    //Windows ComponentMenuItemBorder
    EmptyBorderRefPtr WindowsComponentMenuItemSelectedBorder = EmptyBorder::create();

    //Windows ComponentMenuItemBackground
    ColorLayerRefPtr WindowsComponentMenuItemSelectedBackground = ColorLayer::create();
    WindowsComponentMenuItemSelectedBackground->setColor(Color4f(0.19,0.42,0.77,1.0));

    //Windows ComponentMenuItem
    WindowsComponentMenuItem->setEnabled(true);
    WindowsComponentMenuItem->setVisible(true);

    WindowsComponentMenuItem->setConstraints(NULL);
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
    WindowsComponentMenuItem->setAcceleratorKey(KeyEventDetails::KEY_NONE);

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
    WindowsComponentMenuItem->setAlignment(Vec2f(0.0f,0.5f));
    WindowsComponentMenuItem->setActiveOffset(Vec2f(0.0f,0.0f));
    

    //************************** Menu*****************************
    //Windows MenuBorder
    EmptyBorderRefPtr WindowsMenuBorder = EmptyBorder::create();

    //Windows MenuBackground
    ColorLayerRefPtr WindowsMenuBackground = ColorLayer::create();
    WindowsMenuBackground->setColor(Color4f(1.0,1.0,1.0,1.0));

    //Windows MenuBorder
    EmptyBorderRefPtr WindowsMenuSelectedBorder = EmptyBorder::create();

    //Windows MenuBackground
    ColorLayerRefPtr WindowsMenuSelectedBackground = ColorLayer::create();
    WindowsMenuSelectedBackground->setColor(Color4f(0.19,0.42,0.77,1.0));


    //Expanding Draw Object
    PolygonUIDrawObjectRefPtr MenuExpandablePolygon = PolygonUIDrawObject::create();
    MenuExpandablePolygon->setColor(Color4f(0.0,0.0,0.0,1.0));
    MenuExpandablePolygon->setOpacity(1.0);
    MenuExpandablePolygon->editMFVerticies()->push_back(Pnt2f(0,0));
    MenuExpandablePolygon->editMFVerticies()->push_back(Pnt2f(0,7));
    MenuExpandablePolygon->editMFVerticies()->push_back(Pnt2f(4,4));

    UIDrawObjectCanvasRefPtr defaultMenuDrawObject = UIDrawObjectCanvas::create();
    defaultMenuDrawObject->pushToDrawObjects(MenuExpandablePolygon);

    //Windows Menu
    WindowsMenu->setEnabled(true);
    WindowsMenu->setVisible(true);

    WindowsMenu->setConstraints(NULL);
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
    WindowsMenu->setAcceleratorKey(KeyEventDetails::KEY_NONE);

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
    WindowsMenu->setAlignment(Vec2f(0.0f,0.5f));

    //Expanding Draw Object
    WindowsMenu->setExpandDrawObject(defaultMenuDrawObject);
    

    //************************** PopupMenu*****************************
    //Windows PopupMenuBorder
    LineBorderRefPtr WindowsPopupMenuLineBorder = LineBorder::create();
    WindowsPopupMenuLineBorder->setColor(Color4f(0.67,0.66,0.60,1.0));
    WindowsPopupMenuLineBorder->setWidth(1);

    ShadowBorderRefPtr WindowsPopupMenuBorder = OSG::ShadowBorder::create();
    WindowsPopupMenuBorder->setTopOffset(0);
    WindowsPopupMenuBorder->setBottomOffset(4);
    WindowsPopupMenuBorder->setLeftOffset(0);
    WindowsPopupMenuBorder->setRightOffset(4);
    WindowsPopupMenuBorder->setInsideBorder(WindowsPopupMenuLineBorder);
    WindowsPopupMenuBorder->setCornerRadius(3);
    WindowsPopupMenuBorder->setInternalColor(Color4f(0.36, 0.36, 0.36, 0.5));
    WindowsPopupMenuBorder->setEdgeColor(Color4f(0.36, 0.36, 0.36, 0.0));
    WindowsPopupMenuBorder->setInternalToEdgeColorLength(3);

    //Windows PopupMenuBackground
    ColorLayerRefPtr WindowsPopupMenuBackground = ColorLayer::create();
    WindowsPopupMenuBackground->setColor(Color4f(1.0,1.0,1.0,1.0));


    //Windows PopupMenu Default Separator
    SeparatorRefPtr WindowsPopupMenuDefaultSeparator = Separator::create();
    WindowsPopupMenuDefaultSeparator->setSeparatorSize(1.0f);
    WindowsPopupMenuDefaultSeparator->setColor(Color4f(0.67,0.66,0.6,1.0));

    //Windows PopupMenu
    WindowsPopupMenu->setEnabled(true);
    WindowsPopupMenu->setVisible(false);

    WindowsPopupMenu->setConstraints(NULL);
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
    //WindowsPopupMenu->setAllInsets(2);

    WindowsPopupMenu->setDefaultSeparator(WindowsPopupMenuDefaultSeparator);
    

    //************************** ListGeneratedPopupMenu*****************************
    //Windows ListGeneratedPopupMenuBorder
    LineBorderRefPtr WindowsListGeneratedPopupMenuLineBorder = LineBorder::create();
    WindowsListGeneratedPopupMenuLineBorder->setColor(Color4f(0.67,0.66,0.60,1.0));
    WindowsListGeneratedPopupMenuLineBorder->setWidth(1);

    ShadowBorderRefPtr WindowsListGeneratedPopupMenuBorder = OSG::ShadowBorder::create();
    WindowsListGeneratedPopupMenuBorder->setTopOffset(0);
    WindowsListGeneratedPopupMenuBorder->setBottomOffset(4);
    WindowsListGeneratedPopupMenuBorder->setLeftOffset(0);
    WindowsListGeneratedPopupMenuBorder->setRightOffset(4);
    WindowsListGeneratedPopupMenuBorder->setInsideBorder(WindowsListGeneratedPopupMenuLineBorder);
    WindowsListGeneratedPopupMenuBorder->setCornerRadius(3);
    WindowsListGeneratedPopupMenuBorder->setInternalColor(Color4f(0.36, 0.36, 0.36, 0.5));
    WindowsListGeneratedPopupMenuBorder->setEdgeColor(Color4f(0.36, 0.36, 0.36, 0.0));
    WindowsListGeneratedPopupMenuBorder->setInternalToEdgeColorLength(3);

    //Windows ListGeneratedPopupMenuBackground
    ColorLayerRefPtr WindowsListGeneratedPopupMenuBackground = ColorLayer::create();
    WindowsListGeneratedPopupMenuBackground->setColor(Color4f(1.0,1.0,1.0,1.0));

    //Windows ListGeneratedPopupMenu
    WindowsListGeneratedPopupMenu->setEnabled(true);
    WindowsListGeneratedPopupMenu->setVisible(false);

    WindowsListGeneratedPopupMenu->setConstraints(NULL);
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
    
    //************************** MenuBar*****************************
    //Windows MenuBarBorder
    EmptyBorderRefPtr WindowsMenuBarBorder = EmptyBorder::create();

    //Windows MenuBarBackground
    ColorLayerRefPtr WindowsMenuBarBackground = ColorLayer::create();
    WindowsMenuBarBackground->setColor(Color4f(0.93,0.93,0.93,1.0));

    //Windows MenuBar
    WindowsMenuBar->setEnabled(true);
    WindowsMenuBar->setVisible(true);

    WindowsMenuBar->setConstraints(NULL);
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
    

    //************************** ScrollBar*****************************
    //Windows ScrollBarBorder
    EmptyBorderRefPtr WindowsScrollBarBorder = EmptyBorder::create();

    //Windows ScrollBarBackground
    EmptyLayerRefPtr WindowsScrollBarBackground = EmptyLayer::create();

    RoundedCornerLineBorderRefPtr WindowsWhiteCorneredBorder = RoundedCornerLineBorder::create();
    WindowsWhiteCorneredBorder->setWidth(1);
    WindowsWhiteCorneredBorder->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
    WindowsWhiteCorneredBorder->setCornerRadius(2);

    RoundedCornerLineBorderRefPtr WindowsBlueCorneredBorder = RoundedCornerLineBorder::create();
    WindowsBlueCorneredBorder->setWidth(1);
    WindowsBlueCorneredBorder->setColor(Color4f(0.49, 0.62, 0.83, 1.0));
    WindowsBlueCorneredBorder->setCornerRadius(2);

    RoundedCornerLineBorderRefPtr WindowsLightBlueCorneredBorder = RoundedCornerLineBorder::create();
    WindowsLightBlueCorneredBorder->setWidth(1);
    WindowsLightBlueCorneredBorder->setColor(Color4f(0.73, 0.80, 0.96, 1.0));
    WindowsLightBlueCorneredBorder->setCornerRadius(2);

    RoundedCornerLineBorderRefPtr WindowsDisabledCorneredBorder = RoundedCornerLineBorder::create();
    WindowsDisabledCorneredBorder->setWidth(1);
    WindowsDisabledCorneredBorder->setColor(Color4f(0.93,0.93,0.90,1.0));
    WindowsDisabledCorneredBorder->setCornerRadius(2);

    //Vertical Min Draw Object
    PolygonUIDrawObjectRefPtr WindowsScrollBarVerticalMinButtonDrawObject1 = PolygonUIDrawObject::create();
    WindowsScrollBarVerticalMinButtonDrawObject1->setColor(Color4f(0.3,0.38,0.52,1.0));
    WindowsScrollBarVerticalMinButtonDrawObject1->setOpacity(1.0);
    WindowsScrollBarVerticalMinButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(0,4));
    WindowsScrollBarVerticalMinButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(4,0));
    WindowsScrollBarVerticalMinButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(4,2));
    WindowsScrollBarVerticalMinButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(1,5));
    PolygonUIDrawObjectRefPtr WindowsScrollBarVerticalMinButtonDrawObject2 = PolygonUIDrawObject::create();
    WindowsScrollBarVerticalMinButtonDrawObject2->setColor(Color4f(0.3,0.38,0.52,1.0));
    WindowsScrollBarVerticalMinButtonDrawObject2->setOpacity(1.0);
    WindowsScrollBarVerticalMinButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(4,0));
    WindowsScrollBarVerticalMinButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(8,4));
    WindowsScrollBarVerticalMinButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(7,5));
    WindowsScrollBarVerticalMinButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(4,2));

    UIDrawObjectCanvasRefPtr WindowsScrollBarVerticalMinButtonCanvas = UIDrawObjectCanvas::create();
    WindowsScrollBarVerticalMinButtonCanvas->pushToDrawObjects(WindowsScrollBarVerticalMinButtonDrawObject1);
    WindowsScrollBarVerticalMinButtonCanvas->pushToDrawObjects(WindowsScrollBarVerticalMinButtonDrawObject2);

    //Vertical Min Button
    CompoundBorderRefPtr WindowsScrollBarButtonOuterBorder = CompoundBorder::create();
    WindowsScrollBarButtonOuterBorder->setInnerBorder(WindowsWhiteCorneredBorder);
    WindowsScrollBarButtonOuterBorder->setOuterBorder(WindowsBlueCorneredBorder);

    CompoundBorderRefPtr WindowsScrollBarButtonBorder = CompoundBorder::create();
    WindowsScrollBarButtonBorder->setInnerBorder(WindowsLightBlueCorneredBorder);
    WindowsScrollBarButtonBorder->setOuterBorder(WindowsScrollBarButtonOuterBorder);

    CompoundBorderRefPtr WindowsScrollBarButtonDisabledOuterBorder = CompoundBorder::create();
    WindowsScrollBarButtonDisabledOuterBorder->setInnerBorder(WindowsWhiteCorneredBorder);
    WindowsScrollBarButtonDisabledOuterBorder->setOuterBorder(WindowsDisabledCorneredBorder);

    CompoundBorderRefPtr WindowsScrollBarDisabledButtonBorder = CompoundBorder::create();
    WindowsScrollBarDisabledButtonBorder->setInnerBorder(WindowsDisabledCorneredBorder);
    WindowsScrollBarDisabledButtonBorder->setOuterBorder(WindowsScrollBarButtonDisabledOuterBorder);

    ColorLayerRefPtr WindowsScrollBarButtonBackground = ColorLayer::create();
    WindowsScrollBarButtonBackground->setColor(Color4f(0.76,0.84,0.99,1.0));

    ColorLayerRefPtr WindowsScrollBarRolloverButtonBackground = ColorLayer::create();
    WindowsScrollBarRolloverButtonBackground->setColor(Color4f(0.82,0.92,1.0,1.0));

    ColorLayerRefPtr WindowsScrollBarDisabledButtonBackground = ColorLayer::create();
    WindowsScrollBarDisabledButtonBackground->setColor(Color4f(0.93,0.93,0.90,1.0));

    ColorLayerRefPtr WindowsScrollBarActiveButtonBackground = ColorLayer::create();
    WindowsScrollBarActiveButtonBackground->setColor(Color4f(0.55,0.63,0.94,1.0));

    ButtonRefPtr WindowsScrollBarVerticalMinButton = Button::create();
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

    //Vertical Max Draw Object
    PolygonUIDrawObjectRefPtr WindowsScrollBarVerticalMaxButtonDrawObject1 = PolygonUIDrawObject::create();
    WindowsScrollBarVerticalMaxButtonDrawObject1->setColor(Color4f(0.3,0.38,0.52,1.0));
    WindowsScrollBarVerticalMaxButtonDrawObject1->setOpacity(1.0);
    WindowsScrollBarVerticalMaxButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(1,0));
    WindowsScrollBarVerticalMaxButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(4,3));
    WindowsScrollBarVerticalMaxButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(4,5));
    WindowsScrollBarVerticalMaxButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(0,1));
    PolygonUIDrawObjectRefPtr WindowsScrollBarVerticalMaxButtonDrawObject2 = PolygonUIDrawObject::create();
    WindowsScrollBarVerticalMaxButtonDrawObject2->setColor(Color4f(0.3,0.38,0.52,1.0));
    WindowsScrollBarVerticalMaxButtonDrawObject2->setOpacity(1.0);
    WindowsScrollBarVerticalMaxButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(4,3));
    WindowsScrollBarVerticalMaxButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(7,0));
    WindowsScrollBarVerticalMaxButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(8,1));
    WindowsScrollBarVerticalMaxButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(4,5));

    UIDrawObjectCanvasRefPtr WindowsScrollBarVerticalMaxButtonCanvas = UIDrawObjectCanvas::create();
    WindowsScrollBarVerticalMaxButtonCanvas->pushToDrawObjects(WindowsScrollBarVerticalMaxButtonDrawObject1);
    WindowsScrollBarVerticalMaxButtonCanvas->pushToDrawObjects(WindowsScrollBarVerticalMaxButtonDrawObject2);
    //Vertical Max Button
    ButtonRefPtr WindowsScrollBarVerticalMaxButton = Button::create();
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

    //Horizontal Min Draw Object
    PolygonUIDrawObjectRefPtr WindowsScrollBarHorizontalMinButtonDrawObject1 = PolygonUIDrawObject::create();
    WindowsScrollBarHorizontalMinButtonDrawObject1->setColor(Color4f(0.3,0.38,0.52,1.0));
    WindowsScrollBarHorizontalMinButtonDrawObject1->setOpacity(1.0);
    WindowsScrollBarHorizontalMinButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(0,4));
    WindowsScrollBarHorizontalMinButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(4,0));
    WindowsScrollBarHorizontalMinButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(5,1));
    WindowsScrollBarHorizontalMinButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(2,4));
    PolygonUIDrawObjectRefPtr WindowsScrollBarHorizontalMinButtonDrawObject2 = PolygonUIDrawObject::create();
    WindowsScrollBarHorizontalMinButtonDrawObject2->setColor(Color4f(0.3,0.38,0.52,1.0));
    WindowsScrollBarHorizontalMinButtonDrawObject2->setOpacity(1.0);
    WindowsScrollBarHorizontalMinButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(0,4));
    WindowsScrollBarHorizontalMinButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(2,4));
    WindowsScrollBarHorizontalMinButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(5,7));
    WindowsScrollBarHorizontalMinButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(4,8));

    UIDrawObjectCanvasRefPtr WindowsScrollBarHorizontalMinButtonCanvas = UIDrawObjectCanvas::create();
    WindowsScrollBarHorizontalMinButtonCanvas->pushToDrawObjects(WindowsScrollBarHorizontalMinButtonDrawObject1);
    WindowsScrollBarHorizontalMinButtonCanvas->pushToDrawObjects(WindowsScrollBarHorizontalMinButtonDrawObject2);

    //Horizontal Min Button
    ButtonRefPtr WindowsScrollBarHorizontalMinButton = Button::create();
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

    //Horizontal Max Draw Object
    PolygonUIDrawObjectRefPtr WindowsScrollBarHorizontalMaxButtonDrawObject1 = PolygonUIDrawObject::create();
    WindowsScrollBarHorizontalMaxButtonDrawObject1->setColor(Color4f(0.3,0.38,0.52,1.0));
    WindowsScrollBarHorizontalMaxButtonDrawObject1->setOpacity(1.0);
    WindowsScrollBarHorizontalMaxButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(0,1));
    WindowsScrollBarHorizontalMaxButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(1,0));
    WindowsScrollBarHorizontalMaxButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(5,4));
    WindowsScrollBarHorizontalMaxButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(3,4));
    PolygonUIDrawObjectRefPtr WindowsScrollBarHorizontalMaxButtonDrawObject2 = PolygonUIDrawObject::create();
    WindowsScrollBarHorizontalMaxButtonDrawObject2->setColor(Color4f(0.3,0.38,0.52,1.0));
    WindowsScrollBarHorizontalMaxButtonDrawObject2->setOpacity(1.0);
    WindowsScrollBarHorizontalMaxButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(3,4));
    WindowsScrollBarHorizontalMaxButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(5,4));
    WindowsScrollBarHorizontalMaxButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(1,8));
    WindowsScrollBarHorizontalMaxButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(0,7));

    UIDrawObjectCanvasRefPtr WindowsScrollBarHorizontalMaxButtonCanvas = UIDrawObjectCanvas::create();
    WindowsScrollBarHorizontalMaxButtonCanvas->pushToDrawObjects(WindowsScrollBarHorizontalMaxButtonDrawObject1);
    WindowsScrollBarHorizontalMaxButtonCanvas->pushToDrawObjects(WindowsScrollBarHorizontalMaxButtonDrawObject2);
    //Horizontal Max Button
    ButtonRefPtr WindowsScrollBarHorizontalMaxButton = Button::create();
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

    //Vertical Scroll Field
    //Vertical Scroll Field Border
    MatteBorderRefPtr WindowsVerticalScrollFieldBorder = MatteBorder::create();
    WindowsVerticalScrollFieldBorder->setLeftWidth(1);
    WindowsVerticalScrollFieldBorder->setRightWidth(1);
    WindowsVerticalScrollFieldBorder->setTopWidth(0);
    WindowsVerticalScrollFieldBorder->setBottomWidth(0);
    WindowsVerticalScrollFieldBorder->setColor(Color4f(0.93, 0.93, 0.9, 1.0));

    //Vertical Scroll Field Disabled Border
    BevelBorderRefPtr WindowsVerticalDisabledScrollFieldBorder = BevelBorder::create();
    WindowsVerticalDisabledScrollFieldBorder->setRaised(true);
    WindowsVerticalDisabledScrollFieldBorder->setWidth(1);
    WindowsVerticalDisabledScrollFieldBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
    WindowsVerticalDisabledScrollFieldBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
    WindowsVerticalDisabledScrollFieldBorder->setShadowInner(Color4f(0.85, 0.85, 0.85, 1.0));
    WindowsVerticalDisabledScrollFieldBorder->setShadowOuter(Color4f(0.65, 0.65, 0.65, 1.0));

    //Vertical Scroll Field Background
    GradientLayerRefPtr WindowsVerticalScrollFieldBackground = GradientLayer::create();
    WindowsVerticalScrollFieldBackground->editMFColors()->push_back(Color4f(0.95,0.95,0.93,1.0));
    WindowsVerticalScrollFieldBackground->editMFStops()->push_back(0.0);
    WindowsVerticalScrollFieldBackground->editMFColors()->push_back(Color4f(1.0,1.0,0.98,1.0));
    WindowsVerticalScrollFieldBackground->editMFStops()->push_back(1.0);
    WindowsVerticalScrollFieldBackground->setStartPosition(Vec2f(0.0f,0.0f));
    WindowsVerticalScrollFieldBackground->setEndPosition(Vec2f(1.0f,0.0f));

    //Vertical Scroll Field Disabled Background
    ColorLayerRefPtr WindowsVerticalDisabledScrollFieldBackground = ColorLayer::create();
    WindowsVerticalDisabledScrollFieldBackground->setColor(Color4f(1.0,1.0,1.0,1.0));

    ButtonRefPtr WindowsVerticalScrollFieldButton = Button::create();
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

    //Vertical Scroll Bar
    //Vertical Scroll Bar Border

    CompoundBorderRefPtr WindowsVerticalScrollBarDrawObjectOuterBorder = CompoundBorder::create();
    WindowsVerticalScrollBarDrawObjectOuterBorder->setInnerBorder(WindowsWhiteCorneredBorder);
    WindowsVerticalScrollBarDrawObjectOuterBorder->setOuterBorder(WindowsBlueCorneredBorder);

    CompoundBorderRefPtr WindowsVerticalScrollBarDrawObjectBorder = CompoundBorder::create();
    WindowsVerticalScrollBarDrawObjectBorder->setInnerBorder(WindowsLightBlueCorneredBorder);
    WindowsVerticalScrollBarDrawObjectBorder->setOuterBorder(WindowsVerticalScrollBarDrawObjectOuterBorder);

    //Vertical Scroll Bar Disabled Border
    BevelBorderRefPtr WindowsDisabledVerticalScrollBarDrawObjectBorder = BevelBorder::create();
    WindowsDisabledVerticalScrollBarDrawObjectBorder->setRaised(true);
    WindowsDisabledVerticalScrollBarDrawObjectBorder->setWidth(2);
    WindowsDisabledVerticalScrollBarDrawObjectBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
    WindowsDisabledVerticalScrollBarDrawObjectBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
    WindowsDisabledVerticalScrollBarDrawObjectBorder->setShadowInner(Color4f(0.85, 0.85, 0.85, 1.0));
    WindowsDisabledVerticalScrollBarDrawObjectBorder->setShadowOuter(Color4f(0.65, 0.65, 0.65, 1.0));

    //Vertical Scroll Bar Background
    GradientLayerRefPtr WindowsVerticalScrollBarDrawObjectBackground = GradientLayer::create();
    WindowsVerticalScrollBarDrawObjectBackground->editMFColors()->push_back(Color4f(0.79,0.85,0.99,1.0));
    WindowsVerticalScrollBarDrawObjectBackground->editMFStops()->push_back(0.0);
    WindowsVerticalScrollBarDrawObjectBackground->editMFColors()->push_back(Color4f(0.73,0.8,0.98,1.0));
    WindowsVerticalScrollBarDrawObjectBackground->editMFStops()->push_back(1.0);
    WindowsVerticalScrollBarDrawObjectBackground->setStartPosition(Vec2f(0.0f,0.0f));
    WindowsVerticalScrollBarDrawObjectBackground->setEndPosition(Vec2f(1.0f,0.0f));

    //Vertical Scroll Bar Disabled Background
    ColorLayerRefPtr WindowsDisabledVerticalScrollBarDrawObjectBackground = ColorLayer::create();
    WindowsDisabledVerticalScrollBarDrawObjectBackground->setColor(Color4f(1.0,1.0,1.0,1.0));

    //Vertical Scroll Bar Rollover Background
    GradientLayerRefPtr WindowsRolloverVerticalScrollBarDrawObjectBackground = GradientLayer::create();
    WindowsRolloverVerticalScrollBarDrawObjectBackground->editMFColors()->push_back(Color4f(0.84,0.91,1.0,1.0));
    WindowsRolloverVerticalScrollBarDrawObjectBackground->editMFStops()->push_back(0.0);
    WindowsRolloverVerticalScrollBarDrawObjectBackground->editMFColors()->push_back(Color4f(0.80,0.88,1.0,1.0));
    WindowsRolloverVerticalScrollBarDrawObjectBackground->editMFStops()->push_back(1.0);
    WindowsRolloverVerticalScrollBarDrawObjectBackground->setStartPosition(Vec2f(0.0f,0.0f));
    WindowsRolloverVerticalScrollBarDrawObjectBackground->setEndPosition(Vec2f(1.0f,0.0f));

    //Vertical Scroll Bar Active Background
    GradientLayerRefPtr WindowsActiveVerticalScrollBarDrawObjectBackground = GradientLayer::create();
    WindowsActiveVerticalScrollBarDrawObjectBackground->editMFColors()->push_back(Color4f(0.84,0.91,1.0,1.0));
    WindowsActiveVerticalScrollBarDrawObjectBackground->editMFStops()->push_back(0.0);
    WindowsActiveVerticalScrollBarDrawObjectBackground->editMFColors()->push_back(Color4f(0.80,0.88,1.0,1.0));
    WindowsActiveVerticalScrollBarDrawObjectBackground->editMFStops()->push_back(1.0);
    WindowsActiveVerticalScrollBarDrawObjectBackground->setStartPosition(Vec2f(0.0f,0.0f));
    WindowsActiveVerticalScrollBarDrawObjectBackground->setEndPosition(Vec2f(0.0f,1.0f));

    //Vertical Scroll Bar Center Ridges
    RectUIDrawObjectRefPtr VerticalWhiteRidge1 = RectUIDrawObject::create();
    VerticalWhiteRidge1->setTopLeft(Pnt2f(0,0));
    VerticalWhiteRidge1->setBottomRight(Pnt2f(6,1));
    VerticalWhiteRidge1->setColor(Color4f(0.93,0.96,1.0,1.0));

    RectUIDrawObjectRefPtr VerticalWhiteRidge2 = RectUIDrawObject::create();
    VerticalWhiteRidge2->setTopLeft(Pnt2f(0,2));
    VerticalWhiteRidge2->setBottomRight(Pnt2f(6,3));
    VerticalWhiteRidge2->setColor(Color4f(0.93,0.96,1.0,1.0));

    RectUIDrawObjectRefPtr VerticalWhiteRidge3 = RectUIDrawObject::create();
    VerticalWhiteRidge3->setTopLeft(Pnt2f(0,4));
    VerticalWhiteRidge3->setBottomRight(Pnt2f(6,5));
    VerticalWhiteRidge3->setColor(Color4f(0.93,0.96,1.0,1.0));

    RectUIDrawObjectRefPtr VerticalWhiteRidge4 = RectUIDrawObject::create();
    VerticalWhiteRidge4->setTopLeft(Pnt2f(0,6));
    VerticalWhiteRidge4->setBottomRight(Pnt2f(6,7));
    VerticalWhiteRidge4->setColor(Color4f(0.93,0.96,1.0,1.0));

    RectUIDrawObjectRefPtr VerticalBlueRidge1 = RectUIDrawObject::create();
    VerticalBlueRidge1->setTopLeft(Pnt2f(1,1));
    VerticalBlueRidge1->setBottomRight(Pnt2f(7,2));
    VerticalBlueRidge1->setColor(Color4f(0.55,0.69,0.97,1.0));

    RectUIDrawObjectRefPtr VerticalBlueRidge2 = RectUIDrawObject::create();
    VerticalBlueRidge2->setTopLeft(Pnt2f(1,3));
    VerticalBlueRidge2->setBottomRight(Pnt2f(7,4));
    VerticalBlueRidge2->setColor(Color4f(0.55,0.69,0.97,1.0));

    RectUIDrawObjectRefPtr VerticalBlueRidge3 = RectUIDrawObject::create();
    VerticalBlueRidge3->setTopLeft(Pnt2f(1,5));
    VerticalBlueRidge3->setBottomRight(Pnt2f(7,6));
    VerticalBlueRidge3->setColor(Color4f(0.55,0.69,0.97,1.0));

    RectUIDrawObjectRefPtr VerticalBlueRidge4 = RectUIDrawObject::create();
    VerticalBlueRidge4->setTopLeft(Pnt2f(1,7));
    VerticalBlueRidge4->setBottomRight(Pnt2f(7,8));
    VerticalBlueRidge4->setColor(Color4f(0.55,0.69,0.97,1.0));

    UIDrawObjectCanvasRefPtr WindowsVerticalScrollBarRidges = UIDrawObjectCanvas::create();
    WindowsVerticalScrollBarRidges->pushToDrawObjects(VerticalWhiteRidge1);
    WindowsVerticalScrollBarRidges->pushToDrawObjects(VerticalBlueRidge1);
    WindowsVerticalScrollBarRidges->pushToDrawObjects(VerticalWhiteRidge2);
    WindowsVerticalScrollBarRidges->pushToDrawObjects(VerticalBlueRidge2);
    WindowsVerticalScrollBarRidges->pushToDrawObjects(VerticalWhiteRidge3);
    WindowsVerticalScrollBarRidges->pushToDrawObjects(VerticalBlueRidge3);
    WindowsVerticalScrollBarRidges->pushToDrawObjects(VerticalWhiteRidge4);
    WindowsVerticalScrollBarRidges->pushToDrawObjects(VerticalBlueRidge4);

    //Vertical Active Scroll Bar Center Ridges
    RectUIDrawObjectRefPtr VerticalActiveWhiteRidge1 = RectUIDrawObject::create();
    VerticalActiveWhiteRidge1->setTopLeft(Pnt2f(0,0));
    VerticalActiveWhiteRidge1->setBottomRight(Pnt2f(6,1));
    VerticalActiveWhiteRidge1->setColor(Color4f(0.81,0.87,0.99,1.0));

    RectUIDrawObjectRefPtr VerticalActiveWhiteRidge2 = RectUIDrawObject::create();
    VerticalActiveWhiteRidge2->setTopLeft(Pnt2f(0,2));
    VerticalActiveWhiteRidge2->setBottomRight(Pnt2f(6,3));
    VerticalActiveWhiteRidge2->setColor(Color4f(0.81,0.87,0.99,1.0));

    RectUIDrawObjectRefPtr VerticalActiveWhiteRidge3 = RectUIDrawObject::create();
    VerticalActiveWhiteRidge3->setTopLeft(Pnt2f(0,4));
    VerticalActiveWhiteRidge3->setBottomRight(Pnt2f(6,5));
    VerticalActiveWhiteRidge3->setColor(Color4f(0.81,0.87,0.99,1.0));

    RectUIDrawObjectRefPtr VerticalActiveWhiteRidge4 = RectUIDrawObject::create();
    VerticalActiveWhiteRidge4->setTopLeft(Pnt2f(0,6));
    VerticalActiveWhiteRidge4->setBottomRight(Pnt2f(6,7));
    VerticalActiveWhiteRidge4->setColor(Color4f(0.81,0.87,0.99,1.0));

    RectUIDrawObjectRefPtr VerticalActiveBlueRidge1 = RectUIDrawObject::create();
    VerticalActiveBlueRidge1->setTopLeft(Pnt2f(1,1));
    VerticalActiveBlueRidge1->setBottomRight(Pnt2f(7,2));
    VerticalActiveBlueRidge1->setColor(Color4f(0.51,0.62,0.85,1.0));

    RectUIDrawObjectRefPtr VerticalActiveBlueRidge2 = RectUIDrawObject::create();
    VerticalActiveBlueRidge2->setTopLeft(Pnt2f(1,3));
    VerticalActiveBlueRidge2->setBottomRight(Pnt2f(7,4));
    VerticalActiveBlueRidge2->setColor(Color4f(0.51,0.62,0.85,1.0));

    RectUIDrawObjectRefPtr VerticalActiveBlueRidge3 = RectUIDrawObject::create();
    VerticalActiveBlueRidge3->setTopLeft(Pnt2f(1,5));
    VerticalActiveBlueRidge3->setBottomRight(Pnt2f(7,6));
    VerticalActiveBlueRidge3->setColor(Color4f(0.51,0.62,0.85,1.0));

    RectUIDrawObjectRefPtr VerticalActiveBlueRidge4 = RectUIDrawObject::create();
    VerticalActiveBlueRidge4->setTopLeft(Pnt2f(1,7));
    VerticalActiveBlueRidge4->setBottomRight(Pnt2f(7,8));
    VerticalActiveBlueRidge4->setColor(Color4f(0.51,0.62,0.85,1.0));

    UIDrawObjectCanvasRefPtr WindowsVerticalActiveScrollBarRidges = UIDrawObjectCanvas::create();
    WindowsVerticalActiveScrollBarRidges->pushToDrawObjects(VerticalActiveWhiteRidge1);
    WindowsVerticalActiveScrollBarRidges->pushToDrawObjects(VerticalActiveBlueRidge1);
    WindowsVerticalActiveScrollBarRidges->pushToDrawObjects(VerticalActiveWhiteRidge2);
    WindowsVerticalActiveScrollBarRidges->pushToDrawObjects(VerticalActiveBlueRidge2);
    WindowsVerticalActiveScrollBarRidges->pushToDrawObjects(VerticalActiveWhiteRidge3);
    WindowsVerticalActiveScrollBarRidges->pushToDrawObjects(VerticalActiveBlueRidge3);
    WindowsVerticalActiveScrollBarRidges->pushToDrawObjects(VerticalActiveWhiteRidge4);
    WindowsVerticalActiveScrollBarRidges->pushToDrawObjects(VerticalActiveBlueRidge4);

    //Vertical Rollover Scroll Bar Center Ridges
    RectUIDrawObjectRefPtr VerticalRolloverWhiteRidge1 = RectUIDrawObject::create();
    VerticalRolloverWhiteRidge1->setTopLeft(Pnt2f(0,0));
    VerticalRolloverWhiteRidge1->setBottomRight(Pnt2f(6,1));
    VerticalRolloverWhiteRidge1->setColor(Color4f(0.99,0.99,1.0,1.0));

    RectUIDrawObjectRefPtr VerticalRolloverWhiteRidge2 = RectUIDrawObject::create();
    VerticalRolloverWhiteRidge2->setTopLeft(Pnt2f(0,2));
    VerticalRolloverWhiteRidge2->setBottomRight(Pnt2f(6,3));
    VerticalRolloverWhiteRidge2->setColor(Color4f(0.99,0.99,1.0,1.0));

    RectUIDrawObjectRefPtr VerticalRolloverWhiteRidge3 = RectUIDrawObject::create();
    VerticalRolloverWhiteRidge3->setTopLeft(Pnt2f(0,4));
    VerticalRolloverWhiteRidge3->setBottomRight(Pnt2f(6,5));
    VerticalRolloverWhiteRidge3->setColor(Color4f(0.99,0.99,1.0,1.0));

    RectUIDrawObjectRefPtr VerticalRolloverWhiteRidge4 = RectUIDrawObject::create();
    VerticalRolloverWhiteRidge4->setTopLeft(Pnt2f(0,6));
    VerticalRolloverWhiteRidge4->setBottomRight(Pnt2f(6,7));
    VerticalRolloverWhiteRidge4->setColor(Color4f(0.99,0.99,1.0,1.0));

    RectUIDrawObjectRefPtr VerticalRolloverBlueRidge1 = RectUIDrawObject::create();
    VerticalRolloverBlueRidge1->setTopLeft(Pnt2f(1,1));
    VerticalRolloverBlueRidge1->setBottomRight(Pnt2f(7,2));
    VerticalRolloverBlueRidge1->setColor(Color4f(0.61,0.77,1.0,1.0));

    RectUIDrawObjectRefPtr VerticalRolloverBlueRidge2 = RectUIDrawObject::create();
    VerticalRolloverBlueRidge2->setTopLeft(Pnt2f(1,3));
    VerticalRolloverBlueRidge2->setBottomRight(Pnt2f(7,4));
    VerticalRolloverBlueRidge2->setColor(Color4f(0.61,0.77,1.0,1.0));

    RectUIDrawObjectRefPtr VerticalRolloverBlueRidge3 = RectUIDrawObject::create();
    VerticalRolloverBlueRidge3->setTopLeft(Pnt2f(1,5));
    VerticalRolloverBlueRidge3->setBottomRight(Pnt2f(7,6));
    VerticalRolloverBlueRidge3->setColor(Color4f(0.61,0.77,1.0,1.0));

    RectUIDrawObjectRefPtr VerticalRolloverBlueRidge4 = RectUIDrawObject::create();
    VerticalRolloverBlueRidge4->setTopLeft(Pnt2f(1,7));
    VerticalRolloverBlueRidge4->setBottomRight(Pnt2f(7,8));
    VerticalRolloverBlueRidge4->setColor(Color4f(0.61,0.77,1.0,1.0));

    UIDrawObjectCanvasRefPtr WindowsVerticalRolloverScrollBarRidges = UIDrawObjectCanvas::create();
    WindowsVerticalRolloverScrollBarRidges->pushToDrawObjects(VerticalRolloverWhiteRidge1);
    WindowsVerticalRolloverScrollBarRidges->pushToDrawObjects(VerticalRolloverBlueRidge1);
    WindowsVerticalRolloverScrollBarRidges->pushToDrawObjects(VerticalRolloverWhiteRidge2);
    WindowsVerticalRolloverScrollBarRidges->pushToDrawObjects(VerticalRolloverBlueRidge2);
    WindowsVerticalRolloverScrollBarRidges->pushToDrawObjects(VerticalRolloverWhiteRidge3);
    WindowsVerticalRolloverScrollBarRidges->pushToDrawObjects(VerticalRolloverBlueRidge3);
    WindowsVerticalRolloverScrollBarRidges->pushToDrawObjects(VerticalRolloverWhiteRidge4);
    WindowsVerticalRolloverScrollBarRidges->pushToDrawObjects(VerticalRolloverBlueRidge4);

    ButtonRefPtr WindowsVerticalScrollBarDrawObject = Button::create();
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

    WindowsVerticalScrollBarDrawObject->setAlignment(Vec2f(0.5f,0.5f));
    WindowsVerticalScrollBarDrawObject->setActiveOffset(Vec2f(0,0));

    WindowsVerticalScrollBarDrawObject->setDrawObject(WindowsVerticalScrollBarRidges);
    WindowsVerticalScrollBarDrawObject->setActiveDrawObject(WindowsVerticalActiveScrollBarRidges);
    WindowsVerticalScrollBarDrawObject->setFocusedDrawObject(WindowsVerticalScrollBarRidges);
    WindowsVerticalScrollBarDrawObject->setRolloverDrawObject(WindowsVerticalRolloverScrollBarRidges);
    WindowsVerticalScrollBarDrawObject->setDisabledDrawObject(WindowsVerticalScrollBarRidges);

    //Horizontal Scroll Field
    //Horizontal Scroll Field Border
    MatteBorderRefPtr WindowsHorizontalScrollFieldBorder = MatteBorder::create();
    WindowsHorizontalScrollFieldBorder->setLeftWidth(0);
    WindowsHorizontalScrollFieldBorder->setRightWidth(0);
    WindowsHorizontalScrollFieldBorder->setTopWidth(1);
    WindowsHorizontalScrollFieldBorder->setBottomWidth(1);
    WindowsHorizontalScrollFieldBorder->setColor(Color4f(0.93, 0.93, 0.9, 1.0));

    //Horizontal Scroll Field Disabled Border
    BevelBorderRefPtr WindowsHorizontalDisabledScrollFieldBorder = BevelBorder::create();
    WindowsHorizontalDisabledScrollFieldBorder->setRaised(true);
    WindowsHorizontalDisabledScrollFieldBorder->setWidth(1);
    WindowsHorizontalDisabledScrollFieldBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
    WindowsHorizontalDisabledScrollFieldBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
    WindowsHorizontalDisabledScrollFieldBorder->setShadowInner(Color4f(0.85, 0.85, 0.85, 1.0));
    WindowsHorizontalDisabledScrollFieldBorder->setShadowOuter(Color4f(0.65, 0.65, 0.65, 1.0));

    //Horizontal Scroll Field Background
    GradientLayerRefPtr WindowsHorizontalScrollFieldBackground = GradientLayer::create();
    WindowsHorizontalScrollFieldBackground->editMFColors()->push_back(Color4f(0.95,0.95,0.93,1.0));
    WindowsHorizontalScrollFieldBackground->editMFStops()->push_back(0.0);
    WindowsHorizontalScrollFieldBackground->editMFColors()->push_back(Color4f(1.0,1.0,0.98,1.0));
    WindowsHorizontalScrollFieldBackground->editMFStops()->push_back(1.0);
    WindowsHorizontalScrollFieldBackground->setStartPosition(Vec2f(0.0f,0.0f));
    WindowsHorizontalScrollFieldBackground->setEndPosition(Vec2f(0.0f,1.0f));

    //Horizontal Scroll Field Disabled Background
    ColorLayerRefPtr WindowsHorizontalDisabledScrollFieldBackground = ColorLayer::create();
    WindowsHorizontalDisabledScrollFieldBackground->setColor(Color4f(1.0,1.0,1.0,1.0));

    ButtonRefPtr WindowsHorizontalScrollFieldButton = Button::create();
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

    //Horizontal Scroll Bar
    //Horizontal Scroll Bar Border
    CompoundBorderRefPtr WindowsHorizontalScrollBarDrawObjectBorder = CompoundBorder::create();
    WindowsHorizontalScrollBarDrawObjectBorder->setInnerBorder(WindowsWhiteCorneredBorder);
    WindowsHorizontalScrollBarDrawObjectBorder->setOuterBorder(WindowsBlueCorneredBorder);

    //Horizontal Scroll Bar Disabled Border
    BevelBorderRefPtr WindowsDisabledHorizontalScrollBarDrawObjectBorder = BevelBorder::create();
    WindowsDisabledHorizontalScrollBarDrawObjectBorder->setRaised(true);
    WindowsDisabledHorizontalScrollBarDrawObjectBorder->setWidth(2);
    WindowsDisabledHorizontalScrollBarDrawObjectBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
    WindowsDisabledHorizontalScrollBarDrawObjectBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
    WindowsDisabledHorizontalScrollBarDrawObjectBorder->setShadowInner(Color4f(0.85, 0.85, 0.85, 1.0));
    WindowsDisabledHorizontalScrollBarDrawObjectBorder->setShadowOuter(Color4f(0.65, 0.65, 0.65, 1.0));

    //Horizontal Scroll Bar Background
    GradientLayerRefPtr WindowsHorizontalScrollBarDrawObjectBackground = GradientLayer::create();
    WindowsHorizontalScrollBarDrawObjectBackground->editMFColors()->push_back(Color4f(0.79,0.85,0.99,1.0));
    WindowsHorizontalScrollBarDrawObjectBackground->editMFStops()->push_back(0.0);
    WindowsHorizontalScrollBarDrawObjectBackground->editMFColors()->push_back(Color4f(0.73,0.8,0.98,1.0));
    WindowsHorizontalScrollBarDrawObjectBackground->editMFStops()->push_back(1.0);
    WindowsHorizontalScrollBarDrawObjectBackground->setStartPosition(Vec2f(0.0f,0.0f));
    WindowsHorizontalScrollBarDrawObjectBackground->setEndPosition(Vec2f(0.0f,1.0f));

    //Horizontal Scroll Bar Disabled Background
    ColorLayerRefPtr WindowsDisabledHorizontalScrollBarDrawObjectBackground = ColorLayer::create();
    WindowsDisabledHorizontalScrollBarDrawObjectBackground->setColor(Color4f(1.0,1.0,1.0,1.0));

    //Horizontal Scroll Bar Rollover Background
    GradientLayerRefPtr WindowsRolloverHorizontalScrollBarDrawObjectBackground = GradientLayer::create();
    WindowsRolloverHorizontalScrollBarDrawObjectBackground->editMFColors()->push_back(Color4f(0.84,0.91,1.0,1.0));
    WindowsRolloverHorizontalScrollBarDrawObjectBackground->editMFStops()->push_back(0.0);
    WindowsRolloverHorizontalScrollBarDrawObjectBackground->editMFColors()->push_back(Color4f(0.80,0.88,1.0,1.0));
    WindowsRolloverHorizontalScrollBarDrawObjectBackground->editMFStops()->push_back(1.0);
    WindowsRolloverHorizontalScrollBarDrawObjectBackground->setStartPosition(Vec2f(0.0f,0.0f));
    WindowsRolloverHorizontalScrollBarDrawObjectBackground->setEndPosition(Vec2f(0.0f,1.0f));

    //Horizontal Scroll Bar Active Background
    GradientLayerRefPtr WindowsActiveHorizontalScrollBarDrawObjectBackground = GradientLayer::create();
    WindowsActiveHorizontalScrollBarDrawObjectBackground->editMFColors()->push_back(Color4f(0.84,0.91,1.0,1.0));
    WindowsActiveHorizontalScrollBarDrawObjectBackground->editMFStops()->push_back(0.0);
    WindowsActiveHorizontalScrollBarDrawObjectBackground->editMFColors()->push_back(Color4f(0.80,0.88,1.0,1.0));
    WindowsActiveHorizontalScrollBarDrawObjectBackground->editMFStops()->push_back(1.0);
    WindowsActiveHorizontalScrollBarDrawObjectBackground->setStartPosition(Vec2f(0.0f,0.0f));
    WindowsActiveHorizontalScrollBarDrawObjectBackground->setEndPosition(Vec2f(0.0f,1.0f));

    //Horizontal Scroll Bar Center Ridges
    RectUIDrawObjectRefPtr HorizontalWhiteRidge1 = RectUIDrawObject::create();
    HorizontalWhiteRidge1->setTopLeft(Pnt2f(0,0));
    HorizontalWhiteRidge1->setBottomRight(Pnt2f(1,6));
    HorizontalWhiteRidge1->setColor(Color4f(0.93,0.96,1.0,1.0));

    RectUIDrawObjectRefPtr HorizontalWhiteRidge2 = RectUIDrawObject::create();
    HorizontalWhiteRidge2->setTopLeft(Pnt2f(2,0));
    HorizontalWhiteRidge2->setBottomRight(Pnt2f(3,6));
    HorizontalWhiteRidge2->setColor(Color4f(0.93,0.96,1.0,1.0));

    RectUIDrawObjectRefPtr HorizontalWhiteRidge3 = RectUIDrawObject::create();
    HorizontalWhiteRidge3->setTopLeft(Pnt2f(4,0));
    HorizontalWhiteRidge3->setBottomRight(Pnt2f(5,6));
    HorizontalWhiteRidge3->setColor(Color4f(0.93,0.96,1.0,1.0));

    RectUIDrawObjectRefPtr HorizontalWhiteRidge4 = RectUIDrawObject::create();
    HorizontalWhiteRidge4->setTopLeft(Pnt2f(6,0));
    HorizontalWhiteRidge4->setBottomRight(Pnt2f(7,6));
    HorizontalWhiteRidge4->setColor(Color4f(0.93,0.96,1.0,1.0));

    RectUIDrawObjectRefPtr HorizontalBlueRidge1 = RectUIDrawObject::create();
    HorizontalBlueRidge1->setTopLeft(Pnt2f(1,1));
    HorizontalBlueRidge1->setBottomRight(Pnt2f(2,7));
    HorizontalBlueRidge1->setColor(Color4f(0.55,0.69,0.97,1.0));

    RectUIDrawObjectRefPtr HorizontalBlueRidge2 = RectUIDrawObject::create();
    HorizontalBlueRidge2->setTopLeft(Pnt2f(3,1));
    HorizontalBlueRidge2->setBottomRight(Pnt2f(4,7));
    HorizontalBlueRidge2->setColor(Color4f(0.55,0.69,0.97,1.0));

    RectUIDrawObjectRefPtr HorizontalBlueRidge3 = RectUIDrawObject::create();
    HorizontalBlueRidge3->setTopLeft(Pnt2f(5,1));
    HorizontalBlueRidge3->setBottomRight(Pnt2f(6,7));
    HorizontalBlueRidge3->setColor(Color4f(0.55,0.69,0.97,1.0));

    RectUIDrawObjectRefPtr HorizontalBlueRidge4 = RectUIDrawObject::create();
    HorizontalBlueRidge4->setTopLeft(Pnt2f(7,1));
    HorizontalBlueRidge4->setBottomRight(Pnt2f(8,7));
    HorizontalBlueRidge4->setColor(Color4f(0.55,0.69,0.97,1.0));

    UIDrawObjectCanvasRefPtr WindowsHorizontalScrollBarRidges = UIDrawObjectCanvas::create();
    WindowsHorizontalScrollBarRidges->pushToDrawObjects(HorizontalWhiteRidge1);
    WindowsHorizontalScrollBarRidges->pushToDrawObjects(HorizontalBlueRidge1);
    WindowsHorizontalScrollBarRidges->pushToDrawObjects(HorizontalWhiteRidge2);
    WindowsHorizontalScrollBarRidges->pushToDrawObjects(HorizontalBlueRidge2);
    WindowsHorizontalScrollBarRidges->pushToDrawObjects(HorizontalWhiteRidge3);
    WindowsHorizontalScrollBarRidges->pushToDrawObjects(HorizontalBlueRidge3);
    WindowsHorizontalScrollBarRidges->pushToDrawObjects(HorizontalWhiteRidge4);
    WindowsHorizontalScrollBarRidges->pushToDrawObjects(HorizontalBlueRidge4);

    //Horizontal Active Scroll Bar Center Ridges
    RectUIDrawObjectRefPtr HorizontalActiveWhiteRidge1 = RectUIDrawObject::create();
    HorizontalActiveWhiteRidge1->setTopLeft(Pnt2f(0,0));
    HorizontalActiveWhiteRidge1->setBottomRight(Pnt2f(1,6));
    HorizontalActiveWhiteRidge1->setColor(Color4f(0.81,0.87,0.99,1.0));

    RectUIDrawObjectRefPtr HorizontalActiveWhiteRidge2 = RectUIDrawObject::create();
    HorizontalActiveWhiteRidge2->setTopLeft(Pnt2f(2,0));
    HorizontalActiveWhiteRidge2->setBottomRight(Pnt2f(3,6));
    HorizontalActiveWhiteRidge2->setColor(Color4f(0.81,0.87,0.99,1.0));

    RectUIDrawObjectRefPtr HorizontalActiveWhiteRidge3 = RectUIDrawObject::create();
    HorizontalActiveWhiteRidge3->setTopLeft(Pnt2f(4,0));
    HorizontalActiveWhiteRidge3->setBottomRight(Pnt2f(5,6));
    HorizontalActiveWhiteRidge3->setColor(Color4f(0.81,0.87,0.99,1.0));

    RectUIDrawObjectRefPtr HorizontalActiveWhiteRidge4 = RectUIDrawObject::create();
    HorizontalActiveWhiteRidge4->setTopLeft(Pnt2f(6,0));
    HorizontalActiveWhiteRidge4->setBottomRight(Pnt2f(7,6));
    HorizontalActiveWhiteRidge4->setColor(Color4f(0.81,0.87,0.99,1.0));

    RectUIDrawObjectRefPtr HorizontalActiveBlueRidge1 = RectUIDrawObject::create();
    HorizontalActiveBlueRidge1->setTopLeft(Pnt2f(1,1));
    HorizontalActiveBlueRidge1->setBottomRight(Pnt2f(2,7));
    HorizontalActiveBlueRidge1->setColor(Color4f(0.51,0.62,0.85,1.0));

    RectUIDrawObjectRefPtr HorizontalActiveBlueRidge2 = RectUIDrawObject::create();
    HorizontalActiveBlueRidge2->setTopLeft(Pnt2f(3,1));
    HorizontalActiveBlueRidge2->setBottomRight(Pnt2f(4,7));
    HorizontalActiveBlueRidge2->setColor(Color4f(0.51,0.62,0.85,1.0));

    RectUIDrawObjectRefPtr HorizontalActiveBlueRidge3 = RectUIDrawObject::create();
    HorizontalActiveBlueRidge3->setTopLeft(Pnt2f(5,1));
    HorizontalActiveBlueRidge3->setBottomRight(Pnt2f(6,7));
    HorizontalActiveBlueRidge3->setColor(Color4f(0.51,0.62,0.85,1.0));

    RectUIDrawObjectRefPtr HorizontalActiveBlueRidge4 = RectUIDrawObject::create();
    HorizontalActiveBlueRidge4->setTopLeft(Pnt2f(7,1));
    HorizontalActiveBlueRidge4->setBottomRight(Pnt2f(8,7));
    HorizontalActiveBlueRidge4->setColor(Color4f(0.51,0.62,0.85,1.0));

    UIDrawObjectCanvasRefPtr WindowsHorizontalActiveScrollBarRidges = UIDrawObjectCanvas::create();
    WindowsHorizontalActiveScrollBarRidges->pushToDrawObjects(HorizontalActiveWhiteRidge1);
    WindowsHorizontalActiveScrollBarRidges->pushToDrawObjects(HorizontalActiveBlueRidge1);
    WindowsHorizontalActiveScrollBarRidges->pushToDrawObjects(HorizontalActiveWhiteRidge2);
    WindowsHorizontalActiveScrollBarRidges->pushToDrawObjects(HorizontalActiveBlueRidge2);
    WindowsHorizontalActiveScrollBarRidges->pushToDrawObjects(HorizontalActiveWhiteRidge3);
    WindowsHorizontalActiveScrollBarRidges->pushToDrawObjects(HorizontalActiveBlueRidge3);
    WindowsHorizontalActiveScrollBarRidges->pushToDrawObjects(HorizontalActiveWhiteRidge4);
    WindowsHorizontalActiveScrollBarRidges->pushToDrawObjects(HorizontalActiveBlueRidge4);

    //Horizontal Rollover Scroll Bar Center Ridges
    RectUIDrawObjectRefPtr HorizontalRolloverWhiteRidge1 = RectUIDrawObject::create();
    HorizontalRolloverWhiteRidge1->setTopLeft(Pnt2f(0,0));
    HorizontalRolloverWhiteRidge1->setBottomRight(Pnt2f(1,6));
    HorizontalRolloverWhiteRidge1->setColor(Color4f(0.99,0.99,1.0,1.0));

    RectUIDrawObjectRefPtr HorizontalRolloverWhiteRidge2 = RectUIDrawObject::create();
    HorizontalRolloverWhiteRidge2->setTopLeft(Pnt2f(2,0));
    HorizontalRolloverWhiteRidge2->setBottomRight(Pnt2f(3,6));
    HorizontalRolloverWhiteRidge2->setColor(Color4f(0.99,0.99,1.0,1.0));

    RectUIDrawObjectRefPtr HorizontalRolloverWhiteRidge3 = RectUIDrawObject::create();
    HorizontalRolloverWhiteRidge3->setTopLeft(Pnt2f(4,0));
    HorizontalRolloverWhiteRidge3->setBottomRight(Pnt2f(5,6));
    HorizontalRolloverWhiteRidge3->setColor(Color4f(0.99,0.99,1.0,1.0));

    RectUIDrawObjectRefPtr HorizontalRolloverWhiteRidge4 = RectUIDrawObject::create();
    HorizontalRolloverWhiteRidge4->setTopLeft(Pnt2f(6,0));
    HorizontalRolloverWhiteRidge4->setBottomRight(Pnt2f(7,6));
    HorizontalRolloverWhiteRidge4->setColor(Color4f(0.99,0.99,1.0,1.0));

    RectUIDrawObjectRefPtr HorizontalRolloverBlueRidge1 = RectUIDrawObject::create();
    HorizontalRolloverBlueRidge1->setTopLeft(Pnt2f(1,1));
    HorizontalRolloverBlueRidge1->setBottomRight(Pnt2f(2,7));
    HorizontalRolloverBlueRidge1->setColor(Color4f(0.61,0.77,1.0,1.0));

    RectUIDrawObjectRefPtr HorizontalRolloverBlueRidge2 = RectUIDrawObject::create();
    HorizontalRolloverBlueRidge2->setTopLeft(Pnt2f(3,1));
    HorizontalRolloverBlueRidge2->setBottomRight(Pnt2f(4,7));
    HorizontalRolloverBlueRidge2->setColor(Color4f(0.61,0.77,1.0,1.0));

    RectUIDrawObjectRefPtr HorizontalRolloverBlueRidge3 = RectUIDrawObject::create();
    HorizontalRolloverBlueRidge3->setTopLeft(Pnt2f(5,1));
    HorizontalRolloverBlueRidge3->setBottomRight(Pnt2f(6,7));
    HorizontalRolloverBlueRidge3->setColor(Color4f(0.61,0.77,1.0,1.0));

    RectUIDrawObjectRefPtr HorizontalRolloverBlueRidge4 = RectUIDrawObject::create();
    HorizontalRolloverBlueRidge4->setTopLeft(Pnt2f(7,1));
    HorizontalRolloverBlueRidge4->setBottomRight(Pnt2f(8,7));
    HorizontalRolloverBlueRidge4->setColor(Color4f(0.61,0.77,1.0,1.0));

    UIDrawObjectCanvasRefPtr WindowsHorizontalRolloverScrollBarRidges = UIDrawObjectCanvas::create();
    WindowsHorizontalRolloverScrollBarRidges->pushToDrawObjects(HorizontalRolloverWhiteRidge1);
    WindowsHorizontalRolloverScrollBarRidges->pushToDrawObjects(HorizontalRolloverBlueRidge1);
    WindowsHorizontalRolloverScrollBarRidges->pushToDrawObjects(HorizontalRolloverWhiteRidge2);
    WindowsHorizontalRolloverScrollBarRidges->pushToDrawObjects(HorizontalRolloverBlueRidge2);
    WindowsHorizontalRolloverScrollBarRidges->pushToDrawObjects(HorizontalRolloverWhiteRidge3);
    WindowsHorizontalRolloverScrollBarRidges->pushToDrawObjects(HorizontalRolloverBlueRidge3);
    WindowsHorizontalRolloverScrollBarRidges->pushToDrawObjects(HorizontalRolloverWhiteRidge4);
    WindowsHorizontalRolloverScrollBarRidges->pushToDrawObjects(HorizontalRolloverBlueRidge4);

    ButtonRefPtr WindowsHorizontalScrollBarDrawObject = Button::create();
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

    WindowsHorizontalScrollBarDrawObject->setAlignment(Vec2f(0.5f,0.5f));
    WindowsHorizontalScrollBarDrawObject->setActiveOffset(Vec2f(0,0));

    WindowsHorizontalScrollBarDrawObject->setDrawObject(WindowsHorizontalScrollBarRidges);
    WindowsHorizontalScrollBarDrawObject->setActiveDrawObject(WindowsHorizontalActiveScrollBarRidges);
    WindowsHorizontalScrollBarDrawObject->setFocusedDrawObject(WindowsHorizontalScrollBarRidges);
    WindowsHorizontalScrollBarDrawObject->setRolloverDrawObject(WindowsHorizontalRolloverScrollBarRidges);
    WindowsHorizontalScrollBarDrawObject->setDisabledDrawObject(WindowsHorizontalScrollBarRidges);

    //Windows ScrollBar
    WindowsScrollBar->setEnabled(true);
    WindowsScrollBar->setVisible(true);

    WindowsScrollBar->setConstraints(NULL);
    //Sizes
    WindowsScrollBar->setMinSize(Vec2f(0,0));
    WindowsScrollBar->setMaxSize(Vec2f(32767,32767)); //2^15
    WindowsScrollBar->setPreferredSize(Vec2f(17,17));

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
    

    //************************** ScrollPanel*****************************
    //Windows ScrollPanelBorder
    EmptyBorderRefPtr WindowsScrollPanelBorder = EmptyBorder::create();

    //Windows ScrollPanelBackground
    EmptyLayerRefPtr WindowsScrollPanelBackground = EmptyLayer::create();



    //Windows ScrollPanel
    WindowsScrollPanel->setEnabled(true);
    WindowsScrollPanel->setVisible(true);

    WindowsScrollPanel->setConstraints(NULL);
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

    //Horizontal Scroll Bar
    WindowsScrollPanel->setHorizontalScrollBarDisplayPolicy(ScrollPanel::SCROLLBAR_AS_NEEDED);


    WindowsScrollPanel->setVerticalScrollBarAlignment(ScrollPanel::SCROLLBAR_ALIGN_RIGHT);
    WindowsScrollPanel->setHorizontalScrollBarAlignment(ScrollPanel::SCROLLBAR_ALIGN_BOTTOM);
    

    //************************** UIViewport *****************************
    //Windows UIViewportBorder
    EmptyBorderRefPtr WindowsUIViewportBorder = EmptyBorder::create();
    WindowsUIViewportBorder->setLeftWidth(0);
    WindowsUIViewportBorder->setRightWidth(0);
    WindowsUIViewportBorder->setTopWidth(0);
    WindowsUIViewportBorder->setBottomWidth(0);

    //Windows UIViewportBackground
    EmptyLayerRefPtr WindowsUIViewportBackground = EmptyLayer::create();

    //Windows UIViewport
    WindowsUIViewport->setEnabled(true);
    WindowsUIViewport->setVisible(true);

    WindowsUIViewport->setConstraints(NULL);
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
    

    //************************** RotatedComponent*****************************
    //Windows RotatedComponentBorder
    EmptyBorderRefPtr WindowsRotatedComponentBorder = EmptyBorder::create();

    //Windows RotatedComponentBackground
    EmptyLayerRefPtr WindowsRotatedComponentBackground = EmptyLayer::create();

    //Windows RotatedComponent
    WindowsRotatedComponent->setEnabled(true);
    WindowsRotatedComponent->setVisible(true);

    WindowsRotatedComponent->setConstraints(NULL);
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

    WindowsRotatedComponent->setInternalComponent(NULL);

    WindowsRotatedComponent->setResizePolicy(RotatedComponent::RESIZE_TO_MIN);
    

    //************************** List *****************************
    //Windows RotatedComponentBorder
    EmptyBorderRefPtr WindowsListBorder = EmptyBorder::create();

    //Windows RotatedComponentBackground
    EmptyLayerRefPtr WindowsListBackground = EmptyLayer::create();

    //************************** DefaultListComponentGenerator *****************************
    LabelRefPtr WindowsDefaultListComponentGeneratorComponentPrototype = Label::create();
    WindowsDefaultListComponentGeneratorComponentPrototype->setBorders(WindowsEmptyBorder);

    ColorLayerRefPtr WindowsDefaultListComponentGeneratorSelectedBackground = ColorLayer::create();
    WindowsDefaultListComponentGeneratorSelectedBackground->setColor(Color4f(0.4f,0.4f,1.0f,1.0f));

    LayerRefPtr WindowsDefaultListComponentGeneratorFocusedBackground = WindowsDefaultListComponentGeneratorComponentPrototype->getBackground();

    BorderRefPtr WindowsDefaultListComponentGeneratorSelectedBorder = WindowsDefaultListComponentGeneratorComponentPrototype->getBorder();

    LineBorderRefPtr WindowsDefaultListComponentGeneratorFocusedBorder = LineBorder::create();
    WindowsDefaultListComponentGeneratorFocusedBorder->setWidth(1);
    WindowsDefaultListComponentGeneratorFocusedBorder->setColor(Color4f(0.0f,0.0f,1.0f,1.0f));

    //DefaultListComponentGenerator
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

    //Windows List
    WindowsList->setEnabled(true);
    WindowsList->setVisible(true);

    WindowsList->setConstraints(NULL);
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
    


    //************************** Spinner *****************************

    //Spinner Next Draw Object
    PolygonUIDrawObjectRefPtr WindowsSpinnerNextButtonDrawObject1 = PolygonUIDrawObject::create();
    WindowsSpinnerNextButtonDrawObject1->setColor(Color4f(0.3,0.38,0.52,1.0));
    WindowsSpinnerNextButtonDrawObject1->setOpacity(1.0);
    WindowsSpinnerNextButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(0,4));
    WindowsSpinnerNextButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(4,0));
    WindowsSpinnerNextButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(4,2));
    WindowsSpinnerNextButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(1,5));
    PolygonUIDrawObjectRefPtr WindowsSpinnerNextButtonDrawObject2 = PolygonUIDrawObject::create();
    WindowsSpinnerNextButtonDrawObject2->setColor(Color4f(0.3,0.38,0.52,1.0));
    WindowsSpinnerNextButtonDrawObject2->setOpacity(1.0);
    WindowsSpinnerNextButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(4,0));
    WindowsSpinnerNextButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(8,4));
    WindowsSpinnerNextButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(7,5));
    WindowsSpinnerNextButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(4,2));

    UIDrawObjectCanvasRefPtr WindowsSpinnerNextButtonCanvas = UIDrawObjectCanvas::create();
    WindowsSpinnerNextButtonCanvas->pushToDrawObjects(WindowsSpinnerNextButtonDrawObject1);
    WindowsSpinnerNextButtonCanvas->pushToDrawObjects(WindowsSpinnerNextButtonDrawObject2);

    ButtonRefPtr WindowsSpinnerNextButton = Button::create();
    WindowsSpinnerNextButton->setPreferredSize(Vec2f(17,17));
    WindowsSpinnerNextButton->setEnableActionOnMouseDownTime(true);
    WindowsSpinnerNextButton->setActionOnMouseDownRate(0.1);

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

    WindowsSpinnerNextButton->setAlignment(Vec2f(0.5f,0.5f));

    //Spinner Previous Draw Object
    PolygonUIDrawObjectRefPtr WindowsSpinnerPreviousButtonDrawObject1 = PolygonUIDrawObject::create();
    WindowsSpinnerPreviousButtonDrawObject1->setColor(Color4f(0.3,0.38,0.52,1.0));
    WindowsSpinnerPreviousButtonDrawObject1->setOpacity(1.0);
    WindowsSpinnerPreviousButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(1,0));
    WindowsSpinnerPreviousButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(4,3));
    WindowsSpinnerPreviousButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(4,5));
    WindowsSpinnerPreviousButtonDrawObject1->editMFVerticies()->push_back(Pnt2f(0,1));
    PolygonUIDrawObjectRefPtr WindowsSpinnerPreviousButtonDrawObject2 = PolygonUIDrawObject::create();
    WindowsSpinnerPreviousButtonDrawObject2->setColor(Color4f(0.3,0.38,0.52,1.0));
    WindowsSpinnerPreviousButtonDrawObject2->setOpacity(1.0);
    WindowsSpinnerPreviousButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(4,3));
    WindowsSpinnerPreviousButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(7,0));
    WindowsSpinnerPreviousButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(8,1));
    WindowsSpinnerPreviousButtonDrawObject2->editMFVerticies()->push_back(Pnt2f(4,5));

    UIDrawObjectCanvasRefPtr WindowsSpinnerPreviousButtonCanvas = UIDrawObjectCanvas::create();
    WindowsSpinnerPreviousButtonCanvas->pushToDrawObjects(WindowsSpinnerPreviousButtonDrawObject1);
    WindowsSpinnerPreviousButtonCanvas->pushToDrawObjects(WindowsSpinnerPreviousButtonDrawObject2);
    ButtonRefPtr WindowsSpinnerPreviousButton = Button::create();
    WindowsSpinnerPreviousButton->setPreferredSize(Vec2f(17,17));
    WindowsSpinnerPreviousButton->setEnableActionOnMouseDownTime(true);
    WindowsSpinnerPreviousButton->setActionOnMouseDownRate(0.1);
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

    WindowsSpinnerPreviousButton->setAlignment(Vec2f(0.5f,0.5f));

    //Windows SpinnerBorder
    EmptyBorderRefPtr WindowsSpinnerBorder = EmptyBorder::create();

    //Windows SpinnerBackground
    EmptyLayerRefPtr WindowsSpinnerBackground = EmptyLayer::create();

    WindowsSpinner->setConstraints(NULL);
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

    //************************** SpinnerDefaultEditor *****************************
    //Windows SpinnerDefaultEditor TextField
    TextFieldRefPtr WindowsSpinnerDefaultEditorTextField = TextField::create();
    WindowsSpinnerDefaultEditorTextField->setAlignment(Vec2f(1.0f,0.5f));

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

    WindowsSpinnerDefaultEditor->setConstraints(NULL);
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

    //************************** SpinnerNumberEditor *****************************
    //Windows SpinnerNumberEditor TextField
    TextFieldRefPtr WindowsSpinnerNumberEditorTextField = TextField::create();
    WindowsSpinnerNumberEditorTextField->setAlignment(Vec2f(1.0f,0.5f));

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

    WindowsSpinnerNumberEditor->setConstraints(NULL);
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

    //************************** Separator *****************************
    //Windows SeparatorBorder

    //Windows SeparatorBackground
    EmptyBorderRefPtr WindowsSeparatorBorder = EmptyBorder::create();
    EmptyLayerRefPtr WindowsSeparatorBackground = EmptyLayer::create();

    WindowsSeparator->setConstraints(NULL);
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
    

    //************************** ProgressBar *****************************
    //Windows ProgressBarBorder
    RoundedCornerLineBorderRefPtr WindowsProgressBarBorder = RoundedCornerLineBorder::create();
    WindowsProgressBarBorder->setColor( Color4f(0.0, 0.0, 0.0 ,1.0) );
    WindowsProgressBarBorder->setWidth(1);
    WindowsProgressBarBorder->setCornerRadius(5);

    //Windows ProgressBarBackground
    ColorLayerRefPtr ProgressBarBackground = ColorLayer::create();
    ProgressBarBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));

    //Windows ProgressBarDrawObjectBackground
    ColorLayerRefPtr ProgressBarDrawObjectBackground = ColorLayer::create();
    ProgressBarDrawObjectBackground->setColor(Color4f(0.0, 1.0, 0.0, 1.0));

    //ProgressBar DrawObjectCanvas
    UIDrawObjectCanvasRefPtr WindowsProgressBarCanvas = UIDrawObjectCanvas::create();
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

    //ProgressBar
    WindowsProgressBar->setConstraints(NULL);
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
    WindowsProgressBar->setAlignment(Vec2f(0.5f,0.5f));
    WindowsProgressBar->setFont(WindowsFont);
    WindowsProgressBar->setTextColor(Color4f(0.0,0.0,0.0,1.0));
    WindowsProgressBar->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
    WindowsProgressBar->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
    WindowsProgressBar->setDisabledTextColor(Color4f(0.0,0.0,0.0,1.0));
    WindowsProgressBar->setDrawObject(WindowsProgressBarCanvas);
    WindowsProgressBar->setFocusedDrawObject(WindowsProgressBarCanvas);
    WindowsProgressBar->setRolloverDrawObject(WindowsProgressBarCanvas);
    WindowsProgressBar->setDisabledDrawObject(WindowsProgressBarCanvas);

    //************************** Slider *****************************
    RoundedCornerLineBorderRefPtr WindowsSliderKnobButtonRoundedCornerBorder = RoundedCornerLineBorder::create();
    WindowsSliderKnobButtonRoundedCornerBorder->setColor( Color4f(0.71, 0.77, 0.80 ,1.0) );
    WindowsSliderKnobButtonRoundedCornerBorder->setWidth(1);
    WindowsSliderKnobButtonRoundedCornerBorder->setCornerRadius(3);

    MatteBorderRefPtr WindowsSliderKnobButtonMatteBorder = MatteBorder::create();
    WindowsSliderKnobButtonMatteBorder->setRightWidth(3);
    WindowsSliderKnobButtonMatteBorder->setLeftWidth(3);
    WindowsSliderKnobButtonMatteBorder->setTopWidth(0);
    WindowsSliderKnobButtonMatteBorder->setBottomWidth(0);
    WindowsSliderKnobButtonMatteBorder->setColor(Color4f(0.28, 0.8, 0.27, 1.0));

    CompoundBorderRefPtr WindowsSliderKnobButtonBorder = CompoundBorder::create();
    WindowsSliderKnobButtonBorder->setInnerBorder(WindowsSliderKnobButtonMatteBorder);
    WindowsSliderKnobButtonBorder->setOuterBorder(WindowsSliderKnobButtonRoundedCornerBorder);

    ColorLayerRefPtr WindowsSliderBackground = ColorLayer::create();
    WindowsSliderBackground->setColor(Color4f(0.95, 0.95, 0.94, 1.0));

    ButtonRefPtr WindowsSliderKnobButton = Button::create();
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

    LabelRefPtr WindowsSliderPrototypeLabel = Label::create();
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

    WindowsSliderPrototypeLabel->setAlignment(Vec2f(0.0f,0.5f));

    //Windows SliderBorder
    EtchedBorderRefPtr WindowsSliderBorder = EtchedBorder::create();
    WindowsSliderBorder->setWidth(2);
    WindowsSliderBorder->setRaised(true);
    WindowsSliderBorder->setHighlight(Color4f(1.0, 1.0, 1.0, 1.0));
    WindowsSliderBorder->setShadow(Color4f(0.65, 0.65, 0.65, 1.0));

    //Windows SliderBackground
    ColorLayerRefPtr SliderBackground = ColorLayer::create();
    SliderBackground->setColor(Color4f(0.93, 0.91, 0.85, 1.0));

    //Windows SliderDrawObjectBackground
    ColorLayerRefPtr SliderTrackDrawObjectBackground = ColorLayer::create();
    SliderTrackDrawObjectBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));

    BevelBorderRefPtr SliderTrackDrawObjectBorder = BevelBorder::create();
    SliderTrackDrawObjectBorder->setRaised(true);
    SliderTrackDrawObjectBorder->setWidth(1);
    SliderTrackDrawObjectBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
    SliderTrackDrawObjectBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
    SliderTrackDrawObjectBorder->setShadowInner(Color4f(0.85, 0.85, 0.85, 1.0));
    SliderTrackDrawObjectBorder->setShadowOuter(Color4f(0.65, 0.65, 0.65, 1.0));

    //Slider DrawObjectCanvas
    UIDrawObjectCanvasRefPtr WindowsSliderTrackCanvas = UIDrawObjectCanvas::create();
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

    //Slider Major Tick Marks
    RectUIDrawObjectRefPtr WindowsSliderMajorTickMarks = RectUIDrawObject::create();
    WindowsSliderMajorTickMarks->setTopLeft(Pnt2f(0,0));
    WindowsSliderMajorTickMarks->setBottomRight(Pnt2f(7,1));
    WindowsSliderMajorTickMarks->setColor(Color4f(0.63,0.63,0.57,1.0));

    //Slider Minor Tick Marks
    RectUIDrawObjectRefPtr WindowsSliderMinorTickMarks = RectUIDrawObject::create();
    WindowsSliderMinorTickMarks->setTopLeft(Pnt2f(0,0));
    WindowsSliderMinorTickMarks->setBottomRight(Pnt2f(4,1));
    WindowsSliderMinorTickMarks->setColor(Color4f(0.63,0.63,0.57,1.0));


    //Slider
    WindowsSlider->setConstraints(NULL);
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
    WindowsSlider->setMinTrackDrawObject(NULL);
    WindowsSlider->setMaxTrackDrawObject(NULL);
    WindowsSlider->setTrackInset(8);
    WindowsSlider->setTrackToTickOffset(8);
    WindowsSlider->setTrackToLabelOffset(18);

    WindowsSlider->clearMajorTickDrawObjects();
    WindowsSlider->pushToMajorTickDrawObjects(WindowsSliderMajorTickMarks);
    WindowsSlider->clearMinorTickDrawObjects();
    WindowsSlider->pushToMinorTickDrawObjects(WindowsSliderMinorTickMarks);

    //************************** ComboBox *****************************

    //Expand Button
    ToggleButtonRefPtr WindowsComboBoxExpandButton = ToggleButton::create();
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

    //Windows ComboBoxBorder
    EtchedBorderRefPtr WindowsComboBoxBorder = EtchedBorder::create();
    WindowsComboBoxBorder->setWidth(2);
    WindowsComboBoxBorder->setRaised(true);
    WindowsComboBoxBorder->setHighlight(Color4f(1.0, 1.0, 1.0, 1.0));
    WindowsComboBoxBorder->setShadow(Color4f(0.65, 0.65, 0.65, 1.0));

    //Windows ComboBoxBackground
    ColorLayerRefPtr WindowsComboBoxBackground = ColorLayer::create();
    WindowsComboBoxBackground->setColor(Color4f(0.93, 0.91, 0.85, 1.0));

    //Default ComboBoxEditor
    //Windows Default ComboBoxEditor TextField
    TextFieldRefPtr WindowsDefaultComboBoxTextField = TextField::create();
    WindowsDefaultComboBoxTextField->setAlignment(Vec2f(0.0f,0.5f));

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

    DefaultComboBoxEditorRefPtr WindowsDefaultComboBoxEditor = DefaultComboBoxEditor::create();
    WindowsDefaultComboBoxEditor->setEditor(WindowsDefaultComboBoxTextField);

    //************************** DefaultComboBoxComponentGenerator *****************************
    LabelRefPtr WindowsDefaultComboBoxComponentGeneratorComponentPrototype = Label::create();
    WindowsDefaultComboBoxComponentGeneratorComponentPrototype->setBorders(WindowsEmptyBorder);
    WindowsDefaultComboBoxComponentGeneratorComponentPrototype->setBackgrounds(WindowsEmptyBackground);

    ColorLayerRefPtr WindowsDefaultComboBoxComponentGeneratorSelectedBackground = ColorLayer::create();
    WindowsDefaultComboBoxComponentGeneratorSelectedBackground->setColor(Color4f(0.4f,0.4f,1.0f,1.0f));

    LayerRefPtr WindowsDefaultComboBoxComponentGeneratorFocusedBackground = WindowsDefaultComboBoxComponentGeneratorComponentPrototype->getBackground();

    BorderRefPtr WindowsDefaultComboBoxComponentGeneratorSelectedBorder = WindowsDefaultComboBoxComponentGeneratorComponentPrototype->getBorder();

    BorderRefPtr WindowsDefaultComboBoxComponentGeneratorFocusedBorder = WindowsDefaultComboBoxComponentGeneratorComponentPrototype->getBorder();

    //DefaultComboBoxComponentGenerator
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

    //ComboBox
    WindowsComboBox->setConstraints(NULL);
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

    //************************** TableHeader *****************************
    //Windows RotatedComponentBorder
    EmptyBorderRefPtr WindowsTableHeaderBorder = EmptyBorder::create();

    //Windows RotatedComponentBackground
    EmptyLayerRefPtr WindowsTableHeaderBackground = EmptyLayer::create();

    //Windows RotatedComponent
    WindowsTableHeader->setEnabled(true);
    WindowsTableHeader->setVisible(true);

    WindowsTableHeader->setConstraints(NULL);
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
    WindowsTableHeader->setReorderingAllowed(true);
    WindowsTableHeader->setResizingAllowed(true);
    WindowsTableHeader->setDefaultMarginDrawObject(NULL);
    WindowsTableHeader->setDefaultRenderer(TableCellRendererPtr(new DefaultTableHeaderCellRenderer()));
    WindowsTableHeader->setResizingCursorDriftAllowance(1);



    //************************** Table *****************************
    //Windows RotatedComponentBorder
    EmptyBorderRefPtr WindowsTableBorder = EmptyBorder::create();

    //Windows RotatedComponentBackground
    EmptyLayerRefPtr WindowsTableBackground = EmptyLayer::create();

    //Windows RotatedComponent
    WindowsTable->setEnabled(true);
    WindowsTable->setVisible(true);

    WindowsTable->setConstraints(NULL);
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
    TableColumnModelUnrecPtr WindowsTableColumnModel(DefaultTableColumnModel::create());
    WindowsTable->setColumnModel(WindowsTableColumnModel);

    WindowsTable->setDefaultRenderer(typeid(GLenum), TableCellRendererPtr(new DefaultGLenumTableCellRenderer()));
    WindowsTable->setDefaultRenderer(typeid(std::string), TableCellRendererPtr(new DefaultStringTableCellRenderer()));
    WindowsTable->setDefaultRenderer(typeid(bool), TableCellRendererPtr(new DefaultBoolTableCellRenderer()));
    WindowsTable->setDefaultRenderer(typeid(Int32), TableCellRendererPtr(new DefaultInt32TableCellRenderer()));
    WindowsTable->setDefaultRenderer(typeid(UInt32), TableCellRendererPtr(new DefaultUInt32TableCellRenderer()));
    WindowsTable->setDefaultRenderer(typeid(Real32), TableCellRendererPtr(new DefaultReal32TableCellRenderer()));


    //************************** DefaultTreeEditor *****************************

    //DefaultTreeCellEditor
    WindowsDefaultTreeCellEditor->setClickCountToStart(3);
    WindowsDefaultTreeCellEditor->setDefaultEditor(WindowsTextField);
    WindowsDefaultTreeCellEditor->setDefaultStringEditor(WindowsTextField);

    //************************** DefaultTreeComponentGenerator *****************************
    LineBorderRefPtr WindowsTreeComponentExpandingBorder = LineBorder::create();
    WindowsTreeComponentExpandingBorder->setWidth(1.0);
    WindowsTreeComponentExpandingBorder->setColor(Color4f(0.545, 0.545, 0.835, 1.0));

    GradientLayerRefPtr WindowsTreeComponentExpandingBackground = GradientLayer::create();
    WindowsTreeComponentExpandingBackground->editMFColors()->push_back(Color4f(1.0, 1.0, 1.0, 1.0));
    WindowsTreeComponentExpandingBackground->editMFStops()->push_back(0.0);
    WindowsTreeComponentExpandingBackground->editMFColors()->push_back(Color4f(.75, .75, .75, 1.0));
    WindowsTreeComponentExpandingBackground->editMFStops()->push_back(1.0);
    WindowsTreeComponentExpandingBackground->setStartPosition(Vec2f(0.0f,0.0f));
    WindowsTreeComponentExpandingBackground->setEndPosition(Vec2f(0.0f,1.0f));

    //Expanded Draw Object
    RectUIDrawObjectRefPtr ExpanedDrawObject = RectUIDrawObject::create();
    ExpanedDrawObject->setTopLeft(Pnt2f(2,4));
    ExpanedDrawObject->setBottomRight(Pnt2f(7,5));
    ExpanedDrawObject->setColor(Color4f(0.0,0.0,0.0,1.0));
    ExpanedDrawObject->setOpacity(1.0);

    UIDrawObjectCanvasRefPtr WindowsExpandedDrawObject = UIDrawObjectCanvas::create();
    //Border
    WindowsExpandedDrawObject->setBorders(WindowsTreeComponentExpandingBorder);

    //Background
    WindowsExpandedDrawObject->setBackgrounds(WindowsTreeComponentExpandingBackground);

    WindowsExpandedDrawObject->setPreferredSize(Vec2f(9.0f,9.0f));
    WindowsExpandedDrawObject->setMaxSize(Vec2f(9.0f,9.0f));
    WindowsExpandedDrawObject->setMinSize(Vec2f(9.0f,9.0f));

    WindowsExpandedDrawObject->pushToDrawObjects(ExpanedDrawObject);
    WindowsExpandedDrawObject->setUsePreferredSizeAsRequested(true);

    RectUIDrawObjectRefPtr NotExpanedDrawObject = RectUIDrawObject::create();
    NotExpanedDrawObject->setTopLeft(Pnt2f(4,2));
    NotExpanedDrawObject->setBottomRight(Pnt2f(5,7));
    NotExpanedDrawObject->setColor(Color4f(0.0,0.0,0.0,1.0));
    NotExpanedDrawObject->setOpacity(1.0);

    UIDrawObjectCanvasRefPtr WindowsNotExpandedDrawObjectPrototype = UIDrawObjectCanvas::create();
    //Border
    WindowsNotExpandedDrawObjectPrototype->setBorders(WindowsTreeComponentExpandingBorder);

    //Background
    WindowsNotExpandedDrawObjectPrototype->setBackgrounds(WindowsTreeComponentExpandingBackground);

    WindowsNotExpandedDrawObjectPrototype->setPreferredSize(Vec2f(9.0f,9.0f));
    WindowsNotExpandedDrawObjectPrototype->setMaxSize(Vec2f(9.0f,9.0f));
    WindowsNotExpandedDrawObjectPrototype->setMinSize(Vec2f(9.0f,9.0f));
    WindowsNotExpandedDrawObjectPrototype->pushToDrawObjects(ExpanedDrawObject);
    WindowsNotExpandedDrawObjectPrototype->pushToDrawObjects(NotExpanedDrawObject);
    WindowsNotExpandedDrawObjectPrototype->setUsePreferredSizeAsRequested(true);

    UIDrawObjectCanvasRefPtr WindowsLeafDrawObjectPrototype = UIDrawObjectCanvas::create();

    UIDrawObjectCanvasRefPtr WindowsNonLeafDrawObjectPrototype = UIDrawObjectCanvas::create();

    UIDrawObjectCanvasRefPtr WindowsExpandedNonLeafDrawObjectPrototype = UIDrawObjectCanvas::create();

    //LabelRefPtr WindowsDefaultTreeComponentGeneratorNodeLabelPrototype = Label::create();
    LabelRefPtr WindowsDefaultTreeComponentGeneratorNodeLabelPrototype = WindowsDefaultListComponentGeneratorComponentPrototype;

    //ColorLayerRefPtr WindowsDefaultTreeComponentGeneratorSelectedBackground = ColorLayer::create();
    LayerRefPtr WindowsDefaultTreeComponentGeneratorSelectedBackground = WindowsDefaultListComponentGeneratorSelectedBackground;

    //ColorLayerRefPtr WindowsDefaultTreeComponentGeneratorNonSelectedBackground = ColorLayer::create();
    LayerRefPtr WindowsDefaultTreeComponentGeneratorNonSelectedBackground = WindowsEmptyBackground;

    //LineBorderRefPtr WindowsDefaultTreeComponentGeneratorSelectedBorder = LineBorder::create();
    BorderRefPtr WindowsDefaultTreeComponentGeneratorSelectedBorder = WindowsDefaultListComponentGeneratorSelectedBorder;

    PanelRefPtr WindowsDefaultTreeComponentGeneratorPanelPrototype = Panel::create();
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



    //DefaultTreeComponentGenerator
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

    //DefaultTreeLayout
    TreeModelLayoutRefPtr WindowsDefaultTreeModelLayout = FixedHeightTreeModelLayout::create();
    WindowsDefaultTreeModelLayout->setRootVisible(false);
    WindowsDefaultTreeModelLayout->setRowHeight(20);

    //************************** Tree *****************************
    //Windows RotatedComponentBorder
    LineBorderRefPtr WindowsTreeBorder = LineBorder::create();
    WindowsTreeBorder->setWidth(1);
    WindowsTreeBorder->setColor(Color4f(0.0, 0.0, 0.0, 1.0));

    //Windows RotatedComponentBackground
    ColorLayerRefPtr WindowsTreeBackground = ColorLayer::create();
    WindowsTreeBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));

    //Windows WindowsTree
    WindowsTree->setEnabled(true);
    WindowsTree->setVisible(true);

    WindowsTree->setConstraints(NULL);
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



    //************************** RGBColorChooserPanel *****************************
    RGBColorChooserPanelRefPtr WindowsRGBColorChooserPanel = RGBColorChooserPanel::create();
    WindowsRGBColorChooserPanel->setEnabled(true);
    WindowsRGBColorChooserPanel->setVisible(true);

    WindowsRGBColorChooserPanel->setConstraints(NULL);

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

    //************************** HSVColorChooserPanel *****************************
    //HSVColorChooserPanelRefPtr WindowsHSVColorChooserPanel = HSVColorChooserPanel::create();
    //WindowsHSVColorChooserPanel->setEnabled(true);
    //WindowsHSVColorChooserPanel->setVisible(true);

    //WindowsHSVColorChooserPanel->setConstraints(NULL);

    ////Sizes
    //WindowsHSVColorChooserPanel->setMinSize(Vec2f(0,0));
    //WindowsHSVColorChooserPanel->setMaxSize(Vec2f(32767,32767)); //2^15
    //WindowsHSVColorChooserPanel->setPreferredSize(Vec2f(100,100));

    ////Border
    //WindowsHSVColorChooserPanel->setBorder(WindowsEmptyBorder);
    //WindowsHSVColorChooserPanel->setRolloverBorder(WindowsEmptyBorder);
    //WindowsHSVColorChooserPanel->setFocusedBorder(WindowsEmptyBorder);
    //WindowsHSVColorChooserPanel->setDisabledBorder(WindowsEmptyBorder);

    ////Background
    //WindowsHSVColorChooserPanel->setBackground(WindowsEmptyBackground);
    //WindowsHSVColorChooserPanel->setRolloverBackground(WindowsEmptyBackground);
    //WindowsHSVColorChooserPanel->setFocusedBackground(WindowsEmptyBackground);
    //WindowsHSVColorChooserPanel->setDisabledBackground(WindowsEmptyBackground);

    ////Opacity
    //WindowsHSVColorChooserPanel->setOpacity(1.0);

    //WindowsHSVColorChooserPanel->setIncludeAlpha(true);

    //************************** ColorChooser *****************************

    //Windows WindowsColorChooser
    WindowsColorChooser->setEnabled(true);
    WindowsColorChooser->setVisible(true);

    WindowsColorChooser->setConstraints(NULL);
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
    WindowsColorChooser->editMFChooserPanelTypeIds()->push_back(RGBColorChooserPanel::getClassType().getId());
    WindowsColorChooser->setPreviewPanel(NULL);

    initUndefinedPrototypes();
    
    commitChanges();
    return;
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

void WindowsLookAndFeel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void WindowsLookAndFeel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump WindowsLookAndFeel NI" << std::endl;
}

OSG_END_NAMESPACE
