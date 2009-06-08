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

#ifndef _OSGPHYSICSPISTONJOINT_H_
#define _OSGPHYSICSPISTONJOINT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGPhysicsPistonJointBase.h"
#include "ODE/OSGPhysicsWorldFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief PhysicsPistonJoint class. See \ref 
           PagePhysicsPhysicsPistonJoint for a description.
*/

class OSG_PHYSICSLIB_DLLMAPPING PhysicsPistonJoint : public PhysicsPistonJointBase
{
  private:

    typedef PhysicsPistonJointBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    Vec3f getPistonAnchor2(void) const;
    Real32 getPistonPosition(void) const;
    Real32 getPistonPositionRate(void) const;
    Real32 getPistonAngle(void) const;
    Real32 getPistonAngleRate(void) const;

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
    static PhysicsPistonJointPtr create(PhysicsWorldPtr w); 
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
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class PhysicsPistonJointBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const PhysicsPistonJoint &source);
};

typedef PhysicsPistonJoint *PhysicsPistonJointP;

OSG_END_NAMESPACE

#include "OSGPhysicsPistonJointBase.inl"
#include "OSGPhysicsPistonJoint.inl"

#define OSGPHYSICSPISTONJOINT_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGPHYSICSPISTONJOINT_H_ */
