/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#ifndef _OSGPHYSICSPLANE2DJOINT_H_
#define _OSGPHYSICSPLANE2DJOINT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGPhysicsPlane2DJointBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PhysicsPlane2DJoint class. See \ref 
           PagePhysicsPhysicsPlane2DJoint for a description.
*/

class OSG_PHYSICSLIB_DLLMAPPING PhysicsPlane2DJoint : public PhysicsPlane2DJointBase
{
  private:

    typedef PhysicsPlane2DJointBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

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
    static PhysicsPlane2DJointPtr create(PhysicsWorldPtr w); 
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in PhysicsPlane2DJointBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsPlane2DJoint(void);
    PhysicsPlane2DJoint(const PhysicsPlane2DJoint &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsPlane2DJoint(void); 

    /*! \}                                                                 */
	void onCreate(const PhysicsPlane2DJoint *id = NULL);
	void onDestroy();
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class PhysicsPlane2DJointBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const PhysicsPlane2DJoint &source);
};

typedef PhysicsPlane2DJoint *PhysicsPlane2DJointP;

OSG_END_NAMESPACE

#include "OSGPhysicsPlane2DJointBase.inl"
#include "OSGPhysicsPlane2DJoint.inl"

#endif /* _OSGPHYSICSPLANE2DJOINT_H_ */
