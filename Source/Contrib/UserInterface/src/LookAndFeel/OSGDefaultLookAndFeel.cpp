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

#include "OSGDefaultLookAndFeel.h"
#include "OSGUIFont.h"
#include "OSGBorders.h"
#include "OSGLayers.h"
#include "OSGButton.h"
#include "OSGCheckboxButton.h"
#include "OSGRadioButton.h"
#include "OSGToggleButton.h"
#include "OSGLabel.h"
#include "OSGInternalWindow.h"
#include "OSGPanel.h"
//#include "OSGSplitPanel.h"
#include "OSGImageComponent.h"
#include "OSGRectUIDrawObject.h"
#include "OSGPolygonUIDrawObject.h"
#include "OSGArcUIDrawObject.h"
#include "OSGDiscUIDrawObject.h"
#include "OSGLineUIDrawObject.h"
#include "OSGUIDrawObjectCanvas.h"
#include "OSGTextField.h"
#include "OSGPasswordField.h"
#include "OSGTextArea.h"

#include "OSGMenuItem.h"
#include "OSGMenu.h"
#include "OSGPopupMenu.h"
#include "OSGMenuBar.h"

#include "OSGScrollBar.h"
#include "OSGScrollPanel.h"

#include "OSGRotatedComponent.h"
#include "OSGUIViewport.h"

//#include "OSGTableHeader.h"
//#include "OSGTable.h"
//#include "OSGDefaultTableCellRenderers.h"

#include "OSGList.h"
#include "OSGDefaultListSelectionModel.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDefaultLookAndFeelBase.cpp file.
// To modify it, please change the .fcd file (OSGDefaultLookAndFeel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultLookAndFeel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void DefaultLookAndFeel::init(void)
{

    assert(false && "Needs to be implemented!");
    setTextCaretRate(1.0);
    setToolTipPopupTime(1.5);
    setToolTipPopupTime(0.25);
    setKeyAcceleratorMenuFlashTime(0.15);

    //Default Font
    UIFontRefPtr DefaultFont = UIFont::create();
    DefaultFont->setFamily("SANS");
    DefaultFont->setGap(3);
    DefaultFont->setGlyphPixelSize(14);
    DefaultFont->setSize(14);
    DefaultFont->setTextureWidth(0);
    DefaultFont->setStyle(TextFace::STYLE_PLAIN);

    //Default ButtonBorder
    BevelBorderRefPtr DefaultButtonBorder = BevelBorder::create();
    DefaultButtonBorder->setRaised(true);
    DefaultButtonBorder->setWidth(2);
    DefaultButtonBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultButtonBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultButtonBorder->setShadowInner(Color4f(0.65, 0.65, 0.65, 1.0));
    DefaultButtonBorder->setShadowOuter(Color4f(0.45, 0.45, 0.45, 1.0));

    //Default Disabled ButtonBorder
    BevelBorderRefPtr DefaultDisabledButtonBorder = BevelBorder::create();
    DefaultDisabledButtonBorder->setRaised(true);
    DefaultDisabledButtonBorder->setWidth(2);
    DefaultDisabledButtonBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultDisabledButtonBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultDisabledButtonBorder->setShadowInner(Color4f(0.85, 0.85, 0.85, 1.0));
    DefaultDisabledButtonBorder->setShadowOuter(Color4f(0.65, 0.65, 0.65, 1.0));


    //default active button border
    BevelBorderRefPtr DefaultActiveButtonBorder = BevelBorder::create();
    DefaultActiveButtonBorder->setRaised(false);
    DefaultActiveButtonBorder->setWidth(2);
    DefaultActiveButtonBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultActiveButtonBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultActiveButtonBorder->setShadowInner(Color4f(0.65, 0.65, 0.65, 1.0));
    DefaultActiveButtonBorder->setShadowOuter(Color4f(0.45, 0.45, 0.45, 1.0));

    //Default ButtonBackground
    ColorLayerRefPtr DefaultButtonBackground = ColorLayer::create();
    DefaultButtonBackground->setColor(Color4f(0.93,0.93,0.93,1.0));

    //Default Disabled ButtonBackground
    ColorLayerRefPtr DefaultDisabledButtonBackground = ColorLayer::create();
    DefaultDisabledButtonBackground->setColor(Color4f(1.0,1.0,1.0,1.0));

    //Default Button
    ButtonRefPtr DefaultButton = Button::create();
    DefaultButton->setEnabled(true);
    DefaultButton->setVisible(true);

    DefaultButton->setConstraints(NULL);
    //Sizes
    DefaultButton->setMinSize(Vec2f(0,0));
    DefaultButton->setMaxSize(Vec2f(32767,32767)); //2^15
    DefaultButton->setPreferredSize(Vec2f(100,50));

    //Border
    DefaultButton->setBorder(DefaultButtonBorder);
    DefaultButton->setRolloverBorder(DefaultButtonBorder);
    DefaultButton->setFocusedBorder(DefaultButtonBorder);
    DefaultButton->setDisabledBorder(DefaultDisabledButtonBorder);
    DefaultButton->setActiveBorder(DefaultActiveButtonBorder);

    //Background
    DefaultButton->setBackground(DefaultButtonBackground);
    DefaultButton->setRolloverBackground(DefaultButtonBackground);
    DefaultButton->setFocusedBackground(DefaultButtonBackground);
    DefaultButton->setDisabledBackground(DefaultDisabledButtonBackground);
    DefaultButton->setActiveBackground(DefaultButtonBackground);

    //Opacity
    DefaultButton->setOpacity(1.0);

    //Text
    DefaultButton->setText("");
    DefaultButton->setFont(DefaultFont);
    DefaultButton->setAlignment(Vec2f(0.5f,0.5f));
    DefaultButton->setTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultButton->setActiveTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultButton->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultButton->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultButton->setDisabledTextColor(Color4f(0.4,0.4,0.4,1.0));

    DefaultButton->setActiveOffset(Vec2f(2,2));

    Button::getClassType().setPrototype(DefaultButton);

    //************************** Label*****************************
    //Default LabelBorder
    LineBorderRefPtr DefaultLabelBorder = LineBorder::create();
    DefaultLabelBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultLabelBorder->setWidth(1);

    //Default LabelBackground
    ColorLayerRefPtr DefaultLabelBackground = ColorLayer::create();
    DefaultLabelBackground->setColor(Color4f(1.0,1.0,1.0,1.0));

    //Default Label
    LabelRefPtr DefaultLabel = Label::create();
    DefaultLabel->setEnabled(true);
    DefaultLabel->setVisible(true);

    DefaultLabel->setConstraints(NULL);
    //Sizes
    DefaultLabel->setMinSize(Vec2f(0,0));
    DefaultLabel->setMaxSize(Vec2f(32767,32767)); //2^15
    DefaultLabel->setPreferredSize(Vec2f(100,30));

    //Border
    DefaultLabel->setBorder(DefaultLabelBorder);

    //Background
    DefaultLabel->setBackground(DefaultLabelBackground);

    //Opacity
    DefaultLabel->setOpacity(1.0);

    //Text
    DefaultLabel->setText("");
    DefaultLabel->setFont(DefaultFont);
    DefaultLabel->setTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultLabel->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultLabel->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultLabel->setDisabledTextColor(Color4f(0.4,0.4,0.4,1.0));

    Label::getClassType().setPrototype(DefaultLabel);

    //************************** InternalWindow *****************************
    //Default InternalWindowBorder
    EmptyBorderRefPtr DefaultInternalWindowBorder = EmptyBorder::create();
    DefaultInternalWindowBorder->setLeftWidth(0);
    DefaultInternalWindowBorder->setRightWidth(0);
    DefaultInternalWindowBorder->setTopWidth(0);
    DefaultInternalWindowBorder->setBottomWidth(0);

    //Default InternalWindowBackground
    EmptyLayerRefPtr DefaultInternalWindowBackground = EmptyLayer::create();

    //Default InternalWindow
    InternalWindowRefPtr DefaultInternalWindow = InternalWindow::create();
    DefaultInternalWindow->setEnabled(true);
    DefaultInternalWindow->setVisible(true);

    DefaultInternalWindow->setConstraints(NULL);
    //Sizes
    DefaultInternalWindow->setMinSize(Vec2f(0,0));
    DefaultInternalWindow->setMaxSize(Vec2f(32767,32767)); //2^15
    DefaultInternalWindow->setPreferredSize(Vec2f(100,100));

    //Border
    DefaultInternalWindow->setBorder(DefaultInternalWindowBorder);

    //Background
    DefaultInternalWindow->setBackground(DefaultInternalWindowBackground);

    //Opacity
    DefaultInternalWindow->setOpacity(1.0);

    InternalWindow::getClassType().setPrototype(DefaultInternalWindow);

    //************************** Panel *****************************
    //Default PanelBorder
    //LineBorderRefPtr DefaultPanelBorder = LineBorder::create();
      //DefaultPanelBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
      //DefaultPanelBorder->setWidth(1);

      EtchedBorderRefPtr DefaultPanelBorder = EtchedBorder::create();
      DefaultPanelBorder->setWidth(2);
      DefaultPanelBorder->setHighlight(Color4f(1.0, 1.0, 1.0, 1.0));
      DefaultPanelBorder->setShadow(Color4f(0.65, 0.65, 0.65, 1.0));
      DefaultPanelBorder->setRaised(true);

    //Default PanelBackground
    ColorLayerRefPtr DefaultPanelBackground = ColorLayer::create();
    DefaultPanelBackground->setColor(Color4f(0.93,0.93,0.93,1.0));


    //Default Panel
    PanelRefPtr DefaultPanel = Panel::create();
    DefaultPanel->setEnabled(true);
    DefaultPanel->setVisible(true);

    DefaultPanel->setConstraints(NULL);
    //Sizes
    DefaultPanel->setMinSize(Vec2f(0,0));
    DefaultPanel->setMaxSize(Vec2f(32767,32767)); //2^15
    DefaultPanel->setPreferredSize(Vec2f(100,100));

    //Border
    DefaultPanel->setBorder(DefaultPanelBorder);

    //Background
    DefaultPanel->setBackground(DefaultPanelBackground);

    //Opacity
    DefaultPanel->setOpacity(1.0);

    Panel::getClassType().setPrototype(DefaultPanel);

    ///[>************************* SplitPanel *****************************
    ////The only default value set will be the divider

    ////Default Divider Background and Border
    //LineBorderRefPtr DefaultDividerBorder = OSG::LineBorder::create();
    //DefaultDividerBorder->setWidth(1);
    //DefaultDividerBorder->setColor(Color4f(0.13, 0.13, 0.13, 1.0));
    //ColorLayerRefPtr DefaultDividerBackground = ColorLayer::create();
    //DefaultDividerBackground->setColor(Color4f(0.93,0.93,0.93,1.0));

    ////Default Divider
    //UIDrawObjectCanvasRefPtr DefaultDividerDrawObject = UIDrawObjectCanvas::create();
    //DefaultDividerDrawObject->setBorder(DefaultDividerBorder);
    //DefaultDividerDrawObject->setBackground(DefaultDividerBackground);

    ////Default SplitPanel
    //SplitPanelRefPtr DefaultSplitPanel = SplitPanel::create();

    //DefaultSplitPanel->setDividerDrawObject(DefaultDividerDrawObject);
    //DefaultSplitPanel->setDividerSize(5);
    //DefaultSplitPanel->setDividerPosition(100);
    //DefaultSplitPanel->setExpandable(true);
    //DefaultSplitPanel->setOrientation(SplitPanel::HORIZONTAL_ORIENTATION);

    //SplitPanel::getClassType().setPrototype(DefaultSplitPanel);

    //************************** UIViewport *****************************
    //Default UIViewportBorder
    EmptyBorderRefPtr DefaultUIViewportBorder = EmptyBorder::create();
    DefaultUIViewportBorder->setLeftWidth(0);
    DefaultUIViewportBorder->setRightWidth(0);
    DefaultUIViewportBorder->setTopWidth(0);
    DefaultUIViewportBorder->setBottomWidth(0);

    //Default UIViewportBackground
    EmptyLayerRefPtr DefaultUIViewportBackground = EmptyLayer::create();

    //Default UIViewport
    UIViewportRefPtr DefaultUIViewport = UIViewport::create();
    DefaultUIViewport->setEnabled(true);
    DefaultUIViewport->setVisible(true);

    DefaultUIViewport->setConstraints(NULL);
    //Sizes
    DefaultUIViewport->setMinSize(Vec2f(0,0));
    DefaultUIViewport->setMaxSize(Vec2f(32767,32767)); //2^15
    DefaultUIViewport->setPreferredSize(Vec2f(100,100));

    //Border
    DefaultUIViewport->setBorder(DefaultUIViewportBorder);

    //Background
    DefaultUIViewport->setBackground(DefaultUIViewportBackground);

    //Opacity
    DefaultUIViewport->setOpacity(1.0);

    UIViewport::getClassType().setPrototype(DefaultUIViewport);

    //************************** ImageComponent *****************************
    //Default ImageComponentBorder
    EmptyBorderRefPtr DefaultImageComponentBorder = EmptyBorder::create();

    //Default ImageComponentBackground
    EmptyLayerRefPtr DefaultImageComponentBackground = EmptyLayer::create();

    //Default ImageComponent
    ImageComponentRefPtr DefaultImageComponent = ImageComponent::create();
    DefaultImageComponent->setEnabled(true);
    DefaultImageComponent->setVisible(true);

    DefaultImageComponent->setConstraints(NULL);
    //Sizes
    DefaultImageComponent->setMinSize(Vec2f(0,0));
    DefaultImageComponent->setMaxSize(Vec2f(32767,32767)); //2^15
    DefaultImageComponent->setPreferredSize(Vec2f(100,100));
    DefaultImageComponent->setSize(Vec2f(0,0));

    //Border
    DefaultImageComponent->setBorder(DefaultImageComponentBorder);

    //Background
    DefaultImageComponent->setBackground(DefaultImageComponentBackground);

    //Opacity
    DefaultImageComponent->setOpacity(1.0);

    //Image Alignment
    DefaultImageComponent->setScale(ImageComponent::SCALE_NONE);
    DefaultImageComponent->setAlignment(Vec2f(0.5f,0.5f));

    ImageComponent::getClassType().setPrototype(DefaultImageComponent);


    //************************** Checkbox Button Component *****************************
    UIDrawObjectCanvasRefPtr defaultCheckboxDrawObject = UIDrawObjectCanvas::create();
    UIDrawObjectCanvasRefPtr defaultSelectedCheckboxDrawObject = UIDrawObjectCanvas::create();
    UIDrawObjectCanvasRefPtr defaultActiveCheckboxDrawObject = UIDrawObjectCanvas::create();
    UIDrawObjectCanvasRefPtr defaultActiveSelectedCheckboxDrawObject = UIDrawObjectCanvas::create();

    RectUIDrawObjectRefPtr CheckboxBackground = RectUIDrawObject::create();
    CheckboxBackground->setTopLeft(Pnt2f(1,1));
    CheckboxBackground->setBottomRight(Pnt2f(25,25));
    CheckboxBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
    CheckboxBackground->setOpacity(1.0);

    RectUIDrawObjectRefPtr CheckboxBackgroundBorder = RectUIDrawObject::create();
    CheckboxBackgroundBorder->setTopLeft(Pnt2f(0,0));
    CheckboxBackgroundBorder->setBottomRight(Pnt2f(26,26));
    CheckboxBackgroundBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
    CheckboxBackgroundBorder->setOpacity(1.0);

    RectUIDrawObjectRefPtr CheckboxActiveBorder = RectUIDrawObject::create();
    CheckboxActiveBorder->setTopLeft(Pnt2f(1,1));
    CheckboxActiveBorder->setBottomRight(Pnt2f(25, 25));
    CheckboxActiveBorder->setColor(Color4f(0.0, 1.0, 0.0, 1.0));
    CheckboxActiveBorder->setOpacity(1.0);

    LineUIDrawObjectRefPtr CheckboxLine1 = LineUIDrawObject::create();
    CheckboxLine1->setTopLeft(Pnt2f(1,1));
    CheckboxLine1->setBottomRight(Pnt2f(25,25));
    CheckboxLine1->setColor(Color4f(0.0, 0.0, 0.0, 1.0));
    CheckboxLine1->setOpacity(1.0);
    CheckboxLine1->setWidth(4);

    LineUIDrawObjectRefPtr CheckboxLine2 = LineUIDrawObject::create();
    CheckboxLine2->setTopLeft(Pnt2f(1,25));
    CheckboxLine2->setBottomRight(Pnt2f(25,1));
    CheckboxLine2->setColor(Color4f(0.0, 0.0, 0.0, 1.0));
    CheckboxLine2->setOpacity(1.0);
    CheckboxLine2->setWidth(4);

    defaultCheckboxDrawObject->pushToDrawObjects(CheckboxBackgroundBorder);
    defaultCheckboxDrawObject->pushToDrawObjects(CheckboxBackground);

    defaultSelectedCheckboxDrawObject->pushToDrawObjects(CheckboxBackgroundBorder);
    defaultSelectedCheckboxDrawObject->pushToDrawObjects(CheckboxBackground);
    defaultSelectedCheckboxDrawObject->pushToDrawObjects(CheckboxLine1);
    defaultSelectedCheckboxDrawObject->pushToDrawObjects(CheckboxLine2);

    defaultActiveSelectedCheckboxDrawObject->pushToDrawObjects(CheckboxBackgroundBorder);
    defaultActiveSelectedCheckboxDrawObject->pushToDrawObjects(CheckboxBackground);
    defaultActiveSelectedCheckboxDrawObject->pushToDrawObjects(CheckboxActiveBorder);
    defaultActiveSelectedCheckboxDrawObject->pushToDrawObjects(CheckboxLine1);
    defaultActiveSelectedCheckboxDrawObject->pushToDrawObjects(CheckboxLine2);

    defaultActiveCheckboxDrawObject->pushToDrawObjects(CheckboxBackgroundBorder);
    defaultActiveCheckboxDrawObject->pushToDrawObjects(CheckboxBackground);
    defaultActiveCheckboxDrawObject->pushToDrawObjects(CheckboxActiveBorder);

    EmptyBorderRefPtr DefaultCheckboxButtonBorder = EmptyBorder::create();


    ColorLayerRefPtr DefaultCheckboxButtonBackground = ColorLayer::create();
    DefaultCheckboxButtonBackground->setColor(Color4f(0.93,0.93,0.93,1.0));

    CheckboxButtonRefPtr DefaultCheckboxButton = CheckboxButton::create();
    DefaultCheckboxButton->setEnabled(true);
    DefaultCheckboxButton->setVisible(true);

    DefaultCheckboxButton->setConstraints(NULL);
    //Sizes
    DefaultCheckboxButton->setMinSize(Vec2f(0,0));
    DefaultCheckboxButton->setMaxSize(Vec2f(32767,32767)); //2^15
    DefaultCheckboxButton->setPreferredSize(Vec2f(100,30));
    DefaultCheckboxButton->setSize(Vec2f(0,0));
    DefaultCheckboxButton->setDrawObject(defaultCheckboxDrawObject);

    //Draw Objects
    DefaultCheckboxButton->setCheckboxDrawObject(defaultCheckboxDrawObject);
    DefaultCheckboxButton->setSelectedCheckboxDrawObject(defaultSelectedCheckboxDrawObject);
    DefaultCheckboxButton->setActiveCheckboxDrawObject(defaultActiveCheckboxDrawObject);
    DefaultCheckboxButton->setActiveSelectedCheckboxDrawObject(defaultActiveSelectedCheckboxDrawObject);
    DefaultCheckboxButton->setRolloverCheckboxDrawObject(defaultCheckboxDrawObject);
    DefaultCheckboxButton->setRolloverSelectedCheckboxDrawObject(defaultSelectedCheckboxDrawObject);
    DefaultCheckboxButton->setDisabledCheckboxDrawObject(defaultCheckboxDrawObject);
    DefaultCheckboxButton->setDisabledSelectedCheckboxDrawObject(defaultSelectedCheckboxDrawObject);

    //Border
    DefaultCheckboxButton->setBorder(DefaultCheckboxButtonBorder);
    DefaultCheckboxButton->setActiveBorder(DefaultCheckboxButtonBorder);

    //Background
    DefaultCheckboxButton->setBackground(DefaultCheckboxButtonBackground);
    DefaultCheckboxButton->setActiveBackground(DefaultCheckboxButtonBackground);

    //Opacity
    DefaultCheckboxButton->setOpacity(1.0);

    //Text
    DefaultCheckboxButton->setText("");
    DefaultCheckboxButton->setFont(DefaultFont);
    DefaultCheckboxButton->setAlignment(Vec2f(0.5f,0.5f));
    DefaultCheckboxButton->setTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultCheckboxButton->setActiveTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultCheckboxButton->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultCheckboxButton->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultCheckboxButton->setDisabledTextColor(Color4f(0.4,0.4,0.4,1.0));

    DefaultCheckboxButton->setActiveOffset(Vec2f(0,0));

    CheckboxButton::getClassType().setPrototype(DefaultCheckboxButton);

    //************************** Radio Button Component *****************************
    UIDrawObjectCanvasRefPtr defaultRadioDrawObject = UIDrawObjectCanvas::create();
    UIDrawObjectCanvasRefPtr defaultSelectedRadioDrawObject = UIDrawObjectCanvas::create();
    UIDrawObjectCanvasRefPtr defaultActiveRadioDrawObject = UIDrawObjectCanvas::create();
    UIDrawObjectCanvasRefPtr defaultActiveSelectedRadioDrawObject = UIDrawObjectCanvas::create();

    DiscUIDrawObjectRefPtr RadioBackground = DiscUIDrawObject::create();
    Pnt2f DefaultRadioCenter(10,10);
    RadioBackground->setWidth(10);
    RadioBackground->setHeight(10);
    RadioBackground->setSubDivisions(10);
    RadioBackground->setStartAngleRad(0);
    RadioBackground->setEndAngleRad(6.28318531);
    RadioBackground->setCenterColor(Color4f(1.0,1.0,1.0,1.0));
    RadioBackground->setOuterColor(Color4f(1.0,1.0,1.0,1.0));
    RadioBackground->setOpacity(1.0);
    RadioBackground->setCenter(DefaultRadioCenter);

    ArcUIDrawObjectRefPtr RadioBackgroundBorder = ArcUIDrawObject::create();
    RadioBackgroundBorder->setWidth(10);
    RadioBackgroundBorder->setHeight(10);
    RadioBackgroundBorder->setSubDivisions(20);
    RadioBackgroundBorder->setStartAngleRad(0);
    RadioBackgroundBorder->setEndAngleRad(6.28318531);
    RadioBackgroundBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
    RadioBackgroundBorder->setOpacity(1.0);
    RadioBackgroundBorder->setLineWidth(1);
    RadioBackgroundBorder->setCenter(DefaultRadioCenter);

    DiscUIDrawObjectRefPtr RadioSelected = DiscUIDrawObject::create();
    RadioSelected->setWidth(6);
    RadioSelected->setHeight(6);
    RadioSelected->setSubDivisions(20);
    RadioSelected->setStartAngleRad(0);
    RadioSelected->setEndAngleRad(6.28318531);
    RadioSelected->setCenterColor(Color4f(0.0,0.0,0.0,1.0));
    RadioSelected->setOuterColor(Color4f(0.0,0.0,0.0,1.0));
    RadioSelected->setOpacity(1.0);
    RadioSelected->setCenter(DefaultRadioCenter);

    ArcUIDrawObjectRefPtr RadioActiveBorder = ArcUIDrawObject::create();
    RadioActiveBorder->setWidth(9);
    RadioActiveBorder->setHeight(9);
    RadioActiveBorder->setSubDivisions(10);
    RadioActiveBorder->setStartAngleRad(0);
    RadioActiveBorder->setEndAngleRad(6.28318531);
    RadioActiveBorder->setColor(Color4f(0.0,0.0,1.0,1.0));
    RadioActiveBorder->setOpacity(1.0);
    RadioActiveBorder->setCenter(DefaultRadioCenter);

    defaultRadioDrawObject->pushToDrawObjects(RadioBackground);
    defaultRadioDrawObject->pushToDrawObjects(RadioBackgroundBorder);

    defaultSelectedRadioDrawObject->pushToDrawObjects(RadioBackground);
    defaultSelectedRadioDrawObject->pushToDrawObjects(RadioBackgroundBorder);
    defaultSelectedRadioDrawObject->pushToDrawObjects(RadioSelected);

    defaultActiveRadioDrawObject->pushToDrawObjects(RadioBackground);
    defaultActiveRadioDrawObject->pushToDrawObjects(RadioBackgroundBorder);
    defaultActiveRadioDrawObject->pushToDrawObjects(RadioActiveBorder);

    defaultActiveSelectedRadioDrawObject->pushToDrawObjects(RadioBackground);
    defaultActiveSelectedRadioDrawObject->pushToDrawObjects(RadioBackgroundBorder);
    defaultActiveSelectedRadioDrawObject->pushToDrawObjects(RadioSelected);
    defaultActiveSelectedRadioDrawObject->pushToDrawObjects(RadioActiveBorder);

    EmptyBorderRefPtr DefaultRadioButtonBorder = EmptyBorder::create();

    ColorLayerRefPtr DefaultRadioButtonBackground = ColorLayer::create();
    DefaultRadioButtonBackground->setColor(Color4f(0.93,0.93,0.93,1.0));

    RadioButtonRefPtr DefaultRadioButton = RadioButton::create();
    DefaultRadioButton->setEnabled(true);
    DefaultRadioButton->setVisible(true);
    DefaultRadioButton->setConstraints(NULL);

    //sizes
    DefaultRadioButton->setMinSize(Vec2f(0, 0));
    DefaultRadioButton->setMaxSize(Vec2f(32767,32767));
    DefaultRadioButton->setPreferredSize(Vec2f(100, 30));

    //draw objects
    DefaultRadioButton->setRadioDrawObject(defaultRadioDrawObject);
    DefaultRadioButton->setSelectedRadioDrawObject(defaultSelectedRadioDrawObject);
    DefaultRadioButton->setActiveRadioDrawObject(defaultActiveRadioDrawObject);
    DefaultRadioButton->setActiveSelectedRadioDrawObject(defaultActiveSelectedRadioDrawObject);
    DefaultRadioButton->setRolloverRadioDrawObject(defaultRadioDrawObject);
    DefaultRadioButton->setRolloverSelectedRadioDrawObject(defaultSelectedRadioDrawObject);
    DefaultRadioButton->setDisabledRadioDrawObject(defaultRadioDrawObject);
    DefaultRadioButton->setDisabledSelectedRadioDrawObject(defaultSelectedRadioDrawObject);

    //borders
    DefaultRadioButton->setBorder(DefaultRadioButtonBorder);
    DefaultRadioButton->setActiveBorder(DefaultRadioButtonBorder);

    //backgrounds
    DefaultRadioButton->setBackground(DefaultRadioButtonBackground);
    DefaultRadioButton->setActiveBackground(DefaultRadioButtonBackground);

    //Opacity
    DefaultRadioButton->setOpacity(1.0);

    //text
    DefaultRadioButton->setText("");
    DefaultRadioButton->setFont(DefaultFont);

    //alignment
    DefaultRadioButton->setAlignment(Vec2f(0.5f,0.5f));
    DefaultRadioButton->setTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultRadioButton->setActiveTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultRadioButton->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultRadioButton->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultRadioButton->setDisabledTextColor(Color4f(0.4,0.4,0.4,1.0));

    DefaultRadioButton->setActiveOffset(Vec2f(0,0));

    RadioButton::getClassType().setPrototype(DefaultRadioButton);

    /********Toggle Button********/

    ToggleButtonRefPtr DefaultToggleButton = ToggleButton::create();
    DefaultToggleButton->setEnabled(true);
    DefaultToggleButton->setVisible(true);

    DefaultToggleButton->setConstraints(NULL);
    //Sizes
    DefaultToggleButton->setMinSize(Vec2f(0,0));
    DefaultToggleButton->setMaxSize(Vec2f(32767,32767)); //2^15
    DefaultToggleButton->setPreferredSize(Vec2f(100,50));

    //Border
    DefaultToggleButton->setBorder(DefaultButtonBorder);
    DefaultToggleButton->setDisabledBorder(DefaultDisabledButtonBorder);
    DefaultToggleButton->setActiveBorder(DefaultActiveButtonBorder);

    //Background
    DefaultToggleButton->setBackground(DefaultButtonBackground);
    DefaultToggleButton->setDisabledBackground(DefaultDisabledButtonBackground);
    DefaultToggleButton->setActiveBackground(DefaultButtonBackground);

    //Opacity
    DefaultToggleButton->setOpacity(1.0);

    //Text
    DefaultToggleButton->setText("");
    DefaultToggleButton->setFont(DefaultFont);
    DefaultToggleButton->setAlignment(Vec2f(0.5f,0.5f));
    DefaultToggleButton->setTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultToggleButton->setActiveTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultToggleButton->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultToggleButton->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultToggleButton->setDisabledTextColor(Color4f(0.4,0.4,0.4,1.0));

    DefaultToggleButton->setActiveOffset(Vec2f(2,2));

    ToggleButton::getClassType().setPrototype(DefaultToggleButton);

    /********Text Field********/
    ColorLayerRefPtr DefaultTextFieldBackground = ColorLayer::create();
    DefaultTextFieldBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));

    ColorLayerRefPtr DefaultDisabledTextFieldBackground = ColorLayer::create();
    DefaultDisabledTextFieldBackground->setColor(Color4f(.8, .8, .8, 1.0));

    BevelBorderRefPtr DefaultTextFieldBorder = BevelBorder::create();
    DefaultTextFieldBorder->setRaised(false);
    DefaultTextFieldBorder->setWidth(2);
    DefaultTextFieldBorder->setHighlightInner(Color4f(.9, .9, .9, 1.0));
    DefaultTextFieldBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultTextFieldBorder->setShadowInner(Color4f(0.65, 0.65, 0.65, 1.0));
    DefaultTextFieldBorder->setShadowOuter(Color4f(0.45, 0.45, 0.45, 1.0));

    TextFieldRefPtr DefaultTextField = TextField::create();
    //size
    DefaultTextField->setMinSize(Vec2f(0, 0));
    DefaultTextField->setMaxSize(Vec2f(32767,32767));
    DefaultTextField->setPreferredSize(Vec2f(100, 25));

    //font
    DefaultTextField->setFont(DefaultFont);
    DefaultTextField->setTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultTextField->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultTextField->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultTextField->setDisabledTextColor(Color4f(0.4,0.4,0.4,1.0));

    //background
    DefaultTextField->setBackground(DefaultTextFieldBackground);
    DefaultTextField->setDisabledBackground(DefaultDisabledTextFieldBackground);

    //Border
    DefaultTextField->setBorder(DefaultTextFieldBorder);
    DefaultTextField->setDisabledBorder(DefaultTextFieldBorder);

    DefaultTextField->setAlignment(Vec2f(0.0f,0.5f));

    TextField::getClassType().setPrototype(DefaultTextField);

    /********Password Field********/
    ColorLayerRefPtr DefaultPasswordFieldBackground = ColorLayer::create();
    DefaultPasswordFieldBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));

    ColorLayerRefPtr DefaultDisabledPasswordFieldBackground = ColorLayer::create();
    DefaultDisabledPasswordFieldBackground->setColor(Color4f(.8, .8, .8, 1.0));

    BevelBorderRefPtr DefaultPasswordFieldBorder = BevelBorder::create();
    DefaultPasswordFieldBorder->setRaised(false);
    DefaultPasswordFieldBorder->setWidth(2);
    DefaultPasswordFieldBorder->setHighlightInner(Color4f(.9, .9, .9, 1.0));
    DefaultPasswordFieldBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultPasswordFieldBorder->setShadowInner(Color4f(0.65, 0.65, 0.65, 1.0));
    DefaultPasswordFieldBorder->setShadowOuter(Color4f(0.45, 0.45, 0.45, 1.0));

    PasswordFieldRefPtr DefaultPasswordField = PasswordField::create();
    //size
    DefaultPasswordField->setMinSize(Vec2f(0, 0));
    DefaultPasswordField->setMaxSize(Vec2f(32767,32767));
    DefaultPasswordField->setPreferredSize(Vec2f(100, 25));
    DefaultPasswordField->setEchoChar("*");

    //font
    DefaultPasswordField->setFont(DefaultFont);
    DefaultPasswordField->setTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultPasswordField->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultPasswordField->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultPasswordField->setDisabledTextColor(Color4f(0.4,0.4,0.4,1.0));

    //background
    DefaultPasswordField->setBackground(DefaultPasswordFieldBackground);
    DefaultPasswordField->setDisabledBackground(DefaultDisabledPasswordFieldBackground);

    //Border
    DefaultPasswordField->setBorder(DefaultPasswordFieldBorder);
    DefaultPasswordField->setDisabledBorder(DefaultPasswordFieldBorder);


    PasswordField::getClassType().setPrototype(DefaultPasswordField);

    /********Text Area********/
    ColorLayerRefPtr DefaultTextAreaBackground = ColorLayer::create();
    DefaultTextAreaBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));

    ColorLayerRefPtr DefaultDisabledTextAreaBackground = ColorLayer::create();
    DefaultDisabledTextAreaBackground->setColor(Color4f(.8, .8, .8, 1.0));

    BevelBorderRefPtr DefaultTextAreaBorder = BevelBorder::create();
    DefaultTextAreaBorder->setRaised(false);
    DefaultTextAreaBorder->setWidth(2);
    DefaultTextAreaBorder->setHighlightInner(Color4f(.9, .9, .9, 1.0));
    DefaultTextAreaBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultTextAreaBorder->setShadowInner(Color4f(0.65, 0.65, 0.65, 1.0));
    DefaultTextAreaBorder->setShadowOuter(Color4f(0.45, 0.45, 0.45, 1.0));

    TextAreaRefPtr DefaultTextArea = TextArea::create();
    //size
    DefaultTextArea->setMinSize(Vec2f(0, 0));
    DefaultTextArea->setMaxSize(Vec2f(32767,32767));
    DefaultTextArea->setPreferredSize(Vec2f(100, 25));

    //font
    DefaultTextArea->setFont(DefaultFont);
    DefaultTextArea->setSelectionBoxColor(Color4f(0.0, 0.0, 1.0, 1.0));
    DefaultTextArea->setSelectionTextColor(Color4f(0.0, 0.0, 0.0, 1.0));
    DefaultTextArea->setTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultTextArea->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultTextArea->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultTextArea->setDisabledTextColor(Color4f(0.4,0.4,0.4,1.0));


    //background
    DefaultTextArea->setBackground(DefaultTextAreaBackground);
    DefaultTextArea->setDisabledBackground(DefaultDisabledTextAreaBackground);

    //Border
    DefaultTextArea->setBorder(DefaultTextAreaBorder);
    DefaultTextArea->setDisabledBorder(DefaultTextAreaBorder);


    TextArea::getClassType().setPrototype(DefaultTextArea);

    //************************** ToolTip*****************************
    //Default ToolTipBorder
    LineBorderRefPtr DefaultToolTipLineBorder = LineBorder::create();
    DefaultToolTipLineBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultToolTipLineBorder->setWidth(1);

    ShadowBorderRefPtr DefaultToolTipBorder = OSG::ShadowBorder::create();
    DefaultToolTipBorder->setTopOffset(0);
    DefaultToolTipBorder->setBottomOffset(2);
    DefaultToolTipBorder->setLeftOffset(0);
    DefaultToolTipBorder->setRightOffset(2);
    DefaultToolTipBorder->setInsideBorder(DefaultToolTipLineBorder);
    DefaultToolTipBorder->setCornerRadius(3);
    DefaultToolTipBorder->setInternalColor(Color4f(0.0, 0.0, 0.0, 0.5));
    DefaultToolTipBorder->setEdgeColor(Color4f(0.0, 0.0, 0.0, 0.0));
    DefaultToolTipBorder->setInternalToEdgeColorLength(2);

    //Default ToolTipBackground
    ColorLayerRefPtr DefaultToolTipBackground = ColorLayer::create();
    DefaultToolTipBackground->setColor(Color4f(1.0,1.0,0.9,1.0));

    //Default ToolTip
    LabelRefPtr DefaultToolTip = Label::create();
    DefaultToolTip->setEnabled(true);
    DefaultToolTip->setVisible(true);

    DefaultToolTip->setConstraints(NULL);
    //Sizes
    DefaultToolTip->setMinSize(Vec2f(0,0));
    DefaultToolTip->setMaxSize(Vec2f(32767,32767)); //2^15
    DefaultToolTip->setPreferredSize(Vec2f(100,50));

    //Border
    DefaultToolTip->setBorder(DefaultToolTipBorder);

    //Background
    DefaultToolTip->setBackground(DefaultToolTipBackground);

    //Opacity
    DefaultToolTip->setOpacity(1.0);

    //Text
    DefaultToolTip->setText("");
    DefaultToolTip->setFont(DefaultFont);
    DefaultToolTip->setAlignment(Vec2f(0.0f,0.5f));
    DefaultToolTip->setTextColor(Color4f(0.0,0.0,0.0,1.0));

    setDefaultToolTip(DefaultToolTip);

    //************************** MenuItem*****************************
    //Default MenuItemBorder
    EmptyBorderRefPtr DefaultMenuItemBorder = EmptyBorder::create();

    //Default MenuItemBackground
    ColorLayerRefPtr DefaultMenuItemBackground = ColorLayer::create();
    DefaultMenuItemBackground->setColor(Color4f(1.0,1.0,1.0,1.0));

    //Default MenuItemBorder
    EmptyBorderRefPtr DefaultMenuItemSelectedBorder = EmptyBorder::create();

    //Default MenuItemBackground
    ColorLayerRefPtr DefaultMenuItemSelectedBackground = ColorLayer::create();
    DefaultMenuItemSelectedBackground->setColor(Color4f(0.3,0.3,1.0,1.0));

    //Default MenuItem
    MenuItemRefPtr DefaultMenuItem = MenuItem::create();
    DefaultMenuItem->setEnabled(true);
    DefaultMenuItem->setVisible(true);

    DefaultMenuItem->setConstraints(NULL);
    //Sizes
    DefaultMenuItem->setMinSize(Vec2f(0,0));
    DefaultMenuItem->setMaxSize(Vec2f(32767,32767)); //2^15
    DefaultMenuItem->setPreferredSize(Vec2f(100,25));

    //Border
    DefaultMenuItem->setBorder(DefaultMenuItemBorder);

    //Background
    DefaultMenuItem->setBackground(DefaultMenuItemBackground);

    //Opacity
    DefaultMenuItem->setOpacity(1.0);

    //Accelerators
    DefaultMenuItem->setAcceleratorModifiers(0);
    DefaultMenuItem->setAcceleratorKey(KeyEventDetails::KEY_NONE);

    //Selected
    DefaultMenuItem->setSelected(false);
    DefaultMenuItem->setSelectedBorder(DefaultMenuItemSelectedBorder);
    DefaultMenuItem->setSelectedBackground(DefaultMenuItemSelectedBackground);

    //Text
    DefaultMenuItem->setText("");
    DefaultMenuItem->setFont(DefaultFont);
    DefaultMenuItem->setTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultMenuItem->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultMenuItem->setSelectedTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultMenuItem->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultMenuItem->setDisabledTextColor(Color4f(0.4,0.4,0.4,1.0));

    MenuItem::getClassType().setPrototype(DefaultMenuItem);

    //************************** Menu*****************************
    //Default MenuBorder
    EmptyBorderRefPtr DefaultMenuBorder = EmptyBorder::create();

    //Default MenuBackground
    ColorLayerRefPtr DefaultMenuBackground = ColorLayer::create();
    DefaultMenuBackground->setColor(Color4f(1.0,1.0,1.0,1.0));

    //Default MenuBorder
    EmptyBorderRefPtr DefaultMenuSelectedBorder = EmptyBorder::create();

    //Default MenuBackground
    ColorLayerRefPtr DefaultMenuSelectedBackground = ColorLayer::create();
    DefaultMenuSelectedBackground->setColor(Color4f(0.3,0.3,1.0,1.0));


    //Expanding Draw Object
    PolygonUIDrawObjectRefPtr MenuExpandablePolygon = PolygonUIDrawObject::create();
    MenuExpandablePolygon->setColor(Color4f(0.0,0.0,0.0,1.0));
    MenuExpandablePolygon->setOpacity(1.0);
    MenuExpandablePolygon->editMFVerticies()->push_back(Pnt2f(0,0));
    MenuExpandablePolygon->editMFVerticies()->push_back(Pnt2f(0,7));
    MenuExpandablePolygon->editMFVerticies()->push_back(Pnt2f(4,4));

    UIDrawObjectCanvasRefPtr defaultMenuDrawObject = UIDrawObjectCanvas::create();
    defaultMenuDrawObject->pushToDrawObjects(MenuExpandablePolygon);

    //Default Menu
    MenuRefPtr DefaultMenu = Menu::create();
    DefaultMenu->setEnabled(true);
    DefaultMenu->setVisible(true);

    DefaultMenu->setConstraints(NULL);
    //Sizes
    DefaultMenu->setMinSize(Vec2f(0,0));
    DefaultMenu->setMaxSize(Vec2f(32767,32767)); //2^15
    DefaultMenu->setPreferredSize(Vec2f(100,25));

    //Border
    DefaultMenu->setBorder(DefaultMenuBorder);

    //Background
    DefaultMenu->setBackground(DefaultMenuBackground);

    //Opacity
    DefaultMenu->setOpacity(1.0);

    //Accelerators
    DefaultMenu->setAcceleratorModifiers(0);
    DefaultMenu->setAcceleratorKey(KeyEventDetails::KEY_NONE);

    //Selected
    DefaultMenu->setSelected(false);
    DefaultMenu->setSelectedBorder(DefaultMenuSelectedBorder);
    DefaultMenu->setSelectedBackground(DefaultMenuSelectedBackground);

    //Text
    DefaultMenu->setText("");
    DefaultMenu->setFont(DefaultFont);
    DefaultMenu->setTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultMenu->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultMenu->setSelectedTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultMenu->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultMenu->setDisabledTextColor(Color4f(0.4,0.4,0.4,1.0));

    //Expanding Draw Object
    DefaultMenu->setExpandDrawObject(defaultMenuDrawObject);

    Menu::getClassType().setPrototype(DefaultMenu);

    //************************** PopupMenu*****************************
    //Default PopupMenuBorder
    LineBorderRefPtr DefaultPopupMenuLineBorder = LineBorder::create();
    DefaultPopupMenuLineBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultPopupMenuLineBorder->setWidth(1);

    ShadowBorderRefPtr DefaultPopupMenuBorder = OSG::ShadowBorder::create();
    DefaultPopupMenuBorder->setTopOffset(0);
    DefaultPopupMenuBorder->setBottomOffset(2);
    DefaultPopupMenuBorder->setLeftOffset(0);
    DefaultPopupMenuBorder->setRightOffset(2);
    DefaultPopupMenuBorder->setInsideBorder(DefaultPopupMenuLineBorder);
    DefaultPopupMenuBorder->setCornerRadius(3);
    DefaultPopupMenuBorder->setInternalColor(Color4f(0.0, 0.0, 0.0, 0.5));
    DefaultPopupMenuBorder->setEdgeColor(Color4f(0.0, 0.0, 0.0, 0.0));
    DefaultPopupMenuBorder->setInternalToEdgeColorLength(2);

    //Default PopupMenuBackground
    ColorLayerRefPtr DefaultPopupMenuBackground = ColorLayer::create();
    DefaultPopupMenuBackground->setColor(Color4f(1.0,1.0,1.0,1.0));

    //Default PopupMenu
    PopupMenuRefPtr DefaultPopupMenu = PopupMenu::create();
    DefaultPopupMenu->setEnabled(true);
    DefaultPopupMenu->setVisible(false);

    DefaultPopupMenu->setConstraints(NULL);
    //Sizes
    DefaultPopupMenu->setMinSize(Vec2f(0,0));
    DefaultPopupMenu->setMaxSize(Vec2f(32767,32767)); //2^15
    DefaultPopupMenu->setPreferredSize(Vec2f(100,50));

    //Border
    DefaultPopupMenu->setBorder(DefaultPopupMenuBorder);

    //Background
    DefaultPopupMenu->setBackground(DefaultPopupMenuBackground);

    //Opacity
    DefaultPopupMenu->setOpacity(1.0);

    //SubMenu delay in seconds
    DefaultPopupMenu->setSubMenuDelay(getSubMenuPopupTime());

    PopupMenu::getClassType().setPrototype(DefaultPopupMenu);

    //************************** MenuBar*****************************
    //Default MenuBarBorder
    EmptyBorderRefPtr DefaultMenuBarBorder = EmptyBorder::create();

    //Default MenuBarBackground
    ColorLayerRefPtr DefaultMenuBarBackground = ColorLayer::create();
    DefaultMenuBarBackground->setColor(Color4f(0.93,0.93,0.93,1.0));

    //Default MenuBar
    MenuBarRefPtr DefaultMenuBar = MenuBar::create();
    DefaultMenuBar->setEnabled(true);
    DefaultMenuBar->setVisible(true);

    DefaultMenuBar->setConstraints(NULL);
    //Sizes
    DefaultMenuBar->setMinSize(Vec2f(0,0));
    DefaultMenuBar->setMaxSize(Vec2f(32767,32767)); //2^15
    DefaultMenuBar->setPreferredSize(Vec2f(100,50));

    //Border
    DefaultMenuBar->setBorder(DefaultMenuBarBorder);

    //Background
    DefaultMenuBar->setBackground(DefaultMenuBarBackground);

    //Opacity
    DefaultMenuBar->setOpacity(1.0);

    //SubMenu delay in seconds
    DefaultMenuBar->setMenuDelay(getSubMenuPopupTime());

    MenuBar::getClassType().setPrototype(DefaultMenuBar);

    //************************** ScrollBar*****************************
    //Default ScrollBarBorder
    EmptyBorderRefPtr DefaultScrollBarBorder = EmptyBorder::create();

    //Default ScrollBarBackground
    EmptyLayerRefPtr DefaultScrollBarBackground = EmptyLayer::create();

    //Vertical Min Draw Object
    PolygonUIDrawObjectRefPtr DefaultScrollBarVerticalMinButtonDrawObject = PolygonUIDrawObject::create();
    DefaultScrollBarVerticalMinButtonDrawObject->setColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultScrollBarVerticalMinButtonDrawObject->setOpacity(1.0);
    DefaultScrollBarVerticalMinButtonDrawObject->editMFVerticies()->push_back(Pnt2f(0,4));
    DefaultScrollBarVerticalMinButtonDrawObject->editMFVerticies()->push_back(Pnt2f(7,4));
    DefaultScrollBarVerticalMinButtonDrawObject->editMFVerticies()->push_back(Pnt2f(4,0));

    UIDrawObjectCanvasRefPtr DefaultScrollBarVerticalMinButtonCanvas = UIDrawObjectCanvas::create();
    DefaultScrollBarVerticalMinButtonCanvas->pushToDrawObjects(DefaultScrollBarVerticalMinButtonDrawObject);

    //Vertical Min Button
    ButtonRefPtr DefaultScrollBarVerticalMinButton = Button::create();
    DefaultScrollBarVerticalMinButton->setPreferredSize(Vec2f(20,20));
    DefaultScrollBarVerticalMinButton->setEnableActionOnMouseDownTime(true);
    DefaultScrollBarVerticalMinButton->setActionOnMouseDownRate(0.1);

    DefaultScrollBarVerticalMinButton->setDrawObject(DefaultScrollBarVerticalMinButtonCanvas);
    DefaultScrollBarVerticalMinButton->setActiveDrawObject(DefaultScrollBarVerticalMinButtonCanvas);
    DefaultScrollBarVerticalMinButton->setFocusedDrawObject(DefaultScrollBarVerticalMinButtonCanvas);
    DefaultScrollBarVerticalMinButton->setRolloverDrawObject(DefaultScrollBarVerticalMinButtonCanvas);
    DefaultScrollBarVerticalMinButton->setDisabledDrawObject(DefaultScrollBarVerticalMinButtonCanvas);

    //Vertical Max Draw Object
    PolygonUIDrawObjectRefPtr DefaultScrollBarVerticalMaxButtonDrawObject = PolygonUIDrawObject::create();
    DefaultScrollBarVerticalMaxButtonDrawObject->setColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultScrollBarVerticalMaxButtonDrawObject->setOpacity(1.0);
    DefaultScrollBarVerticalMaxButtonDrawObject->editMFVerticies()->push_back(Pnt2f(0,0));
    DefaultScrollBarVerticalMaxButtonDrawObject->editMFVerticies()->push_back(Pnt2f(7,0));
    DefaultScrollBarVerticalMaxButtonDrawObject->editMFVerticies()->push_back(Pnt2f(4,4));

    UIDrawObjectCanvasRefPtr DefaultScrollBarVerticalMaxButtonCanvas = UIDrawObjectCanvas::create();
    DefaultScrollBarVerticalMaxButtonCanvas->pushToDrawObjects(DefaultScrollBarVerticalMaxButtonDrawObject);
    //Vertical Max Button
    ButtonRefPtr DefaultScrollBarVerticalMaxButton = Button::create();
    DefaultScrollBarVerticalMaxButton->setPreferredSize(Vec2f(20,20));
    DefaultScrollBarVerticalMaxButton->setEnableActionOnMouseDownTime(true);
    DefaultScrollBarVerticalMaxButton->setActionOnMouseDownRate(0.1);

    DefaultScrollBarVerticalMaxButton->setDrawObject(DefaultScrollBarVerticalMaxButtonCanvas);
    DefaultScrollBarVerticalMaxButton->setActiveDrawObject(DefaultScrollBarVerticalMaxButtonCanvas);
    DefaultScrollBarVerticalMaxButton->setFocusedDrawObject(DefaultScrollBarVerticalMaxButtonCanvas);
    DefaultScrollBarVerticalMaxButton->setRolloverDrawObject(DefaultScrollBarVerticalMaxButtonCanvas);
    DefaultScrollBarVerticalMaxButton->setDisabledDrawObject(DefaultScrollBarVerticalMaxButtonCanvas);

    //Horizontal Min Draw Object
    PolygonUIDrawObjectRefPtr DefaultScrollBarHorizontalMinButtonDrawObject = PolygonUIDrawObject::create();
    DefaultScrollBarHorizontalMinButtonDrawObject->setColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultScrollBarHorizontalMinButtonDrawObject->setOpacity(1.0);
    DefaultScrollBarHorizontalMinButtonDrawObject->editMFVerticies()->push_back(Pnt2f(4,0));
    DefaultScrollBarHorizontalMinButtonDrawObject->editMFVerticies()->push_back(Pnt2f(4,7));
    DefaultScrollBarHorizontalMinButtonDrawObject->editMFVerticies()->push_back(Pnt2f(0,4));

    UIDrawObjectCanvasRefPtr DefaultScrollBarHorizontalMinButtonCanvas = UIDrawObjectCanvas::create();
    DefaultScrollBarHorizontalMinButtonCanvas->pushToDrawObjects(DefaultScrollBarHorizontalMinButtonDrawObject);

    //Horizontal Min Button
    ButtonRefPtr DefaultScrollBarHorizontalMinButton = Button::create();
    DefaultScrollBarHorizontalMinButton->setPreferredSize(Vec2f(20,20));
    DefaultScrollBarHorizontalMinButton->setEnableActionOnMouseDownTime(true);
    DefaultScrollBarHorizontalMinButton->setActionOnMouseDownRate(0.1);

    DefaultScrollBarHorizontalMinButton->setDrawObject(DefaultScrollBarHorizontalMinButtonCanvas);
    DefaultScrollBarHorizontalMinButton->setActiveDrawObject(DefaultScrollBarHorizontalMinButtonCanvas);
    DefaultScrollBarHorizontalMinButton->setFocusedDrawObject(DefaultScrollBarHorizontalMinButtonCanvas);
    DefaultScrollBarHorizontalMinButton->setRolloverDrawObject(DefaultScrollBarHorizontalMinButtonCanvas);
    DefaultScrollBarHorizontalMinButton->setDisabledDrawObject(DefaultScrollBarHorizontalMinButtonCanvas);

    //Horizontal Max Draw Object
    PolygonUIDrawObjectRefPtr DefaultScrollBarHorizontalMaxButtonDrawObject = PolygonUIDrawObject::create();
    DefaultScrollBarHorizontalMaxButtonDrawObject->setColor(Color4f(0.0,0.0,0.0,1.0));
    DefaultScrollBarHorizontalMaxButtonDrawObject->setOpacity(1.0);
    DefaultScrollBarHorizontalMaxButtonDrawObject->editMFVerticies()->push_back(Pnt2f(0,0));
    DefaultScrollBarHorizontalMaxButtonDrawObject->editMFVerticies()->push_back(Pnt2f(0,7));
    DefaultScrollBarHorizontalMaxButtonDrawObject->editMFVerticies()->push_back(Pnt2f(4,4));

    UIDrawObjectCanvasRefPtr DefaultScrollBarHorizontalMaxButtonCanvas = UIDrawObjectCanvas::create();
    DefaultScrollBarHorizontalMaxButtonCanvas->pushToDrawObjects(DefaultScrollBarHorizontalMaxButtonDrawObject);
    //Horizontal Max Button
    ButtonRefPtr DefaultScrollBarHorizontalMaxButton = Button::create();
    DefaultScrollBarHorizontalMaxButton->setPreferredSize(Vec2f(20,20));
    DefaultScrollBarHorizontalMaxButton->setEnableActionOnMouseDownTime(true);
    DefaultScrollBarHorizontalMaxButton->setActionOnMouseDownRate(0.1);

    DefaultScrollBarHorizontalMaxButton->setDrawObject(DefaultScrollBarHorizontalMaxButtonCanvas);
    DefaultScrollBarHorizontalMaxButton->setActiveDrawObject(DefaultScrollBarHorizontalMaxButtonCanvas);
    DefaultScrollBarHorizontalMaxButton->setFocusedDrawObject(DefaultScrollBarHorizontalMaxButtonCanvas);
    DefaultScrollBarHorizontalMaxButton->setRolloverDrawObject(DefaultScrollBarHorizontalMaxButtonCanvas);
    DefaultScrollBarHorizontalMaxButton->setDisabledDrawObject(DefaultScrollBarHorizontalMaxButtonCanvas);

    //Scroll Field
    //Scroll Field Border
    BevelBorderRefPtr DefaultScrollFieldBorder = BevelBorder::create();
    DefaultScrollFieldBorder->setRaised(true);
    DefaultScrollFieldBorder->setWidth(1);
    DefaultScrollFieldBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultScrollFieldBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultScrollFieldBorder->setShadowInner(Color4f(0.65, 0.65, 0.65, 1.0));
    DefaultScrollFieldBorder->setShadowOuter(Color4f(0.45, 0.45, 0.45, 1.0));

    //Scroll Field Disabled Border
    BevelBorderRefPtr DefaultDisabledScrollFieldBorder = BevelBorder::create();
    DefaultDisabledScrollFieldBorder->setRaised(true);
    DefaultDisabledScrollFieldBorder->setWidth(1);
    DefaultDisabledScrollFieldBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultDisabledScrollFieldBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultDisabledScrollFieldBorder->setShadowInner(Color4f(0.85, 0.85, 0.85, 1.0));
    DefaultDisabledScrollFieldBorder->setShadowOuter(Color4f(0.65, 0.65, 0.65, 1.0));

    //Scroll Field Background
    ColorLayerRefPtr DefaultScrollFieldBackground = ColorLayer::create();
    DefaultScrollFieldBackground->setColor(Color4f(0.93,0.93,0.93,1.0));

    //Scroll Field Disabled Background
    ColorLayerRefPtr DefaultDisabledScrollFieldBackground = ColorLayer::create();
    DefaultDisabledScrollFieldBackground->setColor(Color4f(1.0,1.0,1.0,1.0));

    ButtonRefPtr DefaultScrollFieldButton = Button::create();
    DefaultScrollFieldButton->setPreferredSize(Vec2f(20,20));
    DefaultScrollFieldButton->setEnableActionOnMouseDownTime(true);
    DefaultScrollFieldButton->setActionOnMouseDownRate(0.2);

    DefaultScrollFieldButton->setBorder(DefaultScrollFieldBorder);
    DefaultScrollFieldButton->setActiveBorder(DefaultScrollFieldBorder);
    DefaultScrollFieldButton->setRolloverBorder(DefaultScrollFieldBorder);
    DefaultScrollFieldButton->setFocusedBorder(DefaultScrollFieldBorder);
    DefaultScrollFieldButton->setDisabledBorder(DefaultDisabledScrollFieldBorder);

    DefaultScrollFieldButton->setBackground(DefaultScrollFieldBackground);
    DefaultScrollFieldButton->setActiveBackground(DefaultScrollFieldBackground);
    DefaultScrollFieldButton->setRolloverBackground(DefaultScrollFieldBackground);
    DefaultScrollFieldButton->setFocusedBackground(DefaultScrollFieldBackground);
    DefaultScrollFieldButton->setDisabledBackground(DefaultDisabledScrollFieldBackground);

    //Scroll Bar
    //Scroll Bar Border
    BevelBorderRefPtr DefaultScrollBarDrawObjectBorder = BevelBorder::create();
    DefaultScrollBarDrawObjectBorder->setRaised(true);
    DefaultScrollBarDrawObjectBorder->setWidth(2);
    DefaultScrollBarDrawObjectBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultScrollBarDrawObjectBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultScrollBarDrawObjectBorder->setShadowInner(Color4f(0.65, 0.65, 0.65, 1.0));
    DefaultScrollBarDrawObjectBorder->setShadowOuter(Color4f(0.45, 0.45, 0.45, 1.0));

    //Scroll Bar Disabled Border
    BevelBorderRefPtr DefaultDisabledScrollBarDrawObjectBorder = BevelBorder::create();
    DefaultDisabledScrollBarDrawObjectBorder->setRaised(true);
    DefaultDisabledScrollBarDrawObjectBorder->setWidth(2);
    DefaultDisabledScrollBarDrawObjectBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultDisabledScrollBarDrawObjectBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultDisabledScrollBarDrawObjectBorder->setShadowInner(Color4f(0.85, 0.85, 0.85, 1.0));
    DefaultDisabledScrollBarDrawObjectBorder->setShadowOuter(Color4f(0.65, 0.65, 0.65, 1.0));


    //Scroll Bar Rollover border
    BevelBorderRefPtr DefaultRolloverScrollBarDrawObjectBorder = BevelBorder::create();
    DefaultRolloverScrollBarDrawObjectBorder->setRaised(true);
    DefaultRolloverScrollBarDrawObjectBorder->setWidth(2);
    DefaultRolloverScrollBarDrawObjectBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultRolloverScrollBarDrawObjectBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultRolloverScrollBarDrawObjectBorder->setShadowInner(Color4f(0.65, 0.65, 0.65, 1.0));
    DefaultRolloverScrollBarDrawObjectBorder->setShadowOuter(Color4f(0.45, 0.45, 0.45, 1.0));

    //Scroll Bar Rollover border
    BevelBorderRefPtr DefaultActiveScrollBarDrawObjectBorder = BevelBorder::create();
    DefaultActiveScrollBarDrawObjectBorder->setRaised(false);
    DefaultActiveScrollBarDrawObjectBorder->setWidth(2);
    DefaultActiveScrollBarDrawObjectBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultActiveScrollBarDrawObjectBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultActiveScrollBarDrawObjectBorder->setShadowInner(Color4f(0.65, 0.65, 0.65, 1.0));
    DefaultActiveScrollBarDrawObjectBorder->setShadowOuter(Color4f(0.45, 0.45, 0.45, 1.0));

    //Scroll Bar Background
    ColorLayerRefPtr DefaultScrollBarDrawObjectBackground = ColorLayer::create();
    DefaultScrollBarDrawObjectBackground->setColor(Color4f(0.93,0.93,0.93,1.0));

    //Scroll Bar Disabled Background
    ColorLayerRefPtr DefaultDisabledScrollBarDrawObjectBackground = ColorLayer::create();
    DefaultDisabledScrollBarDrawObjectBackground->setColor(Color4f(1.0,1.0,1.0,1.0));

    //Scroll Bar Rollover Background
    ColorLayerRefPtr DefaultRolloverScrollBarDrawObjectBackground = ColorLayer::create();
    DefaultRolloverScrollBarDrawObjectBackground->setColor(Color4f(1.0,1.0,1.0,1.0));

    ButtonRefPtr DefaultScrollBarDrawObject = Button::create();
    DefaultScrollBarDrawObject->setBorder(DefaultScrollBarDrawObjectBorder);
    DefaultScrollBarDrawObject->setRolloverBorder(DefaultRolloverScrollBarDrawObjectBorder);
    DefaultScrollBarDrawObject->setFocusedBorder(DefaultScrollBarDrawObjectBorder);
    DefaultScrollBarDrawObject->setDisabledBorder(DefaultDisabledScrollBarDrawObjectBorder);
    DefaultScrollBarDrawObject->setActiveBorder(DefaultActiveScrollBarDrawObjectBorder);

    DefaultScrollBarDrawObject->setBackground(DefaultScrollBarDrawObjectBackground);
    DefaultScrollBarDrawObject->setRolloverBackground(DefaultRolloverScrollBarDrawObjectBackground);
    DefaultScrollBarDrawObject->setFocusedBackground(DefaultScrollBarDrawObjectBackground);
    DefaultScrollBarDrawObject->setDisabledBackground(DefaultDisabledScrollBarDrawObjectBackground);
    DefaultScrollBarDrawObject->setActiveBackground(DefaultScrollBarDrawObjectBackground);

    //Default ScrollBar
    ScrollBarRefPtr DefaultScrollBar = ScrollBar::create();
    DefaultScrollBar->setEnabled(true);
    DefaultScrollBar->setVisible(true);

    DefaultScrollBar->setConstraints(NULL);
    //Sizes
    DefaultScrollBar->setMinSize(Vec2f(0,0));
    DefaultScrollBar->setMaxSize(Vec2f(32767,32767)); //2^15
    DefaultScrollBar->setPreferredSize(Vec2f(20,20));

    //Border
    DefaultScrollBar->setBorder(DefaultScrollBarBorder);
    DefaultScrollBar->setRolloverBorder(DefaultScrollBarBorder);
    DefaultScrollBar->setFocusedBorder(DefaultScrollBarBorder);
    DefaultScrollBar->setDisabledBorder(DefaultScrollBarBorder);

    //Background
    DefaultScrollBar->setBackground(DefaultScrollBarBackground);
    DefaultScrollBar->setRolloverBackground(DefaultScrollBarBackground);
    DefaultScrollBar->setFocusedBackground(DefaultScrollBarBackground);
    DefaultScrollBar->setDisabledBackground(DefaultScrollBarBackground);

    //Opacity
    DefaultScrollBar->setOpacity(1.0);

    //Min Button
    DefaultScrollBar->setVerticalMinButton(DefaultScrollBarVerticalMinButton);
    DefaultScrollBar->setHorizontalMinButton(DefaultScrollBarHorizontalMinButton);

    //Max Button
    DefaultScrollBar->setVerticalMaxButton(DefaultScrollBarVerticalMaxButton);
    DefaultScrollBar->setHorizontalMaxButton(DefaultScrollBarHorizontalMaxButton);

    //Scroll Field
    DefaultScrollBar->setVerticalScrollField(DefaultScrollFieldButton);
    DefaultScrollBar->setHorizontalScrollField(DefaultScrollFieldButton);

    //Scroll Bar
    DefaultScrollBar->setVerticalScrollBar(DefaultScrollBarDrawObject);
    DefaultScrollBar->setHorizontalScrollBar(DefaultScrollBarDrawObject);
    DefaultScrollBar->setScrollBarMinLength(20);

    ScrollBar::getClassType().setPrototype(DefaultScrollBar);

    //************************** ScrollPanel*****************************
    //Default ScrollPanelBorder
    EmptyBorderRefPtr DefaultScrollPanelBorder = EmptyBorder::create();

    //Default ScrollPanelBackground
    EmptyLayerRefPtr DefaultScrollPanelBackground = EmptyLayer::create();

    //Default ScrollPanel
    ScrollPanelRefPtr DefaultScrollPanel = ScrollPanel::create();
    DefaultScrollPanel->setEnabled(true);
    DefaultScrollPanel->setVisible(true);

    DefaultScrollPanel->setConstraints(NULL);
    //Sizes
    DefaultScrollPanel->setMinSize(Vec2f(0,0));
    DefaultScrollPanel->setMaxSize(Vec2f(32767,32767)); //2^15
    DefaultScrollPanel->setPreferredSize(Vec2f(100,100));

    //Border
    DefaultScrollPanel->setBorder(DefaultScrollPanelBorder);
    DefaultScrollPanel->setRolloverBorder(DefaultScrollPanelBorder);
    DefaultScrollPanel->setFocusedBorder(DefaultScrollPanelBorder);
    DefaultScrollPanel->setDisabledBorder(DefaultScrollPanelBorder);

    //Background
    DefaultScrollPanel->setBackground(DefaultScrollPanelBackground);
    DefaultScrollPanel->setRolloverBackground(DefaultScrollPanelBackground);
    DefaultScrollPanel->setFocusedBackground(DefaultScrollPanelBackground);
    DefaultScrollPanel->setDisabledBackground(DefaultScrollPanelBackground);

    //Opacity
    DefaultScrollPanel->setOpacity(1.0);

    //Vertical Scroll Bar
    DefaultScrollPanel->setVerticalScrollBarDisplayPolicy(ScrollPanel::SCROLLBAR_AS_NEEDED);

    //Horizontal Scroll Bar
    DefaultScrollPanel->setHorizontalScrollBarDisplayPolicy(ScrollPanel::SCROLLBAR_AS_NEEDED);

    ScrollPanel::getClassType().setPrototype(DefaultScrollPanel);

    //************************** RotatedComponent*****************************
    //Default RotatedComponentBorder
    EmptyBorderRefPtr DefaultRotatedComponentBorder = EmptyBorder::create();

    //Default RotatedComponentBackground
    EmptyLayerRefPtr DefaultRotatedComponentBackground = EmptyLayer::create();

    //Default RotatedComponent
    RotatedComponentRefPtr DefaultRotatedComponent = RotatedComponent::create();
    DefaultRotatedComponent->setEnabled(true);
    DefaultRotatedComponent->setVisible(true);

    DefaultRotatedComponent->setConstraints(NULL);
    //Sizes
    DefaultRotatedComponent->setMinSize(Vec2f(0,0));
    DefaultRotatedComponent->setMaxSize(Vec2f(32767,32767)); //2^15
    DefaultRotatedComponent->setPreferredSize(Vec2f(100,100));

    //Border
    DefaultRotatedComponent->setBorder(DefaultRotatedComponentBorder);
    DefaultRotatedComponent->setRolloverBorder(DefaultRotatedComponentBorder);
    DefaultRotatedComponent->setFocusedBorder(DefaultRotatedComponentBorder);
    DefaultRotatedComponent->setDisabledBorder(DefaultRotatedComponentBorder);

    //Background
    DefaultRotatedComponent->setBackground(DefaultRotatedComponentBackground);
    DefaultRotatedComponent->setRolloverBackground(DefaultRotatedComponentBackground);
    DefaultRotatedComponent->setFocusedBackground(DefaultRotatedComponentBackground);
    DefaultRotatedComponent->setDisabledBackground(DefaultRotatedComponentBackground);

    //Opacity
    DefaultRotatedComponent->setOpacity(1.0);

    DefaultRotatedComponent->setInternalComponent(NULL);

    DefaultRotatedComponent->setResizePolicy(RotatedComponent::RESIZE_TO_MIN);

    RotatedComponent::getClassType().setPrototype(DefaultRotatedComponent);
    /*******Borders********/
    /*******Line Border********/

    LineBorderRefPtr DefaultLineBorder = LineBorder::create();
    DefaultLineBorder->setWidth(1);
    DefaultLineBorder->setColor(Color4f(0.0, 0.0, 0.0, 1.0));

    LineBorder::getClassType().setPrototype(DefaultLineBorder);

    /********Etched Border********/

    EtchedBorderRefPtr DefaultEtchedBorder = EtchedBorder::create();
    DefaultEtchedBorder->setWidth(2);
    DefaultEtchedBorder->setRaised(true);
    DefaultEtchedBorder->setHighlight(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultEtchedBorder->setShadow(Color4f(0.65, 0.65, 0.65, 1.0));

    EtchedBorder::getClassType().setPrototype(DefaultEtchedBorder);

    /********Empty Border*********/
    EmptyBorderRefPtr DefaultEmptyBorder = EmptyBorder::create();
    DefaultEmptyBorder->setTopWidth(0);
    DefaultEmptyBorder->setBottomWidth(0);
    DefaultEmptyBorder->setRightWidth(0);
    DefaultEmptyBorder->setLeftWidth(0);

    EmptyBorder::getClassType().setPrototype(DefaultEmptyBorder);


    /********Bevel Border**********/

    BevelBorderRefPtr DefaultBevelBorder = BevelBorder::create();
    DefaultBevelBorder->setRaised(true);
    DefaultBevelBorder->setWidth(2);
    DefaultBevelBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultBevelBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultBevelBorder->setShadowInner(Color4f(0.65, 0.65, 0.65, 1.0));
    DefaultBevelBorder->setShadowOuter(Color4f(0.45, 0.45, 0.45, 1.0));

    BevelBorder::getClassType().setPrototype(DefaultBevelBorder);

    /********Matte Border**********/

    MatteBorderRefPtr DefaultMatteBorder = MatteBorder::create();
    DefaultMatteBorder->setRightWidth(1);
    DefaultMatteBorder->setLeftWidth(1);
    DefaultMatteBorder->setTopWidth(1);
    DefaultMatteBorder->setBottomWidth(1);
    DefaultMatteBorder->setColor(Color4f(0.0, 0.0, 0.0, 1.0));

    MatteBorder::getClassType().setPrototype(DefaultMatteBorder);

    /********Compound Border********/
    CompoundBorderRefPtr DefaultCompoundBorder = CompoundBorder::create();
    DefaultCompoundBorder->setInnerBorder(NULL);
    DefaultCompoundBorder->setOuterBorder(NULL);

    CompoundBorder::getClassType().setPrototype(DefaultCompoundBorder);

    /********Rounded Corner Line Border********/
    RoundedCornerLineBorderRefPtr DefaultRoundedCornerLineBorder = RoundedCornerLineBorder::create();
    DefaultRoundedCornerLineBorder->setCornerRadius(8);
    DefaultRoundedCornerLineBorder->setWidth(2);
    DefaultRoundedCornerLineBorder->setColor(Color4f(0.0, 0.0, 0.0, 1.0));

    RoundedCornerLineBorder::getClassType().setPrototype(DefaultRoundedCornerLineBorder);

    /*********Backgounds***********/
    /*********Color Background**********/
    ColorLayerRefPtr DefaultColorBackground = ColorLayer::create();
    DefaultColorBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));

    ColorLayer::getClassType().setPrototype(DefaultColorBackground);

    /**********Gradient Background***********/
    GradientLayerRefPtr DefaultGradientBackground = GradientLayer::create();
    DefaultGradientBackground->editMFColors()->push_back(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultGradientBackground->editMFStops()->push_back(0.0);
    DefaultGradientBackground->editMFColors()->push_back(Color4f(1.0, 1.0, 1.0, 1.0));
    DefaultGradientBackground->editMFStops()->push_back(1.0);
    DefaultGradientBackground->setStartPosition(Vec2f(0.0f,0.0f));
    DefaultGradientBackground->setEndPosition(Vec2f(1.0f,0.0f));

    GradientLayer::getClassType().setPrototype(DefaultGradientBackground);

    /**********Material Background***********/
    MaterialLayerRefPtr DefaultMaterialBackground = MaterialLayer::create();
    DefaultMaterialBackground->setMaterial(NULL);

    MaterialLayer::getClassType().setPrototype(DefaultMaterialBackground);

    /*********Texture Background********/
    TextureLayerRefPtr DefaultTextureBackground = TextureLayer::create();
    DefaultTextureBackground->setTexture(NULL);

    TextureLayer::getClassType().setPrototype(DefaultTextureBackground);


    //************************** List *****************************
    //Default RotatedComponentBorder
    EmptyBorderRefPtr DefaultListBorder = EmptyBorder::create();

    //Default RotatedComponentBackground
    EmptyLayerRefPtr DefaultListBackground = EmptyLayer::create();

    //Default RotatedComponent
    ListRefPtr DefaultList = List::create();
    DefaultList->setEnabled(true);
    DefaultList->setVisible(true);

    DefaultList->setConstraints(NULL);
    //Sizes
    DefaultList->setMinSize(Vec2f(0,0));
    DefaultList->setMaxSize(Vec2f(32767,32767)); //2^15
    DefaultList->setPreferredSize(Vec2f(100,100));

    //Border
    DefaultList->setBorder(DefaultListBorder);
    DefaultList->setRolloverBorder(DefaultListBorder);
    DefaultList->setFocusedBorder(DefaultListBorder);
    DefaultList->setDisabledBorder(DefaultListBorder);

    //Background
    DefaultList->setBackground(DefaultListBackground);
    DefaultList->setRolloverBackground(DefaultListBackground);
    DefaultList->setFocusedBackground(DefaultListBackground);
    DefaultList->setDisabledBackground(DefaultListBackground);

    //Opacity
    DefaultList->setOpacity(1.0);

    DefaultList->setCellMajorAxisLength(25);

    List::getClassType().setPrototype(DefaultList);


    ///[>************************* TableHeader *****************************
    ////Default RotatedComponentBorder
    //EmptyBorderRefPtr DefaultTableHeaderBorder = EmptyBorder::create();

    ////Default RotatedComponentBackground
    //EmptyLayerRefPtr DefaultTableHeaderBackground = EmptyLayer::create();

    ////Default RotatedComponent
    //TableHeaderRefPtr DefaultTableHeader = TableHeader::create();
    //DefaultTableHeader->setEnabled(true);
    //DefaultTableHeader->setVisible(true);

    //DefaultTableHeader->setConstraints(NULL);
    ////Sizes
    //DefaultTableHeader->setMinSize(Vec2f(0,0));
    //DefaultTableHeader->setMaxSize(Vec2f(32767,32767)); //2^15
    //DefaultTableHeader->setPreferredSize(Vec2f(100,100));

    ////Border
    //DefaultTableHeader->setBorder(DefaultTableHeaderBorder);
    //DefaultTableHeader->setRolloverBorder(DefaultTableHeaderBorder);
    //DefaultTableHeader->setFocusedBorder(DefaultTableHeaderBorder);
    //DefaultTableHeader->setDisabledBorder(DefaultTableHeaderBorder);

    ////Background
    //DefaultTableHeader->setBackground(DefaultTableHeaderBackground);
    //DefaultTableHeader->setRolloverBackground(DefaultTableHeaderBackground);
    //DefaultTableHeader->setFocusedBackground(DefaultTableHeaderBackground);
    //DefaultTableHeader->setDisabledBackground(DefaultTableHeaderBackground);

    ////Opacity
    //DefaultTableHeader->setOpacity(1.0);

    ////Table Values
    //DefaultTableHeader->setTable(NULL);
    //DefaultTableHeader->setReorderingAllowed(true);
    //DefaultTableHeader->setResizingAllowed(true);
    //DefaultTableHeader->setDefaultMarginDrawObject(NULL);
    //DefaultTableHeader->setDefaultRenderer(TableCellRendererRefPtr(new DefaultTableHeaderCellRenderer()));
    //DefaultTableHeader->setResizingCursorDriftAllowance(1);


    //TableHeader::getClassType().setPrototype(DefaultTableHeader);


    ///[>************************* Table *****************************
    ////Default RotatedComponentBorder
    //EmptyBorderRefPtr DefaultTableBorder = EmptyBorder::create();

    ////Default RotatedComponentBackground
    //EmptyLayerRefPtr DefaultTableBackground = EmptyLayer::create();

    ////Default RotatedComponent
    //TableRefPtr DefaultTable = Table::create();
    //DefaultTable->setEnabled(true);
    //DefaultTable->setVisible(true);

    //DefaultTable->setConstraints(NULL);
    ////Sizes
    //DefaultTable->setMinSize(Vec2f(0,0));
    //DefaultTable->setMaxSize(Vec2f(32767,32767)); //2^15
    //DefaultTable->setPreferredSize(Vec2f(100,100));

    ////Border
    //DefaultTable->setBorder(DefaultTableBorder);
    //DefaultTable->setRolloverBorder(DefaultTableBorder);
    //DefaultTable->setFocusedBorder(DefaultTableBorder);
    //DefaultTable->setDisabledBorder(DefaultTableBorder);

    ////Background
    //DefaultTable->setBackground(DefaultTableBackground);
    //DefaultTable->setRolloverBackground(DefaultTableBackground);
    //DefaultTable->setFocusedBackground(DefaultTableBackground);
    //DefaultTable->setDisabledBackground(DefaultTableBackground);

    ////Opacity
    //DefaultTable->setOpacity(1.0);

    ////Table Properties
    //DefaultTable->setHeader(DefaultTableHeader);
    //DefaultTable->setAutoCreateColumnsFromModel(true);
    //DefaultTable->setAutoResizeMode(Table::AUTO_RESIZE_SUBSEQUENT_COLUMNS);
    //DefaultTable->setRowHeight(50);
    //DefaultTable->setRowMargin(1);
    //DefaultTable->setRowSelectionAllowed(true);
    //DefaultTable->setShowHorizontalLines(true);
    //DefaultTable->setShowVerticalLines(true);
    //DefaultTable->setGridColor(Color4f(0.0,0.0,0.0,1.0));

    //DefaultTable->setDefaultRenderer(typeid(GLenum), TableCellRendererRefPtr(new DefaultGLenumTableCellRenderer()));
    //DefaultTable->setDefaultRenderer(typeid(std::string), TableCellRendererRefPtr(new DefaultStringTableCellRenderer()));
    //DefaultTable->setDefaultRenderer(typeid(bool), TableCellRendererRefPtr(new DefaultBoolTableCellRenderer()));
    //DefaultTable->setDefaultRenderer(typeid(Int32), TableCellRendererRefPtr(new DefaultInt32TableCellRenderer()));
    //DefaultTable->setDefaultRenderer(typeid(UInt32), TableCellRendererRefPtr(new DefaultUInt32TableCellRenderer()));
    //DefaultTable->setDefaultRenderer(typeid(Real32), TableCellRendererRefPtr(new DefaultReal32TableCellRenderer()));


    //Table::getClassType().setPrototype(DefaultTable);

    //CompoundBackground and Empty Background don't require prototypes.


    pushToPrototypes(DefaultButton);
    pushToPrototypes(DefaultLabel);
    pushToPrototypes(DefaultInternalWindow);
    pushToPrototypes(DefaultPanel);
    pushToPrototypes(DefaultImageComponent);
    pushToPrototypes(DefaultCheckboxButton);
    pushToPrototypes(DefaultRadioButton);
    pushToPrototypes(DefaultToggleButton);
    pushToPrototypes(DefaultTextField);
    pushToPrototypes(DefaultPasswordField);
    pushToPrototypes(DefaultTextArea);
    pushToPrototypes(DefaultToolTip);
    pushToPrototypes(DefaultMenuItem);
    pushToPrototypes(DefaultMenu);
    pushToPrototypes(DefaultPopupMenu);
    pushToPrototypes(DefaultMenuBar);
    pushToPrototypes(DefaultScrollBar);
    pushToPrototypes(DefaultScrollPanel);
    pushToPrototypes(DefaultRotatedComponent);
    pushToPrototypes(DefaultUIViewport);
    pushToPrototypes(DefaultList);
    //pushToPrototypes(DefaultTableHeader);
    //pushToPrototypes(DefaultTable);
    //pushToPrototypes(DefaultSplitPanel);


    initUndefinedPrototypes();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultLookAndFeel::DefaultLookAndFeel(void) :
    Inherited()
{
}

DefaultLookAndFeel::DefaultLookAndFeel(const DefaultLookAndFeel &source) :
    Inherited(source)
{
}

DefaultLookAndFeel::~DefaultLookAndFeel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultLookAndFeel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DefaultLookAndFeel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DefaultLookAndFeel NI" << std::endl;
}

OSG_END_NAMESPACE
