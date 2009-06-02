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
#include <OpenSG/OSGGeometry.h>
#include <OpenSG/OSGTriangleIterator.h>
#include <OpenSG/OSGFaceIterator.h>
#include <OpenSG/OSGGeoFunctions.h>

#include "OSGPhysicsTriMeshGeom.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PhysicsTriMeshGeom

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsTriMeshGeom::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
/***************************************************************************\
*                              Field Get	                               *
\***************************************************************************/
NodePtr PhysicsTriMeshGeom::getGeometryNode(void)
{
    PhysicsTriMeshGeomPtr tmpPtr(*this);
    if(tmpPtr->geoNode!=NullFC)
        return tmpPtr->geoNode;
    else
        return NullFC;
}
/***************************************************************************\
*                              Field Set	                               *
\***************************************************************************/
void PhysicsTriMeshGeom::setGeometryNode(NodePtr& node)
{
    PhysicsTriMeshGeomPtr tmpPtr(*this);

    GeometryPtr geo = GeometryPtr::dcast(node->getCore());
    if(geo!=NullFC)
    {
        calcVertexNormals(geo, deg2rad( 30));
        separateProperties(geo);
        createSingleIndex(geo);

        GeoPositions3f::StoredFieldType* positions = 
            GeoPositions3fPtr::dcast( geo->getPositions())->getFieldPtr();
        GeoIndicesUI32::StoredFieldType* indices = 
            GeoIndicesUI32Ptr::dcast( geo->getIndices())->getFieldPtr();
        GeoNormals3f::StoredFieldType* normals = 
            GeoNormals3fPtr::dcast( geo->getNormals())->getFieldPtr(); 

        GeoPTypesPtr geoTypes = geo->getTypes();
        bool triangles = false;
        //has to be some triangle soup!
        for( Int32 i=0; i < geoTypes->size(); ++i) {
            switch( geoTypes->getValue(i)) {
            case GL_TRIANGLES:
                triangles=true;
                break;
            case GL_TRIANGLE_STRIP:
                triangles=true;
                break;
            case GL_TRIANGLE_FAN:
                triangles=true;
                break;
            }
        }

        UInt32 vertexCount = 
            GeoPositions3fPtr::dcast(geo->getPositions())->getSize();
        UInt32 vertexStride = 3*sizeof(Real32);
        UInt32 indexCount = 
            GeoIndicesUI32Ptr::dcast(geo->getIndices())->getSize();
        UInt32 indexStride = 3*sizeof(UInt32);

        //pass the pointers to ODE
        if(tmpPtr->data)
            dGeomTriMeshDataDestroy(tmpPtr->data);
        tmpPtr->data = dGeomTriMeshDataCreate();
        if(triangles)
        {
            dGeomTriMeshDataBuildSingle(tmpPtr->data, (Real32*)&positions->front(), 
                vertexStride, vertexCount, (Int32*)&indices->front(), indexCount, 
                indexStride/* just can't use this, (Real32*)&normals->front()*/);
            tmpPtr->setData(tmpPtr->data);
                
            /* use this method if you build with single precision
            dGeomTriMeshDataBuildSingle1(tmpPtr->data, (Real32*)&positions->front(), 
                vertexStride, vertexCount, (Int32*)&indices->front(), indexCount, 
                indexStride, (Real32*)&normals->front());
            tmpPtr->setData(tmpPtr->data);
            */
            
        }
        else
        {
            FWARNING(("No triangle mesh given to ODE! Convert to triangles first!\n"));
            tmpPtr->setData(tmpPtr->data);
        }
    }
    tmpPtr->geoNode=node;
    PhysicsTriMeshGeomBase::setGeometryNode(node);
}
/*-------------------------------------------------------------------------*\
-  public                                                                 -
\*-------------------------------------------------------------------------*/
void PhysicsTriMeshGeom::onCreate(const PhysicsTriMeshGeom *)
{
	PhysicsTriMeshGeomPtr tmpPtr(*this);
	tmpPtr->id = dCreateTriMesh(0, 0, 0, 0, 0);
	data = 0;
    numVertices = 0;
    numFaces = 0;
    vertexData = 0;
    faceData = 0;
    normalData = 0;
    geoNode=NullFC;
    PhysicsGeomBase::setCategoryBits(dGeomGetCategoryBits(id));
    PhysicsGeomBase::setCollideBits(dGeomGetCollideBits(id));
}

void PhysicsTriMeshGeom::onDestroy()
{
	PhysicsTriMeshGeomPtr tmpPtr(*this);
	if (tmpPtr->data) dGeomTriMeshDataDestroy(tmpPtr->data);
    if(vertexData) free((void*)vertexData);
    if(faceData) free((void*)faceData);
    if(normalData) free((void*)normalData);
    geoNode=NullFC;
}


/***************************************************************************\
*                              Class Specific                              *
\***************************************************************************/
void PhysicsTriMeshGeom::initTriMeshGeom()
{
    setGeometryNode(PhysicsTriMeshGeomBase::getGeometryNode());
    initGeom();
}
void PhysicsTriMeshGeom::setCallback( dTriCallback* callback )
{
	PhysicsTriMeshGeomPtr tmpPtr(*this);
	dGeomTriMeshSetCallback(tmpPtr->id, callback);
}

dTriCallback* PhysicsTriMeshGeom::getCallback(void)
{
	PhysicsTriMeshGeomPtr tmpPtr(*this);
	return dGeomTriMeshGetCallback(tmpPtr->id);
}

dTriArrayCallback* PhysicsTriMeshGeom::getArrayCallback(void)
{
	PhysicsTriMeshGeomPtr tmpPtr(*this);
	return dGeomTriMeshGetArrayCallback(tmpPtr->id);
}

void PhysicsTriMeshGeom::setRayCallback( dTriRayCallback* callback )
{
	PhysicsTriMeshGeomPtr tmpPtr(*this);
	dGeomTriMeshSetRayCallback(tmpPtr->id, callback);
}

dTriRayCallback* PhysicsTriMeshGeom::getRayCallback(void)
{
	PhysicsTriMeshGeomPtr tmpPtr(*this);
	return dGeomTriMeshGetRayCallback(tmpPtr->id);
}

void PhysicsTriMeshGeom::setData( dTriMeshDataID data )
{
	PhysicsTriMeshGeomPtr tmpPtr(*this);
	dGeomTriMeshSetData(tmpPtr->id, data);
}

void PhysicsTriMeshGeom::enableTC( Int32 geomClass, bool enable )
{
	PhysicsTriMeshGeomPtr tmpPtr(*this);
	dGeomTriMeshEnableTC(tmpPtr->id, geomClass, enable ? 1:0);
}

bool PhysicsTriMeshGeom::isTCEnabled( Int32 geomClass)
{
	PhysicsTriMeshGeomPtr tmpPtr(*this);
	return dGeomTriMeshIsTCEnabled(tmpPtr->id, geomClass) == 1;
}

void PhysicsTriMeshGeom::clearTCCache(void)
{
	PhysicsTriMeshGeomPtr tmpPtr(*this);
	dGeomTriMeshClearTCCache(tmpPtr->id);
}

void PhysicsTriMeshGeom::getTriangle( Int32 index, Vec3f& v0, Vec3f& v1, Vec3f& v2 )
{
	PhysicsTriMeshGeomPtr tmpPtr(*this);
	dVector3 _v0, _v1, _v2;
	dGeomTriMeshGetTriangle(tmpPtr->id, index, &_v0, &_v1, &_v2);
	v0.setValue(Vec3f(_v0[0], _v0[1], _v0[2]));
	v1.setValue(Vec3f(_v1[0], _v1[1], _v1[2]));
	v2.setValue(Vec3f(_v2[0], _v2[1], _v2[2]));
}

void PhysicsTriMeshGeom::getPoint( Int32 index, Real32 u, Real32 v, Vec3f& out )
{
	PhysicsTriMeshGeomPtr tmpPtr(*this);
	dVector3 _out;
	dGeomTriMeshGetPoint(tmpPtr->id, index, u, v, _out);
	out.setValue(Vec3f(_out[0], _out[1], _out[2]));
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PhysicsTriMeshGeom::PhysicsTriMeshGeom(void) :
    Inherited()
{
}

PhysicsTriMeshGeom::PhysicsTriMeshGeom(const PhysicsTriMeshGeom &source) :
    Inherited(source)
{
}

PhysicsTriMeshGeom::~PhysicsTriMeshGeom(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PhysicsTriMeshGeom::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PhysicsTriMeshGeom::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PhysicsTriMeshGeom NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPhysicsTriMeshGeom.cpp,v 1.1 2005/10/21 15:44:25 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGPHYSICSTRIMESHGEOMBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPHYSICSTRIMESHGEOMBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPHYSICSTRIMESHGEOMFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

