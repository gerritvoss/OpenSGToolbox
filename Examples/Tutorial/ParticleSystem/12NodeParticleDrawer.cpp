// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"
#include "OSGSimpleGeometry.h"
#include "OSGWindowUtils.h"

// Input
#include "OSGKeyListener.h"

#include "OSGParticleSystem.h"
#include "OSGNodeParticleSystemCore.h"
#include "OSGCollectiveGravityParticleSystemAffector.h"

#include "OSGGaussianNormalDistribution1D.h"
#include "OSGCylinderDistribution3D.h"

#include "OSGSceneFileHandler.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

Distribution3DRefPtr createPositionDistribution(void);
Distribution1DRefPtr createLifespanDistribution(void);

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
  public:

    virtual void keyPressed(const KeyEventUnrecPtr e)
    {
        if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
        {
            TutorialWindow->closeWindow();
        }
    }

    virtual void keyReleased(const KeyEventUnrecPtr e)
    {
    }

    virtual void keyTyped(const KeyEventUnrecPtr e)
    {
    }
};

class TutorialMouseListener : public MouseListener
{
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
        mgr->mouseButtonPress(e->getButton(), e->getLocation().x(), e->getLocation().y());
    }
    virtual void mouseReleased(const MouseEventUnrecPtr e)
    {
        mgr->mouseButtonRelease(e->getButton(), e->getLocation().x(), e->getLocation().y());
    }
};

class TutorialMouseMotionListener : public MouseMotionListener
{
  public:
    virtual void mouseMoved(const MouseEventUnrecPtr e)
    {
        mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
    }

    virtual void mouseDragged(const MouseEventUnrecPtr e)
    {
        mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
    }
};
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindow = createNativeWindow();
    TutorialWindow->initWindow();

    TutorialWindow->setDisplayCallback(display);
    TutorialWindow->setReshapeCallback(reshape);

    TutorialKeyListener TheKeyListener;
    TutorialWindow->addKeyListener(&TheKeyListener);
    TutorialMouseListener TheTutorialMouseListener;
    TutorialMouseMotionListener TheTutorialMouseMotionListener;
    TutorialWindow->addMouseListener(&TheTutorialMouseListener);
    TutorialWindow->addMouseMotionListener(&TheTutorialMouseMotionListener);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindow);

    Distribution3DRefPtr PositionDistribution = createPositionDistribution();
    Distribution1DRefPtr LifespanDistribution = createLifespanDistribution();

    Pnt3f PositionReturnValue;
    Time LifespanReturnValue = -1;

    //Particle System
    ParticleSystemRefPtr ExampleParticleSystem = OSG::ParticleSystem::create();
    for(UInt32 i(0) ; i<200 ; ++i)//controls how many particles are created
    {
        if(PositionDistribution != NULL)
        {
            PositionReturnValue = Pnt3f(PositionDistribution->generate());
        }
        if(LifespanDistribution != NULL)
        {
            LifespanReturnValue = LifespanDistribution->generate();
        }

        ExampleParticleSystem->addParticle(
                                           PositionReturnValue,
                                           Vec3f(1.0f,0.0f,0.0f),
                                           Color4f(1.0,0.0,0.0,1.0), 
                                           Vec3f(1.0,1.0,1.0), 
                                           LifespanReturnValue, 
                                           Vec3f(0.0f,0.0f,0.0f), //Velocity
                                           Vec3f(0.0f,0.0f,0.0f)	//acceleration
                                          );
    }
    ExampleParticleSystem->attachUpdateListener(TutorialWindow);

    //NodeRefPtr ParticlePrototypeNode = makeTorus(1.0,4.0,16,16);
    NodeRefPtr ParticlePrototypeNode = SceneFileHandler::the()->read("Data/rocket.obj");
    if(ParticlePrototypeNode == NULL)
    {
        ParticlePrototypeNode = makeTorus(.5, 2, 16, 16);
    }
    //Particle System Node
    NodeParticleSystemCoreRefPtr NodeParticleNodeCore = OSG::NodeParticleSystemCore::create();
    NodeParticleNodeCore->setSystem(ExampleParticleSystem);
    NodeParticleNodeCore->setPrototypeNode(ParticlePrototypeNode);
    NodeParticleNodeCore->setNormalSource(NodeParticleSystemCore::NORMAL_VELOCITY);
    NodeParticleNodeCore->setUpSource(NodeParticleSystemCore::UP_STATIC);
    NodeParticleNodeCore->setUp(Vec3f(0.0f,1.0f,0.0f));

    NodeRefPtr ParticleNode = OSG::Node::create();
    ParticleNode->setCore(NodeParticleNodeCore);

    //Create an CollectiveGravityParticleSystemAffector
    CollectiveGravityParticleSystemAffectorRefPtr ExampleCollectiveGravityParticleSystemAffector = OSG::CollectiveGravityParticleSystemAffector::create();
    ExampleCollectiveGravityParticleSystemAffector->setParticleMass(10000000000.0f);

    ExampleParticleSystem->pushToSystemAffectors(ExampleCollectiveGravityParticleSystemAffector);


    // Make Main Scene Node and add the Torus
    NodeRefPtr scene = OSG::Node::create();
    scene->setCore(OSG::Group::create());
    scene->addChild(ParticleNode);

    mgr->setRoot(scene);

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
                               WinSize,
                               "12NodeParticleDrawer");

    //Enter main Loop
    TutorialWindow->mainLoop();

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

Distribution3DRefPtr createPositionDistribution(void)
{
    //Cylinder Distribution
    CylinderDistribution3DRefPtr TheCylinderDistribution = CylinderDistribution3D::create();
    TheCylinderDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheCylinderDistribution->setInnerRadius(30.0);
    TheCylinderDistribution->setOuterRadius(100.0);
    TheCylinderDistribution->setMinTheta(0.0);
    TheCylinderDistribution->setMaxTheta(6.283185);
    TheCylinderDistribution->setHeight(400.0);
    TheCylinderDistribution->setNormal(Vec3f(0.0,0.0,1.0));
    TheCylinderDistribution->setSurfaceOrVolume(CylinderDistribution3D::SURFACE);

    return TheCylinderDistribution;
}

Distribution1DRefPtr createLifespanDistribution(void)
{
    GaussianNormalDistribution1DRefPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    TheLifespanDistribution->setMean(100.0f);
    TheLifespanDistribution->setStandardDeviation(2.0);

    return TheLifespanDistribution;
}
