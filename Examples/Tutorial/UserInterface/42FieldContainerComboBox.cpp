// OpenSG Tutorial Example: Creating a Button Component
//
// This tutorial explains how to edit the basic features of
// a Button and a ToggleButtoncreated in the OSG User 
// Interface library.
// 
// Includes: Button PreferredSize, MaximumSize, MinimumSize, Font,
// Text,and adding a Button to a Scene.  Also note that clicking
// the Button causes it to appear pressed


// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// Methods to create simple geometry: boxes, spheres, tori etc.
#include "OSGSimpleGeometry.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"

// the general scene file loading handler
#include "OSGSceneFileHandler.h"

//Input
#include "OSGWindowUtils.h"


//UserInterface Headers
#include "OSGUIForeground.h"
#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"
#include "OSGGraphics2D.h"
#include "OSGFlowLayout.h"
#include "OSGLookAndFeelManager.h"
#include "OSGLayers.h"

#include "OSGComboBox.h"
#include "OSGDerivedFieldContainerComboBoxModel.h"

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerRefPtr TutorialWindow;

// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// Create a class to allow for the use of the Escape
// key to exit
class TutorialKeyListener : public KeyListener
{
  public:

    virtual void keyPressed(const KeyEventUnrecPtr e)
    {
        if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
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


// Initialize WIN32 & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindow = createNativeWindow();
    TutorialWindow->initWindow();

    TutorialWindow->setDisplayCallback(display);
    TutorialWindow->setReshapeCallback(reshape);

    TutorialKeyListener TheKeyListener;
    TutorialWindow->addKeyListener(&TheKeyListener);

    // Make Torus Node (creates Torus in background of scene)
    NodeRefPtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Main Scene Node and add the Torus
    NodeRefPtr scene = OSG::Node::create();
    scene->setCore(OSG::Group::create());
    scene->addChild(TorusGeometryNode);

    // Create the Graphics
    GraphicsRefPtr graphics = OSG::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

    /******************************************************

      Create the DerivedFieldContainerComboBoxModel and
      add Elements to it (derived FieldContainerTypes
      ).  These will be the data
      values shown in the ComboBox.

     ******************************************************/   

    DerivedFieldContainerComboBoxModelRefPtr ExampleComboBoxModel = DerivedFieldContainerComboBoxModel::create();
    ExampleComboBoxModel->editMFDerivedFieldContainerTypes()->push_back(std::string(Component::getClassType().getCName()));

    /******************************************************

      Create an editable ComboBox.  A ComboBox 
      has a Model just like various other 
      Components.  

     ******************************************************/   

    //Create the ComboBox
    /******************************************************

      Create a non-editable ComboBox.  

      -setEditable(bool): Determine whether
      the user can type in the ComboBox
      or if it is uneditable.  In this
      case, it is set to false.

      When creating a non-editable ComboBox,
      a Renderer must also be assigned.  For
      editable ComboBoxes, the ComboBox
      automatically shows its text due to the
      nature of the ComboBox.  However, when
      uneditable, this aspect of the ComboBox
      is disabled, and so to display the 
      selection, a renderer must be created and
      assigned to the ComboBox.

Note: as with Sliders and ScrollBars,
having the same Model assigned causes
the ComboBoxes to be tied together.

     ******************************************************/   
    // Create another ComboBox
    ComboBoxRefPtr ExampleUneditableComboBox = ComboBox::create();

    // Set it to be uneditable
    ExampleUneditableComboBox->setEditable(false);
    ExampleUneditableComboBox->setModel(ExampleComboBoxModel);

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerRefPtr MainInternalWindowBackground = OSG::ColorLayer::create();
    MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));

    LayoutRefPtr MainInternalWindowLayout = OSG::FlowLayout::create();

    InternalWindowRefPtr MainInternalWindow = OSG::InternalWindow::create();
    MainInternalWindow->pushToChildren(ExampleUneditableComboBox);
    MainInternalWindow->setLayout(MainInternalWindowLayout);
    MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
    MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
    MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
    MainInternalWindow->setDrawTitlebar(false);
    MainInternalWindow->setResizable(false);

    //Create the Drawing Surface
    UIDrawingSurfaceRefPtr TutorialDrawingSurface = UIDrawingSurface::create();
    TutorialDrawingSurface->setGraphics(graphics);
    TutorialDrawingSurface->setEventProducer(TutorialWindow);

    TutorialDrawingSurface->openWindow(MainInternalWindow);

    // Create the UI Foreground Object
    UIForegroundRefPtr foreground = OSG::UIForeground::create();

    foreground->setDrawingSurface(TutorialDrawingSurface);


    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the manager what to manage
    mgr->setWindow(TutorialWindow);
    mgr->setRoot(scene);

    // Add the UI Foreground Object to the Scene
    ViewportRefPtr viewport = mgr->getWindow()->getPort(0);
    viewport->addForeground(foreground);

    // Show the whole scene
    mgr->showAll();

    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
                               WinSize,
                               "42FieldContainerComboBox");

    //Enter main Loop
    TutorialWindow->mainLoop();

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
