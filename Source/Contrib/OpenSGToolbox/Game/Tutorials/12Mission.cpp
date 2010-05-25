/*************************************************
Welcome to the 12 Mission tutorial. This tutorial
is a mini game created to demonstrate the function
of the mission system.
*************************************************/


// General OpenSG configuration, needed everywhere
#include <OpenSG/OSGConfig.h>

// Methods to create simple geometry: boxes, spheres, tori etc.
#include <OpenSG/OSGSimpleGeometry.h>

// A little helper to simplify scene management and interaction
#include <OpenSG/OSGSimpleSceneManager.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGDirectionalLight.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGTransform.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGSolidBackground.h>
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/Toolbox/OSGCameraUtils.h>


// The general scene file loading handler
#include <OpenSG/OSGSceneFileHandler.h>

// Input
#include <OpenSG/Input/OSGWindowUtils.h>


#include <OpenSG/Game/OSGRubberBandCamera.h>


// UserInterface Headers
#include <OpenSG/UserInterface/OSGUIForeground.h>
#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/UserInterface/OSGUIDrawingSurface.h>
#include <OpenSG/UserInterface/OSGGraphics2D.h>
#include <OpenSG/UserInterface/OSGLookAndFeelManager.h>

// Button Headers

#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGToggleButton.h>
#include <OpenSG/UserInterface/OSGUIFont.h>
#include <OpenSG/UserInterface/OSGColorLayer.h>
#include <OpenSG/UserInterface/OSGBorderLayout.h>
#include <OpenSG/UserInterface/OSGBorderLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGPolygonUIDrawObject.h>
#include <OpenSG/UserInterface/OSGUIDrawObjectCanvas.h>
#include <OpenSG/UserInterface/OSGImageComponent.h>

// MiniMap Headers
#include <OpenSG/Game/OSGLayeredImageMiniMap.h>
#include <OpenSG/Game/OSGMiniMapIndicator.h>
#include <OpenSG/Game/OSGMiniMapMatrixTransformation.h>
#include <OpenSG/Game/OSGDefaultMiniMapIndicatorComponentGenerator.h>


// MiniMap Overlay Headers
#include <OpenSG/Game/OSGDirectionalIndicatorMiniMapOverlay.h>
#include <OpenSG/Game/OSGDefaultDirectionalIndicatorComponentGenerator.h>

// Mission Headers
#include <OpenSG/Game/OSGMission.h>
#include <OpenSG/Game/OSGDefaultMission.h>
#include <OpenSG/Game/OSGDefaultMissionTreeComponentGenerator.h>
#include <OpenSG/Game/OSGGenericMissionTreeModel.h>

#include <OpenSG/Game/OSGDefaultMissionTreeComponentGenerator.h>

#include <OpenSG/Toolbox/OSGStringToUInt32MapType.h>

#include <OpenSG/UserInterface/OSGTree.h>


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

WindowEventProducerPtr TutorialWindowEventProducer;

/*************************************************
Instead of using the built-in scene manager we need
to over ride that to fit our needs. Here is the 
necessary code to do so.
*************************************************/
class SceneManager
{
protected:
	WindowPtr 	_win;
	NodePtr 	_root;
	NodePtr 	_internalRoot;
	DirectionalLightPtr 	_headlight;
	RenderAction * 	_action;
	RenderAction * 	_ownAction;
	TransformPtr 	_cart;
	CameraPtr 	_camera;
public:
	SceneManager() : 
		_win(NullFC),
		_root(NullFC),
		_internalRoot(NullFC),
		_headlight(NullFC),
		_action(NULL),
		_ownAction(NULL),
		_cart(NullFC),
		_camera(NullFC)
	{
	}

	virtual void redraw (void)
	{
		if (_internalRoot == NullFC)
		{
			initialize();
			showAll();
		}

		_win->render(_action);

	}

	virtual void resize(UInt16 width, UInt16 height)
	{
		_win->resize(width, height);
	}

	virtual void  setRoot          ( NodePtr root )
	{
		if(_internalRoot == NullFC)
		{
			initialize();
		}

		if(_root != root)
		{
			if(_root != NullFC)
			{
				beginEditCP(_internalRoot, Node::ChildrenFieldMask);
				_internalRoot->subChild(_root);
				endEditCP(_internalRoot, Node::ChildrenFieldMask);
			}

			_root = root;
			if(_root != NullFC)
			{
				beginEditCP(_internalRoot, Node::ChildrenFieldMask);
				_internalRoot->addChild(_root);
				endEditCP(_internalRoot, Node::ChildrenFieldMask);
			}
		}
	}

	WindowPtr getWindow( void )
	{
		return _win;
	}

	CameraPtr getCamera(void)
	{
		return _camera;
	}
	
	void setCamera(CameraPtr c)
	{
		_camera = c;
		ViewportPtr vp = _win->getPort(0);
		beginEditCP(vp);
			vp->setCamera(_camera);
		endEditCP(vp);

	}

	virtual void  setWindow( WindowPtr win )
	{
		_win = win;
	}

	virtual void  showAll(void)
	{
		osg::showAll(_camera,_root);
	}

	virtual void  initialize(void)
	{
		// Check necessary stuff
		if(_win == NullFC)
		{
			FWARNING(("SceneManager::initialize: window not set, "
					  "ignoring!\n"));
			return;
		}
	    
		// the rendering action
		_ownAction = RenderAction::create();
		_action = _ownAction;

		// the camera and light beacon
		NodePtr cartN = Node::create();
		_cart = Transform::create();

		beginEditCP(cartN);
			cartN->setCore(_cart);
		endEditCP(cartN);

		// the headlight
		_internalRoot = Node::create();
		_headlight    = DirectionalLight::create();

		addRefCP(_internalRoot);
		beginEditCP(_internalRoot);
			_internalRoot->setCore(_headlight);
			_internalRoot->addChild(cartN);
		endEditCP(_internalRoot);

		beginEditCP(_headlight);
			_headlight->setAmbient  (.3, .3, .3, 1);
			_headlight->setDiffuse  ( 1,  1,  1, 1);
			_headlight->setSpecular ( 1,  1,  1, 1);
			_headlight->setDirection( 0,  0,  1);
			_headlight->setBeacon   (cartN);
		endEditCP(_headlight);

		// the camera
		_camera = PerspectiveCamera::create();
		addRefCP(_camera);
		beginEditCP(PerspectiveCameraPtr::dcast(_camera));
			PerspectiveCameraPtr::dcast(_camera)->setBeacon(cartN);
			PerspectiveCameraPtr::dcast(_camera)->setFov   (deg2rad(60.f));
			PerspectiveCameraPtr::dcast(_camera)->setNear  (0.1f);
			PerspectiveCameraPtr::dcast(_camera)->setFar   (10000.f);
		endEditCP(PerspectiveCameraPtr::dcast(_camera));

		// need a viewport?
		if(_win->getPort().size() == 0)
		{
			SolidBackgroundPtr bg = SolidBackground::create();
			beginEditCP(bg);
				bg->setColor(Color3f(0, 0, 0));
			endEditCP(bg);

			ViewportPtr vp = Viewport::create();
			beginEditCP(vp);
				vp->setCamera                  (_camera);
				vp->setRoot                    (_internalRoot);
				vp->setSize                    (0,0, 1,1);
				vp->setBackground              (bg);
			endEditCP(vp);

			beginEditCP(_win);
				_win->addPort(vp);
			endEditCP(_win);
		}

	}


};

// The SimpleSceneManager to manage simple applications
SceneManager *mgr;

//Camera Beacon
TransformPtr CameraBeaconTransform;

//Viewpoint Indicator Location Information
TransformPtr ViewpointTransform;

//Centalized location marked with a Torus
TransformPtr BaseTransform;

//Location of one of the example objects
TransformPtr StationOneTransform;

//Location of the other example object
TransformPtr StationTwoTransform;

TransformPtr StationThreeTransform;


Matrix DriftMatrix;


DirectionalIndicatorMiniMapOverlayPtr DirectionalOverlay;

MiniMapIndicatorPtr BaseIndicator;
MiniMapIndicatorPtr StationOneIndicator;
MiniMapIndicatorPtr StationTwoIndicator;
MiniMapIndicatorPtr StationThreeIndicator;



//Mission and Mission tree variables

GenericMissionTreeModelPtr TutorialMissionModel;

DefaultMissionPtr Recon;
DefaultMissionPtr M1subA;
DefaultMissionPtr M1subB;
DefaultMissionPtr M1subC;
DefaultMissionPtr M1subReturn;


RubberBandCameraPtr RubberCamera;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_COMMAND)
       {
            TutorialWindowEventProducer->closeWindow();
       }

	   float TranslateAmount(0.05f);
	   float RotateAmount(0.1f);

	   switch(e->getKey())
	   {
	   case KeyEvent::KEY_LEFT:
		   {
		   }
		   break;
		   break;
	   default:
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

/*************************************************
This is the Listener for motion of the player object.
*************************************************/

class TutorialUpdateListener : public UpdateListener
{
public:
    virtual void update(const UpdateEventPtr e)
	{
		RubberCamera->update(e->getElapsedTime());

	   float TranslateAmount(1.0f);
	   float RotateAmount(1.0f);

	   Matrix ViewPointMat = ViewpointTransform->getMatrix();

	   TransformPtr CurrentWaypoint;
	   if(M1subReturn->getProperties()["Completed"] != 0)
	   {
	   }
	   else if(M1subC->getProperties()["Completed"] != 0)
	   {
		   CurrentWaypoint = BaseTransform;
	   }
	   else if(M1subB->getProperties()["Completed"] != 0)
	   {
		   CurrentWaypoint = StationThreeTransform;
	   }
	   else if(M1subA->getProperties()["Completed"] != 0)
	   {
		   CurrentWaypoint = StationTwoTransform;
	   }
	   
	   else
	   {
		   CurrentWaypoint = StationOneTransform;
	   }
        Vec3f IndictorPosition, ViewpointPosition, DummyVec;
        Quaternion DummyQuat;

        CurrentWaypoint->getMatrix().getTransform(IndictorPosition, DummyQuat, DummyVec, DummyQuat);
        ViewPointMat.getTransform(ViewpointPosition, DummyQuat, DummyVec, DummyQuat);

        Vec3f Delta = IndictorPosition - ViewpointPosition;
        Real32 Distance = Delta.length();

		if(Distance < 0.5)
		{
			if(CurrentWaypoint == StationOneTransform)
			{
				M1subA->getProperties()["Completed"] = 1;
				beginEditCP(DirectionalOverlay, DirectionalIndicatorMiniMapOverlay::IndicatorsFieldMask);
					DirectionalOverlay->getIndicators().clear();
					DirectionalOverlay->getIndicators().push_back(StationTwoIndicator); 
				beginEditCP(DirectionalOverlay, DirectionalIndicatorMiniMapOverlay::IndicatorsFieldMask);
				beginEditCP(Recon, DefaultMission::MissionsFieldMask);
					Recon->getMissions().push_back(M1subB);
				endEditCP(Recon, DefaultMission::MissionsFieldMask);

			}
			else if(CurrentWaypoint == StationTwoTransform)
			{
				M1subB->getProperties()["Completed"] = 1;
				beginEditCP(DirectionalOverlay, DirectionalIndicatorMiniMapOverlay::IndicatorsFieldMask);
					DirectionalOverlay->getIndicators().clear();
					DirectionalOverlay->getIndicators().push_back(StationThreeIndicator); 
				beginEditCP(DirectionalOverlay, DirectionalIndicatorMiniMapOverlay::IndicatorsFieldMask);
				beginEditCP(Recon, DefaultMission::MissionsFieldMask);
					Recon->getMissions().push_back(M1subC);
				endEditCP(Recon, DefaultMission::MissionsFieldMask);
			}
			else if(CurrentWaypoint == StationThreeTransform)
			{
				M1subC->getProperties()["Completed"] = 1;
				beginEditCP(DirectionalOverlay, DirectionalIndicatorMiniMapOverlay::IndicatorsFieldMask);
					DirectionalOverlay->getIndicators().clear();
					DirectionalOverlay->getIndicators().push_back(BaseIndicator); 
				beginEditCP(DirectionalOverlay, DirectionalIndicatorMiniMapOverlay::IndicatorsFieldMask);
				beginEditCP(Recon, DefaultMission::MissionsFieldMask);
					Recon->getMissions().push_back(M1subReturn);
				endEditCP(Recon, DefaultMission::MissionsFieldMask);
			}
			else if(CurrentWaypoint == BaseTransform)
			{
				M1subReturn->getProperties()["Completed"] = 1;
				beginEditCP(DirectionalOverlay, DirectionalIndicatorMiniMapOverlay::IndicatorsFieldMask);
					DirectionalOverlay->getIndicators().clear();
				beginEditCP(DirectionalOverlay, DirectionalIndicatorMiniMapOverlay::IndicatorsFieldMask);
			}
		}

		WindowEventProducerPtr TheEventProducer(WindowEventProducerPtr::dcast(e->getSource()));
		
		
		if(TheEventProducer->getKeyState(KeyEvent::KEY_UP) == KeyEvent::KEY_STATE_DOWN)
	   {
		   Matrix TranslateTransform;
		   TranslateTransform.setTranslate(0.0f,0.0f,-TranslateAmount*e->getElapsedTime()*0.01f);

		   DriftMatrix.mult(TranslateTransform);

	   }
		if(TheEventProducer->getKeyState(KeyEvent::KEY_DOWN) == KeyEvent::KEY_STATE_DOWN)
	   {
		   Matrix TranslateTransform;
		   TranslateTransform.setTranslate(0.0f,0.0f,TranslateAmount*e->getElapsedTime()*0.01f);

		   DriftMatrix.mult(TranslateTransform);

	   }
		if(TheEventProducer->getKeyState(KeyEvent::KEY_LEFT) == KeyEvent::KEY_STATE_DOWN)
	   {
		   Matrix TranslateTransform;
		   //TranslateTransform.setTranslate(-TranslateAmount,0.0f,0.0f);
		   TranslateTransform.setRotate(Quaternion(Vec3f(0.0f,1.0f,0.0f), RotateAmount*e->getElapsedTime()*0.01f));

		   DriftMatrix.mult(TranslateTransform);

	   }
		if(TheEventProducer->getKeyState(KeyEvent::KEY_RIGHT) == KeyEvent::KEY_STATE_DOWN)
	   {
		   Matrix TranslateTransform;
		   //TranslateTransform.setTranslate(TranslateAmount,0.0f,0.0f);
		   TranslateTransform.setRotate(Quaternion(Vec3f(0.0f,1.0f,0.0f), -RotateAmount*e->getElapsedTime()*0.01f));

		   DriftMatrix.mult(TranslateTransform);
	   }
	   
		Matrix NewTransform(ViewpointTransform->getMatrix());

		NewTransform.mult(DriftMatrix);

	   beginEditCP(ViewpointTransform, Transform::MatrixFieldMask);
		   ViewpointTransform->setMatrix(NewTransform);
	   endEditCP(ViewpointTransform, Transform::MatrixFieldMask);
      
	}
};

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    // Set up Window
    TutorialWindowEventProducer = createDefaultWindowEventProducer();
    WindowPtr MainWindow = TutorialWindowEventProducer->initWindow();

    TutorialWindowEventProducer->setDisplayCallback(display);
    TutorialWindowEventProducer->setReshapeCallback(reshape);

    TutorialKeyListener TheKeyListener;
    TutorialWindowEventProducer->addKeyListener(&TheKeyListener);
	TutorialUpdateListener TheUpdateListener;
    TutorialWindowEventProducer->addUpdateListener(&TheUpdateListener);

    // Create the SceneManager
    mgr = new SceneManager;

	 // Create the Graphics
    GraphicsPtr TutorialGraphics = osg::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
	
    // Make Torus Node (creates Torus in background of scene)
    NodePtr BaseGeometryNode = makeTorus(.25, 1, 16, 16);

	Matrix BaseTransMatrix;
	BaseTransMatrix.setTransform(Vec3f(-10.0,0.0,10.0));
	BaseTransform = Transform::create();
    beginEditCP(BaseTransform, Transform::MatrixFieldMask);
		BaseTransform->setMatrix(BaseTransMatrix);
    endEditCP(BaseTransform, Transform::MatrixFieldMask);

	NodePtr BaseNode = Node::create();
    beginEditCP(BaseNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        BaseNode->setCore(BaseTransform);
        BaseNode->addChild(BaseGeometryNode);
    endEditCP(BaseNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
	
    // Make Sphere Node
    NodePtr StationOneGeometryNode = makeSphere(2,1.0f);

	Matrix StationOneTransMatrix;
	StationOneTransMatrix.setTransform(Vec3f(5.0,0.0,5.0));
	StationOneTransform = Transform::create();
    beginEditCP(StationOneTransform, Transform::MatrixFieldMask);
		StationOneTransform->setMatrix(StationOneTransMatrix);
    endEditCP(StationOneTransform, Transform::MatrixFieldMask);

	NodePtr StationOneNode = Node::create();
    beginEditCP(StationOneNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        StationOneNode->setCore(StationOneTransform);
        StationOneNode->addChild(StationOneGeometryNode);
    endEditCP(StationOneNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
	
    // Make Cylinder Node
    NodePtr CylinderGeometryNode = makeBox(0.5,0.5,0.5,2,2,2);//makeCylinder(1.0,0.25,2,true,true,true);

    // Make Box Node
    NodePtr StationTwoGeometryNode = makeBox(1.5,1.5,1.5,2,2,2);

	Matrix BoxTransMatrix;
	BoxTransMatrix.setTransform(Vec3f(6.0,0.0,-7.0));
	StationTwoTransform = Transform::create();
    beginEditCP(StationTwoTransform, Transform::MatrixFieldMask);
		StationTwoTransform->setMatrix(BoxTransMatrix);
    endEditCP(StationTwoTransform, Transform::MatrixFieldMask);

	NodePtr BoxNode = Node::create();
    beginEditCP(BoxNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        BoxNode->setCore(StationTwoTransform);
        BoxNode->addChild(StationTwoGeometryNode);
    endEditCP(BoxNode, Node::CoreFieldMask | Node::ChildrenFieldMask);


	// Make StationThree
    NodePtr StationThreeGeometryNode = makeBox(1.5,1.5,1.5,2,2,2);

	Matrix StationThreeTransMatrix;
	StationThreeTransMatrix.setTransform(Vec3f(-1.0,0.0,-2.0));
	StationThreeTransform = Transform::create();
    beginEditCP(StationThreeTransform, Transform::MatrixFieldMask);
		StationThreeTransform->setMatrix(StationThreeTransMatrix);
    endEditCP(StationThreeTransform, Transform::MatrixFieldMask);

	NodePtr StationThreeNode = Node::create();
    beginEditCP(StationThreeNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        StationThreeNode->setCore(StationThreeTransform);
        StationThreeNode->addChild(StationThreeGeometryNode);
    endEditCP(StationThreeNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

	//Set the Camera Beacon Node
	Matrix Offset;
	//Offset.setTranslate(0.0f,2.5f,6.0f);
	Offset.setTranslate(0.0f,0.0,6.0f);
	CameraBeaconTransform = Transform::create();
    beginEditCP(CameraBeaconTransform, Transform::MatrixFieldMask);
        CameraBeaconTransform->setMatrix(Offset);
    endEditCP(CameraBeaconTransform, Transform::MatrixFieldMask);

	NodePtr CameraBeaconNode = Node::create();
    beginEditCP(CameraBeaconNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        CameraBeaconNode->setCore(CameraBeaconTransform);
    endEditCP(CameraBeaconNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

	//Set the Viewpoint Transform Node
	ViewpointTransform = Transform::create();

	Matrix StartingLocation;

	StartingLocation.setTransform(Vec3f(-10.0f,0.0f,9.4f));

	ViewpointTransform->setMatrix(StartingLocation);

	NodePtr ViewpointGeomtryNode = Node::create();
    beginEditCP(ViewpointGeomtryNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        ViewpointGeomtryNode->setCore(ViewpointTransform);
        ViewpointGeomtryNode->addChild(CylinderGeometryNode);
        ViewpointGeomtryNode->addChild(CameraBeaconNode);
    endEditCP(ViewpointGeomtryNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

    // Make Main Scene Node and add the Torus
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
        scene->addChild(BaseNode);
        scene->addChild(StationOneNode);
        scene->addChild(BoxNode);
        scene->addChild(StationThreeNode);
        scene->addChild(ViewpointGeomtryNode);
    endEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);

	//Set the Root node to the Scene Manager
	mgr->setRoot(scene);

	//The perspective decoratee camera
	CameraPtr PCamera = PerspectiveCamera::create();
	beginEditCP(PerspectiveCameraPtr::dcast(PCamera));
		PerspectiveCameraPtr::dcast(PCamera)->setBeacon(CameraBeaconNode);
		PerspectiveCameraPtr::dcast(PCamera)->setFov   (deg2rad(60.f));
		PerspectiveCameraPtr::dcast(PCamera)->setNear  (0.1f);
		PerspectiveCameraPtr::dcast(PCamera)->setFar   (10000.f);
	endEditCP(PerspectiveCameraPtr::dcast(PCamera));
	
	//Create the Rubber band Camera
	Vec3f PositionCoefficients(0.1,1.5,1.5);
	Vec3f OrientationCoefficients(0.1,2.5,2.5);

	RubberCamera = RubberBandCamera::create();
	beginEditCP(RubberCamera, RubberBandCamera::DecorateeFieldMask | RubberBandCamera::BeaconFieldMask | RubberBandCamera::PositionCoefficientsFieldMask | RubberBandCamera::OrientationCoefficientsFieldMask);
		RubberCamera->setDecoratee(PCamera);
		RubberCamera->setBeacon(CameraBeaconNode);
		RubberCamera->setPositionCoefficients(PositionCoefficients);
		RubberCamera->setOrientationCoefficients(OrientationCoefficients);
	endEditCP(RubberCamera, RubberBandCamera::DecorateeFieldMask | RubberBandCamera::BeaconFieldMask | RubberBandCamera::PositionCoefficientsFieldMask | RubberBandCamera::OrientationCoefficientsFieldMask);
	RubberCamera->setToBeacon();

    //Set the Rubber band camera as the viewpoint of the scene
	mgr->setCamera(RubberCamera);

    //Create the Mini Map itself
	LayeredImageMiniMapPtr MiniMap = osg::LayeredImageMiniMap::create();

	//World to MiniMap Transformation
	MiniMapMatrixTransformationPtr WorldToMiniMapTransformation = MiniMapMatrixTransformation::create();
	Matrix Transform;
	Transform.setTransform(Vec3f(0.5,0.5,0.0f), Quaternion(Vec3f(1.0f,0.0f,0.0f),deg2rad(-90.0)), Vec3f(0.042, 1.0, 0.042));
	beginEditCP(WorldToMiniMapTransformation, MiniMapMatrixTransformation::TransformationFieldMask);
		WorldToMiniMapTransformation->setTransformation(Transform);
	endEditCP(WorldToMiniMapTransformation, MiniMapMatrixTransformation::TransformationFieldMask);

	//Create the Viewpoint Component
	ImageComponentPtr ViewPointComponentPrototype = ImageComponent::create();
	beginEditCP(ViewPointComponentPrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
		ViewPointComponentPrototype->setPreferredSize(Vec2f(30.0f,30.0f));
		ViewPointComponentPrototype->setScale(ImageComponent::SCALE_MIN_AXIS);
		ViewPointComponentPrototype->setAlignment(Vec2f(0.5f,0.5f));
	endEditCP(ViewPointComponentPrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
	ImagePtr ShipImage = ImageFileHandler::the().read(Path("./Data/MissionMiniGame/Ship.PNG").string().c_str());
	ViewPointComponentPrototype->setImage(ShipImage);
	ViewPointComponentPrototype->setRolloverImage(ShipImage);
	ViewPointComponentPrototype->setDisabledImage(ShipImage);
	ViewPointComponentPrototype->setFocusedImage(ShipImage);

	//Create the Viewpoint Component Generator
	DefaultMiniMapIndicatorComponentGeneratorPtr ShipComponentGenerator = DefaultMiniMapIndicatorComponentGenerator::create();
	beginEditCP(ShipComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);
		ShipComponentGenerator->setComponentPrototype(ViewPointComponentPrototype);
	endEditCP(ShipComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);

	//Create the Torus Node Indicator Prototype
	ImageComponentPtr BasePrototype = ImageComponent::create();
	beginEditCP(BasePrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
		BasePrototype->setPreferredSize(Vec2f(200.0f,200.0f));
		BasePrototype->setScale(ImageComponent::SCALE_MIN_AXIS);
		BasePrototype->setAlignment(Vec2f(0.5f,0.5f));
	endEditCP(BasePrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
	ImagePtr BaseImage = ImageFileHandler::the().read(Path("./Data/MissionMiniGame/Base.PNG").string().c_str());
	BasePrototype->setImage(BaseImage);
	BasePrototype->setRolloverImage(BaseImage);
	BasePrototype->setDisabledImage(BaseImage);
	BasePrototype->setFocusedImage(BaseImage);

	//Create the Torus Component Generator
	DefaultMiniMapIndicatorComponentGeneratorPtr BaseComponentGenerator = DefaultMiniMapIndicatorComponentGenerator::create();
	beginEditCP(BaseComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);
		BaseComponentGenerator->setComponentPrototype(BasePrototype);
	endEditCP(BaseComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);
	

	ImagePtr StationImage = ImageFileHandler::the().read(Path("./Data/MissionMiniGame/Station.PNG").string().c_str());

	//Create the Sphere Node Indicator Prototype
	ImageComponentPtr StationNodePrototype = ImageComponent::create();
	beginEditCP(StationNodePrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
		StationNodePrototype->setPreferredSize(Vec2f(50.0f,50.0f));
		StationNodePrototype->setScale(ImageComponent::SCALE_MIN_AXIS);
		StationNodePrototype->setAlignment(Vec2f(0.5f,0.5f));
	endEditCP(StationNodePrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
	StationNodePrototype->setImage(StationImage);
	StationNodePrototype->setRolloverImage(StationImage);
	StationNodePrototype->setDisabledImage(StationImage);
	StationNodePrototype->setFocusedImage(StationImage);

	//Create the Sphere Component Generator
	DefaultMiniMapIndicatorComponentGeneratorPtr StationComponentGenerator = DefaultMiniMapIndicatorComponentGenerator::create();
	beginEditCP(StationComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);
		StationComponentGenerator->setComponentPrototype(StationNodePrototype);
	endEditCP(StationComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);

	//Create the Viewpoint Indicator
	MiniMapIndicatorPtr ViewpointIndicator = MiniMapIndicator::create();

	beginEditCP(ViewpointIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
		ViewpointIndicator->setGenerator(ShipComponentGenerator);
		ViewpointIndicator->setLocation(ViewpointGeomtryNode);
	endEditCP(ViewpointIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);

	//Other Indicators
	BaseIndicator = MiniMapIndicator::create();
	beginEditCP(BaseIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
		BaseIndicator->setGenerator(BaseComponentGenerator);
		BaseIndicator->setLocation(BaseGeometryNode);
	endEditCP(BaseIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
	
	StationOneIndicator = MiniMapIndicator::create();
	beginEditCP(StationOneIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
		StationOneIndicator->setGenerator(StationComponentGenerator);
		StationOneIndicator->setLocation(StationOneGeometryNode);
	endEditCP(StationOneIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
	
	StationTwoIndicator = MiniMapIndicator::create();
	beginEditCP(StationTwoIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
		StationTwoIndicator->setGenerator(StationComponentGenerator);
		StationTwoIndicator->setLocation(StationTwoGeometryNode);
	endEditCP(StationTwoIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);

	StationThreeIndicator = MiniMapIndicator::create();
	beginEditCP(StationThreeIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
		StationThreeIndicator->setGenerator(StationComponentGenerator);
		StationThreeIndicator->setLocation(StationThreeGeometryNode);
	endEditCP(StationThreeIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);



	//Create the Directional Indicator Prototype
	ImageComponentPtr DirectionalComponentPrototype = ImageComponent::create();
	beginEditCP(DirectionalComponentPrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
		DirectionalComponentPrototype->setPreferredSize(Vec2f(15.0f,20.0f));
        DirectionalComponentPrototype->setScale(ImageComponent::SCALE_STRETCH);
		DirectionalComponentPrototype->setAlignment(Vec2f(0.5f,0.5f));
	endEditCP(DirectionalComponentPrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
	ImagePtr PointerImage = ImageFileHandler::the().read((Path("./Data/Pointer.png")).string().c_str());
	DirectionalComponentPrototype->setImage(PointerImage);
	DirectionalComponentPrototype->setRolloverImage(PointerImage);
	DirectionalComponentPrototype->setDisabledImage(PointerImage);
	DirectionalComponentPrototype->setFocusedImage(PointerImage);

	//Create the Directional Component Generator
	DefaultDirectionalIndicatorComponentGeneratorPtr DirectionalComponentGenerator = DefaultDirectionalIndicatorComponentGenerator::create();
	beginEditCP(DirectionalComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);
		DirectionalComponentGenerator->setComponentPrototype(DirectionalComponentPrototype);
	endEditCP(DirectionalComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);

	//Create the Overlay
	DirectionalOverlay = DirectionalIndicatorMiniMapOverlay::create();
	beginEditCP(DirectionalOverlay, DirectionalIndicatorMiniMapOverlay::IndicatorsFieldMask | DirectionalIndicatorMiniMapOverlay::DirectionComponentGeneratorFieldMask);
		DirectionalOverlay->getIndicators().push_back(StationOneIndicator);     //Link the Torus Indicator to the Mini Map
		DirectionalOverlay->setDirectionComponentGenerator(DirectionalComponentGenerator);
		DirectionalOverlay->setDrawWhenVisible(false);
		DirectionalOverlay->setMinimumDistance(40.0f);
	endEditCP(DirectionalOverlay, DirectionalIndicatorMiniMapOverlay::IndicatorsFieldMask | DirectionalIndicatorMiniMapOverlay::DirectionComponentGeneratorFieldMask);


	//Mission

	M1subA = DefaultMission::create();
	beginEditCP(M1subA, DefaultMission::DescriptionFieldMask | DefaultMission::PropertiesFieldMask);
		M1subA->setDescription("Fly to station 1");
		M1subA->getProperties()["Completed"] = 0;
	endEditCP(M1subA, DefaultMission::DescriptionFieldMask | DefaultMission::PropertiesFieldMask);

	M1subB = DefaultMission::create();
	beginEditCP(M1subB, DefaultMission::DescriptionFieldMask | DefaultMission::PropertiesFieldMask);
		M1subB->setDescription("Fly to station 2");
		M1subB->getProperties()["Completed"] = 0;
	endEditCP(M1subB, DefaultMission::DescriptionFieldMask | DefaultMission::PropertiesFieldMask);

	M1subC = DefaultMission::create();
	beginEditCP(M1subC, DefaultMission::DescriptionFieldMask | DefaultMission::PropertiesFieldMask);
		M1subC->setDescription("Fly to station 3");
		M1subC->getProperties()["Completed"] = 0;
	endEditCP(M1subC, DefaultMission::DescriptionFieldMask | DefaultMission::PropertiesFieldMask);

	M1subReturn = DefaultMission::create();
	beginEditCP(M1subReturn, DefaultMission::DescriptionFieldMask | DefaultMission::PropertiesFieldMask);
		M1subReturn->setDescription("Fly back to base");
		M1subReturn->getProperties()["Completed"] = 0;
	endEditCP(M1subReturn, DefaultMission::DescriptionFieldMask | DefaultMission::PropertiesFieldMask);

	DefaultMissionPtr MissionOne = DefaultMission::create();

	Recon = DefaultMission::create();

	beginEditCP(Recon, DefaultMission::DescriptionFieldMask | DefaultMission::MissionsFieldMask);
		Recon->setDescription("Mission 1 - RECON");
		Recon->getMissions().push_back(M1subA);
	endEditCP(Recon, DefaultMission::DescriptionFieldMask | DefaultMission::MissionsFieldMask);
	
	beginEditCP(MissionOne, DefaultMission::DescriptionFieldMask | DefaultMission::MissionsFieldMask);
		MissionOne->setDescription("");
		MissionOne->getMissions().push_back(Recon);
	endEditCP(MissionOne, DefaultMission::DescriptionFieldMask | DefaultMission::MissionsFieldMask);
	


	//Tree

	TutorialMissionModel = GenericMissionTreeModel::create();

	TutorialMissionModel->setRoot(MissionOne);

	TreePtr TutorialMissionTree = Tree::create();

	DefaultMissionTreeComponentGeneratorPtr TutorialMissionComponentGenerator = DefaultMissionTreeComponentGenerator::create();

	BorderLayoutConstraintsPtr MissionConstraints = osg::BorderLayoutConstraints::create();
	beginEditCP(MissionConstraints, BorderLayoutConstraints::RegionFieldMask);
		MissionConstraints->setRegion(BorderLayoutConstraints::BORDER_EAST);
	endEditCP(MissionConstraints, BorderLayoutConstraints::RegionFieldMask);

	beginEditCP(TutorialMissionTree, Tree::PreferredSizeFieldMask | Tree::ModelFieldMask | Tree::ConstraintsFieldMask);
        TutorialMissionTree->setPreferredSize(Vec2f(150, 500));
        TutorialMissionTree->setModel(TutorialMissionModel);
		TutorialMissionTree->setConstraints(MissionConstraints);
		TutorialMissionTree->setCellGenerator(TutorialMissionComponentGenerator);
    endEditCP(TutorialMissionTree, Tree::PreferredSizeFieldMask | Tree::ModelFieldMask | Tree::ConstraintsFieldMask);

    //Layout Expansion
	TutorialMissionTree->expandPath(TutorialMissionModel->getPath(MissionPtr::dcast(Recon)));


	// Setup the size and other preferences to the minimap
    BorderLayoutConstraintsPtr MiniMapConstraints = osg::BorderLayoutConstraints::create();
	beginEditCP(MiniMapConstraints, BorderLayoutConstraints::RegionFieldMask);
		MiniMapConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
	endEditCP(MiniMapConstraints, BorderLayoutConstraints::RegionFieldMask);
	 
    beginEditCP(MiniMap, LayeredImageMiniMap::PreferredSizeFieldMask | LayeredImageMiniMap::ViewPointIndicatorFieldMask | LayeredImageMiniMap::TransformationFieldMask | LayeredImageMiniMap::OpacityFieldMask | LayeredImageMiniMap::ConstraintsFieldMask | LayeredImageMiniMap::LockMapOrientationFieldMask | MiniMap::UnlockedMapSizeFieldMask | MiniMap::IndicatorsFieldMask);
	    MiniMap->setPreferredSize(Pnt2f(450,450));
	    MiniMap->setViewPointIndicator(ViewpointIndicator);
		MiniMap->setTransformation(WorldToMiniMapTransformation);
		MiniMap->setOpacity(1.0);
		MiniMap->setConstraints(MiniMapConstraints);
		MiniMap->setLockMapOrientation(false);                  //If this is changed to true the map will then remain stationary and the indicator will then move and rotate
        MiniMap->setUnlockedMapSize(Vec2f(3000,3000));          //This item is only necassary when the map is set to Unlocked Orientation
		MiniMap->getIndicators().push_back(BaseIndicator);     //Link the Torus Indicator to the Mini Map
		MiniMap->getIndicators().push_back(StationOneIndicator);    //Link the Sphere Indicator to the Mini Map
		MiniMap->getIndicators().push_back(StationTwoIndicator);       //Link the Box Indicator to the Mini Map
		MiniMap->getIndicators().push_back(StationThreeIndicator);
		MiniMap->getOverlays().push_back(DirectionalOverlay);
	endEditCP(MiniMap, LayeredImageMiniMap::PreferredSizeFieldMask | LayeredImageMiniMap::ViewPointIndicatorFieldMask | LayeredImageMiniMap::TransformationFieldMask | LayeredImageMiniMap::OpacityFieldMask | LayeredImageMiniMap::ConstraintsFieldMask | LayeredImageMiniMap::LockMapOrientationFieldMask | MiniMap::UnlockedMapSizeFieldMask | MiniMap::IndicatorsFieldMask);

    //Set the images the map will use a layers of the scene.
    //The second arg in the method call is the space between that layer and the layer befor it
	MiniMap->insertLayer(Path("./Data/MissionMiniGame/Starmap.jpg").string().c_str(), 5);

 
 
    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
    LayoutPtr MainInternalWindowLayout = osg::BorderLayout::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
	   MainInternalWindow->getChildren().push_back(TutorialMissionTree);
	   MainInternalWindow->getChildren().push_back(MiniMap);
	   MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(1.0f,1.0f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(1.0f,1.0f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
    endEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);

	
    // Create the Drawing Surface
    UIDrawingSurfacePtr TutorialDrawingSurface = UIDrawingSurface::create();
    beginEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindowEventProducer);
    endEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
    
	TutorialDrawingSurface->openWindow(MainInternalWindow);
	
	
	// Create the UI Foreground Object
    UIForegroundPtr TutorialUIForeground = osg::UIForeground::create();

    beginEditCP(TutorialUIForeground, UIForeground::DrawingSurfaceFieldMask);
        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);
    endEditCP(TutorialUIForeground, UIForeground::DrawingSurfaceFieldMask);

    mgr->setRoot(scene);

    // Add the UI Foreground Object to the Scene
    ViewportPtr TutorialViewport = mgr->getWindow()->getPort(0);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);
        TutorialViewport->getForegrounds().push_back(TutorialUIForeground);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);

    // Show the whole Scene
    //mgr->showAll();

    Vec2f WinSize(TutorialWindowEventProducer->getDesktopSize() * 0.85f);
    Pnt2f WinPos((TutorialWindowEventProducer->getDesktopSize() - WinSize) *0.85);
    TutorialWindowEventProducer->openWindow(WinPos,
            WinSize,
            "OpenSG 12Mission Window");

    //Enter main Loop
    TutorialWindowEventProducer->mainLoop();

    osgExit();

    return 0;
}


// Callback functions


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
