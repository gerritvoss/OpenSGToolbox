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

#ifndef _OSGBOXDISTRIBUTION3D_H_
#define _OSGBOXDISTRIBUTION3D_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBoxDistribution3DBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief BoxDistribution3D class. See \ref
           PageContribParticleSystemBoxDistribution3D for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING BoxDistribution3D : public BoxDistribution3DBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum SurfaceOrVolume {VOLUME=0, SURFACE=1};

    typedef BoxDistribution3DBase Inherited;
    typedef BoxDistribution3D     Self;

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

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in BoxDistribution3DBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    BoxDistribution3D(void);
    BoxDistribution3D(const BoxDistribution3D &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~BoxDistribution3D(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class BoxDistribution3DBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const BoxDistribution3D &source);
};

typedef BoxDistribution3D *BoxDistribution3DP;

OSG_END_NAMESPACE

#include "OSGBoxDistribution3DBase.inl"
#include "OSGBoxDistribution3D.inl"

#endif /* _OSGBOXDISTRIBUTION3D_H_ */
