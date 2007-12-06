
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

// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

//Input
#include <OpenSG/Input/OSGWindowUtils.h>
#include <OpenSG/Input/OSGWindowAdapter.h>
// UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGBoxLayout.h>
#include <OpenSG/UserInterface/OSGCardLayout.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGUIDefines.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGToggleButton.h>
#include <OpenSG/UserInterface/OSGGridBagLayout.h>
#include <OpenSG/UserInterface/OSGTabPanel.h>
#include <OpenSG/UserInterface/OSGRadioButton.h>
#include <OpenSG/UserInterface/OSGRadioButtonGroup.h>
#include <OpenSG/UserInterface/OSGCheckboxButton.h>
#include <OpenSG/UserInterface/OSGPasswordField.h>
#include <OpenSG/UserInterface/OSGUIBackgrounds.h>
#include <OpenSG/UserInterface/OSGBorders.h>
#include <OpenSG/UserInterface/OSGTextField.h>
#include <OpenSG/UserInterface/OSGTextArea.h>
#include <OpenSG/UserInterface/OSGTextField.h>
#include <OpenSG/UserInterface/OSGSpinner.h>
#include <OpenSG/UserInterface/OSGNumberSpinnerModel.h>
#include <OpenSG/UserInterface/OSGGridBagLayout.h>
#include <OpenSG/UserInterface/OSGGridBagLayoutConstraints.h>
#include <sstream>
#include <OpenSG/UserInterface/OSGGridLayout.h>


OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
bool ExitApp = false;

RadioButtonGroup DeselectedRadioButtonGroup;
RadioButtonGroup SelectedRadioButtonGroup;
RadioButtonGroup DisabledSelectedRadioButtonGroup;
RadioButtonGroup DisabledDeselectedRadioButtonGroup;

// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2s Size);

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


PanelPtr createStatePanel(void);


// Initialize GLUT & OpenSG and set up the scene
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
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask  | Component::ConstraintsFieldMask);
    {
        scene->setCore(osg::Group::create());
 
        // add the torus as a child
        scene->addChild(TorusGeometryNode);
    }
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask  | Component::ConstraintsFieldMask);

	// Create the Graphics
	GraphicsPtr graphics = osg::Graphics2D::create();

	// Initialize the LookAndFeelManager to enable default settings
	LookAndFeelManager::the()->getLookAndFeel()->init();



	/******************************************************

			Create Button Components to be used with 
			TabPanel and specify their characteristics

	******************************************************/
	LabelPtr label1 = osg::Label::create();
	LabelPtr label2 = osg::Label::create();
	LabelPtr label3 = osg::Label::create();
	LabelPtr label4 = osg::Label::create();
	LabelPtr label5 = osg::Label::create();
	LabelPtr label6 = osg::Label::create();
	ButtonPtr buttonA = osg::Button::create();
	ButtonPtr buttonB = osg::Button::create();
	ButtonPtr buttonC = osg::Button::create();
	ButtonPtr buttonD = osg::Button::create();
	ButtonPtr buttonE = osg::Button::create();
	ButtonPtr buttonF = osg::Button::create();

	ButtonPtr button1 = osg::Button::create();
	ButtonPtr button2 = osg::Button::create();
	ButtonPtr button3 = osg::Button::create();
	ButtonPtr button4 = osg::Button::create();
	ButtonPtr button5 = osg::Button::create();
	ButtonPtr button6 = osg::Button::create();

	beginEditCP(label1, Label::TextFieldMask  | Component::ConstraintsFieldMask);
		label1->setText("State");
	endEditCP(label1, Label::TextFieldMask  | Component::ConstraintsFieldMask);
	beginEditCP(label2, Label::TextFieldMask  | Component::ConstraintsFieldMask);
		label2->setText("Tab2");
	endEditCP(label2, Label::TextFieldMask  | Component::ConstraintsFieldMask);
	beginEditCP(label3, Label::TextFieldMask  | Component::ConstraintsFieldMask);
		label3->setText("Tab3");
	endEditCP(label3, Label::TextFieldMask  | Component::ConstraintsFieldMask);
	beginEditCP(label4, Label::TextFieldMask  | Component::ConstraintsFieldMask);
		label4->setText("Tab4");
	endEditCP(label4, Label::TextFieldMask  | Component::ConstraintsFieldMask);
	beginEditCP(label5, Label::TextFieldMask  | Component::ConstraintsFieldMask);
		label5->setText("Tab5");
	endEditCP(label5, Label::TextFieldMask  | Component::ConstraintsFieldMask);
	beginEditCP(label6, Label::TextFieldMask  | Component::ConstraintsFieldMask);
		label6->setText("Tab6");
	endEditCP(label6, Label::TextFieldMask  | Component::ConstraintsFieldMask);
	
	beginEditCP(buttonA, Button::TextFieldMask  | Component::ConstraintsFieldMask);
		buttonA->setText("Add another Tab");
	endEditCP(buttonA, Button::TextFieldMask  | Component::ConstraintsFieldMask);


	beginEditCP(buttonB, Button::TextFieldMask  | Component::ConstraintsFieldMask);
		buttonB->setText("Add a Tab in Tab1!");
	endEditCP(buttonB, Button::TextFieldMask  | Component::ConstraintsFieldMask);

	beginEditCP(buttonC, Button::TextFieldMask  | Component::ConstraintsFieldMask);
		buttonC->setText("Stuff for Tab3");
	endEditCP(buttonC, Button::TextFieldMask  | Component::ConstraintsFieldMask);
		
	beginEditCP(buttonD, Button::TextFieldMask  | Component::ConstraintsFieldMask);
		buttonD->setText("Stuff for Tab5");
	endEditCP(buttonD, Button::TextFieldMask  | Component::ConstraintsFieldMask);	

	beginEditCP(buttonE, Button::TextFieldMask  | Component::ConstraintsFieldMask);
		buttonE->setText("Stuff for Tab6");
	endEditCP(buttonE, Button::TextFieldMask  | Component::ConstraintsFieldMask);


		
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
	beginEditCP(TabPanelLayout, BoxLayout::AlignmentFieldMask  | Component::ConstraintsFieldMask);
		TabPanelLayout->setAlignment(VERTICAL_ALIGNMENT);
	endEditCP(TabPanelLayout, BoxLayout::AlignmentFieldMask  | Component::ConstraintsFieldMask);

	// Create and edit Panel
	PanelPtr tabPanelPanel = osg::Panel::create();
	beginEditCP(tabPanelPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask  | Component::ConstraintsFieldMask);
		tabPanelPanel->setPreferredSize( Vec2s(180, 500) );
		tabPanelPanel->getChildren().addValue(tabPanelButton1);
		tabPanelPanel->getChildren().addValue(tabPanelButton2);
		tabPanelPanel->getChildren().addValue(tabPanelButton3);
		tabPanelPanel->getChildren().addValue(tabPanelButton4);
		tabPanelPanel->getChildren().addValue(tabPanelButton5);
		tabPanelPanel->getChildren().addValue(tabPanelButton6);
		tabPanelPanel->setLayout(TabPanelLayout);
	endEditCP(tabPanelPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask  | Component::ConstraintsFieldMask);


	
	/******************************************************

			Create TabPanel.  
	******************************************************/
	PanelPtr testing = createStatePanel();
	TabPanelPtr tabPanel = osg::TabPanel::create();
	beginEditCP(tabPanel, Component::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::ActiveTabFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask  | Component::ConstraintsFieldMask);
		tabPanel->setPreferredSize( Vec2s(600,600) );
		tabPanel->addTab(button1, testing);
		tabPanel->addTab(button2, buttonB);
		tabPanel->addTab(button3, buttonC);
		tabPanel->addTab(button4, tabPanelPanel);
		tabPanel->addTab(button5, buttonD);
		tabPanel->addTab(button6, buttonE);
		tabPanel->setActiveTab(0);
		tabPanel->setTabAlignment(AXIS_CENTER_ALIGNMENT);
		tabPanel->setTabPlacement(PLACEMENT_NORTH);
	endEditCP(tabPanel, Component::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::ActiveTabFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask  | Component::ConstraintsFieldMask);


	// Create The Main Frame
	FramePtr MainFrame = osg::Frame::create();
	// CardLayout causes the TabPanel to occupy the entire
	// MainFrame view (useful with TabPanel)
	CardLayoutPtr MainFrameLayout = osg::CardLayout::create();

	beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask  | Component::ConstraintsFieldMask);
	   MainFrame->setLayout(MainFrameLayout);
	   MainFrame->getChildren().addValue(tabPanel);
	endEditCP  (MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask  | Component::ConstraintsFieldMask);

	// Create the Drawing Surface
	UIDrawingSurfacePtr drawingSurface = UIDrawingSurface::create();
	beginEditCP(drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask  | Component::ConstraintsFieldMask);
		drawingSurface->setGraphics(graphics);
		drawingSurface->setRootFrame(MainFrame);
	    drawingSurface->setEventProducer(TheWindowEventProducer);
    endEditCP  (drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask  | Component::ConstraintsFieldMask);
	
	// Create the UI Foreground Object
	UIForegroundPtr foreground = osg::UIForeground::create();

	beginEditCP(foreground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask  | Component::ConstraintsFieldMask);
	    foreground->setDrawingSurface(drawingSurface);
		foreground->setFramePositionOffset(Vec2s(0,0));
		foreground->setFrameBounds(Vec2f(0.65,0.65));
    endEditCP  (foreground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask  | Component::ConstraintsFieldMask);
    
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
                                        "OpenSG 49LookAndFeel Window");

    //Main Event Loop
    while(!ExitApp)
    {
        TheWindowEventProducer->update();
        TheWindowEventProducer->draw();
    }
    osgExit();

    return 0;
}


PanelPtr createStatePanel(void)
{
	/******************************************************

			Create a Panel and its Layout

	******************************************************/

	GridBagLayoutPtr statePanelLayout = osg::GridBagLayout::create();
	beginEditCP(statePanelLayout, GridBagLayout::RowsFieldMask | GridBagLayout::ColumnsFieldMask  | Component::ConstraintsFieldMask);
		statePanelLayout->setRows(9);
		statePanelLayout->setColumns(5);
	endEditCP(statePanelLayout, GridBagLayout::RowsFieldMask | GridBagLayout::ColumnsFieldMask  | Component::ConstraintsFieldMask);
	
	//GridLayoutPtr statePanelLayout = osg::GridLayout::create();
	//beginEditCP(statePanelLayout);
	//	statePanelLayout->setRows(8);
	//	statePanelLayout->setColumns(5);
	//endEditCP(statePanelLayout);

	PanelPtr statePanel = osg::Panel::create();

	/******************************************************
			LayoutConstraints
				Note: 0506 represents a constraint 
					at X = 5, Y = 6
			Row0
	******************************************************/
	
	GridBagLayoutConstraintsPtr constraint0000 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0100 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0200 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0300 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0400 = osg::GridBagLayoutConstraints::create();

	beginEditCP(constraint0000, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0000->setGridX(0);
		constraint0000->setGridY(0);
	endEditCP(constraint0000, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	
	beginEditCP(constraint0100, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0100->setGridX(1);
		constraint0100->setGridY(0);
	endEditCP(constraint0100, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	
	beginEditCP(constraint0200, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0200->setGridX(2);
		constraint0200->setGridY(0);
	endEditCP(constraint0200, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);

	beginEditCP(constraint0300, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0300->setGridX(3);
		constraint0300->setGridY(0);
	endEditCP(constraint0300, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);

	beginEditCP(constraint0400, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0400->setGridX(4);
		constraint0400->setGridY(0);
	endEditCP(constraint0400, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);

	/******************************************************
							Row1
	******************************************************/
	GridBagLayoutConstraintsPtr constraint0001 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0101 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0201 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0301 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0401 = osg::GridBagLayoutConstraints::create();

	beginEditCP(constraint0001, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0001->setGridX(0);
		constraint0001->setGridY(1);
	endEditCP(constraint0001, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	
	beginEditCP(constraint0101, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0101->setGridX(1);
		constraint0101->setGridY(1);
	endEditCP(constraint0101, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	
	beginEditCP(constraint0201, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0201->setGridX(2);
		constraint0201->setGridY(1);
	endEditCP(constraint0201, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);

	beginEditCP(constraint0301, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0301->setGridX(3);
		constraint0301->setGridY(1);
	endEditCP(constraint0301, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);

	beginEditCP(constraint0401, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0401->setGridX(4);
		constraint0401->setGridY(1);
	endEditCP(constraint0401, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	/******************************************************
							Row2
	******************************************************/
	GridBagLayoutConstraintsPtr constraint0002 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0102 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0202 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0302 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0402 = osg::GridBagLayoutConstraints::create();
	
	beginEditCP(constraint0002, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0002->setGridX(0);
		constraint0002->setGridY(2);
	endEditCP(constraint0002, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	
	beginEditCP(constraint0102, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0102->setGridX(1);
		constraint0102->setGridY(2);
	endEditCP(constraint0102, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	
	beginEditCP(constraint0202, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0202->setGridX(2);
		constraint0202->setGridY(2);
	endEditCP(constraint0202, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);

	beginEditCP(constraint0302, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0302->setGridX(3);
		constraint0302->setGridY(2);
	endEditCP(constraint0302, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);

	beginEditCP(constraint0402, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0402->setGridX(4);
		constraint0402->setGridY(2);
	endEditCP(constraint0402, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	/******************************************************
							Row3
	******************************************************/
	GridBagLayoutConstraintsPtr constraint0003 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0103 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0203 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0303 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0403 = osg::GridBagLayoutConstraints::create();
	
	beginEditCP(constraint0003, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0003->setGridX(0);
		constraint0003->setGridY(3);
	endEditCP(constraint0003, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	
	beginEditCP(constraint0103, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0103->setGridX(1);
		constraint0103->setGridY(3);
	endEditCP(constraint0103, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	
	beginEditCP(constraint0203, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0203->setGridX(2);
		constraint0203->setGridY(3);
	endEditCP(constraint0203, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);

	beginEditCP(constraint0303, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0303->setGridX(3);
		constraint0303->setGridY(3);
	endEditCP(constraint0303, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);

	beginEditCP(constraint0403, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0403->setGridX(4);
		constraint0403->setGridY(3);
	endEditCP(constraint0403, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	/******************************************************
							Row4
	******************************************************/
	GridBagLayoutConstraintsPtr constraint0004 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0104 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0204 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0304 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0404 = osg::GridBagLayoutConstraints::create();
		
	beginEditCP(constraint0004, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0004->setGridX(0);
		constraint0004->setGridY(4);
	endEditCP(constraint0004, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	
	beginEditCP(constraint0104, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0104->setGridX(1);
		constraint0104->setGridY(4);
	endEditCP(constraint0104, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	
	beginEditCP(constraint0204, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0204->setGridX(2);
		constraint0204->setGridY(4);
	endEditCP(constraint0204, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);

	beginEditCP(constraint0304, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0304->setGridX(3);
		constraint0304->setGridY(4);
	endEditCP(constraint0304, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);

	beginEditCP(constraint0404, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0404->setGridX(4);
		constraint0404->setGridY(4);
	endEditCP(constraint0404, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	/******************************************************
							Row5
	******************************************************/
	GridBagLayoutConstraintsPtr constraint0005 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0105 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0205 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0305 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0405 = osg::GridBagLayoutConstraints::create();
			
	beginEditCP(constraint0005, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0005->setGridX(0);
		constraint0005->setGridY(5);
	endEditCP(constraint0005, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	
	beginEditCP(constraint0105, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0105->setGridX(1);
		constraint0105->setGridY(5);
	endEditCP(constraint0105, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	
	beginEditCP(constraint0205, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0205->setGridX(2);
		constraint0205->setGridY(5);
	endEditCP(constraint0205, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);

	beginEditCP(constraint0305, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0305->setGridX(3);
		constraint0305->setGridY(5);
	endEditCP(constraint0305, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);

	beginEditCP(constraint0405, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0405->setGridX(4);
		constraint0405->setGridY(5);
	endEditCP(constraint0405, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	/******************************************************
							Row6
	******************************************************/	
	GridBagLayoutConstraintsPtr constraint0006 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0106 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0206 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0306 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0406 = osg::GridBagLayoutConstraints::create();
			
	beginEditCP(constraint0006, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0006->setGridX(0);
		constraint0006->setGridY(6);
	endEditCP(constraint0006, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	
	beginEditCP(constraint0106, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0106->setGridX(1);
		constraint0106->setGridY(6);
	endEditCP(constraint0106, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	
	beginEditCP(constraint0206, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0206->setGridX(2);
		constraint0206->setGridY(6);
	endEditCP(constraint0206, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);

	beginEditCP(constraint0306, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0306->setGridX(3);
		constraint0306->setGridY(6);
	endEditCP(constraint0306, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);

	beginEditCP(constraint0406, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0406->setGridX(4);
		constraint0406->setGridY(6);
	endEditCP(constraint0406, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	/******************************************************
							Row7
	******************************************************/	
	GridBagLayoutConstraintsPtr constraint0007 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0107 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0207 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0307 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0407 = osg::GridBagLayoutConstraints::create();
			
	beginEditCP(constraint0007, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0007->setGridX(0);
		constraint0007->setGridY(7);
	endEditCP(constraint0007, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	
	beginEditCP(constraint0107, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0107->setGridX(1);
		constraint0107->setGridY(7);
	endEditCP(constraint0107, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	
	beginEditCP(constraint0207, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0207->setGridX(2);
		constraint0207->setGridY(7);
	endEditCP(constraint0207, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);

	beginEditCP(constraint0307, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0307->setGridX(3);
		constraint0307->setGridY(7);
	endEditCP(constraint0307, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);

	beginEditCP(constraint0407, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0407->setGridX(4);
		constraint0407->setGridY(7);
	endEditCP(constraint0407, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	/******************************************************
							Row8
	******************************************************/	
	GridBagLayoutConstraintsPtr constraint0008 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0108 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0208 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0308 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0408 = osg::GridBagLayoutConstraints::create();
			
	beginEditCP(constraint0008, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0008->setGridX(0);
		constraint0008->setGridY(8);
	endEditCP(constraint0008, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	
	beginEditCP(constraint0108, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0108->setGridX(1);
		constraint0108->setGridY(8);
	endEditCP(constraint0108, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	
	beginEditCP(constraint0208, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0208->setGridX(2);
		constraint0208->setGridY(8);
	endEditCP(constraint0208, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);

	beginEditCP(constraint0308, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0308->setGridX(3);
		constraint0308->setGridY(8);
	endEditCP(constraint0308, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);

	beginEditCP(constraint0408, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0408->setGridX(4);
		constraint0408->setGridY(8);
	endEditCP(constraint0408, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	/******************************************************
							Row9
	******************************************************/	
	GridBagLayoutConstraintsPtr constraint0009 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0109 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0209 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0309 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0409 = osg::GridBagLayoutConstraints::create();
			
	beginEditCP(constraint0009, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0009->setGridX(0);
		constraint0009->setGridY(9);
	endEditCP(constraint0009, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	
	beginEditCP(constraint0109, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0109->setGridX(1);
		constraint0109->setGridY(9);
	endEditCP(constraint0109, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	
	beginEditCP(constraint0209, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0209->setGridX(2);
		constraint0209->setGridY(9);
	endEditCP(constraint0209, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);

	beginEditCP(constraint0309, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0309->setGridX(3);
		constraint0309->setGridY(9);
	endEditCP(constraint0309, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);

	beginEditCP(constraint0409, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0409->setGridX(4);
		constraint0409->setGridY(9);
	endEditCP(constraint0409, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	/******************************************************
							Row10
	******************************************************/	
	GridBagLayoutConstraintsPtr constraint0010 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0110 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0210 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0310 = osg::GridBagLayoutConstraints::create();
	GridBagLayoutConstraintsPtr constraint0410 = osg::GridBagLayoutConstraints::create();
			
	beginEditCP(constraint0010, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0010->setGridX(0);
		constraint0010->setGridY(10);
	endEditCP(constraint0010, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	
	beginEditCP(constraint0110, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0110->setGridX(1);
		constraint0110->setGridY(10);
	endEditCP(constraint0110, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
	
	beginEditCP(constraint0210, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0210->setGridX(2);
		constraint0210->setGridY(10);
	endEditCP(constraint0210, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);

	beginEditCP(constraint0310, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0310->setGridX(3);
		constraint0310->setGridY(10);
	endEditCP(constraint0310, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);

	beginEditCP(constraint0410, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);
		constraint0410->setGridX(4);
		constraint0410->setGridY(10);
	endEditCP(constraint0410, GridBagLayoutConstraints::GridXFieldMask | GridBagLayoutConstraints::GridYFieldMask  | Component::ConstraintsFieldMask);

	/******************************************************

			Create Components to add to Panel

						Buttons
	******************************************************/
	ButtonPtr inactiveButton = osg::Button::create();
	ButtonPtr activeButton = osg::Button::create();
	ButtonPtr disabledInactiveButton = osg::Button::create();
	ButtonPtr disabledActiveButton = osg::Button::create();

	beginEditCP(inactiveButton, Button::ActiveFieldMask | Button::TextFieldMask | Component::ConstraintsFieldMask  | Component::ConstraintsFieldMask);
		inactiveButton->setActive(FALSE);
		inactiveButton->setText("Inactive");
		inactiveButton->setConstraints(constraint0101);
	endEditCP(inactiveButton, Button::ActiveFieldMask | Button::TextFieldMask | Component::ConstraintsFieldMask  | Component::ConstraintsFieldMask);
	
	beginEditCP(activeButton, Button::TextFieldMask  | Component::ConstraintsFieldMask);
		activeButton->setText("Active");
		activeButton->setConstraints(constraint0201);
	endEditCP(activeButton, Button::TextFieldMask  | Component::ConstraintsFieldMask);

	beginEditCP(disabledInactiveButton, Button::ActiveFieldMask | Component::EnabledFieldMask | Button::TextFieldMask | Component::ConstraintsFieldMask  | Component::ConstraintsFieldMask);
		disabledInactiveButton->setActive(FALSE);
		disabledInactiveButton->setEnabled(FALSE);
		disabledInactiveButton->setText("Disabled/Inactive");
		disabledInactiveButton->setConstraints(constraint0301);
	endEditCP(disabledInactiveButton, Button::ActiveFieldMask | Component::EnabledFieldMask | Button::TextFieldMask | Component::ConstraintsFieldMask  | Component::ConstraintsFieldMask);
	
	beginEditCP(disabledActiveButton, Component::EnabledFieldMask | Button::TextFieldMask| Component::ConstraintsFieldMask);
		disabledActiveButton->setEnabled(FALSE);
		disabledActiveButton->setText("Disabled");
		disabledActiveButton->setConstraints(constraint0401);
	endEditCP(disabledActiveButton, Component::EnabledFieldMask | Button::TextFieldMask| Component::ConstraintsFieldMask);
	
	/******************************************************
						ToggleButtons
	******************************************************/
	ToggleButtonPtr nonSelectedToggleButton = osg::ToggleButton::create();
	ToggleButtonPtr selectedToggleButton = osg::ToggleButton::create();
	ToggleButtonPtr disabledSelectedToggleButton = osg::ToggleButton::create();
	ToggleButtonPtr disabledNonselectedToggleButton = osg::ToggleButton::create();
	
	beginEditCP(nonSelectedToggleButton,Button::TextFieldMask| Component::ConstraintsFieldMask);
		nonSelectedToggleButton->setText("NonSelected");
		nonSelectedToggleButton->setConstraints(constraint0102);
	endEditCP(nonSelectedToggleButton, Button::TextFieldMask| Component::ConstraintsFieldMask);

	beginEditCP(selectedToggleButton, ToggleButton::SelectedFieldMask | Button::TextFieldMask| Component::ConstraintsFieldMask);
		selectedToggleButton->setSelected(TRUE);
		selectedToggleButton->setText("Selected");
		selectedToggleButton->setConstraints(constraint0202);
	endEditCP(selectedToggleButton, ToggleButton::SelectedFieldMask | Button::TextFieldMask| Component::ConstraintsFieldMask);
	
	beginEditCP(disabledSelectedToggleButton, ToggleButton::SelectedFieldMask | Component::EnabledFieldMask | Button::TextFieldMask| Component::ConstraintsFieldMask);
		disabledSelectedToggleButton->setSelected(TRUE);
		disabledSelectedToggleButton->setEnabled(FALSE);
		disabledSelectedToggleButton->setText("Disabled/Selected");
		disabledSelectedToggleButton->setConstraints(constraint0302);
	endEditCP(disabledSelectedToggleButton, ToggleButton::SelectedFieldMask | Component::EnabledFieldMask | Button::TextFieldMask| Component::ConstraintsFieldMask);
	
	beginEditCP(disabledNonselectedToggleButton, ToggleButton::SelectedFieldMask | Component::EnabledFieldMask | Button::TextFieldMask| Component::ConstraintsFieldMask);
		disabledNonselectedToggleButton->setSelected(FALSE);
		disabledNonselectedToggleButton->setEnabled(FALSE);
		disabledNonselectedToggleButton->setText("Disabled");
		disabledNonselectedToggleButton->setConstraints(constraint0402);
	endEditCP(disabledNonselectedToggleButton, ToggleButton::SelectedFieldMask | Component::EnabledFieldMask | Button::TextFieldMask| Component::ConstraintsFieldMask);

	/******************************************************
						RadioButtons
	******************************************************/
	RadioButtonPtr deselectedRadioButton = osg::RadioButton::create();
	RadioButtonPtr selectedRadioButton = osg::RadioButton::create();
	RadioButtonPtr disabledDeselectedRadioButton = osg::RadioButton::create();
	RadioButtonPtr disabledSelectedRadioButton = osg::RadioButton::create();
	DeselectedRadioButtonGroup.addButton(deselectedRadioButton);

	SelectedRadioButtonGroup.addButton(selectedRadioButton);
	
	DisabledDeselectedRadioButtonGroup.addButton(disabledDeselectedRadioButton);
	
	DisabledSelectedRadioButtonGroup.addButton(disabledSelectedRadioButton);

	beginEditCP(deselectedRadioButton, Button::TextFieldMask| Component::ConstraintsFieldMask);
		deselectedRadioButton->setText("Deselected");
		deselectedRadioButton->setConstraints(constraint0103);
	endEditCP(deselectedRadioButton, Button::TextFieldMask| Component::ConstraintsFieldMask);

	beginEditCP(selectedRadioButton, RadioButton::SelectedFieldMask | Button::TextFieldMask| Component::ConstraintsFieldMask);
		selectedRadioButton->setSelected(TRUE);
		selectedRadioButton->setText("Selected");
		selectedRadioButton->setConstraints(constraint0203);
	endEditCP(selectedRadioButton, RadioButton::SelectedFieldMask | Button::TextFieldMask| Component::ConstraintsFieldMask);

	beginEditCP(disabledDeselectedRadioButton, Component::EnabledFieldMask | RadioButton::SelectedFieldMask | Button::TextFieldMask| Component::ConstraintsFieldMask);
		disabledDeselectedRadioButton->setEnabled(FALSE);
		disabledDeselectedRadioButton->setSelected(FALSE);
		disabledDeselectedRadioButton->setText("Disabled");
		disabledDeselectedRadioButton->setConstraints(constraint0303);
	endEditCP(disabledDeselectedRadioButton, Component::EnabledFieldMask | RadioButton::SelectedFieldMask | Button::TextFieldMask| Component::ConstraintsFieldMask);
	
	beginEditCP(disabledSelectedRadioButton, Component::EnabledFieldMask | RadioButton::SelectedFieldMask | Button::TextFieldMask| Component::ConstraintsFieldMask);
		disabledSelectedRadioButton->setEnabled(FALSE);
		disabledSelectedRadioButton->setSelected(TRUE);
		disabledSelectedRadioButton->setText("Disabled/Selected");
		disabledSelectedRadioButton->setConstraints(constraint0403);
	endEditCP(disabledSelectedRadioButton, Component::EnabledFieldMask | RadioButton::SelectedFieldMask | Button::TextFieldMask| Component::ConstraintsFieldMask);
	
	
	/******************************************************
						CheckboxButtons
	******************************************************/
	CheckboxButtonPtr deselectedCheckboxButton = osg::CheckboxButton::create();
	CheckboxButtonPtr selectedCheckboxButton = osg::CheckboxButton::create();
	CheckboxButtonPtr disabledDeselectedCheckboxButton = osg::CheckboxButton::create();
	CheckboxButtonPtr disabledSelectedCheckboxButton = osg::CheckboxButton::create();

	beginEditCP(deselectedCheckboxButton, Button::TextFieldMask| Component::ConstraintsFieldMask);
		deselectedCheckboxButton->setText("Deselected");
		deselectedCheckboxButton->setConstraints(constraint0104);
	endEditCP(deselectedCheckboxButton, Button::TextFieldMask| Component::ConstraintsFieldMask);

	beginEditCP(selectedCheckboxButton, CheckboxButton::SelectedFieldMask | Button::TextFieldMask| Component::ConstraintsFieldMask);
		selectedCheckboxButton->setSelected(TRUE);
		selectedCheckboxButton->setText("Selected");
		selectedCheckboxButton->setConstraints(constraint0204);
	endEditCP(selectedCheckboxButton, CheckboxButton::SelectedFieldMask | Button::TextFieldMask| Component::ConstraintsFieldMask);

	beginEditCP(disabledDeselectedCheckboxButton, CheckboxButton::SelectedFieldMask | Component::EnabledFieldMask | Button::TextFieldMask| Component::ConstraintsFieldMask);
		disabledDeselectedCheckboxButton->setSelected(FALSE);
		disabledDeselectedCheckboxButton->setEnabled(FALSE);
		disabledDeselectedCheckboxButton->setText("Disabled");
		disabledDeselectedCheckboxButton->setConstraints(constraint0304);
	endEditCP(disabledDeselectedCheckboxButton, CheckboxButton::SelectedFieldMask | Component::EnabledFieldMask | Button::TextFieldMask| Component::ConstraintsFieldMask);

	beginEditCP(disabledSelectedCheckboxButton, CheckboxButton::SelectedFieldMask | Component::EnabledFieldMask | Button::TextFieldMask| Component::ConstraintsFieldMask);
		disabledSelectedCheckboxButton->setSelected(TRUE);
		disabledSelectedCheckboxButton->setEnabled(FALSE);
		disabledSelectedCheckboxButton->setText("Disabled/Selected");
		disabledSelectedCheckboxButton->setConstraints(constraint0404);
	endEditCP(disabledSelectedCheckboxButton, CheckboxButton::SelectedFieldMask | Component::EnabledFieldMask | Button::TextFieldMask| Component::ConstraintsFieldMask);
	/******************************************************
						TextFields
	******************************************************/
	TextFieldPtr editableTextField = osg::TextField::create();
	TextFieldPtr noneditableTextField = osg::TextField::create();
	TextFieldPtr disabledEditableTextField = osg::TextField::create();
	TextFieldPtr disabledNoneditableTextField = osg::TextField::create();

	beginEditCP(editableTextField, TextField::TextFieldMask| Component::ConstraintsFieldMask);
		editableTextField->setText("Editable");
		editableTextField->setConstraints(constraint0105);
	endEditCP(editableTextField, TextField::TextFieldMask| Component::ConstraintsFieldMask);

	beginEditCP(noneditableTextField, TextField::EditableFieldMask | TextField::TextFieldMask| Component::ConstraintsFieldMask);
		noneditableTextField->setEditable(FALSE);
		noneditableTextField->setText("Noneditable");
		noneditableTextField->setConstraints(constraint0205);
	endEditCP(noneditableTextField, TextField::EditableFieldMask | TextField::TextFieldMask| Component::ConstraintsFieldMask);
	
	beginEditCP(disabledEditableTextField, Component::EnabledFieldMask | TextField::TextFieldMask| Component::ConstraintsFieldMask);
		disabledEditableTextField->setEnabled(FALSE);
		disabledEditableTextField->setText("Disabled");
		disabledEditableTextField->setConstraints(constraint0305);
	endEditCP(disabledEditableTextField, Component::EnabledFieldMask | TextField::TextFieldMask| Component::ConstraintsFieldMask);
	
	beginEditCP(disabledNoneditableTextField, TextField::EditableFieldMask | Component::EnabledFieldMask | TextField::TextFieldMask| Component::ConstraintsFieldMask);
		disabledNoneditableTextField->setEditable(FALSE);
		disabledNoneditableTextField->setEnabled(FALSE);
		disabledNoneditableTextField->setText("Disabled/Noneditable");
		disabledNoneditableTextField->setConstraints(constraint0405);
	endEditCP(disabledNoneditableTextField, TextField::EditableFieldMask | Component::EnabledFieldMask | TextField::TextFieldMask| Component::ConstraintsFieldMask);
	/******************************************************
						TextAreas
	******************************************************/	
	TextAreaPtr editableTextArea = osg::TextArea::create();
	TextAreaPtr noneditableTextArea = osg::TextArea::create();
	TextAreaPtr disabledEditableTextArea = osg::TextArea::create();
	TextAreaPtr disabledNoneditableTextArea = osg::TextArea::create();

	beginEditCP(editableTextArea, TextArea::TextFieldMask| Component::ConstraintsFieldMask);
		editableTextArea->setText("Uneditable");
		editableTextArea->setConstraints(constraint0106);
	endEditCP(editableTextArea, TextArea::TextFieldMask| Component::ConstraintsFieldMask);

	beginEditCP(noneditableTextArea, TextArea::EditableFieldMask | TextArea::TextFieldMask| Component::ConstraintsFieldMask);
		noneditableTextArea->setEditable(FALSE);
		noneditableTextArea->setText("Uneditable");
		noneditableTextArea->setConstraints(constraint0206);
	endEditCP(noneditableTextArea, TextArea::EditableFieldMask | TextArea::TextFieldMask| Component::ConstraintsFieldMask);
	
	beginEditCP(disabledEditableTextArea, Component::EnabledFieldMask | TextArea::TextFieldMask| Component::ConstraintsFieldMask);
		disabledEditableTextArea->setEnabled(FALSE);
		disabledEditableTextArea->setText("Disabled");
		disabledEditableTextArea->setConstraints(constraint0306);
	endEditCP(disabledEditableTextArea, Component::EnabledFieldMask | TextArea::TextFieldMask| Component::ConstraintsFieldMask);
	
	beginEditCP(disabledNoneditableTextArea, TextArea::EditableFieldMask | Component::EnabledFieldMask | TextArea::TextFieldMask| Component::ConstraintsFieldMask);
		disabledNoneditableTextArea->setEditable(FALSE);
		disabledNoneditableTextArea->setEnabled(FALSE);
		disabledNoneditableTextArea->setText("Disabled");
		disabledNoneditableTextArea->setConstraints(constraint0406);
	endEditCP(disabledNoneditableTextArea, TextArea::EditableFieldMask | Component::EnabledFieldMask | TextArea::TextFieldMask| Component::ConstraintsFieldMask);

	/******************************************************
						PasswordFields
	******************************************************/	
	PasswordFieldPtr editablePasswordField = osg::PasswordField::create();
	PasswordFieldPtr nonEditablePasswordField = osg::PasswordField::create();
	PasswordFieldPtr disabledInactivePasswordField = osg::PasswordField::create();
	PasswordFieldPtr disabledActivePasswordField = osg::PasswordField::create(); 
	
	beginEditCP(editablePasswordField, PasswordField::TextFieldMask| Component::ConstraintsFieldMask);
		editablePasswordField->setText("editable");
		editablePasswordField->setConstraints(constraint0107);
	endEditCP(editablePasswordField, PasswordField::TextFieldMask| Component::ConstraintsFieldMask);

	beginEditCP(nonEditablePasswordField, TextArea::EditableFieldMask | PasswordField::TextFieldMask| Component::ConstraintsFieldMask);
		nonEditablePasswordField->setEditable(FALSE);
		nonEditablePasswordField->setText("editable");
		nonEditablePasswordField->setConstraints(constraint0207);
	endEditCP(nonEditablePasswordField, TextArea::EditableFieldMask | PasswordField::TextFieldMask| Component::ConstraintsFieldMask);
	
	beginEditCP(disabledInactivePasswordField, Component::EnabledFieldMask | PasswordField::TextFieldMask| Component::ConstraintsFieldMask);
		disabledInactivePasswordField->setEnabled(FALSE);
		disabledInactivePasswordField->setText("editable");
		disabledInactivePasswordField->setConstraints(constraint0307);
	endEditCP(disabledInactivePasswordField, Component::EnabledFieldMask | PasswordField::TextFieldMask| Component::ConstraintsFieldMask);
	
	beginEditCP(disabledActivePasswordField, TextArea::EditableFieldMask | Component::EnabledFieldMask | PasswordField::TextFieldMask| Component::ConstraintsFieldMask);
		disabledActivePasswordField->setEditable(FALSE);
		disabledActivePasswordField->setEnabled(FALSE);
		disabledActivePasswordField->setText("editable");
		disabledActivePasswordField->setConstraints(constraint0407);
	endEditCP(disabledActivePasswordField, TextArea::EditableFieldMask | Component::EnabledFieldMask | PasswordField::TextFieldMask| Component::ConstraintsFieldMask);

	/******************************************************
						Spinners
	******************************************************/
	SpinnerPtr inactiveSpinner = osg::Spinner::create();
	SpinnerPtr activeSpinner = osg::Spinner::create();
	SpinnerPtr disabledInactiveSpinner = osg::Spinner::create();
	SpinnerPtr disabledActiveSpinner = osg::Spinner::create();

	Int32SpinnerModelPtr spinnerModel(new Int32SpinnerModel());
	spinnerModel->setMaximum(10);
    spinnerModel->setMinimum(-10);
    spinnerModel->setStepSize(1);
    spinnerModel->setValue(SharedFieldPtr(new SFInt32(0)));
    inactiveSpinner->setModel(spinnerModel);
    activeSpinner->setModel(spinnerModel);
    disabledInactiveSpinner->setModel(spinnerModel);
    disabledActiveSpinner->setModel(spinnerModel);

	/******************************************************
						Labels
	******************************************************/
	LabelPtr buttonLabel = osg::Label::create();
	LabelPtr toggleButtonLabel = osg::Label::create();
	LabelPtr radioButtonLabel = osg::Label::create();
	LabelPtr checkboxButtonLabel = osg::Label::create();
	LabelPtr textFieldLabel = osg::Label::create();
	LabelPtr textAreaLabel = osg::Label::create();
	LabelPtr passwordFieldLabel = osg::Label::create();
	LabelPtr spinnerLabel = osg::Label::create();
	LabelPtr enabledLabel = osg::Label::create();
	LabelPtr disabledLabel = osg::Label::create();
	EmptyUIBackgroundPtr labelBackground = osg::EmptyUIBackground::create();
	EmptyBorderPtr labelBorder = osg::EmptyBorder::create();
	beginEditCP(buttonLabel, Label::TextFieldMask| Component::ConstraintsFieldMask | Component::BackgroundFieldMask);
		buttonLabel->setText("Buttons");
		buttonLabel->setConstraints(constraint0001);
		buttonLabel->setBackground(labelBackground);
		buttonLabel->setBorder(labelBorder);
	endEditCP(buttonLabel, Label::TextFieldMask| Component::ConstraintsFieldMask | Component::BackgroundFieldMask);

	beginEditCP(toggleButtonLabel, Label::TextFieldMask| Component::ConstraintsFieldMask | Component::BackgroundFieldMask);
		toggleButtonLabel->setText("ToggleButtons");
		toggleButtonLabel->setConstraints(constraint0002);
		toggleButtonLabel->setBackground(labelBackground);
		toggleButtonLabel->setBorder(labelBorder);
	endEditCP(toggleButtonLabel, Label::TextFieldMask| Component::ConstraintsFieldMask | Component::BackgroundFieldMask);

	beginEditCP(radioButtonLabel, Label::TextFieldMask| Component::ConstraintsFieldMask | Component::BackgroundFieldMask);
		radioButtonLabel->setText("RadioButtons");
		radioButtonLabel->setConstraints(constraint0003);
		radioButtonLabel->setBackground(labelBackground);
		radioButtonLabel->setBorder(labelBorder);
	endEditCP(radioButtonLabel, Label::TextFieldMask| Component::ConstraintsFieldMask | Component::BackgroundFieldMask);
	
	beginEditCP(checkboxButtonLabel, Label::TextFieldMask| Component::ConstraintsFieldMask | Component::BackgroundFieldMask);
		checkboxButtonLabel->setText("CheckboxButtons");
		checkboxButtonLabel->setConstraints(constraint0004);
		checkboxButtonLabel->setBackground(labelBackground);
		checkboxButtonLabel->setBorder(labelBorder);
	endEditCP(checkboxButtonLabel, Label::TextFieldMask| Component::ConstraintsFieldMask | Component::BackgroundFieldMask);
	
	beginEditCP(textFieldLabel, Label::TextFieldMask| Component::ConstraintsFieldMask | Component::BackgroundFieldMask);
		textFieldLabel->setText("TextFields");
		textFieldLabel->setConstraints(constraint0005);
		textFieldLabel->setBackground(labelBackground);
		textFieldLabel->setBorder(labelBorder);
	endEditCP(textFieldLabel, Label::TextFieldMask| Component::ConstraintsFieldMask | Component::BackgroundFieldMask);

	beginEditCP(textAreaLabel, Label::TextFieldMask| Component::ConstraintsFieldMask | Component::BackgroundFieldMask);
		textAreaLabel->setText("TextAreas");
		textAreaLabel->setConstraints(constraint0006);
		textAreaLabel->setBackground(labelBackground);
		textAreaLabel->setBorder(labelBorder);
	endEditCP(textAreaLabel, Label::TextFieldMask| Component::ConstraintsFieldMask | Component::BackgroundFieldMask);

	beginEditCP(passwordFieldLabel, Label::TextFieldMask| Component::ConstraintsFieldMask | Component::BackgroundFieldMask);
		passwordFieldLabel->setText("PasswordFields");
		passwordFieldLabel->setConstraints(constraint0007);
		passwordFieldLabel->setBackground(labelBackground);
		passwordFieldLabel->setBorder(labelBorder);
	endEditCP(passwordFieldLabel, Label::TextFieldMask| Component::ConstraintsFieldMask | Component::BackgroundFieldMask);

	beginEditCP(spinnerLabel, Label::TextFieldMask| Component::ConstraintsFieldMask | Component::BackgroundFieldMask);
		spinnerLabel->setText("Spinners");
		spinnerLabel->setConstraints(constraint0008);
		spinnerLabel->setBackground(labelBackground);
		spinnerLabel->setBorder(labelBorder);
	endEditCP(spinnerLabel, Label::TextFieldMask| Component::ConstraintsFieldMask | Component::BackgroundFieldMask);

	beginEditCP(enabledLabel, Label::TextFieldMask| Component::ConstraintsFieldMask | Component::BackgroundFieldMask);
		enabledLabel->setText("Enabled");
		enabledLabel->setConstraints(constraint0100);
		enabledLabel->setBackground(labelBackground);
		enabledLabel->setBorder(labelBorder);
	endEditCP(enabledLabel, Label::TextFieldMask| Component::ConstraintsFieldMask | Component::BackgroundFieldMask);

	beginEditCP(disabledLabel, Label::TextFieldMask| Component::ConstraintsFieldMask | Component::BackgroundFieldMask);
		disabledLabel->setText("Disabled");
		disabledLabel->setConstraints(constraint0300);
		disabledLabel->setBackground(labelBackground);
		disabledLabel->setBorder(labelBorder);
	endEditCP(disabledLabel, Label::TextFieldMask| Component::ConstraintsFieldMask | Component::BackgroundFieldMask);


	beginEditCP(statePanel, Container::ChildrenFieldMask | Container::LayoutFieldMask  | Component::PreferredSizeFieldMask);
		statePanel->getChildren().addValue(inactiveButton);
		statePanel->getChildren().addValue(activeButton);
		statePanel->getChildren().addValue(disabledInactiveButton);
		statePanel->getChildren().addValue(disabledActiveButton);
		statePanel->getChildren().addValue(nonSelectedToggleButton);
		statePanel->getChildren().addValue(selectedToggleButton);
		statePanel->getChildren().addValue(disabledSelectedToggleButton);
		statePanel->getChildren().addValue(disabledNonselectedToggleButton);
		statePanel->getChildren().addValue(deselectedCheckboxButton);
		statePanel->getChildren().addValue(selectedCheckboxButton);
		statePanel->getChildren().addValue(disabledDeselectedCheckboxButton);
		statePanel->getChildren().addValue(disabledSelectedCheckboxButton);
		statePanel->getChildren().addValue(deselectedRadioButton);
		statePanel->getChildren().addValue(selectedRadioButton);
		statePanel->getChildren().addValue(disabledDeselectedRadioButton);
		statePanel->getChildren().addValue(disabledSelectedRadioButton);
		statePanel->getChildren().addValue(editableTextField);
		statePanel->getChildren().addValue(noneditableTextField);
		statePanel->getChildren().addValue(disabledEditableTextField);
		statePanel->getChildren().addValue(disabledNoneditableTextField);
		statePanel->getChildren().addValue(editableTextArea);
		statePanel->getChildren().addValue(noneditableTextArea);
		statePanel->getChildren().addValue(disabledEditableTextArea);
		statePanel->getChildren().addValue(disabledNoneditableTextArea);
		statePanel->getChildren().addValue(editablePasswordField);
		statePanel->getChildren().addValue(nonEditablePasswordField);
		statePanel->getChildren().addValue(disabledInactivePasswordField);
		statePanel->getChildren().addValue(disabledActivePasswordField);
		statePanel->getChildren().addValue(buttonLabel);
		statePanel->getChildren().addValue(toggleButtonLabel);
		statePanel->getChildren().addValue(radioButtonLabel);
		statePanel->getChildren().addValue(checkboxButtonLabel);
		statePanel->getChildren().addValue(textFieldLabel);
		statePanel->getChildren().addValue(textAreaLabel);
		statePanel->getChildren().addValue(passwordFieldLabel);
		statePanel->getChildren().addValue(spinnerLabel);
		statePanel->getChildren().addValue(enabledLabel);
		statePanel->getChildren().addValue(disabledLabel);
		statePanel->setLayout(statePanelLayout);
		statePanel->setPreferredSize( Vec2s(500,800) );
	beginEditCP(statePanel, Container::ChildrenFieldMask | Container::LayoutFieldMask  | Component::PreferredSizeFieldMask);

	return statePanel;

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