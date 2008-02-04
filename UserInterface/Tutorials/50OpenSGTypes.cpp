// OpenSG Tutorial Example: Creating a Label and Creating Fonts
//
// This tutorial explains how to change Fonts and create
// Labels
// 
// Includes: Font and Label creation and settings

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>

// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

//Input
#include <OpenSG/Input/OSGWindowUtils.h>
#include <OpenSG/Input/OSGWindowAdapter.h>
#include <OpenSG/Input/OSGMouseAdapter.h>

// UserInterface Headers
#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGUIBackgrounds.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGBorderLayout.h>
#include <OpenSG/UserInterface/OSGGridBagLayout.h>
#include <OpenSG/UserInterface/OSGBorderLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGGridBagLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGGradientUIBackground.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGUIDefines.h>
#include <OpenSG/OSGTypeFactory.h>
#include <OpenSG/OSGFieldFactory.h>
#include <OpenSG/OSGFieldContainerFactory.h>

// Include Label and Font headerfiles
#include <OpenSG/UserInterface/OSGLabel.h>

// List header files
#include <OpenSG/UserInterface/OSGList.h>
#include <OpenSG/UserInterface/OSGAbstractListModel.h>
#include <OpenSG/UserInterface/OSGDefaultListSelectionModel.h>
#include <OpenSG/UserInterface/OSGListModel.h>

#include <OpenSG/UserInterface/OSGScrollPanel.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGLabel.h>

#include <sstream>


// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
bool ExitApp = false;
std::map<std::string, UIFontPtr> FontMap;

// Declare upfront so they can be referenced

// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2s Size);

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

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEvent& e)
   {
       if(e.getKey() == KeyEvent::KEY_Q && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           ExitApp = true;
       }
   }

   virtual void keyReleased(const KeyEvent& e)
   {
   }

   virtual void keyTyped(const KeyEvent& e)
   {
   }
};

// Setup a listener to change the label's font
// when a different item in the list is
// selected
class TypeListListener: public MouseAdapter
{
  public:
    virtual void mouseClicked(const MouseEvent& e)
    {
    }
};

class OpenSGTypePanel
{
protected:
	PanelPtr _MainPanel;
	AbstractListModel _TypeModel;
	AbstractListModel _FieldTypeModel;
	AbstractListModel _FieldContainerTypeModel;

	PanelPtr createTypePanel(void)
	{
		//Put all the FieldTypes into the model
		for (UInt32 i(1); i <= 1311/*TypeFactory::the()->getNumTypes()*/ ; ++i)
		{
			TypeBase* TheType;
			TheType = TypeFactory::the()->findType(i);
			if(TheType != NULL)
			{
				// Add all available Fonts to it
				_TypeModel.pushBack(SharedFieldPtr(new SFString(TheType->getCName())));
			}
		}
		// Create TypeList
		ListPtr TypeList = List::create();
		beginEditCP(TypeList, Component::PreferredSizeFieldMask | List::CellOrientationFieldMask);
			TypeList->setPreferredSize( Vec2s (200, 300) );
			TypeList->setCellOrientation(VERTICAL_ALIGNMENT);
		endEditCP(TypeList, Component::PreferredSizeFieldMask | List::CellOrientationFieldMask);

		// Assign the Model, and SelectionModel
		// to the List
		TypeList->setModel(&_TypeModel);
		// Creates and assigns a SelectionMode
		ListSelectionModelPtr  FieldSelectionModel(new DefaultListSelectionModel);
		FieldSelectionModel->setSelectionMode(DefaultListSelectionModel::SINGLE_SELECTION);
		TypeList->setSelectionModel(FieldSelectionModel);
		
		GridBagLayoutConstraintsPtr TypeListScrollPanelConstraints = osg::GridBagLayoutConstraints::create();
		beginEditCP(TypeListScrollPanelConstraints);
			TypeListScrollPanelConstraints->setGridX(0);
			TypeListScrollPanelConstraints->setGridY(0);
			TypeListScrollPanelConstraints->setGridHeight(1);
			TypeListScrollPanelConstraints->setGridWidth(2);
			TypeListScrollPanelConstraints->setFill(FILL_HORIZONTAL);
			TypeListScrollPanelConstraints->setVerticalAlignment(1.0);
		endEditCP(TypeListScrollPanelConstraints);

		//TypeListScrollPanel
		ScrollPanelPtr TypeListScrollPanel = ScrollPanel::create();
		beginEditCP(TypeListScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask | Component::ConstraintsFieldMask);
			TypeListScrollPanel->setPreferredSize(Vec2s(200,300));
			TypeListScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
			//TheScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
			TypeListScrollPanel->setConstraints(TypeListScrollPanelConstraints);
		endEditCP(TypeListScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask | Component::ConstraintsFieldMask);
		TypeListScrollPanel->setViewComponent(TypeList);

		//Number of FieldContainerTypes Label
		GridBagLayoutConstraintsPtr NumTypesLabelConstraints = osg::GridBagLayoutConstraints::create();
		beginEditCP(NumTypesLabelConstraints);
			NumTypesLabelConstraints->setGridX(0);
			NumTypesLabelConstraints->setGridY(1);
			NumTypesLabelConstraints->setGridHeight(1);
			NumTypesLabelConstraints->setGridWidth(1);
			NumTypesLabelConstraints->setFill(FILL_HORIZONTAL);
			NumTypesLabelConstraints->setWeightX(1.0);
			NumTypesLabelConstraints->setVerticalAlignment(0.0);
		endEditCP(NumTypesLabelConstraints);

		LabelPtr NumTypesLabel = Label::create();
		beginEditCP(NumTypesLabel, Label::TextFieldMask | Component::ConstraintsFieldMask);
			NumTypesLabel->setText("Number Field Types: ");
			NumTypesLabel->setConstraints(NumTypesLabelConstraints);
		endEditCP(NumTypesLabel, Label::TextFieldMask | Component::ConstraintsFieldMask);
		
		//Number of FieldContainerTypes Value Label
		GridBagLayoutConstraintsPtr NumTypesValueLabelConstraints = osg::GridBagLayoutConstraints::create();
		beginEditCP(NumTypesValueLabelConstraints);
			NumTypesValueLabelConstraints->setGridX(1);
			NumTypesValueLabelConstraints->setGridY(1);
			NumTypesValueLabelConstraints->setGridHeight(1);
			NumTypesValueLabelConstraints->setGridWidth(1);
			NumTypesValueLabelConstraints->setFill(FILL_HORIZONTAL);
			NumTypesValueLabelConstraints->setWeightX(1.0);
			NumTypesValueLabelConstraints->setVerticalAlignment(0.0);
		endEditCP(NumTypesValueLabelConstraints);

		LabelPtr NumTypesValueLabel = Label::create();
		std::stringstream TempSStream;
		TempSStream << TypeFactory::the()->getNumTypes();
		beginEditCP(NumTypesValueLabel, Label::TextFieldMask | Component::ConstraintsFieldMask);
			NumTypesValueLabel->setText(TempSStream.str());
			NumTypesValueLabel->setConstraints(NumTypesValueLabelConstraints);
		endEditCP(NumTypesValueLabel, Label::TextFieldMask | Component::ConstraintsFieldMask);

		//Create Main Panel Layout
		GridBagLayoutPtr TypePanelLayout = osg::GridBagLayout::create();
		beginEditCP(TypePanelLayout, GridBagLayout::ColumnsFieldMask | GridBagLayout::RowsFieldMask);
			TypePanelLayout->setColumns(2);
			TypePanelLayout->setRows(2);
		endEditCP(TypePanelLayout, GridBagLayout::ColumnsFieldMask | GridBagLayout::RowsFieldMask);

		//Create Main Panel
		PanelPtr TypePanel = Panel::create();

		beginEditCP(TypePanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
			TypePanel->getChildren().push_back(TypeListScrollPanel);
			TypePanel->getChildren().push_back(NumTypesLabel);
			TypePanel->getChildren().push_back(NumTypesValueLabel);
			TypePanel->setLayout(TypePanelLayout);
		endEditCP(TypePanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
		return TypePanel;
	}

	PanelPtr createFieldTypePanel(void)
	{
		//Put all the FieldTypes into the model
		UInt32 NumTypesFound(0);
		for (UInt32 i(0); NumTypesFound < FieldFactory::the().getNFieldTypes() ; ++i)
		{
			FieldType* TheType;
			TheType = FieldFactory::the().getFieldType(i);
			if(TheType != NULL)
			{
				// Add all available Fonts to it
				_FieldTypeModel.pushBack(SharedFieldPtr(new SFString(TheType->getCName())));
				++NumTypesFound;
			}
		}

		// Create FieldTypeList
		ListPtr FieldTypeList = List::create();
		beginEditCP(FieldTypeList, Component::PreferredSizeFieldMask | List::CellOrientationFieldMask);
			FieldTypeList->setPreferredSize( Vec2s (200, 300) );
			FieldTypeList->setCellOrientation(VERTICAL_ALIGNMENT);
		endEditCP(FieldTypeList, Component::PreferredSizeFieldMask | List::CellOrientationFieldMask);

		// Assign the Model, and SelectionModel
		// to the List
		FieldTypeList->setModel(&_FieldTypeModel);
		// Creates and assigns a SelectionMode
		ListSelectionModelPtr  FieldSelectionModel(new DefaultListSelectionModel);
		FieldSelectionModel->setSelectionMode(DefaultListSelectionModel::SINGLE_SELECTION);
		FieldTypeList->setSelectionModel(FieldSelectionModel);
		
		GridBagLayoutConstraintsPtr FieldTypeListScrollPanelConstraints = osg::GridBagLayoutConstraints::create();
		beginEditCP(FieldTypeListScrollPanelConstraints);
			FieldTypeListScrollPanelConstraints->setGridX(0);
			FieldTypeListScrollPanelConstraints->setGridY(0);
			FieldTypeListScrollPanelConstraints->setGridHeight(1);
			FieldTypeListScrollPanelConstraints->setGridWidth(2);
			FieldTypeListScrollPanelConstraints->setFill(FILL_HORIZONTAL);
			FieldTypeListScrollPanelConstraints->setVerticalAlignment(1.0);
		endEditCP(FieldTypeListScrollPanelConstraints);

		//FieldTypeListScrollPanel
		ScrollPanelPtr FieldTypeListScrollPanel = ScrollPanel::create();
		beginEditCP(FieldTypeListScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask | Component::ConstraintsFieldMask);
			FieldTypeListScrollPanel->setPreferredSize(Vec2s(200,300));
			FieldTypeListScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
			//TheScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
			FieldTypeListScrollPanel->setConstraints(FieldTypeListScrollPanelConstraints);
		endEditCP(FieldTypeListScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask | Component::ConstraintsFieldMask);
		FieldTypeListScrollPanel->setViewComponent(FieldTypeList);

		//Number of FieldContainerTypes Label
		GridBagLayoutConstraintsPtr NumFieldTypesLabelConstraints = osg::GridBagLayoutConstraints::create();
		beginEditCP(NumFieldTypesLabelConstraints);
			NumFieldTypesLabelConstraints->setGridX(0);
			NumFieldTypesLabelConstraints->setGridY(1);
			NumFieldTypesLabelConstraints->setGridHeight(1);
			NumFieldTypesLabelConstraints->setGridWidth(1);
			NumFieldTypesLabelConstraints->setFill(FILL_HORIZONTAL);
			NumFieldTypesLabelConstraints->setWeightX(1.0);
			NumFieldTypesLabelConstraints->setVerticalAlignment(0.0);
		endEditCP(NumFieldTypesLabelConstraints);

		LabelPtr NumFieldTypesLabel = Label::create();
		beginEditCP(NumFieldTypesLabel, Label::TextFieldMask | Component::ConstraintsFieldMask);
			NumFieldTypesLabel->setText("Number Field Types: ");
			NumFieldTypesLabel->setConstraints(NumFieldTypesLabelConstraints);
		endEditCP(NumFieldTypesLabel, Label::TextFieldMask | Component::ConstraintsFieldMask);
		
		//Number of FieldContainerTypes Value Label
		GridBagLayoutConstraintsPtr NumFieldTypesValueLabelConstraints = osg::GridBagLayoutConstraints::create();
		beginEditCP(NumFieldTypesValueLabelConstraints);
			NumFieldTypesValueLabelConstraints->setGridX(1);
			NumFieldTypesValueLabelConstraints->setGridY(1);
			NumFieldTypesValueLabelConstraints->setGridHeight(1);
			NumFieldTypesValueLabelConstraints->setGridWidth(1);
			NumFieldTypesValueLabelConstraints->setFill(FILL_HORIZONTAL);
			NumFieldTypesValueLabelConstraints->setWeightX(1.0);
			NumFieldTypesValueLabelConstraints->setVerticalAlignment(0.0);
		endEditCP(NumFieldTypesValueLabelConstraints);

		LabelPtr NumFieldTypesValueLabel = Label::create();
		std::stringstream TempSStream;
		TempSStream << FieldFactory::the().getNFieldTypes();
		beginEditCP(NumFieldTypesValueLabel, Label::TextFieldMask | Component::ConstraintsFieldMask);
			NumFieldTypesValueLabel->setText(TempSStream.str());
			NumFieldTypesValueLabel->setConstraints(NumFieldTypesValueLabelConstraints);
		endEditCP(NumFieldTypesValueLabel, Label::TextFieldMask | Component::ConstraintsFieldMask);

		//Create Main Panel Layout
		GridBagLayoutPtr FieldTypePanelLayout = osg::GridBagLayout::create();
		beginEditCP(FieldTypePanelLayout, GridBagLayout::ColumnsFieldMask | GridBagLayout::RowsFieldMask);
			FieldTypePanelLayout->setColumns(2);
			FieldTypePanelLayout->setRows(2);
		endEditCP(FieldTypePanelLayout, GridBagLayout::ColumnsFieldMask | GridBagLayout::RowsFieldMask);

		//Create Main Panel
		PanelPtr FieldTypePanel = Panel::create();

		beginEditCP(FieldTypePanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
			FieldTypePanel->getChildren().push_back(FieldTypeListScrollPanel);
			FieldTypePanel->getChildren().push_back(NumFieldTypesLabel);
			FieldTypePanel->getChildren().push_back(NumFieldTypesValueLabel);
			FieldTypePanel->setLayout(FieldTypePanelLayout);
		endEditCP(FieldTypePanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
		return FieldTypePanel;
	}

	PanelPtr createFieldContainerTypePanel(void)
	{
		//Put all the FieldContainerTypes into the model
		UInt32 NumTypesFound(0);
		for (UInt32 i(0); NumTypesFound < FieldContainerFactory::the()->getNumTypes() ; ++i)
		{
			FieldContainerType* TheType;
			TheType = FieldContainerFactory::the()->findType(i);
			if(TheType != NULL)
			{
				// Add all available Fonts to it
				_FieldContainerTypeModel.pushBack(SharedFieldPtr(new SFString(TheType->getCName())));
				++NumTypesFound;
			}
		}

		// Create FieldContainerTypeList
		ListPtr FieldContainerTypeList = List::create();
		beginEditCP(FieldContainerTypeList, Component::PreferredSizeFieldMask | List::CellOrientationFieldMask);
			FieldContainerTypeList->setPreferredSize( Vec2s (200, 300) );
			FieldContainerTypeList->setCellOrientation(VERTICAL_ALIGNMENT);
		endEditCP(FieldContainerTypeList, Component::PreferredSizeFieldMask | List::CellOrientationFieldMask);

		// Assign the Model, and SelectionModel
		// to the List
		FieldContainerTypeList->setModel(&_FieldContainerTypeModel);
		// Creates and assigns a SelectionMode
		ListSelectionModelPtr  FieldSelectionModel(new DefaultListSelectionModel);
		FieldSelectionModel->setSelectionMode(DefaultListSelectionModel::SINGLE_SELECTION);
		FieldContainerTypeList->setSelectionModel(FieldSelectionModel);
		
		GridBagLayoutConstraintsPtr FieldContainerTypeListScrollPanelConstraints = osg::GridBagLayoutConstraints::create();
		beginEditCP(FieldContainerTypeListScrollPanelConstraints);
			FieldContainerTypeListScrollPanelConstraints->setGridX(0);
			FieldContainerTypeListScrollPanelConstraints->setGridY(0);
			FieldContainerTypeListScrollPanelConstraints->setGridHeight(1);
			FieldContainerTypeListScrollPanelConstraints->setGridWidth(2);
			FieldContainerTypeListScrollPanelConstraints->setFill(FILL_NONE);
			FieldContainerTypeListScrollPanelConstraints->setVerticalAlignment(1.0);
		endEditCP(FieldContainerTypeListScrollPanelConstraints);

		//FieldContainerTypeListScrollPanel
		ScrollPanelPtr FieldContainerTypeListScrollPanel = ScrollPanel::create();
		beginEditCP(FieldContainerTypeListScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask | ScrollPanel::ConstraintsFieldMask);
			FieldContainerTypeListScrollPanel->setPreferredSize(Vec2s(200,300));
			FieldContainerTypeListScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
			//TheScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
			FieldContainerTypeListScrollPanel->setConstraints(FieldContainerTypeListScrollPanelConstraints);
		endEditCP(FieldContainerTypeListScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask | ScrollPanel::ConstraintsFieldMask);
		FieldContainerTypeListScrollPanel->setViewComponent(FieldContainerTypeList);

		//Number of FieldContainerTypes Label
		GridBagLayoutConstraintsPtr NumFCTypesLabelConstraints = osg::GridBagLayoutConstraints::create();
		beginEditCP(NumFCTypesLabelConstraints);
			NumFCTypesLabelConstraints->setGridX(0);
			NumFCTypesLabelConstraints->setGridY(1);
			NumFCTypesLabelConstraints->setGridHeight(1);
			NumFCTypesLabelConstraints->setGridWidth(1);
			NumFCTypesLabelConstraints->setFill(FILL_HORIZONTAL);
			NumFCTypesLabelConstraints->setWeightX(1.0);
			NumFCTypesLabelConstraints->setVerticalAlignment(0.0);
		endEditCP(NumFCTypesLabelConstraints);

		LabelPtr NumFCTypesLabel = Label::create();
		beginEditCP(NumFCTypesLabel, Label::TextFieldMask | Component::ConstraintsFieldMask);
			NumFCTypesLabel->setText("Number Field Container Types: ");
			NumFCTypesLabel->setConstraints(NumFCTypesLabelConstraints);
		endEditCP(NumFCTypesLabel, Label::TextFieldMask | Component::ConstraintsFieldMask);
		
		//Number of FieldContainerTypes Value Label
		GridBagLayoutConstraintsPtr NumFCTypesValueLabelConstraints = osg::GridBagLayoutConstraints::create();
		beginEditCP(NumFCTypesValueLabelConstraints);
			NumFCTypesValueLabelConstraints->setGridX(1);
			NumFCTypesValueLabelConstraints->setGridY(1);
			NumFCTypesValueLabelConstraints->setGridHeight(1);
			NumFCTypesValueLabelConstraints->setGridWidth(1);
			NumFCTypesValueLabelConstraints->setFill(FILL_HORIZONTAL);
			NumFCTypesValueLabelConstraints->setWeightX(1.0);
			NumFCTypesValueLabelConstraints->setVerticalAlignment(0.0);
		endEditCP(NumFCTypesValueLabelConstraints);

		LabelPtr NumFCTypesValueLabel = Label::create();
		std::stringstream TempSStream;
		TempSStream << FieldContainerFactory::the()->getNumTypes();
		beginEditCP(NumFCTypesValueLabel, Label::TextFieldMask | Component::ConstraintsFieldMask);
			NumFCTypesValueLabel->setText(TempSStream.str());
			NumFCTypesValueLabel->setConstraints(NumFCTypesValueLabelConstraints);
		endEditCP(NumFCTypesValueLabel, Label::TextFieldMask | Component::ConstraintsFieldMask);

		//Create Main Panel Layout
		GridBagLayoutPtr FieldContainerTypePanelLayout = osg::GridBagLayout::create();
		beginEditCP(FieldContainerTypePanelLayout, GridBagLayout::ColumnsFieldMask | GridBagLayout::RowsFieldMask);
			FieldContainerTypePanelLayout->setColumns(2);
			FieldContainerTypePanelLayout->setRows(2);
		endEditCP(FieldContainerTypePanelLayout, GridBagLayout::ColumnsFieldMask | GridBagLayout::RowsFieldMask);

		//Create Main Panel
		PanelPtr FieldContainerTypePanel = Panel::create();

		beginEditCP(FieldContainerTypePanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
			FieldContainerTypePanel->getChildren().push_back(FieldContainerTypeListScrollPanel);
			FieldContainerTypePanel->getChildren().push_back(NumFCTypesLabel);
			FieldContainerTypePanel->getChildren().push_back(NumFCTypesValueLabel);
			FieldContainerTypePanel->setLayout(FieldContainerTypePanelLayout);
		endEditCP(FieldContainerTypePanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
		return FieldContainerTypePanel;
	}
public:
	PanelPtr getPanel(void) const
	{
		return _MainPanel;
	}

	OpenSGTypePanel()
	{
		//Create the Type Panels
		GridBagLayoutConstraintsPtr TypePanelConstraints = osg::GridBagLayoutConstraints::create();
		beginEditCP(TypePanelConstraints);
			TypePanelConstraints->setGridX(0);
			TypePanelConstraints->setGridY(0);
			TypePanelConstraints->setGridHeight(1);
			TypePanelConstraints->setGridWidth(1);
			TypePanelConstraints->setFill(FILL_BOTH);
			TypePanelConstraints->setWeightX(1.0);
			TypePanelConstraints->setWeightY(1.0);
			TypePanelConstraints->setPadBottom(2);
			TypePanelConstraints->setPadLeft(2);
			TypePanelConstraints->setPadRight(2);
			TypePanelConstraints->setPadTop(2);
		endEditCP(TypePanelConstraints);

		PanelPtr TypePanel = createTypePanel();
		beginEditCP(TypePanel, Component::ConstraintsFieldMask);
			TypePanel->setConstraints(TypePanelConstraints);
		endEditCP(TypePanel, Component::ConstraintsFieldMask);


		GridBagLayoutConstraintsPtr FieldTypePanelConstraints = osg::GridBagLayoutConstraints::create();
		beginEditCP(FieldTypePanelConstraints);
			FieldTypePanelConstraints->setGridX(1);
			FieldTypePanelConstraints->setGridY(0);
			FieldTypePanelConstraints->setGridHeight(1);
			FieldTypePanelConstraints->setGridWidth(1);
			FieldTypePanelConstraints->setFill(FILL_BOTH);
			FieldTypePanelConstraints->setWeightX(1.0);
			FieldTypePanelConstraints->setWeightY(1.0);
			FieldTypePanelConstraints->setPadBottom(2);
			FieldTypePanelConstraints->setPadLeft(2);
			FieldTypePanelConstraints->setPadRight(2);
			FieldTypePanelConstraints->setPadTop(2);
		endEditCP(FieldTypePanelConstraints);

		PanelPtr FieldTypePanel = createFieldTypePanel();
		beginEditCP(FieldTypePanel, Component::ConstraintsFieldMask);
			FieldTypePanel->setConstraints(FieldTypePanelConstraints);
		endEditCP(FieldTypePanel, Component::ConstraintsFieldMask);

		GridBagLayoutConstraintsPtr FieldContainerTypePanelConstraints = osg::GridBagLayoutConstraints::create();
		beginEditCP(FieldContainerTypePanelConstraints);
			FieldContainerTypePanelConstraints->setGridX(2);
			FieldContainerTypePanelConstraints->setGridY(0);
			FieldContainerTypePanelConstraints->setGridHeight(1);
			FieldContainerTypePanelConstraints->setGridWidth(1);
			FieldContainerTypePanelConstraints->setFill(FILL_BOTH);
			FieldContainerTypePanelConstraints->setWeightX(1.0);
			FieldContainerTypePanelConstraints->setWeightY(1.0);
			FieldContainerTypePanelConstraints->setPadBottom(2);
			FieldContainerTypePanelConstraints->setPadLeft(2);
			FieldContainerTypePanelConstraints->setPadRight(2);
			FieldContainerTypePanelConstraints->setPadTop(2);
		endEditCP(FieldContainerTypePanelConstraints);

		PanelPtr FieldContainerTypePanel = createFieldContainerTypePanel();
		beginEditCP(FieldContainerTypePanel, Component::ConstraintsFieldMask);
			FieldContainerTypePanel->setConstraints(FieldContainerTypePanelConstraints);
		endEditCP(FieldContainerTypePanel, Component::ConstraintsFieldMask);

		//Create Main Panel Layout
		GridBagLayoutPtr MainPanelLayout = osg::GridBagLayout::create();

			
		beginEditCP(MainPanelLayout, GridBagLayout::ColumnsFieldMask | GridBagLayout::RowsFieldMask);
			MainPanelLayout->setColumns(3);
			MainPanelLayout->setRows(1);
		endEditCP(MainPanelLayout, GridBagLayout::ColumnsFieldMask | GridBagLayout::RowsFieldMask);

		//Create Main Panel
        _MainPanel = Panel::createEmpty();

		beginEditCP(_MainPanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
			_MainPanel->getChildren().push_back(TypePanel);
			_MainPanel->getChildren().push_back(FieldTypePanel);
			_MainPanel->getChildren().push_back(FieldContainerTypePanel);
			_MainPanel->setLayout(MainPanelLayout);
		endEditCP(_MainPanel, Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
	}
};

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    WindowEventProducerPtr TheWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TheWindowEventProducer->initWindow();
    
    TheWindowEventProducer->setDisplayCallback(display);
    TheWindowEventProducer->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TheWindowEventProducer->addWindowListener(&TheTutorialWindowListener);
    TutorialKeyListener TheKeyListener;
    TheWindowEventProducer->addKeyListener(&TheKeyListener);


    // Make Torus Node
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

	// Initialize the LookAndFeelManager to enable default settings
	LookAndFeelManager::the()->getLookAndFeel()->init();


	// Create ListModel Component
	/*AbstractListModel TypeModel;

	// Display all Types available
	for (UInt32 i(1); i < TypeFactory::the()->getNumTypes()+1 ; ++i)
	{
		TypeBase* TheType;
		TheType = TypeFactory::the()->findType(i);
		if(TheType != NULL)
		{
			// Add all available Fonts to it
			TypeModel.pushBack(SharedFieldPtr(new SFString(TheType->getCName())));
		}
	}*/
	
	

	OpenSGTypePanel TheOpenSGTypePanel;
	BorderLayoutConstraintsPtr OpenSGTypePanelConstraints = osg::BorderLayoutConstraints::create();
	beginEditCP(OpenSGTypePanelConstraints, BorderLayoutConstraints::RegionFieldMask);
		OpenSGTypePanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
	endEditCP(OpenSGTypePanelConstraints, BorderLayoutConstraints::RegionFieldMask);
	
	beginEditCP(TheOpenSGTypePanel.getPanel(), Component::ConstraintsFieldMask);
		TheOpenSGTypePanel.getPanel()->setConstraints(OpenSGTypePanelConstraints);
	endEditCP(TheOpenSGTypePanel.getPanel(), Component::ConstraintsFieldMask);


    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorUIBackgroundPtr MainInternalWindowBackground = osg::ColorUIBackground::create();
    beginEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);

	BorderLayoutPtr MainInternalWindowLayout = osg::BorderLayout::create();

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
	   MainInternalWindow->getChildren().addValue(TheOpenSGTypePanel.getPanel());
	   MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
    endEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);

	//Create the Drawing Surface
	UIDrawingSurfacePtr TutorialDrawingSurface = UIDrawingSurface::create();
	beginEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask|UIDrawingSurface::EventProducerFieldMask);
		TutorialDrawingSurface->setGraphics(graphics);
	    TutorialDrawingSurface->setEventProducer(TheWindowEventProducer);
    endEditCP  (TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask|UIDrawingSurface::EventProducerFieldMask);
	
	TutorialDrawingSurface->openWindow(MainInternalWindow);

	// Create the UI Foreground Object
	UIForegroundPtr foreground = osg::UIForeground::create();

	beginEditCP(foreground, UIForeground::DrawingSurfaceFieldMask);
	    foreground->setDrawingSurface(TutorialDrawingSurface);
    endEditCP  (foreground, UIForeground::DrawingSurfaceFieldMask);
 
    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(MainWindow );
    mgr->setRoot  (scene);

	// Add the UI Foreground Object to the Scene
	ViewportPtr viewport = mgr->getWindow()->getPort(0);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);
		viewport->getForegrounds().addValue(foreground);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);

    // show the whole scene
    mgr->showAll();

    TheWindowEventProducer->openWindow(Pnt2s(50,50),
                                        Vec2s(1700,1000),
                                        "OpenSG 50OpenSGTypes Window");

    //Main Event Loop
    while(!ExitApp)
    {
        TheWindowEventProducer->update();
        TheWindowEventProducer->draw();
    }
    osgExit();

    return 0;
}

// redraw the window
void display(void)
{
    mgr->redraw();
}

// react to size changes
void reshape(Vec2s Size)
{
    mgr->resize(Size.x(), Size.y());
}
