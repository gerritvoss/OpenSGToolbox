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

#ifndef _OSGSEGMENTSETDISTRIBUTION1D_H_
#define _OSGSEGMENTSETDISTRIBUTION1D_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGParticleSystemDef.h"

#include "OSGSegmentSetDistribution1DBase.h"
#include <OpenSG/OSGSysFieldDataType.h>

OSG_BEGIN_NAMESPACE

#define OSG_SEGMENTSET_DIST_OUTPUTPARAMETERS (1, \
    (\
      ("RandomValue", Real32) \
    ))


#define OSG_SEGMENTSET_DIST_INPUTPARAMETERS (0, ())

class OSG_PARTICLESYSTEMLIB_DLLMAPPING SegmentSetDistribution1D : public SegmentSetDistribution1DBase
{
  private:

    typedef SegmentSetDistribution1DBase Inherited;

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

    // Variables should all be in SegmentSetDistribution1DBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SegmentSetDistribution1D(void);
    SegmentSetDistribution1D(const SegmentSetDistribution1D &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SegmentSetDistribution1D(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class SegmentSetDistribution1DBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const SegmentSetDistribution1D &source);
};

typedef SegmentSetDistribution1D *SegmentSetDistribution1DP;

OSG_END_NAMESPACE

#include "OSGSegmentSetDistribution1DBase.inl"
#include "OSGSegmentSetDistribution1D.inl"

#endif /* _OSGSEGMENTSETDISTRIBUTION1D_H_ */
