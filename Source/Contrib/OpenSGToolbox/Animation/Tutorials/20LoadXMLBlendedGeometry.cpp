// 
// OpenSGToolbox Tutorial: 20LoadXMLBlendedGeometry 
//
// Loads a skeleton and an attached geometry from an
// XML file.
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

//Animation
#include <OpenSG/Animation/OSGJoint.h>
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
NodePtr MeshNode;
NodePtr UnboundGeometry;
AnimationPtr TheSkeletonAnimation;
AnimationAdvancerPtr TheAnimationAdvancer;
bool animationPaused = false;

// The pointer to the transformation
TransformPtr trans;

// The pointer to the geometry core
GeometryPtr geo;





// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// Create a class to allow for the use of the keyboard shortucts 
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventPtr e)
   {
	   //Exit
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           TutorialWindowEventProducer->closeWindow();
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
		   if(e->getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
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
	   if(e->getKey() == KeyEvent::KEY_P)
	   {
		   if(e->getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
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

   virtual void keyReleased(const KeyEventPtr e)
   {
   }

   virtual void keyTyped(const KeyEventPtr e)
   {
   }
};

class TutorialMouseListener : public MouseListener
{
  public:
    virtual void mouseClicked(const MouseEventPtr e)
    {
    }
    virtual void mouseEntered(const MouseEventPtr e)
    {
    }
    virtual void mouseExited(const MouseEventPtr e)
    {
    }
    virtual void mousePressed(const MouseEventPtr e)
    {
            mgr->mouseButtonPress(e->getButton(), e->getLocation().x(), e->getLocation().y());
    }
    virtual void mouseReleased(const MouseEventPtr e)
    {
           mgr->mouseButtonRelease(e->getButton(), e->getLocation().x(), e->getLocation().y());
    }
};

class TutorialMouseMotionListener : public MouseMotionListener
{
  public:
    virtual void mouseMoved(const MouseEventPtr e)
    {
            mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
    }

    virtual void mouseDragged(const MouseEventPtr e)
    {
            mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
    }
};

class TutorialUpdateListener : public UpdateListener
{
  public:
    virtual void update(const UpdateEventPtr e)
    {
		if(!animationPaused)
		{
			osg::ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->update(e->getElapsedTime());

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
	


    //Import scene from XML
    ChunkMaterialPtr ExampleMaterial;
    SkeletonPtr ExampleSkeleton;
    SkeletonBlendedGeometryPtr TheNewSkeletonGeometry;
    GeometryPtr ExampleGeometry;

    FCFileType::FCPtrStore NewContainers;
    NewContainers = FCFileHandler::the()->read(Path("./Data/20BlendedGeometry.xml"));

    FCFileType::FCPtrStore::iterator Itor;
    for(Itor = NewContainers.begin() ; Itor != NewContainers.end() ; ++Itor)
    {
        if( (*Itor)->getType() == (ChunkMaterial::getClassType()))
        {
			  //Set ExampleMaterial to the ChunkMaterial we just read in
            ExampleMaterial = (ChunkMaterial::Ptr::dcast(*Itor));
        }
        if( (*Itor)->getType() == (Skeleton::getClassType()))
        {
			  //Set ExampleSkeleton to the Skeleton we just read in
            ExampleSkeleton = (Skeleton::Ptr::dcast(*Itor));
        }
        if( (*Itor)->getType() == (Geometry::getClassType()))
        {
			  //Set ExampleGeometry to the geometry we just read in
            ExampleGeometry = (Geometry::Ptr::dcast(*Itor));
        }
        if( (*Itor)->getType() == (SkeletonBlendedGeometry::getClassType()))
        {
			  //Set TheNewSkeletonGeometry to the SkeletonBlendedGeometry we just read in
            TheNewSkeletonGeometry = (SkeletonBlendedGeometry::Ptr::dcast(*Itor));
        }
        if( (*Itor)->getType().isDerivedFrom(Animation::getClassType()))
        {
			  //Set TheSkeletonAnimation to the Animation we just read in
            TheSkeletonAnimation = (Animation::Ptr::dcast(*Itor));
        }
    }

	//UnboundGeometry
	UnboundGeometry = Node::create();
	beginEditCP(UnboundGeometry, Node::CoreFieldMask | Node::TravMaskFieldMask);
        UnboundGeometry->setCore(ExampleGeometry);
		UnboundGeometry->setTravMask(0);
    endEditCP(UnboundGeometry, Node::CoreFieldMask | Node::TravMaskFieldMask);

	//SkeletonDrawer
    SkeletonDrawablePtr ExampleSkeletonDrawable = osg::SkeletonDrawable::create();
    beginEditCP(ExampleSkeletonDrawable, SkeletonDrawable::SkeletonFieldMask | SkeletonDrawable::MaterialFieldMask | SkeletonDrawable::DrawBindPoseFieldMask | SkeletonDrawable::BindPoseColorFieldMask | SkeletonDrawable::DrawPoseFieldMask | SkeletonDrawable::PoseColorFieldMask);
		ExampleSkeletonDrawable->setSkeleton(ExampleSkeleton);
		ExampleSkeletonDrawable->setMaterial(ExampleMaterial);
		ExampleSkeletonDrawable->setDrawBindPose(false);  //By default, we don't draw the skeleton's bind pose
		ExampleSkeletonDrawable->setBindPoseColor(Color4f(0.0, 1.0, 0.0, 1.0));  //When drawn, the skeleton's bind pose renders in green
		ExampleSkeletonDrawable->setDrawPose(true);  //By default, we do draw the skeleton's current pose
		ExampleSkeletonDrawable->setPoseColor(Color4f(0.0, 0.0, 1.0, 1.0));  //The skeleton's current pose renders in blue
    endEditCP(ExampleSkeletonDrawable, SkeletonDrawable::SkeletonFieldMask | SkeletonDrawable::MaterialFieldMask | SkeletonDrawable::DrawBindPoseFieldMask | SkeletonDrawable::BindPoseColorFieldMask | SkeletonDrawable::DrawPoseFieldMask | SkeletonDrawable::PoseColorFieldMask);
	
	//Skeleton Node
	SkeletonNode = osg::Node::create();
    beginEditCP(SkeletonNode, Node::CoreFieldMask);
        SkeletonNode->setCore(ExampleSkeletonDrawable);
    endEditCP(SkeletonNode, Node::CoreFieldMask);

	//Skeleton Blended Geometry Node
	MeshNode = osg::Node::create();
    beginEditCP(MeshNode, Node::CoreFieldMask);
        MeshNode->setCore(TheNewSkeletonGeometry);
    endEditCP(MeshNode, Node::CoreFieldMask);
	
   //Animation Advancer
   TheAnimationAdvancer = osg::ElapsedTimeAnimationAdvancer::create();
   osg::beginEditCP(TheAnimationAdvancer);
   osg::ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->setStartTime( 0.0 );
   osg::beginEditCP(TheAnimationAdvancer);


    //Create scene
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
		scene->addChild(UnboundGeometry);
        scene->addChild(SkeletonNode);
        scene->addChild(MeshNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    mgr->setRoot(scene);


    // Show the whole Scene
    mgr->showAll();
    TheAnimationAdvancer->start();

	 //Show window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "20LoadXMLBlendedGeometry");

    //Enter main Loop
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
