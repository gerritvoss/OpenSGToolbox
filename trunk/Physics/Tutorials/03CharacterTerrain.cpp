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
#include <OpenSG/OSGShadowViewport.h>

#include <OpenSG/OSGFieldContainerFactory.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include <OpenSG/OSGGeoFunctions.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGPointLight.h>
#include <OpenSG/OSGGradientBackground.h>

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
PhysicsBodyPtr buildBox(Vec3f Dimensions, Pnt3f Position);
PhysicsBodyPtr buildCharacter(Vec3f Dimensions, Pnt3f Position);
GeometryPtr buildTerrain(Vec2f Dimensions, UInt32 XSubdivisions, UInt32 YSubdivisions);
PhysicsLMotorJointPtr buildMover(PhysicsBodyPtr character);

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

PhysicsHandlerPtr physHandler;
PhysicsWorldPtr physicsWorld;
PhysicsHashSpacePtr physicsSpace;
PhysicsBodyPtr CharacterPhysicsBody;
PhysicsLMotorJointPtr CharacterMover;

Vec3f ForceOnCharacter;
bool _IsUpKeyDown(false);
bool _IsDownKeyDown(false);
bool _IsLeftKeyDown(false);
bool _IsRightKeyDown(false);
bool _IsAKeyDown(false);
bool _IsDKeyDown(false);
bool _ShouldJump(false);

//just for hierarchy
NodePtr spaceGroupNode;

NodePtr rootNode;
ShadowViewportPtr svp;

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

   virtual void keyReleased(const KeyEvent& e)
   {
	   switch(e.getKey())
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
        ForceOnCharacter.setValues(0.0,0.0,0.0);
        Real32 PushForce(5000.0);
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
        beginEditCP(CharacterMover, PhysicsLMotorJoint::FMaxFieldMask | 
                               PhysicsLMotorJoint::VelFieldMask |
                               PhysicsLMotorJoint::FMax2FieldMask | 
                               PhysicsLMotorJoint::Vel2FieldMask |
                               PhysicsLMotorJoint::FMax3FieldMask | 
                               PhysicsLMotorJoint::Vel3FieldMask);
            if(ForceOnCharacter.x() !=0.0)
            {
                CharacterMover->setFMax(osgabs(ForceOnCharacter.x()));
                CharacterMover->setVel(osgSgn(ForceOnCharacter.x())*Speed);
            }
            else
            {
                CharacterMover->setFMax(0.0);
                CharacterMover->setVel(0.0);
            }
            if(ForceOnCharacter.y() !=0.0)
            {
                CharacterMover->setFMax2(osgabs(ForceOnCharacter.y()));
                CharacterMover->setVel2(osgSgn(ForceOnCharacter.y())*Speed);
            }
            else
            {
                CharacterMover->setFMax2(0.0);
                CharacterMover->setVel2(0.0);
            }
            if(ForceOnCharacter.z() !=0.0)
            {
                CharacterMover->setFMax3(osgabs(ForceOnCharacter.z()));
                CharacterMover->setVel3(osgSgn(ForceOnCharacter.z())*Speed);
            }
            else
            {
                CharacterMover->setFMax3(0.0);
                CharacterMover->setVel3(0.0);
            }
        endEditCP(CharacterMover, PhysicsLMotorJoint::FMaxFieldMask | 
                               PhysicsLMotorJoint::VelFieldMask |
                               PhysicsLMotorJoint::FMax2FieldMask | 
                               PhysicsLMotorJoint::Vel2FieldMask |
                               PhysicsLMotorJoint::FMax3FieldMask | 
                               PhysicsLMotorJoint::Vel3FieldMask);

        Real32 RotationRate(1.57);
        if(_IsAKeyDown)
        {
            beginEditCP(CharacterPhysicsBody, PhysicsBody::QuaternionFieldMask);
                Quaternion newRotation(CharacterPhysicsBody->getQuaternion());
                newRotation.mult(Quaternion(Vec3f(0.0,0.0,1.0),RotationRate*e.getElapsedTime()));
                CharacterPhysicsBody->setQuaternion( newRotation );
            endEditCP(CharacterPhysicsBody, PhysicsBody::QuaternionFieldMask);
        }
        if(_IsDKeyDown)
        {
            beginEditCP(CharacterPhysicsBody, PhysicsBody::QuaternionFieldMask);
                Quaternion newRotation(CharacterPhysicsBody->getQuaternion());
                newRotation.mult(Quaternion(Vec3f(0.0,0.0,1.0),-RotationRate*e.getElapsedTime()));
                CharacterPhysicsBody->setQuaternion( newRotation );
            endEditCP(CharacterPhysicsBody, PhysicsBody::QuaternionFieldMask);
        }
    }
};

PhysicsLMotorJointPtr buildMover(PhysicsBodyPtr character)
{
    //Create LMotor Joint
    PhysicsLMotorJointPtr TutorialLMotorJoint = PhysicsLMotorJoint::create(character->getWorld());
    beginEditCP(TutorialLMotorJoint, PhysicsLMotorJoint::FirstBodyFieldMask | 
                                    PhysicsLMotorJoint::SecondBodyFieldMask | 
                                    PhysicsLMotorJoint::NumAxesFieldMask | 
                                    PhysicsLMotorJoint::Axis1FieldMask | 
                                    PhysicsLMotorJoint::Axis1ReferenceFrameFieldMask |
                                    PhysicsLMotorJoint::Axis2FieldMask | 
                                    PhysicsLMotorJoint::Axis2ReferenceFrameFieldMask |
                                    PhysicsLMotorJoint::Axis3FieldMask | 
                                    PhysicsLMotorJoint::Axis3ReferenceFrameFieldMask);
        TutorialLMotorJoint->setFirstBody(character);
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
                                        "OpenSG 03CharacterTerrain Window");

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
    Matrix LightTransformMat;
    LightTransformMat.setTranslate(Vec3f(0.0,0.0,30.0));

    TransformPtr LightTransform = Transform::create();
    beginEditCP(LightTransform, Transform::MatrixFieldMask);
        LightTransform->setMatrix(LightTransformMat);
    endEditCP(LightTransform, Transform::MatrixFieldMask);

    NodePtr TutorialLightBeacon = Node::create();
    beginEditCP(TutorialLightBeacon, Node::CoreFieldMask);
        TutorialLightBeacon->setCore(LightTransform);
    endEditCP(TutorialLightBeacon, Node::CoreFieldMask);

    //Light Node
    PointLightPtr TutorialLight = PointLight::create();
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
                              PhysicsWorld::GravityFieldMask);
        physicsWorld->setWorldContactSurfaceLayer(0.005);
        physicsWorld->setAutoDisableFlag(1);
        physicsWorld->setAutoDisableTime(0.75);
        physicsWorld->setWorldContactMaxCorrectingVel(100.0);
        physicsWorld->setGravity(Vec3f(0.0, 0.0, -9.81));
    endEditCP(physicsWorld, PhysicsWorld::WorldContactSurfaceLayerFieldMask | 
                              PhysicsWorld::AutoDisableFlagFieldMask | 
                              PhysicsWorld::AutoDisableTimeFieldMask | 
                              PhysicsWorld::WorldContactMaxCorrectingVelFieldMask | 
                              PhysicsWorld::GravityFieldMask);

    physicsSpace = PhysicsHashSpace::create();

    //Setup the default collision parameters
    CollisionContactParametersPtr DefaultCollisionParams = CollisionContactParameters::createEmpty();
    beginEditCP(DefaultCollisionParams);
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
    endEditCP(DefaultCollisionParams);

    beginEditCP(physicsSpace, PhysicsSpace::DefaultCollisionParametersFieldMask);
        physicsSpace->setDefaultCollisionParameters(DefaultCollisionParams);
    endEditCP(physicsSpace, PhysicsSpace::DefaultCollisionParametersFieldMask);

    physHandler = PhysicsHandler::create();
    beginEditCP(physHandler, PhysicsHandler::WorldFieldMask | PhysicsHandler::SpacesFieldMask | PhysicsHandler::StepSizeFieldMask | PhysicsHandler::UpdateNodeFieldMask);
        physHandler->setWorld(physicsWorld);
        physHandler->getSpaces().push_back(physicsSpace);
        physHandler->setUpdateNode(rootNode);
    endEditCP(physHandler, PhysicsHandler::WorldFieldMask | PhysicsHandler::SpacesFieldMask | PhysicsHandler::StepSizeFieldMask | PhysicsHandler::UpdateNodeFieldMask);
    physHandler->attachUpdateProducer(TutorialWindowEventProducer);
    

    beginEditCP(rootNode, Node::AttachmentsFieldMask);
        rootNode->addAttachment(physHandler);    
        rootNode->addAttachment(physicsWorld);
        rootNode->addAttachment(physicsSpace);
    endEditCP(rootNode, Node::AttachmentsFieldMask);


	/************************************************************************/
	/* create spaces, geoms and bodys                                                                     */
	/************************************************************************/
    //create a group for our space
    GroupPtr spaceGroup;
	spaceGroupNode = makeCoredNode<Group>(&spaceGroup);

    //create the ground terrain
    GeometryPtr TerrainGeo = buildTerrain(Vec2f(400.0,400.0),25,25);

    //and its Material
	SimpleMaterialPtr TerrainMat = SimpleMaterial::create();
	beginEditCP(TerrainMat);
		TerrainMat->setAmbient(Color3f(0.3,0.5,0.3));
		TerrainMat->setDiffuse(Color3f(0.5,0.9,0.5));
	endEditCP(TerrainMat);
    beginEditCP(TerrainGeo, Geometry::MaterialFieldMask);
	    TerrainGeo->setMaterial(TerrainMat);
    endEditCP(TerrainGeo, Geometry::MaterialFieldMask);
    
    NodePtr TerrainNode = Node::create();
    beginEditCP(TerrainNode, Node::CoreFieldMask);
	    TerrainNode->setCore(TerrainGeo);
    endEditCP(TerrainNode, Node::CoreFieldMask);


    //create ODE data
    PhysicsGeomPtr TerrainODEGeom = PhysicsTriMeshGeom::create();

    beginEditCP(TerrainODEGeom,PhysicsTriMeshGeom::SpaceFieldMask | 
                    PhysicsTriMeshGeom::GeometryNodeFieldMask);
        //add geom to space for collision
        TerrainODEGeom->setSpace(physicsSpace);
        //set the geometryNode to fill the ode-triMesh
        PhysicsTriMeshGeom::Ptr::dcast(TerrainODEGeom)->setGeometryNode(TerrainNode);
    endEditCP(TerrainODEGeom,PhysicsTriMeshGeom::SpaceFieldMask | 
                    PhysicsTriMeshGeom::GeometryNodeFieldMask);
    
    //add attachments
	//add Attachments to nodes...
    beginEditCP(spaceGroupNode, Node::AttachmentsFieldMask | Node::ChildrenFieldMask);
	    spaceGroupNode->addAttachment(physicsSpace);
        spaceGroupNode->addChild(TerrainNode);
    endEditCP(spaceGroupNode, Node::AttachmentsFieldMask | Node::ChildrenFieldMask);

    beginEditCP(TerrainNode, Node::AttachmentsFieldMask);
        TerrainNode->addAttachment(TerrainODEGeom);
    endEditCP(TerrainNode, Node::AttachmentsFieldMask);
    
	beginEditCP(TutorialLightNode, Node::ChildrenFieldMask);
	    TutorialLightNode->addChild(spaceGroupNode);
	endEditCP(TutorialLightNode, Node::ChildrenFieldMask);

    //Create Character
    CharacterPhysicsBody = buildCharacter(Vec3f(3.0,3.0,10.0), Pnt3f((Real32)(rand()%100)-50.0,(Real32)(rand()%100)-50.0,25.0));
    CharacterMover = buildMover(CharacterPhysicsBody);

    //Create the Shadowing
	svp = ShadowViewport::create();
	GradientBackgroundPtr gbg = GradientBackground::create();

	beginEditCP(gbg);
		gbg->addLine(Color3f(0.7, 0.7, 0.8), 0);
		gbg->addLine(Color3f(0.0, 0.1, 0.3), 1);
	endEditCP(gbg);

	// Shadow viewport
	beginEditCP(svp);
		svp->setBackground(gbg);
		svp->setRoot(rootNode);
		svp->setSize(0,0,1,1);
        svp->setOffFactor(4.0);
        svp->setOffBias(8.0);
		//svp->setShadowColor(Color4f(0.2, 0.2, 0.2, 0.5));
		svp->setMapSize(1024);
        svp->setShadowSmoothness(0.5);
		// you can add the light sources here, as default all light source in
		// the scenegraph are used.
		svp->getLightNodes().push_back(TutorialLightNode);
	endEditCP(svp);


    // tell the manager what to manage
    mgr->setRoot  (rootNode);
    dynamic_cast<RenderAction *>(mgr->getAction())->setLocalLights(true);

    beginEditCP(mgr->getWindow(),Window::PortFieldMask);
        mgr->getWindow()->addPort(svp);
    endEditCP(mgr->getWindow(),Window::PortFieldMask);
	beginEditCP(svp);//Viewport
		svp->setCamera(mgr->getCamera());
	endEditCP(svp);
    svp->setShadowOn(true);

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


GeometryPtr buildTerrain(Vec2f Dimensions, UInt32 XSubdivisions, UInt32 YSubdivisions)
{
	GeoPTypesPtr type = GeoPTypesUI8::create();        
    beginEditCP(type, GeoPTypesUI8::GeoPropDataFieldMask);
    {
        type->addValue(GL_TRIANGLES);
    }
    endEditCP  (type, GeoPTypesUI8::GeoPropDataFieldMask);

	GeoPositions3fPtr pnts = GeoPositions3f::create();
	GeoNormals3fPtr norms = GeoNormals3f::create();
    beginEditCP(pnts, GeoPositions3f::GeoPropDataFieldMask);
    beginEditCP(norms, GeoNormals3f::GeoPropDataFieldMask);
    {
        Real32 ZScale(8.0);
        for(UInt32 i(0) ; i<XSubdivisions ; ++i)
        {
            for(UInt32 j(0) ; j<YSubdivisions ; ++j)
            {
                Real32 Theta(5*3.14159*(static_cast<Real32>(i)/static_cast<Real32>(XSubdivisions))),
                       ThetaNext(5*3.14159*(static_cast<Real32>(i+1)/static_cast<Real32>(XSubdivisions)));
		        // the points of the Tris
                pnts->addValue(Pnt3f(-Dimensions.x()/2.0+i*(Dimensions.x()/static_cast<Real32>(XSubdivisions)),  Dimensions.y()/2.0-j*(Dimensions.y()/static_cast<Real32>(YSubdivisions)),  ZScale*osgcos(Theta)));
                norms->addValue(Vec3f( 0.0,0.0,1.0));
                pnts->addValue(Pnt3f(-Dimensions.x()/2.0+i*(Dimensions.x()/static_cast<Real32>(XSubdivisions)),  Dimensions.y()/2.0-(j+1)*(Dimensions.y()/static_cast<Real32>(YSubdivisions)),  ZScale*osgcos(Theta)));
                norms->addValue(Vec3f( 0.0,0.0,1.0));
                pnts->addValue(Pnt3f(-Dimensions.x()/2.0+(i+1)*(Dimensions.x()/static_cast<Real32>(XSubdivisions)),  Dimensions.y()/2.0-j*(Dimensions.y()/static_cast<Real32>(YSubdivisions)),  ZScale*osgcos(ThetaNext)));
                norms->addValue(Vec3f( 0.0,0.0,1.0));

                pnts->addValue(Pnt3f(-Dimensions.x()/2.0+i*(Dimensions.x()/static_cast<Real32>(XSubdivisions)),  Dimensions.y()/2.0-(j+1)*(Dimensions.y()/static_cast<Real32>(YSubdivisions)),  ZScale*osgcos(Theta)));
                norms->addValue(Vec3f( 0.0,0.0,1.0));
                pnts->addValue(Pnt3f(-Dimensions.x()/2.0+(i+1)*(Dimensions.x()/static_cast<Real32>(XSubdivisions)),  Dimensions.y()/2.0-(j+1)*(Dimensions.y()/static_cast<Real32>(YSubdivisions)),  ZScale*osgcos(ThetaNext)));
                norms->addValue(Vec3f( 0.0,0.0,1.0));
                pnts->addValue(Pnt3f(-Dimensions.x()/2.0+(i+1)*(Dimensions.x()/static_cast<Real32>(XSubdivisions)),  Dimensions.y()/2.0-j*(Dimensions.y()/static_cast<Real32>(YSubdivisions)),  ZScale*osgcos(ThetaNext)));
                norms->addValue(Vec3f( 0.0,0.0,1.0));
            }
        }

    }
    endEditCP(norms, GeoNormals3f::GeoPropDataFieldMask);
    endEditCP  (pnts, GeoPositions3f::GeoPropDataFieldMask);
    
    GeoIndicesUI32Ptr indicies = GeoIndicesUI32::create();
    beginEditCP(indicies, GeoIndicesUI16::GeoPropDataFieldMask);
    for(UInt32 i(0) ; i<pnts->size() ; ++i)
    {
        indicies->addValue(i);
    }
    endEditCP(indicies, GeoIndicesUI16::GeoPropDataFieldMask);
    
	GeoPLengthsPtr lens = GeoPLengthsUI32::create();    
    beginEditCP(lens, GeoPLengthsUI32::GeoPropDataFieldMask);
    {
        lens->addValue(pnts->size());
    }
    endEditCP  (lens, GeoPLengthsUI32::GeoPropDataFieldMask);

    GeometryPtr Terrain = Geometry::create();
    beginEditCP(Terrain, Geometry::TypesFieldMask     |
                     Geometry::LengthsFieldMask   |
                     Geometry::PositionsFieldMask |
                     Geometry::NormalsFieldMask |
                     Geometry::IndicesFieldMask  );
    {
        Terrain->setTypes    (type);
        Terrain->setLengths  (lens);
        Terrain->setPositions(pnts);
        Terrain->setNormals(norms);
        Terrain->setIndices(indicies);
    }
    endEditCP  (Terrain, Geometry::TypesFieldMask     |
                     Geometry::LengthsFieldMask   |
                     Geometry::PositionsFieldMask |
                     Geometry::NormalsFieldMask |
                     Geometry::IndicesFieldMask  );

    calcVertexNormals(Terrain);
    
    return Terrain;
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
    beginEditCP(boxBody, PhysicsBody::PositionFieldMask);
        boxBody->setPosition(Vec3f(Position));
        //boxBody->setLinearDamping(0.001);
        //boxBody->setAngularDamping(0.001);
    endEditCP(boxBody, PhysicsBody::PositionFieldMask);
    boxBody->setBoxMass(1.0,Dimensions.x(), Dimensions.y(), Dimensions.z());

    PhysicsBoxGeomPtr boxGeom = PhysicsBoxGeom::create();
    beginEditCP(boxGeom, PhysicsBoxGeom::BodyFieldMask | PhysicsBoxGeom::SpaceFieldMask | PhysicsBoxGeom::LengthsFieldMask);
        boxGeom->setBody(boxBody);
        boxGeom->setSpace(physicsSpace);
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
PhysicsBodyPtr buildCharacter(Vec3f Dimensions, Pnt3f Position)
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

    //create ODE data
    PhysicsBodyPtr boxBody = PhysicsBody::create(physicsWorld);
    beginEditCP(boxBody, PhysicsBody::PositionFieldMask | PhysicsBody::MaxAngularSpeedFieldMask);
        boxBody->setPosition(Vec3f(Position));
        //boxBody->setLinearDamping(0.001);
        //boxBody->setAngularDamping(0.001);
        boxBody->setMaxAngularSpeed(0.0);
        endEditCP(boxBody, PhysicsBody::PositionFieldMask | PhysicsBody::MaxAngularSpeedFieldMask);
    boxBody->setCCylinderMass(1.0,3,Radius, Length);

    PhysicsCCylinderGeomPtr CapsuleGeom = PhysicsCCylinderGeom::create();
    beginEditCP(CapsuleGeom, PhysicsCCylinderGeom::BodyFieldMask | PhysicsCCylinderGeom::SpaceFieldMask | PhysicsCCylinderGeom::ParamsFieldMask);
        CapsuleGeom->setBody(boxBody);
        CapsuleGeom->setSpace(physicsSpace);
        CapsuleGeom->setParams(Vec2f(Radius,Length));
    endEditCP(CapsuleGeom, PhysicsCCylinderGeom::BodyFieldMask | PhysicsCCylinderGeom::SpaceFieldMask | PhysicsCCylinderGeom::ParamsFieldMask);

    //add attachments
    beginEditCP(boxNode, Node::AttachmentsFieldMask);
        boxNode->addAttachment(CapsuleGeom);
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
