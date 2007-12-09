// OpenSG Tutorial Example: Using the Flow Layout
//		to place Components 
//
// This tutorial explains how to place Buttons within a 
// frame utilizing the Flow Layout command to 
// manage the layout through the OSG User Interface library.
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

// 14RadioButton Headers
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
#include <OpenSG/UserInterface/OSGBevelBorder.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGRadioButton.h>
#include <OpenSG/UserInterface/OSGRadioButtonGroup.h>

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

    // Set up Window
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




	/******************************************************
			
			Creates some RadioButton components 
			and edit them.  The RadioButton class
			inherits from the Button class.

			Advanced options for RadioButton can
			be found in the DefaultLookAndFeel.cpp
			file found in OSGUserInterface/Source Files/
			LookAndFeel.

	******************************************************/
	RadioButtonPtr button1 = osg::RadioButton::create();
	RadioButtonPtr button2 = osg::RadioButton::create();
	RadioButtonPtr button3 = osg::RadioButton::create();

	beginEditCP(button1, Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask | Component::PreferredSizeFieldMask | Button::TextFieldMask);
		button1->setVerticalAlignment(0.5);
		button1->setHorizontalAlignment(0.0);
		button1->setPreferredSize(Vec2s(100, 50));
		button1->setText("Option 1");
	endEditCP(button1, Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask | Component::PreferredSizeFieldMask | Button::TextFieldMask);

	beginEditCP(button2,Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask | Component::PreferredSizeFieldMask | Button::TextFieldMask);
		button2->setVerticalAlignment(0.5);
		button2->setHorizontalAlignment(0.0);
		button2->setPreferredSize(Vec2s(100, 50));
		button2->setText("Option 2");
	endEditCP(button2, Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask | Component::PreferredSizeFieldMask | Button::TextFieldMask);

	beginEditCP(button3, Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask | Component::PreferredSizeFieldMask | Button::TextFieldMask);
		button3->setVerticalAlignment(0.5);
		button3->setHorizontalAlignment(0.0);
		button3->setPreferredSize(Vec2s(100, 50));
		button3->setText("Option 3");
	endEditCP(button3, Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask | Component::PreferredSizeFieldMask | Button::TextFieldMask);

	/***************************************************
					
		Create and populate the group of Radio Buttons
		Defining the group allows you to pick which radio
		buttons are tied together so that only one can be
		selected. Note that RadioButtonGroup is not a Field
		Container, so it is edited differently

		Radio Buttons are special toggle buttons.  When 
		they are selected, any radio button in the same 
		group is deselected, so there can only be one 
		option selected.

	******************************************************/
	RadioButtonGroup buttonGroup;
	buttonGroup.addButton(button1);
	buttonGroup.addButton(button2);
	buttonGroup.addButton(button3);

	FlowLayoutPtr MainFrameLayout = osg::FlowLayout::create();

	beginEditCP(MainFrameLayout, FlowLayout::AlignmentFieldMask | FlowLayout::MajorAxisAlignmentFieldMask | FlowLayout::MinorAxisAlignmentFieldMask);
		MainFrameLayout->setAlignment(VERTICAL_ALIGNMENT);
		MainFrameLayout->setMajorAxisAlignment(AXIS_CENTER_ALIGNMENT);
		MainFrameLayout->setMinorAxisAlignment(AXIS_CENTER_ALIGNMENT);
	endEditCP(MainFrameLayout, FlowLayout::AlignmentFieldMask | FlowLayout::MajorAxisAlignmentFieldMask | FlowLayout::MinorAxisAlignmentFieldMask);
	
 	// Create The Main Frame
	// Create Background to be used with the Main Frame
	ColorUIBackgroundPtr mainBackground = osg::ColorUIBackground::create();
	beginEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
		mainBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
	endEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
	
	FramePtr MainFrame = osg::Frame::create();
	beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);
	   MainFrame->getChildren().addValue(button1);
	   MainFrame->getChildren().addValue(button2);
	   MainFrame->getChildren().addValue(button3);
	   MainFrame->setLayout(MainFrameLayout);
	   MainFrame->setBackground(mainBackground);
	   MainFrame->setAllInsets(10);
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
		foreground->setFrameBounds(Vec2f(0.5,0.5));
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
                                        "OpenSG 14RadioButton Window");

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