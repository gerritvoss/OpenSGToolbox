#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

OSG_BEGIN_NAMESPACE

inline
const EventType &ListDataEvent::getClassType(void)
{
    return _Type;
}

inline
Int32 	ListDataEvent::getIndex0(void) const
{
   return _Index0;
}

inline
Int32 	ListDataEvent::getIndex1(void) const
{
   return _Index1;
}

inline
ListDataEvent::EventEnum ListDataEvent::getEventEnum(void) const
{
   return _EventEnum;
}

inline
ListModelPtr ListDataEvent::getModel(void) const
{
	return _Model;
}

inline
ListDataEvent::ListDataEvent(FieldContainerPtr Source, Time TimeStamp, Int32 Index0, Int32 Index1, EventEnum Type, ListModelPtr Model)
 : Event(Source, TimeStamp),
   _Index0(Index0),
   _Index1(Index1),
   _EventEnum(Type),
   _Model(Model)
{
}
    
OSG_END_NAMESPACE
