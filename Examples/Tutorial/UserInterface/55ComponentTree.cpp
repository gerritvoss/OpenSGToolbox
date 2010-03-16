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
#include "OSGComponentTreeModel.h"
#include "OSGFixedHeightTreeModelLayout.h"
#include "OSGDefaultTreeComponentGenerator.h"
#include "OSGNameAttachment.h"

#include "OSGScrollPanel.h"
#include "OSGNameAttachment.h"

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

ComponentTreeModelRefPtr TheTreeModel;
TreeRefPtr TheTree;

class ComponentTreeItemGenerator : public DefaultTreeComponentGenerator
{
    /*==========================  PUBLIC  =================================*/
  public:
    typedef          DefaultTreeComponentGenerator Inherited;
    typedef          ComponentTreeItemGenerator Self;
    typedef          FCRefPtr<Inherited::RefPtr,  Self      > PtrType;

    OSG_FIELD_CONTAINER_DECL(PtrType)

        virtual ComponentRefPtr getTreeComponent(TreeRefPtr Parent, const boost::any& Value, bool IsSelected, bool Expanded, bool Leaf, UInt32 Row, bool HasFocus)
        {
            std::string LabelText("");
            try
            {
                ComponentRefPtr TheComponent = boost::any_cast<ComponentRefPtr>(Value);
                if(TheComponent != NULL)
                {
                    const Char8* CompName = getName(TheComponent);
                    if(CompName != NULL)
                    {
                        LabelText = CompName;
                    }
                    else
                    {
                        LabelText = std::string("Unnamed ") + TheComponent->getType().getCName();
                    }
                }
            }
            catch (boost::bad_any_cast &)
            {
            }

            return getTreeComponentText(Parent,LabelText,IsSelected,Expanded,Leaf,Row,HasFocus);
        }


  protected:

    static FieldContainerType  _type;

    ComponentTreeItemGenerator(void) : Inherited()
    {
    }

    ComponentTreeItemGenerator(const ComponentTreeItemGenerator& source) : Inherited(source)
    {
    }

    virtual ~ComponentTreeItemGenerator(void)
    {
    }
  private:
    friend class FieldContainer;

    ComponentTreeItemGenerator &operator =(const ComponentTreeItemGenerator &source)
    {
        return *this;
    }
};

FieldContainerType ComponentTreeItemGenerator::_type("ComponentTreeItemGenerator",
                                                     "DefaultTreeComponentGenerator",
                                                     NULL,
                                                     (PrototypeCreateF) &ComponentTreeItemGenerator::createEmpty,
                                                     NULL,
                                                     NULL,
                                                     0);

    OSG_FIELD_CONTAINER_INL_DEF(ComponentTreeItemGenerator::Self, ComponentTreeItemGenerator::PtrType)
OSG_FIELD_CONTAINER_DEF(ComponentTreeItemGenerator::Self, ComponentTreeItemGenerator::PtrType)

    typedef ComponentTreeItemGenerator::PtrType ComponentTreeItemGeneratorRefPtr;

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

    ComponentTreeItemGeneratorRefPtr TheGenerator = ComponentTreeItemGenerator::create();

    //Create the Tree
    TheTree = Tree::create();

    TheTree->setPreferredSize(Vec2f(100, 500));
    TheTree->setCellGenerator(TheGenerator);
    setName(TheTree, std::string("TheTree"));

    // Create a ScrollPanel for easier viewing of the List (see 27ScrollPanel)
    ScrollPanelRefPtr ExampleScrollPanel = ScrollPanel::create();
    ExampleScrollPanel->setPreferredSize(Vec2s(350,300));
    //ExampleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    //ExampleScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    ExampleScrollPanel->setViewComponent(TheTree);
    setName(ExampleScrollPanel, std::string("ExampleScrollPanel"));

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
    MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    LayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();

    //Import InternalWindow(s) from XML file
    std::vector<InternalWindowRefPtr> StoreWindows;

    FCFileType::FCPtrStore NewContainers;
    NewContainers = FCFileHandler::the()->read(Path("./Data/55ComponentTree.xml"));

    //Store each window found in the XML in the vector
    FCFileType::FCPtrStore::iterator Itor;
    for(Itor = NewContainers.begin(); Itor != NewContainers.end(); ++Itor)
    {
        if( (*Itor)->getType() == (InternalWindow::getClassType()))
        {
            StoreWindows.push_back(dynamic_pointer_cast<InternalWindow>(*Itor));
        }
    }

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
    MainInternalWindow->pushToChildren(ExampleScrollPanel);
    MainInternalWindow->setLayout(MainInternalWindowLayout);
    MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
    MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
    MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.85f,0.85f));
    MainInternalWindow->setDrawTitlebar(false);
    MainInternalWindow->setResizable(false);
    setName(MainInternalWindow, std::string("MainInternalWindow"));

    //Tree Model
    TheTreeModel = ComponentTreeModel::create();
    TheTreeModel->setRoot(StoreWindows.back());

    TheTree->setModel(TheTreeModel);
    TheTree->setRootVisible(true);

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
                               "54ComponentTree");

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
