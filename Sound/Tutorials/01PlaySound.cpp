/*************************************************
Welcome to the Playsound tutorial.  This Tutorial
is simply a test of the Mini Map at it's current state.
Once the Mini Map section of the game library has been
completed this tutorial will also be furnished with 
helpful tips and incites into the workings of MiniMap

*************************************************/

#define DISTANCEFACTOR 1.0f

// GLUT is used for window handling
#include <OpenSG/OSGGLUT.h>

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

//fmod wrapper
#include <OpenSG/Sound/OSGFModSoundManager.h>
#include <OpenSG/Sound/OSGFModSound.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

bool ExitApp = false;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

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

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
	
    TutorialWindowEventProducer->openWindow(Pnt2f(50,50),
                                        Vec2f(550,550),
                                        "OpenSG 01PlaySound Window");
										
    // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    mgr->setRoot(TorusGeometryNode);

    // Show the whole Scene
    mgr->showAll();
/*
	*/
	
#if 0
	FMOD_EVENTSYSTEM  *eventsystem;
    FMOD_EVENT        *event;
    FMOD_RESULT        result;
    //int                key;
	result = FMOD_EventSystem_Create(&eventsystem);
    result = FMOD_EventSystem_Init(eventsystem, 64, FMOD_INIT_NORMAL, 0, FMOD_EVENT_INIT_NORMAL);
    result = FMOD_EventSystem_SetMediaPath(eventsystem, ".\\");
    result = FMOD_EventSystem_Load(eventsystem, "test.fev", 0, 0);
    result = FMOD_EventSystem_GetEventBySystemID(eventsystem, 0, FMOD_EVENT_DEFAULT, &event);
	{
	FMOD_EventSystem_Set3DNumListeners(eventsystem, 1);
	FMOD_VECTOR *pos = new FMOD_VECTOR();
	FMOD_VECTOR *vel = new FMOD_VECTOR();
	FMOD_VECTOR *frwrd = new FMOD_VECTOR();
	FMOD_VECTOR *up = new FMOD_VECTOR();
	
	frwrd->x = 0;frwrd->y = 0;frwrd->z = -1;
	up->x = 0;up->y = 1;up->z = 0;

	FMOD_EventSystem_Set3DListenerAttributes(eventsystem, 0, pos,  vel, frwrd, up);
	}
	{
	FMOD_VECTOR *pos = new FMOD_VECTOR();
	FMOD_VECTOR *vel = new FMOD_VECTOR();
	pos->x = 10;pos->y = 0;pos->z = -1;
	
	FMOD_Event_Set3DAttributes(event, pos, vel, 0);
	}


	//result = FMOD_System_Set3DSettings(eventsystem, 1.0, DISTANCEFACTOR, 1.0f);
	FMOD_Event_Start(event);
#else
	//fmod wrapper
	SoundManagerPtr soundManager = FModSoundManager::create();
	//initialization, args: media path, media filename, max_channel
	soundManager->init(".\\","test.fev", 64);
	SoundPtr sound = soundManager->getSound(0);
	
	Pnt3f position(0, 0, 0);
	Vec3f velocity(0, 0, 0);
	Vec3f foward(0, 0, -1);
	Vec3f up(0, 1, 0);
	
	soundManager->setListenerProperties(position, velocity, foward, up);
	//FModSoundPtr fmodSound = (FModSoundPtr)sound;
	
	Pnt3f pos(10, 0, 0);
	
	sound->setVelocity(velocity);
	sound->play();
	sound->setPosition(pos);
#endif

    while(!ExitApp)
    {
        TutorialWindowEventProducer->update();
        TutorialWindowEventProducer->draw();
		soundManager->update(0);
		
    }
	sound->stop();
	//FMOD_Event_Stop(event, 1);
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
