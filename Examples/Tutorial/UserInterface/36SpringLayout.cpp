// OpenSG Tutorial Example: Creating a Button Component
//
// This tutorial explains how to edit the basic features of
// a Button created in the OSG User Interface library.
// 
// Includes: Button PreferredSize, MaximumSize, MinimumSize, Font,
// Text,and adding a Button to a Scene.  Also note that clicking
// the Button causes it to appear pressed


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

#include "OSGBorders.h"
#include "OSGLayers.h"
#include "OSGUIFont.h"
#include "OSGButton.h"
#include "OSGLayoutSpring.h"
#include "OSGSpringLayout.h"
#include "OSGSpringLayoutConstraints.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

void keyPressed(KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_Q &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
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

          Creates some Button components

         ******************************************************/
        ButtonRecPtr ExampleButton1 = Button::create();
        ButtonRecPtr ExampleButton2 = Button::create();
        ButtonRecPtr ExampleButton3 = Button::create();
        ButtonRecPtr ExampleButton4 = Button::create();
        ButtonRecPtr ExampleButton5 = Button::create();
        ButtonRecPtr ExampleButton6 = Button::create();


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

        SpringLayoutRecPtr MainInternalWindowLayout = SpringLayout::create();

        // OverlayLayout has no options to edit!
        // NOTHING : )


        /******************************************************

          Create and edit some Button Components.

         ******************************************************/

        ExampleButton1->setPreferredSize(Vec2f(50,50));
        ExampleButton1->setText("Button 1");

        ExampleButton2->setPreferredSize(Vec2f(50,50));
        ExampleButton2->setText("Button 2");

        ExampleButton3->setPreferredSize(Vec2f(50,50));
        ExampleButton3->setText("Button 3");

        ExampleButton4->setPreferredSize(Vec2f(50,50));
        ExampleButton4->setText("Button 4");

        ExampleButton5->setPreferredSize(Vec2f(50,50));
        ExampleButton5->setText("Button 5");

        ExampleButton6->setPreferredSize(Vec2f(50,50));
        ExampleButton6->setText("Button 6");

        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();

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
        ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

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
                                   "36SpringLayout");

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
