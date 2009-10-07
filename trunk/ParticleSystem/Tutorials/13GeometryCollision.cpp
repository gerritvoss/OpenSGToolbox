// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/Input/OSGWindowUtils.h>

// Input
#include <OpenSG/Input/OSGKeyListener.h>
#include <OpenSG/Toolbox/OSGMathUtils.h>

#include <OpenSG/ParticleSystem/OSGParticleSystem.h>
#include <OpenSG/ParticleSystem/OSGParticleSystemCore.h>
#include <OpenSG/ParticleSystem/OSGPointParticleSystemDrawer.h>
#include <OpenSG/ParticleSystem/OSGGeometryCollisionParticleSystemAffector.h>
#include <OpenSG/ParticleSystem/OSGRateParticleGenerator.h>
#include <OpenSG/ParticleSystem/OSGParticleCollisionListener.h>

#include <OpenSG/Dynamics/OSGDataConverter.h>
#include <OpenSG/Dynamics/OSGCompoundFunction.h>
#include <OpenSG/Dynamics/OSGLineDistribution3D.h>
#include <OpenSG/Dynamics/OSGGaussianNormalDistribution1D.h>
#include <OpenSG/Dynamics/OSGDiscDistribution3D.h>

#include <OpenSG/OSGBlendChunk.h>
#include <OpenSG/OSGPointChunk.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialChunk.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

FunctionPtr createPositionDistribution(void);
FunctionPtr createLifespanDistribution(void);
FunctionPtr createVelocityDistribution(void);

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
            TutorialWindowEventProducer->closeWindow();
       }
   }

   virtual void keyReleased(const KeyEventPtr e)
   {
   }

   virtual void keyTyped(const KeyEventPtr e)
   {
   }
};

class TutorialMouseListener : public MouseListener
{
  public:
    virtual void mouseClicked(const MouseEventPtr e)
    {
    }
    virtual void mouseEntered(const MouseEventPtr e)
    {
    }
    virtual void mouseExited(const MouseEventPtr e)
    {
    }
    virtual void mousePressed(const MouseEventPtr e)
    {
            mgr->mouseButtonPress(e->getButton(), e->getLocation().x(), e->getLocation().y());
    }
    virtual void mouseReleased(const MouseEventPtr e)
    {
           mgr->mouseButtonRelease(e->getButton(), e->getLocation().x(), e->getLocation().y());
    }
};

class TutorialMouseMotionListener : public MouseMotionListener
{
  public:
    virtual void mouseMoved(const MouseEventPtr e)
    {
            mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
    }

    virtual void mouseDragged(const MouseEventPtr e)
    {
            mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
    }
};


class TutorialParticleCollisionListener : public ParticleCollisionListener
{
   virtual void particleCollision(const ParticleEventPtr ParE, const ParticleCollisionEventPtr ColE)
   {
	   Vec3f Reflect(reflect(ParE->getParticleVelocity(), ColE->getHitNormal()));
       ParticleSystemPtr::dcast(ParE->getSource())->setVelocity(Reflect, ParE->getParticleIndex());
	   ParticleSystemPtr::dcast(ParE->getSource())->setPosition(ColE->getHitPoint() + (0.00001f*Reflect), ParE->getParticleIndex());
   }
};

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    TutorialKeyListener TheKeyListener;
    TutorialWindowEventProducer->addKeyListener(&TheKeyListener);
    TutorialMouseListener TheTutorialMouseListener;
    TutorialMouseMotionListener TheTutorialMouseMotionListener;
    TutorialWindowEventProducer->addMouseListener(&TheTutorialMouseListener);
    TutorialWindowEventProducer->addMouseMotionListener(&TheTutorialMouseMotionListener);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
	

	//Particle System
    ParticleSystemPtr ExampleParticleSystem = osg::ParticleSystem::create();
    ExampleParticleSystem->attachUpdateListener(TutorialWindowEventProducer);

	PointParticleSystemDrawerPtr ExamplePointParticleSystemDrawer = osg::PointParticleSystemDrawer::create();
	//NodePtr ParticlePrototypeNode = makeTorus(1.0,4.0,16,16);
	//NodePtr CollisionNode = makeBox(5.0,5.0,5.0,1,1,1);//makeSphere(4,10.0f);
	NodePtr CollisionNode = makeSphere(2,4.0f);
	
	//Particle System Material
	PointChunkPtr PSPointChunk = PointChunk::create();
	beginEditCP(PSPointChunk);
		PSPointChunk->setSize(5.0f);
		PSPointChunk->setSmooth(true);
	endEditCP(PSPointChunk);
	BlendChunkPtr PSBlendChunk = BlendChunk::create();
	PSBlendChunk->setSrcFactor(GL_SRC_ALPHA);
	PSBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

	MaterialChunkPtr PSMaterialChunkChunk = MaterialChunk::create();
	beginEditCP(PSMaterialChunkChunk);
		PSMaterialChunkChunk->setAmbient(Color4f(1.0f,0.0f,0.0f,1.0f));
		PSMaterialChunkChunk->setDiffuse(Color4f(1.0f,0.0f,0.0f,1.0f));
		PSMaterialChunkChunk->setSpecular(Color4f(1.0f,0.0f,0.0f,1.0f));
		PSMaterialChunkChunk->setColorMaterial(GL_NONE);
		//PSMaterialChunkChunk->setLit(false);
	endEditCP(PSMaterialChunkChunk);

	ChunkMaterialPtr PSMaterial = ChunkMaterial::create();
	beginEditCP(PSMaterial, ChunkMaterial::ChunksFieldMask);
		PSMaterial->addChunk(PSPointChunk);
		PSMaterial->addChunk(PSMaterialChunkChunk);
		PSMaterial->addChunk(PSBlendChunk);
	endEditCP(PSMaterial, ChunkMaterial::ChunksFieldMask);

    ParticleSystemCorePtr ParticleNodeCore = osg::ParticleSystemCore::create();
    beginEditCP(ParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
		ParticleNodeCore->setSystem(ExampleParticleSystem);
		ParticleNodeCore->setDrawer(ExamplePointParticleSystemDrawer);
		ParticleNodeCore->setMaterial(PSMaterial);
    endEditCP(ParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
    
	NodePtr ParticleNode = osg::Node::create();
    beginEditCP(ParticleNode, Node::CoreFieldMask);
        ParticleNode->setCore(ParticleNodeCore);
    endEditCP(ParticleNode, Node::CoreFieldMask);

	//Generator
	//Attach the function objects to the Generator
	RateParticleGeneratorPtr ExampleGenerator= RateParticleGenerator::create();
	beginEditCP(ExampleGenerator, RateParticleGenerator::PositionFunctionFieldMask | RateParticleGenerator::LifespanFunctionFieldMask | RateParticleGenerator::GenerationRateFieldMask);
		ExampleGenerator->setPositionFunction(createPositionDistribution());
		ExampleGenerator->setLifespanFunction(createLifespanDistribution());
		ExampleGenerator->setGenerationRate(20.0);
		ExampleGenerator->setVelocityFunction(createVelocityDistribution());
	endEditCP(ExampleGenerator, RateParticleGenerator::PositionFunctionFieldMask | RateParticleGenerator::LifespanFunctionFieldMask | RateParticleGenerator::GenerationRateFieldMask);
	
	//Geometry Collision Affector
	GeometryCollisionParticleSystemAffectorPtr ExampleGeometryCollisionParticleSystemAffector = GeometryCollisionParticleSystemAffector::create();
	beginEditCP(ExampleGeometryCollisionParticleSystemAffector, GeometryCollisionParticleSystemAffector::CollisionNodeFieldMask);
		ExampleGeometryCollisionParticleSystemAffector->setCollisionNode(CollisionNode);
	endEditCP(ExampleGeometryCollisionParticleSystemAffector, GeometryCollisionParticleSystemAffector::CollisionNodeFieldMask);

	TutorialParticleCollisionListener TheCollisionListener;
	ExampleGeometryCollisionParticleSystemAffector->addParticleCollisionListener(&TheCollisionListener);

	beginEditCP(ExampleParticleSystem, ParticleSystem::SystemAffectorsFieldMask | ParticleSystem::GeneratorsFieldMask);
		ExampleParticleSystem->getSystemAffectors().push_back(ExampleGeometryCollisionParticleSystemAffector);
		ExampleParticleSystem->getGenerators().push_back(ExampleGenerator);
	endEditCP(ExampleParticleSystem, ParticleSystem::SystemAffectorsFieldMask | ParticleSystem::GeneratorsFieldMask);


    // Make Main Scene Node and add the Torus
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
        scene->addChild(ParticleNode);
        scene->addChild(CollisionNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    mgr->setRoot(scene);

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "13CollisionGeometry");

    //Enter main Loop
    TutorialWindowEventProducer->mainLoop();
    
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

FunctionPtr createPositionDistribution(void)
{
     //Disc Distribution
    DiscDistribution3DPtr TheDiscDistribution = DiscDistribution3D::create();
    beginEditCP(TheDiscDistribution);
      TheDiscDistribution->setCenter(Pnt3f(0.0,0.0,10.0));
      TheDiscDistribution->setInnerRadius(0.0);
      TheDiscDistribution->setOuterRadius(3.0);
      TheDiscDistribution->setMinTheta(0.0);
      TheDiscDistribution->setMaxTheta(6.283185307);
      TheDiscDistribution->setNormal(Vec3f(0.0,0.0,1.0));
      TheDiscDistribution->setSurfaceOrEdge(DiscDistribution3D::SURFACE);
    endEditCP(TheDiscDistribution);


    return TheDiscDistribution;
}

FunctionPtr createLifespanDistribution(void)
{
    GaussianNormalDistribution1DPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    beginEditCP(TheLifespanDistribution);
      TheLifespanDistribution->setMean(15.0f);
      TheLifespanDistribution->setStandardDeviation(3.0);
    endEditCP(TheLifespanDistribution);
	
	return TheLifespanDistribution;
}

FunctionPtr createVelocityDistribution(void)
{
	 //Sphere Distribution
    LineDistribution3DPtr TheLineDistribution = LineDistribution3D::create();
    beginEditCP(TheLineDistribution);
 		TheLineDistribution->setPoint1(Pnt3f(0.0,0.0,-4.5));
		TheLineDistribution->setPoint2(Pnt3f(0.0,0.0,-5.0));
    endEditCP(TheLineDistribution);

	DataConverterPtr TheVec3fConverter = DataConverter::create();
	beginEditCP(TheVec3fConverter);
		TheVec3fConverter->setToType(&FieldDataTraits<Vec3f>::getType());
	endEditCP(TheVec3fConverter);

	CompoundFunctionPtr TheVelocityDistribution = CompoundFunction::create();
	beginEditCP(TheVelocityDistribution);
		TheVelocityDistribution->getFunctions().push_back(TheLineDistribution);
		TheVelocityDistribution->getFunctions().push_back(TheVec3fConverter);
	endEditCP(TheVelocityDistribution);

    return TheVelocityDistribution;
}
