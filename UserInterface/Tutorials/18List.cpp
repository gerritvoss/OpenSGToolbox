// OpenSG Tutorial Example: Creating a List
//
// This tutorial explains how to create a List 
// via the  OSG User Interface library.
// 
// Includes: placing multiple buttons using Flow Layout


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

// 18List Headers
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
#include <OpenSG/UserInterface/OSGBevelBorder.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGToggleButton.h>
#include <OpenSG/UserInterface/OSGScrollPanel.h>

// List header files
#include <OpenSG/UserInterface/OSGList.h>
#include <OpenSG/UserInterface/OSGAbstractListModel.h>
#include <OpenSG/UserInterface/OSGDefaultListCellGenerator.h>
#include <OpenSG/UserInterface/OSGDefaultListSelectionModel.h>



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



// Declare the SelectionModel up front to allow for
// the ActionListeners
ListSelectionModelPtr SelectionModel(new DefaultListSelectionModel());
ToggleButtonPtr singleButton;
ToggleButtonPtr singleIntervalButton;
ToggleButtonPtr multipleIntervalButton;

class SingleSelection : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
	{

		beginEditCP(singleIntervalButton, ToggleButton::SelectedFieldMask);
			singleIntervalButton->setSelected(false);
		endEditCP(singleIntervalButton, ToggleButton::SelectedFieldMask);

		beginEditCP(multipleIntervalButton, ToggleButton::SelectedFieldMask);
			multipleIntervalButton->setSelected(false);
		endEditCP(multipleIntervalButton, ToggleButton::SelectedFieldMask);

		SelectionModel->setSelectionMode(DefaultListSelectionModel::SINGLE_SELECTION);
		
	}
      virtual void buttonDeselected(const ButtonSelectedEvent& e)
   {
   }

};

class SingleIntervalSelection : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
	{
		beginEditCP(singleButton, ToggleButton::SelectedFieldMask);
			singleButton->setSelected(false);
		endEditCP(singleButton, ToggleButton::SelectedFieldMask);

		beginEditCP(multipleIntervalButton, ToggleButton::SelectedFieldMask);
			multipleIntervalButton->setSelected(false);
		endEditCP(multipleIntervalButton, ToggleButton::SelectedFieldMask);

		SelectionModel->setSelectionMode(DefaultListSelectionModel::SINGLE_INTERVAL_SELECTION);
	}

   virtual void buttonDeselected(const ButtonSelectedEvent& e)
   {

   }
};

class MultipleIntervalSelection : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
	{	
		beginEditCP(singleButton, ToggleButton::SelectedFieldMask);
			singleButton->setSelected(false);
		endEditCP(singleButton, ToggleButton::SelectedFieldMask);

		beginEditCP(singleIntervalButton, ToggleButton::SelectedFieldMask);
			singleIntervalButton->setSelected(false);
		endEditCP(singleIntervalButton, ToggleButton::SelectedFieldMask);

		SelectionModel->setSelectionMode(DefaultListSelectionModel::MULTIPLE_INTERVAL_SELECTION);
	}

   virtual void buttonDeselected(const ButtonSelectedEvent& e)
   {
   }


};



int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    WindowEventProducerPtr TheWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TheWindowEventProducer->initWindow();
    
    TheWindowEventProducer->setDisplayCallback(display);
    TheWindowEventProducer->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TheWindowEventProducer->addWindowListener(&TheTutorialWindowListener);


    // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Main Scene Node
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        scene->setCore(osg::Group::create());
 
        // add the torus as a child
        scene->addChild(TorusGeometryNode);
    }
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

	// Create the Graphics
	GraphicsPtr graphics = osg::Graphics2D::create();

	// Initialize the LookAndFeelManager to enable default 
	// settings for the Button
	LookAndFeelManager::the()->getLookAndFeel()->init();


	// Create some Buttons to show changing List format
	singleButton = osg::ToggleButton::create();
	singleIntervalButton = osg::ToggleButton::create();
	multipleIntervalButton = osg::ToggleButton::create();
	// Give them text, change sizes, add ActionListeners
	beginEditCP(singleButton, Button::TextFieldMask | Component::PreferredSizeFieldMask);
		singleButton->setText("Single Selection");
		singleButton->setPreferredSize( Vec2s(160, 50) );
	endEditCP(singleButton, Button::TextFieldMask | Component::PreferredSizeFieldMask);
		SingleSelection singleButtonListener;
		singleButton->addButtonSelectedListener(&singleButtonListener);
	
	beginEditCP(singleIntervalButton, Button::TextFieldMask | Component::PreferredSizeFieldMask);
		singleIntervalButton->setText("Single Interval Selection");
		singleIntervalButton->setPreferredSize( Vec2s(160, 50) );
	endEditCP(singleIntervalButton, Button::TextFieldMask | Component::PreferredSizeFieldMask);
		SingleIntervalSelection singleIntervalButtonListener;
		singleIntervalButton->addButtonSelectedListener(&singleIntervalButtonListener);
	
	beginEditCP(multipleIntervalButton, Button::TextFieldMask | Component::PreferredSizeFieldMask);
		multipleIntervalButton->setText("Multiple Interval Selection");
		multipleIntervalButton->setPreferredSize( Vec2s(160, 50) );
	endEditCP(multipleIntervalButton, Button::TextFieldMask | Component::PreferredSizeFieldMask);
		MultipleIntervalSelection multipleIntervalButtonListener;
		multipleIntervalButton->addButtonSelectedListener(&multipleIntervalButtonListener);


	/******************************************************

			Create ListModel.  This is where you set
			the values for the List.

			After creating an AbstractListModel,
			do the following to make a list.
			
			First, create SFStrings and use the 
			.setValue("VALUE") function to set their
			values.  Then, use the .pushBack(&SFStringName)
			to add them to the List.

			Next, create the CellGenerator and ListSelectionModel
			defaults.

			Finally, actually create the List.  Set
			its Model, CellGenerator, and SelectionModel
			as shown below.  Finally, choose the
			type of display for the List (choices outlined
			below).

			

	******************************************************/
	// Create ListModel Component to add things to
	AbstractListModel Model;

	// Add values to it
	Model.pushBack(SharedFieldPtr(new SFString("Red")));
	Model.pushBack(SharedFieldPtr(new SFString("Green")));
	Model.pushBack(SharedFieldPtr(new SFString("Blue")));
	Model.pushBack(SharedFieldPtr(new SFString("Orange")));
	Model.pushBack(SharedFieldPtr(new SFString("Purple")));
	Model.pushBack(SharedFieldPtr(new SFString("Yellow")));
	Model.pushBack(SharedFieldPtr(new SFString("White")));
	Model.pushBack(SharedFieldPtr(new SFString("Black")));
	Model.pushBack(SharedFieldPtr(new SFString("Gray")));
	Model.pushBack(SharedFieldPtr(new SFString("Brown")));
	Model.pushBack(SharedFieldPtr(new SFString("Indigo")));
	Model.pushBack(SharedFieldPtr(new SFString("Pink")));
	Model.pushBack(SharedFieldPtr(new SFString("Violet")));
	Model.pushBack(SharedFieldPtr(new SFString("Mauve")));
	Model.pushBack(SharedFieldPtr(new SFString("Peach")));


	// Create ListCellRenderer and ListSelectionModel
	// (normally will be default).
	// Note that the DefaultListSelectionModel was
	// created at the top of this file before
	// the ActionListeners
	DefaultListCellGenerator CellGenerator;
	//DefaultListSelectionModel SelectionModel;

	// Create Background to be used with the Main Frame
	ColorUIBackgroundPtr mainBackground = osg::ColorUIBackground::create();
	beginEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
		mainBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
	endEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
	// Create ListPtr
	ListPtr list = List::create();
	beginEditCP(list);
		list->setPreferredSize( Vec2s (200, 300) );
		list->setBackground(mainBackground);
        list->setCellLayout(VERTICAL_ALIGNMENT);
        //list->setCellLayout(HORIZONTAL_ALIGNMENT);
	endEditCP(list);
	// Assign the Model, CellGenerator, and SelectionModel
	// to the List
	list->setModel(&Model);
	list->setCellGenerator(&CellGenerator);
	list->setSelectionModel(SelectionModel);


	/******************************************************

			Determine the SelectionModel
			-SINGLE_SELECTION lets you select ONE item
				via a single mouse click
			-SINGLE_INTERVAL_SELECTION lets you select
				one interval via mouse and SHIFT key
			-MULTIPLE_INTERVAL_SELECTION lets you select
				via mouse, and SHIFT and CONTRL keys

			Note: this tutorial is currently set up
			to allow for this to be changed via Buttons
			with ActionListeners attached to them so
			this code is commented out

	******************************************************/

	//SelectionModel.setMode(DefaultListSelectionModel::SINGLE_SELECTION);
	//SelectionModel.setMode(DefaultListSelectionModel::SINGLE_INTERVAL_SELECTION);
	//SelectionModel.setMode(DefaultListSelectionModel::MULTIPLE_INTERVAL_SELECTION);

    //ScrollPanel
    ScrollPanelPtr TheScrollPanel = ScrollPanel::create();
    beginEditCP(TheScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
	    TheScrollPanel->setPreferredSize(Vec2s(200,300));
        TheScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //TheScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(TheScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    TheScrollPanel->setViewComponent(list);

	// Create MainFramelayout
	FlowLayoutPtr MainFrameLayout = osg::FlowLayout::create();
	beginEditCP(MainFrameLayout, FlowLayout::AlignmentFieldMask | FlowLayout::MajorAxisAlignmentFieldMask | FlowLayout::MinorAxisAlignmentFieldMask);
		MainFrameLayout->setAlignment(HORIZONTAL_ALIGNMENT);
		MainFrameLayout->setMajorAxisAlignment(AXIS_CENTER_ALIGNMENT);
		MainFrameLayout->setMinorAxisAlignment(AXIS_CENTER_ALIGNMENT);
	endEditCP(MainFrameLayout, FlowLayout::AlignmentFieldMask | FlowLayout::MajorAxisAlignmentFieldMask | FlowLayout::MinorAxisAlignmentFieldMask);
		

	// Create The Main Frame
	FramePtr MainFrame = osg::Frame::create();
	beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);
	   MainFrame->getChildren().addValue(singleButton);
	   MainFrame->getChildren().addValue(singleIntervalButton);
	   MainFrame->getChildren().addValue(multipleIntervalButton);
	   MainFrame->getChildren().addValue(TheScrollPanel);
	   MainFrame->setLayout(MainFrameLayout);
	   MainFrame->setBackground(mainBackground);
	endEditCP  (MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);

	// Create the Drawing Surface
	UIDrawingSurfacePtr drawingSurface = UIDrawingSurface::create();
	beginEditCP(drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask | UIDrawingSurface::EventProducerFieldMask);
		drawingSurface->setGraphics(graphics);
		drawingSurface->setRootFrame(MainFrame);
	    drawingSurface->setEventProducer(TheWindowEventProducer);
    endEditCP  (drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask | UIDrawingSurface::EventProducerFieldMask);
	
	// Create the UI Foreground Object
	UIForegroundPtr foreground = osg::UIForeground::create();

	beginEditCP(foreground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
	    foreground->setDrawingSurface(drawingSurface);
		foreground->setFramePositionOffset(Vec2s(0,0));
		foreground->setFrameBounds(Vec2f(0.7,0.5));
    endEditCP  (foreground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the manager what to manage
    mgr->setWindow(MainWindow);
    mgr->setRoot(scene);

	// Add the UI Foreground Object to the Scene
	ViewportPtr viewport = mgr->getWindow()->getPort(0);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);
		viewport->getForegrounds().addValue(foreground);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);

    // Show the whole scene
    mgr->showAll();

    TheWindowEventProducer->openWindow(Pnt2s(50,50),
                                        Vec2s(900,900),
                                        "OpenSG 18List Window");

    //Main Event Loop
    while(!ExitApp)
    {
        TheWindowEventProducer->update();
        TheWindowEventProducer->draw();
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