// 
// OpenSGToolbox Tutorial: 08MorphGeometry
//
// Demonstrates a simple animation using transformation keyframes. 
//


// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// Methods to create simple geometry: boxes, spheres, tori etc.
#include "OSGSimpleGeometry.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"

// Input
#include "OSGWindowUtils.h"
#include "OSGWindowEventProducer.h"

#include "OSGFCFileHandler.h"
#include <boost/filesystem/convenience.hpp>

#include "OSGAnimation.h"

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE


// forward declaration so we can have the interesting stuff upfront
// The SimpleSceneManager to manage simple applications
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

void keyPressed(KeyEventDetails* const details, WindowEventProducer* const TutorialWindow)
{
    if(details->getKey() == KeyEventDetails::KEY_Q &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        TutorialWindow->closeWindow();
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

        //Initialize Window
        TutorialWindow->initWindow();

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
        TutorialWindow->connectKeyPressed(boost::bind(keyPressed, _1, TutorialWindow.get()));

        BoostPath FilePath("../Animation/Data/Nanobot.dae");
        if(argc >= 2)
        {
            FilePath = BoostPath(argv[1]);
            if(!boost::filesystem::exists(FilePath))
            {
                std::cerr << "Could not load file: "<< FilePath.string()
                          << ", because no such files exists."<< std::endl;
                FilePath = BoostPath("../Animation/Data/Nanobot.dae");
            }
        }

        NodeRefPtr LoadedRoot;
        std::vector<AnimationRecPtr> LoadedAnimations;

        FCFileType::FCPtrStore ObjStore;
        try
        {
            ObjStore = FCFileHandler::the()->read(FilePath);
        }
        catch(std::exception &ex)
        {
            std::cerr << "Failed to load file: " << FilePath.string() << ", error:"
                     << ex.what()                        << std::endl;
            return -1;
        }
        for(FCFileType::FCPtrStore::iterator StorItor(ObjStore.begin());
            StorItor != ObjStore.end();
            ++StorItor)
        {
            //Animations
            if((*StorItor)->getType().isDerivedFrom(Animation::getClassType()))
            {
                LoadedAnimations.push_back(dynamic_pointer_cast<Animation>(*StorItor));
                LoadedAnimations.back()->attachUpdateProducer(TutorialWindow);
                LoadedAnimations.back()->start();
            }
            //Root Node
            if((*StorItor)->getType() == Node::getClassType() &&
                    dynamic_pointer_cast<Node>(*StorItor)->getParent() == NULL)
            {
                LoadedRoot = dynamic_pointer_cast<Node>(*StorItor);
            }
        }

        if(LoadedRoot == NULL)
        {
            LoadedRoot= makeTorus(.5, 2, 32, 32);
        }

        //Make Main Scene Node
        NodeRefPtr scene = makeCoredNode<Group>();

        scene->addChild(LoadedRoot);

        // tell the manager what to manage
        sceneManager.setRoot  (scene);

        // show the whole scene
        sceneManager.showAll();
        sceneManager.setStatistics(true);

        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "Collada Loader");

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

