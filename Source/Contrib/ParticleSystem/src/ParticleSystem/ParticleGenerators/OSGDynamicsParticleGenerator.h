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

#ifndef _OSGDYNAMICSPARTICLEGENERATOR_H_
#define _OSGDYNAMICSPARTICLEGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDynamicsParticleGeneratorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief DynamicsParticleGenerator class. See \ref
           PageContribParticleSystemDynamicsParticleGenerator for a description.
*/

class OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING DynamicsParticleGenerator : public DynamicsParticleGeneratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DynamicsParticleGeneratorBase Inherited;
    typedef DynamicsParticleGenerator     Self;

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

    // Variables should all be in DynamicsParticleGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DynamicsParticleGenerator(void);
    DynamicsParticleGenerator(const DynamicsParticleGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DynamicsParticleGenerator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

	void generateDynamic(ParticleSystemRefPtr System, Real32 AdditionalAging = 0.0f) const;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DynamicsParticleGeneratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DynamicsParticleGenerator &source);
};

typedef DynamicsParticleGenerator *DynamicsParticleGeneratorP;

OSG_END_NAMESPACE

#include "OSGDynamicsParticleGeneratorBase.inl"
#include "OSGDynamicsParticleGenerator.inl"

#endif /* _OSGDYNAMICSPARTICLEGENERATOR_H_ */
