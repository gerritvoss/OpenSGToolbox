// 
// OpenSGToolbox Tutorial: 11BoneAnimation 
//
// Creates a simple skeleton and animates a bone using transformation keyframes. 
//


// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"
#include "OSGWindowUtils.h"

// Input
#include "OSGKeyListener.h"
#include "OSGUpdateListener.h"

#include "OSGLineChunk.h"
#include "OSGBlendChunk.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGSimpleGeometry.h"

//Animation
#include "OSGSkeletonBlendedGeometry.h"
#include "OSGSkeletonDrawable.h"

#include "OSGRandomPoolManager.h"

// FROM ANIMATION.CPP
#include "OSGTime.h"
#include "OSGKeyframeSequence.h"
#include "OSGFieldAnimation.h"
#include "OSGAnimationGroup.h"
#include "OSGKeyframeAnimator.h"
#include "OSGNameAttachment.h"
#include "OSGKeyframeSequences.h"



// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Forward declaration so we can have the interesting stuff upfront
AnimationTransitPtr setupAnimation(Transform* const TheJoint,
                                   Transform* const TheChildJoint);
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

void keyPressed(KeyEventDetails* const details,
                Animation* const TheCurrentAnimation,
                Node* const SkeletonNode,
                WindowEventProducer* const win)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        win->closeWindow();
    }
    //Toggle animation
    if(details->getKey() == KeyEventDetails::KEY_SPACE)
    {
        TheCurrentAnimation->pause(!TheCurrentAnimation->isPaused());
    }

    //Toggle bind pose
    if(details->getKey() == KeyEventDetails::KEY_B)
    {
        //Toggle skeleton
        if(dynamic_cast<SkeletonDrawable*>(SkeletonNode->getCore())->getDrawBindPose() == false)
        {
            dynamic_cast<SkeletonDrawable*>(SkeletonNode->getCore())->setDrawBindPose(true);
        } 
        else
        {
            dynamic_cast<SkeletonDrawable*>(SkeletonNode->getCore())->setDrawBindPose(false);
        }
    }

    //Toggle current pose
    if(details->getKey() == KeyEventDetails::KEY_P)
    {
        //Toggle skeleton
        if(dynamic_cast<SkeletonDrawable*>(SkeletonNode->getCore())->getDrawPose() == false)
        {
            dynamic_cast<SkeletonDrawable*>(SkeletonNode->getCore())->setDrawPose(true);
        } 
        else
        {
            dynamic_cast<SkeletonDrawable*>(SkeletonNode->getCore())->setDrawPose(false);
        }
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
            //mgr->updateCameraTransformation();
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
        TutorialWindow->connectMouseWheelMoved(boost::bind(mouseWheelMoved, _1, &sceneManager));

        //Print key command info
        std::cout << "\n\nKEY COMMANDS:" << std::endl;
        std::cout << "space   Play/Pause the animation" << std::endl;
        std::cout << "B       Show/Hide the bind pose skeleton" << std::endl;
        std::cout << "P       Show/Hide the current pose skeleton" << std::endl;
        //std::cout << "1       Play first example animation" << std::endl;
        //std::cout << "2       Play second example animation" << std::endl;
        std::cout << "CTRL-Q  Exit\n\n" << std::endl;


        //SkeletonDrawer System Material
        LineChunkUnrecPtr ExampleLineChunk = LineChunk::create();
        ExampleLineChunk->setWidth(2.0f);
        ExampleLineChunk->setSmooth(true);

        BlendChunkUnrecPtr ExampleBlendChunk = BlendChunk::create();
        ExampleBlendChunk->setSrcFactor(GL_SRC_ALPHA);
        ExampleBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

        MaterialChunkUnrecPtr ExampleMaterialChunk = MaterialChunk::create();
        ExampleMaterialChunk->setAmbient(Color4f(1.0f,1.0f,1.0f,1.0f));
        ExampleMaterialChunk->setDiffuse(Color4f(0.0f,0.0f,0.0f,1.0f));
        ExampleMaterialChunk->setSpecular(Color4f(0.0f,0.0f,0.0f,1.0f));

        ChunkMaterialUnrecPtr ExampleMaterial = ChunkMaterial::create();
        ExampleMaterial->addChunk(ExampleLineChunk);
        ExampleMaterial->addChunk(ExampleMaterialChunk);
        ExampleMaterial->addChunk(ExampleBlendChunk);

        GeometryRefPtr SphereGeometry = makeSphereGeo(2, 0.25f);
        GeometryRefPtr BoxGeometry = makeBoxGeo(0.5f,0.5f,0.5f,1,1,1);

        //Skeleton
        SkeletonBlendedGeometryUnrecPtr ExampleSkeleton = SkeletonBlendedGeometry::create();

        //Joint
        TransformRecPtr ExampleRootJoint = Transform::create();

        NodeRecPtr ExampleRootJointNode = makeNodeFor(ExampleRootJoint);

        //Add this joint to the skeleton
        ExampleSkeleton->pushToJoints(ExampleRootJointNode, Matrix());

        NodeRecPtr TempRootJointNode = ExampleRootJointNode;
        NodeRefPtr GeoNode = makeNodeFor(BoxGeometry);
        TempRootJointNode->addChild(GeoNode);

        Matrix TempMat;
        //Create a set of randomly placed child joints
        for (Real32 i = 0.0f; i < 5.0f; ++i)
        {
            TransformRecPtr ExampleChildJoint = Transform::create();
            NodeRecPtr ExampleChildJointNode = makeNodeFor(ExampleChildJoint);

            GeoNode = makeNodeFor(SphereGeometry);
            ExampleChildJointNode->addChild(GeoNode);

            //TempMat.setTranslate(RandomPoolManager::getRandomReal32(0.0, 10.0f), RandomPoolManager::getRandomReal32(0.0f, 10.0f), RandomPoolManager::getRandomReal32(0.0f, 10.0f));
            switch((static_cast<UInt32>(i) % 3))
            {
                case 0:
                    TempMat.setTranslate(2.0f,0.0f,0.0f);
                    break;
                case 1:
                    TempMat.setTranslate(0.0f,2.0f,0.0f);
                    break;
                case 2:
                    TempMat.setTranslate(0.0f,0.0f,2.0f);
                    break;
            }

            //Set bind and current transformations to TempMat (calculated above)
            ExampleChildJoint->setMatrix(TempMat);

            //Add ExampleChildJoint as a child to the previous joint	
            TempRootJointNode->addChild(ExampleChildJointNode);//add a Child to the root joint

            //ExampleChildJoint will be the next parent joint
            TempRootJointNode = ExampleChildJointNode;

            //Add this joint to the skeleton
            Matrix InvBind(TempRootJointNode->getToWorld());
            InvBind.invert();
            ExampleSkeleton->pushToJoints(ExampleChildJointNode, InvBind);
        }

        //SkeletonDrawer
        SkeletonDrawableUnrecPtr ExampleSkeletonDrawable = SkeletonDrawable::create();
        ExampleSkeletonDrawable->setSkeleton(ExampleSkeleton);
        ExampleSkeletonDrawable->setMaterial(ExampleMaterial);
        ExampleSkeletonDrawable->setDrawBindPose(false);  //By default, we won't draw the skeleton's bind pose
        ExampleSkeletonDrawable->setBindPoseColor(Color4f(0.0, 1.0, 0.0, 1.0));  //When the skeleton's bind pose is rendered, it will be green
        ExampleSkeletonDrawable->setDrawPose(true);  //By default, we do draw the skeleton's current pose
        ExampleSkeletonDrawable->setPoseColor(Color4f(0.0, 0.0, 1.0, 1.0));  //The skeleton's current pose is rendered in blue

        //Skeleton Node
        NodeUnrecPtr SkeletonNode = Node::create();
        SkeletonNode->setCore(ExampleSkeletonDrawable);

        //Create scene
        NodeUnrecPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(SkeletonNode);
        scene->addChild(ExampleRootJointNode);

        sceneManager.setRoot(scene);

        //Setup the Animation
        AnimationUnrecPtr TheAnimation = setupAnimation(ExampleRootJoint,
                                                        dynamic_cast<Transform*>(ExampleRootJointNode->getChild(1)->getCore()));
        TheAnimation->attachUpdateProducer(TutorialWindow);
        TheAnimation->start();

        TutorialWindow->connectKeyPressed(boost::bind(keyPressed, _1,
                                                      TheAnimation.get(),
                                                      SkeletonNode.get(),
                                                      TutorialWindow.get()));

        // Show the whole Scene
        sceneManager.showAll();


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "11BoneAnimation");

        //Main Loop
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

AnimationTransitPtr setupAnimation(Transform* const TheJoint, Transform* const TheChildJoint)
{
    //Create an animation for TheJoint
    //TheJoint Transformation keyframes (we'll animate TheJoint's translation)
    Matrix transform = TheJoint->getMatrix();

    KeyframeTransformationSequenceUnrecPtr TheJointTranformationKeyframes = KeyframeTransformationSequenceMatrix4f::create();

    transform.setTranslate(0.0f,0.0f,0.0f);
    TheJointTranformationKeyframes->addKeyframe(transform, 0.0f);

    transform.setTranslate(2.0f,0.0f,0.0f);
    TheJointTranformationKeyframes->addKeyframe(transform, 2.0f);

    transform.setTranslate(1.0f,0.0f,0.0f);
    TheJointTranformationKeyframes->addKeyframe(transform, 4.0f);

    transform.setTranslate(3.0f,0.0f,0.0f);
    TheJointTranformationKeyframes->addKeyframe(transform, 6.0f);

    transform = TheJoint->getMatrix();
    transform.setTranslate(0.0f,0.0f,0.0f);
    TheJointTranformationKeyframes->addKeyframe(transform, 8.0f);

    //TheJoint Animator
    AnimatorUnrecPtr TheJointAnimator = KeyframeAnimator::create();
    dynamic_pointer_cast<KeyframeAnimator>(TheJointAnimator)->setKeyframeSequence(TheJointTranformationKeyframes);

    //TheJoint Animation
    FieldAnimationUnrecPtr TheJointAnimation = FieldAnimation::create();
    TheJointAnimation->setAnimator(TheJointAnimator);
    TheJointAnimation->setInterpolationType(Animator::CUBIC_INTERPOLATION);
    TheJointAnimation->setCycling(-1);
    TheJointAnimation->setAnimatedField(TheJoint,
                                        std::string("matrix"));

    //Create an animation for TheChildJoint
    //TheChildJoint Transformation keyframes (we'll animate TheChildJoint's rotation)
    transform = TheChildJoint->getMatrix();

    KeyframeTransformationSequenceUnrecPtr TheChildJointTransformationKeyframes = KeyframeTransformationSequenceMatrix4f::create();

    TheChildJointTransformationKeyframes->addKeyframe(transform, 0.0f);

    transform.setRotate(Quaternion(Vec3f(0.0,1.0,0.0),0.0));
    TheChildJointTransformationKeyframes->addKeyframe(transform, 2.0f);

    transform.setRotate(Quaternion(Vec3f(0.0,1.0,0.0),0.5*Pi));
    TheChildJointTransformationKeyframes->addKeyframe(transform, 4.0f);

    transform.setRotate(Quaternion(Vec3f(0.0,1.0,0.0),Pi));
    TheChildJointTransformationKeyframes->addKeyframe(transform, 6.0f);

    transform.setRotate(Quaternion(Vec3f(0.0,1.0,0.0),1.5*Pi));
    TheChildJointTransformationKeyframes->addKeyframe(transform, 8.0f);

    transform.setRotate(Quaternion(Vec3f(0.0,1.0,0.0),2.0*Pi));
    TheChildJointTransformationKeyframes->addKeyframe(transform, 10.0f);

    //TheChildJoint Animator
    AnimatorUnrecPtr TheChildJointAnimator = KeyframeAnimator::create();
    dynamic_pointer_cast<KeyframeAnimator>(TheChildJointAnimator)->setKeyframeSequence(TheChildJointTransformationKeyframes);

    //TheChildJoint Animation
    FieldAnimationUnrecPtr TheChildJointAnimation = FieldAnimation::create();
    TheChildJointAnimation->setAnimator(TheChildJointAnimator);
    TheChildJointAnimation->setInterpolationType(Animator::CUBIC_INTERPOLATION);
    TheChildJointAnimation->setCycling(-1);
    TheChildJointAnimation->setAnimatedField(TheChildJoint, std::string("matrix"));

    AnimationGroupUnrecPtr TheAnimationGroup = AnimationGroup::create();
    TheAnimationGroup->pushToAnimations(TheJointAnimation);
    TheAnimationGroup->pushToAnimations(TheChildJointAnimation);

    return AnimationTransitPtr(TheAnimationGroup);
}

