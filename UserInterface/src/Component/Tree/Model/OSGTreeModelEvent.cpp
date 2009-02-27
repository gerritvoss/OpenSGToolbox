#include "OSGTreeModelEvent.h"

OSG_BEGIN_NAMESPACE

EventType TreeModelEvent::_Type("TreeModelEvent", "EventType");

const EventType &TreeModelEvent::getType(void) const
{
    return _Type;
}

TreeModelEvent::TreeModelEvent(FieldContainerPtr Source, Time TimeStamp, std::vector<boost::any> path)
		: Event(Source, TimeStamp),
		_Path(path)
{
}

TreeModelEvent::TreeModelEvent(FieldContainerPtr Source, Time TimeStamp, std::vector<boost::any> path, std::vector<UInt32> childIndices, std::vector<boost::any> children)
		: Event(Source, TimeStamp),
		_Path(path),
		_Children(children),
		_ChildIndices(childIndices)
{
}

TreeModelEvent::TreeModelEvent(FieldContainerPtr Source, Time TimeStamp, TreePath path)
		: Event(Source, TimeStamp),
		_Path(path)
{
}

TreeModelEvent::TreeModelEvent(FieldContainerPtr Source, Time TimeStamp, TreePath path, std::vector<UInt32> childIndices, std::vector<boost::any> children)
		: Event(Source, TimeStamp),
		_Path(path),
		_Children(children),
		_ChildIndices(childIndices)
{
}
OSG_END_NAMESPACE
