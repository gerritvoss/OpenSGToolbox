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
#include <OpenSG/OSGShaderParameterInt.h>
#include <OpenSG/OSGShaderParameterReal.h>
#include <OpenSG/OSGShaderParameterVec3f.h>
#include <OpenSG/OSGShaderParameterVec4f.h>

#include "OSGLambertMaterial.h"
#include "OSGMaterialLibrary.h"
#include <boost/lexical_cast.hpp>

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

bool LambertMaterial::isTransparent(void) const
{
    return (getTransparencyTexture() != NullFC || getTransparency() != Color3f(0.0f,0.0f,0.0f));
}

void LambertMaterial::updateShaderCode(void)
{
    beginEditCP(getShader(), SHLChunk::VertexProgramFieldMask | SHLChunk::FragmentProgramFieldMask);
        getShader()->setVertexProgram(generateVertexCode());
        getShader()->setFragmentProgram(generateFragmentCode());
    endEditCP(getShader(), SHLChunk::VertexProgramFieldMask | SHLChunk::FragmentProgramFieldMask);
}

void LambertMaterial::updateShaderParameters(void)
{
    UInt8 NumTextures(0);
    beginEditCP(getParameters(), SHLParameterChunk::ParametersFieldMask);
        getParameters()->getParameters().clear();

        //Color
        if(getColorTexture() == NullFC)
        {
            ShaderParameterVec3fPtr ColorParam = ShaderParameterVec3f::create();
            ColorParam->setValue(Vec3f(getColor().getValuesRGB()));
            getParameters()->getParameters().push_back(ColorParam);
        }
        else
        {
            ShaderParameterIntPtr ColorTexParam = ShaderParameterInt::create();
            ColorTexParam->setValue(NumTextures);
            getParameters()->getParameters().push_back(ColorTexParam);
            ++NumTextures;
        }
        //Transparency
        if(getTransparencyTexture() == NullFC && isTransparent())
        {
            ShaderParameterVec3fPtr TransparencyParam = ShaderParameterVec3f::create();
            TransparencyParam->setValue(Vec3f(getTransparency().getValuesRGB()));
            getParameters()->getParameters().push_back(TransparencyParam);
        }
        else
        {
            ShaderParameterIntPtr TransparencyTexParam = ShaderParameterInt::create();
            TransparencyTexParam->setValue(NumTextures);
            getParameters()->getParameters().push_back(TransparencyTexParam);
            ++NumTextures;
        }
        //AmbientColor
        if(getAmbientColorTexture() == NullFC)
        {
            ShaderParameterVec3fPtr AmbientColorParam = ShaderParameterVec3f::create();
            AmbientColorParam->setValue(Vec3f(getAmbientColor().getValuesRGB()));
            getParameters()->getParameters().push_back(AmbientColorParam);
        }
        else
        {
            ShaderParameterIntPtr AmbientColorTexParam = ShaderParameterInt::create();
            AmbientColorTexParam->setValue(NumTextures);
            getParameters()->getParameters().push_back(AmbientColorTexParam);
            ++NumTextures;
        }
        //Incandescence
        if(getIncandescenceTexture() == NullFC)
        {
            ShaderParameterVec3fPtr IncandescenceParam = ShaderParameterVec3f::create();
            IncandescenceParam->setValue(Vec3f(getIncandescence().getValuesRGB()));
            getParameters()->getParameters().push_back(IncandescenceParam);
        }
        else
        {
            ShaderParameterIntPtr IncandescenceTexParam = ShaderParameterInt::create();
            IncandescenceTexParam->setValue(NumTextures);
            getParameters()->getParameters().push_back(IncandescenceTexParam);
            ++NumTextures;
        }
        //Normal
        if(getNormalMapTexture() != NullFC)
        {
            ShaderParameterIntPtr NormalTexParam = ShaderParameterInt::create();
            NormalTexParam->setValue(NumTextures);
            getParameters()->getParameters().push_back(NormalTexParam);
            ++NumTextures;
        }
        //Bump Depth
        if(getBumpDepthTexture() == NullFC)
        {
            ShaderParameterRealPtr BumpDepthParam = ShaderParameterReal::create();
            BumpDepthParam->setValue(getBumpDepth());
            getParameters()->getParameters().push_back(BumpDepthParam);
        }
        else
        {
            ShaderParameterIntPtr BumpDepthTexParam = ShaderParameterInt::create();
            BumpDepthTexParam->setValue(NumTextures);
            getParameters()->getParameters().push_back(BumpDepthTexParam);
            ++NumTextures;
        }
        //Diffuse
        if(getDiffuseTexture() == NullFC)
        {
            ShaderParameterRealPtr DiffuseParam = ShaderParameterReal::create();
            DiffuseParam->setValue(getDiffuse());
            getParameters()->getParameters().push_back(DiffuseParam);
        }
        else
        {
            ShaderParameterIntPtr DiffuseTexParam = ShaderParameterInt::create();
            DiffuseTexParam->setValue(NumTextures);
            getParameters()->getParameters().push_back(DiffuseTexParam);
            ++NumTextures;
        }
        //Transleucence
        //Transleucence Depth
        //Transleucence Focus
    endEditCP(getParameters(), SHLParameterChunk::ParametersFieldMask);
}

void LambertMaterial::updateChunks(void)
{
    updateShaderCode();
    updateShaderParameters();
    beginEditCP(LambertMaterialPtr(this), LambertMaterial::ChunksFieldMask);
        getChunks().clear();
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
        }
        //Bump Depth
        if(getBumpDepthTexture() != NullFC)
        {
            getChunks().push_back(getBumpDepthTexture());
        }
        //Diffuse
        if(getDiffuseTexture() != NullFC)
        {
            getChunks().push_back(getDiffuseTexture());
        }
        //Transleucence
        //Transleucence Depth
        //Transleucence Focus
    endEditCP(LambertMaterialPtr(this), LambertMaterial::ChunksFieldMask);
}

std::string LambertMaterial::generateVertexCode(void)
{
    std::string Result("");
	Result += 
	 "//Lambert Shader\n"
	 "//Ambient and Diffuse\n"
	 "//Per vertex lighting\n";
    //Diffuse
    if(getDiffuseTexture() == NullFC)
    {
	    Result += "uniform float Diffuse;\n";
    }
    else
    {
		Result += "uniform sampler2D DiffuseTexture;\n";
    }

	Result += 
	 "void main()\n"
	 "{\n"
	 "    vec4 DiffuseColor = vec4(0.0);\n"

	 "    vec3 normal, lightDir;\n"
	 "    vec4 diffuse;\n"
	 "    float NdotL = 0.0;\n"

	 "    //Vertex Position\n"
	 "    vec4 ecPos = gl_ModelViewMatrix * gl_Vertex;\n"

	 "    /* first transform the normal into eye space and normalize the result */\n"
	 "    normal = normalize(gl_NormalMatrix * gl_Normal);\n";

    for(UInt32 i(0) ; i<getNumLights() ; ++i)
    {
	    Result +=  "        //Light " + boost::lexical_cast<std::string>(i) +  "\n"
	    "        if(gl_LightSource[" + boost::lexical_cast<std::string>(i) + "].position.w == 0.0) // Directional Light\n"
	    "        {\n"
	    "            /* now normalize the light's direction. Note that according to the\n"
	    "            OpenGL specification, the light is stored in eye space. Also since \n"
	    "            we're talking about a directional light, the position field is actually \n"
	    "            direction */\n"
	    "            lightDir = normalize(vec3(gl_LightSource[" + boost::lexical_cast<std::string>(i) + "].position));\n"
	    "        }\n"
	    "        else //Point or Spot Light\n"
	    "        {\n"
	    "		    lightDir = normalize(vec3(gl_LightSource[" + boost::lexical_cast<std::string>(i) + "].position-ecPos));\n"
	    "        }\n"
        
	    "       /* compute the cos of the angle between the normal and lights direction. \n"
	    "        The light is directional so the direction is constant for every vertex.\n"
	    "       Since these two are normalized the cosine is the dot product. We also \n"
	    "        need to clamp the result to the [0,1] range. */\n"
	    "        NdotL = NdotL + max(dot(normal, lightDir), 0.0);\n"
        
	    "        DiffuseColor += NdotL * Diffuse * gl_FrontMaterial.diffuse * gl_LightSource[" + boost::lexical_cast<std::string>(i) + "].diffuse * gl_Color;\n\n";
    }

	Result += "    //Diffuse Term\n"
	"    //Set the Color as the diffuse term\n"
	"    gl_FrontColor = DiffuseColor;\n"

	"    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;\n"

	"    gl_Position = ftransform();\n"

	"}\n";
    return Result;
}

std::string LambertMaterial::generateFragmentCode(void)
{
    std::string Result("");
    Result += ""
	"//Lambert Shader\n"
	"//Ambient and Diffuse\n"
	"//Per vertex lighting\n";
    //Color
    if(getColorTexture() == NullFC)
    {
	    Result += "uniform vec3 Color;\n";
    }
    else
    {
		Result += "uniform sampler2D ColorTexture;\n";
    }
    //Transparency
    if(getTransparencyTexture() == NullFC && isTransparent())
    {
	    Result += "uniform vec3 Transparency;\n";
    }
    else
    {
		Result += "uniform sampler2D TransparencyTexture;\n";
    }
    //AmbientColor
    if(getAmbientColorTexture() == NullFC)
    {
	    Result += "uniform vec3 AmbientColor;\n";
    }
    else
    {
		Result += "uniform sampler2D AmbientColorTexture;\n";
    }
    //Incandescence
    if(getIncandescenceTexture() == NullFC)
    {
	    Result += "uniform vec3 Incandescence;\n";
    }
    else
    {
		Result += "uniform sampler2D IncandescenceTexture;\n";
    }
    //Normal
    if(getNormalMapTexture() != NullFC)
    {
		Result += "uniform sampler2D NormalTexture;\n";
    }
    //Bump Depth
    if(getBumpDepthTexture() == NullFC)
    {
	    Result += "uniform float BumpDepth;\n";
    }
    else
    {
		Result += "uniform sampler2D BumpDepthTexture;\n";
    }
    //Diffuse
    if(getDiffuseTexture() == NullFC)
    {
	    Result += "uniform float Diffuse;\n";
    }
    else
    {
		Result += "uniform sampler2D DiffuseTexture;\n";
    }
    //Transleucence
    //Transleucence Depth
    //Transleucence Focus

	Result += "void main()\n"
	"{\n"
	"    vec4 Color = gl_Color; //Diffuse Color\n"

	"    //For the number of lights\n"
	"    vec4 LightAmbient = vec4(0.0);\n";
    for(UInt32 i(0) ; i<getNumLights() ; ++i)
    {
	    Result += "    //Light " + boost::lexical_cast<std::string>(i) + "\n"
                           "    LightAmbient += gl_LightSource[" + boost::lexical_cast<std::string>(i) +  "].ambient.rgba;\n\n";
    }

	Result += "    //Ambient Color\n";
	//if(hasAmbientTexture)
	//{
	//	FragmentCodeStream << "    Color += texture2D(AmbientTexture,gl_TexCoord[0].st).rgb * LightAmbient;\n";
	//}
	if(getDiffuseTexture() != NullFC)
	{
		Result += "    Color.rgb += texture2D(DiffuseTexture,gl_TexCoord[0].st).rgb * LightAmbient.rgb;\n";
	}
	else
	{
		Result += "    Color.rgb += gl_FrontMaterial.ambient.rgb*LightAmbient.rgb;\n";
	}

	Result += "    //Diffuse Color Map\n";
	if(getDiffuseTexture() != NullFC)
	{
		Result += "    Color = Color * texture2D(DiffuseTexture,gl_TexCoord[0].st).rgb;\n";
	}

	Result += "    //Emissive\n";
	if(getIncandescenceTexture() != NullFC)
	{
		Result += "    Color += texture2D(EmissiveTexture,gl_TexCoord[0].st).rgb;\n";
	}
	else
	{
		Result += "    Color += gl_FrontMaterial.emission.rgba;\n";
	}

	Result += "    //No Specular for Lambert\n"
	"    gl_FragColor = vec4(Color.r,Color.g,Color.b,";
	if(getTransparencyTexture() != NullFC)
	{
		Result += "texture2D(TransparencyTexture,gl_TexCoord[0].st).r";
	}
    else if(isTransparent())
    {
		Result += "(Transparency.r + Transparency.g + Transparency.b)*.3333333";
    }
	else
	{
		Result += "Color.a";
	}
	Result += ");\n"
	"}\n";
    return Result;
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
    setParameters(SHLParameterChunk::create());

    //Shader Chunk
    setShader(SHLChunk::create());
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

