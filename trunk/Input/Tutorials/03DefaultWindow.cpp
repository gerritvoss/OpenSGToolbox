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

bool ExitMainLoop = false;

// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

class TutorialMouseWheelListener : public MouseWheelListener
{
    /*=========================  PUBLIC  ===============================*/
  public:
  
    virtual void mouseWheelMoved(const MouseWheelEvent& e)
    {
       std::cout << "Mouse Wheel Moved " << e.getScrollAmount() << std::endl;
    }
};

class TutorialMouseMotionListener : public osg::MouseMotionListener
{
    virtual void mouseMoved(const MouseEvent& e)
    {
        std::cout << "Mouse Move: " << e.getLocation().x() << ", " << e.getLocation().y() << std::endl;
    }

    virtual void mouseDragged(const MouseEvent& e)
    {
        std::cout << "Mouse Drag Button " << e.getButton() << ": " << e.getLocation().x() << ", " << e.getLocation().y() << std::endl;    
    }
};

class TutorialMouseListener : public osg::MouseListener
{
    /*=========================  PUBLIC  ===============================*/
  public:
  
    virtual void mouseClicked(const MouseEvent& e)
    {
        std::cout << "Button " << e.getButton() << " Clicked" << std::endl;
    }
    virtual void mouseEntered(const MouseEvent& e)
    {
        std::cout << "Mouse Entered" << std::endl;
    }
    virtual void mouseExited(const MouseEvent& e)
    {
        std::cout << "Mouse Exited" << std::endl;
    }
    virtual void mousePressed(const MouseEvent& e)
    {
        std::cout << "Button " << e.getButton() << " Pressed" << std::endl;
    }
    virtual void mouseReleased(const MouseEvent& e)
    {
        std::cout << "Button " << e.getButton() << " Released" << std::endl;
    }
};

class TutorialKeyListener : public KeyListener
{
   /*=========================  PUBLIC  ===============================*/
public:

   virtual void keyPressed(const KeyEvent& e)
    {
        std::cout << "Key: " << e.getKey() << " with char value: " << e.getKeyChar()<< " Pressed" << std::endl;
        switch(e.getKey()){
            case KeyEvent::KEY_ESCAPE:
                TheWindowEventProducer->closeWindow();
                break;
            case KeyEvent::KEY_P:
                TheWindowEventProducer->setPosition(Pnt2s(50,50));
                break;
            case KeyEvent::KEY_R:
                TheWindowEventProducer->setSize(Vec2us(300,300));
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
            case KeyEvent::KEY_L:
                TheWindowEventProducer->setFocused(false);
                break;
            case KeyEvent::KEY_C:
                TheWindowEventProducer->setShowCursor(!TheWindowEventProducer->getShowCursor());
                break;
            case KeyEvent::KEY_M:
                std::cout << TheWindowEventProducer->getMousePosition() << std::endl;
                break;
            default:
                break;
        }
		if(e.getKey() == KeyEvent::KEY_O &&
			e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
		{
            std::vector<WindowEventProducer::FileDialogFilter> Filters;
            Filters.push_back(WindowEventProducer::FileDialogFilter("Some File Type","*.CPP"));
            Filters.push_back(WindowEventProducer::FileDialogFilter("All","*.*"));

			std::vector<Path> FilesToOpen;
			FilesToOpen = WindowEventProducer::Ptr::dcast(e.getSource())->openFileDialog("Open A File, Yo?",
				Filters,
				Path(".."),
				false);

            std::cout << "Files to Open: "<< std::endl;
            for(std::vector<Path>::iterator Itor(FilesToOpen.begin()) ; Itor != FilesToOpen.end(); ++Itor)
            {
                std::cout << Itor->string() << std::endl;
            }
		}
		if(e.getKey() == KeyEvent::KEY_S &&
			e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
		{
			std::vector<WindowEventProducer::FileDialogFilter> Filters;
            Filters.push_back(WindowEventProducer::FileDialogFilter("Some File Type","*.CPP"));
            Filters.push_back(WindowEventProducer::FileDialogFilter("All","*.*"));

			Path SavePath = WindowEventProducer::Ptr::dcast(e.getSource())->saveFileDialog("Save A File, Yo?",
				Filters,
				Path(),
				Path(".."),
				true);
            
            std::cout << "File to Save: " << SavePath.string() << std::endl;
		}
    }
    virtual void keyReleased(const KeyEvent& e)
    {
        std::cout << "Key: " << e.getKey() << " with char value: " << e.getKeyChar() << " Released" << std::endl;
    }
    virtual void keyTyped(const KeyEvent& e)
    {
        std::cout << "Key: " << e.getKey() << " with char value: " << e.getKeyChar() << " Typed" << std::endl;
    }
};

class TutorialWindowListener : public WindowListener
{
    /*=========================  PUBLIC  ===============================*/
  public:
  
    virtual void windowOpened(const WindowEvent& e)
    {
       std::cout << "Window Opened" << std::endl;
    }

    virtual void windowClosing(const WindowEvent& e)
    {
       std::cout << "Window Closing" << std::endl;
    }

    virtual void windowClosed(const WindowEvent& e)
    {
       std::cout << "Window Closed" << std::endl;
	   ExitMainLoop = true;
    }

    virtual void windowIconified(const WindowEvent& e)
    {
       std::cout << "Window Iconified" << std::endl;
    }

    virtual void windowDeiconified(const WindowEvent& e)
    {
       std::cout << "Window Deiconified" << std::endl;
    }

    virtual void windowActivated(const WindowEvent& e)
    {
       std::cout << "Window Activated" << std::endl;
    }

    virtual void windowDeactivated(const WindowEvent& e)
    {
       std::cout << "Window Deactivated" << std::endl;
    }

    virtual void windowEntered(const WindowEvent& e)
    {
       std::cout << "Window Entered" << std::endl;
    }

    virtual void windowExited(const WindowEvent& e)
    {
       std::cout << "Window Exited" << std::endl;
    }

};

// Initialize WIN32 & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);
    
    TheWindowEventProducer = createDefaultWindowEventProducer();
    TheWindowEventProducer->initWindow();

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
    

    // create the scene
    NodePtr scene = makeTorus(.5, 2, 16, 16);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(TheWindowEventProducer->getWindow() );
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();

    TheWindowEventProducer->openWindow(Pnt2s(0,0),
                        Vec2s(1280,1024),
                        //Vec2f(1920,1200),
                        "Default Window");

    while(!ExitMainLoop)
    {
        TheWindowEventProducer->update();
        TheWindowEventProducer->draw();
    }

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


