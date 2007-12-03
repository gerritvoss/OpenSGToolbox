
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
#include <OpenSG/UserInterface/OSGTextField.h>
#include <OpenSG/UserInterface/OSGTextArea.h>
#include <OpenSG/UserInterface/OSGTextField.h>
#include <OpenSG/UserInterface/OSGSpinner.h>
#include <OpenSG/UserInterface/OSGNumberSpinnerModel.h>
#include <sstream>


OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
bool ExitApp = false;

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


ComponentPtr createStatePanel(void);


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

	beginEditCP(label1, Label::TextFieldMask);
		label1->setText("State");
	endEditCP(label1, Label::TextFieldMask);
	beginEditCP(label2, Label::TextFieldMask);
		label2->setText("Tab2");
	endEditCP(label2, Label::TextFieldMask);
	beginEditCP(label3, Label::TextFieldMask);
		label3->setText("Tab3");
	endEditCP(label3, Label::TextFieldMask);
	beginEditCP(label4, Label::TextFieldMask);
		label4->setText("Tab4");
	endEditCP(label4, Label::TextFieldMask);
	beginEditCP(label5, Label::TextFieldMask);
		label5->setText("Tab5");
	endEditCP(label5, Label::TextFieldMask);
	beginEditCP(label6, Label::TextFieldMask);
		label6->setText("Tab6");
	endEditCP(label6, Label::TextFieldMask);
	
	beginEditCP(buttonA, Button::TextFieldMask);
		buttonA->setText("Add another Tab");
	endEditCP(buttonA, Button::TextFieldMask);


	beginEditCP(buttonB, Button::TextFieldMask);
		buttonB->setText("Add a Tab in Tab1!");
	endEditCP(buttonB, Button::TextFieldMask);

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
			distorted.  Also, removeTab is most useful
			when combined with ActionListeners to allow
			for interactability. 

	******************************************************/
	
	TabPanelPtr tabPanel = osg::TabPanel::create();
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
		tabPanel->setTabPlacement(PLACEMENT_NORTH);
	endEditCP(tabPanel, Component::PreferredSizeFieldMask | TabPanel::TabsFieldMask | TabPanel::TabContentsFieldMask | TabPanel::ActiveTabFieldMask | TabPanel::TabAlignmentFieldMask | TabPanel::TabPlacementFieldMask);


	// Create The Main Frame
	FramePtr MainFrame = osg::Frame::create();
	// CardLayout causes the TabPanel to occupy the entire
	// MainFrame view (useful with TabPanel)
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

	beginEditCP(foreground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
	    foreground->setDrawingSurface(drawingSurface);
		foreground->setFramePositionOffset(Vec2s(0,0));
		foreground->setFrameBounds(Vec2f(0.65,0.65));
	   //Set the Event Producer for the DrawingSurface
	   //This is needed in order to get Mouse/Keyboard/etc Input to the UI DrawingSurface
    endEditCP  (foreground, UIForeground::DrawingSurfaceFieldMask | UIForeground::FramePositionOffsetFieldMask | UIForeground::FrameBoundsFieldMask);
 
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


ComponentPtr createStatePanel(void)
{
	/******************************************************

			Create a Panel and its Layout

	******************************************************/

	GridBagLayoutPtr statePanelLayout = osg::GridBagLayout::create();
	beginEditCP(statePanelLayout, GridBagLayout::RowsFieldMask | GridBagLayout::ColumnsFieldMask);
		statePanelLayout->setRows(9);
		statePanelLayout->setColumns(5);
	endEditCP(statePanelLayout, GridBagLayout::RowsFieldMask | GridBagLayout::ColumnsFieldMask);
	PanelPtr statePanel = osg::Panel::create();


	/******************************************************

			Create Components to add to Panel

	******************************************************/	
	/******************************************************
						Buttons
	******************************************************/
	ButtonPtr inactiveButton = osg::Button::create();
	ButtonPtr activeButton = osg::Button::create();
	ButtonPtr disabledInactiveButton = osg::Button::create();
	ButtonPtr disabledActiveButton = osg::Button::create();

	beginEditCP(inactiveButton, Button::ActiveFieldMask | Button::TextFieldMask);
		inactiveButton->setActive(FALSE);
		inactiveButton->setText("Inactive");
	endEditCP(inactiveButton, Button::ActiveFieldMask | Button::TextFieldMask);
	
	beginEditCP(activeButton, Button::TextFieldMask);
		activeButton->setText("Active");
	endEditCP(activeButton, Button::TextFieldMask);

	beginEditCP(disabledInactiveButton, Button::ActiveFieldMask | Component::EnabledFieldMask | Button::TextFieldMask);
		disabledInactiveButton->setActive(FALSE);
		disabledInactiveButton->setEnabled(FALSE);
		disabledInactiveButton->setText("Disabled/Inactive");
	endEditCP(disabledInactiveButton, Button::ActiveFieldMask | Component::EnabledFieldMask | Button::TextFieldMask);
	
	beginEditCP(disabledActiveButton, Component::EnabledFieldMask | Button::TextFieldMask);
		disabledActiveButton->setEnabled(FALSE);
		disabledActiveButton->setText("Disabled");
	endEditCP(disabledActiveButton, Component::EnabledFieldMask | Button::TextFieldMask);
	
	/******************************************************
						ToggleButtons
	******************************************************/
	ToggleButtonPtr nonSelectedToggleButton = osg::ToggleButton::create();
	ToggleButtonPtr selectedToggleButton = osg::ToggleButton::create();
	ToggleButtonPtr disabledSelectedToggleButton = osg::ToggleButton::create();
	ToggleButtonPtr disabledNonselectedToggleButton = osg::ToggleButton::create();
	
	beginEditCP(nonSelectedToggleButton,Button::TextFieldMask);
		nonSelectedToggleButton->setText("NonSelected");
	endEditCP(nonSelectedToggleButton, Button::TextFieldMask);

	beginEditCP(selectedToggleButton, ToggleButton::SelectedFieldMask | Button::TextFieldMask);
		selectedToggleButton->setSelected(TRUE);
		selectedToggleButton->setText("Selected");
	endEditCP(selectedToggleButton, ToggleButton::SelectedFieldMask | Button::TextFieldMask);
	
	beginEditCP(disabledSelectedToggleButton, ToggleButton::SelectedFieldMask | Component::EnabledFieldMask | Button::TextFieldMask);
		disabledSelectedToggleButton->setSelected(TRUE);
		disabledSelectedToggleButton->setEnabled(FALSE);
		disabledSelectedToggleButton->setText("Disabled/Selected");
	endEditCP(disabledSelectedToggleButton, ToggleButton::SelectedFieldMask | Component::EnabledFieldMask | Button::TextFieldMask);
	
	beginEditCP(disabledNonselectedToggleButton, ToggleButton::SelectedFieldMask | Component::EnabledFieldMask | Button::TextFieldMask);
		disabledNonselectedToggleButton->setSelected(FALSE);
		disabledNonselectedToggleButton->setEnabled(FALSE);
		disabledNonselectedToggleButton->setText("Disabled");
	endEditCP(disabledNonselectedToggleButton, ToggleButton::SelectedFieldMask | Component::EnabledFieldMask | Button::TextFieldMask);

	/******************************************************
						RadioButtons
	******************************************************/
	RadioButtonPtr deselectedRadioButton = osg::RadioButton::create();
	RadioButtonPtr selectedRadioButton = osg::RadioButton::create();
	RadioButtonPtr disabledDeselectedRadioButton = osg::RadioButton::create();
	RadioButtonPtr disabledSelectedRadioButton = osg::RadioButton::create();
	RadioButtonGroup buttonGroup;
	buttonGroup.addButton(deselectedRadioButton);
	buttonGroup.addButton(selectedRadioButton);
	buttonGroup.addButton(disabledDeselectedRadioButton);
	buttonGroup.addButton(disabledSelectedRadioButton);

	beginEditCP(deselectedRadioButton, Button::TextFieldMask);
		deselectedRadioButton->setText("Deselected");
	endEditCP(deselectedRadioButton, Button::TextFieldMask);

	beginEditCP(selectedRadioButton, RadioButton::SelectedFieldMask | Button::TextFieldMask);
		selectedRadioButton->setSelected(TRUE);
		selectedRadioButton->setText("Selected");
	endEditCP(selectedRadioButton, RadioButton::SelectedFieldMask | Button::TextFieldMask);

	beginEditCP(disabledDeselectedRadioButton, Component::EnabledFieldMask | RadioButton::SelectedFieldMask | Button::TextFieldMask);
		disabledDeselectedRadioButton->setEnabled(FALSE);
		disabledDeselectedRadioButton->setSelected(FALSE);
		disabledDeselectedRadioButton->setText("Disabled");
	endEditCP(disabledDeselectedRadioButton, Component::EnabledFieldMask | RadioButton::SelectedFieldMask | Button::TextFieldMask);
	
	beginEditCP(disabledSelectedRadioButton, Component::EnabledFieldMask | RadioButton::SelectedFieldMask | Button::TextFieldMask);
		disabledSelectedRadioButton->setEnabled(FALSE);
		disabledSelectedRadioButton->setSelected(TRUE);
		disabledSelectedRadioButton->setText("Disabled/Selected");
	endEditCP(disabledSelectedRadioButton, Component::EnabledFieldMask | RadioButton::SelectedFieldMask | Button::TextFieldMask);
	
	
	/******************************************************
						CheckboxButtons
	******************************************************/
	CheckboxButtonPtr deselectedCheckboxButton = osg::CheckboxButton::create();
	CheckboxButtonPtr selectedCheckboxButton = osg::CheckboxButton::create();
	CheckboxButtonPtr disabledDeselectedCheckboxButton = osg::CheckboxButton::create();
	CheckboxButtonPtr disabledSelectedCheckboxButton = osg::CheckboxButton::create();

	beginEditCP(deselectedCheckboxButton, Button::TextFieldMask);
		deselectedCheckboxButton->setText("Deselected");
	endEditCP(deselectedCheckboxButton, Button::TextFieldMask);

	beginEditCP(selectedCheckboxButton, CheckboxButton::SelectedFieldMask | Button::TextFieldMask);
		selectedCheckboxButton->setSelected(TRUE);
		selectedCheckboxButton->setText("Selected");
	endEditCP(selectedCheckboxButton, CheckboxButton::SelectedFieldMask | Button::TextFieldMask);

	beginEditCP(disabledDeselectedCheckboxButton, CheckboxButton::SelectedFieldMask | Component::EnabledFieldMask | Button::TextFieldMask);
		disabledDeselectedCheckboxButton->setSelected(FALSE);
		disabledDeselectedCheckboxButton->setEnabled(FALSE);
		disabledDeselectedCheckboxButton->setText("Disabled");
	endEditCP(disabledDeselectedCheckboxButton, CheckboxButton::SelectedFieldMask | Component::EnabledFieldMask | Button::TextFieldMask);

	beginEditCP(disabledSelectedCheckboxButton, CheckboxButton::SelectedFieldMask | Component::EnabledFieldMask | Button::TextFieldMask);
		disabledSelectedCheckboxButton->setSelected(TRUE);
		disabledSelectedCheckboxButton->setEnabled(FALSE);
		disabledSelectedCheckboxButton->setText("Disabled/Selected");
	endEditCP(disabledSelectedCheckboxButton, CheckboxButton::SelectedFieldMask | Component::EnabledFieldMask | Button::TextFieldMask);
	/******************************************************
						TextFields
	******************************************************/
	TextFieldPtr editableTextField = osg::TextField::create();
	TextFieldPtr noneditableTextField = osg::TextField::create();
	TextFieldPtr disabledEditableTextField = osg::TextField::create();
	TextFieldPtr disabledNoneditableTextField = osg::TextField::create();

	beginEditCP(editableTextField, TextField::TextFieldMask);
		editableTextField->setText("Editable");
	endEditCP(editableTextField, TextField::TextFieldMask);

	beginEditCP(noneditableTextField, TextField::EditableFieldMask | TextField::TextFieldMask);
		noneditableTextField->setEditable(FALSE);
		noneditableTextField->setText("Noneditable");
	endEditCP(noneditableTextField, TextField::EditableFieldMask | TextField::TextFieldMask);
	
	beginEditCP(disabledEditableTextField, Component::EnabledFieldMask | TextField::TextFieldMask);
		disabledNoneditableTextField->setEnabled(FALSE);
		disabledNoneditableTextField->setText("Disabled");
	endEditCP(disabledEditableTextField, Component::EnabledFieldMask | TextField::TextFieldMask);
	
	beginEditCP(disabledNoneditableTextField, TextField::EditableFieldMask | Component::EnabledFieldMask | TextField::TextFieldMask);
		disabledNoneditableTextField->setEditable(FALSE);
		disabledNoneditableTextField->setEnabled(FALSE);
		disabledNoneditableTextField->setText("Disabled/Noneditable");
	endEditCP(disabledNoneditableTextField, TextField::EditableFieldMask | Component::EnabledFieldMask | TextField::TextFieldMask);
	/******************************************************
						TextAreas
	******************************************************/	
	TextAreaPtr editableTextArea = osg::TextArea::create();
	TextAreaPtr noneditableTextArea = osg::TextArea::create();
	TextAreaPtr disabledEditableTextArea = osg::TextArea::create();
	TextAreaPtr disabledNoneditableTextArea = osg::TextArea::create();

	beginEditCP(editableTextArea, TextArea::TextFieldMask);
		editableTextArea->setText("Uneditable");
	endEditCP(editableTextArea, TextArea::TextFieldMask);

	beginEditCP(noneditableTextArea, TextArea::EditableFieldMask | TextArea::TextFieldMask);
		noneditableTextArea->setEditable(FALSE);
		noneditableTextArea->setText("Uneditable");
	endEditCP(noneditableTextArea, TextArea::EditableFieldMask | TextArea::TextFieldMask);
	
	beginEditCP(disabledEditableTextArea, Component::EnabledFieldMask | TextArea::TextFieldMask);
		disabledEditableTextArea->setEnabled(FALSE);
		disabledEditableTextArea->setText("Disabled");
	endEditCP(disabledEditableTextArea, Component::EnabledFieldMask | TextArea::TextFieldMask);
	
	beginEditCP(disabledNoneditableTextArea, TextArea::EditableFieldMask | Component::EnabledFieldMask | TextArea::TextFieldMask);
		disabledNoneditableTextArea->setEditable(FALSE);
		disabledNoneditableTextArea->setEnabled(FALSE);
		disabledNoneditableTextArea->setText("Disabled");
	endEditCP(disabledNoneditableTextArea, TextArea::EditableFieldMask | Component::EnabledFieldMask | TextArea::TextFieldMask);

	/******************************************************
						PasswordFields
	******************************************************/	
	PasswordFieldPtr editablePasswordField = osg::PasswordField::create();
	PasswordFieldPtr nonEditablePasswordField = osg::PasswordField::create();
	PasswordFieldPtr disabledInactivePasswordField = osg::PasswordField::create();
	PasswordFieldPtr disabledActivePasswordField = osg::PasswordField::create(); 
	
	beginEditCP(editableTextArea, PasswordField::TextFieldMask);
		editableTextArea->setText("editable");
	endEditCP(editableTextArea, PasswordField::TextFieldMask);

	beginEditCP(nonEditablePasswordField, TextArea::EditableFieldMask | PasswordField::TextFieldMask);
		nonEditablePasswordField->setEditable(FALSE);
		editableTextArea->setText("editable");
	endEditCP(nonEditablePasswordField, TextArea::EditableFieldMask | PasswordField::TextFieldMask);
	
	beginEditCP(disabledEditableTextArea, Component::EnabledFieldMask | PasswordField::TextFieldMask);
		disabledEditableTextArea->setEnabled(FALSE);
		editableTextArea->setText("editable");
	endEditCP(disabledEditableTextArea, Component::EnabledFieldMask | PasswordField::TextFieldMask);
	
	beginEditCP(disabledNoneditableTextArea, TextArea::EditableFieldMask | Component::EnabledFieldMask | PasswordField::TextFieldMask);
		disabledNoneditableTextArea->setEditable(FALSE);
		disabledNoneditableTextArea->setEnabled(FALSE);
		editableTextArea->setText("editable");
	endEditCP(disabledNoneditableTextArea, TextArea::EditableFieldMask | Component::EnabledFieldMask | PasswordField::TextFieldMask);

	/******************************************************
						Spinners
	******************************************************/
	//SpinnerPtr inactiveSpinner = osg::Spinner::create();
	//SpinnerPtr activeSpinner = osg::Spinner::create();
	//SpinnerPtr disabledInactiveSpinner = osg::Spinner::create();
	//SpinnerPtr disabledActiveSpinner = osg::Spinner::create();
	//Int32SpinnerModelPtr TheModel(new Int32SpinnerModel());

		
	beginEditCP(statePanel, Container::ChildrenFieldMask | Container::LayoutFieldMask);
//		statePanel->getChildren().addValue( );
		statePanel->setLayout(statePanelLayout);
	beginEditCP(statePanel, Container::ChildrenFieldMask | Container::LayoutFieldMask);

	return statePanel;

	}