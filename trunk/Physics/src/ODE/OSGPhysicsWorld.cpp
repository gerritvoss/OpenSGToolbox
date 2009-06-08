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
    SLOG << "ODE Configuration: " << dGetConfiguration() << std::endl;
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

dWorldID PhysicsWorld::getWorldID(void)
{
    return _World;
}

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

