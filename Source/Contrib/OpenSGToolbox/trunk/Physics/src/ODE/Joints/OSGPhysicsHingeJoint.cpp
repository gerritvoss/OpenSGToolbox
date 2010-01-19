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

#include <OpenSG/OSGConfig.h>
#include "OSGPhysicsDef.h"

#include "OSGPhysicsHingeJoint.h"
#include "ODE/OSGPhysicsWorld.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsHingeJoint

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsHingeJoint::initMethod (void)
{
}


PhysicsHingeJointPtr PhysicsHingeJoint::create(PhysicsWorldPtr w)
{
    PhysicsHingeJointPtr fc; 

    if(getClassType().getPrototype() != OSG::NullFC) 
    {
        fc = PhysicsHingeJointPtr::dcast(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    if(fc != NullFC)
    {
        beginEditCP(fc, PhysicsHingeJoint::WorldFieldMask);
            fc->setWorld(w);
        endEditCP(fc, PhysicsHingeJoint::WorldFieldMask);
    }
    
    return fc; 
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
/*-------------------------------------------------------------------------*\
-  public                                                                 -
\*-------------------------------------------------------------------------*/
void PhysicsHingeJoint::onCreate(const PhysicsHingeJoint *)
{
	//call initJoint!
}

void PhysicsHingeJoint::onDestroy()
{
	//empty
}

/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/
Vec3f PhysicsHingeJoint::getAnchor2(void)
{
	dVector3 a;
	dJointGetHingeAnchor2(_JointID, a);
	return Vec3f(a[0], a[1], a[2]);
}

Real32 PhysicsHingeJoint::getAngle(void)
{
	return dJointGetHingeAngle(_JointID);
}

Real32 PhysicsHingeJoint::getAngleRate(void)
{
	return dJointGetHingeAngleRate(_JointID);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsHingeJoint::PhysicsHingeJoint(void) :
    Inherited()
{
}

PhysicsHingeJoint::PhysicsHingeJoint(const PhysicsHingeJoint &source) :
    Inherited(source)
{
}

PhysicsHingeJoint::~PhysicsHingeJoint(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsHingeJoint::changed(BitVector whichField, UInt32 origin)
{
    if(whichField & WorldFieldMask)
    {
        if(_JointID)
        {
            dJointDestroy(_JointID);
            _JointID = dJointCreateHinge(getWorld()->getWorldID(), 0);
        }
        else
        {
            _JointID = dJointCreateHinge(getWorld()->getWorldID(), 0);
            if(!(whichField & HiStopFieldMask))
            {
                setHiStop(dJointGetHingeParam(_JointID,dParamHiStop));
            }
            if(!(whichField & LoStopFieldMask))
            {
                setLoStop(dJointGetHingeParam(_JointID,dParamLoStop));
            }
            if(!(whichField & BounceFieldMask))
            {
                setBounce(dJointGetHingeParam(_JointID,dParamBounce));
            }
            if(!(whichField & CFMFieldMask))
            {
                setCFM(dJointGetHingeParam(_JointID,dParamCFM));
            }
            if(!(whichField & StopCFMFieldMask))
            {
                setStopCFM(dJointGetHingeParam(_JointID,dParamStopCFM));
            }
            if(!(whichField & StopERPFieldMask))
            {
                setStopERP(dJointGetHingeParam(_JointID,dParamStopERP));
            }
        }
    }

    Inherited::changed(whichField, origin);

    if((whichField & AnchorFieldMask) || (whichField & WorldFieldMask))
    {
	    dJointSetHingeAnchor(_JointID, getAnchor().x(), getAnchor().y(), getAnchor().z());
    }
    if((whichField & AxisFieldMask) || (whichField & WorldFieldMask))
    {
	    dJointSetHingeAxis(_JointID, getAxis().x(), getAxis().y(), getAxis().z());
    }
    if((whichField & HiStopFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetHingeParam(_JointID,  dParamHiStop, getHiStop());
    }
    if((whichField & LoStopFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetHingeParam(_JointID,  dParamLoStop, getLoStop());
    }
    if((whichField & BounceFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetHingeParam(_JointID,  dParamBounce, getBounce());
    }
    if((whichField & CFMFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetHingeParam(_JointID,  dParamCFM, getCFM());
    }
    if((whichField & StopERPFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetHingeParam(_JointID,  dParamStopERP, getStopERP());
    }
    if((whichField & StopCFMFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetHingeParam(_JointID,  dParamStopCFM, getStopCFM());
    }
}

void PhysicsHingeJoint::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsHingeJoint NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPhysicsHingeJoint.cpp,v 1.1 2005/10/21 15:44:25 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGPHYSICSHINGEJOINTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSHINGEJOINTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSHINGEJOINTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

