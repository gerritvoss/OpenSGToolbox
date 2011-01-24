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
PhysicsBodyUnrecPtr  buildBox(const Pnt3f& Position,
                              const Vec3f& Dimensions,
                              const Color3f& Color,
                              Node* const spaceGroupNode,
                              PhysicsWorld* const physicsWorld,
                              PhysicsHashSpace* const physicsSpace);
PhysicsBodyRefPtr buildCharacter(Vec3f Dimensions,
                                 Pnt3f Position,
                                 Node* const spaceGroupNode,
                                 PhysicsWorld* const physicsWorld,
                                 PhysicsHashSpace* const physicsSpace
                                );
GeometryRefPtr buildTerrain(Vec2f Dimensions, UInt32 XSubdivisions, UInt32 YSubdivisions);
PhysicsLMotorJointRefPtr buildMover(PhysicsBodyRefPtr character);

Vec3f ForceOnCharacter;
bool _IsUpKeyDown(false);
bool _IsDownKeyDown(false);
bool _IsLeftKeyDown(false);
bool _IsRightKeyDown(false);
bool _IsAKeyDown(false);
bool _IsDKeyDown(false);
bool _ShouldJump(false);

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
        case KeyEventDetails::KEY_B:
            buildBox(Pnt3f((Real32)(rand()%100)-50.0,(Real32)(rand()%100)-50.0,55.0),
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
        case KeyEventDetails::KEY_A:
            _IsAKeyDown = true;
            break;
        case KeyEventDetails::KEY_D:
            _IsDKeyDown = true;
            break;
        case KeyEventDetails::KEY_SPACE:
            _ShouldJump = true;
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
        case KeyEventDetails::KEY_A:
            _IsAKeyDown = false;
            break;
        case KeyEventDetails::KEY_D:
            _IsDKeyDown = false;
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

void handleUpdate(UpdateEventDetails* const details,
                  PhysicsBody* const CharacterPhysicsBody,
                  PhysicsLMotorJoint* const CharacterMover)
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
        newRotation.mult(Quaternion(Vec3f(0.0,0.0,1.0),RotationRate*details->getElapsedTime()));
        CharacterPhysicsBody->setQuaternion( newRotation );
    }
    if(_IsDKeyDown)
    {
        Quaternion newRotation(CharacterPhysicsBody->getQuaternion());
        newRotation.mult(Quaternion(Vec3f(0.0,0.0,1.0),-RotationRate*details->getElapsedTime()));
        CharacterPhysicsBody->setQuaternion( newRotation );
    }
}

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
        ComponentTransformRefPtr Trans = ComponentTransform::create();
        rootNode->setCore(Trans);
        rootNode->addChild(scene);

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
        PhysicsWorldRecPtr physicsWorld = PhysicsWorld::create();
        physicsWorld->setWorldContactSurfaceLayer(0.005);
        physicsWorld->setAutoDisableFlag(1);
        physicsWorld->setAutoDisableTime(0.75);
        physicsWorld->setWorldContactMaxCorrectingVel(100.0);
        physicsWorld->setGravity(Vec3f(0.0, 0.0, -9.81));

        PhysicsHashSpaceRecPtr physicsSpace = PhysicsHashSpace::create();

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
        GroupRefPtr spaceGroup;
        NodeRecPtr spaceGroupNode = makeCoredNode<Group>(&spaceGroup);

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
        PhysicsBodyRefPtr CharacterPhysicsBody = buildCharacter(Vec3f(5.0,5.0,10.0),
                                                                Pnt3f((Real32)(rand()%100)-50.0,(Real32)(rand()%100)-50.0,25.0),
                                                                spaceGroupNode,
                                                                physicsWorld,
                                                                physicsSpace);

        PhysicsLMotorJointRefPtr CharacterMover = buildMover(CharacterPhysicsBody);

        TutorialWindow->connectKeyPressed(boost::bind(keyPressed, _1,
                                                      spaceGroupNode.get(),
                                                      physicsWorld.get(),
                                                      physicsSpace.get()));

        TutorialWindow->connectUpdate(boost::bind(handleUpdate, _1,
                                                  CharacterPhysicsBody.get(),
                                                  CharacterMover.get()));

        // tell the manager what to manage
        sceneManager.setRoot  (rootNode);

        // show the whole rootNode
        sceneManager.showAll();

        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "03CharacterTerrain");

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
//! build a character
//////////////////////////////////////////////////////////////////////////
PhysicsBodyRefPtr buildCharacter(Vec3f Dimensions,
                                 Pnt3f Position,
                                 Node* const spaceGroupNode,
                                 PhysicsWorld* const physicsWorld,
                                 PhysicsHashSpace* const physicsSpace
                                 )
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
