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

#include "OSGRotatedComponent.h"
#include "OSGUIDrawUtils.h"
#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGRotatedComponentBase.cpp file.
// To modify it, please change the .fcd file (OSGRotatedComponent.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void RotatedComponent::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Pnt2f RotatedComponent::getParentToLocal(const Pnt2f& Location) const
{
    Pnt2f Result(Inherited::getParentToLocal(Location));
    Result = Result - Vec2f(static_cast<Real32>(getSize().x())/2.0,static_cast<Real32>(getSize().y())/2.0);
    Result.setValues( Result[0]*osgCos(getAngle()) - Result[1]*osgSin(getAngle()), Result[0]*osgSin(getAngle()) + Result[1]*osgCos(getAngle()));
    Result = Result + Vec2f(static_cast<Real32>(getInternalComponent()->getSize().x())/2.0,static_cast<Real32>(getInternalComponent()->getSize().y())/2.0);
    return Result;
}

Pnt2f RotatedComponent::getLocalToParent(const Pnt2f& Location) const
{
    Pnt2f Result(Location);
    Result = Result - Vec2f(static_cast<Real32>(getInternalComponent()->getSize().x())/2.0,static_cast<Real32>(getInternalComponent()->getSize().y())/2.0);

    Result.setValues( Result[0]*osgCos(-getAngle()) - Result[1]*osgSin(-getAngle()), Result[0]*osgSin(-getAngle()) + Result[1]*osgCos(-getAngle()));

    Result = Result + Vec2f(static_cast<Real32>(getSize().x())/2.0,static_cast<Real32>(getSize().y())/2.0);
    Result = Inherited::getLocalToParent(Result);
    return Result;
}

void RotatedComponent::drawInternal(Graphics* const TheGraphics, Real32 Opacity) const
{
    if(getInternalComponent() != NULL)
    {
        Pnt2f TopLeft, BottomRight;
        getInsideInsetsBounds(TopLeft, BottomRight);

        TheGraphics->incrDrawBounderiesNesting();

        TheGraphics->initAddDrawBounderies();
        TheGraphics->drawRect(TopLeft, BottomRight,Color4f(0.0f,0.0f,0.0f,1.0f),1.0);
        TheGraphics->uninitAddDrawBounderies();

        TheGraphics->activateDrawBounderiesTest();


        glPushMatrix();
        glTranslatef(static_cast<Real32>(getSize().x())/2.0,static_cast<Real32>(getSize().y())/2.0,0.0);
        glRotatef(-osgRad2Degree(getAngle()), 0.0,0.0,1.0);
        glTranslatef(-static_cast<Real32>(getInternalComponent()->getSize().x())/2.0,-static_cast<Real32>(getInternalComponent()->getSize().y())/2.0,0.0);
        getInternalComponent()->draw(TheGraphics, getOpacity()*Opacity);
        glPopMatrix();


        TheGraphics->decrDrawBounderiesNestring();
        TheGraphics->initRemoveDrawBounderies();
        TheGraphics->drawRect(TopLeft, BottomRight,Color4f(0.0f,0.0f,0.0f,1.0f),1.0);
        TheGraphics->uninitRemoveDrawBounderies();
        TheGraphics->activateDrawBounderiesTest();
    }
}

void RotatedComponent::updateLayout(void)
{
    Pnt2f TopLeft, BottomRight;
    getInsideInsetsBounds(TopLeft, BottomRight);

    for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        if(getChildren(i)->getPosition() != Pnt2f(0,0))
        {
            getChildren(i)->setPosition(Pnt2f(0,0));
        }
        if(getChildren(i)->getSize() != getChildren(i)->getPreferredSize())
        {
            getChildren(i)->setSize(getChildren(i)->getPreferredSize());
        }
    }
}

void RotatedComponent::mouseClicked(MouseEventDetails* const e)
{
    bool isContained;
    for(Int32 i(getMFChildren()->size()-1) ; i>=0 ; --i)
    {
        isContained = getChildren(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getChildren(i),isContained,e->getViewport());
        if(isContained)
        {
            getChildren(i)->mouseClicked(e);
            break;
        }
    }
    Component::mouseClicked(e);
}

void RotatedComponent::mouseEntered(MouseEventDetails* const e)
{
    bool isContained;
    for(Int32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        isContained = getChildren(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getChildren(i),isContained,e->getViewport());
    }
    Component::mouseEntered(e);
}

void RotatedComponent::mouseExited(MouseEventDetails* const e)
{
    bool isContained;
    for(Int32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        isContained = getChildren(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getChildren(i),isContained,e->getViewport());
    }
    Component::mouseExited(e);
}

void RotatedComponent::mousePressed(MouseEventDetails* const e)
{
    bool isContained(false);
    for(Int32 i(getMFChildren()->size()-1) ; i>=0 ; --i)
    {
        isContained = getChildren(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getChildren(i),isContained,e->getViewport());
        if(isContained)
        {
            //Give myself temporary focus
            takeFocus(true);
            if(!getChildren(i)->getType().isDerivedFrom(ComponentContainer::getClassType()))
            {
                getChildren(i)->takeFocus();
            }
            getChildren(i)->mousePressed(e);
            break;
        }
    }
    if(isContained)
    {
        //Remove my temporary focus
        giveFocus(NULL, false);
    }
    else
    {
        //Give myself permenant focus
        takeFocus();
    }
    Component::mousePressed(e);
}

void RotatedComponent::mouseReleased(MouseEventDetails* const e)
{
    bool isContained;
    for(Int32 i(getMFChildren()->size()-1) ; i>=0 ; --i)
    {
        isContained = getChildren(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getChildren(i),isContained,e->getViewport());
        if(isContained)
        {
            getChildren(i)->mouseReleased(e);
            break;
        }
    }
    Component::mouseReleased(e);
}


void RotatedComponent::mouseMoved(MouseEventDetails* const e)
{
    bool isContained;
    for(Int32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        isContained = getChildren(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getChildren(i),isContained,e->getViewport());
        if(isContained)
        {
            getChildren(i)->mouseMoved(e);
        }
    }
    Component::mouseMoved(e);
}

void RotatedComponent::mouseDragged(MouseEventDetails* const e)
{
    bool isContained;
    for(Int32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        isContained = getChildren(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getChildren(i),isContained,e->getViewport());
        if(isContained)
        {
            getChildren(i)->mouseDragged(e);
        }
    }
    Component::mouseDragged(e);
}

void RotatedComponent::mouseWheelMoved(MouseWheelEventDetails* const e)
{
    bool isContained;
    for(Int32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        isContained = getChildren(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getChildren(i),isContained,e->getViewport());
        if(isContained)
        {
            getChildren(i)->mouseWheelMoved(e);
        }
    }
    Component::mouseWheelMoved(e);
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

void RotatedComponent::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & InternalComponentFieldMask)
    {
            clearChildren();
            if(getInternalComponent() != NULL)
            {
                pushToChildren(getInternalComponent());
            }
    }
        
    if((whichField & InternalComponentFieldMask) ||
       (whichField & AngleFieldMask) || 
       (whichField & ResizePolicyFieldMask))
    {
        if(getInternalComponent() != NULL)
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
                    
                        setPreferredSize(Vec2f(Max.x() - Min.x() + (BorderTopLeft.x() - TopLeft.x()) + (BottomRight.x() - BorderBottomRight.x()),
                                               Max.y() - Min.y() + (BorderTopLeft.y() - TopLeft.y()) + (BottomRight.y() - BorderBottomRight.y())));
                    break;
                }
            case RESIZE_TO_MAX:
                {
                    //Get the Internal Components Center
                    Pnt2f ComponentCenter(static_cast<Real32>(getInternalComponent()->getSize().x())/2.0, static_cast<Real32>(getInternalComponent()->getSize().y())/2.0);
                    //Get the distance from the Center to one of the TopLeft Corner
                    Real32 Length = 2*ComponentCenter.dist(Pnt2f(0,0));
                    
                        setPreferredSize(Vec2f(Length,Length));
                    break;
                }
            case NO_RESIZING:
            default:
                break;
            }
            getInternalComponent()->updateClipBounds();

			//Check the Mouse
			if( getParentWindow() != NULL &&
				getParentWindow()->getParentDrawingSurface() != NULL &&
				getParentWindow()->getParentDrawingSurface()->getEventProducer() != NULL)
			{
				Pnt2f MouseLoc(getParentWindow()->getParentDrawingSurface()->getEventProducer()->getMousePosition());
				MouseEventDetailsUnrecPtr e = MouseEventDetails::create(getParentWindow()->getParentDrawingSurface()->getEventProducer(),getSystemTime(),MouseEventDetails::NO_BUTTON,0,MouseLoc, NULL);
				checkMouseEnterExit(e,e->getLocation(),getInternalComponent(),getInternalComponent()->isContained(MouseLoc, true),e->getViewport());
			}
        }
    }
}

void RotatedComponent::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump RotatedComponent NI" << std::endl;
}

OSG_END_NAMESPACE
