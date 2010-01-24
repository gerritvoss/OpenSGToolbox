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

#ifndef _OSGSEGMENTDISTRIBUTION1D_H_
#define _OSGSEGMENTDISTRIBUTION1D_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSegmentDistribution1DBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief SegmentDistribution1D class. See \ref
           PageContribParticleSystemSegmentDistribution1D for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING SegmentDistribution1D : public SegmentDistribution1DBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SegmentDistribution1DBase Inherited;
    typedef SegmentDistribution1D     Self;

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

    virtual Real32 generate(void) const;
    
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SegmentDistribution1DBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SegmentDistribution1D(void);
    SegmentDistribution1D(const SegmentDistribution1D &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SegmentDistribution1D(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SegmentDistribution1DBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SegmentDistribution1D &source);
};

typedef SegmentDistribution1D *SegmentDistribution1DP;

OSG_END_NAMESPACE

#include "OSGSegmentDistribution1DBase.inl"
#include "OSGSegmentDistribution1D.inl"

#endif /* _OSGSEGMENTDISTRIBUTION1D_H_ */
