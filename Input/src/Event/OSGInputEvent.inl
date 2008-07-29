#include <OpenSG/OSGConfig.h>
#include <assert.h>

OSG_BEGIN_NAMESPACE


inline
const EventType &InputEvent::getClassType(void)
{
    return _Type;
}

inline
void InputEvent::consume(void) const
{
	_Consumed = true;
}

inline
bool InputEvent::isConsumed(void) const
{
    return _Consumed;
}

inline
WindowEventProducerPtr InputEvent::getEventProducer(void) const
{
    return _EventProducer;
}

inline
InputEvent::InputEvent(FieldContainerPtr Source, Time TimeStamp, WindowEventProducerPtr Producer) 
: Event(Source, TimeStamp),
_Consumed(false),
_EventProducer(Producer)
{}

    
OSG_END_NAMESPACE
