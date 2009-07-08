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

#ifndef _OSGPERLINNOISEDISTRIBUTION2D_H_
#define _OSGPERLINNOISEDISTRIBUTION2D_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGPerlinNoiseDistribution2DBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PerlinNoiseDistribution2D class. See \ref 
           PageDynamicsPerlinNoiseDistribution2D for a description.
*/

#define OSG_PERLINNOISE2D_DIST_OUTPUTPARAMETERS (1, \
    (\
      ("RandomValue", Real32) \
    ))


#define OSG_PERLINNOISE2D_DIST_INPUTPARAMETERS (1, \
    (\
      ("Parameter", Pnt2f) \
    ))


class OSG_DYNAMICSLIB_DLLMAPPING PerlinNoiseDistribution2D : public PerlinNoiseDistribution2DBase
{
  private:

    typedef PerlinNoiseDistribution2DBase Inherited;

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

    /*! \}   */

	virtual FunctionIOTypeVector getOutputTypes(FunctionIOTypeVector& InputTypes) const;
    virtual FunctionIOTypeVector getInputTypes(FunctionIOTypeVector& OutputTypes) const;
    virtual FunctionIOParameterVector evaluate(FunctionIOParameterVector& InputParameters);

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in PerlinNoiseDistribution2DBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PerlinNoiseDistribution2D(void);
    PerlinNoiseDistribution2D(const PerlinNoiseDistribution2D &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PerlinNoiseDistribution2D(void); 

    /*! \}*/

    Real32 generate(Pnt2f t) const;
	Real32 interpolatedNoise(Pnt2f t, UInt32 & octave) const;
	Real32 interpolateCosine(Real32 a, Real32 b, Real32 t) const;
	Real32 interpolateLinear(Real32 a, Real32 b, Real32 t) const;
	Real32 smoothNoise(Real32 x, Real32 y, UInt32 & octave) const;
	Real32 getNoise(Int32 t1, Int32 t2, UInt32 & octave) const;

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class PerlinNoiseDistribution2DBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const PerlinNoiseDistribution2D &source);
};

typedef PerlinNoiseDistribution2D *PerlinNoiseDistribution2DP;

OSG_END_NAMESPACE

#include "OSGPerlinNoiseDistribution2DBase.inl"
#include "OSGPerlinNoiseDistribution2D.inl"

#define OSGPERLINNOISEDISTRIBUTION2D_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGPERLINNOISEDISTRIBUTION2D_H_ */
