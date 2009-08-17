// 
// OpenSGToolbox Tutorial: 04ShaderAnimation 
//
// Demonstrates a simple animation. 
//

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGLineChunk.h>
#include <OpenSG/OSGBlendChunk.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/OSGPolygonChunk.h>
#include <OpenSG/OSGSHLChunk.h>
#include <OpenSG/OSGSHLParameterChunk.h>
#include <OpenSG/OSGShaderParameterVec4f.h>
#include <OpenSG/OSGShaderParameterReal.h>
#include <OpenSG/OSGMultiPassMaterial.h>
#include <OpenSG/OSGDepthChunk.h>

// Input
#include <OpenSG/Input/OSGKeyListener.h>
#include <OpenSG/Input/OSGWindowAdapter.h>
#include <OpenSG/Input/OSGWindowUtils.h>

// output
#include <OpenSG/Toolbox/OSGFCFileHandler.h>

#include <sstream>

//Animation
#include <OpenSG/Animation/OSGKeyframeSequences.h>
#include <OpenSG/Animation/OSGKeyframeAnimator.h>
#include <OpenSG/Animation/OSGFieldAnimation.h>
#include <OpenSG/Animation/OSGElapsedTimeAnimationAdvancer.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);
std::string createSHLVertexProgGooch(void);
std::string createSHLFragProgGooch(void);

std::string createSHLVertexProgBlack(void);
std::string createSHKFragProgBlack(void);

// Create a class to allow for the use of the keyboard shortcuts 
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEvent& e)
   {
       if(e.getKey() == KeyEvent::KEY_Q && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           TutorialWindowEventProducer->closeWindow();
       }
   }

   virtual void keyReleased(const KeyEvent& e)
   {
   }

   virtual void keyTyped(const KeyEvent& e)
   {
   }
};

class TutorialMouseListener : public MouseListener
{
  public:
    virtual void mouseClicked(const MouseEvent& e)
    {
    }
    virtual void mouseEntered(const MouseEvent& e)
    {
    }
    virtual void mouseExited(const MouseEvent& e)
    {
    }
    virtual void mousePressed(const MouseEvent& e)
    {
            mgr->mouseButtonPress(e.getButton(), e.getLocation().x(), e.getLocation().y());
    }
    virtual void mouseReleased(const MouseEvent& e)
    {
           mgr->mouseButtonRelease(e.getButton(), e.getLocation().x(), e.getLocation().y());
    }
};

class TutorialMouseMotionListener : public MouseMotionListener
{
  public:
    virtual void mouseMoved(const MouseEvent& e)
    {
            mgr->mouseMove(e.getLocation().x(), e.getLocation().y());
    }

    virtual void mouseDragged(const MouseEvent& e)
    {
            mgr->mouseMove(e.getLocation().x(), e.getLocation().y());
    }
};

class TutorialUpdateListener : public UpdateListener
{
  public:
    virtual void update(const UpdateEvent& e)
    {

    }
};

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialKeyListener TheKeyListener;
    TutorialWindowEventProducer->addKeyListener(&TheKeyListener);
    TutorialMouseListener TheTutorialMouseListener;
    TutorialMouseMotionListener TheTutorialMouseMotionListener;
    TutorialWindowEventProducer->addMouseListener(&TheTutorialMouseListener);
    TutorialWindowEventProducer->addMouseMotionListener(&TheTutorialMouseMotionListener);
	TutorialUpdateListener TheTutorialUpdateListener;
    TutorialWindowEventProducer->addUpdateListener(&TheTutorialUpdateListener);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
	

	/*	 Shader Material
		Creating the materials used by OpenSG to implement a shader


	*/
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

	PolygonChunkPtr GoochShaderPolyChunk = PolygonChunk::create();
	beginEditCP(GoochShaderPolyChunk);
		GoochShaderPolyChunk->setCullFace(GL_BACK);
		GoochShaderPolyChunk->setBackMode(GL_FILL);
		GoochShaderPolyChunk->setFrontMode(GL_FILL);
	beginEditCP(GoochShaderPolyChunk);

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
		WarmColorParameter->setValue(Vec4f(0.6f,0.6f,0.0f,1.0f));
	endEditCP(WarmColorParameter);
	
	ShaderParameterVec4fPtr CoolColorParameter = ShaderParameterVec4f::create();
	beginEditCP(CoolColorParameter);
		CoolColorParameter->setName("CoolColor");
		CoolColorParameter->setValue(Vec4f(0.0f,0.0f,0.6f,1.0f));
	endEditCP(CoolColorParameter);

	ShaderParameterVec4fPtr SurfaceColorParameter = ShaderParameterVec4f::create();
	beginEditCP(SurfaceColorParameter);
		SurfaceColorParameter->setName("SurfaceColor");
		SurfaceColorParameter->setValue(Vec4f(0.75f,0.75f,0.75f,1.0f));
	endEditCP(SurfaceColorParameter);

	ShaderParameterRealPtr DiffuseWarmParameter = ShaderParameterReal::create();
	beginEditCP(DiffuseWarmParameter);
		DiffuseWarmParameter->setName("DiffuseWarm");
		DiffuseWarmParameter->setValue(0.45);
	endEditCP(DiffuseWarmParameter);

	ShaderParameterRealPtr DiffuseCoolParameter = ShaderParameterReal::create();
	beginEditCP(DiffuseCoolParameter);
		DiffuseCoolParameter->setName("DiffuseCool");
		DiffuseCoolParameter->setValue(0.45);
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

	//Black outline shading materials
	SHLChunkPtr TheBlackSHLChunk = SHLChunk::create();
	beginEditCP(TheBlackSHLChunk);
		TheBlackSHLChunk->setVertexProgram(createSHLVertexProgBlack());
		TheBlackSHLChunk->setFragmentProgram(createSHKFragProgBlack());
	endEditCP(TheBlackSHLChunk);

	// line chunk for setting width of outline
	LineChunkPtr BlackShaderLineChunk = LineChunk::create();
	beginEditCP(BlackShaderLineChunk);
		BlackShaderLineChunk->setWidth(3.5);
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


	// Mulit-Pass material to comine gooch and black outline shading
	MultiPassMaterialPtr ShaderMaterial = MultiPassMaterial::create();
	beginEditCP(ShaderMaterial);
		ShaderMaterial->addMaterial(GoochMaterial);
		ShaderMaterial->addMaterial(BlackFragmentMaterial);
	endEditCP(ShaderMaterial);


	//Torus Node
	GeometryPtr TorusGeometry = makeTorusGeo(5.0f,20.0f, 32,32);
	GeometryPtr SphereGeometry = makeCylinderGeo(10.0f,5.0f,32,true,true,true);

	beginEditCP(SphereGeometry, Geometry::MaterialFieldMask);
		SphereGeometry->setMaterial(ShaderMaterial);
	endEditCP(SphereGeometry, Geometry::MaterialFieldMask);

	beginEditCP(TorusGeometry, Geometry::MaterialFieldMask);
		TorusGeometry->setMaterial(ShaderMaterial);
	endEditCP(TorusGeometry, Geometry::MaterialFieldMask);

	NodePtr TorusNode = Node::create();
    beginEditCP(TorusNode, Node::CoreFieldMask);
        TorusNode->setCore(TorusGeometry);
    endEditCP(TorusNode, Node::CoreFieldMask);

	NodePtr SphereNode = Node::create();
    beginEditCP(SphereNode, Node::CoreFieldMask);
		SphereNode->setCore(SphereGeometry);
    endEditCP(SphereNode, Node::CoreFieldMask);



    // Make Main Scene Node
    NodePtr scene = Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(Group::create());
		scene->addChild(TorusNode);
		scene->addChild(SphereNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

	//FCFileType::FCPtrStore Containers;
	//Containers.insert(scene);

	//FCFileType::FCTypeVector IgnoreTypes;
	////Save the Field Containers to a xml file
	//FCFileHandler::the()->write(Containers,Path("./Data/TestOutput.xml"),IgnoreTypes);

    mgr->setRoot(scene);

    // Show the whole Scene
    mgr->showAll();

    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,WinSize, "06GoochShader");

    //Main Loop
    TutorialWindowEventProducer->mainLoop();

    osgExit();

    return 0;
}


// Callback functions


// Redraw the window
void display(void)
{
    mgr->redraw();
}

// React to size changes
void reshape(Vec2f Size)
{
    mgr->resize(Size.x(), Size.y());
}

std::string createSHLVertexProgGooch(void)
{
	std::ostringstream VertexProgStream;
	VertexProgStream
	<< "uniform vec4 view_position;\n"
	<< "uniform vec3 light_position;\n"

	<< "varying out vec3 ReflectVec;\n"
	<< "varying out vec3 ViewVec;\n"
	<< "varying out float NdotL;\n"

	<< "void main(void)\n"
	<< "{ \n"
	<< "  vec3 ecPos = vec3(gl_ModelViewMatrix * gl_Vertex);\n"
	<< "   vec3 tnorm = normalize(gl_NormalMatrix * gl_Normal);\n"
	<< "  vec3 lightVec = normalize(gl_LightSource[0].position - ecPos);\n"
	<< "   ReflectVec = normalize(reflect(-lightVec, tnorm));\n"
	<< "   ViewVec = normalize(-ecPos);\n"
	<< "   NdotL = dot(lightVec, tnorm) * 0.5 + 0.5;\n"
	<< "   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\n" 
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
	<< "in float NdotL;\n" 
	<< "in vec3 ReflectVec;\n" 
	<< "in vec3 ViewVec;\n" 
	<< "void main(void)\n" 
	<< "{\n" 
	<< "   vec3 kcool = min(CoolColor.xyz + DiffuseCool * SurfaceColor.xyz, 1.0);\n" 
	<< "   vec3 kwarm = min(WarmColor.xyz + DiffuseWarm * SurfaceColor.xyz, 1.0);\n" 
	<< "   vec3 kfinal = mix(kcool,kwarm,NdotL);\n" 
	<< "   vec3 nreflect = normalize(ReflectVec);\n" 
	<< "   vec3 nview = normalize(ViewVec); \n" 
	<< "   float spec = max(dot(nreflect, nview), 0.0);\n" 
 	<< "   spec = pow(spec, 32.0);\n" 
	<< "   gl_FragColor = vec4(min(kfinal + spec, 1.0), 1.0);\n" 
	<< "}\n" ;

	return  FragProgStream.str();
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

