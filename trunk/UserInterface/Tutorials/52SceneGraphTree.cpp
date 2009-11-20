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

// A little helper to simplify Root management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>

// The general Root file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

// Input
#include <OpenSG/Input/OSGWindowUtils.h>

// UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGTreeSelectionListener.h>
#include <OpenSG/Toolbox/OSGGeometryUtils.h>

#include <sstream>
#include <boost/lexical_cast.hpp>

//Tree Headers
#include <OpenSG/UserInterface/OSGTree.h>
#include <OpenSG/UserInterface/OSGLayers.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGBorderLayout.h>
#include <OpenSG/UserInterface/OSGBorderLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGSceneGraphTreeModel.h>
#include <OpenSG/UserInterface/OSGFileSystemTreeModel.h>
#include <OpenSG/UserInterface/OSGFixedHeightTreeModelLayout.h>
#include <OpenSG/UserInterface/OSGGridLayout.h>

#include <OpenSG/UserInterface/OSGScrollPanel.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include <OpenSG/OSGSceneFileHandler.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;

SceneGraphTreeModelPtr TheTreeModel;
FileSystemTreeModelPtr TheFileSystemTreeModel;
TreePtr TheTree;
NodePtr SelectedNode = NullFC;

LabelPtr NodeNameValueLabel;
LabelPtr NodeCoreTypeValueLabel;
LabelPtr NodeMinValueLabel;
LabelPtr NodeMaxValueLabel;
LabelPtr NodeCenterValueLabel;
LabelPtr NodeTriCountValueLabel;
LabelPtr NodeTravMaskValueLabel;
LabelPtr NodeOcclusionMaskValueLabel;
LabelPtr NodeActiveValueLabel;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);
void selectedNodeChanged(void);


// Create a class to allow for the use of the Escape
// key to exit
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
            TutorialWindowEventProducer->closeWindow();
       }
   }

   virtual void keyReleased(const KeyEventPtr e)
   {
   }

   virtual void keyTyped(const KeyEventPtr e)
   {
   }
};

class TutorialTreeSelectionListener : public TreeSelectionListener
{
public:
    //Called whenever elements are added to the selection
    virtual void selectionAdded(const TreeSelectionEventPtr e)
    {
        //Get the selected Node
        try
        {
            SelectedNode = boost::any_cast<NodePtr>(TheTree->getLastSelectedPathComponent());
        }
        catch (boost::bad_any_cast &)
        {
            SelectedNode = NullFC;
        }
        selectedNodeChanged();
    }

    //Called whenever elements are removed to the selection
    virtual void selectionRemoved(const TreeSelectionEventPtr e)
    {
        SelectedNode = NullFC;
        selectedNodeChanged();
    }
};

void selectedNodeChanged(void)
{
    mgr->setHighlight(SelectedNode);


    //Update Details Panel
    if(SelectedNode == NullFC)
    {
        beginEditCP(NodeNameValueLabel, Label::TextFieldMask);
            NodeNameValueLabel->setText("");
        endEditCP(NodeNameValueLabel, Label::TextFieldMask);

        beginEditCP(NodeCoreTypeValueLabel, Label::TextFieldMask);
            NodeCoreTypeValueLabel->setText("");
        endEditCP(NodeCoreTypeValueLabel, Label::TextFieldMask);

        beginEditCP(NodeMinValueLabel, Label::TextFieldMask);
            NodeMinValueLabel->setText("");
        endEditCP(NodeMinValueLabel, Label::TextFieldMask);

        beginEditCP(NodeMaxValueLabel, Label::TextFieldMask);
            NodeMaxValueLabel->setText("");
        endEditCP(NodeMaxValueLabel, Label::TextFieldMask);

        beginEditCP(NodeCenterValueLabel, Label::TextFieldMask);
            NodeCenterValueLabel->setText("");
        endEditCP(NodeCenterValueLabel, Label::TextFieldMask);

        beginEditCP(NodeTriCountValueLabel, Label::TextFieldMask);
            NodeTriCountValueLabel->setText("");
        endEditCP(NodeTriCountValueLabel, Label::TextFieldMask);

        beginEditCP(NodeTravMaskValueLabel, Label::TextFieldMask);
            NodeTravMaskValueLabel->setText("");
        endEditCP(NodeTravMaskValueLabel, Label::TextFieldMask);

        beginEditCP(NodeOcclusionMaskValueLabel, Label::TextFieldMask);
            NodeOcclusionMaskValueLabel->setText("");
        endEditCP(NodeOcclusionMaskValueLabel, Label::TextFieldMask);

        beginEditCP(NodeActiveValueLabel, Label::TextFieldMask);
            NodeActiveValueLabel->setText("");
        endEditCP(NodeActiveValueLabel, Label::TextFieldMask);

    }
    else
    {
        const Char8 *NodeName = getName(SelectedNode);
        beginEditCP(NodeNameValueLabel, Label::TextFieldMask);
            if(NodeName == NULL)
            {
                NodeNameValueLabel->setText("Unnamed Node");
            }
            else
            {
                NodeNameValueLabel->setText(NodeName);
            }
        endEditCP(NodeNameValueLabel, Label::TextFieldMask);

        beginEditCP(NodeCoreTypeValueLabel, Label::TextFieldMask);
            NodeCoreTypeValueLabel->setText(SelectedNode->getCore()->getType().getCName());
        endEditCP(NodeCoreTypeValueLabel, Label::TextFieldMask);

        DynamicVolume DyVol;
        SelectedNode->getWorldVolume(DyVol);
        Pnt3f Min,Max,Center;
        DyVol.getBounds(Min,Max);
        DyVol.getCenter(Center);

        std::string TempText("");

        TempText = boost::lexical_cast<std::string>(Min.x()) + ", " +boost::lexical_cast<std::string>(Min.x()) + ", " + boost::lexical_cast<std::string>(Min.x());
        beginEditCP(NodeMinValueLabel, Label::TextFieldMask);
            NodeMinValueLabel->setText(TempText);
        endEditCP(NodeMinValueLabel, Label::TextFieldMask);

        TempText = boost::lexical_cast<std::string>(Max.x()) + ", " +boost::lexical_cast<std::string>(Max.x()) + ", " + boost::lexical_cast<std::string>(Max.x());
        beginEditCP(NodeMaxValueLabel, Label::TextFieldMask);
            NodeMaxValueLabel->setText(TempText);
        endEditCP(NodeMaxValueLabel, Label::TextFieldMask);

        TempText = boost::lexical_cast<std::string>(Center.x()) + ", " +boost::lexical_cast<std::string>(Center.x()) + ", " + boost::lexical_cast<std::string>(Center.x());
        beginEditCP(NodeCenterValueLabel, Label::TextFieldMask);
            NodeCenterValueLabel->setText(TempText);
        endEditCP(NodeCenterValueLabel, Label::TextFieldMask);

        GeometryPrimitivesCounter PrimCounter;
        PrimCounter(SelectedNode);
        beginEditCP(NodeTriCountValueLabel, Label::TextFieldMask);
            NodeTriCountValueLabel->setText(boost::lexical_cast<std::string>(PrimCounter.getTriCount()));
        endEditCP(NodeTriCountValueLabel, Label::TextFieldMask);

        beginEditCP(NodeTravMaskValueLabel, Label::TextFieldMask);
            NodeTravMaskValueLabel->setText(boost::lexical_cast<std::string>(SelectedNode->getTravMask()));
        endEditCP(NodeTravMaskValueLabel, Label::TextFieldMask);

        beginEditCP(NodeOcclusionMaskValueLabel, Label::TextFieldMask);
            NodeOcclusionMaskValueLabel->setText(boost::lexical_cast<std::string>(SelectedNode->getOcclusionMask()));
        endEditCP(NodeOcclusionMaskValueLabel, Label::TextFieldMask);

        beginEditCP(NodeActiveValueLabel, Label::TextFieldMask);
            NodeActiveValueLabel->setText(boost::lexical_cast<std::string>(SelectedNode->getActive()));
        endEditCP(NodeActiveValueLabel, Label::TextFieldMask);
    }


}

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    TutorialKeyListener TheKeyListener;
    TutorialWindowEventProducer->addKeyListener(&TheKeyListener);

	NodePtr Root(NullFC);
    if(argc == 2)
    {
		Root = SceneFileHandler::the().read(argv[1]);
	}

	if(Root == NullFC)
	{
		// Make Torus Node (creates Torus in background of Root)
		NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);
		setName(TorusGeometryNode, std::string("Torus"));

		NodePtr TorusNode = Node::create();
		beginEditCP(TorusNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
			TorusNode->setCore(osg::Transform::create());
			TorusNode->addChild(TorusGeometryNode);
		endEditCP(TorusNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
		setName(TorusNode, std::string("Torus Transform"));

		NodePtr SphereGeometryNode = makeSphere(2,1.0f);
		setName(SphereGeometryNode, std::string("Sphere"));
		NodePtr BoxGeometryNode = makeBox(1.0,1.0,1.0,1,1,1);
		setName(BoxGeometryNode, std::string("Box"));

		// Make Main Scene Node and add the Torus
		Root = osg::Node::create();
		beginEditCP(Root, Node::CoreFieldMask | Node::ChildrenFieldMask);
			Root->setCore(osg::Group::create());
			Root->addChild(TorusNode);
			Root->addChild(SphereGeometryNode);
			Root->addChild(BoxGeometryNode);
		endEditCP(Root, Node::CoreFieldMask | Node::ChildrenFieldMask);
		setName(Root, std::string("Root"));
	}

    // Create the Graphics
    GraphicsPtr TutorialGraphics = osg::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

    //Tree Model
    TheTreeModel = SceneGraphTreeModel::create();
    TheTreeModel->setRoot(Root);

    TheFileSystemTreeModel = FileSystemTreeModel::create();
    //TheFileSystemTreeModel->setRoot(Path("C:\\"));
    TheFileSystemTreeModel->setRoot(Path("/"));
    
    //Create the Tree
    TheTree = Tree::create();

    beginEditCP(TheTree, Tree::PreferredSizeFieldMask | Tree::ModelFieldMask);
        TheTree->setPreferredSize(Vec2f(100, 500));
        TheTree->setModel(TheTreeModel);
        //TheTree->setModel(TheFileSystemTreeModel);
    endEditCP(TheTree, Tree::PreferredSizeFieldMask | Tree::ModelFieldMask);
    TutorialTreeSelectionListener  TheTutorialTreeSelectionListener;
    TheTree->getSelectionModel()->addTreeSelectionListener(&TheTutorialTreeSelectionListener);


    // Create a ScrollPanel for easier viewing of the List (see 27ScrollPanel)
    BorderLayoutConstraintsPtr SceneTreeConstraints = osg::BorderLayoutConstraints::create();
    beginEditCP(SceneTreeConstraints, BorderLayoutConstraints::RegionFieldMask);
        SceneTreeConstraints->setRegion(BorderLayoutConstraints::BORDER_WEST);
    endEditCP(SceneTreeConstraints, BorderLayoutConstraints::RegionFieldMask);

    ScrollPanelPtr ExampleScrollPanel = ScrollPanel::create();
    beginEditCP(ExampleScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask | ScrollPanel::ConstraintsFieldMask);
        ExampleScrollPanel->setPreferredSize(Vec2s(350,300));
        ExampleScrollPanel->setConstraints(SceneTreeConstraints);
        //ExampleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //ExampleScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(ExampleScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask | ScrollPanel::ConstraintsFieldMask);
    ExampleScrollPanel->setViewComponent(TheTree);
    
    //Details Panel Labels
    LabelPtr NodeNameLabel = Label::create();
    beginEditCP(NodeNameLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeNameLabel->setText("Name");
        NodeNameLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeNameLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeNameValueLabel = Label::create();
    beginEditCP(NodeNameValueLabel, Label::PreferredSizeFieldMask);
        NodeNameValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeNameValueLabel, Label::PreferredSizeFieldMask);

    LabelPtr NodeCoreTypeLabel = Label::create();
    beginEditCP(NodeCoreTypeLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeCoreTypeLabel->setText("Core Type");
        NodeCoreTypeLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeCoreTypeLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeCoreTypeValueLabel = Label::create();
    beginEditCP(NodeCoreTypeValueLabel, Label::PreferredSizeFieldMask);
        NodeCoreTypeValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeCoreTypeValueLabel, Label::PreferredSizeFieldMask);

    LabelPtr NodeMinLabel = Label::create();
    beginEditCP(NodeMinLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeMinLabel->setText("Min");
        NodeMinLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeMinLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeMinValueLabel = Label::create();
    beginEditCP(NodeMinValueLabel, Label::PreferredSizeFieldMask);
        NodeMinValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeMinValueLabel, Label::PreferredSizeFieldMask);

    LabelPtr NodeMaxLabel = Label::create();
    beginEditCP(NodeMaxLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeMaxLabel->setText("Max");
        NodeMaxLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeMaxLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeMaxValueLabel = Label::create();
    beginEditCP(NodeMaxValueLabel, Label::PreferredSizeFieldMask);
        NodeMaxValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeMaxValueLabel, Label::PreferredSizeFieldMask);

    LabelPtr NodeCenterLabel = Label::create();
    beginEditCP(NodeCenterLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeCenterLabel->setText("Center");
        NodeCenterLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeCenterLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeCenterValueLabel = Label::create();
    beginEditCP(NodeCenterValueLabel, Label::PreferredSizeFieldMask);
        NodeCenterValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeCenterValueLabel, Label::PreferredSizeFieldMask);

    LabelPtr NodeTriCountLabel = Label::create();
    beginEditCP(NodeTriCountLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeTriCountLabel->setText("TriCount");
        NodeTriCountLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeTriCountLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeTriCountValueLabel = Label::create();
    beginEditCP(NodeTriCountValueLabel, Label::PreferredSizeFieldMask);
        NodeTriCountValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeTriCountValueLabel, Label::PreferredSizeFieldMask);

    LabelPtr NodeTravMaskLabel = Label::create();
    beginEditCP(NodeTravMaskLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeTravMaskLabel->setText("Traversal Mask");
        NodeTravMaskLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeTravMaskLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeTravMaskValueLabel = Label::create();
    beginEditCP(NodeTravMaskValueLabel, Label::PreferredSizeFieldMask);
        NodeTravMaskValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeTravMaskValueLabel, Label::PreferredSizeFieldMask);

    LabelPtr NodeOcclusionMaskLabel = Label::create();
    beginEditCP(NodeOcclusionMaskLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeOcclusionMaskLabel->setText("Occlusion Mask");
        NodeOcclusionMaskLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeOcclusionMaskLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeOcclusionMaskValueLabel = Label::create();
    beginEditCP(NodeOcclusionMaskValueLabel, Label::PreferredSizeFieldMask);
        NodeOcclusionMaskValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeOcclusionMaskValueLabel, Label::PreferredSizeFieldMask);

    LabelPtr NodeActiveLabel = Label::create();
    beginEditCP(NodeActiveLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);
        NodeActiveLabel->setText("Active");
        NodeActiveLabel->setPreferredSize(Vec2f(100.0f, 20.0f));
    endEditCP(NodeActiveLabel, Label::TextFieldMask | Label::PreferredSizeFieldMask);

    NodeActiveValueLabel = Label::create();
    beginEditCP(NodeActiveValueLabel, Label::PreferredSizeFieldMask);
        NodeActiveValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
    endEditCP(NodeActiveValueLabel, Label::PreferredSizeFieldMask);
    //Details Panel
    BorderLayoutConstraintsPtr NodeDetailPanelConstraints = osg::BorderLayoutConstraints::create();
    beginEditCP(NodeDetailPanelConstraints, BorderLayoutConstraints::RegionFieldMask);
        NodeDetailPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_SOUTH);
    endEditCP(NodeDetailPanelConstraints, BorderLayoutConstraints::RegionFieldMask);

    GridLayoutPtr NodeDetailPanelLayout = osg::GridLayout::create();

    beginEditCP(NodeDetailPanelLayout, GridLayout::RowsFieldMask | GridLayout::ColumnsFieldMask | 
		GridLayout::HorizontalGapFieldMask | GridLayout::VerticalGapFieldMask);
        NodeDetailPanelLayout->setRows(9);
        NodeDetailPanelLayout->setColumns(2);
        NodeDetailPanelLayout->setHorizontalGap(2);
        NodeDetailPanelLayout->setVerticalGap(2);
    endEditCP(NodeDetailPanelLayout, GridLayout::RowsFieldMask | GridLayout::ColumnsFieldMask | 
		GridLayout::HorizontalGapFieldMask | GridLayout::VerticalGapFieldMask);

    PanelPtr NodeDetailPanel = Panel::create();
    beginEditCP(NodeDetailPanel, Panel::ConstraintsFieldMask | Panel::ChildrenFieldMask | Panel::PreferredSizeFieldMask | Panel::LayoutFieldMask);
        NodeDetailPanel->setConstraints(NodeDetailPanelConstraints);
        NodeDetailPanel->setPreferredSize(Vec2f(100.0f, 200.0f));
        NodeDetailPanel->setLayout(NodeDetailPanelLayout);
        NodeDetailPanel->getChildren().push_back(NodeNameLabel);
        NodeDetailPanel->getChildren().push_back(NodeNameValueLabel);
        NodeDetailPanel->getChildren().push_back(NodeCoreTypeLabel);
        NodeDetailPanel->getChildren().push_back(NodeCoreTypeValueLabel);
        NodeDetailPanel->getChildren().push_back(NodeMinLabel);
        NodeDetailPanel->getChildren().push_back(NodeMinValueLabel);
        NodeDetailPanel->getChildren().push_back(NodeMaxLabel);
        NodeDetailPanel->getChildren().push_back(NodeMaxValueLabel);
        NodeDetailPanel->getChildren().push_back(NodeCenterLabel);
        NodeDetailPanel->getChildren().push_back(NodeCenterValueLabel);
        NodeDetailPanel->getChildren().push_back(NodeTriCountLabel);
        NodeDetailPanel->getChildren().push_back(NodeTriCountValueLabel);
        NodeDetailPanel->getChildren().push_back(NodeTravMaskLabel);
        NodeDetailPanel->getChildren().push_back(NodeTravMaskValueLabel);
        NodeDetailPanel->getChildren().push_back(NodeOcclusionMaskLabel);
        NodeDetailPanel->getChildren().push_back(NodeOcclusionMaskValueLabel);
        NodeDetailPanel->getChildren().push_back(NodeActiveLabel);
        NodeDetailPanel->getChildren().push_back(NodeActiveValueLabel);
    endEditCP(NodeDetailPanel, Panel::ConstraintsFieldMask | Panel::ChildrenFieldMask | Panel::PreferredSizeFieldMask | Panel::LayoutFieldMask);

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);

    LayoutPtr MainInternalWindowLayout = osg::BorderLayout::create();

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().push_back(ExampleScrollPanel);
       MainInternalWindow->getChildren().push_back(NodeDetailPanel);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(NullFC);
       MainInternalWindow->setBorders(NullFC);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.0f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(1.0,1.0));
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
    mgr->setRoot(Root);

    // Add the UI Foreground Object to the Scene
    ViewportPtr TutorialViewport = mgr->getWindow()->getPort(0);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);
        TutorialViewport->getForegrounds().push_back(TutorialUIForeground);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "01RubberBandCamera");

    //Enter main Loop
    TutorialWindowEventProducer->mainLoop();

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
