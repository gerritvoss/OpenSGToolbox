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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGPhysicsJoint.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPhysicsJointBase.cpp file.
// To modify it, please change the .fcd file (OSGPhysicsJoint.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsJoint::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

dJointID PhysicsJoint::getJointID()
{
    return _JointID;
}

void PhysicsJoint::setJointID(const dJointID &value)
{
    _JointID = value;
}

void PhysicsJoint::setData( void* someData)
{
	dJointSetData(_JointID, someData);
}

void* PhysicsJoint::getData( void)
{
	return dJointGetData(_JointID);
}

Int32 PhysicsJoint::getJointType(void)
{
	return dJointGetType(_JointID);
}

dBodyID PhysicsJoint::getBody( Int32 i)
{
	return dJointGetBody(_JointID, i);
}

void PhysicsJoint::setFeedback( dJointFeedback* feed)
{
	dJointSetFeedback(_JointID, feed);
}

dJointFeedback* PhysicsJoint::getFeedback( void)
{
	return dJointGetFeedback(_JointID);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void PhysicsJoint::onCreate(const PhysicsJoint *)
{
	//will be created in subclasses
}

void PhysicsJoint::onDestroy()
{
	if(_JointID)
    {
        //dJointDestroy(_JointID);
        _JointID = 0;
    }
}
/*----------------------- constructors & destructors ----------------------*/

PhysicsJoint::PhysicsJoint(void) :
    Inherited(),
    _JointID(0)
{
}

PhysicsJoint::PhysicsJoint(const PhysicsJoint &source) :
    Inherited(source),
    _JointID(0)
{
}

PhysicsJoint::~PhysicsJoint(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsJoint::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
    
    if(((whichField & FirstBodyFieldMask) || (whichField & WorldFieldMask)) ||
       ((whichField & SecondBodyFieldMask) || (whichField & WorldFieldMask)))
    {
        dBodyID First(NULL);
        dBodyID Second(NULL);
        if(getFirstBody() != NULL)
        {
            First = getFirstBody()->getBodyID();
        }
        if(getSecondBody() != NULL)
        {
            Second = getSecondBody()->getBodyID();
        }
        dJointAttach(_JointID, First, Second);
    }
}

void PhysicsJoint::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump PhysicsJoint NI" << std::endl;
}

OSG_END_NAMESPACE
