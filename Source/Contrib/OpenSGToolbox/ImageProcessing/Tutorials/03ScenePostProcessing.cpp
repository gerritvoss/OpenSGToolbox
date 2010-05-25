
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
#include <OpenSG/OSGDepthClearBackground.h>
#include <OpenSG/OSGTextureChunk.h>
#include <OpenSG/OSGFBOViewport.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGPointLight.h>
#include <OpenSG/OSGDepthChunk.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/OSGChunkMaterial.h>

#include <OpenSG/OSGImageFileHandler.h>

// The general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

// Input
#include <OpenSG/Input/OSGWindowUtils.h>


#include <OpenSG/ImageProcessing/OSGImageProcessedForeground.h>
#include <OpenSG/ImageProcessing/OSGFBOSourceTextureFilter.h>
#include <OpenSG/ImageProcessing/OSGShaderTextureFilter.h>

#ifndef GL_ARB_depth_texture
    #define GL_DEPTH_COMPONENT16_ARB 0x81A5
    #define GL_DEPTH_COMPONENT24_ARB 0x81A6
    #define GL_DEPTH_COMPONENT32_ARB 0x81A7
    #define GL_TEXTURE_DEPTH_SIZE_ARB 0x884A
    #define GL_DEPTH_TEXTURE_MODE_ARB 0x884B
#endif

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;
TransformPtr RootTransformCore;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

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
   }

   virtual void keyReleased(const KeyEventPtr e)
   {
   }

   virtual void keyTyped(const KeyEventPtr e)
   {
   }
};

class TutorialUpdateListener : public UpdateListener
{
  public:
    virtual void update(const UpdateEventPtr e)
    {
        Real32 RotateRate(1.0f);

        Matrix RotMat;
        RotMat.setRotate(Quaternion(Vec3f(0.0,1.0,0.0),RotateRate*e->getElapsedTime()));

        Matrix NewMat(RootTransformCore->getMatrix());
        NewMat.multLeft(RotMat);

        beginEditCP(RootTransformCore, Transform::MatrixFieldMask);
            RootTransformCore->setMatrix(NewMat);
        endEditCP(RootTransformCore, Transform::MatrixFieldMask);
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

    TutorialUpdateListener TheUpdateListener;
    TutorialWindowEventProducer->addUpdateListener(&TheUpdateListener);

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
    beginEditCP(TutorialFBOSourceTextureFilter, FBOSourceTextureFilter::FBOFieldMask | FBOSourceTextureFilter::FBOSizeFieldMask);
        TutorialFBOSourceTextureFilter->setFBO(createSceneFBO());
        TutorialFBOSourceTextureFilter->setFBOSize(Vec2f(-1.0,-1.0));
    endEditCP(TutorialFBOSourceTextureFilter, FBOSourceTextureFilter::FBOFieldMask | FBOSourceTextureFilter::FBOSizeFieldMask);

    //Create a Grayscale filter
    std::string GrayScaleFragProg = "";
    GrayScaleFragProg += 
        "uniform sampler2D Slot0Texture;"
        "void main()"
        "{"
        //"    vec2 ScaleBias = vec2(2.0,-0.5);"
        //"    float depth = ScaleBias.x*(texture2D(Slot0Texture,gl_TexCoord[0].st).r +ScaleBias.y);"
        "    float ContrastAmount = 9.0;"
        "    float depth = 2.0*(texture2D(Slot0Texture,gl_TexCoord[0].st).r - 0.5);"
        "    depth = 0.5*pow(depth, ContrastAmount) + 0.5;"
        //"    float depth = 10.0*(texture2D(Slot0Texture,gl_TexCoord[0].st).r-0.9);"
        "    gl_FragColor = vec4(vec3(1.0-depth), 1.0);"
        "}";

    //Create a shader Filter
    ShaderTextureFilterPtr GrayscaleTextureFilter = ShaderTextureFilter::create();
    GrayscaleTextureFilter->attachSource(TutorialFBOSourceTextureFilter, 1, 0);
    GrayscaleTextureFilter->setFragmentSource(GrayScaleFragProg);
	
	// Create the ImageProcessed Foreground Object
    ImageProcessedForegroundPtr TutorialImageProcessedForeground = ImageProcessedForeground::create();

    beginEditCP(TutorialImageProcessedForeground, ImageProcessedForeground::FilterFieldMask | ImageProcessedForeground::OutputSlotFieldMask);
        TutorialImageProcessedForeground->setFilter(GrayscaleTextureFilter);
        //TutorialImageProcessedForeground->setFilter(TutorialFBOSourceTextureFilter);
        TutorialImageProcessedForeground->setOutputSlot(0);
    endEditCP(TutorialImageProcessedForeground, ImageProcessedForeground::FilterFieldMask | ImageProcessedForeground::OutputSlotFieldMask);

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
            "03ScenePostProcessing");

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
    CameraMat.setTranslate(0.0f,0.0f,4.0f);
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
    
    //Make the Material
    ChunkMaterialPtr TheMaterial = ChunkMaterial::create();

    beginEditCP(TheMaterial);
        TheMaterial->addChunk(MaterialChunk::create());
        TheMaterial->addChunk(DepthChunk::create());
    endEditCP(TheMaterial);
										
    // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 24, 48);

    beginEditCP(TorusGeometryNode->getCore());
        GeometryPtr::dcast(TorusGeometryNode->getCore())->setMaterial(TheMaterial);
    endEditCP(TorusGeometryNode->getCore());

    RootTransformCore = Transform::create();

    NodePtr TorusTransformNode = Node::create();
    beginEditCP(TorusTransformNode, Node::CoreFieldMask);
        TorusTransformNode->setCore(RootTransformCore);
        TorusTransformNode->addChild(TorusGeometryNode);
    endEditCP(TorusTransformNode, Node::CoreFieldMask);

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
        LightNode->addChild(TorusTransformNode);
    endEditCP(LightNode, Node::CoreFieldMask);


    //Create Root

    NodePtr TheRoot = Node::create();
    beginEditCP(TheRoot);
        TheRoot->setCore(Group::create());
        TheRoot->addChild(CameraBeconNode);
        TheRoot->addChild(LightNode);
        TheRoot->addChild(LightBeconNode);
    endEditCP(TheRoot);

    //Create Background
    SolidBackgroundPtr TheBackground = SolidBackground::create();
    TheBackground->setColor(Color3f(1.0,0.0,0.0));

    //DepthClearBackgroundPtr TheBackground = DepthClearBackground::create();

    //Create the Image
    ImagePtr TheColorImage = Image::create();
    TheColorImage->set(Image::OSG_RGB_PF,2,2);

    //Create the texture
    TextureChunkPtr TheColorTextureChunk = TextureChunk::create();
    beginEditCP(TheColorTextureChunk);
        TheColorTextureChunk->setImage(TheColorImage);

        TheColorTextureChunk->setMinFilter(GL_NEAREST);
        TheColorTextureChunk->setMagFilter(GL_NEAREST);

        TheColorTextureChunk->setWrapS(GL_CLAMP_TO_EDGE);
        TheColorTextureChunk->setWrapR(GL_CLAMP_TO_EDGE);

        TheColorTextureChunk->setScale(false);
        TheColorTextureChunk->setNPOTMatrixScale(true);
        
        TheColorTextureChunk->setEnvMode(GL_REPLACE);

    endEditCP(TheColorTextureChunk);

    //Create the Image
    ImagePtr TheDepthImage = Image::create();
    TheDepthImage->set(Image::OSG_I_PF,2,2);

    //Create the texture
    TextureChunkPtr TheDepthTextureChunk = TextureChunk::create();
    beginEditCP(TheDepthTextureChunk);
        TheDepthTextureChunk->setImage(TheDepthImage);

        TheDepthTextureChunk->setMinFilter(GL_NEAREST);
        TheDepthTextureChunk->setMagFilter(GL_NEAREST);

        TheDepthTextureChunk->setWrapS(GL_CLAMP_TO_EDGE);
        TheDepthTextureChunk->setWrapR(GL_CLAMP_TO_EDGE);

        TheDepthTextureChunk->setScale(false);
        TheDepthTextureChunk->setNPOTMatrixScale(true);
        
        TheDepthTextureChunk->setEnvMode(GL_REPLACE);

        TheDepthTextureChunk->setExternalFormat(GL_DEPTH_COMPONENT);
        TheDepthTextureChunk->setInternalFormat(GL_DEPTH_COMPONENT32_ARB);
        //TheDepthTextureChunk->setCompareMode(GL_NONE);
        //TheDepthTextureChunk->setCompareFunc(GL_LEQUAL);
        //TheDepthTextureChunk->setDepthMode(GL_INTENSITY);

    endEditCP(TheDepthTextureChunk);

    //Create FBO
    FBOViewportPtr TheFBO = FBOViewport::create();
    beginEditCP(TheFBO);
        TheFBO->setBackground(TheBackground);
        TheFBO->setRoot(TheRoot);
        TheFBO->setCamera(TheCamera);

        TheFBO->setEnabled(true);
        TheFBO->getTextures().push_back(TheColorTextureChunk);
        TheFBO->getTextures().push_back(TheDepthTextureChunk);

        TheFBO->setStorageWidth(TheColorTextureChunk->getImage()->getWidth());
        TheFBO->setStorageHeight(TheColorTextureChunk->getImage()->getHeight());
        
        TheFBO->setSize(0,0,TheColorTextureChunk->getImage()->getWidth()-1, TheColorTextureChunk->getImage()->getHeight()-1);
    endEditCP(TheFBO);
    return TheFBO;
}
