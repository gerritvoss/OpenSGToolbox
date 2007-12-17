#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

OSG_BEGIN_NAMESPACE
    
inline
const EventType &TreeSelectionEvent::getClassType(void)
{
    return _Type;
}

inline
const EventType &TreeSelectionEvent::getType(void) const
{
    return _Type;
}

inline
TreePath TreeSelectionEvent::getNewLeadSelectionPath(void) const
{
	return _NewLeadSelectionPath;
}

inline
TreePath TreeSelectionEvent::getOldLeadSelectionPath(void) const
{
	return _OldLeadSelectionPath;
}

inline
TreePath TreeSelectionEvent::getPath(void) const
{
	return _Path.front();
}

inline
std::vector<TreePath> TreeSelectionEvent::getPaths(void) const
{
	return _Path;
}

inline
bool TreeSelectionEvent::isAddedPath(void) const
{
	return _IsPathNew.front();
}

OSG_END_NAMESPACE
