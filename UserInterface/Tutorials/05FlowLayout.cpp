// OpenSG Tutorial Example: Using the Flow Layout
//        to place Components 
//
// This tutorial explains how to place Buttons within a 
// frame utilizing the Flow Layout command to 
// manage the layout through the OSG User Interface library.
// 
// Includes: placing multiple ExampleButtons using Flow Layout

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

// 05FlowLayout Headers
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
#include <OpenSG/UserInterface/OSGBevelBorder.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>

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
            
            Create and edit a few Button Components. 

    ******************************************************/
    ButtonPtr ExampleButton1 = osg::Button::create();
    ButtonPtr ExampleButton2 = osg::Button::create();
    ButtonPtr ExampleButton3 = osg::Button::create();
    ButtonPtr ExampleButton4 = osg::Button::create();
    ButtonPtr ExampleButton5 = osg::Button::create();
    ButtonPtr ExampleButton6 = osg::Button::create();

    beginEditCP(ExampleButton1, Button::PreferredSizeFieldMask);
        ExampleButton1->setPreferredSize( Vec2s (200, 50));
    endEditCP(ExampleButton1, Button::PreferredSizeFieldMask);

    beginEditCP(ExampleButton4, Button::PreferredSizeFieldMask);
        ExampleButton4->setPreferredSize( Vec2s (50, 50));
    endEditCP(ExampleButton4, Button::PreferredSizeFieldMask);

    /******************************************************

        Create Flow Layout.  Flow Layout arranges objects
        automatically within the Frame, so that depending 
        on Frame size, the objects may appear in a vertical
        line, horizontal line, or multiple lines.  Objects 
        fill from the upper left hand corner of the Frame
        across, then down (when the line becomes full) while
        arranged Horizontally, or from the upper left hand
        corner across when arranged Vertically, starting a 
        new column when necessary.

        You can experiment with this by changing the window 
        size, changing the orientation, changing the 
        PreferredSize of the Buttons, or adding more 
		Buttons to the view.

        Note that if the Frame is too small or resized
		too much, the FlowLayout will become slightly
		distorted.  For Layouts which will often
		be dynamically changed, FlowLayout is not
		the best choice.
	
		-setHorizontalGap(int): Determine the Horizontal
			gap in pixels between Components in 
			FlowLayout.
		-setVerticalGap(int): Determine the Vertical
			gap in pixels between Components in 
			FlowLayout.
		-setAlignment(ENUM): Determine whether the
			Layout is arranged Vertically or
			Horizontally.  Takes HORIZONTAL_ALIGNMENT
			or VERTICAL_ALIGNMENT arguments.
		-setMajorAxisAlignment(ENUM): Determines
			the alignment of the entire Layout 
			within its Container.  See below.
		-setMinorAxistAlignment(ENUM): Determines
			the alignment of Components within
			the Layout.  See below.

		Both of the last two functions take the
		following arguments: AXIS_MAX_ALIGNMENT, 
		AXIS_CENTER_ALIGNMENT, and AXIS_MIN_ALIGNMENT.
		MAX puts it to the bottom/right, CENTER
		centers it, and MIN puts it to the
		top/left (for Vertical/Horizontal as
		set above, respectively).

    ******************************************************/
    FlowLayoutPtr MainFrameLayout = osg::FlowLayout::create();
    beginEditCP(MainFrameLayout, FlowLayout::HorizontalGapFieldMask | FlowLayout::VerticalGapFieldMask | FlowLayout::AlignmentFieldMask | FlowLayout::MajorAxisAlignmentFieldMask | FlowLayout::MinorAxisAlignmentFieldMask);
        MainFrameLayout->setHorizontalGap(3);
        MainFrameLayout->setVerticalGap(3);
        MainFrameLayout->setAlignment(VERTICAL_ALIGNMENT);
        MainFrameLayout->setMajorAxisAlignment(AXIS_CENTER_ALIGNMENT);
        MainFrameLayout->setMinorAxisAlignment(AXIS_MAX_ALIGNMENT);
    endEditCP(MainFrameLayout, FlowLayout::HorizontalGapFieldMask | FlowLayout::VerticalGapFieldMask | FlowLayout::AlignmentFieldMask | FlowLayout::MajorAxisAlignmentFieldMask | FlowLayout::MinorAxisAlignmentFieldMask);
    
    // Create The Main Frame
    // Create Background to be used with the Main Frame
    ColorUIBackgroundPtr MainFrameBackground = osg::ColorUIBackground::create();
    beginEditCP(MainFrameBackground, ColorUIBackground::ColorFieldMask);
        MainFrameBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainFrameBackground, ColorUIBackground::ColorFieldMask);
    
    FramePtr MainFrame = osg::Frame::create();
    beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);
       // Add the ExampleButtons to the mainframe so they will be displayed
       MainFrame->getChildren().addValue(ExampleButton1);
       MainFrame->getChildren().addValue(ExampleButton2);
       MainFrame->getChildren().addValue(ExampleButton3);
       MainFrame->getChildren().addValue(ExampleButton4);
       MainFrame->getChildren().addValue(ExampleButton5);
       MainFrame->getChildren().addValue(ExampleButton6);
       // Add the Layout to the MainFrame
       MainFrame->setLayout(MainFrameLayout);
       MainFrame->setBackground(MainFrameBackground);
	   // Add a 10 pixel "padding" inside the MainFrame
       MainFrame->setAllInsets(10);
    endEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);

    //Create the Drawing Surface
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
                                        "OpenSG 05FlowLayout Window");

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