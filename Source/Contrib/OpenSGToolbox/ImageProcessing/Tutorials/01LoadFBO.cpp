// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>

// Input
#include <OpenSG/Input/OSGKeyListener.h>
#include <OpenSG/Input/OSGWindowAdapter.h>
#include <OpenSG/Input/OSGWindowUtils.h>

//FBOs
#include <OpenSG/OSGFBOViewport.h>
#include <OpenSG/OSGTextureChunk.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/OSGChunkMaterial.h>

#include <OpenSG/Toolbox/OSGFCFileHandler.h>


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

FBOViewportPtr TheFBOViewport(NullFC);

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
       {
            TutorialWindowEventProducer->closeWindow();
       }

	   switch(e->getKey())
	   {
       case KeyEvent::KEY_T:
           break;
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

    Path FBOFilePath;
    if(argc < 2)
    {
        FWARNING(("No FBO file given!\n"));
        FBOFilePath = Path("./Data/01LoadFBO.xml");
    }
    else
    {
        FBOFilePath = Path(std::string(argv[1]));
    }
    std::cout << "Loading xml File: " << FBOFilePath << std::endl;

    FCFileType::FCPtrStore NewContainers;
    NewContainers = FCFileHandler::the()->read(FBOFilePath);

    FCFileType::FCPtrStore::iterator Itor;
    for(Itor = NewContainers.begin() ; Itor != NewContainers.end() ; ++Itor)
    {
        if( (*Itor)->getType() == FBOViewport::getClassType())
        {
            TheFBOViewport = FBOViewport::Ptr::dcast(*Itor);
        }
    }

    ChunkMaterialPtr BoxMaterial = ChunkMaterial::create();

    GeometryPtr BoxGeoCore = makeBoxGeo(1.0,1.0,1.0,2,2,2);
    beginEditCP(BoxGeoCore, Geometry::MaterialFieldMask);
        BoxGeoCore->setMaterial(BoxMaterial);
    endEditCP(BoxGeoCore, Geometry::MaterialFieldMask);

    NodePtr BoxGeoNode = Node::create();
    beginEditCP(BoxGeoNode, Node::CoreFieldMask);
        BoxGeoNode->setCore(BoxGeoCore);
    endEditCP(BoxGeoNode, Node::CoreFieldMask);

    NodePtr SceneNode = Node::create();
    beginEditCP(SceneNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        SceneNode->setCore(Group::create());
        SceneNode->addChild(BoxGeoNode);
    endEditCP(SceneNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

    // tell the manager what to manage
    mgr->setRoot  (SceneNode);

    // show the whole scene
    mgr->showAll();
    
    if(TheFBOViewport != NullFC)
    {
        //Add the texture chunk of the FBO to the Material for the box
        beginEditCP(BoxMaterial, ChunkMaterial::ChunksFieldMask);
            BoxMaterial->addChunk(TheFBOViewport->editTextures(0));
        endEditCP(BoxMaterial, ChunkMaterial::ChunksFieldMask);

        //Add The FBO Viewport the the Window
        beginEditCP(TheFBOViewport, FBOViewport::ParentFieldMask);
            TheFBOViewport->setParent(TutorialWindowEventProducer->getWindow());
        endEditCP(TheFBOViewport, FBOViewport::ParentFieldMask);

        beginEditCP(TutorialWindowEventProducer->getWindow());
            ViewportPtr vp = TutorialWindowEventProducer->getWindow()->getPort(0);
            addRefCP(vp);
            
            TutorialWindowEventProducer->getWindow()->subPort(0);

            //Put the FBO Vieport in front, so it is rendered first
            TutorialWindowEventProducer->getWindow()->addPort(TheFBOViewport);
            TutorialWindowEventProducer->getWindow()->addPort(vp   );
        endEditCP  (TutorialWindowEventProducer->getWindow());
    }

    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
                        WinSize,
                                        "07LoadFBO");

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

