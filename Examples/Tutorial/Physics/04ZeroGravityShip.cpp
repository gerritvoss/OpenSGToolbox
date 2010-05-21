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
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE


// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);
PhysicsBodyRefPtr buildBox(Vec3f Dimensions, Pnt3f Position);
PhysicsBodyRefPtr buildShip(Vec3f Dimensions, Pnt3f Position);
PhysicsLMotorJointRefPtr buildMotor(PhysicsBodyRefPtr ship);

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

NodeUnrecPtr PhysDrawableNode;
PhysicsHandlerRefPtr physHandler;
PhysicsWorldRefPtr physicsWorld;
PhysicsHashSpaceRefPtr hashSpace;
PhysicsBodyRefPtr ShipBody;
PhysicsLMotorJointRefPtr ShipMotor;
Vec3f ForceOnCharacter;
bool _IsUpKeyDown(false);
bool _IsDownKeyDown(false);
bool _IsLeftKeyDown(false);
bool _IsRightKeyDown(false);

//just for hierarchy
NodeRefPtr spaceGroupNode;

NodeRefPtr rootNode;

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

class TutorialUpdateListener : public UpdateListener
{
  public:
    virtual void update(const UpdateEventUnrecPtr e)
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
};

PhysicsLMotorJointRefPtr buildMotor(PhysicsBodyRefPtr ship)
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
	TutorialUpdateListener TheTutorialUpdateListener;
    TutorialWindow->addUpdateListener(&TheTutorialUpdateListener);


    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

	
    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindow);

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

    //Make The Physics Characteristics Node
    PhysicsCharacteristicsDrawableUnrecPtr PhysDrawable = PhysicsCharacteristicsDrawable::create();
        PhysDrawable->setRoot(rootNode);

	PhysDrawableNode = Node::create();
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
    physicsWorld = PhysicsWorld::create();
        physicsWorld->setWorldContactSurfaceLayer(0.01);
        physicsWorld->setAutoDisableFlag(1);
        physicsWorld->setAutoDisableTime(0.75);
        physicsWorld->setWorldContactMaxCorrectingVel(1.0);
        //physicsWorld->setGravity(Vec3f(0.0, 0.0, -9.81));
        //physicsWorld->setCfm(0.001);
        //physicsWorld->setErp(0.2);

    hashSpace = PhysicsHashSpace::create();

    physHandler = PhysicsHandler::create();
        physHandler->setWorld(physicsWorld);
        physHandler->pushToSpaces(hashSpace);
        physHandler->setUpdateNode(rootNode);
    physHandler->attachUpdateProducer(TutorialWindow->editEventProducer());
    

        rootNode->addAttachment(physHandler);    
        rootNode->addAttachment(physicsWorld);
        rootNode->addAttachment(hashSpace);


	/************************************************************************/
	/* create spaces, geoms and bodys                                                                     */
	/************************************************************************/
    //create a group for our space
    GroupRefPtr spaceGroup;
	spaceGroupNode = makeCoredNode<Group>(&spaceGroup);
	//add Attachments to nodes...
	    spaceGroupNode->addAttachment(hashSpace);

	    TutorialLightNode->addChild(spaceGroupNode);

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
    
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
            WinSize,
            "04ZeroGravityShip");

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
PhysicsBodyRefPtr buildBox(Vec3f Dimensions, Pnt3f Position)
{
    Matrix m;
    //create OpenSG mesh
    GeometryRefPtr box;
    NodeRefPtr boxNode = makeBox(Dimensions.x(), Dimensions.y(), Dimensions.z(), 1, 1, 1);
    box = dynamic_cast<Geometry*>(boxNode->getCore());
    SimpleMaterialRefPtr box_mat = SimpleMaterial::create();
        box_mat->setAmbient(Color3f(0.0,0.0,0.0));
        box_mat->setDiffuse(Color3f(0.0,1.0 ,1.0));
        box->setMaterial(box_mat);
    TransformRefPtr boxTrans;
    NodeRefPtr boxTransNode = makeCoredNode<Transform>(&boxTrans);
    m.setIdentity();
    m.setTranslate(Position);
        boxTrans->setMatrix(m);

    //create ODE data
    PhysicsBodyRefPtr boxBody = PhysicsBody::create(physicsWorld);
        boxBody->setPosition(Vec3f(Position));
        boxBody->setLinearDamping(0.001);
        boxBody->setAngularDamping(0.001);
    boxBody->setBoxMass(1.0,Dimensions.x(), Dimensions.y(), Dimensions.z());

    PhysicsBoxGeomRefPtr boxGeom = PhysicsBoxGeom::create();
        boxGeom->setBody(boxBody);
        boxGeom->setSpace(hashSpace);
        boxGeom->setLengths(Dimensions);

    //add attachments
        boxNode->addAttachment(boxGeom);
        boxTransNode->addAttachment(boxBody);
        boxTransNode->addChild(boxNode);

    //add to SceneGraph
        spaceGroupNode->addChild(boxTransNode);

    commitChanges();

    return boxBody;
}


//////////////////////////////////////////////////////////////////////////
//! build a ship
//////////////////////////////////////////////////////////////////////////
PhysicsBodyRefPtr buildShip(Vec3f Dimensions, Pnt3f Position)
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
        CapsuleGeom->setSpace(hashSpace);
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
