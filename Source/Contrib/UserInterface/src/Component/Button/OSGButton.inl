/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

OSG_BEGIN_NAMESPACE

inline
bool Button::isActionListenerAttached(ActionListenerPtr Listener) const
{
    return _ActionListeners.find(Listener) != _ActionListeners.end();
}

inline
bool Button::isMousePressedActionListenerAttached(ActionListenerPtr Listener) const
{
    return _MousePressedActionListeners.find(Listener) != _MousePressedActionListeners.end();
}

inline
bool Button::getActive(void) const
{
    return _Active;
}

inline
void Button::setActive(bool Value)
{
    _Active = Value;
}

inline
Button::ButtonArmedListener::ButtonArmedListener(ButtonRefPtr TheButton) :
_Button(TheButton)
{
}

inline
void Button::removeMousePressedActionListener(ActionListenerPtr Listener)
{
   ActionListenerSetItor EraseIter(_MousePressedActionListeners.find(Listener));
   if(EraseIter != _MousePressedActionListeners.end())
   {
      _MousePressedActionListeners.erase(EraseIter);
   }
}


inline
void Button::ButtonArmedListener::reset(void)
{
    _ActionFireElps = 0.0;
}

OSG_END_NAMESPACE
