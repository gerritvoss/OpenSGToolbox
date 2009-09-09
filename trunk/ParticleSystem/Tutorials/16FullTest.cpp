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
#include <OpenSG/Dynamics/OSGGaussianNormalDistribution1D.h>
#include <OpenSG/Dynamics/OSGSegmentDistribution1D.h>
#include <OpenSG/Dynamics/OSGGaussianNormalDistribution3D.h>
#include <OpenSG/Dynamics/OSGGeoSurfaceDistribution3D.h>
#include <OpenSG/Dynamics/OSGSphereDistribution3D.h>
#include <OpenSG/Dynamics/OSGConeDistribution3D.h>
#include <OpenSG/Dynamics/OSGLineDistribution3D.h>
#include <OpenSG/Dynamics/OSGDataConverter.h>
#include <OpenSG/Dynamics/OSGCompoundFunction.h>
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


// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEvent& e)
   {
       if(e.getKey() == KeyEvent::KEY_Q && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
            TutorialWindowEventProducer->closeWindow();
       }
   }

   virtual void keyReleased(const KeyEvent& e)
   {
   }

   virtual void keyTyped(const KeyEvent& e)
   {
	   if(e.getKey()== KeyEvent::KEY_1) // Use the Point Drawer
	   {
			beginEditCP(ParticleNodeCore, ParticleSystemCore::DrawerFieldMask);
				ParticleNodeCore->setDrawer(ExamplePointParticleSystemDrawer);
			endEditCP(ParticleNodeCore,ParticleSystemCore::DrawerFieldMask );
	   }

	   if(e.getKey()== KeyEvent::KEY_2)//Use the Line Drawer for 2
	   {
			 beginEditCP(ParticleNodeCore, ParticleSystemCore::DrawerFieldMask);
				ParticleNodeCore->setDrawer(ExampleLineParticleSystemDrawer);
			endEditCP(ParticleNodeCore,ParticleSystemCore::DrawerFieldMask );
	   }

	   if(e.getKey()== KeyEvent::KEY_3)//Use the Quad Drawer for 3
	   {
			beginEditCP(ParticleNodeCore, ParticleSystemCore::DrawerFieldMask);
				ParticleNodeCore->setDrawer(ExampleQuadParticleSystemDrawer);
			endEditCP(ParticleNodeCore,ParticleSystemCore::DrawerFieldMask );
	   }
	   if(e.getKey() == KeyEvent::KEY_F) //particles will be sorted from closest to the view point to the furthest
	   {
			beginEditCP(ParticleNodeCore, ParticleSystemCore::SortingModeFieldMask);
				ParticleNodeCore->setSortingMode(ParticleSystemCore::FRONT_TO_BACK);
			endEditCP(ParticleNodeCore,ParticleSystemCore::SortingModeFieldMask );
	   }
	   if(e.getKey() == KeyEvent::KEY_R) //particles will be sorted from furthest to the view point to the closest.
	   {
			beginEditCP(ParticleNodeCore, ParticleSystemCore::SortingModeFieldMask);
				ParticleNodeCore->setSortingMode(ParticleSystemCore::BACK_TO_FRONT);
			endEditCP(ParticleNodeCore,ParticleSystemCore::SortingModeFieldMask );
	   }
	    if(e.getKey() == KeyEvent::KEY_N) //particles will not be sorted
	   {
			beginEditCP(ParticleNodeCore, ParticleSystemCore::SortingModeFieldMask);
				ParticleNodeCore->setSortingMode(ParticleSystemCore::NONE);
			endEditCP(ParticleNodeCore,ParticleSystemCore::SortingModeFieldMask);
	   }
   }
};

class TutorialMouseListener : public MouseListener
{
  public:
    virtual void mouseClicked(const MouseEvent& e)
    {
    }
    virtual void mouseEntered(const MouseEvent& e)
    {
    }
    virtual void mouseExited(const MouseEvent& e)
    {
    }
    virtual void mousePressed(const MouseEvent& e)
    {
            mgr->mouseButtonPress(e.getButton(), e.getLocation().x(), e.getLocation().y());
    }
    virtual void mouseReleased(const MouseEvent& e)
    {
           mgr->mouseButtonRelease(e.getButton(), e.getLocation().x(), e.getLocation().y());
    }
};

class TutorialMouseMotionListener : public MouseMotionListener
{
  public:
    virtual void mouseMoved(const MouseEvent& e)
    {
            mgr->mouseMove(e.getLocation().x(), e.getLocation().y());
    }

    virtual void mouseDragged(const MouseEvent& e)
    {
            mgr->mouseMove(e.getLocation().x(), e.getLocation().y());
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
		PSPointChunk->setSize(6.0f);
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
		PSMaterialChunkChunk->setColorMaterial(GL_NONE);
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

	//Particle System Drawer
		//Point
	/*ExamplePointParticleSystemDrawer = osg::PointParticleSystemDrawer::create();*/
    //ExamplePointParticleSystemDrawer->setForcePerParticleSizing(true);

		//Line
	//ExampleLineParticleSystemDrawer = osg::LineParticleSystemDrawer::create();
	//beginEditCP(ExampleLineParticleSystemDrawer);
	//	ExampleLineParticleSystemDrawer->setLineDirectionSource(LineParticleSystemDrawer::DIRECTION_NORMAL);//DIRECTION_VELOCITY_CHANGE);
	//	ExampleLineParticleSystemDrawer->setLineLengthSource(LineParticleSystemDrawer::LENGTH_SIZE_X);
	//	ExampleLineParticleSystemDrawer->setEndPointFading(Vec2f(1.0,0.0));
	//endEditCP(ExampleLineParticleSystemDrawer);
	//	//Quad
	//ExampleQuadParticleSystemDrawer = osg::QuadParticleSystemDrawer::create();
	//beginEditCP(ExampleQuadParticleSystemDrawer);
	//	ExampleQuadParticleSystemDrawer->setQuadSizeScaling(Vec2f(0.8,1.2));
	//	ExampleQuadParticleSystemDrawer->setNormalSource(QuadParticleSystemDrawer::NORMAL_PARTICLE_NORMAL);
	//endEditCP(ExampleQuadParticleSystemDrawer);
	//
	//ExampleDiscParticleSystemDrawer = osg::DiscParticleSystemDrawer::create();

		//Create a Rate Particle Generator
	//BurstParticleGeneratorPtr ExampleGenerator = osg::BurstParticleGenerator::create();

	RateParticleGeneratorPtr ExampleGeneratorTheSequel = osg::RateParticleGenerator::create();

	////Attach the function objects to the Generator
	//beginEditCP(ExampleGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask | BurstParticleGenerator::BurstAmountFieldMask);
	//	ExampleGenerator->setPositionFunction(createPositionDistribution());
	//	ExampleGenerator->setLifespanFunction(createLifespanDistribution());
	//	ExampleGenerator->setVelocityFunction(createVelocityDistribution());
	//	ExampleGenerator->setBurstAmount(1000);
	//endEditCP(ExampleGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask | BurstParticleGenerator::BurstAmountFieldMask);
	//
	//Attach the function objects to the Generator
	beginEditCP(ExampleGeneratorTheSequel, RateParticleGenerator::PositionFunctionFieldMask | RateParticleGenerator::LifespanFunctionFieldMask | RateParticleGenerator::GenerationRateFieldMask);
		ExampleGeneratorTheSequel->setPositionFunction(createPositionDistribution());
		//ExampleGeneratorTheSequel->setLifespanFunction(createLifespanDistribution());
		ExampleGeneratorTheSequel->setGenerationRate(300.0);
		ExampleGeneratorTheSequel->setVelocityFunction(createVelocityDistribution());
		ExampleGeneratorTheSequel->setSizeFunction(NullFC);
	endEditCP(ExampleGeneratorTheSequel, RateParticleGenerator::PositionFunctionFieldMask | RateParticleGenerator::LifespanFunctionFieldMask | RateParticleGenerator::GenerationRateFieldMask);

	// create a gravity affector

	//NodePtr AffectorBeacon = osg::Node::create();

	//RadialParticleAffectorPtr ExampleRadialAffector = osg::RadialParticleAffector::create();
	//beginEditCP(ExampleRadialAffector);
	//	ExampleRadialAffector->setBeacon(osg::Node::create());
	//	ExampleRadialAffector->setMagnitude(-9.5);
	//	ExampleRadialAffector->setAttenuation(2.0);
	//endEditCP(ExampleRadialAffector);


	//VortexParticleAffectorPtr ExampleVortexAffector = osg::VortexParticleAffector::create();
	//beginEditCP(ExampleVortexAffector);
	//	ExampleVortexAffector->setBeacon(osg::Node::create());
	//	ExampleVortexAffector->setMagnitude(-9.5);
	//	ExampleVortexAffector->setAttenuation(2.0);
	//endEditCP(ExampleVortexAffector);




	//Attach the Generator to the Particle System
	beginEditCP(ExampleParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::MaxParticlesFieldMask | ParticleSystem::SystemAffectorsFieldMask);
		//ExampleParticleSystem->getGenerators().push_back(ExampleGenerator);
		ExampleParticleSystem->setMaxParticles(100);
		ExampleParticleSystem->getGenerators().push_back(ExampleGeneratorTheSequel);
		//ExampleParticleSystem->getAffectors().push_back(ExampleVortexAffector);
	endEditCP(ExampleParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::MaxParticlesFieldMask | ParticleSystem::SystemAffectorsFieldMask);
	
	//Particle System Node
    ParticleNodeCore = osg::ParticleSystemCore::create();
    beginEditCP(ParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask | ParticleSystemCore::SortingModeFieldMask);
		ParticleNodeCore->setSystem(ExampleParticleSystem);
		ParticleNodeCore->setDrawer(ExamplePointParticleSystemDrawer);
		ParticleNodeCore->setMaterial(TestMaterial);
		ParticleNodeCore->setSortingMode(ParticleSystemCore::FRONT_TO_BACK);
    endEditCP(ParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask | ParticleSystemCore::SortingModeFieldMask);


    GeometryPtr NewGeo = makeSphereGeo(1,1.0f);
	beginEditCP(NewGeo);
		NewGeo->setMaterial(TestMaterial);
	endEditCP(NewGeo);

	NodePtr PSGeometryNode = Node::create();
	beginEditCP(PSGeometryNode);
		PSGeometryNode->setCore(NewGeo);
	endEditCP(PSGeometryNode);

	NodeParticleSystemCorePtr NodePSCore = osg::NodeParticleSystemCore::create();
	beginEditCP(NodePSCore);
		NodePSCore->setSystem(ExampleParticleSystem);
		NodePSCore->setSizeScaling(Vec3f(1.0f,1.0f,1.0f));
		NodePSCore->setNormal(Vec3f(0.0,1.0,0.0));
		NodePSCore->setPrototypeNode(PSGeometryNode);
	endEditCP(NodePSCore);


	NodePtr ParticleNode = osg::Node::create();
    beginEditCP(ParticleNode, Node::CoreFieldMask);
        ParticleNode->setCore(NodePSCore);
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

	mgr->getCamera()->setFar(500.0);

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
      TheLifespanDistribution->setSegment(Pnt2f(10.0,20.1));
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

