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
void buildHingeJointMesh(Node* const spaceGroupNode,
                         PhysicsWorld* const physicsWorld,
                         PhysicsHashSpace* const physicsSpace);
void buildBallJointMesh(Node* const spaceGroupNode,
                        PhysicsWorld* const physicsWorld,
                        PhysicsHashSpace* const physicsSpace);
void buildMotorJointMesh(Node* const spaceGroupNode,
                         PhysicsWorld* const physicsWorld,
                         PhysicsHashSpace* const physicsSpace);

void keyPressed(KeyEventDetails* const details,
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
        case KeyEventDetails::KEY_H:
            {
                buildHingeJointMesh(spaceGroupNode,
                                    physicsWorld,
                                    physicsSpace);
            }
            break;
        case KeyEventDetails::KEY_B:
            {
                buildBallJointMesh(spaceGroupNode,
                                   physicsWorld,
                                   physicsSpace);
            }
            break;
        case KeyEventDetails::KEY_M:
            {
                buildMotorJointMesh(spaceGroupNode,
                                    physicsWorld,
                                    physicsSpace);
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
        physicsWorld->setCfm(0.001);
        physicsWorld->setErp(0.2);

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
        GroupUnrecPtr spaceGroup;
        NodeRecPtr spaceGroupNode = makeCoredNode<Group>(&spaceGroup);
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
        planeGeom->setSpace(hashSpace);

        //add Attachments to nodes...
        spaceGroupNode->addAttachment(hashSpace);
        spaceGroupNode->addChild(planeNode);

        planeNode->addAttachment(planeGeom);

        scene->addChild(spaceGroupNode);

        TutorialWindow->connectKeyPressed(boost::bind(keyPressed, _1,
                                                      spaceGroupNode.get(),
                                                      physicsWorld.get(),
                                                      hashSpace.get()));

        // tell the manager what to manage
        sceneManager.setRoot  (rootNode);

        // show the whole rootNode
        sceneManager.getNavigator()->set(Pnt3f(-10.0,10.0,15.0), Pnt3f(0.0,0.0,0.0), Vec3f(0.0,0.0,1.0));
        sceneManager.getNavigator()->setMotionFactor(1.0f);
        sceneManager.getCamera()->setFar(10000.0f);
        sceneManager.getCamera()->setNear(0.1f);

        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "02Joints");

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
//! build a Hinge joint with attached Meshes
//////////////////////////////////////////////////////////////////////////
void buildHingeJointMesh(Node* const spaceGroupNode,
                         PhysicsWorld* const physicsWorld,
                         PhysicsHashSpace* const physicsSpace)
{
    Vec3f Box1Size(1.0,1.0,0.1),
    Box2Size(1.0,1.0,1.0);
    Pnt3f Box1Position((Real32)(rand()%10)-5.0, (Real32)(rand()%10)-5.0, 10.0);
    Pnt3f Box2Position(Box1Position + (Vec3f(Box1Size.x()+.05,0.0,0.0)));

    PhysicsBodyUnrecPtr Box1Body = buildBox(Box1Position,
                                            Box1Size,
                                            Color3f(0.0f,1.0f,0.0f),
                                            spaceGroupNode,
                                            physicsWorld,
                                            physicsSpace);

    PhysicsBodyUnrecPtr Box2Body = buildBox(Box2Position,
                                            Box2Size,
                                            Color3f(0.0f,0.5f,0.0f),
                                            spaceGroupNode,
                                            physicsWorld,
                                            physicsSpace );

    //Create Hinge Joint
    PhysicsHingeJointUnrecPtr TutorialHingeJoint = PhysicsHingeJoint::create(Box1Body->getWorld());
    TutorialHingeJoint->setFirstBody(Box1Body);
    TutorialHingeJoint->setSecondBody(Box2Body);
    TutorialHingeJoint->setAxis(Vec3f(0.0,1.0,0.0));
    TutorialHingeJoint->setAnchor(Vec3f(Box1Position) + (Vec3f(Box1Size.x()/2,0.0,0.0)));
    TutorialHingeJoint->setLoStop(-0.3);
    TutorialHingeJoint->setHiStop(0.3);

    commitChanges();
}

void buildMotorJointMesh(Node* const spaceGroupNode,
                         PhysicsWorld* const physicsWorld,
                         PhysicsHashSpace* const physicsSpace)
{
    Vec3f Box1Size(1.0,1.5,0.1),
          Box2Size(1.0,1.0,1.0);
    Pnt3f Box1Position((Real32)(rand()%10)-5.0, (Real32)(rand()%10)-5.0, 10.0);
    Pnt3f Box2Position(Box1Position + (Vec3f(Box1Size.x()+0.01,0.0,0.0)));

    PhysicsBodyUnrecPtr Box1Body = buildBox(Box1Position,
                                            Box1Size,
                                            Color3f(0.0f,1.0f,0.0f),
                                            spaceGroupNode,
                                            physicsWorld,
                                            physicsSpace);

    PhysicsBodyUnrecPtr Box2Body = buildBox(Box2Position,
                                            Box2Size,
                                            Color3f(0.0f,0.5f,0.0f),
                                            spaceGroupNode,
                                            physicsWorld,
                                            physicsSpace );

    //Create AMotor Joint
    PhysicsAMotorJointUnrecPtr TutorialAMotorJoint = PhysicsAMotorJoint::create(Box1Body->getWorld());
    TutorialAMotorJoint->setFirstBody(Box1Body);
    TutorialAMotorJoint->setSecondBody(NULL);
    TutorialAMotorJoint->setMode(dAMotorUser);
    TutorialAMotorJoint->setNumAxes(1);
    TutorialAMotorJoint->setAxis1Properties(Vec3f(1.0,0.0,0.0),1);

    TutorialAMotorJoint->setFMax(13.0);
    TutorialAMotorJoint->setVel(6.0);

    PhysicsHingeJointUnrecPtr TutorialHingeJoint = PhysicsHingeJoint::create(Box1Body->getWorld());
    TutorialHingeJoint->setFirstBody(Box1Body);
    TutorialHingeJoint->setSecondBody(Box2Body);
    TutorialHingeJoint->setAxis(Vec3f(1.0,0.0,0.0));
    TutorialHingeJoint->setAnchor(Vec3f(Box1Position) + (Vec3f(Box1Size.x()/2,0.0,0.0)));
    commitChanges();

}

void buildUniversalJointMesh(Node* const spaceGroupNode,
                             PhysicsWorld* const physicsWorld,
                             PhysicsHashSpace* const physicsSpace)
{
    /*PhysicsUniversalJointUnrecPtr TutorialUniversalJoint = PhysicsUniversalJoint::create(Box1Body->getWorld());
      TutorialUniversalJoint->setFirstBody(Box1Body);
      TutorialUniversalJoint->setSecondBody(Box2Body);
      TutorialUniversalJoint->setAnchor(Box1Position + (Vec3f(Box1Size.x()/2+0.005,0.0,0.0)));
      TutorialUniversalJoint->setAxis1(Vec3f(0.0,0.0,1.0));
      TutorialUniversalJoint->setAxis2(Vec3f(0.0,1.0,0.0));
      TutorialUniversalJoint->setLoStop(-0.3);
      TutorialUniversalJoint->setHiStop(0.3);
      TutorialUniversalJoint->setLoStop2(-0.3);
      TutorialUniversalJoint->setHiStop2(0.3);*/
    commitChanges();
}

void buildBallJointMesh(Node* const spaceGroupNode,
                        PhysicsWorld* const physicsWorld,
                        PhysicsHashSpace* const physicsSpace)
{
    Vec3f Box1Size(1.0,0.1,0.1),
    Box2Size(1.0,1.0,1.0);
    Pnt3f Box1Position((Real32)(rand()%10)-5.0, (Real32)(rand()%10)-5.0, 10.0);
    Pnt3f Box2Position(Box1Position + (Vec3f(Box1Size.x()+0.1,0.0,0.0)));

    PhysicsBodyUnrecPtr Box1Body = buildBox(Box1Position,
                                            Box1Size,
                                            Color3f(0.0f,1.0f,0.0f),
                                            spaceGroupNode,
                                            physicsWorld,
                                            physicsSpace);

    PhysicsBodyUnrecPtr Box2Body = buildBox(Box2Position,
                                            Box2Size,
                                            Color3f(0.0f,0.5f,0.0f),
                                            spaceGroupNode,
                                            physicsWorld,
                                            physicsSpace );

    //Create Ball Joint
    PhysicsBallJointUnrecPtr TutorialBallJoint = PhysicsBallJoint::create(Box1Body->getWorld());
    TutorialBallJoint->setFirstBody(Box1Body);
    TutorialBallJoint->setSecondBody(Box2Body);
    TutorialBallJoint->setAnchor(Vec3f(Box1Position) + (Vec3f(Box1Size.x()/2+0.05,0.0,0.0)));

    commitChanges();
}
