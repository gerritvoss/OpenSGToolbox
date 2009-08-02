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
#include <OpenSG/OSGSHLChunk.h>
#include <OpenSG/OSGSHLParameterChunk.h>
#include <OpenSG/OSGShaderParameterVec4f.h>

// Input
#include <OpenSG/Input/OSGKeyListener.h>
#include <OpenSG/Input/OSGWindowAdapter.h>
#include <OpenSG/Input/OSGWindowUtils.h>

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

ElapsedTimeAnimationAdvancerPtr TheAnimationAdvancer;
AnimationPtr TheAnimation;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);
std::string createSHLVertexProg(void);
std::string createSHLFragProg(void);

void initAnimations(FieldContainerPtr AnimatedObject, std::string AnimatedField);
AnimationPtr createColorAnimation(FieldContainerPtr AnimatedObject, std::string AnimatedField);

// Create a class to allow for the use of the Ctrl+q
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
		ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->update(e.getElapsedTime());

		TheAnimation->update(TheAnimationAdvancer);
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
	

	//Shader Material
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

	//Shader Chunk
	SHLChunkPtr TheSHLChunk = SHLChunk::create();
	beginEditCP(TheSHLChunk);
		TheSHLChunk->setVertexProgram(createSHLVertexProg());
		TheSHLChunk->setFragmentProgram(createSHLFragProg());
	endEditCP(TheSHLChunk);

	//Color Parameter
	ShaderParameterVec4fPtr Color1Parameter = ShaderParameterVec4f::create();
	beginEditCP(Color1Parameter);
		Color1Parameter->setName("Color1");
		Color1Parameter->setValue(Vec4f(0.0f,1.0f,0.0f,1.0f));
	endEditCP(Color1Parameter);
	
	ShaderParameterVec4fPtr Color2Parameter = ShaderParameterVec4f::create();
	beginEditCP(Color2Parameter);
		Color2Parameter->setName("Color2");
		Color2Parameter->setValue(Vec4f(1.0f,1.0f,1.0f,1.0f));
	endEditCP(Color2Parameter);


	//Shader Parameter Chunk
	SHLParameterChunkPtr SHLParameters = SHLParameterChunk::create();
	beginEditCP(SHLParameters);
		SHLParameters->getParameters().push_back(Color1Parameter);
		SHLParameters->getParameters().push_back(Color2Parameter);
		SHLParameters->setSHLChunk(TheSHLChunk);
	endEditCP(SHLParameters);

	ChunkMaterialPtr ShaderMaterial = ChunkMaterial::create();
	beginEditCP(ShaderMaterial, ChunkMaterial::ChunksFieldMask);
		ShaderMaterial->addChunk(ShaderMaterialChunk);
		ShaderMaterial->addChunk(TheSHLChunk);
		ShaderMaterial->addChunk(SHLParameters);
	endEditCP(ShaderMaterial, ChunkMaterial::ChunksFieldMask);

	//Torus Node
	GeometryPtr TorusGeometry = makeTorusGeo(5.0f,20.0f, 32,32);

	beginEditCP(TorusGeometry, Geometry::MaterialFieldMask);
		TorusGeometry->setMaterial(ShaderMaterial);
	endEditCP(TorusGeometry, Geometry::MaterialFieldMask);

	NodePtr TorusNode = Node::create();
    beginEditCP(TorusNode, Node::CoreFieldMask);
        TorusNode->setCore(TorusGeometry);
    endEditCP(TorusNode, Node::CoreFieldMask);


    // Make Main Scene Node
    NodePtr scene = Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(Group::create());
		scene->addChild(TorusNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    mgr->setRoot(scene);

    // Show the whole Scene
    mgr->showAll();


	//Create the Animations
	initAnimations(Color1Parameter, "value");
    TheAnimationAdvancer->start();

    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
                        WinSize,
                                        "04ShaderAnimation");

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

std::string createSHLVertexProg(void)
{
	std::string Result("");

	return Result;
}

std::string createSHLFragProg(void)
{
	std::ostringstream FragCodeStream;

	FragCodeStream
	<< "//Fragment Shader\n"
	<< "uniform vec4 Color1;\n"
	<< "uniform vec4 Color2;\n"

	<< "void main()\n"
	<< "{\n"
	<< "    gl_FragColor = mix(Color1,Color2,1.0-(0.3*gl_Color.r + 0.59*gl_Color.g + 0.11*gl_Color.b));\n"
	<< "}\n";


	return FragCodeStream.str();
}

AnimationPtr createColorAnimation(FieldContainerPtr AnimatedObject, std::string AnimatedField)
{
    //Color Keyframe Sequence
    KeyframeVectorsSequencePtr ColorKeyframes = KeyframeVectorsSequence4f::create();
    ColorKeyframes->addKeyframe(Vec4f(1.0f,0.0f,0.0f,1.0f),0.0f);
    ColorKeyframes->addKeyframe(Vec4f(0.0f,1.0f,0.0f,1.0f),2.0f);
    ColorKeyframes->addKeyframe(Vec4f(0.0f,0.0f,1.0f,1.0f),4.0f);
    ColorKeyframes->addKeyframe(Vec4f(1.0f,0.0f,0.0f,1.0f),6.0f);

    //Animator
    AnimatorPtr Animator = KeyframeAnimator::create();
    beginEditCP(KeyframeAnimatorPtr::dcast(Animator), KeyframeAnimator::KeyframeSequenceFieldMask);
        KeyframeAnimatorPtr::dcast(Animator)->setKeyframeSequence(ColorKeyframes);
    endEditCP(KeyframeAnimatorPtr::dcast(Animator), KeyframeAnimator::KeyframeSequenceFieldMask);
    
    //Animation
    FieldAnimationPtr ColorAnimation = FieldAnimation::create();
    beginEditCP(ColorAnimation);
        FieldAnimationPtr::dcast(ColorAnimation)->setAnimator(Animator);
        FieldAnimationPtr::dcast(ColorAnimation)->setInterpolationType(LINEAR_INTERPOLATION);
        FieldAnimationPtr::dcast(ColorAnimation)->setCycling(-1);
    endEditCP(ColorAnimation);
	ColorAnimation->setAnimatedField(AnimatedObject, AnimatedField);

	return ColorAnimation;
}

void initAnimations(FieldContainerPtr AnimatedObject, std::string AnimatedField)
{
	//Main Animation
	TheAnimation = createColorAnimation(AnimatedObject, AnimatedField);
	
	//Animation Advancer
	TheAnimationAdvancer = ElapsedTimeAnimationAdvancer::create();
	beginEditCP(TheAnimationAdvancer);
		TheAnimationAdvancer->setStartTime( 0.0 );
	beginEditCP(TheAnimationAdvancer);
}
