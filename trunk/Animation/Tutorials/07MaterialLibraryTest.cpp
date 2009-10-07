// 
// OpenSGToolbox Tutorial: 07MaterialLibraryTest
//
// Demonstrates use of Material Library
//

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGTextureChunk.h>
#include <OpenSG/OSGImageFileHandler.h>
#include <OpenSG/OSGSkyBackground.h>
#include <OpenSG/Toolbox/OSGMaterialLibrary.h>
#include <OpenSG/Toolbox/OSGMaterials.h>

// Input
#include <OpenSG/Input/OSGKeyListener.h>
#include <OpenSG/Input/OSGWindowAdapter.h>
#include <OpenSG/Input/OSGWindowUtils.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

BackgroundPtr createBackground(void);


// Create a class to allow for the use of the keyboard shortcuts 
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           TutorialWindowEventProducer->closeWindow();
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

    //Add Window Listener
    TutorialKeyListener TheKeyListener;
    TutorialWindowEventProducer->addKeyListener(&TheKeyListener);
    TutorialMouseListener TheTutorialMouseListener;
    TutorialMouseMotionListener TheTutorialMouseMotionListener;
    TutorialWindowEventProducer->addMouseListener(&TheTutorialMouseListener);
    TutorialWindowEventProducer->addMouseMotionListener(&TheTutorialMouseMotionListener);
	TutorialUpdateListener TheTutorialUpdateListener;
    TutorialWindowEventProducer->addUpdateListener(&TheTutorialUpdateListener);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);

	MaterialPtr ComplexGlass = createComplexGlassMaterial( 0.65, Vec3f(-0.02f,0.0f,0.02f), 1.0f, false, createCubeTextureChunk());

	//Torus Node
	GeometryPtr TorusGeometry = makeTorusGeo(3.0f,15.0f, 64,64);
	GeometryPtr CylinderGeometry = makeCylinderGeo(10.0f,10.0f,32,true,true,true);
	GeometryPtr SphereGeometry = makeSphereGeo(3,5.0f);
	GeometryPtr BoxGeometry = makeBoxGeo(5.0,5.0,5.0,4,4,4);

	beginEditCP(CylinderGeometry, Geometry::MaterialFieldMask);
		CylinderGeometry->setMaterial(MaterialLibrary::the()->createMaterial("ComplexGlass"));
	endEditCP(CylinderGeometry, Geometry::MaterialFieldMask);

	beginEditCP(TorusGeometry, Geometry::MaterialFieldMask);
		TorusGeometry->setMaterial(MaterialLibrary::the()->createMaterial("ComplexGlass"));
	endEditCP(TorusGeometry, Geometry::MaterialFieldMask);

	beginEditCP(SphereGeometry, Geometry::MaterialFieldMask);
		SphereGeometry->setMaterial(MaterialLibrary::the()->createMaterial("ComplexGlass"));
	endEditCP(SphereGeometry, Geometry::MaterialFieldMask);

	beginEditCP(BoxGeometry, Geometry::MaterialFieldMask);
		BoxGeometry->setMaterial(MaterialLibrary::the()->createMaterial("ComplexGlass"));
	endEditCP(BoxGeometry, Geometry::MaterialFieldMask);


	NodePtr TorusNode = Node::create();
    beginEditCP(TorusNode, Node::CoreFieldMask);
        TorusNode->setCore(TorusGeometry);
    endEditCP(TorusNode, Node::CoreFieldMask);

	NodePtr SphereNode = Node::create();
    beginEditCP(SphereNode, Node::CoreFieldMask);
		SphereNode->setCore(SphereGeometry);
    endEditCP(SphereNode, Node::CoreFieldMask);

	NodePtr CylinderNode = Node::create();
    beginEditCP(CylinderNode, Node::CoreFieldMask);
		CylinderNode->setCore(CylinderGeometry);
    endEditCP(CylinderNode, Node::CoreFieldMask);

	NodePtr BoxNode = Node::create();
    beginEditCP(BoxNode, Node::CoreFieldMask);
		BoxNode->setCore(BoxGeometry);
    endEditCP(BoxNode, Node::CoreFieldMask);

    // Make Main Scene Node
    NodePtr scene = Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(Group::create());
		scene->addChild(TorusNode);
		//scene->addChild(SphereNode);
		scene->addChild(CylinderNode);
		//scene->addChild(BoxNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    mgr->setRoot(scene);


	mgr->getWindow()->getPort(0)->setBackground(createBackground());

    // Show the whole Scene
    mgr->showAll();

    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,WinSize, "07MaterialLibrary");

    //Main Loop
    TutorialWindowEventProducer->mainLoop();

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


BackgroundPtr createBackground(void)
{
	ImagePtr CubeTextureFront = ImageFileHandler::the().read("Data/cell_front.jpg");
	ImagePtr CubeTextureBack = ImageFileHandler::the().read("Data/cell_back.jpg");
	ImagePtr CubeTextureLeft = ImageFileHandler::the().read("Data/cell_left.jpg");
	ImagePtr CubeTextureRight = ImageFileHandler::the().read("Data/cell_right.jpg");
	ImagePtr CubeTextureTop = ImageFileHandler::the().read("Data/cell_top.jpg");
	ImagePtr CubeTextureBottom = ImageFileHandler::the().read("Data/cell_bottom.jpg");

	TextureChunkPtr BGTop = TextureChunk::create();
	TextureChunkPtr BGBottom = TextureChunk::create();
	TextureChunkPtr BGLeft = TextureChunk::create();
	TextureChunkPtr BGRight = TextureChunk::create();
	TextureChunkPtr BGBack = TextureChunk::create();
	TextureChunkPtr BGFront = TextureChunk::create();

	beginEditCP(BGTop);
		BGTop->setImage(CubeTextureTop);

	endEditCP(BGTop);
	beginEditCP(BGBottom);
		BGBottom->setImage(CubeTextureBottom);
	endEditCP(BGBottom);
	beginEditCP(BGLeft);
		BGLeft->setImage(CubeTextureLeft);
	endEditCP(BGLeft);
	beginEditCP(BGRight);
		BGRight->setImage(CubeTextureRight);
	endEditCP(BGRight);
	beginEditCP(BGBack);
		BGBack->setImage(CubeTextureBack);
	endEditCP(BGBack);
	beginEditCP(BGFront);
		BGFront->setImage(CubeTextureFront);
	endEditCP(BGFront);

	SkyBackgroundPtr TheBackground = SkyBackground::create();
	beginEditCP(TheBackground);
		TheBackground->setBackTexture(BGFront);
		TheBackground->setFrontTexture(BGBack);
		TheBackground->setBottomTexture(BGBottom);
		TheBackground->setLeftTexture(BGLeft);
		TheBackground->setRightTexture(BGRight);
		TheBackground->setTopTexture(BGTop);
		TheBackground->setBoxInside(true);
	endEditCP(TheBackground);

	return TheBackground;
}

