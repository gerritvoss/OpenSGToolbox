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

// Inventory header files
#include <OpenSG/Game/OSGInventoryListModel.h>
#include <OpenSG/Game/OSGInventory.h>
#include <OpenSG/Game/OSGGenericInventoryItem.h>

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
#include <OpenSG/UserInterface/OSGTextArea.h>
#include <OpenSG/UserInterface/OSGImageComponent.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// 18List Headers
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGColorLayer.h>
#include <OpenSG/UserInterface/OSGBevelBorder.h>
#include <OpenSG/UserInterface/OSGBoxLayout.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGToggleButton.h>
#include <OpenSG/UserInterface/OSGScrollPanel.h>

// List header files
#include <OpenSG/UserInterface/OSGList.h>
#include <OpenSG/UserInterface/OSGDefaultListSelectionModel.h>
#include <OpenSG/UserInterface/OSGListSelectionListener.h>

#include <OpenSG/Game/OSGDefaultInventoryListComparitor.h>
#include <OpenSG/Game/OSGDefaultInventorySubset.h>
#include <OpenSG/Game/OSGDefaultInventoryListComponentGenerator.h>
#include <OpenSG/OSGTextureChunk.h>


// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEvent& e)
   {
       if(e.getKey() == KeyEvent::KEY_Q && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
            TutorialWindowEventProducer->closeWindow();
       }
   }

   virtual void keyReleased(const KeyEvent& e)
   {
   }

   virtual void keyTyped(const KeyEvent& e)
   {
   }
};


// Declare the SelectionModel up front to allow for
// the ActionListeners
ListSelectionModelPtr ExampleListSelectionModel(new DefaultListSelectionModel());

TextAreaPtr DetailsWindow;

// Create ListModel   
ListPtr ExampleList;
InventoryListModelPtr ExampleListModel;
InventoryPtr ExampleInventory;

ButtonPtr MainButton;
ButtonPtr AdminButton;
ButtonPtr DeveloperButton;
ButtonPtr GraphicButton;

DefaultInventorySubsetPtr ExampleSubset;

class InventoryListListener: public ListSelectionListener
{
  public:
    virtual void selectionChanged(const ListSelectionEvent& e)
    {
		if(ExampleList->getSelectionModel()->getMinSelectionIndex() != -1)
		{	
			beginEditCP(DetailsWindow, TextArea::TextFieldMask);

			if(ExampleList->getSelectionModel()->isSelectionEmpty())
			{
				DetailsWindow->setText("");
			}
			else
			{
				InventoryItemPtr Item;
				try
				{
					Item = boost::any_cast<InventoryItemPtr>(ExampleList->getModel()->getElementAt(ExampleList->getSelectionModel()->getMinSelectionIndex()));
				}
				catch(boost::bad_any_cast&)
				{
					DetailsWindow->setText("bad any_cast");
				}

				if(Item != NULL)
				{
					DetailsWindow->setText(GenericInventoryItemPtr::dcast(Item)->getDetails());
				}
			}
			endEditCP(DetailsWindow, TextArea::TextFieldMask);
		}
	}
};


class ClassSelectionListener : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
    {
		if(ButtonPtr::dcast(e.getSource()) == MainButton)
		{
		    beginEditCP(ExampleListModel, InventoryListModel::CurrentSubsetFieldMask);
				ExampleListModel->setCurrentSubset(NullFC);
			endEditCP(ExampleListModel, InventoryListModel::CurrentSubsetFieldMask);
		}
		if(ButtonPtr::dcast(e.getSource()) == AdminButton)
		{
			beginEditCP(ExampleSubset, DefaultInventorySubset::ClassDefinitionFieldMask);
				ExampleSubset->setClassDefinition("Admin");
			endEditCP(ExampleSubset, DefaultInventorySubset::ClassDefinitionFieldMask);

			beginEditCP(ExampleListModel, InventoryListModel::CurrentSubsetFieldMask);
				ExampleListModel->setCurrentSubset(ExampleSubset);
			endEditCP(ExampleListModel, InventoryListModel::CurrentSubsetFieldMask);
		}
		if(ButtonPtr::dcast(e.getSource()) == DeveloperButton)
		{
			beginEditCP(ExampleSubset, DefaultInventorySubset::ClassDefinitionFieldMask);
				ExampleSubset->setClassDefinition("Developer");
			endEditCP(ExampleSubset, DefaultInventorySubset::ClassDefinitionFieldMask);

			beginEditCP(ExampleListModel, InventoryListModel::CurrentSubsetFieldMask);
				ExampleListModel->setCurrentSubset(ExampleSubset);
			endEditCP(ExampleListModel, InventoryListModel::CurrentSubsetFieldMask);
		}
		if(ButtonPtr::dcast(e.getSource()) == GraphicButton)
		{
			beginEditCP(ExampleSubset, DefaultInventorySubset::ClassDefinitionFieldMask);
				ExampleSubset->setClassDefinition("Graphic");
			endEditCP(ExampleSubset, DefaultInventorySubset::ClassDefinitionFieldMask);

			beginEditCP(ExampleListModel, InventoryListModel::CurrentSubsetFieldMask);
				ExampleListModel->setCurrentSubset(ExampleSubset);
			endEditCP(ExampleListModel, InventoryListModel::CurrentSubsetFieldMask);
		}
    }

};

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

	//Create InventoryItems
	ExampleInventory = Inventory::create();
	GenericInventoryItemPtr ExampleItem1 = GenericInventoryItem::create();
	GenericInventoryItemPtr ExampleItem2 = GenericInventoryItem::create(); 
	GenericInventoryItemPtr ExampleItem3 = GenericInventoryItem::create(); 
	GenericInventoryItemPtr ExampleItem4 = GenericInventoryItem::create();
	GenericInventoryItemPtr ExampleItem5 = GenericInventoryItem::create();
	GenericInventoryItemPtr ExampleItem6 = GenericInventoryItem::create();
	GenericInventoryItemPtr ExampleItem7 = GenericInventoryItem::create();

	TextureChunkPtr ShipImage = TextureChunk::create();
	beginEditCP(ShipImage , TextureChunk::ImageFieldMask);
		ShipImage->setImage(ImageFileHandler::the().read(Path("./Data/Ship.JPG").string().c_str()));
	endEditCP(ShipImage , TextureChunk::ImageFieldMask);

	beginEditCP(ExampleItem1, InventoryItem::NameFieldMask | GenericInventoryItem::DetailsFieldMask | GenericInventoryItem::ClassesFieldMask | GenericInventoryItem::IconFieldMask);
		ExampleItem1->setName(std::string("David K"));
		ExampleItem1->setIcon(ShipImage);
		ExampleItem1->getClasses().push_back("Developer");
		ExampleItem1->setDetails(std::string("Major: Human Computer Interaction \nDegree: PhD \nDepartment: Computer Science \nCollege: LAS"));
	endEditCP(ExampleItem1, InventoryItem::NameFieldMask | GenericInventoryItem::DetailsFieldMask | GenericInventoryItem::ClassesFieldMask | GenericInventoryItem::IconFieldMask);

	beginEditCP(ExampleItem2, InventoryItem::NameFieldMask | GenericInventoryItem::DetailsFieldMask | GenericInventoryItem::ClassesFieldMask | GenericInventoryItem::IconFieldMask);
		ExampleItem2->setName(std::string("Eve W"));
		ExampleItem2->setIcon(ShipImage);
		ExampleItem2->getClasses().push_back("Admin");
		ExampleItem2->setDetails(std::string("Department: Genetics Development and Cell Biology\n\nCollege: Agriculture"));
	endEditCP(ExampleItem2, InventoryItem::NameFieldMask | GenericInventoryItem::DetailsFieldMask | GenericInventoryItem::ClassesFieldMask | GenericInventoryItem::IconFieldMask);

	beginEditCP(ExampleItem3, InventoryItem::NameFieldMask | GenericInventoryItem::DetailsFieldMask | GenericInventoryItem::ClassesFieldMask | GenericInventoryItem::IconFieldMask);
		ExampleItem3->setName(std::string("Will S"));
		ExampleItem3->setIcon(ShipImage);
		ExampleItem3->getClasses().push_back("Graphic");
		ExampleItem3->setDetails(std::string("Major: Art And Design\nDegree: BFA\nDepartment: Art and Design\nCollege: Design"));
	endEditCP(ExampleItem3, InventoryItem::NameFieldMask | GenericInventoryItem::DetailsFieldMask | GenericInventoryItem::ClassesFieldMask | GenericInventoryItem::IconFieldMask);

	beginEditCP(ExampleItem4, InventoryItem::NameFieldMask | GenericInventoryItem::DetailsFieldMask | GenericInventoryItem::ClassesFieldMask | GenericInventoryItem::IconFieldMask);
		ExampleItem4->setName(std::string("Eric L"));
		ExampleItem4->setIcon(ShipImage);
		ExampleItem4->getClasses().push_back("Developer");
		ExampleItem4->setDetails(std::string("Major: Software Engineering\nDegree: BS\nDepartment: Software Engineering\nCollege: Engineering"));
	endEditCP(ExampleItem4, InventoryItem::NameFieldMask | GenericInventoryItem::DetailsFieldMask | GenericInventoryItem::ClassesFieldMask | GenericInventoryItem::IconFieldMask);

	beginEditCP(ExampleItem5, InventoryItem::NameFieldMask | GenericInventoryItem::DetailsFieldMask | GenericInventoryItem::ClassesFieldMask | GenericInventoryItem::IconFieldMask);
		ExampleItem5->setName(std::string("Jeffery F"));
		ExampleItem5->setIcon(ShipImage);
		ExampleItem5->getClasses().push_back("Graphic");
		ExampleItem5->setDetails(std::string("Major: Integrated Studio Arts\nDegree: BFA\nDepartment: Art and Design\nCollege: Design"));
	endEditCP(ExampleItem5, InventoryItem::NameFieldMask | GenericInventoryItem::DetailsFieldMask | GenericInventoryItem::ClassesFieldMask | GenericInventoryItem::IconFieldMask);

	beginEditCP(ExampleItem6, InventoryItem::NameFieldMask | GenericInventoryItem::DetailsFieldMask | GenericInventoryItem::ClassesFieldMask | GenericInventoryItem::IconFieldMask);
		ExampleItem6->setName(std::string("Tao L"));
		ExampleItem6->setIcon(ShipImage);
		ExampleItem6->getClasses().push_back("Developer");
		ExampleItem6->setDetails(std::string("Major: Computer Engineering\nDegree: PhD\nDepartment: Computer Engineering\nCollege: Engineering"));
	endEditCP(ExampleItem6, InventoryItem::NameFieldMask | GenericInventoryItem::DetailsFieldMask | GenericInventoryItem::ClassesFieldMask | GenericInventoryItem::IconFieldMask);

	beginEditCP(ExampleItem7, InventoryItem::NameFieldMask | GenericInventoryItem::DetailsFieldMask | GenericInventoryItem::ClassesFieldMask | GenericInventoryItem::IconFieldMask);
		ExampleItem7->setName(std::string("Daniel G"));
		ExampleItem7->setIcon(ShipImage);
		ExampleItem7->getClasses().push_back("Developer");
		ExampleItem7->setDetails(std::string("Major: Computer Engineering\nDegree: BS\nDepartment: Computer Engineering\nCollege: Engineering"));
	endEditCP(ExampleItem7, InventoryItem::NameFieldMask | GenericInventoryItem::DetailsFieldMask | GenericInventoryItem::ClassesFieldMask | GenericInventoryItem::IconFieldMask);

	ExampleInventory->addItem(ExampleItem1);
	ExampleInventory->addItem(ExampleItem2);
	ExampleInventory->addItem(ExampleItem3);
	ExampleInventory->addItem(ExampleItem4);
	ExampleInventory->addItem(ExampleItem5);
	ExampleInventory->addItem(ExampleItem6);
	ExampleInventory->addItem(ExampleItem7);



    /******************************************************

            Create a List.  A List has several 
			parts to it:
			-ListModel: Contains the data which is to be
			    displayed in the List.  Data is added
				as shown below
			-ListCellRenderer: Creates the Components to
				be used within the List (the default
				setting is to create Labels using 
				the desired text).
			-ListSelectionModel: Determines how
				the List may be selected.

			To add values to the list:
            
            First, create SFStrings and use the 
            .setValue("Value") function to set their
            values.  Then, use the .pushBack(&SFStringName)
            to add them to the List.

            Next, create the CellRenderer and ListSelectionModel
            defaults.

            Finally, actually create the List.  Set
            its Model, CellRenderer, and SelectionModel
            as shown below.  Finally, choose the
            type of display for the List (choices outlined
            below).

    ******************************************************/

	DefaultInventoryListComparitorPtr ExampleComparitor = DefaultInventoryListComparitor::create();

    // Add data to it
	ExampleListModel = InventoryListModel::create();
    beginEditCP(ExampleListModel, InventoryListModel::CurrentInventoryFieldMask);
	    ExampleListModel->setCurrentInventory(ExampleInventory);
    endEditCP(ExampleListModel, InventoryListModel::CurrentInventoryFieldMask);
	
    beginEditCP(ExampleListModel, InventoryListModel::ComparitorFieldMask);
	    ExampleListModel->setComparitor(ExampleComparitor);
    endEditCP(ExampleListModel, InventoryListModel::ComparitorFieldMask);
    

    /******************************************************

            Create ListCellRenderer and 
			ListSelectionModel.  Most 
			often the defauls will be used.
			
			Note: the ListSelectionModel was
			created above and is referenced
			by the ActionListeners.

    ******************************************************/    


    /******************************************************

            Create List itself and assign its 
			Model, CellRenderer, and SelectionModel
			to it.
			-setOrientation(ENUM): Determine the
				Layout of the cells (Horizontal
				or Vertical).  Takes List::VERTICAL_ORIENTATION
				and List::HORIZONTAL_ORIENTATION arguments.

    ******************************************************/    
	DefaultInventoryListComponentGeneratorPtr ExampleListComponentGenerator = DefaultInventoryListComponentGenerator::create();
	ExampleList = List::create();
	beginEditCP(ExampleList, List::PreferredSizeFieldMask | List::OrientationFieldMask | List::ModelFieldMask | List::CellGeneratorFieldMask);
        ExampleList->setPreferredSize(Vec2f(200, 300));
        ExampleList->setOrientation(List::VERTICAL_ORIENTATION);
        //ExampleList->setOrientation(List::HORIZONTAL_ORIENTATION);
		ExampleList->setModel(ExampleListModel);
		ExampleList->setCellGenerator(ExampleListComponentGenerator);
    endEditCP(ExampleList, List::PreferredSizeFieldMask | List::OrientationFieldMask | List::ModelFieldMask | List::CellGeneratorFieldMask);

    ExampleList->setSelectionModel(ExampleListSelectionModel);
	InventoryListListener TheInventoryListListener;
    ExampleList->getSelectionModel()->addListSelectionListener(&TheInventoryListListener);


	// Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);

    /******************************************************

            Determine the SelectionModel
            -SINGLE_SELECTION lets you select ONE item
                via a single mouse click
            -SINGLE_INTERVAL_SELECTION lets you select
                one interval via mouse and SHIFT key
            -MULTIPLE_INTERVAL_SELECTION lets you select
                via mouse, and SHIFT and CONTRL keys

            Note: this tutorial is currently set up
            to allow for this to be changed via 
			TogggleButtons with ActionListeners attached 
            to them so this code is commented out.

    ******************************************************/

    //SelectionModel.setMode(DefaultListSelectionModel::SINGLE_SELECTION);
    //SelectionModel.setMode(DefaultListSelectionModel::SINGLE_INTERVAL_SELECTION);
    //SelectionModel.setMode(DefaultListSelectionModel::MULTIPLE_INTERVAL_SELECTION);

    // Create a ScrollPanel for easier viewing of the List (see 27ScrollPanel)
    ScrollPanelPtr ExampleScrollPanel = ScrollPanel::create();
	beginEditCP(ExampleScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask | ScrollPanel::BackgroundFieldMask);
        ExampleScrollPanel->setPreferredSize(Vec2f(200,100));
		ExampleScrollPanel->setBackgrounds(MainInternalWindowBackground);
        ExampleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //ExampleScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(ExampleScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask | ScrollPanel::BackgroundFieldMask);
    ExampleScrollPanel->setViewComponent(ExampleList);

    // Create MainFramelayout
    BoxLayoutPtr MainInternalWindowLayout = osg::BoxLayout::create();
    beginEditCP(MainInternalWindowLayout, BoxLayout::OrientationFieldMask | BoxLayout::MajorAxisAlignmentFieldMask | BoxLayout::MinorAxisAlignmentFieldMask);
		MainInternalWindowLayout->setOrientation(BoxLayout::HORIZONTAL_ORIENTATION);
        MainInternalWindowLayout->setMajorAxisAlignment(0.5f);
        MainInternalWindowLayout->setMinorAxisAlignment(0.5f);
    endEditCP(MainInternalWindowLayout, BoxLayout::OrientationFieldMask | BoxLayout::MajorAxisAlignmentFieldMask | BoxLayout::MinorAxisAlignmentFieldMask);
    
	UIFontPtr ButtonFont = osg::UIFont::create();

    beginEditCP(ButtonFont, UIFont::SizeFieldMask);
        ButtonFont->setSize(16);
    endEditCP(ButtonFont, UIFont::SizeFieldMask);

	ExampleSubset = DefaultInventorySubset::create();

	MainButton = osg::Button::create();
    beginEditCP(MainButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask );
            MainButton->setMinSize(Vec2f(50, 25));
            MainButton->setMaxSize(Vec2f(200, 100));
            MainButton->setPreferredSize(Vec2f(100, 50));
            MainButton->setToolTipText("These buttons are for selecting a response!");

            MainButton->setText("Main");
            MainButton->setFont(ButtonFont);
            MainButton->setTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
            MainButton->setRolloverTextColor(Color4f(1.0, 0.0, 1.0, 1.0));
            MainButton->setActiveTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
    endEditCP(MainButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask );


    AdminButton = osg::Button::create();
    beginEditCP(AdminButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask );
            AdminButton->setMinSize(Vec2f(50, 25));
            AdminButton->setMaxSize(Vec2f(200, 100));
            AdminButton->setPreferredSize(Vec2f(100, 50));
            AdminButton->setToolTipText("These buttons are for selecting a response!");

            AdminButton->setText("Admins");
            AdminButton->setFont(ButtonFont);
            AdminButton->setTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
            AdminButton->setRolloverTextColor(Color4f(1.0, 0.0, 1.0, 1.0));
            AdminButton->setActiveTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
    endEditCP(AdminButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask );

	DeveloperButton = osg::Button::create();
    beginEditCP(DeveloperButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask );
            DeveloperButton->setMinSize(Vec2f(50, 25));
            DeveloperButton->setMaxSize(Vec2f(200, 100));
            DeveloperButton->setPreferredSize(Vec2f(100, 50));
            DeveloperButton->setToolTipText("These buttons are for selecting a response!");

            DeveloperButton->setText("Developers");
            DeveloperButton->setFont(ButtonFont);
            DeveloperButton->setTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
            DeveloperButton->setRolloverTextColor(Color4f(1.0, 0.0, 1.0, 1.0));
            DeveloperButton->setActiveTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
    endEditCP(DeveloperButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask );

	GraphicButton = osg::Button::create();
    beginEditCP(GraphicButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask );
            GraphicButton->setMinSize(Vec2f(50, 25));
            GraphicButton->setMaxSize(Vec2f(200, 100));
            GraphicButton->setPreferredSize(Vec2f(100, 50));
            GraphicButton->setToolTipText("These buttons are for selecting a response!");

            GraphicButton->setText("Graphics");
            GraphicButton->setFont(ButtonFont);
            GraphicButton->setTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
            GraphicButton->setRolloverTextColor(Color4f(1.0, 0.0, 1.0, 1.0));
            GraphicButton->setActiveTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
    endEditCP(GraphicButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask );

	ClassSelectionListener ExampleListener;

	MainButton->addActionListener(&ExampleListener);
	AdminButton->addActionListener(&ExampleListener);
	DeveloperButton->addActionListener(&ExampleListener);
	GraphicButton->addActionListener(&ExampleListener);

	DetailsWindow = osg::TextArea::create();
	beginEditCP(DetailsWindow, TextArea::PreferredSizeFieldMask);
		DetailsWindow->setPreferredSize(Pnt2f(200,100));
		DetailsWindow->setMinSize(Vec2f(200,100));
    endEditCP(DetailsWindow, TextArea::PreferredSizeFieldMask);

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().push_back(MainButton);
       MainInternalWindow->getChildren().push_back(AdminButton);
       MainInternalWindow->getChildren().push_back(DeveloperButton);
       MainInternalWindow->getChildren().push_back(GraphicButton);
       MainInternalWindow->getChildren().push_back(ExampleScrollPanel);
       MainInternalWindow->getChildren().push_back(DetailsWindow);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.7f,0.5f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
    endEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);

    // Create the Drawing Surface
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

    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "09Inventory");

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
