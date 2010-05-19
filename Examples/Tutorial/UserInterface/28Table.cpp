// OpenSG Tutorial Example: Creating a List
//
// This tutorial explains how to create a List 
// via the  OSG User Interface library.
// 
// Includes: placing multiple buttons using Flow Layout

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

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);


// 28Table Headers
#include "OSGLookAndFeelManager.h"
#include "OSGColorLayer.h"
#include "OSGBevelBorder.h"
#include "OSGPanel.h"
#include "OSGLabel.h"
#include "OSGRadioButton.h"
#include "OSGCheckboxButton.h"
#include "OSGRadioButtonGroup.h"
#include "OSGDefaultListSelectionModel.h"
#include "OSGFlowLayout.h"
#include "OSGBoxLayout.h"
#include "OSGScrollPanel.h"

// Table header files
#include "OSGTable.h"
#include "OSGAbstractTableModel.h"

PanelRefPtr createSelectionModePanel(void);
PanelRefPtr createSelectionOptionPanel(void);
RadioButtonGroupRefPtr SelectionButtonGroup;

// Declare the Table so it can
// be referenced by ActionListeners
TableRefPtr table;
CheckboxButtonRefPtr CellSelectionButton;
CheckboxButtonRefPtr RowSelectionButton;
CheckboxButtonRefPtr ColumnSelectionButton;
/******************************************************

  Create ActionListeners to dynamically
  change the Table selection characteristics
  while running the program.

 ******************************************************/
class SingleSelectionListener : public ButtonSelectedListener
{
  public:

    virtual void buttonSelected(const ButtonSelectedEventUnrecPtr e)
    {
        table->getColumnModel()->getSelectionModel()->setSelectionMode(DefaultListSelectionModel::SINGLE_SELECTION);
        table->getSelectionModel()->setSelectionMode(DefaultListSelectionModel::SINGLE_SELECTION);

        CellSelectionButton->setEnabled(true);
    }

    virtual void buttonDeselected(const ButtonSelectedEventUnrecPtr e){}
};

class SingleIntervalSelectionListener : public ButtonSelectedListener
{
  public:

    virtual void buttonSelected(const ButtonSelectedEventUnrecPtr e)
    {
        table->getColumnModel()->getSelectionModel()->setSelectionMode(DefaultListSelectionModel::SINGLE_INTERVAL_SELECTION);
        table->getSelectionModel()->setSelectionMode(DefaultListSelectionModel::SINGLE_INTERVAL_SELECTION);
        CellSelectionButton->setEnabled(true);
    }

    virtual void buttonDeselected(const ButtonSelectedEventUnrecPtr e){}
};

class MultipleIntervalSelectionListener : public ButtonSelectedListener
{
  public:

    virtual void buttonSelected(const ButtonSelectedEventUnrecPtr e)
    {
        table->getColumnModel()->getSelectionModel()->setSelectionMode(DefaultListSelectionModel::MULTIPLE_INTERVAL_SELECTION);
        table->getSelectionModel()->setSelectionMode(DefaultListSelectionModel::MULTIPLE_INTERVAL_SELECTION);
        CellSelectionButton->setEnabled(false);
        CellSelectionButton->setSelected(false);
    }

    virtual void buttonDeselected(const ButtonSelectedEventUnrecPtr e){}
};

class RowSelectionListener : public ButtonSelectedListener
{
  public:

    virtual void buttonSelected(const ButtonSelectedEventUnrecPtr e)
    {
        table->setRowSelectionAllowed(true);
    }

    virtual void buttonDeselected(const ButtonSelectedEventUnrecPtr e)
    {
        table->setRowSelectionAllowed(false);
    }
};

class ColumnSelectionListener : public ButtonSelectedListener
{
  public:

    virtual void buttonSelected(const ButtonSelectedEventUnrecPtr e)
    {
        table->setColumnSelectionAllowed(true);
    }

    virtual void buttonDeselected(const ButtonSelectedEventUnrecPtr e)
    {
        table->setColumnSelectionAllowed(false);
    }
};

class CellSelectionListener : public ButtonSelectedListener
{
  public:

    virtual void buttonSelected(const ButtonSelectedEventUnrecPtr e)
    {
        RowSelectionButton->setSelected(true);
        ColumnSelectionButton->setSelected(true);
    }

    virtual void buttonDeselected(const ButtonSelectedEventUnrecPtr e)
    {
        RowSelectionButton->setSelected(false);
        ColumnSelectionButton->setSelected(false);
    }
};

// Create a class to allow for the use of the Ctrl+q
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

    TutorialWindow = createNativeWindow();
    TutorialWindow->initWindow();

    TutorialWindow->setDisplayCallback(display);
    TutorialWindow->setReshapeCallback(reshape);

    TutorialKeyListener TheKeyListener;
    TutorialWindow->addKeyListener(&TheKeyListener);


    // Make Torus Node (creates Torus in background of scene)
    NodeRefPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Main Scene Node and add the Torus
    NodeRefPtr scene = OSG::Node::create();
    scene->setCore(OSG::Group::create());
    scene->addChild(TorusGeometryNode);

    // Create the Graphics
    GraphicsRefPtr TutorialGraphics = OSG::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

    // Create TableRefPtr
    table = Table::create();
    table->setPreferredSize(Vec2f(500, 500));
    ExampleTableModelUnrecPtr TheTableModel(ExampleTableModel::create());
    table->setModel(TheTableModel);
    table->updateLayout();

    /******************************************************

      Create a ScrollPanel to display the Table
      within (see 27ScrollPanel for more 
      information).

     ******************************************************/
    ScrollPanelRefPtr TheScrollPanel = ScrollPanel::create();
    TheScrollPanel->setPreferredSize(Vec2f(402,200));
    TheScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    TheScrollPanel->setViewComponent(table);

    //Create the Selection Mode Panel
    PanelRefPtr SelectionModePanel = createSelectionModePanel();

    //Create the Selection Options Panel
    PanelRefPtr SelectionOptionPanel = createSelectionOptionPanel();

    // Create MainFramelayout
    FlowLayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();
    MainInternalWindowLayout->setOrientation(FlowLayout::HORIZONTAL_ORIENTATION);
    MainInternalWindowLayout->setMajorAxisAlignment(0.5f);
    MainInternalWindowLayout->setMinorAxisAlignment(0.5f);


    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
    MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
    MainInternalWindow->pushToChildren(TheScrollPanel);
    MainInternalWindow->pushToChildren(SelectionModePanel);
    MainInternalWindow->pushToChildren(SelectionOptionPanel);
    MainInternalWindow->setLayout(MainInternalWindowLayout);
    MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
    MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
    MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.85f,0.85f));
    MainInternalWindow->setDrawTitlebar(false);
    MainInternalWindow->setResizable(false);

    //Create the Drawing Surface
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
    mgr->setRoot(scene);

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
                               "28Table.");

    //Enter main Loop
    TutorialWindow->mainLoop();

    osgExit();

    return 0;
}

SingleSelectionListener TheSingleSelectionListener;
SingleIntervalSelectionListener TheSingleIntervalSelectionListener;
MultipleIntervalSelectionListener TheMultipleIntervalSelectionListener;

PanelRefPtr createSelectionModePanel(void)
{

    //Label
    LabelRefPtr SelectionModeLabel = Label::create();
    SelectionModeLabel->setText("Selection Mode");
    SelectionModeLabel->setAlignment(Vec2f(0.0,0.5));

    //Buttons
    RadioButtonRefPtr SingleSelectionButton = RadioButton::create();
    SingleSelectionButton->setText("Single Selection");
    SingleSelectionButton->setSelected(true);
    SingleSelectionButton->setPreferredSize(Vec2f(180,30));
    SingleSelectionButton->setAlignment(Vec2f(0.0,0.5));
    SingleSelectionButton->addButtonSelectedListener(&TheSingleSelectionListener);

    RadioButtonRefPtr SingleIntervalSelectionButton = RadioButton::create();
    SingleIntervalSelectionButton->setText("Single Interval Selection");
    SingleIntervalSelectionButton->setPreferredSize(Vec2f(180,30));
    SingleIntervalSelectionButton->setAlignment(Vec2f(0.0,0.5));
    SingleIntervalSelectionButton->addButtonSelectedListener(&TheSingleIntervalSelectionListener);

    RadioButtonRefPtr MultipleIntervalSelectionButton = RadioButton::create();
    MultipleIntervalSelectionButton->setText("Multiple Interval Selection");
    MultipleIntervalSelectionButton->setPreferredSize(Vec2f(180,30));
    MultipleIntervalSelectionButton->setAlignment(Vec2f(0.0,0.5));
    MultipleIntervalSelectionButton->addButtonSelectedListener(&TheMultipleIntervalSelectionListener);

    SelectionButtonGroup = RadioButtonGroup::create();
    SelectionButtonGroup->addButton(SingleSelectionButton);
    SelectionButtonGroup->addButton(SingleIntervalSelectionButton);
    SelectionButtonGroup->addButton(MultipleIntervalSelectionButton);

    //Box Layout
    BoxLayoutRefPtr PanelLayout = BoxLayout::create();
    PanelLayout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);
    PanelLayout->setMinorAxisAlignment(0.5f);


    //The Panel
    PanelRefPtr ThePanel = Panel::create();
    ThePanel->pushToChildren(SelectionModeLabel);
    ThePanel->pushToChildren(SingleSelectionButton);
    ThePanel->pushToChildren(SingleIntervalSelectionButton);
    ThePanel->pushToChildren(MultipleIntervalSelectionButton);
    ThePanel->setLayout(PanelLayout);
    ThePanel->setPreferredSize(Vec2f(300, 200));
    return ThePanel;
}

RowSelectionListener TheRowSelectionListener;
ColumnSelectionListener TheColumnSelectionListener;
CellSelectionListener TheCellSelectionListener;

PanelRefPtr createSelectionOptionPanel(void)
{
    //Label
    LabelRefPtr SelectionOptionLabel = Label::create();
    SelectionOptionLabel->setText("Selection Options");
    SelectionOptionLabel->setAlignment(Vec2f(0.0,0.5));

    //Buttons
    RowSelectionButton = CheckboxButton::create();
    RowSelectionButton->setText("Row Selection");
    RowSelectionButton->setPreferredSize(Vec2f(180,30));
    RowSelectionButton->setAlignment(Vec2f(0.0,0.5));
    RowSelectionButton->setSelected(true);
    RowSelectionButton->addButtonSelectedListener(&TheRowSelectionListener);

    ColumnSelectionButton = CheckboxButton::create();
    ColumnSelectionButton->setText("Column Selection");
    ColumnSelectionButton->setPreferredSize(Vec2f(180,30));
    ColumnSelectionButton->setAlignment(Vec2f(0.0,0.5));
    ColumnSelectionButton->setSelected(true);
    ColumnSelectionButton->addButtonSelectedListener(&TheColumnSelectionListener);


    CellSelectionButton = CheckboxButton::create();
    CellSelectionButton->setText("Cell Selection");
    CellSelectionButton->setPreferredSize(Vec2f(180,30));
    CellSelectionButton->setAlignment(Vec2f(0.0,0.5));
    CellSelectionButton->setSelected(false);
    CellSelectionButton->addButtonSelectedListener(&TheCellSelectionListener);

    //Box Layout
    BoxLayoutRefPtr PanelLayout = BoxLayout::create();
    PanelLayout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);
    PanelLayout->setMinorAxisAlignment(0.5f);


    //The Panel
    PanelRefPtr ThePanel = Panel::create();
    ThePanel->pushToChildren(SelectionOptionLabel);
    ThePanel->pushToChildren(RowSelectionButton);
    ThePanel->pushToChildren(ColumnSelectionButton);
    ThePanel->pushToChildren(CellSelectionButton);
    ThePanel->setLayout(PanelLayout);
    ThePanel->setPreferredSize(Vec2f(300, 200));
    return ThePanel;
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
