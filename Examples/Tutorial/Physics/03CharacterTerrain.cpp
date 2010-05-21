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
#include "OSGGeoFunctions.h"
#include "OSGSceneFileHandler.h"
#include "OSGPointLight.h"
#include "OSGGradientBackground.h"
#include "OSGGeoProperties.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGTypedGeoVectorProperty.h"

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
PhysicsBodyRefPtr buildBox(Vec3f Dimensions, Pnt3f Position);
PhysicsBodyRefPtr buildCharacter(Vec3f Dimensions, Pnt3f Position);
GeometryRefPtr buildTerrain(Vec2f Dimensions, UInt32 XSubdivisions, UInt32 YSubdivisions);
PhysicsLMotorJointRefPtr buildMover(PhysicsBodyRefPtr character);

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

PhysicsHandlerRefPtr physHandler;
PhysicsWorldRefPtr physicsWorld;
PhysicsHashSpaceRefPtr physicsSpace;
PhysicsBodyRefPtr CharacterPhysicsBody;
PhysicsLMotorJointRefPtr CharacterMover;

Vec3f ForceOnCharacter;
bool _IsUpKeyDown(false);
bool _IsDownKeyDown(false);
bool _IsLeftKeyDown(false);
bool _IsRightKeyDown(false);
bool _IsAKeyDown(false);
bool _IsDKeyDown(false);
bool _ShouldJump(false);

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
           buildBox(Vec3f(10.0,10.0,10.0), Pnt3f((Real32)(rand()%100)-50.0,(Real32)(rand()%100)-50.0,55.0));
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
	   case KeyEvent::KEY_A:
           _IsAKeyDown = true;
		   break;
	   case KeyEvent::KEY_D:
           _IsDKeyDown = true;
           break;
	   case KeyEvent::KEY_SPACE:
           _ShouldJump = true;
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
	   case KeyEvent::KEY_A:
           _IsAKeyDown = false;
		   break;
	   case KeyEvent::KEY_D:
           _IsDKeyDown = false;
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
        Real32 PushForce(55000.0);
        Real32 Speed(10.0);
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
        if(_ShouldJump)
        {
            ForceOnCharacter += Vec3f(0.0, 0.0, 50000.0);
            _ShouldJump = false;
        }
        if(ForceOnCharacter != Vec3f(0.0,0.0,0.0))
        {
            CharacterPhysicsBody->setEnable(true);
        }
            if(ForceOnCharacter.x() !=0.0)
            {
                CharacterMover->setFMax(osgAbs(ForceOnCharacter.x()));
                CharacterMover->setVel(osgSgn(ForceOnCharacter.x())*Speed);
            }
            else
            {
                CharacterMover->setFMax(0.0);
                CharacterMover->setVel(0.0);
            }
            if(ForceOnCharacter.y() !=0.0)
            {
                CharacterMover->setFMax2(osgAbs(ForceOnCharacter.y()));
                CharacterMover->setVel2(osgSgn(ForceOnCharacter.y())*Speed);
            }
            else
            {
                CharacterMover->setFMax2(0.0);
                CharacterMover->setVel2(0.0);
            }
            if(ForceOnCharacter.z() !=0.0)
            {
                CharacterMover->setFMax3(osgAbs(ForceOnCharacter.z()));
                CharacterMover->setVel3(osgSgn(ForceOnCharacter.z())*Speed);
            }
            else
            {
                CharacterMover->setFMax3(0.0);
                CharacterMover->setVel3(0.0);
            }

        Real32 RotationRate(1.57);
        if(_IsAKeyDown)
        {
                Quaternion newRotation(CharacterPhysicsBody->getQuaternion());
                newRotation.mult(Quaternion(Vec3f(0.0,0.0,1.0),RotationRate*e->getElapsedTime()));
                CharacterPhysicsBody->setQuaternion( newRotation );
        }
        if(_IsDKeyDown)
        {
                Quaternion newRotation(CharacterPhysicsBody->getQuaternion());
                newRotation.mult(Quaternion(Vec3f(0.0,0.0,1.0),-RotationRate*e->getElapsedTime()));
                CharacterPhysicsBody->setQuaternion( newRotation );
        }
    }
};

PhysicsLMotorJointRefPtr buildMover(PhysicsBodyRefPtr character)
{
    //Create LMotor Joint
    PhysicsLMotorJointRefPtr TutorialLMotorJoint = PhysicsLMotorJoint::create(character->getWorld());
        TutorialLMotorJoint->setFirstBody(character);
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

    //Light Beacon
    Matrix LightTransformMat;
    LightTransformMat.setTranslate(Vec3f(50.0,0.0,100.0));

    TransformRefPtr LightTransform = Transform::create();
        LightTransform->setMatrix(LightTransformMat);

    NodeRefPtr TutorialLightBeacon = Node::create();
        TutorialLightBeacon->setCore(LightTransform);

    //Light Node
    PointLightRefPtr TutorialLight = PointLight::create();
    TutorialLight->setBeacon(TutorialLightBeacon);

    NodeRefPtr TutorialLightNode = Node::create();
    TutorialLightNode->setCore(TutorialLight);

    scene->addChild(TutorialLightNode);
    scene->addChild(TutorialLightBeacon);


    //Setup Physics Scene
    physicsWorld = PhysicsWorld::create();
        physicsWorld->setWorldContactSurfaceLayer(0.005);
        physicsWorld->setAutoDisableFlag(1);
        physicsWorld->setAutoDisableTime(0.75);
        physicsWorld->setWorldContactMaxCorrectingVel(100.0);
        physicsWorld->setGravity(Vec3f(0.0, 0.0, -9.81));

    physicsSpace = PhysicsHashSpace::create();

    //Setup the default collision parameters
    CollisionContactParametersRefPtr DefaultCollisionParams = CollisionContactParameters::createEmpty();
        DefaultCollisionParams->setMode(dContactApprox1);
        DefaultCollisionParams->setMu(1.0);
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

    physHandler = PhysicsHandler::create();
        physHandler->setWorld(physicsWorld);
        physHandler->pushToSpaces(physicsSpace);
        physHandler->setUpdateNode(rootNode);
    physHandler->attachUpdateProducer(TutorialWindow->editEventProducer());
    

        rootNode->addAttachment(physHandler);    
        rootNode->addAttachment(physicsWorld);
        rootNode->addAttachment(physicsSpace);


	/************************************************************************/
	/* create spaces, geoms and bodys                                                                     */
	/************************************************************************/
    //create a group for our space
    GroupRefPtr spaceGroup;
	spaceGroupNode = makeCoredNode<Group>(&spaceGroup);

    //create the ground terrain
    GeometryRefPtr TerrainGeo = buildTerrain(Vec2f(400.0,400.0),25,25);

    //and its Material
	SimpleMaterialRefPtr TerrainMat = SimpleMaterial::create();
		TerrainMat->setAmbient(Color3f(0.3,0.5,0.3));
		TerrainMat->setDiffuse(Color3f(0.5,0.9,0.5));
	    TerrainGeo->setMaterial(TerrainMat);
    
    NodeRefPtr TerrainNode = Node::create();
	    TerrainNode->setCore(TerrainGeo);


    //create ODE data
    PhysicsGeomRefPtr TerrainODEGeom = PhysicsTriMeshGeom::create();

        //add geom to space for collision
        TerrainODEGeom->setSpace(physicsSpace);
        //set the geometryNode to fill the ode-triMesh
        dynamic_pointer_cast<PhysicsTriMeshGeom>(TerrainODEGeom)->setGeometryNode(TerrainNode);
    
    //add attachments
	//add Attachments to nodes...
	    spaceGroupNode->addAttachment(physicsSpace);
        spaceGroupNode->addChild(TerrainNode);

        TerrainNode->addAttachment(TerrainODEGeom);
    
	    TutorialLightNode->addChild(spaceGroupNode);

    //Create Character
    CharacterPhysicsBody = buildCharacter(Vec3f(5.0,5.0,10.0), Pnt3f((Real32)(rand()%100)-50.0,(Real32)(rand()%100)-50.0,25.0));
    CharacterMover = buildMover(CharacterPhysicsBody);

    // tell the manager what to manage
    mgr->setRoot  (rootNode);

    // show the whole rootNode
    mgr->showAll();
    
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
            WinSize,
            "03CharacterTerrain");

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


GeometryRefPtr buildTerrain(Vec2f Dimensions, UInt32 XSubdivisions, UInt32 YSubdivisions)
{
    GeoUInt8PropertyRefPtr type = GeoUInt8Property::create();        
    type->addValue(GL_TRIANGLES);

    GeoPnt3fPropertyRefPtr  pnts  = GeoPnt3fProperty ::create();
    GeoVec3fPropertyRefPtr  norms = GeoVec3fProperty ::create();
    Real32 ZScale(8.0);
    for(UInt32 i(0) ; i<XSubdivisions ; ++i)
    {
        for(UInt32 j(0) ; j<YSubdivisions ; ++j)
        {
            Real32 Theta(5*3.14159*(static_cast<Real32>(i)/static_cast<Real32>(XSubdivisions))),
                   ThetaNext(5*3.14159*(static_cast<Real32>(i+1)/static_cast<Real32>(XSubdivisions)));
            // the points of the Tris
            pnts->addValue(Pnt3f(-Dimensions.x()/2.0+i*(Dimensions.x()/static_cast<Real32>(XSubdivisions)),  Dimensions.y()/2.0-j*(Dimensions.y()/static_cast<Real32>(YSubdivisions)),  ZScale*osgCos(Theta)));
            norms->addValue(Vec3f( 0.0,0.0,1.0));
            pnts->addValue(Pnt3f(-Dimensions.x()/2.0+i*(Dimensions.x()/static_cast<Real32>(XSubdivisions)),  Dimensions.y()/2.0-(j+1)*(Dimensions.y()/static_cast<Real32>(YSubdivisions)),  ZScale*osgCos(Theta)));
            norms->addValue(Vec3f( 0.0,0.0,1.0));
            pnts->addValue(Pnt3f(-Dimensions.x()/2.0+(i+1)*(Dimensions.x()/static_cast<Real32>(XSubdivisions)),  Dimensions.y()/2.0-j*(Dimensions.y()/static_cast<Real32>(YSubdivisions)),  ZScale*osgCos(ThetaNext)));
            norms->addValue(Vec3f( 0.0,0.0,1.0));

            pnts->addValue(Pnt3f(-Dimensions.x()/2.0+i*(Dimensions.x()/static_cast<Real32>(XSubdivisions)),  Dimensions.y()/2.0-(j+1)*(Dimensions.y()/static_cast<Real32>(YSubdivisions)),  ZScale*osgCos(Theta)));
            norms->addValue(Vec3f( 0.0,0.0,1.0));
            pnts->addValue(Pnt3f(-Dimensions.x()/2.0+(i+1)*(Dimensions.x()/static_cast<Real32>(XSubdivisions)),  Dimensions.y()/2.0-(j+1)*(Dimensions.y()/static_cast<Real32>(YSubdivisions)),  ZScale*osgCos(ThetaNext)));
            norms->addValue(Vec3f( 0.0,0.0,1.0));
            pnts->addValue(Pnt3f(-Dimensions.x()/2.0+(i+1)*(Dimensions.x()/static_cast<Real32>(XSubdivisions)),  Dimensions.y()/2.0-j*(Dimensions.y()/static_cast<Real32>(YSubdivisions)),  ZScale*osgCos(ThetaNext)));
            norms->addValue(Vec3f( 0.0,0.0,1.0));
        }
    }

    
    GeoUInt32PropertyUnrecPtr lens = GeoUInt32Property::create();    
    lens->addValue(pnts->size());

    GeometryRefPtr Terrain = Geometry::create();
        Terrain->setTypes    (type);
        Terrain->setLengths  (lens);
        Terrain->setPositions(pnts);
        Terrain->setNormals(norms);

    calcVertexNormals(Terrain);
    
    return Terrain;
}

//////////////////////////////////////////////////////////////////////////
//! build a box
//////////////////////////////////////////////////////////////////////////
PhysicsBodyRefPtr buildBox(Vec3f Dimensions, Pnt3f Position)
{
    Matrix m;
    //create OpenSG mesh
    GeometryRefPtr box;
    NodeRefPtr characterNode = makeBox(Dimensions.x(), Dimensions.y(), Dimensions.z(), 1, 1, 1);
    box = dynamic_cast<Geometry*>(characterNode->getCore());
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
        //boxBody->setLinearDamping(0.001);
        //boxBody->setAngularDamping(0.001);
    boxBody->setBoxMass(1.0,Dimensions.x(), Dimensions.y(), Dimensions.z());

    PhysicsBoxGeomRefPtr boxGeom = PhysicsBoxGeom::create();
        boxGeom->setBody(boxBody);
        boxGeom->setSpace(physicsSpace);
        boxGeom->setLengths(Dimensions);

    //add attachments
        characterNode->addAttachment(boxGeom);
        boxTransNode->addAttachment(boxBody);
        boxTransNode->addChild(characterNode);

    //add to SceneGraph
        spaceGroupNode->addChild(boxTransNode);


    commitChanges();

    return boxBody;
}


//////////////////////////////////////////////////////////////////////////
//! build a character
//////////////////////////////////////////////////////////////////////////
PhysicsBodyRefPtr buildCharacter(Vec3f Dimensions, Pnt3f Position)
{
    Real32 Radius(osgMax(Dimensions.x(), Dimensions.y())/2.0f);
    Real32 Length(Dimensions.z() - 2.0f*Radius);

    Matrix m;
    //create OpenSG mesh
    GeometryRefPtr box;
    //NodeRefPtr characterNode = makeBox(Dimensions.x(), Dimensions.y(), Dimensions.z(), 1, 1, 1);
    NodeRefPtr characterNode = SceneFileHandler::the()->read("Data/Jack.osb");
	if(characterNode == NULL)
	{
		characterNode = makeBox(Dimensions.x(), Dimensions.y(), Dimensions.z(), 1, 1, 1);
	}
    box = dynamic_cast<Geometry*>(characterNode->getCore());
    TransformRefPtr boxTrans;
    NodeRefPtr boxTransNode = makeCoredNode<Transform>(&boxTrans);
    m.setIdentity();
    m.setTranslate(Position);
        boxTrans->setMatrix(m);

    //create ODE data
    PhysicsBodyRefPtr boxBody = PhysicsBody::create(physicsWorld);
        boxBody->setPosition(Vec3f(Position));
        //boxBody->setLinearDamping(0.001);
        //boxBody->setAngularDamping(0.001);
        boxBody->setMaxAngularSpeed(0.0);
    boxBody->setCapsuleMass(1.0,3,Radius, Length);

    PhysicsCapsuleGeomRefPtr CapsuleGeom = PhysicsCapsuleGeom::create();
        CapsuleGeom->setBody(boxBody);
        CapsuleGeom->setSpace(physicsSpace);
        CapsuleGeom->setRadius(Radius);
        CapsuleGeom->setLength(Length);

    //add attachments
        characterNode->addAttachment(CapsuleGeom);
        boxTransNode->addAttachment(boxBody);
        boxTransNode->addChild(characterNode);

    //add to SceneGraph
        spaceGroupNode->addChild(boxTransNode);
    commitChanges();

    return boxBody;
}
