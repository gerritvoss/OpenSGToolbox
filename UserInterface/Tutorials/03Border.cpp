// OpenSG Tutorial Example: Creating a Border
//
// This tutorial explains how to implement the 
// Borders offered by the OSG User Interface 
// library and how to modify their features.
// 
// Includes: BevelBorder, CompoundBorder, EmptyBorder
// EtchedBorder, LineBorder, MatteBorder

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


// UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>

// Include Border header files
#include <OpenSG/UserInterface/OSGMatteBorder.h>
#include <OpenSG/UserInterface/OSGCompoundBorder.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGBevelBorder.h>
#include <OpenSG/UserInterface/OSGEtchedBorder.h>
#include <OpenSG/UserInterface/OSGEmptyBorder.h>
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


    // Make Torus Node
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

	// Initialize the LookAndFeelManager to enable default settings
	LookAndFeelManager::the()->getLookAndFeel()->init();

	/******************************************************

		Create Border components and assign
		each attribute to each Border.  Note
		that the LookAndFeelManager automatically
		assigns default settings to Borders.
		Each attribute will be set individually
		in this	tutorial.

	******************************************************/
	BevelBorderPtr bevelBorder = osg::BevelBorder::create();
	CompoundBorderPtr compoundBorder = osg::CompoundBorder::create();
	EtchedBorderPtr etchedBorder = osg::EtchedBorder::create();
	LineBorderPtr lineBorder = osg::LineBorder::create();
	MatteBorderPtr matteBorder = osg::MatteBorder::create();
	EmptyBorderPtr emptyBorder = osg::EmptyBorder::create();
	
	// Edit each Border Component and set all attributes
	
	// The BevelBorder causes the Button to appear raised or lowered
	beginEditCP(bevelBorder, BevelBorder::HighlightInnerFieldMask | BevelBorder::RaisedFieldMask | BevelBorder::HighlightOuterFieldMask);
		// Determines whether Button appears raised (true) or indented into screen (false)
		bevelBorder->setRaised(true);
		// Determines Width of Border
		bevelBorder->setWidth(5);
		// Determines the four colors involved in BevelBorder
		// The HighlightInner and HighlightOuter are the left and top
		// of the Border while setRaised(false) and the bottom and right 
		// while setRaised(true).  The ShadowInner and ShadowOuter are the 
		// opposite two sides.
		bevelBorder->setHighlightInner(Color4f(1.0, 1.0, 0.5, 1.0));
		bevelBorder->setHighlightOuter(Color4f(0.5, 0.5, 1.0, 1.0));
		bevelBorder->setShadowInner(Color4f(1.0, 0.5, 1.0, 1.0));
		bevelBorder->setShadowOuter(Color4f(0.5, 1.0, 1.0, 1.0));
	endEditCP(bevelBorder);

	// The CompoundBorder takes two Border Components and creates a single Border
	// out of the two Components.  It is possible to take use a CompoundBorder
	// within a CompoundBorder within a CompoundBorder... etc.
	beginEditCP(compoundBorder, CompoundBorder::InnerBorderFieldMask | CompoundBorder::OuterBorderFieldMask);
		// Determine the Inner and Outer Borders of the CompoundBorder
		compoundBorder->setInnerBorder(bevelBorder);
		compoundBorder->setOuterBorder(matteBorder);
	endEditCP(compoundBorder, CompoundBorder::InnerBorderFieldMask | CompoundBorder::OuterBorderFieldMask);
	
	// The EmptyBorder does not have a visible Border, however 
	// the Border still is a part of the Component with its 
	// assigned dimensions (note how this causes the Button
	// to appear spaced out from the other Buttons)
	beginEditCP(emptyBorder, EmptyBorder::LeftWidthFieldMask | EmptyBorder::TopWidthFieldMask | EmptyBorder::RightWidthFieldMask | EmptyBorder::BottomWidthFieldMask);
		// Determine the four Edge Widths
		emptyBorder->setBottomWidth(5);
		emptyBorder->setLeftWidth(5);
		emptyBorder->setRightWidth(30);
		emptyBorder->setTopWidth(30);
	endEditCP(emptyBorder, EmptyBorder::LeftWidthFieldMask | EmptyBorder::TopWidthFieldMask | EmptyBorder::RightWidthFieldMask | EmptyBorder::BottomWidthFieldMask);
	
	// The EtchedBorder causes the Button to appear raised
	// or indented into the screen similar to the BevelBorder
	// but in a different style
	beginEditCP(etchedBorder, EtchedBorder::WidthFieldMask | EtchedBorder::HighlightFieldMask | EtchedBorder::ShadowFieldMask | EtchedBorder::RaisedFieldMask);
		// Determine the Width of the Border
		etchedBorder->setWidth(3);
		// Determine Highlight and Shadow colors
		etchedBorder->setHighlight(Color4f(1.0, 1.0, 1.0, 1.0));
		etchedBorder->setShadow(Color4f(0.8, 0.8, 0.8, 1.0));
		// Determines if the Border appears raised (true) or indented (false)
		etchedBorder->setRaised(false);
	endEditCP(etchedBorder, EtchedBorder::WidthFieldMask | EtchedBorder::HighlightFieldMask | EtchedBorder::ShadowFieldMask | EtchedBorder::RaisedFieldMask);

	// The LineBorder is simply a line Border
	beginEditCP(lineBorder, LineBorder::WidthFieldMask | LineBorder::ColorFieldMask);
		// Determine Width
		lineBorder->setWidth(1);
		// Determine Color
		lineBorder->setColor(Color4f(.7, 0.0, .5, 1.0));
	endEditCP(lineBorder, LineBorder::WidthFieldMask | LineBorder::ColorFieldMask);
	
	// The MatteBorder creates a Border with dimensions
	// on all edges specified individually
	beginEditCP(matteBorder, MatteBorder::LeftWidthFieldMask | MatteBorder::RightWidthFieldMask | MatteBorder::BottomWidthFieldMask | MatteBorder::TopWidthFieldMask | MatteBorder::ColorFieldMask);
		// Determine the four Edge Widths
		matteBorder->setLeftWidth(3);
		matteBorder->setRightWidth(2);
		matteBorder->setBottomWidth(5);
		matteBorder->setTopWidth(1);
		// Determine Color
		matteBorder->setColor(Color4f(1.0, .5, .5, 1.0));
	endEditCP(matteBorder, MatteBorder::LeftWidthFieldMask | MatteBorder::RightWidthFieldMask | MatteBorder::BottomWidthFieldMask | MatteBorder::TopWidthFieldMask | MatteBorder::ColorFieldMask);


	
	/******************************************************

		Create Button components to display each 
		of the varying Borders.  Buttons will 
		be placed via the Flow layout.  The Preferred
		Size, Text, and Border will be edited for each
		Button.

	******************************************************/
	// Create Button components
	ButtonPtr bevelButton = osg::Button::create();
	ButtonPtr compoundButton = osg::Button::create();
	ButtonPtr emptyButton = osg::Button::create();
	ButtonPtr etchedButton = osg::Button::create();
	ButtonPtr lineButton = osg::Button::create();
	ButtonPtr matteButton = osg::Button::create();
	
	// Edit each Button Component and assign its Border via the
	// setBorder function
	beginEditCP(bevelButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);
		bevelButton->setPreferredSize(Vec2s(100,50));
		bevelButton->setText("Bevel Border");
		bevelButton->setBorder(bevelBorder);
	endEditCP  (bevelButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);
	
	beginEditCP(compoundButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);
		compoundButton->setPreferredSize(Vec2s(100,50));
		compoundButton->setText("Compound Border");
		compoundButton->setBorder(compoundBorder);
	endEditCP  (compoundButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);

	beginEditCP(emptyButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);
		emptyButton->setPreferredSize(Vec2s(100,50));
		emptyButton->setText("Empty Border");
		emptyButton->setBorder(emptyBorder);
	endEditCP  (emptyButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);
	
	beginEditCP(etchedButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);
		etchedButton->setPreferredSize(Vec2s(100,50));
		etchedButton->setText("Etched Border");
		etchedButton->setBorder(etchedBorder);
	endEditCP  (etchedButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);

	beginEditCP(lineButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);
		lineButton->setPreferredSize(Vec2s(100,50));
		lineButton->setText("Line Border");
		lineButton->setBorder(lineBorder);
	endEditCP  (lineButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);

	beginEditCP(matteButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);
		matteButton->setPreferredSize(Vec2s(100,50));
		matteButton->setText("Matte Border");
		matteButton->setBorder(matteBorder);
	endEditCP  (matteButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);


	
	// Create The Main Frame
	// Create Background to be used with the Main Frame
	ColorUIBackgroundPtr mainBackground = osg::ColorUIBackground::create();
	beginEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
		mainBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
	endEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
	FramePtr MainFrame = osg::Frame::create();
	LayoutPtr MainFrameLayout = osg::FlowLayout::create();
	beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);
	   MainFrame->getChildren().addValue(bevelButton);
	   MainFrame->getChildren().addValue(compoundButton);
	   MainFrame->getChildren().addValue(etchedButton);
	   MainFrame->getChildren().addValue(emptyButton);
	   MainFrame->getChildren().addValue(lineButton);
	   MainFrame->getChildren().addValue(matteButton);
	   MainFrame->setLayout(MainFrameLayout);
	   MainFrame->setBackground(mainBackground);
	endEditCP  (MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask| Frame::BackgroundFieldMask);

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
    
    int winid = glutCreateWindow("OpenSG UserInterface Button");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    return winid;
}
