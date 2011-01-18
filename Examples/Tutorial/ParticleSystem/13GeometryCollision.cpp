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
#include "OSGVector.h"

#include "OSGParticleSystem.h"
#include "OSGParticleSystemCore.h"
#include "OSGPointParticleSystemDrawer.h"
#include "OSGGeometryCollisionParticleSystemAffector.h"
#include "OSGRateParticleGenerator.h"

#include "OSGLineDistribution3D.h"
#include "OSGGaussianNormalDistribution1D.h"
#include "OSGDiscDistribution3D.h"

#include "OSGBlendChunk.h"
#include "OSGPointChunk.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

Distribution3DRefPtr createPositionDistribution(void);
Distribution1DRefPtr createLifespanDistribution(void);
Distribution3DRefPtr createVelocityDistribution(void);

void particleCollision(ParticleGeometryCollisionEventDetails* const details)
{
    ParticleSystemRefPtr TheSystem= details->getSystem();
    UInt32 ParticleIndex(details->getParticleIndex());

    Vec3f Reflect(TheSystem->getVelocity(ParticleIndex).reflect(details->getHitNormal()));
    TheSystem->setVelocity(Reflect, ParticleIndex);
    TheSystem->setPosition(details->getHitPoint() + (0.00001f*Reflect), ParticleIndex);
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
        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1, &sceneManager));

        //Particle System
        ParticleSystemRefPtr ExampleParticleSystem = ParticleSystem::create();
        ExampleParticleSystem->attachUpdateProducer(TutorialWindow);

        PointParticleSystemDrawerRefPtr ExamplePointParticleSystemDrawer = PointParticleSystemDrawer::create();
        //NodeRefPtr ParticlePrototypeNode = makeTorus(1.0,4.0,16,16);
        //NodeRefPtr CollisionNode = makeBox(5.0,5.0,5.0,1,1,1);//makeSphere(4,10.0f);
        NodeRefPtr CollisionNode = makeSphere(2,4.0f);

        //Particle System Material
        PointChunkRefPtr PSPointChunk = PointChunk::create();
        PSPointChunk->setSize(5.0f);
        PSPointChunk->setSmooth(true);
        BlendChunkRefPtr PSBlendChunk = BlendChunk::create();
        PSBlendChunk->setSrcFactor(GL_SRC_ALPHA);
        PSBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

        MaterialChunkRefPtr PSMaterialChunkChunk = MaterialChunk::create();
        PSMaterialChunkChunk->setAmbient(Color4f(1.0f,0.0f,0.0f,1.0f));
        PSMaterialChunkChunk->setDiffuse(Color4f(1.0f,0.0f,0.0f,1.0f));
        PSMaterialChunkChunk->setSpecular(Color4f(1.0f,0.0f,0.0f,1.0f));
        PSMaterialChunkChunk->setColorMaterial(GL_NONE);
        //PSMaterialChunkChunk->setLit(false);

        ChunkMaterialRefPtr PSMaterial = ChunkMaterial::create();
        PSMaterial->addChunk(PSPointChunk);
        PSMaterial->addChunk(PSMaterialChunkChunk);
        PSMaterial->addChunk(PSBlendChunk);

        ParticleSystemCoreRefPtr ParticleNodeCore = ParticleSystemCore::create();
        ParticleNodeCore->setSystem(ExampleParticleSystem);
        ParticleNodeCore->setDrawer(ExamplePointParticleSystemDrawer);
        ParticleNodeCore->setMaterial(PSMaterial);

        NodeRefPtr ParticleNode = Node::create();
        ParticleNode->setCore(ParticleNodeCore);

        //Generator
        //Attach the function objects to the Generator
        RateParticleGeneratorRefPtr ExampleGenerator= RateParticleGenerator::create();
        ExampleGenerator->setPositionDistribution(createPositionDistribution());
        ExampleGenerator->setLifespanDistribution(createLifespanDistribution());
        ExampleGenerator->setGenerationRate(20.0);
        ExampleGenerator->setVelocityDistribution(createVelocityDistribution());

        //Geometry Collision Affector
        GeometryCollisionParticleSystemAffectorRefPtr ExampleGeometryCollisionParticleSystemAffector = GeometryCollisionParticleSystemAffector::create();
        ExampleGeometryCollisionParticleSystemAffector->setCollisionNode(CollisionNode);

        ExampleGeometryCollisionParticleSystemAffector->connectParticleCollision(boost::bind(particleCollision, _1));

        ExampleParticleSystem->pushToSystemAffectors(ExampleGeometryCollisionParticleSystemAffector);
        ExampleParticleSystem->pushToGenerators(ExampleGenerator);


        // Make Main Scene Node and add the Torus
        NodeRefPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(ParticleNode);
        scene->addChild(CollisionNode);

        sceneManager.setRoot(scene);

        // Show the whole Scene
        sceneManager.showAll();


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "13CollisionGeometry");

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
    //Disc Distribution
    DiscDistribution3DRefPtr TheDiscDistribution = DiscDistribution3D::create();
    TheDiscDistribution->setCenter(Pnt3f(0.0,0.0,10.0));
    TheDiscDistribution->setInnerRadius(0.0);
    TheDiscDistribution->setOuterRadius(3.0);
    TheDiscDistribution->setMinTheta(0.0);
    TheDiscDistribution->setMaxTheta(6.283185307);
    TheDiscDistribution->setNormal(Vec3f(0.0,0.0,1.0));
    TheDiscDistribution->setSurfaceOrEdge(DiscDistribution3D::SURFACE);


    return TheDiscDistribution;
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
    //Sphere Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(0.0,0.0,-4.5));
    TheLineDistribution->setPoint2(Pnt3f(0.0,0.0,-5.0));

    return TheLineDistribution;
}
