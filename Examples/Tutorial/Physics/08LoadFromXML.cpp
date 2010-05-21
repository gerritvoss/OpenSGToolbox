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

#include "OSGSimpleStatisticsForeground.h"

#include "OSGFCFileHandler.h"
#include "OSGContainerUtils.h"

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
void buildCar();
void buildTriMesh(void);
void buildSphere(void);
void buildBox(void);

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerUnrecPtr TutorialWindow;
NodeUnrecPtr TriGeometryBase;

PhysicsHandlerUnrecPtr physHandler;
PhysicsWorldUnrecPtr physicsWorld;
PhysicsSpaceUnrecPtr physicsSpace;

//just for hierarchy
NodeUnrecPtr spaceGroupNode;

NodeUnrecPtr rootNode;

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
            case KeyEvent::KEY_S:
                {
                    buildSphere();
                }
                break;
            case KeyEvent::KEY_B:
                {
                    buildBox();
                }
                break;
            case KeyEvent::KEY_Z:
                {
                    //SceneFileHandler::the().write(rootNode, "scene.osb");
                }
                break;
            case KeyEvent::KEY_T:
                {
                    buildTriMesh();
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

    //Make Base Geometry Node
    TriGeometryBase = makeTorus(0.5, 1.0, 24, 24);

    //Setup Physics Scene
    FCFileType::FCPtrStore NewContainers;
    NewContainers = FCFileHandler::the()->read(BoostPath("Data/08PhysicsData.xml"));

    FCFileType::FCPtrStore::iterator Itor;
    for(Itor = NewContainers.begin() ; Itor != NewContainers.end() ; ++Itor)
    {
        //Get Physics Handler
        if( (*Itor)->getType() == PhysicsHandler::getClassType())
        {
            physHandler = dynamic_pointer_cast<PhysicsHandler>(*Itor);
        }
        //Get Physics World
        if( (*Itor)->getType() == PhysicsWorld::getClassType())
        {
            physicsWorld=dynamic_pointer_cast<PhysicsWorld>(*Itor);
        }
        //Get Physics World
        if( (*Itor)->getType().isDerivedFrom(PhysicsSpace::getClassType()))
        {
            physicsSpace = dynamic_pointer_cast<PhysicsSpace>(*Itor);
        }

        //Get Root Node
        if( (*Itor)->getType() == Node::getClassType() &&
                dynamic_pointer_cast<Node>(*Itor)->getParent() == NULL)
        {
            rootNode = dynamic_pointer_cast<Node>(*Itor);
        }
    }
    commitChanges();

    FCFileType::FCPtrStore SaveContainers;
    SaveContainers.insert(rootNode);
    FCFileHandler::the()->write(SaveContainers, BoostPath("08Output.xml"));

    //Find the Physics Space Node
    spaceGroupNode = dynamic_pointer_cast<Node>(getFieldContainer("Physics Space Group Node"));
    std::cout << "spaceGroupNode " << spaceGroupNode << std::endl;

    physHandler->attachUpdateProducer(TutorialWindow->editEventProducer());

    //Create Statistics Foreground
    SimpleStatisticsForegroundUnrecPtr PhysicsStatForeground = SimpleStatisticsForeground::create();
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

    SimpleStatisticsForegroundUnrecPtr RenderStatForeground = SimpleStatisticsForeground::create();
    RenderStatForeground->setSize(25);
    RenderStatForeground->setColor(Color4f(0,1,0,0.7));
    RenderStatForeground->addElement(RenderAction::statDrawTime, "Draw FPS: %r.3f");
    RenderStatForeground->addElement(RenderAction::statNGeometries, 
            "%d Nodes drawn");




    // tell the manager what to manage
    mgr->setRoot  (rootNode);

    mgr->getWindow()->getPort(0)->addForeground(PhysicsStatForeground);
    mgr->getWindow()->getPort(0)->addForeground(RenderStatForeground);
    physHandler->setStatistics(PhysicsStatForeground->getCollector());
    mgr->getRenderAction()->setStatCollector(RenderStatForeground->getCollector());

    // show the whole rootNode
    mgr->showAll();

    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
            WinSize,
            "08LoadFromXML");

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
void buildBox(void)
{
    Vec3f Lengths((Real32)(rand()%2)+1.0, (Real32)(rand()%2)+1.0, (Real32)(rand()%2)+1.0);
    Matrix m;
    //create OpenSG mesh
    GeometryUnrecPtr box;
    NodeUnrecPtr boxNode = makeBox(Lengths.x(), Lengths.y(), Lengths.z(), 1, 1, 1);
    box = dynamic_cast<Geometry*>(boxNode->getCore());
    SimpleMaterialUnrecPtr box_mat = SimpleMaterial::create();
    box_mat->setAmbient(Color3f(0.0,0.0,0.0));
    box_mat->setDiffuse(Color3f(0.0,1.0 ,0.0));
    box->setMaterial(box_mat);
    TransformUnrecPtr boxTrans;
    NodeUnrecPtr boxTransNode = makeCoredNode<Transform>(&boxTrans);
    m.setIdentity();
    Real32 randX = (Real32)(rand()%10)-5.0;
    Real32 randY = (Real32)(rand()%10)-5.0;
    m.setTranslate(randX, randY, 10.0);
    boxTrans->setMatrix(m);

    //create ODE data
    PhysicsBodyUnrecPtr boxBody = PhysicsBody::create(physicsWorld);
    boxBody->setPosition(Vec3f(randX, randY, 10.0));
    boxBody->setBoxMass(1.0, Lengths.x(), Lengths.y(), Lengths.z());

    PhysicsBoxGeomUnrecPtr boxGeom = PhysicsBoxGeom::create();
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
void buildSphere(void)
{
    Real32 Radius((Real32)(rand()%2)*0.5+0.5);
    Matrix m;
    //create OpenSG mesh
    GeometryUnrecPtr sphere;
    NodeUnrecPtr sphereNode = makeSphere(2, Radius);
    sphere = dynamic_cast<Geometry*>(sphereNode->getCore());
    SimpleMaterialUnrecPtr sphere_mat = SimpleMaterial::create();
    sphere_mat->setAmbient(Color3f(0.0,0.0,0.0));
    sphere_mat->setDiffuse(Color3f(0.0,0.0,1.0));
    sphere->setMaterial(sphere_mat);
    TransformUnrecPtr sphereTrans;
    NodeUnrecPtr sphereTransNode = makeCoredNode<Transform>(&sphereTrans);
    m.setIdentity();
    Real32 randX = (Real32)(rand()%10)-5.0;
    Real32 randY = (Real32)(rand()%10)-5.0;
    m.setTranslate(randX, randY, 10.0);
    sphereTrans->setMatrix(m);
    //create ODE data
    PhysicsBodyUnrecPtr sphereBody = PhysicsBody::create(physicsWorld);
    sphereBody->setPosition(Vec3f(randX, randY, 10.0));
    sphereBody->setAngularDamping(0.0001);
    sphereBody->setSphereMass(1.0,Radius);

    PhysicsSphereGeomUnrecPtr sphereGeom = PhysicsSphereGeom::create();
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
void buildTriMesh(void)
{
    //NodeUnrecPtr tri = makeTorus(0.5, 1.0, 24, 12);
    //NodeUnrecPtr tri = makeBox(10.0, 10.0, 10.0, 1, 1, 1);
    NodeRefPtr tri = cloneTree(TriGeometryBase);
    if(tri!=NULL)
    {
        GeometryUnrecPtr triGeo = dynamic_cast<Geometry*>(tri->getCore()); 
        Matrix m;
        SimpleMaterialUnrecPtr tri_mat = SimpleMaterial::create();
        tri_mat->setAmbient(Color3f(0.1,0.1,0.2));
        tri_mat->setDiffuse(Color3f(1.0,0.1,0.7));
        triGeo->setMaterial(tri_mat);
        TransformUnrecPtr triTrans;
        NodeUnrecPtr triTransNode = makeCoredNode<Transform>(&triTrans);
        m.setIdentity();
        Real32 randX = (Real32)(rand()%10)-5.0;
        Real32 randY = (Real32)(rand()%10)-5.0;
        m.setTranslate(randX, randY, 18.0);
        triTrans->setMatrix(m);

        //create ODE data
        Vec3f GeometryBounds(calcMinGeometryBounds(triGeo));
        PhysicsBodyUnrecPtr triBody = PhysicsBody::create(physicsWorld);
        triBody->setPosition(Vec3f(randX, randY, 18.0));
        triBody->setLinearDamping(0.0001);
        triBody->setAngularDamping(0.0001);
        triBody->setBoxMass(1.0,GeometryBounds.x(), GeometryBounds.y(), GeometryBounds.z());
        PhysicsGeomUnrecPtr triGeom;
        if(true)
        {
            triGeom = PhysicsTriMeshGeom::create();
            triGeom->setBody(triBody);
            //add geom to space for collision
            triGeom->setSpace(physicsSpace);
            //set the geometryNode to fill the ode-triMesh
            NodeUnrecPtr TorusGeomNode(makeTorus(0.5, 1.0, 10, 10));
            dynamic_pointer_cast<PhysicsTriMeshGeom>(triGeom)->setGeometryNode(TorusGeomNode);
        }
        else
        {

            triGeom = PhysicsBoxGeom::create();
            triGeom->setBody(triBody);
            triGeom->setSpace(physicsSpace);
            dynamic_pointer_cast<PhysicsBoxGeom>(triGeom)->setLengths(GeometryBounds);

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
