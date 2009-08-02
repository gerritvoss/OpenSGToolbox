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
#include <OpenSG/ParticleSystem/OSGQuadParticleSystemDrawer.h>
#include <OpenSG/ParticleSystem/OSGDistanceFadeParticleAffector.h>
#include <OpenSG/ParticleSystem/OSGDistanceAttractRepelParticleAffector.h>


#include <OpenSG/Dynamics/OSGGaussianNormalDistribution1D.h>
#include <OpenSG/Dynamics/OSGCylinderDistribution3D.h>

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
	MaterialChunkPtr PSMaterialChunkChunk = MaterialChunk::create();
	beginEditCP(PSMaterialChunkChunk);
		PSMaterialChunkChunk->setAmbient(Color4f(0.3f,0.3f,0.3f,1.0f));
		PSMaterialChunkChunk->setDiffuse(Color4f(0.7f,0.7f,0.7f,1.0f));
		PSMaterialChunkChunk->setSpecular(Color4f(0.9f,0.9f,0.9f,1.0f));
		PSMaterialChunkChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);
	endEditCP(PSMaterialChunkChunk);

	ChunkMaterialPtr PSMaterial = ChunkMaterial::create();
	beginEditCP(PSMaterial, ChunkMaterial::ChunksFieldMask);
		PSMaterial->addChunk(PSMaterialChunkChunk);
	endEditCP(PSMaterial, ChunkMaterial::ChunksFieldMask);

	FunctionPtr PositionFunction = createPositionDistribution();
	
	Pnt3f PositionReturnValue;

	//Particle System
    FunctionIOParameterVector EmptyParameters;
    ParticleSystemPtr ExampleParticleSystem = osg::ParticleSystem::create();
	for(UInt32 i(0) ; i<500 ; ++i)//controls how many particles are created
	{
		if(PositionFunction != NullFC)
		{
			PositionReturnValue = 
				FunctionIOData<Pnt3f>::dcast(
				PositionFunction->evaluate(EmptyParameters).front().getDataPtr()
				)->getData();
		}

		ExampleParticleSystem->addParticle(
			PositionReturnValue,
			Vec3f(0.0f,0.0f,1.0f),
			Color4f(1.0,0.0,0.0,1.0), 
			Vec3f(1.0,1.0,1.0), 
			-1, 
			Vec3f(0.0f,0.0f,0.0f), //Velocity
			Vec3f(0.0f,0.0f,0.0f)	//acceleration
										   );
	}
    ExampleParticleSystem->attachUpdateListener(TutorialWindowEventProducer);

	//Particle System Drawer
	QuadParticleSystemDrawerPtr ExampleParticleSystemDrawer = osg::QuadParticleSystemDrawer::create();
	



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

	
	//AttractionNode
    TransformPtr AttractionCore = osg::Transform::create();
	Matrix AttractTransform;
	AttractTransform.setTranslate(0.0f, 0.0,0.0);

    beginEditCP(AttractionCore, Transform::MatrixFieldMask);
		AttractionCore->setMatrix(AttractTransform);
    endEditCP(AttractionCore, Transform::MatrixFieldMask);

    NodePtr AttractionNode = osg::Node::create();
    beginEditCP(AttractionNode, Node::CoreFieldMask);
		AttractionNode->setCore(AttractionCore);
    endEditCP(AttractionNode, Node::CoreFieldMask);

    // Make Main Scene Node and add the Torus
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
        scene->addChild(ParticleNode);
        scene->addChild(AttractionNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    mgr->setRoot(scene);

    // Show the whole Scene
    //mgr->showAll();
	mgr->getNavigator()->set(Pnt3f(0.0,0.0,500.0), Pnt3f(0.0,0.0,0.0), Vec3f(0.0,1.0,0.0));
	mgr->getNavigator()->setMotionFactor(1.0f);
	mgr->getCamera()->setNear(0.1f);
	mgr->getCamera()->setFar(1000.0f);

	DistanceAttractRepelParticleAffectorPtr ExampleDistanceAttractRepelParticleAffector = osg::DistanceAttractRepelParticleAffector::create();
	beginEditCP(ExampleDistanceAttractRepelParticleAffector,DistanceAttractRepelParticleAffector::MinDistanceFieldMask | DistanceAttractRepelParticleAffector::MaxDistanceFieldMask | DistanceAttractRepelParticleAffector::QuadraticFieldMask | DistanceAttractRepelParticleAffector::LinearFieldMask | DistanceAttractRepelParticleAffector::ConstantFieldMask | DistanceAttractRepelParticleAffector::ParticleSystemNodeFieldMask | DistanceAttractRepelParticleAffector::DistanceFromSourceFieldMask |	DistanceAttractRepelParticleAffector::DistanceFromNodeFieldMask);
		
			ExampleDistanceAttractRepelParticleAffector->setMinDistance(0.0);
			ExampleDistanceAttractRepelParticleAffector->setMaxDistance(1000.0);
			ExampleDistanceAttractRepelParticleAffector->setQuadratic(0.0);
			ExampleDistanceAttractRepelParticleAffector->setLinear(100.0);
			ExampleDistanceAttractRepelParticleAffector->setConstant(0.0);
			ExampleDistanceAttractRepelParticleAffector->setParticleSystemNode(ParticleNode);
			ExampleDistanceAttractRepelParticleAffector->setDistanceFromSource(DistanceAttractRepelParticleAffector::DISTANCE_FROM_NODE);
			ExampleDistanceAttractRepelParticleAffector->setDistanceFromNode(AttractionNode);

	endEditCP(ExampleDistanceAttractRepelParticleAffector,DistanceAttractRepelParticleAffector::MinDistanceFieldMask | DistanceAttractRepelParticleAffector::MaxDistanceFieldMask | DistanceAttractRepelParticleAffector::QuadraticFieldMask | DistanceAttractRepelParticleAffector::LinearFieldMask | DistanceAttractRepelParticleAffector::ConstantFieldMask | DistanceAttractRepelParticleAffector::ParticleSystemNodeFieldMask | DistanceAttractRepelParticleAffector::DistanceFromSourceFieldMask |	DistanceAttractRepelParticleAffector::DistanceFromNodeFieldMask);

	beginEditCP(ExampleParticleSystem, ParticleSystem::AffectorsFieldMask);
		ExampleParticleSystem->getAffectors().push_back(ExampleDistanceAttractRepelParticleAffector);
	endEditCP(ExampleParticleSystem, ParticleSystem::AffectorsFieldMask);

    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "11DistanceAttractRepelParticleAffector");

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
      TheLifespanDistribution->setMean(05.0f);
      TheLifespanDistribution->setStandardDeviation(10.0);
    endEditCP(TheLifespanDistribution);
	
	return TheLifespanDistribution;
}
