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
#include "OSGGeoFunctions.h"
#include "OSGSceneFileHandler.h"
#include "OSGDirectionalLight.h"

// Input
#include "OSGKeyListener.h"
#include "OSGWindowUtils.h"

//Physics
#include "OSGPhysics.h"
#include "OSGPhysicsCharacteristicsDrawable.h"

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with , but that would be a bit tedious for this example
OSG_USING_NAMESPACE


// forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);
PhysicsBodyUnrecPtr  buildBox(const Pnt3f& Position,
                              const Vec3f& Dimensions,
                              const Color3f& Color,
                              Node* const spaceGroupNode,
                              PhysicsWorld* const physicsWorld,
                              PhysicsHashSpace* const physicsSpace);
PhysicsBodyRefPtr buildShip(Vec3f Dimensions, Pnt3f Position,
                            Node* const spaceGroupNode,
                            PhysicsWorld* const physicsWorld,
                            PhysicsHashSpace* const physicsSpace);
PhysicsLMotorJointRefPtr buildMotor(PhysicsBody* const ship);

Vec3f ForceOnCharacter;
bool _IsUpKeyDown(false);
bool _IsDownKeyDown(false);
bool _IsLeftKeyDown(false);
bool _IsRightKeyDown(false);

void keyPressed(KeyEventDetails* const details,
                Node* const spaceGroupNode,
                PhysicsWorld* const physicsWorld,
                PhysicsHashSpace* const physicsSpace,
                Node* const PhysDrawableNode)
{
    if(details->getKey() == KeyEventDetails::KEY_Q &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
    switch(details->getKey())
    {
        case KeyEventDetails::KEY_B:

            buildBox(Pnt3f((Real32)(rand()%100)-50.0,(Real32)(rand()%100)-50.0,25.0),
                     Vec3f(10.0,10.0,10.0),
                     Color3f(0.0f,1.0f,0.0f),
                     spaceGroupNode,
                     physicsWorld,
                     physicsSpace);
            break;
        case KeyEventDetails::KEY_UP:
            _IsUpKeyDown = true;
            break;
        case KeyEventDetails::KEY_DOWN:
            _IsDownKeyDown = true;
            break;
        case KeyEventDetails::KEY_LEFT:
            _IsLeftKeyDown = true;
            break;
        case KeyEventDetails::KEY_RIGHT:
            _IsRightKeyDown = true;
            break;
        case KeyEventDetails::KEY_D:
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

void keyReleased(KeyEventDetails* const details)
{
    switch(details->getKey())
    {
        case KeyEventDetails::KEY_UP:
            _IsUpKeyDown = false;
            break;
        case KeyEventDetails::KEY_DOWN:
            _IsDownKeyDown = false;
            break;
        case KeyEventDetails::KEY_LEFT:
            _IsLeftKeyDown = false;
            break;
        case KeyEventDetails::KEY_RIGHT:
            _IsRightKeyDown = false;
            break;
    }
}
void handleUpdate(UpdateEventDetails* const details,
                  PhysicsBody* const ShipBody,
                  PhysicsLMotorJoint* const ShipMotor)
{
    ForceOnCharacter.setValues(0.0,0.0,0.0);
    Real32 PushForce(10000.0);
    Real32 Speed(20.0);
    if(_IsUpKeyDown)
    {
        ForceOnCharacter += Vec3f(0.0, PushForce, 0.0);
    }
    if(_IsDownKeyDown)
    {
        ForceOnCharacter += Vec3f(0.0, -PushForce, 0.0);
    }
    if(_IsLeftKeyDown)
    {
        ForceOnCharacter += Vec3f(-PushForce, 0.0, 0.0);
    }
    if(_IsRightKeyDown)
    {
        ForceOnCharacter += Vec3f(PushForce, 0.0, 0.0);
    }
    if(ForceOnCharacter != Vec3f(0.0,0.0,0.0))
    {
        ShipBody->setEnable(true);
    }
    if(ForceOnCharacter.x() !=0.0)
    {
        ShipMotor->setFMax(osgAbs(ForceOnCharacter.x()));
        ShipMotor->setVel(osgSgn(ForceOnCharacter.x())*Speed);
    }
    else
    {
        ShipMotor->setFMax(0.0);
        ShipMotor->setVel(0.0);
    }
    if(ForceOnCharacter.y() !=0.0)
    {
        ShipMotor->setFMax2(osgAbs(ForceOnCharacter.y()));
        ShipMotor->setVel2(osgSgn(ForceOnCharacter.y())*Speed);
    }
    else
    {
        ShipMotor->setFMax2(0.0);
        ShipMotor->setVel2(0.0);
    }
    if(ForceOnCharacter.z() !=0.0)
    {
        ShipMotor->setFMax3(osgAbs(ForceOnCharacter.z()));
        ShipMotor->setVel3(osgSgn(ForceOnCharacter.z())*Speed);
    }
    else
    {
        ShipMotor->setFMax3(0.0);
        ShipMotor->setVel3(0.0);
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

PhysicsLMotorJointRefPtr buildMotor(PhysicsBody* const ship)
{
    //Create LMotor Joint
    PhysicsLMotorJointRefPtr TutorialLMotorJoint = PhysicsLMotorJoint::create(ship->getWorld());
    TutorialLMotorJoint->setFirstBody(ship);
    TutorialLMotorJoint->setSecondBody(NULL);
    TutorialLMotorJoint->setNumAxes(3);
    TutorialLMotorJoint->setAxis1Properties(Vec3f(1.0,0.0,0.0),1);
    TutorialLMotorJoint->setAxis2Properties(Vec3f(0.0,1.0,0.0),1);
    TutorialLMotorJoint->setAxis3Properties(Vec3f(0.0,0.0,1.0),1);

    return TutorialLMotorJoint;
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
        TutorialWindow->connectKeyReleased(boost::bind(keyReleased, _1));

        //Make Main Scene Node
        NodeRefPtr scene = makeCoredNode<Group>();
        setName(scene, "scene");
        NodeRecPtr rootNode = Node::create();
        setName(rootNode, "rootNode");
        ComponentTransformRefPtr Trans;
        Trans = ComponentTransform::create();
        {
            rootNode->setCore(Trans);

            // add the torus as a child
            rootNode->addChild(scene);
        }

        //Make The Physics Characteristics Node
        PhysicsCharacteristicsDrawableUnrecPtr PhysDrawable = PhysicsCharacteristicsDrawable::create();
        PhysDrawable->setRoot(rootNode);

        NodeRecPtr PhysDrawableNode = Node::create();
        PhysDrawableNode->setCore(PhysDrawable);
        PhysDrawableNode->setTravMask(TypeTraits<UInt32>::getMin());

        rootNode->addChild(PhysDrawableNode);

        //Light Beacon
        NodeRefPtr TutorialLightBeacon = makeCoredNode<Transform>();

        //Light Node
        DirectionalLightRefPtr TutorialLight = DirectionalLight::create();
        TutorialLight->setDirection(0.0,0.0,-1.0);
        TutorialLight->setBeacon(TutorialLightBeacon);

        NodeRefPtr TutorialLightNode = Node::create();
        TutorialLightNode->setCore(TutorialLight);

        scene->addChild(TutorialLightNode);
        scene->addChild(TutorialLightBeacon);


        //Setup Physics Scene
        PhysicsWorldRecPtr physicsWorld = PhysicsWorld::create();
        physicsWorld->setWorldContactSurfaceLayer(0.01);
        physicsWorld->setAutoDisableFlag(1);
        physicsWorld->setAutoDisableTime(0.75);
        physicsWorld->setWorldContactMaxCorrectingVel(1.0);
        //physicsWorld->setGravity(Vec3f(0.0, 0.0, -9.81));
        //physicsWorld->setCfm(0.001);
        //physicsWorld->setErp(0.2);

        PhysicsHashSpaceRecPtr hashSpace = PhysicsHashSpace::create();

        PhysicsHandlerRecPtr physHandler = PhysicsHandler::create();
        physHandler->setWorld(physicsWorld);
        physHandler->pushToSpaces(hashSpace);
        physHandler->setUpdateNode(rootNode);
        physHandler->attachUpdateProducer(TutorialWindow);


        rootNode->addAttachment(physHandler);    
        rootNode->addAttachment(physicsWorld);
        rootNode->addAttachment(hashSpace);


        /************************************************************************/
        /* create spaces, geoms and bodys                                                                     */
        /************************************************************************/
        //create a group for our space
        GroupRefPtr spaceGroup;
        NodeRecPtr spaceGroupNode = makeCoredNode<Group>(&spaceGroup);
        //add Attachments to nodes...
        spaceGroupNode->addAttachment(hashSpace);

        TutorialLightNode->addChild(spaceGroupNode);

        //Create Character
        PhysicsBodyRefPtr ShipBody = buildShip(Vec3f(3.0,3.0,10.0),
                                               Pnt3f((Real32)(rand()%100)-50.0,(Real32)(rand()%100)-50.0,25.0),
                                                      spaceGroupNode,
                                                      physicsWorld,
                                                      hashSpace);
        PhysicsLMotorJointRefPtr ShipMotor = buildMotor(ShipBody);

        for(UInt32 i(0) ; i<5 ; ++i)
        {
            buildBox(Pnt3f((Real32)(rand()%100)-50.0,(Real32)(rand()%100)-50.0,25.0),
                     Vec3f(10.0,10.0,10.0),
                     Color3f(0.0f,1.0f,0.0f),
                     spaceGroupNode,
                     physicsWorld,
                     hashSpace);
        }
        TutorialWindow->connectKeyPressed(boost::bind(keyPressed, _1,
                                                      spaceGroupNode.get(),
                                                      physicsWorld.get(),
                                                      hashSpace.get(),
                                                      PhysDrawableNode.get()));

        TutorialWindow->connectUpdate(boost::bind(handleUpdate, _1,
                                                  ShipBody.get(),
                                                  ShipMotor.get()));

        // tell the manager what to manage
        sceneManager.setRoot  (rootNode);

        // show the whole rootNode
        sceneManager.showAll();

        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "04ZeroGravityShip");

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
//! build a ship
//////////////////////////////////////////////////////////////////////////
PhysicsBodyRefPtr buildShip(Vec3f Dimensions, Pnt3f Position,
                            Node* const spaceGroupNode,
                            PhysicsWorld* const physicsWorld,
                            PhysicsHashSpace* const physicsSpace)
{
    Real32 Radius(osgMax(Dimensions.x(), Dimensions.y())/2.0f);
    Real32 Length(Dimensions.z() - 2.0f*Radius);

    Matrix m;
    //create OpenSG mesh
    GeometryRefPtr box;
    NodeRefPtr boxNode = makeBox(Dimensions.x(), Dimensions.y(), Dimensions.z(), 1, 1, 1);
    box = dynamic_cast<Geometry*>(boxNode->getCore());
    SimpleMaterialRefPtr box_mat = SimpleMaterial::create();
    box_mat->setAmbient(Color3f(0.0,0.0,0.0));
    box_mat->setDiffuse(Color3f(1.0,1.0 ,0.0));
    box->setMaterial(box_mat);
    TransformRefPtr boxTrans;
    NodeRefPtr boxTransNode = makeCoredNode<Transform>(&boxTrans);
    m.setIdentity();
    m.setTranslate(Position - Vec3f(0.0f,0.0f,0.5f*Dimensions.z()));
    boxTrans->setMatrix(m);

    for(UInt32 i(0) ; i<box->getPositions()->size() ; ++i)
    {
        box->getPositions()->setValue<Pnt3f>(box->getPositions()->getValue<Pnt3f>(i) + Vec3f(0.0,0.0,Dimensions.z()/2.0f),i);
    }


    //create ODE data

    PhysicsBodyRefPtr CapsuleBody = PhysicsBody::create(physicsWorld);
    CapsuleBody->setPosition(Vec3f(Position - Vec3f(0.0f,0.0f,0.5f*Dimensions.z())));
    CapsuleBody->setLinearDamping(0.01);
    CapsuleBody->setMaxAngularSpeed(0.0);
    CapsuleBody->setCapsuleMass(1.0,3,Radius, Length);

    PhysicsCapsuleGeomRefPtr CapsuleGeom = PhysicsCapsuleGeom::create();
    CapsuleGeom->setBody(CapsuleBody);
    CapsuleGeom->setOffsetPosition(Vec3f(0.0f,0.0f,0.5f*Dimensions.z()));
    CapsuleGeom->setSpace(physicsSpace);
    CapsuleGeom->setRadius(Radius);
    CapsuleGeom->setLength(Length);

    //add attachments
    boxNode->addAttachment(CapsuleGeom);
    boxTransNode->addAttachment(CapsuleBody);
    boxTransNode->addChild(boxNode);

    //add to SceneGraph
    spaceGroupNode->addChild(boxTransNode);

    commitChanges();

    return CapsuleBody;
}
