// 
// OpenSGToolbox Tutorial: 03FieldAnimation 
//
// Demonstrates the use of a field animation.
//

// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// Methods to create simple geometry: boxes, spheres, tori etc.
#include "OSGSimpleGeometry.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"

#include "OSGSimpleMaterial.h"

#include "OSGComponentTransform.h"
#include "OSGTransform.h"
#include "OSGTypeFactory.h"


#include "OSGFieldContainerFactory.h"
#include "OSGNameAttachment.h"
#include "OSGGradientBackground.h"

#include "OSGFieldContainerUtils.h"

// Input
#include "OSGKeyListener.h"
#include "OSGWindowUtils.h"

//Animation
#include "OSGKeyframeSequences.h"
#include "OSGKeyframeAnimator.h"
#include "OSGFieldAnimation.h"

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
   virtual void animationStarted(const AnimationEventUnrecPtr e)
   {
   }

   virtual void animationStopped(const AnimationEventUnrecPtr e)
   {
   }

   virtual void animationPaused(const AnimationEventUnrecPtr e)
   {
   }

   virtual void animationUnpaused(const AnimationEventUnrecPtr e)
   {
   }

   virtual void animationEnded(const AnimationEventUnrecPtr e)
   {
   }

   virtual void animationCycled(const AnimationEventUnrecPtr e)
   {
       std::cout << "Animation Cycled.  Cycle Count: " << dynamic_cast<Animation*>(e->getSource())->getCycles() << std::endl;
   }

};

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerUnrecPtr TutorialWindow;
GradientBackgroundUnrecPtr TutorialBackground;

Time TimeLastIdle;
FieldAnimationUnrecPtr TheAnimation;
TutorialAnimationListener TheAnimationListener;

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

// Initialize GLUT & OpenSG and set up the scene
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
	
    //Torus Node
    NodeUnrecPtr TorusGeometryNode = makeTorus(.5, 2, 32, 32);

    //Make Torus Node
    NodeUnrecPtr TorusNode = Node::create();
    TransformUnrecPtr TorusNodeTrans;
    TorusNodeTrans = Transform::create();

    TorusNode->setCore(TorusNodeTrans);
    TorusNode->addChild(TorusGeometryNode);

    //Make Main Scene Node
    NodeUnrecPtr scene = Node::create();
    ComponentTransformUnrecPtr Trans;
    Trans = ComponentTransform::create();
    scene->setCore(Trans);

    // add the torus as a child
    scene->addChild(TorusNode);

    //Make a gradient Background
    TutorialBackground = GradientBackground::create();
    TutorialBackground->addLine(Color3f(1.0,0.0,0.0),0.0);
    TutorialBackground->addLine(Color3f(0.0,1.0,0.0),0.5);
    TutorialBackground->addLine(Color3f(0.0,0.0,1.0),1.0);
    setName(TutorialBackground, std::string("TutorialGradientBackground"));

    setupAnimation();

    // tell the manager what to manage
    mgr->setRoot  (scene);
    mgr->getWindow()->getPort(0)->setBackground(TutorialBackground);

    // show the whole scene
    mgr->showAll();

    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
                               WinSize,
                               "03MFieldAnimation");

    //Main Loop
    TutorialWindow->mainLoop();

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
    KeyframeColorSequenceUnrecPtr ColorKeyframes = KeyframeColorSequenceColor3f::create();
    ColorKeyframes->addKeyframe(Color4f(1.0f,0.0f,0.0f,1.0f),0.0f);
    ColorKeyframes->addKeyframe(Color4f(0.0f,1.0f,0.0f,1.0f),2.0f);
    ColorKeyframes->addKeyframe(Color4f(0.0f,0.0f,1.0f,1.0f),4.0f);
    ColorKeyframes->addKeyframe(Color4f(1.0f,0.0f,0.0f,1.0f),6.0f);

    //Animator
    KeyframeAnimatorUnrecPtr TheAnimator = KeyframeAnimator::create();
    TheAnimator->setKeyframeSequence(ColorKeyframes);
    
    //Animation
    TheAnimation = FieldAnimation::create();
    TheAnimation->setAnimator(TheAnimator);
    TheAnimation->setInterpolationType(Animator::LINEAR_INTERPOLATION);
    TheAnimation->setCycling(-1);
	TheAnimation->setAnimatedMultiField(TutorialBackground, std::string("color"), 1);

    //Animation Listener
    TheAnimation->addAnimationListener(&TheAnimationListener);

    TheAnimation->attachUpdateProducer(TutorialWindow->editEventProducer());
    TheAnimation->start();
}
