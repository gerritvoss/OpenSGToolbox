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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>
#include "OSGPhysicsConfig.h"

#include "OSGPhysicsBody.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsBody

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsBody::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
/*-------------------------------------------------------------------------*\
-  public                                                                 -
\*-------------------------------------------------------------------------*/
void PhysicsBody::onCreate(const PhysicsBody *)
{
	PhysicsBodyPtr tmpPtr(*this);
	//do not know how to get WorldID to create the bodyid here
    id = 0;
}

void PhysicsBody::onDestroy()
{
	PhysicsBodyPtr tmpPtr(*this);
	if(tmpPtr->id)
    {
		//dBodyDestroy(tmpPtr->id);
        tmpPtr->id =0;
    }
}

/***************************************************************************\
*                              Field Get	                               *
\***************************************************************************/

Vec3f PhysicsBody::getPosition(void)
{
	PhysicsBodyPtr tmpPtr(*this);
	const dReal* tmp = dBodyGetPosition(tmpPtr->id);
	Vec3f v = Vec3f(tmp[0], tmp[1], tmp[2]);
    PhysicsBodyBase::setPosition(v);
    return v;
}

Matrix PhysicsBody::getRotation(void)
{
    
	PhysicsBodyPtr tmpPtr(*this);
	const dReal* tmp = dBodyGetRotation(tmpPtr->id);
	const dMatrix3& rotation = *(const dMatrix3*)tmp;
    
	Matrix M = Matrix(rotation[0],rotation[1], rotation[2],0,
		rotation[4], rotation[5], rotation[6], 0,
		rotation[8], rotation[9], rotation[10], 0,
		0,0,0,1);
    PhysicsBodyBase::setRotation(M);
    return M;
}

Quaternion PhysicsBody::getQuaternion(void)
{
	PhysicsBodyPtr tmpPtr(*this);
	const dReal *t = dBodyGetQuaternion(tmpPtr->id);
	const dQuaternion &q = *(const dQuaternion*)t;
    Quaternion result;
    result.setValueAsQuat(q[1], q[2], q[3], q[0]);
    PhysicsBodyBase::setQuaternion(result);
	return result;
}

Vec3f PhysicsBody::getLinearVel(void)
{
	PhysicsBodyPtr tmpPtr(*this);
	const dReal* tmp = dBodyGetLinearVel(id);
	Vec3f v = Vec3f(tmp[0], tmp[1], tmp[2]);
    PhysicsBodyBase::setLinearVel(v);
    return v;
}

Vec3f PhysicsBody::getAngularVel(void)
{
	PhysicsBodyPtr tmpPtr(*this);
	const dReal* tmp = dBodyGetAngularVel(tmpPtr->id);
	Vec3f v = Vec3f(tmp[0], tmp[1], tmp[2]);
    PhysicsBodyBase::setAngularVel(v);
    return v;
}

Vec3f PhysicsBody::getForce(void)
{
	PhysicsBodyPtr tmpPtr(*this);
	const dReal* tmp = dBodyGetForce(tmpPtr->id);
	Vec3f v = Vec3f(tmp[0], tmp[1], tmp[2]);
    PhysicsBodyBase::setForce(v);
    return v;
}

Vec3f PhysicsBody::getTorque(void)
{
	PhysicsBodyPtr tmpPtr(*this);
	const dReal* tmp = dBodyGetTorque(tmpPtr->id);
	Vec3f v = Vec3f(tmp[0], tmp[1], tmp[2]);
    PhysicsBodyBase::setTorque(v);
    return v;
}

bool PhysicsBody::getEnable(void)
{
	PhysicsBodyPtr tmpPtr(*this);
	return dBodyIsEnabled(tmpPtr->id)==1;
}

Int32 PhysicsBody::getAutoDisableFlag(void)
{
	PhysicsBodyPtr tmpPtr(*this);
	return Int32(dBodyGetAutoDisableFlag(tmpPtr->id));
}

Real32 PhysicsBody::getAutoDisableLinearThreshold(void)
{
	PhysicsBodyPtr tmpPtr(*this);
	return Real32(dBodyGetAutoDisableLinearThreshold(tmpPtr->id));
}

Real32 PhysicsBody::getAutoDisableAngularThreshold(void)
{
	PhysicsBodyPtr tmpPtr(*this);
	return Real32(dBodyGetAutoDisableAngularThreshold(tmpPtr->id));
}

Int32 PhysicsBody::getAutoDisableSteps(void)
{
	PhysicsBodyPtr tmpPtr(*this);
	return Int32(dBodyGetAutoDisableSteps(tmpPtr->id));
}

Real32 PhysicsBody::getAutoDisableTime(void)
{
	PhysicsBodyPtr tmpPtr(*this);
	return (Real32)dBodyGetAutoDisableTime(tmpPtr->id);
}

Int32 PhysicsBody::getFiniteRotationMode(void)
{
	PhysicsBodyPtr tmpPtr(*this);
	return dBodyGetFiniteRotationMode(tmpPtr->id);
}

Vec3f PhysicsBody::getFiniteRotationAxis(void)
{
	PhysicsBodyPtr tmpPtr(*this);
	dVector3 t;
	dBodyGetFiniteRotationAxis(tmpPtr->id, t);
	return Vec3f(t[0], t[1], t[2]);
}

bool PhysicsBody::getGravityMode(void)
{
	PhysicsBodyPtr tmpPtr(*this);
	return dBodyGetGravityMode(tmpPtr->id)==1;
}

dBodyID PhysicsBody::getBodyID(void)
{
    PhysicsBodyPtr tmpPtr(*this);
    return tmpPtr->id;
}

PhysicsWorldPtr PhysicsBody::getWorld(void)
{
    return PhysicsBodyBase::getWorld();
}
/***************************************************************************\
*                              Field Set	                               *
\***************************************************************************/
void PhysicsBody::setWorld(const PhysicsWorldPtr &value)
{
    PhysicsBodyPtr tmpPtr(*this);
    tmpPtr->id = dBodyCreate(value->getWorldID());
    PhysicsBodyBase::setWorld(value);
}

void PhysicsBody::setPosition(const Vec3f &value )
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodySetPosition(tmpPtr->id, value.x(),value.y(),value.z());
	PhysicsBodyBase::setPosition(value);
}

void PhysicsBody::setRotation(const Matrix &value )
{
	PhysicsBodyPtr tmpPtr(*this);
	dMatrix3 rotation;
	Vec4f v1 =  value[0];
	Vec4f v2 =  value[1];
	Vec4f v3 =  value[2];
	rotation[0]   = v1.x();
	rotation[1]   = v1.y();
	rotation[2]   = v1.z();
	rotation[3]   = 0;
	rotation[4]   = v2.x();
	rotation[5]   = v2.y();
	rotation[6]   = v2.z();
	rotation[7]   = 0;
	rotation[8]   = v3.x();
	rotation[9]   = v3.y();
	rotation[10]  = v3.z();
	rotation[11]  = 0;
	dBodySetRotation(tmpPtr->id, rotation);
	PhysicsBodyBase::setRotation(value);
}

void PhysicsBody::setQuaternion(const Quaternion &value )
{
	PhysicsBodyPtr tmpPtr(*this);
	dQuaternion q;
	q[0]=value.w();
	q[1]=value.x();
	q[2]=value.y();
	q[3]=value.z();
	dBodySetQuaternion(tmpPtr->id,q);
	PhysicsBodyBase::setQuaternion(value);
}

void PhysicsBody::setLinearVel(const Vec3f &value )
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodySetLinearVel(tmpPtr->id, value.x(), value.y(), value.z());
	PhysicsBodyBase::setLinearVel(value);
}

void PhysicsBody::setAngularVel(const Vec3f &value )
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodySetAngularVel(tmpPtr->id, value.x(), value.y(), value.z());
	PhysicsBodyBase::setAngularVel(value);
}

void PhysicsBody::setForce(const Vec3f &value )
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodySetForce(tmpPtr->id, value.x(), value.y(), value.z());
	PhysicsBodyBase::setForce(value);
}

void PhysicsBody::setTorque(const Vec3f &value )
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodySetTorque(tmpPtr->id, value.x(), value.y(), value.z());
	PhysicsBodyBase::setTorque(value);
}

void PhysicsBody::setEnable(const bool &value )
{
	PhysicsBodyPtr tmpPtr(*this);
	if(value)
		dBodyEnable(tmpPtr->id);
	else
		dBodyDisable(tmpPtr->id);

	PhysicsBodyBase::setEnable(value);
}


void PhysicsBody::setAutoDisableFlag(const Int32 &value )
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodySetAutoDisableFlag(tmpPtr->id, value);
	PhysicsBodyBase::setAutoDisableFlag(value);
}

void PhysicsBody::setAutoDisableLinearThreshold(const Real32 &value )
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodySetAutoDisableLinearThreshold(tmpPtr->id, value);
	PhysicsBodyBase::setAutoDisableLinearThreshol(value);
}

void PhysicsBody::setAutoDisableAngularThreshold(const Real32 &value )
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodySetAutoDisableAngularThreshold(tmpPtr->id, value);
	PhysicsBodyBase::setAutoDisableAngularThreshol(value);
}

void PhysicsBody::setAutoDisableSteps(const Int32 &value )
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodySetAutoDisableSteps(tmpPtr->id, value);
	PhysicsBodyBase::setAutoDisableSteps(value);
}

void PhysicsBody::setAutoDisableTime(const Real32 &value )
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodySetAutoDisableTime(tmpPtr->id, value);
	PhysicsBodyBase::setAutoDisableTime(value);
}

void PhysicsBody::setFiniteRotationMode(const Int32 &value )
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodySetFiniteRotationMode(tmpPtr->id, value);
	PhysicsBodyBase::setFiniteRotationMode(value);
}

void PhysicsBody::setFiniteRotationAxis(const Vec3f &value )
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodySetFiniteRotationAxis(tmpPtr->id, value.x(), value.y(), value.z());
	PhysicsBodyBase::setFiniteRotationAxis(value);
}

void PhysicsBody::setGravityMode(const bool &value )
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodySetGravityMode(tmpPtr->id, value ? 1:0);
	PhysicsBodyBase::setGravityMode(value);
}

void PhysicsBody::setBodyID(const dBodyID &value)
{
    PhysicsBodyPtr tmpPtr(*this);
    tmpPtr->id = value;
}
/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/
void PhysicsBody::initBody()
{
    setWorld(PhysicsBodyBase::getWorld());
    setPosition(PhysicsBodyBase::getPosition());
    setRotation(PhysicsBodyBase::getRotation());
    setQuaternion(PhysicsBodyBase::getQuaternion());
    setLinearVel(PhysicsBodyBase::getLinearVel());
    setAngularVel(PhysicsBodyBase::getAngularVel());
    setForce(PhysicsBodyBase::getForce());
    setTorque(PhysicsBodyBase::getTorque());
    setEnable(PhysicsBodyBase::getEnable());
    setAutoDisableFlag(PhysicsBodyBase::getAutoDisableFlag());
    setAutoDisableLinearThreshol(PhysicsBodyBase::getAutoDisableLinearThreshol());
    setAutoDisableAngularThreshol(PhysicsBodyBase::getAutoDisableAngularThreshol());
    setAutoDisableSteps(PhysicsBodyBase::getAutoDisableFlag());
    setAutoDisableTime(PhysicsBodyBase::getAutoDisableTime());
    setFiniteRotationMode(PhysicsBodyBase::getFiniteRotationMode());
    setFiniteRotationAxis(PhysicsBodyBase::getFiniteRotationAxis());
    setGravityMode(PhysicsBodyBase::getGravityMode());
}

void PhysicsBody::setMass(const dMass *mass )
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodySetMass(tmpPtr->id, mass);
}

void PhysicsBody::getMass(dMass *mass )
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodyGetMass(tmpPtr->id, mass);
}

void PhysicsBody::addForce(const Vec3f &v)
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodyAddForce(tmpPtr->id,v.x(), v.y(), v.z());
}

void PhysicsBody::addTorque(const Vec3f &v)
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodyAddTorque(tmpPtr->id,v.x(), v.y(), v.z());
}

void PhysicsBody::addForceAtPos(const Vec3f &v, const Vec3f &p)
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodyAddForceAtPos(tmpPtr->id, v.x(), v.y(), v.z(), p.x(), p.y(), p.z());
}

void PhysicsBody::addForceAtRelPos(const Vec3f &v, const Vec3f &p)
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodyAddForceAtRelPos(tmpPtr->id, v.x(), v.y(), v.z(), p.x(), p.y(), p.z());
}

void PhysicsBody::addRelForceAtPos(const Vec3f &v, const Vec3f &p)
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodyAddRelForceAtPos(tmpPtr->id, v.x(), v.y(), v.z(), p.x(), p.y(), p.z());
}

void PhysicsBody::addRelForceAtRelPos(const Vec3f &v, const Vec3f &p)
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodyAddRelForceAtRelPos(tmpPtr->id, v.x(), v.y(), v.z(), p.x(), p.y(), p.z());
}

void PhysicsBody::getRelPointPos(const Vec3f &v, Vec3f &result)
{
	PhysicsBodyPtr tmpPtr(*this);
	dVector3 t;
	dBodyGetRelPointPos(tmpPtr->id, v.x(), v.y(), v.z(), t);
	result.setValue(Vec3f(t[0], t[1], t[2]));
}

void PhysicsBody::getRelPointVel(const Vec3f &v, Vec3f &result)
{
	PhysicsBodyPtr tmpPtr(*this);
	dVector3 t;
	dBodyGetRelPointVel(tmpPtr->id, v.x(), v.y(), v.z(), t);
	result.setValue(Vec3f(t[0], t[1], t[2]));
}

void PhysicsBody::getPointVel(const Vec3f &v, Vec3f &result)
{
	PhysicsBodyPtr tmpPtr(*this);
	dVector3 t;
	dBodyGetPointVel(tmpPtr->id, v.x(), v.y(), v.z(), t);
	result.setValue(Vec3f(t[0], t[1], t[2]));
}

void PhysicsBody::vectorToWorld(const Vec3f &v, Vec3f &result)
{
	PhysicsBodyPtr tmpPtr(*this);
	dVector3 t;
	dBodyVectorToWorld(tmpPtr->id, v.x(), v.y(), v.z(), t);
	result.setValue(Vec3f(t[0], t[1], t[2]));
}

void PhysicsBody::vectorFromWorld(const Vec3f &v, Vec3f &result)
{
	PhysicsBodyPtr tmpPtr(*this);
	dVector3 t;
	dBodyVectorFromWorld(tmpPtr->id, v.x(), v.y(), v.z(), t);
	result.setValue(Vec3f(t[0], t[1], t[2]));
}

void PhysicsBody::setAutoDisableDefaults(void)
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodySetAutoDisableDefaults(tmpPtr->id);
}

void PhysicsBody::setData(void* someData)
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodySetData(tmpPtr->id, someData);
}

void* PhysicsBody::getData(void)
{
	PhysicsBodyPtr tmpPtr(*this);
	return dBodyGetData(tmpPtr->id);
}

Int32 PhysicsBody::getNumJoints(void)
{
	PhysicsBodyPtr tmpPtr(*this);
	return dBodyGetNumJoints(tmpPtr->id);
}

dJointID PhysicsBody::getJoint(Int32 index)
{
	PhysicsBodyPtr tmpPtr(*this);
	return dBodyGetJoint(tmpPtr->id, index);
}
//Mass
void PhysicsBody::resetMass()
{
    PhysicsBodyPtr tmpPtr(*this);
    dMass mass;
    tmpPtr->getMass(&mass);
    dMassSetZero(&mass);
    tmpPtr->setMass(&mass);
}

void PhysicsBody::setMassParams( Real32 theMass, const Vec3f& cg, 
                                Real32 I11, Real32 I22, Real32 I33, 
                                Real32 I12, Real32 I13, Real32 I23 )
{
    PhysicsBodyPtr tmpPtr(*this);
    dMass mass;
    dMassSetParameters(&mass, theMass, cg.x(), cg.y(), cg.z(),
                        I11, I22, I33, I12, I13, I23 );
    tmpPtr->setMass(&mass);
}

void PhysicsBody::setSphereMass( Real32 density, Real32 radius )
{
    PhysicsBodyPtr tmpPtr(*this);
    dMass mass;
    dMassSetSphere(&mass, density, radius);
    tmpPtr->setMass(&mass);
}

void PhysicsBody::setSphereMassTotal( Real32 totalMass, Real32 radius )
{
    PhysicsBodyPtr tmpPtr(*this);
    dMass mass;
    dMassSetSphereTotal(&mass, totalMass, radius);
    tmpPtr->setMass(&mass);
}

void PhysicsBody::setCCylinderMass( Real32 density, Int32 direction, 
                                   Real32 radius, Real32 length )
{
    PhysicsBodyPtr tmpPtr(*this);
    dMass mass;
    dMassSetCappedCylinder(&mass, density, direction, radius, length);
    tmpPtr->setMass(&mass);
}

void PhysicsBody::setCCylinderMassTotal( Real32 totalMass, Int32 direction, 
                                        Real32 radius, Real32 length )
{
    PhysicsBodyPtr tmpPtr(*this);
    dMass mass;
    dMassSetCappedCylinderTotal(&mass, totalMass, direction, radius, length);
    tmpPtr->setMass(&mass);
}

void PhysicsBody::setBoxMass( Real32 density, Real32 lx, Real32 ly, Real32 lz )
{
    PhysicsBodyPtr tmpPtr(*this);
    dMass mass;
    dMassSetBox(&mass, density, lx, ly, lz);
    tmpPtr->setMass(&mass);
}

void PhysicsBody::setBoxMassTotal( Real32 totalMass, Real32 lx, Real32 ly, Real32 lz )
{
    PhysicsBodyPtr tmpPtr(*this);
    dMass mass;
    dMassSetBoxTotal(&mass, totalMass, lx, ly, lz);
    tmpPtr->setMass(&mass);
}

void PhysicsBody::adjustMass( Real32 newMass )
{
    PhysicsBodyPtr tmpPtr(*this);
    dMass mass;
    tmpPtr->getMass(&mass);
    dMassAdjust(&mass, newMass);
    tmpPtr->setMass(&mass);
}

void PhysicsBody::translateMass( const Vec3f& t)
{
    PhysicsBodyPtr tmpPtr(*this);
    dMass mass;
    tmpPtr->getMass(&mass);
    dMassTranslate(&mass, t.x(), t.y(), t.z() );
    tmpPtr->setMass(&mass);
}


void PhysicsBody::rotateMass( const Matrix& R)
{
    dMatrix3 rotation;
    Vec4f v1 =  R[0];
    Vec4f v2 =  R[1];
    Vec4f v3 =  R[2];
    rotation[0]   = v1.x();
    rotation[1]   = v1.y();
    rotation[2]   = v1.z();
    rotation[3]   = 0;
    rotation[4]   = v2.x();
    rotation[5]   = v2.y();
    rotation[6]   = v2.z();
    rotation[7]   = 0;
    rotation[8]   = v3.x();
    rotation[9]   = v3.y();
    rotation[10]  = v3.z();
    rotation[11]  = 0;

    PhysicsBodyPtr tmpPtr(*this);
    dMass mass;
    tmpPtr->getMass(&mass);
    dMassRotate(&mass, rotation);
    tmpPtr->setMass(&mass);
}

void PhysicsBody::addMassOf( dBodyID otherBody )
{
    PhysicsBodyPtr tmpPtr(*this);
    dMass myMass, otherMass;
    tmpPtr->getMass(&myMass);
    dBodyGetMass(otherBody, &otherMass);
    dMassAdd(&myMass, &otherMass);
    tmpPtr->setMass(&myMass);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsBody::PhysicsBody(void) :
    Inherited()
{
}

PhysicsBody::PhysicsBody(const PhysicsBody &source) :
    Inherited(source)
{
}

PhysicsBody::~PhysicsBody(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsBody::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PhysicsBody::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsBody NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPhysicsBody.cpp,v 1.2 2006/08/19 00:21:46 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGPHYSICSBODYBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSBODYBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSBODYFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

