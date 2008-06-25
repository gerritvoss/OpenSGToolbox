// OpenSG Tutorial Example: Creating a Checkbox Button Component
//
// This tutorial explains how to edit the basic features of
// a Checkbox Button created in the OSG User Interface library.
// 
// Includes: 
//
//Checkbox buttons are special buttons that can are toggled between active and inactive when they are selected


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
#include <OpenSG/Input/OSGWindowAdapter.h>

// The general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

// Input
#include <OpenSG/Input/OSGWindowUtils.h>

// UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGLayers.h>
#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>

#include <OpenSG/Dynamics/OSGFunctionComponent.h>
#include <OpenSG/Dynamics/OSGDataConverter.h>
#include <OpenSG/Dynamics/OSGDefaultFunctionComponentIOTabComponentGenerator.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

bool ExitApp = false;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// 12CheckboxButton Headers
#include <OpenSG/UserInterface/OSGBorders.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGUIFont.h>

class TutorialWindowListener : public WindowAdapter
{
public:
    virtual void windowClosing(const WindowEvent& e)
    {
        ExitApp = true;
    }

    virtual void windowClosed(const WindowEvent& e)
    {
        ExitApp = true;
    }
};

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEvent& e)
   {
       if(e.getKey() == KeyEvent::KEY_Q && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           ExitApp = true;
       }
   }

   virtual void keyReleased(const KeyEvent& e)
   {
   }

   virtual void keyTyped(const KeyEvent& e)
   {
   }
};

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);
    
    WindowEventProducerPtr TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

	beginEditCP(TutorialWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);
		TutorialWindowEventProducer->setUseCallbackForDraw(true);
		TutorialWindowEventProducer->setUseCallbackForReshape(true);
	endEditCP(TutorialWindowEventProducer, WindowEventProducer::UseCallbackForDrawFieldMask | WindowEventProducer::UseCallbackForReshapeFieldMask);
    
    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TutorialWindowEventProducer->addWindowListener(&TheTutorialWindowListener);
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
    GraphicsPtr TutorialGraphics = osg::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

	//Function to attach to Component
	DataConverterPtr TheVec3fConverter = DataConverter::create();
	beginEditCP(TheVec3fConverter);
		TheVec3fConverter->setToType(&FieldDataTraits<Vec3f>::getType());
	endEditCP(TheVec3fConverter);

    //Create the Function User Interface Component
    RoundedCornerLineBorderPtr FunctionComponentBorder = RoundedCornerLineBorder::create();
    beginEditCP(FunctionComponentBorder, RoundedCornerLineBorder::ColorFieldMask | RoundedCornerLineBorder::WidthFieldMask | RoundedCornerLineBorder::CornerRadiusFieldMask);
        FunctionComponentBorder->setColor(Color4f(0.0,0.0,0.0,1.0));
        FunctionComponentBorder->setWidth(1.0f);
        FunctionComponentBorder->setCornerRadius(4.0f);
    endEditCP(FunctionComponentBorder, RoundedCornerLineBorder::ColorFieldMask | RoundedCornerLineBorder::WidthFieldMask | RoundedCornerLineBorder::CornerRadiusFieldMask);

    //Create the Default Tab Generator
    DefaultFunctionComponentIOTabComponentGeneratorPtr TabGenerator = DefaultFunctionComponentIOTabComponentGenerator::create();

    FunctionComponentPtr ExampleFunctionComponent = FunctionComponent::create();
    beginEditCP(ExampleFunctionComponent, FunctionComponent::InputTabComponentGeneratorFieldMask | FunctionComponent::OutputTabComponentGeneratorFieldMask | FunctionComponent::PreferredSizeFieldMask | FunctionComponent::BordersFieldMask | FunctionComponent::FunctionFieldMask | FunctionComponent::InputTabOrientationFieldMask | FunctionComponent::OutputTabOrientationFieldMask | FunctionComponent::InputTabVerticalAlignmentFieldMask | FunctionComponent::InputTabHorizontalAlignmentFieldMask | FunctionComponent::OutputTabVerticalAlignmentFieldMask | FunctionComponent::OutputTabHorizontalAlignmentFieldMask);
        ExampleFunctionComponent->setPreferredSize(Vec2f(100.0f,100.0f));
        ExampleFunctionComponent->setBorders(FunctionComponentBorder);
		ExampleFunctionComponent->setFunction(TheVec3fConverter);
		ExampleFunctionComponent->setInputTabOrientation(FunctionComponent::VERTICAL_ORIENTATION);
		ExampleFunctionComponent->setOutputTabOrientation(FunctionComponent::VERTICAL_ORIENTATION);
		ExampleFunctionComponent->setInputTabVerticalAlignment(0.5);
		ExampleFunctionComponent->setInputTabHorizontalAlignment(0.0);
		ExampleFunctionComponent->setOutputTabVerticalAlignment(0.5);
		ExampleFunctionComponent->setOutputTabHorizontalAlignment(1.0);
        
        //Add Generators
		ExampleFunctionComponent->setInputTabComponentGenerator(TabGenerator);
		ExampleFunctionComponent->setOutputTabComponentGenerator(TabGenerator);

    endEditCP(ExampleFunctionComponent, FunctionComponent::InputTabComponentGeneratorFieldMask | FunctionComponent::OutputTabComponentGeneratorFieldMask | FunctionComponent::PreferredSizeFieldMask | FunctionComponent::BordersFieldMask | FunctionComponent::FunctionFieldMask | FunctionComponent::InputTabOrientationFieldMask | FunctionComponent::OutputTabOrientationFieldMask | FunctionComponent::InputTabVerticalAlignmentFieldMask | FunctionComponent::InputTabHorizontalAlignmentFieldMask | FunctionComponent::OutputTabVerticalAlignmentFieldMask | FunctionComponent::OutputTabHorizontalAlignmentFieldMask);
    
    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);

    LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();

    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().push_back(ExampleFunctionComponent);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
    endEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);

    // Create the Drawing Surface
    UIDrawingSurfacePtr TutorialDrawingSurface = UIDrawingSurface::create();
    beginEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindowEventProducer);
    endEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);

	TutorialDrawingSurface->openWindow(MainInternalWindow);

    // Create the UI Foreground Object
    UIForegroundPtr TutorialUIForeground = osg::UIForeground::create();

    beginEditCP(TutorialUIForeground, UIForeground::DrawingSurfaceFieldMask);
        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);
    endEditCP(TutorialUIForeground, UIForeground::DrawingSurfaceFieldMask);


    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
    mgr->setRoot(scene);

    // Add the UI Foreground Object to the Scene
    ViewportPtr TutorialViewport = mgr->getWindow()->getPort(0);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);
        TutorialViewport->getForegrounds().push_back(TutorialUIForeground);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);

    // Show the whole Scene
    mgr->showAll();

    TutorialWindowEventProducer->openWindow(Pnt2f(50,50),
                                        Vec2f(550,550),
                                        "OpenSG 10UserInterface Window");

    //Main Event Loop
    while(!ExitApp)
    {
        TutorialWindowEventProducer->update();
        TutorialWindowEventProducer->draw();
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