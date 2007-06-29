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

OSG_END_NAMESPACE
