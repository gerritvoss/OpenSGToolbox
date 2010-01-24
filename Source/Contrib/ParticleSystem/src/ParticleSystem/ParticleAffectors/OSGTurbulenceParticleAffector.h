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

#ifndef _OSGTURBULENCEPARTICLEAFFECTOR_H_
#define _OSGTURBULENCEPARTICLEAFFECTOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTurbulenceParticleAffectorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief TurbulenceParticleAffector class. See \ref
           PageContribParticleSystemTurbulenceParticleAffector for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING TurbulenceParticleAffector : public TurbulenceParticleAffectorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TurbulenceParticleAffectorBase Inherited;
    typedef TurbulenceParticleAffector     Self;

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

    // Variables should all be in TurbulenceParticleAffectorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TurbulenceParticleAffector(void);
    TurbulenceParticleAffector(const TurbulenceParticleAffector &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TurbulenceParticleAffector(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

	void onCreate(const TurbulenceParticleAffector *Id = NULL);
	void onDestroy();

    /*! \}                                                                 */

	bool distributionIsNotInitialized(void);

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TurbulenceParticleAffectorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TurbulenceParticleAffector &source);
};

typedef TurbulenceParticleAffector *TurbulenceParticleAffectorP;

OSG_END_NAMESPACE

#include "OSGTurbulenceParticleAffectorBase.inl"
#include "OSGTurbulenceParticleAffector.inl"

#endif /* _OSGTURBULENCEPARTICLEAFFECTOR_H_ */
