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

#ifndef _OSGSIMPLEPARTICLETRAILGENERATOR_H_
#define _OSGSIMPLEPARTICLETRAILGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSimpleParticleTrailGeneratorBase.h"
#include "OSGMaterial.h"

OSG_BEGIN_NAMESPACE

/*! \brief SimpleParticleTrailGenerator class. See \ref
           PageContribParticleTrailSimpleParticleTrailGenerator for a description.
*/

class OSG_CONTRIBPARTICLETRAIL_DLLMAPPING SimpleParticleTrailGenerator : public SimpleParticleTrailGeneratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum DrawType
    {
        POINTS = 0,
        LINES = 1
    };

    typedef SimpleParticleTrailGeneratorBase Inherited;
    typedef SimpleParticleTrailGenerator     Self;

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
	  // helper functions to set material used
	  Material* getTrailMaterial(void) const;
	  void setTrailMaterial(Material* const trailMaterial);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SimpleParticleTrailGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SimpleParticleTrailGenerator(void);
    SimpleParticleTrailGenerator(const SimpleParticleTrailGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SimpleParticleTrailGenerator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	void onCreate(const SimpleParticleTrailGenerator *Id = NULL);
	void onDestroy();

	virtual void internalUpdate(ParticleSystemEventDetails* const details);
	virtual void internalKill(ParticleEventDetails* const details);
	virtual void internalGenerated(ParticleEventDetails* const details);
	virtual void internalTrailSectGenerated(const TrailSection& ts, const Vec3f& ppVel);
	virtual void internalTrailSectKilled(const TrailSection& ts);

	bool updateNeeded;
	void updatePoints(void);
	void updateLines(void);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SimpleParticleTrailGeneratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SimpleParticleTrailGenerator &source);
};

typedef SimpleParticleTrailGenerator *SimpleParticleTrailGeneratorP;

OSG_END_NAMESPACE

#include "OSGSimpleParticleTrailGeneratorBase.inl"
#include "OSGSimpleParticleTrailGenerator.inl"

#endif /* _OSGSIMPLEPARTICLETRAILGENERATOR_H_ */
