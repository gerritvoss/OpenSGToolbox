// OpenSG Tutorial Example: Creating a Border
//
// This tutorial explains how to implement the 
// TabPanel and its characteristics
// 
// Includes: TabPanel creation and example TabPanel, as well as 
// utilizing ActionListeners to add/remove Tabs on mouseclicks

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

// 15TabPanel Headers
#include <sstream>
#include "OSGButton.h"
#include "OSGLabel.h"
#include "OSGLayers.h"
#include "OSGBoxLayout.h"
#include "OSGFlowLayout.h"
//#include "OSGUIDefines.h"
#include "OSGPanel.h"
#include "OSGTabPanel.h"

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

/******************************************************

  Create TabPanel and some of the Buttons
  up front so the ActionListeners can 
  reference them

 ******************************************************/

TabPanelRefPtr ExampleTabPanel;
ButtonRefPtr ExampleTabContentA;
ButtonRefPtr ExampleTabContentB;

/******************************************************
  Create ActionListeners
 ******************************************************/



class AddTabActionListener : public ActionListener
{ 
  public:

    virtual void actionPerformed(const ActionEventUnrecPtr e)
    {

        /******************************************************

          Create a Tab and edit texts accordingly.

         ******************************************************/

        LabelRefPtr AddedTabLabel = Label::create();
        ButtonRefPtr AddedTabContent = Button::create();

        AddedTabLabel->setText("Tab7");
        AddedTabLabel->setBorders(NULL);
        AddedTabLabel->setBackgrounds(NULL);

        AddedTabContent->setText("This is where the new Tab content hangs out");

        // Determine if the number of Tabs is 6 and 
        // if so, add a 7th Tab
        if( ExampleTabPanel->getMFTabs()->size() == 6) 
        {
            ExampleTabPanel->addTab(AddedTabLabel, AddedTabContent);

            // Change the text on the Tabs
            ExampleTabContentA->setText("Remove Tab7 under Tab2!");

            ExampleTabContentB->setText("Remove Tab7");

        }

    }

};

class RemoveTabActionListener : public ActionListener
{
  public:

    virtual void actionPerformed(const ActionEventUnrecPtr e)
    {

        /******************************************************

          Remove the last Tab and change texts
          accordingly.

Note: removeTab()
can take either the TabName or index 
number

         ******************************************************/		
        // If the number of Tabs is 7 (one was added)
        // then remove it
        if( ExampleTabPanel->getMFTabs()->size() == 7) 
        {
            ExampleTabPanel->removeTab(6);

            ExampleTabContentA->setText("Add another Tab");

            // Change the text on the Tabs
            ExampleTabContentB->setText("Add a Tab under Tab1!");

        }
    }
};

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindow = createNativeWindow();
    TutorialWindow->initWindow();

    TutorialWindow->setDisplayCallback(display);
    TutorialWindow->setReshapeCallback(reshape);

    TutorialKeyListener TheKeyListener;
    TutorialWindow->addKeyListener(&TheKeyListener);

    // Make Torus Node
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

      Create Button Components to be used with 
      TabPanel and specify their characteristics.

Note: Buttons are used for simplicity,
any Component can be used as Tab content
or as a Tab.  A Panel with several
Buttons within it is also added.

     ******************************************************/

    LabelRefPtr ExampleTabLabel1 = OSG::Label::create();
    LabelRefPtr ExampleTabLabel2 = OSG::Label::create();
    LabelRefPtr ExampleTabLabel3 = OSG::Label::create();
    LabelRefPtr ExampleTabLabel4 = OSG::Label::create();
    LabelRefPtr ExampleTabLabel5 = OSG::Label::create();
    LabelRefPtr ExampleTabLabel6 = OSG::Label::create();
    ExampleTabContentA = OSG::Button::create();
    ExampleTabContentB = OSG::Button::create();
    ButtonRefPtr ExampleTabContentC = OSG::Button::create();
    ButtonRefPtr ExampleTabContentD = OSG::Button::create();
    ButtonRefPtr ExampleTabContentE = OSG::Button::create();
    ButtonRefPtr ExampleTabContentF = OSG::Button::create();

    ExampleTabLabel1->setText("Tab1");
    ExampleTabLabel1->setBorders(NULL);
    ExampleTabLabel1->setBackgrounds(NULL);

    ExampleTabLabel2->setText("Tab2");
    ExampleTabLabel2->setBorders(NULL);
    ExampleTabLabel2->setBackgrounds(NULL);

    ExampleTabLabel3->setText("Tab3");
    ExampleTabLabel3->setBorders(NULL);
    ExampleTabLabel3->setBackgrounds(NULL);

    ExampleTabLabel4->setText("Tab4");
    ExampleTabLabel4->setBorders(NULL);
    ExampleTabLabel4->setBackgrounds(NULL);

    ExampleTabLabel5->setText("Tab5");
    ExampleTabLabel5->setBorders(NULL);
    ExampleTabLabel5->setBackgrounds(NULL);

    ExampleTabLabel6->setText("Tab6");
    ExampleTabLabel6->setBorders(NULL);
    ExampleTabLabel6->setBackgrounds(NULL);

    ExampleTabContentA->setText("Add another Tab");
    // Add ActionListener
    AddTabActionListener TheAddTabActionListener;
    ExampleTabContentA->addActionListener( &TheAddTabActionListener);

    ExampleTabContentB->setText("Add a Tab in Tab1!");
    // Add ActionListener
    RemoveTabActionListener TheRemoveTabActionListener;
    ExampleTabContentB->addActionListener( &TheRemoveTabActionListener);

    ExampleTabContentC->setText("Stuff for Tab3");

    ExampleTabContentD->setText("Stuff for Tab5");

    ExampleTabContentE->setText("Stuff for Tab6");

    /******************************************************

      Create a Panel to add to the TabPanel

     ******************************************************/

    // Create and edit the Panel Buttons
    ButtonRefPtr ExampleTabPanelButton1 = OSG::Button::create();
    ButtonRefPtr ExampleTabPanelButton2 = OSG::Button::create();
    ButtonRefPtr ExampleTabPanelButton3 = OSG::Button::create();
    ButtonRefPtr ExampleTabPanelButton4 = OSG::Button::create();
    ButtonRefPtr ExampleTabPanelButton5 = OSG::Button::create();
    ButtonRefPtr ExampleTabPanelButton6 = OSG::Button::create();

    ExampleTabPanelButton1->setText("This");

    ExampleTabPanelButton2->setText("is a");

    ExampleTabPanelButton3->setText("sample");

    ExampleTabPanelButton4->setText("Panel");

    ExampleTabPanelButton5->setText("within");

    ExampleTabPanelButton6->setText("TabPanel");

    // Create and edit Panel Layout
    BoxLayoutRefPtr TabPanelLayout = OSG::BoxLayout::create();
    TabPanelLayout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);

    // Create and edit Panel
    PanelRefPtr ExampleTabPanelPanel = OSG::Panel::create();
    ExampleTabPanelPanel->setPreferredSize(Vec2f(180, 500));
    ExampleTabPanelPanel->pushToChildren(ExampleTabPanelButton1);
    ExampleTabPanelPanel->pushToChildren(ExampleTabPanelButton2);
    ExampleTabPanelPanel->pushToChildren(ExampleTabPanelButton3);
    ExampleTabPanelPanel->pushToChildren(ExampleTabPanelButton4);
    ExampleTabPanelPanel->pushToChildren(ExampleTabPanelButton5);
    ExampleTabPanelPanel->pushToChildren(ExampleTabPanelButton6);
    ExampleTabPanelPanel->setBorders(NULL);
    ExampleTabPanelPanel->setBackgrounds(NULL);
    ExampleTabPanelPanel->setLayout(TabPanelLayout);

    /******************************************************

      Create TabPanel.  TabPanel automatically
      sizes objects within it to cause the appearance
      of Tabs.  The following functions are 
      unique to TabPanel:
      -addTab(TAB_OBJECT, TAB_CONENT):
      Determine the Tab and content for a new 
      Tab.  See below for detailed explanation
      of arguments.
      -removeTab(TAB_OBJECT or TAB_INDEX):
      Remove a Tab based on either the Tab name
      or the index of the Tab.  See below for 
      detailed explanation of arguments.
      -setActiveTab(TAB_INDEX): Determine which Tab
      is Active (ie shown) based in index.
      See below for detailed explanation of 
      arguments.
      -insertTab(TAB_OBJECT or TAB_INDEX, NEW_TAB_OBJECT, 
      NEW_TAB_CONTENT): Insert a new Tab by
      either an existing Tab (the Tab will 
      be inserted before this Tab) or by 
      its index.
      -tabAlignment(ENUM):  Determine the alignment
      of the Tabs.  Takes AXIS_CENTER_ALIGNMENT,
      AXIS_MAX_ALIGNMENT, and AXIS_MIN_ALIGNMENT
      arguments.
      -tabPlacement(ENUM): Determine location of
      the Tabs around the Tab content.  Takes
      PLACEMENT_NORTH, PLACEMENT_SOUTH, 
      PLACEMENT_WEST, and PLACEMENT_EAST 
      arguments.

      Definition of terms:
TAB_OBJECT: This denotes a component which
is used as the Tab itself.
TAB_INDEX: This denotes the index within
the "list" of Tabs.  The first Tab
is indexed as 0, and subsequent Tabs
are 1, 2, etc.
TAB_CONTENT: This denotes the Component
which will be displayed within the
Tab.

Note: The TabPanel has a PreferredSize
which it displays at and if the Frame is 
too small, then the TabPanel will appear
distorted.  Also, removeTab/addTab are most 
useful when combined with ActionListeners 
to allow for interactability with the 
TabPanel.  An example of this is shown
above, allowing for a Tab to be created/
removed by the user.

     ******************************************************/
    ExampleTabPanel = OSG::TabPanel::create();
    ExampleTabPanel->setPreferredSize(Vec2f(600,600));
    ExampleTabPanel->addTab(ExampleTabLabel1, ExampleTabContentA);
    ExampleTabPanel->addTab(ExampleTabLabel2, ExampleTabContentB);
    ExampleTabPanel->addTab(ExampleTabLabel3, ExampleTabContentC);
    ExampleTabPanel->addTab(ExampleTabLabel4, ExampleTabPanelPanel);
    ExampleTabPanel->addTab(ExampleTabLabel5, ExampleTabContentD);
    ExampleTabPanel->addTab(ExampleTabLabel6, ExampleTabContentE);
    ExampleTabPanel->setTabAlignment(0.5f);
    ExampleTabPanel->setTabPlacement(TabPanel::PLACEMENT_NORTH);
    ExampleTabPanel->setSelectedIndex(3);
    /******************************************************

      By using CardLayout, the TabPanel  
      automatically takes up the entire
      MainFrame (which can be very useful
      with TabPanel).

     ******************************************************/
    LayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
    MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
    MainInternalWindow->pushToChildren(ExampleTabPanel);
    MainInternalWindow->setLayout(MainInternalWindowLayout);
    MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
    MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
    MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.85f,0.85f));
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
                               "15TabPanel");

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
