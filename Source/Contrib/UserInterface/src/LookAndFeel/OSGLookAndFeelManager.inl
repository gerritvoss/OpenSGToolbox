
#include "OSGConfig.h"
#include "OSGDefaultLookAndFeel.h"
#include "OSGWindowsLookAndFeel.h"

OSG_BEGIN_NAMESPACE

inline
LookAndFeelRefPtr LookAndFeelManager::getLookAndFeel(void)
{
	return _LookAndFeel;
}


inline
LookAndFeelManager::LookAndFeelManager(void)
{
	_LookAndFeel = WindowsLookAndFeel::create();
}

inline
LookAndFeelManager::~LookAndFeelManager(void)
{
}

OSG_END_NAMESPACE
