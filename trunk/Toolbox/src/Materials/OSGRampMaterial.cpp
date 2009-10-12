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

#include "OSGRampMaterial.h"
#include <OpenSG/OSGSHLParameterChunk.h>
#include <OpenSG/OSGSHLChunk.h>
#include <OpenSG/OSGTextureChunk.h>
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGShaderParameterInt.h>
#include <OpenSG/OSGShaderParameterReal.h>
#include <OpenSG/OSGShaderParameterMReal.h>
#include <OpenSG/OSGShaderParameterVec3f.h>
#include <OpenSG/OSGShaderParameterMVec3f.h>
#include <OpenSG/OSGShaderParameterVec4f.h>

#include <OpenSG/OSGVecFieldDataType.h>

#include "OSGMaterialLibrary.h"
#include <boost/lexical_cast.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::RampMaterial

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void RampMaterial::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool RampMaterial::isTransparent(void) const
{
    return (getTransparencyTexture() != NullFC || getTransparencies().size() > 0);
}

void RampMaterial::updateShaderCode(void)
{
    beginEditCP(getShader(), SHLChunk::VertexProgramFieldMask | SHLChunk::FragmentProgramFieldMask);
        getShader()->setVertexProgram(generateVertexCode());
        getShader()->setFragmentProgram(generateFragmentCode());
    endEditCP(getShader(), SHLChunk::VertexProgramFieldMask | SHLChunk::FragmentProgramFieldMask);
}

void RampMaterial::internalCreateShaderParameters(void)
{
    //Color
    if(getColorTexture() == NullFC)
    {
        if(getColors().size() <= 1)  // 0-1 Colors
        {
            ShaderParameterVec3fPtr ColorParam = ShaderParameterVec3f::create();
            ColorParam->setName("Color");
            getParameters()->getParameters().push_back(ColorParam);
        }
        else // > 1 Colors
        {
            ShaderParameterMVec3fPtr ColorsParam = ShaderParameterMVec3f::create();
            ColorsParam->setName("Colors");
            getParameters()->getParameters().push_back(ColorsParam);
            
            ShaderParameterMRealPtr ColorPositionsParam = ShaderParameterMReal::create();
            ColorPositionsParam->setName("ColorPositions");
            getParameters()->getParameters().push_back(ColorPositionsParam);
        }
    }
    else // Color Texture
    {
        ShaderParameterIntPtr ColorTexParam = ShaderParameterInt::create();
        ColorTexParam->setName("ColorTexture");
        getParameters()->getParameters().push_back(ColorTexParam);
    }

    //Transparency
    if(getTransparencyTexture() == NullFC)
    {
        if(getTransparencies().size() <= 1)  // 0-1 Transparencies
        {
            ShaderParameterVec3fPtr TransparencyParam = ShaderParameterVec3f::create();
            TransparencyParam->setName("Transparency");
            getParameters()->getParameters().push_back(TransparencyParam);
        }
        else // > 1 Transparencies
        {
            ShaderParameterMVec3fPtr TransparenciesParam = ShaderParameterMVec3f::create();
            TransparenciesParam->setName("Transparencies");
            getParameters()->getParameters().push_back(TransparenciesParam);
            
            ShaderParameterMRealPtr TransparencyPositionsParam = ShaderParameterMReal::create();
            TransparencyPositionsParam->setName("TransparencyPositions");
            getParameters()->getParameters().push_back(TransparencyPositionsParam);
        }
    }
    else // Transparency Texture
    {
        ShaderParameterIntPtr TransparencyTexParam = ShaderParameterInt::create();
        TransparencyTexParam->setName("TransparencyTexture");
        getParameters()->getParameters().push_back(TransparencyTexParam);
    }

    //AmbientColor
    if(getAmbientColorTexture() == NullFC)
    {
        ShaderParameterVec3fPtr AmbientColorParam = ShaderParameterVec3f::create();
        AmbientColorParam->setName("AmbientColor");
        getParameters()->getParameters().push_back(AmbientColorParam);
    }
    else
    {
        ShaderParameterIntPtr AmbientColorTexParam = ShaderParameterInt::create();
        AmbientColorTexParam->setName("AmbientColorTexture");
        getParameters()->getParameters().push_back(AmbientColorTexParam);
    }

    //Incandescence
    if(getIncandescenceTexture() == NullFC)
    {
        if(getIncandescences().size() <= 1)  // 0-1 Incandescences
        {
            ShaderParameterVec3fPtr IncandescenceParam = ShaderParameterVec3f::create();
            IncandescenceParam->setName("Incandescence");
            getParameters()->getParameters().push_back(IncandescenceParam);
        }
        else // > 1 Incandescences
        {
            ShaderParameterMVec3fPtr IncandescencesParam = ShaderParameterMVec3f::create();
            IncandescencesParam->setName("Incandescences");
            getParameters()->getParameters().push_back(IncandescencesParam);
            
            ShaderParameterMRealPtr IncandescencePositionsParam = ShaderParameterMReal::create();
            IncandescencePositionsParam->setName("IncandescencePositions");
            getParameters()->getParameters().push_back(IncandescencePositionsParam);
        }
    }
    else // Incandescence Texture
    {
        ShaderParameterIntPtr IncandescenceTexParam = ShaderParameterInt::create();
        IncandescenceTexParam->setName("IncandescenceTexture");
        getParameters()->getParameters().push_back(IncandescenceTexParam);
    }

    //Normal
    if(getNormalMapTexture() != NullFC)
    {
        ShaderParameterIntPtr NormalTexParam = ShaderParameterInt::create();
        NormalTexParam->setName("NormalTexture");
        getParameters()->getParameters().push_back(NormalTexParam);

        //Bump Depth
        //if(getBumpDepthTexture() == NullFC)
        //{
            //ShaderParameterRealPtr BumpDepthParam = ShaderParameterReal::create();
            //BumpDepthParam->setName("BumpDepth");
            //getParameters()->getParameters().push_back(BumpDepthParam);
        //}
        //else
        //{
            //ShaderParameterIntPtr BumpDepthTexParam = ShaderParameterInt::create();
            //BumpDepthTexParam->setName("BumpDepthTexture");
            //getParameters()->getParameters().push_back(BumpDepthTexParam);
        //}
    }

    //Diffuse
    if(getDiffuseTexture() == NullFC)
    {
        ShaderParameterRealPtr DiffuseParam = ShaderParameterReal::create();
        DiffuseParam->setName("Diffuse");
        getParameters()->getParameters().push_back(DiffuseParam);
    }
    else
    {
        ShaderParameterIntPtr DiffuseTexParam = ShaderParameterInt::create();
        DiffuseTexParam->setName("DiffuseTexture");
        getParameters()->getParameters().push_back(DiffuseTexParam);
    }

    //Specularity
    if(getSpecularityTexture() == NullFC)
    {
        ShaderParameterRealPtr SpecularityParam = ShaderParameterReal::create();
        SpecularityParam->setName("Specularity");
        getParameters()->getParameters().push_back(SpecularityParam);
    }
    else
    {
        ShaderParameterIntPtr SpecularityTexParam = ShaderParameterInt::create();
        SpecularityTexParam->setName("SpecularityTexture");
        getParameters()->getParameters().push_back(SpecularityTexParam);
    }

    //SpecularEccentricity
    if(getSpecularEccentricityTexture() == NullFC)
    {
        ShaderParameterRealPtr SpecularEccentricityParam = ShaderParameterReal::create();
        SpecularEccentricityParam->setName("SpecularEccentricity");
        getParameters()->getParameters().push_back(SpecularEccentricityParam);
    }
    else
    {
        ShaderParameterIntPtr SpecularEccentricityTexParam = ShaderParameterInt::create();
        SpecularEccentricityTexParam->setName("SpecularEccentricityTexture");
        getParameters()->getParameters().push_back(SpecularEccentricityTexParam);
    }
    
    //SpecularColor
    if(getSpecularColorTexture() == NullFC)
    {
        if(getSpecularColors().size() <= 1)  // 0-1 SpecularColors
        {
            ShaderParameterVec3fPtr SpecularColorParam = ShaderParameterVec3f::create();
            SpecularColorParam->setName("SpecularColor");
            getParameters()->getParameters().push_back(SpecularColorParam);
        }
        else // > 1 SpecularColors
        {
            ShaderParameterMVec3fPtr SpecularColorsParam = ShaderParameterMVec3f::create();
            SpecularColorsParam->setName("SpecularColors");
            getParameters()->getParameters().push_back(SpecularColorsParam);
            
            ShaderParameterMRealPtr SpecularColorPositionsParam = ShaderParameterMReal::create();
            SpecularColorPositionsParam->setName("SpecularColorPositions");
            getParameters()->getParameters().push_back(SpecularColorPositionsParam);
        }
    }
    else // SpecularColor Texture
    {
        ShaderParameterIntPtr SpecularColorTexParam = ShaderParameterInt::create();
        SpecularColorTexParam->setName("SpecularColorTexture");
        getParameters()->getParameters().push_back(SpecularColorTexParam);
    }
    
    //SpecularRolloff
    if(getSpecularRolloffTexture() == NullFC)
    {
        if(getSpecularRolloffs().size() <= 1)  // 0-1 SpecularRolloffs
        {
            ShaderParameterRealPtr SpecularRolloffParam = ShaderParameterReal::create();
            SpecularRolloffParam->setName("SpecularRolloff");
            getParameters()->getParameters().push_back(SpecularRolloffParam);
        }
        else // > 1 SpecularRolloffs
        {
            ShaderParameterMRealPtr SpecularRolloffsParam = ShaderParameterMReal::create();
            SpecularRolloffsParam->setName("SpecularRolloffs");
            getParameters()->getParameters().push_back(SpecularRolloffsParam);
            
            ShaderParameterMRealPtr SpecularRolloffPositionsParam = ShaderParameterMReal::create();
            SpecularRolloffPositionsParam->setName("SpecularRolloffPositions");
            getParameters()->getParameters().push_back(SpecularRolloffPositionsParam);
        }
    }
    else // SpecularRolloff Texture
    {
        ShaderParameterIntPtr SpecularRolloffTexParam = ShaderParameterInt::create();
        SpecularRolloffTexParam->setName("SpecularRolloffTexture");
        getParameters()->getParameters().push_back(SpecularRolloffTexParam);
    }
}

void RampMaterial::createShaderParameters(void)
{
    beginEditCP(getParameters(), SHLParameterChunk::ParametersFieldMask);
        getParameters()->getParameters().clear();

        internalCreateShaderParameters();
    endEditCP(getParameters(), SHLParameterChunk::ParametersFieldMask);
}

void RampMaterial::internalUpdateShaderParameters(UInt8& NumTextures, UInt8& ParamIndex)
{
    //Color
    if(getColorTexture() == NullFC)
    {
        if(getColors().size() == 0)  // 0 Colors
        {
            ShaderParameterVec3fPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(Vec3f(0.0,0.0,0.0));
            ++ParamIndex;
        }
        else if(getColors().size() == 1)  // 1 Color
        {
            ShaderParameterVec3fPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(Vec3f(getColors().front().getValuesRGB()));
            ++ParamIndex;
        }
        else // > 1 Colors
        {
            ShaderParameterMVec3fPtr::dcast(getParameters()->getParameters(ParamIndex))->getValue().clear();
            for(UInt32 i(0) ; i<getColors().size() ; ++i)
            {
                ShaderParameterMVec3fPtr::dcast(getParameters()->getParameters(ParamIndex))->getValue().push_back(Vec3f(getColors(i).getValuesRGB()));
            }
            ++ParamIndex;

            ShaderParameterMRealPtr::dcast(getParameters()->getParameters(ParamIndex))->getValue().setValues(getColorPositions());
            ++ParamIndex;
        }
    }
    else // Color Texture
    {
        ShaderParameterIntPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(NumTextures);
        ++NumTextures;
        ++ParamIndex;
    }
    
    //Transparency
    if(getTransparencyTexture() == NullFC)
    {
        if(getTransparencies().size() == 0)  // 0 Transparencies
        {
            ShaderParameterVec3fPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(Vec3f(1.0,1.0,1.0));
            ++ParamIndex;
        }
        else if(getTransparencies().size() == 1)  // 1 Transparency
        {
            ShaderParameterVec3fPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(Vec3f(getTransparencies().front().getValuesRGB()));
            ++ParamIndex;
        }
        else // > 1 Transparencies
        {
            ShaderParameterMVec3fPtr::dcast(getParameters()->getParameters(ParamIndex))->getValue().clear();
            for(UInt32 i(0) ; i<getTransparencies().size() ; ++i)
            {
                ShaderParameterMVec3fPtr::dcast(getParameters()->getParameters(ParamIndex))->getValue().push_back(Vec3f(getTransparencies(i).getValuesRGB()));
            }
            ++ParamIndex;

            ShaderParameterMRealPtr::dcast(getParameters()->getParameters(ParamIndex))->getValue().setValues(getTransparencyPositions());
            ++ParamIndex;
        }
    }
    else // Transparency Texture
    {
        ShaderParameterIntPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(NumTextures);
        ++NumTextures;
        ++ParamIndex;
    }

    //AmbientColor
    if(getAmbientColorTexture() == NullFC)
    {
        ShaderParameterVec3fPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(Vec3f(getAmbientColor().getValuesRGB()));
        ++ParamIndex;
    }
    else
    {
        ShaderParameterIntPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(NumTextures);
        ++NumTextures;
        ++ParamIndex;
    }

    //Incandescence
    if(getIncandescenceTexture() == NullFC)
    {
        if(getIncandescences().size() == 0)  // 0 Incandescences
        {
            ShaderParameterVec3fPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(Vec3f(0.0,0.0,0.0));
            ++ParamIndex;
        }
        else if(getIncandescences().size() == 1)  // 1 Incandescence
        {
            ShaderParameterVec3fPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(Vec3f(getIncandescences().front().getValuesRGB()));
            ++ParamIndex;
        }
        else // > 1 Incandescences
        {
            ShaderParameterMVec3fPtr::dcast(getParameters()->getParameters(ParamIndex))->getValue().clear();
            for(UInt32 i(0) ; i<getIncandescences().size() ; ++i)
            {
                ShaderParameterMVec3fPtr::dcast(getParameters()->getParameters(ParamIndex))->getValue().push_back(Vec3f(getIncandescences(i).getValuesRGB()));
            }
            ++ParamIndex;

            ShaderParameterMRealPtr::dcast(getParameters()->getParameters(ParamIndex))->getValue().setValues(getIncandescencePositions());
            ++ParamIndex;
        }
    }
    else // Incandescence Texture
    {
        ShaderParameterIntPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(NumTextures);
        ++NumTextures;
        ++ParamIndex;
    }

    //Normal
    if(getNormalMapTexture() != NullFC)
    {
        ShaderParameterIntPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(NumTextures);
        ++NumTextures;
        ++ParamIndex;

        //Bump Depth
        //if(getBumpDepthTexture() == NullFC)
        //{
            //ShaderParameterRealPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(getBumpDepth());
            //++ParamIndex;
        //}
        //else
        //{
            //ShaderParameterIntPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(NumTextures);
            //++NumTextures;
            //++ParamIndex;
        //}
    }

    //Diffuse
    if(getDiffuseTexture() == NullFC)
    {
        ShaderParameterRealPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(getDiffuse());
        ++ParamIndex;
    }
    else
    {
        ShaderParameterIntPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(NumTextures);
        ++NumTextures;
        ++ParamIndex;
    }
    
    //Specularity
    if(getSpecularityTexture() == NullFC)
    {
        ShaderParameterRealPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(getSpecularity());
        ++ParamIndex;
    }
    else
    {
        ShaderParameterIntPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(NumTextures);
        ++NumTextures;
        ++ParamIndex;
    }
    
    //SpecularEccentricity
    if(getSpecularEccentricityTexture() == NullFC)
    {
        ShaderParameterRealPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(getSpecularEccentricity());
        ++ParamIndex;
    }
    else
    {
        ShaderParameterIntPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(NumTextures);
        ++NumTextures;
        ++ParamIndex;
    }
    
    //SpecularColor
    if(getSpecularColorTexture() == NullFC)
    {
        if(getSpecularColors().size() == 0)  // 0 SpecularColors
        {
            ShaderParameterVec3fPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(Vec3f(0.0,0.0,0.0));
            ++ParamIndex;
        }
        else if(getSpecularColors().size() == 1)  // 1 SpecularColor
        {
            ShaderParameterVec3fPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(Vec3f(getSpecularColors().front().getValuesRGB()));
            ++ParamIndex;
        }
        else // > 1 SpecularColors
        {
            ShaderParameterMVec3fPtr::dcast(getParameters()->getParameters(ParamIndex))->getValue().clear();
            for(UInt32 i(0) ; i<getSpecularColors().size() ; ++i)
            {
                ShaderParameterMVec3fPtr::dcast(getParameters()->getParameters(ParamIndex))->getValue().push_back(Vec3f(getSpecularColors(i).getValuesRGB()));
            }
            ++ParamIndex;

            ShaderParameterMRealPtr::dcast(getParameters()->getParameters(ParamIndex))->getValue().setValues(getSpecularColorPositions());
            ++ParamIndex;
        }
    }
    else // SpecularColor Texture
    {
        ShaderParameterIntPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(NumTextures);
        ++NumTextures;
        ++ParamIndex;
    }
    
    //SpecularRolloff
    if(getSpecularRolloffTexture() == NullFC)
    {
        if(getSpecularRolloffs().size() == 0)  // 0 SpecularRolloffs
        {
            ShaderParameterRealPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(1.0);
            ++ParamIndex;
        }
        else if(getSpecularRolloffs().size() == 1)  // 1 SpecularRolloff
        {
            ShaderParameterRealPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(getSpecularRolloffs().front());
            ++ParamIndex;
        }
        else // > 1 SpecularRolloffs
        {
            ShaderParameterMRealPtr::dcast(getParameters()->getParameters(ParamIndex))->getValue().setValues(getSpecularRolloffs());
            ++ParamIndex;

            ShaderParameterMRealPtr::dcast(getParameters()->getParameters(ParamIndex))->getValue().setValues(getSpecularRolloffPositions());
            ++ParamIndex;
        }
    }
    else // SpecularRolloff Texture
    {
        ShaderParameterIntPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(NumTextures);
        ++NumTextures;
        ++ParamIndex;
    }
}

void RampMaterial::updateShaderParameters(void)
{
    UInt8 NumTextures(0);
    UInt8 ParamIndex(0);
    internalUpdateShaderParameters(NumTextures, ParamIndex);
}
    
void RampMaterial::internalAttachChunks(void)
{
    //Transparency Chunk
    if(isTransparent())
    {
        getChunks().push_back(MaterialLibrary::the()->getDefaultTransparencyChunk());
    }

    //Depth Chunk
    getChunks().push_back(MaterialLibrary::the()->getDefaultDepthChunk());
    //Polygon Chunk
    getChunks().push_back(MaterialLibrary::the()->getDefaultOneSidedChunk());
    //Color
    if(getColorTexture() != NullFC)
    {
        getChunks().push_back(getColorTexture());
    }
    //Transparency
    if(getTransparencyTexture() != NullFC)
    {
        getChunks().push_back(getTransparencyTexture());
    }
    //AmbientColor
    if(getAmbientColorTexture() != NullFC)
    {
        getChunks().push_back(getAmbientColorTexture());
    }
    //Incandescence
    if(getIncandescenceTexture() != NullFC)
    {
        getChunks().push_back(getIncandescenceTexture());
    }
    //Normal
    if(getNormalMapTexture() != NullFC)
    {
        getChunks().push_back(getNormalMapTexture());

        //Bump Depth
        //if(getBumpDepthTexture() != NullFC)
        //{
            //getChunks().push_back(getBumpDepthTexture());
        //}
    }
    //Diffuse
    if(getDiffuseTexture() != NullFC)
    {
        getChunks().push_back(getDiffuseTexture());
    }
    //Specularity
    if(getDiffuseTexture() != NullFC)
    {
        getChunks().push_back(getDiffuseTexture());
    }
    //Eccentricity
    if(getDiffuseTexture() != NullFC)
    {
        getChunks().push_back(getDiffuseTexture());
    }
    //Specular Color
    if(getSpecularColorTexture() != NullFC)
    {
        getChunks().push_back(getSpecularColorTexture());
    }
    //SpecularRolloff
    if(getSpecularRolloffTexture() != NullFC)
    {
        getChunks().push_back(getSpecularRolloffTexture());
    }

    //Shader Parameters
    getChunks().push_back(getParameters());

    //SHader Chunk
    getChunks().push_back(getShader());

    //Extra Chunks
    for(UInt32 i(0) ; i<getExtraChunks().size() ; ++i)
    {
        getChunks().push_back(getExtraChunks(i));
    }
}

void RampMaterial::attachChunks(void)
{
    beginEditCP(RampMaterialPtr(this), RampMaterial::ChunksFieldMask);
        getChunks().clear();
        internalAttachChunks();
    endEditCP(RampMaterialPtr(this), RampMaterial::ChunksFieldMask);
}

std::string RampMaterial::generateVertexCode(void) const
{
    std::string Result("");
	Result += "//Tangent Space Shader\n"
	"//Per pixel lighting\n"
	 
	"varying vec3 LightDir[" + boost::lexical_cast<std::string>(static_cast<UInt32>(getNumLights())) + "];\n"
	"varying vec3 ViewDir;\n"

	"void main()\n"
	"{\n"
	 
	"    vec3 N,T,B;\n"
	 
	 
	"    //Vertex Positoin\n"
	"    vec4 VertexPos = gl_ModelViewMatrix * gl_Vertex;\n"
	 
	"    /* first transform the normal into eye space and normalize the result */\n"
	"    N = normalize(gl_NormalMatrix * gl_Normal);\n"
	 
	"    /* first transform the tangent into eye space and normalize the result */\n"
	"    T = normalize(gl_NormalMatrix * (gl_TextureMatrix[7] * gl_MultiTexCoord7).xyz);\n"
	 
	"    B = cross(N,T);\n"
	 
	"    mat3 TBN = mat3(T.x, B.x, N.x,\n"
	"                    T.y, B.y, N.y,\n"
	"                    T.z, B.z, N.z);\n";
		
    
    for(unsigned int i(0) ; i<getNumLights() ; ++i)
    {
	    Result +=  "        //Light" + boost::lexical_cast<std::string>(i) + "\n"
	    "        if(gl_LightSource[" + boost::lexical_cast<std::string>(i) + "].position.w == 0.0) // Directional Light\n"
	    "        {\n"
	    "            /* now normalize the light's direction. Note that according to the\n"
	    "            OpenGL specification, the light is stored in eye space. Also since \n"
	    "            we're talking about a directional light, the position field is actually \n"
	    "            direction */\n"
	    "            LightDir[" + boost::lexical_cast<std::string>(i) + "] = vec3(gl_LightSource[" + boost::lexical_cast<std::string>(i) + "].position);\n"
	    "        }\n"
	    "        else //Point or Spot Light\n"
	    "        {\n"
	    "            LightDir[" + boost::lexical_cast<std::string>(i) + "] = vec3(gl_LightSource[" + boost::lexical_cast<std::string>(i) + "].position-VertexPos);\n"
	    "            //LightDir[" + boost::lexical_cast<std::string>(i) + "] = normalize(vec3(gl_LightSource[" + boost::lexical_cast<std::string>(i) + "].position-VertexPos));\n"
	    "        }\n"
	    "        LightDir[" + boost::lexical_cast<std::string>(i) + "] = TBN * LightDir[" + boost::lexical_cast<std::string>(i) + "];\n\n";
    }
	Result += "    //Transform the ViewDirection into TBN space\n"
	"    ViewDir = -VertexPos.xyz;\n"
	"    ViewDir = TBN * ViewDir;\n"
	"    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;\n"
	"    gl_Position = ftransform();\n"
	"}\n";

    return Result;
}

std::string RampMaterial::generateFragmentCode(void) const
{
    //Generate Ramp Func Code for Color Attribute
    std::string ColorRampFuncName(""),
                ColorRampFuncCode("");

    if(getColorTexture() == NullFC && getColors().size() > 1)
    {
        generateRampFunc(getColorInterpolations(), FieldDataTraits<Vec3f>::getType(), "Color",ColorRampFuncName,ColorRampFuncCode);
    }
    
    //Generate Ramp Func Code for Transparency Attribute
    std::string TransparencyRampFuncName(""),
                TransparencyRampFuncCode("");

    if(getTransparencyTexture() == NullFC && getTransparencies().size() > 1)
    {
        generateRampFunc(getTransparencyInterpolations(), FieldDataTraits<Vec3f>::getType(), "Transparency",TransparencyRampFuncName,TransparencyRampFuncCode);
    }
    
    //Generate Ramp Func Code for Incandescence Attribute
    std::string IncandescenceRampFuncName(""),
                IncandescenceRampFuncCode("");

    if(getIncandescenceTexture() == NullFC && getIncandescences().size() > 1)
    {
        generateRampFunc(getIncandescenceInterpolations(), FieldDataTraits<Vec3f>::getType(), "Incandescence",IncandescenceRampFuncName,IncandescenceRampFuncCode);
    }
    
    //Generate Ramp Func Code for SpecularColor Attribute
    std::string SpecularColorRampFuncName(""),
                SpecularColorRampFuncCode("");

    if(getSpecularColorTexture() == NullFC && getSpecularColors().size() > 1)
    {
        generateRampFunc(getSpecularColorInterpolations(), FieldDataTraits<Vec3f>::getType(), "Incandescence",SpecularColorRampFuncName,SpecularColorRampFuncCode);
    }
    
    //Generate Ramp Func Code for SpecularRolloff Attribute
    std::string SpecularRolloffRampFuncName(""),
                SpecularRolloffRampFuncCode("");

    if(getSpecularRolloffTexture() == NullFC && getSpecularRolloffs().size() > 1)
    {
        generateRampFunc(getSpecularRolloffInterpolations(), FieldDataTraits<Real32>::getType(), "Incandescence",SpecularRolloffRampFuncName,SpecularRolloffRampFuncCode);
    }

    std::string Result("");
    
    //Color
    if(getColorTexture() == NullFC)
    {
        if(getColors().size() <= 1)  // 0-1 Colors
        {
		    Result += "uniform vec3 Color;\n";
        }
        else // > 1 Colors
        {
		    Result += "uniform vec3 Colors[" + boost::lexical_cast<std::string>(static_cast<UInt32>(getColors().size())) + "];\n"
                "uniform float ColorPositions[" + boost::lexical_cast<std::string>(static_cast<UInt32>(getColors().size())) + "];\n";
        }
    }
    else // Color Texture
    {
		Result += "uniform sampler2D ColorTexture;\n";
    }

    //Transparency
    if(getTransparencyTexture() == NullFC)
    {
        if(getTransparencies().size() <= 1)  // 0-1 Transparencies
        {
		    Result += "uniform vec3 Transparency;\n";
        }
        else // > 1 Transparencies
        {
		    Result += "uniform vec3 Transparencies[" + boost::lexical_cast<std::string>(static_cast<UInt32>(getTransparencies().size())) + "];\n"
                "uniform float TransparencyPositions[" + boost::lexical_cast<std::string>(static_cast<UInt32>(getTransparencies().size())) + "];\n";
        }
    }
    else // Transparency Texture
    {
		Result += "uniform sampler2D TransparencyTexture;\n";
    }

    //AmbientColor
	if(getAmbientColorTexture() != NullFC)
	{
		Result += "uniform sampler2D AmbientColorTexture;\n";
	}
    else
    {
		Result += "uniform vec3 AmbientColor;\n";
    }

    //Incandescence
    if(getIncandescenceTexture() == NullFC)
    {
        if(getIncandescences().size() <= 1)  // 0-1 Incandescences
        {
		    Result += "uniform vec3 Incandescence;\n";
        }
        else // > 1 Incandescences
        {
		    Result += "uniform vec3 Incandescences[" + boost::lexical_cast<std::string>(static_cast<UInt32>(getIncandescences().size())) + "];\n"
                "uniform float IncandescencePositions[" + boost::lexical_cast<std::string>(static_cast<UInt32>(getIncandescences().size())) + "];\n";
        }
    }
    else // Incandescence Texture
    {
		Result += "uniform sampler2D IncandescenceTexture;\n";
    }

    //Normal
	if(getNormalMapTexture() != NullFC)
	{
		Result += "uniform sampler2D NormalTexture;\n";
        
        //Bump Depth
		//if(getBumpDepthTexture() != NullFC)
		//{
			//Result += "uniform sampler2D BumpDepthTexture;\n";
		//}
        //else
        //{
			//Result += "uniform float BumpDepth;\n";
        //}
	}

    //Diffuse
	if(getDiffuseTexture() != NullFC)
	{
		Result += "uniform sampler2D DiffuseTexture;\n";
	}
    else
    {
		Result += "uniform float Diffuse;\n";
    }

    //Specularity
	if(getSpecularityTexture() != NullFC)
	{
		Result += "uniform sampler2D SpecularityTexture;\n";
	}
    else
    {
		Result += "uniform float Specularity;\n";
    }
    
    //SpecularEccentricity
	if(getSpecularEccentricityTexture() != NullFC)
	{
		Result += "uniform sampler2D SpecularEccentricityTexture;\n";
	}
    else
    {
		Result += "uniform float SpecularEccentricity;\n";
    }
    
    //SpecularColor
    if(getSpecularColorTexture() == NullFC)
    {
        if(getSpecularColors().size() <= 1)  // 0-1 SpecularColors
        {
		    Result += "uniform vec3 SpecularColor;\n";
        }
        else // > 1 SpecularColors
        {
		    Result += "uniform vec3 SpecularColors[" + boost::lexical_cast<std::string>(static_cast<UInt32>(getSpecularColors().size())) + "];\n"
                "uniform float SpecularColorPositions[" + boost::lexical_cast<std::string>(static_cast<UInt32>(getSpecularColors().size())) + "];\n";
        }
    }
    else // SpecularColor Texture
    {
		Result += "uniform sampler2D SpecularColorTexture;\n";
    }
    
    //SpecularRolloff
    if(getSpecularRolloffTexture() == NullFC)
    {
        if(getSpecularRolloffs().size() <= 1)  // 0-1 SpecularRolloffs
        {
		    Result += "uniform float SpecularRolloff;\n";
        }
        else // > 1 SpecularRolloffs
        {
		    Result += "uniform float SpecularRolloffs[" + boost::lexical_cast<std::string>(static_cast<UInt32>(getSpecularRolloffs().size())) + "];\n"
                "uniform float SpecularRolloffPositions[" + boost::lexical_cast<std::string>(static_cast<UInt32>(getSpecularRolloffs().size())) + "];\n";
        }
    }
    else // SpecularRolloff Texture
    {
		Result += "uniform sampler2D SpecularRolloffTexture;\n";
    }
    
	Result += "varying vec3 LightDir[" + boost::lexical_cast<std::string>(static_cast<UInt32>(getNumLights())) + "];\n"
	"varying vec3 ViewDir;\n";

    //Define Ramp Functions
    //Color
    if(getColorTexture() == NullFC && getColors().size() > 1)
    {
        Result += "\n" + ColorRampFuncCode + "\n";
    }
    
    //Transparency
    if(getTransparencyTexture() == NullFC && getTransparencies().size() > 1)
    {
        Result += "\n" + TransparencyRampFuncCode + "\n";
    }
    
    //Incandescence
    if(getIncandescenceTexture() == NullFC && getIncandescences().size() > 1)
    {
        Result += "\n" + IncandescenceRampFuncCode + "\n";
    }
    
    //SpecularColor
    if(getSpecularColorTexture() == NullFC && getSpecularColors().size() > 1)
    {
        Result += "\n" + SpecularColorRampFuncCode + "\n";
    }
    
    //SpecularRolloff
    if(getSpecularRolloffTexture() == NullFC && getSpecularRolloffs().size() > 1)
    {
        Result += "\n" + SpecularRolloffRampFuncCode + "\n";
    }

	Result += "void main()\n"
	"{\n"
	"    vec3 LightDirNorm;\n"
	"    vec3 ViewDirNorm = normalize(ViewDir);\n"
    
	"    //Normal\n";
	if(getNormalMapTexture() != NullFC)
	{
		Result += "    vec3 Normal = (texture2D(NormalTexture,gl_TexCoord[0].st).xyz * 2.0) - vec3(1.0);\n";
	}
	else
	{
		Result += "    vec3 Normal = vec3(0.0,0.0,1.0);\n";
	}
    
	Result += "    //For the number of lights\n"
	"    vec3 FragColor = vec3(0.0);\n"
    
	"    float atten;\n"
    
	"    float nDotL;\n"
	"    float nDotH;\n"
	"    float power;\n"
	"    float Dist;\n";
    
    //Ambient Material Color
    if(getAmbientColorTexture() == NullFC)
    {
        Result += "vec3 FragAmbientColor = AmbientColor;\n";
    }
    else
    {
        Result += "vec3 FragAmbientColor = texture2D(AmbientColorTexture,gl_TexCoord[0].st).rgb;\n";
    }

    
    //Diffuse Material Color
    if(getColorTexture() == NullFC)
    {
        if(getColors().size() <= 1)
        {
            Result += "vec3 FragDiffuseColor = Color;\n";
        }
        else
        {
            Result += "vec3 FragDiffuseColor;\n";
        }
    }
    else
    {
        Result += "vec3 FragDiffuseColor = texture2D(ColorTexture,gl_TexCoord[0].st).rgb;\n";
    }

    //Diffuse Coefficient
    if(getDiffuseTexture() == NullFC)
    {
        Result += "float FragDiffuse = Diffuse;\n";
    }
    else
    {
        Result += "float FragDiffuse = texture2D(DiffuseTexture,gl_TexCoord[0].st).r;\n";
    }

    //SpecularEccentricity
    if(getSpecularEccentricityTexture() == NullFC)
    {
        Result += "float FragSpecularEccentricity = (1.0-SpecularEccentricity) * 128.0;\n";
    }
    else
    {
        Result += "float FragSpecularEccentricity = (1.0-texture2D(SpecularEccentricityTexture,gl_TexCoord[0].st).r) * 128.0;\n";
    }
    //Specularity
    if(getSpecularityTexture() == NullFC)
    {
        Result += "float FragSpecularity = Specularity;\n";
    }
    else
    {
        Result += "float FragSpecularity = texture2D(SpecularityTexture,gl_TexCoord[0].st).r;\n";
    }
    
    //SpecularRolloff
    if(getSpecularRolloffTexture() == NullFC)
    {
        if(getSpecularRolloffs().size() <= 1)
        {
            Result += "float FragSpecularRolloff = SpecularRolloff;\n";
        }
        else
        {
            Result += "float FragSpecularRolloff;\n";
        }
    }
    else
    {
        Result += "float FragSpecularRolloff = texture2D(SpecularRolloffTexture,gl_TexCoord[0].st).r;\n";
    }
    
    //Specular Color
    if(getSpecularColorTexture() == NullFC)
    {
        if(getSpecularColors().size() <= 1)
        {
            Result += "vec3 FragSpecularColor = SpecularColor;\n";
        }
        else
        {
            Result += "vec3 FragSpecularColor;\n";
        }
    }
    else
    {
        Result += "vec3 FragSpecularColor = texture2D(SpecularColorTexture,gl_TexCoord[0].st).rgb;\n";
    }

    for(unsigned int i(0) ; i<getNumLights() ; ++i)
    {
	    Result += 
	    "        //Light " + boost::lexical_cast<std::string>(i) + "\n"
        "        Dist = length(LightDir[" + boost::lexical_cast<std::string>(i) + "]);\n"
	    "        LightDirNorm = LightDir[" + boost::lexical_cast<std::string>(i) + "]/Dist;\n"
         
	    "        nDotL = max(0.0, dot(Normal, LightDirNorm));\n"
	    "        nDotH = max(0.0, dot(Normal, 0.5 * (LightDirNorm + ViewDirNorm))); // Blinn\n";

        Result +=
	    "        //Eccentricity\n"
        "        power = (nDotL == 0.0) ? 0.0 :  pow(nDotH, FragSpecularEccentricity) * FragSpecularity;\n"
        
        "        //Specular Roll Off\n";
        if(getSpecularRolloffTexture() == NullFC && getSpecularRolloffs().size() > 1)
        {
            Result += "        FragSpecularRolloff = " + SpecularRolloffRampFuncName + "(max(0.0, nDotL), SpecularRolloffs, SpecularRolloffPositions);\n";
        }
        Result +=
        "        power *= FragSpecularRolloff;\n"
        
        "        if(gl_LightSource[" + boost::lexical_cast<std::string>(i) + "].spotCosCutoff < 1.0) // Spot Light\n"
	    "        {\n"
	    //<< "            float spotEffect = dot(SpotDir[" + boost::lexical_cast<std::string>(i) + "], -LightDirNorm);\n"
	    "            float spotEffect = dot(normalize(gl_LightSource[" + boost::lexical_cast<std::string>(i) + "].spotDirection), -LightDirNorm);\n"
	    "		    if (spotEffect > gl_LightSource[" + boost::lexical_cast<std::string>(i) + "].spotCosCutoff)\n"
	    "            {\n"
	    "                //Compute the attenuation for spotlight\n"
	    "		        spotEffect = pow(spotEffect, gl_LightSource[" + boost::lexical_cast<std::string>(i) + "].spotExponent);\n"
	    "		        atten = spotEffect / (gl_LightSource[" + boost::lexical_cast<std::string>(i) + "].constantAttenuation +\n"
	    "				    gl_LightSource[" + boost::lexical_cast<std::string>(i) + "].linearAttenuation * Dist +\n"
	    "				    gl_LightSource[" + boost::lexical_cast<std::string>(i) + "].quadraticAttenuation * Dist * Dist);\n"
	    "            }\n"
	    "            else\n"
	    "            {\n"
	    "                atten = 0.0;\n"
	    "            }\n"
	    "		}\n"
	    "        else if(gl_LightSource[" + boost::lexical_cast<std::string>(i) + "].position.w != 0.0) //Point Light\n"
	    "        {\n"
	    "            atten = 1.0/(gl_LightSource[" + boost::lexical_cast<std::string>(i) + "].constantAttenuation +\n"
	    "                gl_LightSource[" + boost::lexical_cast<std::string>(i) + "].linearAttenuation * Dist +\n"
	    "                gl_LightSource[" + boost::lexical_cast<std::string>(i) + "].quadraticAttenuation * Dist * Dist);\n"
	    "        }\n"
	    "        else //Directional Light\n"
	    "        {\n"
	    "            atten = 1.0;\n"
	    "        }\n"
	    "        atten = min(1.0,atten);\n"
         
	    "        //Ambient\n"
        "       FragColor += FragAmbientColor * gl_LightSource[" + boost::lexical_cast<std::string>(i) + "].ambient.rgb;\n"
        //"       FragColor += FragAmbientColor;\n"

	    "        //Diffuse\n";
        if(getColorTexture() == NullFC && getColors().size() > 1)
        {
            Result += "        FragDiffuseColor = " + ColorRampFuncName + "(";
            switch(getRampSource())
            {
            case RAMP_SOURCE_LIGHT_ANGLE:
                Result += "max(0.0, nDotL)";
                break;
            case RAMP_SOURCE_BRIGHTNESS:
                Result += "max(0.0, nDotL* FragDiffuse)";
                break;
            case RAMP_SOURCE_FACING_ANGLE:
            default:
                Result += "max(0.0, dot(Normal, ViewDirNorm))";
                break;
            }
            Result +=
            ", Colors, ColorPositions);\n";
        }
        Result +=
        "        FragColor += FragDiffuseColor * gl_LightSource[" + boost::lexical_cast<std::string>(i) + "].diffuse.rgb * nDotL * FragDiffuse;\n"
        //"        FragColor += FragDiffuseColor * nDotL;\n"
        
	    "        //Specular\n";
        if(getSpecularColorTexture() == NullFC && getSpecularColors().size() > 1)
        {
            Result += "        FragSpecularColor = " + SpecularColorRampFuncName + "(max(0.0, nDotL), SpecularColors, SpecularColorPositions);\n";
        }
        Result +=
        "        FragColor += FragSpecularColor * gl_LightSource[" + boost::lexical_cast<std::string>(i) + "].specular.rgb * power;\n";
        //"        FragColor += FragSpecularColor * power;\n"
    }
    
	Result += 
        "    //Global Ambient\n"
        "    FragColor += gl_LightModel.ambient.rgb * FragAmbientColor;\n";
        
        "    //Incandescence\n";
    if(getIncandescenceTexture() == NullFC)
    {
        if(getIncandescences().size() <= 1)  // 0-1 Incandescences
        {
		    Result += "    FragColor += Incandescence;\n";
        }
        else // > 1 Incandescences
        {
            Result += "        FragColor += " + IncandescenceRampFuncName + "(max(0.0, dot(Normal, ViewDirNorm)), Incandescences, IncandescencePositions);\n";
        }
    }
    else // Incandescence Texture
    {
		Result += "    FragColor += texture2D(IncandescenceTexture,gl_TexCoord[0].st).rgb;\n";
    }
    
	Result += "    gl_FragColor = vec4(FragColor,";
    if(getTransparencyTexture() == NullFC)
    {
        if(getTransparencies().size() <= 1)  // 0-1 Transparencies
        {
		    //Result += "0.3*Transparency.r + 0.59*Transparency.g + 0.11*Transparency.b";
		    Result += "Transparency.r";  //fixed
        }
        else // > 1 Transparencies
        {
            Result += TransparencyRampFuncName + "(max(0.0, dot(Normal, ViewDirNorm)), Transparencies, TransparencyPositions).r"; //fixed
		}
    }
    else // Transparencies Texture
    {
        if(getTransparencyTexture()->getImage()->hasAlphaChannel())
        {
		    Result += "texture2D(TransparencyTexture,gl_TexCoord[0].st).a";
        }
        else
        {
		    Result += "texture2D(TransparencyTexture,gl_TexCoord[0].st).r"; //fixed
        }
    }
	Result += ");\n"
	"}\n";
    //std::cout << Result;
    return Result;
}

void RampMaterial::generateRampFunc(const MFUInt8 &Interpolators, const TypeBase& Type, const std::string& FuncNamePrefix, std::string& FuncName, std::string& RampCode) const
{
    std::string TypeString("");
    if(Type == FieldDataTraits<Vec3f>::getType())
    {
        TypeString = std::string("vec3");
    }
    else if(Type == FieldDataTraits<Real32>::getType())
    {
        TypeString = std::string("float");
    }

    FuncName = FuncNamePrefix + std::string("_Ramp_") + TypeString + "_" + boost::lexical_cast<std::string>(Interpolators.size()+1);

    RampCode.clear();
	RampCode += TypeString + " " + FuncName + "(float t, " + TypeString + " Values[" + boost::lexical_cast<std::string>(Interpolators.size()+1) + "], float Stops[" + boost::lexical_cast<std::string>(Interpolators.size()+1) + "])\n"
	"{\n"
    "   " + TypeString + " Result;\n";
	for(Int32 i(0) ; i<Interpolators.size()+1 ; ++i)
	{
		if(i == 0)
		{
			RampCode += "   if(t<Stops[0])\n"
					"   {\n"
					"      Result = Values[0];\n"
					"   }\n";
		}
		else
		{
			RampCode +="   else if(t<Stops[" + boost::lexical_cast<std::string>(i) + "])\n"
					 "   {\n"
					 "      Result = ";
            if(Interpolators.getValue(i-1) == RAMP_INTERPOLATION_LINEAR)
			{
				RampCode += "mix(Values[" + boost::lexical_cast<std::string>(i-1) + "],Values[" + boost::lexical_cast<std::string>(i) + "], (t - Stops[" + boost::lexical_cast<std::string>(i-1) + "])/(Stops[" + boost::lexical_cast<std::string>(i) + "] - Stops[" + boost::lexical_cast<std::string>(i-1) + "]))";
			}
			else if(Interpolators.getValue(i-1) == RAMP_INTERPOLATION_SMOOTH)
			{
				RampCode += "Values[" + boost::lexical_cast<std::string>(i-1) + "] + (Values[" + boost::lexical_cast<std::string>(i) + "] - Values[" + boost::lexical_cast<std::string>(i-1) + "]) * smoothstep(Stops[" + boost::lexical_cast<std::string>(i-1) + "], Stops[" + boost::lexical_cast<std::string>(i) + "],t)";
			}
			else if(Interpolators.getValue(i-1) == RAMP_INTERPOLATION_SPLINE)
			{
				RampCode += "Values[" + boost::lexical_cast<std::string>(i-1) + "] + (Values[" + boost::lexical_cast<std::string>(i) + "] - Values[" + boost::lexical_cast<std::string>(i-1) + "]) * smoothstep(Stops[" + boost::lexical_cast<std::string>(i-1) + "], Stops[" + boost::lexical_cast<std::string>(i) + "],t)";
			}
            else //Default to Step interpolation
			{
				RampCode += "Values[" + boost::lexical_cast<std::string>(i-1) + "]";
			}
			RampCode += ";\n"
					 "   }\n";
		}
	}
	RampCode += "   else\n"
			"   {\n"
			"      Result = Values[" + boost::lexical_cast<std::string>(Interpolators.size()) + "];\n"
			"   }\n"
            "   return Result;\n"
			"}\n";

}


bool RampMaterial::shouldRecreateChunks(BitVector FieldMask) const
{
    return 
        (FieldMask & NumLightsFieldMask) ||
        (FieldMask & RampSourceFieldMask) ||
        
        (FieldMask & ColorsFieldMask) ||
        (FieldMask & ColorPositionsFieldMask) ||
        (FieldMask & ColorInterpolationsFieldMask) ||
        (FieldMask & ColorTextureFieldMask) ||

        (FieldMask & TransparenciesFieldMask) ||
        (FieldMask & TransparencyPositionsFieldMask) ||
        (FieldMask & TransparencyInterpolationsFieldMask) ||
        (FieldMask & TransparencyTextureFieldMask) ||

        (FieldMask & AmbientColorTextureFieldMask) ||

        (FieldMask & IncandescencesFieldMask) ||
        (FieldMask & IncandescencePositionsFieldMask) ||
        (FieldMask & IncandescenceInterpolationsFieldMask) ||
        (FieldMask & IncandescenceTextureFieldMask) ||

        (FieldMask & BumpDepthTextureFieldMask) ||

        (FieldMask & NormalMapTextureFieldMask) ||

        (FieldMask & DiffuseTextureFieldMask) ||
        
        (FieldMask & SpecularityTextureFieldMask) ||
        
        (FieldMask & SpecularEccentricityTextureFieldMask) ||

        (FieldMask & SpecularColorsFieldMask) ||
        (FieldMask & SpecularColorPositionsFieldMask) ||
        (FieldMask & SpecularColorInterpolationsFieldMask) ||
        (FieldMask & SpecularColorTextureFieldMask) ||

        (FieldMask & SpecularRolloffsFieldMask) ||
        (FieldMask & SpecularRolloffPositionsFieldMask) ||
        (FieldMask & SpecularRolloffInterpolationsFieldMask) ||
        (FieldMask & SpecularRolloffTextureFieldMask);
}

bool RampMaterial::shouldUpdateParameters(BitVector FieldMask) const
{
    return (FieldMask & AmbientColorFieldMask) ||
        (FieldMask & BumpDepthFieldMask) ||
        (FieldMask & DiffuseFieldMask) ||
        (FieldMask & SpecularityFieldMask) ||
        (FieldMask & SpecularEccentricityFieldMask);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

RampMaterial::RampMaterial(void) :
    Inherited()
{
}

RampMaterial::RampMaterial(const RampMaterial &source) :
    Inherited(source)
{
}

RampMaterial::~RampMaterial(void)
{
    getChunks().clear();
}

/*----------------------------- class specific ----------------------------*/

void RampMaterial::onCreate(const RampMaterial *source)
{
    //Shader Chunk
    SHLChunkPtr TheSHLChunk = SHLChunk::create();
    addRefCP(TheSHLChunk);
    setShader(TheSHLChunk);

    //Shader Parameter Chunk
    SHLParameterChunkPtr TheSHLParameterChunk = SHLParameterChunk::create();
    addRefCP(TheSHLParameterChunk);
    setParameters(TheSHLParameterChunk);

    beginEditCP(getParameters(), SHLParameterChunk::SHLChunkFieldMask);
        getParameters()->setSHLChunk(getShader());
    endEditCP(getParameters(), SHLParameterChunk::SHLChunkFieldMask);

    //Need to attach the chunks
    attachChunks();

    //Need to attach the shader parameters
    createShaderParameters();

    //Parameters should be updated
    updateShaderParameters();

    //Shader Code should be updated
    updateShaderCode();

}

void RampMaterial::onDestroy(void)
{
    subRefCP(getShader());
    setShader(NullFC);

    subRefCP(getParameters());
    setParameters(NullFC);
}

void RampMaterial::changed(BitVector whichField, UInt32 origin)
{

    Inherited::changed(whichField, origin);

    //Do the Chunks attached need to be redone
    if(shouldRecreateChunks(whichField) || whichField & ExtraChunksFieldMask)
    {
        //Need to attach the chunks
        attachChunks();
    }

    //Do the Chunks attached need to be redone
    if(shouldRecreateChunks(whichField))
    {
        //Need to attach the shader parameters
        createShaderParameters();

        //Parameters should be updated
        updateShaderParameters();

        //Shader Code should be updated
        updateShaderCode();
    }

    if(shouldUpdateParameters(whichField))
    {
        //Parameters should be updated
        updateShaderParameters();
    }
}
   

void RampMaterial::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump RampMaterial NI" << std::endl;
}


OSG_END_NAMESPACE

