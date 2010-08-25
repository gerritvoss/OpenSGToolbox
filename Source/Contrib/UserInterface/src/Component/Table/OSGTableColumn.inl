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
TableCellRendererPtr TableColumn::getCellRenderer(void) const
{
    return _TableCellRenderer;
}

inline
TableCellRendererPtr TableColumn::getHeaderRenderer(void) const
{
    return _HeaderCellRenderer;
}

inline
boost::any TableColumn::getHeaderValue(void) const
{
    return _HeaderValue;
}

inline
void TableColumn::setCellRenderer(TableCellRendererPtr cellRenderer)
{
    _TableCellRenderer = cellRenderer;
}

inline
void TableColumn::setHeaderRenderer(TableCellRendererPtr headerRenderer)
{
    _HeaderCellRenderer = headerRenderer;
}

inline
void TableColumn::setHeaderValue(const boost::any& headerValue)
{
    _HeaderValue = headerValue;
}

OSG_END_NAMESPACE
