// OpenSG Tutorial Example: Using CardLayout
//
// This tutorial explains how use CardLayout
// 
// Includes: Using CardLayout, including a brief introduction
// to ActionListeners


// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// Methods to create simple geometry: boxes, spheres, tori etc.
#include "OSGSimpleGeometry.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"

// The general scene file loading handler
#include "OSGSceneFileHandler.h"

// Input
#include "OSGWindowUtils.h"

// UserInterface Headers
#include "OSGUIForeground.h"
#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"
#include "OSGGraphics2D.h"
#include "OSGLookAndFeelManager.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// 11CardLayout Headers
#include "OSGButton.h"
#include "OSGLineBorder.h"
#include "OSGColorLayer.h"
#include "OSGPanel.h"
#include "OSGBorderLayout.h"
#include "OSGBorderLayoutConstraints.h"
#include "OSGCardLayout.h"
//#include "OSGUIDefines.h"

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventUnrecPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
            TutorialWindow->closeWindow();
       }
   }

   virtual void keyReleased(const KeyEventUnrecPtr e)
   {
   }

   virtual void keyTyped(const KeyEventUnrecPtr e)
   {
   }
};
    /******************************************************

            Create CardLayout and its ComponentContainer
            so they can be referenced in the 
            ActionListeners (this is required
            when using ActionListeners in this
            manner).

    ******************************************************/
    CardLayoutRefPtr ExampleCardLayout;
    PanelRefPtr ExampleCardPanel;

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

    virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
        // Displays the next Card in CardLayout
        ExampleCardLayout->next(ExampleCardPanel);
    }
};

class BackCardActionListener : public ActionListener
{
  public:

    virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
        ExampleCardLayout->previous(ExampleCardPanel);
    }

};
class FirstCardActionListener : public ActionListener
{
  public:

    virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
        ExampleCardLayout->first(ExampleCardPanel);


    }
};
class LastCardActionListener : public ActionListener
{
  public:

    virtual void actionPerformed(const ActionEventUnrecPtr e)
    {
        ExampleCardLayout->last(ExampleCardPanel);


    }
};

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindow = createNativeWindow();
    TutorialWindow->initWindow();

    TutorialWindow->setDisplayCallback(display);
    TutorialWindow->setReshapeCallback(reshape);

    TutorialKeyListener TheKeyListener;
    TutorialWindow->addKeyListener(&TheKeyListener);

    // Make Torus Node (creates Torus in background of scene)
    NodeRefPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Main Scene Node and add the Torus
    NodeRefPtr scene = OSG::Node::create();
        scene->setCore(OSG::Group::create());
        scene->addChild(TorusGeometryNode);

    // Create the Graphics
    GraphicsRefPtr TutorialGraphics = OSG::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();
    
    /******************************************************

            Create BorderLayout and some
            BorderLayoutConstraints to be used 
            to set up CardLayout.

    ******************************************************/
    
    BorderLayoutRefPtr MainInternalWindowLayout = OSG::BorderLayout::create();
    BorderLayoutConstraintsRefPtr ExampleButton1Constraints = OSG::BorderLayoutConstraints::create();
    BorderLayoutConstraintsRefPtr ExampleButton2Constraints = OSG::BorderLayoutConstraints::create();
    BorderLayoutConstraintsRefPtr ExampleButton7Constraints = OSG::BorderLayoutConstraints::create();
    BorderLayoutConstraintsRefPtr ExampleButton8Constraints = OSG::BorderLayoutConstraints::create();
    BorderLayoutConstraintsRefPtr ExampleCardPanelConstraints = OSG::BorderLayoutConstraints::create();
        
        ExampleButton1Constraints->setRegion(BorderLayoutConstraints::BORDER_EAST);
            
        ExampleButton2Constraints->setRegion(BorderLayoutConstraints::BORDER_WEST);
            
        ExampleButton7Constraints->setRegion(BorderLayoutConstraints::BORDER_NORTH);
            
        ExampleButton8Constraints->setRegion(BorderLayoutConstraints::BORDER_SOUTH);
            
        ExampleCardPanelConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);

    /******************************************************

            Create CardLayout.  CardLayout shows 
            a single Component at a time, meaning
            it is not exactly practical to use it
            alone for a Layout.  This tutorial uses
            the BorderLayout to include a Panel in
            the Center Region, and within that Panel
            using a CardLayout.  A single card is 
			displayed at one time within a 
			ComponentContainer using CardLayout.

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
			of the ComponentContainer which is using the
			CardLayout, while the begin/endEditCP
			is performed on the CardLayout itself.

    ******************************************************/
    
    ExampleCardLayout = OSG::CardLayout::create();
    ExampleCardPanel = OSG::Panel::create();

    /******************************************************

            Create Button Components to be used with 
            CardLayout to allow for interactivity.

    ******************************************************/
    ButtonRefPtr ExampleButton1 = OSG::Button::create();
    ButtonRefPtr ExampleButton2 = OSG::Button::create();
    ButtonRefPtr ExampleButton3 = OSG::Button::create();
    ButtonRefPtr ExampleButton4 = OSG::Button::create();
    ButtonRefPtr ExampleButton5 = OSG::Button::create();
    ButtonRefPtr ExampleButton6 = OSG::Button::create();    
    ButtonRefPtr ExampleButton7 = OSG::Button::create();
    ButtonRefPtr ExampleButton8 = OSG::Button::create();

        ExampleButton1->setText("Next Card");
        ExampleButton1->setConstraints(ExampleButton1Constraints);
    
    // Add ActionListener
    NextCardActionListener TheNextCardActionListener;
    ExampleButton1->addActionListener( &TheNextCardActionListener);
    
        ExampleButton2->setText("Previous Card");
        ExampleButton2->setConstraints(ExampleButton2Constraints);

    // Add ActionListener
    BackCardActionListener TheBackCardActionListener;
    ExampleButton2->addActionListener( &TheBackCardActionListener);

        ExampleButton3->setText("This");

        ExampleButton4->setText("is");

        ExampleButton5->setText("Card");
    
        ExampleButton6->setText("Layout");

        ExampleButton7->setText("First Card");
        ExampleButton7->setConstraints(ExampleButton7Constraints);
        
    // Add ActionListener
    FirstCardActionListener TheFirstCardActionListener;
    ExampleButton7->addActionListener( &TheFirstCardActionListener);

        ExampleButton8->setText("Last Card");
        ExampleButton8->setConstraints(ExampleButton8Constraints);
    
    // Add ActionListener
    LastCardActionListener TheLastCardActionListener;
    ExampleButton8->addActionListener( &TheLastCardActionListener);


        ExampleCardPanel->setLayout(ExampleCardLayout);
        ExampleCardPanel->pushToChildren(ExampleButton3);
        ExampleCardPanel->pushToChildren(ExampleButton4);
        ExampleCardPanel->pushToChildren(ExampleButton5);
        ExampleCardPanel->pushToChildren(ExampleButton6);
        ExampleCardPanel->setConstraints(ExampleCardPanelConstraints);




    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
       MainInternalWindow->pushToChildren(ExampleButton1);
       MainInternalWindow->pushToChildren(ExampleButton2);
       MainInternalWindow->pushToChildren(ExampleButton7);
       MainInternalWindow->pushToChildren(ExampleButton8);
       MainInternalWindow->pushToChildren(ExampleCardPanel);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
    

    // Create the Drawing Surface
    UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindow);
    
	TutorialDrawingSurface->openWindow(MainInternalWindow);

    // Create the UI Foreground Object
    UIForegroundRefPtr TutorialUIForeground = OSG::UIForeground::create();

        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindow);
    mgr->setRoot(scene);

    // Add the UI Foreground Object to the Scene
    ViewportRefPtr TutorialViewport = mgr->getWindow()->getPort(0);
        TutorialViewport->addForeground(TutorialUIForeground);

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
            WinSize,
            "11CardLayout");

    //Enter main Loop
    TutorialWindow->mainLoop();

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
