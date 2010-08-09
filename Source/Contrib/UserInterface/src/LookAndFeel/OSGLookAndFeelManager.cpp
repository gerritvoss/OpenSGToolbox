#include "OSGLookAndFeelManager.h"
#include "OSGBaseInitFunctions.h"

OSG_BEGIN_NAMESPACE

LookAndFeelManager* LookAndFeelManager::_the = NULL;

LookAndFeelManager* LookAndFeelManager::the(void)
{
   if(_the == NULL)
   {
      _the = new LookAndFeelManager();
   }
 
   return _the;
}

bool LookAndFeelManager::uninitialize(void)
{
    _LookAndFeel = NULL;

    return true;
}

void LookAndFeelManager::setLookAndFeel(LookAndFeel* const TheLookAndFeel)
{
	if(TheLookAndFeel != NULL)
	{
		_LookAndFeel = TheLookAndFeel;
	}
}

OSG_END_NAMESPACE
