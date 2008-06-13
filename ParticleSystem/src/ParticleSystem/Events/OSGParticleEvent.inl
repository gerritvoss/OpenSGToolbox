#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
const EventType &ParticleEvent::getClassType(void)
{
    return _Type;
}

OSG_END_NAMESPACE
