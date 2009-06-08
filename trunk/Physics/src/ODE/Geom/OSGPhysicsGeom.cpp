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
	// geom will be created in subclass
}

void PhysicsGeom::onDestroy()
{
	if (_GeomID) {
   		//dGeomDestroy(_GeomID);
        _GeomID = 0;
	}
}

/***************************************************************************\
*                              Field Get	                               *
\***************************************************************************/
dGeomID PhysicsGeom::getGeomID(void) const
{
    return _GeomID;
}
/***************************************************************************\
*                              Field Set	                               *
\***************************************************************************/
void PhysicsGeom::setGeomID(const dGeomID &value)
{
    _GeomID = value;
}
/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/
void PhysicsGeom::getAABB(Real32 aabb[6]) const
{
	dReal t[6];
	dGeomGetAABB(_GeomID, t);
	aabb[0] = t[0];
	aabb[1] = t[1];
	aabb[2] = t[2];
	aabb[3] = t[3];
	aabb[4] = t[4];
	aabb[5] = t[5];
}

bool PhysicsGeom::isSpace(void) const
{
	return static_cast<bool>(dGeomIsSpace(_GeomID));
}

void PhysicsGeom::clearOffset(void)
{
    dGeomClearOffset(_GeomID);
}

Int32 PhysicsGeom::getGeomClass(void) const
{
	return dGeomGetClass(_GeomID);
}

void PhysicsGeom::setData( void* someData)
{
	dGeomSetData(_GeomID, someData);
}

void* PhysicsGeom::getData(void) const
{
	return dGeomGetData(_GeomID);

}

void PhysicsGeom::Collide2(dGeomID otherGID, void* someData, dNearCallback* callback)
{
	dSpaceCollide2(_GeomID, otherGID, someData, callback);
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

    if(whichField & BodyFieldMask)
    {
	    dGeomSetBody(_GeomID, getBody()->getBodyID());
    }
    if(whichField & PositionFieldMask)
    {
	    dGeomSetPosition(_GeomID, getPosition().x(),getPosition().y(),getPosition().z());
    }
    if(whichField & RotationFieldMask)
    {
	    dMatrix3 rotation;
	    Vec4f v1 =  getRotation()[0];
	    Vec4f v2 =  getRotation()[1];
	    Vec4f v3 =  getRotation()[2];
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
	    dGeomSetRotation(_GeomID, rotation);
    }
    if(whichField & QuaternionFieldMask)
    {
	    dQuaternion q;
	    q[0]=getQuaternion().w();
	    q[1]=getQuaternion().x();
	    q[2]=getQuaternion().y();
	    q[3]=getQuaternion().z();
	    dGeomSetQuaternion(_GeomID,q);
    }
    if(whichField & OffsetPositionFieldMask)
    {
	    dGeomSetOffsetPosition(_GeomID, getOffsetPosition().x(),getOffsetPosition().y(),getOffsetPosition().z());
    }
    if(whichField & OffsetRotationFieldMask)
    {
	    dMatrix3 rotation;
	    Vec4f v1 =  getOffsetRotation()[0];
	    Vec4f v2 =  getOffsetRotation()[1];
	    Vec4f v3 =  getOffsetRotation()[2];
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
	    dGeomSetOffsetRotation(_GeomID, rotation);
    }
    if(whichField & OffsetQuaternionFieldMask)
    {
	    dQuaternion q;
	    q[0]=getOffsetQuaternion().w();
	    q[1]=getOffsetQuaternion().x();
	    q[2]=getOffsetQuaternion().y();
	    q[3]=getOffsetQuaternion().z();
	    dGeomSetOffsetQuaternion(_GeomID,q);
    }
    if(whichField & CategoryBitsFieldMask)
    {
	    dGeomSetCategoryBits(_GeomID, getCategoryBits());
    }
    if(whichField & CollideBitsFieldMask)
    {
	    dGeomSetCollideBits(_GeomID, getCollideBits());
    }
    if(whichField & SpaceFieldMask)
    {
	    dSpaceAdd(getSpace()->getSpaceID(), _GeomID);
    }
    if(whichField & EnableFieldMask)
    {
        if(getEnable())
        {
            dGeomEnable(_GeomID);
        }
        else
        {
            dGeomDisable(_GeomID);
        }
    }
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

