#include "OSGTreeModelEvent.h"

OSG_BEGIN_NAMESPACE

EventType TreeModelEvent::_Type("TreeModelEvent", "EventType");

const EventType &TreeModelEvent::getType(void) const
{
    return _Type;
}

std::vector<UInt32> TreeModelEvent::getChildIndices(void) const
{
	//TODO: Implement
	return std::vector<UInt32>();
}

std::vector<SharedFieldPtr> TreeModelEvent::getChildren(void) const
{
	//TODO: Implement
	return std::vector<SharedFieldPtr>();
}

std::vector<SharedFieldPtr> TreeModelEvent::getPath(void) const
{
	//TODO: Implement
	return std::vector<SharedFieldPtr>();
}

TreePath TreeModelEvent::getTreePath(void) const
{
	//TODO: Implement
	return TreePath(SharedFieldPtr());
}

TreeModelEvent::TreeModelEvent(FieldContainerPtr Source, Time TimeStamp, std::vector<SharedFieldPtr> path)
		: Event(Source, TimeStamp)
{
	//TODO: Implement
}

TreeModelEvent::TreeModelEvent(FieldContainerPtr Source, Time TimeStamp, std::vector<SharedFieldPtr> path, std::vector<UInt32> childIndices, std::vector<SharedFieldPtr> children)
		: Event(Source, TimeStamp)
{
	//TODO: Implement
}

TreeModelEvent::TreeModelEvent(FieldContainerPtr Source, Time TimeStamp, TreePath path)
		: Event(Source, TimeStamp)
{
	//TODO: Implement
}

TreeModelEvent::TreeModelEvent(FieldContainerPtr Source, Time TimeStamp, TreePath path, std::vector<UInt32> childIndices, std::vector<SharedFieldPtr> children)
		: Event(Source, TimeStamp)
{
	//TODO: Implement
}
OSG_END_NAMESPACE
