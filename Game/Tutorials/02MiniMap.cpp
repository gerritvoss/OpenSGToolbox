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

// GLUT is used for window handling
#include <OpenSG/OSGGLUT.h>

// Button Headers

#include <OpenSG/UserInterface/OSGButton.h>
#include <OpenSG/UserInterface/OSGToggleButton.h>
#include <OpenSG/UserInterface/OSGUIFont.h>
#include <OpenSG/UserInterface/OSGColorLayer.h>
#include <OpenSG/UserInterface/OSGFlowLayout.h>
#include <OpenSG/UserInterface/OSGPolygonUIDrawObject.h>
#include <OpenSG/UserInterface/OSGUIDrawObjectCanvas.h>

// MiniMap Headers
#include <OpenSG/Game/OSGLayeredImageMiniMap.h>


// Activate the OpenSG namespace
OSG_USING_NAMESPACE

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
		   Matrix NewTransform(BoxTransform->getMatrix());

		   NewTransform.mult(TranslateTransform);

		   beginEditCP(BoxTransform, Transform::MatrixFieldMask);
			   BoxTransform->setMatrix(NewTransform);
		   endEditCP(BoxTransform, Transform::MatrixFieldMask);
		}
		if(TheEventProducer->getKeyState(KeyEvent::KEY_RIGHT) == KeyEvent::KEY_STATE_DOWN)
	   {
		   Matrix TranslateTransform;
		   TranslateTransform.setTranslate(TranslateAmount*e.getElapsedTime(),0.0f,0.0f);
		   Matrix NewTransform(BoxTransform->getMatrix());

		   NewTransform.mult(TranslateTransform);

		   beginEditCP(BoxTransform, Transform::MatrixFieldMask);
			   BoxTransform->setMatrix(NewTransform);
		   endEditCP(BoxTransform, Transform::MatrixFieldMask);
	   }
		if(TheEventProducer->getKeyState(KeyEvent::KEY_UP) == KeyEvent::KEY_STATE_DOWN)
	   {
		   Matrix TranslateTransform;
		   TranslateTransform.setTranslate(0.0f,0.0f,-TranslateAmount*e.getElapsedTime());
		   Matrix NewTransform(BoxTransform->getMatrix());

		   NewTransform.mult(TranslateTransform);

		   beginEditCP(BoxTransform, Transform::MatrixFieldMask);
			   BoxTransform->setMatrix(NewTransform);
		   endEditCP(BoxTransform, Transform::MatrixFieldMask);
	   }
		if(TheEventProducer->getKeyState(KeyEvent::KEY_DOWN) == KeyEvent::KEY_STATE_DOWN)
	   {
		   Matrix TranslateTransform;
		   TranslateTransform.setTranslate(0.0f,0.0f,TranslateAmount*e.getElapsedTime());
		   Matrix NewTransform(BoxTransform->getMatrix());

		   NewTransform.mult(TranslateTransform);

		   beginEditCP(BoxTransform, Transform::MatrixFieldMask);
			   BoxTransform->setMatrix(NewTransform);
		   endEditCP(BoxTransform, Transform::MatrixFieldMask);
	   }
		if(TheEventProducer->getKeyState(KeyEvent::KEY_A) == KeyEvent::KEY_STATE_DOWN)
	   {
		   Matrix TranslateTransform;
		   //TranslateTransform.setTranslate(-TranslateAmount,0.0f,0.0f);
		   TranslateTransform.setRotate(Quaternion(Vec3f(0.0f,1.0f,0.0f), -RotateAmount*e.getElapsedTime()));
		   Matrix NewTransform(BoxTransform->getMatrix());

		   NewTransform.mult(TranslateTransform);

		   beginEditCP(BoxTransform, Transform::MatrixFieldMask);
			   BoxTransform->setMatrix(NewTransform);
		   endEditCP(BoxTransform, Transform::MatrixFieldMask);
	   }
		if(TheEventProducer->getKeyState(KeyEvent::KEY_D) == KeyEvent::KEY_STATE_DOWN)
	   {
		   Matrix TranslateTransform;
		   //TranslateTransform.setTranslate(TranslateAmount,0.0f,0.0f);
		   TranslateTransform.setRotate(Quaternion(Vec3f(0.0f,1.0f,0.0f), RotateAmount*e.getElapsedTime()));
		   Matrix NewTransform(BoxTransform->getMatrix());

		   NewTransform.mult(TranslateTransform);

		   beginEditCP(BoxTransform, Transform::MatrixFieldMask);
			   BoxTransform->setMatrix(NewTransform);
		   endEditCP(BoxTransform, Transform::MatrixFieldMask);
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
                                        "OpenSG 02MiniMap");
										
    // Make Torus Node (creates Torus in background of scene)
    NodePtr TorusGeometryNode = makeTorus(.5, 2, 16, 16);

    // Make Torus Node (creates Torus in background of scene)
    NodePtr BoxGeometryNode = makeBox(0.5,0.5,0.5,50,2,2);

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

	//Set the Box Transform Node
	BoxTransform = Transform::create();
	NodePtr BoxNode = Node::create();
    beginEditCP(BoxNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        BoxNode->setCore(BoxTransform);
        BoxNode->addChild(BoxGeometryNode);
        BoxNode->addChild(CameraBeaconNode);
    endEditCP(BoxNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

    // Make Main Scene Node and add the Torus
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
        scene->addChild(TorusGeometryNode);
        scene->addChild(BoxNode);
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

	mgr->setCamera(RubberCamera);

	LayeredImageMiniMapPtr MiniMap = osg::LayeredImageMiniMap::create();

	// Setup the size and other preferences to the minimap
	beginEditCP(MiniMap, LayeredImageMiniMap::PreferredSizeFieldMask);
	    MiniMap->setPreferredSize(Pnt2f(450,450));
	endEditCP(MiniMap, LayeredImageMiniMap::PreferredSizeFieldMask);

	MiniMap->insertImage(Path("./level1.jpg").string().c_str());
	MiniMap->setScale(10,10,100,100);					//Scale Must be before the setCharacterPosition call because it uses the scale set
	MiniMap->setOpacity(.4);
	MiniMap->setStartLocation(Pnt2f(450,450),0.5,0.5);
	MiniMap->setCharacterTexture(ImageFileHandler::the().read(Path("./Ship.JPG").string().c_str()));

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
    LayoutPtr MainInternalWindowLayout = osg::FlowLayout::create();
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
		MiniMap->setCharacterPosition(BoxGeometryNode->getToWorld());
		std::cout<<BoxGeometryNode->getToWorld()<<std::endl<<std::endl;
		std::cout<<MiniMap->getMapLocationPtr()<<std::endl;
		system("cls");
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
