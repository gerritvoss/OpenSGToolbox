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
#include <OpenSG/Input/OSGWindowAdapter.h>

// The general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

// Input
#include <OpenSG/Input/OSGWindowUtils.h>

// UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

bool ExitApp = false;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2s Size);

// 26MenuBar Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGUIFont.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
#include <OpenSG/UserInterface/OSGEmptyUIBackground.h>
#include <OpenSG/UserInterface/OSGMenu.h>
#include <OpenSG/UserInterface/OSGLabelMenuItem.h>
#include <OpenSG/UserInterface/OSGSeperatorMenuItem.h>
#include <OpenSG/UserInterface/OSGMenuBar.h>


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

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    WindowEventProducerPtr TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();
    
    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TutorialWindowEventProducer->addWindowListener(&TheTutorialWindowListener);

   // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);


    // Make Main Scene Node
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        scene->setCore(osg::Group::create());
 
        // Add the Torus as a Child
        scene->addChild(TorusGeometryNode);
    }
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    // Create the Graphics
    GraphicsPtr TutorialGraphics = osg::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

    
    /******************************************************
            
            Create  components to add to MenuBar
            Menus.  Each MenuBar has multiple Menus 
            which contain multiple MenuItems.

            -setAcceleratorKey(KeyEvent::KEY_****): This
                links the key "****" as a shortcut to 
                selecting the item it is attached to
            -setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_***):
                This adds the "***" key as another 
                requirement to cause the item to be
                selected.  Things such as "CONTROL" are 
                likely to be used here
            Note: these shortcuts will be shown in the list
                with the LabelMenuItem they are attached too
            -setMnemonicKey(KeyEvent::KEY_****): sets the key
                "****" to be underlined within the Menu
                itself


    ******************************************************/

    // Creates MenuItems as in 25PopupMenu
    LabelMenuItemPtr NewMenuItem = LabelMenuItem::create();
    LabelMenuItemPtr OpenMenuItem = LabelMenuItem::create();
    LabelMenuItemPtr CloseMenuItem = LabelMenuItem::create();
    SeperatorMenuItemPtr FileMenuSeperator1 = SeperatorMenuItem::create();
    LabelMenuItemPtr ExitMenuItem = LabelMenuItem::create();
    LabelMenuItemPtr UndoMenuItem = LabelMenuItem::create();
    LabelMenuItemPtr RedoMenuItem = LabelMenuItem::create();

    //Edits MenuItems
    beginEditCP(NewMenuItem, LabelMenuItem::TextFieldMask | LabelMenuItem::AcceleratorKeyFieldMask | LabelMenuItem::AcceleratorModifiersFieldMask | LabelMenuItem::MnemonicKeyFieldMask);
        NewMenuItem->setText("New ...");
        NewMenuItem->setAcceleratorKey(KeyEvent::KEY_N);
        NewMenuItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        NewMenuItem->setMnemonicKey(KeyEvent::KEY_N);
    endEditCP(NewMenuItem, LabelMenuItem::TextFieldMask | LabelMenuItem::AcceleratorKeyFieldMask | LabelMenuItem::AcceleratorModifiersFieldMask | LabelMenuItem::MnemonicKeyFieldMask);
    
    beginEditCP(OpenMenuItem, LabelMenuItem::TextFieldMask | LabelMenuItem::AcceleratorKeyFieldMask | LabelMenuItem::AcceleratorModifiersFieldMask | LabelMenuItem::MnemonicKeyFieldMask);
        OpenMenuItem->setText("Open ...");
        OpenMenuItem->setAcceleratorKey(KeyEvent::KEY_P);
        OpenMenuItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        OpenMenuItem->setMnemonicKey(KeyEvent::KEY_P);
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

    beginEditCP(UndoMenuItem, LabelMenuItem::TextFieldMask | LabelMenuItem::AcceleratorKeyFieldMask | LabelMenuItem::AcceleratorModifiersFieldMask | LabelMenuItem::MnemonicKeyFieldMask);
        UndoMenuItem->setText("Undo");
        UndoMenuItem->setAcceleratorKey(KeyEvent::KEY_Z);
        UndoMenuItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL);
        UndoMenuItem->setMnemonicKey(KeyEvent::KEY_U);
    endEditCP(UndoMenuItem, LabelMenuItem::TextFieldMask | LabelMenuItem::AcceleratorKeyFieldMask | LabelMenuItem::AcceleratorModifiersFieldMask | LabelMenuItem::MnemonicKeyFieldMask);
    beginEditCP(RedoMenuItem, LabelMenuItem::TextFieldMask | LabelMenuItem::MnemonicKeyFieldMask | LabelMenuItem::EnabledFieldMask);
        RedoMenuItem->setText("Redo");
        RedoMenuItem->setEnabled(false);
        RedoMenuItem->setMnemonicKey(KeyEvent::KEY_R);
    endEditCP(RedoMenuItem, LabelMenuItem::TextFieldMask | LabelMenuItem::MnemonicKeyFieldMask | LabelMenuItem::EnabledFieldMask);
    
    // Create an ActionListener and assign it to ExitMenuItem
    // This is defined above, and will cause the program to quit
    // when that MenuItem is selected or Control + Q hit 
    QuitActionListener QuitAL;
    ExitMenuItem->addActionListener( &QuitAL);
    
    /******************************************************
            
            Create Menu components to add to MenuBar
            and adds above components to them.  Note
            that the same abilities: setAcceleratorKey,
            setAcceleratorModifiers, and setMnemnoicKey
            all apply to Menus in addition to MenuItems

    ******************************************************/
    
    // Create a File menu and adds its MenuItems
    MenuPtr FileMenu = Menu::create();
    FileMenu->addItem(NewMenuItem);
    FileMenu->addItem(OpenMenuItem);
    FileMenu->addItem(CloseMenuItem);
    FileMenu->addItem(FileMenuSeperator1);
    FileMenu->addItem(ExitMenuItem);

    // Labels the File Menu
    beginEditCP(FileMenu, LabelMenuItem::TextFieldMask | LabelMenuItem::MnemonicKeyFieldMask);
        FileMenu->setText("File");
        FileMenu->setMnemonicKey(KeyEvent::KEY_F);
    endEditCP(FileMenu, LabelMenuItem::TextFieldMask | LabelMenuItem::MnemonicKeyFieldMask);
    
    // Creates a Edit menu and adds its MenuItems
    MenuPtr EditMenu = Menu::create();
    EditMenu->addItem(UndoMenuItem);
    EditMenu->addItem(RedoMenuItem);

    // Labels the Edit Menu
    beginEditCP(EditMenu, LabelMenuItem::TextFieldMask | LabelMenuItem::MnemonicKeyFieldMask);
        EditMenu->setText("Edit");
        EditMenu->setMnemonicKey(KeyEvent::KEY_E);
    endEditCP(EditMenu, LabelMenuItem::TextFieldMask | LabelMenuItem::MnemonicKeyFieldMask);
    
    /******************************************************
            
            Create MainMenuBar and adds the Menus
            created above to it.

            Also creates several Backgrounds
            to improve MenuBar overall look.
            Both the MenuBar and Menu can have
            Backgrounds; the set up currently
            is to have EmptyBackgrounds in 
            each Menu allowing a single
            overall MenuBar Background which
            is given to the MenuBar itself.

            This can be easily changed by adding
            different Backgrounds to the 
            File and Edit Menus.

            Note: it is added to the MainFrame
            below.

    ******************************************************/
    // Creates two Backgrounds
    EmptyUIBackgroundPtr emptyBackground = osg::EmptyUIBackground::create();
    ColorUIBackgroundPtr colorBackground = osg::ColorUIBackground::create();


    MenuBarPtr MainMenuBar = MenuBar::create();
    // Adds the two Menus to the MainMenuBar
    MainMenuBar->addMenu(FileMenu);
    MainMenuBar->addMenu(EditMenu);

    // Adds Backgrounds to Menus and MenuBar
    beginEditCP(FileMenu, Container::BackgroundFieldMask);
        FileMenu->setBackground(emptyBackground);
    beginEditCP(FileMenu, Container::BackgroundFieldMask);

    beginEditCP(EditMenu, Container::BackgroundFieldMask);
        EditMenu->setBackground(emptyBackground);
    beginEditCP(EditMenu, Container::BackgroundFieldMask);

    beginEditCP(MainMenuBar, Container::BackgroundFieldMask);
        MainMenuBar->setBackground(colorBackground);
    beginEditCP(MainMenuBar, Container::BackgroundFieldMask);
    
    // Create MainFrameBackground
    ColorUIBackgroundPtr MainFrameBackground = osg::ColorUIBackground::create();
    beginEditCP(MainFrameBackground, ColorUIBackground::ColorFieldMask);
        MainFrameBackground->setColor(Color4f(0.0, 0.0, 0.0, 0.0));
    endEditCP(MainFrameBackground, ColorUIBackground::ColorFieldMask);
    // Create The Main Frame
    FramePtr MainFrame = osg::Frame::create();
    LayoutPtr MainFrameLayout = osg::FlowLayout::create();

    // Create two labels to add to MainFrame
    LabelPtr label1 = osg::Label::create();
    LabelPtr label2 = osg::Label::create();
    beginEditCP(label1, Label::TextFieldMask | Component::PreferredSizeFieldMask);
        label1->setText("Look up in the corner!");
        label1->setPreferredSize(Vec2s(150, 25));    
    endEditCP(label1, Label::TextFieldMask | Component::PreferredSizeFieldMask);
    beginEditCP(label2, Label::TextFieldMask | Component::PreferredSizeFieldMask);
        label2->setText("Hit Control + O");
        label2->setPreferredSize(Vec2s(150, 25));    
    endEditCP(label2, Label::TextFieldMask | Component::PreferredSizeFieldMask);

    beginEditCP(MainFrame, Frame::LayoutFieldMask | Component::BackgroundFieldMask | Frame::MenuBarFieldMask | Container::ChildrenFieldMask);
       MainFrame->setLayout(MainFrameLayout);
       // Adds MainMenuBar to MainFrame
       MainFrame->setMenuBar(MainMenuBar);
       MainFrame->setBackground(MainFrameBackground);
       MainFrame->getChildren().addValue(label1);
       MainFrame->getChildren().addValue(label2);
    endEditCP(MainFrame, Frame::LayoutFieldMask | Component::BackgroundFieldMask | Frame::MenuBarFieldMask | Container::ChildrenFieldMask);

    // Create the Drawing Surface
    UIDrawingSurfacePtr TutorialDrawingSurface = UIDrawingSurface::create();
    beginEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask);
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setRootFrame(MainFrame);
        TutorialDrawingSurface->setEventProducer(TutorialWindowEventProducer);
    endEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask);
    // Create the UI Foreground Object
    UIForegroundPtr TutorialUIForeground = osg::UIForeground::create();

    beginEditCP(TutorialUIForeground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);
        TutorialUIForeground->setFramePositionOffset(Vec2s(0,0));
        TutorialUIForeground->setFrameBounds(Vec2f(1.0,1.0));
    endEditCP(TutorialUIForeground, UIForeground::DrawingSurfaceFieldMask |UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);


    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
    mgr->setRoot(scene);

    // Add the UI Foreground Object to the Scene
    ViewportPtr TutorialViewport = mgr->getWindow()->getPort(0);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);
        TutorialViewport->getForegrounds().addValue(TutorialUIForeground);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);

    // Show the whole Scene
    mgr->showAll();

    TutorialWindowEventProducer->openWindow(Pnt2s(50,50),
                                        Vec2s(550,550),
                                        "OpenSG 26MenuBar Window");

    while(!ExitApp)
    {
        TutorialWindowEventProducer->update();
        TutorialWindowEventProducer->draw();
    }
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
void reshape(Vec2s Size)
{
    mgr->resize(Size.x(), Size.y());
}