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

#ifndef _OSGCOLLISIONEVENT_H_
#define _OSGCOLLISIONEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPhysicsGeom.h"
#include "OSGCollisionEventBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief CollisionEvent class. See \ref
           PageContribPhysicsCollisionEvent for a description.
*/

class OSG_CONTRIBPHYSICS_DLLMAPPING CollisionEvent : public CollisionEventBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CollisionEventBase Inherited;
    typedef CollisionEvent     Self;

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
    static  CollisionEventTransitPtr      create(  FieldContainerUnrecPtr Source,
                                                   Time TimeStamp,
                                                   const Pnt3f& Position,
                                                   const Vec3f& Normal,
                                                   PhysicsGeomUnrecPtr Geom1,
                                                   PhysicsGeomUnrecPtr Geom2,
                                                   UInt64 Geom1Cat,
                                                   UInt64 Geom1Col,
                                                   UInt64 Geom2Cat,
                                                   UInt64 Geom2Col,
                                                   const Vec3f& Velocity1,
                                                   const Vec3f& Velocity2,
                                                   const Real32& ProjectedNormalSpeed); 
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in CollisionEventBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CollisionEvent(void);
    CollisionEvent(const CollisionEvent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CollisionEvent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CollisionEventBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CollisionEvent &source);
};

typedef CollisionEvent *CollisionEventP;

OSG_END_NAMESPACE

#include "OSGCollisionEventBase.inl"
#include "OSGCollisionEvent.inl"

#endif /* _OSGCOLLISIONEVENT_H_ */
