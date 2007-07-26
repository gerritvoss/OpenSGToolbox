/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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
UInt32 DefaultBoundedRangeModel::getExtent(void) const
{
    return _Extent;
}

inline
UInt32 DefaultBoundedRangeModel::getMaximum(void) const
{
    return _Maximum;
}

inline
UInt32 DefaultBoundedRangeModel::getMinimum(void) const
{
    return _Minimum;
}

inline
UInt32 DefaultBoundedRangeModel::getValue(void) const
{
    return _Value;
}

inline
bool DefaultBoundedRangeModel::getValueIsAdjusting(void) const
{
    return _ValueIsAdjusting;
}

inline
void DefaultBoundedRangeModel::setExtent(UInt32 newExtent)
{
    _Extent= newExtent;
}

inline
void DefaultBoundedRangeModel::setMaximum(UInt32 newMaximum)
{
    _Maximum= newMaximum;
}

inline
void DefaultBoundedRangeModel::setMinimum(UInt32 newMinimum)
{
    _Minimum= newMinimum;
}

inline
void DefaultBoundedRangeModel::setRangeProperties(UInt32 value, UInt32 extent, UInt32 min, UInt32 max, bool adjusting)
{
    _Extent= extent;
    _Maximum= max;
    _Minimum= min;
    _Value= value;
    _ValueIsAdjusting = adjusting;
}

inline
void DefaultBoundedRangeModel::setValue(UInt32 newValue)
{
    _Value= newValue;
}

inline
void DefaultBoundedRangeModel::setValueIsAdjusting(bool b)
{
    _ValueIsAdjusting = b;
}

inline
void DefaultBoundedRangeModel::addChangeListener(ChangeListenerPtr Listener)
{
   _ChangeListeners.insert(Listener);
}

inline
void DefaultBoundedRangeModel::removeChangeListener(ChangeListenerPtr Listener)
{
   ChangeListenerSetItor EraseIter(_ChangeListeners.find(Listener));
   if(EraseIter != _ChangeListeners.end())
   {
      _ChangeListeners.erase(EraseIter);
   }
}

OSG_END_NAMESPACE


