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

#ifndef _OSGGAUSSIANNORMALDISTRIBUTION1D_H_
#define _OSGGAUSSIANNORMALDISTRIBUTION1D_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGParticleSystemDef.h"

#include "OSGGaussianNormalDistribution1DBase.h"
#include <OpenSG/OSGSysFieldDataType.h>

OSG_BEGIN_NAMESPACE

class OSG_PARTICLESYSTEMLIB_DLLMAPPING GaussianNormalDistribution1D : public GaussianNormalDistribution1DBase
{
  private:

    typedef GaussianNormalDistribution1DBase Inherited;

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

    virtual Real32 generate(void) const;

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in GaussianNormalDistribution1DBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    GaussianNormalDistribution1D(void);
    GaussianNormalDistribution1D(const GaussianNormalDistribution1D &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GaussianNormalDistribution1D(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class GaussianNormalDistribution1DBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const GaussianNormalDistribution1D &source);
};

typedef GaussianNormalDistribution1D *GaussianNormalDistribution1DP;

OSG_END_NAMESPACE

#include "OSGGaussianNormalDistribution1DBase.inl"
#include "OSGGaussianNormalDistribution1D.inl"

#endif /* _OSGGAUSSIANNORMALDISTRIBUTION1D_H_ */
