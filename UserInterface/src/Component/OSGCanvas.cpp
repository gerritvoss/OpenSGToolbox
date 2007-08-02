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

#include "OSGCanvas.h"
#include "Text/OSGFont.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Canvas
A UI Canvas.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Canvas::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Canvas::drawInternal(const GraphicsPtr TheGraphics) const
{

   Pnt2s TopLeft, BottomRight;
   getInsideBorderBounds(TopLeft, BottomRight);

	/*MFPnt2s polygon;
	polygon.addValue(Pnt2s(120,120));
	polygon.addValue(Pnt2s(120,0));
	polygon.addValue(Pnt2s(180,120));
	polygon.addValue(Pnt2s(170,230));
	polygon.addValue(Pnt2s(130,180));

	TheGraphics->drawPolygon( polygon, Color4f(0.0f,1.0f,1.0f,0.5));*/

   //TheGraphics->drawLine(Pnt2s( 50,50), Pnt2s(150,150),5.0, Color4f(1.0,0.0,0.0,1.0),1.0);
   
   TheGraphics->drawDisc(Pnt2s(100,100), 50,50, 0.0, 3.14159, 24, Color4f(0.0,0.0,1.0,1.0), Color4f(0.0,0.0,1.0,1.0),1.0);
   TheGraphics->drawArc(Pnt2s(100,100), 50,50, 0.0, 3.14159,3.0, 24, Color4f(1.0,1.0,1.0,1.0),1.0);
   //TheGraphics->drawText(Pnt2s(10,150), std::string("Eat my shorts foo!"), TheFont, Color4f(1.0,0.0,0.0,1.0), 1.0);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Canvas::Canvas(void) :
    Inherited()
{
}

Canvas::Canvas(const Canvas &source) :
    Inherited(source)
{
}

Canvas::~Canvas(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Canvas::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void Canvas::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Canvas NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGCANVASBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCANVASBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCANVASFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

