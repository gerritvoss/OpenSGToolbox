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
bool InternalWindow::isKeyAcceleratorAttached(KeyEvent::Key TheKey, UInt32 Modifiers) const
{
    return _KeyAcceleratorMap.find(KeyEvent::getHashable(TheKey, Modifiers)) != _KeyAcceleratorMap.end();
}

inline
InternalWindow::PopupMenuInteractionListener::PopupMenuInteractionListener(InternalWindowRefPtr TheInternalWindow) :
_InternalWindow(TheInternalWindow)
{
}

inline
InternalWindow::TitlebarDraggedListener::TitlebarDraggedListener(InternalWindowRefPtr TheInternalWindow) :
	_InternalWindow(TheInternalWindow)
{
}

inline
void InternalWindow::TitlebarDraggedListener::setWindowStartPosition(const Pnt2f& Pos)
{
	_WindowStartPosition = Pos;
}

inline
void InternalWindow::TitlebarDraggedListener::setMouseStartPosition(const Pnt2f& Pos)
{
	_MouseStartPosition = Pos;
}

inline
InternalWindow::BorderDraggedListener::BorderDraggedListener(InternalWindowRefPtr TheInternalWindow) :
	_InternalWindow(TheInternalWindow)
{
}

inline
void InternalWindow::BorderDraggedListener::setWindowStartPosition(const Pnt2f& Pos)
{
	_WindowStartPosition = Pos;
}

inline
void InternalWindow::BorderDraggedListener::setWindowStartSize(const Vec2f& Size)
{
	_WindowStartSize = Size;
}

inline
void InternalWindow::BorderDraggedListener::setMouseStartPosition(const Pnt2f& Pos)
{
	_MouseStartPosition = Pos;
}

inline
void InternalWindow::BorderDraggedListener::setBorderDragged(const WindowArea Value)
{
	_BorderDragged = Value;
}

inline
InternalWindow::TitlebarStartDragListener::TitlebarStartDragListener(InternalWindowRefPtr TheInternalWindow) :
	_InternalWindow(TheInternalWindow)
{
}
	
inline
InternalWindow::CloseButtonListener::CloseButtonListener(InternalWindowRefPtr TheInternalWindow) :
	_InternalWindow(TheInternalWindow)
{
}

inline
InternalWindow::MaximizeButtonListener::MaximizeButtonListener(InternalWindowRefPtr TheInternalWindow) :
	_InternalWindow(TheInternalWindow)
{
}

inline
InternalWindow::IconifyButtonListener::IconifyButtonListener(InternalWindowRefPtr TheInternalWindow) :
	_InternalWindow(TheInternalWindow)
{
}

OSG_END_NAMESPACE
