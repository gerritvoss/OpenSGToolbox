#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

OSG_BEGIN_NAMESPACE

inline
const EventType &TableColumnModelEvent::getClassType(void)
{
    return _Type;
}

inline
const UInt32& TableColumnModelEvent::getFromIndex(void) const
{
    return _FromIndex;
}

inline
const UInt32& TableColumnModelEvent::getToIndex(void) const
{
    return _ToIndex;
}

inline
const UInt32& TableColumnModelEvent::getEventType(void) const
{
    return _EventType;
}

inline
TableColumnModelPtr TableColumnModelEvent::getModel(void)
{
    return _Model;
}

inline
TableColumnModelEvent::TableColumnModelEvent(FieldContainerPtr Source, Time TimeStamp, UInt32 FromIndex, UInt32 ToIndex, EventEnum Type, TableColumnModelPtr Model) :
    Event(Source, TimeStamp),
    _FromIndex(FromIndex),
    _ToIndex(ToIndex),
    _EventType(Type),
    _Model(Model)
{
}

OSG_END_NAMESPACE
