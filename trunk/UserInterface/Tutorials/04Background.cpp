/*************************************************
Welcome to the 04Background tutorial.  In this
tutorial, you will see how to use the 
different Backgrounds available and add them
to components.  The following Backgrounds
are introduced:

    ColorLayer
    CompoundLayer
	EmptyLayer
    GradientLayer
    MaterialLayer
    TextureLayer
    PatternLayer

Backgrounds are used simply to provide a background
for various components.  Using combinations, very
complex possibilities exist.  As with 03Border, the 
easiest way to understand the base differences
is to simply run this tutorial.

The following all are shown and explained
within this tutorial (note the specific
requirements of each Border are not listed
here):

All Backgrounds:
    Creating Background
	Setting Color
	Specifying style
	Adding Backgrounds to components


These tutorials contain potentially relevant
information:



*************************************************/




// OpenSG Tutorial Example: Creating a Layer
//
// This tutorial explains how to implement the 
// Layers offered by the OSG User Interface 
// library and how to modify their features.
// 
// Includes: explanations and examples of how to create
// and use the six different backgrounds included in the
// OSG User Interface library.
//
// Note that the Active Border and Layer are not set, 
// meaning that if pressed, the Buttons revert to the default
// settings for Layer and Border.


// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>

// The general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

// Input
#include <OpenSG/Input/OSGWindowUtils.h>

// UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// 04Layer Headers
#include <OpenSG/UserInterface/OSGLayers.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
// Include Layer header files
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/OSGTextureChunk.h>
#include <OpenSG/OSGImageFileHandler.h>


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

    // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);
   
	// Make Main Scene Node and add the Torus
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
        scene->addChild(TorusGeometryNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    // Create the Graphics
    GraphicsPtr TutorialGraphics = osg::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

    /******************************************************

            Create the Layers.

    ******************************************************/

    ColorLayerPtr ExampleColorLayer = osg::ColorLayer::create();
    CompoundLayerPtr ExampleCompoundLayer = osg::CompoundLayer::create();
	EmptyLayerPtr ExampleEmptyLayer = osg::EmptyLayer::create();
    GradientLayerPtr ExampleGradientLayer = osg::GradientLayer::create();
    MaterialLayerPtr ExampleMaterialLayer = osg::MaterialLayer::create();
    TextureLayerPtr ExampleTextureLayer = osg::TextureLayer::create();
    PatternLayerPtr ExamplePatternLayer = osg::PatternLayer::create();

    /******************************************************

        The ColorLayer is a simple Layer
		having just a Color to it.

		-setColor(Color4f): Determine the Color of
			the Layer.

    ******************************************************/

    beginEditCP(ExampleColorLayer, ColorLayer::ColorFieldMask);
        ExampleColorLayer->setColor(Color4f(1.0,0.0,0.0,1.0));
    endEditCP(ExampleColorLayer, ColorLayer::ColorFieldMask);
	
    /******************************************************

            The CompoundLayer allows you to 
			combine multiple Backgrounds into one.

			The Backgrounds are added sequentially;
			so in this example the 
			ExampleTextureLayer would be added 
			first, and the ExampleGradientLayer
			rendered on top of it.  

			-getBackgrounds().push_back(BackgroundName):
				Adds a Background to the 
				CompoundBackground.

    ******************************************************/

    beginEditCP(ExampleCompoundLayer, CompoundLayer::BackgroundsFieldMask);
        ExampleCompoundLayer->getBackgrounds().push_back(ExampleTextureLayer);
        ExampleCompoundLayer->getBackgrounds().push_back(ExampleGradientLayer);
    endEditCP(ExampleCompoundLayer, CompoundLayer::BackgroundsFieldMask);
	
    /******************************************************

            The EmptyLayer is a Background
			with no attributes.

    ******************************************************/

	beginEditCP(ExampleEmptyLayer);
		// Nothing!
	endEditCP(ExampleEmptyLayer);
		
    /******************************************************

            The GradientLayer is a Background
			which displays a gradient of Color.

			-getColors().push_back(Color4f): Determines the 
				starting Color for the gradient.
			-getColors().push_back(Color4f): Determines the
				ending Color for the gradient.
			-setOrientation(ENUM): Determines the
				gradient alignment.  Takes 
				HORIZONTAL_ORIENTATION or 
				VERTICAL_ORIENTATION arguments.

    ******************************************************/

    beginEditCP(ExampleGradientLayer, GradientLayer::ColorsFieldMask | GradientLayer::StopsFieldMask | GradientLayer::StartPositionFieldMask | GradientLayer::EndPositionFieldMask | GradientLayer::SpreadMethodFieldMask);

		 ExampleGradientLayer->getColors().push_back(Color4f(1.0, 0.0, 0.0, 1.0));
		ExampleGradientLayer->getStops().push_back(0.0);
         ExampleGradientLayer->getColors().push_back(Color4f(0.0, 1.0, 0.0, 0.75));
		ExampleGradientLayer->getStops().push_back(0.5);
         ExampleGradientLayer->getColors().push_back(Color4f(0.0, 0.0, 1.0, 0.5));
		ExampleGradientLayer->getStops().push_back(1.0);
         ExampleGradientLayer->setStartPosition(Vec2f(0.2f,0.2f));
         ExampleGradientLayer->setEndPosition(Vec2f(.6f,0.6f));
         ExampleGradientLayer->setSpreadMethod(GradientLayer::SPREAD_REFLECT);
    endEditCP(ExampleGradientLayer, GradientLayer::ColorsFieldMask | GradientLayer::StopsFieldMask | GradientLayer::StartPositionFieldMask | GradientLayer::EndPositionFieldMask | GradientLayer::SpreadMethodFieldMask);
		
    /******************************************************

            The MaterialLayer is a Background
			which is created using a Material (also
			created here).

			-setMaterial(MaterialName): Determine
				which Material will be used to 
				create the Background.

    ******************************************************/    
	// Creates Material
    ChunkMaterialPtr LayerMaterial = ChunkMaterial::create();
    MaterialChunkPtr LayerMaterialChunk = MaterialChunk::create();
    beginEditCP(LayerMaterialChunk);
      LayerMaterialChunk->setAmbient(Color4f(1.0,0.0,0.0,1.0));
      LayerMaterialChunk->setDiffuse(Color4f(0.0,1.0,0.0,1.0));
      LayerMaterialChunk->setSpecular(Color4f(0.0,0.0,1.0,1.0));
    endEditCP(LayerMaterialChunk);

    beginEditCP(LayerMaterial, ChunkMaterial::ChunksFieldMask);
        LayerMaterial->addChunk(LayerMaterialChunk);
    endEditCP(LayerMaterial, ChunkMaterial::ChunksFieldMask);

	// Edit MaterialLayer
    beginEditCP(ExampleMaterialLayer, MaterialLayer::MaterialFieldMask);
        ExampleMaterialLayer->setMaterial(LayerMaterial);
    endEditCP(ExampleMaterialLayer, MaterialLayer::MaterialFieldMask);
		
    /******************************************************

            The TextureLayer is a Background
			which is created using a Texture (also
			created here).

			-setTexture(TextureName): Determine
				which Texture will be used to 
				create the Background.

    ******************************************************/   
	// Creates Texture from Image
    TextureChunkPtr LayerTextureChunk = TextureChunk::create();
    ImagePtr LoadedImage = ImageFileHandler::the().read("Data/Checker.jpg");    
    beginEditCP(LayerTextureChunk, TextureChunk::ImageFieldMask);
        LayerTextureChunk->setImage(LoadedImage);
    endEditCP(LayerTextureChunk, TextureChunk::ImageFieldMask);

	// Edit TextureLayer
    beginEditCP(ExampleTextureLayer, TextureLayer::TextureFieldMask);
        ExampleTextureLayer->setTexture(LayerTextureChunk);
    endEditCP(ExampleTextureLayer, TextureLayer::TextureFieldMask);

    /******************************************************

            The PatternLayer is a Background
			which is created using a Texture (also
			created here).

			-setTexture(TextureName): Determine
				which Texture will be used to 
				create the Background.
			-setPatternSize(Vec2f):
			-setVerticalAlignment():
			-setHorizontalAlignment():
			-setHorizontalRepeat():
			-setVerticalRepeat():
			-setHorizontalRepeatValue():
			-setVerticalRepeatValue():

    ******************************************************/  
    
   TextureChunkPtr LayerPatternChunk = TextureChunk::create();
   //ImagePtr LoadedImage = ImageFileHandler::the().read("Data/Checker.jpg");    
   beginEditCP(LayerPatternChunk, TextureChunk::ImageFieldMask | TextureChunk::WrapSFieldMask | TextureChunk::WrapTFieldMask);
        LayerPatternChunk->setImage(LoadedImage);
        LayerPatternChunk->setWrapS(GL_REPEAT);
        LayerPatternChunk->setWrapT(GL_CLAMP_TO_EDGE);
    endEditCP(LayerPatternChunk, TextureChunk::ImageFieldMask | TextureChunk::WrapSFieldMask | TextureChunk::WrapTFieldMask);

   beginEditCP(ExamplePatternLayer, PatternLayer::TextureFieldMask | PatternLayer::PatternSizeFieldMask | PatternLayer::VerticalAlignmentFieldMask | PatternLayer::HorizontalAlignmentFieldMask | PatternLayer::HorizontalRepeatFieldId | 
        PatternLayer::VerticalRepeatFieldMask | PatternLayer::HorizontalRepeatValueFieldMask | PatternLayer::VerticalRepeatValueFieldMask);
        ExamplePatternLayer->setTexture(LayerPatternChunk);
        ExamplePatternLayer->setPatternSize(Vec2f(50,50));
        ExamplePatternLayer->setVerticalAlignment(0.5);
        ExamplePatternLayer->setHorizontalAlignment(0.0);
        ExamplePatternLayer->setHorizontalRepeat(PatternLayer::PATTERN_REPEAT_BY_POINT);
        ExamplePatternLayer->setVerticalRepeat(PatternLayer::PATTERN_REPEAT_ABSOLUTE);
        ExamplePatternLayer->setHorizontalRepeatValue(1.0);
        ExamplePatternLayer->setVerticalRepeatValue(2.0);
    endEditCP(ExamplePatternLayer, PatternLayer::TextureFieldMask | PatternLayer::PatternSizeFieldMask | PatternLayer::VerticalAlignmentFieldMask | PatternLayer::HorizontalAlignmentFieldMask | PatternLayer::HorizontalRepeatFieldId | 
        PatternLayer::VerticalRepeatFieldMask | PatternLayer::HorizontalRepeatValueFieldMask | PatternLayer::VerticalRepeatValueFieldMask);
    
    /******************************************************

			Create and edit Button Components to
			display the Layers.

    ******************************************************/

    ButtonPtr ExampleColorLayerButton = osg::Button::create();
    ButtonPtr ExampleCompoundLayerButton = osg::Button::create();
    ButtonPtr ExampleEmptyLayerButton = osg::Button::create();
    ButtonPtr ExampleGradientLayerButton = osg::Button::create();    
    ButtonPtr ExampleMaterialLayerButton = osg::Button::create();
    ButtonPtr ExampleTextureLayerButton = osg::Button::create();
    ButtonPtr ExamplePatternLayerButton = osg::Button::create();
    

    beginEditCP(ExampleColorLayerButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask);
        ExampleColorLayerButton->setText("Color Layer");
        ExampleColorLayerButton->setBackground(ExampleColorLayer);
        ExampleColorLayerButton->setActiveBackground(ExampleColorLayer);
        ExampleColorLayerButton->setRolloverBackground(ExampleColorLayer);
        ExampleColorLayerButton->setPreferredSize(Vec2f(150,50));
    endEditCP(ExampleColorLayerButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask);

    beginEditCP(ExampleCompoundLayerButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask);
        ExampleCompoundLayerButton->setText("Compound Layer");
        ExampleCompoundLayerButton->setBackground(ExampleCompoundLayer);
        ExampleCompoundLayerButton->setActiveBackground(ExampleCompoundLayer);
        ExampleCompoundLayerButton->setRolloverBackground(ExampleCompoundLayer);
        ExampleCompoundLayerButton->setPreferredSize(Vec2f(150,50));
    endEditCP(ExampleCompoundLayerButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask);

    beginEditCP(ExampleEmptyLayerButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask);
        ExampleEmptyLayerButton->setText("Empty Layer");
        ExampleEmptyLayerButton->setBackground(ExampleEmptyLayer);
        ExampleEmptyLayerButton->setActiveBackground(ExampleEmptyLayer);
        ExampleEmptyLayerButton->setRolloverBackground(ExampleEmptyLayer);
        ExampleEmptyLayerButton->setPreferredSize(Vec2f(150,50));
    endEditCP(ExampleEmptyLayerButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask);

    beginEditCP(ExampleGradientLayerButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask);
        ExampleGradientLayerButton->setText("Gradient Layer");
        ExampleGradientLayerButton->setBackground(ExampleGradientLayer);
        ExampleGradientLayerButton->setActiveBackground(ExampleGradientLayer);
        ExampleGradientLayerButton->setRolloverBackground(ExampleGradientLayer);
        ExampleGradientLayerButton->setPreferredSize(Vec2f(150,50));
    endEditCP(ExampleGradientLayerButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask);
    
    beginEditCP(ExampleMaterialLayerButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask |  Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask);
        ExampleMaterialLayerButton->setText("Material Layer");
        ExampleMaterialLayerButton->setBackground(ExampleMaterialLayer);
        ExampleMaterialLayerButton->setActiveBackground(ExampleMaterialLayer);
        ExampleMaterialLayerButton->setRolloverBackground(ExampleMaterialLayer);
        ExampleMaterialLayerButton->setPreferredSize(Vec2f(150,50));
        ExampleMaterialLayerButton->setTextColor(Color4f(1.0,1.0,1.0,1.0));
        ExampleMaterialLayerButton->setRolloverTextColor(Color4f(1.0,1.0,1.0,1.0));
        ExampleMaterialLayerButton->setActiveTextColor(Color4f(1.0,1.0,1.0,1.0));
    endEditCP(ExampleMaterialLayerButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask |  Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask);

    beginEditCP(ExampleTextureLayerButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask);
        ExampleTextureLayerButton->setText("Texture Layer");
        ExampleTextureLayerButton->setBackground(ExampleTextureLayer);
        ExampleTextureLayerButton->setActiveBackground(ExampleTextureLayer);
        ExampleTextureLayerButton->setRolloverBackground(ExampleTextureLayer);
        ExampleTextureLayerButton->setPreferredSize(Vec2f(150,50));
        ExampleTextureLayerButton->setTextColor(Color4f(0.0,1.0,0.0,1.0));
        ExampleTextureLayerButton->setRolloverTextColor(Color4f(0.0,1.0,0.0,1.0));
        ExampleTextureLayerButton->setActiveTextColor(Color4f(0.0,1.0,0.0,1.0));
    endEditCP(ExampleTextureLayerButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask |  Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask);
    
    beginEditCP(ExamplePatternLayerButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask |  Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask);
        ExamplePatternLayerButton->setText("Pattern Layer");
        ExamplePatternLayerButton->setBackground(ExamplePatternLayer);
        ExamplePatternLayerButton->setActiveBackground(ExamplePatternLayer);
        ExamplePatternLayerButton->setRolloverBackground(ExamplePatternLayer);
        ExamplePatternLayerButton->setPreferredSize(Vec2f(150,50));
        ExamplePatternLayerButton->setTextColor(Color4f(0.0,1.0,0.0,1.0));
        ExamplePatternLayerButton->setRolloverTextColor(Color4f(0.0,1.0,0.0,1.0));
        ExamplePatternLayerButton->setActiveTextColor(Color4f(0.0,1.0,0.0,1.0));
    endEditCP(ExamplePatternLayerButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask |  Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask);


    
    /******************************************************

			Create a MainFrameBackground.  For almost
			all Tutorials, this is simply a 
			ColorLayer with a semi-transparent
			white Background.

    ******************************************************/

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);

	//InternalWindow Layout
    LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);

       MainInternalWindow->getChildren().push_back(ExampleColorLayerButton);
       MainInternalWindow->getChildren().push_back(ExampleCompoundLayerButton);
       MainInternalWindow->getChildren().push_back(ExampleEmptyLayerButton);
       MainInternalWindow->getChildren().push_back(ExampleGradientLayerButton);
       MainInternalWindow->getChildren().push_back(ExampleMaterialLayerButton);
       MainInternalWindow->getChildren().push_back(ExampleTextureLayerButton);
       MainInternalWindow->getChildren().push_back(ExamplePatternLayerButton);
	   MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
    endEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
    
    // Create the Drawing Surface
    UIDrawingSurfacePtr TutorialDrawingSurface = UIDrawingSurface::create();
    beginEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindowEventProducer);
    endEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
    
	TutorialDrawingSurface->openWindow(MainInternalWindow);

    // Create the UI Foreground Object
    UIForegroundPtr TutorialUIForeground = osg::UIForeground::create();

    beginEditCP(TutorialUIForeground, UIForeground::DrawingSurfaceFieldMask);
        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);
    endEditCP(TutorialUIForeground, UIForeground::DrawingSurfaceFieldMask);


    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
    mgr->setRoot(scene);

    // Add the UI Foreground Object to the Scene
    ViewportPtr TutorialViewport = mgr->getWindow()->getPort(0);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);
        TutorialViewport->getForegrounds().push_back(TutorialUIForeground);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);

    // Show the whole Scene
    mgr->showAll();

    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "01RubberBandCamera");

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
