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
#include "OSGParticleSystem.h"
#include "OSGParticleSystemCore.h"
#include "OSGQuadParticleSystemDrawer.h"
#include "OSGRandomMovementParticleAffector.h"
#include "OSGAttributeAttractRepelParticleAffector.h"


#include "OSGGaussianNormalDistribution1D.h"
#include "OSGCylinderDistribution3D.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

AttributeAttractRepelParticleAffectorRefPtr ExampleAttributeAttractRepelParticleAffector;
ParticleSystemRefPtr ExampleParticleSystem;
RandomMovementParticleAffectorRefPtr ExampleRMA;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

Distribution3DRefPtr createPositionDistribution(void);
Distribution1DRefPtr createLifespanDistribution(void);

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
        else
        {
            switch(e->getKey())
            {
                case KeyEvent::KEY_R:
                    {
                        if(ExampleParticleSystem->editMFAffectors()->find(ExampleRMA)
                           == ExampleParticleSystem->getMFAffectors()->end())
                        {
                            ExampleParticleSystem->pushToAffectors(ExampleRMA);
                        }
                        else
                        {
                            ExampleParticleSystem->removeObjFromAffectors(ExampleRMA);
                        }
                    }
                    break;
                case KeyEvent::KEY_A:
                    if(ExampleParticleSystem->editMFAffectors()->find(ExampleAttributeAttractRepelParticleAffector)
                       == ExampleParticleSystem->getMFAffectors()->end())
                    {
                        ExampleParticleSystem->pushToAffectors(ExampleAttributeAttractRepelParticleAffector);
                    }
                    else
                    {
                        ExampleParticleSystem->removeObjFromAffectors(ExampleAttributeAttractRepelParticleAffector);
                    }
                    break;
            }
        }
    }

    virtual void keyReleased(const KeyEventUnrecPtr e)
    {
    }

    virtual void keyTyped(const KeyEventUnrecPtr e)
    {
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
    MaterialChunkRefPtr PSMaterialChunkChunk = MaterialChunk::create();
    PSMaterialChunkChunk->setAmbient(Color4f(0.3f,0.3f,0.3f,1.0f));
    PSMaterialChunkChunk->setDiffuse(Color4f(0.7f,0.7f,0.7f,1.0f));
    PSMaterialChunkChunk->setSpecular(Color4f(0.9f,0.9f,0.9f,1.0f));
    PSMaterialChunkChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);

    ChunkMaterialRefPtr PSMaterial = ChunkMaterial::create();
    PSMaterial->addChunk(PSMaterialChunkChunk);

    Distribution3DRefPtr PositionDistribution = createPositionDistribution();

    Pnt3f PositionReturnValue;

    //Particle System

    ExampleParticleSystem = OSG::ParticleSystem::create();
    for(UInt32 i(0) ; i<500 ; ++i)//controls how many particles are created
    {
        if(PositionDistribution != NULL)
        {
            PositionReturnValue = Pnt3f(PositionDistribution->generate());
        }

        ExampleParticleSystem->addParticle(
                                           PositionReturnValue,
                                           PositionReturnValue,
                                           Vec3f(0.0f,0.0f,1.0f),
                                           Color4f(1.0,0.0,0.0,1.0), 
                                           Vec3f(1.0,1.0,1.0), 
                                           -1, 0,
                                           Vec3f(0.0,0.0,0.0),			Vec3f(0.0f,0.0f,0.0f), //Velocity
                                           Vec3f(0.0f,0.0f,0.0f),	//acceleration
                                           StringToUInt32Map()	 );
    }
    ExampleParticleSystem->attachUpdateListener(TutorialWindow);

    //Particle System Drawer
    QuadParticleSystemDrawerRefPtr ExampleParticleSystemDrawer = OSG::QuadParticleSystemDrawer::create();


    //Particle System Node
    ParticleSystemCoreRefPtr ParticleNodeCore = OSG::ParticleSystemCore::create();
    ParticleNodeCore->setSystem(ExampleParticleSystem);
    ParticleNodeCore->setDrawer(ExampleParticleSystemDrawer);
    ParticleNodeCore->setMaterial(PSMaterial);

    NodeRefPtr ParticleNode = OSG::Node::create();
    ParticleNode->setCore(ParticleNodeCore);


    // Make Main Scene Node
    NodeRefPtr scene = OSG::Node::create();
    scene->setCore(OSG::Group::create());
    scene->addChild(ParticleNode);

    mgr->setRoot(scene);

    // Show the whole Scene
    mgr->showAll();

    ExampleRMA = OSG::RandomMovementParticleAffector::create();
    ExampleRMA->setAmplitude(100.0f);

    ExampleAttributeAttractRepelParticleAffector = OSG::AttributeAttractRepelParticleAffector::create();
    ExampleAttributeAttractRepelParticleAffector->setAttributeAffected(RandomMovementParticleAffector::POSITION_ATTRIBUTE);
    ExampleAttributeAttractRepelParticleAffector->setMinDistance(0.0);
    ExampleAttributeAttractRepelParticleAffector->setMaxDistance(10000000000000.0);
    ExampleAttributeAttractRepelParticleAffector->setQuadratic(0.01);
    ExampleAttributeAttractRepelParticleAffector->setLinear(0.01);
    ExampleAttributeAttractRepelParticleAffector->setConstant(0.0);

    ExampleParticleSystem->pushToAffectors(ExampleRMA);
    ExampleParticleSystem->pushToAffectors(ExampleAttributeAttractRepelParticleAffector);
    ExampleParticleSystem->setUpdateSecAttribs(false);

    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
                               WinSize,
                               "17RandomMovement");

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
    TheCylinderDistribution->setInnerRadius(10.0);
    TheCylinderDistribution->setOuterRadius(30.0);
    TheCylinderDistribution->setMinTheta(0.0);
    TheCylinderDistribution->setMaxTheta(6.283185);
    TheCylinderDistribution->setHeight(50.0);
    TheCylinderDistribution->setNormal(Vec3f(0.0,0.0,1.0));
    TheCylinderDistribution->setSurfaceOrVolume(CylinderDistribution3D::SURFACE);

    return TheCylinderDistribution;
}

Distribution1DRefPtr createLifespanDistribution(void)
{
    GaussianNormalDistribution1DRefPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    TheLifespanDistribution->setMean(60.0f);
    TheLifespanDistribution->setStandardDeviation(10.0);

    return TheLifespanDistribution;
}
