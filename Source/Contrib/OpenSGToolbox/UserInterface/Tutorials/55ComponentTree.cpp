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
#include <OpenSG/UserInterface/OSGToggleButton.h>
#include <OpenSG/Toolbox/OSGFCFileHandler.h>

#include <sstream>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

//Tree Headers
#include <OpenSG/UserInterface/OSGTree.h>
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGLayers.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGComponentTreeModel.h>
#include <OpenSG/UserInterface/OSGFixedHeightTreeModelLayout.h>
#include <OpenSG/UserInterface/OSGDefaultTreeComponentGenerator.h>
#include <OpenSG/OSGSimpleAttachments.h>

#include <OpenSG/UserInterface/OSGScrollPanel.h>
#include <OpenSG/OSGSimpleAttachments.h>

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

ComponentTreeModelPtr TheTreeModel;
TreePtr TheTree;

class ComponentTreeItemGenerator : public DefaultTreeComponentGenerator
{
    /*==========================  PUBLIC  =================================*/
  public:
    typedef          DefaultTreeComponentGenerator Inherited;
    typedef          ComponentTreeItemGenerator Self;
	typedef          FCPtr<Inherited::Ptr,  Self      > PtrType;

	OSG_FIELD_CONTAINER_DECL(PtrType)
	
	virtual ComponentPtr getTreeComponent(TreePtr Parent, const boost::any& Value, bool IsSelected, bool Expanded, bool Leaf, UInt32 Row, bool HasFocus)
    {
        std::string LabelText("");
        try
        {
            ComponentPtr TheComponent = boost::any_cast<ComponentPtr>(Value);
            if(TheComponent != NullFC)
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

typedef ComponentTreeItemGenerator::PtrType ComponentTreeItemGeneratorPtr;

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

		NodePtr TorusNode = Node::create();
		beginEditCP(TorusNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
			TorusNode->setCore(osg::Transform::create());
			TorusNode->addChild(TorusGeometryNode);
		endEditCP(TorusNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

		NodePtr SphereGeometryNode = makeSphere(2,1.0f);
		NodePtr BoxGeometryNode = makeBox(1.0,1.0,1.0,1,1,1);

		// Make Main Scene Node and add the Torus
		Root = osg::Node::create();
		beginEditCP(Root, Node::CoreFieldMask | Node::ChildrenFieldMask);
			Root->setCore(osg::Group::create());
			Root->addChild(TorusNode);
			Root->addChild(SphereGeometryNode);
			Root->addChild(BoxGeometryNode);
		endEditCP(Root, Node::CoreFieldMask | Node::ChildrenFieldMask);
	}

    // Create the Graphics
    GraphicsPtr TutorialGraphics = osg::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

	ComponentTreeItemGeneratorPtr TheGenerator = ComponentTreeItemGenerator::create();

    //Create the Tree
    TheTree = Tree::create();

    beginEditCP(TheTree, Tree::PreferredSizeFieldMask);
        TheTree->setPreferredSize(Vec2f(100, 500));
        TheTree->setCellGenerator(TheGenerator);
    endEditCP(TheTree, Tree::PreferredSizeFieldMask);
    setName(TheTree, std::string("TheTree"));

    // Create a ScrollPanel for easier viewing of the List (see 27ScrollPanel)
    ScrollPanelPtr ExampleScrollPanel = ScrollPanel::create();
    beginEditCP(ExampleScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        ExampleScrollPanel->setPreferredSize(Vec2s(350,300));
        //ExampleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //ExampleScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(ExampleScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    ExampleScrollPanel->setViewComponent(TheTree);
    setName(ExampleScrollPanel, std::string("ExampleScrollPanel"));
    
    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);

    LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();

    //Import InternalWindow(s) from XML file
	std::vector<InternalWindowPtr> StoreWindows;

	FCFileType::FCPtrStore NewContainers;
	NewContainers = FCFileHandler::the()->read(Path("./Data/55ComponentTree.xml"));
	
	//Store each window found in the XML in the vector
	FCFileType::FCPtrStore::iterator Itor;
	for(Itor = NewContainers.begin(); Itor != NewContainers.end(); ++Itor)
	{
		if( (*Itor)->getType() == (InternalWindow::getClassType()))
		{
			StoreWindows.push_back(InternalWindow::Ptr::dcast(*Itor));
		}
	}

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().push_back(ExampleScrollPanel);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.85f,0.85f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
    endEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
    setName(MainInternalWindow, std::string("MainInternalWindow"));

    //Tree Model
    TheTreeModel = ComponentTreeModel::create();
    TheTreeModel->setRoot(StoreWindows.back());

    beginEditCP(TheTree, Tree::ModelFieldMask);
        TheTree->setModel(TheTreeModel);
    endEditCP(TheTree, Tree::ModelFieldMask);
    TheTree->setRootVisible(true);

    // Create the Drawing Surface
    UIDrawingSurfacePtr TutorialDrawingSurface = UIDrawingSurface::create();
    beginEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindowEventProducer);
    endEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
	
	TutorialDrawingSurface->openWindow(MainInternalWindow);

    TutorialDrawingSurface->openWindow(StoreWindows.back());

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
            "54ComponentTree");

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
