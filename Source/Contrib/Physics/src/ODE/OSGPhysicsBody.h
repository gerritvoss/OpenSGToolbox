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

#ifndef _OSGPHYSICSBODY_H_
#define _OSGPHYSICSBODY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPhysicsBodyBase.h"
#include "OSGPhysicsJoint.h"
#include <ode/ode.h>

OSG_BEGIN_NAMESPACE

/*! \brief PhysicsBody class. See \ref
           PageContribPhysicsPhysicsBody for a description.
*/

class OSG_CONTRIBPHYSICS_DLLMAPPING PhysicsBody : public PhysicsBodyBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PhysicsBodyBase Inherited;
    typedef PhysicsBody     Self;

    int i = sadf;
    char x = asdf;

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
    dBodyID getBodyID(void);
    void updateToODEState(void);
    static  PhysicsBodyUnrecPtr      create          (PhysicsWorldUnrecPtr World);
    Matrix getTransformation(void) const;


    void setEnable(bool enable);
    bool getEnable(void) const;

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
    Int32 getNumJoints(void) const;
    dJointID getJoint(Int32 index) const;
    std::vector<PhysicsJointUnrecPtr> getJoints(void) const;
    void initDefaults(void);

    //Mass
    void resetMass();
    void setMassParams( Real32 theMass, const Vec3f& cg,
            Real32 I11, Real32 I22, Real32 I33,
            Real32 I12, Real32 I13, Real32 I23 );
    void setSphereMass( Real32 density, Real32 radius );
    void setSphereMassTotal( Real32 totalMass, Real32 radius );
    void setCapsuleMass( Real32 density, Int32 direction,
            Real32 radius, Real32 length );
    void setCapsuleMassTotal( Real32 totalMass, Int32 direction,
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
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const PhysicsBody *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */
    dBodyID _BodyID;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PhysicsBodyBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PhysicsBody &source);
};

typedef PhysicsBody *PhysicsBodyP;

OSG_END_NAMESPACE

#include "OSGPhysicsWorld.h"
#include "OSGPhysicsSpace.h"

#include "OSGPhysicsBodyBase.inl"
#include "OSGPhysicsBody.inl"

#endif /* _OSGPHYSICSBODY_H_ */
