#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
ParticleEvent::ParticleEvent(FieldContainerPtr Source, Time TimeStamp) :
   Event(Source, TimeStamp)
{
}

OSG_END_NAMESPACE
