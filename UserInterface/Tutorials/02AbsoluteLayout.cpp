// OpenSG Tutorial Example: Using the AbsoluteLayout
//
// This tutorial explains how to place ExampleButtons within a 
// frame utilizing the Absolute Layout to manage the layout 
// through the OSG User Interface library.
// 
// Includes: placing multiple ExampleButtons and using 
// AbsoluteLayoutConstraints to locate the ExampleButtons.

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

// Include AbsoluteLayout and AbsoluteLayoutConstraints header files
#include <OpenSG/UserInterface/OSGAbsoluteLayout.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>

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

        Create three Button Components and three 
        AbsoluteLayoutConstraints.

        AbsoluteLayoutConstraints are used within the 
        AbsoluteLayout to define where the Components 
        will be placed.  Each Component is individually
        placed to an exact location using an 
        AbsoluteLayoutConstraint.

    ******************************************************/

    ButtonPtr ExampleButton1 = osg::Button::create();
    ButtonPtr ExampleButton2 = osg::Button::create();
    ButtonPtr ExampleButton3 = osg::Button::create();
    
    AbsoluteLayoutConstraintsPtr ExampleButtonConstraints1 = osg::AbsoluteLayoutConstraints::create();
    AbsoluteLayoutConstraintsPtr ExampleButtonConstraints2 = osg::AbsoluteLayoutConstraints::create();
    AbsoluteLayoutConstraintsPtr ExampleButtonConstraints3 = osg::AbsoluteLayoutConstraints::create();

    /******************************************************

        Edit the AbsoluteLayoutConstraints.

        -setPositition(Pnt2s): Determine the location
            the Constraints represent within the 
            AbsoluteLayout, referenced from the 
            upper left hand corner of the Layout's
            Container.  

        Note that this is not a relative location, so
        if the Container becomes resized and the 
        AbsoluteLayoutConstraints would place the 
        Component they are assigned to outside the
        Layout, then the Component will not be 
        displayed.  Depending on where the 
        
        Define the AbsoluteLayoutConstraints (where Buttons 
        are located in the Layout).  setPosition gives you 
        the location of the Button relative to the Layout
        Manager's upper left hand corner.  Buttons will
        not display if their AbsoluteLayoutConstraints 
        place them outside the Frame in which they are to
        be rendered (the part within the Frame still does
        display).  Changing the window size shows an 
        example of this.

    ******************************************************/
  
   beginEditCP(ExampleButtonConstraints1, AbsoluteLayoutConstraints::PositionFieldMask);
        ExampleButtonConstraints1->setPosition(Pnt2s(0,150));
   endEditCP(ExampleButtonConstraints1, AbsoluteLayoutConstraints::PositionFieldMask);

   beginEditCP(ExampleButtonConstraints2, AbsoluteLayoutConstraints::PositionFieldMask);
        ExampleButtonConstraints2->setPosition(Pnt2s(200,200));
   endEditCP(ExampleButtonConstraints2, AbsoluteLayoutConstraints::PositionFieldMask);
    
   // Note that this will cause the ExampleButton's position to overlap with Button2
   // when the program is run; the AbsoluteLayoutConstraints will overlap
   // if the specified coordinates overlap
   beginEditCP(ExampleButtonConstraints3, AbsoluteLayoutConstraints::PositionFieldMask);
        ExampleButtonConstraints3->setPosition(Pnt2s(150,220));
   endEditCP(ExampleButtonConstraints3, AbsoluteLayoutConstraints::PositionFieldMask);

    /******************************************************

        Edit Button Components and assign Text,
        PreferredSize, and AbsoluteLayoutConstraints.

        By assigning AbsoluteLayoutContraints to
        Components, those Components are then
        displayed in the Layout according to their
        AbsoluteLayoutConstraints.  

        -setContraints(ConstraintName): Determines
            the Constraints for the Component.  In
            AbsoluteLayout, Components will not
            be displayed without Constraints being
            assigned.

        Note: see below for importance of order
        when adding Components to AbsoluteLayouts 

    ******************************************************/

   beginEditCP(ExampleButton1, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);
        ExampleButton1->setPreferredSize(Vec2s(100,50));
        ExampleButton1->setText("Button 1");
        ExampleButton1->setConstraints(ExampleButtonConstraints1);
   endEditCP(ExampleButton1, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);

    beginEditCP(ExampleButton2, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);
        ExampleButton2->setPreferredSize(Vec2s(100,50));
        ExampleButton2->setText("Button 2");
        ExampleButton2->setConstraints(ExampleButtonConstraints2);
    endEditCP(ExampleButton2, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);

    beginEditCP(ExampleButton3, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);
        ExampleButton3->setPreferredSize(Vec2s(100,50));
        ExampleButton3->setText("Button 3");
        ExampleButton3->setConstraints(ExampleButtonConstraints3);
    endEditCP(ExampleButton3, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);

    // Create Background to be used with the Main Frame
    ColorUIBackgroundPtr MainFrameBackground = osg::ColorUIBackground::create();
    beginEditCP(MainFrameBackground, ColorUIBackground::ColorFieldMask);
        MainFrameBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainFrameBackground, ColorUIBackground::ColorFieldMask);
    
    // Create The Main Frame
    FramePtr MainFrame = osg::Frame::create();
    LayoutPtr MainFrameLayout = osg::AbsoluteLayout::create();
    beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);
       // Add the ExampleButtons to the mainframe so they will be displayed.
       // They are displayed in reverse order, so in this case, since ExampleButton2
       // and ExampleButton3 are in conflict with their locations, ExampleButton2 will cover 
       // ExampleButton3.  By commenting out their addValue commands and uncommenting 
       // the other two, this will be reversed.
       MainFrame->getChildren().addValue(ExampleButton1);
       MainFrame->getChildren().addValue(ExampleButton3);
       MainFrame->getChildren().addValue(ExampleButton2);
       // MainFrame->getChildren().addValue(ExampleButton2);
       // MainFrame->getChildren().addValue(ExampleButton3);
       MainFrame->setLayout(MainFrameLayout);
       MainFrame->setBackground(MainFrameBackground);
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
                                        Vec2s(550,550),
                                        "OpenSG 02AbsoluteLayout Window");

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
