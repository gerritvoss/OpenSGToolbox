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
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
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
TextAreaPtr ExampleTextArea;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);



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
           LuaManager::the()->runScript(ExampleTextArea->getText());
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
       LuaManager::the()->runScript(ExampleTextArea->getText());
   }
};


class ClearScriptButtonAction : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
   {
       ExampleTextArea->selectAll();
       ExampleTextArea->deleteSelectedText();
   }
};


class SaveScriptButtonAction : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
   {
		std::vector<WindowEventProducer::FileDialogFilter> Filters;
        Filters.push_back(WindowEventProducer::FileDialogFilter("Some File Type","lua"));
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
            OutFile << ExampleTextArea->getText();
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
                beginEditCP(ExampleTextArea, TextArea::TextFieldMask);
                    ExampleTextArea->setText(InStrStream.str());
                endEditCP(ExampleTextArea, TextArea::TextFieldMask);
            }
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
    ExampleTextArea = osg::TextArea::create();

    beginEditCP(ExampleTextArea, TextArea::MinSizeFieldMask | TextArea::TextFieldMask | TextArea::PreferredSizeFieldMask | TextArea::FontFieldMask);
        ExampleTextArea->setPreferredSize(Vec2f(800, 600));
        ExampleTextArea->setText("print(\"Hello World\")");
        ExampleTextArea->setMinSize(Vec2f(300, 200));
        ExampleTextArea->setFont(CodeFont);
    endEditCP(ExampleTextArea, TextArea::MinSizeFieldMask | TextArea::TextFieldMask | TextArea::PreferredSizeFieldMask | TextArea::FontFieldMask);
        
    // Create a ScrollPanel
    ScrollPanelPtr TextAreaScrollPanel = ScrollPanel::create();
    beginEditCP(TextAreaScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        TextAreaScrollPanel->setPreferredSize(Vec2f(200,200));
        TextAreaScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(TextAreaScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    // Add the TextArea to the ScrollPanel so it is displayed
	TextAreaScrollPanel->setViewComponent(ExampleTextArea);

    
    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);

    //Execute Script Button
    ButtonPtr ExecuteButton = Button::create();
    beginEditCP(ExecuteButton);
        ExecuteButton->setText("Execute");
    endEditCP(ExecuteButton);
    ExecuteScriptButtonAction TheExecuteScriptButtonAction;
    ExecuteButton->addActionListener(&TheExecuteScriptButtonAction);
    
    ButtonPtr OpenButton = Button::create();
    beginEditCP(OpenButton);
        OpenButton->setText("Open");
    endEditCP(OpenButton);
    OpenScriptButtonAction TheOpenScriptButtonAction;
    OpenButton->addActionListener(&TheOpenScriptButtonAction);
    
    ButtonPtr SaveButton = Button::create();
    beginEditCP(SaveButton);
        SaveButton->setText("Save");
    endEditCP(SaveButton);
    SaveScriptButtonAction TheSaveScriptButtonAction;
    SaveButton->addActionListener(&TheSaveScriptButtonAction);
    
    ButtonPtr ClearButton = Button::create();
    beginEditCP(ClearButton);
        ClearButton->setText("Clear");
    endEditCP(ClearButton);
    ClearScriptButtonAction TheClearScriptButtonAction;
    ClearButton->addActionListener(&TheClearScriptButtonAction);

    LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().push_back(TextAreaScrollPanel);
       MainInternalWindow->getChildren().push_back(ExecuteButton);
       MainInternalWindow->getChildren().push_back(OpenButton);
       MainInternalWindow->getChildren().push_back(SaveButton);
       MainInternalWindow->getChildren().push_back(ClearButton);
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

