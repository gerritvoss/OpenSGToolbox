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

#include <OpenSG/OSGConfig.h>

#include "OSGContainer.h"
#include "Util/OSGUIDrawUtils.h"

#include <OpenSG/Input/OSGMouseEvent.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Container
A UI Container. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Container::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Container::getInsideInsetsBounds(Pnt2s& TopLeft, Pnt2s& BottomRight) const
{
   getInsideBorderBounds(TopLeft, BottomRight);

   TopLeft[0] += getLeftInset();
   TopLeft[1] += getTopInset();
   BottomRight[0] -= getRightInset();
   BottomRight[1] -= getBottomInset();
}

void Container::setAllInsets(UInt32 inset)
{
	beginEditCP(ContainerPtr(this), Container::LeftInsetFieldMask | Container::RightInsetFieldMask | Container::TopInsetFieldMask | Container::BottomInsetFieldMask);
		setLeftInset(inset);
		setRightInset(inset);
		setTopInset(inset);
		setBottomInset(inset);
	endEditCP(ContainerPtr(this), Container::LeftInsetFieldMask | Container::RightInsetFieldMask | Container::TopInsetFieldMask | Container::BottomInsetFieldMask);
}

void Container::drawInternal(const GraphicsPtr TheGraphics) const
{
    //Render all of my Child Components
	Pnt2s borderTopLeft, BorderBottomRight;
	//getInsideInsetsBounds(borderTopLeft, BorderBottomRight);
    //glTranslatef(borderTopLeft.x(), borderTopLeft.y(), 0);
    for(UInt32 i(0) ; i<getChildren().size() ; ++i)
    {
        getChildren().getValue(i)->draw(TheGraphics);
    }
    //glTranslatef(-borderTopLeft.x(), -borderTopLeft.y(), 0);
}
void Container::mouseClicked(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(getChildren().size()-1) ; i>=0 ; --i)
    {
		isContained = isPointInComponent(e.getLocation(), getChildren().getValue(i));
		checkMouseEnterExit(e,e.getLocation(),getChildren().getValue(i),isContained,e.getViewport());
		if(isContained)
		{
			getChildren().getValue(i)->mouseClicked(e);
			break;
		}
    }
	Component::mouseClicked(e);
}

void Container::mouseEntered(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(0) ; i<getChildren().size() ; ++i)
    {
		isContained = isPointInComponent(e.getLocation(), getChildren().getValue(i));
		checkMouseEnterExit(e,e.getLocation(),getChildren().getValue(i),isContained,e.getViewport());
		if(isContained)
		{
			getChildren().getValue(i)->mouseDragged(e);
		}
    }
	Component::mouseEntered(e);
}

void Container::mouseExited(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(0) ; i<getChildren().size() ; ++i)
    {
		isContained = isPointInComponent(e.getLocation(), getChildren().getValue(i));
		checkMouseEnterExit(e,e.getLocation(),getChildren().getValue(i),isContained,e.getViewport());
		if(isContained)
		{
			getChildren().getValue(i)->mouseDragged(e);
		}
    }
	Component::mouseExited(e);
}

void Container::mousePressed(const MouseEvent& e)
{
	bool isContained(false);
    for(Int32 i(getChildren().size()-1) ; i>=0 ; --i)
    {
		isContained = isPointInComponent(e.getLocation(), getChildren().getValue(i));
		checkMouseEnterExit(e,e.getLocation(),getChildren().getValue(i),isContained,e.getViewport());
		if(isContained)
		{
			//Give myself temporary focus
			takeFocus(true);
			if(!getChildren().getValue(i)->getType().isDerivedFrom(Container::getClassType()))
			{
				getChildren().getValue(i)->takeFocus();
			}
			getChildren().getValue(i)->mousePressed(e);
			break;
		}
    }
	if(isContained)
	{
		//Remove my temporary focus
		giveFocus(NullFC, false);
	}
	else
	{
		//Give myself permenant focus
		takeFocus();
	}
	Component::mousePressed(e);
}

void Container::mouseReleased(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(getChildren().size()-1) ; i>=0 ; --i)
    {
		isContained = isPointInComponent(e.getLocation(), getChildren().getValue(i));
		checkMouseEnterExit(e,e.getLocation(),getChildren().getValue(i),isContained,e.getViewport());
		if(isContained)
		{
			getChildren().getValue(i)->mouseReleased(e);
			break;
		}
    }
	Component::mouseReleased(e);
}


void Container::mouseMoved(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(0) ; i<getChildren().size() ; ++i)
    {
		isContained = isPointInComponent(e.getLocation(), getChildren().getValue(i));
		checkMouseEnterExit(e,e.getLocation(),getChildren().getValue(i),isContained,e.getViewport());
		if(isContained)
		{
			getChildren().getValue(i)->mouseMoved(e);
		}
    }
	Component::mouseMoved(e);
}

void Container::mouseDragged(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(0) ; i<getChildren().size() ; ++i)
    {
		isContained = isPointInComponent(e.getLocation(), getChildren().getValue(i));
		checkMouseEnterExit(e,e.getLocation(),getChildren().getValue(i),isContained,e.getViewport());
		if(isContained)
		{
			getChildren().getValue(i)->mouseDragged(e);
		}
    }
	Component::mouseDragged(e);
}

void Container::mouseWheelMoved(const MouseWheelEvent& e)
{
	bool isContained;
    for(Int32 i(0) ; i<getChildren().size() ; ++i)
    {
		isContained = isContainedClipBounds(e.getLocation(), getChildren().getValue(i));
		checkMouseEnterExit(e,e.getLocation(),getChildren().getValue(i),isContained,e.getViewport());
    }
	Component::mouseWheelMoved(e);
}

void Container::checkMouseEnterExit(const Event& e, const Pnt2s& MouseLocation, ComponentPtr Comp, bool isMouseContained, ViewportPtr TheViewport)
{
	//Check if mouse is inside of the frame
	if(!isMouseContained)
	{
		if(Comp->getMouseContained())
		{
		    //Mouse has exited the frame
			MouseEvent ExitedEvent(e.getSource(), e.getTimeStamp(), MouseEvent::NO_BUTTON,0,MouseLocation,TheViewport);
			Comp->mouseExited(ExitedEvent);
		}
		Comp->setMouseContained(false);
	}
	else
	{
		if(!Comp->getMouseContained())
		{
			//Mouse has exited the frame
			MouseEvent EnteredEvent(e.getSource(), e.getTimeStamp(), MouseEvent::NO_BUTTON,0,MouseLocation,TheViewport);
			Comp->mouseEntered(EnteredEvent);
		}
		Comp->setMouseContained(true);
	}
}

bool Container::isPointInComponent(const Pnt2s& Point, const ComponentPtr Comp)
{
	//Pnt2s borderTopLeft, BorderBottomRight;
	//getInsideInsetsBounds(borderTopLeft, BorderBottomRight);
	return isContainedClipBounds(Point, Comp);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Container::Container(void) :
    Inherited()
{
}

Container::Container(const Container &source) :
    Inherited(source)
{
}

Container::~Container(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Container::changed(BitVector whichField, UInt32 origin)
{

    if( (whichField & ChildrenFieldMask) ||
        (whichField & ParentFrameFieldMask))
    {
        //Set All of my children's parent to me
        for(UInt32 i(0) ; i<getChildren().size() ; ++i)
        {
            beginEditCP(getChildren().getValue(i), ParentContainerFieldMask | ParentFrameFieldMask);
               getChildren().getValue(i)->setParentContainer(ContainerPtr(this));
               getChildren().getValue(i)->setParentFrame(getParentFrame());
            endEditCP(getChildren().getValue(i), ParentContainerFieldMask | ParentFrameFieldMask);
        }
    }
    if( (whichField & LayoutFieldMask) &&
        getLayout() != NullFC)
    {
        beginEditCP(getLayout(), Layout::ParentContainerFieldMask);
            getLayout()->setParentContainer(ContainerPtr(this));
        endEditCP(getLayout(), Layout::ParentContainerFieldMask);
    }
    
    if( (whichField & ClipTopLeftFieldMask) ||
		(whichField & ClipBottomRightFieldMask) )
	{
        //Set All of my children's parent to me
        for(UInt32 i(0) ; i<getChildren().size() ; ++i)
        {
			getChildren().getValue(i)->updateClipBounds();
        }
	}

    if( (whichField & LayoutFieldMask) ||
        (whichField & LeftInsetFieldMask) ||
        (whichField & RightInsetFieldMask) ||
        (whichField & TopInsetFieldMask) ||
        (whichField & BottomInsetFieldMask) ||
        (whichField & ChildrenFieldMask) ||
        (whichField & SizeFieldMask) ||
        (whichField & BorderFieldMask))
    {
        //Layout needs to be recalculated
        updateLayout();
    }
	
    Inherited::changed(whichField, origin);
}

void Container::updateLayout(void)
{
    //Update Layout
    if(getLayout() != NullFC)
    {
        getLayout()->updateLayout(getChildren(), ContainerPtr(this));
    }
}

void Container::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Container NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGCONTAINERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCONTAINERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCONTAINERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

