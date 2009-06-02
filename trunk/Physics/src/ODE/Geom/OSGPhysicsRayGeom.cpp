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

#include "OSGPhysicsRayGeom.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsRayGeom

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsRayGeom::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
/*-------------------------------------------------------------------------*\
-  public                                                                 -
\*-------------------------------------------------------------------------*/
void PhysicsRayGeom::onCreate(const PhysicsRayGeom *)
{
	PhysicsRayGeomPtr tmpPtr(*this);
	tmpPtr->id = dCreateRay(0, 1.0f);
	PhysicsRayGeomBase::setLenght(tmpPtr->getLenght());
}

void PhysicsRayGeom::onDestroy()
{
	//empty
}
/***************************************************************************\
*                              Field Get	                               *
\***************************************************************************/
Real32 PhysicsRayGeom::getLenght(void)
{
	PhysicsRayGeomPtr tmpPtr(*this);
	return dGeomRayGetLength(tmpPtr->id);
}

/***************************************************************************\
*                              Field Set	                               *
\***************************************************************************/

void PhysicsRayGeom::setLenght(const Real32 &value )
{
	PhysicsRayGeomPtr tmpPtr(*this);
	dGeomRaySetLength(tmpPtr->id, value);
	PhysicsRayGeomBase::setLenght(value);
}

/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/
void PhysicsRayGeom::initRayGeom()
{
    setLenght(PhysicsRayGeomBase::getLenght());
    initGeom();
}
void PhysicsRayGeom::set(const Vec3f& pos, const Vec3f& dir)
{
	PhysicsRayGeomPtr tmpPtr(*this);
	dGeomRaySet(tmpPtr->id,pos.x(), pos.y(), pos.z(), dir.x(), dir.y(), dir.z());
}

void PhysicsRayGeom::get(Vec3f& start, Vec3f& dir)
{
	PhysicsRayGeomPtr tmpPtr(*this);
	dVector3 s,d;
	dGeomRayGet(tmpPtr->id,s, d);
	start.setValue(Vec3f(s[0], s[1], s[2]));
	dir.setValue(Vec3f(d[0], d[1], d[2]));
}

void PhysicsRayGeom::setClosestHit(bool closestHit)
{
	PhysicsRayGeomPtr tmpPtr(*this);
	dGeomRaySetClosestHit(tmpPtr->id, closestHit ? 1:0);
}

bool PhysicsRayGeom::getClosestHit(void)
{
	PhysicsRayGeomPtr tmpPtr(*this);
	return dGeomRayGetClosestHit(tmpPtr->id) ==1;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsRayGeom::PhysicsRayGeom(void) :
    Inherited()
{
}

PhysicsRayGeom::PhysicsRayGeom(const PhysicsRayGeom &source) :
    Inherited(source)
{
}

PhysicsRayGeom::~PhysicsRayGeom(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsRayGeom::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PhysicsRayGeom::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsRayGeom NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPhysicsRayGeom.cpp,v 1.1 2005/10/21 15:44:25 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGPHYSICSRAYGEOMBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSRAYGEOMBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSRAYGEOMFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

