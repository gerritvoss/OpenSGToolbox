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

// Particle Systems and materials, trail generator
#include "OSGSimpleParticleTrailGenerator.h"
#include "OSGBlendChunk.h"
#include "OSGPointChunk.h"
#include "OSGLineChunk.h"
#include "OSGTextureObjChunk.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGParticleSystem.h"
#include "OSGParticleSystemCore.h"
#include "OSGPointParticleSystemDrawer.h"
#include "OSGRateParticleGenerator.h"
#include "OSGBurstParticleGenerator.h"
#include "OSGGaussianNormalDistribution1D.h"
#include "OSGLineDistribution3D.h"
#include "OSGSphereDistribution3D.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

ParticleSystemRefPtr ExampleParticleSystem;
BurstParticleGeneratorRefPtr ExampleBurstGen;
SimpleParticleTrailGeneratorRefPtr ExampleTrailGenerator;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// Helper fucntions for particle system distributions
Distribution3DRefPtr createPositionDistribution(void);
Distribution3DRefPtr createVelocityDistribution(void);
Distribution3DRefPtr createNormalDistribution(void);
Distribution1DRefPtr createLifespanDistribution(void);
Distribution3DRefPtr createSizeDistribution(void);


// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
  public:

    virtual void keyPressed(const KeyEventUnrecPtr e)
    {
        if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
        {
            TutorialWindow->closeWindow();
        }
        else
        {
            switch(e->getKey())
            {
                case KeyEvent::KEY_B:
                    {	// check if the burst generator is null
                        if(ExampleBurstGen == NULL)
                        {
                            ExampleBurstGen = OSG::BurstParticleGenerator::create();
                            ExampleBurstGen->setPositionDistribution(createPositionDistribution());
                            ExampleBurstGen->setBurstAmount(20);
                            ExampleBurstGen->setVelocityDistribution(createVelocityDistribution());
                            ExampleBurstGen->setNormalDistribution(createNormalDistribution());
                            ExampleBurstGen->setLifespanDistribution(createLifespanDistribution());
                            ExampleBurstGen->setSizeDistribution(createSizeDistribution());
                        }
                        // attach the burst generator
                        ExampleParticleSystem->pushToGenerators(ExampleBurstGen);
                    }
                    break;
                case KeyEvent::KEY_P:
                    {	// increase trail resolution
                        ExampleTrailGenerator->setTrailResolution(ExampleTrailGenerator->getTrailResolution() * 0.70 + 0.0001);
                        std::cout << "Trail Resolution:  " << ExampleTrailGenerator->getTrailResolution() << std::endl;
                        break;
                    }
                case KeyEvent::KEY_L:
                    {	// decrease trail resolution
                        ExampleTrailGenerator->setTrailResolution(ExampleTrailGenerator->getTrailResolution() * 1.25);
                        std::cout << "Trail Resolution:  " << ExampleTrailGenerator->getTrailResolution() << std::endl;
                        break;
                    }
                case KeyEvent::KEY_O:
                    {	// increase trail length
                        ExampleTrailGenerator->setTrailLength(ExampleTrailGenerator->getTrailLength() * 1.25 + 0.1);
                        std::cout << "Trail Length:  " << ExampleTrailGenerator->getTrailLength() << std::endl;
                        break;
                    }
                case KeyEvent::KEY_K:
                    {	// decrease trail length
                        ExampleTrailGenerator->setTrailLength(ExampleTrailGenerator->getTrailLength() * 0.7);
                        std::cout << "Trail Length:  " << ExampleTrailGenerator->getTrailLength() << std::endl;
                        break;
                    }
                case KeyEvent::KEY_I:
                    {	// toggle lines/points as trail draw method
                        ExampleTrailGenerator->setDrawMethod((ExampleTrailGenerator->getDrawMethod() == SimpleParticleTrailGenerator::LINES)?
                                                             (SimpleParticleTrailGenerator::POINTS):(SimpleParticleTrailGenerator::LINES));
                        break;
                    }
                case KeyEvent::KEY_J:
                    {	// toggle trail length method
                        ExampleTrailGenerator->setTrailLengthMethod((ExampleTrailGenerator->getTrailLengthMethod() == ParticleTrailGenerator::NUM_POINTS)?
                                                                    (ParticleTrailGenerator::TIME):(ParticleTrailGenerator::NUM_POINTS));
                        std::cout << "Trail Length: " << (ExampleTrailGenerator->getTrailLengthMethod() == ParticleTrailGenerator::NUM_POINTS ? "Num Pts":"Time") << std::endl;
                        break;
                    }
                case KeyEvent::KEY_Y:
                    {	// toggle trail spacing method
                        ExampleTrailGenerator->setTrailResolutionMethod((ExampleTrailGenerator->getTrailResolutionMethod() == ParticleTrailGenerator::TIME_SPACING)?
                                                                        (ParticleTrailGenerator::DISTANCE_SPACING):(ParticleTrailGenerator::TIME_SPACING));
                        std::cout << "Trail resolution: " <<(ExampleTrailGenerator->getTrailResolutionMethod() == ParticleTrailGenerator::TIME_SPACING ? "Time Spacing" : "Distance Spacing") << std::endl;
                        break;
                    }
                case KeyEvent::KEY_V:
                    {
                        mgr->getRenderAction()->setVolumeDrawing(!mgr->getRenderAction()->getVolumeDrawing());
                    }
            }
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

    // Material point chunk, so particles are drawn as points
    PointChunkRefPtr PSPointChunk = PointChunk::create();
    PSPointChunk->setSize(5.0f);
    PSPointChunk->setSmooth(true);

    // Material blend chunk
    BlendChunkRefPtr PSBlendChunk = BlendChunk::create();
    PSBlendChunk->setSrcFactor(GL_SRC_ALPHA);
    PSBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

    LineChunkRefPtr PSLineChunk = LineChunk::create();

    //Texture Chunk
    TextureObjChunkRefPtr PSTexChunk = OSG::TextureObjChunk::create();

    //Particle System Material
    MaterialChunkRefPtr PSMaterialChunkChunk = MaterialChunk::create();
    PSMaterialChunkChunk->setAmbient(Color4f(1.0f,0.5f,0.3f,1.0f));
    PSMaterialChunkChunk->setDiffuse(Color4f(1.0f,0.5f,0.3f,0.6f));
    PSMaterialChunkChunk->setSpecular(Color4f(1.0f,0.5f,0.3f,0.6f));
    PSMaterialChunkChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);

    // Assembling materials
    ChunkMaterialRefPtr PSMaterial = ChunkMaterial::create();
    PSMaterial->addChunk(PSMaterialChunkChunk);
    PSMaterial->addChunk(PSPointChunk);
    PSMaterial->addChunk(PSBlendChunk);
    PSMaterial->addChunk(PSLineChunk);
    PSMaterial->addChunk(PSTexChunk);
    PSMaterial->setTransparencyMode(Material::TransparencyForceTransparent);

    // Creating a particle generator
    RateParticleGeneratorRefPtr ExampleGenerator = OSG::RateParticleGenerator::create();
    //Attach the function objects to the Generator
    ExampleGenerator->setPositionDistribution(createPositionDistribution());
    ExampleGenerator->setGenerationRate(8.0);
    ExampleGenerator->setVelocityDistribution(createVelocityDistribution());
    ExampleGenerator->setLifespanDistribution(createLifespanDistribution());
    ExampleGenerator->setSizeDistribution(createSizeDistribution());

    //Creating Particle System
    ExampleParticleSystem = OSG::ParticleSystem::create();
    // add a couple temp particles so the camera is zoomed out 
    ExampleParticleSystem->addParticle(OSG::Pnt3f(0,0,-100),OSG::Vec3f(0,1,0),OSG::Color4f(1,1,1,1),OSG::Vec3f(1,1,1),0.1,OSG::Vec3f(0,0,0),OSG::Vec3f(0,0,0));
    ExampleParticleSystem->addParticle(OSG::Pnt3f(0,0,100),OSG::Vec3f(0,1,0),OSG::Color4f(1,1,1,1),OSG::Vec3f(1,1,1),0.1,OSG::Vec3f(0,0,0),OSG::Vec3f(0,0,0));
    ExampleParticleSystem->setMaxParticles(200);
    ExampleParticleSystem->attachUpdateListener(TutorialWindow); 

    //Creating Particle System Drawer
    PointParticleSystemDrawerRefPtr ExampleParticleSystemDrawer = OSG::PointParticleSystemDrawer::create();
    ExampleParticleSystemDrawer->setForcePerParticleSizing(true);

    // Attaching affector and generator to the particle system
    ExampleParticleSystem->pushToGenerators(ExampleGenerator);

    //Particle System Core, setting its system, drawer, and material
    ParticleSystemCoreRefPtr ParticleNodeCore = OSG::ParticleSystemCore::create();
    ParticleNodeCore->setSystem(ExampleParticleSystem);
    ParticleNodeCore->setDrawer(ExampleParticleSystemDrawer);
    ParticleNodeCore->setMaterial(PSMaterial);

    // Create Trail Generator(s)
    // simple trail generator
    ExampleTrailGenerator = OSG::SimpleParticleTrailGenerator::create();
    ExampleTrailGenerator->setTrailResolution(2.5f);
    ExampleTrailGenerator->setDrawMethod(SimpleParticleTrailGenerator::POINTS);
    ExampleTrailGenerator->setTrailLength(3.12);
    ExampleTrailGenerator->setTrailLengthMethod(ParticleTrailGenerator::TIME);
    ExampleTrailGenerator->setTrailResolutionMethod(ParticleTrailGenerator::DISTANCE_SPACING);
    ExampleTrailGenerator->setTrailMaterial(PSMaterial);

    // attach listener for trail generator to the particle system
    ExampleParticleSystem->addParticleSystemListener(ExampleTrailGenerator->getParticleSystemListener());

    // Set up node with the particle system at its core
    NodeRefPtr ParticleNode = OSG::Node::create();
    ParticleNode->setCore(ParticleNodeCore);
    // add the trail generator to the scene
    ParticleNode->addChild(ExampleTrailGenerator);

    // Make Main Scene Node
    NodeRefPtr scene = OSG::Node::create();
    scene->setCore(OSG::Group::create());
    scene->addChild(ParticleNode);

    mgr->setRoot(scene);

    // Show the whole Scene
    mgr->showAll();
    mgr->getCamera()->setFar(10000.0f);
    mgr->getCamera()->setNear(0.1f);
    mgr->setStatistics(true);

    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
                               WinSize,
                               "01ParticleTrail");

    std::cout << "Controls: " << std::endl
        << "P: Increase Trail Resolution" << std::endl
        << "L: Decrease Trail Resolution" << std::endl
        << "O: Increase Trail Length" << std::endl
        << "K: Decrease Trail Length" << std::endl
        << "I: Toggle drawing trails as points/lines" << std::endl
        << "J: Toggle calculating trail length by num points/time" << std::endl
        << "Y: Toggle calculating trail point spacing by time/distance" << std::endl
        << "B: Particle burst" << std::endl;

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

// helper functions to create particle system distributions
Distribution3DRefPtr createPositionDistribution(void)
{
    //Line Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(0.0,0.0,0.0));
    TheLineDistribution->setPoint2(Pnt3f(0.0,0.0,0.0));

    return TheLineDistribution;
}

Distribution3DRefPtr createVelocityDistribution(void)
{
    // spherical dist.
    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(10.0);
    TheSphereDistribution->setOuterRadius(20.0);
    TheSphereDistribution->setMinTheta(-3.141950);
    TheSphereDistribution->setMaxTheta(3.141950);
    TheSphereDistribution->setMinZ(-1.0);
    TheSphereDistribution->setMaxZ(1.0);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::SURFACE);

    return TheSphereDistribution;
}

Distribution3DRefPtr createNormalDistribution(void)
{	// spherical distribution
    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(1.0);
    TheSphereDistribution->setOuterRadius(1.0);
    TheSphereDistribution->setMinTheta(-3.141950);
    TheSphereDistribution->setMaxTheta(3.141950);
    TheSphereDistribution->setMinZ(-1.0);
    TheSphereDistribution->setMaxZ(1.0);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::SURFACE);

    return TheSphereDistribution;
}

Distribution1DRefPtr createLifespanDistribution(void)
{	// Normal Distribution
    GaussianNormalDistribution1DRefPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    TheLifespanDistribution->setMean(3.0f);
    TheLifespanDistribution->setStandardDeviation(1.0);

    return TheLifespanDistribution;
}

Distribution3DRefPtr createSizeDistribution(void)
{
    //Line Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(4.0,4.0,4.0));
    TheLineDistribution->setPoint2(Pnt3f(6.0,6.0,6.0));

    return TheLineDistribution;
}

