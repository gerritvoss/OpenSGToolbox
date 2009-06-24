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
#include <OpenSG/Input/OSGWindowAdapter.h>
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

//Material
#include <OpenSG/OSGLineChunk.h>
#include <OpenSG/OSGBlendChunk.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialChunk.h>

//Animation
#include <OpenSG/Animation/OSGSkeleton.h>
#include <OpenSG/Animation/OSGSkeletonDrawable.h>
#include <OpenSG/OSGTime.h>
#include <OpenSG/Animation/OSGKeyframeSequences.h>
#include <OpenSG/Animation/OSGFieldAnimation.h>
#include <OpenSG/Animation/OSGKeyframeAnimator.h>
#include <OpenSG/Animation/OSGElapsedTimeAnimationAdvancer.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include <OpenSG/Animation/OSGSkeletonAnimation.h>
#include <OpenSG/Animation/OSGSkeletonBlendedAnimation.h>
#include <OpenSG/Animation/OSGSkeleton.h>
#include <OpenSG/Animation/OSGJoint.h>

#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/Animation/OSGSkeletonBlendedGeometry.h>

// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// For the skeleton
SkeletonBlendedAnimationPtr TheSkeletonBlendedAnimation;
SkeletonAnimationPtr TheUpperSkeletonAnimation;
SkeletonAnimationPtr TheLowerSkeletonAnimation;
AnimationAdvancerPtr TheAnimationAdvancer;
JointPtr Pelvis,LeftHip,RightHip,LeftKnee,RightKnee,LeftFoot,RightFoot,LeftToes,RightToes, Clavicle, LeftShoulder,RightShoulder,LeftElbow,RightElbow,LeftHand,RightHand,LeftFingers,RightFingers,Head; 
SkeletonPtr ExampleSkeleton;
// The pointer to the geometry core
GeometryPtr geo;

// forward declaration so we can have the interesting stuff upfront
ComponentPtr createGLPanel(void);
NodePtr createSkeleton(void);
NodePtr createMesh(void);
void setupAnimation(void);

bool ExitApp = false;

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

class TutorialUpdateListener : public UpdateListener
{
  public:
    virtual void update(const UpdateEvent& e)
    {
		ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->update(e.getElapsedTime());

		TheSkeletonBlendedAnimation->update(TheAnimationAdvancer);
    }
};

class BlendAmountSliderChangeListener : public ChangeListener
{
  public:
      BlendAmountSliderChangeListener(SkeletonBlendedAnimationPtr TheSkeletonBlendedAnimation,
          UInt32 BlendAmountIndex, SliderPtr TheSlider) : _SkeletonBlendedAnimation(TheSkeletonBlendedAnimation),_BlendAmountIndex(BlendAmountIndex),_Slider(TheSlider)
      {
      }

    virtual void stateChanged(const ChangeEvent& e)
    {
        if(_Slider != NullFC && 
            _SkeletonBlendedAnimation != NullFC)
        {
            _SkeletonBlendedAnimation->setBlendAmount(_BlendAmountIndex,static_cast<Real32>(_Slider->getValue())/100.0f);
        }
    }
protected:
    SkeletonBlendedAnimationPtr _SkeletonBlendedAnimation;
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
    TutorialMouseListener TheTutorialMouseListener;
    TutorialMouseMotionListener TheTutorialMouseMotionListener;
    TutorialWindowEventProducer->addMouseListener(&TheTutorialMouseListener);
    TutorialWindowEventProducer->addMouseMotionListener(&TheTutorialMouseMotionListener);
	TutorialUpdateListener TheTutorialUpdateListener;
    TutorialWindowEventProducer->addUpdateListener(&TheTutorialUpdateListener);

    
    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
	
    TutorialWindowEventProducer->openWindow(Pnt2f(0,0),
                                        Vec2f(1000,740),
                                        "OpenSG 22SkeletonBlendedAnimation Window");

	//Setup scene
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
    DefaultBoundedRangeModelPtr UpperAnimationSliderRangeModel = DefaultBoundedRangeModel::create();
    UpperAnimationSliderRangeModel->setMinimum(-200);
    UpperAnimationSliderRangeModel->setMaximum(200);
    UpperAnimationSliderRangeModel->setValue(0);
    UpperAnimationSliderRangeModel->setExtent(0);
    
    //Create the slider
    LabelPtr TempLabel;
    SliderPtr UpperAnimationSlider = Slider::create();
    beginEditCP(UpperAnimationSlider, Slider::LabelMapFieldMask | Slider::PreferredSizeFieldMask | Slider::MajorTickSpacingFieldMask | Slider::MinorTickSpacingFieldMask | Slider::SnapToTicksFieldMask | Slider::DrawLabelsFieldMask | Slider::RangeModelFieldMask);
        TempLabel = Label::Ptr::dcast(UpperAnimationSlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("-2.0"); endEditCP(TempLabel, Label::TextFieldMask);
        UpperAnimationSlider->getLabelMap()[-200] = TempLabel;
        
        TempLabel = Label::Ptr::dcast(UpperAnimationSlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("-1.0"); endEditCP(TempLabel, Label::TextFieldMask);
        UpperAnimationSlider->getLabelMap()[-100] = TempLabel;

        TempLabel = Label::Ptr::dcast(UpperAnimationSlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("0.0"); endEditCP(TempLabel, Label::TextFieldMask);
        UpperAnimationSlider->getLabelMap()[0] = TempLabel;

        TempLabel = Label::Ptr::dcast(UpperAnimationSlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("1.0"); endEditCP(TempLabel, Label::TextFieldMask);
        UpperAnimationSlider->getLabelMap()[100] = TempLabel;

        TempLabel = Label::Ptr::dcast(UpperAnimationSlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("2.0"); endEditCP(TempLabel, Label::TextFieldMask);
        UpperAnimationSlider->getLabelMap()[200] = TempLabel;


        UpperAnimationSlider->setPreferredSize(Vec2f(100, 300));
        UpperAnimationSlider->setSnapToTicks(false);
        UpperAnimationSlider->setMajorTickSpacing(10);
        UpperAnimationSlider->setMinorTickSpacing(5);
        UpperAnimationSlider->setOrientation(Slider::VERTICAL_ORIENTATION);
        UpperAnimationSlider->setInverted(true);
        UpperAnimationSlider->setDrawLabels(true);
        UpperAnimationSlider->setRangeModel(UpperAnimationSliderRangeModel);
    endEditCP(UpperAnimationSlider, Slider::LabelMapFieldMask | Slider::PreferredSizeFieldMask | Slider::MajorTickSpacingFieldMask | Slider::MinorTickSpacingFieldMask | Slider::SnapToTicksFieldMask | Slider::DrawLabelsFieldMask | Slider::RangeModelFieldMask);
    
    DefaultBoundedRangeModelPtr LowerAnimationSliderRangeModel = DefaultBoundedRangeModel::create();
    LowerAnimationSliderRangeModel->setMinimum(-200);
    LowerAnimationSliderRangeModel->setMaximum(200);
    LowerAnimationSliderRangeModel->setValue(0);
    LowerAnimationSliderRangeModel->setExtent(0);
    
    //Create the slider
    SliderPtr LowerAnimationSlider = Slider::create();
    beginEditCP(LowerAnimationSlider, Slider::LabelMapFieldMask | Slider::PreferredSizeFieldMask | Slider::MajorTickSpacingFieldMask | Slider::MinorTickSpacingFieldMask | Slider::SnapToTicksFieldMask | Slider::DrawLabelsFieldMask | Slider::RangeModelFieldMask);
        TempLabel = Label::Ptr::dcast(LowerAnimationSlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("-2.0"); endEditCP(TempLabel, Label::TextFieldMask);
        LowerAnimationSlider->getLabelMap()[-200] = TempLabel;
        
        TempLabel = Label::Ptr::dcast(LowerAnimationSlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("-1.0"); endEditCP(TempLabel, Label::TextFieldMask);
        LowerAnimationSlider->getLabelMap()[-100] = TempLabel;

        TempLabel = Label::Ptr::dcast(LowerAnimationSlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("0.0"); endEditCP(TempLabel, Label::TextFieldMask);
        LowerAnimationSlider->getLabelMap()[0] = TempLabel;

        TempLabel = Label::Ptr::dcast(LowerAnimationSlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("1.0"); endEditCP(TempLabel, Label::TextFieldMask);
        LowerAnimationSlider->getLabelMap()[100] = TempLabel;

        TempLabel = Label::Ptr::dcast(LowerAnimationSlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("2.0"); endEditCP(TempLabel, Label::TextFieldMask);
        LowerAnimationSlider->getLabelMap()[200] = TempLabel;


        LowerAnimationSlider->setPreferredSize(Vec2f(100, 300));
        LowerAnimationSlider->setSnapToTicks(false);
        LowerAnimationSlider->setMajorTickSpacing(10);
        LowerAnimationSlider->setMinorTickSpacing(5);
        LowerAnimationSlider->setOrientation(Slider::VERTICAL_ORIENTATION);
        LowerAnimationSlider->setInverted(true);
        LowerAnimationSlider->setDrawLabels(true);
        LowerAnimationSlider->setRangeModel(LowerAnimationSliderRangeModel);
    endEditCP(LowerAnimationSlider, Slider::LabelMapFieldMask | Slider::PreferredSizeFieldMask | Slider::MajorTickSpacingFieldMask | Slider::MinorTickSpacingFieldMask | Slider::SnapToTicksFieldMask | Slider::DrawLabelsFieldMask | Slider::RangeModelFieldMask);

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
       MainInternalWindow->getChildren().push_back(UpperAnimationSlider);
       MainInternalWindow->getChildren().push_back(LowerAnimationSlider);
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
    BlendAmountSliderChangeListener UpperAnimationSliderListener(TheSkeletonBlendedAnimation, 0, UpperAnimationSlider);
    UpperAnimationSlider->addChangeListener(&UpperAnimationSliderListener);
    
    BlendAmountSliderChangeListener LowerAnimationSliderListener(TheSkeletonBlendedAnimation, 1, LowerAnimationSlider);
    LowerAnimationSlider->addChangeListener(&LowerAnimationSliderListener);

	//Animation Advancer
    TheAnimationAdvancer = ElapsedTimeAnimationAdvancer::create();
    beginEditCP(TheAnimationAdvancer);
    ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->setStartTime( 0.0 );
    beginEditCP(TheAnimationAdvancer);

	
	// Show the whole Scene
    mgr->showAll();


    while(!ExitApp)
    {
        TutorialWindowEventProducer->update();
        TutorialWindowEventProducer->draw();
    }
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

NodePtr createSkeleton(void)
{
	//SkeletonDrawer System Material
	LineChunkPtr ExampleLineChunk = LineChunk::create();
	beginEditCP(ExampleLineChunk);
		ExampleLineChunk->setWidth(2.0f);
		ExampleLineChunk->setSmooth(true);
	endEditCP(ExampleLineChunk);

	BlendChunkPtr ExampleBlendChunk = BlendChunk::create();
	beginEditCP(ExampleBlendChunk);
	    ExampleBlendChunk->setSrcFactor(GL_SRC_ALPHA);
	    ExampleBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
	endEditCP(ExampleBlendChunk);

	MaterialChunkPtr ExampleMaterialChunk = MaterialChunk::create();
	beginEditCP(ExampleMaterialChunk);
		ExampleMaterialChunk->setAmbient(Color4f(1.0f,1.0f,1.0f,1.0f));
		ExampleMaterialChunk->setDiffuse(Color4f(0.0f,0.0f,0.0f,1.0f));
		ExampleMaterialChunk->setSpecular(Color4f(0.0f,0.0f,0.0f,1.0f));
	endEditCP(ExampleMaterialChunk);

	ChunkMaterialPtr ExampleMaterial = ChunkMaterial::create();
	beginEditCP(ExampleMaterial, ChunkMaterial::ChunksFieldMask);
		ExampleMaterial->addChunk(ExampleLineChunk);
		ExampleMaterial->addChunk(ExampleMaterialChunk);
		ExampleMaterial->addChunk(ExampleBlendChunk);
	endEditCP(ExampleMaterial, ChunkMaterial::ChunksFieldMask);

	//===========================================Joints==================================================================
	Matrix TempMat;

	/*================================================================================================*/
	/*                                       Left Fingers                                                 */
	LeftFingers = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(1.0,0.0,0.0);
	beginEditCP(LeftFingers, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);
		LeftFingers->setRelativeTransformation(TempMat);
		LeftFingers->setBindRelativeTransformation(TempMat);
	endEditCP(LeftFingers, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);

	/*================================================================================================*/
	/*                                       Right Fingers                                                 */
	RightFingers = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(-1.0,0.0,0.0);
	beginEditCP(RightFingers, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);
		RightFingers->setRelativeTransformation(TempMat);
		RightFingers->setBindRelativeTransformation(TempMat);
	endEditCP(RightFingers, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);
	/*================================================================================================*/
	/*                                       Left Hand                                                 */
	LeftHand = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(2.0,0.0,0.0);
	beginEditCP(LeftHand, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		LeftHand->setRelativeTransformation(TempMat);
		LeftHand->setBindRelativeTransformation(TempMat);
		LeftHand->getChildJoints().push_back(LeftFingers);
	endEditCP(LeftHand, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Right Hand                                                 */
	RightHand = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(-2.0,0.0,0.0);
	beginEditCP(RightHand, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		RightHand->setRelativeTransformation(TempMat);
		RightHand->setBindRelativeTransformation(TempMat);
		RightHand->getChildJoints().push_back(RightFingers);
	endEditCP(RightHand, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
	/*================================================================================================*/
	/*                                       Left Elbow                                                 */
	LeftElbow = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(2.0,0.0,0.0);
	beginEditCP(LeftElbow, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		LeftElbow->setRelativeTransformation(TempMat);
		LeftElbow->setBindRelativeTransformation(TempMat);
		LeftElbow->getChildJoints().push_back(LeftHand);
	endEditCP(LeftElbow, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Right Elbow                                                 */
	RightElbow = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(-2.0,0.0,0.0);
	beginEditCP(RightElbow, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		RightElbow->setRelativeTransformation(TempMat);
		RightElbow->setBindRelativeTransformation(TempMat);
		RightElbow->getChildJoints().push_back(RightHand);
	endEditCP(RightElbow, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
	/*================================================================================================*/
	/*                                       Left Shoulder                                                 */
	LeftShoulder = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(1.0,-0.5,0.0);
	beginEditCP(LeftShoulder, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		LeftShoulder->setRelativeTransformation(TempMat);
		LeftShoulder->setBindRelativeTransformation(TempMat);
		LeftShoulder->getChildJoints().push_back(LeftElbow);
	endEditCP(LeftShoulder, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Right Shoulder                                                 */
	RightShoulder = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(-1.0,-0.5,0.0);
	beginEditCP(RightShoulder, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		RightShoulder->setRelativeTransformation(TempMat);
		RightShoulder->setBindRelativeTransformation(TempMat);
		RightShoulder->getChildJoints().push_back(RightElbow);
	endEditCP(RightShoulder, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Head                                                 */
	Head = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(0.0,1.0,0.0);
	beginEditCP(Head, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);
		Head->setRelativeTransformation(TempMat);
		Head->setBindRelativeTransformation(TempMat);
	endEditCP(Head, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);

	/*================================================================================================*/
	/*                                       Clavicle                                                   */
	Clavicle = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(0.0,5.0,0.0);
	beginEditCP(Clavicle, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		Clavicle->setRelativeTransformation(TempMat);
		Clavicle->setBindRelativeTransformation(TempMat);
		Clavicle->getChildJoints().push_back(LeftShoulder);
		Clavicle->getChildJoints().push_back(RightShoulder);
		Clavicle->getChildJoints().push_back(Head);
	endEditCP(Clavicle, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Left Toes                                                 */
	LeftToes = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(0.0,0.0,1.0);
	beginEditCP(LeftToes, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);
		LeftToes->setRelativeTransformation(TempMat);
		LeftToes->setBindRelativeTransformation(TempMat);
	endEditCP(LeftToes, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);

	/*================================================================================================*/
	/*                                       Right Toes                                                 */
	RightToes = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(0.0,0.0,1.0);
	beginEditCP(RightToes, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);
		RightToes->setRelativeTransformation(TempMat);
		RightToes->setBindRelativeTransformation(TempMat);
	endEditCP(RightToes, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask);
	/*================================================================================================*/
	/*                                       Left Foot                                                 */
	LeftFoot = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(0.0,-3.0,0.0);
	beginEditCP(LeftFoot, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		LeftFoot->setRelativeTransformation(TempMat);
		LeftFoot->setBindRelativeTransformation(TempMat);
		LeftFoot->getChildJoints().push_back(LeftToes);
	endEditCP(LeftFoot, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Right Foot                                                 */
	RightFoot = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(0.0,-3.0,0.0);
	beginEditCP(RightFoot, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		RightFoot->setRelativeTransformation(TempMat);
		RightFoot->setBindRelativeTransformation(TempMat);
		RightFoot->getChildJoints().push_back(RightToes);
	endEditCP(RightFoot, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
	/*================================================================================================*/
	/*                                       Left Knee                                                 */
	LeftKnee = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(0.0,-3.0,0.0);
	beginEditCP(LeftKnee, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		LeftKnee->setRelativeTransformation(TempMat);
		LeftKnee->setBindRelativeTransformation(TempMat);
		LeftKnee->getChildJoints().push_back(LeftFoot);
	endEditCP(LeftKnee, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Right Knee                                                 */
	RightKnee = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(0.0,-3.0,0.0);
	beginEditCP(RightKnee, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		RightKnee->setRelativeTransformation(TempMat);
		RightKnee->setBindRelativeTransformation(TempMat);
		RightKnee->getChildJoints().push_back(RightFoot);
	endEditCP(RightKnee, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Left Hip                                                 */
	LeftHip = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(1.0,-1.0,0.0);
	beginEditCP(LeftHip, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		LeftHip->setRelativeTransformation(TempMat);
		LeftHip->setBindRelativeTransformation(TempMat);
		LeftHip->getChildJoints().push_back(LeftKnee);
	endEditCP(LeftHip, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Right Hip                                                 */
	RightHip = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(-1.0,-1.0,0.0);
	beginEditCP(RightHip, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		RightHip->setRelativeTransformation(TempMat);
		RightHip->setBindRelativeTransformation(TempMat);
		RightHip->getChildJoints().push_back(RightKnee);
	endEditCP(RightHip, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);

	/*================================================================================================*/
	/*                                       Pelvis                                                   */
	Pelvis = Joint::create(); //create a bone called ExampleChildbone
	TempMat.setTranslate(0.0,7.0,0.0);
	beginEditCP(Pelvis, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
		Pelvis->setRelativeTransformation(TempMat);
		Pelvis->setBindRelativeTransformation(TempMat);
		Pelvis->getChildJoints().push_back(LeftHip);
		Pelvis->getChildJoints().push_back(RightHip);
		Pelvis->getChildJoints().push_back(Clavicle);
	endEditCP(Pelvis, Joint::RelativeTransformationFieldMask | Joint::BindRelativeTransformationFieldMask | Joint::ChildJointsFieldMask);
	


    //Skeleton
    ExampleSkeleton = Skeleton::create();
	beginEditCP(ExampleSkeleton, Skeleton::RootJointsFieldMask);
		ExampleSkeleton->getRootJoints().push_back(Pelvis);
	endEditCP(ExampleSkeleton, Skeleton::RootJointsFieldMask);


	    //Skeleton
    SkeletonPtr ExampleSkeleton = Skeleton::create();
	beginEditCP(ExampleSkeleton, Skeleton::RootJointsFieldMask);
		ExampleSkeleton->getRootJoints().push_back(Pelvis);
	endEditCP(ExampleSkeleton, Skeleton::RootJointsFieldMask);

    //SkeletonDrawer
    SkeletonDrawablePtr ExampleSkeletonDrawable = SkeletonDrawable::create();
    beginEditCP(ExampleSkeletonDrawable, SkeletonDrawable::SkeletonFieldMask | SkeletonDrawable::MaterialFieldMask);
		ExampleSkeletonDrawable->setSkeleton(ExampleSkeleton);
		ExampleSkeletonDrawable->setMaterial(ExampleMaterial);
    endEditCP(ExampleSkeletonDrawable, SkeletonDrawable::SkeletonFieldMask | SkeletonDrawable::MaterialFieldMask);
	
	//Skeleton Node
	NodePtr SkeletonNode = Node::create();
    beginEditCP(SkeletonNode, Node::CoreFieldMask);
        SkeletonNode->setCore(ExampleSkeletonDrawable);
    endEditCP(SkeletonNode, Node::CoreFieldMask);

	return SkeletonNode;
}

NodePtr createMesh(void)
{
	GeoPTypesPtr type = GeoPTypesUI8::create();        
    beginEditCP(type, GeoPTypesUI8::GeoPropDataFieldMask);
    {
        type->addValue(GL_QUADS);
    }
    endEditCP  (type, GeoPTypesUI8::GeoPropDataFieldMask);

	GeoPLengthsPtr lens = GeoPLengthsUI32::create();    
    beginEditCP(lens, GeoPLengthsUI32::GeoPropDataFieldMask);
    {
        lens->addValue(72);
    }
    endEditCP  (lens, GeoPLengthsUI32::GeoPropDataFieldMask);
	 GeoPositions3fPtr pnts = GeoPositions3f::create();
    beginEditCP(pnts, GeoPositions3f::GeoPropDataFieldMask);
    {
		// the points of the Quads

		//Back
        pnts->addValue(Pnt3f(-0.5,  6.0,  0));
        pnts->addValue(Pnt3f( 0.5,  6.0,  0));
        pnts->addValue(Pnt3f( 0.5,  12.0,  0));
        pnts->addValue(Pnt3f(-0.5,  12.0,  0));

		//Head
        pnts->addValue(Pnt3f(-0.5,  12,  0));
        pnts->addValue(Pnt3f( 0.5,  12,  0));
        pnts->addValue(Pnt3f( 0.5,  13,  0));
        pnts->addValue(Pnt3f(-0.5,  13,  0));

		//Left Shoulder
		pnts->addValue(Pnt3f(0.0,  11.5,  0));
		pnts->addValue(Pnt3f(0.0,  12.5,  0));
		pnts->addValue(Pnt3f(1.0,  12.0,  0));
		pnts->addValue(Pnt3f(1.0,  11.0,  0));

		//Left Humerus
		pnts->addValue(Pnt3f(1.0,  11.0,  0));
		pnts->addValue(Pnt3f(1.0,  12.0,  0));
		pnts->addValue(Pnt3f(3.0,  12.0,  0));
		pnts->addValue(Pnt3f(3.0,  11.0,  0));

		//Left Radius
		pnts->addValue(Pnt3f(3.0,  11.0,  0));
		pnts->addValue(Pnt3f(3.0,  12.0,  0));
		pnts->addValue(Pnt3f(5.0,  12.0,  0));
		pnts->addValue(Pnt3f(5.0,  11.0,  0));

		//Left Hand
		pnts->addValue(Pnt3f(5.0,  11.0,  0));
		pnts->addValue(Pnt3f(5.0,  12.0,  0));
		pnts->addValue(Pnt3f(6.0,  12.0,  0));
		pnts->addValue(Pnt3f(6.0,  11.0,  0));

		//Right Shoulder
		pnts->addValue(Pnt3f(0.0,  11.5,  0));
		pnts->addValue(Pnt3f(0.0,  12.5,  0));
		pnts->addValue(Pnt3f(-1.0,  12.0,  0));
		pnts->addValue(Pnt3f(-1.0,  11.0,  0));

		//Right Humerus
		pnts->addValue(Pnt3f(-1.0,  11.0,  0));
		pnts->addValue(Pnt3f(-1.0,  12.0,  0));
		pnts->addValue(Pnt3f(-3.0,  12.0,  0));
		pnts->addValue(Pnt3f(-3.0,  11.0,  0));

		//Right Radius
		pnts->addValue(Pnt3f(-3.0,  11.0,  0));
		pnts->addValue(Pnt3f(-3.0,  12.0,  0));
		pnts->addValue(Pnt3f(-5.0,  12.0,  0));
		pnts->addValue(Pnt3f(-5.0,  11.0,  0));

		//Right Hand
		pnts->addValue(Pnt3f(-5.0,  11.0,  0));
		pnts->addValue(Pnt3f(-5.0,  12.0,  0));
		pnts->addValue(Pnt3f(-6.0,  12.0,  0));
		pnts->addValue(Pnt3f(-6.0,  11.0,  0));

		//Left Hip
		pnts->addValue(Pnt3f(0.0, 6.5,  0));
		pnts->addValue(Pnt3f(0.5, 7.5,  0));
		pnts->addValue(Pnt3f( 1.5,  6.0,  0));
		pnts->addValue(Pnt3f(0.5,  6.0,  0));

		//Left Femur
		pnts->addValue(Pnt3f(0.5,  6.0,  0));
		pnts->addValue(Pnt3f( 1.5,  6.0,  0));
		pnts->addValue(Pnt3f( 1.5,  3.0,  0));
		pnts->addValue(Pnt3f(0.5,  3.0,  0));

		//Left Tibia
		pnts->addValue(Pnt3f(0.5,  3.0,  0));
		pnts->addValue(Pnt3f( 1.5,  3.0,  0));
		pnts->addValue(Pnt3f( 1.5,  0.0,  0));
		pnts->addValue(Pnt3f(0.5,  0.0,  0));
		
		//Left Foot
		pnts->addValue(Pnt3f(0.5,  0.0,  0));
		pnts->addValue(Pnt3f( 1.5,  0.0,  0));
		pnts->addValue(Pnt3f( 1.5,  0.0,  1.0));
		pnts->addValue(Pnt3f(0.5,  0.0,  1.0));
		

		//Right Hip
		pnts->addValue(Pnt3f(0.0, 6.5,  0));
		pnts->addValue(Pnt3f(-0.5, 7.5,  0));
		pnts->addValue(Pnt3f( -1.5,  6.0,  0));
		pnts->addValue(Pnt3f(-0.5,  6.0,  0));

		//Right Femur
		pnts->addValue(Pnt3f(-0.5,  6.0,  0));
		pnts->addValue(Pnt3f( -1.5,  6.0,  0));
		pnts->addValue(Pnt3f( -1.5,  3.0,  0));
		pnts->addValue(Pnt3f(-0.5,  3.0,  0));

		//Right Tibia
		pnts->addValue(Pnt3f(-0.5,  3.0,  0));
		pnts->addValue(Pnt3f( -1.5,  3.0,  0));
		pnts->addValue(Pnt3f( -1.5,  0.0,  0));
		pnts->addValue(Pnt3f(-0.5,  0.0,  0));
		
		//Right Foot
		pnts->addValue(Pnt3f(-0.5,  0.0,  0));
		pnts->addValue(Pnt3f( -1.5,  0.0,  0));
		pnts->addValue(Pnt3f( -1.5,  0.0,  1.0));
		pnts->addValue(Pnt3f(-0.5,  0.0,  1.0));

    }
    endEditCP  (pnts, GeoPositions3f::GeoPropDataFieldMask);
    
    //Normals
	 GeoNormals3fPtr norms = GeoNormals3f::create();
	 geo=Geometry::create();
    beginEditCP(norms, GeoNormals3f::GeoPropDataFieldMask);
        norms->addValue(Vec3f( 0.0,0.0,1.0));
        norms->addValue(Vec3f( 0.0,0.0,1.0));
        norms->addValue(Vec3f( 0.0,0.0,1.0));
        norms->addValue(Vec3f( 0.0,0.0,1.0));

        norms->addValue(Vec3f( 0.0,0.0,1.0));
        norms->addValue(Vec3f( 0.0,0.0,1.0));
        norms->addValue(Vec3f( 0.0,0.0,1.0));
        norms->addValue(Vec3f( 0.0,0.0,1.0));

		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		//Left Hip
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		//Left Femur
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		//Left Tibia
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		//Left Foot
		norms->addValue(Vec3f( 0.0,1.0,0.0));
		norms->addValue(Vec3f( 0.0,1.0,0.0));
		norms->addValue(Vec3f( 0.0,1.0,0.0));
		norms->addValue(Vec3f( 0.0,1.0,0.0));

		//Right Hip
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		//Right Femur
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		//Right Tibia
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		//Right Foot
		norms->addValue(Vec3f( 0.0,1.0,0.0));
		norms->addValue(Vec3f( 0.0,1.0,0.0));
		norms->addValue(Vec3f( 0.0,1.0,0.0));
		norms->addValue(Vec3f( 0.0,1.0,0.0));

		

    endEditCP(norms, GeoNormals3f::GeoPropDataFieldMask);


    beginEditCP(geo, Geometry::TypesFieldMask     |
                     Geometry::LengthsFieldMask   |
                     Geometry::PositionsFieldMask |
                     Geometry::NormalsFieldMask |
                     Geometry::MaterialFieldMask  );
    {
        geo->setTypes    (type);
        geo->setLengths  (lens);
        geo->setPositions(pnts);
        geo->setNormals(norms);

        // assign a material to the geometry to make it visible. The details
        // of materials are defined later.
        geo->setMaterial(getDefaultMaterial());   
    }
    endEditCP  (geo, Geometry::TypesFieldMask     |
                     Geometry::LengthsFieldMask   |
                     Geometry::PositionsFieldMask |
                     Geometry::NormalsFieldMask |
                     Geometry::MaterialFieldMask  );
    
    // put the geometry core into a node
    NodePtr n = Node::create();
    beginEditCP(n, Node::CoreFieldMask);
    {
        n->setCore(geo);
    }
    endEditCP  (n, Node::CoreFieldMask);

	// Skeleton Blended Geometry

	SkeletonBlendedGeometryPtr TheNewSkeletonGeometry = SkeletonBlendedGeometry::create();
	beginEditCP(TheNewSkeletonGeometry);
		TheNewSkeletonGeometry->addSkeleton(ExampleSkeleton);
		TheNewSkeletonGeometry->setBaseGeometry(geo);
		//Back
		TheNewSkeletonGeometry->addJointBlending(0,Pelvis,1.0f);
		TheNewSkeletonGeometry->addJointBlending(1,Pelvis,1.0f);
		TheNewSkeletonGeometry->addJointBlending(2,Clavicle,1.0f);
		TheNewSkeletonGeometry->addJointBlending(3,Clavicle,1.0f);

		//Head
		TheNewSkeletonGeometry->addJointBlending(4,Clavicle,1.0f);
		TheNewSkeletonGeometry->addJointBlending(5,Clavicle,1.0f);
		TheNewSkeletonGeometry->addJointBlending(6,Head,1.0f);
		TheNewSkeletonGeometry->addJointBlending(7,Head,1.0f);

		//Left Shoulder
		TheNewSkeletonGeometry->addJointBlending(8,Clavicle,1.0f);
		TheNewSkeletonGeometry->addJointBlending(9,Clavicle,1.0f);
		TheNewSkeletonGeometry->addJointBlending(10,LeftShoulder,1.0f);
		TheNewSkeletonGeometry->addJointBlending(11,LeftShoulder,1.0f);

		//Left Humerus
		TheNewSkeletonGeometry->addJointBlending(12,LeftShoulder,1.0f);
		TheNewSkeletonGeometry->addJointBlending(13,LeftShoulder,1.0f);
		TheNewSkeletonGeometry->addJointBlending(14,LeftElbow,1.0f);
		TheNewSkeletonGeometry->addJointBlending(15,LeftElbow,1.0f);

		//Left Radius
		TheNewSkeletonGeometry->addJointBlending(16,LeftElbow,1.0f);
		TheNewSkeletonGeometry->addJointBlending(17,LeftElbow,1.0f);
		TheNewSkeletonGeometry->addJointBlending(18,LeftHand,1.0f);
		TheNewSkeletonGeometry->addJointBlending(19,LeftHand,1.0f);

		//Left Hand
		TheNewSkeletonGeometry->addJointBlending(20,LeftHand,1.0f);
		TheNewSkeletonGeometry->addJointBlending(21,LeftHand,1.0f);
		TheNewSkeletonGeometry->addJointBlending(22,LeftFingers,1.0f);
		TheNewSkeletonGeometry->addJointBlending(23,LeftFingers,1.0f);

		//Right Shoulder
		TheNewSkeletonGeometry->addJointBlending(24,Clavicle,1.0f);
		TheNewSkeletonGeometry->addJointBlending(25,Clavicle,1.0f);
		TheNewSkeletonGeometry->addJointBlending(26,RightShoulder,1.0f);
		TheNewSkeletonGeometry->addJointBlending(27,RightShoulder,1.0f);

		//Right Humerus
		TheNewSkeletonGeometry->addJointBlending(28,RightShoulder,1.0f);
		TheNewSkeletonGeometry->addJointBlending(29,RightShoulder,1.0f);
		TheNewSkeletonGeometry->addJointBlending(30,RightElbow,1.0f);
		TheNewSkeletonGeometry->addJointBlending(31,RightElbow,1.0f);

		//Right Radius
		TheNewSkeletonGeometry->addJointBlending(32,RightElbow,1.0f);
		TheNewSkeletonGeometry->addJointBlending(33,RightElbow,1.0f);
		TheNewSkeletonGeometry->addJointBlending(34,RightHand,1.0f);
		TheNewSkeletonGeometry->addJointBlending(35,RightHand,1.0f);

		//Right Hand
		TheNewSkeletonGeometry->addJointBlending(36,RightHand,1.0f);
		TheNewSkeletonGeometry->addJointBlending(37,RightHand,1.0f);
		TheNewSkeletonGeometry->addJointBlending(38,RightFingers,1.0f);
		TheNewSkeletonGeometry->addJointBlending(39,RightFingers,1.0f);

		//Left Hip
		TheNewSkeletonGeometry->addJointBlending(40,Pelvis,1.0f);
		TheNewSkeletonGeometry->addJointBlending(41,Pelvis,1.0f);
		TheNewSkeletonGeometry->addJointBlending(42,LeftHip,1.0f);
		TheNewSkeletonGeometry->addJointBlending(43,LeftHip,1.0f);

		//Left Femur
		TheNewSkeletonGeometry->addJointBlending(44,LeftHip,1.0f);
		TheNewSkeletonGeometry->addJointBlending(45,LeftHip,1.0f);
		TheNewSkeletonGeometry->addJointBlending(46,LeftKnee,1.0f);
		TheNewSkeletonGeometry->addJointBlending(47,LeftKnee,1.0f);

		//Left Tibia
		TheNewSkeletonGeometry->addJointBlending(48,LeftKnee,1.0f);
		TheNewSkeletonGeometry->addJointBlending(49,LeftKnee,1.0f);
		TheNewSkeletonGeometry->addJointBlending(50,LeftFoot,1.0f);
		TheNewSkeletonGeometry->addJointBlending(51,LeftFoot,1.0f);

		//Left Foot
		TheNewSkeletonGeometry->addJointBlending(52,LeftFoot,1.0f);
		TheNewSkeletonGeometry->addJointBlending(53,LeftFoot,1.0f);
		TheNewSkeletonGeometry->addJointBlending(54,LeftToes,1.0f);
		TheNewSkeletonGeometry->addJointBlending(55,LeftToes,1.0f);

		//Right Hip
		TheNewSkeletonGeometry->addJointBlending(56,Pelvis,1.0f);
		TheNewSkeletonGeometry->addJointBlending(57,Pelvis,1.0f);
		TheNewSkeletonGeometry->addJointBlending(58,RightHip,1.0f);
		TheNewSkeletonGeometry->addJointBlending(59,RightHip,1.0f);

		//Right Femur
		TheNewSkeletonGeometry->addJointBlending(60,RightHip,1.0f);
		TheNewSkeletonGeometry->addJointBlending(61,RightHip,1.0f);
		TheNewSkeletonGeometry->addJointBlending(62,RightKnee,1.0f);
		TheNewSkeletonGeometry->addJointBlending(63,RightKnee,1.0f);

		//Right Tibia
		TheNewSkeletonGeometry->addJointBlending(64,RightKnee,1.0f);
		TheNewSkeletonGeometry->addJointBlending(65,RightKnee,1.0f);
		TheNewSkeletonGeometry->addJointBlending(66,RightFoot,1.0f);
		TheNewSkeletonGeometry->addJointBlending(67,RightFoot,1.0f);

		//Right Foot
		TheNewSkeletonGeometry->addJointBlending(68,RightFoot,1.0f);
		TheNewSkeletonGeometry->addJointBlending(69,RightFoot,1.0f);
		TheNewSkeletonGeometry->addJointBlending(70,RightToes,1.0f);
		TheNewSkeletonGeometry->addJointBlending(71,RightToes,1.0f);
    endEditCP(TheNewSkeletonGeometry);
	
	NodePtr MeshNode = Node::create();
    beginEditCP(MeshNode, Node::CoreFieldMask);
        MeshNode->setCore(TheNewSkeletonGeometry);
    endEditCP(MeshNode, Node::CoreFieldMask);

	return MeshNode;
}

NodePtr createScene(void)
{
	//Make Main Scene Node
    NodePtr scene = osg::Node::create();
    osg::ComponentTransformPtr Trans;
    Trans = osg::ComponentTransform::create();
    osg::setName(Trans, std::string("MainTransformationCore"));
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(Trans);
        scene->addChild(createSkeleton());
        scene->addChild(createMesh());
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

	//Setup animation
	setupAnimation();

    return scene;
}

void setupAnimation(void)
{
	Matrix TempMat;

	//Left Elbow
	KeyframeTransformationsSequencePtr LeftElbowKeyframes = KeyframeTransformationsSequence44f::create();

	TempMat.setTransform(Vec3f(2.0,0.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0));
	LeftElbowKeyframes->addKeyframe(TempMat,0.0f);
	TempMat.setTransform(Vec3f(2.0,0.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),1.1));
	LeftElbowKeyframes->addKeyframe(TempMat,3.0f);
	TempMat.setTransform(Vec3f(2.0,0.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0));
	LeftElbowKeyframes->addKeyframe(TempMat,6.0f);
   
	//Left Elbow Animator
    KeyframeAnimatorPtr LeftElbowAnimator = KeyframeAnimator::create();
    beginEditCP(LeftElbowAnimator);
       LeftElbowAnimator->setKeyframeSequence(LeftElbowKeyframes);
    endEditCP(LeftElbowAnimator);

	//Right Elbow
	KeyframeTransformationsSequencePtr RightElbowKeyframes = KeyframeTransformationsSequence44f::create();

	TempMat.setTransform(Vec3f(-2.0,0.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0));
	RightElbowKeyframes->addKeyframe(TempMat,0.0f);
	TempMat.setTransform(Vec3f(-2.0,0.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),-1.1));
	RightElbowKeyframes->addKeyframe(TempMat,3.0f);
	TempMat.setTransform(Vec3f(-2.0,0.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0));
	RightElbowKeyframes->addKeyframe(TempMat,6.0f);
   
	//Right Elbow Animator
    KeyframeAnimatorPtr RightElbowAnimator = KeyframeAnimator::create();
    beginEditCP(RightElbowAnimator);
       RightElbowAnimator->setKeyframeSequence(RightElbowKeyframes);
    endEditCP(RightElbowAnimator);
	
	//Left Shoulder
	KeyframeTransformationsSequencePtr LeftShoulderKeyframes = KeyframeTransformationsSequence44f::create();

	TempMat.setTransform(Vec3f(1.0,-0.5,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0));
	LeftShoulderKeyframes->addKeyframe(TempMat,0.0f);
	TempMat.setTransform(Vec3f(1.0,-0.5,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.6));
	LeftShoulderKeyframes->addKeyframe(TempMat,3.0f);
	TempMat.setTransform(Vec3f(1.0,-0.5,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0));
	LeftShoulderKeyframes->addKeyframe(TempMat,6.0f);
   
	//Left Shoulder Animator
    KeyframeAnimatorPtr LeftShoulderAnimator = KeyframeAnimator::create();
    beginEditCP(LeftShoulderAnimator);
       LeftShoulderAnimator->setKeyframeSequence(LeftShoulderKeyframes);
    endEditCP(LeftShoulderAnimator);
	
	//Right Shoulder
	KeyframeTransformationsSequencePtr RightShoulderKeyframes = KeyframeTransformationsSequence44f::create();

	TempMat.setTransform(Vec3f(-1.0,-0.5,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0));
	RightShoulderKeyframes->addKeyframe(TempMat,0.0f);
	TempMat.setTransform(Vec3f(-1.0,-0.5,0.0),Quaternion(Vec3f(0.0,0.0,1.0),-0.6));
	RightShoulderKeyframes->addKeyframe(TempMat,3.0f);
	TempMat.setTransform(Vec3f(-1.0,-0.5,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0));
	RightShoulderKeyframes->addKeyframe(TempMat,6.0f);
   
	//Right Shoulder Animator
    KeyframeAnimatorPtr RightShoulderAnimator = KeyframeAnimator::create();
    beginEditCP(RightShoulderAnimator);
       RightShoulderAnimator->setKeyframeSequence(RightShoulderKeyframes);
    endEditCP(RightShoulderAnimator);
	
	//Left Hip
	KeyframeTransformationsSequencePtr LeftHipKeyframes = KeyframeTransformationsSequence44f::create();

	TempMat.setTransform(Vec3f(1.0,-1.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0));
	LeftHipKeyframes->addKeyframe(TempMat,0.0f);
	TempMat.setTransform(Vec3f(1.0,-1.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.4));
	LeftHipKeyframes->addKeyframe(TempMat,3.0f);
	TempMat.setTransform(Vec3f(1.0,-1.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0));
	LeftHipKeyframes->addKeyframe(TempMat,6.0f);
   
	//Left Hip Animator
    KeyframeAnimatorPtr LeftHipAnimator = KeyframeAnimator::create();
    beginEditCP(LeftHipAnimator);
       LeftHipAnimator->setKeyframeSequence(LeftHipKeyframes);
    endEditCP(LeftHipAnimator);

	//Right Hip
	KeyframeTransformationsSequencePtr RightHipKeyframes = KeyframeTransformationsSequence44f::create();

	TempMat.setTransform(Vec3f(-1.0,-1.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0));
	RightHipKeyframes->addKeyframe(TempMat,0.0f);
	TempMat.setTransform(Vec3f(-1.0,-1.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),-0.4));
	RightHipKeyframes->addKeyframe(TempMat,3.0f);
	TempMat.setTransform(Vec3f(-1.0,-1.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0));
	RightHipKeyframes->addKeyframe(TempMat,6.0f);
   
	//Right Hip Animator
    KeyframeAnimatorPtr RightHipAnimator = KeyframeAnimator::create();
    beginEditCP(RightHipAnimator);
       RightHipAnimator->setKeyframeSequence(RightHipKeyframes);
    endEditCP(RightHipAnimator);
	

	//Clavicle
	KeyframeTransformationsSequencePtr ClavicleKeyframes = KeyframeTransformationsSequence44f::create();

	TempMat.setTransform(Vec3f(0.0,5.0,0.0));
	ClavicleKeyframes->addKeyframe(TempMat,0.0f);
	TempMat.setTransform(Vec3f(0.0,3.0,0.0));
	ClavicleKeyframes->addKeyframe(TempMat,2.0f);
	TempMat.setTransform(Vec3f(0.0,3.0,0.0));
	ClavicleKeyframes->addKeyframe(TempMat,4.0f);
	TempMat.setTransform(Vec3f(0.0,5.0,0.0));
	ClavicleKeyframes->addKeyframe(TempMat,6.0f);
   
	//Clavicle Animator
    KeyframeAnimatorPtr ClavicleAnimator = KeyframeAnimator::create();
    beginEditCP(ClavicleAnimator);
       ClavicleAnimator->setKeyframeSequence(ClavicleKeyframes);
    endEditCP(ClavicleAnimator);

	//Upper Skeleton Animation
    TheUpperSkeletonAnimation = SkeletonAnimation::create();
    beginEditCP(TheUpperSkeletonAnimation);
		TheUpperSkeletonAnimation->addTransformationAnimator(LeftElbowAnimator, LeftElbow);
		TheUpperSkeletonAnimation->addTransformationAnimator(RightElbowAnimator, RightElbow);
		TheUpperSkeletonAnimation->addTransformationAnimator(LeftShoulderAnimator, LeftShoulder);
		TheUpperSkeletonAnimation->addTransformationAnimator(RightShoulderAnimator, RightShoulder);
		TheUpperSkeletonAnimation->addTransformationAnimator(ClavicleAnimator, Clavicle);
		TheUpperSkeletonAnimation->setSkeleton(ExampleSkeleton);
    endEditCP(TheUpperSkeletonAnimation);

	//Lower Skeleton Animation
    TheLowerSkeletonAnimation = SkeletonAnimation::create();
    beginEditCP(TheLowerSkeletonAnimation);
		TheLowerSkeletonAnimation->addTransformationAnimator(LeftHipAnimator, LeftHip);
		TheLowerSkeletonAnimation->addTransformationAnimator(RightHipAnimator, RightHip);
		TheLowerSkeletonAnimation->setSkeleton(ExampleSkeleton);
    endEditCP(TheLowerSkeletonAnimation);


    //SkeletonBlendedAnimation
    TheSkeletonBlendedAnimation = SkeletonBlendedAnimation::create();
    beginEditCP(TheSkeletonBlendedAnimation);
		TheSkeletonBlendedAnimation->addAnimationBlending(TheUpperSkeletonAnimation, 1);
		TheSkeletonBlendedAnimation->addAnimationBlending(TheLowerSkeletonAnimation, 1);
    endEditCP(TheSkeletonBlendedAnimation);
   


}


ComponentPtr createGLPanel(void)
{
	//Create the nessicary parts for a viewport

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
        LightNode->addChild(createScene());
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
