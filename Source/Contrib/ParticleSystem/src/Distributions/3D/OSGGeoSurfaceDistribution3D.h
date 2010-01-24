/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#ifndef _OSGGEOSURFACEDISTRIBUTION3D_H_
#define _OSGGEOSURFACEDISTRIBUTION3D_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGeoSurfaceDistribution3DBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief GeoSurfaceDistribution3D class. See \ref
           PageContribParticleSystemGeoSurfaceDistribution3D for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING GeoSurfaceDistribution3D : public GeoSurfaceDistribution3DBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef GeoSurfaceDistribution3DBase Inherited;
    typedef GeoSurfaceDistribution3D     Self;

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

    virtual Vec3f generate(void) const;

    virtual void generate(Pnt3f& Pos, Vec3f& Normal, Vec3f& Tangent) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in GeoSurfaceDistribution3DBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    GeoSurfaceDistribution3D(void);
    GeoSurfaceDistribution3D(const GeoSurfaceDistribution3D &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GeoSurfaceDistribution3D(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	
	void updateSurfaceArea(void);
	
	std::vector<Real32> mAreaVector;
	
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class GeoSurfaceDistribution3DBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const GeoSurfaceDistribution3D &source);
};

typedef GeoSurfaceDistribution3D *GeoSurfaceDistribution3DP;

OSG_END_NAMESPACE

#include "OSGGeoSurfaceDistribution3DBase.inl"
#include "OSGGeoSurfaceDistribution3D.inl"

#endif /* _OSGGEOSURFACEDISTRIBUTION3D_H_ */
