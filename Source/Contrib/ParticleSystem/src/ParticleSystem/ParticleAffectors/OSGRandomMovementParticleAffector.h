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

#ifndef _OSGRANDOMMOVEMENTPARTICLEAFFECTOR_H_
#define _OSGRANDOMMOVEMENTPARTICLEAFFECTOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGRandomMovementParticleAffectorBase.h"
#include "OSGPerlinNoiseDistribution1D.h"

OSG_BEGIN_NAMESPACE

/*! \brief RandomMovementParticleAffector class. See \ref
           PageContribParticleSystemRandomMovementParticleAffector for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING RandomMovementParticleAffector : public RandomMovementParticleAffectorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum ParticleAttributes
    {
        POSITION_ATTRIBUTE = 0,
        VELOCITY_ATTRIBUTE = 1
    };

    typedef RandomMovementParticleAffectorBase Inherited;
    typedef RandomMovementParticleAffector     Self;

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

	virtual bool affect(ParticleSystemRefPtr System, Int32 ParticleIndex, const Time& elps);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in RandomMovementParticleAffectorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    RandomMovementParticleAffector(void);
    RandomMovementParticleAffector(const RandomMovementParticleAffector &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~RandomMovementParticleAffector(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    void onCreate(const RandomMovementParticleAffector *source = NULL);
    void onDestroy(void);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class RandomMovementParticleAffectorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const RandomMovementParticleAffector &source);
};

typedef RandomMovementParticleAffector *RandomMovementParticleAffectorP;

OSG_END_NAMESPACE

#include "OSGRandomMovementParticleAffectorBase.inl"
#include "OSGRandomMovementParticleAffector.inl"

#endif /* _OSGRANDOMMOVEMENTPARTICLEAFFECTOR_H_ */
