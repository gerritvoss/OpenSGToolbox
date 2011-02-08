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

// Input
#include "OSGWindowUtils.h"

// UserInterface Headers
#include "OSGUIForeground.h"
#include "OSGUIDrawingSurface.h"
#include "OSGGraphics2D.h"
#include "OSGLookAndFeelManager.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);


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

void keyPressed(KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
}

// Create functions create Component Panels to make 
// code easier to read
PanelTransitPtr createLeftPanelButtonPanel(void);
PanelTransitPtr createLeftPanelRadioTextPanel(void);
PanelTransitPtr createRightPanelButtonPanel(void);
PanelTransitPtr createRightPanelCheckPanel(Node* const TorusNode,
                                           Node* const SphereNode,
                                           Node* const ConeNode,
                                           Node* const BoxNode);

// This function makes a complex Background outside of the main code
// to make code easier to read
LayerTransitPtr createComplexBackground(void);

// These functions create materials to use with objects in scene
ChunkMaterialTransitPtr createMaterial(const Color4f& TheColor);

NodeTransitPtr createTorus(void);
NodeTransitPtr createCone(void);
NodeTransitPtr createSphere(void);
NodeTransitPtr createBox(void);

void setNodeTravMask(Node* const NodeToChange,
                     UInt32 Mask)
{         
    NodeToChange->setTravMask(Mask);
}

void setTextColors(TextArea* const TextAreaToChange,
                   Color4f TheColor)
{         
    TextAreaToChange->setTextColor(TheColor);
    TextAreaToChange->setRolloverTextColor(TheColor);
}

void mousePressed(MouseEventDetails* const details,
                  SimpleSceneManager *mgr)
{
    if(dynamic_cast<WindowEventProducer*>(details->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_CAPS_LOCK)
    {
        mgr->mouseButtonPress(details->getButton(), details->getLocation().x(), details->getLocation().y());
    }
}

void mouseReleased(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    if(dynamic_cast<WindowEventProducer*>(details->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_CAPS_LOCK)
    {
        mgr->mouseButtonRelease(details->getButton(), details->getLocation().x(), details->getLocation().y());
    }
}

void mouseDragged(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    if(dynamic_cast<WindowEventProducer*>(details->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_CAPS_LOCK)
    {
        mgr->mouseMove(details->getLocation().x(), details->getLocation().y());
    }
}

void mouseWheelMoved(MouseWheelEventDetails* const details, SimpleSceneManager *mgr)
{
    if(dynamic_cast<WindowEventProducer*>(details->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_CAPS_LOCK)
    {
        for(UInt32 i(0) ; i<abs(details->getUnitsToScroll()) ;++i)
        {
            if(details->getUnitsToScroll() > 0)
            {
                mgr->mouseButtonPress(SimpleSceneManager::MouseDown,details->getLocation().x(),details->getLocation().y());
            }
            else if(details->getUnitsToScroll() < 0)
            {
                mgr->mouseButtonPress(SimpleSceneManager::MouseUp,details->getLocation().x(),details->getLocation().y());
            }
        }
    }
}

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    {
        // Set up Window
        WindowEventProducerRecPtr TutorialWindow = createNativeWindow();
        TutorialWindow->initWindow();

        // Create the SimpleSceneManager helper
        SimpleSceneManager sceneManager;
        TutorialWindow->setDisplayCallback(boost::bind(display, &sceneManager));
        TutorialWindow->setReshapeCallback(boost::bind(reshape, _1, &sceneManager));

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

        TutorialWindow->connectMousePressed(boost::bind(mousePressed, _1, &sceneManager));
        TutorialWindow->connectMouseReleased(boost::bind(mouseReleased, _1, &sceneManager));
        TutorialWindow->connectMouseDragged(boost::bind(mouseDragged, _1, &sceneManager));
        TutorialWindow->connectMouseWheelMoved(boost::bind(mouseWheelMoved, _1, &sceneManager));
        TutorialWindow->connectKeyTyped(boost::bind(keyPressed, _1));

        // Make Main Scene Node
        NodeRecPtr Scene = makeCoredNode<Group>();
        
        NodeRecPtr TorusNode  = createTorus();
        NodeRecPtr SphereNode = createSphere();
        NodeRecPtr ConeNode   = createCone();
        NodeRecPtr BoxNode    = createBox();

        Scene->addChild(TorusNode);
        Scene->addChild(SphereNode);
        Scene->addChild(ConeNode);
        Scene->addChild(BoxNode);

        // Create the Graphics
        GraphicsRecPtr TutorialGraphics = Graphics2D::create();

        // Initialize the LookAndFeelManager to enable default settings
        LookAndFeelManager::the()->getLookAndFeel()->init();


        /******************************************************

          Create a Background

         ******************************************************/
        ColorLayerRecPtr GreyBackground = ColorLayer::create();

        GreyBackground->setColor(Color4f(.93,.93,.93,1.0));


        /******************************************************

          Create some Borders

         ******************************************************/
        LineBorderRecPtr PanelBorder = LineBorder::create();
        EmptyBorderRecPtr Panel1Border = EmptyBorder::create();
        EmptyBorderRecPtr Panel2Border = EmptyBorder::create();
        EmptyBorderRecPtr emptyBorder = EmptyBorder::create();

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
        LabelRecPtr LeftPanelLabel1 = Label::create();
        UIFontRecPtr LeftPanelLabel1Font = UIFont::create();

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
        BoxLayoutRecPtr MainInternalWindowLayout = BoxLayout::create();
        FlowLayoutRecPtr LeftPanelLayout = FlowLayout::create();
        BoxLayoutRecPtr RightPanelLayout = BoxLayout::create();
        MainInternalWindowLayout->setOrientation(BoxLayout::HORIZONTAL_ORIENTATION);

        LeftPanelLayout->setOrientation(FlowLayout::HORIZONTAL_ORIENTATION);
        LeftPanelLayout->setMinorAxisAlignment(1.0f);

        RightPanelLayout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);


        /******************************************************

          Create MainFrame and Panels

         ******************************************************/
        PanelRecPtr LeftPanel = Panel::createEmpty();
        PanelRecPtr RightPanel = Panel::createEmpty();

        // LeftPanel stuff
        LeftPanel->setPreferredSize(Vec2f(400, 500));
        LeftPanel->pushToChildren(LeftPanelLabel1);
        PanelRecPtr LeftPanelButtonPanel = createLeftPanelButtonPanel();
        LeftPanel->pushToChildren(LeftPanelButtonPanel);
        PanelRecPtr LeftPanelRadioTextPanel = createLeftPanelRadioTextPanel();
        LeftPanel->pushToChildren(LeftPanelRadioTextPanel);
        LeftPanel->setLayout(LeftPanelLayout);
        LeftPanel->setBackgrounds(GreyBackground);
        LeftPanel->setBorders(Panel1Border);

        //RightPanel stuff
        RightPanel->setPreferredSize(Vec2f(200, 620));
        PanelRecPtr RightPanelButtonPanel = createRightPanelButtonPanel();
        RightPanel->pushToChildren(RightPanelButtonPanel);
        PanelRecPtr RightPanelCheckPanel = createRightPanelCheckPanel(TorusNode,
                                                                      SphereNode,
                                                                      ConeNode,  
                                                                      BoxNode);  
        RightPanel->pushToChildren(RightPanelCheckPanel);
        RightPanel->setLayout(RightPanelLayout);
        RightPanel->setBackgrounds(GreyBackground);
        RightPanel->setBorders(Panel2Border);

        // Create The Main InternalWindow
        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
        MainInternalWindow->pushToChildren(LeftPanel);
        MainInternalWindow->pushToChildren(RightPanel);
        MainInternalWindow->setLayout(MainInternalWindowLayout);
        MainInternalWindow->setBackgrounds(GreyBackground);
        MainInternalWindow->setBorders(PanelBorder);
        MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setScalingInDrawingSurface(Vec2f(1.0f,1.0f));
        MainInternalWindow->setDrawTitlebar(false);
        MainInternalWindow->setResizable(false);
        //MainInternalWindow->setOpacity(0.7f);

        // Create the Drawing Surface
        UIDrawingSurfaceRecPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);

        TutorialDrawingSurface->openWindow(MainInternalWindow);

        // Make A 3D Rectangle to draw the UI on
        UIRectangleRecPtr UIRectCore = UIRectangle::create();
        UIRectCore->setPoint(Pnt3f(-310.0,-310.0,370.0));
        UIRectCore->setWidth(620);
        UIRectCore->setHeight(620);
        UIRectCore->setDrawingSurface(TutorialDrawingSurface);

        NodeRecPtr UIRectNode = Node::create();
        UIRectNode->setCore(UIRectCore);

        // add the UIRect as a child
        Scene->addChild(UIRectNode);


        sceneManager.setRoot(Scene);

        // Show the whole Scene
        sceneManager.showAll();

        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "21ExampleInterface");

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}


PanelTransitPtr createLeftPanelButtonPanel(void)
{
    // Create Label for this Panel
    LabelRecPtr LeftPanelButtonPanelLabel = Label::create();

    LeftPanelButtonPanelLabel->setTextColor(Color4f(1.0,1.0,1.0,1.0));
    LeftPanelButtonPanelLabel->setRolloverTextColor(Color4f(1.0,1.0,1.0,1.0));
    LayerRecPtr ComplexBackground = createComplexBackground();
    LeftPanelButtonPanelLabel->setBackground(ComplexBackground);
    LeftPanelButtonPanelLabel->setPreferredSize(Vec2f(100, 50));
    LeftPanelButtonPanelLabel->setText("Various Options");
    LeftPanelButtonPanelLabel->setAlignment(Vec2f(0.5,0.5));

    // Create and edit the Panel buttons
    ButtonRecPtr LeftPanelButton1 = Button::create();
    ButtonRecPtr LeftPanelButton2 = Button::create();
    ButtonRecPtr LeftPanelButton3 = Button::create();
    ButtonRecPtr LeftPanelButton4 = Button::create();
    ButtonRecPtr LeftPanelButton5 = Button::create();
    ButtonRecPtr LeftPanelButton6 = Button::create();

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
    BoxLayoutRecPtr LeftPanelButtonPanelLayout = BoxLayout::create();
    LeftPanelButtonPanelLayout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);

    // Create an edit Panel Background
    ColorLayerRecPtr LeftPanelButtonPanelBackground = ColorLayer::create();
    LeftPanelButtonPanelBackground->setColor(Color4f(0.93,0.93,0.93,1.0));

    // Create Panel Border
    LineBorderRecPtr LeftPanelBorder = LineBorder::create();
    LeftPanelBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
    LeftPanelBorder->setWidth(1);

    // Create and edit Panel
    PanelRecPtr LeftPanelButtonPanel = Panel::createEmpty();
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

    return PanelTransitPtr(LeftPanelButtonPanel);
}




PanelTransitPtr createLeftPanelRadioTextPanel(void)
{
    // Create TextArea
    TextAreaRecPtr LeftPanelTextArea = TextArea::create();
    LeftPanelTextArea->setPreferredSize(Vec2f(125, 200));
    LeftPanelTextArea->setText("Text Area");

    // Create the RadioButton group
    RadioButtonRecPtr RadioButton1 = RadioButton::create();
    RadioButtonRecPtr RadioButton2 = RadioButton::create();
    RadioButtonRecPtr RadioButton3 = RadioButton::create();
    RadioButtonRecPtr RadioButton4 = RadioButton::create();

    RadioButton1->setAlignment(Vec2f(0.0,0.5));
    RadioButton1->setPreferredSize(Vec2f(100, 40));
    RadioButton1->setText("Black Text");
    RadioButton1->setToolTipText("Set TextArea text black");
    RadioButton1->connectButtonSelected(boost::bind(setTextColors,
                                                    LeftPanelTextArea.get(),
                                                    Color4f(0.0f,0.0f,0.0f,1.0f)));

    RadioButton2->setAlignment(Vec2f(0.0,0.5));
    RadioButton2->setPreferredSize(Vec2f(100, 40));
    RadioButton2->setText("Red Text");
    RadioButton2->setToolTipText("Set TextArea text red");
    RadioButton2->connectButtonSelected(boost::bind(setTextColors,
                                              LeftPanelTextArea.get(),
                                              Color4f(1.0f,0.0f,0.0f,1.0f)));

    RadioButton3->setAlignment(Vec2f(0.0,0.5));
    RadioButton3->setPreferredSize(Vec2f(100, 40));
    RadioButton3->setText("Green Text");
    RadioButton3->setToolTipText("Set TextArea text green");
    RadioButton3->connectButtonSelected(boost::bind(setTextColors,
                                              LeftPanelTextArea.get(),
                                              Color4f(0.0f,1.0f,0.0f,1.0f)));

    RadioButton4->setAlignment(Vec2f(0.0,0.5));
    RadioButton4->setPreferredSize(Vec2f(100, 40));
    RadioButton4->setText("Blue Text");
    RadioButton4->setToolTipText("Set TextArea text blue");
    RadioButton4->connectButtonSelected(boost::bind(setTextColors,
                                              LeftPanelTextArea.get(),
                                              Color4f(0.0f,0.0f,1.0f,1.0f)));

    RadioButtonGroupRecPtr buttonGroup = RadioButtonGroup::create();
    buttonGroup->addButton(RadioButton1);
    buttonGroup->addButton(RadioButton2);
    buttonGroup->addButton(RadioButton3);
    buttonGroup->addButton(RadioButton4);


    // Create Panel and its Background/Border to label TextField
    LabelRecPtr LeftPanelTextFieldLabel = Label::create();
    EmptyLayerRecPtr LeftPanelTextFieldLabelBackground = EmptyLayer::create();
    EmptyBorderRecPtr LeftPanelTextFieldLabelBorder = EmptyBorder::create();
    LeftPanelTextFieldLabel->setPreferredSize(Vec2f(100, 25));
    LeftPanelTextFieldLabel->setBorders(LeftPanelTextFieldLabelBorder);
    LeftPanelTextFieldLabel->setBackgrounds(LeftPanelTextFieldLabelBackground);
    LeftPanelTextFieldLabel->setText("Text Field");

    // Create TextField
    TextFieldRecPtr LeftPanelTextField = TextField::create();
    LeftPanelTextField->setPreferredSize(Vec2f(125.0f, 22.0f));

    // Create an edit Panel Background
    ColorLayerRecPtr LeftPanelRadioTextPanelBackground = ColorLayer::create();
    LeftPanelRadioTextPanelBackground->setColor(Color4f(0.93f,0.93f,0.93f,1.0f));

    // Create and edit Panel layouts
    FlowLayoutRecPtr LeftPanelRadioTextPanelLayout = FlowLayout::create();
    FlowLayoutRecPtr LeftPanelRadioTextPanelRadioPanelLayout = FlowLayout::create();
    FlowLayoutRecPtr LeftPanelRadioTextPanelTextPanelLayout = FlowLayout::create();
    LeftPanelRadioTextPanelLayout->setMinorAxisAlignment(0.0f);

    // Create two Panels for this Panel
    PanelRecPtr LeftPanelRadioTextPanelRadioPanel = Panel::createEmpty();
    PanelRecPtr LeftPanelRadioTextPanelTextPanel = Panel::createEmpty();

    // Create some Borders
    EmptyBorderRecPtr LeftPanelRadioTextPanelRadioPanelBorder = EmptyBorder::create();

    LeftPanelRadioTextPanelRadioPanel->setBorders(LeftPanelRadioTextPanelRadioPanelBorder);
    LeftPanelRadioTextPanelRadioPanel->setPreferredSize(Vec2f(125, 200));
    LeftPanelRadioTextPanelRadioPanel->setLayout(LeftPanelRadioTextPanelRadioPanelLayout);
    LeftPanelRadioTextPanelRadioPanel->setBackgrounds(LeftPanelRadioTextPanelBackground);
    LeftPanelRadioTextPanelRadioPanel->pushToChildren(RadioButton1);
    LeftPanelRadioTextPanelRadioPanel->pushToChildren(RadioButton2);
    LeftPanelRadioTextPanelRadioPanel->pushToChildren(RadioButton3);
    LeftPanelRadioTextPanelRadioPanel->pushToChildren(RadioButton4);

    // Create Panel Border
    LineBorderRecPtr PanelBorder1 = LineBorder::create();
    PanelBorder1->setColor(Color4f(0.0,0.0,0.0,1.0));
    PanelBorder1->setWidth(1);

    // Create and edit Panel
    PanelRecPtr LeftPanelRadioTextPanel = Panel::createEmpty();
    LeftPanelRadioTextPanel->setPreferredSize(Vec2f(180, 500));
    LeftPanelRadioTextPanel->pushToChildren(LeftPanelRadioTextPanelRadioPanel);
    //LeftPanelRadioTextPanel->pushToChildren(LeftPanelTextArea);
    LeftPanelRadioTextPanel->pushToChildren(LeftPanelTextFieldLabel);
    LeftPanelRadioTextPanel->pushToChildren(LeftPanelTextField);
    LeftPanelRadioTextPanel->setLayout(LeftPanelRadioTextPanelLayout);
    LeftPanelRadioTextPanel->setBackgrounds(LeftPanelRadioTextPanelBackground);
    LeftPanelRadioTextPanel->setBorders(PanelBorder1);

    return PanelTransitPtr(LeftPanelRadioTextPanel);
}

PanelTransitPtr createRightPanelButtonPanel(void)
{
    // Create and edit the Panel Buttons
    ToggleButtonRecPtr RightPanelButton1 = ToggleButton::create();
    ToggleButtonRecPtr RightPanelButton2 = ToggleButton::create();
    ToggleButtonRecPtr RightPanelButton3 = ToggleButton::create();
    ToggleButtonRecPtr RightPanelButton4 = ToggleButton::create();

    RightPanelButton1->setText("These");
    RightPanelButton1->setPreferredSize(Vec2f(100,50));

    RightPanelButton2->setText("are");
    RightPanelButton2->setPreferredSize(Vec2f(100,50));

    RightPanelButton3->setText("toggle");
    RightPanelButton3->setPreferredSize(Vec2f(100,50));

    RightPanelButton4->setText("buttons");
    RightPanelButton4->setPreferredSize(Vec2f(100,50));


    // Create an edit Panel Background
    ColorLayerRecPtr RightPanelButtonPanelBackground = ColorLayer::create();
    RightPanelButtonPanelBackground->setColor(Color4f(0.93,0.93,0.93,1.0));

    // Create and edit Panel layout
    BoxLayoutRecPtr RightPanelButtonPanelLayout = BoxLayout::create();
    RightPanelButtonPanelLayout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);

    // Create Panel Border
    LineBorderRecPtr PanelBorder2 = LineBorder::create();
    PanelBorder2->setColor(Color4f(0.0,0.0,0.0,1.0));
    PanelBorder2->setWidth(1);

    // Create and edit Panel
    PanelRecPtr RightPanelButtonPanel = Panel::createEmpty();
    RightPanelButtonPanel->setPreferredSize(Vec2f(200, 300));
    RightPanelButtonPanel->pushToChildren(RightPanelButton1);
    RightPanelButtonPanel->pushToChildren(RightPanelButton2);
    RightPanelButtonPanel->pushToChildren(RightPanelButton3);
    RightPanelButtonPanel->pushToChildren(RightPanelButton4);
    RightPanelButtonPanel->setLayout(RightPanelButtonPanelLayout);
    RightPanelButtonPanel->setBackgrounds(RightPanelButtonPanelBackground);
    RightPanelButtonPanel->setBorders(PanelBorder2);

    return PanelTransitPtr(RightPanelButtonPanel);

}

PanelTransitPtr createRightPanelCheckPanel(Node* const TorusNode,
                                           Node* const SphereNode,
                                           Node* const ConeNode,
                                           Node* const BoxNode)
{
    // Create and edit the CheckBoxes
    CheckboxButtonRecPtr RightPanelCheck1 = CheckboxButton::create();
    CheckboxButtonRecPtr RightPanelCheck2 = CheckboxButton::create();
    CheckboxButtonRecPtr RightPanelCheck3 = CheckboxButton::create();
    CheckboxButtonRecPtr RightPanelCheck4 = CheckboxButton::create();
    //NOTE HorizontalAlignment needs to be changed to Alignment only with Vec2f arg
    RightPanelCheck1->setText("Show Torus");
    RightPanelCheck1->setPreferredSize(Vec2f(125,50));
    RightPanelCheck1->setAlignment(0.0);
    RightPanelCheck1->connectButtonSelected(boost::bind(setNodeTravMask,
                                                        TorusNode,
                                                        1));
    RightPanelCheck1->connectButtonDeselected(boost::bind(setNodeTravMask,
                                                          TorusNode,
                                                          0));

    RightPanelCheck2->setText("Show Box");
    RightPanelCheck2->setPreferredSize(Vec2f(125,50));
    RightPanelCheck2->setAlignment(Vec2f (0.5,0.0));
    RightPanelCheck2->connectButtonSelected(boost::bind(setNodeTravMask, BoxNode, 1));
    RightPanelCheck2->connectButtonDeselected(boost::bind(setNodeTravMask, BoxNode, 0));

    RightPanelCheck3->setText("Show Sphere");
    RightPanelCheck3->setPreferredSize(Vec2f(125,50));
    RightPanelCheck3->setAlignment(Vec2f(0.0,0.0));
    RightPanelCheck3->connectButtonSelected(boost::bind(setNodeTravMask, SphereNode, 1));
    RightPanelCheck3->connectButtonDeselected(boost::bind(setNodeTravMask, SphereNode, 0));

    RightPanelCheck4->setText("Show Cone");
    RightPanelCheck4->setPreferredSize(Vec2f(125,50));
    RightPanelCheck4->setAlignment(Vec2f(0.0,0.0));
    RightPanelCheck4->connectButtonSelected(boost::bind(setNodeTravMask, ConeNode, 1));
    RightPanelCheck4->connectButtonDeselected(boost::bind(setNodeTravMask, ConeNode, 0));

    // Create an edit Panel Background
    ColorLayerRecPtr RightPanelCheckPanelBackground = ColorLayer::create();
    RightPanelCheckPanelBackground->setColor(Color4f(0.93,0.93,0.93,1.0));

    // Create and edit Panel layout
    BoxLayoutRecPtr RightPanelCheckPanelLayout = BoxLayout::create();
    RightPanelCheckPanelLayout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);
    RightPanelCheckPanelLayout->setMinorAxisAlignment(0.5f);

    // Create Panel Border
    LineBorderRecPtr PanelBorder3 = LineBorder::create();
    PanelBorder3->setColor(Color4f(0.0,0.0,0.0,1.0));
    PanelBorder3->setWidth(1);

    // Create and edit Panel
    PanelRecPtr RightPanelCheckPanel = Panel::createEmpty();
    RightPanelCheckPanel->setPreferredSize(Vec2f(200, 300));
    RightPanelCheckPanel->pushToChildren(RightPanelCheck1);
    RightPanelCheckPanel->pushToChildren(RightPanelCheck2);
    RightPanelCheckPanel->pushToChildren(RightPanelCheck3);
    RightPanelCheckPanel->pushToChildren(RightPanelCheck4);
    RightPanelCheckPanel->setLayout(RightPanelCheckPanelLayout);
    RightPanelCheckPanel->setBackgrounds(RightPanelCheckPanelBackground);
    RightPanelCheckPanel->setBorders(PanelBorder3);

    return PanelTransitPtr(RightPanelCheckPanel);
}

LayerTransitPtr createComplexBackground(void)
{

    // Create complex Background 
    ColorLayerRecPtr ComplexBackgroundBase = ColorLayer::create();
    GradientLayerRecPtr ComplexBackgroundGradient1 = GradientLayer::create();
    GradientLayerRecPtr ComplexBackgroundGradient2 = GradientLayer::create();
    GradientLayerRecPtr ComplexBackgroundGradient3 = GradientLayer::create();
    CompoundLayerRecPtr ComplexBackgroundCompound1 = CompoundLayer::create();
    CompoundLayerRecPtr ComplexBackgroundCompound2 = CompoundLayer::create();
    CompoundLayerRecPtr ComplexBackground = CompoundLayer::create();

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

    return LayerTransitPtr(ComplexBackground);
}

ChunkMaterialTransitPtr createMaterial(const Color4f& TheColor)
{
    MaterialChunkRecPtr BackgroundMaterialChunk = MaterialChunk::create();
    BackgroundMaterialChunk->setAmbient (TheColor);
    BackgroundMaterialChunk->setDiffuse (TheColor);
    BackgroundMaterialChunk->setSpecular(TheColor);

    ChunkMaterialRecPtr BackgroundMaterial = ChunkMaterial::create();
    BackgroundMaterial->addChunk(BackgroundMaterialChunk);

    return ChunkMaterialTransitPtr(BackgroundMaterial);
}

NodeTransitPtr createTorus(void)
{
    // Make Object Nodes
    NodeRecPtr ExampleTorusGeo = makeTorus(90, 270, 16, 16);

    // Preform transformations on them
    Matrix mat;

    // On Torus    
    mat.setTranslate(0.0,100.0,-200.0);
    TransformRecPtr TorusTranCore = Transform::create();
    TorusTranCore->setMatrix(mat);

    NodeRecPtr ExampleTorus = Node::create();
    ExampleTorus->setCore(TorusTranCore);
    ExampleTorus->addChild(ExampleTorusGeo);
    ExampleTorus->setTravMask(0);

    return NodeTransitPtr(ExampleTorus);
}

NodeTransitPtr createCone(void)
{
    // Make Object Nodes
    NodeRecPtr ExampleConeGeo = makeCone(150, 50, 16, true, true);

    MaterialRecPtr BlueMaterial = createMaterial(Color4f(0.0f,0.0f,1.0f,1.0f));
    dynamic_cast<Geometry*>(ExampleConeGeo->getCore())->setMaterial(BlueMaterial);

    // Preform transformations on them
    Matrix mat;

    // On Cone
    mat.setTranslate(0.0,0.0,-250.0);

    TransformRecPtr ConeTranCore = Transform::create();
    ConeTranCore->setMatrix(mat);

    NodeRecPtr ExampleCone = Node::create();
    ExampleCone->setCore(ConeTranCore);
    ExampleCone->addChild(ExampleConeGeo);
    ExampleCone->setTravMask(0);

    return NodeTransitPtr(ExampleCone);
}

NodeTransitPtr createSphere(void)
{
    // Make Object Nodes
    NodeRecPtr ExampleSphereGeo = makeSphere(4, 100);

    MaterialRecPtr RedMaterial = createMaterial(Color4f(1.0f,0.0f,0.0f,1.0f));
    dynamic_cast<Geometry*>(ExampleSphereGeo->getCore())->setMaterial(RedMaterial);

    Matrix mat;
    mat.setTranslate(250.0,0.0,0.0);

    TransformRecPtr SphereTranCore = Transform::create();
    SphereTranCore->setMatrix(mat);

    NodeRecPtr ExampleSphere = Node::create();
    ExampleSphere->setCore(SphereTranCore);
    ExampleSphere->addChild(ExampleSphereGeo);
    ExampleSphere->setTravMask(0);

    return NodeTransitPtr(ExampleSphere);
}

NodeTransitPtr createBox(void)
{
    // Make Object Nodes
    NodeRecPtr ExampleBoxGeo = makeBox(100, 100, 100, 1, 1, 1);

    MaterialRecPtr GreenMaterial = createMaterial(Color4f(0.0f,1.0f,0.0f,1.0f));
    dynamic_cast<Geometry*>(ExampleBoxGeo->getCore())->setMaterial(GreenMaterial);

    Matrix mat;
    mat.setTranslate(250.0,250.0,0.0);

    TransformRecPtr ExampleBoxTranCore = Transform::create();
    ExampleBoxTranCore->setMatrix(mat);

    NodeRecPtr ExampleBox = Node::create();
    ExampleBox->setCore(ExampleBoxTranCore);
    ExampleBox->addChild(ExampleBoxGeo);
    ExampleBox->setTravMask(0);

    return NodeTransitPtr(ExampleBox);
}

// Callback functions
// Redraw the window
void display(SimpleSceneManager *mgr)
{
    mgr->redraw();
}

// React to size changes
void reshape(Vec2f Size, SimpleSceneManager *mgr)
{
    mgr->resize(Size.x(), Size.y());
}
