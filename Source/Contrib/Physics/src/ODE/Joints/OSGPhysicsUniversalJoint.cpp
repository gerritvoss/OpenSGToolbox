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

#include "OSGPhysicsUniversalJoint.h"
#include "OSGPhysicsWorld.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPhysicsUniversalJointBase.cpp file.
// To modify it, please change the .fcd file (OSGPhysicsUniversalJoint.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsUniversalJoint::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

PhysicsUniversalJointUnrecPtr PhysicsUniversalJoint::create(PhysicsWorldUnrecPtr w)
{
    PhysicsUniversalJointUnrecPtr fc; 

    if(getClassType().getPrototype() != NULL) 
    {
        fc = dynamic_pointer_cast<PhysicsUniversalJoint>(
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

Vec3f PhysicsUniversalJoint::getAnchor2(void)
{
	dVector3 a;
	dJointGetUniversalAnchor2(_JointID, a);
	return Vec3f(a[0], a[1], a[2]);
}

Real32 PhysicsUniversalJoint::getUniversalAngle1(void) const
{
    return dJointGetUniversalAngle1(_JointID);
}

Real32 PhysicsUniversalJoint::getUniversalAngle1Rate(void) const
{
    return dJointGetUniversalAngle1Rate(_JointID);
}

Real32 PhysicsUniversalJoint::getUniversalAngle2(void) const
{
    return dJointGetUniversalAngle2(_JointID);
}

Real32 PhysicsUniversalJoint::getUniversalAngle2Rate(void) const
{
    return dJointGetUniversalAngle2Rate(_JointID);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void PhysicsUniversalJoint::onCreate(const PhysicsUniversalJoint *)
{
	//call initJoint!
}

void PhysicsUniversalJoint::onDestroy()
{
	//empty
}
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

void PhysicsUniversalJoint::changed(ConstFieldMaskArg whichField, 
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
            _JointID = dJointCreateUniversal(getWorld()->getWorldID(), 0);
        }
        else
        {
            _JointID = dJointCreateUniversal(getWorld()->getWorldID(), 0);
            if(!(whichField & HiStopFieldMask))
            {
                setHiStop(dJointGetUniversalParam(_JointID,dParamHiStop));
            }
            if(!(whichField & LoStopFieldMask))
            {
                setLoStop(dJointGetUniversalParam(_JointID,dParamLoStop));
            }
            if(!(whichField & BounceFieldMask))
            {
                setBounce(dJointGetUniversalParam(_JointID,dParamBounce));
            }
            if(!(whichField & CFMFieldMask))
            {
                setCFM(dJointGetUniversalParam(_JointID,dParamCFM));
            }
            if(!(whichField & StopCFMFieldMask))
            {
                setStopCFM(dJointGetUniversalParam(_JointID,dParamStopCFM));
            }
            if(!(whichField & StopERPFieldMask))
            {
                setStopERP(dJointGetUniversalParam(_JointID,dParamStopERP));
            }
            if(!(whichField & HiStop2FieldMask))
            {
                setHiStop2(dJointGetUniversalParam(_JointID,dParamHiStop2));
            }
            if(!(whichField & LoStop2FieldMask))
            {
                setLoStop2(dJointGetUniversalParam(_JointID,dParamLoStop2));
            }
            if(!(whichField & Bounce2FieldMask))
            {
                setBounce2(dJointGetUniversalParam(_JointID,dParamBounce2));
            }
            if(!(whichField & CFM2FieldMask))
            {
                setCFM2(dJointGetUniversalParam(_JointID,dParamCFM2));
            }
            if(!(whichField & StopCFM2FieldMask))
            {
                setStopCFM2(dJointGetUniversalParam(_JointID,dParamStopCFM2));
            }
            if(!(whichField & StopERP2FieldMask))
            {
                setStopERP2(dJointGetUniversalParam(_JointID,dParamStopERP2));
            }
        }
    }

    Inherited::changed(whichField, origin, details);

    if((whichField & AnchorFieldMask) || (whichField & WorldFieldMask))
    {
	    dJointSetUniversalAnchor(_JointID, getAnchor().x(), getAnchor().y(), getAnchor().z());
    }
    if((whichField & Axis1FieldMask) || (whichField & WorldFieldMask))
    {
	    dJointSetUniversalAxis1(_JointID, getAxis1().x(), getAxis1().y(), getAxis1().z());
    }
    if((whichField & Axis2FieldMask) || (whichField & WorldFieldMask))
    {
	    dJointSetUniversalAxis2(_JointID, getAxis2().x(), getAxis2().y(), getAxis2().z());
    }
    if((whichField & HiStopFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetUniversalParam(_JointID,  dParamHiStop, getHiStop());
    }
    if((whichField & LoStopFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetUniversalParam(_JointID,  dParamLoStop, getLoStop());
    }
    if((whichField & BounceFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetUniversalParam(_JointID,  dParamBounce, getBounce());
    }
    if((whichField & CFMFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetUniversalParam(_JointID,  dParamCFM, getCFM());
    }
    if((whichField & StopERPFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetUniversalParam(_JointID,  dParamStopERP, getStopERP());
    }
    if((whichField & StopCFMFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetUniversalParam(_JointID,  dParamStopCFM, getStopCFM());
    }
    if((whichField & HiStop2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetUniversalParam(_JointID,  dParamHiStop2, getHiStop2());
    }
    if((whichField & LoStop2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetUniversalParam(_JointID,  dParamLoStop2, getLoStop2());
    }
    if((whichField & Bounce2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetUniversalParam(_JointID,  dParamBounce2, getBounce2());
    }
    if((whichField & CFM2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetUniversalParam(_JointID,  dParamCFM2, getCFM2());
    }
    if((whichField & StopERP2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetUniversalParam(_JointID,  dParamStopERP2, getStopERP2());
    }
    if((whichField & StopCFM2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetUniversalParam(_JointID,  dParamStopCFM2, getStopCFM2());
    }
}

void PhysicsUniversalJoint::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump PhysicsUniversalJoint NI" << std::endl;
}

OSG_END_NAMESPACE
