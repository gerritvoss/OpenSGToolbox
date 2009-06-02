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
#include "OSGPhysicsDef.h"

#include "OSGPhysicsHingeJoint.h"
#include "ODE/OSGPhysicsWorld.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsHingeJoint

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsHingeJoint::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
/*-------------------------------------------------------------------------*\
-  public                                                                 -
\*-------------------------------------------------------------------------*/
void PhysicsHingeJoint::onCreate(const PhysicsHingeJoint *)
{
	PhysicsHingeJointPtr tmpPtr(*this);
	//call initJoint!
}

void PhysicsHingeJoint::onDestroy()
{
	//empty
}

/***************************************************************************\
*                              Field Get	                               *
\***************************************************************************/
Vec3f PhysicsHingeJoint::getAnchor(void)
{
	PhysicsHingeJointPtr tmpPtr(*this);
	dVector3 a;
	dJointGetHingeAnchor(tmpPtr->id, a);
	return Vec3f(a[0], a[1], a[2]);
}

Vec3f PhysicsHingeJoint::getAxis(void)
{
	PhysicsHingeJointPtr tmpPtr(*this);
	dVector3 a;
	dJointGetHingeAxis(tmpPtr->id, a);
	return Vec3f(a[0], a[1], a[2]);
}
/***************************************************************************\
*                              Field Set	                               *
\***************************************************************************/
void PhysicsHingeJoint::setAnchor(const Vec3f &value )
{
	PhysicsHingeJointPtr tmpPtr(*this);
	dJointSetHingeAnchor(tmpPtr->id, value.x(), value.y(), value.z());
	PhysicsHingeJointBase::setAnchor(value);
}

void PhysicsHingeJoint::setAxis(const Vec3f &value )
{
	PhysicsHingeJointPtr tmpPtr(*this);
	dJointSetHingeAxis(tmpPtr->id, value.x(), value.y(), value.z());
	PhysicsHingeJointBase::setAxis(value);
}

void PhysicsHingeJoint::setWorld(const PhysicsWorldPtr &value )
{
    PhysicsHingeJointPtr tmpPtr(*this);
    tmpPtr->id = dJointCreateHinge(value->getWorldID(), 0);
    PhysicsJointBase::setWorld(value);
}
/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/
void PhysicsHingeJoint::initHingeJoint()
{
    setAnchor(PhysicsHingeJointBase::getAnchor());
    setAxis(PhysicsHingeJointBase::getAxis());
    setWorld(PhysicsHingeJointBase::getWorld());
    initJoint();
}
Vec3f PhysicsHingeJoint::getAnchor2(void)
{
	PhysicsHingeJointPtr tmpPtr(*this);
	dVector3 a;
	dJointGetHingeAnchor2(tmpPtr->id, a);
	return Vec3f(a[0], a[1], a[2]);
}

Real32 PhysicsHingeJoint::getAngle(void)
{
	PhysicsHingeJointPtr tmpPtr(*this);
	return dJointGetHingeAngle(tmpPtr->id);
}

Real32 PhysicsHingeJoint::getAngleRate(void)
{
	PhysicsHingeJointPtr tmpPtr(*this);
	return dJointGetHingeAngleRate(tmpPtr->id);
}

void PhysicsHingeJoint::setParam(Int32 param, Real32 value )
{
	PhysicsHingeJointPtr tmpPtr(*this);
	dJointSetHingeParam(tmpPtr->id, param, value);
}

Real32 PhysicsHingeJoint::getParam(Int32 param )
{
	PhysicsHingeJointPtr tmpPtr(*this);
	return dJointGetHingeParam(tmpPtr->id, param);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsHingeJoint::PhysicsHingeJoint(void) :
    Inherited()
{
}

PhysicsHingeJoint::PhysicsHingeJoint(const PhysicsHingeJoint &source) :
    Inherited(source)
{
}

PhysicsHingeJoint::~PhysicsHingeJoint(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsHingeJoint::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PhysicsHingeJoint::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsHingeJoint NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPhysicsHingeJoint.cpp,v 1.1 2005/10/21 15:44:25 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGPHYSICSHINGEJOINTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSHINGEJOINTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSHINGEJOINTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

