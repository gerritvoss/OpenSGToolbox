/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com),  Behboud Kalantary         *
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

#ifndef _OSGPHYSICSPISTONJOINT_H_
#define _OSGPHYSICSPISTONJOINT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPhysicsPistonJointBase.h"
#include "OSGPhysicsWorldFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief PhysicsPistonJoint class. See \ref
           PageContribPhysicsPhysicsPistonJoint for a description.
*/

class OSG_CONTRIBPHYSICS_DLLMAPPING PhysicsPistonJoint : public PhysicsPistonJointBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PhysicsPistonJointBase Inherited;
    typedef PhysicsPistonJoint     Self;

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
    Vec3f getPistonAnchor2(void) const;
    Real32 getPistonPosition(void) const;
    Real32 getPistonPositionRate(void) const;
    Real32 getPistonAngle(void) const;
    Real32 getPistonAngleRate(void) const;

    static PhysicsPistonJointUnrecPtr create(PhysicsWorldUnrecPtr w); 
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PhysicsPistonJointBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsPistonJoint(void);
    PhysicsPistonJoint(const PhysicsPistonJoint &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsPistonJoint(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PhysicsPistonJointBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PhysicsPistonJoint &source);
};

typedef PhysicsPistonJoint *PhysicsPistonJointP;

OSG_END_NAMESPACE

#include "OSGPhysicsPistonJointBase.inl"
#include "OSGPhysicsPistonJoint.inl"

#endif /* _OSGPHYSICSPISTONJOINT_H_ */
