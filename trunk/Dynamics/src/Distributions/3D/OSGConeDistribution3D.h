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

#ifndef _OSGCONEDISTRIBUTION3D_H_
#define _OSGCONEDISTRIBUTION3D_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGDynamicsDef.h"

#include "OSGConeDistribution3DBase.h"
#include <OpenSG/OSGVecFieldDataType.h>

OSG_BEGIN_NAMESPACE

#define OSG_CONE3D_DIST_OUTPUTPARAMETERS (1, \
    (\
      ("RandomPoint", Pnt3f) \
    ))

#define OSG_CONE3D_DIST_INPUTPARAMETERS (0, ())

/*! \brief ConeDistribution3D class. See \ref 
           PageDynamicsConeDistribution3D for a description.
*/

class OSG_DYNAMICSLIB_DLLMAPPING ConeDistribution3D : public ConeDistribution3DBase
{
  private:

    typedef ConeDistribution3DBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    enum SurfaceOrVolume {VOLUME=0, SURFACE=1};
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

    // Variables should all be in ConeDistribution3DBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ConeDistribution3D(void);
    ConeDistribution3D(const ConeDistribution3D &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ConeDistribution3D(void); 

    /*! \}                                                                 */
    virtual Pnt3f generate(void);
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ConeDistribution3DBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ConeDistribution3D &source);
};

typedef ConeDistribution3D *ConeDistribution3DP;

OSG_END_NAMESPACE

#include "OSGConeDistribution3DBase.inl"
#include "OSGConeDistribution3D.inl"

#define OSGCONEDISTRIBUTION3D_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGCONEDISTRIBUTION3D_H_ */
