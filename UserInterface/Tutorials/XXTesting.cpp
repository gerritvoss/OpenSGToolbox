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
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayout.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGGradientUIBackground.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>

#include <OpenSG/UserInterface/OSGImageComponent.h>
#include <OpenSG/UserInterface/OSGUIDefines.h>

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
	AbsoluteLayoutConstraintsPtr buttonLayoutConstraints = osg::AbsoluteLayoutConstraints::create();
    beginEditCP(buttonLayoutConstraints, AbsoluteLayoutConstraints::PositionFieldMask);
		buttonLayoutConstraints->setPosition( Pnt2s(0,0) );
    endEditCP  (buttonLayoutConstraints, AbsoluteLayoutConstraints::PositionFieldMask);

	//Create Gradient Background
	GradientUIBackgroundPtr gradientUIBackground = osg::GradientUIBackground::create();
    beginEditCP(gradientUIBackground);
		gradientUIBackground->setAlignment(VERTICAL_ALIGNMENT);
		gradientUIBackground->setColorStart(Color4f(0.0,1.0,1.0,1.0));
		gradientUIBackground->setColorEnd(Color4f(1.0,0.0,0.0,1.0));
    endEditCP(gradientUIBackground);


    beginEditCP(button, Button::TextFieldMask);
		button->setText("Button 1");
		button->setConstraints(buttonLayoutConstraints);
		button->setBackground(gradientUIBackground);
    endEditCP  (button, Button::TextFieldMask);
	
	//Create A Label Component
	LabelPtr label = osg::Label::create();
	AbsoluteLayoutConstraintsPtr labelLayoutConstraints = osg::AbsoluteLayoutConstraints::create();
    beginEditCP(labelLayoutConstraints, AbsoluteLayoutConstraints::PositionFieldMask);
		labelLayoutConstraints->setPosition( Pnt2s(0,100) );
    endEditCP  (labelLayoutConstraints, AbsoluteLayoutConstraints::PositionFieldMask);

	beginEditCP(label, Label::TextFieldMask | Label::ConstraintsFieldMask);
		label->setText("Label 1");
		label->setConstraints(labelLayoutConstraints);
    endEditCP  (label, Label::TextFieldMask | Label::ConstraintsFieldMask);

	
	//Create Image Component
	ImageComponentPtr imageComponent = osg::ImageComponent::create();
	imageComponent->setImage("Data/Checker.jpg");
	beginEditCP(imageComponent, ImageComponent::ScaleFieldMask | ImageComponent::PreferredSizeFieldMask);
		imageComponent->setPreferredSize(Vec2s(10,10));
		imageComponent->setScale(SCALE_NONE);
    endEditCP  (imageComponent, ImageComponent::ScaleFieldMask | ImageComponent::PreferredSizeFieldMask);

	//Create The Main Frame
	FramePtr MainFrame = osg::Frame::create();
	LayoutPtr MainFrameLayout = osg::AbsoluteLayout::create();
   beginEditCP(MainFrame, Panel::LayoutFieldMask | Panel::ChildrenFieldMask);
      MainFrame->getChildren().addValue(imageComponent);
      //MainFrame->getChildren().addValue(button);
      //MainFrame->getChildren().addValue(label);
      MainFrame->setLayout(MainFrameLayout);
   endEditCP  (MainFrame, Panel::LayoutFieldMask | Panel::ChildrenFieldMask);

	//Create the UI Foreground Object
	UIForegroundPtr foreground = osg::UIForeground::create();

    beginEditCP(foreground, UIForeground::GraphicsFieldMask | UIForeground::RootFrameFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
		foreground->setGraphics(graphics);
		foreground->setRootFrame(MainFrame);
		foreground->setFramePositionOffset(Vec2s(0,0));
		foreground->setFrameBounds(Vec2f(0.5,0.5));
    endEditCP(foreground, UIForeground::GraphicsFieldMask | UIForeground::RootFrameFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
	
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
