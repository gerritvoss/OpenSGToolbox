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

#include "OSGPhysicsBallJoint.h"
#include "ODE/OSGPhysicsWorld.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsBallJoint

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsBallJoint::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
/*-------------------------------------------------------------------------*\
-  public                                                                 -
\*-------------------------------------------------------------------------*/
void PhysicsBallJoint::onCreate(const PhysicsBallJoint *)
{
	PhysicsBallJointPtr tmpPtr(*this);
	//call initJoint!
}

void PhysicsBallJoint::onDestroy()
{
	//empty
}

/***************************************************************************\
*                              Field Get	                               *
\***************************************************************************/
Vec3f PhysicsBallJoint::getAnchor(void)
{
	PhysicsBallJointPtr tmpPtr(*this);
	dVector3 a;
	dJointGetBallAnchor(tmpPtr->id, a);
	return Vec3f(a[0], a[1], a[2]);
}


/***************************************************************************\
*                              Field Set	                               *
\***************************************************************************/
void PhysicsBallJoint::setAnchor(const Vec3f &value )
{
	PhysicsBallJointPtr tmpPtr(*this);
	dJointSetBallAnchor(tmpPtr->id, value.x(), value.y(), value.z());
	PhysicsBallJointBase::setAnchor(value);
}

void PhysicsBallJoint::setWorld(const PhysicsWorldPtr &value )
{
    PhysicsBallJointPtr tmpPtr(*this);
    tmpPtr->setJointID(dJointCreateBall(value->getWorldID(), 0));
    PhysicsJointBase::setWorld(value);
}
/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/
void PhysicsBallJoint::initBallJoint()
{
    setAnchor(PhysicsBallJointBase::getAnchor());
    setWorld(PhysicsBallJointBase::getWorld());
    initJoint();
}
Vec3f PhysicsBallJoint::getAnchor2(void)
{
	PhysicsBallJointPtr tmpPtr(*this);
	dVector3 a;
	dJointGetBallAnchor2(tmpPtr->id, a);
	return Vec3f(a[0], a[1], a[2]);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsBallJoint::PhysicsBallJoint(void) :
    Inherited()
{
}

PhysicsBallJoint::PhysicsBallJoint(const PhysicsBallJoint &source) :
    Inherited(source)
{
}

PhysicsBallJoint::~PhysicsBallJoint(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsBallJoint::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PhysicsBallJoint::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsBallJoint NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPhysicsBallJoint.cpp,v 1.1 2005/10/21 15:44:24 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGPHYSICSBALLJOINTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSBALLJOINTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSBALLJOINTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

