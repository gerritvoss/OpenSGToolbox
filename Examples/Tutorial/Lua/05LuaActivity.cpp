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

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

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
   }

   virtual void keyReleased(const KeyEventUnrecPtr e)
   {
   }

   virtual void keyTyped(const KeyEventUnrecPtr e)
   {
   }
};

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    {
        // Set up Window
        TutorialWindow = createNativeWindow();
        TutorialWindow->initWindow();

        TutorialWindow->setDisplayCallback(display);
        TutorialWindow->setReshapeCallback(reshape);

        TutorialKeyListener TheKeyListener;
        TutorialWindow->addKeyListener(&TheKeyListener);
        
        //Make the Lua Activity
        LuaActivityRefPtr TheLuaActivity = LuaActivity::create();
        std::string LuaCode = 
            "eventFuncTable = {}\n"
            "\n"
            "function eventFuncTable.handleEvent(Event, EventID)\n"
            "    print(\"Source:  \", Event:getFieldValue(\"Source\"))\n"
            "    print(\"TimeStamp:  \", Event:getFieldValue(\"TimeStamp\"))\n"
            "    print(\"Button:  \", Event:getFieldValue(\"Button\"))\n"
            "    print(\"Position:  \", Event:getFieldValue(\"Location\"):x(), \", \", Event:getFieldValue(\"Location\"):y())\n"
            "end";
        TheLuaActivity->setCode(LuaCode);
        TheLuaActivity->setEntryFunction("eventFuncTable.handleEvent");

        TutorialWindow->attachActivity(TheLuaActivity, WindowEventProducer::MousePressedMethodId);
        //TutorialWindow->attachActivity(TheLuaActivity, WindowEventProducer::KeyTypedMethodId);

        // Make Torus Node (creates Torus in background of scene)
        NodeRefPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);
        setName(TorusGeometryNode,"TorusGeometryNode");

        // Make Main Scene Node and add the Torus
        NodeRefPtr scene = OSG::Node::create();
            scene->setCore(OSG::Group::create());
            scene->addChild(TorusGeometryNode);
        setName(scene,"Scene Node");

        //Scene Background
        GradientBackgroundRefPtr SceneBackground = GradientBackground::create();
        SceneBackground->addLine(Color3f(0.0,0.0,0.0),0.0);
        setName(SceneBackground,"Scene Background");

        // Create the SimpleSceneManager helper
        mgr = new SimpleSceneManager;

        // Tell the Manager what to manage
        mgr->setWindow(TutorialWindow);
        mgr->setRoot(scene);

        // Add the UI Foreground Object to the Scene
        ViewportRefPtr TutorialViewport = mgr->getWindow()->getPort(0);
            TutorialViewport->setBackground(SceneBackground);

        // Show the whole Scene
        mgr->showAll();


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
void display(void)
{
    mgr->redraw();
}

// React to size changes
void reshape(Vec2f Size)
{
    mgr->resize(Size.x(), Size.y());
}

