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

// Input
#include "OSGKeyListener.h"

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

#include "OSGGaussianNormalDistribution1D.h"
#include "OSGCylinderDistribution3D.h"
#include "OSGLineDistribution3D.h"
#include "OSGSphereDistribution3D.h"


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
        ImageRefPtr LoadedImage = ImageFileHandler::the()->read("Data/SpriteExplode.png");    
        QuadTextureChunk->setImage(LoadedImage);

        TextureEnvChunkRefPtr QuadTextureEnvChunk = TextureEnvChunk::create();
        QuadTextureEnvChunk->setEnvMode(GL_MODULATE);

        BlendChunkRefPtr PSBlendChunk = BlendChunk::create();
        PSBlendChunk->setSrcFactor(GL_SRC_ALPHA);
        PSBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

        MaterialChunkRefPtr PSMaterialChunk = MaterialChunk::create();
        PSMaterialChunk->setAmbient(Color4f(0.3f,0.0f,0.0f,1.0f));
        PSMaterialChunk->setDiffuse(Color4f(0.7f,0.0f,0.0f,1.0f));
        PSMaterialChunk->setSpecular(Color4f(0.9f,0.0f,0.0f,1.0f));
        PSMaterialChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);

        ChunkMaterialRefPtr PSMaterial = ChunkMaterial::create();
        PSMaterial->addChunk(QuadTextureChunk);
        PSMaterial->addChunk(QuadTextureEnvChunk);
        PSMaterial->addChunk(PSMaterialChunk);
        PSMaterial->addChunk(PSBlendChunk);

        //Particle System
        ParticleSystemRecPtr ExampleParticleSystem = ParticleSystem::create();
        ExampleParticleSystem->attachUpdateProducer(TutorialWindow);

        //Age Particle Function.  Controls which image is shown when, based on the age of a particle.
        AgeParticleFunctionRecPtr AgeFunc = AgeParticleFunction::create();
        AgeFunc->setSequenceTime(0.1f); // image changes every 0.1 seconds.
        AgeFunc->setSequenceOrder(AgeParticleFunction::CUSTOM); // using the custom sequence below.
        /*
           Here, a custom sequence for the image ordering is assembled.  The image sequence will be shown in 
           the order specified here.  Once the end of the sequence is reached, the sequence repeats.
           */
        AgeFunc->editMFCustomSequence()->push_back(0);
        AgeFunc->editMFCustomSequence()->push_back(1);
        AgeFunc->editMFCustomSequence()->push_back(2);
        AgeFunc->editMFCustomSequence()->push_back(3);
        AgeFunc->editMFCustomSequence()->push_back(4);
        AgeFunc->editMFCustomSequence()->push_back(5);
        AgeFunc->editMFCustomSequence()->push_back(4);
        AgeFunc->editMFCustomSequence()->push_back(3);
        AgeFunc->editMFCustomSequence()->push_back(2);
        AgeFunc->editMFCustomSequence()->push_back(1);

        //Particle System Drawer - 
        QuadSequenceParticleSystemDrawerRecPtr ExampleParticleSystemDrawer = QuadSequenceParticleSystemDrawer::create();
        // image dimensions (in pixels) are required if there is a border on the images.
        ExampleParticleSystemDrawer->setImageDimensions(Vec2us(780,520));
        // The "dimensions" of the sequence contained in the image.  For this image,
        // there are 3 images in the "x" direction, and two in the "y" direction, for a 
        // total of 6.
        ExampleParticleSystemDrawer->setSequenceDimensions(Vec2b(3,2));
        // width of the border on each side of the image, in pixels.
        ExampleParticleSystemDrawer->setBorderOffsets(Vec2b(0,0));
        // this is the age function we just created above.
        ExampleParticleSystemDrawer->setSequenceFunction(AgeFunc);

        RateParticleGeneratorRecPtr ExampleParticleGenerator = RateParticleGenerator::create();
        //Attach the function objects to the Generator
        ExampleParticleGenerator->setPositionDistribution(createPositionDistribution());
        ExampleParticleGenerator->setLifespanDistribution(createLifespanDistribution());
        ExampleParticleGenerator->setVelocityDistribution(createVelocityDistribution());
        ExampleParticleGenerator->setAccelerationDistribution(createAccelerationDistribution());
        ExampleParticleGenerator->setSizeDistribution(createSizeDistribution());
        ExampleParticleGenerator->setGenerationRate(40.0f);

        //Particle System Node
        ParticleSystemCoreRefPtr ParticleNodeCore = ParticleSystemCore::create();
        ParticleNodeCore->setSystem(ExampleParticleSystem);
        ParticleNodeCore->setDrawer(ExampleParticleSystemDrawer);
        ParticleNodeCore->setMaterial(PSMaterial);
        ParticleNodeCore->setSortingMode(ParticleSystemCore::BACK_TO_FRONT);

        NodeRefPtr ParticleNode = Node::create();
        ParticleNode->setCore(ParticleNodeCore);

        ExampleParticleSystem->addParticle(Pnt3f(10.0,0.0,0.0),
                                           Vec3f(0.0,1.0,0.0),
                                           Color4f(1.0,1.0,1.0,1.0),
                                           Vec3f(1.0,1.0,1.0),
                                           0.01,
                                           Vec3f(0.0,0.0,0.0),
                                           Vec3f(0.0,0.0,0.0));

        ExampleParticleSystem->addParticle(Pnt3f(-10.0,0.0,0.0),
                                           Vec3f(0.0,1.0,0.0),
                                           Color4f(1.0,1.0,1.0,1.0),
                                           Vec3f(1.0,1.0,1.0),
                                           0.01,
                                           Vec3f(0.0,0.0,0.0),
                                           Vec3f(0.0,0.0,0.0));

        ExampleParticleSystem->pushToGenerators(ExampleParticleGenerator);
        // Make Main Scene Node and add the Torus
        NodeRefPtr scene = makeCoredNode<Group>();
        scene->addChild(ParticleNode);

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
                                   "05a - QuadSequenceParticleDrawer");

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
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(2.0);
    TheSphereDistribution->setOuterRadius(5.0);
    TheSphereDistribution->setMinTheta(-1.5);
    TheSphereDistribution->setMaxTheta(1.5);
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
    TheLineDistribution->setPoint1(Pnt3f(0.0,0.0,0.0));
    TheLineDistribution->setPoint2(Pnt3f(0.0,0.0,0.0));

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
