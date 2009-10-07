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
#include <OpenSG/OSGGeoFunctions.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGDirectionalLight.h>

// Input
#include <OpenSG/Input/OSGKeyListener.h>
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
PhysicsBodyPtr buildBox(Vec3f Dimensions, Pnt3f Position);
PhysicsBodyPtr buildShip(Vec3f Dimensions, Pnt3f Position);
PhysicsLMotorJointPtr buildMotor(PhysicsBodyPtr ship);

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;

PhysicsHandlerPtr physHandler;
PhysicsWorldPtr physicsWorld;
PhysicsHashSpacePtr hashSpace;
PhysicsBodyPtr ShipBody;
PhysicsLMotorJointPtr ShipMotor;
Vec3f ForceOnCharacter;
bool _IsUpKeyDown(false);
bool _IsDownKeyDown(false);
bool _IsLeftKeyDown(false);
bool _IsRightKeyDown(false);

//just for hierarchy
NodePtr spaceGroupNode;

NodePtr rootNode;

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           TutorialWindowEventProducer->closeWindow();
       }
       switch(e->getKey())
       {
       case KeyEvent::KEY_B:
           buildBox(Vec3f(10.0,10.0,10.0), Pnt3f((Real32)(rand()%100)-50.0,(Real32)(rand()%100)-50.0,25.0));
           break;
	   case KeyEvent::KEY_UP:
           _IsUpKeyDown = true;
		   break;
	   case KeyEvent::KEY_DOWN:
           _IsDownKeyDown = true;
		   break;
	   case KeyEvent::KEY_LEFT:
           _IsLeftKeyDown = true;
		   break;
	   case KeyEvent::KEY_RIGHT:
           _IsRightKeyDown = true;
           break;
       }
   }

   virtual void keyReleased(const KeyEventPtr e)
   {
	   switch(e->getKey())
	   {
	   case KeyEvent::KEY_UP:
           _IsUpKeyDown = false;
		   break;
	   case KeyEvent::KEY_DOWN:
           _IsDownKeyDown = false;
		   break;
	   case KeyEvent::KEY_LEFT:
           _IsLeftKeyDown = false;
		   break;
	   case KeyEvent::KEY_RIGHT:
           _IsRightKeyDown = false;
           break;
       }
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

class TutorialUpdateListener : public UpdateListener
{
  public:
    virtual void update(const UpdateEventPtr e)
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
        beginEditCP(ShipMotor, PhysicsLMotorJoint::FMaxFieldMask | 
                               PhysicsLMotorJoint::VelFieldMask |
                               PhysicsLMotorJoint::FMax2FieldMask | 
                               PhysicsLMotorJoint::Vel2FieldMask |
                               PhysicsLMotorJoint::FMax3FieldMask | 
                               PhysicsLMotorJoint::Vel3FieldMask);
            if(ForceOnCharacter.x() !=0.0)
            {
                ShipMotor->setFMax(osgabs(ForceOnCharacter.x()));
                ShipMotor->setVel(osgSgn(ForceOnCharacter.x())*Speed);
            }
            else
            {
                ShipMotor->setFMax(0.0);
                ShipMotor->setVel(0.0);
            }
            if(ForceOnCharacter.y() !=0.0)
            {
                ShipMotor->setFMax2(osgabs(ForceOnCharacter.y()));
                ShipMotor->setVel2(osgSgn(ForceOnCharacter.y())*Speed);
            }
            else
            {
                ShipMotor->setFMax2(0.0);
                ShipMotor->setVel2(0.0);
            }
            if(ForceOnCharacter.z() !=0.0)
            {
                ShipMotor->setFMax3(osgabs(ForceOnCharacter.z()));
                ShipMotor->setVel3(osgSgn(ForceOnCharacter.z())*Speed);
            }
            else
            {
                ShipMotor->setFMax3(0.0);
                ShipMotor->setVel3(0.0);
            }
        endEditCP(ShipMotor, PhysicsLMotorJoint::FMaxFieldMask | 
                               PhysicsLMotorJoint::VelFieldMask |
                               PhysicsLMotorJoint::FMax2FieldMask | 
                               PhysicsLMotorJoint::Vel2FieldMask |
                               PhysicsLMotorJoint::FMax3FieldMask | 
                               PhysicsLMotorJoint::Vel3FieldMask);
    }
};

PhysicsLMotorJointPtr buildMotor(PhysicsBodyPtr ship)
{
    //Create LMotor Joint
    PhysicsLMotorJointPtr TutorialLMotorJoint = PhysicsLMotorJoint::create(ship->getWorld());
    beginEditCP(TutorialLMotorJoint, PhysicsLMotorJoint::FirstBodyFieldMask | 
                                    PhysicsLMotorJoint::SecondBodyFieldMask | 
                                    PhysicsLMotorJoint::NumAxesFieldMask | 
                                    PhysicsLMotorJoint::Axis1FieldMask | 
                                    PhysicsLMotorJoint::Axis1ReferenceFrameFieldMask |
                                    PhysicsLMotorJoint::Axis2FieldMask | 
                                    PhysicsLMotorJoint::Axis2ReferenceFrameFieldMask |
                                    PhysicsLMotorJoint::Axis3FieldMask | 
                                    PhysicsLMotorJoint::Axis3ReferenceFrameFieldMask);
        TutorialLMotorJoint->setFirstBody(ship);
        TutorialLMotorJoint->setSecondBody(NullFC);
        TutorialLMotorJoint->setNumAxes(3);
        TutorialLMotorJoint->setAxis1Properties(Vec3f(1.0,0.0,0.0),1);
        TutorialLMotorJoint->setAxis2Properties(Vec3f(0.0,1.0,0.0),1);
        TutorialLMotorJoint->setAxis3Properties(Vec3f(0.0,0.0,1.0),1);
    endEditCP(TutorialLMotorJoint, PhysicsLMotorJoint::FirstBodyFieldMask | 
                                    PhysicsLMotorJoint::SecondBodyFieldMask | 
                                    PhysicsLMotorJoint::NumAxesFieldMask | 
                                    PhysicsLMotorJoint::Axis1FieldMask | 
                                    PhysicsLMotorJoint::Axis1ReferenceFrameFieldMask |
                                    PhysicsLMotorJoint::Axis2FieldMask | 
                                    PhysicsLMotorJoint::Axis2ReferenceFrameFieldMask |
                                    PhysicsLMotorJoint::Axis3FieldMask | 
                                    PhysicsLMotorJoint::Axis3ReferenceFrameFieldMask);

    return TutorialLMotorJoint;
}

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
	TutorialUpdateListener TheTutorialUpdateListener;
    TutorialWindowEventProducer->addUpdateListener(&TheTutorialUpdateListener);


    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

	
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

    //Light Beacon
    NodePtr TutorialLightBeacon = makeCoredNode<Transform>();

    //Light Node
    DirectionalLightPtr TutorialLight = DirectionalLight::create();
    TutorialLight->setDirection(0.0,0.0,-1.0);
    TutorialLight->setBeacon(TutorialLightBeacon);

    NodePtr TutorialLightNode = Node::create();
    TutorialLightNode->setCore(TutorialLight);

    scene->addChild(TutorialLightNode);
    scene->addChild(TutorialLightBeacon);


    //Setup Physics Scene
    physicsWorld = PhysicsWorld::create();
    beginEditCP(physicsWorld, PhysicsWorld::WorldContactSurfaceLayerFieldMask | 
                              PhysicsWorld::AutoDisableFlagFieldMask | 
                              PhysicsWorld::AutoDisableTimeFieldMask | 
                              PhysicsWorld::WorldContactMaxCorrectingVelFieldMask | 
                              PhysicsWorld::GravityFieldMask | 
                              PhysicsWorld::CfmFieldMask | 
                              PhysicsWorld::ErpFieldMask);
        physicsWorld->setWorldContactSurfaceLayer(0.01);
        physicsWorld->setAutoDisableFlag(1);
        physicsWorld->setAutoDisableTime(0.75);
        physicsWorld->setWorldContactMaxCorrectingVel(1.0);
        //physicsWorld->setGravity(Vec3f(0.0, 0.0, -9.81));
        //physicsWorld->setCfm(0.001);
        //physicsWorld->setErp(0.2);
    endEditCP(physicsWorld, PhysicsWorld::WorldContactSurfaceLayerFieldMask | 
                              PhysicsWorld::AutoDisableFlagFieldMask | 
                              PhysicsWorld::AutoDisableTimeFieldMask | 
                              PhysicsWorld::WorldContactMaxCorrectingVelFieldMask | 
                              PhysicsWorld::GravityFieldMask | 
                              PhysicsWorld::CfmFieldMask | 
                              PhysicsWorld::ErpFieldMask);

    hashSpace = PhysicsHashSpace::create();

    physHandler = PhysicsHandler::create();
    beginEditCP(physHandler, PhysicsHandler::WorldFieldMask | PhysicsHandler::SpacesFieldMask | PhysicsHandler::StepSizeFieldMask | PhysicsHandler::UpdateNodeFieldMask);
        physHandler->setWorld(physicsWorld);
        physHandler->getSpaces().push_back(hashSpace);
        physHandler->setUpdateNode(rootNode);
    endEditCP(physHandler, PhysicsHandler::WorldFieldMask | PhysicsHandler::SpacesFieldMask | PhysicsHandler::StepSizeFieldMask | PhysicsHandler::UpdateNodeFieldMask);
    physHandler->attachUpdateProducer(TutorialWindowEventProducer);
    

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
	//add Attachments to nodes...
    beginEditCP(spaceGroupNode, Node::AttachmentsFieldMask | Node::ChildrenFieldMask);
	    spaceGroupNode->addAttachment(hashSpace);
    endEditCP(spaceGroupNode, Node::AttachmentsFieldMask | Node::ChildrenFieldMask);

	beginEditCP(TutorialLightNode, Node::ChildrenFieldMask);
	    TutorialLightNode->addChild(spaceGroupNode);
	endEditCP(TutorialLightNode, Node::ChildrenFieldMask);

    //Create Character
    ShipBody = buildShip(Vec3f(3.0,3.0,10.0), Pnt3f((Real32)(rand()%100)-50.0,(Real32)(rand()%100)-50.0,25.0));
    ShipMotor = buildMotor(ShipBody);

    for(UInt32 i(0) ; i<5 ; ++i)
    {
        buildBox(Vec3f(10.0,10.0,10.0), Pnt3f((Real32)(rand()%100)-50.0,(Real32)(rand()%100)-50.0,25.0));
    }

    // tell the manager what to manage
    mgr->setRoot  (rootNode);

    // show the whole rootNode
    mgr->showAll();
    
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "04ZeroGravityShip");

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
        box_mat->setDiffuse(Color3f(0.0,1.0 ,1.0));
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
    beginEditCP(boxBody, PhysicsBody::PositionFieldMask | PhysicsBody::LinearDampingFieldMask | PhysicsBody::AngularDampingFieldMask);
        boxBody->setPosition(Vec3f(Position));
        boxBody->setLinearDamping(0.001);
        boxBody->setAngularDamping(0.001);
    endEditCP(boxBody, PhysicsBody::PositionFieldMask | PhysicsBody::LinearDampingFieldMask | PhysicsBody::AngularDampingFieldMask);
    boxBody->setBoxMass(1.0,Dimensions.x(), Dimensions.y(), Dimensions.z());

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
//! build a character
//////////////////////////////////////////////////////////////////////////
PhysicsBodyPtr buildShip(Vec3f Dimensions, Pnt3f Position)
{
    Real32 Radius(osgMax(Dimensions.x(), Dimensions.y())/2.0f);
    Real32 Length(Dimensions.z() - 2.0f*Radius);

    Matrix m;
    //create OpenSG mesh
    GeometryPtr box;
    NodePtr boxNode = makeBox(Dimensions.x(), Dimensions.y(), Dimensions.z(), 1, 1, 1);
    box = GeometryPtr::dcast(boxNode->getCore());
    SimpleMaterialPtr box_mat = SimpleMaterial::create();
    beginEditCP(box_mat);
        box_mat->setAmbient(Color3f(0.0,0.0,0.0));
        box_mat->setDiffuse(Color3f(1.0,1.0 ,0.0));
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

    beginEditCP(box->getPositions(), GeoPositions3f::GeoPropDataFieldMask);
        for(UInt32 i(0) ; i<box->getPositions()->size() ; ++i)
        {
            box->getPositions()->setValue(box->getPositions()->getValue(i) + Vec3f(0.0,0.0,Dimensions.z()/2.0f),i);
        }
    endEditCP(box->getPositions(), GeoPositions3f::GeoPropDataFieldMask);


    //create ODE data

    PhysicsBodyPtr CapsuleBody = PhysicsBody::create(physicsWorld);
    beginEditCP(CapsuleBody, PhysicsBody::PositionFieldMask | PhysicsBody::LinearDampingFieldMask | PhysicsBody::MaxAngularSpeedFieldMask);
        CapsuleBody->setPosition(Vec3f(Position));
        CapsuleBody->setLinearDamping(0.01);
        CapsuleBody->setMaxAngularSpeed(0.0);
    endEditCP(CapsuleBody, PhysicsBody::PositionFieldMask | PhysicsBody::LinearDampingFieldMask | PhysicsBody::MaxAngularSpeedFieldMask);
    CapsuleBody->setCapsuleMass(1.0,3,Radius, Length);

    PhysicsCapsuleGeomPtr CapsuleGeom = PhysicsCapsuleGeom::create();
    beginEditCP(CapsuleGeom, PhysicsCapsuleGeom::BodyFieldMask | PhysicsCapsuleGeom::SpaceFieldMask | PhysicsCapsuleGeom::RadiusFieldMask | PhysicsCapsuleGeom::LengthFieldMask);
        CapsuleGeom->setBody(CapsuleBody);
        CapsuleGeom->setSpace(hashSpace);
        CapsuleGeom->setRadius(Radius);
        CapsuleGeom->setLength(Length);
    endEditCP(CapsuleGeom, PhysicsCapsuleGeom::BodyFieldMask | PhysicsCapsuleGeom::SpaceFieldMask | PhysicsCapsuleGeom::RadiusFieldMask | PhysicsCapsuleGeom::LengthFieldMask);

    //add attachments
    beginEditCP(boxNode, Node::AttachmentsFieldMask);
        boxNode->addAttachment(CapsuleGeom);
    endEditCP(boxNode, Node::AttachmentsFieldMask);
    beginEditCP(boxTransNode, Node::AttachmentsFieldMask | Node::ChildrenFieldMask);
        boxTransNode->addAttachment(CapsuleBody);
        boxTransNode->addChild(boxNode);
    endEditCP(boxTransNode, Node::AttachmentsFieldMask | Node::ChildrenFieldMask);

    //add to SceneGraph
    beginEditCP(spaceGroupNode, Node::ChildrenFieldMask);
        spaceGroupNode->addChild(boxTransNode);
    endEditCP(spaceGroupNode, Node::ChildrenFieldMask);

    return CapsuleBody;
}
