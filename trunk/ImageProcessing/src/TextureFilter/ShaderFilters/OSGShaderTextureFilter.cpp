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
#include <OpenSG/OSGFBOViewport.h>
#include <OpenSG/OSGTextureChunk.h>
#include <OpenSG/OSGSHLChunk.h>
#include <OpenSG/OSGSHLParameterChunk.h>
#include <OpenSG/OSGChunkMaterial.h>


#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGPassiveBackground.h>
#include <OpenSG/OSGMatrixCamera.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGImage.h>
#include <OpenSG/Toolbox/OSGFilledQuadForeground.h>

#include <boost/lexical_cast.hpp>

#include "OSGShaderTextureFilter.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ShaderTextureFilter

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderTextureFilter::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

 bool ShaderTextureFilter::isSource(void) const
 {
     return true;
 }

 bool ShaderTextureFilter::isSink(void) const
 {
     return true;
 }


TextureChunkPtr ShaderTextureFilter::pullTexture(void) const
{
    //Just grab the color texture from the FBO
    return getInternalFBO()->getTextures(0);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/


void ShaderTextureFilter::internalUpdate(RenderActionBase *action, const Vec2f& DrawnSize)
{
    //Grab unused FBO, with the same properties that this Filter requires

    //Update the FBO

    //Determin if the size of the FBO Texture should be changed
    Vec2f NewFBOSize(getFBOSize());
    if(getFBOSize().x() < 0.0f)
    {
        NewFBOSize[0] = DrawnSize.x();
    }
    if(getFBOSize().y() < 0.0f)
    {
        NewFBOSize[1] = DrawnSize.y();
    }
    if(getFBOSize() != NewFBOSize)
    {
        //If the size of the FBO Texture has changed then update it
        ImagePtr TheImage(getInternalFBO()->getTextures(0)->getImage());
        beginEditCP(TheImage, Image::WidthFieldMask | Image::HeightFieldMask);
            TheImage->setWidth(getFBOSize().x());
            TheImage->setHeight(getFBOSize().y());
        endEditCP(TheImage, Image::WidthFieldMask | Image::HeightFieldMask);
    }

    //Update The Material to use to draw the quad
    beginEditCP(_DefaultMat, ChunkMaterial::ChunksFieldMask);
        _DefaultMat->clearChunks();
        //Attach Shader
        _DefaultMat->addChunk(getInternalShader());

        //Attach Shader Uniform Parameters
        _DefaultMat->addChunk(getInternalParameters());

        std::string TexParamName("");
        for(FieldContainerMap::const_iterator MapItor( getInternalSourceFilters().begin() );
            MapItor != getInternalSourceFilters().end();
            ++MapItor)
        {
            TexParamName = std::string("Slot") + boost::lexical_cast<std::string>((*MapItor).first) + std::string("Texture");

            //Update Shader Uniform Parameters
            getInternalParameters()->setUniformParameter(TexParamName.c_str(),(*MapItor).first);

            //Attach Source Textures
            _DefaultMat->addChunk( TextureFilterPtr::dcast((*MapItor).second)->pullTexture() );
        }
    endEditCP(_DefaultMat, ChunkMaterial::ChunksFieldMask);


    //Draw the FBO
    getInternalFBO()->render(action);

}

FBOViewportPtr ShaderTextureFilter::createDefaultFBO(void)
{
    //Create Root
    NodePtr TheRoot = Node::create();
    beginEditCP(TheRoot, Node::CoreFieldMask);
        TheRoot->setCore(Group::create());
    endEditCP(TheRoot, Node::CoreFieldMask);

    //Create Camera
    MatrixCameraPtr TheCamera = MatrixCamera::create();

    //Create Background
    PassiveBackgroundPtr TheBackground = PassiveBackground::create();

    //Create the Material
    _DefaultMat = ChunkMaterial::create();

    //Create Foreground
    //Viewport filled quad that uses the attached material
    FilledQuadForegroundPtr TheFilledQuadForeground = FilledQuadForeground::create();
    beginEditCP(TheFilledQuadForeground, FilledQuadForeground::MaterialFieldMask);
        TheFilledQuadForeground->setMaterial(_DefaultMat);
    endEditCP(TheFilledQuadForeground, FilledQuadForeground::MaterialFieldMask);

    //Create the Image
    ImagePtr TheImage = Image::create();
    TheImage->set(Image::OSG_RGB_PF,1,1);

    //Create the texture
    TextureChunkPtr TheTextureChunk = TextureChunk::create();
    beginEditCP(TheTextureChunk);
        TheTextureChunk->setImage(TheImage);

        TheTextureChunk->setMinFilter(GL_NEAREST);
        TheTextureChunk->setMagFilter(GL_NEAREST);

        TheTextureChunk->setWrapS(GL_CLAMP_TO_EDGE);
        TheTextureChunk->setWrapR(GL_CLAMP_TO_EDGE);

        TheTextureChunk->setScale(false);
        TheTextureChunk->setNPOTMatrixScale(true);
        
        TheTextureChunk->setEnvMode(GL_REPLACE);
    endEditCP(TheTextureChunk);

    //Create FBO
    FBOViewportPtr TheFBO = FBOViewport::create();
    beginEditCP(TheFBO);
        TheFBO->setBackground(TheBackground);
        TheFBO->setRoot(TheRoot);
        TheFBO->setCamera(TheCamera);

        TheFBO->setEnabled(true);
        TheFBO->getTextures().push_back(TheTextureChunk);

        TheFBO->getForegrounds().push_back(TheFilledQuadForeground);

        TheFBO->setStorageWidth(TheTextureChunk->getImage()->getWidth());
        TheFBO->setStorageHeight(TheTextureChunk->getImage()->getHeight());
    endEditCP(TheFBO);
    return TheFBO;
}

SHLChunkPtr ShaderTextureFilter::createDefaultShader(void)
{
    return SHLChunk::create();
}

SHLParameterChunkPtr ShaderTextureFilter::createDefaultParameters(void)
{
    return SHLParameterChunk::create();
}

void ShaderTextureFilter::onCreate(const ShaderTextureFilter *source)
{
    beginEditCP(ShaderTextureFilterPtr(this), ShaderTextureFilter::InternalFBOFieldMask | ShaderTextureFilter::InternalShaderFieldMask | ShaderTextureFilter::InternalParametersFieldMask);
        setInternalFBO(createDefaultFBO());
        setInternalShader(createDefaultShader());
        setInternalParameters(createDefaultParameters());
    endEditCP(ShaderTextureFilterPtr(this), ShaderTextureFilter::InternalFBOFieldMask | ShaderTextureFilter::InternalShaderFieldMask | ShaderTextureFilter::InternalParametersFieldMask);
}

void ShaderTextureFilter::onDestroy(void)
{
}

/*----------------------- constructors & destructors ----------------------*/

ShaderTextureFilter::ShaderTextureFilter(void) :
    Inherited()
{
}

ShaderTextureFilter::ShaderTextureFilter(const ShaderTextureFilter &source) :
    Inherited(source)
{
}

ShaderTextureFilter::~ShaderTextureFilter(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ShaderTextureFilter::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ShaderTextureFilter::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ShaderTextureFilter NI" << std::endl;
}


OSG_END_NAMESPACE

