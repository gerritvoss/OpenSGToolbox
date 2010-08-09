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
TableCellRendererPtr TableHeader::getDefaultRenderer(void) const
{
    return _DefaultTableHeaderRenderer;
}

inline
TableColumn* TableHeader::getDraggedColumn(void) const
{
    return _DraggedColumn;
}

inline
Real32 TableHeader::getDraggedDistance(void) const
{
    return _DraggedDistance;
}

inline
void TableHeader::getHeaderBounds(const UInt32 ColumnIndex, Pnt2f& TopLeft, Pnt2f& BottomRight) const
{
    getColumnHeaders(ColumnIndex)->getBounds(TopLeft, BottomRight);
}

inline
Int32 TableHeader::getResizingColumn(void) const
{
    return _ResizingColumn;
}

inline
void TableHeader::setDefaultRenderer(TableCellRendererPtr defaultRenderer)
{
    _DefaultTableHeaderRenderer = defaultRenderer;
}

inline
void TableHeader::setDraggedColumn(TableColumn* const aColumn)
{
    _DraggedColumn = aColumn;
}

inline
void TableHeader::setDraggedDistance(const Real32& distance)
{
    _DraggedDistance = distance;
}

inline
void TableHeader::setResizingColumn(Int32 aColumn)
{
    _ResizingColumn = aColumn;
}

OSG_END_NAMESPACE
