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
#include "OSGConfig.h"

// Methods to create simple geometry: boxes, spheres, tori etc.
#include "OSGSimpleGeometry.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"

// the general scene file loading handler
#include "OSGSceneFileHandler.h"

//Input
#include "OSGWindowUtils.h"

//Sound
#include "OSGSoundManager.h"
#include "OSGSound.h"
#include "OSGSoundGroup.h"

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

WindowEventProducerUnrecPtr TheWindowEventProducer;
EventConnection MouseEventConnection;

SoundUnrecPtr ZapSound;
SoundUnrecPtr ClickSound;
SoundUnrecPtr PopSound;
SoundGroupUnrecPtr EffectsGroup;

// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

class TutorialSoundListener : public SoundListener
{
    virtual void soundPlayed(const SoundEventUnrecPtr e)
    {
        std::cout << "Sound Played" << std::endl;
    }

    virtual void soundStopped(const SoundEventUnrecPtr e)
    {
        std::cout << "Sound Channel Stopped" << std::endl;
    }

    virtual void soundPaused(const SoundEventUnrecPtr e)
    {
        std::cout << "Sound Channel Paused" << std::endl;
    }

    virtual void soundUnpaused(const SoundEventUnrecPtr e)
    {
        std::cout << "Sound Channel Unpaused" << std::endl;
    }

    virtual void soundLooped(const SoundEventUnrecPtr e)
    {
        std::cout << "Sound Channel Looped" << std::endl;
    }

    virtual void soundEnded(const SoundEventUnrecPtr e)
    {
        std::cout << "Sound Channel Ended" << std::endl;
    }
};

class TutorialMouseMotionListener : public MouseMotionListener
{
    virtual void mouseMoved(const MouseEventUnrecPtr e)
    {
    }

    virtual void mouseDragged(const MouseEventUnrecPtr e)
    {
    }
};

class TutorialMouseListener : public MouseListener
{
    /*=========================  PUBLIC  ===============================*/
  public:
  
    virtual void mouseClicked(const MouseEventUnrecPtr e)
    {
    }
    virtual void mouseEntered(const MouseEventUnrecPtr e)
    {
    }
    virtual void mouseExited(const MouseEventUnrecPtr e)
    {
    }
    virtual void mousePressed(const MouseEventUnrecPtr e)
    {
    }
    virtual void mouseReleased(const MouseEventUnrecPtr e)
    {
    }
};

class TutorialKeyListener : public KeyListener
{
   /*=========================  PUBLIC  ===============================*/
public:

   virtual void keyPressed(const KeyEventUnrecPtr e)
    {
    }
    virtual void keyReleased(const KeyEventUnrecPtr e)
    {
    }
    virtual void keyTyped(const KeyEventUnrecPtr e)
    {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           TheWindowEventProducer->closeWindow();
       }

       switch(e->getKey())
       {
       case KeyEvent::KEY_1:
           PopSound->play();
           break;
       case KeyEvent::KEY_2:
           ClickSound->play();
           break;
       case KeyEvent::KEY_3:
           ZapSound->play();
           break;
       case KeyEvent::KEY_P:
           EffectsGroup->pause();
           break;
       case KeyEvent::KEY_U:
           EffectsGroup->unpause();
           break;
       case KeyEvent::KEY_MINUS:
           {
                Real32 Volume(EffectsGroup->getVolume());
                Volume -= 0.1;
                if(Volume < 0.0) Volume = 0.0;
                EffectsGroup->setVolume(Volume);
           }
           break;
       case KeyEvent::KEY_EQUALS:
           {
                Real32 Volume(EffectsGroup->getVolume());
                Volume += 0.1;
                if(Volume > 1.0) Volume = 1.0;
                EffectsGroup->setVolume(Volume);
           }
           break;
       }
    }
protected:
};

// Initialize WIN32 & OpenSG and set up the scene
int main(int argc, char **argv)
{
    std::cout << "\n\nKEY COMMANDS:" << std::endl
              << "1       Play Pop Sound" << std::endl
              << "2       Play Click Sound" << std::endl
              << "3       Play Zap Sound" << std::endl
              << "p       Pause Sounds" << std::endl
              << "u       Unpause Sounds" << std::endl
              << "-       Decrease Sound Group Volume" << std::endl
              << "=       Increase Sound Group Volume" << std::endl
              << "CTRL-Q  Exit\n\n" << std::endl;

    // OSG init
    osgInit(argc,argv);
    
    TheWindowEventProducer = createNativeWindow();
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
    NodeUnrecPtr scene = makeTorus(1.0, 2.0, 16, 16);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(TheWindowEventProducer );
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();


    //Initialize the Sound Manager
    SoundManager::the()->attachUpdateProducer(TheWindowEventProducer);
    SoundManager::the()->setCamera(mgr->getCamera());

    ZapSound = SoundManager::the()->createSound();
        ZapSound->setFile(Path("./Data/zap.wav"));
        ZapSound->setVolume(1.0);
        ZapSound->setStreaming(false);
        ZapSound->setLooping(1);

    ClickSound = SoundManager::the()->createSound();
        ClickSound->setFile(Path("./Data/click.wav"));
        ClickSound->setVolume(1.0);
        ClickSound->setStreaming(false);
        ClickSound->setLooping(1);

    PopSound = SoundManager::the()->createSound();
        PopSound->setFile(Path("./Data/pop.wav"));
        PopSound->setVolume(1.0);
        PopSound->setStreaming(false);
        PopSound->setLooping(1);

    EffectsGroup = SoundGroup::create();
        EffectsGroup->pushToSounds(ZapSound);
        EffectsGroup->pushToSounds(ClickSound);
        EffectsGroup->pushToSounds(PopSound);
    
    TutorialSoundListener TheSoundListerner;
    ZapSound->addSoundListener(&TheSoundListerner);
    ClickSound->addSoundListener(&TheSoundListerner);
    PopSound->addSoundListener(&TheSoundListerner);


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


