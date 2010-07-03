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
#include "OSGLayers.h"
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
#include "OSGBoxLayout.h"
#include "OSGCardLayout.h"
//#include "OSGUIDefines.h"
#include "OSGPanel.h"
#include "OSGTabPanel.h"
#include "OSGUIRectangle.h"

// Declare some variables/functions up front
TabPanelRefPtr ExampleTabPanel;
ButtonRefPtr ExampleTabContentA;
ButtonRefPtr ExampleTabContentB;
InternalWindowRefPtr createMainInternalWindow(void);

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
                
				 Create ActionListeners for TabPanel.
				 Note: This tutorial uses as its 
				 base 15TabPanel; for commented version
				 see 15TabPanel.

    ******************************************************/

class AddTabActionListener : public ActionListener
{ 
public:

   virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
      
        ButtonRefPtr AddedTabButton = Button::create(),
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

};

class RemoveTabActionListener : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEventUnrecPtr e)
    {

        if( ExampleTabPanel->getMFTabs()->size() == 7) 
		{
				ExampleTabPanel->removeTab(6);
	        
				ExampleTabContentA->setText("Add another Tab");

			// Change the text on the Tabs
				ExampleTabContentB->setText("Add a Tab under Tab1!");

        }
    }
};
    
RemoveTabActionListener TheRemoveTabActionListener;
AddTabActionListener TheAddTabActionListener;

    /******************************************************

             Create ActionListeners to let the 
			 Mouse change viewing angle and move
			 UIRectangle around.

    ******************************************************/

class TutorialMouseListener : public MouseListener
{
  public:
    virtual void mouseClicked(const MouseEventUnrecPtr e)
    {
    }
    virtual void mouseEntered(const MouseEventUnrecPtr e)
    {
    }
    virtual void mouseExited(const MouseEventUnrecPtr e)
    {
    }
    virtual void mousePressed(const MouseEventUnrecPtr e)
    {
        if(TutorialWindow->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
            mgr->mouseButtonPress(e->getButton(), e->getLocation().x(), e->getLocation().y());
        }
    }
    virtual void mouseReleased(const MouseEventUnrecPtr e)
    {
        if(TutorialWindow->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
           mgr->mouseButtonRelease(e->getButton(), e->getLocation().x(), e->getLocation().y());
        }
    }
};

class TutorialMouseMotionListener : public MouseMotionListener
{
  public:
    virtual void mouseMoved(const MouseEventUnrecPtr e)
    {
        if(TutorialWindow->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
            mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
        }
    }

    virtual void mouseDragged(const MouseEventUnrecPtr e)
    {
        if(TutorialWindow->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
            mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
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

    /******************************************************

             Add MouseListeners and WindowListeners 
			 to the WindowEvent.

    ******************************************************/

    TutorialMouseListener TheTutorialMouseListener;
    TutorialMouseMotionListener TheTutorialMouseMotionListener;
    TutorialWindow->addMouseListener(&TheTutorialMouseListener);
    TutorialWindow->addMouseMotionListener(&TheTutorialMouseMotionListener);
    TutorialKeyListener TheKeyListener;
    TutorialWindow->addKeyListener(&TheKeyListener);

    // Make Torus Node (creates Torus in background of scene)
    NodeRefPtr TorusGeometryNode = makeTorus(90, 270, 16, 16);

    // Make Main Scene Node and add the Torus
    NodeRefPtr scene = OSG::Node::create();
        scene->setCore(OSG::Group::create());
        scene->addChild(TorusGeometryNode);

    // Create the Graphics
    GraphicsRefPtr TutorialGraphics = OSG::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

    /******************************************************

             The Drawing Surface is created the
			 same as with previous Tutorials
			 (however the MainInternalWindow is created
			 in a function below).

    ******************************************************/

    UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);
  
	TutorialDrawingSurface->openWindow(createMainInternalWindow());

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
    UIRectangleRefPtr ExampleUIRectangle = UIRectangle::create();
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
    NodeRefPtr ExampleUIRectangleNode = OSG::Node::create();
        ExampleUIRectangleNode->setCore(ExampleUIRectangle);
    
        // Add the UIRectangle as a child to the scene
        scene->addChild(ExampleUIRectangleNode);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindow);
    mgr->setRoot(scene);
    //mgr->setRoot(ExampleUIRectangleNode);

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
            WinSize,
            "01RubberBandCamera");

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

InternalWindowRefPtr createMainInternalWindow(void)
{
    /******************************************************

            Create Button Components to be used with 
            TabPanel and specify their characteristics.

			Note: Buttons are used for simplicity,
			any Component can be used as Tab content
			or as a Tab.  A Panel with several
			Buttons within it is also added.

    ******************************************************/

    ButtonRefPtr ExampleTabButton1 = OSG::Button::create();
    ButtonRefPtr ExampleTabButton2 = OSG::Button::create();
    ButtonRefPtr ExampleTabButton3 = OSG::Button::create();
    ButtonRefPtr ExampleTabButton4 = OSG::Button::create();
    ButtonRefPtr ExampleTabButton5 = OSG::Button::create();
    ButtonRefPtr ExampleTabButton6 = OSG::Button::create();
    ExampleTabContentA = OSG::Button::create();
    ExampleTabContentB = OSG::Button::create();
    ButtonRefPtr ExampleTabContentC = OSG::Button::create();
    ButtonRefPtr ExampleTabContentD = OSG::Button::create();
    ButtonRefPtr ExampleTabContentE = OSG::Button::create();
    ButtonRefPtr ExampleTabContentF = OSG::Button::create();

        ExampleTabButton1->setText("Tab1");
    
        ExampleTabButton2->setText("Tab2");
        
        ExampleTabButton3->setText("To Rotate");
        
        ExampleTabButton4->setText("Tab4");
        
        ExampleTabButton5->setText("To Zoom");
        
        ExampleTabButton6->setText("To Move");
    
        ExampleTabContentA->setText("Add another Tab");
    // Add ActionListener
    ExampleTabContentA->addActionListener( &TheAddTabActionListener);

        ExampleTabContentB->setText("Add a Tab in Tab1!");
    // Add ActionListener

    ExampleTabContentB->addActionListener( &TheRemoveTabActionListener);

        ExampleTabContentC->setText("Enable CapsLock, then rotate scene using left Mouse button!");
        
        ExampleTabContentD->setText("Enable CapsLock, then zoom in and out with right Mouse button and dragging");

        ExampleTabContentE->setText("Enable CapsLock, then move using center Mouse button");
        
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

		ExampleTabPanelButton1->setText("This is a");
	
		ExampleTabPanelButton2->setText("sample");
	
		ExampleTabPanelButton3->setText("UIRectangle");
	
		ExampleTabPanelButton4->setText("containing");
	
		ExampleTabPanelButton5->setText("interactive");
	
		ExampleTabPanelButton6->setText("components");

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
        ExampleTabPanelPanel->setLayout(TabPanelLayout);

    ExampleTabPanel = OSG::TabPanel::create();
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
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    CardLayoutRefPtr MainInternalWindowLayout = OSG::CardLayout::create();

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
       MainInternalWindow->pushToChildren(ExampleTabPanel);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(1.0f,1.0f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);

	return MainInternalWindow;
}

