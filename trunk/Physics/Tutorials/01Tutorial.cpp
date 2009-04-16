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

#include <OpenSG/OSGTime.h>
#include "Animations/OSGAnimation.h"
#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGTransform.h>

#include <OpenSG/OSGFieldContainerFactory.h>
#include <OpenSG/OSGSimpleAttachments.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

osg::Time TimeLastIdle;
osg::AnimationPtr TheAnimation;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );
void setupAnimation(void);
void display(void);

FieldContainerPtr getFieldContainer(const Char8 *szTypeName, const std::string &namestring);

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
    
    // create the scene

    NodePtr scene = osg::Node::create();
    NodePtr TorusNode = makeTorus(.5, 2, 16, 16);
    osg::ComponentTransformPtr Trans;
    Trans = osg::ComponentTransform::create();
    osg::setName(Trans, std::string("MainTransformationCore"));
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

    TimeLastIdle = osg::getSystemTime();
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
   osg::Time Now = osg::getSystemTime();
   osg::Time Elps(Now - TimeLastIdle);
   TimeLastIdle = Now;
   TheAnimation->update(Elps);

   //std::cout << "Time: " << TheAnimation->getTime() << std::endl;
   //std::cout << "Trans: " << Trans->getScale() << std::endl;
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
    }
}

// setup the GLUT library which handles the windows for us
int setupGLUT(int *argc, char *argv[])
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    
    int winid = glutCreateWindow("OpenSG");
    
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    return winid;
}

//#include "KeyframeSequence/OSGKeyframeSequenceReal32.h"
//#include "KeyframeSequence/OSGKeyframeSequencePnt3f.h"
//#include "KeyframeSequence/OSGKeyframeSequenceColor3f.h"
#include "KeyframeSequence/OSGKeyframeSequenceVec3f.h"
//#include "KeyframeSequence/OSGKeyframeSequenceQuaternion.h"
#include "Animators/OSGKeyframeAnimator.h"
#include "Animations/OSGFieldAnimation.h"

void setupAnimation(void)
{
   
   /*//Real32
   osg::KeyframeSequencePtr KeyframeSequence = osg::KeyframeSequenceReal32::create();
   osg::SFReal32 IntValue;
   
   osg::KeyframeSequenceReal32Ptr::dcast(KeyframeSequence)->getValues().push_back(3.0);
   osg::KeyframeSequenceReal32Ptr::dcast(KeyframeSequence)->getValues().push_back(5.0);
   osg::KeyframeSequenceReal32Ptr::dcast(KeyframeSequence)->getValues().push_back(10.0);
   osg::KeyframeSequenceReal32Ptr::dcast(KeyframeSequence)->getValues().push_back(7.0);
   osg::KeyframeSequenceReal32Ptr::dcast(KeyframeSequence)->getValues().push_back(3.0);*/
   
   
   //Vector
   osg::KeyframeSequencePtr KeyframeSequence = osg::KeyframeSequenceVec3f::create();
   
   osg::KeyframeSequenceVec3fPtr::dcast(KeyframeSequence)->getValues().push_back(osg::Vec3f(-3.0,-3.0,0.0));
   osg::KeyframeSequenceVec3fPtr::dcast(KeyframeSequence)->getValues().push_back(osg::Vec3f(-3.0,3.0,0.0));
   osg::KeyframeSequenceVec3fPtr::dcast(KeyframeSequence)->getValues().push_back(osg::Vec3f(3.0,3.0,0.0));
   osg::KeyframeSequenceVec3fPtr::dcast(KeyframeSequence)->getValues().push_back(osg::Vec3f(3.0,-3.0,0.0));
   osg::KeyframeSequenceVec3fPtr::dcast(KeyframeSequence)->getValues().push_back(osg::Vec3f(-3.0,-3.0,0.0));
         
   //Point
   /*osg::KeyframeSequencePtr KeyframeSequence = osg::KeyframeSequencePnt3f::create();
   osg::SFPnt3f IntValue;
   
   osg::beginEditCP(KeyframeSequence);
      osg::KeyframeSequencePnt3fPtr::dcast(KeyframeSequence)->getValues().push_back(osg::Pnt3f(3.0,0.0,0.0));
      osg::KeyframeSequencePnt3fPtr::dcast(KeyframeSequence)->getValues().push_back(osg::Pnt3f(5.0,0.0,0.0));
      osg::KeyframeSequencePnt3fPtr::dcast(KeyframeSequence)->getValues().push_back(osg::Pnt3f(7.0,0.0,0.0));
      osg::KeyframeSequencePnt3fPtr::dcast(KeyframeSequence)->getValues().push_back(osg::Pnt3f(10.0,0.0,0.0));
      osg::KeyframeSequencePnt3fPtr::dcast(KeyframeSequence)->getValues().push_back(osg::Pnt3f(3.0,0.0,0.0));
   osg::endEditCP(KeyframeSequence);*/
   
   /*//Matrix
   osg::MFMatrix KeyValues;
   osg::Matrix IntValue;
   
   KeyValues.push_back(osg::Matrix());
   KeyValues.push_back(osg::Matrix());
   KeyValues.push_back(osg::Matrix());
   KeyValues.push_back(osg::Matrix());
   KeyValues.push_back(osg::Matrix());*/
         
   //Color
   /*osg::KeyframeSequencePtr KeyframeSequence = osg::KeyframeSequenceColor3f::create();
   osg::SFColor3f IntValue;
   
   osg::beginEditCP(KeyframeSequence);
      osg::KeyframeSequenceColor3fPtr::dcast(KeyframeSequence)->getValues().push_back(osg::Color3f(1.0,0.0,0.0));
      osg::KeyframeSequenceColor3fPtr::dcast(KeyframeSequence)->getValues().push_back(osg::Color3f(1.0,1.0,0.0));
      osg::KeyframeSequenceColor3fPtr::dcast(KeyframeSequence)->getValues().push_back(osg::Color3f(1.0,1.0,1.0));
      osg::KeyframeSequenceColor3fPtr::dcast(KeyframeSequence)->getValues().push_back(osg::Color3f(1.0,0.0,1.0));
      osg::KeyframeSequenceColor3fPtr::dcast(KeyframeSequence)->getValues().push_back(osg::Color3f(1.0,0.0,0.0));
   osg::endEditCP(KeyframeSequence);*/
         
   //Quaternion
   /*osg::KeyframeSequencePtr KeyframeSequence = osg::KeyframeSequenceQuaternion::create();
   
   osg::KeyframeSequenceQuaternionPtr::dcast(KeyframeSequence)->getValues().push_back(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),0.0));
   osg::KeyframeSequenceQuaternionPtr::dcast(KeyframeSequence)->getValues().push_back(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),0.5*osg::Pi));
   osg::KeyframeSequenceQuaternionPtr::dcast(KeyframeSequence)->getValues().push_back(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),osg::Pi));
   osg::KeyframeSequenceQuaternionPtr::dcast(KeyframeSequence)->getValues().push_back(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),1.5*osg::Pi));
   osg::KeyframeSequenceQuaternionPtr::dcast(KeyframeSequence)->getValues().push_back(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),2.0*osg::Pi));*/
   
   //Animator
   osg::AnimatorPtr Animator = osg::KeyframeAnimator::create();
   osg::beginEditCP(Animator);
      osg::KeyframeAnimatorPtr::dcast(Animator)->setValues(KeyframeSequence);
      osg::KeyframeAnimatorPtr::dcast(Animator)->getKeys().push_back(0.0);
      osg::KeyframeAnimatorPtr::dcast(Animator)->getKeys().push_back(2.0);
      osg::KeyframeAnimatorPtr::dcast(Animator)->getKeys().push_back(4.0);
      osg::KeyframeAnimatorPtr::dcast(Animator)->getKeys().push_back(6.0);
      osg::KeyframeAnimatorPtr::dcast(Animator)->getKeys().push_back(8.0);
   osg::endEditCP(Animator);
         
   //Animated Object
   osg::FieldContainerPtr AnimatedObject = getFieldContainer("ComponentTransform",std::string("MainTransformationCore"));
   
   //Animation
   TheAnimation = osg::FieldAnimation::create();
   osg::beginEditCP(TheAnimation);
      osg::FieldAnimationPtr::dcast(TheAnimation)->setAnimator(Animator);
      osg::FieldAnimationPtr::dcast(TheAnimation)->setContainer(AnimatedObject);
      osg::FieldAnimationPtr::dcast(TheAnimation)->setFieldName( std::string("translation") );
      osg::FieldAnimationPtr::dcast(TheAnimation)->setInterpolationType(osg::CUBIC_INTERPOLATION);
      osg::FieldAnimationPtr::dcast(TheAnimation)->setCycling(-1);
   osg::endEditCP(TheAnimation);
}

osg::FieldContainerPtr getFieldContainer(const osg::Char8 *szTypeName, const std::string &namestring)
{
   const osg::FieldContainerType * TheFieldType( osg::FieldContainerFactory::the()->findType(szTypeName) );
   if(TheFieldType == NULL)
   {
      std::cout << "The " << szTypeName << " Field type is not defined." << std::endl;
   }

   const std::vector<osg::FieldContainerPtr>* FCStore(	osg::FieldContainerFactory::the()->getFieldContainerStore () );

   std::vector<osg::FieldContainerPtr>::const_iterator FCStoreIter;
   for(FCStoreIter = FCStore->begin() ; FCStoreIter != FCStore->end() ; ++FCStoreIter)
   {
      if( (*FCStoreIter) != osg::NullFC && (*FCStoreIter)->getType() == (*TheFieldType) )
      {
         const osg::Char8 *Name( osg::getName(osg::AttachmentContainerPtr::dcast(*FCStoreIter)) );
         if(Name != NULL && namestring.compare(Name) == 0)
         {
            return (*FCStoreIter);
         }
      }
   }

   return osg::NullFC;
}
