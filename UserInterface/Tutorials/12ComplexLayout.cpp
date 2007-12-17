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
#include <OpenSG/UserInterface/OSGFrame.h>
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

    // Make Torus Node (creates Torus in background of scene)
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

    // Initialize the LookAndFeelManager to enable default 
    // settings for the Button
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
    
    beginEditCP(ExampleLabel1GradientBackground, GradientUIBackground::ColorStartFieldMask | GradientUIBackground::ColorEndFieldMask | GradientUIBackground::AlignmentFieldMask);
        ExampleLabel1GradientBackground->setColorStart(Color4f(1.0, 0.0, 1.0, 0.8));
        ExampleLabel1GradientBackground->setColorEnd(Color4f(0.0, 0.0, 1.0, 0.3));
        ExampleLabel1GradientBackground->setAlignment(HORIZONTAL_ALIGNMENT);
    endEditCP(ExampleLabel1GradientBackground, GradientUIBackground::ColorStartFieldMask | GradientUIBackground::ColorEndFieldMask | GradientUIBackground::AlignmentFieldMask);
    
    beginEditCP(ExampleLabel1CompoundBackground, CompoundUIBackground::BackgroundsFieldMask);
        ExampleLabel1CompoundBackground->getBackgrounds().addValue(ExampleLabel1ColorBackground);
        ExampleLabel1CompoundBackground->getBackgrounds().addValue(ExampleLabel1GradientBackground);
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
        ExampleLabel1->setPreferredSize(Vec2s(800, 50));
        ExampleLabel1->setBackground(ExampleLabel1CompoundBackground);
        ExampleLabel1->setBorder(ExampleLabel1Border);
    endEditCP(ExampleLabel1, Button::PreferredSizeFieldMask | Button::BackgroundFieldMask | Button::BorderFieldMask);

    beginEditCP(ExampleButton1, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);
        ExampleButton1->setPreferredSize(Vec2s(800, 50));
        ExampleButton1->setMaxSize(Vec2s(50, 50));
        ExampleButton1->setText("Resize the Window to Show Diificulties with Using Just One Layout");
    endEditCP(ExampleButton1, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);

    beginEditCP(ExampleButton2, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);
        ExampleButton2->setPreferredSize(Vec2s(50, 50));
        ExampleButton2->setMaxSize(Vec2s(50, 50));
    endEditCP(ExampleButton2, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);
    
    beginEditCP(ExampleButton3, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);
        ExampleButton3->setPreferredSize(Vec2s(50, 50));
        ExampleButton3->setMaxSize(Vec2s(50, 50));
    endEditCP(ExampleButton3, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);

    beginEditCP(ExampleButton4, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);
        ExampleButton4->setPreferredSize(Vec2s(100, 50));
        ExampleButton4->setMaxSize(Vec2s(100, 50));
    endEditCP(ExampleButton4, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);

    beginEditCP(ExampleButton5, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);
        ExampleButton5->setPreferredSize(Vec2s(100, 50));
        ExampleButton5->setMaxSize(Vec2s(100, 50));
    endEditCP(ExampleButton5, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);

    beginEditCP(ExampleButton6, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);
        ExampleButton6->setPreferredSize(Vec2s(100, 50));
        ExampleButton6->setMaxSize(Vec2s(100, 50));
    endEditCP(ExampleButton6, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);

    beginEditCP(ExampleButton7, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);
        ExampleButton7->setPreferredSize(Vec2s(100, 50));
        ExampleButton7->setMaxSize(Vec2s(100, 50));
    endEditCP(ExampleButton7, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);

    beginEditCP(ExampleButton8, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);
        ExampleButton8->setPreferredSize(Vec2s(100, 50));
        ExampleButton8->setMaxSize(Vec2s(100, 50));
    endEditCP(ExampleButton8, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);

    beginEditCP(ExampleButton9, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);
        ExampleButton9->setPreferredSize(Vec2s(100, 50));
        ExampleButton9->setMaxSize(Vec2s(100, 50));
    endEditCP(ExampleButton9, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);

    beginEditCP(ExampleButton10, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);
        ExampleButton10->setPreferredSize(Vec2s(100, 50));
        ExampleButton10->setMaxSize(Vec2s(100, 50));
    endEditCP(ExampleButton10, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);

    beginEditCP(ExampleButton11, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);
        ExampleButton11->setPreferredSize(Vec2s(100, 50));
        ExampleButton11->setMaxSize(Vec2s(100, 50));
    endEditCP(ExampleButton11, Button::PreferredSizeFieldMask | Button::MaxSizeFieldMask | Button::TextFieldMask);

    /******************************************************

            Create some Layouts

    ******************************************************/
    FlowLayoutPtr MainFrameLayout = osg::FlowLayout::create();
    BoxLayoutPtr ExamplePanel1Layout = osg::BoxLayout::create();
    BoxLayoutPtr ExamplePanel2Layout = osg::BoxLayout::create();
    BoxLayoutPtr ExamplePanel3Layout = osg::BoxLayout::create();
    BoxLayoutPtr ExamplePanel4Layout = osg::BoxLayout::create();
    BoxLayoutPtr ExamplePanel5Layout = osg::BoxLayout::create();
    BoxLayoutPtr ExamplePanel6Layout = osg::BoxLayout::create();

    beginEditCP(ExamplePanel1Layout, BoxLayout::AlignmentFieldMask);
        ExamplePanel1Layout->setAlignment(VERTICAL_ALIGNMENT);
    endEditCP(ExamplePanel1Layout, BoxLayout::AlignmentFieldMask);

    beginEditCP(ExamplePanel2Layout, BoxLayout::AlignmentFieldMask);
        ExamplePanel2Layout->setAlignment(VERTICAL_ALIGNMENT);
    endEditCP(ExamplePanel2Layout, BoxLayout::AlignmentFieldMask);

    beginEditCP(ExamplePanel3Layout, BoxLayout::AlignmentFieldMask);
        ExamplePanel3Layout->setAlignment(VERTICAL_ALIGNMENT);
    endEditCP(ExamplePanel3Layout, BoxLayout::AlignmentFieldMask);

    beginEditCP(ExamplePanel4Layout, BoxLayout::AlignmentFieldMask);
        ExamplePanel4Layout->setAlignment(VERTICAL_ALIGNMENT);
    endEditCP(ExamplePanel4Layout, BoxLayout::AlignmentFieldMask);

    beginEditCP(ExamplePanel5Layout, BoxLayout::AlignmentFieldMask);
        ExamplePanel5Layout->setAlignment(VERTICAL_ALIGNMENT);
    endEditCP(ExamplePanel5Layout, BoxLayout::AlignmentFieldMask);

    beginEditCP(ExamplePanel6Layout, BoxLayout::AlignmentFieldMask);
        ExamplePanel6Layout->setAlignment(VERTICAL_ALIGNMENT);
    endEditCP(ExamplePanel6Layout, BoxLayout::AlignmentFieldMask);

    beginEditCP(MainFrameLayout, FlowLayout::AlignmentFieldMask | FlowLayout::MinorAxisAlignmentFieldMask);
        MainFrameLayout->setAlignment(HORIZONTAL_ALIGNMENT);
        MainFrameLayout->setMinorAxisAlignment(AXIS_CENTER_ALIGNMENT);
    endEditCP(MainFrameLayout, FlowLayout::AlignmentFieldMask | FlowLayout::MinorAxisAlignmentFieldMask);



    /******************************************************

        Create MainFrame and some Panels


    ******************************************************/
    FramePtr MainFrame = osg::Frame::create();
    PanelPtr ExamplePanel1 = osg::Panel::create();
    PanelPtr ExamplePanel2 = osg::Panel::create();
    PanelPtr ExamplePanel3 = osg::Panel::create();
    PanelPtr ExamplePanel4 = osg::Panel::create();
    PanelPtr ExamplePanel5 = osg::Panel::create();
    PanelPtr ExamplePanel6 = osg::Panel::create();

    
    // Edit Panel1, Panel2
    beginEditCP(ExamplePanel1, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundFieldMask | Panel::BorderFieldMask);
        ExamplePanel1->setPreferredSize(Vec2s(400, 400));
        ExamplePanel1->getChildren().addValue(ExampleButton2);
        ExamplePanel1->getChildren().addValue(ExamplePanel3);
        ExamplePanel1->getChildren().addValue(ExamplePanel4);
        ExamplePanel1->setLayout(ExamplePanel1Layout);
        ExamplePanel1->setBackground(ExamplePanelBackground);
        ExamplePanel1->setBorder(ExamplePanelBorder);
    endEditCP(ExamplePanel1, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundFieldMask | Panel::BorderFieldMask);

    beginEditCP(ExamplePanel2, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundFieldMask | Panel::BorderFieldMask);
        ExamplePanel2->setPreferredSize(Vec2s(400, 400));
        ExamplePanel2->getChildren().addValue(ExampleButton3);
        ExamplePanel2->getChildren().addValue(ExamplePanel5);
        ExamplePanel2->getChildren().addValue(ExamplePanel6);
        ExamplePanel2->setLayout(ExamplePanel2Layout);
        ExamplePanel2->setBackground(ExamplePanelBackground);
        ExamplePanel2->setBorder(ExamplePanelBorder);
    endEditCP(ExamplePanel2, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundFieldMask | Panel::BorderFieldMask);
    
    beginEditCP(ExamplePanel3, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask | Panel::BackgroundFieldMask);
        ExamplePanel3->getChildren().addValue(ExampleButton4);
        ExamplePanel3->getChildren().addValue(ExampleButton5);
        ExamplePanel3->setLayout(ExamplePanel3Layout);
        ExamplePanel3->setPreferredSize(Vec2s(125, 130));
        ExamplePanel3->setBackground(ExampleSmallPanelBackground);
    endEditCP(ExamplePanel3, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask | Panel::BackgroundFieldMask);
    
    beginEditCP(ExamplePanel4, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask | Panel::BackgroundFieldMask);
        ExamplePanel4->getChildren().addValue(ExampleButton6);
        ExamplePanel4->getChildren().addValue(ExampleButton7);
        ExamplePanel4->setLayout(ExamplePanel4Layout);
        ExamplePanel4->setPreferredSize(Vec2s(125, 130));
        ExamplePanel4->setBackground(ExampleSmallPanelBackground);
    endEditCP(ExamplePanel4, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask | Panel::BackgroundFieldMask);
        
    beginEditCP(ExamplePanel5, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask | Panel::BackgroundFieldMask);
        ExamplePanel5->getChildren().addValue(ExampleButton8);
        ExamplePanel5->getChildren().addValue(ExampleButton9);
        ExamplePanel5->setLayout(ExamplePanel5Layout);
        ExamplePanel5->setPreferredSize(Vec2s(125, 130));
        ExamplePanel5->setBackground(ExampleSmallPanelBackground);
    endEditCP(ExamplePanel5, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask | Panel::BackgroundFieldMask);
        
    beginEditCP(ExamplePanel6, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask | Panel::BackgroundFieldMask);
        ExamplePanel6->getChildren().addValue(ExampleButton10);
        ExamplePanel6->getChildren().addValue(ExampleButton11);
        ExamplePanel6->setLayout(ExamplePanel6Layout);
        ExamplePanel6->setPreferredSize(Vec2s(125, 130));
        ExamplePanel6->setBackground(ExampleSmallPanelBackground);
    endEditCP(ExamplePanel6, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask | Panel::BackgroundFieldMask);


    // Edit MainFrame
    beginEditCP(MainFrame, Frame::BorderFieldMask | Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);
       MainFrame->setBorder(ExamplePanelBorder);
       MainFrame->getChildren().addValue(ExampleLabel1);
       MainFrame->getChildren().addValue(ExampleButton1);
       MainFrame->getChildren().addValue(ExamplePanel1);
       MainFrame->getChildren().addValue(ExamplePanel2);
       MainFrame->setLayout(MainFrameLayout);
       MainFrame->setBackground(MainFrameBackground);
    endEditCP(MainFrame, Frame::BorderFieldMask | Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);

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
        TutorialUIForeground->setFrameBounds(Vec2f(0.8,0.8));
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
                                        Vec2s(1100,900),
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
void reshape(Vec2s Size)
{
    mgr->resize(Size.x(), Size.y());
}
