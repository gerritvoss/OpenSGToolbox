/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#include "OSGUIDrawingSurface.h"
#include "Util/OSGUIDrawUtils.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::UIDrawingSurface
A UI DrawingSurface. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void UIDrawingSurface::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void UIDrawingSurface::mouseClicked(const MouseEvent& e)
{
	if(getRootFrame() != NullFC)
	{
		checkMouseEnterExit(e, e.getLocation());
		if(isContainedClipBounds(e.getLocation(), getRootFrame()))
		{
			getRootFrame()->mouseClicked(e);
		}
	}
}

void UIDrawingSurface::mouseEntered(const MouseEvent& e)
{
	checkMouseEnterExit(e, e.getLocation());
}

void UIDrawingSurface::mouseExited(const MouseEvent& e)
{
	checkMouseEnterExit(e, e.getLocation());
}

void UIDrawingSurface::mousePressed(const MouseEvent& e)
{
	if(getRootFrame() != NullFC)
	{
		checkMouseEnterExit(e, e.getLocation());
		if(isContainedClipBounds(e.getLocation(), getRootFrame()))
		{
			getRootFrame()->mousePressed(e);
		}
	}
}

void UIDrawingSurface::mouseReleased(const MouseEvent& e)
{
	if(getRootFrame() != NullFC)
	{
		checkMouseEnterExit(e, e.getLocation());
		if(isContainedClipBounds(e.getLocation(), getRootFrame()))
		{
			getRootFrame()->mouseReleased(e);
		}
	}
}


void UIDrawingSurface::mouseMoved(const MouseEvent& e)
{
	if(getRootFrame() != NullFC)
	{
		checkMouseEnterExit(e, e.getLocation());
		if(isContainedClipBounds(e.getLocation(), getRootFrame()))
		{
			getRootFrame()->mouseMoved(e);
		}
	}
}

void UIDrawingSurface::mouseDragged(const MouseEvent& e)
{
	if(getRootFrame() != NullFC)
	{
		checkMouseEnterExit(e, e.getLocation());
		if(isContainedClipBounds(e.getLocation(), getRootFrame()))
		{
			getRootFrame()->mouseDragged(e);
		}
	}
}

void UIDrawingSurface::mouseWheelMoved(const MouseWheelEvent& e)
{
	if(getRootFrame() != NullFC)
	{
		checkMouseEnterExit(e, e.getLocation());
	    getRootFrame()->mouseWheelMoved(e);
	}
}

void UIDrawingSurface::keyPressed(const KeyEvent& e)
{
	if((getRootFrame() != NullFC))
	{
		getRootFrame()->keyPressed(e);
	}
}

void UIDrawingSurface::keyReleased(const KeyEvent& e)
{
	if((getRootFrame() != NullFC))
	{
		getRootFrame()->keyReleased(e);
	}
}

void UIDrawingSurface::keyTyped(const KeyEvent& e)
{
	if((getRootFrame() != NullFC))
	{
		getRootFrame()->keyTyped(e);
	}
}

void UIDrawingSurface::checkMouseEnterExit(const Event& e, const Pnt2s& MouseLocation)
{
	if(_MouseInFrameLastMouse)
	{
		//Check if mouse is outside of the frame
		if(!isContainedClipBounds(MouseLocation, getRootFrame()))
		{
			//Mouse has exited the frame
			_MouseInFrameLastMouse = !_MouseInFrameLastMouse;
			MouseEvent ExitedEvent(e.getSource(), e.getTimeStamp(), MouseEvent::NO_BUTTON,0,MouseLocation);
			getRootFrame()->mouseExited(ExitedEvent);
		}
	}
	else
	{
		//Check if mouse is inside of the frame
		if(isContainedClipBounds(MouseLocation, getRootFrame()))
		{
			//Mouse has exited the frame
			_MouseInFrameLastMouse = !_MouseInFrameLastMouse;
			MouseEvent EnteredEvent(e.getSource(), e.getTimeStamp(), MouseEvent::NO_BUTTON,0,MouseLocation);
			getRootFrame()->mouseEntered(EnteredEvent);
		}
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

UIDrawingSurface::UIDrawingSurface(void) :
    Inherited(),
		_MouseInFrameLastMouse(false)
{
}

UIDrawingSurface::UIDrawingSurface(const UIDrawingSurface &source) :
    Inherited(source),
		_MouseInFrameLastMouse(false)
{
}

UIDrawingSurface::~UIDrawingSurface(void)
{
}

/*----------------------------- class specific ----------------------------*/

void UIDrawingSurface::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
	
	if( (whichField & EventProducerFieldMask) )
    {
		//Remove Listeners from old EventProducer
		//Add Listeners to the EventProducer
		if(getEventProducer() != NullFC)
		{
			getEventProducer()->addMouseListener(this);
			getEventProducer()->addMouseMotionListener(this);
			getEventProducer()->addMouseWheelListener(this);
			getEventProducer()->addKeyListener(this);
		}
	}
}

void UIDrawingSurface::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump UIDrawingSurface NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGUIDRAWINGSURFACEBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGUIDRAWINGSURFACEBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGUIDRAWINGSURFACEFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

