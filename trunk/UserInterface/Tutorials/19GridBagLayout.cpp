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
#include <OpenSG/UserInterface/OSGInternalWindow.h>
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
void reshape(Vec2f Size);


// 19GridBagLayout Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGColorLayer.h>
#include <OpenSG/UserInterface/OSGGridBagLayout.h>
#include <OpenSG/UserInterface/OSGGridBagLayoutConstraints.h>


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

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEvent& e)
   {
       if(e.getKey() == KeyEvent::KEY_Q && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           ExitApp = true;
       }
   }

   virtual void keyReleased(const KeyEvent& e)
   {
   }

   virtual void keyTyped(const KeyEvent& e)
   {
   }
};

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    WindowEventProducerPtr TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

	beginEditCP(TutorialWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);
		TutorialWindowEventProducer->setUseCallbackForDraw(true);
		TutorialWindowEventProducer->setUseCallbackForReshape(true);
	endEditCP(TutorialWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);
    
    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TutorialWindowEventProducer->addWindowListener(&TheTutorialWindowListener);
    TutorialKeyListener TheKeyListener;
    TutorialWindowEventProducer->addKeyListener(&TheKeyListener);

    // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Main Scene Node and add the Torus
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
        scene->addChild(TorusGeometryNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    // Create the Graphics
    GraphicsPtr TutorialGraphics = osg::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

    /******************************************************
            
               Creates some Button components

    ******************************************************/
    ButtonPtr ExampleButton1 = osg::Button::create();
    ButtonPtr ExampleButton2 = osg::Button::create();
    ButtonPtr ExampleButton3 = osg::Button::create();
    ButtonPtr ExampleButton4 = osg::Button::create();
    ButtonPtr ExampleButton5 = osg::Button::create();
    ButtonPtr ExampleButton6 = osg::Button::create();


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
    GridBagLayoutPtr MainInternalWindowLayout = osg::GridBagLayout::create();

    beginEditCP(MainInternalWindowLayout, GridBagLayout::ColumnsFieldMask | GridBagLayout::RowsFieldMask);
        MainInternalWindowLayout->setColumns(3);
        MainInternalWindowLayout->setRows(3);
    endEditCP(MainInternalWindowLayout, GridBagLayout::ColumnsFieldMask | GridBagLayout::RowsFieldMask); 

    
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
				the X direction, i.e. FILL_HORIZONTAL.  Float 
				values: [0.0,1.0].
			-setWeightY(float): Determine the percent of the
				Grid place the Constraint takes up in the Y
				direction, assuming a fill property is set in
				the X direction, i.e. FILLY_VERTICAL.  Float 
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
    GridBagLayoutConstraintsPtr ExampleButton1Constraints = osg::GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsPtr ExampleButton2Constraints = osg::GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsPtr ExampleButton3Constraints = osg::GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsPtr ExampleButton4Constraints = osg::GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsPtr ExampleButton5Constraints = osg::GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsPtr ExampleButton6Constraints = osg::GridBagLayoutConstraints::create();

    beginEditCP(ExampleButton1Constraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask | GridBagLayoutConstraints::GridHeightFieldMask |
        GridBagLayoutConstraints::GridWidthFieldMask | GridBagLayoutConstraints::FillFieldMask | GridBagLayoutConstraints::WeightXFieldMask | GridBagLayoutConstraints::WeightYFieldMask |
        GridBagLayoutConstraints::PadBottomFieldMask | GridBagLayoutConstraints::PadLeftFieldMask | GridBagLayoutConstraints::PadRightFieldMask | GridBagLayoutConstraints::PadTopFieldMask |
        GridBagLayoutConstraints::InternalPadXFieldMask | GridBagLayoutConstraints::InternalPadYFieldMask | GridBagLayoutConstraints::HorizontalAlignmentFieldMask |
        GridBagLayoutConstraints::VerticalAlignmentFieldMask);
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
    endEditCP(ExampleButton1Constraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask | GridBagLayoutConstraints::GridHeightFieldMask |
        GridBagLayoutConstraints::GridWidthFieldMask | GridBagLayoutConstraints::FillFieldMask | GridBagLayoutConstraints::WeightXFieldMask | GridBagLayoutConstraints::WeightYFieldMask |
        GridBagLayoutConstraints::PadBottomFieldMask | GridBagLayoutConstraints::PadLeftFieldMask | GridBagLayoutConstraints::PadRightFieldMask | GridBagLayoutConstraints::PadTopFieldMask |
        GridBagLayoutConstraints::InternalPadXFieldMask | GridBagLayoutConstraints::InternalPadYFieldMask | GridBagLayoutConstraints::HorizontalAlignmentFieldMask |
        GridBagLayoutConstraints::VerticalAlignmentFieldMask);
    
    beginEditCP(ExampleButton2Constraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        ExampleButton2Constraints->setGridX(1);
        ExampleButton2Constraints->setGridY(1);
    endEditCP(ExampleButton2Constraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
    
    beginEditCP(ExampleButton3Constraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        ExampleButton3Constraints->setGridX(2);
        ExampleButton3Constraints->setGridY(2);
    endEditCP(ExampleButton3Constraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
    
    beginEditCP(ExampleButton4Constraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        ExampleButton4Constraints->setGridX(2);
        ExampleButton4Constraints->setGridY(1);
    endEditCP(ExampleButton4Constraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
    
    beginEditCP(ExampleButton5Constraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        ExampleButton5Constraints->setGridX(1);
        ExampleButton5Constraints->setGridY(2);
    endEditCP(ExampleButton5Constraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
    
    beginEditCP(ExampleButton6Constraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);
        ExampleButton6Constraints->setGridX(0);
        ExampleButton6Constraints->setGridY(2);
    endEditCP(ExampleButton6Constraints, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask);


    beginEditCP(ExampleButton1, Button::TextFieldMask | Button::ConstraintsFieldMask);
        ExampleButton1->setText("Button1");
        ExampleButton1->setConstraints(ExampleButton1Constraints);
    endEditCP(ExampleButton1, Button::TextFieldMask |  Button::ConstraintsFieldMask);

    beginEditCP(ExampleButton2, Button::TextFieldMask | Button::ConstraintsFieldMask);
        ExampleButton2->setText("Button2");
        ExampleButton2->setConstraints(ExampleButton2Constraints);
    endEditCP(ExampleButton2, Button::TextFieldMask |  Button::ConstraintsFieldMask);

    beginEditCP(ExampleButton3, Button::TextFieldMask | Button::ConstraintsFieldMask);
        ExampleButton3->setText("Button3");
        ExampleButton3->setConstraints(ExampleButton3Constraints);
    endEditCP(ExampleButton3, Button::TextFieldMask |  Button::ConstraintsFieldMask);

    beginEditCP(ExampleButton4, Button::TextFieldMask | Button::ConstraintsFieldMask);
        ExampleButton4->setText("Button4");
        ExampleButton4->setConstraints(ExampleButton4Constraints);
    endEditCP(ExampleButton4, Button::TextFieldMask |  Button::ConstraintsFieldMask);

    beginEditCP(ExampleButton5, Button::TextFieldMask | Button::ConstraintsFieldMask);
        ExampleButton5->setText("Button5");
        ExampleButton5->setConstraints(ExampleButton5Constraints);
    endEditCP(ExampleButton5, Button::TextFieldMask |  Button::ConstraintsFieldMask);
    
    beginEditCP(ExampleButton6, Button::TextFieldMask | Button::ConstraintsFieldMask);
        ExampleButton6->setText("Button6");
        ExampleButton6->setConstraints(ExampleButton6Constraints);
    endEditCP(ExampleButton6, Button::TextFieldMask |  Button::ConstraintsFieldMask);

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().push_back(ExampleButton1);
       MainInternalWindow->getChildren().push_back(ExampleButton2);
       MainInternalWindow->getChildren().push_back(ExampleButton3);
       MainInternalWindow->getChildren().push_back(ExampleButton4);
       MainInternalWindow->getChildren().push_back(ExampleButton5);
       MainInternalWindow->getChildren().push_back(ExampleButton6);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
    endEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);

    // Create the Drawing Surface
    UIDrawingSurfacePtr TutorialDrawingSurface = UIDrawingSurface::create();
    beginEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindowEventProducer);
    endEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
    
	TutorialDrawingSurface->openWindow(MainInternalWindow);

    // Create the UI Foreground Object
    UIForegroundPtr TutorialUIForeground = osg::UIForeground::create();

    beginEditCP(TutorialUIForeground, UIForeground::DrawingSurfaceFieldMask);
        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);
	endEditCP(TutorialUIForeground, UIForeground::DrawingSurfaceFieldMask);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
    mgr->setRoot(scene);

    // Add the UI Foreground Object to the Scene
    ViewportPtr TutorialViewport = mgr->getWindow()->getPort(0);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);
        TutorialViewport->getForegrounds().push_back(TutorialUIForeground);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);

    // Show the whole Scene
    mgr->showAll();

    TutorialWindowEventProducer->openWindow(Pnt2f(50,50),
                                        Vec2f(900,900),
                                        "OpenSG 19GridBagLayout Window");

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
void reshape(Vec2f Size)
{
    mgr->resize(Size.x(), Size.y());
}
