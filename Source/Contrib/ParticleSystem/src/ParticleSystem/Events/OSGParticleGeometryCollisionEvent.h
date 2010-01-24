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

#ifndef _OSGPARTICLEGEOMETRYCOLLISIONEVENT_H_
#define _OSGPARTICLEGEOMETRYCOLLISIONEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGParticleGeometryCollisionEventBase.h"
#include "OSGNode.h"
#include "OSGParticleSystem.h"

OSG_BEGIN_NAMESPACE

/*! \brief ParticleGeometryCollisionEvent class. See \ref
           PageContribParticleSystemParticleGeometryCollisionEvent for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING ParticleGeometryCollisionEvent : public ParticleGeometryCollisionEventBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ParticleGeometryCollisionEventBase Inherited;
    typedef ParticleGeometryCollisionEvent     Self;

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
    static ParticleGeometryCollisionEventTransitPtr create(FieldContainerRefPtr Source,
                                                           Time TimeStamp,
                                                           Real32 HitT,
                                                           NodeRefPtr HitNode,
                                                           Int32 HitPolygonIndex,
                                                           Vec3f HitNormal,
                                                           Pnt3f HitPoint,
                                                           ParticleSystemRefPtr System,
                                                           UInt32 Index); 
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ParticleGeometryCollisionEventBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ParticleGeometryCollisionEvent(void);
    ParticleGeometryCollisionEvent(const ParticleGeometryCollisionEvent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ParticleGeometryCollisionEvent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ParticleGeometryCollisionEventBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ParticleGeometryCollisionEvent &source);
};

typedef ParticleGeometryCollisionEvent *ParticleGeometryCollisionEventP;

OSG_END_NAMESPACE

#include "OSGParticleGeometryCollisionEventBase.inl"
#include "OSGParticleGeometryCollisionEvent.inl"

#endif /* _OSGPARTICLEGEOMETRYCOLLISIONEVENT_H_ */
