#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
FieldContainerPtr Event::getSource() const
{
    return _Source; 
}

inline
Time Event::getTimeStamp() const
{
    return _TimeStamp; 
}
    
inline
Event::Event(FieldContainerPtr Source, Time TimeStamp) : _Source(Source), _TimeStamp(TimeStamp)
{
}
  
OSG_END_NAMESPACE
