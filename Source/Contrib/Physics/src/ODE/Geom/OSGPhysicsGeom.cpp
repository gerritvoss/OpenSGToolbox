/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com),  Behboud Kalantary         *
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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGPhysicsGeom.h"
#include "OSGPhysicsSpace.h"
#include "OSGPhysicsBody.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPhysicsGeomBase.cpp file.
// To modify it, please change the .fcd file (OSGPhysicsGeom.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsGeom::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
bool PhysicsGeom::isPlaceable(void) const
{
    return true;
}

Matrix PhysicsGeom::getTransformation(void) const
{
    Matrix Transformation;
    
    Vec3f Translation;
    const dReal* t = dGeomGetOffsetPosition(_GeomID);
    Translation.setValues( t[0],t[1],t[2] );

    dQuaternion q;
    dGeomGetOffsetQuaternion(_GeomID, q);
    Quaternion Rotation;
    Rotation.setValueAsQuat(q[1], q[2], q[3], q[0]);

    Transformation.setTransform(Translation,Rotation);

    if(isPlaceable())
    {

        t = dGeomGetPosition(_GeomID);
        Translation.setValues( t[0],t[1],t[2] );

        dGeomGetQuaternion(_GeomID, q);
        Rotation.setValueAsQuat(q[1], q[2], q[3], q[0]);

        Matrix NonBodyTransformation;
        NonBodyTransformation.setTransform(Translation,Rotation);
        Transformation.mult(NonBodyTransformation);
    }

    return Transformation;
}

dGeomID PhysicsGeom::getGeomID(void) const
{
    return _GeomID;
}

void PhysicsGeom::setGeomID(const dGeomID &value)
{
    _GeomID = value;
}

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

void PhysicsGeom::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & BodyFieldMask)
    {
        if(getBody() != NULL)
        {
	        dGeomSetBody(_GeomID, getBody()->getBodyID());
        }
        else
        {
	        dGeomSetBody(_GeomID, 0);
        }
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
    if(whichField & OffsetPositionFieldMask &&
        getBody() != NULL)
    {
	    dGeomSetOffsetPosition(_GeomID, getOffsetPosition().x(),getOffsetPosition().y(),getOffsetPosition().z());
    }
    if(whichField & OffsetRotationFieldMask &&
        getBody() != NULL)
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
    if(whichField & OffsetQuaternionFieldMask && getBody() != NULL)
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
        dSpaceID CurSpace(dGeomGetSpace(_GeomID));
     
        if(CurSpace != 0 &&
           (getSpace() == NULL ||
            CurSpace != getSpace()->getSpaceID()))
        {
            dSpaceRemove(CurSpace,_GeomID);
        }

        if(getSpace() != NULL)
        {
	        dSpaceAdd(getSpace()->getSpaceID(), _GeomID);
        }
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

OSG_END_NAMESPACE
