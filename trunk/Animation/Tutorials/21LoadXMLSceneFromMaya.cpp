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


// The pointer to the transformation
TransformPtr trans;

// The pointer to the geometry core
GeometryPtr geo;





// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);
void setupAnimation(BonePtr TheLeftHumerus,BonePtr TheLeftRadius,BonePtr TheLeftHand,BonePtr TheLeftFemur,BonePtr TheRightHumerus,BonePtr TheRightRadius,BonePtr TheRightHand,BonePtr TheRightFemur,BonePtr TheTorso, SkeletonPtr TheSkeleton);

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
                                        "OpenSG 21LoadXMLSceneFromMayaWindow");






	//Setup axes
	LineChunkPtr AxesLineChunk = LineChunk::create();
	beginEditCP(AxesLineChunk);
		AxesLineChunk->setWidth(0.0f);
		AxesLineChunk->setSmooth(true);
	endEditCP(AxesLineChunk);

	ChunkMaterialPtr AxesMaterial = ChunkMaterial::create();
	beginEditCP(AxesMaterial, ChunkMaterial::ChunksFieldMask);
		AxesMaterial->addChunk(AxesLineChunk);
		//AxesMaterial->addChunk(ExampleMaterialChunk);
		//AxesMaterial->addChunk(ExampleBlendChunk);
	endEditCP(AxesMaterial, ChunkMaterial::ChunksFieldMask);


	GeoPTypesPtr type = GeoPTypesUI8::create();        
    beginEditCP(type, GeoPTypesUI8::GeoPropDataFieldMask);
    {
        type->addValue(GL_LINES);
    }
    endEditCP  (type, GeoPTypesUI8::GeoPropDataFieldMask);

	GeoPLengthsPtr lens = GeoPLengthsUI32::create();    
    beginEditCP(lens, GeoPLengthsUI32::GeoPropDataFieldMask);
    {
        lens->addValue(90);
    }
    endEditCP  (lens, GeoPLengthsUI32::GeoPropDataFieldMask);
	 GeoPositions3fPtr pnts = GeoPositions3f::create();
    beginEditCP(pnts, GeoPositions3f::GeoPropDataFieldMask);
    {
		// X-Axis
        pnts->addValue(Pnt3f(0,  0,  0));
        pnts->addValue(Pnt3f(15,  0,  0));
        
		// Y-Axis
		pnts->addValue(Pnt3f(0,  0,  0));
        pnts->addValue(Pnt3f(0,  15,  0));

		// Z-Axis
        pnts->addValue(Pnt3f(0,  0, 0));
        pnts->addValue(Pnt3f(0,  0, 15));

		//GRID
		float height = 0;

		pnts->addValue(Pnt3f(-10, height, 0));
		if(height == 0)
			pnts->addValue(Pnt3f(0, height, 0));
		else
			pnts->addValue(Pnt3f(10, height, 0));

		pnts->addValue(Pnt3f(-10, height, 1));
		pnts->addValue(Pnt3f(10, height, 1));

		pnts->addValue(Pnt3f(-10, height, 2));
		pnts->addValue(Pnt3f(10, height, 2));

		pnts->addValue(Pnt3f(-10, height, 3));
		pnts->addValue(Pnt3f(10, height, 3));

		pnts->addValue(Pnt3f(-10, height, 4));
		pnts->addValue(Pnt3f(10, height, 4));

		pnts->addValue(Pnt3f(-10, height, 5));
		pnts->addValue(Pnt3f(10, height, 5));

		pnts->addValue(Pnt3f(-10, height, 6));
		pnts->addValue(Pnt3f(10, height, 6));

		pnts->addValue(Pnt3f(-10, height, 7));
		pnts->addValue(Pnt3f(10, height, 7));

		pnts->addValue(Pnt3f(-10, height, 8));
		pnts->addValue(Pnt3f(10, height, 8));

		pnts->addValue(Pnt3f(-10, height, 9));
		pnts->addValue(Pnt3f(10, height, 9));

		pnts->addValue(Pnt3f(-10, height, 10));
		pnts->addValue(Pnt3f(10, height, 10));

		pnts->addValue(Pnt3f(-10, height, -1));
		pnts->addValue(Pnt3f(10, height, -1));

		pnts->addValue(Pnt3f(-10, height, -2));
		pnts->addValue(Pnt3f(10, height, -2));

		pnts->addValue(Pnt3f(-10, height, -3));
		pnts->addValue(Pnt3f(10, height, -3));

		pnts->addValue(Pnt3f(-10, height, -4));
		pnts->addValue(Pnt3f(10, height, -4));

		pnts->addValue(Pnt3f(-10, height, -5));
		pnts->addValue(Pnt3f(10, height, -5));

		pnts->addValue(Pnt3f(-10, height, -6));
		pnts->addValue(Pnt3f(10, height, -6));

		pnts->addValue(Pnt3f(-10, height, -7));
		pnts->addValue(Pnt3f(10, height, -7));

		pnts->addValue(Pnt3f(-10, height, -8));
		pnts->addValue(Pnt3f(10, height, -8));

		pnts->addValue(Pnt3f(-10, height, -9));
		pnts->addValue(Pnt3f(10, height, -9));

		pnts->addValue(Pnt3f(-10, height, -10));
		pnts->addValue(Pnt3f(10, height, -10));


		pnts->addValue(Pnt3f(0, height, -10));
		if(height == 0)
			pnts->addValue(Pnt3f(0, height, 0));
		else
			pnts->addValue(Pnt3f(0, height, 10));
		
		pnts->addValue(Pnt3f(1, height, -10));
		pnts->addValue(Pnt3f(1, height, 10));

		pnts->addValue(Pnt3f(2, height, -10));
		pnts->addValue(Pnt3f(2, height, 10));

		pnts->addValue(Pnt3f(3, height, -10));
		pnts->addValue(Pnt3f(3, height, 10));

		pnts->addValue(Pnt3f(4, height, -10));
		pnts->addValue(Pnt3f(4, height, 10));

		pnts->addValue(Pnt3f(5, height, -10));
		pnts->addValue(Pnt3f(5, height, 10));

		pnts->addValue(Pnt3f(6, height, -10));
		pnts->addValue(Pnt3f(6, height, 10));

		pnts->addValue(Pnt3f(7, height, -10));
		pnts->addValue(Pnt3f(7, height, 10));

		pnts->addValue(Pnt3f(8, height, -10));
		pnts->addValue(Pnt3f(8, height, 10));

		pnts->addValue(Pnt3f(9, height, -10));
		pnts->addValue(Pnt3f(9, height, 10));

		pnts->addValue(Pnt3f(10, height, -10));
		pnts->addValue(Pnt3f(10, height, 10));

		pnts->addValue(Pnt3f(-1, height, -10));
		pnts->addValue(Pnt3f(-1, height, 10));

		pnts->addValue(Pnt3f(-2, height, -10));
		pnts->addValue(Pnt3f(-2, height, 10));

		pnts->addValue(Pnt3f(-3, height, -10));
		pnts->addValue(Pnt3f(-3, height, 10));

		pnts->addValue(Pnt3f(-4, height, -10));
		pnts->addValue(Pnt3f(-4, height, 10));

		pnts->addValue(Pnt3f(-5, height, -10));
		pnts->addValue(Pnt3f(-5, height, 10));

		pnts->addValue(Pnt3f(-6, height, -10));
		pnts->addValue(Pnt3f(-6, height, 10));

		pnts->addValue(Pnt3f(-7, height, -10));
		pnts->addValue(Pnt3f(-7, height, 10));

		pnts->addValue(Pnt3f(-8, height, -10));
		pnts->addValue(Pnt3f(-8, height, 10));

		pnts->addValue(Pnt3f(-9, height, -10));
		pnts->addValue(Pnt3f(-9, height, 10));

		pnts->addValue(Pnt3f(-10, height, -10));
		pnts->addValue(Pnt3f(-10, height, 10));

		
    }
    endEditCP  (pnts, GeoPositions3f::GeoPropDataFieldMask);
    
    //Normals
	GeoNormals3fPtr norms = GeoNormals3f::create();
    beginEditCP(norms, GeoNormals3f::GeoPropDataFieldMask);
        norms->addValue(Vec3f( 0.0,0.0,1.0));
        norms->addValue(Vec3f( 0.0,0.0,1.0));
        
		norms->addValue(Vec3f( 0.0,0.0,1.0));
        norms->addValue(Vec3f( 0.0,0.0,1.0));

        norms->addValue(Vec3f( 1.0,0.0,0.0));
        norms->addValue(Vec3f( 1.0,0.0,0.0));

		//GRID
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

		norms->addValue(Vec3f( 0.0,0.0,1.0));
        norms->addValue(Vec3f( 0.0,0.0,1.0));

		norms->addValue(Vec3f( 0.0,0.0,1.0));
        norms->addValue(Vec3f( 0.0,0.0,1.0));
    endEditCP(norms, GeoNormals3f::GeoPropDataFieldMask);

	 GeoColors3fPtr colors = GeoColors3f::create();
    beginEditCP(colors, GeoColors3f::GeoPropDataFieldMask);
        colors->addValue(Color3f( 1.0,0.0,0.0));
        colors->addValue(Color3f( 1.0,0.0,0.0));
        
		colors->addValue(Color3f( 0.0,1.0,0.0));
        colors->addValue(Color3f( 0.0,1.0,0.0));

        colors->addValue(Color3f( 0.0,0.0,1.0));
        colors->addValue(Color3f( 0.0,0.0,1.0));

		//GRID
		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));

		colors->addValue(Color3f( 0.5,0.5,0.5));
        colors->addValue(Color3f( 0.5,0.5,0.5));
    endEditCP(colors, GeoColors3f::GeoPropDataFieldMask);

	GeometryPtr axesGeo = Geometry::create();
    beginEditCP(axesGeo, Geometry::TypesFieldMask     |
                     Geometry::LengthsFieldMask   |
                     Geometry::PositionsFieldMask |
                     Geometry::NormalsFieldMask |
                     Geometry::MaterialFieldMask |
					 Geometry::ColorsFieldMask);
    {
        axesGeo->setTypes    (type);
        axesGeo->setLengths  (lens);
        axesGeo->setPositions(pnts);
        axesGeo->setNormals(norms);
        axesGeo->setColors(colors);

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

	//Create unbound geometry Node
	NodePtr Axes = Node::create();
	beginEditCP(Axes, Node::CoreFieldMask);
		Axes->setCore(axesGeo);
	endEditCP(Axes, Node::CoreFieldMask);





	


	//Import scene from XML
	ChunkMaterialPtr ExampleMaterial;
	
	SkeletonPtr ExampleSkeleton;

	std::vector<SkeletonPtr> SkeletonPtrs;

	std::vector<SkeletonBlendedGeometryPtr> SkeletonBlendedGeometryPtrs;

	std::vector<GeometryPtr> GeometryPtrs;


	FCFileType::FCPtrStore NewContainers;
	NewContainers = FCFileHandler::the()->read(Path("./Data/SkeletonExportTest.xml"));

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

	
	
	
	//Create unbound geometry Node
	std::vector<NodePtr> UnboundGeometries;
	for (int i(0); i < GeometryPtrs.size(); ++i)
	{
		NodePtr UnboundGeometry = Node::create();
		beginEditCP(UnboundGeometry, Node::CoreFieldMask);
			UnboundGeometry->setCore(GeometryPtrs[i]);
		endEditCP(UnboundGeometry, Node::CoreFieldMask);

		UnboundGeometries.push_back(UnboundGeometry);
	}


	//Skeletons
	std::vector<NodePtr> SkeletonNodes;
	for (int i(0); i < SkeletonPtrs.size(); ++i)
	{
		//SkeletonDrawer
		SkeletonDrawablePtr ExampleSkeletonDrawable = osg::SkeletonDrawable::create();
		beginEditCP(ExampleSkeletonDrawable, SkeletonDrawable::SkeletonFieldMask | SkeletonDrawable::MaterialFieldMask);
			ExampleSkeletonDrawable->setSkeleton(SkeletonPtrs[i]);
			ExampleSkeletonDrawable->setMaterial(AxesMaterial);
		endEditCP(ExampleSkeletonDrawable, SkeletonDrawable::SkeletonFieldMask | SkeletonDrawable::MaterialFieldMask);
		
		//Skeleton Node
		NodePtr SkeletonNode = osg::Node::create();
		beginEditCP(SkeletonNode, Node::CoreFieldMask);
			SkeletonNode->setCore(ExampleSkeletonDrawable);
		endEditCP(SkeletonNode, Node::CoreFieldMask);

		SkeletonNodes.push_back(SkeletonNode);
	}



	//Skeleton Blended Geometry Node
	std::vector<NodePtr> MeshNodes;
	for (int i(0); i < SkeletonBlendedGeometryPtrs.size(); ++i)
	{
		NodePtr MeshNode = osg::Node::create();
		beginEditCP(MeshNode, Node::CoreFieldMask);
			MeshNode->setCore(SkeletonBlendedGeometryPtrs[i]);
		endEditCP(MeshNode, Node::CoreFieldMask);

		MeshNodes.push_back(MeshNode);

		//SkeletonBlendedGeometryPtrs[i]->printStats();

		//SkeletonBlendedGeometryPtrs[i]->printInfluences();
	}



    //Animation Advancer
    TheAnimationAdvancer = osg::ElapsedTimeAnimationAdvancer::create();
    osg::beginEditCP(TheAnimationAdvancer);
    osg::ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->setStartTime( 0.0 );
    osg::beginEditCP(TheAnimationAdvancer);


    
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
		scene->addChild(Axes);

		for (int i(0); i < SkeletonNodes.size(); ++i)
		{
			scene->addChild(SkeletonNodes[i]);
		}

		for (int i(0); i < UnboundGeometries.size(); ++i)
		{
			//scene->addChild(UnboundGeometries[i]);
		}

		for (int i(0); i < MeshNodes.size(); ++i)
		{
			scene->addChild(MeshNodes[i]);
		}
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    mgr->setRoot(scene);


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