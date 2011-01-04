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
#include "OSGSimpleSHLVariableChunk.h"
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

// Forward declaration so we can have the interesting stuff upfront
std::string createSHLVertexProg(void);
std::string createSHLFragProg(void);

AnimationTransitPtr setupAnimation(FieldContainer* const AnimatedObject,
                                   const std::string& AnimatedField);

void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

void animationCycled(AnimationEventDetails* const details)
{
    std::cout << "Animation Cycled.  Cycle Count: " << dynamic_cast<Animation*>(details->getSource())->getCycles() << std::endl;
}

// The SimpleSceneManager to manage simple applications
void keyPressed(KeyEventDetails* const details, WindowEventProducer* const TutorialWindow)
{
    if(details->getKey() == KeyEventDetails::KEY_Q &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        TutorialWindow->closeWindow();
    }
}

void mousePressed(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    mgr->mouseButtonPress(details->getButton(), details->getLocation().x(), details->getLocation().y());
}

void mouseReleased(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    mgr->mouseButtonRelease(details->getButton(), details->getLocation().x(), details->getLocation().y());
}

void mouseMoved(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    mgr->mouseMove(details->getLocation().x(), details->getLocation().y());
}

void mouseDragged(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    mgr->mouseMove(details->getLocation().x(), details->getLocation().y());
}

void mouseWheelMoved(MouseWheelEventDetails* const details, SimpleSceneManager *mgr)
{
    if(details->getUnitsToScroll() > 0)
    {
        for(UInt32 i(0) ; i<details->getUnitsToScroll() ;++i)
        {
            mgr->mouseButtonPress(Navigator::DOWN_MOUSE,details->getLocation().x(),details->getLocation().y());
            mgr->mouseButtonRelease(Navigator::DOWN_MOUSE,details->getLocation().x(),details->getLocation().y());
        }
    }
    else if(details->getUnitsToScroll() < 0)
    {
        for(UInt32 i(0) ; i<abs(details->getUnitsToScroll()) ;++i)
        {
            mgr->mouseButtonPress(Navigator::UP_MOUSE,details->getLocation().x(),details->getLocation().y());
            mgr->mouseButtonRelease(Navigator::UP_MOUSE,details->getLocation().x(),details->getLocation().y());
        }
    }
}

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);
    {
        // Set up Window
        WindowEventProducerRecPtr TutorialWindow = createNativeWindow();

        //Initialize Window
        TutorialWindow->initWindow();

        SimpleSceneManager sceneManager;
        TutorialWindow->setDisplayCallback(boost::bind(display, &sceneManager));
        TutorialWindow->setReshapeCallback(boost::bind(reshape, _1, &sceneManager));

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

        //Attach to events
        TutorialWindow->connectMousePressed(boost::bind(mousePressed, _1, &sceneManager));
        TutorialWindow->connectMouseReleased(boost::bind(mouseReleased, _1, &sceneManager));
        TutorialWindow->connectMouseMoved(boost::bind(mouseMoved, _1, &sceneManager));
        TutorialWindow->connectMouseDragged(boost::bind(mouseDragged, _1, &sceneManager));
        TutorialWindow->connectMouseWheelMoved(boost::bind(mouseWheelMoved, _1, &sceneManager));
        TutorialWindow->connectKeyPressed(boost::bind(keyPressed, _1, TutorialWindow.get()));

        //Shader Chunk
        SimpleSHLChunkUnrecPtr TheSHLChunk = SimpleSHLChunk::create();
        //TheSHLChunk->setVertexProgram(createSHLVertexProg());
        TheSHLChunk->setFragmentProgram(createSHLFragProg());
        TheSHLChunk->addUniformVariable("Color1",Vec4f(0.0f,1.0f,0.0f,1.0f));
        TheSHLChunk->addUniformVariable("Color2",Vec4f(1.0f,1.0f,1.0f,1.0f));

        //Shader Parameter Chunk
        //SimpleSHLVariableChunkUnrecPtr SHLParameters = SimpleSHLVariableChunk::create();
        ////Color Parameter
        //SHLParameters->addUniformVariable("Color1",Vec4f(0.0f,1.0f,0.0f,1.0f));
        //SHLParameters->addUniformVariable("Color2",Vec4f(1.0f,1.0f,1.0f,1.0f));

        ShaderVariableVec4fUnrecPtr Color1Parameter;
        ShaderVariableVec4fUnrecPtr Color2Parameter;

        Color1Parameter = dynamic_cast<ShaderVariableVec4f*>(const_cast<ShaderVariable*>(TheSHLChunk->getVariables()->getVariable("Color1")));
        Color2Parameter = dynamic_cast<ShaderVariableVec4f*>(const_cast<ShaderVariable*>(TheSHLChunk->getVariables()->getVariable("Color2")));
        //Color1Parameter = dynamic_cast<ShaderVariableVec4f*>(const_cast<ShaderVariable*>(SHLParameters->getVariables()->getVariable("Color1")));
        //Color2Parameter = dynamic_cast<ShaderVariableVec4f*>(const_cast<ShaderVariable*>(SHLParameters->getVariables()->getVariable("Color2")));

        ChunkMaterialUnrecPtr ShaderMaterial = ChunkMaterial::create();
        ShaderMaterial->addChunk(TheSHLChunk);
        //ShaderMaterial->addChunk(SHLParameters);

        //Torus Node
        GeometryUnrecPtr TorusGeometry = makeTorusGeo(5.0f,20.0f, 32,32);

        TorusGeometry->setMaterial(ShaderMaterial);

        NodeUnrecPtr TorusNode = Node::create();
        TorusNode->setCore(TorusGeometry);

        // Make Main Scene Node
        NodeUnrecPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(TorusNode);

        sceneManager.setRoot(scene);

        // Show the whole Scene
        sceneManager.showAll();

        //Create the Animations
        AnimationUnrecPtr TheAnimation = setupAnimation(Color1Parameter, "value");
        TheAnimation->attachUpdateProducer(TutorialWindow);
        TheAnimation->start();

        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "04ShaderAnimation");

        //Main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}


// Callback functions


// Redraw the window
void display(SimpleSceneManager *mgr)
{
    mgr->redraw();
}

// React to size changes
void reshape(Vec2f Size, SimpleSceneManager *mgr)
{
    mgr->resize(Size.x(), Size.y());
}

std::string createSHLVertexProg(void)
{
    std::ostringstream FragCodeStream;

    FragCodeStream
        << "//Vertex Shader\n"

        << "void main(void)\n"
        << "{\n"
        << "    gl_Position = ftransform();\n"
        << "}\n";


    return FragCodeStream.str();
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

AnimationTransitPtr setupAnimation(FieldContainer* const AnimatedObject,
                                   const std::string& AnimatedField)
{
    //Color Keyframe Sequence
    KeyframeVectorSequenceVec4fUnrecPtr ColorKeyframes = KeyframeVectorSequenceVec4f::create();
    ColorKeyframes->addRawKeyframe(Vec4f(1.0f,0.0f,0.0f,1.0f),0.0f);
    ColorKeyframes->addRawKeyframe(Vec4f(0.0f,1.0f,0.0f,1.0f),2.0f);
    ColorKeyframes->addRawKeyframe(Vec4f(0.0f,0.0f,1.0f,1.0f),4.0f);
    ColorKeyframes->addRawKeyframe(Vec4f(1.0f,0.0f,0.0f,1.0f),6.0f);

    //Animator
    KeyframeAnimatorUnrecPtr Animator = KeyframeAnimator::create();
    Animator->setKeyframeSequence(ColorKeyframes);

    //Animation
    FieldAnimationUnrecPtr ColorAnimation = FieldAnimation::create();
    ColorAnimation->setAnimator(Animator);
    ColorAnimation->setInterpolationType(Animator::LINEAR_INTERPOLATION);
    ColorAnimation->setCycling(-1);
    ColorAnimation->setAnimatedField(AnimatedObject, AnimatedField);

    return AnimationTransitPtr(ColorAnimation);
}

