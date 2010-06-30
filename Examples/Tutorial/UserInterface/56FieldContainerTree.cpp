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
#include "OSGToggleButton.h"
#include "OSGFCFileHandler.h"

#include <sstream>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

//Tree Headers
#include "OSGTree.h"
#include "OSGLabel.h"
#include "OSGLayers.h"
#include "OSGFlowLayout.h"
#include "OSGFieldContainerTreeModel.h"
#include "OSGFixedHeightTreeModelLayout.h"
#include "OSGFieldContainerFieldPathComponentGenerator.h"
#include "OSGNameAttachment.h"
#include "OSGCheckboxButton.h"

#include "OSGScrollPanel.h"
#include "OSGNameAttachment.h"

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

FieldContainerTreeModelRefPtr TheTreeModel;
TreeRefPtr TheTree;
CheckboxButtonRefPtr ShowMultiFieldsButton;
CheckboxButtonRefPtr ShowSingleFieldsButton;
CheckboxButtonRefPtr ShowPtrFieldsButton;
CheckboxButtonRefPtr ShowDataFieldsButton;
CheckboxButtonRefPtr ShowParentPtrFieldsButton;
CheckboxButtonRefPtr ShowChildPtrFieldsButton;
CheckboxButtonRefPtr ShowAttachmentsButton;
CheckboxButtonRefPtr ShowCallbackFunctorsButton;
CheckboxButtonRefPtr ShowInternalFieldsButton;

class ShowCheckboxesListener : public ButtonSelectedListener
{
  public:
    void init(void)
    {
        ShowMultiFieldsButton->setSelected(TheTreeModel->getShowMultiFields());
        ShowSingleFieldsButton->setSelected(TheTreeModel->getShowSingleFields());
        ShowPtrFieldsButton->setSelected(TheTreeModel->getShowPtrFields());
        ShowDataFieldsButton->setSelected(TheTreeModel->getShowDataFields());
        ShowParentPtrFieldsButton->setSelected(TheTreeModel->getShowParentPtrFields());
        ShowChildPtrFieldsButton->setSelected(TheTreeModel->getShowChildPtrFields());
        ShowAttachmentsButton->setSelected(TheTreeModel->getShowAttachments());
        ShowCallbackFunctorsButton->setSelected(TheTreeModel->getShowCallbackFunctors());
        ShowInternalFieldsButton->setSelected(TheTreeModel->getShowInternalFields());
    }

    virtual void buttonSelected(const ButtonSelectedEventUnrecPtr e)
    {
        update(dynamic_cast<const CheckboxButton*>(e->getSource()), true);
    }

    virtual void buttonDeselected(const ButtonSelectedEventUnrecPtr e)
    {
        update(dynamic_cast<const CheckboxButton*>(e->getSource()), false);
    }

  protected:
    void update(const CheckboxButton* button, bool selected)
    {
        if(button == ShowMultiFieldsButton)
        {
            TheTreeModel->setShowMultiFields(selected);
        }
        else if(button == ShowSingleFieldsButton)
        {
            TheTreeModel->setShowSingleFields(selected);
        }
        else if(button == ShowPtrFieldsButton)
        {
            TheTreeModel->setShowPtrFields(selected);
        }
        else if(button == ShowDataFieldsButton)
        {
            TheTreeModel->setShowDataFields(selected);
        }
        else if(button == ShowParentPtrFieldsButton)
        {
            TheTreeModel->setShowParentPtrFields(selected);
        }
        else if(button == ShowChildPtrFieldsButton)
        {
            TheTreeModel->setShowChildPtrFields(selected);
        }
        else if(button == ShowAttachmentsButton)
        {
            TheTreeModel->setShowAttachments(selected);
        }
        else if(button == ShowCallbackFunctorsButton)
        {
            TheTreeModel->setShowCallbackFunctors(selected);
        }
        else if(button == ShowInternalFieldsButton)
        {
            TheTreeModel->setShowInternalFields(selected);
        }
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

    NodeRefPtr Root(NULL);
    if(argc == 2)
    {
        Root = SceneFileHandler::the()->read(argv[1]);
    }

    if(Root == NULL)
    {
        // Make Torus Node (creates Torus in background of Root)
        NodeRefPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

        NodeRefPtr TorusNode = Node::create();
        TorusNode->setCore(OSG::Transform::create());
        TorusNode->addChild(TorusGeometryNode);

        NodeRefPtr SphereGeometryNode = makeSphere(2,1.0f);
        NodeRefPtr BoxGeometryNode = makeBox(1.0,1.0,1.0,1,1,1);

        // Make Main Scene Node and add the Torus
        Root = OSG::Node::create();
        Root->setCore(OSG::Group::create());
        Root->addChild(TorusNode);
        Root->addChild(SphereGeometryNode);
        Root->addChild(BoxGeometryNode);
    }

    // Create the Graphics
    GraphicsRefPtr TutorialGraphics = OSG::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
    MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    LayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();

    //Import InternalWindow(s) from XML file
    std::vector<InternalWindowRefPtr> StoreWindows;

    FCFileType::FCPtrStore NewContainers;
    NewContainers = FCFileHandler::the()->read(BoostPath("./Data/55ComponentTree.xml"));

    //Store each window found in the XML in the vector
    FCFileType::FCPtrStore::iterator Itor;
    for(Itor = NewContainers.begin(); Itor != NewContainers.end(); ++Itor)
    {
        if( (*Itor)->getType() == (InternalWindow::getClassType()))
        {
            StoreWindows.push_back(dynamic_pointer_cast<InternalWindow>(*Itor));
        }
    }
    //Tree Model
    TheTreeModel = FieldContainerTreeModel::create();
    TheTreeModel->setRoot(StoreWindows.front());
    //TheTreeModel->setShowPtrFields(false);
    //TheTreeModel->setShowDataFields(false);
    //TheTreeModel->setShowParentPtrFields(false);
    //TheTreeModel->setShowChildPtrFields(false);
    TheTreeModel->setShowAttachments(false);
    //TheTreeModel->setShowCallbackFunctors(false);

    //Tree Component Generator
    FieldContainerFieldPathComponentGeneratorRefPtr TheTreeComponentGenerator = FieldContainerFieldPathComponentGenerator::create();

    //Create the Tree
    TheTree = Tree::create();

    TheTree->setPreferredSize(Vec2f(100, 500));
    TheTree->setRootVisible(true);
    TheTree->setModel(TheTreeModel);
    TheTree->setCellGenerator(TheTreeComponentGenerator);
    setName(TheTree, std::string("TheTree"));

    // Create a ScrollPanel for easier viewing of the List (see 27ScrollPanel)
    ScrollPanelRefPtr ExampleScrollPanel = ScrollPanel::create();
    ExampleScrollPanel->setPreferredSize(Vec2f(350,500));
    //ExampleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    //ExampleScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    ExampleScrollPanel->setViewComponent(TheTree);
    setName(ExampleScrollPanel, std::string("ExampleScrollPanel"));

    //Show Buttons
    ShowMultiFieldsButton = CheckboxButton::create();
    ShowSingleFieldsButton = CheckboxButton::create();
    ShowPtrFieldsButton = CheckboxButton::create();
    ShowDataFieldsButton = CheckboxButton::create();
    ShowParentPtrFieldsButton = CheckboxButton::create();
    ShowChildPtrFieldsButton = CheckboxButton::create();
    ShowAttachmentsButton = CheckboxButton::create();
    ShowCallbackFunctorsButton = CheckboxButton::create();
    ShowInternalFieldsButton = CheckboxButton::create();

    ShowMultiFieldsButton->setText("Multi Fields");
    ShowMultiFieldsButton->setPreferredSize(Vec2f(120.0f,ShowMultiFieldsButton->getPreferredSize().y()));
    ShowMultiFieldsButton->setAlignment(Vec2f(0.0f,0.5f));
    ShowSingleFieldsButton->setText("Single Fields");
    ShowSingleFieldsButton->setPreferredSize(Vec2f(120.0f,ShowSingleFieldsButton->getPreferredSize().y()));
    ShowSingleFieldsButton->setAlignment(Vec2f(0.0f,0.5f));
    ShowPtrFieldsButton->setText("Ptr Fields");
    ShowPtrFieldsButton->setPreferredSize(Vec2f(120.0f,ShowPtrFieldsButton->getPreferredSize().y()));
    ShowPtrFieldsButton->setAlignment(Vec2f(0.0f,0.5f));
    ShowDataFieldsButton->setText("Data Fields");
    ShowDataFieldsButton->setPreferredSize(Vec2f(120.0f,ShowDataFieldsButton->getPreferredSize().y()));
    ShowDataFieldsButton->setAlignment(Vec2f(0.0f,0.5f));
    ShowParentPtrFieldsButton->setText("ParentPtr Fields");
    ShowParentPtrFieldsButton->setPreferredSize(Vec2f(120.0f,ShowParentPtrFieldsButton->getPreferredSize().y()));
    ShowParentPtrFieldsButton->setAlignment(Vec2f(0.0f,0.5f));
    ShowChildPtrFieldsButton->setText("ChildPtr Fields");
    ShowChildPtrFieldsButton->setPreferredSize(Vec2f(120.0f,ShowChildPtrFieldsButton->getPreferredSize().y()));
    ShowChildPtrFieldsButton->setAlignment(Vec2f(0.0f,0.5f));
    ShowAttachmentsButton->setText("Attachments");
    ShowAttachmentsButton->setPreferredSize(Vec2f(120.0f,ShowAttachmentsButton->getPreferredSize().y()));
    ShowAttachmentsButton->setAlignment(Vec2f(0.0f,0.5f));
    ShowCallbackFunctorsButton->setText("Callback Functors");
    ShowCallbackFunctorsButton->setPreferredSize(Vec2f(120.0f,ShowCallbackFunctorsButton->getPreferredSize().y()));
    ShowCallbackFunctorsButton->setAlignment(Vec2f(0.0f,0.5f));
    ShowInternalFieldsButton->setText("Internal Fields");
    ShowInternalFieldsButton->setPreferredSize(Vec2f(120.0f,ShowInternalFieldsButton->getPreferredSize().y()));
    ShowInternalFieldsButton->setAlignment(Vec2f(0.0f,0.5f));

    ShowCheckboxesListener TheShowCheckboxesListener;
    TheShowCheckboxesListener.init();
    ShowMultiFieldsButton->addButtonSelectedListener(&TheShowCheckboxesListener);
    ShowSingleFieldsButton->addButtonSelectedListener(&TheShowCheckboxesListener);
    ShowPtrFieldsButton->addButtonSelectedListener(&TheShowCheckboxesListener);
    ShowDataFieldsButton->addButtonSelectedListener(&TheShowCheckboxesListener);
    ShowParentPtrFieldsButton->addButtonSelectedListener(&TheShowCheckboxesListener);
    ShowChildPtrFieldsButton->addButtonSelectedListener(&TheShowCheckboxesListener);
    ShowAttachmentsButton->addButtonSelectedListener(&TheShowCheckboxesListener);
    ShowCallbackFunctorsButton->addButtonSelectedListener(&TheShowCheckboxesListener);
    ShowInternalFieldsButton->addButtonSelectedListener(&TheShowCheckboxesListener);

    PanelRefPtr OptionsPanel = Panel::create();
    FlowLayoutRefPtr OptionsPanelLayout = FlowLayout::create();
    OptionsPanel->setLayout(OptionsPanelLayout);
    OptionsPanel->setPreferredSize(Vec2f(250.0f, 300.0f));
    OptionsPanel->pushToChildren(ShowMultiFieldsButton);
    OptionsPanel->pushToChildren(ShowSingleFieldsButton);
    OptionsPanel->pushToChildren(ShowPtrFieldsButton);
    OptionsPanel->pushToChildren(ShowDataFieldsButton);
    OptionsPanel->pushToChildren(ShowInternalFieldsButton);
    OptionsPanel->pushToChildren(ShowParentPtrFieldsButton);
    OptionsPanel->pushToChildren(ShowChildPtrFieldsButton);
    OptionsPanel->pushToChildren(ShowAttachmentsButton);
    OptionsPanel->pushToChildren(ShowCallbackFunctorsButton);

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
    MainInternalWindow->pushToChildren(ExampleScrollPanel);
    MainInternalWindow->pushToChildren(OptionsPanel);
    MainInternalWindow->setLayout(MainInternalWindowLayout);
    MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
    MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
    MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.85f,0.85f));
    MainInternalWindow->setDrawTitlebar(false);
    MainInternalWindow->setResizable(false);
    setName(MainInternalWindow, std::string("MainInternalWindow"));

    // Create the Drawing Surface
    UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
    TutorialDrawingSurface->setGraphics(TutorialGraphics);
    TutorialDrawingSurface->setEventProducer(TutorialWindow);

    TutorialDrawingSurface->openWindow(MainInternalWindow);

    TutorialDrawingSurface->openWindow(StoreWindows.back());

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
                               "56FieldContainerTree");

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
