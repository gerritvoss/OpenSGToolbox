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

#ifndef _OSGPHYSICSTRIMESHGEOM_H_
#define _OSGPHYSICSTRIMESHGEOM_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPhysicsTriMeshGeomBase.h"
#include "OSGNode.h"

OSG_BEGIN_NAMESPACE

/*! \brief PhysicsTriMeshGeom class. See \ref
           PageContribPhysicsPhysicsTriMeshGeom for a description.
*/

class OSG_CONTRIBPHYSICS_DLLMAPPING PhysicsTriMeshGeom : public PhysicsTriMeshGeomBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PhysicsTriMeshGeomBase Inherited;
    typedef PhysicsTriMeshGeom     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Class Specific                             */
    /*! \{																*/
    void setCallback( dTriCallback* callback );
    dTriCallback* getCallback(void) const;
    void setArrayCallback( dTriArrayCallback* arrayCallback );
    dTriArrayCallback* getArrayCallback(void) const;
    void setRayCallback( dTriRayCallback* callback );
    dTriRayCallback* getRayCallback(void) const;
    void setData( dTriMeshDataID data );

    void enableTC( Int32 geomClass, bool enable );
    bool isTCEnabled( Int32 geomClass ) const;
    void clearTCCache(void);
    void getTriangle( Int32 index, Vec3f& v0, Vec3f& v1, Vec3f& v2 ) const;
    UInt32 getTriangleCount(void) const;
    void getPoint( Int32 index, Real32 u, Real32 v, Vec3f& out ) const;
    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in PhysicsTriMeshGeomBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PhysicsTriMeshGeom(void);
    PhysicsTriMeshGeom(const PhysicsTriMeshGeom &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PhysicsTriMeshGeom(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const PhysicsTriMeshGeom *id = NULL);
	void onDestroy();
	void createODEGeometry(NodeUnrecPtr node);
	/*! \}                                                                 */
	dTriMeshDataID _TriMeshData;

    std::vector<dTriIndex> _TriIndexes;
    std::vector<Pnt3f> _Positions;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PhysicsTriMeshGeomBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PhysicsTriMeshGeom &source);
};

typedef PhysicsTriMeshGeom *PhysicsTriMeshGeomP;

OSG_END_NAMESPACE

#include "OSGPhysicsTriMeshGeomBase.inl"
#include "OSGPhysicsTriMeshGeom.inl"

#endif /* _OSGPHYSICSTRIMESHGEOM_H_ */
