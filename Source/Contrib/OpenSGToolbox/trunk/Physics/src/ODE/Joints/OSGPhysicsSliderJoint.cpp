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

PhysicsSliderJointPtr PhysicsSliderJoint::create(PhysicsWorldPtr w)
{
    PhysicsSliderJointPtr fc; 

    if(getClassType().getPrototype() != OSG::NullFC) 
    {
        fc = PhysicsSliderJointPtr::dcast(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    if(fc != NullFC)
    {
        beginEditCP(fc, PhysicsSliderJoint::WorldFieldMask);
            fc->setWorld(w);
        endEditCP(fc, PhysicsSliderJoint::WorldFieldMask);
    }
    
    return fc; 
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
/*-------------------------------------------------------------------------*\
-  public                                                                 -
\*-------------------------------------------------------------------------*/
void PhysicsSliderJoint::onCreate(const PhysicsSliderJoint *)
{
	//call initJoint!
}

void PhysicsSliderJoint::onDestroy()
{
	//empty
}
/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/

Real32 PhysicsSliderJoint::getPosition(void)
{
	return dJointGetSliderPosition(_JointID);
}

Real32 PhysicsSliderJoint::getPositionRate(void)
{
	return dJointGetSliderPositionRate(_JointID);
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
    if(whichField & WorldFieldMask)
    {
        if(_JointID)
        {
            dJointDestroy(_JointID);
            _JointID = dJointCreateSlider(getWorld()->getWorldID(), 0);
        }
        else
        {
            _JointID = dJointCreateSlider(getWorld()->getWorldID(), 0);
            if(!(whichField & HiStopFieldMask))
            {
                setHiStop(dJointGetSliderParam(_JointID,dParamHiStop));
            }
            if(!(whichField & LoStopFieldMask))
            {
                setLoStop(dJointGetSliderParam(_JointID,dParamLoStop));
            }
            if(!(whichField & BounceFieldMask))
            {
                setBounce(dJointGetSliderParam(_JointID,dParamBounce));
            }
            if(!(whichField & CFMFieldMask))
            {
                setCFM(dJointGetSliderParam(_JointID,dParamCFM));
            }
            if(!(whichField & StopCFMFieldMask))
            {
                setStopCFM(dJointGetSliderParam(_JointID,dParamStopCFM));
            }
            if(!(whichField & StopERPFieldMask))
            {
                setStopERP(dJointGetSliderParam(_JointID,dParamStopERP));
            }
        }
    }

    Inherited::changed(whichField, origin);

    if((whichField & AxisFieldMask) || (whichField & WorldFieldMask))
    {
	    dJointSetSliderAxis(_JointID, getAxis().x(), getAxis().y(), getAxis().z());
    }
    if((whichField & HiStopFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetSliderParam(_JointID,  dParamHiStop, getHiStop());
    }
    if((whichField & LoStopFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetSliderParam(_JointID,  dParamLoStop, getLoStop());
    }
    if((whichField & BounceFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetSliderParam(_JointID,  dParamBounce, getBounce());
    }
    if((whichField & CFMFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetSliderParam(_JointID,  dParamCFM, getCFM());
    }
    if((whichField & StopERPFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetSliderParam(_JointID,  dParamStopERP, getStopERP());
    }
    if((whichField & StopCFMFieldMask) || (whichField & WorldFieldMask))
    {
        dJointSetSliderParam(_JointID,  dParamStopCFM, getStopCFM());
    }
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

