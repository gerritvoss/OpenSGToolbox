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
            
            Create Popup Menu Components
        
        -LabelMenuItem: These are items that are contained
            within a menu; they are the things you click
            on to cause something to occur
        -SeperatorMenuItem:  These place a seperator 
            line between items in a menu
        -Menu: These are sub-menus within another Menu;
            LabelMenuItems and SeperatorMenuItems
            are added to a Menu


    ******************************************************/

    LabelMenuItemPtr Item1 = LabelMenuItem::create();
    LabelMenuItemPtr Item2 = LabelMenuItem::create();
    LabelMenuItemPtr Item3 = LabelMenuItem::create();
    LabelMenuItemPtr Item4 = LabelMenuItem::create();
    LabelMenuItemPtr SubItem1 = LabelMenuItem::create();
    LabelMenuItemPtr SubItem2 = LabelMenuItem::create();
    LabelMenuItemPtr SubItem3 = LabelMenuItem::create();
    SeperatorMenuItemPtr Seperator1 = SeperatorMenuItem::create();
    MenuPtr Item5 = Menu::create();

    
    /******************************************************
            
            Edit the LabelMenuItems

            -setText("TEXT"): Sets the text on the 
                item to be TEXT
            -setEnabled(Boolean): sets the menu item
                to be either enabled or disabled

    ******************************************************/

    beginEditCP(Item1, LabelMenuItem::TextFieldMask | LabelMenuItem::AcceleratorKeyFieldMask);
        Item1->setText("Menu Item 1");
    endEditCP(Item1, LabelMenuItem::TextFieldMask | LabelMenuItem::AcceleratorKeyFieldMask);
    
    beginEditCP(Item2, LabelMenuItem::TextFieldMask);
        Item2->setText("Menu Item 2");
    endEditCP(Item2, LabelMenuItem::TextFieldMask);
    
    beginEditCP(Item3, LabelMenuItem::TextFieldMask | LabelMenuItem::AcceleratorKeyFieldMask | LabelMenuItem::AcceleratorModifiersFieldMask);
        Item3->setText("Menu Item 3");
    endEditCP(Item3, LabelMenuItem::TextFieldMask | LabelMenuItem::AcceleratorKeyFieldMask | LabelMenuItem::AcceleratorModifiersFieldMask);
    
    beginEditCP(Item4, LabelMenuItem::TextFieldMask | LabelMenuItem::EnabledFieldMask);
        Item4->setText("Menu Item 4");
        Item4->setEnabled(false);
    endEditCP(Item4, LabelMenuItem::TextFieldMask | LabelMenuItem::EnabledFieldMask);
    
    beginEditCP(SubItem1, LabelMenuItem::TextFieldMask);
        SubItem1->setText("SubMenu Item 1");
    endEditCP(SubItem1, LabelMenuItem::TextFieldMask);
    
    beginEditCP(SubItem2, LabelMenuItem::TextFieldMask);
        SubItem2->setText("SubMenu Item 2");
    endEditCP(SubItem2, LabelMenuItem::TextFieldMask);
    
    beginEditCP(SubItem3, LabelMenuItem::TextFieldMask);
        SubItem3->setText("SubMenu Item 3");
    endEditCP(SubItem3, LabelMenuItem::TextFieldMask);
    
    beginEditCP(Item5, LabelMenuItem::TextFieldMask);
        Item5->setText("Sub Menu");
    endEditCP(Item5, LabelMenuItem::TextFieldMask);

    // This adds three LabelMenuItems to the Menu,
    // creating a submenu.  Note this does not
    // involve begin/endEditCPs to do

    Item5->addItem(SubItem1);
    Item5->addItem(SubItem2);
    Item5->addItem(SubItem3);
    
    /******************************************************
            
            Create the PopupMenu itself

            Items are added in the order in which
            they will be displayed (top to bottom)
            via addItem(ITEM_TO_BE_ADDED)

            The PopupMenu is attached to bbutton1
            below using setPopupMenu(POPUP_MENU_NAME)

    ******************************************************/
    PopupMenuPtr Button1PopupMenu = PopupMenu::create();
    Button1PopupMenu->addItem(Item1);
    Button1PopupMenu->addItem(Item2);
    Button1PopupMenu->addItem(Item3);
    Button1PopupMenu->addItem(Seperator1);
    Button1PopupMenu->addItem(Item5);
    Button1PopupMenu->addItem(Item4);
    
    // Create a Button and Font
    UIFontPtr button1Font = osg::UIFont::create();
    beginEditCP(button1Font, UIFont::SizeFieldMask);
        button1Font->setSize(16);
    endEditCP(button1Font, UIFont::SizeFieldMask);

    ButtonPtr button1 = osg::Button::create();
    beginEditCP(button1, Component::PopupMenuFieldMask | Button::TextFieldMask | Component::PreferredSizeFieldMask | Button::FontFieldMask);
        button1->setText("RightClickMe!");
        // Add the PopupMenu to button1 so that when right clicked,
        // the PopupMenu will appear
        button1->setPopupMenu(Button1PopupMenu);
        button1->setPreferredSize(Vec2s(200,100));
        button1->setFont(button1Font);
    endEditCP(button1, Component::PopupMenuFieldMask | Button::TextFieldMask| Component::PreferredSizeFieldMask | Button::FontFieldMask);


    // Create Background to be used with the MainFrame
    ColorUIBackgroundPtr MainFrameBackground = osg::ColorUIBackground::create();
    beginEditCP(MainFrameBackground, ColorUIBackground::ColorFieldMask);
        MainFrameBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainFrameBackground, ColorUIBackground::ColorFieldMask);
    // Create The Main Frame
    FramePtr MainFrame = osg::Frame::create();
    LayoutPtr MainFrameLayout = osg::FlowLayout::create();
    beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Component::BackgroundFieldMask);
       MainFrame->getChildren().addValue(button1);
       MainFrame->setLayout(MainFrameLayout);
       MainFrame->setBackground(MainFrameBackground);
    endEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Component::BackgroundFieldMask);

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
        TutorialUIForeground->setFrameBounds(Vec2f(0.5,0.5));
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
void reshape(Vec2s Size)
{
    mgr->resize(Size.x(), Size.y());
}