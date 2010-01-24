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

#ifndef _OSGCOLLECTIVEGRAVITYPARTICLESYSTEMAFFECTOR_H_
#define _OSGCOLLECTIVEGRAVITYPARTICLESYSTEMAFFECTOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGCollectiveGravityParticleSystemAffectorBase.h"
#include "OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

/*! \brief CollectiveGravityParticleSystemAffector class. See \ref
           PageContribParticleSystemCollectiveGravityParticleSystemAffector for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING CollectiveGravityParticleSystemAffector : public CollectiveGravityParticleSystemAffectorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum MassSource {MASS_STATIC=0, MASS_SIZE_X=1, MASS_SIZE_Y=2, MASS_SIZE_Z=3};

    typedef CollectiveGravityParticleSystemAffectorBase Inherited;
    typedef CollectiveGravityParticleSystemAffector     Self;

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

    virtual void affect(ParticleSystemRefPtr System, const Time& elps);
    
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in CollectiveGravityParticleSystemAffectorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CollectiveGravityParticleSystemAffector(void);
    CollectiveGravityParticleSystemAffector(const CollectiveGravityParticleSystemAffector &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CollectiveGravityParticleSystemAffector(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CollectiveGravityParticleSystemAffectorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CollectiveGravityParticleSystemAffector &source);
};

typedef CollectiveGravityParticleSystemAffector *CollectiveGravityParticleSystemAffectorP;

OSG_END_NAMESPACE

#include "OSGCollectiveGravityParticleSystemAffectorBase.inl"
#include "OSGCollectiveGravityParticleSystemAffector.inl"

#endif /* _OSGCOLLECTIVEGRAVITYPARTICLESYSTEMAFFECTOR_H_ */
