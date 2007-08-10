// OpenSG Tutorial Example: Using the Split Panel
//		to place two user-resizable Components 
//
// This tutorial explains how to use a Split Panel
// container to make a user-resizable area.
// 
// Includes: placing multiple buttons using Flow Layout
//           placing two containers using Split Panel

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
#include <OpenSG/Input/OSGWindowAdapter.h>

//UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
#include <OpenSG/UserInterface/OSGBevelBorder.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGBorderLayout.h>
#include <OpenSG/UserInterface/OSGBorderLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGPanel.h>
// The Split Panel include file
#include <OpenSG/UserInterface/OSGSplitPanel.h>
// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
bool ExitApp = false;

// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2s Size);

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

// Initialize GLUT & OpenSG and set up the scene
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
			
				Creates some Button components
				and edit their PreferredSizes

	******************************************************/
	ButtonPtr button1 = osg::Button::create();
	ButtonPtr button2 = osg::Button::create();
	ButtonPtr button3 = osg::Button::create();
	ButtonPtr button4 = osg::Button::create();
	ButtonPtr button5 = osg::Button::create();
	ButtonPtr button6 = osg::Button::create();


	beginEditCP(button1, Component::PreferredSizeFieldMask);
		button1->setPreferredSize( Vec2s (200, 50) );
	endEditCP(button1, Component::PreferredSizeFieldMask);

	beginEditCP(button4, Component::PreferredSizeFieldMask);
		button4->setPreferredSize( Vec2s (50, 50) );
	endEditCP(button4, Component::PreferredSizeFieldMask);

	FlowLayoutPtr flowLayout = osg::FlowLayout::create();

	beginEditCP(flowLayout);
		flowLayout->setHorizontalGap(3);
		flowLayout->setVerticalGap(3);
	endEditCP(flowLayout);

	// the border layout is the simplest way to make a container completely fill the frame
	BorderLayoutConstraintsPtr SplitPanelConstraints = osg::BorderLayoutConstraints::create();

	beginEditCP(SplitPanelConstraints);
		SplitPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
	endEditCP(SplitPanelConstraints);

	BorderLayoutPtr MainFrameLayout = osg::BorderLayout::create();

	// these are the two panels being added to split panel
	// each panel will have half of the buttons
	PanelPtr panel1 = osg::Panel::create();
	PanelPtr panel2 = osg::Panel::create();

	beginEditCP(panel1, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);
		panel1->getChildren().addValue(button1);
	    panel1->getChildren().addValue(button2);
	    panel1->getChildren().addValue(button3);
		panel1->setLayout(flowLayout);
	endEditCP(panel1, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);
	beginEditCP(panel2, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);
		panel2->getChildren().addValue(button4);
	    panel2->getChildren().addValue(button5);
	    panel2->getChildren().addValue(button6);
		panel2->setLayout(flowLayout);
	endEditCP(panel2, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);

	// this is the split panel
	SplitPanelPtr SplitPanel = osg::SplitPanel::create();

	beginEditCP(SplitPanel);
		// these constraints put the panel as the center in the border layout
		SplitPanel->setConstraints(SplitPanelConstraints);

		// in split panel, never add children, instead use these two sets
		// they automatically add them as children and they set up which
		// side of the panel to place each.
		SplitPanel->setMinComponent(panel1);
		SplitPanel->setMaxComponent(panel2);

		// the alignment determines whether the panel is split to be
		// north and south, or east and west. the default is a
		// horizontal layout, splitting them east and west.
		// the min component is always the west or north component,
		// and the max component is always the east or south component,
		// both of these components were set in the previous two statements
		//SplitPanel->setAlignment(VERTICAL_ALIGNMENT);

		// next we can set the position and size of the divider. the position
		// gives the position of the center of the divider. the position can
		// either be set using a percentage, or and absolute size. this is 
		// done by using a "smart" real, where if it is between the values of
		// 0.0 and 1.0, inclusive, then it is viewed as a percentage, whereas
		// any value higher than 1.0 is viewed as an absolute distance.
		// note that when resizing as a percentage, the divider moves, but when
		// resizing as an absolute it will stick to it's spot until it no longer
		// fits. the default position is .5
		//SplitPanel->setDividerPosition(.25); // this is a percentage
		SplitPanel->setDividerPosition(300); // this is an absolute location from the left/top
		SplitPanel->setDividerSize(5);

		// also, if you want to change the way the divider looks, you can always set a
		// DrawObjectCanvas in place of the default divider
		//SplitPanel->setDividerDrawObject(drawObjectName);

		// if you don't want the user moving the divider, then setExpandable to false.
		// the default is true.
		//SplitPanel->setExpandable(false);

		// the divider's max and min position can also be set, either as an absolute
		// or percentage just like setDividerPosition. Mixing absolute and percentage
		// works when setting maximum and minimum values. keep in mind that if the
		// components have max and min values, that might also effect the location of
		// the divider, although the components are always stretched to fill the entire
		// area of their respective sides of the split panel
		SplitPanel->setMaxDividerPosition(.9);
		SplitPanel->setMinDividerPosition(220);
	endEditCP(SplitPanel);
	
 	// Create The Main Frame

	// Create Background to be used with the Main Frame
	ColorUIBackgroundPtr mainBackground = osg::ColorUIBackground::create();
	beginEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
		mainBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
	endEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
	
	FramePtr MainFrame = osg::Frame::create();
	beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);
	   // Add the buttons to the mainframe so they will be displayed
	   MainFrame->getChildren().addValue(SplitPanel);
	   MainFrame->setLayout(MainFrameLayout);
	   MainFrame->setBackground(mainBackground);
	   MainFrame->setAllInsets(5);
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
                                        "OpenSG 23SplitPanel Window");

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
