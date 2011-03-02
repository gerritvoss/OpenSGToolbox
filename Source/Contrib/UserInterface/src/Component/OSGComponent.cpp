/*---------------------------------------------------------------------------*\
 *                             OpenSGToolbox                                 *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2007-2011                                     *
 *                                                                           *
 *                        www.opensgtoolbox.org                              *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
 *                                                                           *
 \*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library Lesser General Public License as       *
 * published  by the Free Software Foundation, version 3.                    *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library Lesser General Public License for more details.                   *
 *                                                                           *
 * You should have received a copy of the GNU Library Lesser General Public  *
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

#include "OSGComponent.h"
#include "OSGViewport.h"
#include "OSGWindowEventProducer.h"

#include "OSGComponentContainer.h"
#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"
#include "OSGUIDrawingSurfaceMouseTransformFunctor.h"
#include "OSGUIDrawUtils.h"
#include "OSGLookAndFeelManager.h"
#include "OSGPopupMenu.h"
#include "OSGScrollBar.h"
#include "OSGLayoutConstraints.h"
#include "OSGInternalWindow.h"

#include "OSGRotatedComponent.h"

#include "OSGUIViewport.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGComponentBase.cpp file.
// To modify it, please change the .fcd file (OSGComponent.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const OSG::BitVector  Component::BordersFieldMask = 
    (TypeTraits<BitVector>::One << ComponentBase::BorderFieldId) |
    (TypeTraits<BitVector>::One << ComponentBase::DisabledBorderFieldId) |
    (TypeTraits<BitVector>::One << ComponentBase::FocusedBorderFieldId) |
    (TypeTraits<BitVector>::One << ComponentBase::RolloverBorderFieldId);

const OSG::BitVector  Component::BackgroundsFieldMask = 
    (TypeTraits<BitVector>::One << ComponentBase::BackgroundFieldId) |
    (TypeTraits<BitVector>::One << ComponentBase::DisabledBackgroundFieldId) |
    (TypeTraits<BitVector>::One << ComponentBase::FocusedBackgroundFieldId) |
    (TypeTraits<BitVector>::One << ComponentBase::RolloverBackgroundFieldId);

const OSG::BitVector  Component::ForegroundsFieldMask = 
    (TypeTraits<BitVector>::One << ComponentBase::ForegroundFieldId) |
    (TypeTraits<BitVector>::One << ComponentBase::DisabledForegroundFieldId) |
    (TypeTraits<BitVector>::One << ComponentBase::FocusedForegroundFieldId) |
    (TypeTraits<BitVector>::One << ComponentBase::RolloverForegroundFieldId);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Component::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool Component::setupClipping(Graphics* const Graphics) const
{
    if(getClipping())
    {    
        //Get Clipping initial settings
        Pnt2f ClipTopLeft,ClipBottomRight;
        getClipBounds(ClipTopLeft,ClipBottomRight);

        Vec4d LeftPlaneEquation  (1.0,0.0,0.0, -ClipTopLeft.x()     + Graphics->getClipPlaneOffset()),
              RightPlaneEquation (-1.0,0.0,0.0, ClipBottomRight.x() + Graphics->getClipPlaneOffset()),
              TopPlaneEquation   (0.0,1.0,0.0, -ClipTopLeft.y()     + Graphics->getClipPlaneOffset()),
              BottomPlaneEquation(0.0,-1.0,0.0, ClipBottomRight.y() + Graphics->getClipPlaneOffset());

        //glClipPlane
        //Clip with the Intersection of this components RenderingSurface bounds
        //and its parents RenderingSurface bounds
        if(ClipBottomRight.x()-ClipTopLeft.x() <= 0 || ClipBottomRight.y()-ClipTopLeft.y()<= 0)
        {
            return false;
        }

        if(!glIsEnabled(GL_CLIP_PLANE0)) { glEnable(GL_CLIP_PLANE0); }
        if(!glIsEnabled(GL_CLIP_PLANE1)) { glEnable(GL_CLIP_PLANE1); }
        if(!glIsEnabled(GL_CLIP_PLANE2)) { glEnable(GL_CLIP_PLANE2); }
        if(!glIsEnabled(GL_CLIP_PLANE3)) { glEnable(GL_CLIP_PLANE3); }

        //Clip Plane Equations
        //Clip Planes get transformed by the ModelViewMatrix when set
        //So we can rely on the fact that our current coordinate space
        //is relative to the this components position

        glClipPlane(GL_CLIP_PLANE0,LeftPlaneEquation.getValues());
        glClipPlane(GL_CLIP_PLANE1,RightPlaneEquation.getValues());
        glClipPlane(GL_CLIP_PLANE2,TopPlaneEquation.getValues());
        glClipPlane(GL_CLIP_PLANE3,BottomPlaneEquation.getValues());
    }
    else
    {
        if(glIsEnabled(GL_CLIP_PLANE0)) { glDisable(GL_CLIP_PLANE0); }
        if(glIsEnabled(GL_CLIP_PLANE1)) { glDisable(GL_CLIP_PLANE1); }
        if(glIsEnabled(GL_CLIP_PLANE2)) { glDisable(GL_CLIP_PLANE2); }
        if(glIsEnabled(GL_CLIP_PLANE3)) { glDisable(GL_CLIP_PLANE3); }
    }
    return true;
}

void Component::draw(Graphics* const TheGraphics, Real32 Opacity) const
{
    //If not visible then don't draw
    if (!getVisible())
        return;

    //Grab the initial transformation
    GLdouble InitMat[16];
    glGetDoublev(GL_MODELVIEW_MATRIX, InitMat);

    //Translate to my position
    glTranslatef(getPosition().x(), getPosition().y(), 0);

    if(setupClipping(TheGraphics))
    {

        //Activate My Border Drawing constraints
        Border* DrawnBorder = getDrawnBorder();
        if(DrawnBorder != NULL)
        {
            DrawnBorder->activateInternalDrawConstraints(TheGraphics,0,0,getSize().x(),getSize().y());
        }


        //Draw My Background
        drawBackground(TheGraphics, getDrawnBackground(), Opacity);

        //Draw Internal
        drawInternal(TheGraphics, Opacity);

        //Make sure the clipping is reset
        setupClipping(TheGraphics);

        //Draw My Foreground
        drawForeground(TheGraphics, getDrawnForeground(), Opacity);

        //Draw all parts that should not be clipped against
        drawUnclipped(TheGraphics, Opacity);
    }

    //Reset the transformation
    glLoadMatrixd(InitMat);
}


void Component::drawUnclipped(Graphics* const TheGraphics, Real32 Opacity) const
{
    //Draw Border
    drawBorder(TheGraphics, getDrawnBorder(), Opacity);
}


void Component::updateClipBounds(void)
{
    Pnt2f TopLeft, BottomRight;
    if((getParentContainer() == NULL && useBoundsForClipping()) ||
       (getParentContainer() && getParentContainer()->getType() == RotatedComponent::getClassType()))
    {
        //If I have no parent container use my bounds
        getBounds(TopLeft, BottomRight);
    }
    else if(getParentContainer() != NULL)
    {
        //Get the intersection of:
        //     My Bounds
        //     My Parent Containers Clip Bounds
        //     My Parent Containers Inset Bounds
        Pnt2f MyTopLeft,MyBottomRight;
        getBounds(MyTopLeft,MyBottomRight);

        //Get Parent ComponentContainer's Clip Bounds
        Pnt2f ContainerClipTopLeft, ContainerClipBottomRight;
        dynamic_cast<ComponentContainer*>(getParentContainer())->getClipBounds(ContainerClipTopLeft,ContainerClipBottomRight);

        //Parent ComponentContainer's Clip Bounds are in the Parent ComponentContainer's Coordinate space
        //We need to convert them to this Components Coordinate space
        ContainerClipTopLeft -= Vec2f(getPosition());
        ContainerClipBottomRight -= Vec2f(getPosition());

        //Get Parent ComponentContainer's Inset Bounds
        Pnt2f ContainerInsetTopLeft, ContainerInsetBottomRight;
        dynamic_cast<ComponentContainer*>(getParentContainer())->getInsideInsetsBounds(ContainerInsetTopLeft, ContainerInsetBottomRight);

        //Parent ComponentContainer's Inset Bounds are in the Parent ComponentContainer's Coordinate space
        //We need to convert them to this Components Coordinate space
        ContainerInsetTopLeft -= Vec2f(getPosition());
        ContainerInsetBottomRight -= Vec2f(getPosition());

        //Get the intersection of my bounds with my parent containers clip bounds
        quadIntersection(MyTopLeft,MyBottomRight,
                         ContainerClipTopLeft,ContainerClipBottomRight,
                         TopLeft, BottomRight);

        quadIntersection(TopLeft,BottomRight,
                         ContainerInsetTopLeft,ContainerInsetBottomRight,
                         TopLeft, BottomRight);
    }

    //The Clip Bounds calculated are in my Parent Containers coordinate space
    //Translate these bounds into my own coordinate space
    if(getClipTopLeft() != TopLeft)
    {
        setClipTopLeft(TopLeft);
    }
    if(getClipBottomRight() != BottomRight)
    {
        setClipBottomRight(BottomRight);
    }
}

bool Component::isAncestor(Component* const TheComponent) const
{
    //Move up the tree until the Root or the component testing for is found
    const Component* TestComponent(getParentContainer());
    while(TestComponent != NULL)
    {
        if(TestComponent = TheComponent)
        {
            return true;
        }
        TestComponent = TestComponent->getParentContainer();
    }
    return false;
}

void Component::moveFocus(Int32 MoveAmount)
{
    //Follow a depth first search of Components that are isFocusInteractable 
    ComponentUnrecPtr ComponentToFocus = ComponentUnrecPtr(this);
    if(MoveAmount > 0)
    {
        //Focus forward the given amount
        for(Int32 i(0) ; i<MoveAmount ; ++i)
        {
            //Find the next component that is Focus Interactable
            do
            {
                ComponentToFocus = ComponentToFocus->getNextDepthFirstComponent();
            }while(ComponentToFocus != NULL &&               //None found
                   ComponentToFocus != this &&               //Looped back to this component
                   !ComponentToFocus->isFocusInteractable());

            //Has the Depth first order reached the end
            if(ComponentToFocus == NULL &&
               getParentWindow() != NULL)
            {
                ComponentToFocus = getParentWindow()->getLeftmostDecendent();
            }

            //Is the focus allowed to go here
            ComponentContainer* ParentTest(getParentContainer());
            while(ParentTest != NULL &&
                  !ParentTest->isDecendent(ComponentToFocus))
            {
                if(!ParentTest->allowFocusToLeave())
                {
                    //Change the focus to the first child of this parent
                    ComponentToFocus = ParentTest->getLeftmostDecendent();
                    break;
                }
                ParentTest = ParentTest->getParentContainer();
            }
        }
    }
    else if(MoveAmount < 0)
    {
        //Focus backward the given amount
        for(Int32 i(0) ; i>MoveAmount ; --i)
        {
            //Find the next component that is Focus Interactable
            do
            {
                ComponentToFocus = ComponentToFocus->getPrevDepthFirstComponent();
            }while(ComponentToFocus != NULL &&               //None found
                   ComponentToFocus != this &&               //Looped back to this component
                   !ComponentToFocus->isFocusInteractable());

            //Has the Depth first order reached the first
            if(ComponentToFocus == NULL &&
               getParentWindow() != NULL)
            {
                ComponentToFocus = getParentWindow()->getRightmostDecendent();
            }

            //Is the focus allowed to go here
            ComponentContainer* ParentTest(getParentContainer());
            while(ParentTest != NULL &&
                  !ParentTest->isDecendent(ComponentToFocus))
            {
                if(!ParentTest->allowFocusToLeave())
                {
                    //Change the focus to the first child of this parent
                    ComponentToFocus = ParentTest->getRightmostDecendent();
                    break;
                }
                ParentTest = ParentTest->getParentContainer();
            }
        }
    }

    //If a component was found to move to
    if(ComponentToFocus != NULL &&
       ComponentToFocus != this)
    {
        ComponentToFocus->takeFocus();
    }
}


void Component::moveFocusPosX(void)
{
    ComponentUnrecPtr ComponentToFocus(getNextSiblingInPosX());

    //If a component was found to move to
    if(ComponentToFocus != NULL)
    {
        ComponentToFocus->takeFocus();
    }
}

void Component::moveFocusNegX(void)
{
    ComponentUnrecPtr ComponentToFocus(getNextSiblingInNegX());

    //If a component was found to move to
    if(ComponentToFocus != NULL)
    {
        ComponentToFocus->takeFocus();
    }
}

void Component::moveFocusPosY(void)
{
    ComponentUnrecPtr ComponentToFocus(getNextSiblingInPosY());

    //If a component was found to move to
    if(ComponentToFocus != NULL)
    {
        ComponentToFocus->takeFocus();
    }
}

void Component::moveFocusNegY(void)
{
    ComponentUnrecPtr ComponentToFocus(getNextSiblingInNegY());

    //If a component was found to move to
    if(ComponentToFocus != NULL)
    {
        ComponentToFocus->takeFocus();
    }
}

bool Component::isFocusInteractable(void) const
{
    return false;
}

Component* Component::getNextDepthFirstComponent(void) const
{
    if(getParentContainer() != NULL)
    {
        Component* TestComp(getNextSibling());
        if(TestComp == NULL)
        {
            TestComp = getParentContainer();
            while(TestComp != NULL &&
                  TestComp->getNextSibling() == NULL)
            {
                TestComp = TestComp->getParentContainer();
            }

            if(TestComp != NULL)
            {
                TestComp = TestComp->getNextSibling();
            }
        }

        if(TestComp != NULL &&
           TestComp->getType().isDerivedFrom(ComponentContainer::getClassType()))
        {
            return TestComp->getLeftmostDecendent();
        }
        else
        {
            return TestComp;
        }
    }

    return NULL;
}

Component* Component::getPrevDepthFirstComponent(void) const
{
    if(getParentContainer() != NULL)
    {
        Component* TestComp(getPrevSibling());
        if(TestComp == NULL)
        {
            TestComp = getParentContainer();
            while(TestComp != NULL &&
                  TestComp->getPrevSibling() == NULL)
            {
                TestComp = TestComp->getParentContainer();
            }

            if(TestComp != NULL)
            {
                TestComp = TestComp->getPrevSibling();
            }
        }

        if(TestComp != NULL &&
           TestComp->getType().isDerivedFrom(ComponentContainer::getClassType()))
        {
            return TestComp->getRightmostDecendent();
        }
        else
        {
            return TestComp;
        }
    }

    return NULL;
}

Component* Component::getNextSibling(void) const
{
    if(getParentContainer() != NULL)
    {
        return getParentContainer()->getNextSiblingOfChild(const_cast<Component* const>(this));
    }

    return NULL;
}

Component* Component::getPrevSibling(void) const
{
    if(getParentContainer() != NULL)
    {
        return getParentContainer()->getPrevSiblingOfChild(const_cast<Component* const>(this));
    }

    return NULL;
}

Component* Component::getLeftmostDecendent(void) const
{
    if(getType().isDerivedFrom(ComponentContainer::getClassType()))
    {
        const ComponentContainer* ThisCast(dynamic_cast<const ComponentContainer*>(this));
        if(ThisCast->getMFChildren()->size() > 0)
        {
            if(!ThisCast->getChildren(0)->getType().isDerivedFrom(ComponentContainer::getClassType()) )
            {
                return ThisCast->getChildren(0);
            }
            else
            {
                return ThisCast->getChildren(0)->getLeftmostDecendent();
            }
        }
    }

    return NULL;
}

Component* Component::getRightmostDecendent(void) const
{
    if(getType().isDerivedFrom(ComponentContainer::getClassType()))
    {
        const ComponentContainer* ThisCast(dynamic_cast<const ComponentContainer*>(this));
        if(ThisCast->getMFChildren()->size() > 0)
        {
            if(!ThisCast->getMFChildren()->back()->getType().isDerivedFrom(ComponentContainer::getClassType()) )
            {
                return ThisCast->getMFChildren()->back();
            }
            else
            {
                return ThisCast->getMFChildren()->back()->getRightmostDecendent();
            }
        }
    }

    return NULL;
}

Component* Component::getNextSiblingInPosX(void) const
{
    Component* TestComponent(NULL);
    if(getParentContainer() != NULL)
    {
        for(UInt32 i(0) ; getParentContainer()->getMFChildren()->size(); ++i)
        {
            if(getParentContainer()->getChildren(i)->getPosition().x() >= getPosition().x() &&
               (TestComponent == NULL ||
                getParentContainer()->getChildren(i)->getPosition().x() <= TestComponent->getPosition().x()))
            {
                TestComponent = getParentContainer()->getChildren(i);
            }
        }
    }

    if(TestComponent != this)
    {
        return TestComponent;
    }
    else
    {
        return NULL;
    }
}

Component* Component::getNextSiblingInNegX(void) const
{
    Component* TestComponent(NULL);
    if(getParentContainer() != NULL)
    {
        for(UInt32 i(0) ; getParentContainer()->getMFChildren()->size(); ++i)
        {
            if(getParentContainer()->getChildren(i)->getPosition().x() <= getPosition().x() &&
               (TestComponent == NULL ||
                getParentContainer()->getChildren(i)->getPosition().x() >= TestComponent->getPosition().x()))
            {
                TestComponent = getParentContainer()->getChildren(i);
            }
        }
    }

    if(TestComponent != this)
    {
        return TestComponent;
    }
    else
    {
        return NULL;
    }
}

Component* Component::getNextSiblingInPosY(void) const
{
    Component* TestComponent(NULL);
    if(getParentContainer() != NULL)
    {
        for(UInt32 i(0) ; getParentContainer()->getMFChildren()->size(); ++i)
        {
            if(getParentContainer()->getChildren(i)->getPosition().y() >= getPosition().y() &&
               (TestComponent == NULL ||
                getParentContainer()->getChildren(i)->getPosition().y() <= TestComponent->getPosition().y()))
            {
                TestComponent = getParentContainer()->getChildren(i);
            }
        }
    }

    if(TestComponent != this)
    {
        return TestComponent;
    }
    else
    {
        return NULL;
    }
}

Component* Component::getNextSiblingInNegY(void) const
{
    Component* TestComponent(NULL);
    if(getParentContainer() != NULL)
    {
        for(UInt32 i(0) ; getParentContainer()->getMFChildren()->size(); ++i)
        {
            if(getParentContainer()->getChildren(i)->getPosition().y() <= getPosition().y() &&
               (TestComponent == NULL ||
                getParentContainer()->getChildren(i)->getPosition().y() >= TestComponent->getPosition().y()))
            {
                TestComponent = getParentContainer()->getChildren(i);
            }
        }
    }

    if(TestComponent != this)
    {
        return TestComponent;
    }
    else
    {
        return NULL;
    }
}

ComponentContainer* Component::getParentContainer(void) const
{
    return dynamic_cast<ComponentContainer*>(_sfParentContainer.getValue());
}

InternalWindow* Component::getParentWindow(void) const
{
    return _ParentWindow;
}

void Component::setParentWindow(InternalWindow* const parent)
{
    _ParentWindow = parent;
}

bool Component::useBoundsForClipping(void) const
{
    return true;
}

void Component::detachFromEventProducer(void)
{
    _ToolTipActivateUpdateConnection.disconnect();
}

Pnt2f Component::getClipTopLeft(void) const
{
    return Pnt2f(ComponentBase::getClipBounds()[0], ComponentBase::getClipBounds()[1]);
}

Pnt2f Component::getClipBottomRight(void) const
{
    return Pnt2f(ComponentBase::getClipBounds()[2], ComponentBase::getClipBounds()[3]);
}

void Component::setClipTopLeft    (const Pnt2f &value)
{
    setClipBounds(Pnt4f(value[0], value[1], ComponentBase::getClipBounds()[2],ComponentBase::getClipBounds()[3]));
}

void Component::setClipBottomRight(const Pnt2f &value)
{
    setClipBounds(Pnt4f(ComponentBase::getClipBounds()[0],ComponentBase::getClipBounds()[1], value[0], value[1]));
}

Pnt2f Component::getParentToLocal(const Pnt2f& Location) const
{
    return Location - getPosition();
}

Pnt2f Component::getLocalToParent(const Pnt2f& Location) const
{
    return Location + getPosition().subZero();
}

UInt32 Component::queryCursor(const Pnt2f& CursorLoc) const
{
    return getCursor();
}

Vec2f Component::getRequestedSize(void) const
{
    return getBorderingLength() + getContentRequestedSize();
}

Vec2f Component::getContentRequestedSize(void) const
{
    return Vec2f(0.0,0.0);
}

Vec2f Component::getBorderingLength(void) const
{
    Pnt2f BoundsTopLeft, BoundsBottomRight;
    Pnt2f InsideBorderTopLeft, InsideBorderBottomRight;

    getBounds(BoundsTopLeft, BoundsBottomRight);
    getInsideBorderBounds(InsideBorderTopLeft, InsideBorderBottomRight);

    return (BoundsBottomRight - BoundsTopLeft) - (InsideBorderBottomRight - InsideBorderTopLeft);
}

void Component::setBorders(Border* const TheBorder)
{
    setBorder        (TheBorder);
    setDisabledBorder(TheBorder);
    setFocusedBorder (TheBorder);
    setRolloverBorder(TheBorder);
}

void Component::setBackgrounds(Layer* const TheBackground)
{
    setBackground        (TheBackground);
    setDisabledBackground(TheBackground);
    setFocusedBackground (TheBackground);
    setRolloverBackground(TheBackground);
}


void Component::setForegrounds(Layer* const TheForeground)
{
    setForeground        (TheForeground);
    setDisabledForeground(TheForeground);
    setFocusedForeground (TheForeground);
    setRolloverForeground(TheForeground);
}

Border* Component::getDrawnBorder(void) const
{
    if(getEnabled())
    {
        if(_MouseInComponentLastMouse)
        {
            return getRolloverBorder();
        }
        else if(getFocused())
        {
            return getFocusedBorder();
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

Layer* Component::getDrawnBackground(void) const
{
    if(getEnabled())
    {
        if(_MouseInComponentLastMouse)
        {
            return getRolloverBackground();
        }
        else if(getFocused())
        {
            return getFocusedBackground();
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

Layer* Component::getDrawnForeground(void) const
{
    if(getEnabled())
    {
        if(_MouseInComponentLastMouse)
        {
            return getFocusedForeground();
        }
        else if(getFocused())
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

bool Component::isContained(const Pnt2f& p, bool TestAgainstClipBounds) const
{
    if(!getVisible())
    {
        return false;
    }

    Pnt2f PointInCompSpace(DrawingSurfaceToComponent(p,this));
    Border* DrawnBorder(getDrawnBorder());
    Pnt2f TopLeft, BottomRight;
    if(TestAgainstClipBounds && getClipping())
    {
        TopLeft = getClipTopLeft();
        BottomRight = getClipBottomRight();
    }
    else
    {
        TopLeft.setValues(0,0);
        BottomRight = Pnt2f(getSize());
    }

    if(DrawnBorder == NULL)
    {
        return isContainedBounds(PointInCompSpace, TopLeft, BottomRight);
    }
    else
    {
        return isContainedBounds(PointInCompSpace, TopLeft, BottomRight) && 
            DrawnBorder->isContained(PointInCompSpace,0,0,getSize().x(),getSize().y());
    }
}

ComponentTransitPtr Component::createDefaultToolTip(void)
{
    ComponentTransitPtr Result(NULL);

    //Get the active LookAndFeel
    //Copy the default ToolTip
    Component* DefaultTooltip = LookAndFeelManager::the()->getLookAndFeel()->getDefaultToolTip();

    if(DefaultTooltip != NULL)
    {
        FieldContainerTransitPtr tmpPtr = DefaultTooltip->shallowCopy();

        Result = dynamic_pointer_cast<Component>(tmpPtr);
    }

    return Result;
}

void Component::getBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const
{
    TopLeft = Pnt2f(0,0);
    BottomRight = Pnt2f(getSize());
}

void Component::getInsideBorderBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const
{
    Real32 TopInset(0), LeftInset(0), BottomInset(0), RightInset(0);

    if(getBorder() != NULL)
    {
        //Get Border Insets
        getBorder()->getInsets(LeftInset,RightInset,TopInset,BottomInset);
    }
    TopLeft.setValues(LeftInset, TopInset);
    BottomRight.setValues(TopLeft.x()+getSize().x()-(LeftInset + RightInset), TopLeft.y()+getSize().y()-(TopInset + BottomInset));
}

void Component::getBoundsRenderingSurfaceSpace(Pnt2f& TopLeft, Pnt2f& BottomRight) const
{
    Pnt2f ParentContainerTopLeft(0,0),ParentContainerBottomRight(0,0);
    if(getParentContainer() != NULL)
    {
        dynamic_cast<ComponentContainer*>(getParentContainer())->getBoundsRenderingSurfaceSpace(ParentContainerTopLeft, ParentContainerBottomRight);
    }
    TopLeft = ParentContainerTopLeft + Vec2f(getPosition());
    BottomRight = TopLeft + getSize();
}

void Component::drawBorder(Graphics* const TheGraphics, const Border* Border, Real32 Opacity) const
{
    if(Border != NULL)
    {
        //Draw My Border
        Border->draw(TheGraphics,0,0,getSize().x(),getSize().y(), getOpacity()*Opacity, getClipping());
    }
}

void Component::drawBackground(Graphics* const TheGraphics, const Layer* Background, Real32 Opacity) const
{
    //Draw the Background on the Inside of my border
    if(Background != NULL)
    {
        Pnt2f TopLeft, BottomRight;
        getInsideBorderBounds(TopLeft, BottomRight);
        Background->draw(TheGraphics, TopLeft, BottomRight, getOpacity()*Opacity);
    }
}

void Component::drawForeground(Graphics* const TheGraphics, const Layer* Foreground, Real32 Opacity) const
{
    //Draw the Foreground on the Inside of my border
    if(Foreground != NULL)
    {
        Pnt2f TopLeft, BottomRight;
        getInsideBorderBounds(TopLeft, BottomRight);
        Foreground->draw(TheGraphics, TopLeft, BottomRight, getOpacity()*Opacity);
    }
}

void Component::mouseClicked(MouseEventDetails* const e)
{
    produceMouseClicked(e);
}

void Component::mouseEntered(MouseEventDetails* const e)
{
    produceMouseEntered(e);
}

void Component::mouseExited(MouseEventDetails* const e)
{
    produceMouseExited(e);
}

void Component::mousePressed(MouseEventDetails* const e)
{
    produceMousePressed(e);

    if(e->getButton() == MouseEventDetails::BUTTON3
       && getPopupMenu() != NULL)
    {
        getPopupMenu()->setInvoker(this);
        getPopupMenu()->setVisible(true);
        getPopupMenu()->setPosition(ViewportToComponent(e->getLocation(),getParentWindow(),e->getViewport()));

        getParentWindow()->pushToActivePopupMenus(getPopupMenu());
    }
}

void Component::mouseReleased(MouseEventDetails* const e)
{
    produceMouseReleased(e);
}


void Component::mouseMoved(MouseEventDetails* const e)
{

    if(getParentWindow() != NULL && getParentWindow()->getParentDrawingSurface()!=NULL&&getParentWindow()->getParentDrawingSurface()->getEventProducer() != NULL)
    {
        getParentWindow()->getParentDrawingSurface()->getEventProducer()->setCursorType(queryCursor(e->getLocation()));
    }
    produceMouseMoved(e);
}

void Component::mouseDragged(MouseEventDetails* const e)
{
    produceMouseDragged(e);
}

void Component::mouseWheelMoved(MouseWheelEventDetails* const e)
{
    produceMouseWheelMoved(e);
}

void Component::keyPressed(KeyEventDetails* const e)
{
    produceKeyPressed(e);
}

void Component::keyReleased(KeyEventDetails* const e)
{
    produceKeyReleased(e);
}

void Component::keyTyped(KeyEventDetails* const e)
{
    produceKeyTyped(e);

    if(getFocused() &&
       !e->isConsumed() &&
       e->getKey() == KeyEventDetails::KEY_TAB)
    {
        if(e->getModifiers() & KeyEventDetails::KEY_MODIFIER_SHIFT)
        {
            moveFocusPrev();
        }
        else if(e->getModifiers() == 0)
        {
            moveFocusNext();
        }
    }
}

void Component::focusGained(FocusEventDetails* const e)
{
    produceFocusGained(e);
}

void Component::focusLost(FocusEventDetails* const e)
{
    produceFocusLost(e);
}

bool Component::giveFocus(Component* const NewFocusedComponent, bool Temporary)
{
    if(this == NewFocusedComponent)
    {
        return true;
    }
    else
    {
        setFocused(false);
        FocusEventDetailsUnrecPtr Details(FocusEventDetails::create(this,getSystemTime(),Temporary, NewFocusedComponent));
        focusLost(Details);
        return true;
    }
}

bool Component::takeFocus(bool Temporary)
{

    if(getFocused() &&
       getParentWindow() != NULL &&
       getParentWindow()->getFocusedComponent() == this)
    {
        return true;
    }
    setFocused(true);
    if(Temporary || getParentWindow() == NULL)
    {
        FocusEventDetailsUnrecPtr Details(FocusEventDetails::create(this,getSystemTime(),Temporary, NULL));
        focusGained(Details);
    }
    else
    {
        if(getParentWindow()->getFocusedComponent() != NULL)
        {
            getParentWindow()->getFocusedComponent()->giveFocus(this);
        }
        getParentWindow()->setFocusedComponent(this);
        FocusEventDetailsUnrecPtr Details(FocusEventDetails::create(this,getSystemTime(),Temporary, getParentWindow()->getFocusedComponent()));
        focusGained(Details);
    }
    return true;
}

Real32 Component::getBaseline(const Real32& x, const Real32& y) const
{
    return -1.0f;
}

Vec2f Component::getPreferredScrollableViewportSize(void)
{
    return getPreferredSize();
}

Int32 Component::getScrollableBlockIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
    UInt16 MajorAxis;
    if(orientation == ScrollBar::VERTICAL_ORIENTATION)
    {
        MajorAxis = 1;
    }
    else
    {
        MajorAxis = 0;
    }

    return direction * (VisibleRectBottomRight[MajorAxis] - VisibleRectTopLeft[MajorAxis]);
}

bool Component::getScrollableTracksViewportHeight(void)
{
    return getScrollTrackingCharacteristics() & SCROLLABLE_TRACKS_VIEWPORT_HEIGHT;
}

bool Component::getScrollableTracksViewportWidth(void)
{
    return getScrollTrackingCharacteristics() & SCROLLABLE_TRACKS_VIEWPORT_WIDTH;
}

bool Component::getScrollableHeightMinTracksViewport(void)
{
    return getScrollTrackingCharacteristics() & SCROLLABLE_HEIGHT_MIN_TRACKS_VIEWPORT;
}

bool Component::getScrollableWidthMinTracksViewport(void)
{
    return getScrollTrackingCharacteristics() & SCROLLABLE_WIDTH_MIN_TRACKS_VIEWPORT;
}

void Component::setScrollableTracksViewportHeight(bool enable)
{
    UInt32 NewMask(getScrollTrackingCharacteristics());
    if(enable)
    {
        NewMask |= static_cast<UInt16>(SCROLLABLE_TRACKS_VIEWPORT_HEIGHT);
    }
    else
    {
        NewMask &= ~static_cast<UInt16>(SCROLLABLE_TRACKS_VIEWPORT_HEIGHT);
    }
    setScrollTrackingCharacteristics(NewMask);
}

void Component::setScrollableTracksViewportWidth(bool enable)
{
    UInt32 NewMask(getScrollTrackingCharacteristics());
    if(enable)
    {
        NewMask |= static_cast<UInt16>(SCROLLABLE_TRACKS_VIEWPORT_WIDTH);
    }
    else
    {
        NewMask &= ~static_cast<UInt16>(SCROLLABLE_TRACKS_VIEWPORT_WIDTH);
    }
    setScrollTrackingCharacteristics(NewMask);
}

void Component::setScrollableHeightMinTracksViewport(bool enable)
{
    UInt32 NewMask(getScrollTrackingCharacteristics());
    if(enable)
    {
        NewMask |= static_cast<UInt16>(SCROLLABLE_HEIGHT_MIN_TRACKS_VIEWPORT);
    }
    else
    {
        NewMask &= ~static_cast<UInt16>(SCROLLABLE_HEIGHT_MIN_TRACKS_VIEWPORT);
    }
    setScrollTrackingCharacteristics(NewMask);
}

void Component::setScrollableWidthMinTracksViewport(bool enable)
{
    UInt32 NewMask(getScrollTrackingCharacteristics());
    if(enable)
    {
        NewMask |= static_cast<UInt16>(SCROLLABLE_WIDTH_MIN_TRACKS_VIEWPORT);
    }
    else
    {
        NewMask &= ~static_cast<UInt16>(SCROLLABLE_WIDTH_MIN_TRACKS_VIEWPORT);
    }
    setScrollTrackingCharacteristics(NewMask);
}

Int32 Component::getScrollableUnitIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
    UInt16 MajorAxis;
    if(orientation == ScrollBar::VERTICAL_ORIENTATION)
    {
        MajorAxis = 1;
    }
    else
    {
        MajorAxis = 0;
    }

    return direction * 5;
}

void Component::scrollToPoint(const Pnt2f& PointInComponent)
{
    if(getParentContainer() != NULL &&
       getParentContainer()->getType() == UIViewport::getClassType())
    {
        dynamic_cast<UIViewport*>(getParentContainer())->setViewPosition(PointInComponent);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void Component::resolveLinks(void)
{
    Inherited::resolveLinks();

    _ToolTipActivateUpdateConnection.disconnect();
    _ToolTipActivateMouseEnterConnection.disconnect();
    _ToolTipActivateMouseExitConnection.disconnect();
    _ActiveTooltipClickConnection.disconnect();
    _ActiveTooltipExitConnection.disconnect();
    _ActiveTooltipPressConnection.disconnect();
    _ActiveTooltipReleaseConnection.disconnect();
}

/*----------------------- constructors & destructors ----------------------*/

Component::Component(void) :
    Inherited(),
    _MouseInComponentLastMouse(false),
    _ParentWindow(NULL),
    _TimeSinceMouseEntered(0.0),
    _IsToolTipActive(false)
{
}

Component::Component(const Component &source) :
    Inherited(source),
    _MouseInComponentLastMouse(false),
    _ParentWindow(NULL),
    _TimeSinceMouseEntered(0.0),
    _IsToolTipActive(false)
{
}

Component::~Component(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Component::changed(ConstFieldMaskArg whichField, 
                        UInt32            origin,
                        BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if( (whichField & MinSizeFieldMask) ||
        (whichField & MaxSizeFieldMask) ||
        (whichField & PreferredSizeFieldMask) ||
        (whichField & ConstraintsFieldMask))
    {
        //Layout needs to be recalculated for my parent ComponentContainer
        updateContainerLayout();
    }

    if( (whichField & SizeFieldMask) ||
        (whichField & PositionFieldMask) )
    {
        updateClipBounds();
    }

    if( (whichField & SizeFieldMask) )
    {
        produceComponentResized();
    }
    if( (whichField & PositionFieldMask) )
    {
        produceComponentMoved();
    }
    if( (whichField & EnabledFieldMask) )
    {
        if(getEnabled())
        {
            produceComponentEnabled();    
        }
        else
        {
            produceComponentDisabled();    
        }
    }
    if( (whichField & VisibleFieldMask) )
    {
        if(getVisible())
        {
            produceComponentVisible();    
        }
        else
        {
            produceComponentHidden();    
        }
    }

    if(whichField & ToolTipFieldMask)
    {
        _ToolTipActivateMouseEnterConnection.disconnect();
        _ToolTipActivateMouseExitConnection.disconnect();

        if(getToolTip() != NULL)
        {
            getToolTip()->setVisible(true);
            getToolTip()->setEnabled(true);
            getToolTip()->updateClipBounds();

            getToolTip()->setPosition(Pnt2f(0.0f,0.0f));

            _ToolTipActivateMouseEnterConnection = connectMouseEntered(boost::bind(&Component::handleToolTipActivateMouseEntered, this, _1));
            _ToolTipActivateMouseExitConnection = connectMouseExited(boost::bind(&Component::handleToolTipActivateMouseExited, this, _1));
        }
    }

    if((whichField & CursorFieldMask) &&
       _MouseInComponentLastMouse &&
       getParentWindow() != NULL &&
       getParentWindow()->getParentDrawingSurface() != NULL &&
       getParentWindow()->getParentDrawingSurface()->getEventProducer() != NULL)
    {
        getParentWindow()->getParentDrawingSurface()->getEventProducer()->setCursorType(getCursor());
    }
}

void Component::dump(      UInt32    ,
                           const BitVector ) const
{
    SLOG << "Dump Component NI" << std::endl;
}

void Component::produceComponentResized(void)
{
    ComponentEventDetailsUnrecPtr Details(ComponentEventDetails::create(this,getSystemTime()));

    Inherited::produceComponentResized(Details);
}

void Component::produceComponentMoved(void)
{
    ComponentEventDetailsUnrecPtr Details(ComponentEventDetails::create(this,getSystemTime()));

    Inherited::produceComponentMoved(Details);
}

void Component::produceComponentEnabled(void)
{
    ComponentEventDetailsUnrecPtr Details(ComponentEventDetails::create(this,getSystemTime()));

    Inherited::produceComponentEnabled(Details);
}

void Component::produceComponentDisabled(void)
{
    ComponentEventDetailsUnrecPtr Details(ComponentEventDetails::create(this,getSystemTime()));

    Inherited::produceComponentDisabled(Details);
}

void Component::produceComponentVisible(void)
{
    ComponentEventDetailsUnrecPtr Details(ComponentEventDetails::create(this,getSystemTime()));

    Inherited::produceComponentVisible(Details);
}

void Component::produceComponentHidden(void)
{
    ComponentEventDetailsUnrecPtr Details(ComponentEventDetails::create(this,getSystemTime()));

    Inherited::produceComponentHidden(Details);
}

void Component::produceToolTipActivated  (void)
{
    ComponentEventDetailsUnrecPtr Details(ComponentEventDetails::create(this,getSystemTime()));

    Inherited::produceToolTipActivated(Details);
}

void Component::produceToolTipDeactivated(void)
{
    ComponentEventDetailsUnrecPtr Details(ComponentEventDetails::create(this,getSystemTime()));

    Inherited::produceToolTipDeactivated(Details);
}

void Component::updateContainerLayout(void)
{
    if(getParentContainer() != NULL)
    {
        dynamic_cast<ComponentContainer*>(getParentContainer())->updateLayout();
    }
}

void Component::setToolTipText(const std::string& ToolTipText)
{
    ComponentRefPtr TheToolTip = createDefaultToolTip();
    if(TheToolTip->getType().isDerivedFrom(TextComponent::getClassType()))
    {
        dynamic_pointer_cast<TextComponent>(TheToolTip)->setText(ToolTipText);
    }

    setToolTip(TheToolTip);
}

void Component::activateToolTip(void)
{
    if(getToolTip() != NULL &&
       !isToolTipActive()   &&
       getParentWindow() != NULL)
    {
        _IsToolTipActive = true;
        getParentWindow()->pushToToolTips(getToolTip());

        _ActiveTooltipClickConnection = connectMouseClicked(boost::bind(&Component::handleDeactivateToolTipEvent, this, _1));
        _ActiveTooltipExitConnection = connectMouseExited(boost::bind(&Component::handleDeactivateToolTipEvent, this, _1));
        _ActiveTooltipPressConnection = connectMousePressed(boost::bind(&Component::handleDeactivateToolTipEvent, this, _1));
        _ActiveTooltipReleaseConnection = connectMouseReleased(boost::bind(&Component::handleDeactivateToolTipEvent, this, _1));

        produceToolTipActivated();
    }
}

void Component::deactivateToolTip(void)
{
    if(isToolTipActive())
    {
        _TimeSinceMouseEntered = 0.0f;
        _IsToolTipActive = false;

        _ActiveTooltipClickConnection.disconnect();
        _ActiveTooltipExitConnection.disconnect();
        _ActiveTooltipPressConnection.disconnect();
        _ActiveTooltipReleaseConnection.disconnect();

        if(getParentWindow() != NULL)
        {
            getParentWindow()->removeObjFromToolTips(getToolTip());
        }
        produceToolTipDeactivated();
    }
}

Pnt2f Component::getToolTipLocation(void) const
{
    Pnt2f Result(0.0f,0.0f);
    if(getToolTip() != NULL)
    {
        Result = getToolTip()->getPosition();
    }

    return Result;
}

void Component::setToolTipLocation(const Pnt2f& Location)
{
    if(getToolTip() != NULL)
    {
        if(getParentWindow() != NULL &&
           getParentWindow()->getParentDrawingSurface() != NULL)
        {
            getToolTip()->setPosition(ComponentToFrame(Location,this));
        }
        else
        {
            getToolTip()->setPosition(Location);
        }
    }
}

void Component::handleToolTipActivateUpdate(UpdateEventDetails* const e)
{
    _TimeSinceMouseEntered += e->getElapsedTime();
    if(!isToolTipActive() &&
       _TimeSinceMouseEntered >= LookAndFeelManager::the()->getLookAndFeel()->getToolTipPopupTime())
    {
        Pnt2f Location(0.0f,0.0f);

        if(getParentWindow() != NULL &&
           getParentWindow()->getParentDrawingSurface() != NULL)
        {
            //TODO: Make this configurable
            Vec2f DefaultToolTipOffset(5,18);

            Location = DrawingSurfaceToComponent(getParentWindow()->getParentDrawingSurface()->getMousePosition(),this)
                + DefaultToolTipOffset;
        }

        setToolTipLocation(Location);
        activateToolTip();
    }
}

void Component::handleToolTipActivateMouseEntered(MouseEventDetails* const e)
{
    _TimeSinceMouseEntered = 0.0f;
    if( getParentWindow() != NULL &&
        getParentWindow()->getParentDrawingSurface() != NULL &&
        getParentWindow()->getParentDrawingSurface()->getEventProducer() != NULL)
    {
        _ToolTipActivateUpdateConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectUpdate(boost::bind(&Component::handleToolTipActivateUpdate, this, _1));
    }
}

void Component::handleToolTipActivateMouseExited(MouseEventDetails* const e)
{
    _ToolTipActivateUpdateConnection.disconnect();
}

void Component::handleDeactivateToolTipEvent(MouseEventDetails* const e)
{
    deactivateToolTip();
}

OSG_END_NAMESPACE
