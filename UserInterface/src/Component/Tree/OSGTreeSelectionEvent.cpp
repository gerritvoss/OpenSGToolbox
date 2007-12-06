#include "OSGTreeSelectionEvent.h"

#include <OpenSG/Toolbox/OSGSharedFieldPtr.h>

OSG_BEGIN_NAMESPACE

EventType TreeSelectionEvent::_Type("TreeSelectionEvent", "EventType");

const EventType &TreeSelectionEvent::getType(void) const
{
    return _Type;
}

TreePath TreeSelectionEvent::getNewLeadSelectionPath(void) const
{
	//TODO: Implement
	return TreePath(SharedFieldPtr());
}

TreePath TreeSelectionEvent::getOldLeadSelectionPath(void) const
{
	//TODO: Implement
	return TreePath(SharedFieldPtr());
}

TreePath TreeSelectionEvent::getPath(void) const
{
	//TODO: Implement
	return TreePath(SharedFieldPtr());
}

std::vector<TreePath> TreeSelectionEvent::getPaths(void) const
{
	//TODO: Implement
	return std::vector<TreePath>();
}

bool TreeSelectionEvent::isAddedPath(void) const
{
	//TODO: Implement
	return false;
}

bool TreeSelectionEvent::isAddedPath(const UInt32& index) const
{
	//TODO: Implement
	return false;
}

bool TreeSelectionEvent::isAddedPath(const TreePath& path) const
{
	//TODO: Implement
	return false;
}

OSG_END_NAMESPACE
