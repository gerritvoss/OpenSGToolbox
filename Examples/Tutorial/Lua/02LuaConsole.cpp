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

//Lua Manager
#include "OSGLuaManager.h"

#include <boost/filesystem.hpp>
#include <sstream>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

TextAreaRecPtr CodeTextArea;
TextAreaRecPtr ErrorTextArea;
TextAreaRecPtr MessageTextArea;
TextAreaRecPtr StackTraceTextArea;
TabPanelRecPtr InfoTabPanel;
UIFontRecPtr CodeFont;
LabelRecPtr ColumnValueLabel;
LabelRecPtr LineValueLabel;

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);
std::string getCodeText(void);

void clearError(void)
{
    ErrorTextArea->setText("");
    StackTraceTextArea->setText("");
}

//Ctrl+q handler
void keyTyped(KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() &
       KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
    if(details->getKey() == KeyEventDetails::KEY_E && details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        clearError();
        LuaManager::the()->runScript(CodeTextArea->getText());
    }
}

void executeScriptButtonAction(ActionEventDetails* const details)
{
    clearError();
    LuaManager::the()->runScript(CodeTextArea->getText());
}


void clearScriptButtonAction(ActionEventDetails* const details)
{
    CodeTextArea->selectAll();
    CodeTextArea->deleteSelectedText();
    clearError();
}


void saveScriptButtonAction(ActionEventDetails* const details)
{
    std::vector<WindowEventProducer::FileDialogFilter> Filters;
    Filters.push_back(WindowEventProducer::FileDialogFilter("Lua File Type","lua"));
    Filters.push_back(WindowEventProducer::FileDialogFilter("All","*"));

    BoostPath SavePath = dynamic_cast<Component*>(details->getSource())->getParentWindow()->
        getParentDrawingSurface()->getEventProducer()->saveFileDialog("Save Lua Script to?",
                                                                      Filters,
                                                                      std::string("LuaScript.lua"),
                                                                      BoostPath("Data"),
                                                                      true);

    //Try to write the file
    std::ofstream OutFile(SavePath.string().c_str());
    if(OutFile)
    {
        OutFile << CodeTextArea->getText();
        OutFile.close();
    }
}


void openScriptButtonAction(ActionEventDetails* const details)
{
    //Get a file using the open file dialog
    std::vector<WindowEventProducer::FileDialogFilter> Filters;
    Filters.push_back(WindowEventProducer::FileDialogFilter("Lua File Type","lua"));
    Filters.push_back(WindowEventProducer::FileDialogFilter("All","*"));

    std::vector<BoostPath> FilesToOpen;
    FilesToOpen = dynamic_cast<Component*>(details->getSource())->
        getParentWindow()->getParentDrawingSurface()->getEventProducer()->openFileDialog("Open Lua Script File.",
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
            CodeTextArea->setText(InStrStream.str());
            clearError();
        }
    }
}

void handlLuaError(LuaErrorEventDetails* const details)
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
    ErrorTextArea->moveCaretToEnd();
    if(ErrorTextArea->getText().size() != 0)
    {
        ErrorTextArea->write("\n");
    }
    ErrorTextArea->write(ErrorType + ":\n    " + details->getErrorString());

    //Select the Error Tab
    InfoTabPanel->setSelectedIndex(1);

    //Fill Stack Trace
    if(details->getStatus() == LUA_ERRMEM ||
       details->getStatus() == LUA_ERRERR ||
       details->getStatus() == LUA_ERRRUN)
    {
        std::stringstream ss;
        ss << "Lua Stack Trace: " << std::endl;

        //MFString::StorageType::const_iterator ListItor(details->getMFStackTrace()->begin());
        //for(; ListItor != details->getMFStackTrace()->end() ; ++ListItor)
        //{
        //ss << "     " << (*ListItor) << std::endl;
        //}
        //StackTraceTextArea->write(ss.str());
    }
}

void codeAreaCaretChanged(CaretEventDetails* const details)
{
    //Update Caret Position Labels
    //Line
    LineValueLabel->setText(boost::lexical_cast<std::string>(CodeTextArea->getCaretLine()+1));

    //Column
    ColumnValueLabel->setText(boost::lexical_cast<std::string>(CodeTextArea->getCaretColumn()+1));
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

        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1));

        // Make Torus Node (creates Torus in background of scene)
        NodeRecPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);
        setName(TorusGeometryNode,"TorusGeometryNode");

        // Make Main Scene Node and add the Torus
        NodeRecPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(TorusGeometryNode);
        setName(scene,"Scene Node");

        // Create the Graphics
        GraphicsRecPtr TutorialGraphics = Graphics2D::create();

        // Initialize the LookAndFeelManager to enable default settings
        LookAndFeelManager::the()->getLookAndFeel()->init();


        //Create the default font
        CodeFont = UIFont::create();
        CodeFont->setFamily("Courier New");
        CodeFont->setSize(18);
        CodeFont->setGlyphPixelSize(20);
        CodeFont->setAntiAliasing(true);

        // Create a TextArea component
        CodeTextArea = TextArea::create();

        CodeTextArea->setPreferredSize(Vec2f(600, 600));
        CodeTextArea->setText("print(\"Hello World\")");
        CodeTextArea->setMinSize(Vec2f(300, 600));
        CodeTextArea->setFont(CodeFont);
        CodeTextArea->setTextColors(Color4f(0.0,0.0,0.0,1.0));
        setName(CodeTextArea,"Code TextArea");

        // Create a ScrollPanel
        ScrollPanelRecPtr TextAreaScrollPanel = ScrollPanel::create();
        TextAreaScrollPanel->setPreferredSize(Vec2f(200,600));
        TextAreaScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        // Add the TextArea to the ScrollPanel so it is displayed
        TextAreaScrollPanel->setViewComponent(CodeTextArea);

        //Create the Error Text Area
        ErrorTextArea = TextArea::create();

        ErrorTextArea->setPreferredSize(Vec2f(600, 150));
        ErrorTextArea->setText("");
        ErrorTextArea->setMinSize(Vec2f(300, 150));
        ErrorTextArea->setFont(CodeFont);
        ErrorTextArea->setTextColors(Color4f(0.2,0.0,0.0,1.0));
        ErrorTextArea->setEditable(false);
        setName(ErrorTextArea,"Error TextArea");
        LuaManager::the()->connectLuaError(boost::bind(&handlLuaError, _1));

        // Create a ScrollPanel
        ScrollPanelRecPtr ErrorAreaScrollPanel = ScrollPanel::create();
        ErrorAreaScrollPanel->setPreferredSize(Vec2f(200,150));
        ErrorAreaScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        // Add the TextArea to the ScrollPanel so it is displayed
        ErrorAreaScrollPanel->setViewComponent(ErrorTextArea);

        //Create the StackTrace Text Area
        StackTraceTextArea = TextArea::create();

        StackTraceTextArea->setPreferredSize(Vec2f(600, 150));
        StackTraceTextArea->setText("");
        StackTraceTextArea->setMinSize(Vec2f(300, 150));
        StackTraceTextArea->setFont(CodeFont);
        StackTraceTextArea->setTextColors(Color4f(0.2,0.0,0.0,1.0));
        StackTraceTextArea->setEditable(false);
        setName(StackTraceTextArea,"Stack Trace TextArea");

        // Create a ScrollPanel
        ScrollPanelRecPtr StackTraceAreaScrollPanel = ScrollPanel::create();
        StackTraceAreaScrollPanel->setPreferredSize(Vec2f(200,150));
        StackTraceAreaScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        // Add the TextArea to the ScrollPanel so it is displayed
        StackTraceAreaScrollPanel->setViewComponent(StackTraceTextArea);

        //Create the Message Text Area
        MessageTextArea = TextArea::create();

        MessageTextArea->setPreferredSize(Vec2f(600, 150));
        MessageTextArea->setText("");
        MessageTextArea->setMinSize(Vec2f(300, 150));
        MessageTextArea->setFont(CodeFont);
        MessageTextArea->setTextColors(Color4f(0.2,0.0,0.0,1.0));
        MessageTextArea->setEditable(false);
        setName(MessageTextArea,"Message TextArea");

        // Create a ScrollPanel
        ScrollPanelRecPtr MessageAreaScrollPanel = ScrollPanel::create();
        MessageAreaScrollPanel->setPreferredSize(Vec2f(200,150));
        MessageAreaScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        // Add the TextArea to the ScrollPanel so it is displayed
        MessageAreaScrollPanel->setViewComponent(MessageTextArea);

        //Tab Panel
        LabelRecPtr MessageTabLabel = Label::create();
        MessageTabLabel->setText("Output");

        LabelRecPtr ErrorTabLabel = Label::create();
        ErrorTabLabel->setText("Error");

        LabelRecPtr StackTraceTabLabel = Label::create();
        StackTraceTabLabel->setText("Stack");

        InfoTabPanel = TabPanel::create();
        InfoTabPanel->addTab(MessageTabLabel, MessageAreaScrollPanel);
        InfoTabPanel->addTab(ErrorTabLabel, ErrorAreaScrollPanel);
        InfoTabPanel->addTab(StackTraceTabLabel, StackTraceAreaScrollPanel);
        InfoTabPanel->setTabAlignment(0.5f);
        InfoTabPanel->setTabPlacement(TabPanel::PLACEMENT_NORTH);
        InfoTabPanel->setSelectedIndex(0);
        setName(InfoTabPanel,"Info Tab Panel");


        //Split Panel
        BorderLayoutConstraintsRecPtr SplitPanelConstraints = BorderLayoutConstraints::create();
        SplitPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);

        SplitPanelRecPtr MainSplitPanel = SplitPanel::create();
        MainSplitPanel->setMinComponent(TextAreaScrollPanel);
        MainSplitPanel->setMaxComponent(InfoTabPanel);
        MainSplitPanel->setOrientation(SplitPanel::VERTICAL_ORIENTATION);
        MainSplitPanel->setDividerPosition(0.7);
        // location from the left/top
        MainSplitPanel->setDividerSize(4);
        MainSplitPanel->setMaxDividerPosition(.8);
        MainSplitPanel->setMinDividerPosition(.2);
        MainSplitPanel->setConstraints(SplitPanelConstraints);


        //Execute Script Button
        ButtonRecPtr ExecuteButton = Button::create();
        ExecuteButton->setText("Execute");
        setName(ExecuteButton,"Execute Button");
        ExecuteButton->connectActionPerformed(boost::bind(&executeScriptButtonAction, _1));

        ButtonRecPtr OpenButton = Button::create();
        OpenButton->setText("Open");
        setName(OpenButton,"Open Button");
        OpenButton->connectActionPerformed(boost::bind(&openScriptButtonAction, _1));

        ButtonRecPtr SaveButton = Button::create();
        SaveButton->setText("Save");
        setName(SaveButton,"Save Button");
        SaveButton->connectActionPerformed(boost::bind(&saveScriptButtonAction, _1));

        ButtonRecPtr ClearButton = Button::create();
        ClearButton->setText("Clear");
        setName(ClearButton,"Clear Button");
        ClearButton->connectActionPerformed(boost::bind(&clearScriptButtonAction, _1));

        //Make the Button Panel
        FlowLayoutRecPtr ButtonPanelLayout = FlowLayout::create();
        ButtonPanelLayout->setOrientation(FlowLayout::HORIZONTAL_ORIENTATION);

        BorderLayoutConstraintsRecPtr ButtonPanelConstraints = BorderLayoutConstraints::create();
        ButtonPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_NORTH);
        PanelRecPtr ButtonPanel = Panel::createEmpty();
        ButtonPanel->setPreferredSize(Vec2f(400.0f, 50.0f));
        ButtonPanel->pushToChildren(ExecuteButton);
        ButtonPanel->pushToChildren(OpenButton);
        ButtonPanel->pushToChildren(SaveButton);
        ButtonPanel->pushToChildren(ClearButton);
        ButtonPanel->setLayout(ButtonPanelLayout);
        ButtonPanel->setConstraints(ButtonPanelConstraints);
        setName(ButtonPanel,"Button Panel");

        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        BorderLayoutRecPtr MainInternalWindowLayout = BorderLayout::create();

        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
        MainInternalWindow->pushToChildren(ButtonPanel);
        MainInternalWindow->pushToChildren(MainSplitPanel);
        MainInternalWindow->setLayout(MainInternalWindowLayout);
        MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
        MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.85f,0.85f));
        MainInternalWindow->setDrawTitlebar(false);
        MainInternalWindow->setResizable(false);
        setName(MainInternalWindow,"Internal Window");

        // Create the Drawing Surface
        UIDrawingSurfaceRecPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);

        TutorialDrawingSurface->openWindow(MainInternalWindow);

        // Create the UI Foreground Object
        UIForegroundRecPtr TutorialUIForeground = UIForeground::create();

        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);

        //Scene Background
        GradientBackgroundRecPtr SceneBackground = GradientBackground::create();
        SceneBackground->addLine(Color3f(0.0,0.0,0.0),0.0);
        setName(SceneBackground,"Scene Background");


        // Tell the Manager what to manage
        sceneManager.setRoot(scene);

        // Add the UI Foreground Object to the Scene
        ViewportRecPtr TutorialViewport = sceneManager.getWindow()->getPort(0);
        TutorialViewport->addForeground(TutorialUIForeground);
        TutorialViewport->setBackground(SceneBackground);

        // Show the whole Scene
        sceneManager.showAll();


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "02LuaConsole");

        //Enter main Loop
        TutorialWindow->mainLoop();
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

