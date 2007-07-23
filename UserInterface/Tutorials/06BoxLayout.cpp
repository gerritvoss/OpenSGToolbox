// OpenSG Tutorial Example: Using the Box Layout
//		to place Components 
//
// This tutorial explains how to place buttons within a 
// frame utilizing the Box Layout command to 
// manage the layout through the OSG User Interface library.
// 
// Includes: placing multiple buttons using Box Layout

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

//UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
// Include BoxLayout header file
#include <OpenSG/UserInterface/OSGBoxLayout.h>

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
                                        "OpenSG 08BoxLayout Window",
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

	// Initialize the LookAndFeelManager to enable default 
	// settings for the Buttons
	LookAndFeelManager::the()->getLookAndFeel()->init();




	/******************************************************
			
				Creates some Button components

	******************************************************/
	ButtonPtr button1 = osg::Button::create();
	ButtonPtr button2 = osg::Button::create();
	ButtonPtr button3 = osg::Button::create();
	ButtonPtr button4 = osg::Button::create();


	/******************************************************

		Create Box Layout.  Box Layout arranges objects
		automatically within the Frame, so that the objects
		are evenly spaced within the Frame.

		Box Layout also causes all objects to have the same 
		height (if arranged Horizontally) or the same width
		(if arranged Vertically) using the maximum width of the
		objects in the Layout.  This overrides the specified 
		dimensions of the object, unless the object has a 
		Maximum or Minimum size set.  In this case, the object 
		size cannot be changed to greater than the Maximum size,
		or less than the Minimum size (it will still be changed,
		however it will not exceed the Max/Min size).

		You can experiment with this by changing the window 
		size, changing the size of the Buttons as shown 
		in 01Button, editing the Buttons, or adding more 
		Buttons to the view.

		Note that if the Frame is too small, the objects will 
		appear out of the Frame background.


	******************************************************/
	BoxLayoutPtr MainFrameLayout = osg::BoxLayout::create();

	// Determine whether the Layout is Horizontal (HORIZONTAL_ALIGNMENT) or
	// Vertical (VERTICAL_ALIGNMENT)
	beginEditCP(MainFrameLayout, BoxLayout::AlignmentFieldMask);
		MainFrameLayout->setAlignment(VERTICAL_ALIGNMENT);
		// MainFrameLayout->setAlignment(HORIZONTAL_ALIGNMENT);
	endEditCP(MainFrameLayout, BoxLayout::AlignmentFieldMask); 
	

	// Edit two different Buttons
	beginEditCP(button1, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask);
		button1->setPreferredSize( Vec2s(50,50) );
		// Set button to have a MaxSize.  This is never exceeded, therefore
		// even in BoxLayout it will not change to have a width of greater than
		// 80.  By commenting the setMaxSize line, button1 will have its width 
		// expanded to match the size of the largest object in the BoxLayout;
		// in this case button2.
		button1->setMaxSize( Vec2s (50, 50) );
	endEditCP(button1, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask);

	beginEditCP(button2, Button::PreferredSizeFieldMask);
		// Edit the PreferredSize of button2.  Because this is the largest
		// PreferredSize, all Buttons will have the same width unless they
		// have MaxSize limits (see above).  If setPreferredSize is commented, 
		// and setSize uncommented, note that button2 will no longer have the same
		// display size.
		button2->setPreferredSize( Vec2s(200,100) );
		
	endEditCP(button2, Button::PreferredSizeFieldMask);

 	// Create The Main Frame

	// Create Background to be used with the Main Frame
	ColorUIBackgroundPtr mainBackground = osg::ColorUIBackground::create();
	beginEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
		mainBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
	endEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
	
	FramePtr MainFrame = osg::Frame::create();
	beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);
	   // Add the buttons to the mainframe so they will be displayed
	   MainFrame->getChildren().addValue(button1);
	   MainFrame->getChildren().addValue(button2);
	   MainFrame->getChildren().addValue(button3);
	   MainFrame->getChildren().addValue(button4);
	   // Add the Layout to the MainFrame
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
