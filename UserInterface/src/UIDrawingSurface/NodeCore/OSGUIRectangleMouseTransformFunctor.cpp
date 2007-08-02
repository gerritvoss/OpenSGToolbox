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
#include <OpenSG/OSGLine.h>
#include <OpenSG/OSGVector.h>
#include <OpenSG/OSGMatrix.h>
#include <OpenSG/OSGCamera.h>

#include "OSGUIRectangleMouseTransformFunctor.h"
#include "OSGUIRectangle.h"
#include "Util/OSGLineUtils.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::UIRectangleMouseTransformFunctor
A UI UIRectangleMouseTransformFunctor. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void UIRectangleMouseTransformFunctor::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool UIRectangleMouseTransformFunctor::viewportToRenderingSurface(const Pnt2s& ViewportPoint,
		                                    ViewportPtr TheViewport,
		                                        Pnt2s& Result) const
{
	//Get Viewport to View Space line
	Line l;
	if( !TheViewport->getCamera()->calcViewRay( l, ViewportPoint.x(), ViewportPoint.y(), *TheViewport ) )
	{
		return false;
	}

	//Transform Line to UIRectangle Space
	Matrix m ;
	getParent()->accumulateMatrix(m);

    m.invert();

    Pnt3f pos;
    Vec3f dir;

    m.multFullMatrixPnt(l.getPosition (), pos);
    m.multMatrixVec    (l.getDirection(), dir);

	l.setValue(pos, dir);
    //ia->scale(dir.length());

	//Intersect the Line with the UIRectangle quad
	Real32 t;
	if(!intersectLineRect(l,getParent()->getPoint(),
		getParent()->getPoint() + Vec3f(getParent()->getWidth(),0,0),
		getParent()->getPoint() + Vec3f(getParent()->getWidth(),getParent()->getHeight(),0),
		getParent()->getPoint() + Vec3f(0,getParent()->getHeight(),0)
		,t))
	{
		return false;
	}

	//Return the point on the quad of the intersection if there was one
	Result.setValues(l.getPosition().x() + t*l.getDirection().x() - getParent()->getPoint().x(), 
		getParent()->getHeight() - l.getPosition().y() - t*l.getDirection().y() + getParent()->getPoint().y());
	return true;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

UIRectangleMouseTransformFunctor::UIRectangleMouseTransformFunctor(void) :
    Inherited()
{
}

UIRectangleMouseTransformFunctor::UIRectangleMouseTransformFunctor(const UIRectangleMouseTransformFunctor &source) :
    Inherited(source)
{
}

UIRectangleMouseTransformFunctor::~UIRectangleMouseTransformFunctor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void UIRectangleMouseTransformFunctor::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void UIRectangleMouseTransformFunctor::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump UIRectangleMouseTransformFunctor NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGUIRECTANGLEMOUSETRANSFORMFUNCTORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGUIRECTANGLEMOUSETRANSFORMFUNCTORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGUIRECTANGLEMOUSETRANSFORMFUNCTORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

