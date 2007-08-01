// OpenSG Tutorial Example: Using the GridBag Layout
//		to place Components 
//
// This tutorial explains how to place buttons within a 
// frame utilizing the GridBag Layout command to 
// manage the layout through the OSG User Interface library.
//
// GridBagLayout is incredibly customizable with many more
// features than most Layouts
// 
// Includes: using GridBagLayout and GridBagLayoutConstraints

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
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>

// Include GridBagLayout and GridBayLayoutConstraints header files
#include <OpenSG/UserInterface/OSGGridBagLayout.h>
#include <OpenSG/UserInterface/OSGGridBagLayoutConstraints.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2s Size);

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    WindowPtr MainWindow;
    WindowEventProducerPtr TheWindowEventProducer;
    createDefaultWindow(Pnt2s(50,50),
                                        Vec2s(900,900),
                                        "OpenSG 19GridBagLayout Window",
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
	// settings for the Buttons
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


	/******************************************************

			Create GridBagLayout
			-setColumns(NUMBER) determines the number of
				Columns in the Layout, and then sets the
				correct number of weights in the MF
				ColumnWeights and the correct number of
				widths in the MF ColumnWidths. The default
				value for the weights sets their sum to 1.0
				(so they all have equal weight), and it
				fills ColumnWidths with 0s, which signals
				to use the weights instead of an absolute
				height.
			-setRows(NUMBER) determines the number of Rows
				in the Layout, then sets its corresponding
				MFs in the same fashion as its column
				counterpart.

			NOTE: If values have already been pushed onto
				any of the MFs, they will not be
				overwritten, the remaining spots will be
				filled. Also, when resetting the values
				to something lower than the previous 
				value, then the extra weights and lengths
				will be removed.

	******************************************************/
	GridBagLayoutPtr MainFrameLayout = osg::GridBagLayout::create();

		
	beginEditCP(MainFrameLayout, GridBagLayout::ColumnsFieldMask | GridBagLayout::RowsFieldMask);
		MainFrameLayout->setColumns(3);
		MainFrameLayout->setRows(3);
	endEditCP(MainFrameLayout); 

	
	/******************************************************

			Create GridBagLayoutConstraints for each 
			Button and edit	them.  GridBagLayoutConstraints
			are very versatile and there are many 
			options for locating Components.

			-setGridX(X_LOCATION) and setGridY(Y_LOCATION) 
				determine where the starting Grid space
				for the Constraints are, keeping in mind
				that 0,0 is the upper left corner
			-setGridHeight(HEIGHT) and setGridWidth(WIDTH)
				determine the number of Grid spaces that
				the Constraints' Component encompass
			-setFill(FILL_TYPE) determines the Fill categories.
				Options are:
				FILL_BOTH: Stretches both X/Y directions
				FILL_HORIZONTAL: Stretches X direction; Y dir
					remains untouched (so will display whatever
					is the PreferredSize Y value)
				FILL_VERTICAL: Stretches Y direction; X dir
					remains untouched (so will display whatever
					is the PreferredSize X value)
				FILL_NONE: Does not stretch either direction,
					Component displays at PreferredSize
			-setWeightX(PERCENT) and setWeightY(PERCENT) 
				determine the percent of the grid space
				in each respective direction that the Component
				occupies.  PERCENT in this case is a float 
				between 0.0 and 1.0. This is only used if the
				fill property is set for its direction, i.e.
				if you use setFill(FILL_VERTICAL), it will stretch
				by the weightY but not weightX.
			-setPadBottom/Top/Right/Left(AMOUNT) determines the
				padding	within the Grid space in each direction 
				in pixels
			-setInternalPadX(AMOUNT) and setInternalPadY(AMOUNT)
				will increase the minimum size that the component
				is set to. If the component is supposed to be drawn
				below its minSize + 2*internalPad, then it will
				be increased until then, unless it is too big to fit
				into the cell.
			-setHorizontalAlignment(PERCENT) and 
				setVerticalAlignment(PERCENT) determine the 
				alignment in both directions, based on a float 
				between 0.0 and 1.0, where 0.0 is the same as
				MIN_ALIGN and 0.5 will center it.




	******************************************************/
	GridBagLayoutConstraintsPtr button1Constraints = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr button2Constraints = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr button3Constraints = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr button4Constraints = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr button5Constraints = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr button6Constraints = osg::GridBagLayoutConstraints::create();

	beginEditCP(button1Constraints);
		button1Constraints->setGridX(0);
		button1Constraints->setGridY(0);
		button1Constraints->setGridHeight(2);
		button1Constraints->setGridWidth(1);
		button1Constraints->setFill(FILL_HORIZONTAL);
		button1Constraints->setWeightX(0.5);
		button1Constraints->setWeightY(0.5);
		button1Constraints->setPadBottom(0);
		button1Constraints->setPadLeft(0);
		button1Constraints->setPadRight(0);
		button1Constraints->setPadTop(0);
		button1Constraints->setInternalPadX(10);
		button1Constraints->setInternalPadY(10);
		button1Constraints->setHorizontalAlignment(0.75);
		button1Constraints->setVerticalAlignment(0.75);
	endEditCP(button1Constraints);
	
	beginEditCP(button2Constraints);
		button2Constraints->setGridX(1);
		button2Constraints->setGridY(1);
	endEditCP(button2Constraints);
	
	beginEditCP(button3Constraints);
		button3Constraints->setGridX(2);
		button3Constraints->setGridY(2);
	endEditCP(button3Constraints);
	
	beginEditCP(button4Constraints);
		button4Constraints->setGridX(2);
		button4Constraints->setGridY(1);
	endEditCP(button4Constraints);
	
	beginEditCP(button5Constraints);
		button5Constraints->setGridX(1);
		button5Constraints->setGridY(2);
	endEditCP(button5Constraints);
	
	beginEditCP(button6Constraints);
		button6Constraints->setGridX(0);
		button6Constraints->setGridY(2);
	endEditCP(button6Constraints);


	
	beginEditCP(button1, Button::TextFieldMask | Component::ConstraintsFieldMask);
		button1->setText("button1");
		button1->setConstraints(button1Constraints);
	endEditCP(button1, Button::TextFieldMask |  Component::ConstraintsFieldMask);

	beginEditCP(button2, Button::TextFieldMask | Component::ConstraintsFieldMask);
		button2->setText("button2");
		button2->setConstraints(button2Constraints);
	endEditCP(button2, Button::TextFieldMask |  Component::ConstraintsFieldMask);

	beginEditCP(button3, Button::TextFieldMask | Component::ConstraintsFieldMask);
		button3->setText("button3");
		button3->setConstraints(button3Constraints);
	endEditCP(button3, Button::TextFieldMask |  Component::ConstraintsFieldMask);

	beginEditCP(button4, Button::TextFieldMask | Component::ConstraintsFieldMask);
		button4->setText("button4");
		button4->setConstraints(button4Constraints);
	endEditCP(button4, Button::TextFieldMask |  Component::ConstraintsFieldMask);

	beginEditCP(button5, Button::TextFieldMask | Component::ConstraintsFieldMask);
		button5->setText("button5");
		button5->setConstraints(button5Constraints);
	endEditCP(button5, Button::TextFieldMask |  Component::ConstraintsFieldMask);
	
	beginEditCP(button6, Button::TextFieldMask | Component::ConstraintsFieldMask);
		button6->setText("button6");
		button6->setConstraints(button6Constraints);
	endEditCP(button6, Button::TextFieldMask |  Component::ConstraintsFieldMask);

 	// Create The Main Frame

	// Create Background to be used with the Main Frame
	ColorUIBackgroundPtr mainBackground = osg::ColorUIBackground::create();
	beginEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
		mainBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
	endEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
	
	FramePtr MainFrame = osg::Frame::create();
	beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);
	   // Add the buttons to the mainframe so they will be displayed
	   MainFrame->getChildren().addValue(button1);
	   MainFrame->getChildren().addValue(button2);
	   MainFrame->getChildren().addValue(button3);
	   MainFrame->getChildren().addValue(button4);
	   MainFrame->getChildren().addValue(button5);
	   MainFrame->getChildren().addValue(button6);
	   // Add the Layout to the MainFrame
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
