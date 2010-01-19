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

#include "OSGPhysicsAMotorJoint.h"
#include "OSGPhysicsWorld.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPhysicsAMotorJointBase.cpp file.
// To modify it, please change the .fcd file (OSGPhysicsAMotorJoint.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsAMotorJoint::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


PhysicsAMotorJointUnrecPtr PhysicsAMotorJoint::create(PhysicsWorldUnrecPtr w)
{
    PhysicsAMotorJointUnrecPtr fc; 

    if(getClassType().getPrototype() != NULL) 
    {
        fc = dynamic_pointer_cast<PhysicsAMotorJoint>(
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


void PhysicsAMotorJoint::setAxis1Properties(const Vec3f& Axis, UInt8 ReferenceFrame)
{
    setAxis1(Axis);
    setAxis3ReferenceFrame(ReferenceFrame);
}

void PhysicsAMotorJoint::setAxis2Properties(const Vec3f& Axis, UInt8 ReferenceFrame)
{
    setAxis2(Axis);
    setAxis2ReferenceFrame(ReferenceFrame);
}

void PhysicsAMotorJoint::setAxis3Properties(const Vec3f& Axis, UInt8 ReferenceFrame)
{
    setAxis3(Axis);
    setAxis3ReferenceFrame(ReferenceFrame);
}

void PhysicsAMotorJoint::setAngle(Int32 anum, Real32 angle)
{
	dJointSetAMotorAngle(_JointID, anum, angle);
}

Real32 PhysicsAMotorJoint::getAngle(Int32 anum)
{
	return dJointGetAMotorAngle(_JointID, anum);
}

Real32 PhysicsAMotorJoint::getAngleRate(Int32 anum)
{
	return dJointGetAMotorAngleRate(_JointID, anum);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void PhysicsAMotorJoint::onCreate(const PhysicsAMotorJoint *)
{
	//call initJoint!
}

void PhysicsAMotorJoint::onDestroy()
{
	//empty
}

/*----------------------- constructors & destructors ----------------------*/

PhysicsAMotorJoint::PhysicsAMotorJoint(void) :
    Inherited()
{
}

PhysicsAMotorJoint::PhysicsAMotorJoint(const PhysicsAMotorJoint &source) :
    Inherited(source)
{
}

PhysicsAMotorJoint::~PhysicsAMotorJoint(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsAMotorJoint::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    if(whichField & WorldFieldMask)
    {
        if(_JointID)
        {
            dJointDestroy(_JointID);
            _JointID = dJointCreateAMotor(getWorld()->getWorldID(), 0);
        }
        else
        {
            _JointID = dJointCreateAMotor(getWorld()->getWorldID(), 0);
            if(!(whichField & VelFieldMask))
            {
                setVel(dJointGetAMotorParam(_JointID,dParamVel));
            }
            if(!(whichField & FMaxFieldMask))
            {
                setFMax(dJointGetAMotorParam(_JointID,dParamFMax));
            }
            if(!(whichField & FudgeFactorFieldMask))
            {
                setFudgeFactor(dJointGetAMotorParam(_JointID,dParamFudgeFactor));
            }
            if(!(whichField & Vel2FieldMask))
            {
                setVel2(dJointGetAMotorParam(_JointID,dParamVel2));
            }
            if(!(whichField & FMax2FieldMask))
            {
                setFMax2(dJointGetAMotorParam(_JointID,dParamFMax2));
            }
            if(!(whichField & FudgeFactor2FieldMask))
            {
                setFudgeFactor2(dJointGetAMotorParam(_JointID,dParamFudgeFactor2));
            }
            if(!(whichField & Vel3FieldMask))
            {
                setVel3(dJointGetAMotorParam(_JointID,dParamVel3));
            }
            if(!(whichField & FMax3FieldMask))
            {
                setFMax3(dJointGetAMotorParam(_JointID,dParamFMax3));
            }
            if(!(whichField & FudgeFactor3FieldMask))
            {
                setFudgeFactor3(dJointGetAMotorParam(_JointID,dParamFudgeFactor3));
            }
            if(!(whichField & HiStopFieldMask))
            {
                setHiStop(dJointGetAMotorParam(_JointID,dParamHiStop));
            }
            if(!(whichField & LoStopFieldMask))
            {
                setLoStop(dJointGetAMotorParam(_JointID,dParamLoStop));
            }
            if(!(whichField & BounceFieldMask))
            {
                setBounce(dJointGetAMotorParam(_JointID,dParamBounce));
            }
            if(!(whichField & CFMFieldMask))
            {
                setCFM(dJointGetAMotorParam(_JointID,dParamCFM));
            }
            if(!(whichField & StopCFMFieldMask))
            {
                setStopCFM(dJointGetAMotorParam(_JointID,dParamStopCFM));
            }
            if(!(whichField & StopERPFieldMask))
            {
                setStopERP(dJointGetAMotorParam(_JointID,dParamStopERP));
            }
            if(!(whichField & HiStop2FieldMask))
            {
                setHiStop2(dJointGetAMotorParam(_JointID,dParamHiStop2));
            }
            if(!(whichField & LoStop2FieldMask))
            {
                setLoStop2(dJointGetAMotorParam(_JointID,dParamLoStop2));
            }
            if(!(whichField & Bounce2FieldMask))
            {
                setBounce2(dJointGetAMotorParam(_JointID,dParamBounce2));
            }
            if(!(whichField & CFM2FieldMask))
            {
                setCFM2(dJointGetAMotorParam(_JointID,dParamCFM2));
            }
            if(!(whichField & StopCFM2FieldMask))
            {
                setStopCFM2(dJointGetAMotorParam(_JointID,dParamStopCFM2));
            }
            if(!(whichField & StopERP2FieldMask))
            {
                setStopERP2(dJointGetAMotorParam(_JointID,dParamStopERP2));
            }
            if(!(whichField & HiStop3FieldMask))
            {
                setHiStop3(dJointGetAMotorParam(_JointID,dParamHiStop3));
            }
            if(!(whichField & LoStop3FieldMask))
            {
                setLoStop3(dJointGetAMotorParam(_JointID,dParamLoStop3));
            }
            if(!(whichField & Bounce3FieldMask))
            {
                setBounce3(dJointGetAMotorParam(_JointID,dParamBounce3));
            }
            if(!(whichField & CFM3FieldMask))
            {
                setCFM3(dJointGetAMotorParam(_JointID,dParamCFM3));
            }
            if(!(whichField & StopCFM3FieldMask))
            {
                setStopCFM3(dJointGetAMotorParam(_JointID,dParamStopCFM3));
            }
            if(!(whichField & StopERP3FieldMask))
            {
                setStopERP3(dJointGetAMotorParam(_JointID,dParamStopERP3));
            }
        }
    }

    Inherited::changed(whichField, origin, details);

    if((whichField & NumAxesFieldMask) ||
       (whichField & WorldFieldMask))
    {
	    dJointSetAMotorNumAxes(_JointID,getNumAxes());
    }
    if((whichField & Axis1FieldMask) ||
       (whichField & Axis1ReferenceFrameFieldMask) ||
       (whichField & WorldFieldMask))
    {
	    dJointSetAMotorAxis(_JointID,0, getAxis1ReferenceFrame(), getAxis1().x(), getAxis1().y(), getAxis1().z());
    }
    if((whichField & Axis2FieldMask) ||
       (whichField & Axis2ReferenceFrameFieldMask) ||
       (whichField & WorldFieldMask))
    {
	    dJointSetAMotorAxis(_JointID,1, getAxis2ReferenceFrame(), getAxis2().x(), getAxis2().y(), getAxis2().z());
    }
    if((whichField & Axis3FieldMask) ||
       (whichField & Axis3ReferenceFrameFieldMask) ||
       (whichField & WorldFieldMask))
    {
	    dJointSetAMotorAxis(_JointID,2, getAxis3ReferenceFrame(), getAxis3().x(), getAxis3().y(), getAxis3().z());
    }
    if((whichField & VelFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamVel, getVel());
    }
    if((whichField & FMaxFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamFMax, getFMax());
    }
    if((whichField & FudgeFactorFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamFudgeFactor, getFudgeFactor());
    }
    if((whichField & Vel2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamVel2, getVel2());
    }
    if((whichField & FMax2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamFMax2, getFMax2());
    }
    if((whichField & FudgeFactor2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamFudgeFactor2, getFudgeFactor2());
    }
    if((whichField & Vel3FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamVel3, getVel3());
    }
    if((whichField & FMax3FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamFMax3, getFMax3());
    }
    if((whichField & FudgeFactor3FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamFudgeFactor3, getFudgeFactor3());
    }
    if((whichField & HiStopFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamHiStop, getHiStop());
    }
    if((whichField & LoStopFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamLoStop, getLoStop());
    }
    if((whichField & BounceFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamBounce, getBounce());
    }
    if((whichField & CFMFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamCFM, getCFM());
    }
    if((whichField & StopERPFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamStopERP, getStopERP());
    }
    if((whichField & StopCFMFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamStopCFM, getStopCFM());
    }
    if((whichField & HiStop2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamHiStop2, getHiStop2());
    }
    if((whichField & LoStop2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamLoStop2, getLoStop2());
    }
    if((whichField & Bounce2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamBounce2, getBounce2());
    }
    if((whichField & CFM2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamCFM2, getCFM2());
    }
    if((whichField & StopERP2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamStopERP2, getStopERP2());
    }
    if((whichField & StopCFM2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamStopCFM2, getStopCFM2());
    }
    if((whichField & HiStop3FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamHiStop3, getHiStop3());
    }
    if((whichField & LoStop3FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamLoStop3, getLoStop3());
    }
    if((whichField & Bounce3FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamBounce3, getBounce3());
    }
    if((whichField & CFM3FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamCFM3, getCFM3());
    }
    if((whichField & StopERP3FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamStopERP3, getStopERP3());
    }
    if((whichField & StopCFM3FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetAMotorParam(_JointID,  dParamStopCFM3, getStopCFM3());
    }
}

void PhysicsAMotorJoint::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump PhysicsAMotorJoint NI" << std::endl;
}

OSG_END_NAMESPACE
