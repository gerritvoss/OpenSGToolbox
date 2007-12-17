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

// 22TextArea Headers
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGUIFont.h>
#include <OpenSG/UserInterface/OSGScrollPanel.h>
#include <OpenSG/UserInterface/OSGTextArea.h>


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

    // Create a simple Font to be used with the ExampleTextArea
    UIFontPtr ExampleFont = osg::UIFont::create();
    beginEditCP(ExampleFont, UIFont::SizeFieldMask);
        ExampleFont->setSize(16);
    endEditCP(ExampleFont, UIFont::SizeFieldMask);

    /******************************************************


        Create and edit the TextArea and determine its 
        characteristics.  A TextArea is a component 
        that allows you to enter text into the box via 
        keyboard input.  You can select text by    using 
        your mouse or pressing shift and the left and 
        right arrow keys.

        The only difference between a TextArea and
        TextField is that a TextArea can have 
        multiple lines of text 
        within it.

        -setTextColor(Color4f): Determine color of 
            text within TextArea.
        -setSelectionBoxColor(Color4f): Determine the
			color that highlighting around the 
			selected text appears.
        -setSelectionTextColor(Color4f): Determine the 
            color the selected text appears.
        -setText("TextToBeDisplayed"): Determine  
            initial text within TextArea.
        -setFont(FontName): Determine the Font 
			used within TextArea
        -setSelectionStart(StartCharacterNumber):
            Determine the character which the 
            selection will initially start after.
        -setSelectionEnd(EndCharacterNumber): 
            Determine the character which the 
            selection will end before.
        -setCaretPosition(Location): Determine the 
            location of the Caret within the TextArea.
			Note: this does not do too much
            currently because the only way 
            to cause the TextArea to gain focus is
            to click within it, causing the 
            Caret to move.
            
    ******************************************************/

    // Create a TextArea component
    TextAreaPtr ExampleTextArea = osg::TextArea::create();

    beginEditCP(ExampleTextArea, TextArea::MinSizeFieldMask | TextArea::MaxSizeFieldMask | TextArea::PreferredSizeFieldMask | TextArea::MinSizeFieldMask 
        | TextArea::TextColorFieldMask | TextArea::FontFieldMask 
        | TextArea::SelectionBoxColorFieldMask | TextArea::SelectionTextColorFieldMask);
        ExampleTextArea->setPreferredSize(Vec2s(300, 200));
        ExampleTextArea->setMinSize(Vec2s(300, 200));
        ExampleTextArea->setTextColor(Color4f(0.0, 0.0, 0.0, 1.0));
        ExampleTextArea->setSelectionBoxColor(Color4f(0.0, 0.0, 1.0, 1.0));
        ExampleTextArea->setSelectionTextColor(Color4f(1.0, 1.0, 1.0, 1.0));
        // Determine the font and initial text
        ExampleTextArea->setText("What");
        ExampleTextArea->setFont(ExampleFont);
        // This will select the "a" from above
        ExampleTextArea->setSelectionStart(2);
        ExampleTextArea->setSelectionEnd(3);
        ExampleTextArea->setCaretPosition(2);
    endEditCP(ExampleTextArea, TextArea::MinSizeFieldMask | TextArea::MaxSizeFieldMask | TextArea::PreferredSizeFieldMask | TextArea::MinSizeFieldMask 
        | TextArea::TextColorFieldMask| TextArea::FontFieldMask 
        | TextArea::SelectionBoxColorFieldMask | TextArea::SelectionTextColorFieldMask);
        
    // Create a ScrollPanel
    ScrollPanelPtr TextAreaScrollPanel = ScrollPanel::create();
    beginEditCP(TextAreaScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        TextAreaScrollPanel->setPreferredSize(Vec2s(200,200));
        TextAreaScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(TextAreaScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    // Add the TextArea to the ScrollPanel so it is displayed
	TextAreaScrollPanel->setViewComponent(ExampleTextArea);

    
    // Create The Main Frame
    FramePtr MainFrame = osg::Frame::create();
    LayoutPtr MainFrameLayout = osg::FlowLayout::create();
    beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);
       MainFrame->getChildren().addValue(TextAreaScrollPanel);
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

    beginEditCP(TutorialUIForeground, UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);
        TutorialUIForeground->setFramePositionOffset(Vec2s(0,0));
        TutorialUIForeground->setFrameBounds(Vec2f(0.5,0.5));
    endEditCP(TutorialUIForeground, UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);


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
                                        Vec2s(750,750),
                                        "OpenSG 22TextArea Window");

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