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

//Animation
#include <OpenSG/Animation/OSGJoint.h>
#include <OpenSG/Animation/OSGSkeleton.h>
#include <OpenSG/Animation/OSGSkeletonDrawable.h>

#include <OpenSG/Toolbox/OSGRandomPoolManager.h>

// FROM ANIMATION.CPP
#include <OpenSG/OSGTime.h>
#include <OpenSG/Animation/OSGKeyframeSequence.h>
#include <OpenSG/Animation/OSGFieldAnimation.h>
#include <OpenSG/Animation/OSGKeyframeAnimator.h>
#include <OpenSG/Animation/OSGElapsedTimeAnimationAdvancer.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include <OpenSG/Animation/OSGKeyframeSequences.h>



// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;

Time TimeLastIdle;
NodePtr SkeletonNode;
AnimationPtr TheJointAnimation;
AnimationPtr TheChildJointAnimation;
AnimationPtr TheCurrentAnimation;
AnimationAdvancerPtr TheAnimationAdvancer;
bool animationPaused = false;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);
void setupAnimation(JointPtr TheJoint, JointPtr TheChildJoint);

// Create a class to allow for the use of the Ctrl+q
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

	   //Switch animation
	   if(e.getKey() == KeyEvent::KEY_1)
	   {
			TheCurrentAnimation = TheJointAnimation;
	   }
	   else if(e.getKey() == KeyEvent::KEY_2)
	   {
			TheCurrentAnimation = TheChildJointAnimation;
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

			TheCurrentAnimation->update(TheAnimationAdvancer);
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
	std::cout << "P       Show/Hide the current pose skeleton" << std::endl;
	std::cout << "1       Play first example animation" << std::endl;
	std::cout << "2       Play second example animation" << std::endl;
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

    //Joint
	JointPtr ExampleRootJoint = Joint::create();
	JointPtr TempRootJoint;
	TempRootJoint = ExampleRootJoint;
	Matrix TempMat;

	for (Real32 i = 1.0f; i < 9.0f; i++)
	{
		JointPtr ExampleChildJoint;

		TempMat.setTranslate(RandomPoolManager::getRandomReal32(0.0, 10.0f), RandomPoolManager::getRandomReal32(0.0f, 10.0f), RandomPoolManager::getRandomReal32(0.0f, 10.0f));
		ExampleChildJoint = Joint::create(); //create a bone called ExampleChildbone
		beginEditCP(ExampleChildJoint, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::UseParentTranslationFieldMask);//use the field masks
			ExampleChildJoint->setRelativeTransformation(TempMat);
			ExampleChildJoint->setBindRelativeTransformation(TempMat);
			ExampleChildJoint->setUseParentTranslation(true);
		endEditCP(ExampleChildJoint, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::UseParentTranslationFieldMask);

	
		beginEditCP(TempRootJoint, Joint::ChildJointsFieldMask);
			TempRootJoint->getChildJoints().push_back(ExampleChildJoint);//add a Child to the root bone
		endEditCP(TempRootJoint, Joint::ChildJointsFieldMask);
		

		TempRootJoint = TempRootJoint->getChildJoints(0);
	}

	

    //Skeleton
    SkeletonPtr ExampleSkeleton = Skeleton::create();
	beginEditCP(ExampleSkeleton, Skeleton::RootJointsFieldMask);
		ExampleSkeleton->getRootJoints().push_back(ExampleRootJoint);
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

    //Create scene
    NodePtr scene = Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(Group::create());
        scene->addChild(SkeletonNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    mgr->setRoot(scene);

	//Setup the Animation
	setupAnimation(ExampleRootJoint, ExampleRootJoint->getChildJoints(0));

	//Set the currently playing animation to TheJointAnimation
	TheCurrentAnimation = TheJointAnimation;


    // Show the whole Scene
    mgr->showAll();
    TheAnimationAdvancer->start();


    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
                        WinSize,
                                        "11BoneAnimation");

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



void setupAnimation(JointPtr TheJoint, JointPtr TheChildJoint)
{
	//TheJoint Transformation keyframes (setting translation)
	Matrix transform = TheJoint->getRelativeTransformation();

	KeyframeTransformationsSequencePtr TheJointTranformationKeyframes = KeyframeTransformationsSequence44f::create();
	
	transform.setTranslate(1.2, 2.3, 3.4);
	TheJointTranformationKeyframes->addKeyframe(transform, 0.0f);

	transform.setTranslate(1.2, 2.3, 3.4);
	TheJointTranformationKeyframes->addKeyframe(transform, 2.0f);

	transform.setTranslate(1.2, 2.3, 3.4);
	TheJointTranformationKeyframes->addKeyframe(transform, 4.0f);

	transform.setTranslate(1.2, 2.3, 3.4);
	TheJointTranformationKeyframes->addKeyframe(transform, 6.0f);

	transform = TheJoint->getRelativeTransformation();
	transform.setTranslate(1.2, 2.3, 3.4);
	TheJointTranformationKeyframes->addKeyframe(transform, 8.0f);

	//TheJoint Animator
    AnimatorPtr TheJointAnimator = KeyframeAnimator::create();
    beginEditCP(TheJointAnimator);
       KeyframeAnimatorPtr::dcast(TheJointAnimator)->setKeyframeSequence(TheJointTranformationKeyframes);
    endEditCP(TheJointAnimator);

    //TheJoint Animation
    TheJointAnimation = FieldAnimation::create();
    beginEditCP(TheJointAnimation);
       FieldAnimationPtr::dcast(TheJointAnimation)->setAnimator(TheJointAnimator);
       FieldAnimationPtr::dcast(TheJointAnimation)->setInterpolationType(CUBIC_INTERPOLATION);
       FieldAnimationPtr::dcast(TheJointAnimation)->setCycling(-1);
    endEditCP(TheJointAnimation);
    FieldAnimationPtr::dcast(TheJointAnimation)->setAnimatedField(TheJoint, std::string("RelativeTransformation"));
	


	//TheChildJoint Transformation keyframes (setting rotation)
	transform = TheChildJoint->getRelativeTransformation();

	KeyframeTransformationsSequencePtr TheChildJointTransformationKeyframes = KeyframeTransformationsSequence44f::create();

	TheChildJointTransformationKeyframes->addKeyframe(transform, 0.0f);

	transform.setRotate(Quaternion(Vec3f(0.0,1.0,0.0),0.0));
	TheChildJointTransformationKeyframes->addKeyframe(transform, 2.0f);

	transform.setRotate(Quaternion(Vec3f(0.0,1.0,0.0),0.5*Pi));
	TheChildJointTransformationKeyframes->addKeyframe(transform, 4.0f);

	transform.setRotate(Quaternion(Vec3f(0.0,1.0,0.0),Pi));
	TheChildJointTransformationKeyframes->addKeyframe(transform, 6.0f);

	transform.setRotate(Quaternion(Vec3f(0.0,1.0,0.0),1.5*Pi));
	TheChildJointTransformationKeyframes->addKeyframe(transform, 8.0f);

	//TheChildJoint Animator
    AnimatorPtr TheChildJointAnimator = KeyframeAnimator::create();
    beginEditCP(TheChildJointAnimator);
       KeyframeAnimatorPtr::dcast(TheChildJointAnimator)->setKeyframeSequence(TheChildJointTransformationKeyframes);
    endEditCP(TheChildJointAnimator);

	//TheChildJoint Animation
    TheChildJointAnimation = FieldAnimation::create();
    beginEditCP(TheChildJointAnimation);
       FieldAnimationPtr::dcast(TheChildJointAnimation)->setAnimator(TheChildJointAnimator);
       FieldAnimationPtr::dcast(TheChildJointAnimation)->setInterpolationType(CUBIC_INTERPOLATION);
       FieldAnimationPtr::dcast(TheChildJointAnimation)->setCycling(-1);
    endEditCP(TheChildJointAnimation);
    FieldAnimationPtr::dcast(TheChildJointAnimation)->setAnimatedField(TheChildJoint, std::string("RelativeTransformation"));
	
	
    //Animation Advancer
    TheAnimationAdvancer = ElapsedTimeAnimationAdvancer::create();
	beginEditCP(TheAnimationAdvancer);
		ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->setStartTime( 0.0 );
    endEditCP(TheAnimationAdvancer);
}





FieldContainerPtr getFieldContainer(const Char8 *szTypeName, const std::string &namestring)
{
   const FieldContainerType * TheFieldType( FieldContainerFactory::the()->findType(szTypeName) );
   if(TheFieldType == NULL)
   {
      std::cout << "The " << szTypeName << " Field type is not defined." << std::endl;
   }

   const std::vector<FieldContainerPtr>* FCStore(	FieldContainerFactory::the()->getFieldContainerStore () );

   std::vector<FieldContainerPtr>::const_iterator FCStoreIter;
   for(FCStoreIter = FCStore->begin() ; FCStoreIter != FCStore->end() ; ++FCStoreIter)
   {
      if( (*FCStoreIter) != NullFC && (*FCStoreIter)->getType() == (*TheFieldType) )
      {
         const Char8 *Name( getName(AttachmentContainerPtr::dcast(*FCStoreIter)) );
         if(Name != NULL && namestring.compare(Name) == 0)
         {
            return (*FCStoreIter);
         }
      }
   }

   return NullFC;
}
