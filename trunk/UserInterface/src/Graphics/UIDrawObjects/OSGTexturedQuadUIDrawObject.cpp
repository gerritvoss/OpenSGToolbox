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

#include "OSGTexturedQuadUIDrawObject.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TexturedQuadUIDrawObject
A UI TexturedQuadUIDrawObject. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TexturedQuadUIDrawObject::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void TexturedQuadUIDrawObject::draw(const GraphicsPtr Graphics) const
{
    //TODO: add Color Field to TexturedQuadUIDrawObject
	Graphics->drawQuad(getPoint1(),getPoint2(),getPoint3(),getPoint4(),
                       getTexCoord1(), getTexCoord2(), getTexCoord3(), getTexCoord4(),
                       Color4f(1.0f,1.0f,1.0f,1.0f), getTexture(),
                       getOpacity());
}

void TexturedQuadUIDrawObject::getBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const
{
   TopLeft.setValues(
       osgMin(osgMin(osgMin(getPoint1().x(), getPoint2().x()),getPoint3().x()),getPoint4().x()),
       osgMin(osgMin(osgMin(getPoint1().y(), getPoint2().y()),getPoint3().y()),getPoint4().y()));
   
   BottomRight.setValues(
       osgMax(osgMax(osgMax(getPoint1().x(), getPoint2().x()),getPoint3().x()),getPoint4().x()),
       osgMax(osgMax(osgMax(getPoint1().y(), getPoint2().y()),getPoint3().y()),getPoint4().y()));
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TexturedQuadUIDrawObject::TexturedQuadUIDrawObject(void) :
    Inherited()
{
}

TexturedQuadUIDrawObject::TexturedQuadUIDrawObject(const TexturedQuadUIDrawObject &source) :
    Inherited(source)
{
}

TexturedQuadUIDrawObject::~TexturedQuadUIDrawObject(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TexturedQuadUIDrawObject::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void TexturedQuadUIDrawObject::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump TexturedQuadUIDrawObject NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGTEXTUREDQUADUIDRAWOBJECTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGTEXTUREDQUADUIDRAWOBJECTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTEXTUREDQUADUIDRAWOBJECTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

