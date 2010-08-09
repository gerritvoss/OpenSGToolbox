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

#ifndef _OSGPARTICLEGEOMETRYCOLLISIONEVENTDETAILS_H_
#define _OSGPARTICLEGEOMETRYCOLLISIONEVENTDETAILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGParticleGeometryCollisionEventDetailsBase.h"
#include "OSGNode.h"
#include "OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

/*! \brief ParticleGeometryCollisionEventDetails class. See \ref
           PageContribParticleSystemParticleGeometryCollisionEventDetails for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING ParticleGeometryCollisionEventDetails : public ParticleGeometryCollisionEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ParticleGeometryCollisionEventDetailsBase Inherited;
    typedef ParticleGeometryCollisionEventDetails     Self;

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
    static ParticleGeometryCollisionEventDetailsTransitPtr create(FieldContainer* const Source,
                                                           Time TimeStamp,
                                                           Real32 HitT,
                                                           Node* const HitNode,
                                                           Int32 HitPolygonIndex,
                                                           Vec3f HitNormal,
                                                           Pnt3f HitPoint,
                                                           ParticleSystem* const System,
                                                           UInt32 Index); 
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ParticleGeometryCollisionEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ParticleGeometryCollisionEventDetails(void);
    ParticleGeometryCollisionEventDetails(const ParticleGeometryCollisionEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ParticleGeometryCollisionEventDetails(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ParticleGeometryCollisionEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ParticleGeometryCollisionEventDetails &source);
};

typedef ParticleGeometryCollisionEventDetails *ParticleGeometryCollisionEventDetailsP;

OSG_END_NAMESPACE

#include "OSGParticleGeometryCollisionEventDetailsBase.inl"
#include "OSGParticleGeometryCollisionEventDetails.inl"

#endif /* _OSGPARTICLEGEOMETRYCOLLISIONEVENTDETAILS_H_ */
