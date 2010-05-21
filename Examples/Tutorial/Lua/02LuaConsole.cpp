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

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;
TextAreaRefPtr CodeTextArea;
TextAreaRefPtr ErrorTextArea;
TextAreaRefPtr MessageTextArea;
TextAreaRefPtr StackTraceTextArea;
TabPanelRefPtr InfoTabPanel;
UIFontRefPtr CodeFont;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);



void clearError(void)
{
        ErrorTextArea->setText("");
        StackTraceTextArea->setText("");
}

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
       if(e->getKey() == KeyEvent::KEY_E && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
       {
           clearError();
           LuaManager::the()->runScript(CodeTextArea->getText());
       }
   }

   virtual void keyReleased(const KeyEventUnrecPtr e)
   {
   }

   virtual void keyTyped(const KeyEventUnrecPtr e)
   {
   }
};

class ExecuteScriptButtonAction : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEventUnrecPtr e)
   {
       clearError();
       LuaManager::the()->runScript(CodeTextArea->getText());
   }
};


class ClearScriptButtonAction : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEventUnrecPtr e)
   {
       CodeTextArea->selectAll();
       CodeTextArea->deleteSelectedText();
       clearError();
   }
};


class SaveScriptButtonAction : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEventUnrecPtr e)
   {
		std::vector<WindowEventProducer::FileDialogFilter> Filters;
        Filters.push_back(WindowEventProducer::FileDialogFilter("Lua File Type","lua"));
        Filters.push_back(WindowEventProducer::FileDialogFilter("All","*"));

		BoostPath SavePath = TutorialWindow->saveFileDialog("Save Lua Script to?",
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
};


class OpenScriptButtonAction : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEventUnrecPtr e)
   {
        //Get a file using the open file dialog
        std::vector<WindowEventProducer::FileDialogFilter> Filters;
        Filters.push_back(WindowEventProducer::FileDialogFilter("Lua File Type","lua"));
        Filters.push_back(WindowEventProducer::FileDialogFilter("All","*"));

		std::vector<BoostPath> FilesToOpen;
		FilesToOpen = TutorialWindow->openFileDialog("Open Lua Script File.",
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
};

class LuaErrorListener : public LuaListener
{
public:

    virtual void error(const LuaErrorEventUnrecPtr e)
    {
        std::string ErrorType("");
        switch(e->getStatus())
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
        ErrorTextArea->write(ErrorType + ":\n    " + e->getErrorString());

        //Select the Error Tab
        InfoTabPanel->setSelectedIndex(1);

        //Fill Stack Trace
        if(e->getStackTraceEnabled() && 
            (e->getStatus() == LUA_ERRMEM ||
             e->getStatus() == LUA_ERRERR ||
             e->getStatus() == LUA_ERRRUN))
        {
            std::stringstream ss;
            ss << "Lua Stack Trace: " << std::endl;
            
            MFString::StorageType::const_iterator ListItor(e->getMFStackTrace()->begin());
            for(; ListItor != e->getMFStackTrace()->end() ; ++ListItor)
            {
                ss << "     " << (*ListItor) << std::endl;
            }
            StackTraceTextArea->write(ss.str());
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

    TutorialKeyListener TheKeyListener;
    TutorialWindow->addKeyListener(&TheKeyListener);

    // Make Torus Node (creates Torus in background of scene)
    NodeRefPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);
    setName(TorusGeometryNode,"TorusGeometryNode");

    // Make Main Scene Node and add the Torus
    NodeRefPtr scene = OSG::Node::create();
        scene->setCore(OSG::Group::create());
        scene->addChild(TorusGeometryNode);
    setName(scene,"Scene Node");

    // Create the Graphics
    GraphicsRefPtr TutorialGraphics = OSG::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();


    //Create the default font
    CodeFont = OSG::UIFont::create();
        CodeFont->setFamily("Courier New");
        CodeFont->setSize(18);
        CodeFont->setGlyphPixelSize(20);
        CodeFont->setAntiAliasing(true);

    // Create a TextArea component
    CodeTextArea = OSG::TextArea::create();

        CodeTextArea->setPreferredSize(Vec2f(600, 600));
        CodeTextArea->setText("print(\"Hello World\")");
        CodeTextArea->setMinSize(Vec2f(300, 600));
        CodeTextArea->setFont(CodeFont);
        CodeTextArea->setTextColors(Color4f(0.0,0.0,0.0,1.0));
    setName(CodeTextArea,"Code TextArea");
        
    // Create a ScrollPanel
    ScrollPanelRefPtr TextAreaScrollPanel = ScrollPanel::create();
        TextAreaScrollPanel->setPreferredSize(Vec2f(200,600));
        TextAreaScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    // Add the TextArea to the ScrollPanel so it is displayed
	TextAreaScrollPanel->setViewComponent(CodeTextArea);
    
    //Create the Error Text Area
    ErrorTextArea = OSG::TextArea::create();

        ErrorTextArea->setPreferredSize(Vec2f(600, 150));
        ErrorTextArea->setText("");
        ErrorTextArea->setMinSize(Vec2f(300, 150));
        ErrorTextArea->setFont(CodeFont);
        ErrorTextArea->setTextColors(Color4f(0.2,0.0,0.0,1.0));
        ErrorTextArea->setEditable(false);
    setName(ErrorTextArea,"Error TextArea");
    LuaErrorListener  TheLuaErrorListener;
    LuaManager::the()->addLuaListener(&TheLuaErrorListener);
    
    // Create a ScrollPanel
    ScrollPanelRefPtr ErrorAreaScrollPanel = ScrollPanel::create();
        ErrorAreaScrollPanel->setPreferredSize(Vec2f(200,150));
        ErrorAreaScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    // Add the TextArea to the ScrollPanel so it is displayed
	ErrorAreaScrollPanel->setViewComponent(ErrorTextArea);

    //Create the StackTrace Text Area
    StackTraceTextArea = OSG::TextArea::create();

        StackTraceTextArea->setPreferredSize(Vec2f(600, 150));
        StackTraceTextArea->setText("");
        StackTraceTextArea->setMinSize(Vec2f(300, 150));
        StackTraceTextArea->setFont(CodeFont);
        StackTraceTextArea->setTextColors(Color4f(0.2,0.0,0.0,1.0));
        StackTraceTextArea->setEditable(false);
    setName(StackTraceTextArea,"Stack Trace TextArea");
    
    // Create a ScrollPanel
    ScrollPanelRefPtr StackTraceAreaScrollPanel = ScrollPanel::create();
        StackTraceAreaScrollPanel->setPreferredSize(Vec2f(200,150));
        StackTraceAreaScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    // Add the TextArea to the ScrollPanel so it is displayed
	StackTraceAreaScrollPanel->setViewComponent(StackTraceTextArea);
    
    //Create the Message Text Area
    MessageTextArea = OSG::TextArea::create();

        MessageTextArea->setPreferredSize(Vec2f(600, 150));
        MessageTextArea->setText("");
        MessageTextArea->setMinSize(Vec2f(300, 150));
        MessageTextArea->setFont(CodeFont);
        MessageTextArea->setTextColors(Color4f(0.2,0.0,0.0,1.0));
        MessageTextArea->setEditable(false);
    setName(MessageTextArea,"Message TextArea");
    
    // Create a ScrollPanel
    ScrollPanelRefPtr MessageAreaScrollPanel = ScrollPanel::create();
        MessageAreaScrollPanel->setPreferredSize(Vec2f(200,150));
        MessageAreaScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    // Add the TextArea to the ScrollPanel so it is displayed
	MessageAreaScrollPanel->setViewComponent(MessageTextArea);

    //Tab Panel
    LabelRefPtr MessageTabLabel = OSG::Label::create();
        MessageTabLabel->setText("Output");

    LabelRefPtr ErrorTabLabel = OSG::Label::create();
        ErrorTabLabel->setText("Error");

    LabelRefPtr StackTraceTabLabel = OSG::Label::create();
        StackTraceTabLabel->setText("Stack");

    

    InfoTabPanel = OSG::TabPanel::create();
        InfoTabPanel->addTab(MessageTabLabel, MessageAreaScrollPanel);
        InfoTabPanel->addTab(ErrorTabLabel, ErrorAreaScrollPanel);
        InfoTabPanel->addTab(StackTraceTabLabel, StackTraceAreaScrollPanel);
        InfoTabPanel->setTabAlignment(0.5f);
        InfoTabPanel->setTabPlacement(TabPanel::PLACEMENT_NORTH);
    InfoTabPanel->setSelectedIndex(0);
    setName(InfoTabPanel,"Info Tab Panel");


    //Split Panel
    BorderLayoutConstraintsRefPtr SplitPanelConstraints = BorderLayoutConstraints::create();
        SplitPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);

    SplitPanelRefPtr MainSplitPanel = OSG::SplitPanel::create();
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
    ButtonRefPtr ExecuteButton = Button::create();
        ExecuteButton->setText("Execute");
    setName(ExecuteButton,"Execute Button");
    ExecuteScriptButtonAction TheExecuteScriptButtonAction;
    ExecuteButton->addActionListener(&TheExecuteScriptButtonAction);
    
    ButtonRefPtr OpenButton = Button::create();
        OpenButton->setText("Open");
    setName(OpenButton,"Open Button");
    OpenScriptButtonAction TheOpenScriptButtonAction;
    OpenButton->addActionListener(&TheOpenScriptButtonAction);
    
    ButtonRefPtr SaveButton = Button::create();
        SaveButton->setText("Save");
    setName(SaveButton,"Save Button");
    SaveScriptButtonAction TheSaveScriptButtonAction;
    SaveButton->addActionListener(&TheSaveScriptButtonAction);
    
    ButtonRefPtr ClearButton = Button::create();
        ClearButton->setText("Clear");
    setName(ClearButton,"Clear Button");
    ClearScriptButtonAction TheClearScriptButtonAction;
    ClearButton->addActionListener(&TheClearScriptButtonAction);

    //Make the Button Panel
    FlowLayoutRefPtr ButtonPanelLayout = OSG::FlowLayout::create();
        ButtonPanelLayout->setOrientation(FlowLayout::HORIZONTAL_ORIENTATION);

    BorderLayoutConstraintsRefPtr ButtonPanelConstraints = BorderLayoutConstraints::create();
        ButtonPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_NORTH);
    PanelRefPtr ButtonPanel = Panel::createEmpty();
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
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    BorderLayoutRefPtr MainInternalWindowLayout = BorderLayout::create();

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
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
    UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);
	
	TutorialDrawingSurface->openWindow(MainInternalWindow);

    // Create the UI Foreground Object
    UIForegroundRefPtr TutorialUIForeground = OSG::UIForeground::create();

        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);

    //Scene Background
    GradientBackgroundRefPtr SceneBackground = GradientBackground::create();
    SceneBackground->addLine(Color3f(0.0,0.0,0.0),0.0);
    setName(SceneBackground,"Scene Background");

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindow);
    mgr->setRoot(scene);

    // Add the UI Foreground Object to the Scene
    ViewportRefPtr TutorialViewport = mgr->getWindow()->getPort(0);
        TutorialViewport->addForeground(TutorialUIForeground);
        TutorialViewport->setBackground(SceneBackground);

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
            WinSize,
            "02LuaConsole");

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

