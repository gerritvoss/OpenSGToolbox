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
#include "OSGUpdateListener.h"

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

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

/******************************************************
  Declare variable upfront
 ******************************************************/    

ToggleButtonRefPtr ProgressControlToggleButton;

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
class ProgressUpdateListener : public UpdateListener
{
  public:
    ProgressUpdateListener(ProgressBarRefPtr ExampleProgressBar) :
        _ProgressBar(ExampleProgressBar),
        _Elps(0.0),
        _ProgPerSec(1.0)
    {
    }

    virtual void update(const UpdateEventUnrecPtr e)
    {
        // Increment the time
        _Elps += e->getElapsedTime();

        // Increment the ProgressBar if it is under its Maximum value
        if (_ProgressBar->getRangeModel()->getValue() <= (_ProgressBar->getRangeModel()->getMaximum() - _ProgPerSec) )
        {
            _ProgressBar->getRangeModel()->setValue(_ProgressBar->getRangeModel()->getValue() + _ProgPerSec * _Elps);
        }

        if(_ProgressBar->getRangeModel()->getValue() >= (_ProgressBar->getRangeModel()->getMaximum() - _ProgPerSec))
        {	
            // Set the ProgressBar to the Maximum value when needed (in case the increment and 
            // value do not exactly equal the Maximum)
            _ProgressBar->getRangeModel()->setValue(_ProgressBar->getRangeModel()->getMaximum());

            // Change the Controlling ToggleButton accordingly
            ProgressControlToggleButton->setText("Reset Progress Bar");
            ProgressControlToggleButton->setSelected(false);
            ProgressControlToggleButton->setEnabled(false);
            // Reset the time
            _Elps = 0;
        }

    }

    // Function to reset the time

    void reset(void)       
    {
        _Elps = 0.0f;
    }
  protected:
    ProgressBarRefPtr _ProgressBar;
    Time _Elps;
    Real32 _ProgPerSec;
};

/******************************************************

  Create a class to turn the ProgressBar
  on/off.

 ******************************************************/    

class ProgressControlListener : public ButtonSelectedListener
{
  public:
    ProgressControlListener(ProgressUpdateListener *TheProgressUpdateListener,
                            WindowEventProducerRefPtr TutorialWindow):
        _ProgressUpdateListener(TheProgressUpdateListener),
        _WindowEventProducer(TutorialWindow)
    {
    }

    // Create functions to change Text and add/remove UpdateListeners
    virtual void buttonSelected(const ButtonSelectedEventUnrecPtr e)
    {
        dynamic_cast<ToggleButton*>(e->getSource())->setText("Stop Incrementing");

        // Adds the UpdateListener so that the ProgressBar starts incrementing
        _WindowEventProducer->addUpdateListener(_ProgressUpdateListener);
    }

    virtual void buttonDeselected(const ButtonSelectedEventUnrecPtr e)
    {
        dynamic_cast<ToggleButton*>(e->getSource())->setText("Start Incrementing");

        // Removes UpdateListener to stop ProgressBar from incrementing
        _WindowEventProducer->removeUpdateListener(_ProgressUpdateListener);
        // Resets time when ToggleButton deselected
        _ProgressUpdateListener->reset();
    }
  protected:
    ProgressUpdateListener *_ProgressUpdateListener;
    WindowEventProducerRefPtr _WindowEventProducer;
};

/******************************************************

  Create ActionListener to reset
  ProgressBar when a Button
  is pressed.

 ******************************************************/    

class ResetProgressBarActionListener : public ActionListener
{
  public: ResetProgressBarActionListener(ProgressBarRefPtr ExampleProgressBar, ToggleButtonRefPtr ProgressControlToggleButton) :
          _ProgressBar(ExampleProgressBar), _ProgressControlToggleButton(ProgressControlToggleButton)

    {		
    }

          virtual void actionPerformed(const ActionEventUnrecPtr e)
          {	
              // Finds Minimum value for ProgressBar and sets it as the ProgressBar's value
              _ProgressBar->getRangeModel()->setValue( _ProgressBar->getRangeModel()->getMinimum());

              // Edits ProgressControlToggleButton accordingly
              _ProgressControlToggleButton->setSelected(false);
              _ProgressControlToggleButton->setText("Start Incrementing");
              _ProgressControlToggleButton->setEnabled(true);
          }

  protected:
          ProgressBarRefPtr _ProgressBar;
          ToggleButtonRefPtr _ProgressControlToggleButton;
};

// Initialize WIN32 & OpenSG and set up the scene
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

    DefaultBoundedRangeModelRefPtr ExampleProgressBarBoundedRangeModel = DefaultBoundedRangeModel::create();
    ExampleProgressBarBoundedRangeModel->setMinimum(0);
    ExampleProgressBarBoundedRangeModel->setMaximum(100);
    ExampleProgressBarBoundedRangeModel->setValue(0);
    ExampleProgressBarBoundedRangeModel->setExtent(0);

    // Create the ProgressBar
    ProgressBarRefPtr ExampleProgressBar = ProgressBar::create();


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
      incremented via the UpdateListener
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

      Create Listeners and Buttons to 
      control ProgressBar

     ******************************************************/    
    ProgressUpdateListener TheProgressUpdateListener(ExampleProgressBar);

    // Create a ToggleButton
    ProgressControlToggleButton = OSG::ToggleButton::create();
    ProgressControlListener TheProgressControlListener(&TheProgressUpdateListener, TutorialWindow);
    ProgressControlToggleButton->addButtonSelectedListener(&TheProgressControlListener);

    // Modify ToggleButton
    ProgressControlToggleButton->setText("Start Incrementing");
    ProgressControlToggleButton->setPreferredSize(Vec2f(150,50));

    // Create a "reset" Button
    ButtonRefPtr ProgressBarResetButton = OSG::Button::create();

    ProgressBarResetButton->setText("Reset ProgressBar");
    ProgressBarResetButton->setPreferredSize(Vec2f(150,50));

    ResetProgressBarActionListener TheResetProgressBarActionListener(ExampleProgressBar, ProgressControlToggleButton);
    ProgressBarResetButton->addActionListener(&TheResetProgressBarActionListener);

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
    MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    LayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
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
                               "31ProgressBar");

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
