/*---------------------------------------------------------------------------*\
 *                          OpenSG Toolbox Physics                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala                                                   *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
const Pnt3f& CollisionEvent::getPosition(void) const
{
    return _Position;
}

inline
const Vec3f& CollisionEvent::getNormal(void) const
{
    return _Normal;
}

inline
const Vec3f& CollisionEvent::getVelocity1(void) const
{
    return _Velocity1;
}

inline
const Vec3f& CollisionEvent::getVelocity2(void) const
{
    return _Velocity2;
}

inline
PhysicsGeomPtr CollisionEvent::getGeom1(void) const
{
    return _Geom1;
}

inline
PhysicsGeomPtr CollisionEvent::getGeom2(void) const
{
    return _Geom2;
}


inline
const EventType &CollisionEvent::getClassType(void)
{
    return _Type;
}

inline
CollisionEvent::    CollisionEvent(FieldContainerPtr Source, Time TimeStamp, const Pnt3f& Position,const Vec3f& Normal, PhysicsGeomPtr Geom1,PhysicsGeomPtr Geom2,const Vec3f& Velocity1,const Vec3f& Velocity2) :
   Event(Source, TimeStamp),
    _Position(Position),
    _Normal(Normal),
    _Geom1(Geom1), _Geom2(Geom2),
    _Velocity1(Velocity1), _Velocity2(Velocity2)
{
}

OSG_END_NAMESPACE
