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

#ifndef _OSGLINEDISTRIBUTION3D_H_
#define _OSGLINEDISTRIBUTION3D_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGLineDistribution3DBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief LineDistribution3D class. See \ref
           PageContribParticleSystemLineDistribution3D for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING LineDistribution3D : public LineDistribution3DBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef LineDistribution3DBase Inherited;
    typedef LineDistribution3D     Self;

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

    // Variables should all be in LineDistribution3DBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    LineDistribution3D(void);
    LineDistribution3D(const LineDistribution3D &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LineDistribution3D(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class LineDistribution3DBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const LineDistribution3D &source);
};

typedef LineDistribution3D *LineDistribution3DP;

OSG_END_NAMESPACE

#include "OSGLineDistribution3DBase.inl"
#include "OSGLineDistribution3D.inl"

#endif /* _OSGLINEDISTRIBUTION3D_H_ */
