// OpenSG Tutorial Example: Hello World
//
// Minimalistic OpenSG program
// 
// This is the shortest useful OpenSG program 
// (if you remove all the comments ;)
//
// It shows how to use OpenSG together with GLUT to create a little
// interactive scene viewer.
//

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
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayout.h>
#include <OpenSG/UserInterface/OSGBoxLayout.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGCardLayout.h>
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


    //Make Torus Node
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

	//Init the LookAndFeel
	LookAndFeelManager::the()->getLookAndFeel()->init();

	//Create A Button Component
	ButtonPtr button = osg::Button::create();
	ButtonPtr button2 = osg::Button::create();
	ButtonPtr button3 = osg::Button::create();
	ButtonPtr button4 = osg::Button::create();
	ButtonPtr button5 = osg::Button::create();
	ButtonPtr button6 = osg::Button::create();

	beginEditCP(button, Button::PreferredSizeFieldMask | Button::TextFieldMask);
		button->setPreferredSize(Vec2s(60,10));
		button->setMaxSize(Vec2s(80,30));
		button->setText("1");
    endEditCP  (button, Button::PreferredSizeFieldMask | Button::TextFieldMask);

	beginEditCP(button2, Button::PreferredSizeFieldMask | Button::TextFieldMask);
		button2->setPreferredSize(Vec2s(40,50));
		button2->setText("2");
    endEditCP  (button2, Button::PreferredSizeFieldMask | Button::TextFieldMask);\

	beginEditCP(button3, Button::PreferredSizeFieldMask | Button::TextFieldMask);
		button3->setPreferredSize(Vec2s(60,40));
		button3->setText("3");
    endEditCP  (button3, Button::PreferredSizeFieldMask | Button::TextFieldMask);

	beginEditCP(button4, Button::PreferredSizeFieldMask | Button::TextFieldMask);
		button4->setPreferredSize(Vec2s(40,60));
		button4->setText("4");
    endEditCP  (button4, Button::PreferredSizeFieldMask | Button::TextFieldMask);

	beginEditCP(button5, Button::PreferredSizeFieldMask | Button::TextFieldMask);
		button5->setPreferredSize(Vec2s(20,50));
		button5->setText("5");
		button5->setMaxSize(Vec2s(20,50));
    endEditCP  (button5, Button::PreferredSizeFieldMask | Button::TextFieldMask);

	beginEditCP(button6, Button::PreferredSizeFieldMask | Button::TextFieldMask);
		button6->setPreferredSize(Vec2s(30,20));
		button6->setText("6");
    endEditCP  (button6, Button::PreferredSizeFieldMask | Button::TextFieldMask);

	//Create a custom background
	ColorUIBackgroundPtr background = osg::ColorUIBackground::create();
	beginEditCP(background);
		background->setColor(Color4f(1.0, 0.0, 0.0, 0.5));
	endEditCP(background);

	//Create The Main Frame
	FramePtr MainFrame = osg::Frame::create();
	LayoutPtr MainFrameLayout = osg::BoxLayout::create();
	beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);
	   MainFrame->getChildren().addValue(button);
	   MainFrame->getChildren().addValue(button2);
	   MainFrame->getChildren().addValue(button3);
	   MainFrame->getChildren().addValue(button4);
	   MainFrame->getChildren().addValue(button5);
	   MainFrame->getChildren().addValue(button6);
	   MainFrame->setLayout(MainFrameLayout);
	   MainFrame->setBackground(background);
    endEditCP  (MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);

/*	beginEditCP(MainFrameLayout);
		MainFrameLayout->last(MainFrame);
		MainFrameLayout->next(MainFrame);
	endEditCP(MainFrameLayout);*/

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
