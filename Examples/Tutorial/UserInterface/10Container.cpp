// OpenSG Tutorial Example: Using Containers (Frames and Panels)
//
// This tutorial explains how use Frame and Panel Containers
// 
// Includes: creating and editing Frames, Panels, and adding
// Panels

// Note: in almost all cases, each Scene should have only ONE
// Frame, but may have unlimited Panels.


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

// 10Container Headers
#include "OSGButton.h"
#include "OSGLineBorder.h"
#include "OSGColorLayer.h"
#include "OSGAbsoluteLayout.h"
#include "OSGAbsoluteLayoutConstraints.h"
#include "OSGBoxLayout.h"
#include "OSGFlowLayout.h"
#include "OSGComponentContainer.h"
#include "OSGPanel.h"
#include "OSGLineBorder.h"
#include "OSGBevelBorder.h"


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
            
                Creates some Button components
                and edit their Text.

    ******************************************************/

    ButtonRefPtr ExampleButton1 = OSG::Button::create();
    ButtonRefPtr ExampleButton2 = OSG::Button::create();
    ButtonRefPtr ExampleButton3 = OSG::Button::create();
    ButtonRefPtr ExampleButton4 = OSG::Button::create();
    ButtonRefPtr ExampleButton5 = OSG::Button::create();
    ButtonRefPtr ExampleButton6 = OSG::Button::create();
    
        ExampleButton1->setText("This");

        ExampleButton2->setText("is a");

        ExampleButton3->setText("sample");

        ExampleButton4->setText("two");

        ExampleButton5->setText("ExamplePanel");

        ExampleButton6->setText("layout");

    
    /******************************************************

            Create some Flow and BoxLayouts to be 
            used with the Main Frame and two 
            Panels.

    ******************************************************/
    FlowLayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();
    FlowLayoutRefPtr ExamplePanel1Layout = OSG::FlowLayout::create();
    FlowLayoutRefPtr ExamplePanel2Layout = OSG::FlowLayout::create();

        ExamplePanel1Layout->setOrientation(FlowLayout::VERTICAL_ORIENTATION);


    /******************************************************
            
            Create two Backgrounds to be used with
            Panels and MainInternalWindow.

    ******************************************************/
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
    ColorLayerRefPtr ExamplePanelBackground = OSG::ColorLayer::create();

        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        ExamplePanelBackground->setColor(Color4f(0.0,0.0,0.0,1.0));
    
    /******************************************************
            
            Create a Border to be used with
            the two Panels.

    ******************************************************/
    LineBorderRefPtr ExamplePanelBorder = OSG::LineBorder::create();
        ExamplePanelBorder->setColor(Color4f(0.9, 0.9, 0.9, 1.0));
        ExamplePanelBorder->setWidth(3);


    /******************************************************

        Create MainInternalWindow and two Panel Components and
        edit their characteristics.

        -setPreferredSize(Vec2f): Determine the 
			size of the Panel.
        -pushToChildren(ComponentName):
			Adds a Component to the
			ComponentContainer as a Child (meaning it 
			will be displayed within it).
        -setLayout(LayoutName): Determines the 
			Layout of the ComponentContainer.

    ******************************************************/
    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
    PanelRefPtr ExamplePanel1 = OSG::Panel::create();
    PanelRefPtr ExamplePanel2 = OSG::Panel::create();
    
    // Edit Panel1, Panel2
        ExamplePanel1->setPreferredSize(Vec2f(200, 200));
        ExamplePanel1->pushToChildren(ExampleButton1);
        ExamplePanel1->pushToChildren(ExampleButton2);
        ExamplePanel1->pushToChildren(ExampleButton3);
        ExamplePanel1->setLayout(ExamplePanel1Layout);
        ExamplePanel1->setBackgrounds(ExamplePanelBackground);
        ExamplePanel1->setBorders(ExamplePanelBorder);

        ExamplePanel2->setPreferredSize(Vec2f(200, 200));
        ExamplePanel2->pushToChildren(ExampleButton4);
        ExamplePanel2->pushToChildren(ExampleButton5);
        ExamplePanel2->pushToChildren(ExampleButton6);
        ExamplePanel2->setLayout(ExamplePanel2Layout);
        ExamplePanel2->setBackgrounds(ExamplePanelBackground);
        ExamplePanel2->setBorders(ExamplePanelBorder);

    // Create The Main InternalWindow
       MainInternalWindow->pushToChildren(ExamplePanel1);
       MainInternalWindow->pushToChildren(ExamplePanel2);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
	   MainInternalWindow->setAllInsets(5);
    
    // Create the Drawing Surface
    UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);
    
	TutorialDrawingSurface->openWindow(MainInternalWindow);

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
            "10Container");

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
