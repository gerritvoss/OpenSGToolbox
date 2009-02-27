#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

OSG_BEGIN_NAMESPACE
    
inline
const EventType &TreeModelEvent::getClassType(void)
{
    return _Type;
}

inline
std::vector<UInt32> TreeModelEvent::getChildIndices(void) const
{
	return _ChildIndices;
}

inline
std::vector<boost::any> TreeModelEvent::getChildren(void) const
{
	return _Children;
}

inline
TreePath TreeModelEvent::getPath(void) const
{
	return _Path;
}
OSG_END_NAMESPACE
