// OpenSG Tutorial Example: Hello World
//
// Minimalistic OpenSG program
// 
// This is the shortest useful OpenSG program 
// (if you remove all the comments ;)
//
// It shows how to use OpenSG together with GLUT to create a little
// interactive rootNode viewer.
//

// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// Methods to create simple geometry: boxes, spheres, tori etc.
#include "OSGSimpleGeometry.h"

// A little helper to simplify rootNode management and interaction
#include "OSGSimpleSceneManager.h"

#include "OSGSimpleMaterial.h"

#include "OSGComponentTransform.h"
#include "OSGTransform.h"
#include "OSGTypeFactory.h"
#include "OSGSimpleStatisticsForeground.h"


#include "OSGFieldContainerFactory.h"
#include "OSGNameAttachment.h"
#include "OSGSceneFileHandler.h"

// Input
#include "OSGKeyListener.h"
#include "OSGWindowUtils.h"

//Physics
#include "OSGPhysics.h"

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE


// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);
PhysicsBodyUnrecPtr buildSphere(void);
PhysicsBodyUnrecPtr buildBox(void);
void makeExplosion(Pnt3f Location, Real32 Force);

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerUnrecPtr TutorialWindow;

PhysicsHandlerUnrecPtr physHandler;
PhysicsWorldUnrecPtr physicsWorld;
PhysicsSpaceUnrecPtr physicsSpace;

//just for hierarchy
NodeUnrecPtr spaceGroupNode;
std::vector<PhysicsBodyUnrecPtr> allPhysicsBodies;

NodeUnrecPtr rootNode;

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventUnrecPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
       {
           TutorialWindow->closeWindow();
       }
       switch(e->getKey())
       {
       case KeyEvent::KEY_S:
            {
                allPhysicsBodies.push_back(buildSphere());
            }
            break;
       case KeyEvent::KEY_B:
            {
                allPhysicsBodies.push_back(buildBox());
            }
            break;
       case KeyEvent::KEY_E:
           makeExplosion(Pnt3f(0.0f,0.0f,-5.0f), 1280.0f);
           break;
       case KeyEvent::KEY_1:
           makeExplosion(Pnt3f(0.0f,0.0f,-5.0f), 20.0f);
           break;
       case KeyEvent::KEY_2:
           makeExplosion(Pnt3f(0.0f,0.0f,-5.0f), 80.0f);
           break;
       case KeyEvent::KEY_3:
           makeExplosion(Pnt3f(0.0f,0.0f,-5.0f), 320.0f);
           break;
       case KeyEvent::KEY_4:
           makeExplosion(Pnt3f(0.0f,0.0f,-5.0f), 1280.0f);
           break;
       case KeyEvent::KEY_5:
           makeExplosion(Pnt3f(0.0f,0.0f,-5.0f), 5120.0f);
           break;
       case KeyEvent::KEY_6:
           makeExplosion(Pnt3f(0.0f,0.0f,-5.0f), 20480.0f);
           break;
       }
   }

   virtual void keyReleased(const KeyEventUnrecPtr e)
   {
   }

   virtual void keyTyped(const KeyEventUnrecPtr e)
   {
   }
};

class TutorialMouseListener : public MouseListener
{
  public:
    virtual void mouseClicked(const MouseEventUnrecPtr e)
    {
    }
    virtual void mouseEntered(const MouseEventUnrecPtr e)
    {
    }
    virtual void mouseExited(const MouseEventUnrecPtr e)
    {
    }
    virtual void mousePressed(const MouseEventUnrecPtr e)
    {
            mgr->mouseButtonPress(e->getButton(), e->getLocation().x(), e->getLocation().y());
    }
    virtual void mouseReleased(const MouseEventUnrecPtr e)
    {
           mgr->mouseButtonRelease(e->getButton(), e->getLocation().x(), e->getLocation().y());
    }
};

class TutorialMouseMotionListener : public MouseMotionListener
{
  public:
    virtual void mouseMoved(const MouseEventUnrecPtr e)
    {
            mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
    }

    virtual void mouseDragged(const MouseEventUnrecPtr e)
    {
            mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
    }
};

void makeExplosion(Pnt3f Location, Real32 Impulse)
{
    for(UInt32 i(0) ; i<allPhysicsBodies.size() ; ++i)
    {
        Vec3f Direction(allPhysicsBodies[i]->getPosition()-Location.subZero());

        Real32 Distance(Direction.length());
        Direction.normalize();

        allPhysicsBodies[i]->addForce(physicsWorld->impulseToForce(physHandler->getStepSize(), Direction*Impulse*(1.0f/Distance)));
        //The bodies need to be enabled because they may be auto-disabled when they
        //come to rest
        //The bodies are not re-enabled untill a new collision is detected
        allPhysicsBodies[i]->setEnable(true);
    }
}

// Initialize GLUT & OpenSG and set up the rootNode
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindow = createNativeWindow();
    TutorialWindow->initWindow();

    TutorialWindow->setDisplayCallback(display);
    TutorialWindow->setReshapeCallback(reshape);

    TutorialKeyListener TheKeyListener;
    TutorialWindow->addKeyListener(&TheKeyListener);
    TutorialMouseListener TheTutorialMouseListener;
    TutorialMouseMotionListener TheTutorialMouseMotionListener;
    TutorialWindow->addMouseListener(&TheTutorialMouseListener);
    TutorialWindow->addMouseMotionListener(&TheTutorialMouseMotionListener);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

	
    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindow);

    //Make Torus Node
    NodeUnrecPtr TorusNode = makeTorus(.5, 2, 32, 32);

    //Make Main Scene Node
	NodeUnrecPtr scene = makeCoredNode<Group>();
    setName(scene, "scene");
    rootNode = Node::create();
    setName(rootNode, "rootNode");
    ComponentTransformUnrecPtr Trans;
    Trans = ComponentTransform::create();
        rootNode->setCore(Trans);
 
        // add the torus as a child
        rootNode->addChild(scene);

    //Setup Physics Scene
    physicsWorld = PhysicsWorld::create();
        physicsWorld->setWorldContactSurfaceLayer(0.005);
        physicsWorld->setAutoDisableFlag(1);
        physicsWorld->setAutoDisableTime(0.75);
        physicsWorld->setWorldContactMaxCorrectingVel(100.0);
        physicsWorld->setGravity(Vec3f(0.0, 0.0, -9.81));

    //physicsSpace = PhysicsSimpleSpace::create();
    //physicsSpace = PhysicsQuadTreeSpace::create();
    //physicsSpace = PhysicsHashSpace::create();
    physicsSpace = PhysicsSweepAndPruneSpace::create();

    CollisionContactParametersUnrecPtr DefaultCollisionParams = CollisionContactParameters::createEmpty();
        DefaultCollisionParams->setMode(dContactApprox1 | dContactBounce);
        DefaultCollisionParams->setMu(0.3);
        DefaultCollisionParams->setMu2(0.0);
        DefaultCollisionParams->setBounce(0.2);
        DefaultCollisionParams->setBounceSpeedThreshold(0.1);
        DefaultCollisionParams->setSoftCFM(0.1);
        DefaultCollisionParams->setSoftERP(0.2);
        DefaultCollisionParams->setMotion1(0.0);
        DefaultCollisionParams->setMotion2(0.0);
        DefaultCollisionParams->setMotionN(0.0);
        DefaultCollisionParams->setSlip1(0.0);
        DefaultCollisionParams->setSlip2(0.0);

        physicsSpace->setDefaultCollisionParameters(DefaultCollisionParams);

    physHandler = PhysicsHandler::create();
        physHandler->setWorld(physicsWorld);
        physHandler->pushToSpaces(physicsSpace);
        physHandler->setUpdateNode(rootNode);
    physHandler->attachUpdateProducer(TutorialWindow->editEventProducer());
    

        rootNode->addAttachment(physHandler);    
        rootNode->addAttachment(physicsWorld);
        rootNode->addAttachment(physicsSpace);


	/************************************************************************/
	/* create spaces, geoms and bodys                                                                     */
	/************************************************************************/
    //create a group for our space
    GroupUnrecPtr spaceGroup;
	spaceGroupNode = makeCoredNode<Group>(&spaceGroup);
    //create the ground plane
    GeometryUnrecPtr plane;
	NodeUnrecPtr planeNode = makeBox(30.0, 30.0, 1.0, 1, 1, 1);
    plane = dynamic_cast<Geometry*>(planeNode->getCore());
    //and its Material
	SimpleMaterialUnrecPtr plane_mat = SimpleMaterial::create();
		plane_mat->setAmbient(Color3f(0.7,0.7,0.7));
		plane_mat->setDiffuse(Color3f(0.9,0.6,1.0));
	    plane->setMaterial(plane_mat);


    //create Physical Attachments
	PhysicsBoxGeomUnrecPtr planeGeom = PhysicsBoxGeom::create();
        planeGeom->setLengths(Vec3f(30.0, 30.0, 1.0));
        //add geoms to space for collision
        planeGeom->setSpace(physicsSpace);

	//add Attachments to nodes...
	    spaceGroupNode->addAttachment(physicsSpace);
        spaceGroupNode->addChild(planeNode);

        planeNode->addAttachment(planeGeom);
    
	    scene->addChild(spaceGroupNode);

    //Create Statistics Foreground
    SimpleStatisticsForegroundUnrecPtr PhysicsStatForeground = SimpleStatisticsForeground::create();
        PhysicsStatForeground->setSize(25);
        PhysicsStatForeground->setColor(Color4f(0,1,0,0.7));
        PhysicsStatForeground->addElement(PhysicsHandler::statPhysicsTime, 
            "Physics time: %.3f s");
        PhysicsStatForeground->addElement(PhysicsHandler::statCollisionTime, 
            "Collision time: %.3f s");
        PhysicsStatForeground->addElement(PhysicsHandler::statSimulationTime, 
            "Simulation time: %.3f s");
        PhysicsStatForeground->addElement(PhysicsHandler::statNCollisions, 
            "%d collisions");
        PhysicsStatForeground->addElement(PhysicsHandler::statNCollisionTests, 
            "%d collision tests");
        PhysicsStatForeground->addElement(PhysicsHandler::statNPhysicsSteps, 
            "%d simulation steps per frame");

    // tell the manager what to manage
    mgr->setRoot  (rootNode);

    mgr->getWindow()->getPort(0)->addForeground(PhysicsStatForeground);
    physHandler->setStatistics(PhysicsStatForeground->getCollector());

    // show the whole rootNode
    mgr->showAll();
    
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
            WinSize,
            "05Explosion");

    //Enter main Loop
    TutorialWindow->mainLoop();

    osgExit();

    return 0;
}

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


//////////////////////////////////////////////////////////////////////////
//! build a box
//////////////////////////////////////////////////////////////////////////
PhysicsBodyUnrecPtr buildBox(void)
{
    Vec3f Lengths((Real32)(rand()%2)+1.0, (Real32)(rand()%2)+1.0, (Real32)(rand()%2)+1.0);
    Matrix m;
    //create OpenSG mesh
    GeometryUnrecPtr box;
    NodeUnrecPtr boxNode = makeBox(Lengths.x(), Lengths.y(), Lengths.z(), 1, 1, 1);
    box = dynamic_cast<Geometry*>(boxNode->getCore());
    SimpleMaterialUnrecPtr box_mat = SimpleMaterial::create();
        box_mat->setAmbient(Color3f(0.0,0.0,0.0));
        box_mat->setDiffuse(Color3f(0.0,1.0 ,0.0));
        box->setMaterial(box_mat);
    TransformUnrecPtr boxTrans;
    NodeUnrecPtr boxTransNode = makeCoredNode<Transform>(&boxTrans);
    m.setIdentity();
    Real32 randX = (Real32)(rand()%10)-5.0;
    Real32 randY = (Real32)(rand()%10)-5.0;
    m.setTranslate(randX, randY, 10.0);
        boxTrans->setMatrix(m);

    //create ODE data
    PhysicsBodyUnrecPtr boxBody = PhysicsBody::create(physicsWorld);
        boxBody->setPosition(Vec3f(randX, randY, 10.0));
    boxBody->setBoxMass(1.0, Lengths.x(), Lengths.y(), Lengths.z());

    PhysicsBoxGeomUnrecPtr boxGeom = PhysicsBoxGeom::create();
        boxGeom->setBody(boxBody);
        boxGeom->setSpace(physicsSpace);
        boxGeom->setLengths(Lengths);

    //add attachments
        boxNode->addAttachment(boxGeom);
        boxTransNode->addAttachment(boxBody);
        boxTransNode->addChild(boxNode);

    //add to SceneGraph
        spaceGroupNode->addChild(boxTransNode);

    commitChanges();
    return boxBody;
}

//////////////////////////////////////////////////////////////////////////
//! build a sphere
//////////////////////////////////////////////////////////////////////////
PhysicsBodyUnrecPtr buildSphere(void)
{
    Real32 Radius((Real32)(rand()%2)*0.5+0.5);
    Matrix m;
    //create OpenSG mesh
    GeometryUnrecPtr sphere;
    NodeUnrecPtr sphereNode = makeSphere(2, Radius);
    sphere = dynamic_cast<Geometry*>(sphereNode->getCore());
    SimpleMaterialUnrecPtr sphere_mat = SimpleMaterial::create();
    sphere_mat->setAmbient(Color3f(0.0,0.0,0.0));
    sphere_mat->setDiffuse(Color3f(0.0,0.0,1.0));
    sphere->setMaterial(sphere_mat);
    TransformUnrecPtr sphereTrans;
    NodeUnrecPtr sphereTransNode = makeCoredNode<Transform>(&sphereTrans);
    m.setIdentity();
    Real32 randX = (Real32)(rand()%10)-5.0;
    Real32 randY = (Real32)(rand()%10)-5.0;
    m.setTranslate(randX, randY, 10.0);
    sphereTrans->setMatrix(m);
    //create ODE data
    PhysicsBodyUnrecPtr sphereBody = PhysicsBody::create(physicsWorld);
        sphereBody->setPosition(Vec3f(randX, randY, 10.0));
        sphereBody->setLinearDamping(0.0001);
        sphereBody->setAngularDamping(0.0001);
    sphereBody->setSphereMass(1.0,Radius);

    PhysicsSphereGeomUnrecPtr sphereGeom = PhysicsSphereGeom::create();
        sphereGeom->setBody(sphereBody);
        sphereGeom->setSpace(physicsSpace);
        sphereGeom->setRadius(Radius);
    
    //add attachments
    sphereNode->addAttachment(sphereGeom);
    sphereTransNode->addAttachment(sphereBody);
    sphereTransNode->addChild(sphereNode);
    //add to SceneGraph
    spaceGroupNode->addChild(sphereTransNode);

    commitChanges();

    return sphereBody;
}

