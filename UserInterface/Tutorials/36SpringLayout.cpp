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

#include <OpenSG/UserInterface/OSGBorders.h>
#include <OpenSG/UserInterface/OSGUIBackgrounds.h>
#include <OpenSG/UserInterface/OSGUIFont.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLayoutSpring.h>
#include <OpenSG/UserInterface/OSGSpringLayout.h>
#include <OpenSG/UserInterface/OSGSpringLayoutConstraints.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

bool ExitApp = false;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// Create the WindowEvent 
WindowEventProducerPtr TutorialWindowEventProducer;

class TutorialKeyListener : public KeyListener // Key Listener to exit the application if escape key is pressed
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

class TutorialWindowListener : public WindowAdapter // Window Listener to exit the application if the window is closed
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
            
                Creates some Button components

    ******************************************************/
    ButtonPtr ExampleButton1 = osg::Button::create();
    ButtonPtr ExampleButton2 = osg::Button::create();
    ButtonPtr ExampleButton3 = osg::Button::create();
    ButtonPtr ExampleButton4 = osg::Button::create();
    ButtonPtr ExampleButton5 = osg::Button::create();
    ButtonPtr ExampleButton6 = osg::Button::create();


    /******************************************************

        Create SpringLayout.  This layout simply
        places all Components within it on top of
        each other.

        They are placed in reverse order of how they
        are added to the MainFrame (Components added
        first are rendered last, those added last are
        rendered first).

		Note: SpringLayout has no options which
		can be set.


    ******************************************************/

    SpringLayoutPtr MainInternalWindowLayout = osg::SpringLayout::create();

    // OverlayLayout has no options to edit!
    beginEditCP(MainInternalWindowLayout);
        // NOTHING : )
    endEditCP(MainInternalWindowLayout); 

    
    /******************************************************

            Create and edit some Button Components.

    ******************************************************/

	beginEditCP(ExampleButton1, Button::PreferredSizeFieldMask);
        ExampleButton1->setPreferredSize(Vec2f(50,50));
		ExampleButton1->setText("Button 1");
    endEditCP(ExampleButton1, Button::PreferredSizeFieldMask);

	beginEditCP(ExampleButton2, Button::PreferredSizeFieldMask);
        ExampleButton2->setPreferredSize(Vec2f(50,50));
		ExampleButton2->setText("Button 2");
    endEditCP(ExampleButton2, Button::PreferredSizeFieldMask);

	beginEditCP(ExampleButton3, Button::PreferredSizeFieldMask);
        ExampleButton3->setPreferredSize(Vec2f(50,50));
		ExampleButton3->setText("Button 3");
    endEditCP(ExampleButton3, Button::PreferredSizeFieldMask);

	beginEditCP(ExampleButton4, Button::PreferredSizeFieldMask);
        ExampleButton4->setPreferredSize(Vec2f(50,50));
		ExampleButton4->setText("Button 4");
    endEditCP(ExampleButton4, Button::PreferredSizeFieldMask);

	beginEditCP(ExampleButton5, Button::PreferredSizeFieldMask);
        ExampleButton5->setPreferredSize(Vec2f(50,50));
		ExampleButton5->setText("Button 5");
    endEditCP(ExampleButton5, Button::PreferredSizeFieldMask);

	beginEditCP(ExampleButton6, Button::PreferredSizeFieldMask);
        ExampleButton6->setPreferredSize(Vec2f(50,50));
		ExampleButton6->setText("Button 6");
    endEditCP(ExampleButton6, Button::PreferredSizeFieldMask);
    
    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();

	// SpringLayoutConstraints Information
	// It is possible to set the constraint for the Y_EDGE, X_EDGE, BASELINE_EDGE, NORTH_EDGE, SOUTH_EDGE, EAST_EDGE, WEST_EDGE, HEIGHT_EDGE, and/or WIDTH_EDGE of a component.
	// It is possible to constrain a component's edge x pixels above, below, to the right of, or to the left of the edges other components, frames, and/or the MainInternalWindow.
	// It is possible to constrain a component to the Y_EDGE, X_EDGE, BASELINE_EDGE, NORTH_EDGE, SOUTH_EDGE, EAST_EDGE, WEST_EDGE, HORIZONTAL_CENTER_EDGE, VERTICAL_CENTER_EDGE, HEIGHT_EDGE, and/or WIDTH_EDGE of whatever component to which it is constrained.
	
	//Example Button 1    
    MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, ExampleButton1, 25, SpringLayoutConstraints::NORTH_EDGE, MainInternalWindow);  // The North edge of ExampleButton1 is 25 pixels below the North edge of the MainInternalWindow.
    MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, ExampleButton1, -5, SpringLayoutConstraints::VERTICAL_CENTER_EDGE, MainInternalWindow);  // The South edge of ExampleButton1 is 5 pixels above the Vertical Center of the MainInternalWindow.
    MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, ExampleButton1, -25, SpringLayoutConstraints::EAST_EDGE, MainInternalWindow);  // The East edge of ExampleButton1 is 25 pixels to the left of the East edge of the MainInternalWindow.
    MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, ExampleButton1, 25, SpringLayoutConstraints::WEST_EDGE, MainInternalWindow);  // The West edge of ExampleButton1 is 25 pixels to the right of the West edge of the MainInternalWindow.

	//Example Button 2
	MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, ExampleButton2, LayoutSpring::height(ExampleButton2));  // The Height edge of ExampleButton2 is set to the height of ExampleButton2.
	MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, ExampleButton2, -25, SpringLayoutConstraints::SOUTH_EDGE, MainInternalWindow);  // The South edge of ExampleButton2 is 25 pixels above the South edge of the MainInternalWindow.
	MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, ExampleButton2, -5, SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, MainInternalWindow);  // The East edge of ExampleButton2 is 5 pixels to the left of the Horizontal Center of the MainInternalWindow.
    MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, ExampleButton2, 25, SpringLayoutConstraints::WEST_EDGE, MainInternalWindow);  // The West edge of ExampleButton2 is 25 pixels to the right of the West edge of the MainInternalWindow.

	//Example Button 3
	MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, ExampleButton3, LayoutSpring::height(ExampleButton3));  // The Height edge of ExampleButton3 is set to the height of ExampleButton3.
	MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, ExampleButton3, -25, SpringLayoutConstraints::SOUTH_EDGE, MainInternalWindow);  // The South edge of ExampleButton3 is 25 pixels above the South edge of the MainInternalWindow.
	MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, ExampleButton3, 5, SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, MainInternalWindow);  // The West edge of ExampleButton3 is 5 pixels to the right of the Horizontal Center of the MainInternalWindow.
    MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, ExampleButton3, -25, SpringLayoutConstraints::EAST_EDGE, MainInternalWindow);  // The East edge of ExampleButton3 is 25 pixels to the left of the East edge of the MainInternalWindow.

	//Example Button 4
	MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, ExampleButton4, 25, SpringLayoutConstraints::SOUTH_EDGE, ExampleButton1);  // The North edge of ExampleButton4 is 25 pixels below the South edge of ExampleButton1.
	MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, ExampleButton4, -25, SpringLayoutConstraints::NORTH_EDGE, ExampleButton2);  // The South edge of ExampleButton4 is 25 pixels above the North edge of ExampleButton2.
	MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, ExampleButton4, 25, SpringLayoutConstraints::WEST_EDGE, MainInternalWindow);  // The West edge of ExampleButton4 is 25 pixels to the right of the West edge of the MainInternalWindow.
    MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, ExampleButton4, -100, SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, MainInternalWindow);  // The East edge of ExampleButton4 is 100 pixels to the left of the Horizontal Center of the MainInternalWindow.
	
	//Example Button 5
	MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, ExampleButton5, 25, SpringLayoutConstraints::SOUTH_EDGE, ExampleButton1);  // The North edge of ExampleButton5 is 25 pixels below the South edge of ExampleButton1.
	MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::HEIGHT_EDGE, ExampleButton5, 0, SpringLayoutConstraints::HEIGHT_EDGE, ExampleButton4);  // The Height of ExampleButton5 is set to the Height of ExampleButton4.
	MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, ExampleButton5, 75, SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, MainInternalWindow);  // The East edge of ExampleButton5 is 75 pixels to the right of the Horizontal Center of the MainInternalWindow.
    MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, ExampleButton5, -75, SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, MainInternalWindow);  // The West edge of ExampleButton5 is 75 pixels to the left of the Horizontal Center of the MainInternalWindow.

	//Example Button 6
	MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, ExampleButton6, 25, SpringLayoutConstraints::SOUTH_EDGE, ExampleButton1);  // The North edge of ExampleButton6 is 25 pixels below the South edge of ExampleButton1.
	MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, ExampleButton6, -25, SpringLayoutConstraints::NORTH_EDGE, ExampleButton2);  // The South edge of ExampleButton6 is 25 pixels above the North edge of ExampleButton2.
	MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, ExampleButton6, 100, SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, MainInternalWindow);  // The West edge of ExampleButton6 is 100 pixels to the right of the Horizontal Center of the MainInternalWindow.
    MainInternalWindowLayout->putConstraint(SpringLayoutConstraints::WIDTH_EDGE, ExampleButton6, 0, SpringLayoutConstraints::WIDTH_EDGE, ExampleButton4);  // The Width of ExampleButton6 is set to the Width of ExampleButton4.

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorUIBackgroundPtr MainInternalWindowBackground = osg::ColorUIBackground::create();
    beginEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);

	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().addValue(ExampleButton1);
       MainInternalWindow->getChildren().addValue(ExampleButton2);
       MainInternalWindow->getChildren().addValue(ExampleButton3);
	   MainInternalWindow->getChildren().addValue(ExampleButton4);
       MainInternalWindow->getChildren().addValue(ExampleButton5);
       MainInternalWindow->getChildren().addValue(ExampleButton6);
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
                                        "OpenSG 36SpringLayout Window");

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
