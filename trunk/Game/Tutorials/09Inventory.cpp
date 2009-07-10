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
#include <OpenSG/Input/OSGWindowAdapter.h>

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

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

bool ExitApp = false;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// 18List Headers
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGColorLayer.h>
#include <OpenSG/UserInterface/OSGBevelBorder.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGToggleButton.h>
#include <OpenSG/UserInterface/OSGScrollPanel.h>

// List header files
#include <OpenSG/UserInterface/OSGList.h>
#include <OpenSG/UserInterface/OSGDefaultListSelectionModel.h>
#include <OpenSG/UserInterface/OSGListSelectionListener.h>



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


// Declare the SelectionModel up front to allow for
// the ActionListeners
ListSelectionModelPtr ExampleListSelectionModel(new DefaultListSelectionModel());

TextAreaPtr DetailsWindow;

// Create ListModel   
ListPtr ExampleList;
InventoryListModelPtr ExampleListModel;
InventoryPtr ExampleInventory;

class InventoryListListener: public ListSelectionListener
{
  public:
    virtual void selectionChanged(const ListSelectionEvent& e)
    {
		if(ExampleList->getSelectionModel()->getMinSelectionIndex() != -1)
		{	
			beginEditCP(DetailsWindow, TextArea::TextFieldMask);
				DetailsWindow->setText(GenericInventoryItem::Ptr::dcast(ExampleInventory->getInventoryItems(ExampleList->getSelectionModel()->getMinSelectionIndex()))->getDetails());
			endEditCP(DetailsWindow, TextArea::TextFieldMask);
		}
	}
};


class AddItemButtonSelectedListener : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
    {
    }

};

class RemoveItemButtonSelectedListener : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
    {
    }

};

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    WindowEventProducerPtr TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

	beginEditCP(TutorialWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);
		TutorialWindowEventProducer->setUseCallbackForDraw(true);
		TutorialWindowEventProducer->setUseCallbackForReshape(true);
	endEditCP(TutorialWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);
    
    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TutorialWindowEventProducer->addWindowListener(&TheTutorialWindowListener);
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

	beginEditCP(ExampleItem1, InventoryItem::NameFieldMask | GenericInventoryItem::DetailsFieldMask);
		ExampleItem1->setName(std::string("David K"));
		ExampleItem1->setDetails(std::string("Major: Human Computer Interaction \nDegree: PhD \nDepartment: Computer Science \nCollege: LAS"));
	endEditCP(ExampleItem1, InventoryItem::NameFieldMask | GenericInventoryItem::DetailsFieldMask);

	beginEditCP(ExampleItem2, InventoryItem::NameFieldMask | GenericInventoryItem::DetailsFieldMask);
		ExampleItem2->setName(std::string("Eve W"));
		ExampleItem2->setDetails(std::string("Department: Genetics Development and Cell Biology\n College: Agriculture"));
	endEditCP(ExampleItem2, InventoryItem::NameFieldMask | GenericInventoryItem::DetailsFieldMask);

	beginEditCP(ExampleItem3, InventoryItem::NameFieldMask | GenericInventoryItem::DetailsFieldMask);
		ExampleItem3->setName(std::string("Will S"));
		ExampleItem3->setDetails(std::string("Major: Art And Design\nDegree: BFA\nDepartment: Art and Design\nCollege: Design"));
	endEditCP(ExampleItem3, InventoryItem::NameFieldMask | GenericInventoryItem::DetailsFieldMask);

	ExampleInventory->addItem(ExampleItem1);
	ExampleInventory->addItem(ExampleItem2);
	ExampleInventory->addItem(ExampleItem3);



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

    // Add data to it
	ExampleListModel = InventoryListModel::create();
	ExampleListModel->addInventory(ExampleInventory);
    

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
    ExampleList = List::create();
	beginEditCP(ExampleList, List::PreferredSizeFieldMask | List::OrientationFieldMask | List::ModelFieldMask);
        ExampleList->setPreferredSize(Vec2f(200, 300));
        ExampleList->setOrientation(List::VERTICAL_ORIENTATION);
        //ExampleList->setOrientation(List::HORIZONTAL_ORIENTATION);
		ExampleList->setModel(ExampleListModel);
    endEditCP(ExampleList, List::PreferredSizeFieldMask | List::OrientationFieldMask | List::ModelFieldMask);

    ExampleList->setSelectionModel(ExampleListSelectionModel);
	InventoryListListener TheInventoryListListener;
    ExampleList->getSelectionModel()->addListSelectionListener(&TheInventoryListListener);


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
    beginEditCP(ExampleScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
        ExampleScrollPanel->setPreferredSize(Vec2f(200,300));
        ExampleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //ExampleScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(ExampleScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    ExampleScrollPanel->setViewComponent(ExampleList);

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

	DetailsWindow = osg::TextArea::create();
	beginEditCP(DetailsWindow, TextArea::PreferredSizeFieldMask);
		DetailsWindow->setPreferredSize(Pnt2f(200,100));
    endEditCP(DetailsWindow, TextArea::PreferredSizeFieldMask);

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
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

    TutorialWindowEventProducer->openWindow(Pnt2f(50,50),
                                        Vec2f(900,900),
                                        "OpenSG 18List Window");

    //Main Event Loop
    while(!ExitApp)
    {
        TutorialWindowEventProducer->update();
        TutorialWindowEventProducer->draw();
    }
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
