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
#include <OpenSG/Animation/OSGKeyframeSequence.h>
#include <OpenSG/Animation/OSGFieldAnimation.h>
#include <OpenSG/Animation/OSGKeyframeAnimator.h>
#include <OpenSG/Animation/OSGKeyframeSequenceVec3f.h>
#include <OpenSG/Animation/OSGKeyframeSequenceQuaternion.h>
#include <OpenSG/Animation/OSGElapsedTimeAnimationAdvancer.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include <OpenSG/Animation/OSGKeyframeSequenceReal32.h>
#include <OpenSG/Animation/OSGSkeletonAnimation.h>



// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

osg::Time TimeLastIdle;
osg::AnimationPtr TheSkeletonAnimation;
osg::AnimationAdvancerPtr TheAnimationAdvancer;

bool ExitApp = false;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);
void setupAnimation(BonePtr TheBone, BonePtr TheChildBone, BonePtr TheBoneLength);

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
		osg::ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->update(e.getElapsedTime());

		TheSkeletonAnimation->update(TheAnimationAdvancer);
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

//===========================================BONE==================================================================
	const int num = 9;
	BonePtr Torso, LeftHumerus, LeftRadius, LeftHand, LeftFemur, LeftTibia, LeftFeet,
		           RightHumerus, RighRadius, RighHand, RighFemur, RighTibia, RightFeet; 

	BonePtr ExampleRootBone = Bone::create();
	BonePtr TempRootBone;
	BonePtr ExampleChildBone;
	TempRootBone = ExampleRootBone;


	for (int i = 1; i < num; i++)
	{
		

		Real32 Rand = RandomPoolManager::getRandomReal32(9.0f, 180.0);  // opsg 32 bit real random number generator
																		// check OSGRandomPoolManager.h in 
                                                                        // vs-8.0-ToolBoxTutorials

		// Pic a bone and animate it 

		ExampleChildBone = Bone::create(); //create a bone called ExampleChildbone
		beginEditCP(ExampleChildBone, Bone::RotationFieldMask | Bone::LengthFieldMask);//use the field masks
			ExampleChildBone->setLength(5.0f);
			ExampleChildBone->setRotation(Quaternion(Vec3f((Rand/i),(Rand/i),(Rand/i)), osgdegree2rad(Rand)));
		endEditCP(ExampleChildBone, Bone::RotationFieldMask | Bone::LengthFieldMask);
		
		
		TempRootBone->addChild(ExampleChildBone);//add a Child to the root bone
		TempRootBone = TempRootBone->getChild(0);
	
	}
//=================================================================================================================
	UInt32 SelectedChildDepth=1;
	BonePtr TheSelectedBone = ExampleRootBone;
	for(UInt32 i(0) ; i<SelectedChildDepth && TheSelectedBone->getNumChildren() >0 ; ++i )
	{
		TheSelectedBone = TheSelectedBone->getChild(0);
		
	}


	

    //Skeleton
    SkeletonPtr ExampleSkeleton = Skeleton::create();
	beginEditCP(ExampleSkeleton, Skeleton::RootBonesFieldMask);
		ExampleSkeleton->getRootBones().push_back(ExampleRootBone);
	endEditCP(ExampleSkeleton, Skeleton::RootBonesFieldMask);

    //SkeletonDrawer
    SkeletonDrawablePtr ExampleSkeletonDrawable = osg::SkeletonDrawable::create();
    beginEditCP(ExampleSkeletonDrawable, SkeletonDrawable::SkeletonFieldMask | SkeletonDrawable::MaterialFieldMask);
		ExampleSkeletonDrawable->setSkeleton(ExampleSkeleton);
		ExampleSkeletonDrawable->setMaterial(ExampleMaterial);
    endEditCP(ExampleSkeletonDrawable, SkeletonDrawable::SkeletonFieldMask | SkeletonDrawable::MaterialFieldMask);
	
	//Particle System Node
    
	NodePtr SkeletonNode = osg::Node::create();
    beginEditCP(SkeletonNode, Node::CoreFieldMask);
        SkeletonNode->setCore(ExampleSkeletonDrawable);
    endEditCP(SkeletonNode, Node::CoreFieldMask);


    
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
        scene->addChild(SkeletonNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    mgr->setRoot(scene);

	//Setup the Animation
	setupAnimation(ExampleRootBone,TheSelectedBone,TheSelectedBone);
	


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



void setupAnimation(BonePtr TheBone,BonePtr TheChildBone,BonePtr TheBoneLength )
{

   //Quaternion
   osg::KeyframeSequencePtr KeyframeSequence = osg::KeyframeSequenceQuaternion::create();
   
   osg::KeyframeSequenceQuaternionPtr::dcast(KeyframeSequence)->getValues().push_back(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),0.0));
   osg::KeyframeSequenceQuaternionPtr::dcast(KeyframeSequence)->getValues().push_back(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),0.5*osg::Pi));
   osg::KeyframeSequenceQuaternionPtr::dcast(KeyframeSequence)->getValues().push_back(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),osg::Pi));
   osg::KeyframeSequenceQuaternionPtr::dcast(KeyframeSequence)->getValues().push_back(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),1.5*osg::Pi));
   osg::KeyframeSequenceQuaternionPtr::dcast(KeyframeSequence)->getValues().push_back(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),2.0*osg::Pi));


   //Length
   osg::KeyframeSequencePtr LengthKeyframeSequence = osg::KeyframeSequenceReal32::create();
   
   osg::KeyframeSequenceReal32Ptr::dcast(LengthKeyframeSequence)->getValues().push_back(0.7);
   osg::KeyframeSequenceReal32Ptr::dcast(LengthKeyframeSequence)->getValues().push_back(20.0);
   osg::KeyframeSequenceReal32Ptr::dcast(LengthKeyframeSequence)->getValues().push_back(0.7);
   osg::KeyframeSequenceReal32Ptr::dcast(LengthKeyframeSequence)->getValues().push_back(99.0);
   osg::KeyframeSequenceReal32Ptr::dcast(LengthKeyframeSequence)->getValues().push_back(0.7);
   


   //Rotation Animator
   osg::KeyframeAnimatorPtr Animator = osg::KeyframeAnimator::create();
   osg::beginEditCP(Animator);
      osg::KeyframeAnimatorPtr::dcast(Animator)->setValues(KeyframeSequence);
      osg::KeyframeAnimatorPtr::dcast(Animator)->getKeys().push_back(0.0);
      osg::KeyframeAnimatorPtr::dcast(Animator)->getKeys().push_back(2.0);
      osg::KeyframeAnimatorPtr::dcast(Animator)->getKeys().push_back(4.0);
      osg::KeyframeAnimatorPtr::dcast(Animator)->getKeys().push_back(6.0);
      osg::KeyframeAnimatorPtr::dcast(Animator)->getKeys().push_back(8.0);
   osg::endEditCP(Animator);

 //Length Animator
   osg::KeyframeAnimatorPtr LengthAnimator = osg::KeyframeAnimator::create();
   osg::beginEditCP(LengthAnimator);
      osg::KeyframeAnimatorPtr::dcast(LengthAnimator)->setValues(LengthKeyframeSequence);
      osg::KeyframeAnimatorPtr::dcast(LengthAnimator)->getKeys().push_back(0.0);
      osg::KeyframeAnimatorPtr::dcast(LengthAnimator)->getKeys().push_back(2.0);
      osg::KeyframeAnimatorPtr::dcast(LengthAnimator)->getKeys().push_back(4.0);
      osg::KeyframeAnimatorPtr::dcast(LengthAnimator)->getKeys().push_back(6.0);
      osg::KeyframeAnimatorPtr::dcast(LengthAnimator)->getKeys().push_back(8.0);
   osg::endEditCP(LengthAnimator);



  //Skeleton Animation
   TheSkeletonAnimation = osg::SkeletonAnimation::create();
   osg::SkeletonAnimationPtr::dcast(TheSkeletonAnimation)->addRotationAnimator(Animator, TheBone);
   osg::SkeletonAnimationPtr::dcast(TheSkeletonAnimation)->addRotationAnimator(Animator, TheChildBone);
   osg::SkeletonAnimationPtr::dcast(TheSkeletonAnimation)->addLengthAnimator(LengthAnimator, TheBoneLength);


   //Animation Advancer
   TheAnimationAdvancer = osg::ElapsedTimeAnimationAdvancer::create();
   osg::beginEditCP(TheAnimationAdvancer);
   osg::ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->setStartTime( 0.0 );
   osg::beginEditCP(TheAnimationAdvancer);
}
