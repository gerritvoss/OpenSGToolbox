
// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// A little helper to simplify rootNode management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>

#include <OpenSG/OSGSimpleMaterial.h>

#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGTypeFactory.h>
#include <OpenSG/OSGFieldFactory.h>

#include <OpenSG/OSGFieldContainerFactory.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include <OpenSG/OSGSceneFileHandler.h>

#include <OpenSG/OSGSimpleStatisticsForeground.h>

// Input
#include <OpenSG/Input/OSGKeyListener.h>
#include <OpenSG/Input/OSGWindowUtils.h>

//Physics
#include <OpenSG/Physics/OSGPhysics.h>
#include <OpenSG/Physics/OSGCollisionListener.h>

//Sound
#include <OpenSG/Sound/OSGSoundManager.h>
#include <OpenSG/Sound/OSGSound.h>

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
WindowEventProducerPtr TutorialWindowEventProducer;
NodePtr TriGeometryBase;

PhysicsHandlerPtr physHandler;
PhysicsWorldPtr physicsWorld;
PhysicsHashSpacePtr physicsSpace;

//just for hierarchy
NodePtr spaceGroupNode;

NodePtr rootNode;

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
protected:
    SoundPtr _CollisionSound;
    /*=========================  PUBLIC  ===============================*/
  public:
    TutorialCollisionListener(Path SoundFilePath)
    {
        _CollisionSound = SoundManager::the()->createSound();
        beginEditCP(_CollisionSound, Sound::FileFieldMask | Sound::VolumeFieldMask | Sound::StreamingFieldMask | Sound::LoopingFieldMask);
            _CollisionSound->setFile(SoundFilePath);
            _CollisionSound->setVolume(1.0);
            _CollisionSound->setStreaming(false);
            _CollisionSound->setLooping(0);
        endEditCP(_CollisionSound, Sound::FileFieldMask | Sound::VolumeFieldMask | Sound::StreamingFieldMask | Sound::LoopingFieldMask);
    }
  
    virtual void collision(const CollisionEventPtr e)
    {
        _CollisionSound->play();
    }
};

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
       {
            TutorialWindowEventProducer->closeWindow();
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

// Initialize GLUT & OpenSG and set up the rootNode
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
    mgr->setWindow(TutorialWindowEventProducer->getWindow());

    //Make Torus Node
    TriGeometryBase = makeTorus(.55, 1.5, 16, 16);

    //Make Main Scene Node
	NodePtr scene = makeCoredNode<Group>();
    setName(scene, "scene");
    rootNode = Node::create();
    setName(rootNode, "rootNode");
    ComponentTransformPtr Trans;
    Trans = ComponentTransform::create();
    beginEditCP(rootNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
         rootNode->setCore(Trans);
        // add the torus as a child
        rootNode->addChild(scene);
    endEditCP  (rootNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

    //Setup Physics Scene
    physicsWorld = PhysicsWorld::create();
    beginEditCP(physicsWorld, PhysicsWorld::WorldContactSurfaceLayerFieldMask | 
                              PhysicsWorld::AutoDisableFlagFieldMask | 
                              PhysicsWorld::AutoDisableTimeFieldMask | 
                              PhysicsWorld::WorldContactMaxCorrectingVelFieldMask | 
                              PhysicsWorld::GravityFieldMask);
        physicsWorld->setWorldContactSurfaceLayer(0.005);
        physicsWorld->setAutoDisableFlag(1);
        physicsWorld->setAutoDisableTime(0.75);
        physicsWorld->setWorldContactMaxCorrectingVel(100.0);
        physicsWorld->setGravity(Vec3f(0.0, 0.0, -9.81));
    endEditCP(physicsWorld, PhysicsWorld::WorldContactSurfaceLayerFieldMask | 
                              PhysicsWorld::AutoDisableFlagFieldMask | 
                              PhysicsWorld::AutoDisableTimeFieldMask | 
                              PhysicsWorld::WorldContactMaxCorrectingVelFieldMask | 
                              PhysicsWorld::GravityFieldMask);

    //Create the Collision Space
    physicsSpace = PhysicsHashSpace::create();

    //Setup the default collision parameters
    CollisionContactParametersPtr DefaultCollisionParams = CollisionContactParameters::createEmpty();
    beginEditCP(DefaultCollisionParams);
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
    endEditCP(DefaultCollisionParams);

    beginEditCP(physicsSpace, PhysicsSpace::DefaultCollisionParametersFieldMask);
        physicsSpace->setDefaultCollisionParameters(DefaultCollisionParams);
    endEditCP(physicsSpace, PhysicsSpace::DefaultCollisionParametersFieldMask);

    //Bouncy Sphere collision parameters
    CollisionContactParametersPtr BouncySphereCollisionParams = CollisionContactParameters::createEmpty();
    beginEditCP(BouncySphereCollisionParams);
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
    endEditCP(BouncySphereCollisionParams);
    physicsSpace->addCollisionContactCategory(SphereCategory, TerrainCategory, BouncySphereCollisionParams);
    physicsSpace->addCollisionContactCategory(SphereCategory, BoxCategory, BouncySphereCollisionParams);
    physicsSpace->addCollisionContactCategory(SphereCategory, SphereCategory, BouncySphereCollisionParams);
    physicsSpace->addCollisionContactCategory(SphereCategory, TriCategory, BouncySphereCollisionParams);

    //Soft Box collision parameters
    CollisionContactParametersPtr SlickBoxParams = CollisionContactParameters::createEmpty();
    beginEditCP(SlickBoxParams);
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
    endEditCP(SlickBoxParams);
    physicsSpace->addCollisionContactCategory(BoxCategory, TerrainCategory, SlickBoxParams);
    physicsSpace->addCollisionContactCategory(BoxCategory, BoxCategory, SlickBoxParams);
    //physicsSpace->addCollisionContactCategory(BoxCategory, SphereCategory, SlickBoxParams);
    physicsSpace->addCollisionContactCategory(BoxCategory, TriCategory, SlickBoxParams);

    
    TutorialCollisionListener BoxColListener(Path("./Data/click.wav"));
    physicsSpace->addCollisionListener(&BoxColListener,BoxCategory, 2.0);

    TutorialCollisionListener SphereColListener(Path("./Data/pop.wav"));
    physicsSpace->addCollisionListener(&SphereColListener,SphereCategory, 2.0);

    physHandler = PhysicsHandler::create();
    beginEditCP(physHandler, PhysicsHandler::WorldFieldMask | PhysicsHandler::SpacesFieldMask | PhysicsHandler::StepSizeFieldMask | PhysicsHandler::UpdateNodeFieldMask);
        physHandler->setWorld(physicsWorld);
        physHandler->getSpaces().push_back(physicsSpace);
        physHandler->setStepSize(0.001);
        physHandler->setUpdateNode(rootNode);
    endEditCP(physHandler, PhysicsHandler::WorldFieldMask | PhysicsHandler::SpacesFieldMask | PhysicsHandler::StepSizeFieldMask | PhysicsHandler::UpdateNodeFieldMask);
    physHandler->attachUpdateProducer(TutorialWindowEventProducer);

    beginEditCP(rootNode, Node::AttachmentsFieldMask);
        rootNode->addAttachment(physHandler);    
        rootNode->addAttachment(physicsWorld);
        rootNode->addAttachment(physicsSpace);
    endEditCP(rootNode, Node::AttachmentsFieldMask);


	/************************************************************************/
	/* create spaces, geoms and bodys                                                                     */
	/************************************************************************/
    //create a group for our space
    GroupPtr spaceGroup;
	spaceGroupNode = makeCoredNode<Group>(&spaceGroup);
    //create the ground plane
    GeometryPtr plane;
	NodePtr planeNode = makeBox(30.0, 30.0, 1.0, 1, 1, 1);
    plane = GeometryPtr::dcast(planeNode->getCore());
    //and its Material
	SimpleMaterialPtr plane_mat = SimpleMaterial::create();
	beginEditCP(plane_mat);
		plane_mat->setAmbient(Color3f(0.7,0.7,0.7));
		plane_mat->setDiffuse(Color3f(0.9,0.6,1.0));
	endEditCP(plane_mat);
    beginEditCP(plane, Geometry::MaterialFieldMask);
	    plane->setMaterial(plane_mat);
    endEditCP(plane);


    //create Physical Attachments
	PhysicsBoxGeomPtr planeGeom = PhysicsBoxGeom::create();
    beginEditCP(planeGeom, PhysicsBoxGeom::LengthsFieldMask | PhysicsBoxGeom::SpaceFieldMask | PhysicsBoxGeom::CategoryBitsFieldMask);
        planeGeom->setLengths(Vec3f(30.0, 30.0, 1.0));
        //add geoms to space for collision
        planeGeom->setSpace(physicsSpace);
        //Set the Geoms Category - this will be used by the collision space 
        //for determining if collision tests should occur
        //and for selecting the collision contact parameters when a collision does occur
        planeGeom->setCategoryBits(TerrainCategory);
    endEditCP(planeGeom, PhysicsBoxGeom::LengthsFieldMask | PhysicsBoxGeom::SpaceFieldMask | PhysicsBoxGeom::CategoryBitsFieldMask);

	//add Attachments to nodes...
    beginEditCP(spaceGroupNode, Node::AttachmentsFieldMask | Node::ChildrenFieldMask);
	    spaceGroupNode->addAttachment(physicsSpace);
        spaceGroupNode->addChild(planeNode);
    endEditCP(spaceGroupNode, Node::AttachmentsFieldMask | Node::ChildrenFieldMask);

    beginEditCP(planeNode, Node::AttachmentsFieldMask);
        planeNode->addAttachment(planeGeom);
    endEditCP(planeNode, Node::AttachmentsFieldMask);
    
	beginEditCP(scene, Node::ChildrenFieldMask);
	    scene->addChild(spaceGroupNode);
	endEditCP(scene, Node::ChildrenFieldMask);
    
    //Create Statistics Foreground
    SimpleStatisticsForegroundPtr PhysicsStatForeground = SimpleStatisticsForeground::create();
    beginEditCP(PhysicsStatForeground);
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
    endEditCP(PhysicsStatForeground);




    // tell the manager what to manage
    mgr->setRoot  (rootNode);

    beginEditCP(mgr->getWindow()->getPort(0), Viewport::ForegroundsFieldMask);
        mgr->getWindow()->getPort(0)->getForegrounds().push_back(PhysicsStatForeground);
    endEditCP(mgr->getWindow()->getPort(0), Viewport::ForegroundsFieldMask);
    physHandler->setStatistics(&PhysicsStatForeground->getCollector());

    // show the whole rootNode
    mgr->showAll();

    //Attach the Sound Manager to the update and the camera
    SoundManager::the()->attachUpdateProducer(TutorialWindowEventProducer);
    SoundManager::the()->setCamera(mgr->getCamera());
    
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "21Collisions");

    //Enter main Loop
    TutorialWindowEventProducer->mainLoop();

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
    GeometryPtr box;
    NodePtr boxNode = makeBox(Lengths.x(), Lengths.y(), Lengths.z(), 1, 1, 1);
    box = GeometryPtr::dcast(boxNode->getCore());
    SimpleMaterialPtr box_mat = SimpleMaterial::create();
    beginEditCP(box_mat);
        box_mat->setAmbient(Color3f(0.0,0.0,0.0));
        box_mat->setDiffuse(Color3f(0.0,1.0 ,0.0));
    endEditCP(box_mat);
    beginEditCP(box, Geometry::MaterialFieldMask);
        box->setMaterial(box_mat);
    endEditCP(box, Geometry::MaterialFieldMask);
    TransformPtr boxTrans;
    NodePtr boxTransNode = makeCoredNode<Transform>(&boxTrans);
    m.setIdentity();
    Real32 randX = frand()*10.0-5.0;
    Real32 randY = frand()*10.0-5.0;
    m.setTranslate(randX, randY, 10.0);
    beginEditCP(boxTrans, Transform::MatrixFieldMask);
        boxTrans->setMatrix(m);
    endEditCP(boxTrans, Transform::MatrixFieldMask);

    //create ODE data
    PhysicsBodyPtr boxBody = PhysicsBody::create(physicsWorld);
    beginEditCP(boxBody, PhysicsBody::PositionFieldMask);
        boxBody->setPosition(Vec3f(randX, randY, 10.0));
    endEditCP(boxBody, PhysicsBody::PositionFieldMask);
    boxBody->setBoxMass(1.0, Lengths.x(), Lengths.y(), Lengths.z());

    PhysicsBoxGeomPtr boxGeom = PhysicsBoxGeom::create();
    beginEditCP(boxGeom, PhysicsBoxGeom::BodyFieldMask | PhysicsBoxGeom::SpaceFieldMask  | PhysicsBoxGeom::LengthsFieldMask | PhysicsBoxGeom::CategoryBitsFieldMask);
        boxGeom->setBody(boxBody);
        boxGeom->setSpace(physicsSpace);
        boxGeom->setLengths(Lengths);
        boxGeom->setCategoryBits(BoxCategory);
    endEditCP(boxGeom, PhysicsBoxGeom::BodyFieldMask | PhysicsBoxGeom::SpaceFieldMask | PhysicsBoxGeom::LengthsFieldMask | PhysicsBoxGeom::CategoryBitsFieldMask);

    //add attachments
    beginEditCP(boxNode, Node::AttachmentsFieldMask);
        boxNode->addAttachment(boxGeom);
    endEditCP(boxNode, Node::AttachmentsFieldMask);
    beginEditCP(boxTransNode, Node::AttachmentsFieldMask | Node::ChildrenFieldMask);
        boxTransNode->addAttachment(boxBody);
        boxTransNode->addChild(boxNode);
    endEditCP(boxTransNode, Node::AttachmentsFieldMask | Node::ChildrenFieldMask);

    //add to SceneGraph
    beginEditCP(spaceGroupNode, Node::ChildrenFieldMask);
        spaceGroupNode->addChild(boxTransNode);
    endEditCP(spaceGroupNode, Node::ChildrenFieldMask);
}

//////////////////////////////////////////////////////////////////////////
//! build a sphere
//////////////////////////////////////////////////////////////////////////
void buildSphere(void)
{
    Real32 Radius(frand()*1.5+0.2);
    Matrix m;
    //create OpenSG mesh
    GeometryPtr sphere;
    NodePtr sphereNode = makeSphere(2, Radius);
    sphere = GeometryPtr::dcast(sphereNode->getCore());
    SimpleMaterialPtr sphere_mat = SimpleMaterial::create();
    beginEditCP(sphere_mat);
    sphere_mat->setAmbient(Color3f(0.0,0.0,0.0));
    sphere_mat->setDiffuse(Color3f(0.0,0.0,1.0));
    endEditCP(sphere_mat);
    beginEditCP(sphere, Geometry::MaterialFieldMask);
    sphere->setMaterial(sphere_mat);
    endEditCP(sphere);
    TransformPtr sphereTrans;
    NodePtr sphereTransNode = makeCoredNode<Transform>(&sphereTrans);
    m.setIdentity();
    Real32 randX = frand()*10.0-5.0;
    Real32 randY = frand()*10.0-5.0;
    m.setTranslate(randX, randY, 10.0);
    beginEditCP(sphereTrans, Transform::MatrixFieldMask);
    sphereTrans->setMatrix(m);
    endEditCP(sphereTrans);
    //create ODE data
    PhysicsBodyPtr sphereBody = PhysicsBody::create(physicsWorld);
    beginEditCP(sphereBody, PhysicsBody::PositionFieldMask | PhysicsBody::AngularDampingFieldMask);
        sphereBody->setPosition(Vec3f(randX, randY, 10.0));
        sphereBody->setAngularDamping(0.0001);
    endEditCP(sphereBody, PhysicsBody::PositionFieldMask | PhysicsBody::AngularDampingFieldMask);
    sphereBody->setSphereMass(0.4,Radius);

    PhysicsSphereGeomPtr sphereGeom = PhysicsSphereGeom::create();
    beginEditCP(sphereGeom, PhysicsSphereGeom::BodyFieldMask | PhysicsSphereGeom::SpaceFieldMask | PhysicsSphereGeom::RadiusFieldMask | PhysicsSphereGeom::CategoryBitsFieldMask);
        sphereGeom->setBody(sphereBody);
        sphereGeom->setSpace(physicsSpace);
        sphereGeom->setRadius(Radius);
        sphereGeom->setCategoryBits(SphereCategory);
    endEditCP(sphereGeom, PhysicsSphereGeom::BodyFieldMask | PhysicsSphereGeom::SpaceFieldMask | PhysicsSphereGeom::RadiusFieldMask | PhysicsSphereGeom::CategoryBitsFieldMask);
    
    //add attachments
    beginEditCP(sphereNode, Node::AttachmentsFieldMask);
    sphereNode->addAttachment(sphereGeom);
    endEditCP(sphereNode);
    beginEditCP(sphereTransNode, Node::AttachmentsFieldMask | Node::ChildrenFieldMask);
    sphereTransNode->addAttachment(sphereBody);
    sphereTransNode->addChild(sphereNode);
    endEditCP(sphereTransNode);
    //add to SceneGraph
    beginEditCP(spaceGroupNode, Node::ChildrenFieldMask);
    spaceGroupNode->addChild(sphereTransNode);
    endEditCP(spaceGroupNode);
}

//////////////////////////////////////////////////////////////////////////
//! trimesh defined by filenode will be loaded
//////////////////////////////////////////////////////////////////////////
void buildTriMesh(void)
{
    //NodePtr tri = makeTorus(0.5, 1.0, 24, 12);
    //NodePtr tri = makeBox(10.0, 10.0, 10.0, 1, 1, 1);
    NodePtr tri = Node::Ptr::dcast(TriGeometryBase->shallowCopy());
    if(tri!=NullFC)
    {
        GeometryPtr triGeo = GeometryPtr::dcast(tri->getCore()); 
        Matrix m;
        SimpleMaterialPtr tri_mat = SimpleMaterial::create();
        beginEditCP(tri_mat);
        tri_mat->setAmbient(Color3f(0.1,0.1,0.2));
        tri_mat->setDiffuse(Color3f(1.0,0.1,0.7));
        endEditCP(tri_mat);
        triGeo->setMaterial(tri_mat);
        TransformPtr triTrans;
        NodePtr triTransNode = makeCoredNode<Transform>(&triTrans);
        m.setIdentity();
        Real32 randX = frand()*10.0-5.0;
        Real32 randY = frand()*10.0-5.0;
        m.setTranslate(randX, randY, 18.0);
        triTrans->setMatrix(m);

        //create ODE data
        Vec3f GeometryBounds(calcMinGeometryBounds(triGeo));
        PhysicsBodyPtr triBody = PhysicsBody::create(physicsWorld);
        beginEditCP(triBody, PhysicsBody::PositionFieldMask | PhysicsBody::LinearDampingFieldMask | PhysicsBody::AngularDampingFieldMask);
            triBody->setPosition(Vec3f(randX, randY, 18.0));
            triBody->setLinearDamping(0.0001);
            triBody->setAngularDamping(0.0001);
        endEditCP(triBody, PhysicsBody::PositionFieldMask | PhysicsBody::LinearDampingFieldMask | PhysicsBody::AngularDampingFieldMask);
            triBody->setBoxMass(1.0,GeometryBounds.x(), GeometryBounds.y(), GeometryBounds.z());
        PhysicsGeomPtr triGeom;
        if(true)
        {
            triGeom = PhysicsTriMeshGeom::create();
            beginEditCP(triGeom, PhysicsTriMeshGeom::BodyFieldMask | 
                            PhysicsTriMeshGeom::SpaceFieldMask | 
                            PhysicsTriMeshGeom::GeometryNodeFieldMask);
                triGeom->setBody(triBody);
                //add geom to space for collision
                triGeom->setSpace(physicsSpace);
                //set the geometryNode to fill the ode-triMesh
                PhysicsTriMeshGeom::Ptr::dcast(triGeom)->setGeometryNode(tri);
            endEditCP(triGeom, PhysicsTriMeshGeom::BodyFieldMask | 
                            PhysicsTriMeshGeom::SpaceFieldMask | 
                            PhysicsTriMeshGeom::GeometryNodeFieldMask);
        }
        else
        {

            triGeom = PhysicsBoxGeom::create();
            beginEditCP(triGeom, PhysicsBoxGeom::BodyFieldMask | PhysicsBoxGeom::SpaceFieldMask | PhysicsBoxGeom::LengthsFieldMask);
                triGeom->setBody(triBody);
                triGeom->setSpace(physicsSpace);
                PhysicsBoxGeom::Ptr::dcast(triGeom)->setLengths(GeometryBounds);

            endEditCP(triGeom, PhysicsBoxGeom::BodyFieldMask | PhysicsBoxGeom::SpaceFieldMask | PhysicsBoxGeom::LengthsFieldMask);
        }
        beginEditCP(triGeom, PhysicsGeom::CategoryBitsFieldMask);
            triGeom->setCategoryBits(TriCategory);
        endEditCP(triGeom, PhysicsGeom::CategoryBitsFieldMask);
        
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
}
