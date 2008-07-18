#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
const EventType &ParticleEvent::getClassType(void)
{
    return _Type;
}

inline
const Pnt3f &ParticleEvent::getPosition(void) const
{
	return _ParticlePosition;
}

OSG_END_NAMESPACE
