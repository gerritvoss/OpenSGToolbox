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

#ifndef _OSGDISTANCEPARTICLEAFFECTOR_H_
#define _OSGDISTANCEPARTICLEAFFECTOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDistanceParticleAffectorBase.h"
#include "OSGCamera.h"

OSG_BEGIN_NAMESPACE

/*! \brief DistanceParticleAffector class. See \ref
           PageContribParticleSystemDistanceParticleAffector for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING DistanceParticleAffector : public DistanceParticleAffectorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum DistanceSource
    {
        DISTANCE_FROM_CAMERA = 0,
        DISTANCE_FROM_NODE   = 1
    };

    typedef DistanceParticleAffectorBase Inherited;
    typedef DistanceParticleAffector     Self;

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

    // Variables should all be in DistanceParticleAffectorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DistanceParticleAffector(void);
    DistanceParticleAffector(const DistanceParticleAffector &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DistanceParticleAffector(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    virtual bool affect(ParticleSystemRefPtr System, Int32 ParticleIndex, const Time& elps, const Vec3f& Displacement) = 0;
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DistanceParticleAffectorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DistanceParticleAffector &source);
};

typedef DistanceParticleAffector *DistanceParticleAffectorP;

OSG_END_NAMESPACE

#include "OSGDistanceParticleAffectorBase.inl"
#include "OSGDistanceParticleAffector.inl"

#endif /* _OSGDISTANCEPARTICLEAFFECTOR_H_ */
