// OpenSG Tutorial Example: Creating a Button Component
//
// This tutorial explains how to edit the basic features of
// a Button created in the OSG User Interface library.
// 
// Includes: Button PreferredSize, MaximumSize, MinimumSize, Font,
// Text,and adding a Button to a Scene.  Also note that clicking
// the Button causes it to appear pressed


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


// 21ExampleInterface Headers
#include "OSGUIRectangle.h"
#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"
#include "OSGGraphics2D.h"
#include "OSGButton.h"
#include "OSGToggleButton.h"
#include "OSGLineBorder.h"
#include "OSGColorLayer.h"
#include "OSGUIFont.h"
#include "OSGAbsoluteLayout.h"
#include "OSGAbsoluteLayoutConstraints.h"
#include "OSGBoxLayout.h"
#include "OSGFlowLayout.h"
#include "OSGGridLayout.h"
#include "OSGComponentContainer.h"
#include "OSGPanel.h"
#include "OSGLineBorder.h"
#include "OSGEmptyBorder.h"
#include "OSGEtchedBorder.h"
#include "OSGLayers.h"
#include "OSGLabel.h"
#include "OSGCheckboxButton.h"
#include "OSGRadioButton.h"
#include "OSGRadioButtonGroup.h"
#include "OSGTextArea.h"
#include "OSGTextField.h"

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

// Create functions create Component Panels to make 
// code easier to read
ComponentRefPtr createLeftPanelButtonPanel(void);
ComponentRefPtr createLeftPanelRadioTextPanel(void);
ComponentRefPtr createRightPanelButtonPanel(void);
ComponentRefPtr createRightPanelCheckPanel(void);
// This function makes a complex Background outside of the main code
// to make code easier to read
LayerRefPtr createComplexBackground(void);
// These functions create materials to use with objects in scene
ChunkMaterialRefPtr createRedMaterial(void);
ChunkMaterialRefPtr createBlueMaterial(void);
ChunkMaterialRefPtr createGreenMaterial(void);
NodeRefPtr scene, ExampleTorus, ExampleCone, ExampleSphere, ExampleBox;
void create3DObjects(void);



// Declare some variables up front 
RadioButtonGroupRefPtr buttonGroup;
TextAreaRefPtr LeftPanelTextArea;

class MakeTorus : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEventUnrecPtr e)
        {         
                scene->addChild(ExampleTorus);
        }

   virtual void buttonDeselected(const ButtonSelectedEventUnrecPtr e)
        {         
                scene->subChild(ExampleTorus);
        }
};
class MakeSphere : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEventUnrecPtr e)
        {         
                scene->addChild(ExampleSphere);
        }

   virtual void buttonDeselected(const ButtonSelectedEventUnrecPtr e)
   {
                scene->subChild(ExampleSphere);
   }
};
class MakeBox : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEventUnrecPtr e)
        {         
                scene->addChild(ExampleBox);
        }

   virtual void buttonDeselected(const ButtonSelectedEventUnrecPtr e)
   {
                scene->subChild(ExampleBox);
   }
};
class MakeCone : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEventUnrecPtr e)
        {         
                scene->addChild(ExampleCone);
        }

   virtual void buttonDeselected(const ButtonSelectedEventUnrecPtr e)
   {
                scene->subChild(ExampleCone);
   }
};


// These classes create Listeners to change Font Color
// in the TextArea
class BlackFont : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEventUnrecPtr e)
    {
            LeftPanelTextArea->setTextColor(Color4f( 0.0, 0.0 , 0.0, 1.0));
            LeftPanelTextArea->setRolloverTextColor(Color4f( 0.0, 0.0 , 0.0, 1.0));
   }

   virtual void buttonDeselected(const ButtonSelectedEventUnrecPtr e)
   {
    
   }
};
class RedFont : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEventUnrecPtr e)
    {

            LeftPanelTextArea->setTextColor(Color4f( 1.0, 0.0 , 0.0, 1.0));
            LeftPanelTextArea->setRolloverTextColor(Color4f( 1.0, 0.0 , 0.0, 1.0));
    
    }

   virtual void buttonDeselected(const ButtonSelectedEventUnrecPtr e)
   {

   }
};
class BlueFont : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEventUnrecPtr e)
    {

            LeftPanelTextArea->setTextColor(Color4f( 0.0, 0.0 , 1.0, 1.0));
            LeftPanelTextArea->setRolloverTextColor(Color4f( 0.0, 0.0 , 1.0, 1.0));
    
    }

   virtual void buttonDeselected(const ButtonSelectedEventUnrecPtr e)
   {

   }
};
class GreenFont : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEventUnrecPtr e)
    {

            LeftPanelTextArea->setTextColor(Color4f( 0.0, 1.0 , 0.0, 1.0));
            LeftPanelTextArea->setRolloverTextColor(Color4f( 0.0, 1.0 , 0.0, 1.0));
    
    }

   virtual void buttonDeselected(const ButtonSelectedEventUnrecPtr e)
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
    virtual void mouseClicked(const MouseEventUnrecPtr e)
    {
    }
    virtual void mouseEntered(const MouseEventUnrecPtr e)
    {
    }
    virtual void mouseExited(const MouseEventUnrecPtr e)
    {
    }
    virtual void mousePressed(const MouseEventUnrecPtr e)
    {
        if(TutorialWindow->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
            mgr->mouseButtonPress(e->getButton(), e->getLocation().x(), e->getLocation().y());
        }
    }
    virtual void mouseReleased(const MouseEventUnrecPtr e)
    {
        if(TutorialWindow->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
           mgr->mouseButtonRelease(e->getButton(), e->getLocation().x(), e->getLocation().y());
        }
    }
};

class TutorialMouseMotionListener : public MouseMotionListener
{
  public:
    virtual void mouseMoved(const MouseEventUnrecPtr e)
    {
        if(TutorialWindow->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
            mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
        }
    }

    virtual void mouseDragged(const MouseEventUnrecPtr e)
    {
        if(TutorialWindow->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
            mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
        }
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

    TutorialMouseListener mouseListener;
    TutorialMouseMotionListener mouseMotionListener;
    TutorialWindow->addMouseListener(&mouseListener);
    TutorialWindow->addMouseMotionListener(&mouseMotionListener);

    TutorialKeyListener TheKeyListener;
    TutorialWindow->addKeyListener(&TheKeyListener);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindow);

    // Set up Window

	//Load in File
	NodeRefPtr LoadedFile = SceneFileHandler::the()->read("C:\\Documents and Settings\\All Users\\Documents\\Cell.osb");

    // Make Main Scene Node
    create3DObjects();
    scene = OSG::Node::create();
        scene->setCore(OSG::Group::create());
		scene->addChild(LoadedFile);

    // Create the Graphics
    GraphicsRefPtr TutorialGraphics = OSG::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

        
    /******************************************************
            
            Create a Background

    ******************************************************/
    ColorLayerRefPtr GreyBackground = OSG::ColorLayer::create();

        GreyBackground->setColor(Color4f(.93,.93,.93,1.0));


    /******************************************************
            
            Create some Borders

    ******************************************************/
    LineBorderRefPtr PanelBorder = OSG::LineBorder::create();
    EmptyBorderRefPtr Panel1Border = OSG::EmptyBorder::create();
    EmptyBorderRefPtr Panel2Border = OSG::EmptyBorder::create();
    EmptyBorderRefPtr emptyBorder = OSG::EmptyBorder::create();
    
        PanelBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
        PanelBorder->setWidth(1);

        Panel1Border->setTopWidth(0);
        Panel1Border->setBottomWidth(6);
        Panel1Border->setLeftWidth(0);
        Panel1Border->setRightWidth(0);
        Panel2Border->setTopWidth(0);
        Panel2Border->setBottomWidth(0);
        Panel2Border->setLeftWidth(0);
        Panel2Border->setRightWidth(0);
    

    /******************************************************

            Create some Labels and stuff to go 
            with them

    ******************************************************/
    LabelRefPtr LeftPanelLabel1 = OSG::Label::create();
    UIFontRefPtr LeftPanelLabel1Font = OSG::UIFont::create();

        LeftPanelLabel1Font->setSize(50);

        LeftPanelLabel1->setBorders(emptyBorder);
        LeftPanelLabel1->setBackgrounds(GreyBackground);
        LeftPanelLabel1->setFont(LeftPanelLabel1Font);
        LeftPanelLabel1->setText("OSG Gui");
        LeftPanelLabel1->setPreferredSize(Vec2f(300, 100));
		LeftPanelLabel1->setAlignment(Vec2f(0.0f, 0.5f));

     /******************************************************

            Create some Layouts

    ******************************************************/
    BoxLayoutRefPtr MainInternalWindowLayout = OSG::BoxLayout::create();
    FlowLayoutRefPtr LeftPanelLayout = OSG::FlowLayout::create();
    BoxLayoutRefPtr RightPanelLayout = OSG::BoxLayout::create();
        MainInternalWindowLayout->setOrientation(BoxLayout::HORIZONTAL_ORIENTATION);

        LeftPanelLayout->setOrientation(FlowLayout::HORIZONTAL_ORIENTATION);
        LeftPanelLayout->setMinorAxisAlignment(1.0f);

        RightPanelLayout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);
    

    /******************************************************

        Create MainFrame and Panels

    ******************************************************/
    PanelRefPtr LeftPanel = OSG::Panel::create();
    PanelRefPtr RightPanel = OSG::Panel::create();

    // LeftPanel stuff
        LeftPanel->setPreferredSize(Vec2f(400, 500));
        LeftPanel->pushToChildren(LeftPanelLabel1);
        LeftPanel->pushToChildren(createLeftPanelButtonPanel());
        LeftPanel->pushToChildren(createLeftPanelRadioTextPanel());
        LeftPanel->setLayout(LeftPanelLayout);
        LeftPanel->setBackgrounds(GreyBackground);
        LeftPanel->setBorders(Panel1Border);

    //RightPanel stuff
        RightPanel->setPreferredSize(Vec2f(200, 620));
        RightPanel->pushToChildren(createRightPanelButtonPanel());
        RightPanel->pushToChildren(createRightPanelCheckPanel());
        RightPanel->setLayout(RightPanelLayout);
        RightPanel->setBackgrounds(GreyBackground);
        RightPanel->setBorders(Panel2Border);
    
    // Create The Main InternalWindow
    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
       MainInternalWindow->pushToChildren(LeftPanel);
       MainInternalWindow->pushToChildren(RightPanel);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(GreyBackground);
       MainInternalWindow->setBorders(PanelBorder);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(1.0f,1.0f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);

    // Create the Drawing Surface
    UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);
    
	TutorialDrawingSurface->openWindow(MainInternalWindow);

    // Make A 3D Rectangle to draw the UI on
    UIRectangleRefPtr UIRectCore = UIRectangle::create();
        UIRectCore->setPoint(Pnt3f(-310.0,-310.0,370.0));
        UIRectCore->setWidth(620);
        UIRectCore->setHeight(620);
        UIRectCore->setDrawingSurface(TutorialDrawingSurface);
    
    NodeRefPtr UIRectNode = OSG::Node::create();
        UIRectNode->setCore(UIRectCore);
    
        // add the UIRect as a child
        scene->addChild(UIRectNode);


    mgr->setRoot(scene);

    // Show the whole Scene
    mgr->showAll();

    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
            WinSize,
            "21ExampleInterface");

    //Enter main Loop
    TutorialWindow->mainLoop();

    osgExit();

    return 0;
}


ComponentRefPtr createLeftPanelButtonPanel(void)

{

    // Create Label for this Panel
    LabelRefPtr LeftPanelButtonPanelLabel = OSG::Label::create();

        LeftPanelButtonPanelLabel->setTextColor(Color4f(1.0,1.0,1.0,1.0));
        LeftPanelButtonPanelLabel->setRolloverTextColor(Color4f(1.0,1.0,1.0,1.0));
        LeftPanelButtonPanelLabel->setBackground(createComplexBackground());
        LeftPanelButtonPanelLabel->setPreferredSize(Vec2f(100, 50));
        LeftPanelButtonPanelLabel->setText("Various Options");
		LeftPanelButtonPanelLabel->setAlignment(Vec2f(0.5,0.5));

    // Create and edit the Panel buttons
    ButtonRefPtr LeftPanelButton1 = OSG::Button::create();
    ButtonRefPtr LeftPanelButton2 = OSG::Button::create();
    ButtonRefPtr LeftPanelButton3 = OSG::Button::create();
    ButtonRefPtr LeftPanelButton4 = OSG::Button::create();
    ButtonRefPtr LeftPanelButton5 = OSG::Button::create();
    ButtonRefPtr LeftPanelButton6 = OSG::Button::create();

        LeftPanelButton1->setText("This");
        LeftPanelButton1->setPreferredSize(Vec2f(100,50));
    
        LeftPanelButton2->setText("is");
        LeftPanelButton2->setPreferredSize(Vec2f(100,50));

        LeftPanelButton3->setText("an");
        LeftPanelButton3->setPreferredSize(Vec2f(100,50));

        LeftPanelButton4->setText("example");
        LeftPanelButton4->setPreferredSize(Vec2f(100,50));

        LeftPanelButton5->setText("user");
        LeftPanelButton5->setPreferredSize(Vec2f(100,50));
    
        LeftPanelButton6->setText("interface.");
        LeftPanelButton6->setPreferredSize(Vec2f(100,50));
    

    // Create and edit Panel layout
    BoxLayoutRefPtr LeftPanelButtonPanelLayout = OSG::BoxLayout::create();
        LeftPanelButtonPanelLayout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);

    // Create an edit Panel Background
    ColorLayerRefPtr LeftPanelButtonPanelBackground = OSG::ColorLayer::create();
        LeftPanelButtonPanelBackground->setColor(Color4f(0.93,0.93,0.93,1.0));

    // Create Panel Border
    LineBorderRefPtr LeftPanelBorder = OSG::LineBorder::create();
        LeftPanelBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
        LeftPanelBorder->setWidth(1);

    // Create and edit Panel
    PanelRefPtr LeftPanelButtonPanel = OSG::Panel::create();
        LeftPanelButtonPanel->setPreferredSize(Vec2f(180, 500));
        LeftPanelButtonPanel->pushToChildren(LeftPanelButtonPanelLabel);
        LeftPanelButtonPanel->pushToChildren(LeftPanelButton1);
        LeftPanelButtonPanel->pushToChildren(LeftPanelButton2);
        LeftPanelButtonPanel->pushToChildren(LeftPanelButton3);
        LeftPanelButtonPanel->pushToChildren(LeftPanelButton4);
        LeftPanelButtonPanel->pushToChildren(LeftPanelButton5);
        LeftPanelButtonPanel->pushToChildren(LeftPanelButton6);
        LeftPanelButtonPanel->setLayout(LeftPanelButtonPanelLayout);
        LeftPanelButtonPanel->setBackgrounds(LeftPanelButtonPanelBackground);
        LeftPanelButtonPanel->setBorders(LeftPanelBorder);

    return LeftPanelButtonPanel;
}




ComponentRefPtr createLeftPanelRadioTextPanel(void)
{

    // Create the RadioButton group
    RadioButtonRefPtr RadioButton1 = OSG::RadioButton::create();
    RadioButtonRefPtr RadioButton2 = OSG::RadioButton::create();
    RadioButtonRefPtr RadioButton3 = OSG::RadioButton::create();
    RadioButtonRefPtr RadioButton4 = OSG::RadioButton::create();

        RadioButton1->setAlignment(Vec2f(0.0,0.5));
        RadioButton1->setPreferredSize(Vec2f(100, 40));
        RadioButton1->setText("Black Text");
        RadioButton1->setToolTipText("Set TextArea text black");
    RadioButton1->addButtonSelectedListener(&RadioButton1Listener);

        RadioButton2->setAlignment(Vec2f(0.0,0.5));
        RadioButton2->setPreferredSize(Vec2f(100, 40));
        RadioButton2->setText("Red Text");
        RadioButton2->setToolTipText("Set TextArea text red");
    RadioButton2->addButtonSelectedListener(&RadioButton2Listener);

        RadioButton3->setAlignment(Vec2f(0.0,0.5));
        RadioButton3->setPreferredSize(Vec2f(100, 40));
        RadioButton3->setText("Green Text");
        RadioButton3->setToolTipText("Set TextArea text green");
    RadioButton3->addButtonSelectedListener(&RadioButton3Listener);

        RadioButton4->setAlignment(Vec2f(0.0,0.5));
        RadioButton4->setPreferredSize(Vec2f(100, 40));
        RadioButton4->setText("Blue Text");
        RadioButton4->setToolTipText("Set TextArea text blue");
    RadioButton4->addButtonSelectedListener(&RadioButton4Listener);

    buttonGroup = RadioButtonGroup::create();
    buttonGroup->addButton(RadioButton1);
    buttonGroup->addButton(RadioButton2);
    buttonGroup->addButton(RadioButton3);
    buttonGroup->addButton(RadioButton4);


    // Create TextArea
    LeftPanelTextArea = OSG::TextArea::create();
        LeftPanelTextArea->setPreferredSize(Vec2f(125, 200));

    // Create Panel and its Background/Border to label TextField
    LabelRefPtr LeftPanelTextFieldLabel = OSG::Label::create();
    EmptyLayerRefPtr LeftPanelTextFieldLabelBackground = OSG::EmptyLayer::create();
    EmptyBorderRefPtr LeftPanelTextFieldLabelBorder = OSG::EmptyBorder::create();
        LeftPanelTextFieldLabel->setPreferredSize(Vec2f(100, 25));
        LeftPanelTextFieldLabel->setBorders(LeftPanelTextFieldLabelBorder);
        LeftPanelTextFieldLabel->setBackgrounds(LeftPanelTextFieldLabelBackground);
        LeftPanelTextFieldLabel->setText("Text Field");

    // Create TextField
    TextFieldRefPtr LeftPanelTextField = OSG::TextField::create();
        LeftPanelTextField->setPreferredSize(Vec2f(125.0f, 22.0f));

    
    // Create an edit Panel Background
    ColorLayerRefPtr LeftPanelRadioTextPanelBackground = OSG::ColorLayer::create();
        LeftPanelRadioTextPanelBackground->setColor(Color4f(0.93f,0.93f,0.93f,1.0f));

    // Create and edit Panel layouts
    FlowLayoutRefPtr LeftPanelRadioTextPanelLayout = OSG::FlowLayout::create();
    FlowLayoutRefPtr LeftPanelRadioTextPanelRadioPanelLayout = OSG::FlowLayout::create();
    FlowLayoutRefPtr LeftPanelRadioTextPanelTextPanelLayout = OSG::FlowLayout::create();
        LeftPanelRadioTextPanelLayout->setMinorAxisAlignment(0.0f);

    // Create two Panels for this Panel
    PanelRefPtr LeftPanelRadioTextPanelRadioPanel = OSG::Panel::create();
    PanelRefPtr LeftPanelRadioTextPanelTextPanel = OSG::Panel::create();

    // Create some Borders
    EmptyBorderRefPtr LeftPanelRadioTextPanelRadioPanelBorder = OSG::EmptyBorder::create();

        LeftPanelRadioTextPanelRadioPanel->setBorders(LeftPanelRadioTextPanelRadioPanelBorder);
        LeftPanelRadioTextPanelRadioPanel->setPreferredSize(Vec2f(125, 200));
        LeftPanelRadioTextPanelRadioPanel->setLayout(LeftPanelRadioTextPanelRadioPanelLayout);
        LeftPanelRadioTextPanelRadioPanel->setBackgrounds(LeftPanelRadioTextPanelBackground);
        LeftPanelRadioTextPanelRadioPanel->pushToChildren(RadioButton1);
        LeftPanelRadioTextPanelRadioPanel->pushToChildren(RadioButton2);
        LeftPanelRadioTextPanelRadioPanel->pushToChildren(RadioButton3);
        LeftPanelRadioTextPanelRadioPanel->pushToChildren(RadioButton4);

    // Create Panel Border
    LineBorderRefPtr PanelBorder1 = OSG::LineBorder::create();
        PanelBorder1->setColor(Color4f(0.0,0.0,0.0,1.0));
        PanelBorder1->setWidth(1);

    // Create and edit Panel
    PanelRefPtr LeftPanelRadioTextPanel = OSG::Panel::create();
        LeftPanelRadioTextPanel->setPreferredSize(Vec2f(180, 500));
        LeftPanelRadioTextPanel->pushToChildren(LeftPanelRadioTextPanelRadioPanel);
        LeftPanelRadioTextPanel->pushToChildren(LeftPanelTextArea);
        LeftPanelRadioTextPanel->pushToChildren(LeftPanelTextFieldLabel);
        LeftPanelRadioTextPanel->pushToChildren(LeftPanelTextField);
        LeftPanelRadioTextPanel->setLayout(LeftPanelRadioTextPanelLayout);
        LeftPanelRadioTextPanel->setBackgrounds(LeftPanelRadioTextPanelBackground);
        LeftPanelRadioTextPanel->setBorders(PanelBorder1);

    return LeftPanelRadioTextPanel;
}
ComponentRefPtr createRightPanelButtonPanel(void)
{
    // Create and edit the Panel Buttons
    ToggleButtonRefPtr RightPanelButton1 = OSG::ToggleButton::create();
    ToggleButtonRefPtr RightPanelButton2 = OSG::ToggleButton::create();
    ToggleButtonRefPtr RightPanelButton3 = OSG::ToggleButton::create();
    ToggleButtonRefPtr RightPanelButton4 = OSG::ToggleButton::create();

        RightPanelButton1->setText("These");
        RightPanelButton1->setPreferredSize(Vec2f(100,50));
    
        RightPanelButton2->setText("are");
        RightPanelButton2->setPreferredSize(Vec2f(100,50));

        RightPanelButton3->setText("toggle");
        RightPanelButton3->setPreferredSize(Vec2f(100,50));

        RightPanelButton4->setText("buttons");
        RightPanelButton4->setPreferredSize(Vec2f(100,50));


    // Create an edit Panel Background
    ColorLayerRefPtr RightPanelButtonPanelBackground = OSG::ColorLayer::create();
        RightPanelButtonPanelBackground->setColor(Color4f(0.93,0.93,0.93,1.0));

    // Create and edit Panel layout
    BoxLayoutRefPtr RightPanelButtonPanelLayout = OSG::BoxLayout::create();
        RightPanelButtonPanelLayout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);

    // Create Panel Border
    LineBorderRefPtr PanelBorder2 = OSG::LineBorder::create();
        PanelBorder2->setColor(Color4f(0.0,0.0,0.0,1.0));
        PanelBorder2->setWidth(1);

    // Create and edit Panel
    PanelRefPtr RightPanelButtonPanel = OSG::Panel::create();
        RightPanelButtonPanel->setPreferredSize(Vec2f(200, 300));
        RightPanelButtonPanel->pushToChildren(RightPanelButton1);
        RightPanelButtonPanel->pushToChildren(RightPanelButton2);
        RightPanelButtonPanel->pushToChildren(RightPanelButton3);
        RightPanelButtonPanel->pushToChildren(RightPanelButton4);
        RightPanelButtonPanel->setLayout(RightPanelButtonPanelLayout);
        RightPanelButtonPanel->setBackgrounds(RightPanelButtonPanelBackground);
        RightPanelButtonPanel->setBorders(PanelBorder2);

    return RightPanelButtonPanel;

}
ComponentRefPtr createRightPanelCheckPanel(void)
{
    // Create and edit the CheckBoxes
    CheckboxButtonRefPtr RightPanelCheck1 = OSG::CheckboxButton::create();
    CheckboxButtonRefPtr RightPanelCheck2 = OSG::CheckboxButton::create();
    CheckboxButtonRefPtr RightPanelCheck3 = OSG::CheckboxButton::create();
    CheckboxButtonRefPtr RightPanelCheck4 = OSG::CheckboxButton::create();
	//NOTE HorizontalAlignment needs to be changed to Alignment only with Vec2f arg
        RightPanelCheck1->setText("Show Torus");
        RightPanelCheck1->setPreferredSize(Vec2f(125,50));
        RightPanelCheck1->setAlignment(0.0);
        // Add Listener
        RightPanelCheck1->addButtonSelectedListener(&RightPanelCheck1Listener);
    
        RightPanelCheck2->setText("Show Box");
        RightPanelCheck2->setPreferredSize(Vec2f(125,50));
        RightPanelCheck2->setAlignment(Vec2f (0.5,0.0));
        // Add Listener
        RightPanelCheck2->addButtonSelectedListener(&RightPanelCheck2Listener);

        RightPanelCheck3->setText("Show Sphere");
        RightPanelCheck3->setPreferredSize(Vec2f(125,50));
        RightPanelCheck3->setAlignment(Vec2f(0.0,0.0));
        // Add Listener
        RightPanelCheck3->addButtonSelectedListener(&RightPanelCheck3Listener);

        RightPanelCheck4->setText("Show Cone");
        RightPanelCheck4->setPreferredSize(Vec2f(125,50));
        RightPanelCheck4->setAlignment(Vec2f(0.0,0.0));
        // Add Listener
        RightPanelCheck4->addButtonSelectedListener(&RightPanelCheck4Listener);

    // Create an edit Panel Background
    ColorLayerRefPtr RightPanelCheckPanelBackground = OSG::ColorLayer::create();
        RightPanelCheckPanelBackground->setColor(Color4f(0.93,0.93,0.93,1.0));

    // Create and edit Panel layout
    BoxLayoutRefPtr RightPanelCheckPanelLayout = OSG::BoxLayout::create();
        RightPanelCheckPanelLayout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);
        RightPanelCheckPanelLayout->setMinorAxisAlignment(0.5f);

    // Create Panel Border
    LineBorderRefPtr PanelBorder3 = OSG::LineBorder::create();
        PanelBorder3->setColor(Color4f(0.0,0.0,0.0,1.0));
        PanelBorder3->setWidth(1);

    // Create and edit Panel
    PanelRefPtr RightPanelCheckPanel = OSG::Panel::create();
        RightPanelCheckPanel->setPreferredSize(Vec2f(200, 300));
        RightPanelCheckPanel->pushToChildren(RightPanelCheck1);
        RightPanelCheckPanel->pushToChildren(RightPanelCheck2);
        RightPanelCheckPanel->pushToChildren(RightPanelCheck3);
        RightPanelCheckPanel->pushToChildren(RightPanelCheck4);
        RightPanelCheckPanel->setLayout(RightPanelCheckPanelLayout);
        RightPanelCheckPanel->setBackgrounds(RightPanelCheckPanelBackground);
        RightPanelCheckPanel->setBorders(PanelBorder3);

    return RightPanelCheckPanel;
}
LayerRefPtr createComplexBackground(void)
{

    // Create complex Background 
    ColorLayerRefPtr ComplexBackgroundBase = OSG::ColorLayer::create();
    GradientLayerRefPtr ComplexBackgroundGradient1 = OSG::GradientLayer::create();
    GradientLayerRefPtr ComplexBackgroundGradient2 = OSG::GradientLayer::create();
    GradientLayerRefPtr ComplexBackgroundGradient3 = OSG::GradientLayer::create();
    CompoundLayerRefPtr ComplexBackgroundCompound1 = OSG::CompoundLayer::create();
    CompoundLayerRefPtr ComplexBackgroundCompound2 = OSG::CompoundLayer::create();
    CompoundLayerRefPtr ComplexBackground = OSG::CompoundLayer::create();

        ComplexBackgroundBase->setColor(Color4f(0.0, 0.0, .25, 1.0));

        ComplexBackgroundGradient1->editMFColors()->push_back(Color4f(1.0, 0.0, 0.0, 0.5));
		ComplexBackgroundGradient1->editMFStops()->push_back(0.0);
        ComplexBackgroundGradient1->editMFColors()->push_back(Color4f(0.5, 0.0, 0.0, 0.3));
		ComplexBackgroundGradient1->editMFStops()->push_back(1.0);
        ComplexBackgroundGradient1->setStartPosition(Vec2f(0.0f,0.0f));
        ComplexBackgroundGradient1->setEndPosition(Vec2f(1.0f,0.0f));

        ComplexBackgroundGradient2->editMFColors()->push_back(Color4f(.6, 0.0, 0.3, 1.0));
		ComplexBackgroundGradient2->editMFStops()->push_back(0.0);
        ComplexBackgroundGradient2->editMFColors()->push_back(Color4f(.2, 0.0, 0.3, 0.5));
		ComplexBackgroundGradient2->editMFStops()->push_back(1.0);
        ComplexBackgroundGradient2->setStartPosition(Vec2f(0.0f,0.0f));
        ComplexBackgroundGradient2->setEndPosition(Vec2f(0.0f,1.0f));

        ComplexBackgroundGradient3->editMFColors()->push_back(Color4f(0.0, 0.0, 0.2, 0.2));
		ComplexBackgroundGradient3->editMFStops()->push_back(0.0);
        ComplexBackgroundGradient3->editMFColors()->push_back(Color4f(0.0, 0.0, 0.2, 0.3));
		ComplexBackgroundGradient3->editMFStops()->push_back(1.0);
        ComplexBackgroundGradient3->setStartPosition(Vec2f(0.0f,0.0f));
        ComplexBackgroundGradient3->setEndPosition(Vec2f(1.0f,0.0f));

        ComplexBackgroundCompound1->pushToBackgrounds(ComplexBackgroundBase);
        ComplexBackgroundCompound1->pushToBackgrounds(ComplexBackgroundGradient1);

        ComplexBackgroundCompound2->pushToBackgrounds(ComplexBackgroundGradient2);
        ComplexBackgroundCompound2->pushToBackgrounds(ComplexBackgroundGradient3);

        ComplexBackground->pushToBackgrounds(ComplexBackgroundCompound1);
        ComplexBackground->pushToBackgrounds(ComplexBackgroundCompound2);

    return ComplexBackground;
}

ChunkMaterialRefPtr createRedMaterial(void){

    ChunkMaterialRefPtr RedBackgroundMaterial = ChunkMaterial::create();
    MaterialChunkRefPtr RedBackgroundMaterialChunk = MaterialChunk::create();
        RedBackgroundMaterialChunk->setAmbient(Color4f(1.0,0.0,0.0,1.0));
        RedBackgroundMaterialChunk->setDiffuse(Color4f(1.0,0.0,0.0,1.0));
        RedBackgroundMaterialChunk->setSpecular(Color4f(1.0,0.0,0.0,1.0));

        RedBackgroundMaterial->addChunk(RedBackgroundMaterialChunk);

    return RedBackgroundMaterial;

}
ChunkMaterialRefPtr createBlueMaterial(void){

    ChunkMaterialRefPtr BlueBackgroundMaterial = ChunkMaterial::create();
    MaterialChunkRefPtr BlueBackgroundMaterialChunk = MaterialChunk::create();
        BlueBackgroundMaterialChunk->setAmbient(Color4f(0.0,0.0,0.8,1.0));
        BlueBackgroundMaterialChunk->setDiffuse(Color4f(0.0,0.0,0.8,1.0));
        BlueBackgroundMaterialChunk->setSpecular(Color4f(0.0,0.0,0.8,1.0));

        BlueBackgroundMaterial->addChunk(BlueBackgroundMaterialChunk);

    return BlueBackgroundMaterial;

}
ChunkMaterialRefPtr createGreenMaterial(void){

    ChunkMaterialRefPtr GreenBackgroundMaterial = ChunkMaterial::create();
    MaterialChunkRefPtr GreenBackgroundMaterialChunk = MaterialChunk::create();
        GreenBackgroundMaterialChunk->setAmbient(Color4f(0.0,1.0,0.0,1.0));
        GreenBackgroundMaterialChunk->setDiffuse(Color4f(0.0,1.0,0.0,1.0));
        GreenBackgroundMaterialChunk->setSpecular(Color4f(0.0,1.0,0.0,1.0));

        GreenBackgroundMaterial->addChunk(GreenBackgroundMaterialChunk);

    return GreenBackgroundMaterial;

}

void create3DObjects(void)
{
    // Make Object Nodes
    NodeRefPtr ExampleTorusGeo = makeTorus(90, 270, 16, 16);
    NodeRefPtr ExampleConeGeo = makeCone(150, 50, 16, true, true);
    NodeRefPtr ExampleSphereGeo = makeSphere(4, 100);
    NodeRefPtr ExampleBoxGeo = makeBox(100, 100, 100, 1, 1, 1);

    // AssignTextures

    dynamic_cast<Geometry*>(ExampleConeGeo->getCore())->setMaterial(createBlueMaterial());

    dynamic_cast<Geometry*>(ExampleSphereGeo->getCore())->setMaterial(createRedMaterial());

    dynamic_cast<Geometry*>(ExampleBoxGeo->getCore())->setMaterial(createGreenMaterial());

    // Preform transformations on them
    Matrix mat;

    
    // On Torus    
    mat.setTranslate(0.0,100.0,-200.0);
    TransformRefPtr TorusTranCore = Transform::create();
        TorusTranCore->setMatrix(mat);
    
    ExampleTorus = Node::create();
        ExampleTorus->setCore(TorusTranCore);
        ExampleTorus->addChild(ExampleTorusGeo);
    
    // On Sphere
    mat.setTranslate(250.0,0.0,0.0);

    TransformRefPtr SphereTranCore = Transform::create();
        SphereTranCore->setMatrix(mat);
    
    ExampleSphere = Node::create();
        ExampleSphere->setCore(SphereTranCore);
        ExampleSphere->addChild(ExampleSphereGeo);

    // On Cone
    mat.setTranslate(0.0,0.0,-250.0);

    TransformRefPtr ConeTranCore = Transform::create();
        ConeTranCore->setMatrix(mat);
    
    ExampleCone = Node::create();
        ExampleCone->setCore(ConeTranCore);
        ExampleCone->addChild(ExampleConeGeo);
        
    // On Box
    mat.setTranslate(250.0,250.0,0.0);

    TransformRefPtr ExampleBoxTranCore = Transform::create();
        ExampleBoxTranCore->setMatrix(mat);
    
    ExampleBox = Node::create();
        ExampleBox->setCore(ExampleBoxTranCore);
        ExampleBox->addChild(ExampleBoxGeo);

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
