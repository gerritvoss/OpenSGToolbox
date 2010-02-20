/*************************************************
Welcome to the 03Border tutorial.  In this
tutorial, you will see how to use the 
different Borders available and add them
to components.  The following Borders are
introduced:
	
	BevelBorder
	CompoundBorder
	EmptyBorder
	EtchedBorder
	LineBorder
	MatteBorder
	MultiColorMatteBorder
    RoundedCornerLineBorder
	ShadowBorder
	PolygonBorder

Borders are used to quite simply give 
borders to components.  They can be added to 
components which are displayed for visual,
aesthetic, or interactive effect.  The 
different styles can be seen by running
this Tutorial.

The following all are shown and explained
within this tutorial (note the specific
requirements of each Border are not listed
here):

All Borders (where applicable):
	Creating Border
    Setting Color
	Setting Width
	Specifying style
	Adding Borders to components

These tutorials contain potentially relevant
information:



*************************************************/


// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// Methods to create simple geometry: boxes, spheres, tori etc.
#include "OSGSimpleGeometry.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"

// The general scene file loading handler
#include "OSGSceneFileHandler.h"

// Input
#include "OSGWindowUtils.h"

// UserInterface Headers
#include "OSGUIForeground.h"
#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"
#include "OSGGraphics2D.h"
#include "OSGLookAndFeelManager.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// Include Border header files
#include "OSGBorders.h"
#include "OSGLayers.h"
#include "OSGButton.h"
#include "OSGFlowLayout.h"


// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventUnrecPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
            TutorialWindow->closeWindow();
       }
   }

   virtual void keyReleased(const KeyEventUnrecPtr e)
   {
   }

   virtual void keyTyped(const KeyEventUnrecPtr e)
   {
   }
};

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindow = createNativeWindow();
    TutorialWindow->initWindow();

    TutorialWindow->setDisplayCallback(display);
    TutorialWindow->setReshapeCallback(reshape);

    TutorialKeyListener TheKeyListener;
    TutorialWindow->addKeyListener(&TheKeyListener);

    // Make Torus Node
    NodeRefPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Main Scene Node and add the Torus
    NodeRefPtr scene = OSG::Node::create();
        scene->setCore(OSG::Group::create());
        scene->addChild(TorusGeometryNode);

    // Create the Graphics
    GraphicsRefPtr TutorialGraphics = OSG::Graphics2D::create();

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
    BevelBorderRefPtr ExampleBevelBorder = OSG::BevelBorder::create();
    CompoundBorderRefPtr ExampleCompoundBorder = OSG::CompoundBorder::create();
    EtchedBorderRefPtr ExampleEtchedBorder = OSG::EtchedBorder::create();
    LineBorderRefPtr ExampleLineBorder = OSG::LineBorder::create();
    MatteBorderRefPtr ExampleMatteBorder = OSG::MatteBorder::create();
    EmptyBorderRefPtr ExampleEmptyBorder = OSG::EmptyBorder::create();
    MultiColorMatteBorderRefPtr ExampleMultiColorMatteBorder = OSG::MultiColorMatteBorder::create();
    RoundedCornerLineBorderRefPtr ExampleRoundedCornerLineBorder = OSG::RoundedCornerLineBorder::create();
    ShadowBorderRefPtr ExampleShadowBorder = OSG::ShadowBorder::create();
    PolygonBorderRefPtr ExamplePolygonBorder = OSG::PolygonBorder::create();
    
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

        ExampleBevelBorder->setRaised(true);
        ExampleBevelBorder->setWidth(5);
        ExampleBevelBorder->setHighlightInner(Color4f(1.0, 1.0, 0.5, 1.0));
        ExampleBevelBorder->setHighlightOuter(Color4f(0.5, 0.5, 1.0, 1.0));
        ExampleBevelBorder->setShadowInner(Color4f(1.0, 0.5, 1.0, 1.0));
        ExampleBevelBorder->setShadowOuter(Color4f(0.5, 1.0, 1.0, 1.0));

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

        ExampleCompoundBorder->setInnerBorder(ExampleBevelBorder);
        ExampleCompoundBorder->setOuterBorder(ExampleMatteBorder);
   
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

        ExampleEmptyBorder->setBottomWidth(5);
        ExampleEmptyBorder->setLeftWidth(5);
        ExampleEmptyBorder->setRightWidth(30);
        ExampleEmptyBorder->setTopWidth(30);

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

        ExampleEtchedBorder->setWidth(4);
        ExampleEtchedBorder->setHighlight(Color4f(1.0, 1.0, 1.0, 1.0));
        ExampleEtchedBorder->setShadow(Color4f(0.8, 0.8, 0.8, 1.0));
        ExampleEtchedBorder->setRaised(false);
    
	/******************************************************

        The LineBorder is simply a plain Line Border.

		-setWidth(int): Determines Width of	
			the Border in pixels.
		-setColor(Color4f): Determine the Color
			of the Border.

    ******************************************************/

        ExampleLineBorder->setWidth(1);
        ExampleLineBorder->setColor(Color4f(.7, 0.0, .5, 1.0));
 
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

        ExampleMatteBorder->setLeftWidth(3);
        ExampleMatteBorder->setRightWidth(2);
        ExampleMatteBorder->setBottomWidth(5);
        ExampleMatteBorder->setTopWidth(1);
        ExampleMatteBorder->setColor(Color4f(1.0, .5, .5, 1.0));
	
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
    
	/******************************************************

        The RoundedCornerLineBorder is a LineBorder
		with rounded corners.

		-setWidth(int): Determines Width of	
			the Border in pixels.
		-setColor(Color4f): Determine the Color
			of the Border.
		-setCornerRadius(int): Determine the radius
			of the corner in pixels.

    ******************************************************/

        ExampleRoundedCornerLineBorder->setWidth(2);
        ExampleRoundedCornerLineBorder->setColor(Color4f(1.0, 0.5, 0.5, 1.0));
        ExampleRoundedCornerLineBorder->setCornerRadius(15);
    
    // The ShadowBorder
        ExampleShadowBorder->setTopOffset(0);
        ExampleShadowBorder->setBottomOffset(5);
        ExampleShadowBorder->setLeftOffset(0);
        ExampleShadowBorder->setRightOffset(5);
        ExampleShadowBorder->setInsideBorder(ExampleRoundedCornerLineBorder);
        ExampleShadowBorder->setCornerRadius(15);
        ExampleShadowBorder->setInternalColor(Color4f(0.0, 0.0, 0.0, 0.5));
        ExampleShadowBorder->setEdgeColor(Color4f(0.0, 0.0, 0.0, 0.0));
        ExampleShadowBorder->setInternalToEdgeColorLength(5);

    // The PolygonBorder
        ExamplePolygonBorder->setWidth(4.0f);
        ExamplePolygonBorder->setColor(Color4f(1.0, 0.0, 0.0, 1.0));
        //ExamplePolygonBorder->editMFVertices()->push_back(Vec2f(0.2, 0.2));
        //ExamplePolygonBorder->editMFVertices()->push_back(Vec2f(1.0, 0.0));
        //ExamplePolygonBorder->editMFVertices()->push_back(Vec2f(0.0, 1.0));
		
        ExamplePolygonBorder->editMFVertices()->push_back(Vec2f(0.0, 0.0));
        ExamplePolygonBorder->editMFVertices()->push_back(Vec2f(0.4, 0.1));
        ExamplePolygonBorder->editMFVertices()->push_back(Vec2f(0.5, 0.0));
        ExamplePolygonBorder->editMFVertices()->push_back(Vec2f(0.6, 0.1));
		
        ExamplePolygonBorder->editMFVertices()->push_back(Vec2f(1.0, 0.0));
        ExamplePolygonBorder->editMFVertices()->push_back(Vec2f(0.9, 0.4));
        ExamplePolygonBorder->editMFVertices()->push_back(Vec2f(1.0, 0.5));
        ExamplePolygonBorder->editMFVertices()->push_back(Vec2f(0.9, 0.6));
		
        ExamplePolygonBorder->editMFVertices()->push_back(Vec2f(1.0, 1.0));
        ExamplePolygonBorder->editMFVertices()->push_back(Vec2f(0.6, 0.9));
        ExamplePolygonBorder->editMFVertices()->push_back(Vec2f(0.5, 1.0));
        ExamplePolygonBorder->editMFVertices()->push_back(Vec2f(0.4, 0.9));
		
        ExamplePolygonBorder->editMFVertices()->push_back(Vec2f(0.0, 1.0));
        ExamplePolygonBorder->editMFVertices()->push_back(Vec2f(0.1, 0.6));
        ExamplePolygonBorder->editMFVertices()->push_back(Vec2f(0.0, 0.5));
        ExamplePolygonBorder->editMFVertices()->push_back(Vec2f(0.1, 0.4));

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

    ButtonRefPtr ExampleBevelBorderButton = OSG::Button::create();
    ButtonRefPtr ExampleCompoundBorderButton = OSG::Button::create();
    ButtonRefPtr ExampleEmptyBorderButton = OSG::Button::create();
    ButtonRefPtr ExampleEtchedBorderButton = OSG::Button::create();
    ButtonRefPtr ExampleLineBorderButton = OSG::Button::create();
    ButtonRefPtr ExampleMatteBorderButton = OSG::Button::create();
    ButtonRefPtr ExampleMultiColorMatteBorderButton = OSG::Button::create();
    ButtonRefPtr ExampleoundedCornerLineBorderButton = OSG::Button::create();
    ButtonRefPtr ExampleShadowBorderButton = OSG::Button::create();
    ButtonRefPtr ExamplePolygonBorderButton = OSG::Button::create();
    
        ExampleBevelBorderButton->setPreferredSize(Vec2f(100,50));
        ExampleBevelBorderButton->setText("Bevel Border");
        ExampleBevelBorderButton->setBorder(ExampleBevelBorder);
        ExampleBevelBorderButton->setActiveBorder(ExampleBevelBorder);
        ExampleBevelBorderButton->setRolloverBorder(ExampleBevelBorder);
    
        ExampleCompoundBorderButton->setPreferredSize(Vec2f(100,50));
        ExampleCompoundBorderButton->setText("Compound Border");
        ExampleCompoundBorderButton->setBorder(ExampleCompoundBorder);
        ExampleCompoundBorderButton->setActiveBorder(ExampleCompoundBorder);
        ExampleCompoundBorderButton->setRolloverBorder(ExampleCompoundBorder);

        ExampleEmptyBorderButton->setPreferredSize(Vec2f(100,50));
        ExampleEmptyBorderButton->setText("Empty Border");
        ExampleEmptyBorderButton->setBorder(ExampleEmptyBorder);
        ExampleEmptyBorderButton->setActiveBorder(ExampleEmptyBorder);
        ExampleEmptyBorderButton->setRolloverBorder(ExampleEmptyBorder);
    
        ExampleEtchedBorderButton->setPreferredSize(Vec2f(100,50));
        ExampleEtchedBorderButton->setText("Etched Border");
        ExampleEtchedBorderButton->setBorder(ExampleEtchedBorder);
        ExampleEtchedBorderButton->setActiveBorder(ExampleEtchedBorder);
        ExampleEtchedBorderButton->setRolloverBorder(ExampleEtchedBorder);

        ExampleLineBorderButton->setPreferredSize(Vec2f(100,50));
        ExampleLineBorderButton->setText("Line Border");
        ExampleLineBorderButton->setBorder(ExampleLineBorder);
        ExampleLineBorderButton->setActiveBorder(ExampleLineBorder);
        ExampleLineBorderButton->setRolloverBorder(ExampleLineBorder);

        ExampleMatteBorderButton->setPreferredSize(Vec2f(100,50));
        ExampleMatteBorderButton->setText("Matte Border");
        ExampleMatteBorderButton->setBorder(ExampleMatteBorder);
        ExampleMatteBorderButton->setRolloverBorder(ExampleMatteBorder);
        // Note that when ExampleMatteBorderButton is pressed, the Border will revert to the 
        // default Border for Buttons, a "pressed" BevelBorder.  This is because no
		// ActiveBorder is specified.
    
        ExampleMultiColorMatteBorderButton->setPreferredSize(Vec2f(100,50));
        ExampleMultiColorMatteBorderButton->setText("Multi-Color Matte Border");
        ExampleMultiColorMatteBorderButton->setBorder(ExampleMultiColorMatteBorder);
        ExampleMultiColorMatteBorderButton->setActiveBorder(ExampleMultiColorMatteBorder);
        ExampleMultiColorMatteBorderButton->setRolloverBorder(ExampleMultiColorMatteBorder);

        ExampleoundedCornerLineBorderButton->setPreferredSize(Vec2f(100,50));
        ExampleoundedCornerLineBorderButton->setText("Rounded Border");
        ExampleoundedCornerLineBorderButton->setBorder(ExampleRoundedCornerLineBorder);
        ExampleoundedCornerLineBorderButton->setActiveBorder(ExampleRoundedCornerLineBorder);
        ExampleoundedCornerLineBorderButton->setRolloverBorder(ExampleRoundedCornerLineBorder);

        ExampleShadowBorderButton->setPreferredSize(Vec2f(100,50));
        ExampleShadowBorderButton->setText("Shadow Border");
        ExampleShadowBorderButton->setBorder(ExampleShadowBorder);
        ExampleShadowBorderButton->setActiveBorder(ExampleShadowBorder);
        ExampleShadowBorderButton->setRolloverBorder(ExampleShadowBorder);

        ExamplePolygonBorderButton->setPreferredSize(Vec2f(100,50));
        ExamplePolygonBorderButton->setText("Polygon Border");    
        ExamplePolygonBorderButton->setBorder(ExamplePolygonBorder);
        ExamplePolygonBorderButton->setActiveBorder(ExamplePolygonBorder);
        ExamplePolygonBorderButton->setRolloverBorder(ExamplePolygonBorder);


    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
    LayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();
       MainInternalWindow->pushToChildren(ExampleBevelBorderButton);
       MainInternalWindow->pushToChildren(ExampleCompoundBorderButton);
       MainInternalWindow->pushToChildren(ExampleEtchedBorderButton);
       MainInternalWindow->pushToChildren(ExampleEmptyBorderButton);
       MainInternalWindow->pushToChildren(ExampleLineBorderButton);
       MainInternalWindow->pushToChildren(ExampleMatteBorderButton);
       MainInternalWindow->pushToChildren(ExampleMultiColorMatteBorderButton);
       MainInternalWindow->pushToChildren(ExampleoundedCornerLineBorderButton);
       MainInternalWindow->pushToChildren(ExampleShadowBorderButton);
       MainInternalWindow->pushToChildren(ExamplePolygonBorderButton);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);

    // Create the Drawing Surface
    UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);
    
	TutorialDrawingSurface->openWindow(MainInternalWindow);

    // Create the UI Foreground Object
    UIForegroundRefPtr TutorialUIForeground = OSG::UIForeground::create();

        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);
 

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindow);
    mgr->setRoot(scene);

    // Add the UI Foreground Object to the Scene
    ViewportRefPtr TutorialViewport = mgr->getWindow()->getPort(0);
        TutorialViewport->addForeground(TutorialUIForeground);

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
            WinSize,
            "03Border");

    //Enter main Loop
    TutorialWindow->mainLoop();

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
void reshape(Vec2f Size)
{
    mgr->resize(Size.x(), Size.y());
}
