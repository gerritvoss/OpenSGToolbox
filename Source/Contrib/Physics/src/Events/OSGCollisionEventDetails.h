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

#ifndef _OSGCOLLISIONEVENTDETAILS_H_
#define _OSGCOLLISIONEVENTDETAILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGCollisionEventDetailsBase.h"
#include "OSGPhysicsGeomFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief CollisionEventDetails class. See \ref
           PageContribPhysicsCollisionEventDetails for a description.
*/

class OSG_CONTRIBPHYSICS_DLLMAPPING CollisionEventDetails : public CollisionEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CollisionEventDetailsBase Inherited;
    typedef CollisionEventDetails     Self;

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
    static  CollisionEventDetailsTransitPtr      create(  FieldContainer* const Source,
                                                   Time TimeStamp,
                                                   const Pnt3f& Position,
                                                   const Vec3f& Normal,
                                                   PhysicsGeom* const Geom1,
                                                   PhysicsGeom* const Geom2,
                                                   UInt64 Geom1Cat,
                                                   UInt64 Geom1Col,
                                                   UInt64 Geom2Cat,
                                                   UInt64 Geom2Col,
                                                   const Vec3f& Velocity1,
                                                   const Vec3f& Velocity2,
                                                   const Real32& ProjectedNormalSpeed); 
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in CollisionEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CollisionEventDetails(void);
    CollisionEventDetails(const CollisionEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CollisionEventDetails(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CollisionEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CollisionEventDetails &source);
};

typedef CollisionEventDetails *CollisionEventDetailsP;

OSG_END_NAMESPACE

#include "OSGCollisionEventDetailsBase.inl"
#include "OSGCollisionEventDetails.inl"

#endif /* _OSGCOLLISIONEVENTDETAILS_H_ */
