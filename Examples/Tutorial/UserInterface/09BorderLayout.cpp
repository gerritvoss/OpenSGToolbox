// OpenSG Tutorial Example: Using the Border Layout
//        to place Components 
//
// This tutorial explains how to place ExampleButtons within a 
// frame utilizing the Border Layout command to 
// manage the layout through the OSG User Interface library.
// 
// Includes: placing multiple ExampleButtons using Border Layout


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

// 09BorderLayout Headers
#include "OSGButton.h"
#include "OSGColorLayer.h"
#include "OSGBorderLayout.h"
#include "OSGBorderLayoutConstraints.h"

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
        BorderLayoutRecPtr MainInternalWindowLayout = BorderLayout::create();

        // BorderLayout has no options to edit!   
        // Nothing!


        /******************************************************

          Create and edit the BorderLayoutConstraints.

          -setRegion(BorderLayoutContraints::ENUM): 
          Determine where in the BorderLayout the 
          Components will appear (based off of their 
          Constraints).  Takes BORDER_CENTER, 
          BORDER_NORTH, BORDER_EAST, BORDER_SOUTH, 
          and BORDER_WEST arguments.

         ******************************************************/
        BorderLayoutConstraintsRecPtr ExampleButton1Constraints = BorderLayoutConstraints::create();
        BorderLayoutConstraintsRecPtr ExampleButton2Constraints = BorderLayoutConstraints::create();
        BorderLayoutConstraintsRecPtr ExampleButton3Constraints = BorderLayoutConstraints::create();
        BorderLayoutConstraintsRecPtr ExampleButton4Constraints = BorderLayoutConstraints::create();
        BorderLayoutConstraintsRecPtr ExampleButton5Constraints = BorderLayoutConstraints::create();


        ExampleButton1Constraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);

        ExampleButton2Constraints->setRegion(BorderLayoutConstraints::BORDER_NORTH);

        ExampleButton3Constraints->setRegion(BorderLayoutConstraints::BORDER_EAST);

        ExampleButton4Constraints->setRegion(BorderLayoutConstraints::BORDER_SOUTH);

        ExampleButton5Constraints->setRegion(BorderLayoutConstraints::BORDER_WEST);


        /******************************************************

          Create some Button Components and assign the
          BorderLayoutConstraints to those Components. 

          Note that unless BorderLayoutConstraints are 
          assigned, a Component will not display within
          BorderLayout (such as ExampleButton1 currently).

         ******************************************************/
        ButtonRecPtr ExampleButton1 = Button::create();
        ButtonRecPtr ExampleButton2 = Button::create();
        ButtonRecPtr ExampleButton3 = Button::create();
        ButtonRecPtr ExampleButton4 = Button::create();
        ButtonRecPtr ExampleButton5 = Button::create();


        //ExampleButton1->setConstraints(ExampleButton1Constraints);

        ExampleButton2->setConstraints(ExampleButton2Constraints);
        ExampleButton2->setPreferredSize(Vec2f(200, 200));
        ExampleButton2->setMaxSize(Vec2f(200,200));

        ExampleButton3->setConstraints(ExampleButton3Constraints);

        ExampleButton4->setConstraints(ExampleButton4Constraints);

        ExampleButton5->setConstraints(ExampleButton5Constraints);

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
                                   "09BorderLayout");

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
