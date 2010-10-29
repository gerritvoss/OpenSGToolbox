// 
// OpenSGToolbox Tutorial: 08MorphGeometry
//
// Demonstrates a simple animation using transformation keyframes. 
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

#include "OSGContainerUtils.h"
#include "OSGMTRefCountPtr.h"

// Input
#include "OSGWindowUtils.h"
#include "OSGWindowEventProducer.h"
//#include "OSGKeyListener.h"

//Animation
#include "OSGKeyframeSequences.h"
#include "OSGKeyframeAnimator.h"
#include "OSGMorphGeometry.h"
#include "OSGFieldAnimation.h"
#include "OSGAnimationGroup.h"

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE


// forward declaration so we can have the interesting stuff upfront
void setupAnimation(void);
void display(void);
void reshape(Vec2f Size);

//class TutorialAnimationListener : public AnimationListener
//{
//public:
//   virtual void animationStarted(const AnimationEventUnrecPtr e)
//   {
//       std::cout << "Animation Started"  << std::endl;
//   }
//
//   virtual void animationStopped(const AnimationEventUnrecPtr e)
//   {
//       std::cout << "Animation Stopped"  << std::endl;
//   }
//
//   virtual void animationPaused(const AnimationEventUnrecPtr e)
//   {
//       std::cout << "Animation Paused"  << std::endl;
//   }
//
//   virtual void animationUnpaused(const AnimationEventUnrecPtr e)
//   {
//       std::cout << "Animation Unpaused"  << std::endl;
//   }
//
//   virtual void animationEnded(const AnimationEventUnrecPtr e)
//   {
//       std::cout << "Animation Ended"  << std::endl;
//   }
//
//   virtual void animationCycled(const AnimationEventUnrecPtr e)
//   {
//       std::cout << "Animation Cycled.  Cycle Count: " << dynamic_cast<Animation*>(e->getSource())->getCycles() << std::endl;
//   }
//
//};

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerUnrecPtr TutorialWindow;

Time TimeLastIdle;
//TutorialAnimationListener TheAnimationListener;
MorphGeometryRefPtr TheMorphGeometry;
AnimationGroupRefPtr TheAnimationGroup;
// Create a class to allow for the use of the keyboard shortucts 
//class TutorialKeyListener : public KeyListener
//{
//public:
//
//   virtual void keyPressed(const KeyEventUnrecPtr e)
//   {
//       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
//       {
//           TutorialWindow->closeWindow();
//       }
//
//       switch(e->getKey())
//       {
//       case KeyEvent::KEY_SPACE:
//           TheAnimationGroup->pause(!TheAnimationGroup->isPaused());
//           break;
//       case KeyEvent::KEY_ENTER:
//           TheAnimationGroup->attachUpdateProducer(TutorialWindow->editEventProducer());
//           TheAnimationGroup->start();
//           break;
//       }
//   }
//
//   virtual void keyReleased(const KeyEventUnrecPtr e)
//   {
//   }
//
//   virtual void keyTyped(const KeyEventUnrecPtr e)
//   {
//   }
//};
//
//class TutorialMouseListener : public MouseListener
//{
//  public:
//    virtual void mouseClicked(const MouseEventUnrecPtr e)
//    {
//    }
//    virtual void mouseEntered(const MouseEventUnrecPtr e)
//    {
//    }
//    virtual void mouseExited(const MouseEventUnrecPtr e)
//    {
//    }
//    virtual void mousePressed(const MouseEventUnrecPtr e)
//    {
//            mgr->mouseButtonPress(e->getButton(), e->getLocation().x(), e->getLocation().y());
//    }
//    virtual void mouseReleased(const MouseEventUnrecPtr e)
//    {
//           mgr->mouseButtonRelease(e->getButton(), e->getLocation().x(), e->getLocation().y());
//    }
//};
//
//class TutorialMouseMotionListener : public MouseMotionListener
//{
//  public:
//    virtual void mouseMoved(const MouseEventUnrecPtr e)
//    {
//            mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
//    }
//
//    virtual void mouseDragged(const MouseEventUnrecPtr e)
//    {
//            mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
//    }
//};

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    {

    // Set up Window
    TutorialWindow = createNativeWindow();

    TutorialWindow->setDisplayCallback(display);
    TutorialWindow->setReshapeCallback(reshape);

    ////Add Window Listener
    //TutorialKeyListener TheKeyListener;
    //TutorialWindow->addKeyListener(&TheKeyListener);
    //TutorialMouseListener TheTutorialMouseListener;
    //TutorialMouseMotionListener TheTutorialMouseMotionListener;
    //TutorialWindow->addMouseListener(&TheTutorialMouseListener);
    //TutorialWindow->addMouseMotionListener(&TheTutorialMouseMotionListener);

    //Initialize Window
    TutorialWindow->initWindow();

    //Torus Geometry
    GeometryRefPtr BaseTorusGeometry = makeTorusGeo(.5, 2, 32, 32);
    GeometryRefPtr Target0TorusGeometry = makeTorusGeo(1.5, 2, 32, 32);
    GeometryRefPtr Target1TorusGeometry = makeTorusGeo(0.3, 1.5, 32, 32);
    GeometryRefPtr Target2TorusGeometry = makeTorusGeo(.2, 3, 32, 32);

    TheMorphGeometry = MorphGeometry::create();
    TheMorphGeometry->setBaseGeometry(BaseTorusGeometry);
    TheMorphGeometry->addMorphTarget(Target0TorusGeometry, 0.0f);
    TheMorphGeometry->addMorphTarget(Target1TorusGeometry, 0.0f);
    TheMorphGeometry->addMorphTarget(Target2TorusGeometry, 0.0f);
    
    NodeRefPtr TorusGeometryNode = Node::create();
    TorusGeometryNode->setCore(TheMorphGeometry);

    //Make Torus Node
    NodeRefPtr TorusNode = Node::create();
    TransformRecPtr TorusNodeTrans = Transform::create();
    setName(TorusNodeTrans, std::string("TorusNodeTransformationCore"));

    TorusNode->setCore(TorusNodeTrans);
    TorusNode->addChild(TorusGeometryNode);

    //Make Main Scene Node
    NodeRefPtr scene = Node::create();
    TransformRefPtr Trans = ComponentTransform::create();
    setName(Trans, std::string("MainTransformationCore"));

    scene->setCore(Trans);
    scene->addChild(TorusNode);

    setupAnimation();

    commitChanges();

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindow);

    // tell the manager what to manage
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();

    
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
            WinSize,
            "OpenSG 08MorphGeometry Window");

    //Enter main Loop
    TutorialWindow->mainLoop();

    }

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
    //Number Keyframe Sequence
    KeyframeVectorSequenceVec1fUnrecPtr Target0WeightSeq = KeyframeVectorSequenceVec1f::create();
    Target0WeightSeq->addRawKeyframe(Vec1f(0.0),0.0f);
    Target0WeightSeq->addRawKeyframe(Vec1f(1.0),2.0f);
    Target0WeightSeq->addRawKeyframe(Vec1f(0.0),4.0f);
    Target0WeightSeq->addRawKeyframe(Vec1f(0.0),12.0f);

    KeyframeVectorSequenceVec1fUnrecPtr Target1WeightSeq = KeyframeVectorSequenceVec1f::create();
    Target1WeightSeq->addRawKeyframe(Vec1f(0.0),0.0f);
    Target1WeightSeq->addRawKeyframe(Vec1f(0.0),4.0f);
    Target1WeightSeq->addRawKeyframe(Vec1f(1.0),6.0f);
    Target1WeightSeq->addRawKeyframe(Vec1f(0.0),8.0f);
    Target1WeightSeq->addRawKeyframe(Vec1f(0.0),12.0f);

    KeyframeVectorSequenceVec1fUnrecPtr Target2WeightSeq = KeyframeVectorSequenceVec1f::create();
    Target2WeightSeq->addRawKeyframe(Vec1f(0.0),0.0f);
    Target2WeightSeq->addRawKeyframe(Vec1f(0.0),8.0f);
    Target2WeightSeq->addRawKeyframe(Vec1f(1.0),10.0f);
    Target2WeightSeq->addRawKeyframe(Vec1f(0.0),12.0f);

    //Animator
    KeyframeAnimatorUnrecPtr TheAnimator0 = KeyframeAnimator::create();
    TheAnimator0->setKeyframeSequence(Target0WeightSeq);
    
    KeyframeAnimatorUnrecPtr TheAnimator1 = KeyframeAnimator::create();
    TheAnimator1->setKeyframeSequence(Target1WeightSeq);
    
    KeyframeAnimatorUnrecPtr TheAnimator2 = KeyframeAnimator::create();
    TheAnimator2->setKeyframeSequence(Target2WeightSeq);
    
    //Animation
    FieldAnimationUnrecPtr TheAnimation0 = FieldAnimation::create();
    TheAnimation0->setAnimator(TheAnimator0);
    TheAnimation0->setInterpolationType(Animator::LINEAR_INTERPOLATION);
    TheAnimation0->setCycling(-1);
    TheAnimation0->setAnimatedMultiField(TheMorphGeometry->getWeights(), std::string("values"), 0);

    FieldAnimationUnrecPtr TheAnimation1 = FieldAnimation::create();
    TheAnimation1->setAnimator(TheAnimator1);
    TheAnimation1->setInterpolationType(Animator::LINEAR_INTERPOLATION);
    TheAnimation1->setCycling(-1);
    TheAnimation1->setAnimatedMultiField(TheMorphGeometry->getWeights(), std::string("values"), 1);

    FieldAnimationUnrecPtr TheAnimation2 = FieldAnimation::create();
    TheAnimation2->setAnimator(TheAnimator2);
    TheAnimation2->setInterpolationType(Animator::LINEAR_INTERPOLATION);
    TheAnimation2->setCycling(-1);
    TheAnimation2->setAnimatedMultiField(TheMorphGeometry->getWeights(), std::string("values"), 2);

    TheAnimationGroup = AnimationGroup::create();
    TheAnimationGroup->pushToAnimations(TheAnimation0);
    TheAnimationGroup->pushToAnimations(TheAnimation1);
    TheAnimationGroup->pushToAnimations(TheAnimation2);

    TheAnimationGroup->attachUpdateProducer(TutorialWindow);
    TheAnimationGroup->start();
}

