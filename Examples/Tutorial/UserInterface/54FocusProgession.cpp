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

#include "OSGButton.h"
#include "OSGTextField.h"
#include "OSGPasswordField.h"
#include "OSGToggleButton.h"
#include "OSGColorLayer.h"
#include "OSGFlowLayout.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

//Ctrl+q handler
void keyTyped(KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() &
       KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
}

/******************************************************

  Create an ActionListener to display text
  in the Console Window when the Button is
  pressed (causing an action).

 ******************************************************/

void actionPerformed(ActionEventDetails* const details)
{
    std::cout << "Button 1 Action" << std::endl;
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

        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1));

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

        ButtonRefPtr ExampleButton = OSG::Button::create();
        ExampleButton->setMinSize(Vec2f(50, 25));
        ExampleButton->setMaxSize(Vec2f(200, 100));
        ExampleButton->setPreferredSize(Vec2f(100, 50));
        ExampleButton->setText("Button 1");

        // Create an ActionListener and assign it to ExampleButton
        // This Class is defined above, and will cause the output
        // window to display "Button 1 Action" when pressed
        ExampleButton->connectActionPerformed(boost::bind(actionPerformed, _1));

        //Toggle Button
        ToggleButtonRefPtr ExampleToggleButton = OSG::ToggleButton::create();
        ExampleToggleButton->setSelected(false);
        ExampleToggleButton->setText("ToggleMe");


        //Text Field
        TextFieldRefPtr ExampleTextField = OSG::TextField::create();
        
        //Password Field
        PasswordFieldRefPtr ExamplePasswordField = OSG::PasswordField::create();

        LayoutRefPtr MainLayout = OSG::FlowLayout::create();

        //Panel
        PanelRecPtr ExamplePanel = Panel::create();
        ExamplePanel->setPreferredSize(Vec2f(200.0f,200.0f));
        ExamplePanel->setLayout(MainLayout);
        ExamplePanel->pushToChildren(ExampleTextField);
        ExamplePanel->pushToChildren(ExamplePasswordField);

        //Text Field 2
        TextFieldRefPtr ExampleTextField2 = OSG::TextField::create();

        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
        MainInternalWindow->pushToChildren(ExampleButton);
        MainInternalWindow->pushToChildren(ExampleToggleButton);
        MainInternalWindow->pushToChildren(ExamplePanel);
        MainInternalWindow->pushToChildren(ExampleTextField2);

        MainInternalWindow->setLayout(MainLayout);
        MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
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

        sceneManager.setRoot(scene);

        // Add the UI Foreground Object to the Scene
        ViewportRefPtr TutorialViewport = sceneManager.getWindow()->getPort(0);
        TutorialViewport->addForeground(TutorialUIForeground);

        // Show the whole Scene
        sceneManager.showAll();


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5f);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "54FocusProgession");

        commitChanges();

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
