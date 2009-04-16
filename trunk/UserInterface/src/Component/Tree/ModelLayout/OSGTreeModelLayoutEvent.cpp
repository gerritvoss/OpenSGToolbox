#include "OSGTreeModelLayoutEvent.h"

OSG_BEGIN_NAMESPACE

EventType TreeModelLayoutEvent::_Type("TreeModelLayoutEvent", "EventType");

const EventType &TreeModelLayoutEvent::getType(void) const
{
    return _Type;
}

TreeModelLayoutEvent::TreeModelLayoutEvent(FieldContainerPtr Source, Time TimeStamp, EventEnum TheEvent, TreePath path)
		: Event(Source, TimeStamp),
        _Event(TheEvent),
		_Path(path)
{
}

OSG_END_NAMESPACE
