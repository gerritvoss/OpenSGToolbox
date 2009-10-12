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

#include "OSGAnisotropicMaterial.h"
#include <OpenSG/OSGSHLParameterChunk.h>
#include <OpenSG/OSGSHLChunk.h>
#include <OpenSG/OSGTextureChunk.h>
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGShaderParameterInt.h>
#include <OpenSG/OSGShaderParameterReal.h>
#include <OpenSG/OSGShaderParameterVec3f.h>
#include <OpenSG/OSGShaderParameterVec4f.h>

#include "OSGMaterialLibrary.h"
#include <boost/lexical_cast.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AnisotropicMaterial

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AnisotropicMaterial::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
void AnisotropicMaterial::internalCreateShaderParameters(void)
{
    Inherited::internalCreateShaderParameters();
    
    //SpecularAngle
    if(getSpecularAngleTexture() == NullFC)
    {
        ShaderParameterRealPtr SpecularAngleParam = ShaderParameterReal::create();
        SpecularAngleParam->setName("SpecularAngle");
        getParameters()->getParameters().push_back(SpecularAngleParam);
    }
    else
    {
        ShaderParameterIntPtr SpecularAngleTexParam = ShaderParameterInt::create();
        SpecularAngleTexParam->setName("SpecularAngleTexture");
        getParameters()->getParameters().push_back(SpecularAngleTexParam);
    }
    
    //SpecularSpreadX
    if(getSpecularSpreadXTexture() == NullFC)
    {
        ShaderParameterRealPtr SpecularSpreadXParam = ShaderParameterReal::create();
        SpecularSpreadXParam->setName("SpecularSpreadX");
        getParameters()->getParameters().push_back(SpecularSpreadXParam);
    }
    else
    {
        ShaderParameterIntPtr SpecularSpreadXTexParam = ShaderParameterInt::create();
        SpecularSpreadXTexParam->setName("SpecularSpreadXTexture");
        getParameters()->getParameters().push_back(SpecularSpreadXTexParam);
    }
    
    //SpecularSpreadY
    if(getSpecularSpreadYTexture() == NullFC)
    {
        ShaderParameterRealPtr SpecularSpreadYParam = ShaderParameterReal::create();
        SpecularSpreadYParam->setName("SpecularSpreadY");
        getParameters()->getParameters().push_back(SpecularSpreadYParam);
    }
    else
    {
        ShaderParameterIntPtr SpecularSpreadYTexParam = ShaderParameterInt::create();
        SpecularSpreadYTexParam->setName("SpecularSpreadYTexture");
        getParameters()->getParameters().push_back(SpecularSpreadYTexParam);
    }
    
    //SpecularRoughness
    if(getSpecularRoughnessTexture() == NullFC)
    {
        ShaderParameterRealPtr SpecularRoughnessParam = ShaderParameterReal::create();
        SpecularRoughnessParam->setName("SpecularRoughness");
        getParameters()->getParameters().push_back(SpecularRoughnessParam);
    }
    else
    {
        ShaderParameterIntPtr SpecularRoughnessTexParam = ShaderParameterInt::create();
        SpecularRoughnessTexParam->setName("SpecularRoughnessTexture");
        getParameters()->getParameters().push_back(SpecularRoughnessTexParam);
    }
    
    //SpecularFresnelIndex
    if(getSpecularFresnelIndexTexture() == NullFC)
    {
        ShaderParameterRealPtr SpecularFresnelIndexParam = ShaderParameterReal::create();
        SpecularFresnelIndexParam->setName("SpecularFresnelIndex");
        getParameters()->getParameters().push_back(SpecularFresnelIndexParam);
    }
    else
    {
        ShaderParameterIntPtr SpecularFresnelIndexTexParam = ShaderParameterInt::create();
        SpecularFresnelIndexTexParam->setName("SpecularFresnelIndexTexture");
        getParameters()->getParameters().push_back(SpecularFresnelIndexTexParam);
    }
    
    //SpecularColor
    if(getSpecularColorTexture() == NullFC)
    {
        ShaderParameterVec3fPtr SpecularColorParam = ShaderParameterVec3f::create();
        SpecularColorParam->setName("SpecularColor");
        getParameters()->getParameters().push_back(SpecularColorParam);
    }
    else
    {
        ShaderParameterIntPtr SpecularColorTexParam = ShaderParameterInt::create();
        SpecularColorTexParam->setName("SpecularColorTexture");
        getParameters()->getParameters().push_back(SpecularColorTexParam);
    }
}

void AnisotropicMaterial::internalUpdateShaderParameters(UInt8& NumTextures, UInt8& ParamIndex)
{
    Inherited::internalUpdateShaderParameters(NumTextures, ParamIndex);
    
    //SpecularAngle
    if(getSpecularAngleTexture() == NullFC)
    {
        ShaderParameterRealPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(getSpecularAngle());
        ++ParamIndex;
    }
    else
    {
        ShaderParameterIntPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(NumTextures);
        ++NumTextures;
        ++ParamIndex;
    }
    
    //SpecularSpreadX
    if(getSpecularSpreadXTexture() == NullFC)
    {
        ShaderParameterRealPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(getSpecularSpreadX());
        ++ParamIndex;
    }
    else
    {
        ShaderParameterIntPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(NumTextures);
        ++NumTextures;
        ++ParamIndex;
    }
    
    //SpecularSpreadY
    if(getSpecularSpreadYTexture() == NullFC)
    {
        ShaderParameterRealPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(getSpecularSpreadY());
        ++ParamIndex;
    }
    else
    {
        ShaderParameterIntPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(NumTextures);
        ++NumTextures;
        ++ParamIndex;
    }
    
    //SpecularRoughness
    if(getSpecularRoughnessTexture() == NullFC)
    {
        ShaderParameterRealPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(getSpecularRoughness());
        ++ParamIndex;
    }
    else
    {
        ShaderParameterIntPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(NumTextures);
        ++NumTextures;
        ++ParamIndex;
    }
    
    //SpecularFresnelIndex
    if(getSpecularFresnelIndexTexture() == NullFC)
    {
        ShaderParameterRealPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(getSpecularFresnelIndex());
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
        ShaderParameterVec3fPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(Vec3f(getSpecularColor().getValuesRGB()));
        ++ParamIndex;
    }
    else
    {
        ShaderParameterIntPtr::dcast(getParameters()->getParameters(ParamIndex))->setValue(NumTextures);
        ++NumTextures;
        ++ParamIndex;
    }
}

void AnisotropicMaterial::internalAttachChunks(void)
{
    Inherited::internalAttachChunks();

    //SpecularAngleTexture
    if(getSpecularAngleTexture() != NullFC)
    {
        getChunks().push_back(getSpecularAngleTexture());
    }

    //SpecularSpreadXTexture
    if(getSpecularSpreadXTexture() != NullFC)
    {
        getChunks().push_back(getSpecularSpreadXTexture());
    }

    //SpecularSpreadYTexture
    if(getSpecularSpreadYTexture() != NullFC)
    {
        getChunks().push_back(getSpecularSpreadYTexture());
    }

    //SpecularRoughnessTexture
    if(getSpecularRoughnessTexture() != NullFC)
    {
        getChunks().push_back(getSpecularRoughnessTexture());
    }

    //SpecularFresnelIndexTexture
    if(getSpecularFresnelIndexTexture() != NullFC)
    {
        getChunks().push_back(getSpecularFresnelIndexTexture());
    }

    //SpecularColorTexture
    if(getSpecularColorTexture() != NullFC)
    {
        getChunks().push_back(getSpecularColorTexture());
    }
}

bool AnisotropicMaterial::shouldRecreateChunks(BitVector FieldMask) const
{
    return Inherited::shouldRecreateChunks(FieldMask) ||
        (FieldMask & SpecularAngleTextureFieldMask) ||
        (FieldMask & SpecularSpreadXTextureFieldMask) ||
        (FieldMask & SpecularSpreadYTextureFieldMask) ||
        (FieldMask & SpecularRoughnessTextureFieldMask) ||
        (FieldMask & SpecularFresnelIndexTextureFieldMask) ||
        (FieldMask & SpecularColorTextureFieldMask);
}

bool AnisotropicMaterial::shouldUpdateParameters(BitVector FieldMask) const
{
    return Inherited::shouldUpdateParameters(FieldMask) ||
        (FieldMask & SpecularAngleFieldMask) ||
        (FieldMask & SpecularSpreadXFieldMask) ||
        (FieldMask & SpecularSpreadYFieldMask) ||
        (FieldMask & SpecularRoughnessFieldMask) ||
        (FieldMask & SpecularFresnelIndexFieldMask) ||
        (FieldMask & SpecularColorFieldMask);
}

std::string AnisotropicMaterial::generateVertexCode(void)
{
    std::string Result("");
	Result += "//Tangent Space Shader\n"
	"//Per pixel lighting\n"
	 
	"varying vec3 LightDir[" + boost::lexical_cast<std::string>(static_cast<UInt32>(getNumLights())) + "];\n"
	"varying vec3 ViewDir;\n"
	"varying vec3 N;\n"
	"varying vec3 T;\n"
	"varying vec3 B;\n"

	"void main()\n"
	"{\n"
	 
	 
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

std::string AnisotropicMaterial::generateFragmentCode(void)
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
    
    //SpecularAngle
	if(getSpecularAngleTexture() != NullFC)
	{
		Result += "uniform sampler2D SpecularAngleTexture;\n";
	}
    else
    {
		Result += "uniform float SpecularAngle;\n";
    }
    
    //SpecularSpreadX
	if(getSpecularSpreadXTexture() != NullFC)
	{
		Result += "uniform sampler2D SpecularSpreadXTexture;\n";
	}
    else
    {
		Result += "uniform float SpecularSpreadX;\n";
    }
    
    //SpecularSpreadY
	if(getSpecularSpreadYTexture() != NullFC)
	{
		Result += "uniform sampler2D SpecularSpreadYTexture;\n";
	}
    else
    {
		Result += "uniform float SpecularSpreadY;\n";
    }
    
    //SpecularRoughness
	if(getSpecularRoughnessTexture() != NullFC)
	{
		Result += "uniform sampler2D SpecularRoughnessTexture;\n";
	}
    else
    {
		Result += "uniform float SpecularRoughness;\n";
    }
    
    //SpecularFresnelIndex
	if(getSpecularFresnelIndexTexture() != NullFC)
	{
		Result += "uniform sampler2D SpecularFresnelIndexTexture;\n";
	}
    else
    {
		Result += "uniform float SpecularFresnelIndex;\n";
    }
    
    //SpecularColor
	if(getSpecularColorTexture() != NullFC)
	{
		Result += "uniform sampler2D SpecularColorTexture;\n";
	}
    else
    {
		Result += "uniform vec3 SpecularColor;\n";
    }
    
	Result += "varying vec3 LightDir[" + boost::lexical_cast<std::string>(static_cast<UInt32>(getNumLights())) + "];\n"
	"varying vec3 ViewDir;\n"
	"varying vec3 N;\n"
	"varying vec3 T;\n"
	"varying vec3 B;\n"

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
	"    float nDotH;\n"
	"    float power;\n"
	"    float Dist;\n"
    "    float cs;\n"
    "    float sn;\n"
    "    float cl;\n"
    "    float sl;\n";
    
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
        Result += "vec3 FragDiffuseColor = Color;\n";
    }
    else
    {
        Result += "vec3 FragDiffuseColor = texture2D(ColorTexture,gl_TexCoord[0].st).rgb;\n";
    }

    //Diffuse Coefficient
    if(getDiffuseTexture() == NullFC)
    {
        Result += "FragDiffuseColor *= Diffuse;\n";
    }
    else
    {
        Result += "FragDiffuseColor *= texture2D(DiffuseTexture,gl_TexCoord[0].st).rgb;\n";
    }

    //SpecularAngle
    if(getSpecularAngleTexture() == NullFC)
    {
        Result += "float FragSpecularAngle = (1.0-SpecularAngle) * 128.0;\n";
    }
    else
    {
        Result += "float FragSpecularAngle = (1.0-texture2D(SpecularAngleTexture,gl_TexCoord[0].st).r) * 128.0;\n";
    }
    
    //SpecularSpreadX
    if(getSpecularSpreadXTexture() == NullFC)
    {
        Result += "float FragSpecularSpreadX = SpecularSpreadX;\n";
    }
    else
    {
        Result += "float FragSpecularSpreadX = texture2D(SpecularSpreadXTexture,gl_TexCoord[0].st).r;\n";
    }
    
    //SpecularSpreadY
    if(getSpecularSpreadYTexture() == NullFC)
    {
        Result += "float FragSpecularSpreadY = SpecularSpreadY;\n";
    }
    else
    {
        Result += "float FragSpecularSpreadY = texture2D(SpecularSpreadYTexture,gl_TexCoord[0].st).r;\n";
    }
    
    //SpecularRoughness
    if(getSpecularRoughnessTexture() == NullFC)
    {
        Result += "float FragSpecularRoughness = SpecularRoughness;\n";
    }
    else
    {
        Result += "float FragSpecularRoughness = texture2D(SpecularRoughnessTexture,gl_TexCoord[0].st).r;\n";
    }
    
    //SpecularFresnelIndex
    if(getSpecularFresnelIndexTexture() == NullFC)
    {
        Result += "float FragSpecularFresnelIndex = SpecularFresnelIndex;\n";
    }
    else
    {
        Result += "float FragSpecularFresnelIndex = texture2D(SpecularFresnelIndexTexture,gl_TexCoord[0].st).r;\n";
    }
    
    //Specular Color
    if(getSpecularColorTexture() == NullFC)
    {
        Result += "vec3 FragSpecularColor = SpecularColor;\n";
    }
    else
    {
        Result += "vec3 FragSpecularColor = texture2D(SpecularColorTexture,gl_TexCoord[0].st).rgb;\n";
    }

    // Rotate tangent around the normal
    Result += 
        "vec3 FragTangent =  sin(FragSpecularAngle) * T + cos(FragSpecularAngle) * B;\n";

    for(unsigned int i(0) ; i<getNumLights() ; ++i)
    {
	    Result += 
	    "        //Light " + boost::lexical_cast<std::string>(i) + "\n"
        "        Dist = length(LightDir[" + boost::lexical_cast<std::string>(i) + "]);\n"
	    "        LightDirNorm = LightDir[" + boost::lexical_cast<std::string>(i) + "]/Dist;\n"
         
	    "        nDotL = max(0.0, dot(Normal, LightDirNorm));\n"
        
	    "        cs = -dot(ViewDirNorm, FragTangent);\n"
	    "        sn = sqrt(1.0 - cs * cs);\n"
	    "        cl =  dot(LightDirNorm.xyz, FragTangent);\n"
	    "        sl = sqrt(1.0 - cl * cl);\n"
	    "        power = pow( clamp( (cs * cl + sn * sl), 0.0, 1.0 ), FragSpecularRoughness * FragSpecularSpreadX);\n"

        "        cs = -dot(ViewDirNorm, cross(Normal, FragTangent));\n"
	    "        sn = sqrt(1.0 - cs * cs);\n"
        "        cl =  dot(LightDirNorm.xyz, cross(Normal, FragTangent));\n"
	    "        sl = sqrt(1.0 - cl * cl);\n"
	    "        power += pow( clamp( (cs * cl + sn * sl), 0.0, 1.0 ), FragSpecularRoughness * FragSpecularSpreadY);\n"
	    "        power *= FragSpecularFresnelIndex;\n"
        
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
        "        FragColor += FragDiffuseColor * gl_LightSource[" + boost::lexical_cast<std::string>(i) + "].diffuse.rgb * nDotL;\n"
        //"        FragColor += FragDiffuseColor * nDotL;\n"
        
	    "        //Specular\n"
        "        FragColor += FragSpecularColor * gl_LightSource[" + boost::lexical_cast<std::string>(i) + "].specular.rgb * power;\n";
        //"        FragColor += FragSpecularColor * power;\n"
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
    
    if(getTransparencyTexture() != NullFC)
    {
        if(getTransparencyTexture()->getImage()->hasAlphaChannel())
        {
            Result += "    gl_FragColor = vec4(FragColor,texture2D(TransparencyTexture,gl_TexCoord[0].st).a * gl_Color.a);\n";
        }
        else
        {
            Result += "vec3 Transparency = texture2D(TransparencyTexture,gl_TexCoord[0].st).rgb;\n";
            Result += "    gl_FragColor = vec4(FragColor,max(Transparency.r,max(Transparency.g,Transparency.b)) * gl_Color.a);\n";
        }
    }
    else if(getTransparencyTexture() == NullFC && isTransparent())
    {
        //Result += "0.3*Transparency.r + 0.59*Transparency.g + 0.11*Transparency.b";
        Result += "    gl_FragColor = vec4(FragColor,1.0-max(Transparency.r,max(Transparency.g,Transparency.b)) * gl_Color.a);\n";
    }
    else
    {
        Result += "    gl_FragColor = vec4(FragColor,gl_Color.a);\n";
    }
	Result += "}\n";
    return Result;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AnisotropicMaterial::AnisotropicMaterial(void) :
    Inherited()
{
}

AnisotropicMaterial::AnisotropicMaterial(const AnisotropicMaterial &source) :
    Inherited(source)
{
}

AnisotropicMaterial::~AnisotropicMaterial(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AnisotropicMaterial::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void AnisotropicMaterial::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump AnisotropicMaterial NI" << std::endl;
}


OSG_END_NAMESPACE

