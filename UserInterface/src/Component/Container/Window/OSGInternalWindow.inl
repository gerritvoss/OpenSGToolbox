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
InternalWindow::PopupMenuInteractionListener::PopupMenuInteractionListener(InternalWindowPtr TheInternalWindow) :
_InternalWindow(TheInternalWindow)
{
}

inline
InternalWindow::TitlebarDraggedListener::TitlebarDraggedListener(InternalWindowPtr TheInternalWindow) :
	_InternalWindow(TheInternalWindow)
{
}

inline
void InternalWindow::TitlebarDraggedListener::setWindowStartPosition(const Pnt2s& Pos)
{
	_WindowStartPosition = Pos;
}

inline
void InternalWindow::TitlebarDraggedListener::setMouseStartPosition(const Pnt2s& Pos)
{
	_MouseStartPosition = Pos;
}

inline
InternalWindow::BorderDraggedListener::BorderDraggedListener(InternalWindowPtr TheInternalWindow) :
	_InternalWindow(TheInternalWindow)
{
}

inline
void InternalWindow::BorderDraggedListener::setWindowStartPosition(const Pnt2s& Pos)
{
	_WindowStartPosition = Pos;
}

inline
void InternalWindow::BorderDraggedListener::setWindowStartSize(const Vec2s& Size)
{
	_WindowStartSize = Size;
}

inline
void InternalWindow::BorderDraggedListener::setMouseStartPosition(const Pnt2s& Pos)
{
	_MouseStartPosition = Pos;
}

inline
void InternalWindow::BorderDraggedListener::setBorderDragged(const WindowArea Value)
{
	_BorderDragged = Value;
}

inline
InternalWindow::TitlebarStartDragListener::TitlebarStartDragListener(InternalWindowPtr TheInternalWindow) :
	_InternalWindow(TheInternalWindow)
{
}
	
inline
InternalWindow::CloseButtonListener::CloseButtonListener(InternalWindowPtr TheInternalWindow) :
	_InternalWindow(TheInternalWindow)
{
}

inline
InternalWindow::MaximizeButtonListener::MaximizeButtonListener(InternalWindowPtr TheInternalWindow) :
	_InternalWindow(TheInternalWindow)
{
}

inline
InternalWindow::IconifyButtonListener::IconifyButtonListener(InternalWindowPtr TheInternalWindow) :
	_InternalWindow(TheInternalWindow)
{
}

OSG_END_NAMESPACE

#define OSGINTERNALWINDOW_INLINE_CVSID "@(#)$Id: FCTemplate_inl.h,v 1.8 2002/12/04 14:22:22 dirk Exp $"

