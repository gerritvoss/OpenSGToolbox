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
void List::setSelectedIndex(UInt32 index)
{
   getSelectionModel()->setSelectionInterval(index,index);
}

inline
Int32 List::getSelectedIndex(void) const
{
   return getSelectionModel()->getMinSelectionIndex();
}

inline
Int32 List::getMinSelectedIndex(void) const
{
   return getSelectionModel()->getMinSelectionIndex();
}

inline
Int32 List::getMaxSelectedIndex(void) const
{
   return getSelectionModel()->getMaxSelectionIndex();
}

inline
boost::any List::getSelectedItem(void) const
{
   return ( getSelectionModel()->isSelectionEmpty() ?
            boost::any() :
            getValueAtIndex(getSelectedIndex()) );
}

OSG_END_NAMESPACE
