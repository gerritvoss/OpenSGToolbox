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

#include "OSGPhysicsPlaneGeom.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsPlaneGeom

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsPlaneGeom::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
void PhysicsPlaneGeom::onCreate(const PhysicsPlaneGeom *)
{
	PhysicsPlaneGeomPtr tmpPtr(*this);
	tmpPtr->id = dCreatePlane(0, 0, 0, 1, 0);
	PhysicsPlaneGeomBase::setParams(tmpPtr->getParams());
    PhysicsGeomBase::setCategoryBits(dGeomGetCategoryBits(id));
    PhysicsGeomBase::setCollideBits(dGeomGetCollideBits(id));
}

void PhysicsPlaneGeom::onDestroy()
{
	//empty
}
/***************************************************************************\
*                              Field Get	                               *
\***************************************************************************/
Vec4f PhysicsPlaneGeom::getParams(void)
{
	PhysicsPlaneGeomPtr tmpPtr(*this);
	dVector4 t;
	dGeomPlaneGetParams(tmpPtr->id, t);
	return Vec4f(t[0], t[1],t[2], t[3]);
}
/***************************************************************************\
*                              Field Set	                               *
\***************************************************************************/

void PhysicsPlaneGeom::setParams(const Vec4f &value )
{
	PhysicsPlaneGeomPtr tmpPtr(*this);
	dGeomPlaneSetParams(tmpPtr->id, value.x(), value.y(), value.z(), value.w());
	PhysicsPlaneGeomBase::setParams(value);
}
/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/
void PhysicsPlaneGeom::initPlaneGeom()
{
    setParams(PhysicsPlaneGeomBase::getParams());
    initGeom();
}
Real32 PhysicsPlaneGeom::getPointDepth(const Vec3f& p)
{
	PhysicsPlaneGeomPtr tmpPtr(*this);
	return (Real32)dGeomPlanePointDepth(tmpPtr->id, p.x(), p.y(), p.z());
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsPlaneGeom::PhysicsPlaneGeom(void) :
    Inherited()
{
}

PhysicsPlaneGeom::PhysicsPlaneGeom(const PhysicsPlaneGeom &source) :
    Inherited(source)
{
}

PhysicsPlaneGeom::~PhysicsPlaneGeom(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsPlaneGeom::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PhysicsPlaneGeom::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsPlaneGeom NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPhysicsPlaneGeom.cpp,v 1.1 2005/10/21 15:44:25 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGPHYSICSPLANEGEOMBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSPLANEGEOMBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSPLANEGEOMFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

