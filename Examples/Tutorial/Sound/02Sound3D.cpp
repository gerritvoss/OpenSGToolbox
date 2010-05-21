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
#include "OSGSoundEmitter.h"

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

WindowEventProducerUnrecPtr TheWindowEventProducer;
EventConnection MouseEventConnection;
TransformUnrecPtr TheSphereTransform;

SoundUnrecPtr PopSound;
SoundEmitterUnrecPtr TheEmitter;

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
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
       {
           TheWindowEventProducer->closeWindow();
       }

       switch(e->getKey())
       {
       case KeyEvent::KEY_P:
           TheEmitter->emitSound();
           break;
       }
    }
protected:
    UInt32 _PopChannelID;
};

class TutorialUpdateListener : public UpdateListener
{
    /*=========================  PUBLIC  ===============================*/
protected:
    Real32 _TotalTime;
public:
      TutorialUpdateListener(void) : _TotalTime(0.0)
      {
      }

    virtual void update(const UpdateEventUnrecPtr e)
    {
        _TotalTime += e->getElapsedTime();
        Matrix Translate;
        Translate.setTranslate(0.0,0.0,-5.0);
        Matrix Rotation;
        Rotation.setRotate(Quaternion(Vec3f(0.0,1.0,0.0), osgDegree2Rad(_TotalTime*80.0)));

        Matrix Total(Rotation);
        Total.mult(Translate);

            TheSphereTransform->setMatrix(Total);
    }
};

// Initialize WIN32 & OpenSG and set up the scene
int main(int argc, char **argv)
{
    std::cout << "\n\nKEY COMMANDS:" << std::endl
              << "p       Play Pop Sound" << std::endl
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

    TutorialUpdateListener TheUpdateListener;
    TheWindowEventProducer->addUpdateListener(&TheUpdateListener);
    


    //Sound Emitter Node
    TheEmitter = SoundEmitter::create();
    TheEmitter->attachUpdateListener(TheWindowEventProducer);

    NodeUnrecPtr TheEmitterNode = Node::create();
        TheEmitterNode->setCore(TheEmitter);

    //Sphere Transformation Node
    Matrix Translate;
    Translate.setTranslate(0.0,0.0,-5.0);
    Matrix Rotation;
    Rotation.setRotate(Quaternion(Vec3f(0.0,1.0,0.0), 0.0));

    Matrix Total(Translate);
    Total.mult(Rotation);

    TheSphereTransform = Transform::create();
        TheSphereTransform->setMatrix(Total);

    NodeUnrecPtr SphereTransformNode = Node::create();
        SphereTransformNode->setCore(TheSphereTransform);
        SphereTransformNode->addChild(makeSphere(2, 1.0));
        SphereTransformNode->addChild(TheEmitterNode);

    // create the scene
    NodeUnrecPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(SphereTransformNode);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(TheWindowEventProducer );
    mgr->setRoot  (scene);

    CameraUnrecPtr TheCamera = mgr->getCamera();
        TheCamera->setNear(0.1);
        TheCamera->setFar(100.0);

    //Initialize the Sound Manager
    SoundManager::the()->attachUpdateProducer(TheWindowEventProducer);
    SoundManager::the()->setCamera(mgr->getCamera());

    PopSound = SoundManager::the()->createSound();
        PopSound->setFile(BoostPath("./Data/pop.wav"));
        PopSound->setVolume(1.0);
        PopSound->setStreaming(false);
        PopSound->setLooping(-1);
        PopSound->setEnable3D(true);
    
    TutorialSoundListener TheSoundListerner;
    PopSound->addSoundListener(&TheSoundListerner);

    //Attach this sound to the emitter node
        TheEmitter->setSound(PopSound);
    


    Vec2f WinSize(TheWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TheWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TheWindowEventProducer->openWindow(WinPos,
            WinSize,
            "02 Sound3D Window");


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


