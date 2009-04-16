/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
bool Component::isMouseListenerAttached(MouseListenerPtr Listener) const
{
    return _MouseListeners.find(Listener) != _MouseListeners.end();
}

inline
bool Component::isMouseMotionListenerAttached(MouseMotionListenerPtr Listener) const
{
    return _MouseMotionListeners.find(Listener) != _MouseMotionListeners.end();
}

inline
bool Component::isMouseWheelListenerAttached(MouseWheelListenerPtr Listener) const
{
    return _MouseWheelListeners.find(Listener) != _MouseWheelListeners.end();
}

inline
bool Component::isKeyListenerAttached(KeyListenerPtr Listener) const
{
    return _KeyListeners.find(Listener) != _KeyListeners.end();
}

inline
bool Component::isFocusListenerAttached(FocusListenerPtr Listener) const
{
    return _FocusListeners.find(Listener) != _FocusListeners.end();
}

inline
bool Component::isComponentListenerAttached(ComponentListenerPtr Listener) const
{
    return _ComponentListeners.find(Listener) != _ComponentListeners.end();
}

inline
void Component::getClipBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const
{
	TopLeft = getClipTopLeft();
	BottomRight = getClipBottomRight();
}


inline
void Component::setMouseContained(bool Value)
{
	_MouseInComponentLastMouse = Value;
}

inline
bool Component::getMouseContained(void)
{
	return _MouseInComponentLastMouse;
}

inline
Component::ComponentUpdater::ComponentUpdater(ComponentPtr TheComponent) :
    _Component(TheComponent)
{
}

inline
Component::ActivateToolTipListener::ActivateToolTipListener(ComponentPtr TheComponent) :
    _Component(TheComponent)
{
}

inline
Component::DeactivateToolTipListener::DeactivateToolTipListener(ComponentPtr TheComponent) :
    _Component(TheComponent)
{
}

OSG_END_NAMESPACE

#define OSGCOMPONENT_INLINE_CVSID "@(#)$Id: FCTemplate_inl.h,v 1.8 2002/12/04 14:22:22 dirk Exp $"

