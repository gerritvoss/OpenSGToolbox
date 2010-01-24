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

#ifndef _OSGPERLINNOISEDISTRIBUTION3D_H_
#define _OSGPERLINNOISEDISTRIBUTION3D_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPerlinNoiseDistribution3DBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PerlinNoiseDistribution3D class. See \ref
           PageContribParticleSystemPerlinNoiseDistribution3D for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING PerlinNoiseDistribution3D : public PerlinNoiseDistribution3DBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
	enum InterpolationType {COSINE = 1,LINEAR = 2};	

    typedef PerlinNoiseDistribution3DBase Inherited;
    typedef PerlinNoiseDistribution3D     Self;

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

    virtual Vec3f generate(void) const;

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

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PerlinNoiseDistribution3DBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PerlinNoiseDistribution3D &source);
};

typedef PerlinNoiseDistribution3D *PerlinNoiseDistribution3DP;

OSG_END_NAMESPACE

#include "OSGPerlinNoiseDistribution3DBase.inl"
#include "OSGPerlinNoiseDistribution3D.inl"

#endif /* _OSGPERLINNOISEDISTRIBUTION3D_H_ */
