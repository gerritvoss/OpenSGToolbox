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

// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

//Input
#include <OpenSG/Input/OSGWindowUtils.h>


//UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGLayers.h>

#include <OpenSG/UserInterface/OSGProgressBar.h>
#include <OpenSG/UserInterface/OSGDefaultBoundedRangeModel.h>
#include <OpenSG/UserInterface/OSGToggleButton.h>
#include <OpenSG/Input/OSGUpdateListener.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;

// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEvent& e)
   {
       if(e.getKey() == KeyEvent::KEY_Q && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
            TutorialWindowEventProducer->closeWindow();
       }
   }

   virtual void keyReleased(const KeyEvent& e)
   {
   }

   virtual void keyTyped(const KeyEvent& e)
   {
   }
};

    /******************************************************
            Declare variable upfront
    ******************************************************/    

ToggleButtonPtr ProgressControlToggleButton;

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
    ProgressUpdateListener(ProgressBarPtr ExampleProgressBar) :
        _ProgressBar(ExampleProgressBar),
        _Elps(0.0),
        _ProgPerSec(1.0)
    {
    }
    
    virtual void update(const UpdateEvent& e)
    {
		// Increment the time
        _Elps += e.getElapsedTime();

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
			beginEditCP(ProgressControlToggleButton, ToggleButton::TextColorFieldMask | ToggleButton::SelectedFieldMask | ToggleButton::EnabledFieldMask);
				ProgressControlToggleButton->setText("Reset Progress Bar");
				ProgressControlToggleButton->setSelected(false);
				ProgressControlToggleButton->setEnabled(false);
			endEditCP(ProgressControlToggleButton, ToggleButton::TextColorFieldMask | ToggleButton::SelectedFieldMask | ToggleButton::EnabledFieldMask);
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
    ProgressBarPtr _ProgressBar;
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
        WindowEventProducerPtr TutorialWindowEventProducer):
        _ProgressUpdateListener(TheProgressUpdateListener),
        _WindowEventProducer(TutorialWindowEventProducer)
    {
    }

	// Create functions to change Text and add/remove UpdateListeners
    virtual void buttonSelected(const ButtonSelectedEvent& e)
    {
        beginEditCP(ToggleButton::Ptr::dcast(e.getSource()), ToggleButton::TextFieldMask);
            ToggleButton::Ptr::dcast(e.getSource())->setText("Stop Incrementing");
        endEditCP(ToggleButton::Ptr::dcast(e.getSource()), ToggleButton::TextFieldMask);
        
		// Adds the UpdateListener so that the ProgressBar starts incrementing
        _WindowEventProducer->addUpdateListener(_ProgressUpdateListener);
    }

    virtual void buttonDeselected(const ButtonSelectedEvent& e)
    {
        beginEditCP(ToggleButton::Ptr::dcast(e.getSource()), ToggleButton::TextFieldMask);
            ToggleButton::Ptr::dcast(e.getSource())->setText("Start Incrementing");
		endEditCP(ToggleButton::Ptr::dcast(e.getSource()), ToggleButton::TextFieldMask);
        
		// Removes UpdateListener to stop ProgressBar from incrementing
		_WindowEventProducer->removeUpdateListener(_ProgressUpdateListener);
		// Resets time when ToggleButton deselected
		_ProgressUpdateListener->reset();
    }
protected:
    ProgressUpdateListener *_ProgressUpdateListener;
    WindowEventProducerPtr _WindowEventProducer;
};

    /******************************************************
            
			Create ActionListener to reset
			ProgressBar when a Button
			is pressed.

    ******************************************************/    

class ResetProgressBarActionListener : public ActionListener
{
	public: ResetProgressBarActionListener(ProgressBarPtr ExampleProgressBar, ToggleButtonPtr ProgressControlToggleButton) :
        _ProgressBar(ExampleProgressBar), _ProgressControlToggleButton(ProgressControlToggleButton)

		{		
		}
			
			virtual void actionPerformed(const ActionEvent& e)
			{	
				// Finds Minimum value for ProgressBar and sets it as the ProgressBar's value
				_ProgressBar->getRangeModel()->setValue( _ProgressBar->getRangeModel()->getMinimum());

				// Edits ProgressControlToggleButton accordingly
				beginEditCP(_ProgressControlToggleButton, ToggleButton::SelectedFieldMask | ToggleButton::TextFieldMask);
					_ProgressControlToggleButton->setSelected(false);
					_ProgressControlToggleButton->setText("Start Incrementing");
					_ProgressControlToggleButton->setEnabled(true);
				endEditCP(_ProgressControlToggleButton, ToggleButton::SelectedFieldMask | ToggleButton::TextFieldMask);
			}

protected:
	ProgressBarPtr _ProgressBar;
	ToggleButtonPtr _ProgressControlToggleButton;
};

// Initialize WIN32 & OpenSG and set up the scene
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

    DefaultBoundedRangeModelPtr ExampleProgressBarBoundedRangeModel = DefaultBoundedRangeModel::create();
    ExampleProgressBarBoundedRangeModel->setMinimum(0);
    ExampleProgressBarBoundedRangeModel->setMaximum(100);
    ExampleProgressBarBoundedRangeModel->setValue(0);
    ExampleProgressBarBoundedRangeModel->setExtent(0);

	// Create the ProgressBar
    ProgressBarPtr ExampleProgressBar = ProgressBar::create();
	

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
	beginEditCP(ExampleProgressBar, ProgressBar::EnableProgressStringFieldMask | ProgressBar::IndeterminateFieldMask | ProgressBar::OrientationFieldMask | ProgressBar::ProgressStringFieldMask | ProgressBar::RangeModelFieldMask);
        ExampleProgressBar->setEnableProgressString(true);
        ExampleProgressBar->setIndeterminate(false);
        ExampleProgressBar->setOrientation(ProgressBar::HORIZONTAL_ORIENTATION);
        // ExampleProgressBar->setIndeterminateBarMoveRate(0.0);
        // ExampleProgressBar->setIndeterminateBarSize(2.0);
		// ExampleProgressBar->setProgressString("Loading...");
	    // Add its BoundedRangeModel
        ExampleProgressBar->setRangeModel(ExampleProgressBarBoundedRangeModel);
    endEditCP(ExampleProgressBar, ProgressBar::EnableProgressStringFieldMask | ProgressBar::IndeterminateFieldMask | ProgressBar::OrientationFieldMask | ProgressBar::ProgressStringFieldMask | ProgressBar::RangeModelFieldMask);

	/******************************************************
         
		 Create Listeners and Buttons to 
		 control ProgressBar

    ******************************************************/    
    ProgressUpdateListener TheProgressUpdateListener(ExampleProgressBar);

	// Create a ToggleButton
	ProgressControlToggleButton = osg::ToggleButton::create();
    ProgressControlListener TheProgressControlListener(&TheProgressUpdateListener, TutorialWindowEventProducer);
	ProgressControlToggleButton->addButtonSelectedListener(&TheProgressControlListener);

	// Modify ToggleButton
	beginEditCP(ProgressControlToggleButton, ToggleButton::TextColorFieldMask | ToggleButton::PreferredSizeFieldMask);
		ProgressControlToggleButton->setText("Start Incrementing");
		ProgressControlToggleButton->setPreferredSize(Vec2f(150,50));
	endEditCP(ProgressControlToggleButton, ToggleButton::TextColorFieldMask | ToggleButton::PreferredSizeFieldMask);

	// Create a "reset" Button
	ButtonPtr ProgressBarResetButton = osg::Button::create();

	beginEditCP(ProgressBarResetButton, Button::TextFieldMask | Button::PreferredSizeFieldMask);
		ProgressBarResetButton->setText("Reset ProgressBar");
		ProgressBarResetButton->setPreferredSize(Vec2f(150,50));
	endEditCP(ProgressBarResetButton, Button::TextFieldMask | Button::PreferredSizeFieldMask);

	ResetProgressBarActionListener TheResetProgressBarActionListener(ExampleProgressBar, ProgressControlToggleButton);
	ProgressBarResetButton->addActionListener(&TheResetProgressBarActionListener);

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);

    LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().push_back(ExampleProgressBar);
       MainInternalWindow->getChildren().push_back(ProgressControlToggleButton);
       MainInternalWindow->getChildren().push_back(ProgressBarResetButton);
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
