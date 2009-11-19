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
#include <OpenSG/OSGLineChunk.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/ParticleSystem/OSGParticleSystem.h>
#include <OpenSG/ParticleSystem/OSGParticleSystemCore.h>
#include <OpenSG/ParticleSystem/OSGPointParticleSystemDrawer.h>
#include <OpenSG/ParticleSystem/OSGLineParticleSystemDrawer.h>

#include <OpenSG/ParticleSystem/OSGGaussianNormalDistribution1D.h>

#include <OpenSG/ParticleSystem/OSGLineDistribution3D.h>
#include <OpenSG/ParticleSystem/OSGBoxDistribution3D.h>
#include <OpenSG/ParticleSystem/OSGDiscDistribution3D.h>
#include <OpenSG/ParticleSystem/OSGCylinderDistribution3D.h>
#include <OpenSG/ParticleSystem/OSGSphereDistribution3D.h>
#include <OpenSG/ParticleSystem/OSGGaussianNormalDistribution3D.h>
#include <OpenSG/ParticleSystem/OSGTriDistribution3D.h>
// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

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

Distribution3DPtr createPositionDistribution(void);
Distribution3DPtr createNormalDistribution(void);
Distribution3DPtr createColorDistribution(void);
Distribution3DPtr createSizeDistribution(void);
Distribution1DPtr createLifespanDistribution(void);
Distribution3DPtr createVelocityDistribution(void);
Distribution3DPtr createAccelerationDistribution(void);

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
	LineChunkPtr PSLineChunk = LineChunk::create();
	beginEditCP(PSLineChunk);
		PSLineChunk->setWidth(1.0f);
	endEditCP(PSLineChunk);

	BlendChunkPtr PSBlendChunk = BlendChunk::create();
	beginEditCP(PSBlendChunk);
		PSBlendChunk->setSrcFactor(GL_SRC_ALPHA);
		PSBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
	beginEditCP(PSBlendChunk);

	MaterialChunkPtr PSMaterialChunk = MaterialChunk::create();
	beginEditCP(PSMaterialChunk);
		PSMaterialChunk->setAmbient(Color4f(0.3f,0.3f,0.3f,1.0f));
		PSMaterialChunk->setDiffuse(Color4f(0.7f,0.7f,0.7f,1.0f));
		PSMaterialChunk->setSpecular(Color4f(0.9f,0.9f,0.9f,1.0f));
		PSMaterialChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);
		PSMaterialChunk->setLit(false);
	endEditCP(PSMaterialChunk);

	ChunkMaterialPtr PSMaterial = ChunkMaterial::create();
	beginEditCP(PSMaterial, ChunkMaterial::ChunksFieldMask);
		PSMaterial->addChunk(PSLineChunk);
		PSMaterial->addChunk(PSMaterialChunk);
		PSMaterial->addChunk(PSBlendChunk);
	endEditCP(PSMaterial, ChunkMaterial::ChunksFieldMask);

	//Particle System
    ParticleSystemPtr ExampleParticleSystem = osg::ParticleSystem::create();
    ExampleParticleSystem->attachUpdateListener(TutorialWindowEventProducer);


	//Create the particles
    UInt32 NumParticlesToGenerate(2500);

	Distribution3DPtr PositionDistribution = createPositionDistribution();
	Distribution3DPtr NormalDistribution = createNormalDistribution();
	Distribution3DPtr ColorDistribution = createColorDistribution();
	Distribution3DPtr SizeDistribution = createSizeDistribution();
	Distribution1DPtr LifespanDistribution = createLifespanDistribution();
	Distribution3DPtr VelocityDistribution = createVelocityDistribution();
	Distribution3DPtr AccelerationDistribution = createAccelerationDistribution();

	Pnt3f PositionReturnValue;
	Vec3f NormalReturnValue = Vec3f(0.0,0.0f,1.0f);
	Color4f ColorReturnValue = Color4f(1.0,1.0f,1.0f, 1.0f);
	Vec3f SizeReturnValue;
	Time LifespanReturnValue = -1;
	Vec3f VelocityReturnValue;
	Vec3f AccelerationReturnValue;


    for(UInt32 i(0) ; i< NumParticlesToGenerate ; ++i)
    {
		if(PositionDistribution != NullFC)
		{
			PositionReturnValue.setValue(PositionDistribution->generate().getValues());
		}

		
		if(ColorDistribution != NullFC)
		{
            Vec3f ColorRGB = ColorDistribution->generate();
			ColorReturnValue.setValuesRGBA(ColorRGB[0],ColorRGB[1],ColorRGB[2],1.0f);
		}

		
		if(SizeDistribution != NullFC)
		{
			SizeReturnValue = SizeDistribution->generate();
		}

		if(LifespanDistribution != NullFC)
		{
			LifespanReturnValue = LifespanDistribution->generate();
		}
		if(VelocityDistribution != NullFC)
		{
			VelocityReturnValue = VelocityDistribution->generate();
		}

		ExampleParticleSystem->addParticle(PositionReturnValue,
			NormalReturnValue,
			ColorReturnValue,
			SizeReturnValue,
			LifespanReturnValue,
			VelocityReturnValue,
			AccelerationReturnValue
			);
	
    }

	//Particle System Drawer
	LineParticleSystemDrawerPtr ExampleParticleSystemDrawer = osg::LineParticleSystemDrawer::create();
	beginEditCP(ExampleParticleSystemDrawer);
		ExampleParticleSystemDrawer->setLineDirectionSource(LineParticleSystemDrawer::DIRECTION_VELOCITY);
		ExampleParticleSystemDrawer->setLineLengthSource(LineParticleSystemDrawer::LENGTH_SIZE_X);
		ExampleParticleSystemDrawer->setEndPointFading(Vec3f(0.0f,1.0f));
	endEditCP(ExampleParticleSystemDrawer);

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


    // Make Main Scene Node and add the Torus
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
        scene->addChild(ParticleNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    mgr->setRoot(scene);

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "02DynamicDistribution");

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
    //Make The Distribution
    
    //Box Distribution
    /*BoxDistribution3DPtr TheBoxDistribution = BoxDistribution3D::create();
    beginEditCP(TheBoxDistribution);
      TheBoxDistribution->setMinPoint(Pnt3f(-10.0,-10.0,-10.0));
      TheBoxDistribution->setMaxPoint(Pnt3f(10.0,10.0,10.0));
      TheBoxDistribution->setSurfaceOrVolume(BoxDistribution3D::SURFACE);
    endEditCP(TheBoxDistribution);

    //Disc Distribution
    DiscDistribution3DPtr TheDiscDistribution = DiscDistribution3D::create();
    beginEditCP(TheDiscDistribution);
      TheDiscDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
      TheDiscDistribution->setInnerRadius(10.0);
      TheDiscDistribution->setOuterRadius(20.0);
      TheDiscDistribution->setMinTheta(0.0);
      TheDiscDistribution->setMaxTheta(6.283185307);
      TheDiscDistribution->setNormal(Vec3f(0.0,0.0,1.0));
      TheDiscDistribution->setSurfaceOrEdge(DiscDistribution3D::SURFACE);
    endEditCP(TheDiscDistribution);

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
      TheCylinderDistribution->setSurfaceOrVolume(CylinderDistribution3D::VOLUME);
    endEditCP(TheCylinderDistribution); 
    
    //Tri Distribution
    TriDistribution3DPtr TheTriDistribution = TriDistribution3D::create();
    beginEditCP(TheTriDistribution);
      TheTriDistribution->setPoint1(Pnt3f(0.0,0.0,0.0));
      TheTriDistribution->setPoint2(Pnt3f(-50.0,1000.0,0.0));
      TheTriDistribution->setPoint3(Pnt3f(50.0,1000.0,0.0));
      TheTriDistribution->setPoint3(Pnt3f(50.0,1000.0,0.0));
      TheTriDistribution->setSurfaceOrEdge(TriDistribution3D::SURFACE);
    endEditCP(TheTriDistribution);

    //GaussianNormal Distribution
    GaussianNormalDistribution3DPtr TheGaussianNormalDistribution = GaussianNormalDistribution3D::create();
    beginEditCP(TheGaussianNormalDistribution);
      TheGaussianNormalDistribution->setMean(Pnt3f(0.0,0.0,0.0));
      TheGaussianNormalDistribution->setStandardDeviationX(100.0);
      TheGaussianNormalDistribution->setStandardDeviationY(100.0);
      TheGaussianNormalDistribution->setStandardDeviationZ(100.0);
    endEditCP(TheGaussianNormalDistribution);*/

    
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

Distribution3DPtr createNormalDistribution(void)
{
    //Sphere Distribution
    SphereDistribution3DPtr TheSphereDistribution = SphereDistribution3D::create();
    beginEditCP(TheSphereDistribution);
      TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
      TheSphereDistribution->setInnerRadius(500.0);
      TheSphereDistribution->setOuterRadius(5000.0);
      TheSphereDistribution->setMinTheta(0.0);
      TheSphereDistribution->setMaxTheta(6.283185);
      TheSphereDistribution->setMinZ(-1.0);
      TheSphereDistribution->setMaxZ(1.0);
      TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::VOLUME);
    endEditCP(TheSphereDistribution);

    return TheSphereDistribution;
}

Distribution3DPtr createColorDistribution(void)
{
    //Line Distribution
    LineDistribution3DPtr TheLineDistribution = LineDistribution3D::create();
    beginEditCP(TheLineDistribution);
      TheLineDistribution->setPoint1(Pnt3f(1.0,1.0,1.0));
      TheLineDistribution->setPoint2(Pnt3f(1.0,1.0,0.1));
    endEditCP(TheLineDistribution);

	return TheLineDistribution;
}

Distribution3DPtr createSizeDistribution(void)
{
    LineDistribution3DPtr TheLineDistribution = LineDistribution3D::create();
    beginEditCP(TheLineDistribution);
      TheLineDistribution->setPoint1(Pnt3f(3.0,3.0,3.0));
      TheLineDistribution->setPoint2(Pnt3f(1.0,1.0,1.0));
    endEditCP(TheLineDistribution);

	return TheLineDistribution;
}
Distribution1DPtr createLifespanDistribution(void)
{
    GaussianNormalDistribution1DPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    beginEditCP(TheLifespanDistribution);
      TheLifespanDistribution->setMean(30.0f);
      TheLifespanDistribution->setStandardDeviation(3.0);
    endEditCP(TheLifespanDistribution);
	
	return TheLifespanDistribution;
}
Distribution3DPtr createVelocityDistribution(void)
{
    //Sphere Distribution
    SphereDistribution3DPtr TheSphereDistribution = SphereDistribution3D::create();
    beginEditCP(TheSphereDistribution);
      TheSphereDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
      TheSphereDistribution->setInnerRadius(100.0);
      TheSphereDistribution->setOuterRadius(150.0);
      TheSphereDistribution->setMinTheta(0.0);
      TheSphereDistribution->setMaxTheta(6.283185);
      TheSphereDistribution->setMinZ(-1.0);
      TheSphereDistribution->setMaxZ(1.0);
      TheSphereDistribution->setSurfaceOrVolume(SphereDistribution3D::VOLUME);
    endEditCP(TheSphereDistribution);

    return TheSphereDistribution;
}

Distribution3DPtr createAccelerationDistribution(void)
{

	return NullFC;
}
