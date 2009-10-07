// 
// OpenSGToolbox Tutorial: 15LoadXMLAnimation 
//
// Loads a skeleton and a skeleton animation from an
// XML file.
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
#include <OpenSG/Input/OSGWindowUtils.h>

// Input
#include <OpenSG/Input/OSGKeyListener.h>


#include <OpenSG/OSGSimpleMaterial.h>

#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGTypeFactory.h>
#include <OpenSG/OSGFieldFactory.h>

#include <OpenSG/OSGFieldContainerFactory.h>
#include <OpenSG/OSGSimpleAttachments.h>

#include <OpenSG/Toolbox/OSGFieldContainerUtils.h>

#include <OpenSG/Animation/OSGKeyframeSequences.h>
#include <OpenSG/Animation/OSGKeyframeAnimator.h>
#include <OpenSG/Animation/OSGFieldAnimation.h>
#include <OpenSG/Animation/OSGElapsedTimeAnimationAdvancer.h>

#include <OpenSG/Toolbox/OSGFCFileHandler.h>


// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;

AnimationPtr TheAnimation;
AnimationAdvancerPtr TheAnimationAdvancer;
MaterialPtr TheTorusMaterial;
GeometryPtr TorusGeometry;

bool animationPaused = false;

// forward declaration so we can have the interesting stuff upfront
void setupAnimation(void);
void display(void);
void reshape(Vec2f Size);

/*
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
};*/
/*
class TutorialAnimationListener : public AnimationListener
{
public:
   virtual void animationStarted(const AnimationEventPtr e)
   {
   }

   virtual void animationStopped(const AnimationEventPtr e)
   {
   }

   virtual void animationPaused(const AnimationEventPtr e)
   {
   }

   virtual void animationUnpaused(const AnimationEventPtr e)
   {
   }

   virtual void animationEnded(const AnimationEventPtr e)
   {
   }

   virtual void animationCycled(const AnimationEventPtr e)
   {
       std::cout << "Animation Cycled.  Cycle Count: " << AnimationPtr::dcast(e)->getCycles() << std::endl;
   }

};*/


// Create a class to allow for the use of the keyboard shortcuts 
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventPtr e)
   {
	   //Exit
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           TutorialWindowEventProducer->closeWindow();
       }

	   //Toggle animation
	   if(e->getKey() == KeyEvent::KEY_SPACE)
	   {
		   if(animationPaused)
			   animationPaused = false;
		   else
			   animationPaused = true;
	   }
   }

   virtual void keyReleased(const KeyEventPtr e)
   {
   }

   virtual void keyTyped(const KeyEventPtr e)
   {
   }
};

class TutorialMouseListener : public MouseListener
{
  public:
    virtual void mouseClicked(const MouseEventPtr e)
    {
    }
    virtual void mouseEntered(const MouseEventPtr e)
    {
    }
    virtual void mouseExited(const MouseEventPtr e)
    {
    }
    virtual void mousePressed(const MouseEventPtr e)
    {
            mgr->mouseButtonPress(e->getButton(), e->getLocation().x(), e->getLocation().y());
    }
    virtual void mouseReleased(const MouseEventPtr e)
    {
           mgr->mouseButtonRelease(e->getButton(), e->getLocation().x(), e->getLocation().y());
    }
};

class TutorialMouseMotionListener : public MouseMotionListener
{
  public:
    virtual void mouseMoved(const MouseEventPtr e)
    {
            mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
    }

    virtual void mouseDragged(const MouseEventPtr e)
    {
            mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
    }
};

class TutorialUpdateListener : public UpdateListener
{
  public:
    virtual void update(const UpdateEventPtr e)
    {
		if(!animationPaused)
		{
			ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->update(e->getElapsedTime());

			TheAnimation->update(TheAnimationAdvancer);
		}
    }
};


KeyframeAnimatorPtr TheAnimator;
KeyframeTransformationsSequencePtr TransformationKeyframes;
KeyframeColorsSequencePtr ColorKeyframes;
KeyframeVectorsSequencePtr VectorKeyframes;
KeyframeRotationsSequencePtr RotationKeyframes;

// Initialize OpenSG and set up the scene
int main(int argc, char **argv)
{
	//Print key command info
	std::cout << "\n\nKEY COMMANDS:" << std::endl;
	std::cout << "space   Play/Pause the animation" << std::endl;
	std::cout << "CTRL-Q  Exit\n\n" << std::endl;

    // OSG init
    osgInit(argc,argv);


    // Set up Window
    TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

    TutorialUpdateListener TheTutorialUpdateListener;  

    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);
    TutorialWindowEventProducer->addUpdateListener(&TheTutorialUpdateListener);

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

    //Torus Geometry
    TorusGeometry = makeTorusGeo(.5, 2, 16, 16);
    
    NodePtr TorusGeometryNode = Node::create();
    beginEditCP(TorusGeometryNode, Node::CoreFieldMask);
        TorusGeometryNode->setCore(TorusGeometry);
    endEditCP  (TorusGeometryNode, Node::CoreFieldMask);

    //Make Torus Node
    NodePtr TorusNode = Node::create();
    TransformPtr TorusNodeTrans;
    TorusNodeTrans = Transform::create();
    setName(TorusNodeTrans, std::string("TorusNodeTransformationCore"));

    beginEditCP(TorusNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        TorusNode->setCore(TorusNodeTrans);
        TorusNode->addChild(TorusGeometryNode);
    endEditCP  (TorusNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

    //Make Main Scene Node
    NodePtr scene = Node::create();
    //ComponentTransformPtr Trans;
    //Trans = ComponentTransform::create();
    //setName(Trans, std::string("MainTransformationCore"));
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        scene->setCore(Group::create());
 
        // add the torus as a child
        scene->addChild(TorusNode);
    }
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);


	setupAnimation();
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();
    TheAnimationAdvancer->start();


    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
                        WinSize,
                                        "15LoadXMLAnimation");

    //Enter main Loop
    TutorialWindowEventProducer->mainLoop();

    osgExit();


    return 0;
}

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

void setupAnimation(void)
{
	//Read animation data from XML file
	FCFileType::FCPtrStore NewContainers;
	NewContainers = FCFileHandler::the()->read(Path("./Data/15TestAnimations.xml"));

	FCFileType::FCPtrStore::iterator Itor;
    for(Itor = NewContainers.begin() ; Itor != NewContainers.end() ; ++Itor)
    {
		if( (*Itor)->getType().isDerivedFrom(Animation::getClassType()))
		{
			//Set the animation to the one we just read in
			TheAnimation = (Animation::Ptr::dcast(*Itor));
		}
		else if( (*Itor)->getType() == (SimpleMaterial::getClassType()))
		{
			//Set torus material
			TheTorusMaterial = (SimpleMaterial::Ptr::dcast(*Itor));
			
			//Attach torus material to torus geometry
			beginEditCP(TorusGeometry);
				TorusGeometry->setMaterial(TheTorusMaterial);
			endEditCP  (TorusGeometry);
		}
    }

    //Animation Advancer
    TheAnimationAdvancer = ElapsedTimeAnimationAdvancer::create();
    beginEditCP(TheAnimationAdvancer);
    ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->setStartTime( 0.0 );
    beginEditCP(TheAnimationAdvancer);
}
