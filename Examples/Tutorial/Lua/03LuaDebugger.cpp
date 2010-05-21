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

//Lua Manager
#include "OSGLuaManager.h"

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
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
LabelRefPtr ColumnValueLabel;
LabelRefPtr LineValueLabel;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);
std::string getCodeText(void);



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

// Create a class to allow for the use of the Ctrl+q
class CodeAreaCaretListener : public CaretListener
{
public:
    virtual void caretChanged(const CaretEventUnrecPtr e)
    {
        //Update Caret Position Labels
        //Line
            LineValueLabel->setText(boost::lexical_cast<std::string>(CodeTextArea->getCaretLine()+1));

        //Column
            ColumnValueLabel->setText(boost::lexical_cast<std::string>(CodeTextArea->getCaretColumn()+1));
    }
};

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindow = createNativeWindow();
    setName(TutorialWindow,"Tutorial Window Event Producer");

    TutorialWindow->initWindow();

    TutorialWindow->setDisplayCallback(display);
    TutorialWindow->setReshapeCallback(reshape);

    TutorialKeyListener TheKeyListener;
    TutorialWindow->addKeyListener(&TheKeyListener);


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
    NodeRefPtr scene = OSG::Node::create();
        scene->setCore(OSG::Group::create());
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
    GraphicsRefPtr TutorialGraphics = OSG::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();


    //Create the default font
    CodeFont = OSG::UIFont::create();
        CodeFont->setFamily("Courier New");
        CodeFont->setSize(21);
        CodeFont->setGlyphPixelSize(22);
        CodeFont->setAntiAliasing(false);

    // Create a TextArea component
    CodeTextArea = OSG::TextArea::create();

        CodeTextArea->setPreferredSize(Vec2f(600, 600));
        CodeTextArea->setText(getCodeText());
        CodeTextArea->setMinSize(Vec2f(300, 600));
        CodeTextArea->setFont(CodeFont);
        CodeTextArea->setTextColors(Color4f(0.0,0.0,0.0,1.0));
    setName(CodeTextArea,"Code TextArea");
    CodeAreaCaretListener TheCodeAreaCaretListener;
    CodeTextArea->addCaretListener(&TheCodeAreaCaretListener);

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

    //Code Area Info
    LabelRefPtr LineLabel = Label::create();
        LineLabel->setText("Line:");
        LineLabel->setPreferredSize(Vec2f(40.0f, 30.0f));
        LineLabel->setAlignment(Vec2f(1.0f, 0.5f));

    LineValueLabel = Label::create();
        LineValueLabel->setText("");
        LineValueLabel->setPreferredSize(Vec2f(40.0f, 30.0f));

    LabelRefPtr ColumnLabel = Label::create();
        ColumnLabel->setText("Column:");
        ColumnLabel->setPreferredSize(Vec2f(55.0f, 30.0f));
        ColumnLabel->setAlignment(Vec2f(1.0f, 0.5f));

    ColumnValueLabel = Label::create();
        ColumnValueLabel->setText("");
        ColumnValueLabel->setPreferredSize(Vec2f(40.0f, 30.0f));
    //TextArea Info Panel
    BorderLayoutConstraintsRefPtr CodeAreaInfoPanelConstraints = BorderLayoutConstraints::create();
        CodeAreaInfoPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_SOUTH);

    PanelRefPtr CodeAreaInfoPanel = Panel::create();

    SpringLayoutRefPtr CodeAreaInfoLayout = OSG::SpringLayout::create();

	//ColumnValueLabel
    CodeAreaInfoLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, ColumnValueLabel, 0, SpringLayoutConstraints::NORTH_EDGE, CodeAreaInfoPanel);
    CodeAreaInfoLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, ColumnValueLabel, 0, SpringLayoutConstraints::SOUTH_EDGE, CodeAreaInfoPanel);
    CodeAreaInfoLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, ColumnValueLabel, 0, SpringLayoutConstraints::EAST_EDGE, CodeAreaInfoPanel);

	//ColumnLabel    
    CodeAreaInfoLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, ColumnLabel, 0, SpringLayoutConstraints::NORTH_EDGE, CodeAreaInfoPanel);
    CodeAreaInfoLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, ColumnLabel, 0, SpringLayoutConstraints::SOUTH_EDGE, CodeAreaInfoPanel);
    CodeAreaInfoLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, ColumnLabel, -1, SpringLayoutConstraints::WEST_EDGE, ColumnValueLabel);

	//LineValueLabel    
    CodeAreaInfoLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, LineValueLabel, 0, SpringLayoutConstraints::NORTH_EDGE, CodeAreaInfoPanel);
    CodeAreaInfoLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, LineValueLabel, 0, SpringLayoutConstraints::SOUTH_EDGE, CodeAreaInfoPanel);
    CodeAreaInfoLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, LineValueLabel, -1, SpringLayoutConstraints::WEST_EDGE, ColumnLabel);

	//LineLabel    
    CodeAreaInfoLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, LineLabel, 0, SpringLayoutConstraints::NORTH_EDGE, CodeAreaInfoPanel);
    CodeAreaInfoLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, LineLabel, 0, SpringLayoutConstraints::SOUTH_EDGE, CodeAreaInfoPanel);
    CodeAreaInfoLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, LineLabel, -1, SpringLayoutConstraints::WEST_EDGE, LineValueLabel);

       CodeAreaInfoPanel->setPreferredSize(Vec2f(400.0f, 22.0f));
       CodeAreaInfoPanel->pushToChildren(LineLabel);
       CodeAreaInfoPanel->pushToChildren(LineValueLabel);
       CodeAreaInfoPanel->pushToChildren(ColumnLabel);
       CodeAreaInfoPanel->pushToChildren(ColumnValueLabel);
       CodeAreaInfoPanel->setConstraints(CodeAreaInfoPanelConstraints);
       CodeAreaInfoPanel->setBorders(NULL);
       CodeAreaInfoPanel->setLayout(CodeAreaInfoLayout);

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    BorderLayoutRefPtr MainInternalWindowLayout = BorderLayout::create();

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
       MainInternalWindow->pushToChildren(ButtonPanel);
       MainInternalWindow->pushToChildren(MainSplitPanel);
       MainInternalWindow->pushToChildren(CodeAreaInfoPanel);
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
    mgr->setRoot(RootNode);
    //mgr->setHeadlight(false);

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
                               "03LuaDebugger");

	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setPreferredSize(WinSize * 0.85);

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

std::string getCodeText(void)
{
	return "print(\"Hello World\")";
}

