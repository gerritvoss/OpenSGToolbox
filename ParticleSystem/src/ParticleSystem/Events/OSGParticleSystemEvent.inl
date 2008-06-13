#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE


inline
const EventType &ParticleSystemEvent::getClassType(void)
{
    return _Type;
}

OSG_END_NAMESPACE
