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

#ifndef _OSGPARTICLESYSTEMPARTICLETRAILGENERATOR_H_
#define _OSGPARTICLESYSTEMPARTICLETRAILGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGParticleSystemParticleTrailGeneratorBase.h"
#include "OSGMaterial.h"
#include "OSGParticleSystemDrawer.h" 
#include "OSGDistribution1D.h"
#include "OSGDistribution3D.h"

OSG_BEGIN_NAMESPACE

/*! \brief ParticleSystemParticleTrailGenerator class. See \ref
           PageContribParticleTrailParticleSystemParticleTrailGenerator for a description.
*/

class OSG_CONTRIBPARTICLETRAIL_DLLMAPPING ParticleSystemParticleTrailGenerator : public ParticleSystemParticleTrailGeneratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    //Enum defining the source form which to generaate trail particles' velocity
    enum TrailVelocitySource
    {
        DISTRIBUTION,		// velocity generated from the VelocityDistribution field
        PARENT_PARTICLE,	// velocity from the parent particle used (the particle this trail is generated form)
        BLEND,				// The average between DISTRIBUTION and PARENT_PARTICLE is used
        NONE
    };			    // velocity of trail particles will be 0

    typedef ParticleSystemParticleTrailGeneratorBase Inherited;
    typedef ParticleSystemParticleTrailGenerator     Self;

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

	// virt. functions from parent class
	virtual void internalUpdate(ParticleSystemEventDetails* const details);
	virtual void internalKill(ParticleEventDetails* const details);
	virtual void internalGenerated(ParticleEventDetails* const details);
	virtual void internalTrailSectGenerated(const TrailSection& ts,const Vec3f& ppVel);
	virtual void internalTrailSectKilled(const TrailSection& ts);


	void setTrailDrawer(ParticleSystemDrawer* const drawer);
	
	Material* getTrailMaterial(void) const;
	void setTrailMaterial(Material* const newMaterial);

    void attachUpdateProducer(ReflexiveContainer* const producer);
    void detachUpdateProducer(void);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ParticleSystemParticleTrailGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ParticleSystemParticleTrailGenerator(void);
    ParticleSystemParticleTrailGenerator(const ParticleSystemParticleTrailGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ParticleSystemParticleTrailGenerator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	void onCreate(const ParticleTrailGenerator *Id = NULL);
	void onDestroy();

    std::map<UInt32,UInt32> _mTrailIDtoParticleIDMap;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ParticleSystemParticleTrailGeneratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ParticleSystemParticleTrailGenerator &source);
};

typedef ParticleSystemParticleTrailGenerator *ParticleSystemParticleTrailGeneratorP;

OSG_END_NAMESPACE

#include "OSGParticleSystemParticleTrailGeneratorBase.inl"
#include "OSGParticleSystemParticleTrailGenerator.inl"

#endif /* _OSGPARTICLESYSTEMPARTICLETRAILGENERATOR_H_ */
