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
#include "Component/Container/OSGFrame.h"
#include "Component/Container/OSGPanel.h"
#include "Component/Container/OSGSplitPanel.h"
#include "Component/Misc/OSGImageComponent.h"
#include "Util/OSGUIDefines.h"
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

#include "Component/Menu/OSGLabelMenuItem.h"
#include "Component/Menu/OSGMenu.h"
#include "Component/Menu/OSGSeperatorMenuItem.h"
#include "Component/Menu/OSGPopupMenu.h"
#include "Component/Menu/OSGMenuBar.h"

#include "Component/Misc/OSGRotatedComponent.h"

#include "Component/Scroll/OSGScrollBar.h"
#include "Component/Scroll/OSGScrollPanel.h"
#include "Component/Container/OSGUIViewport.h"

#include "Component/Table/OSGTableHeader.h"
#include "Component/Table/OSGTable.h"
#include "Component/Table/DefaultRenderers/OSGDefaultTableCellRenderers.h"

#include "Component/List/OSGList.h"
#include "Component/List/OSGDefaultListSelectionModel.h"
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

Time WindowsLookAndFeel::getKeyAcceleratorMenuFlashTime(void) const
{
	return _KeyAcceleratorMenuFlashTime;
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
        
        WindowsButton->setActiveOffset(Vec2s(2,2));
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
        
        WindowsCheckboxButton->setActiveOffset(Vec2s(0,0));
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

        WindowsRadioButton->setActiveOffset(Vec2s(0,0));
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
        
        WindowsToggleButton->setActiveOffset(Vec2s(2,2));
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

		WindowsTextField->setHorizontalAlignment(0.0);
		WindowsTextField->setVerticalAlignment(0.5);
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

	//************************** LabelMenuItem*****************************
	//Windows LabelMenuItemBorder
	EmptyBorderPtr WindowsLabelMenuItemBorder = EmptyBorder::create();

	//Windows LabelMenuItemBackground
	ColorUIBackgroundPtr WindowsLabelMenuItemBackground = ColorUIBackground::create();
	beginEditCP(WindowsLabelMenuItemBackground);
		WindowsLabelMenuItemBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
	endEditCP(WindowsLabelMenuItemBackground);
	
	//Windows LabelMenuItemBorder
	EmptyBorderPtr WindowsLabelMenuItemSelectedBorder = EmptyBorder::create();

	//Windows LabelMenuItemBackground
	ColorUIBackgroundPtr WindowsLabelMenuItemSelectedBackground = ColorUIBackground::create();
	beginEditCP(WindowsLabelMenuItemSelectedBackground);
		WindowsLabelMenuItemSelectedBackground->setColor(Color4f(0.19,0.42,0.77,1.0));
	endEditCP(WindowsLabelMenuItemSelectedBackground);

	//Windows LabelMenuItem
	LabelMenuItemPtr WindowsLabelMenuItem = LabelMenuItem::create();
	beginEditCP(WindowsLabelMenuItem);
		WindowsLabelMenuItem->setEnabled(true);
		WindowsLabelMenuItem->setVisible(true);
		
		WindowsLabelMenuItem->setConstraints(NullFC);
		//Sizes
		WindowsLabelMenuItem->setMinSize(Vec2s(0,0));
		WindowsLabelMenuItem->setMaxSize(Vec2s(32767,32767)); //2^15
		WindowsLabelMenuItem->setPreferredSize(Vec2s(100,17));

		//Border
		WindowsLabelMenuItem->setBorder(WindowsLabelMenuItemBorder);
		
		//Background
		WindowsLabelMenuItem->setBackground(WindowsLabelMenuItemBackground);
		
		//Opacity
		WindowsLabelMenuItem->setOpacity(1.0);

        //Accelerators
        WindowsLabelMenuItem->setAcceleratorModifiers(0);
        WindowsLabelMenuItem->setAcceleratorKey(KeyEvent::KEY_NONE);

        //Selected
        WindowsLabelMenuItem->setSelected(false);
        WindowsLabelMenuItem->setSelectedBorder(WindowsLabelMenuItemSelectedBorder);
        WindowsLabelMenuItem->setSelectedBackground(WindowsLabelMenuItemSelectedBackground);
        
		//Text
		WindowsLabelMenuItem->setText("");
		WindowsLabelMenuItem->setFont(WindowsFont);
		WindowsLabelMenuItem->setTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsLabelMenuItem->setFocusedTextColor(Color4f(0.0,0.0,0.0,1.0));
		WindowsLabelMenuItem->setSelectedTextColor(Color4f(1.0,1.0,1.0,1.0));
		WindowsLabelMenuItem->setRolloverTextColor(Color4f(1.0,1.0,1.0,1.0));
		WindowsLabelMenuItem->setDisabledTextColor(Color4f(0.4,0.4,0.4,1.0));
	endEditCP(WindowsLabelMenuItem);
	
    LabelMenuItem::getClassType().setPrototype(WindowsLabelMenuItem);
    
	//************************** SeperatorMenuItem*****************************
	//Windows SeperatorMenuItemBorder
	EmptyBorderPtr WindowsSeperatorMenuItemBorder = EmptyBorder::create();

	//Windows SeperatorMenuItemBackground
	EmptyUIBackgroundPtr WindowsSeperatorMenuItemBackground = EmptyUIBackground::create();

	//Windows SeperatorMenuItem
	SeperatorMenuItemPtr WindowsSeperatorMenuItem = SeperatorMenuItem::create();
	beginEditCP(WindowsSeperatorMenuItem);
		WindowsSeperatorMenuItem->setEnabled(true);
		WindowsSeperatorMenuItem->setVisible(true);
		
		WindowsSeperatorMenuItem->setConstraints(NullFC);
		//Sizes
		WindowsSeperatorMenuItem->setMinSize(Vec2s(0,0));
		WindowsSeperatorMenuItem->setMaxSize(Vec2s(32767,32767)); //2^15
		WindowsSeperatorMenuItem->setPreferredSize(Vec2s(100,7));

		//Border
		WindowsSeperatorMenuItem->setBorder(WindowsSeperatorMenuItemBorder);
		
		//Background
		WindowsSeperatorMenuItem->setBackground(WindowsSeperatorMenuItemBackground);
		
		//Opacity
		WindowsSeperatorMenuItem->setOpacity(1.0);

        //Seperator Color
        WindowsSeperatorMenuItem->setColor(Color4f(0.67,0.66,0.6,1.0));

	endEditCP(WindowsSeperatorMenuItem);
	
    SeperatorMenuItem::getClassType().setPrototype(WindowsSeperatorMenuItem);
    
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
        MenuExpandablePolygon->getVerticies().addValue(Pnt2s(0,0));
        MenuExpandablePolygon->getVerticies().addValue(Pnt2s(0,7));
        MenuExpandablePolygon->getVerticies().addValue(Pnt2s(4,4));
	endEditCP(MenuExpandablePolygon);

	UIDrawObjectCanvasPtr defaultMenuDrawObject = UIDrawObjectCanvas::create();
	beginEditCP(defaultMenuDrawObject);
	   defaultMenuDrawObject->getDrawObjects().addValue(MenuExpandablePolygon);
	endEditCP(defaultMenuDrawObject);

	//Windows Menu
	MenuPtr WindowsMenu = Menu::create();
	beginEditCP(WindowsMenu);
		WindowsMenu->setEnabled(true);
		WindowsMenu->setVisible(true);
		
		WindowsMenu->setConstraints(NullFC);
		//Sizes
		WindowsMenu->setMinSize(Vec2s(0,0));
		WindowsMenu->setMaxSize(Vec2s(32767,32767)); //2^15
		WindowsMenu->setPreferredSize(Vec2s(100,17));

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

        //Expanding Draw Object
        WindowsMenu->setExpandDrawObject(defaultMenuDrawObject);
	endEditCP(WindowsMenu);
	
    Menu::getClassType().setPrototype(WindowsMenu);
    
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

	//Windows PopupMenu
	PopupMenuPtr WindowsPopupMenu = PopupMenu::create();
	beginEditCP(WindowsPopupMenu);
		WindowsPopupMenu->setEnabled(true);
		WindowsPopupMenu->setVisible(false);
		
		WindowsPopupMenu->setConstraints(NullFC);
		//Sizes
		WindowsPopupMenu->setMinSize(Vec2s(0,0));
		WindowsPopupMenu->setMaxSize(Vec2s(32767,32767)); //2^15
		WindowsPopupMenu->setPreferredSize(Vec2s(100,50));

		//Border
		WindowsPopupMenu->setBorder(WindowsPopupMenuBorder);
		
		//Background
		WindowsPopupMenu->setBackground(WindowsPopupMenuBackground);
		
		//Opacity
		WindowsPopupMenu->setOpacity(1.0);

        //SubMenu delay in seconds
        WindowsPopupMenu->setSubMenuDelay(getSubMenuPopupTime());

        //Insets
        WindowsPopupMenu->setAllInsets(2);
	endEditCP(WindowsPopupMenu);
	
    PopupMenu::getClassType().setPrototype(WindowsPopupMenu);
    
	//************************** MenuBar*****************************
	//Windows MenuBarBorder
	EmptyBorderPtr WindowsMenuBarBorder = EmptyBorder::create();

	//Windows MenuBarBackground
	ColorUIBackgroundPtr WindowsMenuBarBackground = ColorUIBackground::create();
	beginEditCP(WindowsMenuBarBackground);
		WindowsMenuBarBackground->setColor(Color4f(0.93,0.93,0.93,1.0));
	endEditCP(WindowsMenuBarBackground);

	//Windows MenuBar
	MenuBarPtr WindowsMenuBar = MenuBar::create();
	beginEditCP(WindowsMenuBar);
		WindowsMenuBar->setEnabled(true);
		WindowsMenuBar->setVisible(true);
		
		WindowsMenuBar->setConstraints(NullFC);
		//Sizes
		WindowsMenuBar->setMinSize(Vec2s(0,0));
		WindowsMenuBar->setMaxSize(Vec2s(32767,32767)); //2^15
		WindowsMenuBar->setPreferredSize(Vec2s(100,50));

		//Border
		WindowsMenuBar->setBorder(WindowsMenuBarBorder);
		
		//Background
		WindowsMenuBar->setBackground(WindowsMenuBarBackground);
		
		//Opacity
		WindowsMenuBar->setOpacity(1.0);

        //SubMenu delay in seconds
        WindowsMenuBar->setMenuDelay(getSubMenuPopupTime());
	endEditCP(WindowsMenuBar);
	
    MenuBar::getClassType().setPrototype(WindowsMenuBar);
    
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

    //Vertical Min Draw Object
	PolygonUIDrawObjectPtr WindowsScrollBarVerticalMinButtonDrawObject1 = PolygonUIDrawObject::create();
	beginEditCP(WindowsScrollBarVerticalMinButtonDrawObject1);
		WindowsScrollBarVerticalMinButtonDrawObject1->setColor(Color4f(0.3,0.38,0.52,1.0));
		WindowsScrollBarVerticalMinButtonDrawObject1->setOpacity(1.0);
        WindowsScrollBarVerticalMinButtonDrawObject1->getVerticies().addValue(Pnt2s(1,4));
        WindowsScrollBarVerticalMinButtonDrawObject1->getVerticies().addValue(Pnt2s(5,0));
        WindowsScrollBarVerticalMinButtonDrawObject1->getVerticies().addValue(Pnt2s(5,2));
        WindowsScrollBarVerticalMinButtonDrawObject1->getVerticies().addValue(Pnt2s(2,5));
	endEditCP(WindowsScrollBarVerticalMinButtonDrawObject1);
	PolygonUIDrawObjectPtr WindowsScrollBarVerticalMinButtonDrawObject2 = PolygonUIDrawObject::create();
	beginEditCP(WindowsScrollBarVerticalMinButtonDrawObject2);
		WindowsScrollBarVerticalMinButtonDrawObject2->setColor(Color4f(0.3,0.38,0.52,1.0));
		WindowsScrollBarVerticalMinButtonDrawObject2->setOpacity(1.0);
        WindowsScrollBarVerticalMinButtonDrawObject2->getVerticies().addValue(Pnt2s(5,0));
        WindowsScrollBarVerticalMinButtonDrawObject2->getVerticies().addValue(Pnt2s(9,4));
        WindowsScrollBarVerticalMinButtonDrawObject2->getVerticies().addValue(Pnt2s(8,5));
        WindowsScrollBarVerticalMinButtonDrawObject2->getVerticies().addValue(Pnt2s(5,2));
	endEditCP(WindowsScrollBarVerticalMinButtonDrawObject2);

	UIDrawObjectCanvasPtr WindowsScrollBarVerticalMinButtonCanvas = UIDrawObjectCanvas::create();
	beginEditCP(WindowsScrollBarVerticalMinButtonCanvas);
	   WindowsScrollBarVerticalMinButtonCanvas->getDrawObjects().addValue(WindowsScrollBarVerticalMinButtonDrawObject1);
	   WindowsScrollBarVerticalMinButtonCanvas->getDrawObjects().addValue(WindowsScrollBarVerticalMinButtonDrawObject2);
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
        WindowsScrollBarVerticalMinButton->setPreferredSize(Vec2s(17,17));
        WindowsScrollBarVerticalMinButton->setEnableActionOnMouseDownTime(true);
        WindowsScrollBarVerticalMinButton->setActionOnMouseDownRate(0.1);

        WindowsScrollBarVerticalMinButton->setDrawObject(WindowsScrollBarVerticalMinButtonCanvas);
        WindowsScrollBarVerticalMinButton->setActiveDrawObject(WindowsScrollBarVerticalMinButtonCanvas);
        WindowsScrollBarVerticalMinButton->setFocusedDrawObject(WindowsScrollBarVerticalMinButtonCanvas);
        WindowsScrollBarVerticalMinButton->setRolloverDrawObject(WindowsScrollBarVerticalMinButtonCanvas);
        WindowsScrollBarVerticalMinButton->setDisabledDrawObject(WindowsScrollBarVerticalMinButtonCanvas);

        WindowsScrollBarVerticalMinButton->setBorder(WindowsScrollBarButtonBorder);
        WindowsScrollBarVerticalMinButton->setActiveBorder(WindowsScrollBarButtonBorder);
        WindowsScrollBarVerticalMinButton->setDisabledBorder(WindowsScrollBarButtonBorder);
        WindowsScrollBarVerticalMinButton->setFocusedBorder(WindowsScrollBarButtonBorder);
        WindowsScrollBarVerticalMinButton->setRolloverBorder(WindowsScrollBarButtonBorder);
        
        WindowsScrollBarVerticalMinButton->setBackground(WindowsScrollBarButtonBackground);
        WindowsScrollBarVerticalMinButton->setActiveBackground(WindowsScrollBarActiveButtonBackground);
        WindowsScrollBarVerticalMinButton->setDisabledBackground(WindowsScrollBarDisabledButtonBackground);
        WindowsScrollBarVerticalMinButton->setFocusedBackground(WindowsScrollBarButtonBackground);
        WindowsScrollBarVerticalMinButton->setRolloverBackground(WindowsScrollBarRolloverButtonBackground);

        WindowsScrollBarVerticalMinButton->setActiveOffset(Vec2s(0,0));
    endEditCP(WindowsScrollBarVerticalMinButton);

    //Vertical Max Draw Object
	PolygonUIDrawObjectPtr WindowsScrollBarVerticalMaxButtonDrawObject1 = PolygonUIDrawObject::create();
	beginEditCP(WindowsScrollBarVerticalMaxButtonDrawObject1);
		WindowsScrollBarVerticalMaxButtonDrawObject1->setColor(Color4f(0.3,0.38,0.52,1.0));
		WindowsScrollBarVerticalMaxButtonDrawObject1->setOpacity(1.0);
        WindowsScrollBarVerticalMaxButtonDrawObject1->getVerticies().addValue(Pnt2s(2,0));
        WindowsScrollBarVerticalMaxButtonDrawObject1->getVerticies().addValue(Pnt2s(5,3));
        WindowsScrollBarVerticalMaxButtonDrawObject1->getVerticies().addValue(Pnt2s(5,5));
        WindowsScrollBarVerticalMaxButtonDrawObject1->getVerticies().addValue(Pnt2s(1,1));
	endEditCP(WindowsScrollBarVerticalMaxButtonDrawObject1);
	PolygonUIDrawObjectPtr WindowsScrollBarVerticalMaxButtonDrawObject2 = PolygonUIDrawObject::create();
	beginEditCP(WindowsScrollBarVerticalMaxButtonDrawObject2);
		WindowsScrollBarVerticalMaxButtonDrawObject2->setColor(Color4f(0.3,0.38,0.52,1.0));
		WindowsScrollBarVerticalMaxButtonDrawObject2->setOpacity(1.0);
        WindowsScrollBarVerticalMaxButtonDrawObject2->getVerticies().addValue(Pnt2s(5,3));
        WindowsScrollBarVerticalMaxButtonDrawObject2->getVerticies().addValue(Pnt2s(8,0));
        WindowsScrollBarVerticalMaxButtonDrawObject2->getVerticies().addValue(Pnt2s(9,1));
        WindowsScrollBarVerticalMaxButtonDrawObject2->getVerticies().addValue(Pnt2s(5,5));
	endEditCP(WindowsScrollBarVerticalMaxButtonDrawObject2);

	UIDrawObjectCanvasPtr WindowsScrollBarVerticalMaxButtonCanvas = UIDrawObjectCanvas::create();
	beginEditCP(WindowsScrollBarVerticalMaxButtonCanvas);
	   WindowsScrollBarVerticalMaxButtonCanvas->getDrawObjects().addValue(WindowsScrollBarVerticalMaxButtonDrawObject1);
	   WindowsScrollBarVerticalMaxButtonCanvas->getDrawObjects().addValue(WindowsScrollBarVerticalMaxButtonDrawObject2);
	endEditCP(WindowsScrollBarVerticalMaxButtonCanvas);
    //Vertical Max Button
	ButtonPtr WindowsScrollBarVerticalMaxButton = Button::create();
    beginEditCP(WindowsScrollBarVerticalMaxButton);
        WindowsScrollBarVerticalMaxButton->setPreferredSize(Vec2s(17,17));
        WindowsScrollBarVerticalMaxButton->setEnableActionOnMouseDownTime(true);
        WindowsScrollBarVerticalMaxButton->setActionOnMouseDownRate(0.1);
        
        WindowsScrollBarVerticalMaxButton->setDrawObject(WindowsScrollBarVerticalMaxButtonCanvas);
        WindowsScrollBarVerticalMaxButton->setActiveDrawObject(WindowsScrollBarVerticalMaxButtonCanvas);
        WindowsScrollBarVerticalMaxButton->setFocusedDrawObject(WindowsScrollBarVerticalMaxButtonCanvas);
        WindowsScrollBarVerticalMaxButton->setRolloverDrawObject(WindowsScrollBarVerticalMaxButtonCanvas);
        WindowsScrollBarVerticalMaxButton->setDisabledDrawObject(WindowsScrollBarVerticalMaxButtonCanvas);
        
        WindowsScrollBarVerticalMaxButton->setBorder(WindowsScrollBarButtonBorder);
        WindowsScrollBarVerticalMaxButton->setActiveBorder(WindowsScrollBarButtonBorder);
        WindowsScrollBarVerticalMaxButton->setDisabledBorder(WindowsScrollBarButtonBorder);
        WindowsScrollBarVerticalMaxButton->setFocusedBorder(WindowsScrollBarButtonBorder);
        WindowsScrollBarVerticalMaxButton->setRolloverBorder(WindowsScrollBarButtonBorder);
        
        WindowsScrollBarVerticalMaxButton->setBackground(WindowsScrollBarButtonBackground);
        WindowsScrollBarVerticalMaxButton->setActiveBackground(WindowsScrollBarActiveButtonBackground);
        WindowsScrollBarVerticalMaxButton->setDisabledBackground(WindowsScrollBarDisabledButtonBackground);
        WindowsScrollBarVerticalMaxButton->setFocusedBackground(WindowsScrollBarButtonBackground);
        WindowsScrollBarVerticalMaxButton->setRolloverBackground(WindowsScrollBarRolloverButtonBackground);

        WindowsScrollBarVerticalMaxButton->setActiveOffset(Vec2s(0,0));
    endEditCP(WindowsScrollBarVerticalMaxButton);

    //Horizontal Min Draw Object
	PolygonUIDrawObjectPtr WindowsScrollBarHorizontalMinButtonDrawObject1 = PolygonUIDrawObject::create();
	beginEditCP(WindowsScrollBarHorizontalMinButtonDrawObject1);
		WindowsScrollBarHorizontalMinButtonDrawObject1->setColor(Color4f(0.3,0.38,0.52,1.0));
		WindowsScrollBarHorizontalMinButtonDrawObject1->setOpacity(1.0);
        WindowsScrollBarHorizontalMinButtonDrawObject1->getVerticies().addValue(Pnt2s(0,4));
        WindowsScrollBarHorizontalMinButtonDrawObject1->getVerticies().addValue(Pnt2s(4,0));
        WindowsScrollBarHorizontalMinButtonDrawObject1->getVerticies().addValue(Pnt2s(5,1));
        WindowsScrollBarHorizontalMinButtonDrawObject1->getVerticies().addValue(Pnt2s(2,4));
	endEditCP(WindowsScrollBarHorizontalMinButtonDrawObject1);
	PolygonUIDrawObjectPtr WindowsScrollBarHorizontalMinButtonDrawObject2 = PolygonUIDrawObject::create();
	beginEditCP(WindowsScrollBarHorizontalMinButtonDrawObject2);
		WindowsScrollBarHorizontalMinButtonDrawObject2->setColor(Color4f(0.3,0.38,0.52,1.0));
		WindowsScrollBarHorizontalMinButtonDrawObject2->setOpacity(1.0);
        WindowsScrollBarHorizontalMinButtonDrawObject2->getVerticies().addValue(Pnt2s(0,4));
        WindowsScrollBarHorizontalMinButtonDrawObject2->getVerticies().addValue(Pnt2s(2,4));
        WindowsScrollBarHorizontalMinButtonDrawObject2->getVerticies().addValue(Pnt2s(5,7));
        WindowsScrollBarHorizontalMinButtonDrawObject2->getVerticies().addValue(Pnt2s(4,8));
	endEditCP(WindowsScrollBarHorizontalMinButtonDrawObject2);
    
	UIDrawObjectCanvasPtr WindowsScrollBarHorizontalMinButtonCanvas = UIDrawObjectCanvas::create();
	beginEditCP(WindowsScrollBarHorizontalMinButtonCanvas);
	   WindowsScrollBarHorizontalMinButtonCanvas->getDrawObjects().addValue(WindowsScrollBarHorizontalMinButtonDrawObject1);
	   WindowsScrollBarHorizontalMinButtonCanvas->getDrawObjects().addValue(WindowsScrollBarHorizontalMinButtonDrawObject2);
	endEditCP(WindowsScrollBarHorizontalMinButtonCanvas);

    //Horizontal Min Button
	ButtonPtr WindowsScrollBarHorizontalMinButton = Button::create();
    beginEditCP(WindowsScrollBarHorizontalMinButton);
        WindowsScrollBarHorizontalMinButton->setPreferredSize(Vec2s(17,17));
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

        WindowsScrollBarHorizontalMinButton->setActiveOffset(Vec2s(0,0));
    endEditCP(WindowsScrollBarHorizontalMinButton);

    //Horizontal Max Draw Object
	PolygonUIDrawObjectPtr WindowsScrollBarHorizontalMaxButtonDrawObject1 = PolygonUIDrawObject::create();
	beginEditCP(WindowsScrollBarHorizontalMaxButtonDrawObject1);
		WindowsScrollBarHorizontalMaxButtonDrawObject1->setColor(Color4f(0.3,0.38,0.52,1.0));
		WindowsScrollBarHorizontalMaxButtonDrawObject1->setOpacity(1.0);
        WindowsScrollBarHorizontalMaxButtonDrawObject1->getVerticies().addValue(Pnt2s(0,1));
        WindowsScrollBarHorizontalMaxButtonDrawObject1->getVerticies().addValue(Pnt2s(1,0));
        WindowsScrollBarHorizontalMaxButtonDrawObject1->getVerticies().addValue(Pnt2s(5,4));
        WindowsScrollBarHorizontalMaxButtonDrawObject1->getVerticies().addValue(Pnt2s(3,4));
	endEditCP(WindowsScrollBarHorizontalMaxButtonDrawObject1);
	PolygonUIDrawObjectPtr WindowsScrollBarHorizontalMaxButtonDrawObject2 = PolygonUIDrawObject::create();
	beginEditCP(WindowsScrollBarHorizontalMaxButtonDrawObject2);
		WindowsScrollBarHorizontalMaxButtonDrawObject2->setColor(Color4f(0.3,0.38,0.52,1.0));
		WindowsScrollBarHorizontalMaxButtonDrawObject2->setOpacity(1.0);
        WindowsScrollBarHorizontalMaxButtonDrawObject2->getVerticies().addValue(Pnt2s(3,4));
        WindowsScrollBarHorizontalMaxButtonDrawObject2->getVerticies().addValue(Pnt2s(5,4));
        WindowsScrollBarHorizontalMaxButtonDrawObject2->getVerticies().addValue(Pnt2s(1,8));
        WindowsScrollBarHorizontalMaxButtonDrawObject2->getVerticies().addValue(Pnt2s(0,7));
	endEditCP(WindowsScrollBarHorizontalMaxButtonDrawObject2);
    
	UIDrawObjectCanvasPtr WindowsScrollBarHorizontalMaxButtonCanvas = UIDrawObjectCanvas::create();
	beginEditCP(WindowsScrollBarHorizontalMaxButtonCanvas);
	   WindowsScrollBarHorizontalMaxButtonCanvas->getDrawObjects().addValue(WindowsScrollBarHorizontalMaxButtonDrawObject1);
	   WindowsScrollBarHorizontalMaxButtonCanvas->getDrawObjects().addValue(WindowsScrollBarHorizontalMaxButtonDrawObject2);
	endEditCP(WindowsScrollBarHorizontalMaxButtonCanvas);
    //Horizontal Max Button
	ButtonPtr WindowsScrollBarHorizontalMaxButton = Button::create();
    beginEditCP(WindowsScrollBarHorizontalMaxButton);
        WindowsScrollBarHorizontalMaxButton->setPreferredSize(Vec2s(17,17));
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

        WindowsScrollBarHorizontalMaxButton->setActiveOffset(Vec2s(0,0));
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
		WindowsVerticalScrollFieldBackground->setAlignment(HORIZONTAL_ALIGNMENT);
	endEditCP(WindowsVerticalScrollFieldBackground);
	
	//Vertical Scroll Field Disabled Background
	ColorUIBackgroundPtr WindowsVerticalDisabledScrollFieldBackground = ColorUIBackground::create();
	beginEditCP(WindowsVerticalDisabledScrollFieldBackground);
		WindowsVerticalDisabledScrollFieldBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
	endEditCP(WindowsVerticalDisabledScrollFieldBackground);

	ButtonPtr WindowsVerticalScrollFieldButton = Button::create();
    beginEditCP(WindowsVerticalScrollFieldButton, Button::PreferredSizeFieldMask | Button::EnableActionOnMouseDownTimeFieldMask | Button::ActionOnMouseDownRateFieldMask);
        WindowsVerticalScrollFieldButton->setPreferredSize(Vec2s(17,17));
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
		WindowsVerticalScrollBarDrawObjectBackground->setAlignment(HORIZONTAL_ALIGNMENT);
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
		WindowsRolloverVerticalScrollBarDrawObjectBackground->setAlignment(HORIZONTAL_ALIGNMENT);
	endEditCP(WindowsRolloverVerticalScrollBarDrawObjectBackground);

	//Vertical Scroll Bar Active Background
	GradientUIBackgroundPtr WindowsActiveVerticalScrollBarDrawObjectBackground = GradientUIBackground::create();
	beginEditCP(WindowsActiveVerticalScrollBarDrawObjectBackground);
		WindowsActiveVerticalScrollBarDrawObjectBackground->setColorStart(Color4f(0.84,0.91,1.0,1.0));
		WindowsActiveVerticalScrollBarDrawObjectBackground->setColorEnd(Color4f(0.80,0.88,1.0,1.0));
		WindowsActiveVerticalScrollBarDrawObjectBackground->setAlignment(VERTICAL_ALIGNMENT);
	endEditCP(WindowsActiveVerticalScrollBarDrawObjectBackground);

    //Vertical Scroll Bar Center Ridges
    RectUIDrawObjectPtr VerticalWhiteRidge1 = RectUIDrawObject::create();
	beginEditCP(VerticalWhiteRidge1);
       VerticalWhiteRidge1->setTopLeft(Pnt2s(0,0));
       VerticalWhiteRidge1->setBottomRight(Pnt2s(6,1));
       VerticalWhiteRidge1->setColor(Color4f(0.93,0.96,1.0,1.0));
	endEditCP(VerticalWhiteRidge1);

    RectUIDrawObjectPtr VerticalWhiteRidge2 = RectUIDrawObject::create();
	beginEditCP(VerticalWhiteRidge2);
       VerticalWhiteRidge2->setTopLeft(Pnt2s(0,2));
       VerticalWhiteRidge2->setBottomRight(Pnt2s(6,3));
       VerticalWhiteRidge2->setColor(Color4f(0.93,0.96,1.0,1.0));
	endEditCP(VerticalWhiteRidge2);
    
    RectUIDrawObjectPtr VerticalWhiteRidge3 = RectUIDrawObject::create();
	beginEditCP(VerticalWhiteRidge3);
       VerticalWhiteRidge3->setTopLeft(Pnt2s(0,4));
       VerticalWhiteRidge3->setBottomRight(Pnt2s(6,5));
       VerticalWhiteRidge3->setColor(Color4f(0.93,0.96,1.0,1.0));
	endEditCP(VerticalWhiteRidge3);

    RectUIDrawObjectPtr VerticalWhiteRidge4 = RectUIDrawObject::create();
	beginEditCP(VerticalWhiteRidge4);
       VerticalWhiteRidge4->setTopLeft(Pnt2s(0,6));
       VerticalWhiteRidge4->setBottomRight(Pnt2s(6,7));
       VerticalWhiteRidge4->setColor(Color4f(0.93,0.96,1.0,1.0));
	endEditCP(VerticalWhiteRidge4);
    
    RectUIDrawObjectPtr VerticalBlueRidge1 = RectUIDrawObject::create();
	beginEditCP(VerticalBlueRidge1);
       VerticalBlueRidge1->setTopLeft(Pnt2s(1,1));
       VerticalBlueRidge1->setBottomRight(Pnt2s(7,2));
       VerticalBlueRidge1->setColor(Color4f(0.55,0.69,0.97,1.0));
	endEditCP(VerticalBlueRidge1);

    RectUIDrawObjectPtr VerticalBlueRidge2 = RectUIDrawObject::create();
	beginEditCP(VerticalBlueRidge2);
       VerticalBlueRidge2->setTopLeft(Pnt2s(1,3));
       VerticalBlueRidge2->setBottomRight(Pnt2s(7,4));
       VerticalBlueRidge2->setColor(Color4f(0.55,0.69,0.97,1.0));
	endEditCP(VerticalBlueRidge2);
    
    RectUIDrawObjectPtr VerticalBlueRidge3 = RectUIDrawObject::create();
	beginEditCP(VerticalBlueRidge3);
       VerticalBlueRidge3->setTopLeft(Pnt2s(1,5));
       VerticalBlueRidge3->setBottomRight(Pnt2s(7,6));
       VerticalBlueRidge3->setColor(Color4f(0.55,0.69,0.97,1.0));
	endEditCP(VerticalBlueRidge3);

    RectUIDrawObjectPtr VerticalBlueRidge4 = RectUIDrawObject::create();
	beginEditCP(VerticalBlueRidge4);
       VerticalBlueRidge4->setTopLeft(Pnt2s(1,7));
       VerticalBlueRidge4->setBottomRight(Pnt2s(7,8));
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
       VerticalActiveWhiteRidge1->setTopLeft(Pnt2s(0,0));
       VerticalActiveWhiteRidge1->setBottomRight(Pnt2s(6,1));
       VerticalActiveWhiteRidge1->setColor(Color4f(0.81,0.87,0.99,1.0));
	endEditCP(VerticalActiveWhiteRidge1);

    RectUIDrawObjectPtr VerticalActiveWhiteRidge2 = RectUIDrawObject::create();
	beginEditCP(VerticalActiveWhiteRidge2);
       VerticalActiveWhiteRidge2->setTopLeft(Pnt2s(0,2));
       VerticalActiveWhiteRidge2->setBottomRight(Pnt2s(6,3));
       VerticalActiveWhiteRidge2->setColor(Color4f(0.81,0.87,0.99,1.0));
	endEditCP(VerticalActiveWhiteRidge2);
    
    RectUIDrawObjectPtr VerticalActiveWhiteRidge3 = RectUIDrawObject::create();
	beginEditCP(VerticalActiveWhiteRidge3);
       VerticalActiveWhiteRidge3->setTopLeft(Pnt2s(0,4));
       VerticalActiveWhiteRidge3->setBottomRight(Pnt2s(6,5));
       VerticalActiveWhiteRidge3->setColor(Color4f(0.81,0.87,0.99,1.0));
	endEditCP(VerticalActiveWhiteRidge3);

    RectUIDrawObjectPtr VerticalActiveWhiteRidge4 = RectUIDrawObject::create();
	beginEditCP(VerticalActiveWhiteRidge4);
       VerticalActiveWhiteRidge4->setTopLeft(Pnt2s(0,6));
       VerticalActiveWhiteRidge4->setBottomRight(Pnt2s(6,7));
       VerticalActiveWhiteRidge4->setColor(Color4f(0.81,0.87,0.99,1.0));
	endEditCP(VerticalActiveWhiteRidge4);
    
    RectUIDrawObjectPtr VerticalActiveBlueRidge1 = RectUIDrawObject::create();
	beginEditCP(VerticalActiveBlueRidge1);
       VerticalActiveBlueRidge1->setTopLeft(Pnt2s(1,1));
       VerticalActiveBlueRidge1->setBottomRight(Pnt2s(7,2));
       VerticalActiveBlueRidge1->setColor(Color4f(0.51,0.62,0.85,1.0));
	endEditCP(VerticalActiveBlueRidge1);

    RectUIDrawObjectPtr VerticalActiveBlueRidge2 = RectUIDrawObject::create();
	beginEditCP(VerticalActiveBlueRidge2);
       VerticalActiveBlueRidge2->setTopLeft(Pnt2s(1,3));
       VerticalActiveBlueRidge2->setBottomRight(Pnt2s(7,4));
       VerticalActiveBlueRidge2->setColor(Color4f(0.51,0.62,0.85,1.0));
	endEditCP(VerticalActiveBlueRidge2);
    
    RectUIDrawObjectPtr VerticalActiveBlueRidge3 = RectUIDrawObject::create();
	beginEditCP(VerticalActiveBlueRidge3);
       VerticalActiveBlueRidge3->setTopLeft(Pnt2s(1,5));
       VerticalActiveBlueRidge3->setBottomRight(Pnt2s(7,6));
       VerticalActiveBlueRidge3->setColor(Color4f(0.51,0.62,0.85,1.0));
	endEditCP(VerticalActiveBlueRidge3);

    RectUIDrawObjectPtr VerticalActiveBlueRidge4 = RectUIDrawObject::create();
	beginEditCP(VerticalActiveBlueRidge4);
       VerticalActiveBlueRidge4->setTopLeft(Pnt2s(1,7));
       VerticalActiveBlueRidge4->setBottomRight(Pnt2s(7,8));
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
       VerticalRolloverWhiteRidge1->setTopLeft(Pnt2s(0,0));
       VerticalRolloverWhiteRidge1->setBottomRight(Pnt2s(6,1));
       VerticalRolloverWhiteRidge1->setColor(Color4f(0.99,0.99,1.0,1.0));
	endEditCP(VerticalRolloverWhiteRidge1);

    RectUIDrawObjectPtr VerticalRolloverWhiteRidge2 = RectUIDrawObject::create();
	beginEditCP(VerticalRolloverWhiteRidge2);
       VerticalRolloverWhiteRidge2->setTopLeft(Pnt2s(0,2));
       VerticalRolloverWhiteRidge2->setBottomRight(Pnt2s(6,3));
       VerticalRolloverWhiteRidge2->setColor(Color4f(0.99,0.99,1.0,1.0));
	endEditCP(VerticalRolloverWhiteRidge2);
    
    RectUIDrawObjectPtr VerticalRolloverWhiteRidge3 = RectUIDrawObject::create();
	beginEditCP(VerticalRolloverWhiteRidge3);
       VerticalRolloverWhiteRidge3->setTopLeft(Pnt2s(0,4));
       VerticalRolloverWhiteRidge3->setBottomRight(Pnt2s(6,5));
       VerticalRolloverWhiteRidge3->setColor(Color4f(0.99,0.99,1.0,1.0));
	endEditCP(VerticalRolloverWhiteRidge3);

    RectUIDrawObjectPtr VerticalRolloverWhiteRidge4 = RectUIDrawObject::create();
	beginEditCP(VerticalRolloverWhiteRidge4);
       VerticalRolloverWhiteRidge4->setTopLeft(Pnt2s(0,6));
       VerticalRolloverWhiteRidge4->setBottomRight(Pnt2s(6,7));
       VerticalRolloverWhiteRidge4->setColor(Color4f(0.99,0.99,1.0,1.0));
	endEditCP(VerticalRolloverWhiteRidge4);
    
    RectUIDrawObjectPtr VerticalRolloverBlueRidge1 = RectUIDrawObject::create();
	beginEditCP(VerticalRolloverBlueRidge1);
       VerticalRolloverBlueRidge1->setTopLeft(Pnt2s(1,1));
       VerticalRolloverBlueRidge1->setBottomRight(Pnt2s(7,2));
       VerticalRolloverBlueRidge1->setColor(Color4f(0.61,0.77,1.0,1.0));
	endEditCP(VerticalRolloverBlueRidge1);

    RectUIDrawObjectPtr VerticalRolloverBlueRidge2 = RectUIDrawObject::create();
	beginEditCP(VerticalRolloverBlueRidge2);
       VerticalRolloverBlueRidge2->setTopLeft(Pnt2s(1,3));
       VerticalRolloverBlueRidge2->setBottomRight(Pnt2s(7,4));
       VerticalRolloverBlueRidge2->setColor(Color4f(0.61,0.77,1.0,1.0));
	endEditCP(VerticalRolloverBlueRidge2);
    
    RectUIDrawObjectPtr VerticalRolloverBlueRidge3 = RectUIDrawObject::create();
	beginEditCP(VerticalRolloverBlueRidge3);
       VerticalRolloverBlueRidge3->setTopLeft(Pnt2s(1,5));
       VerticalRolloverBlueRidge3->setBottomRight(Pnt2s(7,6));
       VerticalRolloverBlueRidge3->setColor(Color4f(0.61,0.77,1.0,1.0));
	endEditCP(VerticalRolloverBlueRidge3);

    RectUIDrawObjectPtr VerticalRolloverBlueRidge4 = RectUIDrawObject::create();
	beginEditCP(VerticalRolloverBlueRidge4);
       VerticalRolloverBlueRidge4->setTopLeft(Pnt2s(1,7));
       VerticalRolloverBlueRidge4->setBottomRight(Pnt2s(7,8));
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
        WindowsVerticalScrollBarDrawObject->setActiveOffset(Vec2s(0,0));

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
		WindowsHorizontalScrollFieldBackground->setAlignment(VERTICAL_ALIGNMENT);
	endEditCP(WindowsHorizontalScrollFieldBackground);
	
	//Horizontal Scroll Field Disabled Background
	ColorUIBackgroundPtr WindowsHorizontalDisabledScrollFieldBackground = ColorUIBackground::create();
	beginEditCP(WindowsHorizontalDisabledScrollFieldBackground);
		WindowsHorizontalDisabledScrollFieldBackground->setColor(Color4f(1.0,1.0,1.0,1.0));
	endEditCP(WindowsHorizontalDisabledScrollFieldBackground);

	ButtonPtr WindowsHorizontalScrollFieldButton = Button::create();
    beginEditCP(WindowsHorizontalScrollFieldButton, Button::PreferredSizeFieldMask | Button::EnableActionOnMouseDownTimeFieldMask | Button::ActionOnMouseDownRateFieldMask);
        WindowsHorizontalScrollFieldButton->setPreferredSize(Vec2s(17,17));
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
		WindowsHorizontalScrollBarDrawObjectBackground->setAlignment(VERTICAL_ALIGNMENT);
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
		WindowsRolloverHorizontalScrollBarDrawObjectBackground->setAlignment(VERTICAL_ALIGNMENT);
	endEditCP(WindowsRolloverHorizontalScrollBarDrawObjectBackground);

	//Horizontal Scroll Bar Active Background
	GradientUIBackgroundPtr WindowsActiveHorizontalScrollBarDrawObjectBackground = GradientUIBackground::create();
	beginEditCP(WindowsActiveHorizontalScrollBarDrawObjectBackground);
		WindowsActiveHorizontalScrollBarDrawObjectBackground->setColorStart(Color4f(0.84,0.91,1.0,1.0));
		WindowsActiveHorizontalScrollBarDrawObjectBackground->setColorEnd(Color4f(0.80,0.88,1.0,1.0));
		WindowsActiveHorizontalScrollBarDrawObjectBackground->setAlignment(VERTICAL_ALIGNMENT);
	endEditCP(WindowsActiveHorizontalScrollBarDrawObjectBackground);

    //Horizontal Scroll Bar Center Ridges
    RectUIDrawObjectPtr HorizontalWhiteRidge1 = RectUIDrawObject::create();
	beginEditCP(HorizontalWhiteRidge1);
       HorizontalWhiteRidge1->setTopLeft(Pnt2s(0,0));
       HorizontalWhiteRidge1->setBottomRight(Pnt2s(1,6));
       HorizontalWhiteRidge1->setColor(Color4f(0.93,0.96,1.0,1.0));
	endEditCP(HorizontalWhiteRidge1);

    RectUIDrawObjectPtr HorizontalWhiteRidge2 = RectUIDrawObject::create();
	beginEditCP(HorizontalWhiteRidge2);
       HorizontalWhiteRidge2->setTopLeft(Pnt2s(2,0));
       HorizontalWhiteRidge2->setBottomRight(Pnt2s(3,6));
       HorizontalWhiteRidge2->setColor(Color4f(0.93,0.96,1.0,1.0));
	endEditCP(HorizontalWhiteRidge2);
    
    RectUIDrawObjectPtr HorizontalWhiteRidge3 = RectUIDrawObject::create();
	beginEditCP(HorizontalWhiteRidge3);
       HorizontalWhiteRidge3->setTopLeft(Pnt2s(4,0));
       HorizontalWhiteRidge3->setBottomRight(Pnt2s(5,6));
       HorizontalWhiteRidge3->setColor(Color4f(0.93,0.96,1.0,1.0));
	endEditCP(HorizontalWhiteRidge3);

    RectUIDrawObjectPtr HorizontalWhiteRidge4 = RectUIDrawObject::create();
	beginEditCP(HorizontalWhiteRidge4);
       HorizontalWhiteRidge4->setTopLeft(Pnt2s(6,0));
       HorizontalWhiteRidge4->setBottomRight(Pnt2s(7,6));
       HorizontalWhiteRidge4->setColor(Color4f(0.93,0.96,1.0,1.0));
	endEditCP(HorizontalWhiteRidge4);
    
    RectUIDrawObjectPtr HorizontalBlueRidge1 = RectUIDrawObject::create();
	beginEditCP(HorizontalBlueRidge1);
       HorizontalBlueRidge1->setTopLeft(Pnt2s(1,1));
       HorizontalBlueRidge1->setBottomRight(Pnt2s(2,7));
       HorizontalBlueRidge1->setColor(Color4f(0.55,0.69,0.97,1.0));
	endEditCP(HorizontalBlueRidge1);

    RectUIDrawObjectPtr HorizontalBlueRidge2 = RectUIDrawObject::create();
	beginEditCP(HorizontalBlueRidge2);
       HorizontalBlueRidge2->setTopLeft(Pnt2s(3,1));
       HorizontalBlueRidge2->setBottomRight(Pnt2s(4,7));
       HorizontalBlueRidge2->setColor(Color4f(0.55,0.69,0.97,1.0));
	endEditCP(HorizontalBlueRidge2);
    
    RectUIDrawObjectPtr HorizontalBlueRidge3 = RectUIDrawObject::create();
	beginEditCP(HorizontalBlueRidge3);
       HorizontalBlueRidge3->setTopLeft(Pnt2s(5,1));
       HorizontalBlueRidge3->setBottomRight(Pnt2s(6,7));
       HorizontalBlueRidge3->setColor(Color4f(0.55,0.69,0.97,1.0));
	endEditCP(HorizontalBlueRidge3);

    RectUIDrawObjectPtr HorizontalBlueRidge4 = RectUIDrawObject::create();
	beginEditCP(HorizontalBlueRidge4);
       HorizontalBlueRidge4->setTopLeft(Pnt2s(7,1));
       HorizontalBlueRidge4->setBottomRight(Pnt2s(8,7));
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
       HorizontalActiveWhiteRidge1->setTopLeft(Pnt2s(0,0));
       HorizontalActiveWhiteRidge1->setBottomRight(Pnt2s(1,6));
       HorizontalActiveWhiteRidge1->setColor(Color4f(0.81,0.87,0.99,1.0));
	endEditCP(HorizontalActiveWhiteRidge1);

    RectUIDrawObjectPtr HorizontalActiveWhiteRidge2 = RectUIDrawObject::create();
	beginEditCP(HorizontalActiveWhiteRidge2);
       HorizontalActiveWhiteRidge2->setTopLeft(Pnt2s(2,0));
       HorizontalActiveWhiteRidge2->setBottomRight(Pnt2s(3,6));
       HorizontalActiveWhiteRidge2->setColor(Color4f(0.81,0.87,0.99,1.0));
	endEditCP(HorizontalActiveWhiteRidge2);
    
    RectUIDrawObjectPtr HorizontalActiveWhiteRidge3 = RectUIDrawObject::create();
	beginEditCP(HorizontalActiveWhiteRidge3);
       HorizontalActiveWhiteRidge3->setTopLeft(Pnt2s(4,0));
       HorizontalActiveWhiteRidge3->setBottomRight(Pnt2s(5,6));
       HorizontalActiveWhiteRidge3->setColor(Color4f(0.81,0.87,0.99,1.0));
	endEditCP(HorizontalActiveWhiteRidge3);

    RectUIDrawObjectPtr HorizontalActiveWhiteRidge4 = RectUIDrawObject::create();
	beginEditCP(HorizontalActiveWhiteRidge4);
       HorizontalActiveWhiteRidge4->setTopLeft(Pnt2s(6,0));
       HorizontalActiveWhiteRidge4->setBottomRight(Pnt2s(7,6));
       HorizontalActiveWhiteRidge4->setColor(Color4f(0.81,0.87,0.99,1.0));
	endEditCP(HorizontalActiveWhiteRidge4);
    
    RectUIDrawObjectPtr HorizontalActiveBlueRidge1 = RectUIDrawObject::create();
	beginEditCP(HorizontalActiveBlueRidge1);
       HorizontalActiveBlueRidge1->setTopLeft(Pnt2s(1,1));
       HorizontalActiveBlueRidge1->setBottomRight(Pnt2s(2,7));
       HorizontalActiveBlueRidge1->setColor(Color4f(0.51,0.62,0.85,1.0));
	endEditCP(HorizontalActiveBlueRidge1);

    RectUIDrawObjectPtr HorizontalActiveBlueRidge2 = RectUIDrawObject::create();
	beginEditCP(HorizontalActiveBlueRidge2);
       HorizontalActiveBlueRidge2->setTopLeft(Pnt2s(3,1));
       HorizontalActiveBlueRidge2->setBottomRight(Pnt2s(4,7));
       HorizontalActiveBlueRidge2->setColor(Color4f(0.51,0.62,0.85,1.0));
	endEditCP(HorizontalActiveBlueRidge2);
    
    RectUIDrawObjectPtr HorizontalActiveBlueRidge3 = RectUIDrawObject::create();
	beginEditCP(HorizontalActiveBlueRidge3);
       HorizontalActiveBlueRidge3->setTopLeft(Pnt2s(5,1));
       HorizontalActiveBlueRidge3->setBottomRight(Pnt2s(6,7));
       HorizontalActiveBlueRidge3->setColor(Color4f(0.51,0.62,0.85,1.0));
	endEditCP(HorizontalActiveBlueRidge3);

    RectUIDrawObjectPtr HorizontalActiveBlueRidge4 = RectUIDrawObject::create();
	beginEditCP(HorizontalActiveBlueRidge4);
       HorizontalActiveBlueRidge4->setTopLeft(Pnt2s(7,1));
       HorizontalActiveBlueRidge4->setBottomRight(Pnt2s(8,7));
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
       HorizontalRolloverWhiteRidge1->setTopLeft(Pnt2s(0,0));
       HorizontalRolloverWhiteRidge1->setBottomRight(Pnt2s(1,6));
       HorizontalRolloverWhiteRidge1->setColor(Color4f(0.99,0.99,1.0,1.0));
	endEditCP(HorizontalRolloverWhiteRidge1);

    RectUIDrawObjectPtr HorizontalRolloverWhiteRidge2 = RectUIDrawObject::create();
	beginEditCP(HorizontalRolloverWhiteRidge2);
       HorizontalRolloverWhiteRidge2->setTopLeft(Pnt2s(2,0));
       HorizontalRolloverWhiteRidge2->setBottomRight(Pnt2s(3,6));
       HorizontalRolloverWhiteRidge2->setColor(Color4f(0.99,0.99,1.0,1.0));
	endEditCP(HorizontalRolloverWhiteRidge2);
    
    RectUIDrawObjectPtr HorizontalRolloverWhiteRidge3 = RectUIDrawObject::create();
	beginEditCP(HorizontalRolloverWhiteRidge3);
       HorizontalRolloverWhiteRidge3->setTopLeft(Pnt2s(4,0));
       HorizontalRolloverWhiteRidge3->setBottomRight(Pnt2s(5,6));
       HorizontalRolloverWhiteRidge3->setColor(Color4f(0.99,0.99,1.0,1.0));
	endEditCP(HorizontalRolloverWhiteRidge3);

    RectUIDrawObjectPtr HorizontalRolloverWhiteRidge4 = RectUIDrawObject::create();
	beginEditCP(HorizontalRolloverWhiteRidge4);
       HorizontalRolloverWhiteRidge4->setTopLeft(Pnt2s(6,0));
       HorizontalRolloverWhiteRidge4->setBottomRight(Pnt2s(7,6));
       HorizontalRolloverWhiteRidge4->setColor(Color4f(0.99,0.99,1.0,1.0));
	endEditCP(HorizontalRolloverWhiteRidge4);
    
    RectUIDrawObjectPtr HorizontalRolloverBlueRidge1 = RectUIDrawObject::create();
	beginEditCP(HorizontalRolloverBlueRidge1);
       HorizontalRolloverBlueRidge1->setTopLeft(Pnt2s(1,1));
       HorizontalRolloverBlueRidge1->setBottomRight(Pnt2s(2,7));
       HorizontalRolloverBlueRidge1->setColor(Color4f(0.61,0.77,1.0,1.0));
	endEditCP(HorizontalRolloverBlueRidge1);

    RectUIDrawObjectPtr HorizontalRolloverBlueRidge2 = RectUIDrawObject::create();
	beginEditCP(HorizontalRolloverBlueRidge2);
       HorizontalRolloverBlueRidge2->setTopLeft(Pnt2s(3,1));
       HorizontalRolloverBlueRidge2->setBottomRight(Pnt2s(4,7));
       HorizontalRolloverBlueRidge2->setColor(Color4f(0.61,0.77,1.0,1.0));
	endEditCP(HorizontalRolloverBlueRidge2);
    
    RectUIDrawObjectPtr HorizontalRolloverBlueRidge3 = RectUIDrawObject::create();
	beginEditCP(HorizontalRolloverBlueRidge3);
       HorizontalRolloverBlueRidge3->setTopLeft(Pnt2s(5,1));
       HorizontalRolloverBlueRidge3->setBottomRight(Pnt2s(6,7));
       HorizontalRolloverBlueRidge3->setColor(Color4f(0.61,0.77,1.0,1.0));
	endEditCP(HorizontalRolloverBlueRidge3);

    RectUIDrawObjectPtr HorizontalRolloverBlueRidge4 = RectUIDrawObject::create();
	beginEditCP(HorizontalRolloverBlueRidge4);
       HorizontalRolloverBlueRidge4->setTopLeft(Pnt2s(7,1));
       HorizontalRolloverBlueRidge4->setBottomRight(Pnt2s(8,7));
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
        WindowsHorizontalScrollBarDrawObject->setActiveOffset(Vec2s(0,0));

        WindowsHorizontalScrollBarDrawObject->setDrawObject(WindowsHorizontalScrollBarRidges);
        WindowsHorizontalScrollBarDrawObject->setActiveDrawObject(WindowsHorizontalActiveScrollBarRidges);
        WindowsHorizontalScrollBarDrawObject->setFocusedDrawObject(WindowsHorizontalScrollBarRidges);
        WindowsHorizontalScrollBarDrawObject->setRolloverDrawObject(WindowsHorizontalRolloverScrollBarRidges);
        WindowsHorizontalScrollBarDrawObject->setDisabledDrawObject(WindowsHorizontalScrollBarRidges);
	endEditCP(WindowsHorizontalScrollBarDrawObject);

	//Windows ScrollBar
	ScrollBarPtr WindowsScrollBar = ScrollBar::create();
	beginEditCP(WindowsScrollBar);
		WindowsScrollBar->setEnabled(true);
		WindowsScrollBar->setVisible(true);
		
		WindowsScrollBar->setConstraints(NullFC);
		//Sizes
		WindowsScrollBar->setMinSize(Vec2s(0,0));
		WindowsScrollBar->setMaxSize(Vec2s(32767,32767)); //2^15
		WindowsScrollBar->setPreferredSize(Vec2s(17,100));

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
	endEditCP(WindowsScrollBar);
	
    ScrollBar::getClassType().setPrototype(WindowsScrollBar);

	//************************** ScrollPanel*****************************
	//Windows ScrollPanelBorder
	EmptyBorderPtr WindowsScrollPanelBorder = EmptyBorder::create();

	//Windows ScrollPanelBackground
	EmptyUIBackgroundPtr WindowsScrollPanelBackground = EmptyUIBackground::create();
    
	//Vertical ScrollBar
	ScrollBarPtr WindowsScrollPanelVerticalScrollBar = ScrollBar::create();
    beginEditCP(WindowsScrollPanelVerticalScrollBar, ScrollBar::PreferredSizeFieldMask | ScrollBar::OrientationFieldMask);
		WindowsScrollPanelVerticalScrollBar->setPreferredSize(Vec2s(17,100));
        WindowsScrollPanelVerticalScrollBar->setOrientation(VERTICAL_ALIGNMENT);
    beginEditCP(WindowsScrollPanelVerticalScrollBar, ScrollBar::PreferredSizeFieldMask | ScrollBar::OrientationFieldMask);

	//Horizontal ScrollBar
	ScrollBarPtr WindowsScrollPanelHorizontalScrollBar = ScrollBar::create();
    beginEditCP(WindowsScrollPanelHorizontalScrollBar, ScrollBar::PreferredSizeFieldMask | ScrollBar::OrientationFieldMask);
		WindowsScrollPanelHorizontalScrollBar->setPreferredSize(Vec2s(100,17));
        WindowsScrollPanelHorizontalScrollBar->setOrientation(HORIZONTAL_ALIGNMENT);
    beginEditCP(WindowsScrollPanelHorizontalScrollBar, ScrollBar::PreferredSizeFieldMask | ScrollBar::OrientationFieldMask);


	//Windows ScrollPanel
	ScrollPanelPtr WindowsScrollPanel = ScrollPanel::create();
	beginEditCP(WindowsScrollPanel);
		WindowsScrollPanel->setEnabled(true);
		WindowsScrollPanel->setVisible(true);
		
		WindowsScrollPanel->setConstraints(NullFC);
		//Sizes
		WindowsScrollPanel->setMinSize(Vec2s(0,0));
		WindowsScrollPanel->setMaxSize(Vec2s(32767,32767)); //2^15
		WindowsScrollPanel->setPreferredSize(Vec2s(100,100));

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
	
    ScrollPanel::getClassType().setPrototype(WindowsScrollPanel);

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
	UIViewportPtr WindowsUIViewport = UIViewport::create();
	beginEditCP(WindowsUIViewport);
		WindowsUIViewport->setEnabled(true);
		WindowsUIViewport->setVisible(true);
		
		WindowsUIViewport->setConstraints(NullFC);
		//Sizes
		WindowsUIViewport->setMinSize(Vec2s(0,0));
		WindowsUIViewport->setMaxSize(Vec2s(32767,32767)); //2^15
		WindowsUIViewport->setPreferredSize(Vec2s(100,100));

		//Border
		WindowsUIViewport->setBorder(WindowsUIViewportBorder);
		
		//Background
		WindowsUIViewport->setBackground(WindowsUIViewportBackground);
		
		//Opacity
		WindowsUIViewport->setOpacity(1.0);
	endEditCP(WindowsUIViewport);
	
	UIViewport::getClassType().setPrototype(WindowsUIViewport);
	
	//************************** RotatedComponent*****************************
	//Windows RotatedComponentBorder
	EmptyBorderPtr WindowsRotatedComponentBorder = EmptyBorder::create();

	//Windows RotatedComponentBackground
	EmptyUIBackgroundPtr WindowsRotatedComponentBackground = EmptyUIBackground::create();

	//Windows RotatedComponent
	RotatedComponentPtr WindowsRotatedComponent = RotatedComponent::create();
	beginEditCP(WindowsRotatedComponent);
		WindowsRotatedComponent->setEnabled(true);
		WindowsRotatedComponent->setVisible(true);
		
		WindowsRotatedComponent->setConstraints(NullFC);
		//Sizes
		WindowsRotatedComponent->setMinSize(Vec2s(0,0));
		WindowsRotatedComponent->setMaxSize(Vec2s(32767,32767)); //2^15
		WindowsRotatedComponent->setPreferredSize(Vec2s(100,100));

		//Border
		WindowsRotatedComponent->setBorder(WindowsRotatedComponentBorder);
		
		//Background
		WindowsRotatedComponent->setBackground(WindowsRotatedComponentBackground);
		
		//Opacity
		WindowsRotatedComponent->setOpacity(1.0);

		WindowsRotatedComponent->setInternalComponent(NullFC);

        WindowsRotatedComponent->setResizePolicy(RotatedComponent::RESIZE_TO_MIN);
	endEditCP(WindowsRotatedComponent);
	
    RotatedComponent::getClassType().setPrototype(WindowsRotatedComponent);

    
	//************************** List *****************************
	//Windows RotatedComponentBorder
	EmptyBorderPtr WindowsListBorder = EmptyBorder::create();

	//Windows RotatedComponentBackground
	EmptyUIBackgroundPtr WindowsListBackground = EmptyUIBackground::create();

	//Windows RotatedComponent
	ListPtr WindowsList = List::create();
	beginEditCP(WindowsList);
		WindowsList->setEnabled(true);
		WindowsList->setVisible(true);
		
		WindowsList->setConstraints(NullFC);
		//Sizes
		WindowsList->setMinSize(Vec2s(0,0));
		WindowsList->setMaxSize(Vec2s(32767,32767)); //2^15
		WindowsList->setPreferredSize(Vec2s(100,100));

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
		
	endEditCP(WindowsList);
	
    List::getClassType().setPrototype(WindowsList);
    
	
	//************************** TableHeader *****************************
	//Windows RotatedComponentBorder
	EmptyBorderPtr WindowsTableHeaderBorder = EmptyBorder::create();

	//Windows RotatedComponentBackground
	EmptyUIBackgroundPtr WindowsTableHeaderBackground = EmptyUIBackground::create();
    
	//Windows RotatedComponent
	TableHeaderPtr WindowsTableHeader = TableHeader::create();
	beginEditCP(WindowsTableHeader);
		WindowsTableHeader->setEnabled(true);
		WindowsTableHeader->setVisible(true);
		
		WindowsTableHeader->setConstraints(NullFC);
		//Sizes
		WindowsTableHeader->setMinSize(Vec2s(0,0));
		WindowsTableHeader->setMaxSize(Vec2s(32767,32767)); //2^15
		WindowsTableHeader->setPreferredSize(Vec2s(100,100));

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
	
    TableHeader::getClassType().setPrototype(WindowsTableHeader);
    
	
	//************************** Table *****************************
	//Windows RotatedComponentBorder
	EmptyBorderPtr WindowsTableBorder = EmptyBorder::create();

	//Windows RotatedComponentBackground
	EmptyUIBackgroundPtr WindowsTableBackground = EmptyUIBackground::create();

	//Windows RotatedComponent
	TablePtr WindowsTable = Table::create();
	beginEditCP(WindowsTable);
		WindowsTable->setEnabled(true);
		WindowsTable->setVisible(true);
		
		WindowsTable->setConstraints(NullFC);
		//Sizes
		WindowsTable->setMinSize(Vec2s(0,0));
		WindowsTable->setMaxSize(Vec2s(32767,32767)); //2^15
		WindowsTable->setPreferredSize(Vec2s(100,100));

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
	
    Table::getClassType().setPrototype(WindowsTable);
    
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
		getPrototypes().addValue(WindowsLabelMenuItem);
		getPrototypes().addValue(WindowsSeperatorMenuItem);
		getPrototypes().addValue(WindowsMenu);
		getPrototypes().addValue(WindowsPopupMenu);
		getPrototypes().addValue(WindowsMenuBar);
		getPrototypes().addValue(WindowsRotatedComponent);
		getPrototypes().addValue(WindowsScrollBar);
		getPrototypes().addValue(WindowsScrollPanel);
		getPrototypes().addValue(WindowsUIViewport);
		getPrototypes().addValue(WindowsList);
		getPrototypes().addValue(WindowsTableHeader);
		getPrototypes().addValue(WindowsTable);
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
		_SubMenuPopupTime(0.25),
        _KeyAcceleratorMenuFlashTime(0.15)
{
}

WindowsLookAndFeel::WindowsLookAndFeel(const WindowsLookAndFeel &source) :
    Inherited(source),
		_TextCaretRate(source._TextCaretRate),
		_ToolTipPopupTime(source._ToolTipPopupTime),
		_SubMenuPopupTime(source._SubMenuPopupTime),
        _KeyAcceleratorMenuFlashTime(source._KeyAcceleratorMenuFlashTime)
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

