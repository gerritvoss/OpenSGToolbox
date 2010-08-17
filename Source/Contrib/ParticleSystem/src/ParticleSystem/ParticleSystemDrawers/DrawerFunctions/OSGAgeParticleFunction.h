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

#ifndef _OSGAGEPARTICLEFUNCTION_H_
#define _OSGAGEPARTICLEFUNCTION_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAgeParticleFunctionBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief AgeParticleFunction class. See \ref
           PageContribParticleSystemAgeParticleFunction for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING AgeParticleFunction : public AgeParticleFunctionBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
	
	  enum SequenceOrder { CYCLE = 1, REVERSE_CYCLE = 2, CUSTOM = 3 };

	virtual UInt32 evaluate(ParticleSystemUnrecPtr System, UInt32 ParticleIndex, UInt32 SequenceLength);

    typedef AgeParticleFunctionBase Inherited;
    typedef AgeParticleFunction     Self;

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

    // Variables should all be in AgeParticleFunctionBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AgeParticleFunction(void);
    AgeParticleFunction(const AgeParticleFunction &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AgeParticleFunction(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AgeParticleFunctionBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AgeParticleFunction &source);
};

typedef AgeParticleFunction *AgeParticleFunctionP;

OSG_END_NAMESPACE

#include "OSGAgeParticleFunctionBase.inl"
#include "OSGAgeParticleFunction.inl"

#endif /* _OSGAGEPARTICLEFUNCTION_H_ */
