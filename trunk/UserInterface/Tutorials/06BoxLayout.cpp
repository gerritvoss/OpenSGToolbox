/*************************************************
Welcome to the 06BoxLayout tutorial.  This 
tutorial details how to use the BoxLayout
to place components within a frame.  The following
components are introduced:
	
	BoxLayout

BoxLayout takes all components added to it and
creates a single row (or column).  It also
resizes the components to be uniform in
width/height (depending on orientation).  
It is useful when creating simple Panels of
Buttons for example, as it provides a Layout
which gives a good appearance yet remaining
simple.

The following all are shown and explained
within this tutorial:
    Creating BoxLayout
	Setting Alignments of Layout
	Explanation/Examples on automatic resizing


These tutorials contain potentially relevant
information:



*************************************************/
	


// OpenSG Tutorial Example: Using the Box Layout
//        to place Components 
//
// This tutorial explains how to place ExampleButtons within a 
// frame utilizing the Box Layout command to 
// manage the layout through the OSG User Interface library.
// 
// Includes: placing multiple ExampleButtons using Box Layout

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>

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
WindowEventProducerPtr TutorialWindowEventProducer;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// 06BoxLayout Headers
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGColorLayer.h>
#include <OpenSG/UserInterface/OSGBoxLayout.h>


// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEvent& e)
   {
       if(e.getKey() == KeyEvent::KEY_Q && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
            TutorialWindowEventProducer->closeWindow();
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
    TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

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
            
                Create some Button Components

    ******************************************************/

    ButtonPtr ExampleButton1 = osg::Button::create();
    ButtonPtr ExampleButton2 = osg::Button::create();
    ButtonPtr ExampleButton3 = osg::Button::create();
    ButtonPtr ExampleButton4 = osg::Button::create();

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

		-setOrientation(ENUM): Determine alignment of
			Layout.  Takes VERTICAL_ORIENTATION and
			HORIZONTAL_ORIENTATION arguments.


    ******************************************************/

    BoxLayoutPtr MainInternalWindowLayout = osg::BoxLayout::create();

    beginEditCP(MainInternalWindowLayout, BoxLayout::OrientationFieldMask);
	MainInternalWindowLayout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);			//Make the swap to see what happens Between Vertical and Horizontal!
	//MainInternalWindowLayout->setOrientation(BoxLayout::HORIZONTAL_ORIENTATION);
    endEditCP(MainInternalWindowLayout, BoxLayout::OrientationFieldMask); 
    
    /******************************************************
            
            Edit some of the Button Components.
			
			Because of how BoxLayout works, by
			setting a MaxSize, even though other
			Buttons within the Layout will be resized,
			ExampleButton1 cannot be larger than
			Vec2f(50,50).  The default size for
			all Buttons is Vec2f(100,50) [see
			DefaultLookAndFeel.cpp], but because
			ExampleButton2 is larger, each of
			the other Buttons will be resized
			to match ExampleButton2's larger
			size.

			Experiment by commenting out either
			line and observing the results.


    ******************************************************/
    
    beginEditCP(ExampleButton1, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask);
        ExampleButton1->setPreferredSize(Vec2f(50,50));
        ExampleButton1->setMaxSize(Vec2f(50, 50));			//The max size determines how large this button can be even though the BoxLayout says otherwise.(comment out to see the difference)
    endEditCP(ExampleButton1, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask);

    beginEditCP(ExampleButton2, Button::PreferredSizeFieldMask);
        ExampleButton2->setPreferredSize(Vec2f(200,100));
    endEditCP(ExampleButton2, Button::PreferredSizeFieldMask);

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

    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "01RubberBandCamera");

    //Enter main Loop
    TutorialWindowEventProducer->mainLoop();

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
