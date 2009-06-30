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
#include <OpenSG/Animation/OSGKeyframeSequences.h>
#include <OpenSG/Animation/OSGFieldAnimation.h>
#include <OpenSG/Animation/OSGKeyframeAnimator.h>
#include <OpenSG/Animation/OSGElapsedTimeAnimationAdvancer.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include <OpenSG/Animation/OSGSkeletonAnimation.h>
#include <OpenSG/Animation/OSGSkeleton.h>
#include <OpenSG/Animation/OSGBone.h>

#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/Animation/OSGSkeletonBlendedGeometry.h>

#include <OpenSG/Toolbox/OSGFCFileHandler.h>


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

osg::Time TimeLastIdle;
osg::AnimationPtr TheSkeletonAnimation;
osg::AnimationAdvancerPtr TheAnimationAdvancer;

bool ExitApp = false;


//Store nodes for scene
std::vector<NodePtr> UnboundGeometries;
std::vector<NodePtr> SkeletonNodes;
std::vector<NodePtr> MeshNodes;
NodePtr Axes;
NodePtr Grid;


//Used to control animation
bool animationPaused;



// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

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
			   for(int i(0); i < UnboundGeometries.size(); ++i)
			   {
				   if(UnboundGeometries[i]->getTravMask() == 0)
				   {
					   beginEditCP(UnboundGeometries[i], Node::TravMaskFieldMask);
							UnboundGeometries[i]->setTravMask(1);
						endEditCP(UnboundGeometries[i], Node::TravMaskFieldMask);
				   } 
				   else
				   {
					   beginEditCP(UnboundGeometries[i], Node::TravMaskFieldMask);
							UnboundGeometries[i]->setTravMask(0);
						endEditCP(UnboundGeometries[i], Node::TravMaskFieldMask);
				   }
			   }
		   }
		   else
		   {
			   //Toggle skeleton
			   for(int i(0); i < SkeletonNodes.size(); ++i)
			   {
				   if(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore())->getDrawBindPose() == false)
				   {
					   beginEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore()), SkeletonDrawable::DrawBindPoseFieldMask);
						 SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore())->setDrawBindPose(true);
						endEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore()), SkeletonDrawable::DrawBindPoseFieldMask);
				   } 
				   else
				   {
					   beginEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore()), SkeletonDrawable::DrawBindPoseFieldMask);
						 SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore())->setDrawBindPose(false);
						endEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore()), SkeletonDrawable::DrawBindPoseFieldMask);
				   }
			   }
		   }
	   }

	   //Toggle current pose
	   if(e.getKey() == KeyEvent::KEY_P)
	   {
		   if(e.getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
		   {
			   //Toggle mesh
			   for(int i(0); i < MeshNodes.size(); ++i)
			   {
				   if(MeshNodes[i]->getTravMask() == 0)
				   {
					   beginEditCP(MeshNodes[i], Node::TravMaskFieldMask);
							MeshNodes[i]->setTravMask(1);
						endEditCP(MeshNodes[i], Node::TravMaskFieldMask);
				   } 
				   else
				   {
					   beginEditCP(MeshNodes[i], Node::TravMaskFieldMask);
							MeshNodes[i]->setTravMask(0);
						endEditCP(MeshNodes[i], Node::TravMaskFieldMask);
				   }
			   }
		   }
		   else
		   {
			   //Toggle skeleton
			   for(int i(0); i < SkeletonNodes.size(); ++i)
			   {
				   if(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore())->getDrawPose() == false)
				   {
					   beginEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore()), SkeletonDrawable::DrawPoseFieldMask);
						 SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore())->setDrawPose(true);
						endEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore()), SkeletonDrawable::DrawPoseFieldMask);
				   } 
				   else
				   {
					   beginEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore()), SkeletonDrawable::DrawPoseFieldMask);
						 SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore())->setDrawPose(false);
						endEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore()), SkeletonDrawable::DrawPoseFieldMask);
				   }
			   }
		   }
	   }

	   //Toggle axes
	   if(e.getKey() == KeyEvent::KEY_A)
	   {
		   if(Axes->getTravMask() == 0)
			   Axes->setTravMask(1);
		   else
			   Axes->setTravMask(0);
	   }

	   //Toggle grid
	   if(e.getKey() == KeyEvent::KEY_G)
	   {
			if(Grid->getTravMask() == 0)
			   Grid->setTravMask(1);
			else
			   Grid->setTravMask(0);
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
			osg::ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->update(e.getElapsedTime());

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
                                        "OpenSG 21LoadXMLSceneFromMayaWindow");


	//Print key command info
	std::cout << "\n\nKEY COMMANDS:" << std::endl;
	std::cout << "space   Play/Pause the animation" << std::endl;
	std::cout << "G       Show/Hide the grid" << std::endl;
	std::cout << "A       Show/Hide the axes" << std::endl;
	std::cout << "B       Show/Hide the bind pose skeleton" << std::endl;
	std::cout << "SHIFT-B Show/Hide the bind pose mesh" << std::endl;
	std::cout << "P       Show/Hide the current pose skeleton" << std::endl;
	std::cout << "SHIFT-P Show/Hide the current pose mesh" << std::endl;
	std::cout << "CTRL-Q  Exit\n\n" << std::endl;




	//Setup axes
	LineChunkPtr AxesLineChunk = LineChunk::create();
	beginEditCP(AxesLineChunk);
		AxesLineChunk->setWidth(0.0f);
		AxesLineChunk->setSmooth(true);
	endEditCP(AxesLineChunk);

	//Axes material
	ChunkMaterialPtr AxesMaterial = ChunkMaterial::create();
	beginEditCP(AxesMaterial, ChunkMaterial::ChunksFieldMask);
		AxesMaterial->addChunk(AxesLineChunk);
	endEditCP(AxesMaterial, ChunkMaterial::ChunksFieldMask);

	//Grid material
	ChunkMaterialPtr gridMaterial = ChunkMaterial::create();
	beginEditCP(gridMaterial, ChunkMaterial::ChunksFieldMask);
		gridMaterial->addChunk(AxesLineChunk);
	endEditCP(gridMaterial, ChunkMaterial::ChunksFieldMask);

	//Axes type
	GeoPTypesPtr axesType = GeoPTypesUI8::create();        
    beginEditCP(axesType, GeoPTypesUI8::GeoPropDataFieldMask);
    {
        axesType->addValue(GL_LINES);
    }
    endEditCP  (axesType, GeoPTypesUI8::GeoPropDataFieldMask);

	//Grid type
	GeoPTypesPtr gridType = GeoPTypesUI8::create();        
    beginEditCP(gridType, GeoPTypesUI8::GeoPropDataFieldMask);
    {
        gridType->addValue(GL_LINES);
    }
    endEditCP  (gridType, GeoPTypesUI8::GeoPropDataFieldMask);

	//Axes lens
	GeoPLengthsPtr axesLens = GeoPLengthsUI32::create();    
    beginEditCP(axesLens, GeoPLengthsUI32::GeoPropDataFieldMask);
    {
        axesLens->addValue(6);
    }
    endEditCP  (axesLens, GeoPLengthsUI32::GeoPropDataFieldMask);

	//Grid lens
	GeoPLengthsPtr gridLens = GeoPLengthsUI32::create();    
    beginEditCP(gridLens, GeoPLengthsUI32::GeoPropDataFieldMask);
    {
        gridLens->addValue(84);
    }
    endEditCP  (gridLens, GeoPLengthsUI32::GeoPropDataFieldMask);
	
	//Axes points
	GeoPositions3fPtr axesPnts = GeoPositions3f::create();
    beginEditCP(axesPnts, GeoPositions3f::GeoPropDataFieldMask);
    {
		// X-Axis
        axesPnts->addValue(Pnt3f(0,  0,  0));
        axesPnts->addValue(Pnt3f(15,  0,  0));
        
		// Y-Axis
		axesPnts->addValue(Pnt3f(0,  0,  0));
        axesPnts->addValue(Pnt3f(0,  15,  0));

		// Z-Axis
        axesPnts->addValue(Pnt3f(0,  0, 0));
        axesPnts->addValue(Pnt3f(0,  0, 15));
    }
    endEditCP  (axesPnts, GeoPositions3f::GeoPropDataFieldMask);

	//Grid points
	GeoPositions3fPtr gridPnts = GeoPositions3f::create();
    beginEditCP(gridPnts, GeoPositions3f::GeoPropDataFieldMask);
    {
		float height = 0;

		gridPnts->addValue(Pnt3f(-10, height, 0));
		if(height == 0)
			gridPnts->addValue(Pnt3f(0, height, 0));
		else
			gridPnts->addValue(Pnt3f(10, height, 0));

		gridPnts->addValue(Pnt3f(-10, height, 1));
		gridPnts->addValue(Pnt3f(10, height, 1));

		gridPnts->addValue(Pnt3f(-10, height, 2));
		gridPnts->addValue(Pnt3f(10, height, 2));

		gridPnts->addValue(Pnt3f(-10, height, 3));
		gridPnts->addValue(Pnt3f(10, height, 3));

		gridPnts->addValue(Pnt3f(-10, height, 4));
		gridPnts->addValue(Pnt3f(10, height, 4));

		gridPnts->addValue(Pnt3f(-10, height, 5));
		gridPnts->addValue(Pnt3f(10, height, 5));

		gridPnts->addValue(Pnt3f(-10, height, 6));
		gridPnts->addValue(Pnt3f(10, height, 6));

		gridPnts->addValue(Pnt3f(-10, height, 7));
		gridPnts->addValue(Pnt3f(10, height, 7));

		gridPnts->addValue(Pnt3f(-10, height, 8));
		gridPnts->addValue(Pnt3f(10, height, 8));

		gridPnts->addValue(Pnt3f(-10, height, 9));
		gridPnts->addValue(Pnt3f(10, height, 9));

		gridPnts->addValue(Pnt3f(-10, height, 10));
		gridPnts->addValue(Pnt3f(10, height, 10));

		gridPnts->addValue(Pnt3f(-10, height, -1));
		gridPnts->addValue(Pnt3f(10, height, -1));

		gridPnts->addValue(Pnt3f(-10, height, -2));
		gridPnts->addValue(Pnt3f(10, height, -2));

		gridPnts->addValue(Pnt3f(-10, height, -3));
		gridPnts->addValue(Pnt3f(10, height, -3));

		gridPnts->addValue(Pnt3f(-10, height, -4));
		gridPnts->addValue(Pnt3f(10, height, -4));

		gridPnts->addValue(Pnt3f(-10, height, -5));
		gridPnts->addValue(Pnt3f(10, height, -5));

		gridPnts->addValue(Pnt3f(-10, height, -6));
		gridPnts->addValue(Pnt3f(10, height, -6));

		gridPnts->addValue(Pnt3f(-10, height, -7));
		gridPnts->addValue(Pnt3f(10, height, -7));

		gridPnts->addValue(Pnt3f(-10, height, -8));
		gridPnts->addValue(Pnt3f(10, height, -8));

		gridPnts->addValue(Pnt3f(-10, height, -9));
		gridPnts->addValue(Pnt3f(10, height, -9));

		gridPnts->addValue(Pnt3f(-10, height, -10));
		gridPnts->addValue(Pnt3f(10, height, -10));


		gridPnts->addValue(Pnt3f(0, height, -10));
		if(height == 0)
			gridPnts->addValue(Pnt3f(0, height, 0));
		else
			gridPnts->addValue(Pnt3f(0, height, 10));
		
		gridPnts->addValue(Pnt3f(1, height, -10));
		gridPnts->addValue(Pnt3f(1, height, 10));

		gridPnts->addValue(Pnt3f(2, height, -10));
		gridPnts->addValue(Pnt3f(2, height, 10));

		gridPnts->addValue(Pnt3f(3, height, -10));
		gridPnts->addValue(Pnt3f(3, height, 10));

		gridPnts->addValue(Pnt3f(4, height, -10));
		gridPnts->addValue(Pnt3f(4, height, 10));

		gridPnts->addValue(Pnt3f(5, height, -10));
		gridPnts->addValue(Pnt3f(5, height, 10));

		gridPnts->addValue(Pnt3f(6, height, -10));
		gridPnts->addValue(Pnt3f(6, height, 10));

		gridPnts->addValue(Pnt3f(7, height, -10));
		gridPnts->addValue(Pnt3f(7, height, 10));

		gridPnts->addValue(Pnt3f(8, height, -10));
		gridPnts->addValue(Pnt3f(8, height, 10));

		gridPnts->addValue(Pnt3f(9, height, -10));
		gridPnts->addValue(Pnt3f(9, height, 10));

		gridPnts->addValue(Pnt3f(10, height, -10));
		gridPnts->addValue(Pnt3f(10, height, 10));

		gridPnts->addValue(Pnt3f(-1, height, -10));
		gridPnts->addValue(Pnt3f(-1, height, 10));

		gridPnts->addValue(Pnt3f(-2, height, -10));
		gridPnts->addValue(Pnt3f(-2, height, 10));

		gridPnts->addValue(Pnt3f(-3, height, -10));
		gridPnts->addValue(Pnt3f(-3, height, 10));

		gridPnts->addValue(Pnt3f(-4, height, -10));
		gridPnts->addValue(Pnt3f(-4, height, 10));

		gridPnts->addValue(Pnt3f(-5, height, -10));
		gridPnts->addValue(Pnt3f(-5, height, 10));

		gridPnts->addValue(Pnt3f(-6, height, -10));
		gridPnts->addValue(Pnt3f(-6, height, 10));

		gridPnts->addValue(Pnt3f(-7, height, -10));
		gridPnts->addValue(Pnt3f(-7, height, 10));

		gridPnts->addValue(Pnt3f(-8, height, -10));
		gridPnts->addValue(Pnt3f(-8, height, 10));

		gridPnts->addValue(Pnt3f(-9, height, -10));
		gridPnts->addValue(Pnt3f(-9, height, 10));

		gridPnts->addValue(Pnt3f(-10, height, -10));
		gridPnts->addValue(Pnt3f(-10, height, 10));

		
    }
    endEditCP  (gridPnts, GeoPositions3f::GeoPropDataFieldMask);
    
    //Axes normals
	GeoNormals3fPtr axesNorms = GeoNormals3f::create();
    beginEditCP(axesNorms, GeoNormals3f::GeoPropDataFieldMask);
        axesNorms->addValue(Vec3f( 0.0,0.0,1.0));
        axesNorms->addValue(Vec3f( 0.0,0.0,1.0));
        
		axesNorms->addValue(Vec3f( 0.0,0.0,1.0));
        axesNorms->addValue(Vec3f( 0.0,0.0,1.0));

        axesNorms->addValue(Vec3f( 1.0,0.0,0.0));
        axesNorms->addValue(Vec3f( 1.0,0.0,0.0));
    endEditCP(axesNorms, GeoNormals3f::GeoPropDataFieldMask);

	//Grid normals
	GeoNormals3fPtr gridNorms = GeoNormals3f::create();
    beginEditCP(gridNorms, GeoNormals3f::GeoPropDataFieldMask);
		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));

		gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
        gridNorms->addValue(Vec3f( 0.0,0.0,1.0));
    endEditCP(gridNorms, GeoNormals3f::GeoPropDataFieldMask);

	//Axes colors
	GeoColors3fPtr axesColors = GeoColors3f::create();
    beginEditCP(axesColors, GeoColors3f::GeoPropDataFieldMask);
        axesColors->addValue(Color3f( 1.0,0.0,0.0));
        axesColors->addValue(Color3f( 1.0,0.0,0.0));
        
		axesColors->addValue(Color3f( 0.0,1.0,0.0));
        axesColors->addValue(Color3f( 0.0,1.0,0.0));

        axesColors->addValue(Color3f( 0.0,0.0,1.0));
        axesColors->addValue(Color3f( 0.0,0.0,1.0));
    endEditCP(axesColors, GeoColors3f::GeoPropDataFieldMask);

	//Grid gridColors
	GeoColors3fPtr gridColors = GeoColors3f::create();
    beginEditCP(gridColors, GeoColors3f::GeoPropDataFieldMask);
		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));

		gridColors->addValue(Color3f( 0.5,0.5,0.5));
        gridColors->addValue(Color3f( 0.5,0.5,0.5));
    endEditCP(gridColors, GeoColors3f::GeoPropDataFieldMask);

	//Create axes geometry
	GeometryPtr axesGeo = Geometry::create();
    beginEditCP(axesGeo, Geometry::TypesFieldMask     |
                     Geometry::LengthsFieldMask   |
                     Geometry::PositionsFieldMask |
                     Geometry::NormalsFieldMask |
                     Geometry::MaterialFieldMask |
					 Geometry::ColorsFieldMask);
    {
        axesGeo->setTypes    (axesType);
        axesGeo->setLengths  (axesLens);
        axesGeo->setPositions(axesPnts);
        axesGeo->setNormals(axesNorms);
        axesGeo->setColors(axesColors);

        // assign a material to the geometry to make it visible. The details
        // of materials are defined later.
        axesGeo->setMaterial(AxesMaterial);   
    }
    endEditCP  (axesGeo, Geometry::TypesFieldMask     |
                     Geometry::LengthsFieldMask   |
                     Geometry::PositionsFieldMask |
                     Geometry::NormalsFieldMask |
                     Geometry::MaterialFieldMask |
					 Geometry::ColorsFieldMask  );

	//Create grid geometry
	GeometryPtr gridGeo = Geometry::create();
    beginEditCP(gridGeo, Geometry::TypesFieldMask     |
                     Geometry::LengthsFieldMask   |
                     Geometry::PositionsFieldMask |
                     Geometry::NormalsFieldMask |
                     Geometry::MaterialFieldMask |
					 Geometry::ColorsFieldMask);
    {
        gridGeo->setTypes    (gridType);
        gridGeo->setLengths  (gridLens);
        gridGeo->setPositions(gridPnts);
        gridGeo->setNormals(gridNorms);
        gridGeo->setColors(gridColors);

        // assign a material to the geometry to make it visible. The details
        // of materials are defined later.
        gridGeo->setMaterial(AxesMaterial);   
    }
    endEditCP  (gridGeo, Geometry::TypesFieldMask     |
                     Geometry::LengthsFieldMask   |
                     Geometry::PositionsFieldMask |
                     Geometry::NormalsFieldMask |
                     Geometry::MaterialFieldMask |
					 Geometry::ColorsFieldMask  );

	//Create unbound geometry Node
	Axes = osg::Node::create();
	beginEditCP(Axes, Node::CoreFieldMask);
		Axes->setCore(axesGeo);
	endEditCP(Axes, Node::CoreFieldMask);

	//Create unbound geometry Node
	Grid = osg::Node::create();
	beginEditCP(Grid, Node::CoreFieldMask);
		Grid->setCore(gridGeo);
	endEditCP(Grid, Node::CoreFieldMask);


	//Import scene from XML
	ChunkMaterialPtr ExampleMaterial;
	std::vector<SkeletonPtr> SkeletonPtrs;
	std::vector<SkeletonBlendedGeometryPtr> SkeletonBlendedGeometryPtrs;
	std::vector<GeometryPtr> GeometryPtrs;

	FCFileType::FCPtrStore NewContainers;
	NewContainers = FCFileHandler::the()->read(Path("./Data/21SceneFromMaya.xml"));
	FCFileType::FCPtrStore::iterator Itor;
    for(Itor = NewContainers.begin() ; Itor != NewContainers.end() ; ++Itor)
    {
		if( (*Itor)->getType() == (ChunkMaterial::getClassType()))
		{
			ExampleMaterial = (ChunkMaterial::Ptr::dcast(*Itor));
		}
		if( (*Itor)->getType() == (Skeleton::getClassType()))
		{
			SkeletonPtrs.push_back(Skeleton::Ptr::dcast(*Itor));
		}
		if( (*Itor)->getType() == (SkeletonBlendedGeometry::getClassType()))
		{
			SkeletonBlendedGeometryPtrs.push_back(SkeletonBlendedGeometry::Ptr::dcast(*Itor));
		}
		if( (*Itor)->getType().isDerivedFrom(SkeletonAnimation::getClassType()))
		{
			TheSkeletonAnimation = (Animation::Ptr::dcast(*Itor));
		}
		if( (*Itor)->getType() == (Geometry::getClassType()))
		{
			GeometryPtrs.push_back(Geometry::Ptr::dcast(*Itor));
		}
    }
	
	//Create unbound geometry Node (to show the mesh in its bind pose)
	for (int i(0); i < GeometryPtrs.size(); ++i)
	{
		NodePtr UnboundGeometry = Node::create();
		beginEditCP(UnboundGeometry, Node::CoreFieldMask | Node::TravMaskFieldMask);
			UnboundGeometry->setCore(GeometryPtrs[i]);
			UnboundGeometry->setTravMask(0);
		endEditCP(UnboundGeometry, Node::CoreFieldMask | Node::TravMaskFieldMask);

		UnboundGeometries.push_back(UnboundGeometry);
	}


	//Create skeleton nodes
	for (int i(0); i < SkeletonPtrs.size(); ++i)
	{
		//SkeletonDrawer
		SkeletonDrawablePtr ExampleSkeletonDrawable = osg::SkeletonDrawable::create();
		beginEditCP(ExampleSkeletonDrawable, SkeletonDrawable::SkeletonFieldMask | SkeletonDrawable::MaterialFieldMask | SkeletonDrawable::DrawPoseFieldMask | SkeletonDrawable::PoseColorFieldMask  | SkeletonDrawable::DrawBindPoseFieldMask | SkeletonDrawable::BindPoseColorFieldMask);
			ExampleSkeletonDrawable->setSkeleton(SkeletonPtrs[i]);
			ExampleSkeletonDrawable->setMaterial(AxesMaterial);
			ExampleSkeletonDrawable->setDrawPose(true);								  //By default we draw the current skeleton
			ExampleSkeletonDrawable->setPoseColor(Color4f(1.0, 0.0, 1.0, 1.0));       //Set color of current skeleton
			ExampleSkeletonDrawable->setDrawBindPose(false);                          //By default we don't draw the bind pose skeleton
			ExampleSkeletonDrawable->setBindPoseColor(Color4f(1.0, 1.0, 0.0, 1.0));   //Set color of bind pose skeleton
		endEditCP(ExampleSkeletonDrawable, SkeletonDrawable::SkeletonFieldMask | SkeletonDrawable::MaterialFieldMask | SkeletonDrawable::DrawPoseFieldMask | SkeletonDrawable::PoseColorFieldMask  | SkeletonDrawable::DrawBindPoseFieldMask | SkeletonDrawable::BindPoseColorFieldMask);
		
		//Skeleton Node
		NodePtr SkeletonNode = osg::Node::create();
		beginEditCP(SkeletonNode, Node::CoreFieldMask);
			SkeletonNode->setCore(ExampleSkeletonDrawable);
		endEditCP(SkeletonNode, Node::CoreFieldMask);

		SkeletonNodes.push_back(SkeletonNode);
	}



	//Create skeleton blended geometry nodes
	for (int i(0); i < SkeletonBlendedGeometryPtrs.size(); ++i)
	{
		NodePtr MeshNode = osg::Node::create();
		beginEditCP(MeshNode, Node::CoreFieldMask);
			MeshNode->setCore(SkeletonBlendedGeometryPtrs[i]);
		endEditCP(MeshNode, Node::CoreFieldMask);

		MeshNodes.push_back(MeshNode);
	}



    //Create Animation Advancer
    TheAnimationAdvancer = osg::ElapsedTimeAnimationAdvancer::create();
    osg::beginEditCP(TheAnimationAdvancer);
    osg::ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->setStartTime( 0.0 );
    osg::beginEditCP(TheAnimationAdvancer);


    //Add nodes to scene
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
		scene->addChild(Axes);
		scene->addChild(Grid);

		for (int i(0); i < SkeletonNodes.size(); ++i)
		{
			scene->addChild(SkeletonNodes[i]);
		}

		for (int i(0); i < UnboundGeometries.size(); ++i)
		{
			scene->addChild(UnboundGeometries[i]);
		}

		for (int i(0); i < MeshNodes.size(); ++i)
		{
			scene->addChild(MeshNodes[i]);
		}
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    mgr->setRoot(scene);


	//By default the animation is not paused
	animationPaused = false;

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