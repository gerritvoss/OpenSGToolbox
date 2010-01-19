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
#include "OSGKeyListener.h"
#include "OSGWindowUtils.h"

//Physics
#include "OSGPhysics.h"

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
WindowEventProducerUnrecPtr TutorialWindow;

PhysicsHandlerUnrecPtr physHandler;
PhysicsWorldUnrecPtr physicsWorld;
PhysicsHashSpaceUnrecPtr hashSpace;

//just for hierarchy
NodeUnrecPtr spaceGroupNode;

NodeUnrecPtr rootNode;

// Create a class to allow for the use of the Ctrl+q
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

    //Make Main Scene Node
	NodeUnrecPtr scene = makeCoredNode<Group>();
    setName(scene, "scene");
    rootNode = Node::create();
    setName(rootNode, "rootNode");
    ComponentTransformUnrecPtr Trans;
    Trans = ComponentTransform::create();
        rootNode->setCore(Trans);
 
        // add the torus as a child
        rootNode->addChild(scene);

    //Setup Physics Scene
    physicsWorld = PhysicsWorld::create();
        physicsWorld->setWorldContactSurfaceLayer(0.005);
        physicsWorld->setAutoDisableFlag(1);
        physicsWorld->setAutoDisableTime(0.75);
        physicsWorld->setWorldContactMaxCorrectingVel(100.0);
        physicsWorld->setGravity(Vec3f(0.0, 0.0, -9.81));
        physicsWorld->setCfm(0.001);
        physicsWorld->setErp(0.2);

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
    GroupUnrecPtr spaceGroup;
	spaceGroupNode = makeCoredNode<Group>(&spaceGroup);
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

    // tell the manager what to manage
    mgr->setRoot  (rootNode);

    // show the whole rootNode
    mgr->showAll();
    
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
            WinSize,
            "02Joints");

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


PhysicsBodyUnrecPtr buildBox(Vec3f Dimensions, Pnt3f Position)
{
    Matrix m;
    //create OpenSG mesh
    GeometryUnrecPtr box;
    NodeUnrecPtr boxNode = makeBox(Dimensions.x(), Dimensions.y(), Dimensions.z(), 1, 1, 1);
    box = dynamic_cast<Geometry*>(boxNode->getCore());
    SimpleMaterialUnrecPtr box_mat = SimpleMaterial::create();
        box_mat->setAmbient(Color3f(0.0,0.0,0.0));
        box_mat->setDiffuse(Color3f(0.0,1.0 ,0.0));
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
        boxGeom->setSpace(hashSpace);
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
void buildHingeJointMesh(void)
{
    Vec3f Box1Size(1.0,1.0,0.1),
          Box2Size(1.0,1.0,1.0);
    Pnt3f Box1Position((Real32)(rand()%10)-5.0, (Real32)(rand()%10)-5.0, 10.0);
    Pnt3f Box2Position(Box1Position + (Vec3f(Box1Size.x()+.05,0.0,0.0)));

    PhysicsBodyUnrecPtr Box1Body = buildBox(Box1Size, Box1Position);
    PhysicsBodyUnrecPtr Box2Body = buildBox(Box2Size, Box2Position);

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

void buildMotorJointMesh(void)
{
    Vec3f Box1Size(1.0,1.5,0.1),
          Box2Size(1.0,1.0,1.0);
    Pnt3f Box1Position((Real32)(rand()%10)-5.0, (Real32)(rand()%10)-5.0, 10.0);
    Pnt3f Box2Position(Box1Position + (Vec3f(Box1Size.x()+0.01,0.0,0.0)));

    PhysicsBodyUnrecPtr Box1Body = buildBox(Box1Size, Box1Position);
    PhysicsBodyUnrecPtr Box2Body = buildBox(Box2Size, Box2Position);

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

void buildUniversalJointMesh(void)
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

void buildBallJointMesh(void)
{
    Vec3f Box1Size(1.0,0.1,0.1),
          Box2Size(1.0,1.0,1.0);
    Pnt3f Box1Position((Real32)(rand()%10)-5.0, (Real32)(rand()%10)-5.0, 10.0);
    Pnt3f Box2Position(Box1Position + (Vec3f(Box1Size.x()+0.1,0.0,0.0)));

    PhysicsBodyUnrecPtr Box1Body = buildBox(Box1Size, Box1Position);
    PhysicsBodyUnrecPtr Box2Body = buildBox(Box2Size, Box2Position);

    //Create Ball Joint
    PhysicsBallJointUnrecPtr TutorialBallJoint = PhysicsBallJoint::create(Box1Body->getWorld());
        TutorialBallJoint->setFirstBody(Box1Body);
        TutorialBallJoint->setSecondBody(Box2Body);
        TutorialBallJoint->setAnchor(Vec3f(Box1Position) + (Vec3f(Box1Size.x()/2+0.05,0.0,0.0)));

    commitChanges();
}
