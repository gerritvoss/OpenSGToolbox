#include "OSGComboBoxSelectionEvent.h"

OSG_BEGIN_NAMESPACE

EventType ComboBoxSelectionEvent::_Type("ComboBoxSelectionEvent", "EventType");

const EventType &ComboBoxSelectionEvent::getType(void) const
{
    return _Type;
}

OSG_END_NAMESPACE
