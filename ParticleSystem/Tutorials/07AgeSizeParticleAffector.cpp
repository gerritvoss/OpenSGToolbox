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
#include <OpenSG/Input/OSGWindowAdapter.h>

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
#include <OpenSG/ParticleSystem/OSGAgeSizeParticleAffector.h>

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

bool ExitApp = false;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);
void ClickToGenerate(const MouseEvent& e);

FunctionPtr createPositionDistribution(void);
FunctionPtr createLifespanDistribution(void);
FunctionPtr createVelocityDistribution(void);
FunctionPtr createAccelerationDistribution(void);
FunctionPtr createSizeDistribution(void);



ParticleSystemPtr ExampleParticleSystem;
QuadParticleSystemDrawerPtr ExampleParticleSystemDrawer;
BurstParticleGeneratorPtr ExampleBurstGenerator;
AgeSizeParticleAffectorPtr ExampleAgeSizeParticleAffector;


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
		  //Attach the Generator to the Particle System
		   beginEditCP(ExampleParticleSystem, ParticleSystem::GeneratorsFieldMask |ParticleSystem::AffectorsFieldMask);
					ExampleParticleSystem->getGenerators().push_back(ExampleBurstGenerator);
				endEditCP(ExampleParticleSystem, ParticleSystem::GeneratorsFieldMask |ParticleSystem::AffectorsFieldMask);
	   }
   }

   virtual void keyReleased(const KeyEvent& e)
   {
   }

   virtual void keyTyped(const KeyEvent& e)
   {
	   UInt32 CHANGE_SOURCE;
	   if(e.getKey()== KeyEvent::KEY_P)
	   {
		   
		   CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_POSITION_CHANGE;
	   }
		
	   else if(e.getKey()== KeyEvent::KEY_C)
	   {
		   CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_VELOCITY_CHANGE;
	   }

	    else if(e.getKey()== KeyEvent::KEY_V)
	   {
		   CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_VELOCITY;
	   }
	   
	    else if(e.getKey()== KeyEvent::KEY_A)
	   {
		   CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_ACCELERATION;
	   }
	   
	   else  if(e.getKey()== KeyEvent::KEY_N)
	   {
		   CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_PARTICLE_NORMAL;
	   }
	   
	    else if(e.getKey()== KeyEvent::KEY_D)
	   {
		   CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_VIEW_POSITION;
	   }
	   
	    else if(e.getKey()== KeyEvent::KEY_S)
	   {
		   CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_STATIC;
	   }

	   else  if(e.getKey()== KeyEvent::KEY_W)
	   {
			CHANGE_SOURCE = QuadParticleSystemDrawer::NORMAL_VIEW_DIRECTION;
	   }
	   else {
		   return;
			}
	beginEditCP(ExampleParticleSystemDrawer);
		ExampleParticleSystemDrawer->setNormalSource(CHANGE_SOURCE);
	endEditCP(ExampleParticleSystemDrawer);

   }
};

void ClickToGenerate(const MouseEvent& e)
{
	

}

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
		if(e.getButton()== MouseEvent::BUTTON1)
		{

			
		}

		if(e.getButton()== MouseEvent::BUTTON3)
		{

		}

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
                                        "OpenSG 05QuadParticleDrawer Window");
										

	//Particle System Material
	TextureChunkPtr QuadTextureChunk = TextureChunk::create();
    ImagePtr LoadedImage = ImageFileHandler::the().read("Data/DragonPhase.jpg");    
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



	//Affector
	ExampleAgeSizeParticleAffector = osg::AgeSizeParticleAffector::create();
	beginEditCP(ExampleAgeSizeParticleAffector,AgeSizeParticleAffector::AgesFieldMask,AgeSizeParticleAffector::SizesFieldMask);
			//ages
			ExampleAgeSizeParticleAffector->getAges().push_back(0.05);
			ExampleAgeSizeParticleAffector->getAges().push_back(0.2);
			ExampleAgeSizeParticleAffector->getAges().push_back(0.36);
			ExampleAgeSizeParticleAffector->getAges().push_back(0.7);
			ExampleAgeSizeParticleAffector->getAges().push_back(0.8);
			ExampleAgeSizeParticleAffector->getAges().push_back(1.1);

			//sizes
			ExampleAgeSizeParticleAffector->getSizes().push_back(Vec3f(1.0,0.5,1.0));
			ExampleAgeSizeParticleAffector->getSizes().push_back(Vec3f(2.0,0.5,3.0));
			ExampleAgeSizeParticleAffector->getSizes().push_back(Vec3f(3.0,3.0,3.0));
			ExampleAgeSizeParticleAffector->getSizes().push_back(Vec3f(6.0,6.0,6.0));
			ExampleAgeSizeParticleAffector->getSizes().push_back(Vec3f(2.0,3.0,1.0));
			ExampleAgeSizeParticleAffector->getSizes().push_back(Vec3f(1.0,1.0,1.0));
	endEditCP(ExampleAgeSizeParticleAffector,AgeSizeParticleAffector::AgesFieldMask,AgeSizeParticleAffector::SizesFieldMask);

	//Particle System
    ExampleParticleSystem = osg::ParticleSystem::create();
	ExampleParticleSystem->attachUpdateListener(TutorialWindowEventProducer);
	beginEditCP(ExampleParticleSystem, ParticleSystem::AffectorsFieldMask);
		ExampleParticleSystem->getAffectors().push_back(ExampleAgeSizeParticleAffector);
	endEditCP(ExampleParticleSystem, ParticleSystem::AffectorsFieldMask);
	
			

    FunctionIOParameterVector EmptyParameters;

	//Particle System Drawer
	ExampleParticleSystemDrawer = osg::QuadParticleSystemDrawer::create();


	 ExampleBurstGenerator = osg::BurstParticleGenerator::create();
	//Attach the function objects to the Generator
	beginEditCP(ExampleBurstGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask | BurstParticleGenerator::SizeFunctionFieldMask);
		ExampleBurstGenerator->setPositionFunction(createPositionDistribution());
		ExampleBurstGenerator->setLifespanFunction(createLifespanDistribution());
		ExampleBurstGenerator->setBurstAmount(6.0);
		ExampleBurstGenerator->setVelocityFunction(createVelocityDistribution());
		//ExampleBurstGenerator->setAccelerationFunction(createAccelerationDistribution());
		ExampleBurstGenerator->setSizeFunction(createSizeDistribution());
	endEditCP(ExampleBurstGenerator, BurstParticleGenerator::PositionFunctionFieldMask | BurstParticleGenerator::LifespanFunctionFieldMask | BurstParticleGenerator::SizeFunctionFieldMask);
	
	//Particle System Node
    ParticleSystemCorePtr ParticleNodeCore = osg::ParticleSystemCore::create();
    beginEditCP(ParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
		ParticleNodeCore->setSystem(ExampleParticleSystem);
		ParticleNodeCore->setDrawer(ExampleParticleSystemDrawer);
		ParticleNodeCore->setMaterial(PSMaterial);
    endEditCP(ParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
    
	NodePtr ParticleNode = osg::Node::create();
    beginEditCP(ParticleNode, Node::CoreFieldMask);
        ParticleNode->setCore(ParticleNodeCore);
    endEditCP(ParticleNode, Node::CoreFieldMask);

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
        scene->addChild(GroundTransformNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    mgr->setRoot(scene);

    // Show the whole Scene
    mgr->showAll();


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
	Pnt3f pt1 = (0.0,-30.0,0.0);

	 //Sphere Distribution
    LineDistribution3DPtr TheLineDistribution = LineDistribution3D::create();
    beginEditCP(TheLineDistribution);
      TheLineDistribution->setPoint1(pt1);
	  TheLineDistribution->setPoint2(pt1);
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
	Pnt3f pt1 = (5.0,5.0,1.0), pt2 = (10.0,10.0,1.0);


	 //Sphere Distribution
    LineDistribution3DPtr TheLineDistribution = LineDistribution3D::create();
    beginEditCP(TheLineDistribution);
      TheLineDistribution->setPoint1(pt1);
	  TheLineDistribution->setPoint2(pt2);
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