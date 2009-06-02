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

#include "OSGPhysicsSliderJoint.h"
#include "ODE/OSGPhysicsWorld.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsSliderJoint

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsSliderJoint::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
/*-------------------------------------------------------------------------*\
-  public                                                                 -
\*-------------------------------------------------------------------------*/
void PhysicsSliderJoint::onCreate(const PhysicsSliderJoint *)
{
	PhysicsSliderJointPtr tmpPtr(*this);
	//call initJoint!
}

void PhysicsSliderJoint::onDestroy()
{
	//empty
}

/***************************************************************************\
*                              Field Get	                               *
\***************************************************************************/

Vec3f PhysicsSliderJoint::getAxis(void)
{
	PhysicsSliderJointPtr tmpPtr(*this);
	dVector3 a;
	dJointGetSliderAxis(tmpPtr->id, a);
	return Vec3f(a[0], a[1], a[2]);
}
/***************************************************************************\
*                              Field Set	                               *
\***************************************************************************/

void PhysicsSliderJoint::setAxis(const Vec3f &value )
{
	PhysicsSliderJointPtr tmpPtr(*this);
	dJointSetSliderAxis(tmpPtr->id, value.x(), value.y(), value.z());
	//PhysicsJointBase::setAxis(value);
}

void PhysicsSliderJoint::setWorld(const PhysicsWorldPtr &value )
{
    PhysicsSliderJointPtr tmpPtr(*this);
    tmpPtr->setJointID(dJointCreateSlider(value->getWorldID(), 0));
    PhysicsJointBase::setWorld(value);
}
/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/
void PhysicsSliderJoint::initSliderJoint()
{
    setAxis(PhysicsSliderJointBase::getAxis());
    setWorld(PhysicsSliderJointBase::getWorld());
    initJoint();
}

Real32 PhysicsSliderJoint::getPosition(void)
{
	PhysicsSliderJointPtr tmpPtr(*this);
	return dJointGetSliderPosition(tmpPtr->id);
}

Real32 PhysicsSliderJoint::getPositionRate(void)
{
	PhysicsSliderJointPtr tmpPtr(*this);
	return dJointGetSliderPositionRate(tmpPtr->id);
}

void PhysicsSliderJoint::setParam(Int32 param, Real32 value )
{
	PhysicsSliderJointPtr tmpPtr(*this);
	dJointSetSliderParam(tmpPtr->id, param, value);
}

Real32 PhysicsSliderJoint::getParam(Int32 param )
{
	PhysicsSliderJointPtr tmpPtr(*this);
	return dJointGetSliderParam(tmpPtr->id, param);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsSliderJoint::PhysicsSliderJoint(void) :
    Inherited()
{
}

PhysicsSliderJoint::PhysicsSliderJoint(const PhysicsSliderJoint &source) :
    Inherited(source)
{
}

PhysicsSliderJoint::~PhysicsSliderJoint(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsSliderJoint::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PhysicsSliderJoint::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsSliderJoint NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPhysicsSliderJoint.cpp,v 1.1 2005/10/21 15:44:25 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGPHYSICSSLIDERJOINTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSSLIDERJOINTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSSLIDERJOINTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

