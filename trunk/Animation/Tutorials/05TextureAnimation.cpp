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

#include <OpenSG/OSGChunkMaterial.h>

#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGTypeFactory.h>
#include <OpenSG/OSGFieldFactory.h>

#include <OpenSG/OSGFieldContainerFactory.h>
#include <OpenSG/OSGSimpleAttachments.h>

#include <OpenSG/Toolbox/OSGFieldContainerUtils.h>

// Input
#include <OpenSG/Input/OSGKeyListener.h>
#include <OpenSG/Input/OSGWindowAdapter.h>
#include <OpenSG/Input/OSGWindowUtils.h>

//Animation
#include <OpenSG/Animation/OSGKeyframeSequences.h>
#include <OpenSG/Animation/OSGKeyframeAnimator.h>
#include <OpenSG/Animation/OSGFieldAnimation.h>
#include <OpenSG/Animation/OSGElapsedTimeAnimationAdvancer.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE


// forward declaration so we can have the interesting stuff upfront
void setupAnimation(void);
void display(void);
void reshape(Vec2f Size);

class TutorialAnimationListener : public AnimationListener
{
public:
   virtual void animationStarted(const AnimationEvent& e)
   {
   }

   virtual void animationStopped(const AnimationEvent& e)
   {
   }

   virtual void animationPaused(const AnimationEvent& e)
   {
   }

   virtual void animationUnpaused(const AnimationEvent& e)
   {
   }

   virtual void animationEnded(const AnimationEvent& e)
   {
   }

   virtual void animationCycled(const AnimationEvent& e)
   {
       std::cout << "Animation Cycled.  Cycle Count: " << e.getAnimation()->getCycles() << std::endl;
   }

};

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

Time TimeLastIdle;
FieldAnimationPtr TutorialTextureAnimation;
TutorialAnimationListener TutorialTextureAnimationListener;
AnimationAdvancerPtr TutorialTextureAnimationAdvancer;

KeyframeAnimatorPtr TutorialTextureAnimator;

bool ExitApp = false;

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
		ElapsedTimeAnimationAdvancer::Ptr::dcast(TutorialTextureAnimationAdvancer)->update(e.getElapsedTime());

		TutorialTextureAnimation->update(TutorialTextureAnimationAdvancer);
    }
};

// Initialize GLUT & OpenSG and set up the scene
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

	
    TutorialWindowEventProducer->openWindow(Pnt2f(0,0),
                                        Vec2f(1280,1024),
                                        "OpenSG 05TextureAnimation Window");

    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindowEventProducer->getWindow());

    //Torus Material
    ChunkMaterialPtr TheTorusMaterial = ChunkMaterial::create();
    beginEditCP(TheTorusMaterial);
        SimpleMaterialPtr::dcast(TheTorusMaterial)->setAmbient(Color3f(0.3,0.3,0.3));
        SimpleMaterialPtr::dcast(TheTorusMaterial)->setDiffuse(Color3f(0.7,0.7,0.7));
        SimpleMaterialPtr::dcast(TheTorusMaterial)->setSpecular(Color3f(1.0,1.0,1.0));
    endEditCP(TheTorusMaterial);

    //Torus Geometry
    GeometryPtr TorusGeometry = makeTorusGeo(.5, 2, 32, 32);
    beginEditCP(TorusGeometry);
        TorusGeometry->setMaterial(TheTorusMaterial);
    endEditCP  (TorusGeometry);
    
    NodePtr TorusGeometryNode = Node::create();
    beginEditCP(TorusGeometryNode, Node::CoreFieldMask);
        TorusGeometryNode->setCore(TorusGeometry);
    endEditCP  (TorusGeometryNode, Node::CoreFieldMask);

    //Make Torus Node
    NodePtr TorusNode = Node::create();
    TransformPtr TorusNodeTrans;
    TorusNodeTrans = Transform::create();

    beginEditCP(TorusNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        TorusNode->setCore(TorusNodeTrans);
        TorusNode->addChild(TorusGeometryNode);
    endEditCP  (TorusNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

    //Make Main Scene Node
    NodePtr scene = Node::create();
    ComponentTransformPtr Trans;
    Trans = ComponentTransform::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(Trans);
 
        // add the torus as a child
        scene->addChild(TorusNode);
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    //Setup the Animation
    setupAnimation();

    // tell the manager what to manage
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();

    TutorialTextureAnimation->start();
    
    while(!ExitApp)
    {
        TutorialWindowEventProducer->update();
        TutorialWindowEventProducer->draw();
    }

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
    std::vector<Path> _ImagePaths;
    std::vector<TextureChunkPtr> _Textures;
    //Make the textures
    for(UInt32 i(0) ; i<_ImagePaths.size(); ++i)
    {
    }

    //Color Keyframe Sequence
    TextureKeyframes = KeyframeColorsSequence3f::create();
    for(UInt32 i(0) ; i<_Textures.size(); ++i)
    {
    }
    
    //Animator
    TutorialTextureAnimator = KeyframeAnimator::create();
    beginEditCP(TutorialTextureAnimator, KeyframeAnimator::KeyframeSequenceFieldMask);
        TutorialTextureAnimator->setKeyframeSequence(TextureKeyframes);
    endEditCP(TutorialTextureAnimator, KeyframeAnimator::KeyframeSequenceFieldMask);
    
    //Animation
    TutorialTextureAnimation = FieldAnimation::create();
    beginEditCP(TutorialTextureAnimation);
        TutorialTextureAnimation->setAnimator(TutorialTextureAnimator);
        TutorialTextureAnimation->setInterpolationType(STEP_INTERPOLATION);
        TutorialTextureAnimation->setCycling(-1);
    endEditCP(TutorialTextureAnimation);
	//TutorialTextureAnimation->setAnimatedField(getFieldContainer("Transform",std::string("TorusNodeTransformationCore")), std::string("matrix"));

    //Animation Listener
    TutorialTextureAnimation->addAnimationListener(&TutorialTextureAnimationListener);

    //Animation Advancer
    TutorialTextureAnimationAdvancer = ElapsedTimeAnimationAdvancer::create();
    beginEditCP(TutorialTextureAnimationAdvancer);
    ElapsedTimeAnimationAdvancer::Ptr::dcast(TutorialTextureAnimationAdvancer)->setStartTime( 0.0 );
    beginEditCP(TutorialTextureAnimationAdvancer);
}
