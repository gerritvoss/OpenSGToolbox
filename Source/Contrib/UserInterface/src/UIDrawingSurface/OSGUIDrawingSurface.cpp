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

void UIDrawingSurface::openWindow(InternalWindow* const TheWindow, const Int32 Layer)
{
    MFInternalWindowsType::iterator WindowItor(_mfInternalWindows.find(TheWindow));

    if(WindowItor == _mfInternalWindows.end())
    {
        pushToInternalWindows(TheWindow);

        if(Layer < 0 || Layer > _mfInternalWindows.size())
        {
            moveWindowToTop(TheWindow);
        }
        else
        {
            setWindowToLayer(TheWindow, Layer);
        }

        if(_mfInternalWindows.back() == TheWindow)
        {
            _mfInternalWindows.back()->takeFocus();
        }

        TheWindow->open();
    }

}

void UIDrawingSurface::closeWindow(InternalWindow* const TheWindow)
{
    if(_IsProcessingEvents)
    {
        _WindowsToClose.insert(TheWindow);
        return;
    }

    removeObjFromInternalWindows(TheWindow);

    if(_mfInternalWindows.size() > 0)
    {
        _mfInternalWindows.back()->takeFocus();
    }
    else
    {
        setFocusedWindow(NULL);
    }
}

UInt32 UIDrawingSurface::getNumWindowLayers(void) const
{
    return _mfInternalWindows.size();
}

InternalWindow* UIDrawingSurface::getWindowAtLayer(const UInt32& Layer) const
{
    if(Layer < _mfInternalWindows.size())
    {
        return getInternalWindows(Layer);
    }
    else
    {
        return NULL;
    }
}

Int32 UIDrawingSurface::getWindowLayer(InternalWindow* const TheWindow) const
{
    UInt32 i(0);
    while(i<_mfInternalWindows.size() &&
          getInternalWindows(i) != TheWindow)
    {
        ++i;
    }

    if(i < _mfInternalWindows.size() )
    {
        return i;
    }
    else
    {
        return -1;
    }
}

void UIDrawingSurface::setWindowToLayer(InternalWindow* const TheWindow, const UInt32& Layer)
{
    MFInternalWindowsType::iterator RemovalItor(_mfInternalWindows.begin());
    while(RemovalItor != _mfInternalWindows.end() &&
          (*RemovalItor) != TheWindow)
    {
        ++RemovalItor;
    }

    if(RemovalItor != _mfInternalWindows.end() &&
       Layer < _mfInternalWindows.size())
    {
        InternalWindowRefPtr SwapWindow(*RemovalItor);
        _mfInternalWindows.erase(RemovalItor);

        MFInternalWindowsType::iterator InsertItor(_mfInternalWindows.begin());
        for(UInt32 i(0) ; i<Layer ; ++i){++InsertItor;}

        _mfInternalWindows.insert(InsertItor, SwapWindow);

        if(getFocusedWindow() != NULL)
        {
            _mfInternalWindows.back()->takeFocus();
        }
    }
}

void UIDrawingSurface::moveWindowUp(InternalWindow* const TheWindow)
{
    Int32 WindowLayer(getWindowLayer(TheWindow));
    if(WindowLayer < _mfInternalWindows.size() &&
        TheWindow->getAllwaysOnTop() == getInternalWindows(WindowLayer)->getAllwaysOnTop())
    {
        setWindowToLayer(TheWindow,  WindowLayer+1);
    }
}

void UIDrawingSurface::moveWindowDown(InternalWindow* const TheWindow)
{
    Int32 WindowLayer(getWindowLayer(TheWindow));
    if(WindowLayer > 0 && 
       (!TheWindow->getModal() ||
        TheWindow->getAllwaysOnTop() == getInternalWindows(WindowLayer)->getAllwaysOnTop()))
    {
        setWindowToLayer(TheWindow,  WindowLayer-1);
    }
}

void UIDrawingSurface::moveWindowToTop(InternalWindow* const TheWindow)
{
    MFInternalWindowsType::iterator RemovalItor(_mfInternalWindows.begin());
    while(RemovalItor != _mfInternalWindows.end() &&
          (*RemovalItor) != TheWindow)
    {
        ++RemovalItor;
    }

    if(RemovalItor != _mfInternalWindows.end())
    {
        InternalWindowRefPtr SwapWindow(*RemovalItor);
        _mfInternalWindows.erase(RemovalItor);

        MFInternalWindowsType::iterator InsertItor(_mfInternalWindows.begin());
        while(InsertItor != _mfInternalWindows.end() &&
              !(*TheWindow < *(*InsertItor)))
        {
            ++InsertItor;
        }

        MFInternalWindowsType::iterator NewPosition = _mfInternalWindows.insert(InsertItor,SwapWindow);

        if(getFocusedWindow() != NULL)
        {
            _mfInternalWindows.back()->takeFocus();
        }
    }
}

void UIDrawingSurface::moveWindowToBottom(InternalWindow* const TheWindow)
{
    MFInternalWindowsType::iterator RemovalItor(_mfInternalWindows.begin());
    while(RemovalItor != _mfInternalWindows.end() &&
          (*RemovalItor) != TheWindow)
    {
        ++RemovalItor;
    }

    if(RemovalItor != _mfInternalWindows.end())
    {
        InternalWindowRefPtr SwapWindow(*RemovalItor);
        _mfInternalWindows.erase(RemovalItor);

        _mfInternalWindows.insert(_mfInternalWindows.begin(), SwapWindow);

        if(getFocusedWindow() != NULL)
        {
            _mfInternalWindows.back()->takeFocus();
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

void UIDrawingSurface::handleMouseClicked(MouseEventDetails* const e)
{
    _IsProcessingEvents = true;

    Pnt2f ResultMouseLoc;
    if(getMouseTransformFunctor()->viewportToRenderingSurface(e->getLocation(),e->getViewport(), ResultMouseLoc))
    {
        MouseEventDetailsUnrecPtr TransformedMouseEvent = MouseEventDetails::create(e->getSource(), e->getTimeStamp(), e->getButton(), e->getClickCount(),
                                                                            ResultMouseLoc,e->getViewport());

        checkMouseEnterExit(TransformedMouseEvent, TransformedMouseEvent->getLocation(),TransformedMouseEvent->getViewport());

        for(Int32 i(_mfInternalWindows.size()-1) ; i>=0 ; --i)
        {
            //If the event is consumed then stop sending the event
            if(TransformedMouseEvent->isConsumed())
            {
                e->consume();
                break;
            }

            if(isContainedClipBounds(TransformedMouseEvent->getLocation(), getInternalWindows(i)) &&
               (getInternalWindows(i) == _mfInternalWindows.back() ||
                !_mfInternalWindows.back()->getModal()))
            {
                getInternalWindows(i)->mouseClicked(TransformedMouseEvent);
                break;
            }
        }
    }

    _IsProcessingEvents = false;
    closeWindows();
}

void UIDrawingSurface::handleMouseEntered(MouseEventDetails* const e)
{
    _IsProcessingEvents = true;

    Pnt2f ResultMouseLoc;
    if(getMouseTransformFunctor()->viewportToRenderingSurface(e->getLocation(),e->getViewport(), ResultMouseLoc))
    {
        MouseEventDetailsUnrecPtr TransformedMouseEvent = MouseEventDetails::create(e->getSource(), e->getTimeStamp(), e->getButton(), e->getClickCount(),
                                                                            ResultMouseLoc,e->getViewport());

        checkMouseEnterExit(TransformedMouseEvent, TransformedMouseEvent->getLocation(),TransformedMouseEvent->getViewport());
    }

    _IsProcessingEvents = false;
    closeWindows();
}

void UIDrawingSurface::handleMouseExited(MouseEventDetails* const e)
{
    _IsProcessingEvents = true;

    Pnt2f ResultMouseLoc;
    if(getMouseTransformFunctor()->viewportToRenderingSurface(e->getLocation(),e->getViewport(), ResultMouseLoc))
    {
        MouseEventDetailsUnrecPtr TransformedMouseEvent = MouseEventDetails::create(e->getSource(), e->getTimeStamp(), e->getButton(), e->getClickCount(),
                                                                            ResultMouseLoc,e->getViewport());

        checkMouseEnterExit(TransformedMouseEvent, TransformedMouseEvent->getLocation(),TransformedMouseEvent->getViewport());
    }

    _IsProcessingEvents = false;
    closeWindows();
}

void UIDrawingSurface::handleMousePressed(MouseEventDetails* const e)
{
    _IsProcessingEvents = true;

    Pnt2f ResultMouseLoc;
    if(getMouseTransformFunctor()->viewportToRenderingSurface(e->getLocation(),e->getViewport(), ResultMouseLoc))
    {
        MouseEventDetailsUnrecPtr TransformedMouseEvent = MouseEventDetails::create(e->getSource(), e->getTimeStamp(), e->getButton(), e->getClickCount(),
                                                                            ResultMouseLoc,e->getViewport());

        checkMouseEnterExit(TransformedMouseEvent, TransformedMouseEvent->getLocation(),TransformedMouseEvent->getViewport());

        InternalWindow* MoveToTopWindow(NULL);
        for(Int32 i(_mfInternalWindows.size()-1) ; i>=0 ; --i)
        {
            //If the event is consumed then stop sending the event
            if(TransformedMouseEvent->isConsumed())
            {
                e->consume();
                break;
            }

            if(isContainedClipBounds(TransformedMouseEvent->getLocation(), getInternalWindows(i)))
            {
                if(getInternalWindows(i) != getFocusedWindow() &&
                   MoveToTopWindow != NULL)
                {
                    MoveToTopWindow = getInternalWindows(i);
                }

                if(getInternalWindows(i) == _mfInternalWindows.back() ||
                   !_mfInternalWindows.back()->getModal())
                {
                    getInternalWindows(i)->mousePressed(TransformedMouseEvent);
                    break;
                }
            }
        }
        if(MoveToTopWindow != NULL)
        {
            moveWindowToTop(MoveToTopWindow);
            MoveToTopWindow->takeFocus();
        }
    }

    _IsProcessingEvents = false;
    closeWindows();
}

void UIDrawingSurface::handleMouseReleased(MouseEventDetails* const e)
{
    _IsProcessingEvents = true;

    Pnt2f ResultMouseLoc;
    if(getMouseTransformFunctor()->viewportToRenderingSurface(e->getLocation(),e->getViewport(), ResultMouseLoc))
    {
        MouseEventDetailsUnrecPtr TransformedMouseEvent = MouseEventDetails::create(e->getSource(), e->getTimeStamp(), e->getButton(), e->getClickCount(),
                                                                            ResultMouseLoc,e->getViewport());

        checkMouseEnterExit(TransformedMouseEvent, TransformedMouseEvent->getLocation(),TransformedMouseEvent->getViewport());

        for(Int32 i(_mfInternalWindows.size()-1) ; i>=0 ; --i)
        {
            //If the event is consumed then stop sending the event
            if(TransformedMouseEvent->isConsumed())
            {
                e->consume();
                break;
            }

            if(isContainedClipBounds(TransformedMouseEvent->getLocation(), getInternalWindows(i)) &&
               (getInternalWindows(i) == _mfInternalWindows.back() ||
                !_mfInternalWindows.back()->getModal()))
            {
                getInternalWindows(i)->mouseReleased(TransformedMouseEvent);
                break;
            }
        }
    }

    _IsProcessingEvents = false;
    closeWindows();
}


void UIDrawingSurface::handleMouseMoved(MouseEventDetails* const e)
{
    _IsProcessingEvents = true;

    Pnt2f ResultMouseLoc;
    if(getMouseTransformFunctor()->viewportToRenderingSurface(e->getLocation(),e->getViewport(), ResultMouseLoc))
    {
        MouseEventDetailsUnrecPtr TransformedMouseEvent = MouseEventDetails::create(e->getSource(), e->getTimeStamp(), e->getButton(), e->getClickCount(),
                                                                            ResultMouseLoc,e->getViewport());

        checkMouseEnterExit(TransformedMouseEvent, TransformedMouseEvent->getLocation(),TransformedMouseEvent->getViewport());

        for(Int32 i(_mfInternalWindows.size()-1) ; i>=0 ; --i)
        {
            //If the event is consumed then stop sending the event
            if(TransformedMouseEvent->isConsumed())
            {
                e->consume();
                break;
            }

            if(isContainedClipBounds(TransformedMouseEvent->getLocation(), getInternalWindows(i)) &&
               (getInternalWindows(i) == _mfInternalWindows.back() ||
                !_mfInternalWindows.back()->getModal()))
            {
                getInternalWindows(i)->mouseMoved(TransformedMouseEvent);
                break;
            }
        }
    }

    _IsProcessingEvents = false;
    closeWindows();
}

void UIDrawingSurface::handleMouseDragged(MouseEventDetails* const e)
{
    _IsProcessingEvents = true;

    Pnt2f ResultMouseLoc;
    if(getMouseTransformFunctor()->viewportToRenderingSurface(e->getLocation(),e->getViewport(), ResultMouseLoc))
    {
        MouseEventDetailsUnrecPtr TransformedMouseEvent = MouseEventDetails::create(e->getSource(), e->getTimeStamp(), e->getButton(), e->getClickCount(),
                                                                            ResultMouseLoc,e->getViewport());

        checkMouseEnterExit(TransformedMouseEvent, TransformedMouseEvent->getLocation(),TransformedMouseEvent->getViewport());

        for(Int32 i(_mfInternalWindows.size()-1) ; i>=0 ; --i)
        {
            //If the event is consumed then stop sending the event
            if(TransformedMouseEvent->isConsumed())
            {
                e->consume();
                break;
            }

            if(isContainedClipBounds(TransformedMouseEvent->getLocation(), getInternalWindows(i)) &&
               (getInternalWindows(i) == _mfInternalWindows.back() ||
                !_mfInternalWindows.back()->getModal()))
            {
                getInternalWindows(i)->mouseDragged(TransformedMouseEvent);
                break;
            }
        }
    }

    _IsProcessingEvents = false;
    closeWindows();
}

void UIDrawingSurface::handleMouseWheelMoved(MouseWheelEventDetails* const e)
{
    _IsProcessingEvents = true;

    Pnt2f ResultMouseLoc;
    if(getMouseTransformFunctor()->viewportToRenderingSurface(e->getLocation(),e->getViewport(), ResultMouseLoc))
    {
        MouseWheelEventDetailsUnrecPtr TransformedMouseEvent = MouseWheelEventDetails::create(e->getSource(), e->getTimeStamp(), e->getWheelRotation(), e->getScrollType(),e->getScrollOrientation(),
                                                                                      ResultMouseLoc,e->getViewport());

        checkMouseEnterExit(TransformedMouseEvent, TransformedMouseEvent->getLocation(),TransformedMouseEvent->getViewport());

        for(Int32 i(_mfInternalWindows.size()-1) ; i>=0 ; --i)
        {
            //If the event is consumed then stop sending the event
            if(TransformedMouseEvent->isConsumed())
            {
                e->consume();
                break;
            }

            if(isContainedClipBounds(TransformedMouseEvent->getLocation(), getInternalWindows(i)) &&
               (getInternalWindows(i) == _mfInternalWindows.back() ||
                !_mfInternalWindows.back()->getModal()))
            {
                getInternalWindows(i)->mouseWheelMoved(TransformedMouseEvent);
                break;
            }
        }
    }

    _IsProcessingEvents = false;
    closeWindows();
}

void UIDrawingSurface::handleKeyPressed(KeyEventDetails* const e)
{
    _IsProcessingEvents = true;

    if(getFocusedWindow() != NULL)
    {
        getFocusedWindow()->keyPressed(e);
    }

    _IsProcessingEvents = false;
    closeWindows();
}

void UIDrawingSurface::handleKeyReleased(KeyEventDetails* const e)
{
    _IsProcessingEvents = true;

    if(getFocusedWindow() != NULL)
    {
        getFocusedWindow()->keyReleased(e);
    }

    _IsProcessingEvents = false;
    closeWindows();
}

void UIDrawingSurface::handleKeyTyped(KeyEventDetails* const e)
{
    _IsProcessingEvents = true;

    if(getFocusedWindow() != NULL)
    {
        getFocusedWindow()->keyTyped(e);
    }

    _IsProcessingEvents = false;
    closeWindows();
}

void UIDrawingSurface::checkMouseEnterExit(InputEventDetails* const e, const Pnt2f& MouseLocation, Viewport* const TheViewport)
{
    for(UInt32 i(0) ; i<_mfInternalWindows.size() ; ++i)
    {
        if(getInternalWindows(i)->getMouseContained())
        {
            //Check if mouse is outside of the frame
            if(!isContainedClipBounds(MouseLocation, getInternalWindows(i)))
            {
                //Mouse has exited the frame
                getInternalWindows(i)->setMouseContained(false);
                MouseEventDetailsUnrecPtr ExitedEvent = MouseEventDetails::create(e->getSource(), e->getTimeStamp(), MouseEventDetails::NO_BUTTON,0,MouseLocation,TheViewport);
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
                MouseEventDetailsUnrecPtr EnteredEvent = MouseEventDetails::create(e->getSource(), e->getTimeStamp(), MouseEventDetails::NO_BUTTON,0,MouseLocation, TheViewport);
                getInternalWindows(i)->mouseEntered(EnteredEvent);
            }
        }
    }
}

void UIDrawingSurface::detachFromEventProducer(void)
{

    if(getEventProducer() == NULL)
    {
        for(UInt32 i(0) ; i<_mfInternalWindows.size() ; ++i)
        {
            getInternalWindows(i)->detachFromEventProducer();
        }
    }
    else
    {
        setEventProducer(NULL);
    }
}
    
void UIDrawingSurface::closeWindows(void)
{
    if(!_IsProcessingEvents)
    {
        for(std::set<InternalWindow*>::iterator Itor(_WindowsToClose.begin()) ;
            Itor != _WindowsToClose.end();
            ++Itor)
        {
            closeWindow(*Itor);
        }
         _WindowsToClose.clear();
    }
}

void UIDrawingSurface::updateWindowLayout(InternalWindow* const TheWindow)
{
    Vec2f Size;
    Pnt2f Position;
    bool isSizeDifferent(false);
    bool isPositionDifferent(false);

    isSizeDifferent = false;
    isPositionDifferent = false;

    if(TheWindow->isScalableInDrawingSurface())
    {
        //Update Scaling
        Size.setValues(TheWindow->getScalingInDrawingSurface().x() * static_cast<Real32>(getSize().x()),
                       TheWindow->getScalingInDrawingSurface().y() * static_cast<Real32>(getSize().y()));
    }
    else
    {
        Size = TheWindow->getPreferredSize();
    }

    Size.setValues(osgMax(osgMin(Size.x(), TheWindow->getMaxSize().x()), TheWindow->getMinSize().x()),
                   osgMax(osgMin(Size.y(), TheWindow->getMaxSize().y()), TheWindow->getMinSize().y()));

    isSizeDifferent = (TheWindow->getSize().x() != Size.x() ||
                       TheWindow->getSize().y() != Size.y());

    if(TheWindow->isAlignableInDrawingSurface())
    {
        //Update Alignment
        Position = calculateAlignment(Pnt2f(0.0f,0.0f),
                                      getSize(),
                                      Size,
                                      TheWindow->getAlignmentInDrawingSurface().y(),
                                      TheWindow->getAlignmentInDrawingSurface().x());

        isPositionDifferent = (TheWindow->getPosition().x() != Position.x() ||
                               TheWindow->getPosition().y() != Position.y());
    }


    if(isSizeDifferent)
    {
        TheWindow->setSize(Size);
    }
    if(isPositionDifferent)
    {
        TheWindow->setPosition(Position);
    }

    if(!isPositionDifferent && !isSizeDifferent)
    {
        TheWindow->updateClipBounds();
    }
}

void UIDrawingSurface::updateWindowLayouts(void)
{
    for(UInt32 i(0) ; i<_mfInternalWindows.size() ; ++i)
    {
        updateWindowLayout(_mfInternalWindows[i]);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

UIDrawingSurface::UIDrawingSurface(void) :
    Inherited(),
    _IsProcessingEvents(false)
{
}

UIDrawingSurface::UIDrawingSurface(const UIDrawingSurface &source) :
    Inherited(source),
    _IsProcessingEvents(false)
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

    if( (whichField & EventProducerFieldMask) &&
        getEventProducer() == NULL)
    {
        detachFromEventProducer();
    }

    if( (whichField & EventProducerFieldMask) ||
        (whichField & ActiveFieldMask) ||
        (whichField & MouseTransformFunctorFieldMask))
    {
        _MouseClickedConnection.disconnect();
        _MouseEnteredConnection.disconnect();
        _MouseExitedConnection.disconnect();
        _MousePressedConnection.disconnect();
        _MouseReleasedConnection.disconnect();

        _MouseMovedConnection.disconnect();
        _MouseDraggedConnection.disconnect();

        _MouseWheelMovedConnection.disconnect();

        _KeyPressedConnection.disconnect();
        _KeyReleasedConnection.disconnect();
        _KeyTypedConnection.disconnect();

        if(getEventProducer() != NULL &&
           getActive() &&
           getMouseTransformFunctor() != NULL)
        {           
            _MouseClickedConnection = getEventProducer()->connectMouseClicked(boost::bind(&UIDrawingSurface::handleMouseClicked, this, _1));
            _MouseEnteredConnection = getEventProducer()->connectMouseEntered(boost::bind(&UIDrawingSurface::handleMouseEntered, this, _1));
            _MouseExitedConnection = getEventProducer()->connectMouseExited(boost::bind(&UIDrawingSurface::handleMouseExited, this, _1));
            _MousePressedConnection = getEventProducer()->connectMousePressed(boost::bind(&UIDrawingSurface::handleMousePressed, this, _1));
            _MouseReleasedConnection = getEventProducer()->connectMouseReleased(boost::bind(&UIDrawingSurface::handleMouseReleased, this, _1));

            _MouseMovedConnection = getEventProducer()->connectMouseMoved(boost::bind(&UIDrawingSurface::handleMouseMoved, this, _1));
            _MouseDraggedConnection = getEventProducer()->connectMouseDragged(boost::bind(&UIDrawingSurface::handleMouseDragged, this, _1));

            _MouseWheelMovedConnection = getEventProducer()->connectMouseWheelMoved(boost::bind(&UIDrawingSurface::handleMouseWheelMoved, this, _1));

            _KeyPressedConnection = getEventProducer()->connectKeyPressed(boost::bind(&UIDrawingSurface::handleKeyPressed, this, _1));
            _KeyReleasedConnection = getEventProducer()->connectKeyReleased(boost::bind(&UIDrawingSurface::handleKeyReleased, this, _1));
            _KeyTypedConnection = getEventProducer()->connectKeyTyped(boost::bind(&UIDrawingSurface::handleKeyTyped, this, _1));
        }
    }

    if(whichField & SizeFieldMask)
    {
        updateWindowLayouts();
    }
}

void UIDrawingSurface::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump UIDrawingSurface NI" << std::endl;
}

OSG_END_NAMESPACE
