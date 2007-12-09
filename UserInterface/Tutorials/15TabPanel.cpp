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



// Create tabPanel and some of the Buttons up front so 
//that the ActionListeners can reference them
TabPanelPtr tabPanel;
ButtonPtr buttonA;
ButtonPtr buttonB;
// Create ActionListeners so that a Tab can be added
// and removed
class addTab : public ActionListener
{ 
public:

   virtual void actionPerformed(const ActionEvent& e)
	{
		// Create a Tab, and add it (see below for
		// explanations)
		ButtonPtr tabButton = Button::create(),
		tabContents = Button::create();
		beginEditCP(tabButton, Button::TextFieldMask);
			tabButton->setText("Tab7");
		endEditCP(tabButton, Button::TextFieldMask);

		beginEditCP(tabContents, Button::TextFieldMask);
			tabContents->setText("This is where the new Tab content hangs out");
		endEditCP(tabContents, Button::TextFieldMask);
		
		// Determine if the number of Tabs is 6 and 
		// if so, add a 7th Tab
		if( tabPanel->getTabs().getSize() == 6) {
		
		beginEditCP(tabPanel, TabPanel::TabsFieldMask);
		
			tabPanel->addTab(tabButton, tabContents);

		endEditCP(tabPanel, TabPanel::TabsFieldMask);
		
		// Change the text on the Tabs

		beginEditCP(buttonA, Button::TextFieldMask);
			buttonA->setText("Remove Tab7 under Tab2!");
		endEditCP(buttonA, Button::TextFieldMask);

		beginEditCP(buttonB, Button::TextFieldMask);
			buttonB->setText("Remove Tab7");
		endEditCP(buttonB, Button::TextFieldMask);

		
		}

	}
   

private:

};

// Creates class to remove a Tab
class removeTab : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
	{
		// If the number of Tabs is 7 (one was added)
		// then remove it
		if( tabPanel->getTabs().getSize() == 7) {
		beginEditCP(tabPanel, TabPanel::TabsFieldMask);
			// Removes the Tab.  This can be done by index number
			// or by putting the Tab name
			tabPanel->removeTab(6);
		endEditCP(tabPanel, TabPanel::TabsFieldMask);

		
		beginEditCP(buttonA, Button::TextFieldMask);
			buttonA->setText("Add another Tab");
		endEditCP(buttonA, Button::TextFieldMask);

		// Change the text on the Tabs
		beginEditCP(buttonB, Button::TextFieldMask);
			buttonB->setText("Add a Tab under Tab1!");
		endEditCP(buttonB, Button::TextFieldMask);

		}
	}
};

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    WindowEventProducerPtr TheWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TheWindowEventProducer->initWindow();
    
    TheWindowEventProducer->setDisplayCallback(display);
    TheWindowEventProducer->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TheWindowEventProducer->addWindowListener(&TheTutorialWindowListener);


    // Make Torus Node
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Main Scene Node
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        scene->setCore(osg::Group::create());
 
        // add the torus as a child
        scene->addChild(TorusGeometryNode);
    }
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

	// Create the Graphics
	GraphicsPtr graphics = osg::Graphics2D::create();

	// Initialize the LookAndFeelManager to enable default settings
	LookAndFeelManager::the()->getLookAndFeel()->init();



	/******************************************************

			Create Button Components to be used with 
			TabPanel and specify their characteristics

	******************************************************/
	ButtonPtr button1 = osg::Button::create();
	ButtonPtr button2 = osg::Button::create();
	ButtonPtr button3 = osg::Button::create();
	ButtonPtr button4 = osg::Button::create();
	ButtonPtr button5 = osg::Button::create();
	ButtonPtr button6 = osg::Button::create();
	buttonA = osg::Button::create();
	buttonB = osg::Button::create();
	ButtonPtr buttonC = osg::Button::create();
	ButtonPtr buttonD = osg::Button::create();
	ButtonPtr buttonE = osg::Button::create();
	ButtonPtr buttonF = osg::Button::create();


	beginEditCP(button1, Button::TextFieldMask);
		button1->setText("Tab1");
	endEditCP(button1, Button::TextFieldMask);
	
	beginEditCP(button2, Button::TextFieldMask);
		button2->setText("Tab2");
	endEditCP(button2, Button::TextFieldMask);
		
	beginEditCP(button3, Button::TextFieldMask);
		button3->setText("Tab3");
	endEditCP(button3, Button::TextFieldMask);
		
	beginEditCP(button4, Button::TextFieldMask);
		button4->setText("Tab4");
	endEditCP(button4, Button::TextFieldMask);
		
	beginEditCP(button5, Button::TextFieldMask);
		button5->setText("Tab5");
	endEditCP(button5, Button::TextFieldMask);
		
	beginEditCP(button6, Button::TextFieldMask);
		button6->setText("Tab6");
	endEditCP(button6, Button::TextFieldMask);
	
	beginEditCP(buttonA, Button::TextFieldMask);
		buttonA->setText("Add another Tab");
	endEditCP(buttonA, Button::TextFieldMask);
		// Add ActionListener
		addTab button6Add;
		buttonA->addActionListener( &button6Add);

	beginEditCP(buttonB, Button::TextFieldMask);
		buttonB->setText("Add a Tab in Tab1!");
	endEditCP(buttonB, Button::TextFieldMask);
		// Add ActionListener
		removeTab button6Remove;
		buttonB->addActionListener( &button6Remove);

	beginEditCP(buttonC, Button::TextFieldMask);
		buttonC->setText("Stuff for Tab3");
	endEditCP(buttonC, Button::TextFieldMask);
		
	beginEditCP(buttonD, Button::TextFieldMask);
		buttonD->setText("Stuff for Tab5");
	endEditCP(buttonD, Button::TextFieldMask);	

	beginEditCP(buttonE, Button::TextFieldMask);
		buttonE->setText("Stuff for Tab6");
	endEditCP(buttonE, Button::TextFieldMask);


		
	/******************************************************

			Create a Panel to add to the TabPanel

	******************************************************/

	// Create and edit the Panel buttons
	ButtonPtr tabPanelButton1 = osg::Button::create();
	ButtonPtr tabPanelButton2 = osg::Button::create();
	ButtonPtr tabPanelButton3 = osg::Button::create();
	ButtonPtr tabPanelButton4 = osg::Button::create();
	ButtonPtr tabPanelButton5 = osg::Button::create();
	ButtonPtr tabPanelButton6 = osg::Button::create();

	// Create and edit Panel layout
	BoxLayoutPtr TabPanelLayout = osg::BoxLayout::create();
	beginEditCP(TabPanelLayout, BoxLayout::AlignmentFieldMask);
		TabPanelLayout->setAlignment(VERTICAL_ALIGNMENT);
	endEditCP(TabPanelLayout, BoxLayout::AlignmentFieldMask);

	// Create and edit Panel
	PanelPtr tabPanelPanel = osg::Panel::create();
	beginEditCP(tabPanelPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask);
		tabPanelPanel->setPreferredSize( Vec2s(180, 500) );
		tabPanelPanel->getChildren().addValue(tabPanelButton1);
		tabPanelPanel->getChildren().addValue(tabPanelButton2);
		tabPanelPanel->getChildren().addValue(tabPanelButton3);
		tabPanelPanel->getChildren().addValue(tabPanelButton4);
		tabPanelPanel->getChildren().addValue(tabPanelButton5);
		tabPanelPanel->getChildren().addValue(tabPanelButton6);
		tabPanelPanel->setLayout(TabPanelLayout);
	endEditCP(tabPanelPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask);


	
	/******************************************************

			Create TabPanel.  TabPanel automatically
			sizes objects within it to cause the appearance
			of Tabs.  The following functions are 
			unique to TabPanel:
			-addTab(TAB_OBJECT, OBJECT_DISPLAYED_BY_TAB)
				The first argument is the Component which
				appears as the Tab while the second
				is the Component which is the Tab content
			-removeTab(TAB_OBJECT or TAB_INDEX)
				This removes a Tab.  Argument can be either
				TabComponent name (as added by addTab) or
				the Index Number of the Tab.  Note that
				the index starts at 0, so the first Tab
				is #0.  See the ActionListener above
				for an example of how this is used.
			-setActiveTab(TAB_INDEX)
				This sets which Tab appears to be selected
				by the numerical order in which they are 
				added (note the index starts with 0)
			-insertTab(TAB_OBJECT, NEW_TAB_OBJECT, NEW_TAB_CONTENT)
				or insertTab(TAB_INDEX, NEW_TAB_OBJECT, NEW_TAB_CONTENT)
				This lets you insert a Tab anywhere in the
				Tab order.  The first argument can be 
				either the index you want the new Tab,
				or the existing Tab you want the
				new Tab placed before.  The last two
				arguments are the same as with the
				addTab function
			-tabAlignment(ALIGNMENT) uses AXIS_CENTER_ALIGNMENT,
				AXIS_MAX_ALIGNMENT, and AXIS_MIN_ALIGNMENT
				to determine how the Tabs are aligned
			-tabPlacement(LOCATION) uses PLACEMENT_NORTH,
				PLACEMENT_SOUTH, PLACEMENT_WEST, and 
				PLACEMENT_EAST to determine where the Tabs
				are placed

			Note that the TabPanel has a PreferredSize
			which it displays at and if the Frame is 
			too small, then the TabPanel will appear
			distorted.  Also, removeTab is most useful
			when combined with ActionListeners to allow
			for interactability. 

	******************************************************/
	tabPanel = osg::TabPanel::create();
	beginEditCP(tabPanel, Component::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::ActiveTabFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);
		tabPanel->setPreferredSize( Vec2s(350,350) );
		tabPanel->addTab(button1, buttonA);
		tabPanel->addTab(button2, buttonB);
		tabPanel->addTab(button3, buttonC);
		tabPanel->addTab(button4, tabPanelPanel);
		tabPanel->addTab(button5, buttonD);
		tabPanel->addTab(button6, buttonE);
		tabPanel->setActiveTab(3);
		tabPanel->setTabAlignment(AXIS_CENTER_ALIGNMENT);
		tabPanel->setTabPlacement(PLACEMENT_SOUTH);
	endEditCP(tabPanel, Component::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::ActiveTabFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);


	// Create The Main Frame
	FramePtr MainFrame = osg::Frame::create();

	
	/******************************************************

			CardLayout causes the TabPanel 
			to occupy the entire MainFrame 
			view (useful with TabPanel)

	******************************************************/
	CardLayoutPtr MainFrameLayout = osg::CardLayout::create();

	beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);
	   MainFrame->setLayout(MainFrameLayout);
	   MainFrame->getChildren().addValue(tabPanel);
	endEditCP  (MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);

	// Create the Drawing Surface
	UIDrawingSurfacePtr drawingSurface = UIDrawingSurface::create();
	beginEditCP(drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask | UIDrawingSurface::EventProducerFieldMask);
		drawingSurface->setGraphics(graphics);
		drawingSurface->setRootFrame(MainFrame);
	    drawingSurface->setEventProducer(TheWindowEventProducer);
    endEditCP  (drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask | UIDrawingSurface::EventProducerFieldMask);
	
	// Create the UI Foreground Object
	UIForegroundPtr foreground = osg::UIForeground::create();

	beginEditCP(foreground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
	    foreground->setDrawingSurface(drawingSurface);
		foreground->setFramePositionOffset(Vec2s(0,0));
		foreground->setFrameBounds(Vec2f(0.65,0.65));
    endEditCP  (foreground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
 
    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the manager what to manage
    mgr->setWindow(MainWindow);
    mgr->setRoot(scene);

	// Add the UI Foreground Object to the Scene
	ViewportPtr viewport = mgr->getWindow()->getPort(0);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);
		viewport->getForegrounds().addValue(foreground);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);

    // Show the whole scene
    mgr->showAll();

    TheWindowEventProducer->openWindow(Pnt2s(50,50),
                                        Vec2s(900,900),
                                        "OpenSG 15TabPanel Window");

    //Main Event Loop
    while(!ExitApp)
    {
        TheWindowEventProducer->update();
        TheWindowEventProducer->draw();
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