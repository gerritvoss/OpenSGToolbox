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
#include "OSGTextureObjChunk.h"
#include "OSGImageFileHandler.h"

#include "OSGSimpleSceneManager.h"
#include "OSGSceneFileHandler.h"

#include "OSGAgeFadeParticleAffector.h"
#include "OSGAgeSizeParticleAffector.h"
#include "OSGRateParticleGenerator.h"
#include "OSGBurstParticleGenerator.h"

#include "OSGParticleSystem.h"
#include "OSGParticleSystemCore.h"
#include "OSGNodeParticleSystemCore.h"
#include "OSGPointParticleSystemDrawer.h"
#include "OSGBurstParticleGenerator.h"
#include "OSGSphereDistribution3D.h"
#include "OSGLineDistribution3D.h"

#include "OSGGaussianNormalDistribution1D.h"
#include "OSGCylinderDistribution3D.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

Distribution3DRefPtr createPositionDistribution(void);
Distribution1DRefPtr createLifespanDistribution(void);
Distribution3DRefPtr createVelocityDistribution(void);
Distribution3DRefPtr createAccelerationDistribution(void);

void keyTyped(KeyEventDetails* const details,
              SimpleSceneManager *mgr,
              ParticleSystem* const ExampleParticleSystem,
              BurstParticleGenerator* const ExampleBurstGenerator
             )
{
    if(details->getKey() == KeyEventDetails::KEY_Q &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
    if(details->getKey() == KeyEventDetails::KEY_B)//generate particles when clicked
    {
        //Attach the Generator to the Particle System
        ExampleParticleSystem->pushToGenerators(ExampleBurstGenerator);

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
        PSPointChunk->setSize(12.0f);
        PSPointChunk->setSmooth(true);
        BlendChunkRefPtr PSBlendChunk = BlendChunk::create();
        PSBlendChunk->setSrcFactor(GL_SRC_ALPHA);
        PSBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

        MaterialChunkRefPtr PSMaterialChunkChunk = MaterialChunk::create();
        PSMaterialChunkChunk->setAmbient(Color4f(0.3f,0.3f,0.3f,1.0f));
        PSMaterialChunkChunk->setDiffuse(Color4f(0.7f,0.7f,0.7f,1.0f));
        PSMaterialChunkChunk->setSpecular(Color4f(0.9f,0.9f,0.9f,1.0f));
        PSMaterialChunkChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);

        ChunkMaterialRefPtr PSMaterial = ChunkMaterial::create();
        PSMaterial->addChunk(PSPointChunk);
        PSMaterial->addChunk(PSMaterialChunkChunk);
        PSMaterial->addChunk(PSBlendChunk);

        //Particle System

        ParticleSystemRefPtr ExampleParticleSystem = ParticleSystem::create();
        ExampleParticleSystem->attachUpdateProducer(TutorialWindow);

        //Particle System Drawer
        PointParticleSystemDrawerRefPtr ExampleParticleSystemDrawer = PointParticleSystemDrawer::create();

        BurstParticleGeneratorRefPtr ExampleBurstGenerator = BurstParticleGenerator::create();
        //Attach the function objects to the Generator
        ExampleBurstGenerator->setPositionDistribution(createPositionDistribution());
        ExampleBurstGenerator->setLifespanDistribution(createLifespanDistribution());
        ExampleBurstGenerator->setBurstAmount(50.0);
        ExampleBurstGenerator->setVelocityDistribution(createVelocityDistribution());
        ExampleBurstGenerator->setAccelerationDistribution(createAccelerationDistribution());



        //Particle System Node
        ParticleSystemCoreRefPtr ParticleNodeCore = ParticleSystemCore::create();
        ParticleNodeCore->setSystem(ExampleParticleSystem);
        ParticleNodeCore->setDrawer(ExampleParticleSystemDrawer);
        ParticleNodeCore->setMaterial(PSMaterial);

        NodeRefPtr ParticleNode = Node::create();
        ParticleNode->setCore(ParticleNodeCore);

        // Make Main Scene Node and add the Torus
        NodeRefPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(ParticleNode);

        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1,
                                                    &sceneManager,
                                                    ExampleParticleSystem.get(),
                                                    ExampleBurstGenerator.get()));

        sceneManager.setRoot(scene);

        // Show the whole Scene
        sceneManager.showAll();


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "04BurstParticleGenerator");

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


    //Sphere Distribution
    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(3.0);
    TheSphereDistribution->setOuterRadius(6.0);
    TheSphereDistribution->setMinTheta(-3.141950);
    TheSphereDistribution->setMaxTheta(3.141950);
    TheSphereDistribution->setMinZ(-1.0);
    TheSphereDistribution->setMaxZ(1.0);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::VOLUME);

    return TheSphereDistribution;
}



Distribution1DRefPtr createLifespanDistribution(void)
{
    GaussianNormalDistribution1DRefPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    TheLifespanDistribution->setMean(30.0f);
    TheLifespanDistribution->setStandardDeviation(3.0);

    return TheLifespanDistribution;
}

Distribution3DRefPtr createAccelerationDistribution(void)
{
    //Line Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(0.0,0.0,0.0));
    TheLineDistribution->setPoint2(Pnt3f(0.0,0.0,0.0));

    return TheLineDistribution;
}
