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

#include "OSGPhysicsWorld.h"
#include "OSGBaseInitFunctions.h"
#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPhysicsWorldBase.cpp file.
// To modify it, please change the .fcd file (OSGPhysicsWorld.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsWorld::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::Static)
    {
        addPreFactoryInitFunction(boost::bind(&PhysicsWorld::odeInitFunc));
        addPostFactoryExitFunction(boost::bind(&PhysicsWorld::odeExitFunc));
    }
}

bool PhysicsWorld::odeInitFunc(void)
{
    SLOG << "Initializing ODE." << std::endl;
    SLOG << "ODE Configuration: " << dGetConfiguration() << std::endl;
    return dInitODE2(0);
}

bool PhysicsWorld::odeExitFunc(void)
{
    SLOG << "Uninitializing ODE." << std::endl;
    dCloseODE();
    return true;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

PhysicsHandler* PhysicsWorld::getParentHandler(void) const
{
    return dynamic_cast<PhysicsHandler* const>(_sfParentHandler.getValue());
}

dWorldID PhysicsWorld::getWorldID(void)
{
    return _World;
}

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

Vec3f PhysicsWorld::impulseToForce(Real32 stepsize, const Vec3f& Impulse)
{
	dVector3 f;
	dWorldImpulseToForce(_World, stepsize, Impulse.x(), Impulse.y(), Impulse.z(), f);

    return Vec3f(&f[0]);
}

void PhysicsWorld::worldStep(Real32 stepsize)
{
	dWorldStep(_World, stepsize);
}

void PhysicsWorld::worldQuickStep(Real32 stepsize)
{
	dWorldQuickStep(_World, stepsize);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void PhysicsWorld::onCreate(const PhysicsWorld *)
{
	_World = dWorldCreate();
}

void PhysicsWorld::onDestroy()
{
    if(_World)
    {
	    dWorldDestroy(_World);
    }
}

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

void PhysicsWorld::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & ErpFieldMask)
    {
	    dWorldSetERP(_World, getErp());
    }
    if(whichField & CfmFieldMask)
    {
	    dWorldSetCFM(_World, getCfm());
    }
    if(whichField & GravityFieldMask)
    {
	    dWorldSetGravity(_World,getGravity().x(), getGravity().y(), getGravity().z());
    }
    if(whichField & AutoDisableFlagFieldMask)
    {
	    dWorldSetAutoDisableFlag(_World, getAutoDisableFlag());
    }
    if(whichField & AutoDisableLinearThresholdFieldMask)
    {
	    dWorldSetAutoDisableLinearThreshold(_World, getAutoDisableLinearThreshold());
    }
    if(whichField & AutoDisableAngularThresholdFieldMask)
    {
	    dWorldSetAutoDisableAngularThreshold(_World, getAutoDisableAngularThreshold());
    }
    if(whichField & AutoDisableStepsFieldMask)
    {
	    dWorldSetAutoDisableSteps(_World, getAutoDisableSteps());
    }
    if(whichField & AutoDisableTimeFieldMask)
    {
	    dWorldSetAutoDisableTime(_World, getAutoDisableTime());
    }
    if(whichField & WorldQuickStepNumIterationsFieldMask)
    {
	    dWorldSetQuickStepNumIterations(_World, getWorldQuickStepNumIterations());
    }
    if(whichField & WorldContactMaxCorrectingVelFieldMask)
    {
	    dWorldSetContactMaxCorrectingVel(_World, getWorldContactMaxCorrectingVel());
    }
    if(whichField & WorldContactSurfaceLayerFieldMask)
    {
	    dWorldSetContactSurfaceLayer(_World, getWorldContactSurfaceLayer());
    }
}

void PhysicsWorld::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump PhysicsWorld NI" << std::endl;
}

OSG_END_NAMESPACE
