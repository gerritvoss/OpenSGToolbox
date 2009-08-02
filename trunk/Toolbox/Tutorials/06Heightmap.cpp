// OpenSG Tutorial Example: Hello World
//
// Minimalistic OpenSG program
// 
// This is the shortest useful OpenSG program 
// (if you remove all the comments ;)
//
// It shows how to use OpenSG together with GLUT to create a little
// interactive scene viewer.
//

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>

#include <OpenSG/OSGSimpleMaterial.h>

#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGImageFileHandler.h>

// Input
#include <OpenSG/Input/OSGKeyListener.h>
#include <OpenSG/Input/OSGWindowAdapter.h>
#include <OpenSG/Input/OSGWindowUtils.h>

//Heightmap Geometry
#include <OpenSG/Toolbox/OSGHeightmapGeometry.h>
#include <OpenSG/Toolbox/OSGPerlinNoise.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE


// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;
bool statFlag(false);

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEvent& e)
   {
       if(e.getKey() == KeyEvent::KEY_Q && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
            TutorialWindowEventProducer->closeWindow();
       }

	   switch(e.getKey())
	   {
	   case KeyEvent::KEY_S:
		   statFlag = !statFlag;
		   mgr->setStatistics(statFlag);
		   break;
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

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

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
    mgr->setWindow(TutorialWindowEventProducer->getWindow());


	//Load in the Heightmap Image
	ImagePtr PerlinNoiseImage = createPerlinImage(Vec2s(256,256), Vec2f(10.0f,10.0f),0.5f,1.0f,Vec2f(0.0f,0.0f),0.25f,6,PERLIN_INTERPOLATE_COSINE,false,Image::OSG_L_PF, Image::OSG_UINT8_IMAGEDATA);

	//Make the Heightmap Geometry
	HeightmapGeometryPtr TutorialHeightmapGeo = HeightmapGeometry::create();
	beginEditCP(TutorialHeightmapGeo, HeightmapGeometry::HeightImageFieldMask | HeightmapGeometry::DimensionsFieldMask | HeightmapGeometry::SegmentsFieldMask | HeightmapGeometry::ScaleFieldMask | HeightmapGeometry::OffsetFieldMask | HeightmapGeometry::MaterialFieldMask);
		TutorialHeightmapGeo->setHeightImage(PerlinNoiseImage);
		TutorialHeightmapGeo->setDimensions(Vec2f(200.0,200.0));
		TutorialHeightmapGeo->setSegments(Vec2f(150.0,150.0));
		TutorialHeightmapGeo->setScale(20.0);
		TutorialHeightmapGeo->setOffset(0.0);
		TutorialHeightmapGeo->setMaterial( getDefaultMaterial() );
	endEditCP(TutorialHeightmapGeo, HeightmapGeometry::HeightImageFieldMask | HeightmapGeometry::DimensionsFieldMask | HeightmapGeometry::SegmentsFieldMask | HeightmapGeometry::ScaleFieldMask | HeightmapGeometry::OffsetFieldMask | HeightmapGeometry::MaterialFieldMask);

    //Make the Heightmap Node
    NodePtr TutorialHeightmapNode = Node::create();
    beginEditCP(TutorialHeightmapNode, Node::CoreFieldMask);
		TutorialHeightmapNode->setCore(TutorialHeightmapGeo);
    endEditCP  (TutorialHeightmapNode, Node::CoreFieldMask);

    //Make Main Scene Node
    NodePtr scene = Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
		scene->setCore(Group::create());
 
        // add the torus as a child
        scene->addChild(TutorialHeightmapNode);
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    // tell the manager what to manage
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();
    
    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
                        WinSize,
                                        "06Heightmap");

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

