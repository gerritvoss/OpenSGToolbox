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
#include <OpenSG/UserInterface/OSGToggleButton.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGUIFont.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
#include <OpenSG/UserInterface/OSGPopupMenu.h>
#include <OpenSG/UserInterface/OSGMenu.h>
#include <OpenSG/UserInterface/OSGLabelMenuItem.h>
#include <OpenSG/UserInterface/OSGSeperatorMenuItem.h>

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

    //Create a Popup Menu
    LabelMenuItemPtr Item1 = LabelMenuItem::create();
    LabelMenuItemPtr Item2 = LabelMenuItem::create();
    LabelMenuItemPtr Item3 = LabelMenuItem::create();
    SeperatorMenuItemPtr Seperator1 = SeperatorMenuItem::create();
    LabelMenuItemPtr Item4 = LabelMenuItem::create();
    MenuPtr Item5 = Menu::create();
    LabelMenuItemPtr SubItem1 = LabelMenuItem::create();
    LabelMenuItemPtr SubItem2 = LabelMenuItem::create();
    LabelMenuItemPtr SubItem3 = LabelMenuItem::create();
    
    beginEditCP(Item1, LabelMenuItem::TextFieldMask | LabelMenuItem::AcceleratorKeyFieldMask);
        Item1->setText("Menu Item 1");
        Item1->setAcceleratorKey(KeyEvent::KEY_F9);
    endEditCP(Item1, LabelMenuItem::TextFieldMask | LabelMenuItem::AcceleratorKeyFieldMask);
    
    beginEditCP(Item2, LabelMenuItem::TextFieldMask);
        Item2->setText("Menu Item 2");
    endEditCP(Item2, LabelMenuItem::TextFieldMask);
    
    beginEditCP(Item3, LabelMenuItem::TextFieldMask | LabelMenuItem::AcceleratorKeyFieldMask | LabelMenuItem::AcceleratorModifiersFieldMask);
        Item3->setText("Menu Item 3");
        Item3->setAcceleratorKey(KeyEvent::KEY_G);
        Item3->setAcceleratorModifiers(KeyEvent::KEY_MODIFIER_CONTROL | KeyEvent::KEY_MODIFIER_SHIFT);
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
    Item5->addItem(SubItem1);
    Item5->addItem(SubItem2);
    Item5->addItem(SubItem3);
    
    PopupMenuPtr Button1PopupMenu = PopupMenu::create();
    Button1PopupMenu->addItem(Item1);
    Button1PopupMenu->addItem(Item2);
    Button1PopupMenu->addItem(Item3);
    Button1PopupMenu->addItem(Seperator1);
    Button1PopupMenu->addItem(Item5);
    Button1PopupMenu->addItem(Item4);
    
	// Create a Button component
	ButtonPtr button1 = osg::Button::create();
	// Create a simple Font to be used with the Button
	UIFontPtr sampleFont = osg::UIFont::create();
    beginEditCP(sampleFont, UIFont::SizeFieldMask);
		sampleFont->setSize(16);
	endEditCP(sampleFont, UIFont::SizeFieldMask);


    beginEditCP(button1, Component::MinSizeFieldMask | Component::MaxSizeFieldMask | Component::PreferredSizeFieldMask | Component::PopupMenuFieldMask | Button::TextColorFieldMask | Button::TextFieldMask | Button::FontFieldMask | Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask | Button::ToolTipTextFieldMask);
		button1->setText("Button 1");
        button1->setPopupMenu(Button1PopupMenu);
    endEditCP(button1, Component::MinSizeFieldMask | Component::MaxSizeFieldMask | Component::PreferredSizeFieldMask | Component::PopupMenuFieldMask | Button::TextColorFieldMask | Button::TextFieldMask | Button::FontFieldMask | Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask | Button::ToolTipTextFieldMask);

	/******************************************************


		Create a ToggleButton and determine its 
		characteristics.  All characteristics Buttons
		have are also present in ToggleButton.

		The only difference is that when pressed,
		ToggleButton remains pressed until pressed 
		again.



	******************************************************/
	ToggleButtonPtr toggleButton1 = osg::ToggleButton::create();
	
	beginEditCP(toggleButton1, ToggleButton::SelectedFieldMask | Button::TextFieldMask | Button::ToolTipTextFieldMask);
		// Determine if the ToggleButton appears pressed (TRUE) or released (FALSE)
		toggleButton1->setSelected(false);
		toggleButton1->setText("ToggleMe");
	endEditCP(toggleButton1, ToggleButton::SelectedFieldMask | Button::TextFieldMask | Button::ToolTipTextFieldMask);


	// Create Background to be used with the MainFrame
	ColorUIBackgroundPtr mainBackground = osg::ColorUIBackground::create();
	beginEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
		mainBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
	endEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
	// Create The Main Frame
	FramePtr MainFrame = osg::Frame::create();
	LayoutPtr MainFrameLayout = osg::FlowLayout::create();
	beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Component::BackgroundFieldMask);
	   // Assign the Button to the MainFrame so it will be displayed
	   // when the view is rendered.
	   MainFrame->getChildren().addValue(button1);
	   MainFrame->getChildren().addValue(toggleButton1);
	   MainFrame->setLayout(MainFrameLayout);
	   MainFrame->setBackground(mainBackground);
	endEditCP  (MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Component::BackgroundFieldMask);

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
		foreground->setFrameBounds(Vec2f(0.5,0.5));
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
