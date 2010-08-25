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
void ScrollBar::setValue(Int32 newValue)
{
    getRangeModel()->setValue(newValue);
}

inline
bool ScrollBar::getValueIsAdjusting(void) const
{
    return getRangeModel()->getValueIsAdjusting();
}

inline
void ScrollBar::setValueIsAdjusting(bool Value)
{
    getRangeModel()->setValueIsAdjusting(Value);
}

inline
UInt32 ScrollBar::getExtent(void) const
{
    return getRangeModel()->getExtent();
}

inline
Int32 ScrollBar::getMaximum(void) const
{
    return getRangeModel()->getMaximum();
}

inline
Int32 ScrollBar::getMinimum(void) const
{
    return getRangeModel()->getMinimum();
}

inline
Int32 ScrollBar::getValue(void) const
{
    return getRangeModel()->getValue();
}

inline
void ScrollBar::setExtent(UInt32 newExtent)
{
    getRangeModel()->setExtent(newExtent);
}

inline
void ScrollBar::setMaximum(Int32 newMaximum)
{
    getRangeModel()->setMaximum(newMaximum);
}

inline
void ScrollBar::setMinimum(Int32 newMinimum)
{
    getRangeModel()->setMinimum(newMinimum);
}

inline
void ScrollBar::setRangeProperties(Int32 value, UInt32 extent, Int32 min, Int32 max, bool adjusting)
{
    getRangeModel()->setRangeProperties(value, extent, min, max, adjusting);
}

OSG_END_NAMESPACE
