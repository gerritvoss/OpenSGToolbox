// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGSimpleGeometry.h>
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
#include <OpenSG/ParticleSystem/OSGPointParticleSystemDrawer.h>

#include <OpenSG/Dynamics/OSGLineDistribution3D.h>
#include <OpenSG/Dynamics/OSGBoxDistribution3D.h>
#include <OpenSG/Dynamics/OSGDiscDistribution3D.h>
#include <OpenSG/Dynamics/OSGCylinderDistribution3D.h>
#include <OpenSG/Dynamics/OSGSphereDistribution3D.h>
#include <OpenSG/Dynamics/OSGGaussianNormalDistribution3D.h>
#include <OpenSG/Dynamics/OSGTriDistribution3D.h>
#include <OpenSG/Dynamics/OSGGeoSurfaceDistribution3D.h>
#include <OpenSG/Dynamics/OSGGeoVolumeDistribution3D.h>
#include <OpenSG/Dynamics/OSGPerlinNoiseDistribution1D.h>
#include <OpenSG/Dynamics/OSGPerlinNoiseDistribution2D.h>
#include <OpenSG/Dynamics/OSGPerlinNoiseDistribution3D.h>

#include <OpenSG/Dynamics/OSGDataSplitter.h>
#include <OpenSG/Dynamics/OSGDataCombiner.h>
#include <OpenSG/Dynamics/OSGDataConverter.h>
#include <OpenSG/Dynamics/OSGCompoundFunction.h>
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
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

	// Set up Window
    TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

	beginEditCP(TutorialWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);
		TutorialWindowEventProducer->setUseCallbackForDraw(true);
		TutorialWindowEventProducer->setUseCallbackForReshape(true);
	endEditCP(TutorialWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);

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
	PSBlendChunk->setSrcFactor(GL_SRC_ALPHA);
	PSBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

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
		PSMaterial->addChunk(PSPointChunk);
		PSMaterial->addChunk(PSMaterialChunk);
		PSMaterial->addChunk(PSBlendChunk);
	endEditCP(PSMaterial, ChunkMaterial::ChunksFieldMask);

	//Particle System
    ParticleSystemPtr ExampleParticleSystem = osg::ParticleSystem::create();
	Color3f ColorReturnValue;
	Vec3f SizeReturnValue;
	Pnt3f PositionReturnValue;
    FunctionIOParameterVector input;

	//Make The Distribution

	// Three dimensional:  Looks like an object of varying density.

	//PerlinNoiseDistribution3DPtr PerlinNoise3D = PerlinNoiseDistribution3D::create();
	//beginEditCP(PerlinNoise3D);
	//	PerlinNoise3D->setFrequency(1);
	//	PerlinNoise3D->setOctaves(6);
	//	PerlinNoise3D->setPersistance(0.25);
	//	PerlinNoise3D->setAmplitude(1);
	//	PerlinNoise3D->setInterpolationType(PerlinNoiseDistribution2D::LINEAR);
	//	PerlinNoise3D->setPhase(Vec3f(3.0,-6.2,1.0));
	//	PerlinNoise3D->setUseSmoothing(true);
	//endEditCP(PerlinNoise3D);

 //   for(Real32 i(0) ; i < 7.5f ; i += 0.25f)
 //   {
 //      for(Real32 j(0) ; j < 7.5f ; j += 0.25f)
	//   {	
	//		for(Real32 k(0); k < 7.5f ; k += 0.25f)
	//		{
	//			input.clear();
	//			input.push_back(FunctionIOParameter(std::string("Value"), new FunctionIOData<Pnt3f>(Pnt3f(i,j,k))));
	//			Real32 tmp = FunctionIOData<Real32>::dcast(PerlinNoise3D->evaluate(input).front().getDataPtr())->getData();
	//			tmp = osg::osgClamp<Real32>(0.0f,std::abs(tmp),1.0f);
	//			ExampleParticleSystem->addParticle(Pnt3f(i,j,k), // pos
	//				Vec3f(0.0,0.0f,1.0f), // normal
	//				Color4f(0.3,1.0,0.0, tmp), // color
	//				Vec3f(1.0,1.0,1.0), 
	//				-1.0f, 
	//				Vec3f(0.0f,0.0f,0.0f),
	//				Vec3f(0.0f,0.0f,0.0f),0);
	//		}
	//   }
	//
 //   }
	
	// 2-dimensional: Let's make the mountain!

	PerlinNoiseDistribution2DPtr PerlinNoise2D = PerlinNoiseDistribution2D::create();
	beginEditCP(PerlinNoise2D);
		PerlinNoise2D->setFrequency(0.2);
		PerlinNoise2D->setOctaves(4);
		PerlinNoise2D->setPersistance(0.15);
		PerlinNoise2D->setAmplitude(15.0);
		PerlinNoise2D->setInterpolationType(PerlinNoiseDistribution2D::COSINE);
		PerlinNoise2D->setUseSmoothing(true);
		PerlinNoise2D->setPhase(Vec2f(15.0,-26.3));
	endEditCP(PerlinNoise2D);

    for(Real32 i(0) ; i < 40 ; i += 0.25f)
    {
       for(Real32 j(0) ; j < 40 ; j += 0.25f)
	   {	
			input.clear();
			input.push_back(FunctionIOParameter(std::string("Value"), new FunctionIOData<Pnt2f>(Pnt2f(i,j))));
			Real32 tmp = FunctionIOData<Real32>::dcast(PerlinNoise2D->evaluate(input).front().getDataPtr())->getData();
			
			ExampleParticleSystem->addParticle(Pnt3f(i,tmp,j), // pos
				Vec3f(0.0,0.0f,1.0f), // normal
				Color4f(0.6f,1.0f,0.3f, 1.0), // color
				Vec3f(1.0,1.0,1.0), 
				-1.0f, 
				Vec3f(0.0f,0.0f,0.0f),
				Vec3f(0.0f,0.0f,0.0f));
	   }
	
    }

	// 1 dimensional:  The stock market.
		
	//PerlinNoiseDistribution1DPtr PerlinNoise1D = PerlinNoiseDistribution1D::create();
	//beginEditCP(PerlinNoise1D);
	//	PerlinNoise1D->setFrequency(1.55);
	//	PerlinNoise1D->setOctaves(6);
	//	PerlinNoise1D->setPersistance(0.39);
	//	PerlinNoise1D->setAmplitude(4);
	//	PerlinNoise1D->setInterpolationType(PerlinNoiseDistribution2D::COSINE);
	//	PerlinNoise1D->setUseSmoothing(true);
	//	PerlinNoise1D->setPhase(0.0);
	//endEditCP(PerlinNoise1D);

 //  for(Real32 j(0) ; j < 40 ; j += 0.05f)
 //  {	
	//	input.clear();
	//	input.push_back(FunctionIOParameter(std::string("Value"), new FunctionIOData<Real32>(j)));
	//	Real32 tmp = FunctionIOData<Real32>::dcast(PerlinNoise1D->evaluate(input).front().getDataPtr())->getData();
	//	
	//	ExampleParticleSystem->addParticle(Pnt3f(j,tmp,0), // pos
	//		Vec3f(0.0,0.0f,1.0f), // normal
	//		Color4f(0.6f,1.0f,0.3f, 1.0), // color
	//		Vec3f(1.0,1.0,1.0), 
	//		-1.0f, 
	//		Vec3f(0.0f,0.0f,0.0f),
	//		Vec3f(0.0f,0.0f,0.0f),0);
 //  }

	//Particle System Drawer
	PointParticleSystemDrawerPtr ExampleParticleSystemDrawer = osg::PointParticleSystemDrawer::create();

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
            "02BlendedGeometry");

    //Main Loop
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
