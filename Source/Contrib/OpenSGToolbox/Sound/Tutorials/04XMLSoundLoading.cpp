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

#include <OpenSG/Toolbox/OSGFCFileHandler.h>
#include <OpenSG/Toolbox/OSGFieldContainerUtils.h>

//Input
#include <OpenSG/Input/OSGWindowUtils.h>

//Sound
#include <OpenSG/Sound/OSGSoundManager.h>
#include <OpenSG/Sound/OSGSound.h>
#include <OpenSG/Sound/OSGSoundGroup.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

WindowEventProducerPtr TheWindowEventProducer;
EventConnection MouseEventConnection;

std::vector<SoundPtr> Sounds;
std::vector<SoundGroupPtr> SoundGroups;

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
       case KeyEvent::KEY_1:
       case KeyEvent::KEY_2:
       case KeyEvent::KEY_3:
       case KeyEvent::KEY_4:
       case KeyEvent::KEY_5:
       case KeyEvent::KEY_6:
       case KeyEvent::KEY_7:
       case KeyEvent::KEY_8:
       case KeyEvent::KEY_9:
           {
               UInt8 Index(e->getKeyChar() - '1');
               if(Index < Sounds.size())
               {
                   Sounds[Index]->play();
               }
           }
           break;
       case KeyEvent::KEY_P:
           SoundGroups[0]->pause();
           break;
       case KeyEvent::KEY_U:
           SoundGroups[0]->unpause();
           break;
       case KeyEvent::KEY_MINUS:
           {
                Real32 Volume(SoundGroups[0]->getVolume());
                Volume -= 0.1;
                if(Volume < 0.0) Volume = 0.0;
                SoundGroups[0]->setVolume(Volume);
           }
           break;
       case KeyEvent::KEY_EQUALS:
           {
                Real32 Volume(SoundGroups[0]->getVolume());
                Volume += 0.1;
                if(Volume > 1.0) Volume = 1.0;
                SoundGroups[0]->setVolume(Volume);
           }
           break;
       }
    }
protected:
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

    //Load Sound Definitions
	FCFileType::FCPtrStore NewContainers;
    NewContainers = FCFileHandler::the()->read(Path("Data/04SoundData.xml"));

    FCFileType::FCPtrStore::iterator Itor;
    TutorialSoundListener TheSoundListerner;
    for(Itor = NewContainers.begin() ; Itor != NewContainers.end() ; ++Itor)
    {
        //Get Sounds
        if( (*Itor)->getType().isDerivedFrom(Sound::getClassType()))
        {
            Sounds.push_back(SoundPtr::dcast(*Itor));
            SoundPtr::dcast(*Itor)->addSoundListener(&TheSoundListerner);
            addRefCP(*Itor);
        }
        //Get Sound Groups
        if( (*Itor)->getType().isDerivedFrom(SoundGroup::getClassType()))
        {
            SoundGroups.push_back(SoundGroupPtr::dcast(*Itor));
            addRefCP(*Itor);
        }
    }

    //Initialize the Sound Manager
    SoundManager::the()->attachUpdateProducer(TheWindowEventProducer);
    SoundManager::the()->setCamera(mgr->getCamera());

    Vec2f WinSize(TheWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TheWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TheWindowEventProducer->openWindow(WinPos,
            WinSize,
            "04 XML Sound Loading Window");

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


