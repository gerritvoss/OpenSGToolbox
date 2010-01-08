// 
// OpenSGToolbox Tutorial: 04ShaderAnimation 
//
// Demonstrates a simple animation. 
//

// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"
#include "OSGSimpleGeometry.h"
#include "OSGLineChunk.h"
#include "OSGBlendChunk.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGSimpleSHLChunk.h"
#include "OSGSHLParameterChunk.h"
#include "OSGShaderVariableVec4f.h"

// Input
#include "OSGKeyListener.h"
#include "OSGWindowAdapter.h"
#include "OSGWindowUtils.h"

#include <sstream>

//Animation
#include "OSGKeyframeSequences.h"
#include "OSGKeyframeAnimator.h"
#include "OSGFieldAnimation.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerUnrecPtr TutorialWindow;

AnimationUnrecPtr TheAnimation;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);
std::string createSHLVertexProg(void);
std::string createSHLFragProg(void);

void initAnimations(FieldContainerUnrecPtr AnimatedObject, std::string AnimatedField);
AnimationUnrecPtr createColorAnimation(FieldContainerUnrecPtr AnimatedObject, std::string AnimatedField);

// Create a class to allow for the use of the keyboard shortcuts 
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventUnrecPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           TutorialWindow->closeWindow();
       }
   }

   virtual void keyReleased(const KeyEventUnrecPtr e)
   {
   }

   virtual void keyTyped(const KeyEventUnrecPtr e)
   {
   }
};

class TutorialMouseListener : public MouseListener
{
public:
    virtual void mouseClicked(const MouseEventUnrecPtr e)
    {
    }
    virtual void mouseEntered(const MouseEventUnrecPtr e)
    {
    }
    virtual void mouseExited(const MouseEventUnrecPtr e)
    {
    }
    virtual void mousePressed(const MouseEventUnrecPtr e)
    {
        mgr->mouseButtonPress(e->getButton(), e->getLocation().x(), e->getLocation().y());
    }
    virtual void mouseReleased(const MouseEventUnrecPtr e)
    {
        mgr->mouseButtonRelease(e->getButton(), e->getLocation().x(), e->getLocation().y());
    }
};

class TutorialMouseMotionListener : public MouseMotionListener
{
public:
    virtual void mouseMoved(const MouseEventUnrecPtr e)
    {
        mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
    }

    virtual void mouseDragged(const MouseEventUnrecPtr e)
    {
        mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
    }
};

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindow = createNativeWindow();
    TutorialWindow->initWindow();

    TutorialWindow->setDisplayCallback(display);
    TutorialWindow->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialKeyListener TheKeyListener;
    TutorialWindow->addKeyListener(&TheKeyListener);
    TutorialMouseListener TheTutorialMouseListener;
    TutorialMouseMotionListener TheTutorialMouseMotionListener;
    TutorialWindow->addMouseListener(&TheTutorialMouseListener);
    TutorialWindow->addMouseMotionListener(&TheTutorialMouseMotionListener);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindow);
	

	//Shader Material
	BlendChunkUnrecPtr ExampleBlendChunk = BlendChunk::create();
    ExampleBlendChunk->setSrcFactor(GL_SRC_ALPHA);
    ExampleBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

	//Material Chunk
	MaterialChunkUnrecPtr ShaderMaterialChunk = MaterialChunk::create();
    ShaderMaterialChunk->setAmbient(Color4f(0.4f,0.4f,0.4f,1.0f));
    ShaderMaterialChunk->setDiffuse(Color4f(0.7f,0.7f,0.7f,1.0f));
    ShaderMaterialChunk->setSpecular(Color4f(1.0f,1.0f,1.0f,1.0f));

	//Shader Chunk
	SimpleSHLChunkUnrecPtr TheSHLChunk = SimpleSHLChunk::create();
    TheSHLChunk->setVertexProgram(createSHLVertexProg());
    TheSHLChunk->setFragmentProgram(createSHLFragProg());

	//Color Parameter
	ShaderVariableVec4fUnrecPtr Color1Parameter = ShaderVariableVec4f::create();
    Color1Parameter->setName("Color1");
    Color1Parameter->setValue(Vec4f(0.0f,1.0f,0.0f,1.0f));
	
	ShaderVariableVec4fUnrecPtr Color2Parameter = ShaderVariableVec4f::create();
    Color2Parameter->setName("Color2");
    Color2Parameter->setValue(Vec4f(1.0f,1.0f,1.0f,1.0f));


	//Shader Parameter Chunk
	SHLParameterChunkUnrecPtr SHLParameters = SHLParameterChunk::create();
    SHLParameters->getParameters().push_back(Color1Parameter);
    SHLParameters->getParameters().push_back(Color2Parameter);
    SHLParameters->setSHLChunk(TheSHLChunk);

	ChunkMaterialUnrecPtr ShaderMaterial = ChunkMaterial::create();
    ShaderMaterial->addChunk(ShaderMaterialChunk);
    ShaderMaterial->addChunk(TheSHLChunk);
    ShaderMaterial->addChunk(SHLParameters);

	//Torus Node
	GeometryUnrecPtr TorusGeometry = makeTorusGeo(5.0f,20.0f, 32,32);

    TorusGeometry->setMaterial(ShaderMaterial);

	NodeUnrecPtr TorusNode = Node::create();
    TorusNode->setCore(TorusGeometry);


    // Make Main Scene Node
    NodeUnrecPtr scene = Node::create();
    scene->setCore(Group::create());
    scene->addChild(TorusNode);

    mgr->setRoot(scene);

    // Show the whole Scene
    mgr->showAll();

	//Create the Animations
	initAnimations(Color1Parameter, "value");

    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
                               WinSize,
                               "04ShaderAnimation");

    //Main Loop
    TutorialWindow->mainLoop();

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

AnimationUnrecPtr createColorAnimation(FieldContainerUnrecPtr AnimatedObject, std::string AnimatedField)
{
    //Color Keyframe Sequence
    KeyframeVectorSequenceUnrecPtr ColorKeyframes = KeyframeVectorSequenceVec4f::create();
    ColorKeyframes->addKeyframe(Vec4f(1.0f,0.0f,0.0f,1.0f),0.0f);
    ColorKeyframes->addKeyframe(Vec4f(0.0f,1.0f,0.0f,1.0f),2.0f);
    ColorKeyframes->addKeyframe(Vec4f(0.0f,0.0f,1.0f,1.0f),4.0f);
    ColorKeyframes->addKeyframe(Vec4f(1.0f,0.0f,0.0f,1.0f),6.0f);

    //Animator
    AnimatorUnrecPtr Animator = KeyframeAnimator::create();
    dynamic_pointer_cast<KeyframeAnimator>(Animator)->setKeyframeSequence(ColorKeyframes);
    
    //Animation
    FieldAnimationUnrecPtr ColorAnimation = FieldAnimation::create();
    dynamic_pointer_cast<FieldAnimation>(ColorAnimation)->setInterpolationType(Animator::LINEAR_INTERPOLATION);
    dynamic_pointer_cast<FieldAnimation>(ColorAnimation)->setCycling(-1);
	ColorAnimation->setAnimatedField(AnimatedObject, AnimatedField);

	return ColorAnimation;
}

void initAnimations(FieldContainerUnrecPtr AnimatedObject, std::string AnimatedField)
{
	//Main Animation
	TheAnimation = createColorAnimation(AnimatedObject, AnimatedField);

    TheAnimation->attachUpdateProducer(TutorialWindow->editEventProducer());
    TheAnimation->start();
}
