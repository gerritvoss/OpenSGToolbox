// OpenSG Tutorial Example: Creating a Border
//
// This tutorial explains how to implement the 
// TabPanel and its characteristics
// 
// Includes: TabPanel creation and example 

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>

// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

//Input
#include <OpenSG/Input/OSGWindowUtils.h>

// UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGCardLayout.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGUIDefines.h>

// Include TabPanel header file
#include <OpenSG/UserInterface/OSGTabPanel.h>

#include <sstream>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2s Size);

	/******************************************************
			
			Declare some variables up front to be 
			able to create an ActionListener to 
			remove and add a Tab by pressing a Button

	******************************************************/
TabPanelPtr tabPanel;
ButtonPtr button6, buttonF;



class addTab : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
	{
		ButtonPtr tabButton = Button::create(),
			tabContents = Button::create();
		
		std::stringstream stream;
		stream << _TabNumber;

		beginEditCP(tabButton, Button::TextFieldMask);
		    tabButton->setText("Tab " + stream.str());
		endEditCP(tabButton, Button::TextFieldMask);
		beginEditCP(tabContents, Button::TextFieldMask);
		    tabContents->setText("Tab Contents " + stream.str());
		endEditCP(tabContents, Button::TextFieldMask);

		beginEditCP(tabPanel, TabPanel::TabsFieldMask);
		
			tabPanel->addTab(tabButton, tabContents);

		endEditCP(tabPanel, TabPanel::TabsFieldMask);

		_TabNumber++;

	}
   
	addTab(void) : _TabNumber(6)
	{
	}
private:
	UInt32 _TabNumber;

};

class removeTab : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
	{
		beginEditCP(tabPanel, TabPanel::TabsFieldMask);
			tabPanel->removeTab(2);
		endEditCP(tabPanel, TabPanel::TabsFieldMask);
		
	}
};

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    WindowPtr MainWindow;
    WindowEventProducerPtr TheWindowEventProducer;
    createDefaultWindow(Pnt2s(50,50),
                                        Vec2s(900,900),
                                        "OpenSG 15TabPanel Window",
                                        MainWindow,
                                        TheWindowEventProducer);
    
    TheWindowEventProducer->setDisplayCallback(display);
    TheWindowEventProducer->setReshapeCallback(reshape);


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
	button6 = osg::Button::create();
	ButtonPtr buttonA = osg::Button::create();
	ButtonPtr buttonB = osg::Button::create();
	ButtonPtr buttonC = osg::Button::create();
	ButtonPtr buttonD = osg::Button::create();
	ButtonPtr buttonE = osg::Button::create();
	buttonF = osg::Button::create();


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
		buttonB->setText("Remove Tab6");
	endEditCP(buttonB, Button::TextFieldMask);

	// Add ActionListener
	removeTab button6Remove;
	buttonB->addActionListener( &button6Remove);
		
	beginEditCP(buttonC, Button::TextFieldMask);
		buttonC->setText("Stuff for Tab3");
	endEditCP(buttonC, Button::TextFieldMask);
		
	beginEditCP(buttonD, Button::TextFieldMask);
		buttonD->setText("Stuff for Tab4");
	endEditCP(buttonD, Button::TextFieldMask);	

	beginEditCP(buttonE, Button::TextFieldMask);
		buttonE->setText("Stuff for Tab5");
	endEditCP(buttonE, Button::TextFieldMask);

	beginEditCP(buttonF, Button::TextFieldMask);
		buttonF->setText("Stuff for Tab6");
	endEditCP(buttonF, Button::TextFieldMask);
	
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
				is #0
			-setActiveTab(TAB_INDEX)
				This sets which Tab appears to be selected
				by the numerical order in which they are 
				added (in this example, button1 is indexed
				as 0)
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
			distorted.
	******************************************************/
	tabPanel = osg::TabPanel::create();
	beginEditCP(tabPanel, Component::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::ActiveTabFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);
		tabPanel->setPreferredSize( Vec2s(350,350) );
		tabPanel->addTab(button1, buttonA);
		tabPanel->addTab(button2, buttonB);
		tabPanel->addTab(button3, buttonC);
		tabPanel->addTab(button4, buttonD);
		tabPanel->addTab(button5, buttonE);
		tabPanel->addTab(button6, buttonF);
		//tabPanel->removeTab(button6);
		tabPanel->setActiveTab(3);
		tabPanel->setTabAlignment(AXIS_CENTER_ALIGNMENT);
		tabPanel->setTabPlacement(PLACEMENT_SOUTH);
	endEditCP(tabPanel, Component::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::ActiveTabFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);


	// Create The Main Frame
	// Create Background to be used with the Main Frame
	FramePtr MainFrame = osg::Frame::create();
	CardLayoutPtr MainFrameLayout = osg::CardLayout::create();

	beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);
	   MainFrame->setLayout(MainFrameLayout);
	   MainFrame->getChildren().addValue(tabPanel);
	endEditCP  (MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);

	//Create the Drawing Surface
	UIDrawingSurfacePtr drawingSurface = UIDrawingSurface::create();
	beginEditCP(drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask);
		drawingSurface->setGraphics(graphics);
		drawingSurface->setRootFrame(MainFrame);
	    drawingSurface->setEventProducer(TheWindowEventProducer);
    endEditCP  (drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask);
	
	// Create the UI Foreground Object
	UIForegroundPtr foreground = osg::UIForeground::create();

	beginEditCP(foreground, UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
	    foreground->setDrawingSurface(drawingSurface);
		foreground->setFramePositionOffset(Vec2s(0,0));
		foreground->setFrameBounds(Vec2f(0.5,0.5));
	   //Set the Event Producer for the DrawingSurface
	   //This is needed in order to get Mouse/Keyboard/etc Input to the UI DrawingSurface
    endEditCP  (foreground, UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
 
    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(MainWindow );
    mgr->setRoot  (scene);

	// Add the UI Foreground Object to the Scene
	ViewportPtr viewport = mgr->getWindow()->getPort(0);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);
		viewport->getForegrounds().addValue(foreground);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);

    // show the whole scene
    mgr->showAll();

    openWindow(TheWindowEventProducer);

    return 0;
}

// redraw the window
void display(void)
{
    mgr->redraw();
}

// react to size changes
void reshape(Vec2s Size)
{
    mgr->resize(Size.x(), Size.y());
}
