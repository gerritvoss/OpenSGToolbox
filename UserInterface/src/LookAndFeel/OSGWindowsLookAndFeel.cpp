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
#include "Component/OSGLabel.h"
#include "Component/Container/OSGFrame.h"
#include "Component/Container/OSGPanel.h"
#include "Component/Container/OSGSplitPanel.h"
#include "Component/OSGImageComponent.h"
#include "Util/OSGUIDefines.h"
#include "Graphics/UIDrawObjects/OSGRectUIDrawObject.h"
#include "Graphics/UIDrawObjects/OSGMultiColoredQuadUIDrawObject.h"
#include "Graphics/UIDrawObjects/OSGArcUIDrawObject.h"
#include "Graphics/UIDrawObjects/OSGDiscUIDrawObject.h"
#include "Graphics/UIDrawObjects/OSGLineUIDrawObject.h"
#include "Component/OSGUIDrawObjectCanvas.h"
#include "Component/Text/OSGTextField.h"
#include "Component/Text/OSGPasswordField.h"
#include "Component/Text/OSGTextArea.h"
#include "Component/Misc/OSGToolTip.h"

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

Time WindowsLookAndFeel::getTextCaretRate(void) const
{
	return _TextCaretRate;
}


Time WindowsLookAndFeel::getToolTipPopupTime(void) const
{
	return _ToolTipPopupTime;
}


Time WindowsLookAndFeel::getSubMenuPopupTime(void) const
{
	return _SubMenuPopupTime;
}

void WindowsLookAndFeel::init(void)
{








	//Windows Font
	UIFontPtr WindowsFont = UIFont::create();
	beginEditCP(WindowsFont);
		WindowsFont->setFamily("Tahoma");
		WindowsFont->setGap(1);
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
		WindowsButtonBackground->setAlignment(VERTICAL_ALIGNMENT);
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
		WindowsActiveButtonBackground->setAlignment(VERTICAL_ALIGNMENT);
	endEditCP(WindowsActiveButtonBackground);
    
	//Windows Rollover ButtonBackground
	GradientUIBackgroundPtr WindowsRolloverButtonBackground = GradientUIBackground::create();
	beginEditCP(WindowsRolloverButtonBackground);
		WindowsRolloverButtonBackground->setColorStart(Color4f(.99, .99, .98, 1.0));
		WindowsRolloverButtonBackground->setColorEnd(Color4f(.93, .92, .90, 1.0));
		WindowsRolloverButtonBackground->setAlignment(VERTICAL_ALIGNMENT);
	endEditCP(WindowsRolloverButtonBackground);

	//Windows Button
	ButtonPtr WindowsButton = Button::create();
	beginEditCP(WindowsButton);
		WindowsButton->setEnabled(true);
		WindowsButton->setVisible(true);
		
		WindowsButton->setConstraints(NullFC);
		//Sizes
		WindowsButton->setMinSize(Vec2s(0,0));
		WindowsButton->setMaxSize(Vec2s(32767,32767)); //2^15
		WindowsButton->setPreferredSize(Vec2s(75,23));

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
		WindowsLabel->setPreferredSize(Vec2s(75,23));

		//Border
		WindowsLabel->setBorder(WindowsLabelBorder);
		
		//Background
		WindowsLabel->setBackground(WindowsLabelBackground);
		
		//Opacity
		WindowsLabel->setOpacity(1.0);

		//Text
		WindowsLabel->setText("");
		WindowsLabel->setFont(WindowsFont);
		WindowsLabel->setTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsLabel->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsLabel->setRolloverTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsLabel->setDisabledTextColor(WindowsDisabledTextColor);
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
		
		//Opacity
		WindowsPanel->setOpacity(1.0);
	endEditCP(WindowsPanel);
	
	Panel::getClassType().setPrototype(WindowsPanel);
	
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
	SplitPanelPtr WindowsSplitPanel = SplitPanel::create();
	beginEditCP(WindowsSplitPanel);
		WindowsSplitPanel->setDividerDrawObject(WindowsDividerDrawObject);
		WindowsSplitPanel->setDividerSize(5);
	endEditCP(WindowsSplitPanel);

	SplitPanel::getClassType().setPrototype(WindowsSplitPanel);

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
		
		//Opacity
		WindowsImageComponent->setOpacity(1.0);

		//Image Alignment
		WindowsImageComponent->setScale(SCALE_NONE);
		WindowsImageComponent->setVerticalAlignment(0.5);
		WindowsImageComponent->setHorizontalAlignment(0.5);
	endEditCP(WindowsImageComponent);
	
	ImageComponent::getClassType().setPrototype(WindowsImageComponent);

	
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
        CheckboxBackground->setPoint1(Pnt2s(1,1));
        CheckboxBackground->setPoint2(Pnt2s(12,1));
        CheckboxBackground->setPoint3(Pnt2s(12,12));
        CheckboxBackground->setPoint4(Pnt2s(1,12));
		CheckboxBackground->setColor1(Color4f(.86,.86,.84,1.0));
		CheckboxBackground->setColor2(Color4f(.95,.95,.94,1.0));
		CheckboxBackground->setColor3(Color4f(1.0,1.0,1.0,1.0));
		CheckboxBackground->setColor4(Color4f(.95,.95,.94,1.0));
		CheckboxBackground->setOpacity(1.0);
	endEditCP(CheckboxBackground);

    //Normal Border
	RectUIDrawObjectPtr CheckboxBackgroundBorder = RectUIDrawObject::create();
	beginEditCP(CheckboxBackgroundBorder);
		CheckboxBackgroundBorder->setTopLeft(Pnt2s(0,0));
		CheckboxBackgroundBorder->setBottomRight(Pnt2s(13,13));
		CheckboxBackgroundBorder->setColor(Color4f(.110,.318,.502,1.0));
		CheckboxBackgroundBorder->setOpacity(1.0);
	endEditCP(CheckboxBackgroundBorder);

    //Active Background
	MultiColoredQuadUIDrawObjectPtr CheckboxActiveBackground = MultiColoredQuadUIDrawObject::create();
	beginEditCP(CheckboxActiveBackground);
        CheckboxActiveBackground->setPoint1(Pnt2s(1,1));
        CheckboxActiveBackground->setPoint2(Pnt2s(12,1));
        CheckboxActiveBackground->setPoint3(Pnt2s(12,12));
        CheckboxActiveBackground->setPoint4(Pnt2s(1,12));
		CheckboxActiveBackground->setColor1(Color4f(.69,.69,.65,1.0));
		CheckboxActiveBackground->setColor2(Color4f(.95,.94,.87,1.0));
		CheckboxActiveBackground->setColor3(Color4f(1.0,1.0,1.0,1.0));
		CheckboxActiveBackground->setColor4(Color4f(.84,.84,.78,1.0));
		CheckboxActiveBackground->setOpacity(1.0);
	endEditCP(CheckboxActiveBackground);
    
    //Disabled Background
	RectUIDrawObjectPtr CheckboxDisabledBackground = RectUIDrawObject::create();
	beginEditCP(CheckboxDisabledBackground);
		CheckboxDisabledBackground->setTopLeft(Pnt2s(1,1));
		CheckboxDisabledBackground->setBottomRight(Pnt2s(12,12));
		CheckboxDisabledBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
		CheckboxDisabledBackground->setOpacity(1.0);
	endEditCP(CheckboxDisabledBackground);

    //Disabled Border
	RectUIDrawObjectPtr CheckboxDisabledBackgroundBorder = RectUIDrawObject::create();
	beginEditCP(CheckboxDisabledBackgroundBorder);
		CheckboxDisabledBackgroundBorder->setTopLeft(Pnt2s(0,0));
		CheckboxDisabledBackgroundBorder->setBottomRight(Pnt2s(13,13));
		CheckboxDisabledBackgroundBorder->setColor(Color4f(.79,.78,.73,1.0));
		CheckboxDisabledBackgroundBorder->setOpacity(1.0);
	endEditCP(CheckboxDisabledBackgroundBorder);

    //The Checkmark
    Color4f CheckmarkColor(0.13,0.63,0.13,1.0);
	MultiColoredQuadUIDrawObjectPtr CheckboxCheckQuad1 = MultiColoredQuadUIDrawObject::create();
	beginEditCP(CheckboxCheckQuad1);
        CheckboxCheckQuad1->setPoint1(Pnt2s(3,4));
        CheckboxCheckQuad1->setPoint2(Pnt2s(6,7));
        CheckboxCheckQuad1->setPoint3(Pnt2s(6,10));
        CheckboxCheckQuad1->setPoint4(Pnt2s(3,7));
		CheckboxCheckQuad1->setColor1(CheckmarkColor);
		CheckboxCheckQuad1->setColor2(CheckmarkColor);
		CheckboxCheckQuad1->setColor3(CheckmarkColor);
		CheckboxCheckQuad1->setColor4(CheckmarkColor);
		CheckboxCheckQuad1->setOpacity(1.0);
	endEditCP(CheckboxCheckQuad1);

	MultiColoredQuadUIDrawObjectPtr CheckboxCheckQuad2 = MultiColoredQuadUIDrawObject::create();
	beginEditCP(CheckboxCheckQuad2);
        CheckboxCheckQuad2->setPoint1(Pnt2s(6,7));
        CheckboxCheckQuad2->setPoint2(Pnt2s(10,3));
        CheckboxCheckQuad2->setPoint3(Pnt2s(10,6));
        CheckboxCheckQuad2->setPoint4(Pnt2s(6,10));
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
        CheckboxDisabledCheckQuad1->setPoint1(Pnt2s(3,4));
        CheckboxDisabledCheckQuad1->setPoint2(Pnt2s(6,7));
        CheckboxDisabledCheckQuad1->setPoint3(Pnt2s(6,10));
        CheckboxDisabledCheckQuad1->setPoint4(Pnt2s(3,7));
		CheckboxDisabledCheckQuad1->setColor1(CheckmarkDisabledColor);
		CheckboxDisabledCheckQuad1->setColor2(CheckmarkDisabledColor);
		CheckboxDisabledCheckQuad1->setColor3(CheckmarkDisabledColor);
		CheckboxDisabledCheckQuad1->setColor4(CheckmarkDisabledColor);
		CheckboxDisabledCheckQuad1->setOpacity(1.0);
	endEditCP(CheckboxDisabledCheckQuad1);

	MultiColoredQuadUIDrawObjectPtr CheckboxDisabledCheckQuad2 = MultiColoredQuadUIDrawObject::create();
	beginEditCP(CheckboxDisabledCheckQuad2);
        CheckboxDisabledCheckQuad2->setPoint1(Pnt2s(6,7));
        CheckboxDisabledCheckQuad2->setPoint2(Pnt2s(10,3));
        CheckboxDisabledCheckQuad2->setPoint3(Pnt2s(10,6));
        CheckboxDisabledCheckQuad2->setPoint4(Pnt2s(6,10));
		CheckboxDisabledCheckQuad2->setColor1(CheckmarkDisabledColor);
		CheckboxDisabledCheckQuad2->setColor2(CheckmarkDisabledColor);
		CheckboxDisabledCheckQuad2->setColor3(CheckmarkDisabledColor);
		CheckboxDisabledCheckQuad2->setColor4(CheckmarkDisabledColor);
		CheckboxDisabledCheckQuad2->setOpacity(1.0);
	endEditCP(CheckboxDisabledCheckQuad2);

    //Normal
	beginEditCP(WindowsCheckboxDrawObject);
	   WindowsCheckboxDrawObject->getDrawObjects().addValue(CheckboxBackgroundBorder);
	   WindowsCheckboxDrawObject->getDrawObjects().addValue(CheckboxBackground);
	endEditCP(WindowsCheckboxDrawObject);

    //Normal Selected
	beginEditCP(WindowsSelectedCheckboxDrawObject);
		WindowsSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxBackgroundBorder);
		WindowsSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxBackground);
		WindowsSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxCheckQuad1);
		WindowsSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxCheckQuad2);
	endEditCP(WindowsSelectedCheckboxDrawObject);

    //Active Selected
	beginEditCP(WindowsActiveSelectedCheckboxDrawObject);
	 	WindowsActiveSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxBackgroundBorder);
		WindowsActiveSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxBackground);
		WindowsActiveSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxActiveBackground);
	endEditCP(WindowsActiveSelectedCheckboxDrawObject);

    //Active Non-selected
	beginEditCP(WindowsActiveCheckboxDrawObject);
		WindowsActiveCheckboxDrawObject->getDrawObjects().addValue(CheckboxBackgroundBorder);
		WindowsActiveCheckboxDrawObject->getDrawObjects().addValue(CheckboxBackground);
		WindowsActiveCheckboxDrawObject->getDrawObjects().addValue(CheckboxActiveBackground);
		WindowsActiveCheckboxDrawObject->getDrawObjects().addValue(CheckboxCheckQuad1);
		WindowsActiveCheckboxDrawObject->getDrawObjects().addValue(CheckboxCheckQuad2);
	endEditCP(WindowsActiveCheckboxDrawObject);


    //Rollover Border
	MultiColoredQuadUIDrawObjectPtr RolloverCheckboxBorder = MultiColoredQuadUIDrawObject::create();
	beginEditCP(RolloverCheckboxBorder);
        RolloverCheckboxBorder->setPoint1(Pnt2s(1,1));
        RolloverCheckboxBorder->setPoint2(Pnt2s(12,1));
        RolloverCheckboxBorder->setPoint3(Pnt2s(12,12));
        RolloverCheckboxBorder->setPoint4(Pnt2s(1,12));
		RolloverCheckboxBorder->setColor1(Color4f(1.0,.94,.81,1.0));
		RolloverCheckboxBorder->setColor2(Color4f(.98,.78,.39,1.0));
		RolloverCheckboxBorder->setColor3(Color4f(0.97,0.70,0.19,1.0));
		RolloverCheckboxBorder->setColor4(Color4f(.98,.78,.39,1.0));
		RolloverCheckboxBorder->setOpacity(1.0);
	endEditCP(RolloverCheckboxBorder);

	RectUIDrawObjectPtr RolloverCheckboxBackground = RectUIDrawObject::create();
	beginEditCP(RolloverCheckboxBackground);
		RolloverCheckboxBackground->setTopLeft(Pnt2s(3,3));
		RolloverCheckboxBackground->setBottomRight(Pnt2s(10,10));
		RolloverCheckboxBackground->setColor(Color4f(0.91,.91,.89,1.0));
		RolloverCheckboxBackground->setOpacity(1.0);
	endEditCP(RolloverCheckboxBackground);

    //Rollover Selected
	beginEditCP(WindowsRolloverSelectedCheckboxDrawObject);
		WindowsRolloverSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxBackgroundBorder);
		WindowsRolloverSelectedCheckboxDrawObject->getDrawObjects().addValue(RolloverCheckboxBorder);
		WindowsRolloverSelectedCheckboxDrawObject->getDrawObjects().addValue(RolloverCheckboxBackground);
		WindowsRolloverSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxCheckQuad1);
		WindowsRolloverSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxCheckQuad2);
	endEditCP(WindowsRolloverSelectedCheckboxDrawObject);

    //Rollover Non-selected
	beginEditCP(WindowsRolloverCheckboxDrawObject);
		WindowsRolloverCheckboxDrawObject->getDrawObjects().addValue(CheckboxBackgroundBorder);
		WindowsRolloverCheckboxDrawObject->getDrawObjects().addValue(RolloverCheckboxBorder);
		WindowsRolloverCheckboxDrawObject->getDrawObjects().addValue(RolloverCheckboxBackground);
	endEditCP(WindowsRolloverCheckboxDrawObject);

    //Disabled Selected
	beginEditCP(WindowsDisabledSelectedCheckboxDrawObject);
		WindowsDisabledSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxDisabledBackgroundBorder);
		WindowsDisabledSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxDisabledBackground);
		WindowsDisabledSelectedCheckboxDrawObject->getDrawObjects().addValue(RolloverCheckboxBackground);
		WindowsDisabledSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxDisabledCheckQuad1);
		WindowsDisabledSelectedCheckboxDrawObject->getDrawObjects().addValue(CheckboxDisabledCheckQuad2);
	endEditCP(WindowsDisabledSelectedCheckboxDrawObject);

    //Disabled Non-selected
	beginEditCP(WindowsDisabledCheckboxDrawObject);
		WindowsDisabledCheckboxDrawObject->getDrawObjects().addValue(CheckboxDisabledBackgroundBorder);
		WindowsDisabledCheckboxDrawObject->getDrawObjects().addValue(CheckboxDisabledBackground);
	endEditCP(WindowsDisabledCheckboxDrawObject);

    //Border
	EmptyBorderPtr WindowsCheckboxButtonBorder = EmptyBorder::create();

    //Background
	EmptyUIBackgroundPtr WindowsCheckboxButtonBackground = EmptyUIBackground::create();

	CheckboxButtonPtr WindowsCheckboxButton = CheckboxButton::create();
	beginEditCP(WindowsCheckboxButton);
		WindowsCheckboxButton->setEnabled(true);
		WindowsCheckboxButton->setVisible(true);
		
		WindowsCheckboxButton->setConstraints(NullFC);
		//Sizes
		WindowsCheckboxButton->setMinSize(Vec2s(0,0));
		WindowsCheckboxButton->setMaxSize(Vec2s(32767,32767)); //2^15
		WindowsCheckboxButton->setPreferredSize(Vec2s(75,23));
		WindowsCheckboxButton->setSize(Vec2s(0,0));

        //Draw Objects
		WindowsCheckboxButton->setDrawObject(WindowsCheckboxDrawObject);
		WindowsCheckboxButton->setSelectedDrawObject(WindowsSelectedCheckboxDrawObject);
		WindowsCheckboxButton->setActiveDrawObject(WindowsActiveCheckboxDrawObject);
		WindowsCheckboxButton->setActiveSelectedDrawObject(WindowsActiveSelectedCheckboxDrawObject);
		WindowsCheckboxButton->setRolloverDrawObject(WindowsRolloverCheckboxDrawObject);
		WindowsCheckboxButton->setRolloverSelectedDrawObject(WindowsRolloverSelectedCheckboxDrawObject);
		WindowsCheckboxButton->setDisabledDrawObject(WindowsDisabledCheckboxDrawObject);
		WindowsCheckboxButton->setDisabledSelectedDrawObject(WindowsDisabledSelectedCheckboxDrawObject);

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
	endEditCP(WindowsCheckboxButton);

	CheckboxButton::getClassType().setPrototype(WindowsCheckboxButton);

	//************************** Radio Button Component *****************************
	UIDrawObjectCanvasPtr WindowsRadioDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsSelectedRadioDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsActiveRadioDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsActiveSelectedRadioDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsRolloverRadioDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsRolloverSelectedRadioDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsDisabledRadioDrawObject = UIDrawObjectCanvas::create();
	UIDrawObjectCanvasPtr WindowsDisabledSelectedRadioDrawObject = UIDrawObjectCanvas::create();

    Pnt2s RadioUIDrawObjectsCenter(6,6);
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
		WindowsRadioDrawObject->getDrawObjects().addValue(RadioBackground);
		WindowsRadioDrawObject->getDrawObjects().addValue(RadioBackgroundBorder);
	endEditCP(WindowsRadioDrawObject);

	beginEditCP(WindowsSelectedRadioDrawObject);
		WindowsSelectedRadioDrawObject->getDrawObjects().addValue(RadioBackground);
		WindowsSelectedRadioDrawObject->getDrawObjects().addValue(RadioBackgroundBorder);
		WindowsSelectedRadioDrawObject->getDrawObjects().addValue(RadioSelected);
	endEditCP(WindowsSelectedRadioDrawObject);

	beginEditCP(WindowsActiveRadioDrawObject);
		WindowsActiveRadioDrawObject->getDrawObjects().addValue(RadioActiveBackground);
		WindowsActiveRadioDrawObject->getDrawObjects().addValue(RadioBackgroundBorder);
		WindowsActiveRadioDrawObject->getDrawObjects().addValue(RadioSelected);
	endEditCP(WindowsActiveRadioDrawObject);

	beginEditCP(WindowsActiveSelectedRadioDrawObject);
		WindowsActiveSelectedRadioDrawObject->getDrawObjects().addValue(RadioActiveBackground);
		WindowsActiveSelectedRadioDrawObject->getDrawObjects().addValue(RadioBackgroundBorder);
	endEditCP(WindowsActiveSelectedRadioDrawObject);
    
    //Rollover Not Selected
	beginEditCP(WindowsRolloverRadioDrawObject);
		WindowsRolloverRadioDrawObject->getDrawObjects().addValue(RadioBackground);
		WindowsRolloverRadioDrawObject->getDrawObjects().addValue(RadioBackgroundBorder);
		WindowsRolloverRadioDrawObject->getDrawObjects().addValue(RadioRolloverBorder);
	endEditCP(WindowsRolloverRadioDrawObject);

    //Rollover Selected
	beginEditCP(WindowsRolloverSelectedRadioDrawObject);
		WindowsRolloverSelectedRadioDrawObject->getDrawObjects().addValue(RadioBackground);
		WindowsRolloverSelectedRadioDrawObject->getDrawObjects().addValue(RadioBackgroundBorder);
		WindowsRolloverSelectedRadioDrawObject->getDrawObjects().addValue(RadioRolloverBorder);
		WindowsRolloverSelectedRadioDrawObject->getDrawObjects().addValue(RadioSelected);
	endEditCP(WindowsRolloverSelectedRadioDrawObject);
    
    //Disabled Not Selected
	beginEditCP(WindowsDisabledRadioDrawObject);
		WindowsDisabledRadioDrawObject->getDrawObjects().addValue(RadioDisabledBackground);
		WindowsDisabledRadioDrawObject->getDrawObjects().addValue(RadioDisabledBackgroundBorder);
	endEditCP(WindowsDisabledRadioDrawObject);

    //Disabled Selected
	beginEditCP(WindowsDisabledSelectedRadioDrawObject);
		WindowsDisabledSelectedRadioDrawObject->getDrawObjects().addValue(RadioDisabledBackground);
		WindowsDisabledSelectedRadioDrawObject->getDrawObjects().addValue(RadioDisabledBackgroundBorder);
		WindowsDisabledSelectedRadioDrawObject->getDrawObjects().addValue(RadioDisabledSelected);
	endEditCP(WindowsDisabledSelectedRadioDrawObject);
		
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
		WindowsRadioButton->setPreferredSize(Vec2s(75,23));

		//draw objects
		WindowsRadioButton->setDrawObject(WindowsRadioDrawObject);
		WindowsRadioButton->setSelectedDrawObject(WindowsSelectedRadioDrawObject);
		WindowsRadioButton->setActiveDrawObject(WindowsActiveRadioDrawObject);
		WindowsRadioButton->setActiveSelectedDrawObject(WindowsActiveSelectedRadioDrawObject);
		WindowsRadioButton->setRolloverDrawObject(WindowsRolloverRadioDrawObject);
		WindowsRadioButton->setRolloverSelectedDrawObject(WindowsRolloverSelectedRadioDrawObject);
		WindowsRadioButton->setDisabledDrawObject(WindowsDisabledRadioDrawObject);
		WindowsRadioButton->setDisabledSelectedDrawObject(WindowsDisabledSelectedRadioDrawObject);

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
		WindowsToggleButton->setPreferredSize(Vec2s(75,23));

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
		WindowsTextField->setPreferredSize(Vec2s(75,23));

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
		WindowsTextField->setDisabledBackground(WindowsDisabledTextFieldBackground);

		//Border
		WindowsTextField->setBorder(WindowsTextFieldBorder);
		WindowsTextField->setDisabledBorder(WindowsTextFieldBorder);

	endEditCP(WindowsTextField);

	TextField::getClassType().setPrototype(WindowsTextField);
    
    
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


	PasswordFieldPtr WindowsPasswordField = PasswordField::create();
	beginEditCP(WindowsPasswordField);
		//size
		WindowsPasswordField->setMinSize(Vec2s(0, 0));
		WindowsPasswordField->setMaxSize(Vec2s(32767,32767));
		WindowsPasswordField->setPreferredSize(Vec2s(75,23));

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
		WindowsPasswordField->setDisabledBackground(WindowsDisabledPasswordFieldBackground);

		//Border
		WindowsPasswordField->setBorder(WindowsPasswordFieldBorder);
		WindowsPasswordField->setDisabledBorder(WindowsPasswordFieldBorder);

	endEditCP(WindowsPasswordField);

	PasswordField::getClassType().setPrototype(WindowsPasswordField);

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

	TextAreaPtr WindowsTextArea = TextArea::create();
	beginEditCP(WindowsTextArea);
		//size
		WindowsTextArea->setMinSize(Vec2s(0, 0));
		WindowsTextArea->setMaxSize(Vec2s(32767,32767));
		WindowsTextArea->setPreferredSize(Vec2s(100, 25));

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
		WindowsTextArea->setDisabledBackground(WindowsDisabledTextAreaBackground);

		//Border
		WindowsTextArea->setBorder(WindowsTextAreaBorder);
		WindowsTextArea->setDisabledBorder(WindowsTextAreaBorder);

	endEditCP(WindowsTextArea);

	TextArea::getClassType().setPrototype(WindowsTextArea);

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
	ToolTipPtr WindowsToolTip = ToolTip::create();
	beginEditCP(WindowsToolTip);
		WindowsToolTip->setEnabled(true);
		WindowsToolTip->setVisible(true);
		
		WindowsToolTip->setConstraints(NullFC);
		//Sizes
		WindowsToolTip->setMinSize(Vec2s(0,0));
		WindowsToolTip->setMaxSize(Vec2s(32767,32767)); //2^15
		WindowsToolTip->setPreferredSize(Vec2s(75,23));

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
	
    ToolTip::getClassType().setPrototype(WindowsToolTip);

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
		getPrototypes().addValue(WindowsSplitPanel);
		getPrototypes().addValue(WindowsImageComponent);
		getPrototypes().addValue(WindowsCheckboxButton);
		getPrototypes().addValue(WindowsRadioButton);
		getPrototypes().addValue(WindowsToggleButton);
		getPrototypes().addValue(WindowsTextField);
		getPrototypes().addValue(WindowsPasswordField);
		getPrototypes().addValue(WindowsToolTip);
	endEditCP(WindowsLookAndFeelPtr(this), WindowsLookAndFeel::PrototypesFieldMask);






}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

WindowsLookAndFeel::WindowsLookAndFeel(void) :
    Inherited(),
		_TextCaretRate(1.0),
		_ToolTipPopupTime(1.5),
		_SubMenuPopupTime(0.25)
{
}

WindowsLookAndFeel::WindowsLookAndFeel(const WindowsLookAndFeel &source) :
    Inherited(source),
		_TextCaretRate(source._TextCaretRate),
		_ToolTipPopupTime(source._ToolTipPopupTime),
		_SubMenuPopupTime(source._SubMenuPopupTime)
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

