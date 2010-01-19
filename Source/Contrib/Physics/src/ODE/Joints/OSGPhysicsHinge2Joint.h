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

#ifndef _OSGPHYSICSHINGE2JOINT_H_
#define _OSGPHYSICSHINGE2JOINT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPhysicsHinge2JointBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PhysicsHinge2Joint class. See \ref
           PageContribPhysicsPhysicsHinge2Joint for a description.
*/

class OSG_CONTRIBPHYSICS_DLLMAPPING PhysicsHinge2Joint : public PhysicsHinge2JointBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PhysicsHinge2JointBase Inherited;
    typedef PhysicsHinge2Joint     Self;

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
    Vec3f getAnchor2(void) const;
    Real32 getAngle1(void) const;
    Real32 getAngle1Rate(void) const;
    Real32 getAngle2Rate(void) const;

    static PhysicsHinge2JointUnrecPtr create(PhysicsWorldUnrecPtr w); 
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PhysicsHinge2JointBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsHinge2Joint(void);
    PhysicsHinge2Joint(const PhysicsHinge2Joint &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsHinge2Joint(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const PhysicsHinge2Joint *id = NULL);
	void onDestroy();
	/*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PhysicsHinge2JointBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PhysicsHinge2Joint &source);
};

typedef PhysicsHinge2Joint *PhysicsHinge2JointP;

OSG_END_NAMESPACE

#include "OSGPhysicsHinge2JointBase.inl"
#include "OSGPhysicsHinge2Joint.inl"

#endif /* _OSGPHYSICSHINGE2JOINT_H_ */
