// OpenSG Tutorial Example: Creating a Button Component
//
// This tutorial explains how to edit the basic features of
// a Button and a ToggleButtoncreated in the OSG User 
// Interface library.
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

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// 26MenuBar Headers
#include "OSGUIForeground.h"
#include "OSGUIDrawingSurface.h"
#include "OSGGraphics2D.h"
#include "OSGButton.h"
#include "OSGLabel.h"
#include "OSGFlowLayout.h"
#include "OSGLookAndFeelManager.h"
#include "OSGUIFont.h"
#include "OSGLayers.h"
#include "OSGBorders.h"
#include "OSGMenu.h"
#include "OSGMenuItem.h"
#include "OSGMenuBar.h"


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
    }

    virtual void keyReleased(const KeyEventUnrecPtr e)
    {
    }

    virtual void keyTyped(const KeyEventUnrecPtr e)
    {
    }
};

// Create an ActionListener to Quit the application
class QuitActionListener : public ActionListener
{
  public:

    virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
        TutorialWindow->closeWindow();
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

    // Make Main Scene Node and add the Torus
    NodeRefPtr scene = OSG::Node::create();
    scene->setCore(OSG::Group::create());
    scene->addChild(TorusGeometryNode);

    // Create the Graphics
    GraphicsRefPtr TutorialGraphics = OSG::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

    /******************************************************

      Create Components to add to MenuBar
      Menus.  Each MenuBar has multiple Menus 
      which contain multiple MenuItems.

      -setAcceleratorKey(KeyEvent::KEY_*): This
      links the key "*" as a shortcut to 
      selecting the item it is attached to.
      An example of this would be Q with 
      Control+Q causing programs to quit.
      -setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_*):
      This adds the "*" key as another 
      requirement to cause the item to be
      selected.  Things such as "CONTROL" are 
      likely to be used here (as mentioned 
      above, both Control and Q are specified).

Note: These shortcuts will be shown in the list
with the MenuItem they are attached to.

-setMnemonicKey(KeyEvent::KEY_****): sets the key
"****" to be underlined within the Menu
itself


     ******************************************************/

    // Creates MenuItems as in 25PopupMenu
    MenuItemRefPtr NewMenuItem = MenuItem::create();
    MenuItemRefPtr OpenMenuItem = MenuItem::create();
    MenuItemRefPtr CloseMenuItem = MenuItem::create();
    MenuItemRefPtr ExitMenuItem = MenuItem::create();
    MenuItemRefPtr UndoMenuItem = MenuItem::create();
    MenuItemRefPtr RedoMenuItem = MenuItem::create();

    //Edits MenuItems
    NewMenuItem->setText("New ...");
    NewMenuItem->setAcceleratorKey(KeyEvent::KEY_N);
    NewMenuItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_COMMAND);
    NewMenuItem->setMnemonicKey(KeyEvent::KEY_N);

    OpenMenuItem->setText("Open ...");
    OpenMenuItem->setAcceleratorKey(KeyEvent::KEY_P);
    OpenMenuItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_COMMAND);
    OpenMenuItem->setMnemonicKey(KeyEvent::KEY_P);

    CloseMenuItem->setText("Close ...");
    CloseMenuItem->setAcceleratorKey(KeyEvent::KEY_W);
    CloseMenuItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_COMMAND);
    CloseMenuItem->setMnemonicKey(KeyEvent::KEY_C);

    ExitMenuItem->setText("Quit");
    ExitMenuItem->setAcceleratorKey(KeyEvent::KEY_Q);
    ExitMenuItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_COMMAND);
    ExitMenuItem->setMnemonicKey(KeyEvent::KEY_Q);

    UndoMenuItem->setText("Undo");
    UndoMenuItem->setAcceleratorKey(KeyEvent::KEY_Z);
    UndoMenuItem->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_COMMAND);
    UndoMenuItem->setMnemonicKey(KeyEvent::KEY_U);
    RedoMenuItem->setText("Redo");
    RedoMenuItem->setEnabled(false);
    RedoMenuItem->setMnemonicKey(KeyEvent::KEY_R);

    // Create an ActionListener and assign it to ExitMenuItem
    // This is defined above, and will cause the program to quit
    // when that MenuItem is selected or Control + Q hit 
    QuitActionListener TheQuitActionListener;
    ExitMenuItem->addActionListener( &TheQuitActionListener);

    /******************************************************

      Create Menu Components to add to MenuBar
      and adds above Components to them.  

Note: setAcceleratorKey,
setAcceleratorModifiers, and setMnemnoicKey
all apply to Menus in addition to MenuItems.

     ******************************************************/

    // Create a File menu and adds its MenuItems
    MenuRefPtr FileMenu = Menu::create();
    FileMenu->addItem(NewMenuItem);
    FileMenu->addItem(OpenMenuItem);
    FileMenu->addItem(CloseMenuItem);
    FileMenu->addSeparator();
    FileMenu->addItem(ExitMenuItem);

    // Labels the File Menu
    FileMenu->setText("File");
    FileMenu->setMnemonicKey(KeyEvent::KEY_F);

    // Creates an Edit menu and adds its MenuItems
    MenuRefPtr EditMenu = Menu::create();
    EditMenu->addItem(UndoMenuItem);
    EditMenu->addItem(RedoMenuItem);

    // Labels the Edit Menu
    EditMenu->setText("Edit");
    EditMenu->setMnemonicKey(KeyEvent::KEY_E);

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

Note: The MenuBar is added to the
MainFrame below.

     ******************************************************/
    // Creates two Backgrounds

    MenuBarRefPtr MainMenuBar = MenuBar::create();
    // Adds the two Menus to the MainMenuBar
    MainMenuBar->addMenu(FileMenu);
    MainMenuBar->addMenu(EditMenu);

    // Create two Labels
    LabelRefPtr ExampleLabel1 = OSG::Label::create();
    LabelRefPtr ExampleLabel2 = OSG::Label::create();

    ExampleLabel1->setText("Look up in the corner!");
    ExampleLabel1->setPreferredSize(Vec2f(150, 25));    

    ExampleLabel2->setText("Hit Control + Z");
    ExampleLabel2->setPreferredSize(Vec2f(150, 25));    

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    EmptyLayerRefPtr MainInternalWindowBackground = OSG::EmptyLayer::create();
    EmptyBorderRefPtr MainInternalWindowBorder = OSG::EmptyBorder::create();

    LayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
    MainInternalWindow->pushToChildren(ExampleLabel1);
    MainInternalWindow->pushToChildren(ExampleLabel2);
    MainInternalWindow->setLayout(MainInternalWindowLayout);
    MainInternalWindow->setMenuBar(MainMenuBar);
    MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
    MainInternalWindow->setBorders(MainInternalWindowBorder);
    MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
    MainInternalWindow->setScalingInDrawingSurface(Vec2f(1.0f,1.0f));
    MainInternalWindow->setDrawTitlebar(false);
    MainInternalWindow->setResizable(false);

    // Create the Drawing Surface
    UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
    TutorialDrawingSurface->setGraphics(TutorialGraphics);
    TutorialDrawingSurface->setEventProducer(TutorialWindow);

    TutorialDrawingSurface->openWindow(MainInternalWindow);

    // Create the UI Foreground Object
    UIForegroundRefPtr TutorialUIForeground = OSG::UIForeground::create();

    TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);


    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindow);
    mgr->setRoot(scene);

    // Add the UI Foreground Object to the Scene
    ViewportRefPtr TutorialViewport = mgr->getWindow()->getPort(0);
    TutorialViewport->addForeground(TutorialUIForeground);

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
                               WinSize,
                               "26MenuBar");

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

