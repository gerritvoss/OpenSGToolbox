// OpenSG Tutorial Example: Creating Multiple Buttons
//		and Placing Buttons in the Window
//
// This tutorial explains how to place buttons within a 
// frame utilizing the Box Layout command to 
// manage the layout through the OSG User Interface library.
// 
// Includes: placing multiple buttons using BoxLayout


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


// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>


//UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGBoxLayout.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>


// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );
void display(void);

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);


    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();


    //Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    //Make Main Scene Node
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        scene->setCore(osg::Group::create());
 
        // add the torus as a child
        scene->addChild(TorusGeometryNode);
    }
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

	//Create the Graphics
	GraphicsPtr graphics = osg::Graphics2D::create();

	//Initialize the LookAndFeelManager to enable default 
	//settings for the Buttons
	LookAndFeelManager::the()->getLookAndFeel()->init();



	//Creates some Button components to add
	ButtonPtr button = osg::Button::create();
	ButtonPtr button2 = osg::Button::create();
	ButtonPtr button3 = osg::Button::create();
	ButtonPtr button4 = osg::Button::create();


	/******************************************************

		Create Box Layout.  Box Layout arranges objects
		automatically within the Frame, so that the objects
		are evenly spaced within the Frame.

		Box Layout also causes all objects to have the same 
		height (if arranged Horizontally) or the same width
		(if arranged Vertically) using the maximum width of the
		objects in the Layout.  This overrides the specified 
		dimensions of the object, unless the object has a 
		Maximum or Minimum size set.  In this case, the object 
		size cannot be changed to greater than the Maximum size,
		or less than the Minimum size (it will still be changed,
		however it will not exceed the Max/Min size).

		You can experiment with this by changing the window 
		size, changing the size of the Buttons as shown 
		in 01Button, editing the Buttons, or adding more 
		Buttons to the view.

		Note that if the Frame is too small, the objects will 
		appear out of the Frame background.


	******************************************************/
	BoxLayoutPtr MainFrameLayout = osg::BoxLayout::create();

	//Determine whether the Layout is Horizontal (HORIZONTAL_ALIGNMENT) or
	//Vertical (VERTICAL_ALIGNMENT)
	beginEditCP(MainFrameLayout);
		MainFrameLayout->setAlignment(VERTICAL_ALIGNMENT);
		//MainFrameLayout->setAlignment(HORIZONTAL_ALIGNMENT);
	endEditCP(MainFrameLayout); 
	

	//Edit two different Buttons
	beginEditCP(button, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::SizeFieldMask);
		button->setPreferredSize( Vec2s(80,50) );
		//Set button to have a MaxSize.  This is never exceeded, therefore
		//even in BoxLayout it will not change to have a width of greater than
		//80.  By commenting the setMaxSize line, button will have its width 
		//expanded to match the size of the largest object in the BoxLayout;
		//in this case button2.
		button->setMaxSize( Vec2s (80, 50) );
	endEditCP(button, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::SizeFieldMask);

	beginEditCP(button2, Button::PreferredSizeFieldMask | Button::SizeFieldMask);
		//Edit the PreferredSize of button2.  Because this is the largest
		//PreferredSize, all Buttons will have the same width unless they
		//have MaxSize limits (see above).  If setPreferredSize is commented, 
		//and setSize uncommented, note that button2 will no longer have the same
		//display size.
		//button2->setPreferredSize( Vec2s(200,100) );
		button2->setSize( Vec2s(200,100) );
	endEditCP(button2, Button::PreferredSizeFieldMask | Button::SizeFieldMask);

 	//Create The Main Frame

	//Create Background to be used with the Main Frame
	ColorUIBackgroundPtr mainBackground = osg::ColorUIBackground::create();
	beginEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
		mainBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
	endEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
	
	FramePtr MainFrame = osg::Frame::create();
	beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);
	   //Add the buttons to the mainframe so they will be displayed
	   MainFrame->getChildren().addValue(button);
	   MainFrame->getChildren().addValue(button2);
	   MainFrame->getChildren().addValue(button3);
	   MainFrame->getChildren().addValue(button4);
	   //Add the Layout to the MainFrame
	   MainFrame->setLayout(MainFrameLayout);
	   MainFrame->setBackground(mainBackground);
	 
    endEditCP  (MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);

	//Create the UI Foreground Object
	UIForegroundPtr foreground = osg::UIForeground::create();

	beginEditCP(foreground, UIForeground::GraphicsFieldMask | UIForeground::RootFrameFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
		foreground->setGraphics(graphics);
		foreground->setRootFrame(MainFrame);
		foreground->setFramePositionOffset(Vec2s(0,0));
		foreground->setFrameBounds(Vec2f(0.5,0.5));
    endEditCP  (foreground, UIForeground::GraphicsFieldMask | UIForeground::RootFrameFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);

	//Add the UI Foreground Object to the Scene
	ViewportPtr viewport = mgr->getWindow()->getPort(0);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);
		viewport->getForegrounds().addValue(foreground);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);

    // show the whole scene
    mgr->showAll();

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

void idle(void)
{
   glutPostRedisplay();
}

// redraw the window
void display(void)
{
    mgr->redraw();
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
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
}
