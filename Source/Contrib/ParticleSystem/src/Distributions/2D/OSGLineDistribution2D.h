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

#ifndef _OSGLINEDISTRIBUTION2D_H_
#define _OSGLINEDISTRIBUTION2D_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGLineDistribution2DBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief LineDistribution2D class. See \ref
           PageContribParticleSystemLineDistribution2D for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING LineDistribution2D : public LineDistribution2DBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef LineDistribution2DBase Inherited;
    typedef LineDistribution2D     Self;

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

    virtual Vec2f generate(void) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in LineDistribution2DBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    LineDistribution2D(void);
    LineDistribution2D(const LineDistribution2D &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LineDistribution2D(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class LineDistribution2DBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const LineDistribution2D &source);
};

typedef LineDistribution2D *LineDistribution2DP;

OSG_END_NAMESPACE

#include "OSGLineDistribution2DBase.inl"
#include "OSGLineDistribution2D.inl"

#endif /* _OSGLINEDISTRIBUTION2D_H_ */
