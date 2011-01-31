// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"
#include "OSGWindowUtils.h"


#include "OSGBlendChunk.h"
#include "OSGPointChunk.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGParticleSystem.h"
#include "OSGParticleSystemCore.h"
#include "OSGPointParticleSystemDrawer.h"
#include "OSGSineWaveParticleAffector.h"
#include "OSGRateParticleGenerator.h"
#include "OSGBurstParticleGenerator.h"

#include "OSGGaussianNormalDistribution1D.h"
#include "OSGLineDistribution3D.h"
#include "OSGSphereDistribution3D.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

Distribution3DRefPtr createPositionDistribution(void);
Distribution3DRefPtr createVelocityDistribution(void);
Distribution3DRefPtr createNormalDistribution(void);
Distribution1DRefPtr createLifespanDistribution(void);
Distribution3DRefPtr createSizeDistribution(void);

void keyTyped(KeyEventDetails* const details,
              SimpleSceneManager *mgr,
              ParticleSystem* const ExampleParticleSystem,
              SineWaveParticleAffector* const ExampleSWA,
              BurstParticleGenerator* const ExampleBurstGen)
{
    if(details->getKey() == KeyEventDetails::KEY_Q &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
    else
    {
        switch(details->getKey())
        {
            case KeyEventDetails::KEY_R:
                {
                    if(ExampleParticleSystem->editMFAffectors()->find(ExampleSWA)
                       == ExampleParticleSystem->editMFAffectors()->end())
                    {
                        ExampleParticleSystem->pushToAffectors(ExampleSWA);
                    }
                    else
                    {
                        ExampleParticleSystem->editMFAffectors()->erase(ExampleParticleSystem->editMFAffectors()->find(ExampleSWA));
                    }
                }
                break;
            case KeyEventDetails::KEY_B:
                {	// check if the burst generator is null
                    if(ExampleBurstGen == NULL)
                    {
                    }
                    // attach the burst generator
                    ExampleParticleSystem->pushToGenerators(ExampleBurstGen);
                }
                break;
        }
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

int main(int argc, char **argv)
{
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

        // Material point chunk, so particles are drawn as points
        PointChunkRefPtr PSPointChunk = PointChunk::create();
        PSPointChunk->setSize(5.0f);
        PSPointChunk->setSmooth(true);

        // Material blend chunk
        BlendChunkRefPtr PSBlendChunk = BlendChunk::create();
        PSBlendChunk->setSrcFactor(GL_SRC_ALPHA);
        PSBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

        //Particle System Material
        MaterialChunkRefPtr PSMaterialChunkChunk = MaterialChunk::create();
        PSMaterialChunkChunk->setAmbient(Color4f(0.5f,0.5f,0.5f,1.0f));
        PSMaterialChunkChunk->setDiffuse(Color4f(0.7f,0.7f,0.7f,1.0f));
        PSMaterialChunkChunk->setSpecular(Color4f(0.9f,0.9f,0.9f,1.0f));
        PSMaterialChunkChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);

        // Assembling materials
        ChunkMaterialRefPtr PSMaterial = ChunkMaterial::create();
        PSMaterial->addChunk(PSMaterialChunkChunk);
        PSMaterial->addChunk(PSPointChunk);
        PSMaterial->addChunk(PSBlendChunk);

        // Creating a particle generator
        RateParticleGeneratorRefPtr ExampleGenerator = RateParticleGenerator::create();
        //Attach the function objects to the Generator
        ExampleGenerator->setPositionDistribution(createPositionDistribution());
        ExampleGenerator->setGenerationRate(30.0);
        ExampleGenerator->setVelocityDistribution(createVelocityDistribution());
        ExampleGenerator->setNormalDistribution(createNormalDistribution());
        ExampleGenerator->setLifespanDistribution(createLifespanDistribution());
        ExampleGenerator->setSizeDistribution(createSizeDistribution());

        // Particle System Sine Wave Affector
        SineWaveParticleAffectorRecPtr ExampleSWA = SineWaveParticleAffector::create();
        ExampleSWA->setAmplitude(0.75f);
        ExampleSWA->setUpDirSource(SineWaveParticleAffector::CROSS_PRODUCT);
        ExampleSWA->setFrequency(23.75f);

        //Creating Particle System
        ParticleSystemRecPtr ExampleParticleSystem = ParticleSystem::create();
        ExampleParticleSystem->addParticle(Pnt3f(0,0,-100),Vec3f(0,1,0),Color4f(1,1,1,1),Vec3f(1,1,1),0.01,Vec3f(0,0,0),Vec3f(0,0,0));
        ExampleParticleSystem->addParticle(Pnt3f(0,0,100),Vec3f(0,1,0),Color4f(1,1,1,1),Vec3f(1,1,1),0.01,Vec3f(0,0,0),Vec3f(0,0,0));
        ExampleParticleSystem->setMaxParticles(1000);
        ExampleParticleSystem->attachUpdateProducer(TutorialWindow); 

        //Creating Particle System Drawer
        PointParticleSystemDrawerRefPtr ExampleParticleSystemDrawer = PointParticleSystemDrawer::create();
        ExampleParticleSystemDrawer->setForcePerParticleSizing(true);

        // Attaching affector and generator to the particle system
        ExampleParticleSystem->pushToAffectors(ExampleSWA);
        ExampleParticleSystem->pushToGenerators(ExampleGenerator);

        BurstParticleGeneratorRecPtr ExampleBurstGen = BurstParticleGenerator::create();
        ExampleBurstGen->setPositionDistribution(createPositionDistribution());
        ExampleBurstGen->setBurstAmount(50);
        ExampleBurstGen->setVelocityDistribution(createVelocityDistribution());
        ExampleBurstGen->setNormalDistribution(createNormalDistribution());
        ExampleBurstGen->setLifespanDistribution(createLifespanDistribution());
        ExampleBurstGen->setSizeDistribution(createSizeDistribution());

        //Particle System Core, setting its system, drawer, and material
        ParticleSystemCoreRefPtr ParticleNodeCore = ParticleSystemCore::create();
        ParticleNodeCore->setSystem(ExampleParticleSystem);
        ParticleNodeCore->setDrawer(ExampleParticleSystemDrawer);
        ParticleNodeCore->setMaterial(PSMaterial);

        // Set up node with the particle system at its core
        NodeRefPtr ParticleNode = Node::create();
        ParticleNode->setCore(ParticleNodeCore);

        // Make Main Scene Node
        NodeRefPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(ParticleNode);

        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1,
                                                    &sceneManager,
                                                    ExampleParticleSystem.get(),
                                                    ExampleSWA.get(),
                                                    ExampleBurstGen.get()));

        sceneManager.setRoot(scene);

        // Show the whole Scene
        sceneManager.showAll();
        sceneManager.getCamera()->setFar(10000.0f);
        sceneManager.getCamera()->setNear(0.1f);


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "30SineWave");

        //Enter main Loop
        TutorialWindow->mainLoop();

    }
    osgExit();

    return 0;
}


// Callback functions


// Redraw the window
void display(SimpleSceneManager *mgr)
{
    mgr->redraw();
}

// React to size changes
void reshape(Vec2f Size, SimpleSceneManager *mgr)
{
    mgr->resize(Size.x(), Size.y());
}

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

    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(30.9);
    TheSphereDistribution->setOuterRadius(31.0);
    TheSphereDistribution->setMinTheta(-3.141950);
    TheSphereDistribution->setMaxTheta(3.141950);
    TheSphereDistribution->setMinZ(-1.0);
    TheSphereDistribution->setMaxZ(1.0);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::SURFACE);

    return TheSphereDistribution;
}

Distribution3DRefPtr createNormalDistribution(void)
{

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
{
    GaussianNormalDistribution1DRefPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    TheLifespanDistribution->setMean(5.0f);
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
