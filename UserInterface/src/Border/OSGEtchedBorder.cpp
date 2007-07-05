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

void EtchedBorder::draw(const GraphicsPtr g, const Int16 x, const Int16 y , const UInt16 Width, const UInt16 Height, const Real32 Opacity) const
{
	Pnt2s TopLeft = Pnt2s(x, y);
	Pnt2s BottomLeft = Pnt2s(x, y + Height);
	Pnt2s TopRight = Pnt2s(x + Width, y);
	Pnt2s BottomRight = Pnt2s(x + Width, y + Height);
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

	g->drawRect(Pnt2s(x+getWidth(), y+getWidth()/2.0), Pnt2s(x+Width-getWidth(), y+getWidth()), BottomColor, Opacity);
	g->drawRect(Pnt2s(x,y), Pnt2s(x+Width-getWidth(), y+getWidth()/2.0), TopColor, Opacity);
	//Left	
	g->drawRect(Pnt2s(x, y+getWidth()/2.0), Pnt2s(x+getWidth()/2.0, y+Height-getWidth()), TopColor, Opacity);
	g->drawRect(Pnt2s(x+getWidth()/2.0, y+getWidth()/2.0), Pnt2s(x+getWidth(), y+Height-getWidth()), BottomColor, Opacity);
	//Bottom
	g->drawRect(Pnt2s(x, y+Height-getWidth()), Pnt2s(x+Width-getWidth(), y+Height-getWidth()/2.0), TopColor, Opacity);
	g->drawRect(Pnt2s(x, y+Height-getWidth()/2.0), Pnt2s(x+Width-getWidth()/2.0, y+Height), BottomColor, Opacity);
	//Right
	g->drawRect(Pnt2s(x+Width-getWidth(), y), Pnt2s(x+Width-getWidth()/2.0, y+Height-getWidth()/2.0), TopColor, Opacity);
	g->drawRect(Pnt2s(x+Width-getWidth()/2.0, y), Pnt2s(x+Width, y+Height), BottomColor, Opacity);

}

void EtchedBorder::getInsets(UInt16& Left, UInt16& Right,UInt16& Top,UInt16& Bottom) const
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

