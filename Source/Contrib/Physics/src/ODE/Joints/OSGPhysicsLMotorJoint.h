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

#ifndef _OSGPHYSICSLMOTORJOINT_H_
#define _OSGPHYSICSLMOTORJOINT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPhysicsLMotorJointBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PhysicsLMotorJoint class. See \ref
           PageContribPhysicsPhysicsLMotorJoint for a description.
*/

class OSG_CONTRIBPHYSICS_DLLMAPPING PhysicsLMotorJoint : public PhysicsLMotorJointBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PhysicsLMotorJointBase Inherited;
    typedef PhysicsLMotorJoint     Self;

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
    void setAxis1Properties(const Vec3f& Axis, UInt8 ReferenceFrame);
    void setAxis2Properties(const Vec3f& Axis, UInt8 ReferenceFrame);
    void setAxis3Properties(const Vec3f& Axis, UInt8 ReferenceFrame);

    static PhysicsLMotorJointUnrecPtr create(PhysicsWorldUnrecPtr w); 
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PhysicsLMotorJointBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsLMotorJoint(void);
    PhysicsLMotorJoint(const PhysicsLMotorJoint &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsLMotorJoint(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PhysicsLMotorJointBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PhysicsLMotorJoint &source);
};

typedef PhysicsLMotorJoint *PhysicsLMotorJointP;

OSG_END_NAMESPACE

#include "OSGPhysicsLMotorJointBase.inl"
#include "OSGPhysicsLMotorJoint.inl"

#endif /* _OSGPHYSICSLMOTORJOINT_H_ */
