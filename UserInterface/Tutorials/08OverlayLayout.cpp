// OpenSG Tutorial Example: Using the Overlay Layout
//		to place Components 
//
// This tutorial explains how to place buttons within a 
// frame utilizing the Overlay Layout command to 
// manage the layout through the OSG User Interface library.
// 
// Includes: placing multiple buttons using Overlay Layout

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

// 08OverlayLayout Headers
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
#include <OpenSG/UserInterface/OSGOverlayLayout.h>


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

		Create Overlay Layout.  This layout simply
		places all components within it on top of
		each other.

		They are placed in reverse order of how they
		are added to the MainFrame (components added
		first are rendered last, those added last are
		rendered first).


	******************************************************/
	OverlayLayoutPtr MainFrameLayout = osg::OverlayLayout::create();

	// Overlay Layout has no options!
	beginEditCP(MainFrameLayout);
		// NOTHING : )
	endEditCP(MainFrameLayout); 

	

	// Edit Buttons to change their sizes
	// Note that as with Box Layout, unless a setMaxSize
	// option is specified, the 
	beginEditCP(button1, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask);
		button1->setPreferredSize( Vec2s(50,50) );
		button1->setMaxSize( Vec2s(50,50) );
	endEditCP(button1, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask);

	beginEditCP(button2, Button::PreferredSizeFieldMask);
		 button2->setPreferredSize( Vec2s(300,50) );
	endEditCP(button2, Button::PreferredSizeFieldMask);
		
	// Note that button3 will be resized to be the same
	// size as button2, while button will not
	beginEditCP(button3, Button::PreferredSizeFieldMask);
		 button3->setPreferredSize( Vec2s(50,300) );
	endEditCP(button3, Button::PreferredSizeFieldMask);


 	// Create The Main Frame

	// Create Background to be used with the Main Frame
	ColorUIBackgroundPtr mainBackground = osg::ColorUIBackground::create();
	beginEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
		mainBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
	endEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
	
	FramePtr MainFrame = osg::Frame::create();
	beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);
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

	// Create the Drawing Surface
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
    endEditCP  (foreground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the manager what to manage
    mgr->setWindow(MainWindow);
    mgr->setRoot(scene);

	// Add the UI Foreground Object to the Scene
	ViewportPtr viewport = mgr->getWindow()->getPort(0);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);
		viewport->getForegrounds().addValue(foreground);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);

    // Show the whole scene
    mgr->showAll();

    TheWindowEventProducer->openWindow(Pnt2s(50,50),
                                        Vec2s(900,900),
                                        "OpenSG 08OverlayLayout Window");

    //Main Event Loop
    while(!ExitApp)
    {
        TheWindowEventProducer->update();
        TheWindowEventProducer->draw();
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
void reshape(Vec2s Size)
{
    mgr->resize(Size.x(), Size.y());
}