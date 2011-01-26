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
// with , but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

void handleSoundPlayed(SoundEventDetails* const details)
{
    std::cout << "Sound Played" << std::endl;
}

void handleSoundStopped(SoundEventDetails* const details)
{
    std::cout << "Sound Channel Stopped" << std::endl;
}

void handleSoundPaused(SoundEventDetails* const details)
{
    std::cout << "Sound Channel Paused" << std::endl;
}

void handleSoundUnpaused(SoundEventDetails* const details)
{
    std::cout << "Sound Channel Unpaused" << std::endl;
}

void handleSoundLooped(SoundEventDetails* const details)
{
    std::cout << "Sound Channel Looped" << std::endl;
}


void keyTyped(KeyEventDetails* const details,
              Sound* const ZapSound,
              Sound* const ClickSound,
              Sound* const PopSound,
              SoundGroup* const EffectsGroup
             )
{
    if(details->getKey() == KeyEventDetails::KEY_Q &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }

    switch(details->getKey())
    {
        case KeyEventDetails::KEY_1:
            PopSound->play();
            break;
        case KeyEventDetails::KEY_2:
            ClickSound->play();
            break;
        case KeyEventDetails::KEY_3:
            ZapSound->play();
            break;
        case KeyEventDetails::KEY_P:
            EffectsGroup->pause();
            break;
        case KeyEventDetails::KEY_U:
            EffectsGroup->unpause();
            break;
        case KeyEventDetails::KEY_MINUS:
            {
                Real32 Volume(EffectsGroup->getVolume());
                Volume -= 0.1;
                if(Volume < 0.0) Volume = 0.0;
                EffectsGroup->setVolume(Volume);
            }
            break;
        case KeyEventDetails::KEY_EQUALS:
            {
                Real32 Volume(EffectsGroup->getVolume());
                Volume += 0.1;
                if(Volume > 1.0) Volume = 1.0;
                EffectsGroup->setVolume(Volume);
            }
            break;
    }
}

void mousePressed(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    mgr->mouseButtonPress(details->getButton(), details->getLocation().x(), details->getLocation().y());
}
void mouseReleased(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    mgr->mouseButtonRelease(details->getButton(), details->getLocation().x(), details->getLocation().y());
}

void mouseMoved(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    mgr->mouseMove(details->getLocation().x(), details->getLocation().y());
}

void mouseDragged(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    mgr->mouseMove(details->getLocation().x(), details->getLocation().y());
}

void mouseWheelMoved(MouseWheelEventDetails* const details, SimpleSceneManager *mgr)
{
    if(details->getUnitsToScroll() > 0)
    {
        for(UInt32 i(0) ; i<details->getUnitsToScroll() ;++i)
        {
            mgr->mouseButtonPress(Navigator::DOWN_MOUSE,details->getLocation().x(),details->getLocation().y());
            mgr->mouseButtonRelease(Navigator::DOWN_MOUSE,details->getLocation().x(),details->getLocation().y());
        }
    }
    else if(details->getUnitsToScroll() < 0)
    {
        for(UInt32 i(0) ; i<abs(details->getUnitsToScroll()) ;++i)
        {
            mgr->mouseButtonPress(Navigator::UP_MOUSE,details->getLocation().x(),details->getLocation().y());
            mgr->mouseButtonRelease(Navigator::UP_MOUSE,details->getLocation().x(),details->getLocation().y());
        }
    }
}


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


    {
        // Set up Window
        WindowEventProducerRecPtr TutorialWindow = createNativeWindow();
        TutorialWindow->initWindow();

        // Create the SimpleSceneManager helper
        SimpleSceneManager sceneManager;
        TutorialWindow->setDisplayCallback(boost::bind(display, &sceneManager));
        TutorialWindow->setReshapeCallback(boost::bind(reshape, _1, &sceneManager));

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

        //Attach to events
        TutorialWindow->connectMousePressed(boost::bind(mousePressed, _1, &sceneManager));
        TutorialWindow->connectMouseReleased(boost::bind(mouseReleased, _1, &sceneManager));
        TutorialWindow->connectMouseMoved(boost::bind(mouseMoved, _1, &sceneManager));
        TutorialWindow->connectMouseDragged(boost::bind(mouseDragged, _1, &sceneManager));
        TutorialWindow->connectMouseWheelMoved(boost::bind(mouseWheelMoved, _1, &sceneManager));

        // create the scene
        NodeUnrecPtr scene = makeTorus(1.0, 2.0, 16, 16);

        sceneManager.setRoot  (scene);

        // show the whole scene
        sceneManager.showAll();


        //Initialize the Sound Manager
        SoundManager::the()->attachUpdateProducer(TutorialWindow);
        SoundManager::the()->setCamera(sceneManager.getCamera());

        SoundRecPtr ZapSound = SoundManager::the()->createSound();
        ZapSound->setFile(BoostPath("./Data/zap.wav"));
        ZapSound->setVolume(1.0);
        ZapSound->setStreaming(false);
        ZapSound->setLooping(1);

        SoundRecPtr ClickSound = SoundManager::the()->createSound();
        ClickSound->setFile(BoostPath("./Data/click.wav"));
        ClickSound->setVolume(1.0);
        ClickSound->setStreaming(false);
        ClickSound->setLooping(1);

        SoundRecPtr PopSound = SoundManager::the()->createSound();
        PopSound->setFile(BoostPath("./Data/pop.wav"));
        PopSound->setVolume(1.0);
        PopSound->setStreaming(false);
        PopSound->setLooping(1);

        SoundGroupRecPtr EffectsGroup = SoundGroup::create();
        EffectsGroup->pushToSounds(ZapSound);
        EffectsGroup->pushToSounds(ClickSound);
        EffectsGroup->pushToSounds(PopSound);

        ZapSound->connectSoundPlayed  (boost::bind(handleSoundPlayed,   _1));
        ZapSound->connectSoundStopped (boost::bind(handleSoundStopped,  _1));
        ZapSound->connectSoundPaused  (boost::bind(handleSoundPaused,   _1));
        ZapSound->connectSoundUnpaused(boost::bind(handleSoundUnpaused, _1));
        ZapSound->connectSoundLooped  (boost::bind(handleSoundLooped,   _1));

        ClickSound->connectSoundPlayed  (boost::bind(handleSoundPlayed,   _1));
        ClickSound->connectSoundStopped (boost::bind(handleSoundStopped,  _1));
        ClickSound->connectSoundPaused  (boost::bind(handleSoundPaused,   _1));
        ClickSound->connectSoundUnpaused(boost::bind(handleSoundUnpaused, _1));
        ClickSound->connectSoundLooped  (boost::bind(handleSoundLooped,   _1));

        PopSound->connectSoundPlayed  (boost::bind(handleSoundPlayed,   _1));
        PopSound->connectSoundStopped (boost::bind(handleSoundStopped,  _1));
        PopSound->connectSoundPaused  (boost::bind(handleSoundPaused,   _1));
        PopSound->connectSoundUnpaused(boost::bind(handleSoundUnpaused, _1));
        PopSound->connectSoundLooped  (boost::bind(handleSoundLooped,   _1));

        TutorialWindow->connectKeyTyped(boost::bind(&keyTyped,
                                                    _1,
                                                    ZapSound.get(),
                                                    ClickSound.get(),
                                                    PopSound.get(),
                                                    EffectsGroup.get()));


        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "03SoundGroup Window");

        //Enter main loop
        TutorialWindow->mainLoop();

    }
    osgExit();
    return 0;
}

//
// callback functions
//

// redraw the window
void display(SimpleSceneManager *mgr)
{
    mgr->redraw();
}

// react to size changes
void reshape(Vec2f Size, SimpleSceneManager *mgr)
{
    mgr->resize(Size.x(), Size.y());
}


