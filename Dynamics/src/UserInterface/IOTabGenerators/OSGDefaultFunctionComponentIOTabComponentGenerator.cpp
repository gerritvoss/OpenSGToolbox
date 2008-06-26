/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Dynamics                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#define OSG_COMPILEDYNAMICSLIB

#include <OpenSG/OSGConfig.h>


#include <OpenSG/UserInterface/OSGButton.h>

#include "OSGDefaultFunctionComponentIOTabComponentGenerator.h"

#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGColorLayer.h>
#include <OpenSG/UserInterface/OSGBoxLayout.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGContainer.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGLabel.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultFunctionComponentIOTabComponentGenerator
A UI Default List ComponentGenerator.  	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultFunctionComponentIOTabComponentGenerator::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
ComponentPtr DefaultFunctionComponentIOTabComponentGenerator::getIOTabComponent(FunctionComponentPtr Parent, const FunctionIOType& Value, UInt32 Index, bool IsSelected, bool HasFocus, bool isDragFrom, bool isDragTo)
{
	ButtonPtr Button = Button::create();
    beginEditCP(Button, Button::TextFieldMask);
        Button->setText(Value.getType()->getCName());
    endEditCP(Button, Button::TextFieldMask);
	
	UIFontPtr ParameterNameFont = osg::UIFont::create();
    beginEditCP(ParameterNameFont, UIFont::SizeFieldMask);
        ParameterNameFont->setSize(16);
    endEditCP(ParameterNameFont, UIFont::SizeFieldMask);
	
	LabelPtr ParameterName = osg::Label::create();
	beginEditCP(ParameterName, /*Label::BordersFieldMask | Label::BackgroundsFieldMask |*/ Label::FontFieldMask | Label::TextFieldMask /*| Label::PreferredSizeFieldMask*/ | Label::HorizontalAlignmentFieldMask);
        //ParameterName->setBorders(emptyBorder);
        //ParameterName->setBackgrounds(GreyBackground);
        ParameterName->setFont(ParameterNameFont);
        ParameterName->setText(Value.getParameterName());
        //ParameterName->setPreferredSize(Vec2f(300, 100));
		ParameterName->setHorizontalAlignment(0.5);
	endEditCP(ParameterName, /*Label::BordersFieldMask | Label::BackgroundsFieldMask |*/ Label::FontFieldMask | Label::TextFieldMask /*| Label::PreferredSizeFieldMask*/ | Label::HorizontalAlignmentFieldMask);
	
	FlowLayoutPtr PanelLayout = osg::FlowLayout::create();
	beginEditCP(PanelLayout, FlowLayout::OrientationFieldMask);
        PanelLayout->setOrientation(FlowLayout::VERTICAL_ORIENTATION);
    endEditCP(PanelLayout, FlowLayout::OrientationFieldMask);
	
	LineBorderPtr PanelBorder = osg::LineBorder::create();
    beginEditCP(PanelBorder, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);
        PanelBorder->setColor(Color4f(0.9, 0.9, 0.9, 1.0));
        PanelBorder->setWidth(1);
    endEditCP(PanelBorder, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);
	
	ColorLayerPtr PanelBackground = osg::ColorLayer::create();
	beginEditCP(PanelBackground, ColorLayer::ColorFieldMask);
        PanelBackground->setColor(Color4f(0.0, 0.0, 1.0, 0.1));
    endEditCP(PanelBackground, ColorLayer::ColorFieldMask);
	
	PanelPtr TabComponent = osg::Panel::create();
	beginEditCP(TabComponent, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
        TabComponent->setPreferredSize(Vec2f(100, 50));
        TabComponent->getChildren().push_back(Button);
		TabComponent->getChildren().push_back(ParameterName);
        TabComponent->setLayout(PanelLayout);
        TabComponent->setBackgrounds(PanelBackground);
        TabComponent->setBorders(PanelBorder);
    endEditCP(TabComponent, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);

    return TabComponent;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultFunctionComponentIOTabComponentGenerator::DefaultFunctionComponentIOTabComponentGenerator(void) :
    Inherited()
{
}

DefaultFunctionComponentIOTabComponentGenerator::DefaultFunctionComponentIOTabComponentGenerator(const DefaultFunctionComponentIOTabComponentGenerator &source) :
    Inherited(source)
{
}

DefaultFunctionComponentIOTabComponentGenerator::~DefaultFunctionComponentIOTabComponentGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultFunctionComponentIOTabComponentGenerator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DefaultFunctionComponentIOTabComponentGenerator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DefaultFunctionComponentIOTabComponentGenerator NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDEFAULTFUNCTIONCOMPONENTIOTABCOMPONENTGENERATORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDEFAULTFUNCTIONCOMPONENTIOTABCOMPONENTGENERATORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDEFAULTFUNCTIONCOMPONENTIOTABCOMPONENTGENERATORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

