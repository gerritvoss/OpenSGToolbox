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
#include <OpenSG/Input/OSGWindowAdapter.h>

// The general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

// Input
#include <OpenSG/Input/OSGWindowUtils.h>

// UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics3DExtrude.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>

#include <OpenSG/UserInterface/OSGScrollPanel.h>
#include <OpenSG/UserInterface/OSGLabel.h>

// List header files
#include <OpenSG/UserInterface/OSGList.h>
#include <OpenSG/UserInterface/OSGAbstractListModel.h>
#include <OpenSG/UserInterface/OSGDefaultListCellGenerator.h>
#include <OpenSG/UserInterface/OSGDefaultListSelectionModel.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

bool ExitApp = false;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2s Size);

ListSelectionModelPtr SelectionModel(new DefaultListSelectionModel());

// 20UIRectangle Headers
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGBorders.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGUIBackgrounds.h>
#include <OpenSG/UserInterface/OSGUIFont.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGUIRectangle.h>


// Create the WindowEvent 
WindowEventProducerPtr TheWindowEventProducer;


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
    TheWindowEventProducer = createDefaultWindowEventProducer();
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
	Graphics3DExtrudePtr graphics = osg::Graphics3DExtrude::create();
	beginEditCP(graphics);
	    graphics->setEnablePolygonAntiAliasing(false);
	    graphics->setExtrudeLength(-40.0);
	beginEditCP(graphics);


	// Initialize the LookAndFeelManager to enable default settings
	LookAndFeelManager::the()->getLookAndFeel()->init();

	/******************************************************

		Create three Button Components (button1, button2,
		and button3) and their AbsoluteLayoutConstraints.

		AbsoluteLayoutConstraints are used within the 
		AbsoluteLayout to define where the Components will
		be placed.  Most other Layouts do not need 
		Constraints, as they place things within the Layout
		automatically.

	******************************************************/

	ButtonPtr button1 = osg::Button::create();
	ButtonPtr button2 = osg::Button::create();
	ButtonPtr button3 = osg::Button::create();

	/******************************************************

		Edit Button Components and assign Text,
		PreferredSize, and AbsoluteLayoutConstraints

	******************************************************/

	// Create a simple Font to be used with the Button
	UIFontPtr sampleFont = osg::UIFont::create();
    beginEditCP(sampleFont, UIFont::SizeFieldMask | UIFont::FamilyFieldMask | UIFont::GapFieldMask | UIFont::GlyphPixelSizeFieldMask | UIFont::TextureWidthFieldMask | UIFont::StyleFieldMask);
		sampleFont->setFamily("SANS");
		sampleFont->setGap(1);
		sampleFont->setGlyphPixelSize(46);
		sampleFont->setSize(16);
		//sampleFont->setTextureWidth(0);
        sampleFont->setStyle(TextFace::STYLE_PLAIN);
	endEditCP(sampleFont, UIFont::SizeFieldMask | UIFont::FamilyFieldMask | UIFont::GapFieldMask | UIFont::GlyphPixelSizeFieldMask | UIFont::TextureWidthFieldMask | UIFont::StyleFieldMask);

	ColorUIBackgroundPtr button1Background = ColorUIBackground::create();
	beginEditCP(button1Background);
	button1Background->setColor(Color4f(1.0,0.0,0.0,1.0));
	endEditCP(button1Background);
   beginEditCP(button1, Button::PreferredSizeFieldMask |  Button::SizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);
		button1->setPreferredSize(Vec2s(100,50));
		button1->setSize(Vec2s(100,50));
		button1->setText("Button 1");
		button1->setBackground(EmptyUIBackground::create());
		button1->setTextColor(Color4f(0.0,0.0,0.0,1.0));
		
		button1->setFont(sampleFont);
	endEditCP(button1, Button::PreferredSizeFieldMask | Button::SizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);

    beginEditCP(button2, Button::PreferredSizeFieldMask |  Button::SizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);
		button2->setPreferredSize(Vec2s(100,50));
		button2->setSize(Vec2s(100,50));
		button2->setText("Button 2");
		
		button2->setFont(sampleFont);
    endEditCP  (button2, Button::PreferredSizeFieldMask | Button::SizeFieldMask | Button::TextFieldMask | Button::ConstraintsFieldMask);

    beginEditCP(button3,  Button::PreferredSizeFieldMask | Button::SizeFieldMask | Button::ConstraintsFieldMask);
		button3->setPreferredSize(Vec2s(100,50));
		button3->setSize(Vec2s(100,50));
		button3->setText("Button 3");
		
		button3->setFont(sampleFont);
    endEditCP  (button3,  Button::PreferredSizeFieldMask | Button::SizeFieldMask | Button::ConstraintsFieldMask);

	LabelPtr TheLabel = Label::create();
	beginEditCP(TheLabel,  Label::TextFieldMask);
		TheLabel->setText("Label");
	endEditCP(TheLabel,  Label::TextFieldMask);
	/******************************************************

			Create ListModel.  This is where you set
			the values for the List.

			After creating an AbstractListModel,
			do the following to make a list.
			
			First, create SFStrings and use the 
			.setValue("VALUE") function to set their
			values.  Then, use the .pushBack(&SFStringName)
			to add them to the List.

			Next, create the CellGenerator and ListSelectionModel
			defaults.

			Finally, actually create the List.  Set
			its Model, CellGenerator, and SelectionModel
			as shown below.  Finally, choose the
			type of display for the List (choices outlined
			below).

			

	******************************************************/
	// Create ListModel Component to add things to
	AbstractListModel Model;

	// Add values to it
	Model.pushBack(SharedFieldPtr(new SFString("Red")));
	Model.pushBack(SharedFieldPtr(new SFString("Green")));
	Model.pushBack(SharedFieldPtr(new SFString("Blue")));
	Model.pushBack(SharedFieldPtr(new SFString("Orange")));
	Model.pushBack(SharedFieldPtr(new SFString("Purple")));
	Model.pushBack(SharedFieldPtr(new SFString("Yellow")));
	Model.pushBack(SharedFieldPtr(new SFString("White")));
	Model.pushBack(SharedFieldPtr(new SFString("Black")));
	Model.pushBack(SharedFieldPtr(new SFString("Gray")));
	Model.pushBack(SharedFieldPtr(new SFString("Brown")));
	Model.pushBack(SharedFieldPtr(new SFString("Indigo")));
	Model.pushBack(SharedFieldPtr(new SFString("Pink")));
	Model.pushBack(SharedFieldPtr(new SFString("Violet")));
	Model.pushBack(SharedFieldPtr(new SFString("Mauve")));
	Model.pushBack(SharedFieldPtr(new SFString("Peach")));


	// Create ListCellRenderer and ListSelectionModel
	// (normally will be default).
	// Note that the DefaultListSelectionModel was
	// created at the top of this file before
	// the ActionListeners
	DefaultListCellGenerator CellGenerator;
	//DefaultListSelectionModel SelectionModel;

	// Create Background to be used with the Main Frame
	ColorUIBackgroundPtr mainBackground = osg::ColorUIBackground::create();
	beginEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
		mainBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
	endEditCP(mainBackground, ColorUIBackground::ColorFieldMask);
	// Create ListPtr
	ListPtr list = List::create();
	beginEditCP(list);
		list->setPreferredSize( Vec2s (200, 300) );
		list->setBackground(mainBackground);
        list->setCellLayout(VERTICAL_ALIGNMENT);
        //list->setCellLayout(HORIZONTAL_ALIGNMENT);
	endEditCP(list);
	// Assign the Model, CellGenerator, and SelectionModel
	// to the List
	list->setModel(&Model);
	list->setCellGenerator(&CellGenerator);
	list->setSelectionModel(SelectionModel);


	/******************************************************

			Determine the SelectionModel
			-SINGLE_SELECTION lets you select ONE item
				via a single mouse click
			-SINGLE_INTERVAL_SELECTION lets you select
				one interval via mouse and SHIFT key
			-MULTIPLE_INTERVAL_SELECTION lets you select
				via mouse, and SHIFT and CONTRL keys

			Note: this tutorial is currently set up
			to allow for this to be changed via Buttons
			with ActionListeners attached to them so
			this code is commented out

	******************************************************/

	//SelectionModel.setMode(DefaultListSelectionModel::SINGLE_SELECTION);
	//SelectionModel.setMode(DefaultListSelectionModel::SINGLE_INTERVAL_SELECTION);
	//SelectionModel.setMode(DefaultListSelectionModel::MULTIPLE_INTERVAL_SELECTION);

    //ScrollPanel
    ScrollPanelPtr TheScrollPanel = ScrollPanel::create();
    beginEditCP(TheScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
	    TheScrollPanel->setPreferredSize(Vec2s(200,300));
        TheScrollPanel->setHorizontalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
        //TheScrollPanel->setVerticalResizePolicy(ScrollPanel::RESIZE_TO_VIEW);
    endEditCP(TheScrollPanel, ScrollPanel::PreferredSizeFieldMask | ScrollPanel::HorizontalResizePolicyFieldMask);
    TheScrollPanel->setViewComponent(list);

	// Create The Main Frame
	// Create Background to be used with the Main Frame
	EmptyUIBackgroundPtr MainBackground = osg::EmptyUIBackground::create();
	
	EmptyBorderPtr MainFrameLineBorder = EmptyBorder::create();

	FramePtr MainFrame = osg::Frame::create();
	LayoutPtr MainFrameLayout = osg::FlowLayout::create();
	beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);
	   MainFrame->getChildren().addValue(button1);
	   MainFrame->getChildren().addValue(button3);
	   MainFrame->getChildren().addValue(button2);
	   MainFrame->getChildren().addValue(TheLabel);
	   MainFrame->getChildren().addValue(TheScrollPanel);
	   MainFrame->setLayout(MainFrameLayout);
	   MainFrame->setBackground(MainBackground);
	   MainFrame->setBorder(MainFrameLineBorder);
	 
    endEditCP  (MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask | Frame::BackgroundFieldMask);

	// Create the Drawing Surface
	UIDrawingSurfacePtr drawingSurface = UIDrawingSurface::create();
    beginEditCP(drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask);
		drawingSurface->setGraphics(graphics);
		drawingSurface->setRootFrame(MainFrame);
	    drawingSurface->setEventProducer(TheWindowEventProducer);
    endEditCP  (drawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::RootFrameFieldMask|UIDrawingSurface::EventProducerFieldMask);
	
    //Make A 3D Rectangle to draw the UI on
    UIRectanglePtr UIRectCore = UIRectangle::create();
    beginEditCP(UIRectCore, UIRectangle::PointFieldMask | UIRectangle::WidthFieldMask | UIRectangle::HeightFieldMask | UIRectangle::DrawingSurfaceFieldMask);
        UIRectCore->setPoint(Pnt3f(-250.0,-250.0,370.0));
        UIRectCore->setWidth(500.0);
        UIRectCore->setHeight(500.0);
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

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the manager what to manage
    mgr->setWindow(MainWindow);
    mgr->setRoot(scene);

    // Show the whole scene
    mgr->showAll();

    TheWindowEventProducer->openWindow(Pnt2s(50,50),
                                        Vec2s(950,750),
                                        "OpenSG 35Graphics3DExtrude Window");

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