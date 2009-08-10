// 
// OpenSGToolbox Tutorial: 13MeshBlending 
//
// Creates a skeleton and a "skin" geometry and binds them together
// using a skeleton blended geometry.
//


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

#include <OpenSG/OSGLineChunk.h>
#include <OpenSG/OSGBlendChunk.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialChunk.h>

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
#include <OpenSG/Animation/OSGSkeletonDrawable.h>

#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/Animation/OSGSkeletonBlendedGeometry.h>

#include <OpenSG/Toolbox/OSGFCFileHandler.h>


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;

Time TimeLastIdle;
NodePtr SkeletonNode;
NodePtr UnboundGeometry;
NodePtr MeshNode;
SkeletonAnimationPtr TheSkeletonAnimation;
AnimationAdvancerPtr TheAnimationAdvancer;
bool animationPaused = false;

JointPtr Pelvis,LeftHip,RightHip,LeftKnee,RightKnee,LeftFoot,RightFoot,LeftToes,RightToes, Clavicle, LeftShoulder,RightShoulder,LeftElbow,RightElbow,LeftHand,RightHand,LeftFingers,RightFingers,Head; 
SkeletonPtr ExampleSkeleton;

// The pointer to the transformation
TransformPtr trans;

// The pointer to the geometry core
GeometryPtr geo;





// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);
void setupAnimation(void);

// Create a class to allow for the use of the keyboard shortcuts 
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEvent& e)
   {
	   //Exit
       if(e.getKey() == KeyEvent::KEY_Q && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
            TutorialWindowEventProducer->closeWindow();
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
		   if(e.getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
		   {
			   //Toggle mesh
			   if(UnboundGeometry->getTravMask() == 0)
			   {
				   beginEditCP(UnboundGeometry, Node::TravMaskFieldMask);
						UnboundGeometry->setTravMask(1);
					endEditCP(UnboundGeometry, Node::TravMaskFieldMask);
			   } 
			   else
			   {
				   beginEditCP(UnboundGeometry, Node::TravMaskFieldMask);
						UnboundGeometry->setTravMask(0);
					endEditCP(UnboundGeometry, Node::TravMaskFieldMask);
			   }
		   }
		   else
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
	   }

	   //Toggle current pose
	   if(e.getKey() == KeyEvent::KEY_P)
	   {
		   if(e.getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
		   {
			   //Toggle mesh
			   if(MeshNode->getTravMask() == 0)
			   {
				   beginEditCP(MeshNode, Node::TravMaskFieldMask);
						MeshNode->setTravMask(1);
					endEditCP(MeshNode, Node::TravMaskFieldMask);
			   } 
			   else
			   {
				   beginEditCP(MeshNode, Node::TravMaskFieldMask);
						MeshNode->setTravMask(0);
					endEditCP(MeshNode, Node::TravMaskFieldMask);
			   }
		   }
		   else
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
    TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

	TutorialUpdateListener TheTutorialUpdateListener;
    TutorialWindowEventProducer->addUpdateListener(&TheTutorialUpdateListener);

    //Add Window Listener
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
	
	//Print key command info
	std::cout << "\n\nKEY COMMANDS:" << std::endl;
	std::cout << "space   Play/Pause the animation" << std::endl;
	std::cout << "B       Show/Hide the bind pose skeleton" << std::endl;
	std::cout << "SHIFT-B Show/Hide the bind pose mesh" << std::endl;
	std::cout << "P       Show/Hide the current pose skeleton" << std::endl;
	std::cout << "SHIFT-P Show/Hide the current pose mesh" << std::endl;
	std::cout << "CTRL-Q  Exit\n\n" << std::endl;
										

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
	LeftFingers = Joint::create(); //create a joint called LeftFingers 
	TempMat.setTranslate(1.0,0.0,0.0);
	beginEditCP(LeftFingers, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);
		LeftFingers->setRelativeTransformation(TempMat);
		LeftFingers->setBindRelativeTransformation(TempMat);
	endEditCP(LeftFingers, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);

	/*================================================================================================*/
	/*                                       Right Fingers                                                 */
	RightFingers = Joint::create(); //create a joint called RightFingers 
	TempMat.setTranslate(-1.0,0.0,0.0);
	beginEditCP(RightFingers, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);
		RightFingers->setRelativeTransformation(TempMat);
		RightFingers->setBindRelativeTransformation(TempMat);
	endEditCP(RightFingers, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);
	/*================================================================================================*/
	/*                                       Left Hand                                                 */
	LeftHand = Joint::create(); //create a joint called LeftHand 
	TempMat.setTranslate(2.0,0.0,0.0);
	beginEditCP(LeftHand, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		LeftHand->setRelativeTransformation(TempMat);
		LeftHand->setBindRelativeTransformation(TempMat);
		LeftHand->getChildJoints().push_back(LeftFingers);
	endEditCP(LeftHand, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Right Hand                                                 */
	RightHand = Joint::create(); //create a joint called RightHand 
	TempMat.setTranslate(-2.0,0.0,0.0);
	beginEditCP(RightHand, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		RightHand->setRelativeTransformation(TempMat);
		RightHand->setBindRelativeTransformation(TempMat);
		RightHand->getChildJoints().push_back(RightFingers);
	endEditCP(RightHand, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
	/*================================================================================================*/
	/*                                       Left Elbow                                                 */
	LeftElbow = Joint::create(); //create a joint called LeftElbow 
	TempMat.setTranslate(2.0,0.0,0.0);
	beginEditCP(LeftElbow, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		LeftElbow->setRelativeTransformation(TempMat);
		LeftElbow->setBindRelativeTransformation(TempMat);
		LeftElbow->getChildJoints().push_back(LeftHand);
	endEditCP(LeftElbow, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Right Elbow                                                 */
	RightElbow = Joint::create(); //create a joint called RightElbow 
	TempMat.setTranslate(-2.0,0.0,0.0);
	beginEditCP(RightElbow, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		RightElbow->setRelativeTransformation(TempMat);
		RightElbow->setBindRelativeTransformation(TempMat);
		RightElbow->getChildJoints().push_back(RightHand);
	endEditCP(RightElbow, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
	/*================================================================================================*/
	/*                                       Left Shoulder                                                 */
	LeftShoulder = Joint::create(); //create a joint called LeftShoulder 
	TempMat.setTranslate(1.0,-0.5,0.0);
	beginEditCP(LeftShoulder, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		LeftShoulder->setRelativeTransformation(TempMat);
		LeftShoulder->setBindRelativeTransformation(TempMat);
		LeftShoulder->getChildJoints().push_back(LeftElbow);
	endEditCP(LeftShoulder, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Right Shoulder                                                 */
	RightShoulder = Joint::create(); //create a joint called RightShoulder 
	TempMat.setTranslate(-1.0,-0.5,0.0);
	beginEditCP(RightShoulder, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		RightShoulder->setRelativeTransformation(TempMat);
		RightShoulder->setBindRelativeTransformation(TempMat);
		RightShoulder->getChildJoints().push_back(RightElbow);
	endEditCP(RightShoulder, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Head                                                 */
	Head = Joint::create(); //create a joint called Head 
	TempMat.setTranslate(0.0,1.0,0.0);
	beginEditCP(Head, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);
		Head->setRelativeTransformation(TempMat);
		Head->setBindRelativeTransformation(TempMat);
	endEditCP(Head, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);

	/*================================================================================================*/
	/*                                       Clavicle                                                   */
	Clavicle = Joint::create(); //create a joint called Clavicle 
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
	RightToes = Joint::create(); //create a joint called RightToes 
	TempMat.setTranslate(0.0,0.0,1.0);
	beginEditCP(RightToes, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);
		RightToes->setRelativeTransformation(TempMat);
		RightToes->setBindRelativeTransformation(TempMat);
	endEditCP(RightToes, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);
	/*================================================================================================*/
	/*                                       Left Foot                                                 */
	LeftFoot = Joint::create(); //create a joint called LeftFoot 
	TempMat.setTranslate(0.0,-3.0,0.0);
	beginEditCP(LeftFoot, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		LeftFoot->setRelativeTransformation(TempMat);
		LeftFoot->setBindRelativeTransformation(TempMat);
		LeftFoot->getChildJoints().push_back(LeftToes);
	endEditCP(LeftFoot, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Right Foot                                                 */
	RightFoot = Joint::create(); //create a joint called RightFoot 
	TempMat.setTranslate(0.0,-3.0,0.0);
	beginEditCP(RightFoot, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		RightFoot->setRelativeTransformation(TempMat);
		RightFoot->setBindRelativeTransformation(TempMat);
		RightFoot->getChildJoints().push_back(RightToes);
	endEditCP(RightFoot, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
	/*================================================================================================*/
	/*                                       Left Knee                                                 */
	LeftKnee = Joint::create(); //create a joint called LeftKnee 
	TempMat.setTranslate(0.0,-3.0,0.0);
	beginEditCP(LeftKnee, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		LeftKnee->setRelativeTransformation(TempMat);
		LeftKnee->setBindRelativeTransformation(TempMat);
		LeftKnee->getChildJoints().push_back(LeftFoot);
	endEditCP(LeftKnee, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Right Knee                                                 */
	RightKnee = Joint::create(); //create a joint called RightKnee 
	TempMat.setTranslate(0.0,-3.0,0.0);
	beginEditCP(RightKnee, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		RightKnee->setRelativeTransformation(TempMat);
		RightKnee->setBindRelativeTransformation(TempMat);
		RightKnee->getChildJoints().push_back(RightFoot);
	endEditCP(RightKnee, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Left Hip                                                 */
	LeftHip = Joint::create(); //create a joint called LeftHip 
	TempMat.setTranslate(1.0,-1.0,0.0);
	beginEditCP(LeftHip, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		LeftHip->setRelativeTransformation(TempMat);
		LeftHip->setBindRelativeTransformation(TempMat);
		LeftHip->getChildJoints().push_back(LeftKnee);
	endEditCP(LeftHip, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Right Hip                                                 */
	RightHip = Joint::create(); //create a joint called RightHip 
	TempMat.setTranslate(-1.0,-1.0,0.0);
	beginEditCP(RightHip, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		RightHip->setRelativeTransformation(TempMat);
		RightHip->setBindRelativeTransformation(TempMat);
		RightHip->getChildJoints().push_back(RightKnee);
	endEditCP(RightHip, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Pelvis                                                   */
	Pelvis = Joint::create(); //create a joint called Pelvis 
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
	endEditCP(ExampleSkeleton, Skeleton::RootJointsFieldMask);  //Set Pelvis as skeleton's root joint


	//Create a geometry to attach to the skeleton (i.e. skin)
	GeoPTypesPtr type = GeoPTypesUI8::create();        
    beginEditCP(type, GeoPTypesUI8::GeoPropDataFieldMask);
    {
        type->addValue(GL_QUADS);
    }
    endEditCP  (type, GeoPTypesUI8::GeoPropDataFieldMask);

	GeoPLengthsPtr lens = GeoPLengthsUI32::create();    
    beginEditCP(lens, GeoPLengthsUI32::GeoPropDataFieldMask);
    {
        lens->addValue(72);
    }
    endEditCP  (lens, GeoPLengthsUI32::GeoPropDataFieldMask);
	 GeoPositions3fPtr pnts = GeoPositions3f::create();
    beginEditCP(pnts, GeoPositions3f::GeoPropDataFieldMask);
    {
		// the points of the Quads

		//Back
        pnts->addValue(Pnt3f(-0.5,  6.0,  0));
        pnts->addValue(Pnt3f( 0.5,  6.0,  0));
        pnts->addValue(Pnt3f( 0.5,  12.0,  0));
        pnts->addValue(Pnt3f(-0.5,  12.0,  0));

		//Head
        pnts->addValue(Pnt3f(-0.5,  12,  0));
        pnts->addValue(Pnt3f( 0.5,  12,  0));
        pnts->addValue(Pnt3f( 0.5,  13,  0));
        pnts->addValue(Pnt3f(-0.5,  13,  0));

		//Left Shoulder
		pnts->addValue(Pnt3f(0.0,  11.5,  0));
		pnts->addValue(Pnt3f(0.0,  12.5,  0));
		pnts->addValue(Pnt3f(1.0,  12.0,  0));
		pnts->addValue(Pnt3f(1.0,  11.0,  0));

		//Left Humerus
		pnts->addValue(Pnt3f(1.0,  11.0,  0));
		pnts->addValue(Pnt3f(1.0,  12.0,  0));
		pnts->addValue(Pnt3f(3.0,  12.0,  0));
		pnts->addValue(Pnt3f(3.0,  11.0,  0));

		//Left Radius
		pnts->addValue(Pnt3f(3.0,  11.0,  0));
		pnts->addValue(Pnt3f(3.0,  12.0,  0));
		pnts->addValue(Pnt3f(5.0,  12.0,  0));
		pnts->addValue(Pnt3f(5.0,  11.0,  0));

		//Left Hand
		pnts->addValue(Pnt3f(5.0,  11.0,  0));
		pnts->addValue(Pnt3f(5.0,  12.0,  0));
		pnts->addValue(Pnt3f(6.0,  12.0,  0));
		pnts->addValue(Pnt3f(6.0,  11.0,  0));

		//Right Shoulder
		pnts->addValue(Pnt3f(0.0,  11.5,  0));
		pnts->addValue(Pnt3f(0.0,  12.5,  0));
		pnts->addValue(Pnt3f(-1.0,  12.0,  0));
		pnts->addValue(Pnt3f(-1.0,  11.0,  0));

		//Right Humerus
		pnts->addValue(Pnt3f(-1.0,  11.0,  0));
		pnts->addValue(Pnt3f(-1.0,  12.0,  0));
		pnts->addValue(Pnt3f(-3.0,  12.0,  0));
		pnts->addValue(Pnt3f(-3.0,  11.0,  0));

		//Right Radius
		pnts->addValue(Pnt3f(-3.0,  11.0,  0));
		pnts->addValue(Pnt3f(-3.0,  12.0,  0));
		pnts->addValue(Pnt3f(-5.0,  12.0,  0));
		pnts->addValue(Pnt3f(-5.0,  11.0,  0));

		//Right Hand
		pnts->addValue(Pnt3f(-5.0,  11.0,  0));
		pnts->addValue(Pnt3f(-5.0,  12.0,  0));
		pnts->addValue(Pnt3f(-6.0,  12.0,  0));
		pnts->addValue(Pnt3f(-6.0,  11.0,  0));

		//Left Hip
		pnts->addValue(Pnt3f(0.0, 6.5,  0));
		pnts->addValue(Pnt3f(0.5, 7.5,  0));
		pnts->addValue(Pnt3f( 1.5,  6.0,  0));
		pnts->addValue(Pnt3f(0.5,  6.0,  0));

		//Left Femur
		pnts->addValue(Pnt3f(0.5,  6.0,  0));
		pnts->addValue(Pnt3f( 1.5,  6.0,  0));
		pnts->addValue(Pnt3f( 1.5,  3.0,  0));
		pnts->addValue(Pnt3f(0.5,  3.0,  0));

		//Left Tibia
		pnts->addValue(Pnt3f(0.5,  3.0,  0));
		pnts->addValue(Pnt3f( 1.5,  3.0,  0));
		pnts->addValue(Pnt3f( 1.5,  0.0,  0));
		pnts->addValue(Pnt3f(0.5,  0.0,  0));
		
		//Left Foot
		pnts->addValue(Pnt3f(0.5,  0.0,  0));
		pnts->addValue(Pnt3f( 1.5,  0.0,  0));
		pnts->addValue(Pnt3f( 1.5,  0.0,  1.0));
		pnts->addValue(Pnt3f(0.5,  0.0,  1.0));
		

		//Right Hip
		pnts->addValue(Pnt3f(0.0, 6.5,  0));
		pnts->addValue(Pnt3f(-0.5, 7.5,  0));
		pnts->addValue(Pnt3f( -1.5,  6.0,  0));
		pnts->addValue(Pnt3f(-0.5,  6.0,  0));

		//Right Femur
		pnts->addValue(Pnt3f(-0.5,  6.0,  0));
		pnts->addValue(Pnt3f( -1.5,  6.0,  0));
		pnts->addValue(Pnt3f( -1.5,  3.0,  0));
		pnts->addValue(Pnt3f(-0.5,  3.0,  0));

		//Right Tibia
		pnts->addValue(Pnt3f(-0.5,  3.0,  0));
		pnts->addValue(Pnt3f( -1.5,  3.0,  0));
		pnts->addValue(Pnt3f( -1.5,  0.0,  0));
		pnts->addValue(Pnt3f(-0.5,  0.0,  0));
		
		//Right Foot
		pnts->addValue(Pnt3f(-0.5,  0.0,  0));
		pnts->addValue(Pnt3f( -1.5,  0.0,  0));
		pnts->addValue(Pnt3f( -1.5,  0.0,  1.0));
		pnts->addValue(Pnt3f(-0.5,  0.0,  1.0));

    }
    endEditCP  (pnts, GeoPositions3f::GeoPropDataFieldMask);
    
    //Normals
	 GeoNormals3fPtr norms = GeoNormals3f::create();
	 geo=Geometry::create();
    beginEditCP(norms, GeoNormals3f::GeoPropDataFieldMask);
        norms->addValue(Vec3f( 0.0,0.0,1.0));
        norms->addValue(Vec3f( 0.0,0.0,1.0));
        norms->addValue(Vec3f( 0.0,0.0,1.0));
        norms->addValue(Vec3f( 0.0,0.0,1.0));

        norms->addValue(Vec3f( 0.0,0.0,1.0));
        norms->addValue(Vec3f( 0.0,0.0,1.0));
        norms->addValue(Vec3f( 0.0,0.0,1.0));
        norms->addValue(Vec3f( 0.0,0.0,1.0));

		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		//Left Hip
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		//Left Femur
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		//Left Tibia
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		//Left Foot
		norms->addValue(Vec3f( 0.0,1.0,0.0));
		norms->addValue(Vec3f( 0.0,1.0,0.0));
		norms->addValue(Vec3f( 0.0,1.0,0.0));
		norms->addValue(Vec3f( 0.0,1.0,0.0));

		//Right Hip
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		//Right Femur
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		//Right Tibia
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		//Right Foot
		norms->addValue(Vec3f( 0.0,1.0,0.0));
		norms->addValue(Vec3f( 0.0,1.0,0.0));
		norms->addValue(Vec3f( 0.0,1.0,0.0));
		norms->addValue(Vec3f( 0.0,1.0,0.0));

		

    endEditCP(norms, GeoNormals3f::GeoPropDataFieldMask);


	 //Tell the geometry (geo) to use the points and normals we just defined
    beginEditCP(geo, Geometry::TypesFieldMask     |
                     Geometry::LengthsFieldMask   |
                     Geometry::PositionsFieldMask |
                     Geometry::NormalsFieldMask |
                     Geometry::MaterialFieldMask  );
    {
        geo->setTypes    (type);
        geo->setLengths  (lens);
        geo->setPositions(pnts);
        geo->setNormals(norms);

        // assign a material to the geometry to make it visible. The details
        // of materials are defined later.
        geo->setMaterial(getDefaultMaterial());   
    }
    endEditCP  (geo, Geometry::TypesFieldMask     |
                     Geometry::LengthsFieldMask   |
                     Geometry::PositionsFieldMask |
                     Geometry::NormalsFieldMask |
                     Geometry::MaterialFieldMask  );

	//Create unbound geometry node (for displaying mesh in its bind pose)
	UnboundGeometry = Node::create();
	beginEditCP(UnboundGeometry, Node::CoreFieldMask | Node::TravMaskFieldMask);
        UnboundGeometry->setCore(geo);
		UnboundGeometry->setTravMask(0);  //By default, we won't show the mesh's bind pose
    endEditCP  (UnboundGeometry, Node::CoreFieldMask | Node::TravMaskFieldMask);
   



    //SkeletonDrawer
    SkeletonDrawablePtr ExampleSkeletonDrawable = SkeletonDrawable::create();
    beginEditCP(ExampleSkeletonDrawable, SkeletonDrawable::SkeletonFieldMask | SkeletonDrawable::MaterialFieldMask | SkeletonDrawable::DrawBindPoseFieldMask | SkeletonDrawable::BindPoseColorFieldMask | SkeletonDrawable::DrawPoseFieldMask | SkeletonDrawable::PoseColorFieldMask);
		ExampleSkeletonDrawable->setSkeleton(ExampleSkeleton);
		ExampleSkeletonDrawable->setMaterial(ExampleMaterial);
		ExampleSkeletonDrawable->setDrawBindPose(false);  //By default, we don't draw the skeleton's bind pose
		ExampleSkeletonDrawable->setBindPoseColor(Color4f(0.0, 1.0, 0.0, 1.0));  //When drawn, the skeleton's bind pose renders green
		ExampleSkeletonDrawable->setDrawPose(true);  //By default, we do draw the skeleton's current pose
		ExampleSkeletonDrawable->setPoseColor(Color4f(0.0, 0.0, 1.0, 1.0));  //The skeleton's current pose renders blue
    endEditCP(ExampleSkeletonDrawable, SkeletonDrawable::SkeletonFieldMask | SkeletonDrawable::MaterialFieldMask | SkeletonDrawable::DrawBindPoseFieldMask | SkeletonDrawable::BindPoseColorFieldMask | SkeletonDrawable::DrawPoseFieldMask | SkeletonDrawable::PoseColorFieldMask);
	
	//Skeleton Node
	SkeletonNode = Node::create();
    beginEditCP(SkeletonNode, Node::CoreFieldMask);
        SkeletonNode->setCore(ExampleSkeletonDrawable);
    endEditCP(SkeletonNode, Node::CoreFieldMask);




	// Skeleton Blended Geometry
	// Here we are attaching the "skin" to the skeleton so that when the skeleton is animated, the skin moves with it
	SkeletonBlendedGeometryPtr TheNewSkeletonGeometry = SkeletonBlendedGeometry::create();
	beginEditCP(TheNewSkeletonGeometry);
		TheNewSkeletonGeometry->addSkeleton(ExampleSkeleton);
		TheNewSkeletonGeometry->setBaseGeometry(geo);
		//Back
		TheNewSkeletonGeometry->addJointBlending(0,Pelvis,1.0f);
		TheNewSkeletonGeometry->addJointBlending(1,Pelvis,1.0f);
		TheNewSkeletonGeometry->addJointBlending(2,Clavicle,1.0f);
		TheNewSkeletonGeometry->addJointBlending(3,Clavicle,1.0f);

		//Head
		TheNewSkeletonGeometry->addJointBlending(4,Clavicle,1.0f);
		TheNewSkeletonGeometry->addJointBlending(5,Clavicle,1.0f);
		TheNewSkeletonGeometry->addJointBlending(6,Head,1.0f);
		TheNewSkeletonGeometry->addJointBlending(7,Head,1.0f);

		//Left Shoulder
		TheNewSkeletonGeometry->addJointBlending(8,Clavicle,1.0f);
		TheNewSkeletonGeometry->addJointBlending(9,Clavicle,1.0f);
		TheNewSkeletonGeometry->addJointBlending(10,LeftShoulder,1.0f);
		TheNewSkeletonGeometry->addJointBlending(11,LeftShoulder,1.0f);

		//Left Humerus
		TheNewSkeletonGeometry->addJointBlending(12,LeftShoulder,1.0f);
		TheNewSkeletonGeometry->addJointBlending(13,LeftShoulder,1.0f);
		TheNewSkeletonGeometry->addJointBlending(14,LeftElbow,1.0f);
		TheNewSkeletonGeometry->addJointBlending(15,LeftElbow,1.0f);

		//Left Radius
		TheNewSkeletonGeometry->addJointBlending(16,LeftElbow,1.0f);
		TheNewSkeletonGeometry->addJointBlending(17,LeftElbow,1.0f);
		TheNewSkeletonGeometry->addJointBlending(18,LeftHand,1.0f);
		TheNewSkeletonGeometry->addJointBlending(19,LeftHand,1.0f);

		//Left Hand
		TheNewSkeletonGeometry->addJointBlending(20,LeftHand,1.0f);
		TheNewSkeletonGeometry->addJointBlending(21,LeftHand,1.0f);
		TheNewSkeletonGeometry->addJointBlending(22,LeftFingers,1.0f);
		TheNewSkeletonGeometry->addJointBlending(23,LeftFingers,1.0f);

		//Right Shoulder
		TheNewSkeletonGeometry->addJointBlending(24,Clavicle,1.0f);
		TheNewSkeletonGeometry->addJointBlending(25,Clavicle,1.0f);
		TheNewSkeletonGeometry->addJointBlending(26,RightShoulder,1.0f);
		TheNewSkeletonGeometry->addJointBlending(27,RightShoulder,1.0f);

		//Right Humerus
		TheNewSkeletonGeometry->addJointBlending(28,RightShoulder,1.0f);
		TheNewSkeletonGeometry->addJointBlending(29,RightShoulder,1.0f);
		TheNewSkeletonGeometry->addJointBlending(30,RightElbow,1.0f);
		TheNewSkeletonGeometry->addJointBlending(31,RightElbow,1.0f);

		//Right Radius
		TheNewSkeletonGeometry->addJointBlending(32,RightElbow,1.0f);
		TheNewSkeletonGeometry->addJointBlending(33,RightElbow,1.0f);
		TheNewSkeletonGeometry->addJointBlending(34,RightHand,1.0f);
		TheNewSkeletonGeometry->addJointBlending(35,RightHand,1.0f);

		//Right Hand
		TheNewSkeletonGeometry->addJointBlending(36,RightHand,1.0f);
		TheNewSkeletonGeometry->addJointBlending(37,RightHand,1.0f);
		TheNewSkeletonGeometry->addJointBlending(38,RightFingers,1.0f);
		TheNewSkeletonGeometry->addJointBlending(39,RightFingers,1.0f);

		//Left Hip
		TheNewSkeletonGeometry->addJointBlending(40,Pelvis,1.0f);
		TheNewSkeletonGeometry->addJointBlending(41,Pelvis,1.0f);
		TheNewSkeletonGeometry->addJointBlending(42,LeftHip,1.0f);
		TheNewSkeletonGeometry->addJointBlending(43,LeftHip,1.0f);

		//Left Femur
		TheNewSkeletonGeometry->addJointBlending(44,LeftHip,1.0f);
		TheNewSkeletonGeometry->addJointBlending(45,LeftHip,1.0f);
		TheNewSkeletonGeometry->addJointBlending(46,LeftKnee,1.0f);
		TheNewSkeletonGeometry->addJointBlending(47,LeftKnee,1.0f);

		//Left Tibia
		TheNewSkeletonGeometry->addJointBlending(48,LeftKnee,1.0f);
		TheNewSkeletonGeometry->addJointBlending(49,LeftKnee,1.0f);
		TheNewSkeletonGeometry->addJointBlending(50,LeftFoot,1.0f);
		TheNewSkeletonGeometry->addJointBlending(51,LeftFoot,1.0f);

		//Left Foot
		TheNewSkeletonGeometry->addJointBlending(52,LeftFoot,1.0f);
		TheNewSkeletonGeometry->addJointBlending(53,LeftFoot,1.0f);
		TheNewSkeletonGeometry->addJointBlending(54,LeftToes,1.0f);
		TheNewSkeletonGeometry->addJointBlending(55,LeftToes,1.0f);

		//Right Hip
		TheNewSkeletonGeometry->addJointBlending(56,Pelvis,1.0f);
		TheNewSkeletonGeometry->addJointBlending(57,Pelvis,1.0f);
		TheNewSkeletonGeometry->addJointBlending(58,RightHip,1.0f);
		TheNewSkeletonGeometry->addJointBlending(59,RightHip,1.0f);

		//Right Femur
		TheNewSkeletonGeometry->addJointBlending(60,RightHip,1.0f);
		TheNewSkeletonGeometry->addJointBlending(61,RightHip,1.0f);
		TheNewSkeletonGeometry->addJointBlending(62,RightKnee,1.0f);
		TheNewSkeletonGeometry->addJointBlending(63,RightKnee,1.0f);

		//Right Tibia
		TheNewSkeletonGeometry->addJointBlending(64,RightKnee,1.0f);
		TheNewSkeletonGeometry->addJointBlending(65,RightKnee,1.0f);
		TheNewSkeletonGeometry->addJointBlending(66,RightFoot,1.0f);
		TheNewSkeletonGeometry->addJointBlending(67,RightFoot,1.0f);

		//Right Foot
		TheNewSkeletonGeometry->addJointBlending(68,RightFoot,1.0f);
		TheNewSkeletonGeometry->addJointBlending(69,RightFoot,1.0f);
		TheNewSkeletonGeometry->addJointBlending(70,RightToes,1.0f);
		TheNewSkeletonGeometry->addJointBlending(71,RightToes,1.0f);
    endEditCP(TheNewSkeletonGeometry);
	
	MeshNode = Node::create();
    beginEditCP(MeshNode, Node::CoreFieldMask);
        MeshNode->setCore(TheNewSkeletonGeometry);
    endEditCP(MeshNode, Node::CoreFieldMask);


	
   //Animation Advancer
   TheAnimationAdvancer = ElapsedTimeAnimationAdvancer::create();
   beginEditCP(TheAnimationAdvancer);
   ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->setStartTime( 0.0 );
   beginEditCP(TheAnimationAdvancer);


   //Create scene node 
    NodePtr scene = Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(Group::create());
		scene->addChild(UnboundGeometry);
        scene->addChild(SkeletonNode);
        scene->addChild(MeshNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    mgr->setRoot(scene);

	//Setup the Animation
	setupAnimation();


    // Show the whole Scene
    mgr->showAll();
    TheAnimationAdvancer->start();


    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
                        WinSize,
                                        "13MeshBlending");

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
	Matrix TempMat;

	//We create an animation and an animator for each joint we wish to animate

	//Left Elbow
	KeyframeTransformationsSequencePtr LeftElbowKeyframes = KeyframeTransformationsSequence44f::create();
	//Make keyframes
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
	//Make keyframes
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
	//Make keyframes
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
	//Make keyframes
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
	//Make keyframes
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
	//Make keyframes
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
    KeyframeAnimatorPtr ClavicleAnimator = KeyframeAnimator::create();
    beginEditCP(ClavicleAnimator);
       ClavicleAnimator->setKeyframeSequence(ClavicleKeyframes);
    endEditCP(ClavicleAnimator);

	//Skeleton Animation
   TheSkeletonAnimation = SkeletonAnimation::create();
	//Add the animators we just made to the skeleton animation
   beginEditCP(TheSkeletonAnimation);
		TheSkeletonAnimation->addTransformationAnimator(LeftElbowAnimator, LeftElbow);  //Here we tell the skeleton animation the it should use the animator LeftElbowAnimator to animate the joint LeftElbow
		TheSkeletonAnimation->addTransformationAnimator(RightElbowAnimator, RightElbow);
		TheSkeletonAnimation->addTransformationAnimator(LeftShoulderAnimator, LeftShoulder);
		TheSkeletonAnimation->addTransformationAnimator(RightShoulderAnimator, RightShoulder);
		TheSkeletonAnimation->addTransformationAnimator(LeftHipAnimator, LeftHip);
		TheSkeletonAnimation->addTransformationAnimator(RightHipAnimator, RightHip);
		TheSkeletonAnimation->addTransformationAnimator(ClavicleAnimator, Clavicle);
		TheSkeletonAnimation->setSkeleton(ExampleSkeleton);
   endEditCP(TheSkeletonAnimation);
}
