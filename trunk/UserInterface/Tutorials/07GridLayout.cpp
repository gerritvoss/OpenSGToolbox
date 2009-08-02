/*************************************************
Welcome to the 07GridLayout tutorial.  This 
tutorial details how to use the GridLayout
to place components within a frame.  The following
components are introduced:
	
	GridLayout

GridLayout provides a simple way to put components
into a grid layout. It allows you to make an X
by Y 

The following all are shown and explained
within this tutorial:
    Creating BoxLayout
	Setting Alignments of Layout
	Explanation/Examples on automatic resizing


These tutorials contain potentially relevant
information:



*************************************************/


// OpenSG Tutorial Example: Using the Grid Layout
//        to place Components 
//
// This tutorial explains how to place ExampleButtons within a 
// frame utilizing the Grid Layout command to 
// manage the layout through the OSG User Interface library.
// 
// Includes: placing multiple ExampleButtons using Grid Layout


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

// 07GridLayout Headers
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGColorLayer.h>
#include <OpenSG/UserInterface/OSGGridLayout.h>



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

        Create Grid Layout.  Grid Layout arranges the 
        objects in a grid, with user specified rows, 
        columns, and gap size (conceptually imagine that
        an invisible grid is drawn, and components are 
        placed into that grid one per "box").

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
        scene.

        Note that if the Frame is too small, the objects will 
        appear out of the Frame background.

		-setRows(int): Determine the number of rows
			in the Layout.
		-setColumns(int): Determine the number of
			columns in the Layout.
		-setHorizontalGap(int): Determine the number
			of pixels between each column.
		setVerticalGap(int): Determine the number
			of pixels between each row.


    ******************************************************/

    GridLayoutPtr MainInternalWindowLayout = osg::GridLayout::create();

    beginEditCP(MainInternalWindowLayout, GridLayout::RowsFieldMask | GridLayout::ColumnsFieldMask | 
		GridLayout::HorizontalGapFieldMask | GridLayout::VerticalGapFieldMask);
        MainInternalWindowLayout->setRows(3);
        MainInternalWindowLayout->setColumns(2);
        MainInternalWindowLayout->setHorizontalGap(4);
        MainInternalWindowLayout->setVerticalGap(4);
    endEditCP(MainInternalWindowLayout, GridLayout::RowsFieldMask | GridLayout::ColumnsFieldMask | 
		GridLayout::HorizontalGapFieldMask | GridLayout::VerticalGapFieldMask);


    /******************************************************
            
             Create and edit some Button Components.

			 Note that as with BoxLayout, Components
			 are resized to fit their respective
			 grid boxes.  Unless a MaxSize is set,
			 this will be the case.  This will
			 override even PreferredSizes (see
			 ExampleButton3).

    ******************************************************/

    ButtonPtr ExampleButton1 = osg::Button::create();
    ButtonPtr ExampleButton2 = osg::Button::create();
    ButtonPtr ExampleButton3 = osg::Button::create();
    ButtonPtr ExampleButton4 = osg::Button::create();
    ButtonPtr ExampleButton5 = osg::Button::create();
    ButtonPtr ExampleButton6 = osg::Button::create();

    beginEditCP(ExampleButton1, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask);
        ExampleButton1->setPreferredSize(Vec2f(50,50));
        ExampleButton1->setMaxSize(Vec2f(50,50));			//if MaxSize is commented out, this button then will revert to being the same size as the others in the grid.
    endEditCP(ExampleButton1, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask);

    beginEditCP(ExampleButton2, Button::PreferredSizeFieldMask);
         ExampleButton2->setPreferredSize(Vec2f(200,100));	//<----
    endEditCP(ExampleButton2, Button::PreferredSizeFieldMask);//  |
															//    |
    beginEditCP(ExampleButton3, Button::PreferredSizeFieldMask);//|
         ExampleButton3->setPreferredSize(Vec2f(50,100));		//Notice that even though these two differ in size they appear the same on the grid
    endEditCP(ExampleButton3, Button::PreferredSizeFieldMask);


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
       MainInternalWindow->getChildren().push_back(ExampleButton6);
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
