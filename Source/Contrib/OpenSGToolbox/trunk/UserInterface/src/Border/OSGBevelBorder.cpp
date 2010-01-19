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

void BevelBorder::draw(const GraphicsPtr g, const Real32 x, const Real32 y , const Real32 Width, const Real32 Height, const Real32 Opacity, bool Clipping) const
{

	Color4f TopOuter, TopInner, BottomOuter, BottomInner;
	//x, y is upper left hand side.
	if(getRaised())
	{
		TopOuter=getHighlightOuter();
		TopInner=getHighlightInner();
		BottomOuter = getShadowOuter();
		BottomInner = getShadowInner();
	}
	else
	{
		TopOuter = getShadowOuter();
		TopInner = getShadowInner();
		BottomOuter = getHighlightOuter();
		BottomInner = getHighlightInner();
	}
	//Top
	g->drawQuad(Pnt2f(x, y), Pnt2f(x+Width, y), Pnt2f(x+Width-getWidth(), y+getWidth()), Pnt2f(x+getWidth(), y+getWidth()), TopOuter, TopOuter, TopInner, TopInner, Opacity);
	//Left
	g->drawQuad(Pnt2f(x, y), Pnt2f(x, y+Height), Pnt2f(x+getWidth(), y+Height-getWidth()), Pnt2f(x+getWidth(), y+getWidth()), TopOuter, TopOuter, TopInner, TopInner, Opacity);
	//Right
	g->drawQuad(Pnt2f(x+Width-getWidth(), y+getWidth()), Pnt2f(x+Width-getWidth(), y+Height-getWidth()), Pnt2f(x+Width, y+Height), Pnt2f(x+Width, y),BottomInner, BottomInner, BottomOuter, BottomOuter,  Opacity);
	//Bottom
	g->drawQuad(Pnt2f(x, y+Height),Pnt2f(x+Width, y+Height), Pnt2f(x+Width-getWidth(), y+Height-getWidth()), Pnt2f(x+getWidth(), y+Height-getWidth()), BottomOuter, BottomOuter, BottomInner, BottomInner, Opacity);
}

void BevelBorder::getInsets(Real32& Left, Real32& Right,Real32& Top,Real32& Bottom) const
{
	Left = Right = Top = Bottom = getWidth();
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

