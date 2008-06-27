// OpenSG Tutorial Example: Creating a Button Component
//
// This tutorial explains how to edit the basic features of
// a Button created in the OSG User Interface library.
// 
// Includes: Button PreferredSize, MaximumSize, MinimumSize, Font,
// Text,and adding a Button to a Scene.  Also note that clicking
// the Button causes it to appear pressed


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
void reshape(Vec2f Size);


// 21ExampleInterface Headers
#include <OpenSG/UserInterface/OSGUIRectangle.h>
#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGToggleButton.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGColorLayer.h>
#include <OpenSG/UserInterface/OSGUIFont.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayout.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGBoxLayout.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGGridLayout.h>
#include <OpenSG/UserInterface/OSGContainer.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGEmptyBorder.h>
#include <OpenSG/UserInterface/OSGEtchedBorder.h>
#include <OpenSG/UserInterface/OSGLayers.h>
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGCheckboxButton.h>
#include <OpenSG/UserInterface/OSGRadioButton.h>
#include <OpenSG/UserInterface/OSGRadioButtonGroup.h>
#include <OpenSG/UserInterface/OSGTextArea.h>
#include <OpenSG/UserInterface/OSGTextField.h>




WindowEventProducerPtr TutorialWindowEventProducer;


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

// Create functions create Component Panels to make 
// code easier to read
ComponentPtr createLeftPanelButtonPanel(void);
ComponentPtr createLeftPanelRadioTextPanel(void);
ComponentPtr createRightPanelButtonPanel(void);
ComponentPtr createRightPanelCheckPanel(void);
// This function makes a complex Background outside of the main code
// to make code easier to read
LayerPtr createComplexBackground(void);
// These functions create materials to use with objects in scene
ChunkMaterialPtr createRedMaterial(void);
ChunkMaterialPtr createBlueMaterial(void);
ChunkMaterialPtr createGreenMaterial(void);
NodePtr scene, ExampleTorus, ExampleCone, ExampleSphere, ExampleBox;
void create3DObjects(void);



// Declare some variables up front 
RadioButtonGroup buttonGroup;
TextAreaPtr LeftPanelTextArea;

class MakeTorus : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
        {         
            beginEditCP(scene, Node::ChildrenFieldMask);
                scene->addChild(ExampleTorus);
            endEditCP(scene, Node::ChildrenFieldMask);
        }

   virtual void buttonDeselected(const ButtonSelectedEvent& e)
        {         
            beginEditCP(scene, Node::ChildrenFieldMask);
                scene->subChild(ExampleTorus);
            endEditCP(scene, Node::ChildrenFieldMask);
        }
};
class MakeSphere : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
        {         
            beginEditCP(scene, Node::ChildrenFieldMask);
                scene->addChild(ExampleSphere);
            endEditCP(scene, Node::ChildrenFieldMask);
        }

   virtual void buttonDeselected(const ButtonSelectedEvent& e)
   {
            beginEditCP(scene, Node::ChildrenFieldMask);
                scene->subChild(ExampleSphere);
            endEditCP(scene, Node::ChildrenFieldMask);    
   }
};
class MakeBox : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
        {         
            beginEditCP(scene, Node::ChildrenFieldMask);
                scene->addChild(ExampleBox);
            endEditCP(scene, Node::ChildrenFieldMask);
        }

   virtual void buttonDeselected(const ButtonSelectedEvent& e)
   {
            beginEditCP(scene, Node::ChildrenFieldMask);
                scene->subChild(ExampleBox);
            endEditCP(scene, Node::ChildrenFieldMask);   
   }
};
class MakeCone : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
        {         
            beginEditCP(scene, Node::ChildrenFieldMask);
                scene->addChild(ExampleCone);
            endEditCP(scene, Node::ChildrenFieldMask);
        }

   virtual void buttonDeselected(const ButtonSelectedEvent& e)
   {
            beginEditCP(scene, Node::ChildrenFieldMask);
                scene->subChild(ExampleCone);
            endEditCP(scene, Node::ChildrenFieldMask);   
   }
};


// These classes create Listeners to change Font Color
// in the TextArea
class BlackFont : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
    {
        beginEditCP(LeftPanelTextArea, TextArea::TextColorFieldMask | TextArea::RolloverTextColorFieldMask);
            LeftPanelTextArea->setTextColor(Color4f( 0.0, 0.0 , 0.0, 1.0));
            LeftPanelTextArea->setRolloverTextColor(Color4f( 0.0, 0.0 , 0.0, 1.0));
        endEditCP(LeftPanelTextArea, TextArea::TextColorFieldMask | TextArea::RolloverTextColorFieldMask);
   }

   virtual void buttonDeselected(const ButtonSelectedEvent& e)
   {
    
   }
};
class RedFont : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
    {

        beginEditCP(LeftPanelTextArea, TextArea::TextColorFieldMask | TextArea::RolloverTextColorFieldMask);
            LeftPanelTextArea->setTextColor(Color4f( 1.0, 0.0 , 0.0, 1.0));
            LeftPanelTextArea->setRolloverTextColor(Color4f( 1.0, 0.0 , 0.0, 1.0));
        endEditCP(LeftPanelTextArea, TextArea::TextColorFieldMask | TextArea::RolloverTextColorFieldMask);
    
    }

   virtual void buttonDeselected(const ButtonSelectedEvent& e)
   {

   }
};
class BlueFont : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
    {

        beginEditCP(LeftPanelTextArea, TextArea::TextColorFieldMask | TextArea::RolloverTextColorFieldMask);
            LeftPanelTextArea->setTextColor(Color4f( 0.0, 0.0 , 1.0, 1.0));
            LeftPanelTextArea->setRolloverTextColor(Color4f( 0.0, 0.0 , 1.0, 1.0));
        endEditCP(LeftPanelTextArea, TextArea::TextColorFieldMask | TextArea::RolloverTextColorFieldMask);
    
    }

   virtual void buttonDeselected(const ButtonSelectedEvent& e)
   {

   }
};
class GreenFont : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
    {

        beginEditCP(LeftPanelTextArea, TextArea::TextColorFieldMask | TextArea::RolloverTextColorFieldMask);
            LeftPanelTextArea->setTextColor(Color4f( 0.0, 1.0 , 0.0, 1.0));
            LeftPanelTextArea->setRolloverTextColor(Color4f( 0.0, 1.0 , 0.0, 1.0));
        endEditCP(LeftPanelTextArea, TextArea::TextColorFieldMask | TextArea::RolloverTextColorFieldMask);
    
    }

   virtual void buttonDeselected(const ButtonSelectedEvent& e)
   {

   }
};

// Declare listeners to be global
BlackFont RadioButton1Listener;
RedFont RadioButton2Listener;
GreenFont RadioButton3Listener;
BlueFont RadioButton4Listener;
MakeTorus RightPanelCheck1Listener;
MakeBox RightPanelCheck2Listener;
MakeSphere RightPanelCheck3Listener;
MakeCone RightPanelCheck4Listener;
class TutorialMouseListener : public MouseListener
{
  public:
    virtual void mouseClicked(const MouseEvent& e)
    {
    }
    virtual void mouseEntered(const MouseEvent& e)
    {
    }
    virtual void mouseExited(const MouseEvent& e)
    {
    }
    virtual void mousePressed(const MouseEvent& e)
    {
        if(TutorialWindowEventProducer->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
            mgr->mouseButtonPress(e.getButton(), e.getLocation().x(), e.getLocation().y());
        }
    }
    virtual void mouseReleased(const MouseEvent& e)
    {
        if(TutorialWindowEventProducer->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
           mgr->mouseButtonRelease(e.getButton(), e.getLocation().x(), e.getLocation().y());
        }
    }
};

class TutorialMouseMotionListener : public MouseMotionListener
{
  public:
    virtual void mouseMoved(const MouseEvent& e)
    {
        if(TutorialWindowEventProducer->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
            mgr->mouseMove(e.getLocation().x(), e.getLocation().y());
        }
    }

    virtual void mouseDragged(const MouseEvent& e)
    {
        if(TutorialWindowEventProducer->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
            mgr->mouseMove(e.getLocation().x(), e.getLocation().y());
        }
    }
};


int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

	beginEditCP(TutorialWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);
		TutorialWindowEventProducer->setUseCallbackForDraw(true);
		TutorialWindowEventProducer->setUseCallbackForReshape(true);
	endEditCP(TutorialWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);
    
    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    TutorialMouseListener mouseListener;
    TutorialMouseMotionListener mouseMotionListener;
    TutorialWindowEventProducer->addMouseListener(&mouseListener);
    TutorialWindowEventProducer->addMouseMotionListener(&mouseMotionListener);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TutorialWindowEventProducer->addWindowListener(&TheTutorialWindowListener);
    TutorialKeyListener TheKeyListener;
    TutorialWindowEventProducer->addKeyListener(&TheKeyListener);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);

    // Set up Window
    TutorialWindowEventProducer->openWindow(Pnt2f(50,50),
                                        Vec2f(550,550),
                                        "OpenSG 21ExampleInterface Window");
    // Make Main Scene Node
    create3DObjects();
    scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    // Create the Graphics
    GraphicsPtr TutorialGraphics = osg::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->setLookAndFeel(WindowsLookAndFeel::create());
    LookAndFeelManager::the()->getLookAndFeel()->init();

        
    /******************************************************
            
            Create a Background

    ******************************************************/
    ColorLayerPtr GreyBackground = osg::ColorLayer::create();

    beginEditCP(GreyBackground, ColorLayer::ColorFieldMask);
        GreyBackground->setColor(Color4f(.93,.93,.93,1.0));
    endEditCP(GreyBackground, ColorLayer::ColorFieldMask);


    /******************************************************
            
            Create some Borders

    ******************************************************/
    LineBorderPtr PanelBorder = osg::LineBorder::create();
    EmptyBorderPtr Panel1Border = osg::EmptyBorder::create();
    EmptyBorderPtr Panel2Border = osg::EmptyBorder::create();
    EmptyBorderPtr emptyBorder = osg::EmptyBorder::create();
    
    beginEditCP(PanelBorder, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);
        PanelBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
        PanelBorder->setWidth(1);
    endEditCP(PanelBorder, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);

    beginEditCP(Panel1Border, EmptyBorder::TopWidthFieldMask | EmptyBorder::BottomWidthFieldMask | EmptyBorder::LeftWidthFieldMask | EmptyBorder::RightWidthFieldMask);
        Panel1Border->setTopWidth(0);
        Panel1Border->setBottomWidth(6);
        Panel1Border->setLeftWidth(0);
        Panel1Border->setRightWidth(0);
    beginEditCP(Panel1Border, EmptyBorder::TopWidthFieldMask | EmptyBorder::BottomWidthFieldMask | EmptyBorder::LeftWidthFieldMask | EmptyBorder::RightWidthFieldMask);
    beginEditCP(Panel2Border, EmptyBorder::TopWidthFieldMask | EmptyBorder::BottomWidthFieldMask | EmptyBorder::LeftWidthFieldMask | EmptyBorder::RightWidthFieldMask);
        Panel2Border->setTopWidth(0);
        Panel2Border->setBottomWidth(0);
        Panel2Border->setLeftWidth(0);
        Panel2Border->setRightWidth(0);
    beginEditCP(Panel2Border, EmptyBorder::TopWidthFieldMask | EmptyBorder::BottomWidthFieldMask | EmptyBorder::LeftWidthFieldMask | EmptyBorder::RightWidthFieldMask);
    

    /******************************************************

            Create some Labels and stuff to go 
            with them

    ******************************************************/
    LabelPtr LeftPanelLabel1 = osg::Label::create();
    UIFontPtr LeftPanelLabel1Font = osg::UIFont::create();

    beginEditCP(LeftPanelLabel1Font, UIFont::SizeFieldMask);
        LeftPanelLabel1Font->setSize(50);
    endEditCP(LeftPanelLabel1Font, UIFont::SizeFieldMask);

    beginEditCP(LeftPanelLabel1, Label::BordersFieldMask | Label::BackgroundsFieldMask | Label::FontFieldMask | Label::TextFieldMask | Label::PreferredSizeFieldMask | Label::HorizontalAlignmentFieldMask);
        LeftPanelLabel1->setBorders(emptyBorder);
        LeftPanelLabel1->setBackgrounds(GreyBackground);
        LeftPanelLabel1->setFont(LeftPanelLabel1Font);
        LeftPanelLabel1->setText("OSG Gui");
        LeftPanelLabel1->setPreferredSize(Vec2f(300, 100));
		LeftPanelLabel1->setHorizontalAlignment(.5);
	endEditCP(LeftPanelLabel1, Label::BordersFieldMask | Label::BackgroundsFieldMask | Label::FontFieldMask | Label::TextFieldMask | Label::PreferredSizeFieldMask | Label::HorizontalAlignmentFieldMask);

     /******************************************************

            Create some Layouts

    ******************************************************/
    BoxLayoutPtr MainInternalWindowLayout = osg::BoxLayout::create();
    FlowLayoutPtr LeftPanelLayout = osg::FlowLayout::create();
    BoxLayoutPtr RightPanelLayout = osg::BoxLayout::create();
    beginEditCP(MainInternalWindowLayout, BoxLayout::OrientationFieldMask);
        MainInternalWindowLayout->setOrientation(BoxLayout::HORIZONTAL_ORIENTATION);
    endEditCP(MainInternalWindowLayout, BoxLayout::OrientationFieldMask);

	beginEditCP(LeftPanelLayout, FlowLayout::OrientationFieldMask | FlowLayout::MinorAxisAlignmentFieldMask);
        LeftPanelLayout->setOrientation(FlowLayout::HORIZONTAL_ORIENTATION);
        LeftPanelLayout->setMinorAxisAlignment(1.0f);
    endEditCP(LeftPanelLayout, FlowLayout::OrientationFieldMask | FlowLayout::MinorAxisAlignmentFieldMask);

    beginEditCP(RightPanelLayout, BoxLayout::OrientationFieldMask);
        RightPanelLayout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);
    endEditCP(RightPanelLayout, BoxLayout::OrientationFieldMask);
    

    /******************************************************

        Create MainFrame and Panels

    ******************************************************/
    PanelPtr LeftPanel = osg::Panel::create();
    PanelPtr RightPanel = osg::Panel::create();

    // LeftPanel stuff
    beginEditCP(LeftPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
        LeftPanel->setPreferredSize(Vec2f(400, 500));
        LeftPanel->getChildren().push_back(LeftPanelLabel1);
        LeftPanel->getChildren().push_back(createLeftPanelButtonPanel());
        LeftPanel->getChildren().push_back(createLeftPanelRadioTextPanel());
        LeftPanel->setLayout(LeftPanelLayout);
        LeftPanel->setBackgrounds(GreyBackground);
        LeftPanel->setBorders(Panel1Border);
    endEditCP(LeftPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);

    //RightPanel stuff
    beginEditCP(RightPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
        RightPanel->setPreferredSize(Vec2f(200, 620));
        RightPanel->getChildren().push_back(createRightPanelButtonPanel());
        RightPanel->getChildren().push_back(createRightPanelCheckPanel());
        RightPanel->setLayout(RightPanelLayout);
        RightPanel->setBackgrounds(GreyBackground);
        RightPanel->setBorders(Panel2Border);
    endEditCP(RightPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
    
    // Create The Main InternalWindow
    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::BordersFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().push_back(LeftPanel);
       MainInternalWindow->getChildren().push_back(RightPanel);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(GreyBackground);
       MainInternalWindow->setBorders(PanelBorder);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(1.0f,1.0f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
    endEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::BordersFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);

    // Create the Drawing Surface
    UIDrawingSurfacePtr TutorialDrawingSurface = UIDrawingSurface::create();
    beginEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindowEventProducer);
    endEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
    
	TutorialDrawingSurface->openWindow(MainInternalWindow);

    // Make A 3D Rectangle to draw the UI on
    UIRectanglePtr UIRectCore = UIRectangle::create();
    beginEditCP(UIRectCore, UIRectangle::PointFieldMask | UIRectangle::WidthFieldMask | UIRectangle::HeightFieldMask | UIRectangle::DrawingSurfaceFieldMask);
        UIRectCore->setPoint(Pnt3f(-310.0,-310.0,370.0));
        UIRectCore->setWidth(620);
        UIRectCore->setHeight(620);
        UIRectCore->setDrawingSurface(TutorialDrawingSurface);
    endEditCP(UIRectCore, UIRectangle::PointFieldMask | UIRectangle::WidthFieldMask | UIRectangle::HeightFieldMask | UIRectangle::DrawingSurfaceFieldMask);
    
    NodePtr UIRectNode = osg::Node::create();
    beginEditCP(UIRectNode, Node::CoreFieldMask);
        UIRectNode->setCore(UIRectCore);
    endEditCP(UIRectNode, Node::CoreFieldMask);
    
    beginEditCP(scene, Node::ChildrenFieldMask);
        // add the UIRect as a child
        scene->addChild(UIRectNode);
    endEditCP(scene, Node::ChildrenFieldMask);


    mgr->setRoot(scene);

    // Show the whole Scene
    mgr->showAll();

    while(!ExitApp)
    {
        TutorialWindowEventProducer->update();
        TutorialWindowEventProducer->draw();
    }
    osgExit();

    return 0;
}


ComponentPtr createLeftPanelButtonPanel(void)

{

    // Create Label for this Panel
    LabelPtr LeftPanelButtonPanelLabel = osg::Label::create();

    beginEditCP(LeftPanelButtonPanelLabel, Label::TextColorFieldMask | Label::BackgroundFieldMask | Label::PreferredSizeFieldMask | Label::TextFieldMask | Label::HorizontalAlignmentFieldMask);
        LeftPanelButtonPanelLabel->setTextColor(Color4f(1.0,1.0,1.0,1.0));
        LeftPanelButtonPanelLabel->setRolloverTextColor(Color4f(1.0,1.0,1.0,1.0));
        LeftPanelButtonPanelLabel->setBackground(createComplexBackground());
        LeftPanelButtonPanelLabel->setPreferredSize(Vec2f(100, 50));
        LeftPanelButtonPanelLabel->setText("Various Options");
		LeftPanelButtonPanelLabel->setHorizontalAlignment(.5);
	endEditCP(LeftPanelButtonPanelLabel, Label::TextColorFieldMask | Label::BackgroundFieldMask | Label::PreferredSizeFieldMask | Label::TextFieldMask | Label::HorizontalAlignmentFieldMask);

    // Create and edit the Panel buttons
    ButtonPtr LeftPanelButton1 = osg::Button::create();
    ButtonPtr LeftPanelButton2 = osg::Button::create();
    ButtonPtr LeftPanelButton3 = osg::Button::create();
    ButtonPtr LeftPanelButton4 = osg::Button::create();
    ButtonPtr LeftPanelButton5 = osg::Button::create();
    ButtonPtr LeftPanelButton6 = osg::Button::create();

    beginEditCP(LeftPanelButton1, Button::TextFieldMask, Component::PreferredSizeFieldMask);
        LeftPanelButton1->setText("This");
        LeftPanelButton1->setPreferredSize(Vec2f(100,50));
    endEditCP(LeftPanelButton1, Button::TextFieldMask, Component::PreferredSizeFieldMask);
    
    beginEditCP(LeftPanelButton2, Button::TextFieldMask, Component::PreferredSizeFieldMask);
        LeftPanelButton2->setText("is");
        LeftPanelButton2->setPreferredSize(Vec2f(100,50));
    endEditCP(LeftPanelButton2, Button::TextFieldMask, Component::PreferredSizeFieldMask);

    beginEditCP(LeftPanelButton3, Button::TextFieldMask, Component::PreferredSizeFieldMask);
        LeftPanelButton3->setText("an");
        LeftPanelButton3->setPreferredSize(Vec2f(100,50));
    endEditCP(LeftPanelButton3, Button::TextFieldMask, Component::PreferredSizeFieldMask);

    beginEditCP(LeftPanelButton4, Button::TextFieldMask, Component::PreferredSizeFieldMask);
        LeftPanelButton4->setText("example");
        LeftPanelButton4->setPreferredSize(Vec2f(100,50));
    endEditCP(LeftPanelButton4, Button::TextFieldMask, Component::PreferredSizeFieldMask);

    beginEditCP(LeftPanelButton5, Button::TextFieldMask, Component::PreferredSizeFieldMask);
        LeftPanelButton5->setText("user");
        LeftPanelButton5->setPreferredSize(Vec2f(100,50));
    endEditCP(LeftPanelButton5, Button::TextFieldMask, Component::PreferredSizeFieldMask);
    
    beginEditCP(LeftPanelButton6, Button::TextFieldMask, Component::PreferredSizeFieldMask);
        LeftPanelButton6->setText("interface.");
        LeftPanelButton6->setPreferredSize(Vec2f(100,50));
    endEditCP(LeftPanelButton6, Button::TextFieldMask, Component::PreferredSizeFieldMask);
    

    // Create and edit Panel layout
    BoxLayoutPtr LeftPanelButtonPanelLayout = osg::BoxLayout::create();
    beginEditCP(LeftPanelButtonPanelLayout, BoxLayout::OrientationFieldMask);
        LeftPanelButtonPanelLayout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);
    endEditCP(LeftPanelButtonPanelLayout, BoxLayout::OrientationFieldMask);

    // Create an edit Panel Background
    ColorLayerPtr LeftPanelButtonPanelBackground = osg::ColorLayer::create();
    beginEditCP(LeftPanelButtonPanelBackground, ColorLayer::ColorFieldMask);
        LeftPanelButtonPanelBackground->setColor(Color4f(0.93,0.93,0.93,1.0));
    endEditCP(LeftPanelButtonPanelBackground, ColorLayer::ColorFieldMask);

    // Create Panel Border
    LineBorderPtr LeftPanelBorder = osg::LineBorder::create();
    beginEditCP(LeftPanelBorder, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);
        LeftPanelBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
        LeftPanelBorder->setWidth(1);
    endEditCP(LeftPanelBorder, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);

    // Create and edit Panel
    PanelPtr LeftPanelButtonPanel = osg::Panel::create();
    beginEditCP(LeftPanelButtonPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
        LeftPanelButtonPanel->setPreferredSize(Vec2f(180, 500));
        LeftPanelButtonPanel->getChildren().push_back(LeftPanelButtonPanelLabel);
        LeftPanelButtonPanel->getChildren().push_back(LeftPanelButton1);
        LeftPanelButtonPanel->getChildren().push_back(LeftPanelButton2);
        LeftPanelButtonPanel->getChildren().push_back(LeftPanelButton3);
        LeftPanelButtonPanel->getChildren().push_back(LeftPanelButton4);
        LeftPanelButtonPanel->getChildren().push_back(LeftPanelButton5);
        LeftPanelButtonPanel->getChildren().push_back(LeftPanelButton6);
        LeftPanelButtonPanel->setLayout(LeftPanelButtonPanelLayout);
        LeftPanelButtonPanel->setBackgrounds(LeftPanelButtonPanelBackground);
        LeftPanelButtonPanel->setBorders(LeftPanelBorder);
    endEditCP(LeftPanelButtonPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);

    return LeftPanelButtonPanel;
}




ComponentPtr createLeftPanelRadioTextPanel(void)
{

    // Create the RadioButton group
    RadioButtonPtr RadioButton1 = osg::RadioButton::create();
    RadioButtonPtr RadioButton2 = osg::RadioButton::create();
    RadioButtonPtr RadioButton3 = osg::RadioButton::create();
    RadioButtonPtr RadioButton4 = osg::RadioButton::create();

    beginEditCP(RadioButton1, RadioButton::VerticalAlignmentFieldMask | RadioButton::HorizontalAlignmentFieldMask | RadioButton::PreferredSizeFieldMask | RadioButton::TextFieldMask | RadioButton::ToolTipTextFieldMask);
        RadioButton1->setVerticalAlignment(0.5);
        RadioButton1->setHorizontalAlignment(0.0);
        RadioButton1->setPreferredSize(Vec2f(100, 40));
        RadioButton1->setText("Black Text");
        RadioButton1->setToolTipText("Set TextArea text black");
    endEditCP(RadioButton1, RadioButton::VerticalAlignmentFieldMask | RadioButton::HorizontalAlignmentFieldMask | RadioButton::SizeFieldMask | RadioButton::TextFieldMask | RadioButton::ToolTipTextFieldMask);
    RadioButton1->addButtonSelectedListener(&RadioButton1Listener);

    beginEditCP(RadioButton2, RadioButton::VerticalAlignmentFieldMask | RadioButton::HorizontalAlignmentFieldMask | RadioButton::SizeFieldMask | RadioButton::TextFieldMask | RadioButton::ToolTipTextFieldMask);
        RadioButton2->setVerticalAlignment(0.5);
        RadioButton2->setHorizontalAlignment(0.0);
        RadioButton2->setPreferredSize(Vec2f(100, 40));
        RadioButton2->setText("Red Text");
        RadioButton2->setToolTipText("Set TextArea text red");
    endEditCP(RadioButton2, RadioButton::VerticalAlignmentFieldMask | RadioButton::HorizontalAlignmentFieldMask | RadioButton::SizeFieldMask | RadioButton::TextFieldMask | RadioButton::ToolTipTextFieldMask);
    RadioButton2->addButtonSelectedListener(&RadioButton2Listener);

    beginEditCP(RadioButton3, RadioButton::VerticalAlignmentFieldMask | RadioButton::HorizontalAlignmentFieldMask | RadioButton::SizeFieldMask | RadioButton::TextFieldMask | RadioButton::ToolTipTextFieldMask);
        RadioButton3->setVerticalAlignment(0.5);
        RadioButton3->setHorizontalAlignment(0.0);
        RadioButton3->setPreferredSize(Vec2f(100, 40));
        RadioButton3->setText("Green Text");
        RadioButton3->setToolTipText("Set TextArea text green");
    endEditCP(RadioButton3, RadioButton::VerticalAlignmentFieldMask | RadioButton::HorizontalAlignmentFieldMask | RadioButton::SizeFieldMask | RadioButton::TextFieldMask | RadioButton::ToolTipTextFieldMask);
    RadioButton3->addButtonSelectedListener(&RadioButton3Listener);

    beginEditCP(RadioButton4, RadioButton::VerticalAlignmentFieldMask | RadioButton::HorizontalAlignmentFieldMask | RadioButton::SizeFieldMask | RadioButton::TextFieldMask | RadioButton::ToolTipTextFieldMask);
        RadioButton4->setVerticalAlignment(0.5);
        RadioButton4->setHorizontalAlignment(0.0);
        RadioButton4->setPreferredSize(Vec2f(100, 40));
        RadioButton4->setText("Blue Text");
        RadioButton4->setToolTipText("Set TextArea text blue");
    endEditCP(RadioButton4, RadioButton::VerticalAlignmentFieldMask | RadioButton::HorizontalAlignmentFieldMask | RadioButton::SizeFieldMask | RadioButton::TextFieldMask | RadioButton::ToolTipTextFieldMask);
    RadioButton4->addButtonSelectedListener(&RadioButton4Listener);

    buttonGroup.addButton(RadioButton1);
    buttonGroup.addButton(RadioButton2);
    buttonGroup.addButton(RadioButton3);
    buttonGroup.addButton(RadioButton4);


    // Create TextArea
    LeftPanelTextArea = osg::TextArea::create();
    beginEditCP(LeftPanelTextArea, TextArea::PreferredSizeFieldMask);
        LeftPanelTextArea->setPreferredSize(Vec2f(125, 200));
    endEditCP(LeftPanelTextArea, TextArea::PreferredSizeFieldMask);

    // Create Panel and its Background/Border to label TextField
    LabelPtr LeftPanelTextFieldLabel = osg::Label::create();
    EmptyLayerPtr LeftPanelTextFieldLabelBackground = osg::EmptyLayer::create();
    EmptyBorderPtr LeftPanelTextFieldLabelBorder = osg::EmptyBorder::create();
    beginEditCP(LeftPanelTextFieldLabel, Label::PreferredSizeFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask | Label::TextFieldMask);
        LeftPanelTextFieldLabel->setPreferredSize(Vec2f(100, 25));
        LeftPanelTextFieldLabel->setBorders(LeftPanelTextFieldLabelBorder);
        LeftPanelTextFieldLabel->setBackgrounds(LeftPanelTextFieldLabelBackground);
        LeftPanelTextFieldLabel->setText("Text Field");
    endEditCP(LeftPanelTextFieldLabel, Label::PreferredSizeFieldMask | Label::BordersFieldMask |  Label::BackgroundsFieldMask | Label::TextFieldMask);

    // Create TextField
    TextFieldPtr LeftPanelTextField = osg::TextField::create();
    beginEditCP(LeftPanelTextField, Component::PreferredSizeFieldMask);
        LeftPanelTextField->setPreferredSize(Vec2f(125.0f, 22.0f));
    endEditCP(LeftPanelTextField, Component::PreferredSizeFieldMask);

    
    // Create an edit Panel Background
    ColorLayerPtr LeftPanelRadioTextPanelBackground = osg::ColorLayer::create();
    beginEditCP(LeftPanelRadioTextPanelBackground, ColorLayer::ColorFieldMask);
        LeftPanelRadioTextPanelBackground->setColor(Color4f(0.93f,0.93f,0.93f,1.0f));
    endEditCP(LeftPanelRadioTextPanelBackground, ColorLayer::ColorFieldMask);

    // Create and edit Panel layouts
    FlowLayoutPtr LeftPanelRadioTextPanelLayout = osg::FlowLayout::create();
    FlowLayoutPtr LeftPanelRadioTextPanelRadioPanelLayout = osg::FlowLayout::create();
    FlowLayoutPtr LeftPanelRadioTextPanelTextPanelLayout = osg::FlowLayout::create();
    beginEditCP(LeftPanelRadioTextPanelLayout, FlowLayout::MinorAxisAlignmentFieldMask);
        LeftPanelRadioTextPanelLayout->setMinorAxisAlignment(0.0f);
    beginEditCP(LeftPanelRadioTextPanelLayout, FlowLayout::MinorAxisAlignmentFieldMask);

    // Create two Panels for this Panel
    PanelPtr LeftPanelRadioTextPanelRadioPanel = osg::Panel::create();
    PanelPtr LeftPanelRadioTextPanelTextPanel = osg::Panel::create();

    // Create some Borders
    EmptyBorderPtr LeftPanelRadioTextPanelRadioPanelBorder = osg::EmptyBorder::create();

    beginEditCP(LeftPanelRadioTextPanelRadioPanel, Component::BordersFieldMask | Component::PreferredSizeFieldMask | Component::BackgroundsFieldMask | Container::LayoutFieldMask | Container::ChildrenFieldMask);
        LeftPanelRadioTextPanelRadioPanel->setBorders(LeftPanelRadioTextPanelRadioPanelBorder);
        LeftPanelRadioTextPanelRadioPanel->setPreferredSize(Vec2f(125, 200));
        LeftPanelRadioTextPanelRadioPanel->setLayout(LeftPanelRadioTextPanelRadioPanelLayout);
        LeftPanelRadioTextPanelRadioPanel->setBackgrounds(LeftPanelRadioTextPanelBackground);
        LeftPanelRadioTextPanelRadioPanel->getChildren().push_back(RadioButton1);
        LeftPanelRadioTextPanelRadioPanel->getChildren().push_back(RadioButton2);
        LeftPanelRadioTextPanelRadioPanel->getChildren().push_back(RadioButton3);
        LeftPanelRadioTextPanelRadioPanel->getChildren().push_back(RadioButton4);
    endEditCP(LeftPanelRadioTextPanelRadioPanel, Component::BordersFieldMask | Component::PreferredSizeFieldMask | Component::BackgroundsFieldMask | Container::LayoutFieldMask | Container::ChildrenFieldMask);

    // Create Panel Border
    LineBorderPtr PanelBorder1 = osg::LineBorder::create();
    beginEditCP(PanelBorder1, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);
        PanelBorder1->setColor(Color4f(0.0,0.0,0.0,1.0));
        PanelBorder1->setWidth(1);
    endEditCP(PanelBorder1, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);

    // Create and edit Panel
    PanelPtr LeftPanelRadioTextPanel = osg::Panel::create();
    beginEditCP(LeftPanelRadioTextPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
        LeftPanelRadioTextPanel->setPreferredSize(Vec2f(180, 500));
        LeftPanelRadioTextPanel->getChildren().push_back(LeftPanelRadioTextPanelRadioPanel);
        LeftPanelRadioTextPanel->getChildren().push_back(LeftPanelTextArea);
        LeftPanelRadioTextPanel->getChildren().push_back(LeftPanelTextFieldLabel);
        LeftPanelRadioTextPanel->getChildren().push_back(LeftPanelTextField);
        LeftPanelRadioTextPanel->setLayout(LeftPanelRadioTextPanelLayout);
        LeftPanelRadioTextPanel->setBackgrounds(LeftPanelRadioTextPanelBackground);
        LeftPanelRadioTextPanel->setBorders(PanelBorder1);
    endEditCP(LeftPanelRadioTextPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);

    return LeftPanelRadioTextPanel;
}
ComponentPtr createRightPanelButtonPanel(void)
{
    // Create and edit the Panel Buttons
    ToggleButtonPtr RightPanelButton1 = osg::ToggleButton::create();
    ToggleButtonPtr RightPanelButton2 = osg::ToggleButton::create();
    ToggleButtonPtr RightPanelButton3 = osg::ToggleButton::create();
    ToggleButtonPtr RightPanelButton4 = osg::ToggleButton::create();

    beginEditCP(RightPanelButton1, Button::TextFieldMask, Component::PreferredSizeFieldMask);
        RightPanelButton1->setText("These");
        RightPanelButton1->setPreferredSize(Vec2f(100,50));
    endEditCP(RightPanelButton1, Button::TextFieldMask, Component::PreferredSizeFieldMask);
    
    beginEditCP(RightPanelButton2, Button::TextFieldMask, Component::PreferredSizeFieldMask);
        RightPanelButton2->setText("are");
        RightPanelButton2->setPreferredSize(Vec2f(100,50));
    endEditCP(RightPanelButton2, Button::TextFieldMask, Component::PreferredSizeFieldMask);

    beginEditCP(RightPanelButton3, Button::TextFieldMask, Component::PreferredSizeFieldMask);
        RightPanelButton3->setText("toggle");
        RightPanelButton3->setPreferredSize(Vec2f(100,50));
    endEditCP(RightPanelButton3, Button::TextFieldMask, Component::PreferredSizeFieldMask);

    beginEditCP(RightPanelButton4, Button::TextFieldMask, Component::PreferredSizeFieldMask);
        RightPanelButton4->setText("buttons");
        RightPanelButton4->setPreferredSize(Vec2f(100,50));
    endEditCP(RightPanelButton4, Button::TextFieldMask, Component::PreferredSizeFieldMask);


    // Create an edit Panel Background
    ColorLayerPtr RightPanelButtonPanelBackground = osg::ColorLayer::create();
    beginEditCP(RightPanelButtonPanelBackground, ColorLayer::ColorFieldMask);
        RightPanelButtonPanelBackground->setColor(Color4f(0.93,0.93,0.93,1.0));
    endEditCP(RightPanelButtonPanelBackground, ColorLayer::ColorFieldMask);

    // Create and edit Panel layout
    BoxLayoutPtr RightPanelButtonPanelLayout = osg::BoxLayout::create();
    beginEditCP(RightPanelButtonPanelLayout, BoxLayout::OrientationFieldMask);
        RightPanelButtonPanelLayout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);
    endEditCP(RightPanelButtonPanelLayout, BoxLayout::OrientationFieldMask);

    // Create Panel Border
    LineBorderPtr PanelBorder2 = osg::LineBorder::create();
    beginEditCP(PanelBorder2, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);
        PanelBorder2->setColor(Color4f(0.0,0.0,0.0,1.0));
        PanelBorder2->setWidth(1);
    endEditCP(PanelBorder2, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);

    // Create and edit Panel
    PanelPtr RightPanelButtonPanel = osg::Panel::create();
    beginEditCP(RightPanelButtonPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
        RightPanelButtonPanel->setPreferredSize(Vec2f(200, 300));
        RightPanelButtonPanel->getChildren().push_back(RightPanelButton1);
        RightPanelButtonPanel->getChildren().push_back(RightPanelButton2);
        RightPanelButtonPanel->getChildren().push_back(RightPanelButton3);
        RightPanelButtonPanel->getChildren().push_back(RightPanelButton4);
        RightPanelButtonPanel->setLayout(RightPanelButtonPanelLayout);
        RightPanelButtonPanel->setBackgrounds(RightPanelButtonPanelBackground);
        RightPanelButtonPanel->setBorders(PanelBorder2);
    endEditCP(RightPanelButtonPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);

    return RightPanelButtonPanel;

}
ComponentPtr createRightPanelCheckPanel(void)
{
    // Create and edit the CheckBoxes
    CheckboxButtonPtr RightPanelCheck1 = osg::CheckboxButton::create();
    CheckboxButtonPtr RightPanelCheck2 = osg::CheckboxButton::create();
    CheckboxButtonPtr RightPanelCheck3 = osg::CheckboxButton::create();
    CheckboxButtonPtr RightPanelCheck4 = osg::CheckboxButton::create();

    beginEditCP(RightPanelCheck1, Button::TextFieldMask, Component::PreferredSizeFieldMask);
        RightPanelCheck1->setText("Show Torus");
        RightPanelCheck1->setPreferredSize(Vec2f(125,50));
        RightPanelCheck1->setHorizontalAlignment(0.0);
    endEditCP(RightPanelCheck1, Button::TextFieldMask, Component::PreferredSizeFieldMask);
        // Add Listener
        RightPanelCheck1->addButtonSelectedListener(&RightPanelCheck1Listener);
    
    beginEditCP(RightPanelCheck2, Button::TextFieldMask, Component::PreferredSizeFieldMask);
        RightPanelCheck2->setText("Show Box");
        RightPanelCheck2->setPreferredSize(Vec2f(125,50));
        RightPanelCheck2->setHorizontalAlignment(0.0);
    endEditCP(RightPanelCheck2, Button::TextFieldMask, Component::PreferredSizeFieldMask);
        // Add Listener
        RightPanelCheck2->addButtonSelectedListener(&RightPanelCheck2Listener);

    beginEditCP(RightPanelCheck3, Button::TextFieldMask, Component::PreferredSizeFieldMask);
        RightPanelCheck3->setText("Show Sphere");
        RightPanelCheck3->setPreferredSize(Vec2f(125,50));
        RightPanelCheck3->setHorizontalAlignment(0.0);
    endEditCP(RightPanelCheck3, Button::TextFieldMask, Component::PreferredSizeFieldMask);
        // Add Listener
        RightPanelCheck3->addButtonSelectedListener(&RightPanelCheck3Listener);

    beginEditCP(RightPanelCheck4, Button::TextFieldMask, Component::PreferredSizeFieldMask);
        RightPanelCheck4->setText("Show Cone");
        RightPanelCheck4->setPreferredSize(Vec2f(125,50));
        RightPanelCheck4->setHorizontalAlignment(0.0);
    endEditCP(RightPanelCheck4, Button::TextFieldMask, Component::PreferredSizeFieldMask);
        // Add Listener
        RightPanelCheck4->addButtonSelectedListener(&RightPanelCheck4Listener);

    // Create an edit Panel Background
    ColorLayerPtr RightPanelCheckPanelBackground = osg::ColorLayer::create();
    beginEditCP(RightPanelCheckPanelBackground, ColorLayer::ColorFieldMask);
        RightPanelCheckPanelBackground->setColor(Color4f(0.93,0.93,0.93,1.0));
    endEditCP(RightPanelCheckPanelBackground, ColorLayer::ColorFieldMask);

    // Create and edit Panel layout
    BoxLayoutPtr RightPanelCheckPanelLayout = osg::BoxLayout::create();
    beginEditCP(RightPanelCheckPanelLayout, BoxLayout::OrientationFieldMask);
        RightPanelCheckPanelLayout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);
        RightPanelCheckPanelLayout->setMinorAxisAlignment(0.5f);
    endEditCP(RightPanelCheckPanelLayout, BoxLayout::OrientationFieldMask);

    // Create Panel Border
    LineBorderPtr PanelBorder3 = osg::LineBorder::create();
    beginEditCP(PanelBorder3, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);
        PanelBorder3->setColor(Color4f(0.0,0.0,0.0,1.0));
        PanelBorder3->setWidth(1);
    endEditCP(PanelBorder3, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);

    // Create and edit Panel
    PanelPtr RightPanelCheckPanel = osg::Panel::create();
    beginEditCP(RightPanelCheckPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);
        RightPanelCheckPanel->setPreferredSize(Vec2f(200, 300));
        RightPanelCheckPanel->getChildren().push_back(RightPanelCheck1);
        RightPanelCheckPanel->getChildren().push_back(RightPanelCheck2);
        RightPanelCheckPanel->getChildren().push_back(RightPanelCheck3);
        RightPanelCheckPanel->getChildren().push_back(RightPanelCheck4);
        RightPanelCheckPanel->setLayout(RightPanelCheckPanelLayout);
        RightPanelCheckPanel->setBackgrounds(RightPanelCheckPanelBackground);
        RightPanelCheckPanel->setBorders(PanelBorder3);
    endEditCP(RightPanelCheckPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundsFieldMask | Panel::BordersFieldMask);

    return RightPanelCheckPanel;
}
LayerPtr createComplexBackground(void)
{

    // Create complex Background 
    ColorLayerPtr ComplexBackgroundBase = osg::ColorLayer::create();
    GradientLayerPtr ComplexBackgroundGradient1 = osg::GradientLayer::create();
    GradientLayerPtr ComplexBackgroundGradient2 = osg::GradientLayer::create();
    GradientLayerPtr ComplexBackgroundGradient3 = osg::GradientLayer::create();
    CompoundLayerPtr ComplexBackgroundCompound1 = osg::CompoundLayer::create();
    CompoundLayerPtr ComplexBackgroundCompound2 = osg::CompoundLayer::create();
    CompoundLayerPtr ComplexBackground = osg::CompoundLayer::create();

    beginEditCP(ComplexBackgroundBase, ColorLayer::ColorFieldMask);
        ComplexBackgroundBase->setColor(Color4f(0.0, 0.0, .25, 1.0));
    endEditCP(ComplexBackgroundBase, ColorLayer::ColorFieldMask);

    beginEditCP(ComplexBackgroundGradient1, GradientLayer::ColorsFieldMask | GradientLayer::PositionsFieldMask | GradientLayer::OrientationFieldMask);
        ComplexBackgroundGradient1->getColors().push_back(Color4f(1.0, 0.0, 0.0, 0.5));
		ComplexBackgroundGradient1->getPositions().push_back(0.0);
        ComplexBackgroundGradient1->getColors().push_back(Color4f(0.5, 0.0, 0.0, 0.3));
		ComplexBackgroundGradient1->getPositions().push_back(1.0);
        ComplexBackgroundGradient1->setOrientation(GradientLayer::HORIZONTAL_ORIENTATION);
    endEditCP(ComplexBackgroundGradient1, GradientLayer::ColorsFieldMask | GradientLayer::PositionsFieldMask | GradientLayer::OrientationFieldMask);

    beginEditCP(ComplexBackgroundGradient2, GradientLayer::ColorsFieldMask | GradientLayer::PositionsFieldMask | GradientLayer::OrientationFieldMask);
        ComplexBackgroundGradient2->getColors().push_back(Color4f(.6, 0.0, 0.3, 1.0));
		ComplexBackgroundGradient2->getPositions().push_back(0.0);
        ComplexBackgroundGradient2->getColors().push_back(Color4f(.2, 0.0, 0.3, 0.5));
		ComplexBackgroundGradient2->getPositions().push_back(1.0);
        ComplexBackgroundGradient2->setOrientation(GradientLayer::VERTICAL_ORIENTATION);
    endEditCP(ComplexBackgroundGradient2, GradientLayer::ColorsFieldMask | GradientLayer::PositionsFieldMask | GradientLayer::OrientationFieldMask);

    beginEditCP(ComplexBackgroundGradient3, GradientLayer::ColorsFieldMask | GradientLayer::PositionsFieldMask | GradientLayer::OrientationFieldMask);
        ComplexBackgroundGradient3->getColors().push_back(Color4f(0.0, 0.0, 0.2, 0.2));
		ComplexBackgroundGradient3->getPositions().push_back(0.0);
        ComplexBackgroundGradient3->getColors().push_back(Color4f(0.0, 0.0, 0.2, 0.3));
		ComplexBackgroundGradient3->getPositions().push_back(1.0);
        ComplexBackgroundGradient3->setOrientation(GradientLayer::HORIZONTAL_ORIENTATION);
    endEditCP(ComplexBackgroundGradient3, GradientLayer::ColorsFieldMask | GradientLayer::PositionsFieldMask | GradientLayer::OrientationFieldMask);

    beginEditCP(ComplexBackgroundCompound1, CompoundLayer::BackgroundsFieldMask);
        ComplexBackgroundCompound1->getBackgrounds().push_back(ComplexBackgroundBase);
        ComplexBackgroundCompound1->getBackgrounds().push_back(ComplexBackgroundGradient1);
    endEditCP(ComplexBackgroundCompound1, CompoundLayer::BackgroundsFieldMask);

    beginEditCP(ComplexBackgroundCompound2, CompoundLayer::BackgroundsFieldMask);
        ComplexBackgroundCompound2->getBackgrounds().push_back(ComplexBackgroundGradient2);
        ComplexBackgroundCompound2->getBackgrounds().push_back(ComplexBackgroundGradient3);
    endEditCP(ComplexBackgroundCompound2, CompoundLayer::BackgroundsFieldMask);

    beginEditCP(ComplexBackground, CompoundLayer::BackgroundsFieldMask);
        ComplexBackground->getBackgrounds().push_back(ComplexBackgroundCompound1);
        ComplexBackground->getBackgrounds().push_back(ComplexBackgroundCompound2);
    endEditCP(ComplexBackground, CompoundLayer::BackgroundsFieldMask);

    return ComplexBackground;
}

ChunkMaterialPtr createRedMaterial(void){

    ChunkMaterialPtr RedBackgroundMaterial = ChunkMaterial::create();
    MaterialChunkPtr RedBackgroundMaterialChunk = MaterialChunk::create();
    beginEditCP(RedBackgroundMaterialChunk);
        RedBackgroundMaterialChunk->setAmbient(Color4f(1.0,0.0,0.0,1.0));
        RedBackgroundMaterialChunk->setDiffuse(Color4f(1.0,0.0,0.0,1.0));
        RedBackgroundMaterialChunk->setSpecular(Color4f(1.0,0.0,0.0,1.0));
    endEditCP(RedBackgroundMaterialChunk);

    beginEditCP(RedBackgroundMaterial, ChunkMaterial::ChunksFieldMask);
        RedBackgroundMaterial->addChunk(RedBackgroundMaterialChunk);
    endEditCP(RedBackgroundMaterial, ChunkMaterial::ChunksFieldMask);

    return RedBackgroundMaterial;

}
ChunkMaterialPtr createBlueMaterial(void){

    ChunkMaterialPtr BlueBackgroundMaterial = ChunkMaterial::create();
    MaterialChunkPtr BlueBackgroundMaterialChunk = MaterialChunk::create();
    beginEditCP(BlueBackgroundMaterialChunk);
        BlueBackgroundMaterialChunk->setAmbient(Color4f(0.0,0.0,0.8,1.0));
        BlueBackgroundMaterialChunk->setDiffuse(Color4f(0.0,0.0,0.8,1.0));
        BlueBackgroundMaterialChunk->setSpecular(Color4f(0.0,0.0,0.8,1.0));
    endEditCP(BlueBackgroundMaterialChunk);

    beginEditCP(BlueBackgroundMaterial, ChunkMaterial::ChunksFieldMask);
        BlueBackgroundMaterial->addChunk(BlueBackgroundMaterialChunk);
    endEditCP(BlueBackgroundMaterial, ChunkMaterial::ChunksFieldMask);

    return BlueBackgroundMaterial;

}
ChunkMaterialPtr createGreenMaterial(void){

    ChunkMaterialPtr GreenBackgroundMaterial = ChunkMaterial::create();
    MaterialChunkPtr GreenBackgroundMaterialChunk = MaterialChunk::create();
    beginEditCP(GreenBackgroundMaterialChunk);
        GreenBackgroundMaterialChunk->setAmbient(Color4f(0.0,1.0,0.0,1.0));
        GreenBackgroundMaterialChunk->setDiffuse(Color4f(0.0,1.0,0.0,1.0));
        GreenBackgroundMaterialChunk->setSpecular(Color4f(0.0,1.0,0.0,1.0));
    endEditCP(GreenBackgroundMaterialChunk);

    beginEditCP(GreenBackgroundMaterial, ChunkMaterial::ChunksFieldMask);
        GreenBackgroundMaterial->addChunk(GreenBackgroundMaterialChunk);
    endEditCP(GreenBackgroundMaterial, ChunkMaterial::ChunksFieldMask);

    return GreenBackgroundMaterial;

}

void create3DObjects(void)
{
    // Make Object Nodes
    NodePtr ExampleTorusGeo = makeTorus(90, 270, 16, 16);
    NodePtr ExampleConeGeo = makeCone(150, 50, 16, true, true);
    NodePtr ExampleSphereGeo = makeSphere(4, 100);
    NodePtr ExampleBoxGeo = makeBox(100, 100, 100, 1, 1, 1);

    // AssignTextures
    
    beginEditCP(ExampleConeGeo->getCore());
        Geometry::Ptr::dcast(ExampleConeGeo->getCore())->setMaterial(createBlueMaterial());
    endEditCP(ExampleConeGeo->getCore());    

    beginEditCP(ExampleSphereGeo->getCore());
        Geometry::Ptr::dcast(ExampleSphereGeo->getCore())->setMaterial(createRedMaterial());
    endEditCP(ExampleSphereGeo->getCore());

    beginEditCP(ExampleBoxGeo->getCore());
        Geometry::Ptr::dcast(ExampleBoxGeo->getCore())->setMaterial(createGreenMaterial());
    endEditCP(ExampleBoxGeo->getCore());    

    // Preform transformations on them
    Matrix mat;

    
    // On Torus    
    mat.setTranslate(0.0,100.0,-200.0);
    TransformPtr TorusTranCore = Transform::create();
    beginEditCP(TorusTranCore, Transform::MatrixFieldMask);
        TorusTranCore->setMatrix(mat);
    endEditCP(TorusTranCore, Transform::MatrixFieldMask);
    
    ExampleTorus = Node::create();
    beginEditCP(ExampleTorus, Node::CoreFieldMask | Node::ChildrenFieldMask);
        ExampleTorus->setCore(TorusTranCore);
        ExampleTorus->addChild(ExampleTorusGeo);
    endEditCP(ExampleTorus, Node::CoreFieldMask | Node::ChildrenFieldMask);
    
    // On Sphere
    mat.setTranslate(250.0,0.0,0.0);

    TransformPtr SphereTranCore = Transform::create();
    beginEditCP(SphereTranCore, Transform::MatrixFieldMask);
        SphereTranCore->setMatrix(mat);
    endEditCP(SphereTranCore, Transform::MatrixFieldMask);
    
    ExampleSphere = Node::create();
    beginEditCP(ExampleSphere, Node::CoreFieldMask | Node::ChildrenFieldMask);
        ExampleSphere->setCore(SphereTranCore);
        ExampleSphere->addChild(ExampleSphereGeo);
    endEditCP(ExampleSphere, Node::CoreFieldMask | Node::ChildrenFieldMask);

    // On Cone
    mat.setTranslate(0.0,0.0,-250.0);

    TransformPtr ConeTranCore = Transform::create();
    beginEditCP(ConeTranCore, Transform::MatrixFieldMask);
        ConeTranCore->setMatrix(mat);
    endEditCP(ConeTranCore, Transform::MatrixFieldMask);
    
    ExampleCone = Node::create();
    beginEditCP(ExampleCone, Node::CoreFieldMask | Node::ChildrenFieldMask);
        ExampleCone->setCore(ConeTranCore);
        ExampleCone->addChild(ExampleConeGeo);
    endEditCP(ExampleCone, Node::CoreFieldMask | Node::ChildrenFieldMask);
        
    // On Box
    mat.setTranslate(250.0,250.0,0.0);

    TransformPtr ExampleBoxTranCore = Transform::create();
    beginEditCP(ExampleBoxTranCore, Transform::MatrixFieldMask);
        ExampleBoxTranCore->setMatrix(mat);
    endEditCP(ExampleBoxTranCore, Transform::MatrixFieldMask);
    
    ExampleBox = Node::create();
    beginEditCP(ExampleBox, Node::CoreFieldMask | Node::ChildrenFieldMask);
        ExampleBox->setCore(ExampleBoxTranCore);
        ExampleBox->addChild(ExampleBoxGeo);
    endEditCP(ExampleBox, Node::CoreFieldMask | Node::ChildrenFieldMask);

    addRefCP(ExampleTorus);
    addRefCP(ExampleSphere);
    addRefCP(ExampleBox);
    addRefCP(ExampleCone);
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
