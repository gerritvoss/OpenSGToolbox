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
#include <OpenSG/UserInterface/OSGDefaultListModel.h>
#include <OpenSG/UserInterface/OSGDefaultListSelectionModel.h>



// Declare the SelectionModel up front to allow for
// the ActionListeners
ListSelectionModelPtr ExampleListSelectionModel(new DefaultListSelectionModel());
ToggleButtonPtr SingleSelectionButton;
ToggleButtonPtr SingleIntervalSelectionButton;
ToggleButtonPtr MultipleIntervalSelectionButton;

// Create ListModel   
ListPtr ExampleList;
DefaultListModelPtr ExampleListModel;
DefaultListModelPtr ExampleListModel2;

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

       switch(e.getKey())
       {
       case KeyEvent::KEY_S:
	        beginEditCP(ExampleList, List::ModelFieldMask);
                if(ExampleList->getModel() == ExampleListModel)
                {
		            ExampleList->setModel(ExampleListModel2);
                }
                else
                {
		            ExampleList->setModel(ExampleListModel);
                }
            endEditCP(ExampleList, List::ModelFieldMask);
           break;
       }
   }

   virtual void keyReleased(const KeyEvent& e)
   {
   }

   virtual void keyTyped(const KeyEvent& e)
   {
   }
};



class SingleSelectionButtonSelectedListener : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
    {

        beginEditCP(SingleIntervalSelectionButton, ToggleButton::SelectedFieldMask);
            SingleIntervalSelectionButton->setSelected(false);
        endEditCP(SingleIntervalSelectionButton, ToggleButton::SelectedFieldMask);

        beginEditCP(MultipleIntervalSelectionButton, ToggleButton::SelectedFieldMask);
            MultipleIntervalSelectionButton->setSelected(false);
        endEditCP(MultipleIntervalSelectionButton, ToggleButton::SelectedFieldMask);

        ExampleListSelectionModel->setSelectionMode(DefaultListSelectionModel::SINGLE_SELECTION);
        
    }
      virtual void buttonDeselected(const ButtonSelectedEvent& e)
   {
   }

};

class SingleIntervalSelectionButtonSelectedListener : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
    {
        beginEditCP(SingleSelectionButton, ToggleButton::SelectedFieldMask);
            SingleSelectionButton->setSelected(false);
        endEditCP(SingleSelectionButton, ToggleButton::SelectedFieldMask);

        beginEditCP(MultipleIntervalSelectionButton, ToggleButton::SelectedFieldMask);
            MultipleIntervalSelectionButton->setSelected(false);
        endEditCP(MultipleIntervalSelectionButton, ToggleButton::SelectedFieldMask);

        ExampleListSelectionModel->setSelectionMode(DefaultListSelectionModel::SINGLE_INTERVAL_SELECTION);
    }

   virtual void buttonDeselected(const ButtonSelectedEvent& e)
   {

   }
};

class MultipleIntervalSelectionButtonSelectedListener : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
    {    
        beginEditCP(SingleSelectionButton, ToggleButton::SelectedFieldMask);
            SingleSelectionButton->setSelected(false);
        endEditCP(SingleSelectionButton, ToggleButton::SelectedFieldMask);

        beginEditCP(SingleIntervalSelectionButton, ToggleButton::SelectedFieldMask);
            SingleIntervalSelectionButton->setSelected(false);
        endEditCP(SingleIntervalSelectionButton, ToggleButton::SelectedFieldMask);

        ExampleListSelectionModel->setSelectionMode(DefaultListSelectionModel::MULTIPLE_INTERVAL_SELECTION);
    }

   virtual void buttonDeselected(const ButtonSelectedEvent& e)
   {
   }

};

class AddItemButtonSelectedListener : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
    {
        std::cout << "Add Item Action" << std::endl;
		UInt32 SelectedItemIndex(ExampleList->getSelectionModel()->getMinSelectionIndex());
        ExampleListModel->insert(SelectedItemIndex, boost::any(std::string("Added")));
    }

};

class RemoveItemButtonSelectedListener : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
    {
        std::cout << "Remove Item Action" << std::endl;
		UInt32 SelectedItemIndex(ExampleList->getSelectionModel()->getMinSelectionIndex());
		ExampleListModel->erase(SelectedItemIndex);
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

    /******************************************************

            Create and edit some ToggleButtons to
			allow for dynamically changing
			List selection options.           

    ******************************************************/
    SingleSelectionButton = osg::ToggleButton::create();
    SingleIntervalSelectionButton = osg::ToggleButton::create();
    MultipleIntervalSelectionButton = osg::ToggleButton::create();

    beginEditCP(SingleSelectionButton, Button::TextFieldMask | Button::PreferredSizeFieldMask);
        SingleSelectionButton->setText("Single Selection");
        SingleSelectionButton->setPreferredSize(Vec2f(160, 50));
    endEditCP(SingleSelectionButton, Button::TextFieldMask | Button::PreferredSizeFieldMask);
        SingleSelectionButtonSelectedListener TheSingleSelectionButtonSelectedListener;
        SingleSelectionButton->addButtonSelectedListener(&TheSingleSelectionButtonSelectedListener);
    
    beginEditCP(SingleIntervalSelectionButton, Button::TextFieldMask | Button::PreferredSizeFieldMask);
        SingleIntervalSelectionButton->setText("Single Interval Selection");
        SingleIntervalSelectionButton->setPreferredSize(Vec2f(160, 50));
    endEditCP(SingleIntervalSelectionButton, Button::TextFieldMask | Button::PreferredSizeFieldMask);
        SingleIntervalSelectionButtonSelectedListener TheSingleIntervalSelectionButtonSelectedListener;
        SingleIntervalSelectionButton->addButtonSelectedListener(&TheSingleIntervalSelectionButtonSelectedListener);
    
    beginEditCP(MultipleIntervalSelectionButton, Button::TextFieldMask | Button::PreferredSizeFieldMask);
        MultipleIntervalSelectionButton->setText("Multiple Interval Selection");
        MultipleIntervalSelectionButton->setPreferredSize(Vec2f(160, 50));
    endEditCP(MultipleIntervalSelectionButton, Button::TextFieldMask | Button::PreferredSizeFieldMask);
        MultipleIntervalSelectionButtonSelectedListener TheMultipleIntervalSelectionButtonSelectedListener;
        MultipleIntervalSelectionButton->addButtonSelectedListener(&TheMultipleIntervalSelectionButtonSelectedListener);

    ButtonPtr AddItemButton = osg::Button::create();
    beginEditCP(AddItemButton, Button::TextFieldMask);
		AddItemButton->setText("Add Item");
    endEditCP(AddItemButton, Button::TextFieldMask);
    AddItemButtonSelectedListener TheAddItemButtonSelectedListener;
    AddItemButton->addActionListener(&TheAddItemButtonSelectedListener);

    ButtonPtr RemoveItemButton = osg::Button::create();
    beginEditCP(RemoveItemButton, Button::TextFieldMask);
		RemoveItemButton->setText("Remove Item");
    endEditCP(RemoveItemButton, Button::TextFieldMask);
    RemoveItemButtonSelectedListener TheRemoveItemButtonSelectedListener;
    RemoveItemButton->addActionListener(&TheRemoveItemButtonSelectedListener);

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
	ExampleListModel = DefaultListModel::create();
    ExampleListModel->pushBack(boost::any(std::string("Red")));
    ExampleListModel->pushBack(boost::any(std::string("Green")));
    ExampleListModel->pushBack(boost::any(std::string("Blue")));
    ExampleListModel->pushBack(boost::any(std::string("Orange")));
    ExampleListModel->pushBack(boost::any(std::string("Purple")));
    ExampleListModel->pushBack(boost::any(std::string("Yellow")));
    ExampleListModel->pushBack(boost::any(std::string("White")));
    ExampleListModel->pushBack(boost::any(std::string("Black")));
    ExampleListModel->pushBack(boost::any(std::string("Gray")));
    ExampleListModel->pushBack(boost::any(std::string("Brown")));
    ExampleListModel->pushBack(boost::any(std::string("Indigo")));
    ExampleListModel->pushBack(boost::any(std::string("Pink")));
    ExampleListModel->pushBack(boost::any(std::string("Violet")));
    ExampleListModel->pushBack(boost::any(std::string("Mauve")));
    ExampleListModel->pushBack(boost::any(std::string("Peach")));
    
	ExampleListModel2 = DefaultListModel::create();
    ExampleListModel2->pushBack(boost::any(std::string("One")));
    ExampleListModel2->pushBack(boost::any(std::string("Two")));
    ExampleListModel2->pushBack(boost::any(std::string("Three")));
    ExampleListModel2->pushBack(boost::any(std::string("Four")));
    ExampleListModel2->pushBack(boost::any(std::string("Five")));
    ExampleListModel2->pushBack(boost::any(std::string("Six")));
    ExampleListModel2->pushBack(boost::any(std::string("Seven")));
    ExampleListModel2->pushBack(boost::any(std::string("Eight")));
    ExampleListModel2->pushBack(boost::any(std::string("Nine")));
    ExampleListModel2->pushBack(boost::any(std::string("Ten")));
    ExampleListModel2->pushBack(boost::any(std::string("Eleven")));
    ExampleListModel2->pushBack(boost::any(std::string("Twelve")));
    ExampleListModel2->pushBack(boost::any(std::string("Thirteen")));
    ExampleListModel2->pushBack(boost::any(std::string("Fourteen")));

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

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().push_back(SingleSelectionButton);
       MainInternalWindow->getChildren().push_back(SingleIntervalSelectionButton);
       MainInternalWindow->getChildren().push_back(MultipleIntervalSelectionButton);
       MainInternalWindow->getChildren().push_back(ExampleScrollPanel);
       MainInternalWindow->getChildren().push_back(AddItemButton);
       MainInternalWindow->getChildren().push_back(RemoveItemButton);
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
