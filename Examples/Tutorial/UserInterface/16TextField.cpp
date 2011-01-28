// OpenSG Tutorial Example: Creating a Button Component
//
// This tutorial explains how to edit the basic features of
// a Button created in the OSG User Interface library.
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
#include "OSGLayers.h"
#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"
#include "OSGGraphics2D.h"
#include "OSGLookAndFeelManager.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

// 16TextField Headers
#include "OSGButton.h"
#include "OSGLineBorder.h"
#include "OSGFlowLayout.h"
#include "OSGLookAndFeelManager.h"
#include "OSGUIFont.h"
#include "OSGTextField.h"

void keyPressed(KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
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

        // Create a simple Font to be used with the TextField
        UIFontRecPtr sampleFont = UIFont::create();
        sampleFont->setSize(16);

        /******************************************************


          Create and edit the TextField.  A TextField is 
          a Component which allows a single line of text
          to be displayed.  Text can be entered via the
          keyboard, and selected with arrow keys or
          the Mouse.

          -setTextColor(Color4f): Determine the 
          Text Color.
          setSelectionBoxColor(Color4f): Determine
          the Color of highlighting around
          selected Text.
          -setSelectionTextColor(Color4f): Determine
          the Color of selected Text.
          -setText("TextToBeDisplayed"): Determine
          initial Text within TextField.
          -setFont(FontName): Determine the Font
          used within TextField.
          -setSelectionStart(StartCharacterNumber):
          Determine the character with which  
          the selection will initially start.
          -setSelectionEnd(EndCharacterNumber): 
          Determine the character which the
          selection ends before.
          -setAlignment(float): Determine 
          the alignment of the text.  
          The float is a percentage is from the 
          top of the text [0.0-1.0].  Note: be 
          sure to visually verify this, as due
          to font size and line size this does
          not always place it exactly
          at the percentage point.

         ******************************************************/

        // Create a TextField component
        TextFieldRecPtr ExampleTextField = TextField::create();

        ExampleTextField->setPreferredSize(Vec2f(100, 50));
        ExampleTextField->setTextColor(Color4f(0.0, 0.0, 0.0, 1.0));
        ExampleTextField->setSelectionBoxColor(Color4f(0.0, 0.0, 1.0, 1.0));
        ExampleTextField->setSelectionTextColor(Color4f(1.0, 1.0, 1.0, 1.0));
        ExampleTextField->setText("What");
        ExampleTextField->setFont(sampleFont);
        // The next two functions will select the "a" from above
        ExampleTextField->setSelectionStart(2);
        ExampleTextField->setSelectionEnd(3);
        ExampleTextField->setAlignment(Vec2f(0.0,0.5));

        // Create another TextField Component
        TextFieldRecPtr ExampleTextField2 = TextField::create();
        ExampleTextField2->setText("");
        ExampleTextField2->setEmptyDescText("Write in me, please");
        ExampleTextField2->setPreferredSize(Vec2f(200.0f,ExampleTextField2->getPreferredSize().y()));


        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        LayoutRecPtr MainInternalWindowLayout = FlowLayout::create();

        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
        MainInternalWindow->pushToChildren(ExampleTextField);
        MainInternalWindow->pushToChildren(ExampleTextField2);
        MainInternalWindow->setLayout(MainInternalWindowLayout);
        MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
        MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setDrawTitlebar(false);
        MainInternalWindow->setResizable(false);

        // Create the Drawing Surface
        UIDrawingSurfaceRecPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);

        TutorialDrawingSurface->openWindow(MainInternalWindow);

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
                                   "16TextField");

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
