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

#include "OSGEtchedBorder.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::EtchedBorder
UI Etched Border. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void EtchedBorder::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void EtchedBorder::draw(const GraphicsPtr g, const Real32 x, const Real32 y , const Real32 Width, const Real32 Height, const Real32 Opacity) const
{
	Pnt2f TopLeft = Pnt2f(x, y);
	Pnt2f BottomLeft = Pnt2f(x, y + Height);
	Pnt2f TopRight = Pnt2f(x + Width, y);
	Pnt2f BottomRight = Pnt2f(x + Width, y + Height);
	Color4f TopColor, BottomColor;
	if(getRaised())
	{
		TopColor = getHighlight();
		BottomColor = getShadow();
	}
	else
	{
		TopColor = getShadow();
		BottomColor = getHighlight();
	}
	//Top

	g->drawRect(Pnt2f(x+getWidth(), y+getWidth()/2.0), Pnt2f(x+Width-getWidth(), y+getWidth()), BottomColor, Opacity);
	g->drawRect(Pnt2f(x,y), Pnt2f(x+Width-getWidth(), y+getWidth()/2.0), TopColor, Opacity);
	//Left	
	g->drawRect(Pnt2f(x, y+getWidth()/2.0), Pnt2f(x+getWidth()/2.0, y+Height-getWidth()), TopColor, Opacity);
	g->drawRect(Pnt2f(x+getWidth()/2.0, y+getWidth()/2.0), Pnt2f(x+getWidth(), y+Height-getWidth()), BottomColor, Opacity);
	//Bottom
	g->drawRect(Pnt2f(x, y+Height-getWidth()), Pnt2f(x+Width-getWidth(), y+Height-getWidth()/2.0), TopColor, Opacity);
	g->drawRect(Pnt2f(x, y+Height-getWidth()/2.0), Pnt2f(x+Width-getWidth()/2.0, y+Height), BottomColor, Opacity);
	//Right
	g->drawRect(Pnt2f(x+Width-getWidth(), y), Pnt2f(x+Width-getWidth()/2.0, y+Height-getWidth()/2.0), TopColor, Opacity);
	g->drawRect(Pnt2f(x+Width-getWidth()/2.0, y), Pnt2f(x+Width, y+Height), BottomColor, Opacity);

}

void EtchedBorder::getInsets(Real32& Left, Real32& Right,Real32& Top,Real32& Bottom) const
{
	Left=Right=Top=Bottom=getWidth();
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

EtchedBorder::EtchedBorder(void) :
    Inherited()
{
}

EtchedBorder::EtchedBorder(const EtchedBorder &source) :
    Inherited(source)
{
}

EtchedBorder::~EtchedBorder(void)
{
}

/*----------------------------- class specific ----------------------------*/

void EtchedBorder::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void EtchedBorder::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump EtchedBorder NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGETCHEDBORDERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGETCHEDBORDERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGETCHEDBORDERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

