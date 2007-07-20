#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
ActionEvent::ActionEvent(FieldContainerPtr Source, Time TimeStamp) :
   Event(Source, TimeStamp)
{
}

OSG_END_NAMESPACE
