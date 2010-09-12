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

#include "OSGAbstractWindow.h"

#include "OSGUIDrawingSurface.h"
#include "OSGUIDrawUtils.h"
#include "OSGBorder.h"
#include "OSGLayer.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAbstractWindowBase.cpp file.
// To modify it, please change the .fcd file (OSGAbstractWindow.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractWindow::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

UIDrawingSurface* AbstractWindow::getParentDrawingSurface(void) const
{
    return dynamic_cast<UIDrawingSurface*>(_sfParentDrawingSurface.getValue());
}

void AbstractWindow::updateContainerLayout(void)
{
    if(getParentContainer() != NULL)
    {
		Inherited::updateContainerLayout();
    }
	else if(getSize() != getPreferredSize())
	{
		Vec2f Size(osgMax(osgMin(getPreferredSize().x(), getMaxSize().x()), getMinSize().x()),
			       osgMax(osgMin(getPreferredSize().y(), getMaxSize().y()), getMinSize().y()));
        if(getSize() != Size)
        {
			setSize(Size);
        }
	}
}

void AbstractWindow::updateClipBounds(void)
{
	Pnt2f TopLeft, BottomRight;
	if( getParentDrawingSurface() == NULL )
	{
		//If I have no parent container use my bounds
		getBounds(TopLeft, BottomRight);
	}
	else
	{
		//Get the intersection of:
		     //My Bounds
		     //My Parent Containers Clip Bounds
		     //My Parent Containers Inset Bounds
        Pnt2f MyTopLeft,MyBottomRight;
        getBounds(MyTopLeft,MyBottomRight);

		//Get Parent Container's Clip Bounds
		Pnt2f ContainerClipTopLeft(0,0), ContainerClipBottomRight(getParentDrawingSurface()->getSize());
		
        //Parent Container's Clip Bounds are in the Parent Container's Coordinate space
        //We need to convert them to this Components Coordinate space
        ContainerClipTopLeft -= Vec2f(getPosition());
		ContainerClipBottomRight -= Vec2f(getPosition());

		//Get the intersection of my bounds with my parent containers clip bounds
		quadIntersection(MyTopLeft,MyBottomRight,
			ContainerClipTopLeft,ContainerClipBottomRight,
			TopLeft, BottomRight);
	}
	//The Clip Bounds calculated are in my Parent Containers coordinate space
	//Translate these bounds into my own coordinate space
		setClipTopLeft(TopLeft);
		setClipBottomRight(BottomRight);
}

Border* AbstractWindow::getDrawnBorder(void) const
{
    if(getDrawDecorations())
    {
        if(getEnabled())
        {
            if(getFocused())
            {
                return getFocusedBorder();
            }
            else if(_MouseInComponentLastMouse)
            {
                return getRolloverBorder();
            }
            else
            {
                return getBorder();
            }
        }
        else
        {
            return getDisabledBorder();
        }
    }
    else
    {
        return NULL;
    }
}

Layer* AbstractWindow::getDrawnBackground(void) const
{
	if(getDrawDecorations())
    {
        if(getEnabled())
        {
            if(getFocused())
            {
                return getFocusedBackground();
            }
            else if(_MouseInComponentLastMouse)
            {
                return getRolloverBackground();
            }
            else
            {
                return getBackground();
            }
        }
        else
        {
            return getDisabledBackground();
        }
    }
	else
	{
		return NULL;
	}
}

Layer* AbstractWindow::getDrawnForeground(void) const
{
	if(getDrawDecorations())
    {
        if(getEnabled())
        {
            if(getFocused())
            {
                return getFocusedForeground();
            }
            else if(_MouseInComponentLastMouse)
            {
                return getRolloverForeground();
            }
            else
            {
                return getForeground();
            }
        }
        else
        {
            return getDisabledForeground();
        }
    }
    else
	{
		return NULL;
	}
}


void AbstractWindow::produceWindowOpened(void)
{
   WindowEventDetailsUnrecPtr Details = WindowEventDetails::create( this, getSystemTime() );

   Inherited::produceWindowOpened(Details);
}

void AbstractWindow::produceWindowClosing(void)
{
   WindowEventDetailsUnrecPtr Details = WindowEventDetails::create( this, getSystemTime() );

   Inherited::produceWindowClosing(Details);
}

void AbstractWindow::produceWindowClosed(void)
{
   WindowEventDetailsUnrecPtr Details = WindowEventDetails::create( NULL, getSystemTime() );

   Inherited::produceWindowClosed(Details);
}

void AbstractWindow::produceWindowIconified(void)
{
   WindowEventDetailsUnrecPtr Details = WindowEventDetails::create( this, getSystemTime() );

   Inherited::produceWindowIconified(Details);
}

void AbstractWindow::produceWindowDeiconified(void)
{
   WindowEventDetailsUnrecPtr Details = WindowEventDetails::create( this, getSystemTime() );

   Inherited::produceWindowDeiconified(Details);
}

void AbstractWindow::produceWindowActivated(void)
{
   WindowEventDetailsUnrecPtr Details = WindowEventDetails::create( this, getSystemTime() );

   Inherited::produceWindowActivated(Details);
}

void AbstractWindow::produceWindowDeactivated(void)
{
   WindowEventDetailsUnrecPtr Details = WindowEventDetails::create( this, getSystemTime() );

   Inherited::produceWindowDeactivated(Details);
}

void AbstractWindow::produceWindowEntered(void)
{
   WindowEventDetailsUnrecPtr Details = WindowEventDetails::create( this, getSystemTime() );

   Inherited::produceWindowEntered(Details);
}

void AbstractWindow::produceWindowExited(void)
{
   WindowEventDetailsUnrecPtr Details = WindowEventDetails::create( this, getSystemTime() );

   Inherited::produceWindowExited(Details);
}

void AbstractWindow::focusGained(FocusEventDetails* const e)
{
	Inherited::focusGained(e);
	produceWindowActivated();
}

void AbstractWindow::focusLost(FocusEventDetails* const e)
{
	Inherited::focusLost(e);
	produceWindowDeactivated();
}

void AbstractWindow::mouseEntered(MouseEventDetails* const e)
{
	Inherited::mouseEntered(e);
	produceWindowEntered();
}

void AbstractWindow::mouseExited(MouseEventDetails* const e)
{
	Inherited::mouseExited(e);
	produceWindowExited();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbstractWindow::AbstractWindow(void) :
    Inherited(),
	_VetoWindowClose(false)
{
}

AbstractWindow::AbstractWindow(const AbstractWindow &source) :
    Inherited(source),
	_VetoWindowClose(false)
{
}

AbstractWindow::~AbstractWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractWindow::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if( whichField & (AlignmentInDrawingSurfaceFieldMask |
                      ScalingInDrawingSurfaceFieldMask))
    {
        updateContainerLayout();
    }
}

void AbstractWindow::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AbstractWindow NI" << std::endl;
}

OSG_END_NAMESPACE
