// OpenSG Tutorial Example: Creating a Border
//
// This tutorial explains how to implement the 
// Borders offered by the OSG User Interface 
// library and how to modify their features.
//
// Note the difference when clicking on matteButton
// as compared with the other Buttons.
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
#include <OpenSG/Input/OSGWindowAdapter.h>

// The general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

// Input
#include <OpenSG/Input/OSGWindowUtils.h>


// UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

bool ExitApp = false;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2s Size);

// Include Border header files
#include <OpenSG/UserInterface/OSGBorders.h>
#include <OpenSG/UserInterface/OSGUIBackgrounds.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>


class TutorialWindowListener : public WindowAdapter
{
public:
    virtual void windowClosing(const WindowEvent& e)
    {
        ExitApp = true;
    }

    virtual void windowClosed(const WindowEvent& e)
    {
        ExitApp = true;
    }
};

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    WindowEventProducerPtr TheWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TheWindowEventProducer->initWindow();
    
    TheWindowEventProducer->setDisplayCallback(display);
    TheWindowEventProducer->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TheWindowEventProducer->addWindowListener(&TheTutorialWindowListener);


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
	MultiColorMatteBorderPtr multiColorMatteBorder = osg::MultiColorMatteBorder::create();
	RoundedCornerLineBorderPtr roundedCornerLineBorder = osg::RoundedCornerLineBorder::create();
	ShadowBorderPtr shadowBorder = osg::ShadowBorder::create();
	
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
		// Determine the Width of the Border (note EtchedBorder works best
		// with a Width which is a multiple of 2)
		etchedBorder->setWidth(4);
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

	// The MatteBorder creates a Border with dimensions
	beginEditCP(multiColorMatteBorder);
		// Determine the four Edge Widths
		multiColorMatteBorder->setLeftWidth(10);
		multiColorMatteBorder->setLeftLineTopColor(Color4f(1.0,0.0,0.0,1.0));
		multiColorMatteBorder->setLeftLineBottomColor(Color4f(1.0,1.0,1.0,1.0));
		multiColorMatteBorder->setRightWidth(10);
		multiColorMatteBorder->setRightLineTopColor(Color4f(0.0,1.0,0.0,1.0));
		multiColorMatteBorder->setRightLineBottomColor(Color4f(0.0,0.0,1.0,1.0));
		multiColorMatteBorder->setBottomWidth(10);
		multiColorMatteBorder->setBottomLineLeftColor(Color4f(1.0,1.0,1.0,1.0));
		multiColorMatteBorder->setBottomLineRightColor(Color4f(0.0,0.0,1.0,1.0));
		multiColorMatteBorder->setTopWidth(10);
		multiColorMatteBorder->setTopLineLeftColor(Color4f(1.0,0.0,0.0,1.0));
		multiColorMatteBorder->setTopLineRightColor(Color4f(0.0,1.0,0.0,1.0));
	endEditCP(multiColorMatteBorder);
	
	// The RoundedCornerLineBorder
    beginEditCP(roundedCornerLineBorder, RoundedCornerLineBorder::WidthFieldMask | RoundedCornerLineBorder::ColorFieldMask | RoundedCornerLineBorder::CornerRadiusFieldMask );
		roundedCornerLineBorder->setWidth(2);
		roundedCornerLineBorder->setColor(Color4f(1.0, 0.5, 0.5, 1.0));
		roundedCornerLineBorder->setCornerRadius(15);
	endEditCP(roundedCornerLineBorder, RoundedCornerLineBorder::WidthFieldMask | RoundedCornerLineBorder::ColorFieldMask | RoundedCornerLineBorder::CornerRadiusFieldMask);
    
	// The ShadowBorder
    beginEditCP(shadowBorder, ShadowBorder::TopOffsetFieldMask | ShadowBorder::BottomOffsetFieldMask | ShadowBorder::LeftOffsetFieldMask | ShadowBorder::RightOffsetFieldMask | ShadowBorder::InternalColorFieldMask| ShadowBorder::EdgeColorFieldMask | ShadowBorder::InsideBorderFieldMask | ShadowBorder::CornerRadiusFieldMask | ShadowBorder::InternalToEdgeColorLengthFieldMask );
		shadowBorder->setTopOffset(0);
		shadowBorder->setBottomOffset(5);
		shadowBorder->setLeftOffset(0);
		shadowBorder->setRightOffset(5);
		shadowBorder->setInsideBorder(roundedCornerLineBorder);
		shadowBorder->setCornerRadius(15);
		shadowBorder->setInternalColor(Color4f(0.0, 0.0, 0.0, 0.5));
		shadowBorder->setEdgeColor(Color4f(0.0, 0.0, 0.0, 0.0));
		shadowBorder->setInternalToEdgeColorLength(5);
	endEditCP(shadowBorder, ShadowBorder::TopOffsetFieldMask | ShadowBorder::BottomOffsetFieldMask | ShadowBorder::LeftOffsetFieldMask | ShadowBorder::RightOffsetFieldMask | ShadowBorder::InternalColorFieldMask| ShadowBorder::EdgeColorFieldMask | ShadowBorder::InsideBorderFieldMask | ShadowBorder::CornerRadiusFieldMask | ShadowBorder::InternalToEdgeColorLengthFieldMask );



	
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
	ButtonPtr multiColorMatteButton = osg::Button::create();
	ButtonPtr roundedCornerLineButton = osg::Button::create();
	ButtonPtr shadowButton = osg::Button::create();
	
	// Edit each Button Component and assign its Border via the
	// setBorder function.  Note that setActiveBorder assigns the
	// Border to also be present while the Button is pressed by
	// clicking on it.
	beginEditCP(bevelButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);
		bevelButton->setPreferredSize(Vec2s(100,50));
		bevelButton->setText("Bevel Border");
		bevelButton->setBorder(bevelBorder);
		bevelButton->setActiveBorder(bevelBorder);
		bevelButton->setRolloverBorder(bevelBorder);
	endEditCP  (bevelButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);
	
	beginEditCP(compoundButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);
		compoundButton->setPreferredSize(Vec2s(100,50));
		compoundButton->setText("Compound Border");
		compoundButton->setBorder(compoundBorder);
		compoundButton->setActiveBorder(compoundBorder);
		compoundButton->setRolloverBorder(compoundBorder);
	endEditCP  (compoundButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);

	beginEditCP(emptyButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);
		emptyButton->setPreferredSize(Vec2s(100,50));
		emptyButton->setText("Empty Border");
		emptyButton->setBorder(emptyBorder);
		emptyButton->setActiveBorder(emptyBorder);
		emptyButton->setRolloverBorder(emptyBorder);
	endEditCP  (emptyButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);
	
	beginEditCP(etchedButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);
		etchedButton->setPreferredSize(Vec2s(100,50));
		etchedButton->setText("Etched Border");
		etchedButton->setBorder(etchedBorder);
		etchedButton->setActiveBorder(etchedBorder);
		etchedButton->setRolloverBorder(etchedBorder);
	endEditCP  (etchedButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);

	beginEditCP(lineButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);
		lineButton->setPreferredSize(Vec2s(100,50));
		lineButton->setText("Line Border");
		lineButton->setBorder(lineBorder);
		lineButton->setActiveBorder(lineBorder);
		lineButton->setRolloverBorder(lineBorder);
	endEditCP  (lineButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);

	beginEditCP(matteButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);
		matteButton->setPreferredSize(Vec2s(100,50));
		matteButton->setText("Matte Border");
		matteButton->setBorder(matteBorder);
		matteButton->setRolloverBorder(matteBorder);
		// Note that when matteButton is pressed, the Border will revert to the 
		// default Border for Buttons, a "pressed" BevelBorder
	endEditCP  (matteButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);
	
	beginEditCP(multiColorMatteButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);
		multiColorMatteButton->setPreferredSize(Vec2s(100,50));
		multiColorMatteButton->setText("Multi-Color Matte Border");
		multiColorMatteButton->setBorder(multiColorMatteBorder);
		multiColorMatteButton->setActiveBorder(multiColorMatteBorder);
		multiColorMatteButton->setRolloverBorder(multiColorMatteBorder);
	endEditCP  (multiColorMatteButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);

	beginEditCP(roundedCornerLineButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);
		roundedCornerLineButton->setPreferredSize(Vec2s(100,50));
		roundedCornerLineButton->setText("Rounded Border");
		roundedCornerLineButton->setBorder(roundedCornerLineBorder);
		roundedCornerLineButton->setActiveBorder(roundedCornerLineBorder);
		roundedCornerLineButton->setRolloverBorder(roundedCornerLineBorder);
	endEditCP  (roundedCornerLineButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);

	beginEditCP(shadowButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);
		shadowButton->setPreferredSize(Vec2s(100,50));
		shadowButton->setText("Shadow Border");
		shadowButton->setBorder(shadowBorder);
		shadowButton->setActiveBorder(shadowBorder);
		shadowButton->setRolloverBorder(shadowBorder);
	endEditCP  (roundedCornerLineButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask);


	
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
	   MainFrame->getChildren().addValue(multiColorMatteButton);
	   MainFrame->getChildren().addValue(roundedCornerLineButton);
	   MainFrame->getChildren().addValue(shadowButton);
	   MainFrame->setLayout(MainFrameLayout);
	   MainFrame->setBackground(mainBackground);
	endEditCP  (MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask| Frame::BackgroundFieldMask);

	//Create the Drawing Surface
	UIDrawingSurfacePtr drawingSurface = UIDrawingSurface::create();
	beginEditCP(drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask);
		drawingSurface->setGraphics(graphics);
		drawingSurface->setRootFrame(MainFrame);
	    drawingSurface->setEventProducer(TheWindowEventProducer);
    endEditCP  (drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask);
	
	// Create the UI Foreground Object
	UIForegroundPtr foreground = osg::UIForeground::create();

	beginEditCP(foreground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
	    foreground->setDrawingSurface(drawingSurface);
		foreground->setFramePositionOffset(Vec2s(0,0));
		foreground->setFrameBounds(Vec2f(0.5,0.5));
	   //Set the Event Producer for the DrawingSurface
	   //This is needed in order to get Mouse/Keyboard/etc Input to the UI DrawingSurface
    endEditCP  (foreground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
 
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

    TheWindowEventProducer->openWindow(Pnt2s(50,50),
                                        Vec2s(900,900),
                                        "OpenSG 03Border Window");

    //Main Event Loop
    while(!ExitApp)
    {
        TheWindowEventProducer->update();
        TheWindowEventProducer->draw();
    }
    osgExit();

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
