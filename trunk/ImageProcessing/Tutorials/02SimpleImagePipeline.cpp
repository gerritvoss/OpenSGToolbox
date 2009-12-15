
// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGImageFunctions.h>
#include <OpenSG/OSGTextureChunk.h>

// The general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

// Input
#include <OpenSG/Input/OSGWindowUtils.h>


#include <OpenSG/ImageProcessing/OSGImageProcessedForeground.h>
#include <OpenSG/ImageProcessing/OSGTextureSourceTextureFilter.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// Create a class to allow for the use of the Ctrl+q
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

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    TutorialKeyListener TheKeyListener;
    TutorialWindowEventProducer->addKeyListener(&TheKeyListener);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
	
										
    // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Main Scene Node and add the Torus
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
        scene->addChild(TorusGeometryNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    //Create the Image
    ImagePtr TheImage = Image::create();
    createNoise(TheImage, Image::OSG_RGBA_PF, 6, 1024);

    //Create the texture
    TextureChunkPtr TheTextureChunk = TextureChunk::create();
    beginEditCP(TheTextureChunk);
        TheTextureChunk->setImage(TheImage);

        TheTextureChunk->setMinFilter(GL_NEAREST);
        TheTextureChunk->setMagFilter(GL_NEAREST);

        TheTextureChunk->setWrapS(GL_CLAMP_TO_EDGE);
        TheTextureChunk->setWrapR(GL_CLAMP_TO_EDGE);

        TheTextureChunk->setScale(false);
        TheTextureChunk->setNPOTMatrixScale(true);
        
        TheTextureChunk->setEnvMode(GL_REPLACE);
    endEditCP(TheTextureChunk);

    //Create a Texture Source
    TextureSourceTextureFilterPtr TutorialTextureSourceTextureFilter = TextureSourceTextureFilter::create();
    beginEditCP(TutorialTextureSourceTextureFilter, TextureSourceTextureFilter::TextureFieldMask);
        TutorialTextureSourceTextureFilter->setTexture(TheTextureChunk);
    endEditCP(TutorialTextureSourceTextureFilter, TextureSourceTextureFilter::TextureFieldMask);
	
	// Create the ImageProcessed Foreground Object
    ImageProcessedForegroundPtr TutorialImageProcessedForeground = ImageProcessedForeground::create();

    beginEditCP(TutorialImageProcessedForeground, ImageProcessedForeground::FilterFieldMask);
        TutorialImageProcessedForeground->setFilter(TutorialTextureSourceTextureFilter);
    endEditCP(TutorialImageProcessedForeground, ImageProcessedForeground::FilterFieldMask);

    mgr->setRoot(scene);

    // Add the ImageProcessed Foreground Object to the Scene
    ViewportPtr TutorialViewport = mgr->getWindow()->getPort(0);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);
        TutorialViewport->getForegrounds().push_back(TutorialImageProcessedForeground);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "02SimpleImagePipeline");

    //Enter main Loop
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
