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

// the general scene file loading handler
#include "OSGSceneFileHandler.h"

//Input
#include "OSGWindowUtils.h"


//UserInterface Headers
#include "OSGUIForeground.h"
#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"
#include "OSGGraphics2D.h"
#include "OSGFlowLayout.h"
#include "OSGLookAndFeelManager.h"
#include "OSGLayers.h"

#include "OSGProgressBar.h"
#include "OSGDefaultBoundedRangeModel.h"
#include "OSGToggleButton.h"

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with , but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

void keyPressed(KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_Q &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
}

/******************************************************
  Declare variable upfront
 ******************************************************/    

/******************************************************

  Create class to cause ProgressBar to
  automatically increment.

Note: In "real" applications, this 
will not be needed as the ProgressBar
will be tied to a process.  However,
to better show its features, this
Tutorial has the option to start/stop
the ProgressBar dynamically.

 ******************************************************/    
class ProgressController
{
  private:

    void handleUpdate(UpdateEventDetails* const details)
    {
        // Increment the time
        _Elps += details->getElapsedTime();

        // Increment the ProgressBar if it is under its Maximum value
        if (_ProgressBar->getRangeModel()->getValue() <= _ProgressBar->getRangeModel()->getMaximum() )
        {
            _ProgressBar->getRangeModel()->setValue(_ProgPerSec * _Elps);
        }

        if(_ProgressBar->getRangeModel()->getValue() >= _ProgressBar->getRangeModel()->getMaximum())
        {	
            // Set the ProgressBar to the Maximum value when needed (in case the increment and 
            // value do not exactly equal the Maximum)
            _ProgressBar->getRangeModel()->setValue(_ProgressBar->getRangeModel()->getMaximum());

            // Change the Controlling ToggleButton accordingly
            _ProgressControlToggleButton->setText("Reset Progress Bar");
            _ProgressControlToggleButton->setSelected(false);
            _ProgressControlToggleButton->setEnabled(false);
            // Reset the time
            _Elps = 0;
        }

    }

    void handleStartButtonSelected(ButtonSelectedEventDetails* const details)
    {
        _ProgressControlToggleButton->setText("Stop Incrementing");

        _UpdateConnection =
            _TutorialWindow->connectUpdate(boost::bind(&ProgressController::handleUpdate,
                                                            this,
                                                            _1));
    }

    void handleStartButtonDeselected(ButtonSelectedEventDetails* const details)
    {
        _ProgressControlToggleButton->setText("Start Incrementing");

        _UpdateConnection.disconnect();
    }

    void handleResetActionPerformed(ActionEventDetails* const details)
    {	
        // Finds Minimum value for ProgressBar and sets it as the ProgressBar's value
        _ProgressBar->getRangeModel()->setValue( _ProgressBar->getRangeModel()->getMinimum());

        // Edits ProgressControlToggleButton accordingly
        _ProgressControlToggleButton->setSelected(false);
        _ProgressControlToggleButton->setText("Start Incrementing");
        _ProgressControlToggleButton->setEnabled(true);

        reset();
    }

    // Function to reset the time
    void reset(void)       
    {
        _Elps = 0.0f;
    }

    WindowEventProducerRecPtr _TutorialWindow;
    ProgressBarRecPtr _ProgressBar;
    ToggleButtonRecPtr _ProgressControlToggleButton;
    ButtonRecPtr _ProgressBarResetButton;
    Time _Elps;
    Real32 _ProgPerSec;
    boost::signals2::connection _UpdateConnection;

  public:
    ProgressController(WindowEventProducer* const TutorialWindow,
                       ProgressBar* const ExampleProgressBar,
                       ToggleButton* const ProgressControlToggleButton,
                       Button* const ProgressBarResetButton) :
        _TutorialWindow(TutorialWindow),
        _ProgressBar(ExampleProgressBar),
        _ProgressControlToggleButton(ProgressControlToggleButton),
        _ProgressBarResetButton(ProgressBarResetButton),
        _Elps(0.0),
        _ProgPerSec(10.0f)
    {
        _ProgressControlToggleButton->connectButtonSelected(boost::bind(&ProgressController::handleStartButtonSelected,
                                                                        this,
                                                                        _1));
        _ProgressControlToggleButton->connectButtonDeselected(boost::bind(&ProgressController::handleStartButtonDeselected,
                                                                          this,
                                                                          _1));

        _ProgressBarResetButton->connectActionPerformed(boost::bind(&ProgressController::handleResetActionPerformed,
                                                                     this,
                                                                     _1));
    }

};

// Initialize WIN32 & OpenSG and set up the scene
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

          Create a BoundedRangeModel for the 
          ProgressBar.  This is done in the
          same manner as with ScrollBars.

          -.setMinimum(int): Determine a numeric
          value for the beginning of the 
          ProgressBar.  Note that the visible
          size will be set separately.
          -.setMaximum(int): Determine a numeric
          value for the end of the 
          ProgressBar. 
          -.setValue(int):  Determine the 
          initial location of the Bar on the
          ProgressBar.  This is determined from
          the Min/Max values.
          -.setExtent(int): Determine the size
          of the Bar on the ProgressBar as a 
          fraction of the total size (which is 
          determined from the Min/Max values)
          as well.

         ******************************************************/    

        DefaultBoundedRangeModelRecPtr ExampleProgressBarBoundedRangeModel = DefaultBoundedRangeModel::create();
        ExampleProgressBarBoundedRangeModel->setMinimum(0);
        ExampleProgressBarBoundedRangeModel->setMaximum(100);
        ExampleProgressBarBoundedRangeModel->setValue(0);
        ExampleProgressBarBoundedRangeModel->setExtent(0);

        // Create the ProgressBar
        ProgressBarRecPtr ExampleProgressBar = ProgressBar::create();

        /******************************************************

          Edit the ProgressBar.
          -setEnableProgressString(bool): Determine
          whether the ProgressBar displays text.
          True displays text, false does not.
          The default text to be displayed is
          the percentage that the ProgressBar
          Model is at, otherwise the text shown
          in the setProgressString() function
          will be displayed.
          -setIndeterminate(bool): Determine if
          the "bar" will be displayed.  True
          displays the bar, false does not.
          -setOrientation(ENUM): Determine the 
          orientation of the ProgressBar.
          Takes HORIZONTAL_ORIENTATION and
          VERTICAL_ORIENTATION arguments.
          This orientation is the direction
          that the "bar" moves.
          -setIndeterminateBarMoveRate(Real32):
          Determine the rate at which the 
          bar increments.  Note: for this
          Tutorial, the ProgressBar is
          incremented via the Update
          above, and this is not used (more
          useful when tied to some other
          process).
          -setIndeterminateBarSize(Real32): 
          Determine the Size of the bar.
          As with the BarMoveRate, this is
          not used in this Tutorial.
          -setProgressString(string): Determine
          what text the bar has on it.  If 
          this is not specified, the
          ProgressBar will show the percent
          complete in numerical format.

         ******************************************************/    
        ExampleProgressBar->setEnableProgressString(true);
        ExampleProgressBar->setIndeterminate(false);
        ExampleProgressBar->setOrientation(ProgressBar::HORIZONTAL_ORIENTATION);
        // ExampleProgressBar->setIndeterminateBarMoveRate(0.0);
        // ExampleProgressBar->setIndeterminateBarSize(2.0);
        // ExampleProgressBar->setProgressString("Loading...");
        // Add its BoundedRangeModel
        ExampleProgressBar->setRangeModel(ExampleProgressBarBoundedRangeModel);

        /******************************************************

          Create Buttons to 
          control ProgressBar

         ******************************************************/    

        // Create a ToggleButton
        ToggleButtonRecPtr ProgressControlToggleButton = ToggleButton::create();

        // Modify ToggleButton
        ProgressControlToggleButton->setText("Start Incrementing");
        ProgressControlToggleButton->setPreferredSize(Vec2f(150,50));

        // Create a "reset" Button
        ButtonRecPtr ProgressBarResetButton = Button::create();

        ProgressBarResetButton->setText("Reset ProgressBar");
        ProgressBarResetButton->setPreferredSize(Vec2f(150,50));

        ProgressController TheProgressController(TutorialWindow,
                                                 ExampleProgressBar,
                                                 ProgressControlToggleButton,
                                                 ProgressBarResetButton);

        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        LayoutRecPtr MainInternalWindowLayout = FlowLayout::create();

        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
        MainInternalWindow->pushToChildren(ExampleProgressBar);
        MainInternalWindow->pushToChildren(ProgressControlToggleButton);
        MainInternalWindow->pushToChildren(ProgressBarResetButton);
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
                                   "31ProgressBar");

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

