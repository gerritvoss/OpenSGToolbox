// 
// OpenSGToolbox Tutorial: 02TransformAnimation
//
// Demonstrates a simple animation using transformation keyframes. 
//


// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// Methods to create simple geometry: boxes, spheres, tori etc.
#include "OSGSimpleGeometry.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"

#include "OSGSimpleMaterial.h"

#include "OSGComponentTransform.h"
#include "OSGTransform.h"
#include "OSGTypeFactory.h"

#include "OSGFieldContainerFactory.h"
#include "OSGNameAttachment.h"

#include "OSGContainerUtils.h"
#include "OSGMTRefCountPtr.h"

// Input
#include "OSGWindowUtils.h"
#include "OSGWindowEventProducer.h"

//Animation
#include "OSGAnimationGroup.h"

#include "OSGFCFileHandler.h"
#include <boost/filesystem/convenience.hpp>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE


// forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

void keyPressed(KeyEventDetails* const details, Animation* const anim, WindowEventProducer* const win)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        win->closeWindow();
    }

    switch(details->getKey())
    {
        case KeyEventDetails::KEY_SPACE:
            anim->pause(!anim->isPaused());
            break;
        case KeyEventDetails::KEY_ENTER:
            anim->attachUpdateProducer(win);
            anim->start();
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
        }
    }
    else if(details->getUnitsToScroll() < 0)
    {
        for(UInt32 i(0) ; i<abs(details->getUnitsToScroll()) ;++i)
        {
            mgr->mouseButtonPress(Navigator::UP_MOUSE,details->getLocation().x(),details->getLocation().y());
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
        TutorialWindow->connectMouseDragged(boost::bind(mouseDragged, _1, &sceneManager));
        TutorialWindow->connectMouseWheelMoved(boost::bind(mouseWheelMoved, _1, &sceneManager));

        AnimationGroupRecPtr TheLoadedAnimations = AnimationGroup::create();
        NodeRecPtr TheLoadedScene;


        BoostPath AnimFilePath("./Data/Nanobot.dae");
        if(argc >= 2)
        {
            AnimFilePath = BoostPath(argv[1]);
            if(!boost::filesystem::exists(AnimFilePath))
            {
                std::cerr << "Could not load file: "<< AnimFilePath.string()
                          << ", because no such files exists."<< std::endl;
                AnimFilePath = BoostPath("./Data/Nanobot.dae");
            }
        }

        FCFileType::FCPtrStore ObjStore = FCFileHandler::the()->read(AnimFilePath);
        for(FCFileType::FCPtrStore::iterator StorItor(ObjStore.begin());
            StorItor != ObjStore.end();
            ++StorItor)
        {
            if((*StorItor)->getType().isDerivedFrom(Animation::getClassType()))
            {
                TheLoadedAnimations->pushToAnimations(dynamic_pointer_cast<Animation>(*StorItor));
            }
            else if((*StorItor)->getType() == Node::getClassType() &&
                    dynamic_pointer_cast<Node>(*StorItor)->getParent() == NULL)
            {
                TheLoadedScene = dynamic_pointer_cast<Node>(*StorItor);
            }
        }
        TheLoadedAnimations->attachUpdateProducer(TutorialWindow);
        TheLoadedAnimations->start();

        //Make Main Scene Node
        NodeRecPtr scene = makeCoredNode<Group>();

        scene->addChild(TheLoadedScene);


        TutorialWindow->connectKeyPressed(boost::bind(keyPressed, _1,
                                                      TheLoadedAnimations.get(),
                                                      TutorialWindow.get()));

        commitChanges();

        // tell the manager what to manage
        sceneManager.setRoot  (scene);

        // show the whole scene
        sceneManager.showAll();

        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "OpenSG 18FileAnimation Window");

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

