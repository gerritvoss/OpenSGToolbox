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

    // Make Main Scene Node
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        scene->setCore(osg::Group::create());
 
        // Add the Torus as a Child
        scene->addChild(TorusGeometryNode);
    }
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    // Create the Graphics
    GraphicsPtr TutorialGraphics = osg::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default 
    // settings for the Button
    LookAndFeelManager::the()->getLookAndFeel()->init();




    /******************************************************
            
                Creates some Button components
                and change some PreferredSizes

    ******************************************************/
    ButtonPtr button1 = osg::Button::create();
    ButtonPtr button2 = osg::Button::create();
    ButtonPtr button3 = osg::Button::create();
    ButtonPtr button4 = osg::Button::create();
    ButtonPtr button5 = osg::Button::create();
    ButtonPtr button6 = osg::Button::create();

    beginEditCP(button1, Component::PreferredSizeFieldMask);
        button1->setPreferredSize( Vec2s (200, 50));
    endEditCP(button1, Component::PreferredSizeFieldMask);

    beginEditCP(button4, Component::PreferredSizeFieldMask);
        button4->setPreferredSize( Vec2s (50, 50));
    endEditCP(button4, Component::PreferredSizeFieldMask);



    /******************************************************
            
                Creates and sets up two Panel 
                components to place Buttons within

    ******************************************************/

    PanelPtr panel1 = osg::Panel::create();
    PanelPtr panel2 = osg::Panel::create();
    FlowLayoutPtr flowLayout = osg::FlowLayout::create();
    
    beginEditCP(flowLayout);
        flowLayout->setHorizontalGap(3);
        flowLayout->setVerticalGap(3);
    endEditCP(flowLayout);

    beginEditCP(panel1, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);
        panel1->getChildren().addValue(button1);
        panel1->getChildren().addValue(button2);
        panel1->getChildren().addValue(button3);
        panel1->setLayout(flowLayout);
    endEditCP(panel1, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);
    beginEditCP(panel2, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);
        panel2->getChildren().addValue(button4);
        panel2->getChildren().addValue(button5);
        panel2->getChildren().addValue(button6);
        panel2->setLayout(flowLayout);
    endEditCP(panel2, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);


    
    
    // Creates a BorderLayout and Constraints (this causes SplitPanel to 
    // automatically fill entire frame)
    BorderLayoutPtr MainFrameLayout = osg::BorderLayout::create();
    BorderLayoutConstraintsPtr SplitPanelConstraints = osg::BorderLayoutConstraints::create();

    beginEditCP(SplitPanelConstraints);
        SplitPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
    endEditCP(SplitPanelConstraints);
        
    /******************************************************
            
        Creates and sets up SplitPanel

        -setMinComponent/setMaxComponent(component): this 
            is how to add components to the SplitPanel.  
            Note that if you do not add both an empty 
            panel will be added automatically.
        -setAlignment(ALIGNMENT): determines the alignment
            of the split aspect.  Takes a VERTICAL_ALIGNMENT
            or HORIZONTAL_ALIGNMENT input.  The default is
            Horizontal with an east/west split. The 
            minComponent set previously is the west or north
            component of the panel (depending on the alignment)
            and the max is the east or west component.
            The default is horizontal.
        -setDividerPosition("smart" REAL): Determines the initial 
            location of the divider.  Note that this REAL is
            a percentage if between 0.0 and 1.0 (inclusive) 
            and absolute is greater than 1.0.  Also note that
            when resizing a window with a percentage, the
            divider will move, but with absolute, it does
            not until it no longer fits in the panel.
        -setDividerSize(SIZE): determines divider size 
        -setExpandable(TRUE/FALSE): Determines whether
            divider can be moved by user.  Default is
            TRUE (is movable) while FALSE removes
            the users ability to move the divider
        -setMaxDividerPosition("smart" REAL): Set the
            maximum position for the divider.
        -setMinDividerPosition("smart" REAL): Set the
            minimum position for the divider.  Note 
            that for both Max/Min, the "smart" REAL
            follows same format as in setDividerPosition;
            it is a percentage if between 0.0 and 1.0 
            and absolute when > 1.0


                

    ******************************************************/
    
    SplitPanelPtr SplitPanel = osg::SplitPanel::create();

    beginEditCP(SplitPanel);
        // Sets the BorderContraints to it
        SplitPanel->setConstraints(SplitPanelConstraints);
        SplitPanel->setMinComponent(panel1);
        SplitPanel->setMaxComponent(panel2);
        //SplitPanel->setAlignment(VERTICAL_ALIGNMENT);
        //SplitPanel->setDividerPosition(.25); // this is a percentage
        SplitPanel->setDividerPosition(300); // this is an absolute (300 > 1.0) 
            //location from the left/top
         SplitPanel->setDividerSize(5);
        // SplitPanel->setExpandable(false);
        SplitPanel->setMaxDividerPosition(.9);
        SplitPanel->setMinDividerPosition(220);
        
        // also, if you want to change the way the divider looks, you can always set a
        // DrawObjectCanvas in place of the default divider
        // SplitPanel->setDividerDrawObject(drawObjectName);
    endEditCP(SplitPanel);
    
     // Create The Main Frame

    // Create Background to be used with the Main Frame
    ColorUIBackgroundPtr MainFrameBackground = osg::ColorUIBackground::create();
    beginEditCP(MainFrameBackground, ColorUIBackground::ColorFieldMask);
        MainFrameBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainFrameBackground, ColorUIBackground::ColorFieldMask);
    
    FramePtr MainFrame = osg::Frame::create();
    beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);
       // Add the buttons to the mainframe so they will be displayed
       MainFrame->getChildren().addValue(SplitPanel);
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