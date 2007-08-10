// OpenSG Tutorial Example: Using CardLayout
//
// This tutorial explains how use CardLayout
// 
// Includes: Using CardLayout, including a brief introduction
// to ActionListeners

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

//UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGBorderLayout.h>
#include <OpenSG/UserInterface/OSGBorderLayoutConstraints.h>

// Include relevant header files
#include <OpenSG/UserInterface/OSGCardLayout.h>
#include <OpenSG/UserInterface/OSGUIDefines.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
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

	/******************************************************

			Create CardLayout and its container
			so they can be referenced in the 
			ActionListeners (this is required
			when using ActionListeners in this
			manner)

	******************************************************/
	CardLayoutPtr cardLayout;
	PanelPtr cardPanel;

	/******************************************************

			Create ActionListeners to use with
			CardLayout and assign each its action.

			EditCP loops with the CardLayout are
			used in the following manner:
			CardLayoutName->FUNCTION(CardLayoutContainer)

	******************************************************/
class nextCard : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
	{
		beginEditCP(cardLayout, CardLayout::CardFieldMask);
			// Displays the next Card in CardLayout
			cardLayout->next(cardPanel);
		endEditCP(cardLayout, CardLayout::CardFieldMask);


	}
};

class backCard : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
	{
		beginEditCP(cardLayout, CardLayout::CardFieldMask);
			cardLayout->previous(cardPanel);
		endEditCP(cardLayout, CardLayout::CardFieldMask);
	}

};
class firstCard : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
	{
		beginEditCP(cardLayout, CardLayout::CardFieldMask);
			cardLayout->first(cardPanel);
		endEditCP(cardLayout, CardLayout::CardFieldMask);


	}
};
class lastCard : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
	{
		beginEditCP(cardLayout, CardLayout::CardFieldMask);
			cardLayout->last(cardPanel);
		endEditCP(cardLayout, CardLayout::CardFieldMask);


	}
};
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


    // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Main Scene Node
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        scene->setCore(osg::Group::create());
 
        // add the torus as a child
        //scene->addChild(TorusGeometryNode);
    }
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

	// Create the Graphics
	GraphicsPtr graphics = osg::Graphics2D::create();

	// Initialize the LookAndFeelManager to enable default 
	// settings for the Button
	LookAndFeelManager::the()->getLookAndFeel()->init();
	
	/******************************************************

			Create some BorderLayouts and 
			BorderLayoutConstraints to be used 
			to set up CardLayout

	******************************************************/
	
	BorderLayoutPtr MainFrameLayout = osg::BorderLayout::create();
	BorderLayoutConstraintsPtr button1Constraints = osg::BorderLayoutConstraints::create();
	BorderLayoutConstraintsPtr button2Constraints = osg::BorderLayoutConstraints::create();
	BorderLayoutConstraintsPtr button7Constraints = osg::BorderLayoutConstraints::create();
	BorderLayoutConstraintsPtr button8Constraints = osg::BorderLayoutConstraints::create();
	BorderLayoutConstraintsPtr cardPanelConstraints = osg::BorderLayoutConstraints::create();
		
	beginEditCP(button1Constraints, BorderLayoutConstraints::RegionFieldMask);
		button1Constraints->setRegion(BorderLayoutConstraints::BORDER_EAST);
	endEditCP(button1Constraints, BorderLayoutConstraints::RegionFieldMask);
			
	beginEditCP(button2Constraints, BorderLayoutConstraints::RegionFieldMask);
		button2Constraints->setRegion(BorderLayoutConstraints::BORDER_WEST);
	endEditCP(button2Constraints, BorderLayoutConstraints::RegionFieldMask);
			
	beginEditCP(button7Constraints, BorderLayoutConstraints::RegionFieldMask);
		button7Constraints->setRegion(BorderLayoutConstraints::BORDER_NORTH);
	endEditCP(button7Constraints, BorderLayoutConstraints::RegionFieldMask);
			
	beginEditCP(button8Constraints, BorderLayoutConstraints::RegionFieldMask);
		button8Constraints->setRegion(BorderLayoutConstraints::BORDER_SOUTH);
	endEditCP(button8Constraints, BorderLayoutConstraints::RegionFieldMask);
			
	beginEditCP(cardPanelConstraints, BorderLayoutConstraints::RegionFieldMask);
		cardPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
	endEditCP(cardPanelConstraints, BorderLayoutConstraints::RegionFieldMask);

	/******************************************************

			Create CardLayout.  CardLayout shows 
			a single Component at a time, meaning
			it is not exactly practical to use it
			alone for a Layout.  This tutorial uses
			the BorderLayout to include a Panel in
			the Center Region, and within that Panel
			setting the CardLayout.

			CardLayout has four function calls-
			next, previous, first, and last.

			To call these functions, use  the "->" 
			command.  For example, in an EditCP loop
			CardLayoutName->FUNCTION(ContainerWithCardLayout)

			These are most useful when combined with 
			ActionListeners, as shown at the top of 
			the code, to assign actions to the Buttons 
			or Components to allow the user to cycle
			through the Card Layout and view different
			cards.

	******************************************************/
	
	cardLayout = osg::CardLayout::create();
	cardPanel = osg::Panel::create();

	/******************************************************

			Create Button Components to be used with 
			CardLayout and specify their characteristics

	******************************************************/
	ButtonPtr button1 = osg::Button::create();
	ButtonPtr button2 = osg::Button::create();
	ButtonPtr button3 = osg::Button::create();
	ButtonPtr button4 = osg::Button::create();
	ButtonPtr button5 = osg::Button::create();
	ButtonPtr button6 = osg::Button::create();	
	ButtonPtr button7 = osg::Button::create();
	ButtonPtr button8 = osg::Button::create();

	beginEditCP(button1, Button::TextFieldMask | Component::ConstraintsFieldMask);
		button1->setText("Next Card");
		button1->setConstraints(button1Constraints);
	endEditCP(button1, Button::TextFieldMask | Component::ConstraintsFieldMask);
	
	// Add ActionListener
	nextCard button1Next;
	button1->addActionListener( &button1Next);
	

	beginEditCP(button2, Button::TextFieldMask | Component::ConstraintsFieldMask);
		button2->setText("Previous Card");
		button2->setConstraints(button2Constraints);
	endEditCP(button2, Button::TextFieldMask | Component::ConstraintsFieldMask);

	// Add ActionListener
	backCard button2Previous;
	button2->addActionListener( &button2Previous);

	beginEditCP(button3, Button::TextFieldMask);
		button3->setText("This");
	endEditCP(button3, Button::TextFieldMask);

	beginEditCP(button4, Button::TextFieldMask);
		button4->setText("is");
	endEditCP(button4, Button::TextFieldMask);

	beginEditCP(button5, Button::TextFieldMask);
		button5->setText("Card");
	endEditCP(button5, Button::TextFieldMask);
	
	beginEditCP(button6, Button::TextFieldMask);
		button6->setText("Layout");
	endEditCP(button6, Button::TextFieldMask);

	beginEditCP(button7, Button::TextFieldMask | Component::ConstraintsFieldMask);
		button7->setText("First Card");
		button7->setConstraints(button7Constraints);
	endEditCP(button7, Button::TextFieldMask | Component::ConstraintsFieldMask);
		
	// Add ActionListener
	firstCard button7First;
	button7->addActionListener( &button7First);

	beginEditCP(button8, Button::TextFieldMask | Component::ConstraintsFieldMask);
		button8->setText("Last Card");
		button8->setConstraints(button8Constraints);
	endEditCP(button8, Button::TextFieldMask | Component::ConstraintsFieldMask);
	
	// Add ActionListener
	lastCard button8Last;
	button8->addActionListener( &button8Last);


	beginEditCP(cardPanel);
		cardPanel->setLayout(cardLayout);
		cardPanel->getChildren().addValue(button3);
		cardPanel->getChildren().addValue(button4);
		cardPanel->getChildren().addValue(button5);
		cardPanel->getChildren().addValue(button6);
		cardPanel->setConstraints(cardPanelConstraints);
	endEditCP(cardPanel);




	FramePtr MainFrame = osg::Frame::create();
	// Edit MainFrame
	beginEditCP(MainFrame, Frame::ChildrenFieldMask | Frame::LayoutFieldMask);
		MainFrame->getChildren().addValue(button1);
		MainFrame->getChildren().addValue(button2);
		MainFrame->getChildren().addValue(button7);
		MainFrame->getChildren().addValue(button8);
		MainFrame->getChildren().addValue(cardPanel);
		MainFrame->setLayout(MainFrameLayout);
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
		foreground->setFrameBounds(Vec2f(0.5,0.5));
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
                                        "OpenSG 11CardLayout Window");

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
