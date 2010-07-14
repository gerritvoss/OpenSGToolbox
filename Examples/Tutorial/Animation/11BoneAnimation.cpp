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
#include "OSGJoint.h"
#include "OSGSkeletonBlendedGeometry.h"
#include "OSGSkeletonDrawable.h"

#include "OSGRandomPoolManager.h"

// FROM ANIMATION.CPP
#include "OSGTime.h"
#include "OSGKeyframeSequence.h"
#include "OSGFieldAnimation.h"
#include "OSGKeyframeAnimator.h"
#include "OSGNameAttachment.h"
#include "OSGKeyframeSequences.h"



// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerUnrecPtr TutorialWindow;

Time TimeLastIdle;
NodeUnrecPtr SkeletonNode;
AnimationUnrecPtr TheJointAnimation;
AnimationUnrecPtr TheChildJointAnimation;
AnimationUnrecPtr TheCurrentAnimation;
bool animationPaused = false;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);
void setupAnimation(JointUnrecPtr TheJoint, JointUnrecPtr TheChildJoint);

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
		   {
				animationPaused = false;
				TheCurrentAnimation->start();
		   }
		   else
		   {
				animationPaused = true;
				TheCurrentAnimation->pause(false);
		   }

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

	   //Switch animation
	   if(e->getKey() == KeyEvent::KEY_1)
	   {
			TheCurrentAnimation = TheJointAnimation;
	   }
	   else if(e->getKey() == KeyEvent::KEY_2)
	   {
			TheCurrentAnimation = TheChildJointAnimation;
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
	std::cout << "\n\nKEY COMMANDS:" << std::endl;
	std::cout << "space   Play/Pause the animation" << std::endl;
	std::cout << "B       Show/Hide the bind pose skeleton" << std::endl;
	std::cout << "P       Show/Hide the current pose skeleton" << std::endl;
	std::cout << "1       Play first example animation" << std::endl;
	std::cout << "2       Play second example animation" << std::endl;
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
	JointRecPtr ExampleRootJoint = Joint::create();

    //Add this joint to the skeleton
    ExampleSkeleton->pushToJoints(ExampleRootJoint, Matrix());

    NodeRecPtr ExampleRootJointNode = makeNodeFor(ExampleRootJoint);

    NodeRecPtr TempRootJointNode = ExampleRootJointNode;
    NodeRefPtr GeoNode = makeNodeFor(BoxGeometry);
    TempRootJointNode->addChild(GeoNode);

	Matrix TempMat;
	//Create a set of randomly placed child joints
	for (Real32 i = 0.0f; i < 5.0f; ++i)
	{
		JointRecPtr ExampleChildJoint = Joint::create();
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
        ExampleChildJoint->setJointTransformation(TempMat);

		//Add ExampleChildJoint as a child to the previous joint	
        TempRootJointNode->addChild(ExampleChildJointNode);//add a Child to the root joint

		//ExampleChildJoint will be the next parent joint
		TempRootJointNode = ExampleChildJointNode;
        
        //Add this joint to the skeleton
        Matrix InvBind(TempRootJointNode->getToWorld());
        InvBind.invert();
        ExampleSkeleton->pushToJoints(ExampleChildJoint, InvBind);
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
	SkeletonNode = Node::create();
    SkeletonNode->setCore(ExampleSkeletonDrawable);

    //Create scene
    NodeUnrecPtr scene = Node::create();
    scene->setCore(Group::create());
    scene->addChild(SkeletonNode);
    scene->addChild(ExampleRootJointNode);

    mgr->setRoot(scene);

	//Setup the Animation
	setupAnimation(ExampleRootJoint,
                   dynamic_cast<Joint*>(ExampleRootJointNode->getChild(1)->getCore()));

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
                        WinSize,
                                        "11BoneAnimation");

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



void setupAnimation(JointUnrecPtr TheJoint, JointUnrecPtr TheChildJoint)
{
	//Create an animation for TheJoint
	//TheJoint Transformation keyframes (we'll animate TheJoint's translation)
	Matrix transform = TheJoint->getJointTransformation();

	KeyframeTransformationSequenceUnrecPtr TheJointTranformationKeyframes = KeyframeTransformationSequenceMatrix4f::create();
	
	transform.setTranslate(0.0f,0.0f,0.0f);
	TheJointTranformationKeyframes->addKeyframe(transform, 0.0f);

	transform.setTranslate(2.0f,0.0f,0.0f);
	TheJointTranformationKeyframes->addKeyframe(transform, 2.0f);

	transform.setTranslate(1.0f,0.0f,0.0f);
	TheJointTranformationKeyframes->addKeyframe(transform, 4.0f);

	transform.setTranslate(3.0f,0.0f,0.0f);
	TheJointTranformationKeyframes->addKeyframe(transform, 6.0f);

	transform = TheJoint->getJointTransformation();
	transform.setTranslate(0.0f,0.0f,0.0f);
	TheJointTranformationKeyframes->addKeyframe(transform, 8.0f);

	//TheJoint Animator
    AnimatorUnrecPtr TheJointAnimator = KeyframeAnimator::create();
    dynamic_pointer_cast<KeyframeAnimator>(TheJointAnimator)->setKeyframeSequence(TheJointTranformationKeyframes);

    //TheJoint Animation
    TheJointAnimation = FieldAnimation::create();
    dynamic_pointer_cast<FieldAnimation>(TheJointAnimation)->setAnimator(TheJointAnimator);
    dynamic_pointer_cast<FieldAnimation>(TheJointAnimation)->setInterpolationType(Animator::CUBIC_INTERPOLATION);
    dynamic_pointer_cast<FieldAnimation>(TheJointAnimation)->setCycling(-1);
    dynamic_pointer_cast<FieldAnimation>(TheJointAnimation)->setAnimatedField(TheJoint, std::string("JointTransformation"));
	
    TheJointAnimation->attachUpdateProducer(TutorialWindow->editEventProducer());
    TheJointAnimation->start();

	//Create an animation for TheChildJoint
	//TheChildJoint Transformation keyframes (we'll animate TheChildJoint's rotation)
	transform = TheChildJoint->getJointTransformation();

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
    TheChildJointAnimation = FieldAnimation::create();
    dynamic_pointer_cast<FieldAnimation>(TheChildJointAnimation)->setAnimator(TheChildJointAnimator);
    dynamic_pointer_cast<FieldAnimation>(TheChildJointAnimation)->setInterpolationType(Animator::CUBIC_INTERPOLATION);
    dynamic_pointer_cast<FieldAnimation>(TheChildJointAnimation)->setCycling(-1);
    dynamic_pointer_cast<FieldAnimation>(TheChildJointAnimation)->setAnimatedField(TheChildJoint, std::string("JointTransformation"));

    TheChildJointAnimation->attachUpdateProducer(TutorialWindow->editEventProducer());
	TheJointAnimation->attachUpdateProducer(TutorialWindow->editEventProducer());

		//Set the currently playing animation to TheJointAnimation (can be switched at runtime via a key command)
	TheCurrentAnimation = TheJointAnimation;
	TheCurrentAnimation->start();
}

