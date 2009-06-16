/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Dynamics                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#include "OSGDynamicsDef.h"

#include "OSGGeoSurfaceDistribution3DBase.h"

OSG_BEGIN_NAMESPACE

#define OSG_GEO_SURFACE_3D_DIST_OUTPUTPARAMETERS (3, \
    (\
      ("Position", Pnt3f), \
      ("Normal", Vec3f), \
      ("Tangent", Vec3f) \
    ))

#define OSG_GEO_SURFACE_3D_DIST_INPUTPARAMETERS (0, ())
class OSG_DYNAMICSLIB_DLLMAPPING GeoSurfaceDistribution3D : public GeoSurfaceDistribution3DBase
{
  private:

    typedef GeoSurfaceDistribution3DBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    virtual FunctionIOTypeVector getOutputTypes(FunctionIOTypeVector& InputTypes) const;
    virtual FunctionIOTypeVector getInputTypes(FunctionIOTypeVector& OutputTypes) const;
    virtual FunctionIOParameterVector evaluate(FunctionIOParameterVector& InputParameters);
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

    virtual void generate(Pnt3f& Pos, Vec3f& Normal, Vec3f& Tangent);
    /*! \}                                                                 */
	
	void updateSurfaceArea(void);
	
	
	std::vector<Real32> mAreaVector;
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class GeoSurfaceDistribution3DBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const GeoSurfaceDistribution3D &source);
};

typedef GeoSurfaceDistribution3D *GeoSurfaceDistribution3DP;

OSG_END_NAMESPACE

#include "OSGGeoSurfaceDistribution3DBase.inl"
#include "OSGGeoSurfaceDistribution3D.inl"

#define OSGGEOSURFACEDISTRIBUTION3D_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGGEOSURFACEDISTRIBUTION3D_H_ */
