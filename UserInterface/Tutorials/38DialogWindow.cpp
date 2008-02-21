// OpenSG Tutorial Example: Creating a Button Component
//
// This tutorial explains how to edit the basic features of
// a Button and a ToggleButtoncreated in the OSG User 
// Interface library.
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
#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGUIDrawUtils.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

bool ExitApp = false;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// 01 Button Headers
#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGDialogFactory.h>
#include <OpenSG/UserInterface/OSGDialogWindow.h>
#include <OpenSG/UserInterface/OSGColorUIBackground.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>

// Create a class to allow for the use of the Escape
// key to exit
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

class DialogWindowListener : public WindowAdapter
{
    virtual void windowClosing(const WindowEvent& e)
    {
		std::cout << "windowClosing" << std::endl;
    }

    virtual void windowClosed(const WindowEvent& e)
    {
		std::cout << "windowClosed" << std::endl;
    }

    virtual void windowOpened(const WindowEvent& e)
    {
		std::cout << "windowOpened" << std::endl;
    }

    virtual void windowIconified(const WindowEvent& e)
    {
		std::cout << "windowIconified" << std::endl;
    }

    virtual void windowDeiconified(const WindowEvent& e)
    {
		std::cout << "windowDeiconified" << std::endl;
    }

    virtual void windowActivated(const WindowEvent& e)
    {
		std::cout << "windowActivated" << std::endl;
    }

    virtual void windowDeactivated(const WindowEvent& e)
    {
		std::cout << "windowDeactivated" << std::endl;
    }

    virtual void windowEntered(const WindowEvent& e)
    {
		std::cout << "windowEntered" << std::endl;
    }

    virtual void windowExited(const WindowEvent& e)
    {
		std::cout << "windowExited" << std::endl;
    }

};

class CreateMessageBoxButtonActionListener : public ActionListener
{
protected:
	DialogWindowListener TheDialogWindowListener;

public:

   virtual void actionPerformed(const ActionEvent& e)
    {
		if(e.getSource()->getType().isDerivedFrom(Component::getClassType()))
		{
			DialogWindowPtr TheDialog = DialogFactory::createMessageDialog("This is a Message Dialog Window", "This is a message!");

			Pnt2f CenteredPosition = calculateAlignment(Component::Ptr::dcast(e.getSource())->getParentWindow()->getPosition(), Component::Ptr::dcast(e.getSource())->getParentWindow()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
			beginEditCP(TheDialog, DialogWindow::PositionFieldMask);
				TheDialog->setPosition(CenteredPosition);
			endEditCP(TheDialog, DialogWindow::PositionFieldMask);

			TheDialog->addWindowListener(&TheDialogWindowListener);

			Component::Ptr::dcast(e.getSource())->getParentWindow()->getDrawingSurface()->openWindow(TheDialog);
		}
    }
};

class CreateColorDialogButtonActionListener : public ActionListener
{

public:

   virtual void actionPerformed(const ActionEvent& e)
    {
		if(e.getSource()->getType().isDerivedFrom(Component::getClassType()))
		{
			DialogWindowPtr TheDialog = DialogFactory::the()->createColorDialog(std::string("Choose a color ..."), Color4f(1.0,0.0,0.0,1.0), std::string("38DialogWindow"));

			Pnt2f CenteredPosition = calculateAlignment(Component::Ptr::dcast(e.getSource())->getParentWindow()->getPosition(), Component::Ptr::dcast(e.getSource())->getParentWindow()->getSize(), TheDialog->getPreferredSize(), 0.5f, 0.5f);
			beginEditCP(TheDialog, DialogWindow::PositionFieldMask);
				TheDialog->setPosition(CenteredPosition);
			endEditCP(TheDialog, DialogWindow::PositionFieldMask);

			Component::Ptr::dcast(e.getSource())->getParentWindow()->getDrawingSurface()->openWindow(TheDialog);
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

                 Create an Button Component and
                 a simple Font.
                 See 17Label_Font for more
                 information about Fonts.

    ******************************************************/
    ButtonPtr ExampleButton = osg::Button::create();

    beginEditCP(ExampleButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::TextFieldMask);
            ExampleButton->setMinSize(Vec2f(50, 25));
            ExampleButton->setMaxSize(Vec2f(200, 100));
            ExampleButton->setPreferredSize(Vec2f(150, 50));
            ExampleButton->setText("Create Message Box");
    endEditCP(ExampleButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::TextFieldMask);
            
    CreateMessageBoxButtonActionListener TheExampleButtonActionListener;
    ExampleButton->addActionListener(&TheExampleButtonActionListener);
	
    ButtonPtr ColorDialogButton = osg::Button::create();

    beginEditCP(ColorDialogButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::TextFieldMask);
            ColorDialogButton->setMinSize(Vec2f(50, 25));
            ColorDialogButton->setMaxSize(Vec2f(200, 100));
            ColorDialogButton->setPreferredSize(Vec2f(150, 50));
            ColorDialogButton->setText("Create Color Dialog");
    endEditCP(ColorDialogButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::TextFieldMask);
            
    CreateColorDialogButtonActionListener TheColorDialogButtonActionListener;
    ColorDialogButton->addActionListener(&TheColorDialogButtonActionListener);

    // Create Background to be used with the MainInternalWindow
    ColorUIBackgroundPtr MainInternalWindowBackground = osg::ColorUIBackground::create();
    beginEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorUIBackground::ColorFieldMask);

    // Create The Internal Window
    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
    LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       // Assign the Button to the MainInternalWindow so it will be displayed
       // when the view is rendered.
       MainInternalWindow->getChildren().addValue(ExampleButton);
       MainInternalWindow->getChildren().addValue(ColorDialogButton);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.65f,0.65f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
    endEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);


    // Create the Drawing Surface
    UIDrawingSurfacePtr TutorialDrawingSurface = UIDrawingSurface::create();
    beginEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::InternalWindowsFieldMask | UIDrawingSurface::EventProducerFieldMask);
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindowEventProducer);
    endEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::InternalWindowsFieldMask | UIDrawingSurface::EventProducerFieldMask);
    
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
        TutorialViewport->getForegrounds().addValue(TutorialUIForeground);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);

    // Show the whole Scene
    mgr->showAll();

    TutorialWindowEventProducer->openWindow(Pnt2f(50,50),
                                        Vec2f(650,650),
                                        "OpenSG 38DialogWindow Window");

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
