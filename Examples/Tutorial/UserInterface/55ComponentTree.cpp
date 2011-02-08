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

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

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

void keyPressed(KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_Q &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
}

class ComponentTreeItemGenerator;

typedef TransitPtr   < ComponentTreeItemGenerator > ComponentTreeItemGeneratorTransitPtr;

class ComponentTreeItemGenerator : public DefaultTreeComponentGenerator
{
    /*==========================  PUBLIC  =================================*/
  public:
    typedef          DefaultTreeComponentGenerator Inherited;
    typedef          ComponentTreeItemGenerator Self;

    OSG_GEN_INTERNALPTR(ComponentTreeItemGenerator);

    virtual ComponentTransitPtr getTreeComponent(Tree* const Parent,
                                                 const boost::any& Value,
                                                 bool IsSelected,
                                                 bool Expanded,
                                                 bool Leaf,
                                                 UInt32 Row,
                                                 bool HasFocus)
    {
        std::string LabelText("");
        try
        {
            Component* TheComponent = boost::any_cast<Component*>(Value);
            if(TheComponent != NULL)
            {
                const Char8* CompName = getName(TheComponent);
                if(CompName != NULL)
                {
                    LabelText = CompName;
                }
                else
                {
                    LabelText = std::string("Unnamed");
                }
                LabelText += std::string(" [") +
                    TheComponent->getType().getCName() + "]";
            }
        }
        catch (boost::bad_any_cast &)
        {
        }

        return getTreeComponentText(Parent,LabelText,IsSelected,Expanded,Leaf,Row,HasFocus);
    }

    static FieldContainerType &getClassType   (void)
    {
        return _type;
    }

    static UInt32              getClassTypeId (void)
    {
        return _type.getId();
    }

    static UInt16              getClassGroupId(void)
    {
        return _type.getGroupId();
    }

    FieldContainerType &getType         (void)
    {
        return _type;
    }

    const FieldContainerType &getType         (void) const
    {
        return _type;
    }

    static ComponentTreeItemGeneratorTransitPtr create(void)
    {
        ComponentTreeItemGeneratorTransitPtr fc;

        if(getClassType().getPrototype() != NULL)
        {
            FieldContainerTransitPtr tmpPtr =
                getClassType().getPrototype()-> shallowCopy();

            fc = dynamic_pointer_cast<ComponentTreeItemGenerator>(tmpPtr);
        }

        return fc;
    }

    static ComponentTreeItemGenerator *createEmpty(void)
    {
        ComponentTreeItemGenerator *returnValue;

        newPtr<ComponentTreeItemGenerator>(returnValue, Thread::getCurrentLocalFlags());

        returnValue->_pFieldFlags->_bNamespaceMask &=
            ~Thread::getCurrentLocalFlags();

        return returnValue;
    }

    static ComponentTreeItemGenerator *createEmptyLocal(BitVector bFlags)
    {
        ComponentTreeItemGenerator *returnValue;

        newPtr<ComponentTreeItemGenerator>(returnValue, bFlags);

        returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

        return returnValue;
    }

    FieldContainerTransitPtr shallowCopy(void) const
    {
        ComponentTreeItemGenerator *tmpPtr;

        newPtr(tmpPtr,
               dynamic_cast<const ComponentTreeItemGenerator *>(this),
               Thread::getCurrentLocalFlags());

        tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

        FieldContainerTransitPtr returnValue(tmpPtr);

        return returnValue;
    }

  protected:

    static FieldContainerType  _type;

    ComponentTreeItemGenerator(void) : Inherited()
    {
    }

    ComponentTreeItemGenerator(const ComponentTreeItemGenerator& source) : Inherited(source)
    {
    }

    ~ComponentTreeItemGenerator(void)
    {
    }
  private:
    friend class FieldContainer;

    ComponentTreeItemGenerator &operator =(const ComponentTreeItemGenerator &source)
    {
        return *this;
    }
};

ComponentTreeItemGenerator::TypeObject ComponentTreeItemGenerator::_type(
                                                                         "ComponentTreeItemGenerator",
                                                                         "DefaultTreeComponentGenerator",
                                                                         "NULL",
                                                                         0,
                                                                         reinterpret_cast<PrototypeCreateF>(&ComponentTreeItemGenerator::createEmptyLocal),
                                                                         NULL,
                                                                         NULL,
                                                                         NULL,//reinterpret_cast<InitalInsertDescFunc>(&DefaultListComponentGenerator::classDescInserter),
                                                                         false,
                                                                         0,
                                                                         "",
                                                                         "ComponentTreeItemGenerator"
                                                                        );

OSG_BEGIN_NAMESPACE

OSG_GEN_CONTAINERPTR(ComponentTreeItemGenerator);
/*! \ingroup GrpContribUserInterfaceFieldTraits
  \ingroup GrpLibOSGContribUserInterface
  */
template <>
struct FieldTraits<ComponentTreeItemGenerator *> :
public FieldTraitsFCPtrBase<ComponentTreeItemGenerator *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<ComponentTreeItemGenerator *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBUSERINTERFACE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
        static const Char8    *getSName     (void);

    //    static const char *getSName(void) { return "SFComponentTreeItemGeneratorPtr"; }
    template<typename RefCountPolicy> inline
        static const Char8    *getMName     (void);

    //    static const char *getMName(void) { return "MFComponentTreeItemGeneratorPtr"; }
};

    template<> inline
const Char8 *FieldTraits<ComponentTreeItemGenerator *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecComponentTreeItemGeneratorPtr"; 
}

    template<> inline
const Char8 *FieldTraits<ComponentTreeItemGenerator *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecComponentTreeItemGeneratorPtr"; 
}

    template<> inline
const Char8 *FieldTraits<ComponentTreeItemGenerator *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakComponentTreeItemGeneratorPtr"; 
}

    template<> inline
const Char8 *FieldTraits<ComponentTreeItemGenerator *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdComponentTreeItemGeneratorPtr"; 
}

    template<> inline
const Char8 *FieldTraits<ComponentTreeItemGenerator *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecComponentTreeItemGeneratorPtr"; 
}

    template<> inline
const Char8 *FieldTraits<ComponentTreeItemGenerator *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecComponentTreeItemGeneratorPtr"; 
}

    template<> inline
const Char8 *FieldTraits<ComponentTreeItemGenerator *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakComponentTreeItemGeneratorPtr"; 
}

    template<> inline
const Char8 *FieldTraits<ComponentTreeItemGenerator *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdComponentTreeItemGeneratorPtr"; 
}

/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<ComponentTreeItemGenerator *,
        RecordedRefCountPolicy  > SFRecComponentTreeItemGeneratorPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<ComponentTreeItemGenerator *,
        UnrecordedRefCountPolicy> SFUnrecComponentTreeItemGeneratorPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<ComponentTreeItemGenerator *,
        WeakRefCountPolicy      > SFWeakComponentTreeItemGeneratorPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<ComponentTreeItemGenerator *,
        NoRefCountPolicy        > SFUncountedComponentTreeItemGeneratorPtr;


/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<ComponentTreeItemGenerator *,
        RecordedRefCountPolicy  > MFRecComponentTreeItemGeneratorPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<ComponentTreeItemGenerator *,
        UnrecordedRefCountPolicy> MFUnrecComponentTreeItemGeneratorPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<ComponentTreeItemGenerator *,
        WeakRefCountPolicy      > MFWeakComponentTreeItemGeneratorPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<ComponentTreeItemGenerator *,
        NoRefCountPolicy        > MFUncountedComponentTreeItemGeneratorPtr;
    OSG_END_NAMESPACE

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

            NodeRecPtr TorusNode = Node::create();
            TorusNode->setCore(Transform::create());
            TorusNode->addChild(TorusGeometryNode);

            NodeRecPtr SphereGeometryNode = makeSphere(2,1.0f);
            NodeRecPtr BoxGeometryNode = makeBox(1.0,1.0,1.0,1,1,1);

            // Make Main Scene Node and add the Torus
            Root = Node::create();
            Root->setCore(Group::create());
            Root->addChild(TorusNode);
            Root->addChild(SphereGeometryNode);
            Root->addChild(BoxGeometryNode);
        }

        // Create the Graphics
        GraphicsRecPtr TutorialGraphics = Graphics2D::create();

        // Initialize the LookAndFeelManager to enable default settings
        LookAndFeelManager::the()->getLookAndFeel()->init();

        ComponentTreeItemGeneratorRecPtr TheGenerator = ComponentTreeItemGenerator::create();

        //Create the Tree
        TreeRecPtr TheTree = Tree::create();

        TheTree->setPreferredSize(Vec2f(100, 500));
        TheTree->setCellGenerator(TheGenerator);
        setName(TheTree, std::string("TheTree"));

        // Create a ScrollPanel for easier viewing of the List (see 27ScrollPanel)
        ScrollPanelRecPtr ExampleScrollPanel = ScrollPanel::create();
        ExampleScrollPanel->setPreferredSize(Vec2f(350,300));
        //ExampleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //ExampleScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        ExampleScrollPanel->setViewComponent(TheTree);
        setName(ExampleScrollPanel, std::string("ExampleScrollPanel"));

        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        LayoutRecPtr MainInternalWindowLayout = FlowLayout::create();

        //Import InternalWindow(s) from XML file
        std::vector<InternalWindowRecPtr> StoreWindows;

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

        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
        MainInternalWindow->pushToChildren(ExampleScrollPanel);
        MainInternalWindow->setLayout(MainInternalWindowLayout);
        MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
        MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.85f,0.85f));
        MainInternalWindow->setDrawTitlebar(false);
        MainInternalWindow->setResizable(false);
        setName(MainInternalWindow, std::string("MainInternalWindow"));

        //Tree Model
        ComponentTreeModelRecPtr TheTreeModel = ComponentTreeModel::create();
        TheTreeModel->setRoot(StoreWindows.back());

        TheTree->setModel(TheTreeModel);
        TheTree->setRootVisible(true);

        // Create the Drawing Surface
        UIDrawingSurfaceRecPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);

        TutorialDrawingSurface->openWindow(MainInternalWindow);

        TutorialDrawingSurface->openWindow(StoreWindows.back());

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
                                   "54ComponentTree");

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
