#include "OSGTreeModelEvent.h"

OSG_BEGIN_NAMESPACE

EventType TreeModelEvent::_Type("TreeModelEvent", "EventType");

const EventType &TreeModelEvent::getType(void) const
{
    return _Type;
}

TreeModelEvent::TreeModelEvent(FieldContainerPtr Source, Time TimeStamp, const TreePath& path)
		: Event(Source, TimeStamp),
		_Path(path)
{
}

TreeModelEvent::TreeModelEvent(FieldContainerPtr Source, Time TimeStamp, const TreePath& path, const std::vector<UInt32>& childIndices, const std::vector<boost::any>& children)
		: Event(Source, TimeStamp),
		_Path(path),
		_Children(children),
		_ChildIndices(childIndices)
{
}

OSG_END_NAMESPACE
