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

#include "OSGRotatedComponent.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::RotatedComponent
A UI Button. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void RotatedComponent::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void RotatedComponent::drawInternal(const GraphicsPtr TheGraphics) const
{
    if(getInternalComponent() != NullFC)
    {
        glPushMatrix();
        glTranslatef(static_cast<Real32>(getSize().x())/2.0,static_cast<Real32>(getSize().y())/2.0,0.0);
        glRotatef(-osgrad2degree(getAngle()), 0.0,0.0,1.0);
        glTranslatef(-static_cast<Real32>(getInternalComponent()->getSize().x())/2.0,-static_cast<Real32>(getInternalComponent()->getSize().y())/2.0,0.0);
        getInternalComponent()->draw(TheGraphics);
        glPopMatrix();
    }
}

void RotatedComponent::updateLayout(void)
{
    Pnt2s TopLeft, BottomRight;
    getInsideInsetsBounds(TopLeft, BottomRight);
    
    for(UInt32 i(0) ; i<getChildren().size() ; ++i)
    {
        beginEditCP(getChildren().getValue(i),PositionFieldMask | SizeFieldMask);
            getChildren().getValue(i)->setPosition(Pnt2s(0,0));
            getChildren().getValue(i)->setSize(getChildren().getValue(i)->getPreferredSize());
        endEditCP(getChildren().getValue(i),PositionFieldMask | SizeFieldMask);
    }
}

void RotatedComponent::mouseClicked(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(getChildren().size()-1) ; i>=0 ; --i)
    {
        isContained = getChildren().getValue(i)->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getChildren().getValue(i),isContained,e.getViewport());
		if(isContained)
		{
			getChildren().getValue(i)->mouseClicked(e);
			break;
		}
    }
	Component::mouseClicked(e);
}

void RotatedComponent::mouseEntered(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(0) ; i<getChildren().size() ; ++i)
    {
        isContained = getChildren().getValue(i)->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getChildren().getValue(i),isContained,e.getViewport());
    }
	Component::mouseEntered(e);
}

void RotatedComponent::mouseExited(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(0) ; i<getChildren().size() ; ++i)
    {
        isContained = getChildren().getValue(i)->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getChildren().getValue(i),isContained,e.getViewport());
    }
	Component::mouseExited(e);
}

void RotatedComponent::mousePressed(const MouseEvent& e)
{
	bool isContained(false);
    for(Int32 i(getChildren().size()-1) ; i>=0 ; --i)
    {
        isContained = getChildren().getValue(i)->isContained(e.getLocation(), true);
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

void RotatedComponent::mouseReleased(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(getChildren().size()-1) ; i>=0 ; --i)
    {
        isContained = getChildren().getValue(i)->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getChildren().getValue(i),isContained,e.getViewport());
		if(isContained)
		{
			getChildren().getValue(i)->mouseReleased(e);
			break;
		}
    }
	Component::mouseReleased(e);
}


void RotatedComponent::mouseMoved(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(0) ; i<getChildren().size() ; ++i)
    {
        isContained = getChildren().getValue(i)->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getChildren().getValue(i),isContained,e.getViewport());
		if(isContained)
		{
			getChildren().getValue(i)->mouseMoved(e);
		}
    }
	Component::mouseMoved(e);
}

void RotatedComponent::mouseDragged(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(0) ; i<getChildren().size() ; ++i)
    {
        isContained = getChildren().getValue(i)->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getChildren().getValue(i),isContained,e.getViewport());
		if(isContained)
		{
			getChildren().getValue(i)->mouseDragged(e);
		}
    }
	Component::mouseDragged(e);
}

void RotatedComponent::mouseWheelMoved(const MouseWheelEvent& e)
{
	bool isContained;
    for(Int32 i(0) ; i<getChildren().size() ; ++i)
    {
        isContained = getChildren().getValue(i)->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getChildren().getValue(i),isContained,e.getViewport());
		if(isContained)
		{
			getChildren().getValue(i)->mouseWheelMoved(e);
        }
    }
	Component::mouseWheelMoved(e);
}

Pnt2s RotatedComponent::getLocalToInternalComponent(const Pnt2s& LocalPoint) const
{
    Pnt2s Result(LocalPoint);
    Result = Result - Vec2s(static_cast<Real32>(getSize().x())/2.0,static_cast<Real32>(getSize().y())/2.0);
    Result.setValues( Result[0]*osgcos(getAngle()) - Result[1]*osgsin(getAngle()), Result[0]*osgsin(getAngle()) + Result[1]*osgcos(getAngle()));
    Result = Result + Vec2s(static_cast<Real32>(getInternalComponent()->getSize().x())/2.0,static_cast<Real32>(getInternalComponent()->getSize().y())/2.0);
    return Result;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

RotatedComponent::RotatedComponent(void) :
    Inherited()
{
}

RotatedComponent::RotatedComponent(const RotatedComponent &source) :
    Inherited(source)
{
}

RotatedComponent::~RotatedComponent(void)
{
}

/*----------------------------- class specific ----------------------------*/

void RotatedComponent::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & InternalComponentFieldMask)
    {
        beginEditCP(RotatedComponentPtr(this), ChildrenFieldMask);
            getChildren().clear();
            if(getInternalComponent() != NullFC)
            {
                getChildren().push_back(getInternalComponent());
            }
        endEditCP(RotatedComponentPtr(this), ChildrenFieldMask);
        
        if(getInternalComponent() != NullFC)
        {
            //Calculate Preferred Size
            //Get the Internal Components Center
            Pnt2s ComponentCenter(static_cast<Real32>(getInternalComponent()->getSize().x())/2.0, static_cast<Real32>(getInternalComponent()->getSize().y())/2.0);
            //Get the distance from the Center to one of the TopLeft Corner
            Int16 Length = 2*ComponentCenter.dist(Pnt2s(0,0));
            beginEditCP(RotatedComponentPtr(this), PreferredSizeFieldMask);
                setPreferredSize(Vec2s(Length,Length));
            endEditCP(RotatedComponentPtr(this), PreferredSizeFieldMask);
        }
    }
}

void RotatedComponent::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump RotatedComponent NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGROTATEDCOMPONENTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGROTATEDCOMPONENTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGROTATEDCOMPONENTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

