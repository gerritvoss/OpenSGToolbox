#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE


inline
const EventType &ParticleSystemEvent::getClassType(void)
{
    return _Type;
}

inline
bool ParticleSystemEvent::getVolumeChanged(void) const
{
    return _VolumeChanged;
}

OSG_END_NAMESPACE
