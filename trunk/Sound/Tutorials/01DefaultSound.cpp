// OpenSG Tutorial Example: Hello World
//
// Minimalistic OpenSG program
// 
// This is the shortest useful OpenSG program 
// (if you remove all the comments ;)
//
// It shows how to use OpenSG together with WIN32 to create a little
// interactive scene viewer.
//

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

//Sound
#include <OpenSG/Sound/OSGSoundManager.h>
#include <OpenSG/Sound/OSGFModSoundManager.h>
#include <OpenSG/Sound/OSGSound.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

WindowEventProducerPtr TheWindowEventProducer;
EventConnection MouseEventConnection;

SoundPtr ZapSound;
SoundPtr MusicSound;

// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

class TutorialSoundListener : public osg::SoundListener
{
    virtual void soundPlayed(const SoundEventPtr e)
    {
        std::cout << "Sound Played" << std::endl;
    }

    virtual void soundStopped(const SoundEventPtr e)
    {
        std::cout << "Sound Channel Stopped" << std::endl;
    }

    virtual void soundPaused(const SoundEventPtr e)
    {
        std::cout << "Sound Channel Paused" << std::endl;
    }

    virtual void soundUnpaused(const SoundEventPtr e)
    {
        std::cout << "Sound Channel Unpaused" << std::endl;
    }

    virtual void soundLooped(const SoundEventPtr e)
    {
        std::cout << "Sound Channel Looped" << std::endl;
    }

    virtual void soundEnded(const SoundEventPtr e)
    {
        std::cout << "Sound Channel Ended" << std::endl;
    }
};

class TutorialMouseMotionListener : public osg::MouseMotionListener
{
    virtual void mouseMoved(const MouseEventPtr e)
    {
    }

    virtual void mouseDragged(const MouseEventPtr e)
    {
    }
};

class TutorialMouseListener : public osg::MouseListener
{
    /*=========================  PUBLIC  ===============================*/
  public:
  
    virtual void mouseClicked(const MouseEventPtr e)
    {
    }
    virtual void mouseEntered(const MouseEventPtr e)
    {
    }
    virtual void mouseExited(const MouseEventPtr e)
    {
    }
    virtual void mousePressed(const MouseEventPtr e)
    {
    }
    virtual void mouseReleased(const MouseEventPtr e)
    {
    }
};

class TutorialKeyListener : public KeyListener
{
   /*=========================  PUBLIC  ===============================*/
public:

    virtual void keyPressed(const KeyEventPtr e)
    {
    }
    virtual void keyReleased(const KeyEventPtr e)
    {
    }
    virtual void keyTyped(const KeyEventPtr e)
    {
        if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
        {
            TheWindowEventProducer->closeWindow();
        }

        switch(e->getKey())
        {
            case KeyEvent::KEY_M:
                _MusicChannelID = MusicSound->play();
                break;
            case KeyEvent::KEY_P:
                _ZapChannelID = ZapSound->play();
                break;
            case KeyEvent::KEY_SPACE:
                ZapSound->pauseToggle(_ZapChannelID);
                MusicSound->pauseToggle(_MusicChannelID);
                break;
            case KeyEvent::KEY_S:
                ZapSound->stop(_ZapChannelID);
                MusicSound->stop(_MusicChannelID);
                break;
            case KeyEvent::KEY_T:
                std::cout << "Zap Time: " << ZapSound->getTime(_ZapChannelID) << std::endl;
                std::cout << "Music Time: " << MusicSound->getTime(_MusicChannelID) << std::endl;
                break;
        }
    }
protected:
    UInt32 _ZapChannelID;
    UInt32 _MusicChannelID;
};

// Initialize WIN32 & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);
    
    TheWindowEventProducer = createDefaultWindowEventProducer();
    TheWindowEventProducer->initWindow();
    
    TheWindowEventProducer->setDisplayCallback(display);
    TheWindowEventProducer->setReshapeCallback(reshape);

    //Attach Mouse Listener
    TutorialMouseListener TheTutorialMouseListener;
    MouseEventConnection = TheWindowEventProducer->addMouseListener(&TheTutorialMouseListener);
    //Attach Key Listener
    TutorialKeyListener TheTutorialKeyListener;
    TheWindowEventProducer->addKeyListener(&TheTutorialKeyListener);
    //Attach MouseMotion Listener
    TutorialMouseMotionListener TheTutorialMouseMotionListener;
    TheWindowEventProducer->addMouseMotionListener(&TheTutorialMouseMotionListener);
    

    // create the scene
    NodePtr scene = makeTorus(1.0, 2.0, 16, 16);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(TheWindowEventProducer->getWindow() );
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();


    //Initialize the Sound Manager
    SoundManager::the()->attachUpdateProducer(TheWindowEventProducer);
    SoundManager::the()->setCamera(mgr->getCamera());

    ZapSound = SoundManager::the()->createSound();
    beginEditCP(ZapSound, Sound::FileFieldMask | Sound::VolumeFieldMask | Sound::StreamingFieldMask | Sound::LoopingFieldMask);
        ZapSound->setFile(Path("./Data/zap.wav"));
        ZapSound->setVolume(1.0);
        ZapSound->setStreaming(false);
        ZapSound->setLooping(1);
    endEditCP(ZapSound, Sound::FileFieldMask | Sound::VolumeFieldMask | Sound::StreamingFieldMask | Sound::LoopingFieldMask);

    MusicSound = SoundManager::the()->createSound();
    beginEditCP(MusicSound, Sound::FileFieldMask | Sound::VolumeFieldMask | Sound::StreamingFieldMask | Sound::LoopingFieldMask);
        MusicSound->setFile(Path("./Data/Chloroplast Theme.ogg"));
        MusicSound->setVolume(1.0);
        MusicSound->setStreaming(true);
        MusicSound->setLooping(-1);
    endEditCP(MusicSound, Sound::FileFieldMask | Sound::VolumeFieldMask | Sound::StreamingFieldMask | Sound::LoopingFieldMask);
    
    TutorialSoundListener TheSoundListerner;
    ZapSound->addSoundListener(&TheSoundListerner);
    MusicSound->addSoundListener(&TheSoundListerner);


    Vec2f WinSize(TheWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TheWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TheWindowEventProducer->openWindow(WinPos,
            WinSize,
            "01 DefaultSound Window");

    //Enter main loop
    TheWindowEventProducer->mainLoop();

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
void reshape(Vec2f Size)
{
    mgr->resize(Size.x(), Size.y());
}


