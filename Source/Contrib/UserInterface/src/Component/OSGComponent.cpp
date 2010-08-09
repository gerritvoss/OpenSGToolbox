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

#include "OSGComponent.h"
#include "OSGViewport.h"
#include "OSGWindowEventProducer.h"

#include "OSGComponentContainer.h"
#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"
#include "OSGUIDrawingSurfaceMouseTransformFunctor.h"
#include "OSGToolTip.h"
#include "OSGUIDrawUtils.h"
#include "OSGLookAndFeelManager.h"
#include "OSGPopupMenu.h"
#include "OSGScrollBar.h"
#include "OSGLayoutConstraints.h"

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

bool Component::useBoundsForClipping(void) const
{
    return true;
}

EventConnection Component::addKeyListener(KeyListenerPtr Listener)
{
    _KeyListeners.insert(Listener);
    return EventConnection(
                           boost::bind(&Component::isKeyListenerAttached, this, Listener),
                           boost::bind(&Component::removeKeyListener, this, Listener));
}

void Component::removeKeyListener(KeyListenerPtr Listener)
{
    KeyListenerSetItor EraseIter(_KeyListeners.find(Listener));
    if(EraseIter != _KeyListeners.end())
    {
        _KeyListeners.erase(EraseIter);
    }
}

EventConnection Component::addMouseListener(MouseListenerPtr Listener)
{
    _MouseListeners.insert(Listener);
    return EventConnection(
                           boost::bind(&Component::isMouseListenerAttached, this, Listener),
                           boost::bind(&Component::removeMouseListener, this, Listener));
}

void Component::removeMouseListener(MouseListenerPtr Listener)
{
    MouseListenerSetItor EraseIter(_MouseListeners.find(Listener));
    if(EraseIter != _MouseListeners.end())
    {
        _MouseListeners.erase(EraseIter);
    }
}

EventConnection Component::addMouseWheelListener(MouseWheelListenerPtr Listener)
{
    _MouseWheelListeners.insert(Listener);
    return EventConnection(
                           boost::bind(&Component::isMouseWheelListenerAttached, this, Listener),
                           boost::bind(&Component::removeMouseWheelListener, this, Listener));
}

void Component::removeMouseWheelListener(MouseWheelListenerPtr Listener)
{
    MouseWheelListenerSetItor EraseIter(_MouseWheelListeners.find(Listener));
    if(EraseIter != _MouseWheelListeners.end())
    {
        _MouseWheelListeners.erase(EraseIter);
    }
}

EventConnection Component::addMouseMotionListener(MouseMotionListenerPtr Listener)
{
    _MouseMotionListeners.insert(Listener);
    return EventConnection(
                           boost::bind(&Component::isMouseMotionListenerAttached, this, Listener),
                           boost::bind(&Component::removeMouseMotionListener, this, Listener));
}

void Component::removeMouseMotionListener(MouseMotionListenerPtr Listener)
{
    MouseMotionListenerSetItor EraseIter(_MouseMotionListeners.find(Listener));
    if(EraseIter != _MouseMotionListeners.end())
    {
        _MouseMotionListeners.erase(EraseIter);
    }
}

EventConnection Component::addFocusListener(FocusListenerPtr Listener)
{
    _FocusListeners.insert(Listener);
    return EventConnection(
                           boost::bind(&Component::isFocusListenerAttached, this, Listener),
                           boost::bind(&Component::removeFocusListener, this, Listener));
}

void Component::removeFocusListener(FocusListenerPtr Listener)
{
    FocusListenerSetItor EraseIter(_FocusListeners.find(Listener));
    if(EraseIter != _FocusListeners.end())
    {
        _FocusListeners.erase(EraseIter);
    }
}

EventConnection Component::addComponentListener(ComponentListener* Listener)
{
    _ComponentListeners.insert(Listener);
    return EventConnection(
                           boost::bind(&Component::isComponentListenerAttached, this, Listener),
                           boost::bind(&Component::removeComponentListener, this, Listener));
}

void Component::removeComponentListener(ComponentListener* Listener)
{
    ComponentListenerSetItor EraseIter(_ComponentListeners.find(Listener));
    if(EraseIter != _ComponentListeners.end())
    {
        _ComponentListeners.erase(EraseIter);
    }
}

void Component::detachFromEventProducer(void)
{
    _ActivateToolTipListener.disconnect();
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

void Component::setBorders(BorderRefPtr TheBorder)
{
    setBorder(TheBorder);
    setDisabledBorder(TheBorder);
    setFocusedBorder(TheBorder);
    setRolloverBorder(TheBorder);
}

void Component::setBackgrounds(LayerRefPtr TheBackground)
{
    setBackground(TheBackground);
    setDisabledBackground(TheBackground);
    setFocusedBackground(TheBackground);
    setRolloverBackground(TheBackground);
}


void Component::setForegrounds(LayerRefPtr TheForeground)
{
    setForeground(TheForeground);
    setDisabledForeground(TheForeground);
    setFocusedForeground(TheForeground);
    setRolloverForeground(TheForeground);
}

BorderRefPtr Component::getDrawnBorder(void) const
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

LayerRefPtr Component::getDrawnBackground(void) const
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

LayerRefPtr Component::getDrawnForeground(void) const
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
    Pnt2f PointInCompSpace(DrawingSurfaceToComponent(p,this));
    BorderRefPtr DrawnBorder(getDrawnBorder());
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

Pnt2f Component::getToolTipLocation(Pnt2f MousePosition)
{
    //TODO:Implement
    return DrawingSurfaceToComponent(MousePosition,ComponentRefPtr(this)) + Vec2f(5,20);
}

ToolTipRefPtr Component::createToolTip(void)
{
    return ToolTip::create();
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

void Component::drawBorder(const GraphicsWeakPtr TheGraphics, const BorderRefPtr Border, Real32 Opacity) const
{
    if(Border != NULL)
    {
        //Draw My Border
        Border->draw(TheGraphics,0,0,getSize().x(),getSize().y(), getOpacity()*Opacity, getClipping());
    }
}

void Component::drawBackground(const GraphicsWeakPtr TheGraphics, const LayerRefPtr Background, Real32 Opacity) const
{
    //Draw the Background on the Inside of my border
    if(Background != NULL)
    {
        Pnt2f TopLeft, BottomRight;
        getInsideBorderBounds(TopLeft, BottomRight);
        Background->draw(TheGraphics, TopLeft, BottomRight, getOpacity()*Opacity);
    }
}

void Component::drawForeground(const GraphicsWeakPtr TheGraphics, const LayerRefPtr Foreground, Real32 Opacity) const
{
    //Draw the Foreground on the Inside of my border
    if(Foreground != NULL)
    {
        Pnt2f TopLeft, BottomRight;
        getInsideBorderBounds(TopLeft, BottomRight);
        Foreground->draw(TheGraphics, TopLeft, BottomRight, getOpacity()*Opacity);
    }
}

bool Component::setupClipping(const GraphicsWeakPtr Graphics) const
{

    if(getClipping())
    {    
        //Get Clipping initial settings
        Pnt2f ClipTopLeft,ClipBottomRight;
        getClipBounds(ClipTopLeft,ClipBottomRight);

        Vec4d LeftPlaneEquation(1.0,0.0,0.0,-ClipTopLeft.x()+ Graphics->getClipPlaneOffset()),
              RightPlaneEquation(-1.0,0.0,0.0,ClipBottomRight.x() + Graphics->getClipPlaneOffset()),
              TopPlaneEquation(0.0,1.0,0.0,-ClipTopLeft.y() + Graphics->getClipPlaneOffset()),
              BottomPlaneEquation(0.0,-1.0,0.0,ClipBottomRight.y() + Graphics->getClipPlaneOffset());

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
    return true;
}

void Component::draw(const GraphicsWeakPtr TheGraphics, Real32 Opacity) const
{
    if (!getVisible())
        return;

    GLdouble InitMat[16];
    glGetDoublev(GL_MODELVIEW_MATRIX, InitMat);
    //Translate to my position
    glTranslatef(getPosition().x(), getPosition().y(), 0);

    if(setupClipping(TheGraphics))
    {

        //Activate My Border Drawing constraints
        BorderRefPtr DrawnBorder = getDrawnBorder();
        if(DrawnBorder != NULL)
        {
            DrawnBorder->activateInternalDrawConstraints(TheGraphics,0,0,getSize().x(),getSize().y());
        }


        //Draw My Background
        drawBackground(TheGraphics, getDrawnBackground(), Opacity);

        //Draw Internal
        drawInternal(TheGraphics, Opacity);

        //Set Clipping to initial settings
        setupClipping(TheGraphics);

        //Draw My Foreground
        drawForeground(TheGraphics, getDrawnForeground(), Opacity);

        //Draw all parts that should not be clipped against
        drawUnclipped(TheGraphics, Opacity);
    }

    //Undo the Translation to Component Space
    glLoadMatrixd(InitMat);
}


void Component::drawUnclipped(const GraphicsWeakPtr TheGraphics, Real32 Opacity) const
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
        //My Bounds
        //My Parent Containers Clip Bounds
        //My Parent Containers Inset Bounds
        Pnt2f MyTopLeft,MyBottomRight;
        getBounds(MyTopLeft,MyBottomRight);

        //Update my Parent ComponentContainer's Clip Bounds
        //dynamic_cast<ComponentContainer*>(getParentContainer())->updateClipBounds();

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
    setClipTopLeft(TopLeft);
    setClipBottomRight(BottomRight);
}

void Component::mouseClicked(const MouseEventUnrecPtr e)
{
    produceMouseClicked(e);
}

void Component::mouseEntered(const MouseEventUnrecPtr e)
{
    produceMouseEntered(e);
}

void Component::mouseExited(const MouseEventUnrecPtr e)
{
    produceMouseExited(e);
}

void Component::mousePressed(const MouseEventUnrecPtr e)
{
    produceMousePressed(e);

    if(e->getButton() == MouseEvent::BUTTON3
       && getPopupMenu() != NULL)
    {
        getPopupMenu()->setInvoker(ComponentRefPtr(this));
        getPopupMenu()->setVisible(true);
        getPopupMenu()->setPosition(ViewportToComponent(e->getLocation(),getParentWindow(),e->getViewport()));

        getParentWindow()->pushToActivePopupMenus(getPopupMenu());
    }
}

void Component::mouseReleased(const MouseEventUnrecPtr e)
{
    produceMouseReleased(e);
}


void Component::mouseMoved(const MouseEventUnrecPtr e)
{

    if(getParentWindow() != NULL && getParentWindow()->getDrawingSurface()!=NULL&&getParentWindow()->getDrawingSurface()->getEventProducer() != NULL)
    {
        getParentWindow()->getDrawingSurface()->getEventProducer()->setCursorType(queryCursor(e->getLocation()));
    }
    produceMouseMoved(e);
}

void Component::mouseDragged(const MouseEventUnrecPtr e)
{
    produceMouseDragged(e);
}

void Component::mouseWheelMoved(const MouseWheelEventUnrecPtr e)
{
    produceMouseWheelMoved(e);
}

void Component::keyPressed(const KeyEventUnrecPtr e)
{
    produceKeyPressed(e);
}

void Component::keyReleased(const KeyEventUnrecPtr e)
{
    produceKeyReleased(e);
}

void Component::keyTyped(const KeyEventUnrecPtr e)
{
    produceKeyTyped(e);
}

void Component::focusGained(const FocusEventUnrecPtr e)
{
    produceFocusGained(e);
}

void Component::focusLost(const FocusEventUnrecPtr e)
{
    produceFocusLost(e);
}

//Producers
void Component::produceMouseWheelMoved(const MouseWheelEventUnrecPtr e)
{
    for(MouseWheelListenerSetConstItor SetItor(_MouseWheelListeners.begin()) ; SetItor != _MouseWheelListeners.end() ; ++SetItor)
    {
        (*SetItor)->mouseWheelMoved(e);
    }
    _Producer.produceEvent(MouseWheelMovedMethodId,e);
}

void Component::produceMouseMoved(const MouseEventUnrecPtr e)
{
    for(MouseMotionListenerSetConstItor SetItor(_MouseMotionListeners.begin()) ; SetItor != _MouseMotionListeners.end() ; ++SetItor)
    {
        (*SetItor)->mouseMoved(e);
    }
    _Producer.produceEvent(MouseMovedMethodId,e);
}

void Component::produceMouseDragged(const MouseEventUnrecPtr e)
{
    for(MouseMotionListenerSetConstItor SetItor(_MouseMotionListeners.begin()) ; SetItor != _MouseMotionListeners.end() ; ++SetItor)
    {
        (*SetItor)->mouseDragged(e);
    }
    _Producer.produceEvent(MouseDraggedMethodId,e);
}

void Component::produceMouseClicked(const MouseEventUnrecPtr e)
{
    MouseListenerSet ListenerSet(_MouseListeners);
    for(MouseListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->mouseClicked(e);
    }
    _Producer.produceEvent(MouseClickedMethodId,e);
}

void Component::produceMouseEntered(const MouseEventUnrecPtr e)
{
    MouseListenerSet ListenerSet(_MouseListeners);
    for(MouseListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->mouseEntered(e);
    }
    _Producer.produceEvent(MouseEnteredMethodId,e);
}

void Component::produceMouseExited(const MouseEventUnrecPtr e)
{
    MouseListenerSet ListenerSet(_MouseListeners);
    for(MouseListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->mouseExited(e);
    }
    _Producer.produceEvent(MouseExitedMethodId,e);
}

void Component::produceMousePressed(const MouseEventUnrecPtr e)
{
    MouseListenerSet ListenerSet(_MouseListeners);
    for(MouseListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->mousePressed(e);
    }
    _Producer.produceEvent(MousePressedMethodId,e);
}

void Component::produceMouseReleased(const MouseEventUnrecPtr e)
{
    MouseListenerSet ListenerSet(_MouseListeners);
    for(MouseListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->mouseReleased(e);
    }
    _Producer.produceEvent(MouseReleasedMethodId,e);
}

void Component::produceKeyPressed(const KeyEventUnrecPtr e)
{
    KeyListenerSet ListenerSet(_KeyListeners);
    for(KeyListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->keyPressed(e);
    }
    _Producer.produceEvent(KeyPressedMethodId,e);
}

void Component::produceKeyReleased(const KeyEventUnrecPtr e)
{
    for(KeyListenerSetConstItor SetItor(_KeyListeners.begin()) ; SetItor != _KeyListeners.end() ; ++SetItor)
    {
        (*SetItor)->keyReleased(e);
    }
    _Producer.produceEvent(KeyReleasedMethodId,e);
}

void Component::produceKeyTyped(const KeyEventUnrecPtr e)
{
    for(KeyListenerSetConstItor SetItor(_KeyListeners.begin()) ; SetItor != _KeyListeners.end() ; ++SetItor)
    {
        (*SetItor)->keyTyped(e);
    }
    _Producer.produceEvent(KeyTypedMethodId,e);
}

void  Component::produceFocusGained(const FocusEventUnrecPtr e)
{
    FocusListenerSet ListenerSet(_FocusListeners);
    for(FocusListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->focusGained(e);
    }
    _Producer.produceEvent(FocusGainedMethodId,e);
}

void  Component::produceFocusLost(const FocusEventUnrecPtr e)
{
    FocusListenerSet ListenerSet(_FocusListeners);
    for(FocusListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->focusLost(e);
    }
    _Producer.produceEvent(FocusLostMethodId,e);
}

void  Component::produceComponentHidden(const ComponentEventUnrecPtr e)
{
    for(ComponentListenerSetConstItor SetItor(_ComponentListeners.begin()) ; SetItor != _ComponentListeners.end() ; ++SetItor)
    {
        (*SetItor)->componentHidden(e);
    }
    _Producer.produceEvent(ComponentHiddenMethodId,e);
}

void  Component::produceComponentVisible(const ComponentEventUnrecPtr e)
{
    for(ComponentListenerSetConstItor SetItor(_ComponentListeners.begin()) ; SetItor != _ComponentListeners.end() ; ++SetItor)
    {
        (*SetItor)->componentVisible(e);
    }
    _Producer.produceEvent(ComponentVisibleMethodId,e);
}

void  Component::produceComponentMoved(const ComponentEventUnrecPtr e)
{
    for(ComponentListenerSetConstItor SetItor(_ComponentListeners.begin()) ; SetItor != _ComponentListeners.end() ; ++SetItor)
    {
        (*SetItor)->componentMoved(e);
    }
    _Producer.produceEvent(ComponentMovedMethodId,e);
}

void  Component::produceComponentResized(const ComponentEventUnrecPtr e)
{
    for(ComponentListenerSetConstItor SetItor(_ComponentListeners.begin()) ; SetItor != _ComponentListeners.end() ; ++SetItor)
    {
        (*SetItor)->componentResized(e);
    }
    _Producer.produceEvent(ComponentResizedMethodId,e);
}

void  Component::produceComponentEnabled(const ComponentEventUnrecPtr e)
{
    for(ComponentListenerSetConstItor SetItor(_ComponentListeners.begin()) ; SetItor != _ComponentListeners.end() ; ++SetItor)
    {
        (*SetItor)->componentEnabled(e);
    }
    _Producer.produceEvent(ComponentEnabledMethodId,e);
}

void  Component::produceComponentDisabled(const ComponentEventUnrecPtr e)
{
    for(ComponentListenerSetConstItor SetItor(_ComponentListeners.begin()) ; SetItor != _ComponentListeners.end() ; ++SetItor)
    {
        (*SetItor)->componentDisabled(e);
    }
    _Producer.produceEvent(ComponentDisabledMethodId,e);
}

bool Component::giveFocus(ComponentRefPtr NewFocusedComponent, bool Temporary)
{
    if(this == NewFocusedComponent)
    {
        return true;
    }
    else
    {
        setFocused(false);
        focusLost(FocusEvent::create(ComponentRefPtr(this),getSystemTime(),Temporary, NewFocusedComponent));
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
        focusGained(FocusEvent::create(this,getSystemTime(),Temporary, NULL));
    }
    else
    {
        if(getParentWindow()->getFocusedComponent() != NULL)
        {
            getParentWindow()->getFocusedComponent()->giveFocus(this);
        }
        getParentWindow()->setFocusedComponent(this);
        focusGained(FocusEvent::create(this,getSystemTime(),Temporary, getParentWindow()->getFocusedComponent()));
    }
    return true;
}

Real32 Component::getBaseline(const Real32& x, const Real32& y) const
{
    return -1;
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
    return false;
}

bool Component::getScrollableTracksViewportWidth(void)
{
    return false;
}

bool Component::getScrollableHeightMinTracksViewport(void)
{
    return false;
}

bool Component::getScrollableWidthMinTracksViewport(void)
{
    return false;
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

/*----------------------- constructors & destructors ----------------------*/

Component::Component(void) :
    Inherited(),
    _MouseInComponentLastMouse(false),
    _TimeSinceMouseEntered(0.0),
    _ComponentUpdater(this),
    _ActivateToolTipListener(this),
    _DeactivateToolTipListener(this)
{
}

Component::Component(const Component &source) :
    Inherited(source),
    _MouseInComponentLastMouse(false),
    _TimeSinceMouseEntered(0.0),
    _ComponentUpdater(this),
    _ActivateToolTipListener(this),
    _DeactivateToolTipListener(this)
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

    if( (whichField & ConstraintsFieldMask) &&
        getConstraints() != NULL)
    {
        getConstraints()->setParentComponent(this);
    }

    if( (whichField & SizeFieldMask) )
    {
        produceComponentResized( ComponentEvent::create(ComponentRefPtr(this),getSystemTime()) );
    }
    if( (whichField & PositionFieldMask) )
    {
        produceComponentMoved( ComponentEvent::create(ComponentRefPtr(this),getSystemTime()) );
    }
    if( (whichField & EnabledFieldMask) )
    {
        if(getEnabled())
        {
            produceComponentEnabled( ComponentEvent::create(ComponentRefPtr(this),getSystemTime()) );    
        }
        else
        {
            produceComponentDisabled( ComponentEvent::create(ComponentRefPtr(this),getSystemTime()) );    
        }
    }
    if( (whichField & VisibleFieldMask) )
    {
        if(getVisible())
        {
            produceComponentVisible( ComponentEvent::create(ComponentRefPtr(this),getSystemTime()) );    
        }
        else
        {
            produceComponentHidden( ComponentEvent::create(ComponentRefPtr(this),getSystemTime()) );    
        }
    }

    if( (whichField & ToolTipTextFieldMask))
    {
        if(getToolTipText().compare(std::string("")) != 0)
        {
            addMouseListener(&_ActivateToolTipListener);
        }
        else
        {
            removeMouseListener(&_ActivateToolTipListener);
        }
    }

    if((whichField & CursorFieldMask) &&
       _MouseInComponentLastMouse &&
       getParentWindow() != NULL &&
       getParentWindow()->getDrawingSurface() != NULL &&
       getParentWindow()->getDrawingSurface()->getEventProducer() != NULL)
    {
        getParentWindow()->getDrawingSurface()->getEventProducer()->setCursorType(getCursor());
    }
}

void Component::dump(      UInt32    ,
                           const BitVector ) const
{
    SLOG << "Dump Component NI" << std::endl;
}

void Component::updateContainerLayout(void)
{
    if(getParentContainer() != NULL)
    {
        dynamic_cast<ComponentContainer*>(getParentContainer())->updateLayout();
    }
}

void Component::ComponentUpdater::update(const UpdateEventUnrecPtr e)
{
    _Component->_TimeSinceMouseEntered += e->getElapsedTime();
    if(_Component->_TimeSinceMouseEntered >= LookAndFeelManager::the()->getLookAndFeel()->getToolTipPopupTime() &&
       _Component->getParentWindow() != NULL &&
       _Component->getParentWindow()->getActiveToolTip() == NULL)
    {
        ToolTipRefPtr TheToolTip = _Component->createToolTip();
        TheToolTip->setTippedComponent(_Component);
        if(_Component->getParentWindow() != NULL &&
           _Component->getParentWindow()->getDrawingSurface() != NULL)
        {
            TheToolTip->setPosition(ComponentToFrame(_Component->getToolTipLocation(
                                                                                    _Component->getParentWindow()->getDrawingSurface()->getMousePosition()), _Component));
        }
        else
        {
            TheToolTip->setPosition(ComponentToFrame(_Component->getToolTipLocation(Pnt2f(0,0)),_Component));
        }
        TheToolTip->setText(_Component->getToolTipText());

        if(_Component->getParentWindow() != NULL)
        {
            _Component->getParentWindow()->setActiveToolTip(TheToolTip);
        }

        _Component->addMouseListener(&(_Component->_DeactivateToolTipListener));
    }
}

void Component::ActivateToolTipListener::mouseClicked(const MouseEventUnrecPtr e)
{
}

void Component::ActivateToolTipListener::mouseEntered(const MouseEventUnrecPtr e)
{
    _Component->_TimeSinceMouseEntered = 0.0f;
    if( _Component->getParentWindow() != NULL &&
        _Component->getParentWindow()->getDrawingSurface() != NULL &&
        _Component->getParentWindow()->getDrawingSurface()->getEventProducer() != NULL)
    {
        _Component->getParentWindow()->getDrawingSurface()->getEventProducer()->addUpdateListener(&(_Component->_ComponentUpdater));
    }
}

void Component::ActivateToolTipListener::mouseExited(const MouseEventUnrecPtr e)
{
    if( _Component->getParentWindow() != NULL &&
        _Component->getParentWindow()->getDrawingSurface() != NULL &&
        _Component->getParentWindow()->getDrawingSurface()->getEventProducer() != NULL)
    {
        disconnect();
    }
}

void Component::ActivateToolTipListener::disconnect(void)
{
    _Component->getParentWindow()->getDrawingSurface()->getEventProducer()->removeUpdateListener(&(_Component->_ComponentUpdater));
}

void Component::ActivateToolTipListener::mousePressed(const MouseEventUnrecPtr e)
{
}

void Component::ActivateToolTipListener::mouseReleased(const MouseEventUnrecPtr e)
{
}

void Component::DeactivateToolTipListener::mouseClicked(const MouseEventUnrecPtr e)
{
    _Component->_TimeSinceMouseEntered = 0.0f;
    if(_Component->getParentWindow() != NULL)
    {
        _Component->getParentWindow()->setActiveToolTip(NULL);
    }
    _Component->removeMouseListener(this);
}

void Component::DeactivateToolTipListener::mouseEntered(const MouseEventUnrecPtr e)
{
}

void Component::DeactivateToolTipListener::mouseExited(const MouseEventUnrecPtr e)
{
    _Component->_TimeSinceMouseEntered = 0.0f;
    if(_Component->getParentWindow() != NULL)
    {
        _Component->getParentWindow()->setActiveToolTip(NULL);
    }
    _Component->removeMouseListener(this);

}

void Component::DeactivateToolTipListener::mousePressed(const MouseEventUnrecPtr e)
{
    _Component->_TimeSinceMouseEntered = 0.0f;
    if(_Component->getParentWindow() != NULL)
    {
        _Component->getParentWindow()->setActiveToolTip(NULL);
    }
    _Component->removeMouseListener(this);
}

void Component::DeactivateToolTipListener::mouseReleased(const MouseEventUnrecPtr e)
{
    _Component->_TimeSinceMouseEntered = 0.0f;
    if(_Component->getParentWindow() != NULL)
    {
        _Component->getParentWindow()->setActiveToolTip(NULL);
    }
    _Component->removeMouseListener(this);
}

OSG_END_NAMESPACE
