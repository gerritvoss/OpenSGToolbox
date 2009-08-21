/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                 Authors: David Kabala, Daniel Guilliams                   *
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
#include "OSGMaterials.h"

#include <OpenSG/OSGLineChunk.h>
#include <OpenSG/OSGBlendChunk.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/OSGPolygonChunk.h>
#include <OpenSG/OSGSHLChunk.h>
#include <OpenSG/OSGSHLParameterChunk.h>
#include <OpenSG/OSGShaderParameterVec4f.h>
#include <OpenSG/OSGShaderParameterVec3f.h>
#include <OpenSG/OSGShaderParameterReal.h>
#include <OpenSG/OSGShaderParameterBool.h>
#include <OpenSG/OSGMultiPassMaterial.h>
#include <OpenSG/OSGDepthChunk.h>
#include <OpenSG/OSGCubeTextureChunk.h>
#include <OpenSG/OSGImageFileHandler.h>
#include <sstream>

OSG_BEGIN_NAMESPACE

struct GoochMaterial {

	MaterialPtr operator()(void)
	{
		return createGoochMaterial();
	}
};

struct SimpleGlassMaterial {

	MaterialPtr operator()(void)
	{
		return createSimpleGlassMaterial();
	}
};

struct ComplexGlassMaterial {

	MaterialPtr operator()(void)
	{
		return createComplexGlassMaterial();
	}
};

struct InitMaterials{
	InitMaterials()
	{
		MaterialLibrary::MaterialFunction f = GoochMaterial();
		MaterialLibrary::the()->addMaterialFunction("Gooch", f);
		f = SimpleGlassMaterial();
		MaterialLibrary::the()->addMaterialFunction("SimpleGlass", f);
		f = ComplexGlassMaterial();
		MaterialLibrary::the()->addMaterialFunction("ComplexGlass", f);
	}
} MyInitMaterials;

CubeTextureChunkPtr createCubeTextureChunk(void)
{
	// for background reflections off of material, may need to change file location, etc...
	ImagePtr CubeTextureFront = ImageFileHandler::the().read("./Data/cell_front.jpg");
	ImagePtr CubeTextureBack = ImageFileHandler::the().read("./Data/cell_back.jpg");
	ImagePtr CubeTextureLeft = ImageFileHandler::the().read("./Data/cell_left.jpg");
	ImagePtr CubeTextureRight = ImageFileHandler::the().read("./Data/cell_right.jpg");
	ImagePtr CubeTextureTop = ImageFileHandler::the().read("./Data/cell_top.jpg");
	ImagePtr CubeTextureBottom = ImageFileHandler::the().read("./Data/cell_bottom.jpg");
	CubeTextureChunkPtr CubeTexture = CubeTextureChunk::create();
	beginEditCP(CubeTexture);
		CubeTexture->setNegXImage(CubeTextureLeft);
		CubeTexture->setNegYImage(CubeTextureBottom);
		CubeTexture->setImage(CubeTextureFront); // negative Z
		CubeTexture->setPosXImage(CubeTextureRight);
		CubeTexture->setPosYImage(CubeTextureTop);
		CubeTexture->setPosZImage(CubeTextureBack);
	endEditCP(CubeTexture);

	return CubeTexture;
}

// create a gooch material
MaterialPtr createGoochMaterial(Vec4f WarmColor, Vec4f CoolColor, Vec4f SurfaceColor, Real32 DiffuseWarm, Real32 DiffuseCool, Real32 OutlineWidth)
{
	/*	 Creating Shader Materials and Parameters
		 Creating the materials/chunks used by OpenSG to implement a shader */
	BlendChunkPtr ExampleBlendChunk = BlendChunk::create();
	beginEditCP(ExampleBlendChunk);
	    ExampleBlendChunk->setSrcFactor(GL_SRC_ALPHA);
	    ExampleBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
	endEditCP(ExampleBlendChunk);

	//Material Chunk
	MaterialChunkPtr ShaderMaterialChunk = MaterialChunk::create();
	beginEditCP(ShaderMaterialChunk);
		ShaderMaterialChunk->setAmbient(Color4f(0.4f,0.4f,0.4f,1.0f));
		ShaderMaterialChunk->setDiffuse(Color4f(0.7f,0.7f,0.7f,1.0f));
		ShaderMaterialChunk->setSpecular(Color4f(1.0f,1.0f,1.0f,1.0f));
	endEditCP(ShaderMaterialChunk);

	// Polygon Chunk
	PolygonChunkPtr GoochShaderPolyChunk = PolygonChunk::create();
	beginEditCP(GoochShaderPolyChunk);
		GoochShaderPolyChunk->setCullFace(GL_BACK);
		GoochShaderPolyChunk->setBackMode(GL_FILL);
		GoochShaderPolyChunk->setFrontMode(GL_FILL);
	beginEditCP(GoochShaderPolyChunk);
	
	//Depth Chunk 
	DepthChunkPtr GoochDepthChunk = DepthChunk::create();
	beginEditCP(GoochDepthChunk);		
		GoochDepthChunk->setFunc(GL_LESS);
	endEditCP(GoochDepthChunk);

	//Shader Chunk
	SHLChunkPtr TheSHLChunk = SHLChunk::create();
	beginEditCP(TheSHLChunk);
		TheSHLChunk->setVertexProgram(createSHLVertexProgGooch());
		TheSHLChunk->setFragmentProgram(createSHLFragProgGooch());
	endEditCP(TheSHLChunk);

	//Shader Parameters
	ShaderParameterVec4fPtr WarmColorParameter = ShaderParameterVec4f::create();
	beginEditCP(WarmColorParameter);
		WarmColorParameter->setName("WarmColor");
		WarmColorParameter->setValue(WarmColor);
	endEditCP(WarmColorParameter);
	
	ShaderParameterVec4fPtr CoolColorParameter = ShaderParameterVec4f::create();
	beginEditCP(CoolColorParameter);
		CoolColorParameter->setName("CoolColor");
		CoolColorParameter->setValue(CoolColor);
	endEditCP(CoolColorParameter);

	ShaderParameterVec4fPtr SurfaceColorParameter = ShaderParameterVec4f::create();
	beginEditCP(SurfaceColorParameter);
		SurfaceColorParameter->setName("SurfaceColor");
		SurfaceColorParameter->setValue(SurfaceColor);
	endEditCP(SurfaceColorParameter);

	ShaderParameterRealPtr DiffuseWarmParameter = ShaderParameterReal::create();
	beginEditCP(DiffuseWarmParameter);
		DiffuseWarmParameter->setName("DiffuseWarm");
		DiffuseWarmParameter->setValue(DiffuseWarm);
	endEditCP(DiffuseWarmParameter);

	ShaderParameterRealPtr DiffuseCoolParameter = ShaderParameterReal::create();
	beginEditCP(DiffuseCoolParameter);
		DiffuseCoolParameter->setName("DiffuseCool");
		DiffuseCoolParameter->setValue(DiffuseCool);
	endEditCP(DiffuseCoolParameter);

	//Shader Parameter Chunk
	SHLParameterChunkPtr SHLParameters = SHLParameterChunk::create();
	beginEditCP(SHLParameters);
		SHLParameters->getParameters().push_back(WarmColorParameter);
		SHLParameters->getParameters().push_back(CoolColorParameter);
		SHLParameters->getParameters().push_back(SurfaceColorParameter);
		SHLParameters->getParameters().push_back(DiffuseWarmParameter);
		SHLParameters->getParameters().push_back(DiffuseCoolParameter);
		SHLParameters->setSHLChunk(TheSHLChunk);
	endEditCP(SHLParameters);

	// adding all materials
	ChunkMaterialPtr GoochMaterial = ChunkMaterial::create();
	beginEditCP(GoochMaterial, ChunkMaterial::ChunksFieldMask);
		GoochMaterial->addChunk(ShaderMaterialChunk);
		GoochMaterial->addChunk(TheSHLChunk);
		GoochMaterial->addChunk(SHLParameters);
		GoochMaterial->addChunk(GoochShaderPolyChunk);
		GoochMaterial->addChunk(GoochDepthChunk);
	endEditCP(GoochMaterial, ChunkMaterial::ChunksFieldMask);

	
	// Mulit-Pass material to combine gooch and black outline shading
	MultiPassMaterialPtr ShaderMaterial = MultiPassMaterial::create();
	beginEditCP(ShaderMaterial);
		ShaderMaterial->addMaterial(GoochMaterial);
		ShaderMaterial->addMaterial(createBlackOutlineMaterial(OutlineWidth));
	endEditCP(ShaderMaterial);

	return ShaderMaterial;
}

std::string createSHLVertexProgGooch(void)
{
	std::ostringstream VertexProgStream;
	VertexProgStream
	<< "varying vec3 ReflectVec;\n"
	<< "varying vec3 ViewVec;\n"
	<< "varying float NdotL;\n"

	<< "void main(void)\n"
	<< "{ \n"
	<< "  vec3 ecPos = vec3(gl_ModelViewMatrix * gl_Vertex);\n"
	<< "  ViewVec = normalize(-ecPos);\n"
	<< "  vec3 tnorm = normalize(gl_NormalMatrix * gl_Normal);\n"
	<< "  vec3 lightVec = normalize(gl_LightSource[0].position - ecPos);\n"
	<< "  ReflectVec = normalize(reflect(-lightVec, tnorm));\n"
	<< "  NdotL = dot(lightVec, tnorm) * 0.5 + 0.5;\n"
	<< "  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n" 
	<< "}\n" ;

	return  VertexProgStream.str();
}

std::string createSHLFragProgGooch(void)
{
	std::ostringstream FragProgStream;

	FragProgStream
	<< "uniform vec4 SurfaceColor;\n" 
	<< "uniform vec4 WarmColor;\n" 
	<< "uniform vec4 CoolColor;\n" 
	<< "uniform float DiffuseWarm;\n" 
	<< "uniform float DiffuseCool;\n" 
	<< "float NdotL;\n" 
	<< "vec3 ReflectVec;\n" 
	<< "vec3 ViewVec;\n" 
	<< "void main(void)\n" 
	<< "{\n" 
	<< "   vec3 kcool = min(CoolColor.xyz + DiffuseCool * SurfaceColor.xyz,1.0);\n" 
	<< "   vec3 kwarm = min(WarmColor.xyz + DiffuseWarm * SurfaceColor.xyz,1.0);\n" 
	<< "   vec3 kfinal = mix(kcool,kwarm,NdotL);\n" 
	<< "   vec3 nreflect = normalize(ReflectVec);\n" 
	<< "   vec3 nview = normalize(ViewVec); \n" 
	<< "   float spec = max(dot(nreflect, nview), 0.0);\n" 
 	<< "   spec = pow(spec, 32.0);\n" 
	<< "   gl_FragColor = vec4(min(kfinal + spec, 1.0), 1.0);\n" 
	<< "}\n" ;

	return  FragProgStream.str();
}

MaterialPtr createBlackOutlineMaterial(Real32 OutlineWidth)
{
	//Black outline shading materials
		//Material Chunk
	MaterialChunkPtr ShaderMaterialChunk = MaterialChunk::create();
	beginEditCP(ShaderMaterialChunk);
		ShaderMaterialChunk->setAmbient(Color4f(0.4f,0.4f,0.4f,1.0f));
		ShaderMaterialChunk->setDiffuse(Color4f(0.7f,0.7f,0.7f,1.0f));
		ShaderMaterialChunk->setSpecular(Color4f(1.0f,1.0f,1.0f,1.0f));
	endEditCP(ShaderMaterialChunk);

	SHLChunkPtr TheBlackSHLChunk = SHLChunk::create();
	beginEditCP(TheBlackSHLChunk);
		TheBlackSHLChunk->setVertexProgram(createSHLVertexProgBlack());
		TheBlackSHLChunk->setFragmentProgram(createSHKFragProgBlack());
	endEditCP(TheBlackSHLChunk);

	// line chunk for setting width of outline
	LineChunkPtr BlackShaderLineChunk = LineChunk::create();
	beginEditCP(BlackShaderLineChunk);
		BlackShaderLineChunk->setWidth(OutlineWidth);
		BlackShaderLineChunk->setSmooth(false);
	endEditCP(BlackShaderLineChunk);

	// only drawing back-facing polygons
	PolygonChunkPtr BlackShaderPolyChunk = PolygonChunk::create();
	beginEditCP(BlackShaderPolyChunk);
		BlackShaderPolyChunk->setCullFace(GL_FRONT);
		BlackShaderPolyChunk->setBackMode(GL_LINE);
	beginEditCP(BlackShaderPolyChunk);

	// depth chunk for black outlining
	DepthChunkPtr BlackDepthChunk = DepthChunk::create();
	beginEditCP(BlackDepthChunk);		
		BlackDepthChunk->setFunc(GL_LEQUAL);
	endEditCP(BlackDepthChunk);

	ChunkMaterialPtr BlackFragmentMaterial = ChunkMaterial::create();
	beginEditCP(BlackFragmentMaterial, ChunkMaterial::ChunksFieldMask);
		BlackFragmentMaterial->addChunk(ShaderMaterialChunk);
		BlackFragmentMaterial->addChunk(TheBlackSHLChunk);
		BlackFragmentMaterial->addChunk(BlackShaderPolyChunk);
		BlackFragmentMaterial->addChunk(BlackShaderLineChunk);
		BlackFragmentMaterial->addChunk(BlackDepthChunk);
	endEditCP(BlackFragmentMaterial, ChunkMaterial::ChunksFieldMask);

	return BlackFragmentMaterial;
}

std::string createSHLVertexProgBlack(void)
{
	return "";
}
std::string createSHKFragProgBlack(void)
{
	std::ostringstream FragProgStream;

	FragProgStream
	<< "void main(void)\n"
	<< "{\n"
    << "\tgl_FragColor = vec4( 0.0, 0.0, 0.0, 1.0 );\n"
	<< "}\n";

	return FragProgStream.str();
}

MaterialPtr createSimpleGlassMaterial(Real32 Rainbowiness, CubeTextureChunkPtr Environment)
{

	BlendChunkPtr ExampleBlendChunk = BlendChunk::create();
	beginEditCP(ExampleBlendChunk);
	    ExampleBlendChunk->setSrcFactor(GL_SRC_ALPHA);
	    ExampleBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
	endEditCP(ExampleBlendChunk);

	//Depth Chunk, default parameters used 
	DepthChunkPtr GlassDepthChunk = DepthChunk::create();
	
	// culling back-facing polygons
	PolygonChunkPtr GlassShaderPolyChunk = PolygonChunk::create();
	beginEditCP(GlassShaderPolyChunk);
		GlassShaderPolyChunk->setCullFace(GL_BACK);
	beginEditCP(GlassShaderPolyChunk);

	//Material Chunk
	MaterialChunkPtr ShaderMaterialChunk = MaterialChunk::create();
	beginEditCP(ShaderMaterialChunk);
		ShaderMaterialChunk->setAmbient(Color4f(0.4f,0.4f,0.4f,1.0f));
		ShaderMaterialChunk->setDiffuse(Color4f(0.7f,0.7f,0.7f,1.0f));
		ShaderMaterialChunk->setSpecular(Color4f(1.0f,1.0f,1.0f,1.0f));
	endEditCP(ShaderMaterialChunk);

	// creating actual shader programs
	SHLChunkPtr TheSHLChunk = SHLChunk::create();
	beginEditCP(TheSHLChunk);
		TheSHLChunk->setVertexProgram(createSimpleGlassVertexProg());
		TheSHLChunk->setFragmentProgram(createSimpleGlassFragProg());
	endEditCP(TheSHLChunk);

	// intensity of diffraction off of 'glass'
	ShaderParameterRealPtr RainbowParameter = ShaderParameterReal::create();
	beginEditCP(RainbowParameter);
		RainbowParameter->setName("rainbowiness");
		RainbowParameter->setValue(Rainbowiness);
	endEditCP(RainbowParameter);
	SHLParameterChunkPtr SHLParameters = SHLParameterChunk::create();
	beginEditCP(SHLParameters);
		SHLParameters->getParameters().push_back(RainbowParameter);
		SHLParameters->setSHLChunk(TheSHLChunk);
	endEditCP(SHLParameters);

	// assembling material
	ChunkMaterialPtr SimpleGlassMaterial = ChunkMaterial::create();
	beginEditCP(SimpleGlassMaterial, ChunkMaterial::ChunksFieldMask);
		SimpleGlassMaterial->addChunk(ShaderMaterialChunk);
		SimpleGlassMaterial->addChunk(SHLParameters);
		SimpleGlassMaterial->addChunk(TheSHLChunk);
		SimpleGlassMaterial->addChunk(ExampleBlendChunk);
		SimpleGlassMaterial->addChunk(Environment);
		SimpleGlassMaterial->addChunk(GlassDepthChunk);
		SimpleGlassMaterial->addChunk(GlassShaderPolyChunk);
	endEditCP(SimpleGlassMaterial, ChunkMaterial::ChunksFieldMask);

	return SimpleGlassMaterial;

}

std::string createSimpleGlassVertexProg(void)
{
	std::ostringstream VertexProgStream;

	VertexProgStream
	<< "varying vec3 vNormal;\n"
	<< "varying vec3 vViewVec;\n"
	<< "void main(void)\n"
	<< "{\n"
	<< "   vec3 u = vec3(gl_ModelViewMatrix[0][0],gl_ModelViewMatrix[1][0],gl_ModelViewMatrix[2][0]);\n"
	<< "   vec3 v = vec3(gl_ModelViewMatrix[0][1],gl_ModelViewMatrix[1][1],gl_ModelViewMatrix[2][1]);\n"
	<< "   vec3 n = vec3(gl_ModelViewMatrix[0][2],gl_ModelViewMatrix[1][2],gl_ModelViewMatrix[2][2]);\n"
	<< "   vec3 d = vec3(gl_ModelViewMatrix[3][0],gl_ModelViewMatrix[3][1],gl_ModelViewMatrix[3][2]);\n"
	<< "   vec4 p = vec4(-vec3((d.x*u) + (d.y*v) + (d.z*n)),1.0);\n" // eye pos in WS
	<< "    vViewVec = p.xyz - gl_Vertex.xyz;\n"
	<< "	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;;\n"
	<< "	vNormal = normalize(gl_Normal);\n"
	<< "}\n";

	return VertexProgStream.str();
}

std::string createSimpleGlassFragProg(void)
{
	std::ostringstream FragProgStream;

	FragProgStream
	<< "uniform samplerCube Environment;\n"
	<< "uniform float rainbowiness;\n"
	<< "varying vec3 vNormal;\n"
	<< "varying vec3 vViewVec;\n"
	<< "vec3 HSVtoRGB(vec3 HSV)\n"
	<< "{\n"
	<< "   vec3 RGB;\n"
	<< "   float f,p,q,t,h = HSV.x/60.0; \n"
	<< "   int i = floor(h);\n"
	<< "   f = h-i;\n"    
	<< "   p = HSV.z*(1-HSV.y);\n"
	<< "   q = HSV.z*(1-HSV.y*f);\n"
	<< "  t = HSV.z*(1-HSV.y*(1-f));\n"
	<< "   switch(i) \n"
	<< "   {\n"
	<< "	  case 0:\n"
	<< "		 RGB = vec3(HSV.z,t,p);\n"
	<< "		 break;\n"
	<< "	  case 1:\n"
	<< "		 RGB = vec3(q,HSV.z,p);\n"
	<< "		 break;\n"
	<< "	  case 2:\n"
	<< "		 RGB = vec3(p,HSV.z,t);\n"
	<< "		 break;\n"
	<< "	  case 3:\n"
	<< "		 RGB = vec3(p,q,HSV.z);\n"
	<< "		 break;\n"
	<< "	  case 4:\n"
	<< "		 RGB = vec3(t,p,HSV.z);\n"
	<< "		 break;\n"
	<< "	  case 5:\n"
	<< "		 RGB = vec3(HSV.z,p,q);\n"
	<< "		 break;\n"
	<< "	  default: // default to case 5\n"
	<< "		 RGB = vec3(HSV.z,p,q);\n"
	<< "		 break;\n"
	<< "   }\n"
	<< "   return RGB;\n"
	<< "}\n"
	<< "void main(void)\n"
	<< "{\n"
	<< "   vec3 normal = normalize(vNormal);\n"
	<< "   vec3 view =  normalize(vViewVec);\n"
	<< "   float v =  dot(view, normal);\n"
	<< "   // get rainbow-ish color\n"
	<< "   vec3 rainbow = HSVtoRGB(vec3(v*360.0,1.0,1.0)); // convert v to degrees before sending to func\n"
	<< "   // Find the reflection\n"
	<< "   vec3 reflVec =  reflect(-vViewVec, normal);\n"
	<< "   vec3 refl = textureCube(Environment, reflVec).xyz;\n"
	<< "   // mix colors from rainbow and env\n"
	<< "   vec3 color = mix(refl, rainbow, rainbowiness * v);\n"
	<< "   gl_FragColor = vec4 (color, 1.0 - v); \n" 
	<< "}\n";

	return FragProgStream.str();

	//gl_FragColor = vec4 (color, 1.0 - v);
}

MaterialPtr createComplexGlassMaterial(Real32 IndexOfRefractionRatio, Vec3f IORDisplacements, Real32 FresnelPower, bool ChromaticAbberation, CubeTextureChunkPtr Environment)
{	
	BlendChunkPtr ExampleBlendChunk = BlendChunk::create();
	beginEditCP(ExampleBlendChunk);
	    ExampleBlendChunk->setSrcFactor(GL_SRC_ALPHA);
	    ExampleBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
	endEditCP(ExampleBlendChunk);

	//Depth Chunk, default parameters used 
	DepthChunkPtr GlassDepthChunk = DepthChunk::create();
	
	// culling back-facing polygons
	PolygonChunkPtr GlassShaderPolyChunk = PolygonChunk::create();
	beginEditCP(GlassShaderPolyChunk);
		GlassShaderPolyChunk->setCullFace(GL_BACK);
	beginEditCP(GlassShaderPolyChunk);

	//Material Chunk
	MaterialChunkPtr ShaderMaterialChunk = MaterialChunk::create();
	beginEditCP(ShaderMaterialChunk);
		ShaderMaterialChunk->setAmbient(Color4f(0.4f,0.4f,0.4f,1.0f));
		ShaderMaterialChunk->setDiffuse(Color4f(0.7f,0.7f,0.7f,1.0f));
		ShaderMaterialChunk->setSpecular(Color4f(1.0f,1.0f,1.0f,1.0f));
	endEditCP(ShaderMaterialChunk);

	// creating actual shader programs
	SHLChunkPtr TheSHLChunk = SHLChunk::create();
	beginEditCP(TheSHLChunk);
		TheSHLChunk->setVertexProgram(createComplexGlassVertexProg());
		TheSHLChunk->setFragmentProgram(createComplexGlassFragProg());
	endEditCP(TheSHLChunk);

	// parameters for diffraction off of 'glass'
	ShaderParameterRealPtr IdxOfRefractionRatio = ShaderParameterReal::create();
	beginEditCP(IdxOfRefractionRatio);
		IdxOfRefractionRatio->setName("IndexOfRefractionRatio");
		IdxOfRefractionRatio->setValue(IndexOfRefractionRatio);
	endEditCP(IdxOfRefractionRatio);

	ShaderParameterRealPtr FresnelPowerParameter = ShaderParameterReal::create();
	beginEditCP(FresnelPowerParameter);
		FresnelPowerParameter->setName("FresnelPower");
		FresnelPowerParameter->setValue(FresnelPower);
	endEditCP(FresnelPowerParameter);

	ShaderParameterVec3fPtr IORDisplacementsParam = ShaderParameterVec3f::create();
	beginEditCP(IORDisplacementsParam);
		IORDisplacementsParam->setName("IOR_displacements");
		IORDisplacementsParam->setValue(IORDisplacements);
	endEditCP(IORDisplacementsParam);

	ShaderParameterBoolPtr UseChromaticAbberation = ShaderParameterBool::create();
	beginEditCP(UseChromaticAbberation);
		UseChromaticAbberation->setName("ChromaticAbberation");
		UseChromaticAbberation->setValue(ChromaticAbberation);
	endEditCP(UseChromaticAbberation);

	SHLParameterChunkPtr SHLParameters = SHLParameterChunk::create();
	beginEditCP(SHLParameters);
		SHLParameters->getParameters().push_back(UseChromaticAbberation);
		SHLParameters->getParameters().push_back(IdxOfRefractionRatio);
		SHLParameters->getParameters().push_back(IORDisplacementsParam);
		SHLParameters->getParameters().push_back(FresnelPowerParameter);
		SHLParameters->setSHLChunk(TheSHLChunk);
	endEditCP(SHLParameters);

	// assembling material
	ChunkMaterialPtr ComplexGlassMaterial = ChunkMaterial::create();
	beginEditCP(ComplexGlassMaterial, ChunkMaterial::ChunksFieldMask);
		ComplexGlassMaterial->addChunk(ShaderMaterialChunk);
		ComplexGlassMaterial->addChunk(SHLParameters);
		ComplexGlassMaterial->addChunk(TheSHLChunk);
		ComplexGlassMaterial->addChunk(ExampleBlendChunk);
		ComplexGlassMaterial->addChunk(Environment);
		ComplexGlassMaterial->addChunk(GlassDepthChunk);
		ComplexGlassMaterial->addChunk(GlassShaderPolyChunk);
	endEditCP(ComplexGlassMaterial, ChunkMaterial::ChunksFieldMask);

	return ComplexGlassMaterial;
}

std::string createComplexGlassVertexProg(void)
{
	std::ostringstream VertexProgStream;

	VertexProgStream
	<< "uniform bool ChromaticAbberation;\n"

	<< "uniform float IndexOfRefractionRatio;\n"
	<< "uniform vec3 IOR_displacements;\n"

	<< "uniform float FresnelPower;\n"

	<< "varying vec3 Reflect;\n"
	<< "varying vec3 RefractR;\n"
	<< "varying vec3 RefractG;\n"
	<< "varying vec3 RefractB;\n"
	<< "varying float Ratio;\n"

	<< "void main(void)\n"
	<< "{\n"
	<< "   vec3 u = vec3(gl_ModelViewMatrix[0][0],gl_ModelViewMatrix[1][0],gl_ModelViewMatrix[2][0]);\n"
	<< "   vec3 v = vec3(gl_ModelViewMatrix[0][1],gl_ModelViewMatrix[1][1],gl_ModelViewMatrix[2][1]);\n"
	<< "   vec3 n = vec3(gl_ModelViewMatrix[0][2],gl_ModelViewMatrix[1][2],gl_ModelViewMatrix[2][2]);\n"
	<< "   vec3 d = vec3(gl_ModelViewMatrix[3][0],gl_ModelViewMatrix[3][1],gl_ModelViewMatrix[3][2]);\n"
	   
	<< "   vec4 p = vec4(-vec3((d.x*u) + (d.y*v) + (d.z*n)),1.0);\n" // eye position in world space

	<< "  vec3 i = -normalize(p.xyz-gl_Vertex.xyz);\n"
	<< "  vec3 normal = normalize(gl_Normal);\n"

	<< "   float F = ((1.0-IndexOfRefractionRatio) * (1.0-IndexOfRefractionRatio))/((1.0+IndexOfRefractionRatio) * (1.0+IndexOfRefractionRatio));\n"
	<< "   Ratio = F + (1.0 - F) * pow((1.0 - dot(-i,normal)), FresnelPower);\n"

	<< "	if(ChromaticAbberation)\n"
	<< "   {\n"
	<< "	 RefractR = vec3(gl_TextureMatrix[0] * vec4(refract(i,normal,IndexOfRefractionRatio+IOR_displacements.r),1.0));\n"
	<< "	 RefractG = vec3(gl_TextureMatrix[0] * vec4(refract(i,normal,IndexOfRefractionRatio+IOR_displacements.g),1.0));\n"
	  
	<< "	 RefractB = vec3(gl_TextureMatrix[0] * vec4(refract(i,normal,IndexOfRefractionRatio+IOR_displacements.b),1.0));\n"
	<< "   } \n"
	<< "   else\n"
	<< "   {\n"
	<< "	 RefractR = refract(i,normal, IndexOfRefractionRatio);\n"
	<< "	 RefractR = normalize(vec3(gl_TextureMatrix[0] * vec4(RefractR,1.0)));\n"
	<< "	}\n"

	<< "   Reflect = ( vec4(reflect(i,normal),1.0)).xyz;\n"
	<< "   Reflect = vec3(gl_TextureMatrix[0] * vec4(Reflect,1.0));\n"

	<< "   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
	<< "}\n";

	return VertexProgStream.str();

}

std::string createComplexGlassFragProg(void)
{
	std::ostringstream FragProgStream;

	FragProgStream

	<< "uniform samplerCube Environment;\n"
	<< "uniform bool ChromaticAbberation;\n"

	<< "varying vec3 Reflect;\n"
	<< "varying vec3 RefractR;\n"
	<< "varying vec3 RefractG;\n"
	<< "varying vec3 RefractB;\n"
	<< "varying float Ratio;\n"

	<< "void main(void)\n"
	<< "{\n"
	<< "   vec3 refractColor, reflectColor;\n"

	<< "   if(ChromaticAbberation)\n"
	<< "   {\n"
	<< "	 refractColor.r = textureCube(Environment, RefractR).r;\n"
	<< "	 refractColor.g = textureCube(Environment, RefractG).g;\n"
	<< "	 refractColor.b = textureCube(Environment, RefractB).b;\n"
	<< "  }\n"
	<< "   else\n"
	<< "   {\n"
	<< "	 refractColor = textureCube(Environment,RefractR).rgb;\n"
	<< "   }\n"

	<< "   reflectColor = textureCube(Environment, Reflect).rgb;\n"

	<< "   vec3 color = mix(refractColor, reflectColor, Ratio);\n"
	<< "   gl_FragColor = vec4(color, 1.0);\n"
	<< "}\n";

	return FragProgStream.str();
}


OSG_END_NAMESPACE