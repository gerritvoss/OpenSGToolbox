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
#include "OSGToggleButton.h"

#include <sstream>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// 34 Tree Headers
#include "OSGTree.h"
#include "OSGLayers.h"
#include "OSGFlowLayout.h"
#include "OSGDefaultTreeModel.h"
#include "OSGFixedHeightTreeModelLayout.h"
#include "OSGDefaultMutableTreeNode.h"

#include "OSGButton.h"
#include "OSGScrollPanel.h"

// Create a class to allow for the use of the Escape
// key to exit
class TutorialKeyListener : public KeyListener
{
  public:

    virtual void keyPressed(const KeyEventUnrecPtr e)
    {
        if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
        {
            TutorialWindow->closeWindow();
        }
    }

    virtual void keyReleased(const KeyEventUnrecPtr e)
    {
    }

    virtual void keyTyped(const KeyEventUnrecPtr e)
    {
    }
};

DefaultTreeModelRefPtr TheTreeModel;
TreeRefPtr TheTree;
ToggleButtonRefPtr SingleSelectionButton;
ToggleButtonRefPtr SingleIntervalSelectionButton;
ToggleButtonRefPtr MultipleIntervalSelectionButton;

class CreateNodeButtonActionListener : public ActionListener
{
  public:

    virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
        static char NodeName('K');

        DefaultMutableTreeNodeRefPtr NewNode = DefaultMutableTreeNode::create() ;

        std::ostringstream outStream;
        outStream << NodeName;
        NewNode->setUserObject(boost::any(outStream.str()));
        NodeName = static_cast<char>(static_cast<unsigned int>(NodeName) + 1);

        ModelTreeNodeRefPtr SelectedNode(TheTreeModel->getNodeForPath(TheTree->getSelectionPath()));

        if(SelectedNode != NULL)
        {
            TheTreeModel->insertNodeInto(NewNode,dynamic_pointer_cast<MutableTreeNode>(SelectedNode),0);
        }
    }
};

class RemoveNodeButtonActionListener : public ActionListener
{
  public:

    virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
        ModelTreeNodeRefPtr SelectedNode(TheTreeModel->getNodeForPath(TheTree->getSelectionPath()));

        if(SelectedNode != NULL)
        {
            TheTreeModel->removeNodeFromParent(dynamic_pointer_cast<MutableTreeNode>(SelectedNode));
        }
    }
};

class SingleSelectionButtonSelectedListener : public ButtonSelectedListener
{
  public:

    virtual void buttonSelected(const ButtonSelectedEventUnrecPtr e)
    {

        SingleIntervalSelectionButton->setSelected(false);

        MultipleIntervalSelectionButton->setSelected(false);

        TheTree->getSelectionModel()->setSelectionMode(TreeSelectionModel::SINGLE_TREE_SELECTION);

    }
    virtual void buttonDeselected(const ButtonSelectedEventUnrecPtr e)
    {
    }

};

class SingleIntervalSelectionButtonSelectedListener : public ButtonSelectedListener
{
  public:

    virtual void buttonSelected(const ButtonSelectedEventUnrecPtr e)
    {
        SingleSelectionButton->setSelected(false);

        MultipleIntervalSelectionButton->setSelected(false);

        TheTree->getSelectionModel()->setSelectionMode(TreeSelectionModel::CONTIGUOUS_TREE_SELECTION);
    }

    virtual void buttonDeselected(const ButtonSelectedEventUnrecPtr e)
    {

    }
};

class MultipleIntervalSelectionButtonSelectedListener : public ButtonSelectedListener
{
  public:

    virtual void buttonSelected(const ButtonSelectedEventUnrecPtr e)
    {    
        SingleSelectionButton->setSelected(false);

        SingleIntervalSelectionButton->setSelected(false);

        TheTree->getSelectionModel()->setSelectionMode(TreeSelectionModel::DISCONTIGUOUS_TREE_SELECTION);
    }

    virtual void buttonDeselected(const ButtonSelectedEventUnrecPtr e)
    {
    }

};
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindow = createNativeWindow();
    TutorialWindow->initWindow();

    TutorialWindow->setDisplayCallback(display);
    TutorialWindow->setReshapeCallback(reshape);

    TutorialKeyListener TheKeyListener;
    TutorialWindow->addKeyListener(&TheKeyListener);

    // Make Torus Node (creates Torus in background of scene)
    NodeRefPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Main Scene Node and add the Torus
    NodeRefPtr scene = OSG::Node::create();
    scene->setCore(OSG::Group::create());
    scene->addChild(TorusGeometryNode);

    // Create the Graphics
    GraphicsRefPtr TutorialGraphics = OSG::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();


    DefaultMutableTreeNodeRefPtr ANode = DefaultMutableTreeNode::create() ;
    DefaultMutableTreeNodeRefPtr BNode = DefaultMutableTreeNode::create() ;
    DefaultMutableTreeNodeRefPtr CNode = DefaultMutableTreeNode::create() ;
    DefaultMutableTreeNodeRefPtr DNode = DefaultMutableTreeNode::create() ;
    DefaultMutableTreeNodeRefPtr ENode = DefaultMutableTreeNode::create() ;
    DefaultMutableTreeNodeRefPtr FNode = DefaultMutableTreeNode::create() ;
    DefaultMutableTreeNodeRefPtr GNode = DefaultMutableTreeNode::create() ;
    DefaultMutableTreeNodeRefPtr HNode = DefaultMutableTreeNode::create() ;
    DefaultMutableTreeNodeRefPtr INode = DefaultMutableTreeNode::create() ;
    DefaultMutableTreeNodeRefPtr JNode = DefaultMutableTreeNode::create() ;

    ANode->setUserObject(boost::any(std::string("A")));
    BNode->setUserObject(boost::any(std::string("B")));
    CNode->setUserObject(boost::any(std::string("C")));
    DNode->setUserObject(boost::any(std::string("D")));
    ENode->setUserObject(boost::any(std::string("E")));
    FNode->setUserObject(boost::any(std::string("F")));
    GNode->setUserObject(boost::any(std::string("G")));
    HNode->setUserObject(boost::any(std::string("H")));
    INode->setUserObject(boost::any(std::string("I")));
    JNode->setUserObject(boost::any(std::string("J")));

    //A
    ANode->insert(BNode);
    ANode->insert(CNode);

    //B
    BNode->insert(DNode);
    BNode->insert(ENode);

    //C
    CNode->insert(FNode);
    CNode->insert(GNode);

    //D
    DNode->insert(HNode);
    DNode->insert(INode);


    /*std::string TempString;

      std::vector<DefaultMutableTreeNodeRefPtr> TreePreorderSequence;
      ANode->preorder(TreePreorderSequence);
      std::cout << "Preorder Sequence: ";
      for(UInt32 i(0) ; i<TreePreorderSequence.size() ; ++i)
      {
      TreePreorderSequence[i]->getUserObject()->getValueByStr(TempString);
      std::cout << TempString << ", ";
      }
      std::cout << std::endl;

      std::vector<DefaultMutableTreeNodeRefPtr> TreePostorderSequence;
      ANode->postorder(TreePostorderSequence);
      std::cout << "Postorder Sequence: ";
      for(UInt32 i(0) ; i<TreePostorderSequence.size() ; ++i)
      {
      TreePostorderSequence[i]->getUserObject()->getValueByStr(TempString);
      std::cout << TempString << ", ";
      }
      std::cout << std::endl;

      std::vector<DefaultMutableTreeNodeRefPtr> BreadthFirstSequence;
      ANode->breadthFirst(BreadthFirstSequence);
      std::cout << "Breadth First Sequence: ";
      for(UInt32 i(0) ; i<BreadthFirstSequence.size() ; ++i)
      {
      BreadthFirstSequence[i]->getUserObject()->getValueByStr(TempString);
      std::cout << TempString << ", ";
      }
      std::cout << std::endl;*/

    //Tree Model
    TheTreeModel = DefaultTreeModel::create();
    TheTreeModel->setRoot(ANode);
    TheTreeModel->setAskAllowsChildren(false);

    //Create the Tree
    TheTree = Tree::create();

    TheTree->setPreferredSize(Vec2f(100, 500));
    TheTree->setModel(TheTreeModel);

    //Layout Expansion
    TheTree->expandPath(TheTreeModel->getRootPath());

    // Create a ScrollPanel for easier viewing of the List (see 27ScrollPanel)
    ScrollPanelRefPtr ExampleScrollPanel = ScrollPanel::create();
    ExampleScrollPanel->setPreferredSize(Vec2f(200,300));
    //ExampleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    //ExampleScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    ExampleScrollPanel->setViewComponent(TheTree);

    /******************************************************

      Create and edit some ToggleButtons to
      allow for dynamically changing
      List selection options.           

     ******************************************************/
    SingleSelectionButton = ToggleButton::create();
    SingleIntervalSelectionButton = ToggleButton::create();
    MultipleIntervalSelectionButton = ToggleButton::create();

    SingleSelectionButton->setText("Single Selection");
    SingleSelectionButton->setPreferredSize(Vec2f(160, 50));
    SingleSelectionButton->setSelected(true);
    SingleSelectionButtonSelectedListener TheSingleSelectionButtonSelectedListener;
    SingleSelectionButton->addButtonSelectedListener(&TheSingleSelectionButtonSelectedListener);

    SingleIntervalSelectionButton->setText("Single Interval Selection");
    SingleIntervalSelectionButton->setPreferredSize(Vec2f(160, 50));
    SingleIntervalSelectionButtonSelectedListener TheSingleIntervalSelectionButtonSelectedListener;
    SingleIntervalSelectionButton->addButtonSelectedListener(&TheSingleIntervalSelectionButtonSelectedListener);

    MultipleIntervalSelectionButton->setText("Multiple Interval Selection");
    MultipleIntervalSelectionButton->setPreferredSize(Vec2f(160, 50));
    MultipleIntervalSelectionButtonSelectedListener TheMultipleIntervalSelectionButtonSelectedListener;
    MultipleIntervalSelectionButton->addButtonSelectedListener(&TheMultipleIntervalSelectionButtonSelectedListener);

    //Create Node Button
    ButtonRefPtr CreateNodeButton = Button::create();

    CreateNodeButton->setText("Create Node");
    CreateNodeButtonActionListener CreateNodeButtonListener;
    CreateNodeButton->addActionListener(&CreateNodeButtonListener);

    //Remove Node Button
    ButtonRefPtr RemoveNodeButton = Button::create();
    RemoveNodeButton->setText("Remove Node");
    RemoveNodeButtonActionListener RemoveNodeButtonListener;
    RemoveNodeButton->addActionListener(&RemoveNodeButtonListener);

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
    MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    LayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
    MainInternalWindow->pushToChildren(ExampleScrollPanel);
    MainInternalWindow->pushToChildren(SingleSelectionButton);
    MainInternalWindow->pushToChildren(SingleIntervalSelectionButton);
    MainInternalWindow->pushToChildren(MultipleIntervalSelectionButton);
    MainInternalWindow->pushToChildren(CreateNodeButton);
    MainInternalWindow->pushToChildren(RemoveNodeButton);
    MainInternalWindow->setLayout(MainInternalWindowLayout);
    MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
    MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
    MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.85f,0.85f));
    MainInternalWindow->setDrawTitlebar(false);
    MainInternalWindow->setResizable(false);

    // Create the Drawing Surface
    UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
    TutorialDrawingSurface->setGraphics(TutorialGraphics);
    TutorialDrawingSurface->setEventProducer(TutorialWindow);

    TutorialDrawingSurface->openWindow(MainInternalWindow);

    // Create the UI Foreground Object
    UIForegroundRefPtr TutorialUIForeground = OSG::UIForeground::create();

    TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindow);
    mgr->setRoot(scene);

    // Add the UI Foreground Object to the Scene
    ViewportRefPtr TutorialViewport = mgr->getWindow()->getPort(0);
    TutorialViewport->addForeground(TutorialUIForeground);

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
                               WinSize,
                               "34Tree");

    //Enter main Loop
    TutorialWindow->mainLoop();

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
