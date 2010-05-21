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
#include "OSGLineParticleSystemDrawer.h"
#include "OSGRateParticleGenerator.h"
#include "OSGConeDistribution3D.h"
#include "OSGGravityParticleAffector.h"

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

GravityParticleAffectorRefPtr ExampleGravityAffector;

PointParticleSystemDrawerRefPtr ExamplePointParticleSystemDrawer;
LineParticleSystemDrawerRefPtr ExampleLineParticleSystemDrawer;

ParticleSystemCoreRefPtr ParticleNodeCore;


// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
  public:

    virtual void keyPressed(const KeyEventUnrecPtr e)
    {
        if(e->getKey()== KeyEvent::KEY_1) // Use the Point Drawer
        {
            ParticleNodeCore->setDrawer(ExamplePointParticleSystemDrawer);
        }

        if(e->getKey()== KeyEvent::KEY_2)//Use the Line Drawer for 2
        {
            ParticleNodeCore->setDrawer(ExampleLineParticleSystemDrawer);
        }
        if(e->getKey()== KeyEvent::KEY_3)// decrease gravity
        {
            ExampleGravityAffector->setMagnitude(OSG::osgClamp<Real32>(1.0f,ExampleGravityAffector->getMagnitude() * 0.8,TypeTraits<Real32>::getMax())); 
        }
        if(e->getKey()== KeyEvent::KEY_4) // increase gravity
        {
            ExampleGravityAffector->setMagnitude(OSG::osgClamp<Real32>(1.0f,ExampleGravityAffector->getMagnitude() * 1.2,TypeTraits<Real32>::getMax())); 

        }
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
    ExampleParticleSystem->addParticle(Pnt3f(0,-150,0),
                                       Vec3f(0.0,0.0f,1.0f),
                                       Color4f(1.0,1.0,1.0,1.0), 
                                       Vec3f(1.0,1.0,1.0), 
                                       0.1, 
                                       Vec3f(0.0f,0.0f,0.0f), //Velocity
                                       Vec3f(0.0f,0.0f,0.0f)
                                      );
    ExampleParticleSystem->addParticle(Pnt3f(0,150,0),
                                       Vec3f(0.0,0.0f,1.0f),
                                       Color4f(1.0,1.0,1.0,1.0), 
                                       Vec3f(1.0,1.0,1.0), 
                                       0.1, 
                                       Vec3f(0.0f,0.0f,0.0f), //Velocity
                                       Vec3f(0.0f,0.0f,0.0f)
                                      );
    ExampleParticleSystem->attachUpdateListener(TutorialWindow);

    //Particle System Drawer (Point)
    PointParticleSystemDrawerRefPtr ExamplePointParticleSystemDrawer = OSG::PointParticleSystemDrawer::create();

    //Particle System Drawer (line)
    ExampleLineParticleSystemDrawer = OSG::LineParticleSystemDrawer::create();
    ExampleLineParticleSystemDrawer->setLineDirectionSource(LineParticleSystemDrawer::DIRECTION_VELOCITY);
    ExampleLineParticleSystemDrawer->setLineLengthSource(LineParticleSystemDrawer::LENGTH_SIZE_X);
    ExampleLineParticleSystemDrawer->setLineLength(0.5f);
    ExampleLineParticleSystemDrawer->setEndPointFading(Vec2f(0.0f,1.0f));


    //Create a Rate Particle Generator
    RateParticleGeneratorRefPtr ExampleGenerator = OSG::RateParticleGenerator::create();

    //Attach the function objects to the Generator
    ExampleGenerator->setPositionDistribution(createPositionDistribution());
    ExampleGenerator->setLifespanDistribution(createLifespanDistribution());
    ExampleGenerator->setGenerationRate(100.0);
    ExampleGenerator->setVelocityDistribution(createVelocityDistribution());

    ExampleGravityAffector = OSG::GravityParticleAffector::create();
    ExampleGravityAffector->setMagnitude(9.8); // Earth's gravitational pull
    ExampleGravityAffector->setDirection(Vec3f(0.0,-1.0,0.0)); // field pulls in downward direction
    NodeRefPtr GravityBeacon = OSG::Node::create();
    ExampleGravityAffector->setBeacon(GravityBeacon); // set to 'emulate' from (0,0,0)
    ExampleGravityAffector->setMaxDistance(-1.0); // no max distance, all particles affected regardless of distance from (0,0,0)
    ExampleGravityAffector->setAttenuation(0.0); // strength of field does not diminish



    //Attach the Generator and Affector to the Particle System
    ExampleParticleSystem->pushToGenerators(ExampleGenerator);
    ExampleParticleSystem->pushToAffectors(ExampleGravityAffector);
    ExampleParticleSystem->setMaxParticles(800);


    //Particle System Node
    ParticleNodeCore = OSG::ParticleSystemCore::create();
    ParticleNodeCore->setSystem(ExampleParticleSystem);
    ParticleNodeCore->setDrawer(ExamplePointParticleSystemDrawer);
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

    std::cout << "Gravity Particle Affector Tutorial Controls:\n"
        << "1: Use point drawer\n"
        << "2: Use line drawer\n"
        << "3: Decrease gravitational pull\n"
        << "4: Increase gravitational pull\n"
        << "Ctrl + Q: Exit Tutorial";

    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
                               WinSize,
                               "18GravityFieldParticleAffector");

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
    //Cone distribution
    ConeDistribution3DRefPtr TheConeDistribution = ConeDistribution3D::create();
    TheConeDistribution->setPosition(Pnt3f(0.0,0.0,0.0));
    TheConeDistribution->setDirection(Vec3f(0.0,1.0,0.0));
    TheConeDistribution->setSpread(0.25);
    TheConeDistribution->setMin(0.0);
    TheConeDistribution->setMax(0.1);
    TheConeDistribution->setSurfaceOrVolume(ConeDistribution3D::VOLUME);


    return TheConeDistribution;
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
    ConeDistribution3DRefPtr TheConeDistribution = ConeDistribution3D::create();
    TheConeDistribution->setPosition(Pnt3f(0.0,0.0,0.0));
    TheConeDistribution->setDirection(Vec3f(0.0,1.0,0.0));
    TheConeDistribution->setSpread(1.5);
    TheConeDistribution->setMin(30.0);
    TheConeDistribution->setMax(40.0);
    TheConeDistribution->setSurfaceOrVolume(ConeDistribution3D::VOLUME);

    return TheConeDistribution;
}
