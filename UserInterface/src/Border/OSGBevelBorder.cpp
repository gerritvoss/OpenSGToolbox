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

#include "OSGBevelBorder.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::BevelBorder
UI Bevel Border. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void BevelBorder::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void BevelBorder::draw(const GraphicsPtr g, const Int16 x, const Int16 y , const UInt16 Width, const UInt16 Height, const Real32 Opacity) const
{
	Pnt2s TopLeft = Pnt2s(x, y);
	Pnt2s BottomLeft = Pnt2s(x, y+Height);
	Pnt2s BottomRight = Pnt2s(x + Width, y + Height);
	Pnt2s TopRight = Pnt2s(x + Width, y);
	//x, y is upper left hand side.
	if(getRaised())
	{
		//Top
		g->drawLine(TopLeft, TopRight, 1, getHighlightOuter(),Opacity);
		g->drawLine(Pnt2s(TopLeft.x()+1, TopLeft.y()+1), Pnt2s(TopRight.x()-1, TopRight.y()+1), 1, getHighlightInner(), Opacity);
		
		//Left
		g->drawLine(TopLeft, BottomLeft, 1, getHighlightOuter(), Opacity);
		g->drawLine(Pnt2s(TopLeft.x()+1, TopLeft.y()+1), Pnt2s(BottomLeft.x()+1, BottomLeft.y()-1), 1, getHighlightInner(), Opacity);

		//Bottom
		g->drawLine(BottomLeft, BottomRight, 1, getShadowOuter(), Opacity);
		g->drawLine(Pnt2s(BottomLeft.x()+1, BottomLeft.y()-1), Pnt2s(BottomRight.x()-1, BottomRight.y()-1), 1, getShadowInner(), Opacity);
		
		//Right
		g->drawLine(BottomRight, TopRight, 1, getShadowOuter(), Opacity);
		g->drawLine(Pnt2s(BottomRight.x()-1, BottomRight.y()-1),Pnt2s(TopRight.x()-1, TopRight.y()+1), 1, getShadowInner(), Opacity);
	}
	else//Lines need to be drawn in a different order, with different colors.
	{
		
		//Bottom
		g->drawLine(BottomLeft, BottomRight, 1, getHighlightOuter(), Opacity);
		g->drawLine(Pnt2s(BottomLeft.x()+1, BottomLeft.y()-1), Pnt2s(BottomRight.x()-1, BottomRight.y()-1), 1, getHighlightInner(), Opacity);
		
		//Right
		g->drawLine(BottomRight, TopRight, 1, getHighlightOuter(), Opacity);
		g->drawLine(Pnt2s(BottomRight.x()-1, BottomRight.y()-1),Pnt2s(TopRight.x()-1, TopRight.y()+1), 1, getHighlightInner(), Opacity);

		//Top
		g->drawLine(TopLeft, TopRight, 1, getShadowOuter(),Opacity);
		g->drawLine(Pnt2s(TopLeft.x()+1, TopLeft.y()+1), Pnt2s(TopRight.x()-1, TopRight.y()+1), 1, getShadowInner(), Opacity);
		
		//Left
		g->drawLine(TopLeft, BottomLeft, 1, getShadowOuter(), Opacity);
		g->drawLine(Pnt2s(TopLeft.x()+1, TopLeft.y()+1), Pnt2s(BottomLeft.x()+1, BottomLeft.y()-1), 1, getShadowInner(), Opacity);

	}

}

void BevelBorder::getInsets(UInt16& Left, UInt16& Right,UInt16& Top,UInt16& Bottom) const
{
	Left = Right = Top = Bottom = 2;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

BevelBorder::BevelBorder(void) :
    Inherited()
{
}

BevelBorder::BevelBorder(const BevelBorder &source) :
    Inherited(source)
{
}

BevelBorder::~BevelBorder(void)
{
}

/*----------------------------- class specific ----------------------------*/

void BevelBorder::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void BevelBorder::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump BevelBorder NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGBEVELBORDERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGBEVELBORDERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGBEVELBORDERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

