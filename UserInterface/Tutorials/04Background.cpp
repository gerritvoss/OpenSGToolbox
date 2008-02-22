// OpenSG Tutorial Example: Creating a UIBackground
//
// This tutorial explains how to implement the 
// UIBackgrounds offered by the OSG User Interface 
// library and how to modify their features.
// 
// Includes: explanations and examples of how to create
// and use the six different backgrounds included in the
// OSG User Interface library.
//
// Note that the Active Border and UIBackground are not set, 
// meaning that if pressed, the Buttons revert to the default
// settings for UIBackground and Border.


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
#include <OpenSG/UserInterface/OSGInternalWindow.h>
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
void reshape(Vec2f Size);

// 04UIBackground Headers
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

            Create the UIBackgrounds.

    ******************************************************/

    ColorUIBackgroundPtr ExampleColorUIBackground = osg::ColorUIBackground::create();
    CompoundUIBackgroundPtr ExampleCompoundUIBackground = osg::CompoundUIBackground::create();
	EmptyUIBackgroundPtr ExampleEmptyUIBackground = osg::EmptyUIBackground::create();
    GradientUIBackgroundPtr ExampleGradientUIBackground = osg::GradientUIBackground::create();
    MaterialUIBackgroundPtr ExampleMaterialUIBackground = osg::MaterialUIBackground::create();
    TextureUIBackgroundPtr ExampleTextureUIBackground = osg::TextureUIBackground::create();
    PatternUIBackgroundPtr ExamplePatternUIBackground = osg::PatternUIBackground::create();

    /******************************************************

        The ColorUIBackground is a simple UIBackground
		having just a Color to it.

		-setColor(Color4f): Determine the Color of
			the UIBackground.

    ******************************************************/

    beginEditCP(ExampleColorUIBackground, ColorUIBackground::ColorFieldMask);
        ExampleColorUIBackground->setColor(Color4f(1.0,0.0,0.0,1.0));
    endEditCP(ExampleColorUIBackground, ColorUIBackground::ColorFieldMask);
	
    /******************************************************

            The CompoundUIBackground allows you to 
			combine multiple Backgrounds into one.

			The Backgrounds are added sequentially;
			so in this example the 
			ExampleTextureUIBackground would be added 
			first, and the ExampleGradientUIBackground
			rendered on top of it.  

			-getBackgrounds().addValue(BackgroundName):
				Adds a Background to the 
				CompoundBackground.

    ******************************************************/

    beginEditCP(ExampleCompoundUIBackground, CompoundUIBackground::BackgroundsFieldMask);
        ExampleCompoundUIBackground->getBackgrounds().addValue(ExampleTextureUIBackground);
        ExampleCompoundUIBackground->getBackgrounds().addValue(ExampleGradientUIBackground);
    endEditCP(ExampleCompoundUIBackground, CompoundUIBackground::BackgroundsFieldMask);
	
    /******************************************************

            The EmptyUIBackground is a Background
			with no attributes.

    ******************************************************/

	beginEditCP(ExampleEmptyUIBackground);
		// Nothing!
	endEditCP(ExampleEmptyUIBackground);
		
    /******************************************************

            The GradientUIBackground is a Background
			which displays a gradient of Color.

			-setColorStart(Color4f): Determines the 
				starting Color for the gradient.
			-setColorEnd(Color4f): Determines the
				ending Color for the gradient.
			-setAlignmnet(ENUM): Determines the
				gradient alignment.  Takes 
				HORIZONTAL_ALIGNMENT or 
				VERTICAL_ALIGNMENT arguments.

    ******************************************************/

    beginEditCP(ExampleGradientUIBackground, GradientUIBackground::ColorStartFieldMask | GradientUIBackground::ColorEndFieldMask | GradientUIBackground::AlignmentFieldMask);
         ExampleGradientUIBackground->setColorStart(Color4f(1.0, 0.0, 0.0, 1.0));
         ExampleGradientUIBackground->setColorEnd(Color4f(0.0, 0.0, 1.0, 0.5));
         ExampleGradientUIBackground->setAlignment(HORIZONTAL_ALIGNMENT);
    endEditCP(ExampleGradientUIBackground, GradientUIBackground::ColorStartFieldMask | GradientUIBackground::ColorEndFieldMask | GradientUIBackground::AlignmentFieldMask);
		
    /******************************************************

            The MaterialUIBackground is a Background
			which is created using a Material (also
			created here).

			-setMaterial(MaterialName): Determine
				which Material will be used to 
				create the Background.

    ******************************************************/    
	// Creates Material
    ChunkMaterialPtr UIBackgroundMaterial = ChunkMaterial::create();
    MaterialChunkPtr UIBackgroundMaterialChunk = MaterialChunk::create();
    beginEditCP(UIBackgroundMaterialChunk);
      UIBackgroundMaterialChunk->setAmbient(Color4f(1.0,0.0,0.0,1.0));
      UIBackgroundMaterialChunk->setDiffuse(Color4f(0.0,1.0,0.0,1.0));
      UIBackgroundMaterialChunk->setSpecular(Color4f(0.0,0.0,1.0,1.0));
    endEditCP(UIBackgroundMaterialChunk);

    beginEditCP(UIBackgroundMaterial, ChunkMaterial::ChunksFieldMask);
        UIBackgroundMaterial->addChunk(UIBackgroundMaterialChunk);
    endEditCP(UIBackgroundMaterial, ChunkMaterial::ChunksFieldMask);

	// Edit MaterialUIBackground
    beginEditCP(ExampleMaterialUIBackground, MaterialUIBackground::MaterialFieldMask);
        ExampleMaterialUIBackground->setMaterial(UIBackgroundMaterial);
    endEditCP(ExampleMaterialUIBackground, MaterialUIBackground::MaterialFieldMask);
		
    /******************************************************

            The TextureUIBackground is a Background
			which is created using a Texture (also
			created here).

			-setTexture(TextureName): Determine
				which Texture will be used to 
				create the Background.

    ******************************************************/   
	// Creates Texture from Image
    TextureChunkPtr UIBackgroundTextureChunk = TextureChunk::create();
    ImagePtr LoadedImage = ImageFileHandler::the().read("Data/Checker.jpg");    
    beginEditCP(UIBackgroundTextureChunk, TextureChunk::ImageFieldMask);
        UIBackgroundTextureChunk->setImage(LoadedImage);
    endEditCP(UIBackgroundTextureChunk, TextureChunk::ImageFieldMask);

	// Edit TextureUIBackground
    beginEditCP(ExampleTextureUIBackground, TextureUIBackground::TextureFieldMask);
        ExampleTextureUIBackground->setTexture(UIBackgroundTextureChunk);
    endEditCP(ExampleTextureUIBackground, TextureUIBackground::TextureFieldMask);

    /******************************************************

            The PatternUIBackground is a Background
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
    
   TextureChunkPtr UIBackgroundPatternChunk = TextureChunk::create();
   //ImagePtr LoadedImage = ImageFileHandler::the().read("Data/Checker.jpg");    
   beginEditCP(UIBackgroundPatternChunk, TextureChunk::ImageFieldMask | TextureChunk::WrapSFieldMask | TextureChunk::WrapTFieldMask);
        UIBackgroundPatternChunk->setImage(LoadedImage);
        UIBackgroundPatternChunk->setWrapS(GL_REPEAT);
        UIBackgroundPatternChunk->setWrapT(GL_CLAMP_TO_EDGE);
    endEditCP(UIBackgroundPatternChunk, TextureChunk::ImageFieldMask | TextureChunk::WrapSFieldMask | TextureChunk::WrapTFieldMask);

   beginEditCP(ExamplePatternUIBackground, PatternUIBackground::TextureFieldMask | PatternUIBackground::PatternSizeFieldMask | PatternUIBackground::VerticalAlignmentFieldMask | PatternUIBackground::HorizontalAlignmentFieldMask | PatternUIBackground::HorizontalRepeatFieldId | 
        PatternUIBackground::VerticalRepeatFieldMask | PatternUIBackground::HorizontalRepeatValueFieldMask | PatternUIBackground::VerticalRepeatValueFieldMask);
        ExamplePatternUIBackground->setTexture(UIBackgroundPatternChunk);
        ExamplePatternUIBackground->setPatternSize(Vec2f(50,50));
        ExamplePatternUIBackground->setVerticalAlignment(0.5);
        ExamplePatternUIBackground->setHorizontalAlignment(0.0);
        ExamplePatternUIBackground->setHorizontalRepeat(PatternUIBackground::PATTERN_REPEAT_BY_POINT);
        ExamplePatternUIBackground->setVerticalRepeat(PatternUIBackground::PATTERN_REPEAT_ABSOLUTE);
        ExamplePatternUIBackground->setHorizontalRepeatValue(1.0);
        ExamplePatternUIBackground->setVerticalRepeatValue(2.0);
    endEditCP(ExamplePatternUIBackground, PatternUIBackground::TextureFieldMask | PatternUIBackground::PatternSizeFieldMask | PatternUIBackground::VerticalAlignmentFieldMask | PatternUIBackground::HorizontalAlignmentFieldMask | PatternUIBackground::HorizontalRepeatFieldId | 
        PatternUIBackground::VerticalRepeatFieldMask | PatternUIBackground::HorizontalRepeatValueFieldMask | PatternUIBackground::VerticalRepeatValueFieldMask);
    
    /******************************************************

			Create and edit Button Components to
			display the UIBackgrounds.

    ******************************************************/

    ButtonPtr ExampleColorUIBackgroundButton = osg::Button::create();
    ButtonPtr ExampleCompoundUIBackgroundButton = osg::Button::create();
    ButtonPtr ExampleEmptyUIBackgroundButton = osg::Button::create();
    ButtonPtr ExampleGradientUIBackgroundButton = osg::Button::create();    
    ButtonPtr ExampleMaterialUIBackgroundButton = osg::Button::create();
    ButtonPtr ExampleTextureUIBackgroundButton = osg::Button::create();
    ButtonPtr ExamplePatternUIBackgroundButton = osg::Button::create();
    

    beginEditCP(ExampleColorUIBackgroundButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask);
        ExampleColorUIBackgroundButton->setText("Color UIBackground");
        ExampleColorUIBackgroundButton->setBackground(ExampleColorUIBackground);
        ExampleColorUIBackgroundButton->setActiveBackground(ExampleColorUIBackground);
        ExampleColorUIBackgroundButton->setRolloverBackground(ExampleColorUIBackground);
        ExampleColorUIBackgroundButton->setPreferredSize(Vec2f(150,50));
    endEditCP(ExampleColorUIBackgroundButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask);

    beginEditCP(ExampleCompoundUIBackgroundButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask);
        ExampleCompoundUIBackgroundButton->setText("Compound UIBackground");
        ExampleCompoundUIBackgroundButton->setBackground(ExampleCompoundUIBackground);
        ExampleCompoundUIBackgroundButton->setActiveBackground(ExampleCompoundUIBackground);
        ExampleCompoundUIBackgroundButton->setRolloverBackground(ExampleCompoundUIBackground);
        ExampleCompoundUIBackgroundButton->setPreferredSize(Vec2f(150,50));
    endEditCP(ExampleCompoundUIBackgroundButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask);

    beginEditCP(ExampleEmptyUIBackgroundButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask);
        ExampleEmptyUIBackgroundButton->setText("Empty UIBackground");
        ExampleEmptyUIBackgroundButton->setBackground(ExampleEmptyUIBackground);
        ExampleEmptyUIBackgroundButton->setActiveBackground(ExampleEmptyUIBackground);
        ExampleEmptyUIBackgroundButton->setRolloverBackground(ExampleEmptyUIBackground);
        ExampleEmptyUIBackgroundButton->setPreferredSize(Vec2f(150,50));
    endEditCP(ExampleEmptyUIBackgroundButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask);

    beginEditCP(ExampleGradientUIBackgroundButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask);
        ExampleGradientUIBackgroundButton->setText("Gradient UIBackground");
        ExampleGradientUIBackgroundButton->setBackground(ExampleGradientUIBackground);
        ExampleGradientUIBackgroundButton->setActiveBackground(ExampleGradientUIBackground);
        ExampleGradientUIBackgroundButton->setRolloverBackground(ExampleGradientUIBackground);
        ExampleGradientUIBackgroundButton->setPreferredSize(Vec2f(150,50));
    endEditCP(ExampleGradientUIBackgroundButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask);
    
    beginEditCP(ExampleMaterialUIBackgroundButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask |  Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask);
        ExampleMaterialUIBackgroundButton->setText("Material UIBackground");
        ExampleMaterialUIBackgroundButton->setBackground(ExampleMaterialUIBackground);
        ExampleMaterialUIBackgroundButton->setActiveBackground(ExampleMaterialUIBackground);
        ExampleMaterialUIBackgroundButton->setRolloverBackground(ExampleMaterialUIBackground);
        ExampleMaterialUIBackgroundButton->setPreferredSize(Vec2f(150,50));
        ExampleMaterialUIBackgroundButton->setTextColor(Color4f(1.0,1.0,1.0,1.0));
        ExampleMaterialUIBackgroundButton->setRolloverTextColor(Color4f(1.0,1.0,1.0,1.0));
        ExampleMaterialUIBackgroundButton->setActiveTextColor(Color4f(1.0,1.0,1.0,1.0));
    endEditCP(ExampleMaterialUIBackgroundButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask |  Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask);

    beginEditCP(ExampleTextureUIBackgroundButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask);
        ExampleTextureUIBackgroundButton->setText("Texture UIBackground");
        ExampleTextureUIBackgroundButton->setBackground(ExampleTextureUIBackground);
        ExampleTextureUIBackgroundButton->setActiveBackground(ExampleTextureUIBackground);
        ExampleTextureUIBackgroundButton->setRolloverBackground(ExampleTextureUIBackground);
        ExampleTextureUIBackgroundButton->setPreferredSize(Vec2f(150,50));
        ExampleTextureUIBackgroundButton->setTextColor(Color4f(0.0,1.0,0.0,1.0));
        ExampleTextureUIBackgroundButton->setRolloverTextColor(Color4f(0.0,1.0,0.0,1.0));
        ExampleTextureUIBackgroundButton->setActiveTextColor(Color4f(0.0,1.0,0.0,1.0));
    endEditCP(ExampleTextureUIBackgroundButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask |  Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask);
    
    beginEditCP(ExamplePatternUIBackgroundButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask |  Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask);
        ExamplePatternUIBackgroundButton->setText("Pattern UIBackground");
        ExamplePatternUIBackgroundButton->setBackground(ExamplePatternUIBackground);
        ExamplePatternUIBackgroundButton->setActiveBackground(ExamplePatternUIBackground);
        ExamplePatternUIBackgroundButton->setRolloverBackground(ExamplePatternUIBackground);
        ExamplePatternUIBackgroundButton->setPreferredSize(Vec2f(150,50));
        ExamplePatternUIBackgroundButton->setTextColor(Color4f(0.0,1.0,0.0,1.0));
        ExamplePatternUIBackgroundButton->setRolloverTextColor(Color4f(0.0,1.0,0.0,1.0));
        ExamplePatternUIBackgroundButton->setActiveTextColor(Color4f(0.0,1.0,0.0,1.0));
    endEditCP(ExamplePatternUIBackgroundButton, Button::TextFieldMask | Button::BackgroundFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBackgroundFieldMask | Button::PreferredSizeFieldMask |  Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask);


    
    /******************************************************

			Create a MainFrameBackground.  For almost
			all Tutorials, this is simply a 
			ColorUIBackground with a semi-transparent
			white Background.

    ******************************************************/

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorUIBackgroundPtr MainInternalWindowBackground = osg::ColorUIBackground::create();
    beginEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);

	//InternalWindow Layout
    LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);

       MainInternalWindow->getChildren().addValue(ExampleColorUIBackgroundButton);
       MainInternalWindow->getChildren().addValue(ExampleCompoundUIBackgroundButton);
       MainInternalWindow->getChildren().addValue(ExampleEmptyUIBackgroundButton);
       MainInternalWindow->getChildren().addValue(ExampleGradientUIBackgroundButton);
       MainInternalWindow->getChildren().addValue(ExampleMaterialUIBackgroundButton);
       MainInternalWindow->getChildren().addValue(ExampleTextureUIBackgroundButton);
       MainInternalWindow->getChildren().addValue(ExamplePatternUIBackgroundButton);
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
        TutorialViewport->getForegrounds().addValue(TutorialUIForeground);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);

    // Show the whole Scene
    mgr->showAll();
    TutorialWindowEventProducer->openWindow(Pnt2f(50,50),
                                        Vec2f(900,900),
                                        "OpenSG 04UIBackground Window");

    //Main Event Loop
    while(!ExitApp)
    {
        TutorialWindowEventProducer->update();
        TutorialWindowEventProducer->draw();
    }
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