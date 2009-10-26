// This tutorial can be used to test anything that needs to be tested for the particle system.  Sorting, drawers, affectors, etc.

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
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGBlendChunk.h>
#include <OpenSG/OSGPointChunk.h>
#include <OpenSG/OSGDepthChunk.h>
#include <OpenSG/OSGLineChunk.h>
#include <OpenSG/OSGPolygonChunk.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/ParticleSystem/OSGParticleSystem.h>
#include <OpenSG/ParticleSystem/OSGParticleSystemCore.h>
#include <OpenSG/ParticleSystem/OSGNodeParticleSystemCore.h>
#include <OpenSG/ParticleSystem/OSGPointParticleSystemDrawer.h>
#include <OpenSG/ParticleSystem/OSGLineParticleSystemDrawer.h>
#include <OpenSG/ParticleSystem/OSGQuadParticleSystemDrawer.h>
#include <OpenSG/ParticleSystem/OSGDiscParticleSystemDrawer.h>
#include <OpenSG/ParticleSystem/OSGRateParticleGenerator.h>
#include <OpenSG/ParticleSystem/OSGBurstParticleGenerator.h>
#include <OpenSG/ParticleSystem/OSGGravityParticleAffector.h>
#include <OpenSG/ParticleSystem/OSGRadialParticleAffector.h>
#include <OpenSG/ParticleSystem/OSGVortexParticleAffector.h>
#include <OpenSG/ParticleSystem/OSGAgeFadeParticleAffector.h>
#include <OpenSG/ParticleSystem/OSGRandomMovementParticleAffector.h>
#include <OpenSG/ParticleSystem/OSGNewtonParticleAffector.h>
#include <OpenSG/ParticleSystem/OSGConditionalParticleAffector.h>
#include <OpenSG/ParticleSystem/OSGDistanceAttractRepelParticleAffector.h>
#include <OpenSG/Dynamics/OSGGaussianNormalDistribution1D.h>
#include <OpenSG/Dynamics/OSGSegmentDistribution1D.h>
#include <OpenSG/Dynamics/OSGGaussianNormalDistribution3D.h>
#include <OpenSG/Dynamics/OSGGeoSurfaceDistribution3D.h>
#include <OpenSG/Dynamics/OSGSphereDistribution3D.h>
#include <OpenSG/Dynamics/OSGConeDistribution3D.h>
#include <OpenSG/Dynamics/OSGLineDistribution3D.h>
#include <OpenSG/Dynamics/OSGDataConverter.h>
#include <OpenSG/Dynamics/OSGCompoundFunction.h>
#include <OpenSG/Toolbox/OSGLambertMaterial.h>
#include <OpenSG/Toolbox/OSGFCFileHandler.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// Particle Generator Functions
FunctionPtr createPositionDistribution(void);
FunctionPtr createLifespanDistribution(void);
FunctionPtr createVelocityDistribution(void);

//Particle System
ParticleSystemCorePtr ParticleNodeCore;

//Particle System Drawers
PointParticleSystemDrawerPtr ExamplePointParticleSystemDrawer;
LineParticleSystemDrawerPtr ExampleLineParticleSystemDrawer;
QuadParticleSystemDrawerPtr ExampleQuadParticleSystemDrawer;
DiscParticleSystemDrawerPtr ExampleDiscParticleSystemDrawer;


//Particle System Generator
RateParticleGeneratorPtr ExampleGenerator;

// ParticleAffectors
ConditionalParticleAffectorPtr ExampleConditionalAffector;

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

	   if(e->getKey()== KeyEvent::KEY_3)//Use the Quad Drawer for 3
	   {
			beginEditCP(ParticleNodeCore, ParticleSystemCore::DrawerFieldMask);
				ParticleNodeCore->setDrawer(ExampleQuadParticleSystemDrawer);
			endEditCP(ParticleNodeCore,ParticleSystemCore::DrawerFieldMask );
	   }
	   if(e->getKey() == KeyEvent::KEY_F) //particles will be sorted from closest to the view point to the furthest
	   {
			beginEditCP(ParticleNodeCore, ParticleSystemCore::SortingModeFieldMask);
				ParticleNodeCore->setSortingMode(ParticleSystemCore::FRONT_TO_BACK);
			endEditCP(ParticleNodeCore,ParticleSystemCore::SortingModeFieldMask );
	   }
	   if(e->getKey() == KeyEvent::KEY_R) //particles will be sorted from furthest to the view point to the closest.
	   {
			beginEditCP(ParticleNodeCore, ParticleSystemCore::SortingModeFieldMask);
				ParticleNodeCore->setSortingMode(ParticleSystemCore::BACK_TO_FRONT);
			endEditCP(ParticleNodeCore,ParticleSystemCore::SortingModeFieldMask );
	   }
	    if(e->getKey() == KeyEvent::KEY_N) 
	   {
			beginEditCP(ParticleNodeCore, ParticleSystemCore::SortingModeFieldMask);
				ParticleNodeCore->setSortingMode(ParticleSystemCore::NONE);
			endEditCP(ParticleNodeCore,ParticleSystemCore::SortingModeFieldMask);
	   }
		if(e->getKey() == KeyEvent::KEY_O) 
		{
			beginEditCP(ExampleConditionalAffector);
				ExampleConditionalAffector->setConditionalOperator(1); //equals
			endEditCP(ExampleConditionalAffector);
				}
		if(e->getKey() == KeyEvent::KEY_P) 
		{
			beginEditCP(ExampleConditionalAffector);
				ExampleConditionalAffector->setConditionalOperator(2); // not equal
			endEditCP(ExampleConditionalAffector);
	
		}
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

	//Add Key Listener
    TutorialKeyListener TheKeyListener;
    TutorialWindowEventProducer->addKeyListener(&TheKeyListener);

	//Add Mouse Listeners
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
		PSPointChunk->setSize(20.0f);
		PSPointChunk->setSmooth(true);
	endEditCP(PSPointChunk);

	BlendChunkPtr PSBlendChunk = BlendChunk::create();
	beginEditCP(PSBlendChunk);
		PSBlendChunk->setSrcFactor(GL_SRC_ALPHA);
		PSBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
	endEditCP(PSBlendChunk);

	MaterialChunkPtr PSMaterialChunkChunk = MaterialChunk::create();
	beginEditCP(PSMaterialChunkChunk);
		PSMaterialChunkChunk->setAmbient(Color4f(0.2f,0.6f,0.5f,0.3f));
		PSMaterialChunkChunk->setDiffuse(Color4f(0.2f,0.9f,0.1f,0.3f));
		PSMaterialChunkChunk->setSpecular(Color4f(0.5f,0.4f,0.2f,0.6f));
		PSMaterialChunkChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);
	endEditCP(PSMaterialChunkChunk);
	
	//enable depth test
	DepthChunkPtr PSDepthChunk = DepthChunk::create();

	ChunkMaterialPtr PSMaterial = ChunkMaterial::create();
	beginEditCP(PSMaterial, ChunkMaterial::ChunksFieldMask);
		PSMaterial->addChunk(PSPointChunk);
		PSMaterial->addChunk(PSMaterialChunkChunk);
		PSMaterial->addChunk(PSBlendChunk);
		PSMaterial->addChunk(PSDepthChunk);
	endEditCP(PSMaterial, ChunkMaterial::ChunksFieldMask);

	LineChunkPtr PSLineChunk = LineChunk::create();
	ChunkMaterialPtr TestMaterial = ChunkMaterial::create();
	beginEditCP(TestMaterial);
		//TestMaterial->addChunk(PointChunk::create());
		//TestMaterial->addChunk(LineChunk::create());
		TestMaterial->addChunk(PSMaterialChunkChunk);
		TestMaterial->addChunk(PolygonChunk::create());
		TestMaterial->addChunk(BlendChunk::create());
		TestMaterial->addChunk(DepthChunk::create());
	endEditCP(TestMaterial);

	//Particle System
    ParticleSystemPtr ExampleParticleSystem = osg::ParticleSystem::create();

	
    ExampleParticleSystem->attachUpdateListener(TutorialWindowEventProducer);

	ExampleParticleSystem->addParticle(Pnt3f(-40.0,0.0,0.0),
										Vec3f(0.0,1.0,0.0),
										Color4f(1.0,1.0,1.0,1.0),
										Vec3f(1.0,1.0,1.0),
										-1,
										Vec3f(0.0,0.0,0.0),
										Vec3f(0.0,0.0,0.0));

	ExampleParticleSystem->addParticle(Pnt3f(40.0,0.0,0.0),
										Vec3f(0.0,1.0,0.0),
										Color4f(1.0,1.0,1.0,1.0),
										Vec3f(1.0,1.0,1.0),
										-1,
										Vec3f(0.0,0.0,0.0),
										Vec3f(0.0,0.0,0.0));

	for(unsigned int i(0); i < ExampleParticleSystem->getNumParticles(); ++i)
	{
		ExampleParticleSystem->setAttribute("active",0,i);
	}

	ExamplePointParticleSystemDrawer = osg::PointParticleSystemDrawer::create();
	beginEditCP(ExamplePointParticleSystemDrawer);
		ExamplePointParticleSystemDrawer->setForcePerParticleSizing(false);
	endEditCP(ExamplePointParticleSystemDrawer);

	Matrix ExampleMatrix;
	ExampleMatrix.setTransform(Vec3f(10.0,10.0,10.0));

	TransformPtr ExampleXform = osg::Transform::create();
	beginEditCP(ExampleXform);
		ExampleXform->setMatrix(ExampleMatrix);
	endEditCP(ExampleXform);


	NodePtr ExampleNode = osg::Node::create();
	beginEditCP(ExampleNode);
		ExampleNode->setCore(ExampleXform);
	endEditCP(ExampleNode);
	addRefCP(ExampleNode);

	ExampleGenerator = osg::RateParticleGenerator::create();
	beginEditCP(ExampleGenerator);
//		ExampleGenerator->setEmitInWorldSpace(true);
		ExampleGenerator->setBeacon(ExampleNode);
		ExampleGenerator->setGenerationRate(5.0);
		ExampleGenerator->setPositionFunction(createPositionDistribution());
		ExampleGenerator->setLifespanFunction(createLifespanDistribution());
	endEditCP(ExampleGenerator);

	NewtonParticleAffectorPtr ExampleAffector = osg::NewtonParticleAffector::create();
	beginEditCP(ExampleAffector);
		ExampleAffector->setBeacon(ExampleNode);
		ExampleAffector->setMaxDistance(-1.0);
	endEditCP(ExampleAffector);

	ExampleConditionalAffector = osg::ConditionalParticleAffector::create();
	beginEditCP(ExampleConditionalAffector);
		ExampleConditionalAffector->setConditionalAttribute("active");
		ExampleConditionalAffector->setConditionalOperator(4); //greater than
		ExampleConditionalAffector->setConditionalValue(0); // testing if the value associated with "test" = 1
		ExampleConditionalAffector->getAffectors().push_back(ExampleAffector);
	endEditCP(ExampleConditionalAffector);

	DistanceAttractRepelParticleAffectorPtr ExampleAttractRepelAffector = osg::DistanceAttractRepelParticleAffector::create();
	beginEditCP(ExampleAttractRepelAffector);
		ExampleAttractRepelAffector->setDistanceFromSource(DistanceParticleAffector::DISTANCE_FROM_NODE);
	endEditCP(ExampleAttractRepelAffector);

	//Attach the Generators and affectors to the Particle System
	beginEditCP(ExampleParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::MaxParticlesFieldMask | ParticleSystem::SystemAffectorsFieldMask);
		ExampleParticleSystem->setBeacon(ExampleNode);
		//ExampleParticleSystem->getGenerators().push_back(ExampleGenerator);
		ExampleParticleSystem->getAffectors().push_back(ExampleConditionalAffector);
		ExampleParticleSystem->getAffectors().push_back(ExampleAttractRepelAffector);
		ExampleParticleSystem->setMaxParticles(1000);
		ExampleParticleSystem->setDynamic(true);
	endEditCP(ExampleParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::MaxParticlesFieldMask | ParticleSystem::SystemAffectorsFieldMask);
	
	//Particle System Core
    ParticleNodeCore = osg::ParticleSystemCore::create();
    beginEditCP(ParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask | ParticleSystemCore::SortingModeFieldMask);
		ParticleNodeCore->setSystem(ExampleParticleSystem);
		ParticleNodeCore->setDrawer(ExamplePointParticleSystemDrawer);
		ParticleNodeCore->setMaterial(PSMaterial);
		ParticleNodeCore->setSortingMode(ParticleSystemCore::BACK_TO_FRONT);
    endEditCP(ParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask | ParticleSystemCore::SortingModeFieldMask);

	NodePtr PSNode = Node::create();
	beginEditCP(PSNode);
		PSNode->setCore(ParticleNodeCore);
	endEditCP(PSNode);

    // Make Main Scene Node and add the Torus
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
        scene->addChild(PSNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    mgr->setRoot(scene);

    // Show the whole Scene
    mgr->showAll();
	mgr->getCamera()->setFar(1000.0);
	mgr->getCamera()->setNear(0.10);

	FCFileType::FCPtrStore Containers;
	Containers.insert(scene);

	FCFileType::FCTypeVector IgnoreTypes;
	//Save the Field Containers to a xml file
	FCFileHandler::the()->write(Containers,Path("./Data/TestFieldContainers.xml"),IgnoreTypes);

    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "16FullTest");

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
		 //Sphere Distribution
    ConeDistribution3DPtr TheConeDistribution = ConeDistribution3D::create();
    beginEditCP(TheConeDistribution);
      TheConeDistribution->setPosition(Pnt3f(0.0,0.0,0.0));
      TheConeDistribution->setDirection(Vec3f(0.0,0.0,1.0));
      TheConeDistribution->setSpread(3.14159);
	  TheConeDistribution->setMin(1.4);
	  TheConeDistribution->setMax(1.5);
	  TheConeDistribution->setSurfaceOrVolume(ConeDistribution3D::VOLUME);
    endEditCP(TheConeDistribution);

	SphereDistribution3DPtr TheSphereDistribution = SphereDistribution3D::create();
	beginEditCP(TheSphereDistribution);
		TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
		TheSphereDistribution->setInnerRadius(1.0);
		TheSphereDistribution->setOuterRadius(2.0);
		TheSphereDistribution->setMinTheta(0.0);
		TheSphereDistribution->setMaxTheta(6.283185);
		TheSphereDistribution->setMinZ(-1.0);
		TheSphereDistribution->setMaxZ(1.0);
		TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::VOLUME);
	endEditCP(TheSphereDistribution);

    return TheSphereDistribution;
}

FunctionPtr createLifespanDistribution(void)
{
	 SegmentDistribution1DPtr TheLifespanDistribution = SegmentDistribution1D::create();
    beginEditCP(TheLifespanDistribution);
      TheLifespanDistribution->setSegment(Pnt2f(1.0,1.1));
    endEditCP(TheLifespanDistribution);
	
	return TheLifespanDistribution;
}

FunctionPtr createVelocityDistribution(void)
{
	 //Line Distribution
   LineDistribution3DPtr TheLineDistribution = LineDistribution3D::create();
    beginEditCP(TheLineDistribution);
 		TheLineDistribution->setPoint1(Pnt3f(0.0,0.0,0.0));
		TheLineDistribution->setPoint2(Pnt3f(0.0,0.0,0.0));
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

