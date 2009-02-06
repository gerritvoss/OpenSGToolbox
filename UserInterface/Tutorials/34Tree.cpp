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
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

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
#include <OpenSG/UserInterface/OSGToggleButton.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

bool ExitApp = false;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// 34 Tree Headers
#include <OpenSG/UserInterface/OSGTree.h>
#include <OpenSG/UserInterface/OSGLayers.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGDefaultTreeModel.h>
#include <OpenSG/UserInterface/OSGFixedHeightTreeModelLayout.h>
#include <OpenSG/UserInterface/OSGDefaultMutableTreeNode.h>

#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGScrollPanel.h>

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

DefaultTreeModel TheTreeModel;
TreePtr TheTree;
ToggleButtonPtr SingleSelectionButton;
ToggleButtonPtr SingleIntervalSelectionButton;
ToggleButtonPtr MultipleIntervalSelectionButton;

class CreateNodeButtonActionListener : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
    {
        DefaultMutableTreeNodePtr NewNode = DefaultMutableTreeNode::create() ;
        NewNode->setUserObject(SharedFieldPtr(new SFString("New Node")));

        //TheTree->
        TheTreeModel.insertNodeInto(NewNode,MutableTreeNode::Ptr::dcast(TheTreeModel.getRootNode()),3);
    }
};

class RemoveNodeButtonActionListener : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
    {
        TheTreeModel.removeNodeFromParent(MutableTreeNode::Ptr::dcast(TheTreeModel.getRootNode()->getChildAt(0)));
    }
};

class SingleSelectionButtonSelectedListener : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
    {

        beginEditCP(SingleIntervalSelectionButton, ToggleButton::SelectedFieldMask);
            SingleIntervalSelectionButton->setSelected(false);
        endEditCP(SingleIntervalSelectionButton, ToggleButton::SelectedFieldMask);

        beginEditCP(MultipleIntervalSelectionButton, ToggleButton::SelectedFieldMask);
            MultipleIntervalSelectionButton->setSelected(false);
        endEditCP(MultipleIntervalSelectionButton, ToggleButton::SelectedFieldMask);

        TheTree->getSelectionModel()->setSelectionMode(TreeSelectionModel::SINGLE_TREE_SELECTION);
        
    }
      virtual void buttonDeselected(const ButtonSelectedEvent& e)
   {
   }

};

class SingleIntervalSelectionButtonSelectedListener : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
    {
        beginEditCP(SingleSelectionButton, ToggleButton::SelectedFieldMask);
            SingleSelectionButton->setSelected(false);
        endEditCP(SingleSelectionButton, ToggleButton::SelectedFieldMask);

        beginEditCP(MultipleIntervalSelectionButton, ToggleButton::SelectedFieldMask);
            MultipleIntervalSelectionButton->setSelected(false);
        endEditCP(MultipleIntervalSelectionButton, ToggleButton::SelectedFieldMask);

        TheTree->getSelectionModel()->setSelectionMode(TreeSelectionModel::CONTIGUOUS_TREE_SELECTION);
    }

   virtual void buttonDeselected(const ButtonSelectedEvent& e)
   {

   }
};

class MultipleIntervalSelectionButtonSelectedListener : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
    {    
        beginEditCP(SingleSelectionButton, ToggleButton::SelectedFieldMask);
            SingleSelectionButton->setSelected(false);
        endEditCP(SingleSelectionButton, ToggleButton::SelectedFieldMask);

        beginEditCP(SingleIntervalSelectionButton, ToggleButton::SelectedFieldMask);
            SingleIntervalSelectionButton->setSelected(false);
        endEditCP(SingleIntervalSelectionButton, ToggleButton::SelectedFieldMask);

        TheTree->getSelectionModel()->setSelectionMode(TreeSelectionModel::DISCONTIGUOUS_TREE_SELECTION);
    }

   virtual void buttonDeselected(const ButtonSelectedEvent& e)
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
    DefaultMutableTreeNodePtr JNode = DefaultMutableTreeNode::create() ;

    ANode->setUserObject(SharedFieldPtr(new SFString("A")));
    BNode->setUserObject(SharedFieldPtr(new SFString("B")));
    CNode->setUserObject(SharedFieldPtr(new SFString("C")));
    DNode->setUserObject(SharedFieldPtr(new SFString("D")));
    ENode->setUserObject(SharedFieldPtr(new SFString("E")));
    FNode->setUserObject(SharedFieldPtr(new SFString("F")));
    GNode->setUserObject(SharedFieldPtr(new SFString("G")));
    HNode->setUserObject(SharedFieldPtr(new SFString("H")));
    INode->setUserObject(SharedFieldPtr(new SFString("I")));
    JNode->setUserObject(SharedFieldPtr(new SFString("J")));

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

    //Tree Model
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

    
    //Create the Tree
    TheTree = Tree::create();

    beginEditCP(TheTree, Tree::PreferredSizeFieldMask);
        TheTree->setPreferredSize(Vec2f(100, 500));
    endEditCP(TheTree, Tree::PreferredSizeFieldMask);
    TheTree->setModel(&TheTreeModel);

    //Layout Expansion
    TheTree->expandPath(ANode->getTreePath());
    
    std::cout << "Row Count: " << TheTree->getRowCount() << std::endl;
    for(UInt32 i(0) ; i<TheTree->getRowCount() ; ++i)
    {
        TheTree->getPathForRow(i).getLastPathComponent()->getValueByStr(TempString);
        std::cout << TempString << " ";
    }
    std::cout << std::endl;

    TheTreeModel.insertNodeInto(JNode, ANode, ANode->getChildCount());
	TheTree->collapsePath(ANode->getTreePath());
    TheTree->expandPath(ANode->getTreePath());

    std::cout << "Row Count: " << TheTree->getRowCount() << std::endl;
    for(UInt32 i(0) ; i<TheTree->getRowCount() ; ++i)
    {
        TheTree->getPathForRow(i).getLastPathComponent()->getValueByStr(TempString);
        std::cout << TempString << " ";
    }
    std::cout << std::endl;

    TheTree->expandPath(BNode->getTreePath());
    std::cout << "Row Count: " << TheTree->getRowCount() << std::endl;
    for(UInt32 i(0) ; i<TheTree->getRowCount() ; ++i)
    {
        TheTree->getPathForRow(i).getLastPathComponent()->getValueByStr(TempString);
        std::cout << TempString << " ";
    }
    std::cout << std::endl;
    
    TheTree->expandPath(DNode->getTreePath());
    std::cout << "Row Count: " << TheTree->getRowCount() << std::endl;
    for(UInt32 i(0) ; i<TheTree->getRowCount() ; ++i)
    {
        TheTree->getPathForRow(i).getLastPathComponent()->getValueByStr(TempString);
        std::cout << TempString << " ";
    }
    std::cout << std::endl;


    // Create a ScrollPanel for easier viewing of the List (see 27ScrollPanel)
    ScrollPanelPtr ExampleScrollPanel = ScrollPanel::create();
    beginEditCP(ExampleScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        ExampleScrollPanel->setPreferredSize(Vec2s(200,300));
        //ExampleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //ExampleScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(ExampleScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    ExampleScrollPanel->setViewComponent(TheTree);

    /******************************************************

            Create and edit some ToggleButtons to
			allow for dynamically changing
			List selection options.           

    ******************************************************/
    SingleSelectionButton = ToggleButton::create();
    SingleIntervalSelectionButton = ToggleButton::create();
    MultipleIntervalSelectionButton = ToggleButton::create();

    beginEditCP(SingleSelectionButton, Button::TextFieldMask | Button::PreferredSizeFieldMask);
        SingleSelectionButton->setText("Single Selection");
        SingleSelectionButton->setPreferredSize(Vec2f(160, 50));
        SingleSelectionButton->setSelected(true);
    endEditCP(SingleSelectionButton, Button::TextFieldMask | Button::PreferredSizeFieldMask);
    SingleSelectionButtonSelectedListener TheSingleSelectionButtonSelectedListener;
    SingleSelectionButton->addButtonSelectedListener(&TheSingleSelectionButtonSelectedListener);
    
    beginEditCP(SingleIntervalSelectionButton, Button::TextFieldMask | Button::PreferredSizeFieldMask);
        SingleIntervalSelectionButton->setText("Single Interval Selection");
        SingleIntervalSelectionButton->setPreferredSize(Vec2f(160, 50));
    endEditCP(SingleIntervalSelectionButton, Button::TextFieldMask | Button::PreferredSizeFieldMask);
    SingleIntervalSelectionButtonSelectedListener TheSingleIntervalSelectionButtonSelectedListener;
    SingleIntervalSelectionButton->addButtonSelectedListener(&TheSingleIntervalSelectionButtonSelectedListener);
    
    beginEditCP(MultipleIntervalSelectionButton, Button::TextFieldMask | Button::PreferredSizeFieldMask);
        MultipleIntervalSelectionButton->setText("Multiple Interval Selection");
        MultipleIntervalSelectionButton->setPreferredSize(Vec2f(160, 50));
    endEditCP(MultipleIntervalSelectionButton, Button::TextFieldMask | Button::PreferredSizeFieldMask);
    MultipleIntervalSelectionButtonSelectedListener TheMultipleIntervalSelectionButtonSelectedListener;
    MultipleIntervalSelectionButton->addButtonSelectedListener(&TheMultipleIntervalSelectionButtonSelectedListener);

    //Create Node Button
    ButtonPtr CreateNodeButton = Button::create();

    beginEditCP(CreateNodeButton, Button::TextFieldMask);
        CreateNodeButton->setText("Create Node");
    endEditCP(CreateNodeButton, Button::TextFieldMask);
    CreateNodeButtonActionListener CreateNodeButtonListener;
    CreateNodeButton->addActionListener(&CreateNodeButtonListener);
    
    //Remove Node Button
    ButtonPtr RemoveNodeButton = Button::create();
    beginEditCP(RemoveNodeButton, Button::TextFieldMask);
        RemoveNodeButton->setText("Remove Node");
    endEditCP(RemoveNodeButton, Button::TextFieldMask);
    RemoveNodeButtonActionListener RemoveNodeButtonListener;
    RemoveNodeButton->addActionListener(&RemoveNodeButtonListener);
    
    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);

    LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().push_back(ExampleScrollPanel);
       MainInternalWindow->getChildren().push_back(SingleSelectionButton);
       MainInternalWindow->getChildren().push_back(SingleIntervalSelectionButton);
       MainInternalWindow->getChildren().push_back(MultipleIntervalSelectionButton);
       MainInternalWindow->getChildren().push_back(CreateNodeButton);
       MainInternalWindow->getChildren().push_back(RemoveNodeButton);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.85f,0.85f));
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
        TutorialViewport->getForegrounds().push_back(TutorialUIForeground);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);

    // Show the whole Scene
    mgr->showAll();

    TutorialWindowEventProducer->openWindow(Pnt2f(50,50),
                                        Vec2f(550,550),
                                        "OpenSG 34 Tree Window");

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
