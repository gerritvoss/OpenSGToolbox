#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

OSG_BEGIN_NAMESPACE
    
inline
const EventType &TreeModelLayoutEvent::getClassType(void)
{
    return _Type;
}

inline
TreePath TreeModelLayoutEvent::getPath(void) const
{
	return _Path;
}

inline
TreeModelLayoutEvent::EventEnum TreeModelLayoutEvent::getEvent(void) const
{
	return _Event;
}

OSG_END_NAMESPACE
