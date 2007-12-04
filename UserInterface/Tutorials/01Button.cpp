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

// 01 Button Headers
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGToggleButton.h>
#include <OpenSG/UserInterface/OSGUIFont.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGPolygonUIDrawObject.h>
#include <OpenSG/UserInterface/OSGUIDrawObjectCanvas.h>

// Create a class to allow for the use of the Escape
// key to exit
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEvent& e)
   {
       if(e.getKey() == KeyEvent::KEY_ESCAPE)
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

	/******************************************************

		 Create an ActionListener to display text
		 in the Console Window when the Button is
		 pressed (causing an action).

	******************************************************/

class Button1ActionListener : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
	{
		std::cout << "Button 1 Action" << std::endl;
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
 
        // Add the torus as a child
        scene->addChild(TorusGeometryNode);
    }
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

	// Create the Graphics
	GraphicsPtr graphics = osg::Graphics2D::create();

	// Initialize the LookAndFeelManager to enable default settings
	LookAndFeelManager::the()->getLookAndFeel()->init();
	/******************************************************

				 Create an Button component and
				 a simple Font to be used.
				 See 17Label_Font for more
				 information about Fonts

	******************************************************/
	ButtonPtr button1 = osg::Button::create();

	UIFontPtr sampleFont = osg::UIFont::create();
    beginEditCP(sampleFont, UIFont::SizeFieldMask);
		sampleFont->setSize(16);
	endEditCP(sampleFont, UIFont::SizeFieldMask);

	/******************************************************

			Edit the Button's characteristics.
			Note: the first 4 functions can
			be used with any Component and 
			are not Button specific.

			-setMinSize(Vec2s): Determine the 
				Minimum	Size of the Component.
				Some Layouts will automatically
				resize Components; this prevents
				the Size from going below a
				certain value.
			-setMaxSize(Vec2s): Determine the 
				Maximum Size of the Component.
			-setPreferredSize(Vec2s): Determine
				the Preferred Size of the Component.
				This is what the Component will
				be displayed at unless changed by
				another Component.
			-setToolTipText("Text"): Determine
				what text is displayed while
				Mouse is hovering above Component.
				The word Text will be displayed.
			
			Button specific functions:
			-setText("DesiredText"): Determine 
				the Button's text.  It will read
				DesiredText in this case.
			-setFont(FontName): Determine the 
				Font to be used on the Button.
			-setTextColor(Color4f): Determine the
				Color the text will be.
			-setRolloverTextColor(Color4f): Determine
				what the text Color will be when
				the Mouse Cursor is above the 
				Button.
			-setActiveTextColor(Color4f): Determine
				what the text Color will be when
				the Button is pressed (Active).
			-setVerticalAlignment(Float OR Enum):
				Determine the Vertical Alignment
				of the text.  The Float value is 
				in [0.0, 1.0] and the Enums are:
				VERTICAL_CENTER, VERTICAL_TOP, 
				or VERTICAL_BOTTOM.
			-setHorizontalAlignmnet(Float OR Enum):
				Determine the Horizontal Alignment
				of the text.  The Float value is 
				in [0.0, 1.0] and the Enums are:
				HORIZONTAL_CENTER, HORIZONTAL_LEFT, 
				or HORIZONTAL_RIGHT.


	******************************************************/
    beginEditCP(button1, Component::MinSizeFieldMask | Component::MaxSizeFieldMask | Component::PreferredSizeFieldMask | Button::TextColorFieldMask | Button::TextFieldMask | Button::FontFieldMask | Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask | Button::ToolTipTextFieldMask);
		    button1->setMinSize( Vec2s (50, 25) );
		    button1->setMaxSize( Vec2s (200, 100) );
		    button1->setPreferredSize( Vec2s (100, 50) );
            button1->setToolTipText("Button 1 ToolTip");

		    button1->setText("Button 1");
		    button1->setFont(sampleFont);
		    button1->setTextColor( Color4f(1.0, 0.0, 0.0, 1.0) );
		    button1->setRolloverTextColor( Color4f(1.0, 0.0, 1.0, 1.0) );
		    button1->setActiveTextColor( Color4f(1.0, 0.0, 0.0, 1.0) );
		    button1->setVerticalAlignment(0.0);
		    button1->setHorizontalAlignment(1.0);
	endEditCP(button1, Component::MinSizeFieldMask | Component::MaxSizeFieldMask | Component::PreferredSizeFieldMask | Button::TextColorFieldMask | Button::TextFieldMask | Button::FontFieldMask | Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask | Button::ToolTipTextFieldMask);
	
	// Create an ActionListener and assign it to button1
	// This is defined above, and wil
	Button1ActionListener button1AL;
	button1->addActionListener( &button1AL);

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
        //Set the Text to be shown as a ToolTip
        toggleButton1->setToolTipText("Toggle Button ToolTip");
	endEditCP(toggleButton1, ToggleButton::SelectedFieldMask | Button::TextFieldMask | Button::ToolTipTextFieldMask);

    //Button with Image
	ButtonPtr DrawObjectButton = osg::Button::create();

    DrawObjectButton->setImage(std::string("Data/ComponentTransform.png"));
    DrawObjectButton->setActiveImage(std::string("Data/ComponentTransform.png"));
    DrawObjectButton->setFocusedImage(std::string("Data/ComponentTransform.png"));
    DrawObjectButton->setRolloverImage(std::string("Data/ComponentTransform.png"));
    DrawObjectButton->setDisabledImage(std::string("Data/ComponentTransform.png"));

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
	   MainFrame->getChildren().addValue(DrawObjectButton);
	   MainFrame->setLayout(MainFrameLayout);
	   MainFrame->setBackground(mainBackground);
	endEditCP  (MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Component::BackgroundFieldMask);

    TutorialKeyListener TheKeyListener;
    MainFrame->addKeyListener(&TheKeyListener);

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
    endEditCP  (foreground, UIForeground::DrawingSurfaceFieldMask |UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);


    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the manager what to manage
    mgr->setWindow(MainWindow );
    mgr->setRoot  (scene);

	// Add the UI Foreground Object to the Scene
	ViewportPtr viewport = mgr->getWindow()->getPort(0);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);
		viewport->getForegrounds().addValue(foreground);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);
    // Show the whole scene
    mgr->showAll();

    TheWindowEventProducer->openWindow(Pnt2s(50,50),
                                        Vec2s(550,550),
                                        "OpenSG 01Button Window");

    while(!ExitApp)
    {
        TheWindowEventProducer->update();
        TheWindowEventProducer->draw();
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
