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

#include "OSGSimpleStatisticsForeground.h"

// Input
#include "OSGWindowUtils.h"

//Physics
#include "OSGPhysics.h"
#include "OSGPhysicsCharacteristicsDrawable.h"

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE


// forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);
void buildTriMesh(Node* const TriGeometryBase, Node* const spaceGroupNode, PhysicsWorld* const physicsWorld, PhysicsHashSpace* const physicsSpace);
void buildSphere(Node* const spaceGroupNode, PhysicsWorld* const physicsWorld, PhysicsHashSpace* const physicsSpace);
void buildBox(Node* const spaceGroupNode, PhysicsWorld* const physicsWorld, PhysicsHashSpace* const physicsSpace);

void keyPressed(KeyEventDetails* const details,
                Node* const TriGeometryBase,
                Node* const spaceGroupNode,
                Node* const PhysDrawableNode,
                PhysicsWorld* const physicsWorld,
                PhysicsHashSpace* const physicsSpace)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
    switch(details->getKey())
    {
        case KeyEventDetails::KEY_S:
            {
                buildSphere(spaceGroupNode, physicsWorld, physicsSpace);
            }
            break;
        case KeyEventDetails::KEY_B:
            {
                buildBox(spaceGroupNode, physicsWorld, physicsSpace);
            }
            break;
        case KeyEventDetails::KEY_T:
            {
                buildTriMesh(TriGeometryBase, spaceGroupNode, physicsWorld, physicsSpace);
            }
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

// Initialize GLUT & OpenSG and set up the rootNode
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    {
        // Set up Window
        WindowEventProducerRecPtr TutorialWindow = createNativeWindow();
        TutorialWindow->initWindow();

        SimpleSceneManager sceneManager;
        TutorialWindow->setDisplayCallback(boost::bind(display, &sceneManager));
        TutorialWindow->setReshapeCallback(boost::bind(reshape, _1, &sceneManager));

        //Attach to events
        TutorialWindow->connectMousePressed(boost::bind(mousePressed, _1, &sceneManager));
        TutorialWindow->connectMouseReleased(boost::bind(mouseReleased, _1, &sceneManager));
        TutorialWindow->connectMouseMoved(boost::bind(mouseMoved, _1, &sceneManager));
        TutorialWindow->connectMouseDragged(boost::bind(mouseDragged, _1, &sceneManager));

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

        //Make Base Geometry Node
        NodeRecPtr TriGeometryBase = makeTorus(0.5, 1.0, 24, 24);

        //Make Main Scene Node
        NodeRecPtr scene = makeCoredNode<Group>();
        setName(scene, "scene");
        NodeRecPtr rootNode = Node::create();
        setName(rootNode, "rootNode");
        ComponentTransformRecPtr Trans;
        Trans = ComponentTransform::create();
        rootNode->setCore(Trans);

        // add the torus as a child
        rootNode->addChild(scene);

        //Make The Physics Characteristics Node
        PhysicsCharacteristicsDrawableRecPtr PhysDrawable = PhysicsCharacteristicsDrawable::create();
        PhysDrawable->setRoot(rootNode);

        NodeRecPtr PhysDrawableNode = Node::create();
        PhysDrawableNode->setCore(PhysDrawable);
        PhysDrawableNode->setTravMask(TypeTraits<UInt32>::getMin());

        rootNode->addChild(PhysDrawableNode);


        //Setup Physics Scene
        PhysicsWorldRecPtr physicsWorld = PhysicsWorld::create();
        physicsWorld->setWorldContactSurfaceLayer(0.005);
        physicsWorld->setAutoDisableFlag(1);
        physicsWorld->setAutoDisableTime(0.75);
        physicsWorld->setWorldContactMaxCorrectingVel(100.0);
        physicsWorld->setGravity(Vec3f(0.0, 0.0, -9.81));

        PhysicsHashSpaceRecPtr physicsSpace = PhysicsHashSpace::create();

        PhysicsHandlerRecPtr physHandler = PhysicsHandler::create();
        physHandler->setWorld(physicsWorld);
        physHandler->pushToSpaces(physicsSpace);
        physHandler->setUpdateNode(rootNode);

        physHandler->attachUpdateProducer(TutorialWindow);


        /************************************************************************/
        /* create spaces, geoms and bodys                                       */
        /************************************************************************/
        //create a group for our space
        GroupRecPtr spaceGroup;
        NodeRecPtr spaceGroupNode = makeCoredNode<Group>(&spaceGroup);
        //create the ground plane
        GeometryRecPtr plane;
        NodeRecPtr planeNode = makeBox(30.0, 30.0, 1.0, 1, 1, 1);
        plane = dynamic_cast<Geometry*>(planeNode->getCore());
        //and its Material
        SimpleMaterialRecPtr plane_mat = SimpleMaterial::create();
        plane_mat->setAmbient(Color3f(0.7,0.7,0.7));
        plane_mat->setDiffuse(Color3f(0.9,0.6,1.0));

        plane->setMaterial(plane_mat);



        //create Physical Attachments
        PhysicsBoxGeomRecPtr planeGeom = PhysicsBoxGeom::create();
        planeGeom->setLengths(Vec3f(30.0, 30.0, 1.0));
        //add geoms to space for collision
        planeGeom->setSpace(physicsSpace);


        //add Attachments to nodes...
        spaceGroupNode->addAttachment(physicsSpace);
        spaceGroupNode->addAttachment(physHandler);    
        spaceGroupNode->addAttachment(physicsWorld);
        spaceGroupNode->addChild(planeNode);


        planeNode->addAttachment(planeGeom);


        scene->addChild(spaceGroupNode);


        //Create Statistics Foreground
        SimpleStatisticsForegroundRecPtr PhysicsStatForeground = SimpleStatisticsForeground::create();
        PhysicsStatForeground->setSize(25);
        PhysicsStatForeground->setColor(Color4f(0,1,0,0.7));
        PhysicsStatForeground->addElement(PhysicsHandler::statPhysicsTime, 
                                          "Physics time: %.3f s");
        PhysicsStatForeground->addElement(PhysicsHandler::statCollisionTime, 
                                          "Collision time: %.3f s");
        PhysicsStatForeground->addElement(PhysicsHandler::statSimulationTime, 
                                          "Simulation time: %.3f s");
        PhysicsStatForeground->addElement(PhysicsHandler::statNCollisions, 
                                          "%d collisions");
        PhysicsStatForeground->addElement(PhysicsHandler::statNCollisionTests, 
                                          "%d collision tests");
        PhysicsStatForeground->addElement(PhysicsHandler::statNPhysicsSteps, 
                                          "%d simulation steps per frame");
        PhysicsStatForeground->setVerticalAlign(SimpleStatisticsForeground::Center);


        SimpleStatisticsForegroundRecPtr RenderStatForeground = SimpleStatisticsForeground::create();
        RenderStatForeground->setSize(25);
        RenderStatForeground->setColor(Color4f(0,1,0,0.7));
        RenderStatForeground->addElement(RenderAction::statDrawTime, "Draw FPS: %r.3f");
        RenderStatForeground->addElement(RenderAction::statNGeometries, 
                                         "%d Nodes drawn");





        // tell the manager what to manage
        sceneManager.setRoot  (rootNode);

        sceneManager.getWindow()->getPort(0)->addForeground(PhysicsStatForeground);
        sceneManager.getWindow()->getPort(0)->addForeground(RenderStatForeground);

        physHandler->setStatistics(PhysicsStatForeground->editCollector());
        sceneManager.getRenderAction()->setStatCollector(RenderStatForeground->editCollector());

        
        TutorialWindow->connectKeyPressed(boost::bind(keyPressed, _1,
            TriGeometryBase.get(),
            spaceGroupNode.get(),
            PhysDrawableNode.get(),
            physicsWorld.get(),
            physicsSpace.get()));

        // show the whole rootNode
        sceneManager.showAll();

        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "01SimplePhysics");

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
void buildBox(Node* const spaceGroupNode, PhysicsWorld* const physicsWorld, PhysicsHashSpace* const physicsSpace)
{
    Vec3f Lengths((Real32)(rand()%2)+1.0, (Real32)(rand()%2)+1.0, (Real32)(rand()%2)+1.0);
    Matrix m;
    //create OpenSG mesh
    GeometryRecPtr box;
    NodeRecPtr boxNode = makeBox(Lengths.x(), Lengths.y(), Lengths.z(), 1, 1, 1);
    box = dynamic_cast<Geometry*>(boxNode->getCore());
    SimpleMaterialRecPtr box_mat = SimpleMaterial::create();
    box_mat->setAmbient(Color3f(0.0,0.0,0.0));
    box_mat->setDiffuse(Color3f(0.0,1.0 ,0.0));

    box->setMaterial(box_mat);

    TransformRecPtr boxTrans;
    NodeRecPtr boxTransNode = makeCoredNode<Transform>(&boxTrans);
    m.setIdentity();
    Real32 randX = (Real32)(rand()%10)-5.0;
    Real32 randY = (Real32)(rand()%10)-5.0;
    m.setTranslate(randX, randY, 10.0);
    boxTrans->setMatrix(m);


    //create ODE data
    PhysicsBodyRecPtr boxBody = PhysicsBody::create(physicsWorld);
    boxBody->setPosition(Vec3f(randX, randY, 10.0));

    boxBody->setBoxMass(1.0, Lengths.x(), Lengths.y(), Lengths.z());
    //std::cout << "mass: "                << boxBody->getMass()                    << std::endl
    //<< "massCenterOfGravity: " << boxBody->getMassCenterOfGravity().x() << ", "      << boxBody->getMassCenterOfGravity().y() << ", " << boxBody->getMassCenterOfGravity().z() << std::endl
    //<< "massInertiaTensor: "   << std::endl
    //<< boxBody->getMassInertiaTensor()[0][0] << " "<< boxBody->getMassInertiaTensor()[0][1] << " "<< boxBody->getMassInertiaTensor()[0][2] << " "   << boxBody->getMassInertiaTensor()[0][3] << std::endl
    //<< boxBody->getMassInertiaTensor()[1][0] << " "<< boxBody->getMassInertiaTensor()[1][1] << " "<< boxBody->getMassInertiaTensor()[1][2] << " "   << boxBody->getMassInertiaTensor()[1][3] << std::endl
    //<< boxBody->getMassInertiaTensor()[2][0] << " "<< boxBody->getMassInertiaTensor()[2][1] << " "<< boxBody->getMassInertiaTensor()[2][2] << " "   << boxBody->getMassInertiaTensor()[2][3] << std::endl
    //<< boxBody->getMassInertiaTensor()[3][0] << " "<< boxBody->getMassInertiaTensor()[3][1] << " "<< boxBody->getMassInertiaTensor()[3][2] << " "   << boxBody->getMassInertiaTensor()[3][3] << std::endl
    //<< std::endl;

    PhysicsBoxGeomRecPtr boxGeom = PhysicsBoxGeom::create();
    boxGeom->setBody(boxBody);
    boxGeom->setSpace(physicsSpace);
    boxGeom->setLengths(Lengths);


    //add attachments
    boxNode->addAttachment(boxGeom);
    boxTransNode->addAttachment(boxBody);
    boxTransNode->addChild(boxNode);


    //add to SceneGraph
    spaceGroupNode->addChild(boxTransNode);

    commitChanges();

}

//////////////////////////////////////////////////////////////////////////
//! build a sphere
//////////////////////////////////////////////////////////////////////////
void buildSphere(Node* const spaceGroupNode, PhysicsWorld* const physicsWorld, PhysicsHashSpace* const physicsSpace)
{
    Real32 Radius((Real32)(rand()%2)*0.5+0.5);
    Matrix m;
    //create OpenSG mesh
    GeometryRecPtr sphere;
    NodeRecPtr sphereNode = makeSphere(2, Radius);
    sphere = dynamic_cast<Geometry*>(sphereNode->getCore());
    SimpleMaterialRecPtr sphere_mat = SimpleMaterial::create();
    sphere_mat->setAmbient(Color3f(0.0,0.0,0.0));
    sphere_mat->setDiffuse(Color3f(0.0,0.0,1.0));

    sphere->setMaterial(sphere_mat);

    TransformRecPtr sphereTrans;
    NodeRecPtr sphereTransNode = makeCoredNode<Transform>(&sphereTrans);
    m.setIdentity();
    Real32 randX = (Real32)(rand()%10)-5.0;
    Real32 randY = (Real32)(rand()%10)-5.0;
    m.setTranslate(randX, randY, 10.0);
    sphereTrans->setMatrix(m);

    //create ODE data
    PhysicsBodyRecPtr sphereBody = PhysicsBody::create(physicsWorld);
    sphereBody->setPosition(Vec3f(randX, randY, 10.0));
    sphereBody->setAngularDamping(0.0001);

    sphereBody->setSphereMass(1.0,Radius);

    PhysicsSphereGeomRecPtr sphereGeom = PhysicsSphereGeom::create();
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
}

//////////////////////////////////////////////////////////////////////////
//! trimesh defined by filenode will be loaded
//////////////////////////////////////////////////////////////////////////
void buildTriMesh(Node* const TriGeometryBase, Node* const spaceGroupNode, PhysicsWorld* const physicsWorld, PhysicsHashSpace* const physicsSpace)
{
    NodeRecPtr tri = cloneTree(TriGeometryBase);
    if(tri!=NULL)
    {
        GeometryRecPtr triGeo = dynamic_cast<Geometry*>(tri->getCore()); 
        Matrix m;
        SimpleMaterialRecPtr tri_mat = SimpleMaterial::create();
        tri_mat->setAmbient(Color3f(0.1,0.1,0.2));
        tri_mat->setDiffuse(Color3f(1.0,0.1,0.7));

        triGeo->setMaterial(tri_mat);
        TransformRecPtr triTrans;
        NodeRecPtr triTransNode = makeCoredNode<Transform>(&triTrans);
        m.setIdentity();
        Real32 randX = (Real32)(rand()%10)-5.0;
        Real32 randY = (Real32)(rand()%10)-5.0;
        m.setTranslate(randX, randY, 18.0);
        triTrans->setMatrix(m);

        //create ODE data
        Vec3f GeometryBounds(calcMinGeometryBounds(triGeo));
        PhysicsBodyRecPtr triBody = PhysicsBody::create(physicsWorld);
        triBody->setPosition(Vec3f(randX, randY, 18.0));
        triBody->setLinearDamping(0.0001);
        triBody->setAngularDamping(0.0001);

        triBody->setBoxMass(1.0,GeometryBounds.x(), GeometryBounds.y(), GeometryBounds.z());
        PhysicsGeomRecPtr triGeom;
        if(true)
        {
            triGeom = PhysicsTriMeshGeom::create();
            triGeom->setBody(triBody);
            //add geom to space for collision
            triGeom->setSpace(physicsSpace);
            //set the geometryNode to fill the ode-triMesh
            NodeRecPtr TorusGeometryNode(makeTorus(0.55, 1.05, 6, 6));
            dynamic_pointer_cast<PhysicsTriMeshGeom>(triGeom)->setGeometryNode(TorusGeometryNode);
        }

        //add attachments
        tri->addAttachment(triGeom);
        triTransNode->addAttachment(triBody);
        //add to SceneGraph
        triTransNode->addChild(tri);
        spaceGroupNode->addChild(triTransNode);
    }
    else
    {
        SLOG << "Could not read MeshData!" << endLog;
    }

    commitChanges();
}

