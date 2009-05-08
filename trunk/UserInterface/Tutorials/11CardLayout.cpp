// OpenSG Tutorial Example: Using CardLayout
//
// This tutorial explains how use CardLayout
// 
// Includes: Using CardLayout, including a brief introduction
// to ActionListeners


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

// 11CardLayout Headers
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGLineBorder.h>
#include <OpenSG/UserInterface/OSGColorLayer.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGBorderLayout.h>
#include <OpenSG/UserInterface/OSGBorderLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGCardLayout.h>
//#include <OpenSG/UserInterface/OSGUIDefines.h>

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

            Create CardLayout and its Container
            so they can be referenced in the 
            ActionListeners (this is required
            when using ActionListeners in this
            manner).

    ******************************************************/
    CardLayoutPtr ExampleCardLayout;
    PanelPtr ExampleCardPanel;

    /******************************************************

            Create ActionListeners to use with
            CardLayout and assign each its action.

            EditCP loops with the CardLayout are
            used in the following manner:
            CardLayoutName->FUNCTION(CardLayoutContainer)

    ******************************************************/
class NextCardActionListener : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
    {
        beginEditCP(ExampleCardLayout, CardLayout::CardFieldMask);
            // Displays the next Card in CardLayout
            ExampleCardLayout->next(ExampleCardPanel);
        endEditCP(ExampleCardLayout, CardLayout::CardFieldMask);


    }
};

class BackCardActionListener : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
    {
        beginEditCP(ExampleCardLayout, CardLayout::CardFieldMask);
            ExampleCardLayout->previous(ExampleCardPanel);
        endEditCP(ExampleCardLayout, CardLayout::CardFieldMask);
    }

};
class FirstCardActionListener : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
    {
        beginEditCP(ExampleCardLayout, CardLayout::CardFieldMask);
            ExampleCardLayout->first(ExampleCardPanel);
        endEditCP(ExampleCardLayout, CardLayout::CardFieldMask);


    }
};
class LastCardActionListener : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
    {
        beginEditCP(ExampleCardLayout, CardLayout::CardFieldMask);
            ExampleCardLayout->last(ExampleCardPanel);
        endEditCP(ExampleCardLayout, CardLayout::CardFieldMask);


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

    // Make Torus Node (creates Torus in background of scene)
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

            Create BorderLayout and some
            BorderLayoutConstraints to be used 
            to set up CardLayout.

    ******************************************************/
    
    BorderLayoutPtr MainInternalWindowLayout = osg::BorderLayout::create();
    BorderLayoutConstraintsPtr ExampleButton1Constraints = osg::BorderLayoutConstraints::create();
    BorderLayoutConstraintsPtr ExampleButton2Constraints = osg::BorderLayoutConstraints::create();
    BorderLayoutConstraintsPtr ExampleButton7Constraints = osg::BorderLayoutConstraints::create();
    BorderLayoutConstraintsPtr ExampleButton8Constraints = osg::BorderLayoutConstraints::create();
    BorderLayoutConstraintsPtr ExampleCardPanelConstraints = osg::BorderLayoutConstraints::create();
        
    beginEditCP(ExampleButton1Constraints, BorderLayoutConstraints::RegionFieldMask);
        ExampleButton1Constraints->setRegion(BorderLayoutConstraints::BORDER_EAST);
    endEditCP(ExampleButton1Constraints, BorderLayoutConstraints::RegionFieldMask);
            
    beginEditCP(ExampleButton2Constraints, BorderLayoutConstraints::RegionFieldMask);
        ExampleButton2Constraints->setRegion(BorderLayoutConstraints::BORDER_WEST);
    endEditCP(ExampleButton2Constraints, BorderLayoutConstraints::RegionFieldMask);
            
    beginEditCP(ExampleButton7Constraints, BorderLayoutConstraints::RegionFieldMask);
        ExampleButton7Constraints->setRegion(BorderLayoutConstraints::BORDER_NORTH);
    endEditCP(ExampleButton7Constraints, BorderLayoutConstraints::RegionFieldMask);
            
    beginEditCP(ExampleButton8Constraints, BorderLayoutConstraints::RegionFieldMask);
        ExampleButton8Constraints->setRegion(BorderLayoutConstraints::BORDER_SOUTH);
    endEditCP(ExampleButton8Constraints, BorderLayoutConstraints::RegionFieldMask);
            
    beginEditCP(ExampleCardPanelConstraints, BorderLayoutConstraints::RegionFieldMask);
        ExampleCardPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
    endEditCP(ExampleCardPanelConstraints, BorderLayoutConstraints::RegionFieldMask);

    /******************************************************

            Create CardLayout.  CardLayout shows 
            a single Component at a time, meaning
            it is not exactly practical to use it
            alone for a Layout.  This tutorial uses
            the BorderLayout to include a Panel in
            the Center Region, and within that Panel
            using a CardLayout.  A single card is 
			displayed at one time within a 
			Container using CardLayout.

            CardLayout has four functions:
            next, previous, first, and last.

            ->next(CardContainerName): Causes 
			    CardLayout to display the next card.
			->previous(CardContainerName): Causes
				CardLayout to display the 
				previous card.
			->first(CardContainerName): Causes
				CardLayout to display the
				first card.
			->last(CardContainerName): Causes
				CardLayout to display the
				last card.
			
            These are most useful when combined with 
            ActionListeners, as shown at the top of 
            this Tutorial, to assign actions to the 
			Buttons or Components to allow the user 
			to cycle through the Card Layout and 
			view different ExampleCards.

			Note that CardContainerName is the name
			of the Container which is using the
			CardLayout, while the begin/endEditCP
			is performed on the CardLayout itself.

    ******************************************************/
    
    ExampleCardLayout = osg::CardLayout::create();
    ExampleCardPanel = osg::Panel::create();

    /******************************************************

            Create Button Components to be used with 
            CardLayout to allow for interactivity.

    ******************************************************/
    ButtonPtr ExampleButton1 = osg::Button::create();
    ButtonPtr ExampleButton2 = osg::Button::create();
    ButtonPtr ExampleButton3 = osg::Button::create();
    ButtonPtr ExampleButton4 = osg::Button::create();
    ButtonPtr ExampleButton5 = osg::Button::create();
    ButtonPtr ExampleButton6 = osg::Button::create();    
    ButtonPtr ExampleButton7 = osg::Button::create();
    ButtonPtr ExampleButton8 = osg::Button::create();

    beginEditCP(ExampleButton1, Button::TextFieldMask | Button::ConstraintsFieldMask);
        ExampleButton1->setText("Next Card");
        ExampleButton1->setConstraints(ExampleButton1Constraints);
    endEditCP(ExampleButton1, Button::TextFieldMask | Button::ConstraintsFieldMask);
    
    // Add ActionListener
    NextCardActionListener TheNextCardActionListener;
    ExampleButton1->addActionListener( &TheNextCardActionListener);
    
    beginEditCP(ExampleButton2, Button::TextFieldMask | Button::ConstraintsFieldMask);
        ExampleButton2->setText("Previous Card");
        ExampleButton2->setConstraints(ExampleButton2Constraints);
    endEditCP(ExampleButton2, Button::TextFieldMask | Button::ConstraintsFieldMask);

    // Add ActionListener
    BackCardActionListener TheBackCardActionListener;
    ExampleButton2->addActionListener( &TheBackCardActionListener);

    beginEditCP(ExampleButton3, Button::TextFieldMask);
        ExampleButton3->setText("This");
    endEditCP(ExampleButton3, Button::TextFieldMask);

    beginEditCP(ExampleButton4, Button::TextFieldMask);
        ExampleButton4->setText("is");
    endEditCP(ExampleButton4, Button::TextFieldMask);

    beginEditCP(ExampleButton5, Button::TextFieldMask);
        ExampleButton5->setText("Card");
    endEditCP(ExampleButton5, Button::TextFieldMask);
    
    beginEditCP(ExampleButton6, Button::TextFieldMask);
        ExampleButton6->setText("Layout");
    endEditCP(ExampleButton6, Button::TextFieldMask);

    beginEditCP(ExampleButton7, Button::TextFieldMask | Button::ConstraintsFieldMask);
        ExampleButton7->setText("First Card");
        ExampleButton7->setConstraints(ExampleButton7Constraints);
    endEditCP(ExampleButton7, Button::TextFieldMask | Button::ConstraintsFieldMask);
        
    // Add ActionListener
    FirstCardActionListener TheFirstCardActionListener;
    ExampleButton7->addActionListener( &TheFirstCardActionListener);

    beginEditCP(ExampleButton8, Button::TextFieldMask | Button::ConstraintsFieldMask);
        ExampleButton8->setText("Last Card");
        ExampleButton8->setConstraints(ExampleButton8Constraints);
    endEditCP(ExampleButton8, Button::TextFieldMask | Button::ConstraintsFieldMask);
    
    // Add ActionListener
    LastCardActionListener TheLastCardActionListener;
    ExampleButton8->addActionListener( &TheLastCardActionListener);


    beginEditCP(ExampleCardPanel, Panel::LayoutFieldMask | Panel::ChildrenFieldMask);
        ExampleCardPanel->setLayout(ExampleCardLayout);
        ExampleCardPanel->getChildren().push_back(ExampleButton3);
        ExampleCardPanel->getChildren().push_back(ExampleButton4);
        ExampleCardPanel->getChildren().push_back(ExampleButton5);
        ExampleCardPanel->getChildren().push_back(ExampleButton6);
        ExampleCardPanel->setConstraints(ExampleCardPanelConstraints);
    endEditCP(ExampleCardPanel, Panel::LayoutFieldMask | Panel::ChildrenFieldMask);




    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().push_back(ExampleButton1);
       MainInternalWindow->getChildren().push_back(ExampleButton2);
       MainInternalWindow->getChildren().push_back(ExampleButton7);
       MainInternalWindow->getChildren().push_back(ExampleButton8);
       MainInternalWindow->getChildren().push_back(ExampleCardPanel);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
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
                                        "OpenSG 11CardLayout Window");

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