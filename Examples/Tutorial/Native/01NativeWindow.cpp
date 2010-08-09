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

void mouseWheelMoved(MouseWheelEventDetails* const e, SimpleSceneManager *mgr )
{
    std::cout << "Mouse Wheel Moved " << e->getScrollAmount() << std::endl;
    Pnt3f Min,Max;
    mgr->getRoot()->getVolume().getBounds(Min,Max);
    Real32 Dist(Min.dist(Max));
    mgr->getNavigator()->setDistance(mgr->getNavigator()->getDistance()+(Dist*e->getUnitsToScroll()*0.05));
}

void mouseMoved(MouseEventDetails* const e, SimpleSceneManager *mgr)
{
    std::cout << "Mouse Move: " << e->getLocation().x() << ", " << e->getLocation().y() << "; delta: " << e->getDelta().x() << ", " << e->getDelta().y() << std::endl;
    mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
}

void mouseDragged(MouseEventDetails* const e, SimpleSceneManager *mgr)
{
    std::cout << "Mouse Drag Button " << e->getButton() << ": " << e->getLocation().x() << ", " << e->getLocation().y()  << "; delta: " << e->getDelta().x() << ", " << e->getDelta().y() << std::endl;    
    mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
}

void mouseClicked(MouseEventDetails* const e)
{
    std::cout << "Button " << e->getButton() << " Clicked" << std::endl;
}

void mouseEntered(MouseEventDetails* const e)
{
    std::cout << "Mouse Entered" << std::endl;
}

void mouseExited(MouseEventDetails* const e)
{
    std::cout << "Mouse Exited" << std::endl;
}

void mousePressed(MouseEventDetails* const e, SimpleSceneManager *mgr)
{
    std::cout << "Button " << e->getButton() << " Pressed" << std::endl;
    mgr->mouseButtonPress(e->getButton(), e->getLocation().x(), e->getLocation().y());
}

void mouseReleased(MouseEventDetails* const e, SimpleSceneManager *mgr)
{
    std::cout << "Button " << e->getButton() << " Released" << std::endl;
    mgr->mouseButtonRelease(e->getButton(), e->getLocation().x(), e->getLocation().y());
}

void keyPressed( KeyEventDetails* const e)
{
    WindowEventProducer* TheWindow(dynamic_cast<WindowEventProducer*>(e->getSource()));
    std::cout << "Key: " << e->getKey() << " with char value: " << e->getKeyChar()<< " Pressed. Modifiers: " << e->getModifiers() << std::endl;
    switch(e->getKey()){
        case KeyEventDetails::KEY_ESCAPE:
            TheWindow->closeWindow();
            break;
        case KeyEventDetails::KEY_P:
            //Center
            TheWindow->setPosition((TheWindow->getDesktopSize() - TheWindow->getSize()) *0.5);
            break;
        case KeyEventDetails::KEY_R:
            TheWindow->setSize(Vec2us(TheWindow->getDesktopSize() * 0.85f));
            break;
        case KeyEventDetails::KEY_F:
            TheWindow->setFullscreen(!TheWindow->getFullscreen());
            break;
        case KeyEventDetails::KEY_G:
            TheWindow->setFullscreen(false);
            break;
        case KeyEventDetails::KEY_S:
            TheWindow->setVisible(true);
            break;
        case KeyEventDetails::KEY_H:
            TheWindow->setVisible(false);
            break;
        case KeyEventDetails::KEY_I:
            TheWindow->setIconify(true);
            break;
        case KeyEventDetails::KEY_D:
            TheWindow->setIconify(false);
            break;
             
        case KeyEventDetails::KEY_K:
            TheWindow->setFocused(true);
            break;
        case KeyEventDetails::KEY_J:
            TheWindow->setFocused(false);
            break;
        case KeyEventDetails::KEY_C:
            TheWindow->setShowCursor(!TheWindow->getShowCursor());
            break;
        case KeyEventDetails::KEY_1:
            TheWindow->putClipboard(std::string("From OpenSGToolbox"));
            break;
        case KeyEventDetails::KEY_2:
            std::cout << TheWindow->getClipboard() << std::endl;
            break;
        case KeyEventDetails::KEY_M:
            std::cout << TheWindow->getMousePosition() << std::endl;
            break;
        default:
            break;
    }
	if(e->getKey() == KeyEventDetails::KEY_L &&
		e->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
	{
        TheWindow->setShowCursor(false);
        TheWindow->setAttachMouseToCursor(false);
    }
	if(e->getKey() == KeyEventDetails::KEY_U &&
		e->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
	{
        TheWindow->setShowCursor(true);
        TheWindow->setAttachMouseToCursor(true);
    }
	if(e->getKey() == KeyEventDetails::KEY_O &&
		e->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
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
	if(e->getKey() == KeyEventDetails::KEY_S &&
		e->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
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

void keyReleased( KeyEventDetails* const e)
{
    std::cout << "Key: " << e->getKey() << " with char value: " << e->getKeyChar() << " Released. Modifiers: " << e->getModifiers()  << std::endl;
}

void keyTyped( KeyEventDetails* const e)
{
    std::cout << "Key: " << e->getKey() << " with char value: " << e->getKeyChar() << " Typed. Modifiers: " << e->getModifiers() << std::endl;
}

void windowOpened( WindowEventDetails* const e)
{
   std::cout << "Window Opened" << std::endl;
}

void windowClosing( WindowEventDetails* const e)
{
   std::cout << "Window Closing" << std::endl;
}

void windowClosed( WindowEventDetails* const e)
{
   std::cout << "Window Closed" << std::endl;
}

void windowIconified( WindowEventDetails* const e)
{
   std::cout << "Window Iconified" << std::endl;
}

void windowDeiconified( WindowEventDetails* const e)
{
   std::cout << "Window Deiconified" << std::endl;
}

void windowActivated( WindowEventDetails* const e)
{
   std::cout << "Window Activated" << std::endl;
}

void windowDeactivated( WindowEventDetails* const e)
{
   std::cout << "Window Deactivated" << std::endl;
}

void windowEntered( WindowEventDetails* const e)
{
   std::cout << "Window Entered" << std::endl;
}

void windowExited( WindowEventDetails* const e)
{
   std::cout << "Window Exited" << std::endl;
}

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

        //Attach to the Mouse Events
        TheWindow->connectMouseClicked(boost::bind(mouseClicked, _1));
        TheWindow->connectMousePressed(boost::bind(mousePressed, _1, &sceneManager));
        TheWindow->connectMouseReleased(boost::bind(mouseReleased, _1, &sceneManager));
        TheWindow->connectMouseMoved(boost::bind(mouseMoved, _1, &sceneManager));
        TheWindow->connectMouseDragged(boost::bind(mouseDragged, _1, &sceneManager));
        TheWindow->connectMouseEntered(boost::bind(mouseEntered, _1));
        TheWindow->connectMouseExited(boost::bind(mouseExited, _1));
        
        TheWindow->connectMouseWheelMoved(boost::bind(mouseWheelMoved, _1, &sceneManager));

        //Attach to the Key Events
        TheWindow->connectKeyPressed(boost::bind(keyPressed, _1));
        TheWindow->connectKeyReleased(boost::bind(keyReleased, _1));
        TheWindow->connectKeyTyped(boost::bind(keyTyped, _1));

        //Attach to the Window Events
        TheWindow->connectWindowOpened(boost::bind(windowOpened, _1));
        TheWindow->connectWindowClosing(boost::bind(windowClosing, _1));
        TheWindow->connectWindowClosed(boost::bind(windowClosed, _1));
        TheWindow->connectWindowIconified(boost::bind(windowIconified, _1));
        TheWindow->connectWindowDeiconified(boost::bind(windowDeiconified, _1));
        TheWindow->connectWindowActivated(boost::bind(windowActivated, _1));
        TheWindow->connectWindowDeactivated(boost::bind(windowDeactivated, _1));
        TheWindow->connectWindowEntered(boost::bind(windowEntered, _1));
        TheWindow->connectWindowExited(boost::bind(windowExited, _1));

        // show the whole scene
        sceneManager.showAll();

        // show statistics
        sceneManager.setStatistics(true);


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


