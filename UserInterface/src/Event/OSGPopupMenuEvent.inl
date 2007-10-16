#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
const EventType &PopupMenuEvent::getClassType(void)
{
    return _Type;
}

inline
PopupMenuEvent::PopupMenuEvent(FieldContainerPtr Source, Time TimeStamp) :
   Event(Source, TimeStamp)
{
}

OSG_END_NAMESPACE
