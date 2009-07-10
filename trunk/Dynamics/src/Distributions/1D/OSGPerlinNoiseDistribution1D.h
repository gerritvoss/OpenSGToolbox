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

#ifndef _OSGPERLINNOISEDISTRIBUTION1D_H_
#define _OSGPERLINNOISEDISTRIBUTION1D_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGPerlinNoiseDistribution1DBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PerlinNoiseDistribution1D class. See \ref 
           PageDynamicsPerlinNoiseDistribution1D for a description.
*/

#define OSG_PERLINNOISE_DIST_OUTPUTPARAMETERS (1, \
    (\
      ("RandomValue", Real32) \
    ))


#define OSG_PERLINNOISE_DIST_INPUTPARAMETERS (1, \
    (\
      ("Parameter", Real32) \
    ))

class OSG_DYNAMICSLIB_DLLMAPPING PerlinNoiseDistribution1D : public PerlinNoiseDistribution1DBase
{
  private:

    typedef PerlinNoiseDistribution1DBase Inherited;

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

    /*! \} */

	virtual FunctionIOTypeVector getOutputTypes(FunctionIOTypeVector& InputTypes) const;
    virtual FunctionIOTypeVector getInputTypes(FunctionIOTypeVector& OutputTypes) const;
    virtual FunctionIOParameterVector evaluate(FunctionIOParameterVector& InputParameters);

	Real32 generate(Real32 t) const;

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in PerlinNoiseDistribution1DBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PerlinNoiseDistribution1D(void);
    PerlinNoiseDistribution1D(const PerlinNoiseDistribution1D &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PerlinNoiseDistribution1D(void); 

    /*! \}                                                                 */

	
	Real32 interpolatedNoise(Real32 t, UInt32 & octave) const;
	Real32 interpolateLinear(Real32 a, Real32 b, Real32 t) const;
	Real32 interpolateCosine(Real32 a, Real32 b, Real32 t) const;
	Real32 getNoise(Int32 t, UInt32 & octave) const;

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class PerlinNoiseDistribution1DBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const PerlinNoiseDistribution1D &source);
};

typedef PerlinNoiseDistribution1D *PerlinNoiseDistribution1DP;

OSG_END_NAMESPACE

#include "OSGPerlinNoiseDistribution1DBase.inl"
#include "OSGPerlinNoiseDistribution1D.inl"

#define OSGPERLINNOISEDISTRIBUTION1D_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGPERLINNOISEDISTRIBUTION1D_H_ */
