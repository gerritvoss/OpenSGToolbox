// OpenSG Tutorial Example: Using the AbsoluteLayout
//
// This tutorial explains how to place buttons within a 
// frame utilizing the Absolute Layout to manage the layout 
// through the OSG User Interface library.
// 
// Includes: placing multiple buttons and using 
// AbsoluteLayoutConstraints to locate the buttons.


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
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>

// Include AbsoluteLayout and AbsoluteLayoutConstraints header files
#include <OpenSG/UserInterface/OSGAbsoluteLayout.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayoutConstraints.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );
void display(void);
void reshape(Vec2s Size);

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    WindowPtr MainWindow;
    WindowEventProducerPtr TheWindowEventProducer;
    createDefaultWindow(Pnt2s(50,50),
                                        Vec2s(550,550),
                                        "OpenSG 02AbsoluteLayout Window",
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

   beginEditCP(button1, Button::PreferredSizeFieldMask |  Button::SizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);
		button1->setPreferredSize(Vec2s(100,50));
		button1->setSize(Vec2s(100,50));
		button1->setText("Button 1");
		
		// Set the constraints created above to button
		// to place the Button within the scene
		button1->setConstraints(buttonConstraints1);
	endEditCP(button1, Button::PreferredSizeFieldMask | Button::SizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);

    beginEditCP(button2, Button::PreferredSizeFieldMask |  Button::SizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);
		button2->setPreferredSize(Vec2s(100,50));
		button2->setSize(Vec2s(100,50));
		button2->setText("Button 2");
		
		// Set the constraints created above to button2
		// to place the Button within the scene
		button2->setConstraints(buttonConstraints2);
    endEditCP  (button2, Button::PreferredSizeFieldMask | Button::SizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);

    beginEditCP(button3,  Button::PreferredSizeFieldMask | Button::SizeFieldMask | Button::ConstraintsFieldMask);
		button3->setPreferredSize(Vec2s(100,50));
		button3->setSize(Vec2s(100,50));
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

    // main loop
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

// react to mouse button presses
/*void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:        
        {
            OSG::osgExit();
            exit(0);
        }
        break;
    }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG UserInterface Button");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    return winid;
}*/
