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
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayout.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGMatteBorder.h>
#include <OpenSG/UserInterface/OSGCompoundBorder.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGBevelBorder.h>
#include <OpenSG/UserInterface/OSGEtchedBorder.h>

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
	MatteBorderPtr border = osg::MatteBorder::create();
	MatteBorderPtr border2 = osg::MatteBorder::create();
	CompoundBorderPtr fborder = osg::CompoundBorder::create();
	LineBorderPtr lborder = osg::LineBorder::create();
	BevelBorderPtr bborder = osg::BevelBorder::create();
	EtchedBorderPtr eborder = osg::EtchedBorder::create();


	beginEditCP(lborder);
		lborder->setWidth(1);
		lborder->setColor(Color4f(.7, 0.0, .5, 1.0));
	endEditCP(lborder);

	beginEditCP(eborder);
		eborder->setWidth(9);
		eborder->setHighlight(Color4f(0.0, 0.0, 1.0, 1.0));
		eborder->setShadow(Color4f(1.0, 0.0, 0.0, 1.0));
		eborder->setRaised(true);
	endEditCP(eborder);


	beginEditCP(border);
		border->setLeftWidth(3);
		border->setRightWidth(2);
		border->setBottomWidth(9);
		border->setTopWidth(1);
		border->setColor(Color4f(1.0, .5, .5, 1.0));
	endEditCP(border);

	beginEditCP(border2);
		border2->setLeftWidth(6);
		border2->setRightWidth(8);
		border2->setBottomWidth(5);
		border2->setTopWidth(3);
		border2->setColor(Color4f(0.0, .5, .5, 1.0));
	endEditCP(border2);

	beginEditCP(bborder);
		bborder->setRaised(false);
		bborder->setWidth(5);
		bborder->setHighlightInner(Color4f(1.0, 1.0, .5, 1.0));
		bborder->setHighlightOuter(Color4f(.5, 1.0, 1.0, 1.0));
		bborder->setShadowInner(Color4f(1.0, .5, 1.0, 1.0));
		bborder->setShadowOuter(Color4f(.5, .5, 1.0, 1.0));
	endEditCP(bborder);

	beginEditCP(fborder);
		fborder->setInnerBorder(border);
		fborder->setOuterBorder(border2);
	endEditCP(fborder);


	beginEditCP(button, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);
		button->setPreferredSize(Vec2s(100,50));
		button->setText("Button 1");
		button->setBorder(eborder);
	endEditCP  (button, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);

	//Create The Main Frame
	FramePtr MainFrame = osg::Frame::create();
	LayoutPtr MainFrameLayout = osg::AbsoluteLayout::create();
	beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);
	   MainFrame->getChildren().addValue(button);
	   MainFrame->setLayout(MainFrameLayout);
	   //MainFrame->setBackgroundColor(Color4f(0.0,0.0,0.5,0.3));
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
