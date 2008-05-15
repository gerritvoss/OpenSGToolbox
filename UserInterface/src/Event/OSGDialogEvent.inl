#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
const EventType &DialogEvent::getClassType(void)
{
    return _Type;
}

inline
UInt32 DialogEvent::getOption(void) const
{
    return _Option;
}

inline
std::string DialogEvent::getInput(void) const
{
    return _Input;
}

inline
DialogEvent::DialogEvent(FieldContainerPtr Source, Time TimeStamp, const UInt32& Option, const std::string& Input) :
   Event(Source, TimeStamp),
       _Option(Option),
       _Input(Input)
{
}

OSG_END_NAMESPACE
