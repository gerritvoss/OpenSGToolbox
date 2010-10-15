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
Component * ScrollPanel::getViewComponent  (void) const
{
    if(getView() == NULL)
    {
        return NULL;
    }
    else
    {
        return getView()->getViewComponent();
    }
}

inline
void ScrollPanel::scrollHorizontalUnit(Int32 Units)
{
    getHorizontalScrollBar()->scrollUnit(Units);
}

inline
void ScrollPanel::scrollHorizontalBlock(Int32 Blocks)
{
    getHorizontalScrollBar()->scrollBlock(Blocks);
}

inline
void ScrollPanel::scrollVerticalUnit(Int32 Units)
{
    getVerticalScrollBar()->scrollUnit(Units);
}

inline
void ScrollPanel::scrollVerticalBlock(Int32 Blocks)
{
    getVerticalScrollBar()->scrollBlock(Blocks);
}

OSG_END_NAMESPACE
