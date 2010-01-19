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

#ifndef _OSGPHYSICSUNIVERSALJOINT_H_
#define _OSGPHYSICSUNIVERSALJOINT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPhysicsUniversalJointBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PhysicsUniversalJoint class. See \ref
           PageContribPhysicsPhysicsUniversalJoint for a description.
*/

class OSG_CONTRIBPHYSICS_DLLMAPPING PhysicsUniversalJoint : public PhysicsUniversalJointBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PhysicsUniversalJointBase Inherited;
    typedef PhysicsUniversalJoint     Self;

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
    Real32 getUniversalAngle1(void) const;
    Real32 getUniversalAngle1Rate(void) const;
    Real32 getUniversalAngle2(void) const;
    Real32 getUniversalAngle2Rate(void) const;

    static PhysicsUniversalJointUnrecPtr create(PhysicsWorldUnrecPtr w); 
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PhysicsUniversalJointBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsUniversalJoint(void);
    PhysicsUniversalJoint(const PhysicsUniversalJoint &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsUniversalJoint(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const PhysicsUniversalJoint *id = NULL);
	void onDestroy();
	/*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PhysicsUniversalJointBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PhysicsUniversalJoint &source);
};

typedef PhysicsUniversalJoint *PhysicsUniversalJointP;

OSG_END_NAMESPACE

#include "OSGPhysicsUniversalJointBase.inl"
#include "OSGPhysicsUniversalJoint.inl"

#endif /* _OSGPHYSICSUNIVERSALJOINT_H_ */
