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

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGWindowsLookAndFeel.h"
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
#include "Component/Container/OSGFrame.h"
#include "Component/Container/OSGPanel.h"
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
#include "Component/Text/OSGTextArea.h"

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

Real32 WindowsLookAndFeel::getTextCaretRate(void) const
{
	return _TextCaretRate;
}

void WindowsLookAndFeel::init(void)
{








	//Windows Font
	FontPtr WindowsFont = Font::create();
	beginEditCP(WindowsFont);
		WindowsFont->setFamily("Tahoma");
		WindowsFont->setGap(1);
		WindowsFont->setGlyphPixelSize(46);
		WindowsFont->setSize(14);
		WindowsFont->setTextureWidth(0);
		WindowsFont->setStyle(TextFace::STYLE_PLAIN);
	endEditCP(WindowsFont);

	//Windows ButtonBorder
	LineBorderPtr WindowsButtonBorder = LineBorder::create();
	LineBorderPtr WindowsButtonBorderBlue = LineBorder::create();
	MatteBorderPtr WindowsButtonBorderMatte = MatteBorder::create();
	CompoundBorderPtr WindowsButtonBorderCompound1 = CompoundBorder::create();
	CompoundBorderPtr WindowsButtonBorderCompound2 = CompoundBorder::create();
	beginEditCP(WindowsButtonBorderBlue);
		WindowsButtonBorderBlue->setColor( Color4f(0.0, 0.235, 0.455 ,1.0) );
		WindowsButtonBorderBlue->setWidth(1);
	endEditCP(WindowsButtonBorderBlue);
	//beginEditCP(WindowsButtonBorderMatte);
	//	WindowsMatteBorder->setRightWidth(2);
	//	WindowsMatteBorder->setLeftWidth(2);
	//	WindowsMatteBorder->setTopWidth(2);
	//	WindowsMatteBorder->setBottomWidth(2);
	//	WindowsMatteBorder->setColor(Color4f(0.0, 0.0, 0.0, 1.0));
	//beginEditCP(WindowsButtonBorderMatte);

	//Windows Disabled ButtonBorder
	BevelBorderPtr WindowsDisabledButtonBorder = BevelBorder::create();
	beginEditCP(WindowsDisabledButtonBorder);
		WindowsDisabledButtonBorder->setRaised(true);
		WindowsDisabledButtonBorder->setWidth(2);
		WindowsDisabledButtonBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
		WindowsDisabledButtonBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));/*
		WindowsButtonBorder->setShadowInner(Color4f(0.85, 0.85, 0.85, 1.0));
		WindowsButtonBorder->setShadowOuter(Color4f(0.65, 0.65, 0.65, 1.0));*/
	endEditCP(WindowsDisabledButtonBorder);


	//Windows active button border
	BevelBorderPtr WindowsActiveButtonBorder = BevelBorder::create();
	beginEditCP(WindowsActiveButtonBorder);
		WindowsActiveButtonBorder->setRaised(false);
		WindowsActiveButtonBorder->setWidth(2);
		WindowsActiveButtonBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
		WindowsActiveButtonBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
		WindowsActiveButtonBorder->setShadowInner(Color4f(0.65, 0.65, 0.65, 1.0));
		WindowsActiveButtonBorder->setShadowOuter(Color4f(0.45, 0.45, 0.45, 1.0));
	endEditCP(WindowsActiveButtonBorder);

	//Windows ButtonBackground
	GradientUIBackgroundPtr WindowsButtonBackground = GradientUIBackground::create();
	beginEditCP(WindowsButtonBackground);
		WindowsButtonBackground->setColorStart(Color4f(.988, .988, .984, 1.0));
		WindowsButtonBackground->setColorEnd(Color4f(.941, .941, .918, 1.0));
		WindowsButtonBackground->setAlignment(VERTICAL_ALIGNMENT);
	endEditCP(WindowsButtonBackground);
	
	//Windows Disabled ButtonBackground
	ColorUIBackgroundPtr WindowsDisabledButtonBackground = ColorUIBackground::create();
	beginEditCP(WindowsDisabledButtonBackground);
		WindowsDisabledButtonBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
	endEditCP(WindowsDisabledButtonBackground);

	//Windows Button
	ButtonPtr WindowsButton = Button::create();
	beginEditCP(WindowsButton);
		WindowsButton->setEnabled(true);
		WindowsButton->setVisible(true);
		
		WindowsButton->setConstraints(NullFC);
		//Sizes
		WindowsButton->setMinSize(Vec2s(0,0));
		WindowsButton->setMaxSize(Vec2s(32767,32767)); //2^15
		WindowsButton->setPreferredSize(Vec2s(68,16));

		//Border
		WindowsButton->setBorder(WindowsButtonBorderBlue);
		WindowsButton->setDisabledBorder(WindowsDisabledButtonBorder);
		WindowsButton->setActiveBorder(WindowsActiveButtonBorder);
		
		//Background
		WindowsButton->setBackground(WindowsButtonBackground);
		WindowsButton->setDisabledBackground(WindowsDisabledButtonBackground);
		WindowsButton->setActiveBackground(WindowsButtonBackground);

		//Foreground
		WindowsButton->setForegroundColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsButton->setDisabledForegroundColor(Color4f(0.4,0.4,0.4,1.0));
		
		//Opacity
		WindowsButton->setOpacity(1.0);

		//Text
		WindowsButton->setText("");
		WindowsButton->setFont(WindowsFont);
		WindowsButton->setVerticalAlignment(VERTICAL_CENTER);
		WindowsButton->setHorizontalAlignment(HORIZONTAL_CENTER);
	endEditCP(WindowsButton);

	Button::getClassType().setPrototype(WindowsButton);

	//************************** Label*****************************
	//Windows LabelBorder
	LineBorderPtr WindowsLabelBorder = LineBorder::create();
	beginEditCP(WindowsLabelBorder);
		WindowsLabelBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsLabelBorder->setWidth(1);
	endEditCP(WindowsLabelBorder);

	//Windows LabelBackground
	ColorUIBackgroundPtr WindowsLabelBackground = ColorUIBackground::create();
	beginEditCP(WindowsLabelBackground);
		WindowsLabelBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
	endEditCP(WindowsLabelBackground);

	//Windows Label
	LabelPtr WindowsLabel = Label::create();
	beginEditCP(WindowsLabel);
		WindowsLabel->setEnabled(true);
		WindowsLabel->setVisible(true);
		
		WindowsLabel->setConstraints(NullFC);
		//Sizes
		WindowsLabel->setMinSize(Vec2s(0,0));
		WindowsLabel->setMaxSize(Vec2s(32767,32767)); //2^15
		WindowsLabel->setPreferredSize(Vec2s(100,50));

		//Border
		WindowsLabel->setBorder(WindowsLabelBorder);
		
		//Background
		WindowsLabel->setBackground(WindowsLabelBackground);

		//Foreground
		WindowsLabel->setForegroundColor(Color4f(0.0,0.0,0.0,1.0));
		
		//Opacity
		WindowsLabel->setOpacity(1.0);

		//Text
		WindowsLabel->setText("");
		WindowsLabel->setFont(WindowsFont);
	endEditCP(WindowsLabel);
	
    Label::getClassType().setPrototype(WindowsLabel);
	
	//************************** Frame *****************************
	//Windows FrameBorder
	EmptyBorderPtr WindowsFrameBorder = EmptyBorder::create();
	beginEditCP(WindowsFrameBorder);
		WindowsFrameBorder->setLeftWidth(0);
		WindowsFrameBorder->setRightWidth(0);
		WindowsFrameBorder->setTopWidth(0);
		WindowsFrameBorder->setBottomWidth(0);
	endEditCP(WindowsFrameBorder);

	//Windows FrameBackground
	ColorUIBackgroundPtr WindowsFrameBackground = ColorUIBackground::create();

	beginEditCP(WindowsFrameBackground);
		WindowsFrameBackground->setColor( Color4f(.9255,.9137,.8471, 1.0) );
	endEditCP(WindowsFrameBackground);

	//Windows Frame
	FramePtr WindowsFrame = Frame::create();
	beginEditCP(WindowsFrame);
		WindowsFrame->setEnabled(true);
		WindowsFrame->setVisible(true);
		
		WindowsFrame->setConstraints(NullFC);
		//Sizes
		WindowsFrame->setMinSize(Vec2s(0,0));
		WindowsFrame->setMaxSize(Vec2s(32767,32767)); //2^15
		WindowsFrame->setPreferredSize(Vec2s(100,100));

		//Border
		WindowsFrame->setBorder(WindowsFrameBorder);
		
		//Background
		WindowsFrame->setBackground(WindowsFrameBackground);

		//Foreground
		WindowsFrame->setForegroundColor(Color4f(0.0,0.0,0.0,1.0));
		
		//Opacity
		WindowsFrame->setOpacity(1.0);
	endEditCP(WindowsFrame);
	
	Frame::getClassType().setPrototype(WindowsFrame);
	
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
	PanelPtr WindowsPanel = Panel::create();
	beginEditCP(WindowsPanel);
		WindowsPanel->setEnabled(true);
		WindowsPanel->setVisible(true);
		
		WindowsPanel->setConstraints(NullFC);
		//Sizes
		WindowsPanel->setMinSize(Vec2s(0,0));
		WindowsPanel->setMaxSize(Vec2s(32767,32767)); //2^15
		WindowsPanel->setPreferredSize(Vec2s(100,100));

		//Border
		WindowsPanel->setBorder(WindowsPanelBorder);
		
		//Background
		WindowsPanel->setBackground(WindowsPanelBackground);

		//Foreground
		WindowsPanel->setForegroundColor(Color4f(0.0,0.0,0.0,1.0));
		
		//Opacity
		WindowsPanel->setOpacity(1.0);
	endEditCP(WindowsPanel);
	
	Panel::getClassType().setPrototype(WindowsPanel);
	
	//************************** ImageComponent *****************************
	//Windows ImageComponentBorder
	EmptyBorderPtr WindowsImageComponentBorder = EmptyBorder::create();

	//Windows ImageComponentBackground
	EmptyUIBackgroundPtr WindowsImageComponentBackground = EmptyUIBackground::create();

	//Windows ImageComponent
	ImageComponentPtr WindowsImageComponent = ImageComponent::create();
	beginEditCP(WindowsImageComponent);
		WindowsImageComponent->setEnabled(true);
		WindowsImageComponent->setVisible(true);
		
		WindowsImageComponent->setConstraints(NullFC);
		//Sizes
		WindowsImageComponent->setMinSize(Vec2s(0,0));
		WindowsImageComponent->setMaxSize(Vec2s(32767,32767)); //2^15
		WindowsImageComponent->setPreferredSize(Vec2s(100,100));
		WindowsImageComponent->setSize(Vec2s(0,0));

		//Border
		WindowsImageComponent->setBorder(WindowsImageComponentBorder);
		
		//Background
		WindowsImageComponent->setBackground(WindowsImageComponentBackground);

		//Foreground
		WindowsImageComponent->setForegroundColor(Color4f(0.0,0.0,0.0,1.0));
		
		//Opacity
		WindowsImageComponent->setOpacity(1.0);

		//Image Alignment
		WindowsImageComponent->setScale(SCALE_NONE);
		WindowsImageComponent->setVerticalAlignment(VERTICAL_CENTER);
		WindowsImageComponent->setHorizontalAlignment(HORIZONTAL_CENTER);
	endEditCP(WindowsImageComponent);
	
	ImageComponent::getClassType().setPrototype(WindowsImageComponent);

	
	//************************** Checkbox Button Component *****************************
	UIDrawObjectCanvasPtr WindowsCheckboxDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsSelectedCheckboxDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsActiveCheckboxDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsActiveSelectedCheckboxDrawObject = UIDrawObjectCanvas::create();

	RectUIDrawObjectPtr CheckboxBackground = RectUIDrawObject::create();
	beginEditCP(CheckboxBackground);
		CheckboxBackground->setTopLeft(Pnt2s(1,1));
		CheckboxBackground->setBottomRight(Pnt2s(12,12));
		CheckboxBackground->setColor(Color4f(.945,.945,.937,1.0));
		CheckboxBackground->setOpacity(1.0);
	endEditCP(CheckboxBackground);

	RectUIDrawObjectPtr CheckboxBackgroundBorder = RectUIDrawObject::create();
	beginEditCP(CheckboxBackgroundBorder);
		CheckboxBackgroundBorder->setTopLeft(Pnt2s(0,0));
		CheckboxBackgroundBorder->setBottomRight(Pnt2s(13,13));
		CheckboxBackgroundBorder->setColor(Color4f(.110,.318,.502,1.0));
		CheckboxBackgroundBorder->setOpacity(1.0);
	endEditCP(CheckboxBackgroundBorder);

	RectUIDrawObjectPtr CheckboxActiveBackground = RectUIDrawObject::create();
	beginEditCP(CheckboxActiveBackground);
		CheckboxActiveBackground->setTopLeft(Pnt2s(1,1));
		CheckboxActiveBackground->setBottomRight(Pnt2s(12, 12));
		CheckboxActiveBackground->setColor(Color4f(.859,.855,.800,1.0));
		CheckboxActiveBackground->setOpacity(1.0);
	endEditCP(CheckboxActiveBackground);

	LineUIDrawObjectPtr CheckboxLine1 = LineUIDrawObject::create();
	beginEditCP(CheckboxLine1);
		CheckboxLine1->setTopLeft(Pnt2s(2,6));
		CheckboxLine1->setBottomRight(Pnt2s(5,9));
		CheckboxLine1->setColor(Color4f(.129, .631, .129, 1.0));
		CheckboxLine1->setOpacity(1.0);
		CheckboxLine1->setWidth(1);
	endEditCP(CheckboxLine1);

	LineUIDrawObjectPtr CheckboxLine2 = LineUIDrawObject::create();
	beginEditCP(CheckboxLine2);
		CheckboxLine2->setTopLeft(Pnt2s(5,9));
		CheckboxLine2->setBottomRight(Pnt2s(10,4));
		CheckboxLine2->setColor(Color4f(.129, .631, .129, 1.0));
		CheckboxLine2->setOpacity(1.0);
		CheckboxLine2->setWidth(1);
	endEditCP(CheckboxLine2);

	beginEditCP(WindowsCheckboxDrawObject);
	   WindowsCheckboxDrawObject->getDrawObjects().addValue(CheckboxBackgroundBorder);
	   WindowsCheckboxDrawObject->getDrawObjects().addValue(CheckboxBackground);
	endEditCP(WindowsCheckboxDrawObject);

	beginEditCP(WindowsSelectedCheckboxDrawObject);
		WindowsSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxBackgroundBorder);
		WindowsSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxBackground);
		WindowsSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxLine1);
		WindowsSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxLine2);
	endEditCP(WindowsSelectedCheckboxDrawObject);

	beginEditCP(WindowsActiveSelectedCheckboxDrawObject);
		WindowsActiveSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxBackgroundBorder);
		WindowsActiveSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxBackground);
		WindowsActiveSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxActiveBackground);
		WindowsActiveSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxLine1);
		WindowsActiveSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxLine2);
	endEditCP(WindowsActiveSelectedCheckboxDrawObject);

	beginEditCP(WindowsActiveCheckboxDrawObject);
	 	WindowsActiveCheckboxDrawObject->getDrawObjects().addValue(CheckboxBackgroundBorder);
		WindowsActiveCheckboxDrawObject->getDrawObjects().addValue(CheckboxBackground);
		WindowsActiveCheckboxDrawObject->getDrawObjects().addValue(CheckboxActiveBackground);
	endEditCP(WindowsActiveCheckboxDrawObject);

	EmptyBorderPtr WindowsCheckboxButtonBorder = EmptyBorder::create();


	EmptyUIBackgroundPtr WindowsCheckboxButtonBackground = EmptyUIBackground::create();


	CheckboxButtonPtr WindowsCheckboxButton = CheckboxButton::create();
	beginEditCP(WindowsCheckboxButton);
		WindowsCheckboxButton->setEnabled(true);
		WindowsCheckboxButton->setVisible(true);
		
		WindowsCheckboxButton->setConstraints(NullFC);
		//Sizes
		WindowsCheckboxButton->setMinSize(Vec2s(0,0));
		WindowsCheckboxButton->setMaxSize(Vec2s(32767,32767)); //2^15
		WindowsCheckboxButton->setPreferredSize(Vec2s(100,50));
		WindowsCheckboxButton->setSize(Vec2s(0,0));
		WindowsCheckboxButton->setDrawObject(WindowsCheckboxDrawObject);
		WindowsCheckboxButton->setSelectedDrawObject(WindowsSelectedCheckboxDrawObject);
		WindowsCheckboxButton->setActiveDrawObject(WindowsActiveCheckboxDrawObject);
		WindowsCheckboxButton->setActiveSelectedDrawObject(WindowsActiveSelectedCheckboxDrawObject);

		//Border
		WindowsCheckboxButton->setBorder(WindowsCheckboxButtonBorder);
		WindowsCheckboxButton->setActiveBorder(WindowsCheckboxButtonBorder);
		
		//Background
		WindowsCheckboxButton->setBackground(WindowsCheckboxButtonBackground);
		WindowsCheckboxButton->setActiveBackground(WindowsCheckboxButtonBackground);

		//Foreground
		WindowsCheckboxButton->setForegroundColor(Color4f(0.0,0.0,0.0,1.0));

		
		//Opacity
		WindowsCheckboxButton->setOpacity(1.0);

		//Text
		WindowsCheckboxButton->setText("");
		WindowsCheckboxButton->setFont(WindowsFont);
		WindowsCheckboxButton->setVerticalAlignment(VERTICAL_CENTER);
		WindowsCheckboxButton->setHorizontalAlignment(HORIZONTAL_CENTER);
	endEditCP(WindowsCheckboxButton);

	CheckboxButton::getClassType().setPrototype(WindowsCheckboxButton);

	//************************** Radio Button Component *****************************
	UIDrawObjectCanvasPtr WindowsRadioDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsSelectedRadioDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsActiveRadioDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsActiveSelectedRadioDrawObject = UIDrawObjectCanvas::create();

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
		RadioBackground->setCenter(Pnt2s(0,0));
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
		RadioBackgroundBorder->setCenter(Pnt2s(0,0));
	endEditCP(RadioBackgroundBorder);

	DiscUIDrawObjectPtr RadioSelected = DiscUIDrawObject::create();
	beginEditCP(RadioSelected);
		RadioSelected->setWidth(3);
		RadioSelected->setHeight(3);
		RadioSelected->setSubDivisions(15);
		RadioSelected->setStartAngleRad(0);
		RadioSelected->setEndAngleRad(6.28318531);
		RadioSelected->setCenterColor(Color4f(0.220,0.725,0.208,1.0));
		RadioSelected->setOuterColor(Color4f(0.220,0.725,0.208,1.0));
		RadioSelected->setOpacity(1.0);
		RadioSelected->setCenter(Pnt2s(0,0));
	endEditCP(RadioSelected);

	DiscUIDrawObjectPtr RadioSelectedBackground = DiscUIDrawObject::create();
	beginEditCP(RadioSelectedBackground);
		RadioSelectedBackground->setWidth(6);
		RadioSelectedBackground->setHeight(6);
		RadioSelectedBackground->setSubDivisions(30);
		RadioSelectedBackground->setStartAngleRad(0);
		RadioSelectedBackground->setEndAngleRad(6.28318531);
		RadioSelectedBackground->setCenterColor(Color4f(.804,.800,.753,1.0));
		RadioSelectedBackground->setOuterColor(Color4f(.804,.800,.753,1.0));
		RadioSelectedBackground->setOpacity(1.0);
		RadioSelectedBackground->setCenter(Pnt2s(0,0));
	endEditCP(RadioSelectedBackground);

	// Yellow highlight border for whenever there is a hover listener

	//ArcUIDrawObjectPtr RadioActiveBorder = ArcUIDrawObject::create();
	//beginEditCP(RadioActiveBorder);
	//	RadioActiveBorder->setWidth(4);
	//	RadioActiveBorder->setHeight(4);
	//	RadioActiveBorder->setSubDivisions(25);
	//	RadioActiveBorder->setStartAngleRad(0);
	//	RadioActiveBorder->setEndAngleRad(6.28318531);
	//	RadioActiveBorder->setColor(Color4f(.980,.753,.306,1.0));
	//	RadioActiveBorder->setOpacity(.85);
	//	RadioActiveBorder->setCenter(Pnt2s(0,0));
	//	RadioActiveBorder->setLineWidth(2);
	//endEditCP(RadioActiveBorder);

	beginEditCP(WindowsRadioDrawObject);
		WindowsRadioDrawObject->getDrawObjects().addValue(RadioBackground);
		WindowsRadioDrawObject->getDrawObjects().addValue(RadioBackgroundBorder);
	endEditCP(WindowsRadioDrawObject);

	beginEditCP(WindowsSelectedRadioDrawObject);
		WindowsSelectedRadioDrawObject->getDrawObjects().addValue(RadioBackground);
		WindowsSelectedRadioDrawObject->getDrawObjects().addValue(RadioBackgroundBorder);
		WindowsSelectedRadioDrawObject->getDrawObjects().addValue(RadioSelected);
	endEditCP(WindowsSelectedRadioDrawObject);

	beginEditCP(WindowsActiveRadioDrawObject);
		WindowsActiveRadioDrawObject->getDrawObjects().addValue(RadioSelectedBackground);
		WindowsActiveRadioDrawObject->getDrawObjects().addValue(RadioBackgroundBorder);
	endEditCP(WindowsActiveRadioDrawObject);

	beginEditCP(WindowsActiveSelectedRadioDrawObject);
		WindowsActiveSelectedRadioDrawObject->getDrawObjects().addValue(RadioSelectedBackground);
		WindowsActiveSelectedRadioDrawObject->getDrawObjects().addValue(RadioBackgroundBorder);
		WindowsActiveSelectedRadioDrawObject->getDrawObjects().addValue(RadioSelected);
	endEditCP(WindowsActiveSelectedRadioDrawObject);
		
	EmptyBorderPtr WindowsRadioButtonBorder = EmptyBorder::create();
	EmptyUIBackgroundPtr WindowsRadioButtonBackground = EmptyUIBackground::create();
	

	RadioButtonPtr WindowsRadioButton = RadioButton::create();
	beginEditCP(WindowsRadioButton);
		WindowsRadioButton->setEnabled(true);
		WindowsRadioButton->setVisible(true);
		WindowsRadioButton->setConstraints(NullFC);

		//sizes
		WindowsRadioButton->setMinSize(Vec2s(0, 0));
		WindowsRadioButton->setMaxSize(Vec2s(32767,32767));
		WindowsRadioButton->setPreferredSize(Vec2s(100, 35));

		//draw objects
		WindowsRadioButton->setDrawObject(WindowsRadioDrawObject);
		WindowsRadioButton->setSelectedDrawObject(WindowsSelectedRadioDrawObject);
		WindowsRadioButton->setActiveDrawObject(WindowsActiveRadioDrawObject);
		WindowsRadioButton->setActiveSelectedDrawObject(WindowsActiveSelectedRadioDrawObject);

		//borders
		WindowsRadioButton->setBorder(WindowsRadioButtonBorder);
		WindowsRadioButton->setActiveBorder(WindowsRadioButtonBorder);

		//backgrounds
		WindowsRadioButton->setBackground(WindowsRadioButtonBackground);
		WindowsRadioButton->setActiveBackground(WindowsRadioButtonBackground);

		//colors
		WindowsRadioButton->setForegroundColor(Color4f(0.0,0.0, 0.0, 1.0));
		WindowsRadioButton->setOpacity(1.0);

		//text
		WindowsRadioButton->setText("");
		WindowsRadioButton->setFont(WindowsFont);

		//alignment
		WindowsRadioButton->setVerticalAlignment(VERTICAL_CENTER);
		WindowsRadioButton->setHorizontalAlignment(HORIZONTAL_CENTER);
	endEditCP(WindowsRadioButton);
	
	RadioButton::getClassType().setPrototype(WindowsRadioButton);

	/********Toggle Button********/

	ToggleButtonPtr WindowsToggleButton = ToggleButton::create();
	beginEditCP(WindowsToggleButton);
		WindowsToggleButton->setEnabled(true);
		WindowsToggleButton->setVisible(true);
		
		WindowsToggleButton->setConstraints(NullFC);
		//Sizes
		WindowsToggleButton->setMinSize(Vec2s(0,0));
		WindowsToggleButton->setMaxSize(Vec2s(32767,32767)); //2^15
		WindowsToggleButton->setPreferredSize(Vec2s(100,50));

		//Border
		WindowsToggleButton->setBorder(WindowsButtonBorder);
		WindowsToggleButton->setDisabledBorder(WindowsDisabledButtonBorder);
		WindowsToggleButton->setActiveBorder(WindowsActiveButtonBorder);
		
		//Background
		WindowsToggleButton->setBackground(WindowsButtonBackground);
		WindowsToggleButton->setDisabledBackground(WindowsDisabledButtonBackground);
		WindowsToggleButton->setActiveBackground(WindowsButtonBackground);

		//Foreground
		WindowsToggleButton->setForegroundColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsToggleButton->setDisabledForegroundColor(Color4f(0.4,0.4,0.4,1.0));
		
		//Opacity
		WindowsToggleButton->setOpacity(1.0);

		//Text
		WindowsToggleButton->setText("");
		WindowsToggleButton->setFont(WindowsFont);
		WindowsToggleButton->setVerticalAlignment(VERTICAL_CENTER);
		WindowsToggleButton->setHorizontalAlignment(HORIZONTAL_CENTER);
	endEditCP(WindowsToggleButton);

	ToggleButton::getClassType().setPrototype(WindowsToggleButton);

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


	TextFieldPtr WindowsTextField = TextField::create();
	beginEditCP(WindowsTextField);
		//size
		WindowsTextField->setMinSize(Vec2s(0, 0));
		WindowsTextField->setMaxSize(Vec2s(32767,32767));
		WindowsTextField->setPreferredSize(Vec2s(100, 22));

		//font
		WindowsTextField->setFont(WindowsFont);
		
		WindowsTextField->setSelectionBoxColor(Color4f(.682, .769, .910, 1.0));
		WindowsTextField->setSelectionTextColor(Color4f(0.0, 0.0, 0.0, 1.0));

		//background
		WindowsTextField->setBackground(WindowsTextFieldBackground);
		WindowsTextField->setDisabledBackground(WindowsDisabledTextFieldBackground);

		//Border
		WindowsTextField->setBorder(WindowsTextFieldBorder);
		WindowsTextField->setDisabledBorder(WindowsTextFieldBorder);

		//Color
		WindowsTextField->setForegroundColor(Color4f(0.0, 0.0, 0.0, 1.0));
		WindowsTextField->setDisabledForegroundColor(Color4f(.1, .1, .1, 1.0));

	endEditCP(WindowsTextField);

	TextField::getClassType().setPrototype(WindowsTextField);

	/********Text Area********/
	ColorUIBackgroundPtr WindowsTextAreaBackground = ColorUIBackground::create();
	beginEditCP(WindowsTextAreaBackground);
		WindowsTextAreaBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
	endEditCP(WindowsTextAreaBackground);

	ColorUIBackgroundPtr WindowsDisabledTextAreaBackground = ColorUIBackground::create();
	beginEditCP(WindowsDisabledTextAreaBackground);
		WindowsDisabledTextAreaBackground->setColor(Color4f(.8, .8, .8, 1.0));
	endEditCP(WindowsDisabledTextAreaBackground);

	BevelBorderPtr WindowsTextAreaBorder = BevelBorder::create();
	beginEditCP(WindowsTextAreaBorder, BevelBorder::RaisedFieldMask);
		WindowsTextAreaBorder->setRaised(false);
		WindowsTextAreaBorder->setWidth(2);
		WindowsTextAreaBorder->setHighlightInner(Color4f(.9, .9, .9, 1.0));
		WindowsTextAreaBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
		WindowsTextAreaBorder->setShadowInner(Color4f(0.65, 0.65, 0.65, 1.0));
		WindowsTextAreaBorder->setShadowOuter(Color4f(0.45, 0.45, 0.45, 1.0));
	endEditCP(WindowsTextAreaBorder, BevelBorder::RaisedFieldMask);

	TextAreaPtr WindowsTextArea = TextArea::create();
	beginEditCP(WindowsTextArea);
		//size
		WindowsTextArea->setMinSize(Vec2s(0, 0));
		WindowsTextArea->setMaxSize(Vec2s(32767,32767));
		WindowsTextArea->setPreferredSize(Vec2s(100, 25));

		//font
		WindowsTextArea->setFont(WindowsFont);
		WindowsTextArea->setSelectionBoxColor(Color4f(0.0, 0.0, 1.0, 1.0));
		WindowsTextArea->setSelectionTextColor(Color4f(0.0, 0.0, 0.0, 1.0));
		

		//background
		WindowsTextArea->setBackground(WindowsTextAreaBackground);
		WindowsTextArea->setDisabledBackground(WindowsDisabledTextAreaBackground);

		//Border
		WindowsTextArea->setBorder(WindowsTextAreaBorder);
		WindowsTextArea->setDisabledBorder(WindowsTextAreaBorder);

		//Color
		WindowsTextArea->setForegroundColor(Color4f(0.0, 0.0, 0.0, 1.0));
		WindowsTextArea->setDisabledForegroundColor(Color4f(.1, .1, .1, 1.0));

	endEditCP(WindowsTextArea);

	TextArea::getClassType().setPrototype(WindowsTextArea);


	/*******Borders********/
	/*******Line Border********/

	LineBorderPtr WindowsLineBorder = LineBorder::create();
	beginEditCP(WindowsLineBorder);
		WindowsLineBorder->setWidth(1);
		WindowsLineBorder->setColor(Color4f(0.0, 0.0, 0.0, 1.0));
	endEditCP(WindowsLineBorder);

	LineBorder::getClassType().setPrototype(WindowsLineBorder);

	/********Etched Border********/

	EtchedBorderPtr WindowsEtchedBorder = EtchedBorder::create();
	beginEditCP(WindowsEtchedBorder);
		WindowsEtchedBorder->setWidth(2);
		WindowsEtchedBorder->setRaised(true);
		WindowsEtchedBorder->setHighlight(Color4f(1.0, 1.0, 1.0, 1.0));
		WindowsEtchedBorder->setShadow(Color4f(0.65, 0.65, 0.65, 1.0));
	endEditCP(WindowsEtchedBorder);

	EtchedBorder::getClassType().setPrototype(WindowsEtchedBorder);
	
	/********Empty Border*********/
	EmptyBorderPtr WindowsEmptyBorder = EmptyBorder::create();
	beginEditCP(WindowsEmptyBorder);
		WindowsEmptyBorder->setTopWidth(0);
		WindowsEmptyBorder->setBottomWidth(0);
		WindowsEmptyBorder->setRightWidth(0);
		WindowsEmptyBorder->setLeftWidth(0);
	endEditCP(WindowsEmptyBorder);

	EmptyBorder::getClassType().setPrototype(WindowsEmptyBorder);


	/********Bevel Border**********/

	BevelBorderPtr WindowsBevelBorder = BevelBorder::create();
	beginEditCP(WindowsBevelBorder);
		WindowsBevelBorder->setRaised(true);
		WindowsBevelBorder->setWidth(2);
		WindowsBevelBorder->setHighlightInner(Color4f(1.0, 1.0, 1.0, 1.0));
		WindowsBevelBorder->setHighlightOuter(Color4f(1.0, 1.0, 1.0, 1.0));
		WindowsBevelBorder->setShadowInner(Color4f(0.65, 0.65, 0.65, 1.0));
		WindowsBevelBorder->setShadowOuter(Color4f(0.45, 0.45, 0.45, 1.0));
	endEditCP(WindowsBevelBorder);

	BevelBorder::getClassType().setPrototype(WindowsBevelBorder);

	/********Matte Border**********/

	MatteBorderPtr WindowsMatteBorder = MatteBorder::create();
	beginEditCP(WindowsMatteBorder);
		WindowsMatteBorder->setRightWidth(1);
		WindowsMatteBorder->setLeftWidth(1);
		WindowsMatteBorder->setTopWidth(1);
		WindowsMatteBorder->setBottomWidth(1);
		WindowsMatteBorder->setColor(Color4f(0.0, 0.0, 0.0, 1.0));
	endEditCP(WindowsMatteBorder);

	MatteBorder::getClassType().setPrototype(WindowsMatteBorder);

	/********Compound Border********/
	CompoundBorderPtr WindowsCompoundBorder = CompoundBorder::create();
	beginEditCP(WindowsCompoundBorder);
		WindowsCompoundBorder->setInnerBorder(NullFC);
		WindowsCompoundBorder->setOuterBorder(NullFC);
	endEditCP(WindowsCompoundBorder);

	CompoundBorder::getClassType().setPrototype(WindowsCompoundBorder);

	/*********Backgounds***********/
	/*********Color Background**********/
	ColorUIBackgroundPtr WindowsColorBackground = ColorUIBackground::create();
	beginEditCP(WindowsColorBackground);
		WindowsColorBackground->setColor(Color4f(1.0, 1.0, 1.0, 1.0));
	endEditCP(WindowsColorBackground);

	ColorUIBackground::getClassType().setPrototype(WindowsColorBackground);
	
	/**********Gradient Background***********/
	GradientUIBackgroundPtr WindowsGradientBackground = GradientUIBackground::create();
	beginEditCP(WindowsGradientBackground);
		WindowsGradientBackground->setColorStart(Color4f(1.0, 1.0, 1.0, 1.0));
		WindowsGradientBackground->setColorEnd(Color4f(1.0, 1.0, 1.0, 1.0));
		WindowsGradientBackground->setAlignment(HORIZONTAL_ALIGNMENT);
	endEditCP(WindowsGradientBackground);

	GradientUIBackground::getClassType().setPrototype(WindowsGradientBackground);

	/**********Material Background***********/
	MaterialUIBackgroundPtr WindowsMaterialBackground = MaterialUIBackground::create();
	beginEditCP(WindowsMaterialBackground);
		WindowsMaterialBackground->setMaterial(NullFC);
	endEditCP(WindowsMaterialBackground);

	MaterialUIBackground::getClassType().setPrototype(WindowsMaterialBackground);

	/*********Texture Background********/
	TextureUIBackgroundPtr WindowsTextureBackground = TextureUIBackground::create();
	beginEditCP(WindowsTextureBackground);
		WindowsTextureBackground->setTexture(NullFC);
	endEditCP(WindowsTextureBackground);

	TextureUIBackground::getClassType().setPrototype(WindowsTextureBackground);

	//CompoundBackground and Empty Background don't require prototypes.


	beginEditCP(WindowsLookAndFeelPtr(this), WindowsLookAndFeel::PrototypesFieldMask);
		getPrototypes().addValue(WindowsButton);
		getPrototypes().addValue(WindowsLabel);
		getPrototypes().addValue(WindowsFrame);
		getPrototypes().addValue(WindowsPanel);
		getPrototypes().addValue(WindowsImageComponent);
		getPrototypes().addValue(WindowsCheckboxButton);
		getPrototypes().addValue(WindowsRadioButton);
		getPrototypes().addValue(WindowsToggleButton);
		getPrototypes().addValue(WindowsTextField);
	endEditCP(WindowsLookAndFeelPtr(this), WindowsLookAndFeel::PrototypesFieldMask);






}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

WindowsLookAndFeel::WindowsLookAndFeel(void) :
    Inherited(),
		_TextCaretRate(1.0)
{
}

WindowsLookAndFeel::WindowsLookAndFeel(const WindowsLookAndFeel &source) :
    Inherited(source),
		_TextCaretRate(source._TextCaretRate)
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

