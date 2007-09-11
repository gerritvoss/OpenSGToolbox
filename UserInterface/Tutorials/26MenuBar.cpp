// OpenSG Tutorial Example: Creating a Button Component
//
// This tutorial explains how to edit the basic features of
// a Button and a ToggleButtoncreated in the OSG User 
// Interface library.
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

// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

//Input
#include <OpenSG/Input/OSGWindowUtils.h>

#include <OpenSG/Input/OSGWindowAdapter.h>

//UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGUIFont.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
#include <OpenSG/UserInterface/OSGMenu.h>
#include <OpenSG/UserInterface/OSGLabelMenuItem.h>
#include <OpenSG/UserInterface/OSGSeperatorMenuItem.h>
#include <OpenSG/UserInterface/OSGMenuBar.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

bool ExitApp = false;

// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2s Size);

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

// Create an ActionListener to Quit the application
class QuitActionListener : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
	{
        ExitApp = true;
	}
};

// Initialize WIN32 & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    WindowEventProducerPtr TheWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TheWindowEventProducer->initWindow();
    
    TheWindowEventProducer->setDisplayCallback(display);
    TheWindowEventProducer->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TheWindowEventProducer->addWindowListener(&TheTutorialWindowListener);

   // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);


    // Make Main Scene Node
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        scene->setCore(osg::Group::create());
 
        // add the torus as a child
        scene->addChild(TorusGeometryNode);
    }
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

	// Create the Graphics
	GraphicsPtr graphics = osg::Graphics2D::create();

	// Initialize the LookAndFeelManager to enable default settings
	LookAndFeelManager::the()->getLookAndFeel()->init();

    //Create a MenuBar
    LabelMenuItemPtr NewMenuItem = LabelMenuItem::create();
    LabelMenuItemPtr OpenMenuItem = LabelMenuItem::create();
    LabelMenuItemPtr CloseMenuItem = LabelMenuItem::create();
    SeperatorMenuItemPtr FileMenuSeperator1 = SeperatorMenuItem::create();
    LabelMenuItemPtr ExitMenuItem = LabelMenuItem::create();

    beginEditCP(NewMenuItem, LabelMenuItem::TextFieldMask | LabelMenuItem::AcceleratorKeyFieldMask | LabelMenuItem::AcceleratorModifiersFieldMask | LabelMenuItem::MnemonicKeyFieldMask);
        NewMenuItem->setText("New ...");
        NewMenuItem->setAcceleratorKey(KeyEvent::KEY_N);
        NewMenuItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        NewMenuItem->setMnemonicKey(KeyEvent::KEY_N);
    endEditCP(NewMenuItem, LabelMenuItem::TextFieldMask | LabelMenuItem::AcceleratorKeyFieldMask | LabelMenuItem::AcceleratorModifiersFieldMask | LabelMenuItem::MnemonicKeyFieldMask);
    
    beginEditCP(OpenMenuItem, LabelMenuItem::TextFieldMask | LabelMenuItem::AcceleratorKeyFieldMask | LabelMenuItem::AcceleratorModifiersFieldMask | LabelMenuItem::MnemonicKeyFieldMask);
        OpenMenuItem->setText("Open ...");
        OpenMenuItem->setAcceleratorKey(KeyEvent::KEY_O);
        OpenMenuItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        OpenMenuItem->setMnemonicKey(KeyEvent::KEY_O);
    endEditCP(OpenMenuItem, LabelMenuItem::TextFieldMask | LabelMenuItem::AcceleratorKeyFieldMask | LabelMenuItem::AcceleratorModifiersFieldMask | LabelMenuItem::MnemonicKeyFieldMask);
    
    beginEditCP(CloseMenuItem, LabelMenuItem::TextFieldMask | LabelMenuItem::AcceleratorKeyFieldMask | LabelMenuItem::AcceleratorModifiersFieldMask | LabelMenuItem::MnemonicKeyFieldMask);
        CloseMenuItem->setText("Close ...");
        CloseMenuItem->setAcceleratorKey(KeyEvent::KEY_W);
        CloseMenuItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        CloseMenuItem->setMnemonicKey(KeyEvent::KEY_C);
    endEditCP(CloseMenuItem, LabelMenuItem::TextFieldMask | LabelMenuItem::AcceleratorKeyFieldMask | LabelMenuItem::AcceleratorModifiersFieldMask | LabelMenuItem::MnemonicKeyFieldMask);
    
    beginEditCP(ExitMenuItem, LabelMenuItem::TextFieldMask | LabelMenuItem::AcceleratorKeyFieldMask | LabelMenuItem::AcceleratorModifiersFieldMask | LabelMenuItem::MnemonicKeyFieldMask);
        ExitMenuItem->setText("Quit");
        ExitMenuItem->setAcceleratorKey(KeyEvent::KEY_Q);
        ExitMenuItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        ExitMenuItem->setMnemonicKey(KeyEvent::KEY_Q);
    endEditCP(ExitMenuItem, LabelMenuItem::TextFieldMask | LabelMenuItem::AcceleratorKeyFieldMask | LabelMenuItem::AcceleratorModifiersFieldMask | LabelMenuItem::MnemonicKeyFieldMask);

	// Create an ActionListener and assign it to ExitMenuItem
	// This is defined above, and wil
	QuitActionListener QuitAL;
	ExitMenuItem->addActionListener( &QuitAL);
    
    MenuPtr FileMenu = Menu::create();
    FileMenu->addItem(NewMenuItem);
    FileMenu->addItem(OpenMenuItem);
    FileMenu->addItem(CloseMenuItem);
    FileMenu->addItem(FileMenuSeperator1);
    FileMenu->addItem(ExitMenuItem);
    beginEditCP(FileMenu, LabelMenuItem::TextFieldMask | LabelMenuItem::MnemonicKeyFieldMask);
        FileMenu->setText("File");
        FileMenu->setMnemonicKey(KeyEvent::KEY_F);
    endEditCP(FileMenu, LabelMenuItem::TextFieldMask | LabelMenuItem::MnemonicKeyFieldMask);
    
    LabelMenuItemPtr UndoMenuItem = LabelMenuItem::create();
    beginEditCP(UndoMenuItem, LabelMenuItem::TextFieldMask | LabelMenuItem::AcceleratorKeyFieldMask | LabelMenuItem::AcceleratorModifiersFieldMask | LabelMenuItem::MnemonicKeyFieldMask);
        UndoMenuItem->setText("Undo");
        UndoMenuItem->setAcceleratorKey(KeyEvent::KEY_Z);
        UndoMenuItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        UndoMenuItem->setMnemonicKey(KeyEvent::KEY_U);
    endEditCP(UndoMenuItem, LabelMenuItem::TextFieldMask | LabelMenuItem::AcceleratorKeyFieldMask | LabelMenuItem::AcceleratorModifiersFieldMask | LabelMenuItem::MnemonicKeyFieldMask);
    
    MenuPtr EditMenu = Menu::create();

    EditMenu->addItem(UndoMenuItem);
    beginEditCP(EditMenu, LabelMenuItem::TextFieldMask | LabelMenuItem::MnemonicKeyFieldMask);
        EditMenu->setText("Edit");
        EditMenu->setMnemonicKey(KeyEvent::KEY_E);
    endEditCP(EditMenu, LabelMenuItem::TextFieldMask | LabelMenuItem::MnemonicKeyFieldMask);

    MenuBarPtr MainMenuBar = MenuBar::create();

    MainMenuBar->addMenu(FileMenu);
    MainMenuBar->addMenu(EditMenu);

    
	// Create a Button component
	ButtonPtr button1 = osg::Button::create();
	// Create a simple Font to be used with the Button
	UIFontPtr sampleFont = osg::UIFont::create();
    beginEditCP(sampleFont, UIFont::SizeFieldMask);
		sampleFont->setSize(16);
	endEditCP(sampleFont, UIFont::SizeFieldMask);

    beginEditCP(button1, Button::TextFieldMask | Button::ConstraintsFieldMask);
		button1->setText("Button 1");
    endEditCP(button1, Button::TextFieldMask | Button::ConstraintsFieldMask);


	// Create Background to be used with the MainFrame
	ColorUIBackgroundPtr mainBackground = osg::ColorUIBackground::create();
	beginEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
		mainBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
	endEditCP(mainBackground, ColorUIBackground::ColorFieldMask);

	// Create The Main Frame
	FramePtr MainFrame = osg::Frame::create();
	LayoutPtr MainFrameLayout = osg::FlowLayout::create();
	beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Component::BackgroundFieldMask | Frame::MenuBarFieldMask);
	   // Assign the Button to the MainFrame so it will be displayed
	   // when the view is rendered.
	   MainFrame->getChildren().addValue(button1);
	   MainFrame->setLayout(MainFrameLayout);
	   MainFrame->setBackground(mainBackground);
       MainFrame->setMenuBar(MainMenuBar);
	endEditCP  (MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Component::BackgroundFieldMask | Frame::MenuBarFieldMask);

	//Create the Drawing Surface
	UIDrawingSurfacePtr drawingSurface = UIDrawingSurface::create();
	beginEditCP(drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask);
		drawingSurface->setGraphics(graphics);
		drawingSurface->setRootFrame(MainFrame);
	    drawingSurface->setEventProducer(TheWindowEventProducer);
    endEditCP  (drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask);
	// Create the UI Foreground Object
	UIForegroundPtr foreground = osg::UIForeground::create();

	beginEditCP(foreground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
	    foreground->setDrawingSurface(drawingSurface);
		foreground->setFramePositionOffset(Vec2s(0,0));
		foreground->setFrameBounds(Vec2f(1.0,1.0));
	   //Set the Event Producer for the DrawingSurface
	   //This is needed in order to get Mouse/Keyboard/etc Input to the UI DrawingSurface
    endEditCP  (foreground, UIForeground::DrawingSurfaceFieldMask |UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);


    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(MainWindow );
    mgr->setRoot  (scene);

	// Add the UI Foreground Object to the Scene
	ViewportPtr viewport = mgr->getWindow()->getPort(0);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);
		viewport->getForegrounds().addValue(foreground);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);
    // show the whole scene
    mgr->showAll();

    TheWindowEventProducer->openWindow(Pnt2s(50,50),
                                        Vec2s(550,550),
                                        "OpenSG 25PopupMenu Window");

    while(!ExitApp)
    {
        TheWindowEventProducer->update();
        TheWindowEventProducer->draw();
    }
    osgExit();

    return 0;
}

//
// callback functions
//

// redraw the window
void display(void)
{
    mgr->redraw();
}

// react to size changes
void reshape(Vec2s Size)
{
    mgr->resize(Size.x(), Size.y());
}
