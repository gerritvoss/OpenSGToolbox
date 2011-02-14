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

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

// 25PopupMenu Headers
#include "OSGButton.h"
#include "OSGToggleButton.h"
#include "OSGFlowLayout.h"
#include "OSGUIFont.h"
#include "OSGColorLayer.h"
#include "OSGPopupMenu.h"
#include "OSGMenu.h"
#include "OSGMenuItem.h"
#include "OSGColorLayer.h"

void keyPressed(KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
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

        TutorialWindow->connectKeyTyped(boost::bind(keyPressed, _1));

        // Make Torus Node (creates Torus in background of scene)
        NodeRecPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

        // Make Main Scene Node and add the Torus
        NodeRecPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(TorusGeometryNode);

        // Create the Graphics
        GraphicsRecPtr TutorialGraphics = Graphics2D::create();

        // Initialize the LookAndFeelManager to enable default settings
        LookAndFeelManager::the()->getLookAndFeel()->init();

        /******************************************************

          Create PopupMenu Components

          -MenuItem: These are items that are contained
          within a Menu; they are the things you click
          on to cause something to occur
          -SeperatorMenuItem:  These place a seperator 
          line between items in a Menu
          -Menu: These are sub-menus within another Menu;
          MenuItems and SeperatorMenuItems
          are added to a Menu

         ******************************************************/

        MenuItemRecPtr MenuItem1 = MenuItem::create();
        MenuItemRecPtr MenuItem2 = MenuItem::create();
        MenuItemRecPtr MenuItem3 = MenuItem::create();
        MenuItemRecPtr MenuItem4 = MenuItem::create();
        MenuItemRecPtr SubMenuItem1 = MenuItem::create();
        MenuItemRecPtr SubMenuItem2 = MenuItem::create();
        MenuItemRecPtr SubMenuItem3 = MenuItem::create();
        MenuRecPtr ExampleSubMenu = Menu::create();

        /******************************************************

          Edit the MenuItems

          -setText("TEXT"): Sets the text on the 
          item to be TEXT
          -setEnabled(Boolean): sets the menu item
          to be either enabled or disabled

         ******************************************************/

        MenuItem1->setText("Menu Item 1");

        MenuItem2->setText("Menu Item 2");

        MenuItem3->setText("Menu Item 3");

        MenuItem4->setText("Menu Item 4");
        MenuItem4->setEnabled(false);

        SubMenuItem1->setText("SubMenu Item 1");

        SubMenuItem2->setText("SubMenu Item 2");

        SubMenuItem3->setText("SubMenu Item 3");

        ExampleSubMenu->setText("Sub Menu");

        // This adds three MenuItems to the Menu,
        // creating a submenu.  Note this does not
        // involve begin/endEditCPs to do

        ExampleSubMenu->addItem(SubMenuItem1);
        ExampleSubMenu->addItem(SubMenuItem2);
        ExampleSubMenu->addItem(SubMenuItem3);

        /******************************************************

          Create the PopupMenu itself.

          Items are added in the order in which
          they will be displayed (top to bottom)
          via addItem(ItemToBeAdded)

          The PopupMenu is attached to a 
          Button below using 
          setPopupMenu(PopupMenuName).  

            Note: PopupMenus can be added to any
            Component.

         ******************************************************/
        PopupMenuRecPtr ExamplePopupMenu = PopupMenu::create();
        ExamplePopupMenu->setMinSize(Vec2f(100.0f, 20.0f));
        ExamplePopupMenu->setMaxSize(Vec2f(100.0f, 50.0f));
        ExamplePopupMenu->addItem(MenuItem1);
        ExamplePopupMenu->addItem(MenuItem2);
        ExamplePopupMenu->addItem(MenuItem3);
        ExamplePopupMenu->addSeparator();
        ExamplePopupMenu->addItem(ExampleSubMenu);
        ExamplePopupMenu->addItem(MenuItem4);

        // Create a Button and Font
        UIFontRecPtr PopupMenuButtonFont = UIFont::create();
        PopupMenuButtonFont->setSize(16);

        ButtonRecPtr PopupMenuButton = Button::create();
        PopupMenuButton->setText("RightClickMe!");
        // Add the PopupMenu to PopupMenuButton so that when right clicked,
        // the PopupMenu will appear
        PopupMenuButton->setPopupMenu(ExamplePopupMenu);
        PopupMenuButton->setPreferredSize(Vec2f(200,100));
        PopupMenuButton->setFont(PopupMenuButtonFont);


        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        LayoutRecPtr MainInternalWindowLayout = FlowLayout::create();

        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
        MainInternalWindow->pushToChildren(PopupMenuButton);
        MainInternalWindow->setLayout(MainInternalWindowLayout);
        MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
        MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setDrawTitlebar(false);
        MainInternalWindow->setResizable(false);

        // Create the Drawing Surface
        UIDrawingSurfaceRecPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);

        TutorialDrawingSurface->openWindow(MainInternalWindow);

        // Create the UI Foreground Object
        UIForegroundRecPtr TutorialUIForeground = UIForeground::create();

        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);


        // Tell the Manager what to manage
        sceneManager.setRoot(scene);

        // Add the UI Foreground Object to the Scene
        ViewportRecPtr TutorialViewport = sceneManager.getWindow()->getPort(0);
        TutorialViewport->addForeground(TutorialUIForeground);

        // Show the whole Scene
        sceneManager.showAll();

        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "01RubberBandCamera");

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
