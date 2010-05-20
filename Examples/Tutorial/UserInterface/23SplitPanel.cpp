// OpenSG Tutorial Example: Using the Split Panel
//        to place two user-resizable Components 
//
// This tutorial explains how to use a Split Panel
// container to make a user-resizable area.
// 
// Includes: placing multiple buttons using Flow Layout
//           placing two containers using Split Panel


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

// 23SplitPanel Headers
#include "OSGUIForeground.h"
#include "OSGUIDrawingSurface.h"
#include "OSGGraphics2D.h"
#include "OSGButton.h"
#include "OSGLookAndFeelManager.h"
#include "OSGColorLayer.h"
#include "OSGBevelBorder.h"
#include "OSGFlowLayout.h"
#include "OSGBorderLayout.h"
#include "OSGBorderLayoutConstraints.h"
#include "OSGPanel.h"
#include "OSGSplitPanel.h"


// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
  public:

    virtual void keyPressed(const KeyEventUnrecPtr e)
    {
        if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
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

      Create and edit some Button Components

     ******************************************************/

    ButtonRefPtr ExampleButton1 = OSG::Button::create();
    ButtonRefPtr ExampleButton2 = OSG::Button::create();
    ButtonRefPtr ExampleButton3 = OSG::Button::create();
    ButtonRefPtr ExampleButton4 = OSG::Button::create();
    ButtonRefPtr ExampleButton5 = OSG::Button::create();
    ButtonRefPtr ExampleButton6 = OSG::Button::create();

    ExampleButton1->setPreferredSize(Vec2f(200, 50));

    ExampleButton4->setPreferredSize(Vec2f(50, 50));

    /******************************************************

      Create two Panels to be used with
      SplitPanel.

     ******************************************************/

    PanelRefPtr ExampleSplitPanelPanel1 = OSG::Panel::create();
    PanelRefPtr ExampleSplitPanelPanel2 = OSG::Panel::create();
    FlowLayoutRefPtr PanelFlowLayout = OSG::FlowLayout::create();

    PanelFlowLayout->setHorizontalGap(3);
    PanelFlowLayout->setVerticalGap(3);

    ExampleSplitPanelPanel1->pushToChildren(ExampleButton1);
    ExampleSplitPanelPanel1->pushToChildren(ExampleButton2);
    ExampleSplitPanelPanel1->pushToChildren(ExampleButton3);
    ExampleSplitPanelPanel1->setLayout(PanelFlowLayout);
    ExampleSplitPanelPanel2->pushToChildren(ExampleButton4);
    ExampleSplitPanelPanel2->pushToChildren(ExampleButton5);
    ExampleSplitPanelPanel2->pushToChildren(ExampleButton6);
    ExampleSplitPanelPanel2->setLayout(PanelFlowLayout);

    // Creates a BorderLayout and Constraints (causing the SplitPanel  
    // to automatically fill entire center Frame)
    BorderLayoutRefPtr MainInternalWindowLayout = OSG::BorderLayout::create();
    BorderLayoutConstraintsRefPtr ExampleSplitPanelConstraints = OSG::BorderLayoutConstraints::create();

    ExampleSplitPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);

    /******************************************************

      Creates and sets up SplitPanel

      -setMinComponent/setMaxComponent(Component):  Add 
      up to two Components to the SplitPanel.  Note
      that if you do not add both an empty Panel
      will be added automatically.
      -setOrientation(ENUM): Determines the alignment
      of the split aspect.  The default is
      Horizontal with an east/west split. The 
      minComponent set previously is the west or 
      north Component of the Panel (depending 
      on the alignment) and the max is the east
      or west Component.  Takes VERTICAL_ORIENTATION
      and HORIZONTAL_ORIENTATION arguments.
      -setDividerPosition("smart" REAL): Determines the initial 
      location of the divider.  Note that this REAL is
      a percentage if between 0.0 and 1.0 (inclusive) 
      and absolute is greater than 1.0.  Also note that
      when resizing a window with a percentage, the
      divider will move, but with absolute, it does
      not until it no longer fits in the panel.
      -setDividerSize(SIZE): Determine divider Size
      in pixels.
      -setExpandable(bool): Determine whether
      divider can be moved by user.  Default is
      TRUE (is movable) while FALSE removes
      the users ability to move the divider.
      -setMaxDividerPosition("smart" REAL): Determine
      the Maximum position for the divider.
      -setMinDividerPosition("smart" REAL): Determine
      the Minimum position for the divider.  Note 
      that for both Max/Min, the "smart" REAL
      follows same format as in setDividerPosition;
      it is a percentage if between 0.0 and 1.0 
      and absolute when > 1.0

     ******************************************************/

    SplitPanelRefPtr ExampleSplitPanel = OSG::SplitPanel::create();

    ExampleSplitPanel->setConstraints(ExampleSplitPanelConstraints);
    ExampleSplitPanel->setMinComponent(ExampleSplitPanelPanel1);
    ExampleSplitPanel->setMaxComponent(ExampleSplitPanelPanel2);
    // ExampleSplitPanel->setOrientation(SplitPanel::VERTICAL_ORIENTATION);
    // ExampleSplitPanel->setDividerPosition(.25); // this is a percentage
    ExampleSplitPanel->setDividerPosition(300); // this is an absolute (300 > 1.0) 
    // location from the left/top
    ExampleSplitPanel->setDividerSize(5);
    // ExampleSplitPanel->setExpandable(false);
    ExampleSplitPanel->setMaxDividerPosition(.9);
    ExampleSplitPanel->setMinDividerPosition(220);

    // also, if you want to change the way the divider looks, you can always set a
    // DrawObjectCanvas in place of the default divider
    // ExampleSplitPanel->setDividerDrawObject(drawObjectName);

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
    MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
    MainInternalWindow->pushToChildren(ExampleSplitPanel);
    MainInternalWindow->setLayout(MainInternalWindowLayout);
    MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
    MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
    MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
    MainInternalWindow->setDrawTitlebar(false);
    MainInternalWindow->setResizable(false);
    MainInternalWindow->setAllInsets(5);

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
                               "23SplitPanel");

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
