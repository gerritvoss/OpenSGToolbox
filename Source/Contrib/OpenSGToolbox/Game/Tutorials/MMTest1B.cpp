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
#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGSolidBackground.h>
#include <OpenSG/Input/OSGWindowAdapter.h>
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/Toolbox/OSGCameraUtils.h>
#include <OpenSG/OSGImageForeground.h>
#include <OpenSG/OSGSimpleStatisticsForeground.h>


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
#include <OpenSG/UserInterface/OSGBorderLayout.h>
#include <OpenSG/UserInterface/OSGBorderLayoutConstraints.h>
#include <OpenSG/UserInterface/OSGPolygonUIDrawObject.h>
#include <OpenSG/UserInterface/OSGUIDrawObjectCanvas.h>
#include <OpenSG/UserInterface/OSGImageComponent.h>
#include <OpenSG/UserInterface/OSGLabel.h>
#include <OpenSG/UserInterface/OSGGridLayout.h>

// MiniMap Headers
#include <OpenSG/Game/OSGLayeredImageMiniMap.h>
#include <OpenSG/Game/OSGMiniMapIndicator.h>
#include <OpenSG/Game/OSGMiniMapMatrixTransformation.h>
#include <OpenSG/Game/OSGDefaultMiniMapIndicatorComponentGenerator.h>

#include <OpenSG/Game/OSGDirectionalIndicatorMiniMapOverlay.h>
#include <OpenSG/Game/OSGDefaultDirectionalIndicatorComponentGenerator.h>


#include <boost/lexical_cast.hpp>

#include <Windowsx.h>

// Activate the OpenSG namespace
OSG_USING_NAMESPACE

/*************************************************
Instead of using the built-in scene manager we need
to over ride that to fit our needs. Here is the 
necessary code to do so.
*************************************************/

//Current Checkpoint
enum Level {ABOVE, BELOW, LEVEL};
UInt32  CheckPointNum = 1;
LayeredImageMiniMapPtr TheMiniMap;

//Camera Beacon
TransformPtr CameraBeaconTransform;

//Viewpoint Indicator Location Information
ComponentTransformPtr ViewpointTransform;

//Centalized location marked with a Cell
TransformPtr CellTransform;

//Location of one of the example objects
TransformPtr CheckPoint1Transform;

//Location of the other example object
TransformPtr CheckPoint2Transform;
TransformPtr CheckPoint3Transform;

DirectionalIndicatorMiniMapOverlayPtr DirectionalOverlay;

RubberBandCameraPtr RubberCamera;

NodePtr CheckPoint3Node;


LabelPtr TimeTrackingInd1ValueLabel;
LabelPtr TimeTrackingInd2ValueLabel;
LabelPtr TimeTrackingInd3ValueLabel;
double TrackingTime(0.0);
bool hasMoved(false);

bool ExitApp = false;

Level CurLevel;
MiniMapIndicatorPtr CheckPoint1AboveIndicator;
MiniMapIndicatorPtr CheckPoint1BelowIndicator;
MiniMapIndicatorPtr CheckPoint1Indicator;

MiniMapIndicatorPtr CheckPoint2AboveIndicator;
MiniMapIndicatorPtr CheckPoint2BelowIndicator;
MiniMapIndicatorPtr CheckPoint2Indicator;

MiniMapIndicatorPtr CheckPoint3AboveIndicator;
MiniMapIndicatorPtr CheckPoint3BelowIndicator;
MiniMapIndicatorPtr CheckPoint3Indicator;

Pnt3f CameraPosition(-30.0f,85.0f,600.0f);
Quaternion CameraRotation;
Vec3f CameraVelocity(0.0,0.0,0.0);
Vec3f CameraAcceleration(0.0,0.0,0.0);
Real32 CameraMaxVelocity(150.0), CameraVelocityDamping(3.0);

NodePtr CellGeometryNode;
NodePtr CellNode;

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
    SimpleStatisticsForegroundPtr RenderStatForeground;
    

    bool _IsUpKeyDown;
    bool _IsDownKeyDown;
    bool _IsLeftKeyDown;
    bool _IsRightKeyDown;
    
    bool _IsAKeyDown;
    bool _IsSKeyDown;
    bool _IsDKeyDown;
    bool _IsWKeyDown;
public:
	SceneManager() : 
		_win(NullFC),
		_root(NullFC),
		_internalRoot(NullFC),
		_headlight(NullFC),
		_action(NULL),
		_ownAction(NULL),
		_cart(NullFC),
		_camera(NullFC),

        _IsUpKeyDown(false),
        _IsDownKeyDown(false),
        _IsLeftKeyDown(false),
        _IsRightKeyDown(false),
        _IsAKeyDown(false),
        _IsSKeyDown(false),
        _IsDKeyDown(false),
        _IsWKeyDown(false)
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
        
        RenderStatForeground = SimpleStatisticsForeground::create();
        beginEditCP(RenderStatForeground);
            RenderStatForeground->setSize(25);
            RenderStatForeground->setVerticalAlign(SimpleStatisticsForeground::Bottom);
            RenderStatForeground->setColor(Color4f(0,1,0,0.7));
            RenderStatForeground->addElement(RenderAction::statDrawTime, "Draw FPS: %r.3f");
            RenderStatForeground->addElement(RenderAction::statNGeometries, "%d Nodes drawn");
            RenderStatForeground->addElement(DrawActionBase::statTravTime, "TravTime: %.3f s");
            RenderStatForeground->addElement(RenderAction::statDrawTime, "DrawTime: %.3f s");
            RenderStatForeground->addElement(DrawActionBase::statCullTestedNodes, "%d Nodes culltested");
            RenderStatForeground->addElement(DrawActionBase::statCulledNodes, "%d Nodes culled");
            RenderStatForeground->addElement(RenderAction::statNMaterials, "%d material changes");
            RenderStatForeground->addElement(RenderAction::statNMatrices, "%d matrix changes");
            RenderStatForeground->addElement(RenderAction::statNGeometries, "%d Nodes drawn");
            RenderStatForeground->addElement(RenderAction::statNTransGeometries, "%d transparent Nodes drawn");
            RenderStatForeground->addElement(Drawable::statNTriangles, "%d triangles drawn");
            RenderStatForeground->addElement(Drawable::statNLines, "%d lines drawn");
            RenderStatForeground->addElement(Drawable::statNPoints, "%d points drawn");
            RenderStatForeground->addElement(Drawable::statNPrimitives,"%d primitive groups drawn");
            RenderStatForeground->addElement(Drawable::statNVertices, "%d vertices transformed");
            RenderStatForeground->addElement(Drawable::statNGeoBytes, "%d bytes of geometry used");
            RenderStatForeground->addElement(RenderAction::statNTextures, "%d textures used");
            RenderStatForeground->addElement(RenderAction::statNTexBytes, "%d bytes of texture used");
        endEditCP(RenderStatForeground);

        _action->setStatistics(&RenderStatForeground->getCollector());

	}
   void keyPressed(const KeyEventPtr e)
   {
       if(e->getKey() == KeyEvent::KEY_Q && e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
       {
           ExitApp = true;
       }

	   switch(e->getKey())
	   {
	   case KeyEvent::KEY_UP:
           _IsUpKeyDown = true;
		   break;
	   case KeyEvent::KEY_DOWN:
           _IsDownKeyDown = true;
		   break;
	   case KeyEvent::KEY_LEFT:
           _IsLeftKeyDown = true;
		   break;
	   case KeyEvent::KEY_RIGHT:
           _IsRightKeyDown = true;
		   break;
	   case KeyEvent::KEY_A:
           _IsAKeyDown = true;
		   break;
	   case KeyEvent::KEY_S:
           _IsSKeyDown = true;
		   break;
	   case KeyEvent::KEY_D:
           _IsDKeyDown = true;
		   break;
	   case KeyEvent::KEY_W:
           _IsWKeyDown = true;
		   break;
	   default:
		   break;
	   }
   }

   void keyReleased(const KeyEventPtr e)
   {
	   switch(e->getKey())
	   {
	   case KeyEvent::KEY_UP:
           _IsUpKeyDown = false;
		   break;
	   case KeyEvent::KEY_DOWN:
           _IsDownKeyDown = false;
		   break;
	   case KeyEvent::KEY_LEFT:
           _IsLeftKeyDown = false;
		   break;
	   case KeyEvent::KEY_RIGHT:
           _IsRightKeyDown = false;
		   break;
	   case KeyEvent::KEY_A:
           _IsAKeyDown = false;
		   break;
	   case KeyEvent::KEY_S:
           _IsSKeyDown = false;
		   break;
	   case KeyEvent::KEY_D:
           _IsDKeyDown = false;
		   break;
	   case KeyEvent::KEY_W:
           _IsWKeyDown = false;
		   break;
	   case KeyEvent::KEY_0:
            beginEditCP(_win->getPort(0), Viewport::ForegroundsFieldMask);
                if(_win->getPort(0)->getForegrounds().find(RenderStatForeground) == _win->getPort(0)->getForegrounds().end())
                {
                    _win->getPort(0)->getForegrounds().push_back(RenderStatForeground);
                }
                else
                {
                    _win->getPort(0)->getForegrounds().erase(_win->getPort(0)->getForegrounds().find(RenderStatForeground));
                }
            endEditCP(_win->getPort(0), Viewport::ForegroundsFieldMask);
		   break;
	   default:
		   break;
	   }
   }

    void update(const UpdateEventPtr e)
	{
		RubberCamera->update(e->getElapsedTime());

        Matrix IndicatorMat;

        if(hasMoved)
        {
            TrackingTime += e->getElapsedTime();
        }
        switch(CheckPointNum)
        {
        case 1:
            IndicatorMat = CheckPoint1Transform->getMatrix();
            beginEditCP(TimeTrackingInd1ValueLabel, Label::TextFieldMask);
                TimeTrackingInd1ValueLabel->setText(boost::lexical_cast<std::string>(TrackingTime));
            endEditCP(TimeTrackingInd1ValueLabel, Label::TextFieldMask);
            break;
        case 2:
            beginEditCP(TimeTrackingInd2ValueLabel, Label::TextFieldMask);
                TimeTrackingInd2ValueLabel->setText(boost::lexical_cast<std::string>(TrackingTime));
            endEditCP(TimeTrackingInd2ValueLabel, Label::TextFieldMask);
            IndicatorMat = CheckPoint2Transform->getMatrix();
            break;
        case 3:
            beginEditCP(TimeTrackingInd3ValueLabel, Label::TextFieldMask);
                TimeTrackingInd3ValueLabel->setText(boost::lexical_cast<std::string>(TrackingTime));
            endEditCP(TimeTrackingInd3ValueLabel, Label::TextFieldMask);
            IndicatorMat = CheckPoint3Transform->getMatrix();
            break;
        }
        Matrix ViewPointMat = ViewpointTransform->getMatrix();

        Vec3f IndictorPosition, ViewpointPosition, DummyVec;
        Quaternion DummyQuat;

        IndicatorMat.getTransform(IndictorPosition, DummyQuat, DummyVec, DummyQuat);
        ViewPointMat.getTransform(ViewpointPosition, DummyQuat, DummyVec, DummyQuat);

        Vec3f Delta = IndictorPosition - ViewpointPosition;
        Real32 Distance = Delta.length();

        Real32 YDelta = IndictorPosition.y() - ViewpointPosition.y();
        bool updateIndicator(false);
        if(osgabs(YDelta) > 10.0)
        {
            if(YDelta < 0.0)
            {
                if(CurLevel != ABOVE)
                {
                    updateIndicator = true;
                }
                CurLevel = ABOVE;
            }
            else
            {
                if(CurLevel != BELOW)
                {
                    updateIndicator = true;
                }
                CurLevel = BELOW;
            }
        }
        else
        {
            if(CurLevel != LEVEL)
            {
                updateIndicator = true;
            }
            CurLevel = LEVEL;
        }

        if(Distance < 2)
        {
            /*if(TheMiniMap != NullFC)
            {
                beginEditCP(TheMiniMap, MiniMap::IndicatorsFieldMask);
                beginEditCP(TheMiniMap, MiniMap::IndicatorsFieldMask);
            }
            beginEditCP(DirectionalOverlay, DirectionalIndicatorMiniMapOverlay::IndicatorsFieldMask);
	            DirectionalOverlay->getIndicators().clear();
            endEditCP(DirectionalOverlay, DirectionalIndicatorMiniMapOverlay::IndicatorsFieldMask);*/
        
            ++CheckPointNum;
            if(CheckPointNum == 2)
            {
                TrackingTime = 0.0;
                beginEditCP(DirectionalOverlay, DirectionalIndicatorMiniMapOverlay::IndicatorsFieldMask);
	            DirectionalOverlay->getIndicators().clear();
		            DirectionalOverlay->getIndicators().push_back(CheckPoint2Indicator);       //Link the Box Indicator to the Mini Map
	            endEditCP(DirectionalOverlay, DirectionalIndicatorMiniMapOverlay::IndicatorsFieldMask);

                if(TheMiniMap != NullFC)
                {
                    beginEditCP(TheMiniMap, MiniMap::IndicatorsFieldMask);
                    TheMiniMap->getIndicators().clear();
                        TheMiniMap->getIndicators().push_back(CheckPoint2Indicator);
                    endEditCP(TheMiniMap, MiniMap::IndicatorsFieldMask);
                }
            }
            if(CheckPointNum == 3)
            {
                TrackingTime = 0.0;
                beginEditCP(DirectionalOverlay, DirectionalIndicatorMiniMapOverlay::IndicatorsFieldMask);
	            DirectionalOverlay->getIndicators().clear();
		            DirectionalOverlay->getIndicators().push_back(CheckPoint3Indicator);       //Link the Box Indicator to the Mini Map
	            endEditCP(DirectionalOverlay, DirectionalIndicatorMiniMapOverlay::IndicatorsFieldMask);
                if(TheMiniMap != NullFC)
                {
                    beginEditCP(TheMiniMap, MiniMap::IndicatorsFieldMask);
                    TheMiniMap->getIndicators().clear();
                        TheMiniMap->getIndicators().push_back(CheckPoint3Indicator);
                    endEditCP(TheMiniMap, MiniMap::IndicatorsFieldMask);
                }
            }
        }
        else if(updateIndicator)
        {
            MiniMapIndicatorPtr TheIndicator;
            switch(CheckPointNum)
            {
            case 1:
                switch(CurLevel)
                {
                case ABOVE:
                    TheIndicator = CheckPoint1AboveIndicator;
                    break;
                case BELOW:
                    TheIndicator = CheckPoint1BelowIndicator;
                    break;
                case LEVEL:
                    TheIndicator = CheckPoint1Indicator;
                    break;
                }
                beginEditCP(DirectionalOverlay, DirectionalIndicatorMiniMapOverlay::IndicatorsFieldMask);
	                DirectionalOverlay->getIndicators().clear();
		            DirectionalOverlay->getIndicators().push_back(TheIndicator);       //Link the Box Indicator to the Mini Map
	            endEditCP(DirectionalOverlay, DirectionalIndicatorMiniMapOverlay::IndicatorsFieldMask);

                if(TheMiniMap != NullFC)
                {
                    beginEditCP(TheMiniMap, MiniMap::IndicatorsFieldMask);
                    TheMiniMap->getIndicators().clear();
                        TheMiniMap->getIndicators().push_back(TheIndicator);
                    endEditCP(TheMiniMap, MiniMap::IndicatorsFieldMask);
                }
                
                break;
            case 2:
                switch(CurLevel)
                {
                case ABOVE:
                    TheIndicator = CheckPoint2AboveIndicator;
                    break;
                case BELOW:
                    TheIndicator = CheckPoint2BelowIndicator;
                    break;
                case LEVEL:
                    TheIndicator = CheckPoint2Indicator;
                    break;
                }
                beginEditCP(DirectionalOverlay, DirectionalIndicatorMiniMapOverlay::IndicatorsFieldMask);
	                DirectionalOverlay->getIndicators().clear();
		            DirectionalOverlay->getIndicators().push_back(TheIndicator);       //Link the Box Indicator to the Mini Map
	            endEditCP(DirectionalOverlay, DirectionalIndicatorMiniMapOverlay::IndicatorsFieldMask);

                if(TheMiniMap != NullFC)
                {
                    beginEditCP(TheMiniMap, MiniMap::IndicatorsFieldMask);
                    TheMiniMap->getIndicators().clear();
                        TheMiniMap->getIndicators().push_back(TheIndicator);
                    endEditCP(TheMiniMap, MiniMap::IndicatorsFieldMask);
                }
                break;
            case 3:
                switch(CurLevel)
                {
                case ABOVE:
                    TheIndicator = CheckPoint3AboveIndicator;
                    break;
                case BELOW:
                    TheIndicator = CheckPoint3BelowIndicator;
                    break;
                case LEVEL:
                    TheIndicator = CheckPoint3Indicator;
                    break;
                }
                beginEditCP(DirectionalOverlay, DirectionalIndicatorMiniMapOverlay::IndicatorsFieldMask);
	                DirectionalOverlay->getIndicators().clear();
		            DirectionalOverlay->getIndicators().push_back(TheIndicator);       //Link the Box Indicator to the Mini Map
	            endEditCP(DirectionalOverlay, DirectionalIndicatorMiniMapOverlay::IndicatorsFieldMask);

                if(TheMiniMap != NullFC)
                {
                    beginEditCP(TheMiniMap, MiniMap::IndicatorsFieldMask);
                    TheMiniMap->getIndicators().clear();
                        TheMiniMap->getIndicators().push_back(TheIndicator);
                    endEditCP(TheMiniMap, MiniMap::IndicatorsFieldMask);
                }
                break;
            }
        }

        


        bool updateTransform(false);
	   float ForwardAcceleration(175.0f);
	   float SideAcceleration(75.0f);
	   float UpwardAcceleration(75.0f);
	   float RotateAmount(1.0f);
        CameraAcceleration.setValues(0.0,0.0,0.0);
		WindowEventProducerPtr TheEventProducer(WindowEventProducerPtr::dcast(e->getSource()));
		if(_IsLeftKeyDown)
		{
		   CameraAcceleration = CameraAcceleration +Vec3f(-SideAcceleration,0.0f,0.0f);
           hasMoved = true;
		}
		if(_IsRightKeyDown)
	   {
		   CameraAcceleration = CameraAcceleration +Vec3f(SideAcceleration,0.0f,0.0f);
           hasMoved = true;
	   }
		if(_IsUpKeyDown)
	   {
		   CameraAcceleration = CameraAcceleration +Vec3f(0.0f,0.0f,-ForwardAcceleration);
           hasMoved = true;
	   }
		if(_IsDownKeyDown)
	   {
		   CameraAcceleration = CameraAcceleration +Vec3f(0.0f,0.0f,ForwardAcceleration);
           hasMoved = true;
	   }
		if(_IsAKeyDown)
	   {
           CameraRotation.mult(Quaternion(Vec3f(0.0f,1.0f,0.0f), RotateAmount*e->getElapsedTime()));
            updateTransform = true;
	   }
		if(_IsDKeyDown)
	   {
           CameraRotation.mult(Quaternion(Vec3f(0.0f,1.0f,0.0f), -RotateAmount*e->getElapsedTime()));
            updateTransform = true;
	   }
        if(_IsWKeyDown)
	   {
		   CameraAcceleration = CameraAcceleration +Vec3f(0.0f,UpwardAcceleration,0.0f);
           hasMoved = true;
	   }
         if(_IsSKeyDown)
	   {
		   CameraAcceleration = CameraAcceleration +Vec3f(0.0f,-UpwardAcceleration,0.0f);
           hasMoved = true;
	   }
        //Update Camera Position
        if(CameraVelocity != Vec3f(0.0,0.0,0.0) || CameraAcceleration != Vec3f(0.0,0.0,0.0))
        {
            ViewpointTransform->getMatrix().multMatrixVec(CameraAcceleration, CameraAcceleration);
            CameraAcceleration += (CameraVelocityDamping * -CameraVelocity);

			//checkCameraIntersection(static_cast<Real32>(e->getElapsedTime())*CameraVelocity+ static_cast<Real32>(0.5*e->getElapsedTime()*e->getElapsedTime())*CameraAcceleration, e->getElapsedTime());
			
			CameraPosition = CameraPosition + static_cast<Real32>(e->getElapsedTime())*CameraVelocity+ static_cast<Real32>(0.5*e->getElapsedTime()*e->getElapsedTime())*CameraAcceleration;
            CameraVelocity = CameraVelocity + static_cast<Real32>(e->getElapsedTime())*CameraAcceleration;
            if(CameraVelocity.length() > CameraMaxVelocity)
            {
                CameraVelocity.normalize();
                CameraVelocity = CameraMaxVelocity * CameraVelocity;
            }
            updateTransform = true;
        }
        if(updateTransform)
        {

            beginEditCP(ViewpointTransform, ComponentTransform::RotationFieldMask | ComponentTransform::TranslationFieldMask);
               ViewpointTransform->setRotation(CameraRotation);
               ViewpointTransform->setTranslation(CameraPosition);
            endEditCP(ViewpointTransform, ComponentTransform::RotationFieldMask | ComponentTransform::TranslationFieldMask);
        }
	}

	virtual void checkCameraIntersection(const Vec3f& Trans, Real32 t)
	{
	   Matrix TranslateTransform;
	   TranslateTransform.setTranslate(Trans.x(),Trans.y(),Trans.z());
	   Matrix NewTransform(ViewpointTransform->getMatrix());
	   Vec3f Translation, Scale;
	   Quaternion temp;
	   NewTransform.getTransform(Translation,temp, Scale, temp);



		Line ray;
		ray.setValue(CameraPosition, CameraPosition + Trans);
		IntersectAction *iAct = IntersectAction::create();
		iAct->setLine(ray);
		iAct->apply(CellNode);
	    
		if (iAct->didHit() && iAct->getHitT() >= 0.0f && iAct->getHitT()*iAct->getHitT() <= Trans.squareLength ())
		{
			//Move up to the hit point
			Vec3f TransDir = Trans;
			TransDir.normalize();
			CameraPosition = iAct->getHitPoint() + 0.001f*iAct->getHitNormal();

			//Get the new velocity
			//Get the time left
			/*Real32 remaining_t(t * (1.0-iAct->getHitT()));
			Vec3f Up_axis = Trans.cross(iAct->getHitNormal());
			Vec3f Slide1 = Up_axis.cross(iAct->getHitNormal());
			Slide1.normalize();
			Vec3f Slide2 = Trans;
			Slide2.projectTo(Slide1);
			
			CameraPosition = CameraPosition + remaining_t*Slide2;*/
				
				CameraVelocity.setValues(0.0,0.0,0.0);
				CameraAcceleration.setValues(0.0,0.0,0.0);
		}
		else
		{
			CameraPosition = CameraPosition + t*CameraVelocity+ static_cast<Real32>(0.5)*t*t*CameraAcceleration;
            CameraVelocity = CameraVelocity + t*CameraAcceleration;
            if(CameraVelocity.length() > CameraMaxVelocity)
            {
                CameraVelocity.normalize();
                CameraVelocity = CameraMaxVelocity * CameraVelocity;
            }
		}
	}

};
// The SimpleSceneManager to manage simple applications
SceneManager *mgr;

// Forward declaration so we can have the interesting stuff upfront
void display(void);
void reshape(Vec2f Size);

// Create a class to allow for the use of the Ctrl+q
class TutorialKeyListener : public KeyListener
{
public:

   virtual void keyPressed(const KeyEventPtr e)
   {
       mgr->keyPressed(e);
   }

   virtual void keyReleased(const KeyEventPtr e)
   {
       mgr->keyReleased(e);
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
        mgr->update(e);
	}
};

class TutorialWindowListener : public WindowAdapter
{
public:
    virtual void windowClosing(const WindowEventPtr e)
    {
        ExitApp = true;
    }

    virtual void windowClosed(const WindowEventPtr e)
    {
        ExitApp = true;
    }
};

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
    // OSG init
    osgInit(0,NULL);

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
                                        Vec2f(1024,800),
                                        "MataBlast Unlocked MiniMap Test");
										
    // Make Cell Node (creates Cell in background of scene)
    
    
    CellGeometryNode = SceneFileHandler::the().read("Data/Cell.osb");
    if(CellGeometryNode == NullFC)
    {
        CellGeometryNode = Node::create();
        beginEditCP(CellGeometryNode, Node::CoreFieldMask);
        CellGeometryNode->setCore(Group::create());
        endEditCP(CellGeometryNode, Node::CoreFieldMask);
    }

	Matrix CellTransMatrix;
	CellTransMatrix.setTransform(Vec3f(-1060.0,140.0,75.0)); //CellPosition
	CellTransform = Transform::create();
    beginEditCP(CellTransform, Transform::MatrixFieldMask);
		CellTransform->setMatrix(CellTransMatrix);
    endEditCP(CellTransform, Transform::MatrixFieldMask);

	CellNode = Node::create();
    beginEditCP(CellNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        CellNode->setCore(CellTransform);
        CellNode->addChild(CellGeometryNode);
    endEditCP(CellNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
	
    // Make Checkpoint #1 Node
    NodePtr SphereGeometryNode = makeSphere(1,2.0);

	Matrix SphereTransMatrix;
	SphereTransMatrix.setTransform(Vec3f(-30.0f,85.0f,-625.0f));
	CheckPoint1Transform = Transform::create();
    beginEditCP(CheckPoint1Transform, Transform::MatrixFieldMask);
		CheckPoint1Transform->setMatrix(SphereTransMatrix);
    endEditCP(CheckPoint1Transform, Transform::MatrixFieldMask);

	NodePtr SphereNode = Node::create();
    beginEditCP(SphereNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        SphereNode->setCore(CheckPoint1Transform);
        SphereNode->addChild(SphereGeometryNode);
    endEditCP(SphereNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
	
    // Make Player Node
    //NodePtr PlayerNode = makeBox(0.5,0.5,0.5,2,2,2);//makeCylinder(1.0,0.25,2,true,true,true);
    NodePtr PlayerNode = Node::create();
    beginEditCP(PlayerNode, Node::CoreFieldMask);
    PlayerNode->setCore(Group::create());
    endEditCP(PlayerNode, Node::CoreFieldMask);

    // Make Checkpoint #2 Node
    NodePtr BoxGeometryNode = makeSphere(1,2.0);

	Matrix BoxTransMatrix;
	BoxTransMatrix.setTransform(Vec3f(-350.0f,155.0f,0.0f));
	CheckPoint2Transform = Transform::create();
    beginEditCP(CheckPoint2Transform, Transform::MatrixFieldMask);
		CheckPoint2Transform->setMatrix(BoxTransMatrix);
    endEditCP(CheckPoint2Transform, Transform::MatrixFieldMask);

	NodePtr BoxNode = Node::create();
    beginEditCP(BoxNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        BoxNode->setCore(CheckPoint2Transform);
        BoxNode->addChild(BoxGeometryNode);
    endEditCP(BoxNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

    // Make Checkpoint #3 Node
    NodePtr CheckPoint3GeometryNode = makeSphere(1,2.0);

	Matrix CheckPoint3TransMatrix;
	CheckPoint3TransMatrix.setTransform(Vec3f(0.0f,85.0f,600.0f));
	CheckPoint3Transform = Transform::create();
    beginEditCP(CheckPoint3Transform, Transform::MatrixFieldMask);
		CheckPoint3Transform->setMatrix(CheckPoint3TransMatrix);
    endEditCP(CheckPoint3Transform, Transform::MatrixFieldMask);

	CheckPoint3Node = Node::create();
    beginEditCP(CheckPoint3Node, Node::CoreFieldMask | Node::ChildrenFieldMask);
        CheckPoint3Node->setCore(CheckPoint3Transform);
        CheckPoint3Node->addChild(CheckPoint3GeometryNode);
    endEditCP(CheckPoint3Node, Node::CoreFieldMask | Node::ChildrenFieldMask);

	//Set the Camera Beacon Node
	Matrix Offset;
	//Offset.setTranslate(0.0f,2.5f,6.0f);
	Offset.setTranslate(0.0f,0.0,0.0f);
	CameraBeaconTransform = Transform::create();
    beginEditCP(CameraBeaconTransform, Transform::MatrixFieldMask);
        CameraBeaconTransform->setMatrix(Offset);
    endEditCP(CameraBeaconTransform, Transform::MatrixFieldMask);

	NodePtr CameraBeaconNode = Node::create();
    beginEditCP(CameraBeaconNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        CameraBeaconNode->setCore(CameraBeaconTransform);
    endEditCP(CameraBeaconNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

	//Set the Viewpoint Transform Node
	ViewpointTransform = ComponentTransform::create();
	NodePtr ViewpointGeomtryNode = Node::create();

    beginEditCP(ViewpointTransform, ComponentTransform::RotationFieldMask | ComponentTransform::TranslationFieldMask);
       ViewpointTransform->setRotation(CameraRotation);
       ViewpointTransform->setTranslation(CameraPosition);
    endEditCP(ViewpointTransform, ComponentTransform::RotationFieldMask | ComponentTransform::TranslationFieldMask);

    beginEditCP(ViewpointGeomtryNode, Node::CoreFieldMask | Node::ChildrenFieldMask);
        ViewpointGeomtryNode->setCore(ViewpointTransform);
        ViewpointGeomtryNode->addChild(PlayerNode);
        ViewpointGeomtryNode->addChild(CameraBeaconNode);
    endEditCP(ViewpointGeomtryNode, Node::CoreFieldMask | Node::ChildrenFieldMask);

    // Make Main Scene Node and add the Cell
    NodePtr scene = osg::Node::create();
    beginEditCP(scene, Node::CoreFieldMask | Node::ChildrenFieldMask);
        scene->setCore(osg::Group::create());
        scene->addChild(CellNode);
        scene->addChild(SphereNode);
        scene->addChild(BoxNode);
        scene->addChild(CheckPoint3Node);
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
	Vec3f PositionCoefficients(10000000.1,10.5,10.5);
	Vec3f OrientationCoefficients(1000000.1,20.5,20.5);

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
	TheMiniMap = osg::LayeredImageMiniMap::create();

	//World to MiniMap Transformation
	MiniMapMatrixTransformationPtr WorldToMiniMapTransformation = MiniMapMatrixTransformation::create();
	Matrix Transform;
	Transform.setTransform(Vec3f(0.5,0.5,0.0f), Quaternion(Vec3f(1.0f,0.0f,0.0f),deg2rad(-90.0)), Vec3f(0.00043, 1.0, 0.00061)); //MapScale
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
	ImagePtr ShipImage = ImageFileHandler::the().read(Path("./Data/Ship.PNG").string().c_str());
	ViewPointComponentPrototype->setImage(ShipImage);
	ViewPointComponentPrototype->setRolloverImage(ShipImage);
	ViewPointComponentPrototype->setDisabledImage(ShipImage);
	ViewPointComponentPrototype->setFocusedImage(ShipImage);

	//Create the Viewpoint Component Generator
	DefaultMiniMapIndicatorComponentGeneratorPtr ShipComponentGenerator = DefaultMiniMapIndicatorComponentGenerator::create();
	beginEditCP(ShipComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);
		ShipComponentGenerator->setComponentPrototype(ViewPointComponentPrototype);
	endEditCP(ShipComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);

	//Create the Cell Node Indicator Prototype
	ImageComponentPtr CellNodeComponentPrototype = ImageComponent::create();
	beginEditCP(CellNodeComponentPrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
		CellNodeComponentPrototype->setPreferredSize(Vec2f(20.0f,20.0f));
		CellNodeComponentPrototype->setScale(ImageComponent::SCALE_MIN_AXIS);
		CellNodeComponentPrototype->setAlignment(Vec2f(0.5f,0.5f));
	endEditCP(CellNodeComponentPrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
	ImagePtr CellImage = ImageFileHandler::the().read(Path("./Data/CellNode.jpg").string().c_str());
	CellNodeComponentPrototype->setImage(CellImage);
	CellNodeComponentPrototype->setRolloverImage(CellImage);
	CellNodeComponentPrototype->setDisabledImage(CellImage);
	CellNodeComponentPrototype->setFocusedImage(CellImage);

	//Create the Cell Component Generator
	DefaultMiniMapIndicatorComponentGeneratorPtr CellComponentGenerator = DefaultMiniMapIndicatorComponentGenerator::create();
	beginEditCP(CellComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);
		CellComponentGenerator->setComponentPrototype(CellNodeComponentPrototype);
	endEditCP(CellComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);
	
	//Create the Sphere Node Indicator Prototype
	ImageComponentPtr SphereNodeComponentPrototype = ImageComponent::create();
	beginEditCP(SphereNodeComponentPrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
		SphereNodeComponentPrototype->setPreferredSize(Vec2f(20.0f,20.0f));
		SphereNodeComponentPrototype->setScale(ImageComponent::SCALE_MIN_AXIS);
		SphereNodeComponentPrototype->setAlignment(Vec2f(0.5f,0.5f));
	endEditCP(SphereNodeComponentPrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
	//ImagePtr SphereImage = ImageFileHandler::the().read(Path("./SameLevelIndicate.PNG").string().c_str());
	

	//Create the Sphere Component Generator
	DefaultMiniMapIndicatorComponentGeneratorPtr SphereComponentGenerator = DefaultMiniMapIndicatorComponentGenerator::create();
	beginEditCP(SphereComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);
		SphereComponentGenerator->setComponentPrototype(SphereNodeComponentPrototype);
	endEditCP(SphereComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);
	
	//Create the Box Node Indicator Prototype
	ImageComponentPtr CheckPointOneNodeComponentPrototype = ImageComponent::create();
	beginEditCP(CheckPointOneNodeComponentPrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
		CheckPointOneNodeComponentPrototype->setPreferredSize(Vec2f(20.0f,20.0f));
		CheckPointOneNodeComponentPrototype->setScale(ImageComponent::SCALE_MIN_AXIS);
		CheckPointOneNodeComponentPrototype->setAlignment(Vec2f(0.5f,0.5f));
	endEditCP(CheckPointOneNodeComponentPrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
	
    ImagePtr SameImage = ImageFileHandler::the().read(Path("./Data/SameLevelIndicate.PNG").string().c_str());
    ImagePtr DownImage = ImageFileHandler::the().read(Path("./Data/DownLevelIndicate.PNG").string().c_str());
    ImagePtr UpImage = ImageFileHandler::the().read(Path("./Data/UpLevelIndicate.PNG").string().c_str());
	CheckPointOneNodeComponentPrototype->setImage(SameImage);
    CheckPointOneNodeComponentPrototype->setRolloverImage(SameImage);
    CheckPointOneNodeComponentPrototype->setDisabledImage(SameImage);
    CheckPointOneNodeComponentPrototype->setFocusedImage(SameImage);

    SphereNodeComponentPrototype->setImage(SameImage);
    SphereNodeComponentPrototype->setRolloverImage(SameImage);
    SphereNodeComponentPrototype->setDisabledImage(SameImage);
    SphereNodeComponentPrototype->setFocusedImage(SameImage);
    
    //Above
	ImageComponentPtr AboveComponentPrototype = ImageComponent::create();
	beginEditCP(AboveComponentPrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
		AboveComponentPrototype->setPreferredSize(Vec2f(20.0f,20.0f));
		AboveComponentPrototype->setScale(ImageComponent::SCALE_MIN_AXIS);
		AboveComponentPrototype->setAlignment(Vec2f(0.5f,0.5f));
	endEditCP(AboveComponentPrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
	AboveComponentPrototype->setImage(DownImage);
    AboveComponentPrototype->setRolloverImage(DownImage);
    AboveComponentPrototype->setDisabledImage(DownImage);
    AboveComponentPrototype->setFocusedImage(DownImage);

	DefaultMiniMapIndicatorComponentGeneratorPtr AboveComponentGenerator = DefaultMiniMapIndicatorComponentGenerator::create();
	beginEditCP(AboveComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);
		AboveComponentGenerator->setComponentPrototype(AboveComponentPrototype);
	endEditCP(AboveComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);
    
    //Below
	ImageComponentPtr BelowComponentPrototype = ImageComponent::create();
	beginEditCP(BelowComponentPrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
		BelowComponentPrototype->setPreferredSize(Vec2f(20.0f,20.0f));
		BelowComponentPrototype->setScale(ImageComponent::SCALE_MIN_AXIS);
		BelowComponentPrototype->setAlignment(Vec2f(0.5f,0.5f));
	endEditCP(BelowComponentPrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
	BelowComponentPrototype->setImage(UpImage);
    BelowComponentPrototype->setRolloverImage(UpImage);
    BelowComponentPrototype->setDisabledImage(UpImage);
    BelowComponentPrototype->setFocusedImage(UpImage);

	DefaultMiniMapIndicatorComponentGeneratorPtr BelowComponentGenerator = DefaultMiniMapIndicatorComponentGenerator::create();
	beginEditCP(BelowComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);
		BelowComponentGenerator->setComponentPrototype(BelowComponentPrototype);
	endEditCP(BelowComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);


	//Create the Box Component Generator
	DefaultMiniMapIndicatorComponentGeneratorPtr BoxComponentGenerator = DefaultMiniMapIndicatorComponentGenerator::create();
	beginEditCP(BoxComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);
		BoxComponentGenerator->setComponentPrototype(CheckPointOneNodeComponentPrototype);
	endEditCP(BoxComponentGenerator, DefaultMiniMapIndicatorComponentGenerator::ComponentPrototypeFieldMask);

	//Create the Viewpoint Indicator
	MiniMapIndicatorPtr ViewpointIndicator = MiniMapIndicator::create();

	beginEditCP(ViewpointIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
		ViewpointIndicator->setGenerator(ShipComponentGenerator);
		ViewpointIndicator->setLocation(ViewpointGeomtryNode);
	endEditCP(ViewpointIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);

	//Other Indicators
	MiniMapIndicatorPtr CellIndicator = MiniMapIndicator::create();
	beginEditCP(CellIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
		CellIndicator->setGenerator(CellComponentGenerator);
		CellIndicator->setLocation(CellGeometryNode);
	endEditCP(CellIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
	
	CheckPoint1Indicator = MiniMapIndicator::create();
	beginEditCP(CheckPoint1Indicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
		CheckPoint1Indicator->setGenerator(SphereComponentGenerator);
		CheckPoint1Indicator->setLocation(SphereGeometryNode);
	endEditCP(CheckPoint1Indicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);

	CheckPoint1AboveIndicator = MiniMapIndicator::create();
	beginEditCP(CheckPoint1AboveIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
		CheckPoint1AboveIndicator->setGenerator(AboveComponentGenerator);
		CheckPoint1AboveIndicator->setLocation(SphereGeometryNode);
	endEditCP(CheckPoint1AboveIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);

	CheckPoint1BelowIndicator = MiniMapIndicator::create();
	beginEditCP(CheckPoint1BelowIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
		CheckPoint1BelowIndicator->setGenerator(BelowComponentGenerator);
		CheckPoint1BelowIndicator->setLocation(SphereGeometryNode);
	endEditCP(CheckPoint1BelowIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
	
	CheckPoint2Indicator = MiniMapIndicator::create();
	beginEditCP(CheckPoint2Indicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
		CheckPoint2Indicator->setGenerator(BoxComponentGenerator);
		CheckPoint2Indicator->setLocation(BoxGeometryNode);
	endEditCP(CheckPoint2Indicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);

	CheckPoint2AboveIndicator = MiniMapIndicator::create();
	beginEditCP(CheckPoint2AboveIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
		CheckPoint2AboveIndicator->setGenerator(AboveComponentGenerator);
		CheckPoint2AboveIndicator->setLocation(BoxGeometryNode);
	endEditCP(CheckPoint2AboveIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);

	CheckPoint2BelowIndicator = MiniMapIndicator::create();
	beginEditCP(CheckPoint2BelowIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
		CheckPoint2BelowIndicator->setGenerator(BelowComponentGenerator);
		CheckPoint2BelowIndicator->setLocation(BoxGeometryNode);
	endEditCP(CheckPoint2BelowIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
	

    CheckPoint3Indicator = MiniMapIndicator::create();
	beginEditCP(CheckPoint3Indicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
		CheckPoint3Indicator->setGenerator(BoxComponentGenerator);
		CheckPoint3Indicator->setLocation(CheckPoint3GeometryNode);
	endEditCP(CheckPoint3Indicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);

	CheckPoint3AboveIndicator = MiniMapIndicator::create();
	beginEditCP(CheckPoint3AboveIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
		CheckPoint3AboveIndicator->setGenerator(AboveComponentGenerator);
		CheckPoint3AboveIndicator->setLocation(CheckPoint3GeometryNode);
	endEditCP(CheckPoint3AboveIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);

	CheckPoint3BelowIndicator = MiniMapIndicator::create();
	beginEditCP(CheckPoint3BelowIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
		CheckPoint3BelowIndicator->setGenerator(BelowComponentGenerator);
		CheckPoint3BelowIndicator->setLocation(CheckPoint3GeometryNode);
	endEditCP(CheckPoint3BelowIndicator, MiniMapIndicator::LocationFieldMask | MiniMapIndicator::GeneratorFieldMask);
	

    //OverLay
	ImageComponentPtr DirectionalComponentPrototype = ImageComponent::create();
	beginEditCP(DirectionalComponentPrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
		DirectionalComponentPrototype->setPreferredSize(Vec2f(15.0f,20.0f));
        DirectionalComponentPrototype->setScale(ImageComponent::SCALE_STRETCH);
		DirectionalComponentPrototype->setAlignment(Vec2f(0.5f,0.5f));
	endEditCP(DirectionalComponentPrototype, ImageComponent::PreferredSizeFieldMask | ImageComponent::ScaleFieldMask | ImageComponent::AlignmentFieldMask);
	ImagePtr PointerImage = ImageFileHandler::the().read(Path("./Data/Pointer.png").string().c_str());
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
		DirectionalOverlay->getIndicators().push_back(CheckPoint1Indicator);     //Link the Sphere Indicator to the Mini Map
		DirectionalOverlay->setDirectionComponentGenerator(DirectionalComponentGenerator);
        DirectionalOverlay->setDrawWhenVisible(false);
        //DirectionalOverlay->setMinimumDistance(4000.0f);
        //DirectionalOverlay->setFadeAsApproaching(true);
	endEditCP(DirectionalOverlay, DirectionalIndicatorMiniMapOverlay::IndicatorsFieldMask | DirectionalIndicatorMiniMapOverlay::DirectionComponentGeneratorFieldMask);
    
    

	// Setup the size and other preferences to the MiniMap
    BorderLayoutConstraintsPtr MiniMapConstraints = osg::BorderLayoutConstraints::create();
	beginEditCP(MiniMapConstraints, BorderLayoutConstraints::RegionFieldMask);
		MiniMapConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
	endEditCP(MiniMapConstraints, BorderLayoutConstraints::RegionFieldMask);
	 
    beginEditCP(TheMiniMap, LayeredImageMiniMap::PreferredSizeFieldMask | LayeredImageMiniMap::ViewPointIndicatorFieldMask | LayeredImageMiniMap::TransformationFieldMask | LayeredImageMiniMap::OpacityFieldMask | LayeredImageMiniMap::ConstraintsFieldMask | LayeredImageMiniMap::LockMapOrientationFieldMask | MiniMap::UnlockedMapSizeFieldMask | MiniMap::IndicatorsFieldMask);
	    TheMiniMap->setPreferredSize(Pnt2f(450,450));
	    TheMiniMap->setViewPointIndicator(ViewpointIndicator);
		TheMiniMap->setTransformation(WorldToMiniMapTransformation);
		TheMiniMap->setOpacity(.6);
		TheMiniMap->setConstraints(MiniMapConstraints);
		TheMiniMap->setLockMapOrientation(false);                  //If this is changed to true the map will then remain stationary and the indicator will then move and rotate
        TheMiniMap->setUnlockedMapSize(Vec2f(1000,1000));          //This item is only necassary when the map is set to Unlocked Orientation
		TheMiniMap->getIndicators().push_back(CheckPoint1Indicator);    //Link the Sphere Indicator to the Mini Map
        //TheMiniMap->getIndicators().push_back(CheckPoint2Indicator);
        TheMiniMap->getOverlays().push_back(DirectionalOverlay);   //Link the Overlay itself to the Mini Map
	endEditCP(TheMiniMap, LayeredImageMiniMap::PreferredSizeFieldMask | LayeredImageMiniMap::ViewPointIndicatorFieldMask | LayeredImageMiniMap::TransformationFieldMask | LayeredImageMiniMap::OpacityFieldMask | LayeredImageMiniMap::ConstraintsFieldMask | LayeredImageMiniMap::LockMapOrientationFieldMask | MiniMap::UnlockedMapSizeFieldMask | MiniMap::IndicatorsFieldMask);

    //Set the images the map will use a layers of the scene.
    //The second arg in the method call is the space between that layer and the layer befor it
	TheMiniMap->insertLayer(Path("./Data/level1.jpg").string().c_str(), 15.0);
    TheMiniMap->insertLayer(Path("./Data/level2.jpg").string().c_str(), 15.0);
    TheMiniMap->insertLayer(Path("./Data/level3.jpg").string().c_str(), 15.0);
    TheMiniMap->insertLayer(Path("./Data/level4.jpg").string().c_str(), 15.0);
    TheMiniMap->insertLayer(Path("./Data/level5.jpg").string().c_str(), 15.0);
    TheMiniMap->insertLayer(Path("./Data/level6.jpg").string().c_str(), 15.0);
    TheMiniMap->insertLayer(Path("./Data/level7.jpg").string().c_str(), 15.0);
    TheMiniMap->insertLayer(Path("./Data/level8.jpg").string().c_str(), 15.0);
    TheMiniMap->insertLayer(Path("./Data/level9.jpg").string().c_str(), 15.0);
    TheMiniMap->insertLayer(Path("./Data/level10.jpg").string().c_str(), 15.0);

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
	   MainInternalWindow->getChildren().push_back(TheMiniMap);
	   MainInternalWindow->setLayout(MainInternalWindowLayout);
       MainInternalWindow->setBackgrounds(MainInternalWindowBackground);
	   MainInternalWindow->setAlignmentInDrawingSurface(Vec2f(1.0f,1.0f));
	   MainInternalWindow->setScalingInDrawingSurface(Vec2f(0.4f,0.4f));
	   MainInternalWindow->setDrawTitlebar(false);
	   MainInternalWindow->setResizable(false);
    endEditCP(MainInternalWindow, InternalWindow::ChildrenFieldMask | InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
    

    LabelPtr TimeTrackingInd1Label = Label::create();
    beginEditCP(TimeTrackingInd1Label, Label::TextFieldMask);
    TimeTrackingInd1Label->setText("Indicator 1: ");
    endEditCP(TimeTrackingInd1Label, Label::TextFieldMask);

    TimeTrackingInd1ValueLabel = Label::create();
    beginEditCP(TimeTrackingInd1ValueLabel, Label::TextFieldMask);
    TimeTrackingInd1ValueLabel->setText("");
    endEditCP(TimeTrackingInd1ValueLabel, Label::TextFieldMask);
    
    LabelPtr TimeTrackingInd2Label = Label::create();
    beginEditCP(TimeTrackingInd2Label, Label::TextFieldMask);
    TimeTrackingInd2Label->setText("Indicator 2: ");
    endEditCP(TimeTrackingInd2Label, Label::TextFieldMask);

    TimeTrackingInd2ValueLabel = Label::create();
    beginEditCP(TimeTrackingInd2ValueLabel, Label::TextFieldMask);
    TimeTrackingInd2ValueLabel->setText("");
    endEditCP(TimeTrackingInd2ValueLabel, Label::TextFieldMask);
    
    LabelPtr TimeTrackingInd3Label = Label::create();
    beginEditCP(TimeTrackingInd3Label, Label::TextFieldMask);
    TimeTrackingInd3Label->setText("Indicator 3: ");
    endEditCP(TimeTrackingInd3Label, Label::TextFieldMask);

    TimeTrackingInd3ValueLabel = Label::create();
    beginEditCP(TimeTrackingInd3ValueLabel, Label::TextFieldMask);
    TimeTrackingInd3ValueLabel->setText("");
    endEditCP(TimeTrackingInd3ValueLabel, Label::TextFieldMask);


    
    //Create the Time Tracking Window
    GridLayoutPtr TimeTrackingWindowLayout = GridLayout::create();
    beginEditCP(TimeTrackingWindowLayout, GridLayout::RowsFieldMask | GridLayout::ColumnsFieldMask | 
		GridLayout::HorizontalGapFieldMask | GridLayout::VerticalGapFieldMask);
        TimeTrackingWindowLayout->setRows(3);
        TimeTrackingWindowLayout->setColumns(2);
        TimeTrackingWindowLayout->setHorizontalGap(1);
        TimeTrackingWindowLayout->setVerticalGap(1);
    endEditCP(TimeTrackingWindowLayout, GridLayout::RowsFieldMask | GridLayout::ColumnsFieldMask | 
		GridLayout::HorizontalGapFieldMask | GridLayout::VerticalGapFieldMask);

    InternalWindowPtr TimeTrackingWindow = osg::InternalWindow::create();
    beginEditCP(TimeTrackingWindow, InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
	   TimeTrackingWindow->setLayout(TimeTrackingWindowLayout);
       TimeTrackingWindow->getChildren().push_back(TimeTrackingInd1Label);
       TimeTrackingWindow->getChildren().push_back(TimeTrackingInd1ValueLabel);
       TimeTrackingWindow->getChildren().push_back(TimeTrackingInd2Label);
       TimeTrackingWindow->getChildren().push_back(TimeTrackingInd2ValueLabel);
       TimeTrackingWindow->getChildren().push_back(TimeTrackingInd3Label);
       TimeTrackingWindow->getChildren().push_back(TimeTrackingInd3ValueLabel);
       TimeTrackingWindow->setBackgrounds(MainInternalWindowBackground);
	   TimeTrackingWindow->setAlignmentInDrawingSurface(Vec2f(0.0f,0.0f));
	   TimeTrackingWindow->setScalingInDrawingSurface(Vec2f(0.2f,0.1f));
	   TimeTrackingWindow->setDrawTitlebar(false);
	   TimeTrackingWindow->setResizable(false);
    endEditCP(TimeTrackingWindow, InternalWindow::LayoutFieldMask | InternalWindow::BackgroundsFieldMask | InternalWindow::AlignmentInDrawingSurfaceFieldMask | InternalWindow::ScalingInDrawingSurfaceFieldMask | InternalWindow::DrawTitlebarFieldMask | InternalWindow::ResizableFieldMask);
    
	
    // Create the Drawing Surface
    UIDrawingSurfacePtr TutorialDrawingSurface = UIDrawingSurface::create();
    beginEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
        TutorialDrawingSurface->setGraphics(TutorialGraphics);
        TutorialDrawingSurface->setEventProducer(TutorialWindowEventProducer);
    endEditCP(TutorialDrawingSurface, UIDrawingSurface::GraphicsFieldMask | UIDrawingSurface::EventProducerFieldMask);
    
	TutorialDrawingSurface->openWindow(MainInternalWindow);
    TutorialDrawingSurface->openWindow(TimeTrackingWindow);
	
	// Create the UI Foreground Object
    UIForegroundPtr TutorialUIForeground = osg::UIForeground::create();

    beginEditCP(TutorialUIForeground, UIForeground::DrawingSurfaceFieldMask);
        TutorialUIForeground->setDrawingSurface(TutorialDrawingSurface);
    endEditCP(TutorialUIForeground, UIForeground::DrawingSurfaceFieldMask);

	//Create a Foreground for a reticule
	ImageForegroundPtr ReticuleForeground = ImageForeground::create();
	beginEditCP(ReticuleForeground, ImageForeground::ImagesFieldMask | ImageForeground::PositionsFieldMask);
		ReticuleForeground->getImages().push_back(ImageFileHandler::the().read(Path("./Data/ret.png").string().c_str()));
		ReticuleForeground->getPositions().push_back(Vec2f(0.5,0.5));
	endEditCP(ReticuleForeground, ImageForeground::ImagesFieldMask | ImageForeground::PositionsFieldMask);

    mgr->setRoot(scene);

    // Add the UI Foreground Object to the Scene
    ViewportPtr TutorialViewport = mgr->getWindow()->getPort(0);
    beginEditCP(TutorialViewport, Viewport::ForegroundsFieldMask);
        TutorialViewport->getForegrounds().push_back(TutorialUIForeground);
        TutorialViewport->getForegrounds().push_back(ReticuleForeground);
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
