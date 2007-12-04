// OpenSG Tutorial Example: Using the AbsoluteLayout
//
// This tutorial explains how to place buttons within a 
// frame utilizing the Absolute Layout to manage the layout 
// through the OSG User Interface library.
// 
// Includes: placing multiple buttons and using 
// AbsoluteLayoutConstraints to locate the buttons.



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

// Include AbsoluteLayout and AbsoluteLayoutConstraints header files
#include <OpenSG/UserInterface/OSGAbsoluteLayout.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>

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

		Create three Button Components (button1, button2,
		and button3) and their AbsoluteLayoutConstraints.

		AbsoluteLayoutConstraints are used within the 
		AbsoluteLayout to define where the Components will
		be placed.  Most other Layouts do not need 
		Constraints, as they place things within the Layout
		automatically.

	******************************************************/

	ButtonPtr button1 = osg::Button::create();
	ButtonPtr button2 = osg::Button::create();
	ButtonPtr button3 = osg::Button::create();
	
	AbsoluteLayoutConstraintsPtr buttonConstraints1 = osg::AbsoluteLayoutConstraints::create();
	AbsoluteLayoutConstraintsPtr buttonConstraints2 = osg::AbsoluteLayoutConstraints::create();
	AbsoluteLayoutConstraintsPtr buttonConstraints3 = osg::AbsoluteLayoutConstraints::create();

	/******************************************************

		Define the AbsoluteLayoutConstraints (where Buttons 
		are located in the Layout).  setPosition gives you 
		the location of the Button relative to the Layout
		manager's upper left hand corner.  Buttons will
		not display if their AbsoluteLayoutConstraints 
		place them outside the Frame in which they are to
		be rendered (the part within the Frame still does
		display).  Changing the window size shows an 
		example of this.

	******************************************************/
  
   beginEditCP(buttonConstraints1, AbsoluteLayoutConstraints::PositionFieldMask);
		buttonConstraints1->setPosition( Pnt2s(0,150) );
   endEditCP(buttonConstraints1, AbsoluteLayoutConstraints::PositionFieldMask);

   beginEditCP(buttonConstraints2, AbsoluteLayoutConstraints::PositionFieldMask);
		buttonConstraints2->setPosition( Pnt2s(200,200) );
   endEditCP(buttonConstraints2, AbsoluteLayoutConstraints::PositionFieldMask);
	
   // Note that this will cause the button's position to overlap with Button2
   // when the program is run; the AbsoluteLayoutConstraints will overlap
   // if the specified coordinates overlap
   beginEditCP(buttonConstraints3, AbsoluteLayoutConstraints::PositionFieldMask);
		buttonConstraints3->setPosition( Pnt2s(150,220) );
   endEditCP(buttonConstraints3, AbsoluteLayoutConstraints::PositionFieldMask);

	/******************************************************

		Edit Button Components and assign Text,
		PreferredSize, and AbsoluteLayoutConstraints

	******************************************************/

   beginEditCP(button1, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);
		button1->setPreferredSize(Vec2s(100,50));
		button1->setText("Button 1");
		
		// Set the constraints created above to button
		// to place the Button within the scene
		button1->setConstraints(buttonConstraints1);
	endEditCP(button1, Button::PreferredSizeFieldMask |Button::TextFieldMask | Button::ConstraintsFieldMask);

    beginEditCP(button2, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);
		button2->setPreferredSize(Vec2s(100,50));
		button2->setText("Button 2");
		
		// Set the constraints created above to button2
		// to place the Button within the scene
		button2->setConstraints(buttonConstraints2);
    endEditCP  (button2, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);

    beginEditCP(button3,  Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);
		button3->setPreferredSize(Vec2s(100,50));
		button3->setText("Button 3");
		
		// Set the constraints created above to button3
		// to place the Button within the scene
		button3->setConstraints(buttonConstraints3);
    endEditCP  (button3,  Button::PreferredSizeFieldMask | Button::SizeFieldMask | Button::ConstraintsFieldMask);

	// Create The Main Frame
	// Create Background to be used with the Main Frame
	ColorUIBackgroundPtr mainBackground = osg::ColorUIBackground::create();
	beginEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
		mainBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
	endEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
	
	FramePtr MainFrame = osg::Frame::create();
	LayoutPtr MainFrameLayout = osg::AbsoluteLayout::create();
	beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);
	   // Add the buttons to the mainframe so they will be displayed.
	   // They are displayed in reverse order, so in this case, since button2
	   // and button3 are in conflict with their locations, button2 will cover 
	   // button3.  By commenting out their addValue commands and uncommenting 
	   // the other two, this will be reversed.
	   MainFrame->getChildren().addValue(button1);
	   MainFrame->getChildren().addValue(button3);
	   MainFrame->getChildren().addValue(button2);
	   // MainFrame->getChildren().addValue(button2);
	   // MainFrame->getChildren().addValue(button3);
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

	beginEditCP(foreground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
	    foreground->setDrawingSurface(drawingSurface);
		foreground->setFramePositionOffset(Vec2s(0,0));
		foreground->setFrameBounds(Vec2f(0.5,0.5));
	   //Set the Event Producer for the DrawingSurface
	   //This is needed in order to get Mouse/Keyboard/etc Input to the UI DrawingSurface
    endEditCP  (foreground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);

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

    TheWindowEventProducer->openWindow(Pnt2s(50,50),
                                        Vec2s(550,550),
                                        "OpenSG 02AbsoluteLayout Window");

    //Main Event Loop
    while(!ExitApp)
    {
        TheWindowEventProducer->update();
        TheWindowEventProducer->draw();
    }
    osgExit();

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
