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
#include <OpenSG/UserInterface/OSGInternalWindow.h>
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
void reshape(Vec2f Size);


// 25PopupMenu Headers
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGToggleButton.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGUIFont.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
#include <OpenSG/UserInterface/OSGPopupMenu.h>
#include <OpenSG/UserInterface/OSGMenu.h>
#include <OpenSG/UserInterface/OSGLabelMenuItem.h>
#include <OpenSG/UserInterface/OSGSeperatorMenuItem.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>



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

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEvent& e)
   {
       if(e.getKey() == KeyEvent::KEY_Q && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           ExitApp = true;
       }
   }

   virtual void keyReleased(const KeyEvent& e)
   {
   }

   virtual void keyTyped(const KeyEvent& e)
   {
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

    /******************************************************
            
                Create PopupMenu Components
        
        -LabelMenuItem: These are items that are contained
            within a Menu; they are the things you click
            on to cause something to occur
        -SeperatorMenuItem:  These place a seperator 
            line between items in a Menu
        -Menu: These are sub-menus within another Menu;
            LabelMenuItems and SeperatorMenuItems
            are added to a Menu

    ******************************************************/

    LabelMenuItemPtr MenuItem1 = LabelMenuItem::create();
    LabelMenuItemPtr MenuItem2 = LabelMenuItem::create();
    LabelMenuItemPtr MenuItem3 = LabelMenuItem::create();
    LabelMenuItemPtr MenuItem4 = LabelMenuItem::create();
    LabelMenuItemPtr SubMenuItem1 = LabelMenuItem::create();
    LabelMenuItemPtr SubMenuItem2 = LabelMenuItem::create();
    LabelMenuItemPtr SubMenuItem3 = LabelMenuItem::create();
    SeperatorMenuItemPtr ExampleSeperator = SeperatorMenuItem::create();
    MenuPtr ExampleSubMenu = Menu::create();
    
    /******************************************************
            
            Edit the LabelMenuItems

            -setText("TEXT"): Sets the text on the 
                item to be TEXT
            -setEnabled(Boolean): sets the menu item
                to be either enabled or disabled

    ******************************************************/

    beginEditCP(MenuItem1, LabelMenuItem::TextFieldMask | LabelMenuItem::AcceleratorKeyFieldMask);
        MenuItem1->setText("Menu Item 1");
    endEditCP(MenuItem1, LabelMenuItem::TextFieldMask | LabelMenuItem::AcceleratorKeyFieldMask);
    
    beginEditCP(MenuItem2, LabelMenuItem::TextFieldMask);
        MenuItem2->setText("Menu Item 2");
    endEditCP(MenuItem2, LabelMenuItem::TextFieldMask);
    
    beginEditCP(MenuItem3, LabelMenuItem::TextFieldMask | LabelMenuItem::AcceleratorKeyFieldMask | LabelMenuItem::AcceleratorModifiersFieldMask);
        MenuItem3->setText("Menu Item 3");
    endEditCP(MenuItem3, LabelMenuItem::TextFieldMask | LabelMenuItem::AcceleratorKeyFieldMask | LabelMenuItem::AcceleratorModifiersFieldMask);
    
    beginEditCP(MenuItem4, LabelMenuItem::TextFieldMask | LabelMenuItem::EnabledFieldMask);
        MenuItem4->setText("Menu Item 4");
        MenuItem4->setEnabled(false);
    endEditCP(MenuItem4, LabelMenuItem::TextFieldMask | LabelMenuItem::EnabledFieldMask);
    
    beginEditCP(SubMenuItem1, LabelMenuItem::TextFieldMask);
        SubMenuItem1->setText("SubMenu Item 1");
    endEditCP(SubMenuItem1, LabelMenuItem::TextFieldMask);
    
    beginEditCP(SubMenuItem2, LabelMenuItem::TextFieldMask);
        SubMenuItem2->setText("SubMenu Item 2");
    endEditCP(SubMenuItem2, LabelMenuItem::TextFieldMask);
    
    beginEditCP(SubMenuItem3, LabelMenuItem::TextFieldMask);
        SubMenuItem3->setText("SubMenu Item 3");
    endEditCP(SubMenuItem3, LabelMenuItem::TextFieldMask);
    
    beginEditCP(ExampleSubMenu, LabelMenuItem::TextFieldMask);
        ExampleSubMenu->setText("Sub Menu");
    endEditCP(ExampleSubMenu, LabelMenuItem::TextFieldMask);

    // This adds three LabelMenuItems to the Menu,
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
    PopupMenuPtr ExamplePopupMenu = PopupMenu::create();
    ExamplePopupMenu->addItem(MenuItem1);
    ExamplePopupMenu->addItem(MenuItem2);
    ExamplePopupMenu->addItem(MenuItem3);
    ExamplePopupMenu->addItem(ExampleSeperator);
    ExamplePopupMenu->addItem(ExampleSubMenu);
    ExamplePopupMenu->addItem(MenuItem4);
    
    // Create a Button and Font
    UIFontPtr PopupMenuButtonFont = osg::UIFont::create();
    beginEditCP(PopupMenuButtonFont, UIFont::SizeFieldMask);
        PopupMenuButtonFont->setSize(16);
    endEditCP(PopupMenuButtonFont, UIFont::SizeFieldMask);

    ButtonPtr PopupMenuButton = osg::Button::create();
    beginEditCP(PopupMenuButton, Button::PopupMenuFieldMask | Button::TextFieldMask | Button::PreferredSizeFieldMask | Button::FontFieldMask);
        PopupMenuButton->setText("RightClickMe!");
        // Add the PopupMenu to PopupMenuButton so that when right clicked,
        // the PopupMenu will appear
        PopupMenuButton->setPopupMenu(ExamplePopupMenu);
        PopupMenuButton->setPreferredSize(Vec2f(200,100));
        PopupMenuButton->setFont(PopupMenuButtonFont);
    endEditCP(PopupMenuButton, Button::PopupMenuFieldMask | Button::TextFieldMask | Button::PreferredSizeFieldMask | Button::FontFieldMask);


    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorUIBackgroundPtr MainInternalWindowBackground = osg::ColorUIBackground::create();
    beginEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);

    LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().addValue(PopupMenuButton);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
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
        TutorialViewport->getForegrounds().addValue(TutorialUIForeground);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);

    // Show the whole Scene
    mgr->showAll();
    TutorialWindowEventProducer->openWindow(Pnt2f(50,50),
                                        Vec2f(550,550),
                                        "OpenSG 25PopupMenu Window");

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
void reshape(Vec2f Size)
{
    mgr->resize(Size.x(), Size.y());
}