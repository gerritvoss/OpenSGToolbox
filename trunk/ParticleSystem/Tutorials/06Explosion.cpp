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

#include <OpenSG/OSGBlendChunk.h>
#include <OpenSG/OSGTextureChunk.h>
#include <OpenSG/OSGImageFileHandler.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/ParticleSystem/OSGParticleSystem.h>
#include <OpenSG/ParticleSystem/OSGParticleSystemCore.h>
#include <OpenSG/ParticleSystem/OSGPointParticleSystemDrawer.h>

#include <OpenSG/Dynamics/OSGSphereDistribution3D.h>
#include <OpenSG/ParticleSystem/OSGQuadParticleSystemDrawer.h>
#include <OpenSG/ParticleSystem/OSGQuadParticleSystemDrawer.h>
#include <OpenSG/ParticleSystem/OSGBurstParticleGenerator.h>


#include <OpenSG/Dynamics/OSGDataConverter.h>
#include <OpenSG/Dynamics/OSGCompoundFunction.h>
#include <OpenSG/Dynamics/OSGGaussianNormalDistribution1D.h>
#include <OpenSG/Dynamics/OSGCylinderDistribution3D.h>
#include <OpenSG/Dynamics/OSGLineDistribution3D.h>
//#include <OpenSG/Dynamics/OSGSizeDistribution3D.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);
void ClickToGenerate(const MouseEventPtr e);

FunctionPtr createPositionDistribution(void);
FunctionPtr createLifespanDistribution(void);
FunctionPtr createVelocityDistribution(void);
FunctionPtr createVelocityDistribution2(void);
FunctionPtr createAccelerationDistribution(void);
FunctionPtr createSizeDistribution(void);



ParticleSystemPtr Example1ParticleSystem;
ParticleSystemPtr Example2ParticleSystem;
QuadParticleSystemDrawerPtr Example1ParticleSystemDrawer;
QuadParticleSystemDrawerPtr Example2ParticleSystemDrawer;
BurstParticleGeneratorPtr ExampleBurstGenerator;
BurstParticleGeneratorPtr Example2BurstGenerator;




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

	   if(e->getKey() == KeyEvent::KEY_B)//generate particles when clicked
	   {
		  //Attach the Generator to the Particle System
				beginEditCP(Example1ParticleSystem, ParticleSystem::GeneratorsFieldMask);
					Example1ParticleSystem->getGenerators().push_back(ExampleBurstGenerator);
				endEditCP(Example1ParticleSystem, ParticleSystem::GeneratorsFieldMask);

				beginEditCP(Example2ParticleSystem, ParticleSystem::GeneratorsFieldMask);
					Example2ParticleSystem->getGenerators().push_back(Example2BurstGenerator);
				endEditCP(Example2ParticleSystem, ParticleSystem::GeneratorsFieldMask);


	   }
   }

   virtual void keyReleased(const KeyEventPtr e)
   {
   }

   virtual void keyTyped(const KeyEventPtr e)
   {
	   UInt32 CHANGE_SOURCE;
	   if(e->getKey()== KeyEvent::KEY_P)
	   {
		   
		   CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_POSITION_CHANGE;
	   }
		
	   else if(e->getKey()== KeyEvent::KEY_C)
	   {
		   CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_VELOCITY_CHANGE;
	   }

	    else if(e->getKey()== KeyEvent::KEY_V)
	   {
		   CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_VELOCITY;
	   }
	   
	    else if(e->getKey()== KeyEvent::KEY_A)
	   {
		   CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_ACCELERATION;
	   }
	   
	   else  if(e->getKey()== KeyEvent::KEY_N)
	   {
		   CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_PARTICLE_NORMAL;
	   }
	   
	    else if(e->getKey()== KeyEvent::KEY_D)
	   {
		   CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_VIEW_POSITION;
	   }
	   
	    else if(e->getKey()== KeyEvent::KEY_S)
	   {
		   CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_STATIC;
	   }

	   else  if(e->getKey()== KeyEvent::KEY_W)
	   {
			CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_VIEW_DIRECTION;
	   }
	   else {
		   return;
			}
	beginEditCP(Example1ParticleSystemDrawer);
		Example1ParticleSystemDrawer->setNormalSource(CHANGE_SOURCE);
	endEditCP(Example1ParticleSystemDrawer);

   }
};

void ClickToGenerate(const MouseEventPtr e)
{
	

}

class TutorialMouseListener : public MouseListener
{
  public:
    virtual void mouseClicked(const MouseEventPtr e)
    {
		if(e->getButton()== MouseEvent::BUTTON1)
		{

			
		}

		if(e->getButton()== MouseEvent::BUTTON3)
		{

		}

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
	TextureChunkPtr QuadTextureChunk = TextureChunk::create();
    ImagePtr LoadedImage = ImageFileHandler::the().read("Data/Checker.jpg");    
    beginEditCP(QuadTextureChunk, TextureChunk::ImageFieldMask);
        QuadTextureChunk->setImage(LoadedImage);
    endEditCP(QuadTextureChunk, TextureChunk::ImageFieldMask);

	MaterialChunkPtr PSMaterialChunk = MaterialChunk::create();
	beginEditCP(PSMaterialChunk);
		PSMaterialChunk->setAmbient(Color4f(0.3f,0.3f,0.3f,1.0f));
		PSMaterialChunk->setDiffuse(Color4f(0.7f,0.7f,0.7f,1.0f));
		PSMaterialChunk->setSpecular(Color4f(0.9f,0.9f,0.9f,1.0f));
		PSMaterialChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);
	endEditCP(PSMaterialChunk);

	ChunkMaterialPtr PSMaterial = ChunkMaterial::create();
	beginEditCP(PSMaterial, ChunkMaterial::ChunksFieldMask);
		PSMaterial->addChunk(QuadTextureChunk);
		PSMaterial->addChunk(PSMaterialChunk);
	endEditCP(PSMaterial, ChunkMaterial::ChunksFieldMask);

	//Particle System Material 2
	TextureChunkPtr QuadTextureChunk2 = TextureChunk::create();
    ImagePtr LoadedImage2 = ImageFileHandler::the().read("Data/Checker.jpg");    
    beginEditCP(QuadTextureChunk2, TextureChunk::ImageFieldMask);
        QuadTextureChunk2->setImage(LoadedImage2);
    endEditCP(QuadTextureChunk2, TextureChunk::ImageFieldMask);

	MaterialChunkPtr PSMaterialChunk2 = MaterialChunk::create();
	beginEditCP(PSMaterialChunk2);
		PSMaterialChunk2->setAmbient(Color4f(0.3f,0.3f,0.3f,1.0f));
		PSMaterialChunk2->setDiffuse(Color4f(0.7f,0.7f,0.7f,1.0f));
		PSMaterialChunk2->setSpecular(Color4f(0.9f,0.9f,0.9f,1.0f));
		PSMaterialChunk2->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);
	endEditCP(PSMaterialChunk2);

	ChunkMaterialPtr PSMaterial2 = ChunkMaterial::create();
	beginEditCP(PSMaterial2, ChunkMaterial::ChunksFieldMask);
		PSMaterial2->addChunk(QuadTextureChunk2);
		PSMaterial2->addChunk(PSMaterialChunk2);
	endEditCP(PSMaterial2, ChunkMaterial::ChunksFieldMask);


	//Particle System
		
    Example1ParticleSystem = osg::ParticleSystem::create();
	Example1ParticleSystem->attachUpdateListener(TutorialWindowEventProducer);

	Example2ParticleSystem = osg::ParticleSystem::create();
	Example2ParticleSystem->attachUpdateListener(TutorialWindowEventProducer);

    FunctionIOParameterVector EmptyParameters;

	//Particle System Drawer
	 Example1ParticleSystemDrawer = osg::QuadParticleSystemDrawer::create();
	 Example2ParticleSystemDrawer = osg::QuadParticleSystemDrawer::create();
	
	

	
	//Attach the function objects to the Generator
	 //Generator 1 
	ExampleBurstGenerator = osg::BurstParticleGenerator::create();
	beginEditCP(ExampleBurstGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask | BurstParticleGenerator::SizeFunctionFieldMask);
		ExampleBurstGenerator->setPositionFunction(createPositionDistribution());
		//ExampleBurstGenerator->setLifespanFunction(createLifespanDistribution());
		ExampleBurstGenerator->setBurstAmount(50.0);
		ExampleBurstGenerator->setVelocityFunction(createVelocityDistribution());
		//ExampleBurstGenerator->setAccelerationFunction(createAccelerationDistribution());
		ExampleBurstGenerator->setSizeFunction(createSizeDistribution());
	endEditCP(ExampleBurstGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask | BurstParticleGenerator::SizeFunctionFieldMask);
	 
	//Generator 2
	Example2BurstGenerator = osg::BurstParticleGenerator::create();
	beginEditCP(Example2BurstGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask | BurstParticleGenerator::SizeFunctionFieldMask);
		Example2BurstGenerator->setPositionFunction(createPositionDistribution());
		//Example2BurstGenerator->setLifespanFunction(createLifespanDistribution());
		Example2BurstGenerator->setBurstAmount(50.0);
		Example2BurstGenerator->setVelocityFunction(createVelocityDistribution2());
		//Example2BurstGenerator->setAccelerationFunction(createAccelerationDistribution());
		Example2BurstGenerator->setSizeFunction(createSizeDistribution());
	endEditCP(Example2BurstGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask | BurstParticleGenerator::SizeFunctionFieldMask);
		


	//Particle System Node
    ParticleSystemCorePtr ParticleNodeCore = osg::ParticleSystemCore::create();
    beginEditCP(ParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
		ParticleNodeCore->setSystem(Example1ParticleSystem);
		ParticleNodeCore->setDrawer(Example1ParticleSystemDrawer);
		ParticleNodeCore->setMaterial(PSMaterial);
    endEditCP(ParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
    
	NodePtr ParticleNode = osg::Node::create();
    beginEditCP(ParticleNode, Node::CoreFieldMask);
        ParticleNode->setCore(ParticleNodeCore);
    endEditCP(ParticleNode, Node::CoreFieldMask);
	
	//Particle System Node2
	ParticleSystemCorePtr ParticleNodeCore2 = osg::ParticleSystemCore::create();
    beginEditCP(ParticleNodeCore2, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
		ParticleNodeCore2->setSystem(Example2ParticleSystem);
		ParticleNodeCore2->setDrawer(Example2ParticleSystemDrawer);
		ParticleNodeCore2->setMaterial(PSMaterial2);
    endEditCP(ParticleNodeCore2, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
	
	NodePtr ParticleNode2 = osg::Node::create();
    beginEditCP(ParticleNode2, Node::CoreFieldMask);
        ParticleNode2->setCore(ParticleNodeCore2);
    endEditCP(ParticleNode2, Node::CoreFieldMask);
	
	//Ground Node
	NodePtr GoundNode = makePlane(30.0,30.0,10,10);

	Matrix GroundTransformation;
	GroundTransformation.setRotate(Quaternion(Vec3f(1.0f,0.0,0.0), -3.14195f));
	TransformPtr GroundTransformCore = Transform::create();
    beginEditCP(GroundTransformCore, Transform::MatrixFieldMask);
		GroundTransformCore->setMatrix(GroundTransformation);
    endEditCP(GroundTransformCore, Transform::MatrixFieldMask);

	NodePtr GroundTransformNode = Node::create();
	beginEditCP(GroundTransformNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
		GroundTransformNode->setCore(GroundTransformCore);
        GroundTransformNode->addChild(GoundNode);
	endEditCP(GroundTransformNode, Node::CoreFieldMask | Node::ChildrenFieldMask);


    // Make Main Scene Node and add the Torus
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
        scene->addChild(ParticleNode);
		scene->addChild(ParticleNode2);
        scene->addChild(GroundTransformNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    mgr->setRoot(scene);

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "06Explosion");

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

FunctionPtr createVelocityDistribution(void)
{
   

	 //Sphere Distribution
    SphereDistribution3DPtr TheSphereDistribution = SphereDistribution3D::create();
    beginEditCP(TheSphereDistribution);
      TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
      TheSphereDistribution->setInnerRadius(3.0);
      TheSphereDistribution->setOuterRadius(10.0);
      TheSphereDistribution->setMinTheta(-3.141950);
      TheSphereDistribution->setMaxTheta(3.141950);
      TheSphereDistribution->setMinZ(0.0);
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

FunctionPtr createVelocityDistribution2(void)
{
   

	 //Sphere Distribution
    SphereDistribution3DPtr TheSphereDistribution = SphereDistribution3D::create();
    beginEditCP(TheSphereDistribution);
      TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
      TheSphereDistribution->setInnerRadius(6.0);
      TheSphereDistribution->setOuterRadius(10.0);
      TheSphereDistribution->setMinTheta(-3.141950);
      TheSphereDistribution->setMaxTheta(3.141950);
      TheSphereDistribution->setMinZ(0.0);
      TheSphereDistribution->setMaxZ(1.0);
	  TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::VOLUME);
    endEditCP(TheSphereDistribution);

	DataConverterPtr TheVec3fConverter = DataConverter::create();
	beginEditCP(TheVec3fConverter);
		TheVec3fConverter->setToType(&FieldDataTraits<Vec3f>::getType());
	endEditCP(TheVec3fConverter);

	CompoundFunctionPtr TheVelocityDistribution2 = CompoundFunction::create();
	beginEditCP(TheVelocityDistribution2);
		TheVelocityDistribution2->getFunctions().push_back(TheSphereDistribution);
		TheVelocityDistribution2->getFunctions().push_back(TheVec3fConverter);
	endEditCP(TheVelocityDistribution2);

    return TheVelocityDistribution2;
}

FunctionPtr createLifespanDistribution(void)
{
    GaussianNormalDistribution1DPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    beginEditCP(TheLifespanDistribution);
      TheLifespanDistribution->setMean(30.0f);
      TheLifespanDistribution->setStandardDeviation(5.0);
    endEditCP(TheLifespanDistribution);
	
	return TheLifespanDistribution;
}

FunctionPtr createAccelerationDistribution(void)
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

FunctionPtr createSizeDistribution(void)
{


	 //Sphere Distribution
    LineDistribution3DPtr TheLineDistribution = LineDistribution3D::create();
    beginEditCP(TheLineDistribution);
      TheLineDistribution->setPoint1(Pnt3f(5.0,5.0,1.0));
	  TheLineDistribution->setPoint2(Pnt3f(10.0,10.0,1.0));
    endEditCP(TheLineDistribution);

	DataConverterPtr TheVec3fConverter = DataConverter::create();
	beginEditCP(TheVec3fConverter);
		TheVec3fConverter->setToType(&FieldDataTraits<Vec3f>::getType());
	endEditCP(TheVec3fConverter);

	CompoundFunctionPtr TheSizeDistribution = CompoundFunction::create();
	beginEditCP(TheSizeDistribution);
		TheSizeDistribution->getFunctions().push_back(TheLineDistribution);
		TheSizeDistribution->getFunctions().push_back(TheVec3fConverter);
	endEditCP(TheSizeDistribution);

	return NullFC;
}
