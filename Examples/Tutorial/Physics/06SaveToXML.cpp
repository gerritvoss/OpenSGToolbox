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

#include "OSGFCFileHandler.h"

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

void keyPressed(KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_Q &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
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
        TutorialWindow->connectKeyPressed(boost::bind(keyPressed, _1));

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
        NodeRecPtr spaceGroupNode = makeCoredNode<Group>();
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

        UInt32 NumBoxes(5);
        for(UInt32 i(0) ; i<NumBoxes ; ++i)
        {
            Vec3f BoxSize(1.0,1.0,1.0);
            Pnt3f BoxPosition((Real32)(rand()%10)-5.0, (Real32)(rand()%10)-5.0, 10.0);

            buildBox(BoxPosition,
                     BoxSize,
                     Color3f(0.0f,1.0f,0.0f),
                     spaceGroupNode,
                     physicsWorld,
                     hashSpace);
        }

        FCFileType::FCPtrStore CollectionStore;
        CollectionStore.insert(rootNode);

        FCFileHandler::the()->write(CollectionStore,BoostPath("./06Output.xml"));

        // tell the manager what to manage
        sceneManager.setRoot  (rootNode);

        // show the whole rootNode
        sceneManager.showAll();

        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "06PhysicsFileIO");

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

