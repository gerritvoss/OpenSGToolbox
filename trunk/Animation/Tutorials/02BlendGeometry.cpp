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

// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>

// Input
#include <OpenSG/Input/OSGKeyListener.h>
#include <OpenSG/Input/OSGWindowUtils.h>

#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGGeometry.h>
#include <OpenSG/OSGGradientBackground.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGDirectionalLight.h>

#include <OpenSG/Animation/OSGBlendGeometry.h>

#include <OpenSG/Toolbox/OSGFieldContainerUtils.h>
#include <OpenSG/OSGSimpleAttachments.h>

//User Interface
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>
#include <OpenSG/UserInterface/OSGLayers.h>
#include <OpenSG/UserInterface/OSGSlider.h>
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGDefaultBoundedRangeModel.h>
#include <OpenSG/UserInterface/OSGGLViewport.h>

// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;

NodePtr BubbleBlendGeometryNode;
NodePtr BlendGeometryTransNode;
osg::BlendGeometryPtr TheBlendGeometry;

// forward declaration so we can have the interesting stuff upfront
void setupBlendGeometry(void);
NodePtr createBlendRootNode(void);
ComponentPtr createGLPanel(void);

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEvent& e)
   {
       if(e.getKey() == KeyEvent::KEY_Q && e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           TutorialWindowEventProducer->closeWindow();
       }
   }

   virtual void keyReleased(const KeyEvent& e)
   {
   }

   virtual void keyTyped(const KeyEvent& e)
   {
   }
};

class TutorialMouseListener : public MouseListener
{
  public:
    virtual void mouseClicked(const MouseEvent& e)
    {
    }
    virtual void mouseEntered(const MouseEvent& e)
    {
    }
    virtual void mouseExited(const MouseEvent& e)
    {
    }
    virtual void mousePressed(const MouseEvent& e)
    {
            mgr->mouseButtonPress(e.getButton(), e.getLocation().x(), e.getLocation().y());
    }
    virtual void mouseReleased(const MouseEvent& e)
    {
           mgr->mouseButtonRelease(e.getButton(), e.getLocation().x(), e.getLocation().y());
    }
};

class TutorialMouseMotionListener : public MouseMotionListener
{
  public:
    virtual void mouseMoved(const MouseEvent& e)
    {
            mgr->mouseMove(e.getLocation().x(), e.getLocation().y());
    }

    virtual void mouseDragged(const MouseEvent& e)
    {
            mgr->mouseMove(e.getLocation().x(), e.getLocation().y());
    }
};

class BlendAmountSliderChangeListener : public ChangeListener
{
  public:
      BlendAmountSliderChangeListener(BlendGeometryPtr TheBlendGeometry,
          UInt32 BlendAmountIndex, SliderPtr TheSlider) : _BlendGeometry(TheBlendGeometry),_BlendAmountIndex(BlendAmountIndex),_Slider(TheSlider)
      {
      }

    virtual void stateChanged(const ChangeEvent& e)
    {
        if(_Slider != NullFC && 
            _BlendGeometry != NullFC)
        {
            _BlendGeometry->setBlendAmount(_BlendAmountIndex,static_cast<Real32>(_Slider->getValue())/100.0f);
        }
    }
protected:
    BlendGeometryPtr _BlendGeometry;
    UInt32 _BlendAmountIndex;
    SliderPtr _Slider;
};

class NamedNodeFinder
{
  public:
  
    NamedNodeFinder(void) : _name(), _found() {}

    NodePtr operator() (NodePtr root, std::string name)
    {
        _name=&name;
        _found=NullFC;
        
        traverse(root, osgTypedMethodFunctor1ObjPtrCPtrRef(
                            this, 
                            &NamedNodeFinder::check));
        
        return _found;
    }
 
    static NodePtr find(NodePtr root, std::string name)
    {
        NamedNodeFinder f;      
        
        return f(root,name);
    }
   
  private:
     
    Action::ResultE check(NodePtr& node)
    {
        if(getName(node) && *_name == getName(node))
        {
            _found = node;
            return Action::Quit;
        }

        return Action::Continue;        
    }
 
    NodePtr  _found;
    std::string  *_name;
};

// Initialize OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialKeyListener TheKeyListener;
    TutorialWindowEventProducer->addKeyListener(&TheKeyListener);
    TutorialMouseListener TheTutorialMouseListener;
    TutorialMouseMotionListener TheTutorialMouseMotionListener;
    TutorialWindowEventProducer->addMouseListener(&TheTutorialMouseListener);
    TutorialWindowEventProducer->addMouseMotionListener(&TheTutorialMouseMotionListener);

    
    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
	

    NodePtr EmptyScene = osg::Node::create();
    beginEditCP(EmptyScene, Node::CoreFieldMask);
        EmptyScene->setCore(Group::create());
    endEditCP  (EmptyScene, Node::CoreFieldMask);

    mgr->setRoot(EmptyScene);

    //User Interface
    // Create the Graphics
    GraphicsPtr TutorialGraphics = osg::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

    // Create the DefaultBoundedRangeModelPtr and 
    // set its values
    DefaultBoundedRangeModelPtr XBlendGeometryRangeModel = DefaultBoundedRangeModel::create();
    XBlendGeometryRangeModel->setMinimum(-200);
    XBlendGeometryRangeModel->setMaximum(200);
    XBlendGeometryRangeModel->setValue(0);
    XBlendGeometryRangeModel->setExtent(0);
    
    //Create the slider
    LabelPtr TempLabel;
    SliderPtr XBlendGeometrySlider = Slider::create();
    beginEditCP(XBlendGeometrySlider, Slider::LabelMapFieldMask | Slider::PreferredSizeFieldMask | Slider::MajorTickSpacingFieldMask | Slider::MinorTickSpacingFieldMask | Slider::SnapToTicksFieldMask | Slider::DrawLabelsFieldMask | Slider::RangeModelFieldMask);
        TempLabel = Label::Ptr::dcast(XBlendGeometrySlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("-2.0"); endEditCP(TempLabel, Label::TextFieldMask);
        XBlendGeometrySlider->getLabelMap()[-200] = TempLabel;
        
        TempLabel = Label::Ptr::dcast(XBlendGeometrySlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("-1.0"); endEditCP(TempLabel, Label::TextFieldMask);
        XBlendGeometrySlider->getLabelMap()[-100] = TempLabel;

        TempLabel = Label::Ptr::dcast(XBlendGeometrySlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("0.0"); endEditCP(TempLabel, Label::TextFieldMask);
        XBlendGeometrySlider->getLabelMap()[0] = TempLabel;

        TempLabel = Label::Ptr::dcast(XBlendGeometrySlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("1.0"); endEditCP(TempLabel, Label::TextFieldMask);
        XBlendGeometrySlider->getLabelMap()[100] = TempLabel;

        TempLabel = Label::Ptr::dcast(XBlendGeometrySlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("2.0"); endEditCP(TempLabel, Label::TextFieldMask);
        XBlendGeometrySlider->getLabelMap()[200] = TempLabel;


        XBlendGeometrySlider->setPreferredSize(Vec2f(100, 300));
        XBlendGeometrySlider->setSnapToTicks(false);
        XBlendGeometrySlider->setMajorTickSpacing(10);
        XBlendGeometrySlider->setMinorTickSpacing(5);
        XBlendGeometrySlider->setOrientation(Slider::VERTICAL_ORIENTATION);
        XBlendGeometrySlider->setInverted(true);
        XBlendGeometrySlider->setDrawLabels(true);
        XBlendGeometrySlider->setRangeModel(XBlendGeometryRangeModel);
    endEditCP(XBlendGeometrySlider, Slider::LabelMapFieldMask | Slider::PreferredSizeFieldMask | Slider::MajorTickSpacingFieldMask | Slider::MinorTickSpacingFieldMask | Slider::SnapToTicksFieldMask | Slider::DrawLabelsFieldMask | Slider::RangeModelFieldMask);
    
    DefaultBoundedRangeModelPtr YBlendGeometryRangeModel = DefaultBoundedRangeModel::create();
    YBlendGeometryRangeModel->setMinimum(-200);
    YBlendGeometryRangeModel->setMaximum(200);
    YBlendGeometryRangeModel->setValue(0);
    YBlendGeometryRangeModel->setExtent(0);
    
    //Create the slider
    SliderPtr YBlendGeometrySlider = Slider::create();
    beginEditCP(YBlendGeometrySlider, Slider::LabelMapFieldMask | Slider::PreferredSizeFieldMask | Slider::MajorTickSpacingFieldMask | Slider::MinorTickSpacingFieldMask | Slider::SnapToTicksFieldMask | Slider::DrawLabelsFieldMask | Slider::RangeModelFieldMask);
        TempLabel = Label::Ptr::dcast(YBlendGeometrySlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("-2.0"); endEditCP(TempLabel, Label::TextFieldMask);
        YBlendGeometrySlider->getLabelMap()[-200] = TempLabel;
        
        TempLabel = Label::Ptr::dcast(YBlendGeometrySlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("-1.0"); endEditCP(TempLabel, Label::TextFieldMask);
        YBlendGeometrySlider->getLabelMap()[-100] = TempLabel;

        TempLabel = Label::Ptr::dcast(YBlendGeometrySlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("0.0"); endEditCP(TempLabel, Label::TextFieldMask);
        YBlendGeometrySlider->getLabelMap()[0] = TempLabel;

        TempLabel = Label::Ptr::dcast(YBlendGeometrySlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("1.0"); endEditCP(TempLabel, Label::TextFieldMask);
        YBlendGeometrySlider->getLabelMap()[100] = TempLabel;

        TempLabel = Label::Ptr::dcast(YBlendGeometrySlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("2.0"); endEditCP(TempLabel, Label::TextFieldMask);
        YBlendGeometrySlider->getLabelMap()[200] = TempLabel;


        YBlendGeometrySlider->setPreferredSize(Vec2f(100, 300));
        YBlendGeometrySlider->setSnapToTicks(false);
        YBlendGeometrySlider->setMajorTickSpacing(10);
        YBlendGeometrySlider->setMinorTickSpacing(5);
        YBlendGeometrySlider->setOrientation(Slider::VERTICAL_ORIENTATION);
        YBlendGeometrySlider->setInverted(true);
        YBlendGeometrySlider->setDrawLabels(true);
        YBlendGeometrySlider->setRangeModel(YBlendGeometryRangeModel);
    endEditCP(YBlendGeometrySlider, Slider::LabelMapFieldMask | Slider::PreferredSizeFieldMask | Slider::MajorTickSpacingFieldMask | Slider::MinorTickSpacingFieldMask | Slider::SnapToTicksFieldMask | Slider::DrawLabelsFieldMask | Slider::RangeModelFieldMask);
    
    DefaultBoundedRangeModelPtr ZBlendGeometryRangeModel = DefaultBoundedRangeModel::create();
    ZBlendGeometryRangeModel->setMinimum(-200);
    ZBlendGeometryRangeModel->setMaximum(200);
    ZBlendGeometryRangeModel->setValue(0);
    ZBlendGeometryRangeModel->setExtent(0);
    
    //Create the slider
    SliderPtr ZBlendGeometrySlider = Slider::create();
    beginEditCP(ZBlendGeometrySlider, Slider::LabelMapFieldMask | Slider::PreferredSizeFieldMask | Slider::MajorTickSpacingFieldMask | Slider::MinorTickSpacingFieldMask | Slider::SnapToTicksFieldMask | Slider::DrawLabelsFieldMask | Slider::RangeModelFieldMask);
        TempLabel = Label::Ptr::dcast(ZBlendGeometrySlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("-2.0"); endEditCP(TempLabel, Label::TextFieldMask);
        ZBlendGeometrySlider->getLabelMap()[-200] = TempLabel;
        
        TempLabel = Label::Ptr::dcast(ZBlendGeometrySlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("-1.0"); endEditCP(TempLabel, Label::TextFieldMask);
        ZBlendGeometrySlider->getLabelMap()[-100] = TempLabel;

        TempLabel = Label::Ptr::dcast(ZBlendGeometrySlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("0.0"); endEditCP(TempLabel, Label::TextFieldMask);
        ZBlendGeometrySlider->getLabelMap()[0] = TempLabel;

        TempLabel = Label::Ptr::dcast(ZBlendGeometrySlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("1.0"); endEditCP(TempLabel, Label::TextFieldMask);
        ZBlendGeometrySlider->getLabelMap()[100] = TempLabel;

        TempLabel = Label::Ptr::dcast(ZBlendGeometrySlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("2.0"); endEditCP(TempLabel, Label::TextFieldMask);
        ZBlendGeometrySlider->getLabelMap()[200] = TempLabel;


        ZBlendGeometrySlider->setPreferredSize(Vec2f(100, 300));
        ZBlendGeometrySlider->setSnapToTicks(false);
        ZBlendGeometrySlider->setMajorTickSpacing(10);
        ZBlendGeometrySlider->setMinorTickSpacing(5);
        ZBlendGeometrySlider->setOrientation(Slider::VERTICAL_ORIENTATION);
        ZBlendGeometrySlider->setInverted(true);
        ZBlendGeometrySlider->setDrawLabels(true);
        ZBlendGeometrySlider->setRangeModel(ZBlendGeometryRangeModel);
    endEditCP(ZBlendGeometrySlider, Slider::LabelMapFieldMask | Slider::PreferredSizeFieldMask | Slider::MajorTickSpacingFieldMask | Slider::MinorTickSpacingFieldMask | Slider::SnapToTicksFieldMask | Slider::DrawLabelsFieldMask | Slider::RangeModelFieldMask);

    // Create Background to be used with the MainFrame
    ColorLayerPtr MainFrameBackground = osg::ColorLayer::create();
    beginEditCP(MainFrameBackground, ColorLayer::ColorFieldMask);
        MainFrameBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainFrameBackground, ColorLayer::ColorFieldMask);

    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);

    LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();

    //GL Viewport
    ComponentPtr TheGLViewport = createGLPanel();
    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
       MainInternalWindow->getChildren().push_back(XBlendGeometrySlider);
       MainInternalWindow->getChildren().push_back(YBlendGeometrySlider);
       MainInternalWindow->getChildren().push_back(ZBlendGeometrySlider);
       MainInternalWindow->getChildren().push_back(TheGLViewport);
       MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(0.5f,0.5f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(1.0f,1.0f));
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

    ViewportPtr TutorialViewport = mgr->getWindow()->getPort(0);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);
        TutorialViewport->getForegrounds().push_back(TutorialUIForeground);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);

    //Attach the Slider Listeners
    BlendAmountSliderChangeListener XBlendSliderListener(TheBlendGeometry, 0, XBlendGeometrySlider);
    XBlendGeometrySlider->addChangeListener(&XBlendSliderListener);
    
    BlendAmountSliderChangeListener YBlendSliderListener(TheBlendGeometry, 1, YBlendGeometrySlider);
    YBlendGeometrySlider->addChangeListener(&YBlendSliderListener);
    
    BlendAmountSliderChangeListener ZBlendSliderListener(TheBlendGeometry, 2, ZBlendGeometrySlider);
    ZBlendGeometrySlider->addChangeListener(&ZBlendSliderListener);

    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "02BlendedGeometry");

    //Main Loop
    TutorialWindowEventProducer->mainLoop();

    osgExit();

    return 0;
}

// redraw the window
void display(void)
{
    mgr->redraw();
}

// React to size changes
void reshape(Vec2f Size)
{
    mgr->resize(Size.x(), Size.y());
}

void setupBlendGeometry(void)
{
    
   osg::NodePtr BaseGeometryNode = NamedNodeFinder::find(BubbleBlendGeometryNode, "Base_Geometry");
   osg::NodePtr BlendShape1Node = NamedNodeFinder::find(BubbleBlendGeometryNode, "Blend_Shape_1");
   osg::NodePtr BlendShape2Node = NamedNodeFinder::find(BubbleBlendGeometryNode, "Blend_Shape_2");

   if(BaseGeometryNode == NullFC)
   {
      std::cout << "BaseGeometryNode Not Found." << std::endl;
      std::cout << "Are you using Data/BubbleBlendShape.osb" << std::endl;
      exit(0);
   }
   if(BlendShape1Node == NullFC)
   {
      std::cout << "BlendShape1Node Not Found." << std::endl;
      std::cout << "Are you using Data/BubbleBlendShape.osb" << std::endl;
      exit(0);
   }
   if(BlendShape2Node == NullFC)
   {
      std::cout << "BlendShape2Node Not Found." << std::endl;
      std::cout << "Are you using Data/BubbleBlendShape.osb" << std::endl;
      exit(0);
   }

   osg::GeometryPtr BaseGeometryCore= osg::Geometry::Ptr::dcast( BaseGeometryNode->getCore() );
   osg::GeometryPtr BaseGeometryCoreCopy= osg::Geometry::Ptr::dcast( deepClone(BaseGeometryCore, std::string("")) );
   osg::GeometryPtr BlendShape1GeoCore= osg::Geometry::Ptr::dcast( BlendShape1Node->getCore() );
   osg::GeometryPtr BlendShape2GeoCore= osg::Geometry::Ptr::dcast( BlendShape2Node->getCore() );

   //Create the BlendGeometry Core
   TheBlendGeometry = osg::BlendGeometry::create(BaseGeometryCore);
   TheBlendGeometry->addBlendGeometry(BlendShape1GeoCore,0.0f);
   TheBlendGeometry->addBlendGeometry(BlendShape2GeoCore,0.0f);

   NodePtr BlendGeometryNode = osg::Node::create();
   beginEditCP(BlendGeometryNode);
      BlendGeometryNode->setCore(TheBlendGeometry);
   endEditCP(BlendGeometryNode);

   //Transformed Node
   osg::TransformPtr BlendGeometryTrans = osg::Transform::create();
   osg::Matrix BlendGeometryTransMatrix;
   BlendGeometryTransMatrix.setTranslate(5.0,5.0,0.0);

   beginEditCP(BlendGeometryTrans);
      BlendGeometryTrans->setMatrix(BlendGeometryTransMatrix);
   endEditCP(BlendGeometryTrans);


   BlendGeometryTransNode = osg::Node::create();
   beginEditCP(BlendGeometryTransNode);
      BlendGeometryTransNode->setCore(BlendGeometryTrans);
      BlendGeometryTransNode->addChild(BlendGeometryNode);
   endEditCP(BlendGeometryTransNode);
}

NodePtr createBlendRootNode(void)
{
    // create the scene
    BubbleBlendGeometryNode = SceneFileHandler::the().read(".\\Data\\BubbleBlendShape.osb");

    //Make the Blend Geometry Node
    setupBlendGeometry();

    //Make Main Scene Node
    NodePtr scene = osg::Node::create();
    osg::ComponentTransformPtr Trans;
    Trans = osg::ComponentTransform::create();
    osg::setName(Trans, std::string("MainTransformationCore"));
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(Trans);
        scene->addChild(BubbleBlendGeometryNode);
        scene->addChild(BlendGeometryTransNode);
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    return scene;
}

ComponentPtr createGLPanel(void)
{
	//Create the nessecary parts for a viewport

    //Camera Beacon
	Matrix TransformMatrix;
	TransformMatrix.setTranslate(0.0f,0.0f, 0.0f);
	TransformPtr CameraBeaconTransform = Transform::create();
	beginEditCP(CameraBeaconTransform, Transform::MatrixFieldMask);
		CameraBeaconTransform->setMatrix(TransformMatrix);
	endEditCP(CameraBeaconTransform, Transform::MatrixFieldMask);

	NodePtr CameraBeaconNode = Node::create();
	beginEditCP(CameraBeaconNode, Node::CoreFieldMask);
		CameraBeaconNode->setCore(CameraBeaconTransform);
	endEditCP(CameraBeaconNode, Node::CoreFieldMask);

    //Light Beacon
	Matrix LightTransformMatrix;
	LightTransformMatrix.setTranslate(0.0f,0.0f, 0.0f);
	TransformPtr LightBeaconTransform = Transform::create();
	beginEditCP(LightBeaconTransform, Transform::MatrixFieldMask);
		LightBeaconTransform->setMatrix(TransformMatrix);
	endEditCP(LightBeaconTransform, Transform::MatrixFieldMask);

	NodePtr LightBeaconNode = Node::create();
	beginEditCP(LightBeaconNode, Node::CoreFieldMask);
		LightBeaconNode->setCore(CameraBeaconTransform);
	endEditCP(LightBeaconNode, Node::CoreFieldMask);
    
    //Light Node
    DirectionalLightPtr TheDirectionLight = DirectionalLight::create();
    beginEditCP(TheDirectionLight, DirectionalLight::DirectionFieldMask);
        TheDirectionLight->setDirection(0.0f,1.0f,0.0f);
    endEditCP(TheDirectionLight, DirectionalLight::DirectionFieldMask);

	NodePtr LightNode = Node::create();
	beginEditCP(LightNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
		LightNode->setCore(TheDirectionLight);
        LightNode->addChild(createBlendRootNode());
	endEditCP(LightNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

    // Make Torus Node (creates Torus in background of scene)
    NodePtr GeometryNode = makeTorus(.5, 2, 32, 32);

    // Make Main Scene Node and add the Torus
    NodePtr DefaultRootNode = osg::Node::create();
    beginEditCP(DefaultRootNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        DefaultRootNode->setCore(osg::Group::create());
        DefaultRootNode->addChild(CameraBeaconNode);
        DefaultRootNode->addChild(LightBeaconNode);
        DefaultRootNode->addChild(LightNode);
    endEditCP(DefaultRootNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

	//Camera
	PerspectiveCameraPtr DefaultCamera = PerspectiveCamera::create();
     beginEditCP(DefaultCamera);
		 DefaultCamera->setBeacon(CameraBeaconNode);
		 DefaultCamera->setFov   (deg2rad(60.f));
		 DefaultCamera->setNear  (0.1f);
		 DefaultCamera->setFar   (100.f);
     endEditCP(DefaultCamera);

	//Background
	GradientBackgroundPtr DefaultBackground = GradientBackground::create();
	beginEditCP(DefaultBackground, GradientBackground::ColorFieldMask | GradientBackground::PositionFieldMask);
		DefaultBackground->addLine(Color3f(0.0f,0.0f,0.0f), 0.0f);
		DefaultBackground->addLine(Color3f(0.0f,0.0f,1.0f), 1.0f);
	endEditCP(DefaultBackground, GradientBackground::ColorFieldMask | GradientBackground::PositionFieldMask);
	
	//Viewport
	ViewportPtr DefaultViewport = Viewport::create();
	beginEditCP(DefaultViewport);
		DefaultViewport->setCamera                  (DefaultCamera);
		DefaultViewport->setRoot                    (DefaultRootNode);
		DefaultViewport->setSize                    (0.0f,0.0f, 1.0f,1.0f);
		DefaultViewport->setBackground              (DefaultBackground);
	endEditCP(DefaultViewport);

	//GL Viewport Component

	GLViewportPtr TheGLViewport = GLViewport::create();
	beginEditCP(TheGLViewport, GLViewport::PortFieldMask | GLViewport::PreferredSizeFieldMask | GLViewport::BordersFieldMask);
		TheGLViewport->setPort(DefaultViewport);
		TheGLViewport->setPreferredSize(Vec2f(600.0f,450.0f));
	endEditCP(TheGLViewport, GLViewport::PortFieldMask | GLViewport::PreferredSizeFieldMask | GLViewport::BordersFieldMask);
	
    TheGLViewport->showAll();

    return TheGLViewport;
}
