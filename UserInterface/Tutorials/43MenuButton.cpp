// OpenSG Tutorial Example: Creating a List
//
// This tutorial explains how to create a List 
// via the  OSG User Interface library.
// 
// Includes: placing multiple buttons using Flow Layout


// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

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

// 18List Headers
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGMenuButton.h>
#include <OpenSG/UserInterface/OSGLayers.h>

// List header files
#include <OpenSG/UserInterface/OSGDefaultListModel.h>


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

class ExampleMenuButtonActionListener : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
    {
        MenuButtonPtr TheMenuButton(MenuButton::Ptr::dcast(e.getSource()));
        if(TheMenuButton != NullFC)
        {
            try
            {
                std::string StrValue = boost::any_cast<std::string>(TheMenuButton->getSelectionValue());
                std::cout << "Selected: " << StrValue << std::endl;
            }
            catch(boost::bad_any_cast &)
            {
            }
        }
    }
};

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

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

    //Create list data model to use for the Popup menu
	DefaultListModelPtr ExampleListModel = DefaultListModel::create();
    ExampleListModel->pushBack(boost::any(std::string("Red")));
    ExampleListModel->pushBack(boost::any(std::string("Green")));
    ExampleListModel->pushBack(boost::any(std::string("Blue")));
    ExampleListModel->pushBack(boost::any(std::string("Orange")));
    ExampleListModel->pushBack(boost::any(std::string("Purple")));
    ExampleListModel->pushBack(boost::any(std::string("Yellow")));
    ExampleListModel->pushBack(boost::any(std::string("White")));
    ExampleListModel->pushBack(boost::any(std::string("Black")));
    ExampleListModel->pushBack(boost::any(std::string("Gray")));
    ExampleListModel->pushBack(boost::any(std::string("Brown")));
    ExampleListModel->pushBack(boost::any(std::string("Indigo")));
    ExampleListModel->pushBack(boost::any(std::string("Pink")));
    ExampleListModel->pushBack(boost::any(std::string("Violet")));
    ExampleListModel->pushBack(boost::any(std::string("Mauve")));
    ExampleListModel->pushBack(boost::any(std::string("Peach")));

    //Create the MenuButton
    MenuButtonPtr ExampleMenuButton = MenuButton::create();

    beginEditCP(ExampleMenuButton, MenuButton::TextFieldMask | MenuButton::PreferredSizeFieldMask | MenuButton::ModelFieldMask);
        ExampleMenuButton->setText("Menu Button");
        ExampleMenuButton->setPreferredSize(Vec2f(120, 20));
        ExampleMenuButton->setModel(ExampleListModel);
    endEditCP(ExampleMenuButton, MenuButton::TextFieldMask | MenuButton::PreferredSizeFieldMask | MenuButton::ModelFieldMask);
    ExampleMenuButtonActionListener TheActionListener;
    ExampleMenuButton->addMenuActionListener(&TheActionListener);

    // Create MainFramelayout
    FlowLayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();
    beginEditCP(MainInternalWindowLayout, FlowLayout::OrientationFieldMask | FlowLayout::MajorAxisAlignmentFieldMask | FlowLayout::MinorAxisAlignmentFieldMask);
        MainInternalWindowLayout->setOrientation(FlowLayout::HORIZONTAL_ORIENTATION);
        MainInternalWindowLayout->setMajorAxisAlignment(0.5f);
        MainInternalWindowLayout->setMinorAxisAlignment(0.5f);
    endEditCP(MainInternalWindowLayout, FlowLayout::OrientationFieldMask | FlowLayout::MajorAxisAlignmentFieldMask | FlowLayout::MinorAxisAlignmentFieldMask);
    
    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().push_back(ExampleMenuButton);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.7f,0.5f));
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
                                        "OpenSG 43 Menu Button Window");

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
