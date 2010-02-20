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

// 30RotatedComponent Headers
#include "OSGFlowLayout.h"
#include "OSGUIFont.h"
#include "OSGColorLayer.h"
#include "OSGPanel.h"
#include "OSGButton.h"
#include "OSGToggleButton.h"
#include "OSGRotatedComponent.h"
#include "OSGUpdateListener.h"

ComponentRefPtr createPanel(void);

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


    /******************************************************
            
            Create Listeners to let RotatedComponent
			rotate
 
    ******************************************************/    
class RotateUpdateListener : public UpdateListener
{
public:
    RotateUpdateListener(RotatedComponentRefPtr TheRotatedComponent) :
        _RotatedComponent(TheRotatedComponent),
        _Elps(0.0),
        _RadPerSec(3.14159)
    {
    }
    
    virtual void update(const UpdateEventUnrecPtr e)
    {
		// Increment the time
        _Elps += e->getElapsedTime();
        
		// Change the RotatedComponent Angle
            _RotatedComponent->setAngle(_Elps * _RadPerSec);
    }
    
    void reset(void)       
    {
        _Elps = 0.0f;
    }
protected:
    RotatedComponentRefPtr _RotatedComponent;
    Time _Elps;
    Real32 _RadPerSec;
};

// Create Listener to turn rotating on/off
class RotateControlListener : public ButtonSelectedListener
{
public:
    RotateControlListener(RotateUpdateListener *TheRotateUpdateListener,
        WindowEventProducerRefPtr TutorialWindow):
        _RotateUpdateListener(TheRotateUpdateListener),
        _WindowEventProducer(TutorialWindow)
    {
    }
    // Create functions to change text based on whether
	// Component is rotating or not
    virtual void buttonSelected(const ButtonSelectedEventUnrecPtr e)
    {
		// When Selected, get the selected Component (in this case
		// a ToggleButton) and then change its text accordingly.
            dynamic_cast<ToggleButton*>(e->getSource())->setText("Stop Rotating");
        
        _WindowEventProducer->addUpdateListener(_RotateUpdateListener);
    }

    // Change text when deselected
    virtual void buttonDeselected(const ButtonSelectedEventUnrecPtr e)
    {
            dynamic_cast<ToggleButton*>(e->getSource())->setText("Start Rotating");
        _WindowEventProducer->removeUpdateListener(_RotateUpdateListener);
    }
protected:
    RotateUpdateListener *_RotateUpdateListener;
    WindowEventProducerRefPtr _WindowEventProducer;
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
            
            Create a RotatedComponent.
            -setAngle(Angle, in radians): Determine
                the angle the Component initially
                is rotated.
            -setInternalComponent(Component): 
                Determine what Component will
				be rotated.
            -setResizePolicy(RotatedComponent::ENUM):
                Takes NO_RESIZING, RESIZE_TO_MIN, or
                RESIZE_TO_MAX arguments.
 
    ******************************************************/    
    
    RotatedComponentRefPtr TheRotatedComponent = RotatedComponent::create();
	// Define PI
    Real32 PI(3.14159);
            TheRotatedComponent->setAngle(PI/4);
            TheRotatedComponent->setInternalComponent(createPanel());
            TheRotatedComponent->setResizePolicy(RotatedComponent::RESIZE_TO_MIN);
    
    /******************************************************
            
            Create a ToggleButton which can 
            be used to start and stop the 
            Button from rotating.

            Note: due to the way FlowLayout works
            you will notice that this ToggleButton
            will move as well.  In cases where
            a Rotating Component is used, an 
            alternate Layout may be preferred
            to prevent other Components from 
            moving as well.  This is 
            intentionally left this way to 
            illustrate why this might be the case.
			A SplitPanel with fixed divider for 
			example would prevent the ToggleButton
			from moving, while still allowing the 
			Panel to move freely.
 
    ******************************************************/    
    ToggleButtonRefPtr RotateControlButton = OSG::ToggleButton::create();
        RotateControlButton->setText("Start Rotating");

    // Pass the to-be-rotated Component to the Listener
    RotateUpdateListener TheRotateUpdateListener(TheRotatedComponent);
    
	// Create a Listener to check whether the Panel should be rotating
    RotateControlListener TheRotateControlListener(&TheRotateUpdateListener, TutorialWindow);
    RotateControlButton->addButtonSelectedListener(&TheRotateControlListener);
    
    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    LayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
       MainInternalWindow->pushToChildren(TheRotatedComponent);
       MainInternalWindow->pushToChildren(RotateControlButton);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.8f,0.8f));
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
            "01RubberBandCamera");

    //Enter main Loop
    TutorialWindow->mainLoop();

    osgExit();

    return 0;
}



ComponentRefPtr createPanel(void)
{
    // Function to create a panel to be rotated
    ButtonRefPtr button1 = OSG::Button::create();
    ButtonRefPtr button2 = OSG::Button::create();
    ButtonRefPtr button3 = OSG::Button::create();
    ButtonRefPtr button4 = OSG::Button::create();
    FlowLayoutRefPtr panel1Layout = OSG::FlowLayout::create();
    PanelRefPtr panel1 = OSG::Panel::create();
        panel1->pushToChildren(button1);    
        panel1->pushToChildren(button2);
        panel1->pushToChildren(button3);
        panel1->pushToChildren(button4);
        panel1->setLayout(panel1Layout);
        panel1->setPreferredSize(Vec2f(100, 220));
            button1->setText("This");
            button2->setText("Can");
            button3->setText("Be");
            button4->setText("Rotated!");
    
    return panel1;
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
