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
#include <OpenSG/UserInterface/OSGInternalWindow.h>
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
void reshape(Vec2f Size);

// 30RotatedComponent Headers
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGUIFont.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGToggleButton.h>
#include <OpenSG/UserInterface/OSGRotatedComponent.h>
#include <OpenSG/Input/OSGUpdateListener.h>

ComponentPtr createPanel(void);

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


    /******************************************************
            
            Create Listeners to let RotatedComponent
			rotate
 
    ******************************************************/    
class RotateUpdateListener : public UpdateListener
{
public:
    RotateUpdateListener(RotatedComponentPtr TheRotatedComponent) :
        _RotatedComponent(TheRotatedComponent),
        _Elps(0.0),
        _RadPerSec(3.14159)
    {
    }
    
    virtual void update(const UpdateEvent& e)
    {
		// Increment the time
        _Elps += e.getElapsedTime();
        
		// Change the RotatedComponent Angle
        beginEditCP(_RotatedComponent, RotatedComponent::AngleFieldMask);
            _RotatedComponent->setAngle(_Elps * _RadPerSec);
        endEditCP(_RotatedComponent, RotatedComponent::AngleFieldMask);
    }
    
    void reset(void)       
    {
        _Elps = 0.0f;
    }
protected:
    RotatedComponentPtr _RotatedComponent;
    Time _Elps;
    Real32 _RadPerSec;
};

// Create Listener to turn rotating on/off
class RotateControlListener : public ButtonSelectedListener
{
public:
    RotateControlListener(RotateUpdateListener *TheRotateUpdateListener,
        WindowEventProducerPtr TutorialWindowEventProducer):
        _RotateUpdateListener(TheRotateUpdateListener),
        _WindowEventProducer(TutorialWindowEventProducer)
    {
    }
    // Create functions to change text based on whether
	// Component is rotating or not
    virtual void buttonSelected(const ButtonSelectedEvent& e)
    {
		// When Selected, get the selected Component (in this case
		// a ToggleButton) and then change its text accordingly.
        beginEditCP(ToggleButton::Ptr::dcast(e.getSource()), ToggleButton::TextFieldMask);
            ToggleButton::Ptr::dcast(e.getSource())->setText("Stop Rotating");
        endEditCP(ToggleButton::Ptr::dcast(e.getSource()), ToggleButton::TextFieldMask);
        
        _WindowEventProducer->addUpdateListener(_RotateUpdateListener);
    }

    // Change text when deselected
    virtual void buttonDeselected(const ButtonSelectedEvent& e)
    {
        beginEditCP(ToggleButton::Ptr::dcast(e.getSource()), ToggleButton::TextFieldMask);
            ToggleButton::Ptr::dcast(e.getSource())->setText("Start Rotating");
        endEditCP(ToggleButton::Ptr::dcast(e.getSource()), ToggleButton::TextFieldMask);
        _WindowEventProducer->removeUpdateListener(_RotateUpdateListener);
    }
protected:
    RotateUpdateListener *_RotateUpdateListener;
    WindowEventProducerPtr _WindowEventProducer;
};

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    WindowEventProducerPtr TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

	beginEditCP(TutorialWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);
		TutorialWindowEventProducer->setUseCallbackForDraw(true);
		TutorialWindowEventProducer->setUseCallbackForReshape(true);
	endEditCP(TutorialWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);
    
    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TutorialWindowEventProducer->addWindowListener(&TheTutorialWindowListener);
    TutorialKeyListener TheKeyListener;
    TutorialWindowEventProducer->addKeyListener(&TheKeyListener);

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
    
    RotatedComponentPtr TheRotatedComponent = RotatedComponent::create();
	// Define PI
    Real32 PI(3.14159);
    beginEditCP(TheRotatedComponent, RotatedComponent::AngleFieldMask | RotatedComponent::InternalComponentFieldMask | RotatedComponent::ResizePolicyFieldMask);
            TheRotatedComponent->setAngle(PI/4);
            TheRotatedComponent->setInternalComponent(createPanel());
            TheRotatedComponent->setResizePolicy(RotatedComponent::RESIZE_TO_MIN);
    endEditCP(TheRotatedComponent, RotatedComponent::AngleFieldMask | RotatedComponent::InternalComponentFieldMask | RotatedComponent::ResizePolicyFieldMask);
    
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
    ToggleButtonPtr RotateControlButton = osg::ToggleButton::create();
    beginEditCP(RotateControlButton, Button::TextFieldMask);
        RotateControlButton->setText("Start Rotating");
    endEditCP(RotateControlButton, Button::TextFieldMask);

    // Pass the to-be-rotated Component to the Listener
    RotateUpdateListener TheRotateUpdateListener(TheRotatedComponent);
    
	// Create a Listener to check whether the Panel should be rotating
    RotateControlListener TheRotateControlListener(&TheRotateUpdateListener, TutorialWindowEventProducer);
    RotateControlButton->addButtonSelectedListener(&TheRotateControlListener);
    
    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorUIBackgroundPtr MainInternalWindowBackground = osg::ColorUIBackground::create();
    beginEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);

    LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().push_back(TheRotatedComponent);
       MainInternalWindow->getChildren().push_back(RotateControlButton);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.8f,0.8f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
    endEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);

    // Create the Drawing Surface
    UIDrawingSurfacePtr TutorialDrawingSurface = UIDrawingSurface::create();
    beginEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindowEventProducer);
    endEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
	
	TutorialDrawingSurface->openWindow(MainInternalWindow);

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
        TutorialViewport->getForegrounds().push_back(TutorialUIForeground);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);

    // Show the whole Scene
    mgr->showAll();
    TutorialWindowEventProducer->openWindow(Pnt2f(50,50),
                                        Vec2f(550,550),
                                        "OpenSG 30RotatedComponent Window");

    while(!ExitApp)
    {
        TutorialWindowEventProducer->update();
        TutorialWindowEventProducer->draw();
    }
    osgExit();

    return 0;
}



ComponentPtr createPanel(void)
{
    // Function to create a panel to be rotated
    ButtonPtr button1 = osg::Button::create();
    ButtonPtr button2 = osg::Button::create();
    ButtonPtr button3 = osg::Button::create();
    ButtonPtr button4 = osg::Button::create();
    FlowLayoutPtr panel1Layout = osg::FlowLayout::create();
    PanelPtr panel1 = osg::Panel::create();
    beginEditCP(panel1, Container::ChildrenFieldMask | Container::LayoutFieldMask | Component::PreferredSizeFieldMask);
        panel1->getChildren().push_back(button1);    
        panel1->getChildren().push_back(button2);
        panel1->getChildren().push_back(button3);
        panel1->getChildren().push_back(button4);
        panel1->setLayout(panel1Layout);
        panel1->setPreferredSize(Vec2f(100, 220));
    endEditCP(panel1, Container::ChildrenFieldMask | Container::LayoutFieldMask | Component::PreferredSizeFieldMask);
    beginEditCP(button1, Button::TextFieldMask);
            button1->setText("This");
    endEditCP(button1, Button::TextFieldMask);
    beginEditCP(button2, Button::TextFieldMask);
            button2->setText("Can");
    endEditCP(button2, Button::TextFieldMask);
    beginEditCP(button3, Button::TextFieldMask);
            button3->setText("Be");
    endEditCP(button3, Button::TextFieldMask);
    beginEditCP(button4, Button::TextFieldMask);
            button4->setText("Rotated!");
    endEditCP(button4, Button::TextFieldMask);
    
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