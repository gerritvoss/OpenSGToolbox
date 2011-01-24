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
#include "OSGWindowUtils.h"

//Physics
#include "OSGPhysics.h"
#include "OSGCollisionEvent.h"

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with , but that would be a bit tedious for this example
OSG_USING_NAMESPACE


// forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);
void buildTriMesh(Node* const TriGeometryBase, Node* const spaceGroupNode, PhysicsWorld* const physicsWorld, PhysicsHashSpace* const physicsSpace);
void buildSphere(Node* const spaceGroupNode, PhysicsWorld* const physicsWorld, PhysicsHashSpace* const physicsSpace);
void buildBox(Node* const spaceGroupNode, PhysicsWorld* const physicsWorld, PhysicsHashSpace* const physicsSpace);

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

void handleCollision(CollisionEventDetails* const details)
{
    if(details->getProjectedNormalSpeed() >= 5.0f)
    {
        Vec3f NormalProjVel(details->getObject1Velocity() + details->getObject2Velocity());
        NormalProjVel.projectTo(details->getNormal());

        std::cout << "Collision Occured: " << std::endl
            << "    Position: " << details->getPosition() << std::endl
            << "    Normal: " << details->getNormal() << std::endl
            << "    Body 1 Velocity: " << details->getObject1Velocity() << std::endl
            << "    Body 2 Velocity: " << details->getObject2Velocity() << std::endl
            << "    Projected Normal speed: " << details->getProjectedNormalSpeed() << std::endl
            << "    Normal projected Velocity: " << NormalProjVel << std::endl<< std::endl;
    }
}

void keyPressed(KeyEventDetails* const details,
                Node* const TriGeometryBase,
                Node* const spaceGroupNode,
                PhysicsWorld* const physicsWorld,
                PhysicsHashSpace* const physicsSpace)
{
    if(details->getKey() == KeyEventDetails::KEY_Q &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
    switch(details->getKey())
    {
        case KeyEventDetails::KEY_S:
            {
                buildSphere(spaceGroupNode, physicsWorld, physicsSpace);
            }
            break;
        case KeyEventDetails::KEY_B:
            {
                buildBox(spaceGroupNode, physicsWorld, physicsSpace);
            }
            break;
        case KeyEventDetails::KEY_T:
            {
                buildTriMesh(TriGeometryBase, spaceGroupNode, physicsWorld, physicsSpace);
            }
            break;
    }
}

void mousePressed(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    mgr->mouseButtonPress(details->getButton(), details->getLocation().x(), details->getLocation().y());
}
void mouseReleased(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    mgr->mouseButtonRelease(details->getButton(), details->getLocation().x(), details->getLocation().y());
}

void mouseMoved(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    mgr->mouseMove(details->getLocation().x(), details->getLocation().y());
}

void mouseDragged(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    mgr->mouseMove(details->getLocation().x(), details->getLocation().y());
}

void mouseWheelMoved(MouseWheelEventDetails* const details, SimpleSceneManager *mgr)
{
    if(details->getUnitsToScroll() > 0)
    {
        for(UInt32 i(0) ; i<details->getUnitsToScroll() ;++i)
        {
            mgr->mouseButtonPress(Navigator::DOWN_MOUSE,details->getLocation().x(),details->getLocation().y());
            mgr->mouseButtonRelease(Navigator::DOWN_MOUSE,details->getLocation().x(),details->getLocation().y());
        }
    }
    else if(details->getUnitsToScroll() < 0)
    {
        for(UInt32 i(0) ; i<abs(details->getUnitsToScroll()) ;++i)
        {
            mgr->mouseButtonPress(Navigator::UP_MOUSE,details->getLocation().x(),details->getLocation().y());
            mgr->mouseButtonRelease(Navigator::UP_MOUSE,details->getLocation().x(),details->getLocation().y());
        }
    }
}

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    {
        // Set up Window
        WindowEventProducerRecPtr TutorialWindow = createNativeWindow();
        TutorialWindow->initWindow();

        // Create the SimpleSceneManager helper
        SimpleSceneManager sceneManager;
        TutorialWindow->setDisplayCallback(boost::bind(display, &sceneManager));
        TutorialWindow->setReshapeCallback(boost::bind(reshape, _1, &sceneManager));

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

        //Attach to events
        TutorialWindow->connectMousePressed(boost::bind(mousePressed, _1, &sceneManager));
        TutorialWindow->connectMouseReleased(boost::bind(mouseReleased, _1, &sceneManager));
        TutorialWindow->connectMouseMoved(boost::bind(mouseMoved, _1, &sceneManager));
        TutorialWindow->connectMouseDragged(boost::bind(mouseDragged, _1, &sceneManager));
        TutorialWindow->connectMouseWheelMoved(boost::bind(mouseWheelMoved, _1, &sceneManager));

        //Make Torus Node
        NodeRecPtr TriGeometryBase = makeTorus(.55, 1.5, 16, 16);

        //Make Main Scene Node
        NodeRefPtr scene = makeCoredNode<Group>();
        setName(scene, "scene");
        NodeRecPtr rootNode = Node::create();
        setName(rootNode, "rootNode");
        ComponentTransformRefPtr Trans = ComponentTransform::create();
        {
            rootNode->setCore(Trans);

            // add the torus as a child
            rootNode->addChild(scene);
        }

        //Setup Physics Scene
        PhysicsWorldRecPtr physicsWorld = PhysicsWorld::create();
        physicsWorld->setWorldContactSurfaceLayer(0.005);
        physicsWorld->setAutoDisableFlag(1);
        physicsWorld->setAutoDisableTime(0.75);
        physicsWorld->setWorldContactMaxCorrectingVel(100.0);
        physicsWorld->setGravity(Vec3f(0.0, 0.0, -9.81));

        //Create the Collision Space
        PhysicsHashSpaceRecPtr physicsSpace = PhysicsHashSpace::create();

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

        physicsSpace->PhysicsSpaceBase::connectCollision(boost::bind(handleCollision, _1));

        PhysicsHandlerRecPtr physHandler = PhysicsHandler::create();
        physHandler->setWorld(physicsWorld);
        physHandler->pushToSpaces(physicsSpace);
        physHandler->setStepSize(0.001);
        physHandler->setUpdateNode(rootNode);
        physHandler->attachUpdateProducer(TutorialWindow);


        rootNode->addAttachment(physHandler);    
        rootNode->addAttachment(physicsWorld);
        rootNode->addAttachment(physicsSpace);


        /************************************************************************/
        /* create spaces, geoms and bodys                                                                     */
        /************************************************************************/
        //create a group for our space
        NodeRecPtr spaceGroupNode = makeCoredNode<Group>();
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

        TutorialWindow->connectKeyPressed(boost::bind(keyPressed, _1,
                                                      TriGeometryBase.get(),
                                                      spaceGroupNode.get(),
                                                      physicsWorld.get(),
                                                      physicsSpace.get()));

        // tell the manager what to manage
        sceneManager.setRoot  (rootNode);

        // show the whole rootNode
        sceneManager.showAll();

        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "07Collisions");

        //Enter main Loop
        TutorialWindow->mainLoop();

    }
    osgExit();

    return 0;
}

// Redraw the window
void display(SimpleSceneManager *mgr)
{
    mgr->redraw();
}

// React to size changes
void reshape(Vec2f Size, SimpleSceneManager *mgr)
{
    mgr->resize(Size.x(), Size.y());
}

//////////////////////////////////////////////////////////////////////////
//! build a box
//////////////////////////////////////////////////////////////////////////
void buildBox(Node* const spaceGroupNode, PhysicsWorld* const physicsWorld, PhysicsHashSpace* const physicsSpace)
{
    Vec3f Lengths((Real32)(rand()%2)+1.0, (Real32)(rand()%2)+1.0, (Real32)(rand()%2)+1.0);
    Matrix m;
    //create OpenSG mesh
    GeometryRecPtr box;
    NodeRecPtr boxNode = makeBox(Lengths.x(), Lengths.y(), Lengths.z(), 1, 1, 1);
    box = dynamic_cast<Geometry*>(boxNode->getCore());
    SimpleMaterialRecPtr box_mat = SimpleMaterial::create();
    box_mat->setAmbient(Color3f(0.0,0.0,0.0));
    box_mat->setDiffuse(Color3f(0.0,1.0 ,0.0));

    box->setMaterial(box_mat);

    TransformRecPtr boxTrans;
    NodeRecPtr boxTransNode = makeCoredNode<Transform>(&boxTrans);
    m.setIdentity();
    Real32 randX = (Real32)(rand()%10)-5.0;
    Real32 randY = (Real32)(rand()%10)-5.0;
    m.setTranslate(randX, randY, 10.0);
    boxTrans->setMatrix(m);


    //create ODE data
    PhysicsBodyRecPtr boxBody = PhysicsBody::create(physicsWorld);
    boxBody->setPosition(Vec3f(randX, randY, 10.0));

    boxBody->setBoxMass(1.0, Lengths.x(), Lengths.y(), Lengths.z());

    PhysicsBoxGeomRecPtr boxGeom = PhysicsBoxGeom::create();
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
void buildSphere(Node* const spaceGroupNode, PhysicsWorld* const physicsWorld, PhysicsHashSpace* const physicsSpace)
{
    Real32 Radius((Real32)(rand()%2)*0.5+0.5);
    Matrix m;
    //create OpenSG mesh
    GeometryRecPtr sphere;
    NodeRecPtr sphereNode = makeSphere(2, Radius);
    sphere = dynamic_cast<Geometry*>(sphereNode->getCore());
    SimpleMaterialRecPtr sphere_mat = SimpleMaterial::create();
    sphere_mat->setAmbient(Color3f(0.0,0.0,0.0));
    sphere_mat->setDiffuse(Color3f(0.0,0.0,1.0));

    sphere->setMaterial(sphere_mat);

    TransformRecPtr sphereTrans;
    NodeRecPtr sphereTransNode = makeCoredNode<Transform>(&sphereTrans);
    m.setIdentity();
    Real32 randX = (Real32)(rand()%10)-5.0;
    Real32 randY = (Real32)(rand()%10)-5.0;
    m.setTranslate(randX, randY, 10.0);
    sphereTrans->setMatrix(m);

    //create ODE data
    PhysicsBodyRecPtr sphereBody = PhysicsBody::create(physicsWorld);
    sphereBody->setPosition(Vec3f(randX, randY, 10.0));
    sphereBody->setAngularDamping(0.0001);

    sphereBody->setSphereMass(1.0,Radius);

    PhysicsSphereGeomRecPtr sphereGeom = PhysicsSphereGeom::create();
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
void buildTriMesh(Node* const TriGeometryBase, Node* const spaceGroupNode, PhysicsWorld* const physicsWorld, PhysicsHashSpace* const physicsSpace)
{
    NodeRecPtr tri = cloneTree(TriGeometryBase);
    if(tri!=NULL)
    {
        GeometryRecPtr triGeo = dynamic_cast<Geometry*>(tri->getCore()); 
        Matrix m;
        SimpleMaterialRecPtr tri_mat = SimpleMaterial::create();
        tri_mat->setAmbient(Color3f(0.1,0.1,0.2));
        tri_mat->setDiffuse(Color3f(1.0,0.1,0.7));

        triGeo->setMaterial(tri_mat);
        TransformRecPtr triTrans;
        NodeRecPtr triTransNode = makeCoredNode<Transform>(&triTrans);
        m.setIdentity();
        Real32 randX = (Real32)(rand()%10)-5.0;
        Real32 randY = (Real32)(rand()%10)-5.0;
        m.setTranslate(randX, randY, 18.0);
        triTrans->setMatrix(m);

        //create ODE data
        Vec3f GeometryBounds(calcMinGeometryBounds(triGeo));
        PhysicsBodyRecPtr triBody = PhysicsBody::create(physicsWorld);
        triBody->setPosition(Vec3f(randX, randY, 18.0));
        triBody->setLinearDamping(0.0001);
        triBody->setAngularDamping(0.0001);

        triBody->setBoxMass(1.0,GeometryBounds.x(), GeometryBounds.y(), GeometryBounds.z());
        PhysicsGeomRecPtr triGeom;
        if(true)
        {
            triGeom = PhysicsTriMeshGeom::create();
            triGeom->setBody(triBody);
            //add geom to space for collision
            triGeom->setSpace(physicsSpace);
            //set the geometryNode to fill the ode-triMesh
            NodeRecPtr TorusGeometryNode(makeTorus(0.55, 1.5, 6, 6));
            dynamic_pointer_cast<PhysicsTriMeshGeom>(triGeom)->setGeometryNode(TorusGeometryNode);
            triGeom->setCategoryBits(TriCategory);
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
