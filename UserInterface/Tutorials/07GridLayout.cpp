// OpenSG Tutorial Example: Using the Grid Layout
//		to place Components 
//
// This tutorial explains how to place buttons within a 
// frame utilizing the Grid Layout command to 
// manage the layout through the OSG User Interface library.
// 
// Includes: placing multiple buttons using Grid Layout

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

// Include Grid Layout header file
#include <OpenSG/UserInterface/OSGGridLayout.h>

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
                                        "OpenSG 07GridLayout Window",
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
	ButtonPtr button5 = osg::Button::create();
	ButtonPtr button6 = osg::Button::create();


	/******************************************************

		Create Grid Layout.  Grid Layout arranges the 
		objects in a grid, with user specified rows, 
		columns, and gap size (conceptually imagine that
		an invisible grid is drawn, and components are 
		placed into that grid one per "box).

		Objects within the Grid Layout fill from left
		to right, and top to bottom, filling in each space
		sequentially.  The Grid Layout "boxes" are each the 
		same size as the largest object within the Layout. 
		
		Smaller objects are automatically resized to fit 
		this size unless they have Max/Min sizes assigned
		(similar to Box Layout).

		You can experiment with this by changing the size of 
		the Buttons as shown in 01Button, editing the Max/Min
		size of the Buttons, or adding more Buttons to the 
		view.

		Note that if the Frame is too small, the objects will 
		appear out of the Frame background.


	******************************************************/
	GridLayoutPtr MainFrameLayout = osg::GridLayout::create();

	beginEditCP(MainFrameLayout, GridLayout::RowsFieldMask | GridLayout::ColumnsFieldMask | GridLayout::HorizontalGapFieldMask | GridLayout::VerticalGapFieldMask);
		// Determine the number of Rows and Columns
		// in the Grid Layout
		MainFrameLayout->setRows(3);
		MainFrameLayout->setColumns(2);
		// Determine the Horizontal and Vertical
		// gaps in the Grid Layout
		MainFrameLayout->setHorizontalGap(4);
		MainFrameLayout->setVerticalGap(4);
	endEditCP(MainFrameLayout, GridLayout::RowsFieldMask | GridLayout::ColumnsFieldMask | GridLayout::HorizontalGapFieldMask | GridLayout::VerticalGapFieldMask);

	

	// Edit Buttons to change their sizes
	// Note that as with Box Layout, unless a setMaxSize
	// option is specified, the components are resized
	// to fit the grid "box" they are in
	beginEditCP(button1, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask);
		button1->setPreferredSize( Vec2s(50,50) );
		button1->setMaxSize( Vec2s(50,50) );
	endEditCP(button1, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask);

	beginEditCP(button2, Button::PreferredSizeFieldMask);
		 button2->setPreferredSize( Vec2s(200,100) );
	endEditCP(button2, Button::PreferredSizeFieldMask);
		
	// Note that button3 will be resized to be the same
	// size as button2, while button will not
	beginEditCP(button3, Button::PreferredSizeFieldMask);
		 button3->setPreferredSize( Vec2s(50,100) );
	endEditCP(button3, Button::PreferredSizeFieldMask);


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
	   MainFrame->getChildren().addValue(button5);
	   MainFrame->getChildren().addValue(button6);
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
