/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGUIForegroundMouseTransformFunctor.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGUIForegroundMouseTransformFunctorBase.cpp file.
// To modify it, please change the .fcd file (OSGUIForegroundMouseTransformFunctor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void UIForegroundMouseTransformFunctor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool UIForegroundMouseTransformFunctor::viewportToRenderingSurface(const Pnt2f& ViewportPoint,
                                                                   const Viewport* TheViewport,
                                                                   Pnt2f& Result) const
{
    Result = ViewportPoint;
    return true;
}

bool UIForegroundMouseTransformFunctor::renderingSurfaceToViewport(const Pnt2f& RenderingSurfacePoint,
                                                                   const Viewport* TheViewport,
                                                                   Pnt2f& Result) const
{
    Result = RenderingSurfacePoint;
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

void UIForegroundMouseTransformFunctor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void UIForegroundMouseTransformFunctor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump UIForegroundMouseTransformFunctor NI" << std::endl;
}

OSG_END_NAMESPACE
