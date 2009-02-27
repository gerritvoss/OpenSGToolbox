#include "OSGTreeSelectionEvent.h"

#include <stdexcept>

OSG_BEGIN_NAMESPACE

EventType TreeSelectionEvent::_Type("TreeSelectionEvent", "EventType");

TreeSelectionEvent::TreeSelectionEvent(FieldContainerPtr Source, Time TimeStamp, const std::vector<NumberRange>& ElementsChanged, Int32 NewLeadSelectionPath, Int32 OldLeadSelectionPath)
		: Event(Source, TimeStamp),
		_NewLeadSelectionPath(NewLeadSelectionPath),
		_OldLeadSelectionPath(OldLeadSelectionPath),
        _ElementsChanged(ElementsChanged)
{
}

OSG_END_NAMESPACE
