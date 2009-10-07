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
#include <OpenSG/ParticleSystem/OSGTurbulenceParticleAffector.h>
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

//Particle System
ParticleSystemCorePtr ParticleNodeCore;

//Particle System Drawers
PointParticleSystemDrawerPtr ExamplePointParticleSystemDrawer;
LineParticleSystemDrawerPtr ExampleLineParticleSystemDrawer;

TurbulenceParticleAffectorPtr ExampleTurbulenceAffector;

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
	   if(e->getKey() == KeyEvent::KEY_3)
	   {
			 beginEditCP(ExampleTurbulenceAffector);
				ExampleTurbulenceAffector->setAmplitude(ExampleTurbulenceAffector->getAmplitude() * 0.8);
			endEditCP(ExampleTurbulenceAffector);

	   }
	   if(e->getKey() == KeyEvent::KEY_4)
	   {
			beginEditCP(ExampleTurbulenceAffector);
				ExampleTurbulenceAffector->setAmplitude(ExampleTurbulenceAffector->getAmplitude() * 1.2 + 0.1);
			endEditCP(ExampleTurbulenceAffector);
	   }
	   if(e->getKey() == KeyEvent::KEY_5)
	   {
			beginEditCP(ExampleTurbulenceAffector);
				ExampleTurbulenceAffector->setFrequency(osg::osgClamp<Real32>(0.0f,ExampleTurbulenceAffector->getFrequency() - 1.0, 10000.0f));
			endEditCP(ExampleTurbulenceAffector);
	   }
	   if(e->getKey() == KeyEvent::KEY_6)
	   {
		   beginEditCP(ExampleTurbulenceAffector);
				ExampleTurbulenceAffector->setFrequency(osg::osgClamp<Real32>(0.0f,ExampleTurbulenceAffector->getFrequency() + 1.0, 10000.0f));
			endEditCP(ExampleTurbulenceAffector);
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
		PSMaterialChunkChunk->setColorMaterial(GL_NONE);
	endEditCP(PSMaterialChunkChunk);

	ChunkMaterialPtr PSMaterial = ChunkMaterial::create();
	beginEditCP(PSMaterial, ChunkMaterial::ChunksFieldMask);
		PSMaterial->addChunk(PSPointChunk);
		PSMaterial->addChunk(PSMaterialChunkChunk);
		PSMaterial->addChunk(PSBlendChunk);
	endEditCP(PSMaterial, ChunkMaterial::ChunksFieldMask);

	//Particle System
    ParticleSystemPtr ExampleParticleSystem = osg::ParticleSystem::create();
		ExampleParticleSystem->addParticle(Pnt3f(0,-15,0),
			Vec3f(0.0,0.0f,1.0f),
			Color4f(1.0,1.0,1.0,1.0), 
			Vec3f(1.0,1.0,1.0), 
			0.1, 
			Vec3f(0.0f,0.0f,0.0f), //Velocity
			Vec3f(0.0f,0.0f,0.0f)
			);
		ExampleParticleSystem->addParticle(Pnt3f(0,15,0),
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
		ExampleGenerator->setGenerationRate(60.0f);
	endEditCP(ExampleGenerator, RateParticleGenerator::PositionFunctionFieldMask | RateParticleGenerator::LifespanFunctionFieldMask | RateParticleGenerator::GenerationRateFieldMask);
	

	ExampleTurbulenceAffector = osg::TurbulenceParticleAffector::create();
	beginEditCP(ExampleTurbulenceAffector);
		ExampleTurbulenceAffector->setAmplitude(12.0f);
		ExampleTurbulenceAffector->setInterpolationType(PerlinNoiseDistribution1D::COSINE);
		ExampleTurbulenceAffector->setBeacon(osg::Node::create()); // set to 'emulate' from (0,0,0)
		ExampleTurbulenceAffector->setMaxDistance(-1.0f); // particles affected regardless of distance from affector
		ExampleTurbulenceAffector->setAttenuation(1.0f); // strength of uniform field dimishes by a factor of dist^attenuation
		ExampleTurbulenceAffector->setPersistance(0.75f); //amplitude reduced by .75 each octave
		ExampleTurbulenceAffector->setFrequency(5.0f);	// frequency of turbulent motion (higher freq. = more irregularities)
		ExampleTurbulenceAffector->setOctaves(3);
		ExampleTurbulenceAffector->setPhase(Vec3f(0.0f,0.0f,0.0f));
	endEditCP(ExampleTurbulenceAffector);

	//Attach the Generator and Affector to the Particle System
	beginEditCP(ExampleParticleSystem);
		ExampleParticleSystem->getGenerators().push_back(ExampleGenerator);
		ExampleParticleSystem->getAffectors().push_back(ExampleTurbulenceAffector);
		ExampleParticleSystem->setMaxParticles(300);
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

	std::cout << "Turbulence Particle Affector Tutorial Controls:\n"
		<< "1: Use point drawer\n"
		<< "2: Use line drawer\n"
		<< "3: Decrease amplitude of turbulence.\n"
		<< "4: Increase amplitude of turbulence.\n"
		<< "5: Decrease frequency of turbulence.\n"
		<< "6: Increase frequency of turbulence.\n"
		<< "Ctrl + Q: Exit Tutorial";


    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "27TurbulanceParticleAffector");

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
    SphereDistribution3DPtr TheSphereDistribution = SphereDistribution3D::create();
    beginEditCP(TheSphereDistribution);
      TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
      TheSphereDistribution->setInnerRadius(0.0f);
      TheSphereDistribution->setOuterRadius(10.0f);
      TheSphereDistribution->setMinTheta(-3.141592);
      TheSphereDistribution->setMaxTheta(3.141592);
      TheSphereDistribution->setMinZ(-1.0);
      TheSphereDistribution->setMaxZ(1.0);
	  TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::VOLUME);
    endEditCP(TheSphereDistribution);

    return TheSphereDistribution;
}

FunctionPtr createLifespanDistribution(void)
{
    GaussianNormalDistribution1DPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    beginEditCP(TheLifespanDistribution);
      TheLifespanDistribution->setMean(8.0f);
      TheLifespanDistribution->setStandardDeviation(3.0f);
    endEditCP(TheLifespanDistribution);
	
	return TheLifespanDistribution;
}

