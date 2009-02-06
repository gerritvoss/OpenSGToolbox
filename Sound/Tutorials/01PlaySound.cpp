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
#include <OpenSG/OSGViewport.h>

//fmod wrapper
#include <OpenSG/Sound/OSGFModSoundManager.h>
#include <OpenSG/Sound/OSGFModSound.h>
#include <OpenSG/Sound/OSGSoundEmitter.h>

#include <OpenSG/Sound/OSGSoundListener.h>

#define PI 3.1415926
// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;

bool ExitApp = false;
bool pauseSound;
SoundPtr sound, sound2, sound3;
float rpm; //sound parameter
float volume = 1;

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

	   if(e.getKey() == KeyEvent::KEY_P)
       {
		   if (!pauseSound){
				pauseSound = true;
				sound->stop();
		   } else {
				pauseSound = false;
				sound->play();
		   }
       }

	   if(e.getKey() == KeyEvent::KEY_A)
       {
		   rpm+=.01;
		   if (rpm > 1)
			   rpm = 1;
		   sound->setParameter(0, rpm);
       }

	   if(e.getKey() == KeyEvent::KEY_Z)
       {
		   rpm-=.01;
		   if (rpm < 0)
			   rpm = 0;
		   sound->setParameter(0, rpm);
       }

	   if(e.getKey() == KeyEvent::KEY_S)
       {
		   volume+=.01;
		   if (volume > 1)
			   volume = 1;
		   sound->setVolume(volume);
       }
	
	   if(e.getKey() == KeyEvent::KEY_X)
       {
		   volume-=.01;
		   if (volume < 0)
			   volume = 0;
		   sound->setVolume(volume);
       }

	   if(e.getKey() == KeyEvent::KEY_D)
       {
		  
		   sound2->play();
       }

	   if(e.getKey() == KeyEvent::KEY_C)
       {
		  
		   sound3->play();
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

    /******************************************************

             Create ActionListeners to let the 
			 Mouse change viewing angle and move
			 UIRectangle around.

    ******************************************************/

class TutorialMouseListener : public MouseListener
{
  public:
    virtual void mouseClicked(const MouseEvent& e)
    {
    }
    virtual void mouseEntered(const MouseEvent& e)
    {
    }
    virtual void mouseExited(const MouseEvent& e)
    {
    }
    virtual void mousePressed(const MouseEvent& e)
    {
            mgr->mouseButtonPress(e.getButton(), e.getLocation().x(), e.getLocation().y());
    }
    virtual void mouseReleased(const MouseEvent& e)
    {
           mgr->mouseButtonRelease(e.getButton(), e.getLocation().x(), e.getLocation().y());
    }
};

class TutorialMouseMotionListener : public MouseMotionListener
{
  public:
    virtual void mouseMoved(const MouseEvent& e)
    {
            mgr->mouseMove(e.getLocation().x(), e.getLocation().y());
    }

    virtual void mouseDragged(const MouseEvent& e)
    {
            mgr->mouseMove(e.getLocation().x(), e.getLocation().y());
    }
};

class TutorialSoundEventListener : public SoundListener{
	void soundPlayed(const SoundEvent& e){
		printf("Sound played\n");
	}
	void soundStopped(const SoundEvent& e){
		printf("Sound stopped\n");
	}
	
};


int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

	beginEditCP(TutorialWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);
		TutorialWindowEventProducer->setUseCallbackForDraw(true);
		TutorialWindowEventProducer->setUseCallbackForReshape(true);
	endEditCP(TutorialWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);

    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialMouseListener TheTutorialMouseListener;
    TutorialMouseMotionListener TheTutorialMouseMotionListener;
    TutorialWindowEventProducer->addMouseListener(&TheTutorialMouseListener);
    TutorialWindowEventProducer->addMouseMotionListener(&TheTutorialMouseMotionListener);

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
#if 0
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);
    mgr->setRoot(TorusGeometryNode);

#else
	NodePtr root = makeSphere(3, 6);
	NodePtr planet = makeSphere(3, 3);
    NodePtr moon = makeSphere(2,1);
	
	NodePtr rootTransformNode = Node::create();
    NodePtr planetTransformNode = Node::create();
    NodePtr moonTransformNode = Node::create();

	TransformPtr rootTransform = Transform::create();
    TransformPtr planetTransform = Transform::create();
    TransformPtr moonTransform = Transform::create();

    Matrix l,m,n;
	Quaternion p(Vec3f(0,0,1), PI/2), q(Vec3f(0,0,1), 0);
	
	l.setIdentity();
	m.setIdentity();
	m.setTranslate(Vec3f(0, 20, 0));

    n.setIdentity();
	n.setTranslate(Vec3f(0, 8, 0));

	
	beginEditCP(rootTransform, Transform::MatrixFieldMask);

        rootTransform->setMatrix(l);

    endEditCP(rootTransform, Transform::MatrixFieldMask);


    beginEditCP(planetTransform, Transform::MatrixFieldMask);

        planetTransform->setMatrix(m);

    endEditCP(planetTransform, Transform::MatrixFieldMask);
	

    beginEditCP(moonTransform, Transform::MatrixFieldMask);

        moonTransform->setMatrix(n);

    endEditCP(moonTransform, Transform::MatrixFieldMask);

	

    //Insert the cores into the apropiate nodes and add the geometry

	beginEditCP(rootTransformNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

        rootTransformNode->setCore(rootTransform);

        rootTransformNode->addChild(root);

    endEditCP(planetTransformNode, Node::CoreFieldMask | Node::ChildrenFieldMask);


    beginEditCP(planetTransformNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

        planetTransformNode->setCore(planetTransform);

        planetTransformNode->addChild(planet);

    endEditCP(planetTransformNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

	

    beginEditCP(moonTransformNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

        moonTransformNode->setCore(moonTransform);

		moonTransformNode->addChild(moon);

    endEditCP(moonTransformNode, Node::CoreFieldMask | Node::ChildrenFieldMask);


    //add the planet to the sun
	beginEditCP(root, Node::ChildrenFieldMask | Node::CoreFieldMask);

        root->addChild(planetTransformNode);

    endEditCP(rootTransform, Node::ChildrenFieldMask);
	

    //add the moon to the planet
    beginEditCP(planet, Node::ChildrenFieldMask);

        planet->addChild(moonTransformNode);

    endEditCP(planet, Node::ChildrenFieldMask);

	mgr->setRoot(rootTransformNode);
#endif

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
	sound = soundManager->getSound(0);
	sound2 = soundManager->getSound(0);
	sound3 = soundManager->getSound(2);
	
#if 0
	Pnt3f position(0, 0, 0);
	Vec3f velocity(0, 0, 0);
	Vec3f foward(0, 0, -1);
	Vec3f up(0, 1, 0);
	
	soundManager->setListenerProperties(position, velocity, foward, up);
	//FModSoundPtr fmodSound = (FModSoundPtr)sound;
	
	Pnt3f pos(10, 0, 0);
	
	sound->setVelocity(velocity);
	sound->setPosition(pos);
#endif
	sound->play();
	
	TutorialSoundEventListener* soundListener = new TutorialSoundEventListener();
	sound2->addSoundListener(soundListener);
	SoundEmitterPtr soundEmitter = SoundEmitter::create();
	beginEditCP(soundEmitter, SoundEmitter::SoundFieldMask);
		soundEmitter->setSound(sound);
	endEditCP(soundEmitter, SoundEmitter::SoundFieldMask);

	soundEmitter->attachUpdateListener(TutorialWindowEventProducer);
	//soundManager->setWindowEventProducer(TutorialWindowEventProducer);
	CameraPtr cam = mgr->getCamera();

	
	NodePtr soundNode = Node::create();
	beginEditCP(soundNode, Node::CoreFieldMask);
		soundNode->setCore(soundEmitter);
	endEditCP(soundNode, Node::CoreFieldMask);

	//NodePtr soundNode = soundManager->getSoundNode(0);
	beginEditCP(planet, Node::ChildrenFieldMask);
		planet->addChild(soundNode);
	endEditCP(planet, Node::ChildrenFieldMask);

#if 1
	SoundEmitterPtr soundEmitter2 = SoundEmitter::create();
	beginEditCP(soundEmitter2, SoundEmitter::SoundFieldMask);
		soundEmitter2->setSound(sound2);
	endEditCP(soundEmitter2, SoundEmitter::SoundFieldMask);

	soundEmitter2->attachUpdateListener(TutorialWindowEventProducer);
	
	NodePtr soundNode2 = Node::create();
	beginEditCP(soundNode2, Node::CoreFieldMask);
		soundNode2->setCore(soundEmitter2);
	endEditCP(soundNode2, Node::CoreFieldMask);

	beginEditCP(moon, Node::ChildrenFieldMask);
		moon->addChild(soundNode2);
	endEditCP(moon, Node::ChildrenFieldMask);
#endif

	SoundEmitterPtr soundEmitter3 = SoundEmitter::create();
	beginEditCP(soundEmitter3, SoundEmitter::SoundFieldMask);
		soundEmitter3->setSound(sound3);
	endEditCP(soundEmitter3, SoundEmitter::SoundFieldMask);

	soundEmitter3->attachUpdateListener(TutorialWindowEventProducer);
	
	NodePtr soundNode3 = Node::create();
	beginEditCP(soundNode3, Node::CoreFieldMask);
		soundNode3->setCore(soundEmitter3);
	endEditCP(soundNode3, Node::CoreFieldMask);

	beginEditCP(root, Node::ChildrenFieldMask);
		moon->addChild(soundNode3);
	endEditCP(root, Node::ChildrenFieldMask);
#endif
	float r = 0;
	soundManager->setCamera(mgr->getCamera());
    while(!ExitApp)
    {
		r += PI/200; //rotation speed
		if (r>PI *2) r = 0;

		beginEditCP(planetTransform, Transform::MatrixFieldMask);
			q.setValueAsAxisRad(Vec3f(0,0,1), r * 2);
			m.setRotate(q);
			planetTransform->setMatrix(m);
		endEditCP(planetTransform, Transform::MatrixFieldMask);

		beginEditCP(rootTransform, Transform::MatrixFieldMask);
			p.setValueAsAxisRad(Vec3f(0,0,1), r);
			n.setRotate(p);
			rootTransform->setMatrix(n);
		endEditCP(rootTransform, Transform::MatrixFieldMask);
		
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
