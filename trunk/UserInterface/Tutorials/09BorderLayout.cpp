// OpenSG Tutorial Example: Using the Border Layout
//        to place Components 
//
// This tutorial explains how to place ExampleButtons within a 
// frame utilizing the Border Layout command to 
// manage the layout through the OSG User Interface library.
// 
// Includes: placing multiple ExampleButtons using Border Layout


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

// 09BorderLayout Headers
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGColorLayer.h>
#include <OpenSG/UserInterface/OSGBorderLayout.h>
#include <OpenSG/UserInterface/OSGBorderLayoutConstraints.h>

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

        Create Border Layout.  The Border Layout has
        five regions, North, South, East, West, and 
        Center.  The Heights of the North/South region 
        are the heights of the Components loctated there 
        (so in the North region, the height of the North 
        region is determined by whatever is in the the
        North region).  The width of the Component is 
        automatically expanded to fit the width of the 
        region.  For the East and West regions, it is the 
        same except the Width of the region is determined 
        by the width of what is in the region, and the Height
        is automatically expanded to fit the region.  The 
        Center region is the entire middle area which is not 
        part of the N, W, S, or E regions.

        Note that by setting Max/Min size for Components, 
        the Components become centered in their region.  So
        a Component in the North or South region with a Max 
        width smaller than its region will be centered 
        horizontally ; likewise a Component in the East/
        West region will be centered vertically if the Max
        height is exceeded.

        Experiment by changing the Button PreferredSizes and 
        adjusting window size for an example of this.  The
        North region currently has a Button with MaxSize 
        restraints.

    ******************************************************/
    BorderLayoutPtr MainInternalWindowLayout = osg::BorderLayout::create();

    // BorderLayout has no options to edit!   
    beginEditCP(MainInternalWindowLayout);
        // Nothing!
    endEditCP(MainInternalWindowLayout);


    /******************************************************

        Create and edit the BorderLayoutConstraints.

		-setRegion(BorderLayoutContraints::ENUM): 
			Determine where in the BorderLayout the 
			Components will appear (based off of their 
			Constraints).  Takes BORDER_CENTER, 
			BORDER_NORTH, BORDER_EAST, BORDER_SOUTH, 
			and BORDER_WEST arguments.

    ******************************************************/
    BorderLayoutConstraintsPtr ExampleButton1Constraints = osg::BorderLayoutConstraints::create();
    BorderLayoutConstraintsPtr ExampleButton2Constraints = osg::BorderLayoutConstraints::create();
    BorderLayoutConstraintsPtr ExampleButton3Constraints = osg::BorderLayoutConstraints::create();
    BorderLayoutConstraintsPtr ExampleButton4Constraints = osg::BorderLayoutConstraints::create();
    BorderLayoutConstraintsPtr ExampleButton5Constraints = osg::BorderLayoutConstraints::create();


    beginEditCP(ExampleButton1Constraints, BorderLayoutConstraints::RegionFieldMask);
        ExampleButton1Constraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
    endEditCP(ExampleButton1Constraints, BorderLayoutConstraints::RegionFieldMask);

    beginEditCP(ExampleButton2Constraints, BorderLayoutConstraints::RegionFieldMask);
        ExampleButton2Constraints->setRegion(BorderLayoutConstraints::BORDER_NORTH);
    endEditCP(ExampleButton2Constraints, BorderLayoutConstraints::RegionFieldMask);
    
    beginEditCP(ExampleButton3Constraints, BorderLayoutConstraints::RegionFieldMask);
        ExampleButton3Constraints->setRegion(BorderLayoutConstraints::BORDER_EAST);
    endEditCP(ExampleButton3Constraints, BorderLayoutConstraints::RegionFieldMask);
    
    beginEditCP(ExampleButton4Constraints, BorderLayoutConstraints::RegionFieldMask);
        ExampleButton4Constraints->setRegion(BorderLayoutConstraints::BORDER_SOUTH);
    endEditCP(ExampleButton4Constraints, BorderLayoutConstraints::RegionFieldMask);
    
    beginEditCP(ExampleButton5Constraints, BorderLayoutConstraints::RegionFieldMask);
        ExampleButton5Constraints->setRegion(BorderLayoutConstraints::BORDER_WEST);
    endEditCP(ExampleButton5Constraints, BorderLayoutConstraints::RegionFieldMask);
    

    /******************************************************

        Create some Button Components and assign the
        BorderLayoutConstraints to those Components. 

        Note that unless BorderLayoutConstraints are 
        assigned, a Component will not display within
        BorderLayout (such as ExampleButton1 currently).

    ******************************************************/
    ButtonPtr ExampleButton1 = osg::Button::create();
    ButtonPtr ExampleButton2 = osg::Button::create();
    ButtonPtr ExampleButton3 = osg::Button::create();
    ButtonPtr ExampleButton4 = osg::Button::create();
    ButtonPtr ExampleButton5 = osg::Button::create();
    

    beginEditCP(ExampleButton1, Button::ConstraintsFieldMask);
        //ExampleButton1->setConstraints(ExampleButton1Constraints);
    endEditCP(ExampleButton1, Button::ConstraintsFieldMask);
    
    beginEditCP(ExampleButton2, Button::ConstraintsFieldMask | Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask);
        ExampleButton2->setConstraints(ExampleButton2Constraints);
        ExampleButton2->setPreferredSize(Vec2f(200, 200));
        ExampleButton2->setMaxSize(Vec2f(200,200));
    endEditCP(ExampleButton2, Button::ConstraintsFieldMask | Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask);
    
    beginEditCP(ExampleButton3, Button::ConstraintsFieldMask);
        ExampleButton3->setConstraints(ExampleButton3Constraints);
    endEditCP(ExampleButton3, Button::ConstraintsFieldMask);
    
    beginEditCP(ExampleButton4, Button::ConstraintsFieldMask);
        ExampleButton4->setConstraints(ExampleButton4Constraints);
    endEditCP(ExampleButton4, Button::ConstraintsFieldMask);
    
    beginEditCP(ExampleButton5, Button::ConstraintsFieldMask);
        ExampleButton5->setConstraints(ExampleButton5Constraints);
    endEditCP(ExampleButton5, Button::ConstraintsFieldMask);
    
    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().push_back(ExampleButton1);
       MainInternalWindow->getChildren().push_back(ExampleButton2);
       MainInternalWindow->getChildren().push_back(ExampleButton3);
       MainInternalWindow->getChildren().push_back(ExampleButton4);
       MainInternalWindow->getChildren().push_back(ExampleButton5);
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
        TutorialViewport->getForegrounds().push_back(TutorialUIForeground);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);

    // Show the whole Scene
    mgr->showAll();

    TutorialWindowEventProducer->openWindow(Pnt2f(50,50),
                                        Vec2f(900,900),
                                        "OpenSG 09BorderLayout Window");

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
