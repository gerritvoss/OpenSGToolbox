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
#include <OpenSG/UserInterface/OSGCanvas.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayout.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>

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

	//Create A Button Component
	ButtonPtr button = osg::Button::create();
	LineBorderPtr buttonBorder = osg::LineBorder::create();
   FontPtr buttonFont = Font::create();
   beginEditCP(buttonFont);
      buttonFont->setSize(24);
   endEditCP(buttonFont);

   beginEditCP(buttonBorder, LineBorder::WidthFieldMask | LineBorder::ColorFieldMask);
      buttonBorder->setWidth(1);
      buttonBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
   endEditCP  (buttonBorder, LineBorder::WidthFieldMask | LineBorder::ColorFieldMask);

    beginEditCP(button, Button::SizeFieldMask);
		button->setPreferredSize(Vec2s(100,100));
		button->setBackgroundColor(Color4f(0.8,0.8,0.8,1.0));
		button->setForegroundColor(Color4f(0.0,0.0,0.0,1.0));
		button->setBorder(buttonBorder);
		button->setFont(buttonFont);
		button->setText("Button 1");
    endEditCP  (button, Button::SizeFieldMask);
	ComponentPtr canvas = osg::Canvas::create();

	PanelPtr panel = osg::Panel::create();
	LayoutPtr layout = osg::AbsoluteLayout::create();

   beginEditCP(panel, Panel::LayoutFieldMask | Panel::ChildrenFieldMask);
      panel->getChildren().addValue(button);
      panel->getChildren().addValue(canvas);
      panel->setLayout(layout);
      panel->setBackgroundColor(Color4f(0.8,0.8,0.8,1.0));
   endEditCP  (panel, Panel::LayoutFieldMask | Panel::ChildrenFieldMask);

	//Create the UI Foreground Object
	UIForegroundPtr foreground = osg::UIForeground::create();

    beginEditCP(foreground, UIForeground::GraphicsFieldMask | UIForeground::RootComponentFieldMask);
		foreground->setGraphics(graphics);
		foreground->setRootComponent(panel);
    endEditCP  (foreground, UIForeground::GraphicsFieldMask | UIForeground::RootComponentFieldMask);

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
