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

#include "OSGPhysicsGeom.h"
#include "ODE/Spaces/OSGPhysicsSpace.h"
#include "ODE/OSGPhysicsBody.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsGeom

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsGeom::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
/*-------------------------------------------------------------------------*\
-  public                                                                 -
\*-------------------------------------------------------------------------*/
void PhysicsGeom::onCreate(const PhysicsGeom *)
{
	PhysicsGeomPtr tmpPtr(*this);
	// geom will be created in subclass
}

void PhysicsGeom::onDestroy()
{
	PhysicsGeomPtr tmpPtr(*this);
	if (tmpPtr->id) {
   		//dGeomDestroy(tmpPtr->id);
        tmpPtr->id = 0;
	}
}

/***************************************************************************\
*                              Field Get	                               *
\***************************************************************************/

Vec3f PhysicsGeom::getPosition(void)
{
	PhysicsGeomPtr tmpPtr(*this);
	const dReal* tmp = dGeomGetPosition(tmpPtr->id);
	return Vec3f(tmp[0], tmp[1], tmp[2]);
}

Matrix PhysicsGeom::getRotation(void)
{
	PhysicsGeomPtr tmpPtr(*this);
	const dReal* tmp = dGeomGetRotation(tmpPtr->id);
	const dMatrix3& rotation = *(const dMatrix3*)tmp;
    return Matrix(rotation[0],rotation[1], rotation[2],0,
        rotation[4], rotation[5], rotation[6], 0,
        rotation[8], rotation[9], rotation[10], 0,
        0,0,0,1);
}

Quaternion PhysicsGeom::getQuaternion(void)
{
	PhysicsGeomPtr tmpPtr(*this);
	dQuaternion q;
	dGeomGetQuaternion(tmpPtr->id, q);
    Quaternion result;
    result.setValueAsQuat(q[1], q[2], q[3], q[0]);
    return result;
}

UInt64 PhysicsGeom::getCategoryBits(void)
{
	PhysicsGeomPtr tmpPtr(*this);
	return (UInt64) dGeomGetCategoryBits(tmpPtr->id);
}

UInt64 PhysicsGeom::getCollideBits(void)
{
	PhysicsGeomPtr tmpPtr(*this);
	return (UInt64) dGeomGetCollideBits(tmpPtr->id);
}

PhysicsSpacePtr PhysicsGeom::getSpace(void)
{
    PhysicsGeomPtr tmpPtr(*this);
    dSpaceID sID = dGeomGetSpace(tmpPtr->id);
    PhysicsSpacePtr space = PhysicsSpacePtr::dcast(PhysicsGeomBase::getSpace());
    assert(space!=NullFC);
    if(sID != space->getSpaceID())
        space->setSpaceID(sID);
    return space;
}

bool PhysicsGeom::getEnable(void)
{
    PhysicsGeomPtr tmpPtr(*this);
    return (dGeomIsEnabled(tmpPtr->id)) ? true : false;
}

dGeomID PhysicsGeom::getGeomID(void)
{
    PhysicsGeomPtr tmpPtr(*this);
    return tmpPtr->id;
}
/***************************************************************************\
*                              Field Set	                               *
\***************************************************************************/

void PhysicsGeom::setBody(const PhysicsBodyPtr &value )
{
	PhysicsGeomPtr tmpPtr(*this);
	dGeomSetBody(tmpPtr->id, value->getBodyID());
	PhysicsGeomBase::setBody(value);
}

void PhysicsGeom::setPosition(const Vec3f &value )
{
	PhysicsGeomPtr tmpPtr(*this);
	dGeomSetPosition(tmpPtr->id, value.x(),value.y(),value.z());
	PhysicsGeomBase::setPosition(value);
}

void PhysicsGeom::setRotation(const Matrix &value )
{
	PhysicsGeomPtr tmpPtr(*this);
	dMatrix3 rotation;
	Vec4f v1 =  value[0];
	Vec4f v2 =  value[1];
	Vec4f v3 =  value[2];
	rotation[0]   = v1.x();
	rotation[1]   = v1.y();
	rotation[2]   = v1.z();
	rotation[3]   = 0;
	rotation[4]   = v2.x();
	rotation[5]   = v2.y();
	rotation[6]   = v2.z();
	rotation[7]   = 0;
	rotation[8]   = v3.x();
	rotation[9]   = v3.y();
	rotation[10]  = v3.z();
	rotation[11]  = 0;
	dGeomSetRotation(tmpPtr->id, rotation);
	PhysicsGeomBase::setRotation(value);
}

void PhysicsGeom::setQuaternion(const Quaternion &value )
{
	PhysicsGeomPtr tmpPtr(*this);
	dQuaternion q;
	q[0]=value.w();
	q[1]=value.x();
	q[2]=value.y();
	q[3]=value.z();
	dGeomSetQuaternion(tmpPtr->id,q);
	PhysicsGeomBase::setQuaternion(value);
}

void PhysicsGeom::setCategoryBits(const UInt64 &value )
{
	PhysicsGeomPtr tmpPtr(*this);
	dGeomSetCategoryBits(tmpPtr->id, value);
	PhysicsGeomBase::setCategoryBits(value);
}

void PhysicsGeom::setCollideBits(const UInt64 &value )
{
	PhysicsGeomPtr tmpPtr(*this);
	dGeomSetCollideBits(tmpPtr->id, value);
	PhysicsGeomBase::setCollideBits(value);
}

void PhysicsGeom::setSpace(const PhysicsSpacePtr &value )
{
    PhysicsGeomPtr tmpPtr(*this);
    dSpaceAdd(value->getSpaceID(), tmpPtr->id);
    PhysicsGeomBase::setSpace(value);
}

void PhysicsGeom::setEnable(const bool &value )
{
    PhysicsGeomPtr tmpPtr(*this);
    if(value)
        dGeomEnable(tmpPtr->id);
    else
        dGeomDisable(tmpPtr->id);
    PhysicsGeomBase::setEnable(value);
}

void PhysicsGeom::setGeomID(const dGeomID &value)
{
    PhysicsGeomPtr tmpPtr(*this);
    tmpPtr->id = value;
}
/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/
void PhysicsGeom::initGeom()
{

    if(PhysicsGeomBase::getBody()!=NullFC)
    {
        setBody(PhysicsGeomBase::getBody());
    }
    else
    {
        setPosition(PhysicsGeomBase::getPosition());
        setRotation(PhysicsGeomBase::getRotation());
        setQuaternion(PhysicsGeomBase::getQuaternion());
    }
    setCategoryBits(PhysicsGeomBase::getCategoryBits());
    setCollideBits(PhysicsGeomBase::getCollideBits());
    setSpace(PhysicsGeomBase::getSpace());
    setEnable(PhysicsGeomBase::getEnable());
}
void PhysicsGeom::getAABB(Real32 aabb[6])
{
	PhysicsGeomPtr tmpPtr(*this);
	dReal t[6];
	dGeomGetAABB(tmpPtr->id, t);
	aabb[0] = t[0];
	aabb[1] = t[1];
	aabb[2] = t[2];
	aabb[3] = t[3];
	aabb[4] = t[4];
	aabb[5] = t[5];
}

Int32 PhysicsGeom::isSpace(void)
{
	PhysicsGeomPtr tmpPtr(*this);
	return dGeomIsSpace(tmpPtr->id);
}

Int32 PhysicsGeom::getGeomClass(void)
{
	PhysicsGeomPtr tmpPtr(*this);
	return dGeomGetClass(tmpPtr->id);
}

void PhysicsGeom::setData( void* someData)
{
	PhysicsGeomPtr tmpPtr(*this);
	dGeomSetData(tmpPtr->id, someData);
}

void* PhysicsGeom::getData(void)
{
	PhysicsGeomPtr tmpPtr(*this);
	return dGeomGetData(tmpPtr->id);

}

void PhysicsGeom::Collide2(dGeomID otherGID, void* someData, dNearCallback* callback)
{
	PhysicsGeomPtr tmpPtr(*this);
	dSpaceCollide2(tmpPtr->id, otherGID, someData, callback);
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsGeom::PhysicsGeom(void) :
    Inherited()
{
}

PhysicsGeom::PhysicsGeom(const PhysicsGeom &source) :
    Inherited(source)
{
}

PhysicsGeom::~PhysicsGeom(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsGeom::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PhysicsGeom::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsGeom NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPhysicsGeom.cpp,v 1.2 2006/08/19 00:21:46 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGPHYSICSGEOMBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSGEOMBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSGEOMFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

