// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/Input/OSGWindowUtils.h>

// Input
#include <OpenSG/Input/OSGKeyListener.h>
#include <OpenSG/Input/OSGUpdateListener.h>
#include <OpenSG/Input/OSGWindowAdapter.h>

#include <OpenSG/OSGLineChunk.h>
#include <OpenSG/OSGBlendChunk.h>
#include <OpenSG/OSGChunkMaterial.h>
#include <OpenSG/OSGMaterialChunk.h>

//Animation
#include <OpenSG/Animation/OSGBone.h>
#include <OpenSG/Animation/OSGSkeleton.h>
#include <OpenSG/Animation/OSGSkeletonDrawable.h>

#include <OpenSG/Toolbox/OSGRandomPoolManager.h>

// FROM ANIMATION.CPP
#include <OpenSG/OSGTime.h>
#include <OpenSG/Animation/OSGKeyframeSequences.h>
#include <OpenSG/Animation/OSGFieldAnimation.h>
#include <OpenSG/Animation/OSGKeyframeAnimator.h>
#include <OpenSG/Animation/OSGElapsedTimeAnimationAdvancer.h>
#include <OpenSG/OSGSimpleAttachments.h>
#include <OpenSG/Animation/OSGSkeletonAnimation.h>
#include <OpenSG/Animation/OSGSkeleton.h>
#include <OpenSG/Animation/OSGBone.h>

#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/Animation/OSGSkeletonBlendedGeometry.h>



// Activate the OpenSG namespace
OSG_USING_NAMESPACE

// The SimpleSceneManager to manage simple applications
SimpleSceneManager *mgr;

osg::Time TimeLastIdle;
osg::AnimationPtr TheSkeletonAnimation;
osg::AnimationAdvancerPtr TheAnimationAdvancer;

bool ExitApp = false;


// The pointer to the transformation
TransformPtr trans;

// The pointer to the geometry core
GeometryPtr geo;





// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);
void setupAnimation(BonePtr TheLeftHumerus,BonePtr TheLeftRadius,BonePtr TheLeftHand,BonePtr TheLeftFemur,BonePtr TheRightHumerus,BonePtr TheRightRadius,BonePtr TheRightHand,BonePtr TheRightFemur,BonePtr TheTorso, SkeletonPtr TheSkeleton);

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
		osg::ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->update(e.getElapsedTime());

		TheSkeletonAnimation->update(TheAnimationAdvancer);
    }
};

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

	TutorialUpdateListener TheTutorialUpdateListener;
    TutorialWindowEventProducer->addUpdateListener(&TheTutorialUpdateListener);

    //Add Window Listener
    TutorialWindowListener TheTutorialWindowListener;
    TutorialWindowEventProducer->addWindowListener(&TheTutorialWindowListener);
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
	
    TutorialWindowEventProducer->openWindow(Pnt2f(0,0),
                                        Vec2f(1280,1024),
                                        "OpenSG 19SmoothAnimationWindow");
										

	//SkeletonDrawer System Material
	LineChunkPtr ExampleLineChunk = LineChunk::create();
	beginEditCP(ExampleLineChunk);
		ExampleLineChunk->setWidth(2.0f);
		ExampleLineChunk->setSmooth(true);
	endEditCP(ExampleLineChunk);

	BlendChunkPtr ExampleBlendChunk = BlendChunk::create();
	beginEditCP(ExampleBlendChunk);
	    ExampleBlendChunk->setSrcFactor(GL_SRC_ALPHA);
	    ExampleBlendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
	endEditCP(ExampleBlendChunk);

	MaterialChunkPtr ExampleMaterialChunk = MaterialChunk::create();
	beginEditCP(ExampleMaterialChunk);
		ExampleMaterialChunk->setAmbient(Color4f(1.0f,1.0f,1.0f,1.0f));
		ExampleMaterialChunk->setDiffuse(Color4f(0.0f,0.0f,0.0f,1.0f));
		ExampleMaterialChunk->setSpecular(Color4f(0.0f,0.0f,0.0f,1.0f));
		//ExampleMaterialChunk->setColorMaterial(GL_AMBIENT_AND_DIFFUSE);
	endEditCP(ExampleMaterialChunk);

	ChunkMaterialPtr ExampleMaterial = ChunkMaterial::create();
	beginEditCP(ExampleMaterial, ChunkMaterial::ChunksFieldMask);
		ExampleMaterial->addChunk(ExampleLineChunk);
		ExampleMaterial->addChunk(ExampleMaterialChunk);
		ExampleMaterial->addChunk(ExampleBlendChunk);
	endEditCP(ExampleMaterial, ChunkMaterial::ChunksFieldMask);

//===========================================BONE==================================================================
	const int num = 9;
	BonePtr Torso, LeftHumerus, LeftRadius, LeftHand, LeftFemur, LeftTibia, LeftFeet,
		           RightHumerus, RightRadius, RightHand, RightFemur, RightTibia, RightFeet;



/*================================================================================================*/
/*                                       TORSO                                                    */

	Torso = Bone::create(); //create a bone called ExampleChildbone
	beginEditCP(Torso, Bone::RotationFieldMask | Bone::LengthFieldMask | Bone::TranslationFieldMask);//use the field masks
		Torso->setLength(15.0f);
		Torso->setRotation(Quaternion(Vec3f(1,0,0), osgdegree2rad(90)));
		Torso->setTranslation(Vec3f(0,15,0));
	endEditCP(Torso, Bone::RotationFieldMask | Bone::LengthFieldMask | Bone::TranslationFieldMask);

	//Save current position as default position
	Torso->setBindPosition();
	

/*================================================================================================*/
/*                                    LEFT HUMERUS                                                */

	LeftHumerus = Bone::create(); //create a bone called ExampleChildbone
			beginEditCP(LeftHumerus, Bone::RotationFieldMask | Bone::LengthFieldMask| Bone::TranslationFieldMask);//use the field masks
				LeftHumerus->setLength(4.0f);
				LeftHumerus->setRotation(Quaternion(Vec3f(0,1,0), osgdegree2rad(90)));
				LeftHumerus->setTranslation(Vec3f(0,0,-10));
			endEditCP(LeftHumerus, Bone::RotationFieldMask | Bone::LengthFieldMask| Bone::TranslationFieldMask);

	//Save current position as default position
	LeftHumerus->setBindPosition();

/*================================================================================================*/
/*                                    LEFT RADIUS                                                 */


	LeftRadius = Bone::create(); //create a bone called ExampleChildbone
			beginEditCP(LeftRadius, Bone::RotationFieldMask | Bone::LengthFieldMask);//use the field masks
				LeftRadius->setLength(4.0f);
				LeftRadius->setRotation(Quaternion(Vec3f(0,0,1), osgdegree2rad(0)));
			endEditCP(LeftRadius, Bone::RotationFieldMask | Bone::LengthFieldMask);


	//Save current position as default position
	LeftRadius->setBindPosition();


/*================================================================================================*/
/*                                    LEFT HAND                                                   */

	LeftHand = Bone::create(); //create a bone called ExampleChildbone
			beginEditCP(LeftHand, Bone::RotationFieldMask | Bone::LengthFieldMask);//use the field masks
				LeftHand->setLength(1.0f);
				LeftHand->setRotation(Quaternion(Vec3f(0,0,1), osgdegree2rad(0)));
			endEditCP(LeftHand, Bone::RotationFieldMask | Bone::LengthFieldMask);

	//Save current position as default position
	LeftHand->setBindPosition();

/*================================================================================================*/
/*                                    LEFT FEMUR                                                  */

	LeftFemur = Bone::create(); //create a bone called ExampleChildbone
			beginEditCP(LeftFemur, Bone::RotationFieldMask | Bone::LengthFieldMask);//use the field masks
				LeftFemur->setLength(5.0f);
				LeftFemur->setRotation(Quaternion(Vec3f(0,1,0), osgdegree2rad(45)));
			endEditCP(LeftFemur, Bone::RotationFieldMask | Bone::LengthFieldMask);

	//Save current position as default position
	LeftFemur->setBindPosition();

/*================================================================================================*/
/*                                    LEFT TIBIA                                                  */

	LeftTibia = Bone::create(); //create a bone called ExampleChildbone
			beginEditCP(LeftTibia, Bone::RotationFieldMask | Bone::LengthFieldMask| Bone::TranslationFieldMask);//use the field masks
				LeftTibia->setLength(8.0f);
				LeftTibia->setRotation(Quaternion(Vec3f(0,0,1), osgdegree2rad(0)));
			endEditCP(LeftTibia, Bone::RotationFieldMask | Bone::LengthFieldMask| Bone::TranslationFieldMask);

	//Save current position as default position
	LeftTibia->setBindPosition();

/*================================================================================================*/
/*                                    LEFT FEET                                                   */

	LeftFeet = Bone::create(); //create a bone called ExampleChildbone
			beginEditCP(LeftFeet, Bone::RotationFieldMask | Bone::LengthFieldMask);//use the field masks
				LeftFeet->setLength(2.0f);
				LeftFeet->setRotation(Quaternion(Vec3f(0,1,1), osgdegree2rad(180)));
			endEditCP(LeftFeet, Bone::RotationFieldMask | Bone::LengthFieldMask);

	//Save current position as default position
	LeftFeet->setBindPosition();


/*================================================================================================*/
/*                                    RIGHT HUMERUS                                               */

	RightHumerus = Bone::create(); //create a bone called ExampleChildbone
			beginEditCP(RightHumerus, Bone::RotationFieldMask | Bone::LengthFieldMask| Bone::TranslationFieldMask);//use the field masks
				RightHumerus->setLength(4.0f);
				RightHumerus->setRotation(Quaternion(Vec3f(0,1,0), osgdegree2rad(-90)));
				RightHumerus->setTranslation(Vec3f(0,0,-10));
			endEditCP(RightHumerus, Bone::RotationFieldMask | Bone::LengthFieldMask| Bone::TranslationFieldMask);

	//Save current position as default position
	RightHumerus->setBindPosition();


/*================================================================================================*/
/*                                    RIGHT RADIUS                                                */

	RightRadius = Bone::create(); //create a bone called ExampleChildbone
			beginEditCP(RightRadius, Bone::RotationFieldMask | Bone::LengthFieldMask);//use the field masks
				RightRadius->setLength(4.0f);
				RightRadius->setRotation(Quaternion(Vec3f(0,0,1), osgdegree2rad(0)));
			endEditCP(RightRadius, Bone::RotationFieldMask | Bone::LengthFieldMask);

	//Save current position as default position
	RightRadius->setBindPosition();


/*================================================================================================*/
/*                                     RIGHT HAND                                                 */


	RightHand = Bone::create(); //create a bone called ExampleChildbone
			beginEditCP(RightHand, Bone::RotationFieldMask | Bone::LengthFieldMask);//use the field masks
				RightHand->setLength(1.0f);
				RightHand->setRotation(Quaternion(Vec3f(0,0,1), osgdegree2rad(0)));
				
			endEditCP(RightHand, Bone::RotationFieldMask | Bone::LengthFieldMask);

	//Save current position as default position
	RightHand->setBindPosition();

/*================================================================================================*/
/*                                     RIGHT FEMUR                                                */


	RightFemur = Bone::create(); //create a bone called ExampleChildbone
			beginEditCP(RightFemur, Bone::RotationFieldMask | Bone::LengthFieldMask);//use the field masks
				RightFemur->setLength(5.0f);
				RightFemur->setRotation(Quaternion(Vec3f(0,1,0), osgdegree2rad(-45)));
			endEditCP(RightFemur, Bone::RotationFieldMask | Bone::LengthFieldMask);

	//Save current position as default position
	RightFemur->setBindPosition();

/*================================================================================================*/
/*                                     RIGHT TIBIA                                                */


	RightTibia = Bone::create(); //create a bone called ExampleChildbone
			beginEditCP(RightTibia, Bone::RotationFieldMask | Bone::LengthFieldMask);//use the field masks
				RightTibia->setLength(8.0f);
				RightTibia->setRotation(Quaternion(Vec3f(0,1,0), osgdegree2rad(0)));
				
			endEditCP(RightTibia, Bone::RotationFieldMask | Bone::LengthFieldMask);

	//Save current position as default position
	RightTibia->setBindPosition();

/*================================================================================================*/
/*                                     RIGHT FEET                                                 */


	RightFeet = Bone::create(); //create a bone called ExampleChildbone
			beginEditCP(RightFeet, Bone::RotationFieldMask | Bone::LengthFieldMask);//use the field masks
				RightFeet->setLength(2.0f);
				RightFeet->setRotation(Quaternion(Vec3f(0,1,1), osgdegree2rad(180)));
			endEditCP(RightFeet, Bone::RotationFieldMask | Bone::LengthFieldMask);

	//Save current position as default position
	RightFeet->setBindPosition();



			Torso->addChild(LeftHumerus);
			Torso->addChild(RightHumerus);
			Torso->addChild(LeftFemur);
			Torso->addChild(RightFemur);

			LeftHumerus->addChild(LeftRadius);
			LeftRadius->addChild(LeftHand);
			RightHumerus->addChild(RightRadius);
			RightRadius->addChild(RightHand);

			LeftFemur->addChild(LeftTibia);
			LeftTibia->addChild(LeftFeet);
			RightFemur->addChild(RightTibia);
			RightTibia->addChild(RightFeet);

			//get the Children

			//BonePtr TheLeftFemur, TheRightFemur; 


			/*LeftHumerus  = Torso->getChild(0);
			RightHumerus = Torso->getChild(1);*/
			//LeftFemur    = Torso->getChild(0);
			//RightFemur   = Torso->getChild(1);
			/*LeftRadius   = LeftHumerus->getChild(0);
			LeftHand     = LeftRadius->getChild(0);
			RightRadius  = RightHumerus->getChild(0);
			RightHand    = RightRadius->getChild(0);
			LeftTibia    = LeftFemur->getChild(0);
			LeftFeet     = LeftTibia->getChild(0);
			RightTibia   = RightFemur->getChild(0);
			RightFeet    = RightTibia->getChild(0);*/



/*=================================================================================================*/

	//UInt32 SelectedChildDepth=4;
	//BonePtr TheSelectedBone = ExampleRootBone;
	//for(UInt32 i(0) ; i<SelectedChildDepth && TheSelectedBone->getNumChildren() >0 ; ++i )
	//{
	//	TheSelectedBone = TheSelectedBone->getChild(0);
	//	
	//}

	GeoPTypesPtr type = GeoPTypesUI8::create();        
    beginEditCP(type, GeoPTypesUI8::GeoPropDataFieldMask);
    {
        type->addValue(GL_QUADS);
    }
    endEditCP  (type, GeoPTypesUI8::GeoPropDataFieldMask);

	GeoPLengthsPtr lens = GeoPLengthsUI32::create();    
    beginEditCP(lens, GeoPLengthsUI32::GeoPropDataFieldMask);
    {
        lens->addValue(52);
    }
    endEditCP  (lens, GeoPLengthsUI32::GeoPropDataFieldMask);
	 GeoPositions3fPtr pnts = GeoPositions3f::create();
    beginEditCP(pnts, GeoPositions3f::GeoPropDataFieldMask);
    {
		// the points of the Quads
		//TORSO
        pnts->addValue(Pnt3f(-0.5,  15,  0));
        pnts->addValue(Pnt3f( 0.5,  15,  0));
        pnts->addValue(Pnt3f( 0.5,  0,  0));
        pnts->addValue(Pnt3f(-0.5,  0,  0));

		//LEFT FEMUR
        pnts->addValue(Pnt3f(-0.3535,  0.3535, 0));
		pnts->addValue(Pnt3f(0.3535, -0.3535, 0));
		pnts->addValue(Pnt3f(-3.182,  -3.889, 0));
        pnts->addValue(Pnt3f(-3.889,  -3.182, 0));

		//RIGHT FEMUR
		pnts->addValue(Pnt3f(0.3535,  0.3535, 0));
        pnts->addValue(Pnt3f(3.889,  -3.182, 0));
        pnts->addValue(Pnt3f(3.182,  -3.889, 0));
        pnts->addValue(Pnt3f(-0.3535, -0.3535, 0));

		//LEFT HUMERUS
		pnts->addValue(Pnt3f(-4,  10.5, 0));
        pnts->addValue(Pnt3f(0,  10.5, 0));
        pnts->addValue(Pnt3f(0,  9.5, 0));
        pnts->addValue(Pnt3f(-4, 9.5, 0));

		//RIGHT HUMERUS
		pnts->addValue(Pnt3f(0,  10.5, 0));
        pnts->addValue(Pnt3f(4,  10.5, 0));
        pnts->addValue(Pnt3f(4,  9.5, 0));
        pnts->addValue(Pnt3f(0, 9.5, 0));

		//LEFT RADIUS
		pnts->addValue(Pnt3f(-8,  10.5, 0));
        pnts->addValue(Pnt3f(-4,  10.5, 0));
        pnts->addValue(Pnt3f(-4,  9.5, 0));
        pnts->addValue(Pnt3f(-8, 9.5, 0));

		//RIGHT RADIUS
		pnts->addValue(Pnt3f(4,  10.5, 0));
        pnts->addValue(Pnt3f(8,  10.5, 0));
        pnts->addValue(Pnt3f(8,  9.5, 0));
        pnts->addValue(Pnt3f(4, 9.5, 0));

		//LEFT HAND
		pnts->addValue(Pnt3f(-9,  10.5, 0));
        pnts->addValue(Pnt3f(-8,  10.5, 0));
        pnts->addValue(Pnt3f(-8,  9.5, 0));
        pnts->addValue(Pnt3f(-9, 9.5, 0));

		//RIGHT HAND
		pnts->addValue(Pnt3f(8,  10.5, 0));
        pnts->addValue(Pnt3f(9,  10.5, 0));
        pnts->addValue(Pnt3f(9,  9.5, 0));
        pnts->addValue(Pnt3f(8, 9.5, 0));

		//LEFT TIBIA
		pnts->addValue(Pnt3f(-3.8890, -3.1820, 0));
		pnts->addValue(Pnt3f(-3.1820, -3.8890, 0));
		pnts->addValue(Pnt3f(-8.8389, -9.5459, 0));
        pnts->addValue(Pnt3f(-9.5459, -8.8389, 0));

		//RIGHT TIBIA
		pnts->addValue(Pnt3f(3.8890, -3.1820, 0));
        pnts->addValue(Pnt3f(9.5459, -8.8389, 0));
        pnts->addValue(Pnt3f(8.8389, -9.5459, 0));
        pnts->addValue(Pnt3f(3.1820, -3.8890, 0));

		//LEFT FOOT
		pnts->addValue(Pnt3f(-9.5459, -8.8389, 0));
		pnts->addValue(Pnt3f(-8.8389, -9.5459, 0));
		pnts->addValue(Pnt3f(-8.8389, -9.5459, 2));
        pnts->addValue(Pnt3f(-9.5459, -8.8389, 2));

		//RIGHT FOOT
		pnts->addValue(Pnt3f(9.5459, -8.8389, 0));
        pnts->addValue(Pnt3f(9.5459, -8.8389, 2));
        pnts->addValue(Pnt3f(8.8389, -9.5459, 2));
        pnts->addValue(Pnt3f(8.8389, -9.5459, 0));
    }
    endEditCP  (pnts, GeoPositions3f::GeoPropDataFieldMask);
    
    //Normals
	 GeoNormals3fPtr norms = GeoNormals3f::create();
	 geo=Geometry::create();
    beginEditCP(norms, GeoNormals3f::GeoPropDataFieldMask);
		//TORSO
        norms->addValue(Vec3f( 0.0,0.0,1.0));
        norms->addValue(Vec3f( 0.0,0.0,1.0));
        norms->addValue(Vec3f( 0.0,0.0,1.0));
        norms->addValue(Vec3f( 0.0,0.0,1.0));

		//LEFT FEMUR
        norms->addValue(Vec3f( 0.0,0.0,1.0));
        norms->addValue(Vec3f( 0.0,0.0,1.0));
        norms->addValue(Vec3f( 0.0,0.0,1.0));
        norms->addValue(Vec3f( 0.0,0.0,1.0));

		//RIGHT FEMUR
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		//LEFT HUMERUS
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		//RIGHT HUMERUS
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		//LEFT RADIUS
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		//RIGHT RADIUS
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		//LEFT HAND
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		//RIGHT HAND
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		//LEFT TIBIA
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		//RIGHT TIBIA
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));
		norms->addValue(Vec3f( 0.0,0.0,1.0));

		//LEFT FOOT
		norms->addValue(Vec3f( 0.7071,-0.7071,0.0));
		norms->addValue(Vec3f( 0.7071,-0.7071,0.0));
		norms->addValue(Vec3f( 0.7071,-0.7071,0.0));
		norms->addValue(Vec3f( 0.7071,-0.7071,0.0));

		//RIGHT FOOT
		norms->addValue(Vec3f( -0.7071,0.7071,0.0));
		norms->addValue(Vec3f( -0.7071,0.7071,0.0));
		norms->addValue(Vec3f( -0.7071,0.7071,0.0));
		norms->addValue(Vec3f( -0.7071,0.7071,0.0));

    endEditCP(norms, GeoNormals3f::GeoPropDataFieldMask);

	 GeoColors3fPtr colors = GeoColors3f::create();
    beginEditCP(colors, GeoColors3f::GeoPropDataFieldMask);
		//TORSO
        colors->addValue(Color3f( 1.0,0.0,0.0));
        colors->addValue(Color3f( 1.0,0.0,0.0));
        colors->addValue(Color3f( 1.0,0.0,0.0));
        colors->addValue(Color3f( 1.0,0.0,0.0));

		//LEFT FEMUR
        colors->addValue(Color3f( 0.0,1.0,0.0));
        colors->addValue(Color3f( 0.0,1.0,0.0));
        colors->addValue(Color3f( 0.0,1.0,0.0));
        colors->addValue(Color3f( 0.0,1.0,0.0));

		//RIGHT FEMUR
		colors->addValue(Color3f( 0.0,0.0,1.0));
		colors->addValue(Color3f( 0.0,0.0,1.0));
		colors->addValue(Color3f( 0.0,0.0,1.0));
		colors->addValue(Color3f( 0.0,0.0,1.0));

		//LEFT HUMERUS
		colors->addValue(Color3f( 0.0,1.0,1.0));
		colors->addValue(Color3f( 0.0,1.0,1.0));
		colors->addValue(Color3f( 0.0,1.0,1.0));
		colors->addValue(Color3f( 0.0,1.0,1.0));

		//RIGHT HUMERUS
		colors->addValue(Color3f( 1.0,1.0,0.0));
		colors->addValue(Color3f( 1.0,1.0,0.0));
		colors->addValue(Color3f( 1.0,1.0,0.0));
		colors->addValue(Color3f( 1.0,1.0,0.0));

		//LEFT RADIUS
		colors->addValue(Color3f( 1.0,0.5,0.0));
		colors->addValue(Color3f( 1.0,0.5,0.0));
		colors->addValue(Color3f( 1.0,0.5,0.0));
		colors->addValue(Color3f( 1.0,0.5,0.0));

		//RIGHT RADIUS
		colors->addValue(Color3f( 1.0,0.0,1.0));
		colors->addValue(Color3f( 1.0,0.0,1.0));
		colors->addValue(Color3f( 1.0,0.0,1.0));
		colors->addValue(Color3f( 1.0,0.0,1.0));

		//LEFT HAND
		colors->addValue(Color3f( 5.0,0.0,1.0));
		colors->addValue(Color3f( 5.0,0.0,1.0));
		colors->addValue(Color3f( 5.0,0.0,1.0));
		colors->addValue(Color3f( 5.0,0.0,1.0));

		//RIGHT HAND
		colors->addValue(Color3f( 0.0,0.5,1.0));
		colors->addValue(Color3f( 0.0,0.5,1.0));
		colors->addValue(Color3f( 0.0,0.5,1.0));
		colors->addValue(Color3f( 0.0,0.5,1.0));

		//LEFT TIBIA
		colors->addValue(Color3f( 1.0,0.0,0.5));
		colors->addValue(Color3f( 1.0,0.0,0.5));
		colors->addValue(Color3f( 1.0,0.0,0.5));
		colors->addValue(Color3f( 1.0,0.0,0.5));

		//RIGHT TIBIA
		colors->addValue(Color3f( 0.0,1.0,0.5));
		colors->addValue(Color3f( 0.0,1.0,0.5));
		colors->addValue(Color3f( 0.0,1.0,0.5));
		colors->addValue(Color3f( 0.0,1.0,0.5));

		//LEFT FOOT
		colors->addValue(Color3f( 0.25,0.25,1.0));
		colors->addValue(Color3f( 0.25,0.25,1.0));
		colors->addValue(Color3f( 0.25,0.25,1.0));
		colors->addValue(Color3f( 0.25,0.25,1.0));

		//RIGHT FOOT
		colors->addValue(Color3f( 1.0,0.25,0.25));
		colors->addValue(Color3f( 1.0,0.25,0.25));
		colors->addValue(Color3f( 1.0,0.25,0.25));
		colors->addValue(Color3f( 1.0,0.25,0.25));
		
    endEditCP(colors, GeoColors3f::GeoPropDataFieldMask);


    beginEditCP(geo, Geometry::TypesFieldMask     |
                     Geometry::LengthsFieldMask   |
                     Geometry::PositionsFieldMask |
                     Geometry::NormalsFieldMask |
                     Geometry::MaterialFieldMask |
					 Geometry::ColorsFieldMask);
    {
        geo->setTypes    (type);
        geo->setLengths  (lens);
        geo->setPositions(pnts);
        geo->setNormals(norms);
        geo->setColors(colors);

        // assign a material to the geometry to make it visible. The details
        // of materials are defined later.
        geo->setMaterial(getDefaultMaterial());   
    }
    endEditCP  (geo, Geometry::TypesFieldMask     |
                     Geometry::LengthsFieldMask   |
                     Geometry::PositionsFieldMask |
                     Geometry::NormalsFieldMask |
                     Geometry::MaterialFieldMask |
					 Geometry::ColorsFieldMask  );
    
    // put the geometry core into a node
    NodePtr n = Node::create();
    beginEditCP(n, Node::CoreFieldMask);
    {
        n->setCore(geo);
    }
    endEditCP  (n, Node::CoreFieldMask);
   


    //Skeleton
    SkeletonPtr ExampleSkeleton = Skeleton::create();
	beginEditCP(ExampleSkeleton, Skeleton::RootBonesFieldMask);
		ExampleSkeleton->getRootBones().push_back(Torso);
	endEditCP(ExampleSkeleton, Skeleton::RootBonesFieldMask);

    //SkeletonDrawer
    SkeletonDrawablePtr ExampleSkeletonDrawable = osg::SkeletonDrawable::create();
    beginEditCP(ExampleSkeletonDrawable, SkeletonDrawable::SkeletonFieldMask | SkeletonDrawable::MaterialFieldMask);
		ExampleSkeletonDrawable->setSkeleton(ExampleSkeleton);
		ExampleSkeletonDrawable->setMaterial(ExampleMaterial);
    endEditCP(ExampleSkeletonDrawable, SkeletonDrawable::SkeletonFieldMask | SkeletonDrawable::MaterialFieldMask);
	
	//Skeleton Node
    
	NodePtr SkeletonNode = osg::Node::create();
    beginEditCP(SkeletonNode, Node::CoreFieldMask);
        SkeletonNode->setCore(ExampleSkeletonDrawable);
    endEditCP(SkeletonNode, Node::CoreFieldMask);




	// Skeleton Blended Geometry

	SkeletonBlendedGeometryPtr TheNewSkeletonGeometry = SkeletonBlendedGeometry::create();
	beginEditCP(TheNewSkeletonGeometry);
		TheNewSkeletonGeometry->addSkeleton(ExampleSkeleton);
		TheNewSkeletonGeometry->setBaseGeometry(geo);
		TheNewSkeletonGeometry->setBlendMode(SkeletonBlendedGeometry::BLEND_RIGID);
		
		//TORSO QUAD
		TheNewSkeletonGeometry->addBoneBlending(0,Torso,1.0f,false);
		TheNewSkeletonGeometry->addBoneBlending(1,Torso,1.0f,false);
		TheNewSkeletonGeometry->addBoneBlending(2,Torso,1.0f,true);
		TheNewSkeletonGeometry->addBoneBlending(3,Torso,1.0f,true);

		
		//LEFT FEMUR QUAD
		TheNewSkeletonGeometry->addBoneBlending(4,RightFemur,1.0f,false);
		TheNewSkeletonGeometry->addBoneBlending(5,RightFemur,1.0f,false);
		TheNewSkeletonGeometry->addBoneBlending(6,RightFemur,1.0f,true);
		TheNewSkeletonGeometry->addBoneBlending(7,RightFemur,1.0f,true);
		
		//TheNewSkeletonGeometry->addBoneBlending(4,LeftFemur,0.5f,false);

		
		//RIGHT FEMUR QUAD
		TheNewSkeletonGeometry->addBoneBlending(8,LeftFemur,1.0f,false);
		TheNewSkeletonGeometry->addBoneBlending(9,LeftFemur,1.0f,true);
		TheNewSkeletonGeometry->addBoneBlending(10,LeftFemur,1.0f,true);
		TheNewSkeletonGeometry->addBoneBlending(11,LeftFemur,1.0f,false);

		//TheNewSkeletonGeometry->addBoneBlending(8,RightFemur,0.5f,false);

		
		//LEFT HUMERUS QUAD
		TheNewSkeletonGeometry->addBoneBlending(12,RightHumerus,1.0f,true);
		TheNewSkeletonGeometry->addBoneBlending(13,RightHumerus,1.0f,false);
		TheNewSkeletonGeometry->addBoneBlending(14,RightHumerus,1.0f,false);
		TheNewSkeletonGeometry->addBoneBlending(15,RightHumerus,1.0f,true);

		//TheNewSkeletonGeometry->addBoneBlending(12,RightRadius,0.5f,false);
		//TheNewSkeletonGeometry->addBoneBlending(15,RightRadius,0.5f,false);


		//RIGHT HUMERUS QUAD
		TheNewSkeletonGeometry->addBoneBlending(16,LeftHumerus,1.0f,false);
		TheNewSkeletonGeometry->addBoneBlending(17,LeftHumerus,1.0f,true);
		TheNewSkeletonGeometry->addBoneBlending(18,LeftHumerus,1.0f,true);
		TheNewSkeletonGeometry->addBoneBlending(19,LeftHumerus,1.0f,false);


		//LEFT RADIUS QUAD
		TheNewSkeletonGeometry->addBoneBlending(20,RightRadius,1.0f,true);
		TheNewSkeletonGeometry->addBoneBlending(21,RightRadius,1.0f,false);
		TheNewSkeletonGeometry->addBoneBlending(22,RightRadius,1.0f,false);
		TheNewSkeletonGeometry->addBoneBlending(23,RightRadius,1.0f,true);

		//TheNewSkeletonGeometry->addBoneBlending(21,RightHumerus,1.0f,true);
		//TheNewSkeletonGeometry->addBoneBlending(22,RightHumerus,1.0f,true);

		//TheNewSkeletonGeometry->addBoneBlending(20,RightHand,1.0f,false);
		//TheNewSkeletonGeometry->addBoneBlending(23,RightHand,1.0f,false);


		//RIGHT RADIUS QUAD
		TheNewSkeletonGeometry->addBoneBlending(24,LeftRadius,1.0f,false);
		TheNewSkeletonGeometry->addBoneBlending(25,LeftRadius,1.0f,true);
		TheNewSkeletonGeometry->addBoneBlending(26,LeftRadius,1.0f,true);
		TheNewSkeletonGeometry->addBoneBlending(27,LeftRadius,1.0f,false);


		//LEFT HAND QUAD
		TheNewSkeletonGeometry->addBoneBlending(28,RightHand,1.0f,true);
		TheNewSkeletonGeometry->addBoneBlending(29,RightHand,1.0f,false);
		TheNewSkeletonGeometry->addBoneBlending(30,RightHand,1.0f,false);
		TheNewSkeletonGeometry->addBoneBlending(31,RightHand,1.0f,true);

		//TheNewSkeletonGeometry->addBoneBlending(29,RightRadius,0.5f,true);
		//TheNewSkeletonGeometry->addBoneBlending(30,RightRadius,0.5f,true);


		//RIGHT HAND QUAD
		TheNewSkeletonGeometry->addBoneBlending(32,LeftHand,1.0f,false);
		TheNewSkeletonGeometry->addBoneBlending(33,LeftHand,1.0f,true);
		TheNewSkeletonGeometry->addBoneBlending(34,LeftHand,1.0f,true);
		TheNewSkeletonGeometry->addBoneBlending(35,LeftHand,1.0f,false);


		//LEFT TIBIA QUAD
		TheNewSkeletonGeometry->addBoneBlending(36,RightTibia,1.0f,true);
		TheNewSkeletonGeometry->addBoneBlending(37,RightTibia,1.0f,false);
		TheNewSkeletonGeometry->addBoneBlending(38,RightTibia,1.0f,false);
		TheNewSkeletonGeometry->addBoneBlending(39,RightTibia,1.0f,true);


		//RIGHT TIBIA QUAD
		TheNewSkeletonGeometry->addBoneBlending(40,LeftTibia,1.0f,false);
		TheNewSkeletonGeometry->addBoneBlending(41,LeftTibia,1.0f,true);
		TheNewSkeletonGeometry->addBoneBlending(42,LeftTibia,1.0f,true);
		TheNewSkeletonGeometry->addBoneBlending(43,LeftTibia,1.0f,false);


		//LEFT FOOT QUAD
		TheNewSkeletonGeometry->addBoneBlending(44,RightFeet,1.0f,true);
		TheNewSkeletonGeometry->addBoneBlending(45,RightFeet,1.0f,false);
		TheNewSkeletonGeometry->addBoneBlending(46,RightFeet,1.0f,false);
		TheNewSkeletonGeometry->addBoneBlending(47,RightFeet,1.0f,true);


		//RIGHT FOOT QUAD
		TheNewSkeletonGeometry->addBoneBlending(48,LeftFeet,1.0f,false);
		TheNewSkeletonGeometry->addBoneBlending(49,LeftFeet,1.0f,true);
		TheNewSkeletonGeometry->addBoneBlending(50,LeftFeet,1.0f,true);
		TheNewSkeletonGeometry->addBoneBlending(51,LeftFeet,1.0f,false);
		
		
    endEditCP(TheNewSkeletonGeometry);
	
	NodePtr MeshNode = osg::Node::create();
    beginEditCP(MeshNode, Node::CoreFieldMask);
        MeshNode->setCore(TheNewSkeletonGeometry);
    endEditCP(MeshNode, Node::CoreFieldMask);

	//Create unbound geometry Node
	NodePtr UnboundGeometry = Node::create();
	beginEditCP(UnboundGeometry, Node::CoreFieldMask);
		UnboundGeometry->setCore(geo);
	endEditCP(UnboundGeometry, Node::CoreFieldMask);


	
   //Animation Advancer
   TheAnimationAdvancer = osg::ElapsedTimeAnimationAdvancer::create();
   osg::beginEditCP(TheAnimationAdvancer);
   osg::ElapsedTimeAnimationAdvancer::Ptr::dcast(TheAnimationAdvancer)->setStartTime( 0.0 );
   osg::beginEditCP(TheAnimationAdvancer);


    
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
        scene->addChild(SkeletonNode);
        scene->addChild(/*UnboundGeometry*/MeshNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

    mgr->setRoot(scene);

	//Setup the Animation
	setupAnimation(LeftHumerus,LeftRadius,LeftHand,LeftFemur,RightHumerus,RightRadius,RightHand,RightFemur,Torso, ExampleSkeleton);


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


void setupAnimation(BonePtr TheLeftHumerus,BonePtr TheLeftRadius,BonePtr TheLeftHand,BonePtr TheLeftFemur,BonePtr TheRightHumerus,BonePtr TheRightRadius,BonePtr TheRightHand,BonePtr TheRightFemur,BonePtr TheTorso, SkeletonPtr TheSkeleton)
{
 
/* ================================ ANIMATION OF THE BONES ==============================================*/
/*================================================================================================*/
/*                                       TORSO                                                    */
 //Length
   osg::KeyframeNumbersSequencePtr TorsoLenghtFrame = osg::KeyframeNumbersSequenceReal32::create();
   
   TorsoLenghtFrame->addKeyframe(15.0f,0.0f);
   TorsoLenghtFrame->addKeyframe(10.0f,3.0f);
   TorsoLenghtFrame->addKeyframe(15.0f,4.0f);
   TorsoLenghtFrame->addKeyframe(10.0f,5.0f);
   TorsoLenghtFrame->addKeyframe(15.0f,6.0f);

  //Length Animator
   osg::KeyframeAnimatorPtr TorsoLengthAnimator = osg::KeyframeAnimator::create();
   osg::beginEditCP(TorsoLengthAnimator);
      osg::KeyframeAnimatorPtr::dcast(TorsoLengthAnimator)->setKeyframeSequence(TorsoLenghtFrame);
   osg::endEditCP(TorsoLengthAnimator);

/*================================================================================================*/
/*                                    LEFT HUMERUS                                                */
 //Quaternion
   osg::KeyframeRotationsSequencePtr LeftHumerusKeyFrame = osg::KeyframeRotationsSequenceQuat::create();
   
   LeftHumerusKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(130.0)), 0.0f);
   LeftHumerusKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(50.5)) , 2.0f);
   LeftHumerusKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(20.0)) , 4.0f);
   LeftHumerusKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(50.5)) , 5.0f);
   LeftHumerusKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(130.0)), 6.0f);

    //Rotation Animator
    osg::KeyframeAnimatorPtr  LeftHumerusAnimator = osg::KeyframeAnimator::create();
    osg::beginEditCP(LeftHumerusAnimator);
      osg::KeyframeAnimatorPtr::dcast(LeftHumerusAnimator)->setKeyframeSequence(LeftHumerusKeyFrame);
    osg::endEditCP(LeftHumerusAnimator);


	//Translation
	osg::KeyframeVectorsSequence3fPtr LeftHumerusTranslationFrame = osg::KeyframeVectorsSequence3f::create();

	LeftHumerusTranslationFrame->addKeyframe(osg::Vec3f(0.0f,0.0f,0.0f), 0.0f);
	LeftHumerusTranslationFrame->addKeyframe(osg::Vec3f(0.0f,0.0f,-3.0), 3.0f);
	LeftHumerusTranslationFrame->addKeyframe(osg::Vec3f(0.0f,0.0f,0.0f), 6.0f);

	osg::KeyframeAnimatorPtr LeftHumerusTranslationAnimator = osg::KeyframeAnimator::create();
	osg::beginEditCP(LeftHumerusTranslationAnimator);
		osg::KeyframeAnimatorPtr::dcast(LeftHumerusTranslationAnimator)->setKeyframeSequence(LeftHumerusTranslationFrame);
	osg::endEditCP(LeftHumerusTranslationAnimator);



 


/*================================================================================================*/
/*                                    LEFT RADIUS                                                 */

//Quaternion
   osg::KeyframeRotationsSequencePtr LeftRadiusKeyFrame = osg::KeyframeRotationsSequenceQuat::create();
   
   LeftRadiusKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(50.0)) , 0.0f);
   LeftRadiusKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(20.0)) , 2.0f);
   LeftRadiusKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(0.0))  , 4.0f);
   LeftRadiusKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(0.0))  , 5.0f);
   LeftRadiusKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(0.0))  , 6.0f);


   //Rotation Animator
   osg::KeyframeAnimatorPtr LeftRadiusAnimator = osg::KeyframeAnimator::create();
   osg::beginEditCP(LeftRadiusAnimator);
      osg::KeyframeAnimatorPtr::dcast(LeftRadiusAnimator)->setKeyframeSequence(LeftRadiusKeyFrame);
   osg::endEditCP(LeftRadiusAnimator);


	


/*================================================================================================*/
/*                                    LEFT HAND                                                   */

//Quaternion
   osg::KeyframeRotationsSequencePtr  LeftHandKeyFrame = osg::KeyframeRotationsSequenceQuat::create();
   
   LeftHandKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(70.0)), 0.0f);
   LeftHandKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(0.0)) , 2.0f);
   LeftHandKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(0.0)) , 4.0f);
   LeftHandKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(0.0)) , 5.0f);
   LeftHandKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(0.0)) , 6.0f);


   //Rotation Animator
   osg::KeyframeAnimatorPtr  LeftHandAnimator= osg::KeyframeAnimator::create();
   osg::beginEditCP(LeftHandAnimator);
      osg::KeyframeAnimatorPtr::dcast(LeftHandAnimator)->setKeyframeSequence(LeftHandKeyFrame);
   osg::endEditCP(LeftHandAnimator);



/*================================================================================================*/
/*                                    LEFT FEMUR                                                  */

 //Quaternion
   osg::KeyframeRotationsSequencePtr  LeftFemurKeyFrame = osg::KeyframeRotationsSequenceQuat::create();
   
   LeftFemurKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(50.0)), 0.0f);
   LeftFemurKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(20.0)), 2.0f);
   LeftFemurKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(5.0)) , 4.0f);
   LeftFemurKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(20.0)), 5.0f);
   LeftFemurKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(50.0)), 6.0f);


   //Rotation Animator
   osg::KeyframeAnimatorPtr  LeftFemurAnimator = osg::KeyframeAnimator::create();
   osg::beginEditCP(LeftFemurAnimator);
      osg::KeyframeAnimatorPtr::dcast(LeftFemurAnimator)->setKeyframeSequence(LeftFemurKeyFrame);
   osg::endEditCP(LeftFemurAnimator);



/*================================================================================================*/
/*                                    LEFT TIBIA                                                  */

	

/*================================================================================================*/
/*                                    LEFT FEET                                                   */

	


/*================================================================================================*/
/*                                    RIGHT HUMERUS                                               */

 //Quaternion
   osg::KeyframeRotationsSequencePtr  RightHumerusKeyFrame = osg::KeyframeRotationsSequenceQuat::create();
   
   RightHumerusKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(-130.0)), 0.0f);
   RightHumerusKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(-50.5)) , 2.0f);
   RightHumerusKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(-20.0)) , 4.0f);
   RightHumerusKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(-50.5)) , 5.0f);
   RightHumerusKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(-130.0)), 6.0f);


   //Rotation Animator
   osg::KeyframeAnimatorPtr RightHumerusAnimator = osg::KeyframeAnimator::create();
   osg::beginEditCP(RightHumerusAnimator);
      osg::KeyframeAnimatorPtr::dcast(RightHumerusAnimator)->setKeyframeSequence(RightHumerusKeyFrame);
   osg::endEditCP(RightHumerusAnimator);

    //Translation
	osg::KeyframeVectorsSequence3fPtr RightHumerusTranslationFrame = osg::KeyframeVectorsSequence3f::create();

	RightHumerusTranslationFrame->addKeyframe(osg::Vec3f(0.0f,0.0f,0.0f), 0.0f);
	RightHumerusTranslationFrame->addKeyframe(osg::Vec3f(0.0f,0.0f,-3.0), 3.0f);
	RightHumerusTranslationFrame->addKeyframe(osg::Vec3f(0.0f,0.0f,0.0f), 6.0f);

	osg::KeyframeAnimatorPtr RightHumerusTranslationAnimator = osg::KeyframeAnimator::create();
	osg::beginEditCP(RightHumerusTranslationAnimator);
		osg::KeyframeAnimatorPtr::dcast(RightHumerusTranslationAnimator)->setKeyframeSequence(RightHumerusTranslationFrame);
	osg::endEditCP(RightHumerusTranslationAnimator);




/*================================================================================================*/
/*                                    RIGHT RADIUS                                                */

//Quaternion
   osg::KeyframeRotationsSequencePtr  RightRadiusKeyFrame = osg::KeyframeRotationsSequenceQuat::create();
   
   RightRadiusKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(-50.0)), 0.0f);
   RightRadiusKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(-20.0)), 2.0f);
   RightRadiusKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(0.0))  , 4.0f);
   RightRadiusKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(0.0))  , 5.0f);
   RightRadiusKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(0.0))  , 6.0f);


   //Rotation Animator
   osg::KeyframeAnimatorPtr  RightRadiusAnimator= osg::KeyframeAnimator::create();
   osg::beginEditCP(RightRadiusAnimator);
      osg::KeyframeAnimatorPtr::dcast(RightRadiusAnimator)->setKeyframeSequence(RightRadiusKeyFrame);
   osg::endEditCP(RightRadiusAnimator);




/*================================================================================================*/
/*                                     RIGHT HAND                                                 */

 //Quaternion
   osg::KeyframeRotationsSequencePtr RightHandKeyFrame = osg::KeyframeRotationsSequenceQuat::create();
   
   RightHandKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(-70.0)), 0.0f);
   RightHandKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(0.0))  , 2.0f);
   RightHandKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(0.0))  , 4.0f);
   RightHandKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(0.0))  , 5.0f);
   RightHandKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(0.0))  , 6.0f);


   //Rotation Animator
   osg::KeyframeAnimatorPtr RightHandAnimator = osg::KeyframeAnimator::create();
   osg::beginEditCP(RightHandAnimator);
      osg::KeyframeAnimatorPtr::dcast(RightHandAnimator)->setKeyframeSequence(RightHandKeyFrame);
   osg::endEditCP(RightHandAnimator);




/*================================================================================================*/
/*                                     RIGHT FEMUR                                                */

 //Quaternion
   osg::KeyframeRotationsSequencePtr RightFemurKeyFrame = osg::KeyframeRotationsSequenceQuat::create();
   
   RightFemurKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(-50.0)), 0.0f);
   RightFemurKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(-20.0)), 2.0f);
   RightFemurKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(-5.0)) , 4.0f);
   RightFemurKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(-20.0)), 5.0f);
   RightFemurKeyFrame->addKeyframe(osg::Quaternion(osg::Vec3f(0.0,1.0,0.0),deg2rad(-50.0)), 6.0f);


   //Rotation Animator
   osg::KeyframeAnimatorPtr RightFemurAnimator = osg::KeyframeAnimator::create();
   osg::beginEditCP(RightFemurAnimator);
      osg::KeyframeAnimatorPtr::dcast(RightFemurAnimator)->setKeyframeSequence(RightFemurKeyFrame);
   osg::endEditCP(RightFemurAnimator);



	

///*================================================================================================*/
///*                                     RIGHT TIBIA                                                */
//
//
//	
//
///*================================================================================================*/
///*                                     RIGHT FEET                                                 */
//

   
//  Skeleton Animation
   TheSkeletonAnimation = osg::SkeletonAnimation::create();
   osg::SkeletonAnimationPtr::dcast(TheSkeletonAnimation)->addRotationAnimator(LeftHumerusAnimator, TheLeftHumerus);
   osg::SkeletonAnimationPtr::dcast(TheSkeletonAnimation)->addRotationAnimator(LeftRadiusAnimator,  TheLeftRadius);
   osg::SkeletonAnimationPtr::dcast(TheSkeletonAnimation)->addRotationAnimator(LeftHandAnimator,    TheLeftHand);
   osg::SkeletonAnimationPtr::dcast(TheSkeletonAnimation)->addRotationAnimator(LeftFemurAnimator,   TheLeftFemur);
   osg::SkeletonAnimationPtr::dcast(TheSkeletonAnimation)->addRotationAnimator(RightHumerusAnimator,TheRightHumerus );
   osg::SkeletonAnimationPtr::dcast(TheSkeletonAnimation)->addRotationAnimator(RightRadiusAnimator, TheRightRadius);
   osg::SkeletonAnimationPtr::dcast(TheSkeletonAnimation)->addRotationAnimator(RightHandAnimator,   TheRightHand);
   osg::SkeletonAnimationPtr::dcast(TheSkeletonAnimation)->addRotationAnimator(RightFemurAnimator,  TheRightFemur);
   osg::SkeletonAnimationPtr::dcast(TheSkeletonAnimation)->addLengthAnimator  (TorsoLengthAnimator, TheTorso);
   osg::SkeletonAnimationPtr::dcast(TheSkeletonAnimation)->addTranslationAnimator(LeftHumerusTranslationAnimator,   TheLeftHumerus);
   osg::SkeletonAnimationPtr::dcast(TheSkeletonAnimation)->addTranslationAnimator(RightHumerusTranslationAnimator,   TheRightHumerus);


}