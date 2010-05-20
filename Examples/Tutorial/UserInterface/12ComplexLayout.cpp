// OpenSG Tutorial Example: Creating a complex Layout
//
// This tutorial gives an example of creating a complex Scene
// Layout with multiple Buttons, Borders, and Panels
// 
// Includes: Containers, Layouts, Borders, and Backgrounds


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

// 12ComplexLayout Headers
#include "OSGButton.h"
#include "OSGLabel.h"
#include "OSGLineBorder.h"
#include "OSGAbsoluteLayout.h"
#include "OSGAbsoluteLayoutConstraints.h"
#include "OSGBoxLayout.h"
#include "OSGFlowLayout.h"
#include "OSGComponentContainer.h"
#include "OSGPanel.h"
#include "OSGLineBorder.h"
#include "OSGEmptyBorder.h"
#include "OSGEtchedBorder.h"
//#include "OSGUIDefines.h"
#include "OSGColorLayer.h"
#include "OSGGradientLayer.h"
#include "OSGCompoundLayer.h"

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
            
            Create some Backgrounds

    ******************************************************/
    ColorLayerRefPtr MainFrameBackground = OSG::ColorLayer::create();
    ColorLayerRefPtr ExamplePanelBackground = OSG::ColorLayer::create();
    ColorLayerRefPtr ExampleSmallPanelBackground = OSG::ColorLayer::create();
    ColorLayerRefPtr ExampleLabel1ColorBackground = OSG::ColorLayer::create();
    GradientLayerRefPtr ExampleLabel1GradientBackground = OSG::GradientLayer::create();
    CompoundLayerRefPtr ExampleLabel1CompoundBackground = OSG::CompoundLayer::create();
    
        MainFrameBackground->setColor(Color4f(0,0,1.0,0.5));

        ExamplePanelBackground->setColor(Color4f(0.0,0.0,0.0,0.5));

        ExampleSmallPanelBackground->setColor(Color4f(0.0,0.5,0.7,1.0));
    
        ExampleLabel1ColorBackground->setColor(Color4f(0.0, 0.0, 0.0, 1.0));
    
        ExampleLabel1GradientBackground->editMFColors()->push_back(Color4f(1.0, 0.0, 1.0, 0.8));
		ExampleLabel1GradientBackground->editMFStops()->push_back(0.0);
        ExampleLabel1GradientBackground->editMFColors()->push_back(Color4f(0.0, 0.0, 1.0, 0.3));
		ExampleLabel1GradientBackground->editMFStops()->push_back(1.0);
        ExampleLabel1GradientBackground->setStartPosition(Vec2f(0.0f,0.0f));
        ExampleLabel1GradientBackground->setEndPosition(Vec2f(1.0f,0.0f));
    
        ExampleLabel1CompoundBackground->pushToBackgrounds(ExampleLabel1ColorBackground);
        ExampleLabel1CompoundBackground->pushToBackgrounds(ExampleLabel1GradientBackground);

    /******************************************************
            
            Create some Borders

    ******************************************************/
    EtchedBorderRefPtr ExamplePanelBorder = OSG::EtchedBorder::create();
    EmptyBorderRefPtr ExampleLabel1Border = OSG::EmptyBorder::create();
        ExamplePanelBorder->setHighlight(Color4f(1.0, 1.0, 1.0, 1.0));
        ExamplePanelBorder->setShadow(Color4f(0.8, 0.8, 0.8, 1.0));
        ExamplePanelBorder->setWidth(6);

    /******************************************************
            
                Creates some Button components

    ******************************************************/

    LabelRefPtr ExampleLabel1 = OSG::Label::create();
    ButtonRefPtr ExampleButton1 = OSG::Button::create();
    ButtonRefPtr ExampleButton2 = OSG::Button::create();
    ButtonRefPtr ExampleButton3 = OSG::Button::create();
    ButtonRefPtr ExampleButton4 = OSG::Button::create();
    ButtonRefPtr ExampleButton5 = OSG::Button::create();
    ButtonRefPtr ExampleButton6 = OSG::Button::create();
    ButtonRefPtr ExampleButton7 = OSG::Button::create();
    ButtonRefPtr ExampleButton8 = OSG::Button::create();
    ButtonRefPtr ExampleButton9 = OSG::Button::create();
    ButtonRefPtr ExampleButton10 = OSG::Button::create();
    ButtonRefPtr ExampleButton11 = OSG::Button::create();


        ExampleLabel1->setPreferredSize(Vec2f(800, 50));
        ExampleLabel1->setBackground(ExampleLabel1CompoundBackground);
        ExampleLabel1->setBorder(ExampleLabel1Border);

        ExampleButton1->setPreferredSize(Vec2f(800, 50));
        ExampleButton1->setMaxSize(Vec2f(50, 50));
        ExampleButton1->setText("Resize the Window to Show Diificulties with Using Just One Layout");

        ExampleButton2->setPreferredSize(Vec2f(50, 50));
        ExampleButton2->setMaxSize(Vec2f(50, 50));
    
        ExampleButton3->setPreferredSize(Vec2f(50, 50));
        ExampleButton3->setMaxSize(Vec2f(50, 50));

        ExampleButton4->setPreferredSize(Vec2f(100, 50));
        ExampleButton4->setMaxSize(Vec2f(100, 50));

        ExampleButton5->setPreferredSize(Vec2f(100, 50));
        ExampleButton5->setMaxSize(Vec2f(100, 50));

        ExampleButton6->setPreferredSize(Vec2f(100, 50));
        ExampleButton6->setMaxSize(Vec2f(100, 50));

        ExampleButton7->setPreferredSize(Vec2f(100, 50));
        ExampleButton7->setMaxSize(Vec2f(100, 50));

        ExampleButton8->setPreferredSize(Vec2f(100, 50));
        ExampleButton8->setMaxSize(Vec2f(100, 50));

        ExampleButton9->setPreferredSize(Vec2f(100, 50));
        ExampleButton9->setMaxSize(Vec2f(100, 50));

        ExampleButton10->setPreferredSize(Vec2f(100, 50));
        ExampleButton10->setMaxSize(Vec2f(100, 50));

        ExampleButton11->setPreferredSize(Vec2f(100, 50));
        ExampleButton11->setMaxSize(Vec2f(100, 50));

    /******************************************************

            Create some Layouts

    ******************************************************/
    FlowLayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();
    BoxLayoutRefPtr ExamplePanel1Layout = OSG::BoxLayout::create();
    BoxLayoutRefPtr ExamplePanel2Layout = OSG::BoxLayout::create();
    BoxLayoutRefPtr ExamplePanel3Layout = OSG::BoxLayout::create();
    BoxLayoutRefPtr ExamplePanel4Layout = OSG::BoxLayout::create();
    BoxLayoutRefPtr ExamplePanel5Layout = OSG::BoxLayout::create();
    BoxLayoutRefPtr ExamplePanel6Layout = OSG::BoxLayout::create();

	ExamplePanel1Layout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);

        ExamplePanel2Layout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);

        ExamplePanel3Layout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);

        ExamplePanel4Layout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);

        ExamplePanel5Layout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);

        ExamplePanel6Layout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);

	MainInternalWindowLayout->setOrientation(BoxLayout::HORIZONTAL_ORIENTATION);
        MainInternalWindowLayout->setMinorAxisAlignment(0.5f);



    /******************************************************

        Create MainFrame and some Panels


    ******************************************************/
    PanelRefPtr ExamplePanel1 = OSG::Panel::create();
    PanelRefPtr ExamplePanel2 = OSG::Panel::create();
    PanelRefPtr ExamplePanel3 = OSG::Panel::create();
    PanelRefPtr ExamplePanel4 = OSG::Panel::create();
    PanelRefPtr ExamplePanel5 = OSG::Panel::create();
    PanelRefPtr ExamplePanel6 = OSG::Panel::create();

    
    // Edit Panel1, Panel2
        ExamplePanel1->setPreferredSize(Vec2f(400, 400));
        ExamplePanel1->pushToChildren(ExampleButton2);
        ExamplePanel1->pushToChildren(ExamplePanel3);
        ExamplePanel1->pushToChildren(ExamplePanel4);
        ExamplePanel1->setLayout(ExamplePanel1Layout);
        ExamplePanel1->setBackgrounds(ExamplePanelBackground);
        ExamplePanel1->setBorders(ExamplePanelBorder);

        ExamplePanel2->setPreferredSize(Vec2f(400, 400));
        ExamplePanel2->pushToChildren(ExampleButton3);
        ExamplePanel2->pushToChildren(ExamplePanel5);
        ExamplePanel2->pushToChildren(ExamplePanel6);
        ExamplePanel2->setLayout(ExamplePanel2Layout);
        ExamplePanel2->setBackgrounds(ExamplePanelBackground);
        ExamplePanel2->setBorders(ExamplePanelBorder);
    
        ExamplePanel3->pushToChildren(ExampleButton4);
        ExamplePanel3->pushToChildren(ExampleButton5);
        ExamplePanel3->setLayout(ExamplePanel3Layout);
        ExamplePanel3->setPreferredSize(Vec2f(125, 130));
        ExamplePanel3->setBackgrounds(ExampleSmallPanelBackground);
    
        ExamplePanel4->pushToChildren(ExampleButton6);
        ExamplePanel4->pushToChildren(ExampleButton7);
        ExamplePanel4->setLayout(ExamplePanel4Layout);
        ExamplePanel4->setPreferredSize(Vec2f(125, 130));
        ExamplePanel4->setBackgrounds(ExampleSmallPanelBackground);
        
        ExamplePanel5->pushToChildren(ExampleButton8);
        ExamplePanel5->pushToChildren(ExampleButton9);
        ExamplePanel5->setLayout(ExamplePanel5Layout);
        ExamplePanel5->setPreferredSize(Vec2f(125, 130));
        ExamplePanel5->setBackgrounds(ExampleSmallPanelBackground);
        
        ExamplePanel6->pushToChildren(ExampleButton10);
        ExamplePanel6->pushToChildren(ExampleButton11);
        ExamplePanel6->setLayout(ExamplePanel6Layout);
        ExamplePanel6->setPreferredSize(Vec2f(125, 130));
        ExamplePanel6->setBackgrounds(ExampleSmallPanelBackground);


    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
       MainInternalWindow->setBorder(ExamplePanelBorder);
       MainInternalWindow->pushToChildren(ExampleLabel1);
       MainInternalWindow->pushToChildren(ExampleButton1);
       MainInternalWindow->pushToChildren(ExamplePanel1);
       MainInternalWindow->pushToChildren(ExamplePanel2);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.8f,0.8f));
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
            "12ComplexLayout");

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
