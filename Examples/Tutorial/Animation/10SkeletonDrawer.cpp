// 
// OpenSGToolbox Tutorial: 10SkeletonDrawer 
//
// Demonstrates creating a simple skeleton. 
//


// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"
#include "OSGWindowUtils.h"

// Input
#include "OSGKeyListener.h"

#include "OSGLineChunk.h"
#include "OSGBlendChunk.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"
#include "OSGSimpleGeometry.h"

//Animation
#include "OSGSkeletonBlendedGeometry.h"
#include "OSGSkeletonDrawable.h"

#include "OSGRandomPoolManager.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

void keyPressed(KeyEventDetails* const details, WindowEventProducer* const win)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        win->closeWindow();
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

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    {
        // Set up Window
        WindowEventProducerRecPtr TutorialWindow = createNativeWindow();

        SimpleSceneManager sceneManager;
        TutorialWindow->setDisplayCallback(boost::bind(display, &sceneManager));
        TutorialWindow->setReshapeCallback(boost::bind(reshape, _1, &sceneManager));

        //Initialize Window
        TutorialWindow->initWindow();

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

        //Attach to events
        TutorialWindow->connectMousePressed(boost::bind(mousePressed, _1, &sceneManager));
        TutorialWindow->connectMouseReleased(boost::bind(mouseReleased, _1, &sceneManager));
        TutorialWindow->connectMouseMoved(boost::bind(mouseMoved, _1, &sceneManager));
        TutorialWindow->connectMouseDragged(boost::bind(mouseDragged, _1, &sceneManager));
        TutorialWindow->connectMouseWheelMoved(boost::bind(mouseWheelMoved, _1, &sceneManager));
        TutorialWindow->connectKeyPressed(boost::bind(keyPressed, _1, TutorialWindow.get()));

        //SkeletonDrawer System Material
        LineChunkUnrecPtr ExampleLineChunk = LineChunk::create();
        ExampleLineChunk->setWidth(4.0f);
        ExampleLineChunk->setSmooth(true);

        BlendChunkUnrecPtr ExampleBlendChunk = BlendChunk::create();
        ExampleBlendChunk->setSrcFactor(GL_SRC_ALPHA);
        ExampleBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

        MaterialChunkUnrecPtr ExampleMaterialChunk = MaterialChunk::create();
        ExampleMaterialChunk->setAmbient(Color4f(1.0f,1.0f,1.0f,1.0f));
        ExampleMaterialChunk->setDiffuse(Color4f(0.0f,0.0f,0.0f,1.0f));
        ExampleMaterialChunk->setSpecular(Color4f(0.0f,0.0f,0.0f,1.0f));

        ChunkMaterialUnrecPtr ExampleMaterial = ChunkMaterial::create();
        ExampleMaterial->addChunk(ExampleLineChunk);
        ExampleMaterial->addChunk(ExampleMaterialChunk);
        ExampleMaterial->addChunk(ExampleBlendChunk);

        GeometryRefPtr SphereGeometry = makeSphereGeo(2, 0.25f);
        GeometryRefPtr BoxGeometry = makeBoxGeo(0.5f,0.5f,0.5f,1,1,1);

        //Skeleton
        SkeletonBlendedGeometryUnrecPtr ExampleSkeleton = SkeletonBlendedGeometry::create();

        //Joint
        TransformRecPtr ExampleRootJoint = Transform::create();

        NodeRecPtr ExampleRootJointNode = makeNodeFor(ExampleRootJoint);

        //Add this joint to the skeleton
        ExampleSkeleton->pushToJoints(ExampleRootJointNode, Matrix());

        NodeRecPtr TempRootJointNode = ExampleRootJointNode;
        NodeRefPtr GeoNode = makeNodeFor(BoxGeometry);
        TempRootJointNode->addChild(GeoNode);

        Matrix TempMat;
        //Create a set of randomly placed child joints
        for (Real32 i = 0.0f; i < 5.0f; ++i)
        {
            TransformRecPtr ExampleChildJoint = Transform::create();
            NodeRecPtr ExampleChildJointNode = makeNodeFor(ExampleChildJoint);

            GeoNode = makeNodeFor(SphereGeometry);
            ExampleChildJointNode->addChild(GeoNode);

            //TempMat.setTranslate(RandomPoolManager::getRandomReal32(0.0, 10.0f), RandomPoolManager::getRandomReal32(0.0f, 10.0f), RandomPoolManager::getRandomReal32(0.0f, 10.0f));
            switch((static_cast<UInt32>(i) % 3))
            {
                case 0:
                    TempMat.setTranslate(2.0f,0.0f,0.0f);
                    break;
                case 1:
                    TempMat.setTranslate(0.0f,2.0f,0.0f);
                    break;
                case 2:
                    TempMat.setTranslate(0.0f,0.0f,2.0f);
                    break;
            }

            //Set bind and current transformations to TempMat (calculated above)
            ExampleChildJoint->setMatrix(TempMat);

            //Add ExampleChildJoint as a child to the previous joint	
            TempRootJointNode->addChild(ExampleChildJointNode);//add a Child to the root joint

            //ExampleChildJoint will be the next parent joint
            TempRootJointNode = ExampleChildJointNode;

            //Add this joint to the skeleton
            Matrix InvBind(TempRootJointNode->getToWorld());
            InvBind.invert();
            ExampleSkeleton->pushToJoints(ExampleChildJointNode, InvBind);
        }


        //SkeletonDrawer
        SkeletonDrawableUnrecPtr ExampleSkeletonDrawable = SkeletonDrawable::create();
        ExampleSkeletonDrawable->setSkeleton(ExampleSkeleton);
        ExampleSkeletonDrawable->setMaterial(ExampleMaterial);

        //Skeleton Particle System Node
        NodeUnrecPtr SkeletonNode = Node::create();
        SkeletonNode->setCore(ExampleSkeletonDrawable);


        // Make Main Scene Node and add the Torus
        NodeUnrecPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(SkeletonNode);
        scene->addChild(ExampleRootJointNode);

        sceneManager.setRoot(scene);

        // Show the whole Scene
        sceneManager.showAll();


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "10SkeletonDrawer");

        //Main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}


// Callback functions

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

