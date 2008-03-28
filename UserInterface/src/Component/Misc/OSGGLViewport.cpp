/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBackground.h>
#include <OpenSG/OSGCamera.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include "Component/Container/Window/OSGInternalWindow.h"

#include "OSGGLViewport.h"
#include "Util/OSGUIDrawUtils.h"
#include <OpenSG/Toolbox/OSGCameraUtils.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::GLViewport
An OpenSG Viewport Component. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GLViewport::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
void GLViewport::drawInternal(const GraphicsPtr Graphics) const
{
	if(getPort() != NullFC)
	{
		Pnt2f InsideInsetTopLeft, InsideInsetBottomRight;
		getInsideBorderBounds(InsideInsetTopLeft,InsideInsetBottomRight);
		
		//Clamp Viewport Bounds with Window clip planes
		Pnt2f InsideInsetTopLeftToWindow, InsideInsetBottomRightToWindow;
		quadIntersection(InsideInsetTopLeft, InsideInsetBottomRight,
						getClipTopLeft(), getClipBottomRight(),
						InsideInsetTopLeftToWindow, InsideInsetBottomRightToWindow);


		InsideInsetTopLeftToWindow = ComponentToWindow(InsideInsetTopLeftToWindow,GLViewportPtr(this), ViewportPtr(Graphics->getDrawAction()->getViewport()));
		InsideInsetBottomRightToWindow = ComponentToWindow(InsideInsetBottomRightToWindow,GLViewportPtr(this), ViewportPtr(Graphics->getDrawAction()->getViewport()));



		if( getParentWindow() != NullFC &&
			getParentWindow()->getDrawingSurface() != NullFC &&
			getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC &&
			getParentWindow()->getDrawingSurface()->getEventProducer()->getWindow() != NullFC)
		{

			WindowPtr TheWindow = getParentWindow()->getDrawingSurface()->getEventProducer()->getWindow();

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
					beginEditCP(getPort()->getCamera(), PerspectiveCamera::FovFieldMask);
						PerspectiveCamera::Ptr::dcast(getPort()->getCamera())->setFov(
							60.0f *
							(abs(InsideInsetTopLeftToWindow.y() - InsideInsetBottomRightToWindow.y())/getSize().y())
							);
					endEditCP(getPort()->getCamera(), PerspectiveCamera::FovFieldMask);
				}
			}

			
		
			beginEditCP(getPort(), Viewport::LeftFieldMask | Viewport::RightFieldMask | Viewport::TopFieldMask | Viewport::BottomFieldMask);
				getPort()->setSize(InsideInsetTopLeftToWindow.x(), InsideInsetBottomRightToWindow.y(), InsideInsetBottomRightToWindow.x(), InsideInsetTopLeftToWindow.y());
			endEditCP(getPort(), Viewport::LeftFieldMask | Viewport::RightFieldMask | Viewport::TopFieldMask | Viewport::BottomFieldMask);


			_Navigator.updateCameraTransformation();

			beginEditCP(getPort(), Viewport::ParentFieldMask);
				getPort()->setParent(getParentWindow()->getDrawingSurface()->getEventProducer()->getWindow());
			endEditCP(getPort(), Viewport::ParentFieldMask);
			

			_Action->setWindow(getPort()->getParent().getCPtr());
			
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

			getPort()->render(_Action);

			
			Graphics->getDrawAction()->getViewport()->activate();

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

void GLViewport::mousePressed(const MouseEvent& e)
{
	Inherited::mousePressed(e);
	
	UInt16 MouseButtons;
	switch(e.getButton())
	{
	case MouseEvent::BUTTON1:
		_MouseControlListener.setInitialMat(_Navigator.getMatrix());
		_Navigator.buttonPress(Navigator::LEFT_MOUSE,e.getLocation().x(),e.getLocation().y());
		getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseListener(&_MouseControlListener);
		getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseMotionListener(&_MouseControlListener);
		getParentWindow()->getDrawingSurface()->getEventProducer()->addKeyListener(&_MouseControlListener);
				
		MouseButtons = 1;
		break;
	case MouseEvent::BUTTON2:
		_MouseControlListener.setInitialMat(_Navigator.getMatrix());
		_Navigator.buttonPress(Navigator::MIDDLE_MOUSE,e.getLocation().x(),e.getLocation().y());
		getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseListener(&_MouseControlListener);
		getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseMotionListener(&_MouseControlListener);
		getParentWindow()->getDrawingSurface()->getEventProducer()->addKeyListener(&_MouseControlListener);
		MouseButtons = 2;
		break;
	case MouseEvent::BUTTON3:
		_MouseControlListener.setInitialMat(_Navigator.getMatrix());
		_Navigator.buttonPress(Navigator::RIGHT_MOUSE,e.getLocation().x(),e.getLocation().y());
		getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseListener(&_MouseControlListener);
		getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseMotionListener(&_MouseControlListener);
		getParentWindow()->getDrawingSurface()->getEventProducer()->addKeyListener(&_MouseControlListener);
		MouseButtons = 4;
		break;
	}
	_Navigator.idle(MouseButtons,e.getLocation().x(),e.getLocation().y());
}

void GLViewport::keyTyped(const KeyEvent& e)
{
	Inherited::keyTyped(e);
	switch ( e.getKey() )
	{
	case KeyEvent::KEY_J:
	case KeyEvent::KEY_LEFT:
		_Navigator.keyPress(Navigator::LEFT,0,0);
		break;
	case KeyEvent::KEY_G:
	case KeyEvent::KEY_RIGHT:
			_Navigator.keyPress(Navigator::RIGHT,0,0);
			break;
	case KeyEvent::KEY_U:
			_Navigator.keyPress(Navigator::LEFTROT,0,0);
			break;
	case KeyEvent::KEY_T:
			_Navigator.keyPress(Navigator::RIGHTROT,0,0);
			break;
	case KeyEvent::KEY_Y:
	case KeyEvent::KEY_UP:
			_Navigator.keyPress(Navigator::FORWARDS,0,0);
			break;
	case KeyEvent::KEY_H:
	case KeyEvent::KEY_DOWN:
			_Navigator.keyPress(Navigator::BACKWARDS,0,0);
			break;
	}
}

void GLViewport::mouseWheelMoved(const MouseWheelEvent& e)
{
	if(e.getUnitsToScroll() > 0)
	{
		for(UInt32 i(0) ; i<e.getUnitsToScroll() ;++i)
		{
			_Navigator.buttonPress(Navigator::UP_MOUSE,e.getLocation().x(),e.getLocation().y());
			_Navigator.buttonRelease(Navigator::UP_MOUSE,e.getLocation().x(),e.getLocation().y());
		}
	}
	else if(e.getUnitsToScroll() < 0)
	{
		for(UInt32 i(0) ; i<abs(e.getUnitsToScroll()) ;++i)
		{
			_Navigator.buttonPress(Navigator::DOWN_MOUSE,e.getLocation().x(),e.getLocation().y());
			_Navigator.buttonRelease(Navigator::DOWN_MOUSE,e.getLocation().x(),e.getLocation().y());
		}
	}
}

void GLViewport::showAll(void)
{
    if(getPort() == NullFC ||
		getPort()->getRoot() == NullFC ||
		getPort()->getCamera() == NullFC ||
		!getPort()->getCamera()->getType().isDerivedFrom(PerspectiveCamera::getClassType()))
        return;

	//
	::osg::showAll(getPort()->getCamera(), getPort()->getRoot());
    _Navigator.set(getPort()->getCamera()->getBeacon()->getToWorld());

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

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GLViewport::GLViewport(void) :
    Inherited(),
		_MouseControlListener(GLViewportPtr(this))
{
	_Action = RenderAction::create();
	_Navigator.setMode(Navigator::TRACKBALL);
	_Navigator.setClickCenter(false);
}

GLViewport::GLViewport(const GLViewport &source) :
    Inherited(source),
		_MouseControlListener(GLViewportPtr(this))
{
	_Action = RenderAction::create();
	_Navigator.setMode(Navigator::TRACKBALL);
	_Navigator.setClickCenter(false);
}

GLViewport::~GLViewport(void)
{
	delete _Action;
}

/*----------------------------- class specific ----------------------------*/

void GLViewport::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

	if(whichField & PortFieldMask)
	{
		//Set up Navigator
		_Navigator.setViewport(getPort());
		_Navigator.setCameraTransformation(getPort()->getCamera()->getBeacon());
	}
}

void GLViewport::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump GLViewport NI" << std::endl;
}


void GLViewport::MouseControlListener::mouseReleased(const MouseEvent& e)
{
	
	UInt16 MouseButtons;
	switch(e.getButton())
	{
	case MouseEvent::BUTTON1:
		_GLViewport->_Navigator.buttonRelease(Navigator::LEFT_MOUSE,e.getLocation().x(),e.getLocation().y());
		MouseButtons = 1;
		break;
	case MouseEvent::BUTTON2:
		_GLViewport->_Navigator.buttonRelease(Navigator::MIDDLE_MOUSE,e.getLocation().x(),e.getLocation().y());
		MouseButtons = 2;
		break;
	case MouseEvent::BUTTON3:
		_GLViewport->_Navigator.buttonRelease(Navigator::RIGHT_MOUSE,e.getLocation().x(),e.getLocation().y());
		MouseButtons = 4;
		break;
	case MouseEvent::BUTTON4:
		MouseButtons = 8;
		break;
	case MouseEvent::BUTTON5:
		_GLViewport->_Navigator.buttonRelease(Navigator::DOWN_MOUSE,e.getLocation().x(),e.getLocation().y());
		MouseButtons = 16;
		break;
	}
	_GLViewport->_Navigator.idle(MouseButtons,e.getLocation().x(),e.getLocation().y());

	_GLViewport->getParentWindow()->getDrawingSurface()->getEventProducer()->removeMouseListener(this);
	_GLViewport->getParentWindow()->getDrawingSurface()->getEventProducer()->removeMouseMotionListener(this);
	_GLViewport->getParentWindow()->getDrawingSurface()->getEventProducer()->removeKeyListener(this);
}

void GLViewport::MouseControlListener::mouseDragged(const MouseEvent& e)
{

	UInt16 MouseButtons;
	switch(e.getButton())
	{
	case MouseEvent::BUTTON1:
		MouseButtons = 1;
		break;
	case MouseEvent::BUTTON2:
		MouseButtons = 2;
		break;
	case MouseEvent::BUTTON3:
		MouseButtons = 4;
		break;
	case MouseEvent::BUTTON4:
		MouseButtons = 8;
		break;
	case MouseEvent::BUTTON5:
		MouseButtons = 16;
		break;
	}
	_GLViewport->_Navigator.moveTo(e.getLocation().x(),e.getLocation().y());
	_GLViewport->_Navigator.idle(MouseButtons,e.getLocation().x(),e.getLocation().y());
}

void GLViewport::MouseControlListener::setInitialMat(const Matrix& Mat)
{
	_InitialMat = Mat;
}

void GLViewport::MouseControlListener::keyPressed(const KeyEvent& e)
{
	if(e.getKey() == KeyEvent::KEY_ESCAPE)
	{
		_GLViewport->_Navigator.set(_InitialMat);
		_GLViewport->getParentWindow()->getDrawingSurface()->getEventProducer()->removeMouseListener(this);
		_GLViewport->getParentWindow()->getDrawingSurface()->getEventProducer()->removeMouseMotionListener(this);
		_GLViewport->getParentWindow()->getDrawingSurface()->getEventProducer()->removeKeyListener(this);
	}
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGGLVIEWPORTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGGLVIEWPORTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGGLVIEWPORTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

