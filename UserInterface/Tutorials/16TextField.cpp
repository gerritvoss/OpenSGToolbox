// OpenSG Tutorial Example: Creating a Button Component
//
// This tutorial explains how to edit the basic features of
// a Button created in the OSG User Interface library.
// 
// Includes: Button PreferredSize, MaximumSize, MinimumSize, Font,
// Text,and adding a Button to a Scene.  Also note that clicking
// the Button causes it to appear pressed


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

// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

//Input
#include <OpenSG/Input/OSGWindowUtils.h>

//UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGFont.h>
#include <OpenSG/UserInterface/OSGTextField.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2s Size);

// Initialize WIN32 & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    WindowPtr MainWindow;
    WindowEventProducerPtr TheWindowEventProducer;
    createDefaultWindow(Pnt2s(50,50),
                                        Vec2s(550,550),
                                        "OpenSG 16TextField Window",
                                        MainWindow,
                                        TheWindowEventProducer);
    
    TheWindowEventProducer->setDisplayCallback(display);
    TheWindowEventProducer->setReshapeCallback(reshape);

   // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);


    // Make Main Scene Node
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

	// Create a TextField component
	TextFieldPtr textField = osg::TextField::create();

	// Create a simple Font to be used with the TextField
	FontPtr sampleFont = osg::Font::create();
    beginEditCP(sampleFont, Font::SizeFieldMask | Font::FamilyFieldMask | Font::GapFieldMask | Font::GlyphPixelSizeFieldMask | Font::TextureWidthFieldMask | Font::StyleFieldMask);
		sampleFont->setSize(16);
	endEditCP(sampleFont, Font::SizeFieldMask | Font::FamilyFieldMask | Font::GapFieldMask | Font::GlyphPixelSizeFieldMask | Font::TextureWidthFieldMask | Font::StyleFieldMask);

	/******************************************************


		Edit the TextField and determine its 
		characteristics.  A text field is a component 
		that allows you to enter text into the box via 
		keyboard input.  You can select text by	using 
		your mouse or pressing shift and the left and 
		right arrow keys.


	******************************************************/

	beginEditCP(textField, Component::MinSizeFieldMask | Component::MaxSizeFieldMask | Component::PreferredSizeFieldMask 
		| Component::ForegroundColorFieldMask | TextComponent::FontFieldMask | TextField::VerticalAlignmentFieldMask 
		| TextComponent::SelectionBoxColorFieldMask | TextComponent::SelectionTextColorFieldMask);
			// Determine initial size of TextField
		textField->setPreferredSize( Vec2s (100, 50) );
			// Determine the Font color for the Field
		textField->setForegroundColor( Color4f(0.0, 0.0, 0.0, 1.0) );
			// Determine the Box Color and the Selection Color
		textField->setSelectionBoxColor(Color4f(0.0, 0.0, 1.0, 1.0));
		textField->setSelectionTextColor(Color4f(1.0, 1.0, 1.0, 1.0));
			// Determine the font and initial text
		textField->setText("What");
		textField->setFont(sampleFont);
			// Determine the area that is to be selected at first 
			// so the selection would be "a" in this case
		textField->setSelectionStart(2);
		textField->setSelectionEnd(3);
			// Determine the initial alignment of the Text
			// from the top (top of the Text will be
			// 30% of the way down from the top of the
			// TextField in this case
		textField->setVerticalAlignment(.3);
	endEditCP(textField, Component::MinSizeFieldMask | Component::MaxSizeFieldMask | Component::PreferredSizeFieldMask 
		| Component::ForegroundColorFieldMask| TextComponent::FontFieldMask | TextField::VerticalAlignmentFieldMask
		| TextComponent::SelectionBoxColorFieldMask | TextComponent::SelectionTextColorFieldMask);
		
	// Create a TextField component
	TextFieldPtr textField2 = osg::TextField::create();
	beginEditCP(textField2, Component::MinSizeFieldMask | Component::MaxSizeFieldMask | Component::PreferredSizeFieldMask 
		| Component::ForegroundColorFieldMask | TextComponent::FontFieldMask | TextField::VerticalAlignmentFieldMask 
		| TextComponent::SelectionBoxColorFieldMask | TextComponent::SelectionTextColorFieldMask);
		textField2->setPreferredSize( Vec2s (100, 50) );
			// Determine the Font color for the Field
		textField2->setForegroundColor( Color4f(0.0, 0.0, 0.0, 1.0) );
			// Determine the Box Color and the Selection Color
		textField2->setSelectionBoxColor(Color4f(0.0, 0.0, 1.0, 1.0));
		textField2->setSelectionTextColor(Color4f(1.0, 1.0, 1.0, 1.0));
			// Determine the font and initial text
		textField2->setText("");
		textField2->setFont(sampleFont);
			// Set the area that is to be selected at first 
		textField2->setSelectionStart(2);
		textField2->setSelectionEnd(3);
			// Set the initial alignment of the Text
			// from the top (top of the Text will be
			// 30% of the way down from the top of the
			// TextField
		textField2->setVerticalAlignment(.3);
	endEditCP(textField2, Component::MinSizeFieldMask | Component::MaxSizeFieldMask | Component::PreferredSizeFieldMask 
		| Component::ForegroundColorFieldMask| TextComponent::FontFieldMask | TextField::VerticalAlignmentFieldMask
		| TextComponent::SelectionBoxColorFieldMask | TextComponent::SelectionTextColorFieldMask);
//	TextActionListener button1AL;
	
//	textField->addActionListener( &button1AL);


	// Create The Main Frame
	FramePtr MainFrame = osg::Frame::create();
	LayoutPtr MainFrameLayout = osg::FlowLayout::create();
	beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);
	   // Add TextField to MainFrame
	   MainFrame->getChildren().addValue(textField);
	   MainFrame->getChildren().addValue(textField2);
	   MainFrame->setLayout(MainFrameLayout);
	endEditCP  (MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);

	//Create the Drawing Surface
	UIDrawingSurfacePtr drawingSurface = UIDrawingSurface::create();
	beginEditCP(drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask);
		drawingSurface->setGraphics(graphics);
		drawingSurface->setRootFrame(MainFrame);
	    drawingSurface->setEventProducer(TheWindowEventProducer);
    endEditCP  (drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask);
	// Create the UI Foreground Object
	UIForegroundPtr foreground = osg::UIForeground::create();

	beginEditCP(foreground, UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
	    foreground->setDrawingSurface(drawingSurface);
		foreground->setFramePositionOffset(Vec2s(0,0));
		foreground->setFrameBounds(Vec2f(0.5,0.5));
	   //Set the Event Producer for the DrawingSurface
	   //This is needed in order to get Mouse/Keyboard/etc Input to the UI DrawingSurface
    endEditCP  (foreground, UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);


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

    openWindow(TheWindowEventProducer);

    return 0;
}

//
// callback functions
//

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
