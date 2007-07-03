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
#include "Background/OSGColorUIBackground.h"
#include "Background/OSGEmptyUIBackground.h"
#include "Component/OSGButton.h"
#include "Component/OSGLabel.h"
#include "Component/OSGFrame.h"
#include "Component/OSGPanel.h"
#include "Component/OSGImageComponent.h"
#include "Util/OSGUIDefines.h"

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
	LineBorderPtr DefaultButtonBorder = LineBorder::create();
	beginEditCP(DefaultButtonBorder);
		DefaultButtonBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
		DefaultButtonBorder->setWidth(1);
	endEditCP(DefaultButtonBorder);

	//Default ButtonBackground
	ColorUIBackgroundPtr DefaultButtonBackground = ColorUIBackground::create();
	beginEditCP(DefaultButtonBackground);
		DefaultButtonBackground->setColor(Color4f(0.7,0.7,0.7,1.0));
	endEditCP(DefaultButtonBackground);

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
		DefaultButton->setSize(Vec2s(0,0));

		//Border
		DefaultButton->setBorder(DefaultButtonBorder);
		
		//Background
		DefaultButton->setBackground(DefaultButtonBackground);

		//Foreground
		DefaultButton->setForegroundColor(Color4f(0.0,0.0,0.0,1.0));
		
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
		DefaultLabel->setSize(Vec2s(0,0));

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
		DefaultFrame->setSize(Vec2s(0,0));

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
	LineBorderPtr DefaultPanelBorder = LineBorder::create();
	beginEditCP(DefaultPanelBorder);
		DefaultPanelBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
		DefaultPanelBorder->setWidth(1);
	endEditCP(DefaultPanelBorder);

	//Default PanelBackground
	ColorUIBackgroundPtr DefaultPanelBackground = ColorUIBackground::create();
	beginEditCP(DefaultPanelBackground);
		DefaultPanelBackground->setColor(Color4f(0.7,0.7,0.7,1.0));
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
		DefaultPanel->setSize(Vec2s(0,0));

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

	beginEditCP(DefaultLookAndFeelPtr(this), DefaultLookAndFeel::PrototypesFieldMask);
		getPrototypes().addValue(DefaultButton);
		getPrototypes().addValue(DefaultLabel);
		getPrototypes().addValue(DefaultFrame);
		getPrototypes().addValue(DefaultPanel);
		getPrototypes().addValue(DefaultImageComponent);
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

