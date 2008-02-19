#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

OSG_BEGIN_NAMESPACE

inline
const EventType &UndoableEditEvent::getClassType(void)
{
    return _Type;
}

inline
UndoableEditPtr 	UndoableEditEvent::getUndoableEdit(void) const
{
   return _UndoableEdit;
}

inline
UndoableEditEvent::UndoableEditEvent(FieldContainerPtr Source, Time TimeStamp, UndoableEditPtr UndoableEdit)
 : Event(Source, TimeStamp),
   _UndoableEdit(UndoableEdit)
{
}
    
OSG_END_NAMESPACE
