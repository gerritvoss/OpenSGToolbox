// OpenSG Tutorial Example: Using the Split Panel
//        to place two user-resizable Components 
//
// This tutorial explains how to use a Split Panel
// container to make a user-resizable area.
// 
// Includes: placing multiple buttons using Flow Layout
//           placing two containers using Split Panel


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

// 23SplitPanel Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
#include <OpenSG/UserInterface/OSGBevelBorder.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGBorderLayout.h>
#include <OpenSG/UserInterface/OSGBorderLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGSplitPanel.h>


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
    WindowEventProducerPtr TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();
    
    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TutorialWindowEventProducer->addWindowListener(&TheTutorialWindowListener);


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
            
            Create and edit some Button Components

    ******************************************************/

    ButtonPtr ExampleButton1 = osg::Button::create();
    ButtonPtr ExampleButton2 = osg::Button::create();
    ButtonPtr ExampleButton3 = osg::Button::create();
    ButtonPtr ExampleButton4 = osg::Button::create();
    ButtonPtr ExampleButton5 = osg::Button::create();
    ButtonPtr ExampleButton6 = osg::Button::create();

    beginEditCP(ExampleButton1, Button::PreferredSizeFieldMask);
        ExampleButton1->setPreferredSize(Vec2s(200, 50));
    endEditCP(ExampleButton1, Button::PreferredSizeFieldMask);

    beginEditCP(ExampleButton4, Button::PreferredSizeFieldMask);
        ExampleButton4->setPreferredSize(Vec2s(50, 50));
    endEditCP(ExampleButton4, Button::PreferredSizeFieldMask);

    /******************************************************
            
                Create two Panels to be used with
				SplitPanel.

    ******************************************************/

    PanelPtr ExampleSplitPanelPanel1 = osg::Panel::create();
    PanelPtr ExampleSplitPanelPanel2 = osg::Panel::create();
    FlowLayoutPtr PanelFlowLayout = osg::FlowLayout::create();
    
	beginEditCP(PanelFlowLayout, FlowLayout::HorizontalGapFieldMask | FlowLayout::VerticalGapFieldMask);
        PanelFlowLayout->setHorizontalGap(3);
        PanelFlowLayout->setVerticalGap(3);
    endEditCP(PanelFlowLayout, FlowLayout::HorizontalGapFieldMask | FlowLayout::VerticalGapFieldMask);

    beginEditCP(ExampleSplitPanelPanel1, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
        ExampleSplitPanelPanel1->getChildren().addValue(ExampleButton1);
        ExampleSplitPanelPanel1->getChildren().addValue(ExampleButton2);
        ExampleSplitPanelPanel1->getChildren().addValue(ExampleButton3);
        ExampleSplitPanelPanel1->setLayout(PanelFlowLayout);
    endEditCP(ExampleSplitPanelPanel1, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
    beginEditCP(ExampleSplitPanelPanel2, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
        ExampleSplitPanelPanel2->getChildren().addValue(ExampleButton4);
        ExampleSplitPanelPanel2->getChildren().addValue(ExampleButton5);
        ExampleSplitPanelPanel2->getChildren().addValue(ExampleButton6);
        ExampleSplitPanelPanel2->setLayout(PanelFlowLayout);
    endEditCP(ExampleSplitPanelPanel2, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);

    // Creates a BorderLayout and Constraints (causing the SplitPanel  
    // to automatically fill entire center Frame)
    BorderLayoutPtr MainFrameLayout = osg::BorderLayout::create();
    BorderLayoutConstraintsPtr ExampleSplitPanelConstraints = osg::BorderLayoutConstraints::create();

	beginEditCP(ExampleSplitPanelConstraints, BorderLayoutConstraints::RegionFieldMask);
        ExampleSplitPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
    endEditCP(ExampleSplitPanelConstraints, BorderLayoutConstraints::RegionFieldMask);
        
    /******************************************************
            
        Creates and sets up SplitPanel

        -setMinComponent/setMaxComponent(Component):  Add 
			up to two Components to the SplitPanel.  Note
			that if you do not add both an empty Panel
			will be added automatically.
		-setAlignment(ENUM): Determines the alignment
            of the split aspect.  The default is
            Horizontal with an east/west split. The 
            minComponent set previously is the west or 
			north Component of the Panel (depending 
			on the alignment) and the max is the east
			or west Component.  Takes VERTICAL_ALIGNMENT
            and HORIZONTAL_ALIGNMENT arguments.
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
    
    SplitPanelPtr ExampleSplitPanel = osg::SplitPanel::create();

	beginEditCP(ExampleSplitPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::AlignmentFieldMask | SplitPanel::DividerPositionFieldMask | 
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);
        ExampleSplitPanel->setConstraints(ExampleSplitPanelConstraints);
        ExampleSplitPanel->setMinComponent(ExampleSplitPanelPanel1);
        ExampleSplitPanel->setMaxComponent(ExampleSplitPanelPanel2);
        // ExampleSplitPanel->setAlignment(VERTICAL_ALIGNMENT);
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
    endEditCP(ExampleSplitPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::AlignmentFieldMask | SplitPanel::DividerPositionFieldMask | 
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);
    
    // Create The Main Frame
    // Create Background to be used with the Main Frame
    ColorUIBackgroundPtr MainFrameBackground = osg::ColorUIBackground::create();
    beginEditCP(MainFrameBackground, ColorUIBackground::ColorFieldMask);
        MainFrameBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainFrameBackground, ColorUIBackground::ColorFieldMask);
    
    FramePtr MainFrame = osg::Frame::create();
    beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);
       // Add the buttons to the mainframe so they will be displayed
       MainFrame->getChildren().addValue(ExampleSplitPanel);
       MainFrame->setLayout(MainFrameLayout);
       MainFrame->setBackground(MainFrameBackground);
       MainFrame->setAllInsets(5);
    endEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);

    // Create the Drawing Surface
    UIDrawingSurfacePtr TutorialDrawingSurface = UIDrawingSurface::create();
    beginEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask | UIDrawingSurface::EventProducerFieldMask);
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setRootFrame(MainFrame);
        TutorialDrawingSurface->setEventProducer(TutorialWindowEventProducer);
    endEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask | UIDrawingSurface::EventProducerFieldMask);
    
    // Create the UI Foreground Object
    UIForegroundPtr TutorialUIForeground = osg::UIForeground::create();

    beginEditCP(TutorialUIForeground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);
        TutorialUIForeground->setFramePositionOffset(Vec2s(0,0));
        TutorialUIForeground->setFrameBounds(Vec2f(0.5,0.5));
    endEditCP(TutorialUIForeground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);

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
    TutorialWindowEventProducer->openWindow(Pnt2s(50,50),
                                        Vec2s(900,900),
                                        "OpenSG 23SplitPanel Window");

    //Main Event Loop
    while(!ExitApp)
    {
        TutorialWindowEventProducer->update();
        TutorialWindowEventProducer->draw();
    }
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
void reshape(Vec2s Size)
{
    mgr->resize(Size.x(), Size.y());
}