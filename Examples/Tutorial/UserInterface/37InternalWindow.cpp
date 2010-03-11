// OpenSG Tutorial Example: Creating a Button Component
//
// This tutorial explains how to edit the basic features of
// a Button and a ToggleButtoncreated in the OSG User 
// Interface library.
// 
// Includes: Button PreferredSize, MaximumSize, MinimumSize, Font,
// Text,and adding a Button to a Scene.  Also note that clicking
// the Button causes it to appear pressed


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
#include "OSGUIDrawingSurface.h"
#include "OSGInternalWindow.h"
#include "OSGGraphics2D.h"
#include "OSGLookAndFeelManager.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

void display(void);
void reshape(Vec2f Size);

// 01 Button Headers
#include "OSGButton.h"
#include "OSGToggleButton.h"
#include "OSGUIFont.h"
#include "OSGColorLayer.h"
#include "OSGFlowLayout.h"

// Create a class to allow for the use of the Escape
// key to exit
class TutorialKeyListener : public KeyListener
{
  public:

    virtual void keyPressed(const KeyEventUnrecPtr e)
    {
        if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
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

      Create an Button Component and
      a simple Font.
      See 17Label_Font for more
      information about Fonts.

     ******************************************************/
    ButtonRefPtr ExampleButton = OSG::Button::create();

    UIFontRefPtr ExampleFont = OSG::UIFont::create();
    ExampleFont->setSize(16);

    ExampleButton->setMinSize(Vec2f(50, 25));
    ExampleButton->setMaxSize(Vec2f(200, 100));
    ExampleButton->setPreferredSize(Vec2f(100, 50));
    ExampleButton->setToolTipText("Button 1 ToolTip");

    ExampleButton->setText("Button 1");
    ExampleButton->setFont(ExampleFont);
    ExampleButton->setTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
    ExampleButton->setRolloverTextColor(Color4f(1.0, 0.0, 1.0, 1.0));
    ExampleButton->setActiveTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
    ExampleButton->setAlignment(Vec2f(1.0,0.0));


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
    ToggleButtonRefPtr ExampleToggleButton = OSG::ToggleButton::create();

    ExampleToggleButton->setSelected(false);
    ExampleToggleButton->setText("ToggleMe");
    ExampleToggleButton->setToolTipText("Toggle Button ToolTip");


    // Create Background to be used with the MainInternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
    MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    // Create The Internal Window
    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
    LayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();
    // Assign the Button to the MainInternalWindow so it will be displayed
    // when the view is rendered.
    MainInternalWindow->pushToChildren(ExampleButton);
    MainInternalWindow->setLayout(MainInternalWindowLayout);
    MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
    MainInternalWindow->setPosition(Pnt2f(50,50));
    MainInternalWindow->setPreferredSize(Vec2f(300,300));
    MainInternalWindow->setTitle(std::string("Internal Window 1"));

    // Create The Internal Window
    InternalWindowRefPtr MainInternalWindow2 = OSG::InternalWindow::create();
    LayoutRefPtr MainInternalWindowLayout2 = OSG::FlowLayout::create();
    // Assign the Button to the MainInternalWindow so it will be displayed
    // when the view is rendered.
    MainInternalWindow2->pushToChildren(ExampleToggleButton);
    MainInternalWindow2->setLayout(MainInternalWindowLayout2);
    MainInternalWindow2->setBackgrounds(MainInternalWindowBackground);
    MainInternalWindow2->setPosition(Pnt2f(150,150));
    MainInternalWindow2->setPreferredSize(Vec2f(300,300));
    MainInternalWindow2->setTitle(std::string("Internal Window 2"));
    MainInternalWindow2->setIconable(false);
    MainInternalWindow2->setAllwaysOnTop(true);

    // Create the Drawing Surface
    UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
    TutorialDrawingSurface->setGraphics(TutorialGraphics);
    TutorialDrawingSurface->setEventProducer(TutorialWindow);

    TutorialDrawingSurface->openWindow(MainInternalWindow);
    TutorialDrawingSurface->openWindow(MainInternalWindow2);
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
                               "37InternalWindow");

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
