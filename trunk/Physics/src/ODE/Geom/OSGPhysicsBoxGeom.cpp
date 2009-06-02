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
#include "OSGPhysicsConfig.h"

#include "OSGPhysicsBoxGeom.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsBoxGeom

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsBoxGeom::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
/*-------------------------------------------------------------------------*\
-  public                                                                 -
\*-------------------------------------------------------------------------*/
void PhysicsBoxGeom::onCreate(const PhysicsBoxGeom *)
{
	PhysicsBoxGeomPtr tmpPtr(*this);
	tmpPtr->id = dCreateBox(0, 1.0f, 1.0f, 1.0f);
	PhysicsBoxGeomBase::setLenghts(tmpPtr->getLenghts());
    PhysicsGeomBase::setCategoryBits(dGeomGetCategoryBits(id));
    PhysicsGeomBase::setCollideBits(dGeomGetCollideBits(id));
}

void PhysicsBoxGeom::onDestroy()
{
	//empty
}
/***************************************************************************\
*                              Field Get	                               *
\***************************************************************************/
Vec3f PhysicsBoxGeom::getLenghts(void)
{
	PhysicsBoxGeomPtr tmpPtr(*this);
	dVector3 t;
	dGeomBoxGetLengths(tmpPtr->id, t);
    return Vec3f(t[0], t[1], t[2]);
}
/***************************************************************************\
*                              Field Set	                               *
\***************************************************************************/

void PhysicsBoxGeom::setLenghts(const Vec3f &value )
{
	PhysicsBoxGeomPtr tmpPtr(*this);
	dGeomBoxSetLengths(tmpPtr->id, value.x(), value.y(), value.z());
	PhysicsBoxGeomBase::setLenghts(value);
}
/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/
void PhysicsBoxGeom::initBoxGeom()
{
    setLenghts(PhysicsBoxGeomBase::getLenghts());
    initGeom();
}
Real32 PhysicsBoxGeom::getPointDepth(const Vec3f& p)
{
	PhysicsBoxGeomPtr tmpPtr(*this);
	return (Real32)dGeomBoxPointDepth(tmpPtr->id, p.x(), p.y(), p.z());
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsBoxGeom::PhysicsBoxGeom(void) :
    Inherited()
{
}

PhysicsBoxGeom::PhysicsBoxGeom(const PhysicsBoxGeom &source) :
    Inherited(source)
{
}

PhysicsBoxGeom::~PhysicsBoxGeom(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsBoxGeom::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PhysicsBoxGeom::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsBoxGeom NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPhysicsBoxGeom.cpp,v 1.1 2005/10/21 15:44:24 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGPHYSICSBOXGEOMBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSBOXGEOMBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSBOXGEOMFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

