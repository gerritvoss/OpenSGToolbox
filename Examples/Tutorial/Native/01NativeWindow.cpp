// OpenSG Tutorial Example: Hello World
//
// Minimalistic OpenSG program
// 
// This is the shortest useful OpenSG program 
// (if you remove all the comments ;)
//
// It shows how to use OpenSG together with Native Window to create a little
// interactive scene viewer.
//

#ifdef OSG_BUILD_ACTIVE
// General OpenSG configuration, needed everywhere
#include <OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OSGSimpleGeometry.h>

// A little helper to simplify scene management and interaction
#include <OSGSimpleSceneManager.h>
#include <OSGNode.h>
#include <OSGGroup.h>
#include <OSGViewport.h>

// the general scene file loading handler
#include <OSGSceneFileHandler.h>

//Input
#include <OSGWindowUtils.h>
#include <OSGWindowEventProducer.h>
#else
// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>

// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

//Input
#include <OpenSG/OSGWindowUtils.h>
#include <OpenSG/OSGWindowEventProducer.h>
#endif

#include <boost/bind.hpp>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// forward declaration so we can have the interesting stuff upfront
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

void mouseWheelMoved(const MouseWheelEventUnrecPtr e, SimpleSceneManager *mgr )
{
    std::cout << "Mouse Wheel Moved " << e->getScrollAmount() << std::endl;
    Pnt3f Min,Max;
    mgr->getRoot()->getVolume().getBounds(Min,Max);
    Real32 Dist(Min.dist(Max));
    mgr->getNavigator()->setDistance(mgr->getNavigator()->getDistance()+(Dist*e->getUnitsToScroll()*0.05));
}

class TutorialMouseMotionListener : public MouseMotionListener
{
    virtual void mouseMoved(const MouseEventUnrecPtr e)
    {
        //std::cout << "Mouse Move: " << e->getLocation().x() << ", " << e->getLocation().y() << "; delta: " << e->getDelta().x() << ", " << e->getDelta().y() << std::endl;
        //mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
    }

    virtual void mouseDragged(const MouseEventUnrecPtr e)
    {
        //std::cout << "Mouse Drag Button " << e->getButton() << ": " << e->getLocation().x() << ", " << e->getLocation().y()  << "; delta: " << e->getDelta().x() << ", " << e->getDelta().y() << std::endl;    
        //mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
    }
};

class TutorialMouseListener : public MouseListener
{
    /*=========================  PUBLIC  ===============================*/
  public:
  
    virtual void mouseClicked(const MouseEventUnrecPtr e)
    {
        std::cout << "Button " << e->getButton() << " Clicked" << std::endl;
    }
    virtual void mouseEntered(const MouseEventUnrecPtr e)
    {
        std::cout << "Mouse Entered" << std::endl;
    }
    virtual void mouseExited(const MouseEventUnrecPtr e)
    {
        std::cout << "Mouse Exited" << std::endl;
    }
    virtual void mousePressed(const MouseEventUnrecPtr e)
    {
        std::cout << "Button " << e->getButton() << " Pressed" << std::endl;
        //mgr->mouseButtonPress(e->getButton(), e->getLocation().x(), e->getLocation().y());
    }
    virtual void mouseReleased(const MouseEventUnrecPtr e)
    {
        std::cout << "Button " << e->getButton() << " Released" << std::endl;
        //mgr->mouseButtonRelease(e->getButton(), e->getLocation().x(), e->getLocation().y());
    }
};

class TutorialKeyListener : public KeyListener
{
   /*=========================  PUBLIC  ===============================*/
public:

   virtual void keyPressed(const KeyEventUnrecPtr e)
    {
        WindowEventProducer* TheWindow(dynamic_cast<WindowEventProducer*>(e->getSource()));
        std::cout << "Key: " << e->getKey() << " with char value: " << e->getKeyChar()<< " Pressed. Modifiers: " << e->getModifiers() << std::endl;
        switch(e->getKey()){
            case KeyEvent::KEY_ESCAPE:
                TheWindow->closeWindow();
                break;
            case KeyEvent::KEY_P:
                //Center
                TheWindow->setPosition((TheWindow->getDesktopSize() - TheWindow->getSize()) *0.5);
                break;
            case KeyEvent::KEY_R:
                TheWindow->setSize(Vec2us(TheWindow->getDesktopSize() * 0.85f));
                break;
            case KeyEvent::KEY_F:
                TheWindow->setFullscreen(!TheWindow->getFullscreen());
                break;
            case KeyEvent::KEY_G:
                TheWindow->setFullscreen(false);
                break;
            case KeyEvent::KEY_S:
                TheWindow->setVisible(true);
                break;
            case KeyEvent::KEY_H:
                TheWindow->setVisible(false);
                break;
            case KeyEvent::KEY_I:
                TheWindow->setIconify(true);
                break;
            case KeyEvent::KEY_D:
                TheWindow->setIconify(false);
                break;
                 
            case KeyEvent::KEY_K:
                TheWindow->setFocused(true);
                break;
            case KeyEvent::KEY_J:
                TheWindow->setFocused(false);
                break;
            case KeyEvent::KEY_C:
                TheWindow->setShowCursor(!TheWindow->getShowCursor());
                break;
            case KeyEvent::KEY_1:
                TheWindow->putClipboard(std::string("From OpenSGToolbox"));
                break;
            case KeyEvent::KEY_2:
                std::cout << TheWindow->getClipboard() << std::endl;
                break;
            case KeyEvent::KEY_M:
                std::cout << TheWindow->getMousePosition() << std::endl;
                break;
            default:
                break;
        }
		if(e->getKey() == KeyEvent::KEY_L &&
			e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
		{
            TheWindow->setShowCursor(false);
            TheWindow->setAttachMouseToCursor(false);
        }
		if(e->getKey() == KeyEvent::KEY_U &&
			e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
		{
            TheWindow->setShowCursor(true);
            TheWindow->setAttachMouseToCursor(true);
        }
		if(e->getKey() == KeyEvent::KEY_O &&
			e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
		{
            std::vector<WindowEventProducer::FileDialogFilter> Filters;
            Filters.push_back(WindowEventProducer::FileDialogFilter("Some File Type","cpp"));
            Filters.push_back(WindowEventProducer::FileDialogFilter("All","*"));

			std::vector<BoostPath> FilesToOpen;
            FilesToOpen = dynamic_cast<WindowEventProducer*>(e->getSource())->openFileDialog("Open A File, Yo?",
                Filters,
                BoostPath(".."),
                true);

            std::cout << "Files to Open: "<< std::endl;
            for(std::vector<BoostPath>::iterator Itor(FilesToOpen.begin()) ; Itor != FilesToOpen.end(); ++Itor)
            {
                std::cout << Itor->string() << std::endl;
            }
		}
		if(e->getKey() == KeyEvent::KEY_S &&
			e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
		{
			std::vector<WindowEventProducer::FileDialogFilter> Filters;
            Filters.push_back(WindowEventProducer::FileDialogFilter("Some File Type","cpp"));
            Filters.push_back(WindowEventProducer::FileDialogFilter("All","*"));

            BoostPath SavePath= dynamic_cast<WindowEventProducer*>(e->getSource())->saveFileDialog("Save A File, Yo?",
                Filters,
                std::string("NewCodeFile.cpp"),
                BoostPath(".."),
                true);
            
            std::cout << "File to Save: " << SavePath.string() << std::endl;
		}
    }
    virtual void keyReleased(const KeyEventUnrecPtr e)
    {
        std::cout << "Key: " << e->getKey() << " with char value: " << e->getKeyChar() << " Released. Modifiers: " << e->getModifiers()  << std::endl;
    }
    virtual void keyTyped(const KeyEventUnrecPtr e)
    {
        std::cout << "Key: " << e->getKey() << " with char value: " << e->getKeyChar() << " Typed. Modifiers: " << e->getModifiers() << std::endl;
    }
};

class TutorialWindowListener : public WindowListener
{
    /*=========================  PUBLIC  ===============================*/
  public:
  
    virtual void windowOpened(const WindowEventUnrecPtr e)
    {
       std::cout << "Window Opened" << std::endl;
    }

    virtual void windowClosing(const WindowEventUnrecPtr e)
    {
       std::cout << "Window Closing" << std::endl;
    }

    virtual void windowClosed(const WindowEventUnrecPtr e)
    {
       std::cout << "Window Closed" << std::endl;
    }

    virtual void windowIconified(const WindowEventUnrecPtr e)
    {
       std::cout << "Window Iconified" << std::endl;
    }

    virtual void windowDeiconified(const WindowEventUnrecPtr e)
    {
       std::cout << "Window Deiconified" << std::endl;
    }

    virtual void windowActivated(const WindowEventUnrecPtr e)
    {
       std::cout << "Window Activated" << std::endl;
    }

    virtual void windowDeactivated(const WindowEventUnrecPtr e)
    {
       std::cout << "Window Deactivated" << std::endl;
    }

    virtual void windowEntered(const WindowEventUnrecPtr e)
    {
       std::cout << "Window Entered" << std::endl;
    }

    virtual void windowExited(const WindowEventUnrecPtr e)
    {
       std::cout << "Window Exited" << std::endl;
    }

};

// Initialize WIN32 & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    {
        // create the scene
        NodeRecPtr scene = makeTorus(.5, 2, 16, 16);

        //Create a Window object
        WindowEventProducerRefPtr TheWindow = createNativeWindow();

        //Apply window settings
        TheWindow->setUseCallbackForDraw(true);
        TheWindow->setUseCallbackForReshape(true);
        //TheWindow->setFullscreen(true);
        
        
        //Attach Mouse Listener
        TutorialMouseListener TheTutorialMouseListener;
        TheWindow->addMouseListener(&TheTutorialMouseListener);
        //Attach Mouse Wheel Listener
        //TheWindow->addMouseWheelListener(&TheTutorialMouseWheelListener);
        //Attach Key Listener
        TutorialKeyListener TheTutorialKeyListener;
        TheWindow->addKeyListener(&TheTutorialKeyListener);
        //Attach Window Listener
        TutorialWindowListener TheTutorialWindowListener;
        TheWindow->addWindowListener(&TheTutorialWindowListener);
        //Attach MouseMotion Listener
        TutorialMouseMotionListener TheTutorialMouseMotionListener;
        TheWindow->addMouseMotionListener(&TheTutorialMouseMotionListener);
        
        //Initialize Window
        TheWindow->initWindow();

        commitChanges();
        
        // create the SimpleSceneManager helper
        SimpleSceneManager sceneManager;
        TheWindow->setDisplayCallback(boost::bind(display, &sceneManager));
        TheWindow->setReshapeCallback(boost::bind(reshape, _1, &sceneManager));

        // tell the manager what to manage
        sceneManager.setWindow(TheWindow);
        sceneManager.setRoot  (scene);

        // show the whole scene
        sceneManager.showAll();


        //Open Window
        Vec2f WinSize(TheWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TheWindow->getDesktopSize() - WinSize) *0.5);
        TheWindow->openWindow(WinPos,
                            WinSize,
                            "01 Native Window");

        //Enter main loop
        TheWindow->mainLoop();
    }

    osgExit();
    return 0;
}

//
// callback functions
//

// redraw the window
void display(SimpleSceneManager *mgr)
{
    mgr->redraw();
}

// react to size changes
void reshape(Vec2f Size, SimpleSceneManager *mgr)
{
    mgr->resize(Size.x(), Size.y());
}


