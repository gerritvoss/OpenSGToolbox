/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#ifndef OSG_COMPILEPHYSICSLIB
#define OSG_COMPILEPHYSICSLIB
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGPhysicsPlane2DJoint.h"
#include "ODE/OSGPhysicsWorld.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsPlane2DJoint

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsPlane2DJoint::initMethod (void)
{
}


PhysicsPlane2DJointPtr PhysicsPlane2DJoint::create(PhysicsWorldPtr w)
{
    PhysicsPlane2DJointPtr fc; 

    if(getClassType().getPrototype() != OSG::NullFC) 
    {
        fc = PhysicsPlane2DJointPtr::dcast(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    if(fc != NullFC)
    {
        beginEditCP(fc, PhysicsPlane2DJoint::WorldFieldMask);
            fc->setWorld(w);
        endEditCP(fc, PhysicsPlane2DJoint::WorldFieldMask);
    }
    
    return fc; 
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void PhysicsPlane2DJoint::onCreate(const PhysicsPlane2DJoint *)
{
}

void PhysicsPlane2DJoint::onDestroy()
{
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

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

void PhysicsPlane2DJoint::changed(BitVector whichField, UInt32 origin)
{
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

    Inherited::changed(whichField, origin);
}

void PhysicsPlane2DJoint::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsPlane2DJoint NI" << std::endl;
}


OSG_END_NAMESPACE

