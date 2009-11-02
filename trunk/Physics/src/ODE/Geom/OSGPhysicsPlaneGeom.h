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

#ifndef _OSGPHYSICSPLANEGEOM_H_
#define _OSGPHYSICSPLANEGEOM_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGPhysicsDef.h"

#include "OSGPhysicsPlaneGeomBase.h"

OSG_BEGIN_NAMESPACE

class  OSG_PHYSICSLIB_DLLMAPPING PhysicsPlaneGeom : public PhysicsPlaneGeomBase
{
  private:

    typedef PhysicsPlaneGeomBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

	  /*---------------------------------------------------------------------*/
	  /*! \name                   Class Specific                             */
	  /*! \{																*/
	  Real32 getPointDepth(const Vec3f& p) const;
      virtual bool isPlaceable(void) const;
	  /*! \}                                                                 */
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

    // Variables should all be in PhysicsPlaneGeomBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsPlaneGeom(void);
    PhysicsPlaneGeom(const PhysicsPlaneGeom &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsPlaneGeom(void); 

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const PhysicsPlaneGeom *id = NULL);
	void onDestroy();
	/*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class PhysicsPlaneGeomBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const PhysicsPlaneGeom &source);
};

typedef PhysicsPlaneGeom *PhysicsPlaneGeomP;

OSG_END_NAMESPACE

#include "OSGPhysicsPlaneGeomBase.inl"
#include "OSGPhysicsPlaneGeom.inl"

#define OSGPHYSICSPLANEGEOM_HEADER_CVSID "@(#)$Id: OSGPhysicsPlaneGeom.h,v 1.2 2006/08/19 00:21:46 dirk Exp $"

#endif /* _OSGPHYSICSPLANEGEOM_H_ */
