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

#include "OSGUIViewport.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::UIViewport
A UI UIViewport 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void UIViewport::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

EventConnection UIViewport::addChangeListener(ChangeListenerPtr Listener)
{
   _ChangeListeners.insert(Listener);
   return EventConnection(
       boost::bind(&UIViewport::isChangeListenerAttached, this, Listener),
       boost::bind(&UIViewport::removeChangeListener, this, Listener));
}

void UIViewport::getViewBounds(Pnt2f& TopLeft, Pnt2f& BottomRight)
{
	Pnt2f InsetsTopLeft, InsetsBottomRight;
	getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);

	TopLeft = getViewPosition();
	BottomRight = TopLeft + (InsetsBottomRight - InsetsTopLeft);
}

void UIViewport::maximizeVisibility(const Pnt2f& TopLeft, const Pnt2f& BottomRight)
{
	//Scroll as little as possible until as much as can be is visible

	Pnt2f ViewTopLeft, ViewBottomRight;
	getViewBounds(ViewTopLeft,ViewBottomRight);

	Pnt2f NewViewPosition(getViewPosition());

	//Vertical
	if(ViewTopLeft.y() > TopLeft.y())
	{
		//Scroll up
		NewViewPosition[1] = TopLeft.y();

	}
	else if(ViewBottomRight.y() < BottomRight.y())
	{
		Pnt2f InsetsTopLeft, InsetsBottomRight;
		getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);
		//Scroll down
		NewViewPosition[1] = BottomRight.y() - (InsetsBottomRight - InsetsTopLeft).y();
	}

	//Horizontal
	if(ViewTopLeft.x() > TopLeft.x())
	{
		//Scroll left
		NewViewPosition[0] = TopLeft.x();

	}
	else if(ViewBottomRight.x() < BottomRight.x())
	{
		Pnt2f InsetsTopLeft, InsetsBottomRight;
		getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);

		//Scroll right
		NewViewPosition[0] = BottomRight.x() - (InsetsBottomRight - InsetsTopLeft).x();
	}

	beginEditCP(UIViewportPtr(this), ViewPositionFieldMask);
		setViewPosition(NewViewPosition);
	endEditCP(UIViewportPtr(this), ViewPositionFieldMask);
}

void UIViewport::removeChangeListener(ChangeListenerPtr Listener)
{
   ChangeListenerSetItor EraseIter(_ChangeListeners.find(Listener));
   if(EraseIter != _ChangeListeners.end())
   {
      _ChangeListeners.erase(EraseIter);
   }
}

void UIViewport::updateLayout(void)
{
    if(getViewComponent() != NullFC)
    {
        Vec2f Size(getCorrectedViewSize());
        
        beginEditCP(getViewComponent(), Component::PositionFieldMask);
            getViewComponent()->setPosition(-getViewPosition());
        endEditCP(getViewComponent(), Component::PositionFieldMask);
		updateViewComponentSize();
        
        produceStateChanged(ChangeEvent(NullFC, getSystemTime(), ChangeEvent::STATE_CHANGED));
    }
}

void UIViewport::produceStateChanged(const ChangeEvent& e)
{
    ChangeListenerSet ListenerSet(_ChangeListeners);
    for(ChangeListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
	    (*SetItor)->stateChanged(e);
    }
}

Vec2f UIViewport::getCorrectedViewSize(void) const
{
    if(getViewSize() != Vec2f(-1,-1))
    {
        return getViewSize();
    }
    else
    {
        return getViewComponent()->getPreferredSize();
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

UIViewport::UIViewport(void) :
    Inherited()
{
}

UIViewport::UIViewport(const UIViewport &source) :
    Inherited(source)
{
}

UIViewport::~UIViewport(void)
{
}

/*----------------------------- class specific ----------------------------*/

void UIViewport::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & ViewComponentFieldMask)
    {
        beginEditCP(UIViewportPtr(this), ChildrenFieldMask);
            getChildren().clear();
            if(getViewComponent() != NullFC)
            {
                getChildren().push_back(getViewComponent());
            }
        endEditCP(UIViewportPtr(this), ChildrenFieldMask);
    }

    if((whichField & ViewSizeFieldMask) && getViewComponent() != NullFC)
    {
		updateViewComponentSize();
        
		produceStateChanged(ChangeEvent(NullFC, getSystemTime(), ChangeEvent::STATE_CHANGED));
    }

    if((whichField & ViewPositionFieldMask) && getViewComponent() != NullFC)
    {
		beginEditCP(getViewComponent(), Component::PositionFieldMask);
			getViewComponent()->setPosition(-getViewPosition());
		endEditCP(getViewComponent(), Component::PositionFieldMask);
        
		produceStateChanged(ChangeEvent(NullFC, getSystemTime(), ChangeEvent::STATE_CHANGED));
    }

    if((whichField & ViewSizeFieldMask) ||
        (whichField & ViewPositionFieldMask) ||
        (whichField & SizeFieldMask))
    {
        produceStateChanged(ChangeEvent(NullFC, getSystemTime(), ChangeEvent::STATE_CHANGED));
    }
    
    if(whichField & SizeFieldMask &&
       getViewComponent() != NullFC &&
       (getViewComponent()->getScrollableTracksViewportHeight() || getViewComponent()->getScrollableTracksViewportWidth()))
    {
		updateViewComponentSize();
    }
}

void UIViewport::updateViewComponentSize(void)
{
	Pnt2f InsetsTopLeft, InsetsBottomRight;
	getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);

    Vec2f Size(getCorrectedViewSize());
    
    if(getViewComponent()->getScrollableTracksViewportHeight())
    {
        Size[1] = (InsetsBottomRight - InsetsTopLeft).y();
    }
    
    if(getViewComponent()->getScrollableTracksViewportWidth())
    {
        Size[0] = (InsetsBottomRight - InsetsTopLeft).x();
    }
    beginEditCP(getViewComponent(), Component::SizeFieldMask);
        getViewComponent()->setSize(Size);
    endEditCP(getViewComponent(), Component::SizeFieldMask);
}

void UIViewport::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump UIViewport NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGUIVIEWPORTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGUIVIEWPORTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGUIVIEWPORTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

