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

#include "OSGPhysicsSphereGeom.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsSphereGeom

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsSphereGeom::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
void PhysicsSphereGeom::onCreate(const PhysicsSphereGeom *)
{
	PhysicsSphereGeomPtr tmpPtr(*this);
	tmpPtr->id = dCreateSphere(0, 1.0f);
	PhysicsSphereGeomBase::setRadius(tmpPtr->getRadius());
    PhysicsGeomBase::setCategoryBits(dGeomGetCategoryBits(id));
    PhysicsGeomBase::setCollideBits(dGeomGetCollideBits(id));
}

void PhysicsSphereGeom::onDestroy()
{
	//empty
}
/***************************************************************************\
*                              Field Get	                               *
\***************************************************************************/
Real32 PhysicsSphereGeom::getRadius(void)
{
	PhysicsSphereGeomPtr tmpPtr(*this);
	return dGeomSphereGetRadius(tmpPtr->id);
}
/***************************************************************************\
*                              Field Set	                               *
\***************************************************************************/

void PhysicsSphereGeom::setRadius(const Real32 &value )
{
	PhysicsSphereGeomPtr tmpPtr(*this);
	dGeomSphereSetRadius(tmpPtr->id, value);
	PhysicsSphereGeomBase::setRadius(value);
}
/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/
void PhysicsSphereGeom::initSphereGeom()
{
    setRadius(PhysicsSphereGeomBase::getRadius());
    initGeom();
}
Real32 PhysicsSphereGeom::getPointDepth(const Vec3f& p)
{
	PhysicsSphereGeomPtr tmpPtr(*this);
	return (Real32)dGeomSpherePointDepth(tmpPtr->id, p.x(), p.y(), p.z());
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsSphereGeom::PhysicsSphereGeom(void) :
    Inherited()
{
}

PhysicsSphereGeom::PhysicsSphereGeom(const PhysicsSphereGeom &source) :
    Inherited(source)
{
}

PhysicsSphereGeom::~PhysicsSphereGeom(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsSphereGeom::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PhysicsSphereGeom::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsSphereGeom NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPhysicsSphereGeom.cpp,v 1.1 2005/10/21 15:44:25 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGPHYSICSSPHEREGEOMBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSSPHEREGEOMBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSSPHEREGEOMFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

