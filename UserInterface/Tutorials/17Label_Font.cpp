// OpenSG Tutorial Example: Creating a Label and Creating Fonts
//
// This tutorial explains how to change Fonts and create
// Labels
// 
// Includes: Font and Label creation and settings

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>

// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

//Input
#include <OpenSG/Input/OSGWindowUtils.h>

// UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGUIDefines.h>

// Include Label and Font headerfiles
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGFont.h>


// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2s Size);


// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    WindowPtr MainWindow;
    WindowEventProducerPtr TheWindowEventProducer;
    createDefaultWindow(Pnt2s(50,50),
                                        Vec2s(900,900),
                                        "OpenSG 17Label/Font Window",
                                        MainWindow,
                                        TheWindowEventProducer);
    
    TheWindowEventProducer->setDisplayCallback(display);
    TheWindowEventProducer->setReshapeCallback(reshape);


    // Make Torus Node
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
	
	/******************************************************

			Create a Font.
			-setFamily(TYPE) determines what format the Font
				is (choices are: SANS, INSERT REMAINDER)
			-setSize(SIZE) determines the size of the 
				Font.
			-setFont(TextFace::STYLE) determines the 
				style the Font is.  Options are: (all 
				preceeded by "TextFace::" : STYLE_PLAIN,
				STYLE_BOLD, STYLE_ITALIC,


	******************************************************/

	FontPtr labelFont = Font::create();
	beginEditCP(labelFont);
		labelFont->setFamily("SANS");
		labelFont->setSize(25);
		labelFont->setStyle(TextFace::STYLE_PLAIN);
	endEditCP(labelFont);

	/******************************************************


		Create a few Labels and edit their characteristics.

		Note that all Component characteristics can be 
		modified as well (Background, PreferredSize, etc).

		-setFont(FONT_NAME) assigns a Font to the Label
		-setText("TEXT") displays TEXT on the Label (or
			whatever else is in the parenthesis
		-setVerticalAlignment(ALIGNMENT) determines the 
			alignment of the text on the Vertical Axis.
			Arguments are: VERTICAL_TOP, VERTICAL_CENTER,
			and VERTICAL_BOTTOM
		-setHorizontalAlignment(ALIGNMENT) determines the
			alignment of the text on the Horizontal Axis.
			Arguments are: HORIZONTAL_CENTER, HORIZONTAL_LEFT, 
			and HORIZONTAL_RIGHT

	******************************************************/

	LabelPtr label1 = osg::Label::create();
	// EditCP for Label ONLY settings
	beginEditCP(label1, Label::FontFieldMask | Label::TextFieldMask | Label::VerticalAlignmentFieldMask | Label::HorizontalAlignmentFieldMask);
		label1->setFont(labelFont);
		label1->setText("Sample Label");
		label1->setVerticalAlignment(VERTICAL_CENTER);
		label1->setHorizontalAlignment(HORIZONTAL_RIGHT);
	endEditCP(label1, Label::FontFieldMask | Label::TextFieldMask | Label::VerticalAlignmentFieldMask | Label::HorizontalAlignmentFieldMask);
	

	// SecondEditCP for Component settings
	beginEditCP(label1, Component::PreferredSizeFieldMask | Component::ForegroundColorFieldMask);
		label1->setPreferredSize( Vec2s(200, 50) );
		// Determine the Color the Font displays at
		label1->setForegroundColor( Color4f(0.1, 0.1, 0.1, 1.0) );
	endEditCP(label1, Component::PreferredSizeFieldMask | Component::ForegroundColorFieldMask);


	
	// Create The Main Frame
	// Create Background to be used with the Main Frame
	FramePtr MainFrame = osg::Frame::create();
	FlowLayoutPtr MainFrameLayout = osg::FlowLayout::create();

	beginEditCP(MainFrame, Frame::ChildrenFieldMask);
	   MainFrame->getChildren().addValue(label1);
	   MainFrame->setLayout(MainFrameLayout);
	endEditCP  (MainFrame, Frame::ChildrenFieldMask);

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
