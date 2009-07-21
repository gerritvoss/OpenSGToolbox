#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
const EventType &ParticleEvent::getClassType(void)
{
    return _Type;
}

inline
const Int32 &ParticleEvent::getIndex(void) const
{
    return _ParticleIndex;
}

inline
const ParticleSystemPtr &ParticleEvent::getSystem(void) const
{
    return _System;
}

inline
const Pnt3f &ParticleEvent::getPosition(void) const
{
    return _ParticlePosition;
}

inline
const Pnt3f &ParticleEvent::getSecPosition(void) const
{
    return _ParticleSecPosition;
}

inline
const Vec3f &ParticleEvent::getNormal(void) const
{
    return _ParticleNormal;
}

inline
const Color4f &ParticleEvent::getColor(void) const
{
    return _ParticleColor;
}

inline
const Vec3f &ParticleEvent::getSize(void) const
{
    return _ParticleSize;
}

inline
const Real32 &ParticleEvent::getLifespan(void) const
{
    return _ParticleLifespan;
}

inline
const Real32 &ParticleEvent::getAge(void) const
{
    return _ParticleAge;
}

inline
const Vec3f &ParticleEvent::getVelocity(void) const
{
    return _ParticleVelocity;
}

inline
const Vec3f &ParticleEvent::getSecVelocity(void) const
{
    return _ParticleSecVelocity;
}

inline
const Vec3f &ParticleEvent::getAcceleration(void) const
{
    return _ParticleAcceleration;
}

inline
const StringToUInt32Map &ParticleEvent::getAttributes(void) const
{
    return _ParticleAttributes;
}


OSG_END_NAMESPACE
