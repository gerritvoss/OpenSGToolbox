// OpenSG Tutorial Example: Creating a Button
//
// This tutorial explains how to implement the 
// backgrounds offered by the OSG User Interface 
// library and how to modify their features.
// 
// Includes: explanations and examples of how to create
// and use the six different backgrounds included in the
// OSG User Interface library.

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
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>

// Include UIDefines- used for HORITONAL_ALIGNMENT and VERTICAL_ALIGNMENT
#include <OpenSG/UserInterface/OSGUIDefines.h>

// Include UIBackground header files
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
#include <OpenSG/UserInterface/OSGCompoundUIBackground.h>
#include <OpenSG/UserInterface/OSGEmptyUIBackground.h>
#include <OpenSG/UserInterface/OSGGradientUIBackground.h>
#include <OpenSG/UserInterface/OSGMaterialUIBackground.h>
#include <OpenSG/UserInterface/OSGTextureUIBackground.h>


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


    //Make Main Scene Node
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

					Creates 
   					the 
					different
					backgrounds

	******************************************************/

	// Creates a ColorUIBackgroundPtr (colorBackground)
	ColorUIBackgroundPtr colorBackground = osg::ColorUIBackground::create();

	// Creates a CompoundUIBackgroundPtr (compoundBackground)
	CompoundUIBackgroundPtr compoundBackground = osg::CompoundUIBackground::create();
	
	// Creates an EmptyUIBackgroundPtr (emptyBackground)
	EmptyUIBackgroundPtr emptyBackground = osg::EmptyUIBackground::create();

	// Create a GradientUIBackgroundPtr (gradientBackground)
	GradientUIBackgroundPtr gradientBackground = osg::GradientUIBackground::create();
	
	// Create a MaterialUIBackgroundPtr (materialBackground)
	MaterialUIBackgroundPtr materialBackground = osg::MaterialUIBackground::create();

	// Create a TextureUIBackgroundPtr (textureBackground)
	TextureUIBackgroundPtr textureBackground = osg::TextureUIBackground::create();

	/******************************************************

				Define the backgrounds
				Every single option for each background
				type will be shown and set

	******************************************************/


	// Set colorBackground- set color
	beginEditCP(colorBackground, ColorUIBackground::ColorFieldMask);
		colorBackground->setColor(Color4f(1.0,0.0,0.0,1.0));
	endEditCP(colorBackground, ColorUIBackground::ColorFieldMask);

	// Set compoundBackground
	beginEditCP(compoundBackground);

	endEditCP(compoundBackground);

	// Set emptyBackground (note that empty background is just that,
	// a background with no attributes
	beginEditCP(emptyBackground);
	endEditCP(emptyBackground);

	// Set gradientBackground- Set initial color, end color,
	// and orientation of gradient
	beginEditCP(gradientBackground, GradientUIBackground::ColorStartFieldMask | GradientUIBackground::ColorEndFieldMask | GradientUIBackground::AlignmentFieldMask);
		 gradientBackground->setColorStart( Color4f(1.0, 0.0, 0.0, 1.0));
		 gradientBackground->setColorEnd( Color4f(0.0, 0.0, 1.0, 1.0));
		 // The input into the following call is either
		 // HORIZONTAL_ALIGNMENT or VERTICAL_ALIGNMENT,
		 // which orient the gradient in the obvious manner 
		 gradientBackground->setAlignment(HORIZONTAL_ALIGNMENT);
	endEditCP(gradientBackground, GradientUIBackground::ColorStartFieldMask | GradientUIBackground::ColorEndFieldMask | GradientUIBackground::AlignmentFieldMask);
	// Set materialBackground- Set material
	beginEditCP(materialBackground);
		// materialBackground->setMaterial(MATERIAL_NAME);
	endEditCP(materialBackground);

	// Set textureBackground- set texture
	beginEditCP(textureBackground);
		// textureBackground->setTexture(TEXTURE_NAME);
	endEditCP(textureBackground);


	// Create and define simple line border to be used on Buttons
	LineBorderPtr lineBorder = osg::LineBorder::create();
	beginEditCP(lineBorder, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);
		lineBorder->setColor( Color4f(0.0, 0.0, 0.0, 1.0) );
		lineBorder->setWidth( 1 );
	endEditCP(lineBorder, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);
	
	/******************************************************

		Create Button components to display each 
		of the varying backgrounds.  Buttons will 
		be placed via the Flow layout.

	******************************************************/
	ButtonPtr buttonColor = osg::Button::create();
	ButtonPtr buttonCompound = osg::Button::create();
	ButtonPtr buttonEmpty = osg::Button::create();
	ButtonPtr buttonGradient = osg::Button::create();	
	ButtonPtr buttonMaterial = osg::Button::create();
	ButtonPtr buttonTexture = osg::Button::create();
	
	// Set the visible text, border, and Background for
	// each of the various Button components
	beginEditCP(buttonColor, Button::TextFieldMask | Button::BackgroundFieldMask | Button::BorderFieldMask);
		buttonColor->setText("Color Background");
		buttonColor->setBackground(colorBackground);
		buttonColor->setBorder(lineBorder);
    endEditCP(buttonColor, Button::TextFieldMask | Button::BackgroundFieldMask | Button::BorderFieldMask);

	beginEditCP(buttonCompound, Button::TextFieldMask | Button::BackgroundFieldMask | Button::PreferredSizeFieldMask |Button::BorderFieldMask);
		buttonCompound->setText("Compound Background");
		buttonCompound->setBackground(compoundBackground);
		buttonCompound->setPreferredSize(Vec2s(150,50));
		buttonCompound->setBorder(lineBorder);
		endEditCP(buttonCompound, Button::TextFieldMask | Button::BackgroundFieldMask | Button::PreferredSizeFieldMask |Button::BorderFieldMask);

	beginEditCP(buttonEmpty, Button::TextFieldMask | Button::BackgroundFieldMask | Button::BorderFieldMask);
		buttonEmpty->setText("Empty Background");
		buttonEmpty->setBackground(emptyBackground);
		buttonEmpty->setBorder(lineBorder);
	endEditCP(buttonEmpty, Button::TextFieldMask | Button::BackgroundFieldMask | Button::BorderFieldMask);

	beginEditCP(buttonGradient, Button::TextFieldMask | Button::BackgroundFieldMask | Button::PreferredSizeFieldMask |Button::BorderFieldMask);
		buttonGradient->setText("Gradient Background");
		buttonGradient->setBackground(gradientBackground);
		buttonGradient->setPreferredSize(Vec2s(150,50));
		buttonGradient->setBorder(lineBorder);
    endEditCP(buttonGradient, Button::TextFieldMask | Button::BackgroundFieldMask | Button::PreferredSizeFieldMask |Button::BorderFieldMask);
	
	// add material and texture buttons at some point



	// This creates a background for the MainFrame so that 
	// the button backgrounds are easier to see. The process
	// is identical, except the background is added to the 
	// MainFrame instead of a Button.
	// The background is a semi-transparent white background.
	ColorUIBackgroundPtr mainBackground = osg::ColorUIBackground::create();
	beginEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
		mainBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
	endEditCP(mainBackground, ColorUIBackground::ColorFieldMask);



	// Create The Main Frame
	FramePtr MainFrame = osg::Frame::create();
	LayoutPtr MainFrameLayout = osg::FlowLayout::create();
	beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);
	   // Assign the button to the mainframe so it will be displayed
	   // when the view is rendered.
	   MainFrame->getChildren().addValue(buttonColor);
	   MainFrame->getChildren().addValue(buttonCompound);
	   MainFrame->getChildren().addValue(buttonEmpty);
	   MainFrame->getChildren().addValue(buttonGradient);
	   MainFrame->setLayout(MainFrameLayout);
	   MainFrame->setBackground(mainBackground);
	endEditCP  (MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);

	// Create the UI Foreground Object
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
