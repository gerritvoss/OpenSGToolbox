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

#ifndef _OSGPHYSICSBODY_H_
#define _OSGPHYSICSBODY_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGPhysicsDef.h"
#include <ode/ode.h>

#include "OSGPhysicsBodyBase.h"
#include "OSGPhysicsWorldFields.h"

OSG_BEGIN_NAMESPACE

class  OSG_PHYSICSLIB_DLLMAPPING PhysicsBody : public PhysicsBodyBase
{
  private:

    typedef PhysicsBodyBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
	  /*---------------------------------------------------------------------*/
	  /*! \name                   Class Specific Get Field                    */
	  /*! \{                                                                 */
      dBodyID getBodyID(void);

	  /*! \}                                                                 */

      void updateToODEState(void);

	  /*---------------------------------------------------------------------*/
	  /*! \name                   Class Specific Set Field                    */
	  /*! \{                                                                 */
	  /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                   Construction                               */
    /*! \{                                                                 */

    static  PhysicsBodyPtr      create          (PhysicsWorldPtr World);

    /*! \}                                                                 */

	  /*---------------------------------------------------------------------*/
	  /*! \name                   Class Specific                             */
	  /*! \{																*/
	  void setMassStruct(const dMass &mass );
	  void getMassStruct(dMass &mass );
	  void addForce(const Vec3f &v);
	  void addTorque(const Vec3f &v);
	  void addRelForce(const Vec3f &v);
	  void addRelTorque(const Vec3f &v);
	  void addForceAtPos(const Vec3f &v,const  Vec3f &p);
	  void addForceAtRelPos(const Vec3f &v,const  Vec3f &p);
	  void addRelForceAtPos(const Vec3f &v,const Vec3f &p);
	  void addRelForceAtRelPos(const Vec3f &v,const Vec3f &p);
	  void getRelPointPos(const Vec3f &p, Vec3f &result);
	  void getRelPointVel(const Vec3f &p, Vec3f &result);
	  void getPointVel(const Vec3f &p, Vec3f &result);
	  void getPosRelPoint(const Vec3f &p, Vec3f &result);
	  void vectorToWorld(const Vec3f &p, Vec3f &result);
	  void vectorFromWorld(const Vec3f &p, Vec3f &result);
	  void setAutoDisableDefaults(void);
	  void setData(void* someData);
	  void* getData(void);
	  Int32 getNumJoints(void);
	  dJointID getJoint(Int32 index);
      void initDefaults(void);

      //Mass
      void resetMass();
      void setMassParams( Real32 theMass, const Vec3f& cg,
          Real32 I11, Real32 I22, Real32 I33,
          Real32 I12, Real32 I13, Real32 I23 );
      void setSphereMass( Real32 density, Real32 radius );
      void setSphereMassTotal( Real32 totalMass, Real32 radius );
      void setCCylinderMass( Real32 density, Int32 direction,
          Real32 radius, Real32 length );
      void setCCylinderMassTotal( Real32 totalMass, Int32 direction,
          Real32 radius, Real32 length );
      void setBoxMass( Real32 density, Real32 lx, Real32 ly, Real32 lz );
      void setBoxMassTotal( Real32 totalMass, Real32 lx, Real32 ly, Real32 lz );
      void adjustMass( Real32 newMass );
      void translateMass( const Vec3f& );
      void rotateMass( const Matrix& );
      void addMassOf( dBodyID otherBody );

      //Damping
      void setDamping (Real32 linear_scale, Real32 angular_scale);


      void setDampingDefaults (void);
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

    void applyAccumForces(void);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in PhysicsBodyBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsBody(void);
    PhysicsBody(const PhysicsBody &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsBody(void); 

    /*! \}                                                                 */
    
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const PhysicsBody *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */

    void updateAddedForceTorque(void);

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class PhysicsBodyBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const PhysicsBody &source);

    dBodyID _BodyID;
    Vec3f _AccumulatedForce;
    Vec3f _AccumulatedTorque;
};

typedef PhysicsBody *PhysicsBodyP;

OSG_END_NAMESPACE

#include "OSGPhysicsBodyBase.inl"
#include "OSGPhysicsBody.inl"

#define OSGPHYSICSBODY_HEADER_CVSID "@(#)$Id: OSGPhysicsBody.h,v 1.2 2006/08/19 00:21:46 dirk Exp $"

#endif /* _OSGPHYSICSBODY_H_ */
