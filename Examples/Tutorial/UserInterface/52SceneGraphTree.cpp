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
#include "OSGGraphOp.h"
#include "OSGDrawableStatsAttachment.h"

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

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);
void selectedNodeChanged(void);

void keyPressed(KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_Q &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
}

class TriCountGraphOp;

OSG_GEN_MEMOBJPTR(TriCountGraphOp);

class TriCountGraphOp : public GraphOp
{

  private:
    /* Some internal helper methods */
    UInt32 _NumTris;

  protected:

    Action::ResultE traverseEnter(Node * const node)
    {
        if(node != NULL &&
           node->getCore() != NULL &&
           node->getCore()->getType().isDerivedFrom(Drawable::getClassType()))
        {
            DrawableStatsAttachmentRecPtr Stat = DrawableStatsAttachment::calcStatic(dynamic_cast<Drawable*>(node->getCore()));
            _NumTris += Stat->getTriangles();
        }

        return Action::Continue;
    }

    Action::ResultE traverseLeave(Node * const node, Action::ResultE res)
    {
        return Action::Continue;
    }

    TriCountGraphOp(const char *name    = "TriCount"): 
        GraphOp(name)
    {
    }

    virtual ~TriCountGraphOp(void)
    {
    }
  public:
    typedef GraphOp                            Inherited;
    typedef TriCountGraphOp                    Self;

    OSG_GEN_INTERNAL_MEMOBJPTR(TriCountGraphOp);

    static const char *getClassname(void) { return "TriCountGraphOp"; };

    static  ObjTransitPtr     create(void)
    {
        return TriCountGraphOpTransitPtr(new TriCountGraphOp());
    }

    virtual GraphOpTransitPtr clone (void)
    {
        return GraphOpTransitPtr(new TriCountGraphOp);
    }

    virtual bool traverse(Node *node)
    {
        //Clear then running tally
        _NumTris = 0;

        GraphOp::traverse(node);

        return true;
    }

    void setParams(const std::string params)
    {
        ParamSet ps(params);   

        std::string out = ps.getUnusedParams();
        if(out.length())
        {
            FWARNING(("TriCountGraphOp doesn't have parameters '%s'.\n",
                      out.c_str()));
        }
    }

    UInt32 getNumTri(void) const
    {
        return _NumTris;
    }

    std::string usage(void)
    {
        return 
            "TriCount: Get triangle count\n"
            "Params: name (type, default)\n"
            ;
    }

};

class SelectionHandler
{
  private:
    NodeRecPtr _SelectedNode;
    TreeRecPtr _TheTree;

    SimpleSceneManager *_mgr;

    LabelRecPtr _NodeNameValueLabel;
    LabelRecPtr _NodeCoreTypeValueLabel;
    LabelRecPtr _NodeMinValueLabel;
    LabelRecPtr _NodeMaxValueLabel;
    LabelRecPtr _NodeCenterValueLabel;
    LabelRecPtr _NodeTriCountValueLabel;
    LabelRecPtr _NodeTravMaskValueLabel;

    void selectedNodeChanged(void)
    {
        _mgr->setHighlight(_SelectedNode);


        //Update Details Panel
        if(_SelectedNode == NULL)
        {
            _NodeNameValueLabel->setText("");

            _NodeCoreTypeValueLabel->setText("");

            _NodeMinValueLabel->setText("");

            _NodeMaxValueLabel->setText("");

            _NodeCenterValueLabel->setText("");

            _NodeTriCountValueLabel->setText("");

            _NodeTravMaskValueLabel->setText("");
        }
        else
        {
            const Char8 *NodeName = getName(_SelectedNode);
            if(NodeName == NULL)
            {
                _NodeNameValueLabel->setText("Unnamed Node");
            }
            else
            {
                _NodeNameValueLabel->setText(NodeName);
            }

            _NodeCoreTypeValueLabel->setText(_SelectedNode->getCore()->getType().getCName());

            BoxVolume DyVol;
            _SelectedNode->getWorldVolume(DyVol);
            Pnt3f Min,Max,Center;
            DyVol.getBounds(Min,Max);
            DyVol.getCenter(Center);

            std::string TempText("");

            TempText = boost::lexical_cast<std::string>(Min.x())
                + ", " +boost::lexical_cast<std::string>(Min.x())
                + ", " + boost::lexical_cast<std::string>(Min.x());
            _NodeMinValueLabel->setText(TempText);

            TempText = boost::lexical_cast<std::string>(Max.x())
                + ", " +boost::lexical_cast<std::string>(Max.x())
                + ", " + boost::lexical_cast<std::string>(Max.x());
            _NodeMaxValueLabel->setText(TempText);

            TempText = boost::lexical_cast<std::string>(Center.x())
                + ", " +boost::lexical_cast<std::string>(Center.x())
                + ", " + boost::lexical_cast<std::string>(Center.x());
            _NodeCenterValueLabel->setText(TempText);

            _NodeTravMaskValueLabel->setText(boost::lexical_cast<std::string>(_SelectedNode->getTravMask()));

            //Tri Cound
            TriCountGraphOpRefPtr TheTriGraphOp = TriCountGraphOp::create();
            TheTriGraphOp->traverse(_SelectedNode);

            _NodeTriCountValueLabel->setText(boost::lexical_cast<std::string>(TheTriGraphOp->getNumTri()));
        }
    }

    //Called whenever elements are added to the selection
    void handleTreeSelectionAdded(TreeSelectionEventDetails* const details)
    {
        //Get the selected Node
        try
        {
            _SelectedNode = boost::any_cast<NodeUnrecPtr>(_TheTree->getLastSelectedPathComponent());
        }
        catch (boost::bad_any_cast &)
        {
            _SelectedNode = NULL;
        }
        selectedNodeChanged();
    }

    //Called whenever elements are removed to the selection
    void handleTreeSelectionRemoved(TreeSelectionEventDetails* const details)
    {
        _SelectedNode = NULL;
        selectedNodeChanged();
    }
  public:
    SelectionHandler(Tree* const TheTree,

                     SimpleSceneManager *mgr,

                     Label* const NodeNameValueLabel,
                     Label* const NodeCoreTypeValueLabel,
                     Label* const NodeMinValueLabel,
                     Label* const NodeMaxValueLabel,
                     Label* const NodeCenterValueLabel,
                     Label* const NodeTriCountValueLabel,
                     Label* const NodeTravMaskValueLabel) :
                        _SelectedNode(NULL),
                        _TheTree(TheTree),

                        _mgr(mgr),

                        _NodeNameValueLabel(NodeNameValueLabel),
                        _NodeCoreTypeValueLabel(NodeCoreTypeValueLabel),
                        _NodeMinValueLabel(NodeMinValueLabel),
                        _NodeMaxValueLabel(NodeMaxValueLabel),
                        _NodeCenterValueLabel(NodeCenterValueLabel),
                        _NodeTriCountValueLabel(NodeTriCountValueLabel),
                        _NodeTravMaskValueLabel(NodeTravMaskValueLabel)
    {
        _TheTree->getSelectionModel()->connectSelectionAdded(boost::bind(&SelectionHandler::handleTreeSelectionAdded,
                                                                         this,
                                                                         _1));
        _TheTree->getSelectionModel()->connectSelectionRemoved(boost::bind(&SelectionHandler::handleTreeSelectionRemoved,
                                                                         this,
                                                                         _1));
    }
};

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

        NodeRecPtr Root(NULL);
        if(argc == 2)
        {
            Root = SceneFileHandler::the()->read(argv[1]);
        }

        if(Root == NULL)
        {
            // Make Torus Node (creates Torus in background of Root)
            NodeRecPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);
            setName(TorusGeometryNode, std::string("Torus"));

            NodeRecPtr TorusNode = Node::create();
            TorusNode->setCore(Transform::create());
            TorusNode->addChild(TorusGeometryNode);
            setName(TorusNode, std::string("Torus Transform"));

            NodeRecPtr SphereGeometryNode = makeSphere(2,1.0f);
            setName(SphereGeometryNode, std::string("Sphere"));
            NodeRecPtr BoxGeometryNode = makeBox(1.0,1.0,1.0,1,1,1);
            setName(BoxGeometryNode, std::string("Box"));

            // Make Main Scene Node and add the Torus
            Root = Node::create();
            Root->setCore(Group::create());
            Root->addChild(TorusNode);
            Root->addChild(SphereGeometryNode);
            Root->addChild(BoxGeometryNode);
            setName(Root, std::string("Root"));
        }

        // Create the Graphics
        GraphicsRecPtr TutorialGraphics = Graphics2D::create();

        // Initialize the LookAndFeelManager to enable default settings
        LookAndFeelManager::the()->getLookAndFeel()->init();

        //Tree Model
        SceneGraphTreeModelRecPtr TheTreeModel = SceneGraphTreeModel::create();
        TheTreeModel->setRoot(Root);

        //Create the Tree
        TreeRecPtr TheTree = Tree::create();

        TheTree->setPreferredSize(Vec2f(100, 500));
        TheTree->setModel(TheTreeModel);


        // Create a ScrollPanel for easier viewing of the List (see 27ScrollPanel)
        BorderLayoutConstraintsRecPtr SceneTreeConstraints = BorderLayoutConstraints::create();
        SceneTreeConstraints->setRegion(BorderLayoutConstraints::BORDER_WEST);

        ScrollPanelRecPtr ExampleScrollPanel = ScrollPanel::create();
        ExampleScrollPanel->setPreferredSize(Vec2f(350,300));
        ExampleScrollPanel->setConstraints(SceneTreeConstraints);
        //ExampleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //ExampleScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        ExampleScrollPanel->setViewComponent(TheTree);

        //Details Panel Labels
        LabelRecPtr NodeNameLabel = Label::create();
        NodeNameLabel->setText("Name");
        NodeNameLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

        LabelRecPtr NodeNameValueLabel = Label::create();
        NodeNameValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

        LabelRecPtr NodeCoreTypeLabel = Label::create();
        NodeCoreTypeLabel->setText("Core Type");
        NodeCoreTypeLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

        LabelRecPtr NodeCoreTypeValueLabel = Label::create();
        NodeCoreTypeValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

        LabelRecPtr NodeMinLabel = Label::create();
        NodeMinLabel->setText("Min");
        NodeMinLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

        LabelRecPtr NodeMinValueLabel = Label::create();
        NodeMinValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

        LabelRecPtr NodeMaxLabel = Label::create();
        NodeMaxLabel->setText("Max");
        NodeMaxLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

        LabelRecPtr NodeMaxValueLabel = Label::create();
        NodeMaxValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

        LabelRecPtr NodeCenterLabel = Label::create();
        NodeCenterLabel->setText("Center");
        NodeCenterLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

        LabelRecPtr NodeCenterValueLabel = Label::create();
        NodeCenterValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

        LabelRecPtr NodeTriCountLabel = Label::create();
        NodeTriCountLabel->setText("TriCount");
        NodeTriCountLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

        LabelRecPtr NodeTriCountValueLabel = Label::create();
        NodeTriCountValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));

        LabelRecPtr NodeTravMaskLabel = Label::create();
        NodeTravMaskLabel->setText("Traversal Mask");
        NodeTravMaskLabel->setPreferredSize(Vec2f(100.0f, 20.0f));

        LabelRecPtr NodeTravMaskValueLabel = Label::create();
        NodeTravMaskValueLabel->setPreferredSize(Vec2f(300.0f, 20.0f));
        //Details Panel
        BorderLayoutConstraintsRecPtr NodeDetailPanelConstraints = BorderLayoutConstraints::create();
        NodeDetailPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_SOUTH);

        GridLayoutRecPtr NodeDetailPanelLayout = GridLayout::create();

        NodeDetailPanelLayout->setRows(7);
        NodeDetailPanelLayout->setColumns(2);
        NodeDetailPanelLayout->setHorizontalGap(2);
        NodeDetailPanelLayout->setVerticalGap(2);

        PanelRecPtr NodeDetailPanel = Panel::create();
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

        SelectionHandler TheTreeSelectionHandler(TheTree,
                                                 &sceneManager,
                                                 NodeNameValueLabel,
                                                 NodeCoreTypeValueLabel,
                                                 NodeMinValueLabel,
                                                 NodeMaxValueLabel,
                                                 NodeCenterValueLabel,
                                                 NodeTriCountValueLabel,
                                                 NodeTravMaskValueLabel);
        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        LayoutRecPtr MainInternalWindowLayout = BorderLayout::create();

        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
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
        UIDrawingSurfaceRecPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);

        TutorialDrawingSurface->openWindow(MainInternalWindow);

        // Create the UI Foreground Object
        UIForegroundRecPtr TutorialUIForeground = UIForeground::create();

        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);


        // Tell the Manager what to manage
        sceneManager.setRoot(Root);

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
                                   "52SceneGraphTree");

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

