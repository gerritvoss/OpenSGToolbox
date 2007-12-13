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


// 20UIRectangle Headers
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
#include <OpenSG/UserInterface/OSGUIFont.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayout.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGUIRectangle.h>


// Create the WindowEvent 
WindowEventProducerPtr TutorialWindowEventProducer;


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

class TutorialMouseListener : public MouseListener
{
  public:
    virtual void mouseClicked(const MouseEvent& e)
    {
    }
    virtual void mouseEntered(const MouseEvent& e)
    {
    }
    virtual void mouseExited(const MouseEvent& e)
    {
    }
    virtual void mousePressed(const MouseEvent& e)
    {
        if(TutorialWindowEventProducer->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
            mgr->mouseButtonPress(e.getButton(), e.getLocation().x(), e.getLocation().y());
        }
    }
    virtual void mouseReleased(const MouseEvent& e)
    {
        if(TutorialWindowEventProducer->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
           mgr->mouseButtonRelease(e.getButton(), e.getLocation().x(), e.getLocation().y());
        }
    }
};

class TutorialMouseMotionListener : public MouseMotionListener
{
  public:
    virtual void mouseMoved(const MouseEvent& e)
    {
        if(TutorialWindowEventProducer->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
            mgr->mouseMove(e.getLocation().x(), e.getLocation().y());
        }
    }

    virtual void mouseDragged(const MouseEvent& e)
    {
        if(TutorialWindowEventProducer->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
            mgr->mouseMove(e.getLocation().x(), e.getLocation().y());
        }
    }
};

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();
    
    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    TutorialMouseListener mouseListener;
    TutorialMouseMotionListener mouseMotionListener;
    TutorialWindowEventProducer->addMouseListener(&mouseListener);
    TutorialWindowEventProducer->addMouseMotionListener(&mouseMotionListener);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TutorialWindowEventProducer->addWindowListener(&TheTutorialWindowListener);

   // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(90, 270, 16, 16);


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
    beginEditCP(TutorialGraphics);
        TutorialGraphics->setEnablePolygonAntiAliasing(false);
    beginEditCP(TutorialGraphics);


    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

    /******************************************************

        Create three Button Components (button1, button2,
        and button3) and their AbsoluteLayoutConstraints.

        AbsoluteLayoutConstraints are used within the 
        AbsoluteLayout to define where the Components will
        be placed.  Most other Layouts do not need 
        Constraints, as they place things within the Layout
        automatically.

    ******************************************************/

    ButtonPtr button1 = osg::Button::create();
    ButtonPtr button2 = osg::Button::create();
    ButtonPtr button3 = osg::Button::create();
    
    AbsoluteLayoutConstraintsPtr buttonConstraints1 = osg::AbsoluteLayoutConstraints::create();
    AbsoluteLayoutConstraintsPtr buttonConstraints2 = osg::AbsoluteLayoutConstraints::create();
    AbsoluteLayoutConstraintsPtr buttonConstraints3 = osg::AbsoluteLayoutConstraints::create();

    /******************************************************

        Define the AbsoluteLayoutConstraints (where Buttons 
        are located in the Layout).  setPosition gives you 
        the location of the Button relative to the Layout
        Manager's upper left hand corner.  Buttons will
        not display if their AbsoluteLayoutConstraints 
        place them outside the Frame in which they are to
        be rendered (the part within the Frame still does
        display).  Changing the window size shows an 
        example of this.

    ******************************************************/
  
   beginEditCP(buttonConstraints1, AbsoluteLayoutConstraints::PositionFieldMask);
        buttonConstraints1->setPosition(Pnt2s(0,150));
   endEditCP(buttonConstraints1, AbsoluteLayoutConstraints::PositionFieldMask);

   beginEditCP(buttonConstraints2, AbsoluteLayoutConstraints::PositionFieldMask);
        buttonConstraints2->setPosition(Pnt2s(200,200));
   endEditCP(buttonConstraints2, AbsoluteLayoutConstraints::PositionFieldMask);
    
   // Note that this will cause the button's position to overlap with Button2
   // when the program is run; the AbsoluteLayoutConstraints will overlap
   // if the specified coordinates overlap
   beginEditCP(buttonConstraints3, AbsoluteLayoutConstraints::PositionFieldMask);
        buttonConstraints3->setPosition(Pnt2s(150,220));
   endEditCP(buttonConstraints3, AbsoluteLayoutConstraints::PositionFieldMask);

    /******************************************************

        Edit Button Components and assign Text,
        PreferredSize, and AbsoluteLayoutConstraints

    ******************************************************/

    // Create a simple Font to be used with the Button
    UIFontPtr sampleFont = osg::UIFont::create();
    beginEditCP(sampleFont, UIFont::SizeFieldMask | UIFont::FamilyFieldMask | UIFont::GapFieldMask | UIFont::GlyphPixelSizeFieldMask | UIFont::TextureWidthFieldMask | UIFont::StyleFieldMask);
        sampleFont->setFamily("SANS");
        sampleFont->setGap(1);
        sampleFont->setGlyphPixelSize(46);
        sampleFont->setSize(16);
        //sampleFont->setTextureWidth(0);
        sampleFont->setStyle(TextFace::STYLE_PLAIN);
    endEditCP(sampleFont, UIFont::SizeFieldMask | UIFont::FamilyFieldMask | UIFont::GapFieldMask | UIFont::GlyphPixelSizeFieldMask | UIFont::TextureWidthFieldMask | UIFont::StyleFieldMask);

    ColorUIBackgroundPtr button1Background = ColorUIBackground::create();
    beginEditCP(button1Background);
    button1Background->setColor(Color4f(1.0,0.0,0.0,1.0));
    endEditCP(button1Background);
   beginEditCP(button1, Button::PreferredSizeFieldMask |  Button::SizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);
        button1->setPreferredSize(Vec2s(100,50));
        button1->setSize(Vec2s(100,50));
        button1->setText("Button 1");
        button1->setBackground(button1Background);
        button1->setTextColor(Color4f(0.0,0.0,0.0,1.0));
        
        // Set the constraints created above to button
        // to place the Button within the scene
        button1->setConstraints(buttonConstraints1);
        button1->setFont(sampleFont);
    endEditCP(button1, Button::PreferredSizeFieldMask | Button::SizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);

    beginEditCP(button2, Button::PreferredSizeFieldMask |  Button::SizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);
        button2->setPreferredSize(Vec2s(100,50));
        button2->setSize(Vec2s(100,50));
        button2->setText("Button 2");
        
        // Set the constraints created above to button2
        // to place the Button within the scene
        button2->setConstraints(buttonConstraints2);
        button2->setFont(sampleFont);
    endEditCP(button2, Button::PreferredSizeFieldMask | Button::SizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);

    beginEditCP(button3,  Button::PreferredSizeFieldMask | Button::SizeFieldMask | Button::ConstraintsFieldMask);
        button3->setPreferredSize(Vec2s(100,50));
        button3->setSize(Vec2s(100,50));
        button3->setText("Button 3");
        
        // Set the constraints created above to button3
        // to place the Button within the scene
        button3->setConstraints(buttonConstraints3);
        button3->setFont(sampleFont);
    endEditCP(button3,  Button::PreferredSizeFieldMask | Button::SizeFieldMask | Button::ConstraintsFieldMask);

    // Create The Main Frame
    // Create Background to be used with the Main Frame
    ColorUIBackgroundPtr MainFrameBackground = osg::ColorUIBackground::create();
    beginEditCP(MainFrameBackground, ColorUIBackground::ColorFieldMask);
        MainFrameBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainFrameBackground, ColorUIBackground::ColorFieldMask);
    
    LineBorderPtr MainFrameLineBorder = LineBorder::create();
    beginEditCP(MainFrameLineBorder);
    MainFrameLineBorder->setColor(Color4f(1.0,0.0,0.0,1.0));
    MainFrameLineBorder->setWidth(2);
    endEditCP(MainFrameLineBorder);

    FramePtr MainFrame = osg::Frame::create();
    LayoutPtr MainFrameLayout = osg::AbsoluteLayout::create();
    beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);
       MainFrame->getChildren().addValue(button1);
       MainFrame->getChildren().addValue(button3);
       MainFrame->getChildren().addValue(button2);
       MainFrame->setLayout(MainFrameLayout);
       MainFrame->setBackground(MainFrameBackground);
       MainFrame->setBorder(MainFrameLineBorder);
     
    endEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);

    // Create the Drawing Surface
    UIDrawingSurfacePtr TutorialDrawingSurface = UIDrawingSurface::create();
    beginEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask | UIDrawingSurface::EventProducerFieldMask);
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setRootFrame(MainFrame);
        TutorialDrawingSurface->setEventProducer(TutorialWindowEventProducer);
    endEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask | UIDrawingSurface::EventProducerFieldMask);
    
    //Make A 3D Rectangle to draw the UI on
    UIRectanglePtr UIRectCore = UIRectangle::create();
    beginEditCP(UIRectCore, UIRectangle::PointFieldMask | UIRectangle::WidthFieldMask | UIRectangle::HeightFieldMask | UIRectangle::DrawingSurfaceFieldMask);
        UIRectCore->setPoint(Pnt3f(-250.0,-250.0,370.0));
        UIRectCore->setWidth(500.0);
        UIRectCore->setHeight(500.0);
        UIRectCore->setDrawingSurface(TutorialDrawingSurface);
    endEditCP(UIRectCore, UIRectangle::PointFieldMask | UIRectangle::WidthFieldMask | UIRectangle::HeightFieldMask | UIRectangle::DrawingSurfaceFieldMask);
    
    NodePtr UIRectNode = osg::Node::create();
    beginEditCP(UIRectNode, Node::CoreFieldMask);
        UIRectNode->setCore(UIRectCore);
    endEditCP(UIRectNode, Node::CoreFieldMask);
    
    beginEditCP(scene, Node::ChildrenFieldMask);
        // add the UIRect as a child
        scene->addChild(UIRectNode);
    endEditCP(scene, Node::ChildrenFieldMask);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
    mgr->setRoot(scene);

    // Show the whole Scene
    mgr->showAll();

    TutorialWindowEventProducer->openWindow(Pnt2s(50,50),
                                        Vec2s(550,550),
                                        "OpenSG 20UIRectangle Window");

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