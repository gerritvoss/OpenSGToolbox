// OpenSG Tutorial Example: Creating a Text area to run a Lua script from
//

// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// Methods to create simple geometry: boxes, spheres, tori etc.
#include "OSGSimpleGeometry.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"
#include "OSGGradientBackground.h"
#include "OSGNameAttachment.h"
#include "OSGDirectionalLight.h"
#include "OSGGeoFunctions.h"

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
#include "OSGAdvancedTextDomArea.h"

#include "OSGLayers.h"
#include "OSGButton.h"
#include "OSGPanel.h"
#include "OSGLineBorder.h"
#include "OSGFlowLayout.h"
#include "OSGBorderLayout.h"
#include "OSGBorderLayoutConstraints.h"
#include "OSGUIFont.h"
#include "OSGScrollPanel.h"
#include "OSGTextArea.h"
#include "OSGTabPanel.h"
#include "OSGSplitPanel.h"
#include "OSGLabel.h"
#include "OSGSpringLayout.h"
#include "OSGSpringLayoutConstraints.h"
#include "OSGAdvancedTextDomArea.h"
#include "OSGDocument.h"
#include "OSGTextDomLayoutManager.h"
#include "OSGGlyphView.h"

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>

//Lua Manager
#ifdef OSG_WITH_LUA_DEBUGGER
#include "OSGLuaDebugger.h"
#include "OSGLuaIntrospectionTreeModel.h"
#include "OSGLuaIntrospectionComponentGenerator.h"
#include "OSGTree.h"
#include "OSGFixedHeightTreeModelLayout.h"
#include "OSGLuaUtils.h"
#else
#include "OSGLuaManager.h"
#endif

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications

#ifdef OSG_WITH_LUA_DEBUGGER
LuaDebugger* TheLuaManager(LuaDebugger::the());
#else
LuaManager* TheLuaManager(LuaManager::the());
#endif

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

//Ctrl+q handler
void keyTyped(KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() &
       KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
    //if(details->getKey() == KeyEventDetails::KEY_E && details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    //{
        //clearError();
        //TheLuaManager->runScript(CodeTextArea->getText());
    //}
}

class LuaDebuggerInterface
{
  public:
    LuaDebuggerInterface(void);

    Panel* getButtonPanel(void) const;
    SplitPanel* getMainSplitPanel(void) const;
    Panel* getCodeAreaInfoPanel(void) const;

  private:
    PanelRefPtr _Toolbars;

    PanelRefPtr _EditorButtonPanel;
    SplitPanelRefPtr _MainSplitPanel;
    PanelRefPtr _CodeAreaInfoPanel;

    BoostPath _BaseIconDir;

    PanelRecPtr _CodeExecutionToolbar;
    ButtonRecPtr _ExecuteButton;
    ButtonRecPtr _StopExecutionButton;
    ButtonRecPtr _StepInButton;
    ButtonRecPtr _StepOutButton;
    ButtonRecPtr _StepOverButton;
    Vec2f        _ToolButtonSize;

    AdvancedTextDomAreaRefPtr _CodeTextArea;
    TextAreaRefPtr _ErrorTextArea;
    TextAreaRefPtr _MessageTextArea;
    TextAreaRefPtr _StackTraceTextArea;
    TextAreaRefPtr _HelpTextArea;
    TabPanelRefPtr _InfoTabPanel;
    UIFontRefPtr _CodeFont;
    LabelRefPtr _ColumnValueLabel;
    LabelRefPtr _LineValueLabel;

    std::string createDefaultCodeText(void);

    void createUtilTabs(void);

    void createExecutionToolbar(void);

    void createEditorToolbar(void);

    void createToolbars(void);

    void createCodeEditor(void);

    void clearError(void);

    void executeScriptButtonAction(ActionEventDetails* const details);

    void clearScriptButtonAction(ActionEventDetails* const details);

    void saveScriptButtonAction(ActionEventDetails* const details);

    void openScriptButtonAction(ActionEventDetails* const details);

    void handlLuaError(LuaErrorEventDetails* const details);

    void codeAreaCaretChanged(CaretEventDetails* const details);

    void handleCodeAreaMouseClicked(MouseEventDetails* const details);

#ifdef OSG_WITH_LUA_DEBUGGER

    void handleUpdateTreeEvent(KeyEventDetails* const details, 
                               Tree* const theTree,
                               LuaIntrospectionTreeModel* const theModel);

    void addIntrospectionTreeTab(TabPanel* const tabPanel);

    void updateExecutionToolbar(void);

#endif
};

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    {
        TheLuaManager->init();

        // Set up Window
        WindowEventProducerRecPtr TutorialWindow = createNativeWindow();
        TutorialWindow->initWindow();

        // Create the SimpleSceneManager helper
        SimpleSceneManager sceneManager;
        TutorialWindow->setDisplayCallback(boost::bind(display, &sceneManager));
        TutorialWindow->setReshapeCallback(boost::bind(reshape, _1, &sceneManager));

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1));

        //Setup the Lua Manager

        BoostPath ModulePath("./Data/");
        std::string PackagePath = std::string("?;")
            + (ModulePath / "?.lua" ).file_string() + ";"
            + (ModulePath / "?" /  "init.lua").file_string();
        TheLuaManager->setPackagePath(PackagePath);

        // Make Torus Node (creates Torus in background of scene)
        GeometryRefPtr TorusGeometry = makeTorusGeo(.5, 2, 16, 16);
        setName(TorusGeometry,"Torus Geometry");
        //calcVertexTangents(TorusGeometry,0,Geometry::TexCoords7FieldId, Geometry::TexCoords6FieldId);


        NodeRefPtr TorusGeometryNode = Node::create();
        setName(TorusGeometryNode,"Torus Geometry Node");
        TorusGeometryNode->setCore(TorusGeometry);

        //Torus Transformation Node
        TransformRefPtr TheTorusNodeTransform = Transform::create();

        NodeRefPtr TheTorusTransfromNode = Node::create();
        TheTorusTransfromNode->setCore(TheTorusNodeTransform);
        TheTorusTransfromNode->addChild(TorusGeometryNode);
        setName(TheTorusTransfromNode,"Torus Transform Node");

        // Make Main Scene Node and add the Torus
        NodeRefPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(TheTorusTransfromNode);
        setName(scene,"Scene Node");

        //Light Beacon Node
        TransformRefPtr TheLightBeaconNodeTransform = Transform::create();

        NodeRefPtr TheLightBeaconNode = Node::create();
        TheLightBeaconNode->setCore(TheLightBeaconNodeTransform);
        setName(TheLightBeaconNode,"Light Beacon Node");


        //Light Node
        DirectionalLightRefPtr TheLightCore = DirectionalLight::create();
        TheLightCore->setDirection(Vec3f(1.0,0.0,0.0));
        TheLightCore->setAmbient(Color4f(1.0,1.0,1.0,1.0));
        TheLightCore->setDiffuse(Color4f(1.0,1.0,1.0,1.0));
        TheLightCore->setSpecular(Color4f(1.0,1.0,1.0,1.0));
        TheLightCore->setBeacon(TheLightBeaconNode);

        NodeRefPtr TheLightNode = Node::create();
        TheLightNode->setCore(TheLightCore);
        TheLightNode->addChild(scene);
        setName(TheLightNode,"Light Node");

        NodeRefPtr RootNode = Node::create();
        RootNode->setCore(Group::create());
        RootNode->addChild(TheLightNode);
        RootNode->addChild(TheLightBeaconNode);
        setName(RootNode,"Root Node");

        // Create the Graphics
        GraphicsRefPtr TutorialGraphics = Graphics2D::create();

        // Initialize the LookAndFeelManager to enable default settings
        LookAndFeelManager::the()->getLookAndFeel()->init();

        //Create the Main interface
        LuaDebuggerInterface TheLuaDebuggerInterface;

        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRefPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        BorderLayoutRefPtr MainInternalWindowLayout = BorderLayout::create();

        //Split Panel
        BorderLayoutConstraintsRefPtr SplitPanelConstraints = BorderLayoutConstraints::create();
        SplitPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
        TheLuaDebuggerInterface.getMainSplitPanel()->setConstraints(SplitPanelConstraints);

        BorderLayoutConstraintsRefPtr ButtonPanelConstraints = BorderLayoutConstraints::create();
        ButtonPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_NORTH);
        TheLuaDebuggerInterface.getButtonPanel()->setConstraints(ButtonPanelConstraints);

        BorderLayoutConstraintsRefPtr CodeAreaInfoPanelConstraints = BorderLayoutConstraints::create();
        CodeAreaInfoPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_SOUTH);
        TheLuaDebuggerInterface.getCodeAreaInfoPanel()->setConstraints(CodeAreaInfoPanelConstraints);

        InternalWindowRefPtr MainInternalWindow = InternalWindow::create();
        MainInternalWindow->pushToChildren(TheLuaDebuggerInterface.getButtonPanel());
        MainInternalWindow->pushToChildren(TheLuaDebuggerInterface.getMainSplitPanel());
        MainInternalWindow->pushToChildren(TheLuaDebuggerInterface.getCodeAreaInfoPanel());
        MainInternalWindow->setLayout(MainInternalWindowLayout);
        MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
        MainInternalWindow->setTitle("Lua Debugger");
        setName(MainInternalWindow,"Internal Window");

        // Create the Drawing Surface
        UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);

        TutorialDrawingSurface->openWindow(MainInternalWindow);

        // Create the UI Foreground Object
        UIForegroundRefPtr TutorialUIForeground = UIForeground::create();

        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);

        //Scene Background
        GradientBackgroundRefPtr SceneBackground = GradientBackground::create();
        SceneBackground->addLine(Color3f(0.0,0.0,0.0),0.0);
        setName(SceneBackground,"Scene Background");

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);
        sceneManager.setRoot(RootNode);
        //sceneManager.setHeadlight(false);

        // Add the UI Foreground Object to the Scene
        ViewportRefPtr TutorialViewport = sceneManager.getWindow()->getPort(0);
        TutorialViewport->addForeground(TutorialUIForeground);
        TutorialViewport->setBackground(SceneBackground);

        // Show the whole Scene
        sceneManager.showAll();


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "03LuaDebugger");

        MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setPreferredSize(WinSize * 0.85);

        //Enter main Loop
        TutorialWindow->mainLoop();

        TheLuaManager->uninit();
    }

    osgExit();

    return 0;
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


std::string LuaDebuggerInterface::createDefaultCodeText(void)
{
    return "print(\"Hello World\")";
}

void LuaDebuggerInterface::createUtilTabs(void)
{
    //Create the Error Text Area
    _ErrorTextArea = TextArea::create();

    _ErrorTextArea->setPreferredSize(Vec2f(600, 150));
    _ErrorTextArea->setText("");
    _ErrorTextArea->setMinSize(Vec2f(300, 150));
    _ErrorTextArea->setFont(_CodeFont);
    _ErrorTextArea->setTextColors(Color4f(0.2,0.0,0.0,1.0));
    _ErrorTextArea->setEditable(false);
    setName(_ErrorTextArea,"Error TextArea");
    TheLuaManager->connectLuaError(boost::bind(&LuaDebuggerInterface::handlLuaError,
                                                this,
                                                _1));

    // Create a ScrollPanel
    ScrollPanelRefPtr ErrorAreaScrollPanel = ScrollPanel::create();
    ErrorAreaScrollPanel->setPreferredSize(Vec2f(200,150));
    ErrorAreaScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    // Add the TextArea to the ScrollPanel so it is displayed
    ErrorAreaScrollPanel->setViewComponent(_ErrorTextArea);

    //Create the StackTrace Text Area
    _StackTraceTextArea = TextArea::create();

    _StackTraceTextArea->setPreferredSize(Vec2f(600, 150));
    _StackTraceTextArea->setText("");
    _StackTraceTextArea->setMinSize(Vec2f(300, 150));
    _StackTraceTextArea->setFont(_CodeFont);
    _StackTraceTextArea->setTextColors(Color4f(0.2,0.0,0.0,1.0));
    _StackTraceTextArea->setEditable(false);
    setName(_StackTraceTextArea,"Stack Trace TextArea");

    // Create a ScrollPanel
    ScrollPanelRefPtr StackTraceAreaScrollPanel = ScrollPanel::create();
    StackTraceAreaScrollPanel->setPreferredSize(Vec2f(200,150));
    StackTraceAreaScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    // Add the TextArea to the ScrollPanel so it is displayed
    StackTraceAreaScrollPanel->setViewComponent(_StackTraceTextArea);

    //Create the Message Text Area
    _MessageTextArea = TextArea::create();

    _MessageTextArea->setPreferredSize(Vec2f(600, 150));
    _MessageTextArea->setText("");
    _MessageTextArea->setMinSize(Vec2f(300, 150));
    _MessageTextArea->setFont(_CodeFont);
    _MessageTextArea->setTextColors(Color4f(0.2,0.0,0.0,1.0));
    _MessageTextArea->setEditable(false);
    setName(_MessageTextArea,"Message TextArea");

    // Create a ScrollPanel
    ScrollPanelRefPtr MessageAreaScrollPanel = ScrollPanel::create();
    MessageAreaScrollPanel->setPreferredSize(Vec2f(200,150));
    MessageAreaScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    // Add the TextArea to the ScrollPanel so it is displayed
    MessageAreaScrollPanel->setViewComponent(_MessageTextArea);

    //Create the Message Text Area
    _HelpTextArea = TextArea::create();

    _HelpTextArea->setPreferredSize(Vec2f(600, 150));
    _HelpTextArea->setText("");
    _HelpTextArea->setMinSize(Vec2f(300, 150));
    _HelpTextArea->setFont(_CodeFont);
    _HelpTextArea->setTextColors(Color4f(0.2,0.0,0.0,1.0));
    _HelpTextArea->setEditable(false);
    setName(_HelpTextArea,"Help TextArea");

    // Create a ScrollPanel
    ScrollPanelRefPtr HelpAreaScrollPanel = ScrollPanel::create();
    HelpAreaScrollPanel->setPreferredSize(Vec2f(200,150));
    HelpAreaScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    // Add the TextArea to the ScrollPanel so it is displayed
    HelpAreaScrollPanel->setViewComponent(_HelpTextArea);

    //Tab Panel
    LabelRefPtr MessageTabLabel = Label::create();
    MessageTabLabel->setText("Output");

    LabelRefPtr ErrorTabLabel = Label::create();
    ErrorTabLabel->setText("Error");

    LabelRefPtr StackTraceTabLabel = Label::create();
    StackTraceTabLabel->setText("Stack");

    LabelRefPtr HelpTabLabel = Label::create();
    HelpTabLabel->setText("Help");

    _InfoTabPanel = TabPanel::create();
    _InfoTabPanel->addTab(MessageTabLabel, MessageAreaScrollPanel);
    _InfoTabPanel->addTab(ErrorTabLabel, ErrorAreaScrollPanel);
    _InfoTabPanel->addTab(StackTraceTabLabel, StackTraceAreaScrollPanel);
    _InfoTabPanel->addTab(HelpTabLabel, HelpAreaScrollPanel);
#ifdef OSG_WITH_LUA_DEBUGGER
    addIntrospectionTreeTab(_InfoTabPanel);
#endif
    _InfoTabPanel->setTabAlignment(0.5f);
    _InfoTabPanel->setTabPlacement(TabPanel::PLACEMENT_NORTH);
    _InfoTabPanel->setSelectedIndex(0);
    setName(_InfoTabPanel,"Info Tab Panel");
}

void LuaDebuggerInterface::createToolbars(void)
{
    createExecutionToolbar();
    createEditorToolbar();

    BorderLayoutRefPtr ToolbarLayout = BorderLayout::create();

    BorderLayoutConstraintsRefPtr EditorPanelConstraints = BorderLayoutConstraints::create();
    EditorPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_WEST);
    _EditorButtonPanel->setConstraints(EditorPanelConstraints);

    BorderLayoutConstraintsRefPtr CodeExecutionPanelConstraints = BorderLayoutConstraints::create();
    CodeExecutionPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
    _CodeExecutionToolbar->setConstraints(CodeExecutionPanelConstraints);

    _Toolbars = Panel::createEmpty();
    _Toolbars->setPreferredSize(Vec2f(45.0f, 45.0f));
    _Toolbars->setLayout(ToolbarLayout);
    _Toolbars->pushToChildren(_EditorButtonPanel);
    _Toolbars->pushToChildren(_CodeExecutionToolbar);
}

void LuaDebuggerInterface::createExecutionToolbar(void)
{
    //Execute Button
    BoostPath ExecuteIconPath(_BaseIconDir / BoostPath("execute.png"));
    BoostPath ExecuteDisabledIconPath(_BaseIconDir / BoostPath("execute-disabled.png"));
    _ExecuteButton = Button::create();
    _ExecuteButton->setPreferredSize(_ToolButtonSize);
    _ExecuteButton->setImages(ExecuteIconPath.string());
    _ExecuteButton->setDisabledImage(ExecuteDisabledIconPath.string());
    _ExecuteButton->setAlignment(Vec2f(0.5f,0.5f));
    _ExecuteButton->setToolTipText("Execute");
    _ExecuteButton->connectActionPerformed(boost::bind(&LuaDebuggerInterface::executeScriptButtonAction,this, _1));

    //Step Into Button
    BoostPath StepInIconPath(_BaseIconDir / BoostPath("basicstepinto.png"));
    BoostPath StepInDisabledIconPath(_BaseIconDir / BoostPath("basicstepinto-disabled.png"));
    _StepInButton = Button::create();
    _StepInButton->setPreferredSize(_ToolButtonSize);
    _StepInButton->setImages(StepInIconPath.string());
    _StepInButton->setDisabledImage(StepInDisabledIconPath.string());
    _StepInButton->setAlignment(Vec2f(0.5f,0.5f));
    _StepInButton->setToolTipText("Step In");

    //Step Out Button
    BoostPath StepOutIconPath(_BaseIconDir / BoostPath("basicstepout.png"));
    BoostPath StepOutDisabledIconPath(_BaseIconDir / BoostPath("basicstepout-disabled.png"));
    _StepOutButton = Button::create();
    _StepOutButton->setPreferredSize(_ToolButtonSize);
    _StepOutButton->setImages(StepOutIconPath.string());
    _StepOutButton->setDisabledImage(StepOutDisabledIconPath.string());
    _StepOutButton->setAlignment(Vec2f(0.5f,0.5f));
    _StepOutButton->setToolTipText("Step Out");

    //Step Over Button
    BoostPath StepOverIconPath(_BaseIconDir / BoostPath("basicstepover.png"));
    BoostPath StepOverDisabledIconPath(_BaseIconDir / BoostPath("basicstepover-disabled.png"));
    _StepOverButton = Button::create();
    _StepOverButton->setPreferredSize(_ToolButtonSize);
    _StepOverButton->setImages(StepOverIconPath.string());
    _StepOverButton->setDisabledImage(StepOverDisabledIconPath.string());
    _StepOverButton->setAlignment(Vec2f(0.5f,0.5f));
    _StepOverButton->setToolTipText("Step Over");

    //Stop Button
    BoostPath StopExecutionIconPath(_BaseIconDir / BoostPath("stop.png"));
    BoostPath StopExecutionDisabledIconPath(_BaseIconDir / BoostPath("stop-disabled.png"));
    _StopExecutionButton = Button::create();
    _StopExecutionButton->setPreferredSize(_ToolButtonSize);
    _StopExecutionButton->setImages(StopExecutionIconPath.string());
    _StopExecutionButton->setDisabledImage(StopExecutionDisabledIconPath.string());
    _StopExecutionButton->setAlignment(Vec2f(0.5f,0.5f));
    _StopExecutionButton->setToolTipText("Stop");

    //Code Execution Toolbar
    //Layout
    FlowLayoutRecPtr ToolbarLayout = FlowLayout::create();
    ToolbarLayout->setOrientation(FlowLayout::HORIZONTAL_ORIENTATION);
    ToolbarLayout->setHorizontalGap(3.0f);
    ToolbarLayout->setMajorAxisAlignment(0.0f);
    ToolbarLayout->setMinorAxisAlignment(0.5);

    _CodeExecutionToolbar = Panel::createEmpty();
    _CodeExecutionToolbar->setPreferredSize(Vec2f(45.0f, 45.0f));
    _CodeExecutionToolbar->setLayout(ToolbarLayout);
    _CodeExecutionToolbar->pushToChildren(_ExecuteButton);
    _CodeExecutionToolbar->pushToChildren(_StopExecutionButton);
    _CodeExecutionToolbar->pushToChildren(_StepOverButton);
    _CodeExecutionToolbar->pushToChildren(_StepInButton);
    _CodeExecutionToolbar->pushToChildren(_StepOutButton);

    updateExecutionToolbar();
}

void LuaDebuggerInterface::createCodeEditor(void)
{
    //Create the Breakpoint images
    BoostPath BreakpointIconPath(_BaseIconDir / BoostPath("breakpoint.png")),
              BreakpointDisabledIconPath(_BaseIconDir / BoostPath("breakpoint-disabled.png")),
              BreakpointConditionalIconPath(_BaseIconDir / BoostPath("breakpoint-conditional.png")),
              BreakpointConditionalDisabledIconPath(_BaseIconDir / BoostPath("breakpoint-conditional-disabled.png")),
              BreakpointCountIconPath(_BaseIconDir / BoostPath("breakpoint-count.png")),
              BreakpointCountDisabledIconPath(_BaseIconDir / BoostPath("breakpoint-count-disabled.png"));
    
    //Breakpoint Button prototypes
    //Regular Breakpoint
    ButtonRecPtr BreakpointProtoButton = Button::create();
    BreakpointProtoButton->setPreferredSize(Vec2f(18.0f, 18.0f));
    BreakpointProtoButton->setImages(BreakpointIconPath.string());
    BreakpointProtoButton->setDisabledImage(BreakpointDisabledIconPath.string());
    BreakpointProtoButton->setBorders(NULL);
    BreakpointProtoButton->setBackgrounds(NULL);
    BreakpointProtoButton->setForegrounds(NULL);

    //Count Breakpoint
    ButtonRecPtr BreakpointCountProtoButton = Button::create();
    BreakpointCountProtoButton->setPreferredSize(Vec2f(18.0f, 18.0f));
    BreakpointCountProtoButton->setImages(BreakpointCountIconPath.string());
    BreakpointCountProtoButton->setDisabledImage(BreakpointCountDisabledIconPath.string());
    BreakpointCountProtoButton->setBorders(NULL);
    BreakpointCountProtoButton->setBackgrounds(NULL);
    BreakpointCountProtoButton->setForegrounds(NULL);

    //Conditional breakpoint
    ButtonRecPtr BreakpointConditionalProtoButton = Button::create();
    BreakpointConditionalProtoButton->setPreferredSize(Vec2f(18.0f, 18.0f));
    BreakpointConditionalProtoButton->setImages(BreakpointConditionalIconPath.string());
    BreakpointConditionalProtoButton->setDisabledImage(BreakpointConditionalDisabledIconPath.string());
    BreakpointConditionalProtoButton->setBorders(NULL);
    BreakpointConditionalProtoButton->setBackgrounds(NULL);
    BreakpointConditionalProtoButton->setForegrounds(NULL);

    //Create the default font
    _CodeFont = UIFont::create();
    _CodeFont->setFamily("Courier New");
    _CodeFont->setSize(21);
    _CodeFont->setGlyphPixelSize(22);
    _CodeFont->setAntiAliasing(false);

    // Create a TextArea component
    _CodeTextArea = AdvancedTextDomArea::create();
    //_CodeTextArea->setWrapStyleWord(false);
    //_CodeTextArea->setPreferredSize(Vec2f(600, 400));
    _CodeTextArea->getTheTextDomArea()->setFont(_CodeFont);
    _CodeTextArea->setGutterWidth(50.0f);
    ColorLayerRefPtr TextDomBg = ColorLayer::create();
    TextDomBg->setColor(Color4f(0.95f,0.95f,0.95f,1.0f));
    _CodeTextArea->setBackgrounds(TextDomBg);
    //_CodeTextArea->clear();
    _CodeTextArea->setText(createDefaultCodeText());

    //_CodeTextArea->connectCaretChanged(boost::bind(&LuaDebuggerInterface::codeAreaCaretChanged,this, _1));
    //_CodeTextArea->connectMouseClicked(boost::bind(&LuaDebuggerInterface::handleCodeAreaMouseClicked,this, _1));

    // Create a ScrollPanel
    ScrollPanelRefPtr TextAreaScrollPanel = ScrollPanel::create();
    TextAreaScrollPanel->setPreferredSize(Vec2f(200,600));
    TextAreaScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    // Add the TextArea to the ScrollPanel so it is displayed
    TextAreaScrollPanel->setViewComponent(_CodeTextArea);


    _MainSplitPanel = SplitPanel::create();
    _MainSplitPanel->setMinComponent(TextAreaScrollPanel);
    _MainSplitPanel->setMaxComponent(_InfoTabPanel);
    _MainSplitPanel->setOrientation(SplitPanel::VERTICAL_ORIENTATION);
    _MainSplitPanel->setDividerPosition(0.7);
    // location from the left/top
    _MainSplitPanel->setDividerSize(4);
    _MainSplitPanel->setMaxDividerPosition(.8);
    _MainSplitPanel->setMinDividerPosition(.2);

    //Code Area Info
    LabelRefPtr LineLabel = Label::create();
    LineLabel->setText("Line:");
    LineLabel->setPreferredSize(Vec2f(40.0f, 30.0f));
    LineLabel->setAlignment(Vec2f(1.0f, 0.5f));

    _LineValueLabel = Label::create();
    _LineValueLabel->setText("");
    _LineValueLabel->setPreferredSize(Vec2f(40.0f, 30.0f));

    LabelRefPtr ColumnLabel = Label::create();
    ColumnLabel->setText("Column:");
    ColumnLabel->setPreferredSize(Vec2f(55.0f, 30.0f));
    ColumnLabel->setAlignment(Vec2f(1.0f, 0.5f));

    _ColumnValueLabel = Label::create();
    _ColumnValueLabel->setText("");
    _ColumnValueLabel->setPreferredSize(Vec2f(40.0f, 30.0f));
    //TextArea Info Panel

    _CodeAreaInfoPanel = Panel::create();

    SpringLayoutRefPtr CodeAreaInfoLayout = SpringLayout::create();

    //ColumnValueLabel
    CodeAreaInfoLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _ColumnValueLabel, 0, SpringLayoutConstraints::NORTH_EDGE, _CodeAreaInfoPanel);
    CodeAreaInfoLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _ColumnValueLabel, 0, SpringLayoutConstraints::SOUTH_EDGE, _CodeAreaInfoPanel);
    CodeAreaInfoLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _ColumnValueLabel, 0, SpringLayoutConstraints::EAST_EDGE, _CodeAreaInfoPanel);

    //ColumnLabel    
    CodeAreaInfoLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, ColumnLabel, 0, SpringLayoutConstraints::NORTH_EDGE, _CodeAreaInfoPanel);
    CodeAreaInfoLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, ColumnLabel, 0, SpringLayoutConstraints::SOUTH_EDGE, _CodeAreaInfoPanel);
    CodeAreaInfoLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, ColumnLabel, -1, SpringLayoutConstraints::WEST_EDGE, _ColumnValueLabel);

    //LineValueLabel    
    CodeAreaInfoLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _LineValueLabel, 0, SpringLayoutConstraints::NORTH_EDGE, _CodeAreaInfoPanel);
    CodeAreaInfoLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _LineValueLabel, 0, SpringLayoutConstraints::SOUTH_EDGE, _CodeAreaInfoPanel);
    CodeAreaInfoLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _LineValueLabel, -1, SpringLayoutConstraints::WEST_EDGE, ColumnLabel);

    //LineLabel    
    CodeAreaInfoLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, LineLabel, 0, SpringLayoutConstraints::NORTH_EDGE, _CodeAreaInfoPanel);
    CodeAreaInfoLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, LineLabel, 0, SpringLayoutConstraints::SOUTH_EDGE, _CodeAreaInfoPanel);
    CodeAreaInfoLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, LineLabel, -1, SpringLayoutConstraints::WEST_EDGE, _LineValueLabel);

    _CodeAreaInfoPanel->setPreferredSize(Vec2f(400.0f, 22.0f));
    _CodeAreaInfoPanel->pushToChildren(LineLabel);
    _CodeAreaInfoPanel->pushToChildren(_LineValueLabel);
    _CodeAreaInfoPanel->pushToChildren(ColumnLabel);
    _CodeAreaInfoPanel->pushToChildren(_ColumnValueLabel);
    _CodeAreaInfoPanel->setBorders(NULL);
    _CodeAreaInfoPanel->setLayout(CodeAreaInfoLayout);
}

void LuaDebuggerInterface::createEditorToolbar(void)
{
    BoostPath OpenIconPath(_BaseIconDir / BoostPath("open.png"));
    ButtonRefPtr OpenButton = Button::create();
    OpenButton->setToolTipText("Open");
    OpenButton->setPreferredSize(_ToolButtonSize);
    OpenButton->setImages(OpenIconPath.string());
    setName(OpenButton,"Open Button");
    OpenButton->connectActionPerformed(boost::bind(&LuaDebuggerInterface::openScriptButtonAction,this, _1));

    BoostPath SaveIconPath(_BaseIconDir / BoostPath("Save.png"));
    ButtonRefPtr SaveButton = Button::create();
    SaveButton->setPreferredSize(_ToolButtonSize);
    SaveButton->setToolTipText("Save");
    setName(SaveButton,"Save Button");
    SaveButton->setImages(SaveIconPath.string());
    SaveButton->connectActionPerformed(boost::bind(&LuaDebuggerInterface::saveScriptButtonAction,this, _1));

    BoostPath ClearIconPath(_BaseIconDir / BoostPath("clear.png"));
    ButtonRefPtr ClearButton = Button::create();
    ClearButton->setPreferredSize(_ToolButtonSize);
    ClearButton->setToolTipText("Clear");
    setName(ClearButton,"Clear Button");
    ClearButton->setImages(ClearIconPath.string());
    ClearButton->connectActionPerformed(boost::bind(&LuaDebuggerInterface::clearScriptButtonAction,this, _1));

    //Make the Button Panel
    FlowLayoutRefPtr ButtonPanelLayout = FlowLayout::create();
    ButtonPanelLayout->setOrientation(FlowLayout::HORIZONTAL_ORIENTATION);
    ButtonPanelLayout->setHorizontalGap(3.0f);
    ButtonPanelLayout->setMajorAxisAlignment(0.0f);
    ButtonPanelLayout->setMinorAxisAlignment(0.5);

    _EditorButtonPanel = Panel::createEmpty();
    _EditorButtonPanel->setPreferredSize(Vec2f(200.0f, 45.0f));
    _EditorButtonPanel->pushToChildren(OpenButton);
    _EditorButtonPanel->pushToChildren(SaveButton);
    _EditorButtonPanel->pushToChildren(ClearButton);
    _EditorButtonPanel->setLayout(ButtonPanelLayout);
    setName(_EditorButtonPanel,"Button Panel");
}

void LuaDebuggerInterface::clearError(void)
{
    _ErrorTextArea->setText("");
    _StackTraceTextArea->setText("");
}

void LuaDebuggerInterface::executeScriptButtonAction(ActionEventDetails* const details)
{
    clearError();
    TheLuaManager->runScript(_CodeTextArea->getText());
}


void LuaDebuggerInterface::clearScriptButtonAction(ActionEventDetails* const details)
{
    _CodeTextArea->clear();
    clearError();
}


void LuaDebuggerInterface::saveScriptButtonAction(ActionEventDetails* const details)
{
    std::vector<WindowEventProducer::FileDialogFilter> Filters;
    Filters.push_back(WindowEventProducer::FileDialogFilter("Lua File Type","lua"));
    Filters.push_back(WindowEventProducer::FileDialogFilter("All","*"));

    BoostPath SavePath = dynamic_cast<Component*>(details->getSource())->
        getParentWindow()->
        getParentDrawingSurface()->
        getEventProducer()->
        saveFileDialog("Save Lua Script to?",
                       Filters,
                       std::string("LuaScript.lua"),
                       BoostPath("Data"),
                       true);

    //Try to write the file
    std::ofstream OutFile(SavePath.string().c_str());
    if(OutFile)
    {
        OutFile << _CodeTextArea->getText();
        OutFile.close();
    }
}


void LuaDebuggerInterface::openScriptButtonAction(ActionEventDetails* const details)
{
    //Get a file using the open file dialog
    std::vector<WindowEventProducer::FileDialogFilter> Filters;
    Filters.push_back(WindowEventProducer::FileDialogFilter("Lua File Type","lua"));
    Filters.push_back(WindowEventProducer::FileDialogFilter("All","*"));

    std::vector<BoostPath> FilesToOpen;
    FilesToOpen = dynamic_cast<Component*>(details->getSource())->
        getParentWindow()->
        getParentDrawingSurface()->
        getEventProducer()->
        openFileDialog("Open Lua Script File.",
                       Filters,
                       BoostPath("Data"),
                       false);

    //Try to open the file
    if(FilesToOpen.size() > 0 &&
       boost::filesystem::exists(FilesToOpen.front()))
    {
        std::ifstream InFile(FilesToOpen.front().string().c_str());
        if(InFile)
        {
            std::ostringstream InStrStream;
            InStrStream << InFile.rdbuf();
            InFile.close();
            //Set the Text of the TextArea to the text of the file
            _CodeTextArea->setText(InStrStream.str());
            clearError();
        }
    }
}

void LuaDebuggerInterface::handlLuaError(LuaErrorEventDetails* const details)
{
    std::string ErrorType("");
    switch(details->getStatus())
    {
        case LUA_ERRSYNTAX:
            //Syntax Error
            ErrorType = "Lua Syntax Error";
            break;
        case LUA_ERRMEM:
            //Memory Allocation Error
            ErrorType = "Lua Memory Allocation Error";
            break;
        case LUA_ERRRUN:
            //Memory Allocation Error
            ErrorType = "Lua Runtime Error";
            break;
        case LUA_ERRERR:
            //Memory Allocation Error
            ErrorType = "Lua Error in Error Handler";
            break;
        default:
            //Unknown
            ErrorType = "Lua Unknown Error";
            break;
    }
    _ErrorTextArea->moveCaretToEnd();
    if(_ErrorTextArea->getText().size() != 0)
    {
        _ErrorTextArea->write("\n");
    }
    _ErrorTextArea->write(ErrorType + ":\n    " + details->getErrorString());

    //Select the Error Tab
    _InfoTabPanel->setSelectedIndex(1);

    //Fill Stack Trace
    if(details->getStatus() == LUA_ERRMEM ||
       details->getStatus() == LUA_ERRERR ||
       details->getStatus() == LUA_ERRRUN)
    {
        std::stringstream ss;
        ss << "Lua Stack Trace: " << std::endl << TheLuaManager->getCallStack() << std::endl;
        _StackTraceTextArea->write(ss.str());
    }
}

void LuaDebuggerInterface::codeAreaCaretChanged(CaretEventDetails* const details)
{
    //Update Caret Position Labels
    //Line
    //_LineValueLabel->setText(boost::lexical_cast<std::string>(_CodeTextArea->getCaretLine()+1));

    //Column
    //_ColumnValueLabel->setText(boost::lexical_cast<std::string>(_CodeTextArea->getCaretColumn()+1));
}

void LuaDebuggerInterface::handleCodeAreaMouseClicked(MouseEventDetails* const details)
{
    //_InfoTabPanel->setSelectedIndex(3);

    ////Try and get the lua object that is below the cursor
    //std::string Word(_CodeTextArea->getWordAtLocation(details->getLocation()));

    ////Get the Lua state
    //lua_State *LuaState(TheLuaManager->getLuaState());

    ////Get the Lua function to be called
    //lua_pushstring(LuaState,"_G");             //push the name of the table on the stack
    //lua_gettable(LuaState, LUA_GLOBALSINDEX);  //Push The table onto the stack

    ////Check if the the value given is a table
    //assert(lua_istable(LuaState, -1));

    //lua_getfield(LuaState, -1, Word.c_str());  //Push The field onto the stack

    //if(!lua_isnil(LuaState, -1))
    //{
        //lua_details::Var TheVar(Word,lua_details::Value(LuaState, -1));
        //_HelpTextArea->setText(TheVar.getName() + " [" +
                               //TheVar.getValue().getTypeName() + "]: " +
                               //TheVar.getValue().getValue());
    //}

    //lua_pop(LuaState, 2); //Pop the values off the stack
}

#ifdef OSG_WITH_LUA_DEBUGGER

void LuaDebuggerInterface::handleUpdateTreeEvent(KeyEventDetails* const details, 
                                                 Tree* const theTree,
                                                 LuaIntrospectionTreeModel* const theModel)
{
    if(details->getKey() == KeyEventDetails::KEY_R &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        theTree->scrollRowToVisible(0);
        theTree->collapsePath(theModel->getRootPath());
        theTree->expandPath(theModel->getRootPath());
    }
}

void LuaDebuggerInterface::addIntrospectionTreeTab(TabPanel* const tabPanel)
{
    LuaIntrospectionTreeModelRecPtr LuaIntroTreeModel = LuaIntrospectionTreeModel::create();
    LuaIntroTreeModel->setRoot("");

    LuaIntrospectionComponentGeneratorRecPtr LuaIntroTreeComponentGenerator = LuaIntrospectionComponentGenerator::create();

    //Create the Tree
    TreeRecPtr TheTree = Tree::create();

    TheTree->setPreferredSize(Vec2f(200, 500));
    TheTree->setModel(LuaIntroTreeModel);
    TheTree->setCellGenerator(LuaIntroTreeComponentGenerator);
    TheTree->connectKeyTyped(boost::bind(&LuaDebuggerInterface::handleUpdateTreeEvent,
                                         this,
                                         _1,
                                         TheTree.get(),
                                         LuaIntroTreeModel.get()));

    //Layout Expansion
    TheTree->expandPath(LuaIntroTreeModel->getRootPath());

    // Create a ScrollPanel for easier viewing of the List (see 27ScrollPanel)
    ScrollPanelRefPtr TreeScrollPanel = ScrollPanel::create();
    TreeScrollPanel->setPreferredSize(Vec2f(200,300));
    TreeScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    TreeScrollPanel->setViewComponent(TheTree);

    LabelRefPtr IntrospectionTreeTabLabel = Label::create();
    IntrospectionTreeTabLabel->setText("Variable Introspection");

    tabPanel->addTab(IntrospectionTreeTabLabel, TreeScrollPanel);
}

void LuaDebuggerInterface::updateExecutionToolbar(void)
{
    _ExecuteButton->setEnabled(!TheLuaManager->isRunning());
    _StopExecutionButton->setEnabled(TheLuaManager->isRunning());
    _StepInButton->setEnabled(TheLuaManager->isStopped() && !TheLuaManager->isFinished());
    _StepOutButton->setEnabled(TheLuaManager->isStopped() && !TheLuaManager->isFinished());
    _StepOverButton->setEnabled(TheLuaManager->isStopped() && !TheLuaManager->isFinished());
}

#endif

LuaDebuggerInterface::LuaDebuggerInterface() :
    _BaseIconDir("./Data/Icons"),
    _ToolButtonSize(40.0f,40.0f)
{
    createUtilTabs();
    createToolbars();
    createCodeEditor();
}

Panel* LuaDebuggerInterface::getButtonPanel(void) const
{
    return _Toolbars;
}

SplitPanel* LuaDebuggerInterface::getMainSplitPanel(void) const
{
    return _MainSplitPanel;
}

Panel* LuaDebuggerInterface::getCodeAreaInfoPanel(void) const
{
    return _CodeAreaInfoPanel;
}

