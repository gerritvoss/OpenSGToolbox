// 
// OpenSGToolbox Tutorial: 12SkeletonAnimation 
//
// Creates a skeleton and animates it. 
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

#include "OSGLineChunk.h"
#include "OSGBlendChunk.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"

#include "OSGRandomPoolManager.h"

// FROM ANIMATION.CPP
#include "OSGTime.h"
#include "OSGKeyframeSequences.h"
#include "OSGFieldAnimation.h"
#include "OSGKeyframeAnimator.h"
#include "OSGNameAttachment.h"
#include "OSGSkeletonAnimation.h"
#include "OSGSkeletonDrawable.h"
#include "OSGSkeleton.h"
#include "OSGJoint.h"



// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerUnrecPtr TutorialWindow;

Time TimeLastIdle;
NodeUnrecPtr SkeletonNode;
SkeletonAnimationUnrecPtr TheSkeletonAnimation;
bool animationPaused = false;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);
void setupAnimation(void);

JointUnrecPtr Pelvis,LeftHip,RightHip,LeftKnee,RightKnee,LeftFoot,RightFoot,LeftToes,RightToes, Clavicle, LeftShoulder,RightShoulder,LeftElbow,RightElbow,LeftHand,RightHand,LeftFingers,RightFingers,Head; 
SkeletonUnrecPtr ExampleSkeleton;


// Create a class to allow for the use of the keyboard shortcuts 
class TutorialKeyListener : public KeyListener
{
public:

    virtual void keyPressed(const KeyEventUnrecPtr e)
    {
        //Exit
        if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
        {
            TutorialWindow->closeWindow();
        }

        //Toggle animation
        if(e->getKey() == KeyEvent::KEY_SPACE)
        {
            if(animationPaused)
                animationPaused = false;
            else
                animationPaused = true;
        }

        //Toggle bind pose
        if(e->getKey() == KeyEvent::KEY_B)
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
        if(e->getKey() == KeyEvent::KEY_P)
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

    //Print key command info
    std::cout << "\n\nKEY COMMANDS:" << std::endl
              << "space   Play/Pause the animation" << std::endl
              << "B       Show/Hide the bind pose skeleton" << std::endl
              << "P       Show/Hide the current pose skeleton" << std::endl
              << "CTRL-Q  Exit\n\n" << std::endl;


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

    //===========================================Joints==================================================================
    Matrix TempMat;

    /*================================================================================================*/
    /*                                       Left Fingers                                                 */
    LeftFingers = Joint::create(); //create a joint called LeftFingers 
    TempMat.setTranslate(1.0,0.0,0.0);
    LeftFingers->setRelativeTransformation(TempMat);
    LeftFingers->setBindRelativeTransformation(TempMat);

    /*================================================================================================*/
    /*                                       Right Fingers                                                 */
    RightFingers = Joint::create(); //create a joint called RightFingers 
    TempMat.setTranslate(-1.0,0.0,0.0);
    RightFingers->setRelativeTransformation(TempMat);
    RightFingers->setBindRelativeTransformation(TempMat);
    /*================================================================================================*/
    /*                                       Left Hand                                                 */
    LeftHand = Joint::create(); //create a joint called LeftHand 
    TempMat.setTranslate(2.0,0.0,0.0);
    LeftHand->setRelativeTransformation(TempMat);
    LeftHand->setBindRelativeTransformation(TempMat);
    LeftHand->pushToChildJoints(LeftFingers);

    /*================================================================================================*/
    /*                                       Right Hand                                                 */
    RightHand = Joint::create(); //create a joint called RightHand 
    TempMat.setTranslate(-2.0,0.0,0.0);
    RightHand->setRelativeTransformation(TempMat);
    RightHand->setBindRelativeTransformation(TempMat);
    RightHand->pushToChildJoints(RightFingers);
    /*================================================================================================*/
    /*                                       Left Elbow                                                 */
    LeftElbow = Joint::create(); //create a joint called LeftElbow 
    TempMat.setTranslate(2.0,0.0,0.0);
    LeftElbow->setRelativeTransformation(TempMat);
    LeftElbow->setBindRelativeTransformation(TempMat);
    LeftElbow->pushToChildJoints(LeftHand);

    /*================================================================================================*/
    /*                                       Right Elbow                                                 */
    RightElbow = Joint::create(); //create a joint called RightElbow 
    TempMat.setTranslate(-2.0,0.0,0.0);
    RightElbow->setRelativeTransformation(TempMat);
    RightElbow->setBindRelativeTransformation(TempMat);
    RightElbow->pushToChildJoints(RightHand);
    /*================================================================================================*/
    /*                                       Left Shoulder                                                 */
    LeftShoulder = Joint::create(); //create a joint called LeftShoulder 
    TempMat.setTranslate(1.0,-0.5,0.0);
    LeftShoulder->setRelativeTransformation(TempMat);
    LeftShoulder->setBindRelativeTransformation(TempMat);
    LeftShoulder->pushToChildJoints(LeftElbow);

    /*================================================================================================*/
    /*                                       Right Shoulder                                                 */
    RightShoulder = Joint::create(); //create a joint called RightShoulder 
    TempMat.setTranslate(-1.0,-0.5,0.0);
    RightShoulder->setRelativeTransformation(TempMat);
    RightShoulder->setBindRelativeTransformation(TempMat);
    RightShoulder->pushToChildJoints(RightElbow);

    /*================================================================================================*/
    /*                                       Head                                                 */
    Head = Joint::create(); //create a joint called Head 
    TempMat.setTranslate(0.0,1.0,0.0);
    Head->setRelativeTransformation(TempMat);
    Head->setBindRelativeTransformation(TempMat);

    /*================================================================================================*/
    /*                                       Clavicle                                                   */
    Clavicle = Joint::create(); //create a joint called Clavicle 
    TempMat.setTranslate(0.0,5.0,0.0);
    Clavicle->setRelativeTransformation(TempMat);
    Clavicle->setBindRelativeTransformation(TempMat);
    Clavicle->pushToChildJoints(LeftShoulder);
    Clavicle->pushToChildJoints(RightShoulder);
    Clavicle->pushToChildJoints(Head);

    /*================================================================================================*/
    /*                                       Left Toes                                                 */
    LeftToes = Joint::create(); //create a bone called ExampleChildbone
    TempMat.setTranslate(0.0,0.0,1.0);
    LeftToes->setRelativeTransformation(TempMat);
    LeftToes->setBindRelativeTransformation(TempMat);

    /*================================================================================================*/
    /*                                       Right Toes                                                 */
    RightToes = Joint::create(); //create a joint called RightToes 
    TempMat.setTranslate(0.0,0.0,1.0);
    RightToes->setRelativeTransformation(TempMat);
    RightToes->setBindRelativeTransformation(TempMat);
    /*================================================================================================*/
    /*                                       Left Foot                                                 */
    LeftFoot = Joint::create(); //create a joint called LeftFoot 
    TempMat.setTranslate(0.0,-3.0,0.0);
    LeftFoot->setRelativeTransformation(TempMat);
    LeftFoot->setBindRelativeTransformation(TempMat);
    LeftFoot->pushToChildJoints(LeftToes);

    /*================================================================================================*/
    /*                                       Right Foot                                                 */
    RightFoot = Joint::create(); //create a joint called RightFoot 
    TempMat.setTranslate(0.0,-3.0,0.0);
    RightFoot->setRelativeTransformation(TempMat);
    RightFoot->setBindRelativeTransformation(TempMat);
    RightFoot->pushToChildJoints(RightToes);
    /*================================================================================================*/
    /*                                       Left Knee                                                 */
    LeftKnee = Joint::create(); //create a joint called LeftKnee 
    TempMat.setTranslate(0.0,-3.0,0.0);
    LeftKnee->setRelativeTransformation(TempMat);
    LeftKnee->setBindRelativeTransformation(TempMat);
    LeftKnee->pushToChildJoints(LeftFoot);

    /*================================================================================================*/
    /*                                       Right Knee                                                 */
    RightKnee = Joint::create(); //create a joint called RightKnee 
    TempMat.setTranslate(0.0,-3.0,0.0);
    RightKnee->setRelativeTransformation(TempMat);
    RightKnee->setBindRelativeTransformation(TempMat);
    RightKnee->pushToChildJoints(RightFoot);

    /*================================================================================================*/
    /*                                       Left Hip                                                 */
    LeftHip = Joint::create(); //create a joint called LeftHip 
    TempMat.setTranslate(1.0,-1.0,0.0);
    LeftHip->setRelativeTransformation(TempMat);
    LeftHip->setBindRelativeTransformation(TempMat);
    LeftHip->pushToChildJoints(LeftKnee);

    /*================================================================================================*/
    /*                                       Right Hip                                                 */
    RightHip = Joint::create(); //create a joint called RightHip 
    TempMat.setTranslate(-1.0,-1.0,0.0);
    RightHip->setRelativeTransformation(TempMat);
    RightHip->setBindRelativeTransformation(TempMat);
    RightHip->pushToChildJoints(RightKnee);

    /*================================================================================================*/
    /*                                       Pelvis                                                   */
    Pelvis = Joint::create(); //create a joint called Pelvis 
    TempMat.setTranslate(0.0,7.0,0.0);
    Pelvis->setRelativeTransformation(TempMat);
    Pelvis->setBindRelativeTransformation(TempMat);
    Pelvis->pushToChildJoints(LeftHip);
    Pelvis->pushToChildJoints(RightHip);
    Pelvis->pushToChildJoints(Clavicle);



    //Skeleton
    ExampleSkeleton = Skeleton::create();
    ExampleSkeleton->pushToRootJoints(Pelvis);  //Set Pelvis as root joint of skeleton

    //SkeletonDrawer
    SkeletonDrawableUnrecPtr ExampleSkeletonDrawable = SkeletonDrawable::create();
    ExampleSkeletonDrawable->setSkeleton(ExampleSkeleton);
    ExampleSkeletonDrawable->setMaterial(ExampleMaterial);
    ExampleSkeletonDrawable->setDrawBindPose(false);  //Be default, we won't draw the skeleton's bind pose
    ExampleSkeletonDrawable->setBindPoseColor(Color4f(0.0, 1.0, 0.0, 1.0));  //When drawn, the skeleton's bind pose renders green
    ExampleSkeletonDrawable->setDrawPose(true);  //Be default, we do draw the skeleton's current pose
    ExampleSkeletonDrawable->setPoseColor(Color4f(0.0, 0.0, 1.0, 1.0));  //The skeleton's current pose renders blue

    //Skeleton Node
    SkeletonNode = Node::create();
    SkeletonNode->setCore(ExampleSkeletonDrawable);

    //Create scene    
    NodeUnrecPtr scene = Node::create();
    scene->setCore(Group::create());
    scene->addChild(SkeletonNode);

    mgr->setRoot(scene);

    //Setup the Animation
    setupAnimation();



    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
            WinSize,
            "12SkeletonAnimation");

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
    Matrix TempMat;

    //We create an animation and an animator for each joint we wish to animate

    //Left Elbow
    KeyframeTransformationSequenceUnrecPtr LeftElbowKeyframes = KeyframeTransformationSequenceMatrix4f::create();
    //Make keyframes
    TempMat.setTransform(Vec3f(2.0,0.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0f));
    LeftElbowKeyframes->addKeyframe(TempMat,0.0f);
    TempMat.setTransform(Vec3f(2.0,0.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),1.57f));
    LeftElbowKeyframes->addKeyframe(TempMat,3.0f);
    TempMat.setTransform(Vec3f(2.0,0.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0f));
    LeftElbowKeyframes->addKeyframe(TempMat,6.0f);

    //Left Elbow Animator
    KeyframeAnimatorUnrecPtr LeftElbowAnimator = KeyframeAnimator::create();
    LeftElbowAnimator->setKeyframeSequence(LeftElbowKeyframes);

    //Right Elbow
    KeyframeTransformationSequenceUnrecPtr RightElbowKeyframes = KeyframeTransformationSequenceMatrix4f::create();
    //Make keyframes
    TempMat.setTransform(Vec3f(-2.0,0.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0f));
    RightElbowKeyframes->addKeyframe(TempMat,0.0f);
    TempMat.setTransform(Vec3f(-2.0,0.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),-1.57f));
    RightElbowKeyframes->addKeyframe(TempMat,3.0f);
    TempMat.setTransform(Vec3f(-2.0,0.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0f));
    RightElbowKeyframes->addKeyframe(TempMat,6.0f);

    //Right Elbow Animator
    KeyframeAnimatorUnrecPtr RightElbowAnimator = KeyframeAnimator::create();
    RightElbowAnimator->setKeyframeSequence(RightElbowKeyframes);

    //Left Shoulder
    KeyframeTransformationSequenceUnrecPtr LeftShoulderKeyframes = KeyframeTransformationSequenceMatrix4f::create();
    //Make keyframes
    TempMat.setTransform(Vec3f(1.0,-0.5,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0f));
    LeftShoulderKeyframes->addKeyframe(TempMat,0.0f);
    TempMat.setTransform(Vec3f(1.0,-0.5,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.4f));
    LeftShoulderKeyframes->addKeyframe(TempMat,3.0f);
    TempMat.setTransform(Vec3f(1.0,-0.5,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0f));
    LeftShoulderKeyframes->addKeyframe(TempMat,6.0f);

    //Left Shoulder Animator
    KeyframeAnimatorUnrecPtr LeftShoulderAnimator = KeyframeAnimator::create();
    LeftShoulderAnimator->setKeyframeSequence(LeftShoulderKeyframes);

    //Right Shoulder
    KeyframeTransformationSequenceUnrecPtr RightShoulderKeyframes = KeyframeTransformationSequenceMatrix4f::create();
    //Make keyframes
    TempMat.setTransform(Vec3f(-1.0,-0.5,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0f));
    RightShoulderKeyframes->addKeyframe(TempMat,0.0f);
    TempMat.setTransform(Vec3f(-1.0,-0.5,0.0),Quaternion(Vec3f(0.0,0.0,1.0),-0.4f));
    RightShoulderKeyframes->addKeyframe(TempMat,3.0f);
    TempMat.setTransform(Vec3f(-1.0,-0.5,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0f));
    RightShoulderKeyframes->addKeyframe(TempMat,6.0f);

    //Right Shoulder Animator
    KeyframeAnimatorUnrecPtr RightShoulderAnimator = KeyframeAnimator::create();
    RightShoulderAnimator->setKeyframeSequence(RightShoulderKeyframes);

    //Left Hip
    KeyframeTransformationSequenceUnrecPtr LeftHipKeyframes = KeyframeTransformationSequenceMatrix4f::create();
    //Make keyframes
    TempMat.setTransform(Vec3f(1.0,-1.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0f));
    LeftHipKeyframes->addKeyframe(TempMat,0.0f);
    TempMat.setTransform(Vec3f(1.0,-1.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.4f));
    LeftHipKeyframes->addKeyframe(TempMat,3.0f);
    TempMat.setTransform(Vec3f(1.0,-1.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0f));
    LeftHipKeyframes->addKeyframe(TempMat,6.0f);

    //Left Hip Animator
    KeyframeAnimatorUnrecPtr LeftHipAnimator = KeyframeAnimator::create();
    LeftHipAnimator->setKeyframeSequence(LeftHipKeyframes);

    //Right Hip
    KeyframeTransformationSequenceUnrecPtr RightHipKeyframes = KeyframeTransformationSequenceMatrix4f::create();
    //Make keyframes
    TempMat.setTransform(Vec3f(-1.0,-1.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0f));
    RightHipKeyframes->addKeyframe(TempMat,0.0f);
    TempMat.setTransform(Vec3f(-1.0,-1.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),-0.4f));
    RightHipKeyframes->addKeyframe(TempMat,3.0f);
    TempMat.setTransform(Vec3f(-1.0,-1.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0f));
    RightHipKeyframes->addKeyframe(TempMat,6.0f);

    //Right Hip Animator
    KeyframeAnimatorUnrecPtr RightHipAnimator = KeyframeAnimator::create();
    RightHipAnimator->setKeyframeSequence(RightHipKeyframes);


    //Clavicle
    KeyframeTransformationSequenceUnrecPtr ClavicleKeyframes = KeyframeTransformationSequenceMatrix4f::create();
    //Make keyframes
    TempMat.setTransform(Vec3f(0.0,5.0,0.0));
    ClavicleKeyframes->addKeyframe(TempMat,0.0f);
    TempMat.setTransform(Vec3f(0.0,3.0,0.0));
    ClavicleKeyframes->addKeyframe(TempMat,2.0f);
    TempMat.setTransform(Vec3f(0.0,3.0,0.0));
    ClavicleKeyframes->addKeyframe(TempMat,4.0f);
    TempMat.setTransform(Vec3f(0.0,5.0,0.0));
    ClavicleKeyframes->addKeyframe(TempMat,6.0f);

    //Clavicle Animator
    KeyframeAnimatorUnrecPtr ClavicleAnimator = KeyframeAnimator::create();
    ClavicleAnimator->setKeyframeSequence(ClavicleKeyframes);

    //Skeleton Animation
    TheSkeletonAnimation = SkeletonAnimation::create();
    //Add the animators we just made to the skeleton animation
    TheSkeletonAnimation->addTransformationAnimator(LeftElbowAnimator, LeftElbow);  //Here we tell the skeleton animation the it should use the animator LeftElbowAnimator to animate the joint LeftElbow
    TheSkeletonAnimation->addTransformationAnimator(RightElbowAnimator, RightElbow);
    TheSkeletonAnimation->addTransformationAnimator(LeftShoulderAnimator, LeftShoulder);
    TheSkeletonAnimation->addTransformationAnimator(RightShoulderAnimator, RightShoulder);
    TheSkeletonAnimation->addTransformationAnimator(LeftHipAnimator, LeftHip);
    TheSkeletonAnimation->addTransformationAnimator(RightHipAnimator, RightHip);
    TheSkeletonAnimation->addTransformationAnimator(ClavicleAnimator, Clavicle);
    TheSkeletonAnimation->setSkeleton(ExampleSkeleton);

    TheSkeletonAnimation->attachUpdateProducer(TutorialWindow->editEventProducer());
    TheSkeletonAnimation->start();
}
