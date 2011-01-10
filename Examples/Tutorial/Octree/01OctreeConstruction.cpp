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
#include "OSGSceneFileHandler.h"

#include "OSGSolidBackground.h"

#include "OSGComponentTransform.h"
#include "OSGTransform.h"
#include "OSGTypeFactory.h"


#include "OSGFieldContainerFactory.h"
#include "OSGNameAttachment.h"

// Input
#include "OSGWindowUtils.h"

#include "OSGOctree.h"
#include "OSGOctreeUtils.h"
#include <boost/filesystem/convenience.hpp>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

void keyPressed(KeyEventDetails* const details,
                Node* const sceneGeoNode,
                Node* const octreeNode)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
    switch(details->getKey())
    {
        case KeyEventDetails::KEY_1:
            if(sceneGeoNode->getTravMask() != 0)
            {
                sceneGeoNode->setTravMask(0);
            }
            else
            {
                sceneGeoNode->setTravMask(1);
            }
            break;
        case KeyEventDetails::KEY_2:
            if(octreeNode->getTravMask() != 0)
            {
                octreeNode->setTravMask(0);
            }
            else
            {
                octreeNode->setTravMask(1);
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

        BoostPath ModelFilePath(".//Data//CellParts.osb");

        if(argc >= 2)
        {
            ModelFilePath = BoostPath(argv[1]);
            if(!boost::filesystem::exists(ModelFilePath))
            {
                ModelFilePath = BoostPath(".//Data//CellParts.osb");
            }
        }

        //Make Base Geometry Node
        NodeRecPtr SceneGeometryNode =
            SceneFileHandler::the()->read(ModelFilePath.string().c_str());
        if(SceneGeometryNode == NULL)
        {
            SceneGeometryNode = makeTorus(1.0, 10.0, 24, 24);
        }

        NodeRecPtr RootNode = makeCoredNode<Group>();
        RootNode->addChild(SceneGeometryNode);
        commitChanges();

        //Create the Octree

        SLOG << "Started Building Octree" << std::endl;
        Time StartTime;
        StartTime = getSystemTime();
		OctreePtr TheOctree = Octree::buildTree(RootNode,1,10,1.5f,true);

        SLOG << "Building Octree: " << getSystemTime() - StartTime << " s" << std::endl;

        //Create a visualization of the octree
        SLOG << "Started Building Visualization" << std::endl;
        StartTime = getSystemTime();
        NodeRecPtr OctreeVisNode = OctreeVisualization::createOctreeVisualization(TheOctree, 100);
        SLOG << "Building Visualization: " << getSystemTime() - StartTime << " s" << std::endl;
        RootNode->addChild(OctreeVisNode);

        TutorialWindow->connectKeyPressed(boost::bind(keyPressed,
                                                      _1,
                                                      SceneGeometryNode.get(),
                                                      OctreeVisNode.get()));

        //Set the background
        SolidBackgroundRecPtr TheBackground = SolidBackground::create();
        TheBackground->setColor(Color3f(0.0f,0.0f,0.0f));

        // tell the manager what to manage
        sceneManager.setRoot  (RootNode);
        sceneManager.getWindow()->getPort(0)->setBackground(TheBackground);

        // show the whole RootNode
        sceneManager.showAll();

        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "01OctreeConstruction");

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

