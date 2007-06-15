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
#include <OpenSG/Animation/OSGAnimation.h>
#include <OpenSG/Animation/OSGBlendGeometry.h>
#include <OpenSG/Animation/OSGElapsedTimeAnimationAdvancer.h>
#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGTypeFactory.h>
#include <OpenSG/OSGFieldFactory.h>

#include <OpenSG/OSGFieldContainerFactory.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include <OpenSG/OSGStatElemDesc.h>

// the general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

// Activate the OpenSG namespace
// This is not strictly necessary, you can also prefix all OpenSG symbols
// with OSG::, but that would be a bit tedious for this example
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

osg::Time TimeLastIdle;
osg::AnimationPtr TheAnimation;
osg::AnimationPtr TheGeometryPositionAnimation;
osg::AnimationPtr TheGeometryNormalAnimation;
osg::AnimationAdvancerPtr TheAnimationAdvancer;

NodePtr BubbleBlendGeometryNode;
NodePtr BlendGeometryTransNode;

// forward declaration so we can have the interesting stuff upfront
int setupGLUT( int *argc, char *argv[] );
void setupAnimation(void);
void display(void);
void setupGeometryAnimation(void);
void setupBlendGeometry(void);

FieldContainerPtr getFieldContainer(const Char8 *szTypeName, const std::string &namestring);

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
    
    // create the scene

    BubbleBlendGeometryNode = SceneFileHandler::the().read("C:\\Documents and Settings\\David\\My Documents\\Work\\VSE\\Plugins\\OpenSG\\Animation\\Builds\\Windows.Build\\lib\\BubbleBlendShape.osb");


    //Make Torus Node
    NodePtr TorusNode = osg::Node::create();
    osg::ComponentTransformPtr TorusNodeTrans;
    TorusNodeTrans = osg::ComponentTransform::create();
    osg::setName(TorusNodeTrans, std::string("TorusNodeTransformationCore"));
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);
    beginEditCP(TorusNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        TorusNode->setCore(TorusNodeTrans);
        TorusNode->addChild(TorusGeometryNode);
    endEditCP  (TorusNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

    //Make the Blend Geometry Node
    setupBlendGeometry();

    //Make Main Scene Node
    NodePtr scene = osg::Node::create();
    osg::ComponentTransformPtr Trans;
    Trans = osg::ComponentTransform::create();
    osg::setName(Trans, std::string("MainTransformationCore"));
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
    {
        scene->setCore(Trans);
 
        // add the torus as a child
        scene->addChild(TorusNode);
        scene->addChild(BubbleBlendGeometryNode);
        scene->addChild(BlendGeometryTransNode);
    }
    endEditCP  (scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    setupAnimation();
    setupGeometryAnimation();

    // create the SimpleSceneManager helper
    mgr = new SimpleSceneManager;

    // tell the manager what to manage
    mgr->setWindow(gwin );
    mgr->setRoot  (scene);

    // show the whole scene
    mgr->showAll();

    TimeLastIdle = osg::getSystemTime();
    TheAnimation->start();
    TheGeometryPositionAnimation->start();
    TheGeometryNormalAnimation->start();

    //osg::StatElemDescBase::printAll();
    
    //********************************Temp//********************************
    osg::UInt32 NumTypes = osg::TypeFactory::the()->getNumTypes();
    std::cout << "Types: " << NumTypes << std::endl;
    for(osg::UInt32 i=1 ; i<NumTypes ; ++i)
    {
       std::cout << "   " << osg::TypeFactory::the()->findType(i)->getName() << std::endl;
    }
    /*osg::UInt32 NumTypes = osg::FieldFactory::the().getNFieldTypes();
    std::cout << "Field Types: " << NumTypes << std::endl;
    for(osg::UInt32 i=1 ; i<NumTypes ; ++i)
    {
       std::cout << "   " << osg::FieldFactory::the().getFieldType(i)->getName() << std::endl;
    }*/
    //********************************Temp//********************************

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
   
   osg::ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->update(Elps);

   TheAnimation->update(TheAnimationAdvancer);
   TheGeometryPositionAnimation->update(TheAnimationAdvancer);
   TheGeometryNormalAnimation->update(TheAnimationAdvancer);

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
#include <OpenSG/Animation/OSGKeyframeSequenceVec3f.h>
//#include "KeyframeSequence/OSGKeyframeSequenceQuaternion.h"
#include <OpenSG/Animation/OSGKeyframeAnimator.h>
#include <OpenSG/Animation/OSGFieldAnimation.h>

#include <OpenSG/Animation/OSGKeyframeSequenceGeoPositionsPtr.h>
#include <OpenSG/Animation/OSGGeoPositionDifferenceSet.h>
#include <OpenSG/Animation/OSGKeyframeSequenceGeoNormalsPtr.h>
#include <OpenSG/Animation/OSGGeoNormalDifferenceSet.h>
#include <OpenSG/Animation/OSGGeometryAnimation.h>
#include <OpenSG/OSGGeometry.h>

void setupBlendGeometry(void)
{
    
   osg::NodePtr BaseGeometryNode = NamedNodeFinder::find(BubbleBlendGeometryNode, "Base Geometry");
   osg::NodePtr XDeformGeometryNode = NamedNodeFinder::find(BubbleBlendGeometryNode, "X Deform Geometry");
   osg::NodePtr YDeformGeometryNode = NamedNodeFinder::find(BubbleBlendGeometryNode, "Y Deform Geometry");
   osg::NodePtr ZDeformGeometryNode = NamedNodeFinder::find(BubbleBlendGeometryNode, "Z Deform Geometry");

   if(BaseGeometryNode == NullFC)
   {
      std::cout << "BaseGeometryNode Not Found." << std::endl;
      return;
   }
   if(XDeformGeometryNode == NullFC)
   {
      std::cout << "XDeformGeometryNode Not Found." << std::endl;
      return;
   }
   if(YDeformGeometryNode == NullFC)
   {
      std::cout << "YDeformGeometryNode Not Found." << std::endl;
      return;
   }
   if(ZDeformGeometryNode == NullFC)
   {
      std::cout << "ZDeformGeometryNode Not Found." << std::endl;
      return;
   }

   osg::GeometryPtr BaseGeometryCore= osg::Geometry::Ptr::dcast( BaseGeometryNode->getCore() );
   osg::GeometryPtr BaseGeometryCoreCopy= osg::Geometry::Ptr::dcast( deepClone(BaseGeometryCore, std::string("")) );
   osg::GeometryPtr XDeformGeometryCore= osg::Geometry::Ptr::dcast( XDeformGeometryNode->getCore() );
   osg::GeometryPtr YDeformGeometryCore= osg::Geometry::Ptr::dcast( YDeformGeometryNode->getCore() );
   osg::GeometryPtr ZDeformGeometryCore= osg::Geometry::Ptr::dcast( ZDeformGeometryNode->getCore() );

   //Positions Difference Sets
   osg::GeoPositionDifferenceSetPtr XDeformGeometryDiffSet = GeoPositionDifferenceSet::create( BaseGeometryCore->getPositions(), XDeformGeometryCore->getPositions() );
   osg::GeoPositionDifferenceSetPtr YDeformGeometryDiffSet = GeoPositionDifferenceSet::create( BaseGeometryCore->getPositions(), YDeformGeometryCore->getPositions() );
   osg::GeoPositionDifferenceSetPtr ZDeformGeometryDiffSet = GeoPositionDifferenceSet::create( BaseGeometryCore->getPositions(), ZDeformGeometryCore->getPositions() );
   osg::GeoPositionDifferenceSetPtr NoDeformGeometryDiffSet = GeoPositionDifferenceSet::create( BaseGeometryCore->getPositions(), BaseGeometryCore->getPositions() );
   
   //Normals Difference Sets
   osg::GeoNormalDifferenceSetPtr XDeformGeometryNormalDiffSet = GeoNormalDifferenceSet::create( BaseGeometryCore->getNormals(), XDeformGeometryCore->getNormals() );
   osg::GeoNormalDifferenceSetPtr YDeformGeometryNormalDiffSet = GeoNormalDifferenceSet::create( BaseGeometryCore->getNormals(), YDeformGeometryCore->getNormals() );
   osg::GeoNormalDifferenceSetPtr ZDeformGeometryNormalDiffSet = GeoNormalDifferenceSet::create( BaseGeometryCore->getNormals(), ZDeformGeometryCore->getNormals() );
   osg::GeoNormalDifferenceSetPtr NoDeformGeometryNormalDiffSet = GeoNormalDifferenceSet::create( BaseGeometryCore->getNormals(), BaseGeometryCore->getNormals() );
   
   //Create the BlendGeometry Core
   osg::BlendGeometryPtr TheBlendGeometry = osg::BlendGeometry::create(BaseGeometryCore);
   beginEditCP(TheBlendGeometry, osg::BlendGeometry::GeoPositionDifferenceSetsFieldMask |
                                 osg::BlendGeometry::GeoNormalDifferenceSetsFieldMask);
      TheBlendGeometry->getBlendAmounts().addValue(1.0);
      TheBlendGeometry->getBlendAmounts().addValue(1.0);
      TheBlendGeometry->getBlendAmounts().addValue(1.0);

      TheBlendGeometry->getGeoPositionDifferenceSets().addValue(XDeformGeometryDiffSet);
      TheBlendGeometry->getGeoPositionDifferenceSets().addValue(YDeformGeometryDiffSet);
      TheBlendGeometry->getGeoPositionDifferenceSets().addValue(ZDeformGeometryDiffSet);
      
      TheBlendGeometry->getGeoNormalDifferenceSets().addValue(XDeformGeometryNormalDiffSet);
      TheBlendGeometry->getGeoNormalDifferenceSets().addValue(YDeformGeometryNormalDiffSet);
      TheBlendGeometry->getGeoNormalDifferenceSets().addValue(ZDeformGeometryNormalDiffSet);
   endEditCP(TheBlendGeometry);
   
   NodePtr BlendGeometryNode = osg::Node::create();
   beginEditCP(BlendGeometryNode);
      BlendGeometryNode->setCore(TheBlendGeometry);
   endEditCP(BlendGeometryNode);

   //Transformed Node
   osg::TransformPtr BlendGeometryTrans = osg::Transform::create();
   osg::Matrix BlendGeometryTransMatrix;
   BlendGeometryTransMatrix.setTranslate(5.0,0.0,0.0);

   beginEditCP(BlendGeometryTrans);
      BlendGeometryTrans->setMatrix(BlendGeometryTransMatrix);
   endEditCP(BlendGeometryTrans);


   BlendGeometryTransNode = osg::Node::create();
   beginEditCP(BlendGeometryTransNode);
      BlendGeometryTransNode->setCore(BlendGeometryTrans);
      BlendGeometryTransNode->addChild(BlendGeometryNode);
   endEditCP(BlendGeometryTransNode);
}

void setupGeometryAnimation(void)
{
   //Get the Base Cores
   osg::NodePtr BaseGeometryNode = NamedNodeFinder::find(BubbleBlendGeometryNode, "Base Geometry");
   osg::NodePtr XDeformGeometryNode = NamedNodeFinder::find(BubbleBlendGeometryNode, "X Deform Geometry");
   osg::NodePtr YDeformGeometryNode = NamedNodeFinder::find(BubbleBlendGeometryNode, "Y Deform Geometry");
   osg::NodePtr ZDeformGeometryNode = NamedNodeFinder::find(BubbleBlendGeometryNode, "Z Deform Geometry");

   if(BaseGeometryNode == NullFC)
   {
      std::cout << "BaseGeometryNode Not Found." << std::endl;
      return;
   }
   if(XDeformGeometryNode == NullFC)
   {
      std::cout << "XDeformGeometryNode Not Found." << std::endl;
      return;
   }
   if(YDeformGeometryNode == NullFC)
   {
      std::cout << "YDeformGeometryNode Not Found." << std::endl;
      return;
   }
   if(ZDeformGeometryNode == NullFC)
   {
      std::cout << "ZDeformGeometryNode Not Found." << std::endl;
      return;
   }

   osg::GeometryPtr BaseGeometryCore= osg::Geometry::Ptr::dcast( BaseGeometryNode->getCore() );
   osg::GeometryPtr BaseGeometryCoreCopy= osg::Geometry::Ptr::dcast( deepClone(BaseGeometryCore, std::string("")) );
   osg::GeometryPtr XDeformGeometryCore= osg::Geometry::Ptr::dcast( XDeformGeometryNode->getCore() );
   osg::GeometryPtr YDeformGeometryCore= osg::Geometry::Ptr::dcast( YDeformGeometryNode->getCore() );
   osg::GeometryPtr ZDeformGeometryCore= osg::Geometry::Ptr::dcast( ZDeformGeometryNode->getCore() );

   //Positions Difference Sets
   osg::GeoPositionDifferenceSetPtr XDeformGeometryDiffSet = GeoPositionDifferenceSet::create( BaseGeometryCore->getPositions(), XDeformGeometryCore->getPositions() );
   osg::GeoPositionDifferenceSetPtr YDeformGeometryDiffSet = GeoPositionDifferenceSet::create( BaseGeometryCore->getPositions(), YDeformGeometryCore->getPositions() );
   osg::GeoPositionDifferenceSetPtr ZDeformGeometryDiffSet = GeoPositionDifferenceSet::create( BaseGeometryCore->getPositions(), ZDeformGeometryCore->getPositions() );
   osg::GeoPositionDifferenceSetPtr NoDeformGeometryDiffSet = GeoPositionDifferenceSet::create( BaseGeometryCore->getPositions(), BaseGeometryCore->getPositions() );
   
   //Positions KeyframeSequence
   osg::KeyframeSequencePtr KeyframeSequence = osg::KeyframeSequenceGeoPositionsPtr::create();
   
   osg::beginEditCP(osg::KeyframeSequenceGeoPositionsPtr::Ptr::dcast(KeyframeSequence));
      osg::KeyframeSequenceGeoPositionsPtr::Ptr::dcast(KeyframeSequence)->setBaseValues(BaseGeometryCoreCopy->getPositions());
      //Add Difference Sets
      osg::KeyframeSequenceGeoPositionsPtr::Ptr::dcast(KeyframeSequence)->getKeyframeDifferenceSets().addValue(XDeformGeometryDiffSet);
      osg::KeyframeSequenceGeoPositionsPtr::Ptr::dcast(KeyframeSequence)->getKeyframeDifferenceSets().addValue(YDeformGeometryDiffSet);
      osg::KeyframeSequenceGeoPositionsPtr::Ptr::dcast(KeyframeSequence)->getKeyframeDifferenceSets().addValue(ZDeformGeometryDiffSet);
      osg::KeyframeSequenceGeoPositionsPtr::Ptr::dcast(KeyframeSequence)->getKeyframeDifferenceSets().addValue(NoDeformGeometryDiffSet);
   osg::endEditCP(osg::KeyframeSequenceGeoPositionsPtr::Ptr::dcast(KeyframeSequence));

   //Positions Animator
   osg::AnimatorPtr Animator = osg::KeyframeAnimator::create();
   osg::beginEditCP(Animator);
      osg::KeyframeAnimatorPtr::dcast(Animator)->setValues(KeyframeSequence);
      osg::KeyframeAnimatorPtr::dcast(Animator)->getKeys().push_back(0.0);
      osg::KeyframeAnimatorPtr::dcast(Animator)->getKeys().push_back(1.0);
      osg::KeyframeAnimatorPtr::dcast(Animator)->getKeys().push_back(2.0);
      osg::KeyframeAnimatorPtr::dcast(Animator)->getKeys().push_back(3.0);
      osg::KeyframeAnimatorPtr::dcast(Animator)->getKeys().push_back(4.0);
   osg::endEditCP(Animator);
   
   //Positions Animation
   TheGeometryPositionAnimation = osg::GeometryAnimation::create();
   osg::beginEditCP(TheGeometryPositionAnimation);
      osg::GeometryAnimationPtr::dcast(TheGeometryPositionAnimation)->setAnimator(Animator);
      osg::GeometryAnimationPtr::dcast(TheGeometryPositionAnimation)->setFieldName( std::string("positions") );
      osg::GeometryAnimationPtr::dcast(TheGeometryPositionAnimation)->setInterpolationType(osg::LINEAR_INTERPOLATION);
      osg::GeometryAnimationPtr::dcast(TheGeometryPositionAnimation)->setGeometryCore(BaseGeometryCore);
      osg::GeometryAnimationPtr::dcast(TheGeometryPositionAnimation)->setReplacementPolicy(osg::OVERWRITE);
      osg::GeometryAnimationPtr::dcast(TheGeometryPositionAnimation)->setCycling(-1);
   osg::endEditCP(TheGeometryPositionAnimation);
   
   //Normals Difference Sets
   osg::GeoNormalDifferenceSetPtr XDeformGeometryNormalDiffSet = GeoNormalDifferenceSet::create( BaseGeometryCore->getNormals(), XDeformGeometryCore->getNormals() );
   osg::GeoNormalDifferenceSetPtr YDeformGeometryNormalDiffSet = GeoNormalDifferenceSet::create( BaseGeometryCore->getNormals(), YDeformGeometryCore->getNormals() );
   osg::GeoNormalDifferenceSetPtr ZDeformGeometryNormalDiffSet = GeoNormalDifferenceSet::create( BaseGeometryCore->getNormals(), ZDeformGeometryCore->getNormals() );
   osg::GeoNormalDifferenceSetPtr NoDeformGeometryNormalDiffSet = GeoNormalDifferenceSet::create( BaseGeometryCore->getNormals(), BaseGeometryCore->getNormals() );
   
   //Normals KeyframeSequence
   osg::KeyframeSequencePtr KeyframeSequenceNormal = osg::KeyframeSequenceGeoNormalsPtr::create();
   
   osg::beginEditCP(osg::KeyframeSequenceGeoNormalsPtr::Ptr::dcast(KeyframeSequenceNormal));
      osg::KeyframeSequenceGeoNormalsPtr::Ptr::dcast(KeyframeSequenceNormal)->setBaseValues(BaseGeometryCoreCopy->getNormals());
      //Add Difference Sets
      osg::KeyframeSequenceGeoNormalsPtr::Ptr::dcast(KeyframeSequenceNormal)->getKeyframeDifferenceSets().addValue(XDeformGeometryNormalDiffSet);
      osg::KeyframeSequenceGeoNormalsPtr::Ptr::dcast(KeyframeSequenceNormal)->getKeyframeDifferenceSets().addValue(YDeformGeometryNormalDiffSet);
      osg::KeyframeSequenceGeoNormalsPtr::Ptr::dcast(KeyframeSequenceNormal)->getKeyframeDifferenceSets().addValue(ZDeformGeometryNormalDiffSet);
      osg::KeyframeSequenceGeoNormalsPtr::Ptr::dcast(KeyframeSequenceNormal)->getKeyframeDifferenceSets().addValue(NoDeformGeometryNormalDiffSet);
   osg::endEditCP(osg::KeyframeSequenceGeoNormalsPtr::Ptr::dcast(KeyframeSequenceNormal));

   //Normals Animator
   osg::AnimatorPtr AnimatorNormal = osg::KeyframeAnimator::create();
   osg::beginEditCP(AnimatorNormal);
      osg::KeyframeAnimatorPtr::dcast(AnimatorNormal)->setValues(KeyframeSequenceNormal);
      osg::KeyframeAnimatorPtr::dcast(AnimatorNormal)->getKeys().push_back(0.0);
      osg::KeyframeAnimatorPtr::dcast(AnimatorNormal)->getKeys().push_back(1.0);
      osg::KeyframeAnimatorPtr::dcast(AnimatorNormal)->getKeys().push_back(2.0);
      osg::KeyframeAnimatorPtr::dcast(AnimatorNormal)->getKeys().push_back(3.0);
      osg::KeyframeAnimatorPtr::dcast(AnimatorNormal)->getKeys().push_back(4.0);
   osg::endEditCP(AnimatorNormal);
   
   //Normals Animation
   TheGeometryNormalAnimation = osg::GeometryAnimation::create();
   osg::beginEditCP(TheGeometryNormalAnimation);
      osg::GeometryAnimationPtr::dcast(TheGeometryNormalAnimation)->setAnimator(AnimatorNormal);
      osg::GeometryAnimationPtr::dcast(TheGeometryNormalAnimation)->setFieldName( std::string("normals") );
      osg::GeometryAnimationPtr::dcast(TheGeometryNormalAnimation)->setInterpolationType(osg::LINEAR_INTERPOLATION);
      osg::GeometryAnimationPtr::dcast(TheGeometryNormalAnimation)->setGeometryCore(BaseGeometryCore);
      osg::GeometryAnimationPtr::dcast(TheGeometryNormalAnimation)->setReplacementPolicy(osg::OVERWRITE);
      osg::GeometryAnimationPtr::dcast(TheGeometryNormalAnimation)->setCycling(-1);
   osg::endEditCP(TheGeometryNormalAnimation);
}

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
   osg::FieldContainerPtr AnimatedObject = getFieldContainer("ComponentTransform",std::string("TorusNodeTransformationCore"));
   
   //Animation
   TheAnimation = osg::FieldAnimation::create();
   osg::beginEditCP(TheAnimation);
      osg::FieldAnimationPtr::dcast(TheAnimation)->setAnimator(Animator);
      osg::FieldAnimationPtr::dcast(TheAnimation)->setContainer(AnimatedObject);
      osg::FieldAnimationPtr::dcast(TheAnimation)->setFieldName( std::string("translation") );
      osg::FieldAnimationPtr::dcast(TheAnimation)->setInterpolationType(osg::CUBIC_INTERPOLATION);
      osg::FieldAnimationPtr::dcast(TheAnimation)->setCycling(-1);
   osg::endEditCP(TheAnimation);

   //Animation Advancer
   TheAnimationAdvancer = osg::ElapsedTimeAnimationAdvancer::create();
   osg::beginEditCP(TheAnimationAdvancer);
   osg::ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->setStartTime( 0.0 );
   osg::beginEditCP(TheAnimationAdvancer);
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
