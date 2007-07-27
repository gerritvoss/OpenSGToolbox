// OpenSG Tutorial Example: Using the Flow Layout
//		to place Components 
//
// This tutorial explains how to place Buttons within a 
// frame utilizing the Flow Layout command to 
// manage the layout through the OSG User Interface library.
// 
// Includes: placing multiple buttons using Flow Layout

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
#include <OpenSG/UserInterface/OSGBevelBorder.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
//include the radio button classes
#include <OpenSG/UserInterface/OSGRadioButton.h>
#include <OpenSG/UserInterface/OSGRadioButtonGroup.h>

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
                                        "OpenSG 14RadioButton Window",
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
	// settings for the Button
	LookAndFeelManager::the()->getLookAndFeel()->init();




	/******************************************************
			
				Creates some Radio Button components and edit
				them

	******************************************************/
	RadioButtonPtr button1 = osg::RadioButton::create();
	RadioButtonPtr button2 = osg::RadioButton::create();
	RadioButtonPtr button3 = osg::RadioButton::create();

	beginEditCP(button1, Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask | Component::PreferredSizeFieldMask | Button::TextFieldMask);
		button1->setVerticalAlignment(VERTICAL_CENTER);
		button1->setHorizontalAlignment(HORIZONTAL_LEFT);
		button1->setPreferredSize(Vec2s(100, 50));
		button1->setText("Option 1");
	endEditCP(button1, Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask | Component::SizeFieldMask | Button::TextFieldMask);

	beginEditCP(button2,Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask | Component::SizeFieldMask | Button::TextFieldMask);
		button2->setVerticalAlignment(VERTICAL_CENTER);
		button2->setHorizontalAlignment(HORIZONTAL_LEFT);
		button2->setPreferredSize(Vec2s(100, 50));
		button2->setText("Option 2");
	endEditCP(button2, Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask | Component::SizeFieldMask | Button::TextFieldMask);

	beginEditCP(button3, Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask | Component::SizeFieldMask | Button::TextFieldMask);
		button3->setVerticalAlignment(VERTICAL_CENTER);
		button3->setHorizontalAlignment(HORIZONTAL_LEFT);
		button3->setPreferredSize(Vec2s(100, 50));
		button3->setText("Option 3");
	endEditCP(button3, Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask | Component::SizeFieldMask | Button::TextFieldMask);

	/***************************************************
					
				Create and populate the group of Radio Buttons
				Defining the group allows you to pick which radio
				buttons are tied together so that only one can be
				selected. Note that RadioButtonGroup is not a Field
				Container, so it is edited differently


	******************************************************/
	RadioButtonGroup buttonGroup;
	buttonGroup.addButton(button1);
	buttonGroup.addButton(button2);
	buttonGroup.addButton(button3);



	/******************************************************

		Radio Buttons are special toggle buttons.  When they are
		selected, any radio button in the same group is deselected,
		so there can only be one option selected.


	******************************************************/
	FlowLayoutPtr MainFrameLayout = osg::FlowLayout::create();
	// Determine whether the Layout is Horizontal (HORIZONTAL_ALIGNMENT) or
	// Vertical (VERTICAL_ALIGNMENT) and determine gap size, and determine
	// alignment along Horizontal and Vertical axis 
	beginEditCP(MainFrameLayout);
		// Determine the Horizontal and Vertical gaps between objects.
		// These gaps are absolute, and measured in pixels.
		MainFrameLayout->setHorizontalGap(0);
		MainFrameLayout->setVerticalGap(3);
		// Determine whether layout is arranged Vertically (VERTICAL_ALIGNMENT)
		// or Horizontally (HORIZONTAL_ALIGNMENT)
		MainFrameLayout->setAlignment(VERTICAL_ALIGNMENT);
		// MainFrameLayout->setAlignment(HORIZONTAL_ALIGNMENT);

		// The options for the following two functions are:
		// AXIS_MAX_ALIGNMENT, AXIS_CENTER_ALIGNMENT, and
		// AXIS_MIN_ALIGNMENT.

		// Determine alignment of entire layout; MAX puts it to the bottom (for vertical
		// overall layout) or right (horizontal overall layout), CENTER centers it, and
		// MIN does the opposite of MAX
		MainFrameLayout->setMajorAxisAlignment(AXIS_CENTER_ALIGNMENT);

		// Determine alignment of Components within Layout
		MainFrameLayout->setMinorAxisAlignment(AXIS_CENTER_ALIGNMENT);
	endEditCP(MainFrameLayout);
	
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
	   MainFrame->setLayout(MainFrameLayout);
	   MainFrame->setBackground(mainBackground);
	   MainFrame->setAllInsets(10);
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
