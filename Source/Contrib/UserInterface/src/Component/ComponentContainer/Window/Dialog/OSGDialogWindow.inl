/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com), Mark Stenerson             *
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
bool DialogWindow::isDialogWindowListenerAttached(DialogWindowListenerPtr Listener) const
{
    return _DialogWindowListeners.find(Listener) != _DialogWindowListeners.end();
}

inline
bool DialogWindow::isEventListenerAttached(EventListenerPtr Listener) const
{
    return _EventListeners.find(Listener) != _EventListeners.end();
}

inline
ActionListener* DialogWindow::getConfirmButtonListener(void)
{
    return &_ConfirmButtonListener;
}

inline
ActionListener* DialogWindow::getCancelButtonListener(void)
{
    return &_CancelButtonListener;
}

inline
ActionListener* DialogWindow::getInputButtonListener(void)
{
    return &_InputButtonListener;
}

inline
ActionListener* DialogWindow::getComboButtonListener(void)
{
    return &_ComboButtonListener;
}

inline
ActionListener* DialogWindow::getTextButtonListener(void)
{
    return &_TextButtonListener;
}

OSG_END_NAMESPACE
