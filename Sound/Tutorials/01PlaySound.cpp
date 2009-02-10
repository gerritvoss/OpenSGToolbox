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
#include <OpenSG/Sound/OSGDialogCoordinator.h>

//metablast sound definition header file
#include "metablast.h"

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


//global variables
NodePtr root;
NodePtr planet;
NodePtr moon;
	
NodePtr rootTransformNode;
NodePtr planetTransformNode;
NodePtr moonTransformNode;

TransformPtr rootTransform;
TransformPtr planetTransform;
TransformPtr moonTransform;

Matrix l,m,n;
Quaternion p, q;

SoundManagerPtr soundManager;
DialogCoordinatorPtr coor;
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
	void soundEnded(const SoundEvent& e){
		printf("Sound stopped\n");
	}
	
};


NodePtr setupScene(){
	root = makeSphere(3, 6);
	planet = makeSphere(3, 3);
    moon = makeSphere(2,1);
	
	rootTransformNode = Node::create();
    planetTransformNode = Node::create();
    moonTransformNode = Node::create();

	rootTransform = Transform::create();
    planetTransform = Transform::create();
    moonTransform = Transform::create();

    
	
	p=Quaternion(Vec3f(0,0,1), PI/2);
	q=Quaternion (Vec3f(0,0,1), 0);
	
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

	return rootTransformNode;
}


void setupSound(){
	//fmod wrapper
	soundManager = FModSoundManager::create();  //create default sound manager
	soundManager->init(".\\","metablast.fev", 64); //initialization, args: media path, media filename, max_channel
	soundManager->setCamera(mgr->getCamera());  //for updating viwer/listener's position, velocity and orientation
	soundManager->setWindowEventProducer(TutorialWindowEventProducer); //for automatic updates


	SoundEmitterPtr clara=SoundEmitter::create(); //sound emitter 1
	SoundEmitterPtr sam=SoundEmitter::create();   //sound emitter 2
	
	clara->attachUpdateListener(TutorialWindowEventProducer);
	sam->attachUpdateListener(TutorialWindowEventProducer);

	//create node for the soundemitter and attach to existing nodes
	NodePtr soundNode1 = Node::create();
	beginEditCP(soundNode1, Node::CoreFieldMask);
		soundNode1->setCore(clara);
	endEditCP(soundNode1, Node::CoreFieldMask);

	NodePtr soundNode2 = Node::create();
	beginEditCP(soundNode2, Node::CoreFieldMask);
		soundNode2->setCore(sam);
	endEditCP(soundNode2, Node::CoreFieldMask);

	beginEditCP(planet, Node::ChildrenFieldMask);
		planet->addChild(soundNode2);
	endEditCP(planet, Node::ChildrenFieldMask);

	beginEditCP(root, Node::ChildrenFieldMask);
		root->addChild(soundNode1);
	endEditCP(root, Node::ChildrenFieldMask);

	//create dialog cooridnator
	coor = DialogCoordinator::create();
	coor->setSoundManager(soundManager);
	coor->addSoundEmitter(clara, 'c', EVENTID_METABLAST_ROOT_DIALOG_CHLOROPLAST_CLARA_1C);
	coor->addSoundEmitter(sam, 's', EVENTID_METABLAST_ROOT_DIALOG_CHLOROPLAST_SAM_2S);
	               //12345678901234567890
	coor->setScript("cscccscscscscscscssc");

	coor->start();
}
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
										
    //setup scene


	mgr->setRoot(setupScene());
	setupSound();

    // Show the whole Scene
    mgr->showAll();

	
	float r = 0;
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
