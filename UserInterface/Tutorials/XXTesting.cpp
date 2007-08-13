// OpenSG Tutorial Example: Creating a Button Component
//
// This tutorial explains how to edit the basic features of
// a Button created in the OSG User Interface library.
// 
// Includes: Button PreferredSize, MaximumSize, MinimumSize, Font,
// Text,and adding a Button to a Scene.  Also note that clicking
// the Button causes it to appear pressed


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
#include <OpenSG/OSGTransform.h>

// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

//Input
#include <OpenSG/Input/OSGWindowUtils.h>
#include <OpenSG/Input/OSGMouseListener.h>
#include <OpenSG/Input/OSGMouseMotionListener.h>
#include <OpenSG/Input/OSGWindowAdapter.h>

//UserInterface Headers
#include <OpenSG/UserInterface/OSGUIRectangle.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGToggleButton.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
#include <OpenSG/UserInterface/OSGFont.h>

// Include relevant header files
#include <OpenSG/UserInterface/OSGAbsoluteLayout.h>
#include <OpenSG/UserInterface/OSGAbsoluteLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGBoxLayout.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGGridLayout.h>
#include <OpenSG/UserInterface/OSGContainer.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGFrame.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGEmptyBorder.h>
#include <OpenSG/UserInterface/OSGEtchedBorder.h>
#include <OpenSG/UserInterface/OSGUIDefines.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
#include <OpenSG/UserInterface/OSGGradientUIBackground.h>
#include <OpenSG/UserInterface/OSGCompoundUIBackground.h>
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGCheckboxButton.h>
#include <OpenSG/UserInterface/OSGRadioButton.h>
#include <OpenSG/UserInterface/OSGRadioButtonGroup.h>
#include <OpenSG/UserInterface/OSGTextArea.h>
#include <OpenSG/UserInterface/OSGTextField.h>




#include <OpenSG/UserInterface/OSGWindowsLookAndFeel.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
bool ExitApp = false;

WindowEventProducerPtr TheWindowEventProducer;

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

// Create functions create Component Panels to make 
// code easier to read
ComponentPtr createleftPanelButtonPanel(void);
ComponentPtr createleftPanelRadioTextPanel(void);
ComponentPtr createrightPanelButtonPanel(void);
ComponentPtr createrightPanelCheckPanel(void);
// This function makes a complex Background outside of the main code
// to make code easier to read
UIBackgroundPtr createComplexBackground(void);
// These functions create materials to use with objects in scene
ChunkMaterialPtr createRedMaterial(void);
ChunkMaterialPtr createBlueMaterial(void);
ChunkMaterialPtr createGreenMaterial(void);
NodePtr scene, torus, cone, sphere, box;
void create3DObjects(void);



// Declare some variables up front 
RadioButtonGroup buttonGroup;
TextAreaPtr leftPanelTextArea;

class MakeTorus : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
		{		 
			beginEditCP(scene, Node::ChildrenFieldMask);
				scene->addChild(torus);
			endEditCP  (scene, Node::ChildrenFieldMask);
		}

   virtual void buttonDeselected(const ButtonSelectedEvent& e)
		{		 
			beginEditCP(scene, Node::ChildrenFieldMask);
				scene->subChild(torus);
			endEditCP  (scene, Node::ChildrenFieldMask);
		}
};
class MakeSphere : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
		{		 
			beginEditCP(scene, Node::ChildrenFieldMask);
				scene->addChild(sphere);
			endEditCP  (scene, Node::ChildrenFieldMask);
		}

   virtual void buttonDeselected(const ButtonSelectedEvent& e)
   {
			beginEditCP(scene, Node::ChildrenFieldMask);
				scene->subChild(sphere);
			endEditCP  (scene, Node::ChildrenFieldMask);	
   }
}; 
class MakeBox : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
		{		 
			beginEditCP(scene, Node::ChildrenFieldMask);
				scene->addChild(box);
			endEditCP  (scene, Node::ChildrenFieldMask);
		}

   virtual void buttonDeselected(const ButtonSelectedEvent& e)
   {
			beginEditCP(scene, Node::ChildrenFieldMask);
				scene->subChild(box);
			endEditCP  (scene, Node::ChildrenFieldMask);   
   }
};
class MakeCone : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
		{		 
			beginEditCP(scene, Node::ChildrenFieldMask);
				scene->addChild(cone);
			endEditCP  (scene, Node::ChildrenFieldMask);
		}

   virtual void buttonDeselected(const ButtonSelectedEvent& e)
   {
			beginEditCP(scene, Node::ChildrenFieldMask);
				scene->subChild(cone);
			endEditCP  (scene, Node::ChildrenFieldMask);   
   }
};


// These classes create Listeners to change Font color
// in the TextArea
class BlackFont : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
	{
		beginEditCP(leftPanelTextArea, TextArea::TextColorFieldMask);
			leftPanelTextArea->setTextColor( Color4f( 0.0, 0.0 , 0.0, 1.0) );
		endEditCP(leftPanelTextArea, TextArea::TextColorFieldMask);
   }

   virtual void buttonDeselected(const ButtonSelectedEvent& e)
   {
	
   }
};
class RedFont : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
	{

		beginEditCP(leftPanelTextArea, TextArea::TextColorFieldMask);
			leftPanelTextArea->setTextColor( Color4f( 1.0, 0.0 , 0.0, 1.0) );
		endEditCP(leftPanelTextArea, TextArea::TextColorFieldMask);
	
	}

   virtual void buttonDeselected(const ButtonSelectedEvent& e)
   {

   }
};
class BlueFont : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
	{

		beginEditCP(leftPanelTextArea, TextArea::TextColorFieldMask);
			leftPanelTextArea->setTextColor( Color4f( 0.0, 0.0 , 1.0, 1.0) );
		endEditCP(leftPanelTextArea, TextArea::TextColorFieldMask);
	
	}

   virtual void buttonDeselected(const ButtonSelectedEvent& e)
   {

   }
};
class GreenFont : public ButtonSelectedListener
{
public:

   virtual void buttonSelected(const ButtonSelectedEvent& e)
	{

		beginEditCP(leftPanelTextArea, TextArea::TextColorFieldMask);
			leftPanelTextArea->setTextColor( Color4f( 0.0, 1.0 , 0.0, 1.0) );
		endEditCP(leftPanelTextArea, TextArea::TextColorFieldMask);
	
	}

   virtual void buttonDeselected(const ButtonSelectedEvent& e)
   {

   }
};

// Declare listeners to be global
BlackFont rbutton1Listener;
RedFont rbutton2Listener;
GreenFont rbutton3Listener;
BlueFont rbutton4Listener;
MakeTorus rightPanelCheck1Listener;
MakeBox rightPanelCheck2Listener;
MakeSphere rightPanelCheck3Listener;
MakeCone rightPanelCheck4Listener;
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
		if(TheWindowEventProducer->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
		{
			mgr->mouseButtonPress(e.getButton(), e.getLocation().x(), e.getLocation().y());
		}
    }
    virtual void mouseReleased(const MouseEvent& e)
    {
		if(TheWindowEventProducer->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
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
		if(TheWindowEventProducer->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
		{
            mgr->mouseMove(e.getLocation().x(), e.getLocation().y());
		}
    }

    virtual void mouseDragged(const MouseEvent& e)
    {
		if(TheWindowEventProducer->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CAPS_LOCK)
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
    WindowEventProducerPtr TheWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TheWindowEventProducer->initWindow();
    
    TheWindowEventProducer->setDisplayCallback(display);
    TheWindowEventProducer->setReshapeCallback(reshape);

    TutorialMouseListener mouseListener;
    TutorialMouseMotionListener mouseMotionListener;
    TheWindowEventProducer->addMouseListener(&mouseListener);
    TheWindowEventProducer->addMouseMotionListener(&mouseMotionListener);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TheWindowEventProducer->addWindowListener(&TheTutorialWindowListener);




    // Make Main Scene Node
	create3DObjects();
    scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
		{
			scene->setCore(osg::Group::create());
		}
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

	// Create the Graphics
	GraphicsPtr graphics = osg::Graphics2D::create();


	// Initialize the LookAndFeelManager to enable default settings
	LookAndFeelManager::the()->setLookAndFeel(WindowsLookAndFeel::create() );
	LookAndFeelManager::the()->getLookAndFeel()->init();

		
	/******************************************************
			
			Create some Backgrounds

	******************************************************/
	ColorUIBackgroundPtr greyBackground = osg::ColorUIBackground::create();
	ColorUIBackgroundPtr button1Color = osg::ColorUIBackground::create();
	GradientUIBackgroundPtr button1Gradient = osg::GradientUIBackground::create();
	CompoundUIBackgroundPtr button1Compound = osg::CompoundUIBackground::create();

	beginEditCP(greyBackground, ColorUIBackground::ColorFieldMask);
		greyBackground->setColor( Color4f(.93,.93,.93,1.0) );
	endEditCP(greyBackground, ColorUIBackground::ColorFieldMask);


	/******************************************************
			
			Create some Borders

	******************************************************/
	LineBorderPtr panelBorder0 = osg::LineBorder::create();
	EmptyBorderPtr panel1Border = osg::EmptyBorder::create();
	EmptyBorderPtr panel2Border = osg::EmptyBorder::create();
	EmptyBorderPtr emptyBorder = osg::EmptyBorder::create();
	
	beginEditCP(panelBorder0, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);
		panelBorder0->setColor( Color4f(0.0,0.0,0.0,1.0) );
		panelBorder0->setWidth(1);
	endEditCP(panelBorder0, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);

	beginEditCP(panel1Border, EmptyBorder::TopWidthFieldMask | EmptyBorder::BottomWidthFieldMask | EmptyBorder::LeftWidthFieldMask | EmptyBorder::RightWidthFieldMask);
		panel1Border->setTopWidth(0);
		panel1Border->setBottomWidth(6);
		panel1Border->setLeftWidth(0);
		panel1Border->setRightWidth(0);
	beginEditCP(panel1Border, EmptyBorder::TopWidthFieldMask | EmptyBorder::BottomWidthFieldMask | EmptyBorder::LeftWidthFieldMask | EmptyBorder::RightWidthFieldMask);
	beginEditCP(panel2Border, EmptyBorder::TopWidthFieldMask | EmptyBorder::BottomWidthFieldMask | EmptyBorder::LeftWidthFieldMask | EmptyBorder::RightWidthFieldMask);
		panel2Border->setTopWidth(0);
		panel2Border->setBottomWidth(0);
		panel2Border->setLeftWidth(0);
		panel2Border->setRightWidth(0);
	beginEditCP(panel2Border, EmptyBorder::TopWidthFieldMask | EmptyBorder::BottomWidthFieldMask | EmptyBorder::LeftWidthFieldMask | EmptyBorder::RightWidthFieldMask);
	

	/******************************************************

			Create some Labels and stuff to go 
			with them

	******************************************************/
	LabelPtr leftPanelLabel1 = osg::Label::create();
	UIFontPtr leftPanelLabel1Font = osg::UIFont::create();

	beginEditCP(leftPanelLabel1Font, UIFont::SizeFieldMask);
		leftPanelLabel1Font->setSize(50);
	endEditCP(leftPanelLabel1Font, UIFont::SizeFieldMask);

	beginEditCP(leftPanelLabel1, Component::BorderFieldMask | Component::BackgroundFieldMask | Label::FontFieldMask | Label::TextFieldMask | Component::PreferredSizeFieldMask);
		leftPanelLabel1->setBorder(emptyBorder);
		leftPanelLabel1->setBackground(greyBackground);
		leftPanelLabel1->setFont(leftPanelLabel1Font);
		leftPanelLabel1->setText("Sample Label");
		leftPanelLabel1->setPreferredSize( Vec2s(300, 100) );
	endEditCP(leftPanelLabel1, Component::BorderFieldMask | Component::BackgroundFieldMask | Label::FontFieldMask | Label::TextFieldMask | Component::PreferredSizeFieldMask);

	

	/******************************************************

			Create some Layouts

	******************************************************/
	BoxLayoutPtr MainFrameLayout = osg::BoxLayout::create();
	FlowLayoutPtr leftPanelLayout = osg::FlowLayout::create();
	BoxLayoutPtr rightPanelLayout = osg::BoxLayout::create();
	beginEditCP(MainFrameLayout, BoxLayout::AlignmentFieldMask);
		MainFrameLayout->setAlignment(HORIZONTAL_ALIGNMENT);
	endEditCP(MainFrameLayout, BoxLayout::AlignmentFieldMask);

	beginEditCP(leftPanelLayout, FlowLayout::AlignmentFieldMask);
		leftPanelLayout->setAlignment(HORIZONTAL_ALIGNMENT);
		leftPanelLayout->setMinorAxisAlignment(AXIS_MAX_ALIGNMENT);
	endEditCP(leftPanelLayout, FlowLayout::AlignmentFieldMask);

	beginEditCP(rightPanelLayout, BoxLayout::AlignmentFieldMask);
		rightPanelLayout->setAlignment(VERTICAL_ALIGNMENT);
	endEditCP(rightPanelLayout, BoxLayout::AlignmentFieldMask);
	

	/******************************************************

		Create MainFrame and Panels

	******************************************************/
	PanelPtr leftPanel = osg::Panel::create();
	PanelPtr rightPanel = osg::Panel::create();

	//Panel 1 stuff
	beginEditCP(leftPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundFieldMask | Panel::BorderFieldMask);
		leftPanel->setPreferredSize( Vec2s(400, 500) );
		leftPanel->getChildren().addValue(leftPanelLabel1);
		leftPanel->getChildren().addValue(createleftPanelButtonPanel());
		leftPanel->getChildren().addValue(createleftPanelRadioTextPanel());
		leftPanel->setLayout(leftPanelLayout);
		leftPanel->setBackground(greyBackground);
		leftPanel->setBorder(panel1Border);
	endEditCP(leftPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundFieldMask | Panel::BorderFieldMask);

	//Panel 2 stuff
	beginEditCP(rightPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundFieldMask | Panel::BorderFieldMask);
		rightPanel->setPreferredSize( Vec2s(200, 620) );
		rightPanel->getChildren().addValue(createrightPanelButtonPanel());
		rightPanel->getChildren().addValue(createrightPanelCheckPanel());
		rightPanel->setLayout(rightPanelLayout);
		rightPanel->setBackground(greyBackground);
		rightPanel->setBorder(panel2Border);
	endEditCP(rightPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundFieldMask | Panel::BorderFieldMask);
	
	

	FramePtr MainFrame = osg::Frame::create();
	beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);
	   MainFrame->setBorder(panelBorder0);
	   MainFrame->getChildren().addValue(leftPanel);
	   MainFrame->getChildren().addValue(rightPanel);
	   MainFrame->setLayout(MainFrameLayout);
	   MainFrame->setBackground(greyBackground); 
	endEditCP  (MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);

	//Create the Drawing Surface
	UIDrawingSurfacePtr drawingSurface = UIDrawingSurface::create();
    beginEditCP(drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask);
		drawingSurface->setGraphics(graphics);
		drawingSurface->setRootFrame(MainFrame);
	    drawingSurface->setEventProducer(TheWindowEventProducer);
    endEditCP  (drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask);
	
    //Make A 3D Rectangle to draw the UI on
    UIRectanglePtr UIRectCore = UIRectangle::create();
    beginEditCP(UIRectCore, UIRectangle::PointFieldMask | UIRectangle::WidthFieldMask | UIRectangle::HeightFieldMask | UIRectangle::DrawingSurfaceFieldMask);
		UIRectCore->setPoint(Pnt3f(-310.0,-310.0,370.0));
        UIRectCore->setWidth(620);
        UIRectCore->setHeight(620);
        UIRectCore->setDrawingSurface(drawingSurface);
	endEditCP(UIRectCore, UIRectangle::PointFieldMask | UIRectangle::WidthFieldMask | UIRectangle::HeightFieldMask | UIRectangle::DrawingSurfaceFieldMask);
	
    NodePtr UIRectNode = osg::Node::create();
    beginEditCP(UIRectNode, Node::CoreFieldMask);
        UIRectNode->setCore(UIRectCore);
    endEditCP  (UIRectNode, Node::CoreFieldMask);
    
    beginEditCP(scene, Node::ChildrenFieldMask);
        // add the UIRect as a child
        scene->addChild(UIRectNode);
    endEditCP  (scene, Node::ChildrenFieldMask);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(MainWindow );
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();

    TheWindowEventProducer->openWindow(Pnt2s(50,50),
                                        Vec2s(550,550),
                                        "OpenSG 21ExampleInterface Window");

    while(!ExitApp)
    {
        TheWindowEventProducer->update();
        TheWindowEventProducer->draw();
    }
    osgExit();

    return 0;
}

//
// callback functions
//

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


ComponentPtr createleftPanelButtonPanel(void)

{

	// Create Label for this Panel
	LabelPtr leftPanelButtonPanelLabel = osg::Label::create();

	beginEditCP(leftPanelButtonPanelLabel, Label::TextColorFieldMask | Component::BackgroundFieldMask | Component::PreferredSizeFieldMask | Label::TextFieldMask);
		leftPanelButtonPanelLabel->setTextColor( Color4f(1.0,1.0,1.0,1.0));
		leftPanelButtonPanelLabel->setBackground(createComplexBackground());
		leftPanelButtonPanelLabel->setPreferredSize( Vec2s(100, 50) );
		leftPanelButtonPanelLabel->setText("Various Options");
	endEditCP(leftPanelButtonPanelLabel, Label::TextColorFieldMask | Component::BackgroundFieldMask | Component::PreferredSizeFieldMask | 		Label::TextFieldMask);

	// Create and edit the Panel buttons
	ButtonPtr leftPanelButton1 = osg::Button::create();
	ButtonPtr leftPanelButton2 = osg::Button::create();
	ButtonPtr leftPanelButton3 = osg::Button::create();
	ButtonPtr leftPanelButton4 = osg::Button::create();
	ButtonPtr leftPanelButton5 = osg::Button::create();
	ButtonPtr leftPanelButton6 = osg::Button::create();

	beginEditCP(leftPanelButton1, Button::TextFieldMask, Component::PreferredSizeFieldMask);
		leftPanelButton1->setText("button1");
		leftPanelButton1->setPreferredSize( Vec2s(100,50) );
	endEditCP(leftPanelButton1, Button::TextFieldMask, Component::PreferredSizeFieldMask);
	
	beginEditCP(leftPanelButton2, Button::TextFieldMask, Component::PreferredSizeFieldMask);
		leftPanelButton2->setText("button2");
		leftPanelButton2->setPreferredSize( Vec2s(100,50) );
	endEditCP(leftPanelButton2, Button::TextFieldMask, Component::PreferredSizeFieldMask);

	beginEditCP(leftPanelButton3, Button::TextFieldMask, Component::PreferredSizeFieldMask);
		leftPanelButton3->setText("button3");
		leftPanelButton3->setPreferredSize( Vec2s(100,50) );
	endEditCP(leftPanelButton3, Button::TextFieldMask, Component::PreferredSizeFieldMask);

	beginEditCP(leftPanelButton4, Button::TextFieldMask, Component::PreferredSizeFieldMask);
		leftPanelButton4->setText("button4");
		leftPanelButton4->setPreferredSize( Vec2s(100,50) );
	endEditCP(leftPanelButton4, Button::TextFieldMask, Component::PreferredSizeFieldMask);

	beginEditCP(leftPanelButton5, Button::TextFieldMask, Component::PreferredSizeFieldMask);
		leftPanelButton5->setText("button5");
		leftPanelButton5->setPreferredSize( Vec2s(100,50) );
	endEditCP(leftPanelButton5, Button::TextFieldMask, Component::PreferredSizeFieldMask);
	
	beginEditCP(leftPanelButton6, Button::TextFieldMask, Component::PreferredSizeFieldMask);
		leftPanelButton6->setText("button6");
		leftPanelButton6->setPreferredSize( Vec2s(100,50) );
	endEditCP(leftPanelButton6, Button::TextFieldMask, Component::PreferredSizeFieldMask);
	

	// Create and edit Panel layout
	BoxLayoutPtr leftPanelButtonPanelLayout = osg::BoxLayout::create();
	beginEditCP(leftPanelButtonPanelLayout, BoxLayout::AlignmentFieldMask);
		leftPanelButtonPanelLayout->setAlignment(VERTICAL_ALIGNMENT);
	endEditCP(leftPanelButtonPanelLayout, BoxLayout::AlignmentFieldMask);

	// Create an edit Panel Background
	ColorUIBackgroundPtr leftPanelButtonPanelBackground = osg::ColorUIBackground::create();
	beginEditCP(leftPanelButtonPanelBackground, ColorUIBackground::ColorFieldMask);
		leftPanelButtonPanelBackground->setColor( Color4f(0.93,0.93,0.93,1.0) );
	endEditCP(leftPanelButtonPanelBackground, ColorUIBackground::ColorFieldMask);

	// Create Panel Border
	LineBorderPtr panelBorder = osg::LineBorder::create();
	beginEditCP(panelBorder, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);
		panelBorder->setColor( Color4f(0.0,0.0,0.0,1.0) );
		panelBorder->setWidth(1);
	endEditCP(panelBorder, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);

	// Create and edit Panel
	PanelPtr leftPanelButtonPanel = osg::Panel::create();
	beginEditCP(leftPanelButtonPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundFieldMask | Panel::BorderFieldMask);
		leftPanelButtonPanel->setPreferredSize( Vec2s(180, 500) );
		leftPanelButtonPanel->getChildren().addValue(leftPanelButtonPanelLabel);
		leftPanelButtonPanel->getChildren().addValue(leftPanelButton1);
		leftPanelButtonPanel->getChildren().addValue(leftPanelButton2);
		leftPanelButtonPanel->getChildren().addValue(leftPanelButton3);
		leftPanelButtonPanel->getChildren().addValue(leftPanelButton4);
		leftPanelButtonPanel->getChildren().addValue(leftPanelButton5);
		leftPanelButtonPanel->getChildren().addValue(leftPanelButton6);
		leftPanelButtonPanel->setLayout(leftPanelButtonPanelLayout);
		leftPanelButtonPanel->setBackground(leftPanelButtonPanelBackground);
		leftPanelButtonPanel->setBorder(panelBorder);
	endEditCP(leftPanelButtonPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundFieldMask | Panel::BorderFieldMask);

	return leftPanelButtonPanel;
}




ComponentPtr createleftPanelRadioTextPanel(void)
{

	// Create the RadioButton group
	RadioButtonPtr rbutton1 = osg::RadioButton::create();
	RadioButtonPtr rbutton2 = osg::RadioButton::create();
	RadioButtonPtr rbutton3 = osg::RadioButton::create();
	RadioButtonPtr rbutton4 = osg::RadioButton::create();

	beginEditCP(rbutton1, Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask | Component::PreferredSizeFieldMask | Button::TextFieldMask);
		rbutton1->setVerticalAlignment(VERTICAL_CENTER);
		rbutton1->setHorizontalAlignment(HORIZONTAL_LEFT);
		rbutton1->setPreferredSize(Vec2s(100, 40));
		rbutton1->setText("Black Text");
	endEditCP(rbutton1, Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask | Component::SizeFieldMask | Button::TextFieldMask);
		rbutton1->addButtonSelectedListener(&rbutton1Listener);

	beginEditCP(rbutton2,Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask | Component::SizeFieldMask | Button::TextFieldMask);
		rbutton2->setVerticalAlignment(VERTICAL_CENTER);
		rbutton2->setHorizontalAlignment(HORIZONTAL_LEFT);
		rbutton2->setPreferredSize(Vec2s(100, 40));
		rbutton2->setText("Red Text");
	endEditCP(rbutton2, Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask | Component::SizeFieldMask | Button::TextFieldMask);
		rbutton2->addButtonSelectedListener(&rbutton2Listener);

	beginEditCP(rbutton3, Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask | Component::SizeFieldMask | Button::TextFieldMask);
		rbutton3->setVerticalAlignment(VERTICAL_CENTER);
		rbutton3->setHorizontalAlignment(HORIZONTAL_LEFT);
		rbutton3->setPreferredSize(Vec2s(100, 40));
		rbutton3->setText("Green Text");
	endEditCP(rbutton3, Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask | Component::SizeFieldMask | Button::TextFieldMask);
		rbutton3->addButtonSelectedListener(&rbutton3Listener);

	beginEditCP(rbutton4, Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask | Component::SizeFieldMask | Button::TextFieldMask);
		rbutton4->setVerticalAlignment(VERTICAL_CENTER);
		rbutton4->setHorizontalAlignment(HORIZONTAL_LEFT);
		rbutton4->setPreferredSize(Vec2s(100, 40));
		rbutton4->setText("Blue Text");
	endEditCP(rbutton4, Button::VerticalAlignmentFieldMask | Button::HorizontalAlignmentFieldMask | Component::SizeFieldMask | Button::TextFieldMask);
		rbutton4->addButtonSelectedListener(&rbutton4Listener);

	buttonGroup.addButton(rbutton1);
	buttonGroup.addButton(rbutton2);
	buttonGroup.addButton(rbutton3);
	buttonGroup.addButton(rbutton4);


	// Create TextArea
	leftPanelTextArea = osg::TextArea::create();
	beginEditCP(leftPanelTextArea, Component::PreferredSizeFieldMask);
		leftPanelTextArea->setPreferredSize( Vec2s(125, 200) );
	endEditCP(leftPanelTextArea, Component::PreferredSizeFieldMask);

	// Create TextField
	TextFieldPtr leftPanelTextField = osg::TextField::create();
	beginEditCP(leftPanelTextField, Component::PreferredSizeFieldMask);
		leftPanelTextField->setPreferredSize( Vec2s(125, 22) );
	endEditCP(leftPanelTextField, Component::PreferredSizeFieldMask);

	
	// Create an edit Panel Background
	ColorUIBackgroundPtr leftPanelRadioTextPanelBackground = osg::ColorUIBackground::create();
	beginEditCP(leftPanelRadioTextPanelBackground, ColorUIBackground::ColorFieldMask);
		leftPanelRadioTextPanelBackground->setColor( Color4f(0.93,0.93,0.93,1.0) );
	endEditCP(leftPanelRadioTextPanelBackground, ColorUIBackground::ColorFieldMask);

	// Create and edit Panel layouts
	FlowLayoutPtr leftPanelRadioTextPanelLayout = osg::FlowLayout::create();
	FlowLayoutPtr leftPanelRadioTextPanelRadioPanelLayout = osg::FlowLayout::create();
	FlowLayoutPtr leftPanelRadioTextPanelTextPanelLayout = osg::FlowLayout::create();
	beginEditCP(leftPanelRadioTextPanelLayout, FlowLayout::MinorAxisAlignmentFieldMask);
		leftPanelRadioTextPanelLayout->setMinorAxisAlignment(AXIS_MIN_ALIGNMENT);
	beginEditCP(leftPanelRadioTextPanelLayout, FlowLayout::MinorAxisAlignmentFieldMask);

	// Create two Panels for this Panel
	PanelPtr leftPanelRadioTextPanelRadioPanel = osg::Panel::create();
	PanelPtr leftPanelRadioTextPanelTextPanel = osg::Panel::create();

	// Create some Borders
	EmptyBorderPtr leftPanelRadioTextPanelRadioPanelBorder = osg::EmptyBorder::create();

	beginEditCP(leftPanelRadioTextPanelRadioPanel, Component::BorderFieldMask | Component::PreferredSizeFieldMask | Component::BackgroundFieldMask | Container::LayoutFieldMask | Container::ChildrenFieldMask);
		leftPanelRadioTextPanelRadioPanel->setBorder(leftPanelRadioTextPanelRadioPanelBorder);
		leftPanelRadioTextPanelRadioPanel->setPreferredSize( Vec2s(125, 200) );
		leftPanelRadioTextPanelRadioPanel->setBackground(leftPanelRadioTextPanelBackground);
		leftPanelRadioTextPanelRadioPanel->setLayout(leftPanelRadioTextPanelRadioPanelLayout);
		leftPanelRadioTextPanelRadioPanel->getChildren().addValue(rbutton1);
		leftPanelRadioTextPanelRadioPanel->getChildren().addValue(rbutton2);
		leftPanelRadioTextPanelRadioPanel->getChildren().addValue(rbutton3);
		leftPanelRadioTextPanelRadioPanel->getChildren().addValue(rbutton4);
	endEditCP(leftPanelRadioTextPanelRadioPanel, Component::BorderFieldMask | Component::PreferredSizeFieldMask | Component::BackgroundFieldMask | Container::LayoutFieldMask | Container::ChildrenFieldMask);

	/*beginEditCP(leftPanelRadioTextPanelLayout, GridLayout::RowsFieldMask | GridLayout::ColumnsFieldMask);
		leftPanelRadioTextPanelLayout->setRows(2);
		leftPanelRadioTextPanelLayout->setColumns(1);
	endEditCP(leftPanelRadioTextPanelLayout, GridLayout::RowsFieldMask | GridLayout::ColumnsFieldMask);
	*/


	// Create Panel Border
	LineBorderPtr panelBorder1 = osg::LineBorder::create();
	beginEditCP(panelBorder1, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);
		panelBorder1->setColor( Color4f(0.0,0.0,0.0,1.0) );
		panelBorder1->setWidth(1);
	endEditCP(panelBorder1, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);

	// Create and edit Panel
	PanelPtr leftPanelRadioTextPanel = osg::Panel::create();
	beginEditCP(leftPanelRadioTextPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundFieldMask | Panel::BorderFieldMask);
		leftPanelRadioTextPanel->setPreferredSize( Vec2s(180, 500) );
		leftPanelRadioTextPanel->getChildren().addValue(leftPanelRadioTextPanelRadioPanel);
		leftPanelRadioTextPanel->getChildren().addValue(leftPanelTextField);
		leftPanelRadioTextPanel->getChildren().addValue(leftPanelTextArea);
		leftPanelRadioTextPanel->setLayout(leftPanelRadioTextPanelLayout);
		leftPanelRadioTextPanel->setBackground(leftPanelRadioTextPanelBackground);
		leftPanelRadioTextPanel->setBorder(panelBorder1);
	endEditCP(leftPanelRadioTextPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundFieldMask | Panel::BorderFieldMask);

	return leftPanelRadioTextPanel;
}
ComponentPtr createrightPanelButtonPanel(void)
{
	// Create and edit the Panel Buttons
	ToggleButtonPtr rightPanelButton1 = osg::ToggleButton::create();
	ToggleButtonPtr rightPanelButton2 = osg::ToggleButton::create();
	ToggleButtonPtr rightPanelButton3 = osg::ToggleButton::create();
	ToggleButtonPtr rightPanelButton4 = osg::ToggleButton::create();

	beginEditCP(rightPanelButton1, Button::TextFieldMask, Component::PreferredSizeFieldMask);
		rightPanelButton1->setText("r button1");
		rightPanelButton1->setPreferredSize( Vec2s(100,50) );
	endEditCP(rightPanelButton1, Button::TextFieldMask, Component::PreferredSizeFieldMask);
	
	beginEditCP(rightPanelButton2, Button::TextFieldMask, Component::PreferredSizeFieldMask);
		rightPanelButton2->setText("r button2");
		rightPanelButton2->setPreferredSize( Vec2s(100,50) );
	endEditCP(rightPanelButton2, Button::TextFieldMask, Component::PreferredSizeFieldMask);

	beginEditCP(rightPanelButton3, Button::TextFieldMask, Component::PreferredSizeFieldMask);
		rightPanelButton3->setText("r button3");
		rightPanelButton3->setPreferredSize( Vec2s(100,50) );
	endEditCP(rightPanelButton3, Button::TextFieldMask, Component::PreferredSizeFieldMask);

	beginEditCP(rightPanelButton4, Button::TextFieldMask, Component::PreferredSizeFieldMask);
		rightPanelButton4->setText("r button4");
		rightPanelButton4->setPreferredSize( Vec2s(100,50) );
	endEditCP(rightPanelButton4, Button::TextFieldMask, Component::PreferredSizeFieldMask);


	// Create an edit Panel Background
	ColorUIBackgroundPtr rightPanelButtonPanelBackground = osg::ColorUIBackground::create();
	beginEditCP(rightPanelButtonPanelBackground, ColorUIBackground::ColorFieldMask);
		rightPanelButtonPanelBackground->setColor( Color4f(0.93,0.93,0.93,1.0) );
	endEditCP(rightPanelButtonPanelBackground, ColorUIBackground::ColorFieldMask);

	// Create and edit Panel layout
	BoxLayoutPtr rightPanelButtonPanelLayout = osg::BoxLayout::create();
	beginEditCP(rightPanelButtonPanelLayout, BoxLayout::AlignmentFieldMask);
		rightPanelButtonPanelLayout->setAlignment(VERTICAL_ALIGNMENT);
	endEditCP(rightPanelButtonPanelLayout, BoxLayout::AlignmentFieldMask);

	// Create Panel Border
	LineBorderPtr panelBorder2 = osg::LineBorder::create();
	beginEditCP(panelBorder2, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);
		panelBorder2->setColor( Color4f(0.0,0.0,0.0,1.0) );
		panelBorder2->setWidth(1);
	endEditCP(panelBorder2, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);

	// Create and edit Panel
	PanelPtr rightPanelButtonPanel = osg::Panel::create();
	beginEditCP(rightPanelButtonPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundFieldMask | Panel::BorderFieldMask);
		rightPanelButtonPanel->setPreferredSize( Vec2s(200, 300) );
		rightPanelButtonPanel->getChildren().addValue(rightPanelButton1);
		rightPanelButtonPanel->getChildren().addValue(rightPanelButton2);
		rightPanelButtonPanel->getChildren().addValue(rightPanelButton3);
		rightPanelButtonPanel->getChildren().addValue(rightPanelButton4);
		rightPanelButtonPanel->setLayout(rightPanelButtonPanelLayout);
		rightPanelButtonPanel->setBackground(rightPanelButtonPanelBackground);
		rightPanelButtonPanel->setBorder(panelBorder2);
	endEditCP(rightPanelButtonPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundFieldMask | Panel::BorderFieldMask);

	return rightPanelButtonPanel;

}
ComponentPtr createrightPanelCheckPanel(void)
{
	// Create and edit the CheckBoxes
	CheckboxButtonPtr rightPanelCheck1 = osg::CheckboxButton::create();
	CheckboxButtonPtr rightPanelCheck2 = osg::CheckboxButton::create();
	CheckboxButtonPtr rightPanelCheck3 = osg::CheckboxButton::create();
	CheckboxButtonPtr rightPanelCheck4 = osg::CheckboxButton::create();

	beginEditCP(rightPanelCheck1, Button::TextFieldMask, Component::PreferredSizeFieldMask);
		rightPanelCheck1->setText("Show Torus");
		rightPanelCheck1->setPreferredSize( Vec2s(125,50) );
		rightPanelCheck1->setHorizontalAlignment(HORIZONTAL_LEFT);
	endEditCP(rightPanelCheck1, Button::TextFieldMask, Component::PreferredSizeFieldMask);
		// Add Listener
		rightPanelCheck1->addButtonSelectedListener(&rightPanelCheck1Listener);
	
	beginEditCP(rightPanelCheck2, Button::TextFieldMask, Component::PreferredSizeFieldMask);
		rightPanelCheck2->setText("Show Box");
		rightPanelCheck2->setPreferredSize( Vec2s(125,50) );
		rightPanelCheck2->setHorizontalAlignment(HORIZONTAL_LEFT);
	endEditCP(rightPanelCheck2, Button::TextFieldMask, Component::PreferredSizeFieldMask);
		// Add Listener
		rightPanelCheck2->addButtonSelectedListener(&rightPanelCheck2Listener);

	beginEditCP(rightPanelCheck3, Button::TextFieldMask, Component::PreferredSizeFieldMask);
		rightPanelCheck3->setText("Show Sphere");
		rightPanelCheck3->setPreferredSize( Vec2s(125,50) );
		rightPanelCheck3->setHorizontalAlignment(HORIZONTAL_LEFT);
	endEditCP(rightPanelCheck3, Button::TextFieldMask, Component::PreferredSizeFieldMask);
		// Add Listener
		rightPanelCheck3->addButtonSelectedListener(&rightPanelCheck3Listener);

	beginEditCP(rightPanelCheck4, Button::TextFieldMask, Component::PreferredSizeFieldMask);
		rightPanelCheck4->setText("Show Cone");
		rightPanelCheck4->setPreferredSize( Vec2s(125,50) );
		rightPanelCheck4->setHorizontalAlignment(HORIZONTAL_LEFT);
	endEditCP(rightPanelCheck4, Button::TextFieldMask, Component::PreferredSizeFieldMask);
		// Add Listener
		rightPanelCheck4->addButtonSelectedListener(&rightPanelCheck4Listener);

	// Create an edit Panel Background
	ColorUIBackgroundPtr rightPanelCheckPanelBackground = osg::ColorUIBackground::create();
	beginEditCP(rightPanelCheckPanelBackground, ColorUIBackground::ColorFieldMask);
		rightPanelCheckPanelBackground->setColor( Color4f(0.93,0.93,0.93,1.0) );
	endEditCP(rightPanelCheckPanelBackground, ColorUIBackground::ColorFieldMask);

	// Create and edit Panel layout
	BoxLayoutPtr rightPanelCheckPanelLayout = osg::BoxLayout::create();
	beginEditCP(rightPanelCheckPanelLayout, BoxLayout::AlignmentFieldMask);
		rightPanelCheckPanelLayout->setAlignment(VERTICAL_ALIGNMENT);
	endEditCP(rightPanelCheckPanelLayout, BoxLayout::AlignmentFieldMask);

	// Create Panel Border
	LineBorderPtr panelBorder3 = osg::LineBorder::create();
	beginEditCP(panelBorder3, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);
		panelBorder3->setColor( Color4f(0.0,0.0,0.0,1.0) );
		panelBorder3->setWidth(1);
	endEditCP(panelBorder3, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);

	// Create and edit Panel
	PanelPtr rightPanelCheckPanel = osg::Panel::create();
	beginEditCP(rightPanelCheckPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundFieldMask | Panel::BorderFieldMask);
		rightPanelCheckPanel->setPreferredSize( Vec2s(200, 300) );
		rightPanelCheckPanel->getChildren().addValue(rightPanelCheck1);
		rightPanelCheckPanel->getChildren().addValue(rightPanelCheck2);
		rightPanelCheckPanel->getChildren().addValue(rightPanelCheck3);
		rightPanelCheckPanel->getChildren().addValue(rightPanelCheck4);
		rightPanelCheckPanel->setLayout(rightPanelCheckPanelLayout);
		rightPanelCheckPanel->setBackground(rightPanelCheckPanelBackground);
		rightPanelCheckPanel->setBorder(panelBorder3);
	endEditCP(rightPanelCheckPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundFieldMask | Panel::BorderFieldMask);

	return rightPanelCheckPanel;
}
UIBackgroundPtr createComplexBackground(void)
{

	// Create complex Background 
	ColorUIBackgroundPtr backgroundBase = osg::ColorUIBackground::create();
	GradientUIBackgroundPtr gradient1 = osg::GradientUIBackground::create();
	GradientUIBackgroundPtr gradient2 = osg::GradientUIBackground::create();
	GradientUIBackgroundPtr gradient3 = osg::GradientUIBackground::create();
	CompoundUIBackgroundPtr compound1 = osg::CompoundUIBackground::create();
	CompoundUIBackgroundPtr compound2 = osg::CompoundUIBackground::create();
	CompoundUIBackgroundPtr background = osg::CompoundUIBackground::create();

	beginEditCP(backgroundBase, ColorUIBackground::ColorFieldMask);
		backgroundBase->setColor( Color4f(0.0, 0.0, .25, 1.0) );
	endEditCP(backgroundBase, ColorUIBackground::ColorFieldMask);

	beginEditCP(gradient1, GradientUIBackground::ColorStartFieldMask | GradientUIBackground::ColorEndFieldMask | GradientUIBackground::AlignmentFieldMask);
		gradient1->setColorStart( Color4f(1.0, 0.0, 0.0, 0.5));
		gradient1->setColorEnd( Color4f(0.5, 0.0, 0.0, 0.3));
		gradient1->setAlignment(HORIZONTAL_ALIGNMENT);
	endEditCP(gradient1, GradientUIBackground::ColorStartFieldMask | GradientUIBackground::ColorEndFieldMask | GradientUIBackground::AlignmentFieldMask);

	beginEditCP(gradient2, GradientUIBackground::ColorStartFieldMask | GradientUIBackground::ColorEndFieldMask | GradientUIBackground::AlignmentFieldMask);
		gradient2->setColorStart( Color4f(.6, 0.0, 0.3, 1.0));
		gradient2->setColorEnd( Color4f(.2, 0.0, 0.3, 0.5));
		gradient2->setAlignment(VERTICAL_ALIGNMENT);
	endEditCP(gradient2, GradientUIBackground::ColorStartFieldMask | GradientUIBackground::ColorEndFieldMask | GradientUIBackground::AlignmentFieldMask);

	beginEditCP(gradient3, GradientUIBackground::ColorStartFieldMask | GradientUIBackground::ColorEndFieldMask | GradientUIBackground::AlignmentFieldMask);
		gradient3->setColorStart( Color4f(0.0, 0.0, 0.2, 0.2));
		gradient3->setColorEnd( Color4f(0.0, 0.0, 0.2, 0.3));
		gradient3->setAlignment(HORIZONTAL_ALIGNMENT);
	endEditCP(gradient3, GradientUIBackground::ColorStartFieldMask | GradientUIBackground::ColorEndFieldMask | GradientUIBackground::AlignmentFieldMask);

	beginEditCP(compound1, CompoundUIBackground::BackgroundsFieldMask);
		compound1->getBackgrounds().addValue(backgroundBase);
		compound1->getBackgrounds().addValue(gradient1);
	endEditCP(compound1, CompoundUIBackground::BackgroundsFieldMask);

	beginEditCP(compound2, CompoundUIBackground::BackgroundsFieldMask);
		compound2->getBackgrounds().addValue(gradient2);
		compound2->getBackgrounds().addValue(gradient3);
	endEditCP(compound2, CompoundUIBackground::BackgroundsFieldMask);

	beginEditCP(background, CompoundUIBackground::BackgroundsFieldMask);
		background->getBackgrounds().addValue(compound1);
		background->getBackgrounds().addValue(compound2);
	endEditCP(background, CompoundUIBackground::BackgroundsFieldMask);

	return background;
}

ChunkMaterialPtr createRedMaterial(void){

	ChunkMaterialPtr redBackgroundMaterial = ChunkMaterial::create();
	MaterialChunkPtr redBackgroundMaterialChunk = MaterialChunk::create();
	beginEditCP(redBackgroundMaterialChunk);
		redBackgroundMaterialChunk->setAmbient (  Color4f(1.0,0.0,0.0,1.0));
		redBackgroundMaterialChunk->setDiffuse (  Color4f(1.0,0.0,0.0,1.0));
		redBackgroundMaterialChunk->setSpecular(  Color4f(1.0,0.0,0.0,1.0));
	endEditCP(redBackgroundMaterialChunk);

	beginEditCP(redBackgroundMaterial, ChunkMaterial::ChunksFieldMask);
		redBackgroundMaterial->addChunk(redBackgroundMaterialChunk);
	endEditCP(redBackgroundMaterial, ChunkMaterial::ChunksFieldMask);

	return redBackgroundMaterial;

}
ChunkMaterialPtr createBlueMaterial(void){

	ChunkMaterialPtr blueBackgroundMaterial = ChunkMaterial::create();
	MaterialChunkPtr blueBackgroundMaterialChunk = MaterialChunk::create();
	beginEditCP(blueBackgroundMaterialChunk);
		blueBackgroundMaterialChunk->setAmbient (  Color4f(0.0,0.0,0.8,1.0));
		blueBackgroundMaterialChunk->setDiffuse (  Color4f(0.0,0.0,0.8,1.0));
		blueBackgroundMaterialChunk->setSpecular(  Color4f(0.0,0.0,0.8,1.0));
	endEditCP(blueBackgroundMaterialChunk);

	beginEditCP(blueBackgroundMaterial, ChunkMaterial::ChunksFieldMask);
		blueBackgroundMaterial->addChunk(blueBackgroundMaterialChunk);
	endEditCP(blueBackgroundMaterial, ChunkMaterial::ChunksFieldMask);

	return blueBackgroundMaterial;

}
ChunkMaterialPtr createGreenMaterial(void){

	ChunkMaterialPtr greenBackgroundMaterial = ChunkMaterial::create();
	MaterialChunkPtr greenBackgroundMaterialChunk = MaterialChunk::create();
	beginEditCP(greenBackgroundMaterialChunk);
		greenBackgroundMaterialChunk->setAmbient (  Color4f(0.0,1.0,0.0,1.0));
		greenBackgroundMaterialChunk->setDiffuse (  Color4f(0.0,1.0,0.0,1.0));
		greenBackgroundMaterialChunk->setSpecular(  Color4f(0.0,1.0,0.0,1.0));
	endEditCP(greenBackgroundMaterialChunk);

	beginEditCP(greenBackgroundMaterial, ChunkMaterial::ChunksFieldMask);
		greenBackgroundMaterial->addChunk(greenBackgroundMaterialChunk);
	endEditCP(greenBackgroundMaterial, ChunkMaterial::ChunksFieldMask);

	return greenBackgroundMaterial;

}

void create3DObjects(void)
{
	// Make Object Nodes
    NodePtr torusGeo = makeTorus(90, 270, 16, 16);
	NodePtr coneGeo = makeCone(150, 50, 16, TRUE, TRUE);
	NodePtr sphereGeo = makeSphere(4, 100);
	NodePtr boxGeo = makeBox(100, 100, 100, 1, 1, 1);

	// AssignTextures
	
	beginEditCP(coneGeo->getCore());
	    Geometry::Ptr::dcast(coneGeo->getCore())->setMaterial(createBlueMaterial());
	endEditCP(coneGeo->getCore());	

	beginEditCP(sphereGeo->getCore());
	    Geometry::Ptr::dcast(sphereGeo->getCore())->setMaterial(createRedMaterial());
	endEditCP(sphereGeo->getCore());

	beginEditCP(boxGeo->getCore());
	    Geometry::Ptr::dcast(boxGeo->getCore())->setMaterial(createGreenMaterial());
	endEditCP(boxGeo->getCore());	

	// Preform transformations on them
	Matrix mat;

	
	// On Torus	
	mat.setTranslate(0.0,100.0,0.0);
	TransformPtr TorusTranCore = Transform::create();
	beginEditCP(TorusTranCore, Transform::MatrixFieldMask);
	    TorusTranCore->setMatrix(mat);
	endEditCP(TorusTranCore, Transform::MatrixFieldMask);
	
	torus = Node::create();
	beginEditCP(torus, Node::CoreFieldMask | Node::ChildrenFieldMask);
	    torus->setCore(TorusTranCore);
		torus->addChild(torusGeo);
	endEditCP(torus, Node::CoreFieldMask | Node::ChildrenFieldMask);
	
	// On Sphere
	mat.setTranslate(100.0,0.0,0.0);

	TransformPtr SphereTranCore = Transform::create();
	beginEditCP(SphereTranCore, Transform::MatrixFieldMask);
	    SphereTranCore->setMatrix(mat);
	endEditCP(SphereTranCore, Transform::MatrixFieldMask);
	
	sphere = Node::create();
	beginEditCP(sphere, Node::CoreFieldMask | Node::ChildrenFieldMask);
	    sphere->setCore(SphereTranCore);
		sphere->addChild(sphereGeo);
	endEditCP(sphere, Node::CoreFieldMask | Node::ChildrenFieldMask);

	// On Cone
	mat.setTranslate(100.0,0.0,0.0);

	TransformPtr ConeTranCore = Transform::create();
	beginEditCP(ConeTranCore, Transform::MatrixFieldMask);
	    ConeTranCore->setMatrix(mat);
	endEditCP(ConeTranCore, Transform::MatrixFieldMask);
	
	cone = Node::create();
	beginEditCP(cone, Node::CoreFieldMask | Node::ChildrenFieldMask);
	    cone->setCore(ConeTranCore);
		cone->addChild(coneGeo);
	endEditCP(cone, Node::CoreFieldMask | Node::ChildrenFieldMask);
		
	// On Box
	mat.setTranslate(100.0,250.0,0.0);

	TransformPtr BoxTranCore = Transform::create();
	beginEditCP(BoxTranCore, Transform::MatrixFieldMask);
	    BoxTranCore->setMatrix(mat);
	endEditCP(BoxTranCore, Transform::MatrixFieldMask);
	
	box = Node::create();
	beginEditCP(box, Node::CoreFieldMask | Node::ChildrenFieldMask);
	    box->setCore(BoxTranCore);
		box->addChild(boxGeo);
	endEditCP(box, Node::CoreFieldMask | Node::ChildrenFieldMask);

	addRefCP(torus);
	addRefCP(sphere);
	addRefCP(box);
	addRefCP(cone);
}
