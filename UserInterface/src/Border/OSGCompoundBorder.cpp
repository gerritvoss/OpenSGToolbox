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

#include "OSGCompoundBorder.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::CompoundBorder
UI Compound Border. A Compound Border made up of an inner border and outer border of any type. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CompoundBorder::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void CompoundBorder::draw(const GraphicsPtr g, const Real32 x, const Real32 y , const Real32 Width, const Real32 Height, const Real32 Opacity) const
{

	Real32 LeftIn, RightIn, BottomIn, UpperIn;
    getOuterBorder()->getInsets(LeftIn, RightIn, UpperIn, BottomIn);
	getInnerBorder()->draw(g, x+LeftIn, y+UpperIn, Width-LeftIn-RightIn, Height-UpperIn-BottomIn, Opacity);

	getOuterBorder()->draw(g, x, y, Width, Height, Opacity);
	
}

void CompoundBorder::getInsets(Real32& Left, Real32& Right,Real32& Top,Real32& Bottom) const
{
	Real32 LeftIn, LeftIn2, RightIn, RightIn2, BottomIn, BottomIn2, UpperIn, UpperIn2;
	getOuterBorder()->getInsets(LeftIn, RightIn, UpperIn, BottomIn);
	getInnerBorder()->getInsets(LeftIn2, RightIn2,UpperIn2, BottomIn2) ;
	Left = LeftIn+LeftIn2;
	Right = RightIn+RightIn2;
	Bottom = BottomIn+BottomIn2;
	Top = UpperIn+UpperIn2;
}

void CompoundBorder::activateInternalDrawConstraints(const GraphicsPtr g, const Real32& x, const Real32& y , const Real32& Width, const Real32& Height) const
{
	Real32 LeftIn, RightIn, BottomIn, UpperIn;
	getOuterBorder()->getInsets(LeftIn, RightIn, UpperIn, BottomIn);
    getOuterBorder()->activateInternalDrawConstraints(g,x,y,Width,Height);
    getInnerBorder()->activateInternalDrawConstraints(g,x+LeftIn, y+UpperIn, Width-LeftIn-RightIn, Height-UpperIn-BottomIn);
}

bool CompoundBorder::isContained(const Pnt2f& p, const Real32& x, const Real32& y , const Real32& Width, const Real32& Height) const
{
	Real32 LeftIn, RightIn, BottomIn, UpperIn;
	getOuterBorder()->getInsets(LeftIn, RightIn, UpperIn, BottomIn);
    return (getInnerBorder()->isContained(p,x+LeftIn, y+UpperIn, Width-LeftIn-RightIn, Height-UpperIn-BottomIn) ||
            getOuterBorder()->isContained(p,x,y,Width,Height));
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CompoundBorder::CompoundBorder(void) :
    Inherited()
{
}

CompoundBorder::CompoundBorder(const CompoundBorder &source) :
    Inherited(source)
{
}

CompoundBorder::~CompoundBorder(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CompoundBorder::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void CompoundBorder::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump CompoundBorder NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGCOMPOUNDBORDERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCOMPOUNDBORDERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCOMPOUNDBORDERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

