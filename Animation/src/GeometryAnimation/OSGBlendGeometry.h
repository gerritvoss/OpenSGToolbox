/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox Animation                            *
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

#ifndef _OSGBLENDGEOMETRY_H_
#define _OSGBLENDGEOMETRY_H_
#ifdef __sgi
#pragma once
#endif
#include <OpenSG/OSGConfig.h>
#include "OSGAnimationDef.h"

#include "OSGBlendGeometryBase.h"

OSG_BEGIN_NAMESPACE

class OSG_ANIMATIONLIB_DLLMAPPING BlendGeometry : public BlendGeometryBase
{
  private:

    typedef BlendGeometryBase Inherited;

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
    static  BlendGeometryPtr      create          (const GeometryPtr Geo); 
    void setBaseGeometry(const GeometryPtr Geo);
    void addBlendGeometry(const GeometryPtr Geo, Real32 b = 0.0f);
    void removeBlendGeometry(UInt32 GeoIndex);

    UInt32 getNumBlendGeometries(void) const;
    void setBlendAmount(UInt32 GeoIndex, Real32 b);
    
    /*=========================  PROTECTED  ===============================*/
  protected:

    void recalculatePositions(void);
    void recalculateNormals(void);

    void recalculateColors(void);
    void recalculateSecondaryColors(void);
    
    void recalculateTexCoords(UInt32 CoordNum);

    // Variables should all be in BlendGeometryBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    BlendGeometry(void);
    BlendGeometry(const BlendGeometry &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~BlendGeometry(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class BlendGeometryBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const BlendGeometry &source);
};

typedef BlendGeometry *BlendGeometryP;

OSG_END_NAMESPACE

#include "OSGBlendGeometryBase.inl"
#include "OSGBlendGeometry.inl"

#define OSGBLENDGEOMETRY_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGBLENDGEOMETRY_H_ */
