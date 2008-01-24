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
void reshape(Vec2s Size);


// 29Spinner Headers
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGUIBackgrounds.h>
#include <OpenSG/UserInterface/OSGRadioButton.h>
#include <OpenSG/UserInterface/OSGRadioButtonGroup.h>
#include <OpenSG/UserInterface/OSGSpinner.h>
#include <OpenSG/UserInterface/OSGNumberSpinnerModel.h>


Int32SpinnerModelPtr TheModel(new Int32SpinnerModel());


class SingleIncrementButtonListener : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
        {         
            TheModel->setStepSize(1);

        }

   virtual void buttonDeselected(const ButtonSelectedEvent& e)
   {
            TheModel->setStepSize(2);
   }
};
class DoubleIncrementButtonListener : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
        {         
            TheModel->setStepSize(2);
        }

   virtual void buttonDeselected(const ButtonSelectedEvent& e)
   {
            TheModel->setStepSize(1);
   }
};


// Create a class to allow for the use of the Ctrl+q
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


int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    //Temp->setValue(0);

    // Set up Window
    WindowEventProducerPtr TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();
    
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
    TheModel->setValue(SharedFieldPtr(new SFInt32(0)));

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
        SingleIncrementButton->setPreferredSize(Vec2s(100, 50));
    beginEditCP(SingleIncrementButton, RadioButton::TextColorFieldMask | RadioButton::PreferredSizeFieldMask);
    SingleIncrementButtonListener TheSingleIncrementButtonListener;
    SingleIncrementButton->addButtonSelectedListener(&TheSingleIncrementButtonListener);

	beginEditCP(DoubleIncrementButton, RadioButton::TextColorFieldMask | RadioButton::PreferredSizeFieldMask | RadioButton::SelectedFieldMask);
        DoubleIncrementButton->setText("Increment by 2");
        DoubleIncrementButton->setPreferredSize(Vec2s(100, 50));
        DoubleIncrementButton->setSelected(TRUE);
    beginEditCP(DoubleIncrementButton, RadioButton::TextColorFieldMask | RadioButton::PreferredSizeFieldMask | RadioButton::SelectedFieldMask);
    DoubleIncrementButtonListener TheDoubleIncrementButtonListener;
    DoubleIncrementButton->addButtonSelectedListener(&TheDoubleIncrementButtonListener);

    RadioButtonGroup SelectionRadioButtonGroup;
    SelectionRadioButtonGroup.addButton(SingleIncrementButton);
    SelectionRadioButtonGroup.addButton(DoubleIncrementButton);

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorUIBackgroundPtr MainInternalWindowBackground = osg::ColorUIBackground::create();
    beginEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);

    LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().addValue(SingleIncrementButton);
       MainInternalWindow->getChildren().addValue(DoubleIncrementButton);
       MainInternalWindow->getChildren().addValue(ExampleSpinner);
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
        TutorialViewport->getForegrounds().addValue(TutorialUIForeground);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);

    // Show the whole Scene
    mgr->showAll();

    TutorialWindowEventProducer->openWindow(Pnt2s(50,50),
                                        Vec2s(550,550),
                                        "OpenSG 29Spinner Window");

    while(!ExitApp)
    {
        TutorialWindowEventProducer->update();
        TutorialWindowEventProducer->draw();
    }
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
void reshape(Vec2s Size)
{
    mgr->resize(Size.x(), Size.y());
}