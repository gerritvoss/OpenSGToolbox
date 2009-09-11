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

#include <OpenSG/OSGSimpleStatisticsForeground.h>

#include <OpenSG/Toolbox/OSGFCFileHandler.h>
#include <OpenSG/Toolbox/OSGFieldContainerUtils.h>

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
void buildCar();
void buildTriMesh(void);
void buildSphere(void);
void buildBox(void);

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;
NodePtr TriGeometryBase;

PhysicsHandlerPtr physHandler;
PhysicsWorldPtr physicsWorld;
PhysicsSpacePtr physicsSpace;

//just for hierarchy
NodePtr spaceGroupNode;

NodePtr rootNode;

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEvent& e)
   {
       if(e.getKey() == KeyEvent::KEY_Q && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           TutorialWindowEventProducer->closeWindow();
       }
       switch(e.getKey())
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

   virtual void keyReleased(const KeyEvent& e)
   {
   }

   virtual void keyTyped(const KeyEvent& e)
   {
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


    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

	
    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindowEventProducer->getWindow());

    //Make Base Geometry Node
    TriGeometryBase = makeTorus(0.5, 1.0, 24, 24);

    //Setup Physics Scene
	FCFileType::FCPtrStore NewContainers;
	NewContainers = FCFileHandler::the()->read(Path("Data/08PhysicsData.xml"));

    FCFileType::FCPtrStore::iterator Itor;
    for(Itor = NewContainers.begin() ; Itor != NewContainers.end() ; ++Itor)
    {
        //Get Physics Handler
        if( (*Itor)->getType() == PhysicsHandler::getClassType())
        {
            addRefCP(*Itor);
            physHandler = PhysicsHandler::Ptr::dcast(*Itor);
        }
        //Get Physics World
        if( (*Itor)->getType() == PhysicsWorld::getClassType())
        {
            addRefCP(*Itor);
            physicsWorld=PhysicsWorld::Ptr::dcast(*Itor);
        }
        //Get Physics World
        if( (*Itor)->getType().isDerivedFrom(PhysicsSpace::getClassType()))
        {
            addRefCP(*Itor);
            physicsSpace = PhysicsSpace::Ptr::dcast(*Itor);
        }

        //Get Root Node
        if( (*Itor)->getType() == Node::getClassType() &&
            Node::Ptr::dcast(*Itor)->getParent() == NullFC)
        {
            rootNode = Node::Ptr::dcast(*Itor);
        }
    }

    //Find the Physics Space Node
    spaceGroupNode = NodePtr::dcast(getFieldContainer("Physics Space Group Node"));

    physHandler->attachUpdateProducer(TutorialWindowEventProducer);
    
    //Create Statistics Foreground
    SimpleStatisticsForegroundPtr PhysicsStatForeground = SimpleStatisticsForeground::create();
    beginEditCP(PhysicsStatForeground);
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
    endEditCP(PhysicsStatForeground);
    
    SimpleStatisticsForegroundPtr RenderStatForeground = SimpleStatisticsForeground::create();
    beginEditCP(RenderStatForeground);
        RenderStatForeground->setSize(25);
        RenderStatForeground->setColor(Color4f(0,1,0,0.7));
        RenderStatForeground->addElement(RenderAction::statDrawTime, "Draw FPS: %r.3f");
        RenderStatForeground->addElement(RenderAction::statNGeometries, 
                           "%d Nodes drawn");
    endEditCP(RenderStatForeground);




    // tell the manager what to manage
    mgr->setRoot  (rootNode);

    beginEditCP(mgr->getWindow()->getPort(0), Viewport::ForegroundsFieldMask);
        mgr->getWindow()->getPort(0)->getForegrounds().push_back(PhysicsStatForeground);
        mgr->getWindow()->getPort(0)->getForegrounds().push_back(RenderStatForeground);
    endEditCP(mgr->getWindow()->getPort(0), Viewport::ForegroundsFieldMask);
    physHandler->setStatistics(&PhysicsStatForeground->getCollector());
    mgr->getAction()->setStatistics(&RenderStatForeground->getCollector());

    // show the whole rootNode
    mgr->showAll();
    
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "08LoadFromXML");

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
void buildBox(void)
{
    Vec3f Lengths((Real32)(rand()%2)+1.0, (Real32)(rand()%2)+1.0, (Real32)(rand()%2)+1.0);
    Matrix m;
    //create OpenSG mesh
    GeometryPtr box;
    NodePtr boxNode = makeBox(Lengths.x(), Lengths.y(), Lengths.z(), 1, 1, 1);
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
    Real32 randX = (Real32)(rand()%10)-5.0;
    Real32 randY = (Real32)(rand()%10)-5.0;
    m.setTranslate(randX, randY, 10.0);
    beginEditCP(boxTrans, Transform::MatrixFieldMask);
        boxTrans->setMatrix(m);
    endEditCP(boxTrans, Transform::MatrixFieldMask);

    //create ODE data
    PhysicsBodyPtr boxBody = PhysicsBody::create(physicsWorld);
    beginEditCP(boxBody, PhysicsBody::PositionFieldMask);
        boxBody->setPosition(Vec3f(randX, randY, 10.0));
    endEditCP(boxBody, PhysicsBody::PositionFieldMask);
    boxBody->setBoxMass(1.0, Lengths.x(), Lengths.y(), Lengths.z());

    PhysicsBoxGeomPtr boxGeom = PhysicsBoxGeom::create();
    beginEditCP(boxGeom, PhysicsBoxGeom::BodyFieldMask | PhysicsBoxGeom::SpaceFieldMask  | PhysicsBoxGeom::LengthsFieldMask);
        boxGeom->setBody(boxBody);
        boxGeom->setSpace(physicsSpace);
        boxGeom->setLengths(Lengths);
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
}

//////////////////////////////////////////////////////////////////////////
//! build a sphere
//////////////////////////////////////////////////////////////////////////
void buildSphere(void)
{
    Real32 Radius((Real32)(rand()%2)*0.5+0.5);
    Matrix m;
    //create OpenSG mesh
    GeometryPtr sphere;
    NodePtr sphereNode = makeSphere(2, Radius);
    sphere = GeometryPtr::dcast(sphereNode->getCore());
    SimpleMaterialPtr sphere_mat = SimpleMaterial::create();
    beginEditCP(sphere_mat);
    sphere_mat->setAmbient(Color3f(0.0,0.0,0.0));
    sphere_mat->setDiffuse(Color3f(0.0,0.0,1.0));
    endEditCP(sphere_mat);
    beginEditCP(sphere, Geometry::MaterialFieldMask);
    sphere->setMaterial(sphere_mat);
    endEditCP(sphere);
    TransformPtr sphereTrans;
    NodePtr sphereTransNode = makeCoredNode<Transform>(&sphereTrans);
    m.setIdentity();
    Real32 randX = (Real32)(rand()%10)-5.0;
    Real32 randY = (Real32)(rand()%10)-5.0;
    m.setTranslate(randX, randY, 10.0);
    beginEditCP(sphereTrans, Transform::MatrixFieldMask);
    sphereTrans->setMatrix(m);
    endEditCP(sphereTrans);
    //create ODE data
    PhysicsBodyPtr sphereBody = PhysicsBody::create(physicsWorld);
    beginEditCP(sphereBody, PhysicsBody::PositionFieldMask | PhysicsBody::AngularDampingFieldMask);
        sphereBody->setPosition(Vec3f(randX, randY, 10.0));
        sphereBody->setAngularDamping(0.0001);
    endEditCP(sphereBody, PhysicsBody::PositionFieldMask | PhysicsBody::AngularDampingFieldMask);
    sphereBody->setSphereMass(1.0,Radius);

    PhysicsSphereGeomPtr sphereGeom = PhysicsSphereGeom::create();
    beginEditCP(sphereGeom, PhysicsSphereGeom::BodyFieldMask | PhysicsSphereGeom::SpaceFieldMask | PhysicsSphereGeom::RadiusFieldMask);
        sphereGeom->setBody(sphereBody);
        sphereGeom->setSpace(physicsSpace);
        sphereGeom->setRadius(Radius);
    endEditCP(sphereGeom, PhysicsSphereGeom::BodyFieldMask | PhysicsSphereGeom::SpaceFieldMask | PhysicsSphereGeom::RadiusFieldMask);
    
    //add attachments
    beginEditCP(sphereNode, Node::AttachmentsFieldMask);
    sphereNode->addAttachment(sphereGeom);
    endEditCP(sphereNode);
    beginEditCP(sphereTransNode, Node::AttachmentsFieldMask | Node::ChildrenFieldMask);
    sphereTransNode->addAttachment(sphereBody);
    sphereTransNode->addChild(sphereNode);
    endEditCP(sphereTransNode);
    //add to SceneGraph
    beginEditCP(spaceGroupNode, Node::ChildrenFieldMask);
    spaceGroupNode->addChild(sphereTransNode);
    endEditCP(spaceGroupNode);
}

//////////////////////////////////////////////////////////////////////////
//! trimesh defined by filenode will be loaded
//////////////////////////////////////////////////////////////////////////
void buildTriMesh(void)
{
    //NodePtr tri = makeTorus(0.5, 1.0, 24, 12);
    //NodePtr tri = makeBox(10.0, 10.0, 10.0, 1, 1, 1);
    NodePtr tri = Node::Ptr::dcast(TriGeometryBase->shallowCopy());
    if(tri!=NullFC)
    {
        GeometryPtr triGeo = GeometryPtr::dcast(tri->getCore()); 
        Matrix m;
        SimpleMaterialPtr tri_mat = SimpleMaterial::create();
        beginEditCP(tri_mat);
        tri_mat->setAmbient(Color3f(0.1,0.1,0.2));
        tri_mat->setDiffuse(Color3f(1.0,0.1,0.7));
        endEditCP(tri_mat);
        triGeo->setMaterial(tri_mat);
        TransformPtr triTrans;
        NodePtr triTransNode = makeCoredNode<Transform>(&triTrans);
        m.setIdentity();
		Real32 randX = (Real32)(rand()%10)-5.0;
		Real32 randY = (Real32)(rand()%10)-5.0;
        m.setTranslate(randX, randY, 18.0);
        triTrans->setMatrix(m);

        //create ODE data
        Vec3f GeometryBounds(calcMinGeometryBounds(triGeo));
        PhysicsBodyPtr triBody = PhysicsBody::create(physicsWorld);
        beginEditCP(triBody, PhysicsBody::PositionFieldMask | PhysicsBody::LinearDampingFieldMask | PhysicsBody::AngularDampingFieldMask);
            triBody->setPosition(Vec3f(randX, randY, 18.0));
            triBody->setLinearDamping(0.0001);
            triBody->setAngularDamping(0.0001);
        endEditCP(triBody, PhysicsBody::PositionFieldMask | PhysicsBody::LinearDampingFieldMask | PhysicsBody::AngularDampingFieldMask);
            triBody->setBoxMass(1.0,GeometryBounds.x(), GeometryBounds.y(), GeometryBounds.z());
        PhysicsGeomPtr triGeom;
        if(true)
        {
            triGeom = PhysicsTriMeshGeom::create();
            beginEditCP(triGeom, PhysicsTriMeshGeom::BodyFieldMask | 
                            PhysicsTriMeshGeom::SpaceFieldMask | 
                            PhysicsTriMeshGeom::GeometryNodeFieldMask);
                triGeom->setBody(triBody);
                //add geom to space for collision
                triGeom->setSpace(physicsSpace);
                //set the geometryNode to fill the ode-triMesh
                PhysicsTriMeshGeom::Ptr::dcast(triGeom)->setGeometryNode(makeTorus(0.5, 1.0, 10, 10));
            endEditCP(triGeom, PhysicsTriMeshGeom::BodyFieldMask | 
                            PhysicsTriMeshGeom::SpaceFieldMask | 
                            PhysicsTriMeshGeom::GeometryNodeFieldMask);
        }
        else
        {

            triGeom = PhysicsBoxGeom::create();
            beginEditCP(triGeom, PhysicsBoxGeom::BodyFieldMask | PhysicsBoxGeom::SpaceFieldMask | PhysicsBoxGeom::LengthsFieldMask);
                triGeom->setBody(triBody);
                triGeom->setSpace(physicsSpace);
                PhysicsBoxGeom::Ptr::dcast(triGeom)->setLengths(GeometryBounds);

            endEditCP(triGeom, PhysicsBoxGeom::BodyFieldMask | PhysicsBoxGeom::SpaceFieldMask | PhysicsBoxGeom::LengthsFieldMask);
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
}
