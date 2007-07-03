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

#include "OSGMatteBorder.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::MatteBorder
UI Matte Border. Creates a matte-look border using a solid color or Material. (The difference between this border and a line border is that you can specify the individual border dimensions.) 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MatteBorder::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void MatteBorder::draw(const GraphicsPtr g, const Int16 x, const Int16 y , const UInt16 Width, const UInt16 Height, const Real32 Opacity) const
{
	//x, y is upper left point
	
	//Top
	g->drawRect(Pnt2s(x,y), Pnt2s(x+Width, y+getTopWidth()), getColor(), Opacity);
	//Left
	g->drawRect(Pnt2s(x,y+getTopWidth()), Pnt2s(x+getLeftWidth(), y+getTopWidth()+Height-getBottomWidth()), getColor(), Opacity);
	//Right
	g->drawRect(Pnt2s(x+Width-getRightWidth(), y+getTopWidth()), Pnt2s(x+Width, y+getTopWidth()+Height-getBottomWidth()), getColor(), Opacity);
	//Bottom
	g->drawRect(Pnt2s(x, y+Height-getBottomWidth()), Pnt2s(x+Width, y+Height), getColor(), Opacity);

}

void MatteBorder::getInsets(UInt16& Left, UInt16& Right,UInt16& Top,UInt16& Bottom) const
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

MatteBorder::MatteBorder(void) :
    Inherited()
{
}

MatteBorder::MatteBorder(const MatteBorder &source) :
    Inherited(source)
{
}

MatteBorder::~MatteBorder(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MatteBorder::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void MatteBorder::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump MatteBorder NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGMATTEBORDERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGMATTEBORDERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGMATTEBORDERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

