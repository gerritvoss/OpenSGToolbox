
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

#include <OpenSG/OSGImageFileHandler.h>

// The general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

// Input
#include <OpenSG/Input/OSGWindowUtils.h>


#include <OpenSG/ImageProcessing/OSGImageProcessedForeground.h>
#include <OpenSG/ImageProcessing/OSGTextureSourceTextureFilter.h>
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
    Path ImagePath("./Data/TutorialImage.jpg");
    ImagePtr TheImage = ImageFileHandler::the().read(ImagePath.string().c_str());

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

    //Create a Grayscale filter
    std::string GrayScaleFragProg = "uniform sampler2D Slot0Texture; void main() { gl_FragColor = vec4(vec3( dot(vec3(0.3,0.59,0.11), texture2D(Slot0Texture,gl_TexCoord[0].st).rgb)), 1.0); }";

    //Create a shader Filter
    ShaderTextureFilterPtr GrayscaleTextureFilter = ShaderTextureFilter::create();
    GrayscaleTextureFilter->attachSource(TutorialTextureSourceTextureFilter, 0, 0);
    GrayscaleTextureFilter->setFragmentSource(GrayScaleFragProg);

    //Create a Color Mult filter
    std::string ColorMultFragProg = "uniform sampler2D Slot0Texture; void main() { gl_FragColor = vec4(vec3(1.0,0.0,0.0) * texture2D(Slot0Texture,gl_TexCoord[0].st).rgb, 1.0); }";

    //Create a shader Filter
    ShaderTextureFilterPtr ColorMultTextureFilter = ShaderTextureFilter::create();
    ColorMultTextureFilter->attachSource(GrayscaleTextureFilter,0,0);
    ColorMultTextureFilter->setFragmentSource(ColorMultFragProg);

    
    ////Create a Blur filter
    //std::string BlurFragProg = "";
    //BlurFragProg += 
    //"uniform sampler2D Slot0Texture;"
    //"void main()"
    //"{"
    //"    vec2 offsets[9];"
    //"    offsets[0] = vec2(-0.000625,0.00111111111);"
    //"    offsets[1] = vec2(0.0,0.00111111111);"
    //"    offsets[2] = vec2(0.000625,0.00111111111);"
    //"    offsets[3] = vec2(-0.000625,0.0);"
    //"    offsets[4] = vec2(0.0,0.0);"
    //"    offsets[5] = vec2(0.0,0.0);"
    //"    offsets[6] = vec2(-0.000625,-0.00111111111);"
    //"    offsets[7] = vec2(0.0,-0.00111111111);"
    //"    offsets[8] = vec2(0.000625,-0.00111111111);"
    //"    vec4 kernel[9];"
    ////"    kernel[0] = vec4(0.0);"
    ////"    kernel[1] = vec4(0.0);"
    ////"    kernel[2] = vec4(0.0);"
    ////"    kernel[3] = vec4(0.0);"
    ////"    kernel[4] = vec4(1.0);"
    ////"    kernel[5] = vec4(0.0);"
    ////"    kernel[6] = vec4(0.0);"
    ////"    kernel[7] = vec4(0.0);"
    ////"    kernel[8] = vec4(0.0);"
    //"    kernel[0] = vec4(0.0);"
    //"    kernel[1] = vec4(0.15);"
    //"    kernel[2] = vec4(0.0);"
    //"    kernel[3] = vec4(0.15);"
    //"    kernel[4] = vec4(0.4);"
    //"    kernel[5] = vec4(0.15);"
    //"    kernel[6] = vec4(0.0);"
    //"    kernel[7] = vec4(0.15);"
    //"    kernel[8] = vec4(0.0);"
    //"    vec4 sum = vec4(0.0);"
    //"    int i;"
    //"    for(i = 0 ; i < 9 ; i++)"
    //"    {"
    //"        sum += kernel[i] * texture2D(Slot0Texture,gl_TexCoord[0].st + offsets[i]);"
    //"    }"
    //"    gl_FragColor = sum;"
    //"}";

    ////Create a shader Filter
    //ShaderTextureFilterPtr BlurTextureFilter = ShaderTextureFilter::create();
    //BlurTextureFilter->attachSource(ColorMultTextureFilter);
    //BlurTextureFilter->setFragmentSource(BlurFragProg);


	
	// Create the ImageProcessed Foreground Object
    ImageProcessedForegroundPtr TutorialImageProcessedForeground = ImageProcessedForeground::create();

    beginEditCP(TutorialImageProcessedForeground, ImageProcessedForeground::FilterFieldMask | ImageProcessedForeground::OutputSlotFieldMask);
        TutorialImageProcessedForeground->setFilter(ColorMultTextureFilter);
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
            "02SimpleImagePipeline");

    //Enter main Loop
    TutorialWindowEventProducer->mainLoop();

    osgExit();

    return 0;
}


//    "    kernel[0] = vec4(0.0);"
//    "    kernel[1] = vec4(0.15);"
//    "    kernel[2] = vec4(0.0);"
//    "    kernel[3] = vec4(0.15);"
//    "    kernel[4] = vec4(0.4);"
//    "    kernel[5] = vec4(0.15);"
//    "    kernel[6] = vec4(0.0);"
//    "    kernel[7] = vec4(0.15);"
//    "    kernel[8] = vec4(0.9);"
//    "    vec4 sum = vec4(0.0);"
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
