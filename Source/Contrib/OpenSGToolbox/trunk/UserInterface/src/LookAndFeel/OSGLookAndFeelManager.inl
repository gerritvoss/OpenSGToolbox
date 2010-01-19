
#include <OpenSG/OSGConfig.h>
#include "OSGDefaultLookAndFeel.h"
#include "OSGWindowsLookAndFeel.h"

OSG_BEGIN_NAMESPACE

inline
LookAndFeelPtr LookAndFeelManager::getLookAndFeel(void)
{
	return _LookAndFeel;
}


inline
LookAndFeelManager::LookAndFeelManager(void)
{
	_LookAndFeel = WindowsLookAndFeel::create();
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
