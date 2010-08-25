/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com), Daniel Guilliams           *
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

#ifndef _OSGPARTICLETRAILGENERATOR_H_
#define _OSGPARTICLETRAILGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGParticleTrailGeneratorBase.h"
#include "OSGParticleSystem.h"
#include "OSGVector.h"
#include <deque>

OSG_BEGIN_NAMESPACE

/*! \brief ParticleTrailGenerator class. See \ref
           PageContribParticleTrailParticleTrailGenerator for a description.
*/

class OSG_CONTRIBPARTICLETRAIL_DLLMAPPING ParticleTrailGenerator : public ParticleTrailGeneratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum LengthMethod
    {
        TIME       = 0,
        NUM_POINTS = 1
    };

    enum ResolutionMethod
    {
        TIME_SPACING     = 0, 
        DISTANCE_SPACING = 1, 
        SIMPLE_SPACING   = 2
    };

    typedef ParticleTrailGeneratorBase Inherited;
    typedef ParticleTrailGenerator     Self;

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
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ParticleTrailGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ParticleTrailGenerator(void);
    ParticleTrailGenerator(const ParticleTrailGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ParticleTrailGenerator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	// internal listener class for managing trail data
	void handleSystemUpdated(ParticleSystemEventDetails* const details);
	void handleParticleGenerated(ParticleEventDetails* const details);
	void handleParticleRemoved(ParticleEventDetails* const details);
    
    boost::signals2::connection _SystemUpdatedConnection;
    boost::signals2::connection _ParticleGeneratedConnection;
    boost::signals2::connection _ParticleKilledConnection;
    boost::signals2::connection _ParticleStolenConnection;

    // holds data for one point of a trail
    struct TrailSection
    {
      public:
        Pnt3f pos;
        Time time;
        UInt32 ID;
    };

    typedef std::deque<TrailSection> ParticleTrail;
    typedef std::map<UInt32,ParticleTrail> ParticleTrailMap;
    typedef std::map<UInt32,ParticleTrail>::iterator PTMItor;
    // the trails themselves
    ParticleTrailMap _mTrails;
    // we still want particles to have trails after they are killed,
    // hence the second vector of trials
    ParticleTrailMap _mKilledParticleTrails;

    virtual void internalUpdate(ParticleSystemEventDetails* const details) = 0;
    virtual void internalKill(ParticleEventDetails* const details) = 0;
    virtual void internalGenerated(ParticleEventDetails* const details) = 0;
    virtual void internalTrailSectGenerated(const TrailSection& ts, const Vec3f& ppVel) = 0;
    virtual void internalTrailSectKilled(const TrailSection& ts) = 0;

    UInt32 _mTrailSectIDCntr;
    UInt32 getNextTSID(void);
    Time _mLastAdded;
    bool _mInitialized;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ParticleTrailGeneratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ParticleTrailGenerator &source);
};

typedef ParticleTrailGenerator *ParticleTrailGeneratorP;

OSG_END_NAMESPACE

#include "OSGParticleTrailGeneratorBase.inl"
#include "OSGParticleTrailGenerator.inl"

#endif /* _OSGPARTICLETRAILGENERATOR_H_ */
