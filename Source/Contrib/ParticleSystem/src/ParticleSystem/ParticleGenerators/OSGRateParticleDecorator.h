/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com), Daniel Guilliams           *
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

#ifndef _OSGRATEPARTICLEDECORATOR_H_
#define _OSGRATEPARTICLEDECORATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGRateParticleDecoratorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief RateParticleDecorator class. See \ref
           PageContribParticleSystemRateParticleDecorator for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING RateParticleDecorator : public RateParticleDecoratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef RateParticleDecoratorBase Inherited;
    typedef RateParticleDecorator     Self;

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
	virtual bool generate(ParticleSystemRefPtr System, const Time& elps);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in RateParticleDecoratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    RateParticleDecorator(void);
    RateParticleDecorator(const RateParticleDecorator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~RateParticleDecorator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class RateParticleDecoratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const RateParticleDecorator &source);
};

typedef RateParticleDecorator *RateParticleDecoratorP;

OSG_END_NAMESPACE

#include "OSGRateParticleDecoratorBase.inl"
#include "OSGRateParticleDecorator.inl"

#endif /* _OSGRATEPARTICLEDECORATOR_H_ */
