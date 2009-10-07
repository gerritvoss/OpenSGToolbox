// OpenSG Tutorial Example: Creating a Border
//
// This tutorial explains how to implement the 
// TabPanel and its characteristics
// 
// Includes: TabPanel creation and example TabPanel, as well as 
// utilizing ActionListeners to add/remove Tabs on mouseclicks

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
#include <OpenSG/UserInterface/OSGLayers.h>
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

// 15TabPanel Headers
#include <sstream>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGBoxLayout.h>
#include <OpenSG/UserInterface/OSGCardLayout.h>
//#include <OpenSG/UserInterface/OSGUIDefines.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGTabPanel.h>
#include <OpenSG/UserInterface/OSGUIRectangle.h>

// Declare some variables/functions up front
TabPanelPtr ExampleTabPanel;
ButtonPtr ExampleTabContentA;
ButtonPtr ExampleTabContentB;
InternalWindowPtr createMainInternalWindow(void);

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
            TutorialWindowEventProducer->closeWindow();
       }
   }

   virtual void keyReleased(const KeyEventPtr e)
   {
   }

   virtual void keyTyped(const KeyEventPtr e)
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

   virtual void actionPerformed(const ActionEventPtr e)
    {
      
        ButtonPtr AddedTabButton = Button::create(),
        AddedTabContent = Button::create();
        beginEditCP(AddedTabButton, Button::TextFieldMask);
            AddedTabButton->setText("Tab7");
        endEditCP(AddedTabButton, Button::TextFieldMask);

        beginEditCP(AddedTabContent, Button::TextFieldMask);
            AddedTabContent->setText("This is where the new Tab content hangs out");
        endEditCP(AddedTabContent, Button::TextFieldMask);
        
        if( ExampleTabPanel->getTabs().getSize() == 6) 
		{
            beginEditCP(ExampleTabPanel, TabPanel::TabsFieldMask);
                ExampleTabPanel->addTab(AddedTabButton, AddedTabContent);
            endEditCP(ExampleTabPanel, TabPanel::TabsFieldMask);
        
			// Change the text on the Tabs
			beginEditCP(ExampleTabContentA, Button::TextFieldMask);
				ExampleTabContentA->setText("Remove Tab7 under Tab2!");
			endEditCP(ExampleTabContentA, Button::TextFieldMask);

			beginEditCP(ExampleTabContentB, Button::TextFieldMask);
				ExampleTabContentB->setText("Remove Tab7");
			endEditCP(ExampleTabContentB, Button::TextFieldMask);
	        
        }

    }

};

class RemoveTabActionListener : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEventPtr e)
    {

        if( ExampleTabPanel->getTabs().getSize() == 7) 
		{
			beginEditCP(ExampleTabPanel, TabPanel::TabsFieldMask);
				ExampleTabPanel->removeTab(6);
			endEditCP(ExampleTabPanel, TabPanel::TabsFieldMask);
	        
			beginEditCP(ExampleTabContentA, Button::TextFieldMask);
				ExampleTabContentA->setText("Add another Tab");
			endEditCP(ExampleTabContentA, Button::TextFieldMask);

			// Change the text on the Tabs
			beginEditCP(ExampleTabContentB, Button::TextFieldMask);
				ExampleTabContentB->setText("Add a Tab under Tab1!");
			endEditCP(ExampleTabContentB, Button::TextFieldMask);

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
    virtual void mouseClicked(const MouseEventPtr e)
    {
    }
    virtual void mouseEntered(const MouseEventPtr e)
    {
    }
    virtual void mouseExited(const MouseEventPtr e)
    {
    }
    virtual void mousePressed(const MouseEventPtr e)
    {
        if(TutorialWindowEventProducer->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
            mgr->mouseButtonPress(e->getButton(), e->getLocation().x(), e->getLocation().y());
        }
    }
    virtual void mouseReleased(const MouseEventPtr e)
    {
        if(TutorialWindowEventProducer->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
           mgr->mouseButtonRelease(e->getButton(), e->getLocation().x(), e->getLocation().y());
        }
    }
};

class TutorialMouseMotionListener : public MouseMotionListener
{
  public:
    virtual void mouseMoved(const MouseEventPtr e)
    {
        if(TutorialWindowEventProducer->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
            mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
        }
    }

    virtual void mouseDragged(const MouseEventPtr e)
    {
        if(TutorialWindowEventProducer->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
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
    TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    /******************************************************

             Add MouseListeners and WindowListeners 
			 to the WindowEvent.

    ******************************************************/

    TutorialMouseListener TheTutorialMouseListener;
    TutorialMouseMotionListener TheTutorialMouseMotionListener;
    TutorialWindowEventProducer->addMouseListener(&TheTutorialMouseListener);
    TutorialWindowEventProducer->addMouseMotionListener(&TheTutorialMouseMotionListener);
    TutorialKeyListener TheKeyListener;
    TutorialWindowEventProducer->addKeyListener(&TheKeyListener);

    // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(90, 270, 16, 16);

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

             The Drawing Surface is created the
			 same as with previous Tutorials
			 (however the MainInternalWindow is created
			 in a function below).

    ******************************************************/

    UIDrawingSurfacePtr TutorialDrawingSurface = UIDrawingSurface::create();
    beginEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindowEventProducer);
    endEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
  
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
    UIRectanglePtr ExampleUIRectangle = UIRectangle::create();
    beginEditCP(ExampleUIRectangle, UIRectangle::PointFieldMask | UIRectangle::WidthFieldMask | UIRectangle::HeightFieldMask | UIRectangle::DrawingSurfaceFieldMask);
        ExampleUIRectangle->setPoint(Pnt3f(-250,-250,200));
        ExampleUIRectangle->setWidth(500.0);
        ExampleUIRectangle->setHeight(500.0);
        ExampleUIRectangle->setDrawingSurface(TutorialDrawingSurface);
    endEditCP(ExampleUIRectangle, UIRectangle::PointFieldMask | UIRectangle::WidthFieldMask | UIRectangle::HeightFieldMask | UIRectangle::DrawingSurfaceFieldMask);
    
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
    NodePtr ExampleUIRectangleNode = osg::Node::create();
    beginEditCP(ExampleUIRectangleNode, Node::CoreFieldMask);
        ExampleUIRectangleNode->setCore(ExampleUIRectangle);
    endEditCP(ExampleUIRectangleNode, Node::CoreFieldMask);
    
    beginEditCP(scene, Node::ChildrenFieldMask);
        // Add the UIRectangle as a child to the scene
        scene->addChild(ExampleUIRectangleNode);
    endEditCP(scene, Node::ChildrenFieldMask);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
    mgr->setRoot(scene);
    //mgr->setRoot(ExampleUIRectangleNode);

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

InternalWindowPtr createMainInternalWindow(void)
{
    /******************************************************

            Create Button Components to be used with 
            TabPanel and specify their characteristics.

			Note: Buttons are used for simplicity,
			any Component can be used as Tab content
			or as a Tab.  A Panel with several
			Buttons within it is also added.

    ******************************************************/

    ButtonPtr ExampleTabButton1 = osg::Button::create();
    ButtonPtr ExampleTabButton2 = osg::Button::create();
    ButtonPtr ExampleTabButton3 = osg::Button::create();
    ButtonPtr ExampleTabButton4 = osg::Button::create();
    ButtonPtr ExampleTabButton5 = osg::Button::create();
    ButtonPtr ExampleTabButton6 = osg::Button::create();
    ExampleTabContentA = osg::Button::create();
    ExampleTabContentB = osg::Button::create();
    ButtonPtr ExampleTabContentC = osg::Button::create();
    ButtonPtr ExampleTabContentD = osg::Button::create();
    ButtonPtr ExampleTabContentE = osg::Button::create();
    ButtonPtr ExampleTabContentF = osg::Button::create();

    beginEditCP(ExampleTabButton1, Button::TextFieldMask);
        ExampleTabButton1->setText("Tab1");
    endEditCP(ExampleTabButton1, Button::TextFieldMask);
    
    beginEditCP(ExampleTabButton2, Button::TextFieldMask);
        ExampleTabButton2->setText("Tab2");
    endEditCP(ExampleTabButton2, Button::TextFieldMask);
        
    beginEditCP(ExampleTabButton3, Button::TextFieldMask);
        ExampleTabButton3->setText("To Rotate");
    endEditCP(ExampleTabButton3, Button::TextFieldMask);
        
    beginEditCP(ExampleTabButton4, Button::TextFieldMask);
        ExampleTabButton4->setText("Tab4");
    endEditCP(ExampleTabButton4, Button::TextFieldMask);
        
    beginEditCP(ExampleTabButton5, Button::TextFieldMask);
        ExampleTabButton5->setText("To Zoom");
    endEditCP(ExampleTabButton5, Button::TextFieldMask);
        
    beginEditCP(ExampleTabButton6, Button::TextFieldMask);
        ExampleTabButton6->setText("To Move");
    endEditCP(ExampleTabButton6, Button::TextFieldMask);
    
    beginEditCP(ExampleTabContentA, Button::TextFieldMask);
        ExampleTabContentA->setText("Add another Tab");
    endEditCP(ExampleTabContentA, Button::TextFieldMask);
    // Add ActionListener
    ExampleTabContentA->addActionListener( &TheAddTabActionListener);

    beginEditCP(ExampleTabContentB, Button::TextFieldMask);
        ExampleTabContentB->setText("Add a Tab in Tab1!");
    endEditCP(ExampleTabContentB, Button::TextFieldMask);
    // Add ActionListener

    ExampleTabContentB->addActionListener( &TheRemoveTabActionListener);

    beginEditCP(ExampleTabContentC, Button::TextFieldMask);
        ExampleTabContentC->setText("Enable CapsLock, then rotate scene using left Mouse button!");
    endEditCP(ExampleTabContentC, Button::TextFieldMask);
        
    beginEditCP(ExampleTabContentD, Button::TextFieldMask);
        ExampleTabContentD->setText("Enable CapsLock, then zoom in and out with right Mouse button and dragging");
    endEditCP(ExampleTabContentD, Button::TextFieldMask);    

    beginEditCP(ExampleTabContentE, Button::TextFieldMask);
        ExampleTabContentE->setText("Enable CapsLock, then move using center Mouse button");
    endEditCP(ExampleTabContentE, Button::TextFieldMask);
        
    /******************************************************

            Create a Panel to add to the TabPanel

    ******************************************************/

    // Create and edit the Panel Buttons
    ButtonPtr ExampleTabPanelButton1 = osg::Button::create();
    ButtonPtr ExampleTabPanelButton2 = osg::Button::create();
    ButtonPtr ExampleTabPanelButton3 = osg::Button::create();
    ButtonPtr ExampleTabPanelButton4 = osg::Button::create();
    ButtonPtr ExampleTabPanelButton5 = osg::Button::create();
    ButtonPtr ExampleTabPanelButton6 = osg::Button::create();

	beginEditCP(ExampleTabPanelButton1, Button::TextFieldMask);
		ExampleTabPanelButton1->setText("This is a");
	endEditCP(ExampleTabPanelButton1, Button::TextFieldMask);
	
	beginEditCP(ExampleTabPanelButton2, Button::TextFieldMask);
		ExampleTabPanelButton2->setText("sample");
	endEditCP(ExampleTabPanelButton2, Button::TextFieldMask);
	
	beginEditCP(ExampleTabPanelButton3, Button::TextFieldMask);
		ExampleTabPanelButton3->setText("UIRectangle");
	endEditCP(ExampleTabPanelButton3, Button::TextFieldMask);
	
	beginEditCP(ExampleTabPanelButton4, Button::TextFieldMask);
		ExampleTabPanelButton4->setText("containing");
	endEditCP(ExampleTabPanelButton4, Button::TextFieldMask);
	
	beginEditCP(ExampleTabPanelButton5, Button::TextFieldMask);
		ExampleTabPanelButton5->setText("interactive");
	endEditCP(ExampleTabPanelButton5, Button::TextFieldMask);
	
	beginEditCP(ExampleTabPanelButton6, Button::TextFieldMask);
		ExampleTabPanelButton6->setText("components");
	endEditCP(ExampleTabPanelButton6, Button::TextFieldMask);

    // Create and edit Panel Layout
    BoxLayoutPtr TabPanelLayout = osg::BoxLayout::create();
    beginEditCP(TabPanelLayout, BoxLayout::OrientationFieldMask);
        TabPanelLayout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);
    endEditCP(TabPanelLayout, BoxLayout::OrientationFieldMask);

    // Create and edit Panel
    PanelPtr ExampleTabPanelPanel = osg::Panel::create();
    beginEditCP(ExampleTabPanelPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
        ExampleTabPanelPanel->setPreferredSize(Vec2f(180, 500));
        ExampleTabPanelPanel->getChildren().push_back(ExampleTabPanelButton1);
        ExampleTabPanelPanel->getChildren().push_back(ExampleTabPanelButton2);
        ExampleTabPanelPanel->getChildren().push_back(ExampleTabPanelButton3);
        ExampleTabPanelPanel->getChildren().push_back(ExampleTabPanelButton4);
        ExampleTabPanelPanel->getChildren().push_back(ExampleTabPanelButton5);
        ExampleTabPanelPanel->getChildren().push_back(ExampleTabPanelButton6);
        ExampleTabPanelPanel->setLayout(TabPanelLayout);
    endEditCP(ExampleTabPanelPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask);

    ExampleTabPanel = osg::TabPanel::create();
    beginEditCP(ExampleTabPanel, TabPanel::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);
        ExampleTabPanel->setPreferredSize(Vec2f(350,350));
        ExampleTabPanel->addTab(ExampleTabButton1, ExampleTabContentA);
        ExampleTabPanel->addTab(ExampleTabButton2, ExampleTabContentB);
        ExampleTabPanel->addTab(ExampleTabButton3, ExampleTabContentC);
        ExampleTabPanel->addTab(ExampleTabButton4, ExampleTabPanelPanel);
        ExampleTabPanel->addTab(ExampleTabButton5, ExampleTabContentD);
        ExampleTabPanel->addTab(ExampleTabButton6, ExampleTabContentE);
        ExampleTabPanel->setTabAlignment(0.5f);
        ExampleTabPanel->setTabPlacement(TabPanel::PLACEMENT_SOUTH);
    endEditCP(ExampleTabPanel, TabPanel::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);
    ExampleTabPanel->setSelectedIndex(3);
	
    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);

    CardLayoutPtr MainInternalWindowLayout = osg::CardLayout::create();

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().push_back(ExampleTabPanel);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(1.0f,1.0f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
    endEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);

	return MainInternalWindow;
}

