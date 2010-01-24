// Simple demonstration of XML file input
// Reads an XML file containing particle systems, and creates a scene with it

// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

#include "OSGSimpleSceneManager.h"
#include "OSGGroup.h"
#include "OSGWindowUtils.h"
// Input
#include "OSGKeyListener.h"

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
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE


SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

// mouse and keyboard support
class TutorialKeyListener : public KeyListener
{
  public:

    virtual void keyPressed(const KeyEventUnrecPtr e)
    {
        if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
        {
            TutorialWindow->closeWindow();
        }
        if(e->getKey() == KeyEvent::KEY_S)
        {
            mgr->setStatistics(true);
        }
        if(e->getKey() == KeyEvent::KEY_A)
        {
            mgr->setStatistics(false);
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

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindow = createNativeWindow();
    TutorialWindow->initWindow();

    TutorialWindow->setDisplayCallback(display);
    TutorialWindow->setReshapeCallback(reshape);

    //Add Key Listener
    TutorialKeyListener TheKeyListener;
    TutorialWindow->addKeyListener(&TheKeyListener);
    //Add Mouse Listeners
    TutorialMouseListener TheTutorialMouseListener;
    TutorialMouseMotionListener TheTutorialMouseMotionListener;
    TutorialWindow->addMouseListener(&TheTutorialMouseListener);
    TutorialWindow->addMouseMotionListener(&TheTutorialMouseMotionListener);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindow);
    // open window

    /* Set up complete, now performing XML import */

    Path ExecutableDirectory(argv[0]);
    ExecutableDirectory.remove_leaf();
    Path FilePath;
    if(argc > 1)
    {
        FilePath  = Path(argv[1]);
    }
    else
    {
        FilePath = Path("./Data/mayaExport1.xml");
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
            ExampleParticleSystems->attachUpdateListener(TutorialWindow);
        }
    }

    // get root node that was extracted from XML file
    if(RootNodes.size() > 0)
    {
        NodeRefPtr scene = RootNodes[0];

        // set root node
        mgr->setRoot(scene);

    }

    // Show the whole Scene
    mgr->showAll();
    mgr->setHeadlight(true);
    mgr->getCamera()->setFar(10000);

    // main loop
    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
                               WinSize,
                               "15FCFileTypeIO");

    //Enter main Loop
    TutorialWindow->mainLoop();


    osgExit();

    return 0;
}
