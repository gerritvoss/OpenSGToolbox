
#include <OpenSG/OSGConfig.h>
#include "OSGDefaultLookAndFeel.h"

OSG_BEGIN_NAMESPACE

inline
LookAndFeelPtr LookAndFeelManager::getLookAndFeel(void)
{
	return _LookAndFeel;
}

inline
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

inline
LookAndFeelManager::LookAndFeelManager(void)
{
	_LookAndFeel = DefaultLookAndFeel::create();
	addRefCP(_LookAndFeel);
}

inline
LookAndFeelManager::~LookAndFeelManager(void)
{
	if(_LookAndFeel != NullFC)
	{
		subRefCP(_LookAndFeel);
	}
}

OSG_END_NAMESPACE
