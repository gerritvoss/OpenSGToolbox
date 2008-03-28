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
#include <OpenSG/UserInterface/OSGInternalWindow.h>
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
void reshape(Vec2f Size);

// 15TabPanel Headers
#include <sstream>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGUIBackgrounds.h>
#include <OpenSG/UserInterface/OSGBoxLayout.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
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

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEvent& e)
   {
       if(e.getKey() == KeyEvent::KEY_Q && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           ExitApp = true;
       }
   }

   virtual void keyReleased(const KeyEvent& e)
   {
   }

   virtual void keyTyped(const KeyEvent& e)
   {
   }
};

    /******************************************************

            Create TabPanel and some of the Buttons
			up front so the ActionListeners can 
			reference them
            
    ******************************************************/

TabPanelPtr ExampleTabPanel;
ButtonPtr ExampleTabContentA;
ButtonPtr ExampleTabContentB;

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

        LabelPtr AddedTabLabel = Label::create();
        ButtonPtr AddedTabContent = Button::create();

		beginEditCP(AddedTabLabel, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
            AddedTabLabel->setText("Tab7");
            AddedTabLabel->setBorders(NullFC);
            AddedTabLabel->setBackgrounds(NullFC);
        endEditCP(AddedTabLabel, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);

        beginEditCP(AddedTabContent, Button::TextFieldMask);
            AddedTabContent->setText("This is where the new Tab content hangs out");
        endEditCP(AddedTabContent, Button::TextFieldMask);
        
        // Determine if the number of Tabs is 6 and 
        // if so, add a 7th Tab
        if( ExampleTabPanel->getTabs().getSize() == 6) 
		{
            beginEditCP(ExampleTabPanel, TabPanel::TabsFieldMask);
                ExampleTabPanel->addTab(AddedTabLabel, AddedTabContent);
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

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    WindowEventProducerPtr TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

	beginEditCP(TutorialWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);
		TutorialWindowEventProducer->setUseCallbackForDraw(true);
		TutorialWindowEventProducer->setUseCallbackForReshape(true);
	endEditCP(TutorialWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);
    
    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TutorialWindowEventProducer->addWindowListener(&TheTutorialWindowListener);
    TutorialKeyListener TheKeyListener;
    TutorialWindowEventProducer->addKeyListener(&TheKeyListener);

    // Make Torus Node
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

            Create Button Components to be used with 
            TabPanel and specify their characteristics.

			Note: Buttons are used for simplicity,
			any Component can be used as Tab content
			or as a Tab.  A Panel with several
			Buttons within it is also added.

    ******************************************************/

    LabelPtr ExampleTabLabel1 = osg::Label::create();
    LabelPtr ExampleTabLabel2 = osg::Label::create();
    LabelPtr ExampleTabLabel3 = osg::Label::create();
    LabelPtr ExampleTabLabel4 = osg::Label::create();
    LabelPtr ExampleTabLabel5 = osg::Label::create();
    LabelPtr ExampleTabLabel6 = osg::Label::create();
    ExampleTabContentA = osg::Button::create();
    ExampleTabContentB = osg::Button::create();
    ButtonPtr ExampleTabContentC = osg::Button::create();
    ButtonPtr ExampleTabContentD = osg::Button::create();
    ButtonPtr ExampleTabContentE = osg::Button::create();
    ButtonPtr ExampleTabContentF = osg::Button::create();

    beginEditCP(ExampleTabLabel1, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        ExampleTabLabel1->setText("Tab1");
        ExampleTabLabel1->setBorders(NullFC);
        ExampleTabLabel1->setBackgrounds(NullFC);
    endEditCP(ExampleTabLabel1, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
    
    beginEditCP(ExampleTabLabel2, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        ExampleTabLabel2->setText("Tab2");
        ExampleTabLabel2->setBorders(NullFC);
        ExampleTabLabel2->setBackgrounds(NullFC);
    endEditCP(ExampleTabLabel2, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        
    beginEditCP(ExampleTabLabel3, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        ExampleTabLabel3->setText("Tab3");
        ExampleTabLabel3->setBorders(NullFC);
        ExampleTabLabel3->setBackgrounds(NullFC);
    endEditCP(ExampleTabLabel3, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        
    beginEditCP(ExampleTabLabel4, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        ExampleTabLabel4->setText("Tab4");
        ExampleTabLabel4->setBorders(NullFC);
        ExampleTabLabel4->setBackgrounds(NullFC);
    endEditCP(ExampleTabLabel4, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        
    beginEditCP(ExampleTabLabel5, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        ExampleTabLabel5->setText("Tab5");
        ExampleTabLabel5->setBorders(NullFC);
        ExampleTabLabel5->setBackgrounds(NullFC);
    endEditCP(ExampleTabLabel5, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        
    beginEditCP(ExampleTabLabel6, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
        ExampleTabLabel6->setText("Tab6");
        ExampleTabLabel6->setBorders(NullFC);
        ExampleTabLabel6->setBackgrounds(NullFC);
    endEditCP(ExampleTabLabel6, Label::TextFieldMask | Label::BordersFieldMask | Label::BackgroundsFieldMask);
    
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
        ExampleTabContentC->setText("Stuff for Tab3");
    endEditCP(ExampleTabContentC, Button::TextFieldMask);
        
    beginEditCP(ExampleTabContentD, Button::TextFieldMask);
        ExampleTabContentD->setText("Stuff for Tab5");
    endEditCP(ExampleTabContentD, Button::TextFieldMask);    

    beginEditCP(ExampleTabContentE, Button::TextFieldMask);
        ExampleTabContentE->setText("Stuff for Tab6");
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
		ExampleTabPanelButton4->setText("Panel");
	endEditCP(ExampleTabPanelButton4, Button::TextFieldMask);
	
	beginEditCP(ExampleTabPanelButton5, Button::TextFieldMask);
		ExampleTabPanelButton5->setText("within");
	endEditCP(ExampleTabPanelButton5, Button::TextFieldMask);
	
	beginEditCP(ExampleTabPanelButton6, Button::TextFieldMask);
		ExampleTabPanelButton6->setText("TabPanel");
	endEditCP(ExampleTabPanelButton6, Button::TextFieldMask);

    // Create and edit Panel Layout
    BoxLayoutPtr TabPanelLayout = osg::BoxLayout::create();
    beginEditCP(TabPanelLayout, BoxLayout::OrientationFieldMask);
        TabPanelLayout->setOrientation(BoxLayout::VERTICAL_ORIENTATION);
    endEditCP(TabPanelLayout, BoxLayout::OrientationFieldMask);

    // Create and edit Panel
    PanelPtr ExampleTabPanelPanel = osg::Panel::create();
	beginEditCP(ExampleTabPanelPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BordersFieldMask | Panel::BackgroundsFieldMask);
        ExampleTabPanelPanel->setPreferredSize(Vec2f(180, 500));
        ExampleTabPanelPanel->getChildren().push_back(ExampleTabPanelButton1);
        ExampleTabPanelPanel->getChildren().push_back(ExampleTabPanelButton2);
        ExampleTabPanelPanel->getChildren().push_back(ExampleTabPanelButton3);
        ExampleTabPanelPanel->getChildren().push_back(ExampleTabPanelButton4);
        ExampleTabPanelPanel->getChildren().push_back(ExampleTabPanelButton5);
        ExampleTabPanelPanel->getChildren().push_back(ExampleTabPanelButton6);
		ExampleTabPanelPanel->setBorders(NullFC);
		ExampleTabPanelPanel->setBackgrounds(NullFC);
        ExampleTabPanelPanel->setLayout(TabPanelLayout);
    endEditCP(ExampleTabPanelPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BordersFieldMask | Panel::BackgroundsFieldMask);

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
    ExampleTabPanel = osg::TabPanel::create();
    beginEditCP(ExampleTabPanel, TabPanel::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::ActiveTabFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);
        ExampleTabPanel->setPreferredSize(Vec2f(600,600));
        ExampleTabPanel->addTab(ExampleTabLabel1, ExampleTabContentA);
        ExampleTabPanel->addTab(ExampleTabLabel2, ExampleTabContentB);
        ExampleTabPanel->addTab(ExampleTabLabel3, ExampleTabContentC);
        ExampleTabPanel->addTab(ExampleTabLabel4, ExampleTabPanelPanel);
        ExampleTabPanel->addTab(ExampleTabLabel5, ExampleTabContentD);
        ExampleTabPanel->addTab(ExampleTabLabel6, ExampleTabContentE);
        ExampleTabPanel->setActiveTab(3);
        ExampleTabPanel->setTabAlignment(0.5f);
        ExampleTabPanel->setTabPlacement(TabPanel::PLACEMENT_NORTH);
    endEditCP(ExampleTabPanel, TabPanel::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::ActiveTabFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);

    /******************************************************

            By using CardLayout, the TabPanel  
			automatically takes up the entire
			MainFrame (which can be very useful
			with TabPanel).

    ******************************************************/
    LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorUIBackgroundPtr MainInternalWindowBackground = osg::ColorUIBackground::create();
    beginEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().push_back(ExampleTabPanel);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.85f,0.85f));
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

    TutorialWindowEventProducer->openWindow(Pnt2f(50,50),
                                        Vec2f(900,900),
                                        "OpenSG 15TabPanel Window");

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
void reshape(Vec2f Size)
{
    mgr->resize(Size.x(), Size.y());
}