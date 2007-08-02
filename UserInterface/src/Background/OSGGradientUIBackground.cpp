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

#include "OSGGradientUIBackground.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::GradientUIBackground
UI Gradient Background. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GradientUIBackground::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void GradientUIBackground::draw(const GraphicsPtr g, const Pnt2s& TopLeft, const Pnt2s& BottomRight, const Real32 Opacity) const
{
	if(getAlignment() == HORIZONTAL_ALIGNMENT)
	{
		g->drawQuad(TopLeft, Pnt2s(BottomRight.x(), TopLeft.y()), BottomRight, Pnt2s(TopLeft.x(), BottomRight.y()), getColorStart(), getColorEnd(), getColorEnd(), getColorStart(), Opacity);
	}
	else
	{
		g->drawQuad(TopLeft, Pnt2s(BottomRight.x(), TopLeft.y()), BottomRight, Pnt2s(TopLeft.x(), BottomRight.y()), getColorStart(), getColorStart(), getColorEnd(), getColorEnd(), Opacity);
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GradientUIBackground::GradientUIBackground(void) :
    Inherited()
{
}

GradientUIBackground::GradientUIBackground(const GradientUIBackground &source) :
    Inherited(source)
{
}

GradientUIBackground::~GradientUIBackground(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GradientUIBackground::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void GradientUIBackground::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump GradientUIBackground NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGGRADIENTUIBACKGROUNDBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGGRADIENTUIBACKGROUNDBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGGRADIENTUIBACKGROUNDFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

