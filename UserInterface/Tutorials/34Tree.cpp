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

// 34 Tree Headers
#include <OpenSG/UserInterface/OSGDefaultTreeModel.h>
#include <OpenSG/UserInterface/OSGDefaultMutableTreeNode.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGUIBackgrounds.h>

// Create a class to allow for the use of the Escape
// key to exit
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

    DefaultMutableTreeNodePtr ANode = DefaultMutableTreeNode::create() ;
    DefaultMutableTreeNodePtr BNode = DefaultMutableTreeNode::create() ;
    DefaultMutableTreeNodePtr CNode = DefaultMutableTreeNode::create() ;
    DefaultMutableTreeNodePtr DNode = DefaultMutableTreeNode::create() ;
    DefaultMutableTreeNodePtr ENode = DefaultMutableTreeNode::create() ;
    DefaultMutableTreeNodePtr FNode = DefaultMutableTreeNode::create() ;
    DefaultMutableTreeNodePtr GNode = DefaultMutableTreeNode::create() ;
    DefaultMutableTreeNodePtr HNode = DefaultMutableTreeNode::create() ;
    DefaultMutableTreeNodePtr INode = DefaultMutableTreeNode::create() ;

    ANode->setUserObject(SharedFieldPtr(new SFString("A")));
    BNode->setUserObject(SharedFieldPtr(new SFString("B")));
    CNode->setUserObject(SharedFieldPtr(new SFString("C")));
    DNode->setUserObject(SharedFieldPtr(new SFString("D")));
    ENode->setUserObject(SharedFieldPtr(new SFString("E")));
    FNode->setUserObject(SharedFieldPtr(new SFString("F")));
    GNode->setUserObject(SharedFieldPtr(new SFString("G")));
    HNode->setUserObject(SharedFieldPtr(new SFString("H")));
    INode->setUserObject(SharedFieldPtr(new SFString("I")));

    //A
    beginEditCP(ANode, DefaultMutableTreeNode::ChildrenInternalFieldMask);
        ANode->getChildrenInternal().addValue(BNode);
        ANode->getChildrenInternal().addValue(CNode);
    endEditCP(ANode, DefaultMutableTreeNode::ChildrenInternalFieldMask);
    
    //B
    beginEditCP(ANode, DefaultMutableTreeNode::ChildrenInternalFieldMask);
        BNode->getChildrenInternal().addValue(DNode);
        BNode->getChildrenInternal().addValue(ENode);
    endEditCP(ANode, DefaultMutableTreeNode::ChildrenInternalFieldMask);
    
    //C
    beginEditCP(ANode, DefaultMutableTreeNode::ChildrenInternalFieldMask);
        CNode->getChildrenInternal().addValue(FNode);
        CNode->getChildrenInternal().addValue(GNode);
    endEditCP(ANode, DefaultMutableTreeNode::ChildrenInternalFieldMask);
    
    //D
    beginEditCP(ANode, DefaultMutableTreeNode::ChildrenInternalFieldMask);
        DNode->getChildrenInternal().addValue(HNode);
        DNode->getChildrenInternal().addValue(INode);
    endEditCP(ANode, DefaultMutableTreeNode::ChildrenInternalFieldMask);

    DefaultTreeModel TheTreeModel;
    TheTreeModel.setRoot(ANode);

    std::string TempString;

    std::vector<DefaultMutableTreeNodePtr> TreePreorderSequence;
    ANode->preorder(TreePreorderSequence);
    std::cout << "Preorder Sequence: ";
    for(UInt32 i(0) ; i<TreePreorderSequence.size() ; ++i)
    {
        TreePreorderSequence[i]->getUserObject()->getValueByStr(TempString);
        std::cout << TempString << ", ";
    }
    std::cout << std::endl;
    
    std::vector<DefaultMutableTreeNodePtr> TreePostorderSequence;
    ANode->postorder(TreePostorderSequence);
    std::cout << "Postorder Sequence: ";
    for(UInt32 i(0) ; i<TreePostorderSequence.size() ; ++i)
    {
        TreePostorderSequence[i]->getUserObject()->getValueByStr(TempString);
        std::cout << TempString << ", ";
    }
    std::cout << std::endl;
    
    std::vector<DefaultMutableTreeNodePtr> BreadthFirstSequence;
    ANode->breadthFirst(BreadthFirstSequence);
    std::cout << "Breadth First Sequence: ";
    for(UInt32 i(0) ; i<BreadthFirstSequence.size() ; ++i)
    {
        BreadthFirstSequence[i]->getUserObject()->getValueByStr(TempString);
        std::cout << TempString << ", ";
    }
    std::cout << std::endl;

    // Create Background to be used with the MainFrame
    ColorUIBackgroundPtr MainFrameBackground = osg::ColorUIBackground::create();
    beginEditCP(MainFrameBackground, ColorUIBackground::ColorFieldMask);
        MainFrameBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainFrameBackground, ColorUIBackground::ColorFieldMask);

    // Create The Main Frame
    FramePtr MainFrame = osg::Frame::create();
    LayoutPtr MainFrameLayout = osg::FlowLayout::create();
    beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);
       // Assign the Button to the MainFrame so it will be displayed
       // when the view is rendered.
       MainFrame->setLayout(MainFrameLayout);
       MainFrame->setBackground(MainFrameBackground);
    endEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);

    TutorialKeyListener TheKeyListener;
    MainFrame->addKeyListener(&TheKeyListener);

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
                                        "OpenSG 01Button Window");

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
