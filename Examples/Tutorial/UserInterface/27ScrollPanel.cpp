// OpenSG Tutorial Example: Using the AbsoluteLayout
//
// This tutorial explains how to place buttons within a 
// frame utilizing the Absolute Layout to manage the layout 
// through the OSG User Interface library.
// 
// Includes: placing multiple buttons and using 
// AbsoluteLayoutConstraints to locate the buttons.


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


// 27ScrollPanel Headers
#include "OSGLookAndFeelManager.h"
#include "OSGLayers.h"
#include "OSGFlowLayout.h"
#include "OSGPanel.h"
#include "OSGScrollPanel.h"
#include "OSGScrollBar.h"
#include "OSGDefaultBoundedRangeModel.h"
#include "OSGUIViewport.h"
#include "OSGButton.h"

// Declare function up front
PanelRefPtr createPanelWithButtons(void);

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

      Create a Panel containing Buttons to
      add to ScrollPanel using a function
      (located at bottom of this file)

     ******************************************************/    

    PanelRefPtr ExampleViewablePanel = createPanelWithButtons();

    /******************************************************

      Create a UIViewport to use with the
      ScrollPanel.  This sets up a secondary
      TutorialViewport inside the ScrollPanel.  
      Without this, the ScrollPanel would 
      not function correctly.

      The Panel created above is added to be
      viewed in the UIViewport and the size
      and position are set.

     ******************************************************/    
    UIViewportRefPtr ScrollPanelUIViewport = UIViewport::create();

    ScrollPanelUIViewport->setViewComponent(ExampleViewablePanel);
    ScrollPanelUIViewport->setViewPosition(Pnt2f(150,150));
    ScrollPanelUIViewport->setPreferredSize(Vec2f(200,200));

    /******************************************************

      Create the ScrollPanel itself.
      -setHorizontalResizePolicy(ScrollPanel::
      ENUM):  Determines the Horizontal 
      resize policy.  The ScrollPanel will 
      automatically resize itself to the
      Size of its Component within for 
      RESIZE_TO_VIEW, or add a ScrollBar 
      as needed for NO_RESIZE.  Takes
      NO_RESIZE and RESIZE_TO_VIEW 
      arguments.
      -setVerticalResizePolicy(ScrollPanel::
      ENUM):  Determines the Vertical 
      resize policy.  The ScrollPanel will 
      automatically resize itself to the
      Size of its Component within for 
      RESIZE_TO_VIEW, or add a ScrollBar 
      as needed for NO_RESIZE.  Takes
      NO_RESIZE and RESIZE_TO_VIEW 
      arguments.
      -setViewComponent(Component): Determine
      which Component will be added into
      the ScrollPanel.  Note that this
      must be the same as the UIViewport
      created above and does not require
      a begin/endEditCP.

     ******************************************************/    

    ScrollPanelRefPtr ExampleScrollPanel = ScrollPanel::create();
    ExampleScrollPanel->setPreferredSize(Vec2f(100,100));
    ExampleScrollPanel->setVerticalScrollBarAlignment(ScrollPanel::SCROLLBAR_ALIGN_LEFT);
    ExampleScrollPanel->setHorizontalScrollBarAlignment(ScrollPanel::SCROLLBAR_ALIGN_BOTTOM);

    //ExampleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    //ExampleScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);

    ExampleScrollPanel->setViewComponent(ExampleViewablePanel);


    /******************************************************

      Create two ScrollBars.

      First, create a DefaultBoundedRangeModel.
      This determines some characteristics of 
      the Scrollbar.  Note that you can link
      several ScollBars to the same 
      DefaultBoundedRangeModel; this will
      cause them to move at the same time.

      -.setMinimum(int): Determine a numeric
      value for the beginning of the 
      ScrollBar.  Note that the visible
      size will be set separately.
      -.setMaximum(int): Determine a numeric
      value for the end of the 
      ScrollBar. 
      -.setValue(int):  Determine the 
      initial location of the Bar on the
      ScrollBar.  This is determined from
      the Min/Max values.
      -.setExtent(int): Determine the size
      of the Bar on the ScrollBar as a 
      fraction of the total size (which is 
      determined from the Min/Max values)
      as well.

      Second, create the ScrollBar itself.

      -setOrientation(ENUM): Determine
      the orientation of the ScrollBar.
      Takes VERTICAL_ORIENTATION
      and HORIZONTAL_ORIENTATION arguments.
      -setUnitIncrement(int): Determines how
      much the Scoller moves per click
      on its end arrows.  References to the
      Min/Max values as well.
      -setBlockIncrement(int): Determine
      how many units the ScrollBar moves 
      when the "non-scroller" is clicked.
      This references the Min/Max values
      above as well (so if the Min/Max
      range was 0 to 100, and this was 
      100, then each click would move the
      scoller to the opposite end).  It 
      would also be impossible to directly
      click the scroller to a middle location.

      Note that while in this tutorial both
      ScrollBars use the same BoundedRangeModel
      (which causes them to be linked), each 
      ScrollBar individually has these last two 
      settings uniquely set.  So while the 
      Scrollers move together (because they
      use the same Model), using each
      will cause them to move at different
      speeds due to these settings being
      different.

     ******************************************************/    

    // Create a DefaultBoundedRangeModel
    DefaultBoundedRangeModelRefPtr TheBoundedRangeModel = DefaultBoundedRangeModel::create();
    TheBoundedRangeModel->setMinimum(10);
    TheBoundedRangeModel->setMaximum(100);
    TheBoundedRangeModel->setValue(10);
    TheBoundedRangeModel->setExtent(20);

    ScrollBarRefPtr ExampleVerticalScrollBar = ScrollBar::create();
    //ExampleScrollPanel->getHorizontalScrollBar()
    ExampleVerticalScrollBar->setOrientation(ScrollBar::VERTICAL_ORIENTATION);
    ExampleVerticalScrollBar->setPreferredSize(Vec2f(20,200));
    ExampleVerticalScrollBar->setEnabled(false);
    ExampleVerticalScrollBar->setUnitIncrement(10);
    ExampleVerticalScrollBar->setBlockIncrement(100);
    ExampleVerticalScrollBar->setRangeModel(TheBoundedRangeModel);

    ScrollBarRefPtr ExampleHorizontalScrollBar = ScrollBar::create();
    ExampleHorizontalScrollBar->setOrientation(ScrollBar::HORIZONTAL_ORIENTATION);
    ExampleHorizontalScrollBar->setPreferredSize(Vec2f(400,20));
    ExampleHorizontalScrollBar->setRangeModel(TheBoundedRangeModel);


    // Creates another DefaultBoundedRangeModel to use 
    // for separating the two ScrollBars from each other.
    // Make sure to comment out the addition of the 
    // previous setModel above.

    /*
       DefaultBoundedRangeModel TheBoundedRangeModel2;
       TheBoundedRangeModel2.setMinimum(0);
       TheBoundedRangeModel2.setMaximum(100);
       TheBoundedRangeModel2.setValue(10);
       TheBoundedRangeModel2.setExtent(20);
       ExampleHorizontalScrollBar->setModel(&TheBoundedRangeModel2);
       */

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
    MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    LayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
    MainInternalWindow->pushToChildren(ExampleHorizontalScrollBar);
    MainInternalWindow->pushToChildren(ExampleVerticalScrollBar);
    MainInternalWindow->pushToChildren(ExampleScrollPanel);
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
                               "27ScrollPanel");

    //Enter main Loop
    TutorialWindow->mainLoop();

    osgExit();

    return 0;
}


PanelRefPtr createPanelWithButtons(void)
{
    ButtonRefPtr PanelButton1 = Button::create();
    ButtonRefPtr PanelButton2 = Button::create();
    ButtonRefPtr PanelButton3 = Button::create();
    ButtonRefPtr PanelButton4 = Button::create();
    ButtonRefPtr PanelButton5 = Button::create();
    ButtonRefPtr PanelButton6 = Button::create();
    PanelButton1->setText("This");
    PanelButton2->setText("is");
    PanelButton3->setText("a");
    PanelButton4->setText("sample");
    PanelButton5->setText("Scroll");
    PanelButton6->setText("Panel!");

    // Create Panel to add Buttons to which will be inserted into 
    // the ScrollPanel itself
    PanelRefPtr ScrollPanelInsertPanel = OSG::Panel::create();
    FlowLayoutRefPtr ScrollPanelInsertPanelLayout = OSG::FlowLayout::create();
    ScrollPanelInsertPanel->setPreferredSize(Vec2f(100, 250 ));
    ScrollPanelInsertPanel->pushToChildren(PanelButton1);
    ScrollPanelInsertPanel->pushToChildren(PanelButton2);
    ScrollPanelInsertPanel->pushToChildren(PanelButton3);
    ScrollPanelInsertPanel->pushToChildren(PanelButton4);
    ScrollPanelInsertPanel->pushToChildren(PanelButton5);
    ScrollPanelInsertPanel->pushToChildren(PanelButton6);
    ScrollPanelInsertPanel->setLayout(ScrollPanelInsertPanelLayout);

    return ScrollPanelInsertPanel;
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
