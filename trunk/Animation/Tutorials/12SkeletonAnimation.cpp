// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/Input/OSGWindowUtils.h>

// Input
#include <OpenSG/Input/OSGKeyListener.h>
#include <OpenSG/Input/OSGUpdateListener.h>
#include <OpenSG/Input/OSGWindowAdapter.h>

#include <OpenSG/OSGLineChunk.h>
#include <OpenSG/OSGBlendChunk.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialChunk.h>

//Animation
#include <OpenSG/Animation/OSGBone.h>
#include <OpenSG/Animation/OSGSkeleton.h>
#include <OpenSG/Animation/OSGSkeletonDrawable.h>

#include <OpenSG/Toolbox/OSGRandomPoolManager.h>

// FROM ANIMATION.CPP
#include <OpenSG/OSGTime.h>
#include <OpenSG/Animation/OSGKeyframeSequences.h>
#include <OpenSG/Animation/OSGFieldAnimation.h>
#include <OpenSG/Animation/OSGKeyframeAnimator.h>
#include <OpenSG/Animation/OSGElapsedTimeAnimationAdvancer.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include <OpenSG/Animation/OSGSkeletonAnimation.h>
#include <OpenSG/Animation/OSGSkeleton.h>
#include <OpenSG/Animation/OSGJoint.h>



// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

Time TimeLastIdle;
NodePtr SkeletonNode;
SkeletonAnimationPtr TheSkeletonAnimation;
AnimationAdvancerPtr TheAnimationAdvancer;
bool animationPaused = false;

bool ExitApp = false;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);
void setupAnimation(void);

JointPtr Pelvis,LeftHip,RightHip,LeftKnee,RightKnee,LeftFoot,RightFoot,LeftToes,RightToes, Clavicle, LeftShoulder,RightShoulder,LeftElbow,RightElbow,LeftHand,RightHand,LeftFingers,RightFingers,Head; 
SkeletonPtr ExampleSkeleton;


// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEvent& e)
   {
	   //Exit
       if(e.getKey() == KeyEvent::KEY_Q && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           ExitApp = true;
       }

	   //Toggle animation
	   if(e.getKey() == KeyEvent::KEY_SPACE)
	   {
		   if(animationPaused)
			   animationPaused = false;
		   else
			   animationPaused = true;
	   }

	   //Toggle bind pose
	   if(e.getKey() == KeyEvent::KEY_B)
	   {
		   //Toggle skeleton
		   if(SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore())->getDrawBindPose() == false)
		   {
			   beginEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore()), SkeletonDrawable::DrawBindPoseFieldMask);
				 SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore())->setDrawBindPose(true);
				endEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore()), SkeletonDrawable::DrawBindPoseFieldMask);
		   } 
		   else
		   {
			   beginEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore()), SkeletonDrawable::DrawBindPoseFieldMask);
				 SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore())->setDrawBindPose(false);
				endEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore()), SkeletonDrawable::DrawBindPoseFieldMask);
		   }
	   }

	   //Toggle current pose
	   if(e.getKey() == KeyEvent::KEY_P)
	   {
		   //Toggle skeleton
		   if(SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore())->getDrawPose() == false)
		   {
			   beginEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore()), SkeletonDrawable::DrawPoseFieldMask);
				 SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore())->setDrawPose(true);
				endEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore()), SkeletonDrawable::DrawPoseFieldMask);
		   } 
		   else
		   {
			   beginEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore()), SkeletonDrawable::DrawPoseFieldMask);
				 SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore())->setDrawPose(false);
				endEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNode->getCore()), SkeletonDrawable::DrawPoseFieldMask);
		   }
	   }
   }

   virtual void keyReleased(const KeyEvent& e)
   {
   }

   virtual void keyTyped(const KeyEvent& e)
   {
   }
};

class TutorialWindowListener : public WindowAdapter
{
public:
    virtual void windowClosing(const WindowEvent& e)
    {
        ExitApp = true;
    }

    virtual void windowClosed(const WindowEvent& e)
    {
        ExitApp = true;
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
		if(!animationPaused)
		{
			ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->update(e.getElapsedTime());

			TheSkeletonAnimation->update(TheAnimationAdvancer);
		}
    }
};

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    WindowEventProducerPtr TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

	beginEditCP(TutorialWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);
		TutorialWindowEventProducer->setUseCallbackForDraw(true);
		TutorialWindowEventProducer->setUseCallbackForReshape(true);
	endEditCP(TutorialWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);

    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

	TutorialUpdateListener TheTutorialUpdateListener;
    TutorialWindowEventProducer->addUpdateListener(&TheTutorialUpdateListener);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TutorialWindowEventProducer->addWindowListener(&TheTutorialWindowListener);
    TutorialKeyListener TheKeyListener;
    TutorialWindowEventProducer->addKeyListener(&TheKeyListener);
    TutorialMouseListener TheTutorialMouseListener;
    TutorialMouseMotionListener TheTutorialMouseMotionListener;
    TutorialWindowEventProducer->addMouseListener(&TheTutorialMouseListener);
    TutorialWindowEventProducer->addMouseMotionListener(&TheTutorialMouseMotionListener);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
	
    TutorialWindowEventProducer->openWindow(Pnt2f(0,0),
                                        Vec2f(1280,1024),
                                        "OpenSG 12SkeletonAnimation Window");
										

	//SkeletonDrawer System Material
	LineChunkPtr ExampleLineChunk = LineChunk::create();
	beginEditCP(ExampleLineChunk);
		ExampleLineChunk->setWidth(2.0f);
		ExampleLineChunk->setSmooth(true);
	endEditCP(ExampleLineChunk);

	BlendChunkPtr ExampleBlendChunk = BlendChunk::create();
	beginEditCP(ExampleBlendChunk);
	    ExampleBlendChunk->setSrcFactor(GL_SRC_ALPHA);
	    ExampleBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
	endEditCP(ExampleBlendChunk);

	MaterialChunkPtr ExampleMaterialChunk = MaterialChunk::create();
	beginEditCP(ExampleMaterialChunk);
		ExampleMaterialChunk->setAmbient(Color4f(1.0f,1.0f,1.0f,1.0f));
		ExampleMaterialChunk->setDiffuse(Color4f(0.0f,0.0f,0.0f,1.0f));
		ExampleMaterialChunk->setSpecular(Color4f(0.0f,0.0f,0.0f,1.0f));
	endEditCP(ExampleMaterialChunk);

	ChunkMaterialPtr ExampleMaterial = ChunkMaterial::create();
	beginEditCP(ExampleMaterial, ChunkMaterial::ChunksFieldMask);
		ExampleMaterial->addChunk(ExampleLineChunk);
		ExampleMaterial->addChunk(ExampleMaterialChunk);
		ExampleMaterial->addChunk(ExampleBlendChunk);
	endEditCP(ExampleMaterial, ChunkMaterial::ChunksFieldMask);

	//===========================================Joints==================================================================
	Matrix TempMat;

	/*================================================================================================*/
	/*                                       Left Fingers                                                 */
	LeftFingers = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(1.0,0.0,0.0);
	beginEditCP(LeftFingers, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);
		LeftFingers->setRelativeTransformation(TempMat);
		LeftFingers->setBindRelativeTransformation(TempMat);
	endEditCP(LeftFingers, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);

	/*================================================================================================*/
	/*                                       Right Fingers                                                 */
	RightFingers = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(-1.0,0.0,0.0);
	beginEditCP(RightFingers, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);
		RightFingers->setRelativeTransformation(TempMat);
		RightFingers->setBindRelativeTransformation(TempMat);
	endEditCP(RightFingers, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);
	/*================================================================================================*/
	/*                                       Left Hand                                                 */
	LeftHand = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(2.0,0.0,0.0);
	beginEditCP(LeftHand, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		LeftHand->setRelativeTransformation(TempMat);
		LeftHand->setBindRelativeTransformation(TempMat);
		LeftHand->getChildJoints().push_back(LeftFingers);
	endEditCP(LeftHand, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Right Hand                                                 */
	RightHand = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(-2.0,0.0,0.0);
	beginEditCP(RightHand, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		RightHand->setRelativeTransformation(TempMat);
		RightHand->setBindRelativeTransformation(TempMat);
		RightHand->getChildJoints().push_back(RightFingers);
	endEditCP(RightHand, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
	/*================================================================================================*/
	/*                                       Left Elbow                                                 */
	LeftElbow = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(2.0,0.0,0.0);
	beginEditCP(LeftElbow, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		LeftElbow->setRelativeTransformation(TempMat);
		LeftElbow->setBindRelativeTransformation(TempMat);
		LeftElbow->getChildJoints().push_back(LeftHand);
	endEditCP(LeftElbow, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Right Elbow                                                 */
	RightElbow = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(-2.0,0.0,0.0);
	beginEditCP(RightElbow, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		RightElbow->setRelativeTransformation(TempMat);
		RightElbow->setBindRelativeTransformation(TempMat);
		RightElbow->getChildJoints().push_back(RightHand);
	endEditCP(RightElbow, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
	/*================================================================================================*/
	/*                                       Left Shoulder                                                 */
	LeftShoulder = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(1.0,-0.5,0.0);
	beginEditCP(LeftShoulder, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		LeftShoulder->setRelativeTransformation(TempMat);
		LeftShoulder->setBindRelativeTransformation(TempMat);
		LeftShoulder->getChildJoints().push_back(LeftElbow);
	endEditCP(LeftShoulder, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Right Shoulder                                                 */
	RightShoulder = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(-1.0,-0.5,0.0);
	beginEditCP(RightShoulder, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		RightShoulder->setRelativeTransformation(TempMat);
		RightShoulder->setBindRelativeTransformation(TempMat);
		RightShoulder->getChildJoints().push_back(RightElbow);
	endEditCP(RightShoulder, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Head                                                 */
	Head = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(0.0,1.0,0.0);
	beginEditCP(Head, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);
		Head->setRelativeTransformation(TempMat);
		Head->setBindRelativeTransformation(TempMat);
	endEditCP(Head, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);

	/*================================================================================================*/
	/*                                       Clavicle                                                   */
	Clavicle = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(0.0,5.0,0.0);
	beginEditCP(Clavicle, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		Clavicle->setRelativeTransformation(TempMat);
		Clavicle->setBindRelativeTransformation(TempMat);
		Clavicle->getChildJoints().push_back(LeftShoulder);
		Clavicle->getChildJoints().push_back(RightShoulder);
		Clavicle->getChildJoints().push_back(Head);
	endEditCP(Clavicle, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Left Toes                                                 */
	LeftToes = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(0.0,0.0,1.0);
	beginEditCP(LeftToes, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);
		LeftToes->setRelativeTransformation(TempMat);
		LeftToes->setBindRelativeTransformation(TempMat);
	endEditCP(LeftToes, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);

	/*================================================================================================*/
	/*                                       Right Toes                                                 */
	RightToes = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(0.0,0.0,1.0);
	beginEditCP(RightToes, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);
		RightToes->setRelativeTransformation(TempMat);
		RightToes->setBindRelativeTransformation(TempMat);
	endEditCP(RightToes, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);
	/*================================================================================================*/
	/*                                       Left Foot                                                 */
	LeftFoot = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(0.0,-3.0,0.0);
	beginEditCP(LeftFoot, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		LeftFoot->setRelativeTransformation(TempMat);
		LeftFoot->setBindRelativeTransformation(TempMat);
		LeftFoot->getChildJoints().push_back(LeftToes);
	endEditCP(LeftFoot, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Right Foot                                                 */
	RightFoot = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(0.0,-3.0,0.0);
	beginEditCP(RightFoot, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		RightFoot->setRelativeTransformation(TempMat);
		RightFoot->setBindRelativeTransformation(TempMat);
		RightFoot->getChildJoints().push_back(RightToes);
	endEditCP(RightFoot, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
	/*================================================================================================*/
	/*                                       Left Knee                                                 */
	LeftKnee = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(0.0,-3.0,0.0);
	beginEditCP(LeftKnee, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		LeftKnee->setRelativeTransformation(TempMat);
		LeftKnee->setBindRelativeTransformation(TempMat);
		LeftKnee->getChildJoints().push_back(LeftFoot);
	endEditCP(LeftKnee, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Right Knee                                                 */
	RightKnee = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(0.0,-3.0,0.0);
	beginEditCP(RightKnee, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		RightKnee->setRelativeTransformation(TempMat);
		RightKnee->setBindRelativeTransformation(TempMat);
		RightKnee->getChildJoints().push_back(RightFoot);
	endEditCP(RightKnee, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Left Hip                                                 */
	LeftHip = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(1.0,-1.0,0.0);
	beginEditCP(LeftHip, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		LeftHip->setRelativeTransformation(TempMat);
		LeftHip->setBindRelativeTransformation(TempMat);
		LeftHip->getChildJoints().push_back(LeftKnee);
	endEditCP(LeftHip, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Right Hip                                                 */
	RightHip = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(-1.0,-1.0,0.0);
	beginEditCP(RightHip, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		RightHip->setRelativeTransformation(TempMat);
		RightHip->setBindRelativeTransformation(TempMat);
		RightHip->getChildJoints().push_back(RightKnee);
	endEditCP(RightHip, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Pelvis                                                   */
	Pelvis = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(0.0,7.0,0.0);
	beginEditCP(Pelvis, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		Pelvis->setRelativeTransformation(TempMat);
		Pelvis->setBindRelativeTransformation(TempMat);
		Pelvis->getChildJoints().push_back(LeftHip);
		Pelvis->getChildJoints().push_back(RightHip);
		Pelvis->getChildJoints().push_back(Clavicle);
	endEditCP(Pelvis, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
	


    //Skeleton
    ExampleSkeleton = Skeleton::create();
	beginEditCP(ExampleSkeleton, Skeleton::RootJointsFieldMask);
		ExampleSkeleton->getRootJoints().push_back(Pelvis);
	endEditCP(ExampleSkeleton, Skeleton::RootJointsFieldMask);

    //SkeletonDrawer
    SkeletonDrawablePtr ExampleSkeletonDrawable = SkeletonDrawable::create();
    beginEditCP(ExampleSkeletonDrawable, SkeletonDrawable::SkeletonFieldMask | SkeletonDrawable::MaterialFieldMask | SkeletonDrawable::DrawBindPoseFieldMask | SkeletonDrawable::BindPoseColorFieldMask | SkeletonDrawable::DrawPoseFieldMask | SkeletonDrawable::PoseColorFieldMask);
		ExampleSkeletonDrawable->setSkeleton(ExampleSkeleton);
		ExampleSkeletonDrawable->setMaterial(ExampleMaterial);
		ExampleSkeletonDrawable->setDrawBindPose(false);
		ExampleSkeletonDrawable->setBindPoseColor(Color4f(0.0, 1.0, 0.0, 1.0));
		ExampleSkeletonDrawable->setDrawPose(true);
		ExampleSkeletonDrawable->setPoseColor(Color4f(0.0, 0.0, 1.0, 1.0));
    endEditCP(ExampleSkeletonDrawable, SkeletonDrawable::SkeletonFieldMask | SkeletonDrawable::MaterialFieldMask | SkeletonDrawable::DrawBindPoseFieldMask | SkeletonDrawable::BindPoseColorFieldMask | SkeletonDrawable::DrawPoseFieldMask | SkeletonDrawable::PoseColorFieldMask);
	
	//Skeleton Node
	SkeletonNode = Node::create();
    beginEditCP(SkeletonNode, Node::CoreFieldMask);
        SkeletonNode->setCore(ExampleSkeletonDrawable);
    endEditCP(SkeletonNode, Node::CoreFieldMask);
	
   //Animation Advancer
   TheAnimationAdvancer = ElapsedTimeAnimationAdvancer::create();
   beginEditCP(TheAnimationAdvancer);
   ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->setStartTime( 0.0 );
   beginEditCP(TheAnimationAdvancer);

	//Create scene    
    NodePtr scene = Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(Group::create());
        scene->addChild(SkeletonNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    mgr->setRoot(scene);

	//Setup the Animation
	setupAnimation();
	


    // Show the whole Scene
    mgr->showAll();


    while(!ExitApp)
    {
        TutorialWindowEventProducer->update();
        TutorialWindowEventProducer->draw();
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
	Matrix TempMat;

	//Left Elbow
	KeyframeTransformationsSequencePtr LeftElbowKeyframes = KeyframeTransformationsSequence44f::create();

	TempMat.setTransform(Vec3f(2.0,0.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0));
	LeftElbowKeyframes->addKeyframe(TempMat,0.0f);
	TempMat.setTransform(Vec3f(2.0,0.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),1.57));
	LeftElbowKeyframes->addKeyframe(TempMat,3.0f);
	TempMat.setTransform(Vec3f(2.0,0.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0));
	LeftElbowKeyframes->addKeyframe(TempMat,6.0f);
   
	//Left Elbow Animator
    KeyframeAnimatorPtr LeftElbowAnimator = KeyframeAnimator::create();
    beginEditCP(LeftElbowAnimator);
       LeftElbowAnimator->setKeyframeSequence(LeftElbowKeyframes);
    endEditCP(LeftElbowAnimator);

	//Right Elbow
	KeyframeTransformationsSequencePtr RightElbowKeyframes = KeyframeTransformationsSequence44f::create();

	TempMat.setTransform(Vec3f(-2.0,0.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0));
	RightElbowKeyframes->addKeyframe(TempMat,0.0f);
	TempMat.setTransform(Vec3f(-2.0,0.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),-1.57));
	RightElbowKeyframes->addKeyframe(TempMat,3.0f);
	TempMat.setTransform(Vec3f(-2.0,0.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0));
	RightElbowKeyframes->addKeyframe(TempMat,6.0f);
   
	//Right Elbow Animator
    KeyframeAnimatorPtr RightElbowAnimator = KeyframeAnimator::create();
    beginEditCP(RightElbowAnimator);
       RightElbowAnimator->setKeyframeSequence(RightElbowKeyframes);
    endEditCP(RightElbowAnimator);
	
	//Left Shoulder
	KeyframeTransformationsSequencePtr LeftShoulderKeyframes = KeyframeTransformationsSequence44f::create();

	TempMat.setTransform(Vec3f(1.0,-0.5,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0));
	LeftShoulderKeyframes->addKeyframe(TempMat,0.0f);
	TempMat.setTransform(Vec3f(1.0,-0.5,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.4));
	LeftShoulderKeyframes->addKeyframe(TempMat,3.0f);
	TempMat.setTransform(Vec3f(1.0,-0.5,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0));
	LeftShoulderKeyframes->addKeyframe(TempMat,6.0f);
   
	//Left Shoulder Animator
    KeyframeAnimatorPtr LeftShoulderAnimator = KeyframeAnimator::create();
    beginEditCP(LeftShoulderAnimator);
       LeftShoulderAnimator->setKeyframeSequence(LeftShoulderKeyframes);
    endEditCP(LeftShoulderAnimator);
	
	//Right Shoulder
	KeyframeTransformationsSequencePtr RightShoulderKeyframes = KeyframeTransformationsSequence44f::create();

	TempMat.setTransform(Vec3f(-1.0,-0.5,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0));
	RightShoulderKeyframes->addKeyframe(TempMat,0.0f);
	TempMat.setTransform(Vec3f(-1.0,-0.5,0.0),Quaternion(Vec3f(0.0,0.0,1.0),-0.4));
	RightShoulderKeyframes->addKeyframe(TempMat,3.0f);
	TempMat.setTransform(Vec3f(-1.0,-0.5,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0));
	RightShoulderKeyframes->addKeyframe(TempMat,6.0f);
   
	//Right Shoulder Animator
    KeyframeAnimatorPtr RightShoulderAnimator = KeyframeAnimator::create();
    beginEditCP(RightShoulderAnimator);
       RightShoulderAnimator->setKeyframeSequence(RightShoulderKeyframes);
    endEditCP(RightShoulderAnimator);
	
	//Left Hip
	KeyframeTransformationsSequencePtr LeftHipKeyframes = KeyframeTransformationsSequence44f::create();

	TempMat.setTransform(Vec3f(1.0,-1.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0));
	LeftHipKeyframes->addKeyframe(TempMat,0.0f);
	TempMat.setTransform(Vec3f(1.0,-1.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.4));
	LeftHipKeyframes->addKeyframe(TempMat,3.0f);
	TempMat.setTransform(Vec3f(1.0,-1.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0));
	LeftHipKeyframes->addKeyframe(TempMat,6.0f);
   
	//Left Hip Animator
    KeyframeAnimatorPtr LeftHipAnimator = KeyframeAnimator::create();
    beginEditCP(LeftHipAnimator);
       LeftHipAnimator->setKeyframeSequence(LeftHipKeyframes);
    endEditCP(LeftHipAnimator);

	//Right Hip
	KeyframeTransformationsSequencePtr RightHipKeyframes = KeyframeTransformationsSequence44f::create();

	TempMat.setTransform(Vec3f(-1.0,-1.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0));
	RightHipKeyframes->addKeyframe(TempMat,0.0f);
	TempMat.setTransform(Vec3f(-1.0,-1.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),-0.4));
	RightHipKeyframes->addKeyframe(TempMat,3.0f);
	TempMat.setTransform(Vec3f(-1.0,-1.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0));
	RightHipKeyframes->addKeyframe(TempMat,6.0f);
   
	//Right Hip Animator
    KeyframeAnimatorPtr RightHipAnimator = KeyframeAnimator::create();
    beginEditCP(RightHipAnimator);
       RightHipAnimator->setKeyframeSequence(RightHipKeyframes);
    endEditCP(RightHipAnimator);
	

	//Clavicle
	KeyframeTransformationsSequencePtr ClavicleKeyframes = KeyframeTransformationsSequence44f::create();

	TempMat.setTransform(Vec3f(0.0,5.0,0.0));
	ClavicleKeyframes->addKeyframe(TempMat,0.0f);
	TempMat.setTransform(Vec3f(0.0,3.0,0.0));
	ClavicleKeyframes->addKeyframe(TempMat,2.0f);
	TempMat.setTransform(Vec3f(0.0,3.0,0.0));
	ClavicleKeyframes->addKeyframe(TempMat,4.0f);
	TempMat.setTransform(Vec3f(0.0,5.0,0.0));
	ClavicleKeyframes->addKeyframe(TempMat,6.0f);
   
	//Clavicle Animator
    KeyframeAnimatorPtr ClavicleAnimator = KeyframeAnimator::create();
    beginEditCP(ClavicleAnimator);
       ClavicleAnimator->setKeyframeSequence(ClavicleKeyframes);
    endEditCP(ClavicleAnimator);

	//Skeleton Animation
   TheSkeletonAnimation = SkeletonAnimation::create();
   beginEditCP(TheSkeletonAnimation);
		TheSkeletonAnimation->addTransformationAnimator(LeftElbowAnimator, LeftElbow);
		TheSkeletonAnimation->addTransformationAnimator(RightElbowAnimator, RightElbow);
		TheSkeletonAnimation->addTransformationAnimator(LeftShoulderAnimator, LeftShoulder);
		TheSkeletonAnimation->addTransformationAnimator(RightShoulderAnimator, RightShoulder);
		TheSkeletonAnimation->addTransformationAnimator(LeftHipAnimator, LeftHip);
		TheSkeletonAnimation->addTransformationAnimator(RightHipAnimator, RightHip);
		TheSkeletonAnimation->addTransformationAnimator(ClavicleAnimator, Clavicle);
		TheSkeletonAnimation->setSkeleton(ExampleSkeleton);
   endEditCP(TheSkeletonAnimation);
}
