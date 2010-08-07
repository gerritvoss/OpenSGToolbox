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
#include "OSGPointParticleSystemDrawer.h"

#include "OSGSphereDistribution3D.h"
#include "OSGQuadParticleSystemDrawer.h"
#include "OSGQuadParticleSystemDrawer.h"
#include "OSGBurstParticleGenerator.h"
#include "OSGAgeSizeParticleAffector.h"

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
Distribution3DRefPtr createAccelerationDistribution(void);
Distribution3DRefPtr createSizeDistribution(void);



ParticleSystemRefPtr ExampleParticleSystem;
QuadParticleSystemDrawerRefPtr ExampleParticleSystemDrawer;
BurstParticleGeneratorRefPtr ExampleBurstGenerator;
AgeSizeParticleAffectorRefPtr ExampleAgeSizeParticleAffector;


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

        if(e->getKey() == KeyEvent::KEY_B)//generate particles when clicked
        {
            //Attach the Generator to the Particle System
            ExampleParticleSystem->pushToGenerators(ExampleBurstGenerator);
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
        ExampleParticleSystemDrawer->setNormalAndUpSource(CHANGE_SOURCE,QuadParticleSystemDrawer::UP_STATIC);

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

    //Particle System Material
    TextureObjChunkRefPtr QuadTextureObjChunk = TextureObjChunk::create();
    ImageRefPtr LoadedImage = ImageFileHandler::the()->read("Data/Cloud.png");    
    QuadTextureObjChunk->setImage(LoadedImage);

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
    PSMaterial->addChunk(QuadTextureObjChunk);
    PSMaterial->addChunk(QuadTextureEnvChunk);
    PSMaterial->addChunk(PSMaterialChunk);
    PSMaterial->addChunk(PSBlendChunk);



    //Affector
    ExampleAgeSizeParticleAffector = OSG::AgeSizeParticleAffector::create();
    //ages
    ExampleAgeSizeParticleAffector->editMFAges()->push_back(0.0);
    ExampleAgeSizeParticleAffector->editMFAges()->push_back(0.05);
    ExampleAgeSizeParticleAffector->editMFAges()->push_back(0.2);
    ExampleAgeSizeParticleAffector->editMFAges()->push_back(0.36);
    ExampleAgeSizeParticleAffector->editMFAges()->push_back(0.7);
    ExampleAgeSizeParticleAffector->editMFAges()->push_back(0.8);
    ExampleAgeSizeParticleAffector->editMFAges()->push_back(1.0);

    //sizes
    ExampleAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(1.0,0.5,1.0));
    ExampleAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(1.0,0.5,1.0));
    ExampleAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(20.0,0.5,30.0));
    ExampleAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(3.0,3.0,3.0));
    ExampleAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(6.0,60.0,6.0));
    ExampleAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(2.0,3.0,1.0));
    ExampleAgeSizeParticleAffector->editMFSizes()->push_back(Vec3f(10.0,1.0,10.0));

    //Particle System
    ExampleParticleSystem = OSG::ParticleSystem::create();
    ExampleParticleSystem->attachUpdateListener(TutorialWindow);
    ExampleParticleSystem->pushToAffectors(ExampleAgeSizeParticleAffector);

    //Particle System Drawer
    ExampleParticleSystemDrawer = OSG::QuadParticleSystemDrawer::create();


    ExampleBurstGenerator = OSG::BurstParticleGenerator::create();
    //Attach the function objects to the Generator
    ExampleBurstGenerator->setPositionDistribution(createPositionDistribution());
    ExampleBurstGenerator->setLifespanDistribution(createLifespanDistribution());
    ExampleBurstGenerator->setBurstAmount(10.0);
    ExampleBurstGenerator->setVelocityDistribution(createVelocityDistribution());
    //ExampleBurstGenerator->setAccelerationDistribution(createAccelerationDistribution());
    ExampleBurstGenerator->setSizeDistribution(createSizeDistribution());

    //Particle System Node
    ParticleSystemCoreRefPtr ParticleNodeCore = OSG::ParticleSystemCore::create();
    ParticleNodeCore->setSystem(ExampleParticleSystem);
    ParticleNodeCore->setDrawer(ExampleParticleSystemDrawer);
    ParticleNodeCore->setMaterial(PSMaterial);

    NodeRefPtr ParticleNode = OSG::Node::create();
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
    NodeRefPtr scene = OSG::Node::create();
    scene->setCore(OSG::Group::create());
    scene->addChild(ParticleNode);
    scene->addChild(GroundTransformNode);

    mgr->setRoot(scene);

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
                               WinSize,
                               "07AgeSizeParticleAffector");

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
    TheSphereDistribution->setOuterRadius(6.0);
    TheSphereDistribution->setMinTheta(-3.141950);
    TheSphereDistribution->setMaxTheta(3.141950);
    TheSphereDistribution->setMinZ(0.0);
    TheSphereDistribution->setMaxZ(0.0);
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
    //Sphere Distribution
    LineDistribution3DRefPtr TheLineDistribution = LineDistribution3D::create();
    TheLineDistribution->setPoint1(Pnt3f(5.0,5.0,1.0));
    TheLineDistribution->setPoint2(Pnt3f(10.0,10.0,1.0));

    return TheLineDistribution;
}
