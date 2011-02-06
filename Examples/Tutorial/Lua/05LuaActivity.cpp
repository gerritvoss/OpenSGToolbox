// OpenSG Tutorial Example: Creating a Text area to run a Lua script from
//

// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// Methods to create simple geometry: boxes, spheres, tori etc.
#include "OSGSimpleGeometry.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"
#include "OSGGradientBackground.h"
#include "OSGNameAttachment.h"

// The general scene file loading handler
#include "OSGSceneFileHandler.h"

// Input
#include "OSGWindowUtils.h"

//Lua
#include "OSGLuaActivity.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// Forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

void keyPressed(KeyEventDetails* const details)
{
    if(details->getKey() == KeyEventDetails::KEY_Q &&
       details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        dynamic_cast<WindowEventProducer*>(details->getSource())->closeWindow();
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

        TutorialWindow->connectKeyTyped(boost::bind(keyPressed, _1));

        //Make the Lua Activity
        std::string LuaButtonCode = 
            "if(not eventFuncTable) then eventFuncTable = {} end\n"
            "\n"
            "function eventFuncTable.handleButtonEvent(Event, EventID)\n"
            "    print(\"Source:  \", Event:getFieldValue(\"Source\"))\n"
            "    print(\"TimeStamp:  \", Event:getFieldValue(\"TimeStamp\"))\n"
            "    print(\"Button:  \", Event:getFieldValue(\"Button\"))\n"
            "    print(\"Position:  \", Event:getFieldValue(\"Location\"):x(), \", \", Event:getFieldValue(\"Location\"):y())\n"
            "end";

        std::string LuaKeyCode = 
            "if(not eventFuncTable) then eventFuncTable = {} end\n"
            "\n"
            "function eventFuncTable.handleKeyEvent(Event, EventID)\n"
            "    print(\"Source:  \", Event:getFieldValue(\"Source\"))\n"
            "    print(\"TimeStamp:  \", Event:getFieldValue(\"TimeStamp\"))\n"
            "    print(\"Key:  \", Event:getFieldValue(\"Key\"))\n"
            "end";
        LuaActivityRecPtr TheLuaButtonActivity = LuaActivity::create();
        TheLuaButtonActivity->setCode(LuaButtonCode);
        TheLuaButtonActivity->setEntryFunction("eventFuncTable.handleButtonEvent");

        LuaActivityRecPtr TheLuaKeyActivity = LuaActivity::create();
        TheLuaKeyActivity->setCode(LuaKeyCode);
        TheLuaKeyActivity->setEntryFunction("eventFuncTable.handleKeyEvent");

        TutorialWindow->attachActivity(WindowEventProducer::MousePressedEventId, TheLuaButtonActivity);
        TutorialWindow->attachActivity(WindowEventProducer::KeyTypedEventId, TheLuaKeyActivity);

        // Make Torus Node (creates Torus in background of scene)
        NodeRecPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);
        setName(TorusGeometryNode,"TorusGeometryNode");

        // Make Main Scene Node and add the Torus
        NodeRecPtr scene = Node::create();
        scene->setCore(Group::create());
        scene->addChild(TorusGeometryNode);
        setName(scene,"Scene Node");

        //Scene Background
        GradientBackgroundRecPtr SceneBackground = GradientBackground::create();
        SceneBackground->addLine(Color3f(0.0,0.0,0.0),0.0);
        setName(SceneBackground,"Scene Background");


        // Tell the Manager what to manage
        sceneManager.setRoot(scene);

        // Add the UI Foreground Object to the Scene
        ViewportRecPtr TutorialViewport = sceneManager.getWindow()->getPort(0);
        TutorialViewport->setBackground(SceneBackground);

        // Show the whole Scene
        sceneManager.showAll();


        //Open Window
        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "05LuaActivity");

        //Enter main Loop
        TutorialWindow->mainLoop();
        TutorialWindow = NULL;
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

