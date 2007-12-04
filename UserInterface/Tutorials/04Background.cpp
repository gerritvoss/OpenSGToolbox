// OpenSG Tutorial Example: Creating a Background
//
// This tutorial explains how to implement the 
// Backgrounds offered by the OSG User Interface 
// library and how to modify their features.
// 
// Includes: explanations and examples of how to create
// and use the six different backgrounds included in the
// OSG User Interface library.
//
// Note that the Active Border and Background are not set, 
// meaning that if pressed, the Buttons revert to the default
// settings for Background and Border.


// GLUT is used for window handling
#include <OpenSG/OSGGLUT.h>

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// The GLUT-OpenSG connection class
#include <OpenSG/OSGGLUTWindow.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/Input/OSGWindowAdapter.h>

// The general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

// Input
#include <OpenSG/Input/OSGWindowUtils.h>


// UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

bool ExitApp = false;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2s Size);

// 04Background Headers
#include <OpenSG/UserInterface/OSGUIBackgrounds.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
// Include UIDefines- used for HORITONAL_ALIGNMENT and VERTICAL_ALIGNMENT
#include <OpenSG/UserInterface/OSGUIDefines.h>
// Include UIBackground header files
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/OSGTextureChunk.h>
#include <OpenSG/OSGImageFileHandler.h>


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

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    WindowEventProducerPtr TheWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TheWindowEventProducer->initWindow();
    
    TheWindowEventProducer->setDisplayCallback(display);
    TheWindowEventProducer->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TheWindowEventProducer->addWindowListener(&TheTutorialWindowListener);


   // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);


    //Make Main Scene Node
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        scene->setCore(osg::Group::create());
        // add the torus as a child
        scene->addChild(TorusGeometryNode);
    }
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

	// Create the Graphics
	GraphicsPtr graphics = osg::Graphics2D::create();

	// Initialize the LookAndFeelManager to enable default settings
	LookAndFeelManager::the()->getLookAndFeel()->init();

	/******************************************************

					Creates 
   					the 
					different
					backgrounds

	******************************************************/

	// Creates a ColorUIBackgroundPtr (colorBackground)
	ColorUIBackgroundPtr colorBackground = osg::ColorUIBackground::create();

	// Creates a CompoundUIBackgroundPtr (compoundBackground)
	CompoundUIBackgroundPtr compoundBackground = osg::CompoundUIBackground::create();
	
	// Creates an EmptyUIBackgroundPtr (emptyBackground)
	EmptyUIBackgroundPtr emptyBackground = osg::EmptyUIBackground::create();

	// Create a GradientUIBackgroundPtr (gradientBackground)
	GradientUIBackgroundPtr gradientBackground = osg::GradientUIBackground::create();
	
	// Create a MaterialUIBackgroundPtr (materialBackground)
	MaterialUIBackgroundPtr materialBackground = osg::MaterialUIBackground::create();

	// Create a TextureUIBackgroundPtr (textureBackground)
	TextureUIBackgroundPtr textureBackground = osg::TextureUIBackground::create();
	
	// Create a PatternUIBackgroundPtr (patternBackground)
	PatternUIBackgroundPtr patternBackground = osg::PatternUIBackground::create();

	/******************************************************

				Define the backgrounds
				Every single option for each background
				type will be shown and set

	******************************************************/


	// Set colorBackground- set color
	beginEditCP(colorBackground, ColorUIBackground::ColorFieldMask);
		colorBackground->setColor(Color4f(1.0,0.0,0.0,1.0));
	endEditCP(colorBackground, ColorUIBackground::ColorFieldMask);

	// Set compoundBackground- use getBackgrounds().addValue(BACKGROUND_TO_BE_ADDED) 
	// function.  Backgrounds render in order, so in this case textureBackground is
	// rendered before gradientBackground.
	beginEditCP(compoundBackground, CompoundUIBackground::BackgroundsFieldMask);
		compoundBackground->getBackgrounds().addValue(textureBackground);
		compoundBackground->getBackgrounds().addValue(gradientBackground);
	endEditCP(compoundBackground, CompoundUIBackground::BackgroundsFieldMask);

	// Set emptyBackground (note that empty background is just that,
	// a background with no attributes
	beginEditCP(emptyBackground);
	endEditCP(emptyBackground);

	// Set gradientBackground- Set initial color, end color,
	// and orientation of gradient
	beginEditCP(gradientBackground, GradientUIBackground::ColorStartFieldMask | GradientUIBackground::ColorEndFieldMask | GradientUIBackground::AlignmentFieldMask);
		 gradientBackground->setColorStart( Color4f(1.0, 0.0, 0.0, 1.0));
		 gradientBackground->setColorEnd( Color4f(0.0, 0.0, 1.0, 0.5));
		 // The input into the following call is either
		 // HORIZONTAL_ALIGNMENT or VERTICAL_ALIGNMENT,
		 // which orient the gradient in the obvious manner 
		 gradientBackground->setAlignment(HORIZONTAL_ALIGNMENT);
	endEditCP(gradientBackground, GradientUIBackground::ColorStartFieldMask | GradientUIBackground::ColorEndFieldMask | GradientUIBackground::AlignmentFieldMask);
	
   // Set materialBackground- Set material
   ChunkMaterialPtr BackgroundMaterial = ChunkMaterial::create();
   MaterialChunkPtr BackgroundMaterialChunk = MaterialChunk::create();
	beginEditCP(BackgroundMaterialChunk);
      BackgroundMaterialChunk->setAmbient (  Color4f(1.0,0.0,0.0,1.0));
      BackgroundMaterialChunk->setDiffuse (  Color4f(0.0,1.0,0.0,1.0));
      BackgroundMaterialChunk->setSpecular(  Color4f(0.0,0.0,1.0,1.0));
	endEditCP(BackgroundMaterialChunk);

	beginEditCP(BackgroundMaterial, ChunkMaterial::ChunksFieldMask);
		BackgroundMaterial->addChunk(BackgroundMaterialChunk);
	endEditCP(BackgroundMaterial, ChunkMaterial::ChunksFieldMask);

	beginEditCP(materialBackground, MaterialUIBackground::MaterialFieldMask);
		materialBackground->setMaterial(BackgroundMaterial);
	endEditCP(materialBackground, MaterialUIBackground::MaterialFieldMask);

	// Set textureBackground- set texture
   TextureChunkPtr BackgroundTextureChunk = TextureChunk::create();
   ImagePtr LoadedImage = ImageFileHandler::the().read("Data/Checker.jpg");	
   beginEditCP(BackgroundTextureChunk, TextureChunk::ImageFieldMask);
		BackgroundTextureChunk->setImage(LoadedImage);
	endEditCP(BackgroundTextureChunk, TextureChunk::ImageFieldMask);

	beginEditCP(textureBackground, TextureUIBackground::TextureFieldMask);
		textureBackground->setTexture(BackgroundTextureChunk);
	endEditCP(textureBackground, TextureUIBackground::TextureFieldMask);

	
   TextureChunkPtr BackgroundPatternChunk = TextureChunk::create();
   //ImagePtr LoadedImage = ImageFileHandler::the().read("Data/Checker.jpg");	
   beginEditCP(BackgroundPatternChunk, TextureChunk::ImageFieldMask | TextureChunk::WrapSFieldMask | TextureChunk::WrapTFieldMask);
		BackgroundPatternChunk->setImage(LoadedImage);
		BackgroundPatternChunk->setWrapS(GL_REPEAT);
		BackgroundPatternChunk->setWrapT(GL_CLAMP_TO_EDGE);
	endEditCP(BackgroundPatternChunk, TextureChunk::ImageFieldMask | TextureChunk::WrapSFieldMask | TextureChunk::WrapTFieldMask);

	beginEditCP(patternBackground);
		patternBackground->setTexture(BackgroundPatternChunk);
		patternBackground->setPatternSize(Vec2s(50,50));
		patternBackground->setVerticalAlignment(0.5);
		patternBackground->setHorizontalAlignment(0.0);
		patternBackground->setHorizontalRepeat(PatternUIBackground::PATTERN_REPEAT_BY_POINT);
		patternBackground->setVerticalRepeat(PatternUIBackground::PATTERN_REPEAT_ABSOLUTE);
		patternBackground->setHorizontalRepeatValue(1.0);
		patternBackground->setVerticalRepeatValue(2.0);
	endEditCP(patternBackground);
	
	/******************************************************

		Create Button components to display each 
		of the varying backgrounds.  Buttons will 
		be placed via the Flow layout.

	******************************************************/
	ButtonPtr buttonColor = osg::Button::create();
	ButtonPtr buttonCompound = osg::Button::create();
	ButtonPtr buttonEmpty = osg::Button::create();
	ButtonPtr buttonGradient = osg::Button::create();	
	ButtonPtr buttonMaterial = osg::Button::create();
	ButtonPtr buttonTexture = osg::Button::create();
	ButtonPtr buttonPattern = osg::Button::create();
	
	// Set the visible text, border, and Background for
	// each of the various Button components
	beginEditCP(buttonColor, Button::TextFieldMask | Component::BackgroundFieldMask | Component::BorderFieldMask);
		buttonColor->setText("Color Background");
		buttonColor->setBackground(colorBackground);
		buttonColor->setActiveBackground(colorBackground);
		buttonColor->setRolloverBackground(colorBackground);
		buttonColor->setPreferredSize(Vec2s(150,50));
    endEditCP(buttonColor, Button::TextFieldMask | Component::BackgroundFieldMask | Component::BorderFieldMask);

	beginEditCP(buttonCompound, Button::TextFieldMask | Component::BackgroundFieldMask | Component::PreferredSizeFieldMask |Component::BorderFieldMask);
		buttonCompound->setText("Compound Background");
		buttonCompound->setBackground(compoundBackground);
		buttonCompound->setActiveBackground(compoundBackground);
		buttonCompound->setRolloverBackground(compoundBackground);
		buttonCompound->setPreferredSize(Vec2s(150,50));
		endEditCP(buttonCompound, Button::TextFieldMask | Component::BackgroundFieldMask | Component::PreferredSizeFieldMask |Component::BorderFieldMask);

	beginEditCP(buttonEmpty, Button::TextFieldMask | Component::BackgroundFieldMask | Component::BorderFieldMask);
		buttonEmpty->setText("Empty Background");
		buttonEmpty->setBackground(emptyBackground);
		buttonEmpty->setActiveBackground(emptyBackground);
		buttonEmpty->setRolloverBackground(emptyBackground);
		buttonEmpty->setPreferredSize(Vec2s(150,50));
	endEditCP(buttonEmpty, Button::TextFieldMask | Component::BackgroundFieldMask | Component::BorderFieldMask);

	beginEditCP(buttonGradient, Button::TextFieldMask | Component::BackgroundFieldMask | Component::PreferredSizeFieldMask |Component::BorderFieldMask);
		buttonGradient->setText("Gradient Background");
		buttonGradient->setBackground(gradientBackground);
		buttonGradient->setActiveBackground(gradientBackground);
		buttonGradient->setRolloverBackground(gradientBackground);
		buttonGradient->setPreferredSize(Vec2s(150,50));
    endEditCP(buttonGradient, Button::TextFieldMask | Component::BackgroundFieldMask | Component::PreferredSizeFieldMask |Component::BorderFieldMask);
	
	beginEditCP(buttonMaterial, Button::TextFieldMask | Component::BackgroundFieldMask | Component::BorderFieldMask | Button::TextColorFieldMask);
		buttonMaterial->setText("Material Background");
		buttonMaterial->setBackground(materialBackground);
		buttonMaterial->setActiveBackground(materialBackground);
		buttonMaterial->setRolloverBackground(materialBackground);
		buttonMaterial->setPreferredSize(Vec2s(150,50));
		buttonMaterial->setTextColor( Color4f(1.0,1.0,1.0,1.0) );
		buttonMaterial->setRolloverTextColor( Color4f(1.0,1.0,1.0,1.0) );
		buttonMaterial->setActiveTextColor( Color4f(1.0,1.0,1.0,1.0) );
		endEditCP(buttonMaterial, Button::TextFieldMask | Component::BackgroundFieldMask | Component::BorderFieldMask | Button::TextColorFieldMask);

	beginEditCP(buttonTexture, Button::TextFieldMask | Component::BackgroundFieldMask | Component::BorderFieldMask | Button::TextColorFieldMask);
		buttonTexture->setText("Texture Background");
		buttonTexture->setBackground(textureBackground);
		buttonTexture->setActiveBackground(textureBackground);
		buttonTexture->setRolloverBackground(textureBackground);
		buttonTexture->setPreferredSize(Vec2s(150,50));
		buttonTexture->setTextColor( Color4f(0.0,1.0,0.0,1.0) );
		buttonTexture->setRolloverTextColor( Color4f(0.0,1.0,0.0,1.0) );
		buttonTexture->setActiveTextColor( Color4f(0.0,1.0,0.0,1.0) );
	endEditCP(buttonTexture, Button::TextFieldMask | Component::BackgroundFieldMask | Component::BorderFieldMask | Button::TextColorFieldMask);
	
	beginEditCP(buttonPattern, Button::TextFieldMask | Component::BackgroundFieldMask | Component::BorderFieldMask | Button::TextColorFieldMask);
		buttonPattern->setText("Pattern Background");
		buttonPattern->setBackground(patternBackground);
		buttonPattern->setActiveBackground(patternBackground);
		buttonPattern->setRolloverBackground(patternBackground);
		buttonPattern->setPreferredSize(Vec2s(150,50));
		buttonPattern->setTextColor( Color4f(0.0,1.0,0.0,1.0) );
		buttonPattern->setRolloverTextColor( Color4f(0.0,1.0,0.0,1.0) );
		buttonPattern->setActiveTextColor( Color4f(0.0,1.0,0.0,1.0) );
	endEditCP(buttonPattern, Button::TextFieldMask | Component::BackgroundFieldMask | Component::BorderFieldMask | Button::TextColorFieldMask);



	// This creates a background for the MainFrame so that 
	// the button backgrounds are easier to see. The process
	// is identical, except the background is added to the 
	// MainFrame instead of a Button.
	// The background is a semi-transparent white background.
	ColorUIBackgroundPtr mainBackground = osg::ColorUIBackground::create();
	beginEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
		mainBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
	endEditCP(mainBackground, ColorUIBackground::ColorFieldMask);



	// Create The Main Frame
	FramePtr MainFrame = osg::Frame::create();
	LayoutPtr MainFrameLayout = osg::FlowLayout::create();
	beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);
	   // Assign the button to the mainframe so it will be displayed
	   // when the view is rendered.
	   MainFrame->getChildren().addValue(buttonColor);
	   MainFrame->getChildren().addValue(buttonCompound);
	   MainFrame->getChildren().addValue(buttonEmpty);
	   MainFrame->getChildren().addValue(buttonGradient);
	   MainFrame->getChildren().addValue(buttonMaterial);
	   MainFrame->getChildren().addValue(buttonTexture);
	   MainFrame->getChildren().addValue(buttonPattern);
	   MainFrame->setLayout(MainFrameLayout);
	   MainFrame->setBackground(mainBackground);
	endEditCP  (MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);

	//Create the Drawing Surface
	UIDrawingSurfacePtr drawingSurface = UIDrawingSurface::create();
	beginEditCP(drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask);
		drawingSurface->setGraphics(graphics);
		drawingSurface->setRootFrame(MainFrame);
	    drawingSurface->setEventProducer(TheWindowEventProducer);
    endEditCP  (drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask);
	
	// Create the UI Foreground Object
	UIForegroundPtr foreground = osg::UIForeground::create();

	beginEditCP(foreground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
	    foreground->setDrawingSurface(drawingSurface);
		foreground->setFramePositionOffset(Vec2s(0,0));
		foreground->setFrameBounds(Vec2f(0.5,0.5));
	   //Set the Event Producer for the DrawingSurface
	   //This is needed in order to get Mouse/Keyboard/etc Input to the UI DrawingSurface
    endEditCP  (foreground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(MainWindow );
    mgr->setRoot  (scene);

	// Add the UI Foreground Object to the Scene
	ViewportPtr viewport = mgr->getWindow()->getPort(0);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);
		viewport->getForegrounds().addValue(foreground);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);

    // show the whole scene
    mgr->showAll();

    TheWindowEventProducer->openWindow(Pnt2s(50,50),
                                        Vec2s(900,900),
                                        "OpenSG 04Background Window");

    //Main Event Loop
    while(!ExitApp)
    {
        TheWindowEventProducer->update();
        TheWindowEventProducer->draw();
    }
    osgExit();

    return 0;
}

// redraw the window
void display(void)
{
    mgr->redraw();
}

// react to size changes
void reshape(Vec2s Size)
{
    mgr->resize(Size.x(), Size.y());
}
