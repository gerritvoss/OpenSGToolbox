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

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

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

void keyPressed(KeyEventDetails* const details,
                List* const ExampleList,
                ListModel* const ExampleListModel,
                ListModel* const ExampleListModel2)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }

    switch(details->getKey())
    {
        case KeyEventDetails::KEY_S:
            ExampleList->setSelectable(!ExampleList->getSelectable());
            break;
        case KeyEventDetails::KEY_M:
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

void handleSingleSelection(ButtonSelectedEventDetails* const details,
                           List* const ExampleList,
                           ToggleButton* const SingleIntervalSelectionButton,
                           ToggleButton* const MultipleIntervalSelectionButton)
{
    SingleIntervalSelectionButton->setSelected(false);

    MultipleIntervalSelectionButton->setSelected(false);

    ExampleList->getSelectionModel()->setSelectionMode(DefaultListSelectionModel::SINGLE_SELECTION);
}

void handleSingleIntervalSelection(ButtonSelectedEventDetails* const details,
                                   List* const ExampleList,
                                   ToggleButton* const SingleSelectionButton,
                                   ToggleButton* const MultipleIntervalSelectionButton)
{
    SingleSelectionButton->setSelected(false);

    MultipleIntervalSelectionButton->setSelected(false);

    ExampleList->getSelectionModel()->setSelectionMode(DefaultListSelectionModel::SINGLE_INTERVAL_SELECTION);
}

void handleMultipleIntervalSelection(ButtonSelectedEventDetails* const details,
                                     List* const ExampleList,
                                     ToggleButton* const SingleIntervalSelectionButton,
                                     ToggleButton* const SingleSelectionButton)
{    
    SingleSelectionButton->setSelected(false);

    SingleIntervalSelectionButton->setSelected(false);

    ExampleList->getSelectionModel()->setSelectionMode(DefaultListSelectionModel::MULTIPLE_INTERVAL_SELECTION);
}


void handleAddItem(ActionEventDetails* const details,
                   List* const ExampleList)
{
    UInt32 SelectedItemIndex(ExampleList->getSelectionModel()->getMinSelectionIndex());
    dynamic_cast<DefaultListModel*>(ExampleList->getModel())->insert(SelectedItemIndex, boost::any(std::string("Added")));
}

void handleRemoveItem(ActionEventDetails* const details,
                      List* const ExampleList)
{
    UInt32 SelectedItemIndex(ExampleList->getSelectionModel()->getMinSelectionIndex());
    dynamic_cast<DefaultListModel*>(ExampleList->getModel())->erase(SelectedItemIndex);
}

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

        // Make Torus Node (creates Torus in background of scene)
        NodeRecPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

        // Make Main Scene Node and add the Torus
        NodeRecPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(TorusGeometryNode);

        // Create the Graphics
        GraphicsRecPtr TutorialGraphics = Graphics2D::create();

        // Initialize the LookAndFeelManager to enable default settings
        LookAndFeelManager::the()->getLookAndFeel()->init();

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
        DefaultListModelRecPtr ExampleListModel = DefaultListModel::create();
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

        DefaultListModelRecPtr ExampleListModel2 = DefaultListModel::create();
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
            by the Action.

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
        ListRecPtr ExampleList = List::create();
        ExampleList->setPreferredSize(Vec2f(200, 300));
        ExampleList->setOrientation(List::VERTICAL_ORIENTATION);
        //ExampleList->setOrientation(List::HORIZONTAL_ORIENTATION);
        ExampleList->setModel(ExampleListModel);


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
            TogggleButtons with Action attached 
to them so this code is commented out.

         ******************************************************/

        //SelectionModel.setMode(DefaultListSelectionModel::SINGLE_SELECTION);
        //SelectionModel.setMode(DefaultListSelectionModel::SINGLE_INTERVAL_SELECTION);
        //SelectionModel.setMode(DefaultListSelectionModel::MULTIPLE_INTERVAL_SELECTION);

        // Create a ScrollPanel for easier viewing of the List (see 27ScrollPanel)
        ScrollPanelRecPtr ExampleScrollPanel = ScrollPanel::create();
        ExampleScrollPanel->setPreferredSize(Vec2f(200,300));
        ExampleScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //ExampleScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        ExampleScrollPanel->setViewComponent(ExampleList);

        /******************************************************

          Create and edit some ToggleButtons to
          allow for dynamically changing
          List selection options.           

         ******************************************************/
        ToggleButtonRecPtr SingleSelectionButton = ToggleButton::create();
        ToggleButtonRecPtr SingleIntervalSelectionButton = ToggleButton::create();
        ToggleButtonRecPtr MultipleIntervalSelectionButton = ToggleButton::create();

        SingleSelectionButton->setText("Single Selection");
        SingleSelectionButton->setPreferredSize(Vec2f(160, 50));
        SingleSelectionButton->connectButtonSelected(boost::bind(handleSingleSelection, _1,
                                                           ExampleList.get(),
                                                           SingleIntervalSelectionButton.get(),
                                                           MultipleIntervalSelectionButton.get()));

        SingleIntervalSelectionButton->setText("Single Interval Selection");
        SingleIntervalSelectionButton->setPreferredSize(Vec2f(160, 50));
        SingleIntervalSelectionButton->connectButtonSelected(boost::bind(handleSingleIntervalSelection, _1,
                                                                         ExampleList.get(),
                                                                         SingleSelectionButton.get(),
                                                                         MultipleIntervalSelectionButton.get()));

        MultipleIntervalSelectionButton->setText("Multiple Interval Selection");
        MultipleIntervalSelectionButton->setPreferredSize(Vec2f(160, 50));
        MultipleIntervalSelectionButton->connectButtonSelected(boost::bind(handleMultipleIntervalSelection, _1,
                                                                         ExampleList.get(),
                                                                         SingleIntervalSelectionButton.get(),
                                                                         SingleSelectionButton.get()));

        ButtonRecPtr AddItemButton = Button::create();
        AddItemButton->setText("Add Item");
        AddItemButton->connectActionPerformed(boost::bind(handleAddItem, _1,
                                                          ExampleList.get()));

        ButtonRecPtr RemoveItemButton = Button::create();
        RemoveItemButton->setText("Remove Item");
        RemoveItemButton->connectActionPerformed(boost::bind(handleRemoveItem, _1,
                                                             ExampleList.get()));


        // Create MainFramelayout
        FlowLayoutRecPtr MainInternalWindowLayout = FlowLayout::create();
        MainInternalWindowLayout->setOrientation(FlowLayout::HORIZONTAL_ORIENTATION);
        MainInternalWindowLayout->setMajorAxisAlignment(0.5f);
        MainInternalWindowLayout->setMinorAxisAlignment(0.5f);

        // Create The Main InternalWindow
        // Create Background to be used with the Main InternalWindow
        ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

        InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
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
        UIDrawingSurfaceRecPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);

        TutorialDrawingSurface->openWindow(MainInternalWindow);

        // Create the UI Foreground Object
        UIForegroundRecPtr TutorialUIForeground = UIForeground::create();

        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);


        TutorialWindow->connectKeyTyped(boost::bind(keyPressed, _1,
                                                    ExampleList.get(),
                                                    ExampleListModel.get(),
                                                    ExampleListModel2.get()));

        // Tell the Manager what to manage
        sceneManager.setRoot(scene);

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
                                   "18List");

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
