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

#include "OSGPhysicsPlane2DJoint.h"
#include "OSGPhysicsWorld.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPhysicsPlane2DJointBase.cpp file.
// To modify it, please change the .fcd file (OSGPhysicsPlane2DJoint.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsPlane2DJoint::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

PhysicsPlane2DJointUnrecPtr PhysicsPlane2DJoint::create(PhysicsWorldUnrecPtr w)
{
    PhysicsPlane2DJointUnrecPtr fc; 

    if(getClassType().getPrototype() != NULL) 
    {
        fc = dynamic_pointer_cast<PhysicsPlane2DJoint>(
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

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/


void PhysicsPlane2DJoint::onCreate(const PhysicsPlane2DJoint *)
{
}

void PhysicsPlane2DJoint::onDestroy()
{
}

/*----------------------- constructors & destructors ----------------------*/

PhysicsPlane2DJoint::PhysicsPlane2DJoint(void) :
    Inherited()
{
}

PhysicsPlane2DJoint::PhysicsPlane2DJoint(const PhysicsPlane2DJoint &source) :
    Inherited(source)
{
}

PhysicsPlane2DJoint::~PhysicsPlane2DJoint(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsPlane2DJoint::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    //Do not respond to changes that have a Sync origin
    if(origin & ChangedOrigin::Sync)
    {
        return;
    }

    if(whichField & WorldFieldMask)
    {
        if(_JointID)
        {
            dJointDestroy(_JointID);
            _JointID = dJointCreatePlane2D(getWorld()->getWorldID(), 0);
        }
        else
        {
            _JointID = dJointCreatePlane2D(getWorld()->getWorldID(), 0);
        }
    }

    Inherited::changed(whichField, origin, details);
}

void PhysicsPlane2DJoint::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump PhysicsPlane2DJoint NI" << std::endl;
}

OSG_END_NAMESPACE
