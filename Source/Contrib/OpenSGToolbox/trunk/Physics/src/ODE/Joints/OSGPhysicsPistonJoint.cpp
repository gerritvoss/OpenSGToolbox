/*---------------------------------------------------------------------------*\
 *                         OpenSG ToolBox Physics                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                          www.vrac.iastate.edu                             *
 *                                                                           *
 *                Authors: Behboud Kalantary, David Kabala                   *
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

#define OSG_COMPILEPHYSICSLIB

#include <OpenSG/OSGConfig.h>

#include "OSGPhysicsPistonJoint.h"
#include "ODE/OSGPhysicsWorld.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsPistonJoint

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsPistonJoint::initMethod (void)
{
}

PhysicsPistonJointPtr PhysicsPistonJoint::create(PhysicsWorldPtr w)
{
    PhysicsPistonJointPtr fc; 

    if(getClassType().getPrototype() != OSG::NullFC) 
    {
        fc = PhysicsPistonJointPtr::dcast(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    if(fc != NullFC)
    {
        beginEditCP(fc, PhysicsPistonJoint::WorldFieldMask);
            fc->setWorld(w);
        endEditCP(fc, PhysicsPistonJoint::WorldFieldMask);
    }
    
    return fc; 
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Vec3f PhysicsPistonJoint::getPistonAnchor2(void) const
{
    dVector3 odeVec;
    dJointGetPistonAnchor2(_JointID, odeVec);

    return Vec3f(odeVec[0], odeVec[1], odeVec[2]);
}

Real32 PhysicsPistonJoint::getPistonPosition(void) const
{
    return dJointGetPistonPosition(_JointID);
}

Real32 PhysicsPistonJoint::getPistonPositionRate(void) const
{
    return dJointGetPistonPositionRate(_JointID);
}

Real32 PhysicsPistonJoint::getPistonAngle(void) const
{
    return dJointGetPistonAngle(_JointID);
}

Real32 PhysicsPistonJoint::getPistonAngleRate(void) const
{
    return dJointGetPistonAngleRate(_JointID);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsPistonJoint::PhysicsPistonJoint(void) :
    Inherited()
{
}

PhysicsPistonJoint::PhysicsPistonJoint(const PhysicsPistonJoint &source) :
    Inherited(source)
{
}

PhysicsPistonJoint::~PhysicsPistonJoint(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsPistonJoint::changed(BitVector whichField, UInt32 origin)
{
    if(whichField & WorldFieldMask)
    {
        if(_JointID)
        {
            dJointDestroy(_JointID);
            _JointID = dJointCreatePiston(getWorld()->getWorldID(), 0);
        }
        else
        {
            _JointID = dJointCreatePiston(getWorld()->getWorldID(), 0);
            if(!(whichField & HiStopFieldMask))
            {
                setHiStop(dJointGetPistonParam(_JointID,dParamHiStop));
            }
            if(!(whichField & LoStopFieldMask))
            {
                setLoStop(dJointGetPistonParam(_JointID,dParamLoStop));
            }
            if(!(whichField & BounceFieldMask))
            {
                setBounce(dJointGetPistonParam(_JointID,dParamBounce));
            }
            if(!(whichField & CFMFieldMask))
            {
                setCFM(dJointGetPistonParam(_JointID,dParamCFM));
            }
            if(!(whichField & StopCFMFieldMask))
            {
                setStopCFM(dJointGetPistonParam(_JointID,dParamStopCFM));
            }
            if(!(whichField & StopERPFieldMask))
            {
                setStopERP(dJointGetPistonParam(_JointID,dParamStopERP));
            }
            if(!(whichField & HiStop2FieldMask))
            {
                setHiStop2(dJointGetPistonParam(_JointID,dParamHiStop2));
            }
            if(!(whichField & LoStop2FieldMask))
            {
                setLoStop2(dJointGetPistonParam(_JointID,dParamLoStop2));
            }
            if(!(whichField & Bounce2FieldMask))
            {
                setBounce2(dJointGetPistonParam(_JointID,dParamBounce2));
            }
            if(!(whichField & CFM2FieldMask))
            {
                setCFM2(dJointGetPistonParam(_JointID,dParamCFM2));
            }
            if(!(whichField & StopCFM2FieldMask))
            {
                setStopCFM2(dJointGetPistonParam(_JointID,dParamStopCFM2));
            }
            if(!(whichField & StopERP2FieldMask))
            {
                setStopERP2(dJointGetPistonParam(_JointID,dParamStopERP2));
            }
        }
    }

    Inherited::changed(whichField, origin);

    if((whichField & AnchorFieldMask) || (whichField & WorldFieldMask))
    {
	    dJointSetPistonAnchor(_JointID, getAnchor().x(), getAnchor().y(), getAnchor().z());
    }
    if((whichField & AxisFieldMask) || (whichField & WorldFieldMask))
    {
	    dJointSetPistonAxis(_JointID, getAxis().x(), getAxis().y(), getAxis().z());
    }
    if((whichField & HiStopFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPistonParam(_JointID,  dParamHiStop, getHiStop());
    }
    if((whichField & LoStopFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPistonParam(_JointID,  dParamLoStop, getLoStop());
    }
    if((whichField & BounceFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPistonParam(_JointID,  dParamBounce, getBounce());
    }
    if((whichField & CFMFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPistonParam(_JointID,  dParamCFM, getCFM());
    }
    if((whichField & StopERPFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPistonParam(_JointID,  dParamStopERP, getStopERP());
    }
    if((whichField & StopCFMFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPistonParam(_JointID,  dParamStopCFM, getStopCFM());
    }
    if((whichField & HiStop2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPistonParam(_JointID,  dParamHiStop2, getHiStop2());
    }
    if((whichField & LoStop2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPistonParam(_JointID,  dParamLoStop2, getLoStop2());
    }
    if((whichField & Bounce2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPistonParam(_JointID,  dParamBounce2, getBounce2());
    }
    if((whichField & CFM2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPistonParam(_JointID,  dParamCFM2, getCFM2());
    }
    if((whichField & StopERP2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPistonParam(_JointID,  dParamStopERP2, getStopERP2());
    }
    if((whichField & StopCFM2FieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetPistonParam(_JointID,  dParamStopCFM2, getStopCFM2());
    }
}

void PhysicsPistonJoint::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsPistonJoint NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGPHYSICSPISTONJOINTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSPISTONJOINTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSPISTONJOINTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

