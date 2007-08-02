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
#include <OpenSG/OSGTextLayoutParam.h>
#include <OpenSG/OSGTextLayoutResult.h>
#include <OpenSG/OSGTextureChunk.h>

#include "OSGTextUIDrawObject.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TextUIDrawObject
A UI TextUIDrawObject. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TextUIDrawObject::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void TextUIDrawObject::draw(const GraphicsPtr Graphics) const
{
	Graphics->drawText(getPosition(), getText(), getFont(), getColor(), getOpacity());
}

void TextUIDrawObject::getBounds(Pnt2s& TopLeft, Pnt2s& BottomRight) const
{
   TextLayoutParam layoutParam;
   layoutParam.spacing = 1.1;
   layoutParam.majorAlignment = TextLayoutParam::ALIGN_BEGIN;
   layoutParam.minorAlignment = TextLayoutParam::ALIGN_BEGIN;
 
   TextLayoutResult layoutResult;
   getFont()->layout(getText(), layoutParam, layoutResult);
   TopLeft = getPosition();
   BottomRight = getPosition()+Vec2s(layoutResult.textBounds.x()*getFont()->getSize(),layoutResult.textBounds.y()*getFont()->getSize());
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TextUIDrawObject::TextUIDrawObject(void) :
    Inherited()
{
}

TextUIDrawObject::TextUIDrawObject(const TextUIDrawObject &source) :
    Inherited(source)
{
}

TextUIDrawObject::~TextUIDrawObject(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TextUIDrawObject::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void TextUIDrawObject::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump TextUIDrawObject NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGTEXTUIDRAWOBJECTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGTEXTUIDRAWOBJECTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTEXTUIDRAWOBJECTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

