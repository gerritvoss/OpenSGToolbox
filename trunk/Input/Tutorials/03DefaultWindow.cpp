// OpenSG Tutorial Example: Hello World
//
// Minimalistic OpenSG program
// 
// This is the shortest useful OpenSG program 
// (if you remove all the comments ;)
//
// It shows how to use OpenSG together with WIN32 to create a little
// interactive scene viewer.
//

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
#include <OpenSG/Input/OSGWindowUtils.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

WindowEventProducerPtr TheWindowEventProducer;
EventConnection MouseEventConnection;

// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

class TutorialMouseWheelListener : public MouseWheelListener
{
    /*=========================  PUBLIC  ===============================*/
  public:
  
    virtual void mouseWheelMoved(const MouseWheelEventPtr e)
    {
       std::cout << "Mouse Wheel Moved " << e->getScrollAmount() << std::endl;
    }
};

class TutorialMouseMotionListener : public osg::MouseMotionListener
{
    virtual void mouseMoved(const MouseEventPtr e)
    {
        std::cout << "Mouse Move: " << e->getLocation().x() << ", " << e->getLocation().y() << "; delta: " << e->getDelta().x() << ", " << e->getDelta().y() << std::endl;
    }

    virtual void mouseDragged(const MouseEventPtr e)
    {
        std::cout << "Mouse Drag Button " << e->getButton() << ": " << e->getLocation().x() << ", " << e->getLocation().y()  << "; delta: " << e->getDelta().x() << ", " << e->getDelta().y() << std::endl;    
    }
};

class TutorialMouseListener : public osg::MouseListener
{
    /*=========================  PUBLIC  ===============================*/
  public:
  
    virtual void mouseClicked(const MouseEventPtr e)
    {
        std::cout << "Button " << e->getButton() << " Clicked" << std::endl;
    }
    virtual void mouseEntered(const MouseEventPtr e)
    {
        std::cout << "Mouse Entered" << std::endl;
    }
    virtual void mouseExited(const MouseEventPtr e)
    {
        std::cout << "Mouse Exited" << std::endl;
    }
    virtual void mousePressed(const MouseEventPtr e)
    {
        std::cout << "Button " << e->getButton() << " Pressed" << std::endl;
    }
    virtual void mouseReleased(const MouseEventPtr e)
    {
        std::cout << "Button " << e->getButton() << " Released" << std::endl;
    }
};

class TutorialKeyListener : public KeyListener
{
   /*=========================  PUBLIC  ===============================*/
public:

   virtual void keyPressed(const KeyEventPtr e)
    {
        std::cout << "Key: " << e->getKey() << " with char value: " << e->getKeyChar()<< " Pressed. Modifiers: " << e->getModifiers() << std::endl;
        switch(e->getKey()){
            case KeyEvent::KEY_ESCAPE:
                TheWindowEventProducer->closeWindow();
                break;
            case KeyEvent::KEY_P:
                //Center
                TheWindowEventProducer->setPosition((TheWindowEventProducer->getDesktopSize() - TheWindowEventProducer->getSize()) *0.5);
                break;
            case KeyEvent::KEY_R:
                TheWindowEventProducer->setSize(TheWindowEventProducer->getDesktopSize() * 0.85f);
                break;
            case KeyEvent::KEY_F:
                TheWindowEventProducer->setFullscreen(!TheWindowEventProducer->getFullscreen());
                break;
            case KeyEvent::KEY_G:
                TheWindowEventProducer->setFullscreen(false);
                break;
            case KeyEvent::KEY_S:
                TheWindowEventProducer->setVisible(true);
                break;
            case KeyEvent::KEY_H:
                TheWindowEventProducer->setVisible(false);
                break;
            case KeyEvent::KEY_I:
                TheWindowEventProducer->setIconify(true);
                break;
            case KeyEvent::KEY_D:
                TheWindowEventProducer->setIconify(false);
                break;
                 
            case KeyEvent::KEY_K:
                TheWindowEventProducer->setFocused(true);
                break;
            case KeyEvent::KEY_J:
                TheWindowEventProducer->setFocused(false);
                break;
            case KeyEvent::KEY_C:
                TheWindowEventProducer->setShowCursor(!TheWindowEventProducer->getShowCursor());
                break;
            case KeyEvent::KEY_1:
                TheWindowEventProducer->putClipboard(std::string("From OpenSGToolbox"));
                break;
            case KeyEvent::KEY_2:
                std::cout << TheWindowEventProducer->getClipboard() << std::endl;
                break;
            case KeyEvent::KEY_M:
                std::cout << TheWindowEventProducer->getMousePosition() << std::endl;
                break;
            default:
                break;
        }
		if(e->getKey() == KeyEvent::KEY_L &&
			e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
		{
            TheWindowEventProducer->setShowCursor(false);
            TheWindowEventProducer->setAttachMouseToCursor(false);
        }
		if(e->getKey() == KeyEvent::KEY_U &&
			e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
		{
            TheWindowEventProducer->setShowCursor(true);
            TheWindowEventProducer->setAttachMouseToCursor(true);
        }
		if(e->getKey() == KeyEvent::KEY_O &&
			e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
		{
            std::vector<WindowEventProducer::FileDialogFilter> Filters;
            Filters.push_back(WindowEventProducer::FileDialogFilter("Some File Type","cpp"));
            Filters.push_back(WindowEventProducer::FileDialogFilter("All","*"));

			std::vector<Path> FilesToOpen;
			FilesToOpen = WindowEventProducer::Ptr::dcast(e->getSource())->openFileDialog("Open A File, Yo?",
				Filters,
				Path(".."),
				true);

            std::cout << "Files to Open: "<< std::endl;
            for(std::vector<Path>::iterator Itor(FilesToOpen.begin()) ; Itor != FilesToOpen.end(); ++Itor)
            {
                std::cout << Itor->string() << std::endl;
            }
		}
		if(e->getKey() == KeyEvent::KEY_S &&
			e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
		{
			std::vector<WindowEventProducer::FileDialogFilter> Filters;
            Filters.push_back(WindowEventProducer::FileDialogFilter("Some File Type","cpp"));
            Filters.push_back(WindowEventProducer::FileDialogFilter("All","*"));

			Path SavePath = WindowEventProducer::Ptr::dcast(e->getSource())->saveFileDialog("Save A File, Yo?",
				Filters,
				std::string("NewCodeFile.cpp"),
				Path(".."),
				true);
            
            std::cout << "File to Save: " << SavePath.string() << std::endl;
		}
    }
    virtual void keyReleased(const KeyEventPtr e)
    {
        std::cout << "Key: " << e->getKey() << " with char value: " << e->getKeyChar() << " Released. Modifiers: " << e->getModifiers()  << std::endl;
    }
    virtual void keyTyped(const KeyEventPtr e)
    {
        std::cout << "Key: " << e->getKey() << " with char value: " << e->getKeyChar() << " Typed. Modifiers: " << e->getModifiers() << std::endl;
    }
};

class TutorialWindowListener : public WindowListener
{
    /*=========================  PUBLIC  ===============================*/
  public:
  
    virtual void windowOpened(const WindowEventPtr e)
    {
       std::cout << "Window Opened" << std::endl;
    }

    virtual void windowClosing(const WindowEventPtr e)
    {
       std::cout << "Window Closing" << std::endl;
    }

    virtual void windowClosed(const WindowEventPtr e)
    {
       std::cout << "Window Closed" << std::endl;
    }

    virtual void windowIconified(const WindowEventPtr e)
    {
       std::cout << "Window Iconified" << std::endl;
    }

    virtual void windowDeiconified(const WindowEventPtr e)
    {
       std::cout << "Window Deiconified" << std::endl;
    }

    virtual void windowActivated(const WindowEventPtr e)
    {
       std::cout << "Window Activated" << std::endl;
    }

    virtual void windowDeactivated(const WindowEventPtr e)
    {
       std::cout << "Window Deactivated" << std::endl;
    }

    virtual void windowEntered(const WindowEventPtr e)
    {
       std::cout << "Window Entered" << std::endl;
    }

    virtual void windowExited(const WindowEventPtr e)
    {
       std::cout << "Window Exited" << std::endl;
    }

};

// Initialize WIN32 & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // create the scene
    NodePtr scene = makeTorus(.5, 2, 16, 16);

    //Create a Window object
    TheWindowEventProducer = createDefaultWindowEventProducer();
    //Apply window settings
	beginEditCP(TheWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);
		TheWindowEventProducer->setUseCallbackForDraw(true);
		TheWindowEventProducer->setUseCallbackForReshape(true);
        //TheWindowEventProducer->setFullscreen(true);
	endEditCP(TheWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);
    
    TheWindowEventProducer->setDisplayCallback(display);
    TheWindowEventProducer->setReshapeCallback(reshape);
    
    //Attach Mouse Listener
    TutorialMouseListener TheTutorialMouseListener;
    MouseEventConnection = TheWindowEventProducer->addMouseListener(&TheTutorialMouseListener);
    //Attach Mouse Wheel Listener
    TutorialMouseWheelListener TheTutorialMouseWheelListener;
    TheWindowEventProducer->addMouseWheelListener(&TheTutorialMouseWheelListener);
    //Attach Key Listener
    TutorialKeyListener TheTutorialKeyListener;
    TheWindowEventProducer->addKeyListener(&TheTutorialKeyListener);
    //Attach Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TheWindowEventProducer->addWindowListener(&TheTutorialWindowListener);
    //Attach MouseMotion Listener
    TutorialMouseMotionListener TheTutorialMouseMotionListener;
    TheWindowEventProducer->addMouseMotionListener(&TheTutorialMouseMotionListener);
    
    //Initialize Window
    TheWindowEventProducer->initWindow();
    
    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(TheWindowEventProducer->getWindow() );
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TheWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TheWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TheWindowEventProducer->openWindow(WinPos,
                        WinSize,
                        "03 Default Window");

    //Enter main loop
    TheWindowEventProducer->mainLoop();

    osgExit();
    return 0;
}

//
// callback functions
//

// redraw the window
void display(void)
{
    mgr->redraw();
}

// react to size changes
void reshape(Vec2f Size)
{
    mgr->resize(Size.x(), Size.y());
}


