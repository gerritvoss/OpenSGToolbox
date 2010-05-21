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
#include "OSGParticleCollisionListener.h"

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
#include "OSGParticleSystemListener.h"

#include "OSGLineDistribution3D.h"
#include "OSGCylinderDistribution3D.h"
#include "OSGGaussianNormalDistribution1D.h"
#include "OSGDiscDistribution3D.h"
#include "OSGSphereDistribution3D.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

//Particle System Drawer

QuadParticleSystemDrawerRefPtr SmokeParticleSystemDrawer;
PointParticleSystemDrawerRefPtr ExampleShrapnelParticleSystemDrawer;
PointParticleSystemDrawerRefPtr ExampleFireballParticleSystemDrawer;

ParticleSystemRefPtr RocketParticleSystem;
ParticleSystemRefPtr SmokeParticleSystem;
ParticleSystemRefPtr ShrapnelParticleSystem;
ParticleSystemRefPtr FireballParticleSystem;
ParticleSystemRefPtr HouseParticleSystem;


BurstParticleGeneratorRefPtr ShrapnelBurstGenerator;
RateParticleGeneratorRefPtr SmokeGenerator;
BurstParticleGeneratorRefPtr FireballGenerator;

AgeFadeParticleAffectorRefPtr SmokeAgeFadeParticleAffector;
AgeSizeParticleAffectorRefPtr SmokeAgeSizeParticleAffector;
AgeSizeParticleAffectorRefPtr FireballAgeSizeParticleAffector;
ParticleSystemCoreRefPtr PointParticleNodeCore;

Distribution3DRefPtr FireballPositionDistribution;
Distribution3DRefPtr ShrapnelPositionDistribution;
Distribution3DRefPtr SmokePositionDistribution;

Distribution3DRefPtr createPositionDistribution(void);
Distribution1DRefPtr createLifespanDistribution(void);
Distribution3DRefPtr createVelocityDistribution(void);

Distribution3DRefPtr createSmokeVelocityDistribution(void);
Distribution1DRefPtr createSmokeLifespanDistribution(void);
Distribution3DRefPtr createSmokePositionDistribution(void);

Distribution3DRefPtr createShrapnelPositionDistribution(void);
Distribution3DRefPtr createShrapnelAccelerationDistribution(void);
Distribution3DRefPtr createShrapnelVelocityDistribution(void);

Distribution3DRefPtr createFireballVelocityDistribution(void);
Distribution3DRefPtr createFireballPositionDistribution(void);
Distribution3DRefPtr createFireballAccelerationDistribution(void);
Distribution1DRefPtr createFireballLifespanDistribution(void);



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

        if(e->getKey() == KeyEvent::KEY_B)//generate particles when clicked
        {

        }
    }

    virtual void keyReleased(const KeyEventUnrecPtr e)
    {
    }

    virtual void keyTyped(const KeyEventUnrecPtr e)
    {
        if(e->getKey()== KeyEvent::KEY_1) // Use the Point Drawer
        {

        }

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
        if(dynamic_cast<WindowEventProducer*>(e->getSource())->getKeyModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
        {
            mgr->mouseButtonPress(e->getButton(), e->getLocation().x(), e->getLocation().y());
        }
        else
        {
            Line TheRay;
            if(e->getButton() == MouseEvent::BUTTON1)
            {

                mgr->getCamera()->calcViewRay(TheRay,e->getLocation().x(),e->getLocation().y(),*(mgr->getWindow()->getPort(0)));
                std::cout<<"Velocity "<<TheRay.getDirection()<<std::endl;
            }
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
    virtual void mouseReleased(const MouseEventUnrecPtr e)
    {
        if(dynamic_cast<WindowEventProducer*>(e->getSource())->getKeyModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
        {
            mgr->mouseButtonRelease(e->getButton(), e->getLocation().x(), e->getLocation().y());
        }
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

class TutorialRocketParticleSystemListener : public ParticleSystemListener
{
  public:
    virtual void systemUpdated(const ParticleSystemEventUnrecPtr e)
    {
    }

    virtual void particleGenerated(const ParticleEventUnrecPtr e) 
    {
    }

    virtual void volumeChanged(const ParticleSystemEventUnrecPtr e)
    {
    }

    virtual void particleKilled(const ParticleEventUnrecPtr e)
    {
        dynamic_pointer_cast<SphereDistribution3D>(FireballPositionDistribution)->setCenter(e->getParticlePosition());

        dynamic_pointer_cast<SphereDistribution3D>(ShrapnelPositionDistribution)->setCenter(e->getParticlePosition());

        dynamic_pointer_cast<DiscDistribution3D>(SmokePositionDistribution)->setCenter(e->getParticlePosition());


        // if()
        {

            //Attach the Generator to the Shrapnel Particle System
            ShrapnelParticleSystem->pushToGenerators(ShrapnelBurstGenerator);

            //Attach the Affector to the Smoke Particle System
            SmokeParticleSystem->pushToGenerators(SmokeGenerator);
            SmokeParticleSystem->pushToAffectors(SmokeAgeFadeParticleAffector);
            SmokeParticleSystem->pushToAffectors(SmokeAgeSizeParticleAffector);

            //Attach the Affector to the fireball Particle System
            FireballParticleSystem->pushToGenerators(FireballGenerator);
            FireballParticleSystem->pushToAffectors(FireballAgeSizeParticleAffector);

        }
        std::cout << "Rocket Died at: " << e->getParticlePosition() << std::endl;
    }
    virtual void particleStolen(const ParticleEventUnrecPtr e)
    {
    }
};

class TutorialParticleCollisionListener : public ParticleGeometryCollisionListener
{
    virtual void particleCollision(const ParticleGeometryCollisionEventUnrecPtr ColE)
    {
        ParticleSystemRefPtr TheSystem= ColE->getSystem();
        UInt32 ParticleIndex(ColE->getParticleIndex());


        Real32 phi= osgACos((-TheSystem->getVelocity(ParticleIndex).dot(ColE->getHitNormal()))/(TheSystem->getVelocity(ParticleIndex).length()*ColE->getHitNormal().length()));

        if( phi < osgDegree2Rad(80.0) )
        {
            TheSystem->killParticle(ParticleIndex);
        }
        else
        {
            //Reflect the Particle
            Vec3f Reflect(TheSystem->getVelocity(ParticleIndex).reflect(ColE->getHitNormal()));
            TheSystem->setVelocity(Reflect, ParticleIndex);
            TheSystem->setPosition(ColE->getHitPoint() + (0.00001f*Reflect), ParticleIndex);
        }

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
    ImageRefPtr LoadedImage = ImageFileHandler::the()->read("Data/Checker.jpg");    
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
    PSSmokeMaterial->addChunk(PSMaterialChunk);
    PSSmokeMaterial->addChunk(QuadTextureEnvChunk);


    //Particle System
    //Rocket
    RocketParticleSystem = OSG::ParticleSystem::create();
    RocketParticleSystem->attachUpdateListener(TutorialWindow);

    TutorialRocketParticleSystemListener TheRocketListener;
    RocketParticleSystem->addParticleSystemListener(&TheRocketListener);

    //smoke
    SmokeParticleSystem = OSG::ParticleSystem::create();
    SmokeParticleSystem->attachUpdateListener(TutorialWindow);
    //Shrapnel
    ShrapnelParticleSystem = OSG::ParticleSystem::create();
    ShrapnelParticleSystem->attachUpdateListener(TutorialWindow);
    //Fireball
    FireballParticleSystem = OSG::ParticleSystem::create();
    FireballParticleSystem->attachUpdateListener(TutorialWindow);



    //Particle System Drawer
    //Rocket does not have a drawer because it is being attached to a special node core
    //Smoke
    SmokeParticleSystemDrawer = OSG::QuadParticleSystemDrawer::create();
    //SmokeParticleSystemDrawer->setQuadSizeScaling(Vec2f(0.5f,0.5f));
    //Shrapnel
    ExampleShrapnelParticleSystemDrawer = OSG::PointParticleSystemDrawer::create();
    ExampleShrapnelParticleSystemDrawer->setForcePerParticleSizing(true);
    //Fireball
    ExampleFireballParticleSystemDrawer = OSG::PointParticleSystemDrawer::create();
    ExampleFireballParticleSystemDrawer->setForcePerParticleSizing(true);



    //Particle System Node
    //collision node
    //NodeRefPtr EnvironmentNode = makeSphere(2,4.0f);

    Matrix EnvironmentTransformation;
    EnvironmentTransformation.setScale(0.1f);

    TransformRefPtr EnvironmentTransformCore = Transform::create();
    EnvironmentTransformCore->setMatrix(EnvironmentTransformation);

    NodeRefPtr EnvironmentNode = Node::create();
    EnvironmentNode->setCore(EnvironmentTransformCore);
    //EnvironmentNode->addChild(SceneFileHandler::the()->read("Data/Chloroplast.osb"));
    EnvironmentNode->addChild(SceneFileHandler::the()->read("Data/house.obj"));

    //NodeRefPtr ParticlePrototypeNode = makeTorus(1.0,4.0,16,16);
    NodeRefPtr RocketParticlePrototypeNode = SceneFileHandler::the()->read("Data/rocket.obj");
    if(RocketParticlePrototypeNode == NULL)
    {
        RocketParticlePrototypeNode = makeTorus(.5, 2, 16, 16);
    }

    NodeParticleSystemCoreRefPtr RocketParticleNodeCore = OSG::NodeParticleSystemCore::create();
    RocketParticleNodeCore->setSystem(RocketParticleSystem);
    RocketParticleNodeCore->setPrototypeNode(RocketParticlePrototypeNode);
    RocketParticleNodeCore->setNormalSource(NodeParticleSystemCore::NORMAL_VELOCITY);
    RocketParticleNodeCore->setUpSource(NodeParticleSystemCore::UP_PARTICLE_NORMAL);
    RocketParticleNodeCore->setUp(Vec3f(0.0f,1.0f,0.0f));

    //Geometry Collision Affector
    GeometryCollisionParticleSystemAffectorRefPtr ExampleGeometryCollisionParticleSystemAffector = GeometryCollisionParticleSystemAffector::create();
    ExampleGeometryCollisionParticleSystemAffector->setCollisionNode(EnvironmentNode);

    TutorialParticleCollisionListener TheCollisionListener;
    ExampleGeometryCollisionParticleSystemAffector->addParticleGeometryCollisionListener(&TheCollisionListener);


    NodeRefPtr RocketParticleNode = OSG::Node::create();
    RocketParticleNode->setCore(RocketParticleNodeCore);

    //Attach the Affector to the Rocket Particle System
    //RocketParticleSystem->pushToAffectors();
    RocketParticleSystem->pushToSystemAffectors(ExampleGeometryCollisionParticleSystemAffector);


    //Smoke
    SmokeGenerator = OSG::RateParticleGenerator::create();
    //Attach the function objects to the Generator
    SmokePositionDistribution = createSmokePositionDistribution();
    SmokeGenerator->setPositionDistribution(SmokePositionDistribution);
    SmokeGenerator->setLifespanDistribution(createSmokeLifespanDistribution());
    SmokeGenerator->setGenerationRate(50.0);
    SmokeGenerator->setVelocityDistribution(createSmokeVelocityDistribution());
    //Attach the function objects the Affectors
    SmokeAgeFadeParticleAffector = OSG::AgeFadeParticleAffector::create();
    SmokeAgeFadeParticleAffector->setFadeInTime(2.0f);
    SmokeAgeFadeParticleAffector->setFadeOutTime(5.0f);
    SmokeAgeFadeParticleAffector->setStartAlpha(0.0f);
    SmokeAgeFadeParticleAffector->setFadeToAlpha(0.2f);
    SmokeAgeFadeParticleAffector->setEndAlpha(0.0f);	

    SmokeAgeSizeParticleAffector = OSG::AgeSizeParticleAffector::create();
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

    ParticleSystemCoreRefPtr SmokeParticleNodeCore = OSG::ParticleSystemCore::create();
    SmokeParticleNodeCore->setSystem(SmokeParticleSystem);
    SmokeParticleNodeCore->setDrawer(SmokeParticleSystemDrawer);
    SmokeParticleNodeCore->setMaterial(PSSmokeMaterial);

    NodeRefPtr SmokeParticleNode = OSG::Node::create();
    SmokeParticleNode->setCore(SmokeParticleNodeCore);
    //end/////////////////////

    //Shrapnel
    ShrapnelBurstGenerator = OSG::BurstParticleGenerator::create();
    NodeRefPtr ShrapnelParticlePrototypeNode = SceneFileHandler::the()->read("Data/Shrapnel.obj");

    NodeParticleSystemCoreRefPtr ShrapnelParticleNodeCore = OSG::NodeParticleSystemCore::create();
    ShrapnelParticleNodeCore->setSystem(ShrapnelParticleSystem);
    ShrapnelParticleNodeCore->setPrototypeNode(ShrapnelParticlePrototypeNode);

    //Attach the function objects to the Generator
    ShrapnelPositionDistribution = createShrapnelPositionDistribution();
    ShrapnelBurstGenerator->setPositionDistribution(ShrapnelPositionDistribution);
    ShrapnelBurstGenerator->setLifespanDistribution(createLifespanDistribution());
    ShrapnelBurstGenerator->setBurstAmount(50.0);
    ShrapnelBurstGenerator->setVelocityDistribution(createShrapnelVelocityDistribution());
    ShrapnelBurstGenerator->setAccelerationDistribution(createShrapnelAccelerationDistribution());

    NodeRefPtr ShrapnelParticleNode = OSG::Node::create();
    ShrapnelParticleNode->setCore(ShrapnelParticleNodeCore);
    //end/////////////////////

    //fireball
    FireballGenerator = OSG::BurstParticleGenerator::create();
    NodeRefPtr FireballParticlePrototypeNode = SceneFileHandler::the()->read("Data/bubble.obj");

    NodeParticleSystemCoreRefPtr FireballParticleNodeCore = OSG::NodeParticleSystemCore::create();
    FireballParticleNodeCore->setSystem(FireballParticleSystem);
    FireballParticleNodeCore->setPrototypeNode(FireballParticlePrototypeNode);
    //Attach the function objects to the Generator
    FireballPositionDistribution = createFireballPositionDistribution();
    FireballGenerator->setPositionDistribution(FireballPositionDistribution);
    FireballGenerator->setLifespanDistribution(createFireballLifespanDistribution());
    FireballGenerator->setBurstAmount(100.0);
    FireballGenerator->setVelocityDistribution(createFireballVelocityDistribution());
    FireballGenerator->setAccelerationDistribution(createFireballAccelerationDistribution());
    //Attach the function objects the Affectors
    FireballAgeSizeParticleAffector = OSG::AgeSizeParticleAffector::create();
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

    NodeRefPtr FireballParticleNode = OSG::Node::create();
    FireballParticleNode->setCore(FireballParticleNodeCore);
    //end/////////////////////


    // Make Main Scene Node 
    NodeRefPtr scene = OSG::Node::create();
    scene->setCore(OSG::Group::create());
    scene->addChild(RocketParticleNode);
    scene->addChild(SmokeParticleNode);
    scene->addChild(ShrapnelParticleNode);
    scene->addChild(FireballParticleNode);
    scene->addChild(EnvironmentNode);

    mgr->setRoot(scene);

    mgr->getNavigator()->set(Pnt3f(0.0,0.0,0.0), Pnt3f(0.0,0.0,-1.0), Vec3f(0.0,1.0,0.0));
    mgr->getNavigator()->setMotionFactor(1.0f);
    mgr->getCamera()->setNear(0.1f);
    mgr->getCamera()->setFar(1000.0f);


    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
                               WinSize,
                               "10RocketLauncher");

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
