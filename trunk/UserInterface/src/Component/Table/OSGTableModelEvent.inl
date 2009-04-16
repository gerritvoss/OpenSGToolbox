#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

OSG_BEGIN_NAMESPACE


inline
const EventType &TableModelEvent::getClassType(void)
{
    return _Type;
}

inline
const UInt32& TableModelEvent::getFirstColumn(void) const
{
    return _FirstColumn;
}

inline
const UInt32& TableModelEvent::getLastColumn(void) const
{
    return _LastColumn;
}

inline
const UInt32& TableModelEvent::getFirstRow(void) const
{
    return _FirstRow;
}

inline
const UInt32& TableModelEvent::getLastRow(void) const
{
    return _LastRow;
}

inline
const UInt32& TableModelEvent::getEventType(void) const
{
    return _EventType;
}

inline
TableModelPtr& TableModelEvent::getModel(void)
{
    return _Model;
}

inline
TableModelEvent::TableModelEvent(FieldContainerPtr Source, Time TimeStamp, UInt32 FirstColumn, UInt32 LastColumn, UInt32 FirstRow, UInt32 LastRow, EventEnum Type, TableModelPtr Model) :
    Event(Source, TimeStamp),
    _FirstColumn(FirstColumn),
    _LastColumn(LastColumn),
    _FirstRow(FirstRow),
    _LastRow(LastRow),
    _EventType(Type),
    _Model(Model)
{
}

OSG_END_NAMESPACE
