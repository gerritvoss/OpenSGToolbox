// OpenSG Tutorial Example: Using Containers (Frames and Panels)
//
// This tutorial explains how use Frame and Panel Containers
// 
// Includes: creating and editing Frames, Panels, and adding
// Panels

// Note: in almost all cases, each Scene should have only ONE
// Frame, but may have unlimited Panels.


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

// 10Container Headers
#include "OSGButton.h"
#include "OSGLineBorder.h"
#include "OSGColorLayer.h"
#include "OSGAbsoluteLayout.h"
#include "OSGAbsoluteLayoutConstraints.h"
#include "OSGBoxLayout.h"
#include "OSGFlowLayout.h"
#include "OSGComponentContainer.h"
#include "OSGPanel.h"
#include "OSGLineBorder.h"
#include "OSGBevelBorder.h"

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

          Creates some Button components
          and edit their Text.

         ******************************************************/

        ButtonRecPtr ExampleButton1 = Button::create();
        ButtonRecPtr ExampleButton2 = Button::create();
        ButtonRecPtr ExampleButton3 = Button::create();
        ButtonRecPtr ExampleButton4 = Button::create();
        ButtonRecPtr ExampleButton5 = Button::create();
        ButtonRecPtr ExampleButton6 = Button::create();

        ExampleButton1->setText("This");

        ExampleButton2->setText("is a");

        ExampleButton3->setText("sample");

        ExampleButton4->setText("two");

        ExampleButton5->setText("ExamplePanel");

        ExampleButton6->setText("layout");


        /******************************************************

          Create some Flow and BoxLayouts to be 
          used with the Main Frame and two 
          Panels.

         ******************************************************/
        FlowLayoutRecPtr MainInternalWindowLayout = FlowLayout::create();
        FlowLayoutRecPtr ExamplePanel1Layout = FlowLayout::create();
        FlowLayoutRecPtr ExamplePanel2Layout = FlowLayout::create();

        ExamplePanel1Layout->setOrientation(FlowLayout::VERTICAL_ORIENTATION);


        /******************************************************

          Create two Backgrounds to be used with
          Panels and MainInternalWindow.

         ******************************************************/
        ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
        ColorLayerRecPtr ExamplePanelBackground = ColorLayer::create();

        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        ExamplePanelBackground->setColor(Color4f(0.0,0.0,0.0,1.0));

        /******************************************************

          Create a Border to be used with
          the two Panels.

         ******************************************************/
        LineBorderRecPtr ExamplePanelBorder = LineBorder::create();
        ExamplePanelBorder->setColor(Color4f(0.9, 0.9, 0.9, 1.0));
        ExamplePanelBorder->setWidth(3);


        /******************************************************

          Create MainInternalWindow and two Panel Components and
          edit their characteristics.

          -setPreferredSize(Vec2f): Determine the 
          size of the Panel.
          -pushToChildren(ComponentName):
          Adds a Component to the
          ComponentContainer as a Child (meaning it 
          will be displayed within it).
          -setLayout(LayoutName): Determines the 
          Layout of the ComponentContainer.

         ******************************************************/
        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
        PanelRecPtr ExamplePanel1 = Panel::create();
        PanelRecPtr ExamplePanel2 = Panel::create();

        // Edit Panel1, Panel2
        ExamplePanel1->setPreferredSize(Vec2f(200, 200));
        ExamplePanel1->pushToChildren(ExampleButton1);
        ExamplePanel1->pushToChildren(ExampleButton2);
        ExamplePanel1->pushToChildren(ExampleButton3);
        ExamplePanel1->setLayout(ExamplePanel1Layout);
        ExamplePanel1->setBackgrounds(ExamplePanelBackground);
        ExamplePanel1->setBorders(ExamplePanelBorder);

        ExamplePanel2->setPreferredSize(Vec2f(200, 200));
        ExamplePanel2->pushToChildren(ExampleButton4);
        ExamplePanel2->pushToChildren(ExampleButton5);
        ExamplePanel2->pushToChildren(ExampleButton6);
        ExamplePanel2->setLayout(ExamplePanel2Layout);
        ExamplePanel2->setBackgrounds(ExamplePanelBackground);
        ExamplePanel2->setBorders(ExamplePanelBorder);

        // Create The Main InternalWindow
        MainInternalWindow->pushToChildren(ExamplePanel1);
        MainInternalWindow->pushToChildren(ExamplePanel2);
        MainInternalWindow->setLayout(MainInternalWindowLayout);
        MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
        MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setDrawTitlebar(false);
        MainInternalWindow->setResizable(false);
        MainInternalWindow->setAllInsets(5);

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
                                   "10Container");

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
