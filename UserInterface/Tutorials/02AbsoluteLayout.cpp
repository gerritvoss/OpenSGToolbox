// OpenSG Tutorial Example: Creating Multiple Buttons
//		and Placing Buttons in the Window
//
// This example explains how to place buttons within a 
// frame utilizing the Absolute Layout command to 
// manage the layout through the OSG User Interface library.
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


// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>


//UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayout.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>

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
	//settings for the Button
	LookAndFeelManager::the()->getLookAndFeel()->init();



	//Create three different Buttons (button, button2, and
	//button3) and their Components.  All Buttons will have the same
	//border, though this could also be changed and give each Button
	//a unique border.

	//Creates three Button components
	ButtonPtr button = osg::Button::create();
	ButtonPtr button2 = osg::Button::create();
	ButtonPtr button3 = osg::Button::create();
	
	//Create the three unique AbsoluteLayoutConstraints pointers,
	//one for each Button
	AbsoluteLayoutConstraintsPtr buttonConstraints = osg::AbsoluteLayoutConstraints::create();
	AbsoluteLayoutConstraintsPtr buttonConstraints2 = osg::AbsoluteLayoutConstraints::create();
	AbsoluteLayoutConstraintsPtr buttonConstraints3 = osg::AbsoluteLayoutConstraints::create();

  
   //Define the Button constraints (where the buttons are located in the layout)
   //setPosition gives you the location of the button relative to the 
   //layout manager's upper left hand corner.  Note that with the AbsoluteLayoutConstraints,
   //the buttons may appear out of the light purple box, as their positions are absolute and
   //not relative to other objects.  By adjusting the window size, this can be easily seen.
   beginEditCP(buttonConstraints);
		buttonConstraints->setPosition(Pnt2s (0,150) );
   endEditCP(buttonConstraints);

   beginEditCP(buttonConstraints2);
		buttonConstraints2->setPosition(Pnt2s (200,200) );
   endEditCP(buttonConstraints2);
	
   //Note that this will cause the button's position to overlap with Button2
   //when the program is run; the AbsoluteLayoutConstraints will overlap
   //if the specified coordinates overlap
   beginEditCP(buttonConstraints3);
		buttonConstraints3->setPosition(Pnt2s (150,220) );
   endEditCP(buttonConstraints3);

   //Edit the first button, set size, color, border, font, text, and constraints
   //to those created above
    beginEditCP(button);
		button->setPreferredSize(Vec2s(100,50));
		button->setSize(Vec2s(100,50));
		button->setText("Button 1");
		
		//Set the constraints created above to button
		//to place the Button within the scene
		button->setConstraints(buttonConstraints);
    endEditCP  (button);

	//Edit the second button, set size, color, border, font, text, and constraints
    //to those created above
    beginEditCP(button2);
		button2->setPreferredSize(Vec2s(100,50));
		button2->setSize(Vec2s(100,50));
		button2->setText("Button 2");
		
		//Set the constraints created above to button2
		//to place the Button within the scene
		button2->setConstraints(buttonConstraints2);
    endEditCP  (button2);

	//Edit the third button, set size, color, border, font, text, and constraints
    //to those created above
    beginEditCP(button3);
		button3->setPreferredSize(Vec2s(100,50));
		button3->setSize(Vec2s(100,50));
		button3->setText("Button 3");
		
		//Set the constraints created above to button3
		//to place the Button within the scene
		button3->setConstraints(buttonConstraints3);
    endEditCP  (button3);

	//Create The Main Frame
	FramePtr MainFrame = osg::Frame::create();
	LayoutPtr MainFrameLayout = osg::AbsoluteLayout::create();
	beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);
	   //Add the buttons to the mainframe so they will be displayed.
	   //They are displayed in reverse order, so in this case, since button2
	   //and button3 are in conflict, button2 will cover button3.  By commenting
	   //out the addValue commands and uncommenting the others, this will
	   //be reversed.
	   MainFrame->getChildren().addValue(button);
	   MainFrame->getChildren().addValue(button3);
	   MainFrame->getChildren().addValue(button2);
	   //MainFrame->getChildren().addValue(button2);
	   //MainFrame->getChildren().addValue(button3);
	   MainFrame->setLayout(MainFrameLayout);
	 
    endEditCP  (MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);

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
