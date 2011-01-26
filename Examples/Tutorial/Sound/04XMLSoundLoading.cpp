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

#include "OSGFCFileHandler.h"
#include "OSGFieldContainerUtils.h"

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

std::vector<SoundUnrecPtr> Sounds;
std::vector<SoundGroupUnrecPtr> SoundGroups;

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

void keyTyped(KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_Q &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
    switch(details->getKey())
    {
        case KeyEventDetails::KEY_1:
        case KeyEventDetails::KEY_2:
        case KeyEventDetails::KEY_3:
        case KeyEventDetails::KEY_4:
        case KeyEventDetails::KEY_5:
        case KeyEventDetails::KEY_6:
        case KeyEventDetails::KEY_7:
        case KeyEventDetails::KEY_8:
        case KeyEventDetails::KEY_9:
            {
                UInt8 Index(details->getKeyChar() - '1');
                if(Index < Sounds.size())
                {
                    Sounds[Index]->play();
                }
            }
            break;
        case KeyEventDetails::KEY_P:
            SoundGroups[0]->pause();
            break;
        case KeyEventDetails::KEY_U:
            SoundGroups[0]->unpause();
            break;
        case KeyEventDetails::KEY_MINUS:
            {
                Real32 Volume(SoundGroups[0]->getVolume());
                Volume -= 0.1;
                if(Volume < 0.0) Volume = 0.0;
                SoundGroups[0]->setVolume(Volume);
            }
            break;
        case KeyEventDetails::KEY_EQUALS:
            {
                Real32 Volume(SoundGroups[0]->getVolume());
                Volume += 0.1;
                if(Volume > 1.0) Volume = 1.0;
                SoundGroups[0]->setVolume(Volume);
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
        << "1-9     Play Sounds 1-9" << std::endl
        << "p       Pause Sounds" << std::endl
        << "u       Unpause Sounds" << std::endl
        << "-       Decrease Sound Group Volume" << std::endl
        << "=       Increase Sound Group Volume" << std::endl
        << "CTRL-Q  Exit\n\n" << std::endl;

    preloadSharedObject("OSGTBFileIO");

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
        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1));

        // create the scene
        NodeUnrecPtr scene = makeTorus(1.0, 2.0, 16, 16);
        sceneManager.setRoot  (scene);

        // show the whole scene
        sceneManager.showAll();

        //Load Sound Definitions
        FCFileType::FCPtrStore NewContainers;
        NewContainers = FCFileHandler::the()->read(BoostPath("Data/04SoundData.xml"));

        FCFileType::FCPtrStore::iterator Itor;
        for(Itor = NewContainers.begin() ; Itor != NewContainers.end() ; ++Itor)
        {
            //Get Sounds
            if( (*Itor)->getType().isDerivedFrom(Sound::getClassType()))
            {
                Sounds.push_back(dynamic_pointer_cast<Sound>(*Itor));
                Sounds.back()->connectSoundPlayed  (boost::bind(handleSoundPlayed,   _1));
                Sounds.back()->connectSoundStopped (boost::bind(handleSoundStopped,  _1));
                Sounds.back()->connectSoundPaused  (boost::bind(handleSoundPaused,   _1));
                Sounds.back()->connectSoundUnpaused(boost::bind(handleSoundUnpaused, _1));
                Sounds.back()->connectSoundLooped  (boost::bind(handleSoundLooped,   _1));
            }
            //Get Sound Groups
            if( (*Itor)->getType().isDerivedFrom(SoundGroup::getClassType()))
            {
                SoundGroups.push_back(dynamic_pointer_cast<SoundGroup>(*Itor));
            }
        }

        //Initialize the Sound Manager
        SoundManager::the()->attachUpdateProducer(TutorialWindow);
        SoundManager::the()->setCamera(sceneManager.getCamera());

        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "04 XML Sound Loading Window");

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


