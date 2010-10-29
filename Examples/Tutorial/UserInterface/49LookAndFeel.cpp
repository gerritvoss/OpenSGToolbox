// OpenSG Tutorial Example: Creating a Button Component
//
// This tutorial explains how to edit the basic features of
// a Button created in the OSG User Interface library.
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

// 49LookAndFeel Headers
#include "OSGButton.h"
#include "OSGBoxLayout.h"
#include "OSGFlowLayout.h"
#include "OSGCardLayout.h"
#include "OSGLookAndFeelManager.h"
#include "OSGPanel.h"
#include "OSGLabel.h"
#include "OSGSeparator.h"
#include "OSGToggleButton.h"
#include "OSGGridBagLayout.h"
#include "OSGTabPanel.h"
#include "OSGRadioButton.h"
#include "OSGRadioButtonGroup.h"
#include "OSGCheckboxButton.h"
#include "OSGPasswordField.h"
#include "OSGLayers.h"
#include "OSGBorders.h"
#include "OSGTextField.h"
#include "OSGTextArea.h"
#include "OSGTextField.h"
#include "OSGSpinner.h"
#include "OSGNumberSpinnerModel.h"
#include "OSGGridBagLayout.h"
#include "OSGGridBagLayoutConstraints.h"
#include <sstream>
#include "OSGGridLayout.h"
#include "OSGComboBox.h"
#include "OSGDefaultMutableComboBoxModel.h"
#include "OSGXMLLookAndFeel.h"
#include "OSGProgressBar.h"
#include "OSGDefaultBoundedRangeModel.h"
#include "OSGScrollBar.h"
#include "OSGSlider.h"
#include "OSGPopupMenu.h"
#include "OSGMenu.h"
#include "OSGMenuItem.h"
#include "OSGMenuBar.h"
#include "OSGUIRectangle.h"
#include "OSGList.h"
#include "OSGDefaultListModel.h"
#include "OSGDefaultListSelectionModel.h"
#include "OSGScrollPanel.h"
#include "OSGTable.h"
#include "OSGAbstractTableModel.h"
#include "OSGTree.h"
#include "OSGDefaultTreeModel.h"
#include "OSGFixedHeightTreeModelLayout.h"
#include "OSGDefaultMutableTreeNode.h"
#include "OSGDialogWindow.h"
#include "OSGUIDrawUtils.h"
#include "OSGDefaultColorSelectionModel.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

class StatePanelCreator
{
  private:
    PanelRecPtr _ThePanel;	
    PanelRecPtr _WindowPanel;
    PanelRecPtr _AdvancedPanel;
    PanelRecPtr _ListPanel;
    PanelRecPtr _TablePanel;
    PanelRecPtr _TreePanel;
    DefaultBoundedRangeModelRecPtr _ProgressBarBoundedRangeModel;	
    DefaultBoundedRangeModelRecPtr _ScrollBarBoundedRangeModel;
    DefaultBoundedRangeModelRecPtr _SliderBoundedRangeModel;
    ToggleButtonRecPtr CreateNoTitlebarWindowButton;
    InternalWindowRecPtr NoTitleExampleInternalWindow;
    ColorSelectionModelRecPtr ColorModel;

    DefaultListModelRecPtr _ExampleListModel;

    void  createWindowButtonAction(ActionEventDetails* const e)
    {
        //Create a window
        InternalWindowRecPtr ExampleInternalWindow = InternalWindow::create();
        // Assign the Button to the MainInternalWindow so it will be displayed
        // when the view is rendered.
        ExampleInternalWindow->setPosition(Pnt2f(0,0));
        ExampleInternalWindow->setPreferredSize(Vec2f(300,300));
        ExampleInternalWindow->setTitle(std::string("Example Window"));

        _ThePanel->getParentWindow()->getParentDrawingSurface()->openWindow(ExampleInternalWindow);
    }

    void  createMessageDialogAction(ActionEventDetails* const e)
    {
        DialogWindowRefPtr TheDialog = DialogWindow::createMessageDialog("Error", "Error 404: Page Not Found!"/*, DialogWindow::MSG_ERROR*/,true);
        Pnt2f CenteredPosition = calculateAlignment(dynamic_cast<Component*>(e->getSource())->getParentWindow()->getPosition(), dynamic_cast<Component*>(e->getSource())->getParentWindow()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
        TheDialog->setPosition(CenteredPosition);
        dynamic_cast<Component*>(e->getSource())->getParentWindow()->getParentDrawingSurface()->openWindow(TheDialog);
    }

    void  createColorChooserDialogAction(ActionEventDetails* const e)
    {
        DialogWindowRefPtr TheDialog = DialogWindow::createColorChooserDialog("Choose a color",
                                                                              "Choose a color",
                                                                              true,
                                                                              ColorModel,
                                                                              true);
        Pnt2f CenteredPosition = calculateAlignment(dynamic_cast<Component*>(e->getSource())->getParentWindow()->getPosition(), dynamic_cast<Component*>(e->getSource())->getParentWindow()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
        TheDialog->setPosition(CenteredPosition);
        dynamic_cast<Component*>(e->getSource())->getParentWindow()->getParentDrawingSurface()->openWindow(TheDialog);
    }

    void  createComboBoxMessageDialogAction(ActionEventDetails* const e)
    {
        std::vector<std::string> inputValues;
        inputValues.push_back("Choice 1");	
        inputValues.push_back("Choice 2");	
        inputValues.push_back("Choice 3");
        DialogWindowRefPtr TheDialog = DialogWindow::createInputDialog("Input Dialog Title", "Please choose an option below", DialogWindow::INPUT_COMBO,true,inputValues);
        Pnt2f CenteredPosition = calculateAlignment(dynamic_cast<Component*>(e->getSource())->getParentWindow()->getPosition(), dynamic_cast<Component*>(e->getSource())->getParentWindow()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
        TheDialog->setPosition(CenteredPosition);
        dynamic_cast<Component*>(e->getSource())->getParentWindow()->getParentDrawingSurface()->openWindow(TheDialog);
    }

    void  createButtonsMessageDialogAction(ActionEventDetails* const e)
    {
        std::vector<std::string> inputValues;
        inputValues.push_back("Choice 1");	
        inputValues.push_back("Choice 2");	
        inputValues.push_back("Choice 3");
        DialogWindowRefPtr TheDialog = DialogWindow::createInputDialog("Input Dialog Title", "Please choose an option below", DialogWindow::INPUT_BTNS,true,inputValues);
        Pnt2f CenteredPosition = calculateAlignment(dynamic_cast<Component*>(e->getSource())->getParentWindow()->getPosition(), dynamic_cast<Component*>(e->getSource())->getParentWindow()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
        TheDialog->setPosition(CenteredPosition);
        dynamic_cast<Component*>(e->getSource())->getParentWindow()->getParentDrawingSurface()->openWindow(TheDialog);
    }

    void  createTextboxMessageDialogAction(ActionEventDetails* const e)
    {
        std::vector<std::string> inputValues;
        inputValues.push_back("Choice 1");	
        inputValues.push_back("Choice 2");	
        inputValues.push_back("Choice 3");
        DialogWindowRefPtr TheDialog = DialogWindow::createInputDialog("Input Dialog Title", "Please enter a choice below", DialogWindow::INPUT_TEXT,true,inputValues);
        Pnt2f CenteredPosition = calculateAlignment(dynamic_cast<Component*>(e->getSource())->getParentWindow()->getPosition(), dynamic_cast<Component*>(e->getSource())->getParentWindow()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
        TheDialog->setPosition(CenteredPosition);
        dynamic_cast<Component*>(e->getSource())->getParentWindow()->getParentDrawingSurface()->openWindow(TheDialog);
    }

    void  createListMessageDialogAction(ActionEventDetails* const e)
    {
        std::vector<std::string> inputValues;
        inputValues.push_back("Choice 1");	
        inputValues.push_back("Choice 2");	
        inputValues.push_back("Choice 3");
        DialogWindowRefPtr TheDialog = DialogWindow::createInputDialog("Input Dialog Title", "Please enter a choice below", DialogWindow::INPUT_LIST,true,inputValues);
        Pnt2f CenteredPosition = calculateAlignment(dynamic_cast<Component*>(e->getSource())->getParentWindow()->getPosition(), dynamic_cast<Component*>(e->getSource())->getParentWindow()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
        TheDialog->setPosition(CenteredPosition);
        dynamic_cast<Component*>(e->getSource())->getParentWindow()->getParentDrawingSurface()->openWindow(TheDialog);
    }


    void createNoTitlebarWindowButtonSelected(ButtonSelectedEventDetails* const e)
    {
        //Create a window
        NoTitleExampleInternalWindow = InternalWindow::create();
        // Assign the Button to the MainInternalWindow so it will be displayed
        // when the view is rendered.
        NoTitleExampleInternalWindow->setPosition(Pnt2f(100,100));
        NoTitleExampleInternalWindow->setPreferredSize(Vec2f(400,400));
        NoTitleExampleInternalWindow->setTitle(std::string("Example No Titlebar Window"));
        NoTitleExampleInternalWindow->setDrawTitlebar(false);

        _ThePanel->getParentWindow()->getParentDrawingSurface()->openWindow(NoTitleExampleInternalWindow);
    }
    void createNoTitlebarWindowButtonDeselected(ButtonSelectedEventDetails* const e)
    {
        if(NoTitleExampleInternalWindow != NULL)
        {
            NoTitleExampleInternalWindow->close();
        }
        NoTitleExampleInternalWindow = NULL;
    }

    PanelRecPtr createStatePanel(void);
    PanelRecPtr createWindowPanel(void);
    PanelRecPtr createAdvancedPanel(void);
    PanelRecPtr createListPanel(void);
    PanelRecPtr createTablePanel(void);
    PanelRecPtr createTreePanel(void);



  public:
    StatePanelCreator(void)
    {
        _ThePanel = createStatePanel();
        _WindowPanel = createWindowPanel();
        _AdvancedPanel = createAdvancedPanel();
        _ListPanel = createListPanel();
        _TablePanel = createTablePanel();
        _TreePanel = createTreePanel();
        ColorModel = DefaultColorSelectionModel::create();
    }

    PanelRecPtr getPanel(void) const
    {
        return _ThePanel;
    }
    PanelRecPtr getWindowPanel(void) const
    {
        return _WindowPanel;
    }
    PanelRecPtr getAdvancedPanel(void) const
    {
        return _AdvancedPanel;
    }
    PanelRecPtr getListPanel(void) const
    {
        return _ListPanel;
    }
    PanelRecPtr getTablePanel(void) const
    {
        return _TablePanel;
    }
    PanelRecPtr getTreePanel(void) const
    {
        return _TreePanel;
    }
};

//PanelRecPtr createStatePanel(void);


// Create a class to allow for the use of the Ctrl+q
void keyPressed(KeyEventDetails* const e, 
                SimpleSceneManager *mgr,
                UIDrawingSurface* const TutorialDrawingSurface,
                Node* const ExampleUIRectangleNode,
                UIRectangle* const ExampleUIRectangle,
                UIForeground* const TutorialUIForeground)
{
    if(e->getKey() == KeyEventDetails::KEY_Q && e->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(e->getSource())->closeWindow();
    }
    if(e->getKey() == KeyEventDetails::KEY_F1)
    {
        ViewportRecPtr TutorialViewport = mgr->getWindow()->getPort(0);
        TutorialViewport->clearForegrounds();
        TutorialViewport->addForeground(TutorialUIForeground);


        // Add the UIRectangle as a child to the scene
        mgr->getRoot()->subChild(ExampleUIRectangleNode);

        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);
    }
    if(e->getKey() == KeyEventDetails::KEY_F2)
    {
        ViewportRecPtr TutorialViewport = mgr->getWindow()->getPort(0);
        TutorialViewport->clearForegrounds();

        // Add the UIRectangle as a child to the scene
        mgr->getRoot()->addChild(ExampleUIRectangleNode);

        ExampleUIRectangle->setDrawingSurface(TutorialDrawingSurface);
    }
}

void mousePressed(MouseEventDetails* const e, SimpleSceneManager *mgr)
{
    if(dynamic_cast<WindowEventProducer*>(e->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_CAPS_LOCK)
    {
        mgr->mouseButtonPress(e->getButton(), e->getLocation().x(), e->getLocation().y());
    }
}
void mouseReleased(MouseEventDetails* const e, SimpleSceneManager *mgr)
{
    if(dynamic_cast<WindowEventProducer*>(e->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_CAPS_LOCK)
    {
        mgr->mouseButtonRelease(e->getButton(), e->getLocation().x(), e->getLocation().y());
    }
}

void mouseMoved(MouseEventDetails* const e, SimpleSceneManager *mgr)
{
    if(dynamic_cast<WindowEventProducer*>(e->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_CAPS_LOCK)
    {
        mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
    }
}

void mouseDragged(MouseEventDetails* const e, SimpleSceneManager *mgr)
{
    if(dynamic_cast<WindowEventProducer*>(e->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_CAPS_LOCK)
    {
        mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
    }
}

void quitActionPerformed(ActionEventDetails* const details, WindowEventProducer* const TutorialWindow)
{
    TutorialWindow->closeWindow();
}

class ExampleTableModel;

typedef TransitPtr   < ExampleTableModel > ExampleTableModelTransitPtr;

class ExampleTableModel : public AbstractTableModel
{
  public:
    typedef          AbstractTableModel Inherited;
    typedef          ExampleTableModel Self;

    OSG_GEN_INTERNALPTR(ExampleTableModel);
  private:
    // Creates two vectors to store column/cell values in
    std::vector<boost::any> _ColumnValues;
    std::vector<boost::any> _CellValues;

    friend class FieldContainer;

    ExampleTableModel &operator =(const ExampleTableModel &source)
    {
        return *this;
    }
  public:

    // Creates some functions to do what the Table requires to be done
    // and which are needed for a non-basic table
    virtual UInt32 getColumnCount(void) const
    {
        return _ColumnValues.size();
    }

    virtual boost::any getColumnValue(UInt32 columnIndex) const
    {
        return _ColumnValues[columnIndex];
    }

    virtual UInt32 getRowCount(void) const
    {
        return _CellValues.size() / _ColumnValues.size();
    }

    virtual boost::any getValueAt(UInt32 rowIndex, UInt32 columnIndex) const
    {
        return _CellValues[rowIndex*_ColumnValues.size() + columnIndex];
    }

    virtual bool isCellEditable(UInt32 rowIndex, UInt32 columnIndex) const
    {
        // Only returns true if the column is 0; means cell is editable, otherwise, returns false and cell is not editable
        return columnIndex == 0;
    }

    virtual void setValueAt(const boost::any& aValue, UInt32 rowIndex, UInt32 columnIndex)
    {
        // 
        if(columnIndex == 0 && aValue.type() == typeid(std::string))
        {
            _CellValues[rowIndex*getColumnCount() + columnIndex] = aValue;
        }
    }

    virtual const std::type_info& getColumnType(const UInt32& columnIndex)
    {
        return typeid(void);
    }

    /******************************************************

      Create the Table values

     ******************************************************/

    static FieldContainerType  _type;

    ExampleTableModel(const ExampleTableModel& source) : Inherited(source),
    _ColumnValues(source._ColumnValues),
    _CellValues(source._CellValues)
    {
    }

    ExampleTableModel() : Inherited()
    {
        // Creates the lists within column/cell values and adds data (1d representation of 2d array basically)
        _ColumnValues.push_back(boost::any(std::string("Column String")));
        _ColumnValues.push_back(boost::any(std::string("Column Integer")));
        _ColumnValues.push_back(boost::any(std::string("Column GLenum")));
        _ColumnValues.push_back(boost::any(std::string("Column Boolean")));
        _ColumnValues.push_back(boost::any(std::string("Column Pnt3f")));

        _CellValues.push_back(boost::any(std::string("A")));
        _CellValues.push_back(boost::any(Int32(1)));
        _CellValues.push_back(boost::any(GLenum(GL_SRC_ALPHA)));
        _CellValues.push_back(boost::any(bool(true)));
        _CellValues.push_back(boost::any(Pnt3f(1.0,0.0,0.0)));

        _CellValues.push_back(boost::any(std::string("B")));
        _CellValues.push_back(boost::any(Int32(2)));
        _CellValues.push_back(boost::any(GLenum(GL_NICEST)));
        _CellValues.push_back(boost::any(bool(false)));
        _CellValues.push_back(boost::any(Pnt3f(0.0,1.0,0.0)));

        _CellValues.push_back(boost::any(std::string("C")));
        _CellValues.push_back(boost::any(Int32(3)));
        _CellValues.push_back(boost::any(GLenum(GL_CCW)));
        _CellValues.push_back(boost::any(bool(true)));
        _CellValues.push_back(boost::any(Pnt3f(0.0,0.0,1.0)));

        _CellValues.push_back(boost::any(std::string("D")));
        _CellValues.push_back(boost::any(Int32(4)));
        _CellValues.push_back(boost::any(GLenum(GL_CW)));
        _CellValues.push_back(boost::any(bool(false)));
        _CellValues.push_back(boost::any(Pnt3f(1.0,1.0,1.0)));
    }

    ~ExampleTableModel()
    {
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

    virtual       FieldContainerType &getType         (void)
    {
        return _type;
    }

    virtual const FieldContainerType &getType         (void) const
    {
        return _type;
    }

	static ExampleTableModelTransitPtr create(void)
	{
		ExampleTableModelTransitPtr fc;

		if(getClassType().getPrototype() != NULL)
		{
			FieldContainerTransitPtr tmpPtr =
				getClassType().getPrototype()-> shallowCopy();

			fc = dynamic_pointer_cast<ExampleTableModel>(tmpPtr);
		}

		return fc;
	}

	static ExampleTableModel *createEmpty(void)
	{
		ExampleTableModel *returnValue;

		newPtr<ExampleTableModel>(returnValue, Thread::getCurrentLocalFlags());

		returnValue->_pFieldFlags->_bNamespaceMask &=
			~Thread::getCurrentLocalFlags();

		return returnValue;
	}

	static ExampleTableModel *createEmptyLocal(BitVector bFlags)
	{
		ExampleTableModel *returnValue;

		newPtr<ExampleTableModel>(returnValue, bFlags);

		returnValue->_pFieldFlags->_bNamespaceMask &= ~bFlags;

		return returnValue;
	}

	FieldContainerTransitPtr shallowCopy(void) const
	{
		ExampleTableModel *tmpPtr;

		newPtr(tmpPtr,
			   dynamic_cast<const ExampleTableModel *>(this),
			   Thread::getCurrentLocalFlags());

		tmpPtr->_pFieldFlags->_bNamespaceMask &= ~Thread::getCurrentLocalFlags();

		FieldContainerTransitPtr returnValue(tmpPtr);

		return returnValue;
	}

    FieldContainerTransitPtr shallowCopyLocal(
        BitVector bFlags) const
    {
        ExampleTableModel *tmpPtr;

        newPtr(tmpPtr, dynamic_cast<const ExampleTableModel *>(this), bFlags);

        FieldContainerTransitPtr returnValue(tmpPtr);

        tmpPtr->_pFieldFlags->_bNamespaceMask &= ~bFlags;

        return returnValue;
    }

    FieldContainerTransitPtr shallowCopyDependent(
        BitVector bFlags) const
    {
        ExampleTableModel *tmpPtr;

        newPtr(tmpPtr, dynamic_cast<const ExampleTableModel *>(this), ~bFlags);

        FieldContainerTransitPtr returnValue(tmpPtr);

        tmpPtr->_pFieldFlags->_bNamespaceMask = bFlags;

        return returnValue;
    }

    FieldContainer *createAspectCopy(
        const FieldContainer *pRefAspect) const
    {
        ExampleTableModel *returnValue;

        newAspectCopy(returnValue,
                      dynamic_cast<const ExampleTableModel *>(pRefAspect),
                      dynamic_cast<const ExampleTableModel *>(this));

        return returnValue;
    }
};


ExampleTableModel::TypeObject ExampleTableModel::_type(
    "ExampleTableModel",
    "AbstractTableModel",
    "NULL",
    0,
    reinterpret_cast<PrototypeCreateF>(&ExampleTableModel::createEmptyLocal),
    NULL,
    NULL,
    NULL,//reinterpret_cast<InitalInsertDescFunc>(&DefaultListComponentGenerator::classDescInserter),
    false,
    0,
    "",
    "ExampleTableModel"
    );

OSG_BEGIN_NAMESPACE

OSG_GEN_CONTAINERPTR(ExampleTableModel);
/*! \ingroup GrpContribUserInterfaceFieldTraits
    \ingroup GrpLibOSGContribUserInterface
 */
template <>
struct FieldTraits<ExampleTableModel *> :
    public FieldTraitsFCPtrBase<ExampleTableModel *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<ExampleTableModel *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBUSERINTERFACE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFExampleTableModelPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFExampleTableModelPtr"; }
};

template<> inline
const Char8 *FieldTraits<ExampleTableModel *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecExampleTableModelPtr"; 
}

template<> inline
const Char8 *FieldTraits<ExampleTableModel *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecExampleTableModelPtr"; 
}

template<> inline
const Char8 *FieldTraits<ExampleTableModel *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakExampleTableModelPtr"; 
}

template<> inline
const Char8 *FieldTraits<ExampleTableModel *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdExampleTableModelPtr"; 
}

template<> inline
const Char8 *FieldTraits<ExampleTableModel *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecExampleTableModelPtr"; 
}

template<> inline
const Char8 *FieldTraits<ExampleTableModel *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecExampleTableModelPtr"; 
}

template<> inline
const Char8 *FieldTraits<ExampleTableModel *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakExampleTableModelPtr"; 
}

template<> inline
const Char8 *FieldTraits<ExampleTableModel *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdExampleTableModelPtr"; 
}

/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<ExampleTableModel *,
                      RecordedRefCountPolicy  > SFRecExampleTableModelPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<ExampleTableModel *,
                      UnrecordedRefCountPolicy> SFUnrecExampleTableModelPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<ExampleTableModel *,
                      WeakRefCountPolicy      > SFWeakExampleTableModelPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<ExampleTableModel *,
                      NoRefCountPolicy        > SFUncountedExampleTableModelPtr;


/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<ExampleTableModel *,
                      RecordedRefCountPolicy  > MFRecExampleTableModelPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<ExampleTableModel *,
                      UnrecordedRefCountPolicy> MFUnrecExampleTableModelPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<ExampleTableModel *,
                      WeakRefCountPolicy      > MFWeakExampleTableModelPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<ExampleTableModel *,
                      NoRefCountPolicy        > MFUncountedExampleTableModelPtr;
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

        TutorialWindow->connectMousePressed(boost::bind(mousePressed, _1, &sceneManager));
        TutorialWindow->connectMouseReleased(boost::bind(mouseReleased, _1, &sceneManager));
        TutorialWindow->connectMouseMoved(boost::bind(mouseMoved, _1, &sceneManager));
        TutorialWindow->connectMouseDragged(boost::bind(mouseDragged, _1, &sceneManager));

        // Make Torus Node
        NodeRecPtr SceneGeometryNode(NULL);

        SceneGeometryNode = SceneFileHandler::the()->read(".//MesophyllCell.osb");
        if(SceneGeometryNode == NULL)
        {
            SceneGeometryNode = makeTorus(150, 600, 32, 32);
        }

        // Make Main Scene Node and add the Torus
        NodeRecPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(SceneGeometryNode);

        // Create the Graphics
        GraphicsRecPtr graphics = Graphics2D::create();

        // Initialize the LookAndFeelManager to enable default settings
        if(argc > 1)
        {
            BoostPath XMLFile(argv[1]);
            LookAndFeelRecPtr TheLookAndFeel = XMLLookAndFeel::create(XMLFile);

            if(TheLookAndFeel != NULL)
            {
                LookAndFeelManager::the()->setLookAndFeel(TheLookAndFeel);
            }
        }

        LookAndFeelManager::the()->getLookAndFeel()->init();

        /******************************************************

          Create Button Components to be used with 
          TabPanel and specify their characteristics

         ******************************************************/
        LabelRecPtr StateTabPanelTab = Label::create();
        StateTabPanelTab->setText("Basic Components");

        LabelRecPtr WindowTabPanelTab = Label::create();
        WindowTabPanelTab->setText("Windows");

        LabelRecPtr AdvancedTabPanelTab = Label::create();
        AdvancedTabPanelTab->setText("Advanced Components");

        LabelRecPtr ListTabPanelTab = Label::create();
        ListTabPanelTab->setText("List Component");

        LabelRecPtr TableTabPanelTab = Label::create();
        TableTabPanelTab->setText("Table Component");

        LabelRecPtr TreeTabPanelTab = Label::create();
        TreeTabPanelTab->setText("Tree Component");

        /******************************************************

          Create TabPanel.  
         ******************************************************/
        StatePanelCreator TheStatePanelCreator;
        PanelRecPtr StatePanel = TheStatePanelCreator.getPanel();
        PanelRecPtr WindowPanel = TheStatePanelCreator.getWindowPanel();
        TabPanelRecPtr MainTabPanel = TabPanel::create();
        MainTabPanel->setPreferredSize(Vec2f(600,600));
        MainTabPanel->addTab(StateTabPanelTab, StatePanel);
        MainTabPanel->addTab(WindowTabPanelTab, WindowPanel);
        MainTabPanel->addTab(AdvancedTabPanelTab, TheStatePanelCreator.getAdvancedPanel());
        MainTabPanel->addTab(ListTabPanelTab, TheStatePanelCreator.getListPanel());
        MainTabPanel->addTab(TableTabPanelTab, TheStatePanelCreator.getTablePanel());
        MainTabPanel->addTab(TreeTabPanelTab, TheStatePanelCreator.getTreePanel());
        MainTabPanel->setTabAlignment(0.5f);
        MainTabPanel->setTabPlacement(TabPanel::PLACEMENT_NORTH);

        MainTabPanel->setSelectedIndex(0);

        // Creates MenuItems as in 25PopupMenu
        MenuItemRecPtr NewMenuItem = MenuItem::create();
        MenuItemRecPtr OpenMenuItem = MenuItem::create();
        MenuItemRecPtr CloseMenuItem = MenuItem::create();
        MenuItemRecPtr ExitMenuItem = MenuItem::create();
        MenuItemRecPtr UndoMenuItem = MenuItem::create();
        MenuItemRecPtr RedoMenuItem = MenuItem::create();

        //Edits MenuItems
        NewMenuItem->setText("New ...");
        NewMenuItem->setAcceleratorKey(KeyEventDetails::KEY_N);
        NewMenuItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
        NewMenuItem->setMnemonicKey(KeyEventDetails::KEY_N);

        OpenMenuItem->setText("Open ...");
        OpenMenuItem->setAcceleratorKey(KeyEventDetails::KEY_P);
        OpenMenuItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
        OpenMenuItem->setMnemonicKey(KeyEventDetails::KEY_P);

        CloseMenuItem->setText("Close ...");
        CloseMenuItem->setAcceleratorKey(KeyEventDetails::KEY_W);
        CloseMenuItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
        CloseMenuItem->setMnemonicKey(KeyEventDetails::KEY_C);

        ExitMenuItem->setText("Quit");
        ExitMenuItem->setAcceleratorKey(KeyEventDetails::KEY_X);
        ExitMenuItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
        ExitMenuItem->setMnemonicKey(KeyEventDetails::KEY_Q);

        UndoMenuItem->setText("Undo");
        UndoMenuItem->setAcceleratorKey(KeyEventDetails::KEY_Z);
        UndoMenuItem->setAcceleratorModifiers(KeyEventDetails::KEY_MODIFIER_COMMAND);
        UndoMenuItem->setMnemonicKey(KeyEventDetails::KEY_U);
        RedoMenuItem->setText("Redo");
        RedoMenuItem->setEnabled(false);
        RedoMenuItem->setMnemonicKey(KeyEventDetails::KEY_R);

        // Create an ActionListener and assign it to ExitMenuItem
        // This is defined above, and will cause the program to quit
        // when that MenuItem is selected or Control + Q hit 
        ExitMenuItem->connectActionPerformed(boost::bind(&quitActionPerformed, _1, TutorialWindow.get()));

        // Create a File menu and adds its MenuItems
        MenuRecPtr FileMenu = Menu::create();
        FileMenu->addItem(NewMenuItem);
        FileMenu->addItem(OpenMenuItem);
        FileMenu->addItem(CloseMenuItem);
        FileMenu->addSeparator();
        FileMenu->addItem(ExitMenuItem);

        // Labels the File Menu
        FileMenu->setText("File");
        FileMenu->setMnemonicKey(KeyEventDetails::KEY_F);

        // Creates an Edit menu and adds its MenuItems
        MenuRecPtr EditMenu = Menu::create();
        EditMenu->addItem(UndoMenuItem);
        EditMenu->addItem(RedoMenuItem);

        // Labels the Edit Menu
        EditMenu->setText("Edit");
        EditMenu->setMnemonicKey(KeyEventDetails::KEY_E);

        // Creates two Backgrounds

        MenuBarRecPtr MainMenuBar = MenuBar::create();
        // Adds the two Menus to the MainMenuBar
        MainMenuBar->addMenu(FileMenu);
        MainMenuBar->addMenu(EditMenu);

        // Create The Main InternalWindow
        CardLayoutRecPtr MainInternalWindowLayout = CardLayout::create();

        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
        MainInternalWindow->pushToChildren(MainTabPanel);
        MainInternalWindow->setLayout(MainInternalWindowLayout);
        MainInternalWindow->setMenuBar(MainMenuBar);
        MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
        MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.65f,0.65f));
        MainInternalWindow->setDrawTitlebar(true);
        MainInternalWindow->setResizable(true);

        // Create the Drawing Surface
        UIDrawingSurfaceRecPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(graphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);

        TutorialDrawingSurface->openWindow(MainInternalWindow);

        //Make A 3D Rectangle to draw the UI on
        UIRectangleRecPtr ExampleUIRectangle = UIRectangle::create();
        ExampleUIRectangle->setPoint(Pnt3f(-640,-512,750));
        ExampleUIRectangle->setWidth(1280);
        ExampleUIRectangle->setHeight(1024);

        NodeRecPtr ExampleUIRectangleNode = Node::create();
        ExampleUIRectangleNode->setCore(ExampleUIRectangle);

        // Create the UI Foreground Object
        UIForegroundRecPtr TutorialUIForeground = UIForeground::create();

        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);
        sceneManager.setRoot(scene);

        // Add the UI Foreground Object to the Scene
        ViewportRecPtr TutorialViewport = sceneManager.getWindow()->getPort(0);
        TutorialViewport->addForeground(TutorialUIForeground);

        // Show the whole Scene
        sceneManager.showAll();

        TutorialWindow->connectKeyPressed(boost::bind(keyPressed, _1,
                                                                  &sceneManager,
                                                                  TutorialDrawingSurface.get(),
                                                                  ExampleUIRectangleNode.get(),
                                                                  ExampleUIRectangle.get(),
                                                                  TutorialUIForeground.get()));

        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "49LookAndFeel");

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}


PanelRecPtr StatePanelCreator::createStatePanel(void)
{
    /******************************************************

      Create a Panel and its Layout

     ******************************************************/

    GridBagLayoutRecPtr statePanelLayout = GridBagLayout::create();
    statePanelLayout->setRows(12);
    statePanelLayout->setColumns(5);

    PanelRecPtr statePanel = Panel::create();

    /******************************************************
      LayoutConstraints
      Note: 0506 represents a Constraint 
      at X = 5, Y = 6

     ******************************************************/

    GridBagLayoutConstraintsRecPtr Constraint0000 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0100 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0200 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0300 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0400 = GridBagLayoutConstraints::create();

    Constraint0000->setGridX(0);
    Constraint0000->setGridY(0);

    Constraint0100->setGridX(1);
    Constraint0100->setGridY(0);

    Constraint0200->setGridX(2);
    Constraint0200->setGridY(0);

    Constraint0300->setGridX(3);
    Constraint0300->setGridY(0);

    Constraint0400->setGridX(4);
    Constraint0400->setGridY(0);

    /******************************************************
      Row1
     ******************************************************/
    GridBagLayoutConstraintsRecPtr Constraint0001 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0101 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0201 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0301 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0401 = GridBagLayoutConstraints::create();

    Constraint0001->setGridX(0);
    Constraint0001->setGridY(1);

    Constraint0101->setGridX(1);
    Constraint0101->setGridY(1);

    Constraint0201->setGridX(2);
    Constraint0201->setGridY(1);

    Constraint0301->setGridX(3);
    Constraint0301->setGridY(1);

    Constraint0401->setGridX(4);
    Constraint0401->setGridY(1);
    /******************************************************
      Row2
     ******************************************************/
    GridBagLayoutConstraintsRecPtr Constraint0002 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0102 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0202 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0302 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0402 = GridBagLayoutConstraints::create();

    Constraint0002->setGridX(0);
    Constraint0002->setGridY(2);

    Constraint0102->setGridX(1);
    Constraint0102->setGridY(2);

    Constraint0202->setGridX(2);
    Constraint0202->setGridY(2);

    Constraint0302->setGridX(3);
    Constraint0302->setGridY(2);

    Constraint0402->setGridX(4);
    Constraint0402->setGridY(2);
    /******************************************************
      Row3
     ******************************************************/
    GridBagLayoutConstraintsRecPtr Constraint0003 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0103 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0203 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0303 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0403 = GridBagLayoutConstraints::create();

    Constraint0003->setGridX(0);
    Constraint0003->setGridY(3);

    Constraint0103->setGridX(1);
    Constraint0103->setGridY(3);

    Constraint0203->setGridX(2);
    Constraint0203->setGridY(3);

    Constraint0303->setGridX(3);
    Constraint0303->setGridY(3);

    Constraint0403->setGridX(4);
    Constraint0403->setGridY(3);
    /******************************************************
      Row4
     ******************************************************/
    GridBagLayoutConstraintsRecPtr Constraint0004 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0104 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0204 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0304 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0404 = GridBagLayoutConstraints::create();

    Constraint0004->setGridX(0);
    Constraint0004->setGridY(4);

    Constraint0104->setGridX(1);
    Constraint0104->setGridY(4);

    Constraint0204->setGridX(2);
    Constraint0204->setGridY(4);

    Constraint0304->setGridX(3);
    Constraint0304->setGridY(4);

    Constraint0404->setGridX(4);
    Constraint0404->setGridY(4);
    /******************************************************
      Row5
     ******************************************************/
    GridBagLayoutConstraintsRecPtr Constraint0005 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0105 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0205 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0305 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0405 = GridBagLayoutConstraints::create();

    Constraint0005->setGridX(0);
    Constraint0005->setGridY(5);

    Constraint0105->setGridX(1);
    Constraint0105->setGridY(5);

    Constraint0205->setGridX(2);
    Constraint0205->setGridY(5);

    Constraint0305->setGridX(3);
    Constraint0305->setGridY(5);

    Constraint0405->setGridX(4);
    Constraint0405->setGridY(5);
    /******************************************************
      Row6
     ******************************************************/    
    GridBagLayoutConstraintsRecPtr Constraint0006 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0106 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0206 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0306 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0406 = GridBagLayoutConstraints::create();

    Constraint0006->setGridX(0);
    Constraint0006->setGridY(6);

    Constraint0106->setGridX(1);
    Constraint0106->setGridY(6);

    Constraint0206->setGridX(2);
    Constraint0206->setGridY(6);

    Constraint0306->setGridX(3);
    Constraint0306->setGridY(6);

    Constraint0406->setGridX(4);
    Constraint0406->setGridY(6);
    /******************************************************
      Row7
     ******************************************************/    
    GridBagLayoutConstraintsRecPtr Constraint0007 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0107 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0207 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0307 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0407 = GridBagLayoutConstraints::create();

    Constraint0007->setGridX(0);
    Constraint0007->setGridY(7);

    Constraint0107->setGridX(1);
    Constraint0107->setGridY(7);

    Constraint0207->setGridX(2);
    Constraint0207->setGridY(7);

    Constraint0307->setGridX(3);
    Constraint0307->setGridY(7);

    Constraint0407->setGridX(4);
    Constraint0407->setGridY(7);
    /******************************************************
      Row8
     ******************************************************/    
    GridBagLayoutConstraintsRecPtr Constraint0008 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0108 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0208 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0308 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0408 = GridBagLayoutConstraints::create();

    Constraint0008->setGridX(0);
    Constraint0008->setGridY(8);

    Constraint0108->setGridX(1);
    Constraint0108->setGridY(8);

    Constraint0208->setGridX(2);
    Constraint0208->setGridY(8);

    Constraint0308->setGridX(3);
    Constraint0308->setGridY(8);

    Constraint0408->setGridX(4);
    Constraint0408->setGridY(8);
    /******************************************************
      Row9
     ******************************************************/    
    GridBagLayoutConstraintsRecPtr Constraint0009 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0109 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0209 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0309 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0409 = GridBagLayoutConstraints::create();

    Constraint0009->setGridX(0);
    Constraint0009->setGridY(9);

    Constraint0109->setGridX(1);
    Constraint0109->setGridY(9);

    Constraint0209->setGridX(2);
    Constraint0209->setGridY(9);

    Constraint0309->setGridX(3);
    Constraint0309->setGridY(9);

    Constraint0409->setGridX(4);
    Constraint0409->setGridY(9);
    /******************************************************
      Row10
     ******************************************************/    
    GridBagLayoutConstraintsRecPtr Constraint0010 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0110 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0210 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0310 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0410 = GridBagLayoutConstraints::create();

    Constraint0010->setGridX(0);
    Constraint0010->setGridY(10);

    Constraint0110->setGridX(1);
    Constraint0110->setGridY(10);

    Constraint0210->setGridX(2);
    Constraint0210->setGridY(10);

    Constraint0310->setGridX(3);
    Constraint0310->setGridY(10);

    Constraint0410->setGridX(4);
    Constraint0410->setGridY(10);
    /******************************************************
      Row11 
     ******************************************************/
    GridBagLayoutConstraintsRecPtr Constraint0011 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0111 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0211 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0311 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0411 = GridBagLayoutConstraints::create();

    Constraint0011->setGridX(0);
    Constraint0011->setGridY(11);

    Constraint0111->setGridX(1);
    Constraint0111->setGridY(11);

    Constraint0211->setGridX(2);
    Constraint0211->setGridY(11);

    Constraint0311->setGridX(3);
    Constraint0311->setGridY(11);

    Constraint0411->setGridX(4);
    Constraint0411->setGridY(11);

    /******************************************************

      Create Components to add to Panel

    /******************************************************
    Labels
     ******************************************************/
    LabelRecPtr normalLabel = Label::create();
    LabelRecPtr theDisabledLabel = Label::create();

    normalLabel->setText("Normal");
    normalLabel->setConstraints(Constraint0110);
    normalLabel->setMaxSize(Vec2f(75, 23));

    theDisabledLabel->setText("Disabled");
    theDisabledLabel->setConstraints(Constraint0310);
    theDisabledLabel->setMaxSize(Vec2f(75, 23));
    theDisabledLabel->setEnabled(false);
    /******************************************************
      Buttons
     ******************************************************/
    ButtonRecPtr inactiveButton = Button::create();
    ButtonRecPtr activeButton = Button::create();
    ButtonRecPtr disabledInactiveButton = Button::create();
    ButtonRecPtr disabledActiveButton = Button::create();

    inactiveButton->setActive(false);
    inactiveButton->setText("Inactive");
    inactiveButton->setToolTipText("Inactive Button Tooltip");
    inactiveButton->setConstraints(Constraint0101);
    inactiveButton->setMaxSize(Vec2f(75, 23));

    activeButton->setText("RolledOver");
    activeButton->setToolTipText("RolledOver Button Tooltip");
    activeButton->setBorder(activeButton->getRolloverBorder());
    activeButton->setConstraints(Constraint0201);
    activeButton->setMaxSize(Vec2f(75, 23));

    disabledInactiveButton->setActive(false);
    disabledInactiveButton->setEnabled(false);
    disabledInactiveButton->setText("Disabled/Inactive");
    disabledInactiveButton->setConstraints(Constraint0301);
    disabledInactiveButton->setMaxSize(Vec2f(110, 23));

    disabledActiveButton->setEnabled(false);
    disabledActiveButton->setText("Disabled");
    disabledActiveButton->setConstraints(Constraint0401);
    disabledActiveButton->setMaxSize(Vec2f(90, 23));

    /******************************************************
      ToggleButtons
     ******************************************************/
    ToggleButtonRecPtr nonSelectedToggleButton = ToggleButton::create();
    ToggleButtonRecPtr selectedToggleButton = ToggleButton::create();
    ToggleButtonRecPtr disabledSelectedToggleButton = ToggleButton::create();
    ToggleButtonRecPtr disabledNonselectedToggleButton = ToggleButton::create();

    nonSelectedToggleButton->setText("NonSelected");
    nonSelectedToggleButton->setConstraints(Constraint0102);
    nonSelectedToggleButton->setPreferredSize(Vec2f(100, 23));		
    nonSelectedToggleButton->setMaxSize(Vec2f(100, 23));

    selectedToggleButton->setSelected(true);
    selectedToggleButton->setText("Selected");
    selectedToggleButton->setConstraints(Constraint0202);
    selectedToggleButton->setMaxSize(Vec2f(75, 23));

    disabledSelectedToggleButton->setSelected(true);
    disabledSelectedToggleButton->setEnabled(false);
    disabledSelectedToggleButton->setText("Disabled/Selected");
    disabledSelectedToggleButton->setConstraints(Constraint0302);
    disabledSelectedToggleButton->setMaxSize(Vec2f(110, 23));

    disabledNonselectedToggleButton->setSelected(false);
    disabledNonselectedToggleButton->setEnabled(false);
    disabledNonselectedToggleButton->setText("Disabled");
    disabledNonselectedToggleButton->setConstraints(Constraint0402);
    disabledNonselectedToggleButton->setMaxSize(Vec2f(90, 23));

    /******************************************************
      RadioButtons
     ******************************************************/
    RadioButtonRecPtr deselectedRadioButton = RadioButton::create();
    RadioButtonRecPtr selectedRadioButton = RadioButton::create();
    RadioButtonRecPtr disabledDeselectedRadioButton = RadioButton::create();
    RadioButtonRecPtr disabledSelectedRadioButton = RadioButton::create();

    deselectedRadioButton->setText("Deselected");
    deselectedRadioButton->setConstraints(Constraint0103);
    deselectedRadioButton->setMaxSize(Vec2f(100, 23));

    selectedRadioButton->setSelected(true);
    selectedRadioButton->setText("Selected");
    selectedRadioButton->setConstraints(Constraint0203);
    selectedRadioButton->setMaxSize(Vec2f(75, 23));

    disabledDeselectedRadioButton->setEnabled(false);
    disabledDeselectedRadioButton->setSelected(false);
    disabledDeselectedRadioButton->setText("Disabled");
    disabledDeselectedRadioButton->setConstraints(Constraint0303);
    disabledDeselectedRadioButton->setMaxSize(Vec2f(75, 23));

    disabledSelectedRadioButton->setEnabled(false);
    disabledSelectedRadioButton->setSelected(true);
    disabledSelectedRadioButton->setText("Disabled/Selected");
    disabledSelectedRadioButton->setConstraints(Constraint0403);
    disabledSelectedRadioButton->setMaxSize(Vec2f(165, 23));


    /******************************************************
      CheckboxButtons
     ******************************************************/
    CheckboxButtonRecPtr deselectedCheckboxButton = CheckboxButton::create();
    CheckboxButtonRecPtr selectedCheckboxButton = CheckboxButton::create();
    CheckboxButtonRecPtr disabledDeselectedCheckboxButton = CheckboxButton::create();
    CheckboxButtonRecPtr disabledSelectedCheckboxButton = CheckboxButton::create();

    deselectedCheckboxButton->setText("Deselected");
    deselectedCheckboxButton->setConstraints(Constraint0104);
    deselectedCheckboxButton->setMaxSize(Vec2f(75, 23));

    selectedCheckboxButton->setSelected(true);
    selectedCheckboxButton->setText("Selected");
    selectedCheckboxButton->setConstraints(Constraint0204);
    selectedCheckboxButton->setMaxSize(Vec2f(75, 23));

    disabledDeselectedCheckboxButton->setSelected(false);
    disabledDeselectedCheckboxButton->setEnabled(false);
    disabledDeselectedCheckboxButton->setText("Disabled");
    disabledDeselectedCheckboxButton->setConstraints(Constraint0304);
    disabledDeselectedCheckboxButton->setMaxSize(Vec2f(75, 23));

    disabledSelectedCheckboxButton->setSelected(true);
    disabledSelectedCheckboxButton->setEnabled(false);
    disabledSelectedCheckboxButton->setText("Disabled/Selected");
    disabledSelectedCheckboxButton->setConstraints(Constraint0404);
    disabledSelectedCheckboxButton->setMaxSize(Vec2f(150, 23));
    /******************************************************
      TextFields
     ******************************************************/
    TextFieldRecPtr editableTextField = TextField::create();
    TextFieldRecPtr noneditableTextField = TextField::create();
    TextFieldRecPtr disabledEditableTextField = TextField::create();
    TextFieldRecPtr disabledNoneditableTextField = TextField::create();

    editableTextField->setText("Editable");
    editableTextField->setConstraints(Constraint0105);
    editableTextField->setMaxSize(Vec2f(75, 23));
    editableTextField->setEmptyDescText("Type in me");

    noneditableTextField->setEditable(false);
    noneditableTextField->setText("Noneditable");
    noneditableTextField->setConstraints(Constraint0205);
    noneditableTextField->setMaxSize(Vec2f(75, 23));

    disabledEditableTextField->setEnabled(false);
    disabledEditableTextField->setText("Disabled");
    disabledEditableTextField->setConstraints(Constraint0305);
    disabledEditableTextField->setMaxSize(Vec2f(75, 23));

    disabledNoneditableTextField->setEditable(false);
    disabledNoneditableTextField->setEnabled(false);
    disabledNoneditableTextField->setText("Disabled/Noneditable");
    disabledNoneditableTextField->setConstraints(Constraint0405);
    disabledNoneditableTextField->setMaxSize(Vec2f(125, 23));
    /******************************************************
      TextAreas
     ******************************************************/    
    TextAreaRecPtr editableTextArea = TextArea::create();
    TextAreaRecPtr noneditableTextArea = TextArea::create();
    TextAreaRecPtr disabledEditableTextArea = TextArea::create();
    TextAreaRecPtr disabledNoneditableTextArea = TextArea::create();

    editableTextArea->setText("Editable");
    editableTextArea->setConstraints(Constraint0106);
    editableTextArea->setMaxSize(Vec2f(100,50));

    noneditableTextArea->setEditable(false);
    noneditableTextArea->setText("Uneditable");
    noneditableTextArea->setConstraints(Constraint0206);
    noneditableTextArea->setMaxSize(Vec2f(100,50));

    disabledEditableTextArea->setEnabled(false);
    disabledEditableTextArea->setText("Disabled");
    disabledEditableTextArea->setConstraints(Constraint0306);
    disabledEditableTextArea->setMaxSize(Vec2f(100,50));

    disabledNoneditableTextArea->setEditable(false);
    disabledNoneditableTextArea->setEnabled(false);
    disabledNoneditableTextArea->setText("Disabled");
    disabledNoneditableTextArea->setConstraints(Constraint0406);
    disabledNoneditableTextArea->setMaxSize(Vec2f(100,50));

    /******************************************************
      PasswordFields
     ******************************************************/    
    PasswordFieldRecPtr editablePasswordField = PasswordField::create();
    PasswordFieldRecPtr nonEditablePasswordField = PasswordField::create();
    PasswordFieldRecPtr disabledInactivePasswordField = PasswordField::create();
    PasswordFieldRecPtr disabledActivePasswordField = PasswordField::create(); 

    editablePasswordField->setText("editable");
    editablePasswordField->setConstraints(Constraint0107);
    editablePasswordField->setMaxSize(Vec2f(75,23));
    editablePasswordField->setEmptyDescText("password");

    nonEditablePasswordField->setEditable(false);
    nonEditablePasswordField->setText("editable");
    nonEditablePasswordField->setConstraints(Constraint0207);
    nonEditablePasswordField->setMaxSize(Vec2f(75,23));

    disabledInactivePasswordField->setEnabled(false);
    disabledInactivePasswordField->setText("editable");
    disabledInactivePasswordField->setConstraints(Constraint0307);
    disabledInactivePasswordField->setMaxSize(Vec2f(75,23));

    disabledActivePasswordField->setEditable(false);
    disabledActivePasswordField->setEnabled(false);
    disabledActivePasswordField->setText("editable");
    disabledActivePasswordField->setConstraints(Constraint0407);
    disabledActivePasswordField->setMaxSize(Vec2f(75,23));

    /******************************************************
      Spinners
     ******************************************************/
    SpinnerRecPtr inactiveSpinner = Spinner::create();
    SpinnerRecPtr activeSpinner = Spinner::create();
    SpinnerRecPtr disabledInactiveSpinner = Spinner::create();
    SpinnerRecPtr disabledActiveSpinner = Spinner::create();

    Int32SpinnerModelPtr inactiveSpinnerModel(new Int32SpinnerModel());
    Int32SpinnerModelPtr activeSpinnerModel(new Int32SpinnerModel());
    Int32SpinnerModelPtr disabledInactiveSpinnerModel(new Int32SpinnerModel());
    Int32SpinnerModelPtr disabledActiveSpinnerModel(new Int32SpinnerModel());

    inactiveSpinnerModel->setMaximum(10);
    inactiveSpinnerModel->setMinimum(-10);
    inactiveSpinnerModel->setStepSize(1);
    inactiveSpinnerModel->setValue(boost::any(Int32(0)));
    activeSpinnerModel->setMaximum(10);
    activeSpinnerModel->setMinimum(-10);
    activeSpinnerModel->setStepSize(1);
    activeSpinnerModel->setValue(boost::any(Int32(0)));
    disabledInactiveSpinnerModel->setMaximum(10);
    disabledInactiveSpinnerModel->setMinimum(-10);
    disabledInactiveSpinnerModel->setStepSize(1);
    disabledInactiveSpinnerModel->setValue(boost::any(Int32(0)));
    disabledActiveSpinnerModel->setMaximum(10);
    disabledActiveSpinnerModel->setMinimum(-10);
    disabledActiveSpinnerModel->setStepSize(1);
    disabledActiveSpinnerModel->setValue(boost::any(Int32(0)));
    inactiveSpinner->setModel(inactiveSpinnerModel);
    activeSpinner->setModel(activeSpinnerModel);
    disabledInactiveSpinner->setModel(disabledInactiveSpinnerModel);
    disabledActiveSpinner->setModel(disabledActiveSpinnerModel);

    activeSpinner->setConstraints(Constraint0108);
    activeSpinner->setMaxSize(Vec2f(50,25));

    inactiveSpinner->setConstraints(Constraint0208);
    inactiveSpinner->setMaxSize(Vec2f(50,25));
    inactiveSpinner->setEditable(false);

    disabledActiveSpinner->setConstraints(Constraint0308);
    disabledActiveSpinner->setEnabled(false);
    disabledActiveSpinner->setMaxSize(Vec2f(50,25));

    disabledInactiveSpinner->setConstraints(Constraint0408);
    disabledInactiveSpinner->setEnabled(false);
    disabledInactiveSpinner->setMaxSize(Vec2f(50,25));
    disabledInactiveSpinner->setEditable(false);

    /******************************************************
      ComboBoxes
     ******************************************************/

    ComboBoxRecPtr editableComboBox = ComboBox::create();
    ComboBoxRecPtr noneditableComboBox = ComboBox::create();
    ComboBoxRecPtr disabledEditableComboBox = ComboBox::create();
    ComboBoxRecPtr disabledNoneditableComboBox = ComboBox::create();

    // Create Models
    DefaultMutableComboBoxModelRecPtr editableComboBoxModel = DefaultMutableComboBoxModel::create();
    editableComboBoxModel->addElement(boost::any(std::string("Editable")));
    editableComboBoxModel->addElement(boost::any(std::string("These")));
    editableComboBoxModel->addElement(boost::any(std::string("Can")));
    editableComboBoxModel->addElement(boost::any(std::string("Be")));
    editableComboBoxModel->addElement(boost::any(std::string("Typed")));
    editableComboBoxModel->addElement(boost::any(std::string("Over")));


    DefaultMutableComboBoxModelRecPtr noneditableComboBoxModel = DefaultMutableComboBoxModel::create();
    noneditableComboBoxModel->addElement(boost::any(std::string("Noneditable")));
    noneditableComboBoxModel->addElement(boost::any(std::string("These")));
    noneditableComboBoxModel->addElement(boost::any(std::string("Can")));
    noneditableComboBoxModel->addElement(boost::any(std::string("NOT")));
    noneditableComboBoxModel->addElement(boost::any(std::string("Be")));
    noneditableComboBoxModel->addElement(boost::any(std::string("Typed")));
    noneditableComboBoxModel->addElement(boost::any(std::string("Over")));


    // Create simple Models for disabled ComboBoxes
    DefaultMutableComboBoxModelRecPtr disabledEditableComboBoxModel = DefaultMutableComboBoxModel::create();
    disabledEditableComboBoxModel->addElement(boost::any(std::string("Editable")));


    DefaultMutableComboBoxModelRecPtr disabledNoneditableComboBoxModel = DefaultMutableComboBoxModel::create();
    disabledNoneditableComboBoxModel->addElement(boost::any(std::string("Noneditable")));


    editableComboBox->setConstraints(Constraint0109);
    editableComboBox->setMaxSize(Vec2f(75, 23));
    editableComboBox->setModel(editableComboBoxModel);
    editableComboBox->setSelectedIndex(0);
    editableComboBox->setEmptyDescText("Type Selection");

    noneditableComboBox->setEditable(false);
    noneditableComboBox->setConstraints(Constraint0209);
    noneditableComboBox->setMaxSize(Vec2f(100, 23));
    noneditableComboBox->setModel(noneditableComboBoxModel);
    noneditableComboBox->setSelectedIndex(0);

    disabledEditableComboBox->setEnabled(false);
    disabledEditableComboBox->setConstraints(Constraint0309);
    disabledEditableComboBox->setMaxSize(Vec2f(75, 23));
    disabledEditableComboBox->setModel(disabledEditableComboBoxModel);
    disabledEditableComboBox->setSelectedIndex(0);

    disabledNoneditableComboBox->setEditable(false);
    disabledNoneditableComboBox->setEnabled(false);
    disabledNoneditableComboBox->setConstraints(Constraint0409);
    disabledNoneditableComboBox->setMaxSize(Vec2f(100, 23));
    disabledNoneditableComboBox->setModel(disabledNoneditableComboBoxModel);
    disabledNoneditableComboBox->setSelectedIndex(0);

    /******************************************************
      Separators
     ******************************************************/
    SeparatorRecPtr normalSeparator = Separator::create();
    SeparatorRecPtr disabledSeparator = Separator::create();

    normalSeparator->setConstraints(Constraint0111);
    normalSeparator->setMaxSize(Vec2f(75, 23));
    normalSeparator->setOrientation(Separator::HORIZONTAL_ORIENTATION);

    disabledSeparator->setConstraints(Constraint0311);
    disabledSeparator->setMaxSize(Vec2f(75, 23));
    disabledSeparator->setOrientation(Separator::HORIZONTAL_ORIENTATION);
    disabledSeparator->setEnabled(false);
    /******************************************************
      Labels
     ******************************************************/
    LabelRecPtr labelLabel = Label::create();
    LabelRecPtr buttonLabel = Label::create();
    LabelRecPtr toggleButtonLabel = Label::create();
    LabelRecPtr radioButtonLabel = Label::create();
    LabelRecPtr checkboxButtonLabel = Label::create();
    LabelRecPtr textFieldLabel = Label::create();
    LabelRecPtr textAreaLabel = Label::create();
    LabelRecPtr passwordFieldLabel = Label::create();
    LabelRecPtr spinnerLabel = Label::create();
    LabelRecPtr comboboxLabel = Label::create();
    LabelRecPtr separatorLabel = Label::create();
    LabelRecPtr enabledLabel = Label::create();
    LabelRecPtr disabledLabel = Label::create();
    EmptyLayerRecPtr labelBackground = EmptyLayer::create();
    EmptyBorderRecPtr labelBorder = EmptyBorder::create();
    labelLabel->setText("Labels");
    labelLabel->setConstraints(Constraint0010);
    labelLabel->setBackground(labelBackground);
    labelLabel->setBorder(labelBorder);

    buttonLabel->setText("Buttons");
    buttonLabel->setConstraints(Constraint0001);
    buttonLabel->setBackground(labelBackground);
    buttonLabel->setBorder(labelBorder);

    toggleButtonLabel->setText("ToggleButtons");
    toggleButtonLabel->setConstraints(Constraint0002);
    toggleButtonLabel->setBackground(labelBackground);
    toggleButtonLabel->setBorder(labelBorder);

    radioButtonLabel->setText("RadioButtons");
    radioButtonLabel->setConstraints(Constraint0003);
    radioButtonLabel->setBackground(labelBackground);
    radioButtonLabel->setBorder(labelBorder);

    checkboxButtonLabel->setText("CheckboxButtons");
    checkboxButtonLabel->setConstraints(Constraint0004);
    checkboxButtonLabel->setBackground(labelBackground);
    checkboxButtonLabel->setBorder(labelBorder);

    textFieldLabel->setText("TextFields");
    textFieldLabel->setConstraints(Constraint0005);
    textFieldLabel->setBackground(labelBackground);
    textFieldLabel->setBorder(labelBorder);

    textAreaLabel->setText("TextAreas");
    textAreaLabel->setConstraints(Constraint0006);
    textAreaLabel->setBackground(labelBackground);
    textAreaLabel->setBorder(labelBorder);

    passwordFieldLabel->setText("PasswordFields");
    passwordFieldLabel->setConstraints(Constraint0007);
    passwordFieldLabel->setBackground(labelBackground);
    passwordFieldLabel->setBorder(labelBorder);

    spinnerLabel->setText("Spinners");
    spinnerLabel->setConstraints(Constraint0008);
    spinnerLabel->setBackground(labelBackground);
    spinnerLabel->setBorder(labelBorder);

    comboboxLabel->setText("ComboBoxes");
    comboboxLabel->setConstraints(Constraint0009);
    comboboxLabel->setBackground(labelBackground);
    comboboxLabel->setBorder(labelBorder);
    separatorLabel->setText("Separators");
    separatorLabel->setConstraints(Constraint0011);
    separatorLabel->setBackground(labelBackground);
    separatorLabel->setBorder(labelBorder);

    enabledLabel->setText("Enabled");
    enabledLabel->setConstraints(Constraint0100);
    enabledLabel->setBackground(labelBackground);
    enabledLabel->setBorder(labelBorder);

    disabledLabel->setText("Disabled");
    disabledLabel->setConstraints(Constraint0300);
    disabledLabel->setBackground(labelBackground);
    disabledLabel->setBorder(labelBorder);

    //PopupMenu

    MenuItemRecPtr MenuItem1 = MenuItem::create();
    MenuItemRecPtr MenuItem2 = MenuItem::create();
    MenuItemRecPtr MenuItem3 = MenuItem::create();
    MenuItemRecPtr MenuItem4 = MenuItem::create();
    MenuItemRecPtr SubMenuItem1 = MenuItem::create();
    MenuItemRecPtr SubMenuItem2 = MenuItem::create();
    MenuItemRecPtr SubMenuItem3 = MenuItem::create();
    MenuRecPtr ExampleSubMenu = Menu::create();

    /******************************************************

      Edit the MenuItems

      -setText("TEXT"): Sets the text on the 
      item to be TEXT
      -setEnabled(Boolean): sets the menu item
      to be either enabled or disabled

     ******************************************************/

    MenuItem1->setText("Menu Item 1");

    MenuItem2->setText("Menu Item 2");

    MenuItem3->setText("Menu Item 3");

    MenuItem4->setText("Menu Item 4");
    MenuItem4->setEnabled(false);

    SubMenuItem1->setText("SubMenu Item 1");

    SubMenuItem2->setText("SubMenu Item 2");

    SubMenuItem3->setText("SubMenu Item 3");

    ExampleSubMenu->setText("Sub Menu");

    // This adds three MenuItems to the Menu,
    // creating a submenu.  Note this does not
    // involve begin/endEditCPs to do

    ExampleSubMenu->addItem(SubMenuItem1);
    ExampleSubMenu->addItem(SubMenuItem2);
    ExampleSubMenu->addItem(SubMenuItem3);

    /******************************************************

      Create the PopupMenu itself.

      Items are added in the order in which
      they will be displayed (top to bottom)
      via addItem(ItemToBeAdded)

      The PopupMenu is attached to a 
      Button below using 
      setPopupMenu(PopupMenuName).  

Note: PopupMenus can be added to any
Component.

     ******************************************************/
    PopupMenuRecPtr ExamplePopupMenu = PopupMenu::create();
    ExamplePopupMenu->addItem(MenuItem1);
    ExamplePopupMenu->addItem(MenuItem2);
    ExamplePopupMenu->addItem(MenuItem3);
    ExamplePopupMenu->addSeparator();
    ExamplePopupMenu->addItem(ExampleSubMenu);
    ExamplePopupMenu->addItem(MenuItem4);

    inactiveButton->setPopupMenu(ExamplePopupMenu);

    statePanel->pushToChildren(inactiveSpinner);
    statePanel->pushToChildren(activeSpinner);
    statePanel->pushToChildren(disabledInactiveSpinner);
    statePanel->pushToChildren(disabledActiveSpinner);
    statePanel->pushToChildren(inactiveButton);
    statePanel->pushToChildren(activeButton);
    statePanel->pushToChildren(disabledInactiveButton);
    statePanel->pushToChildren(disabledActiveButton);
    statePanel->pushToChildren(nonSelectedToggleButton);
    statePanel->pushToChildren(selectedToggleButton);
    statePanel->pushToChildren(disabledSelectedToggleButton);
    statePanel->pushToChildren(disabledNonselectedToggleButton);
    statePanel->pushToChildren(deselectedCheckboxButton);
    statePanel->pushToChildren(selectedCheckboxButton);
    statePanel->pushToChildren(disabledDeselectedCheckboxButton);
    statePanel->pushToChildren(disabledSelectedCheckboxButton);
    statePanel->pushToChildren(deselectedRadioButton);
    statePanel->pushToChildren(selectedRadioButton);
    statePanel->pushToChildren(disabledDeselectedRadioButton);
    statePanel->pushToChildren(disabledSelectedRadioButton);
    statePanel->pushToChildren(editableTextField);
    statePanel->pushToChildren(noneditableTextField);
    statePanel->pushToChildren(disabledEditableTextField);
    statePanel->pushToChildren(disabledNoneditableTextField);
    statePanel->pushToChildren(editableTextArea);
    statePanel->pushToChildren(noneditableTextArea);
    statePanel->pushToChildren(disabledEditableTextArea);
    statePanel->pushToChildren(disabledNoneditableTextArea);
    statePanel->pushToChildren(editablePasswordField);
    statePanel->pushToChildren(nonEditablePasswordField);
    statePanel->pushToChildren(disabledInactivePasswordField);
    statePanel->pushToChildren(disabledActivePasswordField);
    statePanel->pushToChildren(buttonLabel);
    statePanel->pushToChildren(toggleButtonLabel);
    statePanel->pushToChildren(radioButtonLabel);
    statePanel->pushToChildren(checkboxButtonLabel);
    statePanel->pushToChildren(textFieldLabel);
    statePanel->pushToChildren(textAreaLabel);
    statePanel->pushToChildren(passwordFieldLabel);
    statePanel->pushToChildren(spinnerLabel);
    statePanel->pushToChildren(comboboxLabel);
    statePanel->pushToChildren(enabledLabel);
    statePanel->pushToChildren(disabledLabel);
    statePanel->pushToChildren(editableComboBox);
    statePanel->pushToChildren(noneditableComboBox);
    statePanel->pushToChildren(disabledEditableComboBox);
    statePanel->pushToChildren(disabledNoneditableComboBox);
    statePanel->pushToChildren(normalLabel);
    statePanel->pushToChildren(labelLabel);
    statePanel->pushToChildren(theDisabledLabel);
    statePanel->pushToChildren(normalSeparator);
    statePanel->pushToChildren(separatorLabel);
    statePanel->pushToChildren(disabledSeparator);
    statePanel->setLayout(statePanelLayout);
    statePanel->setPreferredSize(Vec2f(500,800));

    return statePanel;

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

PanelRecPtr StatePanelCreator::createWindowPanel(void)
{
    //Button that creates an empty window
    ButtonRecPtr CreateWindowButton = Button::create();
    CreateWindowButton->setText("Create Window");
    CreateWindowButton->setPreferredSize(Vec2f(100.0f,20.0f));
    CreateWindowButton->connectActionPerformed(boost::bind(&StatePanelCreator::createWindowButtonAction, this, _1));

    CreateNoTitlebarWindowButton = ToggleButton::create();
    CreateNoTitlebarWindowButton->setText("Create No Titlebar Window");
    CreateNoTitlebarWindowButton->setPreferredSize(Vec2f(175.0f,20.0f));
    CreateNoTitlebarWindowButton->connectButtonSelected(boost::bind(&StatePanelCreator::createNoTitlebarWindowButtonSelected, this, _1));
    CreateNoTitlebarWindowButton->connectButtonDeselected(boost::bind(&StatePanelCreator::createNoTitlebarWindowButtonDeselected, this, _1));

    ButtonRecPtr CreateMessageButton = Button::create();
    CreateMessageButton->setText("Create Message");
    CreateMessageButton->setPreferredSize(Vec2f(100.0f,20.0f));
    CreateMessageButton->connectActionPerformed(boost::bind(&StatePanelCreator::createMessageDialogAction, this, _1));
    
    ButtonRecPtr CreateColorChooserButton = Button::create();
    CreateColorChooserButton->setText("Create ColorChooser");
    CreateColorChooserButton->setPreferredSize(Vec2f(100.0f,20.0f));
    CreateColorChooserButton->connectActionPerformed(boost::bind(&StatePanelCreator::createColorChooserDialogAction, this, _1));
    
    ButtonRecPtr CreateComboBoxMessageButton = Button::create();
    CreateComboBoxMessageButton->setText("Create ComboBoxMessage");
    CreateComboBoxMessageButton->setPreferredSize(Vec2f(100.0f,20.0f));
    CreateComboBoxMessageButton->connectActionPerformed(boost::bind(&StatePanelCreator::createComboBoxMessageDialogAction, this, _1));
    
    ButtonRecPtr CreateButtonsMessageButton = Button::create();
    CreateButtonsMessageButton->setText("Create ButtonsMessage");
    CreateButtonsMessageButton->setPreferredSize(Vec2f(100.0f,20.0f));
    CreateButtonsMessageButton->connectActionPerformed(boost::bind(&StatePanelCreator::createButtonsMessageDialogAction, this, _1));
    
    ButtonRecPtr CreateTextboxMessageButton = Button::create();
    CreateTextboxMessageButton->setText("Create TextboxMessage");
    CreateTextboxMessageButton->setPreferredSize(Vec2f(100.0f,20.0f));
    CreateTextboxMessageButton->connectActionPerformed(boost::bind(&StatePanelCreator::createTextboxMessageDialogAction, this, _1));
    
    ButtonRecPtr CreateListMessageButton = Button::create();
    CreateListMessageButton->setText("Create ListMessage");
    CreateListMessageButton->setPreferredSize(Vec2f(100.0f,20.0f));
    CreateListMessageButton->connectActionPerformed(boost::bind(&StatePanelCreator::createListMessageDialogAction, this, _1));

    PanelRecPtr WindowPanel = Panel::create();
    FlowLayoutRecPtr WindowPanelLayout = FlowLayout::create();

    WindowPanel->setLayout(WindowPanelLayout);
    WindowPanel->pushToChildren(CreateWindowButton);
    WindowPanel->pushToChildren(CreateNoTitlebarWindowButton);
    WindowPanel->pushToChildren(CreateMessageButton);
    WindowPanel->pushToChildren(CreateColorChooserButton);
    WindowPanel->pushToChildren(CreateComboBoxMessageButton);
    WindowPanel->pushToChildren(CreateButtonsMessageButton);
    WindowPanel->pushToChildren(CreateTextboxMessageButton);
    WindowPanel->pushToChildren(CreateListMessageButton);
    WindowPanel->setPreferredSize(Vec2f(500,800));


    return WindowPanel;
}

PanelRecPtr StatePanelCreator::createAdvancedPanel(void)
{
    GridBagLayoutRecPtr AdvancedPanelLayout = GridBagLayout::create();
    AdvancedPanelLayout->setRows(6);
    AdvancedPanelLayout->setColumns(3);

    /******************************************************
      Row0
     ******************************************************/
    GridBagLayoutConstraintsRecPtr Constraint0000 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0100 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0200 = GridBagLayoutConstraints::create();

    Constraint0000->setGridX(0);
    Constraint0000->setGridY(0);

    Constraint0100->setGridX(1);
    Constraint0100->setGridY(0);

    Constraint0200->setGridX(2);
    Constraint0200->setGridY(0);

    /******************************************************
      Row1
     ******************************************************/
    GridBagLayoutConstraintsRecPtr Constraint0001 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0101 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0201 = GridBagLayoutConstraints::create();

    Constraint0001->setGridX(0);
    Constraint0001->setGridY(1);

    Constraint0101->setGridX(1);
    Constraint0101->setGridY(1);

    Constraint0201->setGridX(2);
    Constraint0201->setGridY(1);

    /******************************************************
      Row2
     ******************************************************/
    GridBagLayoutConstraintsRecPtr Constraint0002 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0102 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0202 = GridBagLayoutConstraints::create();

    Constraint0002->setGridX(0);
    Constraint0002->setGridY(2);

    Constraint0102->setGridX(1);
    Constraint0102->setGridY(2);

    Constraint0202->setGridX(2);
    Constraint0202->setGridY(2);


    /******************************************************
      Row3
     ******************************************************/
    GridBagLayoutConstraintsRecPtr Constraint0003 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0103 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0203 = GridBagLayoutConstraints::create();

    Constraint0003->setGridX(0);
    Constraint0003->setGridY(3);

    Constraint0103->setGridX(1);
    Constraint0103->setGridY(3);

    Constraint0203->setGridX(2);
    Constraint0203->setGridY(3);

    /******************************************************
      Row4
     ******************************************************/
    GridBagLayoutConstraintsRecPtr Constraint0004 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0104 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0204 = GridBagLayoutConstraints::create();

    Constraint0004->setGridX(0);
    Constraint0004->setGridY(4);

    Constraint0104->setGridX(1);
    Constraint0104->setGridY(4);

    Constraint0204->setGridX(2);
    Constraint0204->setGridY(4);

    /******************************************************
      Row5
     ******************************************************/
    GridBagLayoutConstraintsRecPtr Constraint0005 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0105 = GridBagLayoutConstraints::create();
    GridBagLayoutConstraintsRecPtr Constraint0205 = GridBagLayoutConstraints::create();

    Constraint0005->setGridX(0);
    Constraint0005->setGridY(5);

    Constraint0105->setGridX(1);
    Constraint0105->setGridY(5);

    Constraint0205->setGridX(2);
    Constraint0205->setGridY(5);

    //Progress Bar
    _ProgressBarBoundedRangeModel = DefaultBoundedRangeModel::create();
    _ProgressBarBoundedRangeModel->setMinimum(0);
    _ProgressBarBoundedRangeModel->setMaximum(100);
    _ProgressBarBoundedRangeModel->setValue(50);
    _ProgressBarBoundedRangeModel->setExtent(0);

    // Create the ProgressBar
    ProgressBarRecPtr ExampleProgressBar = ProgressBar::create();

    // Add its BoundedRangeModel
    ExampleProgressBar->setEnableProgressString(true);
    ExampleProgressBar->setIndeterminate(false);
    ExampleProgressBar->setOrientation(ProgressBar::HORIZONTAL_ORIENTATION);
    ExampleProgressBar->setProgressString("Loading...");
    ExampleProgressBar->setConstraints(Constraint0101);
    ExampleProgressBar->setMaxSize(ExampleProgressBar->getPreferredSize());
    ExampleProgressBar->setRangeModel(_ProgressBarBoundedRangeModel);


    ProgressBarRecPtr DisabledProgressBar = ProgressBar::create();
    DisabledProgressBar->setOrientation(ProgressBar::HORIZONTAL_ORIENTATION);
    DisabledProgressBar->setProgressString("Loading...");
    DisabledProgressBar->setMaxSize(ExampleProgressBar->getPreferredSize());
    DisabledProgressBar->setRangeModel(_ProgressBarBoundedRangeModel);
    DisabledProgressBar->setConstraints(Constraint0201);
    DisabledProgressBar->setEnabled(false);

    //Scrollbars
    _ScrollBarBoundedRangeModel = DefaultBoundedRangeModel::create();
    _ScrollBarBoundedRangeModel->setMinimum(10);
    _ScrollBarBoundedRangeModel->setMaximum(100);
    _ScrollBarBoundedRangeModel->setValue(10);
    _ScrollBarBoundedRangeModel->setExtent(20);

    ScrollBarRecPtr ExampleVerticalScrollBar = ScrollBar::create();
    //ExampleScrollPanel->getHorizontalScrollBar()
    ExampleVerticalScrollBar->setOrientation(ScrollBar::VERTICAL_ORIENTATION);
    ExampleVerticalScrollBar->setPreferredSize(Vec2f(20,200));
    ExampleVerticalScrollBar->setConstraints(Constraint0102);
    ExampleVerticalScrollBar->setMaxSize(ExampleVerticalScrollBar->getPreferredSize());
    ExampleVerticalScrollBar->setRangeModel(_ScrollBarBoundedRangeModel);

    ScrollBarRecPtr DisabledVerticalScrollBar = ScrollBar::create();
    DisabledVerticalScrollBar->setConstraints(Constraint0202);
    DisabledVerticalScrollBar->setEnabled(false);
    DisabledVerticalScrollBar->setOrientation(ScrollBar::VERTICAL_ORIENTATION);
    DisabledVerticalScrollBar->setPreferredSize(Vec2f(20,200));
    DisabledVerticalScrollBar->setMaxSize(ExampleVerticalScrollBar->getPreferredSize());
    DisabledVerticalScrollBar->setRangeModel(_ScrollBarBoundedRangeModel);

    ScrollBarRecPtr ExampleHorizontalScrollBar = ScrollBar::create();
    ExampleHorizontalScrollBar->setOrientation(ScrollBar::HORIZONTAL_ORIENTATION);
    ExampleHorizontalScrollBar->setPreferredSize(Vec2f(400,20));
    ExampleHorizontalScrollBar->setConstraints(Constraint0103);
    ExampleHorizontalScrollBar->setMaxSize(ExampleHorizontalScrollBar->getPreferredSize());
    ExampleHorizontalScrollBar->setRangeModel(_ScrollBarBoundedRangeModel);

    ScrollBarRecPtr DisabledHorizontalScrollBar = ScrollBar::create();
    DisabledHorizontalScrollBar->setConstraints(Constraint0203);
    DisabledHorizontalScrollBar->setEnabled(false);
    DisabledHorizontalScrollBar->setOrientation(ScrollBar::HORIZONTAL_ORIENTATION);
    DisabledHorizontalScrollBar->setPreferredSize(Vec2f(400,20));
    DisabledHorizontalScrollBar->setMaxSize(ExampleHorizontalScrollBar->getPreferredSize());
    DisabledHorizontalScrollBar->setRangeModel(_ScrollBarBoundedRangeModel);

    //The Slider
    _SliderBoundedRangeModel = DefaultBoundedRangeModel::create();
    _SliderBoundedRangeModel->setMinimum(10);
    _SliderBoundedRangeModel->setMaximum(110);
    _SliderBoundedRangeModel->setValue(60);
    _SliderBoundedRangeModel->setExtent(0);

    //Create the slider
    LabelRecPtr TempLabel;
    SliderRecPtr TheSliderVertical = Slider::create();
    TempLabel = dynamic_pointer_cast<Label>(TheSliderVertical->getLabelPrototype()->shallowCopy());
    TheSliderVertical->editLabelMap()[_SliderBoundedRangeModel->getMinimum()] = TempLabel;

    TempLabel = dynamic_pointer_cast<Label>(TheSliderVertical->getLabelPrototype()->shallowCopy());
    TheSliderVertical->editLabelMap()[_SliderBoundedRangeModel->getMinimum() + (_SliderBoundedRangeModel->getMaximum() - _SliderBoundedRangeModel->getMinimum())/10] = TempLabel;

    TempLabel = dynamic_pointer_cast<Label>(TheSliderVertical->getLabelPrototype()->shallowCopy());
    TheSliderVertical->editLabelMap()[_SliderBoundedRangeModel->getMaximum()] = TempLabel;


    TheSliderVertical->setPreferredSize(Vec2f(100, 300));
    TheSliderVertical->setSnapToTicks(true);
    TheSliderVertical->setMajorTickSpacing(10);
    TheSliderVertical->setMinorTickSpacing(5);
    TheSliderVertical->setOrientation(Slider::VERTICAL_ORIENTATION);
    TheSliderVertical->setInverted(true);
    TheSliderVertical->setDrawLabels(true);
    TheSliderVertical->setConstraints(Constraint0104);
    TheSliderVertical->setMaxSize(TheSliderVertical->getPreferredSize());
    TheSliderVertical->setRangeModel(_SliderBoundedRangeModel);

    SliderRecPtr DisabledVerticalSlider = Slider::create();
    DisabledVerticalSlider->setConstraints(Constraint0204);
    DisabledVerticalSlider->setEnabled(false);
    DisabledVerticalSlider->setPreferredSize(Vec2f(100, 300));
    DisabledVerticalSlider->setSnapToTicks(true);
    DisabledVerticalSlider->setMajorTickSpacing(10);
    DisabledVerticalSlider->setMinorTickSpacing(5);
    DisabledVerticalSlider->setOrientation(Slider::VERTICAL_ORIENTATION);
    DisabledVerticalSlider->setInverted(true);
    DisabledVerticalSlider->setDrawLabels(true);
    DisabledVerticalSlider->setMaxSize(DisabledVerticalSlider->getPreferredSize());
    DisabledVerticalSlider->setRangeModel(_SliderBoundedRangeModel);

    SliderRecPtr TheSliderHorizontal = Slider::create();
    TheSliderHorizontal->setPreferredSize(Vec2f(300, 100));
    TheSliderHorizontal->setSnapToTicks(false);
    TheSliderHorizontal->setMajorTickSpacing(10);
    TheSliderHorizontal->setMinorTickSpacing(5);
    TheSliderHorizontal->setOrientation(Slider::HORIZONTAL_ORIENTATION);
    TheSliderHorizontal->setInverted(false);
    TheSliderHorizontal->setDrawLabels(true);
    TheSliderHorizontal->setConstraints(Constraint0105);
    TheSliderHorizontal->setMaxSize(TheSliderHorizontal->getPreferredSize());
    TheSliderHorizontal->setRangeModel(_SliderBoundedRangeModel);

    SliderRecPtr DisabledHorizontalSlider = Slider::create();
    DisabledHorizontalSlider->setConstraints(Constraint0205);
    DisabledHorizontalSlider->setEnabled(false);
    DisabledHorizontalSlider->setPreferredSize(Vec2f(300, 100));
    DisabledHorizontalSlider->setSnapToTicks(false);
    DisabledHorizontalSlider->setMajorTickSpacing(10);
    DisabledHorizontalSlider->setMinorTickSpacing(5);
    DisabledHorizontalSlider->setOrientation(Slider::HORIZONTAL_ORIENTATION);
    DisabledHorizontalSlider->setInverted(false);
    DisabledHorizontalSlider->setDrawLabels(true);
    DisabledHorizontalSlider->setMaxSize(DisabledHorizontalSlider->getPreferredSize());
    DisabledHorizontalSlider->setRangeModel(_SliderBoundedRangeModel);

    //Labels
    LabelRecPtr labelEnabled = Label::create();
    labelEnabled->setText("Enabled");
    labelEnabled->setConstraints(Constraint0100);
    labelEnabled->setBackground(NULL);
    labelEnabled->setBorder(NULL);

    LabelRecPtr labelDisabled = Label::create();
    labelDisabled->setText("Disabled");
    labelDisabled->setConstraints(Constraint0200);
    labelDisabled->setBackground(NULL);
    labelDisabled->setBorder(NULL);

    LabelRecPtr labelProgressBar = Label::create();
    labelProgressBar->setText("Progress Bars");
    labelProgressBar->setConstraints(Constraint0001);
    labelProgressBar->setBackground(NULL);
    labelProgressBar->setBorder(NULL);

    LabelRecPtr labelVerticalScrolBar = Label::create();
    labelVerticalScrolBar->setText("Vertical Scroll Bars");
    labelVerticalScrolBar->setConstraints(Constraint0002);
    labelVerticalScrolBar->setBackground(NULL);
    labelVerticalScrolBar->setBorder(NULL);

    LabelRecPtr labelHorizontalScrolBar = Label::create();
    labelHorizontalScrolBar->setText("Horizontal Scroll Bars");
    labelHorizontalScrolBar->setConstraints(Constraint0003);
    labelHorizontalScrolBar->setBackground(NULL);
    labelHorizontalScrolBar->setBorder(NULL);

    LabelRecPtr labelVerticalSlider = Label::create();
    labelVerticalSlider->setText("Vertical Slider");
    labelVerticalSlider->setConstraints(Constraint0004);
    labelVerticalSlider->setBackground(NULL);
    labelVerticalSlider->setBorder(NULL);

    LabelRecPtr labelHorizontalSlider = Label::create();
    labelHorizontalSlider->setText("Horizontal Slider");
    labelHorizontalSlider->setConstraints(Constraint0005);
    labelHorizontalSlider->setBackground(NULL);
    labelHorizontalSlider->setBorder(NULL);

    //The Panel
    PanelRecPtr AdvancedPanel = Panel::create();

    AdvancedPanel->pushToChildren(labelEnabled);
    AdvancedPanel->pushToChildren(labelDisabled);
    AdvancedPanel->pushToChildren(labelProgressBar);
    AdvancedPanel->pushToChildren(labelVerticalScrolBar);
    AdvancedPanel->pushToChildren(labelHorizontalScrolBar);
    AdvancedPanel->pushToChildren(labelVerticalSlider);
    AdvancedPanel->pushToChildren(labelHorizontalSlider);
    AdvancedPanel->pushToChildren(ExampleProgressBar);
    AdvancedPanel->pushToChildren(ExampleVerticalScrollBar);
    AdvancedPanel->pushToChildren(ExampleHorizontalScrollBar);
    AdvancedPanel->pushToChildren(TheSliderVertical);
    AdvancedPanel->pushToChildren(TheSliderHorizontal);
    AdvancedPanel->pushToChildren(DisabledProgressBar);
    AdvancedPanel->pushToChildren(DisabledVerticalScrollBar);
    AdvancedPanel->pushToChildren(DisabledHorizontalScrollBar);
    AdvancedPanel->pushToChildren(DisabledVerticalSlider);
    AdvancedPanel->pushToChildren(DisabledHorizontalSlider);
    AdvancedPanel->setLayout(AdvancedPanelLayout);
    AdvancedPanel->setPreferredSize(Vec2f(500,800));
    return AdvancedPanel;
}

PanelRecPtr StatePanelCreator::createListPanel(void)
{
    // Add data to it
    _ExampleListModel = DefaultListModel::create();
    _ExampleListModel->pushBack(boost::any(std::string("Red")));
    _ExampleListModel->pushBack(boost::any(std::string("Green")));
    _ExampleListModel->pushBack(boost::any(std::string("Blue")));
    _ExampleListModel->pushBack(boost::any(std::string("Orange")));
    _ExampleListModel->pushBack(boost::any(std::string("Purple")));
    _ExampleListModel->pushBack(boost::any(std::string("Yellow")));
    _ExampleListModel->pushBack(boost::any(std::string("White")));
    _ExampleListModel->pushBack(boost::any(std::string("Black")));
    _ExampleListModel->pushBack(boost::any(std::string("Gray")));
    _ExampleListModel->pushBack(boost::any(std::string("Brown")));
    _ExampleListModel->pushBack(boost::any(std::string("Indigo")));
    _ExampleListModel->pushBack(boost::any(std::string("Pink")));
    _ExampleListModel->pushBack(boost::any(std::string("Violet")));
    _ExampleListModel->pushBack(boost::any(std::string("Mauve")));
    _ExampleListModel->pushBack(boost::any(std::string("Peach")));

    ListRecPtr ExampleList = List::create();
    ExampleList->setPreferredSize(Vec2f(200, 300));
    ExampleList->setOrientation(List::VERTICAL_ORIENTATION);
    //ExampleList->setOrientation(List::HORIZONTAL_ORIENTATION);
    ExampleList->setModel(_ExampleListModel);


    // Create a ScrollPanel for easier viewing of the List (see 27ScrollPanel)
    ScrollPanelRecPtr ExampleScrollPanel = ScrollPanel::create();
    ExampleScrollPanel->setPreferredSize(Vec2f(200,300));
    ExampleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    //ExampleScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    ExampleScrollPanel->setViewComponent(ExampleList);

    //The Panel
    PanelRecPtr ListPanel = Panel::create();
    ListPanel->pushToChildren(ExampleScrollPanel);
    LayoutRecPtr ListPanelLayout = FlowLayout::create();
    ListPanel->setLayout(ListPanelLayout);
    return ListPanel;
}

PanelRecPtr StatePanelCreator::createTablePanel(void)
{
    // Create TableRecPtr
    TableRecPtr TheTable = Table::create();
    TheTable->setPreferredSize(Vec2f(500, 500));
    TableModelRecPtr TheExampleTableModel = ExampleTableModel::create();
    TheTable->setModel(TheExampleTableModel);
    TheTable->updateLayout();

    /******************************************************

      Create a ScrollPanel to display the Table
      within (see 27ScrollPanel for more 
      information).

     ******************************************************/
    ScrollPanelRecPtr TheScrollPanel = ScrollPanel::create();
    TheScrollPanel->setPreferredSize(Vec2f(402,200));
    TheScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    TheScrollPanel->setViewComponent(TheTable);

    //The Panel
    PanelRecPtr TablePanel = Panel::create();
    TablePanel->pushToChildren(TheScrollPanel);
    LayoutRecPtr TablePanelLayout = FlowLayout::create();
    TablePanel->setLayout(TablePanelLayout);

    return TablePanel;
}

PanelRecPtr StatePanelCreator::createTreePanel(void)
{
    TreeRecPtr TheTree;

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

    //Tree Model
    DefaultTreeModelRecPtr TheTreeModel = DefaultTreeModel::create();
    TheTreeModel->setRoot(ANode);

    //Create the Tree
    TheTree = Tree::create();

    TheTree->setPreferredSize(Vec2f(100.0f, 500.0f));
    TheTree->setModel(TheTreeModel);

    //Layout Expansion
    TheTree->expandPath(TheTreeModel->getRootPath());

    // Create a ScrollPanel for easier viewing of the List (see 27ScrollPanel)
    ScrollPanelRecPtr TheScrollPanel = ScrollPanel::create();
    TheScrollPanel->setPreferredSize(Vec2f(200.0f,300.0f));
    TheScrollPanel->setViewComponent(TheTree);

    //The Panel
    PanelRecPtr TreePanel = Panel::create();
    TreePanel->pushToChildren(TheScrollPanel);
    LayoutRecPtr TreePanelLayout = FlowLayout::create();
    TreePanel->setLayout(TreePanelLayout);

    return TreePanel;
}

