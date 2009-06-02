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

#include "OSGPhysicsUniversalJoint.h"
#include "ODE/OSGPhysicsWorld.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsUniversalJoint

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsUniversalJoint::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
/*-------------------------------------------------------------------------*\
-  public                                                                 -
\*-------------------------------------------------------------------------*/
void PhysicsUniversalJoint::onCreate(const PhysicsUniversalJoint *)
{
	PhysicsUniversalJointPtr tmpPtr(*this);
	//call initJoint!
}

void PhysicsUniversalJoint::onDestroy()
{
	//empty
}

/***************************************************************************\
*                              Field Get	                               *
\***************************************************************************/
Vec3f PhysicsUniversalJoint::getAnchor(void)
{
	PhysicsUniversalJointPtr tmpPtr(*this);
	dVector3 a;
	dJointGetUniversalAnchor(tmpPtr->id, a);
	return Vec3f(a[0], a[1], a[2]);
}

Vec3f PhysicsUniversalJoint::getAxis1(void)
{
	PhysicsUniversalJointPtr tmpPtr(*this);
	dVector3 a;
	dJointGetUniversalAxis1(tmpPtr->id, a);
	return Vec3f(a[0], a[1], a[2]);
}

Vec3f PhysicsUniversalJoint::getAxis2(void)
{
	PhysicsUniversalJointPtr tmpPtr(*this);
	dVector3 a;
	dJointGetUniversalAxis2(tmpPtr->id, a);
	return Vec3f(a[0], a[1], a[2]);
}
/***************************************************************************\
*                              Field Set	                               *
\***************************************************************************/
void PhysicsUniversalJoint::setAnchor(const Vec3f &value )
{
	PhysicsUniversalJointPtr tmpPtr(*this);
	dJointSetUniversalAnchor(tmpPtr->id, value.x(), value.y(), value.z());
	PhysicsUniversalJointBase::setAnchor(value);
}

void PhysicsUniversalJoint::setAxis1(const Vec3f &value )
{
	PhysicsUniversalJointPtr tmpPtr(*this);
	dJointSetUniversalAxis1(tmpPtr->id, value.x(), value.y(), value.z());
	PhysicsUniversalJointBase::setAxis1(value);
}

void PhysicsUniversalJoint::setAxis2(const Vec3f &value )
{
	PhysicsUniversalJointPtr tmpPtr(*this);
	dJointSetUniversalAxis2(tmpPtr->id, value.x(), value.y(), value.z());
	PhysicsUniversalJointBase::setAxis2(value);
}

void PhysicsUniversalJoint::setWorld(const PhysicsWorldPtr &value )
{
    PhysicsUniversalJointPtr tmpPtr(*this);
    tmpPtr->setJointID(dJointCreateUniversal(value->getWorldID(), 0));
    PhysicsJointBase::setWorld(value);
}
/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/
void PhysicsUniversalJoint::initUniversalJoint()
{
    setAnchor(PhysicsUniversalJointBase::getAnchor());
    setAxis1(PhysicsUniversalJointBase::getAxis1());
    setAxis2(PhysicsUniversalJointBase::getAxis2());
    setWorld(PhysicsUniversalJointBase::getWorld());
    initJoint();
}
Vec3f PhysicsUniversalJoint::getAnchor2(void)
{
	PhysicsUniversalJointPtr tmpPtr(*this);
	dVector3 a;
	dJointGetUniversalAnchor2(tmpPtr->id, a);
	return Vec3f(a[0], a[1], a[2]);
}

void PhysicsUniversalJoint::setParam(Int32 param, Real32 value )
{
	PhysicsUniversalJointPtr tmpPtr(*this);
	dJointSetUniversalParam(tmpPtr->id, param, value);
}

Real32 PhysicsUniversalJoint::getParam(Int32 param )
{
	PhysicsUniversalJointPtr tmpPtr(*this);
	return dJointGetUniversalParam(tmpPtr->id, param);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsUniversalJoint::PhysicsUniversalJoint(void) :
    Inherited()
{
}

PhysicsUniversalJoint::PhysicsUniversalJoint(const PhysicsUniversalJoint &source) :
    Inherited(source)
{
}

PhysicsUniversalJoint::~PhysicsUniversalJoint(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsUniversalJoint::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PhysicsUniversalJoint::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsUniversalJoint NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPhysicsUniversalJoint.cpp,v 1.1 2005/10/21 15:44:25 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGPHYSICSUNIVERSALJOINTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSUNIVERSALJOINTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSUNIVERSALJOINTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

