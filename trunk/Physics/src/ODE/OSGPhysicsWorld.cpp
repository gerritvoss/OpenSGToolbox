/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#include "OSGPhysicsWorld.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsWorld
Group is the simplest form of a NodeCore. A group carries no predefined data and most actions will only traverse the children list. So usually the group does nothing.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsWorld::initMethod (void)
{
    addInitFunction(&PhysicsWorld::odeInitFunc);
    addSystemExitFunction(&PhysicsWorld::odeExitFunc);
}

bool PhysicsWorld::odeInitFunc(void)
{
    SLOG << "Initializing ODE." << std::endl;
    return dInitODE2(0);
}

bool PhysicsWorld::odeExitFunc(void)
{
    SLOG << "Exiting ODE." << std::endl;
    dCloseODE();
    return true;
}
/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
/*-------------------------------------------------------------------------*\
-  public                                                                 -
\*-------------------------------------------------------------------------*/
void PhysicsWorld::onCreate(const PhysicsWorld *)
{
	PhysicsWorldPtr tmpPtr(*this);
	tmpPtr->id = dWorldCreate();
    /*  should set ode to the loaded values but this does only work
        in the initWorld method and I do not know why...!?
    beginEditCP(tmpPtr);
        setGravity(PhysicsWorldBase::getGravity());
        PhysicsWorld::setCfm(PhysicsWorldBase::getCfm());
        PhysicsWorld::setErp(PhysicsWorldBase::getErp());
        PhysicsWorld::setWorldContactSurfaceLayer(PhysicsWorldBase::getWorldContactSurfaceLayer());
        PhysicsWorld::setWorldContactMaxCorrectingVel(PhysicsWorldBase::getWorldContactMaxCorrectingVel());
        PhysicsWorld::setWorldQuickStepNumIterations(PhysicsWorldBase::getWorldQuickStepNumIterations());
        PhysicsWorld::setAutoDisableTime(PhysicsWorldBase::getAutoDisableTime());
        PhysicsWorld::setAutoDisableSteps(PhysicsWorldBase::getAutoDisableSteps());
        PhysicsWorld::setAutoDisableAngularThreshold(PhysicsWorldBase::getAutoDisableAngularThreshold());
        PhysicsWorld::setAutoDisableLinearThreshold(PhysicsWorldBase::getAutoDisableLinearThreshold());
        PhysicsWorld::setAutoDisableFlag(PhysicsWorldBase::getAutoDisableFlag());
    endEditCP(tmpPtr);
    */
}

void PhysicsWorld::onDestroy()
{
	PhysicsWorldPtr tmpPtr(*this);
    if(tmpPtr->id)
    {
	    dWorldDestroy(tmpPtr->id);
    }
}


/***************************************************************************\
*                              Field Get	                               *
\***************************************************************************/


Real32 PhysicsWorld::getErp(void)
{
    
	PhysicsWorldPtr tmpPtr(*this);
	return Real32(dWorldGetERP(tmpPtr->id));
}

Real32 PhysicsWorld::getCfm(void)
{
    
	PhysicsWorldPtr tmpPtr(*this);
	return Real32(dWorldGetCFM(tmpPtr->id));
}

Vec3f PhysicsWorld::getGravity(void)
{
    
	PhysicsWorldPtr tmpPtr(*this);
	dVector3 tmp;
	dWorldGetGravity(id, tmp);
	return Vec3f(tmp[0], tmp[1], tmp[2]);
}

Int32 PhysicsWorld::getAutoDisableFlag(void)
{
    
	PhysicsWorldPtr tmpPtr(*this);
	return Int32(dWorldGetAutoDisableFlag(tmpPtr->id));
}

Real32 PhysicsWorld::getAutoDisableLinearThreshold(void)
{
    
	PhysicsWorldPtr tmpPtr(*this);
	return Real32(dWorldGetAutoDisableLinearThreshold(tmpPtr->id));
}

Real32 PhysicsWorld::getAutoDisableAngularThreshold(void)
{
    
	PhysicsWorldPtr tmpPtr(*this);
	return Real32(dWorldGetAutoDisableAngularThreshold(tmpPtr->id));
}

Int32 PhysicsWorld::getAutoDisableSteps(void)
{
    
	PhysicsWorldPtr tmpPtr(*this);
	return Int32(dWorldGetAutoDisableSteps(tmpPtr->id));
}

Real32 PhysicsWorld::getAutoDisableTime(void)
{
    
	PhysicsWorldPtr tmpPtr(*this);
	return Real32(dWorldGetAutoDisableTime(tmpPtr->id));
}

Int32 PhysicsWorld::getWorldQuickStepNumIterations(void)
{
    
	PhysicsWorldPtr tmpPtr(*this);
	return Real32(dWorldGetQuickStepNumIterations(tmpPtr->id));
}

Real32 PhysicsWorld::getWorldContactMaxCorrectingVel(void)
{
    
	PhysicsWorldPtr tmpPtr(*this);
	return Real32(dWorldGetContactMaxCorrectingVel(tmpPtr->id));
}

Real32 PhysicsWorld::getWorldContactSurfaceLayer(void)
{
	PhysicsWorldPtr tmpPtr(*this);
	return (Real32)dWorldGetContactSurfaceLayer(tmpPtr->id);
}

dWorldID PhysicsWorld::getWorldID(void)
{
    PhysicsWorldPtr tmpPtr(*this);
    return tmpPtr->id;
}

/***************************************************************************\
*                              Field Set	                               *
\***************************************************************************/

void PhysicsWorld::setErp(const Real32 &value)
{
    
	PhysicsWorldPtr tmpPtr(*this);
	dWorldSetERP(tmpPtr->id, value);
	PhysicsWorldBase::setErp(value);
}

void PhysicsWorld::setCfm(const Real32 &value)
{
    
	PhysicsWorldPtr tmpPtr(*this);
	dWorldSetCFM(tmpPtr->id, value);
	PhysicsWorldBase::setCfm(value);
}

void PhysicsWorld::setGravity(const Vec3f &value )
{
    
	PhysicsWorldPtr tmpPtr(*this);
	dWorldSetGravity(tmpPtr->id,value.x(), value.y(), value.z());
	PhysicsWorldBase::setGravity(value);
}

void PhysicsWorld::setAutoDisableFlag(const Int32 &value )
{
    
	PhysicsWorldPtr tmpPtr(*this);
	dWorldSetAutoDisableFlag(tmpPtr->id, value);
	PhysicsWorldBase::setAutoDisableFlag(value);
}

void PhysicsWorld::setAutoDisableLinearThreshold(const Real32 &value )
{
    
	PhysicsWorldPtr tmpPtr(*this);
	dWorldSetAutoDisableLinearThreshold(tmpPtr->id, value);
	PhysicsWorldBase::setAutoDisableLinearThreshold(value);
}

void PhysicsWorld::setAutoDisableAngularThreshold(const Real32 &value )
{
    
	PhysicsWorldPtr tmpPtr(*this);
	dWorldSetAutoDisableAngularThreshold(tmpPtr->id, value);
	PhysicsWorldBase::setAutoDisableAngularThreshold(value);
}

void PhysicsWorld::setAutoDisableSteps(const Int32 &value )
{
    
	PhysicsWorldPtr tmpPtr(*this);
	dWorldSetAutoDisableSteps(tmpPtr->id, value);
	PhysicsWorldBase::setAutoDisableSteps(value);
}

void PhysicsWorld::setAutoDisableTime(const Real32 &value )
{
    
	PhysicsWorldPtr tmpPtr(*this);
	dWorldSetAutoDisableTime(tmpPtr->id, value);
	PhysicsWorldBase::setAutoDisableTime(value);
}

void PhysicsWorld::setWorldQuickStepNumIterations(const Int32 &value )
{
    
	PhysicsWorldPtr tmpPtr(*this);
	dWorldSetQuickStepNumIterations(tmpPtr->id, value);
	PhysicsWorldBase::setWorldQuickStepNumIterations(value);
}

void PhysicsWorld::setWorldContactMaxCorrectingVel(const Real32 &value )
{
    
	PhysicsWorldPtr tmpPtr(*this);
	dWorldSetContactMaxCorrectingVel(tmpPtr->id, value);
	PhysicsWorldBase::setWorldContactMaxCorrectingVel(value);
}

void PhysicsWorld::setWorldContactSurfaceLayer(const Real32 &value )
{
    
	PhysicsWorldPtr tmpPtr(*this);
	dWorldSetContactSurfaceLayer(tmpPtr->id, value);
	PhysicsWorldBase::setWorldContactSurfaceLayer(value);
}


/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/
void PhysicsWorld::initWorld()
{
    setGravity(PhysicsWorldBase::getGravity());
    setCfm(PhysicsWorldBase::getCfm());
    setErp(PhysicsWorldBase::getErp());
    setWorldContactSurfaceLayer(PhysicsWorldBase::getWorldContactSurfaceLayer());
    setWorldContactMaxCorrectingVel(PhysicsWorldBase::getWorldContactMaxCorrectingVel());
    setWorldQuickStepNumIterations(PhysicsWorldBase::getWorldQuickStepNumIterations());
    setAutoDisableTime(PhysicsWorldBase::getAutoDisableTime());
    setAutoDisableSteps(PhysicsWorldBase::getAutoDisableSteps());
    setAutoDisableAngularThreshold(PhysicsWorldBase::getAutoDisableAngularThreshold());
    setAutoDisableLinearThreshold(PhysicsWorldBase::getAutoDisableLinearThreshold());
    setAutoDisableFlag(PhysicsWorldBase::getAutoDisableFlag());
}
void PhysicsWorld::worldImpulseToForce(Real32 stepsize, Real32 x, Real32 y, Real32 z, Vec3f force)
{
	PhysicsWorldPtr tmpPtr(*this);
	dVector3 f;
	f[0]=force.x();
	f[1]=force.y();
	f[2]=force.z();
	dWorldImpulseToForce(tmpPtr->id, stepsize, x, y, z, f);
}

void PhysicsWorld::worldStep(Real32 stepsize)
{
	PhysicsWorldPtr tmpPtr(*this);
	dWorldStep(tmpPtr->id, stepsize);
}

void PhysicsWorld::worldQuickStep(Real32 stepsize)
{
	PhysicsWorldPtr tmpPtr(*this);
	dWorldQuickStep(tmpPtr->id, stepsize);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsWorld::PhysicsWorld(void) :
    Inherited()
{
}

PhysicsWorld::PhysicsWorld(const PhysicsWorld &source) :
    Inherited(source)
{
}

PhysicsWorld::~PhysicsWorld(void)
{

}

/*----------------------------- class specific ----------------------------*/

void PhysicsWorld::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PhysicsWorld::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsWorld NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPhysicsWorld.cpp,v 1.1 2005/10/21 15:44:25 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGPHYSICSWORLDBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSWORLDBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSWORLDFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

