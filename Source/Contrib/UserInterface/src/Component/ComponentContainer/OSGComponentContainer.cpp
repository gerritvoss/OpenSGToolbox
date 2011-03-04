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

#include "OSGComponentContainer.h"
#include "OSGUIDrawUtils.h"

#include "OSGMouseEventDetails.h"
#include "OSGNameAttachment.h"

OSG_BEGIN_NAMESPACE

/*!\fn bool ComponentContainer::allowFocusToLeave(void) const
 * \brief Is focus progression allowed to non-descendent Components of this
 * container.
 */

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ComponentContainer::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
bool ComponentContainer::allowFocusToLeave(void) const
{
    return true;
}

Component* ComponentContainer::getNextSiblingOfChild(Component* const Child) const
{
    Int32 ChildIndex = getMFChildren()->findIndex(const_cast<Component*>(Child));
    if(ChildIndex >= 0 &&
       ChildIndex+1 < getMFChildren()->size())
    {
        return getChildren(ChildIndex+1);
    }

    return NULL;
}

Component* ComponentContainer::getPrevSiblingOfChild(Component* const Child) const
{
    Int32 ChildIndex = getMFChildren()->findIndex(const_cast<Component*>(Child));
    if(ChildIndex > 0)
    {
        return getChildren(ChildIndex-1);
    }

    return NULL;
}

bool ComponentContainer::isDecendent(Component* const TheComponent) const
{
    if(getMFChildren()->findIndex(TheComponent) >= 0)
    {
        return true;
    }
    for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        if(getChildren(i)->getType().isDerivedFrom(ComponentContainer::getClassType()))
        {
            return dynamic_cast<ComponentContainer*>(getChildren(i))->isDecendent(TheComponent);
        }
    }

    return false;
}

Int32 ComponentContainer::getChildIndex(Component* const Child)
{
    for(Int32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        if(getChildren(i) == Child)
        {
            return i;
        }
    }
    return -1;
}

Vec2f ComponentContainer::getContentRequestedSize(void) const
{
    if(getLayout() == NULL)
    {
        if(getMFChildren()->size() > 0)
        {
            Pnt2f Minimum(0.0f,0.0f), Maximum(0.0f,0.0f);

            Pnt2f ChildTopLeft, ChildBottomRight, ChildPosition;

            getChildren(0)->getBounds(ChildTopLeft, ChildBottomRight);
            ChildPosition = getChildren(0)->getPosition();
            //These bounds are in the Components coordinate space,
            //we need to convert them to this containers coordinate space
            ChildTopLeft += Vec2f(ChildPosition);
            ChildBottomRight += Vec2f(ChildPosition);

            Minimum[0] = osgMin(ChildTopLeft.x(), ChildBottomRight.x());
            Minimum[1] = osgMin(ChildTopLeft.y(), ChildBottomRight.y());
            Maximum[0] = osgMax(ChildTopLeft.x(), ChildBottomRight.x());
            Maximum[1] = osgMax(ChildTopLeft.y(), ChildBottomRight.y());

            for(UInt32 i(1) ; i<getMFChildren()->size() ; ++i)
            {
                getChildren(i)->getBounds(ChildTopLeft, ChildBottomRight);
                ChildPosition = getChildren(i)->getPosition();
                //These bounds are in the Components coordinate space,
                //we need to convert them to this containers coordinate space
                ChildTopLeft += Vec2f(ChildPosition);
                ChildBottomRight += Vec2f(ChildPosition);

                Minimum[0] = osgMin(osgMin(ChildTopLeft.x(), ChildBottomRight.x()), Minimum.x());
                Minimum[1] = osgMin(osgMin(ChildTopLeft.y(), ChildBottomRight.y()), Minimum.y());
                Maximum[0] = osgMax(osgMax(ChildTopLeft.x(), ChildBottomRight.x()), Maximum.x());
                Maximum[1] = osgMax(osgMax(ChildTopLeft.y(), ChildBottomRight.y()), Maximum.y());
            }
            return Maximum - Minimum;
        }
        else
        {
            return getPreferredSize();
        }

    }
    else
    {
        return getLayout()->requestedContentsLayoutSize(getMFChildren(), this);
    }
}

void ComponentContainer::detachFromEventProducer(void)
{
    Inherited::detachFromEventProducer();
    for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        getChildren(i)->detachFromEventProducer();
    }
}

Vec2f ComponentContainer::getBorderingLength(void) const
{
    Pnt2f BoundsTopLeft, BoundsBottomRight;
    Pnt2f InsideInsetsTopLeft, InsideInsetsBottomRight;

    getBounds(BoundsTopLeft, BoundsBottomRight);
    getInsideBorderBounds(InsideInsetsTopLeft, InsideInsetsBottomRight);

    return (BoundsBottomRight - BoundsTopLeft) - (InsideInsetsBottomRight - InsideInsetsTopLeft);
}

void ComponentContainer::getInsideInsetsBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const
{
    getInsideBorderBounds(TopLeft, BottomRight);

    TopLeft[0] += getLeftInset();
    TopLeft[1] += getTopInset();
    BottomRight[0] -= getRightInset();
    BottomRight[1] -= getBottomInset();
}

void ComponentContainer::setAllInsets(Real32 Inset)
{
    setInset(Vec4f(Inset,Inset,Inset,Inset));
}

void ComponentContainer::setLeftInset ( const Real32 &value )
{
    setInset(Vec4f(value, getInset()[1],getInset()[2], getInset()[3]));
}

void ComponentContainer::setRightInset ( const Real32 &value )
{
    setInset(Vec4f(getInset()[0], value,getInset()[2], getInset()[3]));
}

void ComponentContainer::setTopInset ( const Real32 &value )
{
    setInset(Vec4f(getInset()[0], getInset()[1],value, getInset()[3]));
}

void ComponentContainer::setBottomInset ( const Real32 &value )
{
    setInset(Vec4f(getInset()[0], getInset()[1],getInset()[2], value));
}


void ComponentContainer::drawInternal(Graphics* const TheGraphics, Real32 Opacity) const
{
    //Render all of my Child Components
    for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        getChildren(i)->draw(TheGraphics, Opacity*getOpacity());
    }
}
void ComponentContainer::mouseClicked(MouseEventDetails* const e)
{
    bool isContained;
    for(Int32 i(getMFChildren()->size()-1) ; i>=0 ; --i)
    {
        //If the event is consumed then stop sending the event
        if(e->isConsumed()) return;

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

void ComponentContainer::mouseEntered(MouseEventDetails* const e)
{
    bool isContained;
    for(Int32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        //If the event is consumed then stop sending the event
        if(e->isConsumed()) return;

        isContained = getChildren(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getChildren(i),isContained,e->getViewport());
    }
    Component::mouseEntered(e);
}

void ComponentContainer::mouseExited(MouseEventDetails* const e)
{
    bool isContained;
    for(Int32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        //If the event is consumed then stop sending the event
        if(e->isConsumed()) return;

        isContained = getChildren(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getChildren(i),isContained,e->getViewport());
    }
    Component::mouseExited(e);
}

void ComponentContainer::mousePressed(MouseEventDetails* const e)
{
    bool isContained(false);
    for(Int32 i(getMFChildren()->size()-1) ; i>=0 ; --i)
    {
        //If the event is consumed then stop sending the event
        if(e->isConsumed()) return;

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

void ComponentContainer::mouseReleased(MouseEventDetails* const e)
{
    bool isContained;
    for(Int32 i(getMFChildren()->size()-1) ; i>=0 ; --i)
    {
        //If the event is consumed then stop sending the event
        if(e->isConsumed()) return;

        isContained = getChildren(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getChildren(i),isContained,e->getViewport());
        if(isContained)
        {
            getChildren(i)->mouseReleased(e);
            break;
        }
    }
    if(!e->isConsumed())
    {
        Component::mouseReleased(e);
    }
}


void ComponentContainer::mouseMoved(MouseEventDetails* const e)
{
    Component::mouseMoved(e);

    bool isContained;
    bool isContainedAbove(false);
    for(Int32 i(getMFChildren()->size()-1) ; i>=0 ; --i)
    {
        //If the event is consumed then stop sending the event
        if(e->isConsumed()) return;

        isContained = getChildren(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getChildren(i),isContained && !isContainedAbove,e->getViewport());
        if(isContained && !isContainedAbove)
        {
            isContainedAbove = true;
            getChildren(i)->mouseMoved(e);
        }
    }
}

void ComponentContainer::mouseDragged(MouseEventDetails* const e)
{
    bool isContained;
    bool isContainedAbove(false);
    for(Int32 i(getMFChildren()->size()-1) ; i>=0 ; --i)
    {
        //If the event is consumed then stop sending the event
        if(e->isConsumed()) return;

        isContained = getChildren(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getChildren(i),isContained && !isContainedAbove,e->getViewport());
        if(isContained && !isContainedAbove)
        {
            isContainedAbove = true;
            getChildren(i)->mouseDragged(e);
        }
    }
    Component::mouseDragged(e);
}

void ComponentContainer::mouseWheelMoved(MouseWheelEventDetails* const e)
{
    bool isContained;
    for(Int32 i(getMFChildren()->size()-1) ; i>=0 ; --i)
    {
        //If the event is consumed then stop sending the event
        if(e->isConsumed()) return;

        isContained = getChildren(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getChildren(i),isContained,e->getViewport());
        if(isContained)
        {
            getChildren(i)->mouseWheelMoved(e);
        }
    }
    Component::mouseWheelMoved(e);
}

void ComponentContainer::produceMouseExitOnComponent(MouseEventDetails* const e, Component* const Comp)
{
    Comp->mouseExited(e);
}

void ComponentContainer::produceMouseEnterOnComponent(MouseEventDetails* const e, Component* const Comp)
{
    Comp->mouseEntered(e);
}

void ComponentContainer::checkMouseEnterExit(InputEventDetails* const e, const Pnt2f& MouseLocation, Component* const Comp, bool isMouseContained, Viewport* const TheViewport)
{
    //Check if mouse is inside of this component
    if(!isMouseContained)
    {
        if(Comp->getMouseContained())
        {
            //Mouse has exited the component
            MouseEventDetailsUnrecPtr Details = MouseEventDetails::create(e->getSource(), e->getTimeStamp(), MouseEventDetails::NO_BUTTON,0,MouseLocation,TheViewport);
            produceMouseExitOnComponent(Details, Comp);
        }
        Comp->setMouseContained(false);
    }
    else
    {
        if(!Comp->getMouseContained())
        {
            //Mouse has exited the frame
            MouseEventDetailsUnrecPtr Details = MouseEventDetails::create(e->getSource(), e->getTimeStamp(), MouseEventDetails::NO_BUTTON,0,MouseLocation,TheViewport);
            produceMouseEnterOnComponent(Details, Comp);
        }
        Comp->setMouseContained(true);
    }
}

void ComponentContainer::removeMousePresenceOnComponents(void)
{
    for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        getChildren(i)->setMouseContained(false);
    }
}

void ComponentContainer::setParentWindow(InternalWindow* const parent)
{
    Inherited::setParentWindow(parent);

    //Set All of my children's parent window to mine
    for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        getChildren(i)->setParentWindow(getParentWindow());
    }
}

std::vector<Component*> ComponentContainer::getNamedChildren(const std::string & Name) const
{
    std::vector<Component*> Result;
    
    const Char8* ChildName;
    for(MFChildrenType::const_iterator ChildItor(getMFChildren()->begin()) ; ChildItor != getMFChildren()->end(); ++ChildItor)
    {
        ChildName = getName(*ChildItor);
        if(ChildName != NULL &&
           Name.compare(ChildName) == 0)
        {
            Result.push_back(*ChildItor);
        }
    }

    return Result;
}

std::vector<Component*> ComponentContainer::getNamedDecendents(const std::string & Name) const
{
    std::vector<Component*> Result(getNamedChildren(Name));

    for(MFChildrenType::const_iterator ChildItor(getMFChildren()->begin()) ; ChildItor != getMFChildren()->end(); ++ChildItor)
    {
        if((*ChildItor)->getType().isDerivedFrom(ComponentContainer::getClassType()))
        {
            std::vector<Component*> ChildDec(dynamic_cast<ComponentContainer*>(*ChildItor)->getNamedDecendents(Name));
            Result.insert(Result.end(), ChildDec.begin(), ChildDec.end());
        }
    }

    return Result;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void ComponentContainer::updateLayout(void)
{
    //Update Layout
    if(getLayout() != NULL)
    {
        getLayout()->updateLayout(getMFChildren(), this);
    }
}

/*----------------------- constructors & destructors ----------------------*/

ComponentContainer::ComponentContainer(void) :
    Inherited()
{
}

ComponentContainer::ComponentContainer(const ComponentContainer &source) :
    Inherited(source)
{
}

ComponentContainer::~ComponentContainer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ComponentContainer::changed(ConstFieldMaskArg whichField, 
                                 UInt32            origin,
                                 BitVector         details)
{
    //Do not respond to changes that have a Sync origin
    if(origin & ChangedOrigin::Sync)
    {
        return;
    }

    if(whichField & ChildrenFieldMask)
    {
        //Set All of my children's parent to me
        for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
        {
            getChildren(i)->setParentWindow(getParentWindow());
        }
    }

    if( whichField & ClipBoundsFieldMask )
    {
        //Set All of my children's parent to me
        for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
        {
            getChildren(i)->updateClipBounds();
        }
    }

    if( ((whichField & LayoutFieldMask) ||
        (whichField & InsetFieldMask) ||
        (whichField & ChildrenFieldMask) ||
        (whichField & SizeFieldMask) ||
        (whichField & BorderFieldMask) ||
        (whichField & DisabledBorderFieldMask) ||
        (whichField & FocusedBorderFieldMask) ||
        (whichField & RolloverBorderFieldMask))
        //&& getParentWindow()
        )
    {
        //Layout needs to be recalculated
        updateLayout();
    }
    Inherited::changed(whichField, origin, details);
}

void ComponentContainer::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ComponentContainer NI" << std::endl;
}

OSG_END_NAMESPACE
