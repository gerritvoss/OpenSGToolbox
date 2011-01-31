// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"
#include "OSGSimpleGeometry.h"
#include "OSGWindowUtils.h"

#include "OSGBlendChunk.h"
#include "OSGTextureObjChunk.h"
#include "OSGTextureEnvChunk.h"
#include "OSGImageFileHandler.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGParticleSystem.h"
#include "OSGParticleSystemCore.h"
#include "OSGPointParticleSystemDrawer.h"

#include "OSGSphereDistribution3D.h"
#include "OSGQuadParticleSystemDrawer.h"
#include "OSGQuadParticleSystemDrawer.h"
#include "OSGBurstParticleGenerator.h"


#include "OSGGaussianNormalDistribution1D.h"
#include "OSGCylinderDistribution3D.h"
#include "OSGLineDistribution3D.h"
//#include "OSGSizeDistribution3D.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

Distribution3DRefPtr createPositionDistribution(void);
Distribution1DRefPtr createLifespanDistribution(void);
Distribution3DRefPtr createVelocityDistribution(void);
Distribution3DRefPtr createAccelerationDistribution(void);
Distribution3DRefPtr createSizeDistribution(void);

void keyTyped(KeyEventDetails* const details,
              SimpleSceneManager *mgr,
              ParticleSystem* const ExampleParticleSystem,
              BurstParticleGenerator* const ExampleBurstGenerator,
              QuadParticleSystemDrawer* const ExampleParticleSystemDrawer
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
    UInt32 CHANGE_SOURCE;
    if(details->getKey()== KeyEventDetails::KEY_P)
    {

        CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_POSITION_CHANGE;
    }

    else if(details->getKey()== KeyEventDetails::KEY_C)
    {
        CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_VELOCITY_CHANGE;
    }

    else if(details->getKey()== KeyEventDetails::KEY_V)
    {
        CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_VELOCITY;
    }

    else if(details->getKey()== KeyEventDetails::KEY_A)
    {
        CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_ACCELERATION;
    }

    else  if(details->getKey()== KeyEventDetails::KEY_N)
    {
        CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_PARTICLE_NORMAL;
    }

    else if(details->getKey()== KeyEventDetails::KEY_D)
    {
        CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_VIEW_POSITION;
    }

    else if(details->getKey()== KeyEventDetails::KEY_S)
    {
        CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_STATIC;
    }

    else  if(details->getKey()== KeyEventDetails::KEY_W)
    {
        CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_VIEW_DIRECTION;
    }
    else {
        return;
    }
    ExampleParticleSystemDrawer->setNormalAndUpSource(CHANGE_SOURCE,QuadParticleSystemDrawer::UP_STATIC);

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
        TextureObjChunkRefPtr QuadTextureChunk = TextureObjChunk::create();
        ImageRefPtr LoadedImage = ImageFileHandler::the()->read("Data/Cloud.png");    
        QuadTextureChunk->setImage(LoadedImage);


        TextureEnvChunkRefPtr QuadTextureEnvChunk = TextureEnvChunk::create();
        QuadTextureEnvChunk->setEnvMode(GL_MODULATE);

        BlendChunkRefPtr PSBlendChunk = BlendChunk::create();
        PSBlendChunk->setSrcFactor(GL_SRC_ALPHA);
        PSBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

        MaterialChunkRefPtr PSMaterialChunk = MaterialChunk::create();
        PSMaterialChunk->setAmbient(Color4f(0.3f,0.3f,0.3f,1.0f));
        PSMaterialChunk->setDiffuse(Color4f(0.7f,0.7f,0.7f,1.0f));
        PSMaterialChunk->setSpecular(Color4f(0.9f,0.9f,0.9f,1.0f));
        PSMaterialChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);

        ChunkMaterialRefPtr PSMaterial = ChunkMaterial::create();
        PSMaterial->addChunk(QuadTextureChunk);
        PSMaterial->addChunk(QuadTextureEnvChunk);
        PSMaterial->addChunk(PSMaterialChunk);
        PSMaterial->addChunk(PSBlendChunk);



        //Particle System

        ParticleSystemRecPtr ExampleParticleSystem = ParticleSystem::create();
        ExampleParticleSystem->attachUpdateProducer(TutorialWindow);

        //Particle System Drawer
        QuadParticleSystemDrawerRefPtr ExampleParticleSystemDrawer = QuadParticleSystemDrawer::create();


        BurstParticleGeneratorRecPtr ExampleBurstGenerator = BurstParticleGenerator::create();
        //Attach the function objects to the Generator
        ExampleBurstGenerator->setPositionDistribution(createPositionDistribution());
        ExampleBurstGenerator->setLifespanDistribution(createLifespanDistribution());
        ExampleBurstGenerator->setBurstAmount(50.0);
        ExampleBurstGenerator->setVelocityDistribution(createVelocityDistribution());
        ExampleBurstGenerator->setAccelerationDistribution(createAccelerationDistribution());
        ExampleBurstGenerator->setSizeDistribution(createSizeDistribution());

        //Particle System Node
        ParticleSystemCoreRefPtr ParticleNodeCore = ParticleSystemCore::create();
        ParticleNodeCore->setSystem(ExampleParticleSystem);
        ParticleNodeCore->setDrawer(ExampleParticleSystemDrawer);
        ParticleNodeCore->setMaterial(PSMaterial);

        NodeRefPtr ParticleNode = Node::create();
        ParticleNode->setCore(ParticleNodeCore);

        //Ground Node
        NodeRefPtr GoundNode = makePlane(30.0,30.0,10,10);

        Matrix GroundTransformation;
        GroundTransformation.setRotate(Quaternion(Vec3f(1.0f,0.0,0.0), -3.14195f));
        TransformRefPtr GroundTransformCore = Transform::create();
        GroundTransformCore->setMatrix(GroundTransformation);

        NodeRefPtr GroundTransformNode = Node::create();
        GroundTransformNode->setCore(GroundTransformCore);
        GroundTransformNode->addChild(GoundNode);


        // Make Main Scene Node and add the Torus
        NodeRefPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(ParticleNode);
        scene->addChild(GroundTransformNode);


        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1,
                                                    &sceneManager,
                                                    ExampleParticleSystem.get(),
                                                    ExampleBurstGenerator.get(),
                                                    ExampleParticleSystemDrawer.get()));
        sceneManager.setRoot(scene);

        // Show the whole Scene
        sceneManager.showAll();


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "05QuadParticleDrawer");

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

Distribution3DRefPtr createVelocityDistribution(void)
{


    //Sphere Distribution
    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,1.0));
    TheSphereDistribution->setInnerRadius(5.0);
    TheSphereDistribution->setOuterRadius(15.0);
    TheSphereDistribution->setMinTheta(-3.141950);
    TheSphereDistribution->setMaxTheta(3.141950);
    TheSphereDistribution->setMinZ(0.0);
    TheSphereDistribution->setMaxZ(1.0);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::VOLUME);

    return TheSphereDistribution;
}



Distribution1DRefPtr createLifespanDistribution(void)
{
    GaussianNormalDistribution1DRefPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    TheLifespanDistribution->setMean(10.0f);
    TheLifespanDistribution->setStandardDeviation(2.0);

    return TheLifespanDistribution;
}

Distribution3DRefPtr createAccelerationDistribution(void)
{

    //Sphere Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(0.0,0.0,-3.0));
    TheLineDistribution->setPoint2(Pnt3f(0.0,0.0,-3.0));

    return TheLineDistribution;
}

Distribution3DRefPtr createSizeDistribution(void)
{
    //Line Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(0.2,0.2,1.0));
    TheLineDistribution->setPoint2(Pnt3f(1.0,1.0,1.0));

    return TheLineDistribution;
}
