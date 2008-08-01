#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
const EventType &DragGestureEvent::getClassType(void)
{
    return _Type;
}

inline
ComponentPtr DragGestureEvent::getOriginComponent(void) const
{
    return _OriginComponent;
}

inline
const Pnt2f &DragGestureEvent::getDragLocation(void) const
{
    return _DragLocation;
}

inline
DragGestureEvent::DragGestureEvent(FieldContainerPtr Source, Time TimeStamp, ComponentPtr TheComponent, const Pnt2f &DragLocation) :
   Event(Source, TimeStamp),
       _OriginComponent(TheComponent),
       _DragLocation(DragLocation)
{
}

OSG_END_NAMESPACE
