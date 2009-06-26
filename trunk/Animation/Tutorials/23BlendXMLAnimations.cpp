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

//IO
#include <OpenSG/Toolbox/OSGFCFileHandler.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

// For the skeleton
SkeletonBlendedAnimationPtr TheSkeletonBlendedAnimation;
SkeletonAnimationPtr TheWalkingAnimation;
SkeletonAnimationPtr TheTouchScreenAnimation;
Real32 BlendWalking = 1;
Real32 BlendTouchScreen = 0;
AnimationAdvancerPtr TheAnimationAdvancer;

std::vector<NodePtr> UnboundGeometries;
std::vector<NodePtr> SkeletonNodes;
std::vector<NodePtr> MeshNodes;


////JointPtr Pelvis,LeftHip,RightHip,LeftKnee,RightKnee,LeftFoot,RightFoot,LeftToes,RightToes, Clavicle, LeftShoulder,RightShoulder,LeftElbow,RightElbow,LeftHand,RightHand,LeftFingers,RightFingers,Head; 
//SkeletonPtr ExampleSkeleton;
//// The pointer to the geometry core
//GeometryPtr geo;

// forward declaration so we can have the interesting stuff upfront
ComponentPtr createGLPanel(void);
bool animationPaused = false;

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

	   //Toggle animation
	   if(e.getKey() == KeyEvent::KEY_SPACE)
	   {
		   if(animationPaused)
			   animationPaused = false;
		   else
			   animationPaused = true;
	   }


	   //Toggle bind pose
	   if(e.getKey() == KeyEvent::KEY_B)
	   {
		   if(e.getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
		   {
			   //Toggle mesh
			   for(int i(0); i < UnboundGeometries.size(); ++i)
			   {
				   if(UnboundGeometries[i]->getTravMask() == 0)
				   {
					   beginEditCP(UnboundGeometries[i], Node::TravMaskFieldMask);
							UnboundGeometries[i]->setTravMask(1);
						endEditCP(UnboundGeometries[i], Node::TravMaskFieldMask);
				   } 
				   else
				   {
					   beginEditCP(UnboundGeometries[i], Node::TravMaskFieldMask);
							UnboundGeometries[i]->setTravMask(0);
						endEditCP(UnboundGeometries[i], Node::TravMaskFieldMask);
				   }
			   }
		   }
		   else
		   {
			   //Toggle skeleton
			   for(int i(0); i < SkeletonNodes.size(); ++i)
			   {
				   if(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore())->getDrawBindPose() == false)
				   {
					   beginEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore()), SkeletonDrawable::DrawBindPoseFieldMask);
						 SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore())->setDrawBindPose(true);
						endEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore()), SkeletonDrawable::DrawBindPoseFieldMask);
				   } 
				   else
				   {
					   beginEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore()), SkeletonDrawable::DrawBindPoseFieldMask);
						 SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore())->setDrawBindPose(false);
						endEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore()), SkeletonDrawable::DrawBindPoseFieldMask);
				   }
			   }
		   }
	   }

	   //Toggle current pose
	   if(e.getKey() == KeyEvent::KEY_P)
	   {
		   if(e.getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
		   {
			   //Toggle mesh
			   for(int i(0); i < MeshNodes.size(); ++i)
			   {
				   if(MeshNodes[i]->getTravMask() == 0)
				   {
					   beginEditCP(MeshNodes[i], Node::TravMaskFieldMask);
							MeshNodes[i]->setTravMask(1);
						endEditCP(MeshNodes[i], Node::TravMaskFieldMask);
				   } 
				   else
				   {
					   beginEditCP(MeshNodes[i], Node::TravMaskFieldMask);
							MeshNodes[i]->setTravMask(0);
						endEditCP(MeshNodes[i], Node::TravMaskFieldMask);
				   }
			   }
		   }
		   else
		   {
			   //Toggle skeleton
			   for(int i(0); i < SkeletonNodes.size(); ++i)
			   {
				   if(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore())->getDrawPose() == false)
				   {
					   beginEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore()), SkeletonDrawable::DrawPoseFieldMask);
						 SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore())->setDrawPose(true);
						endEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore()), SkeletonDrawable::DrawPoseFieldMask);
				   } 
				   else
				   {
					   beginEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore()), SkeletonDrawable::DrawPoseFieldMask);
						 SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore())->setDrawPose(false);
						endEditCP(SkeletonDrawable::Ptr::dcast(SkeletonNodes[i]->getCore()), SkeletonDrawable::DrawPoseFieldMask);
				   }
			   }
		   }
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
		if(!animationPaused)
		{
			ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->update(e.getElapsedTime());

			TheSkeletonBlendedAnimation->update(TheAnimationAdvancer);
		}
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










	
	//Import scene from XML
	ChunkMaterialPtr ExampleMaterial;
	std::vector<SkeletonPtr> SkeletonPtrs;
	std::vector<SkeletonBlendedGeometryPtr> SkeletonBlendedGeometryPtrs;
	std::vector<GeometryPtr> GeometryPtrs;

	//Skeleton materaial
	LineChunkPtr SkelLineChunk = LineChunk::create();
	beginEditCP(SkelLineChunk);
		SkelLineChunk->setWidth(0.0f);
		SkelLineChunk->setSmooth(true);
	endEditCP(SkelLineChunk);

	ChunkMaterialPtr SkelMaterial = ChunkMaterial::create();
	beginEditCP(SkelMaterial, ChunkMaterial::ChunksFieldMask);
		SkelMaterial->addChunk(SkelLineChunk);
	endEditCP(SkelMaterial, ChunkMaterial::ChunksFieldMask);

	//LOAD FIRST ANIMATION
	FCFileType::FCPtrStore NewContainers;
	NewContainers = FCFileHandler::the()->read(Path("./Data/23WalkingAnimation.xml"));
	FCFileType::FCPtrStore::iterator Itor;
    for(Itor = NewContainers.begin() ; Itor != NewContainers.end() ; ++Itor)
    {
		if( (*Itor)->getType() == (ChunkMaterial::getClassType()))
		{
			ExampleMaterial = (ChunkMaterial::Ptr::dcast(*Itor));
		}
		if( (*Itor)->getType() == (Skeleton::getClassType()))
		{
			SkeletonPtrs.push_back(Skeleton::Ptr::dcast(*Itor));
		}
		if( (*Itor)->getType() == (SkeletonBlendedGeometry::getClassType()))
		{
			SkeletonBlendedGeometryPtrs.push_back(SkeletonBlendedGeometry::Ptr::dcast(*Itor));
		}
		if( (*Itor)->getType().isDerivedFrom(SkeletonAnimation::getClassType()))
		{
			TheWalkingAnimation = (SkeletonAnimation::Ptr::dcast(*Itor));
		}
		if( (*Itor)->getType() == (Geometry::getClassType()))
		{
			GeometryPtrs.push_back(Geometry::Ptr::dcast(*Itor));
		}
    }

	//LOAD SECOND ANIMATION
	NewContainers = FCFileHandler::the()->read(Path("./Data/23SamAnimation.xml"));
    for(Itor = NewContainers.begin() ; Itor != NewContainers.end() ; ++Itor)
    {
		if( (*Itor)->getType().isDerivedFrom(SkeletonAnimation::getClassType()))
		{
			TheTouchScreenAnimation = (SkeletonAnimation::Ptr::dcast(*Itor));
		}
    }

	//Blend the two animations
    TheSkeletonBlendedAnimation = SkeletonBlendedAnimation::create();
    beginEditCP(TheSkeletonBlendedAnimation);
		TheSkeletonBlendedAnimation->addAnimationBlending(TheWalkingAnimation, BlendWalking, false);
		TheSkeletonBlendedAnimation->addAnimationBlending(TheTouchScreenAnimation, BlendTouchScreen, false);
    endEditCP(TheSkeletonBlendedAnimation);


	
	//Create unbound geometry Node (to show the mesh in its bind pose)
	for (int i(0); i < GeometryPtrs.size(); ++i)
	{
		NodePtr UnboundGeometry = Node::create();
		beginEditCP(UnboundGeometry, Node::CoreFieldMask);
			UnboundGeometry->setCore(GeometryPtrs[i]);
		endEditCP(UnboundGeometry, Node::CoreFieldMask);

		UnboundGeometries.push_back(UnboundGeometry);
	}


	//Create skeleton nodes
	for (int i(0); i < SkeletonPtrs.size(); ++i)
	{
		//SkeletonDrawer
		SkeletonDrawablePtr ExampleSkeletonDrawable = osg::SkeletonDrawable::create();
		beginEditCP(ExampleSkeletonDrawable, SkeletonDrawable::SkeletonFieldMask | SkeletonDrawable::MaterialFieldMask | SkeletonDrawable::DrawPoseFieldMask | SkeletonDrawable::PoseColorFieldMask  | SkeletonDrawable::DrawBindPoseFieldMask | SkeletonDrawable::BindPoseColorFieldMask);
			ExampleSkeletonDrawable->setSkeleton(SkeletonPtrs[i]);
			ExampleSkeletonDrawable->setMaterial(SkelMaterial);
			ExampleSkeletonDrawable->setDrawPose(true);								  //By default we draw the current skeleton
			ExampleSkeletonDrawable->setPoseColor(Color4f(1.0, 0.0, 1.0, 1.0));       //Set color of current skeleton
			ExampleSkeletonDrawable->setDrawBindPose(true);                           //By default we draw the bind pose skeleton
			ExampleSkeletonDrawable->setBindPoseColor(Color4f(1.0, 1.0, 0.0, 1.0));   //Set color of bind pose skeleton
		endEditCP(ExampleSkeletonDrawable, SkeletonDrawable::SkeletonFieldMask | SkeletonDrawable::MaterialFieldMask | SkeletonDrawable::DrawPoseFieldMask | SkeletonDrawable::PoseColorFieldMask  | SkeletonDrawable::DrawBindPoseFieldMask | SkeletonDrawable::BindPoseColorFieldMask);
		
		//Skeleton Node
		NodePtr SkeletonNode = osg::Node::create();
		beginEditCP(SkeletonNode, Node::CoreFieldMask);
			SkeletonNode->setCore(ExampleSkeletonDrawable);
		endEditCP(SkeletonNode, Node::CoreFieldMask);

		SkeletonNodes.push_back(SkeletonNode);
	}



	//Create skeleton blended geometry nodes
	for (int i(0); i < SkeletonBlendedGeometryPtrs.size(); ++i)
	{
		NodePtr MeshNode = osg::Node::create();
		beginEditCP(MeshNode, Node::CoreFieldMask);
			MeshNode->setCore(SkeletonBlendedGeometryPtrs[i]);
		endEditCP(MeshNode, Node::CoreFieldMask);

		MeshNodes.push_back(MeshNode);
	}



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
    UpperAnimationSliderRangeModel->setMinimum(0);
    UpperAnimationSliderRangeModel->setMaximum(100);
    UpperAnimationSliderRangeModel->setValue(BlendWalking * 100);
    UpperAnimationSliderRangeModel->setExtent(0);
    
    //Create the upper animation slider
    LabelPtr TempLabel;
    SliderPtr UpperAnimationSlider = Slider::create();
    beginEditCP(UpperAnimationSlider, Slider::LabelMapFieldMask | Slider::PreferredSizeFieldMask | Slider::MajorTickSpacingFieldMask | Slider::MinorTickSpacingFieldMask | Slider::SnapToTicksFieldMask | Slider::DrawLabelsFieldMask | Slider::RangeModelFieldMask);

		TempLabel = Label::Ptr::dcast(UpperAnimationSlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("0.0"); endEditCP(TempLabel, Label::TextFieldMask);
        UpperAnimationSlider->getLabelMap()[0] = TempLabel;

        TempLabel = Label::Ptr::dcast(UpperAnimationSlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("1.0"); endEditCP(TempLabel, Label::TextFieldMask);
        UpperAnimationSlider->getLabelMap()[100] = TempLabel;


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
    LowerAnimationSliderRangeModel->setMinimum(0);
    LowerAnimationSliderRangeModel->setMaximum(100);
    LowerAnimationSliderRangeModel->setValue(BlendTouchScreen * 100);
    LowerAnimationSliderRangeModel->setExtent(0);
    
    //Create the lower animation slider
    SliderPtr LowerAnimationSlider = Slider::create();
    beginEditCP(LowerAnimationSlider, Slider::LabelMapFieldMask | Slider::PreferredSizeFieldMask | Slider::MajorTickSpacingFieldMask | Slider::MinorTickSpacingFieldMask | Slider::SnapToTicksFieldMask | Slider::DrawLabelsFieldMask | Slider::RangeModelFieldMask);

        TempLabel = Label::Ptr::dcast(LowerAnimationSlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("0.0"); endEditCP(TempLabel, Label::TextFieldMask);
        LowerAnimationSlider->getLabelMap()[0] = TempLabel;

        TempLabel = Label::Ptr::dcast(LowerAnimationSlider->getLabelPrototype()->shallowCopy());
        beginEditCP(TempLabel, Label::TextFieldMask); TempLabel->setText("1.0"); endEditCP(TempLabel, Label::TextFieldMask);
        LowerAnimationSlider->getLabelMap()[100] = TempLabel;


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

NodePtr createScene(void)
{
	//Make Main Scene Node
    NodePtr scene = osg::Node::create();
    osg::ComponentTransformPtr Trans;
    Trans = osg::ComponentTransform::create();
    osg::setName(Trans, std::string("MainTransformationCore"));
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(Trans);

		for (int i(0); i < SkeletonNodes.size(); ++i)
		{
			scene->addChild(SkeletonNodes[i]);
		}

		for (int i(0); i < UnboundGeometries.size(); ++i)
		{
			scene->addChild(UnboundGeometries[i]);
		}

		for (int i(0); i < MeshNodes.size(); ++i)
		{
			scene->addChild(MeshNodes[i]);
		}

    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    return scene;
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
		TheGLViewport->setPreferredSize(Vec2f(1024.0f,768.0f));
	endEditCP(TheGLViewport, GLViewport::PortFieldMask | GLViewport::PreferredSizeFieldMask | GLViewport::BordersFieldMask);
	
    TheGLViewport->showAll();

    return TheGLViewport;
}
