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


// 29Spinner Headers
#include "OSGFlowLayout.h"
#include "OSGLayers.h"
#include "OSGRadioButton.h"
#include "OSGRadioButtonGroup.h"
#include "OSGSpinner.h"
#include "OSGNumberSpinnerModel.h"


Int32SpinnerModelPtr TheModel(new Int32SpinnerModel());


class SingleIncrementButtonListener : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEventUnrecPtr e)
        {         
            TheModel->setStepSize(1);

        }

   virtual void buttonDeselected(const ButtonSelectedEventUnrecPtr e)
   {
            TheModel->setStepSize(2);
   }
};
class DoubleIncrementButtonListener : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEventUnrecPtr e)
        {         
            TheModel->setStepSize(2);
        }

   virtual void buttonDeselected(const ButtonSelectedEventUnrecPtr e)
   {
            TheModel->setStepSize(1);
   }
};


// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventUnrecPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
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

    //Temp->setValue(0);

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
            
            Create a Spinner Model.  This dictates 
            how the Spinner functions.
            -setMaximum(int): Determine the Maximum 
                value the Spinner can have.
            -setMinimum(int): Determine the Minimum 
                value the Spinner can have.
            -setStepSize(int): Determine the 
                incremental step size.
            -setValue(SharedFieldRefPtr(new SFInt32(int)):
                Determine initial starting value
                of the Spinner.

            Note: the StepSize can be changed 
            dynamically as done in this 
            Tutorial with ButtonSelectedListeners.
 
    ******************************************************/    

    //Int32SpinnerModelPtr TheModel(new Int32SpinnerModel());
    TheModel->setMaximum(100);
    TheModel->setMinimum(-100);
    TheModel->setStepSize(2);
    TheModel->setValue(boost::any(Int32(0)));

    /******************************************************
            
            Create a Spinner and and assign it a 
			Model.
 
    ******************************************************/    

    SpinnerRefPtr ExampleSpinner = Spinner::create();
    ExampleSpinner->setModel(TheModel);
    
    /******************************************************
            
            Create a RadioButtonPanel to allow
            for certain characteristics of the
            Spinner to be changed dynamically.
            See 14RadioButton for more 
            information about RadioButtons.
 
    ******************************************************/    

    RadioButtonRefPtr SingleIncrementButton = RadioButton::create();
    RadioButtonRefPtr DoubleIncrementButton = RadioButton::create();
        SingleIncrementButton->setText("Increment by 1");
        SingleIncrementButton->setPreferredSize(Vec2f(100, 50));
    SingleIncrementButtonListener TheSingleIncrementButtonListener;
    SingleIncrementButton->addButtonSelectedListener(&TheSingleIncrementButtonListener);

        DoubleIncrementButton->setText("Increment by 2");
        DoubleIncrementButton->setPreferredSize(Vec2f(100, 50));
        DoubleIncrementButton->setSelected(true);
    DoubleIncrementButtonListener TheDoubleIncrementButtonListener;
    DoubleIncrementButton->addButtonSelectedListener(&TheDoubleIncrementButtonListener);

    RadioButtonGroupRefPtr SelectionRadioButtonGroup = RadioButtonGroup::create();
    SelectionRadioButtonGroup->addButton(SingleIncrementButton);
    SelectionRadioButtonGroup->addButton(DoubleIncrementButton);

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    LayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
       MainInternalWindow->pushToChildren(SingleIncrementButton);
       MainInternalWindow->pushToChildren(DoubleIncrementButton);
       MainInternalWindow->pushToChildren(ExampleSpinner);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
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
            "29Spinner");

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
