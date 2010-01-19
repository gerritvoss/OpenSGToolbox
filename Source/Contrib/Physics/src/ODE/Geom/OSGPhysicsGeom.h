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

#ifndef _OSGPHYSICSGEOM_H_
#define _OSGPHYSICSGEOM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPhysicsGeomBase.h"
#include <ode/ode.h>

OSG_BEGIN_NAMESPACE

/*! \brief PhysicsGeom class. See \ref
           PageContribPhysicsPhysicsGeom for a description.
*/

class OSG_CONTRIBPHYSICS_DLLMAPPING PhysicsGeom : public PhysicsGeomBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PhysicsGeomBase Inherited;
    typedef PhysicsGeom     Self;

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
	  void getAABB(Real32 aabb[6]) const;
      void clearOffset(void);
	  bool isSpace(void) const;
	  Int32 getGeomClass(void) const;
	  bool isEnabled(void) const;
	  void setData(void* someData);
	  void* getData(void) const;
	  void Collide2(dGeomID  otherGID, void* someData, dNearCallback* callback);

      Matrix getTransformation(void) const;
      virtual bool isPlaceable(void) const;
      dGeomID getGeomID(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PhysicsGeomBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsGeom(void);
    PhysicsGeom(const PhysicsGeom &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsGeom(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const PhysicsGeom *id = NULL);
	void onDestroy();
    /*! \}                                                                 */

    //ode Geometry Id
    dGeomID _GeomID;
    void setGeomID(const dGeomID &value);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PhysicsGeomBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PhysicsGeom &source);
};

typedef PhysicsGeom *PhysicsGeomP;

OSG_END_NAMESPACE

#include "OSGPhysicsBody.h"
#include "OSGPhysicsJoint.h"

#include "OSGPhysicsGeomBase.inl"
#include "OSGPhysicsGeom.inl"

#endif /* _OSGPHYSICSGEOM_H_ */
