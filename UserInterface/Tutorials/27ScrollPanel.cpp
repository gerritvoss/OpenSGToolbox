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
void reshape(Vec2s Size);


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

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    WindowEventProducerPtr TheWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TheWindowEventProducer->initWindow();
    
    TheWindowEventProducer->setDisplayCallback(display);
    TheWindowEventProducer->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TheWindowEventProducer->addWindowListener(&TheTutorialWindowListener);


    // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Main Scene Node
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        scene->setCore(osg::Group::create());
 
        // add the torus as a child
        scene->addChild(TorusGeometryNode);
    }
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

	// Create the Graphics
	GraphicsPtr graphics = osg::Graphics2D::create();

	// Initialize the LookAndFeelManager to enable default 
	// settings for the Button
	LookAndFeelManager::the()->setLookAndFeel(WindowsLookAndFeel::create());
	LookAndFeelManager::the()->getLookAndFeel()->init();

	/******************************************************
			
			Create a Panel containing Buttons to
			add to ScrollPanel using a function
			(located at bottom of this file)
 
	******************************************************/	
	PanelPtr viewablePanel = createPanelWithButtons();
 

	/******************************************************
			
			Create a UIViewport to use with the
			ScrollPanel.  This sets up a secondary
			viewport inside the ScrollPanel.  Without
			this, the ScrollPanel would not function
			correctly.

			The Panel created above is added to be
			viewed in the UIViewport and the size
			and position are set.

 
	******************************************************/	
    UIViewportPtr TheUIViewport = UIViewport::create();

    beginEditCP(TheUIViewport, UIViewport::ViewComponentFieldMask | UIViewport::ViewPositionFieldMask | UIViewport::PreferredSizeFieldMask);
        TheUIViewport->setViewComponent(viewablePanel);
        TheUIViewport->setViewPosition(Pnt2s(150,150));
	    TheUIViewport->setPreferredSize(Vec2s(100,100));
    endEditCP(TheUIViewport, UIViewport::ViewComponentFieldMask | UIViewport::ViewPositionFieldMask | UIViewport::PreferredSizeFieldMask);

   	/******************************************************
			
			Create the ScrollPanel itself.
			-setHorizontalResizePolicy(ScrollPanel::
				enum) takes NO_RESIZE or RESIZE_TO_VIEW
				arguments.  This determines if the
				ScrollPanel will automatically
				resize itself to allow for the size
				of its components; otherwise it will
				add a Scrollbar.  Note that in 
				the Horitontal Direction it is
				resized (no Scrollbar) but in the
				Vertical Direction a ScrollBar is 
				added.  Default is NO_RESIZE.
			-setVerticalResizePolicy(): same as
				HorizontalResizePolicy except in
				the Vertical Direction

			-setViewcomponent(COMPONENT): sets which
				Component will be added into
				the ScrollPanel.  Note that this
				must be the same as the UIViewport
				created above and does not require
				a begin/endEditCP
 
	******************************************************/	
    ScrollPanelPtr TheScrollPanel = ScrollPanel::create();
    beginEditCP(TheScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
	    TheScrollPanel->setPreferredSize(Vec2s(100,150));
        TheScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //TheScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
		TheScrollPanel->setEnabled(false);
    endEditCP(TheScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    
	TheScrollPanel->setViewComponent(viewablePanel);


   	/******************************************************
			
			Create two ScrollBars.

			First, create a DefaultBoundedRangeModel.
			This determines some characteristics of 
			the Scrollbar.  Note that you can link
			several ScollBars to the same 
			DefaultBoundedRangeModel; this will
			cause them to move at the same time.
			-.setMinimum(Int): Determines a numeric
				value for the beginning of the 
				ScrollBar.  Note that the visible
				size will be set separately.
			-.setMaximum(Int): Determines a numeric
				value for the end of the 
				ScrollBar. 
			-.setValue(Int):  This determines the 
				initial location of the Bar on the
				ScrollBar.  This is determined from
				the Min/Max values.
			-.setExtent(Int): This determines the size
				of the Bar on the ScrollBar as a 
				fraction of the total size (which is 
				determined from the Min/Max values)

			Second, create the ScrollBar itself.
			This has several characterstics applied 
			to it.

			-setOrientation(ORIENTATION): Determines
				which orientation the ScrollBar will
				be.  Arguments are: VERTICAL_ALIGNMENT
				and HORIZONTAL_ALIGNMENT
			-setUnitIncrement(Int): Determines how
				much the scoller moves per click
				on its end arrows.  Relative to the
				Min/Max values as well.
			-setBlockIncrement(Int): This determines
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
			settings uniquely set.

	******************************************************/	
   
	// Create the DefaultBoundedRangeModel and 
	// set its values
    DefaultBoundedRangeModel TheBoundedRangeModel;
    TheBoundedRangeModel.setMinimum(10);
    TheBoundedRangeModel.setMaximum(100);
    TheBoundedRangeModel.setValue(10);
    TheBoundedRangeModel.setExtent(20);

	ScrollBarPtr TheScrollBar = ScrollBar::create();
	//TheScrollPanel->getHorizontalScrollBar()
    beginEditCP(TheScrollBar, ScrollBar::OrientationFieldMask | ScrollBar::PreferredSizeFieldMask);
        TheScrollBar->setOrientation(VERTICAL_ALIGNMENT);
        TheScrollBar->setPreferredSize(Vec2s(20,200));
		TheScrollBar->setEnabled(false);
		TheScrollBar->setUnitIncrement(10);
		TheScrollBar->setBlockIncrement(100);
    endEditCP(TheScrollBar, ScrollBar::OrientationFieldMask | ScrollBar::PreferredSizeFieldMask);
    TheScrollBar->setModel(&TheBoundedRangeModel);

    ScrollBarPtr TheScrollBarH = ScrollBar::create();
    beginEditCP(TheScrollBarH, ScrollBar::OrientationFieldMask | ScrollBar::PreferredSizeFieldMask);
        TheScrollBarH->setOrientation(HORIZONTAL_ALIGNMENT);
        TheScrollBarH->setPreferredSize(Vec2s(400,20));
    endEditCP(TheScrollBarH, ScrollBar::OrientationFieldMask | ScrollBar::PreferredSizeFieldMask);
    TheScrollBarH->setModel(&TheBoundedRangeModel);
	
   	
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
    TheScrollBarH->setModel(&TheBoundedRangeModel2);
	*/


	// Create The Main Frame
	// Create Background to be used with the Main Frame
	ColorUIBackgroundPtr mainBackground = osg::ColorUIBackground::create();
	beginEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
		mainBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
	endEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
	
	FramePtr MainFrame = osg::Frame::create();
	LayoutPtr MainFrameLayout = osg::FlowLayout::create();
	beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);
	   MainFrame->getChildren().addValue(TheScrollBarH);
	   MainFrame->getChildren().addValue(TheScrollBar);
	   MainFrame->getChildren().addValue(TheScrollPanel);
	   MainFrame->setLayout(MainFrameLayout);
	   MainFrame->setBackground(mainBackground);
    endEditCP  (MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);

	// Create the Drawing Surface
	UIDrawingSurfacePtr drawingSurface = UIDrawingSurface::create();
	beginEditCP(drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask);
		drawingSurface->setGraphics(graphics);
		drawingSurface->setRootFrame(MainFrame);
	    drawingSurface->setEventProducer(TheWindowEventProducer);
    endEditCP  (drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask);
	
	// Create the UI Foreground Object
	UIForegroundPtr foreground = osg::UIForeground::create();

	beginEditCP(foreground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
	    foreground->setDrawingSurface(drawingSurface);
		foreground->setFramePositionOffset(Vec2s(0,0));
		foreground->setFrameBounds(Vec2f(0.5,0.5));

    endEditCP  (foreground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the manager what to manage
    mgr->setWindow(MainWindow);
    mgr->setRoot(scene);

	// Add the UI Foreground Object to the Scene
	ViewportPtr viewport = mgr->getWindow()->getPort(0);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);
		viewport->getForegrounds().addValue(foreground);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);

    // Show the whole scene
    mgr->showAll();

    TheWindowEventProducer->openWindow(Pnt2s(50,50),
                                        Vec2s(550,550),
                                        "OpenSG 27ScrollPanel Window");

    //Main Event Loop
    while(!ExitApp)
    {
        TheWindowEventProducer->update();
        TheWindowEventProducer->draw();
    }
    osgExit();

    return 0;
}


PanelPtr createPanelWithButtons(void)
{
   ButtonPtr Button1 = Button::create();
	ButtonPtr Button2 = Button::create();
	ButtonPtr Button3 = Button::create();
	ButtonPtr Button4 = Button::create();
	ButtonPtr Button5 = Button::create();
	ButtonPtr Button6 = Button::create();
    beginEditCP(Button1, Button::PreferredSizeFieldMask | Button::TextFieldMask);
	    Button1->setText("This");
    endEditCP(Button1, Button::PreferredSizeFieldMask | Button::TextFieldMask);
	beginEditCP(Button2, Button::PreferredSizeFieldMask | Button::TextFieldMask);
	    Button2->setText("is");
    endEditCP(Button2, Button::PreferredSizeFieldMask | Button::TextFieldMask);
	beginEditCP(Button3, Button::PreferredSizeFieldMask | Button::TextFieldMask);
	    Button3->setText("a");
    endEditCP(Button3, Button::PreferredSizeFieldMask | Button::TextFieldMask);
	beginEditCP(Button4, Button::PreferredSizeFieldMask | Button::TextFieldMask);
	    Button4->setText("sample");
    endEditCP(Button4, Button::PreferredSizeFieldMask | Button::TextFieldMask);
    beginEditCP(Button5, Button::PreferredSizeFieldMask | Button::TextFieldMask);
	    Button5->setText("Scroll");
    endEditCP(Button5, Button::PreferredSizeFieldMask | Button::TextFieldMask);
	beginEditCP(Button6, Button::PreferredSizeFieldMask | Button::TextFieldMask);
	    Button6->setText("Panel!");
    endEditCP(Button6, Button::PreferredSizeFieldMask | Button::TextFieldMask);

	// Create Panel to add Buttons to which will be inserted into 
	// the ScrollPanel itself
	PanelPtr ScrollPanelInsertPanel = osg::Panel::create();
	FlowLayoutPtr ScrollPanelInsertPanelLayout = osg::FlowLayout::create();
	beginEditCP(ScrollPanelInsertPanel);
		ScrollPanelInsertPanel->setPreferredSize( Vec2s(100, 250 ) );
		ScrollPanelInsertPanel->getChildren().addValue(Button1);
		ScrollPanelInsertPanel->getChildren().addValue(Button2);
		ScrollPanelInsertPanel->getChildren().addValue(Button3);
		ScrollPanelInsertPanel->getChildren().addValue(Button4);
		ScrollPanelInsertPanel->getChildren().addValue(Button5);
		ScrollPanelInsertPanel->getChildren().addValue(Button6);
		ScrollPanelInsertPanel->setLayout(ScrollPanelInsertPanelLayout);
	endEditCP(ScrollPanelInsertPanel);

	return ScrollPanelInsertPanel;
}

// Callback functions


// Redraw the window
void display(void)
{
    mgr->redraw();
}

// React to size changes
void reshape(Vec2s Size)
{
    mgr->resize(Size.x(), Size.y());
}