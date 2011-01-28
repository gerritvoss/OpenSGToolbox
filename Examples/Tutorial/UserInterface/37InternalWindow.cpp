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

void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

// 01 Button Headers
#include "OSGButton.h"
#include "OSGToggleButton.h"
#include "OSGUIFont.h"
#include "OSGColorLayer.h"
#include "OSGFlowLayout.h"

void keyPressed(KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && 
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
}

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    {
        // Set up Window
        WindowEventProducerRecPtr TutorialWindow = createNativeWindow();
        TutorialWindow->initWindow();

        // Create the SimpleSceneManager helper
        SimpleSceneManager sceneManager;
        TutorialWindow->setDisplayCallback(boost::bind(display, &sceneManager));
        TutorialWindow->setReshapeCallback(boost::bind(reshape, _1, &sceneManager));

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

        TutorialWindow->connectKeyTyped(boost::bind(keyPressed, _1));

        // Make Torus Node (creates Torus in background of scene)
        NodeRecPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

        // Make Main Scene Node and add the Torus
        NodeRecPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(TorusGeometryNode);

        // Create the Graphics
        GraphicsRecPtr TutorialGraphics = Graphics2D::create();

        // Initialize the LookAndFeelManager to enable default settings
        LookAndFeelManager::the()->getLookAndFeel()->init();

        /******************************************************

          Create an Button Component and
          a simple Font.
          See 17Label_Font for more
          information about Fonts.

         ******************************************************/
        ButtonRecPtr ExampleButton = Button::create();

        UIFontRecPtr ExampleFont = UIFont::create();
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
        ToggleButtonRecPtr ExampleToggleButton = ToggleButton::create();

        ExampleToggleButton->setSelected(false);
        ExampleToggleButton->setText("ToggleMe");
        ExampleToggleButton->setToolTipText("Toggle Button ToolTip");


        // Create Background to be used with the MainInternalWindow
        ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        // Create The Internal Window
        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
        LayoutRecPtr MainInternalWindowLayout = FlowLayout::create();
        // Assign the Button to the MainInternalWindow so it will be displayed
        // when the view is rendered.
        MainInternalWindow->pushToChildren(ExampleButton);
        MainInternalWindow->setLayout(MainInternalWindowLayout);
        MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
        MainInternalWindow->setPosition(Pnt2f(50,50));
        MainInternalWindow->setPreferredSize(Vec2f(300,300));
        MainInternalWindow->setTitle(std::string("Internal Window 1"));

        // Create The Internal Window
        InternalWindowRecPtr MainInternalWindow2 = InternalWindow::create();
        LayoutRecPtr MainInternalWindowLayout2 = FlowLayout::create();
        // Assign the Button to the MainInternalWindow so it will be displayed
        // when the view is rendered.
        MainInternalWindow2->pushToChildren(ExampleToggleButton);
        MainInternalWindow2->setLayout(MainInternalWindowLayout2);
        MainInternalWindow2->setBackgrounds(MainInternalWindowBackground);
        MainInternalWindow2->setPosition(Pnt2f(150,150));
        MainInternalWindow2->setPreferredSize(Vec2f(300,300));
        MainInternalWindow2->setTitle(std::string("Allways on top window"));
        MainInternalWindow2->setIconable(false);
        MainInternalWindow2->setAllwaysOnTop(true);

        // Create the Drawing Surface
        UIDrawingSurfaceRecPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);

        TutorialDrawingSurface->openWindow(MainInternalWindow);
        TutorialDrawingSurface->openWindow(MainInternalWindow2);
        // Create the UI Foreground Object
        UIForegroundRecPtr TutorialUIForeground = UIForeground::create();
        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);


        // Tell the Manager what to manage
        sceneManager.setRoot(scene);

        // Add the UI Foreground Object to the Scene
        ViewportRecPtr TutorialViewport = sceneManager.getWindow()->getPort(0);
        TutorialViewport->addForeground(TutorialUIForeground);

        // Show the whole Scene
        sceneManager.showAll();


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "37InternalWindow");

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}


// Callback functions


// Redraw the window
void display(SimpleSceneManager *mgr)
{
    mgr->redraw();
}

// React to size changes
void reshape(Vec2f Size, SimpleSceneManager *mgr)
{
    mgr->resize(Size.x(), Size.y());
}
