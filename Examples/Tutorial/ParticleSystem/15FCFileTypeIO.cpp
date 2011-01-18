// Simple demonstration of XML file input
// Reads an XML file containing particle systems, and creates a scene with it

// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

#include "OSGSimpleSceneManager.h"
#include "OSGGroup.h"
#include "OSGWindowUtils.h"
// Input
#include "OSGPerspectiveCamera.h"
#include "OSGGradientBackground.h"
#include "OSGPolygonForeground.h"
#include "OSGNode.h"
#include "OSGViewport.h"
#include "OSGParticleSystem.h"
#include "OSGParticleSystemCore.h"
#include "OSGFCFileHandler.h"

#include <boost/filesystem/operations.hpp>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with , but that would be a bit tedious for this example
OSG_USING_NAMESPACE

void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

void keyTyped(KeyEventDetails* const details,
              SimpleSceneManager *mgr
             )
{
    if(details->getKey() == KeyEventDetails::KEY_Q &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
    }
    if(details->getKey() == KeyEventDetails::KEY_S)
    {
        mgr->setStatistics(true);
    }
    if(details->getKey() == KeyEventDetails::KEY_A)
    {
        mgr->setStatistics(false);
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

// Initialize GLUT & OpenSG and set up the scene
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
        TutorialWindow->connectKeyTyped(boost::bind(keyTyped, _1, &sceneManager));
        // open window

        /* Set up complete, now performing XML import */

        BoostPath ExecutableDirectory(argv[0]);
        ExecutableDirectory.remove_leaf();
        BoostPath FilePath;
        if(argc > 1)
        {
            FilePath  = BoostPath(argv[1]);
        }
        else
        {
            FilePath = BoostPath("./Data/ParticleSystemExport.xml");
        }

        if(!boost::filesystem::exists(FilePath))
        {
            std::cerr << "Could not find file by path: " << FilePath.string() << std::endl;
            osgExit();
            return -1;
        }


        // parse XML file to get field container data
        FCFileType::FCPtrStore NewContainers;
        NewContainers = FCFileHandler::the()->read(FilePath);

        // find root node from container, attach update listeners to particle systems
        std::vector<NodeRefPtr> RootNodes;
        for(FCFileType::FCPtrStore::iterator Itor = NewContainers.begin() ; Itor != NewContainers.end() ; ++Itor)
        {
            // get root node
            if( (*Itor)->getType() == Node::getClassType() &&
                dynamic_pointer_cast<Node>(*Itor)->getParent() == NULL)
            {
                RootNodes.push_back(dynamic_pointer_cast<Node>(*Itor));
            }
            else if( (*Itor)->getType() == ParticleSystem::getClassType()) //attach update listeners to particle systems present
            {
                ParticleSystemRefPtr ExampleParticleSystems = dynamic_pointer_cast<ParticleSystem>(*Itor);
                ExampleParticleSystems->attachUpdateProducer(TutorialWindow);
            }
        }

        // get root node that was extracted from XML file
        if(RootNodes.size() > 0)
        {
            NodeRefPtr scene = RootNodes[0];

            // set root node
            sceneManager.setRoot(scene);

        }

        // Show the whole Scene
        sceneManager.showAll();
        sceneManager.setHeadlight(true);
        sceneManager.getCamera()->setFar(10000);

        // main loop
        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "15FCFileTypeIO");

        //Enter main Loop
        TutorialWindow->mainLoop();


    }
    osgExit();

    return 0;
}
