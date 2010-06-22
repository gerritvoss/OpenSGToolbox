#include "OSGLookAndFeelManager.h"

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

void LookAndFeelManager::setLookAndFeel(LookAndFeelRefPtr TheLookAndFeel)
{
	if(TheLookAndFeel != NULL)
	{
		_LookAndFeel = TheLookAndFeel;
	}

}

OSG_END_NAMESPACE
