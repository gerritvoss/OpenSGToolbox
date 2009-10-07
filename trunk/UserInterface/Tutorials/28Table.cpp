// OpenSG Tutorial Example: Creating a List
//
// This tutorial explains how to create a List 
// via the  OSG User Interface library.
// 
// Includes: placing multiple buttons using Flow Layout

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>

// The general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

// Input
#include <OpenSG/Input/OSGWindowUtils.h>

// UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);


// 28Table Headers
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGColorLayer.h>
#include <OpenSG/UserInterface/OSGBevelBorder.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGRadioButton.h>
#include <OpenSG/UserInterface/OSGCheckboxButton.h>
#include <OpenSG/UserInterface/OSGRadioButtonGroup.h>
#include <OpenSG/UserInterface/OSGDefaultListSelectionModel.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGBoxLayout.h>
#include <OpenSG/UserInterface/OSGScrollPanel.h>

// Table header files
#include <OpenSG/UserInterface/OSGTable.h>
#include <OpenSG/UserInterface/OSGAbstractTableModel.h>

PanelPtr createSelectionModePanel(void);
PanelPtr createSelectionOptionPanel(void);
RadioButtonGroup SelectionButtonGroup;

// Declare the Table so it can
// be referenced by ActionListeners
TablePtr table;
CheckboxButtonPtr CellSelectionButton;
CheckboxButtonPtr RowSelectionButton;
CheckboxButtonPtr ColumnSelectionButton;
    /******************************************************

        Create ActionListeners to dynamically
        change the Table selection characteristics
        while running the program.

    ******************************************************/
class SingleSelectionListener : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEventPtr e)
    {
        table->getColumnModel()->getSelectionModel()->setSelectionMode(DefaultListSelectionModel::SINGLE_SELECTION);
        table->getSelectionModel()->setSelectionMode(DefaultListSelectionModel::SINGLE_SELECTION);

        beginEditCP(CellSelectionButton, CheckboxButton::EnabledFieldMask);
            CellSelectionButton->setEnabled(true);
        endEditCP(CellSelectionButton, CheckboxButton::EnabledFieldMask);
   }

    virtual void buttonDeselected(const ButtonSelectedEventPtr e){}
};

class SingleIntervalSelectionListener : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEventPtr e)
    {
        table->getColumnModel()->getSelectionModel()->setSelectionMode(DefaultListSelectionModel::SINGLE_INTERVAL_SELECTION);
        table->getSelectionModel()->setSelectionMode(DefaultListSelectionModel::SINGLE_INTERVAL_SELECTION);
        beginEditCP(CellSelectionButton, CheckboxButton::EnabledFieldMask);
            CellSelectionButton->setEnabled(true);
        endEditCP(CellSelectionButton, CheckboxButton::EnabledFieldMask);
   }

    virtual void buttonDeselected(const ButtonSelectedEventPtr e){}
};

class MultipleIntervalSelectionListener : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEventPtr e)
    {
        table->getColumnModel()->getSelectionModel()->setSelectionMode(DefaultListSelectionModel::MULTIPLE_INTERVAL_SELECTION);
        table->getSelectionModel()->setSelectionMode(DefaultListSelectionModel::MULTIPLE_INTERVAL_SELECTION);
        beginEditCP(CellSelectionButton, CheckboxButton::EnabledFieldMask | CheckboxButton::SelectedFieldMask);
            CellSelectionButton->setEnabled(false);
            CellSelectionButton->setSelected(false);
        endEditCP(CellSelectionButton, CheckboxButton::EnabledFieldMask | CheckboxButton::SelectedFieldMask);
   }

    virtual void buttonDeselected(const ButtonSelectedEventPtr e){}
};

class RowSelectionListener : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEventPtr e)
    {
        beginEditCP(table, Table::RowSelectionAllowedFieldMask);
            table->setRowSelectionAllowed(true);
        endEditCP(table, Table::RowSelectionAllowedFieldMask);
   }

    virtual void buttonDeselected(const ButtonSelectedEventPtr e)
    {
        beginEditCP(table, Table::RowSelectionAllowedFieldMask);
            table->setRowSelectionAllowed(false);
        endEditCP(table, Table::RowSelectionAllowedFieldMask);
    }
};

class ColumnSelectionListener : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEventPtr e)
    {
        table->setColumnSelectionAllowed(true);
   }

    virtual void buttonDeselected(const ButtonSelectedEventPtr e)
    {
        table->setColumnSelectionAllowed(false);
    }
};

class CellSelectionListener : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEventPtr e)
   {
       beginEditCP(RowSelectionButton, CheckboxButton::SelectedFieldMask);
          RowSelectionButton->setSelected(true);
       endEditCP(RowSelectionButton, CheckboxButton::SelectedFieldMask);
       beginEditCP(ColumnSelectionButton, CheckboxButton::SelectedFieldMask);
          ColumnSelectionButton->setSelected(true);
       endEditCP(ColumnSelectionButton, CheckboxButton::SelectedFieldMask);
   }

    virtual void buttonDeselected(const ButtonSelectedEventPtr e)
    {
       beginEditCP(RowSelectionButton, CheckboxButton::SelectedFieldMask);
          RowSelectionButton->setSelected(false);
       endEditCP(RowSelectionButton, CheckboxButton::SelectedFieldMask);
       beginEditCP(ColumnSelectionButton, CheckboxButton::SelectedFieldMask);
          ColumnSelectionButton->setSelected(false);
       endEditCP(ColumnSelectionButton, CheckboxButton::SelectedFieldMask);
    }
};

// Create a class to allow for the use of the Ctrl+q
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

class ExampleTableModel : public AbstractTableModel
{
  public:
    typedef          AbstractTableModel Inherited;
    typedef          ExampleTableModel Self;
	typedef          FCPtr<Inherited::Ptr,  Self      > PtrType;

	OSG_FIELD_CONTAINER_DECL(PtrType)
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
};

FieldContainerType ExampleTableModel::_type("ExampleTableModel",
                                     "AbstractTableModel",
                                      NULL,
                                      (PrototypeCreateF) &ExampleTableModel::createEmpty,
                                      NULL,
									  NULL,
                                      0);

OSG_FIELD_CONTAINER_INL_DEF(ExampleTableModel::Self, ExampleTableModel::PtrType)
OSG_FIELD_CONTAINER_DEF(ExampleTableModel::Self, ExampleTableModel::PtrType)
typedef ExampleTableModel::PtrType ExampleTableModelPtr;

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    TutorialKeyListener TheKeyListener;
    TutorialWindowEventProducer->addKeyListener(&TheKeyListener);


    // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Main Scene Node and add the Torus
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
        scene->addChild(TorusGeometryNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    // Create the Graphics
    GraphicsPtr TutorialGraphics = osg::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

    // Create TablePtr
    table = Table::create();
    beginEditCP(table, Table::PreferredSizeFieldMask | Table::ModelFieldMask);
        table->setPreferredSize(Vec2f(500, 500));
        table->setModel(ExampleTableModel::create());
    endEditCP(table, Table::PreferredSizeFieldMask | Table::ModelFieldMask);
    table->updateLayout();

    /******************************************************

        Create a ScrollPanel to display the Table
        within (see 27ScrollPanel for more 
        information).

    ******************************************************/
    ScrollPanelPtr TheScrollPanel = ScrollPanel::create();
    beginEditCP(TheScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        TheScrollPanel->setPreferredSize(Vec2f(402,200));
        TheScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(TheScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    TheScrollPanel->setViewComponent(table);

    //Create the Selection Mode Panel
    PanelPtr SelectionModePanel = createSelectionModePanel();

    //Create the Selection Options Panel
    PanelPtr SelectionOptionPanel = createSelectionOptionPanel();

    // Create MainFramelayout
    FlowLayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();
    beginEditCP(MainInternalWindowLayout, FlowLayout::OrientationFieldMask | FlowLayout::MajorAxisAlignmentFieldMask | FlowLayout::MinorAxisAlignmentFieldMask);
	MainInternalWindowLayout->setOrientation(FlowLayout::HORIZONTAL_ORIENTATION);
        MainInternalWindowLayout->setMajorAxisAlignment(0.5f);
        MainInternalWindowLayout->setMinorAxisAlignment(0.5f);
    endEditCP(MainInternalWindowLayout, FlowLayout::OrientationFieldMask | FlowLayout::MajorAxisAlignmentFieldMask | FlowLayout::MinorAxisAlignmentFieldMask);
        

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().push_back(TheScrollPanel);
       MainInternalWindow->getChildren().push_back(SelectionModePanel);
       MainInternalWindow->getChildren().push_back(SelectionOptionPanel);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.85f,0.85f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
    endEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);

    //Create the Drawing Surface
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
    mgr->setRoot(scene);

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

SingleSelectionListener TheSingleSelectionListener;
SingleIntervalSelectionListener TheSingleIntervalSelectionListener;
MultipleIntervalSelectionListener TheMultipleIntervalSelectionListener;

PanelPtr createSelectionModePanel(void)
{

    //Label
    LabelPtr SelectionModeLabel = Label::create();
    beginEditCP(SelectionModeLabel, Label::TextFieldMask | Label::AlignmentFieldMask);
        SelectionModeLabel->setText("Selection Mode");
        SelectionModeLabel->setAlignment(Vec2f(0.0,0.5));
    endEditCP(SelectionModeLabel, Label::TextFieldMask | Label::AlignmentFieldMask);

    //Buttons
    RadioButtonPtr SingleSelectionButton = RadioButton::create();
    beginEditCP(SingleSelectionButton, RadioButton::TextFieldMask | RadioButton::PreferredSizeFieldMask | RadioButton::SelectedFieldMask | RadioButton::AlignmentFieldMask);
        SingleSelectionButton->setText("Single Selection");
        SingleSelectionButton->setSelected(true);
        SingleSelectionButton->setPreferredSize(Vec2f(180,30));
        SingleSelectionButton->setAlignment(Vec2f(0.0,0.5));
    endEditCP(SingleSelectionButton, RadioButton::TextFieldMask | RadioButton::PreferredSizeFieldMask | RadioButton::SelectedFieldMask | RadioButton::AlignmentFieldMask);
    SingleSelectionButton->addButtonSelectedListener(&TheSingleSelectionListener);
    
    RadioButtonPtr SingleIntervalSelectionButton = RadioButton::create();
    beginEditCP(SingleIntervalSelectionButton, RadioButton::TextFieldMask | RadioButton::PreferredSizeFieldMask | RadioButton::AlignmentFieldMask);
        SingleIntervalSelectionButton->setText("Single Interval Selection");
        SingleIntervalSelectionButton->setPreferredSize(Vec2f(180,30));
        SingleIntervalSelectionButton->setAlignment(Vec2f(0.0,0.5));
    endEditCP(SingleIntervalSelectionButton, RadioButton::TextFieldMask | RadioButton::PreferredSizeFieldMask | RadioButton::AlignmentFieldMask);
    SingleIntervalSelectionButton->addButtonSelectedListener(&TheSingleIntervalSelectionListener);

    RadioButtonPtr MultipleIntervalSelectionButton = RadioButton::create();
    beginEditCP(MultipleIntervalSelectionButton, RadioButton::TextFieldMask | RadioButton::PreferredSizeFieldMask | RadioButton::AlignmentFieldMask);
        MultipleIntervalSelectionButton->setText("Multiple Interval Selection");
        MultipleIntervalSelectionButton->setPreferredSize(Vec2f(180,30));
        MultipleIntervalSelectionButton->setAlignment(Vec2f(0.0,0.5));
    endEditCP(MultipleIntervalSelectionButton, RadioButton::TextFieldMask | RadioButton::PreferredSizeFieldMask | RadioButton::AlignmentFieldMask);
    MultipleIntervalSelectionButton->addButtonSelectedListener(&TheMultipleIntervalSelectionListener);

    SelectionButtonGroup.addButton(SingleSelectionButton);
    SelectionButtonGroup.addButton(SingleIntervalSelectionButton);
    SelectionButtonGroup.addButton(MultipleIntervalSelectionButton);

    //Box Layout
    BoxLayoutPtr PanelLayout = BoxLayout::create();
    beginEditCP(PanelLayout, BoxLayout::MinorAxisAlignmentFieldMask | BoxLayout::OrientationFieldMask);
        PanelLayout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);
        PanelLayout->setMinorAxisAlignment(0.5f);
    endEditCP(PanelLayout, BoxLayout::MinorAxisAlignmentFieldMask | BoxLayout::OrientationFieldMask);


    //The Panel
    PanelPtr ThePanel = Panel::create();
    beginEditCP(ThePanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);
        ThePanel->getChildren().push_back(SelectionModeLabel);
        ThePanel->getChildren().push_back(SingleSelectionButton);
        ThePanel->getChildren().push_back(SingleIntervalSelectionButton);
        ThePanel->getChildren().push_back(MultipleIntervalSelectionButton);
        ThePanel->setLayout(PanelLayout);
        ThePanel->setPreferredSize(Vec2f(300, 200));
    endEditCP(ThePanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);
    return ThePanel;
}

RowSelectionListener TheRowSelectionListener;
ColumnSelectionListener TheColumnSelectionListener;
CellSelectionListener TheCellSelectionListener;

PanelPtr createSelectionOptionPanel(void)
{
    //Label
    LabelPtr SelectionOptionLabel = Label::create();
    beginEditCP(SelectionOptionLabel, Label::TextFieldMask | Label::AlignmentFieldMask);
        SelectionOptionLabel->setText("Selection Options");
        SelectionOptionLabel->setAlignment(Vec2f(0.0,0.5));
    endEditCP(SelectionOptionLabel, Label::TextFieldMask | Label::AlignmentFieldMask);

    //Buttons
    RowSelectionButton = CheckboxButton::create();
    beginEditCP(RowSelectionButton, CheckboxButton::TextFieldMask | CheckboxButton::PreferredSizeFieldMask | CheckboxButton::AlignmentFieldMask | CheckboxButton::SelectedFieldMask );
        RowSelectionButton->setText("Row Selection");
        RowSelectionButton->setPreferredSize(Vec2f(180,30));
        RowSelectionButton->setAlignment(Vec2f(0.0,0.5));
        RowSelectionButton->setSelected(true);
    endEditCP(RowSelectionButton, CheckboxButton::TextFieldMask | CheckboxButton::PreferredSizeFieldMask | CheckboxButton::AlignmentFieldMask | CheckboxButton::SelectedFieldMask );
    RowSelectionButton->addButtonSelectedListener(&TheRowSelectionListener);

    ColumnSelectionButton = CheckboxButton::create();
    beginEditCP(ColumnSelectionButton, CheckboxButton::TextFieldMask | CheckboxButton::PreferredSizeFieldMask | CheckboxButton::SelectedFieldMask | CheckboxButton::AlignmentFieldMask);
        ColumnSelectionButton->setText("Column Selection");
        ColumnSelectionButton->setPreferredSize(Vec2f(180,30));
        ColumnSelectionButton->setAlignment(Vec2f(0.0,0.5));
        ColumnSelectionButton->setSelected(true);
    endEditCP(ColumnSelectionButton, CheckboxButton::TextFieldMask | CheckboxButton::PreferredSizeFieldMask | CheckboxButton::SelectedFieldMask | CheckboxButton::AlignmentFieldMask);
    ColumnSelectionButton->addButtonSelectedListener(&TheColumnSelectionListener);
    

    CellSelectionButton = CheckboxButton::create();
    beginEditCP(CellSelectionButton, CheckboxButton::TextFieldMask | CheckboxButton::PreferredSizeFieldMask | CheckboxButton::AlignmentFieldMask | CheckboxButton::SelectedFieldMask);
        CellSelectionButton->setText("Cell Selection");
        CellSelectionButton->setPreferredSize(Vec2f(180,30));
        CellSelectionButton->setAlignment(Vec2f(0.0,0.5));
        CellSelectionButton->setSelected(false);
    endEditCP(CellSelectionButton, CheckboxButton::TextFieldMask | CheckboxButton::PreferredSizeFieldMask | CheckboxButton::AlignmentFieldMask | CheckboxButton::SelectedFieldMask);
    CellSelectionButton->addButtonSelectedListener(&TheCellSelectionListener);

    //Box Layout
    BoxLayoutPtr PanelLayout = BoxLayout::create();
    beginEditCP(PanelLayout, BoxLayout::MinorAxisAlignmentFieldMask | BoxLayout::OrientationFieldMask);
        PanelLayout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);
        PanelLayout->setMinorAxisAlignment(0.5f);
    endEditCP(PanelLayout, BoxLayout::MinorAxisAlignmentFieldMask | BoxLayout::OrientationFieldMask);


    //The Panel
    PanelPtr ThePanel = Panel::create();
    beginEditCP(ThePanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);
        ThePanel->getChildren().push_back(SelectionOptionLabel);
        ThePanel->getChildren().push_back(RowSelectionButton);
        ThePanel->getChildren().push_back(ColumnSelectionButton);
        ThePanel->getChildren().push_back(CellSelectionButton);
        ThePanel->setLayout(PanelLayout);
        ThePanel->setPreferredSize(Vec2f(300, 200));
    endEditCP(ThePanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);
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
