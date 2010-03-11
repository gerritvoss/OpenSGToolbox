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

#include "OSGUIDrawingSurface.h"
#include "OSGUIDrawUtils.h"
#include "OSGUIDrawingSurfaceMouseTransformFunctor.h"

#include "OSGInternalWindow.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGUIDrawingSurfaceBase.cpp file.
// To modify it, please change the .fcd file (OSGUIDrawingSurface.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void UIDrawingSurface::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void UIDrawingSurface::openWindow(InternalWindowRefPtr TheWindow, const Int32 Layer)
{
    MFInternalWindowsType::iterator WindowItor(editMFInternalWindows()->find(TheWindow));

    if(WindowItor == editMFInternalWindows()->end())
    {
        pushToInternalWindows(TheWindow);

        if(Layer < 0 || Layer > getMFInternalWindows()->size())
        {
            moveWindowToTop(TheWindow);
        }
        else
        {
            setWindowToLayer(TheWindow, Layer);
        }

        if(getMFInternalWindows()->back() == TheWindow)
        {
            getMFInternalWindows()->back()->takeFocus();
        }

        TheWindow->open();
    }

}

void UIDrawingSurface::closeWindow(InternalWindowRefPtr TheWindow)
{
    MFInternalWindowsType::iterator WindowItor(editMFInternalWindows()->find(TheWindow));

    if(WindowItor != editMFInternalWindows()->end())
    {
        editMFInternalWindows()->erase(WindowItor);
    }

    if(getFocusedWindow() != NULL
       && getMFInternalWindows()->size() > 0)
    {
        getMFInternalWindows()->back()->takeFocus();
    }
}

UInt32 UIDrawingSurface::getNumWindowLayers(void) const
{
    return getMFInternalWindows()->size();
}

InternalWindowRefPtr UIDrawingSurface::getWindowAtLayer(const UInt32& Layer) const
{
    if(Layer < getMFInternalWindows()->size())
    {
        return getInternalWindows(Layer);
    }
    else
    {
        return NULL;
    }
}

Int32 UIDrawingSurface::getWindowLayer(InternalWindowRefPtr TheWindow) const
{
    UInt32 i(0);
    while(i<getMFInternalWindows()->size() &&
          getInternalWindows(i) != TheWindow)
    {
        ++i;
    }

    if(i < getMFInternalWindows()->size() )
    {
        return i;
    }
    else
    {
        return -1;
    }
}

void UIDrawingSurface::setWindowToLayer(InternalWindowRefPtr TheWindow, const UInt32& Layer)
{
    MFInternalWindowsType::iterator RemovalItor(editMFInternalWindows()->begin());
    while(RemovalItor != editMFInternalWindows()->end() &&
          (*RemovalItor) != TheWindow)
    {
        ++RemovalItor;
    }

    if(RemovalItor != editMFInternalWindows()->end() &&
       Layer < getMFInternalWindows()->size())
    {
        InternalWindowRefPtr SwapWindow(*RemovalItor);
        editMFInternalWindows()->erase(RemovalItor);

        MFInternalWindowsType::iterator InsertItor(editMFInternalWindows()->begin());
        for(UInt32 i(0) ; i<Layer ; ++i){++InsertItor;}

        editMFInternalWindows()->insert(InsertItor, SwapWindow);

        if(getFocusedWindow() != NULL)
        {
            getMFInternalWindows()->back()->takeFocus();
        }
    }
}

void UIDrawingSurface::moveWindowUp(InternalWindowRefPtr TheWindow)
{
    Int32 WindowLayer(getWindowLayer(TheWindow));
    if(WindowLayer < getMFInternalWindows()->size())
    {
        setWindowToLayer(TheWindow,  WindowLayer+1);
    }
}

void UIDrawingSurface::moveWindowDown(InternalWindowRefPtr TheWindow)
{
    Int32 WindowLayer(getWindowLayer(TheWindow));
    if(WindowLayer > 0)
    {
        setWindowToLayer(TheWindow,  WindowLayer-1);
    }
}

void UIDrawingSurface::moveWindowToTop(InternalWindowRefPtr TheWindow)
{
    MFInternalWindowsType::iterator RemovalItor(editMFInternalWindows()->begin());
    while(RemovalItor != editMFInternalWindows()->end() &&
          (*RemovalItor) != TheWindow)
    {
        ++RemovalItor;
    }

    if(RemovalItor != editMFInternalWindows()->end())
    {
        InternalWindowRefPtr SwapWindow(*RemovalItor);
        editMFInternalWindows()->erase(RemovalItor);

        MFInternalWindowsType::iterator InsertItor(editMFInternalWindows()->begin());
        if(TheWindow->getAllwaysOnTop())
        {
            InsertItor = editMFInternalWindows()->end();
        }
        else
        {
            while(InsertItor != editMFInternalWindows()->end() &&
                  !(*InsertItor)->getAllwaysOnTop())
            {
                ++InsertItor;
            }
        }

        MFInternalWindowsType::iterator NewPosition = editMFInternalWindows()->insert(InsertItor,SwapWindow);

        if(getFocusedWindow() != NULL)
        {
            getMFInternalWindows()->back()->takeFocus();
        }
    }
}

void UIDrawingSurface::moveWindowToBottom(InternalWindowRefPtr TheWindow)
{
    MFInternalWindowsType::iterator RemovalItor(editMFInternalWindows()->begin());
    while(RemovalItor != editMFInternalWindows()->end() &&
          (*RemovalItor) != TheWindow)
    {
        ++RemovalItor;
    }

    if(RemovalItor != editMFInternalWindows()->end())
    {
        InternalWindowRefPtr SwapWindow(*RemovalItor);
        editMFInternalWindows()->erase(RemovalItor);

        editMFInternalWindows()->insert(editMFInternalWindows()->begin(), SwapWindow);

        if(getFocusedWindow() != NULL)
        {
            getMFInternalWindows()->back()->takeFocus();
        }
    }
}

Pnt2f UIDrawingSurface::getMousePosition(void) const
{
    Pnt2f ViewportPoint(0,0);
    ViewportRefPtr TheViewport( getEventProducer()->windowToViewport(getEventProducer()->getMousePosition(),ViewportPoint) );
    Pnt2f Result(0,0);
    getMouseTransformFunctor()->viewportToRenderingSurface( ViewportPoint,TheViewport, Result);
    return Result;
}

void UIDrawingSurface::mouseClicked(const MouseEventUnrecPtr e)
{
    Pnt2f ResultMouseLoc;
    if(getMouseTransformFunctor()->viewportToRenderingSurface(e->getLocation(),e->getViewport(), ResultMouseLoc))
    {
        const MouseEventUnrecPtr TransformedMouseEvent = MouseEvent::create(e->getSource(), e->getTimeStamp(), e->getButton(), e->getClickCount(),
                                                                            ResultMouseLoc,e->getViewport());

        checkMouseEnterExit(TransformedMouseEvent, TransformedMouseEvent->getLocation(),TransformedMouseEvent->getViewport());

        for(Int32 i(getMFInternalWindows()->size()-1) ; i>=0 ; --i)
        {
            if(isContainedClipBounds(TransformedMouseEvent->getLocation(), getInternalWindows(i)))
            {
                getInternalWindows(i)->mouseClicked(TransformedMouseEvent);
                break;
            }
        }
    }
}

void UIDrawingSurface::mouseEntered(const MouseEventUnrecPtr e)
{
    Pnt2f ResultMouseLoc;
    if(getMouseTransformFunctor()->viewportToRenderingSurface(e->getLocation(),e->getViewport(), ResultMouseLoc))
    {
        const MouseEventUnrecPtr TransformedMouseEvent = MouseEvent::create(e->getSource(), e->getTimeStamp(), e->getButton(), e->getClickCount(),
                                                                            ResultMouseLoc,e->getViewport());

        checkMouseEnterExit(TransformedMouseEvent, TransformedMouseEvent->getLocation(),TransformedMouseEvent->getViewport());
    }
}

void UIDrawingSurface::mouseExited(const MouseEventUnrecPtr e)
{
    Pnt2f ResultMouseLoc;
    if(getMouseTransformFunctor()->viewportToRenderingSurface(e->getLocation(),e->getViewport(), ResultMouseLoc))
    {
        const MouseEventUnrecPtr TransformedMouseEvent = MouseEvent::create(e->getSource(), e->getTimeStamp(), e->getButton(), e->getClickCount(),
                                                                            ResultMouseLoc,e->getViewport());

        checkMouseEnterExit(TransformedMouseEvent, TransformedMouseEvent->getLocation(),TransformedMouseEvent->getViewport());
    }
}

void UIDrawingSurface::mousePressed(const MouseEventUnrecPtr e)
{
    Pnt2f ResultMouseLoc;
    if(getMouseTransformFunctor()->viewportToRenderingSurface(e->getLocation(),e->getViewport(), ResultMouseLoc))
    {
        const MouseEventUnrecPtr TransformedMouseEvent = MouseEvent::create(e->getSource(), e->getTimeStamp(), e->getButton(), e->getClickCount(),
                                                                            ResultMouseLoc,e->getViewport());

        checkMouseEnterExit(TransformedMouseEvent, TransformedMouseEvent->getLocation(),TransformedMouseEvent->getViewport());

        for(Int32 i(getMFInternalWindows()->size()-1) ; i>=0 ; --i)
        {
            if(isContainedClipBounds(TransformedMouseEvent->getLocation(), getInternalWindows(i)))
            {
                if(getInternalWindows(i) != getFocusedWindow())
                {
                    moveWindowToTop(getInternalWindows(i));
                }
                getMFInternalWindows()->back()->mousePressed(TransformedMouseEvent);
                break;
            }
        }
    }
}

void UIDrawingSurface::mouseReleased(const MouseEventUnrecPtr e)
{
    Pnt2f ResultMouseLoc;
    if(getMouseTransformFunctor()->viewportToRenderingSurface(e->getLocation(),e->getViewport(), ResultMouseLoc))
    {
        const MouseEventUnrecPtr TransformedMouseEvent = MouseEvent::create(e->getSource(), e->getTimeStamp(), e->getButton(), e->getClickCount(),
                                                                            ResultMouseLoc,e->getViewport());

        checkMouseEnterExit(TransformedMouseEvent, TransformedMouseEvent->getLocation(),TransformedMouseEvent->getViewport());

        for(Int32 i(getMFInternalWindows()->size()-1) ; i>=0 ; --i)
        {
            if(isContainedClipBounds(TransformedMouseEvent->getLocation(), getInternalWindows(i)))
            {
                getInternalWindows(i)->mouseReleased(TransformedMouseEvent);
                break;
            }
        }
    }
}


void UIDrawingSurface::mouseMoved(const MouseEventUnrecPtr e)
{
    Pnt2f ResultMouseLoc;
    if(getMouseTransformFunctor()->viewportToRenderingSurface(e->getLocation(),e->getViewport(), ResultMouseLoc))
    {
        const MouseEventUnrecPtr TransformedMouseEvent = MouseEvent::create(e->getSource(), e->getTimeStamp(), e->getButton(), e->getClickCount(),
                                                                            ResultMouseLoc,e->getViewport());

        checkMouseEnterExit(TransformedMouseEvent, TransformedMouseEvent->getLocation(),TransformedMouseEvent->getViewport());

        for(Int32 i(getMFInternalWindows()->size()-1) ; i>=0 ; --i)
        {
            if(isContainedClipBounds(TransformedMouseEvent->getLocation(), getInternalWindows(i)))
            {
                getInternalWindows(i)->mouseMoved(TransformedMouseEvent);
                break;
            }
        }
    }
}

void UIDrawingSurface::mouseDragged(const MouseEventUnrecPtr e)
{
    Pnt2f ResultMouseLoc;
    if(getMouseTransformFunctor()->viewportToRenderingSurface(e->getLocation(),e->getViewport(), ResultMouseLoc))
    {
        const MouseEventUnrecPtr TransformedMouseEvent = MouseEvent::create(e->getSource(), e->getTimeStamp(), e->getButton(), e->getClickCount(),
                                                                            ResultMouseLoc,e->getViewport());

        checkMouseEnterExit(TransformedMouseEvent, TransformedMouseEvent->getLocation(),TransformedMouseEvent->getViewport());

        for(Int32 i(getMFInternalWindows()->size()-1) ; i>=0 ; --i)
        {
            if(isContainedClipBounds(TransformedMouseEvent->getLocation(), getInternalWindows(i)))
            {
                getInternalWindows(i)->mouseDragged(TransformedMouseEvent);
                break;
            }
        }
    }
}

void UIDrawingSurface::mouseWheelMoved(const MouseWheelEventUnrecPtr e)
{
    Pnt2f ResultMouseLoc;
    if(getMouseTransformFunctor()->viewportToRenderingSurface(e->getLocation(),e->getViewport(), ResultMouseLoc))
    {
        const MouseWheelEventUnrecPtr TransformedMouseEvent = MouseWheelEvent::create(e->getSource(), e->getTimeStamp(), e->getWheelRotation(), e->getScrollType(),e->getScrollOrientation(),
                                                                                      ResultMouseLoc,e->getViewport());

        checkMouseEnterExit(TransformedMouseEvent, TransformedMouseEvent->getLocation(),TransformedMouseEvent->getViewport());

        for(Int32 i(getMFInternalWindows()->size()-1) ; i>=0 ; --i)
        {
            if(isContainedClipBounds(TransformedMouseEvent->getLocation(), getInternalWindows(i)))
            {
                getInternalWindows(i)->mouseWheelMoved(TransformedMouseEvent);
                break;
            }
        }
    }
}

void UIDrawingSurface::keyPressed(const KeyEventUnrecPtr e)
{
    if(getFocusedWindow() != NULL)
    {
        getFocusedWindow()->keyPressed(e);
    }
}

void UIDrawingSurface::keyReleased(const KeyEventUnrecPtr e)
{
    if(getFocusedWindow() != NULL)
    {
        getFocusedWindow()->keyReleased(e);
    }
}

void UIDrawingSurface::keyTyped(const KeyEventUnrecPtr e)
{
    if(getFocusedWindow() != NULL)
    {
        getFocusedWindow()->keyTyped(e);
    }
}

void UIDrawingSurface::checkMouseEnterExit(const InputEventUnrecPtr e, const Pnt2f& MouseLocation, ViewportRefPtr TheViewport)
{
    for(UInt32 i(0) ; i<getMFInternalWindows()->size() ; ++i)
    {
        if(getInternalWindows(i)->getMouseContained())
        {
            //Check if mouse is outside of the frame
            if(!isContainedClipBounds(MouseLocation, getInternalWindows(i)))
            {
                //Mouse has exited the frame
                getInternalWindows(i)->setMouseContained(false);
                const MouseEventUnrecPtr ExitedEvent = MouseEvent::create(e->getSource(), e->getTimeStamp(), MouseEvent::NO_BUTTON,0,MouseLocation,TheViewport);
                getInternalWindows(i)->mouseExited(ExitedEvent);
            }
        }
        else
        {
            //Check if mouse is inside of the frame
            if(isContainedClipBounds(MouseLocation, getInternalWindows(i)))
            {
                //Mouse has entered the frame
                getInternalWindows(i)->setMouseContained(true);
                const MouseEventUnrecPtr EnteredEvent = MouseEvent::create(e->getSource(), e->getTimeStamp(), MouseEvent::NO_BUTTON,0,MouseLocation, TheViewport);
                getInternalWindows(i)->mouseEntered(EnteredEvent);
            }
        }
    }
}

void UIDrawingSurface::detachFromEventProducer(void)
{

    if(getEventProducer() == NULL)
    {
        for(UInt32 i(0) ; i<getMFInternalWindows()->size() ; ++i)
        {
            getInternalWindows(i)->detachFromEventProducer();
        }
    }

    setEventProducer(NULL);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

UIDrawingSurface::UIDrawingSurface(void) :
    Inherited()
{
}

UIDrawingSurface::UIDrawingSurface(const UIDrawingSurface &source) :
    Inherited(source)
{
}

UIDrawingSurface::~UIDrawingSurface(void)
{
}

/*----------------------------- class specific ----------------------------*/

void UIDrawingSurface::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if( (whichField & EventProducerFieldMask) )
    {
        _MouseEventConnection.disconnect();
        _MouseMotionEventConnection.disconnect();
        _MouseWheelEventConnection.disconnect();
        _KeyEventConnection.disconnect();

        if(getEventProducer() != NULL)
        {
            _MouseEventConnection = getEventProducer()->addMouseListener(this);
            _MouseMotionEventConnection = getEventProducer()->addMouseMotionListener(this);
            _MouseWheelEventConnection = getEventProducer()->addMouseWheelListener(this);
            _KeyEventConnection = getEventProducer()->addKeyListener(this);
        }
    }

    if( (whichField & InternalWindowsFieldMask) )
    {
        for(UInt32 i(0) ; i<getMFInternalWindows()->size() ; ++i)
        {
            if(getInternalWindows(i)->getDrawingSurface() != this)
            {
                getInternalWindows(i)->setDrawingSurface(this);
            }
        }
    }

    if(whichField & SizeFieldMask)
    {
        Vec2f Size;
        Pnt2f Position;
        bool isSizeDifferent(false);
        bool isPositionDifferent(false);
        for(UInt32 i(0) ; i<getMFInternalWindows()->size() ; ++i)
        {

            isSizeDifferent = false;
            isPositionDifferent = false;

            if(getInternalWindows(i)->isScalableInDrawingSurface())
            {
                //Update Scaling
                Size.setValues(getInternalWindows(i)->getScalingInDrawingSurface().x() * static_cast<Real32>(getSize().x()),
                               getInternalWindows(i)->getScalingInDrawingSurface().y() * static_cast<Real32>(getSize().y()));
            }
            else
            {
                Size = getInternalWindows(i)->getPreferredSize();
            }

            Size.setValues(osgMax(osgMin(Size.x(), getInternalWindows(i)->getMaxSize().x()), getInternalWindows(i)->getMinSize().x()),
                           osgMax(osgMin(Size.y(), getInternalWindows(i)->getMaxSize().y()), getInternalWindows(i)->getMinSize().y()));

            isSizeDifferent = (getInternalWindows(i)->getSize().x() != Size.x() ||
                               getInternalWindows(i)->getSize().y() != Size.y());

            if(getInternalWindows(i)->isAlignableInDrawingSurface())
            {
                //Update Alignment
                Position = calculateAlignment(Pnt2f(0.0f,0.0f),
                                              getSize(),
                                              Size,
                                              getInternalWindows(i)->getAlignmentInDrawingSurface().y(),
                                              getInternalWindows(i)->getAlignmentInDrawingSurface().x());

                isPositionDifferent = (getInternalWindows(i)->getPosition().x() != Position.x() ||
                                       getInternalWindows(i)->getPosition().y() != Position.y());
            }


            if(isSizeDifferent)
            {
                getInternalWindows(i)->setSize(Size);
            }
            if(isPositionDifferent)
            {
                getInternalWindows(i)->setPosition(Position);
            }

            if(!isPositionDifferent && !isSizeDifferent)
            {
                getInternalWindows(i)->updateClipBounds();
            }
        }
    }
}

void UIDrawingSurface::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump UIDrawingSurface NI" << std::endl;
}

OSG_END_NAMESPACE
