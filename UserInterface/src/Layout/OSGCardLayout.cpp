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

#include "OSGCardLayout.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::CardLayout
A UI CardLayout. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CardLayout::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void CardLayout::first(const ContainerPtr TheContainer)
{
	beginEditCP(CardLayoutPtr(this), CardFieldMask);
		setCard(0);
	endEditCP(CardLayoutPtr(this), CardFieldMask);
}

void CardLayout::last(const ContainerPtr TheContainer)
{
	beginEditCP(CardLayoutPtr(this), CardFieldMask);
	setCard(TheContainer->getChildren().getSize()-1);
	endEditCP(CardLayoutPtr(this), CardFieldMask);
}

void CardLayout::next(const ContainerPtr TheContainer)
{	
	beginEditCP(CardLayoutPtr(this), CardFieldMask);
		setCard((getCard()+1)%TheContainer->getChildren().getSize());
	endEditCP(CardLayoutPtr(this), CardFieldMask);
}

void CardLayout::previous(const ContainerPtr TheContainer)
{   
	beginEditCP(CardLayoutPtr(this), CardFieldMask);
		setCard((getCard()-1)%TheContainer->getChildren().getSize());
	endEditCP(CardLayoutPtr(this), CardFieldMask);
}

void CardLayout::draw(const MFComponentPtr Components,const ComponentPtr ParentComponent, const GraphicsPtr TheGraphics) const
{
	/*!
	  Draw the current "card" component centered in the parent component
	  and set to the size of the parent component, or to its max size
	*/
	Pnt2s borderOffset;
	Vec2s size;
	ParentComponent->getInsideBorderBounds(borderOffset, size);
	ComponentPtr curCard(Components.getValue(getCard()));

	// check each dimension against the max size of the component;
	if (size[0] > curCard->getMaxSize()[0]) 
		size[0] = curCard->getMaxSize()[0];
	if (size[1] > curCard->getMaxSize()[1]) 
		size[1] = curCard->getMaxSize()[1];
	// set the component to its parent component's size, or its max size
	beginEditCP(curCard, Component::SizeFieldMask);
		curCard->setSize(size);
	endEditCP(curCard, Component::SizeFieldMask);

	Int64 offsetx( (ParentComponent->getSize().x() - curCard->getSize().x()) /2);
	Int64 offsety( (ParentComponent->getSize().y() - curCard->getSize().y()) /2);

	glTranslatef(borderOffset.x(), borderOffset.y(), 0);
	glTranslatef(offsetx, offsety, 0);
	curCard->draw(TheGraphics);
	glTranslatef(-offsetx, -offsety, 0);
	glTranslatef(-borderOffset.x(), -borderOffset.y(), 0);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CardLayout::CardLayout(void) :
    Inherited()
{
}

CardLayout::CardLayout(const CardLayout &source) :
    Inherited(source)
{
}

CardLayout::~CardLayout(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CardLayout::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void CardLayout::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump CardLayout NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGCARDLAYOUTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCARDLAYOUTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCARDLAYOUTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

