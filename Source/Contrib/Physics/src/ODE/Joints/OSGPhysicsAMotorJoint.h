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

#ifndef _OSGPHYSICSAMOTORJOINT_H_
#define _OSGPHYSICSAMOTORJOINT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPhysicsAMotorJointBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PhysicsAMotorJoint class. See \ref
           PageContribPhysicsPhysicsAMotorJoint for a description.
*/

class OSG_CONTRIBPHYSICS_DLLMAPPING PhysicsAMotorJoint : public PhysicsAMotorJointBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PhysicsAMotorJointBase Inherited;
    typedef PhysicsAMotorJoint     Self;

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
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{																*/
    void setAxis1Properties(const Vec3f& Axis, UInt8 ReferenceFrame);
    void setAxis2Properties(const Vec3f& Axis, UInt8 ReferenceFrame);
    void setAxis3Properties(const Vec3f& Axis, UInt8 ReferenceFrame);

    void setAngle(Int32 anum, Real32 angle);
    Real32 getAngle(Int32 anum);
    Real32 getAngleRate(Int32 anum);

    static PhysicsAMotorJointUnrecPtr create(PhysicsWorldUnrecPtr w); 
    /*! \} 		                                                       */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PhysicsAMotorJointBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsAMotorJoint(void);
    PhysicsAMotorJoint(const PhysicsAMotorJoint &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsAMotorJoint(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const PhysicsAMotorJoint *id = NULL);
	void onDestroy();
    /*! \} 		                                                       */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PhysicsAMotorJointBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PhysicsAMotorJoint &source);
};

typedef PhysicsAMotorJoint *PhysicsAMotorJointP;

OSG_END_NAMESPACE

#include "OSGPhysicsAMotorJointBase.inl"
#include "OSGPhysicsAMotorJoint.inl"

#endif /* _OSGPHYSICSAMOTORJOINT_H_ */
