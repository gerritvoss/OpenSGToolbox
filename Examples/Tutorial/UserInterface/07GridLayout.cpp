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

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

// 07GridLayout Headers
#include "OSGButton.h"
#include "OSGColorLayer.h"
#include "OSGGridLayout.h"

void keyPressed(KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
}

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    {
        // Set up Window
        WindowEventProducerRecPtr TutorialWindow = createNativeWindow();
        TutorialWindow->initWindow();

        // Create the SimpleSceneManager helper
        SimpleSceneManager sceneManager;
        TutorialWindow->setDisplayCallback(boost::bind(display, &sceneManager));
        TutorialWindow->setReshapeCallback(boost::bind(reshape, _1, &sceneManager));

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

        TutorialWindow->connectKeyTyped(boost::bind(keyPressed, _1));

        // Make Torus Node (creates Torus in background of scene)
        NodeRecPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

        // Make Main Scene Node and add the Torus
        NodeRecPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(TorusGeometryNode);

        // Create the Graphics
        GraphicsRecPtr TutorialGraphics = Graphics2D::create();

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

        GridLayoutRecPtr MainInternalWindowLayout = GridLayout::create();

        MainInternalWindowLayout->setRows(3);
        MainInternalWindowLayout->setColumns(2);
        MainInternalWindowLayout->setHorizontalGap(4);
        MainInternalWindowLayout->setVerticalGap(4);


        /******************************************************

          Create and edit some Button Components.

          Note that as with BoxLayout, Components
          are resized to fit their respective
          grid boxes.  Unless a MaxSize is set,
          this will be the case.  This will
          override even PreferredSizes (see
          ExampleButton3).

         ******************************************************/

        ButtonRecPtr ExampleButton1 = Button::create();
        ButtonRecPtr ExampleButton2 = Button::create();
        ButtonRecPtr ExampleButton3 = Button::create();
        ButtonRecPtr ExampleButton4 = Button::create();
        ButtonRecPtr ExampleButton5 = Button::create();
        ButtonRecPtr ExampleButton6 = Button::create();

        ExampleButton1->setPreferredSize(Vec2f(50,50));
        ExampleButton1->setMaxSize(Vec2f(50,50));			//if MaxSize is commented out, this button then will revert to being the same size as the others in the grid.

        ExampleButton2->setPreferredSize(Vec2f(200,100));	//<----
        //    |
        ExampleButton3->setPreferredSize(Vec2f(50,100));		//Notice that even though these two differ in size they appear the same on the grid


        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
        MainInternalWindow->pushToChildren(ExampleButton1);
        MainInternalWindow->pushToChildren(ExampleButton2);
        MainInternalWindow->pushToChildren(ExampleButton3);
        MainInternalWindow->pushToChildren(ExampleButton4);
        MainInternalWindow->pushToChildren(ExampleButton5);
        MainInternalWindow->pushToChildren(ExampleButton6);
        MainInternalWindow->setLayout(MainInternalWindowLayout);
        MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
        MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setDrawTitlebar(false);
        MainInternalWindow->setResizable(false);

        // Create the Drawing Surface
        UIDrawingSurfaceRecPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);

        TutorialDrawingSurface->openWindow(MainInternalWindow);

        // Create the UI Foreground Object
        UIForegroundRecPtr TutorialUIForeground = UIForeground::create();

        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);


        // Tell the Manager what to manage
        sceneManager.setRoot(scene);

        // Add the UI Foreground Object to the Scene
        ViewportRecPtr TutorialViewport = sceneManager.getWindow()->getPort(0);
        TutorialViewport->addForeground(TutorialUIForeground);

        // Show the whole Scene
        sceneManager.showAll();

        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "07GridLayout");

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}
// Callback functions


// Redraw the window
void display(SimpleSceneManager *mgr)
{
    mgr->redraw();
}

// React to size changes
void reshape(Vec2f Size, SimpleSceneManager *mgr)
{
    mgr->resize(Size.x(), Size.y());
}
