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

void handleUpdate(UpdateEventDetails* const details,
                  Transform* const TheSphereTransform)
{
    static Real32 _TotalTime(0.0f);
    _TotalTime += details->getElapsedTime();

    Matrix Translate;
    Translate.setTranslate(0.0,0.0,-5.0);
    Matrix Rotation;
    Rotation.setRotate(Quaternion(Vec3f(0.0,1.0,0.0), osgDegree2Rad(_TotalTime*80.0)));

    Matrix Total(Rotation);
    Total.mult(Translate);

    TheSphereTransform->setMatrix(Total);
}

void keyTyped(KeyEventDetails* const details,
              SoundEmitter* const TheEmitter)
{
    if(details->getKey() == KeyEventDetails::KEY_Q &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
    switch(details->getKey())
    {
        case KeyEventDetails::KEY_P:
            TheEmitter->emitSound();
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
              << "p       Play Pop Sound" << std::endl
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

        //Sound Emitter Node
        SoundEmitterRecPtr TheEmitter = SoundEmitter::create();
        TheEmitter->attachUpdateProducer(TutorialWindow);

        NodeUnrecPtr TheEmitterNode = Node::create();
        TheEmitterNode->setCore(TheEmitter);

        //Sphere Transformation Node
        Matrix Translate;
        Translate.setTranslate(0.0,0.0,-5.0);
        Matrix Rotation;
        Rotation.setRotate(Quaternion(Vec3f(0.0,1.0,0.0), 0.0));

        Matrix Total(Translate);
        Total.mult(Rotation);

        TransformRecPtr TheSphereTransform = Transform::create();
        TheSphereTransform->setMatrix(Total);

        NodeUnrecPtr SphereTransformNode = Node::create();
        SphereTransformNode->setCore(TheSphereTransform);
        SphereTransformNode->addChild(makeSphere(2, 1.0));
        SphereTransformNode->addChild(TheEmitterNode);

        // create the scene
        NodeUnrecPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(SphereTransformNode);

        // tell the manager what to manage
        sceneManager.setRoot  (scene);

        CameraUnrecPtr TheCamera = sceneManager.getCamera();
        TheCamera->setNear(0.1);
        TheCamera->setFar(100.0);

        //Initialize the Sound Manager
        SoundManager::the()->attachUpdateProducer(TutorialWindow);
        SoundManager::the()->setCamera(sceneManager.getCamera());

        SoundRecPtr PopSound = SoundManager::the()->createSound();
        PopSound->setFile(BoostPath("./Data/pop.wav"));
        PopSound->setVolume(1.0);
        PopSound->setStreaming(false);
        PopSound->setLooping(-1);
        PopSound->setEnable3D(true);

        PopSound->connectSoundPlayed  (boost::bind(handleSoundPlayed,   _1));
        PopSound->connectSoundStopped (boost::bind(handleSoundStopped,  _1));
        PopSound->connectSoundPaused  (boost::bind(handleSoundPaused,   _1));
        PopSound->connectSoundUnpaused(boost::bind(handleSoundUnpaused, _1));
        PopSound->connectSoundLooped  (boost::bind(handleSoundLooped,   _1));

        //Attach this sound to the emitter node
        TheEmitter->setSound(PopSound);

        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1,
                                                    TheEmitter.get()));
        TutorialWindow->connectUpdate(boost::bind(handleUpdate, _1,
                                                  TheSphereTransform.get()));

        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "02 Sound3D Window");


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


