/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox ImageProcessing                      *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#define OSG_COMPILEIMAGEPROCESSINGLIB

#include <OpenSG/OSGConfig.h>

#include "OSGFBOSourceTextureFilter.h"

#include <OpenSG/OSGFBOViewport.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FBOSourceTextureFilter

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FBOSourceTextureFilter::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

TextureChunkPtr FBOSourceTextureFilter::pullTexture(void) const
{
    return getFBO()->getTextures(getTextureIndex());
}

void FBOSourceTextureFilter::internalUpdate(RenderActionBase *action, const Vec2f& DrawnSize)
{
    getFBO()->render(action);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FBOSourceTextureFilter::FBOSourceTextureFilter(void) :
    Inherited()
{
}

FBOSourceTextureFilter::FBOSourceTextureFilter(const FBOSourceTextureFilter &source) :
    Inherited(source)
{
}

FBOSourceTextureFilter::~FBOSourceTextureFilter(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FBOSourceTextureFilter::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void FBOSourceTextureFilter::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump FBOSourceTextureFilter NI" << std::endl;
}


OSG_END_NAMESPACE

