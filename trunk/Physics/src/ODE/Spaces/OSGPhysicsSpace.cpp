/*---------------------------------------------------------------------------*\
 *                         OpenSG ToolBox Physics                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                          www.vrac.iastate.edu                             *
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
#include <ode/ode.h>

#include <OpenSG/OSGConfig.h>
#include "OSGPhysicsDef.h"

#include "OSGPhysicsSpace.h"
#include "ODE/OSGPhysicsWorld.h"
#include "ODE/OSGPhysicsHandler.h"
#include <OpenSG/OSGStatCollector.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsSpace

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsSpace::initMethod (void)
{
}

void PhysicsSpace::collisionCallback (void *data, dGeomID o1, dGeomID o2)
{
    reinterpret_cast<PhysicsSpace*>(data)->collisionCallback(o1,o2);
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
/*-------------------------------------------------------------------------*\
-  public                                                                 -
\*-------------------------------------------------------------------------*/
void PhysicsSpace::onCreate(const PhysicsSpace *id /* = NULL */)
{
	//spaces are created in subclasses
}

void PhysicsSpace::onDestroy()
{
	PhysicsSpacePtr tmpPtr(*this);
    if(tmpPtr->sID)
    {
	    //dSpaceDestroy(tmpPtr->sID);
        tmpPtr->sID = 0;
    }
}

void PhysicsSpace::collisionCallback (dGeomID o1, dGeomID o2)
{
    getParentHandler()->getStatistics()->getElem(PhysicsHandler::statNCollisionTests)->inc();

    if (dGeomIsSpace (o1) || dGeomIsSpace (o2))
    {
        // colliding a space with something
        dSpaceCollide2 (o1,o2,reinterpret_cast<void *>(this),&PhysicsSpace::collisionCallback);
        // collide all geoms internal to the space(s)
        if (dGeomIsSpace (o1)) dSpaceCollide (dGeomGetSpace(o1),reinterpret_cast<void *>(this),&PhysicsSpace::collisionCallback);
        if (dGeomIsSpace (o2)) dSpaceCollide (dGeomGetSpace(o2),reinterpret_cast<void *>(this),&PhysicsSpace::collisionCallback);
    }
    else
    {
        // colliding two non-space geoms, so generate contact
        // points between o1 and o2
        Int32 numContacts = dCollide(o1, o2, _ContactJoints.size(), 
            &(_ContactJoints[0].geom), sizeof(dContact));
    
        getParentHandler()->getStatistics()->getElem(PhysicsHandler::statNCollisions)->add(numContacts);

        // add these contact points to the simulation
        for (Int32 i=0; i < numContacts; i++)
        {
            dJointID jointId = dJointCreateContact(_CollideWorldID, 
                _ColJointGroupId, 
                &_ContactJoints[i]);

            dJointAttach(jointId, dGeomGetBody(o1), dGeomGetBody(o2));
        }
    }
}
/***************************************************************************\
*                              Field Get	                               *
\***************************************************************************/

bool PhysicsSpace::getCleanup(void)
{
	PhysicsSpacePtr tmpPtr(*this);
	return dSpaceGetCleanup(tmpPtr->sID)==1;
}

dSpaceID PhysicsSpace::getSpaceID(void)
{
    PhysicsSpacePtr tmpPtr(*this);
    return tmpPtr->sID;
}
/***************************************************************************\
*                              Field Set	                               *
\***************************************************************************/
void PhysicsSpace::setCleanup(const bool &value )
{
	PhysicsSpacePtr tmpPtr(*this);
	dSpaceSetCleanup(tmpPtr->sID, value ? 1 : 0);
}

void PhysicsSpace::setSpaceID(const dSpaceID &value )
{
    PhysicsSpacePtr tmpPtr(*this);
    tmpPtr->sID = value;
}
/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/
void PhysicsSpace::initSpace()
{
    setCleanup(PhysicsSpaceBase::getCleanup());
}
void PhysicsSpace::AddGeom( dGeomID g)
{
	PhysicsSpacePtr tmpPtr(*this);
	dSpaceAdd(tmpPtr->sID, g);
}

void PhysicsSpace::RemoveGeom( dGeomID g)
{
	PhysicsSpacePtr tmpPtr(*this);
	dSpaceRemove(tmpPtr->sID, g);
}

bool PhysicsSpace::ContainsGeom( dGeomID g)
{
	PhysicsSpacePtr tmpPtr(*this);
	return dSpaceQuery(tmpPtr->sID, g) == 1;
}

void PhysicsSpace::AddSpace( dSpaceID s)
{
	PhysicsSpacePtr tmpPtr(*this);
	dSpaceAdd(tmpPtr->sID, (dGeomID)s);
}

void PhysicsSpace::RemoveSpace( dSpaceID s)
{
	PhysicsSpacePtr tmpPtr(*this);
	dSpaceRemove(tmpPtr->sID, (dGeomID)s);
}

bool PhysicsSpace::ContainsSpace( dSpaceID s)
{
	PhysicsSpacePtr tmpPtr(*this);
	return dSpaceQuery(tmpPtr->sID, (dGeomID)s) == 1;
}

Int32 PhysicsSpace::GetNumGeoms()
{
	PhysicsSpacePtr tmpPtr(*this);
	return dSpaceGetNumGeoms(tmpPtr->sID);
}

dGeomID PhysicsSpace::GetGeom( Int32 i )
{
	PhysicsSpacePtr tmpPtr(*this);
	return dSpaceGetGeom(tmpPtr->sID, i);
}

void PhysicsSpace::Collide( PhysicsWorldPtr w )
{
    _CollideWorldID = w->getWorldID();
    
    //free contact Joints
    dJointGroupEmpty(_ColJointGroupId);

	PhysicsSpacePtr tmpPtr(*this);
	dSpaceCollide(tmpPtr->sID, reinterpret_cast<void *>(this), &PhysicsSpace::collisionCallback);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsSpace::PhysicsSpace(void) :
    Inherited()
{
    _ContactJoints.resize(MAX_PHYS_CONTACTS);
    _ColJointGroupId = dJointGroupCreate(0);
    for (Int32 index = 0; index < _ContactJoints.size(); index++)
    {
        _ContactJoints[index].surface.mode = dContactApprox1;
        _ContactJoints[index].surface.mu = 0.75;
    }
}

PhysicsSpace::PhysicsSpace(const PhysicsSpace &source) :
    Inherited(source)
{
    _ContactJoints.resize(MAX_PHYS_CONTACTS);
    _ColJointGroupId = dJointGroupCreate(0);
    for (Int32 index = 0; index < _ContactJoints.size(); index++)
    {
        _ContactJoints[index].surface.mode = dContactApprox1;
        _ContactJoints[index].surface.mu = 0.75;
        //_ContactJoints[index].surface.mode = dContactApprox1 | dContactBounce;
        //_ContactJoints[index].surface.mu = 0.75;
        //_ContactJoints[index].surface.bounce = 0.1;
        //_ContactJoints[index].surface.mode = dContactBounce;
        //_ContactJoints[index].surface.mu = 0.75;
        //_ContactJoints[index].surface.bounce = 0.9;
    }
}

PhysicsSpace::~PhysicsSpace(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsSpace::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PhysicsSpace::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsSpace NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPhysicsSpace.cpp,v 1.1 2005/10/21 15:44:25 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGPHYSICSSPACEBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSSPACEBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSSPACEFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

