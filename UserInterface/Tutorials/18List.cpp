// OpenSG Tutorial Example: Creating a List
//
// This tutorial explains how to place Buttons within a 
// frame utilizing the Flow Layout command to 
// manage the layout through the OSG User Interface library.
// 
// Includes: placing multiple buttons using Flow Layout

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGFieldFactory.h>


// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

//Input
#include <OpenSG/Input/OSGWindowUtils.h>

//UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
#include <OpenSG/UserInterface/OSGBevelBorder.h>

// Include relevant header files
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGButton.h>

// List header files
#include <OpenSG/UserInterface/OSGList.h>
#include <OpenSG/UserInterface/OSGAbstractListModel.h>
#include <OpenSG/UserInterface/OSGDefaultListCellGenerator.h>
#include <OpenSG/UserInterface/OSGDefaultListSelectionModel.h>
// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2s Size);



// Declare the SelectionModel up front to allow for
// the ActionListeners
DefaultListSelectionModel SelectionModel;
class SingleSelection : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
	{
		SelectionModel.setSelectionMode(DefaultListSelectionModel::SINGLE_SELECTION);
		
	}
};

class SingleIntervalSelection : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
	{
		SelectionModel.setSelectionMode(DefaultListSelectionModel::SINGLE_INTERVAL_SELECTION);
	}
};

class MultipleIntervalSelection : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
	{
		SelectionModel.setSelectionMode(DefaultListSelectionModel::MULTIPLE_INTERVAL_SELECTION);
	}
};



int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    WindowPtr MainWindow;
    WindowEventProducerPtr TheWindowEventProducer;
    createDefaultWindow(Pnt2s(50,50),
                                        Vec2s(900,900),
                                        "OpenSG 18List Window",
                                        MainWindow,
                                        TheWindowEventProducer);
    
    TheWindowEventProducer->setDisplayCallback(display);
    TheWindowEventProducer->setReshapeCallback(reshape);


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
	ButtonPtr singleButton = osg::Button::create();
	ButtonPtr singleIntervalButton = osg::Button::create();
	ButtonPtr multipleIntervalButton = osg::Button::create();
	// Give them text, change sizes, add ActionListeners
	beginEditCP(singleButton, Button::TextFieldMask);
		singleButton->setText("Single Selection");
		singleButton->setPreferredSize( Vec2s(200, 50) );
	endEditCP(singleButton, Button::TextFieldMask);
	SingleSelection singleButtonListener;
		singleButton->addActionListener(&singleButtonListener);
	
	beginEditCP(singleIntervalButton, Button::TextFieldMask);
		singleIntervalButton->setText("Single Inteveral Selection");
		singleIntervalButton->setPreferredSize( Vec2s(200, 50) );
	endEditCP(singleIntervalButton, Button::TextFieldMask);
	SingleIntervalSelection singleIntervalButtonListener;
		singleIntervalButton->addActionListener(&singleIntervalButtonListener);
	
	beginEditCP(multipleIntervalButton, Button::TextFieldMask);
		multipleIntervalButton->setText("Multiple Inverval Selection");
		multipleIntervalButton->setPreferredSize( Vec2s(200, 50) );
	endEditCP(multipleIntervalButton, Button::TextFieldMask);
	MultipleIntervalSelection multipleIntervalButtonListener;
		multipleIntervalButton->addActionListener(&multipleIntervalButtonListener);


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
	SFString StrField1;
	StrField1.setValue("Red");
	Model.pushBack(&StrField1);
	SFString StrField2;
	StrField2.setValue("Green");
	Model.pushBack(&StrField2);
	SFString StrField3;
	StrField3.setValue("Blue");
	Model.pushBack(&StrField3);
	SFString StrField4;
	StrField4.setValue("Orange");
	Model.pushBack(&StrField4);
	SFString StrField5;
	StrField5.setValue("Yellow");
	Model.pushBack(&StrField5);
	SFString StrField6;
	StrField6.setValue("Purple");
	Model.pushBack(&StrField6);


	// Create ListCellRenderer and ListSelectionModel
	// (should always be default).
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
	endEditCP(list);
	// Assign the Model, CellGenerator, and SelectionModel
	// to the List
	list->setModel(&Model);
	list->setCellGenerator(&CellGenerator);
	list->setSelectionModel(&SelectionModel);


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
			with ActionListeners attached to them

	******************************************************/

	//SelectionModel.setMode(DefaultListSelectionModel::SINGLE_SELECTION);
	//SelectionModel.setMode(DefaultListSelectionModel::SINGLE_INTERVAL_SELECTION);
	//SelectionModel.setMode(DefaultListSelectionModel::MULTIPLE_INTERVAL_SELECTION);


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
	   // Add things to the MainFrame
	   MainFrame->getChildren().addValue(singleButton);
	   MainFrame->getChildren().addValue(singleIntervalButton);
	   MainFrame->getChildren().addValue(multipleIntervalButton);
	   MainFrame->getChildren().addValue(list);
	   MainFrame->setLayout(MainFrameLayout);
	   MainFrame->setBackground(mainBackground);
	endEditCP  (MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);

	//Create the Drawing Surface
	UIDrawingSurfacePtr drawingSurface = UIDrawingSurface::create();
	beginEditCP(drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask);
		drawingSurface->setGraphics(graphics);
		drawingSurface->setRootFrame(MainFrame);
	    drawingSurface->setEventProducer(TheWindowEventProducer);
    endEditCP  (drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask);
	
	// Create the UI Foreground Object
	UIForegroundPtr foreground = osg::UIForeground::create();

	beginEditCP(foreground, UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
	    foreground->setDrawingSurface(drawingSurface);
		foreground->setFramePositionOffset(Vec2s(0,0));
		foreground->setFrameBounds(Vec2f(0.5,0.5));
	   //Set the Event Producer for the DrawingSurface
	   //This is needed in order to get Mouse/Keyboard/etc Input to the UI DrawingSurface
    endEditCP  (foreground, UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(MainWindow );
    mgr->setRoot  (scene);

	// Add the UI Foreground Object to the Scene
	ViewportPtr viewport = mgr->getWindow()->getPort(0);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);
		viewport->getForegrounds().addValue(foreground);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);

    // show the whole scene
    mgr->showAll();

    openWindow(TheWindowEventProducer);

    return 0;
}

// redraw the window
void display(void)
{
    mgr->redraw();
}

// react to size changes
void reshape(Vec2s Size)
{
    mgr->resize(Size.x(), Size.y());
}
