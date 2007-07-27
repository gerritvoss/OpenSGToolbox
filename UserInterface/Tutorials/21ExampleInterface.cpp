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

// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

//Input
#include <OpenSG/Input/OSGWindowUtils.h>
#include <OpenSG/Input/OSGMouseListener.h>
#include <OpenSG/Input/OSGMouseMotionListener.h>

//UserInterface Headers
#include <OpenSG/UserInterface/OSGUIRectangle.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
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


// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2s Size);

// Create functions create Component Panels to make 
// code easier to read
ComponentPtr createleftPanelButtonPanel(void);
ComponentPtr createleftPanelTextPanel(void);
ComponentPtr createrightPanelButtonPanel(void);
ComponentPtr createrightPanelCheckPanel(void);

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
        mgr->mouseButtonPress(e.getButton(), e.getLocation().x(), e.getLocation().y());
    }
    virtual void mouseReleased(const MouseEvent& e)
    {
        mgr->mouseButtonRelease(e.getButton(), e.getLocation().x(), e.getLocation().y());
    }
};

class TutorialMouseMotionListener : public MouseMotionListener
{
  public:
    virtual void mouseMoved(const MouseEvent& e)
    {
        mgr->mouseMove(e.getLocation().x(), e.getLocation().y());
    }

    virtual void mouseDragged(const MouseEvent& e)
    {
        mgr->mouseMove(e.getLocation().x(), e.getLocation().y());
    }
};

// Initialize WIN32 & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    WindowPtr MainWindow;
    WindowEventProducerPtr TheWindowEventProducer;
    createDefaultWindow(Pnt2s(50,50),
                                        Vec2s(550,550),
                                        "OpenSG 21ExampleInterface Window",
                                        MainWindow,
                                        TheWindowEventProducer);
    
    TheWindowEventProducer->setDisplayCallback(display);
    TheWindowEventProducer->setReshapeCallback(reshape);

    TutorialMouseListener mouseListener;
    TutorialMouseMotionListener mouseMotionListener;
    TheWindowEventProducer->addMouseListener(&mouseListener);
    TheWindowEventProducer->addMouseMotionListener(&mouseMotionListener);

   // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(90, 270, 16, 16);


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
	FontPtr leftPanelLabel1Font = osg::Font::create();

	beginEditCP(leftPanelLabel1Font, Font::SizeFieldMask);
		leftPanelLabel1Font->setSize(50);
	endEditCP(leftPanelLabel1Font, Font::SizeFieldMask);

	beginEditCP(leftPanelLabel1, Component::BackgroundFieldMask | Label::FontFieldMask | Label::TextFieldMask | Component::PreferredSizeFieldMask);
		leftPanelLabel1->setBackground(greyBackground);
		leftPanelLabel1->setFont(leftPanelLabel1Font);
		leftPanelLabel1->setText("Sample Label");
		leftPanelLabel1->setPreferredSize( Vec2s(300, 100) );
	endEditCP(leftPanelLabel1, Component::BackgroundFieldMask | Label::FontFieldMask | Label::TextFieldMask | Component::PreferredSizeFieldMask);

	

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
		leftPanel->getChildren().addValue(createleftPanelTextPanel());
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
	    //drawingSurface->setEventProducer(TheWindowEventProducer);
    endEditCP  (drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask);
	
    //Make A 3D Rectangle to draw the UI on
    UIRectanglePtr UIRectCore = UIRectangle::create();
    beginEditCP(UIRectCore, UIRectangle::PointFieldMask | UIRectangle::DrawingSurfaceFieldMask);
        UIRectCore->setPoint(Pnt3f(0.0,0.0,370.0));
        UIRectCore->setWidth(620);
        UIRectCore->setHeight(620);
        UIRectCore->setDrawingSurface(drawingSurface);
	endEditCP(UIRectCore, UIRectangle::PointFieldMask | UIRectangle::DrawingSurfaceFieldMask);
	
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

    openWindow(TheWindowEventProducer);

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



ComponentPtr createleftPanelTextPanel(void)
{


// Create and edit the Panel Text areas

	// Create and edit Panel layout
	FlowLayoutPtr leftPanelTextPanelLayout = osg::FlowLayout::create();
	/*beginEditCP(leftPanelTextPanelLayout, GridLayout::RowsFieldMask | GridLayout::ColumnsFieldMask);
		leftPanelTextPanelLayout->setRows(2);
		leftPanelTextPanelLayout->setColumns(1);
	endEditCP(leftPanelTextPanelLayout, GridLayout::RowsFieldMask | GridLayout::ColumnsFieldMask);
	*/
	ButtonPtr test1 = osg::Button::create();
	ButtonPtr test2 = osg::Button::create();
	
	// Create an edit Panel Background
	ColorUIBackgroundPtr leftPanelTextPanelBackground = osg::ColorUIBackground::create();
	beginEditCP(leftPanelTextPanelBackground, ColorUIBackground::ColorFieldMask);
		leftPanelTextPanelBackground->setColor( Color4f(0.93,0.93,0.93,1.0) );
	endEditCP(leftPanelTextPanelBackground, ColorUIBackground::ColorFieldMask);

	// Create Panel Border
	LineBorderPtr panelBorder1 = osg::LineBorder::create();
	beginEditCP(panelBorder1, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);
		panelBorder1->setColor( Color4f(0.0,0.0,0.0,1.0) );
		panelBorder1->setWidth(1);
	endEditCP(panelBorder1, LineBorder::ColorFieldMask | LineBorder::WidthFieldMask);

	// Create and edit Panel
	PanelPtr leftPanelTextPanel = osg::Panel::create();
	beginEditCP(leftPanelTextPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundFieldMask | Panel::BorderFieldMask);
		leftPanelTextPanel->setPreferredSize( Vec2s(180, 500) );
		leftPanelTextPanel->getChildren().addValue(test1);
		leftPanelTextPanel->getChildren().addValue(test2);
		leftPanelTextPanel->setLayout(leftPanelTextPanelLayout);
		leftPanelTextPanel->setBackground(leftPanelTextPanelBackground);
		leftPanelTextPanel->setBorder(panelBorder1);
	endEditCP(leftPanelTextPanel, Panel::PreferredSizeFieldMask | Panel::ChildrenFieldMask | Panel::LayoutFieldMask | Panel::BackgroundFieldMask | Panel::BorderFieldMask);

	return leftPanelTextPanel;
}

ComponentPtr createrightPanelButtonPanel(void)
{
	// Create and edit the Panel Buttons
	ButtonPtr rightPanelButton1 = osg::Button::create();
	ButtonPtr rightPanelButton2 = osg::Button::create();
	ButtonPtr rightPanelButton3 = osg::Button::create();
	ButtonPtr rightPanelButton4 = osg::Button::create();

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
		rightPanelCheck1->setText("check1");
		rightPanelCheck1->setPreferredSize( Vec2s(100,50) );
	endEditCP(rightPanelCheck1, Button::TextFieldMask, Component::PreferredSizeFieldMask);
	
	beginEditCP(rightPanelCheck2, Button::TextFieldMask, Component::PreferredSizeFieldMask);
		rightPanelCheck2->setText("check2");
		rightPanelCheck2->setPreferredSize( Vec2s(100,50) );
	endEditCP(rightPanelCheck2, Button::TextFieldMask, Component::PreferredSizeFieldMask);

	beginEditCP(rightPanelCheck3, Button::TextFieldMask, Component::PreferredSizeFieldMask);
		rightPanelCheck3->setText("check3");
		rightPanelCheck3->setPreferredSize( Vec2s(100,50) );
	endEditCP(rightPanelCheck3, Button::TextFieldMask, Component::PreferredSizeFieldMask);

	beginEditCP(rightPanelCheck4, Button::TextFieldMask, Component::PreferredSizeFieldMask);
		rightPanelCheck4->setText("check4");
		rightPanelCheck4->setPreferredSize( Vec2s(100,50) );
	endEditCP(rightPanelCheck4, Button::TextFieldMask, Component::PreferredSizeFieldMask);


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