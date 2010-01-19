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


#include "OSGFieldContainerFactory.h"
#include "OSGNameAttachment.h"

#include "OSGSimpleStatisticsForeground.h"

// Input
#include "OSGKeyListener.h"
#include "OSGWindowUtils.h"

//Physics
#include "OSGPhysics.h"
#include "OSGPhysicsCharacteristicsDrawable.h"

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
NodeRefPtr PhysDrawableNode;

class TutorialKeyListener : public KeyListener
{
  public:

    virtual void keyPressed(const KeyEventUnrecPtr e)
    {
        if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
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
            case KeyEvent::KEY_T:
                {
                    buildTriMesh();
                }
                break;
            case KeyEvent::KEY_D:
                {
                    if(PhysDrawableNode->getTravMask())
                    {
                        PhysDrawableNode->setTravMask(TypeTraits<UInt32>::getMin());
                    }
                    else
                    {
                        PhysDrawableNode->setTravMask(TypeTraits<UInt32>::getMax());
                    }
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

    //Make Base Geometry Node
    TriGeometryBase = makeTorus(0.5, 1.0, 24, 24);

    //Make Main Scene Node
    NodeRefPtr scene = makeCoredNode<Group>();
    setName(scene, "scene");
    rootNode = Node::create();
    setName(rootNode, "rootNode");
    ComponentTransformRefPtr Trans;
    Trans = ComponentTransform::create();
    rootNode->setCore(Trans);

    // add the torus as a child
    rootNode->addChild(scene);

    //Make The Physics Characteristics Node
    PhysicsCharacteristicsDrawableRefPtr PhysDrawable = PhysicsCharacteristicsDrawable::create();
    PhysDrawable->setRoot(rootNode);

    PhysDrawableNode = Node::create();
    PhysDrawableNode->setCore(PhysDrawable);
    PhysDrawableNode->setTravMask(TypeTraits<UInt32>::getMin());

    rootNode->addChild(PhysDrawableNode);


    //Setup Physics Scene
    physicsWorld = PhysicsWorld::create();
    physicsWorld->setWorldContactSurfaceLayer(0.005);
    physicsWorld->setAutoDisableFlag(1);
    physicsWorld->setAutoDisableTime(0.75);
    physicsWorld->setWorldContactMaxCorrectingVel(100.0);
    physicsWorld->setGravity(Vec3f(0.0, 0.0, -9.81));

    physicsSpace = PhysicsHashSpace::create();

    physHandler = PhysicsHandler::create();
    physHandler->setWorld(physicsWorld);
    physHandler->pushToSpaces(physicsSpace);
    physHandler->setUpdateNode(rootNode);

    physHandler->attachUpdateProducer(TutorialWindow->editEventProducer());


    /************************************************************************/
    /* create spaces, geoms and bodys                                       */
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


    //add Attachments to nodes...
    spaceGroupNode->addAttachment(physicsSpace);
    spaceGroupNode->addAttachment(physHandler);    
    spaceGroupNode->addAttachment(physicsWorld);
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
    PhysicsStatForeground->setVerticalAlign(SimpleStatisticsForeground::Center);


    SimpleStatisticsForegroundRefPtr RenderStatForeground = SimpleStatisticsForeground::create();
    RenderStatForeground->setSize(25);
    RenderStatForeground->setColor(Color4f(0,1,0,0.7));
    RenderStatForeground->addElement(RenderAction::statDrawTime, "Draw FPS: %r.3f");
    RenderStatForeground->addElement(RenderAction::statNGeometries, 
                                     "%d Nodes drawn");





    // tell the manager what to manage
    mgr->setRoot  (rootNode);

    mgr->getWindow()->getPort(0)->addForeground(PhysicsStatForeground);
    mgr->getWindow()->getPort(0)->addForeground(RenderStatForeground);

    physHandler->setStatistics(PhysicsStatForeground->editCollector());
    mgr->getRenderAction()->setStatCollector(RenderStatForeground->editCollector());

    // show the whole rootNode
    mgr->showAll();

    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
                               WinSize,
                               "01SimplePhysics");

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
    Vec3f Lengths((Real32)(rand()%2)+1.0, (Real32)(rand()%2)+1.0, (Real32)(rand()%2)+1.0);
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
    Real32 randX = (Real32)(rand()%10)-5.0;
    Real32 randY = (Real32)(rand()%10)-5.0;
    m.setTranslate(randX, randY, 10.0);
    boxTrans->setMatrix(m);


    //create ODE data
    PhysicsBodyRefPtr boxBody = PhysicsBody::create(physicsWorld);
    boxBody->setPosition(Vec3f(randX, randY, 10.0));

    boxBody->setBoxMass(1.0, Lengths.x(), Lengths.y(), Lengths.z());
    //std::cout << "mass: "                << boxBody->getMass()                    << std::endl
    //<< "massCenterOfGravity: " << boxBody->getMassCenterOfGravity().x() << ", "      << boxBody->getMassCenterOfGravity().y() << ", " << boxBody->getMassCenterOfGravity().z() << std::endl
    //<< "massInertiaTensor: "   << std::endl
    //<< boxBody->getMassInertiaTensor()[0][0] << " "<< boxBody->getMassInertiaTensor()[0][1] << " "<< boxBody->getMassInertiaTensor()[0][2] << " "   << boxBody->getMassInertiaTensor()[0][3] << std::endl
    //<< boxBody->getMassInertiaTensor()[1][0] << " "<< boxBody->getMassInertiaTensor()[1][1] << " "<< boxBody->getMassInertiaTensor()[1][2] << " "   << boxBody->getMassInertiaTensor()[1][3] << std::endl
    //<< boxBody->getMassInertiaTensor()[2][0] << " "<< boxBody->getMassInertiaTensor()[2][1] << " "<< boxBody->getMassInertiaTensor()[2][2] << " "   << boxBody->getMassInertiaTensor()[2][3] << std::endl
    //<< boxBody->getMassInertiaTensor()[3][0] << " "<< boxBody->getMassInertiaTensor()[3][1] << " "<< boxBody->getMassInertiaTensor()[3][2] << " "   << boxBody->getMassInertiaTensor()[3][3] << std::endl
    //<< std::endl;

    PhysicsBoxGeomRefPtr boxGeom = PhysicsBoxGeom::create();
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

}

//////////////////////////////////////////////////////////////////////////
//! build a sphere
//////////////////////////////////////////////////////////////////////////
void buildSphere(void)
{
    Real32 Radius((Real32)(rand()%2)*0.5+0.5);
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
    Real32 randX = (Real32)(rand()%10)-5.0;
    Real32 randY = (Real32)(rand()%10)-5.0;
    m.setTranslate(randX, randY, 10.0);
    sphereTrans->setMatrix(m);

    //create ODE data
    PhysicsBodyRefPtr sphereBody = PhysicsBody::create(physicsWorld);
    sphereBody->setPosition(Vec3f(randX, randY, 10.0));
    sphereBody->setAngularDamping(0.0001);

    sphereBody->setSphereMass(1.0,Radius);

    PhysicsSphereGeomRefPtr sphereGeom = PhysicsSphereGeom::create();
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
}

//////////////////////////////////////////////////////////////////////////
//! trimesh defined by filenode will be loaded
//////////////////////////////////////////////////////////////////////////
void buildTriMesh(void)
{
    NodeRefPtr tri = cloneTree(TriGeometryBase);
    if(tri!=NULL)
    {
        GeometryRefPtr triGeo = dynamic_cast<Geometry*>(tri->getCore()); 
        Matrix m;
        SimpleMaterialRefPtr tri_mat = SimpleMaterial::create();
        tri_mat->setAmbient(Color3f(0.1,0.1,0.2));
        tri_mat->setDiffuse(Color3f(1.0,0.1,0.7));

        triGeo->setMaterial(tri_mat);
        TransformRefPtr triTrans;
        NodeRefPtr triTransNode = makeCoredNode<Transform>(&triTrans);
        m.setIdentity();
        Real32 randX = (Real32)(rand()%10)-5.0;
        Real32 randY = (Real32)(rand()%10)-5.0;
        m.setTranslate(randX, randY, 18.0);
        triTrans->setMatrix(m);

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
            NodeRefPtr TorusGeometryNode(makeTorus(0.55, 1.05, 6, 6));
            dynamic_pointer_cast<PhysicsTriMeshGeom>(triGeom)->setGeometryNode(TorusGeometryNode);
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

    commitChanges();
}

