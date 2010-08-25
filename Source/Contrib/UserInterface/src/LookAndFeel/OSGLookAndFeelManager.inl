
#include "OSGConfig.h"
#include "OSGDefaultLookAndFeel.h"
#include "OSGWindowsLookAndFeel.h"

OSG_BEGIN_NAMESPACE

inline
LookAndFeel* LookAndFeelManager::getLookAndFeel(void) const
{
	return _LookAndFeel;
}


inline
LookAndFeelManager::LookAndFeelManager(void)
{
	_LookAndFeel = WindowsLookAndFeel::create();
    addPreFactoryExitFunction(boost::bind(&LookAndFeelManager::uninitialize, this));
}

inline
LookAndFeelManager::~LookAndFeelManager(void)
{
}

OSG_END_NAMESPACE
