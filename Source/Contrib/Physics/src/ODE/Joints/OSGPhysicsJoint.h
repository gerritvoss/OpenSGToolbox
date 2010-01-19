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

#ifndef _OSGPHYSICSJOINT_H_
#define _OSGPHYSICSJOINT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPhysicsJointBase.h"
#include <ode/ode.h>

OSG_BEGIN_NAMESPACE

/*! \brief PhysicsJoint class. See \ref
           PageContribPhysicsPhysicsJoint for a description.
*/

class OSG_CONTRIBPHYSICS_DLLMAPPING PhysicsJoint : public PhysicsJointBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PhysicsJointBase Inherited;
    typedef PhysicsJoint     Self;

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
    dJointID getJointID(void);

    void setData( void* someData );
    void* getData(void);
    Int32 getJointType(void);
    dBodyID getBody( Int32 );
    // the raw feedback interface
    void setFeedback( dJointFeedback* );
    dJointFeedback* getFeedback(void);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PhysicsJointBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsJoint(void);
    PhysicsJoint(const PhysicsJoint &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsJoint(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const PhysicsJoint *id = NULL);
	void onDestroy();
	/*! \}                                                                 */
    dJointID _JointID;
    void setJointID(const dJointID &value );
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PhysicsJointBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PhysicsJoint &source);
};

typedef PhysicsJoint *PhysicsJointP;

OSG_END_NAMESPACE

#include "OSGPhysicsWorld.h"
#include "OSGPhysicsBody.h"

#include "OSGPhysicsJointBase.inl"
#include "OSGPhysicsJoint.inl"

#endif /* _OSGPHYSICSJOINT_H_ */
