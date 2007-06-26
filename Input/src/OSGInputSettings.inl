#include "OSGInputConfig.h"

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
: _UnitsPerMouseScrollClick(5),
_MultipleClickRate(0.1),
_MultipleClickMouseDriftAllowance(2.0)
{
}

OSG_END_NAMESPACE
