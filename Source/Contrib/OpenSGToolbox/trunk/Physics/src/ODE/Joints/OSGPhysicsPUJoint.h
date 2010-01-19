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

#ifndef _OSGPHYSICSPUJOINT_H_
#define _OSGPHYSICSPUJOINT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGPhysicsDef.h"

#include "OSGPhysicsPUJointBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PhysicsPUJoint class. See \ref 
           PagePhysicsPhysicsPUJoint for a description.
*/

class OSG_PHYSICSLIB_DLLMAPPING PhysicsPUJoint : public PhysicsPUJointBase
{
  private:

    typedef PhysicsPUJointBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    Real32 getPUPosition(void) const;
    Real32 getPUPositionRate(void) const;
    Real32 getPUAngle1(void) const;
    Real32 getPUAngle1Rate(void) const;
    Real32 getPUAngle2(void) const;
    Real32 getPUAngle2Rate(void) const;


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
    static PhysicsPUJointPtr create(PhysicsWorldPtr w); 
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
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class PhysicsPUJointBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const PhysicsPUJoint &source);
};

typedef PhysicsPUJoint *PhysicsPUJointP;

OSG_END_NAMESPACE

#include "OSGPhysicsPUJointBase.inl"
#include "OSGPhysicsPUJoint.inl"

#define OSGPHYSICSPUJOINT_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGPHYSICSPUJOINT_H_ */
