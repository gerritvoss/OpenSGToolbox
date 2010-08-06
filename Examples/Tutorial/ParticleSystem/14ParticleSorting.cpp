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


//Particle System Generator
RateParticleGeneratorRefPtr ExampleGenerator;


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
        if(e->getKey() == KeyEvent::KEY_N) //particles will not be sorted
        {
            ParticleNodeCore->setSortingMode(ParticleSystemCore::NONE);
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
    ParticleSystemRefPtr ExampleParticleSystem = OSG::ParticleSystem::create();
    ExampleParticleSystem->attachUpdateListener(TutorialWindow);

    //Particle System Drawer
    //Point
    ExamplePointParticleSystemDrawer = OSG::PointParticleSystemDrawer::create();
    //ExamplePointParticleSystemDrawer->setForcePerParticleSizing(true);

    //Line
    ExampleLineParticleSystemDrawer = OSG::LineParticleSystemDrawer::create();
    ExampleLineParticleSystemDrawer->setLineDirectionSource(LineParticleSystemDrawer::DIRECTION_NORMAL);//DIRECTION_VELOCITY_CHANGE);
    ExampleLineParticleSystemDrawer->setLineLengthSource(LineParticleSystemDrawer::LENGTH_SIZE_X);
    ExampleLineParticleSystemDrawer->setEndPointFading(Vec2f(1.0,0.0));
    //Quad
    ExampleQuadParticleSystemDrawer = OSG::QuadParticleSystemDrawer::create();
    ExampleQuadParticleSystemDrawer->setQuadSizeScaling(Vec2f(0.1,0.1));
    ExampleQuadParticleSystemDrawer->setNormalAndUpSource(QuadParticleSystemDrawer::NORMAL_PARTICLE_NORMAL,QuadParticleSystemDrawer::UP_STATIC);

    RateParticleGeneratorRefPtr ExampleGeneratorTheSequel = OSG::RateParticleGenerator::create();

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
    ParticleNodeCore = OSG::ParticleSystemCore::create();
    ParticleNodeCore->setSystem(ExampleParticleSystem);
    ParticleNodeCore->setDrawer(ExamplePointParticleSystemDrawer);
    ParticleNodeCore->setMaterial(PSMaterial);

    NodeRefPtr ParticleNode = OSG::Node::create();
    ParticleNode->setCore(ParticleNodeCore);


    // Make Main Scene Node and add the Torus
    NodeRefPtr scene = OSG::Node::create();
    scene->setCore(OSG::Group::create());
    scene->addChild(ParticleNode);

    mgr->setRoot(scene);

    // Show the whole Scene
    mgr->showAll();

    mgr->getCamera()->setFar(500.0);

    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
                               WinSize,
                               "14ParticleSorting");

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

