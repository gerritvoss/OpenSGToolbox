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

void LookAndFeelManager::setLookAndFeel(LookAndFeelPtr TheLookAndFeel)
{
	if(TheLookAndFeel != NullFC)
	{
		if(_LookAndFeel != NullFC)
		{
			subRefCP(_LookAndFeel);
		}
		_LookAndFeel = TheLookAndFeel;
		addRefCP(_LookAndFeel);
	}

}

OSG_END_NAMESPACE
