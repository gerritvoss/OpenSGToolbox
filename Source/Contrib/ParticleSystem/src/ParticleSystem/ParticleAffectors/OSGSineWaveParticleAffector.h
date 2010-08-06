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

#ifndef _OSGSINEWAVEPARTICLEAFFECTOR_H_
#define _OSGSINEWAVEPARTICLEAFFECTOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSineWaveParticleAffectorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief SineWaveParticleAffector class. See \ref
           PageContribParticleSystemSineWaveParticleAffector for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING SineWaveParticleAffector : public SineWaveParticleAffectorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
	enum DisplacementDir
    {
        X_AXIS        = 0,
        Y_AXIS        = 1,
        Z_AXIS        = 2,
        NORMAL        = 3,
        CROSS_PRODUCT = 4
    };

    typedef SineWaveParticleAffectorBase Inherited;
    typedef SineWaveParticleAffector     Self;

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

	virtual bool affect(ParticleSystemRecPtr System, Int32 ParticleIndex, const Time& elps);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SineWaveParticleAffectorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SineWaveParticleAffector(void);
    SineWaveParticleAffector(const SineWaveParticleAffector &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SineWaveParticleAffector(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SineWaveParticleAffectorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SineWaveParticleAffector &source);
};

typedef SineWaveParticleAffector *SineWaveParticleAffectorP;

OSG_END_NAMESPACE

#include "OSGSineWaveParticleAffectorBase.inl"
#include "OSGSineWaveParticleAffector.inl"

#endif /* _OSGSINEWAVEPARTICLEAFFECTOR_H_ */
