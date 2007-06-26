#include "OSGInputSettings.h"


OSG_BEGIN_NAMESPACE

InputSettings *InputSettings::_the = NULL;

InputSettings* InputSettings::the(void)
{
   if(_the == NULL)
   {
      _the = new InputSettings();
   }
 
   return _the;
}

OSG_END_NAMESPACE
