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
#include <OpenSG/ParticleSystem/OSGConeDistribution3D.h>
#include <OpenSG/ParticleSystem/OSGBoxDistribution3D.h>
#include <OpenSG/ParticleSystem/OSGAirParticleAffector.h>

#include <OpenSG/ParticleSystem/OSGGaussianNormalDistribution1D.h>


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

Distribution3DPtr createPositionDistribution(void);
Distribution1DPtr createLifespanDistribution(void);

//Particle System
ParticleSystemCorePtr ParticleNodeCore;

//Particle System Drawers
PointParticleSystemDrawerPtr ExamplePointParticleSystemDrawer;
LineParticleSystemDrawerPtr ExampleLineParticleSystemDrawer;

//Air affector ptr
AirParticleAffectorPtr ExampleAirAffector;

// Create a class to allow for the use of the Ctrl+q
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
	   if(e->getKey()== KeyEvent::KEY_R)
	   {   // reverse the magnitude of the air field
			beginEditCP(ExampleAirAffector);
				ExampleAirAffector->setMagnitude(-(ExampleAirAffector->getMagnitude()));
			endEditCP(ExampleAirAffector);
	   }
	    if(e->getKey()== KeyEvent::KEY_3)
	   {  // decrease spread of field
			beginEditCP(ExampleAirAffector);
				ExampleAirAffector->setSpread(osg::osgClamp<Real32>(0.1f,ExampleAirAffector->getSpread() * 0.8,1.0f));
			endEditCP(ExampleAirAffector);
	   }
		if(e->getKey()== KeyEvent::KEY_4)
	   {  // increase spread of field
			beginEditCP(ExampleAirAffector);
				ExampleAirAffector->setSpread(osg::osgClamp<Real32>(0.1f,ExampleAirAffector->getSpread() * 1.2,1.0f));
			endEditCP(ExampleAirAffector);
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
		PSMaterialChunkChunk->setDiffuse(Color4f(1.0f,1.0f,1.0f,1.0f));
		PSMaterialChunkChunk->setSpecular(Color4f(1.0f,1.0f,1.0f,1.0f));
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
		ExampleParticleSystem->addParticle(Pnt3f(0,25,0),
			Vec3f(0.0,0.0f,1.0f),
			Color4f(1.0,1.0,1.0,1.0), 
			Vec3f(1.0,1.0,1.0), 
			0.1, 
			Vec3f(0.0f,0.0f,0.0f), //Velocity
			Vec3f(0.0f,0.0f,0.0f)
										   );
		ExampleParticleSystem->addParticle(Pnt3f(0,-25,0),
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
	beginEditCP(ExampleGenerator, RateParticleGenerator::PositionDistributionFieldMask | RateParticleGenerator::LifespanDistributionFieldMask | RateParticleGenerator::GenerationRateFieldMask);
		ExampleGenerator->setPositionDistribution(createPositionDistribution());
		ExampleGenerator->setLifespanDistribution(createLifespanDistribution());
		ExampleGenerator->setGenerationRate(200);
	endEditCP(ExampleGenerator, RateParticleGenerator::PositionDistributionFieldMask | RateParticleGenerator::LifespanDistributionFieldMask | RateParticleGenerator::GenerationRateFieldMask);
	
	ExampleAirAffector = osg::AirParticleAffector::create();
	beginEditCP(ExampleAirAffector);
		ExampleAirAffector->setMagnitude(-50.0); // force which the field exerts on particles (negative = towards the air field's beacon location)
		ExampleAirAffector->setBeacon(osg::Node::create()); // set to 'emulate' from (0,0,0)
		ExampleAirAffector->setDirection(Vec3f(1.0,0.0,0.0)); // direction which field is exerted
		ExampleAirAffector->setUseSpread(true); // only affects particles within field spread
		ExampleAirAffector->setSpread(0.2);	// approx 28 degrees of spread
		ExampleAirAffector->setMaxDistance(-1.0); // particles affected regardless of distance from
		ExampleAirAffector->setAttenuation(2.0); // strength of uniform field dimishes by dist^attenuation
	endEditCP(ExampleAirAffector);

		

	//Attach the Generator and Affector to the Particle System
	beginEditCP(ExampleParticleSystem);
		ExampleParticleSystem->getGenerators().push_back(ExampleGenerator);
		ExampleParticleSystem->getAffectors().push_back(ExampleAirAffector);
		ExampleParticleSystem->setMaxParticles(500);
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

	std::cout << "Air Particle Affector Tutorial Controls:\n"
		<< "This affector is set up so that particles within \n\tthe \"spread\" of the affector are pulled towards it.\n"
		<< "1: Use point drawer\n"
		<< "2: Use line drawer\n"
		<< "3: Decrease spread of affector.\n"
		<< "4: Increase spread of affector.\n"
		<< "R: Reverse direction of field\n"
		<< "Ctrl + Q: Exit Tutorial";

    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "25AirFieldParticleAffector");

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

Distribution3DPtr createPositionDistribution(void)
{
	 BoxDistribution3DPtr TheBoxDistribution = BoxDistribution3D::create();
    beginEditCP(TheBoxDistribution);
		TheBoxDistribution->setMinPoint(Pnt3f(-5.0f,-10.0f,-10.0f));
		TheBoxDistribution->setMaxPoint(Pnt3f(15.0f,10.0f,10.0f));
		TheBoxDistribution->setSurfaceOrVolume(BoxDistribution3D::SURFACE);
    endEditCP(TheBoxDistribution);


    return TheBoxDistribution;
}

Distribution1DPtr createLifespanDistribution(void)
{
    GaussianNormalDistribution1DPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    beginEditCP(TheLifespanDistribution);
      TheLifespanDistribution->setMean(15.0f);
      TheLifespanDistribution->setStandardDeviation(3.0);
    endEditCP(TheLifespanDistribution);
	
	return TheLifespanDistribution;
}
