/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#ifndef _OSGGAUSSIANNORMADISTRIBUTION2D_H_
#define _OSGGAUSSIANNORMADISTRIBUTION2D_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDynamicsConfig.h"

#include "OSGGaussianNormaDistribution2DBase.h"

OSG_BEGIN_NAMESPACE

class OSG_DYNAMICS_CLASS_API GaussianNormaDistribution2D : public GaussianNormaDistribution2DBase
{
  private:

    typedef GaussianNormaDistribution2DBase Inherited;

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
    virtual Pnt2f generate(void);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in GaussianNormaDistribution2DBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    GaussianNormaDistribution2D(void);
    GaussianNormaDistribution2D(const GaussianNormaDistribution2D &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GaussianNormaDistribution2D(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class GaussianNormaDistribution2DBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const GaussianNormaDistribution2D &source);
};

typedef GaussianNormaDistribution2D *GaussianNormaDistribution2DP;

OSG_END_NAMESPACE

#include "OSGGaussianNormaDistribution2DBase.inl"
#include "OSGGaussianNormaDistribution2D.inl"

#define OSGGAUSSIANNORMADISTRIBUTION2D_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGGAUSSIANNORMADISTRIBUTION2D_H_ */
