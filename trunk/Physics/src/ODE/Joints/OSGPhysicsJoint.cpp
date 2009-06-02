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

#include "OSGPhysicsJoint.h"
#include "ODE/OSGPhysicsBody.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsJoint

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsJoint::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
/*-------------------------------------------------------------------------*\
-  public                                                                 -
\*-------------------------------------------------------------------------*/
void PhysicsJoint::onCreate(const PhysicsJoint *)
{
	PhysicsJointPtr tmpPtr(*this);
	//will be created in subclasses
}

void PhysicsJoint::onDestroy()
{
	PhysicsJointPtr tmpPtr(*this);
	if(tmpPtr->id)
    {
        //dJointDestroy(tmpPtr->id);
        tmpPtr->id = 0;
    }
}

/***************************************************************************\
*                              Field Get	                               *
\***************************************************************************/
dJointID PhysicsJoint::getJointID()
{
    PhysicsJointPtr tmpPtr(*this);
    return tmpPtr->id;
}

/***************************************************************************\
*                              Field Set	                               *
\***************************************************************************/
void PhysicsJoint::setJointID(const dJointID &value)
{
    PhysicsJointPtr tmpPtr(*this);
    tmpPtr->id = value;
}

void PhysicsJoint::setFirstBody(const PhysicsBodyPtr &value )
{
    PhysicsJointPtr tmpPtr(*this);
    if(PhysicsJointBase::getSecondBody()!= NullFC)
        tmpPtr->attachTo(value->getBodyID(), PhysicsJointBase::getSecondBody()->getBodyID());
    PhysicsJointBase::setFirstBody(value);
}

void PhysicsJoint::setSecondBody(const PhysicsBodyPtr &value )
{
    PhysicsJointPtr tmpPtr(*this);
    if(PhysicsJointBase::getFirstBody()!= NullFC)
        tmpPtr->attachTo(value->getBodyID(), PhysicsJointBase::getFirstBody()->getBodyID());
    PhysicsJointBase::setSecondBody(value);
}
/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/
void PhysicsJoint::initJoint()
{
    setFirstBody(PhysicsJointBase::getFirstBody());
    setSecondBody(PhysicsJointBase::getSecondBody());
}
void PhysicsJoint::attachTo( dBodyID body1, dBodyID body2 )
{
	PhysicsJointPtr tmpPtr(*this);
	dJointAttach(tmpPtr->id, body1, body2);
}

void PhysicsJoint::setData( void* someData)
{
	PhysicsJointPtr tmpPtr(*this);
	dJointSetData(tmpPtr->id, someData);
}

void* PhysicsJoint::getData( void)
{
	PhysicsJointPtr tmpPtr(*this);
	return dJointGetData(tmpPtr->id);
}

Int32 PhysicsJoint::getJointType(void)
{
	PhysicsJointPtr tmpPtr(*this);
	return dJointGetType(tmpPtr->id);
}

dBodyID PhysicsJoint::getBody( Int32 i)
{
	PhysicsJointPtr tmpPtr(*this);
	return dJointGetBody(tmpPtr->id, i);
}

void PhysicsJoint::setFeedback( dJointFeedback* feed)
{
	PhysicsJointPtr tmpPtr(*this);
	dJointSetFeedback(tmpPtr->id, feed);
}

dJointFeedback* PhysicsJoint::getFeedback( void)
{
	PhysicsJointPtr tmpPtr(*this);
	return dJointGetFeedback(tmpPtr->id);
}

void PhysicsJoint::setParam( Int32 param, Real32 value )
{
	//pure virtual function
}

Real32 PhysicsJoint::getParam( Int32 param )
{
	//pure virtual function
	return 0.0f;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsJoint::PhysicsJoint(void) :
    Inherited()
{
}

PhysicsJoint::PhysicsJoint(const PhysicsJoint &source) :
    Inherited(source)
{
}

PhysicsJoint::~PhysicsJoint(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsJoint::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PhysicsJoint::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsJoint NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPhysicsJoint.cpp,v 1.1 2005/10/21 15:44:25 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGPHYSICSJOINTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSJOINTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSJOINTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

