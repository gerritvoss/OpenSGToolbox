// OpenSG Tutorial Example: Creating a Border
//
// This tutorial explains how to implement the 
// TabPanel and its characteristics
// 
// Includes: TabPanel creation and example TabPanel, as well as 
// utilizing Action to add/remove Tabs on mouseclicks

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
#include "OSGLayers.h"
#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"
#include "OSGGraphics2D.h"
#include "OSGLookAndFeelManager.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

// 15TabPanel Headers
#include <sstream>
#include "OSGButton.h"
#include "OSGBoxLayout.h"
#include "OSGCardLayout.h"
//#include "OSGUIDefines.h"
#include "OSGPanel.h"
#include "OSGTabPanel.h"
#include "OSGUIRectangle.h"

InternalWindowTransitPtr createMainInternalWindow(void);

void keyPressed(KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_Q &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
}

/******************************************************

  Create function callbacks for TabPanel.
    Note: This tutorial uses as its 
    base 15TabPanel; for commented version
    see 15TabPanel.

 ******************************************************/
void handleAddTabAction(ActionEventDetails* const details,
                        TabPanel* const ExampleTabPanel,
                        Button* const ExampleTabContentA,
                        Button* const ExampleTabContentB)
{

    ButtonRecPtr AddedTabButton = Button::create(),
                 AddedTabContent = Button::create();
    AddedTabButton->setText("Tab7");

    AddedTabContent->setText("This is where the new Tab content hangs out");

    if( ExampleTabPanel->getMFTabs()->size() == 6) 
    {
        ExampleTabPanel->addTab(AddedTabButton, AddedTabContent);

        // Change the text on the Tabs
        ExampleTabContentA->setText("Remove Tab7 under Tab2!");

        ExampleTabContentB->setText("Remove Tab7");
    }
}

void handleRemoveTabAction(ActionEventDetails* const details,
                           TabPanel* const ExampleTabPanel,
                           Button* const ExampleTabContentA,
                           Button* const ExampleTabContentB)
{

    if( ExampleTabPanel->getMFTabs()->size() == 7) 
    {
        ExampleTabPanel->removeTab(6);

        ExampleTabContentA->setText("Add another Tab");

        // Change the text on the Tabs
        ExampleTabContentB->setText("Add a Tab under Tab1!");
    }
}

void mousePressed(MouseEventDetails* const details,
                  SimpleSceneManager *mgr)
{
    if(dynamic_cast<WindowEventProducer*>(details->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_CAPS_LOCK)
    {
        mgr->mouseButtonPress(details->getButton(), details->getLocation().x(), details->getLocation().y());
    }
}

void mouseReleased(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    if(dynamic_cast<WindowEventProducer*>(details->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_CAPS_LOCK)
    {
        mgr->mouseButtonRelease(details->getButton(), details->getLocation().x(), details->getLocation().y());
    }
}

void mouseDragged(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    if(dynamic_cast<WindowEventProducer*>(details->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_CAPS_LOCK)
    {
        mgr->mouseMove(details->getLocation().x(), details->getLocation().y());
    }
}

void mouseWheelMoved(MouseWheelEventDetails* const details, SimpleSceneManager *mgr)
{
    if(dynamic_cast<WindowEventProducer*>(details->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_CAPS_LOCK)
    {
        for(UInt32 i(0) ; i<abs(details->getUnitsToScroll()) ;++i)
        {
            if(details->getUnitsToScroll() > 0)
            {
                mgr->mouseButtonPress(SimpleSceneManager::MouseDown,details->getLocation().x(),details->getLocation().y());
            }
            else if(details->getUnitsToScroll() < 0)
            {
                mgr->mouseButtonPress(SimpleSceneManager::MouseUp,details->getLocation().x(),details->getLocation().y());
            }
        }
    }
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

        TutorialWindow->connectMousePressed(boost::bind(mousePressed, _1, &sceneManager));
        TutorialWindow->connectMouseReleased(boost::bind(mouseReleased, _1, &sceneManager));
        TutorialWindow->connectMouseDragged(boost::bind(mouseDragged, _1, &sceneManager));
        TutorialWindow->connectMouseWheelMoved(boost::bind(mouseWheelMoved, _1, &sceneManager));
        TutorialWindow->connectKeyTyped(boost::bind(keyPressed, _1));

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

        // Make Torus Node (creates Torus in background of scene)
        NodeRecPtr TorusGeometryNode = makeTorus(90, 270, 16, 16);

        // Make Main Scene Node and add the Torus
        NodeRecPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(TorusGeometryNode);

        // Create the Graphics
        GraphicsRecPtr TutorialGraphics = Graphics2D::create();

        // Initialize the LookAndFeelManager to enable default settings
        LookAndFeelManager::the()->getLookAndFeel()->init();

        /******************************************************

          The Drawing Surface is created the
          same as with previous Tutorials
          (however the MainInternalWindow is created
          in a function below).

         ******************************************************/

        UIDrawingSurfaceRecPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);

        InternalWindowRecPtr MainUIWindow = createMainInternalWindow();
        TutorialDrawingSurface->openWindow(MainUIWindow);

        /******************************************************

          Create the 3D UIRectangle.  This allows
          the DrawingSurface to be rotated relative
          to the screen, allowing a 3D aspect to
          the DrawingSurface.  The Surface
          can still be interacted with, so Buttons,
          Menus, etc. all will still function
          normally.

          -setPoint(Pnt3f): Determine the location
          of the UIRectangle in 3D space.  Keep
          in mind that (0,0,0) is located 
          directly in the center of the sceen.
          (For our purposes it is the center 
          of the tori.) The point is located
          on the lower left corner of the 
          rectangle.
          -setWidth(float): Determine the Width
          of the UIRectangle.  This may 
          physically appear different depending
          on where the UIRectangle is placed
          as above (due to it being located
          further away, etc).
          -setHeight(float): Determine the Height
          of the UIRectangle.  This may 
          physically appear different depending
          on where the UIRectangle is placed
          as above (due to it being located
          further away, etc).
          -setDrawingSurface(DrawingSurface):
          Determine what DrawingSurface is
          drawn on the UIRectangle.  This 
          will typically be the main
          DrawingSurface, however, multiple
          DrawingSurfaces can be used with
          multiple UIRectangles.


         ******************************************************/   

        //Make A 3D Rectangle to draw the UI on
        UIRectangleRecPtr ExampleUIRectangle = UIRectangle::create();
        ExampleUIRectangle->setPoint(Pnt3f(-250,-250,200));
        ExampleUIRectangle->setWidth(500.0);
        ExampleUIRectangle->setHeight(500.0);
        ExampleUIRectangle->setDrawingSurface(TutorialDrawingSurface);

        /******************************************************

          Because the previous Tutorials used a 
          Viewport to view the scene, which is
          no longer being used, the UIRectangle 
          must be added to the scene for it to 
          be displayed (identical to how the
          Torus is added).

          First, create a Node, and set its
          core to be the UIRectangle.  Then,
          add that to the scene Node which 
          is created above.  This scene is
          then set as the Root for the view.
          It is possible to change this Root
          to be just the UIRectangle (as
          commented out below).

         ******************************************************/   	
        NodeRecPtr ExampleUIRectangleNode = Node::create();
        ExampleUIRectangleNode->setCore(ExampleUIRectangle);

        // Add the UIRectangle as a child to the scene
        scene->addChild(ExampleUIRectangleNode);


        // Tell the Manager what to manage
        sceneManager.setRoot(scene);
        //sceneManager.setRoot(ExampleUIRectangleNode);

        // Show the whole Scene
        sceneManager.showAll();


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "01RubberBandCamera");

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

InternalWindowTransitPtr createMainInternalWindow(void)
{
    /******************************************************

      Create Button Components to be used with 
      TabPanel and specify their characteristics.

        Note: Buttons are used for simplicity,
        any Component can be used as Tab content
        or as a Tab.  A Panel with several
        Buttons within it is also added.

     ******************************************************/

    ButtonRecPtr ExampleTabButton1 = Button::create();
    ButtonRecPtr ExampleTabButton2 = Button::create();
    ButtonRecPtr ExampleTabButton3 = Button::create();
    ButtonRecPtr ExampleTabButton4 = Button::create();
    ButtonRecPtr ExampleTabButton5 = Button::create();
    ButtonRecPtr ExampleTabButton6 = Button::create();
    ButtonRecPtr ExampleTabContentA = Button::create();
    ButtonRecPtr ExampleTabContentB = Button::create();
    ButtonRecPtr ExampleTabContentC = Button::create();
    ButtonRecPtr ExampleTabContentD = Button::create();
    ButtonRecPtr ExampleTabContentE = Button::create();
    ButtonRecPtr ExampleTabContentF = Button::create();

    ExampleTabButton1->setText("Tab1");

    ExampleTabButton2->setText("Tab2");

    ExampleTabButton3->setText("To Rotate");

    ExampleTabButton4->setText("Tab4");

    ExampleTabButton5->setText("To Zoom");

    ExampleTabButton6->setText("To Move");

    ExampleTabContentA->setText("Add another Tab");

    ExampleTabContentB->setText("Add a Tab in Tab1!");

    ExampleTabContentC->setText("Enable CapsLock, then rotate scene using left Mouse button!");

    ExampleTabContentD->setText("Enable CapsLock, then zoom in and out with right Mouse button and dragging");

    ExampleTabContentE->setText("Enable CapsLock, then move using center Mouse button");

    /******************************************************

      Create a Panel to add to the TabPanel

     ******************************************************/

    // Create and edit the Panel Buttons
    ButtonRecPtr ExampleTabPanelButton1 = Button::create();
    ButtonRecPtr ExampleTabPanelButton2 = Button::create();
    ButtonRecPtr ExampleTabPanelButton3 = Button::create();
    ButtonRecPtr ExampleTabPanelButton4 = Button::create();
    ButtonRecPtr ExampleTabPanelButton5 = Button::create();
    ButtonRecPtr ExampleTabPanelButton6 = Button::create();

    ExampleTabPanelButton1->setText("This is a");

    ExampleTabPanelButton2->setText("sample");

    ExampleTabPanelButton3->setText("UIRectangle");

    ExampleTabPanelButton4->setText("containing");

    ExampleTabPanelButton5->setText("interactive");

    ExampleTabPanelButton6->setText("components");

    // Create and edit Panel Layout
    BoxLayoutRecPtr TabPanelLayout = BoxLayout::create();
    TabPanelLayout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);

    // Create and edit Panel
    PanelRecPtr ExampleTabPanelPanel = Panel::create();
    ExampleTabPanelPanel->setPreferredSize(Vec2f(180, 500));
    ExampleTabPanelPanel->pushToChildren(ExampleTabPanelButton1);
    ExampleTabPanelPanel->pushToChildren(ExampleTabPanelButton2);
    ExampleTabPanelPanel->pushToChildren(ExampleTabPanelButton3);
    ExampleTabPanelPanel->pushToChildren(ExampleTabPanelButton4);
    ExampleTabPanelPanel->pushToChildren(ExampleTabPanelButton5);
    ExampleTabPanelPanel->pushToChildren(ExampleTabPanelButton6);
    ExampleTabPanelPanel->setLayout(TabPanelLayout);

    TabPanelRecPtr ExampleTabPanel = TabPanel::create();
    ExampleTabPanel->setPreferredSize(Vec2f(350,350));
    ExampleTabPanel->addTab(ExampleTabButton1, ExampleTabContentA);
    ExampleTabPanel->addTab(ExampleTabButton2, ExampleTabContentB);
    ExampleTabPanel->addTab(ExampleTabButton3, ExampleTabContentC);
    ExampleTabPanel->addTab(ExampleTabButton4, ExampleTabPanelPanel);
    ExampleTabPanel->addTab(ExampleTabButton5, ExampleTabContentD);
    ExampleTabPanel->addTab(ExampleTabButton6, ExampleTabContentE);
    ExampleTabPanel->setTabAlignment(0.5f);
    ExampleTabPanel->setTabPlacement(TabPanel::PLACEMENT_SOUTH);
    ExampleTabPanel->setSelectedIndex(3);

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRecPtr MainInternalWindowBackground = ColorLayer::create();
    MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    CardLayoutRecPtr MainInternalWindowLayout = CardLayout::create();

    InternalWindowRecPtr MainInternalWindow = InternalWindow::create();
    MainInternalWindow->pushToChildren(ExampleTabPanel);
    MainInternalWindow->setLayout(MainInternalWindowLayout);
    MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
    MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
    MainInternalWindow->setScalingInDrawingSurface(Vec2f(1.0f,1.0f));
    MainInternalWindow->setDrawTitlebar(false);
    MainInternalWindow->setResizable(false);

    ExampleTabContentB->connectActionPerformed(boost::bind(handleRemoveTabAction, _1,
                                                           ExampleTabPanel.get(),
                                                           ExampleTabContentA.get(),
                                                           ExampleTabContentB.get()));
    ExampleTabContentA->connectActionPerformed(boost::bind(handleAddTabAction, _1,
                                                           ExampleTabPanel.get(),
                                                           ExampleTabContentA.get(),
                                                           ExampleTabContentB.get()));

    return InternalWindowTransitPtr(MainInternalWindow);
}

