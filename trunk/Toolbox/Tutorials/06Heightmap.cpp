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

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE


// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

bool ExitApp = false;

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

// Initialize GLUT & OpenSG and set up the scene
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

	
    TutorialWindowEventProducer->openWindow(Pnt2f(0,0),
                                        Vec2f(1280,1024),
                                        "OpenSG 06Heightmap Window");

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindowEventProducer->getWindow());
    
    //Make Torus Node
    NodePtr TorusNode = makeTorus(.5, 2, 32, 32);


	//Load in the Heightmap Image
	ImagePtr HeightMapImage = ImageFileHandler::the().read("./Data/ExampleHeightMap.png");

	//Make the Heightmap Geometry
	HeightmapGeometryPtr TutorialHeightmapGeo = HeightmapGeometry::create();
	beginEditCP(TutorialHeightmapGeo, HeightmapGeometry::HeightImageFieldMask | HeightmapGeometry::DimensionsFieldMask | HeightmapGeometry::SegmentsFieldMask | HeightmapGeometry::ScaleFieldMask | HeightmapGeometry::OffsetFieldMask | HeightmapGeometry::MaterialFieldMask);
		TutorialHeightmapGeo->setHeightImage(HeightMapImage);
		TutorialHeightmapGeo->setDimensions(Vec2f(200.0,200.0));
		TutorialHeightmapGeo->setSegments(Vec2f(100.0,100.0));
		TutorialHeightmapGeo->setScale(7.0);
		TutorialHeightmapGeo->setOffset(0.0);
		TutorialHeightmapGeo->setMaterial( SimpleMaterial::create() );
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
        scene->addChild(TorusNode);
        scene->addChild(TutorialHeightmapNode);
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    // tell the manager what to manage
    mgr->setRoot  (scene);

    // show the whole scene
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

