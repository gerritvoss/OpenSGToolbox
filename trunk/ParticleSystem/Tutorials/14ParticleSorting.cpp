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
#include <OpenSG/OSGDepthChunk.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/ParticleSystem/OSGParticleSystem.h>
#include <OpenSG/ParticleSystem/OSGParticleSystemCore.h>
#include <OpenSG/ParticleSystem/OSGPointParticleSystemDrawer.h>
#include <OpenSG/ParticleSystem/OSGLineParticleSystemDrawer.h>
#include <OpenSG/ParticleSystem/OSGQuadParticleSystemDrawer.h>
#include <OpenSG/ParticleSystem/OSGDiscParticleSystemDrawer.h>
#include <OpenSG/ParticleSystem/OSGRateParticleGenerator.h>
#include <OpenSG/ParticleSystem/OSGBurstParticleGenerator.h>
#include <OpenSG/ParticleSystem/OSGGravityParticleAffector.h>
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


//Particle System Generator
RateParticleGeneratorPtr ExampleGenerator;


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
	    if(e->getKey() == KeyEvent::KEY_N) //particles will not be sorted
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
		PSMaterialChunkChunk->setEmission(Color4f(0.2f,0.6f,0.5f,0.3f));
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

	//Particle System
    ParticleSystemPtr ExampleParticleSystem = osg::ParticleSystem::create();
    ExampleParticleSystem->attachUpdateListener(TutorialWindowEventProducer);

	//Particle System Drawer
		//Point
	ExamplePointParticleSystemDrawer = osg::PointParticleSystemDrawer::create();
    //ExamplePointParticleSystemDrawer->setForcePerParticleSizing(true);

		//Line
	ExampleLineParticleSystemDrawer = osg::LineParticleSystemDrawer::create();
	beginEditCP(ExampleLineParticleSystemDrawer);
		ExampleLineParticleSystemDrawer->setLineDirectionSource(LineParticleSystemDrawer::DIRECTION_NORMAL);//DIRECTION_VELOCITY_CHANGE);
		ExampleLineParticleSystemDrawer->setLineLengthSource(LineParticleSystemDrawer::LENGTH_SIZE_X);
		ExampleLineParticleSystemDrawer->setEndPointFading(Vec2f(1.0,0.0));
	endEditCP(ExampleLineParticleSystemDrawer);
		//Quad
	ExampleQuadParticleSystemDrawer = osg::QuadParticleSystemDrawer::create();
	beginEditCP(ExampleQuadParticleSystemDrawer);
		ExampleQuadParticleSystemDrawer->setQuadSizeScaling(Vec2f(0.8,1.2));
		ExampleQuadParticleSystemDrawer->setNormalSource(QuadParticleSystemDrawer::NORMAL_PARTICLE_NORMAL);
	endEditCP(ExampleQuadParticleSystemDrawer);

	RateParticleGeneratorPtr ExampleGeneratorTheSequel = osg::RateParticleGenerator::create();

	//Attach the function objects to the Generator
	beginEditCP(ExampleGeneratorTheSequel, RateParticleGenerator::PositionFunctionFieldMask | RateParticleGenerator::LifespanFunctionFieldMask | RateParticleGenerator::GenerationRateFieldMask);
		ExampleGeneratorTheSequel->setPositionFunction(createPositionDistribution());
		ExampleGeneratorTheSequel->setLifespanFunction(createLifespanDistribution());
		ExampleGeneratorTheSequel->setGenerationRate(300.0);
		ExampleGeneratorTheSequel->setVelocityFunction(createVelocityDistribution());
	endEditCP(ExampleGeneratorTheSequel, RateParticleGenerator::PositionFunctionFieldMask | RateParticleGenerator::LifespanFunctionFieldMask | RateParticleGenerator::GenerationRateFieldMask);


	//Attach the Generator to the Particle System
	beginEditCP(ExampleParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::MaxParticlesFieldMask | ParticleSystem::SystemAffectorsFieldMask);
		//ExampleParticleSystem->getGenerators().push_back(ExampleGenerator);
		ExampleParticleSystem->setMaxParticles(500);
		ExampleParticleSystem->getGenerators().push_back(ExampleGeneratorTheSequel);
	endEditCP(ExampleParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::MaxParticlesFieldMask | ParticleSystem::SystemAffectorsFieldMask);
	
	//Particle System Node
    ParticleNodeCore = osg::ParticleSystemCore::create();
    beginEditCP(ParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask | ParticleSystemCore::SortingModeFieldMask);
		ParticleNodeCore->setSystem(ExampleParticleSystem);
		ParticleNodeCore->setDrawer(ExamplePointParticleSystemDrawer);
		ParticleNodeCore->setMaterial(PSMaterial);
    endEditCP(ParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask | ParticleSystemCore::SortingModeFieldMask);

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

	mgr->getCamera()->setFar(500.0);

    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "14ParticleSorting");

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
		 //Cone Distribution
    ConeDistribution3DPtr TheConeDistribution = ConeDistribution3D::create();
    beginEditCP(TheConeDistribution);
      TheConeDistribution->setPosition(Pnt3f(0.0,0.0,0.0));
      TheConeDistribution->setDirection(Vec3f(0.0,0.0,1.0));
      TheConeDistribution->setSpread(1.57);
	  TheConeDistribution->setMinTheta(0.0);
	  TheConeDistribution->setMaxTheta(6.282);
	  TheConeDistribution->setMin(0.0);
	  TheConeDistribution->setMax(1.0);
	  TheConeDistribution->setSurfaceOrVolume(ConeDistribution3D::VOLUME);
    endEditCP(TheConeDistribution);

    return TheConeDistribution;
}

FunctionPtr createLifespanDistribution(void)
{
	 SegmentDistribution1DPtr TheLifespanDistribution = SegmentDistribution1D::create();
    beginEditCP(TheLifespanDistribution);
      TheLifespanDistribution->setSegment(Pnt2f(2.0,3.0));
    endEditCP(TheLifespanDistribution);
	
	return TheLifespanDistribution;
}

FunctionPtr createVelocityDistribution(void)
{
	 //Line Distribution, no velocity
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

