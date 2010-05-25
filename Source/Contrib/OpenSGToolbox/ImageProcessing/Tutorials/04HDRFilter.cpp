
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
#include <OpenSG/OSGGeoFunctions.h>

#include <OpenSG/OSGImageFileHandler.h>

// The general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

// Input
#include <OpenSG/Input/OSGWindowUtils.h>


#include <OpenSG/ImageProcessing/OSGImageProcessedForeground.h>
#include <OpenSG/ImageProcessing/OSGFBOSourceTextureFilter.h>
#include <OpenSG/ImageProcessing/OSGShaderTextureFilter.h>

#include <OpenSG/Toolbox/OSGBlinnMaterial.h>

#define GL_RGB16F 0x881B

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;
TransformPtr RootTransformCore;
PointLightPtr TheLight;
ShaderTextureFilterPtr HDRTextureFilter;

Real32 Exposure(1.0f);
Real32 Gamma(1.0f);
Real32 MaxLuminance(2.0f);

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
       switch(e->getKey())
       {
            case KeyEvent::KEY_UP:
                {
                    Color4f Col(TheLight->getDiffuse());
                    Col += Color4f(0.2,0.2,0.2,0.0);

                    std::cout << "Diffuse Color : " << Col  << std::endl;

                    beginEditCP(TheLight);
                        TheLight->setAmbient(Col*0.1);
                        TheLight->setDiffuse(Col);
                        TheLight->setSpecular(Col);
                    endEditCP(TheLight);

                    MaxLuminance =  Col.red();
                    std::cout << "MaxLuminance : " << MaxLuminance  << std::endl;
                    HDRTextureFilter->setUniformParameter("MaxLuminance", MaxLuminance);
                }
                break;
            case KeyEvent::KEY_DOWN:
                {
                    Color4f Col(TheLight->getDiffuse());
                    Col -= Color4f(0.2,0.2,0.2,0.0);
                    std::cout << "Diffuse Color : " << Col  << std::endl;

                    beginEditCP(TheLight);
                        TheLight->setDiffuse(Col);
                    endEditCP(TheLight);

                    MaxLuminance =  Col.red() + 1.0f;
                    std::cout << "MaxLuminance : " << MaxLuminance  << std::endl;
                    HDRTextureFilter->setUniformParameter("MaxLuminance", MaxLuminance);
                }
                break;
            case KeyEvent::KEY_RIGHT:
                {
                    Exposure +=  0.1f;
                    std::cout << "Exposure : " << Exposure  << std::endl;
                    HDRTextureFilter->setUniformParameter("Exposure", Exposure);
                }
                break;
            case KeyEvent::KEY_LEFT:
                {
                    Exposure -=  0.1f;
                    std::cout << "Exposure : " << Exposure  << std::endl;
                    HDRTextureFilter->setUniformParameter("Exposure", Exposure);
                }
                break;
            case KeyEvent::KEY_8:
                {
                    Gamma +=  0.05f;
                    std::cout << "Gamma : " << Gamma  << std::endl;
                    HDRTextureFilter->setUniformParameter("Gamma", Gamma);
                }
                break;
            case KeyEvent::KEY_7:
                {
                    Gamma -=  0.05f;
                    std::cout << "Gamma : " << Gamma  << std::endl;
                    HDRTextureFilter->setUniformParameter("Gamma", Gamma);
                }
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

    //Create a HDR filter
    std::string HDRFragProg = "";
    HDRFragProg += 
        "uniform sampler2D Slot0Texture;"
        "uniform float Exposure;"
        "uniform float MaxLuminance;"
        "uniform float Gamma;"
        "void main()"
        "{"
        "    vec3 Color = texture2D(Slot0Texture,gl_TexCoord[0].st).rgb;"
        //"    float Intensity = dot(vec3(0.3,0.59,0.11),Color);"
        "    float TonePercent = Exposure * ((Exposure/MaxLuminance + 1.0)/(Exposure + 1.0));"
        //Apply Tone Mapping And Gamma Correction
        "    Color = pow(Color * TonePercent, vec3(Gamma));"
        "    gl_FragColor = vec4(Color, 1.0);"
        "}";

    //Create a shader Filter
    HDRTextureFilter = ShaderTextureFilter::create();
    HDRTextureFilter->attachSource(TutorialFBOSourceTextureFilter, 0, 0);
    HDRTextureFilter->setFragmentSource(HDRFragProg);
    HDRTextureFilter->setUniformParameter("Exposure", Exposure);
    HDRTextureFilter->setUniformParameter("MaxLuminance", MaxLuminance);
    HDRTextureFilter->setUniformParameter("Gamma", Gamma);
	
	// Create the ImageProcessed Foreground Object
    ImageProcessedForegroundPtr TutorialImageProcessedForeground = ImageProcessedForeground::create();

    beginEditCP(TutorialImageProcessedForeground, ImageProcessedForeground::FilterFieldMask | ImageProcessedForeground::OutputSlotFieldMask);
        TutorialImageProcessedForeground->setFilter(HDRTextureFilter);
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
    BlinnMaterialPtr TheMaterial = BlinnMaterial::create();
    beginEditCP(TheMaterial);
        TheMaterial->setDiffuse(0.8);
        TheMaterial->setColor(Color3f(1.0,1.0,1.0));
        TheMaterial->setAmbientColor(Color3f(1.0,1.0,1.0));
        TheMaterial->setNumLights(1);
    endEditCP(TheMaterial);

										
    // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 24, 48);

    beginEditCP(TorusGeometryNode->getCore());
        GeometryPtr::dcast(TorusGeometryNode->getCore())->setMaterial(TheMaterial);
    endEditCP(TorusGeometryNode->getCore());
    calcVertexNormals(GeometryPtr::dcast(TorusGeometryNode->getCore()));
    calcVertexTangents(GeometryPtr::dcast(TorusGeometryNode->getCore()),0,Geometry::TexCoords7FieldId, Geometry::TexCoords6FieldId);

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
    TheLight = PointLight::create();
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
    TheColorImage->set(Image::OSG_RGB_PF,2,2,1,1,1,0.0f,0,Image::OSG_FLOAT16_IMAGEDATA);

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
        TheColorTextureChunk->setInternalFormat(GL_RGB16F);

    endEditCP(TheColorTextureChunk);


    //Create FBO
    FBOViewportPtr TheFBO = FBOViewport::create();
    beginEditCP(TheFBO);
        TheFBO->setBackground(TheBackground);
        TheFBO->setRoot(TheRoot);
        TheFBO->setCamera(TheCamera);

        TheFBO->setEnabled(true);
        TheFBO->getTextures().push_back(TheColorTextureChunk);

        TheFBO->setStorageWidth(TheColorTextureChunk->getImage()->getWidth());
        TheFBO->setStorageHeight(TheColorTextureChunk->getImage()->getHeight());
        
        TheFBO->setSize(0,0,TheColorTextureChunk->getImage()->getWidth()-1, TheColorTextureChunk->getImage()->getHeight()-1);
    endEditCP(TheFBO);
    return TheFBO;
}
