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
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>

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
WindowEventProducerPtr TutorialWindowEventProducer;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);


// 29Spinner Headers
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGLayers.h>
#include <OpenSG/UserInterface/OSGRadioButton.h>
#include <OpenSG/UserInterface/OSGRadioButtonGroup.h>
#include <OpenSG/UserInterface/OSGSpinner.h>
#include <OpenSG/UserInterface/OSGNumberSpinnerModel.h>


Int32SpinnerModelPtr TheModel(new Int32SpinnerModel());


class SingleIncrementButtonListener : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEventPtr e)
        {         
            TheModel->setStepSize(1);

        }

   virtual void buttonDeselected(const ButtonSelectedEventPtr e)
   {
            TheModel->setStepSize(2);
   }
};
class DoubleIncrementButtonListener : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEventPtr e)
        {         
            TheModel->setStepSize(2);
        }

   virtual void buttonDeselected(const ButtonSelectedEventPtr e)
   {
            TheModel->setStepSize(1);
   }
};


// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
            TutorialWindowEventProducer->closeWindow();
       }
   }

   virtual void keyReleased(const KeyEventPtr e)
   {
   }

   virtual void keyTyped(const KeyEventPtr e)
   {
   }
};


int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    //Temp->setValue(0);

    // Set up Window
    TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

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
            
            Create a Spinner Model.  This dictates 
            how the Spinner functions.
            -setMaximum(int): Determine the Maximum 
                value the Spinner can have.
            -setMinimum(int): Determine the Minimum 
                value the Spinner can have.
            -setStepSize(int): Determine the 
                incremental step size.
            -setValue(SharedFieldPtr(new SFInt32(int)):
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

    SpinnerPtr ExampleSpinner = Spinner::create();
    ExampleSpinner->setModel(TheModel);
    
    /******************************************************
            
            Create a RadioButtonPanel to allow
            for certain characteristics of the
            Spinner to be changed dynamically.
            See 14RadioButton for more 
            information about RadioButtons.
 
    ******************************************************/    

    RadioButtonPtr SingleIncrementButton = RadioButton::create();
    RadioButtonPtr DoubleIncrementButton = RadioButton::create();
    beginEditCP(SingleIncrementButton, RadioButton::TextColorFieldMask | RadioButton::PreferredSizeFieldMask);
        SingleIncrementButton->setText("Increment by 1");
        SingleIncrementButton->setPreferredSize(Vec2f(100, 50));
    beginEditCP(SingleIncrementButton, RadioButton::TextColorFieldMask | RadioButton::PreferredSizeFieldMask);
    SingleIncrementButtonListener TheSingleIncrementButtonListener;
    SingleIncrementButton->addButtonSelectedListener(&TheSingleIncrementButtonListener);

	beginEditCP(DoubleIncrementButton, RadioButton::TextColorFieldMask | RadioButton::PreferredSizeFieldMask | RadioButton::SelectedFieldMask);
        DoubleIncrementButton->setText("Increment by 2");
        DoubleIncrementButton->setPreferredSize(Vec2f(100, 50));
        DoubleIncrementButton->setSelected(true);
    beginEditCP(DoubleIncrementButton, RadioButton::TextColorFieldMask | RadioButton::PreferredSizeFieldMask | RadioButton::SelectedFieldMask);
    DoubleIncrementButtonListener TheDoubleIncrementButtonListener;
    DoubleIncrementButton->addButtonSelectedListener(&TheDoubleIncrementButtonListener);

    RadioButtonGroupPtr SelectionRadioButtonGroup = RadioButtonGroup::create();
    SelectionRadioButtonGroup->addButton(SingleIncrementButton);
    SelectionRadioButtonGroup->addButton(DoubleIncrementButton);

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);

    LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().push_back(SingleIncrementButton);
       MainInternalWindow->getChildren().push_back(DoubleIncrementButton);
       MainInternalWindow->getChildren().push_back(ExampleSpinner);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
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


    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "01RubberBandCamera");

    //Enter main Loop
    TutorialWindowEventProducer->mainLoop();

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
