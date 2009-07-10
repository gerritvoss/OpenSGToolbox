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

#ifndef _OSGPERLINNOISEDISTRIBUTION3D_H_
#define _OSGPERLINNOISEDISTRIBUTION3D_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGPerlinNoiseDistribution3DBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PerlinNoiseDistribution3D class. See \ref 
           PageDynamicsPerlinNoiseDistribution3D for a description.
*/

#define OSG_PERLINNOISE3D_DIST_OUTPUTPARAMETERS (1, \
    (\
      ("RandomValue", Real32) \
    ))


#define OSG_PERLINNOISE3D_DIST_INPUTPARAMETERS (1, \
    (\
      ("Parameter", Pnt3f) \
    ))

class OSG_DYNAMICSLIB_DLLMAPPING PerlinNoiseDistribution3D : public PerlinNoiseDistribution3DBase
{
  private:

    typedef PerlinNoiseDistribution3DBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
	enum InterpolationType {COSINE,LINEAR};	
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

	Real32 generate(Pnt3f t) const;

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in PerlinNoiseDistribution3DBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PerlinNoiseDistribution3D(void);
    PerlinNoiseDistribution3D(const PerlinNoiseDistribution3D &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PerlinNoiseDistribution3D(void); 

    /*! \}																   */

	
	Real32 interpolatedNoise(Pnt3f t, UInt32 & octave) const;
	Real32 interpolateCosine(Real32 a, Real32 b, Real32 t) const;
	Real32 interpolateLinear(Real32 a, Real32 b, Real32 t) const;
	Real32 smoothNoise(Real32 x, Real32 y, Real32 z, UInt32 & octave) const;
	Real32 getNoise(Int32 t1, Int32 t2, Int32 t3, UInt32 & octave) const;
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class PerlinNoiseDistribution3DBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const PerlinNoiseDistribution3D &source);
};

typedef PerlinNoiseDistribution3D *PerlinNoiseDistribution3DP;

OSG_END_NAMESPACE

#include "OSGPerlinNoiseDistribution3DBase.inl"
#include "OSGPerlinNoiseDistribution3D.inl"

#define OSGPERLINNOISEDISTRIBUTION3D_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGPERLINNOISEDISTRIBUTION3D_H_ */
