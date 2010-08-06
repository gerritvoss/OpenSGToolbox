// 
// OpenSGToolbox Tutorial: 10SkeletonDrawer 
//
// Demonstrates creating a simple skeleton. 
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
#include "OSGSimpleGeometry.h"

//Animation
#include "OSGSkeletonBlendedGeometry.h"
#include "OSGSkeletonDrawable.h"

#include "OSGRandomPoolManager.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerUnrecPtr TutorialWindow;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// Create a class to allow for keyboard shortcuts 
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventUnrecPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
       {
           TutorialWindow->closeWindow();
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
	
	//SkeletonDrawer System Material
	LineChunkUnrecPtr ExampleLineChunk = LineChunk::create();
    ExampleLineChunk->setWidth(4.0f);
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
	TransformRecPtr ExampleRootJoint = Transform::create();

    NodeRecPtr ExampleRootJointNode = makeNodeFor(ExampleRootJoint);

    //Add this joint to the skeleton
    ExampleSkeleton->pushToJoints(ExampleRootJointNode, Matrix());

    NodeRecPtr TempRootJointNode = ExampleRootJointNode;
    NodeRefPtr GeoNode = makeNodeFor(BoxGeometry);
    TempRootJointNode->addChild(GeoNode);

	Matrix TempMat;
	//Create a set of randomly placed child joints
	for (Real32 i = 0.0f; i < 5.0f; ++i)
	{
		TransformRecPtr ExampleChildJoint = Transform::create();
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
        ExampleChildJoint->setMatrix(TempMat);

		//Add ExampleChildJoint as a child to the previous joint	
        TempRootJointNode->addChild(ExampleChildJointNode);//add a Child to the root joint

		//ExampleChildJoint will be the next parent joint
		TempRootJointNode = ExampleChildJointNode;
        
        //Add this joint to the skeleton
        Matrix InvBind(TempRootJointNode->getToWorld());
        InvBind.invert();
        ExampleSkeleton->pushToJoints(ExampleChildJointNode, InvBind);
	}


    //SkeletonDrawer
    SkeletonDrawableUnrecPtr ExampleSkeletonDrawable = SkeletonDrawable::create();
    ExampleSkeletonDrawable->setSkeleton(ExampleSkeleton);
    ExampleSkeletonDrawable->setMaterial(ExampleMaterial);
	
	//Skeleton Particle System Node
	NodeUnrecPtr SkeletonNode = Node::create();
    SkeletonNode->setCore(ExampleSkeletonDrawable);


    // Make Main Scene Node and add the Torus
    NodeUnrecPtr scene = Node::create();
    scene->setCore(Group::create());
    scene->addChild(SkeletonNode);
    scene->addChild(ExampleRootJointNode);

    mgr->setRoot(scene);

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
            WinSize,
            "10SkeletonDrawer");

    //Main Loop
    TutorialWindow->mainLoop();

    osgExit();

    return 0;
}


// Callback functions

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

