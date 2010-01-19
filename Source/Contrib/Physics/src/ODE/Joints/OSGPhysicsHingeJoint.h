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

#ifndef _OSGPHYSICSHINGEJOINT_H_
#define _OSGPHYSICSHINGEJOINT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPhysicsHingeJointBase.h"
#include "OSGPhysicsWorldFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief PhysicsHingeJoint class. See \ref
           PageContribPhysicsPhysicsHingeJoint for a description.
*/

class OSG_CONTRIBPHYSICS_DLLMAPPING PhysicsHingeJoint : public PhysicsHingeJointBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PhysicsHingeJointBase Inherited;
    typedef PhysicsHingeJoint     Self;

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
    Vec3f getAnchor2(void);
    Real32 getAngle(void);
    Real32 getAngleRate(void);

    static PhysicsHingeJointUnrecPtr create(PhysicsWorldUnrecPtr w); 
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PhysicsHingeJointBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsHingeJoint(void);
    PhysicsHingeJoint(const PhysicsHingeJoint &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsHingeJoint(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const PhysicsHingeJoint *id = NULL);
	void onDestroy();
	/*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PhysicsHingeJointBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PhysicsHingeJoint &source);
};

typedef PhysicsHingeJoint *PhysicsHingeJointP;

OSG_END_NAMESPACE

#include "OSGPhysicsHingeJointBase.inl"
#include "OSGPhysicsHingeJoint.inl"

#endif /* _OSGPHYSICSHINGEJOINT_H_ */
