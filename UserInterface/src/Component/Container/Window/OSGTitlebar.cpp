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

#include "OSGTitlebar.h"
#include "Component/Container/Window/OSGInternalWindow.h"
#include "Component/Button/OSGButton.h"
#include "Component/Text/OSGLabel.h"
#include "Util//OSGUIDrawUtils.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Titlebar
A UI Titlebar.         
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Titlebar::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Titlebar::setTitle(const std::string& Title)
{
	if(getTitleLabel() != NullFC)
	{
		beginEditCP(getTitleLabel(), Label::TextFieldMask);
			getTitleLabel()->setText(Title);
		endEditCP(getTitleLabel(), Label::TextFieldMask);
	}
}

std::string Titlebar::getTitle(void) const
{
	if(getTitleLabel() != NullFC)
	{
		getTitleLabel()->getText();
	}
	else
	{
		return std::string("");
	}
}

void Titlebar::updateLayout(void)
{
	Pnt2s InsetsTopLeft, InsetsBottomRight;
	getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);
	Vec2s InsetsSize(InsetsBottomRight - InsetsTopLeft);

	Pnt2s FrameIconPos;
	Vec2s FrameIconSize;
	if(getFrameIcon() != NullFC)
	{
		FrameIconPos = InsetsTopLeft;
		FrameIconSize.setValues( getFrameIcon()->getPreferredSize().x(), InsetsSize.y() );
		beginEditCP(getFrameIcon(), Component::PositionFieldMask | Component::SizeFieldMask);
			getFrameIcon()->setPosition(FrameIconPos);
			getFrameIcon()->setSize(FrameIconSize);
		endEditCP(getFrameIcon(), Component::PositionFieldMask | Component::SizeFieldMask);
	}
	Pnt2s CloseButtonPos(InsetsBottomRight.x(), InsetsTopLeft.y()+1);
	Vec2s CloseButtonSize;
	if(getDrawClose() && getCloseButton() != NullFC)
	{
		CloseButtonSize.setValues(getCloseButton()->getPreferredSize().x(), InsetsSize.y()-2);
		CloseButtonPos -= Vec2s(CloseButtonSize.x(),0) + Vec2s(3,0);
		beginEditCP(getCloseButton(), Component::PositionFieldMask | Component::SizeFieldMask);
			getCloseButton()->setPosition(CloseButtonPos);
			getCloseButton()->setSize(CloseButtonSize);
		endEditCP(getCloseButton(), Component::PositionFieldMask | Component::SizeFieldMask);
	}
	Pnt2s MaximizeButtonPos(CloseButtonPos);
	Vec2s MaximizeButtonSize;
	if(getDrawMaximize() && getMaximizeButton() != NullFC)
	{
		MaximizeButtonSize.setValues(getMaximizeButton()->getPreferredSize().x(), InsetsSize.y()-2);
		MaximizeButtonPos -= Vec2s(MaximizeButtonSize.x(),0) + Vec2s(3,0);
		beginEditCP(getMaximizeButton(), Component::PositionFieldMask | Component::SizeFieldMask);
			getMaximizeButton()->setPosition(MaximizeButtonPos);
			getMaximizeButton()->setSize(MaximizeButtonSize);
		endEditCP(getMaximizeButton(), Component::PositionFieldMask | Component::SizeFieldMask);
	}
	Pnt2s IconifyButtonPos(MaximizeButtonPos);
	Vec2s IconifyButtonSize;
	if(getDrawIconify() && getIconifyButton() != NullFC)
	{
		IconifyButtonSize.setValues(getIconifyButton()->getPreferredSize().x(), InsetsSize.y()-2);
		IconifyButtonPos -= Vec2s(IconifyButtonSize.x(),0) + Vec2s(3,0);
		beginEditCP(getIconifyButton(), Component::PositionFieldMask | Component::SizeFieldMask);
			getIconifyButton()->setPosition(IconifyButtonPos);
			getIconifyButton()->setSize(IconifyButtonSize);
		endEditCP(getIconifyButton(), Component::PositionFieldMask | Component::SizeFieldMask);
	}
	Pnt2s TitleLabelPos(FrameIconPos + FrameIconSize);
	Vec2s TitleLabelSize;
	if(getTitleLabel() != NullFC)
	{
		TitleLabelSize.setValues(IconifyButtonPos.x()-1-FrameIconPos.x()-FrameIconSize.x(), InsetsSize.y());
		beginEditCP(getTitleLabel(), Component::PositionFieldMask | Component::SizeFieldMask);
			getTitleLabel()->setPosition(FrameIconPos);
			getTitleLabel()->setSize(TitleLabelSize);
		endEditCP(getTitleLabel(), Component::PositionFieldMask | Component::SizeFieldMask);
	}
}

void Titlebar::updateClipBounds(void)
{
	Pnt2s TopLeft, BottomRight;
	if(getParentContainer() == NullFC)
	{
		//If I have no parent container use my bounds
		getBounds(TopLeft, BottomRight);
	}
	else
	{
		//Get the intersection of:
		     //My Bounds
		     //My Parent Containers Clip Bounds
		     //My Parent Containers Inset Bounds
        Pnt2s MyTopLeft,MyBottomRight;
        getBounds(MyTopLeft,MyBottomRight);

		//Update my Parent Container's Clip Bounds
		//Container::Ptr::dcast(getParentContainer())->updateClipBounds();

		//Get Parent Container's Clip Bounds
		Pnt2s ContainerClipTopLeft, ContainerClipBottomRight;
		InternalWindow::Ptr::dcast(getParentWindow())->getClipBounds(ContainerClipTopLeft,ContainerClipBottomRight);
		
        //Parent Container's Clip Bounds are in the Parent Container's Coordinate space
        //We need to convert them to this Components Coordinate space
        ContainerClipTopLeft -= Vec2s(getPosition());
		ContainerClipBottomRight -= Vec2s(getPosition());

		//Get Parent Container's Titlebar Bounds
		Pnt2s ContainerInsetTopLeft, ContainerInsetBottomRight;
		InternalWindow::Ptr::dcast(getParentWindow())->getTitlebarBounds(ContainerInsetTopLeft, ContainerInsetBottomRight);
		
        //Parent Container's Inset Bounds are in the Parent Container's Coordinate space
        //We need to convert them to this Components Coordinate space
        ContainerInsetTopLeft -= Vec2s(getPosition());
		ContainerInsetBottomRight -= Vec2s(getPosition());

		//Get the intersection of my bounds with my parent containers clip bounds
		quadIntersection(MyTopLeft,MyBottomRight,
			ContainerClipTopLeft,ContainerClipBottomRight,
			TopLeft, BottomRight);

		quadIntersection(TopLeft,BottomRight,
			ContainerInsetTopLeft,ContainerInsetBottomRight,
			TopLeft, BottomRight);
	}
	//The Clip Bounds calculated are in my Parent Containers coordinate space
	//Translate these bounds into my own coordinate space
	beginEditCP(ComponentPtr(this), Component::ClipTopLeftFieldMask | Component::ClipBottomRightFieldMask);
		setClipTopLeft(TopLeft);
		setClipBottomRight(BottomRight);
	endEditCP(ComponentPtr(this), Component::ClipTopLeftFieldMask | Component::ClipBottomRightFieldMask);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Titlebar::Titlebar(void) :
    Inherited()
{
}

Titlebar::Titlebar(const Titlebar &source) :
    Inherited(source)
{
    if(getIconifyButton() != NullFC)
    {
        beginEditCP(TitlebarPtr(this), IconifyButtonFieldMask);
			setIconifyButton(Button::Ptr::dcast(getIconifyButton()->shallowCopy()));
        endEditCP(TitlebarPtr(this), IconifyButtonFieldMask);
    }
    if(getMaximizeButton() != NullFC)
    {
        beginEditCP(TitlebarPtr(this), MaximizeButtonFieldMask);
			setMaximizeButton(Button::Ptr::dcast(getMaximizeButton()->shallowCopy()));
        endEditCP(TitlebarPtr(this), MaximizeButtonFieldMask);
    }
    if(getCloseButton() != NullFC)
    {
        beginEditCP(TitlebarPtr(this), CloseButtonFieldMask);
			setCloseButton(Button::Ptr::dcast(getCloseButton()->shallowCopy()));
        endEditCP(TitlebarPtr(this), CloseButtonFieldMask);
    }
    if(getTitleLabel() != NullFC)
    {
        beginEditCP(TitlebarPtr(this), TitleLabelFieldMask);
			setTitleLabel(Label::Ptr::dcast(getTitleLabel()->shallowCopy()));
        endEditCP(TitlebarPtr(this), TitleLabelFieldMask);
    }
}

Titlebar::~Titlebar(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Titlebar::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
	
	

	if( (whichField & FrameIconFieldMask) ||
		(whichField & IconifyButtonFieldMask) ||
		(whichField & MaximizeButtonFieldMask) ||
		(whichField & CloseButtonFieldMask) ||
		(whichField & TitleLabelFieldMask) ||
		(whichField & DrawCloseFieldMask) ||
		(whichField & DrawMaximizeFieldMask) ||
		(whichField & DrawIconifyFieldMask)
		)
	{
		beginEditCP(TitlebarPtr(this), Titlebar::ChildrenFieldMask);
			getChildren().clear();
			if(getFrameIcon() != NullFC)
			{
				getChildren().addValue(getFrameIcon());
			}
			if(getTitleLabel() != NullFC)
			{
				getChildren().addValue(getTitleLabel());
			}
			if(getDrawIconify() && getIconifyButton() != NullFC)
			{
				getChildren().addValue(getIconifyButton());
			}
			if(getDrawMaximize() && getMaximizeButton() != NullFC)
			{
				getChildren().addValue(getMaximizeButton());
			}
			if(getDrawClose() && getCloseButton() != NullFC)
			{
				getChildren().addValue(getCloseButton());
			}
		endEditCP(TitlebarPtr(this), Titlebar::ChildrenFieldMask);
	}

	if(((whichField & IconifyButtonFieldMask) ||
		(whichField & ParentWindowFieldMask)) &&
		getParentWindow() != NullFC &&
		getParentWindow()->getIconable() != getIconifyButton()->getEnabled())
	{
		beginEditCP(getIconifyButton(), Button::EnabledFieldMask);
			getIconifyButton()->setEnabled(getParentWindow()->getIconable());
		endEditCP(getIconifyButton(), Button::EnabledFieldMask);
	}
	
	if(((whichField & MaximizeButtonFieldMask) ||
		(whichField & ParentWindowFieldMask)) &&
		getParentWindow() != NullFC &&
		getParentWindow()->getMaximizable() != getMaximizeButton()->getEnabled())
	{
		beginEditCP(getMaximizeButton(), Button::EnabledFieldMask);
			getMaximizeButton()->setEnabled(getParentWindow()->getMaximizable());
		endEditCP(getMaximizeButton(), Button::EnabledFieldMask);
	}
	
	if(((whichField & CloseButtonFieldMask) ||
		(whichField & ParentWindowFieldMask)) &&
		getParentWindow() != NullFC &&
		getParentWindow()->getClosable() != getCloseButton()->getEnabled())
	{
		beginEditCP(getCloseButton(), Button::EnabledFieldMask);
			getCloseButton()->setEnabled(getParentWindow()->getClosable());
		endEditCP(getCloseButton(), Button::EnabledFieldMask);
	}
}

void Titlebar::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Titlebar NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGTITLEBARBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGTITLEBARBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTITLEBARFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

