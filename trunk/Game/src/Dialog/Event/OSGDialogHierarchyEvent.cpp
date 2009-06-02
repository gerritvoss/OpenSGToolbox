#include "OSGDialogHierarchyEvent.h"

OSG_BEGIN_NAMESPACE

EventType DialogHierarchyEvent::_Type("DialogHierarchyEvent", "EventType");

const EventType &DialogHierarchyEvent::getType(void) const
{
    return _Type;
}

DialogHierarchyEvent::DialogHierarchyEvent(FieldContainerPtr Source, Time TimeStamp) :
   Event(Source, TimeStamp)
{
}

OSG_END_NAMESPACE
