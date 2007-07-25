#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

OSG_BEGIN_NAMESPACE

inline
UInt32 	ListDataEvent::getIndex0(void) const
{
   return _Index0;
}

inline
UInt32 	ListDataEvent::getIndex1(void) const
{
   return _Index1;
}

inline
ListDataEvent::EventType 	ListDataEvent::getType(void) const
{
   return _Type;
}

inline
ListModelPtr ListDataEvent::getModel(void) const
{
	return _Model;
}

inline
ListDataEvent::ListDataEvent(FieldContainerPtr Source, Time TimeStamp, UInt32 Index0, UInt32 Index1, EventType Type, ListModelPtr Model)
 : Event(Source, TimeStamp),
   _Index0(Index0),
   _Index1(Index1),
   _Type(Type),
   _Model(Model)
{
}
    
OSG_END_NAMESPACE
