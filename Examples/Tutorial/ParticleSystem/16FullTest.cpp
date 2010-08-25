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
#include "OSGLineParticleSystemDrawer.h"
#include "OSGQuadParticleSystemDrawer.h"
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

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// Particle Generator Distributions
Distribution3DRefPtr createPositionDistribution(void);
Distribution1DRefPtr createLifespanDistribution(void);
Distribution3DRefPtr createVelocityDistribution(void);

//Particle System
ParticleSystemCoreRefPtr ParticleNodeCore;

//Particle System Drawers
PointParticleSystemDrawerRefPtr ExamplePointParticleSystemDrawer;
LineParticleSystemDrawerRefPtr ExampleLineParticleSystemDrawer;
QuadParticleSystemDrawerRefPtr ExampleQuadParticleSystemDrawer;
DiscParticleSystemDrawerRefPtr ExampleDiscParticleSystemDrawer;


//Particle System Generator
RateParticleGeneratorRefPtr ExampleGenerator;

// ParticleAffectors
ConditionalParticleAffectorRefPtr ExampleConditionalAffector;

//Example system
ParticleSystemRefPtr ExampleParticleSystem;

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
    }

    virtual void keyReleased(const KeyEventUnrecPtr e)
    {
    }

    virtual void keyTyped(const KeyEventUnrecPtr e)
    {
        if(e->getKey()== KeyEvent::KEY_1) // Use the Point Drawer
        {
            ParticleNodeCore->setDrawer(ExamplePointParticleSystemDrawer);
        }

        if(e->getKey()== KeyEvent::KEY_2)//Use the Line Drawer for 2
        {
            ParticleNodeCore->setDrawer(ExampleLineParticleSystemDrawer);
        }

        if(e->getKey()== KeyEvent::KEY_3)//Use the Quad Drawer for 3
        {
            ParticleNodeCore->setDrawer(ExampleQuadParticleSystemDrawer);
        }
        if(e->getKey() == KeyEvent::KEY_F) //particles will be sorted from closest to the view point to the furthest
        {
            ParticleNodeCore->setSortingMode(ParticleSystemCore::FRONT_TO_BACK);
        }
        if(e->getKey() == KeyEvent::KEY_R) //particles will be sorted from furthest to the view point to the closest.
        {
            ParticleNodeCore->setSortingMode(ParticleSystemCore::BACK_TO_FRONT);
        }
        if(e->getKey() == KeyEvent::KEY_N) 
        {
            ParticleNodeCore->setSortingMode(ParticleSystemCore::NONE);
        }
        if(e->getKey() == KeyEvent::KEY_O) 
        {
            ExampleConditionalAffector->setConditionalOperator(1); //equals
        }
        if(e->getKey() == KeyEvent::KEY_P) 
        {
            ExampleConditionalAffector->setConditionalOperator(2); // not equal

        }
		if(e->getKey() == KeyEvent::KEY_H) 
        {
		    for(unsigned int i(0); i < ExampleParticleSystem->getNumParticles(); ++i)
			{
				ExampleParticleSystem->setAttribute("active",1,i);
			}
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

    //Add Key Listener
    TutorialKeyListener TheKeyListener;
    TutorialWindow->addKeyListener(&TheKeyListener);

    //Add Mouse Listeners
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
    ExampleParticleSystem = OSG::ParticleSystem::create();


    ExampleParticleSystem->attachUpdateListener(TutorialWindow);

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

    ExamplePointParticleSystemDrawer = OSG::PointParticleSystemDrawer::create();
    ExamplePointParticleSystemDrawer->setForcePerParticleSizing(false);

    Matrix ExampleMatrix;
    ExampleMatrix.setTransform(Vec3f(10.0,10.0,10.0));

    TransformRefPtr ExampleXform = OSG::Transform::create();
    ExampleXform->setMatrix(ExampleMatrix);


    NodeRefPtr ExampleNode = OSG::Node::create();
    ExampleNode->setCore(ExampleXform);

    ExampleGenerator = OSG::RateParticleGenerator::create();
    //		ExampleGenerator->setEmitInWorldSpace(true);
    ExampleGenerator->setBeacon(ExampleNode);
    ExampleGenerator->setGenerationRate(5.0);
    ExampleGenerator->setPositionDistribution(createPositionDistribution());
    ExampleGenerator->setLifespanDistribution(createLifespanDistribution());

    NewtonParticleAffectorRefPtr ExampleAffector = OSG::NewtonParticleAffector::create();
    ExampleAffector->setBeacon(ExampleNode);
    ExampleAffector->setMaxDistance(-1.0);

    ExampleConditionalAffector = OSG::ConditionalParticleAffector::create();
    ExampleConditionalAffector->setConditionalAttribute("active");
    ExampleConditionalAffector->setConditionalOperator(4); //greater than
    ExampleConditionalAffector->setConditionalValue(0); // testing if the value associated with "test" = 1
    ExampleConditionalAffector->pushToAffectors(ExampleAffector);

    DistanceAttractRepelParticleAffectorRefPtr ExampleAttractRepelAffector = OSG::DistanceAttractRepelParticleAffector::create();
    ExampleAttractRepelAffector->setDistanceFromSource(DistanceParticleAffector::DISTANCE_FROM_NODE);

    //Attach the Generators and affectors to the Particle System
    ExampleParticleSystem->setBeacon(ExampleNode);
    //ExampleParticleSystem->pushToGenerators(ExampleGenerator);
    ExampleParticleSystem->pushToAffectors(ExampleConditionalAffector);
   // ExampleParticleSystem->pushToAffectors(ExampleAttractRepelAffector);
    ExampleParticleSystem->setMaxParticles(1000);
    ExampleParticleSystem->setDynamic(true);

    //Particle System Core
    ParticleNodeCore = OSG::ParticleSystemCore::create();
    ParticleNodeCore->setSystem(ExampleParticleSystem);
    ParticleNodeCore->setDrawer(ExamplePointParticleSystemDrawer);
    ParticleNodeCore->setMaterial(PSMaterial);
    ParticleNodeCore->setSortingMode(ParticleSystemCore::BACK_TO_FRONT);

    NodeRefPtr PSNode = Node::create();
    PSNode->setCore(ParticleNodeCore);

    // Make Main Scene Node and add the Torus
    NodeRefPtr scene = OSG::Node::create();
    scene->setCore(OSG::Group::create());
    scene->addChild(PSNode);

    mgr->setRoot(scene);

    // Show the whole Scene
    mgr->showAll();
    mgr->getCamera()->setFar(1000.0);
    mgr->getCamera()->setNear(0.10);

    FCFileType::FCPtrStore Containers;
    Containers.insert(scene);

    FCFileType::FCTypeVector IgnoreTypes;
    //Save the Field Containers to a xml file
    //FCFileHandler::the()->write(Containers,BoostPath("./Data/TestFieldContainers.xml"),IgnoreTypes);

    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
                               WinSize,
                               "16FullTest");

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

