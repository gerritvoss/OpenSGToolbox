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

#include <OpenSG/Dynamics/OSGDataSplitter.h>
#include <OpenSG/Dynamics/OSGDataCombiner.h>
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
	
    TutorialWindowEventProducer->openWindow(Pnt2f(50,50),
                                        Vec2f(550,550),
                                        "OpenSG 01ParticleSystemDrawer Window");
										

    //Make The Distribution
    //Line Distribution
    LineDistribution3DPtr TheLineDistribution = LineDistribution3D::create();
    beginEditCP(TheLineDistribution);
      TheLineDistribution->setPoint1(Pnt3f(1.0,1.0,1.0));
      TheLineDistribution->setPoint2(Pnt3f(1.0,1.0,0.1));
    endEditCP(TheLineDistribution);
    LineDistribution3DPtr TheLineDistribution2 = LineDistribution3D::create();
    beginEditCP(TheLineDistribution2);
      TheLineDistribution2->setPoint1(Pnt3f(6.0,6.0,6.0));
      TheLineDistribution2->setPoint2(Pnt3f(2.0,2.0,2.0));
    endEditCP(TheLineDistribution2);
    
    //Box Distribution
    BoxDistribution3DPtr TheBoxDistribution = BoxDistribution3D::create();
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
    endEditCP(TheGaussianNormalDistribution);

    LineDistribution3D::Output0DataType::RawType ReturnValue;

    FunctionPtr TheDistribution = TheSphereDistribution;
    FunctionPtr TheInternalColorDistribution = TheLineDistribution;
    FunctionPtr TheInternalSizeDistribution = TheLineDistribution2;

	//Color3f Compound Function
	DataSplitterPtr TheDataSplitter = DataSplitter::create();
	DataConverterPtr TheColor3fConverter = DataConverter::create();
	beginEditCP(TheColor3fConverter);
		TheColor3fConverter->setToType(&FieldDataTraits<Color3f>::getType());
	endEditCP(TheColor3fConverter);
	
	CompoundFunctionPtr TheColorDistribution = CompoundFunction::create();
	beginEditCP(TheColorDistribution);
		TheColorDistribution->getFunctions().push_back(TheInternalColorDistribution);
		TheColorDistribution->getFunctions().push_back(TheColor3fConverter);
	endEditCP(TheColorDistribution);
	
	DataConverterPtr TheVec3fConverter = DataConverter::create();
	beginEditCP(TheVec3fConverter);
		TheVec3fConverter->setToType(&FieldDataTraits<Vec3f>::getType());
	endEditCP(TheVec3fConverter);
	
	CompoundFunctionPtr TheSizeDistribution = CompoundFunction::create();
	beginEditCP(TheSizeDistribution);
		TheSizeDistribution->getFunctions().push_back(TheInternalSizeDistribution);
		TheSizeDistribution->getFunctions().push_back(TheVec3fConverter);
	endEditCP(TheSizeDistribution);

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
    UInt32 NumParticlesToGenerate(5000);
	Color3f ColorReturnValue;
	Vec3f SizeReturnValue;
	Pnt3f PositionReturnValue;
    FunctionIOParameterVector EmptyParameters;
    for(UInt32 i(0) ; i< NumParticlesToGenerate ; ++i)
    {
        PositionReturnValue = 
            FunctionIOData<Pnt3f>::dcast(
            TheDistribution->evaluate(EmptyParameters).front().getDataPtr()
            )->getData();

		
        ColorReturnValue = 
			FunctionIOData<Color3f>::dcast(
            TheColorDistribution->evaluate(EmptyParameters).front().getDataPtr()
            )->getData();

		
        SizeReturnValue = 
			FunctionIOData<Vec3f>::dcast(
            TheSizeDistribution->evaluate(EmptyParameters).front().getDataPtr()
            )->getData();

		ExampleParticleSystem->addParticle(PositionReturnValue,Vec3f(0.0,0.0f,1.0f),Color4f(ColorReturnValue.red(),ColorReturnValue.green(),ColorReturnValue.blue(), 1.0), SizeReturnValue, -1.0f, Vec3f(0.0f,0.0f,0.0f),Vec3f(0.0f,0.0f,0.0f),0);
	
    }

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
