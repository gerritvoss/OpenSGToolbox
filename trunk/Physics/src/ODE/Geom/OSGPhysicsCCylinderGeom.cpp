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

#include "OSGPhysicsCCylinderGeom.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsCCylinderGeom

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsCCylinderGeom::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
void PhysicsCCylinderGeom::onCreate(const PhysicsCCylinderGeom *)
{
	PhysicsCCylinderGeomPtr tmpPtr(*this);
	tmpPtr->id = dCreateCCylinder(0, 1.0f, 1.0f);
	PhysicsCCylinderGeomBase::setParams(tmpPtr->getParams());
    PhysicsGeomBase::setCategoryBits(dGeomGetCategoryBits(id));
    PhysicsGeomBase::setCollideBits(dGeomGetCollideBits(id));
}

void PhysicsCCylinderGeom::onDestroy()
{
	//empty
}
/***************************************************************************\
*                              Field Get	                               *
\***************************************************************************/
Vec2f PhysicsCCylinderGeom::getParams(void)
{
	PhysicsCCylinderGeomPtr tmpPtr(*this);
	dReal u,v;
	dGeomCCylinderGetParams(tmpPtr->id, &u, &v);
	return Vec2f(u, v);
}
/***************************************************************************\
*                              Field Set	                               *
\***************************************************************************/

void PhysicsCCylinderGeom::setParams(const Vec2f &value )
{
	PhysicsCCylinderGeomPtr tmpPtr(*this);
	dGeomCCylinderSetParams(tmpPtr->id, value.x(), value.y());
	PhysicsCCylinderGeomBase::setParams(value);
}
/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/
void PhysicsCCylinderGeom::initCCylinderGeom()
{
    setParams(PhysicsCCylinderGeomBase::getParams());
    initGeom();
}
Real32 PhysicsCCylinderGeom::getPointDepth(const Vec3f& p)
{
	PhysicsCCylinderGeomPtr tmpPtr(*this);
	return (Real32)dGeomCCylinderPointDepth(tmpPtr->id, p.x(), p.y(), p.z());
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsCCylinderGeom::PhysicsCCylinderGeom(void) :
    Inherited()
{
}

PhysicsCCylinderGeom::PhysicsCCylinderGeom(const PhysicsCCylinderGeom &source) :
    Inherited(source)
{
}

PhysicsCCylinderGeom::~PhysicsCCylinderGeom(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsCCylinderGeom::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PhysicsCCylinderGeom::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsCCylinderGeom NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPhysicsCCylinderGeom.cpp,v 1.1 2005/10/21 15:44:24 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGPHYSICSCCYLINDERGEOMBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSCCYLINDERGEOMBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSCCYLINDERGEOMFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

