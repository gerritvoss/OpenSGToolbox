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
#include <OpenSG/OSGSimpleAttachments.h>

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

//Lua Manager
#include <OpenSG/Lua/OSGLuaManager.h>

#include <boost/filesystem.hpp>
#include <sstream>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;
TextAreaPtr CodeTextArea;
TextAreaPtr ErrorTextArea;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);



void clearError(void)
{
    beginEditCP(ErrorTextArea, TextArea::TextFieldMask);
        ErrorTextArea->setText("");
    endEditCP(ErrorTextArea, TextArea::TextFieldMask);
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
			Path("."),
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
        Filters.push_back(WindowEventProducer::FileDialogFilter("All","*"));

		std::vector<Path> FilesToOpen;
		FilesToOpen = TutorialWindowEventProducer->openFileDialog("Open Lua Script File.",
			Filters,
			Path("."),
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
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Main Scene Node and add the Torus
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
        scene->addChild(TorusGeometryNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    // Create the Graphics
    GraphicsPtr TutorialGraphics = osg::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();


    //Create the default font
    UIFontPtr CodeFont = osg::UIFont::create();
    beginEditCP(CodeFont, UIFont::SizeFieldMask | UIFont::FamilyFieldMask | UIFont::AntiAliasingFieldMask);
        CodeFont->setFamily("Courier New");
        CodeFont->setSize(18);
        CodeFont->setAntiAliasing(true);
    endEditCP(CodeFont, UIFont::SizeFieldMask | UIFont::FamilyFieldMask | UIFont::AntiAliasingFieldMask);

    // Create a TextArea component
    CodeTextArea = osg::TextArea::create();

    beginEditCP(CodeTextArea, TextArea::MinSizeFieldMask | TextArea::TextFieldMask | TextArea::PreferredSizeFieldMask | TextArea::FontFieldMask);
        CodeTextArea->setPreferredSize(Vec2f(600, 600));
        CodeTextArea->setText("print(\"Hello World\")");
        CodeTextArea->setMinSize(Vec2f(300, 600));
        CodeTextArea->setFont(CodeFont);
    endEditCP(CodeTextArea, TextArea::MinSizeFieldMask | TextArea::TextFieldMask | TextArea::PreferredSizeFieldMask | TextArea::FontFieldMask);
        
    // Create a ScrollPanel
    BorderLayoutConstraintsPtr CodeTextConstraints = BorderLayoutConstraints::create();
	beginEditCP(CodeTextConstraints);
        CodeTextConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
	endEditCP(CodeTextConstraints);

    ScrollPanelPtr TextAreaScrollPanel = ScrollPanel::create();
    beginEditCP(TextAreaScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        TextAreaScrollPanel->setPreferredSize(Vec2f(200,600));
        TextAreaScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        TextAreaScrollPanel->setConstraints(CodeTextConstraints);
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
    endEditCP(ErrorTextArea, TextArea::MinSizeFieldMask | TextArea::TextFieldMask | TextArea::PreferredSizeFieldMask | TextArea::FontFieldMask);
        
    // Create a ScrollPanel
    BorderLayoutConstraintsPtr ErrorAreaConstraints = BorderLayoutConstraints::create();
	beginEditCP(ErrorAreaConstraints);
        ErrorAreaConstraints->setRegion(BorderLayoutConstraints::BORDER_SOUTH);
	endEditCP(ErrorAreaConstraints);
    LuaErrorListener  TheLuaErrorListener;
    LuaManager::the()->addLuaListener(&TheLuaErrorListener);

    ScrollPanelPtr ErrorAreaScrollPanel = ScrollPanel::create();
    beginEditCP(ErrorAreaScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        ErrorAreaScrollPanel->setPreferredSize(Vec2f(200,150));
        ErrorAreaScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        ErrorAreaScrollPanel->setConstraints(ErrorAreaConstraints);
    endEditCP(ErrorAreaScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    // Add the TextArea to the ScrollPanel so it is displayed
	ErrorAreaScrollPanel->setViewComponent(ErrorTextArea);

    


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
       MainInternalWindow->getChildren().push_back(TextAreaScrollPanel);
       MainInternalWindow->getChildren().push_back(ErrorAreaScrollPanel);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.85f,0.85f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
    endEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);

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


    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
    mgr->setRoot(scene);

    // Add the UI Foreground Object to the Scene
    ViewportPtr TutorialViewport = mgr->getWindow()->getPort(0);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);
        TutorialViewport->getForegrounds().push_back(TutorialUIForeground);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "02LuaConsole");

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

