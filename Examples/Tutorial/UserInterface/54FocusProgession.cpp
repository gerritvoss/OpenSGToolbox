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

// 01 Button Headers
#include "OSGButton.h"
#include "OSGToggleButton.h"
#include "OSGUIFont.h"
#include "OSGColorLayer.h"
#include "OSGFlowLayout.h"
#include "OSGPolygonUIDrawObject.h"
#include "OSGUIDrawObjectCanvas.h"

// Create a class to allow for the use of the Ctrl+q
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

/******************************************************

  Create an ActionListener to display text
  in the Console Window when the Button is
  pressed (causing an action).

 ******************************************************/

class ExampleButtonActionListener : public ActionListener
{
  public:

    virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
        std::cout << "Button 1 Action" << std::endl;
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

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindow);


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

    ColorLayerRefPtr ButtonFocusedBackground = OSG::ColorLayer::create();
    ButtonFocusedBackground->setColor(Color4f(1.0,0.0,0.0,1.0));

    ButtonRefPtr ExampleButton = OSG::Button::create();
    ButtonRefPtr ExampleButton2 = OSG::Button::create();
    ButtonRefPtr ExampleButton3 = OSG::Button::create();

    UIFontRefPtr ExampleFont = OSG::UIFont::create();
    ExampleFont->setSize(16);

    ExampleButton->setMinSize(Vec2f(50, 25));
    ExampleButton->setMaxSize(Vec2f(200, 100));
    ExampleButton->setPreferredSize(Vec2f(100, 50));

    ExampleButton->setFocused(true);
    ExampleButton->setText("Button 1");
    ExampleButton->setFont(ExampleFont);
    ExampleButton->setTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
    ExampleButton->setRolloverTextColor(Color4f(1.0, 0.0, 1.0, 1.0));
    ExampleButton->setActiveTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
    ExampleButton->setAlignment(Vec2f(1.0,0.0));
    ExampleButton->setFocusedBackground(ButtonFocusedBackground);
//    ExampleButton->setFocusIndex(5);

    ExampleButton2->setMinSize(Vec2f(50, 25));
    ExampleButton2->setMaxSize(Vec2f(200, 100));
    ExampleButton2->setPreferredSize(Vec2f(100, 50));

    ExampleButton2->setText("Button 2");
    ExampleButton2->setFont(ExampleFont);
    ExampleButton2->setTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
    ExampleButton2->setRolloverTextColor(Color4f(1.0, 0.0, 1.0, 1.0));
    ExampleButton2->setActiveTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
    ExampleButton2->setAlignment(Vec2f(1.0,0.0));
    ExampleButton2->setFocusedBackground(ButtonFocusedBackground);

    ExampleButton3->setMinSize(Vec2f(50, 25));
    ExampleButton3->setMaxSize(Vec2f(200, 100));
    ExampleButton3->setPreferredSize(Vec2f(100, 50));

    ExampleButton3->setText("Button 3");
    ExampleButton3->setFont(ExampleFont);
    ExampleButton3->setTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
    ExampleButton3->setRolloverTextColor(Color4f(1.0, 0.0, 1.0, 1.0));
    ExampleButton3->setActiveTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
    ExampleButton3->setAlignment(Vec2f(1.0,0.0));
    ExampleButton3->setFocusedBackground(ButtonFocusedBackground);

    // Create an ActionListener and assign it to ExampleButton
    // This Class is defined above, and will cause the output
    // window to display "Button 1 Action" when pressed
    ExampleButtonActionListener TheExampleButtonActionListener;
    ExampleButton->addActionListener(&TheExampleButtonActionListener);

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
    MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
    LayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();
    MainInternalWindow->pushToChildren(ExampleButton);
    MainInternalWindow->pushToChildren(ExampleButton2);
    MainInternalWindow->pushToChildren(ExampleButton3);
    MainInternalWindow->setLayout(MainInternalWindowLayout);
    MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
    MainInternalWindow->setFocusedBackground(ButtonFocusedBackground);
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
                               "54FocusProgession");

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
