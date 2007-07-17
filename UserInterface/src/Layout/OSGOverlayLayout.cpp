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

#include "OSGOverlayLayout.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::OverlayLayout
A UI OverlayLayout. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void OverlayLayout::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void OverlayLayout::draw(const MFComponentPtr Components,const ComponentPtr ParentComponent, const GraphicsPtr TheGraphics) const
{
}

void OverlayLayout::updateLayout(const MFComponentPtr Components,const ComponentPtr ParentComponent) const
{
	Pnt2s borderOffset;
	Vec2s borderSize;
	ParentComponent->getInsideBorderBounds(borderOffset, borderSize);
	int maxX = 0;
	int maxY = 0;
	for(int i = 0; i < Components.size(); i++){
		beginEditCP(Components.getValue(i), Component::SizeFieldMask);
		Components.getValue(i)->setSize(Components.getValue(i)->getPreferredSize());
		if(Components.getValue(i)->getSize().x()>maxX)
			maxX = Components.getValue(i)->getSize().x();
		if(Components.getValue(i)->getSize().y()>maxY)
			maxY = Components.getValue(i)->getSize().y();
		endEditCP(Components.getValue(i), Component::SizeFieldMask);
	}
	//overlay layout simply draws all the components on top of each other, with the reference point for all the components being the same
	for(int i = 0; i <Components.size(); i++){
		//Components.getValue(i)->setSize(Components.getValue(i)->getPreferredSize());
		beginEditCP(Components.getValue(i), Component::PositionFieldMask);
		Components.getValue(i)->setPosition(Pnt2s((maxX-Components.getValue(i)->getSize().x())/2.0+borderOffset.x(),
			(maxY-Components.getValue(i)->getSize().y())/2.0+borderOffset.y()));
		endEditCP(Components.getValue(i), Component::PositionFieldMask);
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

OverlayLayout::OverlayLayout(void) :
    Inherited()
{
}

OverlayLayout::OverlayLayout(const OverlayLayout &source) :
    Inherited(source)
{
}

OverlayLayout::~OverlayLayout(void)
{
}

/*----------------------------- class specific ----------------------------*/

void OverlayLayout::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void OverlayLayout::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump OverlayLayout NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGOVERLAYLAYOUTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGOVERLAYLAYOUTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGOVERLAYLAYOUTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

