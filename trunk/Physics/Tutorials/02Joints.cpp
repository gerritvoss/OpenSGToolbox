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
void buildHingeJointMesh(void);
void buildBallJointMesh(void);
void buildMotorJointMesh(void);

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

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
       case KeyEvent::KEY_H:
            {
                buildHingeJointMesh();
            }
            break;
       case KeyEvent::KEY_B:
            {
                buildBallJointMesh();
            }
            break;
       case KeyEvent::KEY_M:
            {
                buildMotorJointMesh();
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
                                        "OpenSG 02Joints Window");

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindowEventProducer->getWindow());

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
                              PhysicsWorld::GravityFieldMask | 
                              PhysicsWorld::CfmFieldMask | 
                              PhysicsWorld::ErpFieldMask);
        physicsWorld->setWorldContactSurfaceLayer(0.005);
        physicsWorld->setAutoDisableFlag(1);
        physicsWorld->setAutoDisableTime(0.75);
        physicsWorld->setWorldContactMaxCorrectingVel(100.0);
        physicsWorld->setGravity(Vec3f(0.0, 0.0, -9.81));
        physicsWorld->setCfm(0.001);
        physicsWorld->setErp(0.2);
    endEditCP(physicsWorld, PhysicsWorld::WorldContactSurfaceLayerFieldMask | 
                              PhysicsWorld::AutoDisableFlagFieldMask | 
                              PhysicsWorld::AutoDisableTimeFieldMask | 
                              PhysicsWorld::WorldContactMaxCorrectingVelFieldMask | 
                              PhysicsWorld::GravityFieldMask | 
                              PhysicsWorld::CfmFieldMask | 
                              PhysicsWorld::ErpFieldMask);

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


PhysicsBodyPtr buildBox(Vec3f Dimensions, Pnt3f Position)
{
    Matrix m;
    //create OpenSG mesh
    GeometryPtr box;
    NodePtr boxNode = makeBox(Dimensions.x(), Dimensions.y(), Dimensions.z(), 1, 1, 1);
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
    m.setTranslate(Position);
    beginEditCP(boxTrans, Transform::MatrixFieldMask);
        boxTrans->setMatrix(m);
    endEditCP(boxTrans, Transform::MatrixFieldMask);

    //create ODE data
    PhysicsBodyPtr boxBody = PhysicsBody::create(physicsWorld);
    CPEdit(boxBody, PhysicsBody::PositionFieldMask | PhysicsBody::LinearDampingFieldMask | PhysicsBody::AngularDampingFieldMask);
        boxBody->setPosition(Vec3f(Position));
        boxBody->setBoxMass(1.0,Dimensions.x(), Dimensions.y(), Dimensions.z());
        boxBody->setLinearDamping(0.0001);
        boxBody->setAngularDamping(0.0001);
    PhysicsBoxGeomPtr boxGeom = PhysicsBoxGeom::create();
    beginEditCP(boxGeom, PhysicsBoxGeom::BodyFieldMask | PhysicsBoxGeom::SpaceFieldMask | PhysicsBoxGeom::LengthsFieldMask);
        boxGeom->setBody(boxBody);
        boxGeom->setSpace(hashSpace);
        boxGeom->setLengths(Dimensions);
    endEditCP(boxGeom, PhysicsBoxGeom::BodyFieldMask | PhysicsBoxGeom::SpaceFieldMask | PhysicsBoxGeom::LengthsFieldMask);

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

    return boxBody;
}
//////////////////////////////////////////////////////////////////////////
//! build a Hinge joint with attached Meshes
//////////////////////////////////////////////////////////////////////////
void buildHingeJointMesh(void)
{
    Vec3f Box1Size(1.0,1.0,0.1),
          Box2Size(1.0,1.0,1.0);
    Pnt3f Box1Position((Real32)(rand()%10)-5.0, (Real32)(rand()%10)-5.0, 10.0);
    Pnt3f Box2Position(Box1Position + (Vec3f(Box1Size.x()+.05,0.0,0.0)));

    PhysicsBodyPtr Box1Body = buildBox(Box1Size, Box1Position);
    PhysicsBodyPtr Box2Body = buildBox(Box2Size, Box2Position);

    //Create Hinge Joint
    PhysicsHingeJointPtr TutorialHingeJoint = PhysicsHingeJoint::create(Box1Body->getWorld());
    beginEditCP(TutorialHingeJoint, PhysicsHingeJoint::FirstBodyFieldMask | 
                                    PhysicsHingeJoint::SecondBodyFieldMask | 
                                    PhysicsHingeJoint::AxisFieldMask | 
                                    PhysicsHingeJoint::AnchorFieldMask | 
                                    PhysicsHingeJoint::LoStopFieldMask | 
                                    PhysicsHingeJoint::HiStopFieldMask);
        TutorialHingeJoint->setFirstBody(Box1Body);
        TutorialHingeJoint->setSecondBody(Box2Body);
        TutorialHingeJoint->setAxis(Vec3f(0.0,1.0,0.0));
        TutorialHingeJoint->setAnchor(Box1Position + (Vec3f(Box1Size.x()/2,0.0,0.0)));
        TutorialHingeJoint->setLoStop(-0.3);
        TutorialHingeJoint->setHiStop(0.3);
    endEditCP(TutorialHingeJoint, PhysicsHingeJoint::FirstBodyFieldMask | 
                                    PhysicsHingeJoint::SecondBodyFieldMask | 
                                    PhysicsHingeJoint::AxisFieldMask | 
                                    PhysicsHingeJoint::AnchorFieldMask | 
                                    PhysicsHingeJoint::LoStopFieldMask | 
                                    PhysicsHingeJoint::HiStopFieldMask);

}

void buildMotorJointMesh(void)
{
    Vec3f Box1Size(1.0,1.5,0.1),
          Box2Size(1.0,1.0,1.0);
    Pnt3f Box1Position((Real32)(rand()%10)-5.0, (Real32)(rand()%10)-5.0, 10.0);
    Pnt3f Box2Position(Box1Position + (Vec3f(Box1Size.x()+0.01,0.0,0.0)));

    PhysicsBodyPtr Box1Body = buildBox(Box1Size, Box1Position);
    PhysicsBodyPtr Box2Body = buildBox(Box2Size, Box2Position);

    //Create AMotor Joint
    PhysicsAMotorJointPtr TutorialAMotorJoint = PhysicsAMotorJoint::create(Box1Body->getWorld());
    beginEditCP(TutorialAMotorJoint, PhysicsAMotorJoint::FirstBodyFieldMask | 
                                    PhysicsAMotorJoint::SecondBodyFieldMask | 
                                    PhysicsAMotorJoint::ModeFieldMask | 
                                    PhysicsAMotorJoint::NumAxesFieldMask | 
                                    PhysicsAMotorJoint::Axis1FieldMask | 
                                    PhysicsAMotorJoint::Axis1ReferenceFrameFieldMask | 
                                    PhysicsAMotorJoint::FMaxFieldMask | 
                                    PhysicsAMotorJoint::VelFieldMask);
        TutorialAMotorJoint->setFirstBody(Box1Body);
        TutorialAMotorJoint->setSecondBody(NullFC);
        TutorialAMotorJoint->setMode(dAMotorUser);
        TutorialAMotorJoint->setNumAxes(1);
        TutorialAMotorJoint->setAxis1Properties(Vec3f(1.0,0.0,0.0),1);

        TutorialAMotorJoint->setFMax(13.0);
        TutorialAMotorJoint->setVel(6.0);
    endEditCP(TutorialAMotorJoint, PhysicsAMotorJoint::FirstBodyFieldMask | 
                                    PhysicsAMotorJoint::SecondBodyFieldMask | 
                                    PhysicsAMotorJoint::ModeFieldMask | 
                                    PhysicsAMotorJoint::NumAxesFieldMask | 
                                    PhysicsAMotorJoint::Axis1FieldMask | 
                                    PhysicsAMotorJoint::Axis1ReferenceFrameFieldMask | 
                                    PhysicsAMotorJoint::FMaxFieldMask | 
                                    PhysicsAMotorJoint::VelFieldMask);
    
    PhysicsHingeJointPtr TutorialHingeJoint = PhysicsHingeJoint::create(Box1Body->getWorld());
    beginEditCP(TutorialHingeJoint, PhysicsHingeJoint::FirstBodyFieldMask | 
                                    PhysicsHingeJoint::SecondBodyFieldMask | 
                                    PhysicsHingeJoint::AxisFieldMask | 
                                    PhysicsHingeJoint::AnchorFieldMask);
        TutorialHingeJoint->setFirstBody(Box1Body);
        TutorialHingeJoint->setSecondBody(Box2Body);
        TutorialHingeJoint->setAxis(Vec3f(1.0,0.0,0.0));
        TutorialHingeJoint->setAnchor(Box1Position + (Vec3f(Box1Size.x()/2,0.0,0.0)));
    endEditCP(TutorialHingeJoint, PhysicsHingeJoint::FirstBodyFieldMask | 
                                    PhysicsHingeJoint::SecondBodyFieldMask | 
                                    PhysicsHingeJoint::AxisFieldMask | 
                                    PhysicsHingeJoint::AnchorFieldMask );

}

void buildUniversalJointMesh(void)
{
    /*PhysicsUniversalJointPtr TutorialUniversalJoint = PhysicsUniversalJoint::create(Box1Body->getWorld());
    beginEditCP(TutorialUniversalJoint, PhysicsUniversalJoint::FirstBodyFieldMask | 
                                    PhysicsUniversalJoint::SecondBodyFieldMask | 
                                    PhysicsUniversalJoint::AnchorFieldMask | 
                                    PhysicsUniversalJoint::Axis1FieldMask | 
                                    PhysicsUniversalJoint::Axis2FieldMask | 
                                    PhysicsUniversalJoint::HiStopFieldMask | 
                                    PhysicsUniversalJoint::LoStopFieldMask | 
                                    PhysicsUniversalJoint::HiStop2FieldMask | 
                                    PhysicsUniversalJoint::LoStop2FieldMask);
        TutorialUniversalJoint->setFirstBody(Box1Body);
        TutorialUniversalJoint->setSecondBody(Box2Body);
        TutorialUniversalJoint->setAnchor(Box1Position + (Vec3f(Box1Size.x()/2+0.005,0.0,0.0)));
        TutorialUniversalJoint->setAxis1(Vec3f(0.0,0.0,1.0));
        TutorialUniversalJoint->setAxis2(Vec3f(0.0,1.0,0.0));
        TutorialUniversalJoint->setLoStop(-0.3);
        TutorialUniversalJoint->setHiStop(0.3);
        TutorialUniversalJoint->setLoStop2(-0.3);
        TutorialUniversalJoint->setHiStop2(0.3);
    endEditCP(TutorialUniversalJoint, PhysicsUniversalJoint::FirstBodyFieldMask | 
                                    PhysicsUniversalJoint::SecondBodyFieldMask | 
                                    PhysicsUniversalJoint::AnchorFieldMask | 
                                    PhysicsUniversalJoint::Axis1FieldMask | 
                                    PhysicsUniversalJoint::Axis2FieldMask | 
                                    PhysicsUniversalJoint::HiStopFieldMask | 
                                    PhysicsUniversalJoint::LoStopFieldMask | 
                                    PhysicsUniversalJoint::HiStop2FieldMask | 
                                    PhysicsUniversalJoint::LoStop2FieldMask);*/
}

void buildBallJointMesh(void)
{
    Vec3f Box1Size(1.0,0.1,0.1),
          Box2Size(1.0,1.0,1.0);
    Pnt3f Box1Position((Real32)(rand()%10)-5.0, (Real32)(rand()%10)-5.0, 10.0);
    Pnt3f Box2Position(Box1Position + (Vec3f(Box1Size.x()+0.1,0.0,0.0)));

    PhysicsBodyPtr Box1Body = buildBox(Box1Size, Box1Position);
    PhysicsBodyPtr Box2Body = buildBox(Box2Size, Box2Position);

    //Create Ball Joint
    PhysicsBallJointPtr TutorialBallJoint = PhysicsBallJoint::create(Box1Body->getWorld());
    beginEditCP(TutorialBallJoint, PhysicsBallJoint::FirstBodyFieldMask | 
                                    PhysicsBallJoint::SecondBodyFieldMask | 
                                    PhysicsBallJoint::AnchorFieldMask);
        TutorialBallJoint->setFirstBody(Box1Body);
        TutorialBallJoint->setSecondBody(Box2Body);
        TutorialBallJoint->setAnchor(Box1Position + (Vec3f(Box1Size.x()/2+0.05,0.0,0.0)));
    endEditCP(TutorialBallJoint, PhysicsBallJoint::FirstBodyFieldMask | 
                                    PhysicsBallJoint::SecondBodyFieldMask | 
                                    PhysicsBallJoint::AnchorFieldMask);

}
