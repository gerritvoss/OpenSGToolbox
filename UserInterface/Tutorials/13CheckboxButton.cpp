// OpenSG Tutorial Example: Creating a Checkbox Button Component
//
// This tutorial explains how to edit the basic features of
// a Checkbox Button created in the OSG User Interface library.
// 
// Includes: 
//
//Checkbox buttons are special buttons that can are toggled between active and inactive when they are selected


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

// 12CheckboxButton Headers
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayout.h>
#include <OpenSG/UserInterface/OSGUIFont.h>
#include <OpenSG/UserInterface/OSGCheckboxButton.h>
#include <OpenSG/UserInterface/OSGRadioButton.h>

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
    
    WindowEventProducerPtr TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();
    
    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TutorialWindowEventProducer->addWindowListener(&TheTutorialWindowListener);

    //Attach Mouse Listener
    //TutorialWindowEventProducer->addMouseListener(new TutorialMouseListener());
    //Attach Mouse Wheel Listener
    //TutorialWindowEventProducer->addMouseWheelListener(new TutorialMouseWheelListener());
    //Attach Key Listener
    //TutorialWindowEventProducer->addKeyListener(new TutorialKeyListener());
    //Attach Window Listener
    //TutorialWindowEventProducer->addWindowListener(new TutorialWindowListener());

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

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();


    /******************************************************

        Create and edit a CheckboxButton.

		Note: the only function call shown 
		specific to	CheckboxButton is setSelected.
		In DefaultLookAndFeel, the options 
		for changing the style of the CheckBox
		are shown.  CheckboxButton also 
		inherits off Button so all features
		of Button may be used.

		-setSelected(bool): Determines if the 
			CheckboxButton is checked(true) or 
			not checked(false).

    ******************************************************/
    CheckboxButtonPtr ExampleCheckboxButton = osg::CheckboxButton::create();
    beginEditCP(ExampleCheckboxButton, CheckboxButton::MinSizeFieldMask | CheckboxButton::MaxSizeFieldMask | CheckboxButton::PreferredSizeFieldMask | CheckboxButton::SizeFieldMask |
        CheckboxButton::TextFieldMask | CheckboxButton::VerticalAlignmentFieldMask | CheckboxButton::HorizontalAlignmentFieldMask | CheckboxButton::SelectedFieldMask);
        ExampleCheckboxButton->setMinSize( Vec2s (50, 25));
        ExampleCheckboxButton->setMaxSize( Vec2s (300, 100));
        ExampleCheckboxButton->setPreferredSize( Vec2s (200, 50));
        ExampleCheckboxButton->setEnabled(true);
        ExampleCheckboxButton->setText("Checkbox Button");
        ExampleCheckboxButton->setVerticalAlignment(0.5);
        ExampleCheckboxButton->setHorizontalAlignment(0.5);
        ExampleCheckboxButton->setSelected(true);
   endEditCP(ExampleCheckboxButton, CheckboxButton::MinSizeFieldMask | CheckboxButton::MaxSizeFieldMask | CheckboxButton::PreferredSizeFieldMask | CheckboxButton::SizeFieldMask |
        CheckboxButton::TextFieldMask | CheckboxButton::VerticalAlignmentFieldMask | CheckboxButton::HorizontalAlignmentFieldMask | CheckboxButton::SelectedFieldMask);

    
    // Create The Main Frame
    FramePtr MainFrame = osg::Frame::create();
    LayoutPtr MainFrameLayout = osg::AbsoluteLayout::create();
    beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);
       MainFrame->getChildren().addValue(ExampleCheckboxButton);
       MainFrame->setLayout(MainFrameLayout);
    endEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);

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
                                        Vec2s(550,550),
                                        "OpenSG 13CheckboxButton Window");

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