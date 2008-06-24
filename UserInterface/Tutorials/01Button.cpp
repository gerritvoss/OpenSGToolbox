/*************************************************
Welcome to the 01Button tutorial.  In this tutorial, 
you will see examples of how to create the following 
OGS User Interface components:
	
	ActionListener
	Button
	ToggleButton
	
Buttons are often used to create interactivity
within the interface (via clicking, etc).  This
tutorial details how to create simple Buttons and
modify their basic features.  The ActionListener
class is used to create the desired result when
actions are preformed (again, clicking, etc).  A
ToggleButton remains pressed, hence "Toggle."

The following all are shown and explained
within this tutorial for:

Button/ToggleButton
    Setting Sizes (Max/Min, and display size)
	Setting Tool Tip Text
	Setting the displayed Text
	Setting the Font
	Setting the Font Color
	Setting the Active/Rollover text color
		(Active = pressed, Rollover = mousedover)
	Setting the Text alignment

ToggleButton
	Setting to "selected"

These tutorials contain potentially relevant
information:
	02AbsoluteLayout: Assigning constraints to
		Buttons
	03Border: Setting Active Borders
	04Background: Setting Active Backgrounds
	06BoxLayout: Showing Max/Min Size effects



*************************************************/



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

// 01 Button Headers
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGToggleButton.h>
#include <OpenSG/UserInterface/OSGUIFont.h>
#include <OpenSG/UserInterface/OSGColorLayer.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGPolygonUIDrawObject.h>
#include <OpenSG/UserInterface/OSGUIDrawObjectCanvas.h>

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

class ExampleButtonActionListener : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
    {
        std::cout << "Button 1 Action" << std::endl;
    }
};

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    WindowEventProducerPtr TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

	beginEditCP(TutorialWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);
		TutorialWindowEventProducer->setUseCallbackForDraw(true);
		TutorialWindowEventProducer->setUseCallbackForReshape(true);
	endEditCP(TutorialWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);

    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TutorialWindowEventProducer->addWindowListener(&TheTutorialWindowListener);
    TutorialKeyListener TheKeyListener;
    TutorialWindowEventProducer->addKeyListener(&TheKeyListener);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
	
    TutorialWindowEventProducer->openWindow(Pnt2f(50,50),
                                        Vec2f(550,550),
                                        "OpenSG 01Button Window");
										
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

                 Create an Button Component and
                 a simple Font.
                 See 17Label_Font for more
                 information about Fonts.

    ******************************************************/
    ButtonPtr ExampleButton = osg::Button::create();

    UIFontPtr ExampleFont = osg::UIFont::create();
    beginEditCP(ExampleFont, UIFont::SizeFieldMask);
        ExampleFont->setSize(16);
    endEditCP(ExampleFont, UIFont::SizeFieldMask);

    /******************************************************

            Edit the Button's characteristics.
            Note: the first 4 functions can
            be used with any Component and 
            are not specific to Button.

            -setMinSize(Vec2f): Determine the 
                Minimum Size of the Component.
                Some Layouts will automatically
                resize Components; this prevents
                the Size from going below a
                certain value.
            -setMaxSize(Vec2f): Determine the 
                Maximum Size of the Component.
            -setPreferredSize(Vec2f): Determine
                the Preferred Size of the Component.
                This is what the Component will
                be displayed at unless changed by
                another Component (such as a 
                Layout).
            -setToolTipText("Text"): Determine
                what text is displayed while
                Mouse is hovering above Component.
                The word Text will be displayed
                in this case.
            
            Functions specfic to Button:
            -setText("DesiredText"): Determine 
                the Button's text.  It will read
                DesiredText in this case.
            -setFont(FontName): Determine the 
                Font to be used on the Button.
            -setTextColor(Color4f): Determine the
                Color for the text.
            -setRolloverTextColor(Color4f): Determine
                what the text Color will be when
                the Mouse Cursor is above the 
                Button.
            -setActiveTextColor(Color4f): Determine
                what the text Color will be when
                the Button is pressed (denoted by
                Active).
            -setVerticalAlignment(Float OR Enum):
                Determine the Vertical Alignment
                of the text.  The Float value is 
                in [0.0, 1.0] and the Enums are:
                VERTICAL_CENTER, VERTICAL_TOP, 
                or VERTICAL_BOTTOM.
            -setHorizontalAlignmnet(Real32 OR Enum):
                Determine the Horizontal Alignment
                of the text.  The Float value is 
                in [0.0, 1.0] and the Enums are:
                HORIZONTAL_CENTER, HORIZONTAL_LEFT, 
                or HORIZONTAL_RIGHT.

    ******************************************************/
    beginEditCP(ExampleButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask | Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask);
            ExampleButton->setMinSize(Vec2f(50, 25));
            ExampleButton->setMaxSize(Vec2f(200, 100));
            ExampleButton->setPreferredSize(Vec2f(100, 50));
            ExampleButton->setToolTipText("Button 1 ToolTip");

            ExampleButton->setText("Button 1");
            ExampleButton->setFont(ExampleFont);
            ExampleButton->setTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
            ExampleButton->setRolloverTextColor(Color4f(1.0, 0.0, 1.0, 1.0));
            ExampleButton->setActiveTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
            ExampleButton->setVerticalAlignment(0.0);
            ExampleButton->setHorizontalAlignment(1.0);
    endEditCP(ExampleButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask | Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask);
            
    // Create an ActionListener and assign it to ExampleButton
    // This Class is defined above, and will cause the output
    // window to display "Button 1 Action" when pressed
    ExampleButtonActionListener TheExampleButtonActionListener;
    ExampleButton->addActionListener(&TheExampleButtonActionListener);

    /******************************************************

        Create a ToggleButton and determine its 
        characteristics.  ToggleButton inherits
        off of Button, so all characteristsics
        used above can be used with ToggleButtons
        as well.

        The only difference is that when pressed,
        ToggleButton remains pressed until pressed 
        again.

        -setSelected(bool): Determine whether the 
            ToggleButton is Selected (true) or
            deselected (false).  

    ******************************************************/
    ToggleButtonPtr ExampleToggleButton = osg::ToggleButton::create();
    
    beginEditCP(ExampleToggleButton, ToggleButton::SelectedFieldMask | ToggleButton::TextFieldMask | ToggleButton::ToolTipTextFieldMask);
        ExampleToggleButton->setSelected(false);
        ExampleToggleButton->setText("ToggleMe");
        ExampleToggleButton->setToolTipText("Toggle Button ToolTip");
    endEditCP(ExampleToggleButton, ToggleButton::SelectedFieldMask | ToggleButton::TextFieldMask | ToggleButton::ToolTipTextFieldMask);

    //Button with Image
    ButtonPtr ExampleDrawObjectButton = osg::Button::create();

    ExampleDrawObjectButton->setImage(std::string("Data/ComponentTransform.png"));
    ExampleDrawObjectButton->setActiveImage(std::string("Data/ComponentTransform.png"));
    ExampleDrawObjectButton->setFocusedImage(std::string("Data/ComponentTransform.png"));
    ExampleDrawObjectButton->setRolloverImage(std::string("Data/ComponentTransform.png"));
    ExampleDrawObjectButton->setDisabledImage(std::string("Data/ComponentTransform.png"));

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
    LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().push_back(ExampleButton);
       MainInternalWindow->getChildren().push_back(ExampleToggleButton);
       MainInternalWindow->getChildren().push_back(ExampleDrawObjectButton);
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

    mgr->setRoot(scene);

    // Add the UI Foreground Object to the Scene
    ViewportPtr TutorialViewport = mgr->getWindow()->getPort(0);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);
        TutorialViewport->getForegrounds().push_back(TutorialUIForeground);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);

    // Show the whole Scene
    mgr->showAll();


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
