// OpenSG Tutorial Example: Using the AbsoluteLayout
//
// This tutorial explains how to place buttons within a 
// frame utilizing the Absolute Layout to manage the layout 
// through the OSG User Interface library.
// 
// Includes: placing multiple buttons and using 
// AbsoluteLayoutConstraints to locate the buttons.


// GLUT is used for window handling
#include <OpenSG/OSGGLUT.h>

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// The GLUT-OpenSG connection class
#include <OpenSG/OSGGLUTWindow.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/Input/OSGWindowAdapter.h>

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

bool ExitApp = false;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);


// 27ScrollPanel Headers
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGUIBackgrounds.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGScrollPanel.h>
#include <OpenSG/UserInterface/OSGScrollBar.h>
#include <OpenSG/UserInterface/OSGDefaultBoundedRangeModel.h>
#include <OpenSG/UserInterface/OSGUIViewport.h>
#include <OpenSG/UserInterface/OSGButton.h>

// Declare function up front
PanelPtr createPanelWithButtons(void);

class TutorialWindowListener : public WindowAdapter
{
public:
    virtual void windowClosing(const WindowEvent& e)
    {
        ExitApp = true;
    }

    virtual void windowClosed(const WindowEvent& e)
    {
        ExitApp = true;
    }
};

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEvent& e)
   {
       if(e.getKey() == KeyEvent::KEY_Q && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           ExitApp = true;
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
    WindowEventProducerPtr TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();
    
    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TutorialWindowEventProducer->addWindowListener(&TheTutorialWindowListener);
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
    LookAndFeelManager::the()->setLookAndFeel(WindowsLookAndFeel::create());
    LookAndFeelManager::the()->getLookAndFeel()->init();

    /******************************************************
            
            Create a Panel containing Buttons to
            add to ScrollPanel using a function
            (located at bottom of this file)
 
    ******************************************************/    

    PanelPtr ExampleViewablePanel = createPanelWithButtons();
 
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
    UIViewportPtr ScrollPanelUIViewport = UIViewport::create();

    beginEditCP(ScrollPanelUIViewport, UIViewport::ViewComponentFieldMask | UIViewport::ViewPositionFieldMask | UIViewport::PreferredSizeFieldMask);
        ScrollPanelUIViewport->setViewComponent(ExampleViewablePanel);
        ScrollPanelUIViewport->setViewPosition(Pnt2f(150,150));
        ScrollPanelUIViewport->setPreferredSize(Vec2f(100,100));
    endEditCP(ScrollPanelUIViewport, UIViewport::ViewComponentFieldMask | UIViewport::ViewPositionFieldMask | UIViewport::PreferredSizeFieldMask);

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
    
	ScrollPanelPtr ExampleScrollPanel = ScrollPanel::create();
    beginEditCP(ExampleScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        ExampleScrollPanel->setPreferredSize(Vec2f(100,150));
        ExampleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //ExampleScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(ExampleScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    
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
				Takes VERTICAL_ALIGNMENT
                and HORIZONTAL_ALIGNMENT arguments.
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
    DefaultBoundedRangeModel TheBoundedRangeModel;
    TheBoundedRangeModel.setMinimum(10);
    TheBoundedRangeModel.setMaximum(100);
    TheBoundedRangeModel.setValue(10);
    TheBoundedRangeModel.setExtent(20);

    ScrollBarPtr ExampleVerticalScrollBar = ScrollBar::create();
    //ExampleScrollPanel->getHorizontalScrollBar()
    beginEditCP(ExampleVerticalScrollBar, ScrollBar::OrientationFieldMask | ScrollBar::PreferredSizeFieldMask);
        ExampleVerticalScrollBar->setOrientation(VERTICAL_ALIGNMENT);
        ExampleVerticalScrollBar->setPreferredSize(Vec2f(20,200));
        ExampleVerticalScrollBar->setEnabled(false);
        ExampleVerticalScrollBar->setUnitIncrement(10);
        ExampleVerticalScrollBar->setBlockIncrement(100);
    endEditCP(ExampleVerticalScrollBar, ScrollBar::OrientationFieldMask | ScrollBar::PreferredSizeFieldMask);
    ExampleVerticalScrollBar->setModel(&TheBoundedRangeModel);

    ScrollBarPtr ExampleHorizontalScrollBar = ScrollBar::create();
    beginEditCP(ExampleHorizontalScrollBar, ScrollBar::OrientationFieldMask | ScrollBar::PreferredSizeFieldMask);
        ExampleHorizontalScrollBar->setOrientation(HORIZONTAL_ALIGNMENT);
        ExampleHorizontalScrollBar->setPreferredSize(Vec2f(400,20));
    endEditCP(ExampleHorizontalScrollBar, ScrollBar::OrientationFieldMask | ScrollBar::PreferredSizeFieldMask);
    ExampleHorizontalScrollBar->setModel(&TheBoundedRangeModel);
    
       
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
    ColorUIBackgroundPtr MainInternalWindowBackground = osg::ColorUIBackground::create();
    beginEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);

    LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().addValue(ExampleHorizontalScrollBar);
       MainInternalWindow->getChildren().addValue(ExampleVerticalScrollBar);
       MainInternalWindow->getChildren().addValue(ExampleScrollPanel);
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
        TutorialViewport->getForegrounds().addValue(TutorialUIForeground);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);

    // Show the whole Scene
    mgr->showAll();

    TutorialWindowEventProducer->openWindow(Pnt2f(50,50),
                                        Vec2f(550,550),
                                        "OpenSG 27ScrollPanel Window");

    //Main Event Loop
    while(!ExitApp)
    {
        TutorialWindowEventProducer->update();
        TutorialWindowEventProducer->draw();
    }
    osgExit();

    return 0;
}


PanelPtr createPanelWithButtons(void)
{
	ButtonPtr PanelButton1 = Button::create();
    ButtonPtr PanelButton2 = Button::create();
    ButtonPtr PanelButton3 = Button::create();
    ButtonPtr PanelButton4 = Button::create();
    ButtonPtr PanelButton5 = Button::create();
    ButtonPtr PanelButton6 = Button::create();
    beginEditCP(PanelButton1, Button::PreferredSizeFieldMask | Button::TextFieldMask);
        PanelButton1->setText("This");
    endEditCP(PanelButton1, Button::PreferredSizeFieldMask | Button::TextFieldMask);
    beginEditCP(PanelButton2, Button::PreferredSizeFieldMask | Button::TextFieldMask);
        PanelButton2->setText("is");
    endEditCP(PanelButton2, Button::PreferredSizeFieldMask | Button::TextFieldMask);
    beginEditCP(PanelButton3, Button::PreferredSizeFieldMask | Button::TextFieldMask);
        PanelButton3->setText("a");
    endEditCP(PanelButton3, Button::PreferredSizeFieldMask | Button::TextFieldMask);
    beginEditCP(PanelButton4, Button::PreferredSizeFieldMask | Button::TextFieldMask);
        PanelButton4->setText("sample");
    endEditCP(PanelButton4, Button::PreferredSizeFieldMask | Button::TextFieldMask);
    beginEditCP(PanelButton5, Button::PreferredSizeFieldMask | Button::TextFieldMask);
        PanelButton5->setText("Scroll");
    endEditCP(PanelButton5, Button::PreferredSizeFieldMask | Button::TextFieldMask);
    beginEditCP(PanelButton6, Button::PreferredSizeFieldMask | Button::TextFieldMask);
        PanelButton6->setText("Panel!");
    endEditCP(PanelButton6, Button::PreferredSizeFieldMask | Button::TextFieldMask);

    // Create Panel to add Buttons to which will be inserted into 
    // the ScrollPanel itself
    PanelPtr ScrollPanelInsertPanel = osg::Panel::create();
    FlowLayoutPtr ScrollPanelInsertPanelLayout = osg::FlowLayout::create();
	beginEditCP(ScrollPanelInsertPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
        ScrollPanelInsertPanel->setPreferredSize(Vec2f(100, 250 ));
        ScrollPanelInsertPanel->getChildren().addValue(PanelButton1);
        ScrollPanelInsertPanel->getChildren().addValue(PanelButton2);
        ScrollPanelInsertPanel->getChildren().addValue(PanelButton3);
        ScrollPanelInsertPanel->getChildren().addValue(PanelButton4);
        ScrollPanelInsertPanel->getChildren().addValue(PanelButton5);
        ScrollPanelInsertPanel->getChildren().addValue(PanelButton6);
        ScrollPanelInsertPanel->setLayout(ScrollPanelInsertPanelLayout);
    endEditCP(ScrollPanelInsertPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask);

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