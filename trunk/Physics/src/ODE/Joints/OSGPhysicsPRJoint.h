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

#ifndef _OSGPHYSICSPRJOINT_H_
#define _OSGPHYSICSPRJOINT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGPhysicsPRJointBase.h"
#include "ODE/OSGPhysicsWorld.h"

OSG_BEGIN_NAMESPACE

/*! \brief PhysicsPRJoint class. See \ref 
           PagePhysicsPhysicsPRJoint for a description.
*/

class OSG_PHYSICSLIB_DLLMAPPING PhysicsPRJoint : public PhysicsPRJointBase
{
  private:

    typedef PhysicsPRJointBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
    Real32 getPRPosition(void) const;
    Real32 getPRPositionRate(void) const;
    Real32 getPRAngle(void) const;
    Real32 getPRAngleRate(void) const;

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
    static PhysicsPRJointPtr create(PhysicsWorldPtr w); 
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in PhysicsPRJointBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsPRJoint(void);
    PhysicsPRJoint(const PhysicsPRJoint &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsPRJoint(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class PhysicsPRJointBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const PhysicsPRJoint &source);
};

typedef PhysicsPRJoint *PhysicsPRJointP;

OSG_END_NAMESPACE

#include "OSGPhysicsPRJointBase.inl"
#include "OSGPhysicsPRJoint.inl"

#define OSGPHYSICSPRJOINT_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGPHYSICSPRJOINT_H_ */
