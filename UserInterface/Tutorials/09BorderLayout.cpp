// OpenSG Tutorial Example: Using the Border Layout
//		to place Components 
//
// This tutorial explains how to place buttons within a 
// frame utilizing the Border Layout command to 
// manage the layout through the OSG User Interface library.
// 
// Includes: placing multiple buttons using Border Layout

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
#include <OpenSG/UserInterface/OSGFrame.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>

// Include BorderLayout and BorderLayoutConstraints header files
#include <OpenSG/UserInterface/OSGBorderLayout.h>
#include <OpenSG/UserInterface/OSGBorderLayoutConstraints.h>

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
                                        "OpenSG 09BorderLayout Window",
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

		Create Border Layout.  The Border Layout has
		five regions, North, South, East, West, and 
		Center.  The heights of the North/South region 
		are the heights of the Components loctated there 
		(so in the North region, the height of the North 
		region is determined by whatever is in the the
		North region).  The width of the Component is 
		automatically expanded to fit the width of the 
		region.  For the East and West regions, it is the 
		same except the width of the region is determined 
		by the width of what is in the region, and the height
		is automatically expanded to fit the region.  The 
		Center region is the entire middle area which is not 
		part of the N, W, S, or E regions.

		Note that by setting Max/Min size for Components, 
		the Components become centered in their region.  So
		a Component in the North or South region with a Max 
		width smaller than its region will be centered 
		horizontally ; likewise a Component in the East/
		West region	will be centered vertically if the Max
		height is exceeded.

		Experiment by changing the Button PreferredSizes and 
		adjusting window size for an example of this.  The
		North region currently has a Button with MaxSize 
		restraints.



	******************************************************/
	BorderLayoutPtr MainFrameLayout = osg::BorderLayout::create();

	// The main BorderLayout has no options to set, so this 
	// could be ommitted
	beginEditCP(MainFrameLayout);
		// Nothing!
	endEditCP(MainFrameLayout);


	/******************************************************

		Create BorderLayoutConstraints and define
		them.

		BorderLayoutConstraints determine where in the
		BorderLayout the Components appear.  The following
		are the arguments: BORDER_CENTER, BORDER_NORTH, 
		BORDER_EAST, BORDER_SOUTH, and BORDER_WEST, all 
		preceeded by "BorderLayoutConstraints::".


	******************************************************/
	BorderLayoutConstraintsPtr buttonConstraints1 = osg::BorderLayoutConstraints::create();
	BorderLayoutConstraintsPtr buttonConstraints2 = osg::BorderLayoutConstraints::create();
	BorderLayoutConstraintsPtr buttonConstraints3 = osg::BorderLayoutConstraints::create();
	BorderLayoutConstraintsPtr buttonConstraints4 = osg::BorderLayoutConstraints::create();
	BorderLayoutConstraintsPtr buttonConstraints5 = osg::BorderLayoutConstraints::create();


	beginEditCP(buttonConstraints1, BorderLayoutConstraints::RegionFieldMask);
		buttonConstraints1->setRegion(BorderLayoutConstraints::BORDER_CENTER);
	endEditCP(buttonConstraints1, BorderLayoutConstraints::RegionFieldMask);

	beginEditCP(buttonConstraints2, BorderLayoutConstraints::RegionFieldMask);
		buttonConstraints2->setRegion(BorderLayoutConstraints::BORDER_NORTH);
	endEditCP(buttonConstraints2, BorderLayoutConstraints::RegionFieldMask);
	
	beginEditCP(buttonConstraints3, BorderLayoutConstraints::RegionFieldMask);
		buttonConstraints3->setRegion(BorderLayoutConstraints::BORDER_EAST);
	endEditCP(buttonConstraints3, BorderLayoutConstraints::RegionFieldMask);
	
	beginEditCP(buttonConstraints4, BorderLayoutConstraints::RegionFieldMask);
		buttonConstraints4->setRegion(BorderLayoutConstraints::BORDER_SOUTH);
	endEditCP(buttonConstraints4, BorderLayoutConstraints::RegionFieldMask);
	
	beginEditCP(buttonConstraints5, BorderLayoutConstraints::RegionFieldMask);
		buttonConstraints5->setRegion(BorderLayoutConstraints::BORDER_WEST);
	endEditCP(buttonConstraints5, BorderLayoutConstraints::RegionFieldMask);
	



	/******************************************************

		Create some Button Components and Assign the
		BorderLayoutConstraints to those Components. 

		Note that unless BorderLayoutConstraints are 
		assigned, a Component will not display within
		BorderLayout (such as button1 currently).


	******************************************************/
	ButtonPtr button1 = osg::Button::create();
	ButtonPtr button2 = osg::Button::create();
	ButtonPtr button3 = osg::Button::create();
	ButtonPtr button4 = osg::Button::create();
	ButtonPtr button5 = osg::Button::create();
	

	beginEditCP(button1, Component::ConstraintsFieldMask);
		//button1->setConstraints(buttonConstraints1);
	endEditCP(button1, Component::ConstraintsFieldMask);
	
	beginEditCP(button2, Component::ConstraintsFieldMask | Component::PreferredSizeFieldMask | Component::MaxSizeFieldMask);
		button2->setConstraints(buttonConstraints2);
		button2->setPreferredSize( Vec2s(200, 200) );
		button2->setMaxSize( Vec2s(200,200) );
	endEditCP(button2, Component::ConstraintsFieldMask | Component::PreferredSizeFieldMask | Component::MaxSizeFieldMask);
	
	beginEditCP(button3, Component::ConstraintsFieldMask);
		button3->setConstraints(buttonConstraints3);
	endEditCP(button3, Component::ConstraintsFieldMask);
	
	beginEditCP(button4, Component::ConstraintsFieldMask);
		button4->setConstraints(buttonConstraints4);
	endEditCP(button4, Component::ConstraintsFieldMask);
	
	beginEditCP(button5, Component::ConstraintsFieldMask);
		button5->setConstraints(buttonConstraints5);
	endEditCP(button5, Component::ConstraintsFieldMask);
	



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
