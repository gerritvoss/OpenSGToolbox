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

#include <OpenSG/Toolbox/OSGFCFileHandler.h>

// Input
#include <OpenSG/Input/OSGKeyListener.h>
#include <OpenSG/Input/OSGWindowAdapter.h>
#include <OpenSG/Input/OSGWindowUtils.h>

//Physics
#include <OpenSG/Physics/OSGPhysics.h>

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
NodePtr TriGeometryBase;

PhysicsHandlerPtr physHandler;
PhysicsWorldPtr physicsWorld;
PhysicsHashSpacePtr hashSpace;

//just for hierarchy
NodePtr spaceGroupNode;

NodePtr rootNode;

bool ExitApp = false;

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
       switch(e.getKey())
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

class TutorialUpdateListener : public UpdateListener
{
  public:
    virtual void update(const UpdateEvent& e)
    {
        physHandler->update(e.getElapsedTime(), rootNode);
    }
};

// Initialize GLUT & OpenSG and set up the rootNode
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
	TutorialUpdateListener TheTutorialUpdateListener;
    TutorialWindowEventProducer->addUpdateListener(&TheTutorialUpdateListener);


    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

	
    TutorialWindowEventProducer->openWindow(Pnt2f(0,0),
                                        Vec2f(1280,1024),
                                        "OpenSG 01SimplePhysics Window");

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindowEventProducer->getWindow());

    //Make Base Geometry Node
    TriGeometryBase = SceneFileHandler::the().read("./Data/Ship.osb");

    //Make Torus Node
    NodePtr TorusNode = makeTorus(.5, 2, 32, 32);

    //Make Main Scene Node
	NodePtr scene = makeCoredNode<Group>();
    setName(scene, "scene");
    rootNode = Node::create();
    setName(rootNode, "rootNode");
    ComponentTransformPtr Trans;
    Trans = ComponentTransform::create();
    beginEditCP(rootNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        rootNode->setCore(Trans);
 
        // add the torus as a child
        rootNode->addChild(scene);
    }
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

    hashSpace = PhysicsHashSpace::create();

    physHandler = PhysicsHandler::create();
    beginEditCP(physHandler, PhysicsHandler::WorldFieldMask | PhysicsHandler::SpacesFieldMask);
        physHandler->setWorld(physicsWorld);
        physHandler->getSpaces().push_back(hashSpace);
    endEditCP(physHandler, PhysicsHandler::WorldFieldMask | PhysicsHandler::SpacesFieldMask);
    

    beginEditCP(rootNode, Node::AttachmentsFieldMask);
        rootNode->addAttachment(physHandler);    
        rootNode->addAttachment(physicsWorld);
        rootNode->addAttachment(hashSpace);
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
    beginEditCP(planeGeom, PhysicsBoxGeom::LengthsFieldMask | PhysicsBoxGeom::SpaceFieldMask);
        planeGeom->setLengths(Vec3f(30.0, 30.0, 1.0));
        //add geoms to space for collision
        planeGeom->setSpace(hashSpace);
    endEditCP(planeGeom, PhysicsBoxGeom::LengthsFieldMask | PhysicsBoxGeom::SpaceFieldMask);

	//add Attachments to nodes...
    beginEditCP(spaceGroupNode, Node::AttachmentsFieldMask | Node::ChildrenFieldMask);
	    spaceGroupNode->addAttachment(hashSpace);
        spaceGroupNode->addChild(planeNode);
    endEditCP(spaceGroupNode, Node::AttachmentsFieldMask | Node::ChildrenFieldMask);

    beginEditCP(planeNode, Node::AttachmentsFieldMask);
        planeNode->addAttachment(planeGeom);
    endEditCP(planeNode, Node::AttachmentsFieldMask);
    
	beginEditCP(scene, Node::ChildrenFieldMask);
	    scene->addChild(spaceGroupNode);
	endEditCP(scene, Node::ChildrenFieldMask);

    //Save the Physics Sim
	FCFileType::FCPtrStore Containers;
	Containers.insert(physHandler);

	FCFileType::FCTypeVector IgnoreTypes;
	//IgnoreTypes.push_back(Node::getClassType().getId());
	//Save the Field Containers to a xml file
	FCFileHandler::the()->write(Containers,Path("./01PhysicsData.xml"),IgnoreTypes);


    // tell the manager what to manage
    mgr->setRoot  (rootNode);

    // show the whole rootNode
    mgr->showAll();
    
    while(!ExitApp)
    {
        TutorialWindowEventProducer->update();
        TutorialWindowEventProducer->draw();
    }

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
    Matrix m;
    //create OpenSG mesh
    GeometryPtr box;
    NodePtr boxNode = makeBox(1.0, 1.0, 1.0, 1, 1, 1);
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
    Real32 randX = (Real32)(rand()%10)-5.0;
    Real32 randY = (Real32)(rand()%10)-5.0;
    m.setTranslate(randX, randY, 10.0);
    beginEditCP(boxTrans, Transform::MatrixFieldMask);
        boxTrans->setMatrix(m);
    endEditCP(boxTrans, Transform::MatrixFieldMask);

    //create ODE data
    PhysicsBodyPtr boxBody = PhysicsBody::create(physicsWorld);
    beginEditCP(boxBody, PhysicsBody::PositionFieldMask | PhysicsBody::LinearDampingFieldMask | PhysicsBody::AngularDampingFieldMask);
        boxBody->setPosition(Vec3f(randX, randY, 10.0));
        boxBody->setLinearDamping(0.0001);
        boxBody->setAngularDamping(0.0001);
    endEditCP(boxBody, PhysicsBody::PositionFieldMask | PhysicsBody::LinearDampingFieldMask | PhysicsBody::AngularDampingFieldMask);

    PhysicsBoxGeomPtr boxGeom = PhysicsBoxGeom::create();
    beginEditCP(boxGeom, PhysicsBoxGeom::BodyFieldMask | PhysicsBoxGeom::SpaceFieldMask);
        boxGeom->setBody(boxBody);
        boxGeom->setSpace(hashSpace);
    endEditCP(boxGeom, PhysicsBoxGeom::BodyFieldMask | PhysicsBoxGeom::SpaceFieldMask);

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
    Matrix m;
    //create OpenSG mesh
    GeometryPtr sphere;
    NodePtr sphereNode = makeSphere(2, 1);
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
    Real32 randX = (Real32)(rand()%10)-5.0;
    Real32 randY = (Real32)(rand()%10)-5.0;
    m.setTranslate(randX, randY, 10.0);
    beginEditCP(sphereTrans, Transform::MatrixFieldMask);
    sphereTrans->setMatrix(m);
    endEditCP(sphereTrans);
    //create ODE data
    PhysicsBodyPtr sphereBody = PhysicsBody::create(physicsWorld);
    beginEditCP(sphereBody, PhysicsBody::PositionFieldMask | PhysicsBody::LinearDampingFieldMask | PhysicsBody::AngularDampingFieldMask);
        sphereBody->setPosition(Vec3f(randX, randY, 10.0));
        sphereBody->setLinearDamping(0.0001);
        sphereBody->setAngularDamping(0.0001);
    endEditCP(sphereBody, PhysicsBody::PositionFieldMask | PhysicsBody::LinearDampingFieldMask | PhysicsBody::AngularDampingFieldMask);

    PhysicsSphereGeomPtr sphereGeom = PhysicsSphereGeom::create();
    CPEdit(sphereGeom, PhysicsSphereGeom::BodyFieldMask | PhysicsSphereGeom::SpaceFieldMask);
        sphereGeom->setBody(sphereBody);
        sphereGeom->setSpace(hashSpace);
    
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
        Real32 randX = (Real32)(rand()%10)-5.0;
        Real32 randY = (Real32)(rand()%10)-5.0;
        m.setTranslate(randX, randY, 18.0);
        triTrans->setMatrix(m);

        //create ODE data
        PhysicsBodyPtr triBody = PhysicsBody::create(physicsWorld);
        beginEditCP(triBody, PhysicsBody::PositionFieldMask | PhysicsBody::LinearDampingFieldMask | PhysicsBody::AngularDampingFieldMask);
            triBody->setPosition(Vec3f(randX, randY, 18.0));
            triBody->setLinearDamping(0.0001);
            triBody->setAngularDamping(0.0001);
        endEditCP(triBody, PhysicsBody::PositionFieldMask | PhysicsBody::LinearDampingFieldMask | PhysicsBody::AngularDampingFieldMask);
        PhysicsGeomPtr triGeom;
        if(false)
        {
            triGeom = PhysicsTriMeshGeom::create();
            CPEdit(triGeom, PhysicsTriMeshGeom::BodyFieldMask | 
                            PhysicsTriMeshGeom::SpaceFieldMask | 
                            PhysicsTriMeshGeom::GeometryNodeFieldMask);
                triGeom->setBody(triBody);
                //add geom to space for collision
                triGeom->setSpace(hashSpace);
                //set the geometryNode to fill the ode-triMesh
                PhysicsTriMeshGeom::Ptr::dcast(triGeom)->setGeometryNode(tri);
        }
        else
        {

            triGeom = PhysicsBoxGeom::create();
            beginEditCP(triGeom, PhysicsBoxGeom::BodyFieldMask | PhysicsBoxGeom::SpaceFieldMask);
                triGeom->setBody(triBody);
                triGeom->setSpace(hashSpace);
                PhysicsBoxGeom::Ptr::dcast(triGeom)->setLengths(calcMinGeometryBounds(triGeo));
            endEditCP(triGeom, PhysicsBoxGeom::BodyFieldMask | PhysicsBoxGeom::SpaceFieldMask);
        }
        
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
