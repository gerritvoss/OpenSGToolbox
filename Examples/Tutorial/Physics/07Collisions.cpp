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


#include "OSGFieldContainerFactory.h"
#include "OSGNameAttachment.h"
#include "OSGSceneFileHandler.h"

#include "OSGSimpleStatisticsForeground.h"

// Input
#include "OSGKeyListener.h"
#include "OSGWindowUtils.h"

//Physics
#include "OSGPhysics.h"
#include "OSGCollisionListener.h"
#include "OSGCollisionEvent.h"

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE


// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);
void buildCar();
void buildTriMesh(void);
void buildSphere(void);
void buildBox(void);

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;
NodeRefPtr TriGeometryBase;

PhysicsHandlerRefPtr physHandler;
PhysicsWorldRefPtr physicsWorld;
PhysicsHashSpaceRefPtr physicsSpace;

//just for hierarchy
NodeRefPtr spaceGroupNode;

NodeRefPtr rootNode;

//Define the different Geom Categories
//These are used as bit masks
UInt64 TerrainCategory = 1;
UInt64 BoxCategory = 2;
UInt64 SphereCategory = 4;
UInt64 TriCategory = 8;


Real32 frand(void)
{
    return static_cast<Real32>(rand()%RAND_MAX)/static_cast<Real32>(RAND_MAX);
}

class TutorialCollisionListener : public CollisionListener
{
    /*=========================  PUBLIC  ===============================*/
  public:
  
    virtual void collision(const CollisionEventUnrecPtr e)
    {
        if(e->getProjectedNormalSpeed() >= 5.0f)
        {
            Vec3f NormalProjVel(e->getObject1Velocity() + e->getObject2Velocity());
            NormalProjVel.projectTo(e->getNormal());

            std::cout << "Collision Occured: " << std::endl
                      << "    Position: " << e->getPosition() << std::endl
                      << "    Normal: " << e->getNormal() << std::endl
                      << "    Body 1 Velocity: " << e->getObject1Velocity() << std::endl
                      << "    Body 2 Velocity: " << e->getObject2Velocity() << std::endl
                      << "    Projected Normal speed: " << e->getProjectedNormalSpeed() << std::endl
                      << "    Normal projected Velocity: " << NormalProjVel << std::endl<< std::endl;
        }
    }
};

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
                buildSphere();
            }
            break;
       case KeyEvent::KEY_B:
            {
                buildBox();
            }
            break;
       case KeyEvent::KEY_Z:
            {
                //SceneFileHandler::the().write(rootNode, "scene.osb");
            }
            break;
       case KeyEvent::KEY_T:
            {
                buildTriMesh();
            }
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
    TriGeometryBase = makeTorus(.55, 1.5, 16, 16);

    //Make Main Scene Node
	NodeRefPtr scene = makeCoredNode<Group>();
    setName(scene, "scene");
    rootNode = Node::create();
    setName(rootNode, "rootNode");
    ComponentTransformRefPtr Trans;
    Trans = ComponentTransform::create();
    {
        rootNode->setCore(Trans);
 
        // add the torus as a child
        rootNode->addChild(scene);
    }

    //Setup Physics Scene
    physicsWorld = PhysicsWorld::create();
        physicsWorld->setWorldContactSurfaceLayer(0.005);
        physicsWorld->setAutoDisableFlag(1);
        physicsWorld->setAutoDisableTime(0.75);
        physicsWorld->setWorldContactMaxCorrectingVel(100.0);
        physicsWorld->setGravity(Vec3f(0.0, 0.0, -9.81));

    //Create the Collision Space
    physicsSpace = PhysicsHashSpace::create();

    //Setup the default collision parameters
    CollisionContactParametersRefPtr DefaultCollisionParams = CollisionContactParameters::createEmpty();
        DefaultCollisionParams->setMode(dContactApprox1);
        DefaultCollisionParams->setMu(0.3);
        DefaultCollisionParams->setMu2(0.0);
        DefaultCollisionParams->setBounce(0.0);
        DefaultCollisionParams->setBounceSpeedThreshold(0.0);
        DefaultCollisionParams->setSoftCFM(0.1);
        DefaultCollisionParams->setSoftERP(0.2);
        DefaultCollisionParams->setMotion1(0.0);
        DefaultCollisionParams->setMotion2(0.0);
        DefaultCollisionParams->setMotionN(0.0);
        DefaultCollisionParams->setSlip1(0.0);
        DefaultCollisionParams->setSlip2(0.0);

        physicsSpace->setDefaultCollisionParameters(DefaultCollisionParams);

    //Bouncy Sphere collision parameters
    CollisionContactParametersRefPtr BouncySphereCollisionParams = CollisionContactParameters::createEmpty();
        BouncySphereCollisionParams->setMode(dContactApprox1 | dContactBounce);
        BouncySphereCollisionParams->setMu(0.3);
        BouncySphereCollisionParams->setMu2(0.0);
        BouncySphereCollisionParams->setBounce(0.8);
        BouncySphereCollisionParams->setBounceSpeedThreshold(0.1);
        BouncySphereCollisionParams->setSoftCFM(0.1);
        BouncySphereCollisionParams->setSoftERP(0.2);
        BouncySphereCollisionParams->setMotion1(0.0);
        BouncySphereCollisionParams->setMotion2(0.0);
        BouncySphereCollisionParams->setMotionN(0.0);
        BouncySphereCollisionParams->setSlip1(0.0);
        BouncySphereCollisionParams->setSlip2(0.0);
    physicsSpace->addCollisionContactCategory(SphereCategory, TerrainCategory, BouncySphereCollisionParams);
    physicsSpace->addCollisionContactCategory(SphereCategory, BoxCategory, BouncySphereCollisionParams);
    physicsSpace->addCollisionContactCategory(SphereCategory, SphereCategory, BouncySphereCollisionParams);
    physicsSpace->addCollisionContactCategory(SphereCategory, TriCategory, BouncySphereCollisionParams);

    //Soft Box collision parameters
    CollisionContactParametersRefPtr SlickBoxParams = CollisionContactParameters::createEmpty();
        SlickBoxParams->setMode(dContactApprox1);
        SlickBoxParams->setMu(0.01);
        SlickBoxParams->setMu2(0.0);
        SlickBoxParams->setBounce(0.0);
        SlickBoxParams->setBounceSpeedThreshold(0.0);
        SlickBoxParams->setSoftCFM(0.0);
        SlickBoxParams->setSoftERP(0.2);
        SlickBoxParams->setMotion1(0.0);
        SlickBoxParams->setMotion2(0.0);
        SlickBoxParams->setMotionN(0.0);
        SlickBoxParams->setSlip1(0.0);
        SlickBoxParams->setSlip2(0.0);
    physicsSpace->addCollisionContactCategory(BoxCategory, TerrainCategory, SlickBoxParams);
    physicsSpace->addCollisionContactCategory(BoxCategory, BoxCategory, SlickBoxParams);
    //physicsSpace->addCollisionContactCategory(BoxCategory, SphereCategory, SlickBoxParams);
    physicsSpace->addCollisionContactCategory(BoxCategory, TriCategory, SlickBoxParams);

    
    TutorialCollisionListener ColListener;
    physicsSpace->addCollisionListener(&ColListener,BoxCategory, 5.0);

    physHandler = PhysicsHandler::create();
        physHandler->setWorld(physicsWorld);
        physHandler->pushToSpaces(physicsSpace);
        physHandler->setStepSize(0.001);
        physHandler->setUpdateNode(rootNode);
    physHandler->attachUpdateProducer(TutorialWindow->editEventProducer());
    

        rootNode->addAttachment(physHandler);    
        rootNode->addAttachment(physicsWorld);
        rootNode->addAttachment(physicsSpace);


	/************************************************************************/
	/* create spaces, geoms and bodys                                                                     */
	/************************************************************************/
    //create a group for our space
    GroupRefPtr spaceGroup;
	spaceGroupNode = makeCoredNode<Group>(&spaceGroup);
    //create the ground plane
    GeometryRefPtr plane;
	NodeRefPtr planeNode = makeBox(30.0, 30.0, 1.0, 1, 1, 1);
    plane = dynamic_cast<Geometry*>(planeNode->getCore());
    //and its Material
	SimpleMaterialRefPtr plane_mat = SimpleMaterial::create();
		plane_mat->setAmbient(Color3f(0.7,0.7,0.7));
		plane_mat->setDiffuse(Color3f(0.9,0.6,1.0));
	    plane->setMaterial(plane_mat);


    //create Physical Attachments
	PhysicsBoxGeomRefPtr planeGeom = PhysicsBoxGeom::create();
        planeGeom->setLengths(Vec3f(30.0, 30.0, 1.0));
        //add geoms to space for collision
        planeGeom->setSpace(physicsSpace);
        //Set the Geoms Category - this will be used by the collision space 
        //for determining if collision tests should occur
        //and for selecting the collision contact parameters when a collision does occur
        planeGeom->setCategoryBits(TerrainCategory);

	//add Attachments to nodes...
	    spaceGroupNode->addAttachment(physicsSpace);
        spaceGroupNode->addChild(planeNode);

        planeNode->addAttachment(planeGeom);
    
	    scene->addChild(spaceGroupNode);
    
    //Create Statistics Foreground
    SimpleStatisticsForegroundRefPtr PhysicsStatForeground = SimpleStatisticsForeground::create();
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
            "07Collisions");

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
void buildBox(void)
{
    Vec3f Lengths(frand()*2.0+0.5, frand()*2.0+0.5, frand()*2.0+0.5);
    Matrix m;
    //create OpenSG mesh
    GeometryRefPtr box;
    NodeRefPtr boxNode = makeBox(Lengths.x(), Lengths.y(), Lengths.z(), 1, 1, 1);
    box = dynamic_cast<Geometry*>(boxNode->getCore());
    SimpleMaterialRefPtr box_mat = SimpleMaterial::create();
        box_mat->setAmbient(Color3f(0.0,0.0,0.0));
        box_mat->setDiffuse(Color3f(0.0,1.0 ,0.0));
        box->setMaterial(box_mat);
    TransformRefPtr boxTrans;
    NodeRefPtr boxTransNode = makeCoredNode<Transform>(&boxTrans);
    m.setIdentity();
    Real32 randX = frand()*10.0-5.0;
    Real32 randY = frand()*10.0-5.0;
    m.setTranslate(randX, randY, 10.0);
        boxTrans->setMatrix(m);

    //create ODE data
    PhysicsBodyRefPtr boxBody = PhysicsBody::create(physicsWorld);
        boxBody->setPosition(Vec3f(randX, randY, 10.0));
    boxBody->setBoxMass(1.0, Lengths.x(), Lengths.y(), Lengths.z());

    PhysicsBoxGeomRefPtr boxGeom = PhysicsBoxGeom::create();
        boxGeom->setBody(boxBody);
        boxGeom->setSpace(physicsSpace);
        boxGeom->setLengths(Lengths);
        boxGeom->setCategoryBits(BoxCategory);

    //add attachments
        boxNode->addAttachment(boxGeom);
        boxTransNode->addAttachment(boxBody);
        boxTransNode->addChild(boxNode);

    //add to SceneGraph
        spaceGroupNode->addChild(boxTransNode);

    commitChanges();
}

//////////////////////////////////////////////////////////////////////////
//! build a sphere
//////////////////////////////////////////////////////////////////////////
void buildSphere(void)
{
    Real32 Radius(frand()*1.5+0.2);
    Matrix m;
    //create OpenSG mesh
    GeometryRefPtr sphere;
    NodeRefPtr sphereNode = makeSphere(2, Radius);
    sphere = dynamic_cast<Geometry*>(sphereNode->getCore());
    SimpleMaterialRefPtr sphere_mat = SimpleMaterial::create();
    sphere_mat->setAmbient(Color3f(0.0,0.0,0.0));
    sphere_mat->setDiffuse(Color3f(0.0,0.0,1.0));
    sphere->setMaterial(sphere_mat);
    TransformRefPtr sphereTrans;
    NodeRefPtr sphereTransNode = makeCoredNode<Transform>(&sphereTrans);
    m.setIdentity();
    Real32 randX = frand()*10.0-5.0;
    Real32 randY = frand()*10.0-5.0;
    m.setTranslate(randX, randY, 10.0);
    sphereTrans->setMatrix(m);
    //create ODE data
    PhysicsBodyRefPtr sphereBody = PhysicsBody::create(physicsWorld);
        sphereBody->setPosition(Vec3f(randX, randY, 10.0));
        sphereBody->setAngularDamping(0.0001);
    sphereBody->setSphereMass(0.4,Radius);

    PhysicsSphereGeomRefPtr sphereGeom = PhysicsSphereGeom::create();
        sphereGeom->setBody(sphereBody);
        sphereGeom->setSpace(physicsSpace);
        sphereGeom->setRadius(Radius);
        sphereGeom->setCategoryBits(SphereCategory);
    
    //add attachments
    sphereNode->addAttachment(sphereGeom);
    sphereTransNode->addAttachment(sphereBody);
    sphereTransNode->addChild(sphereNode);
    //add to SceneGraph
    spaceGroupNode->addChild(sphereTransNode);

    commitChanges();
}

//////////////////////////////////////////////////////////////////////////
//! trimesh defined by filenode will be loaded
//////////////////////////////////////////////////////////////////////////
void buildTriMesh(void)
{
    //NodeRefPtr tri = makeTorus(0.5, 1.0, 24, 12);
    //NodeRefPtr tri = makeBox(10.0, 10.0, 10.0, 1, 1, 1);
    NodeRefPtr tri = cloneTree(TriGeometryBase);
    if(tri!=NULL)
    {
        GeometryRefPtr triGeo = dynamic_cast<Geometry*>(tri->getCore()); 

        Real32 randX = frand()*10.0-5.0;
        Real32 randY = frand()*10.0-5.0;

        //create ODE data
        Vec3f GeometryBounds(calcMinGeometryBounds(triGeo));
        PhysicsBodyRefPtr triBody = PhysicsBody::create(physicsWorld);
            triBody->setPosition(Vec3f(randX, randY, 18.0));
            triBody->setLinearDamping(0.0001);
            triBody->setAngularDamping(0.0001);
            triBody->setBoxMass(1.0,GeometryBounds.x(), GeometryBounds.y(), GeometryBounds.z());

        PhysicsGeomRefPtr triGeom;
        if(true)
        {
            triGeom = PhysicsTriMeshGeom::create();
                triGeom->setBody(triBody);
                //add geom to space for collision
                triGeom->setSpace(physicsSpace);
                //set the geometryNode to fill the ode-triMesh
                dynamic_pointer_cast<PhysicsTriMeshGeom>(triGeom)->setGeometryNode(tri);
                triGeom->setCategoryBits(TriCategory);
        }

        Matrix m;
        SimpleMaterialRefPtr tri_mat = SimpleMaterial::create();
        tri_mat->setAmbient(Color3f(0.1,0.1,0.2));
        tri_mat->setDiffuse(Color3f(1.0,0.1,0.7));
        triGeo->setMaterial(tri_mat);
        TransformRefPtr triTrans;
        NodeRefPtr triTransNode = makeCoredNode<Transform>(&triTrans);
        m.setIdentity();
        //m.setTranslate(randX, randY, 18.0);
        triTrans->setMatrix(m);

        
        //add attachments
        tri->addAttachment(triGeom);
        triTransNode->addAttachment(triBody);
        //add to SceneGraph
        triTransNode->addChild(tri);
        spaceGroupNode->addChild(triTransNode);
    }
    else
    {
        SLOG << "Could not read MeshData!" << endLog;
    }

    commitChanges();
}
