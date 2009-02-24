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
// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

Time TimeLastIdle;
AnimationPtr TheAnimation;
AnimationAdvancerPtr TheAnimationAdvancer;
MaterialPtr TheTorusMaterial;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );
void setupAnimation(void);
void display(void);

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

// Initialize GLUT & OpenSG and set up the scene
int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);


    // GLUT init
    int winid = setupGLUT(&argc, argv);

    // the connection between GLUT and OpenSG
    GLUTWindowPtr gwin= GLUTWindow::create();
    gwin->setId(winid);
    gwin->init();


    //Make Torus Node
    NodePtr TorusNode = Node::create();
    ComponentTransformPtr TorusNodeTrans;
    TorusNodeTrans = ComponentTransform::create();
    setName(TorusNodeTrans, std::string("TorusNodeTransformationCore"));
    
    

    //Torus Material
    TheTorusMaterial = SimpleMaterial::create();

    //Torus Geometry
    GeometryPtr TorusGeometry = makeTorusGeo(.5, 2, 16, 16);
    beginEditCP(TorusGeometry);
        TorusGeometry->setMaterial(TheTorusMaterial);
    endEditCP  (TorusGeometry);
    
    NodePtr TorusGeometryNode = Node::create();
    beginEditCP(TorusGeometryNode, Node::CoreFieldMask);
        TorusGeometryNode->setCore(TorusGeometry);
    endEditCP  (TorusGeometryNode, Node::CoreFieldMask);

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

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();

    TimeLastIdle = getSystemTime();
    TheAnimation->start();
    

    // GLUT main loop
    glutMainLoop();

    return 0;
}

//
// GLUT callback functions
//

void idle(void)
{
   Time Now = getSystemTime();
   Time Elps(Now - TimeLastIdle);
   TimeLastIdle = Now;
   
   ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->update(Elps);

   TheAnimation->update(TheAnimationAdvancer);

   glutPostRedisplay();
}

// redraw the window
void display(void)
{
    mgr->redraw();
}

// react to size changes
void reshape(int w, int h)
{
    mgr->resize(w, h);
    glutPostRedisplay();
}

// react to mouse button presses
void mouse(int button, int state, int x, int y)
{
    if (state)
        mgr->mouseButtonRelease(button, x, y);
    else
        mgr->mouseButtonPress(button, x, y);
        
    glutPostRedisplay();
}

// react to mouse motions with pressed buttons
void motion(int x, int y)
{
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

// react to keys
void keyboard(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 27:        
        {
            OSG::osgExit();
            exit(0);
        }
        break;
        case 's':
            beginEditCP(TheAnimation, FieldAnimation::InterpolationTypeFieldMask);
                FieldAnimationPtr::dcast(TheAnimation)->setInterpolationType(STEP_INTERPOLATION);
            endEditCP(TheAnimation, FieldAnimation::InterpolationTypeFieldMask);
            break;
        case 'l':
            beginEditCP(TheAnimation, FieldAnimation::InterpolationTypeFieldMask);
                FieldAnimationPtr::dcast(TheAnimation)->setInterpolationType(LINEAR_INTERPOLATION);
            endEditCP(TheAnimation, FieldAnimation::InterpolationTypeFieldMask);
            break;
        case 'c':
            beginEditCP(TheAnimation, FieldAnimation::InterpolationTypeFieldMask);
                FieldAnimationPtr::dcast(TheAnimation)->setInterpolationType(CUBIC_INTERPOLATION);
            endEditCP(TheAnimation, FieldAnimation::InterpolationTypeFieldMask);
            break;
        case 'n':
            beginEditCP(TheAnimation, FieldAnimation::InterpolationTypeFieldMask);
                FieldAnimationPtr::dcast(TheAnimation)->setInterpolationType(LINEAR_NORMAL_INTERPOLATION);
            endEditCP(TheAnimation, FieldAnimation::InterpolationTypeFieldMask);
            break;
    }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG ");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    return winid;
}


void setupAnimation(void)
{
    //Color Animation
    KeyframeColorsSequencePtr ColorKeyframes = KeyframeColorsSequence3f::create();
    ColorKeyframes->addKeyframe(Color4f(1.0f,0.0f,0.0f,1.0f),0.0f);
    ColorKeyframes->addKeyframe(Color4f(0.0f,1.0f,0.0f,1.0f),2.0f);
    ColorKeyframes->addKeyframe(Color4f(0.0f,0.0f,1.0f,1.0f),4.0f);
    ColorKeyframes->addKeyframe(Color4f(1.0f,0.0f,0.0f,1.0f),6.0f);

    KeyframeVectorsSequencePtr VectorKeyframes = KeyframeVectorsSequence3f::create();
    VectorKeyframes->addKeyframe(Vec3f(0.0f,0.0f,0.0f),0.0f);
    VectorKeyframes->addKeyframe(Vec3f(0.0f,1.0f,0.0f),1.0f);
    VectorKeyframes->addKeyframe(Vec3f(1.0f,1.0f,0.0f),2.0f);
    VectorKeyframes->addKeyframe(Vec3f(1.0f,0.0f,0.0f),3.0f);
    VectorKeyframes->addKeyframe(Vec3f(0.0f,0.0f,0.0f),4.0f);
    
    KeyframeRotationsSequencePtr RotationKeyframes = KeyframeRotationsSequenceQuat::create();
    RotationKeyframes->addKeyframe(Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*0.0),0.0f);
    RotationKeyframes->addKeyframe(Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*0.5),1.0f);
    RotationKeyframes->addKeyframe(Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*1.0),2.0f);
    RotationKeyframes->addKeyframe(Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*1.5),3.0f);
    RotationKeyframes->addKeyframe(Quaternion(Vec3f(0.0f,1.0f,0.0f), 3.14159f*0.0),4.0f);
    
    //Animator
    AnimatorPtr Animator = KeyframeAnimator::create();
    beginEditCP(KeyframeAnimatorPtr::dcast(Animator), KeyframeAnimator::KeyframeSequenceFieldMask);
        KeyframeAnimatorPtr::dcast(Animator)->setKeyframeSequence(ColorKeyframes);
    endEditCP(KeyframeAnimatorPtr::dcast(Animator), KeyframeAnimator::KeyframeSequenceFieldMask);
         
    //Animated Object
    //FieldContainerPtr AnimatedObject = getFieldContainer("ComponentTransform",std::string("TorusNodeTransformationCore"));
    FieldContainerPtr AnimatedObject = TheTorusMaterial;
    
    //Animation
    TheAnimation = FieldAnimation::create();
    beginEditCP(TheAnimation);
        FieldAnimationPtr::dcast(TheAnimation)->setAnimator(Animator);
        FieldAnimationPtr::dcast(TheAnimation)->setContainer(AnimatedObject);
        FieldAnimationPtr::dcast(TheAnimation)->setFieldName( std::string("diffuse") );
        //FieldAnimationPtr::dcast(TheAnimation)->setFieldName( std::string("rotation") );
        FieldAnimationPtr::dcast(TheAnimation)->setInterpolationType(LINEAR_INTERPOLATION);
        FieldAnimationPtr::dcast(TheAnimation)->setCycling(-1);
    endEditCP(TheAnimation);

    //Animation Advancer
    TheAnimationAdvancer = ElapsedTimeAnimationAdvancer::create();
    beginEditCP(TheAnimationAdvancer);
    ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->setStartTime( 0.0 );
    beginEditCP(TheAnimationAdvancer);
   
   /*//Real32
   KeyframeSequencePtr KeyframeSequence = KeyframeSequenceReal32::create();
   SFReal32 IntValue;
   
   KeyframeSequenceReal32Ptr::dcast(KeyframeSequence)->getValues().push_back(3.0);
   KeyframeSequenceReal32Ptr::dcast(KeyframeSequence)->getValues().push_back(5.0);
   KeyframeSequenceReal32Ptr::dcast(KeyframeSequence)->getValues().push_back(10.0);
   KeyframeSequenceReal32Ptr::dcast(KeyframeSequence)->getValues().push_back(7.0);
   KeyframeSequenceReal32Ptr::dcast(KeyframeSequence)->getValues().push_back(3.0);*/
   
   
   //Vector
   /*KeyframeSequencePtr KeyframeSequence = KeyframeSequenceVec3f::create();
   
   KeyframeSequenceVec3fPtr::dcast(KeyframeSequence)->getValues().push_back(Vec3f(-1.5,-1.5,0.0));
   KeyframeSequenceVec3fPtr::dcast(KeyframeSequence)->getValues().push_back(Vec3f(-1.5,1.5,0.0));
   KeyframeSequenceVec3fPtr::dcast(KeyframeSequence)->getValues().push_back(Vec3f(1.5,1.5,0.0));
   KeyframeSequenceVec3fPtr::dcast(KeyframeSequence)->getValues().push_back(Vec3f(1.5,-1.5,0.0));
   KeyframeSequenceVec3fPtr::dcast(KeyframeSequence)->getValues().push_back(Vec3f(-1.5,-1.5,0.0));*/
         
   //Point
   /*KeyframeSequencePtr KeyframeSequence = KeyframeSequencePnt3f::create();
   SFPnt3f IntValue;
   
   beginEditCP(KeyframeSequence);
      KeyframeSequencePnt3fPtr::dcast(KeyframeSequence)->getValues().push_back(Pnt3f(3.0,0.0,0.0));
      KeyframeSequencePnt3fPtr::dcast(KeyframeSequence)->getValues().push_back(Pnt3f(5.0,0.0,0.0));
      KeyframeSequencePnt3fPtr::dcast(KeyframeSequence)->getValues().push_back(Pnt3f(7.0,0.0,0.0));
      KeyframeSequencePnt3fPtr::dcast(KeyframeSequence)->getValues().push_back(Pnt3f(10.0,0.0,0.0));
      KeyframeSequencePnt3fPtr::dcast(KeyframeSequence)->getValues().push_back(Pnt3f(3.0,0.0,0.0));
   endEditCP(KeyframeSequence);*/
   
   /*//Matrix
   MFMatrix KeyValues;
   Matrix IntValue;
   
   KeyValues.push_back(Matrix());
   KeyValues.push_back(Matrix());
   KeyValues.push_back(Matrix());
   KeyValues.push_back(Matrix());
   KeyValues.push_back(Matrix());*/
         
   //Color
   /*KeyframeSequencePtr KeyframeSequence = KeyframeSequenceColor3f::create();
   SFColor3f IntValue;
   
   beginEditCP(KeyframeSequence);
      KeyframeSequenceColor3fPtr::dcast(KeyframeSequence)->getValues().push_back(Color3f(1.0,0.0,0.0));
      KeyframeSequenceColor3fPtr::dcast(KeyframeSequence)->getValues().push_back(Color3f(1.0,1.0,0.0));
      KeyframeSequenceColor3fPtr::dcast(KeyframeSequence)->getValues().push_back(Color3f(1.0,1.0,1.0));
      KeyframeSequenceColor3fPtr::dcast(KeyframeSequence)->getValues().push_back(Color3f(1.0,0.0,1.0));
      KeyframeSequenceColor3fPtr::dcast(KeyframeSequence)->getValues().push_back(Color3f(1.0,0.0,0.0));
   endEditCP(KeyframeSequence);
         
   //Quaternion
   KeyframeSequencePtr KeyframeSequence = KeyframeSequenceQuaternion::create();
   
   KeyframeSequenceQuaternionPtr::dcast(KeyframeSequence)->getValues().push_back(Quaternion(Vec3f(0.0,1.0,0.0),0.0));
   KeyframeSequenceQuaternionPtr::dcast(KeyframeSequence)->getValues().push_back(Quaternion(Vec3f(0.0,1.0,0.0),0.5*Pi));
   KeyframeSequenceQuaternionPtr::dcast(KeyframeSequence)->getValues().push_back(Quaternion(Vec3f(0.0,1.0,0.0),Pi));
   KeyframeSequenceQuaternionPtr::dcast(KeyframeSequence)->getValues().push_back(Quaternion(Vec3f(0.0,1.0,0.0),1.5*Pi));
 //  KeyframeSequenceQuaternionPtr::dcast(KeyframeSequence)->getValues().push_back(Quaternion(Vec3f(0.0,1.0,0.0),2.0*Pi));
   */
}
