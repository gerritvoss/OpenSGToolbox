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
#include "OSGBlendChunk.h"
#include "OSGPointChunk.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGTextureObjChunk.h"
#include "OSGTextureEnvChunk.h"
#include "OSGImageFileHandler.h"

#include "OSGSimpleSceneManager.h"
#include "OSGSceneFileHandler.h"

#include "OSGParticleSystem.h"
#include "OSGParticleSystemCore.h"
#include "OSGNodeParticleSystemCore.h"

#include "OSGPointParticleSystemDrawer.h"
#include "OSGLineParticleSystemDrawer.h"
#include "OSGQuadParticleSystemDrawer.h"

#include "OSGAgeFadeParticleAffector.h"
#include "OSGAgeSizeParticleAffector.h"
#include "OSGDistanceKillParticleAffector.h"
#include "OSGCollectiveGravityParticleSystemAffector.h"
#include "OSGGeometryCollisionParticleSystemAffector.h"

#include "OSGRateParticleGenerator.h"
#include "OSGBurstParticleGenerator.h"

#include "OSGLineDistribution3D.h"
#include "OSGCylinderDistribution3D.h"
#include "OSGGaussianNormalDistribution1D.h"
#include "OSGDiscDistribution3D.h"
#include "OSGSphereDistribution3D.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

Distribution3DRefPtr createPositionDistribution(void);
Distribution1DRefPtr createLifespanDistribution(void);
Distribution3DRefPtr createVelocityDistribution(void);
Distribution3DRefPtr createSmokePositionDistribution(void);
Distribution1DRefPtr createSmokeLifespanDistribution(void);
Distribution3DRefPtr createSmokeVelocityDistribution(void);
Distribution3DRefPtr createShrapnelPositionDistribution(void);
Distribution3DRefPtr createShrapnelAccelerationDistribution(void);
Distribution3DRefPtr createShrapnelVelocityDistribution(void);
Distribution3DRefPtr createFireballVelocityDistribution(void);
Distribution3DRefPtr createFireballPositionDistribution(void);
Distribution3DRefPtr createFireballAccelerationDistribution(void);
Distribution1DRefPtr createFireballLifespanDistribution(void);

void particleKilled(ParticleEventDetails* const details,
                    ParticleSystem* const ShrapnelParticleSystem,
                    BurstParticleGenerator* const ShrapnelBurstGenerator,
                    ParticleSystem* const SmokeParticleSystem,
                    RateParticleGenerator* const SmokeGenerator,
                    ParticleSystem* const FireballParticleSystem,
                    BurstParticleGenerator* const FireballGenerator)
{
    dynamic_cast<SphereDistribution3D*>(FireballGenerator->getPositionDistribution())->setCenter(details->getParticlePosition());

    dynamic_cast<SphereDistribution3D*>(ShrapnelBurstGenerator->getPositionDistribution())->setCenter(details->getParticlePosition());

    dynamic_cast<DiscDistribution3D*>(SmokeGenerator->getPositionDistribution())->setCenter(details->getParticlePosition());

    //Attach the Generator to the Shrapnel Particle System
    ShrapnelParticleSystem->pushToGenerators(ShrapnelBurstGenerator);

    //Attach the Affector to the Smoke Particle System
    SmokeParticleSystem->pushToGenerators(SmokeGenerator);

    //Attach the Affector to the fireball Particle System
    FireballParticleSystem->pushToGenerators(FireballGenerator);

    std::cout << "Rocket Died at: " << details->getParticlePosition() << std::endl;
}

void particleCollision(ParticleGeometryCollisionEventDetails* const details)
{
    ParticleSystemRefPtr TheSystem= details->getSystem();
    UInt32 ParticleIndex(details->getParticleIndex());


    Real32 phi= osgACos((-TheSystem->getVelocity(ParticleIndex).dot(details->getHitNormal()))/(TheSystem->getVelocity(ParticleIndex).length()*details->getHitNormal().length()));

    if( phi < osgDegree2Rad(80.0) )
    {
        TheSystem->killParticle(ParticleIndex);
    }
    else
    {
        //Reflect the Particle
        Vec3f Reflect(TheSystem->getVelocity(ParticleIndex).reflect(details->getHitNormal()));
        TheSystem->setVelocity(Reflect, ParticleIndex);
        TheSystem->setPosition(details->getHitPoint() + (0.00001f*Reflect), ParticleIndex);
    }

}

void keyTyped(KeyEventDetails* const details,
              SimpleSceneManager *mgr
             )
{
    if(details->getKey() == KeyEventDetails::KEY_Q &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
}

void mousePressed(MouseEventDetails* const details,
                  SimpleSceneManager *mgr,
                  ParticleSystem* const RocketParticleSystem)
{
    if(dynamic_cast<WindowEventProducer*>(details->getSource())->getKeyModifiers() &
       KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        mgr->mouseButtonPress(details->getButton(), details->getLocation().x(), details->getLocation().y());
    }
    else
    {
        if(details->getButton() == MouseEventDetails::BUTTON1)
        {
            Line TheRay;
            mgr->getCamera()->calcViewRay(TheRay,details->getLocation().x(),details->getLocation().y(),*(mgr->getWindow()->getPort(0)));
            RocketParticleSystem->addParticle(TheRay.getPosition(),
                                              Vec3f(0.0,1.0f,0.0f),
                                              Color4f(1.0,0.0,0.0,1.0), 
                                              Vec3f(1.0,1.0,1.0), 
                                              10, 
                                              Vec3f(TheRay.getDirection()*50), //Velocity
                                              Vec3f(0.0f,0.0f,0.0f)
                                             );
        }
    }
}
void mouseReleased(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    if(dynamic_cast<WindowEventProducer*>(details->getSource())->getKeyModifiers() &
       KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        mgr->mouseButtonRelease(details->getButton(), details->getLocation().x(), details->getLocation().y());
    }
}

void mouseMoved(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    if(dynamic_cast<WindowEventProducer*>(details->getSource())->getKeyModifiers() &
       KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        mgr->mouseMove(details->getLocation().x(), details->getLocation().y());
    }
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
    preloadSharedObject("OSGImageFileIO");

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
        TutorialWindow->connectMouseReleased(boost::bind(mouseReleased, _1, &sceneManager));
        TutorialWindow->connectMouseMoved(boost::bind(mouseMoved, _1, &sceneManager));
        TutorialWindow->connectMouseDragged(boost::bind(mouseDragged, _1, &sceneManager));
        TutorialWindow->connectMouseWheelMoved(boost::bind(mouseWheelMoved, _1, &sceneManager));
        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1, &sceneManager));

        //Particle System Material
        //point material
        PointChunkRefPtr PSPointChunk = PointChunk::create();
        PSPointChunk->setSize(5.0f);
        PSPointChunk->setSmooth(true);
        BlendChunkRefPtr PSBlendChunk = BlendChunk::create();
        PSBlendChunk->setSrcFactor(GL_SRC_ALPHA);
        PSBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

        MaterialChunkRefPtr PSMaterialChunkChunk = MaterialChunk::create();
        PSMaterialChunkChunk->setAmbient(Color4f(0.3f,0.3f,0.3f,1.0f));
        PSMaterialChunkChunk->setDiffuse(Color4f(0.7f,0.7f,0.7f,1.0f));
        PSMaterialChunkChunk->setSpecular(Color4f(0.9f,0.9f,0.9f,1.0f));
        PSMaterialChunkChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);

        ChunkMaterialRefPtr PSPointMaterial = ChunkMaterial::create();
        PSPointMaterial->addChunk(PSPointChunk);
        PSPointMaterial->addChunk(PSMaterialChunkChunk);
        PSPointMaterial->addChunk(PSBlendChunk);

        //smoke material
        TextureObjChunkRefPtr QuadTextureObjChunk = TextureObjChunk::create();
        ImageRefPtr LoadedImage = ImageFileHandler::the()->read("Data/Smoke.png");    
        QuadTextureObjChunk->setImage(LoadedImage);

        TextureEnvChunkRefPtr QuadTextureEnvChunk = TextureEnvChunk::create();
        QuadTextureEnvChunk->setEnvMode(GL_MODULATE);

        MaterialChunkRefPtr PSMaterialChunk = MaterialChunk::create();
        PSMaterialChunk->setAmbient(Color4f(0.3f,0.3f,0.3f,1.0f));
        PSMaterialChunk->setDiffuse(Color4f(0.7f,0.7f,0.7f,1.0f));
        PSMaterialChunk->setSpecular(Color4f(0.9f,0.9f,0.9f,1.0f));
        PSMaterialChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);

        ChunkMaterialRefPtr PSSmokeMaterial = ChunkMaterial::create();
        PSSmokeMaterial->addChunk(QuadTextureObjChunk);
        PSSmokeMaterial->addChunk(PSMaterialChunk);
        PSSmokeMaterial->addChunk(PSBlendChunk);
        PSSmokeMaterial->addChunk(QuadTextureEnvChunk);


        //Particle System
        //Rocket
        ParticleSystemRecPtr RocketParticleSystem = ParticleSystem::create();
        RocketParticleSystem->attachUpdateProducer(TutorialWindow);

        //smoke
        ParticleSystemRecPtr SmokeParticleSystem = ParticleSystem::create();
        SmokeParticleSystem->attachUpdateProducer(TutorialWindow);
        //Shrapnel
        ParticleSystemRecPtr ShrapnelParticleSystem = ParticleSystem::create();
        ShrapnelParticleSystem->attachUpdateProducer(TutorialWindow);
        //Fireball
        ParticleSystemRecPtr FireballParticleSystem = ParticleSystem::create();
        FireballParticleSystem->attachUpdateProducer(TutorialWindow);



        //Particle System Drawer
        //Rocket does not have a drawer because it is being attached to a special node core
        //Smoke
        QuadParticleSystemDrawerRecPtr SmokeParticleSystemDrawer = QuadParticleSystemDrawer::create();
        //SmokeParticleSystemDrawer->setQuadSizeScaling(Vec2f(0.5f,0.5f));
        //Shrapnel
        PointParticleSystemDrawerRecPtr ExampleShrapnelParticleSystemDrawer = PointParticleSystemDrawer::create();
        ExampleShrapnelParticleSystemDrawer->setForcePerParticleSizing(true);
        //Fireball
        PointParticleSystemDrawerRecPtr ExampleFireballParticleSystemDrawer = PointParticleSystemDrawer::create();
        ExampleFireballParticleSystemDrawer->setForcePerParticleSizing(true);

        //Particle System Node
        //collision node
        //NodeRefPtr EnvironmentNode = makeSphere(2,4.0f);

        Matrix EnvironmentTransformation;
        EnvironmentTransformation.setTranslate(0.0f,0.0f,10.0f);

        TransformRefPtr EnvironmentTransformCore = Transform::create();
        EnvironmentTransformCore->setMatrix(EnvironmentTransformation);

        NodeRefPtr EnvironmentNode = Node::create();
        EnvironmentNode->setCore(EnvironmentTransformCore);
        NodeRefPtr EnvironmentGeoNode = SceneFileHandler::the()->read("Data/house.obj");
        if(EnvironmentGeoNode == NULL)
        {
            EnvironmentGeoNode = makeTorus(.5, 2, 16, 16);
        }
        EnvironmentNode->addChild(EnvironmentGeoNode);

        //NodeRefPtr ParticlePrototypeNode = makeTorus(1.0,4.0,16,16);
        NodeRefPtr RocketParticlePrototypeNode = SceneFileHandler::the()->read("Data/rocket.obj");
        if(RocketParticlePrototypeNode == NULL)
        {
            RocketParticlePrototypeNode = makeTorus(.5, 2, 16, 16);
        }

        NodeParticleSystemCoreRefPtr RocketParticleNodeCore = NodeParticleSystemCore::create();
        RocketParticleNodeCore->setSystem(RocketParticleSystem);
        RocketParticleNodeCore->setPrototypeNode(RocketParticlePrototypeNode);
        RocketParticleNodeCore->setNormalSource(NodeParticleSystemCore::NORMAL_VELOCITY);
        RocketParticleNodeCore->setUpSource(NodeParticleSystemCore::UP_PARTICLE_NORMAL);
        RocketParticleNodeCore->setUp(Vec3f(0.0f,1.0f,0.0f));

        //Geometry Collision Affector
        GeometryCollisionParticleSystemAffectorRefPtr ExampleGeometryCollisionParticleSystemAffector = GeometryCollisionParticleSystemAffector::create();
        ExampleGeometryCollisionParticleSystemAffector->setCollisionNode(EnvironmentNode);

        ExampleGeometryCollisionParticleSystemAffector->connectParticleCollision(boost::bind(particleCollision, _1));

        NodeRefPtr RocketParticleNode = Node::create();
        RocketParticleNode->setCore(RocketParticleNodeCore);

        //Attach the Affector to the Rocket Particle System
        //RocketParticleSystem->pushToAffectors();
        RocketParticleSystem->pushToSystemAffectors(ExampleGeometryCollisionParticleSystemAffector);


        //Smoke
        RateParticleGeneratorRecPtr SmokeGenerator = RateParticleGenerator::create();
        //Attach the function objects to the Generator
        Distribution3DRefPtr SmokePositionDistribution = createSmokePositionDistribution();
        SmokeGenerator->setPositionDistribution(SmokePositionDistribution);
        SmokeGenerator->setLifespanDistribution(createSmokeLifespanDistribution());
        SmokeGenerator->setGenerationRate(50.0);
        SmokeGenerator->setVelocityDistribution(createSmokeVelocityDistribution());
        //Attach the function objects the Affectors
        AgeFadeParticleAffectorRecPtr SmokeAgeFadeParticleAffector = AgeFadeParticleAffector::create();
        SmokeAgeFadeParticleAffector->setFadeInTime(2.0f);
        SmokeAgeFadeParticleAffector->setFadeOutTime(5.0f);
        SmokeAgeFadeParticleAffector->setStartAlpha(0.0f);
        SmokeAgeFadeParticleAffector->setFadeToAlpha(0.2f);
        SmokeAgeFadeParticleAffector->setEndAlpha(0.0f);	

        AgeSizeParticleAffectorRecPtr SmokeAgeSizeParticleAffector = AgeSizeParticleAffector::create();
        //ages
        SmokeAgeSizeParticleAffector->editMFAges()->push_back(0.1);
        SmokeAgeSizeParticleAffector->editMFAges()->push_back(0.2);
        SmokeAgeSizeParticleAffector->editMFAges()->push_back(0.3);
        SmokeAgeSizeParticleAffector->editMFAges()->push_back(0.5);
        SmokeAgeSizeParticleAffector->editMFAges()->push_back(0.7);
        SmokeAgeSizeParticleAffector->editMFAges()->push_back(0.8);
        SmokeAgeSizeParticleAffector->editMFAges()->push_back(1.0);

        //sizes
        SmokeAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(0.5,0.5,0.5));
        SmokeAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(1.0,1.0,1.0));
        SmokeAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(2.0,2.0,2.0));
        SmokeAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(3.0,3.0,3.0));
        SmokeAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(4.0,4.0,4.0));
        SmokeAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(5.0,5.0,5.0));
        SmokeAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(6.5,6.5,6.5));

        ParticleSystemCoreRefPtr SmokeParticleNodeCore = ParticleSystemCore::create();
        SmokeParticleNodeCore->setSystem(SmokeParticleSystem);
        SmokeParticleNodeCore->setDrawer(SmokeParticleSystemDrawer);
        SmokeParticleNodeCore->setMaterial(PSSmokeMaterial);

        NodeRefPtr SmokeParticleNode = Node::create();
        SmokeParticleNode->setCore(SmokeParticleNodeCore);
        //end/////////////////////

        //Shrapnel
        BurstParticleGeneratorRecPtr ShrapnelBurstGenerator = BurstParticleGenerator::create();
        NodeRefPtr ShrapnelParticlePrototypeNode = SceneFileHandler::the()->read("Data/Shrapnel.obj");

        NodeParticleSystemCoreRefPtr ShrapnelParticleNodeCore = NodeParticleSystemCore::create();
        ShrapnelParticleNodeCore->setSystem(ShrapnelParticleSystem);
        ShrapnelParticleNodeCore->setPrototypeNode(ShrapnelParticlePrototypeNode);

        //Attach the function objects to the Generator
        Distribution3DRefPtr ShrapnelPositionDistribution = createShrapnelPositionDistribution();
        ShrapnelBurstGenerator->setPositionDistribution(ShrapnelPositionDistribution);
        ShrapnelBurstGenerator->setLifespanDistribution(createLifespanDistribution());
        ShrapnelBurstGenerator->setBurstAmount(50.0);
        ShrapnelBurstGenerator->setVelocityDistribution(createShrapnelVelocityDistribution());
        ShrapnelBurstGenerator->setAccelerationDistribution(createShrapnelAccelerationDistribution());

        NodeRefPtr ShrapnelParticleNode = Node::create();
        ShrapnelParticleNode->setCore(ShrapnelParticleNodeCore);
        //end/////////////////////

        //fireball
        BurstParticleGeneratorRecPtr FireballGenerator = BurstParticleGenerator::create();
        NodeRefPtr FireballParticlePrototypeNode = SceneFileHandler::the()->read("Data/bubble.obj");

        NodeParticleSystemCoreRefPtr FireballParticleNodeCore = NodeParticleSystemCore::create();
        FireballParticleNodeCore->setSystem(FireballParticleSystem);
        FireballParticleNodeCore->setPrototypeNode(FireballParticlePrototypeNode);
        //Attach the function objects to the Generator
        Distribution3DRefPtr FireballPositionDistribution = createFireballPositionDistribution();
        FireballGenerator->setPositionDistribution(FireballPositionDistribution);
        FireballGenerator->setLifespanDistribution(createFireballLifespanDistribution());
        FireballGenerator->setBurstAmount(100.0);
        FireballGenerator->setVelocityDistribution(createFireballVelocityDistribution());
        FireballGenerator->setAccelerationDistribution(createFireballAccelerationDistribution());
        //Attach the function objects the Affectors
        AgeSizeParticleAffectorRecPtr FireballAgeSizeParticleAffector = AgeSizeParticleAffector::create();
        //ages
        FireballAgeSizeParticleAffector->editMFAges()->push_back(0.1);
        FireballAgeSizeParticleAffector->editMFAges()->push_back(0.2);
        FireballAgeSizeParticleAffector->editMFAges()->push_back(0.3);
        FireballAgeSizeParticleAffector->editMFAges()->push_back(0.5);
        FireballAgeSizeParticleAffector->editMFAges()->push_back(0.7);
        FireballAgeSizeParticleAffector->editMFAges()->push_back(0.8);
        FireballAgeSizeParticleAffector->editMFAges()->push_back(1.0);

        //sizes
        FireballAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(2.0,2.0,2.0));
        FireballAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(2.3,2.3,2.3));
        FireballAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(2.5,2.5,2.5));
        FireballAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(3.0,3.0,3.0));
        FireballAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(4.0,4.0,4.0));
        FireballAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(5.0,5.0,5.0));
        FireballAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(6.5,6.5,6.5));

        NodeRefPtr FireballParticleNode = Node::create();
        FireballParticleNode->setCore(FireballParticleNodeCore);
        //end/////////////////////

        //Attach the Affector to the Smoke Particle System
        SmokeParticleSystem->pushToAffectors(SmokeAgeFadeParticleAffector);
        SmokeParticleSystem->pushToAffectors(SmokeAgeSizeParticleAffector);

        //Attach the Affector to the fireball Particle System
        FireballParticleSystem->pushToAffectors(FireballAgeSizeParticleAffector);

        // Make Main Scene Node 
        NodeRefPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(RocketParticleNode);
        scene->addChild(SmokeParticleNode);
        scene->addChild(ShrapnelParticleNode);
        scene->addChild(FireballParticleNode);
        scene->addChild(EnvironmentNode);

        RocketParticleSystem->connectParticleKilled(boost::bind(particleKilled, _1,
                                                                ShrapnelParticleSystem.get(),
                                                                ShrapnelBurstGenerator.get(),
                                                                SmokeParticleSystem.get(),
                                                                SmokeGenerator.get(),
                                                                FireballParticleSystem.get(),
                                                                FireballGenerator.get()));

        TutorialWindow->connectMousePressed(boost::bind(mousePressed, _1,
                                                        &sceneManager,
                                                        RocketParticleSystem.get()));

        sceneManager.setRoot(scene);

        sceneManager.showAll();
        sceneManager.getCamera()->setNear(0.1f);
        sceneManager.getCamera()->setFar(1000.0f);


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "20RocketLauncher");

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

Distribution3DRefPtr createVelocityDistribution(void)
{
    //Sphere Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(0.0,0.0,-4.5));
    TheLineDistribution->setPoint2(Pnt3f(0.0,0.0,-5.0));

    return TheLineDistribution;
}

Distribution3DRefPtr createSmokePositionDistribution(void)
{
    //Disc Distribution
    DiscDistribution3DRefPtr TheDiscDistribution = DiscDistribution3D::create();
    TheDiscDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheDiscDistribution->setInnerRadius(01.0);
    TheDiscDistribution->setOuterRadius(02.0);
    TheDiscDistribution->setMinTheta(0.0);
    TheDiscDistribution->setMaxTheta(6.283185307);
    TheDiscDistribution->setNormal(Vec3f(0.0,0.0,1.0));
    TheDiscDistribution->setSurfaceOrEdge(DiscDistribution3D::SURFACE);


    return TheDiscDistribution;
}

Distribution1DRefPtr createSmokeLifespanDistribution(void)
{
    GaussianNormalDistribution1DRefPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    TheLifespanDistribution->setMean(5.0f);
    TheLifespanDistribution->setStandardDeviation(0.5);

    return TheLifespanDistribution;
}

Distribution3DRefPtr createSmokeVelocityDistribution(void)
{
    //Sphere Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(0.0,1.0,1.0));
    TheLineDistribution->setPoint2(Pnt3f(0.0,1.0,3.0));

    return TheLineDistribution;
}
Distribution3DRefPtr createShrapnelPositionDistribution(void)
{
    //Sphere Distribution
    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(0.0);
    TheSphereDistribution->setOuterRadius(3.0);
    TheSphereDistribution->setMinTheta(0.0);
    TheSphereDistribution->setMaxTheta(6.283185);
    TheSphereDistribution->setMinZ(-1.0);
    TheSphereDistribution->setMaxZ(1.0);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::SURFACE);

    return TheSphereDistribution;
}
Distribution3DRefPtr createShrapnelAccelerationDistribution(void)
{

    //Sphere Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(0.0,0.0,-3.0));
    TheLineDistribution->setPoint2(Pnt3f(0.0,0.0,-3.0));

    return TheLineDistribution;
} 
Distribution3DRefPtr createShrapnelVelocityDistribution(void)
{


    //Sphere Distribution
    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(3.0);
    TheSphereDistribution->setOuterRadius(10.0);
    TheSphereDistribution->setMinTheta(-3.141950);
    TheSphereDistribution->setMaxTheta(3.141950);
    TheSphereDistribution->setMinZ(-1.0);
    TheSphereDistribution->setMaxZ(1.0);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::VOLUME);

    return TheSphereDistribution;
}

Distribution3DRefPtr createFireballVelocityDistribution(void)
{
    //Sphere Distribution
    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(3.0);
    TheSphereDistribution->setOuterRadius(5.0);
    TheSphereDistribution->setMinTheta(-3.141950);
    TheSphereDistribution->setMaxTheta(3.141950);
    TheSphereDistribution->setMinZ(-1.0);
    TheSphereDistribution->setMaxZ(1.0);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::VOLUME);

    return TheSphereDistribution;
}
Distribution3DRefPtr createFireballPositionDistribution(void)
{
    //Sphere Distribution
    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(1.0);
    TheSphereDistribution->setOuterRadius(2.0);
    TheSphereDistribution->setMinTheta(0.0);
    TheSphereDistribution->setMaxTheta(6.283185);
    TheSphereDistribution->setMinZ(-1.0);
    TheSphereDistribution->setMaxZ(1.0);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::SURFACE);

    return TheSphereDistribution;
}

Distribution3DRefPtr createFireballAccelerationDistribution(void)
{

    //Sphere Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(0.0,0.0,1.0));
    TheLineDistribution->setPoint2(Pnt3f(0.0,0.0,1.0));

    return TheLineDistribution;
} 
Distribution1DRefPtr createFireballLifespanDistribution(void)
{
    GaussianNormalDistribution1DRefPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    TheLifespanDistribution->setMean(3.0f);
    TheLifespanDistribution->setStandardDeviation(0.5);

    return TheLifespanDistribution;
}
