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

#ifndef _OSGPARTICLEEVENTDETAILS_H_
#define _OSGPARTICLEEVENTDETAILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGParticleEventDetailsBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ParticleEventDetails class. See \ref
           PageContribParticleSystemParticleEventDetails for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING ParticleEventDetails : public ParticleEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ParticleEventDetailsBase Inherited;
    typedef ParticleEventDetails     Self;

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
    static ParticleEventDetailsTransitPtr create( FieldContainer* const Source,
                                           Time TimeStamp,
                                           Int32 Index,
                                           const Pnt3f& Position,
                                           const Pnt3f& SecPosition,
                                           const Vec3f& Normal,
                                           const Color4f& Color,
                                           const Vec3f& Size,
                                           Real32 Lifespan,
                                           Real32 Age,
                                           const Vec3f& Velocity,
                                           const Vec3f& SecVelocity,
                                           const Vec3f& Acceleration,
                                           const StringToUInt32Map& Attributes,
										   UInt32 ID);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ParticleEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ParticleEventDetails(void);
    ParticleEventDetails(const ParticleEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ParticleEventDetails(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ParticleEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ParticleEventDetails &source);
};

typedef ParticleEventDetails *ParticleEventDetailsP;

OSG_END_NAMESPACE

#include "OSGParticleEventDetailsBase.inl"
#include "OSGParticleEventDetails.inl"

#endif /* _OSGPARTICLEEVENTDETAILS_H_ */
