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

#ifndef _OSGGAUSSIANNORMALDISTRIBUTION1D_H_
#define _OSGGAUSSIANNORMALDISTRIBUTION1D_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGaussianNormalDistribution1DBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief GaussianNormalDistribution1D class. See \ref
           PageContribParticleSystemGaussianNormalDistribution1D for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING GaussianNormalDistribution1D : public GaussianNormalDistribution1DBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef GaussianNormalDistribution1DBase Inherited;
    typedef GaussianNormalDistribution1D     Self;

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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class GaussianNormalDistribution1DBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const GaussianNormalDistribution1D &source);
};

typedef GaussianNormalDistribution1D *GaussianNormalDistribution1DP;

OSG_END_NAMESPACE

#include "OSGGaussianNormalDistribution1DBase.inl"
#include "OSGGaussianNormalDistribution1D.inl"

#endif /* _OSGGAUSSIANNORMALDISTRIBUTION1D_H_ */
