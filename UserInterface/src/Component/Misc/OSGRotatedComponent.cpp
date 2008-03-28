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
#include "Util/OSGUIDrawUtils.h"
#include "Component/Container/Window/OSGInternalWindow.h"

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
    Pnt2f TopLeft, BottomRight;
    getInsideInsetsBounds(TopLeft, BottomRight);
    
    for(UInt32 i(0) ; i<getChildren().size() ; ++i)
    {
        beginEditCP(getChildren()[i],PositionFieldMask | SizeFieldMask);
            getChildren()[i]->setPosition(Pnt2f(0,0));
            getChildren()[i]->setSize(getChildren()[i]->getPreferredSize());
        endEditCP(getChildren()[i],PositionFieldMask | SizeFieldMask);
    }
}

void RotatedComponent::mouseClicked(const MouseEvent& e)
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

void RotatedComponent::mouseEntered(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(0) ; i<getChildren().size() ; ++i)
    {
        isContained = getChildren()[i]->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getChildren()[i],isContained,e.getViewport());
    }
	Component::mouseEntered(e);
}

void RotatedComponent::mouseExited(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(0) ; i<getChildren().size() ; ++i)
    {
        isContained = getChildren()[i]->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getChildren()[i],isContained,e.getViewport());
    }
	Component::mouseExited(e);
}

void RotatedComponent::mousePressed(const MouseEvent& e)
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

void RotatedComponent::mouseReleased(const MouseEvent& e)
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


void RotatedComponent::mouseMoved(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(0) ; i<getChildren().size() ; ++i)
    {
        isContained = getChildren()[i]->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getChildren()[i],isContained,e.getViewport());
		if(isContained)
		{
			getChildren()[i]->mouseMoved(e);
		}
    }
	Component::mouseMoved(e);
}

void RotatedComponent::mouseDragged(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(0) ; i<getChildren().size() ; ++i)
    {
        isContained = getChildren()[i]->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getChildren()[i],isContained,e.getViewport());
		if(isContained)
		{
			getChildren()[i]->mouseDragged(e);
		}
    }
	Component::mouseDragged(e);
}

void RotatedComponent::mouseWheelMoved(const MouseWheelEvent& e)
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

Pnt2f RotatedComponent::getLocalToInternalComponent(const Pnt2f& LocalPoint) const
{
    Pnt2f Result(LocalPoint);
    Result = Result - Vec2f(static_cast<Real32>(getSize().x())/2.0,static_cast<Real32>(getSize().y())/2.0);
    Result.setValues( Result[0]*osgcos(getAngle()) - Result[1]*osgsin(getAngle()), Result[0]*osgsin(getAngle()) + Result[1]*osgcos(getAngle()));
    Result = Result + Vec2f(static_cast<Real32>(getInternalComponent()->getSize().x())/2.0,static_cast<Real32>(getInternalComponent()->getSize().y())/2.0);
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
    }
        
    if((whichField & InternalComponentFieldMask) ||
       (whichField & AngleFieldMask) || 
       (whichField & ResizePolicyFieldMask))
    {
        if(getInternalComponent() != NullFC)
        {
            Vec2f Size;
            switch (static_cast<ResizePolicy>(getResizePolicy()))
            {
            case RESIZE_TO_MIN:
                {
                    //Treat TopLeft as 0,0
                    //Get the Rotated Bounds of the Internal Component
                    Pnt2f p1,p2,p3,p4;

                    Pnt2f ComponentCenter(static_cast<Real32>(getInternalComponent()->getSize().x())/2.0, static_cast<Real32>(getInternalComponent()->getSize().y())/2.0);

                    p1 = -ComponentCenter;
                    p2.setValues(ComponentCenter.x(),-ComponentCenter.y());
                    p3 = ComponentCenter;
                    p4.setValues(-ComponentCenter.x(),ComponentCenter.y());

                    //Rotate them
                    p1 = Rotate(p1, -getAngle());
                    p2 = Rotate(p2, -getAngle());
                    p3 = Rotate(p3, -getAngle());
                    p4 = Rotate(p4, -getAngle());

                    //Get their min and max
                    Pnt2f Min(osgMin(osgMin(osgMin(p1.x(),p2.x()),p3.x()),p4.x()),
                              osgMin(osgMin(osgMin(p1.y(),p2.y()),p3.y()),p4.y()));
                    Pnt2f Max(osgMax(osgMax(osgMax(p1.x(),p2.x()),p3.x()),p4.x()),
                              osgMax(osgMax(osgMax(p1.y(),p2.y()),p3.y()),p4.y()));
                    
	                Pnt2f BorderTopLeft, BorderBottomRight;
	                getInsideInsetsBounds(BorderTopLeft, BorderBottomRight);
	                Pnt2f TopLeft, BottomRight;
	                getBounds(TopLeft, BottomRight);
                    
                    beginEditCP(RotatedComponentPtr(this), PreferredSizeFieldMask);
                        setPreferredSize(Vec2f(Max.x() - Min.x() + (BorderTopLeft.x() - TopLeft.x()) + (BottomRight.x() - BorderBottomRight.x()),
                                               Max.y() - Min.y() + (BorderTopLeft.y() - TopLeft.y()) + (BottomRight.y() - BorderBottomRight.y())));
                    endEditCP(RotatedComponentPtr(this), PreferredSizeFieldMask);
                    break;
                }
            case RESIZE_TO_MAX:
                {
                    //Get the Internal Components Center
                    Pnt2f ComponentCenter(static_cast<Real32>(getInternalComponent()->getSize().x())/2.0, static_cast<Real32>(getInternalComponent()->getSize().y())/2.0);
                    //Get the distance from the Center to one of the TopLeft Corner
                    Real32 Length = 2*ComponentCenter.dist(Pnt2f(0,0));
                    
                    beginEditCP(RotatedComponentPtr(this), PreferredSizeFieldMask);
                        setPreferredSize(Vec2f(Length,Length));
                    endEditCP(RotatedComponentPtr(this), PreferredSizeFieldMask);
                    break;
                }
            case NO_RESIZING:
            default:
                break;
            }
            getInternalComponent()->updateClipBounds();

			//Check the Mouse
			if( getParentWindow() != NullFC &&
				getParentWindow()->getDrawingSurface() != NullFC &&
				getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
			{
				Pnt2f MouseLoc(getParentWindow()->getDrawingSurface()->getEventProducer()->getMousePosition());
				MouseEvent e(NullFC,getSystemTime(),MouseEvent::NO_BUTTON,0,MouseLoc, NullFC);
				checkMouseEnterExit(e,e.getLocation(),getInternalComponent(),getInternalComponent()->isContained(MouseLoc, true),e.getViewport());
			}
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

