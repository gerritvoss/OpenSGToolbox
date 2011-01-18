// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"
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

#include "OSGRateParticleGenerator.h"
#include "OSGBurstParticleGenerator.h"

#include "OSGLineDistribution3D.h"
#include "OSGCylinderDistribution3D.h"
#include "OSGGaussianNormalDistribution1D.h"
#include "OSGDiscDistribution3D.h"
#include "OSGSphereDistribution3D.h"

#include "OSGRandomPoolManager.h"
// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

Distribution3DRefPtr createPositionDistribution(void);
Distribution1DRefPtr createLifespanDistribution(void);
Distribution3DRefPtr createSmokeVelocityDistribution(void);
Distribution1DRefPtr createSmokeLifespanDistribution(void);
Distribution3DRefPtr createSmokePositionDistribution(void);
Distribution3DRefPtr createSmokeColorDistribution(void);
Distribution3DRefPtr createStarVelocityDistribution(void);
Distribution1DRefPtr createStarLifespanDistribution(void);
Distribution3DRefPtr createStarPositionDistribution(void);
Distribution3DRefPtr createComStarVelocityDistribution(void);
Distribution1DRefPtr createComStarLifespanDistribution(void);
Distribution3DRefPtr createComStarPositionDistribution(void);
Distribution3DRefPtr createComStarColorDistribution(void);

Distribution3DRefPtr createComStar2VelocityDistribution(void);
Distribution3DRefPtr createComStar2PositionDistribution(void);
Distribution3DRefPtr createSmoke2PositionDistribution(void);
Distribution3DRefPtr createSmoke2VelocityDistribution(void);
Distribution3DRefPtr createStar2VelocityDistribution(void);
Distribution3DRefPtr createStar2PositionDistribution(void);
Distribution3DRefPtr createExplosionPositionDistribution(void);
Distribution3DRefPtr createExplosionVelocityDistribution(void);
Distribution3DRefPtr createExplosion2PositionDistribution(void);
Distribution3DRefPtr createExplosion2VelocityDistribution(void);
Distribution3DRefPtr createExplosion2ColorDistribution(void);

void particleKilled(ParticleEventDetails* const details,
                    ParticleSystem* const CircleParticleSystem,
                    BurstParticleGenerator* const CircleBurstGenerator,
                    ParticleSystem* const StarParticleSystem,
                    BurstParticleGenerator* const StarBurstGenerator,
                    ParticleSystem* const ComStarParticleSystem,
                    BurstParticleGenerator* const ComStarBurstGenerator)
{
    //Int32 CheckSystem = RandomPoolManager::getRandomInt32(1,4);
    //if(CheckSystem == 1)
    //{

    dynamic_cast<SphereDistribution3D*>(CircleBurstGenerator->getPositionDistribution())->setCenter(details->getParticlePosition());

    dynamic_cast<SphereDistribution3D*>(StarBurstGenerator->getPositionDistribution())->setCenter(details->getParticlePosition());

    dynamic_cast<SphereDistribution3D*>(ComStarBurstGenerator->getPositionDistribution())->setCenter(details->getParticlePosition());

    //Attach the Generator to the Circle Particle System
    CircleParticleSystem->pushToGenerators(CircleBurstGenerator);
    //Attach the Generator to the Star Particle System
    StarParticleSystem->pushToGenerators(StarBurstGenerator);
    //Attach the Generator to the ComStar Particle System
    ComStarParticleSystem->pushToGenerators(ComStarBurstGenerator);
    //}
    //else if(CheckSystem == 2)
    //{
    //dynamic_pointer_cast<SphereDistribution3D>(Circle2PositionDistribution)->setCenter(details->getParticlePosition());

    //dynamic_pointer_cast<SphereDistribution3D>(Star2PositionDistribution)->setCenter(details->getParticlePosition());

    //dynamic_pointer_cast<SphereDistribution3D>(ComStar2PositionDistribution)->setCenter(details->getParticlePosition());

    ////Attach the Affector to the Circle2 Particle System
    //Circle2ParticleSystem->pushToGenerators(Circle2BurstGenerator);
    ////Attach the Affector to the Star2 Particle System
    //Star2ParticleSystem->pushToGenerators(Star2BurstGenerator);
    ////Attach the Affector to the ComStar2 Particle System
    //ComStar2ParticleSystem->pushToGenerators(ComStar2BurstGenerator);

    //}
    //else if(CheckSystem == 3)
    //{
    //dynamic_pointer_cast<SphereDistribution3D>(ExplosionPositionDistribution)->setCenter(details->getParticlePosition());

    ////Attach the Affector to the explosion Particle System
    //ExplosionParticleSystem->pushToGenerators(ExplosionBurstGenerator);
    //}
    //else if(CheckSystem == 4)
    //{
    //dynamic_pointer_cast<DiscDistribution3D>(Explosion2PositionDistribution)->setCenter(details->getParticlePosition());

    ////Attach the Affector to the explosion Particle System
    //Explosion2ParticleSystem->pushToGenerators(Explosion2BurstGenerator);

    //}
}

void particleKilled2(ParticleEventDetails* const details,
                     ParticleSystem* const StarParticleSystem,
                     BurstParticleGenerator* const StarBurstGenerator,
                     ParticleSystem* const ComStarParticleSystem,
                     BurstParticleGenerator* const ComStarBurstGenerator)
{
    dynamic_cast<SphereDistribution3D*>(StarBurstGenerator->getPositionDistribution())->setCenter(details->getParticlePosition());
    dynamic_cast<SphereDistribution3D*>(ComStarBurstGenerator->getPositionDistribution())->setCenter(details->getParticlePosition());

    StarParticleSystem->pushToGenerators(StarBurstGenerator);
    ComStarParticleSystem->pushToGenerators(ComStarBurstGenerator);
}

void keyTyped(KeyEventDetails* const details)
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
    if(dynamic_cast<WindowEventProducer*>(details->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
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
                                              Vec3f(0.0,0.0f,1.0f),
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
    if(dynamic_cast<WindowEventProducer*>(details->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        mgr->mouseButtonRelease(details->getButton(), details->getLocation().x(), details->getLocation().y());
    }
}

void mouseMoved(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    if(dynamic_cast<WindowEventProducer*>(details->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        mgr->mouseMove(details->getLocation().x(), details->getLocation().y());
    }
}

void mouseDragged(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    if(dynamic_cast<WindowEventProducer*>(details->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        mgr->mouseMove(details->getLocation().x(), details->getLocation().y());
    }
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
        TutorialWindow->connectMouseReleased(boost::bind(mouseReleased, _1, &sceneManager));
        TutorialWindow->connectMouseMoved(boost::bind(mouseMoved, _1, &sceneManager));
        TutorialWindow->connectMouseDragged(boost::bind(mouseDragged, _1, &sceneManager));
        TutorialWindow->connectMouseWheelMoved(boost::bind(mouseWheelMoved, _1, &sceneManager));
        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1));

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
        PSMaterialChunkChunk->setDiffuse(Color4f(1.0f,1.0f,1.0f,1.0f));
        PSMaterialChunkChunk->setSpecular(Color4f(0.0f,0.0f,0.0f,1.0f));
        PSMaterialChunkChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);

        ChunkMaterialRefPtr PSPointMaterial = ChunkMaterial::create();
        PSPointMaterial->addChunk(PSPointChunk);
        PSPointMaterial->addChunk(PSMaterialChunkChunk);
        PSPointMaterial->addChunk(PSBlendChunk);

        //Rocket material
        TextureObjChunkRefPtr RocketQuadTextureObjChunk = TextureObjChunk::create();
        ImageRefPtr SmokeImage = ImageFileHandler::the()->read("Data/Smoke.png");    
        RocketQuadTextureObjChunk->setImage(SmokeImage);

        TextureEnvChunkRefPtr QuadTextureEnvChunk = TextureEnvChunk::create();
        QuadTextureEnvChunk->setEnvMode(GL_MODULATE);

        MaterialChunkRefPtr PSRocketMaterialChunk = MaterialChunk::create();
        PSRocketMaterialChunk->setAmbient(Color4f(1.0f,1.0f,1.0f,1.0f));
        PSRocketMaterialChunk->setDiffuse(Color4f(1.0f,1.0f,1.0f,1.0f));
        PSRocketMaterialChunk->setSpecular(Color4f(0.0f,0.0f,0.0f,1.0f));
        PSRocketMaterialChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);

        ChunkMaterialRefPtr PSRocketMaterial = ChunkMaterial::create();
        PSRocketMaterial->addChunk(RocketQuadTextureObjChunk);
        PSRocketMaterial->addChunk(PSRocketMaterialChunk);
        PSRocketMaterial->addChunk(QuadTextureEnvChunk);
        PSRocketMaterial->addChunk(PSBlendChunk);

        //circle material
        TextureObjChunkRefPtr CircleQuadTextureObjChunk = TextureObjChunk::create();
        CircleQuadTextureObjChunk->setImage(SmokeImage);

        MaterialChunkRefPtr PSCircleMaterialChunk = MaterialChunk::create();
        PSCircleMaterialChunk->setAmbient(Color4f(1.0f,1.0f,1.0f,1.0f));
        PSCircleMaterialChunk->setDiffuse(Color4f(1.0f,1.0f,1.0f,1.0f));
        PSCircleMaterialChunk->setSpecular(Color4f(0.0f,0.0f,0.0f,1.0f));
        PSCircleMaterialChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);

        ChunkMaterialRefPtr PSCircleMaterial = ChunkMaterial::create();
        PSCircleMaterial->addChunk(CircleQuadTextureObjChunk);
        PSCircleMaterial->addChunk(PSCircleMaterialChunk);
        PSCircleMaterial->addChunk(PSBlendChunk);
        PSCircleMaterial->addChunk(QuadTextureEnvChunk);

        //star material
        TextureObjChunkRefPtr StarQuadTextureObjChunk = TextureObjChunk::create();
        StarQuadTextureObjChunk->setImage(SmokeImage);

        MaterialChunkRefPtr PSStarMaterialChunk = MaterialChunk::create();
        PSStarMaterialChunk->setAmbient(Color4f(1.0f,1.0f,1.0f,1.0f));
        PSStarMaterialChunk->setDiffuse(Color4f(1.0f,1.0f,1.0f,1.0f));
        PSStarMaterialChunk->setSpecular(Color4f(0.0f,0.0f,0.0f,1.0f));
        PSStarMaterialChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);

        ChunkMaterialRefPtr PSStarMaterial = ChunkMaterial::create();
        PSStarMaterial->addChunk(StarQuadTextureObjChunk);
        PSStarMaterial->addChunk(PSStarMaterialChunk);
        PSStarMaterial->addChunk(PSBlendChunk);
        PSStarMaterial->addChunk(QuadTextureEnvChunk);

        //ComStar material
        BlendChunkRefPtr ComStarBlendChunk = BlendChunk::create();
        ComStarBlendChunk->setSrcFactor(GL_SRC_ALPHA);
        ComStarBlendChunk->setDestFactor(GL_ONE);

        TextureObjChunkRefPtr ComStarQuadTextureObjChunk = TextureObjChunk::create();
        ComStarQuadTextureObjChunk->setImage(SmokeImage);

        MaterialChunkRefPtr PSComStarMaterialChunk = MaterialChunk::create();
        PSComStarMaterialChunk->setAmbient(Color4f(1.0f,1.0f,1.0f,1.0f));
        PSComStarMaterialChunk->setDiffuse(Color4f(1.0f,1.0f,1.0f,1.0f));
        PSComStarMaterialChunk->setSpecular(Color4f(0.0f,0.0f,0.0f,1.0f));
        PSComStarMaterialChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);

        ChunkMaterialRefPtr PSComStarMaterial = ChunkMaterial::create();
        PSComStarMaterial->addChunk(ComStarQuadTextureObjChunk);
        PSComStarMaterial->addChunk(PSComStarMaterialChunk);
        PSComStarMaterial->addChunk(ComStarBlendChunk);
        PSComStarMaterial->addChunk(QuadTextureEnvChunk);

        //exposion material
        TextureObjChunkRefPtr ExplosionQuadTextureObjChunk = TextureObjChunk::create();
        ExplosionQuadTextureObjChunk->setImage(SmokeImage);

        MaterialChunkRefPtr PSExplosionMaterialChunk = MaterialChunk::create();
        PSExplosionMaterialChunk->setAmbient(Color4f(1.0f,1.0f,1.0f,1.0f));
        PSExplosionMaterialChunk->setDiffuse(Color4f(1.0f,1.0f,1.0f,1.0f));
        PSExplosionMaterialChunk->setSpecular(Color4f(0.0f,0.0f,0.0f,1.0f));
        PSExplosionMaterialChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);

        ChunkMaterialRefPtr PSExplosionMaterial = ChunkMaterial::create();
        PSExplosionMaterial->addChunk(ExplosionQuadTextureObjChunk);
        PSExplosionMaterial->addChunk(PSExplosionMaterialChunk);
        PSExplosionMaterial->addChunk(PSBlendChunk);
        PSExplosionMaterial->addChunk(QuadTextureEnvChunk);

        //exposion2 material
        TextureObjChunkRefPtr Explosion2QuadTextureObjChunk = TextureObjChunk::create();
        Explosion2QuadTextureObjChunk->setImage(SmokeImage);

        MaterialChunkRefPtr PSExplosion2MaterialChunk = MaterialChunk::create();
        PSExplosion2MaterialChunk->setAmbient(Color4f(1.0f,1.0f,1.0f,1.0f));
        PSExplosion2MaterialChunk->setDiffuse(Color4f(1.0f,1.0f,1.0f,1.0f));
        PSExplosion2MaterialChunk->setSpecular(Color4f(0.0f,0.0f,0.0f,1.0f));
        PSExplosion2MaterialChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);

        ChunkMaterialRefPtr PSExplosion2Material = ChunkMaterial::create();
        PSExplosion2Material->addChunk(Explosion2QuadTextureObjChunk);
        PSExplosion2Material->addChunk(PSExplosion2MaterialChunk);
        PSExplosion2Material->addChunk(PSBlendChunk);
        PSExplosion2Material->addChunk(QuadTextureEnvChunk);

        //Particle System
        //Rocket
        ParticleSystemRecPtr RocketParticleSystem = ParticleSystem::create();
        RocketParticleSystem->attachUpdateProducer(TutorialWindow);

        //Circle
        ParticleSystemRecPtr CircleParticleSystem = ParticleSystem::create();
        CircleParticleSystem->attachUpdateProducer(TutorialWindow);

        //Star
        ParticleSystemRecPtr StarParticleSystem = ParticleSystem::create();
        StarParticleSystem->attachUpdateProducer(TutorialWindow);

        //ComStar
        ParticleSystemRecPtr ComStarParticleSystem = ParticleSystem::create();
        ComStarParticleSystem->attachUpdateProducer(TutorialWindow);


        ParticleSystemRecPtr ExplosionParticleSystem = ParticleSystem::create();
        ExplosionParticleSystem->attachUpdateProducer(TutorialWindow);

        ParticleSystemRecPtr Explosion2ParticleSystem = ParticleSystem::create();
        Explosion2ParticleSystem->attachUpdateProducer(TutorialWindow);


        //Particle System Drawer
        //Rocket
        QuadParticleSystemDrawerRecPtr RocketParticleSystemDrawer = QuadParticleSystemDrawer::create();
        //Circle
        QuadParticleSystemDrawerRecPtr CircleParticleSystemDrawer = QuadParticleSystemDrawer::create();
        //CircleParticleSystemDrawer->setQuadSizeScaling(Vec2f(0.5f,0.5f));

        //Star
        QuadParticleSystemDrawerRecPtr StarParticleSystemDrawer = QuadParticleSystemDrawer::create();

        //ComStar
        QuadParticleSystemDrawerRecPtr ComStarParticleSystemDrawer = QuadParticleSystemDrawer::create();

        //Explosion
        QuadParticleSystemDrawerRecPtr ExplosionParticleSystemDrawer = QuadParticleSystemDrawer::create();
        //Explosion2
        QuadParticleSystemDrawerRecPtr Explosion2ParticleSystemDrawer = QuadParticleSystemDrawer::create();

        ////////////////2ND GROUP///////////////
        //Circle
        ParticleSystemRecPtr Circle2ParticleSystem = ParticleSystem::create();
        Circle2ParticleSystem->attachUpdateProducer(TutorialWindow);

        //Star
        ParticleSystemRecPtr Star2ParticleSystem = ParticleSystem::create();
        Star2ParticleSystem->attachUpdateProducer(TutorialWindow);

        //ComStar
        ParticleSystemRecPtr ComStar2ParticleSystem = ParticleSystem::create();
        ComStar2ParticleSystem->attachUpdateProducer(TutorialWindow);



        //Particle System Drawer
        //Circle2
        QuadParticleSystemDrawerRecPtr Circle2ParticleSystemDrawer = QuadParticleSystemDrawer::create();
        //CircleParticleSystemDrawer->setQuadSizeScaling(Vec2f(0.5f,0.5f));

        //Star2
        QuadParticleSystemDrawerRecPtr Star2ParticleSystemDrawer = QuadParticleSystemDrawer::create();

        //ComStar2
        QuadParticleSystemDrawerRecPtr ComStar2ParticleSystemDrawer = QuadParticleSystemDrawer::create();




        //Particle System Node    

        ParticleSystemCoreRefPtr RocketParticleNodeCore = ParticleSystemCore::create();
        RocketParticleNodeCore->setSystem(RocketParticleSystem);
        RocketParticleNodeCore->setDrawer(RocketParticleSystemDrawer);
        RocketParticleNodeCore->setMaterial(PSRocketMaterial);

        NodeRefPtr RocketParticleNode = Node::create();
        RocketParticleNode->setCore(RocketParticleNodeCore);

        DistanceKillParticleAffectorRefPtr RocketDistanceKillParticleAffector = DistanceKillParticleAffector::create();
        RocketDistanceKillParticleAffector->setKillDistance(100.0f);
        RocketDistanceKillParticleAffector->setParticleSystemNode(RocketParticleNode);
        RocketDistanceKillParticleAffector->setDistanceFromSource(DistanceKillParticleAffector::DISTANCE_FROM_CAMERA);
        RocketDistanceKillParticleAffector->setDistanceFromCamera(sceneManager.getCamera());
        //Attach the Affector to the Rocket Particle System
        RocketParticleSystem->pushToAffectors(RocketDistanceKillParticleAffector);


        //end/////////////////////

        //Circle
        BurstParticleGeneratorRecPtr CircleBurstGenerator = BurstParticleGenerator::create();
        //Attach the function objects to the Generator
        Distribution3DRefPtr CirclePositionDistribution = createSmokePositionDistribution();
        CircleBurstGenerator->setPositionDistribution(CirclePositionDistribution);
        CircleBurstGenerator->setLifespanDistribution(createSmokeLifespanDistribution());
        CircleBurstGenerator->setBurstAmount(50.0);
        CircleBurstGenerator->setVelocityDistribution(createSmokeVelocityDistribution());
        CircleBurstGenerator->setColorDistribution(createSmokeColorDistribution());

        //Attach the function objects the Affectors
        AgeFadeParticleAffectorRecPtr CircleAgeFadeParticleAffector = AgeFadeParticleAffector::create();
        CircleAgeFadeParticleAffector->setFadeInTime(0.8f);
        CircleAgeFadeParticleAffector->setFadeOutTime(1.5f);
        CircleAgeFadeParticleAffector->setStartAlpha(0.0f);
        CircleAgeFadeParticleAffector->setFadeToAlpha(1.0f);
        CircleAgeFadeParticleAffector->setEndAlpha(0.0f);	

        AgeSizeParticleAffectorRecPtr CircleAgeSizeParticleAffector = AgeSizeParticleAffector::create();
        //ages
        CircleAgeSizeParticleAffector->editMFAges()->push_back(0.1);
        CircleAgeSizeParticleAffector->editMFAges()->push_back(0.2);
        CircleAgeSizeParticleAffector->editMFAges()->push_back(0.3);
        CircleAgeSizeParticleAffector->editMFAges()->push_back(0.4);
        CircleAgeSizeParticleAffector->editMFAges()->push_back(0.5);
        CircleAgeSizeParticleAffector->editMFAges()->push_back(0.6);
        CircleAgeSizeParticleAffector->editMFAges()->push_back(0.7);
        CircleAgeSizeParticleAffector->editMFAges()->push_back(0.8);
        CircleAgeSizeParticleAffector->editMFAges()->push_back(1.0);

        //sizes
        CircleAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(0.5,0.5,0.5));
        CircleAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(1.0,1.0,1.0));
        CircleAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(2.0,2.0,2.0));
        CircleAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(2.5,2.5,2.5));
        CircleAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(3.0,3.0,3.0));
        CircleAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(3.5,3.5,3.5));
        CircleAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(4.0,4.0,4.0));
        CircleAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(5.0,5.0,5.0));
        CircleAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(6.5,6.5,6.5));
        //Attach the Affector to the Circle Particle System
        CircleParticleSystem->pushToAffectors(CircleAgeFadeParticleAffector);
        CircleParticleSystem->pushToAffectors(CircleAgeSizeParticleAffector);

        ParticleSystemCoreRefPtr CircleParticleNodeCore = ParticleSystemCore::create();
        CircleParticleNodeCore->setSystem(CircleParticleSystem);
        CircleParticleNodeCore->setDrawer(CircleParticleSystemDrawer);
        CircleParticleNodeCore->setMaterial(PSCircleMaterial);

        NodeRefPtr CircleParticleNode = Node::create();
        CircleParticleNode->setCore(CircleParticleNodeCore);
        //end/////////////////////

        //Star
        BurstParticleGeneratorRecPtr StarBurstGenerator = BurstParticleGenerator::create();
        //Attach the function objects to the Generator
        Distribution3DRefPtr StarPositionDistribution = createStarPositionDistribution();
        StarBurstGenerator->setPositionDistribution(StarPositionDistribution);
        StarBurstGenerator->setLifespanDistribution(createSmokeLifespanDistribution());
        StarBurstGenerator->setBurstAmount(50.0);
        StarBurstGenerator->setVelocityDistribution(createStarVelocityDistribution());
        //StarBurstGenerator->setAccelerationDistribution(createShrapnelAccelerationDistribution());

        //Attach the function objects the Affectors
        AgeFadeParticleAffectorRecPtr StarAgeFadeParticleAffector = AgeFadeParticleAffector::create();
        StarAgeFadeParticleAffector->setFadeInTime(1.0f);
        StarAgeFadeParticleAffector->setFadeOutTime(2.0f);
        StarAgeFadeParticleAffector->setStartAlpha(0.0f);
        StarAgeFadeParticleAffector->setFadeToAlpha(1.0f);
        StarAgeFadeParticleAffector->setEndAlpha(0.0f);	

        AgeSizeParticleAffectorRecPtr StarAgeSizeParticleAffector = AgeSizeParticleAffector::create();
        //ages
        StarAgeSizeParticleAffector->editMFAges()->push_back(0.1);
        StarAgeSizeParticleAffector->editMFAges()->push_back(0.2);
        StarAgeSizeParticleAffector->editMFAges()->push_back(0.3);
        StarAgeSizeParticleAffector->editMFAges()->push_back(0.4);
        StarAgeSizeParticleAffector->editMFAges()->push_back(0.5);
        StarAgeSizeParticleAffector->editMFAges()->push_back(0.6);
        StarAgeSizeParticleAffector->editMFAges()->push_back(0.7);
        StarAgeSizeParticleAffector->editMFAges()->push_back(0.8);
        StarAgeSizeParticleAffector->editMFAges()->push_back(1.0);

        //sizes
        StarAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(0.5,0.5,0.5));
        StarAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(1.0,1.0,1.0));
        StarAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(2.0,2.0,2.0));
        StarAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(2.5,2.5,2.5));
        StarAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(3.0,3.0,3.0));
        StarAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(3.5,3.5,3.5));
        StarAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(4.0,4.0,4.0));
        StarAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(5.0,5.0,5.0));
        StarAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(6.5,6.5,6.5));


        //Attach the Affector to the Star Particle System
        StarParticleSystem->pushToAffectors(StarAgeSizeParticleAffector);
        StarParticleSystem->pushToAffectors(StarAgeFadeParticleAffector);

        ParticleSystemCoreRefPtr StarParticleNodeCore = ParticleSystemCore::create();
        StarParticleNodeCore->setSystem(StarParticleSystem);
        StarParticleNodeCore->setDrawer(StarParticleSystemDrawer);
        StarParticleNodeCore->setMaterial(PSStarMaterial);

        NodeRefPtr StarParticleNode = Node::create();
        StarParticleNode->setCore(StarParticleNodeCore);
        //end/////////////////////

        //ComStar
        BurstParticleGeneratorRecPtr ComStarBurstGenerator = BurstParticleGenerator::create();
        //Attach the function objects to the Generator
        Distribution3DRefPtr ComStarPositionDistribution = createComStarPositionDistribution();
        ComStarBurstGenerator->setPositionDistribution(ComStarPositionDistribution);
        ComStarBurstGenerator->setLifespanDistribution(createSmokeLifespanDistribution());
        ComStarBurstGenerator->setBurstAmount(50.0);
        ComStarBurstGenerator->setVelocityDistribution(createComStarVelocityDistribution());
        ComStarBurstGenerator->setColorDistribution(createComStarColorDistribution());

        //Attach the function objects the Affectors
        AgeFadeParticleAffectorRecPtr ComStarAgeFadeParticleAffector = AgeFadeParticleAffector::create();
        ComStarAgeFadeParticleAffector->setFadeInTime(1.0f);
        ComStarAgeFadeParticleAffector->setFadeOutTime(2.0f);
        ComStarAgeFadeParticleAffector->setStartAlpha(0.0f);
        ComStarAgeFadeParticleAffector->setFadeToAlpha(1.0f);
        ComStarAgeFadeParticleAffector->setEndAlpha(0.0f);	

        AgeSizeParticleAffectorRecPtr ComStarAgeSizeParticleAffector = AgeSizeParticleAffector::create();
        //ages
        ComStarAgeSizeParticleAffector->editMFAges()->push_back(0.1);
        ComStarAgeSizeParticleAffector->editMFAges()->push_back(0.2);
        ComStarAgeSizeParticleAffector->editMFAges()->push_back(0.3);
        ComStarAgeSizeParticleAffector->editMFAges()->push_back(0.4);
        ComStarAgeSizeParticleAffector->editMFAges()->push_back(0.5);
        ComStarAgeSizeParticleAffector->editMFAges()->push_back(0.6);
        ComStarAgeSizeParticleAffector->editMFAges()->push_back(0.7);
        ComStarAgeSizeParticleAffector->editMFAges()->push_back(0.8);
        ComStarAgeSizeParticleAffector->editMFAges()->push_back(1.0);

        //sizes
        ComStarAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(0.5,0.5,0.5));
        ComStarAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(1.0,1.0,1.0));
        ComStarAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(2.0,2.0,2.0));
        ComStarAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(2.5,2.5,2.5));
        ComStarAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(3.0,3.0,3.0));
        ComStarAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(3.5,3.5,3.5));
        ComStarAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(4.0,4.0,4.0));
        ComStarAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(5.0,5.0,5.0));
        ComStarAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(6.5,6.5,6.5));
        //Attach the Affector to the ComStar Particle System
        ComStarParticleSystem->pushToAffectors(ComStarAgeFadeParticleAffector);
        ComStarParticleSystem->pushToAffectors(ComStarAgeSizeParticleAffector);

        ParticleSystemCoreRefPtr ComStarParticleNodeCore = ParticleSystemCore::create();
        ComStarParticleNodeCore->setSystem(ComStarParticleSystem);
        ComStarParticleNodeCore->setDrawer(ComStarParticleSystemDrawer);
        ComStarParticleNodeCore->setMaterial(PSComStarMaterial);

        NodeRefPtr ComStarParticleNode = Node::create();
        ComStarParticleNode->setCore(ComStarParticleNodeCore);
        //end/////////////////////

        //Explosion
        BurstParticleGeneratorRecPtr ExplosionBurstGenerator = BurstParticleGenerator::create();
        //Attach the function objects to the Generator
        Distribution3DRefPtr ExplosionPositionDistribution = createExplosionPositionDistribution();
        ExplosionBurstGenerator->setPositionDistribution(ExplosionPositionDistribution);
        ExplosionBurstGenerator->setLifespanDistribution(createSmokeLifespanDistribution());
        ExplosionBurstGenerator->setBurstAmount(15.0);
        ExplosionBurstGenerator->setVelocityDistribution(createExplosionVelocityDistribution());
        ExplosionBurstGenerator->setColorDistribution(createSmokeColorDistribution());

        //Attach the function objects the Affectors
        AgeFadeParticleAffectorRecPtr ExplosionAgeFadeParticleAffector = AgeFadeParticleAffector::create();
        ExplosionAgeFadeParticleAffector->setFadeInTime(1.0f);
        ExplosionAgeFadeParticleAffector->setFadeOutTime(2.0f);
        ExplosionAgeFadeParticleAffector->setStartAlpha(0.0f);
        ExplosionAgeFadeParticleAffector->setFadeToAlpha(0.1f);
        ExplosionAgeFadeParticleAffector->setEndAlpha(0.0f);	

        AgeSizeParticleAffectorRecPtr ExplosionAgeSizeParticleAffector = AgeSizeParticleAffector::create();
        //ages
        ExplosionAgeSizeParticleAffector->editMFAges()->push_back(0.1);
        ExplosionAgeSizeParticleAffector->editMFAges()->push_back(0.2);
        ExplosionAgeSizeParticleAffector->editMFAges()->push_back(0.3);
        ExplosionAgeSizeParticleAffector->editMFAges()->push_back(0.4);
        ExplosionAgeSizeParticleAffector->editMFAges()->push_back(0.5);
        ExplosionAgeSizeParticleAffector->editMFAges()->push_back(0.6);
        ExplosionAgeSizeParticleAffector->editMFAges()->push_back(0.7);
        ExplosionAgeSizeParticleAffector->editMFAges()->push_back(0.8);
        ExplosionAgeSizeParticleAffector->editMFAges()->push_back(1.0);

        //sizes
        ExplosionAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(0.5,0.5,0.5));
        ExplosionAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(1.0,1.0,1.0));
        ExplosionAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(2.0,2.0,2.0));
        ExplosionAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(2.5,2.5,2.5));
        ExplosionAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(3.0,3.0,3.0));
        ExplosionAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(3.5,3.5,3.5));
        ExplosionAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(4.0,4.0,4.0));
        ExplosionAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(5.0,5.0,5.0));
        ExplosionAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(6.5,6.5,6.5));


        //Attach the Affector to the Explosion Particle System
        ExplosionParticleSystem->pushToAffectors(ExplosionAgeFadeParticleAffector);

        ParticleSystemCoreRefPtr ExplosionParticleNodeCore = ParticleSystemCore::create();
        ExplosionParticleNodeCore->setSystem(ExplosionParticleSystem);
        ExplosionParticleNodeCore->setDrawer(ExplosionParticleSystemDrawer);
        ExplosionParticleNodeCore->setMaterial(PSExplosionMaterial);

        NodeRefPtr ExplosionParticleNode = Node::create();
        ExplosionParticleNode->setCore(ExplosionParticleNodeCore);
        //end/////////////////////

        //Explosion2
        BurstParticleGeneratorRecPtr Explosion2BurstGenerator = BurstParticleGenerator::create();
        //Attach the function objects to the Generator
        Distribution3DRefPtr Explosion2PositionDistribution = createExplosion2PositionDistribution();
        Explosion2BurstGenerator->setPositionDistribution(Explosion2PositionDistribution);
        Explosion2BurstGenerator->setLifespanDistribution(createSmokeLifespanDistribution());
        Explosion2BurstGenerator->setBurstAmount(15.0);
        Explosion2BurstGenerator->setVelocityDistribution(createExplosion2VelocityDistribution());
        Explosion2BurstGenerator->setColorDistribution(createExplosion2ColorDistribution());

        //Attach the function objects the Affectors
        AgeFadeParticleAffectorRecPtr Explosion2AgeFadeParticleAffector = AgeFadeParticleAffector::create();
        Explosion2AgeFadeParticleAffector->setFadeInTime(1.0f);
        Explosion2AgeFadeParticleAffector->setFadeOutTime(2.0f);
        Explosion2AgeFadeParticleAffector->setStartAlpha(0.0f);
        Explosion2AgeFadeParticleAffector->setFadeToAlpha(1.0f);
        Explosion2AgeFadeParticleAffector->setEndAlpha(0.0f);	

        AgeSizeParticleAffectorRecPtr Explosion2AgeSizeParticleAffector = AgeSizeParticleAffector::create();
        //ages
        Explosion2AgeSizeParticleAffector->editMFAges()->push_back(0.1);
        Explosion2AgeSizeParticleAffector->editMFAges()->push_back(0.2);
        Explosion2AgeSizeParticleAffector->editMFAges()->push_back(0.3);
        Explosion2AgeSizeParticleAffector->editMFAges()->push_back(0.4);
        Explosion2AgeSizeParticleAffector->editMFAges()->push_back(0.5);
        Explosion2AgeSizeParticleAffector->editMFAges()->push_back(0.6);
        Explosion2AgeSizeParticleAffector->editMFAges()->push_back(0.7);
        Explosion2AgeSizeParticleAffector->editMFAges()->push_back(0.8);
        Explosion2AgeSizeParticleAffector->editMFAges()->push_back(1.0);

        //sizes
        Explosion2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(0.5,0.5,0.5));
        Explosion2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(1.0,1.0,1.0));
        Explosion2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(2.0,2.0,2.0));
        Explosion2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(2.5,2.5,2.5));
        Explosion2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(3.0,3.0,3.0));
        Explosion2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(3.5,3.5,3.5));
        Explosion2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(4.0,4.0,4.0));
        Explosion2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(5.0,5.0,5.0));
        Explosion2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(6.5,6.5,6.5));


        //Attach the Affector to the Explosion2 Particle System
        //	Explosion2ParticleSystem->pushToAffectors(Explosion2AgeSizeParticleAffector);

        ParticleSystemCoreRefPtr Explosion2ParticleNodeCore = ParticleSystemCore::create();
        Explosion2ParticleNodeCore->setSystem(Explosion2ParticleSystem);
        Explosion2ParticleNodeCore->setDrawer(Explosion2ParticleSystemDrawer);
        Explosion2ParticleNodeCore->setMaterial(PSExplosion2Material);

        NodeRefPtr Explosion2ParticleNode = Node::create();
        Explosion2ParticleNode->setCore(Explosion2ParticleNodeCore);
        //end/////////////////////

        ////////////////////////2ND GROUP///////////////////////////////////

        //Particle System Node    

        //Circle2
        BurstParticleGeneratorRecPtr Circle2BurstGenerator = BurstParticleGenerator::create();
        //Attach the function objects to the Generator
        Distribution3DRefPtr Circle2PositionDistribution = createSmokePositionDistribution();
        Circle2BurstGenerator->setPositionDistribution(Circle2PositionDistribution);
        Circle2BurstGenerator->setLifespanDistribution(createSmokeLifespanDistribution());
        Circle2BurstGenerator->setBurstAmount(50.0);
        Circle2BurstGenerator->setVelocityDistribution(createSmoke2VelocityDistribution());
        Circle2BurstGenerator->setColorDistribution(createSmokeColorDistribution());

        //Attach the function objects the Affectors
        AgeFadeParticleAffectorRecPtr Circle2AgeFadeParticleAffector = AgeFadeParticleAffector::create();
        Circle2AgeFadeParticleAffector->setFadeInTime(1.0f);
        Circle2AgeFadeParticleAffector->setFadeOutTime(2.0f);
        Circle2AgeFadeParticleAffector->setStartAlpha(0.0f);
        Circle2AgeFadeParticleAffector->setFadeToAlpha(1.0f);
        Circle2AgeFadeParticleAffector->setEndAlpha(0.0f);	

        AgeSizeParticleAffectorRecPtr Circle2AgeSizeParticleAffector = AgeSizeParticleAffector::create();
        //ages
        Circle2AgeSizeParticleAffector->editMFAges()->push_back(0.1);
        Circle2AgeSizeParticleAffector->editMFAges()->push_back(0.2);
        Circle2AgeSizeParticleAffector->editMFAges()->push_back(0.3);
        Circle2AgeSizeParticleAffector->editMFAges()->push_back(0.4);
        Circle2AgeSizeParticleAffector->editMFAges()->push_back(0.5);
        Circle2AgeSizeParticleAffector->editMFAges()->push_back(0.6);
        Circle2AgeSizeParticleAffector->editMFAges()->push_back(0.7);
        Circle2AgeSizeParticleAffector->editMFAges()->push_back(0.8);
        Circle2AgeSizeParticleAffector->editMFAges()->push_back(1.0);

        //sizes
        Circle2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(0.5,0.5,0.5));
        Circle2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(1.0,1.0,1.0));
        Circle2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(2.0,2.0,2.0));
        Circle2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(2.5,2.5,2.5));
        Circle2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(3.0,3.0,3.0));
        Circle2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(3.5,3.5,3.5));
        Circle2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(4.0,4.0,4.0));
        Circle2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(5.0,5.0,5.0));
        Circle2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(6.5,6.5,6.5));

        //Attach the Affector to the Circle2 Particle System
        Circle2ParticleSystem->pushToAffectors(Circle2AgeFadeParticleAffector);
        Circle2ParticleSystem->pushToAffectors(Circle2AgeSizeParticleAffector);

        ParticleSystemCoreRefPtr Circle2ParticleNodeCore = ParticleSystemCore::create();
        Circle2ParticleNodeCore->setSystem(Circle2ParticleSystem);
        Circle2ParticleNodeCore->setDrawer(Circle2ParticleSystemDrawer);
        Circle2ParticleNodeCore->setMaterial(PSCircleMaterial);

        NodeRefPtr Circle2ParticleNode = Node::create();
        Circle2ParticleNode->setCore(Circle2ParticleNodeCore);
        //end/////////////////////

        //Star2
        BurstParticleGeneratorRecPtr Star2BurstGenerator = BurstParticleGenerator::create();
        //Attach the function objects to the Generator
        Distribution3DRefPtr Star2PositionDistribution = createStar2PositionDistribution();
        Star2BurstGenerator->setPositionDistribution(Star2PositionDistribution);
        Star2BurstGenerator->setLifespanDistribution(createSmokeLifespanDistribution());
        Star2BurstGenerator->setBurstAmount(50.0);
        Star2BurstGenerator->setVelocityDistribution(createStar2VelocityDistribution());

        //Attach the function objects the Affectors
        AgeFadeParticleAffectorRecPtr Star2AgeFadeParticleAffector = AgeFadeParticleAffector::create();
        Star2AgeFadeParticleAffector->setFadeInTime(1.0f);
        Star2AgeFadeParticleAffector->setFadeOutTime(2.0f);
        Star2AgeFadeParticleAffector->setStartAlpha(0.0f);
        Star2AgeFadeParticleAffector->setFadeToAlpha(1.0f);
        Star2AgeFadeParticleAffector->setEndAlpha(0.0f);	

        AgeSizeParticleAffectorRecPtr Star2AgeSizeParticleAffector = AgeSizeParticleAffector::create();
        //ages
        Star2AgeSizeParticleAffector->editMFAges()->push_back(0.1);
        Star2AgeSizeParticleAffector->editMFAges()->push_back(0.2);
        Star2AgeSizeParticleAffector->editMFAges()->push_back(0.3);
        Star2AgeSizeParticleAffector->editMFAges()->push_back(0.4);
        Star2AgeSizeParticleAffector->editMFAges()->push_back(0.5);
        Star2AgeSizeParticleAffector->editMFAges()->push_back(0.6);
        Star2AgeSizeParticleAffector->editMFAges()->push_back(0.7);
        Star2AgeSizeParticleAffector->editMFAges()->push_back(0.8);
        Star2AgeSizeParticleAffector->editMFAges()->push_back(1.0);

        //sizes
        Star2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(0.5,0.5,0.5));
        Star2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(1.0,1.0,1.0));
        Star2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(2.0,2.0,2.0));
        Star2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(2.5,2.5,2.5));
        Star2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(3.0,3.0,3.0));
        Star2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(3.5,3.5,3.5));
        Star2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(4.0,4.0,4.0));
        Star2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(5.0,5.0,5.0));
        Star2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(6.5,6.5,6.5));


        //Attach the Affector to the Star2 Particle System
        Star2ParticleSystem->pushToAffectors(Star2AgeSizeParticleAffector);
        Star2ParticleSystem->pushToAffectors(Star2AgeFadeParticleAffector);

        ParticleSystemCoreRefPtr Star2ParticleNodeCore = ParticleSystemCore::create();
        Star2ParticleNodeCore->setSystem(Star2ParticleSystem);
        Star2ParticleNodeCore->setDrawer(Star2ParticleSystemDrawer);
        Star2ParticleNodeCore->setMaterial(PSStarMaterial);

        NodeRefPtr Star2ParticleNode = Node::create();
        Star2ParticleNode->setCore(Star2ParticleNodeCore);
        //end/////////////////////

        //ComStar2
        BurstParticleGeneratorRecPtr ComStar2BurstGenerator = BurstParticleGenerator::create();
        //Attach the function objects to the Generator
        Distribution3DRefPtr ComStar2PositionDistribution = createComStar2PositionDistribution();
        ComStar2BurstGenerator->setPositionDistribution(ComStar2PositionDistribution);
        ComStar2BurstGenerator->setLifespanDistribution(createSmokeLifespanDistribution());
        ComStar2BurstGenerator->setBurstAmount(50.0);
        ComStar2BurstGenerator->setVelocityDistribution(createComStar2VelocityDistribution());
        ComStarBurstGenerator->setColorDistribution(createComStarColorDistribution());

        //Attach the function objects the Affectors
        AgeFadeParticleAffectorRecPtr ComStar2AgeFadeParticleAffector = AgeFadeParticleAffector::create();
        ComStar2AgeFadeParticleAffector->setFadeInTime(1.0f);
        ComStar2AgeFadeParticleAffector->setFadeOutTime(2.0f);
        ComStar2AgeFadeParticleAffector->setStartAlpha(0.0f);
        ComStar2AgeFadeParticleAffector->setFadeToAlpha(1.0f);
        ComStar2AgeFadeParticleAffector->setEndAlpha(0.0f);	

        AgeSizeParticleAffectorRecPtr ComStar2AgeSizeParticleAffector = AgeSizeParticleAffector::create();
        //ages
        ComStar2AgeSizeParticleAffector->editMFAges()->push_back(0.1);
        ComStar2AgeSizeParticleAffector->editMFAges()->push_back(0.2);
        ComStar2AgeSizeParticleAffector->editMFAges()->push_back(0.3);
        ComStar2AgeSizeParticleAffector->editMFAges()->push_back(0.4);
        ComStar2AgeSizeParticleAffector->editMFAges()->push_back(0.5);
        ComStar2AgeSizeParticleAffector->editMFAges()->push_back(0.6);
        ComStar2AgeSizeParticleAffector->editMFAges()->push_back(0.7);
        ComStar2AgeSizeParticleAffector->editMFAges()->push_back(0.8);
        ComStar2AgeSizeParticleAffector->editMFAges()->push_back(1.0);

        //sizes
        ComStar2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(0.5,0.5,0.5));
        ComStar2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(1.0,1.0,1.0));
        ComStar2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(2.0,2.0,2.0));
        ComStar2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(2.5,2.5,2.5));
        ComStar2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(3.0,3.0,3.0));
        ComStar2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(3.5,3.5,3.5));
        ComStar2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(4.0,4.0,4.0));
        ComStar2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(5.0,5.0,5.0));
        ComStar2AgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(6.5,6.5,6.5));
        //Attach the Affector to the ComStar2 Particle System
        ComStar2ParticleSystem->pushToAffectors(ComStar2AgeFadeParticleAffector);
        ComStar2ParticleSystem->pushToAffectors(ComStar2AgeSizeParticleAffector);

        ParticleSystemCoreRefPtr ComStar2ParticleNodeCore = ParticleSystemCore::create();
        ComStar2ParticleNodeCore->setSystem(ComStar2ParticleSystem);
        ComStar2ParticleNodeCore->setDrawer(ComStar2ParticleSystemDrawer);
        ComStar2ParticleNodeCore->setMaterial(PSComStarMaterial);

        NodeRefPtr ComStar2ParticleNode = Node::create();
        ComStar2ParticleNode->setCore(ComStar2ParticleNodeCore);
        //end/////////////////////



        // Make Main Scene Node 
        NodeRefPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(RocketParticleNode);
        scene->addChild(CircleParticleNode);
        scene->addChild(StarParticleNode);
        scene->addChild(ComStarParticleNode);
        scene->addChild(Circle2ParticleNode);
        scene->addChild(Star2ParticleNode);
        scene->addChild(ComStar2ParticleNode);
        scene->addChild(ExplosionParticleNode);
        scene->addChild(Explosion2ParticleNode);

        TutorialWindow->connectMousePressed(boost::bind(mousePressed, _1,
                                                        &sceneManager,
                                                        RocketParticleSystem.get()));
        RocketParticleSystem->connectParticleKilled(boost::bind(particleKilled, _1,
                                                                CircleParticleSystem.get(),
                                                                CircleBurstGenerator.get(),
                                                                StarParticleSystem.get(),
                                                                StarBurstGenerator.get(),
                                                                ComStarParticleSystem.get(),
                                                                ComStarBurstGenerator.get()));
        Explosion2ParticleSystem->connectParticleKilled(boost::bind(particleKilled2, _1,
                                                                    StarParticleSystem.get(),
                                                                    StarBurstGenerator.get(),
                                                                    ComStarParticleSystem.get(),
                                                                    ComStarBurstGenerator.get()));
        ExplosionParticleSystem->connectParticleKilled(boost::bind(particleKilled2, _1,
                                                                   StarParticleSystem.get(),
                                                                   StarBurstGenerator.get(),
                                                                   ComStarParticleSystem.get(),
                                                                   ComStarBurstGenerator.get()));


        sceneManager.setRoot(scene);

        sceneManager.getNavigator()->set(Pnt3f(0.0,0.0,0.0), Pnt3f(0.0,0.0,-1.0), Vec3f(0.0,1.0,0.0));
        sceneManager.getNavigator()->setMotionFactor(1.0f);
        sceneManager.getCamera()->setNear(0.1f);
        sceneManager.getCamera()->setFar(1000.0f);


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "21Fireworks");

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
Distribution3DRefPtr createSmokePositionDistribution(void)
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
    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(3.0);
    TheSphereDistribution->setOuterRadius(10.0);
    TheSphereDistribution->setMinTheta(-3.141950);
    TheSphereDistribution->setMaxTheta(3.141950);
    TheSphereDistribution->setMinZ(-1.0);
    TheSphereDistribution->setMaxZ(1.0);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::SURFACE);

    return TheSphereDistribution;
}

Distribution3DRefPtr createSmokeColorDistribution(void)
{
    //Sphere Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(10.0,0.0,0.0));
    TheLineDistribution->setPoint2(Pnt3f(10.0,0.0,0.0));

    return TheLineDistribution;
}
Distribution3DRefPtr createStarPositionDistribution(void)
{
    //Sphere Distribution
    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(0.0);
    TheSphereDistribution->setOuterRadius(5.0);
    TheSphereDistribution->setMinTheta(0.0);
    TheSphereDistribution->setMaxTheta(6.283185);
    TheSphereDistribution->setMinZ(-1.0);
    TheSphereDistribution->setMaxZ(1.0);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::SURFACE);

    return TheSphereDistribution;
}

Distribution1DRefPtr createStarLifespanDistribution(void)
{
    GaussianNormalDistribution1DRefPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    TheLifespanDistribution->setMean(7.0f);
    TheLifespanDistribution->setStandardDeviation(0.5);

    return TheLifespanDistribution;
}

Distribution3DRefPtr createStarVelocityDistribution(void)
{
    //Sphere Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(0.0,-1.0,0.0));
    TheLineDistribution->setPoint2(Pnt3f(0.0,-5.0,0.0));

    return TheLineDistribution;
}

Distribution3DRefPtr createComStarPositionDistribution(void)
{
    //Sphere Distribution
    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(2.0);
    TheSphereDistribution->setOuterRadius(6.0);
    TheSphereDistribution->setMinTheta(0.0);
    TheSphereDistribution->setMaxTheta(6.283185);
    TheSphereDistribution->setMinZ(-1.0);
    TheSphereDistribution->setMaxZ(1.0);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::SURFACE);

    return TheSphereDistribution;
}

Distribution1DRefPtr createComStarLifespanDistribution(void)
{
    GaussianNormalDistribution1DRefPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    TheLifespanDistribution->setMean(3.0f);
    TheLifespanDistribution->setStandardDeviation(0.5);

    return TheLifespanDistribution;
}

Distribution3DRefPtr createComStarVelocityDistribution(void)
{
    //Sphere Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(0.0,-1.0,0.0));
    TheLineDistribution->setPoint2(Pnt3f(0.0,-5.0,0.0));

    return TheLineDistribution;
}



Distribution3DRefPtr createSmoke2PositionDistribution(void)
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



Distribution3DRefPtr createSmoke2VelocityDistribution(void)
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
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::SURFACE);

    return TheSphereDistribution;
}

Distribution3DRefPtr createStar2PositionDistribution(void)
{
    //Sphere Distribution
    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(0.0);
    TheSphereDistribution->setOuterRadius(1.0);
    TheSphereDistribution->setMinTheta(0.0);
    TheSphereDistribution->setMaxTheta(6.283185);
    TheSphereDistribution->setMinZ(-1.0);
    TheSphereDistribution->setMaxZ(1.0);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::VOLUME);

    return TheSphereDistribution;
}



Distribution3DRefPtr createStar2VelocityDistribution(void)
{
    //Sphere Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(0.0,-1.0,0.0));
    TheLineDistribution->setPoint2(Pnt3f(0.0,-1.0,0.0));

    return TheLineDistribution;
}

Distribution3DRefPtr createComStar2PositionDistribution(void)
{
    //Sphere Distribution
    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(2.0);
    TheSphereDistribution->setOuterRadius(6.0);
    TheSphereDistribution->setMinTheta(0.0);
    TheSphereDistribution->setMaxTheta(6.283185);
    TheSphereDistribution->setMinZ(-1.0);
    TheSphereDistribution->setMaxZ(1.0);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::VOLUME);

    return TheSphereDistribution;
}



Distribution3DRefPtr createComStar2VelocityDistribution(void)
{
    //Sphere Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(-1.0,0.0,0.0));
    TheLineDistribution->setPoint2(Pnt3f(-1.0,0.0,0.0));

    return TheLineDistribution;
}


Distribution3DRefPtr createExplosionPositionDistribution(void)
{
    //Sphere Distribution
    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(0.0);
    TheSphereDistribution->setOuterRadius(1.0);
    TheSphereDistribution->setMinTheta(0.0);
    TheSphereDistribution->setMaxTheta(6.283185);
    TheSphereDistribution->setMinZ(-1.0);
    TheSphereDistribution->setMaxZ(1.0);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::VOLUME);

    return TheSphereDistribution;
}

Distribution3DRefPtr createExplosionVelocityDistribution(void)
{
    //Sphere Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(0.0,-1.0,0.0));
    TheLineDistribution->setPoint2(Pnt3f(0.0,-1.0,0.0));

    return TheLineDistribution;
}


Distribution3DRefPtr createExplosion2PositionDistribution(void)
{

    //Disc Distribution
    DiscDistribution3DRefPtr TheDiscDistribution = DiscDistribution3D::create();
    TheDiscDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheDiscDistribution->setInnerRadius(10.0);
    TheDiscDistribution->setOuterRadius(15.0);
    TheDiscDistribution->setMinTheta(0.0);
    TheDiscDistribution->setMaxTheta(6.283185307);
    TheDiscDistribution->setNormal(Vec3f(0.0,1.0,0.0));
    TheDiscDistribution->setSurfaceOrEdge(DiscDistribution3D::SURFACE);


    return TheDiscDistribution;
}

Distribution3DRefPtr createExplosion2VelocityDistribution(void)
{
    //Sphere Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(0.0,-1.0,0.0));
    TheLineDistribution->setPoint2(Pnt3f(0.0,-1.0,0.0));

    return TheLineDistribution;
}

Distribution3DRefPtr createExplosion2ColorDistribution(void)
{
    //Sphere Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(1.0,0.0,0.0));
    TheLineDistribution->setPoint2(Pnt3f(1.0,0.0,0.0));

    return TheLineDistribution;
}

Distribution3DRefPtr createComStarColorDistribution(void)
{
    //Sphere Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(0.5,0.5,1.0));
    TheLineDistribution->setPoint2(Pnt3f(0.0,0.0,1.0));

    return TheLineDistribution;
}
