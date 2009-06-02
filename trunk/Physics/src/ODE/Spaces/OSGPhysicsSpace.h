/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#ifndef _OSGPHYSICSSPACE_H_
#define _OSGPHYSICSSPACE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGPhysicsDef.h"
#include <ode/ode.h>

#include "OSGPhysicsSpaceBase.h"

OSG_BEGIN_NAMESPACE

class  OSG_PHYSICSLIB_DLLMAPPING PhysicsSpace : public PhysicsSpaceBase
{
  private:

    typedef PhysicsSpaceBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
	  /*---------------------------------------------------------------------*/
	  /*! \name                   Class Specific                             */
	  /*! \{                                                                 */
	  void onCreate(const PhysicsSpace *id = NULL);
	  void onDestroy();
	  /*! \}                                                                 */
	  /*---------------------------------------------------------------------*/
	  /*! \name                   Class Specific Get Field                    */
	  /*! \{                                                                 */
	  bool getCleanup(void);
      dSpaceID getSpaceID(void);
	  /*! \}                                                                 */

	  /*---------------------------------------------------------------------*/
	  /*! \name                   Class Specific Set Field                    */
	  /*! \{                                                                 */
	  void setCleanup(const bool &value );
      void setSpaceID(const dSpaceID &value );
	  /*! \}                                                                 */

	  /*---------------------------------------------------------------------*/
	  /*! \name                   Class Specific                             */
	  /*! \{																*/
      void initSpace();
	  void AddGeom( dGeomID );
	  void RemoveGeom( dGeomID );
	  bool ContainsGeom( dGeomID );
	  void AddSpace( dSpaceID );
	  void RemoveSpace( dSpaceID );
	  bool ContainsSpace( dSpaceID );
	  Int32 GetNumGeoms();
	  dGeomID GetGeom( Int32 i );

	  void Collide( void* somedata, dNearCallback* callback );
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

    // Variables should all be in PhysicsSpaceBase.
    dSpaceID sID;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsSpace(void);
    PhysicsSpace(const PhysicsSpace &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsSpace(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class PhysicsSpaceBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const PhysicsSpace &source);
};

typedef PhysicsSpace *PhysicsSpaceP;

OSG_END_NAMESPACE

#include "OSGPhysicsSpaceBase.inl"
#include "OSGPhysicsSpace.inl"

#define OSGPHYSICSSPACE_HEADER_CVSID "@(#)$Id: OSGPhysicsSpace.h,v 1.2 2006/08/19 00:21:47 dirk Exp $"

#endif /* _OSGPHYSICSSPACE_H_ */
