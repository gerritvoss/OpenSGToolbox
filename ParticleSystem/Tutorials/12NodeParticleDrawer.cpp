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

#include <OpenSG/ParticleSystem/OSGParticleSystem.h>
#include <OpenSG/ParticleSystem/OSGNodeParticleSystemCore.h>
#include <OpenSG/ParticleSystem/OSGCollectiveGravityParticleSystemAffector.h>

#include <OpenSG/Dynamics/OSGGaussianNormalDistribution1D.h>
#include <OpenSG/Dynamics/OSGCylinderDistribution3D.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

bool ExitApp = false;

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
	
    TutorialWindowEventProducer->openWindow(Pnt2f(0,0),
                                        Vec2f(1280,1024),
                                        "OpenSG 12NodeParticleDrawer Window");
									

	FunctionPtr PositionFunction = createPositionDistribution();
	FunctionPtr LifespanFunction = createLifespanDistribution();
	
	Pnt3f PositionReturnValue;
	Time LifespanReturnValue = -1;

	//Particle System
    FunctionIOParameterVector EmptyParameters;
    ParticleSystemPtr ExampleParticleSystem = osg::ParticleSystem::create();
	for(UInt32 i(0) ; i<200 ; ++i)//controls how many particles are created
	{
		if(PositionFunction != NullFC)
		{
			PositionReturnValue = 
				FunctionIOData<Pnt3f>::dcast(
				PositionFunction->evaluate(EmptyParameters).front().getDataPtr()
				)->getData();
		}
		if(LifespanFunction != NullFC)
		{
			LifespanReturnValue = 
				FunctionIOData<Real32>::dcast(
				LifespanFunction->evaluate(EmptyParameters).front().getDataPtr()
				)->getData();
		}

		ExampleParticleSystem->addParticle(
			PositionReturnValue,
			Vec3f(1.0f,0.0f,0.0f),
			Color4f(1.0,0.0,0.0,1.0), 
			Vec3f(1.0,1.0,1.0), 
			LifespanReturnValue, 
			Vec3f(0.0f,0.0f,0.0f), //Velocity
			Vec3f(0.0f,0.0f,0.0f)	//acceleration
			,0);
	}
    ExampleParticleSystem->attachUpdateListener(TutorialWindowEventProducer);

	NodePtr ParticlePrototypeNode = makeTorus(1.0,4.0,16,16);

	//Particle System Node
    NodeParticleSystemCorePtr NodeParticleNodeCore = osg::NodeParticleSystemCore::create();
    beginEditCP(NodeParticleNodeCore, NodeParticleSystemCore::SystemFieldMask | NodeParticleSystemCore::PrototypeNodeFieldMask);
		NodeParticleNodeCore->setSystem(ExampleParticleSystem);
		NodeParticleNodeCore->setPrototypeNode(ParticlePrototypeNode);
        NodeParticleNodeCore->setNormalSource(NodeParticleSystemCore::NORMAL_VELOCITY);
        NodeParticleNodeCore->setUpSource(NodeParticleSystemCore::UP_STATIC);
        NodeParticleNodeCore->setUp(Vec3f(0.0f,1.0f,0.0f));
    endEditCP(NodeParticleNodeCore, NodeParticleSystemCore::SystemFieldMask | NodeParticleSystemCore::PrototypeNodeFieldMask);
	
	NodePtr ParticleNode = osg::Node::create();
    beginEditCP(ParticleNode, Node::CoreFieldMask);
        ParticleNode->setCore(NodeParticleNodeCore);
    endEditCP(ParticleNode, Node::CoreFieldMask);

	//Create an CollectiveGravityParticleSystemAffector
	CollectiveGravityParticleSystemAffectorPtr ExampleCollectiveGravityParticleSystemAffector = osg::CollectiveGravityParticleSystemAffector::create();
	beginEditCP(ExampleCollectiveGravityParticleSystemAffector, CollectiveGravityParticleSystemAffector::ParticleMassFieldMask);
		ExampleCollectiveGravityParticleSystemAffector->setParticleMass(10000000000.0f);
	endEditCP(ExampleCollectiveGravityParticleSystemAffector, CollectiveGravityParticleSystemAffector::ParticleMassFieldMask);

	beginEditCP(ExampleParticleSystem, ParticleSystem::SystemAffectorsFieldMask);
		ExampleParticleSystem->getSystemAffectors().push_back(ExampleCollectiveGravityParticleSystemAffector);
	endEditCP(ExampleParticleSystem, ParticleSystem::SystemAffectorsFieldMask);


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
