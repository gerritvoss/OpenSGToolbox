// 
// OpenSGToolbox Tutorial: 13MeshBlending 
//
// Creates a skeleton and a "skin" geometry and binds them together
// using a skeleton blended geometry.
//


// General OpenSG configuration, needed everywhere
#include "OSGConfig.h"

// A little helper to simplify scene management and interaction
#include "OSGSimpleSceneManager.h"
#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"
#include "OSGWindowUtils.h"

// Input
#include "OSGKeyListener.h"
#include "OSGUpdateListener.h"

#include "OSGLineChunk.h"
#include "OSGBlendChunk.h"
#include "OSGChunkMaterial.h"
#include "OSGMaterialChunk.h"

#include "OSGRandomPoolManager.h"

#include "OSGGeoProperties.h"
#include "OSGTypedGeoIntegralProperty.h"
#include "OSGTypedGeoVectorProperty.h"

#include "OSGKeyframeSequences.h"
#include "OSGFieldAnimation.h"
#include "OSGKeyframeAnimator.h"
#include "OSGNameAttachment.h"
#include "OSGSkeletonAnimation.h"
#include "OSGSkeleton.h"
#include "OSGJoint.h"
#include "OSGSkeletonDrawable.h"

#include "OSGSimpleGeometry.h"
#include "OSGSkeletonBlendedGeometry.h"

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;
WindowEventProducerUnrecPtr TutorialWindow;

Time TimeLastIdle;
NodeUnrecPtr SkeletonNode;
NodeUnrecPtr UnboundGeometry;
NodeUnrecPtr MeshNode;
SkeletonAnimationUnrecPtr TheSkeletonAnimation;
bool animationPaused = false;

JointUnrecPtr Pelvis,LeftHip,RightHip,LeftKnee,RightKnee,LeftFoot,RightFoot,LeftToes,RightToes, Clavicle, LeftShoulder,RightShoulder,LeftElbow,RightElbow,LeftHand,RightHand,LeftFingers,RightFingers,Head; 
SkeletonUnrecPtr ExampleSkeleton;

// The pointer to the transformation
TransformUnrecPtr trans;

// The pointer to the geometry core
GeometryUnrecPtr geo;





// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);
void setupAnimation(void);

// Create a class to allow for the use of the keyboard shortcuts 
class TutorialKeyListener : public KeyListener
{
public:

    virtual void keyPressed(const KeyEventUnrecPtr e)
    {
        //Exit
        if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
        {
            TutorialWindow->closeWindow();
        }

        //Toggle animation
        if(e->getKey() == KeyEvent::KEY_SPACE)
        {
            if(animationPaused)
                animationPaused = false;
            else
                animationPaused = true;
        }

        //Toggle bind pose
        if(e->getKey() == KeyEvent::KEY_B)
        {
            if(e->getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
            {
                //Toggle mesh
                if(UnboundGeometry->getTravMask() == 0)
                {
                    UnboundGeometry->setTravMask(1);
                } 
                else
                {
                    UnboundGeometry->setTravMask(0);
                }
            }
            else
            {
                //Toggle skeleton
                if(dynamic_cast<SkeletonDrawable*>(SkeletonNode->getCore())->getDrawBindPose() == false)
                {
                    dynamic_cast<SkeletonDrawable*>(SkeletonNode->getCore())->setDrawBindPose(true);
                } 
                else
                {
                    dynamic_cast<SkeletonDrawable*>(SkeletonNode->getCore())->setDrawBindPose(false);
                }
            }
        }

        //Toggle current pose
        if(e->getKey() == KeyEvent::KEY_P)
        {
            if(e->getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
            {
                //Toggle mesh
                if(MeshNode->getTravMask() == 0)
                {
                    MeshNode->setTravMask(1);
                } 
                else
                {
                    MeshNode->setTravMask(0);
                }
            }
            else
            {
                //Toggle skeleton
                if(dynamic_cast<SkeletonDrawable*>(SkeletonNode->getCore())->getDrawPose() == false)
                {
                    dynamic_cast<SkeletonDrawable*>(SkeletonNode->getCore())->setDrawPose(true);
                } 
                else
                {
                    dynamic_cast<SkeletonDrawable*>(SkeletonNode->getCore())->setDrawPose(false);
                }
            }
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

    //Print key command info
    std::cout << "\n\nKEY COMMANDS:" << std::endl;
    std::cout << "space   Play/Pause the animation" << std::endl;
    std::cout << "B       Show/Hide the bind pose skeleton" << std::endl;
    std::cout << "SHIFT-B Show/Hide the bind pose mesh" << std::endl;
    std::cout << "P       Show/Hide the current pose skeleton" << std::endl;
    std::cout << "SHIFT-P Show/Hide the current pose mesh" << std::endl;
    std::cout << "CTRL-Q  Exit\n\n" << std::endl;


    //SkeletonDrawer System Material
    LineChunkUnrecPtr ExampleLineChunk = LineChunk::create();
    ExampleLineChunk->setWidth(2.0f);
    ExampleLineChunk->setSmooth(true);

    BlendChunkUnrecPtr ExampleBlendChunk = BlendChunk::create();
    ExampleBlendChunk->setSrcFactor(GL_SRC_ALPHA);
    ExampleBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);

    MaterialChunkUnrecPtr ExampleMaterialChunk = MaterialChunk::create();
    ExampleMaterialChunk->setAmbient(Color4f(1.0f,1.0f,1.0f,1.0f));
    ExampleMaterialChunk->setDiffuse(Color4f(0.0f,0.0f,0.0f,1.0f));
    ExampleMaterialChunk->setSpecular(Color4f(0.0f,0.0f,0.0f,1.0f));

    ChunkMaterialUnrecPtr ExampleMaterial = ChunkMaterial::create();
    ExampleMaterial->addChunk(ExampleLineChunk);
    ExampleMaterial->addChunk(ExampleMaterialChunk);
    ExampleMaterial->addChunk(ExampleBlendChunk);


    //===========================================Joints==================================================================
    Matrix TempMat;

    /*================================================================================================*/
    /*                                       Left Fingers                                                 */
    LeftFingers = Joint::create(); //create a joint called LeftFingers 
    TempMat.setTranslate(1.0,0.0,0.0);
    LeftFingers->setRelativeTransformation(TempMat);
    LeftFingers->setBindRelativeTransformation(TempMat);

    /*================================================================================================*/
    /*                                       Right Fingers                                                 */
    RightFingers = Joint::create(); //create a joint called RightFingers 
    TempMat.setTranslate(-1.0,0.0,0.0);
    RightFingers->setRelativeTransformation(TempMat);
    RightFingers->setBindRelativeTransformation(TempMat);
    /*================================================================================================*/
    /*                                       Left Hand                                                 */
    LeftHand = Joint::create(); //create a joint called LeftHand 
    TempMat.setTranslate(2.0,0.0,0.0);
    LeftHand->setRelativeTransformation(TempMat);
    LeftHand->setBindRelativeTransformation(TempMat);
    LeftHand->pushToChildJoints(LeftFingers);

    /*================================================================================================*/
    /*                                       Right Hand                                                 */
    RightHand = Joint::create(); //create a joint called RightHand 
    TempMat.setTranslate(-2.0,0.0,0.0);
    RightHand->setRelativeTransformation(TempMat);
    RightHand->setBindRelativeTransformation(TempMat);
    RightHand->pushToChildJoints(RightFingers);
    /*================================================================================================*/
    /*                                       Left Elbow                                                 */
    LeftElbow = Joint::create(); //create a joint called LeftElbow 
    TempMat.setTranslate(2.0,0.0,0.0);
    LeftElbow->setRelativeTransformation(TempMat);
    LeftElbow->setBindRelativeTransformation(TempMat);
    LeftElbow->pushToChildJoints(LeftHand);

    /*================================================================================================*/
    /*                                       Right Elbow                                                 */
    RightElbow = Joint::create(); //create a joint called RightElbow 
    TempMat.setTranslate(-2.0,0.0,0.0);
    RightElbow->setRelativeTransformation(TempMat);
    RightElbow->setBindRelativeTransformation(TempMat);
    RightElbow->pushToChildJoints(RightHand);
    /*================================================================================================*/
    /*                                       Left Shoulder                                                 */
    LeftShoulder = Joint::create(); //create a joint called LeftShoulder 
    TempMat.setTranslate(1.0,-0.5,0.0);
    LeftShoulder->setRelativeTransformation(TempMat);
    LeftShoulder->setBindRelativeTransformation(TempMat);
    LeftShoulder->pushToChildJoints(LeftElbow);

    /*================================================================================================*/
    /*                                       Right Shoulder                                                 */
    RightShoulder = Joint::create(); //create a joint called RightShoulder 
    TempMat.setTranslate(-1.0,-0.5,0.0);
    RightShoulder->setRelativeTransformation(TempMat);
    RightShoulder->setBindRelativeTransformation(TempMat);
    RightShoulder->pushToChildJoints(RightElbow);

    /*================================================================================================*/
    /*                                       Head                                                 */
    Head = Joint::create(); //create a joint called Head 
    TempMat.setTranslate(0.0,1.0,0.0);
    Head->setRelativeTransformation(TempMat);
    Head->setBindRelativeTransformation(TempMat);

    /*================================================================================================*/
    /*                                       Clavicle                                                   */
    Clavicle = Joint::create(); //create a joint called Clavicle 
    TempMat.setTranslate(0.0,5.0,0.0);
    Clavicle->setRelativeTransformation(TempMat);
    Clavicle->setBindRelativeTransformation(TempMat);
    Clavicle->pushToChildJoints(LeftShoulder);
    Clavicle->pushToChildJoints(RightShoulder);
    Clavicle->pushToChildJoints(Head);

    /*================================================================================================*/
    /*                                       Left Toes                                                 */
    LeftToes = Joint::create(); //create a bone called ExampleChildbone
    TempMat.setTranslate(0.0,0.0,1.0);
    LeftToes->setRelativeTransformation(TempMat);
    LeftToes->setBindRelativeTransformation(TempMat);

    /*================================================================================================*/
    /*                                       Right Toes                                                 */
    RightToes = Joint::create(); //create a joint called RightToes 
    TempMat.setTranslate(0.0,0.0,1.0);
    RightToes->setRelativeTransformation(TempMat);
    RightToes->setBindRelativeTransformation(TempMat);
    /*================================================================================================*/
    /*                                       Left Foot                                                 */
    LeftFoot = Joint::create(); //create a joint called LeftFoot 
    TempMat.setTranslate(0.0,-3.0,0.0);
    LeftFoot->setRelativeTransformation(TempMat);
    LeftFoot->setBindRelativeTransformation(TempMat);
    LeftFoot->pushToChildJoints(LeftToes);

    /*================================================================================================*/
    /*                                       Right Foot                                                 */
    RightFoot = Joint::create(); //create a joint called RightFoot 
    TempMat.setTranslate(0.0,-3.0,0.0);
    RightFoot->setRelativeTransformation(TempMat);
    RightFoot->setBindRelativeTransformation(TempMat);
    RightFoot->pushToChildJoints(RightToes);
    /*================================================================================================*/
    /*                                       Left Knee                                                 */
    LeftKnee = Joint::create(); //create a joint called LeftKnee 
    TempMat.setTranslate(0.0,-3.0,0.0);
    LeftKnee->setRelativeTransformation(TempMat);
    LeftKnee->setBindRelativeTransformation(TempMat);
    LeftKnee->pushToChildJoints(LeftFoot);

    /*================================================================================================*/
    /*                                       Right Knee                                                 */
    RightKnee = Joint::create(); //create a joint called RightKnee 
    TempMat.setTranslate(0.0,-3.0,0.0);
    RightKnee->setRelativeTransformation(TempMat);
    RightKnee->setBindRelativeTransformation(TempMat);
    RightKnee->pushToChildJoints(RightFoot);

    /*================================================================================================*/
    /*                                       Left Hip                                                 */
    LeftHip = Joint::create(); //create a joint called LeftHip 
    TempMat.setTranslate(1.0,-1.0,0.0);
    LeftHip->setRelativeTransformation(TempMat);
    LeftHip->setBindRelativeTransformation(TempMat);
    LeftHip->pushToChildJoints(LeftKnee);

    /*================================================================================================*/
    /*                                       Right Hip                                                 */
    RightHip = Joint::create(); //create a joint called RightHip 
    TempMat.setTranslate(-1.0,-1.0,0.0);
    RightHip->setRelativeTransformation(TempMat);
    RightHip->setBindRelativeTransformation(TempMat);
    RightHip->pushToChildJoints(RightKnee);

    /*================================================================================================*/
    /*                                       Pelvis                                                   */
    Pelvis = Joint::create(); //create a joint called Pelvis 
    TempMat.setTranslate(0.0,7.0,0.0);
    Pelvis->setRelativeTransformation(TempMat);
    Pelvis->setBindRelativeTransformation(TempMat);
    Pelvis->pushToChildJoints(LeftHip);
    Pelvis->pushToChildJoints(RightHip);
    Pelvis->pushToChildJoints(Clavicle);



    //Skeleton
    ExampleSkeleton = Skeleton::create();
    ExampleSkeleton->pushToRootJoints(Pelvis);

    //Create a geometry to attach to the skeleton (i.e-> skin)
    GeoUInt8PropertyUnrecPtr type = GeoUInt8Property::create();        
        type->push_back(GL_QUADS);

    GeoUInt32PropertyUnrecPtr lens = GeoUInt32Property::create();    
        lens->push_back(72);
    GeoPnt3fPropertyUnrecPtr  pnts  = GeoPnt3fProperty ::create();
        // the points of the Quads

        //Back
        pnts->push_back(Pnt3f(-0.5,  6.0,  0));
        pnts->push_back(Pnt3f( 0.5,  6.0,  0));
        pnts->push_back(Pnt3f( 0.5,  12.0,  0));
        pnts->push_back(Pnt3f(-0.5,  12.0,  0));

        //Head
        pnts->push_back(Pnt3f(-0.5,  12,  0));
        pnts->push_back(Pnt3f( 0.5,  12,  0));
        pnts->push_back(Pnt3f( 0.5,  13,  0));
        pnts->push_back(Pnt3f(-0.5,  13,  0));

        //Left Shoulder
        pnts->push_back(Pnt3f(0.0,  11.5,  0));
        pnts->push_back(Pnt3f(0.0,  12.5,  0));
        pnts->push_back(Pnt3f(1.0,  12.0,  0));
        pnts->push_back(Pnt3f(1.0,  11.0,  0));

        //Left Humerus
        pnts->push_back(Pnt3f(1.0,  11.0,  0));
        pnts->push_back(Pnt3f(1.0,  12.0,  0));
        pnts->push_back(Pnt3f(3.0,  12.0,  0));
        pnts->push_back(Pnt3f(3.0,  11.0,  0));

        //Left Radius
        pnts->push_back(Pnt3f(3.0,  11.0,  0));
        pnts->push_back(Pnt3f(3.0,  12.0,  0));
        pnts->push_back(Pnt3f(5.0,  12.0,  0));
        pnts->push_back(Pnt3f(5.0,  11.0,  0));

        //Left Hand
        pnts->push_back(Pnt3f(5.0,  11.0,  0));
        pnts->push_back(Pnt3f(5.0,  12.0,  0));
        pnts->push_back(Pnt3f(6.0,  12.0,  0));
        pnts->push_back(Pnt3f(6.0,  11.0,  0));

        //Right Shoulder
        pnts->push_back(Pnt3f(0.0,  11.5,  0));
        pnts->push_back(Pnt3f(0.0,  12.5,  0));
        pnts->push_back(Pnt3f(-1.0,  12.0,  0));
        pnts->push_back(Pnt3f(-1.0,  11.0,  0));

        //Right Humerus
        pnts->push_back(Pnt3f(-1.0,  11.0,  0));
        pnts->push_back(Pnt3f(-1.0,  12.0,  0));
        pnts->push_back(Pnt3f(-3.0,  12.0,  0));
        pnts->push_back(Pnt3f(-3.0,  11.0,  0));

        //Right Radius
        pnts->push_back(Pnt3f(-3.0,  11.0,  0));
        pnts->push_back(Pnt3f(-3.0,  12.0,  0));
        pnts->push_back(Pnt3f(-5.0,  12.0,  0));
        pnts->push_back(Pnt3f(-5.0,  11.0,  0));

        //Right Hand
        pnts->push_back(Pnt3f(-5.0,  11.0,  0));
        pnts->push_back(Pnt3f(-5.0,  12.0,  0));
        pnts->push_back(Pnt3f(-6.0,  12.0,  0));
        pnts->push_back(Pnt3f(-6.0,  11.0,  0));

        //Left Hip
        pnts->push_back(Pnt3f(0.0, 6.5,  0));
        pnts->push_back(Pnt3f(0.5, 7.5,  0));
        pnts->push_back(Pnt3f( 1.5,  6.0,  0));
        pnts->push_back(Pnt3f(0.5,  6.0,  0));

        //Left Femur
        pnts->push_back(Pnt3f(0.5,  6.0,  0));
        pnts->push_back(Pnt3f( 1.5,  6.0,  0));
        pnts->push_back(Pnt3f( 1.5,  3.0,  0));
        pnts->push_back(Pnt3f(0.5,  3.0,  0));

        //Left Tibia
        pnts->push_back(Pnt3f(0.5,  3.0,  0));
        pnts->push_back(Pnt3f( 1.5,  3.0,  0));
        pnts->push_back(Pnt3f( 1.5,  0.0,  0));
        pnts->push_back(Pnt3f(0.5,  0.0,  0));

        //Left Foot
        pnts->push_back(Pnt3f(0.5,  0.0,  0));
        pnts->push_back(Pnt3f( 1.5,  0.0,  0));
        pnts->push_back(Pnt3f( 1.5,  0.0,  1.0));
        pnts->push_back(Pnt3f(0.5,  0.0,  1.0));


        //Right Hip
        pnts->push_back(Pnt3f(0.0, 6.5,  0));
        pnts->push_back(Pnt3f(-0.5, 7.5,  0));
        pnts->push_back(Pnt3f( -1.5,  6.0,  0));
        pnts->push_back(Pnt3f(-0.5,  6.0,  0));

        //Right Femur
        pnts->push_back(Pnt3f(-0.5,  6.0,  0));
        pnts->push_back(Pnt3f( -1.5,  6.0,  0));
        pnts->push_back(Pnt3f( -1.5,  3.0,  0));
        pnts->push_back(Pnt3f(-0.5,  3.0,  0));

        //Right Tibia
        pnts->push_back(Pnt3f(-0.5,  3.0,  0));
        pnts->push_back(Pnt3f( -1.5,  3.0,  0));
        pnts->push_back(Pnt3f( -1.5,  0.0,  0));
        pnts->push_back(Pnt3f(-0.5,  0.0,  0));

        //Right Foot
        pnts->push_back(Pnt3f(-0.5,  0.0,  0));
        pnts->push_back(Pnt3f( -1.5,  0.0,  0));
        pnts->push_back(Pnt3f( -1.5,  0.0,  1.0));
        pnts->push_back(Pnt3f(-0.5,  0.0,  1.0));

    //Normals
    GeoVec3fPropertyUnrecPtr  norms = GeoVec3fProperty ::create();
    geo=Geometry::create();
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));

    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));

    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));

    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));

    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));

    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));

    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));

    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));

    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));

    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));

    //Left Hip
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));

    //Left Femur
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));

    //Left Tibia
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));

    //Left Foot
    norms->push_back(Vec3f( 0.0,1.0,0.0));
    norms->push_back(Vec3f( 0.0,1.0,0.0));
    norms->push_back(Vec3f( 0.0,1.0,0.0));
    norms->push_back(Vec3f( 0.0,1.0,0.0));

    //Right Hip
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));

    //Right Femur
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));

    //Right Tibia
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));
    norms->push_back(Vec3f( 0.0,0.0,1.0));

    //Right Foot
    norms->push_back(Vec3f( 0.0,1.0,0.0));
    norms->push_back(Vec3f( 0.0,1.0,0.0));
    norms->push_back(Vec3f( 0.0,1.0,0.0));
    norms->push_back(Vec3f( 0.0,1.0,0.0));

    //Tell the geometry (geo) to use the points and normals we just defined
    geo->setTypes    (type);
    geo->setLengths  (lens);
    geo->setPositions(pnts);
    geo->setNormals(norms);

    // assign a material to the geometry to make it visible. The details
    // of materials are defined later.
    geo->setMaterial(getDefaultMaterial());   

    //Create unbound geometry node (for displaying mesh in its bind pose)
    UnboundGeometry = Node::create();
    UnboundGeometry->setCore(geo);
    UnboundGeometry->setTravMask(0);  //By default, we won't show the mesh's bind pose




    //SkeletonDrawer
    SkeletonDrawableUnrecPtr ExampleSkeletonDrawable = SkeletonDrawable::create();
    ExampleSkeletonDrawable->setSkeleton(ExampleSkeleton);
    ExampleSkeletonDrawable->setMaterial(ExampleMaterial);
    ExampleSkeletonDrawable->setDrawBindPose(false);  //By default, we don't draw the skeleton's bind pose
    ExampleSkeletonDrawable->setBindPoseColor(Color4f(0.0, 1.0, 0.0, 1.0));  //When drawn, the skeleton's bind pose renders green
    ExampleSkeletonDrawable->setDrawPose(true);  //By default, we do draw the skeleton's current pose
    ExampleSkeletonDrawable->setPoseColor(Color4f(0.0, 0.0, 1.0, 1.0));  //The skeleton's current pose renders blue

    //Skeleton Node
    SkeletonNode = Node::create();
    SkeletonNode->setCore(ExampleSkeletonDrawable);




    // Skeleton Blended Geometry
    // Here we are attaching the "skin" to the skeleton so that when the skeleton is animated, the skin moves with it
    SkeletonBlendedGeometryUnrecPtr TheNewSkeletonGeometry = SkeletonBlendedGeometry::create();
    TheNewSkeletonGeometry->pushToSkeletons(ExampleSkeleton);
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

    MeshNode = Node::create();
    MeshNode->setCore(TheNewSkeletonGeometry);

    //Create scene node 
    NodeUnrecPtr scene = Node::create();
    scene->setCore(Group::create());
    scene->addChild(UnboundGeometry);
    scene->addChild(SkeletonNode);
    scene->addChild(MeshNode);

    mgr->setRoot(scene);

    //Setup the Animation
    setupAnimation();


    // Show the whole Scene
    mgr->showAll();


    //Open Window
    Vec2f WinSize(TutorialWindow->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindow->getDesktopSize() - WinSize) *0.5);
    TutorialWindow->openWindow(WinPos,
            WinSize,
            "13MeshBlending");

    //Main Loop
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
    Matrix TempMat;

    //We create an animation and an animator for each joint we wish to animate

    //Left Elbow
    KeyframeTransformationSequenceUnrecPtr LeftElbowKeyframes = KeyframeTransformationSequenceMatrix4f::create();
    //Make keyframes
    TempMat.setTransform(Vec3f(2.0,0.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0f));
    LeftElbowKeyframes->addKeyframe(TempMat,0.0f);
    TempMat.setTransform(Vec3f(2.0,0.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),1.57f));
    LeftElbowKeyframes->addKeyframe(TempMat,3.0f);
    TempMat.setTransform(Vec3f(2.0,0.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0f));
    LeftElbowKeyframes->addKeyframe(TempMat,6.0f);

    //Left Elbow Animator
    KeyframeAnimatorUnrecPtr LeftElbowAnimator = KeyframeAnimator::create();
    LeftElbowAnimator->setKeyframeSequence(LeftElbowKeyframes);

    //Right Elbow
    KeyframeTransformationSequenceUnrecPtr RightElbowKeyframes = KeyframeTransformationSequenceMatrix4f::create();
    //Make keyframes
    TempMat.setTransform(Vec3f(-2.0,0.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0f));
    RightElbowKeyframes->addKeyframe(TempMat,0.0f);
    TempMat.setTransform(Vec3f(-2.0,0.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),-1.57f));
    RightElbowKeyframes->addKeyframe(TempMat,3.0f);
    TempMat.setTransform(Vec3f(-2.0,0.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0f));
    RightElbowKeyframes->addKeyframe(TempMat,6.0f);

    //Right Elbow Animator
    KeyframeAnimatorUnrecPtr RightElbowAnimator = KeyframeAnimator::create();
    RightElbowAnimator->setKeyframeSequence(RightElbowKeyframes);

    //Left Shoulder
    KeyframeTransformationSequenceUnrecPtr LeftShoulderKeyframes = KeyframeTransformationSequenceMatrix4f::create();
    //Make keyframes
    TempMat.setTransform(Vec3f(1.0,-0.5,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0f));
    LeftShoulderKeyframes->addKeyframe(TempMat,0.0f);
    TempMat.setTransform(Vec3f(1.0,-0.5,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.4f));
    LeftShoulderKeyframes->addKeyframe(TempMat,3.0f);
    TempMat.setTransform(Vec3f(1.0,-0.5,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0f));
    LeftShoulderKeyframes->addKeyframe(TempMat,6.0f);

    //Left Shoulder Animator
    KeyframeAnimatorUnrecPtr LeftShoulderAnimator = KeyframeAnimator::create();
    LeftShoulderAnimator->setKeyframeSequence(LeftShoulderKeyframes);

    //Right Shoulder
    KeyframeTransformationSequenceUnrecPtr RightShoulderKeyframes = KeyframeTransformationSequenceMatrix4f::create();
    //Make keyframes
    TempMat.setTransform(Vec3f(-1.0,-0.5,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0f));
    RightShoulderKeyframes->addKeyframe(TempMat,0.0f);
    TempMat.setTransform(Vec3f(-1.0,-0.5,0.0),Quaternion(Vec3f(0.0,0.0,1.0),-0.4f));
    RightShoulderKeyframes->addKeyframe(TempMat,3.0f);
    TempMat.setTransform(Vec3f(-1.0,-0.5,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0f));
    RightShoulderKeyframes->addKeyframe(TempMat,6.0f);

    //Right Shoulder Animator
    KeyframeAnimatorUnrecPtr RightShoulderAnimator = KeyframeAnimator::create();
    RightShoulderAnimator->setKeyframeSequence(RightShoulderKeyframes);

    //Left Hip
    KeyframeTransformationSequenceUnrecPtr LeftHipKeyframes = KeyframeTransformationSequenceMatrix4f::create();
    //Make keyframes
    TempMat.setTransform(Vec3f(1.0,-1.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0f));
    LeftHipKeyframes->addKeyframe(TempMat,0.0f);
    TempMat.setTransform(Vec3f(1.0,-1.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.4f));
    LeftHipKeyframes->addKeyframe(TempMat,3.0f);
    TempMat.setTransform(Vec3f(1.0,-1.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0f));
    LeftHipKeyframes->addKeyframe(TempMat,6.0f);

    //Left Hip Animator
    KeyframeAnimatorUnrecPtr LeftHipAnimator = KeyframeAnimator::create();
    LeftHipAnimator->setKeyframeSequence(LeftHipKeyframes);

    //Right Hip
    KeyframeTransformationSequenceUnrecPtr RightHipKeyframes = KeyframeTransformationSequenceMatrix4f::create();
    //Make keyframes
    TempMat.setTransform(Vec3f(-1.0,-1.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0f));
    RightHipKeyframes->addKeyframe(TempMat,0.0f);
    TempMat.setTransform(Vec3f(-1.0,-1.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),-0.4f));
    RightHipKeyframes->addKeyframe(TempMat,3.0f);
    TempMat.setTransform(Vec3f(-1.0,-1.0,0.0),Quaternion(Vec3f(0.0,0.0,1.0),0.0f));
    RightHipKeyframes->addKeyframe(TempMat,6.0f);

    //Right Hip Animator
    KeyframeAnimatorUnrecPtr RightHipAnimator = KeyframeAnimator::create();
    RightHipAnimator->setKeyframeSequence(RightHipKeyframes);


    //Clavicle
    KeyframeTransformationSequenceUnrecPtr ClavicleKeyframes = KeyframeTransformationSequenceMatrix4f::create();
    //Make keyframes
    TempMat.setTransform(Vec3f(0.0,5.0,0.0));
    ClavicleKeyframes->addKeyframe(TempMat,0.0f);
    TempMat.setTransform(Vec3f(0.0,3.0,0.0));
    ClavicleKeyframes->addKeyframe(TempMat,2.0f);
    TempMat.setTransform(Vec3f(0.0,3.0,0.0));
    ClavicleKeyframes->addKeyframe(TempMat,4.0f);
    TempMat.setTransform(Vec3f(0.0,5.0,0.0));
    ClavicleKeyframes->addKeyframe(TempMat,6.0f);

    //Clavicle Animator
    KeyframeAnimatorUnrecPtr ClavicleAnimator = KeyframeAnimator::create();
    ClavicleAnimator->setKeyframeSequence(ClavicleKeyframes);

    //Skeleton Animation
    TheSkeletonAnimation = SkeletonAnimation::create();
    //Add the animators we just made to the skeleton animation
    TheSkeletonAnimation->addTransformationAnimator(LeftElbowAnimator, LeftElbow);  //Here we tell the skeleton animation the it should use the animator LeftElbowAnimator to animate the joint LeftElbow
    TheSkeletonAnimation->addTransformationAnimator(RightElbowAnimator, RightElbow);
    TheSkeletonAnimation->addTransformationAnimator(LeftShoulderAnimator, LeftShoulder);
    TheSkeletonAnimation->addTransformationAnimator(RightShoulderAnimator, RightShoulder);
    TheSkeletonAnimation->addTransformationAnimator(LeftHipAnimator, LeftHip);
    TheSkeletonAnimation->addTransformationAnimator(RightHipAnimator, RightHip);
    TheSkeletonAnimation->addTransformationAnimator(ClavicleAnimator, Clavicle);
    TheSkeletonAnimation->setSkeleton(ExampleSkeleton);

    TheSkeletonAnimation->attachUpdateProducer(TutorialWindow->editEventProducer());
    TheSkeletonAnimation->start();
}
