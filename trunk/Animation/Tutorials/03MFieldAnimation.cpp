// 
// OpenSGToolbox Tutorial: 03FieldAnimation 
//
// Demonstrates the use of a field animation.
//

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>

#include <OpenSG/OSGSimpleMaterial.h>

#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGTypeFactory.h>
#include <OpenSG/OSGFieldFactory.h>

#include <OpenSG/OSGFieldContainerFactory.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include <OpenSG/OSGGradientBackground.h>

#include <OpenSG/Toolbox/OSGFieldContainerUtils.h>

// Input
#include <OpenSG/Input/OSGKeyListener.h>
#include <OpenSG/Input/OSGWindowUtils.h>

//Animation
#include <OpenSG/Animation/OSGKeyframeSequences.h>
#include <OpenSG/Animation/OSGKeyframeAnimator.h>
#include <OpenSG/Animation/OSGFieldAnimation.h>
#include <OpenSG/Animation/OSGElapsedTimeAnimationAdvancer.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE


// forward declaration so we can have the interesting stuff upfront
void setupAnimation(void);
void display(void);
void reshape(Vec2f Size);

class TutorialAnimationListener : public AnimationListener
{
public:
   virtual void animationStarted(const AnimationEvent& e)
   {
   }

   virtual void animationStopped(const AnimationEvent& e)
   {
   }

   virtual void animationPaused(const AnimationEvent& e)
   {
   }

   virtual void animationUnpaused(const AnimationEvent& e)
   {
   }

   virtual void animationEnded(const AnimationEvent& e)
   {
   }

   virtual void animationCycled(const AnimationEvent& e)
   {
       std::cout << "Animation Cycled.  Cycle Count: " << e.getAnimation()->getCycles() << std::endl;
   }

};

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;

Time TimeLastIdle;
FieldAnimationPtr TheAnimation;
TutorialAnimationListener TheAnimationListener;
AnimationAdvancerPtr TheAnimationAdvancer;

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
		ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->update(e.getElapsedTime());

		TheAnimation->update(TheAnimationAdvancer);
    }
};

// Initialize GLUT & OpenSG and set up the scene
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
	
    //Torus Node
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 32, 32);

    //Make Torus Node
    NodePtr TorusNode = Node::create();
    TransformPtr TorusNodeTrans;
    TorusNodeTrans = Transform::create();

    beginEditCP(TorusNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        TorusNode->setCore(TorusNodeTrans);
        TorusNode->addChild(TorusGeometryNode);
    endEditCP  (TorusNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

    //Make Main Scene Node
    NodePtr scene = Node::create();
    ComponentTransformPtr Trans;
    Trans = ComponentTransform::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        scene->setCore(Trans);
 
        // add the torus as a child
        scene->addChild(TorusNode);
    }
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    //Make a gradient Background
    GradientBackgroundPtr TutorialBackground = GradientBackground::create();
    beginEditCP(TutorialBackground, GradientBackground::ColorFieldMask | GradientBackground::PositionFieldMask);
        TutorialBackground->addLine(Color3f(1.0,0.0,0.0),0.0);
        TutorialBackground->addLine(Color3f(0.0,1.0,0.0),0.5);
        TutorialBackground->addLine(Color3f(0.0,0.0,1.0),1.0);
    endEditCP(TutorialBackground, GradientBackground::ColorFieldMask | GradientBackground::PositionFieldMask);
    setName(TutorialBackground, std::string("TutorialGradientBackground"));

    setupAnimation();

    // tell the manager what to manage
    mgr->setRoot  (scene);
    mgr->getWindow()->getPort(0)->setBackground(TutorialBackground);

    // show the whole scene
    mgr->showAll();

    TheAnimationAdvancer->start();
    
    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
                        WinSize,
                                        "03MFieldAnimation");

    //Main Loop
    TutorialWindowEventProducer->mainLoop();

    osgExit();

    return 0;
}

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

void setupAnimation(void)
{
    //Color Keyframe Sequence
    KeyframeColorsSequencePtr ColorKeyframes = KeyframeColorsSequence3f::create();
    ColorKeyframes->addKeyframe(Color4f(1.0f,0.0f,0.0f,1.0f),0.0f);
    ColorKeyframes->addKeyframe(Color4f(0.0f,1.0f,0.0f,1.0f),2.0f);
    ColorKeyframes->addKeyframe(Color4f(0.0f,0.0f,1.0f,1.0f),4.0f);
    ColorKeyframes->addKeyframe(Color4f(1.0f,0.0f,0.0f,1.0f),6.0f);

    //Animator
    KeyframeAnimatorPtr TheAnimator = KeyframeAnimator::create();
    beginEditCP(TheAnimator, KeyframeAnimator::KeyframeSequenceFieldMask);
        TheAnimator->setKeyframeSequence(ColorKeyframes);
    endEditCP(TheAnimator, KeyframeAnimator::KeyframeSequenceFieldMask);
    
    //Animation
    TheAnimation = FieldAnimation::create();
    beginEditCP(TheAnimation);
        TheAnimation->setAnimator(TheAnimator);
        TheAnimation->setInterpolationType(LINEAR_INTERPOLATION);
        TheAnimation->setCycling(-1);
    endEditCP(TheAnimation);
	TheAnimation->setAnimatedMultiField(getFieldContainer("GradientBackground",std::string("TutorialGradientBackground")), std::string("color"), 1);

    //Animation Listener
    TheAnimation->addAnimationListener(&TheAnimationListener);

    //Animation Advancer
    TheAnimationAdvancer = ElapsedTimeAnimationAdvancer::create();
    beginEditCP(TheAnimationAdvancer);
    ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->setStartTime( 0.0 );
    beginEditCP(TheAnimationAdvancer);
}
