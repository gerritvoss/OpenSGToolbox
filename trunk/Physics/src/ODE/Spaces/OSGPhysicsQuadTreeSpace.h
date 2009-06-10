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
/**************************************************************************//**
 * @class   PhysicsQuadTreeSpace : public PhysicsHashSpaceBase
 * 
 * @brief	A wapper around the ODE QuadTree space type. 
 * 
 * @ingroup PhysicsSpaces
 *
 * @see    @htmlonly <A href="http://www.ode.org/">ODE</A> @endhtmlonly
 *****************************************************************************/

#ifndef _OSGPHYSICSQUADTREESPACE_H_
#define _OSGPHYSICSQUADTREESPACE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGPhysicsDef.h"

#include "OSGPhysicsQuadTreeSpaceBase.h"

OSG_BEGIN_NAMESPACE

class  OSG_PHYSICSLIB_DLLMAPPING PhysicsQuadTreeSpace : public PhysicsQuadTreeSpaceBase
{
  private:

    typedef PhysicsQuadTreeSpaceBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
	  void initQuadTree(dSpaceID space);
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
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in PhysicsQuadTreeSpaceBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsQuadTreeSpace(void);
    PhysicsQuadTreeSpace(const PhysicsQuadTreeSpace &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsQuadTreeSpace(void); 

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const PhysicsQuadTreeSpace *id = NULL);
	void onDestroy();
	/*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class PhysicsQuadTreeSpaceBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const PhysicsQuadTreeSpace &source);
};

typedef PhysicsQuadTreeSpace *PhysicsQuadTreeSpaceP;

OSG_END_NAMESPACE

#include "OSGPhysicsQuadTreeSpaceBase.inl"
#include "OSGPhysicsQuadTreeSpace.inl"

#define OSGPHYSICSQUADTREESPACE_HEADER_CVSID "@(#)$Id: OSGPhysicsQuadTreeSpace.h,v 1.2 2006/08/19 00:21:46 dirk Exp $"

#endif /* _OSGPHYSICSQUADTREESPACE_H_ */
