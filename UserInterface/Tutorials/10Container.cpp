// OpenSG Tutorial Example: Using Containers (Frames and Panels)
//
// This tutorial explains how use Frame and Panel Containers
// 
// Includes: creating and editing Frames, Panels, and adding
// Panels

// Note: in almost all cases, each Scene should have only ONE
// Frame, but may have unlimited Panels.


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

// 10Container Headers
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayout.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGBoxLayout.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGContainer.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGBevelBorder.h>
#include <OpenSG/UserInterface/OSGUIDefines.h>

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
                and edit their Text.

    ******************************************************/

    ButtonPtr ExampleButton1 = osg::Button::create();
    ButtonPtr ExampleButton2 = osg::Button::create();
    ButtonPtr ExampleButton3 = osg::Button::create();
    ButtonPtr ExampleButton4 = osg::Button::create();
    ButtonPtr ExampleButton5 = osg::Button::create();
    ButtonPtr ExampleButton6 = osg::Button::create();
    
    beginEditCP(ExampleButton1, Button::TextFieldMask);
        ExampleButton1->setText("This");
    endEditCP(ExampleButton1, Button::TextFieldMask);

    beginEditCP(ExampleButton2, Button::TextFieldMask);
        ExampleButton2->setText("is a");
    endEditCP(ExampleButton2, Button::TextFieldMask);

    beginEditCP(ExampleButton3, Button::TextFieldMask);
        ExampleButton3->setText("sample");
    endEditCP(ExampleButton3, Button::TextFieldMask);

    beginEditCP(ExampleButton4, Button::TextFieldMask);
        ExampleButton4->setText("two");
    endEditCP(ExampleButton4, Button::TextFieldMask);

    beginEditCP(ExampleButton5, Button::TextFieldMask);
        ExampleButton5->setText("ExamplePanel");
    endEditCP(ExampleButton5, Button::TextFieldMask);

    beginEditCP(ExampleButton6, Button::TextFieldMask);
        ExampleButton6->setText("layout");
    endEditCP(ExampleButton6, Button::TextFieldMask);

    
    /******************************************************

            Create some Flow and BoxLayouts to be 
            used with the Main Frame and two 
            Panels.

    ******************************************************/
    FlowLayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();
    FlowLayoutPtr ExamplePanel1Layout = osg::FlowLayout::create();
    FlowLayoutPtr ExamplePanel2Layout = osg::FlowLayout::create();

    beginEditCP(ExamplePanel1Layout, FlowLayout::AlignmentFieldMask);
        ExamplePanel1Layout->setAlignment(VERTICAL_ALIGNMENT);
    endEditCP(ExamplePanel1Layout, FlowLayout::AlignmentFieldMask);


    /******************************************************
            
            Create two Backgrounds to be used with
            Panels and MainInternalWindow.

    ******************************************************/
    ColorUIBackgroundPtr MainInternalWindowBackground = osg::ColorUIBackground::create();
    ColorUIBackgroundPtr ExamplePanelBackground = osg::ColorUIBackground::create();

    beginEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);

    beginEditCP(ExamplePanelBackground, ColorUIBackground::ColorFieldMask);
        ExamplePanelBackground->setColor(Color4f(0.0,0.0,0.0,1.0));
    endEditCP(ExamplePanelBackground, ColorUIBackground::ColorFieldMask);
    
    /******************************************************
            
            Create a Border to be used with
            the two Panels.

    ******************************************************/
    LineBorderPtr ExamplePanelBorder = osg::LineBorder::create();
    beginEditCP(ExamplePanelBorder, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);
        ExamplePanelBorder->setColor(Color4f(0.9, 0.9, 0.9, 1.0));
        ExamplePanelBorder->setWidth(3);
    endEditCP(ExamplePanelBorder, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);


    /******************************************************

        Create MainInternalWindow and two Panel Components and
        edit their characteristics.

        -setPreferredSize(Vec2f): Determine the 
			size of the Panel.
        -getChildren().addValue(ComponentName):
			Adds a Component to the
			Container as a Child (meaning it 
			will be displayed within it).
        -setLayout(LayoutName): Determines the 
			Layout of the Container.

    ******************************************************/
    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
    PanelPtr ExamplePanel1 = osg::Panel::create();
    PanelPtr ExamplePanel2 = osg::Panel::create();
    
    // Edit Panel1, Panel2
    beginEditCP(ExamplePanel1, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
        ExamplePanel1->setPreferredSize(Vec2f(200, 200));
        ExamplePanel1->getChildren().addValue(ExampleButton1);
        ExamplePanel1->getChildren().addValue(ExampleButton2);
        ExamplePanel1->getChildren().addValue(ExampleButton3);
        ExamplePanel1->setLayout(ExamplePanel1Layout);
        ExamplePanel1->setBackgrounds(ExamplePanelBackground);
        ExamplePanel1->setBorders(ExamplePanelBorder);
    endEditCP(ExamplePanel1, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);

    beginEditCP(ExamplePanel2, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
        ExamplePanel2->setPreferredSize(Vec2f(200, 200));
        ExamplePanel2->getChildren().addValue(ExampleButton4);
        ExamplePanel2->getChildren().addValue(ExampleButton5);
        ExamplePanel2->getChildren().addValue(ExampleButton6);
        ExamplePanel2->setLayout(ExamplePanel2Layout);
        ExamplePanel2->setBackgrounds(ExamplePanelBackground);
        ExamplePanel2->setBorders(ExamplePanelBorder);
    endEditCP(ExamplePanel2, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);

    // Create The Main InternalWindow
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().addValue(ExamplePanel1);
       MainInternalWindow->getChildren().addValue(ExamplePanel2);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
	   MainInternalWindow->setAllInsets(5);
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
        TutorialViewport->getForegrounds().addValue(TutorialUIForeground);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);

    // Show the whole Scene
    mgr->showAll();

    TutorialWindowEventProducer->openWindow(Pnt2f(50,50),
                                        Vec2f(900,900),
                                        "OpenSG 10Container Window");

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