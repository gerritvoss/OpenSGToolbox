// 
// OpenSGToolbox Tutorial: 01Animation
//
// Demonstrates a simple animation using transformation keyframes. 
//


// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>

#include <OpenSG/OSGSimpleMaterial.h>

#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGTypeFactory.h>
#include <OpenSG/OSGFieldFactory.h>

#include <OpenSG/OSGFieldContainerFactory.h>
#include <OpenSG/OSGSimpleAttachments.h>

#include <OpenSG/Toolbox/OSGFieldContainerUtils.h>

// Input
#include <OpenSG/Input/OSGKeyListener.h>
#include <OpenSG/Input/OSGWindowUtils.h>

//Animation
#include <OpenSG/Animation/OSGKeyframeSequences.h>
#include <OpenSG/Animation/OSGKeyframeAnimator.h>
#include <OpenSG/Animation/OSGFieldAnimation.h>
#include <OpenSG/Animation/OSGAnimationGroup.h>

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
   virtual void animationStarted(const AnimationEventPtr e)
   {
       std::cout << "Animation Started"  << std::endl;
   }

   virtual void animationStopped(const AnimationEventPtr e)
   {
       std::cout << "Animation Stopped"  << std::endl;
   }

   virtual void animationPaused(const AnimationEventPtr e)
   {
       std::cout << "Animation Paused"  << std::endl;
   }

   virtual void animationUnpaused(const AnimationEventPtr e)
   {
       std::cout << "Animation Unpaused"  << std::endl;
   }

   virtual void animationEnded(const AnimationEventPtr e)
   {
       std::cout << "Animation Ended"  << std::endl;
   }

   virtual void animationCycled(const AnimationEventPtr e)
   {
       std::cout << "Animation Cycled.  Cycle Count: " << AnimationPtr::dcast(e->getSource())->getCycles() << std::endl;
   }

};

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerPtr TutorialWindowEventProducer;

Time TimeLastIdle;
AnimationGroupPtr TheAnimationGroup;
MaterialPtr TheTorusMaterial;


KeyframeTransformationsSequencePtr TransformationKeyframes;
KeyframeColorsSequencePtr ColorKeyframes;
KeyframeVectorsSequencePtr VectorKeyframes;
KeyframeRotationsSequencePtr RotationKeyframes;

// Create a class to allow for the use of the keyboard shortucts 
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           TutorialWindowEventProducer->closeWindow();
       }

       switch(e->getKey())
       {
       case KeyEvent::KEY_SPACE:
           TheAnimationGroup->pause(!TheAnimationGroup->isPaused());
           break;
       case KeyEvent::KEY_ENTER:
           TheAnimationGroup->attachUpdateProducer(TutorialWindowEventProducer->editEventProducer());
           TheAnimationGroup->start();
           break;
       case KeyEvent::KEY_MINUS:
           beginEditCP(TheAnimationGroup, AnimationGroup::ScaleFieldMask);
               TheAnimationGroup->setScale(osgMax(TheAnimationGroup->getScale()-0.1f, 0.0f));
           endEditCP(TheAnimationGroup, AnimationGroup::ScaleFieldMask);
           break;
       case KeyEvent::KEY_PLUS:
       case KeyEvent::KEY_EQUALS:
           beginEditCP(TheAnimationGroup, AnimationGroup::ScaleFieldMask);
               TheAnimationGroup->setScale(osgMax(TheAnimationGroup->getScale()+0.1f, 0.0f));
           endEditCP(TheAnimationGroup, AnimationGroup::ScaleFieldMask);
           break;
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

// Initialize GLUT & OpenSG and set up the scene
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
    mgr->setWindow(TutorialWindowEventProducer->getWindow());

    //Torus Material
    TheTorusMaterial = SimpleMaterial::create();
    beginEditCP(TheTorusMaterial);
        SimpleMaterialPtr::dcast(TheTorusMaterial)->setAmbient(Color3f(0.3,0.3,0.3));
        SimpleMaterialPtr::dcast(TheTorusMaterial)->setDiffuse(Color3f(0.7,0.7,0.7));
        SimpleMaterialPtr::dcast(TheTorusMaterial)->setSpecular(Color3f(1.0,1.0,1.0));
        SimpleMaterialPtr::dcast(TheTorusMaterial)->setShininess(20.0);
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
    setName(TorusNodeTrans, std::string("TorusNodeTransformationCore"));

    beginEditCP(TorusNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        TorusNode->setCore(TorusNodeTrans);
        TorusNode->addChild(TorusGeometryNode);
    endEditCP  (TorusNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

    //Make Main Scene Node
    NodePtr scene = Node::create();
    ComponentTransformPtr Trans;
    Trans = ComponentTransform::create();
    setName(Trans, std::string("MainTransformationCore"));
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        scene->setCore(Trans);
 
        // add the torus as a child
        scene->addChild(TorusNode);
    }
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    setupAnimation();

    // tell the manager what to manage
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();

    
    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.5);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "OpenSG 07AnimationGroup Window");

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
    //Color Keyframe Sequence
    ColorKeyframes = KeyframeColorsSequence3f::create();
    ColorKeyframes->addKeyframe(Color4f(1.0f,0.0f,0.0f,1.0f),0.0f);
    ColorKeyframes->addKeyframe(Color4f(0.0f,1.0f,0.0f,1.0f),2.0f);
    ColorKeyframes->addKeyframe(Color4f(0.0f,0.0f,1.0f,1.0f),4.0f);
    ColorKeyframes->addKeyframe(Color4f(1.0f,0.0f,0.0f,1.0f),6.0f);
    
    //Color Animator
    KeyframeAnimatorPtr TheColorAnimator = KeyframeAnimator::create();
    beginEditCP(TheColorAnimator, KeyframeAnimator::KeyframeSequenceFieldMask);
        TheColorAnimator->setKeyframeSequence(ColorKeyframes);
    endEditCP(TheColorAnimator, KeyframeAnimator::KeyframeSequenceFieldMask);
    
    //Color Animation
    FieldAnimationPtr TheColorAnimation = FieldAnimation::create();
    beginEditCP(TheColorAnimation);
        TheColorAnimation->setAnimator(TheColorAnimator);
        TheColorAnimation->setInterpolationType(LINEAR_INTERPOLATION);
        TheColorAnimation->setCycling(2);
    endEditCP(TheColorAnimation);
    TheColorAnimation->setAnimatedField(TheTorusMaterial, std::string("diffuse"));

	//Vector Keyframe Sequence
    VectorKeyframes = KeyframeVectorsSequence3f::create();
    VectorKeyframes->addKeyframe(Vec3f(0.0f,0.0f,0.0f),0.0f);
    VectorKeyframes->addKeyframe(Vec3f(0.0f,1.0f,0.0f),1.0f);
    VectorKeyframes->addKeyframe(Vec3f(1.0f,1.0f,0.0f),2.0f);
    VectorKeyframes->addKeyframe(Vec3f(1.0f,0.0f,0.0f),3.0f);
    VectorKeyframes->addKeyframe(Vec3f(0.0f,0.0f,0.0f),4.0f);
    
    
    //Vector Animator
    KeyframeAnimatorPtr TheVectorAnimator = KeyframeAnimator::create();
    beginEditCP(TheVectorAnimator, KeyframeAnimator::KeyframeSequenceFieldMask);
        TheVectorAnimator->setKeyframeSequence(VectorKeyframes);
    endEditCP(TheVectorAnimator, KeyframeAnimator::KeyframeSequenceFieldMask);
    
    //Vector Animation
    FieldAnimationPtr TheVectorAnimation = FieldAnimation::create();
    beginEditCP(TheVectorAnimation);
        TheVectorAnimation->setAnimator(TheVectorAnimator);
        TheVectorAnimation->setInterpolationType(LINEAR_INTERPOLATION);
        TheVectorAnimation->setCycling(2);
    endEditCP(TheVectorAnimation);
	//TheVectorAnimation->setAnimatedField(getFieldContainer("Transform",std::string("TorusNodeVectorCore")), std::string("matrix"));
    
	//Transformation Keyframe Sequence
    TransformationKeyframes = KeyframeTransformationsSequence44f::create();
	Matrix TempMat;
	TempMat.setTransform(Vec3f(0.0f,0.0f,0.0f), Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*0.0));
    TransformationKeyframes->addKeyframe(TempMat,0.0f);
	TempMat.setTransform(Vec3f(0.0f,1.0f,0.0f), Quaternion(Vec2f(0.0f,1.0f,0.0f), 3.14159f*0.5));
    TransformationKeyframes->addKeyframe(TempMat,1.0f);
	TempMat.setTransform(Vec3f(1.0f,1.0f,0.0f), Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*1.0));
    TransformationKeyframes->addKeyframe(TempMat,2.0f);
	TempMat.setTransform(Vec3f(1.0f,0.0f,0.0f), Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*1.5));
    TransformationKeyframes->addKeyframe(TempMat,3.0f);
	TempMat.setTransform(Vec3f(0.0f,0.0f,0.0f), Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*0.0));
    TransformationKeyframes->addKeyframe(TempMat,4.0f);
    
    //Transformation Animator
    KeyframeAnimatorPtr TheTransformationAnimator = KeyframeAnimator::create();
    beginEditCP(TheTransformationAnimator, KeyframeAnimator::KeyframeSequenceFieldMask);
        TheTransformationAnimator->setKeyframeSequence(TransformationKeyframes);
    endEditCP(TheTransformationAnimator, KeyframeAnimator::KeyframeSequenceFieldMask);
    
    //Transformation Animation
    FieldAnimationPtr TheTransformationAnimation = FieldAnimation::create();
    beginEditCP(TheTransformationAnimation);
        TheTransformationAnimation->setAnimator(TheTransformationAnimator);
        TheTransformationAnimation->setInterpolationType(LINEAR_INTERPOLATION);
        TheTransformationAnimation->setCycling(2);
    endEditCP(TheTransformationAnimation);
	TheTransformationAnimation->setAnimatedField(getFieldContainer("Transform",std::string("TorusNodeTransformationCore")), std::string("matrix"));

    TheAnimationGroup = AnimationGroup::create();
    beginEditCP(TheAnimationGroup);
        TheAnimationGroup->getAnimations().push_back(TheColorAnimation);
        TheAnimationGroup->getAnimations().push_back(TheTransformationAnimation);
    endEditCP(TheAnimationGroup);
    TheAnimationGroup->attachUpdateProducer(TutorialWindowEventProducer->editEventProducer());
    TheAnimationGroup->start();
}

