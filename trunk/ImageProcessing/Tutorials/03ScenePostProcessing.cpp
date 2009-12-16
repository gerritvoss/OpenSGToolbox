
// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGSolidBackground.h>
#include <OpenSG/OSGTextureChunk.h>
#include <OpenSG/OSGFBOViewport.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGPointLight.h>

#include <OpenSG/OSGImageFileHandler.h>

// The general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

// Input
#include <OpenSG/Input/OSGWindowUtils.h>


#include <OpenSG/ImageProcessing/OSGImageProcessedForeground.h>
#include <OpenSG/ImageProcessing/OSGFBOSourceTextureFilter.h>
#include <OpenSG/ImageProcessing/OSGShaderTextureFilter.h>

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

FBOViewportPtr createSceneFBO(void);

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
	

    // Make Main Scene Node and add the Torus
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    //Create a FBO Source
    FBOSourceTextureFilterPtr TutorialFBOSourceTextureFilter = FBOSourceTextureFilter::create();
    beginEditCP(TutorialFBOSourceTextureFilter, FBOSourceTextureFilter::FBOFieldMask);
        TutorialFBOSourceTextureFilter->setFBO(createSceneFBO());
        TutorialFBOSourceTextureFilter->setFBOSize(Vec2f(-1.0,-1.0));
    endEditCP(TutorialFBOSourceTextureFilter, FBOSourceTextureFilter::FBOFieldMask);

    //Create a Grayscale filter
    std::string GrayScaleFragProg = "uniform sampler2D Slot0Texture; void main() { gl_FragColor = vec4(vec3( dot(vec3(0.3,0.59,0.11), texture2D(Slot0Texture,gl_TexCoord[0].st).rgb)), 1.0); }";

    //Create a shader Filter
    ShaderTextureFilterPtr GrayscaleTextureFilter = ShaderTextureFilter::create();
    GrayscaleTextureFilter->attachSource(TutorialFBOSourceTextureFilter);
    GrayscaleTextureFilter->setFragmentSource(GrayScaleFragProg);
	
	// Create the ImageProcessed Foreground Object
    ImageProcessedForegroundPtr TutorialImageProcessedForeground = ImageProcessedForeground::create();

    beginEditCP(TutorialImageProcessedForeground, ImageProcessedForeground::FilterFieldMask);
        TutorialImageProcessedForeground->setFilter(GrayscaleTextureFilter);
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
//// Callback functions


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


FBOViewportPtr createSceneFBO(void)
{

    //Create Camera Beacon
    Matrix CameraMat;
    CameraMat.setTranslate(0.0f,0.0f,10.0f);
    TransformPtr CameraBeconCore = Transform::create();
    beginEditCP(CameraBeconCore, Transform::MatrixFieldMask);
        CameraBeconCore->setMatrix(CameraMat);
    endEditCP(CameraBeconCore, Transform::MatrixFieldMask);

    NodePtr CameraBeconNode = Node::create();
    beginEditCP(CameraBeconNode, Node::CoreFieldMask);
        CameraBeconNode->setCore(CameraBeconCore);
    endEditCP(CameraBeconNode, Node::CoreFieldMask);

    //Create Camera
    PerspectiveCameraPtr TheCamera = PerspectiveCamera::create();
    beginEditCP(TheCamera);
        TheCamera->setFov(deg2rad(60.0f));
        TheCamera->setAspect(1.0f);
        TheCamera->setNear(0.1f);
        TheCamera->setFar(100.0f);
        TheCamera->setBeacon(CameraBeconNode);
    endEditCP(TheCamera);
    
										
    // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    //Create Light Beacon
    Matrix LightMat;
    LightMat.setTranslate(0.0f,10.0f,1.0f);
    TransformPtr LightBeconCore = Transform::create();
    beginEditCP(LightBeconCore, Transform::MatrixFieldMask);
        LightBeconCore->setMatrix(LightMat);
    endEditCP(LightBeconCore, Transform::MatrixFieldMask);

    NodePtr LightBeconNode = Node::create();
    beginEditCP(LightBeconNode, Node::CoreFieldMask);
        LightBeconNode->setCore(LightBeconCore);
    endEditCP(LightBeconNode, Node::CoreFieldMask);

    //Create Light
    PointLightPtr TheLight = PointLight::create();
    beginEditCP(TheLight);
        TheLight->setBeacon(LightBeconNode);
    endEditCP(TheLight);

    NodePtr LightNode = Node::create();
    beginEditCP(LightNode, Node::CoreFieldMask);
        LightNode->setCore(TheLight);
        LightNode->addChild(TorusGeometryNode);
    endEditCP(LightNode, Node::CoreFieldMask);


    //Create Root
    NodePtr TheRoot = Node::create();
    beginEditCP(TheRoot, Node::CoreFieldMask);
        TheRoot->setCore(Group::create());
        TheRoot->addChild(CameraBeconNode);
        TheRoot->addChild(LightNode);
        TheRoot->addChild(LightBeconNode);
    endEditCP(TheRoot, Node::CoreFieldMask);

    //Create Background
    SolidBackgroundPtr TheBackground = SolidBackground::create();
    TheBackground->setColor(Color3f(1.0,0.0,0.0));

    //Create the Image
    ImagePtr TheImage = Image::create();
    TheImage->set(Image::OSG_RGB_PF,2,2);

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

    //Create FBO
    FBOViewportPtr TheFBO = FBOViewport::create();
    beginEditCP(TheFBO);
        TheFBO->setBackground(TheBackground);
        TheFBO->setRoot(TheRoot);
        TheFBO->setCamera(TheCamera);

        TheFBO->setEnabled(true);
        TheFBO->getTextures().push_back(TheTextureChunk);

        TheFBO->setStorageWidth(TheTextureChunk->getImage()->getWidth());
        TheFBO->setStorageHeight(TheTextureChunk->getImage()->getHeight());
        
        TheFBO->setSize(0,0,TheTextureChunk->getImage()->getWidth()-1, TheTextureChunk->getImage()->getHeight()-1);
    endEditCP(TheFBO);
    return TheFBO;
}
