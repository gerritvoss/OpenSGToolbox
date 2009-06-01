// Simple demonstration of XML file input/output

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/Input/OSGWindowUtils.h>
// Input
#include <OpenSG/Input/OSGKeyListener.h>
#include <OpenSG/Input/OSGWindowAdapter.h>

#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGGradientBackground.h>
#include <OpenSG/OSGPolygonForeground.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGViewport.h>

#include <OpenSG/OSGBlendChunk.h>
#include <OpenSG/OSGPointChunk.h>
#include <OpenSG/OSGDepthChunk.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialChunk.h>
#include <OpenSG/ParticleSystem/OSGParticleSystem.h>
#include <OpenSG/ParticleSystem/OSGParticleSystemCore.h>
#include <OpenSG/ParticleSystem/OSGPointParticleSystemDrawer.h>
#include <OpenSG/ParticleSystem/OSGQuadParticleSystemDrawer.h>
#include <OpenSG/ParticleSystem/OSGRateParticleGenerator.h>
#include <OpenSG/Dynamics/OSGDataConverter.h>
#include <OpenSG/Dynamics/OSGCompoundFunction.h>
#include <OpenSG/Dynamics/OSGLineDistribution3D.h>
#include <OpenSG/Dynamics/OSGGaussianNormalDistribution1D.h>
#include <OpenSG/Dynamics/OSGDiscDistribution3D.h>

#include <OpenSG/Toolbox/OSGFCFileHandler.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

SimpleSceneManager *mgr;

bool ExitApp = false;

NodePtr createScene(void);

FunctionPtr createPositionDistribution(void);
FunctionPtr createLifespanDistribution(void);
FunctionPtr createVelocityDistribution(void);


// mouse and keyboard support
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEvent& e)
   {
       if(e.getKey() == KeyEvent::KEY_Q && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           ExitApp = true;
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

// Initialize GLUT & OpenSG and set up the scene
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
	//Add Key Listener
    TutorialKeyListener TheKeyListener;
    TutorialWindowEventProducer->addKeyListener(&TheKeyListener);
	//Add Mouse Listeners
    TutorialMouseListener TheTutorialMouseListener;
    TutorialMouseMotionListener TheTutorialMouseMotionListener;
    TutorialWindowEventProducer->addMouseListener(&TheTutorialMouseListener);
    TutorialWindowEventProducer->addMouseMotionListener(&TheTutorialMouseMotionListener);

	
	    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
	// open window
	TutorialWindowEventProducer->openWindow(Pnt2f(0,0),
                                        Vec2f(1280,1024),
                                        "OpenSG 15 Field Container File Type I/O");

	/* Set up complete, now working on XML export and import */
	
	//Create some Field Containers
	NodePtr Root = createScene();
	FCFileType::FCPtrStore Containers;
	//attach scene root to container
	Containers.insert(Root);

	FCFileType::FCTypeVector IgnoreTypes;
	//IgnoreTypes.push_back(Node::getClassType().getId()); //ignored for now

	//Save the Field Containers to a xml file
	FCFileHandler::the()->write(Containers,Path("./TestFieldContainers.xml"),IgnoreTypes);

	// read the file we just created and store to new container
	FCFileType::FCPtrStore NewContainers;
	NewContainers = FCFileHandler::the()->read(Path("./TestFieldContainers.xml"));

	// find root node from container, attach update listeners to particle systems
	std::vector<NodePtr> RootNodes;
    for(FCFileType::FCPtrStore::iterator Itor = NewContainers.begin() ; Itor != NewContainers.end() ; ++Itor)
    {
        if( (*Itor)->getType() == Node::getClassType() &&
            Node::Ptr::dcast(*Itor)->getParent() == NullFC)
        {
            RootNodes.push_back(Node::Ptr::dcast(*Itor));
        }
		else if( (*Itor)->getType() == ParticleSystem::getClassType())
		{
			ParticleSystemPtr ExampleParticleSystems = ParticleSystem::Ptr::dcast(*Itor);
			ExampleParticleSystems->attachUpdateListener(TutorialWindowEventProducer);
		}
    }


	// get root node that was extracted from XML file
	// should check this to make sure a root node was found
	NodePtr scene = RootNodes[0];

	// set root node
	mgr->setRoot(scene);

    // Show the whole Scene
    mgr->showAll();

	//loop
    while(!ExitApp)
    {
        TutorialWindowEventProducer->update();
        TutorialWindowEventProducer->draw();
    }

    osgExit();

    return 0;
}


NodePtr createScene(void)
{
	//Particle System Material Chunks
	PointChunkPtr PSPointChunk = PointChunk::create();
	beginEditCP(PSPointChunk);
		PSPointChunk->setSize(25.0f);
		PSPointChunk->setSmooth(true);
	endEditCP(PSPointChunk);

	BlendChunkPtr PSBlendChunk = BlendChunk::create();
	beginEditCP(PSBlendChunk);
		PSBlendChunk->setSrcFactor(GL_SRC_ALPHA);
		PSBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
	endEditCP(PSBlendChunk);

	MaterialChunkPtr PSMaterialChunkChunk = MaterialChunk::create();
	beginEditCP(PSMaterialChunkChunk);
		PSMaterialChunkChunk->setAmbient(Color4f(0.5f,0.5f,0.5f,0.3f));
		PSMaterialChunkChunk->setDiffuse(Color4f(0.7f,0.7f,0.7f,0.3f));
		PSMaterialChunkChunk->setSpecular(Color4f(0.9f,0.9f,0.9f,0.3f));
		PSMaterialChunkChunk->setColorMaterial(GL_NONE);
	endEditCP(PSMaterialChunkChunk);

		//enable depth test
	DepthChunkPtr PSDepthChunk = DepthChunk::create();

	ChunkMaterialPtr PSMaterial = ChunkMaterial::create();
	beginEditCP(PSMaterial, ChunkMaterial::ChunksFieldMask);
		PSMaterial->addChunk(PSPointChunk);
		PSMaterial->addChunk(PSMaterialChunkChunk);
		PSMaterial->addChunk(PSBlendChunk);
		PSMaterial->addChunk(PSDepthChunk);
	endEditCP(PSMaterial, ChunkMaterial::ChunksFieldMask);

	// make Particle System
    ParticleSystemPtr ExampleParticleSystem = osg::ParticleSystem::create();
		for(UInt32 i(0) ; i<10 ; ++i)
	{
		ExampleParticleSystem->addParticle(Pnt3f(i,i,i),
			Vec3f(0.0,0.0f,1.0f),
			Color4f(1.0,1.0,1.0,0.5), 
			Vec3f(1.0,1.0,1.0), 
			-1, // lifespan
			Vec3f(0.0,0.0,0.0), //Velocity
			Vec3f(0.0,0.0,0.0)
			,0);
	}
	
	//Create a Rate Particle Generator
	RateParticleGeneratorPtr ExampleGenerator = osg::RateParticleGenerator::create();

	//Attach the function objects to the Generator
	beginEditCP(ExampleGenerator, RateParticleGenerator::PositionFunctionFieldMask | RateParticleGenerator::LifespanFunctionFieldMask | RateParticleGenerator::GenerationRateFieldMask);
		ExampleGenerator->setPositionFunction(createPositionDistribution());
		ExampleGenerator->setLifespanFunction(createLifespanDistribution());
		ExampleGenerator->setGenerationRate(50.0);
		ExampleGenerator->setVelocityFunction(createVelocityDistribution());
	endEditCP(ExampleGenerator, RateParticleGenerator::PositionFunctionFieldMask | RateParticleGenerator::LifespanFunctionFieldMask | RateParticleGenerator::GenerationRateFieldMask);

	//attach generator to particle system
	beginEditCP(ExampleParticleSystem, ParticleSystem::GeneratorsFieldMask);
		ExampleParticleSystem->getGenerators().push_back(ExampleGenerator);
	endEditCP(ExampleParticleSystem, ParticleSystem::GeneratorsFieldMask);

	// particle system drawer
	QuadParticleSystemDrawerPtr ExampleQuadParticleSystemDrawer = osg::QuadParticleSystemDrawer::create();
	
	//Particle System Node
	ParticleSystemCorePtr ParticleNodeCore = osg::ParticleSystemCore::create();
    beginEditCP(ParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
		ParticleNodeCore->setSystem(ExampleParticleSystem);
		ParticleNodeCore->setDrawer(ExampleQuadParticleSystemDrawer);
		ParticleNodeCore->setMaterial(PSMaterial);
		// enable sorting
		ParticleNodeCore->setSortingMode(ParticleSystemCore::BACK_TO_FRONT);
    endEditCP(ParticleNodeCore, ParticleSystemCore::SystemFieldMask | ParticleSystemCore::DrawerFieldMask | ParticleSystemCore::MaterialFieldMask);
    
	NodePtr ParticleNode = osg::Node::create();
    beginEditCP(ParticleNode, Node::CoreFieldMask);
        ParticleNode->setCore(ParticleNodeCore);
    endEditCP(ParticleNode, Node::CoreFieldMask);

    // create root node, attach particle system 
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
        scene->addChild(ParticleNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
	
	return scene;

}

FunctionPtr createPositionDistribution(void)
{
     //Disc Distribution
    DiscDistribution3DPtr TheDiscDistribution = DiscDistribution3D::create();
    beginEditCP(TheDiscDistribution);
      TheDiscDistribution->setCenter(Pnt3f(0.0,0.0,0.0));
      TheDiscDistribution->setInnerRadius(10.0);
      TheDiscDistribution->setOuterRadius(20.0);
      TheDiscDistribution->setMinTheta(0.0);
      TheDiscDistribution->setMaxTheta(6.283185307);
      TheDiscDistribution->setNormal(Vec3f(1.0,0.0,0.0));
      TheDiscDistribution->setSurfaceOrEdge(DiscDistribution3D::EDGE);
    endEditCP(TheDiscDistribution);

    return TheDiscDistribution;
}

FunctionPtr createLifespanDistribution(void)
{
    GaussianNormalDistribution1DPtr TheLifespanDistribution = GaussianNormalDistribution1D::create();
    beginEditCP(TheLifespanDistribution);
      TheLifespanDistribution->setMean(20.0f);
      TheLifespanDistribution->setStandardDeviation(3.0);
    endEditCP(TheLifespanDistribution);
	
	return TheLifespanDistribution;
}

FunctionPtr createVelocityDistribution(void)
{
	 //Line Distribution
    LineDistribution3DPtr TheLineDistribution = LineDistribution3D::create();
    beginEditCP(TheLineDistribution);
 		TheLineDistribution->setPoint1(Pnt3f(0.0,0.0,0.0));
		TheLineDistribution->setPoint2(Pnt3f(30.0,30.0,30.0));
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