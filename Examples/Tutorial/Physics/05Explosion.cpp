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
#include "OSGWindowUtils.h"

//Physics
#include "OSGPhysics.h"

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with , but that would be a bit tedious for this example
OSG_USING_NAMESPACE


// forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);
PhysicsBodyUnrecPtr  buildSphere(Node* const spaceGroupNode,
                                 PhysicsWorld* const physicsWorld,
                                 PhysicsHashSpace* const physicsSpace);

PhysicsBodyUnrecPtr  buildBox(const Pnt3f& Position,
                              const Vec3f& Dimensions,
                              const Color3f& Color,
                              Node* const spaceGroupNode,
                              PhysicsWorld* const physicsWorld,
                              PhysicsHashSpace* const physicsSpace);

void makeExplosion(Pnt3f Location,
                   Real32 Impulse,
                   PhysicsWorld* const physicsWorld,
                   PhysicsHandler* const physHandler);

std::vector<PhysicsBodyRecPtr> allPhysicsBodies;

void makeExplosion(Pnt3f Location,
                   Real32 Impulse,
                   PhysicsWorld* const physicsWorld,
                   PhysicsHandler* const physHandler)
{
    for(UInt32 i(0) ; i<allPhysicsBodies.size() ; ++i)
    {
        Vec3f Direction(allPhysicsBodies[i]->getPosition()-Location.subZero());

        Real32 Distance(Direction.length());
        Direction.normalize();

        allPhysicsBodies[i]->addForce(physicsWorld->impulseToForce(physHandler->getStepSize(), Direction*Impulse*(1.0f/Distance)));
        //The bodies need to be enabled because they may be auto-disabled when they
        //come to rest
        //The bodies are not re-enabled until a new collision is detected
        allPhysicsBodies[i]->setEnable(true);
    }
}

void keyPressed(KeyEventDetails* const details,
                Node* const spaceGroupNode,
                PhysicsWorld* const physicsWorld,
                PhysicsHashSpace* const physicsSpace,
                PhysicsHandler* const physHandler)
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
                allPhysicsBodies.push_back(buildSphere(spaceGroupNode,
                                                       physicsWorld,
                                                       physicsSpace));
            }
            break;
        case KeyEventDetails::KEY_B:
            {
                Vec3f BoxSize(1.0,1.0,1.0);
                Pnt3f BoxPosition((Real32)(rand()%10)-5.0, (Real32)(rand()%10)-5.0, 10.0);
                allPhysicsBodies.push_back(buildBox(BoxPosition,
                                                    BoxSize,
                                                    Color3f(0.0f,1.0f,0.0f),
                                                    spaceGroupNode,
                                                    physicsWorld,
                                                    physicsSpace));
            }
            break;
        case KeyEventDetails::KEY_E:
            makeExplosion(Pnt3f(0.0f,0.0f,-5.0f),
                          1280.0f,
                          physicsWorld,
                          physHandler);
            break;
        case KeyEventDetails::KEY_1:
            makeExplosion(Pnt3f(0.0f,0.0f,-5.0f),
                          20.0f,
                          physicsWorld,
                          physHandler);
            break;
        case KeyEventDetails::KEY_2:
            makeExplosion(Pnt3f(0.0f,0.0f,-5.0f),
                          80.0f,
                          physicsWorld,
                          physHandler);
            break;
        case KeyEventDetails::KEY_3:
            makeExplosion(Pnt3f(0.0f,0.0f,-5.0f),
                          320.0f,
                          physicsWorld,
                          physHandler);
            break;
        case KeyEventDetails::KEY_4:
            makeExplosion(Pnt3f(0.0f,0.0f,-5.0f),
                          1280.0f,
                          physicsWorld,
                          physHandler);
            break;
        case KeyEventDetails::KEY_5:
            makeExplosion(Pnt3f(0.0f,0.0f,-5.0f),
                          5120.0f,
                          physicsWorld,
                          physHandler);
            break;
        case KeyEventDetails::KEY_6:
            makeExplosion(Pnt3f(0.0f,0.0f,-5.0f),
                          20480.0f,
                          physicsWorld,
                          physHandler);
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


// Initialize GLUT & OpenSG and set up the rootNode
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
        NodeUnrecPtr TorusNode = makeTorus(.5, 2, 32, 32);

        //Make Main Scene Node
        NodeUnrecPtr scene = makeCoredNode<Group>();
        setName(scene, "scene");
        NodeRecPtr rootNode = Node::create();
        setName(rootNode, "rootNode");
        ComponentTransformUnrecPtr Trans = ComponentTransform::create();
        rootNode->setCore(Trans);

        // add the torus as a child
        rootNode->addChild(scene);

        //Setup Physics Scene
        PhysicsWorldRecPtr physicsWorld = PhysicsWorld::create();
        physicsWorld->setWorldContactSurfaceLayer(0.005);
        physicsWorld->setAutoDisableFlag(1);
        physicsWorld->setAutoDisableTime(0.75);
        physicsWorld->setWorldContactMaxCorrectingVel(100.0);
        physicsWorld->setGravity(Vec3f(0.0, 0.0, -9.81));

        //physicsSpace = PhysicsSimpleSpace::create();
        //physicsSpace = PhysicsQuadTreeSpace::create();
        //physicsSpace = PhysicsHashSpace::create();
        PhysicsHashSpaceRecPtr physicsSpace = PhysicsHashSpace::create();

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

        PhysicsHandlerRecPtr physHandler = PhysicsHandler::create();
        physHandler->setWorld(physicsWorld);
        physHandler->pushToSpaces(physicsSpace);
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

        TutorialWindow->connectKeyPressed(boost::bind(keyPressed, _1,
                                                      spaceGroupNode.get(),
                                                      physicsWorld.get(),
                                                      physicsSpace.get(),
                                                      physHandler.get()));

        // tell the manager what to manage
        sceneManager.setRoot  (rootNode);

        // show the whole rootNode
        sceneManager.showAll();

        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "05Explosion");

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
PhysicsBodyUnrecPtr  buildBox(const Pnt3f& Position,
                              const Vec3f& Dimensions,
                              const Color3f& Color,
                              Node* const spaceGroupNode,
                              PhysicsWorld* const physicsWorld,
                              PhysicsHashSpace* const physicsSpace)
{
    Matrix m;
    //create OpenSG mesh
    GeometryUnrecPtr box;
    NodeUnrecPtr boxNode = makeBox(Dimensions.x(), Dimensions.y(), Dimensions.z(), 1, 1, 1);
    box = dynamic_cast<Geometry*>(boxNode->getCore());
    SimpleMaterialUnrecPtr box_mat = SimpleMaterial::create();
    box_mat->setAmbient(Color3f(0.0,0.0,0.0));
    box_mat->setDiffuse(Color);
    box->setMaterial(box_mat);
    TransformUnrecPtr boxTrans;
    NodeUnrecPtr boxTransNode = makeCoredNode<Transform>(&boxTrans);
    m.setIdentity();
    m.setTranslate(Position);
    boxTrans->setMatrix(m);

    //create ODE data
    PhysicsBodyUnrecPtr boxBody = PhysicsBody::create(physicsWorld);
    boxBody->setPosition(Vec3f(Position));
    boxBody->setBoxMass(1.0,Dimensions.x(), Dimensions.y(), Dimensions.z());
    boxBody->setLinearDamping(0.0001);
    boxBody->setAngularDamping(0.0001);
    PhysicsBoxGeomUnrecPtr boxGeom = PhysicsBoxGeom::create();
    boxGeom->setBody(boxBody);
    boxGeom->setSpace(physicsSpace);
    boxGeom->setLengths(Dimensions);

    //add attachments
    boxNode->addAttachment(boxGeom);
    boxTransNode->addAttachment(boxBody);
    boxTransNode->addChild(boxNode);

    //add to SceneGraph
    spaceGroupNode->addChild(boxTransNode);

    return boxBody;
}

//////////////////////////////////////////////////////////////////////////
//! build a sphere
//////////////////////////////////////////////////////////////////////////
PhysicsBodyUnrecPtr  buildSphere(Node* const spaceGroupNode,
                                 PhysicsWorld* const physicsWorld,
                                 PhysicsHashSpace* const physicsSpace)
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

