// OpenSG Tutorial Example: Creating a Border
//
// This tutorial explains how to implement the 
// Borders offered by the OSG User Interface 
// library and how to modify their features.
//
// Note the difference when clicking on ExampleMatteBorderButton
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
    WindowEventProducerPtr TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();
    
    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TutorialWindowEventProducer->addWindowListener(&TheTutorialWindowListener);


    // Make Torus Node
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Main Scene Node
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        scene->setCore(osg::Group::create());
 
        // Add the Torus as a Child
        scene->addChild(TorusGeometryNode);
    }
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    // Create the Graphics
    GraphicsPtr TutorialGraphics = osg::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

    /******************************************************

        Create Border components and assign
        each attribute to each Border.  Note
        that the LookAndFeelManager automatically
        assigns default settings to Borders.
        Each attribute will be set individually
        in this tutorial.

    ******************************************************/
    BevelBorderPtr ExampleBevelBorder = osg::BevelBorder::create();
    CompoundBorderPtr ExampleCompoundBorder = osg::CompoundBorder::create();
    EtchedBorderPtr ExampleEtchedBorder = osg::EtchedBorder::create();
    LineBorderPtr ExampleLineBorder = osg::LineBorder::create();
    MatteBorderPtr ExampleMatteBorder = osg::MatteBorder::create();
    EmptyBorderPtr ExampleEmptyBorder = osg::EmptyBorder::create();
    MultiColorMatteBorderPtr ExampleMultiColorMatteBorder = osg::MultiColorMatteBorder::create();
    RoundedCornerLineBorderPtr ExampleRoundedCornerLineBorder = osg::RoundedCornerLineBorder::create();
    ShadowBorderPtr ExampleShadowBorder = osg::ShadowBorder::create();
    
    /******************************************************

        The BevelBorder causes the Border to appear
		raised or indented.

		-setRaised(bool): Determines whether Border
			appears Raised (true) or indented (false).
        -setWidth(int): Determines the Width
			of the Border in pixels.
		-setHighlightInner(Color4f): See below.
		-setHighlightOuter(Color4f): See below.
		-setShadowInner(Color4f): See below.
		-setShadowOuter(Color4f): See below.

		These four functions determine the color
		of the BevelBorder.  While setRaised(true):
		HightlightInner and HighlightOuter are bottom
		and right, and left and top while false.  The 
		ShadowInner and ShadowOuter are the opposite 
		sides.			

    ******************************************************/

    beginEditCP(ExampleBevelBorder, BevelBorder::RaisedFieldMask | BevelBorder::WidthFieldMask | BevelBorder::HighlightInnerFieldMask |
        BevelBorder::HighlightOuterFieldMask | BevelBorder::ShadowInnerFieldMask | BevelBorder::ShadowOuterFieldMask);
        ExampleBevelBorder->setRaised(true);
        ExampleBevelBorder->setWidth(5);
        ExampleBevelBorder->setHighlightInner(Color4f(1.0, 1.0, 0.5, 1.0));
        ExampleBevelBorder->setHighlightOuter(Color4f(0.5, 0.5, 1.0, 1.0));
        ExampleBevelBorder->setShadowInner(Color4f(1.0, 0.5, 1.0, 1.0));
        ExampleBevelBorder->setShadowOuter(Color4f(0.5, 1.0, 1.0, 1.0));
    endEditCP(ExampleBevelBorder, BevelBorder::RaisedFieldMask | BevelBorder::WidthFieldMask | BevelBorder::HighlightInnerFieldMask |
        BevelBorder::HighlightOuterFieldMask | BevelBorder::ShadowInnerFieldMask | BevelBorder::ShadowOuterFieldMask);

    /******************************************************

        The CompoundBorder takes two other Borders
		and creates a new Border using both.

		-setInnerBorder(BorderName): Determines 
			the inner Border.
		-setOuterBorder(BorderName): Determines
			the outer Border.

		Note: It is possible to create
		CompoundBorders using CompoundBorders
		using CompoundBorders using other 
		CompoundBorders, etc. 

    ******************************************************/

    beginEditCP(ExampleCompoundBorder, CompoundBorder::InnerBorderFieldMask | CompoundBorder::OuterBorderFieldMask);
        ExampleCompoundBorder->setInnerBorder(ExampleBevelBorder);
        ExampleCompoundBorder->setOuterBorder(ExampleMatteBorder);
    endEditCP(ExampleCompoundBorder, CompoundBorder::InnerBorderFieldMask | CompoundBorder::OuterBorderFieldMask);
   
    /******************************************************

        The EmptyBorder has a transparent Border
		which is not visible.

		-setBottomWidth(int): Determine the bottom
			Width of the Border in pixels.
		-setLeftWidth(int): Determine the left
			Width of the Border in pixels.
		-setRightWidth(int): Determine the right
			Width of the Border in pixels.
		-setTopWidth(int): Determine the top
			Width of the Border in pixels.

    ******************************************************/

    beginEditCP(ExampleEmptyBorder, EmptyBorder::BottomWidthFieldMask | EmptyBorder::LeftWidthFieldMask | EmptyBorder::RightWidthFieldMask | EmptyBorder::TopWidthFieldMask);
        ExampleEmptyBorder->setBottomWidth(5);
        ExampleEmptyBorder->setLeftWidth(5);
        ExampleEmptyBorder->setRightWidth(30);
        ExampleEmptyBorder->setTopWidth(30);
    endEditCP(ExampleEmptyBorder, EmptyBorder::BottomWidthFieldMask | EmptyBorder::LeftWidthFieldMask | EmptyBorder::RightWidthFieldMask | EmptyBorder::TopWidthFieldMask);

    /******************************************************

        The EtchedBorder causes the Border to appear
		raised or indented, but in a different
		style than BevelBorder.

		-setWidth(int): Determine the Width of
			the Border in pixels.  This works
			best with a Width of a multiple of 2.
		-setHighlight(Color4f): Determine the
			hightlight Color of the Border.
		-setShadow(Color4f): Determine the
			shadow Color of the Border.	
		-setRaised(bool): Determine if the 
			Border appears raised (true) or
			indented (false).

    ******************************************************/

    beginEditCP(ExampleEtchedBorder, EtchedBorder::WidthFieldMask | EtchedBorder::HighlightFieldMask | EtchedBorder::ShadowFieldMask | EtchedBorder::RaisedFieldMask);
        ExampleEtchedBorder->setWidth(4);
        ExampleEtchedBorder->setHighlight(Color4f(1.0, 1.0, 1.0, 1.0));
        ExampleEtchedBorder->setShadow(Color4f(0.8, 0.8, 0.8, 1.0));
        ExampleEtchedBorder->setRaised(false);
    endEditCP(ExampleEtchedBorder, EtchedBorder::WidthFieldMask | EtchedBorder::HighlightFieldMask | EtchedBorder::ShadowFieldMask | EtchedBorder::RaisedFieldMask);
    
	/******************************************************

        The LineBorder is simply a ExampleLineBorder Border.

		-setWidth(int): Determines Width of	
			the Border in pixels.
		-setColor(Color4f): Determine the Color
			of the Border.

    ******************************************************/

    beginEditCP(ExampleLineBorder, LineBorder::WidthFieldMask | LineBorder::ColorFieldMask);
        ExampleLineBorder->setWidth(1);
        ExampleLineBorder->setColor(Color4f(.7, 0.0, .5, 1.0));
    endEditCP(ExampleLineBorder, LineBorder::WidthFieldMask | LineBorder::ColorFieldMask);
 
	/******************************************************

        The MatteBorder is a LineBorder, except
		each edge Width can be specified
		individually.

		-setLeftWidth(int): Determines Width of	
			the left side of the Border in pixels.
		-setRightWidth(int): Determines Width of	
			the right side of the Border in pixels.
		-setBottomWidth(int): Determines Width of	
			the bottom side of the Border in pixels.
		-setTopWidth(int): Determines Width of	
			the top side of the Border in pixels.			
		-setColor(Color4f): Determine the Color
			of the Border.

    ******************************************************/

    beginEditCP(ExampleMatteBorder, MatteBorder::LeftWidthFieldMask | MatteBorder::RightWidthFieldMask | MatteBorder::BottomWidthFieldMask | 
		MatteBorder::TopWidthFieldMask | MatteBorder::ColorFieldMask);
        ExampleMatteBorder->setLeftWidth(3);
        ExampleMatteBorder->setRightWidth(2);
        ExampleMatteBorder->setBottomWidth(5);
        ExampleMatteBorder->setTopWidth(1);
        ExampleMatteBorder->setColor(Color4f(1.0, .5, .5, 1.0));
    endEditCP(ExampleMatteBorder, MatteBorder::LeftWidthFieldMask | MatteBorder::RightWidthFieldMask | MatteBorder::BottomWidthFieldMask | 
		MatteBorder::TopWidthFieldMask | MatteBorder::ColorFieldMask);
	
	/******************************************************

        The MultiColorMatteBorder is a MatteBorder,
		except each edge Color can also be
		specified individually.

		-setLeftWidth(int): Determines Width of	
			the left side of the Border in pixels.
		-setRightWidth(int): Determines Width of	
			the right side of the Border in pixels.
		-setBottomWidth(int): Determines Width of	
			the bottom side of the Border in pixels.
		-setTopWidth(int): Determines Width of	
			the top side of the Border in pixels.			

		-setLeftLineTopColor(Color4f): See below.
		-setLeftLineBottomCo(Color4f): See below.
		-setRightLineTopColor(Color4f): See below.
		-setRightLineBottomColor(Color4f): See below.
		-setBottomLineLeftColor(Color4f): See below.
		-setBottomLineRightColor(Color4f): See below.
		-setTopLineLeftColor(Color4f): See below.
		-setTopLineRightColor(Color4f): See below.

		These functions are used to create 
		ColorUIGradients for each of the Border's
		edges.  The functions themselves explain
		which part of the Border they are applicable
		to (bottom, right, etc).

    ******************************************************/

    beginEditCP(ExampleMultiColorMatteBorder, MultiColorMatteBorder::LeftWidthFieldMask | MultiColorMatteBorder::LeftLineTopColorFieldMask | MultiColorMatteBorder::LeftLineBottomColorFieldMask | MultiColorMatteBorder::RightWidthFieldMask |
        MultiColorMatteBorder::RightLineTopColorFieldMask | MultiColorMatteBorder::RightLineBottomColorFieldMask | MultiColorMatteBorder::BottomWidthFieldMask | MultiColorMatteBorder::BottomLineLeftColorFieldMask | MultiColorMatteBorder::BottomLineLeftColorFieldMask |
        MultiColorMatteBorder::TopWidthFieldMask | MultiColorMatteBorder::TopLineLeftColorFieldMask | MultiColorMatteBorder::TopLineRightColorFieldMask);
        ExampleMultiColorMatteBorder->setLeftWidth(10);
        ExampleMultiColorMatteBorder->setLeftLineTopColor(Color4f(1.0,0.0,0.0,1.0));
        ExampleMultiColorMatteBorder->setLeftLineBottomColor(Color4f(1.0,1.0,1.0,1.0));
        ExampleMultiColorMatteBorder->setRightWidth(10);
        ExampleMultiColorMatteBorder->setRightLineTopColor(Color4f(0.0,1.0,0.0,1.0));
        ExampleMultiColorMatteBorder->setRightLineBottomColor(Color4f(0.0,0.0,1.0,1.0));
        ExampleMultiColorMatteBorder->setBottomWidth(10);
        ExampleMultiColorMatteBorder->setBottomLineLeftColor(Color4f(1.0,1.0,1.0,1.0));
        ExampleMultiColorMatteBorder->setBottomLineRightColor(Color4f(0.0,0.0,1.0,1.0));
        ExampleMultiColorMatteBorder->setTopWidth(10);
        ExampleMultiColorMatteBorder->setTopLineLeftColor(Color4f(1.0,0.0,0.0,1.0));
        ExampleMultiColorMatteBorder->setTopLineRightColor(Color4f(0.0,1.0,0.0,1.0));
    endEditCP(ExampleMultiColorMatteBorder, MultiColorMatteBorder::LeftWidthFieldMask | MultiColorMatteBorder::LeftLineTopColorFieldMask | MultiColorMatteBorder::LeftLineBottomColorFieldMask | MultiColorMatteBorder::RightWidthFieldMask |
        MultiColorMatteBorder::RightLineTopColorFieldMask | MultiColorMatteBorder::RightLineBottomColorFieldMask | MultiColorMatteBorder::BottomWidthFieldMask | MultiColorMatteBorder::BottomLineLeftColorFieldMask | MultiColorMatteBorder::BottomLineLeftColorFieldMask |
        MultiColorMatteBorder::TopWidthFieldMask | MultiColorMatteBorder::TopLineLeftColorFieldMask | MultiColorMatteBorder::TopLineRightColorFieldMask);
    
	/******************************************************

        The RoundedCornerLineBorder is  a LineBorder
		with rounded corners.

		-setWidth(int): Determines Width of	
			the Border in pixels.
		-setColor(Color4f): Determine the Color
			of the Border.
		-setCornerRadius(int): Determine the radius
			of the corner in pixels.

    ******************************************************/

    beginEditCP(ExampleRoundedCornerLineBorder, RoundedCornerLineBorder::WidthFieldMask | RoundedCornerLineBorder::ColorFieldMask | RoundedCornerLineBorder::CornerRadiusFieldMask );
        ExampleRoundedCornerLineBorder->setWidth(2);
        ExampleRoundedCornerLineBorder->setColor(Color4f(1.0, 0.5, 0.5, 1.0));
        ExampleRoundedCornerLineBorder->setCornerRadius(15);
    endEditCP(ExampleRoundedCornerLineBorder, RoundedCornerLineBorder::WidthFieldMask | RoundedCornerLineBorder::ColorFieldMask | RoundedCornerLineBorder::CornerRadiusFieldMask);
    
    // The ShadowBorder
    beginEditCP(ExampleShadowBorder, ShadowBorder::TopOffsetFieldMask | ShadowBorder::BottomOffsetFieldMask | ShadowBorder::LeftOffsetFieldMask |
		ShadowBorder::RightOffsetFieldMask | ShadowBorder::InternalColorFieldMask| ShadowBorder::EdgeColorFieldMask | ShadowBorder::InsideBorderFieldMask | 
		ShadowBorder::CornerRadiusFieldMask | ShadowBorder::InternalToEdgeColorLengthFieldMask );
        ExampleShadowBorder->setTopOffset(0);
        ExampleShadowBorder->setBottomOffset(5);
        ExampleShadowBorder->setLeftOffset(0);
        ExampleShadowBorder->setRightOffset(5);
        ExampleShadowBorder->setInsideBorder(ExampleRoundedCornerLineBorder);
        ExampleShadowBorder->setCornerRadius(15);
        ExampleShadowBorder->setInternalColor(Color4f(0.0, 0.0, 0.0, 0.5));
        ExampleShadowBorder->setEdgeColor(Color4f(0.0, 0.0, 0.0, 0.0));
        ExampleShadowBorder->setInternalToEdgeColorLength(5);
    endEditCP(ExampleShadowBorder, ShadowBorder::TopOffsetFieldMask | ShadowBorder::BottomOffsetFieldMask | ShadowBorder::LeftOffsetFieldMask |
		ShadowBorder::RightOffsetFieldMask | ShadowBorder::InternalColorFieldMask| ShadowBorder::EdgeColorFieldMask | ShadowBorder::InsideBorderFieldMask | 
		ShadowBorder::CornerRadiusFieldMask | ShadowBorder::InternalToEdgeColorLengthFieldMask );



    
    /******************************************************

        Create Button Components to display each 
        of the different Borders.  Buttons will 
        be placed via the Flow layout.  

		Note that by setting the ActiveBorder
		and RolloverBorder, the Button will
		have the same Border even if the Button 
		is pressed or if the Mouse is hovering 
		above the Button (Active/Rollover 
		respectively).

    ******************************************************/

    ButtonPtr ExampleBevelBorderButton = osg::Button::create();
    ButtonPtr ExampleCompoundBorderButton = osg::Button::create();
    ButtonPtr ExampleEmptyBorderButton = osg::Button::create();
    ButtonPtr ExampleEtchedBorderButton = osg::Button::create();
    ButtonPtr ExampleLineBorderButton = osg::Button::create();
    ButtonPtr ExampleMatteBorderButton = osg::Button::create();
    ButtonPtr ExampleMultiColorMatteBorderButton = osg::Button::create();
    ButtonPtr ExampleoundedCornerLineBorderButton = osg::Button::create();
    ButtonPtr ExampleShadowBorderButton = osg::Button::create();
    
    beginEditCP(ExampleBevelBorderButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBorderFieldMask);
        ExampleBevelBorderButton->setPreferredSize(Vec2s(100,50));
        ExampleBevelBorderButton->setText("Bevel Border");
        ExampleBevelBorderButton->setBorder(ExampleBevelBorder);
        ExampleBevelBorderButton->setActiveBorder(ExampleBevelBorder);
        ExampleBevelBorderButton->setRolloverBorder(ExampleBevelBorder);
    endEditCP(ExampleBevelBorderButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBorderFieldMask);
    
    beginEditCP(ExampleCompoundBorderButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBorderFieldMask);
        ExampleCompoundBorderButton->setPreferredSize(Vec2s(100,50));
        ExampleCompoundBorderButton->setText("Compound Border");
        ExampleCompoundBorderButton->setBorder(ExampleCompoundBorder);
        ExampleCompoundBorderButton->setActiveBorder(ExampleCompoundBorder);
        ExampleCompoundBorderButton->setRolloverBorder(ExampleCompoundBorder);
    endEditCP(ExampleCompoundBorderButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBorderFieldMask);

    beginEditCP(ExampleEmptyBorderButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBorderFieldMask);
        ExampleEmptyBorderButton->setPreferredSize(Vec2s(100,50));
        ExampleEmptyBorderButton->setText("Empty Border");
        ExampleEmptyBorderButton->setBorder(ExampleEmptyBorder);
        ExampleEmptyBorderButton->setActiveBorder(ExampleEmptyBorder);
        ExampleEmptyBorderButton->setRolloverBorder(ExampleEmptyBorder);
    endEditCP(ExampleEmptyBorderButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBorderFieldMask);
    
    beginEditCP(ExampleEtchedBorderButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBorderFieldMask);
        ExampleEtchedBorderButton->setPreferredSize(Vec2s(100,50));
        ExampleEtchedBorderButton->setText("Etched Border");
        ExampleEtchedBorderButton->setBorder(ExampleEtchedBorder);
        ExampleEtchedBorderButton->setActiveBorder(ExampleEtchedBorder);
        ExampleEtchedBorderButton->setRolloverBorder(ExampleEtchedBorder);
    endEditCP(ExampleEtchedBorderButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBorderFieldMask);

    beginEditCP(ExampleLineBorderButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBorderFieldMask);
        ExampleLineBorderButton->setPreferredSize(Vec2s(100,50));
        ExampleLineBorderButton->setText("Line Border");
        ExampleLineBorderButton->setBorder(ExampleLineBorder);
        ExampleLineBorderButton->setActiveBorder(ExampleLineBorder);
        ExampleLineBorderButton->setRolloverBorder(ExampleLineBorder);
    endEditCP(ExampleLineBorderButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBorderFieldMask);

    beginEditCP(ExampleMatteBorderButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask | Button::RolloverBorderFieldMask);
        ExampleMatteBorderButton->setPreferredSize(Vec2s(100,50));
        ExampleMatteBorderButton->setText("Matte Border");
        ExampleMatteBorderButton->setBorder(ExampleMatteBorder);
        ExampleMatteBorderButton->setRolloverBorder(ExampleMatteBorder);
        // Note that when ExampleMatteBorderButton is pressed, the Border will revert to the 
        // default Border for Buttons, a "pressed" BevelBorder.  This is because no
		// ActiveBorder is specified.
   endEditCP(ExampleMatteBorderButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask | Button::RolloverBorderFieldMask);
    
    beginEditCP(ExampleMultiColorMatteBorderButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBorderFieldMask);
        ExampleMultiColorMatteBorderButton->setPreferredSize(Vec2s(100,50));
        ExampleMultiColorMatteBorderButton->setText("Multi-Color Matte Border");
        ExampleMultiColorMatteBorderButton->setBorder(ExampleMultiColorMatteBorder);
        ExampleMultiColorMatteBorderButton->setActiveBorder(ExampleMultiColorMatteBorder);
        ExampleMultiColorMatteBorderButton->setRolloverBorder(ExampleMultiColorMatteBorder);
    endEditCP(ExampleMultiColorMatteBorderButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBorderFieldMask);

    beginEditCP(ExampleoundedCornerLineBorderButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBorderFieldMask);
        ExampleoundedCornerLineBorderButton->setPreferredSize(Vec2s(100,50));
        ExampleoundedCornerLineBorderButton->setText("Rounded Border");
        ExampleoundedCornerLineBorderButton->setBorder(ExampleRoundedCornerLineBorder);
        ExampleoundedCornerLineBorderButton->setActiveBorder(ExampleRoundedCornerLineBorder);
        ExampleoundedCornerLineBorderButton->setRolloverBorder(ExampleRoundedCornerLineBorder);
    endEditCP(ExampleoundedCornerLineBorderButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBorderFieldMask);

    beginEditCP(ExampleShadowBorderButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBorderFieldMask);
        ExampleShadowBorderButton->setPreferredSize(Vec2s(100,50));
        ExampleShadowBorderButton->setText("Shadow Border");
        ExampleShadowBorderButton->setBorder(ExampleShadowBorder);
        ExampleShadowBorderButton->setActiveBorder(ExampleShadowBorder);
        ExampleShadowBorderButton->setRolloverBorder(ExampleShadowBorder);
    endEditCP(ExampleShadowBorderButton, Button::PreferredSizeFieldMask | Button::TextFieldMask | Button::BorderFieldMask | Button::ActiveBorderFieldMask | Button::RolloverBorderFieldMask);


    
    // Create The Main Frame
    // Create Background to be used with the Main Frame
    ColorUIBackgroundPtr MainFrameBackground = osg::ColorUIBackground::create();
    beginEditCP(MainFrameBackground, ColorUIBackground::ColorFieldMask);
        MainFrameBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainFrameBackground, ColorUIBackground::ColorFieldMask);
    FramePtr MainFrame = osg::Frame::create();
    LayoutPtr MainFrameLayout = osg::FlowLayout::create();
    beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);
       MainFrame->getChildren().addValue(ExampleBevelBorderButton);
       MainFrame->getChildren().addValue(ExampleCompoundBorderButton);
       MainFrame->getChildren().addValue(ExampleEtchedBorderButton);
       MainFrame->getChildren().addValue(ExampleEmptyBorderButton);
       MainFrame->getChildren().addValue(ExampleLineBorderButton);
       MainFrame->getChildren().addValue(ExampleMatteBorderButton);
       MainFrame->getChildren().addValue(ExampleMultiColorMatteBorderButton);
       MainFrame->getChildren().addValue(ExampleoundedCornerLineBorderButton);
       MainFrame->getChildren().addValue(ExampleShadowBorderButton);
       MainFrame->setLayout(MainFrameLayout);
       MainFrame->setBackground(MainFrameBackground);
    endEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask| Frame::BackgroundFieldMask);

    // Create the Drawing Surface
    UIDrawingSurfacePtr TutorialDrawingSurface = UIDrawingSurface::create();
    beginEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask | UIDrawingSurface::EventProducerFieldMask);
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setRootFrame(MainFrame);
        TutorialDrawingSurface->setEventProducer(TutorialWindowEventProducer);
    endEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask | UIDrawingSurface::EventProducerFieldMask);
    
    // Create the UI Foreground Object
    UIForegroundPtr TutorialUIForeground = osg::UIForeground::create();

    beginEditCP(TutorialUIForeground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);
        TutorialUIForeground->setFramePositionOffset(Vec2s(0,0));
        TutorialUIForeground->setFrameBounds(Vec2f(0.5,0.5));
    endEditCP(TutorialUIForeground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
 

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
    mgr->setRoot(scene);

    // Add the UI Foreground Object to the Scene
    ViewportPtr TutorialViewport = mgr->getWindow()->getPort(0);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);
        TutorialViewport->getForegrounds().addValue(TutorialUIForeground);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);

    // Show the whole Scene
    mgr->showAll();

    TutorialWindowEventProducer->openWindow(Pnt2s(50,50),
                                        Vec2s(900,900),
                                        "OpenSG 03Border Window");

    //Main Event Loop
    while(!ExitApp)
    {
        TutorialWindowEventProducer->update();
        TutorialWindowEventProducer->draw();
    }
    osgExit();

    return 0;
}
// Callback functions


// Redraw the window
void display(void)
{
    mgr->redraw();
}

// React to size changes
void reshape(Vec2s Size)
{
    mgr->resize(Size.x(), Size.y());
}