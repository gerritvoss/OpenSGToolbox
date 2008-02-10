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

#include "OSGMultiColorMatteBorder.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::MultiColorMatteBorder
UI MultiColor Matte Border. Creates a matte-look border using a different color for each side. (The difference between this border and a line border is that you can specify the individual border dimensions as well as colors.) 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MultiColorMatteBorder::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void MultiColorMatteBorder::draw(const GraphicsPtr g, const Real32 x, const Real32 y , const Real32 Width, const Real32 Height, const Real32 Opacity) const
{
	//x, y is upper left point
	
	//Top
	g->drawQuad(
		Pnt2f(x+getLeftWidth(),y),
		Pnt2f(x+Width, y),
		Pnt2f(x+Width, y+getTopWidth()),
		Pnt2f(x+getLeftWidth(), y+getTopWidth()),
		getTopLineLeftColor(),
		getTopLineRightColor(),
		getTopLineRightColor(),
		getTopLineLeftColor(),
		Opacity);
	//Left
	g->drawQuad(
		Pnt2f(x,y),
		Pnt2f(x+getRightWidth(), y),
		Pnt2f(x+getRightWidth(), y+Height-getBottomWidth()),
		Pnt2f(x, y+Height-getBottomWidth()),
		getLeftLineTopColor(),
		getLeftLineTopColor(),
		getLeftLineBottomColor(),
		getLeftLineBottomColor(),
		Opacity);
	//Right
	g->drawQuad(
		Pnt2f(x+Width-getRightWidth(),y+getTopWidth()),
		Pnt2f(x+Width, y+getTopWidth()),
		Pnt2f(x+Width, y+Height),
		Pnt2f(x+Width-getRightWidth(), y+Height),
		getRightLineTopColor(),
		getRightLineTopColor(),
		getRightLineBottomColor(),
		getRightLineBottomColor(),
		Opacity);
	//Bottom
	g->drawQuad(
		Pnt2f(x,y+Height-getBottomWidth()),
		Pnt2f(x+Width-getRightWidth(), y+Height-getBottomWidth()),
		Pnt2f(x+Width-getRightWidth(), y+Height),
		Pnt2f(x, y+Height),
		getBottomLineLeftColor(),
		getBottomLineRightColor(),
		getBottomLineRightColor(),
		getBottomLineLeftColor(),
		Opacity);
	//g->drawQuad(Pnt2f(x, y+Height-getBottomWidth()), Pnt2f(x+Width, y+Height), getBottomColor(), Opacity);

}

void MultiColorMatteBorder::getInsets(Real32& Left, Real32& Right,Real32& Top,Real32& Bottom) const
{
	Left = getLeftWidth();
	Right = getRightWidth();
	Top = getTopWidth();
	Bottom = getBottomWidth();
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MultiColorMatteBorder::MultiColorMatteBorder(void) :
    Inherited()
{
}

MultiColorMatteBorder::MultiColorMatteBorder(const MultiColorMatteBorder &source) :
    Inherited(source)
{
}

MultiColorMatteBorder::~MultiColorMatteBorder(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MultiColorMatteBorder::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void MultiColorMatteBorder::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump MultiColorMatteBorder NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGMULTICOLORMATTEBORDERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGMULTICOLORMATTEBORDERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGMULTICOLORMATTEBORDERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

