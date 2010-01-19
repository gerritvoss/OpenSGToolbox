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

#include "OSGPhysicsBallJoint.h"
#include "OSGPhysicsWorld.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPhysicsBallJointBase.cpp file.
// To modify it, please change the .fcd file (OSGPhysicsBallJoint.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsBallJoint::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


PhysicsBallJointUnrecPtr PhysicsBallJoint::create(PhysicsWorldUnrecPtr w)
{
    PhysicsBallJointUnrecPtr fc; 

    if(getClassType().getPrototype() != NULL) 
    {
        fc = dynamic_pointer_cast<PhysicsBallJoint>(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    if(fc != NULL)
    {
        fc->setWorld(w);
    }
    
    return fc; 
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Vec3f PhysicsBallJoint::getAnchor2(void)
{
	dVector3 a;
	dJointGetBallAnchor2(_JointID, a);
	return Vec3f(a[0], a[1], a[2]);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void PhysicsBallJoint::onCreate(const PhysicsBallJoint *)
{
	//call initJoint!
}

void PhysicsBallJoint::onDestroy()
{
	//empty
}

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

void PhysicsBallJoint::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    if(whichField & WorldFieldMask)
    {
        if(_JointID)
        {
            dJointDestroy(_JointID);
        }
        _JointID = dJointCreateBall(getWorld()->getWorldID(), 0);
    }

    Inherited::changed(whichField, origin, details);

    if((whichField & AnchorFieldMask) || (whichField & WorldFieldMask))
    {
	    dJointSetBallAnchor(_JointID, getAnchor().x(), getAnchor().y(), getAnchor().z());
    }
}

void PhysicsBallJoint::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump PhysicsBallJoint NI" << std::endl;
}

OSG_END_NAMESPACE
