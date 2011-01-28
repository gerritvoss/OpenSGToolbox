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

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

// 34 Tree Headers
#include "OSGTree.h"
#include "OSGLayers.h"
#include "OSGFlowLayout.h"
#include "OSGDefaultTreeModel.h"
#include "OSGFixedHeightTreeModelLayout.h"
#include "OSGDefaultMutableTreeNode.h"

#include "OSGButton.h"
#include "OSGScrollPanel.h"

void keyPressed(KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_Q &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
}

void handleCreateNodeButtonAction(ActionEventDetails* const details,
                                  Tree* const ExampleTree,
                                  DefaultTreeModel* const ExampleTreeModel)
{
    static char NodeName('K');

    DefaultMutableTreeNodeRecPtr NewNode = DefaultMutableTreeNode::create() ;

    std::ostringstream outStream;
    outStream << NodeName;
    NewNode->setUserObject(boost::any(outStream.str()));
    NodeName = static_cast<char>(static_cast<unsigned int>(NodeName) + 1);

    ModelTreeNodeRecPtr SelectedNode(ExampleTreeModel->getNodeForPath(ExampleTree->getSelectionPath()));

    if(SelectedNode != NULL)
    {
        ExampleTreeModel->insertNodeInto(NewNode,dynamic_pointer_cast<MutableTreeNode>(SelectedNode),0);
    }
}

void handleRemoveNodeButtonAction(ActionEventDetails* const details,
                                  Tree* const ExampleTree,
                                  DefaultTreeModel* const ExampleTreeModel)
{
    ModelTreeNodeRecPtr SelectedNode(ExampleTreeModel->getNodeForPath(ExampleTree->getSelectionPath()));

    if(SelectedNode != NULL)
    {
        ExampleTreeModel->removeNodeFromParent(dynamic_pointer_cast<MutableTreeNode>(SelectedNode));
    }
}

void handleSingleSelectionButtonSelected(ButtonSelectedEventDetails* const details,
                                         Tree* const ExampleTree,
                                         ToggleButton* const SingleIntervalSelectionButton,
                                         ToggleButton* const MultipleIntervalSelectionButton)
{

    SingleIntervalSelectionButton->setSelected(false);

    MultipleIntervalSelectionButton->setSelected(false);

    ExampleTree->getSelectionModel()->setSelectionMode(TreeSelectionModel::SINGLE_TREE_SELECTION);

}

void handleSingleIntervalSelectionButtonSelected(ButtonSelectedEventDetails* const details,
                                                 Tree* const ExampleTree,
                                                 ToggleButton* const SingleSelectionButton,
                                                 ToggleButton* const MultipleIntervalSelectionButton)
{
    SingleSelectionButton->setSelected(false);

    MultipleIntervalSelectionButton->setSelected(false);

    ExampleTree->getSelectionModel()->setSelectionMode(TreeSelectionModel::CONTIGUOUS_TREE_SELECTION);
}


void handleMultipleIntervalSelectionButtonSelected(ButtonSelectedEventDetails* const details,
                                                   Tree* const ExampleTree,
                                                   ToggleButton* const SingleSelectionButton,
                                                   ToggleButton* const SingleIntervalSelectionButton)
{    
    SingleSelectionButton->setSelected(false);

    SingleIntervalSelectionButton->setSelected(false);

    ExampleTree->getSelectionModel()->setSelectionMode(TreeSelectionModel::DISCONTIGUOUS_TREE_SELECTION);
}

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    {
        // Set up Window
        WindowEventProducerRecPtr TutorialWindow = createNativeWindow();
        TutorialWindow->initWindow();

        // Create the SimpleSceneManager helper
        SimpleSceneManager sceneManager;
        TutorialWindow->setDisplayCallback(boost::bind(display, &sceneManager));
        TutorialWindow->setReshapeCallback(boost::bind(reshape, _1, &sceneManager));

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

        TutorialWindow->connectKeyTyped(boost::bind(keyPressed, _1));

        // Make Torus Node (creates Torus in background of scene)
        NodeRecPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

        // Make Main Scene Node and add the Torus
        NodeRecPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(TorusGeometryNode);

        // Create the Graphics
        GraphicsRecPtr TutorialGraphics = Graphics2D::create();

        // Initialize the LookAndFeelManager to enable default settings
        LookAndFeelManager::the()->getLookAndFeel()->init();

        DefaultMutableTreeNodeRecPtr ANode = DefaultMutableTreeNode::create() ;
        DefaultMutableTreeNodeRecPtr BNode = DefaultMutableTreeNode::create() ;
        DefaultMutableTreeNodeRecPtr CNode = DefaultMutableTreeNode::create() ;
        DefaultMutableTreeNodeRecPtr DNode = DefaultMutableTreeNode::create() ;
        DefaultMutableTreeNodeRecPtr ENode = DefaultMutableTreeNode::create() ;
        DefaultMutableTreeNodeRecPtr FNode = DefaultMutableTreeNode::create() ;
        DefaultMutableTreeNodeRecPtr GNode = DefaultMutableTreeNode::create() ;
        DefaultMutableTreeNodeRecPtr HNode = DefaultMutableTreeNode::create() ;
        DefaultMutableTreeNodeRecPtr INode = DefaultMutableTreeNode::create() ;
        DefaultMutableTreeNodeRecPtr JNode = DefaultMutableTreeNode::create() ;

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

          std::vector<DefaultMutableTreeNodeRecPtr> TreePreorderSequence;
          ANode->preorder(TreePreorderSequence);
          std::cout << "Preorder Sequence: ";
          for(UInt32 i(0) ; i<TreePreorderSequence.size() ; ++i)
          {
          TreePreorderSequence[i]->getUserObject()->getValueByStr(TempString);
          std::cout << TempString << ", ";
          }
          std::cout << std::endl;

          std::vector<DefaultMutableTreeNodeRecPtr> TreePostorderSequence;
          ANode->postorder(TreePostorderSequence);
          std::cout << "Postorder Sequence: ";
          for(UInt32 i(0) ; i<TreePostorderSequence.size() ; ++i)
          {
          TreePostorderSequence[i]->getUserObject()->getValueByStr(TempString);
          std::cout << TempString << ", ";
          }
          std::cout << std::endl;

          std::vector<DefaultMutableTreeNodeRecPtr> BreadthFirstSequence;
          ANode->breadthFirst(BreadthFirstSequence);
          std::cout << "Breadth First Sequence: ";
          for(UInt32 i(0) ; i<BreadthFirstSequence.size() ; ++i)
          {
          BreadthFirstSequence[i]->getUserObject()->getValueByStr(TempString);
          std::cout << TempString << ", ";
          }
          std::cout << std::endl;*/

        //Tree Model
        DefaultTreeModelRecPtr ExampleTreeModel = DefaultTreeModel::create();
        ExampleTreeModel->setRoot(ANode);
        ExampleTreeModel->setAskAllowsChildren(false);

        //Create the Tree
        TreeRecPtr ExampleTree = Tree::create();

        ExampleTree->setPreferredSize(Vec2f(100, 500));
        ExampleTree->setModel(ExampleTreeModel);

        //Layout Expansion
        ExampleTree->expandPath(ExampleTreeModel->getRootPath());

        // Create a ScrollPanel for easier viewing of the List (see 27ScrollPanel)
        ScrollPanelRecPtr ExampleScrollPanel = ScrollPanel::create();
        ExampleScrollPanel->setPreferredSize(Vec2f(200,300));
        //ExampleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //ExampleScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        ExampleScrollPanel->setViewComponent(ExampleTree);

        /******************************************************

          Create and edit some ToggleButtons to
          allow for dynamically changing
          List selection options.           

         ******************************************************/
        ToggleButtonRecPtr SingleSelectionButton = ToggleButton::create();
        ToggleButtonRecPtr SingleIntervalSelectionButton = ToggleButton::create();
        ToggleButtonRecPtr MultipleIntervalSelectionButton = ToggleButton::create();

        SingleSelectionButton->setText("Single Selection");
        SingleSelectionButton->setPreferredSize(Vec2f(160, 50));
        SingleSelectionButton->setSelected(true);
        SingleSelectionButton->connectButtonSelected(boost::bind(handleSingleSelectionButtonSelected,
                                                                 _1,
                                                                 ExampleTree.get(),
                                                                 SingleIntervalSelectionButton.get(),
                                                                 MultipleIntervalSelectionButton.get()));

        SingleIntervalSelectionButton->setText("Single Interval Selection");
        SingleIntervalSelectionButton->setPreferredSize(Vec2f(160, 50));
        SingleIntervalSelectionButton->connectButtonSelected(boost::bind(handleSingleIntervalSelectionButtonSelected,
                                                                         _1,
                                                                         ExampleTree.get(),
                                                                         SingleSelectionButton.get(),
                                                                         MultipleIntervalSelectionButton.get()));

        MultipleIntervalSelectionButton->setText("Multiple Interval Selection");
        MultipleIntervalSelectionButton->setPreferredSize(Vec2f(160, 50));
        MultipleIntervalSelectionButton->connectButtonSelected(boost::bind(handleMultipleIntervalSelectionButtonSelected,
                                                                           _1,
                                                                           ExampleTree.get(),
                                                                           SingleSelectionButton.get(),
                                                                           SingleIntervalSelectionButton.get()));

        //Create Node Button
        ButtonRecPtr CreateNodeButton = Button::create();

        CreateNodeButton->setText("Create Node");
        CreateNodeButton->connectActionPerformed(boost::bind(handleCreateNodeButtonAction,
                                                             _1,
                                                             ExampleTree.get(),
                                                             ExampleTreeModel.get()));

        //Remove Node Button
        ButtonRecPtr RemoveNodeButton = Button::create();
        RemoveNodeButton->setText("Remove Node");
        RemoveNodeButton->connectActionPerformed(boost::bind(handleRemoveNodeButtonAction,
                                                             _1,
                                                             ExampleTree.get(),
                                                             ExampleTreeModel.get()));

        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        LayoutRecPtr MainInternalWindowLayout = FlowLayout::create();

        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
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
        UIDrawingSurfaceRecPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);

        TutorialDrawingSurface->openWindow(MainInternalWindow);

        // Create the UI Foreground Object
        UIForegroundRecPtr TutorialUIForeground = UIForeground::create();

        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);


        // Tell the Manager what to manage
        sceneManager.setRoot(scene);

        // Add the UI Foreground Object to the Scene
        ViewportRecPtr TutorialViewport = sceneManager.getWindow()->getPort(0);
        TutorialViewport->addForeground(TutorialUIForeground);

        // Show the whole Scene
        sceneManager.showAll();


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "34Tree");

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}


// Callback functions


// Redraw the window
void display(SimpleSceneManager *mgr)
{
    mgr->redraw();
}

// React to size changes
void reshape(Vec2f Size, SimpleSceneManager *mgr)
{
    mgr->resize(Size.x(), Size.y());
}
