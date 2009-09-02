/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
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

#define OSG_COMPILETOOLBOXLIB

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSHLParameterChunk.h>
#include <OpenSG/OSGSHLChunk.h>

#include "OSGLambertMaterial.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::LambertMaterial

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LambertMaterial::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void LambertMaterial::updateShaderCode(void)
{
}

void LambertMaterial::updateShaderParameters(void)
{
}

void LambertMaterial::updateChunks(void)
{
    updateShaderCode();
    updateShaderParameters();
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

LambertMaterial::LambertMaterial(void) :
    Inherited()
{
}

LambertMaterial::LambertMaterial(const LambertMaterial &source) :
    Inherited(source)
{
}

LambertMaterial::~LambertMaterial(void)
{
}

/*----------------------------- class specific ----------------------------*/

void LambertMaterial::onCreate(const LambertMaterial *source)
{
    //Shader Parameter Chunk
    SHLParameterChunkPtr TheSHLParameterChunk = SHLParameterChunk::create();
    //Shader Chunk
    SHLChunkPtr TheSHLChunk = SHLChunk::create();
}

void LambertMaterial::onDestroy(void)
{
}

void LambertMaterial::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
    if((whichField & ColorFieldMask) ||
        (whichField & TransparencyFieldMask) ||
        (whichField & AmbientColorFieldMask) ||
        (whichField & IncandescenceFieldMask) ||
        (whichField & BumpDepthFieldMask) ||
        (whichField & DiffuseFieldMask) ||
        (whichField & TransleucenceFieldMask) ||
        (whichField & TransleucenceDepthFieldMask) ||
        (whichField & TransleucenceFocusFieldMask))
    {
        updateShaderParameters();
    //Blend Chunk
    //Polygon Chunk
    //Depth Chunk
    //Texture Chunks
    //Shader Parameter Chunk
    //Shader Chunk
    }
}

void LambertMaterial::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump LambertMaterial NI" << std::endl;
}


OSG_END_NAMESPACE

