// OpenSG Tutorial Example: Creating a Border
//
// This tutorial explains how to implement the 
// TabPanel and its characteristics
// 
// Includes: TabPanel creation and example TabPanel, as well as 
// utilizing ActionListeners to add/remove Tabs on mouseclicks

// GLUT is used for window handling
#include <OpenSG/OSGGLUT.h>

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// The GLUT-OpenSG connection class
#include <OpenSG/OSGGLUTWindow.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/Input/OSGWindowAdapter.h>

// The general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

// Input
#include <OpenSG/Input/OSGWindowUtils.h>


// UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

bool ExitApp = false;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2s Size);

// 15TabPanel Headers
#include <sstream>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGBoxLayout.h>
#include <OpenSG/UserInterface/OSGCardLayout.h>
#include <OpenSG/UserInterface/OSGUIDefines.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGTabPanel.h>
#include <OpenSG/UserInterface/OSGUIRectangle.h>


    /******************************************************

            Create TabPanel and some of the Buttons
			up front so the ActionListeners can 
			reference them
            
    ******************************************************/

TabPanelPtr ExampleTabPanel;
ButtonPtr ExampleTabContentA;
ButtonPtr ExampleTabContentB;
FramePtr createMainFrame(void);

    /******************************************************
                 Create ActionListeners
    ******************************************************/

class AddTabActionListener : public ActionListener
{ 
public:

   virtual void actionPerformed(const ActionEvent& e)
    {
      
    /******************************************************
                 
			Create a Tab and edit texts accordingly.
            
    ******************************************************/

        ButtonPtr AddedTabButton = Button::create(),
        AddedTabContent = Button::create();
        beginEditCP(AddedTabButton, Button::TextFieldMask);
            AddedTabButton->setText("Tab7");
        endEditCP(AddedTabButton, Button::TextFieldMask);

        beginEditCP(AddedTabContent, Button::TextFieldMask);
            AddedTabContent->setText("This is where the new Tab content hangs out");
        endEditCP(AddedTabContent, Button::TextFieldMask);
        
        // Determine if the number of Tabs is 6 and 
        // if so, add a 7th Tab
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

   virtual void actionPerformed(const ActionEvent& e)
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
// Create the WindowEvent 
WindowEventProducerPtr TutorialWindowEventProducer;


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
class TutorialMouseListener : public MouseListener
{
  public:
    virtual void mouseClicked(const MouseEvent& e)
    {
    }
    virtual void mouseEntered(const MouseEvent& e)
    {
    }
    virtual void mouseExited(const MouseEvent& e)
    {
    }
    virtual void mousePressed(const MouseEvent& e)
    {
        if(TutorialWindowEventProducer->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
            mgr->mouseButtonPress(e.getButton(), e.getLocation().x(), e.getLocation().y());
        }
    }
    virtual void mouseReleased(const MouseEvent& e)
    {
        if(TutorialWindowEventProducer->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
           mgr->mouseButtonRelease(e.getButton(), e.getLocation().x(), e.getLocation().y());
        }
    }
};

class TutorialMouseMotionListener : public MouseMotionListener
{
  public:
    virtual void mouseMoved(const MouseEvent& e)
    {
        if(TutorialWindowEventProducer->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
            mgr->mouseMove(e.getLocation().x(), e.getLocation().y());
        }
    }

    virtual void mouseDragged(const MouseEvent& e)
    {
        if(TutorialWindowEventProducer->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
        {
            mgr->mouseMove(e.getLocation().x(), e.getLocation().y());
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

    TutorialMouseListener mouseListener;
    TutorialMouseMotionListener mouseMotionListener;
    TutorialWindowEventProducer->addMouseListener(&mouseListener);
    TutorialWindowEventProducer->addMouseMotionListener(&mouseMotionListener);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TutorialWindowEventProducer->addWindowListener(&TheTutorialWindowListener);

   // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(90, 270, 16, 16);

    // Make Main Scene Node
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        scene->setCore(osg::Group::create());
 
        // Add the Torus as a Child
        scene->addChild(TorusGeometryNode);
    }
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    // Create the Graphics
    GraphicsPtr TutorialGraphics = osg::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();



 // Create the Drawing Surface
    UIDrawingSurfacePtr TutorialDrawingSurface = UIDrawingSurface::create();
    beginEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask | UIDrawingSurface::EventProducerFieldMask);
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setRootFrame(createMainFrame());
        TutorialDrawingSurface->setEventProducer(TutorialWindowEventProducer);
    endEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask | UIDrawingSurface::EventProducerFieldMask);
    
    //Make A 3D Rectangle to draw the UI on
    UIRectanglePtr UIRectCore = UIRectangle::create();
    beginEditCP(UIRectCore, UIRectangle::PointFieldMask | UIRectangle::WidthFieldMask | UIRectangle::HeightFieldMask | UIRectangle::DrawingSurfaceFieldMask);
        UIRectCore->setPoint(Pnt3f(-250.0,-250.0,370.0));
        UIRectCore->setWidth(500.0);
        UIRectCore->setHeight(500.0);
        UIRectCore->setDrawingSurface(TutorialDrawingSurface);
    endEditCP(UIRectCore, UIRectangle::PointFieldMask | UIRectangle::WidthFieldMask | UIRectangle::HeightFieldMask | UIRectangle::DrawingSurfaceFieldMask);
    
    NodePtr UIRectNode = osg::Node::create();
    beginEditCP(UIRectNode, Node::CoreFieldMask);
        UIRectNode->setCore(UIRectCore);
    endEditCP(UIRectNode, Node::CoreFieldMask);
    
    beginEditCP(scene, Node::ChildrenFieldMask);
        // add the UIRect as a child
        scene->addChild(UIRectNode);
    endEditCP(scene, Node::ChildrenFieldMask);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
    mgr->setRoot(scene);

    // Show the whole Scene
    mgr->showAll();

    TutorialWindowEventProducer->openWindow(Pnt2s(50,50),
                                        Vec2s(550,550),
                                        "OpenSG 20UIRectangle Window");

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
void reshape(Vec2s Size)
{
    mgr->resize(Size.x(), Size.y());
}

FramePtr createMainFrame(void)
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
        ExampleTabButton3->setText("Rotate");
    endEditCP(ExampleTabButton3, Button::TextFieldMask);
        
    beginEditCP(ExampleTabButton4, Button::TextFieldMask);
        ExampleTabButton4->setText("Tab4");
    endEditCP(ExampleTabButton4, Button::TextFieldMask);
        
    beginEditCP(ExampleTabButton5, Button::TextFieldMask);
        ExampleTabButton5->setText("Zoom");
    endEditCP(ExampleTabButton5, Button::TextFieldMask);
        
    beginEditCP(ExampleTabButton6, Button::TextFieldMask);
        ExampleTabButton6->setText("Drag");
    endEditCP(ExampleTabButton6, Button::TextFieldMask);
    
    beginEditCP(ExampleTabContentA, Button::TextFieldMask);
        ExampleTabContentA->setText("Add another Tab");
    endEditCP(ExampleTabContentA, Button::TextFieldMask);
    // Add ActionListener
    AddTabActionListener TheAddTabActionListener;
    ExampleTabContentA->addActionListener( &TheAddTabActionListener);

    beginEditCP(ExampleTabContentB, Button::TextFieldMask);
        ExampleTabContentB->setText("Add a Tab in Tab1!");
    endEditCP(ExampleTabContentB, Button::TextFieldMask);
    // Add ActionListener
    RemoveTabActionListener TheRemoveTabActionListener;
    ExampleTabContentB->addActionListener( &TheRemoveTabActionListener);

    beginEditCP(ExampleTabContentC, Button::TextFieldMask);
        ExampleTabContentC->setText("Click CapsLock, then rotate scene using left Mouse button!");
    endEditCP(ExampleTabContentC, Button::TextFieldMask);
        
    beginEditCP(ExampleTabContentD, Button::TextFieldMask);
        ExampleTabContentD->setText("Zoom in and out with right Mouse button and dragging");
    endEditCP(ExampleTabContentD, Button::TextFieldMask);    

    beginEditCP(ExampleTabContentE, Button::TextFieldMask);
        ExampleTabContentE->setText("Move using center Mouse button");
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
		ExampleTabPanelButton1->setText("This");
	endEditCP(ExampleTabPanelButton1, Button::TextFieldMask);
	
	beginEditCP(ExampleTabPanelButton2, Button::TextFieldMask);
		ExampleTabPanelButton2->setText("is a");
	endEditCP(ExampleTabPanelButton2, Button::TextFieldMask);
	
	beginEditCP(ExampleTabPanelButton3, Button::TextFieldMask);
		ExampleTabPanelButton3->setText("sample");
	endEditCP(ExampleTabPanelButton3, Button::TextFieldMask);
	
	beginEditCP(ExampleTabPanelButton4, Button::TextFieldMask);
		ExampleTabPanelButton4->setText("UIRectangle");
	endEditCP(ExampleTabPanelButton4, Button::TextFieldMask);
	
	beginEditCP(ExampleTabPanelButton5, Button::TextFieldMask);
		ExampleTabPanelButton5->setText("containing");
	endEditCP(ExampleTabPanelButton5, Button::TextFieldMask);
	
	beginEditCP(ExampleTabPanelButton6, Button::TextFieldMask);
		ExampleTabPanelButton6->setText("interactive components");
	endEditCP(ExampleTabPanelButton6, Button::TextFieldMask);

    // Create and edit Panel Layout
    BoxLayoutPtr TabPanelLayout = osg::BoxLayout::create();
    beginEditCP(TabPanelLayout, BoxLayout::AlignmentFieldMask);
        TabPanelLayout->setAlignment(VERTICAL_ALIGNMENT);
    endEditCP(TabPanelLayout, BoxLayout::AlignmentFieldMask);

    // Create and edit Panel
    PanelPtr ExampleTabPanelPanel = osg::Panel::create();
    beginEditCP(ExampleTabPanelPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
        ExampleTabPanelPanel->setPreferredSize(Vec2s(180, 500));
        ExampleTabPanelPanel->getChildren().addValue(ExampleTabPanelButton1);
        ExampleTabPanelPanel->getChildren().addValue(ExampleTabPanelButton2);
        ExampleTabPanelPanel->getChildren().addValue(ExampleTabPanelButton3);
        ExampleTabPanelPanel->getChildren().addValue(ExampleTabPanelButton4);
        ExampleTabPanelPanel->getChildren().addValue(ExampleTabPanelButton5);
        ExampleTabPanelPanel->getChildren().addValue(ExampleTabPanelButton6);
        ExampleTabPanelPanel->setLayout(TabPanelLayout);
    endEditCP(ExampleTabPanelPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask);

    ExampleTabPanel = osg::TabPanel::create();
    beginEditCP(ExampleTabPanel, TabPanel::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::ActiveTabFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);
        ExampleTabPanel->setPreferredSize(Vec2s(350,350));
        ExampleTabPanel->addTab(ExampleTabButton1, ExampleTabContentA);
        ExampleTabPanel->addTab(ExampleTabButton2, ExampleTabContentB);
        ExampleTabPanel->addTab(ExampleTabButton3, ExampleTabContentC);
        ExampleTabPanel->addTab(ExampleTabButton4, ExampleTabPanelPanel);
        ExampleTabPanel->addTab(ExampleTabButton5, ExampleTabContentD);
        ExampleTabPanel->addTab(ExampleTabButton6, ExampleTabContentE);
        ExampleTabPanel->setActiveTab(3);
        ExampleTabPanel->setTabAlignment(AXIS_CENTER_ALIGNMENT);
        ExampleTabPanel->setTabPlacement(PLACEMENT_SOUTH);
    endEditCP(ExampleTabPanel, TabPanel::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::ActiveTabFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);

	
    // Create The Main Frame
    FramePtr MainFrame = osg::Frame::create();

    /******************************************************

            By using CardLayout, the TabPanel  
			automatically takes up the entire
			MainFrame (which can be very useful
			with TabPanel).

    ******************************************************/
    CardLayoutPtr MainFrameLayout = osg::CardLayout::create();

    beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);
       MainFrame->setLayout(MainFrameLayout);
       MainFrame->getChildren().addValue(ExampleTabPanel);
    endEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);

	return MainFrame;
}

