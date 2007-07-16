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

#include "OSGAbsoluteLayout.h"
#include "OSGAbsoluteLayoutConstraints.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AbsoluteLayout
A UI AbsoluteLayout.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbsoluteLayout::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void AbsoluteLayout::draw(const MFComponentPtr Components,const ComponentPtr ParentComponent, const GraphicsPtr TheGraphics) const
{	
	Pnt2s borderOffset;
	Vec2s borderSize;
	ParentComponent->getInsideBorderBounds(borderOffset, borderSize);
	glTranslatef(borderOffset.x(), borderOffset.y(), 0);
	for(UInt32 i = 0 ; i<Components.size(); ++i)
	{
		//Calculate the Components Size
		Components.getValue(i)->setSize(Components.getValue(i)->getPreferredSize());
		if(Components.getValue(i)->getConstraints() != NullFC)
		{
			//Get the Components Position
			Pnt2s pos = AbsoluteLayoutConstraintsPtr::dcast(Components.getValue(i)->getConstraints())->getPosition();
			glTranslatef(pos.x(), pos.y(), 0.0);
			Components.getValue(i)->draw(TheGraphics);
			glTranslatef(-pos.x(), -pos.y(), 0.0);
		}
		else
		{
		   Components.getValue(i)->draw(TheGraphics);
		}
	}
	glTranslatef(-borderOffset.x(), -borderOffset.y(), 0);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbsoluteLayout::AbsoluteLayout(void) :
    Inherited()
{
}

AbsoluteLayout::AbsoluteLayout(const AbsoluteLayout &source) :
    Inherited(source)
{
}

AbsoluteLayout::~AbsoluteLayout(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbsoluteLayout::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void AbsoluteLayout::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump AbsoluteLayout NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGABSOLUTELAYOUTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGABSOLUTELAYOUTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGABSOLUTELAYOUTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

