// 
// OpenSGToolbox Tutorial: 01Animation
//
// Demonstrates a simple animation using transformation keyframes. 
//


// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// Methods to create simple geometry: boxes, spheres, tori etc.
#include "OSGSimpleGeometry.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"

#include "OSGSimpleMaterial.h"

#include "OSGComponentTransform.h"
#include "OSGTransform.h"
#include "OSGTypeFactory.h"


#include "OSGFieldContainerFactory.h"
#include "OSGNameAttachment.h"

#include "OSGFieldContainerUtils.h"

// Input
#include "OSGKeyListener.h"
#include "OSGWindowUtils.h"

//Animation
#include "OSGKeyframeSequences.h"
#include "OSGBlendedKeyframeAnimator.h"
#include "OSGFieldAnimation.h"

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
   virtual void animationStarted(const AnimationEventUnrecPtr e)
   {
   }

   virtual void animationStopped(const AnimationEventUnrecPtr e)
   {
   }

   virtual void animationPaused(const AnimationEventUnrecPtr e)
   {
   }

   virtual void animationUnpaused(const AnimationEventUnrecPtr e)
   {
   }

   virtual void animationEnded(const AnimationEventUnrecPtr e)
   {
   }

   virtual void animationCycled(const AnimationEventUnrecPtr e)
   {
       std::cout << "Animation Cycled.  Cycle Count: " << dynamic_cast<Animation*>(e->getSource())->getCycles() << std::endl;
   }

};

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerUnrecPtr TutorialWindow;

Time TimeLastIdle;
FieldAnimationUnrecPtr TheAnimation;
TutorialAnimationListener TheAnimationListener;
MaterialUnrecPtr TheTorusMaterial;

BlendedKeyframeAnimatorUnrecPtr TheAnimator;
KeyframeTransformationSequenceUnrecPtr TransformationKeyframes;
KeyframeTransformationSequenceUnrecPtr TransformationKeyframes2;
KeyframeColorSequenceUnrecPtr ColorKeyframes;
KeyframeVectorSequenceUnrecPtr VectorKeyframes;
KeyframeRotationSequenceUnrecPtr RotationKeyframes;

TransformUnrecPtr TorusNodeTrans;

// Create a class to allow for the use of the keyboard shortucts 
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventUnrecPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
       {
           TutorialWindow->closeWindow();
       }

       switch(e->getKey())
       {
       case KeyEvent::KEY_SPACE:
           break;
       case KeyEvent::KEY_ENTER:
           break;
       case KeyEvent::KEY_0:
            dynamic_pointer_cast<FieldAnimation>(TheAnimation)->setInterpolationType(Animator::STEP_INTERPOLATION);
           break;
       case KeyEvent::KEY_1:
            dynamic_pointer_cast<FieldAnimation>(TheAnimation)->setInterpolationType(Animator::LINEAR_INTERPOLATION);
           break;
       case KeyEvent::KEY_2:
            dynamic_pointer_cast<FieldAnimation>(TheAnimation)->setInterpolationType(Animator::CUBIC_INTERPOLATION);
           break;
       }
   }

   virtual void keyReleased(const KeyEventUnrecPtr e)
   {
   }

   virtual void keyTyped(const KeyEventUnrecPtr e)
   {
   }
};

class TutorialMouseListener : public MouseListener
{
  public:
    virtual void mouseClicked(const MouseEventUnrecPtr e)
    {
    }
    virtual void mouseEntered(const MouseEventUnrecPtr e)
    {
    }
    virtual void mouseExited(const MouseEventUnrecPtr e)
    {
    }
    virtual void mousePressed(const MouseEventUnrecPtr e)
    {
            mgr->mouseButtonPress(e->getButton(), e->getLocation().x(), e->getLocation().y());
    }
    virtual void mouseReleased(const MouseEventUnrecPtr e)
    {
           mgr->mouseButtonRelease(e->getButton(), e->getLocation().x(), e->getLocation().y());
    }
};

class TutorialMouseMotionListener : public MouseMotionListener
{
  public:
    virtual void mouseMoved(const MouseEventUnrecPtr e)
    {
            mgr->mouseMove(e->getLocation().x(), e->getLocation().y());
    }

    virtual void mouseDragged(const MouseEventUnrecPtr e)
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
    TutorialWindow = createNativeWindow();
    TutorialWindow->initWindow();

    TutorialWindow->setDisplayCallback(display);
    TutorialWindow->setReshapeCallback(reshape);

    //Add Window Listener
    TutorialKeyListener TheKeyListener;
    TutorialWindow->addKeyListener(&TheKeyListener);
    TutorialMouseListener TheTutorialMouseListener;
    TutorialMouseMotionListener TheTutorialMouseMotionListener;
    TutorialWindow->addMouseListener(&TheTutorialMouseListener);
    TutorialWindow->addMouseMotionListener(&TheTutorialMouseMotionListener);

    // Create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

	
    // Tell the Manager what to manage
    mgr->setWindow(TutorialWindow);

    //Torus Material
    TheTorusMaterial = SimpleMaterial::create();
    dynamic_pointer_cast<SimpleMaterial>(TheTorusMaterial)->setAmbient(Color3f(0.3,0.3,0.3));
    dynamic_pointer_cast<SimpleMaterial>(TheTorusMaterial)->setDiffuse(Color3f(0.7,0.7,0.7));
    dynamic_pointer_cast<SimpleMaterial>(TheTorusMaterial)->setSpecular(Color3f(1.0,1.0,1.0));

    //Torus Geometry
    GeometryUnrecPtr TorusGeometry = makeTorusGeo(.5, 2, 32, 32);
    TorusGeometry->setMaterial(TheTorusMaterial);
    
    NodeUnrecPtr TorusGeometryNode = Node::create();
    TorusGeometryNode->setCore(TorusGeometry);

    //Make Torus Node
    NodeUnrecPtr TorusNode = Node::create();
    TorusNodeTrans = Transform::create();
    setName(TorusNodeTrans, std::string("TorusNodeTransformationCore"));

    TorusNode->setCore(TorusNodeTrans);
    TorusNode->addChild(TorusGeometryNode);

    //Make Main Scene Node
    NodeUnrecPtr scene = Node::create();
    ComponentTransformUnrecPtr Trans;
    Trans = ComponentTransform::create();
    setName(Trans, std::string("MainTransformationCore"));
    scene->setCore(Trans);

    // add the torus as a child
    scene->addChild(TorusNode);

    setupAnimation();

    // tell the manager what to manage
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();
    
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
            WinSize,
            "OpenSG 06BlenedAnimation Window");

    //Enter main Loop
    TutorialWindow->mainLoop();

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
    ColorKeyframes = KeyframeColorSequenceColor3f::create();
    ColorKeyframes->addKeyframe(Color4f(1.0f,0.0f,0.0f,1.0f),0.0f);
    ColorKeyframes->addKeyframe(Color4f(0.0f,1.0f,0.0f,1.0f),2.0f);
    ColorKeyframes->addKeyframe(Color4f(0.0f,0.0f,1.0f,1.0f),4.0f);
    ColorKeyframes->addKeyframe(Color4f(1.0f,0.0f,0.0f,1.0f),6.0f);

	//Vector Keyframe Sequence
    VectorKeyframes = KeyframeVectorSequenceVec3f::create();
    VectorKeyframes->addKeyframe(Vec3f(0.0f,0.0f,0.0f),0.0f);
    VectorKeyframes->addKeyframe(Vec3f(0.0f,1.0f,0.0f),1.0f);
    VectorKeyframes->addKeyframe(Vec3f(1.0f,1.0f,0.0f),2.0f);
    VectorKeyframes->addKeyframe(Vec3f(1.0f,0.0f,0.0f),3.0f);
    VectorKeyframes->addKeyframe(Vec3f(0.0f,0.0f,0.0f),4.0f);
    
	//Rotation Keyframe Sequence
    RotationKeyframes = KeyframeRotationSequenceQuaternion::create();
    RotationKeyframes->addKeyframe(Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*0.0),0.0f);
    RotationKeyframes->addKeyframe(Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*0.5),1.0f);
    RotationKeyframes->addKeyframe(Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*1.0),2.0f);
    RotationKeyframes->addKeyframe(Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*1.5),3.0f);
    RotationKeyframes->addKeyframe(Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*0.0),4.0f);

	//Transformation Keyframe Sequence
    TransformationKeyframes = KeyframeTransformationSequenceMatrix4f::create();
	Matrix TempMat;
	TempMat.setTransform(Vec3f(0.0f,0.0f,0.0f), Quaternion(Vec3f(0.0f,1.0f,0.0f), 0.0f));
    TransformationKeyframes->addKeyframe(TempMat,0.0f);                              
	TempMat.setTransform(Vec3f(0.0f,1.0f,0.0f), Quaternion(Vec3f(0.0f,1.0f,0.0f), 0.0f));
    TransformationKeyframes->addKeyframe(TempMat,1.0f);                              
	TempMat.setTransform(Vec3f(1.0f,1.0f,0.0f), Quaternion(Vec3f(0.0f,1.0f,0.0f), 0.0f));
    TransformationKeyframes->addKeyframe(TempMat,2.0f);                              
	TempMat.setTransform(Vec3f(1.0f,0.0f,0.0f), Quaternion(Vec3f(0.0f,1.0f,0.0f), 0.0f));
    TransformationKeyframes->addKeyframe(TempMat,3.0f);                              
	TempMat.setTransform(Vec3f(0.0f,0.0f,0.0f), Quaternion(Vec3f(0.0f,1.0f,0.0f), 0.0f));
    TransformationKeyframes->addKeyframe(TempMat,4.0f);
    
    TransformationKeyframes2 = KeyframeTransformationSequenceMatrix4f::create();
	TempMat.setTransform(Vec3f(0.0f,0.0f,0.0f), Quaternion(Vec3f(0.0f,1.0f,0.0f), 0.0f));
    TransformationKeyframes2->addKeyframe(TempMat,0.0f);
	TempMat.setTransform(Vec3f(0.1f,0.1f,0.0f), Quaternion(Vec3f(0.0f,1.0f,0.0f), 0.0f));
    TransformationKeyframes2->addKeyframe(TempMat,0.05f);
	TempMat.setTransform(Vec3f(-0.1f,-0.1f,0.0f), Quaternion(Vec3f(0.0f,1.0f,0.0f), 0.0f));
    TransformationKeyframes2->addKeyframe(TempMat,0.15f);
	TempMat.setTransform(Vec3f(0.0f,0.0f,0.0f), Quaternion(Vec3f(0.0f,1.0f,0.0f), 0.0f));
    TransformationKeyframes2->addKeyframe(TempMat,0.20f);

    //Animator
    TheAnimator = BlendedKeyframeAnimator::create();
    TheAnimator->pushToKeyframeSequences(TransformationKeyframes);
    TheAnimator->editMFBlendAmounts()->push_back(1.0);
    TheAnimator->pushToKeyframeSequences(TransformationKeyframes2);
    TheAnimator->editMFBlendAmounts()->push_back(1.0);
    
    //Animation
    TheAnimation = FieldAnimation::create();
    TheAnimation->setAnimator(TheAnimator);
    TheAnimation->setInterpolationType(Animator::LINEAR_INTERPOLATION);
    TheAnimation->setCycling(-1);
	TheAnimation->setAnimatedField(TorusNodeTrans, std::string("matrix"));

    //Animation Listener
    TheAnimation->addAnimationListener(&TheAnimationListener);

    TheAnimation->attachUpdateProducer(TutorialWindow->editEventProducer());
    TheAnimation->start();

}

