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
QuadParticleSystemDrawerPtr RocketParticleSystemDrawer;
QuadParticleSystemDrawerPtr CircleParticleSystemDrawer;
QuadParticleSystemDrawerPtr StarParticleSystemDrawer;
QuadParticleSystemDrawerPtr ComStarParticleSystemDrawer;
QuadParticleSystemDrawerPtr ExplosionParticleSystemDrawer;
QuadParticleSystemDrawerPtr Explosion2ParticleSystemDrawer;

QuadParticleSystemDrawerPtr Circle2ParticleSystemDrawer;
QuadParticleSystemDrawerPtr Star2ParticleSystemDrawer;
QuadParticleSystemDrawerPtr ComStar2ParticleSystemDrawer;


ParticleSystemPtr RocketParticleSystem;
ParticleSystemPtr CircleParticleSystem;
ParticleSystemPtr StarParticleSystem;
ParticleSystemPtr ComStarParticleSystem;
ParticleSystemPtr ExplosionParticleSystem;
ParticleSystemPtr Explosion2ParticleSystem;

ParticleSystemPtr Circle2ParticleSystem;
ParticleSystemPtr Star2ParticleSystem;
ParticleSystemPtr ComStar2ParticleSystem;



BurstParticleGeneratorPtr RocketBurstGenerator;
BurstParticleGeneratorPtr CircleBurstGenerator;
BurstParticleGeneratorPtr StarBurstGenerator;
BurstParticleGeneratorPtr ComStarBurstGenerator;
BurstParticleGeneratorPtr ExplosionBurstGenerator;
BurstParticleGeneratorPtr Explosion2BurstGenerator;

BurstParticleGeneratorPtr Circle2BurstGenerator;
BurstParticleGeneratorPtr Star2BurstGenerator;
BurstParticleGeneratorPtr ComStar2BurstGenerator;


AgeFadeParticleAffectorPtr CircleAgeFadeParticleAffector;
AgeSizeParticleAffectorPtr CircleAgeSizeParticleAffector;
AgeFadeParticleAffectorPtr StarAgeFadeParticleAffector;
AgeSizeParticleAffectorPtr StarAgeSizeParticleAffector;
AgeFadeParticleAffectorPtr ComStarAgeFadeParticleAffector;
AgeSizeParticleAffectorPtr ComStarAgeSizeParticleAffector;
AgeFadeParticleAffectorPtr ExplosionAgeFadeParticleAffector;
AgeSizeParticleAffectorPtr ExplosionAgeSizeParticleAffector;
AgeFadeParticleAffectorPtr Explosion2AgeFadeParticleAffector;
AgeSizeParticleAffectorPtr Explosion2AgeSizeParticleAffector;
CollectiveGravityParticleSystemAffectorPtr StarCollectiveGravityParticleSystemAffector;


AgeFadeParticleAffectorPtr Circle2AgeFadeParticleAffector;
AgeSizeParticleAffectorPtr Circle2AgeSizeParticleAffector;
AgeFadeParticleAffectorPtr Star2AgeFadeParticleAffector;
AgeSizeParticleAffectorPtr Star2AgeSizeParticleAffector;
AgeFadeParticleAffectorPtr ComStar2AgeFadeParticleAffector;
AgeSizeParticleAffectorPtr ComStar2AgeSizeParticleAffector;


ParticleSystemCorePtr PointParticleNodeCore;

FunctionPtr CirclePositionDistribution;
FunctionPtr StarPositionDistribution;
FunctionPtr ComStarPositionDistribution;
FunctionPtr ExplosionPositionDistribution;
FunctionPtr Explosion2PositionDistribution;

FunctionPtr Circle2PositionDistribution;
FunctionPtr Star2PositionDistribution;
FunctionPtr ComStar2PositionDistribution;

FunctionPtr createPositionDistribution(void);
FunctionPtr createLifespanDistribution(void);
FunctionPtr createSmokeVelocityDistribution(void);
FunctionPtr createSmokeLifespanDistribution(void);
FunctionPtr createSmokePositionDistribution(void);
FunctionPtr createSmokeColorDistribution(void);
FunctionPtr createStarVelocityDistribution(void);
FunctionPtr createStarLifespanDistribution(void);
FunctionPtr createStarPositionDistribution(void);
FunctionPtr createComStarVelocityDistribution(void);
FunctionPtr createComStarLifespanDistribution(void);
FunctionPtr createComStarPositionDistribution(void);
FunctionPtr createComStarColorDistribution(void);

FunctionPtr createComStar2VelocityDistribution(void);
FunctionPtr createComStar2PositionDistribution(void);
FunctionPtr createSmoke2PositionDistribution(void);
FunctionPtr createSmoke2VelocityDistribution(void);
FunctionPtr createStar2VelocityDistribution(void);
FunctionPtr createStar2PositionDistribution(void);
FunctionPtr createExplosionPositionDistribution(void);
FunctionPtr createExplosionVelocityDistribution(void);
FunctionPtr createExplosion2PositionDistribution(void);
FunctionPtr createExplosion2VelocityDistribution(void);
FunctionPtr createExplosion2ColorDistribution(void);


UInt32 CheckSystem = 1;

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

	   switch(e.getKey())
	   {
	   case KeyEvent::KEY_1:
		   CheckSystem = 1;
		   break;
	   case KeyEvent::KEY_2:
		   CheckSystem = 2;
		   break;
	   case KeyEvent::KEY_3:
		   CheckSystem = 3;
		   break;
	   case KeyEvent::KEY_4:
	   CheckSystem = 4;
	   break;
	   }
   }

   virtual void keyReleased(const KeyEvent& e)
   {
   }

   virtual void keyTyped(const KeyEvent& e)
   {
	  

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
    

	
	
	  if(CheckSystem == 1)
	  {

		 beginEditCP(CirclePositionDistribution);
			SphereDistribution3D::Ptr::dcast(CirclePositionDistribution)->setCenter(e.getPosition());
		endEditCP(CirclePositionDistribution);

		beginEditCP(StarPositionDistribution);
			SphereDistribution3D::Ptr::dcast(StarPositionDistribution)->setCenter(e.getPosition());
		endEditCP(StarPositionDistribution);

		beginEditCP(ComStarPositionDistribution);
			SphereDistribution3D::Ptr::dcast(ComStarPositionDistribution)->setCenter(e.getPosition());
		endEditCP(ComStarPositionDistribution);

		//Attach the Affector to the Circle Particle System
				beginEditCP(CircleParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
					CircleParticleSystem->getGenerators().push_back(CircleBurstGenerator);
				endEditCP(CircleParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
		//Attach the Affector to the Star Particle System
				beginEditCP(StarParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask | ParticleSystem::SystemAffectorsFieldMask);
					StarParticleSystem->getGenerators().push_back(StarBurstGenerator);
				endEditCP(StarParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask | ParticleSystem::SystemAffectorsFieldMask);
		//Attach the Affector to the ComStar Particle System
				beginEditCP(ComStarParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
					ComStarParticleSystem->getGenerators().push_back(ComStarBurstGenerator);
				endEditCP(ComStarParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
	   }

	  if(CheckSystem == 2)
	  {
		beginEditCP(Circle2PositionDistribution);
			SphereDistribution3D::Ptr::dcast(Circle2PositionDistribution)->setCenter(e.getPosition());
		endEditCP(Circle2PositionDistribution);

		beginEditCP(Star2PositionDistribution);
			SphereDistribution3D::Ptr::dcast(Star2PositionDistribution)->setCenter(e.getPosition());
		endEditCP(Star2PositionDistribution);

		beginEditCP(ComStar2PositionDistribution);
			SphereDistribution3D::Ptr::dcast(ComStar2PositionDistribution)->setCenter(e.getPosition());
		endEditCP(ComStar2PositionDistribution);

		   //Attach the Affector to the Circle2 Particle System
				beginEditCP(Circle2ParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
					Circle2ParticleSystem->getGenerators().push_back(Circle2BurstGenerator);
				endEditCP(Circle2ParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
		//Attach the Affector to the Star2 Particle System
				beginEditCP(Star2ParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask | ParticleSystem::SystemAffectorsFieldMask);
					Star2ParticleSystem->getGenerators().push_back(Star2BurstGenerator);
				endEditCP(Star2ParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask | ParticleSystem::SystemAffectorsFieldMask);
		//Attach the Affector to the ComStar2 Particle System
				beginEditCP(ComStar2ParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
					ComStar2ParticleSystem->getGenerators().push_back(ComStar2BurstGenerator);
				endEditCP(ComStar2ParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
		
	  }
	   if(CheckSystem == 3)
	  {
		beginEditCP(ExplosionPositionDistribution);
			SphereDistribution3D::Ptr::dcast(ExplosionPositionDistribution)->setCenter(e.getPosition());
		endEditCP(ExplosionPositionDistribution);	

		//Attach the Affector to the explosion Particle System
				beginEditCP(ExplosionParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
					ExplosionParticleSystem->getGenerators().push_back(ExplosionBurstGenerator);
				endEditCP(ExplosionParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
	  }
	  if(CheckSystem == 4)
	  {
		beginEditCP(Explosion2PositionDistribution);
			DiscDistribution3D::Ptr::dcast(Explosion2PositionDistribution)->setCenter(e.getPosition());
		endEditCP(Explosion2PositionDistribution);	

		//Attach the Affector to the explosion Particle System
				beginEditCP(Explosion2ParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
					Explosion2ParticleSystem->getGenerators().push_back(Explosion2BurstGenerator);
				endEditCP(Explosion2ParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
	  
	  }
   }
   virtual void particleStolen(const ParticleEvent& e)
   {
   }
};

class TutorialSecondaryParticleSystemListener : public ParticleSystemListener
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
    

	
	
	   {

		/* beginEditCP(CirclePositionDistribution);
			SphereDistribution3D::Ptr::dcast(CirclePositionDistribution)->setCenter(e.getPosition());
		endEditCP(CirclePositionDistribution);
*/
		/*beginEditCP(StarPositionDistribution);
			SphereDistribution3D::Ptr::dcast(StarPositionDistribution)->setCenter(e.getPosition());
		endEditCP(StarPositionDistribution);
*/
		beginEditCP(ComStarPositionDistribution);
			SphereDistribution3D::Ptr::dcast(ComStarPositionDistribution)->setCenter(e.getPosition());
		endEditCP(ComStarPositionDistribution);

		/*//Attach the Affector to the Circle Particle System
				beginEditCP(CircleParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
					CircleParticleSystem->getGenerators().push_back(CircleBurstGenerator);
				endEditCP(CircleParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
		*///Attach the Affector to the Star Particle System
			/*	beginEditCP(StarParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask | ParticleSystem::SystemAffectorsFieldMask);
					StarParticleSystem->getGenerators().push_back(StarBurstGenerator);
				endEditCP(StarParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask | ParticleSystem::SystemAffectorsFieldMask);
		*///Attach the Affector to the ComStar Particle System
				beginEditCP(ComStarParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
					ComStarParticleSystem->getGenerators().push_back(ComStarBurstGenerator);
				endEditCP(ComStarParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
	   
	   }

	  
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
		PSMaterialChunkChunk->setDiffuse(Color4f(1.0f,1.0f,1.0f,1.0f));
		PSMaterialChunkChunk->setSpecular(Color4f(0.0f,0.0f,0.0f,1.0f));
		PSMaterialChunkChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);
	endEditCP(PSMaterialChunkChunk);

	ChunkMaterialPtr PSPointMaterial = ChunkMaterial::create();
	beginEditCP(PSPointMaterial, ChunkMaterial::ChunksFieldMask);
		PSPointMaterial->addChunk(PSPointChunk);
		PSPointMaterial->addChunk(PSMaterialChunkChunk);
		PSPointMaterial->addChunk(PSBlendChunk);
	endEditCP(PSPointMaterial, ChunkMaterial::ChunksFieldMask);

	//Rocket material
	TextureChunkPtr RocketQuadTextureChunk = TextureChunk::create();
    ImagePtr LoadedImage3 = ImageFileHandler::the().read("Data/fireworkmodel copy1.png");    
    beginEditCP(RocketQuadTextureChunk, TextureChunk::ImageFieldMask);
        RocketQuadTextureChunk->setImage(LoadedImage3);
        RocketQuadTextureChunk->setEnvMode(GL_MODULATE);
    endEditCP(RocketQuadTextureChunk, TextureChunk::ImageFieldMask);

	MaterialChunkPtr PSRocketMaterialChunk = MaterialChunk::create();
	beginEditCP(PSRocketMaterialChunk);
		PSRocketMaterialChunk->setAmbient(Color4f(1.0f,1.0f,1.0f,1.0f));
		PSRocketMaterialChunk->setDiffuse(Color4f(1.0f,1.0f,1.0f,1.0f));
		PSRocketMaterialChunk->setSpecular(Color4f(0.0f,0.0f,0.0f,1.0f));
		PSRocketMaterialChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);
	endEditCP(PSRocketMaterialChunk);

	ChunkMaterialPtr PSRocketMaterial = ChunkMaterial::create();
	beginEditCP(PSRocketMaterial, ChunkMaterial::ChunksFieldMask);
		PSRocketMaterial->addChunk(RocketQuadTextureChunk);
		PSRocketMaterial->addChunk(PSRocketMaterialChunk);
		PSRocketMaterial->addChunk(PSBlendChunk);
	endEditCP(PSRocketMaterial, ChunkMaterial::ChunksFieldMask);
		
		//circle material
	TextureChunkPtr CircleQuadTextureChunk = TextureChunk::create();
    ImagePtr LoadedImage = ImageFileHandler::the().read("Data/fireworkscircle.png");    
    beginEditCP(CircleQuadTextureChunk, TextureChunk::ImageFieldMask);
        CircleQuadTextureChunk->setImage(LoadedImage);
        CircleQuadTextureChunk->setEnvMode(GL_MODULATE);
    endEditCP(CircleQuadTextureChunk, TextureChunk::ImageFieldMask);

	MaterialChunkPtr PSCircleMaterialChunk = MaterialChunk::create();
	beginEditCP(PSCircleMaterialChunk);
		PSCircleMaterialChunk->setAmbient(Color4f(1.0f,1.0f,1.0f,1.0f));
		PSCircleMaterialChunk->setDiffuse(Color4f(1.0f,1.0f,1.0f,1.0f));
		PSCircleMaterialChunk->setSpecular(Color4f(0.0f,0.0f,0.0f,1.0f));
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
		PSStarMaterialChunk->setAmbient(Color4f(1.0f,1.0f,1.0f,1.0f));
		PSStarMaterialChunk->setDiffuse(Color4f(1.0f,1.0f,1.0f,1.0f));
		PSStarMaterialChunk->setSpecular(Color4f(0.0f,0.0f,0.0f,1.0f));
		PSStarMaterialChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);
	endEditCP(PSStarMaterialChunk);

	ChunkMaterialPtr PSStarMaterial = ChunkMaterial::create();
	beginEditCP(PSStarMaterial, ChunkMaterial::ChunksFieldMask);
		PSStarMaterial->addChunk(StarQuadTextureChunk);
		PSStarMaterial->addChunk(PSStarMaterialChunk);
		PSStarMaterial->addChunk(PSBlendChunk);
	endEditCP(PSStarMaterial, ChunkMaterial::ChunksFieldMask);

		//ComStar material
	BlendChunkPtr ComStarBlendChunk = BlendChunk::create();
	ComStarBlendChunk->setSrcFactor(GL_SRC_ALPHA);
	ComStarBlendChunk->setDestFactor(GL_ONE);

	TextureChunkPtr ComStarQuadTextureChunk = TextureChunk::create();
    ImagePtr LoadedImage2 = ImageFileHandler::the().read("Data/fireworkcomstar.png");    
    beginEditCP(ComStarQuadTextureChunk, TextureChunk::ImageFieldMask);
        ComStarQuadTextureChunk->setImage(LoadedImage2);
        ComStarQuadTextureChunk->setEnvMode(GL_MODULATE);
    endEditCP(ComStarQuadTextureChunk, TextureChunk::ImageFieldMask);

	MaterialChunkPtr PSComStarMaterialChunk = MaterialChunk::create();
	beginEditCP(PSComStarMaterialChunk);
		PSComStarMaterialChunk->setAmbient(Color4f(1.0f,1.0f,1.0f,1.0f));
		PSComStarMaterialChunk->setDiffuse(Color4f(1.0f,1.0f,1.0f,1.0f));
		PSComStarMaterialChunk->setSpecular(Color4f(0.0f,0.0f,0.0f,1.0f));
		PSComStarMaterialChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);
	endEditCP(PSComStarMaterialChunk);

	ChunkMaterialPtr PSComStarMaterial = ChunkMaterial::create();
	beginEditCP(PSComStarMaterial, ChunkMaterial::ChunksFieldMask);
		PSComStarMaterial->addChunk(ComStarQuadTextureChunk);
		PSComStarMaterial->addChunk(PSComStarMaterialChunk);
		PSComStarMaterial->addChunk(ComStarBlendChunk);
	endEditCP(PSComStarMaterial, ChunkMaterial::ChunksFieldMask);

	//exposion material
	TextureChunkPtr ExplosionQuadTextureChunk = TextureChunk::create();
    ImagePtr LoadedImage4 = ImageFileHandler::the().read("Data/fireworkstar.png");    
    beginEditCP(ExplosionQuadTextureChunk, TextureChunk::ImageFieldMask);
        ExplosionQuadTextureChunk->setImage(LoadedImage4);
        ExplosionQuadTextureChunk->setEnvMode(GL_MODULATE);
    endEditCP(ExplosionQuadTextureChunk, TextureChunk::ImageFieldMask);

	MaterialChunkPtr PSExplosionMaterialChunk = MaterialChunk::create();
	beginEditCP(PSExplosionMaterialChunk);
		PSExplosionMaterialChunk->setAmbient(Color4f(1.0f,1.0f,1.0f,1.0f));
		PSExplosionMaterialChunk->setDiffuse(Color4f(1.0f,1.0f,1.0f,1.0f));
		PSExplosionMaterialChunk->setSpecular(Color4f(0.0f,0.0f,0.0f,1.0f));
		PSExplosionMaterialChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);
	endEditCP(PSExplosionMaterialChunk);

	ChunkMaterialPtr PSExplosionMaterial = ChunkMaterial::create();
	beginEditCP(PSExplosionMaterial, ChunkMaterial::ChunksFieldMask);
		PSExplosionMaterial->addChunk(ExplosionQuadTextureChunk);
		PSExplosionMaterial->addChunk(PSExplosionMaterialChunk);
		PSExplosionMaterial->addChunk(PSBlendChunk);
	endEditCP(PSExplosionMaterial, ChunkMaterial::ChunksFieldMask);

	//exposion2 material
	TextureChunkPtr Explosion2QuadTextureChunk = TextureChunk::create();
    ImagePtr LoadedImage5 = ImageFileHandler::the().read("Data/fireworkmodel copy.png");    
    beginEditCP(Explosion2QuadTextureChunk, TextureChunk::ImageFieldMask);
        Explosion2QuadTextureChunk->setImage(LoadedImage5);
        Explosion2QuadTextureChunk->setEnvMode(GL_MODULATE);
    endEditCP(Explosion2QuadTextureChunk, TextureChunk::ImageFieldMask);

	MaterialChunkPtr PSExplosion2MaterialChunk = MaterialChunk::create();
	beginEditCP(PSExplosion2MaterialChunk);
		PSExplosion2MaterialChunk->setAmbient(Color4f(1.0f,1.0f,1.0f,1.0f));
		PSExplosion2MaterialChunk->setDiffuse(Color4f(1.0f,1.0f,1.0f,1.0f));
		PSExplosion2MaterialChunk->setSpecular(Color4f(0.0f,0.0f,0.0f,1.0f));
		PSExplosion2MaterialChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);
	endEditCP(PSExplosion2MaterialChunk);

	ChunkMaterialPtr PSExplosion2Material = ChunkMaterial::create();
	beginEditCP(PSExplosion2Material, ChunkMaterial::ChunksFieldMask);
		PSExplosion2Material->addChunk(Explosion2QuadTextureChunk);
		PSExplosion2Material->addChunk(PSExplosion2MaterialChunk);
		PSExplosion2Material->addChunk(PSBlendChunk);
	endEditCP(PSExplosion2Material, ChunkMaterial::ChunksFieldMask);


	//Particle System
		//Rocket
    RocketParticleSystem = osg::ParticleSystem::create();
	RocketParticleSystem->attachUpdateListener(TutorialWindowEventProducer);

	TutorialRocketParticleSystemListener TheRocketListener;
	RocketParticleSystem->addParticleSystemListener(&TheRocketListener);

	ExplosionParticleSystem = osg::ParticleSystem::create();
	ExplosionParticleSystem->attachUpdateListener(TutorialWindowEventProducer);

	TutorialSecondaryParticleSystemListener ExplosionListener;
	ExplosionParticleSystem->addParticleSystemListener(&ExplosionListener);

	Explosion2ParticleSystem = osg::ParticleSystem::create();
	Explosion2ParticleSystem->attachUpdateListener(TutorialWindowEventProducer);

	TutorialSecondaryParticleSystemListener Explosion2Listener;
	Explosion2ParticleSystem->addParticleSystemListener(&Explosion2Listener);

		//Circle
	CircleParticleSystem = osg::ParticleSystem::create();
	CircleParticleSystem->attachUpdateListener(TutorialWindowEventProducer);

		//Star
	StarParticleSystem = osg::ParticleSystem::create();
	StarParticleSystem->attachUpdateListener(TutorialWindowEventProducer);
		
		//ComStar
	ComStarParticleSystem = osg::ParticleSystem::create();
	ComStarParticleSystem->attachUpdateListener(TutorialWindowEventProducer);
		


	//Particle System Drawer
		//Rocket
		RocketParticleSystemDrawer = osg::QuadParticleSystemDrawer::create();
		//Circle
	CircleParticleSystemDrawer = osg::QuadParticleSystemDrawer::create();
	//CircleParticleSystemDrawer->setQuadSizeScaling(Vec2f(0.5f,0.5f));
		
		//Star
	StarParticleSystemDrawer = osg::QuadParticleSystemDrawer::create();
		
		//ComStar
	ComStarParticleSystemDrawer = osg::QuadParticleSystemDrawer::create();

		//Explosion
	ExplosionParticleSystemDrawer = osg::QuadParticleSystemDrawer::create();
		//Explosion2
	Explosion2ParticleSystemDrawer = osg::QuadParticleSystemDrawer::create();
	
			////////////////2ND GROUP///////////////
	//Circle
	Circle2ParticleSystem = osg::ParticleSystem::create();
	Circle2ParticleSystem->attachUpdateListener(TutorialWindowEventProducer);

		//Star
	Star2ParticleSystem = osg::ParticleSystem::create();
	Star2ParticleSystem->attachUpdateListener(TutorialWindowEventProducer);
		
		//ComStar
	ComStar2ParticleSystem = osg::ParticleSystem::create();
	ComStar2ParticleSystem->attachUpdateListener(TutorialWindowEventProducer);
		


	//Particle System Drawer
		//Circle2
	Circle2ParticleSystemDrawer = osg::QuadParticleSystemDrawer::create();
	//CircleParticleSystemDrawer->setQuadSizeScaling(Vec2f(0.5f,0.5f));
		
		//Star2
	Star2ParticleSystemDrawer = osg::QuadParticleSystemDrawer::create();
		
		//ComStar2
	ComStar2ParticleSystemDrawer = osg::QuadParticleSystemDrawer::create();
		
	
		
	
	//Particle System Node    
    
	ParticleSystemCorePtr RocketParticleNodeCore = osg::ParticleSystemCore::create();
    beginEditCP(RocketParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
		RocketParticleNodeCore->setSystem(RocketParticleSystem);
		RocketParticleNodeCore->setDrawer(RocketParticleSystemDrawer);
		RocketParticleNodeCore->setMaterial(PSRocketMaterial);
    endEditCP(RocketParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
   
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
	
	
		//end/////////////////////

		//Circle
	CircleBurstGenerator = osg::BurstParticleGenerator::create();
			//Attach the function objects to the Generator
	CirclePositionDistribution = createSmokePositionDistribution();
	beginEditCP(CircleBurstGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask);
		CircleBurstGenerator->setPositionFunction(CirclePositionDistribution);
		CircleBurstGenerator->setLifespanFunction(createSmokeLifespanDistribution());
		CircleBurstGenerator->setBurstAmount(50.0);
		CircleBurstGenerator->setVelocityFunction(createSmokeVelocityDistribution());
		CircleBurstGenerator->setColorFunction(createSmokeColorDistribution());
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
   //Attach the Affector to the Circle Particle System
	beginEditCP(CircleParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
		CircleParticleSystem->getAffectors().push_back(CircleAgeFadeParticleAffector);
		CircleParticleSystem->getAffectors().push_back(CircleAgeSizeParticleAffector);
	endEditCP(CircleParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
	
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
		StarBurstGenerator->setLifespanFunction(createSmokeLifespanDistribution());
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
		StarAgeFadeParticleAffector->setFadeToAlpha(0.2f);
		StarAgeFadeParticleAffector->setEndAlpha(1.0f);	
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
   
	
	//Attach the Affector to the Star Particle System
	beginEditCP(StarParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask | ParticleSystem::SystemAffectorsFieldMask);
		StarParticleSystem->getAffectors().push_back(StarAgeSizeParticleAffector);
	endEditCP(StarParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask | ParticleSystem::SystemAffectorsFieldMask);

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

		//ComStar
	ComStarBurstGenerator = osg::BurstParticleGenerator::create();
			//Attach the function objects to the Generator
	ComStarPositionDistribution = createComStarPositionDistribution();
	beginEditCP(ComStarBurstGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask);
		ComStarBurstGenerator->setPositionFunction(ComStarPositionDistribution);
		ComStarBurstGenerator->setLifespanFunction(createSmokeLifespanDistribution());
		ComStarBurstGenerator->setBurstAmount(50.0);
		ComStarBurstGenerator->setVelocityFunction(createComStarVelocityDistribution());
		ComStarBurstGenerator->setColorFunction(createComStarColorDistribution());
	endEditCP(ComStarBurstGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask);

	//Attach the function objects the Affectors
	ComStarAgeFadeParticleAffector = osg::AgeFadeParticleAffector::create();
	beginEditCP(ComStarAgeFadeParticleAffector, AgeFadeParticleAffector::FadeInTimeFieldMask | AgeFadeParticleAffector::FadeOutTimeFieldMask | AgeFadeParticleAffector::StartAlphaFieldMask| AgeFadeParticleAffector::FadeToAlphaFieldMask | AgeFadeParticleAffector::EndAlphaFieldMask);
		ComStarAgeFadeParticleAffector->setFadeInTime(2.0f);
		ComStarAgeFadeParticleAffector->setFadeOutTime(5.0f);
		ComStarAgeFadeParticleAffector->setStartAlpha(0.0f);
		ComStarAgeFadeParticleAffector->setFadeToAlpha(1.0f);
		ComStarAgeFadeParticleAffector->setEndAlpha(0.0f);	
	endEditCP(ComStarAgeFadeParticleAffector, AgeFadeParticleAffector::FadeInTimeFieldMask | AgeFadeParticleAffector::FadeOutTimeFieldMask | AgeFadeParticleAffector::StartAlphaFieldMask| AgeFadeParticleAffector::FadeToAlphaFieldMask | AgeFadeParticleAffector::EndAlphaFieldMask);

	ComStarAgeSizeParticleAffector = osg::AgeSizeParticleAffector::create();
	beginEditCP(ComStarAgeSizeParticleAffector,AgeSizeParticleAffector::AgesFieldMask | AgeSizeParticleAffector::SizesFieldMask);
			//ages
			ComStarAgeSizeParticleAffector->getAges().push_back(0.1);
			ComStarAgeSizeParticleAffector->getAges().push_back(0.2);
			ComStarAgeSizeParticleAffector->getAges().push_back(0.3);
			ComStarAgeSizeParticleAffector->getAges().push_back(0.4);
			ComStarAgeSizeParticleAffector->getAges().push_back(0.5);
			ComStarAgeSizeParticleAffector->getAges().push_back(0.6);
			ComStarAgeSizeParticleAffector->getAges().push_back(0.7);
			ComStarAgeSizeParticleAffector->getAges().push_back(0.8);
			ComStarAgeSizeParticleAffector->getAges().push_back(1.0);

			//sizes
			ComStarAgeSizeParticleAffector->getSizes().push_back(Vec3f(0.5,0.5,0.5));
			ComStarAgeSizeParticleAffector->getSizes().push_back(Vec3f(1.0,1.0,1.0));
			ComStarAgeSizeParticleAffector->getSizes().push_back(Vec3f(2.0,2.0,2.0));
			ComStarAgeSizeParticleAffector->getSizes().push_back(Vec3f(2.5,2.5,2.5));
			ComStarAgeSizeParticleAffector->getSizes().push_back(Vec3f(3.0,3.0,3.0));
			ComStarAgeSizeParticleAffector->getSizes().push_back(Vec3f(3.5,3.5,3.5));
			ComStarAgeSizeParticleAffector->getSizes().push_back(Vec3f(4.0,4.0,4.0));
			ComStarAgeSizeParticleAffector->getSizes().push_back(Vec3f(5.0,5.0,5.0));
			ComStarAgeSizeParticleAffector->getSizes().push_back(Vec3f(6.5,6.5,6.5));
	endEditCP(ComStarAgeSizeParticleAffector,AgeSizeParticleAffector::AgesFieldMask | AgeSizeParticleAffector::SizesFieldMask);
   //Attach the Affector to the ComStar Particle System
	beginEditCP(ComStarParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
		//ComStarParticleSystem->getAffectors().push_back(ComStarAgeFadeParticleAffector);
		ComStarParticleSystem->getAffectors().push_back(ComStarAgeSizeParticleAffector);
	endEditCP(ComStarParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);

	ParticleSystemCorePtr ComStarParticleNodeCore = osg::ParticleSystemCore::create();
    beginEditCP(ComStarParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
		ComStarParticleNodeCore->setSystem(ComStarParticleSystem);
		ComStarParticleNodeCore->setDrawer(ComStarParticleSystemDrawer);
		ComStarParticleNodeCore->setMaterial(PSComStarMaterial);
    endEditCP(ComStarParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
    
	NodePtr ComStarParticleNode = osg::Node::create();
    beginEditCP(ComStarParticleNode, Node::CoreFieldMask);
        ComStarParticleNode->setCore(ComStarParticleNodeCore);
    endEditCP(ComStarParticleNode, Node::CoreFieldMask);
		//end/////////////////////

	//Explosion
	ExplosionBurstGenerator = osg::BurstParticleGenerator::create();
			//Attach the function objects to the Generator
	ExplosionPositionDistribution = createExplosionPositionDistribution();
	beginEditCP(ExplosionBurstGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask);
		ExplosionBurstGenerator->setPositionFunction(ExplosionPositionDistribution);
		ExplosionBurstGenerator->setLifespanFunction(createSmokeLifespanDistribution());
		ExplosionBurstGenerator->setBurstAmount(15.0);
		ExplosionBurstGenerator->setVelocityFunction(createExplosionVelocityDistribution());
		ExplosionBurstGenerator->setColorFunction(createSmokeColorDistribution());
	endEditCP(ExplosionBurstGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask);

	//Attach the function objects the Affectors
	ExplosionAgeFadeParticleAffector = osg::AgeFadeParticleAffector::create();
	beginEditCP(ExplosionAgeFadeParticleAffector, AgeFadeParticleAffector::FadeInTimeFieldMask | AgeFadeParticleAffector::FadeOutTimeFieldMask | AgeFadeParticleAffector::StartAlphaFieldMask| AgeFadeParticleAffector::FadeToAlphaFieldMask | AgeFadeParticleAffector::EndAlphaFieldMask);
		ExplosionAgeFadeParticleAffector->setFadeInTime(3.0f);
		ExplosionAgeFadeParticleAffector->setFadeOutTime(5.0f);
		ExplosionAgeFadeParticleAffector->setStartAlpha(0.0f);
		ExplosionAgeFadeParticleAffector->setFadeToAlpha(0.1f);
		ExplosionAgeFadeParticleAffector->setEndAlpha(0.0f);	
	endEditCP(ExplosionAgeFadeParticleAffector, AgeFadeParticleAffector::FadeInTimeFieldMask | AgeFadeParticleAffector::FadeOutTimeFieldMask | AgeFadeParticleAffector::StartAlphaFieldMask| AgeFadeParticleAffector::FadeToAlphaFieldMask | AgeFadeParticleAffector::EndAlphaFieldMask);

	ExplosionAgeSizeParticleAffector = osg::AgeSizeParticleAffector::create();
	beginEditCP(ExplosionAgeSizeParticleAffector,AgeSizeParticleAffector::AgesFieldMask | AgeSizeParticleAffector::SizesFieldMask);
			//ages
			ExplosionAgeSizeParticleAffector->getAges().push_back(0.1);
			ExplosionAgeSizeParticleAffector->getAges().push_back(0.2);
			ExplosionAgeSizeParticleAffector->getAges().push_back(0.3);
			ExplosionAgeSizeParticleAffector->getAges().push_back(0.4);
			ExplosionAgeSizeParticleAffector->getAges().push_back(0.5);
			ExplosionAgeSizeParticleAffector->getAges().push_back(0.6);
			ExplosionAgeSizeParticleAffector->getAges().push_back(0.7);
			ExplosionAgeSizeParticleAffector->getAges().push_back(0.8);
			ExplosionAgeSizeParticleAffector->getAges().push_back(1.0);

			//sizes
			ExplosionAgeSizeParticleAffector->getSizes().push_back(Vec3f(0.5,0.5,0.5));
			ExplosionAgeSizeParticleAffector->getSizes().push_back(Vec3f(1.0,1.0,1.0));
			ExplosionAgeSizeParticleAffector->getSizes().push_back(Vec3f(2.0,2.0,2.0));
			ExplosionAgeSizeParticleAffector->getSizes().push_back(Vec3f(2.5,2.5,2.5));
			ExplosionAgeSizeParticleAffector->getSizes().push_back(Vec3f(3.0,3.0,3.0));
			ExplosionAgeSizeParticleAffector->getSizes().push_back(Vec3f(3.5,3.5,3.5));
			ExplosionAgeSizeParticleAffector->getSizes().push_back(Vec3f(4.0,4.0,4.0));
			ExplosionAgeSizeParticleAffector->getSizes().push_back(Vec3f(5.0,5.0,5.0));
			ExplosionAgeSizeParticleAffector->getSizes().push_back(Vec3f(6.5,6.5,6.5));
	endEditCP(ExplosionAgeSizeParticleAffector,AgeSizeParticleAffector::AgesFieldMask | AgeSizeParticleAffector::SizesFieldMask);
   
	
	//Attach the Affector to the Explosion Particle System
	beginEditCP(ExplosionParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask | ParticleSystem::SystemAffectorsFieldMask);
	//	ExplosionParticleSystem->getAffectors().push_back(ExplosionAgeSizeParticleAffector);
	endEditCP(ExplosionParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask | ParticleSystem::SystemAffectorsFieldMask);

	ParticleSystemCorePtr ExplosionParticleNodeCore = osg::ParticleSystemCore::create();
    beginEditCP(ExplosionParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
		ExplosionParticleNodeCore->setSystem(ExplosionParticleSystem);
		ExplosionParticleNodeCore->setDrawer(ExplosionParticleSystemDrawer);
		ExplosionParticleNodeCore->setMaterial(PSExplosionMaterial);
    endEditCP(ExplosionParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
    
	NodePtr ExplosionParticleNode = osg::Node::create();
    beginEditCP(ExplosionParticleNode, Node::CoreFieldMask);
        ExplosionParticleNode->setCore(ExplosionParticleNodeCore);
    endEditCP(ExplosionParticleNode, Node::CoreFieldMask);
		//end/////////////////////

	//Explosion2
	Explosion2BurstGenerator = osg::BurstParticleGenerator::create();
			//Attach the function objects to the Generator
	Explosion2PositionDistribution = createExplosion2PositionDistribution();
	beginEditCP(Explosion2BurstGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask);
		Explosion2BurstGenerator->setPositionFunction(Explosion2PositionDistribution);
		Explosion2BurstGenerator->setLifespanFunction(createSmokeLifespanDistribution());
		Explosion2BurstGenerator->setBurstAmount(15.0);
		Explosion2BurstGenerator->setVelocityFunction(createExplosion2VelocityDistribution());
		Explosion2BurstGenerator->setColorFunction(createExplosion2ColorDistribution());
	endEditCP(Explosion2BurstGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask);

	//Attach the function objects the Affectors
	Explosion2AgeFadeParticleAffector = osg::AgeFadeParticleAffector::create();
	beginEditCP(Explosion2AgeFadeParticleAffector, AgeFadeParticleAffector::FadeInTimeFieldMask | AgeFadeParticleAffector::FadeOutTimeFieldMask | AgeFadeParticleAffector::StartAlphaFieldMask| AgeFadeParticleAffector::FadeToAlphaFieldMask | AgeFadeParticleAffector::EndAlphaFieldMask);
		Explosion2AgeFadeParticleAffector->setFadeInTime(3.0f);
		Explosion2AgeFadeParticleAffector->setFadeOutTime(5.0f);
		Explosion2AgeFadeParticleAffector->setStartAlpha(0.0f);
		Explosion2AgeFadeParticleAffector->setFadeToAlpha(0.2f);
		Explosion2AgeFadeParticleAffector->setEndAlpha(1.0f);	
	endEditCP(Explosion2AgeFadeParticleAffector, AgeFadeParticleAffector::FadeInTimeFieldMask | AgeFadeParticleAffector::FadeOutTimeFieldMask | AgeFadeParticleAffector::StartAlphaFieldMask| AgeFadeParticleAffector::FadeToAlphaFieldMask | AgeFadeParticleAffector::EndAlphaFieldMask);

	Explosion2AgeSizeParticleAffector = osg::AgeSizeParticleAffector::create();
	beginEditCP(Explosion2AgeSizeParticleAffector,AgeSizeParticleAffector::AgesFieldMask | AgeSizeParticleAffector::SizesFieldMask);
			//ages
			Explosion2AgeSizeParticleAffector->getAges().push_back(0.1);
			Explosion2AgeSizeParticleAffector->getAges().push_back(0.2);
			Explosion2AgeSizeParticleAffector->getAges().push_back(0.3);
			Explosion2AgeSizeParticleAffector->getAges().push_back(0.4);
			Explosion2AgeSizeParticleAffector->getAges().push_back(0.5);
			Explosion2AgeSizeParticleAffector->getAges().push_back(0.6);
			Explosion2AgeSizeParticleAffector->getAges().push_back(0.7);
			Explosion2AgeSizeParticleAffector->getAges().push_back(0.8);
			Explosion2AgeSizeParticleAffector->getAges().push_back(1.0);

			//sizes
			Explosion2AgeSizeParticleAffector->getSizes().push_back(Vec3f(0.5,0.5,0.5));
			Explosion2AgeSizeParticleAffector->getSizes().push_back(Vec3f(1.0,1.0,1.0));
			Explosion2AgeSizeParticleAffector->getSizes().push_back(Vec3f(2.0,2.0,2.0));
			Explosion2AgeSizeParticleAffector->getSizes().push_back(Vec3f(2.5,2.5,2.5));
			Explosion2AgeSizeParticleAffector->getSizes().push_back(Vec3f(3.0,3.0,3.0));
			Explosion2AgeSizeParticleAffector->getSizes().push_back(Vec3f(3.5,3.5,3.5));
			Explosion2AgeSizeParticleAffector->getSizes().push_back(Vec3f(4.0,4.0,4.0));
			Explosion2AgeSizeParticleAffector->getSizes().push_back(Vec3f(5.0,5.0,5.0));
			Explosion2AgeSizeParticleAffector->getSizes().push_back(Vec3f(6.5,6.5,6.5));
	endEditCP(Explosion2AgeSizeParticleAffector,AgeSizeParticleAffector::AgesFieldMask | AgeSizeParticleAffector::SizesFieldMask);
   
	
	//Attach the Affector to the Explosion2 Particle System
	beginEditCP(Explosion2ParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask | ParticleSystem::SystemAffectorsFieldMask);
	//	Explosion2ParticleSystem->getAffectors().push_back(Explosion2AgeSizeParticleAffector);
	endEditCP(Explosion2ParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask | ParticleSystem::SystemAffectorsFieldMask);

	ParticleSystemCorePtr Explosion2ParticleNodeCore = osg::ParticleSystemCore::create();
    beginEditCP(Explosion2ParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
		Explosion2ParticleNodeCore->setSystem(Explosion2ParticleSystem);
		Explosion2ParticleNodeCore->setDrawer(Explosion2ParticleSystemDrawer);
		Explosion2ParticleNodeCore->setMaterial(PSExplosion2Material);
    endEditCP(Explosion2ParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
    
	NodePtr Explosion2ParticleNode = osg::Node::create();
    beginEditCP(Explosion2ParticleNode, Node::CoreFieldMask);
        Explosion2ParticleNode->setCore(Explosion2ParticleNodeCore);
    endEditCP(Explosion2ParticleNode, Node::CoreFieldMask);
		//end/////////////////////

	////////////////////////2ND GROUP///////////////////////////////////

	//Particle System Node    
    
		//Circle2
	Circle2BurstGenerator = osg::BurstParticleGenerator::create();
			//Attach the function objects to the Generator
	Circle2PositionDistribution = createSmokePositionDistribution();
	beginEditCP(Circle2BurstGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask);
		Circle2BurstGenerator->setPositionFunction(Circle2PositionDistribution);
		Circle2BurstGenerator->setLifespanFunction(createSmokeLifespanDistribution());
		Circle2BurstGenerator->setBurstAmount(50.0);
		Circle2BurstGenerator->setVelocityFunction(createSmoke2VelocityDistribution());
		Circle2BurstGenerator->setColorFunction(createSmokeColorDistribution());
	endEditCP(Circle2BurstGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask);

	//Attach the function objects the Affectors
	Circle2AgeFadeParticleAffector = osg::AgeFadeParticleAffector::create();
	beginEditCP(Circle2AgeFadeParticleAffector, AgeFadeParticleAffector::FadeInTimeFieldMask | AgeFadeParticleAffector::FadeOutTimeFieldMask | AgeFadeParticleAffector::StartAlphaFieldMask| AgeFadeParticleAffector::FadeToAlphaFieldMask | AgeFadeParticleAffector::EndAlphaFieldMask);
		Circle2AgeFadeParticleAffector->setFadeInTime(3.0f);
		Circle2AgeFadeParticleAffector->setFadeOutTime(5.0f);
		Circle2AgeFadeParticleAffector->setStartAlpha(0.0f);
		Circle2AgeFadeParticleAffector->setFadeToAlpha(1.0f);
		Circle2AgeFadeParticleAffector->setEndAlpha(0.0f);	
	endEditCP(Circle2AgeFadeParticleAffector, AgeFadeParticleAffector::FadeInTimeFieldMask | AgeFadeParticleAffector::FadeOutTimeFieldMask | AgeFadeParticleAffector::StartAlphaFieldMask| AgeFadeParticleAffector::FadeToAlphaFieldMask | AgeFadeParticleAffector::EndAlphaFieldMask);

	Circle2AgeSizeParticleAffector = osg::AgeSizeParticleAffector::create();
	beginEditCP(Circle2AgeSizeParticleAffector,AgeSizeParticleAffector::AgesFieldMask | AgeSizeParticleAffector::SizesFieldMask);
			//ages
			Circle2AgeSizeParticleAffector->getAges().push_back(0.1);
			Circle2AgeSizeParticleAffector->getAges().push_back(0.2);
			Circle2AgeSizeParticleAffector->getAges().push_back(0.3);
			Circle2AgeSizeParticleAffector->getAges().push_back(0.4);
			Circle2AgeSizeParticleAffector->getAges().push_back(0.5);
			Circle2AgeSizeParticleAffector->getAges().push_back(0.6);
			Circle2AgeSizeParticleAffector->getAges().push_back(0.7);
			Circle2AgeSizeParticleAffector->getAges().push_back(0.8);
			Circle2AgeSizeParticleAffector->getAges().push_back(1.0);

			//sizes
			Circle2AgeSizeParticleAffector->getSizes().push_back(Vec3f(0.5,0.5,0.5));
			Circle2AgeSizeParticleAffector->getSizes().push_back(Vec3f(1.0,1.0,1.0));
			Circle2AgeSizeParticleAffector->getSizes().push_back(Vec3f(2.0,2.0,2.0));
			Circle2AgeSizeParticleAffector->getSizes().push_back(Vec3f(2.5,2.5,2.5));
			Circle2AgeSizeParticleAffector->getSizes().push_back(Vec3f(3.0,3.0,3.0));
			Circle2AgeSizeParticleAffector->getSizes().push_back(Vec3f(3.5,3.5,3.5));
			Circle2AgeSizeParticleAffector->getSizes().push_back(Vec3f(4.0,4.0,4.0));
			Circle2AgeSizeParticleAffector->getSizes().push_back(Vec3f(5.0,5.0,5.0));
			Circle2AgeSizeParticleAffector->getSizes().push_back(Vec3f(6.5,6.5,6.5));
	endEditCP(Circle2AgeSizeParticleAffector,AgeSizeParticleAffector::AgesFieldMask | AgeSizeParticleAffector::SizesFieldMask);
   
	   //Attach the Affector to the Circle2 Particle System
	beginEditCP(Circle2ParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
		Circle2ParticleSystem->getAffectors().push_back(Circle2AgeFadeParticleAffector);
		Circle2ParticleSystem->getAffectors().push_back(Circle2AgeSizeParticleAffector);
	endEditCP(Circle2ParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
	
	ParticleSystemCorePtr Circle2ParticleNodeCore = osg::ParticleSystemCore::create();
    beginEditCP(Circle2ParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
		Circle2ParticleNodeCore->setSystem(Circle2ParticleSystem);
		Circle2ParticleNodeCore->setDrawer(Circle2ParticleSystemDrawer);
		Circle2ParticleNodeCore->setMaterial(PSCircleMaterial);
    endEditCP(Circle2ParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
 
	NodePtr Circle2ParticleNode = osg::Node::create();
    beginEditCP(Circle2ParticleNode, Node::CoreFieldMask);
        Circle2ParticleNode->setCore(Circle2ParticleNodeCore);
    endEditCP(Circle2ParticleNode, Node::CoreFieldMask);
		//end/////////////////////

		//Star2
	Star2BurstGenerator = osg::BurstParticleGenerator::create();
			//Attach the function objects to the Generator
	Star2PositionDistribution = createStar2PositionDistribution();
	beginEditCP(Star2BurstGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask);
		Star2BurstGenerator->setPositionFunction(Star2PositionDistribution);
		Star2BurstGenerator->setLifespanFunction(createSmokeLifespanDistribution());
		Star2BurstGenerator->setBurstAmount(50.0);
		Star2BurstGenerator->setVelocityFunction(createStar2VelocityDistribution());
	endEditCP(Star2BurstGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask);

	//Attach the function objects the Affectors
	Star2AgeFadeParticleAffector = osg::AgeFadeParticleAffector::create();
	beginEditCP(Star2AgeFadeParticleAffector, AgeFadeParticleAffector::FadeInTimeFieldMask | AgeFadeParticleAffector::FadeOutTimeFieldMask | AgeFadeParticleAffector::StartAlphaFieldMask| AgeFadeParticleAffector::FadeToAlphaFieldMask | AgeFadeParticleAffector::EndAlphaFieldMask);
		Star2AgeFadeParticleAffector->setFadeInTime(3.0f);
		Star2AgeFadeParticleAffector->setFadeOutTime(5.0f);
		Star2AgeFadeParticleAffector->setStartAlpha(0.0f);
		Star2AgeFadeParticleAffector->setFadeToAlpha(0.2f);
		Star2AgeFadeParticleAffector->setEndAlpha(1.0f);	
	endEditCP(Star2AgeFadeParticleAffector, AgeFadeParticleAffector::FadeInTimeFieldMask | AgeFadeParticleAffector::FadeOutTimeFieldMask | AgeFadeParticleAffector::StartAlphaFieldMask| AgeFadeParticleAffector::FadeToAlphaFieldMask | AgeFadeParticleAffector::EndAlphaFieldMask);

	Star2AgeSizeParticleAffector = osg::AgeSizeParticleAffector::create();
	beginEditCP(Star2AgeSizeParticleAffector,AgeSizeParticleAffector::AgesFieldMask | AgeSizeParticleAffector::SizesFieldMask);
			//ages
			Star2AgeSizeParticleAffector->getAges().push_back(0.1);
			Star2AgeSizeParticleAffector->getAges().push_back(0.2);
			Star2AgeSizeParticleAffector->getAges().push_back(0.3);
			Star2AgeSizeParticleAffector->getAges().push_back(0.4);
			Star2AgeSizeParticleAffector->getAges().push_back(0.5);
			Star2AgeSizeParticleAffector->getAges().push_back(0.6);
			Star2AgeSizeParticleAffector->getAges().push_back(0.7);
			Star2AgeSizeParticleAffector->getAges().push_back(0.8);
			Star2AgeSizeParticleAffector->getAges().push_back(1.0);

			//sizes
			Star2AgeSizeParticleAffector->getSizes().push_back(Vec3f(0.5,0.5,0.5));
			Star2AgeSizeParticleAffector->getSizes().push_back(Vec3f(1.0,1.0,1.0));
			Star2AgeSizeParticleAffector->getSizes().push_back(Vec3f(2.0,2.0,2.0));
			Star2AgeSizeParticleAffector->getSizes().push_back(Vec3f(2.5,2.5,2.5));
			Star2AgeSizeParticleAffector->getSizes().push_back(Vec3f(3.0,3.0,3.0));
			Star2AgeSizeParticleAffector->getSizes().push_back(Vec3f(3.5,3.5,3.5));
			Star2AgeSizeParticleAffector->getSizes().push_back(Vec3f(4.0,4.0,4.0));
			Star2AgeSizeParticleAffector->getSizes().push_back(Vec3f(5.0,5.0,5.0));
			Star2AgeSizeParticleAffector->getSizes().push_back(Vec3f(6.5,6.5,6.5));
	endEditCP(Star2AgeSizeParticleAffector,AgeSizeParticleAffector::AgesFieldMask | AgeSizeParticleAffector::SizesFieldMask);
   
	
	//Attach the Affector to the Star2 Particle System
	beginEditCP(Star2ParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask | ParticleSystem::SystemAffectorsFieldMask);
		Star2ParticleSystem->getAffectors().push_back(Star2AgeSizeParticleAffector);
	endEditCP(Star2ParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask | ParticleSystem::SystemAffectorsFieldMask);

	ParticleSystemCorePtr Star2ParticleNodeCore = osg::ParticleSystemCore::create();
    beginEditCP(Star2ParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
		Star2ParticleNodeCore->setSystem(Star2ParticleSystem);
		Star2ParticleNodeCore->setDrawer(Star2ParticleSystemDrawer);
		Star2ParticleNodeCore->setMaterial(PSStarMaterial);
    endEditCP(Star2ParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
    
	NodePtr Star2ParticleNode = osg::Node::create();
    beginEditCP(Star2ParticleNode, Node::CoreFieldMask);
        Star2ParticleNode->setCore(Star2ParticleNodeCore);
    endEditCP(Star2ParticleNode, Node::CoreFieldMask);
		//end/////////////////////

		//ComStar2
	ComStar2BurstGenerator = osg::BurstParticleGenerator::create();
			//Attach the function objects to the Generator
	ComStar2PositionDistribution = createComStar2PositionDistribution();
	beginEditCP(ComStar2BurstGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask);
		ComStar2BurstGenerator->setPositionFunction(ComStar2PositionDistribution);
		ComStar2BurstGenerator->setLifespanFunction(createSmokeLifespanDistribution());
		ComStar2BurstGenerator->setBurstAmount(50.0);
		ComStar2BurstGenerator->setVelocityFunction(createComStar2VelocityDistribution());
		ComStarBurstGenerator->setColorFunction(createComStarColorDistribution());
	endEditCP(ComStar2BurstGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask);

	//Attach the function objects the Affectors
	ComStar2AgeFadeParticleAffector = osg::AgeFadeParticleAffector::create();
	beginEditCP(ComStar2AgeFadeParticleAffector, AgeFadeParticleAffector::FadeInTimeFieldMask | AgeFadeParticleAffector::FadeOutTimeFieldMask | AgeFadeParticleAffector::StartAlphaFieldMask| AgeFadeParticleAffector::FadeToAlphaFieldMask | AgeFadeParticleAffector::EndAlphaFieldMask);
		ComStar2AgeFadeParticleAffector->setFadeInTime(2.0f);
		ComStar2AgeFadeParticleAffector->setFadeOutTime(5.0f);
		ComStar2AgeFadeParticleAffector->setStartAlpha(0.0f);
		ComStar2AgeFadeParticleAffector->setFadeToAlpha(0.2f);
		ComStar2AgeFadeParticleAffector->setEndAlpha(0.0f);	
	endEditCP(ComStar2AgeFadeParticleAffector, AgeFadeParticleAffector::FadeInTimeFieldMask | AgeFadeParticleAffector::FadeOutTimeFieldMask | AgeFadeParticleAffector::StartAlphaFieldMask| AgeFadeParticleAffector::FadeToAlphaFieldMask | AgeFadeParticleAffector::EndAlphaFieldMask);

	ComStar2AgeSizeParticleAffector = osg::AgeSizeParticleAffector::create();
	beginEditCP(ComStar2AgeSizeParticleAffector,AgeSizeParticleAffector::AgesFieldMask | AgeSizeParticleAffector::SizesFieldMask);
			//ages
			ComStar2AgeSizeParticleAffector->getAges().push_back(0.1);
			ComStar2AgeSizeParticleAffector->getAges().push_back(0.2);
			ComStar2AgeSizeParticleAffector->getAges().push_back(0.3);
			ComStar2AgeSizeParticleAffector->getAges().push_back(0.4);
			ComStar2AgeSizeParticleAffector->getAges().push_back(0.5);
			ComStar2AgeSizeParticleAffector->getAges().push_back(0.6);
			ComStar2AgeSizeParticleAffector->getAges().push_back(0.7);
			ComStar2AgeSizeParticleAffector->getAges().push_back(0.8);
			ComStar2AgeSizeParticleAffector->getAges().push_back(1.0);

			//sizes
			ComStar2AgeSizeParticleAffector->getSizes().push_back(Vec3f(0.5,0.5,0.5));
			ComStar2AgeSizeParticleAffector->getSizes().push_back(Vec3f(1.0,1.0,1.0));
			ComStar2AgeSizeParticleAffector->getSizes().push_back(Vec3f(2.0,2.0,2.0));
			ComStar2AgeSizeParticleAffector->getSizes().push_back(Vec3f(2.5,2.5,2.5));
			ComStar2AgeSizeParticleAffector->getSizes().push_back(Vec3f(3.0,3.0,3.0));
			ComStar2AgeSizeParticleAffector->getSizes().push_back(Vec3f(3.5,3.5,3.5));
			ComStar2AgeSizeParticleAffector->getSizes().push_back(Vec3f(4.0,4.0,4.0));
			ComStar2AgeSizeParticleAffector->getSizes().push_back(Vec3f(5.0,5.0,5.0));
			ComStar2AgeSizeParticleAffector->getSizes().push_back(Vec3f(6.5,6.5,6.5));
	endEditCP(ComStar2AgeSizeParticleAffector,AgeSizeParticleAffector::AgesFieldMask | AgeSizeParticleAffector::SizesFieldMask);
   //Attach the Affector to the ComStar2 Particle System
	beginEditCP(ComStar2ParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);
		ComStar2ParticleSystem->getAffectors().push_back(ComStar2AgeFadeParticleAffector);
		ComStar2ParticleSystem->getAffectors().push_back(ComStar2AgeSizeParticleAffector);
	endEditCP(ComStar2ParticleSystem, ParticleSystem::GeneratorsFieldMask | ParticleSystem::AffectorsFieldMask);

	ParticleSystemCorePtr ComStar2ParticleNodeCore = osg::ParticleSystemCore::create();
    beginEditCP(ComStar2ParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
		ComStar2ParticleNodeCore->setSystem(ComStar2ParticleSystem);
		ComStar2ParticleNodeCore->setDrawer(ComStar2ParticleSystemDrawer);
		ComStar2ParticleNodeCore->setMaterial(PSComStarMaterial);
    endEditCP(ComStar2ParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
    
	NodePtr ComStar2ParticleNode = osg::Node::create();
    beginEditCP(ComStar2ParticleNode, Node::CoreFieldMask);
        ComStar2ParticleNode->setCore(ComStar2ParticleNodeCore);
    endEditCP(ComStar2ParticleNode, Node::CoreFieldMask);
		//end/////////////////////
	
	

    // Make Main Scene Node 
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
        scene->addChild(RocketParticleNode);
		scene->addChild(CircleParticleNode);
		scene->addChild(StarParticleNode);
		scene->addChild(ComStarParticleNode);
		scene->addChild(Circle2ParticleNode);
		scene->addChild(Star2ParticleNode);
		scene->addChild(ComStar2ParticleNode);
		scene->addChild(ExplosionParticleNode);
		scene->addChild(Explosion2ParticleNode);
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
    SphereDistribution3DPtr TheSphereDistribution = SphereDistribution3D::create();
    beginEditCP(TheSphereDistribution);
      TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
      TheSphereDistribution->setInnerRadius(3.0);
      TheSphereDistribution->setOuterRadius(10.0);
      TheSphereDistribution->setMinTheta(-3.141950);
      TheSphereDistribution->setMaxTheta(3.141950);
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

FunctionPtr createSmokeColorDistribution(void)
{
	 //Sphere Distribution
    LineDistribution3DPtr TheLineDistribution = LineDistribution3D::create();
    beginEditCP(TheLineDistribution);
 		TheLineDistribution->setPoint1(Pnt3f(10.0,0.0,0.0));
		TheLineDistribution->setPoint2(Pnt3f(10.0,0.0,0.0));
    endEditCP(TheLineDistribution);

	DataConverterPtr TheColor4fConverter = DataConverter::create();
	beginEditCP(TheColor4fConverter);
		TheColor4fConverter->setToType(&FieldDataTraits<Color4f>::getType());
	endEditCP(TheColor4fConverter);

	CompoundFunctionPtr TheColorDistribution = CompoundFunction::create();
	beginEditCP(TheColorDistribution);
		TheColorDistribution->getFunctions().push_back(TheLineDistribution);
		TheColorDistribution->getFunctions().push_back(TheColor4fConverter);
	endEditCP(TheColorDistribution);

    return TheColorDistribution;
}
FunctionPtr createStarPositionDistribution(void)
{
    //Sphere Distribution
    SphereDistribution3DPtr TheSphereDistribution = SphereDistribution3D::create();
    beginEditCP(TheSphereDistribution);
      TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
      TheSphereDistribution->setInnerRadius(0.0);
      TheSphereDistribution->setOuterRadius(5.0);
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
 		TheLineDistribution->setPoint1(Pnt3f(0.0,-1.0,0.0));
		TheLineDistribution->setPoint2(Pnt3f(0.0,-5.0,0.0));
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

FunctionPtr createComStarPositionDistribution(void)
{
    //Sphere Distribution
    SphereDistribution3DPtr TheSphereDistribution = SphereDistribution3D::create();
    beginEditCP(TheSphereDistribution);
      TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
      TheSphereDistribution->setInnerRadius(2.0);
      TheSphereDistribution->setOuterRadius(6.0);
      TheSphereDistribution->setMinTheta(0.0);
      TheSphereDistribution->setMaxTheta(6.283185);
      TheSphereDistribution->setMinZ(-1.0);
      TheSphereDistribution->setMaxZ(1.0);
	  TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::SURFACE);
    endEditCP(TheSphereDistribution);

    return TheSphereDistribution;
}

FunctionPtr createComStarLifespanDistribution(void)
{
    GaussianNormalDistribution1DPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    beginEditCP(TheLifespanDistribution);
      TheLifespanDistribution->setMean(3.0f);
      TheLifespanDistribution->setStandardDeviation(0.5);
    endEditCP(TheLifespanDistribution);
	
	return TheLifespanDistribution;
}

FunctionPtr createComStarVelocityDistribution(void)
{
	 //Sphere Distribution
    LineDistribution3DPtr TheLineDistribution = LineDistribution3D::create();
    beginEditCP(TheLineDistribution);
 		TheLineDistribution->setPoint1(Pnt3f(0.0,-1.0,0.0));
		TheLineDistribution->setPoint2(Pnt3f(0.0,-5.0,0.0));
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



FunctionPtr createSmoke2PositionDistribution(void)
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



FunctionPtr createSmoke2VelocityDistribution(void)
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

FunctionPtr createStar2PositionDistribution(void)
{
     //Sphere Distribution
    SphereDistribution3DPtr TheSphereDistribution = SphereDistribution3D::create();
    beginEditCP(TheSphereDistribution);
      TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
      TheSphereDistribution->setInnerRadius(0.0);
      TheSphereDistribution->setOuterRadius(1.0);
      TheSphereDistribution->setMinTheta(0.0);
      TheSphereDistribution->setMaxTheta(6.283185);
      TheSphereDistribution->setMinZ(-1.0);
      TheSphereDistribution->setMaxZ(1.0);
	  TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::VOLUME);
    endEditCP(TheSphereDistribution);

    return TheSphereDistribution;
}



FunctionPtr createStar2VelocityDistribution(void)
{
	 //Sphere Distribution
    LineDistribution3DPtr TheLineDistribution = LineDistribution3D::create();
    beginEditCP(TheLineDistribution);
 		TheLineDistribution->setPoint1(Pnt3f(0.0,-1.0,0.0));
		TheLineDistribution->setPoint2(Pnt3f(0.0,-1.0,0.0));
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

FunctionPtr createComStar2PositionDistribution(void)
{
    //Sphere Distribution
    SphereDistribution3DPtr TheSphereDistribution = SphereDistribution3D::create();
    beginEditCP(TheSphereDistribution);
      TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
      TheSphereDistribution->setInnerRadius(2.0);
      TheSphereDistribution->setOuterRadius(6.0);
      TheSphereDistribution->setMinTheta(0.0);
      TheSphereDistribution->setMaxTheta(6.283185);
      TheSphereDistribution->setMinZ(-1.0);
      TheSphereDistribution->setMaxZ(1.0);
	  TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::VOLUME);
    endEditCP(TheSphereDistribution);

    return TheSphereDistribution;
}



FunctionPtr createComStar2VelocityDistribution(void)
{
	 //Sphere Distribution
    LineDistribution3DPtr TheLineDistribution = LineDistribution3D::create();
    beginEditCP(TheLineDistribution);
 		TheLineDistribution->setPoint1(Pnt3f(-1.0,0.0,0.0));
		TheLineDistribution->setPoint2(Pnt3f(-1.0,0.0,0.0));
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


FunctionPtr createExplosionPositionDistribution(void)
{
    //Sphere Distribution
    SphereDistribution3DPtr TheSphereDistribution = SphereDistribution3D::create();
    beginEditCP(TheSphereDistribution);
      TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
      TheSphereDistribution->setInnerRadius(0.0);
      TheSphereDistribution->setOuterRadius(1.0);
      TheSphereDistribution->setMinTheta(0.0);
      TheSphereDistribution->setMaxTheta(6.283185);
      TheSphereDistribution->setMinZ(-1.0);
      TheSphereDistribution->setMaxZ(1.0);
	  TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::VOLUME);
    endEditCP(TheSphereDistribution);

    return TheSphereDistribution;
}

FunctionPtr createExplosionVelocityDistribution(void)
{
	 //Sphere Distribution
    LineDistribution3DPtr TheLineDistribution = LineDistribution3D::create();
    beginEditCP(TheLineDistribution);
 		TheLineDistribution->setPoint1(Pnt3f(0.0,-1.0,0.0));
		TheLineDistribution->setPoint2(Pnt3f(0.0,-1.0,0.0));
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


FunctionPtr createExplosion2PositionDistribution(void)
{
   
	//Disc Distribution
    DiscDistribution3DPtr TheDiscDistribution = DiscDistribution3D::create();
    beginEditCP(TheDiscDistribution);
      TheDiscDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
      TheDiscDistribution->setInnerRadius(10.0);
      TheDiscDistribution->setOuterRadius(15.0);
      TheDiscDistribution->setMinTheta(0.0);
      TheDiscDistribution->setMaxTheta(6.283185307);
      TheDiscDistribution->setNormal(Vec3f(0.0,1.0,0.0));
      TheDiscDistribution->setSurfaceOrEdge(DiscDistribution3D::SURFACE);
    endEditCP(TheDiscDistribution);


    return TheDiscDistribution;
}

FunctionPtr createExplosion2VelocityDistribution(void)
{
	 //Sphere Distribution
    LineDistribution3DPtr TheLineDistribution = LineDistribution3D::create();
    beginEditCP(TheLineDistribution);
 		TheLineDistribution->setPoint1(Pnt3f(0.0,-1.0,0.0));
		TheLineDistribution->setPoint2(Pnt3f(0.0,-1.0,0.0));
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

FunctionPtr createExplosion2ColorDistribution(void)
{
	 //Sphere Distribution
    LineDistribution3DPtr TheLineDistribution = LineDistribution3D::create();
    beginEditCP(TheLineDistribution);
 		TheLineDistribution->setPoint1(Pnt3f(1.0,0.0,0.0));
		TheLineDistribution->setPoint2(Pnt3f(1.0,0.0,0.0));
    endEditCP(TheLineDistribution);

	DataConverterPtr TheColor4fConverter = DataConverter::create();
	beginEditCP(TheColor4fConverter);
		TheColor4fConverter->setToType(&FieldDataTraits<Color4f>::getType());
	endEditCP(TheColor4fConverter);

	CompoundFunctionPtr TheColorDistribution = CompoundFunction::create();
	beginEditCP(TheColorDistribution);
		TheColorDistribution->getFunctions().push_back(TheLineDistribution);
		TheColorDistribution->getFunctions().push_back(TheColor4fConverter);
	endEditCP(TheColorDistribution);

    return TheColorDistribution;
}

FunctionPtr createComStarColorDistribution(void)
{
	 //Sphere Distribution
    LineDistribution3DPtr TheLineDistribution = LineDistribution3D::create();
    beginEditCP(TheLineDistribution);
 		TheLineDistribution->setPoint1(Pnt3f(0.5,0.5,1.0));
		TheLineDistribution->setPoint2(Pnt3f(0.0,0.0,1.0));
    endEditCP(TheLineDistribution);

	DataConverterPtr TheColor4fConverter = DataConverter::create();
	beginEditCP(TheColor4fConverter);
		TheColor4fConverter->setToType(&FieldDataTraits<Color4f>::getType());
	endEditCP(TheColor4fConverter);

	CompoundFunctionPtr TheColorDistribution = CompoundFunction::create();
	beginEditCP(TheColorDistribution);
		TheColorDistribution->getFunctions().push_back(TheLineDistribution);
		TheColorDistribution->getFunctions().push_back(TheColor4fConverter);
	endEditCP(TheColorDistribution);

    return TheColorDistribution;
}
