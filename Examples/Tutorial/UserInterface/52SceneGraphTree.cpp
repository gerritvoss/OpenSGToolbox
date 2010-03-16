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

// A little helper to simplify Root management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"

// The general Root file loading handler
#include "OSGSceneFileHandler.h"

// Input
#include "OSGWindowUtils.h"

// UserInterface Headers
#include "OSGUIForeground.h"
#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"
#include "OSGGraphics2D.h"
#include "OSGLookAndFeelManager.h"
#include "OSGPanel.h"
#include "OSGLabel.h"
#include "OSGTreeSelectionListener.h"
//#include "OSGGeometryUtils.h"

#include <sstream>
#include <boost/lexical_cast.hpp>

//Tree Headers
#include "OSGTree.h"
#include "OSGLayers.h"
#include "OSGFlowLayout.h"
#include "OSGBorderLayout.h"
#include "OSGBorderLayoutConstraints.h"
#include "OSGSceneGraphTreeModel.h"
#include "OSGFileSystemTreeModel.h"
#include "OSGFixedHeightTreeModelLayout.h"
#include "OSGGridLayout.h"

#include "OSGScrollPanel.h"
#include "OSGNameAttachment.h"
#include "OSGSceneFileHandler.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

SceneGraphTreeModelRefPtr TheTreeModel;
FileSystemTreeModelRefPtr TheFileSystemTreeModel;
TreeRefPtr TheTree;
NodeRefPtr SelectedNode = NULL;

LabelRefPtr NodeNameValueLabel;
LabelRefPtr NodeCoreTypeValueLabel;
LabelRefPtr NodeMinValueLabel;
LabelRefPtr NodeMaxValueLabel;
LabelRefPtr NodeCenterValueLabel;
LabelRefPtr NodeTriCountValueLabel;
LabelRefPtr NodeTravMaskValueLabel;
LabelRefPtr NodeOcclusionMaskValueLabel;
LabelRefPtr NodeActiveValueLabel;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);
void selectedNodeChanged(void);


// Create a class to allow for the use of the Escape
// key to exit
class TutorialKeyListener : public KeyListener
{
  public:

    virtual void keyPressed(const KeyEventUnrecPtr e)
    {
        if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
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

class TutorialTreeSelectionListener : public TreeSelectionListener
{
  public:
    //Called whenever elements are added to the selection
    virtual void selectionAdded(const TreeSelectionEventUnrecPtr e)
    {
        //Get the selected Node
        try
        {
            SelectedNode = boost::any_cast<NodeRefPtr>(TheTree->getLastSelectedPathComponent());
        }
        catch (boost::bad_any_cast &)
        {
            SelectedNode = NULL;
        }
        selectedNodeChanged();
    }

    //Called whenever elements are removed to the selection
    virtual void selectionRemoved(const TreeSelectionEventUnrecPtr e)
    {
        SelectedNode = NULL;
        selectedNodeChanged();
    }
};

void selectedNodeChanged(void)
{
    mgr->setHighlight(SelectedNode);


    //Update Details Panel
    if(SelectedNode == NULL)
    {
        NodeNameValueLabel->setText("");

        NodeCoreTypeValueLabel->setText("");

        NodeMinValueLabel->setText("");

        NodeMaxValueLabel->setText("");

        NodeCenterValueLabel->setText("");

        NodeTriCountValueLabel->setText("");

        NodeTravMaskValueLabel->setText("");

        NodeOcclusionMaskValueLabel->setText("");

        NodeActiveValueLabel->setText("");

    }
    else
    {
        const Char8 *NodeName = getName(SelectedNode);
        if(NodeName == NULL)
        {
            NodeNameValueLabel->setText("Unnamed Node");
        }
        else
        {
            NodeNameValueLabel->setText(NodeName);
        }

        NodeCoreTypeValueLabel->setText(SelectedNode->getCore()->getType().getCName());

        BoxVolume DyVol;
        SelectedNode->getWorldVolume(DyVol);
        Pnt3f Min,Max,Center;
        DyVol.getBounds(Min,Max);
        DyVol.getCenter(Center);

        std::string TempText("");

        TempText = boost::lexical_cast<std::string>(Min.x()) + ", " +boost::lexical_cast<std::string>(Min.x()) + ", " + boost::lexical_cast<std::string>(Min.x());
        NodeMinValueLabel->setText(TempText);

        TempText = boost::lexical_cast<std::string>(Max.x()) + ", " +boost::lexical_cast<std::string>(Max.x()) + ", " + boost::lexical_cast<std::string>(Max.x());
        NodeMaxValueLabel->setText(TempText);

        TempText = boost::lexical_cast<std::string>(Center.x()) + ", " +boost::lexical_cast<std::string>(Center.x()) + ", " + boost::lexical_cast<std::string>(Center.x());
        NodeCenterValueLabel->setText(TempText);

        //GeometryPrimitivesCounter PrimCounter;
        //PrimCounter(SelectedNode);
        //NodeTriCountValueLabel->setText(boost::lexical_cast<std::string>(PrimCounter.getTriCount()));

        //NodeTravMaskValueLabel->setText(boost::lexical_cast<std::string>(SelectedNode->getTravMask()));

        //NodeOcclusionMaskValueLabel->setText(boost::lexical_cast<std::string>(SelectedNode->getOcclusionMask()));

        //NodeActiveValueLabel->setText(boost::lexical_cast<std::string>(SelectedNode->getActive()));
    }


}

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

    NodeRefPtr Root(NULL);
    if(argc == 2)
    {
        Root = SceneFileHandler::the()->read(argv[1]);
    }

    if(Root == NULL)
    {
        // Make Torus Node (creates Torus in background of Root)
        NodeRefPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);
        setName(TorusGeometryNode, std::string("Torus"));

        NodeRefPtr TorusNode = Node::create();
        TorusNode->setCore(OSG::Transform::create());
        TorusNode->addChild(TorusGeometryNode);
        setName(TorusNode, std::string("Torus Transform"));

        NodeRefPtr SphereGeometryNode = makeSphere(2,1.0f);
        setName(SphereGeometryNode, std::string("Sphere"));
        NodeRefPtr BoxGeometryNode = makeBox(1.0,1.0,1.0,1,1,1);
        setName(BoxGeometryNode, std::string("Box"));

        // Make Main Scene Node and add the Torus
        Root = OSG::Node::create();
        Root->setCore(OSG::Group::create());
        Root->addChild(TorusNode);
        Root->addChild(SphereGeometryNode);
        Root->addChild(BoxGeometryNode);
        setName(Root, std::string("Root"));
    }

    // Create the Graphics
    GraphicsRefPtr TutorialGraphics = OSG::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

    //Tree Model
    TheTreeModel = SceneGraphTreeModel::create();
    TheTreeModel->setRoot(Root);

    TheFileSystemTreeModel = FileSystemTreeModel::create();
    //TheFileSystemTreeModel->setRoot(Path("C:\\"));
    TheFileSystemTreeModel->setRoot(BoostPath("/"));

    //Create the Tree
    TheTree = Tree::create();

    TheTree->setPreferredSize(Vec2f(100, 500));
    TheTree->setModel(TheTreeModel);
    //TheTree->setModel(TheFileSystemTreeModel);
    TutorialTreeSelectionListener  TheTutorialTreeSelectionListener;
    TheTree->getSelectionModel()->addTreeSelectionListener(&TheTutorialTreeSelectionListener);


    // Create a ScrollPanel for easier viewing of the List (see 27ScrollPanel)
    BorderLayoutConstraintsRefPtr SceneTreeConstraints = OSG::BorderLayoutConstraints::create();
    SceneTreeConstraints->setRegion(BorderLayoutConstraints::BORDER_WEST);

    ScrollPanelRefPtr ExampleScrollPanel = ScrollPanel::create();
    ExampleScrollPanel->setPreferredSize(Vec2f(350,300));
    ExampleScrollPanel->setConstraints(SceneTreeConstraints);
    //ExampleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    //ExampleScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    ExampleScrollPanel->setViewComponent(TheTree);

    //Details Panel Labels
    LabelRefPtr NodeNameLabel = Label::create();
    NodeNameLabel->setText("Name");
    NodeNameLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

    NodeNameValueLabel = Label::create();
    NodeNameValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

    LabelRefPtr NodeCoreTypeLabel = Label::create();
    NodeCoreTypeLabel->setText("Core Type");
    NodeCoreTypeLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

    NodeCoreTypeValueLabel = Label::create();
    NodeCoreTypeValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

    LabelRefPtr NodeMinLabel = Label::create();
    NodeMinLabel->setText("Min");
    NodeMinLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

    NodeMinValueLabel = Label::create();
    NodeMinValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

    LabelRefPtr NodeMaxLabel = Label::create();
    NodeMaxLabel->setText("Max");
    NodeMaxLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

    NodeMaxValueLabel = Label::create();
    NodeMaxValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

    LabelRefPtr NodeCenterLabel = Label::create();
    NodeCenterLabel->setText("Center");
    NodeCenterLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

    NodeCenterValueLabel = Label::create();
    NodeCenterValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

    LabelRefPtr NodeTriCountLabel = Label::create();
    NodeTriCountLabel->setText("TriCount");
    NodeTriCountLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

    NodeTriCountValueLabel = Label::create();
    NodeTriCountValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

    LabelRefPtr NodeTravMaskLabel = Label::create();
    NodeTravMaskLabel->setText("Traversal Mask");
    NodeTravMaskLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

    NodeTravMaskValueLabel = Label::create();
    NodeTravMaskValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

    LabelRefPtr NodeOcclusionMaskLabel = Label::create();
    NodeOcclusionMaskLabel->setText("Occlusion Mask");
    NodeOcclusionMaskLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

    NodeOcclusionMaskValueLabel = Label::create();
    NodeOcclusionMaskValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

    LabelRefPtr NodeActiveLabel = Label::create();
    NodeActiveLabel->setText("Active");
    NodeActiveLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

    NodeActiveValueLabel = Label::create();
    NodeActiveValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    //Details Panel
    BorderLayoutConstraintsRefPtr NodeDetailPanelConstraints = OSG::BorderLayoutConstraints::create();
    NodeDetailPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_SOUTH);

    GridLayoutRefPtr NodeDetailPanelLayout = OSG::GridLayout::create();

    NodeDetailPanelLayout->setRows(9);
    NodeDetailPanelLayout->setColumns(2);
    NodeDetailPanelLayout->setHorizontalGap(2);
    NodeDetailPanelLayout->setVerticalGap(2);

    PanelRefPtr NodeDetailPanel = Panel::create();
    NodeDetailPanel->setConstraints(NodeDetailPanelConstraints);
    NodeDetailPanel->setPreferredSize(Vec2f(100.0f, 200.0f));
    NodeDetailPanel->setLayout(NodeDetailPanelLayout);
    NodeDetailPanel->pushToChildren(NodeNameLabel);
    NodeDetailPanel->pushToChildren(NodeNameValueLabel);
    NodeDetailPanel->pushToChildren(NodeCoreTypeLabel);
    NodeDetailPanel->pushToChildren(NodeCoreTypeValueLabel);
    NodeDetailPanel->pushToChildren(NodeMinLabel);
    NodeDetailPanel->pushToChildren(NodeMinValueLabel);
    NodeDetailPanel->pushToChildren(NodeMaxLabel);
    NodeDetailPanel->pushToChildren(NodeMaxValueLabel);
    NodeDetailPanel->pushToChildren(NodeCenterLabel);
    NodeDetailPanel->pushToChildren(NodeCenterValueLabel);
    NodeDetailPanel->pushToChildren(NodeTriCountLabel);
    NodeDetailPanel->pushToChildren(NodeTriCountValueLabel);
    NodeDetailPanel->pushToChildren(NodeTravMaskLabel);
    NodeDetailPanel->pushToChildren(NodeTravMaskValueLabel);
    NodeDetailPanel->pushToChildren(NodeOcclusionMaskLabel);
    NodeDetailPanel->pushToChildren(NodeOcclusionMaskValueLabel);
    NodeDetailPanel->pushToChildren(NodeActiveLabel);
    NodeDetailPanel->pushToChildren(NodeActiveValueLabel);

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
    MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    LayoutRefPtr MainInternalWindowLayout = OSG::BorderLayout::create();

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
    MainInternalWindow->pushToChildren(ExampleScrollPanel);
    MainInternalWindow->pushToChildren(NodeDetailPanel);
    MainInternalWindow->setLayout(MainInternalWindowLayout);
    MainInternalWindow->setBackgrounds(NULL);
    MainInternalWindow->setBorders(NULL);
    MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.0f,0.5f));
    MainInternalWindow->setScalingInDrawingSurface(Vec2f(1.0,1.0));
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
    mgr->setRoot(Root);

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
                               "52SceneGraphTree");

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
