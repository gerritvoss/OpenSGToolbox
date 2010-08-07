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

// 18List Headers
#include "OSGLookAndFeelManager.h"
#include "OSGColorLayer.h"
#include "OSGBevelBorder.h"
#include "OSGFlowLayout.h"
#include "OSGButton.h"
#include "OSGToggleButton.h"
#include "OSGScrollPanel.h"

// List header files
#include "OSGList.h"
#include "OSGDefaultListModel.h"
#include "OSGDefaultListSelectionModel.h"



// Declare the SelectionModel up front to allow for
// the ActionListeners
ListSelectionModelPtr ExampleListSelectionModel(new DefaultListSelectionModel());
ToggleButtonRefPtr SingleSelectionButton;
ToggleButtonRefPtr SingleIntervalSelectionButton;
ToggleButtonRefPtr MultipleIntervalSelectionButton;

// Create ListModel   
ListRefPtr ExampleList;
DefaultListModelRefPtr ExampleListModel;
DefaultListModelRefPtr ExampleListModel2;

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

        switch(e->getKey())
        {
            case KeyEvent::KEY_S:
                ExampleList->setSelectable(!ExampleList->getSelectable());
                break;
            case KeyEvent::KEY_M:
                if(ExampleList->getModel() == ExampleListModel)
                {
                    ExampleList->setModel(ExampleListModel2);
                }
                else
                {
                    ExampleList->setModel(ExampleListModel);
                }
                break;
        }
    }

    virtual void keyReleased(const KeyEventUnrecPtr e)
    {
    }

    virtual void keyTyped(const KeyEventUnrecPtr e)
    {
    }
};



class SingleSelectionButtonSelectedListener : public ButtonSelectedListener
{
  public:

    virtual void buttonSelected(const ButtonSelectedEventUnrecPtr e)
    {

        SingleIntervalSelectionButton->setSelected(false);

        MultipleIntervalSelectionButton->setSelected(false);

        ExampleListSelectionModel->setSelectionMode(DefaultListSelectionModel::SINGLE_SELECTION);

    }
    virtual void buttonDeselected(const ButtonSelectedEventUnrecPtr e)
    {
    }

};

class SingleIntervalSelectionButtonSelectedListener : public ButtonSelectedListener
{
  public:

    virtual void buttonSelected(const ButtonSelectedEventUnrecPtr e)
    {
        SingleSelectionButton->setSelected(false);

        MultipleIntervalSelectionButton->setSelected(false);

        ExampleListSelectionModel->setSelectionMode(DefaultListSelectionModel::SINGLE_INTERVAL_SELECTION);
    }

    virtual void buttonDeselected(const ButtonSelectedEventUnrecPtr e)
    {

    }
};

class MultipleIntervalSelectionButtonSelectedListener : public ButtonSelectedListener
{
  public:

    virtual void buttonSelected(const ButtonSelectedEventUnrecPtr e)
    {    
        SingleSelectionButton->setSelected(false);

        SingleIntervalSelectionButton->setSelected(false);

        ExampleListSelectionModel->setSelectionMode(DefaultListSelectionModel::MULTIPLE_INTERVAL_SELECTION);
    }

    virtual void buttonDeselected(const ButtonSelectedEventUnrecPtr e)
    {
    }

};

class AddItemButtonSelectedListener : public ActionListener
{
  public:

    virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
        std::cout << "Add Item Action" << std::endl;
        UInt32 SelectedItemIndex(ExampleList->getSelectionModel()->getMinSelectionIndex());
        ExampleListModel->insert(SelectedItemIndex, boost::any(std::string("Added")));
    }

};

class RemoveItemButtonSelectedListener : public ActionListener
{
  public:

    virtual void actionPerformed(const ActionEventUnrecPtr e)
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

    /******************************************************

            Create and edit some ToggleButtons to
			allow for dynamically changing
			List selection options.           

    ******************************************************/
    SingleSelectionButton = OSG::ToggleButton::create();
    SingleIntervalSelectionButton = OSG::ToggleButton::create();
    MultipleIntervalSelectionButton = OSG::ToggleButton::create();

        SingleSelectionButton->setText("Single Selection");
        SingleSelectionButton->setPreferredSize(Vec2f(160, 50));
        SingleSelectionButtonSelectedListener TheSingleSelectionButtonSelectedListener;
        SingleSelectionButton->addButtonSelectedListener(&TheSingleSelectionButtonSelectedListener);
    
        SingleIntervalSelectionButton->setText("Single Interval Selection");
        SingleIntervalSelectionButton->setPreferredSize(Vec2f(160, 50));
        SingleIntervalSelectionButtonSelectedListener TheSingleIntervalSelectionButtonSelectedListener;
        SingleIntervalSelectionButton->addButtonSelectedListener(&TheSingleIntervalSelectionButtonSelectedListener);
    
        MultipleIntervalSelectionButton->setText("Multiple Interval Selection");
        MultipleIntervalSelectionButton->setPreferredSize(Vec2f(160, 50));
        MultipleIntervalSelectionButtonSelectedListener TheMultipleIntervalSelectionButtonSelectedListener;
        MultipleIntervalSelectionButton->addButtonSelectedListener(&TheMultipleIntervalSelectionButtonSelectedListener);

    ButtonRefPtr AddItemButton = OSG::Button::create();
		AddItemButton->setText("Add Item");
    AddItemButtonSelectedListener TheAddItemButtonSelectedListener;
    AddItemButton->addActionListener(&TheAddItemButtonSelectedListener);

    ButtonRefPtr RemoveItemButton = OSG::Button::create();
		RemoveItemButton->setText("Remove Item");
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
        ExampleList->setPreferredSize(Vec2f(200, 300));
        ExampleList->setOrientation(List::VERTICAL_ORIENTATION);
        //ExampleList->setOrientation(List::HORIZONTAL_ORIENTATION);
		ExampleList->setModel(ExampleListModel);

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
    ScrollPanelRefPtr ExampleScrollPanel = ScrollPanel::create();
        ExampleScrollPanel->setPreferredSize(Vec2f(200,300));
        ExampleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //ExampleScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    ExampleScrollPanel->setViewComponent(ExampleList);

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
       MainInternalWindow->pushToChildren(SingleSelectionButton);
       MainInternalWindow->pushToChildren(SingleIntervalSelectionButton);
       MainInternalWindow->pushToChildren(MultipleIntervalSelectionButton);
       MainInternalWindow->pushToChildren(ExampleScrollPanel);
       MainInternalWindow->pushToChildren(AddItemButton);
       MainInternalWindow->pushToChildren(RemoveItemButton);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.7f,0.5f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);

    // Create the Drawing Surface
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
            "18List");

    //Enter main Loop
    TutorialWindow->mainLoop();

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
