/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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
#include "Text/OSGFont.h"
#include "Border/OSGLineBorder.h"
#include "Border/OSGEmptyBorder.h"
#include "Border/OSGEtchedBorder.h"
#include "Border/OSGBevelBorder.h"
#include "Border/OSGMatteBorder.h"
#include "Border/OSGCompoundBorder.h"
#include "Background/OSGColorUIBackground.h"
#include "Background/OSGEmptyUIBackground.h"
#include "Background/OSGCompoundUIBackground.h"
#include "Background/OSGGradientUIBackground.h"
#include "Background/OSGMaterialUIBackground.h"
#include "Background/OSGTextureUIBackground.h"
#include "Component/OSGButton.h"
#include "Component/OSGLabel.h"
#include "Component/OSGFrame.h"
#include "Component/OSGPanel.h"
#include "Component/OSGImageComponent.h"
#include "Util/OSGUIDefines.h"
#include "Component/OSGCheckboxButton.h"
#include "Component/OSGRadioButton.h"
#include "Component/OSGToggleButton.h"
#include "Graphics/UIDrawObjects/OSGRectUIDrawObject.h"
#include "Graphics/UIDrawObjects/OSGArcUIDrawObject.h"
#include "Graphics/UIDrawObjects/OSGDiscUIDrawObject.h"
#include "Graphics/UIDrawObjects/OSGLineUIDrawObject.h"
#include "Component/OSGUIDrawObjectCanvas.h"
#include "Component/Text/OSGTextField.h"

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
	//Default Font
	FontPtr DefaultFont = Font::create();
	beginEditCP(DefaultFont);
		DefaultFont->setFamily("SANS");
		DefaultFont->setGap(1);
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
		DefaultButtonBorder->setShadowInner(Color4f(0.85, 0.85, 0.85, 1.0));
		DefaultButtonBorder->setShadowOuter(Color4f(0.65, 0.65, 0.65, 1.0));
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
	ColorUIBackgroundPtr DefaultButtonBackground = ColorUIBackground::create();
	beginEditCP(DefaultButtonBackground);
		DefaultButtonBackground->setColor(Color4f(0.93,0.93,0.93,1.0));
	endEditCP(DefaultButtonBackground);
	
	//Default Disabled ButtonBackground
	ColorUIBackgroundPtr DefaultDisabledButtonBackground = ColorUIBackground::create();
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
		DefaultButton->setMinSize(Vec2s(0,0));
		DefaultButton->setMaxSize(Vec2s(32767,32767)); //2^15
		DefaultButton->setPreferredSize(Vec2s(100,50));

		//Border
		DefaultButton->setBorder(DefaultButtonBorder);
		DefaultButton->setDisabledBorder(DefaultDisabledButtonBorder);
		DefaultButton->setActiveBorder(DefaultActiveButtonBorder);
		
		//Background
		DefaultButton->setBackground(DefaultButtonBackground);
		DefaultButton->setDisabledBackground(DefaultDisabledButtonBackground);
		DefaultButton->setActiveBackground(DefaultButtonBackground);

		//Foreground
		DefaultButton->setForegroundColor(Color4f(0.0,0.0,0.0,1.0));
		DefaultButton->setDisabledForegroundColor(Color4f(0.4,0.4,0.4,1.0));
		
		//Opacity
		DefaultButton->setOpacity(1.0);

		//Text
		DefaultButton->setText("");
		DefaultButton->setFont(DefaultFont);
		DefaultButton->setVerticalAlignment(VERTICAL_CENTER);
		DefaultButton->setHorizontalAlignment(HORIZONTAL_CENTER);
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
	ColorUIBackgroundPtr DefaultLabelBackground = ColorUIBackground::create();
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
		DefaultLabel->setMinSize(Vec2s(0,0));
		DefaultLabel->setMaxSize(Vec2s(32767,32767)); //2^15
		DefaultLabel->setPreferredSize(Vec2s(100,50));

		//Border
		DefaultLabel->setBorder(DefaultLabelBorder);
		
		//Background
		DefaultLabel->setBackground(DefaultLabelBackground);

		//Foreground
		DefaultLabel->setForegroundColor(Color4f(0.0,0.0,0.0,1.0));
		
		//Opacity
		DefaultLabel->setOpacity(1.0);

		//Text
		DefaultLabel->setText("");
		DefaultLabel->setFont(DefaultFont);
	endEditCP(DefaultLabel);
	
    Label::getClassType().setPrototype(DefaultLabel);
	
	//************************** Frame *****************************
	//Default FrameBorder
	EmptyBorderPtr DefaultFrameBorder = EmptyBorder::create();
	beginEditCP(DefaultFrameBorder);
		DefaultFrameBorder->setLeftWidth(0);
		DefaultFrameBorder->setRightWidth(0);
		DefaultFrameBorder->setTopWidth(0);
		DefaultFrameBorder->setBottomWidth(0);
	endEditCP(DefaultFrameBorder);

	//Default FrameBackground
	EmptyUIBackgroundPtr DefaultFrameBackground = EmptyUIBackground::create();

	//Default Frame
	FramePtr DefaultFrame = Frame::create();
	beginEditCP(DefaultFrame);
		DefaultFrame->setEnabled(true);
		DefaultFrame->setVisible(true);
		
		DefaultFrame->setConstraints(NullFC);
		//Sizes
		DefaultFrame->setMinSize(Vec2s(0,0));
		DefaultFrame->setMaxSize(Vec2s(32767,32767)); //2^15
		DefaultFrame->setPreferredSize(Vec2s(100,100));

		//Border
		DefaultFrame->setBorder(DefaultFrameBorder);
		
		//Background
		DefaultFrame->setBackground(DefaultFrameBackground);

		//Foreground
		DefaultFrame->setForegroundColor(Color4f(0.0,0.0,0.0,1.0));
		
		//Opacity
		DefaultFrame->setOpacity(1.0);
	endEditCP(DefaultFrame);
	
	Frame::getClassType().setPrototype(DefaultFrame);
	
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
	ColorUIBackgroundPtr DefaultPanelBackground = ColorUIBackground::create();
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
		DefaultPanel->setMinSize(Vec2s(0,0));
		DefaultPanel->setMaxSize(Vec2s(32767,32767)); //2^15
		DefaultPanel->setPreferredSize(Vec2s(100,100));

		//Border
		DefaultPanel->setBorder(DefaultPanelBorder);
		
		//Background
		DefaultPanel->setBackground(DefaultPanelBackground);

		//Foreground
		DefaultPanel->setForegroundColor(Color4f(0.0,0.0,0.0,1.0));
		
		//Opacity
		DefaultPanel->setOpacity(1.0);
	endEditCP(DefaultPanel);
	
	Panel::getClassType().setPrototype(DefaultPanel);
	
	//************************** ImageComponent *****************************
	//Default ImageComponentBorder
	EmptyBorderPtr DefaultImageComponentBorder = EmptyBorder::create();

	//Default ImageComponentBackground
	EmptyUIBackgroundPtr DefaultImageComponentBackground = EmptyUIBackground::create();

	//Default ImageComponent
	ImageComponentPtr DefaultImageComponent = ImageComponent::create();
	beginEditCP(DefaultImageComponent);
		DefaultImageComponent->setEnabled(true);
		DefaultImageComponent->setVisible(true);
		
		DefaultImageComponent->setConstraints(NullFC);
		//Sizes
		DefaultImageComponent->setMinSize(Vec2s(0,0));
		DefaultImageComponent->setMaxSize(Vec2s(32767,32767)); //2^15
		DefaultImageComponent->setPreferredSize(Vec2s(100,100));
		DefaultImageComponent->setSize(Vec2s(0,0));

		//Border
		DefaultImageComponent->setBorder(DefaultImageComponentBorder);
		
		//Background
		DefaultImageComponent->setBackground(DefaultImageComponentBackground);

		//Foreground
		DefaultImageComponent->setForegroundColor(Color4f(0.0,0.0,0.0,1.0));
		
		//Opacity
		DefaultImageComponent->setOpacity(1.0);

		//Image Alignment
		DefaultImageComponent->setScale(SCALE_NONE);
		DefaultImageComponent->setVerticalAlignment(VERTICAL_CENTER);
		DefaultImageComponent->setHorizontalAlignment(HORIZONTAL_CENTER);
	endEditCP(DefaultImageComponent);
	
	ImageComponent::getClassType().setPrototype(DefaultImageComponent);

	
	//************************** Checkbox Button Component *****************************
	UIDrawObjectCanvasPtr defaultCheckboxDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr defaultSelectedCheckboxDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr defaultActiveCheckboxDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr defaultActiveSelectedCheckboxDrawObject = UIDrawObjectCanvas::create();

	RectUIDrawObjectPtr CheckboxBackground = RectUIDrawObject::create();
	beginEditCP(CheckboxBackground);
		CheckboxBackground->setTopLeft(Pnt2s(1,1));
		CheckboxBackground->setBottomRight(Pnt2s(25,25));
		CheckboxBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
		CheckboxBackground->setOpacity(1.0);
	endEditCP(CheckboxBackground);

	RectUIDrawObjectPtr CheckboxBackgroundBorder = RectUIDrawObject::create();
	beginEditCP(CheckboxBackgroundBorder);
		CheckboxBackgroundBorder->setTopLeft(Pnt2s(0,0));
		CheckboxBackgroundBorder->setBottomRight(Pnt2s(26,26));
		CheckboxBackgroundBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
		CheckboxBackgroundBorder->setOpacity(1.0);
	endEditCP(CheckboxBackgroundBorder);

	RectUIDrawObjectPtr CheckboxActiveBorder = RectUIDrawObject::create();
	beginEditCP(CheckboxActiveBorder);
		CheckboxActiveBorder->setTopLeft(Pnt2s(1,1));
		CheckboxActiveBorder->setBottomRight(Pnt2s(25, 25));
		CheckboxActiveBorder->setColor(Color4f(0.0, 1.0, 0.0, 1.0));
		CheckboxActiveBorder->setOpacity(1.0);
	endEditCP(CheckboxActiveBorder);

	LineUIDrawObjectPtr CheckboxLine1 = LineUIDrawObject::create();
	beginEditCP(CheckboxLine1);
		CheckboxLine1->setTopLeft(Pnt2s(1,1));
		CheckboxLine1->setBottomRight(Pnt2s(25,25));
		CheckboxLine1->setColor(Color4f(0.0, 0.0, 0.0, 1.0));
		CheckboxLine1->setOpacity(1.0);
		CheckboxLine1->setWidth(4);
	endEditCP(CheckboxLine1);

	LineUIDrawObjectPtr CheckboxLine2 = LineUIDrawObject::create();
	beginEditCP(CheckboxLine2);
		CheckboxLine2->setTopLeft(Pnt2s(1,25));
		CheckboxLine2->setBottomRight(Pnt2s(25,1));
		CheckboxLine2->setColor(Color4f(0.0, 0.0, 0.0, 1.0));
		CheckboxLine2->setOpacity(1.0);
		CheckboxLine2->setWidth(4);
	endEditCP(CheckboxLine1);

	beginEditCP(defaultCheckboxDrawObject);
	   defaultCheckboxDrawObject->getDrawObjects().addValue(CheckboxBackgroundBorder);
	   defaultCheckboxDrawObject->getDrawObjects().addValue(CheckboxBackground);
	endEditCP(defaultCheckboxDrawObject);

	beginEditCP(defaultSelectedCheckboxDrawObject);
		defaultSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxBackgroundBorder);
		defaultSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxBackground);
		defaultSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxLine1);
		defaultSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxLine2);
	endEditCP(defaultSelectedCheckboxDrawObject);

	beginEditCP(defaultActiveSelectedCheckboxDrawObject);
		defaultActiveSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxBackgroundBorder);
		defaultActiveSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxBackground);
		defaultActiveSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxActiveBorder);
		defaultActiveSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxLine1);
		defaultActiveSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxLine2);
	endEditCP(defaultActiveSelectedCheckboxDrawObject);

	beginEditCP(defaultActiveCheckboxDrawObject);
	 	defaultActiveCheckboxDrawObject->getDrawObjects().addValue(CheckboxBackgroundBorder);
		defaultActiveCheckboxDrawObject->getDrawObjects().addValue(CheckboxBackground);
		defaultActiveCheckboxDrawObject->getDrawObjects().addValue(CheckboxActiveBorder);
	endEditCP(defaultActiveCheckboxDrawObject);

	EmptyBorderPtr DefaultCheckboxButtonBorder = EmptyBorder::create();


	ColorUIBackgroundPtr DefaultCheckboxButtonBackground = ColorUIBackground::create();
	beginEditCP(DefaultCheckboxButtonBackground);
		DefaultCheckboxButtonBackground->setColor(Color4f(0.93,0.93,0.93,1.0));
	endEditCP(DefaultCheckboxButtonBackground);

	CheckboxButtonPtr DefaultCheckboxButton = CheckboxButton::create();
	beginEditCP(DefaultCheckboxButton);
		DefaultCheckboxButton->setEnabled(true);
		DefaultCheckboxButton->setVisible(true);
		
		DefaultCheckboxButton->setConstraints(NullFC);
		//Sizes
		DefaultCheckboxButton->setMinSize(Vec2s(0,0));
		DefaultCheckboxButton->setMaxSize(Vec2s(32767,32767)); //2^15
		DefaultCheckboxButton->setPreferredSize(Vec2s(100,50));
		DefaultCheckboxButton->setSize(Vec2s(0,0));
		DefaultCheckboxButton->setDrawObject(defaultCheckboxDrawObject);
		DefaultCheckboxButton->setSelectedDrawObject(defaultSelectedCheckboxDrawObject);
		DefaultCheckboxButton->setActiveDrawObject(defaultActiveCheckboxDrawObject);
		DefaultCheckboxButton->setActiveSelectedDrawObject(defaultActiveSelectedCheckboxDrawObject);

		//Border
		DefaultCheckboxButton->setBorder(DefaultCheckboxButtonBorder);
		DefaultCheckboxButton->setActiveBorder(DefaultCheckboxButtonBorder);
		
		//Background
		DefaultCheckboxButton->setBackground(DefaultCheckboxButtonBackground);
		DefaultCheckboxButton->setActiveBackground(DefaultCheckboxButtonBackground);

		//Foreground
		DefaultCheckboxButton->setForegroundColor(Color4f(0.0,0.0,0.0,1.0));

		
		//Opacity
		DefaultCheckboxButton->setOpacity(1.0);

		//Text
		DefaultCheckboxButton->setText("");
		DefaultCheckboxButton->setFont(DefaultFont);
		DefaultCheckboxButton->setVerticalAlignment(VERTICAL_CENTER);
		DefaultCheckboxButton->setHorizontalAlignment(HORIZONTAL_CENTER);
	endEditCP(DefaultCheckboxButton);

	CheckboxButton::getClassType().setPrototype(DefaultCheckboxButton);

	//************************** Radio Button Component *****************************
	UIDrawObjectCanvasPtr defaultRadioDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr defaultSelectedRadioDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr defaultActiveRadioDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr defaultActiveSelectedRadioDrawObject = UIDrawObjectCanvas::create();

	DiscUIDrawObjectPtr RadioBackground = DiscUIDrawObject::create();
	beginEditCP(RadioBackground);
		RadioBackground->setWidth(10);
		RadioBackground->setHeight(10);
		RadioBackground->setSubDivisions(10);
		RadioBackground->setStartAngleRad(0);
		RadioBackground->setEndAngleRad(6.28318531);
		RadioBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
		RadioBackground->setOpacity(1.0);
		RadioBackground->setCenter(Pnt2s(0,0));
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
		RadioBackgroundBorder->setCenter(Pnt2s(0,0));
	endEditCP(RadioBackgroundBorder);

	DiscUIDrawObjectPtr RadioSelected = DiscUIDrawObject::create();
	beginEditCP(RadioSelected);
		RadioSelected->setWidth(6);
		RadioSelected->setHeight(6);
		RadioSelected->setSubDivisions(20);
		RadioSelected->setStartAngleRad(0);
		RadioSelected->setEndAngleRad(6.28318531);
		RadioSelected->setColor(Color4f(0.0,0.0,0.0,1.0));
		RadioSelected->setOpacity(1.0);
		RadioSelected->setCenter(Pnt2s(0,0));
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
		RadioActiveBorder->setCenter(Pnt2s(0,0));
	endEditCP(RadioActiveBorder);

	beginEditCP(defaultRadioDrawObject);
		defaultRadioDrawObject->getDrawObjects().addValue(RadioBackground);
		defaultRadioDrawObject->getDrawObjects().addValue(RadioBackgroundBorder);
	endEditCP(defaultRadioDrawObject);

	beginEditCP(defaultSelectedRadioDrawObject);
		defaultSelectedRadioDrawObject->getDrawObjects().addValue(RadioBackground);
		defaultSelectedRadioDrawObject->getDrawObjects().addValue(RadioBackgroundBorder);
		defaultSelectedRadioDrawObject->getDrawObjects().addValue(RadioSelected);
	endEditCP(defaultSelectedRadioDrawObject);

	beginEditCP(defaultActiveRadioDrawObject);
		defaultActiveRadioDrawObject->getDrawObjects().addValue(RadioBackground);
		defaultActiveRadioDrawObject->getDrawObjects().addValue(RadioBackgroundBorder);
		defaultActiveRadioDrawObject->getDrawObjects().addValue(RadioActiveBorder);
	endEditCP(defaultActiveRadioDrawObject);

	beginEditCP(defaultActiveSelectedRadioDrawObject);
		defaultActiveSelectedRadioDrawObject->getDrawObjects().addValue(RadioBackground);
		defaultActiveSelectedRadioDrawObject->getDrawObjects().addValue(RadioBackgroundBorder);
		defaultActiveSelectedRadioDrawObject->getDrawObjects().addValue(RadioSelected);
		defaultActiveSelectedRadioDrawObject->getDrawObjects().addValue(RadioActiveBorder);
	endEditCP(defaultActiveSelectedRadioDrawObject);
		
	EmptyBorderPtr DefaultRadioButtonBorder = EmptyBorder::create();

	ColorUIBackgroundPtr DefaultRadioButtonBackground = ColorUIBackground::create();
	beginEditCP(DefaultRadioButtonBackground);
		DefaultRadioButtonBackground->setColor(Color4f(0.93,0.93,0.93,1.0));
	endEditCP(DefaultRadioButtonBackground);	

	RadioButtonPtr DefaultRadioButton = RadioButton::create();
	beginEditCP(DefaultRadioButton);
		DefaultRadioButton->setEnabled(true);
		DefaultRadioButton->setVisible(true);
		DefaultRadioButton->setConstraints(NullFC);

		//sizes
		DefaultRadioButton->setMinSize(Vec2s(0, 0));
		DefaultRadioButton->setMaxSize(Vec2s(32767,32767));
		DefaultRadioButton->setPreferredSize(Vec2s(100, 100));

		//draw objecs
		DefaultRadioButton->setDrawObject(defaultRadioDrawObject);
		DefaultRadioButton->setSelectedDrawObject(defaultSelectedRadioDrawObject);
		DefaultRadioButton->setActiveDrawObject(defaultActiveRadioDrawObject);
		DefaultRadioButton->setActiveSelectedDrawObject(defaultActiveSelectedRadioDrawObject);

		//borders
		DefaultRadioButton->setBorder(DefaultRadioButtonBorder);
		DefaultRadioButton->setActiveBorder(DefaultRadioButtonBorder);

		//backgrounds
		DefaultRadioButton->setBackground(DefaultRadioButtonBackground);
		DefaultRadioButton->setActiveBackground(DefaultRadioButtonBackground);

		//colors
		DefaultRadioButton->setForegroundColor(Color4f(0.0,0.0, 0.0, 1.0));
		DefaultRadioButton->setOpacity(1.0);

		//text
		DefaultRadioButton->setText("");
		DefaultRadioButton->setFont(DefaultFont);

		//alignment
		DefaultRadioButton->setVerticalAlignment(VERTICAL_CENTER);
		DefaultRadioButton->setHorizontalAlignment(HORIZONTAL_CENTER);
	endEditCP(DefaultRadioButton);
	
	RadioButton::getClassType().setPrototype(DefaultRadioButton);

	/********Toggle Button********/

	ToggleButtonPtr DefaultToggleButton = ToggleButton::create();
	beginEditCP(DefaultToggleButton);
		DefaultToggleButton->setEnabled(true);
		DefaultToggleButton->setVisible(true);
		
		DefaultToggleButton->setConstraints(NullFC);
		//Sizes
		DefaultToggleButton->setMinSize(Vec2s(0,0));
		DefaultToggleButton->setMaxSize(Vec2s(32767,32767)); //2^15
		DefaultToggleButton->setPreferredSize(Vec2s(100,50));

		//Border
		DefaultToggleButton->setBorder(DefaultButtonBorder);
		DefaultToggleButton->setDisabledBorder(DefaultDisabledButtonBorder);
		DefaultToggleButton->setActiveBorder(DefaultActiveButtonBorder);
		
		//Background
		DefaultToggleButton->setBackground(DefaultButtonBackground);
		DefaultToggleButton->setDisabledBackground(DefaultDisabledButtonBackground);
		DefaultToggleButton->setActiveBackground(DefaultButtonBackground);

		//Foreground
		DefaultToggleButton->setForegroundColor(Color4f(0.0,0.0,0.0,1.0));
		DefaultToggleButton->setDisabledForegroundColor(Color4f(0.4,0.4,0.4,1.0));
		
		//Opacity
		DefaultToggleButton->setOpacity(1.0);

		//Text
		DefaultToggleButton->setText("");
		DefaultToggleButton->setFont(DefaultFont);
		DefaultToggleButton->setVerticalAlignment(VERTICAL_CENTER);
		DefaultToggleButton->setHorizontalAlignment(HORIZONTAL_CENTER);
	endEditCP(DefaultToggleButton);

	ToggleButton::getClassType().setPrototype(DefaultToggleButton);

	/********Text Field********/
	ColorUIBackgroundPtr DefaultTextFieldBackground = ColorUIBackground::create();
	beginEditCP(DefaultTextFieldBackground);
		DefaultTextFieldBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
	endEditCP(DefaultTextFieldBackground);

	ColorUIBackgroundPtr DefaultDisabledTextFieldBackground = ColorUIBackground::create();
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
		DefaultTextField->setMinSize(Vec2s(0, 0));
		DefaultTextField->setMaxSize(Vec2s(32767,32767));
		DefaultTextField->setPreferredSize(Vec2s(100, 25));

		//font
		DefaultTextField->setFont(DefaultFont);

		//background
		DefaultTextField->setBackground(DefaultTextFieldBackground);
		DefaultTextField->setDisabledBackground(DefaultDisabledTextFieldBackground);

		//Border
		DefaultTextField->setBorder(DefaultTextFieldBorder);
		DefaultTextField->setDisabledBorder(DefaultTextFieldBorder);

		//Color
		DefaultTextField->setForegroundColor(Color4f(0.0, 0.0, 0.0, 1.0));
		DefaultTextField->setDisabledForegroundColor(Color4f(.1, .1, .1, 1.0));

	endEditCP(DefaultTextField);

	TextField::getClassType().setPrototype(DefaultTextField);



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

	/*********Backgounds***********/
	/*********Color Background**********/
	ColorUIBackgroundPtr DefaultColorBackground = ColorUIBackground::create();
	beginEditCP(DefaultColorBackground);
		DefaultColorBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
	endEditCP(DefaultColorBackground);

	ColorUIBackground::getClassType().setPrototype(DefaultColorBackground);
	
	/**********Gradient Background***********/
	GradientUIBackgroundPtr DefaultGradientBackground = GradientUIBackground::create();
	beginEditCP(DefaultGradientBackground);
		DefaultGradientBackground->setColorStart(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultGradientBackground->setColorEnd(Color4f(1.0, 1.0, 1.0, 1.0));
		DefaultGradientBackground->setAlignment(HORIZONTAL_ALIGNMENT);
	endEditCP(DefaultGradientBackground);

	GradientUIBackground::getClassType().setPrototype(DefaultGradientBackground);

	/**********Material Background***********/
	MaterialUIBackgroundPtr DefaultMaterialBackground = MaterialUIBackground::create();
	beginEditCP(DefaultMaterialBackground);
		DefaultMaterialBackground->setMaterial(NullFC);
	endEditCP(DefaultMaterialBackground);

	MaterialUIBackground::getClassType().setPrototype(DefaultMaterialBackground);

	/*********Texture Background********/
	TextureUIBackgroundPtr DefaultTextureBackground = TextureUIBackground::create();
	beginEditCP(DefaultTextureBackground);
		DefaultTextureBackground->setTexture(NullFC);
	endEditCP(DefaultTextureBackground);

	TextureUIBackground::getClassType().setPrototype(DefaultTextureBackground);

	//CompoundBackground and Empty Background don't require prototypes.


	beginEditCP(DefaultLookAndFeelPtr(this), DefaultLookAndFeel::PrototypesFieldMask);
		getPrototypes().addValue(DefaultButton);
		getPrototypes().addValue(DefaultLabel);
		getPrototypes().addValue(DefaultFrame);
		getPrototypes().addValue(DefaultPanel);
		getPrototypes().addValue(DefaultImageComponent);
		getPrototypes().addValue(DefaultCheckboxButton);
		getPrototypes().addValue(DefaultRadioButton);
		getPrototypes().addValue(DefaultToggleButton);
		getPrototypes().addValue(DefaultTextField);
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
