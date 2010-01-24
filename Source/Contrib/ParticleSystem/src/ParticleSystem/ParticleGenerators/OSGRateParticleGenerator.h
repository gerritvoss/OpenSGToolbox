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

#ifndef _OSGRATEPARTICLEGENERATOR_H_
#define _OSGRATEPARTICLEGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGRateParticleGeneratorBase.h"
#include "OSGDistribution3D.h"
#include "OSGDistribution2D.h"
#include "OSGDistribution1D.h"
#include <boost/random/normal_distribution.hpp>

OSG_BEGIN_NAMESPACE

/*! \brief RateParticleGenerator class. See \ref
           PageContribParticleSystemRateParticleGenerator for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING RateParticleGenerator : public RateParticleGeneratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef RateParticleGeneratorBase Inherited;
    typedef RateParticleGenerator     Self;

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

    virtual bool generate(ParticleSystemRefPtr System, const Time& elps);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in RateParticleGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    RateParticleGenerator(void);
    RateParticleGenerator(const RateParticleGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~RateParticleGenerator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class RateParticleGeneratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const RateParticleGenerator &source);

	bool _IsRateZero;
    boost::normal_distribution<Real32> _NormalDistribution;
};

typedef RateParticleGenerator *RateParticleGeneratorP;

OSG_END_NAMESPACE

#include "OSGRateParticleGeneratorBase.inl"
#include "OSGRateParticleGenerator.inl"

#endif /* _OSGRATEPARTICLEGENERATOR_H_ */
