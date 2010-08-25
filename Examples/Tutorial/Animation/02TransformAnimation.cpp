// 
// OpenSGToolbox Tutorial: 02TransformAnimation
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
#include "OSGTransformAnimator.h"
#include "OSGFieldAnimation.h"

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE


// forward declaration so we can have the interesting stuff upfront
FieldAnimationTransitPtr setupAnimation(Transform* const transCore, WindowEventProducer* const win);
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

void animationStarted(AnimationEventDetails* const details)
{
   std::cout << "Animation Started"  << std::endl;
}

void animationStopped(AnimationEventDetails* const details)
{
   std::cout << "Animation Stopped"  << std::endl;
}

void animationPaused(AnimationEventDetails* const details)
{
   std::cout << "Animation Paused"  << std::endl;
}

void animationUnpaused(AnimationEventDetails* const details)
{
   std::cout << "Animation Unpaused"  << std::endl;
}

void animationEnded(AnimationEventDetails* const details)
{
   std::cout << "Animation Ended"  << std::endl;
}

void animationCycled(AnimationEventDetails* const details)
{
   std::cout << "Animation Cycled.  Cycle Count: " << dynamic_cast<Animation*>(details->getSource())->getCycles() << std::endl;
}

void keyPressed(KeyEventDetails* const details, FieldAnimation* const anim, WindowEventProducer* const win)
{
   if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
   {
       win->closeWindow();
   }

   switch(details->getKey())
   {
   case KeyEventDetails::KEY_SPACE:
       anim->pause(!anim->isPaused());
       break;
   case KeyEventDetails::KEY_ENTER:
       anim->attachUpdateProducer(win);
       anim->start();
       break;
   case KeyEventDetails::KEY_1:
       anim->setInterpolationType(Animator::STEP_INTERPOLATION);
       break;
   case KeyEventDetails::KEY_2:
       anim->setInterpolationType(Animator::LINEAR_INTERPOLATION);
       break;
   case KeyEventDetails::KEY_3:
       anim->setInterpolationType(Animator::CUBIC_INTERPOLATION);
       break;
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

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    {

        // Set up Window
        WindowEventProducerRecPtr TutorialWindow = createNativeWindow();

        SimpleSceneManager sceneManager;
        TutorialWindow->setDisplayCallback(boost::bind(display, &sceneManager));
        TutorialWindow->setReshapeCallback(boost::bind(reshape, _1, &sceneManager));

        //Initialize Window
        TutorialWindow->initWindow();

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

        //Attach to events
        TutorialWindow->connectMousePressed(boost::bind(mousePressed, _1, &sceneManager));
        TutorialWindow->connectMouseReleased(boost::bind(mouseReleased, _1, &sceneManager));
        TutorialWindow->connectMouseMoved(boost::bind(mouseMoved, _1, &sceneManager));
        TutorialWindow->connectMouseDragged(boost::bind(mouseDragged, _1, &sceneManager));
    
        //Torus Material
        SimpleMaterialRecPtr TheTorusMaterial = SimpleMaterial::create();
        dynamic_pointer_cast<SimpleMaterial>(TheTorusMaterial)->setAmbient(Color3f(0.2,0.2,0.2));
        dynamic_pointer_cast<SimpleMaterial>(TheTorusMaterial)->setDiffuse(Color3f(0.7,0.7,0.7));
        dynamic_pointer_cast<SimpleMaterial>(TheTorusMaterial)->setSpecular(Color3f(0.7,0.7,0.7));
        dynamic_pointer_cast<SimpleMaterial>(TheTorusMaterial)->setShininess(100.0f);

        //Torus Geometry
        GeometryRecPtr TorusGeometry = makeTorusGeo(.5, 2, 32, 32);
        TorusGeometry->setMaterial(TheTorusMaterial);
        
        NodeRecPtr TorusGeometryNode = Node::create();
        TorusGeometryNode->setCore(TorusGeometry);

        //Make Torus Node
        NodeRecPtr TorusNode = Node::create();
        TransformRecPtr TorusNodeTrans = Transform::create();
        setName(TorusNodeTrans, std::string("TorusNodeTransformationCore"));

        TorusNode->setCore(TorusNodeTrans);
        TorusNode->addChild(TorusGeometryNode);

        //Make Main Scene Node
        NodeRecPtr scene = Node::create();
        ComponentTransformRecPtr Trans = ComponentTransform::create();
        setName(Trans, std::string("MainTransformationCore"));

        scene->setCore(Trans);
        scene->addChild(TorusNode);

        FieldAnimationRecPtr TheAnimation = setupAnimation(TorusNodeTrans, TutorialWindow);

        TutorialWindow->connectKeyPressed(boost::bind(keyPressed, _1, TheAnimation.get(), TutorialWindow.get()));
        
        TheAnimation->connectAnimationStarted(boost::bind(animationStarted, _1));
        TheAnimation->connectAnimationStopped(boost::bind(animationStopped, _1));
        TheAnimation->connectAnimationPaused(boost::bind(animationPaused, _1));
        TheAnimation->connectAnimationUnpaused(boost::bind(animationUnpaused, _1));
        TheAnimation->connectAnimationEnded(boost::bind(animationEnded, _1));
        TheAnimation->connectAnimationCycled(boost::bind(animationCycled, _1));

        commitChanges();

        // tell the manager what to manage
        sceneManager.setRoot  (scene);

        // show the whole scene
        sceneManager.showAll();

        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                WinSize,
                "OpenSG 02TransformAnimation Window");

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

FieldAnimationTransitPtr setupAnimation(Transform* const transCore, WindowEventProducer* const win)
{
    //Number Keyframe Sequence
    KeyframeNumberSequenceReal32RecPtr XTransKeyframes = KeyframeNumberSequenceReal32::create();
    XTransKeyframes->addKeyframe(1.0,0.0f);
    XTransKeyframes->addKeyframe(5.0,2.0f);
    XTransKeyframes->addKeyframe(-5.0,4.0f);
    XTransKeyframes->addKeyframe(1.0,6.0f);
    
    KeyframeNumberSequenceReal32RecPtr YRotKeyframes = KeyframeNumberSequenceReal32::create();
    YRotKeyframes->addKeyframe(0.0,0.0f);
    YRotKeyframes->addKeyframe(45.0,2.0f);
    YRotKeyframes->addKeyframe(0.0,4.0f);

    KeyframeNumberSequenceReal32RecPtr ZScaleKeyframes = KeyframeNumberSequenceReal32::create();
    ZScaleKeyframes->addKeyframe(1.0,0.0f);
    ZScaleKeyframes->addKeyframe(2.0,2.0f);
    ZScaleKeyframes->addKeyframe(3.0,4.0f);
    ZScaleKeyframes->addKeyframe(1.0,6.0f);

    //Animator
    TransformAnimatorRecPtr TheAnimator = TransformAnimator::create();
    TheAnimator->setXTranslationSequence(XTransKeyframes);
    TheAnimator->setXRotationSequence(YRotKeyframes);
    TheAnimator->setYRotationSequence(YRotKeyframes);
    //TheAnimator->setZRotationSequence(YRotKeyframes);
    TheAnimator->setZScaleSequence(ZScaleKeyframes);
    
    //Animation
    FieldAnimationRecPtr TheAnimation = FieldAnimation::create();
    TheAnimation->setAnimator(TheAnimator);
    TheAnimation->setInterpolationType(Animator::LINEAR_INTERPOLATION);
    TheAnimation->setCycling(2);
    TheAnimation->setAnimatedField(transCore, std::string("matrix"));

    TheAnimation->attachUpdateProducer(win);
    TheAnimation->start();

    return FieldAnimationTransitPtr(TheAnimation);
}

