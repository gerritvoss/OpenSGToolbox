// 
// OpenSGToolbox Tutorial: 01Animation
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
#include "OSGFieldAnimation.h"
#include "OSGAnimationGroup.h"

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE


ThreadRefPtr       RenderThread;
ThreadRefPtr       ApplicationThread;
BarrierRefPtr      SyncBarrier;
WindowEventProducerMTRecPtr TutorialWindow;

// forward declaration so we can have the interesting stuff upfront
AnimationTransitPtr setupAnimation(Transform* const transCore, WindowEventProducer* const win);
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

void keyPressed(KeyEventDetails* const details, Animation* const anim, WindowEventProducer* const win)
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
            //anim->setInterpolationType(Animator::STEP_INTERPOLATION);
       break;
   case KeyEventDetails::KEY_2:
            //anim->setInterpolationType(Animator::LINEAR_INTERPOLATION);
       break;
   case KeyEventDetails::KEY_3:
            //anim->setInterpolationType(Animator::CUBIC_INTERPOLATION);
       break;
	//case '1':
			//TheAnimator->setKeyframeSequence(ColorKeyframes);
		
		//TheAnimation->setAnimatedField(TheTorusMaterial, std::string("diffuse"));
		
		//break;
	//case '2':
			//TheAnimator->setKeyframeSequence(TransformationKeyframes);

		//TheAnimation->setAnimatedField(getFieldContainer("Transform",std::string("TorusNodeTransformationCore")), std::string("matrix"));
        //break;
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

void draw(void *args)
{
    SimpleSceneManager *mgr(reinterpret_cast<SimpleSceneManager *>(args));

    //Render
    while(true)
    {
        //Sync data
        ApplicationThread->getChangeList()->applyAndClear();

        //Draw
        mgr->redraw();
    }
}

// Initialize OpenSG and set up the scene
int main(int argc, char **argv)
{
    //Set the number of aspects
    ThreadManager::setNumAspects(2);
    ChangeList::setReadWriteDefault(true);

    // OSG init
    osgInit(argc,argv);

    {
        // Set up Window
        TutorialWindow = createNativeWindow();
        TutorialWindow->setUseCallbackForDraw(true);
        TutorialWindow->setUseCallbackForReshape(true);

        //Initialize Window
        TutorialWindow->initWindow();


        // Create the SimpleSceneManager helper
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
        
        //Torus Material
        MaterialRecPtr TheTorusMaterial = SimpleMaterial::create();
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

        AnimationRecPtr TheAnimation = setupAnimation(TorusNodeTrans, TutorialWindow);

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
                "OpenSG 01Animation Window");
        
        // store a pointer to the application thread
        ApplicationThread = dynamic_cast<OSG::Thread *>(OSG::ThreadManager::getAppThread());
        
        //create the thread that will run generation of new matrices
        RenderThread =
            OSG::dynamic_pointer_cast<OSG::Thread>(
                OSG::ThreadManager::the()->getThread("render", true));
        
        //Start the render thread on aspect 1
        RenderThread->runFunction(draw, 1, static_cast<void *>(&sceneManager));

        //Enter main Loop
        TutorialWindow->mainLoop();

        //Stop the render thread
        RenderThread->terminate();
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

AnimationTransitPtr setupAnimation(Transform* const transCore, WindowEventProducer* const win)
{
    //Number Keyframe Sequence
    KeyframeNumberSequenceRecPtr NumberKeyframes = KeyframeNumberSequenceReal32::create();
    NumberKeyframes->addKeyframe(1.0,0.0f);
    NumberKeyframes->addKeyframe(60.0,1.0f);
    NumberKeyframes->addKeyframe(20.0,2.0f);
    NumberKeyframes->addKeyframe(1.0,3.0f);
    
    //Color Keyframe Sequence
    KeyframeColorSequenceRecPtr ColorKeyframes = KeyframeColorSequenceColor3f::create();
    ColorKeyframes->addKeyframe(Color4f(1.0f,0.0f,0.0f,1.0f),0.0f);
    ColorKeyframes->addKeyframe(Color4f(0.0f,1.0f,0.0f,1.0f),2.0f);
    ColorKeyframes->addKeyframe(Color4f(0.0f,0.0f,1.0f,1.0f),4.0f);
    ColorKeyframes->addKeyframe(Color4f(1.0f,0.0f,0.0f,1.0f),6.0f);

	//Position Keyframe Sequence
    KeyframePositionSequenceRecPtr PositionKeyframes = KeyframePositionSequencePnt3f::create();
    PositionKeyframes->addKeyframe(Pnt3f(1.0f,1.0f,1.0f),0.0f);
    PositionKeyframes->addKeyframe(Pnt3f(0.5f,1.0f,0.5f),1.0f);
    PositionKeyframes->addKeyframe(Pnt3f(1.0f,1.0f,0.5f),2.0f);
    PositionKeyframes->addKeyframe(Pnt3f(1.0f,0.5f,0.5f),3.0f);
    PositionKeyframes->addKeyframe(Pnt3f(1.0f,1.0f,1.0f),4.0f);

	//Vector Keyframe Sequence
    KeyframeVectorSequenceRecPtr VectorKeyframes = KeyframeVectorSequenceVec3f::create();
    VectorKeyframes->addKeyframe(Vec3f(1.0f,1.0f,1.0f),0.0f);
    VectorKeyframes->addKeyframe(Vec3f(0.5f,1.0f,0.5f),1.0f);
    VectorKeyframes->addKeyframe(Vec3f(1.0f,1.0f,0.5f),2.0f);
    VectorKeyframes->addKeyframe(Vec3f(1.0f,0.5f,0.5f),3.0f);
    VectorKeyframes->addKeyframe(Vec3f(1.0f,1.0f,1.0f),4.0f);
    
	//Rotation Keyframe Sequence
    KeyframeRotationSequenceRecPtr RotationKeyframes = KeyframeRotationSequenceQuaternion::create();
    RotationKeyframes->addKeyframe(Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*0.0f),0.0f);
    RotationKeyframes->addKeyframe(Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*0.5f),1.0f);
    RotationKeyframes->addKeyframe(Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*1.0f),2.0f);
    RotationKeyframes->addKeyframe(Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*1.5f),3.0f);
    RotationKeyframes->addKeyframe(Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*2.0f),4.0f);

	//Transformation Keyframe Sequence
    KeyframeTransformationSequenceRecPtr TransformationKeyframes = KeyframeTransformationSequenceMatrix4f::create();
    Matrix TempMat;
    TempMat.setTransform(Vec3f(0.0f,0.0f,0.0f), Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*0.0f));
    TransformationKeyframes->addKeyframe(TempMat,0.0f);
    TempMat.setTransform(Vec3f(0.0f,1.0f,0.0f), Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*0.5f));
    TransformationKeyframes->addKeyframe(TempMat,1.0f);
    TempMat.setTransform(Vec3f(1.0f,1.0f,0.0f), Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*1.0f));
    TransformationKeyframes->addKeyframe(TempMat,2.0f);
    TempMat.setTransform(Vec3f(1.0f,0.0f,0.0f), Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*1.5f));
    TransformationKeyframes->addKeyframe(TempMat,3.0f);
    TempMat.setTransform(Vec3f(0.0f,0.0f,0.0f), Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*2.0f));
    TransformationKeyframes->addKeyframe(TempMat,4.0f);
    
    //Animator
    KeyframeAnimatorRecPtr TheAnimator = KeyframeAnimator::create();
    //TheAnimator->setKeyframeSequence(VectorKeyframes);
    //TheAnimator->setKeyframeSequence(RotationKeyframes);
    //TheAnimator->setKeyframeSequence(ColorKeyframes);
    TheAnimator->setKeyframeSequence(TransformationKeyframes);
    //TheAnimator->setKeyframeSequence(NumberKeyframes);
    
    //Animation
    FieldAnimationRecPtr TheAnimation = FieldAnimation::create();
    TheAnimation->setAnimator(TheAnimator);
    TheAnimation->setInterpolationType(Animator::LINEAR_INTERPOLATION);
    TheAnimation->setCycling(2);
    //TheAnimation->setAnimatedField(getFieldContainer("Transform",std::string("TorusNodeTransformationCore")), std::string("matrix"));
    //TheAnimation->setAnimatedField(Trans, std::string("scale"));
    //TheAnimation->setAnimatedField(Trans, std::string("rotation"));
    //TheAnimation->setAnimatedField(TheTorusMaterial, std::string("diffuse"));
    //TheAnimation->setAnimatedField(TheTorusMaterial, std::string("shininess"));
    TheAnimation->setAnimatedField(transCore, std::string("matrix"));

    AnimationGroupRecPtr TheAnimationGroup = AnimationGroup::create();
    TheAnimationGroup->pushToAnimations(TheAnimation);
    TheAnimationGroup->setCycling(2);

    TheAnimationGroup->attachUpdateProducer(win);
    TheAnimationGroup->start();

    return AnimationTransitPtr(TheAnimationGroup);
}

