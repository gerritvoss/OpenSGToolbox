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
#include <OpenSG/ParticleSystem/OSGParticleCollisionListener.h>
#include <OpenSG/Input/OSGWindowAdapter.h>
#include <OpenSG/Toolbox/OSGMathUtils.h>

#include <OpenSG/OSGBlendChunk.h>
#include <OpenSG/OSGPointChunk.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/OSGTextureChunk.h>
#include <OpenSG/OSGImageFileHandler.h>

#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSceneFileHandler.h>

#include <OpenSG/ParticleSystem/OSGParticleSystem.h>
#include <OpenSG/ParticleSystem/OSGParticleSystemCore.h>
#include <OpenSG/ParticleSystem/OSGNodeParticleSystemCore.h>

#include <OpenSG/ParticleSystem/OSGPointParticleSystemDrawer.h>
#include <OpenSG/ParticleSystem/OSGLineParticleSystemDrawer.h>
#include <OpenSG/ParticleSystem/OSGQuadParticleSystemDrawer.h>

#include <OpenSG/ParticleSystem/OSGAgeFadeParticleAffector.h>
#include <OpenSG/ParticleSystem/OSGAgeSizeParticleAffector.h>
#include <OpenSG/ParticleSystem/OSGDistanceKillParticleAffector.h>
#include <OpenSG/ParticleSystem/OSGCollectiveGravityParticleSystemAffector.h>
#include <OpenSG/ParticleSystem/OSGGeometryCollisionParticleSystemAffector.h>

#include <OpenSG/ParticleSystem/OSGRateParticleGenerator.h>
#include <OpenSG/ParticleSystem/OSGBurstParticleGenerator.h>
#include <OpenSG/ParticleSystem/OSGParticleSystemListener.h>

#include <OpenSG/Dynamics/OSGLineDistribution3D.h>
#include <OpenSG/Dynamics/OSGCylinderDistribution3D.h>
#include <OpenSG/Dynamics/OSGGaussianNormalDistribution1D.h>
#include <OpenSG/Dynamics/OSGDiscDistribution3D.h>
#include <OpenSG/Dynamics/OSGSphereDistribution3D.h>

#include <OpenSG/Dynamics/OSGDataConverter.h>
#include <OpenSG/Dynamics/OSGCompoundFunction.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

bool ExitApp = false;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

//Particle System Drawer

QuadParticleSystemDrawerPtr SmokeParticleSystemDrawer;
PointParticleSystemDrawerPtr ExampleShrapnelParticleSystemDrawer;
PointParticleSystemDrawerPtr ExampleFireballParticleSystemDrawer;

ParticleSystemPtr RocketParticleSystem;
ParticleSystemPtr SmokeParticleSystem;
ParticleSystemPtr ShrapnelParticleSystem;
ParticleSystemPtr FireballParticleSystem;
ParticleSystemPtr HouseParticleSystem;

BurstParticleGeneratorPtr ShrapnelBurstGenerator;
RateParticleGeneratorPtr SmokeGenerator;
BurstParticleGeneratorPtr FireballGenerator;

AgeFadeParticleAffectorPtr SmokeAgeFadeParticleAffector;
AgeSizeParticleAffectorPtr SmokeAgeSizeParticleAffector;
AgeSizeParticleAffectorPtr FireballAgeSizeParticleAffector;
ParticleSystemCorePtr PointParticleNodeCore;

FunctionPtr FireballPositionDistribution;
FunctionPtr ShrapnelPositionDistribution;
FunctionPtr SmokePositionDistribution;

FunctionPtr createPositionDistribution(void);
FunctionPtr createLifespanDistribution(void);
FunctionPtr createVelocityDistribution(void);

FunctionPtr createSmokeVelocityDistribution(void);
FunctionPtr createSmokeLifespanDistribution(void);
FunctionPtr createSmokePositionDistribution(void);

FunctionPtr createShrapnelPositionDistribution(void);
FunctionPtr createShrapnelAccelerationDistribution(void);
FunctionPtr createShrapnelVelocityDistribution(void);

FunctionPtr createFireballVelocityDistribution(void);
FunctionPtr createFireballPositionDistribution(void);
FunctionPtr createFireballAccelerationDistribution(void);
FunctionPtr createFireballLifespanDistribution(void);



// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEvent& e)
   {
       if(e.getKey() == KeyEvent::KEY_Q && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           ExitApp = true;
       }

	   if(e.getKey() == KeyEvent::KEY_B)//generate particles when clicked
	   {
		 
	   }
   }

   virtual void keyReleased(const KeyEvent& e)
   {
   }

   virtual void keyTyped(const KeyEvent& e)
   {
	   if(e.getKey()== KeyEvent::KEY_1) // Use the Point Drawer
	   {
			
	   }

   }
};

class TutorialWindowListener : public WindowAdapter
{
public:
    virtual void windowClosing(const WindowEvent& e)
    {
        ExitApp = true;
    }

    virtual void windowClosed(const WindowEvent& e)
    {
        ExitApp = true;
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
		if(WindowEventProducer::Ptr::dcast(e.getSource())->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
		{
            mgr->mouseButtonPress(e.getButton(), e.getLocation().x(), e.getLocation().y());
		}
		else
		{
          Line TheRay;
			if(e.getButton() == MouseEvent::BUTTON1)
			{
				
				mgr->getCamera()->calcViewRay(TheRay,e.getLocation().x(),e.getLocation().y(),*(mgr->getWindow()->getPort(0)));
				std::cout<<"Velocity "<<TheRay.getDirection()<<std::endl;
			}
			RocketParticleSystem->addParticle(TheRay.getPosition(),
			Vec3f(0.0,1.0f,0.0f),
			Color4f(1.0,0.0,0.0,1.0), 
			Vec3f(1.0,1.0,1.0), 
			10, 
			Vec3f(TheRay.getDirection()*50), //Velocity
			Vec3f(0.0f,0.0f,0.0f)
			,0);
		}
    }
    virtual void mouseReleased(const MouseEvent& e)
    {
		if(WindowEventProducer::Ptr::dcast(e.getSource())->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
		{
           mgr->mouseButtonRelease(e.getButton(), e.getLocation().x(), e.getLocation().y());
		}
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

class TutorialRocketParticleSystemListener : public ParticleSystemListener
{
  public:
   virtual void systemUpdated(const ParticleSystemEvent& e)
   {
   }
   virtual void particleGenerated(const ParticleEvent& e) 
   {
   }
   virtual void particleKilled(const ParticleEvent& e)
   {
    beginEditCP(FireballPositionDistribution);
		SphereDistribution3D::Ptr::dcast(FireballPositionDistribution)->setCenter(e.getPosition());
    endEditCP(FireballPositionDistribution);

	beginEditCP(ShrapnelPositionDistribution);
		SphereDistribution3D::Ptr::dcast(ShrapnelPositionDistribution)->setCenter(e.getPosition());
    endEditCP(ShrapnelPositionDistribution);

	beginEditCP(SmokePositionDistribution);
		DiscDistribution3D::Ptr::dcast(SmokePositionDistribution)->setCenter(e.getPosition());
    endEditCP(SmokePositionDistribution);
	
	   
	  // if()
	   {

		    //Attach the Generator to the Shrapnel Particle System
				beginEditCP(ShrapnelParticleSystem, ParticleSystem::GeneratorsFieldMask);
					ShrapnelParticleSystem->getGenerators().push_back(ShrapnelBurstGenerator);
				endEditCP(ShrapnelParticleSystem, ParticleSystem::GeneratorsFieldMask);
		
		//Attach the Affector to the Smoke Particle System
				beginEditCP(SmokeParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
					SmokeParticleSystem->getGenerators().push_back(SmokeGenerator);
					SmokeParticleSystem->getAffectors().push_back(SmokeAgeFadeParticleAffector);
					SmokeParticleSystem->getAffectors().push_back(SmokeAgeSizeParticleAffector);
				endEditCP(SmokeParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
		
		//Attach the Affector to the fireball Particle System
				beginEditCP(FireballParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
					FireballParticleSystem->getGenerators().push_back(FireballGenerator);
					FireballParticleSystem->getAffectors().push_back(FireballAgeSizeParticleAffector);
				endEditCP(FireballParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);

	   }
	   std::cout << "Rocket Died at: " << e.getPosition() << std::endl;
   }
   virtual void particleStolen(const ParticleEvent& e)
   {
   }
};
class TutorialParticleCollisionListener : public ParticleCollisionListener
{
   virtual void particleCollision(const ParticleEvent& ParE, const CollisionEvent& ColE)
   {
	   Real32 phi= osgacos((ParE.getVelocity().dot(ColE.getHitNormal()))/(ParE.getVelocity().length()*ColE.getHitNormal().length()));
	   
		float degree = deg2rad(80.0);
	   if( deg2rad(80.0) < phi)
	   {
		   ParE.getSystem()->killParticle(ParE.getIndex());
	   }
	   else
	   {
			//Reflect the Particle
		   Vec3f Reflect(reflect(ParE.getVelocity(), ColE.getHitNormal()));
		   ParE.getSystem()->setVelocity(Reflect, ParE.getIndex());
		   ParE.getSystem()->setPosition(ColE.getHitPoint() + (0.00001f*Reflect), ParE.getIndex());
	   }
	  
   }
};
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    WindowEventProducerPtr TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

	beginEditCP(TutorialWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);
		TutorialWindowEventProducer->setUseCallbackForDraw(true);
		TutorialWindowEventProducer->setUseCallbackForReshape(true);
	endEditCP(TutorialWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);

    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TutorialWindowEventProducer->addWindowListener(&TheTutorialWindowListener);
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
	
    TutorialWindowEventProducer->openWindow(Pnt2f(0,0),
                                        Vec2f(1280,1024),
                                        "OpenSG 20RocketLauncher Window");
										

	//Particle System Material
		//point material
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
		PSMaterialChunkChunk->setAmbient(Color4f(0.3f,0.3f,0.3f,1.0f));
		PSMaterialChunkChunk->setDiffuse(Color4f(0.7f,0.7f,0.7f,1.0f));
		PSMaterialChunkChunk->setSpecular(Color4f(0.9f,0.9f,0.9f,1.0f));
		PSMaterialChunkChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);
	endEditCP(PSMaterialChunkChunk);

	ChunkMaterialPtr PSPointMaterial = ChunkMaterial::create();
	beginEditCP(PSPointMaterial, ChunkMaterial::ChunksFieldMask);
		PSPointMaterial->addChunk(PSPointChunk);
		PSPointMaterial->addChunk(PSMaterialChunkChunk);
		PSPointMaterial->addChunk(PSBlendChunk);
	endEditCP(PSPointMaterial, ChunkMaterial::ChunksFieldMask);

		//smoke material
	TextureChunkPtr QuadTextureChunk = TextureChunk::create();
    ImagePtr LoadedImage = ImageFileHandler::the().read("Data/ooze.png");    
    beginEditCP(QuadTextureChunk, TextureChunk::ImageFieldMask);
        QuadTextureChunk->setImage(LoadedImage);
        QuadTextureChunk->setEnvMode(GL_MODULATE);
    endEditCP(QuadTextureChunk, TextureChunk::ImageFieldMask);

	MaterialChunkPtr PSMaterialChunk = MaterialChunk::create();
	beginEditCP(PSMaterialChunk);
		PSMaterialChunk->setAmbient(Color4f(0.3f,0.3f,0.3f,1.0f));
		PSMaterialChunk->setDiffuse(Color4f(0.7f,0.7f,0.7f,1.0f));
		PSMaterialChunk->setSpecular(Color4f(0.9f,0.9f,0.9f,1.0f));
		PSMaterialChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);
	endEditCP(PSMaterialChunk);

	ChunkMaterialPtr PSSmokeMaterial = ChunkMaterial::create();
	beginEditCP(PSSmokeMaterial, ChunkMaterial::ChunksFieldMask);
		PSSmokeMaterial->addChunk(QuadTextureChunk);
		PSSmokeMaterial->addChunk(PSMaterialChunk);
		PSSmokeMaterial->addChunk(PSBlendChunk);
	endEditCP(PSSmokeMaterial, ChunkMaterial::ChunksFieldMask);


	//Particle System
		//Rocket
    RocketParticleSystem = osg::ParticleSystem::create();
	RocketParticleSystem->attachUpdateListener(TutorialWindowEventProducer);

	TutorialRocketParticleSystemListener TheRocketListener;
	RocketParticleSystem->addParticleSystemListener(&TheRocketListener);

		//smoke
	SmokeParticleSystem = osg::ParticleSystem::create();
	SmokeParticleSystem->attachUpdateListener(TutorialWindowEventProducer);
		//Shrapnel
	ShrapnelParticleSystem = osg::ParticleSystem::create();
	ShrapnelParticleSystem->attachUpdateListener(TutorialWindowEventProducer);
		//Fireball
	FireballParticleSystem = osg::ParticleSystem::create();
	FireballParticleSystem->attachUpdateListener(TutorialWindowEventProducer);



	//Particle System Drawer
		//Rocket does not have a drawer because it is being attached to a special node core
		//Smoke
	SmokeParticleSystemDrawer = osg::QuadParticleSystemDrawer::create();
	//SmokeParticleSystemDrawer->setQuadSizeScaling(Vec2f(0.5f,0.5f));
		//Shrapnel
	ExampleShrapnelParticleSystemDrawer = osg::PointParticleSystemDrawer::create();
    ExampleShrapnelParticleSystemDrawer->setForcePerParticleSizing(true);
		//Fireball
	ExampleFireballParticleSystemDrawer = osg::PointParticleSystemDrawer::create();
    ExampleFireballParticleSystemDrawer->setForcePerParticleSizing(true);

		
	
	//Particle System Node
		//collision node
	//NodePtr EnvironmentNode = makeSphere(2,4.0f);

	Matrix EnvironmentTransformation;
	EnvironmentTransformation.setScale(0.1f);

	TransformPtr EnvironmentTransformCore = Transform::create();
	beginEditCP(EnvironmentTransformCore, Transform::MatrixFieldMask);
		EnvironmentTransformCore->setMatrix(EnvironmentTransformation);
	endEditCP(EnvironmentTransformCore, Transform::MatrixFieldMask);
	
	NodePtr EnvironmentNode = Node::create();
	beginEditCP(EnvironmentNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
		EnvironmentNode->setCore(EnvironmentTransformCore);
		EnvironmentNode->addChild(SceneFileHandler::the().read("Data/Chloroplast.osb"));
	endEditCP(EnvironmentNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

		//NodePtr ParticlePrototypeNode = makeTorus(1.0,4.0,16,16);
	NodePtr RocketParticlePrototypeNode = SceneFileHandler::the().read("Data/rocket.obj");
	
    NodeParticleSystemCorePtr RocketParticleNodeCore = osg::NodeParticleSystemCore::create();
    beginEditCP(RocketParticleNodeCore, NodeParticleSystemCore::SystemFieldMask | NodeParticleSystemCore::PrototypeNodeFieldMask);
		RocketParticleNodeCore->setSystem(RocketParticleSystem);
		RocketParticleNodeCore->setPrototypeNode(RocketParticlePrototypeNode);
        RocketParticleNodeCore->setNormalSource(NodeParticleSystemCore::NORMAL_VELOCITY);
        RocketParticleNodeCore->setUpSource(NodeParticleSystemCore::UP_PARTICLE_NORMAL);
        RocketParticleNodeCore->setUp(Vec3f(0.0f,1.0f,0.0f));
    endEditCP(RocketParticleNodeCore, NodeParticleSystemCore::SystemFieldMask | NodeParticleSystemCore::PrototypeNodeFieldMask);
	
	//Geometry Collision Affector
	GeometryCollisionParticleSystemAffectorPtr ExampleGeometryCollisionParticleSystemAffector = GeometryCollisionParticleSystemAffector::create();
	beginEditCP(ExampleGeometryCollisionParticleSystemAffector, GeometryCollisionParticleSystemAffector::CollisionNodeFieldMask);
		ExampleGeometryCollisionParticleSystemAffector->setCollisionNode(EnvironmentNode);
	endEditCP(ExampleGeometryCollisionParticleSystemAffector, GeometryCollisionParticleSystemAffector::CollisionNodeFieldMask);

	TutorialParticleCollisionListener TheCollisionListener;
	ExampleGeometryCollisionParticleSystemAffector->addParticleCollisionListener(&TheCollisionListener);


	NodePtr RocketParticleNode = osg::Node::create();
    beginEditCP(RocketParticleNode, Node::CoreFieldMask);
        RocketParticleNode->setCore(RocketParticleNodeCore);
    endEditCP(RocketParticleNode, Node::CoreFieldMask);

	//Attach the Affector to the Rocket Particle System
	beginEditCP(RocketParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
		//RocketParticleSystem->getAffectors().push_back();
		RocketParticleSystem->getSystemAffectors().push_back(ExampleGeometryCollisionParticleSystemAffector);
	endEditCP(RocketParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);

		
		//Smoke
	SmokeGenerator = osg::RateParticleGenerator::create();
			//Attach the function objects to the Generator
	SmokePositionDistribution = createSmokePositionDistribution();
	beginEditCP(SmokeGenerator, RateParticleGenerator::PositionFunctionFieldMask | RateParticleGenerator::LifespanFunctionFieldMask | RateParticleGenerator::GenerationRateFieldMask);
		SmokeGenerator->setPositionFunction(SmokePositionDistribution);
		SmokeGenerator->setLifespanFunction(createSmokeLifespanDistribution());
		SmokeGenerator->setGenerationRate(50.0);
		SmokeGenerator->setVelocityFunction(createSmokeVelocityDistribution());
	endEditCP(SmokeGenerator, RateParticleGenerator::PositionFunctionFieldMask | RateParticleGenerator::LifespanFunctionFieldMask | RateParticleGenerator::GenerationRateFieldMask);
			//Attach the function objects the Affectors
	SmokeAgeFadeParticleAffector = osg::AgeFadeParticleAffector::create();
	beginEditCP(SmokeAgeFadeParticleAffector, AgeFadeParticleAffector::FadeInTimeFieldMask | AgeFadeParticleAffector::FadeOutTimeFieldMask | AgeFadeParticleAffector::StartAlphaFieldMask| AgeFadeParticleAffector::FadeToAlphaFieldMask | AgeFadeParticleAffector::EndAlphaFieldMask);
		SmokeAgeFadeParticleAffector->setFadeInTime(2.0f);
		SmokeAgeFadeParticleAffector->setFadeOutTime(5.0f);
		SmokeAgeFadeParticleAffector->setStartAlpha(0.0f);
		SmokeAgeFadeParticleAffector->setFadeToAlpha(0.2f);
		SmokeAgeFadeParticleAffector->setEndAlpha(0.0f);	
	endEditCP(SmokeAgeFadeParticleAffector, AgeFadeParticleAffector::FadeInTimeFieldMask | AgeFadeParticleAffector::FadeOutTimeFieldMask | AgeFadeParticleAffector::StartAlphaFieldMask| AgeFadeParticleAffector::FadeToAlphaFieldMask | AgeFadeParticleAffector::EndAlphaFieldMask);

	SmokeAgeSizeParticleAffector = osg::AgeSizeParticleAffector::create();
	beginEditCP(SmokeAgeSizeParticleAffector,AgeSizeParticleAffector::AgesFieldMask | AgeSizeParticleAffector::SizesFieldMask);
			//ages
			SmokeAgeSizeParticleAffector->getAges().push_back(0.1);
			SmokeAgeSizeParticleAffector->getAges().push_back(0.2);
			SmokeAgeSizeParticleAffector->getAges().push_back(0.3);
			SmokeAgeSizeParticleAffector->getAges().push_back(0.5);
			SmokeAgeSizeParticleAffector->getAges().push_back(0.7);
			SmokeAgeSizeParticleAffector->getAges().push_back(0.8);
			SmokeAgeSizeParticleAffector->getAges().push_back(1.0);

			//sizes
			SmokeAgeSizeParticleAffector->getSizes().push_back(Vec3f(0.5,0.5,0.5));
			SmokeAgeSizeParticleAffector->getSizes().push_back(Vec3f(1.0,1.0,1.0));
			SmokeAgeSizeParticleAffector->getSizes().push_back(Vec3f(2.0,2.0,2.0));
			SmokeAgeSizeParticleAffector->getSizes().push_back(Vec3f(3.0,3.0,3.0));
			SmokeAgeSizeParticleAffector->getSizes().push_back(Vec3f(4.0,4.0,4.0));
			SmokeAgeSizeParticleAffector->getSizes().push_back(Vec3f(5.0,5.0,5.0));
			SmokeAgeSizeParticleAffector->getSizes().push_back(Vec3f(6.5,6.5,6.5));
	endEditCP(SmokeAgeSizeParticleAffector,AgeSizeParticleAffector::AgesFieldMask | AgeSizeParticleAffector::SizesFieldMask);
   
	ParticleSystemCorePtr SmokeParticleNodeCore = osg::ParticleSystemCore::create();
    beginEditCP(SmokeParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
		SmokeParticleNodeCore->setSystem(SmokeParticleSystem);
		SmokeParticleNodeCore->setDrawer(SmokeParticleSystemDrawer);
		SmokeParticleNodeCore->setMaterial(PSSmokeMaterial);
    endEditCP(SmokeParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
    
	NodePtr SmokeParticleNode = osg::Node::create();
    beginEditCP(SmokeParticleNode, Node::CoreFieldMask);
        SmokeParticleNode->setCore(SmokeParticleNodeCore);
    endEditCP(SmokeParticleNode, Node::CoreFieldMask);
		//end/////////////////////

		//Shrapnel
	ShrapnelBurstGenerator = osg::BurstParticleGenerator::create();
	NodePtr ShrapnelParticlePrototypeNode = SceneFileHandler::the().read("Data/Shrapnel.obj");

    NodeParticleSystemCorePtr ShrapnelParticleNodeCore = osg::NodeParticleSystemCore::create();
    beginEditCP(ShrapnelParticleNodeCore, NodeParticleSystemCore::SystemFieldMask | NodeParticleSystemCore::PrototypeNodeFieldMask);
		ShrapnelParticleNodeCore->setSystem(ShrapnelParticleSystem);
		ShrapnelParticleNodeCore->setPrototypeNode(ShrapnelParticlePrototypeNode);
    endEditCP(ShrapnelParticleNodeCore, NodeParticleSystemCore::SystemFieldMask | NodeParticleSystemCore::PrototypeNodeFieldMask);
			
			//Attach the function objects to the Generator
	ShrapnelPositionDistribution = createShrapnelPositionDistribution();
	beginEditCP(ShrapnelBurstGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask);
		ShrapnelBurstGenerator->setPositionFunction(ShrapnelPositionDistribution);
		ShrapnelBurstGenerator->setLifespanFunction(createLifespanDistribution());
		ShrapnelBurstGenerator->setBurstAmount(50.0);
		ShrapnelBurstGenerator->setVelocityFunction(createShrapnelVelocityDistribution());
		ShrapnelBurstGenerator->setAccelerationFunction(createShrapnelAccelerationDistribution());
	endEditCP(ShrapnelBurstGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask);

	NodePtr ShrapnelParticleNode = osg::Node::create();
    beginEditCP(ShrapnelParticleNode, Node::CoreFieldMask);
        ShrapnelParticleNode->setCore(ShrapnelParticleNodeCore);
    endEditCP(ShrapnelParticleNode, Node::CoreFieldMask);
		//end/////////////////////

		//fireball
	FireballGenerator = osg::BurstParticleGenerator::create();
	NodePtr FireballParticlePrototypeNode = SceneFileHandler::the().read("Data/bubble.obj");

	NodeParticleSystemCorePtr FireballParticleNodeCore = osg::NodeParticleSystemCore::create();
    beginEditCP(FireballParticleNodeCore, NodeParticleSystemCore::SystemFieldMask | NodeParticleSystemCore::PrototypeNodeFieldMask);
		FireballParticleNodeCore->setSystem(FireballParticleSystem);
		FireballParticleNodeCore->setPrototypeNode(FireballParticlePrototypeNode);
	 endEditCP(FireballParticleNodeCore, NodeParticleSystemCore::SystemFieldMask | NodeParticleSystemCore::PrototypeNodeFieldMask);
			//Attach the function objects to the Generator
	FireballPositionDistribution = createFireballPositionDistribution();
	beginEditCP(FireballGenerator, RateParticleGenerator::PositionFunctionFieldMask | RateParticleGenerator::LifespanFunctionFieldMask | RateParticleGenerator::GenerationRateFieldMask);
		FireballGenerator->setPositionFunction(FireballPositionDistribution);
		FireballGenerator->setLifespanFunction(createFireballLifespanDistribution());
		FireballGenerator->setBurstAmount(400.0);
		FireballGenerator->setVelocityFunction(createFireballVelocityDistribution());
		FireballGenerator->setAccelerationFunction(createFireballAccelerationDistribution());
	endEditCP(FireballGenerator, RateParticleGenerator::PositionFunctionFieldMask | RateParticleGenerator::LifespanFunctionFieldMask | RateParticleGenerator::GenerationRateFieldMask);
			//Attach the function objects the Affectors
	FireballAgeSizeParticleAffector = osg::AgeSizeParticleAffector::create();
	beginEditCP(FireballAgeSizeParticleAffector,AgeSizeParticleAffector::AgesFieldMask | AgeSizeParticleAffector::SizesFieldMask);
			//ages
			FireballAgeSizeParticleAffector->getAges().push_back(0.1);
			FireballAgeSizeParticleAffector->getAges().push_back(0.2);
			FireballAgeSizeParticleAffector->getAges().push_back(0.3);
			FireballAgeSizeParticleAffector->getAges().push_back(0.5);
			FireballAgeSizeParticleAffector->getAges().push_back(0.7);
			FireballAgeSizeParticleAffector->getAges().push_back(0.8);
			FireballAgeSizeParticleAffector->getAges().push_back(1.0);

			//sizes
			FireballAgeSizeParticleAffector->getSizes().push_back(Vec3f(2.0,2.0,2.0));
			FireballAgeSizeParticleAffector->getSizes().push_back(Vec3f(2.3,2.3,2.3));
			FireballAgeSizeParticleAffector->getSizes().push_back(Vec3f(2.5,2.5,2.5));
			FireballAgeSizeParticleAffector->getSizes().push_back(Vec3f(3.0,3.0,3.0));
			FireballAgeSizeParticleAffector->getSizes().push_back(Vec3f(4.0,4.0,4.0));
			FireballAgeSizeParticleAffector->getSizes().push_back(Vec3f(5.0,5.0,5.0));
			FireballAgeSizeParticleAffector->getSizes().push_back(Vec3f(6.5,6.5,6.5));
	endEditCP(FireballAgeSizeParticleAffector,AgeSizeParticleAffector::AgesFieldMask | AgeSizeParticleAffector::SizesFieldMask);
   
	NodePtr FireballParticleNode = osg::Node::create();
    beginEditCP(FireballParticleNode, Node::CoreFieldMask);
        FireballParticleNode->setCore(FireballParticleNodeCore);
    endEditCP(FireballParticleNode, Node::CoreFieldMask);
		//end/////////////////////


    // Make Main Scene Node 
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
        scene->addChild(RocketParticleNode);
		scene->addChild(SmokeParticleNode);
		scene->addChild(ShrapnelParticleNode);
		scene->addChild(FireballParticleNode);
		scene->addChild(EnvironmentNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    mgr->setRoot(scene);

	mgr->getNavigator()->set(Pnt3f(0.0,0.0,0.0), Pnt3f(0.0,0.0,-1.0), Vec3f(0.0,1.0,0.0));
	mgr->getNavigator()->setMotionFactor(1.0f);
	mgr->getCamera()->setNear(0.1f);
	mgr->getCamera()->setFar(1000.0f);


    while(!ExitApp)
    {
        TutorialWindowEventProducer->update();
        TutorialWindowEventProducer->draw();
    }
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
    //Cylinder Distribution
    CylinderDistribution3DPtr TheCylinderDistribution = CylinderDistribution3D::create();
    beginEditCP(TheCylinderDistribution);
      TheCylinderDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
      TheCylinderDistribution->setInnerRadius(30.0);
      TheCylinderDistribution->setOuterRadius(100.0);
      TheCylinderDistribution->setMinTheta(0.0);
      TheCylinderDistribution->setMaxTheta(6.283185);
      TheCylinderDistribution->setHeight(400.0);
      TheCylinderDistribution->setNormal(Vec3f(0.0,0.0,1.0));
      TheCylinderDistribution->setSurfaceOrVolume(CylinderDistribution3D::SURFACE);
    endEditCP(TheCylinderDistribution);

    return TheCylinderDistribution;
}


FunctionPtr createLifespanDistribution(void)
{
    GaussianNormalDistribution1DPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    beginEditCP(TheLifespanDistribution);
      TheLifespanDistribution->setMean(100.0f);
      TheLifespanDistribution->setStandardDeviation(2.0);
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
FunctionPtr createSmokePositionDistribution(void)
{
     //Disc Distribution
    DiscDistribution3DPtr TheDiscDistribution = DiscDistribution3D::create();
    beginEditCP(TheDiscDistribution);
      TheDiscDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
      TheDiscDistribution->setInnerRadius(01.0);
      TheDiscDistribution->setOuterRadius(02.0);
      TheDiscDistribution->setMinTheta(0.0);
      TheDiscDistribution->setMaxTheta(6.283185307);
      TheDiscDistribution->setNormal(Vec3f(0.0,0.0,1.0));
      TheDiscDistribution->setSurfaceOrEdge(DiscDistribution3D::SURFACE);
    endEditCP(TheDiscDistribution);


    return TheDiscDistribution;
}

FunctionPtr createSmokeLifespanDistribution(void)
{
    GaussianNormalDistribution1DPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    beginEditCP(TheLifespanDistribution);
      TheLifespanDistribution->setMean(5.0f);
      TheLifespanDistribution->setStandardDeviation(0.5);
    endEditCP(TheLifespanDistribution);
	
	return TheLifespanDistribution;
}

FunctionPtr createSmokeVelocityDistribution(void)
{
	 //Sphere Distribution
    LineDistribution3DPtr TheLineDistribution = LineDistribution3D::create();
    beginEditCP(TheLineDistribution);
 		TheLineDistribution->setPoint1(Pnt3f(0.0,1.0,1.0));
		TheLineDistribution->setPoint2(Pnt3f(0.0,1.0,3.0));
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
FunctionPtr createShrapnelPositionDistribution(void)
{
    //Sphere Distribution
    SphereDistribution3DPtr TheSphereDistribution = SphereDistribution3D::create();
    beginEditCP(TheSphereDistribution);
      TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
      TheSphereDistribution->setInnerRadius(0.0);
      TheSphereDistribution->setOuterRadius(3.0);
      TheSphereDistribution->setMinTheta(0.0);
      TheSphereDistribution->setMaxTheta(6.283185);
      TheSphereDistribution->setMinZ(-1.0);
      TheSphereDistribution->setMaxZ(1.0);
	  TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::SURFACE);
    endEditCP(TheSphereDistribution);

    return TheSphereDistribution;
}
FunctionPtr createShrapnelAccelerationDistribution(void)
{

	 //Sphere Distribution
    LineDistribution3DPtr TheLineDistribution = LineDistribution3D::create();
    beginEditCP(TheLineDistribution);
      TheLineDistribution->setPoint1(Pnt3f(0.0,0.0,-3.0));
	  TheLineDistribution->setPoint2(Pnt3f(0.0,0.0,-3.0));
    endEditCP(TheLineDistribution);

	DataConverterPtr TheVec3fConverter = DataConverter::create();
	beginEditCP(TheVec3fConverter);
		TheVec3fConverter->setToType(&FieldDataTraits<Vec3f>::getType());
	endEditCP(TheVec3fConverter);

	CompoundFunctionPtr TheAccelerationDistribution = CompoundFunction::create();
	beginEditCP(TheAccelerationDistribution);
		TheAccelerationDistribution->getFunctions().push_back(TheLineDistribution);
		TheAccelerationDistribution->getFunctions().push_back(TheVec3fConverter);
	endEditCP(TheAccelerationDistribution);

    return TheAccelerationDistribution;
} 
FunctionPtr createShrapnelVelocityDistribution(void)
{
   

	 //Sphere Distribution
    SphereDistribution3DPtr TheSphereDistribution = SphereDistribution3D::create();
    beginEditCP(TheSphereDistribution);
      TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
      TheSphereDistribution->setInnerRadius(3.0);
      TheSphereDistribution->setOuterRadius(10.0);
      TheSphereDistribution->setMinTheta(-3.141950);
      TheSphereDistribution->setMaxTheta(3.141950);
      TheSphereDistribution->setMinZ(-1.0);
      TheSphereDistribution->setMaxZ(1.0);
	  TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::VOLUME);
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

FunctionPtr createFireballVelocityDistribution(void)
{
	 //Sphere Distribution
    SphereDistribution3DPtr TheSphereDistribution = SphereDistribution3D::create();
    beginEditCP(TheSphereDistribution);
      TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
      TheSphereDistribution->setInnerRadius(3.0);
      TheSphereDistribution->setOuterRadius(5.0);
      TheSphereDistribution->setMinTheta(-3.141950);
      TheSphereDistribution->setMaxTheta(3.141950);
      TheSphereDistribution->setMinZ(-1.0);
      TheSphereDistribution->setMaxZ(1.0);
	  TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::VOLUME);
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
FunctionPtr createFireballPositionDistribution(void)
{
     //Sphere Distribution
    SphereDistribution3DPtr TheSphereDistribution = SphereDistribution3D::create();
    beginEditCP(TheSphereDistribution);
      TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
      TheSphereDistribution->setInnerRadius(1.0);
      TheSphereDistribution->setOuterRadius(2.0);
      TheSphereDistribution->setMinTheta(0.0);
      TheSphereDistribution->setMaxTheta(6.283185);
      TheSphereDistribution->setMinZ(-1.0);
      TheSphereDistribution->setMaxZ(1.0);
	  TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::SURFACE);
    endEditCP(TheSphereDistribution);

    return TheSphereDistribution;
}

FunctionPtr createFireballAccelerationDistribution(void)
{

	 //Sphere Distribution
    LineDistribution3DPtr TheLineDistribution = LineDistribution3D::create();
    beginEditCP(TheLineDistribution);
      TheLineDistribution->setPoint1(Pnt3f(0.0,0.0,1.0));
	  TheLineDistribution->setPoint2(Pnt3f(0.0,0.0,1.0));
    endEditCP(TheLineDistribution);

	DataConverterPtr TheVec3fConverter = DataConverter::create();
	beginEditCP(TheVec3fConverter);
		TheVec3fConverter->setToType(&FieldDataTraits<Vec3f>::getType());
	endEditCP(TheVec3fConverter);

	CompoundFunctionPtr TheAccelerationDistribution = CompoundFunction::create();
	beginEditCP(TheAccelerationDistribution);
		TheAccelerationDistribution->getFunctions().push_back(TheLineDistribution);
		TheAccelerationDistribution->getFunctions().push_back(TheVec3fConverter);
	endEditCP(TheAccelerationDistribution);

    return TheAccelerationDistribution;
} 
FunctionPtr createFireballLifespanDistribution(void)
{
    GaussianNormalDistribution1DPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    beginEditCP(TheLifespanDistribution);
      TheLifespanDistribution->setMean(3.0f);
      TheLifespanDistribution->setStandardDeviation(0.5);
    endEditCP(TheLifespanDistribution);
	
	return TheLifespanDistribution;
}
