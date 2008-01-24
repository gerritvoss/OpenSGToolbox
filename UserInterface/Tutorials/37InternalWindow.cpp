// OpenSG Tutorial Example: Creating a Button Component
//
// This tutorial explains how to edit the basic features of
// a Button and a ToggleButtoncreated in the OSG User 
// Interface library.
// 
// Includes: Button PreferredSize, MaximumSize, MinimumSize, Font,
// Text,and adding a Button to a Scene.  Also note that clicking
// the Button causes it to appear pressed


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
#include <OpenSG/UserInterface/OSGInternalWindow.h>
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

// 01 Button Headers
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGToggleButton.h>
#include <OpenSG/UserInterface/OSGUIFont.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>

// Create a class to allow for the use of the Escape
// key to exit
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

                 Create an Button Component and
                 a simple Font.
                 See 17Label_Font for more
                 information about Fonts.

    ******************************************************/
    ButtonPtr ExampleButton = osg::Button::create();

    UIFontPtr ExampleFont = osg::UIFont::create();
    beginEditCP(ExampleFont, UIFont::SizeFieldMask);
        ExampleFont->setSize(16);
    endEditCP(ExampleFont, UIFont::SizeFieldMask);

    /******************************************************

            Edit the Button's characteristics.
            Note: the first 4 functions can
            be used with any Component and 
            are not specific to Button.

            -setMinSize(Vec2s): Determine the 
                Minimum    Size of the Component.
                Some Layouts will automatically
                resize Components; this prevents
                the Size from going below a
                certain value.
            -setMaxSize(Vec2s): Determine the 
                Maximum Size of the Component.
            -setPreferredSize(Vec2s): Determine
                the Preferred Size of the Component.
                This is what the Component will
                be displayed at unless changed by
                another Component (such as a 
                Layout).
            -setToolTipText("Text"): Determine
                what text is displayed while
                Mouse is hovering above Component.
                The word Text will be displayed
                in this case.
            
            Functions specfic to Button:
            -setText("DesiredText"): Determine 
                the Button's text.  It will read
                DesiredText in this case.
            -setFont(FontName): Determine the 
                Font to be used on the Button.
            -setTextColor(Color4f): Determine the
                Color for the text.
            -setRolloverTextColor(Color4f): Determine
                what the text Color will be when
                the Mouse Cursor is above the 
                Button.
            -setActiveTextColor(Color4f): Determine
                what the text Color will be when
                the Button is pressed (denoted by
                Active).
            -setVerticalAlignment(Float OR Enum):
                Determine the Vertical Alignment
                of the text.  The Float value is 
                in [0.0, 1.0] and the Enums are:
                VERTICAL_CENTER, VERTICAL_TOP, 
                or VERTICAL_BOTTOM.
            -setHorizontalAlignmnet(Real32 OR Enum):
                Determine the Horizontal Alignment
                of the text.  The Float value is 
                in [0.0, 1.0] and the Enums are:
                HORIZONTAL_CENTER, HORIZONTAL_LEFT, 
                or HORIZONTAL_RIGHT.

    ******************************************************/
    beginEditCP(ExampleButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask | Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask);
            ExampleButton->setMinSize(Vec2s(50, 25));
            ExampleButton->setMaxSize(Vec2s(200, 100));
            ExampleButton->setPreferredSize(Vec2s(100, 50));
            ExampleButton->setToolTipText("Button 1 ToolTip");

            ExampleButton->setText("Button 1");
            ExampleButton->setFont(ExampleFont);
            ExampleButton->setTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
            ExampleButton->setRolloverTextColor(Color4f(1.0, 0.0, 1.0, 1.0));
            ExampleButton->setActiveTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
            ExampleButton->setVerticalAlignment(0.0);
            ExampleButton->setHorizontalAlignment(1.0);
    endEditCP(ExampleButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask | Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask);
            

    /******************************************************

        Create a ToggleButton and determine its 
        characteristics.  ToggleButton inherits
        off of Button, so all characteristsics
        used above can be used with ToggleButtons
        as well.

        The only difference is that when pressed,
        ToggleButton remains pressed until pressed 
        again.

        -setSelected(bool): Determine whether the 
            ToggleButton is Selected (true) or
            deselected (false).  

    ******************************************************/
    ToggleButtonPtr ExampleToggleButton = osg::ToggleButton::create();
    
    beginEditCP(ExampleToggleButton, ToggleButton::SelectedFieldMask | ToggleButton::TextFieldMask | ToggleButton::ToolTipTextFieldMask);
        ExampleToggleButton->setSelected(false);
        ExampleToggleButton->setText("ToggleMe");
        ExampleToggleButton->setToolTipText("Toggle Button ToolTip");
    endEditCP(ExampleToggleButton, ToggleButton::SelectedFieldMask | ToggleButton::TextFieldMask | ToggleButton::ToolTipTextFieldMask);


    // Create Background to be used with the MainInternalWindow
    ColorUIBackgroundPtr MainInternalWindowBackground = osg::ColorUIBackground::create();
    beginEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);

    // Create The Internal Window
    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
    LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::PositionFieldMask | InternalWindow::PreferredSizeFieldMask | InternalWindow::TitleFieldMask);
       // Assign the Button to the MainInternalWindow so it will be displayed
       // when the view is rendered.
       MainInternalWindow->getChildren().addValue(ExampleButton);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
       MainInternalWindow->setPosition(Pnt2s(50,50));
       MainInternalWindow->setPreferredSize(Vec2s(300,300));
	   MainInternalWindow->setTitle(std::string("Internal Window 1"));
    endEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::PositionFieldMask | InternalWindow::PreferredSizeFieldMask | InternalWindow::TitleFieldMask);

    TutorialKeyListener TheKeyListener;
    MainInternalWindow->addKeyListener(&TheKeyListener);

    // Create The Internal Window
    InternalWindowPtr MainInternalWindow2 = osg::InternalWindow::create();
    LayoutPtr MainInternalWindowLayout2 = osg::FlowLayout::create();
	beginEditCP(MainInternalWindow2, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::PositionFieldMask | InternalWindow::PreferredSizeFieldMask | InternalWindow::TitleFieldMask);
       // Assign the Button to the MainInternalWindow so it will be displayed
       // when the view is rendered.
       MainInternalWindow2->getChildren().addValue(ExampleToggleButton);
       MainInternalWindow2->setLayout(MainInternalWindowLayout2);
       MainInternalWindow2->setBackgrounds(MainInternalWindowBackground);
       MainInternalWindow2->setPosition(Pnt2s(150,150));
       MainInternalWindow2->setPreferredSize(Vec2s(300,300));
	   MainInternalWindow2->setTitle(std::string("Internal Window 2"));
    endEditCP(MainInternalWindow2, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::PositionFieldMask | InternalWindow::PreferredSizeFieldMask | InternalWindow::TitleFieldMask);

    // Create the Drawing Surface
    UIDrawingSurfacePtr TutorialDrawingSurface = UIDrawingSurface::create();
    beginEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::InternalWindowsFieldMask | UIDrawingSurface::EventProducerFieldMask);
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindowEventProducer);
    endEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::InternalWindowsFieldMask | UIDrawingSurface::EventProducerFieldMask);
    
	TutorialDrawingSurface->openWindow(MainInternalWindow);
	TutorialDrawingSurface->openWindow(MainInternalWindow2);
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

    TutorialWindowEventProducer->openWindow(Pnt2s(50,50),
                                        Vec2s(550,550),
                                        "OpenSG 37InternalWindow Window");

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
