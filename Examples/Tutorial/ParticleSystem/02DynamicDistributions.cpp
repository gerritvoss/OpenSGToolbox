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
#include "OSGLineChunk.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGParticleSystem.h"
#include "OSGParticleSystemCore.h"
#include "OSGPointParticleSystemDrawer.h"
#include "OSGLineParticleSystemDrawer.h"

#include "OSGGaussianNormalDistribution1D.h"

#include "OSGLineDistribution3D.h"
#include "OSGBoxDistribution3D.h"
#include "OSGDiscDistribution3D.h"
#include "OSGCylinderDistribution3D.h"
#include "OSGSphereDistribution3D.h"
#include "OSGGaussianNormalDistribution3D.h"
#include "OSGTriDistribution3D.h"
// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

Distribution3DRefPtr createPositionDistribution(void);
Distribution3DRefPtr createNormalDistribution(void);
Distribution3DRefPtr createColorDistribution(void);
Distribution3DRefPtr createSizeDistribution(void);
Distribution1DRefPtr createLifespanDistribution(void);
Distribution3DRefPtr createVelocityDistribution(void);
Distribution3DRefPtr createAccelerationDistribution(void);

void keyTyped(KeyEventDetails* const details,
              SimpleSceneManager *mgr
             )
{
    if(details->getKey() == KeyEventDetails::KEY_Q &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
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
        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1, &sceneManager));

        //Particle System Material
        LineChunkRefPtr PSLineChunk = LineChunk::create();
        PSLineChunk->setWidth(1.0f);

        BlendChunkRefPtr PSBlendChunk = BlendChunk::create();
        PSBlendChunk->setSrcFactor(GL_SRC_ALPHA);
        PSBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

        MaterialChunkRefPtr PSMaterialChunk = MaterialChunk::create();
        PSMaterialChunk->setAmbient(Color4f(0.3f,0.3f,0.3f,1.0f));
        PSMaterialChunk->setDiffuse(Color4f(0.7f,0.7f,0.7f,1.0f));
        PSMaterialChunk->setSpecular(Color4f(0.9f,0.9f,0.9f,1.0f));
        PSMaterialChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);
        PSMaterialChunk->setLit(false);

        ChunkMaterialRefPtr PSMaterial = ChunkMaterial::create();
        PSMaterial->addChunk(PSLineChunk);
        PSMaterial->addChunk(PSMaterialChunk);
        PSMaterial->addChunk(PSBlendChunk);

        //Particle System
        ParticleSystemRefPtr ExampleParticleSystem = ParticleSystem::create();
        ExampleParticleSystem->attachUpdateProducer(TutorialWindow);


        //Create the particles
        UInt32 NumParticlesToGenerate(2500);

        Distribution3DRefPtr PositionDistribution = createPositionDistribution();
        Distribution3DRefPtr NormalDistribution = createNormalDistribution();
        Distribution3DRefPtr ColorDistribution = createColorDistribution();
        Distribution3DRefPtr SizeDistribution = createSizeDistribution();
        Distribution1DRefPtr LifespanDistribution = createLifespanDistribution();
        Distribution3DRefPtr VelocityDistribution = createVelocityDistribution();
        Distribution3DRefPtr AccelerationDistribution = createAccelerationDistribution();

        Pnt3f PositionReturnValue;
        Vec3f NormalReturnValue = Vec3f(0.0,0.0f,1.0f);
        Color4f ColorReturnValue = Color4f(1.0,1.0f,1.0f, 1.0f);
        Vec3f SizeReturnValue;
        Time LifespanReturnValue = -1;
        Vec3f VelocityReturnValue;
        Vec3f AccelerationReturnValue;


        for(UInt32 i(0) ; i< NumParticlesToGenerate ; ++i)
        {
            if(PositionDistribution != NULL)
            {
                PositionReturnValue.setValue(PositionDistribution->generate().getValues());
            }


            if(ColorDistribution != NULL)
            {
                Vec3f ColorRGB = ColorDistribution->generate();
                ColorReturnValue.setValuesRGBA(ColorRGB[0],ColorRGB[1],ColorRGB[2],1.0f);
            }


            if(SizeDistribution != NULL)
            {
                SizeReturnValue = SizeDistribution->generate();
            }

            if(LifespanDistribution != NULL)
            {
                LifespanReturnValue = LifespanDistribution->generate();
            }
            if(VelocityDistribution != NULL)
            {
                VelocityReturnValue = VelocityDistribution->generate();
            }

            ExampleParticleSystem->addParticle(PositionReturnValue,
                                               NormalReturnValue,
                                               ColorReturnValue,
                                               SizeReturnValue,
                                               LifespanReturnValue,
                                               VelocityReturnValue,
                                               AccelerationReturnValue
                                              );

        }

        //Particle System Drawer
        LineParticleSystemDrawerRefPtr ExampleParticleSystemDrawer = LineParticleSystemDrawer::create();
        ExampleParticleSystemDrawer->setLineDirectionSource(LineParticleSystemDrawer::DIRECTION_VELOCITY);
        ExampleParticleSystemDrawer->setLineLengthSource(LineParticleSystemDrawer::LENGTH_SIZE_X);
        ExampleParticleSystemDrawer->setEndPointFading(Vec2f(0.0f,1.0f));

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

        sceneManager.setRoot(scene);

        // Show the whole Scene
        sceneManager.showAll();


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "02DynamicDistribution");

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
    //Make The Distribution

    //Box Distribution
    /*BoxDistribution3DRefPtr TheBoxDistribution = BoxDistribution3D::create();
      TheBoxDistribution->setMinPoint(Pnt3f(-10.0,-10.0,-10.0));
      TheBoxDistribution->setMaxPoint(Pnt3f(10.0,10.0,10.0));
      TheBoxDistribution->setSurfaceOrVolume(BoxDistribution3D::SURFACE);

    //Disc Distribution
    DiscDistribution3DRefPtr TheDiscDistribution = DiscDistribution3D::create();
    TheDiscDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheDiscDistribution->setInnerRadius(10.0);
    TheDiscDistribution->setOuterRadius(20.0);
    TheDiscDistribution->setMinTheta(0.0);
    TheDiscDistribution->setMaxTheta(6.283185307);
    TheDiscDistribution->setNormal(Vec3f(0.0,0.0,1.0));
    TheDiscDistribution->setSurfaceOrEdge(DiscDistribution3D::SURFACE);

    //Cylinder Distribution
    CylinderDistribution3DRefPtr TheCylinderDistribution = CylinderDistribution3D::create();
    TheCylinderDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheCylinderDistribution->setInnerRadius(30.0);
    TheCylinderDistribution->setOuterRadius(100.0);
    TheCylinderDistribution->setMinTheta(0.0);
    TheCylinderDistribution->setMaxTheta(6.283185);
    TheCylinderDistribution->setHeight(400.0);
    TheCylinderDistribution->setNormal(Vec3f(0.0,0.0,1.0));
    TheCylinderDistribution->setSurfaceOrVolume(CylinderDistribution3D::VOLUME);

    //Tri Distribution
    TriDistribution3DRefPtr TheTriDistribution = TriDistribution3D::create();
    TheTriDistribution->setPoint1(Pnt3f(0.0,0.0,0.0));
    TheTriDistribution->setPoint2(Pnt3f(-50.0,1000.0,0.0));
    TheTriDistribution->setPoint3(Pnt3f(50.0,1000.0,0.0));
    TheTriDistribution->setPoint3(Pnt3f(50.0,1000.0,0.0));
    TheTriDistribution->setSurfaceOrEdge(TriDistribution3D::SURFACE);

    //GaussianNormal Distribution
    GaussianNormalDistribution3DRefPtr TheGaussianNormalDistribution = GaussianNormalDistribution3D::create();
    TheGaussianNormalDistribution->setMean(Pnt3f(0.0,0.0,0.0));
    TheGaussianNormalDistribution->setStandardDeviationX(100.0);
    TheGaussianNormalDistribution->setStandardDeviationY(100.0);
    TheGaussianNormalDistribution->setStandardDeviationZ(100.0);*/


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

Distribution3DRefPtr createNormalDistribution(void)
{
    //Sphere Distribution
    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(500.0);
    TheSphereDistribution->setOuterRadius(5000.0);
    TheSphereDistribution->setMinTheta(0.0);
    TheSphereDistribution->setMaxTheta(6.283185);
    TheSphereDistribution->setMinZ(-1.0);
    TheSphereDistribution->setMaxZ(1.0);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::VOLUME);

    return TheSphereDistribution;
}

Distribution3DRefPtr createColorDistribution(void)
{
    //Line Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(1.0,1.0,1.0));
    TheLineDistribution->setPoint2(Pnt3f(1.0,1.0,0.1));

    return TheLineDistribution;
}

Distribution3DRefPtr createSizeDistribution(void)
{
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(3.0,3.0,3.0));
    TheLineDistribution->setPoint2(Pnt3f(1.0,1.0,1.0));

    return TheLineDistribution;
}
Distribution1DRefPtr createLifespanDistribution(void)
{
    GaussianNormalDistribution1DRefPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    TheLifespanDistribution->setMean(30.0f);
    TheLifespanDistribution->setStandardDeviation(3.0);

    return TheLifespanDistribution;
}
Distribution3DRefPtr createVelocityDistribution(void)
{
    //Sphere Distribution
    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(10.0);
    TheSphereDistribution->setOuterRadius(15.0);
    TheSphereDistribution->setMinTheta(0.0);
    TheSphereDistribution->setMaxTheta(6.283185);
    TheSphereDistribution->setMinZ(-1.0);
    TheSphereDistribution->setMaxZ(1.0);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::VOLUME);

    return TheSphereDistribution;
}

Distribution3DRefPtr createAccelerationDistribution(void)
{

    return NULL;
}
