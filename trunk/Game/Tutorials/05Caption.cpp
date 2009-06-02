/*************************************************
Welcome to the 05Caption tutorial.  In this tutorial, 
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

//Caption Includes
#include <OpenSG/Game/OSGCaption.h>
#include <OpenSG/Game/OSGDefaultCaptionComponentGenerator.h>

//Sound
#include <OpenSG/Sound/OSGSoundManager.h>
#include <OpenSG/Sound/OSGSound.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

InternalWindowPtr MainInternalWindow;
CaptionPtr TutorialCaption;
DefaultCaptionComponentGeneratorPtr TutorialCapGen;
double timee = 0.0;
Int32 segUpdate = 0;
NodePtr scene;

SoundPtr TutorialSound;
UInt32 TutorialSoundChannelID;

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

// Create a class for the Caption listener 

class TutorialCaptionListener : public CaptionListener
{
public:
    virtual void segmentActivated(const CaptionEvent& e)
    {
        if(segUpdate == 6)
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
        if(segUpdate == 9)
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
        if(segUpdate == 11)
        {
            beginEditCP(scene, Node::ChildrenFieldMask);
                while(scene->getNChildren() > 0)
                {
                    scene->subChild(scene->getNChildren()-1);
                }
            endEditCP(scene, Node::ChildrenFieldMask);
        }
        ++segUpdate;
        std::cout<<"Segment Activated"<<std::endl;
    }
    virtual void captionStarted(const CaptionEvent& e)
    {
        std::cout<<"Caption Started"<<std::endl;
    }
    virtual void captionEnded(const CaptionEvent& e)
    {
        
        std::cout<<"Caption Ended"<<std::endl;
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

class StartButtonActionListener : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
    {
        TutorialSoundChannelID = TutorialSound->play();
        std::cout << "Start Action" << std::endl;

    }
};

class PauseButtonActionListener : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
    {
        TutorialSound->pauseToggle(TutorialSoundChannelID);
        std::cout << "Pause Action" << std::endl;

    }
};

class StopButtonActionListener : public ActionListener
{
public:

   virtual void actionPerformed(const ActionEvent& e)
    {
        TutorialSound->stop(TutorialSoundChannelID);
        std::cout << "Stop Action" << std::endl;
        NodePtr s = makeTorus(.5, 2, 16, 16);
        beginEditCP(scene, Node::ChildrenFieldMask);
            while(scene->getNChildren() > 0)
            {
                scene->subChild(scene->getNChildren()-1);
            }
            scene->addChild(s);
        endEditCP(scene, Node::ChildrenFieldMask);
        
        segUpdate = 0;
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

    //Create Start and stop buttons for the caption
    ButtonPtr StartButton = osg::Button::create();
    ButtonPtr StopButton = osg::Button::create();
    ButtonPtr PauseButton = osg::Button::create();

    UIFontPtr ButtonFont = osg::UIFont::create();

    beginEditCP(ButtonFont, UIFont::SizeFieldMask);
        ButtonFont->setSize(16);
    endEditCP(ButtonFont, UIFont::SizeFieldMask);
    
    beginEditCP(StartButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask | Button::AlignmentFieldMask);
            StartButton->setMinSize(Vec2f(50, 25));
            StartButton->setMaxSize(Vec2f(200, 100));
            StartButton->setPreferredSize(Vec2f(100, 50));
            StartButton->setToolTipText("This will start playing the caption!");

            StartButton->setText("START");
            StartButton->setFont(ButtonFont);
            StartButton->setTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
            StartButton->setRolloverTextColor(Color4f(1.0, 0.0, 1.0, 1.0));
            StartButton->setActiveTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
            StartButton->setAlignment(Vec2f(0.25,0.5));
    endEditCP(StartButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask | Button::AlignmentFieldMask);

    beginEditCP(StopButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask | Button::AlignmentFieldMask);
            StopButton->setMinSize(Vec2f(50, 25));
            StopButton->setMaxSize(Vec2f(200, 100));
            StopButton->setPreferredSize(Vec2f(100, 50));
            StopButton->setToolTipText("This will stop the caption and reset it!");

            StopButton->setText("STOP");
            StopButton->setFont(ButtonFont);
            StopButton->setTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
            StopButton->setRolloverTextColor(Color4f(1.0, 0.0, 1.0, 1.0));
            StopButton->setActiveTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
            StopButton->setAlignment(Vec2f(0.75,0.5));
    endEditCP(StopButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask | Button::AlignmentFieldMask);

    beginEditCP(PauseButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask | Button::AlignmentFieldMask);
            PauseButton->setMinSize(Vec2f(50, 25));
            PauseButton->setMaxSize(Vec2f(200, 100));
            PauseButton->setPreferredSize(Vec2f(100, 50));
            PauseButton->setToolTipText("This will Pause the caption!");

            PauseButton->setText("PAUSE");
            PauseButton->setFont(ButtonFont);
            PauseButton->setTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
            PauseButton->setRolloverTextColor(Color4f(1.0, 0.0, 1.0, 1.0));
            PauseButton->setActiveTextColor(Color4f(1.0, 0.0, 0.0, 1.0));
            PauseButton->setAlignment(Vec2f(0.5,0.5));
    endEditCP(PauseButton, Button::MinSizeFieldMask | Button::MaxSizeFieldMask | Button::PreferredSizeFieldMask | Button::ToolTipTextFieldMask | Button::TextFieldMask |
        Button::FontFieldMask | Button::TextColorFieldMask | Button::RolloverTextColorFieldMask | Button::ActiveTextColorFieldMask | Button::AlignmentFieldMask);


    StartButtonActionListener TheStartButtonActionListener;
    StartButton->addActionListener(&TheStartButtonActionListener);

    StopButtonActionListener TheStopButtonActionListener;
    StopButton->addActionListener(&TheStopButtonActionListener);

    PauseButtonActionListener ThePauseButtonActionListener;
    PauseButton->addActionListener(&ThePauseButtonActionListener);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
	
    TutorialWindowEventProducer->openWindow(Pnt2f(50,50),
                                        Vec2f(550,550),
                                        "OpenSG 05Caption Window");
										
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

    
    LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();



    PanelPtr CaptionContainer = osg::Panel::create();

    beginEditCP(CaptionContainer, Panel::PreferredSizeFieldMask | Panel::LayoutFieldMask);
        CaptionContainer->setPreferredSize(Pnt2f(250.0,30.0));
        CaptionContainer->setLayout(MainInternalWindowLayout);
    endEditCP(CaptionContainer, Panel::PreferredSizeFieldMask | Panel::LayoutFieldMask);

    //Initialize the Sound Manager
    SoundManager::the()->attachUpdateProducer(TutorialWindowEventProducer);

    TutorialSound = SoundManager::the()->createSound();
    beginEditCP(TutorialSound, Sound::FileFieldMask | Sound::VolumeFieldMask | Sound::StreamingFieldMask | Sound::LoopingFieldMask);
        TutorialSound->setFile(Path("./Data/captionSoundFile.ogg"));
        TutorialSound->setVolume(1.0);
        TutorialSound->setStreaming(true);
        TutorialSound->setLooping(0);
    endEditCP(TutorialSound, Sound::FileFieldMask | Sound::VolumeFieldMask | Sound::StreamingFieldMask | Sound::LoopingFieldMask);

    // Create the Caption
    TutorialCaption = osg::Caption::create();

    //Add the segments of text to be displayed
    TutorialCaption->captionSegment("Listeners can be used for a variety",1.7,3.4);
    TutorialCaption->captionSegment("of different applications.",3.4,4.7);
    TutorialCaption->captionSegment("In this tutorial we will",5.0,6.35);
    TutorialCaption->captionSegment("simply be changing the background though.",6.35,8.0);
    TutorialCaption->captionSegment("First we will change the",8.8,10.2);
    TutorialCaption->captionSegment("torus on screen to a sphere.",10.2,11.75);
    TutorialCaption->captionSegment("By timing things correctly we can make",12.7,14.6);
    TutorialCaption->captionSegment("the changes right as the word is spoken.",14.6,16.75);
    TutorialCaption->captionSegment("Such as changing the sphere to a cube",17.3,20.0);
    TutorialCaption->captionSegment("but personally I would prefer",20.33,21.65);
    TutorialCaption->captionSegment("the background to be blank.",21.65,22.8);
    TutorialCaption->captionSegment("Much better!",23.8,25.0);


    //Add the tutorial Caption Listener to the Caption that was set up for the tutorial
    TutorialCaptionListener TheCaptionListener;
    TutorialCaption->addCaptionListener(&TheCaptionListener);

    //Create the Caption component Generator
    TutorialCapGen = DefaultCaptionComponentGenerator::create();

    TutorialCaption->attachWindowEventProducer(TutorialWindowEventProducer);
    beginEditCP(TutorialCaption, Caption::ParentContainerFieldMask | Caption::ComponentGeneratorFieldMask | Caption::CaptionDialogSoundFieldMask);
        TutorialCaption->setParentContainer(CaptionContainer);
        TutorialCaption->setComponentGenerator(TutorialCapGen);
        TutorialCaption->setCaptionDialogSound(TutorialSound);
    endEditCP(TutorialCaption, Caption::ParentContainerFieldMask | Caption::ComponentGeneratorFieldMask | Caption::CaptionDialogSoundFieldMask);


    //Create and modify the Label prototype that will be used for the caption
    LabelPtr LabelPrototype = Label::create();
    LabelPrototype->setAlignment(Pnt2f(0.5f,0.5f));
    LabelPrototype->setPreferredSize(Pnt2f(250.0,30.0));

    //Add the prototype to the Generator for use
    beginEditCP(TutorialCapGen, DefaultCaptionComponentGenerator::CaptionSegmentPrototypeFieldMask);
        TutorialCapGen->setCaptionSegmentPrototype(LabelPrototype);
    endEditCP(TutorialCapGen, DefaultCaptionComponentGenerator::CaptionSegmentPrototypeFieldMask);
    
    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
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
	   MainInternalWindow->getChildren().push_back(CaptionContainer);
	   MainInternalWindow->getChildren().push_back(StartButton);
	   MainInternalWindow->getChildren().push_back(StopButton);
       MainInternalWindow->getChildren().push_back(PauseButton);
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

    mgr->setRoot(scene);

    // Add the UI Foreground Object to the Scene
    ViewportPtr TutorialViewport = mgr->getWindow()->getPort(0);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);
        TutorialViewport->getForegrounds().push_back(TutorialUIForeground);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);

    // Show the whole Scene
    mgr->showAll();
    SoundManager::the()->setCamera(mgr->getCamera());


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
