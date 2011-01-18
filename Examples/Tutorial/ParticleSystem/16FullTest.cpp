// This tutorial can be used to test anything that needs to be tested for the particle system.  Sorting, drawers, affectors, etc.

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
#include "OSGSimpleGeometry.h"
#include "OSGBlendChunk.h"
#include "OSGPointChunk.h"
#include "OSGDepthChunk.h"
#include "OSGLineChunk.h"
#include "OSGPolygonChunk.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGParticleSystem.h"
#include "OSGParticleSystemCore.h"
#include "OSGNodeParticleSystemCore.h"
#include "OSGPointParticleSystemDrawer.h"
#include "OSGDiscParticleSystemDrawer.h"
#include "OSGRateParticleGenerator.h"
#include "OSGBurstParticleGenerator.h"
#include "OSGGravityParticleAffector.h"
#include "OSGRadialParticleAffector.h"
#include "OSGVortexParticleAffector.h"
#include "OSGAgeFadeParticleAffector.h"
#include "OSGRandomMovementParticleAffector.h"
#include "OSGNewtonParticleAffector.h"
#include "OSGConditionalParticleAffector.h"
#include "OSGDistanceAttractRepelParticleAffector.h"
#include "OSGGaussianNormalDistribution1D.h"
#include "OSGSegmentDistribution1D.h"
#include "OSGGaussianNormalDistribution3D.h"
#include "OSGGeoSurfaceDistribution3D.h"
#include "OSGSphereDistribution3D.h"
#include "OSGConeDistribution3D.h"
#include "OSGLineDistribution3D.h"
#include "OSGFCFileHandler.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

// Particle Generator Distributions
Distribution3DRefPtr createPositionDistribution(void);
Distribution1DRefPtr createLifespanDistribution(void);
Distribution3DRefPtr createVelocityDistribution(void);

void keyTyped(KeyEventDetails* const details,
              SimpleSceneManager *mgr,
              ParticleSystemCore* const ParticleNodeCore,
              PointParticleSystemDrawer* const ExamplePointParticleSystemDrawer,
              ParticleSystem* const ExampleParticleSystem,
              ConditionalParticleAffector* const ExampleConditionalAffector
             )
{
    if(details->getKey() == KeyEventDetails::KEY_Q &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
    if(details->getKey() == KeyEventDetails::KEY_F) //particles will be sorted from closest to the view point to the furthest
    {
        ParticleNodeCore->setSortingMode(ParticleSystemCore::FRONT_TO_BACK);
    }
    if(details->getKey() == KeyEventDetails::KEY_R) //particles will be sorted from furthest to the view point to the closest.
    {
        ParticleNodeCore->setSortingMode(ParticleSystemCore::BACK_TO_FRONT);
    }
    if(details->getKey() == KeyEventDetails::KEY_N) //particles will not be sorted
    {
        ParticleNodeCore->setSortingMode(ParticleSystemCore::NONE);
    }
    if(details->getKey() == KeyEventDetails::KEY_O) 
    {
        ExampleConditionalAffector->setConditionalOperator(1); //equals
    }
    if(details->getKey() == KeyEventDetails::KEY_P) 
    {
        ExampleConditionalAffector->setConditionalOperator(2); // not equal

    }
    if(details->getKey() == KeyEventDetails::KEY_H) 
    {
        for(unsigned int i(0); i < ExampleParticleSystem->getNumParticles(); ++i)
        {
            ExampleParticleSystem->setAttribute("active",1,i);
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

        //Particle System Material
        PointChunkRefPtr PSPointChunk = PointChunk::create();
        PSPointChunk->setSize(20.0f);
        PSPointChunk->setSmooth(true);

        BlendChunkRefPtr PSBlendChunk = BlendChunk::create();
        PSBlendChunk->setSrcFactor(GL_SRC_ALPHA);
        PSBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

        MaterialChunkRefPtr PSMaterialChunkChunk = MaterialChunk::create();
        PSMaterialChunkChunk->setAmbient(Color4f(0.2f,0.6f,0.5f,0.3f));
        PSMaterialChunkChunk->setDiffuse(Color4f(0.2f,0.9f,0.1f,0.3f));
        PSMaterialChunkChunk->setSpecular(Color4f(0.5f,0.4f,0.2f,0.6f));
        PSMaterialChunkChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);

        //enable depth test
        DepthChunkRefPtr PSDepthChunk = DepthChunk::create();

        ChunkMaterialRefPtr PSMaterial = ChunkMaterial::create();
        PSMaterial->addChunk(PSPointChunk);
        PSMaterial->addChunk(PSMaterialChunkChunk);
        PSMaterial->addChunk(PSBlendChunk);
        PSMaterial->addChunk(PSDepthChunk);

        LineChunkRefPtr PSLineChunk = LineChunk::create();
        ChunkMaterialRefPtr TestMaterial = ChunkMaterial::create();
        //TestMaterial->addChunk(PointChunk::create());
        //TestMaterial->addChunk(LineChunk::create());
        TestMaterial->addChunk(PSMaterialChunkChunk);
        PolygonChunkRefPtr ThePolygonChunk = PolygonChunk::create();
        BlendChunkRefPtr TheBlendChunk = BlendChunk::create();
        DepthChunkRefPtr TheDepthChunk = DepthChunk::create();
        TestMaterial->addChunk(ThePolygonChunk);
        TestMaterial->addChunk(TheBlendChunk);
        TestMaterial->addChunk(TheDepthChunk);

        //Particle System
        ParticleSystemRecPtr ExampleParticleSystem = ParticleSystem::create();


        ExampleParticleSystem->attachUpdateProducer(TutorialWindow);

        ExampleParticleSystem->addParticle(Pnt3f(-40.0,0.0,0.0),
                                           Vec3f(0.0,1.0,0.0),
                                           Color4f(1.0,1.0,1.0,1.0),
                                           Vec3f(1.0,1.0,1.0),
                                           -1,
                                           Vec3f(0.0,0.0,0.0),
                                           Vec3f(0.0,0.0,0.0));

        ExampleParticleSystem->addParticle(Pnt3f(40.0,0.0,0.0),
                                           Vec3f(0.0,1.0,0.0),
                                           Color4f(1.0,1.0,1.0,1.0),
                                           Vec3f(1.0,1.0,1.0),
                                           -1,
                                           Vec3f(0.0,0.0,0.0),
                                           Vec3f(0.0,0.0,0.0));

        PointParticleSystemDrawerRecPtr ExamplePointParticleSystemDrawer = PointParticleSystemDrawer::create();
        ExamplePointParticleSystemDrawer->setForcePerParticleSizing(false);

        Matrix ExampleMatrix;
        ExampleMatrix.setTransform(Vec3f(10.0,10.0,10.0));

        TransformRefPtr ExampleXform = Transform::create();
        ExampleXform->setMatrix(ExampleMatrix);


        NodeRefPtr ExampleNode = Node::create();
        ExampleNode->setCore(ExampleXform);

        RateParticleGeneratorRecPtr ExampleGenerator = RateParticleGenerator::create();
        //		ExampleGenerator->setEmitInWorldSpace(true);
        ExampleGenerator->setBeacon(ExampleNode);
        ExampleGenerator->setGenerationRate(5.0);
        ExampleGenerator->setPositionDistribution(createPositionDistribution());
        ExampleGenerator->setLifespanDistribution(createLifespanDistribution());

        NewtonParticleAffectorRefPtr ExampleAffector = NewtonParticleAffector::create();
        ExampleAffector->setBeacon(ExampleNode);
        ExampleAffector->setMaxDistance(-1.0);

        ConditionalParticleAffectorRecPtr ExampleConditionalAffector = ConditionalParticleAffector::create();
        ExampleConditionalAffector->setConditionalAttribute("active");
        ExampleConditionalAffector->setConditionalOperator(4); //greater than
        ExampleConditionalAffector->setConditionalValue(0); // testing if the value associated with "test" = 1
        ExampleConditionalAffector->pushToAffectors(ExampleAffector);

        DistanceAttractRepelParticleAffectorRefPtr ExampleAttractRepelAffector = DistanceAttractRepelParticleAffector::create();
        ExampleAttractRepelAffector->setDistanceFromSource(DistanceParticleAffector::DISTANCE_FROM_NODE);

        //Attach the Generators and affectors to the Particle System
        ExampleParticleSystem->setBeacon(ExampleNode);
        //ExampleParticleSystem->pushToGenerators(ExampleGenerator);
        ExampleParticleSystem->pushToAffectors(ExampleConditionalAffector);
        // ExampleParticleSystem->pushToAffectors(ExampleAttractRepelAffector);
        ExampleParticleSystem->setMaxParticles(1000);
        ExampleParticleSystem->setDynamic(true);

        //Particle System Core
        ParticleSystemCoreRecPtr ParticleNodeCore = ParticleSystemCore::create();
        ParticleNodeCore->setSystem(ExampleParticleSystem);
        ParticleNodeCore->setDrawer(ExamplePointParticleSystemDrawer);
        ParticleNodeCore->setMaterial(PSMaterial);
        ParticleNodeCore->setSortingMode(ParticleSystemCore::BACK_TO_FRONT);

        NodeRefPtr PSNode = Node::create();
        PSNode->setCore(ParticleNodeCore);

        // Make Main Scene Node and add the Torus
        NodeRefPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(PSNode);


        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1, &sceneManager,
                                                    ParticleNodeCore.get(),
                                                    ExamplePointParticleSystemDrawer.get(),
                                                    ExampleParticleSystem.get(),
                                                    ExampleConditionalAffector.get()));
        sceneManager.setRoot(scene);

        // Show the whole Scene
        sceneManager.showAll();
        sceneManager.getCamera()->setFar(1000.0);
        sceneManager.getCamera()->setNear(0.10);

        FCFileType::FCPtrStore Containers;
        Containers.insert(scene);

        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "16FullTest");

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
    //Sphere Distribution
    ConeDistribution3DRefPtr TheConeDistribution = ConeDistribution3D::create();
    TheConeDistribution->setPosition(Pnt3f(0.0,0.0,0.0));
    TheConeDistribution->setDirection(Vec3f(0.0,0.0,1.0));
    TheConeDistribution->setSpread(3.14159);
    TheConeDistribution->setMin(1.4);
    TheConeDistribution->setMax(1.5);
    TheConeDistribution->setSurfaceOrVolume(ConeDistribution3D::VOLUME);

    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(1.0);
    TheSphereDistribution->setOuterRadius(2.0);
    TheSphereDistribution->setMinTheta(0.0);
    TheSphereDistribution->setMaxTheta(6.283185);
    TheSphereDistribution->setMinZ(-1.0);
    TheSphereDistribution->setMaxZ(1.0);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::VOLUME);

    return TheSphereDistribution;
}

Distribution1DRefPtr createLifespanDistribution(void)
{
    SegmentDistribution1DRefPtr TheLifespanDistribution = SegmentDistribution1D::create();
    TheLifespanDistribution->setSegment(Vec2f(1.0,1.1));

    return TheLifespanDistribution;
}

Distribution3DRefPtr createVelocityDistribution(void)
{
    //Line Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(0.0,0.0,0.0));
    TheLineDistribution->setPoint2(Pnt3f(0.0,0.0,0.0));

    return TheLineDistribution;
}

