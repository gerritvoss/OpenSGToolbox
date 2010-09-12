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

#ifndef _OSGPARTICLESYSTEM_H_
#define _OSGPARTICLESYSTEM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGNode.h"

#include "OSGParticleSystemBase.h"
#include "OSGStatElemTypes.h"

#include "OSGLine.h"
#include <set>

OSG_BEGIN_NAMESPACE

/*! \brief ParticleSystem class. See \ref
  PageContribParticleSystemParticleSystem for a description.
  */

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING ParticleSystem : public ParticleSystemBase
{
  protected:
	friend class CollisionParticleSystemAffector;

    struct GreaterThanUInt32
    {
        bool operator()(const UInt32 s1, const UInt32 s2) const;
    };

    /*==========================  PUBLIC  =================================*/

  public:
    static const OSG::BitVector InternalParticlesFieldMask;

    typedef ParticleSystemBase Inherited;
    typedef ParticleSystem     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                            const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    UInt32 getNumParticles(void) const;
    const Pnt3f& getPosition(const UInt32& Index) const;
    const Pnt3f& getSecPosition(const UInt32& Index) const;
    Vec3f getPositionChange(const UInt32& Index) const;
    const Vec3f& getNormal(const UInt32& Index) const;
    const Color4f& getColor(const UInt32& Index) const;
    const Vec3f& getSize(const UInt32& Index) const;
    Real32 getLifespan(const UInt32& Index) const;
    Real32 getAge(const UInt32& Index) const;
    const Vec3f& getVelocity(const UInt32& Index) const;
    const Vec3f& getSecVelocity(const UInt32& Index) const;
    Vec3f getVelocityChange(const UInt32& Index) const;
    const Vec3f& getAcceleration(const UInt32& Index) const;
    UInt32 getAttribute(const UInt32& Index, const std::string& AttributeKey) const;
	UInt32 getID(const UInt32& Index) const;
    const StringToUInt32Map& getAttributes(const UInt32& Index) const;
	Int64 getIndex(UInt32 ParticleID) const;

	Pnt3f getWorldSpacePosition(const UInt32& Index) const;
	Pnt3f getWorldSpaceSecPosition(const UInt32& Index) const;
	Vec3f getWorldSpacePositionChange(const UInt32& Index) const;
	Vec3f getWorldSpaceNormal(const UInt32& Index) const;
	Vec3f getWorldSpaceVelocity(const UInt32& Index) const;
	Vec3f getWorldSpaceSecVelocity(const UInt32& Index) const;
	Vec3f getWorldSpaceVelocityChange(const UInt32& Index) const;
	Vec3f getWorldSpaceAcceleration(const UInt32& Index) const;

    void setPosition(const Pnt3f& Pos, const UInt32& Index);
    void setSecPosition(const Pnt3f& SecPosition, const UInt32& Index);
    void setNormal(const Vec3f& Normal, const UInt32& Index);
    void setColor(const Color4f& Color, const UInt32& Index);
    void setSize(const Vec3f& Size, const UInt32& Index);
    void setLifespan(const Time& Lifespan, const UInt32& Index);
    void setAge(const Time& Age, const UInt32& Index);
    void setVelocity(const Vec3f& Velocity, const UInt32& Index);
    void setSecVelocity(const Vec3f& SecVelocity, const UInt32& Index);
    void setAcceleration(const Vec3f& Acceleration, const UInt32& Index);
    void setAttribute(const std::string& AttributeKey, UInt32 AttributeValue, const UInt32& Index);
    void setAttributes(const StringToUInt32Map& Attributes, const UInt32& Index);
	bool removeAttribute(const UInt32& Index, const std::string& AttributeKey);


    UInt32 getNumSecPositions(void) const;
    UInt32 getNumNormals(void) const;
    UInt32 getNumColors(void) const;
    UInt32 getNumSizes(void) const;
    UInt32 getNumLifespans(void) const;
    UInt32 getNumAges(void) const;
    UInt32 getNumVelocities(void) const;
    UInt32 getNumSecVelocities(void) const;
    UInt32 getNumAccelerations(void) const;
    UInt32 getNumAttributes(void) const;

    bool addParticle(const Pnt3f& Position,
                     const Pnt3f& SecPosition,
                     const Vec3f& Normal,
                     const Color4f& Color,
                     const Vec3f& Size,
                     Real32 Lifespan,
                     Real32 Age,
                     const Vec3f& Velocity,
                     const Vec3f& SecVelocity,
                     const Vec3f& Acceleration,
                     const StringToUInt32Map& Attributes);

    bool addParticle(const Pnt3f& Position,
                     const Vec3f& Normal,
                     const Color4f& Color,
                     const Vec3f& Size,
                     Real32 Lifespan,
                     const Vec3f& Velocity,
                     const Vec3f& Acceleration);

    bool addWorldSpaceParticle(const Pnt3f& Position,
                               const Vec3f& Normal,
                               const Color4f& Color,
                               const Vec3f& Size,
                               Real32 Lifespan,
                               const Vec3f& Velocity,
                               const Vec3f& Acceleration);

    bool addWorldSpaceParticle(const Pnt3f& Position,
                               const Pnt3f& SecPosition,
                               const Vec3f& Normal,
                               const Color4f& Color,
                               const Vec3f& Size,
                               Real32 Lifespan,
                               Real32 Age,
                               const Vec3f& Velocity,
                               const Vec3f& SecVelocity,
                               const Vec3f& Acceleration,
                               const StringToUInt32Map& Attributes);



    bool killParticle(UInt32 Index, bool KillNextUpdate = false);
	bool killParticleByID(UInt32 ID, bool KillNextUpdate = false);

    void updateVolume(void);

    void attachUpdateProducer(ReflexiveContainer* const producer);
    void detachUpdateProducer(void);

    static StatElemDesc<StatIntElem    > statNParticles;
    static StatElemDesc<StatIntElem    > statNParticlesCreated;
    static StatElemDesc<StatIntElem    > statNParticlesKilled;
    static StatElemDesc<StatTimeElem    > statParticleUpdateTime;
    static StatElemDesc<StatTimeElem    > statParticleSortTime;


    std::vector<UInt32> intersect(const Line& Ray, Real32 MinDistFromRay, Real32 MinDistFromRayOrigin, bool sort = false, NodeRefPtr Beacon = NULL) const;
    std::vector<UInt32> intersect(const Pnt3f& p1, const Pnt3f& p2, Real32 IntersectionDistance, NodeRefPtr Beacon = NULL) const;
    std::vector<UInt32> intersect(const Volume& Vol, Real32 IntersectionDistance, NodeRefPtr Beacon = NULL) const;
    std::vector<UInt32> intersect(const NodeRefPtr CollisionNode, bool sort = false, NodeRefPtr Beacon = NULL) const;

    class ParticlePositionSort
    {
      public:
        ParticlePositionSort(const ParticleSystem* System, const Pnt3f& Pos);


        bool operator()(const UInt32& Left, const UInt32& Right);
      protected:
        const ParticleSystem* _System;
        Pnt3f _Pos;
    };

    bool isUpdating(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ParticleSystemBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ParticleSystem(void);
    ParticleSystem(const ParticleSystem &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ParticleSystem(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    void produceSystemUpdated(void);
    void produceVolumeChanged(void);
    void produceParticleGenerated(Int32 Index);

    void produceParticleKilled(Int32 Index,
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
                               UInt32& ID);

    void produceParticleStolen(
                               Int32 Index,
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
                               UInt32& ID);

    void attachedUpdate(EventDetails* const details);

    virtual void update(const Time& elps);

    void addAndExpandSecPositions(const Pnt3f& SecPosition);
    void addAndExpandNormals(const Vec3f& Normal);
    void addAndExpandColors(const Color4f& Color);
    void addAndExpandSizes(const Vec3f& Size);
    void addAndExpandLifespans(Real32 Lifespan);
    void addAndExpandAges(Real32 Age);
    void addAndExpandVelocities(const Vec3f& Velocity);
    void addAndExpandSecVelocities(const Vec3f& SecVelocity);
    void addAndExpandAccelerations(const Vec3f& Acceleration);
    void addAndExpandAttributes(const StringToUInt32Map& AttributeMap);

    void removePosition(UInt32 Index);
    void removeSecPosition(UInt32 Index);
    void removeNormal(UInt32 Index);
    void removeColor(UInt32 Index);
    void removeSize(UInt32 Index);
    void removeLifespan(UInt32 Index);
    void removeAge(UInt32 Index);
    void removeVelocity(UInt32 Index);
    void removeSecVelocity(UInt32 Index);
    void removeAcceleration(UInt32 Index);
    void removeAttributes(UInt32 Index);
	void removeID(UInt32 Index);

    bool internalKillParticle(UInt32 Index);
    void internalKillParticles();

    bool _isUpdating;
    std::set<UInt32, GreaterThanUInt32> _ParticlesToKill;
    boost::signals2::connection _UpdateEventConnection;

	UInt32 _curID;

    void extendVolumeByParticle(UInt32 ParticleIndex);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ParticleSystemBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ParticleSystem &source);
};

typedef ParticleSystem *ParticleSystemP;

OSG_END_NAMESPACE

#include "OSGParticleGenerator.h"
#include "OSGParticleAffector.h"
#include "OSGParticleSystemAffector.h"
#include "OSGParticleEventDetails.h"
#include "OSGParticleSystemEventDetails.h"

#include "OSGParticleSystemBase.inl"
#include "OSGParticleSystem.inl"

#endif /* _OSGPARTICLESYSTEM_H_ */
