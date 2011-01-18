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
#include "OSGDepthChunk.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGParticleSystem.h"
#include "OSGParticleSystemCore.h"
#include "OSGPointParticleSystemDrawer.h"
#include "OSGLineParticleSystemDrawer.h"
#include "OSGQuadParticleSystemDrawer.h"
#include "OSGDiscParticleSystemDrawer.h"
#include "OSGRateParticleGenerator.h"
#include "OSGBurstParticleGenerator.h"
#include "OSGGravityParticleAffector.h"
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
              LineParticleSystemDrawer* const ExampleLineParticleSystemDrawer,
              QuadParticleSystemDrawer* const ExampleQuadParticleSystemDrawer
             )
{
    if(details->getKey() == KeyEventDetails::KEY_Q &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
    if(details->getKey()== KeyEventDetails::KEY_1) // Use the Point Drawer
    {
        ParticleNodeCore->setDrawer(ExamplePointParticleSystemDrawer);
    }

    if(details->getKey()== KeyEventDetails::KEY_2)//Use the Line Drawer for 2
    {
        ParticleNodeCore->setDrawer(ExampleLineParticleSystemDrawer);
    }

    if(details->getKey()== KeyEventDetails::KEY_3)//Use the Quad Drawer for 3
    {
        ParticleNodeCore->setDrawer(ExampleQuadParticleSystemDrawer);
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
        PSPointChunk->setSize(6.0f);
        PSPointChunk->setSmooth(true);

        BlendChunkRefPtr PSBlendChunk = BlendChunk::create();
        PSBlendChunk->setSrcFactor(GL_SRC_ALPHA);
        PSBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

        MaterialChunkRefPtr PSMaterialChunkChunk = MaterialChunk::create();
        PSMaterialChunkChunk->setAmbient(Color4f(0.2f,0.6f,0.5f,0.3f));
        PSMaterialChunkChunk->setDiffuse(Color4f(0.2f,0.9f,0.1f,0.3f));
        PSMaterialChunkChunk->setSpecular(Color4f(0.5f,0.4f,0.2f,0.6f));
        PSMaterialChunkChunk->setEmission(Color4f(0.2f,0.6f,0.5f,0.3f));
        PSMaterialChunkChunk->setColorMaterial(GL_NONE);

        //enable depth test
        DepthChunkRefPtr PSDepthChunk = DepthChunk::create();

        ChunkMaterialRefPtr PSMaterial = ChunkMaterial::create();
        PSMaterial->addChunk(PSPointChunk);
        PSMaterial->addChunk(PSMaterialChunkChunk);
        PSMaterial->addChunk(PSBlendChunk);
        PSMaterial->addChunk(PSDepthChunk);

        //Particle System
        ParticleSystemRefPtr ExampleParticleSystem = ParticleSystem::create();
        ExampleParticleSystem->attachUpdateProducer(TutorialWindow);

        //Particle System Drawer
        //Point
        PointParticleSystemDrawerRecPtr ExamplePointParticleSystemDrawer = PointParticleSystemDrawer::create();
        //ExamplePointParticleSystemDrawer->setForcePerParticleSizing(true);

        //Line
        LineParticleSystemDrawerRecPtr ExampleLineParticleSystemDrawer = LineParticleSystemDrawer::create();
        ExampleLineParticleSystemDrawer->setLineDirectionSource(LineParticleSystemDrawer::DIRECTION_NORMAL);//DIRECTION_VELOCITY_CHANGE);
        ExampleLineParticleSystemDrawer->setLineLengthSource(LineParticleSystemDrawer::LENGTH_SIZE_X);
        ExampleLineParticleSystemDrawer->setEndPointFading(Vec2f(1.0,0.0));
        //Quad
        QuadParticleSystemDrawerRecPtr ExampleQuadParticleSystemDrawer = QuadParticleSystemDrawer::create();
        ExampleQuadParticleSystemDrawer->setQuadSizeScaling(Vec2f(0.1,0.1));
        ExampleQuadParticleSystemDrawer->setNormalAndUpSource(QuadParticleSystemDrawer::NORMAL_PARTICLE_NORMAL,QuadParticleSystemDrawer::UP_STATIC);

        RateParticleGeneratorRefPtr ExampleGeneratorTheSequel = RateParticleGenerator::create();

        //Attach the function objects to the Generator
        ExampleGeneratorTheSequel->setPositionDistribution(createPositionDistribution());
        ExampleGeneratorTheSequel->setLifespanDistribution(createLifespanDistribution());
        ExampleGeneratorTheSequel->setGenerationRate(300.0);
        ExampleGeneratorTheSequel->setVelocityDistribution(createVelocityDistribution());


        //Attach the Generator to the Particle System
        //ExampleParticleSystem->pushToGenerators(ExampleGenerator);
        ExampleParticleSystem->setMaxParticles(500);
        ExampleParticleSystem->pushToGenerators(ExampleGeneratorTheSequel);

        //Particle System Node
        ParticleSystemCoreRecPtr ParticleNodeCore = ParticleSystemCore::create();
        ParticleNodeCore->setSystem(ExampleParticleSystem);
        ParticleNodeCore->setDrawer(ExampleQuadParticleSystemDrawer);
        ParticleNodeCore->setMaterial(PSMaterial);
        ParticleNodeCore->setSortingMode(ParticleSystemCore::BACK_TO_FRONT);

        NodeRefPtr ParticleNode = Node::create();
        ParticleNode->setCore(ParticleNodeCore);


        // Make Main Scene Node and add the Torus
        NodeRefPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(ParticleNode);

        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1, &sceneManager,
                                                    ParticleNodeCore.get(),
                                                    ExamplePointParticleSystemDrawer.get(),
                                                    ExampleLineParticleSystemDrawer.get(),
                                                    ExampleQuadParticleSystemDrawer.get()));
        sceneManager.setRoot(scene);

        // Show the whole Scene
        sceneManager.showAll();

        sceneManager.getCamera()->setFar(500.0);

        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "14ParticleSorting");

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
    //Cone Distribution
    ConeDistribution3DRefPtr TheConeDistribution = ConeDistribution3D::create();
    TheConeDistribution->setPosition(Pnt3f(0.0,0.0,0.0));
    TheConeDistribution->setDirection(Vec3f(0.0,0.0,1.0));
    TheConeDistribution->setSpread(1.57);
    TheConeDistribution->setMinTheta(0.0);
    TheConeDistribution->setMaxTheta(6.282);
    TheConeDistribution->setMin(0.0);
    TheConeDistribution->setMax(1.0);
    TheConeDistribution->setSurfaceOrVolume(ConeDistribution3D::VOLUME);

    return TheConeDistribution;
}

Distribution1DRefPtr createLifespanDistribution(void)
{
    SegmentDistribution1DRefPtr TheLifespanDistribution = SegmentDistribution1D::create();
    TheLifespanDistribution->setSegment(Vec2f(2.0,3.0));

    return TheLifespanDistribution;
}

Distribution3DRefPtr createVelocityDistribution(void)
{
    //Line Distribution, no velocity
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(0.0,0.0,0.0));
    TheLineDistribution->setPoint2(Pnt3f(0.0,0.0,0.0));

    return TheLineDistribution;
}

