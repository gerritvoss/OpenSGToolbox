/*---------------------------------------------------------------------------*\
 *                          OpenSG Toolbox Input                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala                                                   *
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
#include "OSGConfig.h"

OSG_BEGIN_NAMESPACE

inline
UInt32 InputSettings::getUnitsPerMouseScrollClick(void) const
{
   return _UnitsPerMouseScrollClick;
}

inline
void InputSettings::setUnitsPerMouseScrollClick(const UInt32 Ratio)
{
   _UnitsPerMouseScrollClick = Ratio;
}

inline
Real32 InputSettings::getMultipleClickRate(void) const
{
   return _MultipleClickRate;
}

inline
void InputSettings::setMultipleClickRate(const Real32 Rate)
{
   _MultipleClickRate = Rate;
}

inline
Real32 InputSettings::getMultipleClickMouseDriftAllowance(void) const
{
   return _MultipleClickMouseDriftAllowance;
}

inline
void InputSettings::setMultipleClickMouseDriftAllowance(const Real32 Allowance)
{
   _MultipleClickMouseDriftAllowance = Allowance;
}


inline
InputSettings::InputSettings(void) 
: _UnitsPerMouseScrollClick(1),
_MultipleClickRate(0.25),
_MultipleClickMouseDriftAllowance(2.0)
{
}

OSG_END_NAMESPACE
