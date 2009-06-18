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

Time TimeLastIdle;
AnimationPtr TheJointAnimation;
AnimationPtr TheChildJointAnimation;
AnimationAdvancerPtr TheAnimationAdvancer;

bool ExitApp = false;

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
       if(e.getKey() == KeyEvent::KEY_Q && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           ExitApp = true;
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
		ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->update(e.getElapsedTime());

		//TheJointAnimation->update(TheAnimationAdvancer);
		TheChildJointAnimation ->update(TheAnimationAdvancer);
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
                                        "OpenSG 10SkeletonDrawer Window");
										

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
		ExampleSkeletonDrawable->setDrawBindPose(true);
		ExampleSkeletonDrawable->setBindPoseColor(Color4f(0.0, 1.0, 0.0, 1.0));
		ExampleSkeletonDrawable->setDrawPose(true);
		ExampleSkeletonDrawable->setPoseColor(Color4f(0.0, 0.0, 1.0, 1.0));
		
    endEditCP(ExampleSkeletonDrawable, SkeletonDrawable::SkeletonFieldMask | SkeletonDrawable::MaterialFieldMask | SkeletonDrawable::DrawBindPoseFieldMask | SkeletonDrawable::BindPoseColorFieldMask | SkeletonDrawable::DrawPoseFieldMask | SkeletonDrawable::PoseColorFieldMask);
	
	//Particle System Node
    
	NodePtr SkeletonNode = Node::create();
    beginEditCP(SkeletonNode, Node::CoreFieldMask);
        SkeletonNode->setCore(ExampleSkeletonDrawable);
    endEditCP(SkeletonNode, Node::CoreFieldMask);


    
    NodePtr scene = Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(Group::create());
        scene->addChild(SkeletonNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    mgr->setRoot(scene);

	//Setup the Animation
	setupAnimation(ExampleRootJoint, ExampleRootJoint->getChildJoints(0));


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



void setupAnimation(JointPtr TheJoint, JointPtr TheChildJoint)
{
	//TheJoint Transformation keyframes (setting translation)
	Matrix transform = TheJoint->getRelativeTransformation();

	KeyframeTransformationsSequencePtr TheJointTranformationKeyframes = KeyframeTransformationsSequence44f::create();
	
	TheJointTranformationKeyframes->addKeyframe(transform, 0.0f);

	transform.setTranslate(5.0, 0.0, 0.0);
	TheJointTranformationKeyframes->addKeyframe(transform, 2.0f);

	transform.setTranslate(0.0, 5.0, 0.0);
	TheJointTranformationKeyframes->addKeyframe(transform, 4.0f);

	transform.setTranslate(0.0, 0.0, 5.0);
	TheJointTranformationKeyframes->addKeyframe(transform, 6.0f);

	transform = TheJoint->getRelativeTransformation();
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
	
	
	
	
	
	////Quaternion
 //  KeyframeRotationsSequencePtr RotationKeyframes = KeyframeRotationsSequenceQuat::create();
 //  
 //  RotationKeyframes->addKeyframe(Quaternion(Vec3f(0.0,1.0,0.0),0.0),0.0f);
 //  RotationKeyframes->addKeyframe(Quaternion(Vec3f(0.0,1.0,0.0),0.5*Pi),2.0f);
 //  RotationKeyframes->addKeyframe(Quaternion(Vec3f(0.0,1.0,0.0),Pi),4.0f);
 //  RotationKeyframes->addKeyframe(Quaternion(Vec3f(0.0,1.0,0.0),1.5*Pi),6.0f);
 //  RotationKeyframes->addKeyframe(Quaternion(Vec3f(0.0,1.0,0.0),2.0*Pi),8.0f);


 //  //Length
 //  KeyframeNumbersSequencePtr LengthKeyframeSequence = KeyframeNumbersSequenceReal32::create();
 //  
 //  LengthKeyframeSequence->addKeyframe(0.7,0.0f);
 //  LengthKeyframeSequence->addKeyframe(20.2,0.0f);
 //  LengthKeyframeSequence->addKeyframe(0.7,4.0f);
 //  LengthKeyframeSequence->addKeyframe(99.0,6.0f);
 //  LengthKeyframeSequence->addKeyframe(0.7,8.0f);
 //  


 //  //Animator
 //  AnimatorPtr Animator = KeyframeAnimator::create();
 //  beginEditCP(Animator);
 //     KeyframeAnimatorPtr::dcast(Animator)->setKeyframeSequence(RotationKeyframes);
 //  endEditCP(Animator);
 //  
 //  //Animator
 //  AnimatorPtr LengthAnimator = KeyframeAnimator::create();
 //  beginEditCP(LengthAnimator);
 //     KeyframeAnimatorPtr::dcast(LengthAnimator)->setKeyframeSequence(LengthKeyframeSequence);
 //  endEditCP(LengthAnimator);
 //  
 //  //Animation
 //  TheAnimation = FieldAnimation::create();
 //  beginEditCP(TheAnimation);
 //     FieldAnimationPtr::dcast(TheAnimation)->setAnimator(Animator);
 //     FieldAnimationPtr::dcast(TheAnimation)->setInterpolationType(CUBIC_INTERPOLATION);
 //     FieldAnimationPtr::dcast(TheAnimation)->setCycling(-1);
 //  endEditCP(TheAnimation);
 //  FieldAnimationPtr::dcast(TheAnimation)->setAnimatedField(TheJoint, std::string("Rotation"));


 //  //ChildBone Animation
 //  TheChildAnimation = FieldAnimation::create();
 //  beginEditCP(TheChildAnimation);
 //     FieldAnimationPtr::dcast(TheChildAnimation)->setAnimator(Animator);
 //     FieldAnimationPtr::dcast(TheChildAnimation)->setInterpolationType(CUBIC_INTERPOLATION);
 //     FieldAnimationPtr::dcast(TheChildAnimation)->setCycling(-1);
 //  endEditCP(TheChildAnimation);
 //  FieldAnimationPtr::dcast(TheChildAnimation)->setAnimatedField(TheChildJoint, std::string("Rotation"));



 // //Length For Bones
 //  TheChildLengthAnimation = FieldAnimation::create();
 //  beginEditCP(TheChildLengthAnimation);
 //     FieldAnimationPtr::dcast(TheChildLengthAnimation)->setAnimator(LengthAnimator);
 //     FieldAnimationPtr::dcast(TheChildLengthAnimation)->setInterpolationType(CUBIC_INTERPOLATION);
 //     FieldAnimationPtr::dcast(TheChildLengthAnimation)->setCycling(-1);
 //  endEditCP(TheChildLengthAnimation);
 //  FieldAnimationPtr::dcast(TheChildLengthAnimation)->setAnimatedField(TheChildJoint, std::string("Length"));


   //Animation Advancer
   TheAnimationAdvancer = ElapsedTimeAnimationAdvancer::create();
   beginEditCP(TheAnimationAdvancer);
   ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->setStartTime( 0.0 );
   beginEditCP(TheAnimationAdvancer);
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



//glMultMatrixf(m.getValues());
		// const Matrix              &getTransformation(void) const;



	//BonePtr ExampleRootBone = Bone::create();
	//beginEditCP(ExampleRootBone, Bone::RotationFieldMask | Bone::LengthFieldMask);
		//ExampleRootBone->setLength(5.0f);
		//ExampleRootBone->setRotation(Quaternion(Vec3f(1.0f,0.0f,0.0f), osgdegree2rad(225.0f)));
	//endEditCP(ExampleRootBone, Bone::RotationFieldMask | Bone::LengthFieldMask);
	//ExampleRootBone->addChild(SecondChildBone);
	//SecondChildBone->addChild(ThirdChildBone);