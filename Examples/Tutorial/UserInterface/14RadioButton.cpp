// OpenSG Tutorial Example: Using the Flow Layout
//        to place Components 
//
// This tutorial explains how to place Buttons within a 
// frame utilizing the Flow Layout command to 
// manage the layout through the OSG User Interface library.
// 
// Includes: placing multiple ExampleRadioButtons using Flow Layout

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

// 14RadioButton Headers
#include "OSGButton.h"
#include "OSGColorLayer.h"
#include "OSGBevelBorder.h"
#include "OSGFlowLayout.h"
#include "OSGRadioButton.h"
#include "OSGRadioButtonGroup.h"

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

          Creates RadioButton components and
          edit them.  The RadioButton class
          inherits from the Button class.

          Radio Buttons are special ToggleButtons.  
          When they are selected, any RadioButton in 
          the same group is deselected, so there can
          only be one option selected.

          Advanced options for RadioButton can
          be found in the DefaultLookAndFeel.cpp
          file found in OSGUserInterface/Source Files/
          LookAndFeel (options for changing the
          RadioButton style, etc).

         ******************************************************/
        RadioButtonRecPtr ExampleRadioButton1 = RadioButton::create();
        RadioButtonRecPtr ExampleRadioButton2 = RadioButton::create();
        RadioButtonRecPtr ExampleRadioButton3 = RadioButton::create();

        ExampleRadioButton1->setAlignment(Vec2f(0.0,0.5));
        ExampleRadioButton1->setPreferredSize(Vec2f(100, 50));
        ExampleRadioButton1->setText("Option 1");

        ExampleRadioButton2->setAlignment(Vec2f(0.0,0.5));
        ExampleRadioButton2->setPreferredSize(Vec2f(100, 50));
        ExampleRadioButton2->setText("Option 2");

        ExampleRadioButton3->setAlignment(Vec2f(0.0,0.5));
        ExampleRadioButton3->setPreferredSize(Vec2f(100, 50));
        ExampleRadioButton3->setText("Option 3");

        /***************************************************

          Create and populate a group of RadioButtons.
          Defining the group allows you to pick which 
          RadioButtons are tied together so that only one 
          can be selected.

          Each RadioButtonGroup can only have ONE
          RadioButton selected at a time, and by 
          selecting this RadioButton, will deselect
          all other RadioButtons in the RadioButtonGroup.

         ******************************************************/
        RadioButtonGroupRecPtr ExampleRadioButtonGroup = RadioButtonGroup::create();

        ExampleRadioButtonGroup->addButton(ExampleRadioButton1);
        ExampleRadioButtonGroup->addButton(ExampleRadioButton2);
        ExampleRadioButtonGroup->addButton(ExampleRadioButton3);

        ExampleRadioButtonGroup->setSelectedButton(ExampleRadioButton2);

        FlowLayoutRecPtr MainInternalWindowLayout = FlowLayout::create();

        MainInternalWindowLayout->setOrientation(FlowLayout::VERTICAL_ORIENTATION);
        MainInternalWindowLayout->setMajorAxisAlignment(0.5f);
        MainInternalWindowLayout->setMinorAxisAlignment(0.5f);

        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
        MainInternalWindow->pushToChildren(ExampleRadioButton1);
        MainInternalWindow->pushToChildren(ExampleRadioButton2);
        MainInternalWindow->pushToChildren(ExampleRadioButton3);
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
                                   "14RadioButton");

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
