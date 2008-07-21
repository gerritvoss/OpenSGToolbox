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
#include <OpenSG/Input/OSGWindowAdapter.h>

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
PointParticleSystemDrawerPtr ExampleRocketParticleSystemDrawer;
QuadParticleSystemDrawerPtr CircleParticleSystemDrawer;
QuadParticleSystemDrawerPtr StarParticleSystemDrawer;


ParticleSystemPtr RocketParticleSystem;
ParticleSystemPtr CircleParticleSystem;
ParticleSystemPtr StarParticleSystem;



BurstParticleGeneratorPtr CircleBurstGenerator;
BurstParticleGeneratorPtr StarBurstGenerator;


AgeFadeParticleAffectorPtr CircleAgeFadeParticleAffector;
AgeSizeParticleAffectorPtr CircleAgeSizeParticleAffector;
AgeFadeParticleAffectorPtr StarAgeFadeParticleAffector;
AgeSizeParticleAffectorPtr StarAgeSizeParticleAffector;

ParticleSystemCorePtr PointParticleNodeCore;

FunctionPtr CirclePositionDistribution;
FunctionPtr StarPositionDistribution;

FunctionPtr createPositionDistribution(void);
FunctionPtr createLifespanDistribution(void);
FunctionPtr createSmokeVelocityDistribution(void);
FunctionPtr createSmokeLifespanDistribution(void);
FunctionPtr createSmokePositionDistribution(void);
FunctionPtr createStarVelocityDistribution(void);
FunctionPtr createStarLifespanDistribution(void);
FunctionPtr createStarPositionDistribution(void);






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
			Vec3f(0.0,0.0f,1.0f),
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
    

	beginEditCP(CirclePositionDistribution);
		SphereDistribution3D::Ptr::dcast(CirclePositionDistribution)->setCenter(e.getPosition());
    endEditCP(CirclePositionDistribution);

	beginEditCP(StarPositionDistribution);
		SphereDistribution3D::Ptr::dcast(CirclePositionDistribution)->setCenter(e.getPosition());
    endEditCP(StarPositionDistribution);
	
	   {

		
		//Attach the Affector to the Smoke Particle System
				beginEditCP(CircleParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
					CircleParticleSystem->getGenerators().push_back(CircleBurstGenerator);
					CircleParticleSystem->getAffectors().push_back(CircleAgeFadeParticleAffector);
					CircleParticleSystem->getAffectors().push_back(CircleAgeSizeParticleAffector);
				endEditCP(CircleParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
		
	   }
	   std::cout << "Rocket Died at: " << e.getPosition() << std::endl;
   }
   virtual void particleStolen(const ParticleEvent& e)
   {
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
                                        "OpenSG 21Fireworks Window");
										

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

		//circle material
	TextureChunkPtr CircleQuadTextureChunk = TextureChunk::create();
    ImagePtr LoadedImage = ImageFileHandler::the().read("Data/fireworkscircle.png");    
    beginEditCP(CircleQuadTextureChunk, TextureChunk::ImageFieldMask);
        CircleQuadTextureChunk->setImage(LoadedImage);
        CircleQuadTextureChunk->setEnvMode(GL_MODULATE);
    endEditCP(CircleQuadTextureChunk, TextureChunk::ImageFieldMask);

	MaterialChunkPtr PSCircleMaterialChunk = MaterialChunk::create();
	beginEditCP(PSCircleMaterialChunk);
		PSCircleMaterialChunk->setAmbient(Color4f(0.3f,0.3f,0.3f,1.0f));
		PSCircleMaterialChunk->setDiffuse(Color4f(0.7f,0.7f,0.7f,1.0f));
		PSCircleMaterialChunk->setSpecular(Color4f(0.9f,0.9f,0.9f,1.0f));
		PSCircleMaterialChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);
	endEditCP(PSCircleMaterialChunk);

	ChunkMaterialPtr PSCircleMaterial = ChunkMaterial::create();
	beginEditCP(PSCircleMaterial, ChunkMaterial::ChunksFieldMask);
		PSCircleMaterial->addChunk(CircleQuadTextureChunk);
		PSCircleMaterial->addChunk(PSCircleMaterialChunk);
		PSCircleMaterial->addChunk(PSBlendChunk);
	endEditCP(PSCircleMaterial, ChunkMaterial::ChunksFieldMask);
		
		//star material
	TextureChunkPtr StarQuadTextureChunk = TextureChunk::create();
    ImagePtr LoadedImage1 = ImageFileHandler::the().read("Data/fireworkstar.png");    
    beginEditCP(StarQuadTextureChunk, TextureChunk::ImageFieldMask);
        StarQuadTextureChunk->setImage(LoadedImage1);
        StarQuadTextureChunk->setEnvMode(GL_MODULATE);
    endEditCP(StarQuadTextureChunk, TextureChunk::ImageFieldMask);

	MaterialChunkPtr PSStarMaterialChunk = MaterialChunk::create();
	beginEditCP(PSStarMaterialChunk);
		PSStarMaterialChunk->setAmbient(Color4f(0.3f,0.3f,0.3f,1.0f));
		PSStarMaterialChunk->setDiffuse(Color4f(0.7f,0.7f,0.7f,1.0f));
		PSStarMaterialChunk->setSpecular(Color4f(0.9f,0.9f,0.9f,1.0f));
		PSStarMaterialChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);
	endEditCP(PSStarMaterialChunk);

	ChunkMaterialPtr PSStarMaterial = ChunkMaterial::create();
	beginEditCP(PSStarMaterial, ChunkMaterial::ChunksFieldMask);
		PSStarMaterial->addChunk(StarQuadTextureChunk);
		PSStarMaterial->addChunk(PSStarMaterialChunk);
		PSStarMaterial->addChunk(PSBlendChunk);
	endEditCP(PSStarMaterial, ChunkMaterial::ChunksFieldMask);


	//Particle System
		//Rocket
    RocketParticleSystem = osg::ParticleSystem::create();
	RocketParticleSystem->attachUpdateListener(TutorialWindowEventProducer);

	TutorialRocketParticleSystemListener TheRocketListener;
	RocketParticleSystem->addParticleSystemListener(&TheRocketListener);

		//Circle
	CircleParticleSystem = osg::ParticleSystem::create();
	CircleParticleSystem->attachUpdateListener(TutorialWindowEventProducer);

		//Star
	StarParticleSystem = osg::ParticleSystem::create();
	StarParticleSystem->attachUpdateListener(TutorialWindowEventProducer);
		


	//Particle System Drawer
		//Rocket does not have a drawer because it is being attached to a special node core
		
		//Circle
	CircleParticleSystemDrawer = osg::QuadParticleSystemDrawer::create();
	//CircleParticleSystemDrawer->setQuadSizeScaling(Vec2f(0.5f,0.5f));
		
		//Star
	StarParticleSystemDrawer = osg::QuadParticleSystemDrawer::create();
		
	
		
	
	//Particle System Node
	
		//NodePtr ParticlePrototypeNode = makeTorus(1.0,4.0,16,16);
	NodePtr RocketParticlePrototypeNode = SceneFileHandler::the().read("Data/rocket.obj");
	
    NodeParticleSystemCorePtr RocketParticleNodeCore = osg::NodeParticleSystemCore::create();
    beginEditCP(RocketParticleNodeCore, NodeParticleSystemCore::SystemFieldMask | NodeParticleSystemCore::PrototypeNodeFieldMask);
		RocketParticleNodeCore->setSystem(RocketParticleSystem);
		RocketParticleNodeCore->setPrototypeNode(RocketParticlePrototypeNode);
        RocketParticleNodeCore->setNormalSource(NodeParticleSystemCore::NORMAL_VELOCITY);
        RocketParticleNodeCore->setUpSource(NodeParticleSystemCore::UP_STATIC);
        RocketParticleNodeCore->setUp(Vec3f(0.0f,1.0f,0.0f));
    endEditCP(RocketParticleNodeCore, NodeParticleSystemCore::SystemFieldMask | NodeParticleSystemCore::PrototypeNodeFieldMask);
	
	NodePtr RocketParticleNode = osg::Node::create();
    beginEditCP(RocketParticleNode, Node::CoreFieldMask);
        RocketParticleNode->setCore(RocketParticleNodeCore);
    endEditCP(RocketParticleNode, Node::CoreFieldMask);

	DistanceKillParticleAffectorPtr RocketDistanceKillParticleAffector = osg::DistanceKillParticleAffector::create();
	beginEditCP(RocketDistanceKillParticleAffector, DistanceKillParticleAffector::KillDistanceFieldMask | DistanceKillParticleAffector::ParticleSystemNodeFieldMask | DistanceKillParticleAffector::DistanceFromSourceFieldMask |	DistanceKillParticleAffector::DistanceFromCameraFieldMask);
		RocketDistanceKillParticleAffector->setKillDistance(100.0f);
		RocketDistanceKillParticleAffector->setParticleSystemNode(RocketParticleNode);
		RocketDistanceKillParticleAffector->setDistanceFromSource(DistanceKillParticleAffector::DISTANCE_FROM_CAMERA);
		RocketDistanceKillParticleAffector->setDistanceFromCamera(mgr->getCamera());
	endEditCP(RocketDistanceKillParticleAffector, DistanceKillParticleAffector::KillDistanceFieldMask | DistanceKillParticleAffector::ParticleSystemNodeFieldMask | DistanceKillParticleAffector::DistanceFromSourceFieldMask |	DistanceKillParticleAffector::DistanceFromCameraFieldMask);
	//Attach the Affector to the Rocket Particle System
	beginEditCP(RocketParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
		RocketParticleSystem->getAffectors().push_back(RocketDistanceKillParticleAffector);
	endEditCP(RocketParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);

		
		//Circle
	CircleBurstGenerator = osg::BurstParticleGenerator::create();
			//Attach the function objects to the Generator
	CirclePositionDistribution = createSmokePositionDistribution();
	beginEditCP(CircleBurstGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask);
		CircleBurstGenerator->setPositionFunction(CirclePositionDistribution);
		CircleBurstGenerator->setLifespanFunction(createSmokeLifespanDistribution());
		CircleBurstGenerator->setBurstAmount(50.0);
		CircleBurstGenerator->setVelocityFunction(createSmokeVelocityDistribution());
		//CircleBurstGenerator->setAccelerationFunction(createShrapnelAccelerationDistribution());
	endEditCP(CircleBurstGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask);

	//Attach the function objects the Affectors
	CircleAgeFadeParticleAffector = osg::AgeFadeParticleAffector::create();
	beginEditCP(CircleAgeFadeParticleAffector, AgeFadeParticleAffector::FadeInTimeFieldMask | AgeFadeParticleAffector::FadeOutTimeFieldMask | AgeFadeParticleAffector::StartAlphaFieldMask| AgeFadeParticleAffector::FadeToAlphaFieldMask | AgeFadeParticleAffector::EndAlphaFieldMask);
		CircleAgeFadeParticleAffector->setFadeInTime(3.0f);
		CircleAgeFadeParticleAffector->setFadeOutTime(5.0f);
		CircleAgeFadeParticleAffector->setStartAlpha(0.0f);
		CircleAgeFadeParticleAffector->setFadeToAlpha(1.0f);
		CircleAgeFadeParticleAffector->setEndAlpha(0.0f);	
	endEditCP(CircleAgeFadeParticleAffector, AgeFadeParticleAffector::FadeInTimeFieldMask | AgeFadeParticleAffector::FadeOutTimeFieldMask | AgeFadeParticleAffector::StartAlphaFieldMask| AgeFadeParticleAffector::FadeToAlphaFieldMask | AgeFadeParticleAffector::EndAlphaFieldMask);

	CircleAgeSizeParticleAffector = osg::AgeSizeParticleAffector::create();
	beginEditCP(CircleAgeSizeParticleAffector,AgeSizeParticleAffector::AgesFieldMask | AgeSizeParticleAffector::SizesFieldMask);
			//ages
			CircleAgeSizeParticleAffector->getAges().push_back(0.1);
			CircleAgeSizeParticleAffector->getAges().push_back(0.2);
			CircleAgeSizeParticleAffector->getAges().push_back(0.3);
			CircleAgeSizeParticleAffector->getAges().push_back(0.4);
			CircleAgeSizeParticleAffector->getAges().push_back(0.5);
			CircleAgeSizeParticleAffector->getAges().push_back(0.6);
			CircleAgeSizeParticleAffector->getAges().push_back(0.7);
			CircleAgeSizeParticleAffector->getAges().push_back(0.8);
			CircleAgeSizeParticleAffector->getAges().push_back(1.0);

			//sizes
			CircleAgeSizeParticleAffector->getSizes().push_back(Vec3f(0.5,0.5,0.5));
			CircleAgeSizeParticleAffector->getSizes().push_back(Vec3f(1.0,1.0,1.0));
			CircleAgeSizeParticleAffector->getSizes().push_back(Vec3f(2.0,2.0,2.0));
			CircleAgeSizeParticleAffector->getSizes().push_back(Vec3f(2.5,2.5,2.5));
			CircleAgeSizeParticleAffector->getSizes().push_back(Vec3f(3.0,3.0,3.0));
			CircleAgeSizeParticleAffector->getSizes().push_back(Vec3f(3.5,3.5,3.5));
			CircleAgeSizeParticleAffector->getSizes().push_back(Vec3f(4.0,4.0,4.0));
			CircleAgeSizeParticleAffector->getSizes().push_back(Vec3f(5.0,5.0,5.0));
			CircleAgeSizeParticleAffector->getSizes().push_back(Vec3f(6.5,6.5,6.5));
	endEditCP(CircleAgeSizeParticleAffector,AgeSizeParticleAffector::AgesFieldMask | AgeSizeParticleAffector::SizesFieldMask);
   
	ParticleSystemCorePtr CircleParticleNodeCore = osg::ParticleSystemCore::create();
    beginEditCP(CircleParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
		CircleParticleNodeCore->setSystem(CircleParticleSystem);
		CircleParticleNodeCore->setDrawer(CircleParticleSystemDrawer);
		CircleParticleNodeCore->setMaterial(PSCircleMaterial);
    endEditCP(CircleParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
    
	NodePtr CircleParticleNode = osg::Node::create();
    beginEditCP(CircleParticleNode, Node::CoreFieldMask);
        CircleParticleNode->setCore(CircleParticleNodeCore);
    endEditCP(CircleParticleNode, Node::CoreFieldMask);
		//end/////////////////////

		//Star
	StarBurstGenerator = osg::BurstParticleGenerator::create();
			//Attach the function objects to the Generator
	StarPositionDistribution = createStarPositionDistribution();
	beginEditCP(StarBurstGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask);
		StarBurstGenerator->setPositionFunction(StarPositionDistribution);
		StarBurstGenerator->setLifespanFunction(createStarLifespanDistribution());
		StarBurstGenerator->setBurstAmount(50.0);
		StarBurstGenerator->setVelocityFunction(createStarVelocityDistribution());
		//StarBurstGenerator->setAccelerationFunction(createShrapnelAccelerationDistribution());
	endEditCP(StarBurstGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask);

	//Attach the function objects the Affectors
	StarAgeFadeParticleAffector = osg::AgeFadeParticleAffector::create();
	beginEditCP(StarAgeFadeParticleAffector, AgeFadeParticleAffector::FadeInTimeFieldMask | AgeFadeParticleAffector::FadeOutTimeFieldMask | AgeFadeParticleAffector::StartAlphaFieldMask| AgeFadeParticleAffector::FadeToAlphaFieldMask | AgeFadeParticleAffector::EndAlphaFieldMask);
		StarAgeFadeParticleAffector->setFadeInTime(3.0f);
		StarAgeFadeParticleAffector->setFadeOutTime(5.0f);
		StarAgeFadeParticleAffector->setStartAlpha(0.0f);
		StarAgeFadeParticleAffector->setFadeToAlpha(1.0f);
		StarAgeFadeParticleAffector->setEndAlpha(0.0f);	
	endEditCP(StarAgeFadeParticleAffector, AgeFadeParticleAffector::FadeInTimeFieldMask | AgeFadeParticleAffector::FadeOutTimeFieldMask | AgeFadeParticleAffector::StartAlphaFieldMask| AgeFadeParticleAffector::FadeToAlphaFieldMask | AgeFadeParticleAffector::EndAlphaFieldMask);

	StarAgeSizeParticleAffector = osg::AgeSizeParticleAffector::create();
	beginEditCP(StarAgeSizeParticleAffector,AgeSizeParticleAffector::AgesFieldMask | AgeSizeParticleAffector::SizesFieldMask);
			//ages
			StarAgeSizeParticleAffector->getAges().push_back(0.1);
			StarAgeSizeParticleAffector->getAges().push_back(0.2);
			StarAgeSizeParticleAffector->getAges().push_back(0.3);
			StarAgeSizeParticleAffector->getAges().push_back(0.4);
			StarAgeSizeParticleAffector->getAges().push_back(0.5);
			StarAgeSizeParticleAffector->getAges().push_back(0.6);
			StarAgeSizeParticleAffector->getAges().push_back(0.7);
			StarAgeSizeParticleAffector->getAges().push_back(0.8);
			StarAgeSizeParticleAffector->getAges().push_back(1.0);

			//sizes
			StarAgeSizeParticleAffector->getSizes().push_back(Vec3f(0.5,0.5,0.5));
			StarAgeSizeParticleAffector->getSizes().push_back(Vec3f(1.0,1.0,1.0));
			StarAgeSizeParticleAffector->getSizes().push_back(Vec3f(2.0,2.0,2.0));
			StarAgeSizeParticleAffector->getSizes().push_back(Vec3f(2.5,2.5,2.5));
			StarAgeSizeParticleAffector->getSizes().push_back(Vec3f(3.0,3.0,3.0));
			StarAgeSizeParticleAffector->getSizes().push_back(Vec3f(3.5,3.5,3.5));
			StarAgeSizeParticleAffector->getSizes().push_back(Vec3f(4.0,4.0,4.0));
			StarAgeSizeParticleAffector->getSizes().push_back(Vec3f(5.0,5.0,5.0));
			StarAgeSizeParticleAffector->getSizes().push_back(Vec3f(6.5,6.5,6.5));
	endEditCP(StarAgeSizeParticleAffector,AgeSizeParticleAffector::AgesFieldMask | AgeSizeParticleAffector::SizesFieldMask);
   
	ParticleSystemCorePtr StarParticleNodeCore = osg::ParticleSystemCore::create();
    beginEditCP(StarParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
		StarParticleNodeCore->setSystem(StarParticleSystem);
		StarParticleNodeCore->setDrawer(StarParticleSystemDrawer);
		StarParticleNodeCore->setMaterial(PSStarMaterial);
    endEditCP(StarParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
    
	NodePtr StarParticleNode = osg::Node::create();
    beginEditCP(StarParticleNode, Node::CoreFieldMask);
        StarParticleNode->setCore(StarParticleNodeCore);
    endEditCP(StarParticleNode, Node::CoreFieldMask);
		//end/////////////////////
	

    // Make Main Scene Node 
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
        scene->addChild(RocketParticleNode);
		//scene->addChild(CircleParticleNode);
		scene->addChild(StarParticleNode);
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
FunctionPtr createSmokePositionDistribution(void)
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

FunctionPtr createStarPositionDistribution(void)
{
    //Sphere Distribution
    SphereDistribution3DPtr TheSphereDistribution = SphereDistribution3D::create();
    beginEditCP(TheSphereDistribution);
      TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
      TheSphereDistribution->setInnerRadius(0.0);
      TheSphereDistribution->setOuterRadius(4.0);
      TheSphereDistribution->setMinTheta(0.0);
      TheSphereDistribution->setMaxTheta(6.283185);
      TheSphereDistribution->setMinZ(-1.0);
      TheSphereDistribution->setMaxZ(1.0);
	  TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::SURFACE);
    endEditCP(TheSphereDistribution);

    return TheSphereDistribution;
}

FunctionPtr createStarLifespanDistribution(void)
{
    GaussianNormalDistribution1DPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    beginEditCP(TheLifespanDistribution);
      TheLifespanDistribution->setMean(7.0f);
      TheLifespanDistribution->setStandardDeviation(0.5);
    endEditCP(TheLifespanDistribution);
	
	return TheLifespanDistribution;
}

FunctionPtr createStarVelocityDistribution(void)
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
