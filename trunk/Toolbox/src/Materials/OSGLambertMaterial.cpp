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
#include <OpenSG/OSGTextureChunk.h>
#include <OpenSG/OSGImage.h>
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

void LambertMaterial::internalCreateShaderParameters(void)
{
    //Color
    if(getColorTexture() == NullFC)
    {
        ShaderParameterVec3fPtr ColorParam = ShaderParameterVec3f::create();
        ColorParam->setName("Color");
        getParameters()->getParameters().push_back(ColorParam);
    }
    else
    {
        ShaderParameterIntPtr ColorTexParam = ShaderParameterInt::create();
        ColorTexParam->setName("ColorTexture");
        getParameters()->getParameters().push_back(ColorTexParam);
    }
    //Transparency
    if(getTransparencyTexture() == NullFC)
    {
        if(isTransparent())
        {
            ShaderParameterVec3fPtr TransparencyParam = ShaderParameterVec3f::create();
            TransparencyParam->setName("Transparency");
            getParameters()->getParameters().push_back(TransparencyParam);
        }
    }
    else
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
        ShaderParameterVec3fPtr IncandescenceParam = ShaderParameterVec3f::create();
        IncandescenceParam->setName("Incandescence");
        getParameters()->getParameters().push_back(IncandescenceParam);
    }
    else
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
    //Transleucence
    //Transleucence Depth
    //Transleucence Focus
}

void LambertMaterial::createShaderParameters(void)
{
    beginEditCP(getParameters(), SHLParameterChunk::ParametersFieldMask);
        getParameters()->getParameters().clear();

        internalCreateShaderParameters();
    endEditCP(getParameters(), SHLParameterChunk::ParametersFieldMask);
}

void LambertMaterial::internalUpdateShaderParameters(UInt8& NumTextures, UInt8& ParamIndex)
{
    //Color
    if(getColorTexture() == NullFC)
    {
        ShaderParameterVec3fPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(Vec3f(getColor().getValuesRGB()));
        ++ParamIndex;
    }
    else
    {
        ShaderParameterIntPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(NumTextures);
        ++NumTextures;
        ++ParamIndex;
    }
    //Transparency
    if(getTransparencyTexture() == NullFC)
    {
        if( isTransparent())
        {
            ShaderParameterVec3fPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(Vec3f(getTransparency().getValuesRGB()));
            ++ParamIndex;
        }
    }
    else
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
        ShaderParameterVec3fPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(Vec3f(getIncandescence().getValuesRGB()));
        ++ParamIndex;
    }
    else
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
    //Transleucence
    //Transleucence Depth
    //Transleucence Focus
}

void LambertMaterial::updateShaderParameters(void)
{
    UInt8 NumTextures(0);
    UInt8 ParamIndex(0);
    internalUpdateShaderParameters(NumTextures, ParamIndex);
}
    
void LambertMaterial::internalAttachChunks(void)
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
    //Transleucence
    //Transleucence Depth
    //Transleucence Focus

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

void LambertMaterial::attachChunks(void)
{
    beginEditCP(LambertMaterialPtr(this), LambertMaterial::ChunksFieldMask);
        getChunks().clear();
        internalAttachChunks();
    endEditCP(LambertMaterialPtr(this), LambertMaterial::ChunksFieldMask);
}

std::string LambertMaterial::generateVertexCode(void)
{
    std::string Result("");
	Result += "//Tangent Space Shader\n"
	"//Per pixel lighting\n"
	 
	"varying vec3 LightDir[" + boost::lexical_cast<std::string>(static_cast<UInt32>(getNumLights())) + "];\n"
	"varying vec3 ViewDir;\n"

	"void main()\n"
	"{\n"
	 
	"    vec3 N, T, B;\n" //todo restore N
	 
	 
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
	"    gl_FrontColor = gl_Color;\n"
	"    gl_BackColor = gl_Color;\n"
	"    gl_Position = ftransform();\n"
	"}\n";

    return Result;
}

std::string LambertMaterial::generateFragmentCode(void)
{
    std::string Result("");
    
    //Color
	if(getColorTexture() != NullFC)
	{
		Result += "uniform sampler2D ColorTexture;\n";
	}
    else
    {
		Result += "uniform vec3 Color;\n";
    }

    //Transparency
	if(getTransparencyTexture() != NullFC)
	{
        if(isTransparent())
        {
		    Result += "uniform sampler2D TransparencyTexture;\n";
        }
	}
    else
    {
		Result += "uniform vec3 Transparency;\n";
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
	if(getIncandescenceTexture() != NullFC)
	{
		Result += "uniform sampler2D IncandescenceTexture;\n";
	}
    else
    {
		Result += "uniform vec3 Incandescence;\n";
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
    //Transleucence
    //Transleucence Depth
    //Transleucence Focus
    
	Result += "varying vec3 LightDir[" + boost::lexical_cast<std::string>(static_cast<UInt32>(getNumLights())) + "];\n"
	"varying vec3 ViewDir;\n"
	"void main()\n"
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
        Result += "vec3 FragDiffuseColor = Color * gl_Color.rgb;\n";
    }
    else
    {
        Result += "vec3 FragDiffuseColor = texture2D(ColorTexture,gl_TexCoord[0].st).rgb * gl_Color.rgb;\n";
    }

    //Diffuse Coefficient
    if(getDiffuseTexture() == NullFC)
    {
        Result += "FragDiffuseColor *= Diffuse;\n";
    }
    else
    {
        Result += "FragDiffuseColor *= texture2D(DiffuseTexture,gl_TexCoord[0].st).r;\n";
    }

    for(unsigned int i(0) ; i<getNumLights() ; ++i)
    {
	    Result += 
	    "        //Light " + boost::lexical_cast<std::string>(i) + "\n"
        "        Dist = length(LightDir[" + boost::lexical_cast<std::string>(i) + "]);\n"
	    "        LightDirNorm = LightDir[" + boost::lexical_cast<std::string>(i) + "]/Dist;\n"
         
	    "        nDotL = max(0.0, dot(Normal, LightDirNorm));\n"
        
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

	    "        //Diffuse\n"
        "        FragColor += FragDiffuseColor * gl_LightSource[" + boost::lexical_cast<std::string>(i) + "].diffuse.rgb * nDotL * 1.5;\n";
        //"        FragColor += FragDiffuseColor * nDotL;\n";
    }
    
	Result += 
        "    //Global Ambient\n"
        "    FragColor += gl_LightModel.ambient.rgb * FragAmbientColor;\n";
        
        "    //Incandescence\n";
	if(getIncandescenceTexture() != NullFC)
	{
		Result += "    FragColor += texture2D(IncandescenceTexture,gl_TexCoord[0].st).rgb;\n";
	}
	else
	{
		Result += "    FragColor += Incandescence;\n";
	}
    
	Result += "    gl_FragColor = vec4(FragColor,";
	if(getTransparencyTexture() != NullFC)
	{
        if(getTransparencyTexture()->getImage()->hasAlphaChannel())
        {
		    Result += "texture2D(TransparencyTexture,gl_TexCoord[0].st).a * gl_Color.a";
        }
        else
        {
		    Result += "(1.0-texture2D(TransparencyTexture,gl_TexCoord[0].st).r) * gl_Color.a";
        }
	}
	else if(getTransparencyTexture() == NullFC && isTransparent())
    {
		//Result += "0.3*Transparency.r + 0.59*Transparency.g + 0.11*Transparency.b";
		Result += "(1.0-Transparency.r) * gl_Color.a";
	}
	else
    {
		Result += "gl_Color.a";
	}
	Result += ");\n"
	"}\n";
    return Result;
}


bool LambertMaterial::shouldRecreateChunks(BitVector FieldMask) const
{
    return (FieldMask & NumLightsFieldMask) ||
        (FieldMask & ColorTextureFieldMask) ||
        (FieldMask & TransparencyFieldMask) ||
        (FieldMask & TransparencyTextureFieldMask) ||
        (FieldMask & AmbientColorTextureFieldMask) ||
        (FieldMask & IncandescenceTextureFieldMask) ||
        (FieldMask & BumpDepthTextureFieldMask) ||
        (FieldMask & NormalMapTextureFieldMask) ||
        (FieldMask & DiffuseTextureFieldMask) ||
        (FieldMask & TransleucenceTextureFieldMask) ||
        (FieldMask & TransleucenceDepthTextureFieldMask) ||
        (FieldMask & TransleucenceFocusTextureFieldMask);
}

bool LambertMaterial::shouldUpdateParameters(BitVector FieldMask) const
{
    return (FieldMask & ColorFieldMask) ||
        (FieldMask & TransparencyFieldMask) ||
        (FieldMask & AmbientColorFieldMask) ||
        (FieldMask & IncandescenceFieldMask) ||
        (FieldMask & BumpDepthFieldMask) ||
        (FieldMask & DiffuseFieldMask) ||
        (FieldMask & TransleucenceFieldMask) ||
        (FieldMask & TransleucenceDepthFieldMask) ||
        (FieldMask & TransleucenceFocusFieldMask);
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
    getChunks().clear();
}

/*----------------------------- class specific ----------------------------*/

void LambertMaterial::onCreate(const LambertMaterial *source)
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

void LambertMaterial::onDestroy(void)
{
    subRefCP(getShader());
    setShader(NullFC);

    subRefCP(getParameters());
    setParameters(NullFC);
}

void LambertMaterial::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    //Do the Chunks attached need to be redone
    if(shouldRecreateChunks(whichField) || whichField & ExtraChunksFieldMask)
    {
        //Need to attach the chunks
        attachChunks();
    }

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

void LambertMaterial::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump LambertMaterial NI" << std::endl;
}


OSG_END_NAMESPACE

