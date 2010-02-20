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
#include "OSGConfig.h"

// Methods to create simple geometry: boxes, spheres, tori etc.
#include "OSGSimpleGeometry.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"

// The general scene file loading handler
#include "OSGSceneFileHandler.h"

// Input
#include "OSGWindowUtils.h"

// UserInterface Headers
#include "OSGUIForeground.h"
#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"
#include "OSGGraphics2D.h"
#include "OSGLookAndFeelManager.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// 06BoxLayout Headers
#include "OSGButton.h"
#include "OSGLookAndFeelManager.h"
#include "OSGColorLayer.h"
#include "OSGBoxLayout.h"


// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventUnrecPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
            TutorialWindow->closeWindow();
       }
   }

   virtual void keyReleased(const KeyEventUnrecPtr e)
   {
   }

   virtual void keyTyped(const KeyEventUnrecPtr e)
   {
   }
};

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindow = createNativeWindow();
    TutorialWindow->initWindow();

    TutorialWindow->setDisplayCallback(display);
    TutorialWindow->setReshapeCallback(reshape);

    TutorialKeyListener TheKeyListener;
    TutorialWindow->addKeyListener(&TheKeyListener);

    // Make Torus Node (creates Torus in background of scene)
    NodeRefPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Main Scene Node and add the Torus
    NodeRefPtr scene = OSG::Node::create();
        scene->setCore(OSG::Group::create());
        scene->addChild(TorusGeometryNode);

    // Create the Graphics
    GraphicsRefPtr TutorialGraphics = OSG::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

    /******************************************************
            
                Create some Button Components

    ******************************************************/

    ButtonRefPtr ExampleButton1 = OSG::Button::create();
    ButtonRefPtr ExampleButton2 = OSG::Button::create();
    ButtonRefPtr ExampleButton3 = OSG::Button::create();
    ButtonRefPtr ExampleButton4 = OSG::Button::create();

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

    BoxLayoutRefPtr MainInternalWindowLayout = OSG::BoxLayout::create();

	MainInternalWindowLayout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);			//Make the swap to see what happens Between Vertical and Horizontal!
	//MainInternalWindowLayout->setOrientation(BoxLayout::HORIZONTAL_ORIENTATION);
    
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
    
        ExampleButton1->setPreferredSize(Vec2f(50,50));
        ExampleButton1->setMaxSize(Vec2f(50, 50));			//The max size determines how large this button can be even though the BoxLayout says otherwise.(comment out to see the difference)

        ExampleButton2->setPreferredSize(Vec2f(200,100));

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
       MainInternalWindow->pushToChildren(ExampleButton1);
       MainInternalWindow->pushToChildren(ExampleButton2);
       MainInternalWindow->pushToChildren(ExampleButton3);
       MainInternalWindow->pushToChildren(ExampleButton4);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
    
    // Create the Drawing Surface
    UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);
    
	TutorialDrawingSurface->openWindow(MainInternalWindow);

    // Create the UI Foreground Object
    UIForegroundRefPtr TutorialUIForeground = OSG::UIForeground::create();

        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindow);
    mgr->setRoot(scene);

    // Add the UI Foreground Object to the Scene
    ViewportRefPtr TutorialViewport = mgr->getWindow()->getPort(0);
        TutorialViewport->addForeground(TutorialUIForeground);

    // Show the whole Scene
    mgr->showAll();

    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
            WinSize,
            "06BoxLayout");

    //Enter main Loop
    TutorialWindow->mainLoop();

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
