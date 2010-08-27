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
void GLViewport::copyView(const GLViewport& TheViewport)
{
    _Navigator = TheViewport._Navigator;
    _DefaultView = TheViewport._DefaultView;
    _Yaw = TheViewport._Yaw;
    _Pitch = TheViewport._Pitch;
    _Roll = TheViewport._Roll;
    _InitialYaw = TheViewport._InitialYaw;
    _InitialPitch = TheViewport._InitialPitch;
    _InitialRoll = TheViewport._InitialRoll;
    _Offset = TheViewport._Offset;
}

const Matrix& GLViewport::getViewMatrix(void)
{
    if(_Navigator.getMode() == Navigator::NONE && 
       getPort()->getCamera()->getBeacon()->getCore()->getType().isDerivedFrom(Transform::getClassType()))
    {
        return dynamic_cast<Transform*>(getPort()->getCamera()->getBeacon()->getCore())->getMatrix();
    }
    else
    {
        _Navigator.getMatrix();
    }
}
 

void GLViewport::drawInternal(Graphics* const Graphics, Real32 Opacity) const
{
    if(getPort() != NULL &&
       getPort()->getRoot() != NULL &&
       getPort()->getBackground() != NULL &&
       getPort()->getCamera() != NULL)
    {
        Pnt2f InsideInsetTopLeft, InsideInsetBottomRight;
        getInsideBorderBounds(InsideInsetTopLeft,InsideInsetBottomRight);

        //Clamp Viewport Bounds with Window clip planes
        Pnt2f InsideInsetTopLeftToWindow, InsideInsetBottomRightToWindow;
        quadIntersection(InsideInsetTopLeft, InsideInsetBottomRight,
                         getClipTopLeft(), getClipBottomRight(),
                         InsideInsetTopLeftToWindow, InsideInsetBottomRightToWindow);


		ViewportRefPtr ContainingViewport(Graphics->getDrawEnv()->getAction()->getViewport());
        InsideInsetTopLeftToWindow = ComponentToWindow(InsideInsetTopLeftToWindow,this, ContainingViewport);
        InsideInsetBottomRightToWindow = ComponentToWindow(InsideInsetBottomRightToWindow,this, ContainingViewport);



        if( getParentWindow() != NULL &&
            getParentWindow()->getParentDrawingSurface() != NULL &&
            getParentWindow()->getParentDrawingSurface()->getEventProducer() != NULL &&
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
            if(getPort()->getCamera()->getType().isDerivedFrom(PerspectiveCamera::getClassType()))
            {
                if(abs(InsideInsetTopLeftToWindow.y() - InsideInsetBottomRightToWindow.y()) < getSize().y())
                {
                    dynamic_cast<PerspectiveCamera*>(getPort()->getCamera())->setFov(
                                                                                     60.0f *
                                                                                     (abs(InsideInsetTopLeftToWindow.y() - InsideInsetBottomRightToWindow.y())/getSize().y())
                                                                                    );
                }
            }


            //Store the properties of this viewport to reset later
            Vec4f ContainingViewportBounds(ContainingViewport->getLeft(),
                                           ContainingViewport->getBottom(),
                                           ContainingViewport->getRight(),
                                           ContainingViewport->getTop());

            CameraUnrecPtr ContainingViewportCamera(ContainingViewport->getCamera());
            NodeUnrecPtr   ContainingViewportRoot(ContainingViewport->getRoot());
            BackgroundUnrecPtr ContainingViewportBackground(ContainingViewport->getBackground());
            std::vector<ForegroundUnrecPtr> ContainingViewportForegrounds;
            for(UInt32 i(0) ; i<ContainingViewport->getMFForegrounds()->size() ; ++i)
            {
                ContainingViewportForegrounds.push_back(ContainingViewport->getForegrounds(i));
            }
            UInt32 ContainingViewportTravMask(ContainingViewport->getTravMask());
            Real32 ContainingViewportDrawTime(ContainingViewport->getDrawTime());
            Int32 ContainingViewportDrawableId(ContainingViewport->getDrawableId());
            RenderOptionsUnrecPtr ContainingViewportRenderOptions(ContainingViewport->getRenderOptions());

            //Set the properties of the viewport to render this scene into
            ContainingViewport->setSize(InsideInsetTopLeftToWindow.x(), InsideInsetBottomRightToWindow.y()+1, InsideInsetBottomRightToWindow.x()-1, InsideInsetTopLeftToWindow.y());
            ContainingViewport->setCamera(getPort()->getCamera());
            ContainingViewport->setRoot(getPort()->getRoot());
            ContainingViewport->assignForegrounds(*getPort()->getMFForegrounds());
            ContainingViewport->setBackground(getPort()->getBackground());
            ContainingViewport->setCamera(getPort()->getCamera());
            ContainingViewport->setDrawableId(getPort()->getDrawableId());
            ContainingViewport->setRenderOptions(getPort()->getRenderOptions());


            if(_Navigator.getMode() != Navigator::NONE)
            {
                _Navigator.updateCameraTransformation();
            }
            
            _Action->setWindow(ContainingViewport->getParent());

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

            ContainingViewport->render(_Action);


            //Reset the values for the viewport
            ContainingViewport->setSize(ContainingViewportBounds.x(), ContainingViewportBounds.y(), ContainingViewportBounds.z(), ContainingViewportBounds.w());
            ContainingViewport->setCamera(ContainingViewportCamera);
            ContainingViewport->setRoot(ContainingViewportRoot);
            ContainingViewport->clearForegrounds();
            for(UInt32 i(0) ; i<ContainingViewportForegrounds.size() ; ++i)
            {
                ContainingViewport->addForeground(ContainingViewportForegrounds[i]);
            }
            ContainingViewport->setBackground(ContainingViewportBackground);
            ContainingViewport->setTravMask(ContainingViewportTravMask);
            ContainingViewport->setDrawTime(ContainingViewportDrawTime);
            ContainingViewport->setDrawableId(ContainingViewportDrawableId);
            ContainingViewport->setRenderOptions(ContainingViewportRenderOptions);

            ContainingViewport->activate();

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

void GLViewport::mousePressed(MouseEventDetails* const e)
{
    Inherited::mousePressed(e);

    if(_Navigator.getMode() != Navigator::NONE)
    {
        UInt16 MouseButtons;
        switch(e->getButton())
        {
            case MouseEventDetails::BUTTON1:
                _InitialMat = _Navigator.getMatrix();
                _Navigator.buttonPress(Navigator::LEFT_MOUSE,e->getLocation().x(),e->getLocation().y());
                _NavMouseReleasedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseReleased(boost::bind(&GLViewport::handleNavMouseReleased, this, _1));
                _NavMouseDraggedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseReleased(boost::bind(&GLViewport::handleNavMouseDragged, this, _1));
                _NavKeyPressedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectKeyPressed(boost::bind(&GLViewport::handleNavKeyPressed, this, _1));

                MouseButtons = 1;
                break;
            case MouseEventDetails::BUTTON2:
                _InitialMat = _Navigator.getMatrix();
                _Navigator.buttonPress(Navigator::MIDDLE_MOUSE,e->getLocation().x(),e->getLocation().y());
                _NavMouseReleasedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseReleased(boost::bind(&GLViewport::handleNavMouseReleased, this, _1));
                _NavMouseDraggedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseReleased(boost::bind(&GLViewport::handleNavMouseDragged, this, _1));
                _NavKeyPressedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectKeyPressed(boost::bind(&GLViewport::handleNavKeyPressed, this, _1));
                MouseButtons = 2;
                break;
            case MouseEventDetails::BUTTON3:
                _InitialMat = _Navigator.getMatrix();
                _Navigator.buttonPress(Navigator::RIGHT_MOUSE,e->getLocation().x(),e->getLocation().y());
                _NavMouseReleasedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseReleased(boost::bind(&GLViewport::handleNavMouseReleased, this, _1));
                _NavMouseDraggedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseReleased(boost::bind(&GLViewport::handleNavMouseDragged, this, _1));
                _NavKeyPressedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectKeyPressed(boost::bind(&GLViewport::handleNavKeyPressed, this, _1));
                MouseButtons = 4;
                break;
        }
        _Navigator.idle(MouseButtons,e->getLocation().x(),e->getLocation().y());
    }
    else
    {
        _InitialMousePos = e->getLocation();
        _InitialYaw = _Yaw;
        _InitialPitch = _Pitch;
        _InitialRoll = _Roll;
        _NavMouseReleasedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseReleased(boost::bind(&GLViewport::handleNavMouseReleased, this, _1));
        _NavMouseDraggedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseReleased(boost::bind(&GLViewport::handleNavMouseDragged, this, _1));
        _NavKeyPressedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectKeyPressed(boost::bind(&GLViewport::handleNavKeyPressed, this, _1));
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
                break;
            case KeyEventDetails::KEY_G:
            case KeyEventDetails::KEY_RIGHT:
                _Navigator.keyPress(Navigator::RIGHT,0,0);
                break;
            case KeyEventDetails::KEY_U:
                _Navigator.keyPress(Navigator::LEFTROT,0,0);
                break;
            case KeyEventDetails::KEY_T:
                _Navigator.keyPress(Navigator::RIGHTROT,0,0);
                break;
            case KeyEventDetails::KEY_Y:
            case KeyEventDetails::KEY_UP:
                _Navigator.keyPress(Navigator::FORWARDS,0,0);
                break;
            case KeyEventDetails::KEY_H:
            case KeyEventDetails::KEY_DOWN:
                _Navigator.keyPress(Navigator::BACKWARDS,0,0);
                break;
        }
    }
    else
    {
        switch ( e->getKey() )
        {
            case KeyEventDetails::KEY_PLUS:
            case KeyEventDetails::KEY_EQUALS:
            case KeyEventDetails::KEY_UP:
                setOffset(Vec3f(_Offset.x(),_Offset.y(),_Offset.z()-_OffsetMultipliers.z() ));
                break;
            case KeyEventDetails::KEY_MINUS:
            case KeyEventDetails::KEY_UNDERSCORE:
            case KeyEventDetails::KEY_DOWN:
                setOffset(Vec3f(_Offset.x(),_Offset.y(),_Offset.z()+_OffsetMultipliers.z() ));
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
                _Navigator.buttonPress(Navigator::UP_MOUSE,e->getLocation().x(),e->getLocation().y());
                _Navigator.buttonRelease(Navigator::UP_MOUSE,e->getLocation().x(),e->getLocation().y());
            }
        }
        else if(e->getUnitsToScroll() < 0)
        {
            for(UInt32 i(0) ; i<abs(e->getUnitsToScroll()) ;++i)
            {
                _Navigator.buttonPress(Navigator::DOWN_MOUSE,e->getLocation().x(),e->getLocation().y());
                _Navigator.buttonRelease(Navigator::DOWN_MOUSE,e->getLocation().x(),e->getLocation().y());
            }
        }
    }
    else
    {
        setOffset(Vec3f(_Offset.x(),_Offset.y(),_Offset.z()-(_OffsetMultipliers.z()*e->getUnitsToScroll()) ));
    }
    e->setConsumed(true);
}

void GLViewport::lookAt(const Pnt3f& From, const Pnt3f& At, const Vec3f& Up)
{
    if(_Navigator.getMode() == Navigator::NONE)
    {
        if(getPort()->getCamera()->getBeacon()->getCore()->getType().isDerivedFrom(Transform::getClassType()))
        {
            MatrixLookAt(_DefaultView, From, At, Up);
            dynamic_cast<Transform*>(getPort()->getCamera()->getBeacon()->getCore())->setMatrix(_DefaultView);

            //Extract the new yaw pitch and roll
            setYaw(0.0);
            setPitch(0.0);
            setRoll(0.0);
        }
    }
    else
    {
        _Navigator.set(From,At,Up);
    }
}

void GLViewport::showAll(void)
{
    if(getPort() == NULL ||
       getPort()->getRoot() == NULL ||
       getPort()->getCamera() == NULL ||
       !getPort()->getCamera()->getType().isDerivedFrom(PerspectiveCamera::getClassType()))
        return;

    //
    ::OSG::showAll(getPort()->getCamera(), getPort()->getRoot());
    if(_Navigator.getMode() == Navigator::NONE)
    {
    }
    else
    {
        _Navigator.set(getPort()->getCamera()->getBeacon()->getToWorld());
    }

    Vec3f min,max;
    getPort()->getRoot()->getVolume().getBounds( min, max );
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

void GLViewport::updateView(void)
{
    if(_Navigator.getMode() == Navigator::NONE)
    {
        if(getPort()->getCamera()->getBeacon()->getCore()->getType().isDerivedFrom(Transform::getClassType()))
        {
            Matrix View(_DefaultView);
            Matrix YawRot, PitchRot, RollRot;
            YawRot.setRotate(Quaternion(Vec3f(0.0,1.0,0.0),_Yaw));
            PitchRot.setRotate(Quaternion(Vec3f(1.0,0.0,0.0),_Pitch));
            RollRot.setRotate(Quaternion(Vec3f(0.0,0.0,1.0),_Roll));

            Matrix OffsetMat;
            OffsetMat.setTranslate(_Offset);

            View.mult(YawRot);
            View.mult(PitchRot);
            View.mult(RollRot);
            View.mult(OffsetMat);
            dynamic_cast<Transform*>(getPort()->getCamera()->getBeacon()->getCore())->setMatrix(View);
        }
    }
}

void GLViewport::setMultipliers(Real32 YawMultiplier,Real32 PitchMultiplier,Real32 RollMultiplier)
{
    _YawMultiplier = YawMultiplier;
    _PitchMultiplier = PitchMultiplier;
    _RollMultiplier = RollMultiplier;
}

void GLViewport::setClamps(Vec2f YawClamp,Vec2f PitchClamp,Vec2f RollClamp)
{
    _YawClamp = YawClamp;
    _PitchClamp = PitchClamp;
    _RollClamp = RollClamp;
}

void GLViewport::setYaw(Real32 Yaw)
{
    _Yaw = osgClamp(_YawClamp.x(), Yaw, _YawClamp.y());
}

void GLViewport::setRoll(Real32 Roll)
{
    _Roll = osgClamp(_RollClamp.x(), Roll, _RollClamp.y());
}

void GLViewport::setPitch(Real32 Pitch)
{
    _Pitch = osgClamp(_PitchClamp.x(), Pitch, _PitchClamp.y());
}

void GLViewport::setOffset(const Vec3f& Offset)
{
    _Offset.setValues(
                      osgClamp(_MinOffset.x(), Offset.x(), _MaxOffset.x()),
                      osgClamp(_MinOffset.y(), Offset.y(), _MaxOffset.y()),
                      osgClamp(_MinOffset.z(), Offset.z(), _MaxOffset.z()));

    updateView();
}



void GLViewport::updateNavigatorConnections(void)
{
    //Set up Navigator
    _Navigator.setViewport(getPort());
    _Navigator.setCameraTransformation(getPort()->getCamera()->getBeacon());
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GLViewport::GLViewport(void) :
    Inherited(),
        _Yaw(0.0f), _Pitch(0.0f), _Roll(0.0f),
        _InitialYaw(0.0f), _InitialPitch(0.0f), _InitialRoll(0.0f),
        _YawMultiplier(1.0f), _PitchMultiplier(1.0f), _RollMultiplier(1.0f),
        _YawClamp(0.0f, 6.2831853f), _PitchClamp(0.0f, 6.2831853f), _RollClamp(0.0f, 6.2831853f),
        _Offset(0.0f,0.0f,0.0f),
        _OffsetMultipliers(0.0f,0.0f,0.0f),
        _MinOffset(0.0f,0.0f,0.0f),
        _MaxOffset(0.0f,0.0f,0.0f)
{
	_Action = RenderAction::create();
	_Navigator.setMode(Navigator::TRACKBALL);
	_Navigator.setClickCenter(false);
}

GLViewport::GLViewport(const GLViewport &source) :
    Inherited(source),
        _Yaw(source._Yaw), _Pitch(source._Pitch), _Roll(source._Roll),
        _InitialYaw(source._InitialYaw), _InitialPitch(source._InitialPitch), _InitialRoll(source._InitialRoll),
        _YawMultiplier(source._YawMultiplier), _PitchMultiplier(source._PitchMultiplier), _RollMultiplier(source._RollMultiplier),
        _YawClamp(source._YawClamp), _PitchClamp(source._PitchClamp), _RollClamp(source._RollClamp),
        _Offset(source._Offset),
        _OffsetMultipliers(source._OffsetMultipliers),
        _MinOffset(source._MinOffset),
        _MaxOffset(source._MaxOffset)
{
	_Action = RenderAction::create();
	_Navigator.setMode(Navigator::TRACKBALL);
	_Navigator.setClickCenter(false);
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

	if((whichField & PortFieldMask) &&
        getPort() != NULL)
	{
		updateNavigatorConnections();
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
		    _Navigator.buttonRelease(Navigator::MIDDLE_MOUSE,e->getLocation().x(),e->getLocation().y());
		    MouseButtons = 2;
		    break;
	    case MouseEventDetails::BUTTON3:
		    _Navigator.buttonRelease(Navigator::RIGHT_MOUSE,e->getLocation().x(),e->getLocation().y());
		    MouseButtons = 4;
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

    }
    else
    {
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
		    MouseButtons = 2;
		    break;
	    case MouseEventDetails::BUTTON3:
		    MouseButtons = 4;
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
    }
    else
    {
        setYaw( _InitialYaw + (_InitialMousePos.x() - e->getLocation().x())*_YawMultiplier );
        setPitch( _InitialPitch + (_InitialMousePos.y() - e->getLocation().y())*_PitchMultiplier );
        updateView();
    }
}

void GLViewport::set(const Matrix& m)
{
	_Navigator.set(m);
}

void GLViewport::handleNavKeyPressed(KeyEventDetails* const e)
{
    if(_Navigator.getMode() != Navigator::NONE)
    {
	    if(e->getKey() == KeyEventDetails::KEY_ESCAPE)
	    {
		    _Navigator.set(_InitialMat);
            _NavMouseReleasedConnection.disconnect();
            _NavMouseDraggedConnection.disconnect();
            _NavKeyPressedConnection.disconnect();
	    }
    }
    else
    {
    }
}

OSG_END_NAMESPACE
