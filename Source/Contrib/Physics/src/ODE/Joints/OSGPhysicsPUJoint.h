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

#ifndef _OSGPHYSICSPUJOINT_H_
#define _OSGPHYSICSPUJOINT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPhysicsPUJointBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PhysicsPUJoint class. See \ref
           PageContribPhysicsPhysicsPUJoint for a description.
*/

class OSG_CONTRIBPHYSICS_DLLMAPPING PhysicsPUJoint : public PhysicsPUJointBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PhysicsPUJointBase Inherited;
    typedef PhysicsPUJoint     Self;

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

    Real32 getPUPosition(void) const;
    Real32 getPUPositionRate(void) const;
    Real32 getPUAngle1(void) const;
    Real32 getPUAngle1Rate(void) const;
    Real32 getPUAngle2(void) const;
    Real32 getPUAngle2Rate(void) const;

    static PhysicsPUJointUnrecPtr create(PhysicsWorldUnrecPtr w); 
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PhysicsPUJointBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsPUJoint(void);
    PhysicsPUJoint(const PhysicsPUJoint &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsPUJoint(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PhysicsPUJointBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PhysicsPUJoint &source);
};

typedef PhysicsPUJoint *PhysicsPUJointP;

OSG_END_NAMESPACE

#include "OSGPhysicsPUJointBase.inl"
#include "OSGPhysicsPUJoint.inl"

#endif /* _OSGPHYSICSPUJOINT_H_ */
