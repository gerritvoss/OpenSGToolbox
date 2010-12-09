/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGGLViewport.h"
#include "OSGBackground.h"
#include "OSGCamera.h"
#include "OSGTransform.h"
#include "OSGPerspectiveCamera.h"
#include "OSGMatrixUtility.h"
#include "OSGInternalWindow.h"

#include "OSGPassiveWindow.h"
#include "OSGGLViewport.h"
#include "OSGUIDrawUtils.h"
#include "OSGCameraUtils.h"
#include "OSGUIDrawingSurface.h"
#include "OSGWindowEventProducer.h"
#include "OSGIntersectAction.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGGLViewportBase.cpp file.
// To modify it, please change the .fcd file (OSGGLViewport.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GLViewport::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

const Matrix& GLViewport::getViewMatrix(void)
{
    if(_Navigator.getMode() == Navigator::NONE && 
       _DrawingViewport->getCamera()->getBeacon()->getCore()->getType().isDerivedFrom(Transform::getClassType()))
    {
        return dynamic_cast<Transform*>(_DrawingViewport->getCamera()->getBeacon()->getCore())->getMatrix();
    }
    else
    {
        _Navigator.getMatrix();
    }
}
 

void GLViewport::drawInternal(Graphics* const TheGraphics, Real32 Opacity) const
{
    drawViewport(TheGraphics->getDrawEnv());
}

void GLViewport::mousePressed(MouseEventDetails* const e)
{
    Inherited::mousePressed(e);

    if(_Navigator.getMode() != Navigator::NONE/* &&
       dynamic_cast<WindowEventProducer*>(e->getSource())->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_ALT*/)
    {
        UInt16 MouseButtons;
        switch(e->getButton())
        {
            case MouseEventDetails::BUTTON1:
                _InitialMat = _Navigator.getMatrix();
                _Navigator.buttonPress(Navigator::LEFT_MOUSE,e->getLocation().x(),e->getLocation().y());
                _NavMouseReleasedConnection.disconnect();
                _NavMouseDraggedConnection.disconnect();
                _NavKeyPressedConnection.disconnect();
                _NavMouseReleasedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseReleased(boost::bind(&GLViewport::handleNavMouseReleased, this, _1));
                _NavMouseDraggedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseDragged(boost::bind(&GLViewport::handleNavMouseDragged, this, _1));
                _NavKeyPressedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectKeyPressed(boost::bind(&GLViewport::handleNavKeyPressed, this, _1));

                MouseButtons = 1;
                break;
            case MouseEventDetails::BUTTON2:
                _InitialMat = _Navigator.getMatrix();
                _Navigator.buttonPress(Navigator::RIGHT_MOUSE,e->getLocation().x(),e->getLocation().y());
                _NavMouseReleasedConnection.disconnect();
                _NavMouseDraggedConnection.disconnect();
                _NavKeyPressedConnection.disconnect();
                _NavMouseReleasedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseReleased(boost::bind(&GLViewport::handleNavMouseReleased, this, _1));
                _NavMouseDraggedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseDragged(boost::bind(&GLViewport::handleNavMouseDragged, this, _1));
                _NavKeyPressedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectKeyPressed(boost::bind(&GLViewport::handleNavKeyPressed, this, _1));
                MouseButtons = 4;
                break;
            case MouseEventDetails::BUTTON3:
                _InitialMat = _Navigator.getMatrix();
                _Navigator.buttonPress(Navigator::MIDDLE_MOUSE,e->getLocation().x(),e->getLocation().y());
                _NavMouseReleasedConnection.disconnect();
                _NavMouseDraggedConnection.disconnect();
                _NavKeyPressedConnection.disconnect();
                _NavMouseReleasedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseReleased(boost::bind(&GLViewport::handleNavMouseReleased, this, _1));
                _NavMouseDraggedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseDragged(boost::bind(&GLViewport::handleNavMouseDragged, this, _1));
                _NavKeyPressedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectKeyPressed(boost::bind(&GLViewport::handleNavKeyPressed, this, _1));
                MouseButtons = 2;
                break;
        }
        _Navigator.idle(MouseButtons,e->getLocation().x(),e->getLocation().y());
        _Navigator.updateCameraTransformation();
    }
}

void GLViewport::detachFromEventProducer(void)
{
    Inherited::detachFromEventProducer();
    _NavMouseReleasedConnection.disconnect();
    _NavMouseDraggedConnection.disconnect();
    _NavKeyPressedConnection.disconnect();

}

void GLViewport::keyTyped(KeyEventDetails* const e)
{
    Inherited::keyTyped(e);
    if(_Navigator.getMode() != Navigator::NONE)
    {
        switch ( e->getKey() )
        {
            case KeyEventDetails::KEY_J:
            case KeyEventDetails::KEY_LEFT:
                _Navigator.keyPress(Navigator::LEFT,0,0);
                _Navigator.updateCameraTransformation();
                break;
            case KeyEventDetails::KEY_G:
            case KeyEventDetails::KEY_RIGHT:
                _Navigator.keyPress(Navigator::RIGHT,0,0);
                _Navigator.updateCameraTransformation();
                break;
            case KeyEventDetails::KEY_U:
                _Navigator.keyPress(Navigator::LEFTROT,0,0);
                _Navigator.updateCameraTransformation();
                break;
            case KeyEventDetails::KEY_T:
                _Navigator.keyPress(Navigator::RIGHTROT,0,0);
                _Navigator.updateCameraTransformation();
                break;
            case KeyEventDetails::KEY_Y:
            case KeyEventDetails::KEY_UP:
                _Navigator.keyPress(Navigator::FORWARDS,0,0);
                _Navigator.updateCameraTransformation();
                break;
            case KeyEventDetails::KEY_H:
            case KeyEventDetails::KEY_DOWN:
                _Navigator.keyPress(Navigator::BACKWARDS,0,0);
                _Navigator.updateCameraTransformation();
                break;
        }
    }
}

void GLViewport::mouseWheelMoved(MouseWheelEventDetails* const e)
{
    if(_Navigator.getMode() != Navigator::NONE)
    {
        if(e->getUnitsToScroll() > 0)
        {
            for(UInt32 i(0) ; i<e->getUnitsToScroll() ;++i)
            {
                _Navigator.buttonPress(Navigator::DOWN_MOUSE,e->getLocation().x(),e->getLocation().y());
                _Navigator.buttonRelease(Navigator::DOWN_MOUSE,e->getLocation().x(),e->getLocation().y());
                _Navigator.updateCameraTransformation();
            }
        }
        else if(e->getUnitsToScroll() < 0)
        {
            for(UInt32 i(0) ; i<abs(e->getUnitsToScroll()) ;++i)
            {
                _Navigator.buttonPress(Navigator::UP_MOUSE,e->getLocation().x(),e->getLocation().y());
                _Navigator.buttonRelease(Navigator::UP_MOUSE,e->getLocation().x(),e->getLocation().y());
                _Navigator.updateCameraTransformation();
            }
        }
    }
    e->setConsumed(true);
}

void GLViewport::lookAt(const Pnt3f& From, const Pnt3f& At, const Vec3f& Up)
{
    if(_Navigator.getMode() != Navigator::NONE)
    {
        _Navigator.set(From,At,Up);
                _Navigator.updateCameraTransformation();
    }
}

void GLViewport::show(Node* const FocusNode)
{
    commitChanges();

    if(getPort() == NULL ||
       FocusNode == NULL ||
       _NavCamera == NULL ||
       !_NavCamera->getType().isDerivedFrom(PerspectiveCamera::getClassType()))
        return;

    //
    ::OSG::showAll(_NavCamera, FocusNode);
    if(_Navigator.getMode() != Navigator::NONE)
    {
        _Navigator.set(_NavCamera->getBeacon()->getToWorld());
        _Navigator.updateCameraTransformation();
    }

    Vec3f min,max;
    BoxVolume vol;
    FocusNode->getWorldVolume(vol);
    vol.getBounds( min, max );
    Vec3f d = max - min;

    if(d.length() < Eps) // Nothing loaded? Use a unity box
    {
        min.setValues(-1.f,-1.f,-1.f);
        max.setValues( 1.f, 1.f, 1.f);
        d = max - min;
    }

    // adjust the translation factors so that motions are sort of scaled
    _Navigator.setMotionFactor((d[0] + d[1] + d[2]) / 100.f);
}

Node* GLViewport::grabNode(const Pnt2f& Location, UInt32 TravMask, Real32 MaxDistance) const
{
    Pnt2f ViewportPoint(Location);
    Line ViewRay;
    _DrawingViewport->getCamera()->calcViewRay( ViewRay, ViewportPoint.x(), ViewportPoint.y(), *_DrawingViewport);

    boost::scoped_ptr<IntersectAction> CastRayAction(IntersectAction::create());

    CastRayAction->setLine( ViewRay, MaxDistance );
    CastRayAction->setTravMask(TravMask);
    CastRayAction->apply( _DrawingViewport->getRoot() );             

    if ( CastRayAction->didHit() )
    {
        return CastRayAction->getHitObject();
    }
    else
    {
        return NULL;
    }
}

void GLViewport::setParentWindow(InternalWindow* const parent)
{
    Inherited::setParentWindow(parent);
    dettachDrawingViewport();
    if(parent != NULL)
    {
        updateDrawingViewport();
        attachDrawingViewport();
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
void GLViewport::onCreate(const GLViewport *Id)
{
    Inherited::onCreate(Id);

    if(Id != NULL)
    {
        //Camera Transform
        _NavCameraTransform = Transform::create();

        //Camera Beacon
        _NavCameraBeacon = Node::create();
        _NavCameraBeacon->setCore(_NavCameraTransform);

        //Camera
        PerspectiveCameraRecPtr NavCamera = PerspectiveCamera::create();
        NavCamera->setBeacon(_NavCameraBeacon);
        NavCamera->setFov(60.0f);
        NavCamera->setAspect(1.0f);
        NavCamera->setNear(1.0f);
        NavCamera->setFar(1000.0f);

        _NavCamera = NavCamera;
        
        _DrawingViewport = Viewport::create();
        _DrawingViewport->setCamera(_NavCamera);
        
        _Navigator.setViewport(_DrawingViewport);
        _Navigator.setCameraTransformation(_NavCamera->getBeacon());
    }
}

void GLViewport::onDestroy()
{
}

void GLViewport::updateDrawingViewport(void)
{
    if(getPort() == NULL)
    {
        _DrawingViewport->setRoot(NULL);
        _DrawingViewport->clearForegrounds();
        _DrawingViewport->setBackground(NULL);
        _DrawingViewport->setRenderOptions(NULL);
    }
    else
    {
        //Apply the transform of the camera attached to the viewport
        if(getPort()->getCamera() &&
           getPort()->getCamera()->getBeacon())
        {
            //_NavCameraTransform->setMatrix(getPort()->getCamera()->getBeacon()->getToWorld());
        }

        _NavCamera->setNear(getPort()->getCamera()->getNear());
        _NavCamera->setFar(getPort()->getCamera()->getFar());

        if(_NavCamera->getType() == getPort()->getCamera()->getType())
        {
            dynamic_pointer_cast<PerspectiveCamera>(_NavCamera)->setFov(dynamic_cast<PerspectiveCamera*>(getPort()->getCamera())->getFov());
            dynamic_pointer_cast<PerspectiveCamera>(_NavCamera)->setAspect(dynamic_cast<PerspectiveCamera*>(getPort()->getCamera())->getAspect());
        }

        _DrawingViewport->setRoot(getPort()->getRoot());
        _DrawingViewport->setTravMask(getPort()->getTravMask());
        _DrawingViewport->assignForegrounds(*getPort()->getMFForegrounds());
        _DrawingViewport->setBackground(getPort()->getBackground());
        _DrawingViewport->setRenderOptions(getPort()->getRenderOptions());
    }
}

void GLViewport::attachDrawingViewport(void)
{
    if(getParentContainer() != NULL &&
       getParentContainer()->getParentWindow() != NULL)
    {
        //Add the Drawing Viewport to the window
        getParentContainer()->getParentWindow()->getParentDrawingSurface()->getEventProducer()->addPort(_DrawingViewport);
    }
}

void GLViewport::dettachDrawingViewport(void)
{
    if(getParentContainer() != NULL &&
       getParentContainer()->getParentWindow() != NULL)
    {
        //Remove the Drawing Viewport from the window
        getParentContainer()->getParentWindow()->getParentDrawingSurface()->getEventProducer()->subPortByObj(_DrawingViewport);
        _DrawingViewport->setEnabled(false);
    }
}

void GLViewport::drawViewport(DrawEnv* dEnv) const
{
    if(_DrawingViewport->getRoot() != NULL &&
       _DrawingViewport->getBackground() != NULL &&
       _DrawingViewport->getCamera() != NULL)
    {
        Pnt2f InsideInsetTopLeft, InsideInsetBottomRight;
        getInsideBorderBounds(InsideInsetTopLeft,InsideInsetBottomRight);

        //Clamp Viewport Bounds with Window clip planes
        Pnt2f InsideInsetTopLeftToWindow, InsideInsetBottomRightToWindow;
        quadIntersection(InsideInsetTopLeft, InsideInsetBottomRight,
                         getClipTopLeft(), getClipBottomRight(),
                         InsideInsetTopLeftToWindow, InsideInsetBottomRightToWindow);


		ViewportRefPtr ContainingViewport(dEnv->getAction()->getViewport());
        InsideInsetTopLeftToWindow = ComponentToWindow(InsideInsetTopLeftToWindow,this, ContainingViewport);
        InsideInsetBottomRightToWindow = ComponentToWindow(InsideInsetBottomRightToWindow,this, ContainingViewport);



        if( getParentWindow() != NULL &&
            getParentWindow()->getParentDrawingSurface() != NULL &&
            getParentWindow()->getParentDrawingSurface()->getEventProducer() != NULL)
        {

            WindowRefPtr TheWindow = getParentWindow()->getParentDrawingSurface()->getEventProducer();

            //Clamp Viewport Bounds with Window size
            if(InsideInsetTopLeftToWindow.x() < 0)
            {
                InsideInsetTopLeftToWindow[0] = 0.0f;
            }
            if(InsideInsetTopLeftToWindow.y() > TheWindow->getHeight())
            {
                InsideInsetTopLeftToWindow[1] = TheWindow->getHeight();
            }

            if(InsideInsetBottomRightToWindow.x() > TheWindow->getWidth())
            {
                InsideInsetBottomRightToWindow[0] = TheWindow->getWidth();
            }
            if(InsideInsetBottomRightToWindow.y() < 0)
            {
                InsideInsetBottomRightToWindow[1] = 0.0f;
            }

            //Update the camera if Perspective
            if(_DrawingViewport->getCamera()->getType().isDerivedFrom(PerspectiveCamera::getClassType()))
            {
                if(abs(InsideInsetTopLeftToWindow.y() - InsideInsetBottomRightToWindow.y()) < getSize().y())
                {
                    dynamic_cast<PerspectiveCamera*>(_DrawingViewport->getCamera())->setFov(
                                                                                     60.0f *
                                                                                     (abs(InsideInsetTopLeftToWindow.y() - InsideInsetBottomRightToWindow.y())/getSize().y())
                                                                                    );
                }
            }

            //Set the properties of the viewport to render this scene into
            _DrawingViewport->setSize(InsideInsetTopLeftToWindow.x(), InsideInsetBottomRightToWindow.y()+1, InsideInsetBottomRightToWindow.x()-1, InsideInsetTopLeftToWindow.y());
            

            glPushAttrib(GL_ALL_ATTRIB_BITS);

            GLdouble ModelViewMat[16];
            glGetDoublev(GL_MODELVIEW_MATRIX, ModelViewMat);
            GLdouble ProjectionMat[16];
            glGetDoublev(GL_PROJECTION_MATRIX, ProjectionMat);

            GLint MaxClipPlanes;
            glGetIntegerv(GL_MAX_CLIP_PLANES, &MaxClipPlanes);
            for(UInt8 i = 0;i <MaxClipPlanes ;++i)
                glDisable(GL_CLIP_PLANE0 + i);

            glDepthMask(true);

            _DrawingViewport->setEnabled(true);

            _RenderAction->setWindow(dEnv->getAction()->getWindow());
            
            if(dEnv->getAction()->getWindow()->getDrawerId() < 0)
            {
                _RenderAction->setDrawerId(dEnv->getAction()->getWindow()->getId());
            }
            else
            {
                _RenderAction->setDrawerId(dEnv->getAction()->getWindow()->getDrawerId());
            }

            if((dEnv->getAction()->getWindow()->getDrawMode() & Window::PartitionDrawMask) == 
                                                           Window::SequentialPartitionDraw)
            {
                _RenderAction->setDrawPartPar(false);
            }
            else if((dEnv->getAction()->getWindow()->getDrawMode() & Window::PartitionDrawMask) == 
                                                             Window::ParallelPartitionDraw)
            {
                _RenderAction->setDrawPartPar(true);
            }

            _RenderAction->frameInit();

            if(_DrawingViewport->getDrawableId() < 0)
            {
                _RenderAction->setDrawableId(0);
            }
            else
            {
                _RenderAction->setDrawableId(_DrawingViewport->getDrawableId());
            }

            _DrawingViewport->render(_RenderAction.get());
            _DrawingViewport->setEnabled(false);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glMultMatrixd(ModelViewMat);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glMultMatrixd(ProjectionMat);

            glMatrixMode(GL_MODELVIEW);

            glPopAttrib();
        }

    }
}

void GLViewport::resolveLinks(void)
{
    Inherited::resolveLinks();

    _NavMouseReleasedConnection.disconnect();
    _NavMouseDraggedConnection.disconnect();
    _NavKeyPressedConnection.disconnect();

    _DrawingViewport = NULL;
    _NavCameraBeacon = NULL;
    _NavCameraTransform = NULL;
    _NavCamera = NULL;
}

/*----------------------- constructors & destructors ----------------------*/

GLViewport::GLViewport(void) :
    Inherited(),
        _DrawingViewport(NULL)
{
	_Navigator.setMode(Navigator::TRACKBALL);
	_Navigator.setClickCenter(false);
    _RenderAction.reset(RenderAction::create());
}

GLViewport::GLViewport(const GLViewport &source) :
    Inherited(source),
        _DrawingViewport(NULL)
{
	_Navigator.setMode(Navigator::TRACKBALL);
	_Navigator.setClickCenter(false);
    _RenderAction.reset(RenderAction::create());
}

GLViewport::~GLViewport(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GLViewport::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

	if(whichField & PortFieldMask)
    {
        dettachDrawingViewport();
        if(getParentWindow() != NULL)
        {
            updateDrawingViewport();
            attachDrawingViewport();
        }
    }

	if(whichField & SizeFieldMask)
    {
        //Update the size of the Drawing Viewport
    }
}

void GLViewport::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump GLViewport NI" << std::endl;
}

void GLViewport::handleNavMouseReleased(MouseEventDetails* const e)
{
	
    if(_Navigator.getMode() != Navigator::NONE)
    {
	    UInt16 MouseButtons;
	    switch(e->getButton())
	    {
	    case MouseEventDetails::BUTTON1:
		    _Navigator.buttonRelease(Navigator::LEFT_MOUSE,e->getLocation().x(),e->getLocation().y());
		    MouseButtons = 1;
		    break;
	    case MouseEventDetails::BUTTON2:
		    _Navigator.buttonRelease(Navigator::RIGHT_MOUSE,e->getLocation().x(),e->getLocation().y());
		    MouseButtons = 4;
		    break;
	    case MouseEventDetails::BUTTON3:
		    _Navigator.buttonRelease(Navigator::MIDDLE_MOUSE,e->getLocation().x(),e->getLocation().y());
		    MouseButtons = 2;
		    break;
	    case MouseEventDetails::BUTTON4:
		    MouseButtons = 8;
		    break;
	    case MouseEventDetails::BUTTON5:
		    _Navigator.buttonRelease(Navigator::DOWN_MOUSE,e->getLocation().x(),e->getLocation().y());
		    MouseButtons = 16;
		    break;
	    }
	    _Navigator.idle(MouseButtons,e->getLocation().x(),e->getLocation().y());
        _Navigator.updateCameraTransformation();

    }
    _NavMouseReleasedConnection.disconnect();
    _NavMouseDraggedConnection.disconnect();
    _NavKeyPressedConnection.disconnect();
}

void GLViewport::handleNavMouseDragged(MouseEventDetails* const e)
{

    if(_Navigator.getMode() != Navigator::NONE)
    {
	    UInt16 MouseButtons;
	    switch(e->getButton())
	    {
	    case MouseEventDetails::BUTTON1:
		    MouseButtons = 1;
		    break;
	    case MouseEventDetails::BUTTON2:
		    MouseButtons = 4;
		    break;
	    case MouseEventDetails::BUTTON3:
		    MouseButtons = 2;
		    break;
	    case MouseEventDetails::BUTTON4:
		    MouseButtons = 8;
		    break;
	    case MouseEventDetails::BUTTON5:
		    MouseButtons = 16;
		    break;
	    }
	    _Navigator.moveTo(e->getLocation().x(),e->getLocation().y());
	    _Navigator.idle(MouseButtons,e->getLocation().x(),e->getLocation().y());
        _Navigator.updateCameraTransformation();
    }
}

void GLViewport::set(const Matrix& m)
{
	_Navigator.set(m);
    _Navigator.updateCameraTransformation();
}

void GLViewport::handleNavKeyPressed(KeyEventDetails* const e)
{
    if(_Navigator.getMode() != Navigator::NONE)
    {
	    if(e->getKey() == KeyEventDetails::KEY_ESCAPE)
	    {
		    _Navigator.set(_InitialMat);
            _Navigator.updateCameraTransformation();
            _NavMouseReleasedConnection.disconnect();
            _NavMouseDraggedConnection.disconnect();
            _NavKeyPressedConnection.disconnect();
	    }
    }
}

OSG_END_NAMESPACE
