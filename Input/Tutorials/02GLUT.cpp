// OpenSG Tutorial Example: Hello World
//
// Minimalistic OpenSG program
// 
// This is the shortest useful OpenSG program 
// (if you remove all the comments ;)
//
// It shows how to use OpenSG together with GLUT to create a little
// interactive scene viewer.
//

// GLUT is used for window handling
#include <OpenSG/OSGGLUT.h>

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// The GLUT-OpenSG connection class
#include <OpenSG/OSGGLUTWindow.h>

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

// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2s Size);

class TutorialMouseListener : public osg::MouseListener
{
    /*=========================  PUBLIC  ===============================*/
  public:
  
    virtual void mouseClicked(const MouseEvent& e)
    {
       std::cout << "mouseClicked" << std::endl;
    }
    virtual void mouseEntered(const MouseEvent& e)
    {
       std::cout << "mouseEntered" << std::endl;
    }
    virtual void mouseExited(const MouseEvent& e)
    {
       std::cout << "mouseExited" << std::endl;
    }
    virtual void mousePressed(const MouseEvent& e)
    {
       std::cout << "mousePressed" << std::endl;
    }
    virtual void mouseReleased(const MouseEvent& e)
    {
       std::cout << "mouseReleased" << std::endl;
    }
};

class TutorialKeyListener : public KeyListener
{
   /*=========================  PUBLIC  ===============================*/
public:

   virtual void keyPressed(const KeyEvent& e)
    {
       std::cout << "keyPressed" << std::endl;
       switch(e.getKey()){
         case KeyEvent::KEY_ESCAPE:
            osgExit();
            exit(0);
            break;
         default:
            break;
       }
    }
   virtual void keyReleased(const KeyEvent& e)
    {
       std::cout << "keyReleased" << std::endl;
    }
   virtual void keyTyped(const KeyEvent& e)
    {
       std::cout << "keyTyped" << std::endl;
    }
};

class TutorialWindowListener : public WindowListener
{
    /*=========================  PUBLIC  ===============================*/
  public:
  
    virtual void windowOpened(const WindowEvent& e)
    {
       std::cout << "windowOpened" << std::endl;
    }

    virtual void windowClosing(const WindowEvent& e)
    {
       std::cout << "windowClosing" << std::endl;
    }

    virtual void windowClosed(const WindowEvent& e)
    {
       std::cout << "windowClosed" << std::endl;
    }

    virtual void windowIconified(const WindowEvent& e)
    {
       std::cout << "windowIconified" << std::endl;
    }

    virtual void windowDeiconified(const WindowEvent& e)
    {
       std::cout << "windowDeiconified" << std::endl;
    }

    virtual void windowActivated(const WindowEvent& e)
    {
       std::cout << "windowActivated" << std::endl;
    }

    virtual void windowDeactivated(const WindowEvent& e)
    {
       std::cout << "windowDeactivated" << std::endl;
    }

    virtual void windowEntered(const WindowEvent& e)
    {
       std::cout << "windowEntered" << std::endl;
    }

    virtual void windowExited(const WindowEvent& e)
    {
       std::cout << "windowExited" << std::endl;
    }

};

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);
    
    WindowPtr MainWindow;
    createWindow(GLUTWindow::getClassType(),
                                        Pnt2s(50,50),
                                        Vec2s(250,250),
                                        "GLUT Window",
                                        MainWindow,
                                        TheWindowEventProducer);
    
    TheWindowEventProducer->setDisplayCallback(display);
    TheWindowEventProducer->setReshapeCallback(reshape);

    //Attach Mouse Listener
    TheWindowEventProducer->addMouseListener(new TutorialMouseListener());
    //Attach Key Listener
    TheWindowEventProducer->addKeyListener(new TutorialKeyListener());
    //Attach Window Listener
    TheWindowEventProducer->addWindowListener(new TutorialWindowListener());

    // create the scene
    NodePtr scene = makeTorus(.5, 2, 16, 16);

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(MainWindow );
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();

    openWindow(TheWindowEventProducer);

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
void reshape(Vec2s Size)
{
    mgr->resize(Size.x(), Size.y());
}

