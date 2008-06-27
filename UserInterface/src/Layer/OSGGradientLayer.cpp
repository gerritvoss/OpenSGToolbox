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

#include "OSGGradientLayer.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::GradientLayer
UI Gradient Background. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GradientLayer::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void GradientLayer::draw(const GraphicsPtr TheGraphics, const Pnt2f& TopLeft, const Pnt2f& BottomRight, const Real32 Opacity) const
{
	if(getColors().size() == getPositions().size())
	{
		UInt32 MajorAxisIndex, MinorAxisIndex;
		if(getOrientation() == HORIZONTAL_ORIENTATION)
		{
			MajorAxisIndex = 0;
		}
		else
		{
			MajorAxisIndex = 1;
		}
		MinorAxisIndex = (MajorAxisIndex+1)%2;

		if(getColors().size() == 1)
		{
			TheGraphics->drawQuad(TopLeft, Pnt2f(BottomRight.x(), TopLeft.y()), BottomRight, Pnt2f(TopLeft.x(), BottomRight.y()), getColors()[0], getColors()[0], getColors()[0], getColors()[0], Opacity);
		}
		else
		{
			Pnt2f QuadTopLeft(TopLeft), QuadBottomRight(BottomRight);
			for(UInt32 i(1) ; i<getColors().size(); ++i)
			{
				if(getPositions()[i] <=1.0)
				{
					QuadBottomRight[MajorAxisIndex] = TopLeft[MajorAxisIndex] + (getPositions()[i]* (BottomRight[MajorAxisIndex] - TopLeft[MajorAxisIndex]));
				}
				else
				{
					QuadBottomRight[MajorAxisIndex] = getPositions()[i];
				}

				TheGraphics->drawQuad(QuadTopLeft, Pnt2f(QuadBottomRight.x(), QuadTopLeft.y()), QuadBottomRight, Pnt2f(QuadTopLeft.x(), QuadBottomRight.y()), getColors()[i-1], getColors()[i], getColors()[i], getColors()[i-1], Opacity);

				QuadTopLeft[MajorAxisIndex] = QuadBottomRight[MajorAxisIndex];
			}
		}
	}
	/*if(getOrientation() == GradientLayer::HORIZONTAL_ORIENTATION)
	{
		TheGraphics->drawQuad(TopLeft, Pnt2f(BottomRight.x(), TopLeft.y()), BottomRight, Pnt2f(TopLeft.x(), BottomRight.y()), getColorStart(), getColorEnd(), getColorEnd(), getColorStart(), Opacity);
	}
	else
	{
		TheGraphics->drawQuad(TopLeft, Pnt2f(BottomRight.x(), TopLeft.y()), BottomRight, Pnt2f(TopLeft.x(), BottomRight.y()), getColorStart(), getColorStart(), getColorEnd(), getColorEnd(), Opacity);
	}*/
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GradientLayer::GradientLayer(void) :
    Inherited()
{
}

GradientLayer::GradientLayer(const GradientLayer &source) :
    Inherited(source)
{
}

GradientLayer::~GradientLayer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GradientLayer::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void GradientLayer::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump GradientLayer NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGGRADIENTLAYERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGGRADIENTLAYERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGGRADIENTLAYERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

