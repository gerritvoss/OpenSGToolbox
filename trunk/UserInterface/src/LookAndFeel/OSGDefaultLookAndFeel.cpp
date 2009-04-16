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

#include <OpenSG/OSGConfig.h>

#include "OSGDefaultLookAndFeel.h"
#include "Text/OSGUIFont.h"
#include "Border/OSGBorders.h"
#include "Layer/OSGLayers.h"
#include "Component/Button/OSGButton.h"
#include "Component/Button/OSGCheckboxButton.h"
#include "Component/Button/OSGRadioButton.h"
#include "Component/Button/OSGToggleButton.h"
#include "Component/Text/OSGLabel.h"
#include "Component/Container/Window/OSGInternalWindow.h"
#include "Component/Container/OSGPanel.h"
#include "Component/Container/OSGSplitPanel.h"
#include "Component/Misc/OSGImageComponent.h"
#include "Graphics/UIDrawObjects/OSGRectUIDrawObject.h"
#include "Graphics/UIDrawObjects/OSGPolygonUIDrawObject.h"
#include "Graphics/UIDrawObjects/OSGArcUIDrawObject.h"
#include "Graphics/UIDrawObjects/OSGDiscUIDrawObject.h"
#include "Graphics/UIDrawObjects/OSGLineUIDrawObject.h"
#include "Component/Misc/OSGUIDrawObjectCanvas.h"
#include "Component/Text/OSGTextField.h"
#include "Component/Text/OSGPasswordField.h"
#include "Component/Text/OSGTextArea.h"
#include "Component/Misc/OSGToolTip.h"

#include "Component/Menu/OSGMenuItem.h"
#include "Component/Menu/OSGMenu.h"
#include "Component/Menu/OSGPopupMenu.h"
#include "Component/Menu/OSGMenuBar.h"

#include "Component/Scroll/OSGScrollBar.h"
#include "Component/Scroll/OSGScrollPanel.h"

#include "Component/Misc/OSGRotatedComponent.h"
#include "Component/Container/OSGUIViewport.h"

#include "Component/Table/OSGTableHeader.h"
#include "Component/Table/OSGTable.h"
#include "Component/Table/ComponentGenerators/OSGDefaultTableCellRenderers.h"

#include "Component/List/OSGList.h"
#include "Component/List/OSGDefaultListSelectionModel.h"


OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultLookAndFeel
UI Default LookAndFeel. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultLookAndFeel::initMethod (void)
{
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
	UIFontPtr DefaultFont = UIFont::create();
	beginEditCP(DefaultFont);
		DefaultFont->setFamily("SANS");
		DefaultFont->setGap(3);
		DefaultFont->setGlyphPixelSize(46);
		DefaultFont->setSize(14);
		DefaultFont->setTextureWidth(0);
		DefaultFont->setStyle(TextFace::STYLE_PLAIN);
	endEditCP(DefaultFont);

	//Default ButtonBorder
	BevelBorderPtr DefaultButtonBorder = BevelBorder::create();
	beginEditCP(DefaultButtonBorder);
		DefaultButtonBorder->setRaised(true);
		DefaultButtonBorder->setWidth(2);
		DefaultButtonBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultButtonBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultButtonBorder->setShadowInner(Color4f(0.65, 0.65, 0.65, 1.0));
		DefaultButtonBorder->setShadowOuter(Color4f(0.45, 0.45, 0.45, 1.0));
	endEditCP(DefaultButtonBorder);

	//Default Disabled ButtonBorder
	BevelBorderPtr DefaultDisabledButtonBorder = BevelBorder::create();
	beginEditCP(DefaultDisabledButtonBorder);
		DefaultDisabledButtonBorder->setRaised(true);
		DefaultDisabledButtonBorder->setWidth(2);
		DefaultDisabledButtonBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultDisabledButtonBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultDisabledButtonBorder->setShadowInner(Color4f(0.85, 0.85, 0.85, 1.0));
		DefaultDisabledButtonBorder->setShadowOuter(Color4f(0.65, 0.65, 0.65, 1.0));
	endEditCP(DefaultDisabledButtonBorder);


	//default active button border
	BevelBorderPtr DefaultActiveButtonBorder = BevelBorder::create();
	beginEditCP(DefaultActiveButtonBorder);
		DefaultActiveButtonBorder->setRaised(false);
		DefaultActiveButtonBorder->setWidth(2);
		DefaultActiveButtonBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultActiveButtonBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultActiveButtonBorder->setShadowInner(Color4f(0.65, 0.65, 0.65, 1.0));
		DefaultActiveButtonBorder->setShadowOuter(Color4f(0.45, 0.45, 0.45, 1.0));
	endEditCP(DefaultActiveButtonBorder);

	//Default ButtonBackground
	ColorLayerPtr DefaultButtonBackground = ColorLayer::create();
	beginEditCP(DefaultButtonBackground);
		DefaultButtonBackground->setColor(Color4f(0.93,0.93,0.93,1.0));
	endEditCP(DefaultButtonBackground);
	
	//Default Disabled ButtonBackground
	ColorLayerPtr DefaultDisabledButtonBackground = ColorLayer::create();
	beginEditCP(DefaultDisabledButtonBackground);
		DefaultDisabledButtonBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
	endEditCP(DefaultDisabledButtonBackground);

	//Default Button
	ButtonPtr DefaultButton = Button::create();
	beginEditCP(DefaultButton);
		DefaultButton->setEnabled(true);
		DefaultButton->setVisible(true);
		
		DefaultButton->setConstraints(NullFC);
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
	endEditCP(DefaultButton);

	Button::getClassType().setPrototype(DefaultButton);

	//************************** Label*****************************
	//Default LabelBorder
	LineBorderPtr DefaultLabelBorder = LineBorder::create();
	beginEditCP(DefaultLabelBorder);
		DefaultLabelBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
		DefaultLabelBorder->setWidth(1);
	endEditCP(DefaultLabelBorder);

	//Default LabelBackground
	ColorLayerPtr DefaultLabelBackground = ColorLayer::create();
	beginEditCP(DefaultLabelBackground);
		DefaultLabelBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
	endEditCP(DefaultLabelBackground);

	//Default Label
	LabelPtr DefaultLabel = Label::create();
	beginEditCP(DefaultLabel);
		DefaultLabel->setEnabled(true);
		DefaultLabel->setVisible(true);
		
		DefaultLabel->setConstraints(NullFC);
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
	endEditCP(DefaultLabel);
	
    Label::getClassType().setPrototype(DefaultLabel);
	
	//************************** InternalWindow *****************************
	//Default InternalWindowBorder
	EmptyBorderPtr DefaultInternalWindowBorder = EmptyBorder::create();
	beginEditCP(DefaultInternalWindowBorder);
		DefaultInternalWindowBorder->setLeftWidth(0);
		DefaultInternalWindowBorder->setRightWidth(0);
		DefaultInternalWindowBorder->setTopWidth(0);
		DefaultInternalWindowBorder->setBottomWidth(0);
	endEditCP(DefaultInternalWindowBorder);

	//Default InternalWindowBackground
	EmptyLayerPtr DefaultInternalWindowBackground = EmptyLayer::create();

	//Default InternalWindow
	InternalWindowPtr DefaultInternalWindow = InternalWindow::create();
	beginEditCP(DefaultInternalWindow);
		DefaultInternalWindow->setEnabled(true);
		DefaultInternalWindow->setVisible(true);
		
		DefaultInternalWindow->setConstraints(NullFC);
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
	endEditCP(DefaultInternalWindow);
	
	InternalWindow::getClassType().setPrototype(DefaultInternalWindow);
	
	//************************** Panel *****************************
	//Default PanelBorder
	/*LineBorderPtr DefaultPanelBorder = LineBorder::create();
	beginEditCP(DefaultPanelBorder);
		DefaultPanelBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
		DefaultPanelBorder->setWidth(1);
	endEditCP(DefaultPanelBorder);*/

	EtchedBorderPtr DefaultPanelBorder = EtchedBorder::create();
	beginEditCP(DefaultPanelBorder);
		DefaultPanelBorder->setWidth(2);
		DefaultPanelBorder->setHighlight(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultPanelBorder->setShadow(Color4f(0.65, 0.65, 0.65, 1.0));
		DefaultPanelBorder->setRaised(true);
	endEditCP(DefaultPanelBorder);

	//Default PanelBackground
	ColorLayerPtr DefaultPanelBackground = ColorLayer::create();
	beginEditCP(DefaultPanelBackground);
		DefaultPanelBackground->setColor(Color4f(0.93,0.93,0.93,1.0));
	endEditCP(DefaultPanelBackground);


	//Default Panel
	PanelPtr DefaultPanel = Panel::create();
	beginEditCP(DefaultPanel);
		DefaultPanel->setEnabled(true);
		DefaultPanel->setVisible(true);
		
		DefaultPanel->setConstraints(NullFC);
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
	endEditCP(DefaultPanel);
	
	Panel::getClassType().setPrototype(DefaultPanel);

	//************************** SplitPanel *****************************
	//The only default value set will be the divider

	//Default Divider Background and Border
	LineBorderPtr DefaultDividerBorder = osg::LineBorder::create();
	beginEditCP(DefaultDividerBorder, LineBorder::WidthFieldMask | LineBorder::ColorFieldMask);
		DefaultDividerBorder->setWidth(1);
		DefaultDividerBorder->setColor(Color4f(0.13, 0.13, 0.13, 1.0));
	endEditCP(DefaultDividerBorder, LineBorder::WidthFieldMask | LineBorder::ColorFieldMask);
	ColorLayerPtr DefaultDividerBackground = ColorLayer::create();
	beginEditCP(DefaultDividerBackground);
		DefaultDividerBackground->setColor(Color4f(0.93,0.93,0.93,1.0));
	endEditCP(DefaultDividerBackground);

	//Default Divider
	UIDrawObjectCanvasPtr DefaultDividerDrawObject = UIDrawObjectCanvas::create();
	beginEditCP(DefaultDividerDrawObject);
		DefaultDividerDrawObject->setBorder(DefaultDividerBorder);
		DefaultDividerDrawObject->setBackground(DefaultDividerBackground);
	endEditCP(DefaultDividerDrawObject);

	//Default SplitPanel
	SplitPanelPtr DefaultSplitPanel = SplitPanel::create();
	beginEditCP(DefaultSplitPanel);

		DefaultSplitPanel->setDividerDrawObject(DefaultDividerDrawObject);
		DefaultSplitPanel->setDividerSize(5);
		DefaultSplitPanel->setDividerPosition(100);
		DefaultSplitPanel->setExpandable(true);
		DefaultSplitPanel->setOrientation(SplitPanel::HORIZONTAL_ORIENTATION);
	endEditCP(DefaultSplitPanel);

	SplitPanel::getClassType().setPrototype(DefaultSplitPanel);
    
	//************************** UIViewport *****************************
	//Default UIViewportBorder
	EmptyBorderPtr DefaultUIViewportBorder = EmptyBorder::create();
	beginEditCP(DefaultUIViewportBorder);
		DefaultUIViewportBorder->setLeftWidth(0);
		DefaultUIViewportBorder->setRightWidth(0);
		DefaultUIViewportBorder->setTopWidth(0);
		DefaultUIViewportBorder->setBottomWidth(0);
	endEditCP(DefaultUIViewportBorder);

	//Default UIViewportBackground
	EmptyLayerPtr DefaultUIViewportBackground = EmptyLayer::create();

	//Default UIViewport
	UIViewportPtr DefaultUIViewport = UIViewport::create();
	beginEditCP(DefaultUIViewport);
		DefaultUIViewport->setEnabled(true);
		DefaultUIViewport->setVisible(true);
		
		DefaultUIViewport->setConstraints(NullFC);
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
	endEditCP(DefaultUIViewport);
	
	UIViewport::getClassType().setPrototype(DefaultUIViewport);
	
	//************************** ImageComponent *****************************
	//Default ImageComponentBorder
	EmptyBorderPtr DefaultImageComponentBorder = EmptyBorder::create();

	//Default ImageComponentBackground
	EmptyLayerPtr DefaultImageComponentBackground = EmptyLayer::create();

	//Default ImageComponent
	ImageComponentPtr DefaultImageComponent = ImageComponent::create();
	beginEditCP(DefaultImageComponent);
		DefaultImageComponent->setEnabled(true);
		DefaultImageComponent->setVisible(true);
		
		DefaultImageComponent->setConstraints(NullFC);
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
	endEditCP(DefaultImageComponent);
	
	ImageComponent::getClassType().setPrototype(DefaultImageComponent);

	
	//************************** Checkbox Button Component *****************************
	UIDrawObjectCanvasPtr defaultCheckboxDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr defaultSelectedCheckboxDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr defaultActiveCheckboxDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr defaultActiveSelectedCheckboxDrawObject = UIDrawObjectCanvas::create();

	RectUIDrawObjectPtr CheckboxBackground = RectUIDrawObject::create();
	beginEditCP(CheckboxBackground);
		CheckboxBackground->setTopLeft(Pnt2f(1,1));
		CheckboxBackground->setBottomRight(Pnt2f(25,25));
		CheckboxBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
		CheckboxBackground->setOpacity(1.0);
	endEditCP(CheckboxBackground);

	RectUIDrawObjectPtr CheckboxBackgroundBorder = RectUIDrawObject::create();
	beginEditCP(CheckboxBackgroundBorder);
		CheckboxBackgroundBorder->setTopLeft(Pnt2f(0,0));
		CheckboxBackgroundBorder->setBottomRight(Pnt2f(26,26));
		CheckboxBackgroundBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
		CheckboxBackgroundBorder->setOpacity(1.0);
	endEditCP(CheckboxBackgroundBorder);

	RectUIDrawObjectPtr CheckboxActiveBorder = RectUIDrawObject::create();
	beginEditCP(CheckboxActiveBorder);
		CheckboxActiveBorder->setTopLeft(Pnt2f(1,1));
		CheckboxActiveBorder->setBottomRight(Pnt2f(25, 25));
		CheckboxActiveBorder->setColor(Color4f(0.0, 1.0, 0.0, 1.0));
		CheckboxActiveBorder->setOpacity(1.0);
	endEditCP(CheckboxActiveBorder);

	LineUIDrawObjectPtr CheckboxLine1 = LineUIDrawObject::create();
	beginEditCP(CheckboxLine1);
		CheckboxLine1->setTopLeft(Pnt2f(1,1));
		CheckboxLine1->setBottomRight(Pnt2f(25,25));
		CheckboxLine1->setColor(Color4f(0.0, 0.0, 0.0, 1.0));
		CheckboxLine1->setOpacity(1.0);
		CheckboxLine1->setWidth(4);
	endEditCP(CheckboxLine1);

	LineUIDrawObjectPtr CheckboxLine2 = LineUIDrawObject::create();
	beginEditCP(CheckboxLine2);
		CheckboxLine2->setTopLeft(Pnt2f(1,25));
		CheckboxLine2->setBottomRight(Pnt2f(25,1));
		CheckboxLine2->setColor(Color4f(0.0, 0.0, 0.0, 1.0));
		CheckboxLine2->setOpacity(1.0);
		CheckboxLine2->setWidth(4);
	endEditCP(CheckboxLine2);

	beginEditCP(defaultCheckboxDrawObject);
	   defaultCheckboxDrawObject->getDrawObjects().push_back(CheckboxBackgroundBorder);
	   defaultCheckboxDrawObject->getDrawObjects().push_back(CheckboxBackground);
	endEditCP(defaultCheckboxDrawObject);

	beginEditCP(defaultSelectedCheckboxDrawObject);
		defaultSelectedCheckboxDrawObject->getDrawObjects().push_back(CheckboxBackgroundBorder);
		defaultSelectedCheckboxDrawObject->getDrawObjects().push_back(CheckboxBackground);
		defaultSelectedCheckboxDrawObject->getDrawObjects().push_back(CheckboxLine1);
		defaultSelectedCheckboxDrawObject->getDrawObjects().push_back(CheckboxLine2);
	endEditCP(defaultSelectedCheckboxDrawObject);

	beginEditCP(defaultActiveSelectedCheckboxDrawObject);
		defaultActiveSelectedCheckboxDrawObject->getDrawObjects().push_back(CheckboxBackgroundBorder);
		defaultActiveSelectedCheckboxDrawObject->getDrawObjects().push_back(CheckboxBackground);
		defaultActiveSelectedCheckboxDrawObject->getDrawObjects().push_back(CheckboxActiveBorder);
		defaultActiveSelectedCheckboxDrawObject->getDrawObjects().push_back(CheckboxLine1);
		defaultActiveSelectedCheckboxDrawObject->getDrawObjects().push_back(CheckboxLine2);
	endEditCP(defaultActiveSelectedCheckboxDrawObject);

	beginEditCP(defaultActiveCheckboxDrawObject);
	 	defaultActiveCheckboxDrawObject->getDrawObjects().push_back(CheckboxBackgroundBorder);
		defaultActiveCheckboxDrawObject->getDrawObjects().push_back(CheckboxBackground);
		defaultActiveCheckboxDrawObject->getDrawObjects().push_back(CheckboxActiveBorder);
	endEditCP(defaultActiveCheckboxDrawObject);

	EmptyBorderPtr DefaultCheckboxButtonBorder = EmptyBorder::create();


	ColorLayerPtr DefaultCheckboxButtonBackground = ColorLayer::create();
	beginEditCP(DefaultCheckboxButtonBackground);
		DefaultCheckboxButtonBackground->setColor(Color4f(0.93,0.93,0.93,1.0));
	endEditCP(DefaultCheckboxButtonBackground);

	CheckboxButtonPtr DefaultCheckboxButton = CheckboxButton::create();
	beginEditCP(DefaultCheckboxButton);
		DefaultCheckboxButton->setEnabled(true);
		DefaultCheckboxButton->setVisible(true);
		
		DefaultCheckboxButton->setConstraints(NullFC);
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
	endEditCP(DefaultCheckboxButton);

	CheckboxButton::getClassType().setPrototype(DefaultCheckboxButton);

	//************************** Radio Button Component *****************************
	UIDrawObjectCanvasPtr defaultRadioDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr defaultSelectedRadioDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr defaultActiveRadioDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr defaultActiveSelectedRadioDrawObject = UIDrawObjectCanvas::create();

	DiscUIDrawObjectPtr RadioBackground = DiscUIDrawObject::create();
    Pnt2f DefaultRadioCenter(10,10);
	beginEditCP(RadioBackground);
		RadioBackground->setWidth(10);
		RadioBackground->setHeight(10);
		RadioBackground->setSubDivisions(10);
		RadioBackground->setStartAngleRad(0);
		RadioBackground->setEndAngleRad(6.28318531);
		RadioBackground->setCenterColor(Color4f(1.0,1.0,1.0,1.0));
		RadioBackground->setOuterColor(Color4f(1.0,1.0,1.0,1.0));
		RadioBackground->setOpacity(1.0);
		RadioBackground->setCenter(DefaultRadioCenter);
	endEditCP(RadioBackground);

	ArcUIDrawObjectPtr RadioBackgroundBorder = ArcUIDrawObject::create();
	beginEditCP(RadioBackgroundBorder);
		RadioBackgroundBorder->setWidth(10);
		RadioBackgroundBorder->setHeight(10);
		RadioBackgroundBorder->setSubDivisions(20);
		RadioBackgroundBorder->setStartAngleRad(0);
		RadioBackgroundBorder->setEndAngleRad(6.28318531);
		RadioBackgroundBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
		RadioBackgroundBorder->setOpacity(1.0);
		RadioBackgroundBorder->setLineWidth(1);
		RadioBackgroundBorder->setCenter(DefaultRadioCenter);
	endEditCP(RadioBackgroundBorder);

	DiscUIDrawObjectPtr RadioSelected = DiscUIDrawObject::create();
	beginEditCP(RadioSelected);
		RadioSelected->setWidth(6);
		RadioSelected->setHeight(6);
		RadioSelected->setSubDivisions(20);
		RadioSelected->setStartAngleRad(0);
		RadioSelected->setEndAngleRad(6.28318531);
		RadioSelected->setCenterColor(Color4f(0.0,0.0,0.0,1.0));
		RadioSelected->setOuterColor(Color4f(0.0,0.0,0.0,1.0));
		RadioSelected->setOpacity(1.0);
		RadioSelected->setCenter(DefaultRadioCenter);
	endEditCP(RadioSelected);

	ArcUIDrawObjectPtr RadioActiveBorder = ArcUIDrawObject::create();
	beginEditCP(RadioActiveBorder);
		RadioActiveBorder->setWidth(9);
		RadioActiveBorder->setHeight(9);
		RadioActiveBorder->setSubDivisions(10);
		RadioActiveBorder->setStartAngleRad(0);
		RadioActiveBorder->setEndAngleRad(6.28318531);
		RadioActiveBorder->setColor(Color4f(0.0,0.0,1.0,1.0));
		RadioActiveBorder->setOpacity(1.0);
		RadioActiveBorder->setCenter(DefaultRadioCenter);
	endEditCP(RadioActiveBorder);

	beginEditCP(defaultRadioDrawObject);
		defaultRadioDrawObject->getDrawObjects().push_back(RadioBackground);
		defaultRadioDrawObject->getDrawObjects().push_back(RadioBackgroundBorder);
	endEditCP(defaultRadioDrawObject);

	beginEditCP(defaultSelectedRadioDrawObject);
		defaultSelectedRadioDrawObject->getDrawObjects().push_back(RadioBackground);
		defaultSelectedRadioDrawObject->getDrawObjects().push_back(RadioBackgroundBorder);
		defaultSelectedRadioDrawObject->getDrawObjects().push_back(RadioSelected);
	endEditCP(defaultSelectedRadioDrawObject);

	beginEditCP(defaultActiveRadioDrawObject);
		defaultActiveRadioDrawObject->getDrawObjects().push_back(RadioBackground);
		defaultActiveRadioDrawObject->getDrawObjects().push_back(RadioBackgroundBorder);
		defaultActiveRadioDrawObject->getDrawObjects().push_back(RadioActiveBorder);
	endEditCP(defaultActiveRadioDrawObject);

	beginEditCP(defaultActiveSelectedRadioDrawObject);
		defaultActiveSelectedRadioDrawObject->getDrawObjects().push_back(RadioBackground);
		defaultActiveSelectedRadioDrawObject->getDrawObjects().push_back(RadioBackgroundBorder);
		defaultActiveSelectedRadioDrawObject->getDrawObjects().push_back(RadioSelected);
		defaultActiveSelectedRadioDrawObject->getDrawObjects().push_back(RadioActiveBorder);
	endEditCP(defaultActiveSelectedRadioDrawObject);
		
	EmptyBorderPtr DefaultRadioButtonBorder = EmptyBorder::create();

	ColorLayerPtr DefaultRadioButtonBackground = ColorLayer::create();
	beginEditCP(DefaultRadioButtonBackground);
		DefaultRadioButtonBackground->setColor(Color4f(0.93,0.93,0.93,1.0));
	endEditCP(DefaultRadioButtonBackground);	

	RadioButtonPtr DefaultRadioButton = RadioButton::create();
	beginEditCP(DefaultRadioButton);
		DefaultRadioButton->setEnabled(true);
		DefaultRadioButton->setVisible(true);
		DefaultRadioButton->setConstraints(NullFC);

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
	endEditCP(DefaultRadioButton);
	
	RadioButton::getClassType().setPrototype(DefaultRadioButton);

	/********Toggle Button********/

	ToggleButtonPtr DefaultToggleButton = ToggleButton::create();
	beginEditCP(DefaultToggleButton);
		DefaultToggleButton->setEnabled(true);
		DefaultToggleButton->setVisible(true);
		
		DefaultToggleButton->setConstraints(NullFC);
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
	endEditCP(DefaultToggleButton);

	ToggleButton::getClassType().setPrototype(DefaultToggleButton);

	/********Text Field********/
	ColorLayerPtr DefaultTextFieldBackground = ColorLayer::create();
	beginEditCP(DefaultTextFieldBackground);
		DefaultTextFieldBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
	endEditCP(DefaultTextFieldBackground);

	ColorLayerPtr DefaultDisabledTextFieldBackground = ColorLayer::create();
	beginEditCP(DefaultDisabledTextFieldBackground);
		DefaultDisabledTextFieldBackground->setColor(Color4f(.8, .8, .8, 1.0));
	endEditCP(DefaultDisabledTextFieldBackground);

	BevelBorderPtr DefaultTextFieldBorder = BevelBorder::create();
	beginEditCP(DefaultTextFieldBorder, BevelBorder::RaisedFieldMask);
		DefaultTextFieldBorder->setRaised(false);
		DefaultTextFieldBorder->setWidth(2);
		DefaultTextFieldBorder->setHighlightInner(Color4f(.9, .9, .9, 1.0));
		DefaultTextFieldBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultTextFieldBorder->setShadowInner(Color4f(0.65, 0.65, 0.65, 1.0));
		DefaultTextFieldBorder->setShadowOuter(Color4f(0.45, 0.45, 0.45, 1.0));
	endEditCP(DefaultTextFieldBorder, BevelBorder::RaisedFieldMask);

	TextFieldPtr DefaultTextField = TextField::create();
	beginEditCP(DefaultTextField);
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
	endEditCP(DefaultTextField);

	TextField::getClassType().setPrototype(DefaultTextField);
    
	/********Password Field********/
	ColorLayerPtr DefaultPasswordFieldBackground = ColorLayer::create();
	beginEditCP(DefaultPasswordFieldBackground);
		DefaultPasswordFieldBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
	endEditCP(DefaultPasswordFieldBackground);

	ColorLayerPtr DefaultDisabledPasswordFieldBackground = ColorLayer::create();
	beginEditCP(DefaultDisabledPasswordFieldBackground);
		DefaultDisabledPasswordFieldBackground->setColor(Color4f(.8, .8, .8, 1.0));
	endEditCP(DefaultDisabledPasswordFieldBackground);

	BevelBorderPtr DefaultPasswordFieldBorder = BevelBorder::create();
	beginEditCP(DefaultPasswordFieldBorder);
		DefaultPasswordFieldBorder->setRaised(false);
		DefaultPasswordFieldBorder->setWidth(2);
		DefaultPasswordFieldBorder->setHighlightInner(Color4f(.9, .9, .9, 1.0));
		DefaultPasswordFieldBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultPasswordFieldBorder->setShadowInner(Color4f(0.65, 0.65, 0.65, 1.0));
		DefaultPasswordFieldBorder->setShadowOuter(Color4f(0.45, 0.45, 0.45, 1.0));
	endEditCP(DefaultPasswordFieldBorder);

	PasswordFieldPtr DefaultPasswordField = PasswordField::create();
	beginEditCP(DefaultPasswordField);
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

	endEditCP(DefaultPasswordField);

	PasswordField::getClassType().setPrototype(DefaultPasswordField);

    /********Text Area********/
	ColorLayerPtr DefaultTextAreaBackground = ColorLayer::create();
	beginEditCP(DefaultTextAreaBackground);
		DefaultTextAreaBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
	endEditCP(DefaultTextAreaBackground);

	ColorLayerPtr DefaultDisabledTextAreaBackground = ColorLayer::create();
	beginEditCP(DefaultDisabledTextAreaBackground);
		DefaultDisabledTextAreaBackground->setColor(Color4f(.8, .8, .8, 1.0));
	endEditCP(DefaultDisabledTextAreaBackground);

	BevelBorderPtr DefaultTextAreaBorder = BevelBorder::create();
	beginEditCP(DefaultTextAreaBorder, BevelBorder::RaisedFieldMask);
		DefaultTextAreaBorder->setRaised(false);
		DefaultTextAreaBorder->setWidth(2);
		DefaultTextAreaBorder->setHighlightInner(Color4f(.9, .9, .9, 1.0));
		DefaultTextAreaBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultTextAreaBorder->setShadowInner(Color4f(0.65, 0.65, 0.65, 1.0));
		DefaultTextAreaBorder->setShadowOuter(Color4f(0.45, 0.45, 0.45, 1.0));
	endEditCP(DefaultTextAreaBorder, BevelBorder::RaisedFieldMask);

	TextAreaPtr DefaultTextArea = TextArea::create();
	beginEditCP(DefaultTextArea);
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

	endEditCP(DefaultTextArea);

	TextArea::getClassType().setPrototype(DefaultTextArea);

	//************************** ToolTip*****************************
	//Default ToolTipBorder
	LineBorderPtr DefaultToolTipLineBorder = LineBorder::create();
	beginEditCP(DefaultToolTipLineBorder);
		DefaultToolTipLineBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
		DefaultToolTipLineBorder->setWidth(1);
	endEditCP(DefaultToolTipLineBorder);
    
	ShadowBorderPtr DefaultToolTipBorder = osg::ShadowBorder::create();
    beginEditCP(DefaultToolTipBorder, ShadowBorder::TopOffsetFieldMask | ShadowBorder::BottomOffsetFieldMask | ShadowBorder::LeftOffsetFieldMask | ShadowBorder::RightOffsetFieldMask | ShadowBorder::InternalColorFieldMask| ShadowBorder::EdgeColorFieldMask | ShadowBorder::InsideBorderFieldMask | ShadowBorder::CornerRadiusFieldMask | ShadowBorder::InternalToEdgeColorLengthFieldMask );
		DefaultToolTipBorder->setTopOffset(0);
		DefaultToolTipBorder->setBottomOffset(2);
		DefaultToolTipBorder->setLeftOffset(0);
		DefaultToolTipBorder->setRightOffset(2);
		DefaultToolTipBorder->setInsideBorder(DefaultToolTipLineBorder);
		DefaultToolTipBorder->setCornerRadius(3);
		DefaultToolTipBorder->setInternalColor(Color4f(0.0, 0.0, 0.0, 0.5));
		DefaultToolTipBorder->setEdgeColor(Color4f(0.0, 0.0, 0.0, 0.0));
		DefaultToolTipBorder->setInternalToEdgeColorLength(2);
	endEditCP(DefaultToolTipBorder, ShadowBorder::TopOffsetFieldMask | ShadowBorder::BottomOffsetFieldMask | ShadowBorder::LeftOffsetFieldMask | ShadowBorder::RightOffsetFieldMask | ShadowBorder::InternalColorFieldMask| ShadowBorder::EdgeColorFieldMask | ShadowBorder::InsideBorderFieldMask | ShadowBorder::CornerRadiusFieldMask | ShadowBorder::InternalToEdgeColorLengthFieldMask );

	//Default ToolTipBackground
	ColorLayerPtr DefaultToolTipBackground = ColorLayer::create();
	beginEditCP(DefaultToolTipBackground);
		DefaultToolTipBackground->setColor(Color4f(1.0,1.0,0.9,1.0));
	endEditCP(DefaultToolTipBackground);

	//Default ToolTip
	ToolTipPtr DefaultToolTip = ToolTip::create();
	beginEditCP(DefaultToolTip);
		DefaultToolTip->setEnabled(true);
		DefaultToolTip->setVisible(true);
		
		DefaultToolTip->setConstraints(NullFC);
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
	endEditCP(DefaultToolTip);
	
    ToolTip::getClassType().setPrototype(DefaultToolTip);
    
	//************************** MenuItem*****************************
	//Default MenuItemBorder
	EmptyBorderPtr DefaultMenuItemBorder = EmptyBorder::create();

	//Default MenuItemBackground
	ColorLayerPtr DefaultMenuItemBackground = ColorLayer::create();
	beginEditCP(DefaultMenuItemBackground);
		DefaultMenuItemBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
	endEditCP(DefaultMenuItemBackground);
	
	//Default MenuItemBorder
	EmptyBorderPtr DefaultMenuItemSelectedBorder = EmptyBorder::create();

	//Default MenuItemBackground
	ColorLayerPtr DefaultMenuItemSelectedBackground = ColorLayer::create();
	beginEditCP(DefaultMenuItemSelectedBackground);
		DefaultMenuItemSelectedBackground->setColor(Color4f(0.3,0.3,1.0,1.0));
	endEditCP(DefaultMenuItemSelectedBackground);

	//Default MenuItem
	MenuItemPtr DefaultMenuItem = MenuItem::create();
	beginEditCP(DefaultMenuItem);
		DefaultMenuItem->setEnabled(true);
		DefaultMenuItem->setVisible(true);
		
		DefaultMenuItem->setConstraints(NullFC);
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
        DefaultMenuItem->setAcceleratorKey(KeyEvent::KEY_NONE);

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
	endEditCP(DefaultMenuItem);
	
    MenuItem::getClassType().setPrototype(DefaultMenuItem);
    
	//************************** Menu*****************************
	//Default MenuBorder
	EmptyBorderPtr DefaultMenuBorder = EmptyBorder::create();

	//Default MenuBackground
	ColorLayerPtr DefaultMenuBackground = ColorLayer::create();
	beginEditCP(DefaultMenuBackground);
		DefaultMenuBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
	endEditCP(DefaultMenuBackground);
	
	//Default MenuBorder
	EmptyBorderPtr DefaultMenuSelectedBorder = EmptyBorder::create();

	//Default MenuBackground
	ColorLayerPtr DefaultMenuSelectedBackground = ColorLayer::create();
	beginEditCP(DefaultMenuSelectedBackground);
		DefaultMenuSelectedBackground->setColor(Color4f(0.3,0.3,1.0,1.0));
	endEditCP(DefaultMenuSelectedBackground);

    
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

	//Default Menu
	MenuPtr DefaultMenu = Menu::create();
	beginEditCP(DefaultMenu);
		DefaultMenu->setEnabled(true);
		DefaultMenu->setVisible(true);
		
		DefaultMenu->setConstraints(NullFC);
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
        DefaultMenu->setAcceleratorKey(KeyEvent::KEY_NONE);

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
	endEditCP(DefaultMenu);
	
    Menu::getClassType().setPrototype(DefaultMenu);
    
	//************************** PopupMenu*****************************
	//Default PopupMenuBorder
	LineBorderPtr DefaultPopupMenuLineBorder = LineBorder::create();
	beginEditCP(DefaultPopupMenuLineBorder);
		DefaultPopupMenuLineBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
		DefaultPopupMenuLineBorder->setWidth(1);
	endEditCP(DefaultPopupMenuLineBorder);

	ShadowBorderPtr DefaultPopupMenuBorder = osg::ShadowBorder::create();
    beginEditCP(DefaultPopupMenuBorder, ShadowBorder::TopOffsetFieldMask | ShadowBorder::BottomOffsetFieldMask | ShadowBorder::LeftOffsetFieldMask | ShadowBorder::RightOffsetFieldMask | ShadowBorder::InternalColorFieldMask| ShadowBorder::EdgeColorFieldMask | ShadowBorder::InsideBorderFieldMask | ShadowBorder::CornerRadiusFieldMask | ShadowBorder::InternalToEdgeColorLengthFieldMask );
		DefaultPopupMenuBorder->setTopOffset(0);
		DefaultPopupMenuBorder->setBottomOffset(2);
		DefaultPopupMenuBorder->setLeftOffset(0);
		DefaultPopupMenuBorder->setRightOffset(2);
		DefaultPopupMenuBorder->setInsideBorder(DefaultPopupMenuLineBorder);
		DefaultPopupMenuBorder->setCornerRadius(3);
		DefaultPopupMenuBorder->setInternalColor(Color4f(0.0, 0.0, 0.0, 0.5));
		DefaultPopupMenuBorder->setEdgeColor(Color4f(0.0, 0.0, 0.0, 0.0));
		DefaultPopupMenuBorder->setInternalToEdgeColorLength(2);
	endEditCP(DefaultPopupMenuBorder, ShadowBorder::TopOffsetFieldMask | ShadowBorder::BottomOffsetFieldMask | ShadowBorder::LeftOffsetFieldMask | ShadowBorder::RightOffsetFieldMask | ShadowBorder::InternalColorFieldMask| ShadowBorder::EdgeColorFieldMask | ShadowBorder::InsideBorderFieldMask | ShadowBorder::CornerRadiusFieldMask | ShadowBorder::InternalToEdgeColorLengthFieldMask );

	//Default PopupMenuBackground
	ColorLayerPtr DefaultPopupMenuBackground = ColorLayer::create();
	beginEditCP(DefaultPopupMenuBackground);
		DefaultPopupMenuBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
	endEditCP(DefaultPopupMenuBackground);

	//Default PopupMenu
	PopupMenuPtr DefaultPopupMenu = PopupMenu::create();
	beginEditCP(DefaultPopupMenu);
		DefaultPopupMenu->setEnabled(true);
		DefaultPopupMenu->setVisible(false);
		
		DefaultPopupMenu->setConstraints(NullFC);
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
	endEditCP(DefaultPopupMenu);
	
    PopupMenu::getClassType().setPrototype(DefaultPopupMenu);
    
	//************************** MenuBar*****************************
	//Default MenuBarBorder
	EmptyBorderPtr DefaultMenuBarBorder = EmptyBorder::create();

	//Default MenuBarBackground
	ColorLayerPtr DefaultMenuBarBackground = ColorLayer::create();
	beginEditCP(DefaultMenuBarBackground);
		DefaultMenuBarBackground->setColor(Color4f(0.93,0.93,0.93,1.0));
	endEditCP(DefaultMenuBarBackground);

	//Default MenuBar
	MenuBarPtr DefaultMenuBar = MenuBar::create();
	beginEditCP(DefaultMenuBar);
		DefaultMenuBar->setEnabled(true);
		DefaultMenuBar->setVisible(true);
		
		DefaultMenuBar->setConstraints(NullFC);
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
	endEditCP(DefaultMenuBar);
	
    MenuBar::getClassType().setPrototype(DefaultMenuBar);
    
	//************************** ScrollBar*****************************
	//Default ScrollBarBorder
	EmptyBorderPtr DefaultScrollBarBorder = EmptyBorder::create();

	//Default ScrollBarBackground
	EmptyLayerPtr DefaultScrollBarBackground = EmptyLayer::create();

    //Vertical Min Draw Object
	PolygonUIDrawObjectPtr DefaultScrollBarVerticalMinButtonDrawObject = PolygonUIDrawObject::create();
	beginEditCP(DefaultScrollBarVerticalMinButtonDrawObject);
		DefaultScrollBarVerticalMinButtonDrawObject->setColor(Color4f(0.0,0.0,0.0,1.0));
		DefaultScrollBarVerticalMinButtonDrawObject->setOpacity(1.0);
        DefaultScrollBarVerticalMinButtonDrawObject->getVerticies().push_back(Pnt2f(0,4));
        DefaultScrollBarVerticalMinButtonDrawObject->getVerticies().push_back(Pnt2f(7,4));
        DefaultScrollBarVerticalMinButtonDrawObject->getVerticies().push_back(Pnt2f(4,0));
	endEditCP(DefaultScrollBarVerticalMinButtonDrawObject);

	UIDrawObjectCanvasPtr DefaultScrollBarVerticalMinButtonCanvas = UIDrawObjectCanvas::create();
	beginEditCP(DefaultScrollBarVerticalMinButtonCanvas);
	   DefaultScrollBarVerticalMinButtonCanvas->getDrawObjects().push_back(DefaultScrollBarVerticalMinButtonDrawObject);
	endEditCP(DefaultScrollBarVerticalMinButtonCanvas);

    //Vertical Min Button
	ButtonPtr DefaultScrollBarVerticalMinButton = Button::create();
    beginEditCP(DefaultScrollBarVerticalMinButton, Button::PreferredSizeFieldMask | Button::EnableActionOnMouseDownTimeFieldMask | Button::ActionOnMouseDownRateFieldMask
        | Button::DrawObjectFieldMask | Button::ActiveDrawObjectFieldMask | Button::FocusedDrawObjectFieldMask | Button::RolloverDrawObjectFieldMask | Button::DisabledDrawObjectFieldMask);
        DefaultScrollBarVerticalMinButton->setPreferredSize(Vec2f(20,20));
        DefaultScrollBarVerticalMinButton->setEnableActionOnMouseDownTime(true);
        DefaultScrollBarVerticalMinButton->setActionOnMouseDownRate(0.1);

        DefaultScrollBarVerticalMinButton->setDrawObject(DefaultScrollBarVerticalMinButtonCanvas);
        DefaultScrollBarVerticalMinButton->setActiveDrawObject(DefaultScrollBarVerticalMinButtonCanvas);
        DefaultScrollBarVerticalMinButton->setFocusedDrawObject(DefaultScrollBarVerticalMinButtonCanvas);
        DefaultScrollBarVerticalMinButton->setRolloverDrawObject(DefaultScrollBarVerticalMinButtonCanvas);
        DefaultScrollBarVerticalMinButton->setDisabledDrawObject(DefaultScrollBarVerticalMinButtonCanvas);
    endEditCP(DefaultScrollBarVerticalMinButton, Button::PreferredSizeFieldMask | Button::EnableActionOnMouseDownTimeFieldMask | Button::ActionOnMouseDownRateFieldMask
        | Button::DrawObjectFieldMask | Button::ActiveDrawObjectFieldMask | Button::FocusedDrawObjectFieldMask | Button::RolloverDrawObjectFieldMask | Button::DisabledDrawObjectFieldMask);

    //Vertical Max Draw Object
	PolygonUIDrawObjectPtr DefaultScrollBarVerticalMaxButtonDrawObject = PolygonUIDrawObject::create();
	beginEditCP(DefaultScrollBarVerticalMaxButtonDrawObject);
		DefaultScrollBarVerticalMaxButtonDrawObject->setColor(Color4f(0.0,0.0,0.0,1.0));
		DefaultScrollBarVerticalMaxButtonDrawObject->setOpacity(1.0);
        DefaultScrollBarVerticalMaxButtonDrawObject->getVerticies().push_back(Pnt2f(0,0));
        DefaultScrollBarVerticalMaxButtonDrawObject->getVerticies().push_back(Pnt2f(7,0));
        DefaultScrollBarVerticalMaxButtonDrawObject->getVerticies().push_back(Pnt2f(4,4));
	endEditCP(DefaultScrollBarVerticalMaxButtonDrawObject);

	UIDrawObjectCanvasPtr DefaultScrollBarVerticalMaxButtonCanvas = UIDrawObjectCanvas::create();
	beginEditCP(DefaultScrollBarVerticalMaxButtonCanvas);
	   DefaultScrollBarVerticalMaxButtonCanvas->getDrawObjects().push_back(DefaultScrollBarVerticalMaxButtonDrawObject);
	endEditCP(DefaultScrollBarVerticalMaxButtonCanvas);
    //Vertical Max Button
	ButtonPtr DefaultScrollBarVerticalMaxButton = Button::create();
    beginEditCP(DefaultScrollBarVerticalMaxButton, Button::PreferredSizeFieldMask | Button::EnableActionOnMouseDownTimeFieldMask | Button::ActionOnMouseDownRateFieldMask
        | Button::DrawObjectFieldMask | Button::ActiveDrawObjectFieldMask | Button::FocusedDrawObjectFieldMask | Button::RolloverDrawObjectFieldMask | Button::DisabledDrawObjectFieldMask);
        DefaultScrollBarVerticalMaxButton->setPreferredSize(Vec2f(20,20));
        DefaultScrollBarVerticalMaxButton->setEnableActionOnMouseDownTime(true);
        DefaultScrollBarVerticalMaxButton->setActionOnMouseDownRate(0.1);
        
        DefaultScrollBarVerticalMaxButton->setDrawObject(DefaultScrollBarVerticalMaxButtonCanvas);
        DefaultScrollBarVerticalMaxButton->setActiveDrawObject(DefaultScrollBarVerticalMaxButtonCanvas);
        DefaultScrollBarVerticalMaxButton->setFocusedDrawObject(DefaultScrollBarVerticalMaxButtonCanvas);
        DefaultScrollBarVerticalMaxButton->setRolloverDrawObject(DefaultScrollBarVerticalMaxButtonCanvas);
        DefaultScrollBarVerticalMaxButton->setDisabledDrawObject(DefaultScrollBarVerticalMaxButtonCanvas);
    endEditCP(DefaultScrollBarVerticalMaxButton, Button::PreferredSizeFieldMask | Button::EnableActionOnMouseDownTimeFieldMask | Button::ActionOnMouseDownRateFieldMask
        | Button::DrawObjectFieldMask | Button::ActiveDrawObjectFieldMask | Button::FocusedDrawObjectFieldMask | Button::RolloverDrawObjectFieldMask | Button::DisabledDrawObjectFieldMask);

    //Horizontal Min Draw Object
	PolygonUIDrawObjectPtr DefaultScrollBarHorizontalMinButtonDrawObject = PolygonUIDrawObject::create();
	beginEditCP(DefaultScrollBarHorizontalMinButtonDrawObject);
		DefaultScrollBarHorizontalMinButtonDrawObject->setColor(Color4f(0.0,0.0,0.0,1.0));
		DefaultScrollBarHorizontalMinButtonDrawObject->setOpacity(1.0);
        DefaultScrollBarHorizontalMinButtonDrawObject->getVerticies().push_back(Pnt2f(4,0));
        DefaultScrollBarHorizontalMinButtonDrawObject->getVerticies().push_back(Pnt2f(4,7));
        DefaultScrollBarHorizontalMinButtonDrawObject->getVerticies().push_back(Pnt2f(0,4));
	endEditCP(DefaultScrollBarHorizontalMinButtonDrawObject);

	UIDrawObjectCanvasPtr DefaultScrollBarHorizontalMinButtonCanvas = UIDrawObjectCanvas::create();
	beginEditCP(DefaultScrollBarHorizontalMinButtonCanvas);
	   DefaultScrollBarHorizontalMinButtonCanvas->getDrawObjects().push_back(DefaultScrollBarHorizontalMinButtonDrawObject);
	endEditCP(DefaultScrollBarHorizontalMinButtonCanvas);

    //Horizontal Min Button
	ButtonPtr DefaultScrollBarHorizontalMinButton = Button::create();
    beginEditCP(DefaultScrollBarHorizontalMinButton, Button::PreferredSizeFieldMask | Button::EnableActionOnMouseDownTimeFieldMask | Button::ActionOnMouseDownRateFieldMask
        | Button::DrawObjectFieldMask | Button::ActiveDrawObjectFieldMask | Button::FocusedDrawObjectFieldMask | Button::RolloverDrawObjectFieldMask | Button::DisabledDrawObjectFieldMask);
        DefaultScrollBarHorizontalMinButton->setPreferredSize(Vec2f(20,20));
        DefaultScrollBarHorizontalMinButton->setEnableActionOnMouseDownTime(true);
        DefaultScrollBarHorizontalMinButton->setActionOnMouseDownRate(0.1);

        DefaultScrollBarHorizontalMinButton->setDrawObject(DefaultScrollBarHorizontalMinButtonCanvas);
        DefaultScrollBarHorizontalMinButton->setActiveDrawObject(DefaultScrollBarHorizontalMinButtonCanvas);
        DefaultScrollBarHorizontalMinButton->setFocusedDrawObject(DefaultScrollBarHorizontalMinButtonCanvas);
        DefaultScrollBarHorizontalMinButton->setRolloverDrawObject(DefaultScrollBarHorizontalMinButtonCanvas);
        DefaultScrollBarHorizontalMinButton->setDisabledDrawObject(DefaultScrollBarHorizontalMinButtonCanvas);
    endEditCP(DefaultScrollBarHorizontalMinButton, Button::PreferredSizeFieldMask | Button::EnableActionOnMouseDownTimeFieldMask | Button::ActionOnMouseDownRateFieldMask
        | Button::DrawObjectFieldMask | Button::ActiveDrawObjectFieldMask | Button::FocusedDrawObjectFieldMask | Button::RolloverDrawObjectFieldMask | Button::DisabledDrawObjectFieldMask);

    //Horizontal Max Draw Object
	PolygonUIDrawObjectPtr DefaultScrollBarHorizontalMaxButtonDrawObject = PolygonUIDrawObject::create();
	beginEditCP(DefaultScrollBarHorizontalMaxButtonDrawObject);
		DefaultScrollBarHorizontalMaxButtonDrawObject->setColor(Color4f(0.0,0.0,0.0,1.0));
		DefaultScrollBarHorizontalMaxButtonDrawObject->setOpacity(1.0);
        DefaultScrollBarHorizontalMaxButtonDrawObject->getVerticies().push_back(Pnt2f(0,0));
        DefaultScrollBarHorizontalMaxButtonDrawObject->getVerticies().push_back(Pnt2f(0,7));
        DefaultScrollBarHorizontalMaxButtonDrawObject->getVerticies().push_back(Pnt2f(4,4));
	endEditCP(DefaultScrollBarHorizontalMaxButtonDrawObject);

	UIDrawObjectCanvasPtr DefaultScrollBarHorizontalMaxButtonCanvas = UIDrawObjectCanvas::create();
	beginEditCP(DefaultScrollBarHorizontalMaxButtonCanvas);
	   DefaultScrollBarHorizontalMaxButtonCanvas->getDrawObjects().push_back(DefaultScrollBarHorizontalMaxButtonDrawObject);
	endEditCP(DefaultScrollBarHorizontalMaxButtonCanvas);
    //Horizontal Max Button
	ButtonPtr DefaultScrollBarHorizontalMaxButton = Button::create();
    beginEditCP(DefaultScrollBarHorizontalMaxButton, Button::PreferredSizeFieldMask | Button::EnableActionOnMouseDownTimeFieldMask | Button::ActionOnMouseDownRateFieldMask
        | Button::DrawObjectFieldMask | Button::ActiveDrawObjectFieldMask | Button::FocusedDrawObjectFieldMask | Button::RolloverDrawObjectFieldMask | Button::DisabledDrawObjectFieldMask);
        DefaultScrollBarHorizontalMaxButton->setPreferredSize(Vec2f(20,20));
        DefaultScrollBarHorizontalMaxButton->setEnableActionOnMouseDownTime(true);
        DefaultScrollBarHorizontalMaxButton->setActionOnMouseDownRate(0.1);
        
        DefaultScrollBarHorizontalMaxButton->setDrawObject(DefaultScrollBarHorizontalMaxButtonCanvas);
        DefaultScrollBarHorizontalMaxButton->setActiveDrawObject(DefaultScrollBarHorizontalMaxButtonCanvas);
        DefaultScrollBarHorizontalMaxButton->setFocusedDrawObject(DefaultScrollBarHorizontalMaxButtonCanvas);
        DefaultScrollBarHorizontalMaxButton->setRolloverDrawObject(DefaultScrollBarHorizontalMaxButtonCanvas);
        DefaultScrollBarHorizontalMaxButton->setDisabledDrawObject(DefaultScrollBarHorizontalMaxButtonCanvas);
    endEditCP(DefaultScrollBarHorizontalMaxButton, Button::PreferredSizeFieldMask | Button::EnableActionOnMouseDownTimeFieldMask | Button::ActionOnMouseDownRateFieldMask
        | Button::DrawObjectFieldMask | Button::ActiveDrawObjectFieldMask | Button::FocusedDrawObjectFieldMask | Button::RolloverDrawObjectFieldMask | Button::DisabledDrawObjectFieldMask);

    //Scroll Field
	//Scroll Field Border
	BevelBorderPtr DefaultScrollFieldBorder = BevelBorder::create();
	beginEditCP(DefaultScrollFieldBorder);
		DefaultScrollFieldBorder->setRaised(true);
		DefaultScrollFieldBorder->setWidth(1);
		DefaultScrollFieldBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultScrollFieldBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultScrollFieldBorder->setShadowInner(Color4f(0.65, 0.65, 0.65, 1.0));
		DefaultScrollFieldBorder->setShadowOuter(Color4f(0.45, 0.45, 0.45, 1.0));
	endEditCP(DefaultScrollFieldBorder);

	//Scroll Field Disabled Border
	BevelBorderPtr DefaultDisabledScrollFieldBorder = BevelBorder::create();
	beginEditCP(DefaultDisabledScrollFieldBorder);
		DefaultDisabledScrollFieldBorder->setRaised(true);
		DefaultDisabledScrollFieldBorder->setWidth(1);
		DefaultDisabledScrollFieldBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultDisabledScrollFieldBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultDisabledScrollFieldBorder->setShadowInner(Color4f(0.85, 0.85, 0.85, 1.0));
		DefaultDisabledScrollFieldBorder->setShadowOuter(Color4f(0.65, 0.65, 0.65, 1.0));
	endEditCP(DefaultDisabledButtonBorder);

	//Scroll Field Background
	ColorLayerPtr DefaultScrollFieldBackground = ColorLayer::create();
	beginEditCP(DefaultScrollFieldBackground);
		DefaultScrollFieldBackground->setColor(Color4f(0.93,0.93,0.93,1.0));
	endEditCP(DefaultScrollFieldBackground);
	
	//Scroll Field Disabled Background
	ColorLayerPtr DefaultDisabledScrollFieldBackground = ColorLayer::create();
	beginEditCP(DefaultDisabledScrollFieldBackground);
		DefaultDisabledScrollFieldBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
	endEditCP(DefaultDisabledScrollFieldBackground);

	ButtonPtr DefaultScrollFieldButton = Button::create();
    beginEditCP(DefaultScrollFieldButton, Button::PreferredSizeFieldMask | Button::EnableActionOnMouseDownTimeFieldMask | Button::ActionOnMouseDownRateFieldMask);
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
    endEditCP(DefaultScrollFieldButton, Button::PreferredSizeFieldMask | Button::EnableActionOnMouseDownTimeFieldMask | Button::ActionOnMouseDownRateFieldMask);

    //Scroll Bar
	//Scroll Bar Border
	BevelBorderPtr DefaultScrollBarDrawObjectBorder = BevelBorder::create();
	beginEditCP(DefaultScrollBarDrawObjectBorder);
		DefaultScrollBarDrawObjectBorder->setRaised(true);
		DefaultScrollBarDrawObjectBorder->setWidth(2);
		DefaultScrollBarDrawObjectBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultScrollBarDrawObjectBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultScrollBarDrawObjectBorder->setShadowInner(Color4f(0.65, 0.65, 0.65, 1.0));
		DefaultScrollBarDrawObjectBorder->setShadowOuter(Color4f(0.45, 0.45, 0.45, 1.0));
	endEditCP(DefaultScrollBarDrawObjectBorder);

	//Scroll Bar Disabled Border
	BevelBorderPtr DefaultDisabledScrollBarDrawObjectBorder = BevelBorder::create();
	beginEditCP(DefaultDisabledScrollBarDrawObjectBorder);
		DefaultDisabledScrollBarDrawObjectBorder->setRaised(true);
		DefaultDisabledScrollBarDrawObjectBorder->setWidth(2);
		DefaultDisabledScrollBarDrawObjectBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultDisabledScrollBarDrawObjectBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultDisabledScrollBarDrawObjectBorder->setShadowInner(Color4f(0.85, 0.85, 0.85, 1.0));
		DefaultDisabledScrollBarDrawObjectBorder->setShadowOuter(Color4f(0.65, 0.65, 0.65, 1.0));
	endEditCP(DefaultDisabledButtonBorder);


	//Scroll Bar Rollover border
	BevelBorderPtr DefaultRolloverScrollBarDrawObjectBorder = BevelBorder::create();
	beginEditCP(DefaultRolloverScrollBarDrawObjectBorder);
		DefaultRolloverScrollBarDrawObjectBorder->setRaised(true);
		DefaultRolloverScrollBarDrawObjectBorder->setWidth(2);
		DefaultRolloverScrollBarDrawObjectBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultRolloverScrollBarDrawObjectBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultRolloverScrollBarDrawObjectBorder->setShadowInner(Color4f(0.65, 0.65, 0.65, 1.0));
		DefaultRolloverScrollBarDrawObjectBorder->setShadowOuter(Color4f(0.45, 0.45, 0.45, 1.0));
	endEditCP(DefaultRolloverScrollBarDrawObjectBorder);
    
	//Scroll Bar Rollover border
	BevelBorderPtr DefaultActiveScrollBarDrawObjectBorder = BevelBorder::create();
	beginEditCP(DefaultActiveScrollBarDrawObjectBorder);
		DefaultActiveScrollBarDrawObjectBorder->setRaised(false);
		DefaultActiveScrollBarDrawObjectBorder->setWidth(2);
		DefaultActiveScrollBarDrawObjectBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultActiveScrollBarDrawObjectBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultActiveScrollBarDrawObjectBorder->setShadowInner(Color4f(0.65, 0.65, 0.65, 1.0));
		DefaultActiveScrollBarDrawObjectBorder->setShadowOuter(Color4f(0.45, 0.45, 0.45, 1.0));
	endEditCP(DefaultRolloverScrollBarDrawObjectBorder);

	//Scroll Bar Background
	ColorLayerPtr DefaultScrollBarDrawObjectBackground = ColorLayer::create();
	beginEditCP(DefaultScrollBarDrawObjectBackground);
		DefaultScrollBarDrawObjectBackground->setColor(Color4f(0.93,0.93,0.93,1.0));
	endEditCP(DefaultScrollBarDrawObjectBackground);
	
	//Scroll Bar Disabled Background
	ColorLayerPtr DefaultDisabledScrollBarDrawObjectBackground = ColorLayer::create();
	beginEditCP(DefaultDisabledScrollBarDrawObjectBackground);
		DefaultDisabledScrollBarDrawObjectBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
	endEditCP(DefaultDisabledScrollBarDrawObjectBackground);

	//Scroll Bar Rollover Background
	ColorLayerPtr DefaultRolloverScrollBarDrawObjectBackground = ColorLayer::create();
	beginEditCP(DefaultRolloverScrollBarDrawObjectBackground);
		DefaultRolloverScrollBarDrawObjectBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
	endEditCP(DefaultRolloverScrollBarDrawObjectBackground);

	ButtonPtr DefaultScrollBarDrawObject = Button::create();
	beginEditCP(DefaultScrollBarDrawObject);
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
	endEditCP(DefaultScrollBarDrawObject);

	//Default ScrollBar
	ScrollBarPtr DefaultScrollBar = ScrollBar::create();
	beginEditCP(DefaultScrollBar);
		DefaultScrollBar->setEnabled(true);
		DefaultScrollBar->setVisible(true);
		
		DefaultScrollBar->setConstraints(NullFC);
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
	endEditCP(DefaultScrollBar);
	
    ScrollBar::getClassType().setPrototype(DefaultScrollBar);

	//************************** ScrollPanel*****************************
	//Default ScrollPanelBorder
	EmptyBorderPtr DefaultScrollPanelBorder = EmptyBorder::create();

	//Default ScrollPanelBackground
	EmptyLayerPtr DefaultScrollPanelBackground = EmptyLayer::create();

	//Default ScrollPanel
	ScrollPanelPtr DefaultScrollPanel = ScrollPanel::create();
	beginEditCP(DefaultScrollPanel);
		DefaultScrollPanel->setEnabled(true);
		DefaultScrollPanel->setVisible(true);
		
		DefaultScrollPanel->setConstraints(NullFC);
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
	endEditCP(DefaultScrollPanel);
	
    ScrollPanel::getClassType().setPrototype(DefaultScrollPanel);

	//************************** RotatedComponent*****************************
	//Default RotatedComponentBorder
	EmptyBorderPtr DefaultRotatedComponentBorder = EmptyBorder::create();

	//Default RotatedComponentBackground
	EmptyLayerPtr DefaultRotatedComponentBackground = EmptyLayer::create();

	//Default RotatedComponent
	RotatedComponentPtr DefaultRotatedComponent = RotatedComponent::create();
	beginEditCP(DefaultRotatedComponent);
		DefaultRotatedComponent->setEnabled(true);
		DefaultRotatedComponent->setVisible(true);
		
		DefaultRotatedComponent->setConstraints(NullFC);
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

		DefaultRotatedComponent->setInternalComponent(NullFC);

        DefaultRotatedComponent->setResizePolicy(RotatedComponent::RESIZE_TO_MIN);
	endEditCP(DefaultRotatedComponent);
	
    RotatedComponent::getClassType().setPrototype(DefaultRotatedComponent);
	/*******Borders********/
	/*******Line Border********/

	LineBorderPtr DefaultLineBorder = LineBorder::create();
	beginEditCP(DefaultLineBorder);
		DefaultLineBorder->setWidth(1);
		DefaultLineBorder->setColor(Color4f(0.0, 0.0, 0.0, 1.0));
	endEditCP(DefaultLineBorder);

	LineBorder::getClassType().setPrototype(DefaultLineBorder);

	/********Etched Border********/

	EtchedBorderPtr DefaultEtchedBorder = EtchedBorder::create();
	beginEditCP(DefaultEtchedBorder);
		DefaultEtchedBorder->setWidth(2);
		DefaultEtchedBorder->setRaised(true);
		DefaultEtchedBorder->setHighlight(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultEtchedBorder->setShadow(Color4f(0.65, 0.65, 0.65, 1.0));
	endEditCP(DefaultEtchedBorder);

	EtchedBorder::getClassType().setPrototype(DefaultEtchedBorder);
	
	/********Empty Border*********/
	EmptyBorderPtr DefaultEmptyBorder = EmptyBorder::create();
	beginEditCP(DefaultEmptyBorder);
		DefaultEmptyBorder->setTopWidth(0);
		DefaultEmptyBorder->setBottomWidth(0);
		DefaultEmptyBorder->setRightWidth(0);
		DefaultEmptyBorder->setLeftWidth(0);
	endEditCP(DefaultEmptyBorder);

	EmptyBorder::getClassType().setPrototype(DefaultEmptyBorder);


	/********Bevel Border**********/

	BevelBorderPtr DefaultBevelBorder = BevelBorder::create();
	beginEditCP(DefaultBevelBorder);
		DefaultBevelBorder->setRaised(true);
		DefaultBevelBorder->setWidth(2);
		DefaultBevelBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultBevelBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultBevelBorder->setShadowInner(Color4f(0.65, 0.65, 0.65, 1.0));
		DefaultBevelBorder->setShadowOuter(Color4f(0.45, 0.45, 0.45, 1.0));
	endEditCP(DefaultBevelBorder);

	BevelBorder::getClassType().setPrototype(DefaultBevelBorder);

	/********Matte Border**********/

	MatteBorderPtr DefaultMatteBorder = MatteBorder::create();
	beginEditCP(DefaultMatteBorder);
		DefaultMatteBorder->setRightWidth(1);
		DefaultMatteBorder->setLeftWidth(1);
		DefaultMatteBorder->setTopWidth(1);
		DefaultMatteBorder->setBottomWidth(1);
		DefaultMatteBorder->setColor(Color4f(0.0, 0.0, 0.0, 1.0));
	endEditCP(DefaultMatteBorder);

	MatteBorder::getClassType().setPrototype(DefaultMatteBorder);

	/********Compound Border********/
	CompoundBorderPtr DefaultCompoundBorder = CompoundBorder::create();
	beginEditCP(DefaultCompoundBorder);
		DefaultCompoundBorder->setInnerBorder(NullFC);
		DefaultCompoundBorder->setOuterBorder(NullFC);
	endEditCP(DefaultCompoundBorder);

	CompoundBorder::getClassType().setPrototype(DefaultCompoundBorder);

	/********Rounded Corner Line Border********/
	RoundedCornerLineBorderPtr DefaultRoundedCornerLineBorder = RoundedCornerLineBorder::create();
	beginEditCP(DefaultRoundedCornerLineBorder);
		DefaultRoundedCornerLineBorder->setCornerRadius(8);
		DefaultRoundedCornerLineBorder->setWidth(2);
		DefaultRoundedCornerLineBorder->setColor(Color4f(0.0, 0.0, 0.0, 1.0));
	endEditCP(DefaultRoundedCornerLineBorder);

	RoundedCornerLineBorder::getClassType().setPrototype(DefaultRoundedCornerLineBorder);

	/*********Backgounds***********/
	/*********Color Background**********/
	ColorLayerPtr DefaultColorBackground = ColorLayer::create();
	beginEditCP(DefaultColorBackground);
		DefaultColorBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
	endEditCP(DefaultColorBackground);

	ColorLayer::getClassType().setPrototype(DefaultColorBackground);
	
	/**********Gradient Background***********/
	GradientLayerPtr DefaultGradientBackground = GradientLayer::create();
	beginEditCP(DefaultGradientBackground);
		DefaultGradientBackground->getColors().push_back(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultGradientBackground->getStops().push_back(0.0);
		DefaultGradientBackground->getColors().push_back(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultGradientBackground->getStops().push_back(1.0);
        DefaultGradientBackground->setStartPosition(Vec2f(0.0f,0.0f));
        DefaultGradientBackground->setEndPosition(Vec2f(1.0f,0.0f));
	endEditCP(DefaultGradientBackground);

	GradientLayer::getClassType().setPrototype(DefaultGradientBackground);

	/**********Material Background***********/
	MaterialLayerPtr DefaultMaterialBackground = MaterialLayer::create();
	beginEditCP(DefaultMaterialBackground);
		DefaultMaterialBackground->setMaterial(NullFC);
	endEditCP(DefaultMaterialBackground);

	MaterialLayer::getClassType().setPrototype(DefaultMaterialBackground);

	/*********Texture Background********/
	TextureLayerPtr DefaultTextureBackground = TextureLayer::create();
	beginEditCP(DefaultTextureBackground);
		DefaultTextureBackground->setTexture(NullFC);
	endEditCP(DefaultTextureBackground);

	TextureLayer::getClassType().setPrototype(DefaultTextureBackground);

	
	//************************** List *****************************
	//Default RotatedComponentBorder
	EmptyBorderPtr DefaultListBorder = EmptyBorder::create();

	//Default RotatedComponentBackground
	EmptyLayerPtr DefaultListBackground = EmptyLayer::create();

	//Default RotatedComponent
	ListPtr DefaultList = List::create();
	beginEditCP(DefaultList);
		DefaultList->setEnabled(true);
		DefaultList->setVisible(true);
		
		DefaultList->setConstraints(NullFC);
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
	endEditCP(DefaultList);
	
    List::getClassType().setPrototype(DefaultList);
    
	
	//************************** TableHeader *****************************
	//Default RotatedComponentBorder
	EmptyBorderPtr DefaultTableHeaderBorder = EmptyBorder::create();

	//Default RotatedComponentBackground
	EmptyLayerPtr DefaultTableHeaderBackground = EmptyLayer::create();
    
	//Default RotatedComponent
	TableHeaderPtr DefaultTableHeader = TableHeader::create();
	beginEditCP(DefaultTableHeader);
		DefaultTableHeader->setEnabled(true);
		DefaultTableHeader->setVisible(true);
		
		DefaultTableHeader->setConstraints(NullFC);
		//Sizes
		DefaultTableHeader->setMinSize(Vec2f(0,0));
		DefaultTableHeader->setMaxSize(Vec2f(32767,32767)); //2^15
		DefaultTableHeader->setPreferredSize(Vec2f(100,100));

		//Border
		DefaultTableHeader->setBorder(DefaultTableHeaderBorder);
		DefaultTableHeader->setRolloverBorder(DefaultTableHeaderBorder);
		DefaultTableHeader->setFocusedBorder(DefaultTableHeaderBorder);
		DefaultTableHeader->setDisabledBorder(DefaultTableHeaderBorder);
		
		//Background
		DefaultTableHeader->setBackground(DefaultTableHeaderBackground);
		DefaultTableHeader->setRolloverBackground(DefaultTableHeaderBackground);
		DefaultTableHeader->setFocusedBackground(DefaultTableHeaderBackground);
		DefaultTableHeader->setDisabledBackground(DefaultTableHeaderBackground);
		
		//Opacity
		DefaultTableHeader->setOpacity(1.0);

        //Table Values
		DefaultTableHeader->setTable(NullFC);
		DefaultTableHeader->setReorderingAllowed(true);
		DefaultTableHeader->setResizingAllowed(true);
		DefaultTableHeader->setDefaultMarginDrawObject(NullFC);
        DefaultTableHeader->setDefaultRenderer(TableCellRendererPtr(new DefaultTableHeaderCellRenderer()));
        DefaultTableHeader->setResizingCursorDriftAllowance(1);
		
	endEditCP(DefaultTableHeader);
	
    TableHeader::getClassType().setPrototype(DefaultTableHeader);
    
	
	//************************** Table *****************************
	//Default RotatedComponentBorder
	EmptyBorderPtr DefaultTableBorder = EmptyBorder::create();

	//Default RotatedComponentBackground
	EmptyLayerPtr DefaultTableBackground = EmptyLayer::create();

	//Default RotatedComponent
	TablePtr DefaultTable = Table::create();
	beginEditCP(DefaultTable);
		DefaultTable->setEnabled(true);
		DefaultTable->setVisible(true);
		
		DefaultTable->setConstraints(NullFC);
		//Sizes
		DefaultTable->setMinSize(Vec2f(0,0));
		DefaultTable->setMaxSize(Vec2f(32767,32767)); //2^15
		DefaultTable->setPreferredSize(Vec2f(100,100));

		//Border
		DefaultTable->setBorder(DefaultTableBorder);
		DefaultTable->setRolloverBorder(DefaultTableBorder);
		DefaultTable->setFocusedBorder(DefaultTableBorder);
		DefaultTable->setDisabledBorder(DefaultTableBorder);
		
		//Background
		DefaultTable->setBackground(DefaultTableBackground);
		DefaultTable->setRolloverBackground(DefaultTableBackground);
		DefaultTable->setFocusedBackground(DefaultTableBackground);
		DefaultTable->setDisabledBackground(DefaultTableBackground);
		
		//Opacity
		DefaultTable->setOpacity(1.0);

        //Table Properties
        DefaultTable->setHeader(DefaultTableHeader);
        DefaultTable->setAutoCreateColumnsFromModel(true);
        DefaultTable->setAutoResizeMode(Table::AUTO_RESIZE_SUBSEQUENT_COLUMNS);
        DefaultTable->setRowHeight(50);
        DefaultTable->setRowMargin(1);
        DefaultTable->setRowSelectionAllowed(true);
        DefaultTable->setShowHorizontalLines(true);
        DefaultTable->setShowVerticalLines(true);
        DefaultTable->setGridColor(Color4f(0.0,0.0,0.0,1.0));

        DefaultTable->setDefaultRenderer(typeid(GLenum), TableCellRendererPtr(new DefaultGLenumTableCellRenderer()));
        DefaultTable->setDefaultRenderer(typeid(std::string), TableCellRendererPtr(new DefaultStringTableCellRenderer()));
        DefaultTable->setDefaultRenderer(typeid(bool), TableCellRendererPtr(new DefaultBoolTableCellRenderer()));
        DefaultTable->setDefaultRenderer(typeid(Int32), TableCellRendererPtr(new DefaultInt32TableCellRenderer()));
        DefaultTable->setDefaultRenderer(typeid(UInt32), TableCellRendererPtr(new DefaultUInt32TableCellRenderer()));
        DefaultTable->setDefaultRenderer(typeid(Real32), TableCellRendererPtr(new DefaultReal32TableCellRenderer()));
		
	endEditCP(DefaultTable);
	
    Table::getClassType().setPrototype(DefaultTable);

	//CompoundBackground and Empty Background don't require prototypes.


	beginEditCP(DefaultLookAndFeelPtr(this), DefaultLookAndFeel::PrototypesFieldMask);
		getPrototypes().push_back(DefaultButton);
		getPrototypes().push_back(DefaultLabel);
		getPrototypes().push_back(DefaultInternalWindow);
		getPrototypes().push_back(DefaultPanel);
		getPrototypes().push_back(DefaultSplitPanel);
		getPrototypes().push_back(DefaultImageComponent);
		getPrototypes().push_back(DefaultCheckboxButton);
		getPrototypes().push_back(DefaultRadioButton);
		getPrototypes().push_back(DefaultToggleButton);
		getPrototypes().push_back(DefaultTextField);
		getPrototypes().push_back(DefaultPasswordField);
		getPrototypes().push_back(DefaultTextArea);
		getPrototypes().push_back(DefaultToolTip);
		getPrototypes().push_back(DefaultMenuItem);
		getPrototypes().push_back(DefaultMenu);
		getPrototypes().push_back(DefaultPopupMenu);
		getPrototypes().push_back(DefaultMenuBar);
		getPrototypes().push_back(DefaultScrollBar);
		getPrototypes().push_back(DefaultScrollPanel);
		getPrototypes().push_back(DefaultRotatedComponent);
		getPrototypes().push_back(DefaultUIViewport);
		getPrototypes().push_back(DefaultList);
		getPrototypes().push_back(DefaultTableHeader);
		getPrototypes().push_back(DefaultTable);
	endEditCP(DefaultLookAndFeelPtr(this), DefaultLookAndFeel::PrototypesFieldMask);
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

void DefaultLookAndFeel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DefaultLookAndFeel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DefaultLookAndFeel NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDEFAULTLOOKANDFEELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDEFAULTLOOKANDFEELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDEFAULTLOOKANDFEELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE
