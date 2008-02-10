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
void Component::getClipBounds(Pnt2f& TopLeft, Pnt2f& BottomRight) const
{
	TopLeft = getClipTopLeft();
	BottomRight = getClipBottomRight();
}

inline
void Component::addKeyListener(KeyListenerPtr Listener)
{
   _KeyListeners.insert(Listener);
}

inline
void Component::removeKeyListener(KeyListenerPtr Listener)
{
   KeyListenerSetItor EraseIter(_KeyListeners.find(Listener));
   if(EraseIter != _KeyListeners.end())
   {
      _KeyListeners.erase(EraseIter);
   }
}

inline
void Component::addMouseListener(MouseListenerPtr Listener)
{
   _MouseListeners.insert(Listener);
}

inline
void Component::removeMouseListener(MouseListenerPtr Listener)
{
   MouseListenerSetItor EraseIter(_MouseListeners.find(Listener));
   if(EraseIter != _MouseListeners.end())
   {
      _MouseListeners.erase(EraseIter);
   }
}

inline
void Component::addMouseWheelListener(MouseWheelListenerPtr Listener)
{
   _MouseWheelListeners.insert(Listener);
}

inline
void Component::removeMouseWheelListener(MouseWheelListenerPtr Listener)
{
   MouseWheelListenerSetItor EraseIter(_MouseWheelListeners.find(Listener));
   if(EraseIter != _MouseWheelListeners.end())
   {
      _MouseWheelListeners.erase(EraseIter);
   }
}

inline
void Component::addMouseMotionListener(MouseMotionListenerPtr Listener)
{
   _MouseMotionListeners.insert(Listener);
}

inline
void Component::removeMouseMotionListener(MouseMotionListenerPtr Listener)
{
   MouseMotionListenerSetItor EraseIter(_MouseMotionListeners.find(Listener));
   if(EraseIter != _MouseMotionListeners.end())
   {
      _MouseMotionListeners.erase(EraseIter);
   }
}

inline
void Component::addFocusListener(FocusListenerPtr Listener)
{
   _FocusListeners.insert(Listener);
}

inline
void Component::removeFocusListener(FocusListenerPtr Listener)
{
   FocusListenerSetItor EraseIter(_FocusListeners.find(Listener));
   if(EraseIter != _FocusListeners.end())
   {
      _FocusListeners.erase(EraseIter);
   }
}

inline
void Component::addComponentListener(ComponentListener* Listener)
{
   _ComponentListeners.insert(Listener);
}

inline
void Component::removeComponentListener(ComponentListener* Listener)
{
   ComponentListenerSetItor EraseIter(_ComponentListeners.find(Listener));
   if(EraseIter != _ComponentListeners.end())
   {
      _ComponentListeners.erase(EraseIter);
   }
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

