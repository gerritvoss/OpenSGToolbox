/*---------------------------------------------------------------------------*\
 *                         OpenSG ToolBox Physics                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                          www.vrac.iastate.edu                             *
 *                                                                           *
 *                Authors: Behboud Kalantary, David Kabala                   *
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

#include <OpenSG/OSGConfig.h>
#include "OSGPhysicsDef.h"

#include "OSGPhysicsAMotorJointBase.h"

OSG_BEGIN_NAMESPACE

class  OSG_PHYSICSLIB_DLLMAPPING PhysicsAMotorJoint : public PhysicsAMotorJointBase
{
  private:

    typedef PhysicsAMotorJointBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

	  /*---------------------------------------------------------------------*/
	  /*! \name                   Class Specific                             */
	  /*! \{																*/
      void setAxis1Properties(const Vec3f& Axis, UInt8 ReferenceFrame);
      void setAxis2Properties(const Vec3f& Axis, UInt8 ReferenceFrame);
      void setAxis3Properties(const Vec3f& Axis, UInt8 ReferenceFrame);

	  void setAngle(Int32 anum, Real32 angle);
	  Real32 getAngle(Int32 anum);
	  Real32 getAngleRate(Int32 anum);

	  /*! \} 		                                                       */

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    static PhysicsAMotorJointPtr create(PhysicsWorldPtr w); 
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
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const PhysicsAMotorJoint *id = NULL);
	void onDestroy();
    /*! \} 		                                                       */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class PhysicsAMotorJointBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const PhysicsAMotorJoint &source);
};

typedef PhysicsAMotorJoint *PhysicsAMotorJointP;

OSG_END_NAMESPACE

#include "OSGPhysicsAMotorJointBase.inl"
#include "OSGPhysicsAMotorJoint.inl"

#define OSGPHYSICSAMOTORJOINT_HEADER_CVSID "@(#)$Id: OSGPhysicsAMotorJoint.h,v 1.2 2006/08/19 00:21:46 dirk Exp $"

#endif /* _OSGPHYSICSAMOTORJOINT_H_ */
