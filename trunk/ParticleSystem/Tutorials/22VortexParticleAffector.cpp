// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/Input/OSGWindowUtils.h>

// Input
#include <OpenSG/Input/OSGKeyListener.h>

#include <OpenSG/OSGBlendChunk.h>
#include <OpenSG/OSGPointChunk.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/ParticleSystem/OSGParticleSystem.h>
#include <OpenSG/ParticleSystem/OSGParticleSystemCore.h>
#include <OpenSG/ParticleSystem/OSGLineParticleSystemDrawer.h>
#include <OpenSG/ParticleSystem/OSGPointParticleSystemDrawer.h>
#include <OpenSG/ParticleSystem/OSGRateParticleGenerator.h>
#include <OpenSG/Dynamics/OSGConeDistribution3D.h>
#include <OpenSG/Dynamics/OSGSphereDistribution3D.h>
#include <OpenSG/ParticleSystem/OSGVortexParticleAffector.h>
#include <OpenSG/ParticleSystem/OSGConserveVelocityParticleAffector.h>

#include <OpenSG/Dynamics/OSGDataConverter.h>
#include <OpenSG/Dynamics/OSGCompoundFunction.h>

#include <OpenSG/Dynamics/OSGGaussianNormalDistribution1D.h>


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

//Particle System
ParticleSystemCorePtr ParticleNodeCore;

//Particle System Drawers
PointParticleSystemDrawerPtr ExamplePointParticleSystemDrawer;
LineParticleSystemDrawerPtr ExampleLineParticleSystemDrawer;

// Vortex Affector
VortexParticleAffectorPtr ExampleVortexAffector;


// Create a class to allow for the use of the Ctrl+q and changing of drawers
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventPtr e)
   {
	    if(e->getKey()== KeyEvent::KEY_1) // Use the Point Drawer
	   {
			beginEditCP(ParticleNodeCore, ParticleSystemCore::DrawerFieldMask);
				ParticleNodeCore->setDrawer(ExamplePointParticleSystemDrawer);
			endEditCP(ParticleNodeCore,ParticleSystemCore::DrawerFieldMask );
	   }

	   if(e->getKey()== KeyEvent::KEY_2)//Use the Line Drawer for 2
	   {
			 beginEditCP(ParticleNodeCore, ParticleSystemCore::DrawerFieldMask);
				ParticleNodeCore->setDrawer(ExampleLineParticleSystemDrawer);
			endEditCP(ParticleNodeCore,ParticleSystemCore::DrawerFieldMask );
	   }
	   if(e->getKey()== KeyEvent::KEY_3)
	   {
		   beginEditCP(ExampleVortexAffector);
				ExampleVortexAffector->setMagnitude(osg::osgClamp<Real32>(1.0f,ExampleVortexAffector->getMagnitude() * 0.8,TypeTraits<Real32>::getMax()));
			endEditCP(ExampleVortexAffector);
	   }
	   if(e->getKey()== KeyEvent::KEY_4)
		  {
			beginEditCP(ExampleVortexAffector);
				ExampleVortexAffector->setMagnitude(osg::osgClamp<Real32>(1.0f,ExampleVortexAffector->getMagnitude() * 1.2,TypeTraits<Real32>::getMax()));
			endEditCP(ExampleVortexAffector);
		  }
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
	
	//Particle System Material
	PointChunkPtr PSPointChunk = PointChunk::create();
	beginEditCP(PSPointChunk);
		PSPointChunk->setSize(5.0f);
		PSPointChunk->setSmooth(true);
	endEditCP(PSPointChunk);
	
	BlendChunkPtr PSBlendChunk = BlendChunk::create();
	beginEditCP(PSBlendChunk);
		PSBlendChunk->setSrcFactor(GL_SRC_ALPHA);
		PSBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
	endEditCP(PSBlendChunk);

	MaterialChunkPtr PSMaterialChunkChunk = MaterialChunk::create();
	beginEditCP(PSMaterialChunkChunk);
		PSMaterialChunkChunk->setAmbient(Color4f(1.0f,1.0f,1.0f,1.0f));
		PSMaterialChunkChunk->setDiffuse(Color4f(0.7f,0.7f,0.7f,1.0f));
		PSMaterialChunkChunk->setSpecular(Color4f(0.9f,0.9f,0.9f,1.0f));
		PSMaterialChunkChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);
	endEditCP(PSMaterialChunkChunk);

	ChunkMaterialPtr PSMaterial = ChunkMaterial::create();
	beginEditCP(PSMaterial, ChunkMaterial::ChunksFieldMask);
		PSMaterial->addChunk(PSPointChunk);
		PSMaterial->addChunk(PSMaterialChunkChunk);
		PSMaterial->addChunk(PSBlendChunk);
	endEditCP(PSMaterial, ChunkMaterial::ChunksFieldMask);

	//Particle System
    ParticleSystemPtr ExampleParticleSystem = osg::ParticleSystem::create();
		ExampleParticleSystem->addParticle(Pnt3f(0,-100,0),
			Vec3f(0.0,0.0f,1.0f),
			Color4f(1.0,1.0,1.0,1.0), 
			Vec3f(1.0,1.0,1.0), 
			0.1, 
			Vec3f(0.0f,0.0f,0.0f), //Velocity
			Vec3f(0.0f,0.0f,0.0f)
										   );
		ExampleParticleSystem->addParticle(Pnt3f(0,100,0),
			Vec3f(0.0,0.0f,1.0f),
			Color4f(1.0,1.0,1.0,1.0), 
			Vec3f(1.0,1.0,1.0), 
			0.1, 
			Vec3f(0.0f,0.0f,0.0f), //Velocity
			Vec3f(0.0f,0.0f,0.0f)
										   );
    ExampleParticleSystem->attachUpdateListener(TutorialWindowEventProducer);

	//Particle System Drawer (Point)
	ExamplePointParticleSystemDrawer = osg::PointParticleSystemDrawer::create();

	//Particle System Drawer (line)
	ExampleLineParticleSystemDrawer = osg::LineParticleSystemDrawer::create();
	beginEditCP(ExampleLineParticleSystemDrawer);
		ExampleLineParticleSystemDrawer->setLineDirectionSource(LineParticleSystemDrawer::DIRECTION_VELOCITY);
		ExampleLineParticleSystemDrawer->setLineLengthSource(LineParticleSystemDrawer::LENGTH_SIZE_X);
		ExampleLineParticleSystemDrawer->setLineLength(2.0f);
		ExampleLineParticleSystemDrawer->setEndPointFading(Vec2f(0.0f,1.0f));
	endEditCP(ExampleLineParticleSystemDrawer);

	//Create a Rate Particle Generator
	RateParticleGeneratorPtr ExampleGenerator = osg::RateParticleGenerator::create();

	//Attach the function objects to the Generator
	beginEditCP(ExampleGenerator, RateParticleGenerator::PositionFunctionFieldMask | RateParticleGenerator::LifespanFunctionFieldMask | RateParticleGenerator::GenerationRateFieldMask);
		ExampleGenerator->setPositionFunction(createPositionDistribution());
		ExampleGenerator->setLifespanFunction(createLifespanDistribution());
		ExampleGenerator->setGenerationRate(60.0);
		ExampleGenerator->setVelocityFunction(createVelocityDistribution());
	endEditCP(ExampleGenerator, RateParticleGenerator::PositionFunctionFieldMask | RateParticleGenerator::LifespanFunctionFieldMask | RateParticleGenerator::GenerationRateFieldMask);
	
	ExampleVortexAffector = osg::VortexParticleAffector::create();
	beginEditCP(ExampleVortexAffector);
		ExampleVortexAffector->setMagnitude(20.0); 
		ExampleVortexAffector->setVortexAxis(Vec3f(0.0,0.0,1.0)); // field rotates around z axis
		ExampleVortexAffector->setBeacon(osg::Node::create()); // set to 'emulate' from (0,0,0)
		ExampleVortexAffector->setMaxDistance(-1.0); // particles affected regardless of distance
		ExampleVortexAffector->setAttenuation(0.25); // strength of uniform field dimishes by dist^attenuation
	endEditCP(ExampleVortexAffector);


	//Attach the Generator and Affector to the Particle System
	beginEditCP(ExampleParticleSystem);
		ExampleParticleSystem->getGenerators().push_back(ExampleGenerator);
		ExampleParticleSystem->getAffectors().push_back(ExampleVortexAffector);
		ExampleParticleSystem->setMaxParticles(800);
	endEditCP(ExampleParticleSystem);


	//Particle System Node
    ParticleNodeCore = osg::ParticleSystemCore::create();
    beginEditCP(ParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
		ParticleNodeCore->setSystem(ExampleParticleSystem);
		ParticleNodeCore->setDrawer(ExamplePointParticleSystemDrawer);
		ParticleNodeCore->setMaterial(PSMaterial);
    endEditCP(ParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
    
	NodePtr ParticleNode = osg::Node::create();
    beginEditCP(ParticleNode, Node::CoreFieldMask);
        ParticleNode->setCore(ParticleNodeCore);
    endEditCP(ParticleNode, Node::CoreFieldMask);


    // Make Main Scene Node and add the Torus
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
        scene->addChild(ParticleNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    mgr->setRoot(scene);

    // Show the whole Scene
    mgr->showAll();
	
	mgr->getCamera()->setFar(1000.0);

	std::cout << "Vortex Particle Affector Tutorial Controls:\n"
		<< "1: Use point drawer\n"
		<< "2: Use line drawer\n"
		<< "3: Decrease vortex magnitude\n"
		<< "4: Increase vortex magnitude\n"
		<< "Ctrl + Q: Exit Tutorial";

    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "22VortexParticleAffector");

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
	 SphereDistribution3DPtr TheSphereDistribution = SphereDistribution3D::create();
    beginEditCP(TheSphereDistribution);
      	TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
		TheSphereDistribution->setInnerRadius(0.0);
		TheSphereDistribution->setOuterRadius(1.0);
		TheSphereDistribution->setMinTheta(0.0);
		TheSphereDistribution->setMaxTheta(6.283185);
		TheSphereDistribution->setMinZ(-1.0);
		TheSphereDistribution->setMaxZ(1.0);
		TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::SURFACE);
    endEditCP(TheSphereDistribution);


    return TheSphereDistribution;
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
	 SphereDistribution3DPtr TheSphereDistribution = SphereDistribution3D::create();
    beginEditCP(TheSphereDistribution);
      	TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
		TheSphereDistribution->setInnerRadius(10.0);
		TheSphereDistribution->setOuterRadius(20.0);
		TheSphereDistribution->setMinTheta(0.0);
		TheSphereDistribution->setMaxTheta(6.283185);
		TheSphereDistribution->setMinZ(-1.0);
		TheSphereDistribution->setMaxZ(1.0);
		TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::SURFACE);
    endEditCP(TheSphereDistribution);

	DataConverterPtr TheVec3fConverter = DataConverter::create();
	beginEditCP(TheVec3fConverter);
		TheVec3fConverter->setToType(&FieldDataTraits<Vec3f>::getType());
	endEditCP(TheVec3fConverter);

	CompoundFunctionPtr TheVelocityDistribution = CompoundFunction::create();
	beginEditCP(TheVelocityDistribution);
		TheVelocityDistribution->getFunctions().push_back(TheSphereDistribution);
		TheVelocityDistribution->getFunctions().push_back(TheVec3fConverter);
	endEditCP(TheVelocityDistribution);

    return TheVelocityDistribution;
}
