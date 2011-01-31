// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"
#include "OSGWindowUtils.h"


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

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

Distribution3DRefPtr createPositionDistribution(void);
Distribution1DRefPtr createLifespanDistribution(void);

void keyTyped(KeyEventDetails* const details,
              SimpleSceneManager *mgr,
              ParticleSystem* const ExampleParticleSystem,
              RandomMovementParticleAffector* const ExampleRMA,
              AttributeAttractRepelParticleAffector* const ExampleAttributeAttractRepelParticleAffector
             )
{
    if(details->getKey() == KeyEventDetails::KEY_Q &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
    else
    {
        switch(details->getKey())
        {
            case KeyEventDetails::KEY_R:
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
            case KeyEventDetails::KEY_A:
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

        ParticleSystemRecPtr ExampleParticleSystem = ParticleSystem::create();
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
        ExampleParticleSystem->attachUpdateProducer(TutorialWindow);

        RandomMovementParticleAffectorRecPtr ExampleRMA = RandomMovementParticleAffector::create();
        ExampleRMA->setAmplitude(100.0f);

        AttributeAttractRepelParticleAffectorRecPtr ExampleAttributeAttractRepelParticleAffector = AttributeAttractRepelParticleAffector::create();
        ExampleAttributeAttractRepelParticleAffector->setAttributeAffected(RandomMovementParticleAffector::POSITION_ATTRIBUTE);
        ExampleAttributeAttractRepelParticleAffector->setMinDistance(0.0);
        ExampleAttributeAttractRepelParticleAffector->setMaxDistance(10000000000000.0);
        ExampleAttributeAttractRepelParticleAffector->setQuadratic(0.01);
        ExampleAttributeAttractRepelParticleAffector->setLinear(0.01);
        ExampleAttributeAttractRepelParticleAffector->setConstant(0.0);

        ExampleParticleSystem->pushToAffectors(ExampleRMA);
        ExampleParticleSystem->pushToAffectors(ExampleAttributeAttractRepelParticleAffector);
        ExampleParticleSystem->setUpdateSecAttribs(false);

        //Particle System Drawer
        QuadParticleSystemDrawerRefPtr ExampleParticleSystemDrawer = QuadParticleSystemDrawer::create();


        //Particle System Node
        ParticleSystemCoreRefPtr ParticleNodeCore = ParticleSystemCore::create();
        ParticleNodeCore->setSystem(ExampleParticleSystem);
        ParticleNodeCore->setDrawer(ExampleParticleSystemDrawer);
        ParticleNodeCore->setMaterial(PSMaterial);

        NodeRefPtr ParticleNode = Node::create();
        ParticleNode->setCore(ParticleNodeCore);


        // Make Main Scene Node
        NodeRefPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(ParticleNode);


        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1,
                                                    &sceneManager,
                                                    ExampleParticleSystem.get(),
                                                    ExampleRMA.get(),
                                                    ExampleAttributeAttractRepelParticleAffector.get()));
        sceneManager.setRoot(scene);

        // Show the whole Scene
        sceneManager.showAll();

        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "17RandomMovement");

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
