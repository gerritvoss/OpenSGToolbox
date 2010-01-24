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

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);
void ClickToGenerate(const MouseEventUnrecPtr e);

Distribution3DRefPtr createPositionDistribution(void);
Distribution1DRefPtr createLifespanDistribution(void);
Distribution3DRefPtr createVelocityDistribution(void);
Distribution3DRefPtr createVelocityDistribution2(void);
Distribution3DRefPtr createAccelerationDistribution(void);
Distribution3DRefPtr createSizeDistribution(void);



ParticleSystemRefPtr Example1ParticleSystem;
ParticleSystemRefPtr Example2ParticleSystem;
QuadParticleSystemDrawerRefPtr Example1ParticleSystemDrawer;
QuadParticleSystemDrawerRefPtr Example2ParticleSystemDrawer;
BurstParticleGeneratorRefPtr ExampleBurstGenerator;
BurstParticleGeneratorRefPtr Example2BurstGenerator;




// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
  public:

    virtual void keyPressed(const KeyEventUnrecPtr e)
    {
        if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
        {
            TutorialWindow->closeWindow();
        }

        if(e->getKey() == KeyEvent::KEY_B)//generate particles when clicked
        {
            //Attach the Generator to the Particle System
            Example1ParticleSystem->pushToGenerators(ExampleBurstGenerator);

            Example2ParticleSystem->pushToGenerators(Example2BurstGenerator);


        }
    }

    virtual void keyReleased(const KeyEventUnrecPtr e)
    {
    }

    virtual void keyTyped(const KeyEventUnrecPtr e)
    {
        UInt32 CHANGE_SOURCE;
        if(e->getKey()== KeyEvent::KEY_P)
        {

            CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_POSITION_CHANGE;
        }

        else if(e->getKey()== KeyEvent::KEY_C)
        {
            CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_VELOCITY_CHANGE;
        }

        else if(e->getKey()== KeyEvent::KEY_V)
        {
            CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_VELOCITY;
        }

        else if(e->getKey()== KeyEvent::KEY_A)
        {
            CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_ACCELERATION;
        }

        else  if(e->getKey()== KeyEvent::KEY_N)
        {
            CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_PARTICLE_NORMAL;
        }

        else if(e->getKey()== KeyEvent::KEY_D)
        {
            CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_VIEW_POSITION;
        }

        else if(e->getKey()== KeyEvent::KEY_S)
        {
            CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_STATIC;
        }

        else  if(e->getKey()== KeyEvent::KEY_W)
        {
            CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_VIEW_DIRECTION;
        }
        else {
            return;
        }
        Example1ParticleSystemDrawer->setNormalSource(CHANGE_SOURCE);

    }
};

void ClickToGenerate(const MouseEventUnrecPtr e)
{


}

class TutorialMouseListener : public MouseListener
{
  public:
    virtual void mouseClicked(const MouseEventUnrecPtr e)
    {
        if(e->getButton()== MouseEvent::BUTTON1)
        {


        }

        if(e->getButton()== MouseEvent::BUTTON3)
        {

        }

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


    BlendChunkRefPtr PSBlendChunk = BlendChunk::create();
    PSBlendChunk->setSrcFactor(GL_SRC_ALPHA);
    PSBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

    //Particle System Material
    TextureObjChunkRefPtr QuadTextureObjChunk = TextureObjChunk::create();
    ImageRefPtr LoadedImage = ImageFileHandler::the()->read("./Data/Cloud.png");    
    QuadTextureObjChunk->setImage(LoadedImage);

    MaterialChunkRefPtr PSMaterialChunk = MaterialChunk::create();
    PSMaterialChunk->setAmbient(Color4f(0.3f,0.3f,0.3f,1.0f));
    PSMaterialChunk->setDiffuse(Color4f(0.7f,0.7f,0.7f,1.0f));
    PSMaterialChunk->setSpecular(Color4f(0.9f,0.9f,0.9f,1.0f));
    PSMaterialChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);

    ChunkMaterialRefPtr PSMaterial = ChunkMaterial::create();
    PSMaterial->addChunk(QuadTextureObjChunk);
    PSMaterial->addChunk(PSMaterialChunk);
    PSMaterial->addChunk(PSBlendChunk);

    //Particle System Material 2
    TextureObjChunkRefPtr QuadTextureObjChunk2 = TextureObjChunk::create();
    ImageRefPtr LoadedImage2 = ImageFileHandler::the()->read("./Data/Cloud.png");    
    QuadTextureObjChunk2->setImage(LoadedImage2);

    MaterialChunkRefPtr PSMaterialChunk2 = MaterialChunk::create();
    PSMaterialChunk2->setAmbient(Color4f(0.3f,0.3f,0.3f,1.0f));
    PSMaterialChunk2->setDiffuse(Color4f(0.7f,0.7f,0.7f,1.0f));
    PSMaterialChunk2->setSpecular(Color4f(0.9f,0.9f,0.9f,1.0f));
    PSMaterialChunk2->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);

    ChunkMaterialRefPtr PSMaterial2 = ChunkMaterial::create();
    PSMaterial2->addChunk(QuadTextureObjChunk2);
    PSMaterial2->addChunk(PSMaterialChunk2);
    PSMaterial2->addChunk(PSBlendChunk);


    //Particle System

    Example1ParticleSystem = OSG::ParticleSystem::create();
    Example1ParticleSystem->attachUpdateListener(TutorialWindow);

    Example2ParticleSystem = OSG::ParticleSystem::create();
    Example2ParticleSystem->attachUpdateListener(TutorialWindow);

    //Particle System Drawer
    Example1ParticleSystemDrawer = OSG::QuadParticleSystemDrawer::create();
    Example2ParticleSystemDrawer = OSG::QuadParticleSystemDrawer::create();




    //Attach the function objects to the Generator
    //Generator 1 
    ExampleBurstGenerator = OSG::BurstParticleGenerator::create();
    ExampleBurstGenerator->setPositionDistribution(createPositionDistribution());
    ExampleBurstGenerator->setLifespanDistribution(createLifespanDistribution());
    ExampleBurstGenerator->setBurstAmount(50.0);
    ExampleBurstGenerator->setVelocityDistribution(createVelocityDistribution());
    ExampleBurstGenerator->setAccelerationDistribution(createAccelerationDistribution());
    ExampleBurstGenerator->setSizeDistribution(createSizeDistribution());

    //Generator 2
    Example2BurstGenerator = OSG::BurstParticleGenerator::create();
    Example2BurstGenerator->setPositionDistribution(createPositionDistribution());
    Example2BurstGenerator->setLifespanDistribution(createLifespanDistribution());
    Example2BurstGenerator->setBurstAmount(50.0);
    Example2BurstGenerator->setVelocityDistribution(createVelocityDistribution2());
    Example2BurstGenerator->setAccelerationDistribution(createAccelerationDistribution());
    Example2BurstGenerator->setSizeDistribution(createSizeDistribution());



    //Particle System Node
    ParticleSystemCoreRefPtr ParticleNodeCore = OSG::ParticleSystemCore::create();
    ParticleNodeCore->setSystem(Example1ParticleSystem);
    ParticleNodeCore->setDrawer(Example1ParticleSystemDrawer);
    ParticleNodeCore->setMaterial(PSMaterial);

    NodeRefPtr ParticleNode = OSG::Node::create();
    ParticleNode->setCore(ParticleNodeCore);

    //Particle System Node2
    ParticleSystemCoreRefPtr ParticleNodeCore2 = OSG::ParticleSystemCore::create();
    ParticleNodeCore2->setSystem(Example2ParticleSystem);
    ParticleNodeCore2->setDrawer(Example2ParticleSystemDrawer);
    ParticleNodeCore2->setMaterial(PSMaterial2);

    NodeRefPtr ParticleNode2 = OSG::Node::create();
    ParticleNode2->setCore(ParticleNodeCore2);

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
    NodeRefPtr scene = OSG::Node::create();
    scene->setCore(OSG::Group::create());
    scene->addChild(ParticleNode);
    scene->addChild(ParticleNode2);
    scene->addChild(GroundTransformNode);

    mgr->setRoot(scene);

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
                               WinSize,
                               "06Explosion");

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
    TheSphereDistribution->setInnerRadius(3.0);
    TheSphereDistribution->setOuterRadius(10.0);
    TheSphereDistribution->setMinTheta(-3.141950);
    TheSphereDistribution->setMaxTheta(3.141950);
    TheSphereDistribution->setMinZ(0.0);
    TheSphereDistribution->setMaxZ(1.0);
    TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::VOLUME);

    return TheSphereDistribution;
}

Distribution3DRefPtr createVelocityDistribution2(void)
{


    //Sphere Distribution
    SphereDistribution3DRefPtr TheSphereDistribution = SphereDistribution3D::create();
    TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
    TheSphereDistribution->setInnerRadius(6.0);
    TheSphereDistribution->setOuterRadius(10.0);
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
    TheLifespanDistribution->setMean(30.0f);
    TheLifespanDistribution->setStandardDeviation(5.0);

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
    //Sphere Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(5.0,5.0,1.0));
    TheLineDistribution->setPoint2(Pnt3f(10.0,10.0,1.0));

    return TheLineDistribution;
}
