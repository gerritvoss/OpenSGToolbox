// OpenSG Tutorial Example: Creating a Button Component
//
// This tutorial explains how to edit the basic features of
// a Button created in the OSG User Interface library.
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

// 16TextField Headers
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGUIFont.h>
#include <OpenSG/UserInterface/OSGTextField.h>

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

    // Create a simple Font to be used with the TextField
    UIFontPtr sampleFont = osg::UIFont::create();
    beginEditCP(sampleFont, UIFont::SizeFieldMask | UIFont::FamilyFieldMask | UIFont::GapFieldMask | UIFont::GlyphPixelSizeFieldMask | UIFont::TextureWidthFieldMask | UIFont::StyleFieldMask);
        sampleFont->setSize(16);
    endEditCP(sampleFont, UIFont::SizeFieldMask | UIFont::FamilyFieldMask | UIFont::GapFieldMask | UIFont::GlyphPixelSizeFieldMask | UIFont::TextureWidthFieldMask | UIFont::StyleFieldMask);

    /******************************************************


        Create and edit the TextField.  A TextField is 
		a Component which allows a single line of text
		to be displayed.  Text can be entered via the
		keyboard, and selected with arrow keys or
		the Mouse.
		
        -setTextColor(Color4f): Determine the 
			Text Color.
        setSelectionBoxColor(Color4f): Determine
			the Color of highlighting around
			selected Text.
        -setSelectionTextColor(Color4f): Determine
			the Color of selected Text.
        -setText("TextToBeDisplayed"): Determine
		    initial Text within TextField.
        -setFont(FontName): Determine the Font
            used within TextField.
        -setSelectionStart(StartCharacterNumber):
            Determine the character with which  
			the selection will initially start.
        -setSelectionEnd(EndCharacterNumber): 
            Determine the character which the
			selection ends before.
        -setVerticalAlignment(float): Determine 
			the Vertical alignment of the text.  
			The float is a percentage is from the 
			top of the text [0.0-1.0].  Note: be 
			sure to visually verify this, as due
            to font size and line size this does
            not always place it exactly
            at the percentage point.

    ******************************************************/

    // Create a TextField component
    TextFieldPtr ExampleTextField = osg::TextField::create();

    beginEditCP(ExampleTextField, Component::MinSizeFieldMask | Component::MaxSizeFieldMask | Component::PreferredSizeFieldMask 
        | TextComponent::TextColorFieldMask | TextComponent::FontFieldMask | TextField::VerticalAlignmentFieldMask 
        | TextComponent::SelectionBoxColorFieldMask | TextComponent::SelectionTextColorFieldMask);
        ExampleTextField->setPreferredSize( Vec2s (100, 50));
        ExampleTextField->setTextColor(Color4f(0.0, 0.0, 0.0, 1.0));
        ExampleTextField->setSelectionBoxColor(Color4f(0.0, 0.0, 1.0, 1.0));
        ExampleTextField->setSelectionTextColor(Color4f(1.0, 1.0, 1.0, 1.0));
        ExampleTextField->setText("What");
        ExampleTextField->setFont(sampleFont);
        // The next two functions will select the "a" from above
        ExampleTextField->setSelectionStart(2);
        ExampleTextField->setSelectionEnd(3);
        ExampleTextField->setVerticalAlignment(0.5);
    endEditCP(ExampleTextField, Component::MinSizeFieldMask | Component::MaxSizeFieldMask | Component::PreferredSizeFieldMask 
        | TextComponent::TextColorFieldMask| TextComponent::FontFieldMask | TextField::VerticalAlignmentFieldMask
        | TextComponent::SelectionBoxColorFieldMask | TextComponent::SelectionTextColorFieldMask);
        
    // Create another TextField Component
    TextFieldPtr ExampleTextField2 = osg::TextField::create();
    beginEditCP(ExampleTextField2, TextComponent::TextFieldMask);
        ExampleTextField2->setText("");
    endEditCP(ExampleTextField2, TextComponent::TextFieldMask);


    // Create The Main Frame
    FramePtr MainFrame = osg::Frame::create();
    LayoutPtr MainFrameLayout = osg::FlowLayout::create();
    beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);
       // Add TextField to MainFrame
       MainFrame->getChildren().addValue(ExampleTextField);
       MainFrame->getChildren().addValue(ExampleTextField2);
       MainFrame->setLayout(MainFrameLayout);
    endEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);

    // Create the Drawing Surface
    UIDrawingSurfacePtr TutorialDrawingSurface = UIDrawingSurface::create();
    beginEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask | UIDrawingSurface::EventProducerFieldMask);
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setRootFrame(MainFrame);
        TutorialDrawingSurface->setEventProducer(TutorialWindowEventProducer);
    endEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask | UIDrawingSurface::EventProducerFieldMask);
    // Create the UI Foreground Object
    UIForegroundPtr TutorialUIForeground = osg::UIForeground::create();

    beginEditCP(TutorialUIForeground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);
        TutorialUIForeground->setFramePositionOffset(Vec2s(0,0));
        TutorialUIForeground->setFrameBounds(Vec2f(0.5,0.5));
    endEditCP(TutorialUIForeground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);

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
                                        "OpenSG 16TextField Window");

    //Main Event Loop
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