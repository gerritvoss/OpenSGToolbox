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
#include <OpenSG/Input/OSGWindowAdapter.h>

//Sound
#include <OpenSG/Sound/OSGSoundManager.h>
#include <OpenSG/Sound/OSGSound.h>
#include <OpenSG/Sound/OSGSoundEmitter.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

WindowEventProducerPtr TheWindowEventProducer;
EventConnection MouseEventConnection;
TransformPtr TheSphereTransform;

bool ExitMainLoop = false;
SoundPtr PopSound;
SoundEmitterPtr TheEmitter;

// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

class TutorialSoundListener : public osg::SoundListener
{
    virtual void soundPlayed(const SoundEvent& e)
    {
        std::cout << "Sound Played" << std::endl;
    }

    virtual void soundStopped(const SoundEvent& e)
    {
        std::cout << "Sound Channel Stopped" << std::endl;
    }

    virtual void soundPaused(const SoundEvent& e)
    {
        std::cout << "Sound Channel Paused" << std::endl;
    }

    virtual void soundUnpaused(const SoundEvent& e)
    {
        std::cout << "Sound Channel Unpaused" << std::endl;
    }

    virtual void soundLooped(const SoundEvent& e)
    {
        std::cout << "Sound Channel Looped" << std::endl;
    }

    virtual void soundEnded(const SoundEvent& e)
    {
        std::cout << "Sound Channel Ended" << std::endl;
    }
};

class TutorialMouseMotionListener : public osg::MouseMotionListener
{
    virtual void mouseMoved(const MouseEvent& e)
    {
    }

    virtual void mouseDragged(const MouseEvent& e)
    {
    }
};

class TutorialMouseListener : public osg::MouseListener
{
    /*=========================  PUBLIC  ===============================*/
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
    }
    virtual void mouseReleased(const MouseEvent& e)
    {
    }
};

class TutorialKeyListener : public KeyListener
{
   /*=========================  PUBLIC  ===============================*/
public:

   virtual void keyPressed(const KeyEvent& e)
    {
    }
    virtual void keyReleased(const KeyEvent& e)
    {
    }
    virtual void keyTyped(const KeyEvent& e)
    {
       if(e.getKey() == KeyEvent::KEY_Q && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           ExitMainLoop = true;
       }

       switch(e.getKey())
       {
       case KeyEvent::KEY_P:
           TheEmitter->emitSound();
           break;
       }
    }
protected:
    UInt32 _PopChannelID;
};

class TutorialWindowListener : public WindowAdapter
{
    /*=========================  PUBLIC  ===============================*/
  public:

    virtual void windowClosing(const WindowEvent& e)
    {
	   ExitMainLoop = true;
    }

    virtual void windowClosed(const WindowEvent& e)
    {
	   ExitMainLoop = true;
    }
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

    virtual void update(const UpdateEvent& e)
    {
        _TotalTime += e.getElapsedTime();
        Matrix Translate;
        Translate.setTranslate(0.0,0.0,-5.0);
        Matrix Rotation;
        Rotation.setRotate(Quaternion(Vec3f(0.0,1.0,0.0), osgdegree2rad(_TotalTime*80.0)));

        Matrix Total(Rotation);
        Total.mult(Translate);

        beginEditCP(TheSphereTransform,Transform::MatrixFieldMask);
            TheSphereTransform->setMatrix(Total);
        endEditCP(TheSphereTransform,Transform::MatrixFieldMask);
    }
};

// Initialize WIN32 & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);
    
    TheWindowEventProducer = createDefaultWindowEventProducer();
    TheWindowEventProducer->initWindow();
    
	beginEditCP(TheWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);
		TheWindowEventProducer->setUseCallbackForDraw(true);
		TheWindowEventProducer->setUseCallbackForReshape(true);
	endEditCP(TheWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);
    TheWindowEventProducer->setDisplayCallback(display);
    TheWindowEventProducer->setReshapeCallback(reshape);

    //Attach Mouse Listener
    TutorialMouseListener TheTutorialMouseListener;
    MouseEventConnection = TheWindowEventProducer->addMouseListener(&TheTutorialMouseListener);
    //Attach Key Listener
    TutorialKeyListener TheTutorialKeyListener;
    TheWindowEventProducer->addKeyListener(&TheTutorialKeyListener);
    //Attach Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TheWindowEventProducer->addWindowListener(&TheTutorialWindowListener);
    //Attach MouseMotion Listener
    TutorialMouseMotionListener TheTutorialMouseMotionListener;
    TheWindowEventProducer->addMouseMotionListener(&TheTutorialMouseMotionListener);

    TutorialUpdateListener TheUpdateListener;
    TheWindowEventProducer->addUpdateListener(&TheUpdateListener);
    


    //Sound Emitter Node
    TheEmitter = SoundEmitter::create();
    TheEmitter->attachUpdateListener(TheWindowEventProducer);

    NodePtr TheEmitterNode = Node::create();
    beginEditCP(TheEmitterNode,Node::CoreFieldMask);
        TheEmitterNode->setCore(TheEmitter);
    endEditCP(TheEmitterNode,Node::CoreFieldMask);

    //Sphere Transformation Node
    Matrix Translate;
    Translate.setTranslate(0.0,0.0,-5.0);
    Matrix Rotation;
    Rotation.setRotate(Quaternion(Vec3f(0.0,1.0,0.0), 0.0));

    Matrix Total(Translate);
    Total.mult(Rotation);

    TheSphereTransform = Transform::create();
    beginEditCP(TheSphereTransform,Transform::MatrixFieldMask);
        TheSphereTransform->setMatrix(Total);
    endEditCP(TheSphereTransform,Transform::MatrixFieldMask);

    NodePtr SphereTransformNode = Node::create();
    beginEditCP(SphereTransformNode,Node::CoreFieldMask | Node::ChildrenFieldMask);
        SphereTransformNode->setCore(TheSphereTransform);
        SphereTransformNode->addChild(makeSphere(2, 1.0));
        SphereTransformNode->addChild(TheEmitterNode);
    endEditCP(SphereTransformNode,Node::CoreFieldMask | Node::ChildrenFieldMask);

    // create the scene
    NodePtr scene = Node::create();
    beginEditCP(scene,Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(Group::create());
        scene->addChild(SphereTransformNode);
    endEditCP(scene,Node::CoreFieldMask | Node::ChildrenFieldMask);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(TheWindowEventProducer->getWindow() );
    mgr->setRoot  (scene);

    CameraPtr TheCamera = mgr->getCamera();
    beginEditCP(TheCamera, Camera::NearFieldMask | Camera::FarFieldMask);
        TheCamera->setNear(0.1);
        TheCamera->setFar(100.0);
    endEditCP(TheCamera, Camera::NearFieldMask | Camera::FarFieldMask);

    //Initialize the Sound Manager
    SoundManager::the()->init();
    SoundManager::the()->attachUpdateProducer(TheWindowEventProducer);
    SoundManager::the()->setCamera(mgr->getCamera());

    PopSound = SoundManager::the()->createSound();
    beginEditCP(PopSound, Sound::FileFieldMask | Sound::VolumeFieldMask | Sound::StreamingFieldMask | Sound::LoopingFieldMask | Sound::Enable3DFieldMask);
        PopSound->setFile(Path("./Data/pop.wav"));
        PopSound->setVolume(1.0);
        PopSound->setStreaming(false);
        PopSound->setLooping(-1);
        PopSound->setEnable3D(true);
    endEditCP(PopSound, Sound::FileFieldMask | Sound::VolumeFieldMask | Sound::StreamingFieldMask | Sound::LoopingFieldMask | Sound::Enable3DFieldMask);
    
    TutorialSoundListener TheSoundListerner;
    PopSound->addSoundListener(&TheSoundListerner);

    //Attach this sound to the emitter node
    beginEditCP(TheEmitter, SoundEmitter::SoundFieldMask);
        TheEmitter->setSound(PopSound);
    endEditCP(TheEmitter, SoundEmitter::SoundFieldMask);
    


    TheWindowEventProducer->openWindow(Pnt2s(50,50),
                        Vec2s(500,500),
                        "02 Sound3F Window");

    while(!ExitMainLoop)
    {
        TheWindowEventProducer->update();
        TheWindowEventProducer->draw();
    }

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


