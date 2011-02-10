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
// The SimpleSceneManager to manage simple applications
AnimationTransitPtr setupAnimation(MorphGeometry* const TheMorphGeometry);
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

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
        }
    }
    else if(details->getUnitsToScroll() < 0)
    {
        for(UInt32 i(0) ; i<abs(details->getUnitsToScroll()) ;++i)
        {
            mgr->mouseButtonPress(Navigator::UP_MOUSE,details->getLocation().x(),details->getLocation().y());
        }
    }
}

// Initialize GLUT & OpenSG and set up the scene
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
        TutorialWindow->connectMouseDragged(boost::bind(mouseDragged, _1, &sceneManager));
        TutorialWindow->connectMouseWheelMoved(boost::bind(mouseWheelMoved, _1, &sceneManager));
        TutorialWindow->connectKeyPressed(boost::bind(keyPressed, _1, TutorialWindow.get()));

        //Torus Geometry
        GeometryRefPtr BaseTorusGeometry = makeTorusGeo(.5, 2, 32, 32);
        GeometryRefPtr Target0TorusGeometry = makeTorusGeo(1.5, 2, 32, 32);
        GeometryRefPtr Target1TorusGeometry = makeTorusGeo(0.3, 1.5, 32, 32);
        GeometryRefPtr Target2TorusGeometry = makeTorusGeo(.2, 3, 32, 32);

        MorphGeometryUnrecPtr TheMorphGeometry = MorphGeometry::create();
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

        AnimationUnrecPtr TheAnimation = setupAnimation(TheMorphGeometry);
        TheAnimation->attachUpdateProducer(TutorialWindow);
        TheAnimation->start();

        commitChanges();

        // tell the manager what to manage
        sceneManager.setRoot  (scene);

        // show the whole scene
        sceneManager.showAll();


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
void display(SimpleSceneManager *mgr)
{
    mgr->redraw();
}

// React to size changes
void reshape(Vec2f Size, SimpleSceneManager *mgr)
{
    mgr->resize(Size.x(), Size.y());
}

AnimationTransitPtr setupAnimation(MorphGeometry* const TheMorphGeometry)
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

    AnimationGroupUnrecPtr TheAnimationGroup = AnimationGroup::create();
    TheAnimationGroup->pushToAnimations(TheAnimation0);
    TheAnimationGroup->pushToAnimations(TheAnimation1);
    TheAnimationGroup->pushToAnimations(TheAnimation2);

    return AnimationTransitPtr(TheAnimationGroup);
}

