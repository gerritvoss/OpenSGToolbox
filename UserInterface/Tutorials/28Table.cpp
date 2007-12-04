// OpenSG Tutorial Example: Creating a List
//
// This tutorial explains how to create a List 
// via the  OSG User Interface library.
// 
// Includes: placing multiple buttons using Flow Layout


// GLUT is used for window handling
#include <OpenSG/OSGGLUT.h>

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// The GLUT-OpenSG connection class
#include <OpenSG/OSGGLUTWindow.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/Input/OSGWindowAdapter.h>

// The general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

// Input
#include <OpenSG/Input/OSGWindowUtils.h>

// UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

bool ExitApp = false;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2s Size);


// 28Table Headers
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
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

   virtual void buttonSelected(const ButtonSelectedEvent& e)
	{
        table->getColumnModel()->getSelectionModel()->setSelectionMode(DefaultListSelectionModel::SINGLE_SELECTION);
        table->getSelectionModel()->setSelectionMode(DefaultListSelectionModel::SINGLE_SELECTION);

        beginEditCP(CellSelectionButton, CheckboxButton::EnabledFieldMask);
            CellSelectionButton->setEnabled(true);
        endEditCP(CellSelectionButton, CheckboxButton::EnabledFieldMask);
   }

    virtual void buttonDeselected(const ButtonSelectedEvent& e){}
};

class SingleIntervalSelectionListener : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
	{
        table->getColumnModel()->getSelectionModel()->setSelectionMode(DefaultListSelectionModel::SINGLE_INTERVAL_SELECTION);
        table->getSelectionModel()->setSelectionMode(DefaultListSelectionModel::SINGLE_INTERVAL_SELECTION);
        beginEditCP(CellSelectionButton, CheckboxButton::EnabledFieldMask);
            CellSelectionButton->setEnabled(true);
        endEditCP(CellSelectionButton, CheckboxButton::EnabledFieldMask);
   }

    virtual void buttonDeselected(const ButtonSelectedEvent& e){}
};

class MultipleIntervalSelectionListener : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
	{
        table->getColumnModel()->getSelectionModel()->setSelectionMode(DefaultListSelectionModel::MULTIPLE_INTERVAL_SELECTION);
        table->getSelectionModel()->setSelectionMode(DefaultListSelectionModel::MULTIPLE_INTERVAL_SELECTION);
        beginEditCP(CellSelectionButton, CheckboxButton::EnabledFieldMask | CheckboxButton::SelectedFieldMask);
            CellSelectionButton->setEnabled(false);
            CellSelectionButton->setSelected(false);
        endEditCP(CellSelectionButton, CheckboxButton::EnabledFieldMask | CheckboxButton::SelectedFieldMask);
   }

    virtual void buttonDeselected(const ButtonSelectedEvent& e){}
};

class RowSelectionListener : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
	{
        beginEditCP(table, Table::RowSelectionAllowedFieldMask);
            table->setRowSelectionAllowed(true);
        endEditCP(table, Table::RowSelectionAllowedFieldMask);
   }

    virtual void buttonDeselected(const ButtonSelectedEvent& e)
    {
        beginEditCP(table, Table::RowSelectionAllowedFieldMask);
            table->setRowSelectionAllowed(false);
        endEditCP(table, Table::RowSelectionAllowedFieldMask);
    }
};

class ColumnSelectionListener : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
	{
        table->setColumnSelectionAllowed(true);
   }

    virtual void buttonDeselected(const ButtonSelectedEvent& e)
    {
        table->setColumnSelectionAllowed(false);
    }
};

class CellSelectionListener : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
   {
       beginEditCP(RowSelectionButton, CheckboxButton::SelectedFieldMask);
          RowSelectionButton->setSelected(true);
       endEditCP(RowSelectionButton, CheckboxButton::SelectedFieldMask);
       beginEditCP(ColumnSelectionButton, CheckboxButton::SelectedFieldMask);
          ColumnSelectionButton->setSelected(true);
       endEditCP(ColumnSelectionButton, CheckboxButton::SelectedFieldMask);
   }

    virtual void buttonDeselected(const ButtonSelectedEvent& e)
    {
       beginEditCP(RowSelectionButton, CheckboxButton::SelectedFieldMask);
          RowSelectionButton->setSelected(false);
       endEditCP(RowSelectionButton, CheckboxButton::SelectedFieldMask);
       beginEditCP(ColumnSelectionButton, CheckboxButton::SelectedFieldMask);
          ColumnSelectionButton->setSelected(false);
       endEditCP(ColumnSelectionButton, CheckboxButton::SelectedFieldMask);
    }
};

class TutorialWindowListener : public WindowAdapter
{
public:
    virtual void windowClosing(const WindowEvent& e)
    {
        ExitApp = true;
    }

    virtual void windowClosed(const WindowEvent& e)
    {
        ExitApp = true;
    }
};

class ExampleTableModel : public AbstractTableModel
{
private:
	// Creates two vectors to store column/cell values in
    std::vector<SharedFieldPtr> _ColumnValues;
    std::vector<SharedFieldPtr> _CellValues;
public:

	// Creates some functions to do what the Table requires to be done
	// and which are needed for a non-basic table
    virtual UInt32 getColumnCount(void) const
    {
        return _ColumnValues.size();
    }
    
    virtual SharedFieldPtr getColumnValue(UInt32 columnIndex) const
    {
        return _ColumnValues[columnIndex];
    }
    
    virtual UInt32 getRowCount(void) const
    {
        return _CellValues.size() / _ColumnValues.size();
    }
    
    virtual SharedFieldPtr getValueAt(UInt32 rowIndex, UInt32 columnIndex) const
    {
        return _CellValues[rowIndex*_ColumnValues.size() + columnIndex];
    }
    
    virtual bool isCellEditable(UInt32 rowIndex, UInt32 columnIndex) const
    {
		// Only returns true if the column is 0; means cell is editable, otherwise, returns false and cell is not editable
        return columnIndex == 0;
    }
    
    virtual void setValueAt(SharedFieldPtr aValue, UInt32 rowIndex, UInt32 columnIndex)
    {
		// 
        if(columnIndex == 0 && aValue->getType() == SFString::getClassType())
        {
            std::string TempString;
            aValue->getValueByStr(TempString);
            dynamic_cast<SFString*>(_CellValues[rowIndex*getColumnCount() + columnIndex].get())->setValue(dynamic_cast<SFString*>(aValue.get())->getValue());
        }
    }

    virtual const FieldType* getColumnType(const UInt32& columnIndex)
    {
        return NULL;
    }

	/******************************************************

		Create the Table values

	******************************************************/

    ExampleTableModel()
    {
		// Creates the lists within column/cell values and adds data (1d representation of 2d array basically)
        _ColumnValues.push_back(SharedFieldPtr(new SFString("Column String")));
        _ColumnValues.push_back(SharedFieldPtr(new SFString("Column Integer")));
        _ColumnValues.push_back(SharedFieldPtr(new SFString("Column GLenum")));
        _ColumnValues.push_back(SharedFieldPtr(new SFString("Column Boolean")));
        _ColumnValues.push_back(SharedFieldPtr(new SFString("Column Pnt3f")));
        
        _CellValues.push_back(SharedFieldPtr(new SFString("A")));
        _CellValues.push_back(SharedFieldPtr(new SFInt32(1)));
        _CellValues.push_back(SharedFieldPtr(new SFGLenum(GL_SRC_ALPHA)));
        _CellValues.push_back(SharedFieldPtr(new SFBool(true)));
        _CellValues.push_back(SharedFieldPtr(new SFPnt3f(Pnt3f(1.0,0.0,0.0))));
        
        _CellValues.push_back(SharedFieldPtr(new SFString("B")));
        _CellValues.push_back(SharedFieldPtr(new SFInt32(2)));
        _CellValues.push_back(SharedFieldPtr(new SFGLenum(GL_NICEST)));
        _CellValues.push_back(SharedFieldPtr(new SFBool(false)));
        _CellValues.push_back(SharedFieldPtr(new SFPnt3f(Pnt3f(0.0,1.0,0.0))));
        
        _CellValues.push_back(SharedFieldPtr(new SFString("C")));
        _CellValues.push_back(SharedFieldPtr(new SFInt32(3)));
        _CellValues.push_back(SharedFieldPtr(new SFGLenum(GL_CCW)));
        _CellValues.push_back(SharedFieldPtr(new SFBool(true)));
        _CellValues.push_back(SharedFieldPtr(new SFPnt3f(Pnt3f(0.0,0.0,1.0))));

        _CellValues.push_back(SharedFieldPtr(new SFString("D")));
        _CellValues.push_back(SharedFieldPtr(new SFInt32(4)));
        _CellValues.push_back(SharedFieldPtr(new SFGLenum(GL_CW)));
        _CellValues.push_back(SharedFieldPtr(new SFBool(false)));
        _CellValues.push_back(SharedFieldPtr(new SFPnt3f(Pnt3f(1.0,1.0,1.0))));
    }

    ~ExampleTableModel()
    {
    }
};


int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    WindowEventProducerPtr TheWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TheWindowEventProducer->initWindow();
    
    TheWindowEventProducer->setDisplayCallback(display);
    TheWindowEventProducer->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TheWindowEventProducer->addWindowListener(&TheTutorialWindowListener);


    // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Main Scene Node
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        scene->setCore(osg::Group::create());
 
        // add the torus as a child
        scene->addChild(TorusGeometryNode);
    }
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

	// Create the Graphics
	GraphicsPtr graphics = osg::Graphics2D::create();

	// Initialize the LookAndFeelManager to enable default 
	// settings for the Button
	LookAndFeelManager::the()->getLookAndFeel()->init();

	// Create TablePtr
	table = Table::create();
    table->setModel(TableModelPtr(new ExampleTableModel()));
    beginEditCP(table, Table::PreferredSizeFieldMask);
		table->setPreferredSize( Vec2s (500, 500) );
	endEditCP(table, Table::PreferredSizeFieldMask);
    table->updateLayout();

	/******************************************************

		Create a ScrollPanel to display the Table
		within (see 27ScrollPanel for more 
		information).

	******************************************************/
    ScrollPanelPtr TheScrollPanel = ScrollPanel::create();
    beginEditCP(TheScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
	    TheScrollPanel->setPreferredSize(Vec2s(402,200));
        TheScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(TheScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    TheScrollPanel->setViewComponent(table);

    //Create the Selection Mode Panel
    PanelPtr SelectionModePanel = createSelectionModePanel();

    //Create the Selection Options Panel
    PanelPtr SelectionOptionPanel = createSelectionOptionPanel();

	// Create MainFramelayout
	FlowLayoutPtr MainFrameLayout = osg::FlowLayout::create();
	beginEditCP(MainFrameLayout, FlowLayout::AlignmentFieldMask | FlowLayout::MajorAxisAlignmentFieldMask | FlowLayout::MinorAxisAlignmentFieldMask);
		MainFrameLayout->setAlignment(HORIZONTAL_ALIGNMENT);
		MainFrameLayout->setMajorAxisAlignment(AXIS_CENTER_ALIGNMENT);
		MainFrameLayout->setMinorAxisAlignment(AXIS_CENTER_ALIGNMENT);
	endEditCP(MainFrameLayout, FlowLayout::AlignmentFieldMask | FlowLayout::MajorAxisAlignmentFieldMask | FlowLayout::MinorAxisAlignmentFieldMask);
		

	// Create The Main Frame
	FramePtr MainFrame = osg::Frame::create();
	beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);
	   // Add things to the MainFrame
	   MainFrame->getChildren().addValue(TheScrollPanel);
	   MainFrame->getChildren().addValue(SelectionModePanel);
	   MainFrame->getChildren().addValue(SelectionOptionPanel);
	   MainFrame->setLayout(MainFrameLayout);
	endEditCP  (MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);

	//Create the Drawing Surface
	UIDrawingSurfacePtr drawingSurface = UIDrawingSurface::create();
	beginEditCP(drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask);
		drawingSurface->setGraphics(graphics);
		drawingSurface->setRootFrame(MainFrame);
	    drawingSurface->setEventProducer(TheWindowEventProducer);
    endEditCP  (drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask);
	
	// Create the UI Foreground Object
	UIForegroundPtr foreground = osg::UIForeground::create();

	beginEditCP(foreground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
	    foreground->setDrawingSurface(drawingSurface);
		foreground->setFramePositionOffset(Vec2s(0,0));
		foreground->setFrameBounds(Vec2f(1.0,1.0));
    endEditCP  (foreground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the manager what to manage
    mgr->setWindow(MainWindow);
    mgr->setRoot(scene);

	// Add the UI Foreground Object to the Scene
	ViewportPtr viewport = mgr->getWindow()->getPort(0);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);
		viewport->getForegrounds().addValue(foreground);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);

    // Show the whole scene
    mgr->showAll();

    TheWindowEventProducer->openWindow(Pnt2s(50,50),
                                        Vec2s(900,900),
                                        "OpenSG 27Table Window");

    //Main Event Loop
    while(!ExitApp)
    {
        TheWindowEventProducer->update();
        TheWindowEventProducer->draw();
    }
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
    beginEditCP(SelectionModeLabel, Label::TextFieldMask | Label::HorizontalAlignmentFieldMask);
        SelectionModeLabel->setText("Selection Mode");
        SelectionModeLabel->setHorizontalAlignment(0.0);
    endEditCP(SelectionModeLabel, Label::TextFieldMask | Label::HorizontalAlignmentFieldMask);

    //Buttons
    RadioButtonPtr SingleSelectionButton = RadioButton::create();
    beginEditCP(SingleSelectionButton, RadioButton::TextFieldMask | RadioButton::PreferredSizeFieldMask | RadioButton::SelectedFieldMask | RadioButton::HorizontalAlignmentFieldMask);
        SingleSelectionButton->setText("Single Selection");
        SingleSelectionButton->setSelected(true);
        SingleSelectionButton->setPreferredSize(Vec2s(180,30));
        SingleSelectionButton->setHorizontalAlignment(0.0);
    endEditCP(SingleSelectionButton, RadioButton::TextFieldMask | RadioButton::PreferredSizeFieldMask| RadioButton::SelectedFieldMask | RadioButton::HorizontalAlignmentFieldMask);
    SingleSelectionButton->addButtonSelectedListener(&TheSingleSelectionListener);
    
    RadioButtonPtr SingleIntervalSelectionButton = RadioButton::create();
    beginEditCP(SingleIntervalSelectionButton, RadioButton::TextFieldMask | RadioButton::PreferredSizeFieldMask | RadioButton::HorizontalAlignmentFieldMask);
        SingleIntervalSelectionButton->setText("Single Interval Selection");
        SingleIntervalSelectionButton->setPreferredSize(Vec2s(180,30));
        SingleIntervalSelectionButton->setHorizontalAlignment(0.0);
    endEditCP(SingleIntervalSelectionButton, RadioButton::TextFieldMask | RadioButton::PreferredSizeFieldMask | RadioButton::HorizontalAlignmentFieldMask);
    SingleIntervalSelectionButton->addButtonSelectedListener(&TheSingleIntervalSelectionListener);

    RadioButtonPtr MultipleIntervalSelectionButton = RadioButton::create();
    beginEditCP(MultipleIntervalSelectionButton, RadioButton::TextFieldMask | RadioButton::PreferredSizeFieldMask | RadioButton::HorizontalAlignmentFieldMask);
        MultipleIntervalSelectionButton->setText("Multiple Interval Selection");
        MultipleIntervalSelectionButton->setPreferredSize(Vec2s(180,30));
        MultipleIntervalSelectionButton->setHorizontalAlignment(0.0);
    endEditCP(MultipleIntervalSelectionButton, RadioButton::TextFieldMask | RadioButton::PreferredSizeFieldMask | RadioButton::HorizontalAlignmentFieldMask);
    MultipleIntervalSelectionButton->addButtonSelectedListener(&TheMultipleIntervalSelectionListener);

    SelectionButtonGroup.addButton(SingleSelectionButton);
    SelectionButtonGroup.addButton(SingleIntervalSelectionButton);
    SelectionButtonGroup.addButton(MultipleIntervalSelectionButton);

    //Box Layout
    BoxLayoutPtr PanelLayout = BoxLayout::create();
    beginEditCP(PanelLayout, BoxLayout::MinorAxisAlignmentFieldMask | BoxLayout::AlignmentFieldMask);
        PanelLayout->setAlignment(VERTICAL_ALIGNMENT);
        PanelLayout->setMinorAxisAlignment(AXIS_CENTER_ALIGNMENT);
    endEditCP(PanelLayout, BoxLayout::MinorAxisAlignmentFieldMask | BoxLayout::AlignmentFieldMask);


    //The Panel
    PanelPtr ThePanel = Panel::create();
    beginEditCP(ThePanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);
        ThePanel->getChildren().push_back(SelectionModeLabel);
        ThePanel->getChildren().push_back(SingleSelectionButton);
        ThePanel->getChildren().push_back(SingleIntervalSelectionButton);
        ThePanel->getChildren().push_back(MultipleIntervalSelectionButton);
        ThePanel->setLayout(PanelLayout);
        ThePanel->setPreferredSize(Vec2s(300, 200));
    endEditCP(ThePanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask| Panel::PreferredSizeFieldMask);
    return ThePanel;
}

RowSelectionListener TheRowSelectionListener;
ColumnSelectionListener TheColumnSelectionListener;
CellSelectionListener TheCellSelectionListener;

PanelPtr createSelectionOptionPanel(void)
{
    //Label
    LabelPtr SelectionOptionLabel = Label::create();
    beginEditCP(SelectionOptionLabel, Label::TextFieldMask | Label::HorizontalAlignmentFieldMask);
        SelectionOptionLabel->setText("Selection Options");
        SelectionOptionLabel->setHorizontalAlignment(0.0);
    endEditCP(SelectionOptionLabel, Label::TextFieldMask | Label::HorizontalAlignmentFieldMask);

    //Buttons
    RowSelectionButton = CheckboxButton::create();
    beginEditCP(RowSelectionButton, CheckboxButton::TextFieldMask | CheckboxButton::PreferredSizeFieldMask | CheckboxButton::HorizontalAlignmentFieldMask| CheckboxButton::SelectedFieldMask );
        RowSelectionButton->setText("Row Selection");
        RowSelectionButton->setPreferredSize(Vec2s(180,30));
        RowSelectionButton->setHorizontalAlignment(0.0);
        RowSelectionButton->setSelected(true);
    endEditCP(RowSelectionButton, CheckboxButton::TextFieldMask | CheckboxButton::PreferredSizeFieldMask | CheckboxButton::HorizontalAlignmentFieldMask| CheckboxButton::SelectedFieldMask );
    RowSelectionButton->addButtonSelectedListener(&TheRowSelectionListener);

    ColumnSelectionButton = CheckboxButton::create();
    beginEditCP(ColumnSelectionButton, CheckboxButton::TextFieldMask | CheckboxButton::PreferredSizeFieldMask | CheckboxButton::SelectedFieldMask | CheckboxButton::HorizontalAlignmentFieldMask);
        ColumnSelectionButton->setText("Column Selection");
        ColumnSelectionButton->setPreferredSize(Vec2s(180,30));
        ColumnSelectionButton->setHorizontalAlignment(0.0);
        ColumnSelectionButton->setSelected(true);
    endEditCP(ColumnSelectionButton, CheckboxButton::TextFieldMask | CheckboxButton::PreferredSizeFieldMask| CheckboxButton::SelectedFieldMask | CheckboxButton::HorizontalAlignmentFieldMask);
    ColumnSelectionButton->addButtonSelectedListener(&TheColumnSelectionListener);
    

    CellSelectionButton = CheckboxButton::create();
    beginEditCP(CellSelectionButton, CheckboxButton::TextFieldMask | CheckboxButton::PreferredSizeFieldMask | CheckboxButton::HorizontalAlignmentFieldMask| CheckboxButton::SelectedFieldMask);
        CellSelectionButton->setText("Cell Selection");
        CellSelectionButton->setPreferredSize(Vec2s(180,30));
        CellSelectionButton->setHorizontalAlignment(0.0);
        CellSelectionButton->setSelected(false);
    endEditCP(CellSelectionButton, CheckboxButton::TextFieldMask | CheckboxButton::PreferredSizeFieldMask | CheckboxButton::HorizontalAlignmentFieldMask| CheckboxButton::SelectedFieldMask);
    CellSelectionButton->addButtonSelectedListener(&TheCellSelectionListener);

    //Box Layout
    BoxLayoutPtr PanelLayout = BoxLayout::create();
    beginEditCP(PanelLayout, BoxLayout::MinorAxisAlignmentFieldMask | BoxLayout::AlignmentFieldMask);
        PanelLayout->setAlignment(VERTICAL_ALIGNMENT);
        PanelLayout->setMinorAxisAlignment(AXIS_CENTER_ALIGNMENT);
    endEditCP(PanelLayout, BoxLayout::MinorAxisAlignmentFieldMask | BoxLayout::AlignmentFieldMask);


    //The Panel
    PanelPtr ThePanel = Panel::create();
    beginEditCP(ThePanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::PreferredSizeFieldMask);
        ThePanel->getChildren().push_back(SelectionOptionLabel);
        ThePanel->getChildren().push_back(RowSelectionButton);
        ThePanel->getChildren().push_back(ColumnSelectionButton);
        ThePanel->getChildren().push_back(CellSelectionButton);
        ThePanel->setLayout(PanelLayout);
        ThePanel->setPreferredSize(Vec2s(300, 200));
    endEditCP(ThePanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask| Panel::PreferredSizeFieldMask);
    return ThePanel;
}
 // Callback functions


// Redraw the window
void display(void)
{
    mgr->redraw();
}

// React to size changes
void reshape(Vec2s Size)
{
    mgr->resize(Size.x(), Size.y());
}
