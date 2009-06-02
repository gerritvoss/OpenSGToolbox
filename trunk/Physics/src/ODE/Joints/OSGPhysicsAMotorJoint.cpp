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

#include "OSGPhysicsAMotorJoint.h"
#include "ODE/OSGPhysicsWorld.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsAMotorJoint

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsAMotorJoint::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
/*-------------------------------------------------------------------------*\
-  public                                                                 -
\*-------------------------------------------------------------------------*/
void PhysicsAMotorJoint::onCreate(const PhysicsAMotorJoint *)
{
	PhysicsAMotorJointPtr tmpPtr(*this);
	//call initJoint!
}

void PhysicsAMotorJoint::onDestroy()
{
	//empty
}
/***************************************************************************\
*                              Field Get	                               *
\***************************************************************************/
Int32 PhysicsAMotorJoint::getMode(void)
{
	PhysicsAMotorJointPtr tmpPtr(*this);
	return dJointGetAMotorMode(tmpPtr->id);
}

Int32 PhysicsAMotorJoint::getNumAxes(void)
{
	PhysicsAMotorJointPtr tmpPtr(*this);
	return dJointGetAMotorNumAxes(tmpPtr->id);
}
/***************************************************************************\
*                              Field Set	                               *
\***************************************************************************/
void PhysicsAMotorJoint::setMode(const Int32 &value )
{
	PhysicsAMotorJointPtr tmpPtr(*this);
	dJointSetAMotorMode(tmpPtr->id, value);
	PhysicsAMotorJointBase::setMode(value);
}

void PhysicsAMotorJoint::setNumAxes(const Int32 &value )
{
	PhysicsAMotorJointPtr tmpPtr(*this);
	dJointSetAMotorNumAxes(tmpPtr->id, value);
	PhysicsAMotorJointBase::setNumAxes(value);
}

void PhysicsAMotorJoint::setWorld(const PhysicsWorldPtr &value )
{
    PhysicsAMotorJointPtr tmpPtr(*this);
    tmpPtr->setJointID(dJointCreateAMotor(value->getWorldID(), 0));
    PhysicsJointBase::setWorld(value);
}
/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/
void PhysicsAMotorJoint::initAMotorJoint()
{
    setMode(PhysicsAMotorJointBase::getMode());
    setNumAxes(PhysicsAMotorJointBase::getNumAxes());
    setWorld(PhysicsAMotorJointBase::getWorld());
    initJoint();
}
void PhysicsAMotorJoint::setAxis(Int32 anum, Int32 rel, const Vec3f& axis)
{
	PhysicsAMotorJointPtr tmpPtr(*this);
	dJointSetAMotorAxis(tmpPtr->id, anum, rel, axis.x(), axis.y(), axis.z());
}

void PhysicsAMotorJoint::getAxis(Int32 anum, Vec3f& result)
{
	PhysicsAMotorJointPtr tmpPtr(*this);
	dVector3 res;
	dJointGetAMotorAxis(tmpPtr->id, anum, res);
	result.setValue(Vec3f(res[0], res[1], res[2]));
}

Int32 PhysicsAMotorJoint::getAxisRel(Int32 anum)
{
	PhysicsAMotorJointPtr tmpPtr(*this);
	return dJointGetAMotorAxisRel(tmpPtr->id, anum);
}

void PhysicsAMotorJoint::setAngle(Int32 anum, Real32 angle)
{
	PhysicsAMotorJointPtr tmpPtr(*this);
	dJointSetAMotorAngle(tmpPtr->id, anum, angle);
}

Real32 PhysicsAMotorJoint::getAngle(Int32 anum)
{
	PhysicsAMotorJointPtr tmpPtr(*this);
	return dJointGetAMotorAngle(tmpPtr->id, anum);
}

Real32 PhysicsAMotorJoint::getAngleRate(Int32 anum)
{
	PhysicsAMotorJointPtr tmpPtr(*this);
	return dJointGetAMotorAngleRate(tmpPtr->id, anum);
}

void PhysicsAMotorJoint::setParam(Int32 param, Real32 value )
{
	PhysicsAMotorJointPtr tmpPtr(*this);
	dJointSetAMotorParam(tmpPtr->id, param, value);
}

Real32 PhysicsAMotorJoint::getParam(Int32 param )
{
	PhysicsAMotorJointPtr tmpPtr(*this);
	return dJointGetAMotorParam(tmpPtr->id, param);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsAMotorJoint::PhysicsAMotorJoint(void) :
    Inherited()
{
}

PhysicsAMotorJoint::PhysicsAMotorJoint(const PhysicsAMotorJoint &source) :
    Inherited(source)
{
}

PhysicsAMotorJoint::~PhysicsAMotorJoint(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsAMotorJoint::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PhysicsAMotorJoint::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsAMotorJoint NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPhysicsAMotorJoint.cpp,v 1.1 2005/10/21 15:44:24 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGPHYSICSAMOTORJOINTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSAMOTORJOINTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSAMOTORJOINTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

