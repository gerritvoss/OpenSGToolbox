// NOTE: If the images are not loading correctly, make sure the working 
// directory is set to the location of the .cpp file for this tutorial.

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
#include "OSGRateParticleGenerator.h"

#include "OSGQuadSequenceParticleSystemDrawer.h"
#include "OSGAgeParticleFunction.h"
#include "OSGAgeSizeParticleAffector.h"
#include "OSGAgeFadeParticleAffector.h"
#include "OSGVortexParticleAffector.h"

#include "OSGGaussianNormalDistribution1D.h"
#include "OSGCylinderDistribution3D.h"
#include "OSGLineDistribution3D.h"
#include "OSGSphereDistribution3D.h"


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

Distribution3DRecPtr createPositionDistribution(void);
Distribution1DRecPtr createLifespanDistribution(void);
Distribution3DRecPtr createVelocityDistribution(void);
Distribution3DRecPtr createAccelerationDistribution(void);
Distribution3DRecPtr createSizeDistribution(void);

Distribution3DRefPtr createSmokeColorDistribution(void);
Distribution3DRecPtr createSmokePositionDistribution(void);
Distribution1DRecPtr createSmokeLifespanDistribution(void);
Distribution3DRecPtr createSmokeVelocityDistribution(void);
Distribution3DRecPtr createSmokeSizeDistribution(void);

void keyTyped(KeyEventDetails* const details,
              SimpleSceneManager *mgr,
              AgeParticleFunction* const AgeFunc
             )
{
    if(details->getKey() == KeyEventDetails::KEY_Q &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
    if (details->getKey() == KeyEventDetails::KEY_1)
    {
        AgeFunc->setSequenceOrder(AgeParticleFunction::CYCLE);
    }		
    else if (details->getKey() == KeyEventDetails::KEY_2)
    {
        AgeFunc->setSequenceOrder(AgeParticleFunction::REVERSE_CYCLE);
    }
    else if (details->getKey() == KeyEventDetails::KEY_3)
    {
        AgeFunc->setSequenceOrder(AgeParticleFunction::CUSTOM);
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
    preloadSharedObject("OSGImageFileIO");
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

        // Creating the Particle System Material
        // Here, the image is loaded.  The entire image sequence is conatined in one image,
        // which reduces texture memory overhead and runs faster.
        TextureObjChunkRefPtr QuadTextureChunk = TextureObjChunk::create();
        ImageRefPtr LoadedImage = ImageFileHandler::the()->read("Data/Explosion.png");    
        QuadTextureChunk->setImage(LoadedImage);

        TextureEnvChunkRefPtr QuadTextureEnvChunk = TextureEnvChunk::create();
        QuadTextureEnvChunk->setEnvMode(GL_MODULATE);

        BlendChunkRefPtr PSBlendChunk = BlendChunk::create();
        PSBlendChunk->setSrcFactor(GL_SRC_ALPHA);
        PSBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

        MaterialChunkRefPtr PSMaterialChunk = MaterialChunk::create();
        PSMaterialChunk->setLit(false);

        ChunkMaterialRefPtr PSMaterial = ChunkMaterial::create();
        PSMaterial->addChunk(QuadTextureChunk);
        PSMaterial->addChunk(QuadTextureEnvChunk);
        PSMaterial->addChunk(PSMaterialChunk);
        PSMaterial->addChunk(PSBlendChunk);

        //Particle System
        ParticleSystemRecPtr ExplosionParticleSystem = ParticleSystem::create();
        ExplosionParticleSystem->attachUpdateProducer(TutorialWindow);

        //Age Particle Function.  Controls which image is shown when, based on the age of a particle.
        AgeParticleFunctionRecPtr AgeFunc = AgeParticleFunction::create();
        AgeFunc->setSequenceTime(0.07f); // image changes every 0.1 seconds.
        AgeFunc->setSequenceOrder(AgeParticleFunction::CUSTOM); // using the custom sequence below.
        /*
           Here, a custom sequence for the image ordering is assembled.  The image sequence will be shown in 
           the order specified here.  Once the end of the sequence is reached, the sequence repeats.
           */
        UInt32 NumImages(25);
        for(UInt32 i(0) ; i<NumImages ; ++i)
        {
            AgeFunc->editMFCustomSequence()->push_back(i);
        }

        //Particle System Drawer - 
        QuadSequenceParticleSystemDrawerRecPtr ExplosionParticleSystemDrawer = QuadSequenceParticleSystemDrawer::create();
        // image dimensions (in pixels) are required if there is a border on the images.
        ExplosionParticleSystemDrawer->setImageDimensions(Vec2us(320,320));
        // The "dimensions" of the sequence contained in the image.  For this image,
        // there are 3 images in the "x" direction, and two in the "y" direction, for a 
        // total of 6.
        ExplosionParticleSystemDrawer->setSequenceDimensions(Vec2b(5,5));
        // width of the border on each side of the image, in pixels.
        ExplosionParticleSystemDrawer->setBorderOffsets(Vec2b(0,0));
        // this is the age function we just created above.
        ExplosionParticleSystemDrawer->setSequenceFunction(AgeFunc);

        RateParticleGeneratorRecPtr ExplosionParticleGenerator = RateParticleGenerator::create();
        //Attach the function objects to the Generator
        ExplosionParticleGenerator->setPositionDistribution(createPositionDistribution());
        ExplosionParticleGenerator->setLifespanDistribution(createLifespanDistribution());
        ExplosionParticleGenerator->setVelocityDistribution(createVelocityDistribution());
        ExplosionParticleGenerator->setAccelerationDistribution(createAccelerationDistribution());
        ExplosionParticleGenerator->setSizeDistribution(createSizeDistribution());
        ExplosionParticleGenerator->setGenerationRate(100.0f);

        //Particle System Node
        ParticleSystemCoreRefPtr ExplosionParticleCore = ParticleSystemCore::create();
        ExplosionParticleCore->setSystem(ExplosionParticleSystem);
        ExplosionParticleCore->setDrawer(ExplosionParticleSystemDrawer);
        ExplosionParticleCore->setMaterial(PSMaterial);
        ExplosionParticleCore->setSortingMode(ParticleSystemCore::BACK_TO_FRONT);

        NodeRefPtr ExplosionParticleNode = Node::create();
        ExplosionParticleNode->setCore(ExplosionParticleCore);

        ExplosionParticleSystem->addParticle(Pnt3f(10.0,0.0,0.0),
                                           Vec3f(0.0,1.0,0.0),
                                           Color4f(1.0,1.0,1.0,1.0),
                                           Vec3f(1.0,1.0,1.0),
                                           0.01,
                                           Vec3f(0.0,0.0,0.0),
                                           Vec3f(0.0,0.0,0.0));

        ExplosionParticleSystem->addParticle(Pnt3f(-10.0,0.0,0.0),
                                           Vec3f(0.0,1.0,0.0),
                                           Color4f(1.0,1.0,1.0,1.0),
                                           Vec3f(1.0,1.0,1.0),
                                           0.01,
                                           Vec3f(0.0,0.0,0.0),
                                           Vec3f(0.0,0.0,0.0));

        ExplosionParticleSystem->pushToGenerators(ExplosionParticleGenerator);

        AgeSizeParticleAffectorRecPtr ExampleAgeSizeParticleAffector = AgeSizeParticleAffector::create();

        //Age and size
        ExampleAgeSizeParticleAffector->editMFAges()->push_back(0.0);
        ExampleAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(0.2,0.2,0.2));
        ExampleAgeSizeParticleAffector->editMFAges()->push_back(1.0);
        ExampleAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(4.0,4.0,4.0));
        ExampleAgeSizeParticleAffector->editMFAges()->push_back(1.8);
        ExampleAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(2.2,2.2,0.1));

        //Age Fade Affector
        AgeFadeParticleAffectorRecPtr ExampleAgeFadeParticleAffector = AgeFadeParticleAffector::create();

        //Age and size
        ExampleAgeFadeParticleAffector->setStartAlpha(0.0f);
        ExampleAgeFadeParticleAffector->setFadeInTime(0.5f);
        ExampleAgeFadeParticleAffector->setFadeToAlpha(1.0f);
        ExampleAgeFadeParticleAffector->setFadeOutTime(0.5f);
        ExampleAgeFadeParticleAffector->setEndAlpha(0.0f);
        ExplosionParticleSystem->pushToAffectors(ExampleAgeFadeParticleAffector);

        //Smoke Particle System
        VortexParticleAffectorRecPtr SmokeVortexAffector = VortexParticleAffector::create();
        SmokeVortexAffector->setMagnitude(0.2); 
        SmokeVortexAffector->setVortexAxis(Vec3f(0.0,1.0,0.0)); // field rotates around y axis
        NodeRefPtr VortexBeacon = makeCoredNode<Group>();
        SmokeVortexAffector->setBeacon(VortexBeacon); // set to 'emulate' from (0,0,0)
        SmokeVortexAffector->setMaxDistance(-1.0); // particles affected regardless of distance
        SmokeVortexAffector->setAttenuation(0.25); // strength of uniform field dimishes by dist^attenuation

        AgeFadeParticleAffectorRecPtr SmokeAgeFadeParticleAffector = AgeFadeParticleAffector::create();

        //Age and size
        SmokeAgeFadeParticleAffector->setStartAlpha(0.0f);
        SmokeAgeFadeParticleAffector->setFadeInTime(0.2f);
        SmokeAgeFadeParticleAffector->setFadeToAlpha(1.0f);
        SmokeAgeFadeParticleAffector->setFadeOutTime(3.5f);
        SmokeAgeFadeParticleAffector->setEndAlpha(0.0f);

        RateParticleGeneratorRecPtr SmokeParticleGenerator = RateParticleGenerator::create();
        SmokeParticleGenerator->setSizeDistribution(createSmokeSizeDistribution());
        SmokeParticleGenerator->setPositionDistribution(createSmokePositionDistribution());
        SmokeParticleGenerator->setLifespanDistribution(createSmokeLifespanDistribution());
        SmokeParticleGenerator->setVelocityDistribution(createSmokeVelocityDistribution());
        SmokeParticleGenerator->setColorDistribution(createSmokeColorDistribution());
        SmokeParticleGenerator->setGenerationRate(80.0f);

        ParticleSystemRecPtr SmokeParticleSystem = ParticleSystem::create();
        SmokeParticleSystem->pushToGenerators(SmokeParticleGenerator);
        SmokeParticleSystem->attachUpdateProducer(TutorialWindow);
        SmokeParticleSystem->pushToAffectors(SmokeAgeFadeParticleAffector);
        SmokeParticleSystem->pushToAffectors(SmokeVortexAffector);

        TextureObjChunkRefPtr SmokeTextureObjChunk = TextureObjChunk::create();
        ImageRefPtr SmokeImage = ImageFileHandler::the()->read("Data/Smoke.png");    
        SmokeTextureObjChunk->setImage(SmokeImage);

        ChunkMaterialRefPtr SmokeMaterial = ChunkMaterial::create();
        SmokeMaterial->addChunk(SmokeTextureObjChunk);
        SmokeMaterial->addChunk(QuadTextureEnvChunk);
        SmokeMaterial->addChunk(PSMaterialChunk);
        SmokeMaterial->addChunk(PSBlendChunk);
        SmokeMaterial->setSortKey(-1.0f);

        QuadParticleSystemDrawerRecPtr SmokeParticleSystemDrawer = QuadParticleSystemDrawer::create();

        ParticleSystemCoreRefPtr SmokeParticleCore = ParticleSystemCore::create();
        SmokeParticleCore->setSystem(SmokeParticleSystem);
        SmokeParticleCore->setDrawer(SmokeParticleSystemDrawer);
        SmokeParticleCore->setMaterial(SmokeMaterial);
        SmokeParticleCore->setSortingMode(ParticleSystemCore::BACK_TO_FRONT);

        NodeRefPtr SmokeParticleNode = Node::create();
        SmokeParticleNode->setCore(SmokeParticleCore);

        // Make Main Scene Node and add the Torus
        NodeRefPtr scene = makeCoredNode<Group>();
        scene->addChild(ExplosionParticleNode);
        scene->addChild(SmokeParticleNode);
        scene->addChild(VortexBeacon);

        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1,
                                                    &sceneManager,
                                                    AgeFunc.get()));

        sceneManager.setRoot(scene);

        // Show the whole Scene
        sceneManager.showAll();

        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "06Explosion");

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

Distribution3DRecPtr createPositionDistribution(void)
{
    //Sphere Distribution
    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(0.0);
    TheSphereDistribution->setOuterRadius(0.2);
    TheSphereDistribution->setMinTheta(0.0);
    TheSphereDistribution->setMaxTheta(6.283185);
    TheSphereDistribution->setMinZ(-1.0);
    TheSphereDistribution->setMaxZ(1.0);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::SURFACE);

    return TheSphereDistribution;
}

Distribution3DRecPtr createVelocityDistribution(void)
{
    //Sphere Distribution
    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(2.0);
    TheSphereDistribution->setOuterRadius(4.0);
    TheSphereDistribution->setMinTheta(0.0);
    TheSphereDistribution->setMaxTheta(3.14195);
    TheSphereDistribution->setMinZ(-1.0);
    TheSphereDistribution->setMaxZ(1.0);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::VOLUME);

    return TheSphereDistribution;
}

Distribution1DRecPtr createLifespanDistribution(void)
{
    GaussianNormalDistribution1DRefPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    TheLifespanDistribution->setMean(1.0f);
    TheLifespanDistribution->setStandardDeviation(0.2);

    return TheLifespanDistribution;
}

Distribution3DRecPtr createAccelerationDistribution(void)
{

    //Sphere Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(0.0,0.0,0.0));
    TheLineDistribution->setPoint2(Pnt3f(0.0,0.0,0.0));

    return TheLineDistribution;
}

Distribution3DRecPtr createSizeDistribution(void)
{
    //Line Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(1.2,1.2,1.0));
    TheLineDistribution->setPoint2(Pnt3f(1.4,1.4,1.0));

    return TheLineDistribution;
}

Distribution3DRecPtr createSmokePositionDistribution(void)
{
    //Sphere Distribution
    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(0.0);
    TheSphereDistribution->setOuterRadius(0.2);
    TheSphereDistribution->setMinTheta(0.0);
    TheSphereDistribution->setMaxTheta(6.283185);
    TheSphereDistribution->setMinZ(-1.0);
    TheSphereDistribution->setMaxZ(1.0);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::SURFACE);

    return TheSphereDistribution;
}

Distribution3DRecPtr createSmokeVelocityDistribution(void)
{
    //Sphere Distribution
    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(1.0);
    TheSphereDistribution->setOuterRadius(1.0);
    TheSphereDistribution->setMinTheta(1.0);
    TheSphereDistribution->setMaxTheta(2.0);
    TheSphereDistribution->setMinZ(-0.6);
    TheSphereDistribution->setMaxZ(0.6);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::VOLUME);

    return TheSphereDistribution;
}

Distribution1DRecPtr createSmokeLifespanDistribution(void)
{
    GaussianNormalDistribution1DRefPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    TheLifespanDistribution->setMean(8.0f);
    TheLifespanDistribution->setStandardDeviation(1.4);

    return TheLifespanDistribution;
}

Distribution3DRecPtr createSmokeSizeDistribution(void)
{
    //Line Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(1.0,1.0,1.0));
    TheLineDistribution->setPoint2(Pnt3f(1.0,1.0,1.0));

    return TheLineDistribution;
}

Distribution3DRefPtr createSmokeColorDistribution(void)
{
    //Line Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(0.0,0.0,0.0));
    TheLineDistribution->setPoint2(Pnt3f(0.15,0.15,0.15));

    return TheLineDistribution;
}

