// OpenSG Tutorial Example: Using Containers (Frames and Panels)
//
// This tutorial explains how use Frame and Panel Containers
// 
// Includes: creating and editing Frames, Panels, and adding
// Panels


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
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>

// Include relevant header files
#include <OpenSG/UserInterface/OSGAbsoluteLayout.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGBoxLayout.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGContainer.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGBevelBorder.h>
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


    // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Main Scene Node
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        scene->setCore(osg::Group::create());
 
        // add the torus as a child
        //scene->addChild(TorusGeometryNode);
    }
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

	// Create the Graphics
	GraphicsPtr graphics = osg::Graphics2D::create();

	// Initialize the LookAndFeelManager to enable default 
	// settings for the Button
	LookAndFeelManager::the()->getLookAndFeel()->init();


	/******************************************************
			
				Creates some Button components

	******************************************************/

	ButtonPtr button1 = osg::Button::create();
	ButtonPtr button2 = osg::Button::create();
	ButtonPtr button3 = osg::Button::create();
	ButtonPtr button4 = osg::Button::create();
	ButtonPtr button5 = osg::Button::create();
	ButtonPtr button6 = osg::Button::create();

	beginEditCP(button1);
		button1->setText("This");
	endEditCP(button1);

	beginEditCP(button2);
		button2->setText("is a");
	endEditCP(button2);

	beginEditCP(button3);
		button3->setText("sample");
	endEditCP(button3);

	beginEditCP(button4);
	button4->setText("two");
	endEditCP(button4);

	beginEditCP(button5);
		button5->setText("panel");
	endEditCP(button5);

	beginEditCP(button6);
		button6->setText("layout");
	endEditCP(button6);
	/******************************************************

			Create some Flow Layouts to be used
			with the Main Frame and the two 
			Panels

	******************************************************/
	BoxLayoutPtr MainFrameLayout = osg::BoxLayout::create();
	BoxLayoutPtr panel1Layout = osg::BoxLayout::create();
	BoxLayoutPtr panel2Layout = osg::BoxLayout::create();

	beginEditCP(panel1Layout, BoxLayout::AlignmentFieldMask);
		panel1Layout->setAlignment(VERTICAL_ALIGNMENT);
	endEditCP(panel1Layout, BoxLayout::AlignmentFieldMask);
	beginEditCP(panel2Layout, BoxLayout::AlignmentFieldMask);
		panel2Layout->setAlignment(VERTICAL_ALIGNMENT);
	endEditCP(panel2Layout, BoxLayout::AlignmentFieldMask);
	beginEditCP(MainFrameLayout, BoxLayout::AlignmentFieldMask);
		MainFrameLayout->setAlignment(HORIZONTAL_ALIGNMENT);
	endEditCP(MainFrameLayout, BoxLayout::AlignmentFieldMask);

	/******************************************************
			
			Create two Backgrounds to be used with
			Panels and MainFrame

	******************************************************/
	ColorUIBackgroundPtr mainBackground = osg::ColorUIBackground::create();
	ColorUIBackgroundPtr panelBackground = osg::ColorUIBackground::create();
	beginEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
		mainBackground->setColor(Color4f(0,0,1.0,0.5));
	endEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
	beginEditCP(panelBackground, ColorUIBackground::ColorFieldMask);
		panelBackground->setColor(Color4f(0.0,0.0,0.0,1.0));
	endEditCP(panelBackground, ColorUIBackground::ColorFieldMask);
	
	/******************************************************
			
			Create a Border to be used with
			the two Panels

	******************************************************/
	LineBorderPtr panelBorder = osg::LineBorder::create();
	beginEditCP(panelBorder, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);
		panelBorder->setColor( Color4f(0.9, 0.9, 0.9, 1.0) );
		panelBorder->setWidth(3);
	endEditCP(panelBorder, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);


	/******************************************************

		Create MainFrame and two Panel Components and
		edit their characteristics: 
		-PreferredSize changes their size
		-getChildren adds Components to the Panel or
		Frame (you can add Panels or Frames to other
		Panels and Frames)
		-setLayout determines the Layout of the Panel/
		Frame (each Frame and Panel can have its own 
		Layout, even within another Frame/Panel)


	******************************************************/
	FramePtr MainFrame = osg::Frame::create();
	PanelPtr panel1 = osg::Panel::create();
	PanelPtr panel2 = osg::Panel::create();
	
	// Edit Panel1, Panel2
	beginEditCP(panel1, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundFieldMask | Panel::BorderFieldMask);
		panel1->setPreferredSize( Vec2s(200, 200) );
		panel1->getChildren().addValue(button1);
		panel1->getChildren().addValue(button2);
		panel1->getChildren().addValue(button3);
		panel1->setLayout(panel1Layout);
		panel1->setBackground(panelBackground);
		panel1->setBorder(panelBorder);
	endEditCP(panel1, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundFieldMask | Panel::BorderFieldMask);

	beginEditCP(panel2, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundFieldMask | Panel::BorderFieldMask);
		panel2->setPreferredSize( Vec2s(200, 200) );
		panel2->getChildren().addValue(button4);
		panel2->getChildren().addValue(button5);
		panel2->getChildren().addValue(button6);
		panel2->setLayout(panel2Layout);
		panel2->setBackground(panelBackground);
		panel2->setBorder(panelBorder);
	endEditCP(panel2, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundFieldMask | Panel::BorderFieldMask);

	// Edit MainFrame
	beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);
	   MainFrame->getChildren().addValue(panel1);
	   MainFrame->getChildren().addValue(panel2);
	   MainFrame->setLayout(MainFrameLayout);
	   MainFrame->setBackground(mainBackground);
	endEditCP  (MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);

	//Create the Drawing Surface
	UIDrawingSurfacePtr drawingSurface = UIDrawingSurface::create();
	beginEditCP(drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask);
		drawingSurface->setGraphics(graphics);
		drawingSurface->setRootFrame(MainFrame);
	    //drawingSurface->setEventProducer(TheWindowEventProducer);
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
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);

	// Add the UI Foreground Object to the Scene
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
    
    int winid = glutCreateWindow("OpenSG UserInterface Example");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    return winid;
}
