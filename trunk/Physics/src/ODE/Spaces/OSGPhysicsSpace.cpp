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
#include <ode/ode.h>

#include <OpenSG/OSGConfig.h>
#include "OSGPhysicsDef.h"

#include "OSGPhysicsSpace.h"

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

void PhysicsSpace::Collide( void* somedata, dNearCallback* callback )
{
	PhysicsSpacePtr tmpPtr(*this);
	dSpaceCollide(tmpPtr->sID, somedata, callback);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsSpace::PhysicsSpace(void) :
    Inherited()
{
}

PhysicsSpace::PhysicsSpace(const PhysicsSpace &source) :
    Inherited(source)
{
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

