/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala, Dan Guilliams (djkabala/dan.guilliams@gmail.com)*
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

#ifndef _OSGATTRIBUTEPARTICLEFUNCTION_H_
#define _OSGATTRIBUTEPARTICLEFUNCTION_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAttributeParticleFunctionBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief AttributeParticleFunction class. See \ref
           PageContribParticleSystemAttributeParticleFunction for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING AttributeParticleFunction : public AttributeParticleFunctionBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

	  enum SequenceOrder { DIRECT = 1, CUSTOM = 2 };

	virtual UInt32 evaluate(ParticleSystemUnrecPtr System, UInt32 ParticleIndex, UInt32 SequenceLength);

    typedef AttributeParticleFunctionBase Inherited;
    typedef AttributeParticleFunction     Self;

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
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in AttributeParticleFunctionBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AttributeParticleFunction(void);
    AttributeParticleFunction(const AttributeParticleFunction &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AttributeParticleFunction(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AttributeParticleFunctionBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AttributeParticleFunction &source);
};

typedef AttributeParticleFunction *AttributeParticleFunctionP;

OSG_END_NAMESPACE

#include "OSGAttributeParticleFunctionBase.inl"
#include "OSGAttributeParticleFunction.inl"

#endif /* _OSGATTRIBUTEPARTICLEFUNCTION_H_ */
