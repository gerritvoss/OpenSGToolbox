/*************************************************
Welcome to the 06Dialog tutorial.  In this tutorial, 
you will see examples of how to create the following 
OGS Game components:
	
	CaptionListener
	Caption
	
As well as:

    Sound
	
Caption is used mainly for the purpose of diplaying
text on screen corresponding with the sound being 
played. The CaptionListener is used to listen for
a change in a specific caption. The CaptionListener 
listens for:

    segmentActivated - When a new segment of text is started
    captionStarted - When the specified caption itself is started
    captionEnded - When the specified caption ends

*************************************************/



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

#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGToggleButton.h>
#include <OpenSG/UserInterface/OSGUIFont.h>
#include <OpenSG/UserInterface/OSGColorLayer.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGPolygonUIDrawObject.h>
#include <OpenSG/UserInterface/OSGUIDrawObjectCanvas.h>
#include <OpenSG/UserInterface/OSGPanel.h>
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/Game/OSGCaptionListener.h>
#include <OpenSG/Game/OSGDialogListener.h>
#include <OpenSG/Game/OSGDefaultDialogComponentGenerator.h>
#include <OpenSG/Game/OSGDialogInterface.h>

//Dialog Includes
#include <OpenSG/Game/OSGDialog.h>
#include <OpenSG/Game/OSGDialogHierarchy.h>
#include <OpenSG/Game/OSGDialogListener.h>

//Sound
#include <OpenSG/Sound/OSGSoundManager.h>
#include <OpenSG/Sound/OSGSound.h>

#include <map>


//XML header files
#include <OpenSG/Toolbox/OSGFCFileHandler.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

DialogHierarchyPtr TutorialDialog;
InternalWindowPtr MainInternalWindow;
Int32 segUpdate = 0;
NodePtr scene;
UIFontPtr ButtonFont;

DialogPtr Restart1;
DialogPtr End1;
DialogPtr Restart2;
DialogPtr End2;
DialogPtr Restart3;
DialogPtr End3;
DialogPtr Restart4;
DialogPtr End4;

ColorLayerPtr MainInternalWindowBackground;

DialogPtr BDialogChildA;
DialogPtr BDialogChildB;
DialogPtr ADialogChildA;
DialogPtr ADialogChildB;

SoundPtr TutorialSound;
UInt32 TutorialSoundChannelID;

std::map<ButtonPtr, DialogPtr> _ButtonToResponseMap;

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

bool ExitApp = false;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

class TutorialUpdateListener : public UpdateListener
{
public:
    virtual void update(const UpdateEvent& e)
    {

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

class ResponseButtonActionListener : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
    {
        _ButtonToResponseMap[ButtonPtr::dcast(e.getSource())]->selectResponse();
    }

};
ResponseButtonActionListener TutorialResponseListener;

class TutorialDialogListener : public DialogListener
{
public:

    virtual void started(const DialogEvent& e)
    {
        if(DialogPtr::dcast(e.getSource()) == BDialogChildB)
        {
            NodePtr s = makeSphere(1,2);
            beginEditCP(scene, Node::ChildrenFieldMask);
                while(scene->getNChildren() > 0)
                {
                    scene->subChild(scene->getNChildren()-1);
                }
                scene->addChild(s);
            endEditCP(scene, Node::ChildrenFieldMask);
        }
        if(DialogPtr::dcast(e.getSource()) == BDialogChildA)
        {
            NodePtr s = makeBox(3,3,3,2,2,2);
            beginEditCP(scene, Node::ChildrenFieldMask);
                while(scene->getNChildren() > 0)
                {
                    scene->subChild(scene->getNChildren()-1);
                }
                scene->addChild(s);
            endEditCP(scene, Node::ChildrenFieldMask);
        }
        if(DialogPtr::dcast(e.getSource()) == ADialogChildA)
        {
            beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
                MainInternalWindowBackground->setColor(Color4f(0.0,0.0,1.0,0.5));
            endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        }
        if(DialogPtr::dcast(e.getSource()) == ADialogChildB)
        {
            beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
                MainInternalWindowBackground->setColor(Color4f(1.0,0.0,0.0,0.5));
            endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        }
        if(DialogPtr::dcast(e.getSource()) == End1 || DialogPtr::dcast(e.getSource()) == End2 || DialogPtr::dcast(e.getSource()) == End3 || DialogPtr::dcast(e.getSource()) == End4 )
        {
            ExitApp = true;
        }
        if(DialogPtr::dcast(e.getSource()) == Restart1 || DialogPtr::dcast(e.getSource()) == Restart2 || DialogPtr::dcast(e.getSource()) == Restart3 || DialogPtr::dcast(e.getSource()) == Restart4)
        {
            beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
                MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
            endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);

            NodePtr s = makeTorus(.5, 2, 16, 16);
            beginEditCP(scene, Node::ChildrenFieldMask);
                while(scene->getNChildren() > 0)
                {
                    scene->subChild(scene->getNChildren()-1);
                }
                scene->addChild(s);
            endEditCP(scene, Node::ChildrenFieldMask);
        }
    }
    virtual void ended(const DialogEvent& e)
    {
        std::cout<<"Dialog Ended"<<std::endl;
        
    }
    virtual void responseSelected(const DialogEvent& e)
    {
    }
    virtual void responsesReady(const DialogEvent& e)
    {

    }
    virtual void terminated(const DialogEvent& e)
    {
        std::cout<<"Dialog Terminated"<<std::endl;
        if(DialogPtr::dcast(e.getSource()) == Restart1 || DialogPtr::dcast(e.getSource()) == Restart2 || DialogPtr::dcast(e.getSource()) == Restart3 || DialogPtr::dcast(e.getSource()) == Restart4)
        {
            TutorialDialog->reset();
            TutorialDialog->start();
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
    TutorialUpdateListener TheTutorialUpdateListener;
    TutorialWindowEventProducer->addUpdateListener(&TheTutorialUpdateListener);


    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
	
    TutorialWindowEventProducer->openWindow(Pnt2f(50,50),
                                        Vec2f(550,550),
                                        "OpenSG 08 XML Dialog Window");
										
    // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Main Scene Node and add the Torus
    scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
        scene->addChild(TorusGeometryNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);


    // Create the Graphics
    GraphicsPtr TutorialGraphics = osg::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

    //Create Start and stop buttons for the caption
    ButtonPtr StartButton = osg::Button::create();
    ButtonPtr StopButton = osg::Button::create();
    ButtonPtr PauseButton = osg::Button::create();

    DefaultDialogComponentGeneratorPtr TutorialDialogGenerator = DefaultDialogComponentGenerator::create();

    ButtonFont = osg::UIFont::create();

    beginEditCP(ButtonFont, UIFont::SizeFieldMask);
        ButtonFont->setSize(16);
    endEditCP(ButtonFont, UIFont::SizeFieldMask);

    ButtonPtr Response = osg::Button::create();
    beginEditCP(Response, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask );
            Response->setMinSize(Vec2f(50, 25));
            Response->setMaxSize(Vec2f(200, 100));
            Response->setPreferredSize(Vec2f(100, 50));
            Response->setToolTipText("These buttons are for selecting a response!");

            Response->setFont(ButtonFont);
            Response->setTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
            Response->setRolloverTextColor(Color4f(1.0, 0.0, 1.0, 1.0));
            Response->setActiveTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
    endEditCP(Response, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask );

    LabelPtr LabelPrototype = Label::create();
    LabelPrototype->setAlignment(Pnt2f(0.5f,0.5f));
    LabelPrototype->setPreferredSize(Pnt2f(250.0,30.0));

    DialogInterfacePtr TutorialDialogInterface = osg::DialogInterface::create();

    beginEditCP(TutorialDialogGenerator, DefaultDialogComponentGenerator::ResponseButtonPrototypeFieldMask | DefaultDialogComponentGenerator::QuestionPrototypeFieldMask);
        TutorialDialogGenerator->setResponseButtonPrototype(Response);
        TutorialDialogGenerator->setQuestionPrototype(LabelPrototype);
    endEditCP(TutorialDialogGenerator, DefaultDialogComponentGenerator::ResponseButtonPrototypeFieldMask | DefaultDialogComponentGenerator::QuestionPrototypeFieldMask);


    TutorialDialog = osg::DialogHierarchy::create();

    beginEditCP(TutorialDialog, DialogHierarchy::DualNodeStyleFieldMask);
        TutorialDialog->setDualNodeStyle(true);
    endEditCP(TutorialDialog, DialogHierarchy::DualNodeStyleFieldMask);

    DialogPtr rootDialog = TutorialDialog->addDialog("Which do you prefer?", 0.0, NullFC, true, NullFC);

    DialogPtr RootDialogChildA = TutorialDialog->addDialog("Foreground", 0.0, NullFC, false, rootDialog);
    DialogPtr RootDialogChildB = TutorialDialog->addDialog("Background", 0.0, NullFC, false, rootDialog);
    
    DialogPtr SelectableDialogChildA = TutorialDialog->addDialog("What color would you like the forground to be?", 0.0, NullFC, true, RootDialogChildA);
    DialogPtr SelectableDialogChildB = TutorialDialog->addDialog("What object do you want to be in the background?", 0.0, NullFC, true, RootDialogChildB);

    ADialogChildA = TutorialDialog->addDialog("Blue", 0.0, NullFC, false, SelectableDialogChildA);
    ADialogChildB = TutorialDialog->addDialog("Red", 0.0, NullFC, false, SelectableDialogChildA);

    BDialogChildA = TutorialDialog->addDialog("Square", 0.0, NullFC, false, SelectableDialogChildB);
    BDialogChildB = TutorialDialog->addDialog("Sphere", 0.0, NullFC, false, SelectableDialogChildB);

    DialogPtr RestartEnd1 = TutorialDialog->addDialog("What would you like to do?", 0.0, NullFC, true, ADialogChildA);
    DialogPtr RestartEnd2 = TutorialDialog->addDialog("What would you like to do?", 0.0, NullFC, true, ADialogChildB);
    DialogPtr RestartEnd3 = TutorialDialog->addDialog("What would you like to do?", 0.0, NullFC, true, BDialogChildA);
    DialogPtr RestartEnd4 = TutorialDialog->addDialog("What would you like to do?", 0.0, NullFC, true, BDialogChildB);

    Restart1 = TutorialDialog->addDialog("Restart", 0.0, NullFC, false, RestartEnd1);
    End1 = TutorialDialog->addDialog("End", 0.0, NullFC, false, RestartEnd1);
    Restart2 = TutorialDialog->addDialog("Restart", 0.0, NullFC, false, RestartEnd2);
    End2 = TutorialDialog->addDialog("End", 0.0, NullFC, false, RestartEnd2);
    Restart3 = TutorialDialog->addDialog("Restart", 0.0, NullFC, false, RestartEnd3);
    End3 = TutorialDialog->addDialog("End", 0.0, NullFC, false, RestartEnd3);
    Restart4 = TutorialDialog->addDialog("Restart", 0.0, NullFC, false, RestartEnd4);
    End4 = TutorialDialog->addDialog("End", 0.0, NullFC, false, RestartEnd4);


    
    TutorialDialogListener TheTutorialDialogListener;
    rootDialog->addDialogListener(&TheTutorialDialogListener);
    RootDialogChildA->addDialogListener(&TheTutorialDialogListener);
    RootDialogChildB->addDialogListener(&TheTutorialDialogListener);
    ADialogChildA->addDialogListener(&TheTutorialDialogListener);
    ADialogChildB->addDialogListener(&TheTutorialDialogListener);
    BDialogChildA->addDialogListener(&TheTutorialDialogListener);
    BDialogChildB->addDialogListener(&TheTutorialDialogListener);
    Restart1->addDialogListener(&TheTutorialDialogListener);
    End1->addDialogListener(&TheTutorialDialogListener);
    Restart2->addDialogListener(&TheTutorialDialogListener);
    End2->addDialogListener(&TheTutorialDialogListener);
    Restart3->addDialogListener(&TheTutorialDialogListener);
    End3->addDialogListener(&TheTutorialDialogListener);
    Restart4->addDialogListener(&TheTutorialDialogListener);
    End4->addDialogListener(&TheTutorialDialogListener);

    SelectableDialogChildA->addDialogListener(&TheTutorialDialogListener);
    SelectableDialogChildB->addDialogListener(&TheTutorialDialogListener);
    RestartEnd1->addDialogListener(&TheTutorialDialogListener);
    RestartEnd2->addDialogListener(&TheTutorialDialogListener);
    RestartEnd3->addDialogListener(&TheTutorialDialogListener);
    RestartEnd4->addDialogListener(&TheTutorialDialogListener);
    
    LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();


    //XML Writing

    FCFileType::FCPtrStore Containers;
	Containers.insert(TutorialDialog);

	FCFileType::FCTypeVector IgnoreTypes;
	//IgnoreTypes.push_back(Node::getClassType().getId());
	//Save the Field Containers to a xml file
	FCFileHandler::the()->write(Containers,Path("./DialogHierarchy.xml"),IgnoreTypes);


    
    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    MainInternalWindowBackground = osg::ColorLayer::create();
    MainInternalWindow = osg::InternalWindow::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
    endEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);

    beginEditCP(TutorialDialogInterface, DialogInterface::ComponentGeneratorFieldMask | DialogInterface::ParentContainerFieldMask | DialogInterface::SourceDialogHierarchyFieldMask);
        TutorialDialogInterface->setComponentGenerator(TutorialDialogGenerator);
        TutorialDialogInterface->setParentContainer(MainInternalWindow);
        TutorialDialogInterface->setSourceDialogHierarchy(TutorialDialog);
    endEditCP(TutorialDialogInterface, DialogInterface::ComponentGeneratorFieldMask | DialogInterface::ParentContainerFieldMask | DialogInterface::SourceDialogHierarchyFieldMask);

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

    mgr->setRoot(scene);

    // Add the UI Foreground Object to the Scene
    ViewportPtr TutorialViewport = mgr->getWindow()->getPort(0);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);
        TutorialViewport->getForegrounds().push_back(TutorialUIForeground);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);

    // Show the whole Scene
    mgr->showAll();
    SoundManager::the()->setCamera(mgr->getCamera());

    TutorialDialog->start();

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
