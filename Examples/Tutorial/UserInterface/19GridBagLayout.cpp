// OpenSG Tutorial Example: Using the GridBag Layout
//        to place Components 
//
// This tutorial explains how to place ExampleButtons within a 
// frame utilizing the GridBag Layout command to 
// manage the layout through the OSG User Interface library.
//
// GridBagLayout is incredibly customizable with many more
// features than most Layouts
// 
// Includes: using GridBagLayout and GridBagLayoutConstraints

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


// 19GridBagLayout Headers
#include "OSGUIForeground.h"
#include "OSGUIDrawingSurface.h"
#include "OSGGraphics2D.h"
#include "OSGButton.h"
#include "OSGLookAndFeelManager.h"
#include "OSGColorLayer.h"
#include "OSGGridBagLayout.h"
#include "OSGGridBagLayoutConstraints.h"


// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventUnrecPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
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

    // Make Torus Node (creates Torus in background of scene)
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
            
               Creates some Button components

    ******************************************************/
    ButtonRefPtr ExampleButton1 = OSG::Button::create();
    ButtonRefPtr ExampleButton2 = OSG::Button::create();
    ButtonRefPtr ExampleButton3 = OSG::Button::create();
    ButtonRefPtr ExampleButton4 = OSG::Button::create();
    ButtonRefPtr ExampleButton5 = OSG::Button::create();
    ButtonRefPtr ExampleButton6 = OSG::Button::create();


    /******************************************************

            Create and edit GridBagLayout.

            -setColumns(int): Determine	the number of
                Columns in the Layout.  This automatically
				sets the Column Width weights equal, so
				that each Column is the same Width 
				unless otherwise specified (using
				GridBayLayoutConstraints).
			-setRows(int): Determines the number of Rows
                in the Layout.  This also sets the
				Row Height weights equal as above.

    ******************************************************/
    GridBagLayoutRefPtr MainInternalWindowLayout = OSG::GridBagLayout::create();

        MainInternalWindowLayout->setColumns(3);
        MainInternalWindowLayout->setRows(3);

    
    /******************************************************

            Create and edit GridBagLayoutConstraints.
			GridBagLayoutConstraints have many 
			options and can be incredibly
			versatile.

            -setGridX(X_LOCATION): Determine X location
				of Constraint (0,0 is the upper left 
				hand corner).
			-setGridY(Y_LOCATION): Determine Y location
				of Constraint.
            -setGridHeight(int): Determine how many 
				Grid spaces the Constraint occupies in
				the Vertical direction (a single
				Constraint can cause its Component to
				fill more than a single Grid space).
			-setGridWidth(int): Determine how many 
				Grid spaces the Constraint occupies in
				the Horizontal direction.
            -setFill(ENUM): Determines fill options.
                Arguments are:
                FILL_BOTH: Stretches both X/Y directions.
                FILL_HORIZONTAL: Stretches X direction; Y dir
                    remains untouched (so will display whatever
                    is the PreferredSize Y value).
                FILL_VERTICAL: Stretches Y direction; X dir
                    remains untouched (so will display whatever
                    is the PreferredSize X value).
                FILL_NONE: Does not stretch either direction,
                    Component displays at PreferredSize.
            -setWeightX(float): Determine the percent of the
				Grid place the Constraint takes up in the X
				direction, assuming a fill property is set in
				the X direction, i.e-> FILL_HORIZONTAL.  Float 
				values: [0.0,1.0].
			-setWeightY(float): Determine the percent of the
				Grid place the Constraint takes up in the Y
				direction, assuming a fill property is set in
				the X direction, i.e-> FILLY_VERTICAL.  Float 
				values: [0.0,1.0].
            -setPadBottom/Top/Right/Left(int): Determine the
                padding within the Grid space in each 
				respective direction in pixels.
            -setInternalPadX(int): Determine the internal
				padding in the X direction, and resizes
				Component to fit that size.
			-setInternalPadY(int): Determine the internal
				padding in the Y direction, and resizes
				Component to fit that size.
            -setHorizontalAlignment(float): Determine 
				alignment in Horizontal direction.  
				Float values: [0.0,1.0]  Note: 0.5 will
				center it.
			-setVerticalAlignment(float): Determine 
				alignment in Vertical direction.  
				Float values: [0.0,1.0]  Note: 0.5 will
				center it.

    ******************************************************/
    GridBagLayoutConstraintsRefPtr ExampleButton1Constraints = OSG::GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRefPtr ExampleButton2Constraints = OSG::GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRefPtr ExampleButton3Constraints = OSG::GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRefPtr ExampleButton4Constraints = OSG::GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRefPtr ExampleButton5Constraints = OSG::GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRefPtr ExampleButton6Constraints = OSG::GridBagLayoutConstraints::create();

        ExampleButton1Constraints->setGridX(0);
        ExampleButton1Constraints->setGridY(0);
        ExampleButton1Constraints->setGridHeight(2);
        ExampleButton1Constraints->setGridWidth(1);
        ExampleButton1Constraints->setFill(GridBagLayoutConstraints::FILL_HORIZONTAL);
        ExampleButton1Constraints->setWeightX(0.5);
        ExampleButton1Constraints->setWeightY(0.5);
        ExampleButton1Constraints->setPadBottom(0);
        ExampleButton1Constraints->setPadLeft(0);
        ExampleButton1Constraints->setPadRight(0);
        ExampleButton1Constraints->setPadTop(0);
        ExampleButton1Constraints->setInternalPadX(10);
        ExampleButton1Constraints->setInternalPadY(10);
        ExampleButton1Constraints->setHorizontalAlignment(0.75);
        ExampleButton1Constraints->setVerticalAlignment(0.75);
    
        ExampleButton2Constraints->setGridX(1);
        ExampleButton2Constraints->setGridY(1);
    
        ExampleButton3Constraints->setGridX(2);
        ExampleButton3Constraints->setGridY(2);
    
        ExampleButton4Constraints->setGridX(2);
        ExampleButton4Constraints->setGridY(1);
    
        ExampleButton5Constraints->setGridX(1);
        ExampleButton5Constraints->setGridY(2);
    
        ExampleButton6Constraints->setGridX(0);
        ExampleButton6Constraints->setGridY(2);


        ExampleButton1->setText("Button1");
        ExampleButton1->setConstraints(ExampleButton1Constraints);

        ExampleButton2->setText("Button2");
        ExampleButton2->setConstraints(ExampleButton2Constraints);

        ExampleButton3->setText("Button3");
        ExampleButton3->setConstraints(ExampleButton3Constraints);

        ExampleButton4->setText("Button4");
        ExampleButton4->setConstraints(ExampleButton4Constraints);

        ExampleButton5->setText("Button5");
        ExampleButton5->setConstraints(ExampleButton5Constraints);
    
        ExampleButton6->setText("Button6");
        ExampleButton6->setConstraints(ExampleButton6Constraints);

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
       MainInternalWindow->pushToChildren(ExampleButton1);
       MainInternalWindow->pushToChildren(ExampleButton2);
       MainInternalWindow->pushToChildren(ExampleButton3);
       MainInternalWindow->pushToChildren(ExampleButton4);
       MainInternalWindow->pushToChildren(ExampleButton5);
       MainInternalWindow->pushToChildren(ExampleButton6);
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
            "01RubberBandCamera");

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
