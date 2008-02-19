#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

OSG_BEGIN_NAMESPACE

inline
const EventType &CommandEvent::getClassType(void)
{
    return _Type;
}

inline
CommandPtr 	CommandEvent::getCommand(void) const
{
   return _Command;
}

inline
CommandEvent::CommandEvent(FieldContainerPtr Source, Time TimeStamp, CommandPtr Command)
 : Event(Source, TimeStamp),
   _Command(Command)
{
}
    
OSG_END_NAMESPACE
