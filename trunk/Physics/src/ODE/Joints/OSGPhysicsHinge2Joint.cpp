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

#include "OSGPhysicsHinge2Joint.h"
#include "ODE/OSGPhysicsWorld.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsHinge2Joint

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsHinge2Joint::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
/*-------------------------------------------------------------------------*\
-  public                                                                 -
\*-------------------------------------------------------------------------*/
void PhysicsHinge2Joint::onCreate(const PhysicsHinge2Joint *)
{
	PhysicsHinge2JointPtr tmpPtr(*this);
	//call initJoint!
}

void PhysicsHinge2Joint::onDestroy()
{
	//empty
}

/***************************************************************************\
*                              Field Get	                               *
\***************************************************************************/
Vec3f PhysicsHinge2Joint::getAnchor(void)
{
	PhysicsHinge2JointPtr tmpPtr(*this);
	dVector3 a;
	dJointGetHinge2Anchor(tmpPtr->id, a);
	return Vec3f(a[0], a[1], a[2]);
}

Vec3f PhysicsHinge2Joint::getAxis1(void)
{
	PhysicsHinge2JointPtr tmpPtr(*this);
	dVector3 a;
	dJointGetHinge2Axis1(tmpPtr->id, a);
	return Vec3f(a[0], a[1], a[2]);
}

Vec3f PhysicsHinge2Joint::getAxis2(void)
{
	PhysicsHinge2JointPtr tmpPtr(*this);
	dVector3 a;
	dJointGetHinge2Axis2(tmpPtr->id, a);
	return Vec3f(a[0], a[1], a[2]);
}
/***************************************************************************\
*                              Field Set	                               *
\***************************************************************************/
void PhysicsHinge2Joint::setAnchor(const Vec3f &value )
{
	PhysicsHinge2JointPtr tmpPtr(*this);
	dJointSetHinge2Anchor(tmpPtr->id, value.x(), value.y(), value.z());
	PhysicsHinge2JointBase::setAnchor(value);
}

void PhysicsHinge2Joint::setAxis1(const Vec3f &value )
{
	PhysicsHinge2JointPtr tmpPtr(*this);
	dJointSetHinge2Axis1(tmpPtr->id, value.x(), value.y(), value.z());
	PhysicsHinge2JointBase::setAxis1(value);
}

void PhysicsHinge2Joint::setAxis2(const Vec3f &value )
{
	PhysicsHinge2JointPtr tmpPtr(*this);
	dJointSetHinge2Axis2(tmpPtr->id, value.x(), value.y(), value.z());
	PhysicsHinge2JointBase::setAxis2(value);
}

void PhysicsHinge2Joint::setWorld(const PhysicsWorldPtr &value )
{
    PhysicsHinge2JointPtr tmpPtr(*this);
    tmpPtr->id = dJointCreateHinge2(value->getWorldID(), 0);
    PhysicsJointBase::setWorld(value);
}
/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/
void PhysicsHinge2Joint::initHinge2Joint()
{
    setAnchor(PhysicsHinge2JointBase::getAnchor());
    setAxis1(PhysicsHinge2JointBase::getAxis1());
    setAxis2(PhysicsHinge2JointBase::getAxis2());
    setWorld(PhysicsHinge2JointBase::getWorld());
    initJoint();
}
Vec3f PhysicsHinge2Joint::getAnchor2(void)
{
	PhysicsHinge2JointPtr tmpPtr(*this);
	dVector3 a;
	dJointGetHinge2Anchor2(tmpPtr->id, a);
	return Vec3f(a[0], a[1], a[2]);
}

Real32 PhysicsHinge2Joint::getAngle1(void)
{
	PhysicsHinge2JointPtr tmpPtr(*this);
	return dJointGetHinge2Angle1(tmpPtr->id);
}

Real32 PhysicsHinge2Joint::getAngle1Rate(void)
{
	PhysicsHinge2JointPtr tmpPtr(*this);
	return dJointGetHinge2Angle1Rate(tmpPtr->id);
}

Real32 PhysicsHinge2Joint::getAngle2Rate(void)
{
	PhysicsHinge2JointPtr tmpPtr(*this);
	return dJointGetHinge2Angle2Rate(tmpPtr->id);
}

void PhysicsHinge2Joint::setParam(Int32 param, Real32 value )
{
	PhysicsHinge2JointPtr tmpPtr(*this);
	dJointSetHinge2Param(tmpPtr->id, param, value);
}

Real32 PhysicsHinge2Joint::getParam(Int32 param )
{
	PhysicsHinge2JointPtr tmpPtr(*this);
	return dJointGetHinge2Param(tmpPtr->id, param);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsHinge2Joint::PhysicsHinge2Joint(void) :
    Inherited()
{
}

PhysicsHinge2Joint::PhysicsHinge2Joint(const PhysicsHinge2Joint &source) :
    Inherited(source)
{
}

PhysicsHinge2Joint::~PhysicsHinge2Joint(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsHinge2Joint::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PhysicsHinge2Joint::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsHinge2Joint NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPhysicsHinge2Joint.cpp,v 1.1 2005/10/21 15:44:25 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGPHYSICSHINGE2JOINTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSHINGE2JOINTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSHINGE2JOINTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

