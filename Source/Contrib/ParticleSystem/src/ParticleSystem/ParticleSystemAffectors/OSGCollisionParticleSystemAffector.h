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

#ifndef _OSGCOLLISIONPARTICLESYSTEMAFFECTOR_H_
#define _OSGCOLLISIONPARTICLESYSTEMAFFECTOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGCollisionParticleSystemAffectorBase.h"
#include "OSGParticleCollisionEventDetails.h"

OSG_BEGIN_NAMESPACE

/*! \brief CollisionParticleSystemAffector class. See \ref
           PageContribParticleSystemCollisionParticleSystemAffector for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING CollisionParticleSystemAffector : public CollisionParticleSystemAffectorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CollisionParticleSystemAffectorBase Inherited;
    typedef CollisionParticleSystemAffector     Self;

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

    // Variables should all be in CollisionParticleSystemAffectorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CollisionParticleSystemAffector(void);
    CollisionParticleSystemAffector(const CollisionParticleSystemAffector &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CollisionParticleSystemAffector(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    void produceParticleCollision(ParticleSystem* const System,
                                  UInt32 PrimaryIndex,
                                  ParticleSystem* const SecondarySystem,
                                  UInt32 SecondaryIndex);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CollisionParticleSystemAffectorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CollisionParticleSystemAffector &source);
};

typedef CollisionParticleSystemAffector *CollisionParticleSystemAffectorP;

OSG_END_NAMESPACE

#include "OSGCollisionParticleSystemAffectorBase.inl"
#include "OSGCollisionParticleSystemAffector.inl"

#endif /* _OSGCOLLISIONPARTICLESYSTEMAFFECTOR_H_ */
