// OpenSG Tutorial Example: Creating a Text area to run a Lua script from
//

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGGradientBackground.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include <OpenSG/OSGDirectionalLight.h>
#include <OpenSG/OSGGeoFunctions.h>

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

#include <OpenSG/UserInterface/OSGLayers.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGBorderLayout.h>
#include <OpenSG/UserInterface/OSGBorderLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGUIFont.h>
#include <OpenSG/UserInterface/OSGScrollPanel.h>
#include <OpenSG/UserInterface/OSGTextArea.h>
#include <OpenSG/UserInterface/OSGTabPanel.h>
#include <OpenSG/UserInterface/OSGSplitPanel.h>
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGSpringLayout.h>
#include <OpenSG/UserInterface/OSGSpringLayoutConstraints.h>

//Lua Manager
#include <OpenSG/Lua/OSGLuaManager.h>

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;
TextAreaPtr CodeTextArea;
TextAreaPtr ErrorTextArea;
TextAreaPtr MessageTextArea;
TextAreaPtr StackTraceTextArea;
TabPanelPtr InfoTabPanel;
UIFontPtr CodeFont;
LabelPtr ColumnValueLabel;
LabelPtr LineValueLabel;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);



void clearError(void)
{
    beginEditCP(ErrorTextArea, TextArea::TextFieldMask);
        ErrorTextArea->setText("");
    endEditCP(ErrorTextArea, TextArea::TextFieldMask);
    beginEditCP(StackTraceTextArea, TextArea::TextFieldMask);
        StackTraceTextArea->setText("");
    endEditCP(StackTraceTextArea, TextArea::TextFieldMask);
}

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEvent& e)
   {
       if(e.getKey() == KeyEvent::KEY_Q && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
            TutorialWindowEventProducer->closeWindow();
       }
       if(e.getKey() == KeyEvent::KEY_E && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           clearError();
           LuaManager::the()->runScript(CodeTextArea->getText());
       }
   }

   virtual void keyReleased(const KeyEvent& e)
   {
   }

   virtual void keyTyped(const KeyEvent& e)
   {
   }
};

class ExecuteScriptButtonAction : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
   {
       clearError();
       LuaManager::the()->runScript(CodeTextArea->getText());
   }
};


class ClearScriptButtonAction : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
   {
       CodeTextArea->selectAll();
       CodeTextArea->deleteSelectedText();
       clearError();
   }
};


class SaveScriptButtonAction : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
   {
		std::vector<WindowEventProducer::FileDialogFilter> Filters;
        Filters.push_back(WindowEventProducer::FileDialogFilter("Lua File Type","lua"));
        Filters.push_back(WindowEventProducer::FileDialogFilter("All","*"));

		Path SavePath = TutorialWindowEventProducer->saveFileDialog("Save Lua Script to?",
			Filters,
			std::string("LuaScript.lua"),
			Path("Data"),
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

   virtual void actionPerformed(const ActionEvent& e)
   {
        //Get a file using the open file dialog
        std::vector<WindowEventProducer::FileDialogFilter> Filters;
        Filters.push_back(WindowEventProducer::FileDialogFilter("Lua File Type","lua"));
        Filters.push_back(WindowEventProducer::FileDialogFilter("All","*"));

		std::vector<Path> FilesToOpen;
		FilesToOpen = TutorialWindowEventProducer->openFileDialog("Open Lua Script File.",
			Filters,
			Path("Data"),
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
                beginEditCP(CodeTextArea, TextArea::TextFieldMask);
                    CodeTextArea->setText(InStrStream.str());
                endEditCP(CodeTextArea, TextArea::TextFieldMask);
               clearError();
            }
        }
   }
};

class LuaErrorListener : public LuaListener
{
public:

    virtual void error(const LuaErrorEvent& e)
    {
        std::string ErrorType("");
        switch(e.getStatus())
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
        ErrorTextArea->write(ErrorType + ":\n    " + e.getErrorString());

        //Select the Error Tab
        InfoTabPanel->setSelectedIndex(1);

        //Fill Stack Trace
        if(e.getEnableStackTrace() && 
            (e.getStatus() == LUA_ERRMEM ||
             e.getStatus() == LUA_ERRERR ||
             e.getStatus() == LUA_ERRRUN))
        {
            std::stringstream ss;
            ss << "Lua Stack Trace: " << std::endl;
            
            std::list<std::string>::const_iterator ListItor(e.getStackTrace().begin());
            for(; ListItor != e.getStackTrace().end() ; ++ListItor)
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
    virtual void caretChanged(const CaretEvent& e)
    {
        //Update Caret Position Labels
        //Line
        beginEditCP(LineValueLabel, Label::TextFieldMask);
            LineValueLabel->setText(boost::lexical_cast<std::string>(CodeTextArea->getCaretLine()+1));
        endEditCP(LineValueLabel, Label::TextFieldMask);

        //Column
        beginEditCP(ColumnValueLabel, Label::TextFieldMask);
            ColumnValueLabel->setText(boost::lexical_cast<std::string>(CodeTextArea->getCaretColumn()+1));
        endEditCP(ColumnValueLabel, Label::TextFieldMask);
    }
};

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    TutorialKeyListener TheKeyListener;
    TutorialWindowEventProducer->addKeyListener(&TheKeyListener);

    // Make Torus Node (creates Torus in background of scene)
    GeometryPtr TorusGeometry = makeTorusGeo(.5, 2, 16, 16);
    setName(TorusGeometry,"Torus Geometry");
    calcVertexTangents(TorusGeometry,0,Geometry::TexCoords7FieldId, Geometry::TexCoords6FieldId);


    NodePtr TorusGeometryNode = Node::create();
    setName(TorusGeometryNode,"Torus Geometry Node");
    beginEditCP(TorusGeometryNode, Node::CoreFieldMask);
        TorusGeometryNode->setCore(TorusGeometry);
    endEditCP(TorusGeometryNode, Node::CoreFieldMask);

    // Make Main Scene Node and add the Torus
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
        scene->addChild(TorusGeometryNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    setName(scene,"Scene Node");

    //Light Beacon Node
    TransformPtr TheLightBeaconNodeTransform = Transform::create();
    beginEditCP(TheLightBeaconNodeTransform);
    endEditCP(TheLightBeaconNodeTransform);

    NodePtr TheLightBeaconNode = Node::create();
    beginEditCP(TheLightBeaconNode, Node::CoreFieldMask);
        TheLightBeaconNode->setCore(TheLightBeaconNodeTransform);
    endEditCP(TheLightBeaconNode, Node::CoreFieldMask);
    setName(TheLightBeaconNode,"Light Beacon Node");


    //Light Node
    DirectionalLightPtr TheLightCore = DirectionalLight::create();
    beginEditCP(TheLightCore);
        TheLightCore->setDirection(Vec3f(1.0,0.0,0.0));
        TheLightCore->setAmbient(Color4f(1.0,1.0,1.0,1.0));
        TheLightCore->setDiffuse(Color4f(1.0,1.0,1.0,1.0));
        TheLightCore->setSpecular(Color4f(1.0,1.0,1.0,1.0));
        TheLightCore->setBeacon(TheLightBeaconNode);
    endEditCP(TheLightCore);

    NodePtr TheLightNode = Node::create();
    beginEditCP(TheLightNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        TheLightNode->setCore(TheLightCore);
        TheLightNode->addChild(scene);
    endEditCP(TheLightNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
    setName(TheLightNode,"Light Node");
    
    NodePtr RootNode = Node::create();
    beginEditCP(RootNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        RootNode->setCore(Group::create());
        RootNode->addChild(TheLightNode);
        RootNode->addChild(TheLightBeaconNode);
    endEditCP(RootNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
    setName(RootNode,"Root Node");

    // Create the Graphics
    GraphicsPtr TutorialGraphics = osg::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();


    //Create the default font
    CodeFont = osg::UIFont::create();
    beginEditCP(CodeFont, UIFont::SizeFieldMask | UIFont::FamilyFieldMask | UIFont::AntiAliasingFieldMask);
        CodeFont->setFamily("Courier New");
        CodeFont->setSize(18);
        CodeFont->setGlyphPixelSize(20);
        CodeFont->setAntiAliasing(true);
    endEditCP(CodeFont, UIFont::SizeFieldMask | UIFont::FamilyFieldMask | UIFont::AntiAliasingFieldMask);

    // Create a TextArea component
    CodeTextArea = osg::TextArea::create();

    beginEditCP(CodeTextArea, TextArea::MinSizeFieldMask | TextArea::TextFieldMask | TextArea::PreferredSizeFieldMask | TextArea::FontFieldMask);
        CodeTextArea->setPreferredSize(Vec2f(600, 600));
        CodeTextArea->setText("print(\"Hello World\")");
        CodeTextArea->setMinSize(Vec2f(300, 600));
        CodeTextArea->setFont(CodeFont);
        CodeTextArea->setTextColors(Color4f(0.0,0.0,0.0,1.0));
    endEditCP(CodeTextArea, TextArea::MinSizeFieldMask | TextArea::TextFieldMask | TextArea::PreferredSizeFieldMask | TextArea::FontFieldMask);
    setName(CodeTextArea,"Code TextArea");
    CodeAreaCaretListener TheCodeAreaCaretListener;
    CodeTextArea->addCaretListener(&TheCodeAreaCaretListener);

    // Create a ScrollPanel
    ScrollPanelPtr TextAreaScrollPanel = ScrollPanel::create();
    beginEditCP(TextAreaScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        TextAreaScrollPanel->setPreferredSize(Vec2f(200,600));
        TextAreaScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(TextAreaScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    // Add the TextArea to the ScrollPanel so it is displayed
	TextAreaScrollPanel->setViewComponent(CodeTextArea);
    
    //Create the Error Text Area
    ErrorTextArea = osg::TextArea::create();

    beginEditCP(ErrorTextArea, TextArea::MinSizeFieldMask | TextArea::TextFieldMask | TextArea::PreferredSizeFieldMask | TextArea::FontFieldMask);
        ErrorTextArea->setPreferredSize(Vec2f(600, 150));
        ErrorTextArea->setText("");
        ErrorTextArea->setMinSize(Vec2f(300, 150));
        ErrorTextArea->setFont(CodeFont);
        ErrorTextArea->setTextColors(Color4f(0.2,0.0,0.0,1.0));
        ErrorTextArea->setEditable(false);
    endEditCP(ErrorTextArea, TextArea::MinSizeFieldMask | TextArea::TextFieldMask | TextArea::PreferredSizeFieldMask | TextArea::FontFieldMask);
    setName(ErrorTextArea,"Error TextArea");
    LuaErrorListener  TheLuaErrorListener;
    LuaManager::the()->addLuaListener(&TheLuaErrorListener);
    
    // Create a ScrollPanel
    ScrollPanelPtr ErrorAreaScrollPanel = ScrollPanel::create();
    beginEditCP(ErrorAreaScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        ErrorAreaScrollPanel->setPreferredSize(Vec2f(200,150));
        ErrorAreaScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(ErrorAreaScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    // Add the TextArea to the ScrollPanel so it is displayed
	ErrorAreaScrollPanel->setViewComponent(ErrorTextArea);

    //Create the StackTrace Text Area
    StackTraceTextArea = osg::TextArea::create();

    beginEditCP(StackTraceTextArea, TextArea::MinSizeFieldMask | TextArea::TextFieldMask | TextArea::PreferredSizeFieldMask | TextArea::FontFieldMask);
        StackTraceTextArea->setPreferredSize(Vec2f(600, 150));
        StackTraceTextArea->setText("");
        StackTraceTextArea->setMinSize(Vec2f(300, 150));
        StackTraceTextArea->setFont(CodeFont);
        StackTraceTextArea->setTextColors(Color4f(0.2,0.0,0.0,1.0));
        StackTraceTextArea->setEditable(false);
    endEditCP(StackTraceTextArea, TextArea::MinSizeFieldMask | TextArea::TextFieldMask | TextArea::PreferredSizeFieldMask | TextArea::FontFieldMask);
    setName(StackTraceTextArea,"Stack Trace TextArea");
    
    // Create a ScrollPanel
    ScrollPanelPtr StackTraceAreaScrollPanel = ScrollPanel::create();
    beginEditCP(StackTraceAreaScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        StackTraceAreaScrollPanel->setPreferredSize(Vec2f(200,150));
        StackTraceAreaScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(StackTraceAreaScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    // Add the TextArea to the ScrollPanel so it is displayed
	StackTraceAreaScrollPanel->setViewComponent(StackTraceTextArea);
    
    //Create the Message Text Area
    MessageTextArea = osg::TextArea::create();

    beginEditCP(MessageTextArea, TextArea::MinSizeFieldMask | TextArea::TextFieldMask | TextArea::PreferredSizeFieldMask | TextArea::FontFieldMask);
        MessageTextArea->setPreferredSize(Vec2f(600, 150));
        MessageTextArea->setText("");
        MessageTextArea->setMinSize(Vec2f(300, 150));
        MessageTextArea->setFont(CodeFont);
        MessageTextArea->setTextColors(Color4f(0.2,0.0,0.0,1.0));
        MessageTextArea->setEditable(false);
    endEditCP(MessageTextArea, TextArea::MinSizeFieldMask | TextArea::TextFieldMask | TextArea::PreferredSizeFieldMask | TextArea::FontFieldMask);
    setName(MessageTextArea,"Message TextArea");
    
    // Create a ScrollPanel
    ScrollPanelPtr MessageAreaScrollPanel = ScrollPanel::create();
    beginEditCP(MessageAreaScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        MessageAreaScrollPanel->setPreferredSize(Vec2f(200,150));
        MessageAreaScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(MessageAreaScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    // Add the TextArea to the ScrollPanel so it is displayed
	MessageAreaScrollPanel->setViewComponent(MessageTextArea);

    //Tab Panel
    LabelPtr MessageTabLabel = osg::Label::create();
    beginEditCP(MessageTabLabel, Label::TextFieldMask);
        MessageTabLabel->setText("Output");
    endEditCP(MessageTabLabel, Label::TextFieldMask);

    LabelPtr ErrorTabLabel = osg::Label::create();
    beginEditCP(ErrorTabLabel, Label::TextFieldMask);
        ErrorTabLabel->setText("Error");
    endEditCP(ErrorTabLabel, Label::TextFieldMask);

    LabelPtr StackTraceTabLabel = osg::Label::create();
    beginEditCP(StackTraceTabLabel, Label::TextFieldMask);
        StackTraceTabLabel->setText("Stack");
    endEditCP(StackTraceTabLabel, Label::TextFieldMask);

    

    InfoTabPanel = osg::TabPanel::create();
    beginEditCP(InfoTabPanel, TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);
        InfoTabPanel->addTab(MessageTabLabel, MessageAreaScrollPanel);
        InfoTabPanel->addTab(ErrorTabLabel, ErrorAreaScrollPanel);
        InfoTabPanel->addTab(StackTraceTabLabel, StackTraceAreaScrollPanel);
        InfoTabPanel->setTabAlignment(0.5f);
        InfoTabPanel->setTabPlacement(TabPanel::PLACEMENT_NORTH);
    endEditCP(InfoTabPanel, TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);
    InfoTabPanel->setSelectedIndex(0);
    setName(InfoTabPanel,"Info Tab Panel");


    //Split Panel
    BorderLayoutConstraintsPtr SplitPanelConstraints = BorderLayoutConstraints::create();
	beginEditCP(SplitPanelConstraints);
        SplitPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
	endEditCP(SplitPanelConstraints);

    SplitPanelPtr MainSplitPanel = osg::SplitPanel::create();
	beginEditCP(MainSplitPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);
        MainSplitPanel->setMinComponent(TextAreaScrollPanel);
        MainSplitPanel->setMaxComponent(InfoTabPanel);
        MainSplitPanel->setOrientation(SplitPanel::VERTICAL_ORIENTATION);
        MainSplitPanel->setDividerPosition(0.7);
        // location from the left/top
        MainSplitPanel->setDividerSize(4);
        MainSplitPanel->setMaxDividerPosition(.8);
        MainSplitPanel->setMinDividerPosition(.2);
        MainSplitPanel->setConstraints(SplitPanelConstraints);
    endEditCP(MainSplitPanel, SplitPanel::ConstraintsFieldMask | SplitPanel::MinComponentFieldMask | SplitPanel::MaxComponentFieldMask | SplitPanel::OrientationFieldMask | SplitPanel::DividerPositionFieldMask | 
		SplitPanel::DividerSizeFieldMask | SplitPanel::ExpandableFieldMask | SplitPanel::MaxDividerPositionFieldMask | SplitPanel::MinDividerPositionFieldMask);
    

    //Execute Script Button
    ButtonPtr ExecuteButton = Button::create();
    beginEditCP(ExecuteButton);
        ExecuteButton->setText("Execute");
    endEditCP(ExecuteButton);
    setName(ExecuteButton,"Execute Button");
    ExecuteScriptButtonAction TheExecuteScriptButtonAction;
    ExecuteButton->addActionListener(&TheExecuteScriptButtonAction);
    
    ButtonPtr OpenButton = Button::create();
    beginEditCP(OpenButton);
        OpenButton->setText("Open");
    endEditCP(OpenButton);
    setName(OpenButton,"Open Button");
    OpenScriptButtonAction TheOpenScriptButtonAction;
    OpenButton->addActionListener(&TheOpenScriptButtonAction);
    
    ButtonPtr SaveButton = Button::create();
    beginEditCP(SaveButton);
        SaveButton->setText("Save");
    endEditCP(SaveButton);
    setName(SaveButton,"Save Button");
    SaveScriptButtonAction TheSaveScriptButtonAction;
    SaveButton->addActionListener(&TheSaveScriptButtonAction);
    
    ButtonPtr ClearButton = Button::create();
    beginEditCP(ClearButton);
        ClearButton->setText("Clear");
    endEditCP(ClearButton);
    setName(ClearButton,"Clear Button");
    ClearScriptButtonAction TheClearScriptButtonAction;
    ClearButton->addActionListener(&TheClearScriptButtonAction);

    //Make the Button Panel
    FlowLayoutPtr ButtonPanelLayout = osg::FlowLayout::create();
	beginEditCP(ButtonPanelLayout);
        ButtonPanelLayout->setOrientation(FlowLayout::HORIZONTAL_ORIENTATION);
	endEditCP(ButtonPanelLayout);

    BorderLayoutConstraintsPtr ButtonPanelConstraints = BorderLayoutConstraints::create();
	beginEditCP(ButtonPanelConstraints);
        ButtonPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_NORTH);
	endEditCP(ButtonPanelConstraints);
    PanelPtr ButtonPanel = Panel::createEmpty();
	beginEditCP(ButtonPanel);
       ButtonPanel->setPreferredSize(Vec2f(400.0f, 50.0f));
       ButtonPanel->getChildren().push_back(ExecuteButton);
       ButtonPanel->getChildren().push_back(OpenButton);
       ButtonPanel->getChildren().push_back(SaveButton);
       ButtonPanel->getChildren().push_back(ClearButton);
       ButtonPanel->setLayout(ButtonPanelLayout);
       ButtonPanel->setConstraints(ButtonPanelConstraints);
	endEditCP(ButtonPanel);
    setName(ButtonPanel,"Button Panel");

    //Code Area Info
    LabelPtr LineLabel = Label::create();
	beginEditCP(LineLabel);
        LineLabel->setText("Line:");
        LineLabel->setPreferredSize(Vec2f(40.0f, 30.0f));
        LineLabel->setAlignment(Vec2f(1.0f, 0.5f));
	endEditCP(LineLabel);

    LineValueLabel = Label::create();
	beginEditCP(LineValueLabel);
        LineValueLabel->setText("");
        LineValueLabel->setPreferredSize(Vec2f(40.0f, 30.0f));
	endEditCP(LineValueLabel);

    LabelPtr ColumnLabel = Label::create();
	beginEditCP(ColumnLabel);
        ColumnLabel->setText("Column:");
        ColumnLabel->setPreferredSize(Vec2f(55.0f, 30.0f));
        ColumnLabel->setAlignment(Vec2f(1.0f, 0.5f));
	endEditCP(ColumnLabel);

    ColumnValueLabel = Label::create();
	beginEditCP(ColumnValueLabel );
        ColumnValueLabel->setText("");
        ColumnValueLabel->setPreferredSize(Vec2f(40.0f, 30.0f));
	endEditCP(ColumnValueLabel);
    //TextArea Info Panel
    BorderLayoutConstraintsPtr CodeAreaInfoPanelConstraints = BorderLayoutConstraints::create();
	beginEditCP(CodeAreaInfoPanelConstraints );
        CodeAreaInfoPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_SOUTH);
	endEditCP(CodeAreaInfoPanelConstraints);

    PanelPtr CodeAreaInfoPanel = Panel::create();

    SpringLayoutPtr CodeAreaInfoLayout = osg::SpringLayout::create();

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

	beginEditCP(CodeAreaInfoPanel);
       CodeAreaInfoPanel->setPreferredSize(Vec2f(400.0f, 22.0f));
       CodeAreaInfoPanel->getChildren().push_back(LineLabel);
       CodeAreaInfoPanel->getChildren().push_back(LineValueLabel);
       CodeAreaInfoPanel->getChildren().push_back(ColumnLabel);
       CodeAreaInfoPanel->getChildren().push_back(ColumnValueLabel);
       CodeAreaInfoPanel->setConstraints(CodeAreaInfoPanelConstraints);
       CodeAreaInfoPanel->setBorders(NullFC);
       CodeAreaInfoPanel->setLayout(CodeAreaInfoLayout);
	endEditCP(CodeAreaInfoPanel);

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);

    BorderLayoutPtr MainInternalWindowLayout = BorderLayout::create();

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().push_back(ButtonPanel);
       MainInternalWindow->getChildren().push_back(MainSplitPanel);
       MainInternalWindow->getChildren().push_back(CodeAreaInfoPanel);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
       MainInternalWindow->setTitle("Lua Debugger");
    endEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
    setName(MainInternalWindow,"Internal Window");

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

    //Scene Background
    GradientBackgroundPtr SceneBackground = GradientBackground::create();
    SceneBackground->addLine(Color3f(0.0,0.0,0.0),0.0);
    setName(SceneBackground,"Scene Background");

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
    mgr->setRoot(RootNode);
    //mgr->setHeadlight(false);

    // Add the UI Foreground Object to the Scene
    ViewportPtr TutorialViewport = mgr->getWindow()->getPort(0);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask | Viewport::ForegroundsFieldMask);
        TutorialViewport->getForegrounds().push_back(TutorialUIForeground);
        TutorialViewport->setBackground(SceneBackground);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask | Viewport::ForegroundsFieldMask);

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "03LuaDebugger");

	beginEditCP(MainInternalWindow);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setPreferredSize(WinSize * 0.85);
	endEditCP(MainInternalWindow);

    //Enter main Loop
    TutorialWindowEventProducer->mainLoop();

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

