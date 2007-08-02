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

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGUIForegroundMouseTransformFunctor.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::UIForegroundMouseTransformFunctor
A UI UIDrawingSurfaceMouseTransformFunctor. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void UIForegroundMouseTransformFunctor::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool UIForegroundMouseTransformFunctor::viewportToRenderingSurface(const Pnt2s& ViewportPoint,
		                                    ViewportPtr TheViewport,
		                                        Pnt2s& Result) const
{
	Result = ViewportPoint;
	return true;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

UIForegroundMouseTransformFunctor::UIForegroundMouseTransformFunctor(void) :
    Inherited()
{
}

UIForegroundMouseTransformFunctor::UIForegroundMouseTransformFunctor(const UIForegroundMouseTransformFunctor &source) :
    Inherited(source)
{
}

UIForegroundMouseTransformFunctor::~UIForegroundMouseTransformFunctor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void UIForegroundMouseTransformFunctor::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void UIForegroundMouseTransformFunctor::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump UIForegroundMouseTransformFunctor NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGUIFOREGROUNDMOUSETRANSFORMFUNCTORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGUIFOREGROUNDMOUSETRANSFORMFUNCTORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGUIFOREGROUNDMOUSETRANSFORMFUNCTORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

