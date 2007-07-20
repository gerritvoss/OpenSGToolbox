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

//Input
#include <OpenSG/Input/OSGWindowUtils.h>

//UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>


// Include relevant header files
#include <OpenSG/UserInterface/OSGAbsoluteLayout.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGBoxLayout.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGContainer.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGFrame.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGEmptyBorder.h>
#include <OpenSG/UserInterface/OSGEtchedBorder.h>
#include <OpenSG/UserInterface/OSGUIDefines.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
#include <OpenSG/UserInterface/OSGGradientUIBackground.h>
#include <OpenSG/UserInterface/OSGCompoundUIBackground.h>

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
    
    WindowPtr MainWindow;
    WindowEventProducerPtr TheWindowEventProducer;
    createDefaultWindow(Pnt2s(50,50),
                                        Vec2s(900,900),
                                        "OpenSG 01Button Window",
                                        MainWindow,
                                        TheWindowEventProducer);
    
    TheWindowEventProducer->setDisplayCallback(display);
    TheWindowEventProducer->setReshapeCallback(reshape);

    //Attach Mouse Listener
    //TheWindowEventProducer->addMouseListener(new TutorialMouseListener());
    //Attach Mouse Wheel Listener
    //TheWindowEventProducer->addMouseWheelListener(new TutorialMouseWheelListener());
    //Attach Key Listener
    //TheWindowEventProducer->addKeyListener(new TutorialKeyListener());
    //Attach Window Listener
    //TheWindowEventProducer->addWindowListener(new TutorialWindowListener());




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
	// settings for the Button
	LookAndFeelManager::the()->getLookAndFeel()->init();

	
	/******************************************************
			
			Create some Backgrounds

	******************************************************/
	ColorUIBackgroundPtr mainBackground = osg::ColorUIBackground::create();
	ColorUIBackgroundPtr panelBackground = osg::ColorUIBackground::create();
	ColorUIBackgroundPtr button1Color = osg::ColorUIBackground::create();
	GradientUIBackgroundPtr button1Gradient = osg::GradientUIBackground::create();
	CompoundUIBackgroundPtr button1Compound = osg::CompoundUIBackground::create();
	
	beginEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
		mainBackground->setColor(Color4f(0,0,1.0,0.5));
	endEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
	beginEditCP(panelBackground, ColorUIBackground::ColorFieldMask);
		panelBackground->setColor(Color4f(0.0,0.0,0.0,0.5));
	endEditCP(panelBackground, ColorUIBackground::ColorFieldMask);
	
	// button1 Backgrounds
	beginEditCP(button1Color, ColorUIBackground::ColorFieldMask);
		button1Color->setColor( Color4f(0.0, 0.0, 0.0, 1.0) );
	endEditCP(button1Color, ColorUIBackground::ColorFieldMask);
	beginEditCP(button1Gradient);
		button1Gradient->setColorStart( Color4f(1.0, 0.0, 1.0, 0.8) );
		button1Gradient->setColorEnd( Color4f(0.0, 0.0, 1.0, 0.3) );
		button1Gradient->setAlignment(HORIZONTAL_ALIGNMENT);
	endEditCP(button1Gradient);
	beginEditCP(button1Compound);
		button1Compound->getBackgrounds().addValue(button1Color);
		button1Compound->getBackgrounds().addValue(button1Gradient);
	endEditCP(button1Compound);

	/******************************************************
			
			Create some Borders

	******************************************************/
	EtchedBorderPtr panelBorder = osg::EtchedBorder::create();
	EmptyBorderPtr button1Border = osg::EmptyBorder::create();
	beginEditCP(panelBorder, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);
		panelBorder->setHighlight(Color4f(1.0, 1.0, 1.0, 1.0));
		panelBorder->setShadow(Color4f(0.8, 0.8, 0.8, 1.0));
		panelBorder->setWidth(6);
	endEditCP(panelBorder, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);

	/******************************************************
			
				Creates some Button components

	******************************************************/

	ButtonPtr button1 = osg::Button::create();
	ButtonPtr button2 = osg::Button::create();
	ButtonPtr button3 = osg::Button::create();
	ButtonPtr button4 = osg::Button::create();
	ButtonPtr button5 = osg::Button::create();
	ButtonPtr button6 = osg::Button::create();
	ButtonPtr button7 = osg::Button::create();
	ButtonPtr button8 = osg::Button::create();
	ButtonPtr button9 = osg::Button::create();
	ButtonPtr button10 = osg::Button::create();
	ButtonPtr button11 = osg::Button::create();
	ButtonPtr button12 = osg::Button::create();
	ButtonPtr button13 = osg::Button::create();
	ButtonPtr button14 = osg::Button::create();
	ButtonPtr button15 = osg::Button::create();

	beginEditCP(button1, Component::PreferredSizeFieldMask | Component::BackgroundFieldMask | Component::BorderFieldMask);
		button1->setPreferredSize( Vec2s(800, 50) );
		button1->setBackground(button1Compound);
		button1->setBorder(button1Border);
	endEditCP(button1, Component::PreferredSizeFieldMask | Component::BackgroundFieldMask | Component::BorderFieldMask);

	beginEditCP(button2, Component::PreferredSizeFieldMask | Component::MaxSizeFieldMask | Button::TextFieldMask);
		button2->setPreferredSize( Vec2s(50, 50) );
		button2->setMaxSize( Vec2s(50, 50) );
	endEditCP(button2, Component::PreferredSizeFieldMask | Component::MaxSizeFieldMask | Button::TextFieldMask);
	
	beginEditCP(button3, Component::PreferredSizeFieldMask | Component::MaxSizeFieldMask | Button::TextFieldMask);
		button3->setPreferredSize( Vec2s(50, 50) );
		button3->setMaxSize( Vec2s(50, 50) );
	endEditCP(button3, Component::PreferredSizeFieldMask | Component::MaxSizeFieldMask | Button::TextFieldMask);

	beginEditCP(button4, Component::PreferredSizeFieldMask | Component::MaxSizeFieldMask | Button::TextFieldMask);
		button4->setPreferredSize( Vec2s(50, 50) );
		button4->setMaxSize( Vec2s(50, 50) );
	endEditCP(button4, Component::PreferredSizeFieldMask | Component::MaxSizeFieldMask | Button::TextFieldMask);

	beginEditCP(button5, Component::PreferredSizeFieldMask | Component::MaxSizeFieldMask | Button::TextFieldMask);
		button5->setPreferredSize( Vec2s(50, 50) );
		button5->setMaxSize( Vec2s(50, 50) );
	endEditCP(button5, Component::PreferredSizeFieldMask | Component::MaxSizeFieldMask | Button::TextFieldMask);

	beginEditCP(button6, Component::PreferredSizeFieldMask | Component::MaxSizeFieldMask | Button::TextFieldMask);
		button6->setPreferredSize( Vec2s(50, 50) );
		button6->setMaxSize( Vec2s(50, 50) );
	endEditCP(button6, Component::PreferredSizeFieldMask | Component::MaxSizeFieldMask | Button::TextFieldMask);

	beginEditCP(button7, Component::PreferredSizeFieldMask | Component::MaxSizeFieldMask | Button::TextFieldMask);
		button7->setPreferredSize( Vec2s(50, 50) );
		button7->setMaxSize( Vec2s(50, 50) );
	endEditCP(button7, Component::PreferredSizeFieldMask | Component::MaxSizeFieldMask | Button::TextFieldMask);

	beginEditCP(button8, Component::PreferredSizeFieldMask | Component::MaxSizeFieldMask | Button::TextFieldMask);
		button8->setPreferredSize( Vec2s(50, 50) );
		button8->setMaxSize( Vec2s(50, 50) );
	endEditCP(button8, Component::PreferredSizeFieldMask | Component::MaxSizeFieldMask | Button::TextFieldMask);

	beginEditCP(button9, Component::PreferredSizeFieldMask | Component::MaxSizeFieldMask | Button::TextFieldMask);
		button9->setPreferredSize( Vec2s(50, 50) );
		button9->setMaxSize( Vec2s(50, 50) );
	endEditCP(button9, Component::PreferredSizeFieldMask | Component::MaxSizeFieldMask | Button::TextFieldMask);


	/******************************************************

			Create some Layouts

	******************************************************/
	FlowLayoutPtr MainFrameLayout = osg::FlowLayout::create();
	BoxLayoutPtr panel1Layout = osg::BoxLayout::create();
	BoxLayoutPtr panel2Layout = osg::BoxLayout::create();
	BoxLayoutPtr panel3Layout = osg::BoxLayout::create();
	BoxLayoutPtr panel4Layout = osg::BoxLayout::create();
	BoxLayoutPtr panel5Layout = osg::BoxLayout::create();
	BoxLayoutPtr panel6Layout = osg::BoxLayout::create();

	beginEditCP(panel1Layout, BoxLayout::AlignmentFieldMask);
		panel1Layout->setAlignment(VERTICAL_ALIGNMENT);
	endEditCP(panel1Layout, BoxLayout::AlignmentFieldMask);

	beginEditCP(panel2Layout, BoxLayout::AlignmentFieldMask);
		panel2Layout->setAlignment(VERTICAL_ALIGNMENT);
	endEditCP(panel2Layout, BoxLayout::AlignmentFieldMask);

	beginEditCP(panel3Layout, BoxLayout::AlignmentFieldMask);
		panel3Layout->setAlignment(VERTICAL_ALIGNMENT);
	endEditCP(panel3Layout, BoxLayout::AlignmentFieldMask);

	beginEditCP(panel4Layout, BoxLayout::AlignmentFieldMask);
		panel4Layout->setAlignment(VERTICAL_ALIGNMENT);
	endEditCP(panel4Layout, BoxLayout::AlignmentFieldMask);

	beginEditCP(panel5Layout, BoxLayout::AlignmentFieldMask);
		panel5Layout->setAlignment(VERTICAL_ALIGNMENT);
	endEditCP(panel5Layout, BoxLayout::AlignmentFieldMask);

	beginEditCP(panel6Layout, BoxLayout::AlignmentFieldMask);
		panel6Layout->setAlignment(VERTICAL_ALIGNMENT);
	endEditCP(panel6Layout, BoxLayout::AlignmentFieldMask);

	beginEditCP(MainFrameLayout, FlowLayout::AlignmentFieldMask | FlowLayout::MinorAxisAlignmentFieldMask);
		MainFrameLayout->setAlignment(HORIZONTAL_ALIGNMENT);
		MainFrameLayout->setMinorAxisAlignment(AXIS_CENTER_ALIGNMENT);
	endEditCP(MainFrameLayout, FlowLayout::AlignmentFieldMask | FlowLayout::MinorAxisAlignmentFieldMask);



	/******************************************************

		Create MainFrame and some Panels


	******************************************************/
	FramePtr MainFrame = osg::Frame::create();
	PanelPtr panel1 = osg::Panel::create();
	PanelPtr panel2 = osg::Panel::create();
	PanelPtr panel3 = osg::Panel::create();
	PanelPtr panel4 = osg::Panel::create();
	PanelPtr panel5 = osg::Panel::create();
	PanelPtr panel6 = osg::Panel::create();

	
	// Edit Panel1, Panel2
	beginEditCP(panel1, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundFieldMask | Panel::BorderFieldMask);
		panel1->setPreferredSize( Vec2s(400, 400) );
		panel1->getChildren().addValue(button2);
		panel1->getChildren().addValue(panel3);
		panel1->getChildren().addValue(panel4);
		panel1->setLayout(panel1Layout);
		panel1->setBackground(panelBackground);
		panel1->setBorder(panelBorder);
	endEditCP(panel1, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundFieldMask | Panel::BorderFieldMask);

	beginEditCP(panel2, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundFieldMask | Panel::BorderFieldMask);
		panel2->setPreferredSize( Vec2s(400, 400) );
		panel2->getChildren().addValue(button3);
		panel2->getChildren().addValue(panel5);
		panel2->getChildren().addValue(panel6);
		panel2->setLayout(panel2Layout);
		panel2->setBackground(panelBackground);
		panel2->setBorder(panelBorder);
	endEditCP(panel2, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundFieldMask | Panel::BorderFieldMask);
	
	beginEditCP(panel3);
		panel3->getChildren().addValue(button4);
		panel3->getChildren().addValue(button5);
		panel3->setLayout(panel3Layout);
		panel3->setPreferredSize( Vec2s(75, 130) );
	endEditCP(panel3);


	// Edit MainFrame
	beginEditCP(MainFrame, Frame::BorderFieldMask | Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);
	   MainFrame->setBorder(panelBorder);
	   MainFrame->getChildren().addValue(button1);
	   MainFrame->getChildren().addValue(panel1);
	   MainFrame->getChildren().addValue(panel2);
	   MainFrame->setLayout(MainFrameLayout);
	   MainFrame->setBackground(mainBackground);
	endEditCP  (MainFrame, Frame::BorderFieldMask | Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);

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
		foreground->setFrameBounds(Vec2f(0.8,0.8));
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
