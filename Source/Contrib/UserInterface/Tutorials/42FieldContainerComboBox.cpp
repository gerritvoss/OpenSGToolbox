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


//UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGLayers.h>

#include <OpenSG/UserInterface/OSGComboBox.h>
#include <OpenSG/UserInterface/OSGDerivedFieldContainerComboBoxModel.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;

// forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// Create a class to allow for the use of the Escape
// key to exit
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventPtr e)
   {
	   if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
            TutorialWindowEventProducer->closeWindow();
       }
   }

   virtual void keyReleased(const KeyEventPtr e)
   {
   }

   virtual void keyTyped(const KeyEventPtr e)
   {
   }
};


// Initialize WIN32 & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();
    
    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    TutorialKeyListener TheKeyListener;
    TutorialWindowEventProducer->addKeyListener(&TheKeyListener);

    // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Main Scene Node and add the Torus
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
        scene->addChild(TorusGeometryNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

	// Create the Graphics
	GraphicsPtr graphics = osg::Graphics2D::create();

	// Initialize the LookAndFeelManager to enable default settings
	LookAndFeelManager::the()->getLookAndFeel()->init();
   
	/******************************************************
            
			Create the DerivedFieldContainerComboBoxModel and
			add Elements to it (derived FieldContainerTypes
            ).  These will be the data
			values shown in the ComboBox.

    ******************************************************/   

    DerivedFieldContainerComboBoxModelPtr ExampleComboBoxModel = DerivedFieldContainerComboBoxModel::create();
    beginEditCP(ExampleComboBoxModel, DerivedFieldContainerComboBoxModel::DerivedFieldContainerTypesFieldMask);
        ExampleComboBoxModel->getDerivedFieldContainerTypes().push_back(std::string(Component::getClassType().getCName()));
    endEditCP(ExampleComboBoxModel, DerivedFieldContainerComboBoxModel::DerivedFieldContainerTypesFieldMask);

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
	ComboBoxPtr ExampleUneditableComboBox = ComboBox::create();

	// Set it to be uneditable
	beginEditCP(ExampleUneditableComboBox, ComboBox::EditableFieldMask | ComboBox::ModelFieldMask);
		ExampleUneditableComboBox->setEditable(false);
		ExampleUneditableComboBox->setModel(ExampleComboBoxModel);
	endEditCP(ExampleUneditableComboBox, ComboBox::EditableFieldMask | ComboBox::ModelFieldMask);

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
	
	LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().push_back(ExampleUneditableComboBox);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
    endEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);

	//Create the Drawing Surface
	UIDrawingSurfacePtr TutorialDrawingSurface = UIDrawingSurface::create();
	beginEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
		TutorialDrawingSurface->setGraphics(graphics);
	    TutorialDrawingSurface->setEventProducer(TutorialWindowEventProducer);
    endEditCP  (TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
	
	TutorialDrawingSurface->openWindow(MainInternalWindow);

	// Create the UI Foreground Object
	UIForegroundPtr foreground = osg::UIForeground::create();

	beginEditCP(foreground, UIForeground::DrawingSurfaceFieldMask);
	    foreground->setDrawingSurface(TutorialDrawingSurface);
    endEditCP  (foreground, UIForeground::DrawingSurfaceFieldMask);


    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the manager what to manage
    mgr->setWindow(MainWindow);
    mgr->setRoot(scene);

	// Add the UI Foreground Object to the Scene
	ViewportPtr viewport = mgr->getWindow()->getPort(0);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);
		viewport->getForegrounds().push_back(foreground);
    beginEditCP(viewport, Viewport::ForegroundsFieldMask);

    // Show the whole scene
    mgr->showAll();

    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "01RubberBandCamera");

    //Enter main Loop
    TutorialWindowEventProducer->mainLoop();

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
