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

#include "OSGPhysicsTriMeshGeom.h"
#include "OSGGeometry.h"
#include "OSGTriangleIterator.h"
#include "OSGFaceIterator.h"
#include "OSGGeoFunctions.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPhysicsTriMeshGeomBase.cpp file.
// To modify it, please change the .fcd file (OSGPhysicsTriMeshGeom.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PhysicsTriMeshGeom::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void PhysicsTriMeshGeom::createODEGeometry(NodeUnrecPtr node)
{

    GeometryUnrecPtr geo = dynamic_pointer_cast<Geometry>(deepClone(dynamic_cast<Geometry*>(node->getCore())));
    if(geo!=NULL)
    {
        
        //calcVertexNormals(geo, deg2rad( 30));
        //separateProperties(geo);
        //createSingleIndex(geo);

        GeoVectorProperty* positions = geo->getPositions();

        GeoVectorProperty* normals = geo->getNormals();

        //Get this nodes Transformation
        Matrix ToWorldMat(node->getToWorld());

        //Get all of the transformed Positions
        _Positions.clear();
        for(UInt32 i = 0; i < positions->size(); ++i)
        {
            _Positions.push_back(ToWorldMat * positions->getValue<Pnt3f>(i));
        }

        UInt32 VertexStride = 3*sizeof(Real32);
        UInt32 VertexCount = _Positions.size();
        UInt32 IndexStride = 3*sizeof(dTriIndex);

        //Create a Index array that ODE can understand
        TriangleIterator TriItor;
        for(TriItor = geo->beginTriangles() ; TriItor != geo->endTriangles() ; ++TriItor)
        {
            _TriIndexes.push_back(TriItor.getPositionIndex(0));
            _TriIndexes.push_back(TriItor.getPositionIndex(1));
            _TriIndexes.push_back(TriItor.getPositionIndex(2));
        }
        //pass the pointers to ODE
        if(_TriMeshData)
        {
            dGeomTriMeshDataDestroy(_TriMeshData);
        }
        _TriMeshData = dGeomTriMeshDataCreate();
        if(_TriIndexes.size() > 0)
        {
            dGeomTriMeshDataBuildSingle(_TriMeshData, (Real32*)&_Positions.front(), 
                VertexStride, VertexCount, &_TriIndexes[0], _TriIndexes.size(), 
                IndexStride/* , (Real32*)&normals->front()*/);
            setData(_TriMeshData);
                
            /* use this method if you build with single precision
            dGeomTriMeshDataBuildSingle1(_TriMeshData, (Real32*)&positions->front(), 
                vertexStride, vertexCount, (Int32*)&indices->front(), indexCount, 
                indexStride, (Real32*)&normals->front());
            setData(_TriMeshData);
            */
            
        }
        else
        {
            SWARNING << "PhysicsTriMeshGeom: No triangle mesh given to ODE! Convert to triangles first!\n";
            setData(_TriMeshData);
        }
    }
}

void PhysicsTriMeshGeom::setCallback( dTriCallback* callback )
{
	dGeomTriMeshSetCallback(_GeomID, callback);
}

dTriCallback* PhysicsTriMeshGeom::getCallback(void) const
{
	return dGeomTriMeshGetCallback(_GeomID);
}

dTriArrayCallback* PhysicsTriMeshGeom::getArrayCallback(void) const
{
	return dGeomTriMeshGetArrayCallback(_GeomID);
}

void PhysicsTriMeshGeom::setRayCallback( dTriRayCallback* callback )
{
	dGeomTriMeshSetRayCallback(_GeomID, callback);
}

dTriRayCallback* PhysicsTriMeshGeom::getRayCallback(void) const
{
	return dGeomTriMeshGetRayCallback(_GeomID);
}

void PhysicsTriMeshGeom::setData( dTriMeshDataID data )
{
    _TriMeshData = data;
	dGeomTriMeshSetData(_GeomID, _TriMeshData);
}

void PhysicsTriMeshGeom::enableTC( Int32 geomClass, bool enable )
{
	dGeomTriMeshEnableTC(_GeomID, geomClass, enable ? 1:0);
}

bool PhysicsTriMeshGeom::isTCEnabled( Int32 geomClass) const
{
	return dGeomTriMeshIsTCEnabled(_GeomID, geomClass) == 1;
}

void PhysicsTriMeshGeom::clearTCCache(void)
{
	dGeomTriMeshClearTCCache(_GeomID);
}

void PhysicsTriMeshGeom::getTriangle( Int32 index, Vec3f& v0, Vec3f& v1, Vec3f& v2 ) const
{
	dVector3 _v0, _v1, _v2;
	dGeomTriMeshGetTriangle(_GeomID, index, &_v0, &_v1, &_v2);
	v0.setValue(Vec3f(_v0[0], _v0[1], _v0[2]));
	v1.setValue(Vec3f(_v1[0], _v1[1], _v1[2]));
	v2.setValue(Vec3f(_v2[0], _v2[1], _v2[2]));
}

UInt32 PhysicsTriMeshGeom::getTriangleCount(void) const
{
	return dGeomTriMeshGetTriangleCount(_GeomID);
}

void PhysicsTriMeshGeom::getPoint( Int32 index, Real32 u, Real32 v, Vec3f& out ) const
{
	dVector3 _out;
	dGeomTriMeshGetPoint(_GeomID, index, u, v, _out);
	out.setValue(Vec3f(_out[0], _out[1], _out[2]));
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void PhysicsTriMeshGeom::onCreate(const PhysicsTriMeshGeom *)
{
	_GeomID = dCreateTriMesh(0, 0, 0, 0, 0);
	_TriMeshData = 0;
    setCategoryBits(dGeomGetCategoryBits(_GeomID));
    setCollideBits(dGeomGetCollideBits(_GeomID));
}

void PhysicsTriMeshGeom::onDestroy()
{
	if (_TriMeshData) dGeomTriMeshDataDestroy(_TriMeshData);
}

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

void PhysicsTriMeshGeom::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

	if(whichField & GeometryNodeFieldMask)
	{
		createODEGeometry(getGeometryNode());
	}
}

void PhysicsTriMeshGeom::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump PhysicsTriMeshGeom NI" << std::endl;
}

OSG_END_NAMESPACE
