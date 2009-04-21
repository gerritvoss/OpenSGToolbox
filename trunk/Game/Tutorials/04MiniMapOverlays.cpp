/*************************************************
Welcome to the 03 Mini Map Multiple Indicator 
Tutorial. This is pretty much a continuation of the
previous tutorial except as the title implies we 
will be putting in more indicators. 

The extra indicators in this tutorial mark objects
that are stationary. Although if you look carefully
the potential to use these indicators for other 
moving objects is there.
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
#include <OpenSG/Input/OSGWindowAdapter.h>
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

#include <OpenSG/Game/OSGDirectionalIndicatorMiniMapOverlay.h>
#include <OpenSG/Game/OSGDefaultDirectionalIndicatorComponentGenerator.h>


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

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
TransformPtr TorusTransform;

//Location of one of the example objects
TransformPtr SphereTransform;

//Location of the other example object
TransformPtr BoxTransform;


RubberBandCameraPtr RubberCamera;

bool ExitApp = false;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

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

	   float TranslateAmount(0.05f);
	   float RotateAmount(0.1f);

	   switch(e.getKey())
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

   virtual void keyReleased(const KeyEvent& e)
   {
   }

   virtual void keyTyped(const KeyEvent& e)
   {
   }
};

/*************************************************
This is the Listener for motion of the player object.
*************************************************/

class TutorialUpdateListener : public UpdateListener
{
public:
    virtual void update(const UpdateEvent& e)
	{
		RubberCamera->update(e.getElapsedTime());


	   float TranslateAmount(1.0f);
	   float RotateAmount(1.0f);

		WindowEventProducerPtr TheEventProducer(WindowEventProducerPtr::dcast(e.getSource()));
		if(TheEventProducer->getKeyState(KeyEvent::KEY_LEFT) == KeyEvent::KEY_STATE_DOWN)
		{
		   Matrix TranslateTransform;
		   TranslateTransform.setTranslate(-TranslateAmount*e.getElapsedTime(),0.0f,0.0f);
		   Matrix NewTransform(ViewpointTransform->getMatrix());

		   NewTransform.mult(TranslateTransform);

		   beginEditCP(ViewpointTransform, Transform::MatrixFieldMask);
			   ViewpointTransform->setMatrix(NewTransform);
		   endEditCP(ViewpointTransform, Transform::MatrixFieldMask);
		}
		if(TheEventProducer->getKeyState(KeyEvent::KEY_RIGHT) == KeyEvent::KEY_STATE_DOWN)
	   {
		   Matrix TranslateTransform;
		   TranslateTransform.setTranslate(TranslateAmount*e.getElapsedTime(),0.0f,0.0f);
		   Matrix NewTransform(ViewpointTransform->getMatrix());

		   NewTransform.mult(TranslateTransform);

		   beginEditCP(ViewpointTransform, Transform::MatrixFieldMask);
			   ViewpointTransform->setMatrix(NewTransform);
		   endEditCP(ViewpointTransform, Transform::MatrixFieldMask);
	   }
		if(TheEventProducer->getKeyState(KeyEvent::KEY_UP) == KeyEvent::KEY_STATE_DOWN)
	   {
		   Matrix TranslateTransform;
		   TranslateTransform.setTranslate(0.0f,0.0f,-TranslateAmount*e.getElapsedTime());
		   Matrix NewTransform(ViewpointTransform->getMatrix());

		   NewTransform.mult(TranslateTransform);

		   beginEditCP(ViewpointTransform, Transform::MatrixFieldMask);
			   ViewpointTransform->setMatrix(NewTransform);
		   endEditCP(ViewpointTransform, Transform::MatrixFieldMask);
	   }
		if(TheEventProducer->getKeyState(KeyEvent::KEY_DOWN) == KeyEvent::KEY_STATE_DOWN)
	   {
		   Matrix TranslateTransform;
		   TranslateTransform.setTranslate(0.0f,0.0f,TranslateAmount*e.getElapsedTime());
		   Matrix NewTransform(ViewpointTransform->getMatrix());

		   NewTransform.mult(TranslateTransform);

		   beginEditCP(ViewpointTransform, Transform::MatrixFieldMask);
			   ViewpointTransform->setMatrix(NewTransform);
		   endEditCP(ViewpointTransform, Transform::MatrixFieldMask);
	   }
		if(TheEventProducer->getKeyState(KeyEvent::KEY_A) == KeyEvent::KEY_STATE_DOWN)
	   {
		   Matrix TranslateTransform;
		   //TranslateTransform.setTranslate(-TranslateAmount,0.0f,0.0f);
		   TranslateTransform.setRotate(Quaternion(Vec3f(0.0f,1.0f,0.0f), RotateAmount*e.getElapsedTime()));
		   Matrix NewTransform(ViewpointTransform->getMatrix());

		   NewTransform.mult(TranslateTransform);

		   beginEditCP(ViewpointTransform, Transform::MatrixFieldMask);
			   ViewpointTransform->setMatrix(NewTransform);
		   endEditCP(ViewpointTransform, Transform::MatrixFieldMask);
	   }
		if(TheEventProducer->getKeyState(KeyEvent::KEY_D) == KeyEvent::KEY_STATE_DOWN)
	   {
		   Matrix TranslateTransform;
		   //TranslateTransform.setTranslate(TranslateAmount,0.0f,0.0f);
		   TranslateTransform.setRotate(Quaternion(Vec3f(0.0f,1.0f,0.0f), -RotateAmount*e.getElapsedTime()));
		   Matrix NewTransform(ViewpointTransform->getMatrix());

		   NewTransform.mult(TranslateTransform);

		   beginEditCP(ViewpointTransform, Transform::MatrixFieldMask);
			   ViewpointTransform->setMatrix(NewTransform);
		   endEditCP(ViewpointTransform, Transform::MatrixFieldMask);
	   }
        if(TheEventProducer->getKeyState(KeyEvent::KEY_W) == KeyEvent::KEY_STATE_DOWN)
	   {
		   Matrix TranslateTransform;
		   TranslateTransform.setTranslate(0.0f,TranslateAmount*e.getElapsedTime(),0.0f);
		   Matrix NewTransform(ViewpointTransform->getMatrix());

		   NewTransform.mult(TranslateTransform);

		   beginEditCP(ViewpointTransform, Transform::MatrixFieldMask);
			   ViewpointTransform->setMatrix(NewTransform);
		   endEditCP(ViewpointTransform, Transform::MatrixFieldMask);
	   }
         if(TheEventProducer->getKeyState(KeyEvent::KEY_S) == KeyEvent::KEY_STATE_DOWN)
	   {
		   Matrix TranslateTransform;
		   TranslateTransform.setTranslate(0.0f,-TranslateAmount*e.getElapsedTime(),0.0f);
		   Matrix NewTransform(ViewpointTransform->getMatrix());

		   NewTransform.mult(TranslateTransform);

		   beginEditCP(ViewpointTransform, Transform::MatrixFieldMask);
			   ViewpointTransform->setMatrix(NewTransform);
		   endEditCP(ViewpointTransform, Transform::MatrixFieldMask);
	   }
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
	TutorialUpdateListener TheUpdateListener;
    TutorialWindowEventProducer->addUpdateListener(&TheUpdateListener);

    // Create the SceneManager
    mgr = new SceneManager;

    // Tell the Manager what to manage
    mgr->setWindow(MainWindow);
	
    TutorialWindowEventProducer->openWindow(Pnt2f(0,0),
                                        Vec2f(700,850),
                                        "OpenSG 04MiniMapOverlays");
										
    // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.25, 1, 16, 16);

	Matrix TorusTransMatrix;
	TorusTransMatrix.setTransform(Vec3f(0.0,0.0,0.0));
	TorusTransform = Transform::create();
    beginEditCP(TorusTransform, Transform::MatrixFieldMask);
		TorusTransform->setMatrix(TorusTransMatrix);
    endEditCP(TorusTransform, Transform::MatrixFieldMask);

	NodePtr TorusNode = Node::create();
    beginEditCP(TorusNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        TorusNode->setCore(TorusTransform);
        TorusNode->addChild(TorusGeometryNode);
    endEditCP(TorusNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
	
    // Make Sphere Node
    NodePtr SphereGeometryNode = makeSphere(2,1.0f);

	Matrix SphereTransMatrix;
	SphereTransMatrix.setTransform(Vec3f(3.0,0.0,0.0));
	SphereTransform = Transform::create();
    beginEditCP(SphereTransform, Transform::MatrixFieldMask);
		SphereTransform->setMatrix(SphereTransMatrix);
    endEditCP(SphereTransform, Transform::MatrixFieldMask);

	NodePtr SphereNode = Node::create();
    beginEditCP(SphereNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        SphereNode->setCore(SphereTransform);
        SphereNode->addChild(SphereGeometryNode);
    endEditCP(SphereNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
	
    // Make Cylinder Node
    NodePtr CylinderGeometryNode = makeBox(0.5,0.5,0.5,2,2,2);//makeCylinder(1.0,0.25,2,true,true,true);

    // Make Box Node
    NodePtr BoxGeometryNode = makeBox(1.5,1.5,1.5,2,2,2);

	Matrix BoxTransMatrix;
	BoxTransMatrix.setTransform(Vec3f(-3.0,0.0,0.0));
	BoxTransform = Transform::create();
    beginEditCP(BoxTransform, Transform::MatrixFieldMask);
		BoxTransform->setMatrix(BoxTransMatrix);
    endEditCP(BoxTransform, Transform::MatrixFieldMask);

	NodePtr BoxNode = Node::create();
    beginEditCP(BoxNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        BoxNode->setCore(BoxTransform);
        BoxNode->addChild(BoxGeometryNode);
    endEditCP(BoxNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

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
        scene->addChild(TorusNode);
        scene->addChild(SphereNode);
        scene->addChild(BoxNode);
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
		ViewPointComponentPrototype->setPreferredSize(Vec2f(20.0f,20.0f));
		ViewPointComponentPrototype->setScale(ImageComponent::SCALE_MIN_AXIS);
		ViewPointComponentPrototype->setAlignment(Vec2f(0.5f,0.5f));
	endEditCP(ViewPointComponentPrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
	ImagePtr ShipImage = ImageFileHandler::the().read(Path("./Ship.JPG").string().c_str());
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
	ImageComponentPtr TorusNodeComponentPrototype = ImageComponent::create();
	beginEditCP(TorusNodeComponentPrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
		TorusNodeComponentPrototype->setPreferredSize(Vec2f(20.0f,20.0f));
		TorusNodeComponentPrototype->setScale(ImageComponent::SCALE_MIN_AXIS);
		TorusNodeComponentPrototype->setAlignment(Vec2f(0.5f,0.5f));
	endEditCP(TorusNodeComponentPrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
	ImagePtr TorusImage = ImageFileHandler::the().read(Path("./TorusNode.jpg").string().c_str());
	TorusNodeComponentPrototype->setImage(TorusImage);
	TorusNodeComponentPrototype->setRolloverImage(TorusImage);
	TorusNodeComponentPrototype->setDisabledImage(TorusImage);
	TorusNodeComponentPrototype->setFocusedImage(TorusImage);

	//Create the Torus Component Generator
	DefaultMiniMapIndicatorComponentGeneratorPtr TorusComponentGenerator = DefaultMiniMapIndicatorComponentGenerator::create();
	beginEditCP(TorusComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);
		TorusComponentGenerator->setComponentPrototype(TorusNodeComponentPrototype);
	endEditCP(TorusComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);
	
	//Create the Sphere Node Indicator Prototype
	ImageComponentPtr SphereNodeComponentPrototype = ImageComponent::create();
	beginEditCP(SphereNodeComponentPrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
		SphereNodeComponentPrototype->setPreferredSize(Vec2f(20.0f,20.0f));
		SphereNodeComponentPrototype->setScale(ImageComponent::SCALE_MIN_AXIS);
		SphereNodeComponentPrototype->setAlignment(Vec2f(0.5f,0.5f));
	endEditCP(SphereNodeComponentPrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
	ImagePtr SphereImage = ImageFileHandler::the().read(Path("./SphereNode.jpg").string().c_str());
	SphereNodeComponentPrototype->setImage(SphereImage);
	SphereNodeComponentPrototype->setRolloverImage(SphereImage);
	SphereNodeComponentPrototype->setDisabledImage(SphereImage);
	SphereNodeComponentPrototype->setFocusedImage(SphereImage);

	//Create the Sphere Component Generator
	DefaultMiniMapIndicatorComponentGeneratorPtr SphereComponentGenerator = DefaultMiniMapIndicatorComponentGenerator::create();
	beginEditCP(SphereComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);
		SphereComponentGenerator->setComponentPrototype(SphereNodeComponentPrototype);
	endEditCP(SphereComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);
	
	//Create the Box Node Indicator Prototype
	ImageComponentPtr BoxNodeComponentPrototype = ImageComponent::create();
	beginEditCP(BoxNodeComponentPrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
		BoxNodeComponentPrototype->setPreferredSize(Vec2f(20.0f,20.0f));
		BoxNodeComponentPrototype->setScale(ImageComponent::SCALE_MIN_AXIS);
		BoxNodeComponentPrototype->setAlignment(Vec2f(0.5f,0.5f));
	endEditCP(BoxNodeComponentPrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
	ImagePtr BoxImage = ImageFileHandler::the().read(Path("./BoxNode.jpg").string().c_str());
	BoxNodeComponentPrototype->setImage(BoxImage);
	BoxNodeComponentPrototype->setRolloverImage(BoxImage);
	BoxNodeComponentPrototype->setDisabledImage(BoxImage);
	BoxNodeComponentPrototype->setFocusedImage(BoxImage);

	//Create the Box Component Generator
	DefaultMiniMapIndicatorComponentGeneratorPtr BoxComponentGenerator = DefaultMiniMapIndicatorComponentGenerator::create();
	beginEditCP(BoxComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);
		BoxComponentGenerator->setComponentPrototype(BoxNodeComponentPrototype);
	endEditCP(BoxComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);

	//Create the Viewpoint Indicator
	MiniMapIndicatorPtr ViewpointIndicator = MiniMapIndicator::create();

	beginEditCP(ViewpointIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
		ViewpointIndicator->setGenerator(ShipComponentGenerator);
		ViewpointIndicator->setLocation(ViewpointGeomtryNode);
	endEditCP(ViewpointIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);

	//Other Indicators
	MiniMapIndicatorPtr TorusIndicator = MiniMapIndicator::create();
	beginEditCP(TorusIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
		TorusIndicator->setGenerator(TorusComponentGenerator);
		TorusIndicator->setLocation(TorusGeometryNode);
	endEditCP(TorusIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
	
	MiniMapIndicatorPtr SphereIndicator = MiniMapIndicator::create();
	beginEditCP(SphereIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
		SphereIndicator->setGenerator(SphereComponentGenerator);
		SphereIndicator->setLocation(SphereGeometryNode);
	endEditCP(SphereIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
	
	MiniMapIndicatorPtr BoxIndicator = MiniMapIndicator::create();
	beginEditCP(BoxIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
		BoxIndicator->setGenerator(BoxComponentGenerator);
		BoxIndicator->setLocation(BoxGeometryNode);
	endEditCP(BoxIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);

	//*****************Overlay**************************
	//Create the Directional Indicator Prototype
	ImageComponentPtr DirectionalComponentPrototype = ImageComponent::create();
	beginEditCP(DirectionalComponentPrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
		DirectionalComponentPrototype->setPreferredSize(Vec2f(20.0f,20.0f));
		DirectionalComponentPrototype->setScale(ImageComponent::SCALE_MIN_AXIS);
		DirectionalComponentPrototype->setAlignment(Vec2f(0.5f,0.5f));
	endEditCP(DirectionalComponentPrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
	ImagePtr PointerImage = ImageFileHandler::the().read(Path("./Pointer.png").string().c_str());
	DirectionalComponentPrototype->setImage(PointerImage);
	DirectionalComponentPrototype->setRolloverImage(PointerImage);
	DirectionalComponentPrototype->setDisabledImage(PointerImage);
	DirectionalComponentPrototype->setFocusedImage(PointerImage);

	//Create the Directional Component Generator
	DefaultDirectionalIndicatorComponentGeneratorPtr DirectionalComponentGenerator = DefaultDirectionalIndicatorComponentGenerator::create();
	beginEditCP(DirectionalComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);
		DirectionalComponentGenerator->setComponentPrototype(BoxNodeComponentPrototype);
	endEditCP(DirectionalComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);

	//Create the Overlay
	DirectionalIndicatorMiniMapOverlayPtr DirectionalOverlay = DirectionalIndicatorMiniMapOverlay::create();
	beginEditCP(DirectionalOverlay, DirectionalIndicatorMiniMapOverlay::IndicatorsFieldMask | DirectionalIndicatorMiniMapOverlay::DirectionComponentGeneratorFieldMask);
		DirectionalOverlay->getIndicators().push_back(TorusIndicator);     //Link the Torus Indicator to the Mini Map
		DirectionalOverlay->getIndicators().push_back(SphereIndicator);    //Link the Sphere Indicator to the Mini Map
		DirectionalOverlay->getIndicators().push_back(BoxIndicator);       //Link the Box Indicator to the Mini Map
		DirectionalOverlay->setDirectionComponentGenerator(DirectionalComponentGenerator);
	endEditCP(DirectionalOverlay, DirectionalIndicatorMiniMapOverlay::IndicatorsFieldMask | DirectionalIndicatorMiniMapOverlay::DirectionComponentGeneratorFieldMask);
	//*******************************************
	

	// Setup the size and other preferences to the minimap
    BorderLayoutConstraintsPtr MiniMapConstraints = osg::BorderLayoutConstraints::create();
	beginEditCP(MiniMapConstraints, BorderLayoutConstraints::RegionFieldMask);
		MiniMapConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
	endEditCP(MiniMapConstraints, BorderLayoutConstraints::RegionFieldMask);
	 
    beginEditCP(MiniMap, LayeredImageMiniMap::OverlaysFieldMask | LayeredImageMiniMap::PreferredSizeFieldMask | LayeredImageMiniMap::ViewPointIndicatorFieldMask | LayeredImageMiniMap::TransformationFieldMask | LayeredImageMiniMap::OpacityFieldMask | LayeredImageMiniMap::ConstraintsFieldMask | LayeredImageMiniMap::LockMapOrientationFieldMask | MiniMap::UnlockedMapSizeFieldMask | MiniMap::IndicatorsFieldMask);
	    MiniMap->setPreferredSize(Pnt2f(450,450));
	    MiniMap->setViewPointIndicator(ViewpointIndicator);
		MiniMap->setTransformation(WorldToMiniMapTransformation);
		MiniMap->setOpacity(.6);
		MiniMap->setConstraints(MiniMapConstraints);
		MiniMap->setLockMapOrientation(false);                  //If this is changed to true the map will then remain stationary and the indicator will then move and rotate
        MiniMap->setUnlockedMapSize(Vec2f(1000,1000));          //This item is only necassary when the map is set to Unlocked Orientation
		MiniMap->getIndicators().push_back(TorusIndicator);     //Link the Torus Indicator to the Mini Map
		MiniMap->getIndicators().push_back(SphereIndicator);    //Link the Sphere Indicator to the Mini Map
		MiniMap->getIndicators().push_back(BoxIndicator);       //Link the Box Indicator to the Mini Map
		MiniMap->getOverlays().push_back(DirectionalOverlay);
	endEditCP(MiniMap, LayeredImageMiniMap::OverlaysFieldMask | LayeredImageMiniMap::PreferredSizeFieldMask | LayeredImageMiniMap::ViewPointIndicatorFieldMask | LayeredImageMiniMap::TransformationFieldMask | LayeredImageMiniMap::OpacityFieldMask | LayeredImageMiniMap::ConstraintsFieldMask | LayeredImageMiniMap::LockMapOrientationFieldMask | MiniMap::UnlockedMapSizeFieldMask | MiniMap::IndicatorsFieldMask);

    //Set the images the map will use a layers of the scene.
    //The second arg in the method call is the space between that layer and the layer befor it
	MiniMap->insertLayer(Path("./level1.jpg").string().c_str(), .3);
    MiniMap->insertLayer(Path("./level2.jpg").string().c_str(), .3);
    MiniMap->insertLayer(Path("./level3.jpg").string().c_str(), .3);
    MiniMap->insertLayer(Path("./level4.jpg").string().c_str(), .3);
    MiniMap->insertLayer(Path("./level5.jpg").string().c_str(), .3);
    MiniMap->insertLayer(Path("./level6.jpg").string().c_str(), .3);
    MiniMap->insertLayer(Path("./level7.jpg").string().c_str(), .3);
    MiniMap->insertLayer(Path("./level8.jpg").string().c_str(), .3);
    MiniMap->insertLayer(Path("./level9.jpg").string().c_str(), .3);
    MiniMap->insertLayer(Path("./level10.jpg").string().c_str(), .3);

	 // Create the Graphics
    GraphicsPtr TutorialGraphics = osg::Graphics2D::create();

    // Initialize the LookAndFeelManager to enable default settings
    LookAndFeelManager::the()->getLookAndFeel()->init();
 
 
    // Create The Main InternalWindow
    // Create Background to be used with the Main InternalWindow
    ColorLayerPtr MainInternalWindowBackground = osg::ColorLayer::create();
    beginEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
        MainInternalWindowBackground->setColor(Color4f(1.0,1.0,1.0,0.5));
    endEditCP(MainInternalWindowBackground, ColorLayer::ColorFieldMask);
    InternalWindowPtr MainInternalWindow = osg::InternalWindow::create();
    LayoutPtr MainInternalWindowLayout = osg::BorderLayout::create();
	beginEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
	   MainInternalWindow->getChildren().push_back(MiniMap);
	   MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(1.0f,1.0f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.4f,0.4f));
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

    while(!ExitApp)
    {
        TutorialWindowEventProducer->update();
        TutorialWindowEventProducer->draw();
    }
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
