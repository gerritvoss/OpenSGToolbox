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
#include "OSGAnimationGroup.h"
#include "OSGSkeletonDrawable.h"
//#include "OSGSkeleton.h"



// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerUnrecPtr TutorialWindow;

Time TimeLastIdle;
NodeUnrecPtr SkeletonNode;
AnimationGroupUnrecPtr TheSkeletonAnimation;
bool animationPaused = false;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);
void setupAnimation(void);

TransformUnrecPtr Pelvis,LeftHip,RightHip,LeftKnee,RightKnee,LeftFoot,RightFoot,LeftToes,RightToes, Clavicle, LeftShoulder,RightShoulder,LeftElbow,RightElbow,LeftHand,RightHand,LeftFingers,RightFingers,Head; 
SkeletonBlendedGeometryUnrecPtr ExampleSkeleton;


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

    //Skeleton
    ExampleSkeleton = SkeletonBlendedGeometry::create();

    //===========================================Joints==================================================================
    Matrix TempMat;
    Matrix InvBind;

    /*================================================================================================*/
    /*                                       Pelvis                                                   */
    Pelvis = Transform::create(); //create a joint called Pelvis 
    TempMat.setTranslate(0.0,7.0,0.0);
    Pelvis->setMatrix(TempMat);

    NodeRecPtr PelvisNode = makeNodeFor(Pelvis);

    InvBind = PelvisNode->getToWorld();
    InvBind.invert();
    ExampleSkeleton->pushToJoints(PelvisNode, InvBind);
    
    /*================================================================================================*/
    /*                                       Clavicle                                                   */
    Clavicle = Transform::create(); //create a joint called Clavicle 
    TempMat.setTranslate(0.0,5.0,0.0);
    Clavicle->setMatrix(TempMat);

    NodeRecPtr ClavicleNode = makeNodeFor(Clavicle);
    PelvisNode->addChild(ClavicleNode);

    InvBind = ClavicleNode->getToWorld();
    InvBind.invert();
    ExampleSkeleton->pushToJoints(ClavicleNode, InvBind);

    /*================================================================================================*/
    /*                                       Left Shoulder                                                 */
    LeftShoulder = Transform::create(); //create a joint called LeftShoulder 
    TempMat.setTranslate(1.0,-0.5,0.0);
    LeftShoulder->setMatrix(TempMat);

    NodeRecPtr LeftShoulderNode = makeNodeFor(LeftShoulder);
    ClavicleNode->addChild(LeftShoulderNode);

    InvBind = LeftShoulderNode->getToWorld();
    InvBind.invert();
    ExampleSkeleton->pushToJoints(LeftShoulderNode, InvBind);

    /*================================================================================================*/
    /*                                       Left Elbow                                                 */
    LeftElbow = Transform::create(); //create a joint called LeftElbow 
    TempMat.setTranslate(2.0,0.0,0.0);
    LeftElbow->setMatrix(TempMat);

    NodeRecPtr LeftElbowNode = makeNodeFor(LeftElbow);
    LeftShoulderNode->addChild(LeftElbowNode);

    InvBind = LeftElbowNode->getToWorld();
    InvBind.invert();
    ExampleSkeleton->pushToJoints(LeftElbowNode, InvBind);

    /*================================================================================================*/
    /*                                       Left Hand                                                 */
    LeftHand = Transform::create(); //create a joint called LeftHand 
    TempMat.setTranslate(2.0,0.0,0.0);
    LeftHand->setMatrix(TempMat);

    NodeRecPtr LeftHandNode = makeNodeFor(LeftHand);
    LeftElbowNode->addChild(LeftHandNode);

    InvBind = LeftHandNode->getToWorld();
    InvBind.invert();
    ExampleSkeleton->pushToJoints(LeftHandNode, InvBind);
    /*================================================================================================*/
    /*                                       Left Fingers                                                 */
    LeftFingers = Transform::create(); //create a joint called LeftFingers 
    TempMat.setTranslate(1.0,0.0,0.0);
    LeftFingers->setMatrix(TempMat);

    NodeRecPtr LeftFingersNode = makeNodeFor(LeftFingers);
    LeftHandNode->addChild(LeftFingersNode);

    InvBind = LeftFingersNode->getToWorld();
    InvBind.invert();
    ExampleSkeleton->pushToJoints(LeftFingersNode, InvBind);

    /*================================================================================================*/
    /*                                       Right Shoulder                                                 */
    RightShoulder = Transform::create(); //create a joint called RightShoulder 
    TempMat.setTranslate(-1.0,-0.5,0.0);
    RightShoulder->setMatrix(TempMat);

    NodeRecPtr RightShoulderNode = makeNodeFor(RightShoulder);
    ClavicleNode->addChild(RightShoulderNode);

    InvBind = RightShoulderNode->getToWorld();
    InvBind.invert();
    ExampleSkeleton->pushToJoints(RightShoulderNode, InvBind);

    /*================================================================================================*/
    /*                                       Right Elbow                                                 */
    RightElbow = Transform::create(); //create a joint called RightElbow 
    TempMat.setTranslate(-2.0,0.0,0.0);
    RightElbow->setMatrix(TempMat);

    NodeRecPtr RightElbowNode = makeNodeFor(RightElbow);
    RightShoulderNode->addChild(RightElbowNode);

    InvBind = RightElbowNode->getToWorld();
    InvBind.invert();
    ExampleSkeleton->pushToJoints(RightElbowNode, InvBind);

    /*================================================================================================*/
    /*                                       Right Hand                                                 */
    RightHand = Transform::create(); //create a joint called RightHand 
    TempMat.setTranslate(-2.0,0.0,0.0);
    RightHand->setMatrix(TempMat);

    NodeRecPtr RightHandNode = makeNodeFor(RightHand);
    RightElbowNode->addChild(RightHandNode);

    InvBind = RightHandNode->getToWorld();
    InvBind.invert();
    ExampleSkeleton->pushToJoints(RightHandNode, InvBind);

    /*================================================================================================*/
    /*                                       Right Fingers                                                 */
    RightFingers = Transform::create(); //create a joint called RightFingers 
    TempMat.setTranslate(-1.0,0.0,0.0);
    RightFingers->setMatrix(TempMat);

    NodeRecPtr RightFingersNode = makeNodeFor(RightFingers);
    RightHandNode->addChild(RightFingersNode);

    InvBind = RightFingersNode->getToWorld();
    InvBind.invert();
    ExampleSkeleton->pushToJoints(RightFingersNode, InvBind);

    /*================================================================================================*/
    /*                                       Head                                                 */
    Head = Transform::create(); //create a joint called Head 
    TempMat.setTranslate(0.0,1.0,0.0);
    Head->setMatrix(TempMat);

    NodeRecPtr HeadNode = makeNodeFor(Head);
    ClavicleNode->addChild(HeadNode);

    InvBind = HeadNode->getToWorld();
    InvBind.invert();
    ExampleSkeleton->pushToJoints(HeadNode, InvBind);

    /*================================================================================================*/
    /*                                       Left Hip                                                 */
    LeftHip = Transform::create(); //create a joint called LeftHip 
    TempMat.setTranslate(1.0,-1.0,0.0);
    LeftHip->setMatrix(TempMat);

    NodeRecPtr LeftHipNode = makeNodeFor(LeftHip);
    PelvisNode->addChild(LeftHipNode);

    InvBind = LeftHipNode->getToWorld();
    InvBind.invert();
    ExampleSkeleton->pushToJoints(LeftHipNode, InvBind);

    /*================================================================================================*/
    /*                                       Left Knee                                                 */
    LeftKnee = Transform::create(); //create a joint called LeftKnee 
    TempMat.setTranslate(0.0,-3.0,0.0);
    LeftKnee->setMatrix(TempMat);

    NodeRecPtr LeftKneeNode = makeNodeFor(LeftKnee);
    LeftHipNode->addChild(LeftKneeNode);

    InvBind = LeftKneeNode->getToWorld();
    InvBind.invert();
    ExampleSkeleton->pushToJoints(LeftKneeNode, InvBind);

    /*================================================================================================*/
    /*                                       Left Foot                                                 */
    LeftFoot = Transform::create(); //create a joint called LeftFoot 
    TempMat.setTranslate(0.0,-3.0,0.0);
    LeftFoot->setMatrix(TempMat);

    NodeRecPtr LeftFootNode = makeNodeFor(LeftFoot);
    LeftKneeNode->addChild(LeftFootNode);

    InvBind = LeftFootNode->getToWorld();
    InvBind.invert();
    ExampleSkeleton->pushToJoints(LeftFootNode, InvBind);

    /*================================================================================================*/
    /*                                       Left Toes                                                 */
    LeftToes = Transform::create(); //create a bone called ExampleChildbone
    TempMat.setTranslate(0.0,0.0,1.0);
    LeftToes->setMatrix(TempMat);

    NodeRecPtr LeftToesNode = makeNodeFor(LeftToes);
    LeftFootNode->addChild(LeftToesNode);

    InvBind = LeftToesNode->getToWorld();
    InvBind.invert();
    ExampleSkeleton->pushToJoints(LeftToesNode, InvBind);

    /*================================================================================================*/
    /*                                       Right Hip                                                 */
    RightHip = Transform::create(); //create a joint called RightHip 
    TempMat.setTranslate(-1.0,-1.0,0.0);
    RightHip->setMatrix(TempMat);

    NodeRecPtr RightHipNode = makeNodeFor(RightHip);
    PelvisNode->addChild(RightHipNode);

    InvBind = RightHipNode->getToWorld();
    InvBind.invert();
    ExampleSkeleton->pushToJoints(RightHipNode, InvBind);

    /*================================================================================================*/
    /*                                       Right Knee                                                 */
    RightKnee = Transform::create(); //create a joint called RightKnee 
    TempMat.setTranslate(0.0,-3.0,0.0);
    RightKnee->setMatrix(TempMat);

    NodeRecPtr RightKneeNode = makeNodeFor(RightKnee);
    RightHipNode->addChild(RightKneeNode);

    InvBind = RightKneeNode->getToWorld();
    InvBind.invert();
    ExampleSkeleton->pushToJoints(RightKneeNode, InvBind);

    /*================================================================================================*/
    /*                                       Right Foot                                                 */
    RightFoot = Transform::create(); //create a joint called RightFoot 
    TempMat.setTranslate(0.0,-3.0,0.0);
    RightFoot->setMatrix(TempMat);

    NodeRecPtr RightFootNode = makeNodeFor(RightFoot);
    RightKneeNode->addChild(RightFootNode);

    InvBind = RightFootNode->getToWorld();
    InvBind.invert();
    ExampleSkeleton->pushToJoints(RightFootNode, InvBind);
    
    /*================================================================================================*/
    /*                                       Right Toes                                                 */
    RightToes = Transform::create(); //create a joint called RightToes 
    TempMat.setTranslate(0.0,0.0,1.0);
    RightToes->setMatrix(TempMat);

    NodeRecPtr RightToesNode = makeNodeFor(RightToes);
    RightFootNode->addChild(RightToesNode);

    InvBind = RightToesNode->getToWorld();
    InvBind.invert();
    ExampleSkeleton->pushToJoints(RightToesNode, InvBind);

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

    FieldAnimationUnrecPtr LeftElbowAnimation = FieldAnimation::create();
    LeftElbowAnimation->setAnimator(LeftElbowAnimator);
    LeftElbowAnimation->setInterpolationType(Animator::LINEAR_INTERPOLATION);
    LeftElbowAnimation->setCycling(-1);
	LeftElbowAnimation->setAnimatedField(LeftElbow, std::string("matrix"));

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

    FieldAnimationUnrecPtr RightElbowAnimation = FieldAnimation::create();
    RightElbowAnimation->setAnimator(RightElbowAnimator);
    RightElbowAnimation->setInterpolationType(Animator::LINEAR_INTERPOLATION);
    RightElbowAnimation->setCycling(-1);
	RightElbowAnimation->setAnimatedField(RightElbow, std::string("matrix"));

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

    FieldAnimationUnrecPtr LeftShoulderAnimation = FieldAnimation::create();
    LeftShoulderAnimation->setAnimator(LeftShoulderAnimator);
    LeftShoulderAnimation->setInterpolationType(Animator::LINEAR_INTERPOLATION);
    LeftShoulderAnimation->setCycling(-1);
	LeftShoulderAnimation->setAnimatedField(LeftShoulder, std::string("matrix"));

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

    FieldAnimationUnrecPtr RightShoulderAnimation = FieldAnimation::create();
    RightShoulderAnimation->setAnimator(RightShoulderAnimator);
    RightShoulderAnimation->setInterpolationType(Animator::LINEAR_INTERPOLATION);
    RightShoulderAnimation->setCycling(-1);
	RightShoulderAnimation->setAnimatedField(RightShoulder, std::string("matrix"));

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

    FieldAnimationUnrecPtr LeftHipAnimation = FieldAnimation::create();
    LeftHipAnimation->setAnimator(LeftHipAnimator);
    LeftHipAnimation->setInterpolationType(Animator::LINEAR_INTERPOLATION);
    LeftHipAnimation->setCycling(-1);
	LeftHipAnimation->setAnimatedField(LeftHip, std::string("matrix"));

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


    FieldAnimationUnrecPtr RightHipAnimation = FieldAnimation::create();
    RightHipAnimation->setAnimator(RightHipAnimator);
    RightHipAnimation->setInterpolationType(Animator::LINEAR_INTERPOLATION);
    RightHipAnimation->setCycling(-1);
	RightHipAnimation->setAnimatedField(RightHip, std::string("matrix"));

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

    FieldAnimationUnrecPtr ClavicleAnimation = FieldAnimation::create();
    ClavicleAnimation->setAnimator(ClavicleAnimator);
    ClavicleAnimation->setInterpolationType(Animator::LINEAR_INTERPOLATION);
    ClavicleAnimation->setCycling(-1);
	ClavicleAnimation->setAnimatedField(Clavicle, std::string("matrix"));

    //Skeleton Animation
    TheSkeletonAnimation = AnimationGroup::create();
    //Add the animators we just made to the skeleton animation
    TheSkeletonAnimation->pushToAnimations(LeftElbowAnimation);  //Here we tell the skeleton animation the it should use the animator LeftElbowAnimator to animate the joint LeftElbow
    TheSkeletonAnimation->pushToAnimations(RightElbowAnimation);
    TheSkeletonAnimation->pushToAnimations(LeftShoulderAnimation);
    TheSkeletonAnimation->pushToAnimations(RightShoulderAnimation);
    TheSkeletonAnimation->pushToAnimations(LeftHipAnimation);
    TheSkeletonAnimation->pushToAnimations(RightHipAnimation);
    TheSkeletonAnimation->pushToAnimations(ClavicleAnimation);

    TheSkeletonAnimation->attachUpdateProducer(TutorialWindow->editEventProducer());
    TheSkeletonAnimation->start();
}
