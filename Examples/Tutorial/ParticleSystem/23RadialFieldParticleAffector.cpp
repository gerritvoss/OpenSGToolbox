// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"
#include "OSGWindowUtils.h"

// Input
#include "OSGKeyListener.h"

#include "OSGBlendChunk.h"
#include "OSGPointChunk.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGParticleSystem.h"
#include "OSGParticleSystemCore.h"
#include "OSGPointParticleSystemDrawer.h"
#include "OSGRateParticleGenerator.h"
#include "OSGConeDistribution3D.h"
#include "OSGSphereDistribution3D.h"
#include "OSGRadialParticleAffector.h"

#include "OSGGaussianNormalDistribution1D.h"


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
Distribution3DRefPtr createVelocityDistribution(void);

RadialParticleAffectorRefPtr ExampleRadialAffector;

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
        if(e->getKey() == KeyEvent::KEY_R)
        {
            ExampleRadialAffector->setMagnitude(-(ExampleRadialAffector->getMagnitude()));
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

    //Particle System Material
    PointChunkRefPtr PSPointChunk = PointChunk::create();
    PSPointChunk->setSize(5.0f);
    PSPointChunk->setSmooth(true);

    BlendChunkRefPtr PSBlendChunk = BlendChunk::create();
    PSBlendChunk->setSrcFactor(GL_SRC_ALPHA);
    PSBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

    MaterialChunkRefPtr PSMaterialChunkChunk = MaterialChunk::create();
    PSMaterialChunkChunk->setAmbient(Color4f(1.0f,1.0f,1.0f,1.0f));
    PSMaterialChunkChunk->setDiffuse(Color4f(0.7f,0.7f,0.7f,1.0f));
    PSMaterialChunkChunk->setSpecular(Color4f(0.9f,0.9f,0.9f,1.0f));
    PSMaterialChunkChunk->setColorMaterial(GL_NONE);

    ChunkMaterialRefPtr PSMaterial = ChunkMaterial::create();
    PSMaterial->addChunk(PSPointChunk);
    PSMaterial->addChunk(PSMaterialChunkChunk);
    PSMaterial->addChunk(PSBlendChunk);

    //Particle System
    ParticleSystemRefPtr ExampleParticleSystem = OSG::ParticleSystem::create();
    ExampleParticleSystem->addParticle(Pnt3f(0,100,0),
                                       Vec3f(0.0,0.0f,1.0f),
                                       Color4f(1.0,1.0,1.0,1.0), 
                                       Vec3f(1.0,1.0,1.0), 
                                       0.1, 
                                       Vec3f(0.0f,0.0f,0.0f), //Velocity
                                       Vec3f(0.0f,0.0f,0.0f)
                                      );
    ExampleParticleSystem->addParticle(Pnt3f(0,-100,0),
                                       Vec3f(0.0,0.0f,1.0f),
                                       Color4f(1.0,1.0,1.0,1.0), 
                                       Vec3f(1.0,1.0,1.0), 
                                       0.1, 
                                       Vec3f(0.0f,0.0f,0.0f), //Velocity
                                       Vec3f(0.0f,0.0f,0.0f)
                                      );
    ExampleParticleSystem->attachUpdateListener(TutorialWindow);

    //Particle System Drawer (Point)
    PointParticleSystemDrawerRefPtr ExampleParticleSystemDrawer = OSG::PointParticleSystemDrawer::create();


    //Create a Rate Particle Generator
    RateParticleGeneratorRefPtr ExampleGenerator = OSG::RateParticleGenerator::create();

    //Attach the function objects to the Generator
    ExampleGenerator->setPositionDistribution(createPositionDistribution());
    ExampleGenerator->setLifespanDistribution(createLifespanDistribution());
    ExampleGenerator->setGenerationRate(80.0);
    ExampleGenerator->setVelocityDistribution(createVelocityDistribution());

    ExampleRadialAffector = OSG::RadialParticleAffector::create();
    ExampleRadialAffector->setMagnitude(15.0);
    NodeRefPtr RadialBeacon = OSG::Node::create();
    ExampleRadialAffector->setBeacon(RadialBeacon); // set to 'emulate' from (0,0,0)
    ExampleRadialAffector->setMaxDistance(-1.0); // particles affected regardless of distance
    ExampleRadialAffector->setAttenuation(0.0); // strength of uniform field dimishes by dist^attenuation



    //Attach the Generator and Affector to the Particle System
    ExampleParticleSystem->pushToGenerators(ExampleGenerator);
    ExampleParticleSystem->pushToAffectors(ExampleRadialAffector);
    ExampleParticleSystem->setMaxParticles(800);


    //Particle System Node
    ParticleSystemCoreRefPtr ParticleNodeCore = OSG::ParticleSystemCore::create();
    ParticleNodeCore->setSystem(ExampleParticleSystem);
    ParticleNodeCore->setDrawer(ExampleParticleSystemDrawer);
    ParticleNodeCore->setMaterial(PSMaterial);

    NodeRefPtr ParticleNode = OSG::Node::create();
    ParticleNode->setCore(ParticleNodeCore);


    // Make Main Scene Node and add the Torus
    NodeRefPtr scene = OSG::Node::create();
    scene->setCore(OSG::Group::create());
    scene->addChild(ParticleNode);

    mgr->setRoot(scene);

    // Show the whole Scene
    mgr->showAll();

    mgr->getCamera()->setFar(1000.0);

    std::cout << "Radial Particle Affector Tutorial Controls:\n"
        << "R: Reverse direction of field\n"
        << "Ctrl + Q: Exit Tutorial";

    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
                               WinSize,
                               "23RadialFieldParticleAffector");

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
    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(20.0);
    TheSphereDistribution->setOuterRadius(25.0);
    TheSphereDistribution->setMinTheta(0.0);
    TheSphereDistribution->setMaxTheta(6.283185);
    TheSphereDistribution->setMinZ(-1.0);
    TheSphereDistribution->setMaxZ(1.0);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::VOLUME);


    return TheSphereDistribution;
}

Distribution1DRefPtr createLifespanDistribution(void)
{
    GaussianNormalDistribution1DRefPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    TheLifespanDistribution->setMean(15.0f);
    TheLifespanDistribution->setStandardDeviation(3.0);

    return TheLifespanDistribution;
}

Distribution3DRefPtr createVelocityDistribution(void)
{
    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(0.0);
    TheSphereDistribution->setOuterRadius(0.1);
    TheSphereDistribution->setMinTheta(0.0);
    TheSphereDistribution->setMaxTheta(6.283185);
    TheSphereDistribution->setMinZ(-1.0);
    TheSphereDistribution->setMaxZ(1.0);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::SURFACE);

    return TheSphereDistribution;
}
