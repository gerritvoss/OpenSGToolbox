/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGParticleSystem.h"
#include "OSGParticleAffector.h"
#include "OSGParticleSystemAffector.h"
#include "OSGParticleGenerator.h"
#include "OSGIntersectAction.h"
#include "OSGUpdateEventDetails.h"
#include "OSGStatCollector.h"
#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGParticleSystemBase.cpp file.
// To modify it, please change the .fcd file (OSGParticleSystem.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

const OSG::BitVector  ParticleSystem::InternalParticlesFieldMask = 
    (TypeTraits<BitVector>::One << ParticleSystem::InternalPositionsFieldId) ||
    (TypeTraits<BitVector>::One << ParticleSystem::InternalSecPositionsFieldId) ||
    (TypeTraits<BitVector>::One << ParticleSystem::InternalNormalsFieldId) ||
    (TypeTraits<BitVector>::One << ParticleSystem::InternalColorsFieldId) ||
    (TypeTraits<BitVector>::One << ParticleSystem::InternalSizesFieldId) ||
    (TypeTraits<BitVector>::One << ParticleSystem::InternalLifespansFieldId) ||
    (TypeTraits<BitVector>::One << ParticleSystem::InternalAgesFieldId) ||
    (TypeTraits<BitVector>::One << ParticleSystem::InternalVelocitiesFieldId) ||
    (TypeTraits<BitVector>::One << ParticleSystem::InternalSecVelocitiesFieldId) ||
    (TypeTraits<BitVector>::One << ParticleSystem::InternalAccelerationsFieldId) ||
    (TypeTraits<BitVector>::One << ParticleSystem::InternalAttributesFieldId) ||
    (TypeTraits<BitVector>::One << ParticleSystem::InternalIDsFieldId);

StatElemDesc<StatIntElem> ParticleSystem::statNParticles("NParticles", 
                                                         "number of particles");

StatElemDesc<StatIntElem> ParticleSystem::statNParticlesCreated("NParticlesCreated", 
                                                                "number of particles created");

StatElemDesc<StatIntElem> ParticleSystem::statNParticlesKilled("NParticlesKilled", 
                                                                  "number of particles killed");

StatElemDesc<StatTimeElem> ParticleSystem::statParticleUpdateTime("ParticleUpdateTime", 
                                                                    "time for particle system updates");

StatElemDesc<StatTimeElem> ParticleSystem::statParticleSortTime("ParticleSortTime", 
                                                                    "time for particle sorting");
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParticleSystem::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ParticleSystem::attachUpdateProducer(ReflexiveContainer* const producer)
{
    if(_UpdateEventConnection.connected())
    {
        _UpdateEventConnection.disconnect();
    }
    //Get the Id of the UpdateEvent
    const EventDescription* Desc(producer->getProducerType().findEventDescription("Update"));
    if(Desc == NULL)
    {
        SWARNING << "There is no Update event defined on " << producer->getType().getName() << " types." << std::endl;
    }
    else
    {
        _UpdateEventConnection = producer->connectEvent(Desc->getEventId(), boost::bind(&ParticleSystem::attachedUpdate, this, _1));
    }
}

void ParticleSystem::attachedUpdate(EventDetails* const details)
{
    update(dynamic_cast<UpdateEventDetails* const>(details)->getElapsedTime());
}

//Particle to Geometry Intersection
std::vector<UInt32> ParticleSystem::intersect(const NodeRefPtr CollisionNode, bool sort, NodeRefPtr Beacon) const
{
    //Get all of the particles that collide with the geometries volume
    BoxVolume Vol;
    CollisionNode->getWorldVolume(Vol);
    std::vector<UInt32> IndexesToTest = intersect(Vol, 0.0f, Beacon);

    std::vector<UInt32> Result;

    Line ray;
    IntersectAction *iAct = IntersectAction::create();
    Pnt3f ParticlePos, ParticleSecPos;

    Real32 HitT(0.0f);

    BoxVolume BeaconWorldVol;
    Matrix BeaconToWorld;

    //If the Beacon node given to this function is Null
    if(Beacon == NULL)
    {
        //If the Beacon node attached to this particle system is Null
        if(getBeacon() == NULL)
        {
            BeaconToWorld.setIdentity();
            BeaconWorldVol.setInfinite(true);
        }
        else
        {
            BeaconToWorld = getBeacon()->getToWorld();
            getBeacon()->getWorldVolume(BeaconWorldVol);
        }
    }
    else
    {
        BeaconToWorld = Beacon->getToWorld();
        Beacon->getWorldVolume(BeaconWorldVol);
    }
    //Test all of the particles that collide with the geometries volume
    for(UInt32 i(0) ; i<IndexesToTest.size() ; ++i)
    {
        ParticlePos = BeaconToWorld*getPosition(IndexesToTest[i]);
        ParticleSecPos = BeaconToWorld*getSecPosition(IndexesToTest[i]);
        ray.setValue(ParticleSecPos, ParticlePos);
        iAct->setLine(ray);
        iAct->apply(CollisionNode);

        if (iAct->didHit())
        {
            HitT = iAct->getHitT();
            if(HitT > 0.0f && HitT*HitT<ParticlePos.dist2(ParticleSecPos))
            {
                Result.push_back(IndexesToTest[i]);
            }
        }
    }

    //if(sort)
    //{
    //    std::sort(Result.begin(), Result.end(), ParticlePositionSort(this, Ray.getPosition()));
    //}
    return Result;
}

//Particle to Line Segment intersection
std::vector<UInt32> ParticleSystem::intersect(const Pnt3f& p1, const Pnt3f& p2, Real32 IntersectionDistance, NodeRefPtr Beacon) const
{
    std::vector<UInt32> Result;

    BoxVolume BeaconWorldVol;
    Matrix BeaconToWorld;


    //If the Beacon node given to this function is Null
    if(Beacon == NULL)
    {
        //If the Beacon node attached to this particle system is Null
        if(getBeacon() == NULL)
        {
            BeaconToWorld.setIdentity();
            BeaconWorldVol.setInfinite(true);
        }
        else
        {
            BeaconToWorld = getBeacon()->getToWorld();
            getBeacon()->getWorldVolume(BeaconWorldVol);
        }
    }
    else
    {
        BeaconToWorld = Beacon->getToWorld();
        Beacon->getWorldVolume(BeaconWorldVol);
    }

    Pnt3f ClosestPoint;
    Pnt3f ParticleWorldPosition;
    Real32 MinDist2(IntersectionDistance * IntersectionDistance);

    //Real32 EnterVol,ExitVol;
    //Check if this ray intersects with the Beacons volume

    //TODO: Check for intersection with the volume

    //The volume needs to be extended so that there is an intersection
    //When the bound volume is not intersecting with the line but is intersecting
    //with the IntersectionDistance from the line
    //BeaconWorldVol.extendBy(BeaconWorldVol.getMin() - Vec3f(IntersectionDistance, IntersectionDistance, IntersectionDistance));
    //BeaconWorldVol.extendBy(BeaconWorldVol.getMax() + Vec3f(IntersectionDistance, IntersectionDistance, IntersectionDistance));
    //if(
    //(BeaconWorldVol.getType() == BoxVolume::BOX_VOLUME && Ray.intersect(static_cast<const BoxVolume&>(BeaconWorldVol.getInstance()),EnterVol,ExitVol)) ||
    //(BeaconWorldVol.getType() == BoxVolume::SPHERE_VOLUME && Ray.intersect(static_cast<const SphereVolume&>(BeaconWorldVol.getInstance()),EnterVol,ExitVol))
    //)
    //{
    //Point on Line Segment
    //p = p1 + t*(p2-p1);  for 0 <= t <= 1
    //
    //Test for point on Line Segment
    //(p . p) = (p1 . p) + t((p2 . p) - (p1 . p)) 
    //((p-p1).p)/((p2-p1).p) = t
    Vec3f Disp(p2-p1);
    Vec3f Dir(Disp);
    Dir.normalize();
    Real32 t(0.0);
    //For each particle
    for(UInt32 i(0) ; i< getNumParticles(); ++i)
    {
        ParticleWorldPosition = BeaconToWorld*getPosition(i);
        Vec3f vec(ParticleWorldPosition - p1);

        t = osgClamp(0.0f,(Disp.dot(vec)/Disp.length()),1.0f);

        ClosestPoint = p1 + Disp*t;

        if(ClosestPoint.dist2(ParticleWorldPosition) < MinDist2)
        {
            Result.push_back(i);
        }
    }
    //}

    return Result;
}

std::vector<UInt32> ParticleSystem::intersect(const Volume& Vol, Real32 IntersectionDistance, NodeRefPtr Beacon) const
{
    std::vector<UInt32> Result;

    BoxVolume BeaconWorldVol, TestVolume;
    TestVolume.extendBy(Vol);
    Matrix BeaconToWorld;


    //If the Beacon node given to this function is Null
    if(Beacon == NULL)
    {
        //If the Beacon node attached to this particle system is Null
        if(getBeacon() == NULL)
        {
            BeaconToWorld.setIdentity();
            BeaconWorldVol.setInfinite(true);
        }
        else
        {
            BeaconToWorld = getBeacon()->getToWorld();
            getBeacon()->getWorldVolume(BeaconWorldVol);
        }
    }
    else
    {
        BeaconToWorld = Beacon->getToWorld();
        Beacon->getWorldVolume(BeaconWorldVol);
    }

    Pnt3f ClosestPoint;
    Pnt3f ParticleWorldPosition;
    Real32 MinDist2(IntersectionDistance * IntersectionDistance);

    //Check if this ray intersects with the Beacons volume

    //The volume needs to be extended so that there is an intersection
    //When the bound volume is not intersecting with the line but is intersecting
    //with the IntersectionDistance from the line
    TestVolume.extendBy(BeaconWorldVol.getMin() - Vec3f(IntersectionDistance, IntersectionDistance, IntersectionDistance));
    TestVolume.extendBy(BeaconWorldVol.getMax() + Vec3f(IntersectionDistance, IntersectionDistance, IntersectionDistance));
    if(BeaconWorldVol.intersect(TestVolume))
    {
        //For each particle
        for(UInt32 i(0) ; i< getNumParticles(); ++i)
        {
            ParticleWorldPosition = BeaconToWorld*getPosition(i);
            if(TestVolume.intersect(ParticleWorldPosition))
            {
                Result.push_back(i);
            }
        }
    }

    return Result;
}

std::vector<UInt32> ParticleSystem::intersect(const Line& Ray, Real32 MinDistFromRay, Real32 MinDistFromRayOrigin, bool sort, NodeRefPtr Beacon) const
{
    std::vector<UInt32> Result;

    BoxVolume BeaconWorldVol;
    Matrix BeaconToWorld;


    //If the Beacon node given to this function is Null
    if(Beacon == NULL)
    {
        //If the Beacon node attached to this particle system is Null
        if(getBeacon() == NULL)
        {
            BeaconToWorld.setIdentity();
            BeaconWorldVol.setInfinite(true);
        }
        else
        {
            BeaconToWorld = getBeacon()->getToWorld();
            getBeacon()->getWorldVolume(BeaconWorldVol);
        }
    }
    else
    {
        BeaconToWorld = Beacon->getToWorld();
        Beacon->getWorldVolume(BeaconWorldVol);
    }

    Pnt3f ClosestPoint;
    Pnt3f ParticleWorldPosition;
    Real32 MinDistFromRaySqr(MinDistFromRay * MinDistFromRay);
    Real32 MinDistFromRayOriginSqr(MinDistFromRayOrigin * MinDistFromRayOrigin);

    Real32 EnterVol,ExitVol;
    //Check if this ray intersects with the Beacons volume

    //The volume needs to be extended so that there is an intersection
    //When the bound volume is not intersecting with the line but is intersecting
    //with the IntersectionDistance from the line
    BeaconWorldVol.extendBy(BeaconWorldVol.getMin() - Vec3f(MinDistFromRay, MinDistFromRay, MinDistFromRay));
    BeaconWorldVol.extendBy(BeaconWorldVol.getMax() + Vec3f(MinDistFromRay, MinDistFromRay, MinDistFromRay));
    if(Ray.intersect(BeaconWorldVol,EnterVol,ExitVol))
    {
        Real32 t(0.0f);
        //For each particle
        for(UInt32 i(0) ; i< getNumParticles(); ++i)
        {
            ParticleWorldPosition = BeaconToWorld*getPosition(i);
            ClosestPoint = Ray.getClosestPoint(ParticleWorldPosition);
            t = (Vec3f(ClosestPoint).dot(Vec3f(ClosestPoint) - Vec3f(Ray.getPosition())))/(Ray.getDirection().dot(Vec3f(ClosestPoint)));
            if(t < 0.0)
            {
                ClosestPoint = Ray.getPosition();
            }

            if(ClosestPoint.dist2(ParticleWorldPosition) < MinDistFromRaySqr &&
               (MinDistFromRayOrigin <= 0 || Ray.getPosition().dist2(ParticleWorldPosition) < MinDistFromRayOriginSqr))
            {
                Result.push_back(i);
            }
        }
    }

    if(sort)
    {
        BeaconToWorld.invert();
        std::sort(Result.begin(), Result.end(), ParticlePositionSort(this, BeaconToWorld*Ray.getPosition()));
    }

    return Result;
}

void ParticleSystem::addAndExpandSecPositions(const Pnt3f& SecPosition)
{
    if(getMFInternalSecPositions()->size() == 1)
    {
        if(getInternalSecPositions(0) != SecPosition)
        {
            editMFInternalSecPositions()->resize(getMFInternalPositions()->size(), getInternalSecPositions(0));

            editMFInternalSecPositions()->back() = SecPosition;
        }
    }
    else
    {
        editMFInternalSecPositions()->push_back(SecPosition);
    }
}

void ParticleSystem::addAndExpandNormals(const Vec3f& Normal)
{
    if(getMFInternalNormals()->size() == 1)
    {
        if(getInternalNormals(0) != Normal)
        {
            editMFInternalNormals()->resize(getMFInternalPositions()->size(), getInternalNormals(0));

            editMFInternalNormals()->back() = Normal;
        }
    }
    else
    {
        editMFInternalNormals()->push_back(Normal);
    }
}

void ParticleSystem::addAndExpandColors(const Color4f& Color)
{
    if(getMFInternalColors()->size() == 1)
    {
        if(getInternalColors(0) != Color)
        {
            editMFInternalColors()->resize(getMFInternalPositions()->size(), getInternalColors(0));

            editMFInternalColors()->back() = Color;
        }
    }
    else
    {
        editMFInternalColors()->push_back(Color);
    }
}

void ParticleSystem::addAndExpandSizes(const Vec3f& Size)
{
    if(getMFInternalSizes()->size() == 1)
    {
        if(getInternalSizes(0) != Size)
        {
            editMFInternalSizes()->resize(getMFInternalPositions()->size(), getInternalSizes(0));

            editMFInternalSizes()->back() = Size;
        }
    }
    else
    {
        editMFInternalSizes()->push_back(Size);
    }
}

void ParticleSystem::addAndExpandLifespans(Real32 Lifespan)
{
    if(getMFInternalLifespans()->size() == 1)
    {
        if(getInternalLifespans(0) != Lifespan)
        {
            editMFInternalLifespans()->resize(getMFInternalPositions()->size(), getInternalLifespans(0));

            editMFInternalLifespans()->back() = Lifespan;
        }
    }
    else
    {
        editMFInternalLifespans()->push_back(Lifespan);
    }
}

void ParticleSystem::addAndExpandAges(Real32 Age)
{
    if(getMFInternalAges()->size() == 1)
    {
        if(getInternalAges(0) != Age)
        {
            editMFInternalAges()->resize(getMFInternalPositions()->size(), getInternalAges(0));

            editMFInternalAges()->back() = Age;
        }
    }
    else
    {
        editMFInternalAges()->push_back(Age);
    }
}

void ParticleSystem::addAndExpandVelocities(const Vec3f& Velocity)
{
    if(getMFInternalVelocities()->size() == 1)
    {
        if(getInternalVelocities(0) != Velocity)
        {
            editMFInternalVelocities()->resize(getMFInternalPositions()->size(), getInternalVelocities(0));

            editMFInternalVelocities()->back() = Velocity;
        }
    }
    else
    {
        editMFInternalVelocities()->push_back(Velocity);
    }
}

void ParticleSystem::addAndExpandSecVelocities(const Vec3f& SecVelocity)
{
    if(getMFInternalSecVelocities()->size() == 1)
    {
        if(getInternalSecVelocities(0) != SecVelocity)
        {
            editMFInternalSecVelocities()->resize(getMFInternalPositions()->size(), getInternalSecVelocities(0));

            editMFInternalSecVelocities()->back() = SecVelocity;
        }
    }
    else
    {
        editMFInternalSecVelocities()->push_back(SecVelocity);
    }
}

void ParticleSystem::addAndExpandAccelerations(const Vec3f& Acceleration)
{
    if(getMFInternalAccelerations()->size() == 1)
    {
        if(getInternalAccelerations(0) != Acceleration)
        {
            editMFInternalAccelerations()->resize(getMFInternalPositions()->size(), getInternalAccelerations(0));

            editMFInternalAccelerations()->back() = Acceleration;
        }
    }
    else
    {
        editMFInternalAccelerations()->push_back(Acceleration);
    }
}

void ParticleSystem::addAndExpandAttributes(const StringToUInt32Map& AttributeMap)
{
    if(getMFInternalAttributes()->size() == 1)
    {
        if(getInternalAttributes(0) != AttributeMap)
        {
            editMFInternalAttributes()->resize(getMFInternalPositions()->size(), getInternalAttributes(0));

            editMFInternalAttributes()->back() = AttributeMap;
        }
    }
    else
    {
        editMFInternalAttributes()->push_back(AttributeMap);
    }
}

Int64 ParticleSystem::getIndex(UInt32 ParticleID) const
{
    Int64 i;
    for(i = 0; i < getNumParticles(); ++i)
    {
        if(getID(i) == ParticleID)
        {
            return i;
        }
    }
    return -1;
}

bool ParticleSystem::internalKillParticle(UInt32 Index)
{
    if(Index >= getNumParticles())
    {
        return false;
    }

    Pnt3f Position(getPosition(Index));
    Pnt3f SecPosition(getSecPosition(Index));
    Vec3f Normal(getNormal(Index));
    Color4f Color(getColor(Index));
    Vec3f Size(getSize(Index));
    Real32 Lifespan(getLifespan(Index));
    Real32 Age(getAge(Index));
    Vec3f Velocity(getVelocity(Index));
    Vec3f SecVelocity(getSecVelocity(Index));
    Vec3f Acceleration(getAcceleration(Index));
    UInt32 ID(getID(Index));
    StringToUInt32Map Attributes;
    // only attempting to retrieve attributes if there are any present
    if(getNumAttributes() > 0) Attributes = getAttributes(Index);

    removePosition(Index);
    removeSecPosition(Index);
    removeNormal(Index);
    removeColor(Index);
    removeSize(Index);
    removeLifespan(Index);
    removeAge(Index);
    removeVelocity(Index);
    removeSecVelocity(Index);
    removeAcceleration(Index);
    removeAttributes(Index);
    removeID(Index);

    //If not currently updating the whole system, then update the volume
    if(!_isUpdating)
    {
        updateVolume();
    }

    //Increment the Num particles created statistic
    StatIntElem *statElem = StatCollector::getGlobalElem(ParticleSystem::statNParticlesKilled);
    if(statElem)
    {
        statElem->inc();
    }

    produceParticleKilled(Index, Position, SecPosition, Normal, Color, Size, Lifespan, Age, Velocity, SecVelocity, Acceleration, Attributes,ID);

    return true;
}

bool ParticleSystem::killParticle(UInt32 Index, bool KillNextUpdate)
{
    if(_isUpdating || KillNextUpdate)
    {
        _ParticlesToKill.insert(Index);
        return false;
    }
    else
    {
        return internalKillParticle(Index);
    }
}

bool ParticleSystem::killParticleByID(UInt32 ID, bool KillNextUpdate)
{
    Int64 index(getIndex(ID));

    if(index >= 0) 
        return killParticle(index,KillNextUpdate);
    else 
        return false;
}

void ParticleSystem::removePosition(UInt32 Index)
{
    editInternalPositions(Index) = getMFInternalPositions()->back();
    editMFInternalPositions()->erase(--editMFInternalPositions()->end());
}

void ParticleSystem::removeID(UInt32 Index)
{
    editInternalIDs(Index) = getMFInternalIDs()->back();
    editMFInternalIDs()->erase(--editMFInternalIDs()->end());
}

void ParticleSystem::removeSecPosition(UInt32 Index)
{
    if(getNumSecPositions() > 1)
    {
        editInternalSecPositions(Index) = getMFInternalSecPositions()->back();
        editMFInternalSecPositions()->erase(--editMFInternalSecPositions()->end());
    }
    else if(getNumParticles() == 0)
    {
        editMFInternalSecPositions()->clear();
    }
}

void ParticleSystem::removeNormal(UInt32 Index)
{
    if(getNumNormals() > 1)
    {
        editInternalNormals(Index) = getMFInternalNormals()->back();
        editMFInternalNormals()->erase(--editMFInternalNormals()->end());
    }
    else if(getNumParticles() == 0)
    {
        editMFInternalNormals()->clear();
    }
}

void ParticleSystem::removeColor(UInt32 Index)
{
    if(getNumColors() > 1)
    {
        editInternalColors(Index) = getMFInternalColors()->back();
        editMFInternalColors()->erase(--editMFInternalColors()->end());
    }
    else if(getNumParticles() == 0)
    {
        editMFInternalColors()->clear();
    }
}

void ParticleSystem::removeSize(UInt32 Index)
{
    if(getNumSizes() > 1)
    {
        editInternalSizes(Index) = getMFInternalSizes()->back();
        editMFInternalSizes()->erase(--editMFInternalSizes()->end());
    }
    else if(getNumParticles() == 0)
    {
        editMFInternalSizes()->clear();
    }
}

void ParticleSystem::removeLifespan(UInt32 Index)
{
    if(getNumLifespans() > 1)
    {
        editInternalLifespans(Index) = getMFInternalLifespans()->back();
        editMFInternalLifespans()->erase(--editMFInternalLifespans()->end());
    }
    else if(getNumParticles() == 0)
    {
        editMFInternalLifespans()->clear();
    }
}

void ParticleSystem::removeAge(UInt32 Index)
{
    if(getNumAges() > 1)
    {
        editInternalAges(Index) = getMFInternalAges()->back();
        editMFInternalAges()->erase(--editMFInternalAges()->end());
    }
    else if(getNumParticles() == 0)
    {
        editMFInternalAges()->clear();
    }
}

void ParticleSystem::removeVelocity(UInt32 Index)
{
    if(getNumVelocities() > 1)
    {
        editInternalVelocities(Index) = getMFInternalVelocities()->back();
        editMFInternalVelocities()->erase(--editMFInternalVelocities()->end());
    }
    else if(getNumParticles() == 0)
    {
        editMFInternalVelocities()->clear();
    }
}

void ParticleSystem::removeSecVelocity(UInt32 Index)
{
    if(getNumSecVelocities() > 1)
    {
        editInternalSecVelocities(Index) = getMFInternalSecVelocities()->back();
        editMFInternalSecVelocities()->erase(--editMFInternalSecVelocities()->end());
    }
    else if(getNumParticles() == 0)
    {
        editMFInternalSecVelocities()->clear();
    }
}

void ParticleSystem::removeAcceleration(UInt32 Index)
{
    if(getNumAccelerations() > 1)
    {
        editInternalAccelerations(Index) = getMFInternalAccelerations()->back();
        editMFInternalAccelerations()->erase(--editMFInternalAccelerations()->end());
    }
    else if(getNumParticles() == 0)
    {
        editMFInternalAccelerations()->clear();
    }
}

void ParticleSystem::removeAttributes(UInt32 Index)
{
    if(getNumAttributes() > 1)
    {
        editInternalAttributes(Index) = getMFInternalAttributes()->back();
        editMFInternalAttributes()->erase(--editMFInternalAttributes()->end());
    }
    else if(getNumParticles() == 0)
    {
        editMFInternalAttributes()->clear();
    }
}

bool ParticleSystem::removeAttribute(const UInt32& Index, const std::string& AttributeKey)
{
	UInt32 removed(0);
	if(getNumAttributes() > Index)
	{
		removed = editInternalAttributes(Index).erase(AttributeKey);
	} else if(getNumAttributes() == 1)
	{
		removed = editInternalAttributes(0).erase(AttributeKey);
	}

	return (removed == 0)?(false):(true);
}

bool ParticleSystem::addParticle(const Pnt3f& Position,
                                 const Pnt3f& SecPosition,
                                 const Vec3f& Normal,
                                 const Color4f& Color,
                                 const Vec3f& Size,
                                 Real32 Lifespan,
                                 Real32 Age,
                                 const Vec3f& Velocity,
                                 const Vec3f& SecVelocity,
                                 const Vec3f& Acceleration,
                                 const StringToUInt32Map& Attributes)
{
    if(getNumParticles() >= getMaxParticles())
    {
        return false;
    }



    //Apply the accumulated velocity and acceleration onto the position
    editMFInternalPositions()->push_back(Position + Velocity*Age + Acceleration*Age*Age);
    editMFInternalIDs()->push_back(_curID++);

    addAndExpandSecPositions(SecPosition);
    addAndExpandNormals(Normal);
    addAndExpandColors(Color);
    addAndExpandSizes(Size);
    addAndExpandLifespans(Lifespan);
    addAndExpandAges(Age);
    //Apply the accumulated acceleration onto the velocity
    addAndExpandVelocities(Velocity + Acceleration*Age);
    addAndExpandSecVelocities(SecVelocity + Acceleration*Age);
    addAndExpandAccelerations(Acceleration);
    addAndExpandAttributes(Attributes);

    //Affect Particles with Affectors
    for(UInt32 j(0) ; j<getMFAffectors()->size(); ++j)
    {
        getAffectors(j)->affect(this, getMFInternalPositions()->size()-1, Age);
    }

    //If not currently updating the whole system, then update the volume
    if(!_isUpdating)
    {
        extendVolumeByParticle(getMFInternalPositions()->size()-1);
    }

    //Increment the Num particles created statistic
    StatIntElem *statElem = StatCollector::getGlobalElem(ParticleSystem::statNParticlesCreated);
    if(statElem)
    {
        statElem->inc();
    }

    produceParticleGenerated(getMFInternalPositions()->size()-1);

    return true;
}

bool ParticleSystem::addParticle(const Pnt3f& Position,
                                 const Vec3f& Normal,
                                 const Color4f& Color,
                                 const Vec3f& Size,
                                 Real32 Lifespan,
                                 const Vec3f& Velocity,
                                 const Vec3f& Acceleration)
{
    StringToUInt32Map EmptyAttributes;

    return addParticle(Position,
                       Position,
                       Normal,
                       Color,
                       Size,
                       Lifespan,
                       0.0f,
                       Velocity,
                       Velocity,
                       Acceleration,
                       EmptyAttributes);
}

bool ParticleSystem::addWorldSpaceParticle(const Pnt3f& Position,
                                           const Vec3f& Normal,
                                           const Color4f& Color,
                                           const Vec3f& Size,
                                           Real32 Lifespan,
                                           const Vec3f& Velocity,
                                           const Vec3f& Acceleration)
{
    StringToUInt32Map EmptyAttributes;

    return addWorldSpaceParticle(Position,
                                 Position,
                                 Normal,
                                 Color,
                                 Size,
                                 Lifespan,
                                 0.0f,
                                 Velocity,
                                 Velocity,
                                 Acceleration,
                                 EmptyAttributes);
}

bool ParticleSystem::addWorldSpaceParticle(const Pnt3f& Position,
                                           const Pnt3f& SecPosition,
                                           const Vec3f& Normal,
                                           const Color4f& Color,
                                           const Vec3f& Size,
                                           Real32 Lifespan,
                                           Real32 Age,
                                           const Vec3f& Velocity,
                                           const Vec3f& SecVelocity,
                                           const Vec3f& Acceleration,
                                           const StringToUInt32Map& Attributes)
{
    Matrix PSBeaconMatrix;

    // behavior for this method is undefined if the beacon is not present
    if(getBeacon() == NULL)
    {	// no beacon, so we can't do anything to convert the particle
        // to local particle system space, except assume it already is.
		SWARNING << "Adding a worldspace particle onto a particle system with no beacon." << std::endl;
    }
	else
	{
		getBeacon()->getToWorld(PSBeaconMatrix);
	}

    if(PSBeaconMatrix.invert())
    {
        Pnt3f NewPosition(PSBeaconMatrix * Position);
        Pnt3f NewSecPosition(PSBeaconMatrix * SecPosition);
        Vec3f NewNormal(PSBeaconMatrix * Normal);
        Vec3f NewVelocity(PSBeaconMatrix * Velocity);
        Vec3f NewSecVelocity(PSBeaconMatrix * SecVelocity);
        Vec3f NewAcceleration(PSBeaconMatrix * Acceleration);

        // tranformation to local particle system space complete
        // so add it to the particle system
        return addParticle(NewPosition,
                           NewSecPosition,
                           NewNormal,
                           Color,
                           Size,
                           Lifespan,
                           Age,
                           NewVelocity,
                           NewSecVelocity,
                           NewAcceleration,
                           Attributes);
    }


    // if this is reached, the inversion of the matrix was unsucessful
    return false;
}

Pnt3f ParticleSystem::getWorldSpacePosition(const UInt32& Index) const
{
	Pnt3f result;
    if(getBeacon() != NULL) 
		getBeacon()->getToWorld().mult(getPosition(Index),result);

	return result; 
}

Pnt3f ParticleSystem::getWorldSpaceSecPosition(const UInt32& Index) const
{
	Pnt3f result;
    if(getBeacon() != NULL) 
		getBeacon()->getToWorld().mult(getSecPosition(Index),result);

	return result; 
}

Vec3f ParticleSystem::getWorldSpacePositionChange(const UInt32& Index) const
{
	return getWorldSpacePosition(Index) - getWorldSpaceSecPosition(Index);
}

Vec3f ParticleSystem::getWorldSpaceNormal(const UInt32& Index) const
{
	Vec3f result;
	if(getBeacon() != NULL) 
		getBeacon()->getToWorld().mult(getNormal(Index),result);

	return result; 
}

Vec3f ParticleSystem::getWorldSpaceVelocity(const UInt32& Index) const
{
	Vec3f result;
	if(getBeacon() != NULL) 
		getBeacon()->getToWorld().mult(getVelocity(Index),result);

	return result; 
}

Vec3f ParticleSystem::getWorldSpaceSecVelocity(const UInt32& Index) const
{
	Vec3f result;
    if(getBeacon() != NULL)
		getBeacon()->getToWorld().mult(getSecVelocity(Index),result);
	return result; 
}

Vec3f ParticleSystem::getWorldSpaceVelocityChange(const UInt32& Index) const
{
	return getWorldSpaceVelocity(Index) - getWorldSpaceSecVelocity(Index);
}

Vec3f ParticleSystem::getWorldSpaceAcceleration(const UInt32& Index) const
{
	Vec3f result;
    if(getBeacon() != NULL) 	
		getBeacon()->getToWorld().mult(getAcceleration(Index),result);

	return result; 
}

Vec3f ParticleSystem::getPositionChange(const UInt32& Index) const
{
    return getPosition(Index) - getSecPosition(Index);
}

Vec3f ParticleSystem::getVelocityChange(const UInt32& Index) const
{
    return getVelocity(Index) - getSecVelocity(Index);
}

const Pnt3f& ParticleSystem::getSecPosition(const UInt32& Index) const
{
    if(Index < getMFInternalSecPositions()->size())
    {
        return getInternalSecPositions(Index);
    }
    else
    {
        return getInternalSecPositions(0);
    }
}

const Vec3f& ParticleSystem::getNormal(const UInt32& Index) const
{
    if(Index < getMFInternalNormals()->size())
    {
        return getInternalNormals(Index);
    }
    else
    {
        return getInternalNormals(0);
    }
}

const Color4f& ParticleSystem::getColor(const UInt32& Index) const
{
    if(Index < getMFInternalColors()->size())
    {
        return getInternalColors(Index);
    }
    else
    {
        return getInternalColors(0);
    }
}

const Vec3f& ParticleSystem::getSize(const UInt32& Index) const
{
    if(Index < getMFInternalSizes()->size())
    {
        return getInternalSizes(Index);
    }
    else
    {
        return getInternalSizes(0);
    }
}

Real32 ParticleSystem::getLifespan(const UInt32& Index) const
{
    if(Index < getMFInternalLifespans()->size())
    {
        return getInternalLifespans(Index);
    }
    else
    {
        return getInternalLifespans(0);
    }
}

Real32 ParticleSystem::getAge(const UInt32& Index) const
{
    if(Index < getMFInternalAges()->size())
    {
        return getInternalAges(Index);
    }
    else
    {
        return getInternalAges(0);
    }
}

const Vec3f& ParticleSystem::getVelocity(const UInt32& Index) const
{
    if(Index < getMFInternalVelocities()->size())
    {
        return getInternalVelocities(Index);
    }
    else
    {
        return getInternalVelocities(0);
    }
}

const Vec3f& ParticleSystem::getSecVelocity(const UInt32& Index) const
{
    if(Index < getMFInternalSecVelocities()->size())
    {
        return getInternalSecVelocities(Index);
    }
    else
    {
        return getInternalSecVelocities(0);
    }
}

const Vec3f& ParticleSystem::getAcceleration(const UInt32& Index) const
{
    if(Index < getMFInternalAccelerations()->size())
    {
        return getInternalAccelerations(Index);
    }
    else
    {
        return getInternalAccelerations(0);
    }
}

const StringToUInt32Map& ParticleSystem::getAttributes(const UInt32& Index) const
{
    if(Index < getMFInternalAttributes()->size())
    {
        return getInternalAttributes(Index);
    }
    else 
    {
        return getInternalAttributes(0);
    }
}

UInt32 ParticleSystem::getAttribute(const UInt32& Index, const std::string& AttributeKey) const
{
	StringToUInt32Map::const_iterator itor, itorEnd;

    if(Index < getMFInternalAttributes()->size())
    {
		itor = getInternalAttributes(Index).find(AttributeKey);
		itorEnd = getInternalAttributes(Index).end();
    }
    else
    {	
		itor = getInternalAttributes(0).find(AttributeKey);
		itorEnd = getInternalAttributes(0).end();
    }

	if(itor != itorEnd)
    {
		return itor->second;
    }
	else
    {
		return 0;
    }
}

void ParticleSystem::setSecPosition(const Pnt3f& SecPosition, const UInt32& Index)
{
    if(getNumSecPositions() > 1)
    {
        editInternalSecPositions(Index) = SecPosition;
    }
    else if(getNumSecPositions() == 1)
    {
        if(getNumParticles() > 1)
        {
            if(getInternalSecPositions(0) != SecPosition)
            {
                //Expand to Positions size-1
                for(UInt32 i(0) ; i<getNumParticles() ; ++i)
                {
                    editMFInternalSecPositions()->push_back(getInternalSecPositions(0));
                }
                editInternalSecPositions(Index) = SecPosition;
            }
        }
        else
        {
            editInternalSecPositions(Index) = SecPosition;
        }
    }
}

void ParticleSystem::setNormal(const Vec3f& Normal, const UInt32& Index)
{
    if(getNumNormals() > 1)
    {
        editInternalNormals(Index) = Normal;
    }
    else if(getNumNormals() == 1)
    {
        if(getNumParticles() > 1)
        {
            if(getInternalNormals(0) != Normal)
            {
                //Expand to Positions size-1
                for(UInt32 i(0) ; i<getNumParticles() ; ++i)
                {
                    editMFInternalNormals()->push_back(getInternalNormals(0));
                }
                editInternalNormals(Index) = Normal;
            }
        }
        else
        {
            editInternalNormals(Index) = Normal;
        }
    }
}
void ParticleSystem::setColor(const Color4f& Color, const UInt32& Index)
{
    if(getNumColors() > 1)
    {
        editInternalColors(Index) = Color;
    }
    else if(getNumColors() == 1)
    {
        if(getNumParticles() > 1)
        {
            if(getInternalColors(0) != Color)
            {
                //Expand to Positions size-1
                for(UInt32 i(0) ; i<getNumParticles() ; ++i)
                {
                    editMFInternalColors()->push_back(getInternalColors(0));
                }
                editInternalColors(Index) = Color;
            }
        }
        else
        {
            editInternalColors(Index) = Color;
        }
    }
}


void ParticleSystem::setSize(const Vec3f& Size, const UInt32& Index)
{
    if(getNumSizes() > 1)
    {
        editInternalSizes(Index) = Size;
    }
    else if(getNumSizes() == 1)
    {
        if(getNumParticles() > 1)
        {
            if(getInternalSizes(0) != Size)
            {
                //Expand to Positions size-1
                for(UInt32 i(0) ; i<getNumParticles() ; ++i)
                {
                    editMFInternalSizes()->push_back(getInternalSizes(0));
                }
                editInternalSizes(Index) = Size;
            }
        }
        else
        {
            editInternalSizes(Index) = Size;
        }
    }
}
void ParticleSystem::setLifespan(const Time& Lifespan, const UInt32& Index)
{
    if(getNumLifespans() > 1)
    {
        editInternalLifespans(Index) = Lifespan;
    }
    else if(getNumLifespans() == 1)
    {
        if(getNumParticles() > 1)
        {
            if(getInternalLifespans(0) != Lifespan)
            {
                //Expand to Positions size-1
                for(UInt32 i(0) ; i<getNumParticles() ; ++i)
                {
                    editMFInternalLifespans()->push_back(getInternalLifespans(0));
                }
                editInternalLifespans(Index) = Lifespan;
            }
        }
        else
        {
            editInternalLifespans(Index) = Lifespan;
        }
    }
}

void ParticleSystem::setAge(const Time& Age, const UInt32& Index)
{
    if(getNumAges() > 1)
    {
        editInternalAges(Index) = Age;
    }
    else if(getNumAges() == 1)
    {
        if(getNumParticles() > 1)
        {
            if(getInternalAges(0) != Age)
            {
                //Expand to Positions size-1
                for(UInt32 i(0) ; i<getNumParticles() ; ++i)
                {
                    editMFInternalAges()->push_back(getInternalAges(0));
                }
                editInternalAges(Index) = Age;
            }
        }
        else
        {
            editInternalAges(Index) = Age;
        }
    }
}

void ParticleSystem::setVelocity(const Vec3f& Velocity, const UInt32& Index)
{
    if(getNumVelocities() > 1)
    {
        editInternalVelocities(Index) = Velocity;
    }
    else if(getNumVelocities() == 1)
    {
        if(getNumParticles() > 1)
        {
            if(getInternalVelocities(0) != Velocity)
            {
                //Expand to Positions size-1
                for(UInt32 i(0) ; i<getNumParticles() ; ++i)
                {
                    editMFInternalVelocities()->push_back(getInternalVelocities(0));
                }
                editInternalVelocities(Index) = Velocity;
            }
        }
        else
        {
            editInternalVelocities(Index) = Velocity;
        }
    }
}

void ParticleSystem::setSecVelocity(const Vec3f& SecVelocity, const UInt32& Index)
{
    if(getNumSecVelocities() > 1)
    {
        editInternalSecVelocities(Index) = SecVelocity;
    }
    else if(getNumSecVelocities() == 1)
    {
        if(getNumParticles() > 1)
        {
            if(getInternalSecVelocities(0) != SecVelocity)
            {
                //Expand to Positions size-1
                for(UInt32 i(0) ; i<getNumParticles() ; ++i)
                {
                    editMFInternalSecVelocities()->push_back(getInternalSecVelocities(0));
                }
                editInternalSecVelocities(Index) = SecVelocity;
            }
        }
        else
        {
            editInternalSecVelocities(Index) = SecVelocity;
        }
    }
}

void ParticleSystem::setAcceleration(const Vec3f& Acceleration, const UInt32& Index)
{
    if(getNumAccelerations() > 1)
    {
        editInternalAccelerations(Index) = Acceleration;
    }
    else if(getNumAccelerations() == 1)
    {
        if(getNumParticles() > 1)
        {
            if(getInternalAccelerations(0) != Acceleration)
            {
                //Expand to Positions size-1
                for(UInt32 i(0) ; i<getNumParticles() ; ++i)
                {
                    editMFInternalAccelerations()->push_back(getInternalAccelerations(0));
                }
                editInternalAccelerations(Index) = Acceleration;
            }
        }
        else
        {
            editInternalAccelerations(Index) = Acceleration;
        }
    }
}

void ParticleSystem::setAttributes(const StringToUInt32Map& Attributes, const UInt32& Index)
{
    if(getNumAttributes() > 1)
    {
        editInternalAttributes(Index) = Attributes;
    }
    else if(getNumAttributes() == 1)
    {
        if(getNumParticles() > 1)
        {
            //if(getInternalAttributes(0) != Attributes)
            //{
            //Expand to Positions size-1
            for(UInt32 i(0) ; i<getNumParticles() ; ++i)
            {
                editMFInternalAttributes()->push_back(getInternalAttributes(0));
            }
            editInternalAttributes(Index) = Attributes;
            //}
        }
        else
        {
            editInternalAttributes(Index) = Attributes;
        }
    }
}

void ParticleSystem::setAttribute(const std::string& AttributeKey, UInt32 AttributeValue, const UInt32& Index)
{
    if(getNumAttributes() > 1)
    {
        editInternalAttributes(Index)[AttributeKey] = AttributeValue;
    }
    else if(getNumAttributes() == 1)
    {
        if(getNumParticles() > 1)
        {
            if(editInternalAttributes(0)[AttributeKey] != AttributeValue)
            {
                //Expand to Positions size-1
                for(UInt32 i(0) ; i<getNumParticles() ; ++i)
                {
                    editMFInternalAttributes()->push_back(getInternalAttributes(0));
                }
                editInternalAttributes(Index)[AttributeKey] = AttributeValue;
            }
        }
        else
        {
            editInternalAttributes(Index)[AttributeKey] = AttributeValue;
        }
    }
}

void ParticleSystem::internalKillParticles()
{
    if(!_isUpdating)
    {
        //Kill Particles
        for(std::set<UInt32, GreaterThanUInt32>::iterator Itor(_ParticlesToKill.begin()) ; Itor != _ParticlesToKill.end() ; ++Itor)
        {
            killParticle(*Itor);
        }
        _ParticlesToKill.clear();
    }
}

void ParticleSystem::extendVolumeByParticle(UInt32 ParticleIndex)
{
    UInt32 NumParticles(getNumParticles());
    BoxVolume NewVolume(getVolume());

    NewVolume.extendBy(getPosition(ParticleIndex));
    Vec3f NewMaxSize(osgMax(getMaxParticleSize().x(),getSize(ParticleIndex).x()),
                     osgMax(getMaxParticleSize().y(),getSize(ParticleIndex).y()),
                     osgMax(getMaxParticleSize().z(),getSize(ParticleIndex).z())
                    );

    if(NumParticles > 0)
    {
        if(getVolume() != NewVolume || NewMaxSize != getMaxParticleSize())
        {
            setVolume(NewVolume);
            setMaxParticleSize(NewMaxSize);
        }
    }
}

void ParticleSystem::updateVolume(void)
{
    UInt32 NumParticles(getNumParticles());

    BoxVolume NewVolume;
    Vec3f NewMaxSize(0.0f,0.0f,0.0f);

    for(UInt32 i(0) ; i<NumParticles ; ++i)
    {
        NewVolume.extendBy(getPosition(i));
        NewMaxSize.setValues(osgMax(NewMaxSize.x(),getSize(i).x()),
                             osgMax(NewMaxSize.y(),getSize(i).y()),
                             osgMax(NewMaxSize.z(),getSize(i).z())
                            );
    }

    if(NumParticles > 0)
    {
        if(getVolume() != NewVolume || NewMaxSize != getMaxParticleSize())
        {
            setVolume(NewVolume);
            setMaxParticleSize(NewMaxSize);
        }
    }
}

void ParticleSystem::update(const Time& elps)
{
    //If the Update Time statistic is being tracked then start the timer
    StatTimeElem *UpdateTimeStatElem = StatCollector::getGlobalElem(statParticleUpdateTime);
    if(UpdateTimeStatElem)
    {
        UpdateTimeStatElem->start();
    }

    BoxVolume PrevVolume(getVolume());

    _isUpdating = true;

    UInt32 NumParticles(getNumParticles());

    BoxVolume NewVolume;
    Vec3f NewMaxSize(0.0f,0.0f,0.0f);

    bool AdvanceIterator(true);

    //Loop through all of the particles
    for(UInt32 i(0) ; i<NumParticles; ++i)
    {
        //Kill Particles that have ages > lifespans
        setAge(getAge(i) + elps,i);
        if(getLifespan(i) > 0.0f && getAge(i)>getLifespan(i))
        {
            killParticle(i);
            continue;
        }


        if(getUpdateSecAttribs())
        {
            //Remember the Old Postions and velocities
            setSecPosition(getPosition(i),i);
            setSecVelocity(getVelocity(i),i);
        }


        //Apply Acceleration and Velocity
        setPosition(getPosition(i) + getVelocity(i)*elps + getAcceleration(i)*elps*elps, i);


        //Clear Velocities
        if(getClearVelocities())
        {
            setVelocity(Vec3f(0.0f,0.0f,0.0f),i);
        }

        setVelocity(getVelocity(i) + getAcceleration(i)*elps,i);


        //Clear Accelerations
        if(getClearAccelerations())
        {
            setAcceleration(Vec3f(0.0f,0.0f,0.0f),i);
        }

        //Affect Particles with Affectors
        for(UInt32 j(0) ; j<getMFAffectors()->size(); ++j)
        {
            if(getAffectors(j)->getActive() &&
               getAffectors(j)->affect(this, i, elps))
            {
                killParticle(i);
                continue;
            }

        }

        NewVolume.extendBy(getPosition(i));
        NewMaxSize.setValues(osgMax(NewMaxSize.x(),getSize(i).x()),
                             osgMax(NewMaxSize.y(),getSize(i).y()),
                             osgMax(NewMaxSize.z(),getSize(i).z())
                            );
    }

    //Generate Particles with Generators
    UInt32 NumGenerators(getMFGenerators()->size());
    for(UInt32 j(0) ; j<NumGenerators; )
    {
        if(getGenerators(j)->getActive() &&
           getGenerators(j)->generate(this, elps))
        {
            removeFromGenerators(j); 
            --NumGenerators;
        }
        else
        {
            ++j;
        }
    }
    //Update the Generated Particles by there age

    //Affect Particles with System Affectors
    for(UInt32 j(0) ; j<getMFSystemAffectors()->size(); ++j)
    {
        if(getSystemAffectors(j)->getActive())
        {
            getSystemAffectors(j)->affect(this, elps);
        }
    }

    _isUpdating = false;
    internalKillParticles();

    if(NumParticles > 0)
    {
        if(getVolume() != NewVolume || NewMaxSize != getMaxParticleSize())
        {
            setVolume(NewVolume);
            setMaxParticleSize(NewMaxSize);
        }
    }

    //If the Update Time statistic is being tracked then stop the timer
    if(UpdateTimeStatElem)
    {
        UpdateTimeStatElem->stop();
    }

    produceSystemUpdated();
}

void ParticleSystem::produceParticleGenerated(Int32 Index)
{
    if(numSlotsParticleGenerated() > 0)
    {
        ParticleEventDetailsUnrecPtr Details = ParticleEventDetails::create(this, 
                                                                      getSystemTime(),
                                                                      Index,
                                                                      getPosition(Index),
                                                                      getSecPosition(Index),
                                                                      getNormal(Index),
                                                                      getColor(Index),
                                                                      getSize(Index),
                                                                      getLifespan(Index),
                                                                      getAge(Index),
                                                                      getVelocity(Index),
                                                                      getSecVelocity(Index),
                                                                      getAcceleration(Index),
                                                                      getAttributes(Index),
                                                                      getID(Index));
       
        Inherited::produceParticleGenerated(Details);
    }
}

void ParticleSystem::produceParticleKilled(Int32 Index,
                                           const Pnt3f& Position,
                                           const Pnt3f& SecPosition,
                                           const Vec3f& Normal,
                                           const Color4f& Color,
                                           const Vec3f& Size,
                                           Real32 Lifespan,
                                           Real32 Age,
                                           const Vec3f& Velocity,
                                           const Vec3f& SecVelocity,
                                           const Vec3f& Acceleration,
                                           const StringToUInt32Map& Attributes,
                                           UInt32& ID)
{
    ParticleEventDetailsUnrecPtr Details = ParticleEventDetails::create(this, getSystemTime(), Index, Position, SecPosition, Normal, Color, Size, Lifespan, Age, Velocity, SecVelocity, Acceleration, Attributes,ID);
   
    Inherited::produceParticleKilled(Details);
}

void ParticleSystem::produceParticleStolen(Int32 Index,
                                           const Pnt3f& Position,
                                           const Pnt3f& SecPosition,
                                           const Vec3f& Normal,
                                           const Color4f& Color,
                                           const Vec3f& Size,
                                           Real32 Lifespan,
                                           Real32 Age,
                                           const Vec3f& Velocity,
                                           const Vec3f& SecVelocity,
                                           const Vec3f& Acceleration,
                                           const StringToUInt32Map& Attributes,
                                           UInt32& ID)
{
    ParticleEventDetailsUnrecPtr Details = ParticleEventDetails::create(this, getSystemTime(), Index, Position, SecPosition, Normal, Color, Size, Lifespan, Age, Velocity, SecVelocity, Acceleration, Attributes,ID);
   
    Inherited::produceParticleStolen(Details);
}

void ParticleSystem::produceSystemUpdated()
{
    ParticleSystemEventDetailsUnrecPtr Details = ParticleSystemEventDetails::create(this, getSystemTime());
   
    Inherited::produceSystemUpdated(Details);
}

void ParticleSystem::produceVolumeChanged()
{
    ParticleSystemEventDetailsUnrecPtr Details = ParticleSystemEventDetails::create(this, getSystemTime());
   
    Inherited::produceVolumeChanged(Details);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ParticleSystem::ParticleSystem(void) :
    Inherited(),
    _isUpdating(false),
	_curID(0)
{
}

ParticleSystem::ParticleSystem(const ParticleSystem &source) :
    Inherited(source),
    _isUpdating(false),
	_curID(source._curID)
{
}

ParticleSystem::~ParticleSystem(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ParticleSystem::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & VolumeFieldMask)
    {
        //Fire a Volume Change Event
        produceVolumeChanged();
    }

    if(whichField & InternalPositionsFieldMask)
    {

        if(getNumParticles() > 0)
        {
            if(getMFInternalSecPositions()->size() == 0)
            {
                addAndExpandSecPositions(Pnt3f(0.0f,0.0f,0.0f));
            }
            
            if(getMFInternalNormals()->size() == 0)
            {
                addAndExpandNormals(Vec3f(0.0f,0.0f,1.0f));
            }
            
            if(getMFInternalColors()->size() == 0)
            {
                addAndExpandColors(Color4f(1.0f,1.0f,1.0f,1.0f));
            }
            
            if(getMFInternalSizes()->size() == 0)
            {
                addAndExpandSizes(Vec3f(1.0f,1.0f,1.0f));
            }
            
            if(getMFInternalLifespans()->size() == 0)
            {
                addAndExpandLifespans(-1.0f);
            }
            
            if(getMFInternalAges()->size() == 0)
            {
                addAndExpandAges(0.0f);
            }
            if(getMFInternalVelocities()->size() == 0)
            {
                addAndExpandVelocities(Vec3f(0.0f,0.0f,0.0f));
            }
            if(getMFInternalSecVelocities()->size() == 0)
            {
                addAndExpandSecVelocities(Vec3f(0.0f,0.0f,0.0f));
            }
            if(getMFInternalAccelerations()->size() == 0)
            {
                addAndExpandAccelerations(Vec3f(0.0f,0.0f,0.0f));
            }

            if(getMFInternalAttributes()->size() == 0)
            {
                addAndExpandAttributes(StringToUInt32Map());
            }
        }
        else
        {
        }
    }

}

void ParticleSystem::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ParticleSystem NI" << std::endl;
}

ParticleSystem::ParticlePositionSort::ParticlePositionSort(const ParticleSystem* System, const Pnt3f& Pos) : _System(System), _Pos(Pos)
{
}

bool ParticleSystem::ParticlePositionSort::operator()(const UInt32& Left, const UInt32& Right)
{
    return _System->getPosition(Left).dist2(_Pos) < _System->getPosition(Right).dist2(_Pos);
}

OSG_END_NAMESPACE
