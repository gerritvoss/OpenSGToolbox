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
#include "OSGKeyframeAnimator.h"
#include "OSGFieldAnimation.h"
#include "OSGAnimationGroup.h"

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE



// forward declaration so we can have the interesting stuff upfront
AnimationGroupUnrecPtr setupAnimation(SimpleMaterial* const TheTorusMaterial,
                                      Transform* const TorusNodeTrans);
void display(SimpleSceneManager *mgr);
void reshape(Vec2f Size, SimpleSceneManager *mgr);

void animationCycled(AnimationEventDetails* const details)
{
    std::cout << "Animation Cycled.  Cycle Count: " << dynamic_cast<Animation*>(details->getSource())->getCycles() << std::endl;
}

// The SimpleSceneManager to manage simple applications
void keyPressed(KeyEventDetails* const details,
                AnimationGroup* const TheAnimationGroup,
                WindowEventProducer* const TutorialWindow)
{
    if(details->getKey() == KeyEventDetails::KEY_Q && details->getModifiers() & KeyEventDetails::KEY_MODIFIER_COMMAND)
    {
        TutorialWindow->closeWindow();
    }

    switch(details->getKey())
    {
        case KeyEventDetails::KEY_SPACE:
            TheAnimationGroup->pause(!TheAnimationGroup->isPaused());
            break;
        case KeyEventDetails::KEY_ENTER:
            TheAnimationGroup->attachUpdateProducer(TutorialWindow);
            TheAnimationGroup->start();
            break;
        case KeyEventDetails::KEY_MINUS:
            TheAnimationGroup->setScale(osgMax(TheAnimationGroup->getScale()-0.1f, 0.0f));
            break;
        case KeyEventDetails::KEY_PLUS:
        case KeyEventDetails::KEY_EQUALS:
            TheAnimationGroup->setScale(osgMax(TheAnimationGroup->getScale()+0.1f, 0.0f));
            break;
    }
}

void mousePressed(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    mgr->mouseButtonPress(details->getButton(), details->getLocation().x(), details->getLocation().y());
}

void mouseReleased(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    mgr->mouseButtonRelease(details->getButton(), details->getLocation().x(), details->getLocation().y());
}

void mouseMoved(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    mgr->mouseMove(details->getLocation().x(), details->getLocation().y());
}

void mouseDragged(MouseEventDetails* const details, SimpleSceneManager *mgr)
{
    mgr->mouseMove(details->getLocation().x(), details->getLocation().y());
}

void mouseWheelMoved(MouseWheelEventDetails* const details, SimpleSceneManager *mgr)
{
    if(details->getUnitsToScroll() > 0)
    {
        for(UInt32 i(0) ; i<details->getUnitsToScroll() ;++i)
        {
            mgr->mouseButtonPress(Navigator::DOWN_MOUSE,details->getLocation().x(),details->getLocation().y());
            mgr->mouseButtonRelease(Navigator::DOWN_MOUSE,details->getLocation().x(),details->getLocation().y());
        }
    }
    else if(details->getUnitsToScroll() < 0)
    {
        for(UInt32 i(0) ; i<abs(details->getUnitsToScroll()) ;++i)
        {
            mgr->mouseButtonPress(Navigator::UP_MOUSE,details->getLocation().x(),details->getLocation().y());
            mgr->mouseButtonRelease(Navigator::UP_MOUSE,details->getLocation().x(),details->getLocation().y());
        }
    }
}

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    {
        // Set up Window
        WindowEventProducerRecPtr TutorialWindow = createNativeWindow();

        //Initialize Window
        TutorialWindow->initWindow();

        SimpleSceneManager sceneManager;
        TutorialWindow->setDisplayCallback(boost::bind(display, &sceneManager));
        TutorialWindow->setReshapeCallback(boost::bind(reshape, _1, &sceneManager));

        // Tell the Manager what to manage
        sceneManager.setWindow(TutorialWindow);

        //Attach to events
        TutorialWindow->connectMousePressed(boost::bind(mousePressed, _1, &sceneManager));
        TutorialWindow->connectMouseReleased(boost::bind(mouseReleased, _1, &sceneManager));
        TutorialWindow->connectMouseMoved(boost::bind(mouseMoved, _1, &sceneManager));
        TutorialWindow->connectMouseDragged(boost::bind(mouseDragged, _1, &sceneManager));
        TutorialWindow->connectMouseWheelMoved(boost::bind(mouseWheelMoved, _1, &sceneManager));

        //Torus Material
        SimpleMaterialUnrecPtr TheTorusMaterial = SimpleMaterial::create();
        TheTorusMaterial->setAmbient(Color3f(0.3,0.3,0.3));
        TheTorusMaterial->setDiffuse(Color3f(0.7,0.7,0.7));
        TheTorusMaterial->setSpecular(Color3f(1.0,1.0,1.0));
        TheTorusMaterial->setShininess(20.0);

        //Torus Geometry
        GeometryUnrecPtr TorusGeometry = makeTorusGeo(.5, 2, 32, 32);
        TorusGeometry->setMaterial(TheTorusMaterial);

        NodeUnrecPtr TorusGeometryNode = Node::create();
        TorusGeometryNode->setCore(TorusGeometry);

        //Make Torus Node
        NodeUnrecPtr TorusNode = Node::create();
        TransformUnrecPtr TorusNodeTrans = Transform::create();
        setName(TorusNodeTrans, std::string("TorusNodeTransformationCore"));

        TorusNode->setCore(TorusNodeTrans);
        TorusNode->addChild(TorusGeometryNode);

        //Make Main Scene Node
        NodeUnrecPtr scene = Node::create();
        ComponentTransformUnrecPtr Trans = ComponentTransform::create();
        setName(Trans, std::string("MainTransformationCore"));
        scene->setCore(Trans);

        // add the torus as a child
        scene->addChild(TorusNode);

        AnimationGroupUnrecPtr TheAnimation = setupAnimation(TheTorusMaterial, TorusNodeTrans);
        TutorialWindow->connectKeyPressed(boost::bind(keyPressed, _1,
                                                      TheAnimation.get(),
                                                      TutorialWindow.get()));
        TheAnimation->attachUpdateProducer(TutorialWindow);
        TheAnimation->start();

        // tell the manager what to manage
        sceneManager.setRoot  (scene);

        // show the whole scene
        sceneManager.showAll();


        Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
        Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
        TutorialWindow->openWindow(WinPos,
                                   WinSize,
                                   "07AnimationGroup");

        //Enter main Loop
        TutorialWindow->mainLoop();
    }

    osgExit();

    return 0;
}

// Redraw the window
void display(SimpleSceneManager *mgr)
{
    mgr->redraw();
}

// React to size changes
void reshape(Vec2f Size, SimpleSceneManager *mgr)
{
    mgr->resize(Size.x(), Size.y());
}

AnimationGroupUnrecPtr setupAnimation(SimpleMaterial* const TheTorusMaterial,
                                      Transform* const TorusNodeTrans)
{
    //Color Keyframe Sequence
    KeyframeColorSequenceColor3fUnrecPtr ColorKeyframes = KeyframeColorSequenceColor3f::create();
    ColorKeyframes->addKeyframe(Color4f(1.0f,0.0f,0.0f,1.0f),0.0f);
    ColorKeyframes->addKeyframe(Color4f(0.0f,1.0f,0.0f,1.0f),2.0f);
    ColorKeyframes->addKeyframe(Color4f(0.0f,0.0f,1.0f,1.0f),4.0f);
    ColorKeyframes->addKeyframe(Color4f(1.0f,0.0f,0.0f,1.0f),6.0f);

    //Color Animator
    KeyframeAnimatorUnrecPtr TheColorAnimator = KeyframeAnimator::create();
    TheColorAnimator->setKeyframeSequence(ColorKeyframes);

    //Color Animation
    FieldAnimationUnrecPtr TheColorAnimation = FieldAnimation::create();
    TheColorAnimation->setAnimator(TheColorAnimator);
    TheColorAnimation->setInterpolationType(Animator::LINEAR_INTERPOLATION);
    TheColorAnimation->setCycling(2);
    TheColorAnimation->setAnimatedField(TheTorusMaterial, std::string("diffuse"));

    //Transformation Keyframe Sequence
    KeyframeTransformationSequenceMatrix4fUnrecPtr TransformationKeyframes = KeyframeTransformationSequenceMatrix4f::create();
    Matrix TempMat;
    TempMat.setTransform(Vec3f(0.0f,0.0f,0.0f), Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*0.0f));
    TransformationKeyframes->addKeyframe(TempMat,0.0f);
    TempMat.setTransform(Vec3f(0.0f,1.0f,0.0f), Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*0.5f));
    TransformationKeyframes->addKeyframe(TempMat,1.0f);
    TempMat.setTransform(Vec3f(1.0f,1.0f,0.0f), Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*1.0f));
    TransformationKeyframes->addKeyframe(TempMat,2.0f);
    TempMat.setTransform(Vec3f(1.0f,0.0f,0.0f), Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*1.5f));
    TransformationKeyframes->addKeyframe(TempMat,3.0f);
    TempMat.setTransform(Vec3f(0.0f,0.0f,0.0f), Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*2.0f));
    TransformationKeyframes->addKeyframe(TempMat,4.0f);

    //Transformation Animator
    KeyframeAnimatorUnrecPtr TheTransformationAnimator = KeyframeAnimator::create();
    TheTransformationAnimator->setKeyframeSequence(TransformationKeyframes);

    //Transformation Animation
    FieldAnimationUnrecPtr TheTransformationAnimation = FieldAnimation::create();
    TheTransformationAnimation->setAnimator(TheTransformationAnimator);
    TheTransformationAnimation->setInterpolationType(Animator::LINEAR_INTERPOLATION);
    TheTransformationAnimation->setCycling(2);
    TheTransformationAnimation->setAnimatedField(TorusNodeTrans, std::string("matrix"));

    AnimationGroupUnrecPtr TheAnimationGroup = AnimationGroup::create();
    TheAnimationGroup->pushToAnimations(TheColorAnimation);
    TheAnimationGroup->pushToAnimations(TheTransformationAnimation);

    return AnimationGroupTransitPtr(TheAnimationGroup);
}

