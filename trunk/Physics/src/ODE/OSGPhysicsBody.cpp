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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>
#include "OSGPhysicsDef.h"

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

//! create a new instance of the class
PhysicsBodyPtr PhysicsBody::create(PhysicsWorldPtr World) 
{
    PhysicsBodyPtr fc; 

    if(getClassType().getPrototype() != OSG::NullFC) 
    {
        fc = PhysicsBodyPtr::dcast(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    if(fc != NullFC)
    {
        beginEditCP(fc, WorldFieldMask);
            fc->setWorld(World);
        endEditCP(fc, WorldFieldMask);

        fc->initDefaults();
    }
    
    return fc; 
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
    _BodyID = 0;
}

void PhysicsBody::onDestroy()
{
	if(_BodyID)
    {
		dBodyDestroy(_BodyID);
        _BodyID =0;
    }
}

/***************************************************************************\
*                              Field Get	                               *
\***************************************************************************/

dBodyID PhysicsBody::getBodyID(void)
{
    PhysicsBodyPtr tmpPtr(*this);
    return tmpPtr->_BodyID;
}

/***************************************************************************\
*                              Field Set	                               *
\***************************************************************************/

void PhysicsBody::setBodyID(const dBodyID &value)
{
    PhysicsBodyPtr tmpPtr(*this);
    tmpPtr->_BodyID = value;
}

/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/
void PhysicsBody::initDefaults(void)
{
    setAutoDisableFlag(dBodyGetAutoDisableFlag(_BodyID));
    setAutoDisableLinearThreshold(dBodyGetAutoDisableLinearThreshold(_BodyID));
    setAutoDisableAngularThreshold(dBodyGetAutoDisableAngularThreshold(_BodyID));
    setAutoDisableSteps(dBodyGetAutoDisableSteps(_BodyID));
    setAutoDisableTime(dBodyGetAutoDisableTime(_BodyID));
    setFiniteRotationMode(dBodyGetFiniteRotationMode(_BodyID));
    dVector3 odeVec;
    dBodyGetFiniteRotationAxis(_BodyID, odeVec);
    setFiniteRotationAxis(Vec3f(odeVec[0], odeVec[1], odeVec[3]));
    setGravityMode(dBodyGetGravityMode(_BodyID));
}

void PhysicsBody::setMass(const dMass *mass )
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodySetMass(tmpPtr->_BodyID, mass);
}

void PhysicsBody::getMass(dMass *mass )
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodyGetMass(tmpPtr->_BodyID, mass);
}

void PhysicsBody::addForce(const Vec3f &v)
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodyAddForce(tmpPtr->_BodyID,v.x(), v.y(), v.z());
}

void PhysicsBody::addTorque(const Vec3f &v)
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodyAddTorque(tmpPtr->_BodyID,v.x(), v.y(), v.z());
}

void PhysicsBody::addRelForce(const Vec3f &v)
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodyAddRelForce(tmpPtr->_BodyID,v.x(), v.y(), v.z());
}

void PhysicsBody::addRelTorque(const Vec3f &v)
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodyAddRelTorque(tmpPtr->_BodyID,v.x(), v.y(), v.z());
}

void PhysicsBody::addForceAtPos(const Vec3f &v, const Vec3f &p)
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodyAddForceAtPos(tmpPtr->_BodyID, v.x(), v.y(), v.z(), p.x(), p.y(), p.z());
}

void PhysicsBody::addForceAtRelPos(const Vec3f &v, const Vec3f &p)
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodyAddForceAtRelPos(tmpPtr->_BodyID, v.x(), v.y(), v.z(), p.x(), p.y(), p.z());
}

void PhysicsBody::addRelForceAtPos(const Vec3f &v, const Vec3f &p)
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodyAddRelForceAtPos(tmpPtr->_BodyID, v.x(), v.y(), v.z(), p.x(), p.y(), p.z());
}

void PhysicsBody::addRelForceAtRelPos(const Vec3f &v, const Vec3f &p)
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodyAddRelForceAtRelPos(tmpPtr->_BodyID, v.x(), v.y(), v.z(), p.x(), p.y(), p.z());
}

void PhysicsBody::getRelPointPos(const Vec3f &v, Vec3f &result)
{
	PhysicsBodyPtr tmpPtr(*this);
	dVector3 t;
	dBodyGetRelPointPos(tmpPtr->_BodyID, v.x(), v.y(), v.z(), t);
	result.setValue(Vec3f(t[0], t[1], t[2]));
}

void PhysicsBody::getRelPointVel(const Vec3f &v, Vec3f &result)
{
	PhysicsBodyPtr tmpPtr(*this);
	dVector3 t;
	dBodyGetRelPointVel(tmpPtr->_BodyID, v.x(), v.y(), v.z(), t);
	result.setValue(Vec3f(t[0], t[1], t[2]));
}

void PhysicsBody::getPointVel(const Vec3f &v, Vec3f &result)
{
	PhysicsBodyPtr tmpPtr(*this);
	dVector3 t;
	dBodyGetPointVel(tmpPtr->_BodyID, v.x(), v.y(), v.z(), t);
	result.setValue(Vec3f(t[0], t[1], t[2]));
}

void PhysicsBody::vectorToWorld(const Vec3f &v, Vec3f &result)
{
	PhysicsBodyPtr tmpPtr(*this);
	dVector3 t;
	dBodyVectorToWorld(tmpPtr->_BodyID, v.x(), v.y(), v.z(), t);
	result.setValue(Vec3f(t[0], t[1], t[2]));
}

void PhysicsBody::vectorFromWorld(const Vec3f &v, Vec3f &result)
{
	PhysicsBodyPtr tmpPtr(*this);
	dVector3 t;
	dBodyVectorFromWorld(tmpPtr->_BodyID, v.x(), v.y(), v.z(), t);
	result.setValue(Vec3f(t[0], t[1], t[2]));
}

void PhysicsBody::setAutoDisableDefaults(void)
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodySetAutoDisableDefaults(tmpPtr->_BodyID);
}

void PhysicsBody::setData(void* someData)
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodySetData(tmpPtr->_BodyID, someData);
}

void* PhysicsBody::getData(void)
{
	PhysicsBodyPtr tmpPtr(*this);
	return dBodyGetData(tmpPtr->_BodyID);
}

Int32 PhysicsBody::getNumJoints(void)
{
	PhysicsBodyPtr tmpPtr(*this);
	return dBodyGetNumJoints(tmpPtr->_BodyID);
}

dJointID PhysicsBody::getJoint(Int32 index)
{
	PhysicsBodyPtr tmpPtr(*this);
	return dBodyGetJoint(tmpPtr->_BodyID, index);
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

//Damping
void PhysicsBody::setDampingDefaults (void)
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodySetDampingDefaults(tmpPtr->_BodyID);
}

void PhysicsBody::setDamping (Real32 linear_scale, Real32 angular_scale)
{
	PhysicsBodyPtr tmpPtr(*this);
	dBodySetDamping(tmpPtr->_BodyID, linear_scale, angular_scale);
}

void PhysicsBody::updateToODEState(void)
{
    const dReal* pos(dBodyGetPosition(_BodyID));
    const dReal* quat(dBodyGetQuaternion(_BodyID));

    setPosition(Vec3f(pos[0], pos[1], pos[2]));
    Quaternion osgQuat;
    osgQuat.setValueAsQuat(quat[1], quat[2], quat[3], quat[0]);
    setQuaternion(osgQuat);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsBody::PhysicsBody(void) :
    Inherited(),
        _BodyID(0)
{
}

PhysicsBody::PhysicsBody(const PhysicsBody &source) :
    Inherited(source),
        _BodyID(0)
{
}

PhysicsBody::~PhysicsBody(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsBody::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & WorldFieldMask)
    {
        if(_BodyID != 0)
        {
            dBodyDestroy(_BodyID);
        }

        if(getWorld() != NullFC)
        {
            _BodyID = dBodyCreate(getWorld()->getWorldID());
        }
    }
    if(whichField & PositionFieldMask)
    {
	    dBodySetPosition(_BodyID, getPosition().x(),getPosition().y(),getPosition().z());
    }
    if(whichField & RotationFieldMask)
    {
	    dMatrix3 rotation;
	    Vec4f v1 =  getRotation()[0];
	    Vec4f v2 =  getRotation()[1];
	    Vec4f v3 =  getRotation()[2];
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
	    dBodySetRotation(_BodyID, rotation);
    }
    if(whichField & QuaternionFieldMask)
    {
	    dQuaternion q;
	    q[0]=getQuaternion().w();
	    q[1]=getQuaternion().x();
	    q[2]=getQuaternion().y();
	    q[3]=getQuaternion().z();
	    dBodySetQuaternion(_BodyID,q);
    }
    if(whichField & LinearVelFieldMask)
    {
	    dBodySetLinearVel(_BodyID, getLinearVel().x(),getLinearVel().y(),getLinearVel().z());
    }
    if(whichField & AngularVelFieldMask)
    {
	    dBodySetAngularVel(_BodyID, getAngularVel().x(),getAngularVel().y(),getAngularVel().z());
    }
    if(whichField & ForceFieldMask)
    {
	    dBodySetForce(_BodyID, getForce().x(),getForce().y(),getForce().z());
    }
    if(whichField & TorqueFieldMask)
    {
	    dBodySetTorque(_BodyID, getTorque().x(),getTorque().y(),getTorque().z());
    }
    if(whichField & EnableFieldMask)
    {
	    if(getEnable())
		    dBodyEnable(_BodyID);
	    else
		    dBodyDisable(_BodyID);
    }
    if(whichField & AutoDisableFlagFieldMask)
    {
	    dBodySetAutoDisableFlag(_BodyID, getAutoDisableFlag());
    }
    if(whichField & AutoDisableLinearThresholdFieldMask)
    {
	    dBodySetAutoDisableLinearThreshold(_BodyID, getAutoDisableLinearThreshold());
    }
    if(whichField & AutoDisableAngularThresholdFieldMask)
    {
	    dBodySetAutoDisableAngularThreshold(_BodyID, getAutoDisableAngularThreshold());
    }
    if(whichField & AutoDisableStepsFieldMask)
    {
	    dBodySetAutoDisableSteps(_BodyID, getAutoDisableSteps());
    }
    if(whichField & AutoDisableTimeFieldMask)
    {
	    dBodySetAutoDisableTime(_BodyID, getAutoDisableTime());
    }
    if(whichField & FiniteRotationModeFieldMask)
    {
	    dBodySetFiniteRotationMode(_BodyID, getFiniteRotationMode());
    }
    if(whichField & FiniteRotationModeFieldMask)
    {
	    dBodySetFiniteRotationMode(_BodyID, getFiniteRotationMode());
    }
    if(whichField & FiniteRotationAxisFieldMask)
    {
	    dBodySetFiniteRotationAxis(_BodyID, getFiniteRotationAxis().x(),getFiniteRotationAxis().y(),getFiniteRotationAxis().z());
    }
    if(whichField & GravityModeFieldMask)
    {
	    dBodySetFiniteRotationMode(_BodyID, getGravityMode());
    }
    if(whichField & LinearDampingFieldMask)
    {
	    dBodySetLinearDamping(_BodyID, getLinearDamping());
    }
    if(whichField & AngularDampingFieldMask)
    {
	    dBodySetAngularDamping(_BodyID, getAngularDamping());
    }
    if(whichField & LinearDampingThresholdFieldMask)
    {
	    dBodySetLinearDampingThreshold(_BodyID, getLinearDampingThreshold());
    }
    if(whichField & AngularDampingThresholdFieldMask)
    {
	    dBodySetAngularDampingThreshold(_BodyID, getAngularDampingThreshold());
    }
    if(whichField & MaxAngularSpeedFieldMask)
    {
	    dBodySetMaxAngularSpeed(_BodyID, getMaxAngularSpeed());
    }
}

void PhysicsBody::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsBody NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs _BodyID's                                  */

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

