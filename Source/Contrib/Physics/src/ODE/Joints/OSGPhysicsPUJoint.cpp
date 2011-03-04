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

#include "OSGPhysicsPUJoint.h"
#include "OSGPhysicsWorld.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPhysicsPUJointBase.cpp file.
// To modify it, please change the .fcd file (OSGPhysicsPUJoint.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsPUJoint::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

PhysicsPUJointUnrecPtr PhysicsPUJoint::create(PhysicsWorldUnrecPtr w)
{
    PhysicsPUJointUnrecPtr fc; 

    if(getClassType().getPrototype() != NULL) 
    {
        fc = dynamic_pointer_cast<PhysicsPUJoint>(
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

Real32 PhysicsPUJoint::getPUPosition(void) const
{
    return dJointGetPUPosition(_JointID);
}

Real32 PhysicsPUJoint::getPUPositionRate(void) const
{
    return dJointGetPUPositionRate(_JointID);
}

Real32 PhysicsPUJoint::getPUAngle1(void) const
{
    return dJointGetPUAngle1(_JointID);
}

Real32 PhysicsPUJoint::getPUAngle1Rate(void) const
{
    return dJointGetPUAngle1Rate(_JointID);
}

Real32 PhysicsPUJoint::getPUAngle2(void) const
{
    return dJointGetPUAngle2(_JointID);
}

Real32 PhysicsPUJoint::getPUAngle2Rate(void) const
{
    return dJointGetPUAngle2Rate(_JointID);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsPUJoint::PhysicsPUJoint(void) :
    Inherited()
{
}

PhysicsPUJoint::PhysicsPUJoint(const PhysicsPUJoint &source) :
    Inherited(source)
{
}

PhysicsPUJoint::~PhysicsPUJoint(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsPUJoint::changed(ConstFieldMaskArg whichField, 
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
            _JointID = dJointCreatePU(getWorld()->getWorldID(), 0);
        }
        else
        {
            _JointID = dJointCreatePU(getWorld()->getWorldID(), 0);
            if(!(whichField & HiStopFieldMask))
            {
                setHiStop(dJointGetPUParam(_JointID,dParamHiStop));
            }
            if(!(whichField & LoStopFieldMask))
            {
                setLoStop(dJointGetPUParam(_JointID,dParamLoStop));
            }
            if(!(whichField & BounceFieldMask))
            {
                setBounce(dJointGetPUParam(_JointID,dParamBounce));
            }
            if(!(whichField & CFMFieldMask))
            {
                setCFM(dJointGetPUParam(_JointID,dParamCFM));
            }
            if(!(whichField & StopCFMFieldMask))
            {
                setStopCFM(dJointGetPUParam(_JointID,dParamStopCFM));
            }
            if(!(whichField & StopERPFieldMask))
            {
                setStopERP(dJointGetPUParam(_JointID,dParamStopERP));
            }
            if(!(whichField & HiStop2FieldMask))
            {
                setHiStop2(dJointGetPUParam(_JointID,dParamHiStop2));
            }
            if(!(whichField & LoStop2FieldMask))
            {
                setLoStop2(dJointGetPUParam(_JointID,dParamLoStop2));
            }
            if(!(whichField & Bounce2FieldMask))
            {
                setBounce2(dJointGetPUParam(_JointID,dParamBounce2));
            }
            if(!(whichField & CFM2FieldMask))
            {
                setCFM2(dJointGetPUParam(_JointID,dParamCFM2));
            }
            if(!(whichField & StopCFM2FieldMask))
            {
                setStopCFM2(dJointGetPUParam(_JointID,dParamStopCFM2));
            }
            if(!(whichField & StopERP2FieldMask))
            {
                setStopERP2(dJointGetPUParam(_JointID,dParamStopERP2));
            }
            if(!(whichField & HiStop3FieldMask))
            {
                setHiStop3(dJointGetPUParam(_JointID,dParamHiStop3));
            }
            if(!(whichField & LoStop3FieldMask))
            {
                setLoStop3(dJointGetPUParam(_JointID,dParamLoStop3));
            }
            if(!(whichField & Bounce3FieldMask))
            {
                setBounce3(dJointGetPUParam(_JointID,dParamBounce3));
            }
            if(!(whichField & CFM3FieldMask))
            {
                setCFM3(dJointGetPUParam(_JointID,dParamCFM3));
            }
            if(!(whichField & StopCFM3FieldMask))
            {
                setStopCFM3(dJointGetPUParam(_JointID,dParamStopCFM3));
            }
            if(!(whichField & StopERP3FieldMask))
            {
                setStopERP3(dJointGetPUParam(_JointID,dParamStopERP3));
            }
        }
    }

    Inherited::changed(whichField, origin, details);

    if((whichField & AnchorFieldMask) || (whichField & WorldFieldMask))
    {
	    dJointSetPUAnchor(_JointID, getAnchor().x(), getAnchor().y(), getAnchor().z());
    }
    if((whichField & Axis1FieldMask) || (whichField & WorldFieldMask))
    {
	    dJointSetPUAxis1(_JointID, getAxis1().x(), getAxis1().y(), getAxis1().z());
    }
    if((whichField & Axis2FieldMask) || (whichField & WorldFieldMask))
    {
	    dJointSetPUAxis2(_JointID, getAxis2().x(), getAxis2().y(), getAxis2().z());
    }
    if((whichField & Axis3FieldMask) || (whichField & WorldFieldMask))
    {
	    dJointSetPUAxis3(_JointID, getAxis3().x(), getAxis3().y(), getAxis3().z());
    }
    if((whichField & HiStopFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPUParam(_JointID,  dParamHiStop, getHiStop());
    }
    if((whichField & LoStopFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPUParam(_JointID,  dParamLoStop, getLoStop());
    }
    if((whichField & BounceFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPUParam(_JointID,  dParamBounce, getBounce());
    }
    if((whichField & CFMFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPUParam(_JointID,  dParamCFM, getCFM());
    }
    if((whichField & StopERPFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPUParam(_JointID,  dParamStopERP, getStopERP());
    }
    if((whichField & StopCFMFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPUParam(_JointID,  dParamStopCFM, getStopCFM());
    }
    if((whichField & HiStop2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPUParam(_JointID,  dParamHiStop2, getHiStop2());
    }
    if((whichField & LoStop2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPUParam(_JointID,  dParamLoStop2, getLoStop2());
    }
    if((whichField & Bounce2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPUParam(_JointID,  dParamBounce2, getBounce2());
    }
    if((whichField & CFM2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPUParam(_JointID,  dParamCFM2, getCFM2());
    }
    if((whichField & StopERP2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPUParam(_JointID,  dParamStopERP2, getStopERP2());
    }
    if((whichField & StopCFM2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPUParam(_JointID,  dParamStopCFM2, getStopCFM2());
    }
    if((whichField & HiStop3FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPUParam(_JointID,  dParamHiStop3, getHiStop3());
    }
    if((whichField & LoStop3FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPUParam(_JointID,  dParamLoStop3, getLoStop3());
    }
    if((whichField & Bounce3FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPUParam(_JointID,  dParamBounce3, getBounce3());
    }
    if((whichField & CFM3FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPUParam(_JointID,  dParamCFM3, getCFM3());
    }
    if((whichField & StopERP3FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPUParam(_JointID,  dParamStopERP3, getStopERP3());
    }
    if((whichField & StopCFM3FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPUParam(_JointID,  dParamStopCFM3, getStopCFM3());
    }
}

void PhysicsPUJoint::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump PhysicsPUJoint NI" << std::endl;
}

OSG_END_NAMESPACE
