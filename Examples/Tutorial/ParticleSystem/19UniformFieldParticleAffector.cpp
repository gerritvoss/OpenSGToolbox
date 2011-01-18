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
#include "OSGLineParticleSystemDrawer.h"
#include "OSGPointParticleSystemDrawer.h"

#include "OSGRateParticleGenerator.h"
#include "OSGConeDistribution3D.h"
#include "OSGBoxDistribution3D.h"
#include "OSGUniformParticleAffector.h"

#include "OSGGaussianNormalDistribution1D.h"


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

Distribution3DRefPtr createPositionDistribution(void);
Distribution1DRefPtr createLifespanDistribution(void);

void keyTyped(KeyEventDetails* const details,
              SimpleSceneManager *mgr,
              ParticleSystemCore* const ParticleNodeCore,
              PointParticleSystemDrawer* const ExamplePointParticleSystemDrawer,
              LineParticleSystemDrawer* const ExampleLineParticleSystemDrawer,
              UniformParticleAffector* const ExampleUniformAffector             )
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
    if(details->getKey()== KeyEventDetails::KEY_R)
    {   // reverse the magnitude of the field
        ExampleUniformAffector->setMagnitude(-(ExampleUniformAffector->getMagnitude()));


    }

    // change direction of the field
    if(details->getKey()== KeyEventDetails::KEY_A)
    {
        ExampleUniformAffector->setDirection(Vec3f(-1.0,0.0,0.0));

    }
    if(details->getKey()== KeyEventDetails::KEY_W)
    {
        ExampleUniformAffector->setDirection(Vec3f(0.0,1.0,0.0));

    }
    if(details->getKey()== KeyEventDetails::KEY_S)
    {
        ExampleUniformAffector->setDirection(Vec3f(0.0,-1.0,0.0));

    }
    if(details->getKey()== KeyEventDetails::KEY_D)
    {
        ExampleUniformAffector->setDirection(Vec3f(1.0,0.0,0.0));

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
        PSPointChunk->setSize(5.0f);
        PSPointChunk->setSmooth(true);

        BlendChunkRefPtr PSBlendChunk = BlendChunk::create();
        PSBlendChunk->setSrcFactor(GL_SRC_ALPHA);
        PSBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

        MaterialChunkRefPtr PSMaterialChunkChunk = MaterialChunk::create();
        PSMaterialChunkChunk->setAmbient(Color4f(1.0f,1.0f,1.0f,1.0f));
        PSMaterialChunkChunk->setDiffuse(Color4f(0.7f,0.7f,0.7f,1.0f));
        PSMaterialChunkChunk->setSpecular(Color4f(0.9f,0.9f,0.9f,1.0f));
        PSMaterialChunkChunk->setColorMaterial(GL_NONE);

        ChunkMaterialRefPtr PSMaterial = ChunkMaterial::create();
        PSMaterial->addChunk(PSPointChunk);
        PSMaterial->addChunk(PSMaterialChunkChunk);
        PSMaterial->addChunk(PSBlendChunk);

        //Particle System
        ParticleSystemRefPtr ExampleParticleSystem = ParticleSystem::create();
        ExampleParticleSystem->addParticle(Pnt3f(0,25,0),
                                           Vec3f(0.0,0.0f,1.0f),
                                           Color4f(1.0,1.0,1.0,1.0), 
                                           Vec3f(1.0,1.0,1.0), 
                                           0.1, 
                                           Vec3f(0.0f,0.0f,0.0f), //Velocity
                                           Vec3f(0.0f,0.0f,0.0f)
                                          );
        ExampleParticleSystem->addParticle(Pnt3f(0,-25,0),
                                           Vec3f(0.0,0.0f,1.0f),
                                           Color4f(1.0,1.0,1.0,1.0), 
                                           Vec3f(1.0,1.0,1.0), 
                                           0.1, 
                                           Vec3f(0.0f,0.0f,0.0f), //Velocity
                                           Vec3f(0.0f,0.0f,0.0f)
                                          );
        ExampleParticleSystem->attachUpdateProducer(TutorialWindow);

        //Particle System Drawer (Point)
        PointParticleSystemDrawerRecPtr ExamplePointParticleSystemDrawer = PointParticleSystemDrawer::create();

        //Particle System Drawer (line)
        LineParticleSystemDrawerRecPtr ExampleLineParticleSystemDrawer = LineParticleSystemDrawer::create();
        ExampleLineParticleSystemDrawer->setLineDirectionSource(LineParticleSystemDrawer::DIRECTION_VELOCITY);
        ExampleLineParticleSystemDrawer->setLineLengthSource(LineParticleSystemDrawer::LENGTH_SIZE_X);
        ExampleLineParticleSystemDrawer->setLineLength(2.0f);
        ExampleLineParticleSystemDrawer->setEndPointFading(Vec2f(0.0f,1.0f));

        //Create a Rate Particle Generator
        RateParticleGeneratorRefPtr ExampleGenerator = RateParticleGenerator::create();

        //Attach the function objects to the Generator
        ExampleGenerator->setPositionDistribution(createPositionDistribution());
        ExampleGenerator->setLifespanDistribution(createLifespanDistribution());
        ExampleGenerator->setGenerationRate(200);

        UniformParticleAffectorRecPtr ExampleUniformAffector = UniformParticleAffector::create();
        ExampleUniformAffector->setMagnitude(20.0); // force which the field exerts on particles (negative = towards the air field's beacon location)
        NodeRefPtr UniformBeacon = Node::create();
        ExampleUniformAffector->setBeacon(UniformBeacon); // set to 'emulate' from (0,0,0)
        ExampleUniformAffector->setDirection(Vec3f(1.0,0.0,0.0)); // direction which field is exerted
        ExampleUniformAffector->setMaxDistance(-1.0); // particles affected regardless of distance from
        ExampleUniformAffector->setAttenuation(0.0); // strength of uniform field dimishes by dist^attenuation, in this case it is constant regardless of distance
        ExampleUniformAffector->setParticleMass(10.0);



        //Attach the Generator and Affector to the Particle System
        ExampleParticleSystem->pushToGenerators(ExampleGenerator);
        ExampleParticleSystem->pushToAffectors(ExampleUniformAffector);
        ExampleParticleSystem->setMaxParticles(500);


        //Particle System Node
        ParticleSystemCoreRecPtr ParticleNodeCore = ParticleSystemCore::create();
        ParticleNodeCore->setSystem(ExampleParticleSystem);
        ParticleNodeCore->setDrawer(ExamplePointParticleSystemDrawer);
        ParticleNodeCore->setMaterial(PSMaterial);

        NodeRefPtr ParticleNode = Node::create();
        ParticleNode->setCore(ParticleNodeCore);


        // Make Main Scene Node and add the Torus
        NodeRefPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(ParticleNode);

        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1,
                                                    &sceneManager,
                                                    ParticleNodeCore.get(),
                                                    ExamplePointParticleSystemDrawer.get(),
                                                    ExampleLineParticleSystemDrawer.get(),
                                                    ExampleUniformAffector.get()));

        sceneManager.setRoot(scene);

        // Show the whole Scene
        sceneManager.showAll();

        sceneManager.getCamera()->setFar(1000.0);

        std::cout << "Uniform Particle Affector Tutorial Controls:\n"
            << "1: Use point drawer\n"
            << "2: Use line drawer\n"
            << "W,A,S,D: Change direction of field\n"
            << "Ctrl + Q: Exit Tutorial";

        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "19UniformFieldParticleAffector");

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
    BoxDistribution3DRefPtr TheBoxDistribution = BoxDistribution3D::create();
    TheBoxDistribution->setMinPoint(Pnt3f(-10.0f,-10.0f,-10.0f));
    TheBoxDistribution->setMaxPoint(Pnt3f(10.0f,10.0f,10.0f));
    TheBoxDistribution->setSurfaceOrVolume(BoxDistribution3D::VOLUME);


    return TheBoxDistribution;
}

Distribution1DRefPtr createLifespanDistribution(void)
{
    GaussianNormalDistribution1DRefPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    TheLifespanDistribution->setMean(15.0f);
    TheLifespanDistribution->setStandardDeviation(3.0);

    return TheLifespanDistribution;
}
