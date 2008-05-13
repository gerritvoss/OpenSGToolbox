// OpenSG Tutorial Example: Creating a complex Layout
//
// This tutorial gives an example of creating a complex Scene
// Layout with multiple Buttons, Borders, and Panels
// 
// Includes: Containers, Layouts, Borders, and Backgrounds


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

// 12ComplexLayout Headers
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayout.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGBoxLayout.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGContainer.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGEmptyBorder.h>
#include <OpenSG/UserInterface/OSGEtchedBorder.h>
#include <OpenSG/UserInterface/OSGUIDefines.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
#include <OpenSG/UserInterface/OSGGradientUIBackground.h>
#include <OpenSG/UserInterface/OSGCompoundUIBackground.h>

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
            
            Create some Backgrounds

    ******************************************************/
    ColorUIBackgroundPtr MainFrameBackground = osg::ColorUIBackground::create();
    ColorUIBackgroundPtr ExamplePanelBackground = osg::ColorUIBackground::create();
    ColorUIBackgroundPtr ExampleSmallPanelBackground = osg::ColorUIBackground::create();
    ColorUIBackgroundPtr ExampleLabel1ColorBackground = osg::ColorUIBackground::create();
    GradientUIBackgroundPtr ExampleLabel1GradientBackground = osg::GradientUIBackground::create();
    CompoundUIBackgroundPtr ExampleLabel1CompoundBackground = osg::CompoundUIBackground::create();
    
    beginEditCP(MainFrameBackground, ColorUIBackground::ColorFieldMask);
        MainFrameBackground->setColor(Color4f(0,0,1.0,0.5));
    endEditCP(MainFrameBackground, ColorUIBackground::ColorFieldMask);

    beginEditCP(ExamplePanelBackground, ColorUIBackground::ColorFieldMask);
        ExamplePanelBackground->setColor(Color4f(0.0,0.0,0.0,0.5));
    endEditCP(ExamplePanelBackground, ColorUIBackground::ColorFieldMask);

    beginEditCP(ExampleSmallPanelBackground, ColorUIBackground::ColorFieldMask);
        ExampleSmallPanelBackground->setColor(Color4f(0.0,0.5,0.7,1.0));
    endEditCP(ExampleSmallPanelBackground, ColorUIBackground::ColorFieldMask);
    
    beginEditCP(ExampleLabel1ColorBackground, ColorUIBackground::ColorFieldMask);
        ExampleLabel1ColorBackground->setColor(Color4f(0.0, 0.0, 0.0, 1.0));
    endEditCP(ExampleLabel1ColorBackground, ColorUIBackground::ColorFieldMask);
    
    beginEditCP(ExampleLabel1GradientBackground, GradientUIBackground::ColorStartFieldMask | GradientUIBackground::ColorEndFieldMask | GradientUIBackground::OrientationFieldMask);
        ExampleLabel1GradientBackground->setColorStart(Color4f(1.0, 0.0, 1.0, 0.8));
        ExampleLabel1GradientBackground->setColorEnd(Color4f(0.0, 0.0, 1.0, 0.3));
        ExampleLabel1GradientBackground->setOrientation(GradientUIBackground::HORIZONTAL_ORIENTATION);
    endEditCP(ExampleLabel1GradientBackground, GradientUIBackground::ColorStartFieldMask | GradientUIBackground::ColorEndFieldMask | GradientUIBackground::OrientationFieldMask);
    
    beginEditCP(ExampleLabel1CompoundBackground, CompoundUIBackground::BackgroundsFieldMask);
        ExampleLabel1CompoundBackground->getBackgrounds().push_back(ExampleLabel1ColorBackground);
        ExampleLabel1CompoundBackground->getBackgrounds().push_back(ExampleLabel1GradientBackground);
    endEditCP(ExampleLabel1CompoundBackground, CompoundUIBackground::BackgroundsFieldMask);

    /******************************************************
            
            Create some Borders

    ******************************************************/
    EtchedBorderPtr ExamplePanelBorder = osg::EtchedBorder::create();
    EmptyBorderPtr ExampleLabel1Border = osg::EmptyBorder::create();
    beginEditCP(ExamplePanelBorder, EtchedBorder::HighlightFieldMask | EtchedBorder::ShadowFieldMask | EtchedBorder::WidthFieldMask);
        ExamplePanelBorder->setHighlight(Color4f(1.0, 1.0, 1.0, 1.0));
        ExamplePanelBorder->setShadow(Color4f(0.8, 0.8, 0.8, 1.0));
        ExamplePanelBorder->setWidth(6);
    endEditCP(ExamplePanelBorder, EtchedBorder::HighlightFieldMask | EtchedBorder::ShadowFieldMask | EtchedBorder::WidthFieldMask);

    /******************************************************
            
                Creates some Button components

    ******************************************************/

    LabelPtr ExampleLabel1 = osg::Label::create();
    ButtonPtr ExampleButton1 = osg::Button::create();
    ButtonPtr ExampleButton2 = osg::Button::create();
    ButtonPtr ExampleButton3 = osg::Button::create();
    ButtonPtr ExampleButton4 = osg::Button::create();
    ButtonPtr ExampleButton5 = osg::Button::create();
    ButtonPtr ExampleButton6 = osg::Button::create();
    ButtonPtr ExampleButton7 = osg::Button::create();
    ButtonPtr ExampleButton8 = osg::Button::create();
    ButtonPtr ExampleButton9 = osg::Button::create();
    ButtonPtr ExampleButton10 = osg::Button::create();
    ButtonPtr ExampleButton11 = osg::Button::create();


    beginEditCP(ExampleLabel1, Button::PreferredSizeFieldMask | Button::BackgroundFieldMask | Button::BorderFieldMask);
        ExampleLabel1->setPreferredSize(Vec2f(800, 50));
        ExampleLabel1->setBackground(ExampleLabel1CompoundBackground);
        ExampleLabel1->setBorder(ExampleLabel1Border);
    endEditCP(ExampleLabel1, Button::PreferredSizeFieldMask | Button::BackgroundFieldMask | Button::BorderFieldMask);

    beginEditCP(ExampleButton1, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);
        ExampleButton1->setPreferredSize(Vec2f(800, 50));
        ExampleButton1->setMaxSize(Vec2f(50, 50));
        ExampleButton1->setText("Resize the Window to Show Diificulties with Using Just One Layout");
    endEditCP(ExampleButton1, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);

    beginEditCP(ExampleButton2, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);
        ExampleButton2->setPreferredSize(Vec2f(50, 50));
        ExampleButton2->setMaxSize(Vec2f(50, 50));
    endEditCP(ExampleButton2, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);
    
    beginEditCP(ExampleButton3, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);
        ExampleButton3->setPreferredSize(Vec2f(50, 50));
        ExampleButton3->setMaxSize(Vec2f(50, 50));
    endEditCP(ExampleButton3, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);

    beginEditCP(ExampleButton4, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);
        ExampleButton4->setPreferredSize(Vec2f(100, 50));
        ExampleButton4->setMaxSize(Vec2f(100, 50));
    endEditCP(ExampleButton4, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);

    beginEditCP(ExampleButton5, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);
        ExampleButton5->setPreferredSize(Vec2f(100, 50));
        ExampleButton5->setMaxSize(Vec2f(100, 50));
    endEditCP(ExampleButton5, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);

    beginEditCP(ExampleButton6, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);
        ExampleButton6->setPreferredSize(Vec2f(100, 50));
        ExampleButton6->setMaxSize(Vec2f(100, 50));
    endEditCP(ExampleButton6, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);

    beginEditCP(ExampleButton7, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);
        ExampleButton7->setPreferredSize(Vec2f(100, 50));
        ExampleButton7->setMaxSize(Vec2f(100, 50));
    endEditCP(ExampleButton7, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);

    beginEditCP(ExampleButton8, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);
        ExampleButton8->setPreferredSize(Vec2f(100, 50));
        ExampleButton8->setMaxSize(Vec2f(100, 50));
    endEditCP(ExampleButton8, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);

    beginEditCP(ExampleButton9, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);
        ExampleButton9->setPreferredSize(Vec2f(100, 50));
        ExampleButton9->setMaxSize(Vec2f(100, 50));
    endEditCP(ExampleButton9, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);

    beginEditCP(ExampleButton10, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);
        ExampleButton10->setPreferredSize(Vec2f(100, 50));
        ExampleButton10->setMaxSize(Vec2f(100, 50));
    endEditCP(ExampleButton10, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);

    beginEditCP(ExampleButton11, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);
        ExampleButton11->setPreferredSize(Vec2f(100, 50));
        ExampleButton11->setMaxSize(Vec2f(100, 50));
    endEditCP(ExampleButton11, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);

    /******************************************************

            Create some Layouts

    ******************************************************/
    FlowLayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();
    BoxLayoutPtr ExamplePanel1Layout = osg::BoxLayout::create();
    BoxLayoutPtr ExamplePanel2Layout = osg::BoxLayout::create();
    BoxLayoutPtr ExamplePanel3Layout = osg::BoxLayout::create();
    BoxLayoutPtr ExamplePanel4Layout = osg::BoxLayout::create();
    BoxLayoutPtr ExamplePanel5Layout = osg::BoxLayout::create();
    BoxLayoutPtr ExamplePanel6Layout = osg::BoxLayout::create();

    beginEditCP(ExamplePanel1Layout, BoxLayout::OrientationFieldMask);
	ExamplePanel1Layout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);
    endEditCP(ExamplePanel1Layout, BoxLayout::OrientationFieldMask);

    beginEditCP(ExamplePanel2Layout, BoxLayout::OrientationFieldMask);
        ExamplePanel2Layout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);
    endEditCP(ExamplePanel2Layout, BoxLayout::OrientationFieldMask);

    beginEditCP(ExamplePanel3Layout, BoxLayout::OrientationFieldMask);
        ExamplePanel3Layout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);
    endEditCP(ExamplePanel3Layout, BoxLayout::OrientationFieldMask);

    beginEditCP(ExamplePanel4Layout, BoxLayout::OrientationFieldMask);
        ExamplePanel4Layout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);
    endEditCP(ExamplePanel4Layout, BoxLayout::OrientationFieldMask);

    beginEditCP(ExamplePanel5Layout, BoxLayout::OrientationFieldMask);
        ExamplePanel5Layout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);
    endEditCP(ExamplePanel5Layout, BoxLayout::OrientationFieldMask);

    beginEditCP(ExamplePanel6Layout, BoxLayout::OrientationFieldMask);
        ExamplePanel6Layout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);
    endEditCP(ExamplePanel6Layout, BoxLayout::OrientationFieldMask);

    beginEditCP(MainInternalWindowLayout, FlowLayout::OrientationFieldMask | FlowLayout::MinorAxisAlignmentFieldMask);
	MainInternalWindowLayout->setOrientation(BoxLayout::HORIZONTAL_ORIENTATION);
        MainInternalWindowLayout->setMinorAxisAlignment(0.5f);
    endEditCP(MainInternalWindowLayout, FlowLayout::OrientationFieldMask | FlowLayout::MinorAxisAlignmentFieldMask);



    /******************************************************

        Create MainFrame and some Panels


    ******************************************************/
    PanelPtr ExamplePanel1 = osg::Panel::create();
    PanelPtr ExamplePanel2 = osg::Panel::create();
    PanelPtr ExamplePanel3 = osg::Panel::create();
    PanelPtr ExamplePanel4 = osg::Panel::create();
    PanelPtr ExamplePanel5 = osg::Panel::create();
    PanelPtr ExamplePanel6 = osg::Panel::create();

    
    // Edit Panel1, Panel2
    beginEditCP(ExamplePanel1, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
        ExamplePanel1->setPreferredSize(Vec2f(400, 400));
        ExamplePanel1->getChildren().push_back(ExampleButton2);
        ExamplePanel1->getChildren().push_back(ExamplePanel3);
        ExamplePanel1->getChildren().push_back(ExamplePanel4);
        ExamplePanel1->setLayout(ExamplePanel1Layout);
        ExamplePanel1->setBackgrounds(ExamplePanelBackground);
        ExamplePanel1->setBorders(ExamplePanelBorder);
    endEditCP(ExamplePanel1, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);

    beginEditCP(ExamplePanel2, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
        ExamplePanel2->setPreferredSize(Vec2f(400, 400));
        ExamplePanel2->getChildren().push_back(ExampleButton3);
        ExamplePanel2->getChildren().push_back(ExamplePanel5);
        ExamplePanel2->getChildren().push_back(ExamplePanel6);
        ExamplePanel2->setLayout(ExamplePanel2Layout);
        ExamplePanel2->setBackgrounds(ExamplePanelBackground);
        ExamplePanel2->setBorders(ExamplePanelBorder);
    endEditCP(ExamplePanel2, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
    
    beginEditCP(ExamplePanel3, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask | Panel::BackgroundsFieldMask);
        ExamplePanel3->getChildren().push_back(ExampleButton4);
        ExamplePanel3->getChildren().push_back(ExampleButton5);
        ExamplePanel3->setLayout(ExamplePanel3Layout);
        ExamplePanel3->setPreferredSize(Vec2f(125, 130));
        ExamplePanel3->setBackgrounds(ExampleSmallPanelBackground);
    endEditCP(ExamplePanel3, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask | Panel::BackgroundsFieldMask);
    
    beginEditCP(ExamplePanel4, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask | Panel::BackgroundsFieldMask);
        ExamplePanel4->getChildren().push_back(ExampleButton6);
        ExamplePanel4->getChildren().push_back(ExampleButton7);
        ExamplePanel4->setLayout(ExamplePanel4Layout);
        ExamplePanel4->setPreferredSize(Vec2f(125, 130));
        ExamplePanel4->setBackgrounds(ExampleSmallPanelBackground);
    endEditCP(ExamplePanel4, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask | Panel::BackgroundsFieldMask);
        
    beginEditCP(ExamplePanel5, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask | Panel::BackgroundsFieldMask);
        ExamplePanel5->getChildren().push_back(ExampleButton8);
        ExamplePanel5->getChildren().push_back(ExampleButton9);
        ExamplePanel5->setLayout(ExamplePanel5Layout);
        ExamplePanel5->setPreferredSize(Vec2f(125, 130));
        ExamplePanel5->setBackgrounds(ExampleSmallPanelBackground);
    endEditCP(ExamplePanel5, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask | Panel::BackgroundsFieldMask);
        
    beginEditCP(ExamplePanel6, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask | Panel::BackgroundsFieldMask);
        ExamplePanel6->getChildren().push_back(ExampleButton10);
        ExamplePanel6->getChildren().push_back(ExampleButton11);
        ExamplePanel6->setLayout(ExamplePanel6Layout);
        ExamplePanel6->setPreferredSize(Vec2f(125, 130));
        ExamplePanel6->setBackgrounds(ExampleSmallPanelBackground);
    endEditCP(ExamplePanel6, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask | Panel::BackgroundsFieldMask);


    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorUIBackgroundPtr MainInternalWindowBackground = osg::ColorUIBackground::create();
    beginEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->setBorder(ExamplePanelBorder);
       MainInternalWindow->getChildren().push_back(ExampleLabel1);
       MainInternalWindow->getChildren().push_back(ExampleButton1);
       MainInternalWindow->getChildren().push_back(ExamplePanel1);
       MainInternalWindow->getChildren().push_back(ExamplePanel2);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.8f,0.8f));
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
                                        Vec2f(1100,900),
                                        "OpenSG 12ComplexLayout Window");

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
