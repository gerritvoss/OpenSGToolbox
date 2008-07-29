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


Vec2f Container::getContentRequestedSize(void) const
{
	Pnt2f Minimum(0.0f,0.0f), Maximum(0.0f,0.0f);

	if(getChildren().size() > 0)
	{
		Pnt2f ChildTopLeft, ChildBottomRight, ChildPosition;

		getChildren()[0]->getBounds(ChildTopLeft, ChildBottomRight);
        ChildPosition = getChildren()[0]->getPosition();
        //These bounds are in the Components coordinate space,
        //we need to convert them to this containers coordinate space
        ChildTopLeft += Vec3f(ChildPosition);
        ChildBottomRight += Vec3f(ChildPosition);

		Minimum[0] = osgMin(ChildTopLeft.x(), ChildBottomRight.x());
		Minimum[1] = osgMin(ChildTopLeft.y(), ChildBottomRight.y());
		Maximum[0] = osgMax(ChildTopLeft.x(), ChildBottomRight.x());
		Maximum[1] = osgMax(ChildTopLeft.y(), ChildBottomRight.y());

		for(UInt32 i(1) ; i<getChildren().size() ; ++i)
		{
			getChildren()[i]->getBounds(ChildTopLeft, ChildBottomRight);
            ChildPosition = getChildren()[i]->getPosition();
            //These bounds are in the Components coordinate space,
            //we need to convert them to this containers coordinate space
            ChildTopLeft += Vec3f(ChildPosition);
            ChildBottomRight += Vec3f(ChildPosition);
			
			Minimum[0] = osgMin(osgMin(ChildTopLeft.x(), ChildBottomRight.x()), Minimum.x());
			Minimum[1] = osgMin(osgMin(ChildTopLeft.y(), ChildBottomRight.y()), Minimum.y());
			Maximum[0] = osgMax(osgMax(ChildTopLeft.x(), ChildBottomRight.x()), Maximum.x());
			Maximum[1] = osgMax(osgMax(ChildTopLeft.y(), ChildBottomRight.y()), Maximum.y());
		}
	}

	return Maximum - Minimum;
}

Vec2f Container::getBorderingLength(void) const
{
	Pnt2f BoundsTopLeft, BoundsBottomRight;
	Pnt2f InsideInsetsTopLeft, InsideInsetsBottomRight;
	
	getBounds(BoundsTopLeft, BoundsBottomRight);
	getInsideBorderBounds(InsideInsetsTopLeft, InsideInsetsBottomRight);
	
	return (BoundsBottomRight - BoundsTopLeft) - (InsideInsetsBottomRight - InsideInsetsTopLeft);
}

void Container::getInsideInsetsBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const
{
   getInsideBorderBounds(TopLeft, BottomRight);

   TopLeft[0] += getLeftInset();
   TopLeft[1] += getTopInset();
   BottomRight[0] -= getRightInset();
   BottomRight[1] -= getBottomInset();
}

void Container::setAllInsets(Real32 Inset)
{
	beginEditCP(ContainerPtr(this), Container::LeftInsetFieldMask | Container::RightInsetFieldMask | Container::TopInsetFieldMask | Container::BottomInsetFieldMask);
		setLeftInset(Inset);
		setRightInset(Inset);
		setTopInset(Inset);
		setBottomInset(Inset);
	endEditCP(ContainerPtr(this), Container::LeftInsetFieldMask | Container::RightInsetFieldMask | Container::TopInsetFieldMask | Container::BottomInsetFieldMask);
}

void Container::drawInternal(const GraphicsPtr TheGraphics) const
{
    //Render all of my Child Components
    for(UInt32 i(0) ; i<getChildren().size() ; ++i)
    {
        getChildren()[i]->draw(TheGraphics);
    }
}
void Container::mouseClicked(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(getChildren().size()-1) ; i>=0 ; --i)
    {
        isContained = getChildren()[i]->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getChildren()[i],isContained,e.getViewport());
		if(isContained)
		{
			getChildren()[i]->mouseClicked(e);
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
        isContained = getChildren()[i]->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getChildren()[i],isContained,e.getViewport());
    }
	Component::mouseEntered(e);
}

void Container::mouseExited(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(0) ; i<getChildren().size() ; ++i)
    {
        isContained = getChildren()[i]->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getChildren()[i],isContained,e.getViewport());
    }
	Component::mouseExited(e);
}

void Container::mousePressed(const MouseEvent& e)
{
	bool isContained(false);
    for(Int32 i(getChildren().size()-1) ; i>=0 ; --i)
    {
        isContained = getChildren()[i]->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getChildren()[i],isContained,e.getViewport());
		if(isContained)
		{
			//Give myself temporary focus
			takeFocus(true);
			if(!getChildren()[i]->getType().isDerivedFrom(Container::getClassType()))
			{
				getChildren()[i]->takeFocus();
			}
			getChildren()[i]->mousePressed(e);
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
        isContained = getChildren()[i]->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getChildren()[i],isContained,e.getViewport());
		if(isContained)
		{
			getChildren()[i]->mouseReleased(e);
			break;
		}
    }
	Component::mouseReleased(e);
}


void Container::mouseMoved(const MouseEvent& e)
{
	Component::mouseMoved(e);

	bool isContained;
	bool isContainedAbove(false);
    for(Int32 i(getChildren().size()-1) ; i>=0 ; --i)
    {
        isContained = getChildren()[i]->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getChildren()[i],isContained && !isContainedAbove,e.getViewport());
		if(isContained && !isContainedAbove)
		{
			isContainedAbove = true;
			getChildren()[i]->mouseMoved(e);
		}
    }
}

void Container::mouseDragged(const MouseEvent& e)
{
	bool isContained;
	bool isContainedAbove(false);
    for(Int32 i(getChildren().size()-1) ; i>=0 ; --i)
    {
        isContained = getChildren()[i]->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getChildren()[i],isContained && !isContainedAbove,e.getViewport());
		if(isContained && !isContainedAbove)
		{
			isContainedAbove = true;
			getChildren()[i]->mouseDragged(e);
		}
    }
	Component::mouseDragged(e);
}

void Container::mouseWheelMoved(const MouseWheelEvent& e)
{
	bool isContained;
    for(Int32 i(0) ; i<getChildren().size() ; ++i)
    {
        isContained = getChildren()[i]->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getChildren()[i],isContained,e.getViewport());
		if(isContained)
		{
			getChildren()[i]->mouseWheelMoved(e);
        }
    }
	Component::mouseWheelMoved(e);
}

void Container::produceMouseExitOnComponent(const MouseEvent& e, ComponentPtr Comp)
{
	Comp->mouseExited(e);
}

void Container::produceMouseEnterOnComponent(const MouseEvent& e, ComponentPtr Comp)
{
	Comp->mouseEntered(e);
}

void Container::checkMouseEnterExit(const InputEvent& e, const Pnt2f& MouseLocation, ComponentPtr Comp, bool isMouseContained, ViewportPtr TheViewport)
{
	//Check if mouse is inside of this component
	if(!isMouseContained)
	{
		if(Comp->getMouseContained())
		{
		    //Mouse has exited the component
			MouseEvent ExitedEvent(e.getSource(), e.getTimeStamp(), e.getEventProducer(), MouseEvent::NO_BUTTON,0,MouseLocation,TheViewport);
			produceMouseExitOnComponent(ExitedEvent, Comp);
		}
		Comp->setMouseContained(false);
	}
	else
	{
		if(!Comp->getMouseContained())
		{
			//Mouse has exited the frame
			MouseEvent EnteredEvent(e.getSource(), e.getTimeStamp(), e.getEventProducer(), MouseEvent::NO_BUTTON,0,MouseLocation,TheViewport);
			produceMouseEnterOnComponent(EnteredEvent, Comp);
		}
		Comp->setMouseContained(true);
	}
}

void Container::removeMousePresenceOnComponents(void)
{
    for(UInt32 i(0) ; i<getChildren().size() ; ++i)
    {
        getChildren()[i]->setMouseContained(false);
    }
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
        (whichField & ParentWindowFieldMask))
    {
        //Set All of my children's parent to me
        for(UInt32 i(0) ; i<getChildren().size() ; ++i)
        {
            beginEditCP(getChildren()[i], ParentContainerFieldMask | ParentWindowFieldMask);
               getChildren()[i]->setParentContainer(ContainerPtr(this));
               getChildren()[i]->setParentWindow(getParentWindow());
            endEditCP(getChildren()[i], ParentContainerFieldMask | ParentWindowFieldMask);
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
			getChildren()[i]->updateClipBounds();
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
	
    if(whichField & EnabledFieldMask)
    {
        for(UInt32 i(0) ; i< getChildren().size() ; ++i)
        {
            beginEditCP(getChildren()[i], EnabledFieldMask);
                getChildren()[i]->setEnabled(getEnabled());
            endEditCP(getChildren()[i], EnabledFieldMask);
        }
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

